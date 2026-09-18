#ifndef _PE_SHP_REG_O26A0_H_
#define _PE_SHP_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC952000 RW 0x0000_0421
	UINT32 reg_top_actv_sel                 :1;	//(0:0,NA,1) //0: use core pass-through active	1: use active sync delay active
	UINT32 reg_pat_head                     :1;	//(1:1,NA,0) //H-pattern enable (for HEAD map)
	UINT32 reg_pat_body                     :1;	//(2:2,NA,0) //H-pattern enable (for BODY map)
	UINT32 reg_pat_text_rgn                 :1;	//(3:3,NA,0) //H-pattern enable (for text region map)
	UINT32 reg_top_core_detour              :1;	//(4:4,NA,0) //SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//(5:5,NA,1) //SHP core bypass enable
	UINT32 reg_iir_rst                      :1;	//(6:6,NA,0) //Tmap/Text IIR reset (reset to first frame)
	UINT32 resvd0                           :1;
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,0) //0: sync-based, 1: valid-based
	UINT32 reg_pat_black                    :1;	//(9:9,NA,0) //HEAD/BODY/TEXT to black
	UINT32 reg_etc_sync_dly_gen_en          :1;	//(10:10,NA,1) //General delay mode enable for rest of sync_actv_dly (to prevent abnormal case)
	UINT32 resvd1                           :9;
	UINT32 reg_top_lsb_copy_mode            :2;	//(21:20,NA,0) //0: lsb force 0	1: lsb force 1	2: lsb force copy [1] -> [0]
	UINT32 resvd2                           :2;
	UINT32 reg_top_422to444_mode            :1;	//(24:24,NA,0) //0: H-average mode	1: repeatition mode
	UINT32 resvd3                           :3;
	UINT32 reg_top_mode_444                 :1;	//(28:28,NA,0) //0: 422 mode	1: 444 mode
	UINT32 reg_top_mode_8k                  :1;	//(29:29,NA,0) //Simple SHP 8K DP mode (444)
	UINT32 reg_obc_debug                    :2;	//(31:30,NA,0) //0: SHP result 	1: face map	2: object map
	};
}PE_O26_VSD_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952004 RW 0x0870_0F00
	UINT32 reg_top_width                    :16;	//(15:0,NA,3840) //Processing width (default : 3840)
	UINT32 reg_top_height                   :16;	//(31:16,NA,2160) //Processing height (default : 2160)
	};
}PE_O26_VSD_SHP_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952008 RW 0x0118_0003
	UINT32 reg_top_use_extern_valid         :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//(1:1,NA,1) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_VSD_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95200C RW 0x0000_000C
	UINT32 reg_top_pic_init_latency         :16;	//(15:0,NA,12) //Pic init latency
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952010 RW 0x0000_0019
	UINT32 reg_top_update_ctrl              :5;	//(4:0,NA,25) //[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd                            :27;
	};
}PE_O26_VSD_SHP_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952014 RW 0x0E00_0810
	UINT32 reg_new_fd_detail_beta_mul       :8;	//(7:0,NA,16) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul      :8;	//(15:8,NA,8) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul         :8;	//(23:16,NA,0) //Get t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul        :8;	//(31:24,NA,14) //Get t_map (alpha*t_map - beta*a_map)
	};
}PE_O26_VSD_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952018 RW 0x60A0_0020
	UINT32 reg_new_fd_edge_minmax_y0        :8;	//(7:0,NA,32) //Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0        :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1        :8;	//(23:16,NA,160) //Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1        :8;	//(31:24,NA,96) //Final edge LUT, x1
	};
}PE_O26_VSD_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95201C RW 0xFFFF_82DC
	UINT32 reg_new_fd_edge_minmax_y2        :8;	//(7:0,NA,220) //Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2        :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3        :8;	//(23:16,NA,255) //Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3        :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O26_VSD_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952020 RW 0x2860_0040
	UINT32 reg_new_fd_detail_minmax_y0      :8;	//(7:0,NA,64) //Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0      :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1      :8;	//(23:16,NA,96) //Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1      :8;	//(31:24,NA,40) //Final detail LUT, x1
	};
}PE_O26_VSD_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952024 RW 0x64A0_4678
	UINT32 reg_new_fd_detail_minmax_y2      :8;	//(7:0,NA,120) //Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2      :8;	//(15:8,NA,70) //Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3      :8;	//(23:16,NA,160) //Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3      :8;	//(31:24,NA,100) //Final detail LUT, x3
	};
}PE_O26_VSD_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952028 RW 0x0000_0180
	UINT32 reg_texture_region_alpha         :8;	//(7:0,NA,128) //Region texture blending alpha
	UINT32 reg_region_text_en_aux           :1;	//(8:8,NA,1) //Region texture enable
	UINT32 reg_obj_shp_en_aux               :1;	//(9:9,NA,0) //Object SHP enable
	UINT32 resvd                            :22;
	};
}PE_O26_VSD_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952040 RW 0xFFFF_FF00
	UINT32 reg_pat_en                       :1;	//(0:0,NA,0) //Pattern enable
	UINT32 reg_pat_thickness                :2;	//(2:1,NA,0) //Pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//(15:8,NA,255) //Pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//(23:16,NA,255) //Pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//(31:24,NA,255) //Pattern pixel value (Cr)
	};
}PE_O26_VSD_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952050 RW 0x0000_0000
	UINT32 reg_out_hgos_head_crop_ptr       :15;	//(14:0,NA,0) //Output horizontal gos head crop pointer
	UINT32 reg_out_hgos_head_en             :1;	//(15:15,NA,0) //Output horizontal gos head crop enable
	UINT32 reg_out_hgos_tail_crop_ptr       :15;	//(30:16,NA,0) //Output horizontal gos tail crop pointer
	UINT32 reg_out_hgos_tail_en             :1;	//(31:31,NA,0) //Output horizontal gos tail crop enable
	};
}PE_O26_VSD_SHP_GOS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952060 RW 0x0004_0005
	UINT32 reg_sync_dly_vsync               :16;	//(15:0,NA,5) //V sync (2K
	UINT32 reg_sync_dly_vfp                 :16;	//(31:16,NA,4) //V front porch (2K
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952064 RW 0x0024_0438
	UINT32 reg_sync_dly_va                  :16;	//(15:0,NA,1080) //V active (2K
	UINT32 reg_sync_dly_vbp                 :16;	//(31:16,NA,36) //V back porch (2K
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952068 RW 0x0058_002C
	UINT32 reg_sync_dly_hsync               :16;	//(15:0,NA,44) //H sync (2K
	UINT32 reg_sync_dly_hfp                 :16;	//(31:16,NA,88) //H front porch (2K
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95206C RW 0x0094_0780
	UINT32 reg_sync_dly_ha                  :16;	//(15:0,NA,1920) //H active (2K
	UINT32 reg_sync_dly_hbp                 :16;	//(31:16,NA,148) //H back porch (2K
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952070 RW 0x0000_0060
	UINT32 reg_sync_dly_line_start          :16;	//(15:0,NA,96) //Line increase position
	UINT32 reg_sync_dly_actv_sel_in_h_src   :1;	//(16:16,NA,0) //Select inverse in ha source
	UINT32 reg_sync_dly_actv_sel_in_v_src   :1;	//(17:17,NA,0) //Select inverse in va source
	UINT32 reg_sync_dly_actv_sel_in_h_inv   :1;	//(18:18,NA,0) //Inverse in ha
	UINT32 reg_sync_dly_actv_sel_in_v_inv   :1;	//(19:19,NA,0) //Inverse in va
	UINT32 reg_sync_dly_actv_sel_out_ha     :1;	//(20:20,NA,0) //Select out ha
	UINT32 reg_sync_dly_actv_sel_out_va     :1;	//(21:21,NA,0) //Select out va
	UINT32 reg_sync_dly_actv_sel_out_hs     :1;	//(22:22,NA,0) //Select out hs
	UINT32 reg_sync_dly_actv_sel_out_vs     :1;	//(23:23,NA,0) //Select out vs
	UINT32 reg_sync_dly_tp_update_hv_zero   :1;	//(24:24,NA,0) //Sync parameter update
	UINT32 reg_sync_dly_force_out_ha        :1;	//(25:25,NA,0) //Force out ha
	UINT32 reg_sync_dly_force_out_va        :1;	//(26:26,NA,0) //Force out va
	UINT32 reg_sync_dly_force_out_hs        :1;	//(27:27,NA,0) //Force out hs
	UINT32 reg_sync_dly_cnt_rst_h_value_en  :1;	//(28:28,NA,0) //Manual cnt h value enable
	UINT32 reg_sync_dly_cnt_rst_v_value_en  :1;	//(29:29,NA,0) //Manual cnt v value enable
	UINT32 reg_sync_dly_force_out_vs        :1;	//(30:30,NA,0) //Force out vs
	UINT32 reg_sync_dly_force_update        :1;	//(31:31,NA,0) //Force update
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952074 RW 0x000A_0102
	UINT32 reg_sync_dly_sync_h_dly          :16;	//(15:0,NA,258) //Pixel delay
	UINT32 reg_sync_dly_sync_v_dly          :16;	//(31:16,NA,10) //Line delay
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952078 RW 0x0008_0058
	UINT32 reg_sync_dly_cnt_rst_h_value     :16;	//(15:0,NA,88) //disp_pulse_dly Delay
	UINT32 reg_sync_dly_cnt_rst_v_value     :16;	//(31:16,NA,8) //[RO] disp_pulse_dly Counter
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95207C RW 0x000A_8102
	UINT32 reg_sync_dly_auto_actv_h_dly     :15;	//(14:0,NA,258) //Auto actv pixel delay
	UINT32 reg_sync_dly_auto_actv_gen_en    :1;	//(15:15,NA,1) //Auto actv gen enable
	UINT32 reg_sync_dly_auto_actv_v_dly     :15;	//(30:16,NA,10) //Auto actv line delay
	UINT32 reg_sync_dly_auto_actv_seam_en   :1;	//(31:31,NA,0) //Auto actv seam enable
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952080 RW 0x000A_8102
	UINT32 reg_sync_dly_auto_sync_h_dly     :15;	//(14:0,NA,258) //Auto sync pixel delay
	UINT32 reg_sync_dly_auto_sync_gen_en    :1;	//(15:15,NA,1) //Auto sync gen enable
	UINT32 reg_sync_dly_auto_sync_v_dly     :15;	//(30:16,NA,10) //Auto sync line delay
	UINT32 reg_sync_dly_auto_sync_seam_en   :1;	//(31:31,NA,0) //Auto sync seam enable
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952084 RW 0x0000_0000
	UINT32 reg_sync_dly_normal_number       :16;	//(15:0,NA,0) //Protection mode
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952088 RW 0x0000_0000
	UINT32 reg_sync_dly_cnt_h_rst_position  :16;	//(15:0,NA,0) //Manual cnt h value position
	UINT32 reg_sync_dly_cnt_v_rst_position  :16;	//(31:16,NA,0) //Manual cnt v value position
	};
}PE_O26_VSD_SHP_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952090 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0) //ROI mask pixel value (Y)
	UINT32 reg_roi_mask_pix_val_cb          :8;	//(23:16,NA,0) //ROI mask pixel value (Cb)
	UINT32 reg_roi_mask_pix_val_cr          :8;	//(31:24,NA,0) //ROI mask pixel value (Cr)
	};
}PE_O26_VSD_SHP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952094 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :16;	//(15:0,NA,0) //ROI mask window start position, x0
	UINT32 reg_roi_mask_win_y0              :16;	//(31:16,NA,0) //ROI mask window start position, y0
	};
}PE_O26_VSD_SHP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952098 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :16;	//(15:0,NA,0) //ROI mask window end position, x1
	UINT32 reg_roi_mask_win_y1              :16;	//(31:16,NA,0) //ROI mask window end position, y1
	};
}PE_O26_VSD_SHP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520A0 RW 0x0000_0010
	UINT32 reg_esf_detour_mode              :1;	//(0:0,NA,0) //Edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en         :1;	//(1:1,NA,0) //Edge shift filter buffer detour enable
	UINT32 resvd0                           :2;
	UINT32 reg_esf_en                       :1;	//(4:4,NA,1) //Edge shift filter enable
	UINT32 resvd1                           :3;
	UINT32 reg_esf_dbg_en                   :1;	//(8:8,NA,0) //Edge shift filter debug enable
	UINT32 resvd2                           :23;
	};
}PE_O26_VSD_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520A4 RW 0x4040_C814
	UINT32 reg_esf_min_ratio                :8;	//(7:0,NA,20) //Edge shift filter min ratio
	UINT32 reg_esf_base                     :8;	//(15:8,NA,200) //Edge shift filter base
	UINT32 reg_esf_max_clip                 :8;	//(23:16,NA,64) //Edge shift filter max clipping
	UINT32 reg_esf_master_gain              :8;	//(31:24,NA,64) //Edge shift filter master gain
	};
}PE_O26_VSD_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520A8 RW 0x0000_0819
	UINT32 reg_esf_ltv_offset               :8;	//(7:0,NA,25) //Edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul                  :8;	//(15:8,NA,8) //Edge shift filter ltv mul
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520B0 RW 0x0000_0000
	UINT32 reg_win_esf_win0_en              :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_esf_win1_en              :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_esf_win01_en             :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_esf_win_outside          :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_esf_win_en               :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_esf_bdr_alpha            :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_esf_bdr_wid              :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_esf_bdr_en               :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_esf_cr5                  :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_esf_cb5                  :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_esf_yy6                  :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_VSD_SHP_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520B4 RW 0x0000_0000
	UINT32 reg_win_esf_win_w0_x0            :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_win_esf_win_w0_y0            :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520B8 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w0_x1            :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_win_esf_win_w0_y1            :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520BC RW 0x0000_0000
	UINT32 reg_win_esf_win_w1_x0            :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_win_esf_win_w1_y0            :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520C0 RW 0x086F_0EFF
	UINT32 reg_win_esf_win_w1_x1            :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_win_esf_win_w1_y1            :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9520F0 RW 0x0000_0000
	UINT32 reg_dp_debug_display             :5;	//(4:0,NA,0) //Debug display	0 : Normal display (output 1)	1 : Normal display (output 2)	2 : TGEN only	3 : Luma adaptive gain map	4 : Weight(A)	5 : Weight(Texture)	6 : A-map	7 : T-map	8 : Soft edge gain map	9 : A-map for der	10: Motion map	11: Gain A-map	12: Gain T-map	13: Texture region map	14: OBJT map	15: FACE map	16: Text gain map	17: Non-text gain map
	UINT32 resvd0                           :3;
	UINT32 reg_dp_detour_en                 :1;	//(8:8,NA,0) //DP detour enable
	UINT32 resvd1                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//(12:12,NA,0) //DP buffer detour enable
	UINT32 resvd2                           :19;
	};
}PE_O26_VSD_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952100 RW 0x0001_0003
	UINT32 reg_fd_a_map_h_size              :2;	//(1:0,NA,3) //A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//(8:8,NA,0) //Post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //Pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //Pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //Pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952104 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952108 RW 0x1002_0404
	UINT32 reg_fd_detail_beta_mul           :8;	//(7:0,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//(15:8,NA,4) //Get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//(23:16,NA,2) //Get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//(31:24,NA,16) //Get_t_map (alpha*t_map - beta*a_map)
	};
}PE_O26_VSD_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95210C RW 0x60FF_2000
	UINT32 reg_fd_a_lut_edge_y0             :8;	//(7:0,NA,0) //A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//(15:8,NA,32) //A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//(23:16,NA,255) //A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//(31:24,NA,96) //A-map edge LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952110 RW 0x50FF_1000
	UINT32 reg_fd_a_lut_detail_y0           :8;	//(7:0,NA,0) //A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//(15:8,NA,16) //A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//(23:16,NA,255) //A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//(31:24,NA,80) //A-map detail LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952114 RW 0x50FF_1000
	UINT32 reg_fd_t_lut_edge_y0             :8;	//(7:0,NA,0) //T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//(15:8,NA,16) //T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//(23:16,NA,255) //T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//(31:24,NA,80) //T-map edge LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952118 RW 0x32FF_0040
	UINT32 reg_fd_t_lut_detail_y0           :8;	//(7:0,NA,64) //T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//(15:8,NA,0) //T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//(23:16,NA,255) //T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//(31:24,NA,50) //T-map detail LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95211C RW 0xFF40_0010
	UINT32 reg_fd_edge_minmax_y0            :8;	//(7:0,NA,16) //Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//(15:8,NA,0) //Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//(23:16,NA,64) //Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//(31:24,NA,255) //Final edge LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952120 RW 0xFF80_826E
	UINT32 reg_fd_edge_minmax_y2            :8;	//(7:0,NA,110) //Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//(15:8,NA,130) //Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//(23:16,NA,128) //Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//(31:24,NA,255) //Final edge LUT, x3
	};
}PE_O26_VSD_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952124 RW 0x5040_0018
	UINT32 reg_fd_detail_minmax_y0          :8;	//(7:0,NA,24) //Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//(15:8,NA,0) //Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//(23:16,NA,64) //Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//(31:24,NA,80) //Final detail LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952128 RW 0xA064_6450
	UINT32 reg_fd_detail_minmax_y2          :8;	//(7:0,NA,80) //Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//(15:8,NA,100) //Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//(23:16,NA,100) //Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//(31:24,NA,160) //Final detail LUT, x3
	};
}PE_O26_VSD_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95212C RW 0x0000_0010
	UINT32 reg_fd_mnr_gain_e_en             :1;	//(0:0,NA,0) //Edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//(1:1,NA,0) //Texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//(5:4,NA,1) //s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952130 RW 0x0020_0000
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//(7:0,NA,0) //s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//(23:16,NA,32) //s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_O26_VSD_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952134 RW 0x4000_0005
	UINT32 reg_fd_mnr_gain_x0               :8;	//(7:0,NA,5) //MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//(15:8,NA,0) //MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//(23:16,NA,0) //MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//(31:24,NA,64) //MNR gain LUT, y1
	};
}PE_O26_VSD_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952138 RW 0x0620_0000
	UINT32 reg_fd_dct_t_lut_y0              :8;	//(7:0,NA,0) //DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//(15:8,NA,0) //DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//(23:16,NA,32) //DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//(31:24,NA,6) //DCT T-map LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95213C RW 0x2280_0B40
	UINT32 reg_fd_dct_t_lut_y2              :8;	//(7:0,NA,64) //DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//(15:8,NA,11) //DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//(23:16,NA,128) //DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//(31:24,NA,34) //DCT T-map LUT, x3
	};
}PE_O26_VSD_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952140 RW 0xBBFF_7DC4
	UINT32 reg_fd_dct_t_lut_y4              :8;	//(7:0,NA,196) //DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//(15:8,NA,125) //DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//(23:16,NA,255) //DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//(31:24,NA,187) //DCT T-map LUT, x5
	};
}PE_O26_VSD_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952144 RW 0x0000_0000
	UINT32 reg_fd_soft_gain_e_en            :1;	//(0:0,NA,0) //Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//(1:1,NA,0) //Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_O26_VSD_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952148 RW 0x0000_086E
	UINT32 reg_fd_soft_ratio                :8;	//(7:0,NA,110) //Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//(15:8,NA,8) //Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95214C RW 0x4030_0802
	UINT32 reg_fd_soft_score_x0             :8;	//(7:0,NA,2) //Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//(15:8,NA,8) //Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//(23:16,NA,48) //Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//(31:24,NA,64) //Soft edge score, x3
	};
}PE_O26_VSD_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952150 RW 0x2C3E_0C06
	UINT32 reg_fd_soft_score_y0             :6;	//(5:0,NA,6) //Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//(13:8,NA,12) //Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//(21:16,NA,-2) //Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//(29:24,NA,-20) //Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_O26_VSD_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952154 RW 0x0000_0003
	UINT32 reg_fd_flat_input_sel            :2;	//(1:0,NA,3) //Input selection for flat region LUT	0: a_map	1: t_map	2: max(a_map,t_map)	3: min(255,a_map+t_map) (default)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//(4:4,NA,0) //Add a flat gain to A-map enable
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//(8:8,NA,0) //Add a flat gain to T-map enable
	UINT32 resvd2                           :23;
	};
}PE_O26_VSD_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952158 RW 0x2800_0A82
	UINT32 reg_fd_flat_lut_y0               :8;	//(7:0,NA,130) //Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//(15:8,NA,10) //Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//(23:16,NA,0) //Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//(31:24,NA,40) //Flat region LUT, x1
	};
}PE_O26_VSD_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952160 RW 0x0000_0001
	UINT32 reg_mp_shp_en                    :1;	//(0:0,NA,1) //MP enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952164 RW 0x1820_2020
	UINT32 reg_mp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//(31:24,NA,24) //im gain v
	};
}PE_O26_VSD_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952168 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_VSD_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95216C RW 0x3000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//(7:4,NA,0) //Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//(11:8,NA,3) //Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//(15:12,NA,0) //Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_VSD_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952170 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_VSD_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952174 RW 0x0002_0100
	UINT32 reg_mp_gb_en                     :1;	//(0:0,NA,0) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952178 RW 0x00FF_2008
	UINT32 reg_mp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//(15:8,NA,32) //Gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//(23:16,NA,255) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_VSD_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95217C RW 0xD8D0_6040
	UINT32 reg_mp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_VSD_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952180 RW 0x40FF_FFFF
	UINT32 reg_mp_lum1_y0                   :8;	//(7:0,NA,255) //Level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//(15:8,NA,255) //Level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_VSD_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952184 RW 0xFFD8_D060
	UINT32 reg_mp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//(31:24,NA,255) //Level-balancing, lum2_y0
	};
}PE_O26_VSD_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952188 RW 0x0000_FFFF
	UINT32 reg_mp_lum2_y1                   :8;	//(7:0,NA,255) //Level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95218C RW 0x0000_0037
	UINT32 reg_mp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952190 RW 0x2020_1018
	UINT32 reg_mp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//(22:16,NA,32) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//(30:24,NA,32) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952194 RW 0x0000_F001
	UINT32 reg_apl_iir_en                   :1;	//(0:0,NA,1) //APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//(15:8,NA,240) //APL gain
	UINT32 resvd1                           :16;
	};
}PE_O26_VSD_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521A0 RW 0xFFFF_4011
	UINT32 reg_lc_shp_en                    :1;	//(0:0,NA,1) //LC enable
	UINT32 resvd                            :7;
	UINT32 reg_lc_center_target             :8;	//(15:8,NA,64) //Center target
	UINT32 reg_lc_center_gain               :8;	//(23:16,NA,255) //Center gain
	UINT32 reg_lc_local_gain                :8;	//(31:24,NA,255) //Local gain
	};
}PE_O26_VSD_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521A4 RW 0x2020_4030
	UINT32 reg_lc_gb_y2                     :8;	//(7:0,NA,48) //Gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//(15:8,NA,64) //Gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//(23:16,NA,32) //Gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//(31:24,NA,32) //Gain balancing, x1
	};
}PE_O26_VSD_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521A8 RW 0xFF30_4000
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//(23:16,NA,48) //Gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//(31:24,NA,255) //Gain balancing, x3
	};
}PE_O26_VSD_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521AC RW 0x0000_0037
	UINT32 reg_lc_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521B0 RW 0x0808_0101
	UINT32 reg_lc_coring_gain_e_b           :7;	//(6:0,NA,1) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//(14:8,NA,1) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521C0 RW 0x1E04_0100
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//(13:8,NA,1) //reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//(21:16,NA,4) //reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//(30:24,NA,30) //reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//(31:31,NA,0) //reg_th_manual_en
	};
}PE_O26_VSD_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521C4 RW 0x8500_0000
	UINT32 reg_derh_bflt_tap_size           :3;	//(2:0,NA,0) //Bilateral filter tap size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//(24:24,NA,1) //reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//(27:26,NA,1) //Edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//(31:31,NA,1) //Edge filter en
	};
}PE_O26_VSD_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521C8 RW 0x0004_0400
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//(13:8,NA,4) //Edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//(21:16,NA,4) //Edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_O26_VSD_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521CC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521D8 RW 0x4020_1010
	UINT32 reg_der_a_lut_y0                 :8;	//(7:0,NA,16) //A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//(15:8,NA,16) //A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//(23:16,NA,32) //A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//(31:24,NA,64) //A-map for der LUT, x1
	};
}PE_O26_VSD_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521DC RW 0x8080_5060
	UINT32 reg_der_a_lut_y2                 :8;	//(7:0,NA,96) //A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//(15:8,NA,80) //A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//(23:16,NA,128) //A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//(31:24,NA,128) //A-map for de-rining LUT, x3
	};
}PE_O26_VSD_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521E0 RW 0x0000_0001
	UINT32 reg_sp_shp_en                    :1;	//(0:0,NA,1) //SP enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521E4 RW 0x0020_2020
	UINT32 reg_sp_im_os_gain                :7;	//(6:0,NA,32) //im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//(14:8,NA,32) //im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//(23:16,NA,32) //im gain h
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521E8 RW 0x0000_4000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//(15:8,NA,64) //Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_O26_VSD_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521EC RW 0x3000_0000
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//(23:20,NA,0) //Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//(27:24,NA,0) //Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//(31:28,NA,3) //Laplacian gain h 3
	};
}PE_O26_VSD_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521F0 RW 0x0000_0000
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//(11:8,NA,0) //Display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_O26_VSD_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521F4 RW 0x0002_0101
	UINT32 reg_sp_gb_en                     :1;	//(0:0,NA,1) //Gain balancing	0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//(4:4,NA,0) //Delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//(15:8,NA,1) //Gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//(23:16,NA,2) //Gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521F8 RW 0x0080_1008
	UINT32 reg_sp_gb_x2                     :8;	//(7:0,NA,8) //Gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//(15:8,NA,16) //Gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//(23:16,NA,128) //Gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_O26_VSD_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9521FC RW 0xD8D0_6040
	UINT32 reg_sp_lum1_x_l0                 :8;	//(7:0,NA,64) //Level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//(15:8,NA,96) //Level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//(23:16,NA,208) //Level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//(31:24,NA,216) //Level-balancing, lum1_x_H1
	};
}PE_O26_VSD_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952200 RW 0x40FF_C480
	UINT32 reg_sp_lum1_y0                   :8;	//(7:0,NA,128) //Level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//(15:8,NA,196) //Level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//(23:16,NA,255) //Level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//(31:24,NA,64) //Level-balancing, lum2_x_L0
	};
}PE_O26_VSD_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952204 RW 0x80D8_D060
	UINT32 reg_sp_lum2_x_l1                 :8;	//(7:0,NA,96) //Level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//(15:8,NA,208) //Level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//(23:16,NA,216) //Level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//(31:24,NA,128) //Level-balancing, lum2_y0
	};
}PE_O26_VSD_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952208 RW 0x0000_FFC4
	UINT32 reg_sp_lum2_y1                   :8;	//(7:0,NA,196) //Level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//(15:8,NA,255) //Level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95220C RW 0x0000_0037
	UINT32 reg_sp_coring_en                 :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952210 RW 0x0808_1018
	UINT32 reg_sp_coring_gain_e_b           :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//(22:16,NA,8) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//(30:24,NA,8) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952220 RW 0x0000_8028
	UINT32 reg_ptiv_enable                  :1;	//(0:0,NA,0) //PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//(3:2,NA,2) //Min-max tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//(5:4,NA,2) //Average tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//(15:8,NA,128) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_VSD_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952224 RW 0x0000_FF00
	UINT32 reg_ptih_enable                  :1;	//(0:0,NA,0) //PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//(3:2,NA,0) //Min-max tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//(5:4,NA,0) //Average tap size
	UINT32 reg_ptih_ti_mode                 :1;	//(6:6,NA,0) //TI mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//(15:8,NA,255) //Master gain
	UINT32 resvd2                           :16;
	};
}PE_O26_VSD_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952228 RW 0x0000_0037
	UINT32 reg_pti_coring_en                :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95222C RW 0x0000_1018
	UINT32 reg_pti_coring_gain_e_b          :7;	//(6:0,NA,24) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//(14:8,NA,16) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//(22:16,NA,0) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//(30:24,NA,0) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952230 RW 0x1010_2014
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
}PE_O26_VSD_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952240 RW 0x8000_0011
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
}PE_O26_VSD_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952244 RW 0x0640_0810
	UINT32 reg_tgen_delta_h_bound           :5;	//(4:0,NA,16) //R clipping bound for delta
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//(12:8,NA,8) //L clipping bound for delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//(22:16,NA,64) //Max threshold for delta
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//(26:24,NA,6) //Scale factor for delta
	UINT32 resvd3                           :5;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952248 RW 0x003F_0580
	UINT32 reg_tgen_rnd_th                  :8;	//(7:0,NA,128) //Rand val threshold
	UINT32 reg_tgen_delta_wcurr             :4;	//(11:8,NA,5) //Weight for curr for delta
	UINT32 resvd                            :20;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95224C RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c0        :32;	//(31:0,NA,18603) //Initial seed value for manual seed mode
	};
}PE_O26_VSD_SHP_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952250 RW 0x0000_48AB
	UINT32 reg_tgen_rand_init_val_c1        :32;	//(31:0,NA,18603) //Initial seed value for manual seed mode
	};
}PE_O26_VSD_SHP_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952254 RW 0x0202_1F04
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_mm_offset               :5;	//(20:16,NA,2) //Min-max offset
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//(25:24,NA,2) //Min-max selection mode
	UINT32 resvd2                           :6;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952258 RW 0x0008_0050
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//(20:16,NA,8) //Rand scale factor for noise delta
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//(28:24,NA,0) //Min-max scale factor for noise delta
	UINT32 resvd2                           :3;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95225C RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_x2            :6;	//(5:0,NA,0) //Noise blur coefficient, x2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//(13:8,NA,8) //Noise blur coefficient, x1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//(29:24,NA,26) //Noise blur coefficient, x0
	UINT32 resvd2                           :2;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952260 RW 0x1A00_0800
	UINT32 reg_tgen_blur_coef_y2            :6;	//(5:0,NA,0) //Noise blur coefficient, y2
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//(13:8,NA,8) //Noise blur coefficient, y1
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//(29:24,NA,26) //Noise blur coefficient, y0
	UINT32 resvd2                           :2;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952264 RW 0x3F80_1F1F
	UINT32 resvd0                           :24;
	UINT32 reg_tgen_gs_noise                :6;	//(29:24,NA,63) //Noise gain
	UINT32 resvd1                           :2;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952268 RW 0x48AB_CDFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95226C RW 0x0000_0037
	UINT32 reg_tgen_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952270 RW 0x1010_0000
	UINT32 reg_tgen_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952274 RW 0x0003_0411
	UINT32 reg_snr_blur_en                  :1;	//(0:0,NA,1) //SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//(5:4,NA,1) //Filter tap	0: 3x3	1: 5x5	2: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//(15:8,NA,4) //Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//(18:16,NA,3) //SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_O26_VSD_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952280 RW 0x0000_0001
	UINT32 reg_dctp_en                      :1;	//(0:0,NA,1) //DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952284 RW 0x0FED_0F99
	UINT32 reg_dctp_filt0_coef_0            :12;	//(11:0,NA,-103) //DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//(27:16,NA,-19) //DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952288 RW 0x025B_0046
	UINT32 reg_dctp_filt0_coef_2            :12;	//(11:0,NA,70) //DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//(27:16,NA,603) //DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95228C RW 0x002B_0FF1
	UINT32 reg_dctp_filt0_coef_4            :12;	//(11:0,NA,-15) //DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//(27:16,NA,43) //DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952290 RW 0x0FDC_0FE1
	UINT32 reg_dctp_filt0_coef_6            :12;	//(11:0,NA,-31) //DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//(27:16,NA,-36) //DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952294 RW 0x0F68_0050
	UINT32 reg_dctp_filt1_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952298 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt1_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95229C RW 0x0FB1_0F17
	UINT32 reg_dctp_filt1_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522A0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt1_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522A4 RW 0x0F63_0059
	UINT32 reg_dctp_filt2_coef_0            :12;	//(11:0,NA,89) //DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//(27:16,NA,-157) //DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522A8 RW 0x04FE_0E92
	UINT32 reg_dctp_filt2_coef_2            :12;	//(11:0,NA,-366) //DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//(27:16,NA,1278) //DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522AC RW 0x0FAE_0F08
	UINT32 reg_dctp_filt2_coef_4            :12;	//(11:0,NA,-248) //DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//(27:16,NA,-82) //DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522B0 RW 0x0FFA_0004
	UINT32 reg_dctp_filt2_coef_6            :12;	//(11:0,NA,4) //DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522B4 RW 0x0F58_0063
	UINT32 reg_dctp_filt3_coef_0            :12;	//(11:0,NA,99) //DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//(27:16,NA,-168) //DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522B8 RW 0x0516_0E86
	UINT32 reg_dctp_filt3_coef_2            :12;	//(11:0,NA,-378) //DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//(27:16,NA,1302) //DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522BC RW 0x0FA9_0F00
	UINT32 reg_dctp_filt3_coef_4            :12;	//(11:0,NA,-256) //DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//(27:16,NA,-87) //DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522C0 RW 0x0FFA_0007
	UINT32 reg_dctp_filt3_coef_6            :12;	//(11:0,NA,7) //DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//(27:16,NA,-6) //DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522C4 RW 0x0F68_0050
	UINT32 reg_dctp_filt4_coef_0            :12;	//(11:0,NA,80) //DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//(27:16,NA,-152) //DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522C8 RW 0x04DD_0EA8
	UINT32 reg_dctp_filt4_coef_2            :12;	//(11:0,NA,-344) //DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//(27:16,NA,1245) //DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522CC RW 0x0FB1_0F17
	UINT32 reg_dctp_filt4_coef_4            :12;	//(11:0,NA,-233) //DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//(27:16,NA,-79) //DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522D0 RW 0x0FF8_0002
	UINT32 reg_dctp_filt4_coef_6            :12;	//(11:0,NA,2) //DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//(27:16,NA,-8) //DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522D4 RW 0x0FB5_0005
	UINT32 reg_dctp_filt5_coef_0            :12;	//(11:0,NA,5) //DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//(27:16,NA,-75) //DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522D8 RW 0x0394_0F62
	UINT32 reg_dctp_filt5_coef_2            :12;	//(11:0,NA,-158) //DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//(27:16,NA,916) //DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522DC RW 0x0FD7_0F93
	UINT32 reg_dctp_filt5_coef_4            :12;	//(11:0,NA,-109) //DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//(27:16,NA,-41) //DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522E0 RW 0x0FF3_0FF4
	UINT32 reg_dctp_filt5_coef_6            :12;	//(11:0,NA,-12) //DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//(27:16,NA,-13) //DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522E4 RW 0x8040_2000
	UINT32 reg_dctp_text_lut_x0             :8;	//(7:0,NA,0) //DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//(15:8,NA,32) //DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//(23:16,NA,64) //DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//(31:24,NA,128) //DCT peaking texture LUT point, x3
	};
}PE_O26_VSD_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522E8 RW 0x0000_FFC4
	UINT32 reg_dctp_text_lut_x4             :8;	//(7:0,NA,196) //DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//(15:8,NA,255) //DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522EC RW 0x4040_2080
	UINT32 reg_dctp_edge_lut_y0             :8;	//(7:0,NA,128) //DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//(15:8,NA,32) //DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//(23:16,NA,64) //DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//(31:24,NA,64) //DCT peaking edge LUT point, x1
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522F0 RW 0xC000_8020
	UINT32 reg_dctp_edge_lut_y2             :8;	//(7:0,NA,32) //DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//(15:8,NA,128) //DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//(23:16,NA,0) //DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//(31:24,NA,192) //DCT peaking edge LUT point, x3
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522F4 RW 0x0000_0080
	UINT32 reg_dctp_gain                    :8;	//(7:0,NA,128) //DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522F8 RW 0x0000_0037
	UINT32 reg_dctp_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9522FC RW 0x1010_0000
	UINT32 reg_dctp_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952300 RW 0x0000_0001
	UINT32 reg_nntg_en                      :1;	//(0:0,NA,1) //4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//(5:4,NA,0) //4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952304 RW 0x0000_159C
	UINT32 reg_nntg_lsfr_init_1st_c0        :32;	//(31:0,NA,5532) //4K nano-noise LSFR init (1st)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952308 RW 0x2CA3_7199
	UINT32 reg_nntg_lsfr_init_2nd_c0        :32;	//(31:0,NA,748908953) //4K nano-noise LSFR init (2nd)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95230C RW 0x3236_3B62
	UINT32 reg_nntg_lsfr_init_3rd_c0        :32;	//(31:0,NA,842414946) //4K nano-noise LSFR init (3rd)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952310 RW 0xFD1C_D00A
	UINT32 reg_nntg_lsfr_init_4th_c0        :32;	//(31:0,NA,4246523914) //4K nano-noise LSFR init (4th)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952314 RW 0x8C3C_2327
	UINT32 reg_nntg_lsfr_init_5th_c0        :32;	//(31:0,NA,2352751399) //4K nano-noise LSFR init (5th)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952318 RW 0xF275_9828
	UINT32 reg_nntg_lsfr_init_1st_c1        :32;	//(31:0,NA,4067792936) //4K nano-noise LSFR init (1st)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95231C RW 0xFEEA_5094
	UINT32 reg_nntg_lsfr_init_2nd_c1        :32;	//(31:0,NA,4276768916) //4K nano-noise LSFR init (2nd)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952320 RW 0xECBE_ACAA
	UINT32 reg_nntg_lsfr_init_3rd_c1        :32;	//(31:0,NA,3971919018) //4K nano-noise LSFR init (3rd)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952324 RW 0xD9C5_DFEA
	UINT32 reg_nntg_lsfr_init_4th_c1        :32;	//(31:0,NA,3653623786) //4K nano-noise LSFR init (4th)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952328 RW 0x23E8_D99E
	UINT32 reg_nntg_lsfr_init_5th_c1        :32;	//(31:0,NA,602462622) //4K nano-noise LSFR init (5th)
	};
}PE_O26_VSD_SHP_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95232C RW 0x00FF_308C
	UINT32 reg_nntg_rand_ratio              :8;	//(7:0,NA,140) //4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//(14:8,NA,48) //4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//(23:16,NA,255) //4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952330 RW 0x0E12_0145
	UINT32 reg_nntg_rand_coef_g00           :4;	//(3:0,NA,5) //4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//(7:4,NA,4) //4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//(11:8,NA,1) //4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//(19:16,NA,2) //4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//(23:20,NA,1) //4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//(27:24,NA,-2) //4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952334 RW 0x01E0_0FEE
	UINT32 reg_nntg_rand_coef_g20           :4;	//(3:0,NA,-2) //4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//(7:4,NA,-2) //4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//(11:8,NA,-1) //4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//(19:16,NA,0) //4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//(23:20,NA,-2) //4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//(27:24,NA,1) //4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952338 RW 0x0E11_011E
	UINT32 reg_nntg_nano_coef_g10           :4;	//(3:0,NA,-2) //4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//(7:4,NA,1) //4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//(11:8,NA,1) //4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//(19:16,NA,1) //4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//(23:20,NA,1) //4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//(27:24,NA,-2) //4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95233C RW 0x0220_0000
	UINT32 reg_nntg_diff_lut_y0             :8;	//(7:0,NA,0) //4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//(15:8,NA,0) //4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//(23:16,NA,32) //4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//(31:24,NA,2) //4K nano-noise diff LUT point, x1
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952340 RW 0x0880_0460
	UINT32 reg_nntg_diff_lut_y2             :8;	//(7:0,NA,96) //4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//(15:8,NA,4) //4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//(23:16,NA,128) //4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//(31:24,NA,8) //4K nano-noise diff LUT point, x3
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952344 RW 0x4090_20FF
	UINT32 reg_nntg_edge_lut_y0             :8;	//(7:0,NA,255) //4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//(15:8,NA,32) //4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//(23:16,NA,144) //4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//(31:24,NA,64) //4K nano-noise edge LUT point, x1
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952348 RW 0xA400_8040
	UINT32 reg_nntg_edge_lut_y2             :8;	//(7:0,NA,64) //4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//(15:8,NA,128) //4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//(23:16,NA,0) //4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//(31:24,NA,164) //4K nano-noise edge LUT point, x3
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95234C RW 0xFF10_088C
	UINT32 reg_nntg_random_gain             :8;	//(7:0,NA,140) //4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//(15:8,NA,8) //4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//(23:16,NA,16) //4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//(31:24,NA,255) //4K nano-noise denoise gain
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952350 RW 0x0000_0037
	UINT32 reg_nntg_coring_en               :1;	//(0:0,NA,1) //Coring on/off	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//(2:1,NA,3) //Coring mode	0: disable edge/texture peaking	1: enable edge peaking only	2: enable texture peaking only	3: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//(5:4,NA,3) //Coring input selection	0: weight_a, weight_t	1: a_map, weight_t	2: weight_a, t_map	3: a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952354 RW 0x1010_0000
	UINT32 reg_nntg_coring_gain_e_b         :7;	//(6:0,NA,0) //Edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//(14:8,NA,0) //Edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//(22:16,NA,16) //Texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//(30:24,NA,16) //Texture white gain
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952360 RW 0x0000_0280
	UINT32 reg_dp_sum_gain                  :8;	//(7:0,NA,128) //DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//(9:8,NA,2) //DP sum LUT mode	0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952364 RW 0x2828_0000
	UINT32 reg_dp_sum_lut_y0                :8;	//(7:0,NA,0) //DP sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//(15:8,NA,0) //DP sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//(23:16,NA,40) //DP sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//(31:24,NA,40) //DP sum LUT for delta control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952368 RW 0xFFFF_5050
	UINT32 reg_dp_sum_lut_y2                :8;	//(7:0,NA,80) //DP sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//(15:8,NA,80) //DP sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//(23:16,NA,255) //DP sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//(31:24,NA,255) //DP sum LUT for delta control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95236C RW 0x4080_0070
	UINT32 reg_obj_dct_delta_lut_y0         :8;	//(7:0,NA,112) //Object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0         :8;	//(15:8,NA,0) //Object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1         :8;	//(23:16,NA,128) //Object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1         :8;	//(31:24,NA,64) //Object dct LUT for delta control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952370 RW 0xFFA0_6090
	UINT32 reg_obj_dct_delta_lut_y2         :8;	//(7:0,NA,144) //Object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2         :8;	//(15:8,NA,96) //Object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3         :8;	//(23:16,NA,160) //Object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3         :8;	//(31:24,NA,255) //Object dct LUT for delta control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952374 RW 0x4080_0070
	UINT32 reg_obj_tgen_delta_lut_y0        :8;	//(7:0,NA,112) //Object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0        :8;	//(15:8,NA,0) //Object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1        :8;	//(23:16,NA,128) //Object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1        :8;	//(31:24,NA,64) //Object tgen LUT for delta control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952378 RW 0xFFB0_6090
	UINT32 reg_obj_tgen_delta_lut_y2        :8;	//(7:0,NA,144) //Object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2        :8;	//(15:8,NA,96) //Object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3        :8;	//(23:16,NA,176) //Object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3        :8;	//(31:24,NA,255) //Object tgen LUT for delta control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95237C RW 0x4080_0070
	UINT32 reg_obj_lc_delta_lut_y0          :8;	//(7:0,NA,112) //Object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0          :8;	//(15:8,NA,0) //Object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1          :8;	//(23:16,NA,128) //Object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1          :8;	//(31:24,NA,64) //Object local contrast LUT for delta control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952380 RW 0xFFA0_6090
	UINT32 reg_obj_lc_delta_lut_y2          :8;	//(7:0,NA,144) //Object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2          :8;	//(15:8,NA,96) //Object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3          :8;	//(23:16,NA,160) //Object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3          :8;	//(31:24,NA,255) //Object local contrast LUT for delta control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952384 RW 0x2828_0000
	UINT32 reg_dp_sum_cg_lut_y0             :8;	//(7:0,NA,0) //DP sum LUT for delta_cg control, y0
	UINT32 reg_dp_sum_cg_lut_x0             :8;	//(15:8,NA,0) //DP sum LUT for delta_cg control, x0
	UINT32 reg_dp_sum_cg_lut_y1             :8;	//(23:16,NA,40) //DP sum LUT for delta_cg control, y1
	UINT32 reg_dp_sum_cg_lut_x1             :8;	//(31:24,NA,40) //DP sum LUT for delta_cg control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952388 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_lut_y2             :8;	//(7:0,NA,80) //DP sum LUT for delta_cg control, y2
	UINT32 reg_dp_sum_cg_lut_x2             :8;	//(15:8,NA,80) //DP sum LUT for delta_cg control, x2
	UINT32 reg_dp_sum_cg_lut_y3             :8;	//(23:16,NA,255) //DP sum LUT for delta_cg control, y3
	UINT32 reg_dp_sum_cg_lut_x3             :8;	//(31:24,NA,255) //DP sum LUT for delta_cg control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952390 RW 0x0000_0001
	UINT32 reg_psp_obj_en                   :1;	//(0:0,NA,1) //PSP object contrast enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952394 RW 0x2828_0000
	UINT32 reg_dp_sum_obj_lut_y0            :8;	//(7:0,NA,0) //DP sum LUT for object control, y0
	UINT32 reg_dp_sum_obj_lut_x0            :8;	//(15:8,NA,0) //DP sum LUT for object control, x0
	UINT32 reg_dp_sum_obj_lut_y1            :8;	//(23:16,NA,40) //DP sum LUT for object control, y1
	UINT32 reg_dp_sum_obj_lut_x1            :8;	//(31:24,NA,40) //DP sum LUT for object control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952398 RW 0xFFFF_5050
	UINT32 reg_dp_sum_obj_lut_y2            :8;	//(7:0,NA,80) //DP sum LUT for object control, y2
	UINT32 reg_dp_sum_obj_lut_x2            :8;	//(15:8,NA,80) //DP sum LUT for object control, x2
	UINT32 reg_dp_sum_obj_lut_y3            :8;	//(23:16,NA,255) //DP sum LUT for object control, y3
	UINT32 reg_dp_sum_obj_lut_x3            :8;	//(31:24,NA,255) //DP sum LUT for object control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523A0 RW 0x0000_0000
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
}PE_O26_VSD_SHP_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523A4 RW 0x0000_0000
	UINT32 reg_win_dp_win_w0_x0             :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_win_dp_win_w0_y0             :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523A8 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w0_x1             :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_win_dp_win_w0_y1             :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523AC RW 0x0000_0000
	UINT32 reg_win_dp_win_w1_x0             :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_win_dp_win_w1_y0             :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523B0 RW 0x086F_0EFF
	UINT32 reg_win_dp_win_w1_x1             :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_win_dp_win_w1_y1             :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523C0 RW 0x0432_0C40
	UINT32 reg_region_text_en               :1;	//(0:0,NA,0) //Region texture enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523C4 RW 0x0F50_0410
	UINT32 reg_region_text_lut_y0           :8;	//(7:0,NA,16) //Region texture LUT, y0
	UINT32 reg_region_text_lut_x0           :8;	//(15:8,NA,4) //Region texture LUT, x0
	UINT32 reg_region_text_lut_y1           :8;	//(23:16,NA,80) //Region texture LUT, y1
	UINT32 reg_region_text_lut_x1           :8;	//(31:24,NA,15) //Region texture LUT, x1
	};
}PE_O26_VSD_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523C8 RW 0x46C8_2380
	UINT32 reg_region_text_lut_y2           :8;	//(7:0,NA,128) //Region texture LUT, y2
	UINT32 reg_region_text_lut_x2           :8;	//(15:8,NA,35) //Region texture LUT, x2
	UINT32 reg_region_text_lut_y3           :8;	//(23:16,NA,200) //Region texture LUT, y3
	UINT32 reg_region_text_lut_x3           :8;	//(31:24,NA,70) //Region texture LUT, x3
	};
}PE_O26_VSD_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523CC RW 0x0000_FF00
	UINT32 reg_tmap_temp_iir_en             :1;	//(0:0,NA,0) //Tmap temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//(4:4,NA,0) //Tmap temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//(15:8,NA,255) //Tmap temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//(24:24,NA,0) //Tmap temporal process status selection	0: original tmap status	1: iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523D0 RW 0x2840_0A00
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//(7:0,NA,0) //Tmap temporal previous blend LUT, y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//(15:8,NA,10) //Tmap temporal previous blend LUT, x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//(23:16,NA,64) //Tmap temporal previous blend LUT, y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//(31:24,NA,40) //Tmap temporal previous blend LUT, x1
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523D4 RW 0x5080_3C60
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//(7:0,NA,96) //Tmap temporal previous blend LUT, y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//(15:8,NA,60) //Tmap temporal previous blend LUT, x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//(23:16,NA,128) //Tmap temporal previous blend LUT, y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//(31:24,NA,80) //Tmap temporal previous blend LUT, x3
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523D8 RW 0x08D0_00C0
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//(7:0,NA,192) //Tmap temporal iir positive LUT, y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//(15:8,NA,0) //Tmap temporal iir positive LUT, x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//(23:16,NA,208) //Tmap temporal iir positive LUT, y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//(31:24,NA,8) //Tmap temporal iir positive LUT, x1
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523DC RW 0x30F0_10E0
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//(7:0,NA,224) //Tmap temporal iir positive LUT, y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//(15:8,NA,16) //Tmap temporal iir positive LUT, x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//(23:16,NA,240) //Tmap temporal iir positive LUT, y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//(31:24,NA,48) //Tmap temporal iir positive LUT, x3
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523E0 RW 0x80C0_60D0
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//(7:0,NA,208) //Tmap temporal iir positive LUT, y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//(15:8,NA,96) //Tmap temporal iir positive LUT, x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//(23:16,NA,192) //Tmap temporal iir positive LUT, y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//(31:24,NA,128) //Tmap temporal iir positive LUT, x5
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523E4 RW 0x0870_0080
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//(7:0,NA,128) //Tmap temporal iir negative LUT, y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//(15:8,NA,0) //Tmap temporal iir negative LUT, x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//(23:16,NA,112) //Tmap temporal iir negative LUT, y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//(31:24,NA,8) //Tmap temporal iir negative LUT, x1
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523E8 RW 0x1850_1060
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//(7:0,NA,96) //Tmap temporal iir negative LUT, y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//(15:8,NA,16) //Tmap temporal iir negative LUT, x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//(23:16,NA,80) //Tmap temporal iir negative LUT, y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//(31:24,NA,24) //Tmap temporal iir negative LUT, x3
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523EC RW 0x4000_2040
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//(7:0,NA,64) //Tmap temporal iir negative LUT, y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//(15:8,NA,32) //Tmap temporal iir negative LUT, x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//(23:16,NA,0) //Tmap temporal iir negative LUT, y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//(31:24,NA,64) //Tmap temporal iir negative LUT, x5
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523F0 RW 0x0000_0000
	UINT32 reg_tmap_stat_win0_start_x       :16;	//(15:0,NA,0) //Tmap temporal texture status window position (window0)
	UINT32 reg_tmap_stat_win0_start_y       :16;	//(31:16,NA,0) //Tmap temporal texture status window position (window0)
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523F4 RW 0x086F_077F
	UINT32 reg_tmap_stat_win0_end_x         :16;	//(15:0,NA,1919) //Tmap temporal texture status window position (window0)
	UINT32 reg_tmap_stat_win0_end_y         :16;	//(31:16,NA,2159) //Tmap temporal texture status window position (window0)
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523F8 RW 0x0000_0780
	UINT32 reg_tmap_stat_win1_start_x       :16;	//(15:0,NA,1920) //Tmap temporal texture status window position (window1)
	UINT32 reg_tmap_stat_win1_start_y       :16;	//(31:16,NA,0) //Tmap temporal texture status window position (window1)
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9523FC RW 0x0438_0EFF
	UINT32 reg_tmap_stat_win1_end_x         :16;	//(15:0,NA,3839) //Tmap temporal texture status window position (window1)
	UINT32 reg_tmap_stat_win1_end_y         :16;	//(31:16,NA,1080) //Tmap temporal texture status window position (window1)
	};
}PE_O26_VSD_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952400 RW 0x8010_0179
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
}PE_O26_VSD_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952404 RW 0x0080_0000
	UINT32 reg_dj_level_th                  :8;	//(7:0,NA,0) //g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//(23:16,NA,128) //Neighborhood pixel averaging: gain
	UINT32 resvd1                           :8;
	};
}PE_O26_VSD_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952408 RW 0x0000_1010
	UINT32 reg_dj_g0_cnt_min                :5;	//(4:0,NA,16) //g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :6;	//(13:8,NA,16) //g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :18;
	};
}PE_O26_VSD_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95240C RW 0x8010_0840
	UINT32 reg_dj_g1_protect_min            :8;	//(7:0,NA,64) //g1: min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//(14:8,NA,8) //g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//(23:16,NA,16) //Edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//(31:24,NA,128) //Edge adaptive filter multiplication value
	};
}PE_O26_VSD_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952410 RW 0x0000_0000
	UINT32 reg_dj_dir_sel_c1                :1;	//(0:0,NA,0) //DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//(1:1,NA,0) //DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//(2:2,NA,0) //DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//(3:3,NA,0) //DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_O26_VSD_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952414 RW 0x0000_0000
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
}PE_O26_VSD_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952418 RW 0x0000_0040
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
}PE_O26_VSD_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95241C RW 0x0015_5550
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
}PE_O26_VSD_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952420 RW 0x0000_0040
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
}PE_O26_VSD_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952424 RW 0x002A_A040
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
}PE_O26_VSD_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952428 RW 0x002A_A040
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
}PE_O26_VSD_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95242C RW 0x000A_A040
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
}PE_O26_VSD_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952430 RW 0x0000_00E4
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
}PE_O26_VSD_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952434 RW 0x0000_5540
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
}PE_O26_VSD_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952438 RW 0x0020_5542
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
}PE_O26_VSD_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95243C RW 0x0008_1508
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
}PE_O26_VSD_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952440 RW 0x0002_0420
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
}PE_O26_VSD_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952444 RW 0x0000_8080
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
}PE_O26_VSD_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952448 RW 0x0000_2A00
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
}PE_O26_VSD_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95244C RW 0x0000_2A00
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
}PE_O26_VSD_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952450 RW 0x0000_0008
	UINT32 reg_dj_pattern1_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//(2:2,NA,0) //DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//(3:3,NA,1) //DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_VSD_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952454 RW 0x0000_2800
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
}PE_O26_VSD_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952458 RW 0x0005_0A00
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
}PE_O26_VSD_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95245C RW 0x0005_4280
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
}PE_O26_VSD_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952460 RW 0x0005_50A0
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
}PE_O26_VSD_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952464 RW 0x0005_4280
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
}PE_O26_VSD_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952468 RW 0x0005_0A00
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
}PE_O26_VSD_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95246C RW 0x0000_2800
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
}PE_O26_VSD_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952470 RW 0x0000_0004
	UINT32 reg_dj_pattern2_flip0_h          :1;	//(0:0,NA,0) //DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//(1:1,NA,0) //DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//(2:2,NA,1) //DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//(3:3,NA,0) //DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_O26_VSD_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952474 RW 0x00FF_0628
	UINT32 reg_dj_soft_g0_mul               :6;	//(5:0,NA,40) //Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//(12:8,NA,6) //Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//(23:16,NA,255) //Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952478 RW 0x00FF_0414
	UINT32 reg_dj_soft_g1_mul               :6;	//(5:0,NA,20) //Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//(12:8,NA,4) //Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//(23:16,NA,255) //Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95247C RW 0x00FF_0620
	UINT32 reg_dj_soft_g2_mul               :6;	//(5:0,NA,32) //Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//(12:8,NA,6) //Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//(23:16,NA,255) //Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952480 RW 0x0001_1400
	UINT32 reg_dj_soft_base                 :8;	//(7:0,NA,0) //Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//(15:8,NA,20) //Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//(16:16,NA,1) //Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_O26_VSD_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952490 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952494 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524A0 RW 0x0000_0000
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
}PE_O26_VSD_SHP_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524A4 RW 0x0000_0000
	UINT32 reg_win_dj_win_w0_x0             :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_win_dj_win_w0_y0             :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524A8 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w0_x1             :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_win_dj_win_w0_y1             :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524AC RW 0x0000_0000
	UINT32 reg_win_dj_win_w1_x0             :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_win_dj_win_w1_y0             :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524B0 RW 0x086F_0EFF
	UINT32 reg_win_dj_win_w1_x1             :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_win_dj_win_w1_y1             :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524BC RW 0x10BC_4DB3
	UINT32 reg_dj_text_gain_mmd_mul         :8;	//(7:0,NA,179) //DJ text gain MMD factor
	UINT32 reg_dj_text_gain_avg_mul         :8;	//(15:8,NA,77) //DJ text gain average factor
	UINT32 reg_dj_text_gain_threshold       :10;	//(25:16,NA,188) //DJ text gain threshold
	UINT32 reg_dj_text_gain_all_text_flag   :1;	//(26:26,NA,0) //DJ text gain all text flag
	UINT32 resvd0                           :1;
	UINT32 reg_dj_text_gain_en              :1;	//(28:28,NA,1) //DJ text gain enable
	UINT32 resvd1                           :3;
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524C0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir0_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir0), y0
	UINT32 reg_dj_text_gain_dir0_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir0), x0
	UINT32 reg_dj_text_gain_dir0_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir0), y1
	UINT32 reg_dj_text_gain_dir0_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir0), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524C4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir0_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir0), y2
	UINT32 reg_dj_text_gain_dir0_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir0), x2
	UINT32 reg_dj_text_gain_dir0_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir0), y3
	UINT32 reg_dj_text_gain_dir0_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir0), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524C8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir1_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir1), y0
	UINT32 reg_dj_text_gain_dir1_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir1), x0
	UINT32 reg_dj_text_gain_dir1_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir1), y1
	UINT32 reg_dj_text_gain_dir1_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir1), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524CC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir1_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir1), y2
	UINT32 reg_dj_text_gain_dir1_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir1), x2
	UINT32 reg_dj_text_gain_dir1_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir1), y3
	UINT32 reg_dj_text_gain_dir1_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir1), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524D0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir3_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir3), y0
	UINT32 reg_dj_text_gain_dir3_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir3), x0
	UINT32 reg_dj_text_gain_dir3_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir3), y1
	UINT32 reg_dj_text_gain_dir3_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir3), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524D4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir3_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir3), y2
	UINT32 reg_dj_text_gain_dir3_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir3), x2
	UINT32 reg_dj_text_gain_dir3_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir3), y3
	UINT32 reg_dj_text_gain_dir3_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir3), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524D8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir5_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir5), y0
	UINT32 reg_dj_text_gain_dir5_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir5), x0
	UINT32 reg_dj_text_gain_dir5_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir5), y1
	UINT32 reg_dj_text_gain_dir5_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir5), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524DC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir5_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir5), y2
	UINT32 reg_dj_text_gain_dir5_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir5), x2
	UINT32 reg_dj_text_gain_dir5_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir5), y3
	UINT32 reg_dj_text_gain_dir5_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir5), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524E0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir6_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir6), y0
	UINT32 reg_dj_text_gain_dir6_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir6), x0
	UINT32 reg_dj_text_gain_dir6_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir6), y1
	UINT32 reg_dj_text_gain_dir6_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir6), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524E4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir6_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir6), y2
	UINT32 reg_dj_text_gain_dir6_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir6), x2
	UINT32 reg_dj_text_gain_dir6_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir6), y3
	UINT32 reg_dj_text_gain_dir6_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir6), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524E8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir7_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir7), y0
	UINT32 reg_dj_text_gain_dir7_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir7), x0
	UINT32 reg_dj_text_gain_dir7_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir7), y1
	UINT32 reg_dj_text_gain_dir7_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir7), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524EC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir7_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir7), y2
	UINT32 reg_dj_text_gain_dir7_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir7), x2
	UINT32 reg_dj_text_gain_dir7_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir7), y3
	UINT32 reg_dj_text_gain_dir7_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir7), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524F0 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir9_y0         :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir9), y0
	UINT32 reg_dj_text_gain_dir9_x0         :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir9), x0
	UINT32 reg_dj_text_gain_dir9_y1         :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir9), y1
	UINT32 reg_dj_text_gain_dir9_x1         :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir9), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524F4 RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir9_y2         :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir9), y2
	UINT32 reg_dj_text_gain_dir9_x2         :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir9), x2
	UINT32 reg_dj_text_gain_dir9_y3         :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir9), y3
	UINT32 reg_dj_text_gain_dir9_x3         :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir9), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524F8 RW 0x00C0_00C0
	UINT32 reg_dj_text_gain_dir11_y0        :8;	//(7:0,NA,192) //Final DJ text gain LUT (dir11), y0
	UINT32 reg_dj_text_gain_dir11_x0        :8;	//(15:8,NA,0) //Final DJ text gain LUT (dir11), x0
	UINT32 reg_dj_text_gain_dir11_y1        :8;	//(23:16,NA,192) //Final DJ text gain LUT (dir11), y1
	UINT32 reg_dj_text_gain_dir11_x1        :8;	//(31:24,NA,0) //Final DJ text gain LUT (dir11), x1
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9524FC RW 0x8020_8020
	UINT32 reg_dj_text_gain_dir11_y2        :8;	//(7:0,NA,32) //Final DJ text gain LUT (dir11), y2
	UINT32 reg_dj_text_gain_dir11_x2        :8;	//(15:8,NA,128) //Final DJ text gain LUT (dir11), x2
	UINT32 reg_dj_text_gain_dir11_y3        :8;	//(23:16,NA,32) //Final DJ text gain LUT (dir11), y3
	UINT32 reg_dj_text_gain_dir11_x3        :8;	//(31:24,NA,128) //Final DJ text gain LUT (dir11), x3
	};
}PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952500 RW 0x0000_0000
	UINT32 reg_color_region_en              :1;	//(0:0,NA,0) //Color region processing enable
	UINT32 reg_color_region_debug_en        :1;	//(1:1,NA,0) //Color region debug map enable
	UINT32 resvd0                           :2;
	UINT32 reg_chr_protection_en            :1;	//(4:4,NA,0) //Chroma protection enable
	UINT32 resvd1                           :3;
	UINT32 reg_chr_compensation_en          :1;	//(8:8,NA,0) //Chroma compensation enable
	UINT32 resvd2                           :23;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952504 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952508 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95250C RW 0x28FF_1400
	UINT32 reg_chr_gain_r0_cb_y0            :8;	//(7:0,NA,0) //Chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0            :8;	//(15:8,NA,20) //Chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1            :8;	//(23:16,NA,255) //Chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1            :8;	//(31:24,NA,40) //Chroma gain LUT, R0, Cb, x1
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952510 RW 0x7800_64FF
	UINT32 reg_chr_gain_r0_cb_y2            :8;	//(7:0,NA,255) //Chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2            :8;	//(15:8,NA,100) //Chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3            :8;	//(23:16,NA,0) //Chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3            :8;	//(31:24,NA,120) //Chroma gain LUT, R0, Cb, x3
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952514 RW 0x96FF_8200
	UINT32 reg_chr_gain_r0_cr_y0            :8;	//(7:0,NA,0) //Chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0            :8;	//(15:8,NA,130) //Chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1            :8;	//(23:16,NA,255) //Chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1            :8;	//(31:24,NA,150) //Chroma gain LUT, R0, Cr, x1
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952518 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r0_cr_y2            :8;	//(7:0,NA,200) //Chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2            :8;	//(15:8,NA,255) //Chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3            :8;	//(23:16,NA,240) //Chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3            :8;	//(31:24,NA,0) //Chroma gain LUT, R0, Cr, x3
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95251C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952520 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952524 RW 0x96FF_8200
	UINT32 reg_chr_gain_r1_cb_y0            :8;	//(7:0,NA,0) //Chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0            :8;	//(15:8,NA,130) //Chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1            :8;	//(23:16,NA,255) //Chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1            :8;	//(31:24,NA,150) //Chroma gain LUT, R1, Cb, x1
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952528 RW 0x00F0_FFC8
	UINT32 reg_chr_gain_r1_cb_y2            :8;	//(7:0,NA,200) //Chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2            :8;	//(15:8,NA,255) //Chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3            :8;	//(23:16,NA,240) //Chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3            :8;	//(31:24,NA,0) //Chroma gain LUT, R1, Cb, x3
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95252C RW 0x28FF_1400
	UINT32 reg_chr_gain_r1_cr_y0            :8;	//(7:0,NA,0) //Chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0            :8;	//(15:8,NA,20) //Chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1            :8;	//(23:16,NA,255) //Chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1            :8;	//(31:24,NA,40) //Chroma gain LUT, R1, Cr, x1
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952530 RW 0x7800_64FF
	UINT32 reg_chr_gain_r1_cr_y2            :8;	//(7:0,NA,255) //Chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2            :8;	//(15:8,NA,100) //Chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3            :8;	//(23:16,NA,0) //Chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3            :8;	//(31:24,NA,120) //Chroma gain LUT, R1, Cr, x3
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952534 RW 0x00FF_0000
	UINT32 reg_chr_gain_r0_gain             :8;	//(7:0,NA,0) //Chroma gain alpha, R0
	UINT32 resvd0                           :8;
	UINT32 reg_chr_gain_r1_gain             :8;	//(23:16,NA,255) //Chroma gain alpha, R1
	UINT32 reg_chr_gain_sel                 :1;	//(24:24,NA,0) //0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1                           :7;
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952538 RW 0x28FF_1400
	UINT32 reg_chr_comp_y0                  :8;	//(7:0,NA,0) //Chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0                  :8;	//(15:8,NA,20) //Chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1                  :8;	//(23:16,NA,255) //Chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1                  :8;	//(31:24,NA,40) //Chroma comp. linear mapping, x1
	};
}PE_O26_VSD_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952550 RW 0x0000_2A60
	UINT32 reg_cti_en                       :1;	//(0:0,NA,0) //CTI enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_filter_tap_size          :3;	//(6:4,NA,6) //0: 21 tap	1: 19 tap	2: 17 tap	3: 15 tap	4: 13 tap	5: 11 tap	6:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_gain                     :8;	//(15:8,NA,42) //CTI gain (3.5u)
	UINT32 resvd2                           :16;
	};
}PE_O26_VSD_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952554 RW 0x0001_1810
	UINT32 reg_cti_coring_th0               :8;	//(7:0,NA,16) //Coring th0
	UINT32 reg_cti_coring_th1               :8;	//(15:8,NA,24) //Coring_th1
	UINT32 reg_cti_coring_map_filter        :3;	//(18:16,NA,1) //0: no filtering	1: 5-tap filtering	2: 7-tap filtering	3: 9-tap filtering	4: 11-tap filtering	5: 13-tap filtering
	UINT32 resvd0                           :1;
	UINT32 reg_cti_coring_tap_size          :3;	//(22:20,NA,0) //0: 21 tap	1: 19 tap	2: 17 tap	3: 15 tap	4: 13 tap	5: 11 tap	6:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_debug_mode               :2;	//(25:24,NA,0) //0: normal display	2: coring_map(cb)	3: coring_map(cr)
	UINT32 resvd2                           :6;
	};
}PE_O26_VSD_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952558 RW 0x0088_0850
	UINT32 reg_cti_ycm_en                   :1;	//(0:0,NA,0) //YC merge enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_ycm_band_sel             :3;	//(6:4,NA,5) //YC merge band sel
	UINT32 resvd1                           :1;
	UINT32 reg_cti_ycm_diff_th              :8;	//(15:8,NA,8) //YC merge diff threshold
	UINT32 reg_cti_ycm_y_gain               :4;	//(19:16,NA,8) //YC merge gain, Y
	UINT32 reg_cti_ycm_c_gain               :4;	//(23:20,NA,8) //YC merge gain, C
	UINT32 resvd2                           :8;
	};
}PE_O26_VSD_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952560 RW 0x0000_0000
	UINT32 reg_flick_en                     :1;	//(0:0,NA,0) //FRC flicker blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_flick_motion_sel             :2;	//(5:4,NA,0) //FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :2;
	UINT32 reg_flick_blur_type              :2;	//(9:8,NA,0) //FRC flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2                           :22;
	};
}PE_O26_VSD_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952564 RW 0x2040_0000
	UINT32 reg_flick_motion_lut_y0          :8;	//(7:0,NA,0) //FRC flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0          :8;	//(15:8,NA,0) //FRC flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1          :8;	//(23:16,NA,64) //FRC flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1          :8;	//(31:24,NA,32) //FRC flicker blur motion LUT point, x1
	};
}PE_O26_VSD_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952568 RW 0x80FF_4080
	UINT32 reg_flick_motion_lut_y2          :8;	//(7:0,NA,128) //FRC flicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2          :8;	//(15:8,NA,64) //FRC flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3          :8;	//(23:16,NA,255) //FRC flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3          :8;	//(31:24,NA,128) //FRC flicker blur motion LUT point, x3
	};
}PE_O26_VSD_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95256C RW 0x0000_0080
	UINT32 reg_flick_master_gain            :8;	//(7:0,NA,128) //FRC flicker blur master gain
	UINT32 resvd                            :24;
	};
}PE_O26_VSD_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952570 RW 0x0000_0000
	UINT32 reg_force_block_en               :1;	//(0:0,NA,0) //Tmap temporal forcing the number of block enable
	UINT32 resvd0                           :15;
	UINT32 reg_block_no_v                   :7;	//(22:16,NA,0) //Tmap temporal forcing the number of vertical block
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_h                   :8;	//(31:24,NA,0) //Tmap temporal forcing the number of horizontal block
	};
}PE_O26_VSD_SHP_TEMPORAL_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952574 RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,NA,0) //Tmap temporal forcing vertical block size
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,NA,0) //Tmap temporal forcing horizontal block size
	UINT32 resvd1                           :1;
	UINT32 reg_last_block_size_v            :7;	//(22:16,NA,0) //Tmap temporal forcing last vertical block size
	UINT32 resvd2                           :1;
	UINT32 reg_last_block_size_h            :7;	//(30:24,NA,0) //Tmap temporal forcing last horizontal block size
	UINT32 resvd3                           :1;
	};
}PE_O26_VSD_SHP_TEMPORAL_MAP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9525A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9525A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9525A8 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9525AC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9525B0 RW 0x086F_0EFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952600 RW 0x0000_0000
	UINT32 mif_r_motion_gain_line_inc       :2;	//(1:0,NA,0) //Manual line increment
	UINT32 mif_r_motion_gain_pf_flag_en     :1;	//(2:2,NA,0) //Pre-fetch enable
	UINT32 mif_r_motion_gain_manual_en      :1;	//(3:3,NA,0) //Manual line increment enable
	UINT32 mif_r_motion_gain_en             :1;	//(4:4,NA,0) //MIF enable
	UINT32 mif_r_motion_vreverse            :1;	//(5:5,NA,0) //V-reverse enable
	UINT32 resvd0                           :2;
	UINT32 motion_gain_l5sc_out_sel         :2;	//(9:8,NA,0) //Output selection (0: scaler out, 1: H-gradation, 2: black, 3: white)
	UINT32 resvd1                           :2;
	UINT32 shp_mgs_mode                     :1;	//(12:12,NA,0) //SHP MGS only mode (csr_mgs_mode should be 0)
	UINT32 csr_mgs_mode                     :1;	//(13:13,NA,0) //CSR MGS only mode (shp_mgs_mode should be 0)
	UINT32 resvd2                           :2;
	UINT32 mif_r_motion_gain_voffset        :9;	//(24:16,NA,0) //MRD V-offset
	UINT32 resvd3                           :5;
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0) //Clock gating disp_clk
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0) //Clock gating de_clk
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952604 RW 0x0000_0000
	UINT32 reg_motion_gain_in_hoffset       :16;	//(15:0,NA,0) //Input window offset
	UINT32 reg_motion_gain_in_voffset       :16;	//(31:16,NA,0) //Input window offset
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952608 RW 0x0011_001E
	UINT32 reg_motion_gain_in_hactive       :16;	//(15:0,NA,30) //Input window active size
	UINT32 reg_motion_gain_in_vactive       :16;	//(31:16,NA,17) //Input window active size
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95260C RW 0x0011_001E
	UINT32 reg_motion_gain_in_hsize         :16;	//(15:0,NA,30) //Input source total size
	UINT32 reg_motion_gain_in_vsize         :16;	//(31:16,NA,17) //Input source total size
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952610 RW 0x0870_0780
	UINT32 reg_motion_gain_out_pic_width    :16;	//(15:0,NA,1920) //Output width (default: 3840/2)
	UINT32 reg_motion_gain_out_pic_height   :16;	//(31:16,NA,2160) //Output height (default: 2160)
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952614 RW 0x8000_3030
	UINT32 reg_motion_gain_phase_off_h      :6;	//(5:0,NA,-16) //Vertical offset of initial pixel position (min:-31 ~ max:+31, signed value)
	UINT32 resvd0                           :2;
	UINT32 reg_motion_gain_phase_off_v      :6;	//(13:8,NA,-16) //Horizontal offset of initial pixel position (min:-31 ~ max:+31, signed value)
	UINT32 resvd1                           :17;
	UINT32 reg_motion_gain_sampling_mode    :1;	//(31:31,NA,1) //Sampling mode (0: normal-auto, 1: manual-set)
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952618 RW 0x0001_0001
	UINT32 reg_motion_gain_numerator_h      :16;	//(15:0,NA,1) //Numerator (when sampling mode = 1)
	UINT32 reg_motion_gain_numerator_v      :16;	//(31:16,NA,1) //Numerator (when sampling mode = 1)
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95261C RW 0x0080_0040
	UINT32 reg_motion_gain_denominator_h    :16;	//(15:0,NA,64) //Denominator (when sampling mode = 1) (default: (3840/2)/30)
	UINT32 reg_motion_gain_denominator_v    :16;	//(31:16,NA,128) //Denominator (when sampling mode = 1) (default: 2160/17 -> 128)
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952620 RW 0x0000_0000
	UINT32 reg_motion_gain_win0_en          :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_motion_gain_win1_en          :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_motion_gain_win01_en         :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_motion_gain_win_outside      :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_motion_gain_win_en           :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_motion_gain_bdr_alpha        :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_motion_gain_bdr_wid          :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_motion_gain_bdr_en           :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_motion_gain_cr5              :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_motion_gain_cb5              :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_motion_gain_yy6              :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952624 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x0        :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_motion_gain_win_w0_y0        :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952628 RW 0x0000_0000
	UINT32 reg_motion_gain_win_w0_x1        :16;	//(15:0,NA,0) //Window control, win_w0_x1
	UINT32 reg_motion_gain_win_w0_y1        :16;	//(31:16,NA,0) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95262C RW 0x0000_0000
	UINT32 reg_motion_gain_out_hoffset      :16;	//(15:0,NA,0) //Output window offset
	UINT32 reg_motion_gain_out_voffset      :16;	//(31:16,NA,0) //Output window offset
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952630 RW 0x0870_0780
	UINT32 reg_motion_gain_out_hactive      :16;	//(15:0,NA,1920) //Output window active size (default: 3840/2)
	UINT32 reg_motion_gain_out_vactive      :16;	//(31:16,NA,2160) //Output window active size (default: 2160)
	};
}PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952640 RW 0x0000_0000
	UINT32 reg_motion_prot_adaptive_en      :1;	//(0:0,NA,0) //Motion protection enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952644 RW 0x4040_0000
	UINT32 reg_motion_prot_lut_a_y0         :8;	//(7:0,NA,0) //Motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//(15:8,NA,0) //Motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//(23:16,NA,64) //Motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//(31:24,NA,64) //Motion gain LUT, A, x1
	};
}PE_O26_VSD_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952648 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_a_y2         :8;	//(7:0,NA,80) //Motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//(15:8,NA,110) //Motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//(23:16,NA,120) //Motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//(31:24,NA,255) //Motion gain LUT, A, x3
	};
}PE_O26_VSD_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95264C RW 0x4040_0000
	UINT32 reg_motion_prot_lut_t_y0         :8;	//(7:0,NA,0) //Motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//(15:8,NA,0) //Motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//(23:16,NA,64) //Motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//(31:24,NA,64) //Motion gain LUT, T, x1
	};
}PE_O26_VSD_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952650 RW 0xFF78_6E50
	UINT32 reg_motion_prot_lut_t_y2         :8;	//(7:0,NA,80) //Motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//(15:8,NA,110) //Motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//(23:16,NA,120) //Motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//(31:24,NA,255) //Motion gain LUT, T, x3
	};
}PE_O26_VSD_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952670 RW 0x0000_0000
	UINT32 reg_win_mot_win0_en              :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_win_mot_win1_en              :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_win_mot_win01_en             :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_win_mot_win_outside          :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_win_mot_win_en               :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_win_mot_bdr_alpha            :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_win_mot_bdr_wid              :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_win_mot_bdr_en               :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_win_mot_cr5                  :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_win_mot_cb5                  :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_win_mot_yy6                  :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_VSD_SHP_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952674 RW 0x0000_0000
	UINT32 reg_win_mot_win_w0_x0            :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_win_mot_win_w0_y0            :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952678 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w0_x1            :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_win_mot_win_w0_y1            :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95267C RW 0x0000_0000
	UINT32 reg_win_mot_win_w1_x0            :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_win_mot_win_w1_y0            :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952680 RW 0x086F_0EFF
	UINT32 reg_win_mot_win_w1_x1            :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_win_mot_win_w1_y1            :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952690 RW 0x0000_0000
	UINT32 reg_obj_shp_en                   :1;	//(0:0,NA,0) //Object sharpness (0:disable, 1:enable)
	UINT32 resvd0                           :3;
	UINT32 reg_obj_sel_bit                  :1;	//(4:4,NA,0) //Object map bit selection (0:7bit, 1:6bit)
	UINT32 resvd1                           :27;
	};
}PE_O26_VSD_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952694 RW 0x4080_005A
	UINT32 reg_obj_face_gain_lut_y0         :8;	//(7:0,NA,90) //Object face gain LUT, y2
	UINT32 reg_obj_face_gain_lut_x0         :8;	//(15:8,NA,0) //Object face gain LUT, x2
	UINT32 reg_obj_face_gain_lut_y1         :8;	//(23:16,NA,128) //Object face gain LUT, y3
	UINT32 reg_obj_face_gain_lut_x1         :8;	//(31:24,NA,64) //Object face gain LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952698 RW 0xC4FF_6090
	UINT32 reg_obj_face_gain_lut_y2         :8;	//(7:0,NA,144) //Object face gain LUT, y0
	UINT32 reg_obj_face_gain_lut_x2         :8;	//(15:8,NA,96) //Object face gain LUT, x0
	UINT32 reg_obj_face_gain_lut_y3         :8;	//(23:16,NA,255) //Object face gain LUT, y1
	UINT32 reg_obj_face_gain_lut_x3         :8;	//(31:24,NA,196) //Object face gain LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95269C RW 0x2080_005A
	UINT32 reg_obj_obj_gain_lut_y0          :8;	//(7:0,NA,90) //Object object gain LUT, y2
	UINT32 reg_obj_obj_gain_lut_x0          :8;	//(15:8,NA,0) //Object object gain LUT, x2
	UINT32 reg_obj_obj_gain_lut_y1          :8;	//(23:16,NA,128) //Object object gain LUT, y3
	UINT32 reg_obj_obj_gain_lut_x1          :8;	//(31:24,NA,32) //Object object gain LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526A0 RW 0x90B0_4090
	UINT32 reg_obj_obj_gain_lut_y2          :8;	//(7:0,NA,144) //Object object gain LUT, y0
	UINT32 reg_obj_obj_gain_lut_x2          :8;	//(15:8,NA,64) //Object object gain LUT, x0
	UINT32 reg_obj_obj_gain_lut_y3          :8;	//(23:16,NA,176) //Object object gain LUT, y1
	UINT32 reg_obj_obj_gain_lut_x3          :8;	//(31:24,NA,144) //Object object gain LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526A4 RW 0x1090_00AC
	UINT32 reg_obj_final_blend_obj_lut_y0   :8;	//(7:0,NA,172) //Object final_blend_obj LUT, y2
	UINT32 reg_obj_final_blend_obj_lut_x0   :8;	//(15:8,NA,0) //Object final_blend_obj LUT, x2
	UINT32 reg_obj_final_blend_obj_lut_y1   :8;	//(23:16,NA,144) //Object final_blend_obj LUT, y3
	UINT32 reg_obj_final_blend_obj_lut_x1   :8;	//(31:24,NA,16) //Object final_blend_obj LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526A8 RW 0x8000_2060
	UINT32 reg_obj_final_blend_obj_lut_y2   :8;	//(7:0,NA,96) //Object final_blend_obj LUT, y0
	UINT32 reg_obj_final_blend_obj_lut_x2   :8;	//(15:8,NA,32) //Object final_blend_obj LUT, x0
	UINT32 reg_obj_final_blend_obj_lut_y3   :8;	//(23:16,NA,0) //Object final_blend_obj LUT, y1
	UINT32 reg_obj_final_blend_obj_lut_x3   :8;	//(31:24,NA,128) //Object final_blend_obj LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526AC RW 0x10DC_00C4
	UINT32 reg_obj_final_blend_face_lut_y0  :8;	//(7:0,NA,196) //Object final_blend_face LUT, y2
	UINT32 reg_obj_final_blend_face_lut_x0  :8;	//(15:8,NA,0) //Object final_blend_face LUT, x2
	UINT32 reg_obj_final_blend_face_lut_y1  :8;	//(23:16,NA,220) //Object final_blend_face LUT, y3
	UINT32 reg_obj_final_blend_face_lut_x1  :8;	//(31:24,NA,16) //Object final_blend_face LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526B0 RW 0x40FF_20DC
	UINT32 reg_obj_final_blend_face_lut_y2  :8;	//(7:0,NA,220) //Object final_blend_face LUT, y0
	UINT32 reg_obj_final_blend_face_lut_x2  :8;	//(15:8,NA,32) //Object final_blend_face LUT, x0
	UINT32 reg_obj_final_blend_face_lut_y3  :8;	//(23:16,NA,255) //Object final_blend_face LUT, y1
	UINT32 reg_obj_final_blend_face_lut_x3  :8;	//(31:24,NA,64) //Object final_blend_face LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526B4 RW 0x3060_0050
	UINT32 reg_obj_master_gain_a_map_lut_y0 :8;	//(7:0,NA,80) //Object master_gain LUT, y2
	UINT32 reg_obj_master_gain_a_map_lut_x0 :8;	//(15:8,NA,0) //Object master_gain LUT, x2
	UINT32 reg_obj_master_gain_a_map_lut_y1 :8;	//(23:16,NA,96) //Object master_gain LUT, y3
	UINT32 reg_obj_master_gain_a_map_lut_x1 :8;	//(31:24,NA,48) //Object master_gain LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526B8 RW 0x9080_6080
	UINT32 reg_obj_master_gain_a_map_lut_y2 :8;	//(7:0,NA,128) //Object master_gain LUT, y0
	UINT32 reg_obj_master_gain_a_map_lut_x2 :8;	//(15:8,NA,96) //Object master_gain LUT, x0
	UINT32 reg_obj_master_gain_a_map_lut_y3 :8;	//(23:16,NA,128) //Object master_gain LUT, y1
	UINT32 reg_obj_master_gain_a_map_lut_x3 :8;	//(31:24,NA,144) //Object master_gain LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526BC RW 0x3060_0050
	UINT32 reg_obj_master_gain_t_map_lut_y0 :8;	//(7:0,NA,80) //Object master_gain LUT, y2
	UINT32 reg_obj_master_gain_t_map_lut_x0 :8;	//(15:8,NA,0) //Object master_gain LUT, x2
	UINT32 reg_obj_master_gain_t_map_lut_y1 :8;	//(23:16,NA,96) //Object master_gain LUT, y3
	UINT32 reg_obj_master_gain_t_map_lut_x1 :8;	//(31:24,NA,48) //Object master_gain LUT, x3
	};
}PE_O26_VSD_SHP_OBJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526C0 RW 0x9080_6080
	UINT32 reg_obj_master_gain_t_map_lut_y2 :8;	//(7:0,NA,128) //Object master_gain LUT, y0
	UINT32 reg_obj_master_gain_t_map_lut_x2 :8;	//(15:8,NA,96) //Object master_gain LUT, x0
	UINT32 reg_obj_master_gain_t_map_lut_y3 :8;	//(23:16,NA,128) //Object master_gain LUT, y1
	UINT32 reg_obj_master_gain_t_map_lut_x3 :8;	//(31:24,NA,144) //Object master_gain LUT, x1
	};
}PE_O26_VSD_SHP_OBJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526D0 RW 0x0000_0000
	UINT32 reg_text_gain_en                 :1;	//(0:0,NA,0) //Text gain enable
	UINT32 resvd                            :31;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526D4 RW 0x0000_0000
	UINT32 reg_text_gain_lut_y0             :8;	//(7:0,NA,0) //Text gain LUT, y0
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x0             :15;	//(30:16,NA,0) //Text gain LUT, x0
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526D8 RW 0x0BB8_0014
	UINT32 reg_text_gain_lut_y1             :8;	//(7:0,NA,20) //Text gain LUT, y1
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x1             :15;	//(30:16,NA,3000) //Text gain LUT, x1
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526DC RW 0x157C_0050
	UINT32 reg_text_gain_lut_y2             :8;	//(7:0,NA,80) //Text gain LUT, y2
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x2             :15;	//(30:16,NA,5500) //Text gain LUT, x2
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526E0 RW 0x2328_0096
	UINT32 reg_text_gain_lut_y3             :8;	//(7:0,NA,150) //Text gain LUT, y3
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x3             :15;	//(30:16,NA,9000) //Text gain LUT, x3
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526E4 RW 0x2EE0_00C8
	UINT32 reg_text_gain_lut_y4             :8;	//(7:0,NA,200) //Text gain LUT, y4
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x4             :15;	//(30:16,NA,12000) //Text gain LUT, x4
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526E8 RW 0x3A98_00E6
	UINT32 reg_text_gain_lut_y5             :8;	//(7:0,NA,230) //Text gain LUT, y5
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x5             :15;	//(30:16,NA,15000) //Text gain LUT, x5
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526EC RW 0x4E20_00FF
	UINT32 reg_text_gain_lut_y6             :8;	//(7:0,NA,255) //Text gain LUT, y6
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x6             :15;	//(30:16,NA,20000) //Text gain LUT, x6
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526F0 RW 0x6897_00FF
	UINT32 reg_text_gain_lut_y7             :8;	//(7:0,NA,255) //Text gain LUT, y7
	UINT32 resvd0                           :8;
	UINT32 reg_text_gain_lut_x7             :15;	//(30:16,NA,26775) //Text gain LUT, x7
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_SHP_FD_TEXT_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526F4 RW 0x0000_FF00
	UINT32 reg_text_temp_iir_en             :1;	//(0:0,NA,0) //Text temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_text_temp_init_en            :1;	//(4:4,NA,0) //Text temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_text_temp_init_val           :8;	//(15:8,NA,255) //Text temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_text_stat_sel                :1;	//(24:24,NA,0) //Text temporal process status selection	0: original tmap status	1: iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526F8 RW 0x2840_0A00
	UINT32 reg_text_temp_prev_lut_y0        :8;	//(7:0,NA,0) //Text temporal previous blend LUT, y0
	UINT32 reg_text_temp_prev_lut_x0        :8;	//(15:8,NA,10) //Text temporal previous blend LUT, x0
	UINT32 reg_text_temp_prev_lut_y1        :8;	//(23:16,NA,64) //Text temporal previous blend LUT, y1
	UINT32 reg_text_temp_prev_lut_x1        :8;	//(31:24,NA,40) //Text temporal previous blend LUT, x1
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9526FC RW 0x5080_3C60
	UINT32 reg_text_temp_prev_lut_y2        :8;	//(7:0,NA,96) //Text temporal previous blend LUT, y2
	UINT32 reg_text_temp_prev_lut_x2        :8;	//(15:8,NA,60) //Text temporal previous blend LUT, x2
	UINT32 reg_text_temp_prev_lut_y3        :8;	//(23:16,NA,128) //Text temporal previous blend LUT, y3
	UINT32 reg_text_temp_prev_lut_x3        :8;	//(31:24,NA,80) //Text temporal previous blend LUT, x3
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952700 RW 0x08D0_00C0
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952704 RW 0x30F0_10E0
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952708 RW 0x80C0_60D0
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95270C RW 0x0870_0080
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952710 RW 0x1850_1060
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952714 RW 0x4000_2040
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952718 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95271C RW 0x086F_077F
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952720 RW 0x0000_0780
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952724 RW 0x0438_0EFF
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FD_TEXT_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952730 RO 0x0000_0000
	UINT32 ro_text_status_window0           :32;	//(31:0,NA,0) //Tmap temporal text status register (window0)
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952734 RO 0x0000_0000
	UINT32 ro_text_status_window1           :32;	//(31:0,NA,0) //Tmap temporal text status register (window1)
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952738 RO 0x0000_0000
	UINT32 ro_text_status_0                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_1                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95273C RO 0x0000_0000
	UINT32 ro_text_status_2                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_3                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952740 RO 0x0000_0000
	UINT32 ro_text_status_4                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_5                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952744 RO 0x0000_0000
	UINT32 ro_text_status_6                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_7                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952748 RO 0x0000_0000
	UINT32 ro_text_status_8                 :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_9                 :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95274C RO 0x0000_0000
	UINT32 ro_text_status_10                :16;	//(15:0,NA,0) //Tmap temporal text status register
	UINT32 ro_text_status_11                :16;	//(31:16,NA,0) //Tmap temporal text status register
	};
}PE_O26_VSD_SHP_CORE_TEXT_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952750 RW 0x0000_0000
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
}PE_O26_VSD_SHP_TEXT_BLEND_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952754 RW 0x5050_0000
	UINT32 reg_text_blend_mmd_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (SP/DER blend MMD), y0
	UINT32 reg_text_blend_mmd_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (SP/DER blend MMD), x0
	UINT32 reg_text_blend_mmd_lut_y1        :8;	//(23:16,NA,80) //Text blend LUT (SP/DER blend MMD), y1
	UINT32 reg_text_blend_mmd_lut_x1        :8;	//(31:24,NA,80) //Text blend LUT (SP/DER blend MMD), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952758 RW 0xFFFF_9696
	UINT32 reg_text_blend_mmd_lut_y2        :8;	//(7:0,NA,150) //Text blend LUT (SP/DER blend MMD), y2
	UINT32 reg_text_blend_mmd_lut_x2        :8;	//(15:8,NA,150) //Text blend LUT (SP/DER blend MMD), x2
	UINT32 reg_text_blend_mmd_lut_y3        :8;	//(23:16,NA,255) //Text blend LUT (SP/DER blend MMD), y3
	UINT32 reg_text_blend_mmd_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (SP/DER blend MMD), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95275C RW 0x5AC8_0000
	UINT32 reg_text_blend_sp_lut_y0         :8;	//(7:0,NA,0) //Text blend LUT (SP text blend), y0
	UINT32 reg_text_blend_sp_lut_x0         :8;	//(15:8,NA,0) //Text blend LUT (SP text blend), x0
	UINT32 reg_text_blend_sp_lut_y1         :8;	//(23:16,NA,200) //Text blend LUT (SP text blend), y1
	UINT32 reg_text_blend_sp_lut_x1         :8;	//(31:24,NA,90) //Text blend LUT (SP text blend), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952760 RW 0xDCFF_B4FF
	UINT32 reg_text_blend_sp_lut_y2         :8;	//(7:0,NA,255) //Text blend LUT (SP text blend), y2
	UINT32 reg_text_blend_sp_lut_x2         :8;	//(15:8,NA,180) //Text blend LUT (SP text blend), x2
	UINT32 reg_text_blend_sp_lut_y3         :8;	//(23:16,NA,255) //Text blend LUT (SP text blend), y3
	UINT32 reg_text_blend_sp_lut_x3         :8;	//(31:24,NA,220) //Text blend LUT (SP text blend), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952764 RW 0x5A00_0000
	UINT32 reg_text_blend_pti_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (PTI text blend), y0
	UINT32 reg_text_blend_pti_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (PTI text blend), x0
	UINT32 reg_text_blend_pti_lut_y1        :8;	//(23:16,NA,0) //Text blend LUT (PTI text blend), y1
	UINT32 reg_text_blend_pti_lut_x1        :8;	//(31:24,NA,90) //Text blend LUT (PTI text blend), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952768 RW 0xFF00_B400
	UINT32 reg_text_blend_pti_lut_y2        :8;	//(7:0,NA,0) //Text blend LUT (PTI text blend), y2
	UINT32 reg_text_blend_pti_lut_x2        :8;	//(15:8,NA,180) //Text blend LUT (PTI text blend), x2
	UINT32 reg_text_blend_pti_lut_y3        :8;	//(23:16,NA,0) //Text blend LUT (PTI text blend), y3
	UINT32 reg_text_blend_pti_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (PTI text blend), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95276C RW 0x50C8_0000
	UINT32 reg_text_blend_snr_lut_y0        :8;	//(7:0,NA,0) //Text blend LUT (SNR text blend), y0
	UINT32 reg_text_blend_snr_lut_x0        :8;	//(15:8,NA,0) //Text blend LUT (SNR text blend), x0
	UINT32 reg_text_blend_snr_lut_y1        :8;	//(23:16,NA,200) //Text blend LUT (SNR text blend), y1
	UINT32 reg_text_blend_snr_lut_x1        :8;	//(31:24,NA,80) //Text blend LUT (SNR text blend), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952770 RW 0xFFFF_96FF
	UINT32 reg_text_blend_snr_lut_y2        :8;	//(7:0,NA,255) //Text blend LUT (SNR text blend), y2
	UINT32 reg_text_blend_snr_lut_x2        :8;	//(15:8,NA,150) //Text blend LUT (SNR text blend), x2
	UINT32 reg_text_blend_snr_lut_y3        :8;	//(23:16,NA,255) //Text blend LUT (SNR text blend), y3
	UINT32 reg_text_blend_snr_lut_x3        :8;	//(31:24,NA,255) //Text blend LUT (SNR text blend), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952774 RW 0x32FF_0000
	UINT32 reg_text_blend_dpsum_lut_y0      :8;	//(7:0,NA,0) //Text blend LUT (DP sum blend), y0
	UINT32 reg_text_blend_dpsum_lut_x0      :8;	//(15:8,NA,0) //Text blend LUT (DP sum blend), x0
	UINT32 reg_text_blend_dpsum_lut_y1      :8;	//(23:16,NA,255) //Text blend LUT (DP sum blend), y1
	UINT32 reg_text_blend_dpsum_lut_x1      :8;	//(31:24,NA,50) //Text blend LUT (DP sum blend), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952778 RW 0xFFFF_78FF
	UINT32 reg_text_blend_dpsum_lut_y2      :8;	//(7:0,NA,255) //Text blend LUT (DP sum blend), y2
	UINT32 reg_text_blend_dpsum_lut_x2      :8;	//(15:8,NA,120) //Text blend LUT (DP sum blend), x2
	UINT32 reg_text_blend_dpsum_lut_y3      :8;	//(23:16,NA,255) //Text blend LUT (DP sum blend), y3
	UINT32 reg_text_blend_dpsum_lut_x3      :8;	//(31:24,NA,255) //Text blend LUT (DP sum blend), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95277C RW 0x320A_0000
	UINT32 reg_text_blend_dpsum_nt_lut_y0   :8;	//(7:0,NA,0) //Text blend LUT (DP sum blend, non-text), y0
	UINT32 reg_text_blend_dpsum_nt_lut_x0   :8;	//(15:8,NA,0) //Text blend LUT (DP sum blend, non-text), x0
	UINT32 reg_text_blend_dpsum_nt_lut_y1   :8;	//(23:16,NA,10) //Text blend LUT (DP sum blend, non-text), y1
	UINT32 reg_text_blend_dpsum_nt_lut_x1   :8;	//(31:24,NA,50) //Text blend LUT (DP sum blend, non-text), x1
	};
}PE_O26_VSD_SHP_TEXT_BLEND_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952780 RW 0xFF28_7814
	UINT32 reg_text_blend_dpsum_nt_lut_y2   :8;	//(7:0,NA,20) //Text blend LUT (DP sum blend, non-text), y2
	UINT32 reg_text_blend_dpsum_nt_lut_x2   :8;	//(15:8,NA,120) //Text blend LUT (DP sum blend, non-text), x2
	UINT32 reg_text_blend_dpsum_nt_lut_y3   :8;	//(23:16,NA,40) //Text blend LUT (DP sum blend, non-text), y3
	UINT32 reg_text_blend_dpsum_nt_lut_x3   :8;	//(31:24,NA,255) //Text blend LUT (DP sum blend, non-text), x3
	};
}PE_O26_VSD_SHP_TEXT_BLEND_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952784 RW 0x1830_0200
	UINT32 reg_dp_sum_nt_lut_y0             :8;	//(7:0,NA,0) //DP sum LUT for non-text control, y0
	UINT32 reg_dp_sum_nt_lut_x0             :8;	//(15:8,NA,2) //DP sum LUT for non-text control, x0
	UINT32 reg_dp_sum_nt_lut_y1             :8;	//(23:16,NA,48) //DP sum LUT for non-text control, y1
	UINT32 reg_dp_sum_nt_lut_x1             :8;	//(31:24,NA,24) //DP sum LUT for non-text control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_NT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952788 RW 0xFFFF_5050
	UINT32 reg_dp_sum_nt_lut_y2             :8;	//(7:0,NA,80) //DP sum LUT for non-text control, y2
	UINT32 reg_dp_sum_nt_lut_x2             :8;	//(15:8,NA,80) //DP sum LUT for non-text control, x2
	UINT32 reg_dp_sum_nt_lut_y3             :8;	//(23:16,NA,255) //DP sum LUT for non-text control, y3
	UINT32 reg_dp_sum_nt_lut_x3             :8;	//(31:24,NA,255) //DP sum LUT for non-text control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_NT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95278C RW 0x2828_0000
	UINT32 reg_dp_sum_cg_nt_lut_y0          :8;	//(7:0,NA,0) //DP sum LUT for delta_cg non-text control, y0
	UINT32 reg_dp_sum_cg_nt_lut_x0          :8;	//(15:8,NA,0) //DP sum LUT for delta_cg non-text control, x0
	UINT32 reg_dp_sum_cg_nt_lut_y1          :8;	//(23:16,NA,40) //DP sum LUT for delta_cg non-text control, y1
	UINT32 reg_dp_sum_cg_nt_lut_x1          :8;	//(31:24,NA,40) //DP sum LUT for delta_cg non-text control, x1
	};
}PE_O26_VSD_SHP_DP_SUM_NT_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952790 RW 0xFFFF_5050
	UINT32 reg_dp_sum_cg_nt_lut_y2          :8;	//(7:0,NA,80) //DP sum LUT for delta_cg non-text control, y2
	UINT32 reg_dp_sum_cg_nt_lut_x2          :8;	//(15:8,NA,80) //DP sum LUT for delta_cg non-text control, x2
	UINT32 reg_dp_sum_cg_nt_lut_y3          :8;	//(23:16,NA,255) //DP sum LUT for delta_cg non-text control, y3
	UINT32 reg_dp_sum_cg_nt_lut_x3          :8;	//(31:24,NA,255) //DP sum LUT for delta_cg non-text control, x3
	};
}PE_O26_VSD_SHP_DP_SUM_NT_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527A0 RO 0x0000_0000
	UINT32 reg_mon_core_fin_out_vert_cnt    :16;	//(15:0,NA,0) //Output previous frame vertical counter (core)
	UINT32 reg_mon_core_fin_in_vert_cnt     :16;	//(31:16,NA,0) //Input previous frame vertical counter (core)
	};
}PE_O26_VSD_SHP_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527A4 RO 0x0000_0000
	UINT32 reg_mon_in_vert_cnt              :16;	//(15:0,NA,0) //Input vertical counter(0~3839)
	UINT32 reg_mon_in_hori_cnt              :16;	//(31:16,NA,0) //Input horizontal counter(0~3839)
	};
}PE_O26_VSD_SHP_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527A8 RO 0x0000_0000
	UINT32 reg_mon_out_vert_cnt             :16;	//(15:0,NA,0) //Output vertical counter(0~3839)
	UINT32 reg_mon_out_hori_cnt             :16;	//(31:16,NA,0) //Output horizontal counter(0~3839)
	};
}PE_O26_VSD_SHP_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527AC RO 0x0000_0000
	UINT32 reg_mon_fin_out_vert_cnt         :16;	//(15:0,NA,0) //Output previous frame vertical counter 4K Last = 2160
	UINT32 reg_mon_fin_in_vert_cnt          :16;	//(31:16,NA,0) //Input previous frame vertical counter 4K Last = 2160
	};
}PE_O26_VSD_SHP_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527B0 RO 0x0000_0000
	UINT32 reg_mon_shp_i_sucfail            :32;	//(31:0,NA,0) //Input success/fail monitoring register
	};
}PE_O26_VSD_SHP_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527B4 RO 0x0000_0000
	UINT32 reg_mon_shp_o_sucfail            :32;	//(31:0,NA,0) //Output success/fail monitoring register
	};
}PE_O26_VSD_SHP_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527D0 RO 0x0000_0000
	UINT32 reg_status_a_avg                 :32;	//(31:0,NA,0) //FD status register (a_avg)
	};
}PE_O26_VSD_SHP_CORE_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527D4 RO 0x0000_0000
	UINT32 reg_status_t_avg                 :32;	//(31:0,NA,0) //FD status register (t_avg)
	};
}PE_O26_VSD_SHP_CORE_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527D8 RO 0x0000_0000
	UINT32 reg_status_e_avg                 :32;	//(31:0,NA,0) //FD status register (e_avg)
	};
}PE_O26_VSD_SHP_CORE_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527DC RO 0x0000_0000
	UINT32 reg_status_d_avg                 :32;	//(31:0,NA,0) //FD status register (d_avg)
	};
}PE_O26_VSD_SHP_CORE_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527E0 RO 0x0000_0000
	UINT32 ro_ibuf_vcnt                     :9;	//(8:0,NA,0) //MIF read vertical count
	UINT32 resvd                            :23;
	};
}PE_O26_VSD_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527E4 RO 0x0000_0000
	UINT32 ro_out_v_line                    :16;	//(15:0,NA,0) //Scaler core output vertical count remained
	UINT32 ro_in_v_line                     :16;	//(31:16,NA,0) //Scaler core input vertical count remained
	};
}PE_O26_VSD_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527E8 RO 0x0000_0000
	UINT32 ro_edge_status_0                 :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_1                 :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527EC RO 0x0000_0000
	UINT32 ro_edge_status_2                 :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_3                 :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527F0 RO 0x0000_0000
	UINT32 ro_edge_status_4                 :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_5                 :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527F4 RO 0x0000_0000
	UINT32 ro_edge_status_6                 :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_7                 :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527F8 RO 0x0000_0000
	UINT32 ro_edge_status_8                 :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_9                 :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9527FC RO 0x0000_0000
	UINT32 ro_edge_status_10                :16;	//(15:0,NA,0) //Edge status register
	UINT32 ro_edge_status_11                :16;	//(31:16,NA,0) //Edge status register
	};
}PE_O26_VSD_SHP_CORE_EDGE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952800 RO 0x0000_0000
	UINT32 ro_tmap_status_window0           :32;	//(31:0,NA,0) //Tmap temporal texture status register (window0)
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952804 RO 0x0000_0000
	UINT32 ro_tmap_status_window1           :32;	//(31:0,NA,0) //Tmap temporal texture status register (window1)
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952808 RO 0x0000_0000
	UINT32 ro_tmap_status_0                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_1                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95280C RO 0x0000_0000
	UINT32 ro_tmap_status_2                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_3                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952810 RO 0x0000_0000
	UINT32 ro_tmap_status_4                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_5                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952814 RO 0x0000_0000
	UINT32 ro_tmap_status_6                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_7                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952818 RO 0x0000_0000
	UINT32 ro_tmap_status_8                 :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_9                 :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95281C RO 0x0000_0000
	UINT32 ro_tmap_status_10                :16;	//(15:0,NA,0) //Tmap temporal texture status register
	UINT32 ro_tmap_status_11                :16;	//(31:16,NA,0) //Tmap temporal texture status register
	};
}PE_O26_VSD_SHP_CORE_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952820 RW 0x0000_0000
	UINT32 reg_core0_win_face_win0_en       :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_core0_win_face_win1_en       :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_core0_win_face_win01_en      :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_face_win_outside   :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_core0_win_face_win_en        :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_core0_win_face_bdr_alpha     :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_core0_win_face_bdr_wid       :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_core0_win_face_bdr_en        :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_core0_win_face_cr5           :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_core0_win_face_cb5           :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_core0_win_face_yy6           :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952824 RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w0_x0     :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_core0_win_face_win_w0_y0     :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952828 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w0_x1     :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_core0_win_face_win_w0_y1     :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95282C RW 0x0000_0000
	UINT32 reg_core0_win_face_win_w1_x0     :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_core0_win_face_win_w1_y0     :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952830 RW 0x086F_0EFF
	UINT32 reg_core0_win_face_win_w1_x1     :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_core0_win_face_win_w1_y1     :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952834 RW 0x0000_0000
	UINT32 reg_core0_win_face_value         :8;	//(7:0,NA,0) //Force FACE value
	UINT32 resvd                            :24;
	};
}PE_O26_VSD_SHP_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952838 RW 0x0000_0000
	UINT32 reg_core0_win_body_win0_en       :1;	//(0:0,NA,0) //Window control, select only window0 as active area
	UINT32 reg_core0_win_body_win1_en       :1;	//(1:1,NA,0) //Window control, select only window1 as active area
	UINT32 reg_core0_win_body_win01_en      :1;	//(2:2,NA,0) //Window control, select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_body_win_outside   :1;	//(6:6,NA,0) //Window control, using (0:inside, 1:the other side) of selected area
	UINT32 reg_core0_win_body_win_en        :1;	//(7:7,NA,0) //Window control, active area (0:full screen, 1:specified by win0 or win1)
	UINT32 reg_core0_win_body_bdr_alpha     :5;	//(12:8,NA,0) //Window control, border alpha for alpha-blending
	UINT32 reg_core0_win_body_bdr_wid       :2;	//(14:13,NA,0) //Window control, border width
	UINT32 reg_core0_win_body_bdr_en        :1;	//(15:15,NA,0) //Window control, border enable
	UINT32 reg_core0_win_body_cr5           :5;	//(20:16,NA,0) //Window control, border color: cr5
	UINT32 reg_core0_win_body_cb5           :5;	//(25:21,NA,0) //Window control, border color: cb5
	UINT32 reg_core0_win_body_yy6           :6;	//(31:26,NA,0) //Window control, border color: yy6
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95283C RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w0_x0     :16;	//(15:0,NA,0) //Window control, win_w0_x0
	UINT32 reg_core0_win_body_win_w0_y0     :16;	//(31:16,NA,0) //Window control, win_w0_y0
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952840 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w0_x1     :16;	//(15:0,NA,3839) //Window control, win_w0_x1
	UINT32 reg_core0_win_body_win_w0_y1     :16;	//(31:16,NA,2159) //Window control, win_w0_y1
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952844 RW 0x0000_0000
	UINT32 reg_core0_win_body_win_w1_x0     :16;	//(15:0,NA,0) //Window control, win_w1_x0
	UINT32 reg_core0_win_body_win_w1_y0     :16;	//(31:16,NA,0) //Window control, win_w1_y0
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952848 RW 0x086F_0EFF
	UINT32 reg_core0_win_body_win_w1_x1     :16;	//(15:0,NA,3839) //Window control, win_w1_x1
	UINT32 reg_core0_win_body_win_w1_y1     :16;	//(31:16,NA,2159) //Window control, win_w1_y1
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95284C RW 0x0000_0000
	UINT32 reg_core0_win_body_value         :8;	//(7:0,NA,0) //Force BODY value
	UINT32 resvd                            :24;
	};
}PE_O26_VSD_SHP_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952850 RW 0x0000_0000
	UINT32 reg_luma_dp_blend_en             :1;	//(0:0,NA,0) //Luma blend enable
	UINT32 resvd0                           :7;
	UINT32 reg_luma_dp_blend_debug_sel_en   :1;	//(8:8,NA,0) //Debug mode (0: gain, 1: bypass Y)
	UINT32 resvd1                           :23;
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952854 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y0                  :8;	//(7:0,NA,192) //Luma blend LUT, y0
	UINT32 reg_gain_lut_x0                  :8;	//(15:8,NA,0) //Luma blend LUT, x0
	UINT32 reg_gain_lut_y1                  :8;	//(23:16,NA,192) //Luma blend LUT, y1
	UINT32 reg_gain_lut_x1                  :8;	//(31:24,NA,0) //Luma blend LUT, x1
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952858 RW 0x8020_8020
	UINT32 reg_gain_lut_y2                  :8;	//(7:0,NA,32) //Luma blend LUT, y2
	UINT32 reg_gain_lut_x2                  :8;	//(15:8,NA,128) //Luma blend LUT, x2
	UINT32 reg_gain_lut_y3                  :8;	//(23:16,NA,32) //Luma blend LUT, y3
	UINT32 reg_gain_lut_x3                  :8;	//(31:24,NA,128) //Luma blend LUT, x3
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95285C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y4                  :8;	//(7:0,NA,192) //Luma blend LUT, y4
	UINT32 reg_gain_lut_x4                  :8;	//(15:8,NA,0) //Luma blend LUT, x4
	UINT32 reg_gain_lut_y5                  :8;	//(23:16,NA,192) //Luma blend LUT, y5
	UINT32 reg_gain_lut_x5                  :8;	//(31:24,NA,0) //Luma blend LUT, x5
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952860 RW 0x8020_8020
	UINT32 reg_gain_lut_y6                  :8;	//(7:0,NA,32) //Luma blend LUT, y6
	UINT32 reg_gain_lut_x6                  :8;	//(15:8,NA,128) //Luma blend LUT, x6
	UINT32 reg_gain_lut_y7                  :8;	//(23:16,NA,32) //Luma blend LUT, y7
	UINT32 reg_gain_lut_x7                  :8;	//(31:24,NA,128) //Luma blend LUT, x7
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952864 RW 0x00C0_00C0
	UINT32 reg_gain_lut_y8                  :8;	//(7:0,NA,192) //Luma blend LUT, y8
	UINT32 reg_gain_lut_x8                  :8;	//(15:8,NA,0) //Luma blend LUT, x8
	UINT32 reg_gain_lut_y9                  :8;	//(23:16,NA,192) //Luma blend LUT, y9
	UINT32 reg_gain_lut_x9                  :8;	//(31:24,NA,0) //Luma blend LUT, x9
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952868 RW 0x8020_8020
	UINT32 reg_gain_lut_y10                 :8;	//(7:0,NA,32) //Luma blend LUT, y10
	UINT32 reg_gain_lut_x10                 :8;	//(15:8,NA,128) //Luma blend LUT, x10
	UINT32 reg_gain_lut_y11                 :8;	//(23:16,NA,32) //Luma blend LUT, y11
	UINT32 reg_gain_lut_x11                 :8;	//(31:24,NA,128) //Luma blend LUT, x11
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95286C RW 0x00C0_00C0
	UINT32 reg_gain_lut_y12                 :8;	//(7:0,NA,192) //Luma blend LUT, y12
	UINT32 reg_gain_lut_x12                 :8;	//(15:8,NA,0) //Luma blend LUT, x12
	UINT32 reg_gain_lut_y13                 :8;	//(23:16,NA,192) //Luma blend LUT, y13
	UINT32 reg_gain_lut_x13                 :8;	//(31:24,NA,0) //Luma blend LUT, x13
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952870 RW 0x8020_8020
	UINT32 reg_gain_lut_y14                 :8;	//(7:0,NA,32) //Luma blend LUT, y14
	UINT32 reg_gain_lut_x14                 :8;	//(15:8,NA,128) //Luma blend LUT, x14
	UINT32 reg_gain_lut_y15                 :8;	//(23:16,NA,32) //Luma blend LUT, y15
	UINT32 reg_gain_lut_x15                 :8;	//(31:24,NA,128) //Luma blend LUT, x15
	};
}PE_O26_VSD_SHP_LUMA_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952874 RW 0x0001_0003
	UINT32 resvd0                           :16;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//(18:16,NA,1) //Pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//(20:19,NA,0) //Pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//(23:21,NA,0) //Pre-mmd cut resolution
	UINT32 resvd1                           :8;
	};
}PE_O26_VSD_SHP_SMTH_MMD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952878 RW 0x8080_8007
	UINT32 reg_textgain_en                  :1;	//(0:0,NA,1) //Texture gain enable
	UINT32 reg_bodygain_en                  :1;	//(1:1,NA,1) //BODY gain enable
	UINT32 reg_headgain_en                  :1;	//(2:2,NA,1) //HEAD gain enable
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :2;	//(5:4,NA,0) //Object gain selection (0:max, 1:sum, 2:mul)
	UINT32 reg_head_body_sel                :1;	//(6:6,NA,0) //HEAD/BODY gain selection (0:max, 1:sum)
	UINT32 resvd1                           :1;
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,128) //Texture master gain
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,128) //BODY master gain
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,128) //HEAD master gain
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95287C RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,64) //HEAD gain LUT, y1
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,64) //HEAD gain LUT, x1
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0) //HEAD gain LUT, y0
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0) //HEAD gain LUT, x0
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952880 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,255) //HEAD gain LUT, y3
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,255) //HEAD gain LUT, x3
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,128) //HEAD gain LUT, y2
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,128) //HEAD gain LUT, x2
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952884 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,64) //BODY gain LUT, y1
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,64) //BODY gain LUT, x1
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0) //BODY gain LUT, y0
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0) //BODY gain LUT, x0
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952888 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,255) //BODY gain LUT, y3
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,255) //BODY gain LUT, x3
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,128) //BODY gain LUT, y2
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,128) //BODY gain LUT, x2
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95288C RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,64) //Texture gain LUT, y1
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,64) //Texture gain LUT, x1
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0) //Texture gain LUT, y0
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0) //Texture gain LUT, x0
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952890 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,255) //Texture gain LUT, x3
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,255) //Texture gain LUT, y3
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,128) //Texture gain LUT, x2
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,128) //Texture gain LUT, y2
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952894 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :15;	//(14:0,NA,0) //Window mode, x start
	UINT32 reg_win_in_disable               :1;	//(15:15,NA,0) //Disable merge_gain inside window
	UINT32 reg_pxl_y0                       :15;	//(30:16,NA,0) //Window mode, y start
	UINT32 reg_win_out_disable              :1;	//(31:31,NA,0) //Disable merge_gain outside window
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC952898 RW 0x0000_0000
	UINT32 reg_pxl_width                    :16;	//(15:0,NA,0) //Window mode, height
	UINT32 reg_pxl_height                   :16;	//(31:16,NA,0) //Window mode, width
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95289C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0) //Inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0) //Outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_VSD_SHP_SMTH_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528A0 RW 0x0000_0000
	UINT32 reg_cr_smth_control_en           :2;	//(1:0,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd0                           :2;
	UINT32 reg_cb_smth_control_en           :2;	//(5:4,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd1                           :2;
	UINT32 reg_yy_smth_control_en           :2;	//(9:8,NA,0) //0: alpha blending	1: original	2: 7x7 blur
	UINT32 resvd2                           :22;
	};
}PE_O26_VSD_SHP_SMTH_CON_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528B0 RW 0x0000_02A0
	UINT32 reg_ca_en                        :1;	//(0:0,NA,0) //CA enable
	UINT32 reg_ca_default_cb_en             :1;	//(1:1,NA,0) //CA blending default CB value(=512) enable
	UINT32 reg_ca_default_cr_en             :1;	//(2:2,NA,0) //CA blending default CR value(=512) enable
	UINT32 resvd0                           :1;
	UINT32 reg_ca_gain_yy_shift             :2;	//(5:4,NA,2) //CA gain shift mode (0: shift4, 1: shift5, 2: shift6, 3: shift7), Y
	UINT32 reg_ca_gain_cb_shift             :2;	//(7:6,NA,2) //CA gain shift mode (0: shift4, 1: shift5, 2: shift6, 3: shift7), CB
	UINT32 reg_ca_gain_cr_shift             :2;	//(9:8,NA,2) //CA gain shift mode (0: shift4, 1: shift5, 2: shift6, 3: shift7), CR
	UINT32 reg_ca_mmd_shift                 :3;	//(12:10,NA,2) //CA gain shift mode (0: shift4, 1: shift5, 2: shift6, 3: shift7), MMD
	UINT32 reg_ca_debug_mode                :2;	//(14:13,NA,2) //CA debug mode (0: normal output, 1: gain Y, 2: final gain)
	UINT32 resvd1                           :17;
	};
}PE_O26_VSD_SHP_CA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528B4 RW 0x0000_0000
	UINT32 reg_ca_gain_yy_lut_y0            :11;	//(10:0,NA,0) //CA gain LUT, Y, y0
	UINT32 resvd0                           :5;
	UINT32 reg_ca_gain_yy_lut_x0            :10;	//(25:16,NA,0) //CA gain LUT, Y, x0
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528B8 RW 0x0000_0000
	UINT32 reg_ca_gain_yy_lut_y1            :11;	//(10:0,NA,0) //CA gain LUT, Y, y1
	UINT32 resvd0                           :5;
	UINT32 reg_ca_gain_yy_lut_x1            :10;	//(25:16,NA,0) //CA gain LUT, Y, x1
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528BC RW 0x0000_0000
	UINT32 reg_ca_gain_yy_lut_y2            :11;	//(10:0,NA,0) //CA gain LUT, Y, y2
	UINT32 resvd0                           :5;
	UINT32 reg_ca_gain_yy_lut_x2            :10;	//(25:16,NA,0) //CA gain LUT, Y, x2
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528C0 RW 0x0258_07F8
	UINT32 reg_ca_gain_yy_lut_y3            :11;	//(10:0,NA,2040) //CA gain LUT, Y, y3
	UINT32 resvd0                           :5;
	UINT32 reg_ca_gain_yy_lut_x3            :10;	//(25:16,NA,600) //CA gain LUT, Y, x3
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528C4 RW 0x0000_0000
	UINT32 reg_ca_gain_cb_lut_y0            :10;	//(9:0,NA,0) //CA gain LUT, CB, y0
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cb_lut_x0            :10;	//(25:16,NA,0) //CA gain LUT, CB, x0
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528C8 RW 0x001E_03FF
	UINT32 reg_ca_gain_cb_lut_y1            :10;	//(9:0,NA,1023) //CA gain LUT, CB, y1
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cb_lut_x1            :10;	//(25:16,NA,30) //CA gain LUT, CB, x1
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528CC RW 0x03E8_03FF
	UINT32 reg_ca_gain_cb_lut_y2            :10;	//(9:0,NA,1023) //CA gain LUT, CB, y2
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cb_lut_x2            :10;	//(25:16,NA,1000) //CA gain LUT, CB, x2
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528D0 RW 0x03FF_0000
	UINT32 reg_ca_gain_cb_lut_y3            :10;	//(9:0,NA,0) //CA gain LUT, CB, y3
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cb_lut_x3            :10;	//(25:16,NA,1023) //CA gain LUT, CB, x3
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528D4 RW 0x0000_0000
	UINT32 reg_ca_gain_cr_lut_y0            :10;	//(9:0,NA,0) //CA gain LUT, CR, y0
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cr_lut_x0            :10;	//(25:16,NA,0) //CA gain LUT, CR, x0
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528D8 RW 0x001E_03FF
	UINT32 reg_ca_gain_cr_lut_y1            :10;	//(9:0,NA,1023) //CA gain LUT, CR, y1
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cr_lut_x1            :10;	//(25:16,NA,30) //CA gain LUT, CR, x1
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528DC RW 0x03E8_03FF
	UINT32 reg_ca_gain_cr_lut_y2            :10;	//(9:0,NA,1023) //CA gain LUT, CR, y2
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cr_lut_x2            :10;	//(25:16,NA,1000) //CA gain LUT, CR, x2
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528E0 RW 0x03FF_0000
	UINT32 reg_ca_gain_cr_lut_y3            :10;	//(9:0,NA,0) //CA gain LUT, CR, y3
	UINT32 resvd0                           :6;
	UINT32 reg_ca_gain_cr_lut_x3            :10;	//(25:16,NA,1023) //CA gain LUT, CR, x3
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_SHP_CA_CTRL_0C_T;

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
}PE_O26_VSD_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228F4 RW 0x0000_0000
	UINT32 reg_cur_sc						:8;		//7:0	IWSC - iir weight scene change cur sc
	UINT32 reg_ui_gain_w					:8;		//15:8	UGW - ui gain white
	UINT32 reg_ui_gain_b					:8;		//23:16 UGB - ui gain black
	UINT32 reg_vy_mode                      :2;		//25:24 ui rgb select
	UINT32 resvd0							:6;		
	};
}PE_O26_VSD_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCA228F8 RW 0x0000_0000
	UINT32 reg_obc_debug                      : 2;  // 1:0, 0: shp result   1 : face map   2 : object map
	};
}PE_O26_VSD_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9528FC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_VSD_SHP_FSW_CTRL_03_T;

typedef struct {
	PE_O26_VSD_SHP_CORE_CTRL_00_T                     shp_core_ctrl_00;	//0xCC952000
	PE_O26_VSD_SHP_CORE_CTRL_01_T                     shp_core_ctrl_01;	//0xCC952004
	PE_O26_VSD_SHP_CORE_CTRL_02_T                     shp_core_ctrl_02;	//0xCC952008
	PE_O26_VSD_SHP_CORE_CTRL_03_T                     shp_core_ctrl_03;	//0xCC95200C
	PE_O26_VSD_SHP_CORE_CTRL_04_T                     shp_core_ctrl_04;	//0xCC952010
	PE_O26_VSD_SHP_NEW_FD_CTRL_00_T                 shp_new_fd_ctrl_00;	//0xCC952014
	PE_O26_VSD_SHP_NEW_FD_CTRL_01_T                 shp_new_fd_ctrl_01;	//0xCC952018
	PE_O26_VSD_SHP_NEW_FD_CTRL_02_T                 shp_new_fd_ctrl_02;	//0xCC95201C
	PE_O26_VSD_SHP_NEW_FD_CTRL_03_T                 shp_new_fd_ctrl_03;	//0xCC952020
	PE_O26_VSD_SHP_NEW_FD_CTRL_04_T                 shp_new_fd_ctrl_04;	//0xCC952024
	PE_O26_VSD_SHP_TEXT_REGION_MAP_00_T         shp_text_region_map_00;	//0xCC952028
	UINT32                                                      reserved0;	//0xCC95202C
	UINT32                                                      reserved1;	//0xCC952030
	UINT32                                                      reserved2;	//0xCC952034
	UINT32                                                      reserved3;	//0xCC952038
	UINT32                                                      reserved4;	//0xCC95203C
	PE_O26_VSD_SHP_PAT_GEN_CTRL_00_T               shp_pat_gen_ctrl_00;	//0xCC952040
	UINT32                                                      reserved5;	//0xCC952044
	UINT32                                                      reserved6;	//0xCC952048
	UINT32                                                      reserved7;	//0xCC95204C
	PE_O26_VSD_SHP_GOS_CTRL_00_T                       shp_gos_ctrl_00;	//0xCC952050
	UINT32                                                      reserved8;	//0xCC952054
	UINT32                                                      reserved9;	//0xCC952058
	UINT32                                                  reserved10;	//0xCC95205C
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_00_T             shp_sync_dly_ctrl_00;	//0xCC952060
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_01_T             shp_sync_dly_ctrl_01;	//0xCC952064
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_02_T             shp_sync_dly_ctrl_02;	//0xCC952068
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_03_T             shp_sync_dly_ctrl_03;	//0xCC95206C
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_04_T             shp_sync_dly_ctrl_04;	//0xCC952070
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_05_T             shp_sync_dly_ctrl_05;	//0xCC952074
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_06_T             shp_sync_dly_ctrl_06;	//0xCC952078
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_07_T             shp_sync_dly_ctrl_07;	//0xCC95207C
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_08_T             shp_sync_dly_ctrl_08;	//0xCC952080
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_09_T             shp_sync_dly_ctrl_09;	//0xCC952084
	PE_O26_VSD_SHP_SYNC_DLY_CTRL_0A_T             shp_sync_dly_ctrl_0a;	//0xCC952088
	UINT32                                                  reserved11;	//0xCC95208C
	PE_O26_VSD_SHP_ROI_MASK_CTRL_00_T             shp_roi_mask_ctrl_00;	//0xCC952090
	PE_O26_VSD_SHP_ROI_MASK_CTRL_01_T             shp_roi_mask_ctrl_01;	//0xCC952094
	PE_O26_VSD_SHP_ROI_MASK_CTRL_02_T             shp_roi_mask_ctrl_02;	//0xCC952098
	UINT32                                                  reserved12;	//0xCC95209C
	PE_O26_VSD_SHP_ESF_CTRL_00_T                       shp_esf_ctrl_00;	//0xCC9520A0
	PE_O26_VSD_SHP_ESF_CTRL_01_T                       shp_esf_ctrl_01;	//0xCC9520A4
	PE_O26_VSD_SHP_ESF_CTRL_02_T                       shp_esf_ctrl_02;	//0xCC9520A8
	UINT32                                                  reserved13;	//0xCC9520AC
	PE_O26_VSD_SHP_ESF_WIN_CTRL_00_T               shp_esf_win_ctrl_00;	//0xCC9520B0
	PE_O26_VSD_SHP_ESF_WIN_CTRL_01_T               shp_esf_win_ctrl_01;	//0xCC9520B4
	PE_O26_VSD_SHP_ESF_WIN_CTRL_02_T               shp_esf_win_ctrl_02;	//0xCC9520B8
	PE_O26_VSD_SHP_ESF_WIN_CTRL_03_T               shp_esf_win_ctrl_03;	//0xCC9520BC
	PE_O26_VSD_SHP_ESF_WIN_CTRL_04_T               shp_esf_win_ctrl_04;	//0xCC9520C0
	UINT32                                                  reserved14;	//0xCC9520C4
	UINT32                                                  reserved15;	//0xCC9520C8
	UINT32                                                  reserved16;	//0xCC9520CC
	UINT32                                                  reserved17;	//0xCC9520D0
	UINT32                                                  reserved18;	//0xCC9520D4
	UINT32                                                  reserved19;	//0xCC9520D8
	UINT32                                                  reserved20;	//0xCC9520DC
	UINT32                                                  reserved21;	//0xCC9520E0
	UINT32                                                  reserved22;	//0xCC9520E4
	UINT32                                                  reserved23;	//0xCC9520E8
	UINT32                                                  reserved24;	//0xCC9520EC
	PE_O26_VSD_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0xCC9520F0
	UINT32                                                  reserved25;	//0xCC9520F4
	UINT32                                                  reserved26;	//0xCC9520F8
	UINT32                                                  reserved27;	//0xCC9520FC
	PE_O26_VSD_SHP_FD_CTRL_00_T                         shp_fd_ctrl_00;	//0xCC952100
	PE_O26_VSD_SHP_FD_CTRL_01_T                         shp_fd_ctrl_01;	//0xCC952104
	PE_O26_VSD_SHP_FD_CTRL_02_T                         shp_fd_ctrl_02;	//0xCC952108
	PE_O26_VSD_SHP_FD_CTRL_03_T                         shp_fd_ctrl_03;	//0xCC95210C
	PE_O26_VSD_SHP_FD_CTRL_04_T                         shp_fd_ctrl_04;	//0xCC952110
	PE_O26_VSD_SHP_FD_CTRL_05_T                         shp_fd_ctrl_05;	//0xCC952114
	PE_O26_VSD_SHP_FD_CTRL_06_T                         shp_fd_ctrl_06;	//0xCC952118
	PE_O26_VSD_SHP_FD_CTRL_07_T                         shp_fd_ctrl_07;	//0xCC95211C
	PE_O26_VSD_SHP_FD_CTRL_08_T                         shp_fd_ctrl_08;	//0xCC952120
	PE_O26_VSD_SHP_FD_CTRL_09_T                         shp_fd_ctrl_09;	//0xCC952124
	PE_O26_VSD_SHP_FD_CTRL_0A_T                         shp_fd_ctrl_0a;	//0xCC952128
	PE_O26_VSD_SHP_FD_CTRL_0B_T                         shp_fd_ctrl_0b;	//0xCC95212C
	PE_O26_VSD_SHP_FD_CTRL_0C_T                         shp_fd_ctrl_0c;	//0xCC952130
	PE_O26_VSD_SHP_FD_CTRL_0D_T                         shp_fd_ctrl_0d;	//0xCC952134
	PE_O26_VSD_SHP_FD_CTRL_0E_T                         shp_fd_ctrl_0e;	//0xCC952138
	PE_O26_VSD_SHP_FD_CTRL_0F_T                         shp_fd_ctrl_0f;	//0xCC95213C
	PE_O26_VSD_SHP_FD_CTRL_10_T                         shp_fd_ctrl_10;	//0xCC952140
	PE_O26_VSD_SHP_FD_CTRL_11_T                         shp_fd_ctrl_11;	//0xCC952144
	PE_O26_VSD_SHP_FD_CTRL_12_T                         shp_fd_ctrl_12;	//0xCC952148
	PE_O26_VSD_SHP_FD_CTRL_13_T                         shp_fd_ctrl_13;	//0xCC95214C
	PE_O26_VSD_SHP_FD_CTRL_14_T                         shp_fd_ctrl_14;	//0xCC952150
	PE_O26_VSD_SHP_FD_CTRL_15_T                         shp_fd_ctrl_15;	//0xCC952154
	PE_O26_VSD_SHP_FD_CTRL_16_T                         shp_fd_ctrl_16;	//0xCC952158
	UINT32                                                  reserved28;	//0xCC95215C
	PE_O26_VSD_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0xCC952160
	PE_O26_VSD_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0xCC952164
	PE_O26_VSD_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0xCC952168
	PE_O26_VSD_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0xCC95216C
	PE_O26_VSD_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0xCC952170
	PE_O26_VSD_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0xCC952174
	PE_O26_VSD_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0xCC952178
	PE_O26_VSD_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0xCC95217C
	PE_O26_VSD_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0xCC952180
	PE_O26_VSD_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0xCC952184
	PE_O26_VSD_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0xCC952188
	PE_O26_VSD_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0xCC95218C
	PE_O26_VSD_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0xCC952190
	PE_O26_VSD_SHP_APL_CTRL_00_T                       shp_apl_ctrl_00;	//0xCC952194
	UINT32                                                  reserved29;	//0xCC952198
	UINT32                                                  reserved30;	//0xCC95219C
	PE_O26_VSD_SHP_LC_CTRL_00_T                         shp_lc_ctrl_00;	//0xCC9521A0
	PE_O26_VSD_SHP_LC_CTRL_01_T                         shp_lc_ctrl_01;	//0xCC9521A4
	PE_O26_VSD_SHP_LC_CTRL_02_T                         shp_lc_ctrl_02;	//0xCC9521A8
	PE_O26_VSD_SHP_LC_CTRL_03_T                         shp_lc_ctrl_03;	//0xCC9521AC
	PE_O26_VSD_SHP_LC_CTRL_04_T                         shp_lc_ctrl_04;	//0xCC9521B0
	UINT32                                                  reserved31;	//0xCC9521B4
	UINT32                                                  reserved32;	//0xCC9521B8
	UINT32                                                  reserved33;	//0xCC9521BC
	PE_O26_VSD_SHP_DER_CTRL_00_T                       shp_der_ctrl_00;	//0xCC9521C0
	PE_O26_VSD_SHP_DER_CTRL_01_T                       shp_der_ctrl_01;	//0xCC9521C4
	PE_O26_VSD_SHP_DER_CTRL_02_T                       shp_der_ctrl_02;	//0xCC9521C8
	PE_O26_VSD_SHP_DER_CTRL_03_T                       shp_der_ctrl_03;	//0xCC9521CC
	PE_O26_VSD_SHP_DER_CTRL_04_T                       shp_der_ctrl_04;	//0xCC9521D0
	PE_O26_VSD_SHP_DER_CTRL_05_T                       shp_der_ctrl_05;	//0xCC9521D4
	PE_O26_VSD_SHP_DER_CTRL_06_T                       shp_der_ctrl_06;	//0xCC9521D8
	PE_O26_VSD_SHP_DER_CTRL_07_T                       shp_der_ctrl_07;	//0xCC9521DC
	PE_O26_VSD_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0xCC9521E0
	PE_O26_VSD_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0xCC9521E4
	PE_O26_VSD_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0xCC9521E8
	PE_O26_VSD_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0xCC9521EC
	PE_O26_VSD_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0xCC9521F0
	PE_O26_VSD_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0xCC9521F4
	PE_O26_VSD_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0xCC9521F8
	PE_O26_VSD_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0xCC9521FC
	PE_O26_VSD_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0xCC952200
	PE_O26_VSD_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0xCC952204
	PE_O26_VSD_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0xCC952208
	PE_O26_VSD_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0xCC95220C
	PE_O26_VSD_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0xCC952210
	UINT32                                                  reserved34;	//0xCC952214
	UINT32                                                  reserved35;	//0xCC952218
	UINT32                                                  reserved36;	//0xCC95221C
	PE_O26_VSD_SHP_PTI_CTRL_00_T                       shp_pti_ctrl_00;	//0xCC952220
	PE_O26_VSD_SHP_PTI_CTRL_01_T                       shp_pti_ctrl_01;	//0xCC952224
	PE_O26_VSD_SHP_PTI_CTRL_02_T                       shp_pti_ctrl_02;	//0xCC952228
	PE_O26_VSD_SHP_PTI_CTRL_03_T                       shp_pti_ctrl_03;	//0xCC95222C
	PE_O26_VSD_SHP_STI_CTRL_00_T                       shp_sti_ctrl_00;	//0xCC952230
	UINT32                                                  reserved37;	//0xCC952234
	UINT32                                                  reserved38;	//0xCC952238
	UINT32                                                  reserved39;	//0xCC95223C
	PE_O26_VSD_SHP_TGEN_CTRL_00_T                     shp_tgen_ctrl_00;	//0xCC952240
	PE_O26_VSD_SHP_TGEN_CTRL_01_T                     shp_tgen_ctrl_01;	//0xCC952244
	PE_O26_VSD_SHP_TGEN_CTRL_02_T                     shp_tgen_ctrl_02;	//0xCC952248
	PE_O26_VSD_SHP_TGEN_CTRL_03_C0_T               shp_tgen_ctrl_03_c0;	//0xCC95224C
	PE_O26_VSD_SHP_TGEN_CTRL_03_C1_T               shp_tgen_ctrl_03_c1;	//0xCC952250
	PE_O26_VSD_SHP_TGEN_CTRL_04_T                     shp_tgen_ctrl_04;	//0xCC952254
	PE_O26_VSD_SHP_TGEN_CTRL_05_T                     shp_tgen_ctrl_05;	//0xCC952258
	PE_O26_VSD_SHP_TGEN_CTRL_06_T                     shp_tgen_ctrl_06;	//0xCC95225C
	PE_O26_VSD_SHP_TGEN_CTRL_07_T                     shp_tgen_ctrl_07;	//0xCC952260
	PE_O26_VSD_SHP_TGEN_CTRL_08_T                     shp_tgen_ctrl_08;	//0xCC952264
	PE_O26_VSD_SHP_TGEN_CTRL_09_T                     shp_tgen_ctrl_09;	//0xCC952268
	PE_O26_VSD_SHP_TGEN_CTRL_0A_T                     shp_tgen_ctrl_0a;	//0xCC95226C
	PE_O26_VSD_SHP_TGEN_CTRL_0B_T                     shp_tgen_ctrl_0b;	//0xCC952270
	PE_O26_VSD_SHP_SNR_CTRL_00_T                       shp_snr_ctrl_00;	//0xCC952274
	UINT32                                                  reserved40;	//0xCC952278
	UINT32                                                  reserved41;	//0xCC95227C
	PE_O26_VSD_SHP_DCTP_CTRL_00_T                     shp_dctp_ctrl_00;	//0xCC952280
	PE_O26_VSD_SHP_DCTP_CTRL_01_T                     shp_dctp_ctrl_01;	//0xCC952284
	PE_O26_VSD_SHP_DCTP_CTRL_02_T                     shp_dctp_ctrl_02;	//0xCC952288
	PE_O26_VSD_SHP_DCTP_CTRL_03_T                     shp_dctp_ctrl_03;	//0xCC95228C
	PE_O26_VSD_SHP_DCTP_CTRL_04_T                     shp_dctp_ctrl_04;	//0xCC952290
	PE_O26_VSD_SHP_DCTP_CTRL_05_T                     shp_dctp_ctrl_05;	//0xCC952294
	PE_O26_VSD_SHP_DCTP_CTRL_06_T                     shp_dctp_ctrl_06;	//0xCC952298
	PE_O26_VSD_SHP_DCTP_CTRL_07_T                     shp_dctp_ctrl_07;	//0xCC95229C
	PE_O26_VSD_SHP_DCTP_CTRL_08_T                     shp_dctp_ctrl_08;	//0xCC9522A0
	PE_O26_VSD_SHP_DCTP_CTRL_09_T                     shp_dctp_ctrl_09;	//0xCC9522A4
	PE_O26_VSD_SHP_DCTP_CTRL_0A_T                     shp_dctp_ctrl_0a;	//0xCC9522A8
	PE_O26_VSD_SHP_DCTP_CTRL_0B_T                     shp_dctp_ctrl_0b;	//0xCC9522AC
	PE_O26_VSD_SHP_DCTP_CTRL_0C_T                     shp_dctp_ctrl_0c;	//0xCC9522B0
	PE_O26_VSD_SHP_DCTP_CTRL_0D_T                     shp_dctp_ctrl_0d;	//0xCC9522B4
	PE_O26_VSD_SHP_DCTP_CTRL_0E_T                     shp_dctp_ctrl_0e;	//0xCC9522B8
	PE_O26_VSD_SHP_DCTP_CTRL_0F_T                     shp_dctp_ctrl_0f;	//0xCC9522BC
	PE_O26_VSD_SHP_DCTP_CTRL_10_T                     shp_dctp_ctrl_10;	//0xCC9522C0
	PE_O26_VSD_SHP_DCTP_CTRL_11_T                     shp_dctp_ctrl_11;	//0xCC9522C4
	PE_O26_VSD_SHP_DCTP_CTRL_12_T                     shp_dctp_ctrl_12;	//0xCC9522C8
	PE_O26_VSD_SHP_DCTP_CTRL_13_T                     shp_dctp_ctrl_13;	//0xCC9522CC
	PE_O26_VSD_SHP_DCTP_CTRL_14_T                     shp_dctp_ctrl_14;	//0xCC9522D0
	PE_O26_VSD_SHP_DCTP_CTRL_15_T                     shp_dctp_ctrl_15;	//0xCC9522D4
	PE_O26_VSD_SHP_DCTP_CTRL_16_T                     shp_dctp_ctrl_16;	//0xCC9522D8
	PE_O26_VSD_SHP_DCTP_CTRL_17_T                     shp_dctp_ctrl_17;	//0xCC9522DC
	PE_O26_VSD_SHP_DCTP_CTRL_18_T                     shp_dctp_ctrl_18;	//0xCC9522E0
	PE_O26_VSD_SHP_DCTP_CTRL_19_T                     shp_dctp_ctrl_19;	//0xCC9522E4
	PE_O26_VSD_SHP_DCTP_CTRL_1A_T                     shp_dctp_ctrl_1a;	//0xCC9522E8
	PE_O26_VSD_SHP_DCTP_CTRL_1B_T                     shp_dctp_ctrl_1b;	//0xCC9522EC
	PE_O26_VSD_SHP_DCTP_CTRL_1C_T                     shp_dctp_ctrl_1c;	//0xCC9522F0
	PE_O26_VSD_SHP_DCTP_CTRL_1D_T                     shp_dctp_ctrl_1d;	//0xCC9522F4
	PE_O26_VSD_SHP_DCTP_CTRL_1E_T                     shp_dctp_ctrl_1e;	//0xCC9522F8
	PE_O26_VSD_SHP_DCTP_CTRL_1F_T                     shp_dctp_ctrl_1f;	//0xCC9522FC
	PE_O26_VSD_SHP_NNTG_CTRL_00_T                     shp_nntg_ctrl_00;	//0xCC952300
	PE_O26_VSD_SHP_NNTG_CTRL_01_C0_T               shp_nntg_ctrl_01_c0;	//0xCC952304
	PE_O26_VSD_SHP_NNTG_CTRL_02_C0_T               shp_nntg_ctrl_02_c0;	//0xCC952308
	PE_O26_VSD_SHP_NNTG_CTRL_03_C0_T               shp_nntg_ctrl_03_c0;	//0xCC95230C
	PE_O26_VSD_SHP_NNTG_CTRL_04_C0_T               shp_nntg_ctrl_04_c0;	//0xCC952310
	PE_O26_VSD_SHP_NNTG_CTRL_05_C0_T               shp_nntg_ctrl_05_c0;	//0xCC952314
	PE_O26_VSD_SHP_NNTG_CTRL_01_C1_T               shp_nntg_ctrl_01_c1;	//0xCC952318
	PE_O26_VSD_SHP_NNTG_CTRL_02_C1_T               shp_nntg_ctrl_02_c1;	//0xCC95231C
	PE_O26_VSD_SHP_NNTG_CTRL_03_C1_T               shp_nntg_ctrl_03_c1;	//0xCC952320
	PE_O26_VSD_SHP_NNTG_CTRL_04_C1_T               shp_nntg_ctrl_04_c1;	//0xCC952324
	PE_O26_VSD_SHP_NNTG_CTRL_05_C1_T               shp_nntg_ctrl_05_c1;	//0xCC952328
	PE_O26_VSD_SHP_NNTG_CTRL_06_T                     shp_nntg_ctrl_06;	//0xCC95232C
	PE_O26_VSD_SHP_NNTG_CTRL_07_T                     shp_nntg_ctrl_07;	//0xCC952330
	PE_O26_VSD_SHP_NNTG_CTRL_08_T                     shp_nntg_ctrl_08;	//0xCC952334
	PE_O26_VSD_SHP_NNTG_CTRL_09_T                     shp_nntg_ctrl_09;	//0xCC952338
	PE_O26_VSD_SHP_NNTG_CTRL_0A_T                     shp_nntg_ctrl_0a;	//0xCC95233C
	PE_O26_VSD_SHP_NNTG_CTRL_0B_T                     shp_nntg_ctrl_0b;	//0xCC952340
	PE_O26_VSD_SHP_NNTG_CTRL_0C_T                     shp_nntg_ctrl_0c;	//0xCC952344
	PE_O26_VSD_SHP_NNTG_CTRL_0D_T                     shp_nntg_ctrl_0d;	//0xCC952348
	PE_O26_VSD_SHP_NNTG_CTRL_0E_T                     shp_nntg_ctrl_0e;	//0xCC95234C
	PE_O26_VSD_SHP_NNTG_CTRL_0F_T                     shp_nntg_ctrl_0f;	//0xCC952350
	PE_O26_VSD_SHP_NNTG_CTRL_10_T                     shp_nntg_ctrl_10;	//0xCC952354
	UINT32                                                  reserved42;	//0xCC952358
	UINT32                                                  reserved43;	//0xCC95235C
	PE_O26_VSD_SHP_DP_SUM_CTRL_00_T                 shp_dp_sum_ctrl_00;	//0xCC952360
	PE_O26_VSD_SHP_DP_SUM_CTRL_01_T                 shp_dp_sum_ctrl_01;	//0xCC952364
	PE_O26_VSD_SHP_DP_SUM_CTRL_02_T                 shp_dp_sum_ctrl_02;	//0xCC952368
	PE_O26_VSD_SHP_DP_SUM_CTRL_03_T                 shp_dp_sum_ctrl_03;	//0xCC95236C
	PE_O26_VSD_SHP_DP_SUM_CTRL_04_T                 shp_dp_sum_ctrl_04;	//0xCC952370
	PE_O26_VSD_SHP_DP_SUM_CTRL_05_T                 shp_dp_sum_ctrl_05;	//0xCC952374
	PE_O26_VSD_SHP_DP_SUM_CTRL_06_T                 shp_dp_sum_ctrl_06;	//0xCC952378
	PE_O26_VSD_SHP_DP_SUM_CTRL_07_T                 shp_dp_sum_ctrl_07;	//0xCC95237C
	PE_O26_VSD_SHP_DP_SUM_CTRL_08_T                 shp_dp_sum_ctrl_08;	//0xCC952380
	PE_O26_VSD_SHP_DP_SUM_CTRL_09_T                 shp_dp_sum_ctrl_09;	//0xCC952384
	PE_O26_VSD_SHP_DP_SUM_CTRL_0A_T                 shp_dp_sum_ctrl_0a;	//0xCC952388
	UINT32                                                  reserved44;	//0xCC95238C
	PE_O26_VSD_SHP_PSP_CTRL_00_T                       shp_psp_ctrl_00;	//0xCC952390
	PE_O26_VSD_SHP_DP_SUM_CTRL_0B_T                 shp_dp_sum_ctrl_0b;	//0xCC952394
	PE_O26_VSD_SHP_DP_SUM_CTRL_0C_T                 shp_dp_sum_ctrl_0c;	//0xCC952398
	UINT32                                                  reserved45;	//0xCC95239C
	PE_O26_VSD_SHP_DP_WIN_CTRL_00_T                 shp_dp_win_ctrl_00;	//0xCC9523A0
	PE_O26_VSD_SHP_DP_WIN_CTRL_01_T                 shp_dp_win_ctrl_01;	//0xCC9523A4
	PE_O26_VSD_SHP_DP_WIN_CTRL_02_T                 shp_dp_win_ctrl_02;	//0xCC9523A8
	PE_O26_VSD_SHP_DP_WIN_CTRL_03_T                 shp_dp_win_ctrl_03;	//0xCC9523AC
	PE_O26_VSD_SHP_DP_WIN_CTRL_04_T                 shp_dp_win_ctrl_04;	//0xCC9523B0
	UINT32                                                  reserved46;	//0xCC9523B4
	UINT32                                                  reserved47;	//0xCC9523B8
	UINT32                                                  reserved48;	//0xCC9523BC
	PE_O26_VSD_SHP_FD_REGION_TEXT_00_T           shp_fd_region_text_00;	//0xCC9523C0
	PE_O26_VSD_SHP_FD_REGION_TEXT_01_T           shp_fd_region_text_01;	//0xCC9523C4
	PE_O26_VSD_SHP_FD_REGION_TEXT_02_T           shp_fd_region_text_02;	//0xCC9523C8
	PE_O26_VSD_SHP_FD_TMAP_TEMP_00_T               shp_fd_tmap_temp_00;	//0xCC9523CC
	PE_O26_VSD_SHP_FD_TMAP_TEMP_01_T               shp_fd_tmap_temp_01;	//0xCC9523D0
	PE_O26_VSD_SHP_FD_TMAP_TEMP_02_T               shp_fd_tmap_temp_02;	//0xCC9523D4
	PE_O26_VSD_SHP_FD_TMAP_TEMP_03_T               shp_fd_tmap_temp_03;	//0xCC9523D8
	PE_O26_VSD_SHP_FD_TMAP_TEMP_04_T               shp_fd_tmap_temp_04;	//0xCC9523DC
	PE_O26_VSD_SHP_FD_TMAP_TEMP_05_T               shp_fd_tmap_temp_05;	//0xCC9523E0
	PE_O26_VSD_SHP_FD_TMAP_TEMP_06_T               shp_fd_tmap_temp_06;	//0xCC9523E4
	PE_O26_VSD_SHP_FD_TMAP_TEMP_07_T               shp_fd_tmap_temp_07;	//0xCC9523E8
	PE_O26_VSD_SHP_FD_TMAP_TEMP_08_T               shp_fd_tmap_temp_08;	//0xCC9523EC
	PE_O26_VSD_SHP_FD_TMAP_TEMP_09_T               shp_fd_tmap_temp_09;	//0xCC9523F0
	PE_O26_VSD_SHP_FD_TMAP_TEMP_0A_T               shp_fd_tmap_temp_0a;	//0xCC9523F4
	PE_O26_VSD_SHP_FD_TMAP_TEMP_0B_T               shp_fd_tmap_temp_0b;	//0xCC9523F8
	PE_O26_VSD_SHP_FD_TMAP_TEMP_0C_T               shp_fd_tmap_temp_0c;	//0xCC9523FC
	PE_O26_VSD_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0xCC952400
	PE_O26_VSD_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0xCC952404
	PE_O26_VSD_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0xCC952408
	PE_O26_VSD_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0xCC95240C
	PE_O26_VSD_SHP_DJ_CTRL_04_T                         shp_dj_ctrl_04;	//0xCC952410
	PE_O26_VSD_SHP_DJ_CTRL_05_T                         shp_dj_ctrl_05;	//0xCC952414
	PE_O26_VSD_SHP_DJ_CTRL_06_T                         shp_dj_ctrl_06;	//0xCC952418
	PE_O26_VSD_SHP_DJ_CTRL_07_T                         shp_dj_ctrl_07;	//0xCC95241C
	PE_O26_VSD_SHP_DJ_CTRL_08_T                         shp_dj_ctrl_08;	//0xCC952420
	PE_O26_VSD_SHP_DJ_CTRL_09_T                         shp_dj_ctrl_09;	//0xCC952424
	PE_O26_VSD_SHP_DJ_CTRL_0A_T                         shp_dj_ctrl_0a;	//0xCC952428
	PE_O26_VSD_SHP_DJ_CTRL_0B_T                         shp_dj_ctrl_0b;	//0xCC95242C
	PE_O26_VSD_SHP_DJ_CTRL_0C_T                         shp_dj_ctrl_0c;	//0xCC952430
	PE_O26_VSD_SHP_DJ_CTRL_0D_T                         shp_dj_ctrl_0d;	//0xCC952434
	PE_O26_VSD_SHP_DJ_CTRL_0E_T                         shp_dj_ctrl_0e;	//0xCC952438
	PE_O26_VSD_SHP_DJ_CTRL_0F_T                         shp_dj_ctrl_0f;	//0xCC95243C
	PE_O26_VSD_SHP_DJ_CTRL_10_T                         shp_dj_ctrl_10;	//0xCC952440
	PE_O26_VSD_SHP_DJ_CTRL_11_T                         shp_dj_ctrl_11;	//0xCC952444
	PE_O26_VSD_SHP_DJ_CTRL_12_T                         shp_dj_ctrl_12;	//0xCC952448
	PE_O26_VSD_SHP_DJ_CTRL_13_T                         shp_dj_ctrl_13;	//0xCC95244C
	PE_O26_VSD_SHP_DJ_CTRL_14_T                         shp_dj_ctrl_14;	//0xCC952450
	PE_O26_VSD_SHP_DJ_CTRL_15_T                         shp_dj_ctrl_15;	//0xCC952454
	PE_O26_VSD_SHP_DJ_CTRL_16_T                         shp_dj_ctrl_16;	//0xCC952458
	PE_O26_VSD_SHP_DJ_CTRL_17_T                         shp_dj_ctrl_17;	//0xCC95245C
	PE_O26_VSD_SHP_DJ_CTRL_18_T                         shp_dj_ctrl_18;	//0xCC952460
	PE_O26_VSD_SHP_DJ_CTRL_19_T                         shp_dj_ctrl_19;	//0xCC952464
	PE_O26_VSD_SHP_DJ_CTRL_1A_T                         shp_dj_ctrl_1a;	//0xCC952468
	PE_O26_VSD_SHP_DJ_CTRL_1B_T                         shp_dj_ctrl_1b;	//0xCC95246C
	PE_O26_VSD_SHP_DJ_CTRL_1C_T                         shp_dj_ctrl_1c;	//0xCC952470
	PE_O26_VSD_SHP_DJ_CTRL_1D_T                         shp_dj_ctrl_1d;	//0xCC952474
	PE_O26_VSD_SHP_DJ_CTRL_1E_T                         shp_dj_ctrl_1e;	//0xCC952478
	PE_O26_VSD_SHP_DJ_CTRL_1F_T                         shp_dj_ctrl_1f;	//0xCC95247C
	PE_O26_VSD_SHP_DJ_CTRL_20_T                         shp_dj_ctrl_20;	//0xCC952480
	UINT32                                                  reserved49;	//0xCC952484
	UINT32                                                  reserved50;	//0xCC952488
	UINT32                                                  reserved51;	//0xCC95248C
	PE_O26_VSD_SHP_DB_CTRL_00_T                         shp_db_ctrl_00;	//0xCC952490
	PE_O26_VSD_SHP_DB_CTRL_01_T                         shp_db_ctrl_01;	//0xCC952494
	UINT32                                                  reserved52;	//0xCC952498
	UINT32                                                  reserved53;	//0xCC95249C
	PE_O26_VSD_SHP_DJ_WIN_CTRL_00_T                 shp_dj_win_ctrl_00;	//0xCC9524A0
	PE_O26_VSD_SHP_DJ_WIN_CTRL_01_T                 shp_dj_win_ctrl_01;	//0xCC9524A4
	PE_O26_VSD_SHP_DJ_WIN_CTRL_02_T                 shp_dj_win_ctrl_02;	//0xCC9524A8
	PE_O26_VSD_SHP_DJ_WIN_CTRL_03_T                 shp_dj_win_ctrl_03;	//0xCC9524AC
	PE_O26_VSD_SHP_DJ_WIN_CTRL_04_T                 shp_dj_win_ctrl_04;	//0xCC9524B0
	UINT32                                                  reserved54;	//0xCC9524B4
	UINT32                                                  reserved55;	//0xCC9524B8
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_00_T     shp_dj_text_gain_ctrl_00;	//0xCC9524BC
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_01_T     shp_dj_text_gain_ctrl_01;	//0xCC9524C0
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_02_T     shp_dj_text_gain_ctrl_02;	//0xCC9524C4
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_03_T     shp_dj_text_gain_ctrl_03;	//0xCC9524C8
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_04_T     shp_dj_text_gain_ctrl_04;	//0xCC9524CC
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_05_T     shp_dj_text_gain_ctrl_05;	//0xCC9524D0
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_06_T     shp_dj_text_gain_ctrl_06;	//0xCC9524D4
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_07_T     shp_dj_text_gain_ctrl_07;	//0xCC9524D8
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_08_T     shp_dj_text_gain_ctrl_08;	//0xCC9524DC
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_09_T     shp_dj_text_gain_ctrl_09;	//0xCC9524E0
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_10_T     shp_dj_text_gain_ctrl_10;	//0xCC9524E4
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_11_T     shp_dj_text_gain_ctrl_11;	//0xCC9524E8
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_12_T     shp_dj_text_gain_ctrl_12;	//0xCC9524EC
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_13_T     shp_dj_text_gain_ctrl_13;	//0xCC9524F0
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_14_T     shp_dj_text_gain_ctrl_14;	//0xCC9524F4
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_15_T     shp_dj_text_gain_ctrl_15;	//0xCC9524F8
	PE_O26_VSD_SHP_DJ_TEXT_GAIN_CTRL_16_T     shp_dj_text_gain_ctrl_16;	//0xCC9524FC
	PE_O26_VSD_SHP_CHROMA_CTRL_00_T                 shp_chroma_ctrl_00;	//0xCC952500
	PE_O26_VSD_SHP_CHROMA_CTRL_01_T                 shp_chroma_ctrl_01;	//0xCC952504
	PE_O26_VSD_SHP_CHROMA_CTRL_02_T                 shp_chroma_ctrl_02;	//0xCC952508
	PE_O26_VSD_SHP_CHROMA_CTRL_03_T                 shp_chroma_ctrl_03;	//0xCC95250C
	PE_O26_VSD_SHP_CHROMA_CTRL_04_T                 shp_chroma_ctrl_04;	//0xCC952510
	PE_O26_VSD_SHP_CHROMA_CTRL_05_T                 shp_chroma_ctrl_05;	//0xCC952514
	PE_O26_VSD_SHP_CHROMA_CTRL_06_T                 shp_chroma_ctrl_06;	//0xCC952518
	PE_O26_VSD_SHP_CHROMA_CTRL_07_T                 shp_chroma_ctrl_07;	//0xCC95251C
	PE_O26_VSD_SHP_CHROMA_CTRL_08_T                 shp_chroma_ctrl_08;	//0xCC952520
	PE_O26_VSD_SHP_CHROMA_CTRL_09_T                 shp_chroma_ctrl_09;	//0xCC952524
	PE_O26_VSD_SHP_CHROMA_CTRL_0A_T                 shp_chroma_ctrl_0a;	//0xCC952528
	PE_O26_VSD_SHP_CHROMA_CTRL_0B_T                 shp_chroma_ctrl_0b;	//0xCC95252C
	PE_O26_VSD_SHP_CHROMA_CTRL_0C_T                 shp_chroma_ctrl_0c;	//0xCC952530
	PE_O26_VSD_SHP_CHROMA_CTRL_0D_T                 shp_chroma_ctrl_0d;	//0xCC952534
	PE_O26_VSD_SHP_CHROMA_CTRL_0E_T                 shp_chroma_ctrl_0e;	//0xCC952538
	UINT32                                                  reserved56;	//0xCC95253C
	UINT32                                                  reserved57;	//0xCC952540
	UINT32                                                  reserved58;	//0xCC952544
	UINT32                                                  reserved59;	//0xCC952548
	UINT32                                                  reserved60;	//0xCC95254C
	PE_O26_VSD_SHP_CTI_CTRL_00_T                       shp_cti_ctrl_00;	//0xCC952550
	PE_O26_VSD_SHP_CTI_CTRL_01_T                       shp_cti_ctrl_01;	//0xCC952554
	PE_O26_VSD_SHP_CTI_CTRL_02_T                       shp_cti_ctrl_02;	//0xCC952558
	UINT32                                                  reserved61;	//0xCC95255C
	PE_O26_VSD_SHP_FRC_FLICK_CTRL_00_T           shp_frc_flick_ctrl_00;	//0xCC952560
	PE_O26_VSD_SHP_FRC_FLICK_CTRL_01_T           shp_frc_flick_ctrl_01;	//0xCC952564
	PE_O26_VSD_SHP_FRC_FLICK_CTRL_02_T           shp_frc_flick_ctrl_02;	//0xCC952568
	PE_O26_VSD_SHP_FRC_FLICK_CTRL_03_T           shp_frc_flick_ctrl_03;	//0xCC95256C
	PE_O26_VSD_SHP_TEMPORAL_MAP_00_T               shp_temporal_map_00;	//0xCC952570
	PE_O26_VSD_SHP_TEMPORAL_MAP_01_T               shp_temporal_map_01;	//0xCC952574
	UINT32                                                  reserved62;	//0xCC952578
	UINT32                                                  reserved63;	//0xCC95257C
	UINT32                                                  reserved64;	//0xCC952580
	UINT32                                                  reserved65;	//0xCC952584
	UINT32                                                  reserved66;	//0xCC952588
	UINT32                                                  reserved67;	//0xCC95258C
	UINT32                                                  reserved68;	//0xCC952590
	UINT32                                                  reserved69;	//0xCC952594
	UINT32                                                  reserved70;	//0xCC952598
	UINT32                                                  reserved71;	//0xCC95259C
	PE_O26_VSD_SHP_FRC_WIN_CTRL_00_T               shp_frc_win_ctrl_00;	//0xCC9525A0
	PE_O26_VSD_SHP_FRC_WIN_CTRL_01_T               shp_frc_win_ctrl_01;	//0xCC9525A4
	PE_O26_VSD_SHP_FRC_WIN_CTRL_02_T               shp_frc_win_ctrl_02;	//0xCC9525A8
	PE_O26_VSD_SHP_FRC_WIN_CTRL_03_T               shp_frc_win_ctrl_03;	//0xCC9525AC
	PE_O26_VSD_SHP_FRC_WIN_CTRL_04_T               shp_frc_win_ctrl_04;	//0xCC9525B0
	UINT32                                                  reserved72;	//0xCC9525B4
	UINT32                                                  reserved73;	//0xCC9525B8
	UINT32                                                  reserved74;	//0xCC9525BC
	UINT32                                                  reserved75;	//0xCC9525C0
	UINT32                                                  reserved76;	//0xCC9525C4
	UINT32                                                  reserved77;	//0xCC9525C8
	UINT32                                                  reserved78;	//0xCC9525CC
	UINT32                                                  reserved79;	//0xCC9525D0
	UINT32                                                  reserved80;	//0xCC9525D4
	UINT32                                                  reserved81;	//0xCC9525D8
	UINT32                                                  reserved82;	//0xCC9525DC
	UINT32                                                  reserved83;	//0xCC9525E0
	UINT32                                                  reserved84;	//0xCC9525E4
	UINT32                                                  reserved85;	//0xCC9525E8
	UINT32                                                  reserved86;	//0xCC9525EC
	UINT32                                                  reserved87;	//0xCC9525F0
	UINT32                                                  reserved88;	//0xCC9525F4
	UINT32                                                  reserved89;	//0xCC9525F8
	UINT32                                                  reserved90;	//0xCC9525FC
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_00_T       shp_motion_gain_ctrl_00;	//0xCC952600
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_01_T       shp_motion_gain_ctrl_01;	//0xCC952604
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_02_T       shp_motion_gain_ctrl_02;	//0xCC952608
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_03_T       shp_motion_gain_ctrl_03;	//0xCC95260C
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_04_T       shp_motion_gain_ctrl_04;	//0xCC952610
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_05_T       shp_motion_gain_ctrl_05;	//0xCC952614
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_06_T       shp_motion_gain_ctrl_06;	//0xCC952618
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_07_T       shp_motion_gain_ctrl_07;	//0xCC95261C
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_08_T       shp_motion_gain_ctrl_08;	//0xCC952620
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_09_T       shp_motion_gain_ctrl_09;	//0xCC952624
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0A_T       shp_motion_gain_ctrl_0a;	//0xCC952628
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0B_T       shp_motion_gain_ctrl_0b;	//0xCC95262C
	PE_O26_VSD_SHP_MOTION_GAIN_CTRL_0C_T       shp_motion_gain_ctrl_0c;	//0xCC952630
	UINT32                                                  reserved91;	//0xCC952634
	UINT32                                                  reserved92;	//0xCC952638
	UINT32                                                  reserved93;	//0xCC95263C
	PE_O26_VSD_SHP_MOTION_PROT_CTRL_00_T       shp_motion_prot_ctrl_00;	//0xCC952640
	PE_O26_VSD_SHP_MOTION_PROT_CTRL_01_T       shp_motion_prot_ctrl_01;	//0xCC952644
	PE_O26_VSD_SHP_MOTION_PROT_CTRL_02_T       shp_motion_prot_ctrl_02;	//0xCC952648
	PE_O26_VSD_SHP_MOTION_PROT_CTRL_03_T       shp_motion_prot_ctrl_03;	//0xCC95264C
	PE_O26_VSD_SHP_MOTION_PROT_CTRL_04_T       shp_motion_prot_ctrl_04;	//0xCC952650
	UINT32                                                  reserved94;	//0xCC952654
	UINT32                                                  reserved95;	//0xCC952658
	UINT32                                                  reserved96;	//0xCC95265C
	UINT32                                                  reserved97;	//0xCC952660
	UINT32                                                  reserved98;	//0xCC952664
	UINT32                                                  reserved99;	//0xCC952668
	UINT32                                                 reserved100;	//0xCC95266C
	PE_O26_VSD_SHP_MOT_WIN_CTRL_00_T               shp_mot_win_ctrl_00;	//0xCC952670
	PE_O26_VSD_SHP_MOT_WIN_CTRL_01_T               shp_mot_win_ctrl_01;	//0xCC952674
	PE_O26_VSD_SHP_MOT_WIN_CTRL_02_T               shp_mot_win_ctrl_02;	//0xCC952678
	PE_O26_VSD_SHP_MOT_WIN_CTRL_03_T               shp_mot_win_ctrl_03;	//0xCC95267C
	PE_O26_VSD_SHP_MOT_WIN_CTRL_04_T               shp_mot_win_ctrl_04;	//0xCC952680
	UINT32                                                 reserved101;	//0xCC952684
	UINT32                                                 reserved102;	//0xCC952688
	UINT32                                                 reserved103;	//0xCC95268C
	PE_O26_VSD_SHP_OBJ_CTRL_00_T                       shp_obj_ctrl_00;	//0xCC952690
	PE_O26_VSD_SHP_OBJ_CTRL_01_T                       shp_obj_ctrl_01;	//0xCC952694
	PE_O26_VSD_SHP_OBJ_CTRL_02_T                       shp_obj_ctrl_02;	//0xCC952698
	PE_O26_VSD_SHP_OBJ_CTRL_03_T                       shp_obj_ctrl_03;	//0xCC95269C
	PE_O26_VSD_SHP_OBJ_CTRL_04_T                       shp_obj_ctrl_04;	//0xCC9526A0
	PE_O26_VSD_SHP_OBJ_CTRL_05_T                       shp_obj_ctrl_05;	//0xCC9526A4
	PE_O26_VSD_SHP_OBJ_CTRL_06_T                       shp_obj_ctrl_06;	//0xCC9526A8
	PE_O26_VSD_SHP_OBJ_CTRL_07_T                       shp_obj_ctrl_07;	//0xCC9526AC
	PE_O26_VSD_SHP_OBJ_CTRL_08_T                       shp_obj_ctrl_08;	//0xCC9526B0
	PE_O26_VSD_SHP_OBJ_CTRL_09_T                       shp_obj_ctrl_09;	//0xCC9526B4
	PE_O26_VSD_SHP_OBJ_CTRL_0A_T                       shp_obj_ctrl_0a;	//0xCC9526B8
	PE_O26_VSD_SHP_OBJ_CTRL_0B_T                       shp_obj_ctrl_0b;	//0xCC9526BC
	PE_O26_VSD_SHP_OBJ_CTRL_0C_T                       shp_obj_ctrl_0c;	//0xCC9526C0
	UINT32                                                 reserved104;	//0xCC9526C4
	UINT32                                                 reserved105;	//0xCC9526C8
	UINT32                                                 reserved106;	//0xCC9526CC
	PE_O26_VSD_SHP_FD_TEXT_CTRL_00_T               shp_fd_text_ctrl_00;	//0xCC9526D0
	PE_O26_VSD_SHP_FD_TEXT_CTRL_01_T               shp_fd_text_ctrl_01;	//0xCC9526D4
	PE_O26_VSD_SHP_FD_TEXT_CTRL_02_T               shp_fd_text_ctrl_02;	//0xCC9526D8
	PE_O26_VSD_SHP_FD_TEXT_CTRL_03_T               shp_fd_text_ctrl_03;	//0xCC9526DC
	PE_O26_VSD_SHP_FD_TEXT_CTRL_04_T               shp_fd_text_ctrl_04;	//0xCC9526E0
	PE_O26_VSD_SHP_FD_TEXT_CTRL_05_T               shp_fd_text_ctrl_05;	//0xCC9526E4
	PE_O26_VSD_SHP_FD_TEXT_CTRL_06_T               shp_fd_text_ctrl_06;	//0xCC9526E8
	PE_O26_VSD_SHP_FD_TEXT_CTRL_07_T               shp_fd_text_ctrl_07;	//0xCC9526EC
	PE_O26_VSD_SHP_FD_TEXT_CTRL_08_T               shp_fd_text_ctrl_08;	//0xCC9526F0
	PE_O26_VSD_SHP_FD_TEXT_TEMP_00_T               shp_fd_text_temp_00;	//0xCC9526F4
	PE_O26_VSD_SHP_FD_TEXT_TEMP_01_T               shp_fd_text_temp_01;	//0xCC9526F8
	PE_O26_VSD_SHP_FD_TEXT_TEMP_02_T               shp_fd_text_temp_02;	//0xCC9526FC
	PE_O26_VSD_SHP_FD_TEXT_TEMP_03_T               shp_fd_text_temp_03;	//0xCC952700
	PE_O26_VSD_SHP_FD_TEXT_TEMP_04_T               shp_fd_text_temp_04;	//0xCC952704
	PE_O26_VSD_SHP_FD_TEXT_TEMP_05_T               shp_fd_text_temp_05;	//0xCC952708
	PE_O26_VSD_SHP_FD_TEXT_TEMP_06_T               shp_fd_text_temp_06;	//0xCC95270C
	PE_O26_VSD_SHP_FD_TEXT_TEMP_07_T               shp_fd_text_temp_07;	//0xCC952710
	PE_O26_VSD_SHP_FD_TEXT_TEMP_08_T               shp_fd_text_temp_08;	//0xCC952714
	PE_O26_VSD_SHP_FD_TEXT_TEMP_09_T               shp_fd_text_temp_09;	//0xCC952718
	PE_O26_VSD_SHP_FD_TEXT_TEMP_0A_T               shp_fd_text_temp_0a;	//0xCC95271C
	PE_O26_VSD_SHP_FD_TEXT_TEMP_0B_T               shp_fd_text_temp_0b;	//0xCC952720
	PE_O26_VSD_SHP_FD_TEXT_TEMP_0C_T               shp_fd_text_temp_0c;	//0xCC952724
	UINT32                                                 reserved107;	//0xCC952728
	UINT32                                                 reserved108;	//0xCC95272C
	PE_O26_VSD_SHP_CORE_TEXT_STAT_00_T           shp_core_text_stat_00;	//0xCC952730
	PE_O26_VSD_SHP_CORE_TEXT_STAT_01_T           shp_core_text_stat_01;	//0xCC952734
	PE_O26_VSD_SHP_CORE_TEXT_STAT_02_T           shp_core_text_stat_02;	//0xCC952738
	PE_O26_VSD_SHP_CORE_TEXT_STAT_03_T           shp_core_text_stat_03;	//0xCC95273C
	PE_O26_VSD_SHP_CORE_TEXT_STAT_04_T           shp_core_text_stat_04;	//0xCC952740
	PE_O26_VSD_SHP_CORE_TEXT_STAT_05_T           shp_core_text_stat_05;	//0xCC952744
	PE_O26_VSD_SHP_CORE_TEXT_STAT_06_T           shp_core_text_stat_06;	//0xCC952748
	PE_O26_VSD_SHP_CORE_TEXT_STAT_07_T           shp_core_text_stat_07;	//0xCC95274C
	PE_O26_VSD_SHP_TEXT_BLEND_00_T                   shp_text_blend_00;	//0xCC952750
	PE_O26_VSD_SHP_TEXT_BLEND_01_T                   shp_text_blend_01;	//0xCC952754
	PE_O26_VSD_SHP_TEXT_BLEND_02_T                   shp_text_blend_02;	//0xCC952758
	PE_O26_VSD_SHP_TEXT_BLEND_03_T                   shp_text_blend_03;	//0xCC95275C
	PE_O26_VSD_SHP_TEXT_BLEND_04_T                   shp_text_blend_04;	//0xCC952760
	PE_O26_VSD_SHP_TEXT_BLEND_05_T                   shp_text_blend_05;	//0xCC952764
	PE_O26_VSD_SHP_TEXT_BLEND_06_T                   shp_text_blend_06;	//0xCC952768
	PE_O26_VSD_SHP_TEXT_BLEND_07_T                   shp_text_blend_07;	//0xCC95276C
	PE_O26_VSD_SHP_TEXT_BLEND_08_T                   shp_text_blend_08;	//0xCC952770
	PE_O26_VSD_SHP_TEXT_BLEND_09_T                   shp_text_blend_09;	//0xCC952774
	PE_O26_VSD_SHP_TEXT_BLEND_0A_T                   shp_text_blend_0a;	//0xCC952778
	PE_O26_VSD_SHP_TEXT_BLEND_0B_T                   shp_text_blend_0b;	//0xCC95277C
	PE_O26_VSD_SHP_TEXT_BLEND_0C_T                   shp_text_blend_0c;	//0xCC952780
	PE_O26_VSD_SHP_DP_SUM_NT_CTRL_01_T           shp_dp_sum_nt_ctrl_01;	//0xCC952784
	PE_O26_VSD_SHP_DP_SUM_NT_CTRL_02_T           shp_dp_sum_nt_ctrl_02;	//0xCC952788
	PE_O26_VSD_SHP_DP_SUM_NT_CTRL_09_T           shp_dp_sum_nt_ctrl_09;	//0xCC95278C
	PE_O26_VSD_SHP_DP_SUM_NT_CTRL_0A_T           shp_dp_sum_nt_ctrl_0a;	//0xCC952790
	UINT32                                                 reserved109;	//0xCC952794
	UINT32                                                 reserved110;	//0xCC952798
	UINT32                                                 reserved111;	//0xCC95279C
	PE_O26_VSD_SHP_CORE_STAT_00_T                     shp_core_stat_00;	//0xCC9527A0
	PE_O26_VSD_SHP_CORE_STAT_01_T                     shp_core_stat_01;	//0xCC9527A4
	PE_O26_VSD_SHP_CORE_STAT_02_T                     shp_core_stat_02;	//0xCC9527A8
	PE_O26_VSD_SHP_CORE_STAT_03_T                     shp_core_stat_03;	//0xCC9527AC
	PE_O26_VSD_SHP_CORE_STAT_04_T                     shp_core_stat_04;	//0xCC9527B0
	PE_O26_VSD_SHP_CORE_STAT_05_T                     shp_core_stat_05;	//0xCC9527B4
	UINT32                                                 reserved112;	//0xCC9527B8
	UINT32                                                 reserved113;	//0xCC9527BC
	UINT32                                                 reserved114;	//0xCC9527C0
	UINT32                                                 reserved115;	//0xCC9527C4
	UINT32                                                 reserved116;	//0xCC9527C8
	UINT32                                                 reserved117;	//0xCC9527CC
	PE_O26_VSD_SHP_CORE_FD_STAT_00_T               shp_core_fd_stat_00;	//0xCC9527D0
	PE_O26_VSD_SHP_CORE_FD_STAT_01_T               shp_core_fd_stat_01;	//0xCC9527D4
	PE_O26_VSD_SHP_CORE_FD_STAT_02_T               shp_core_fd_stat_02;	//0xCC9527D8
	PE_O26_VSD_SHP_CORE_FD_STAT_03_T               shp_core_fd_stat_03;	//0xCC9527DC
	PE_O26_VSD_SHP_MOTION_GAIN_STAT_00_T       shp_motion_gain_stat_00;	//0xCC9527E0
	PE_O26_VSD_SHP_MOTION_GAIN_STAT_01_T       shp_motion_gain_stat_01;	//0xCC9527E4
	PE_O26_VSD_SHP_CORE_EDGE_STAT_00_T           shp_core_edge_stat_00;	//0xCC9527E8
	PE_O26_VSD_SHP_CORE_EDGE_STAT_01_T           shp_core_edge_stat_01;	//0xCC9527EC
	PE_O26_VSD_SHP_CORE_EDGE_STAT_02_T           shp_core_edge_stat_02;	//0xCC9527F0
	PE_O26_VSD_SHP_CORE_EDGE_STAT_03_T           shp_core_edge_stat_03;	//0xCC9527F4
	PE_O26_VSD_SHP_CORE_EDGE_STAT_04_T           shp_core_edge_stat_04;	//0xCC9527F8
	PE_O26_VSD_SHP_CORE_EDGE_STAT_05_T           shp_core_edge_stat_05;	//0xCC9527FC
	PE_O26_VSD_SHP_CORE_TMAP_STAT_00_T           shp_core_tmap_stat_00;	//0xCC952800
	PE_O26_VSD_SHP_CORE_TMAP_STAT_01_T           shp_core_tmap_stat_01;	//0xCC952804
	PE_O26_VSD_SHP_CORE_TMAP_STAT_02_T           shp_core_tmap_stat_02;	//0xCC952808
	PE_O26_VSD_SHP_CORE_TMAP_STAT_03_T           shp_core_tmap_stat_03;	//0xCC95280C
	PE_O26_VSD_SHP_CORE_TMAP_STAT_04_T           shp_core_tmap_stat_04;	//0xCC952810
	PE_O26_VSD_SHP_CORE_TMAP_STAT_05_T           shp_core_tmap_stat_05;	//0xCC952814
	PE_O26_VSD_SHP_CORE_TMAP_STAT_06_T           shp_core_tmap_stat_06;	//0xCC952818
	PE_O26_VSD_SHP_CORE_TMAP_STAT_07_T           shp_core_tmap_stat_07;	//0xCC95281C
	PE_O26_VSD_SHP_FACE_WIN_CTRL_00_T             shp_face_win_ctrl_00;	//0xCC952820
	PE_O26_VSD_SHP_FACE_WIN_CTRL_01_T             shp_face_win_ctrl_01;	//0xCC952824
	PE_O26_VSD_SHP_FACE_WIN_CTRL_02_T             shp_face_win_ctrl_02;	//0xCC952828
	PE_O26_VSD_SHP_FACE_WIN_CTRL_03_T             shp_face_win_ctrl_03;	//0xCC95282C
	PE_O26_VSD_SHP_FACE_WIN_CTRL_04_T             shp_face_win_ctrl_04;	//0xCC952830
	PE_O26_VSD_SHP_FACE_WIN_CTRL_05_T             shp_face_win_ctrl_05;	//0xCC952834
	PE_O26_VSD_SHP_BODY_WIN_CTRL_00_T             shp_body_win_ctrl_00;	//0xCC952838
	PE_O26_VSD_SHP_BODY_WIN_CTRL_01_T             shp_body_win_ctrl_01;	//0xCC95283C
	PE_O26_VSD_SHP_BODY_WIN_CTRL_02_T             shp_body_win_ctrl_02;	//0xCC952840
	PE_O26_VSD_SHP_BODY_WIN_CTRL_03_T             shp_body_win_ctrl_03;	//0xCC952844
	PE_O26_VSD_SHP_BODY_WIN_CTRL_04_T             shp_body_win_ctrl_04;	//0xCC952848
	PE_O26_VSD_SHP_BODY_WIN_CTRL_05_T             shp_body_win_ctrl_05;	//0xCC95284C
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_00_T         shp_luma_blend_ctrl_00;	//0xCC952850
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_01_T         shp_luma_blend_ctrl_01;	//0xCC952854
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_02_T         shp_luma_blend_ctrl_02;	//0xCC952858
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_03_T         shp_luma_blend_ctrl_03;	//0xCC95285C
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_04_T         shp_luma_blend_ctrl_04;	//0xCC952860
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_05_T         shp_luma_blend_ctrl_05;	//0xCC952864
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_06_T         shp_luma_blend_ctrl_06;	//0xCC952868
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_07_T         shp_luma_blend_ctrl_07;	//0xCC95286C
	PE_O26_VSD_SHP_LUMA_BLEND_CTRL_08_T         shp_luma_blend_ctrl_08;	//0xCC952870
	PE_O26_VSD_SHP_SMTH_MMD_CTRL_00_T             shp_smth_mmd_ctrl_00;	//0xCC952874
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_00_T           shp_smth_gain_ctrl_00;	//0xCC952878
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_01_T           shp_smth_gain_ctrl_01;	//0xCC95287C
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_02_T           shp_smth_gain_ctrl_02;	//0xCC952880
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_03_T           shp_smth_gain_ctrl_03;	//0xCC952884
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_04_T           shp_smth_gain_ctrl_04;	//0xCC952888
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_05_T           shp_smth_gain_ctrl_05;	//0xCC95288C
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_06_T           shp_smth_gain_ctrl_06;	//0xCC952890
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_07_T           shp_smth_gain_ctrl_07;	//0xCC952894
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_08_T           shp_smth_gain_ctrl_08;	//0xCC952898
	PE_O26_VSD_SHP_SMTH_GAIN_CTRL_09_T           shp_smth_gain_ctrl_09;	//0xCC95289C
	PE_O26_VSD_SHP_SMTH_CON_CTRL_00_T             shp_smth_con_ctrl_00;	//0xCC9528A0
	UINT32                                                 reserved118;	//0xCC9528A4
	UINT32                                                 reserved119;	//0xCC9528A8
	UINT32                                                 reserved120;	//0xCC9528AC
	PE_O26_VSD_SHP_CA_CTRL_00_T                         shp_ca_ctrl_00;	//0xCC9528B0
	PE_O26_VSD_SHP_CA_CTRL_01_T                         shp_ca_ctrl_01;	//0xCC9528B4
	PE_O26_VSD_SHP_CA_CTRL_02_T                         shp_ca_ctrl_02;	//0xCC9528B8
	PE_O26_VSD_SHP_CA_CTRL_03_T                         shp_ca_ctrl_03;	//0xCC9528BC
	PE_O26_VSD_SHP_CA_CTRL_04_T                         shp_ca_ctrl_04;	//0xCC9528C0
	PE_O26_VSD_SHP_CA_CTRL_05_T                         shp_ca_ctrl_05;	//0xCC9528C4
	PE_O26_VSD_SHP_CA_CTRL_06_T                         shp_ca_ctrl_06;	//0xCC9528C8
	PE_O26_VSD_SHP_CA_CTRL_07_T                         shp_ca_ctrl_07;	//0xCC9528CC
	PE_O26_VSD_SHP_CA_CTRL_08_T                         shp_ca_ctrl_08;	//0xCC9528D0
	PE_O26_VSD_SHP_CA_CTRL_09_T                         shp_ca_ctrl_09;	//0xCC9528D4
	PE_O26_VSD_SHP_CA_CTRL_0A_T                         shp_ca_ctrl_0a;	//0xCC9528D8
	PE_O26_VSD_SHP_CA_CTRL_0B_T                         shp_ca_ctrl_0b;	//0xCC9528DC
	PE_O26_VSD_SHP_CA_CTRL_0C_T                         shp_ca_ctrl_0c;	//0xCC9528E0
	UINT32                                                 reserved121;	//0xCC9528E4
	UINT32                                                 reserved122;	//0xCC9528E8
	UINT32                                                 reserved123;	//0xCC9528EC
	PE_O26_VSD_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xCC9528F0
	PE_O26_VSD_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xCC9528F4
	PE_O26_VSD_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xCC9528F8
	PE_O26_VSD_SHP_FSW_CTRL_03_T                       shp_fsw_ctrl_03;	//0xCC9528FC
}PE_VSD_SHP_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950500 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,NA,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,NA,0x870) //vertical resolution   2160
	UINT32 resvd1                           :2;
	UINT32 reg_psp_detour_en                :1;	//(31:31,NA,0x0) //0 : obc enable	1 : obc_detour(obc : no dleay value 0, video : no delay in->bg)
	};
}PE_O26_OBC_BODY_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950504 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,NA,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,NA,0x10) //Block size       16
	UINT32 resvd1                           :18;
	};
}PE_O26_OBC_BODY_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950508 RW 0x00000000
	UINT32 resvd0                           :1;
	UINT32 reg_psp_en                       :1;	//(1:1,NA,0x00) //1 : obc enable(obc : delay obc_res, video : delay in->out)	0 : obc_bypass(obc : delay value 0, video : delay in->out)
	UINT32 resvd1                           :6;
	UINT32 reg_psp_body_blur_en             :1;	//(8:8,NA,0x00) //0: disable , 1: enable
	UINT32 reg_psp_sam_blur_en              :1;	//(9:9,NA,0x00) //0: disable , 1: enable
	UINT32 reg_psp_sam_8bit_en              :1;	//(10:10,NA,0x00) //0: 6bit , 1: 8 bit
	UINT32 resvd2                           :21;
	};
}PE_O26_OBC_BODY_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95050C RW 0x3F3F0000
	UINT32 y0_point                         :8;	//(7:0,NA,0x00) //control point of Y0
	UINT32 x0_point                         :8;	//(15:8,NA,0x00) //control point of X0
	UINT32 y1_point                         :8;	//(23:16,NA,0x3F) //control point of Y1
	UINT32 x1_point                         :8;	//(31:24,NA,0x3F) //control point of X1
	};
}PE_O26_OBC_BODY_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950510 RW 0x3F3F3F3F
	UINT32 y2_point                         :8;	//(7:0,NA,0x3F) //control point of Y2
	UINT32 x2_point                         :8;	//(15:8,NA,0x3F) //control point of X2
	UINT32 y3_point                         :8;	//(23:16,NA,0x3F) //control point of Y3
	UINT32 x3_point                         :8;	//(31:24,NA,0x3F) //control point of X3
	};
}PE_O26_OBC_BODY_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950514 RW 0x008700F0
	UINT32 reg_blk_wid                      :9;	//(8:0,NA,0xF0) //Number of hblock 240
	UINT32 resvd0                           :7;
	UINT32 reg_blk_hei                      :9;	//(24:16,NA,0x87) //Number of vblock 135
	UINT32 resvd1                           :7;
	};
}PE_O26_OBC_BODY_PSP_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950518 RW 0x00000000
	UINT32 reg_comp_img_wid                 :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_img_hei                 :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_en                      :1;	//(31:31,NA,0x0) //Composition enable
	};
}PE_O26_OBC_BODY_PSP_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95051C RW 0x00000000
	UINT32 reg_comp_win_x0                  :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y0                  :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950520 RW 0x00000000
	UINT32 reg_comp_win_x1                  :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y1                  :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950524 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0x0) //ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0x0) //ROI mask pixel value (Y)
	UINT32 reg_comp_value                   :8;	//(23:16,NA,0x0) //Composition pixel value (Y)
	UINT32 reg_comp_3x3_blur_value          :8;	//(31:24,NA,0x0) //Composition pixel value (Y) value * 4
	};
}PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950528 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :13;	//(12:0,NA,0x0) //ROI mask window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y0              :13;	//(28:16,NA,0x0) //ROI mask window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95052C RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :13;	//(12:0,NA,0x0) //ROI mask window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y1              :13;	//(28:16,NA,0x0) //ROI mask window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950530 RW 0x000E0E0E
	UINT32 reg_3x3_wgt_u1_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_u1_01                :8;	//(15:8,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_u1_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :7;
	UINT32 reg_3x3_wgt_bypass_en            :1;	//(31:31,NA,0x0) //0 : bypass value, 1 : weight value
	};
}PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950534 RW 0x000E0F0E
	UINT32 reg_3x3_wgt_cc_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_cc_01                :8;	//(15:8,NA,0x0F) //weight_value
	UINT32 reg_3x3_wgt_cc_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :8;
	};
}PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950538 RW 0x000E0E0E
	UINT32 reg_3x3_wgt_d1_00                :8;	//(7:0,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_d1_01                :8;	//(15:8,NA,0x0E) //weight_value
	UINT32 reg_3x3_wgt_d1_02                :8;	//(23:16,NA,0x0E) //weight_value
	UINT32 resvd                            :8;
	};
}PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95053C RW 0x00000000
	UINT32 reg_comp_3x3_blur_img_wid        :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_img_hei        :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_3x3_blur_en             :1;	//(31:31,NA,0x0) //Composition enable
	};
}PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950540 RW 0x00000000
	UINT32 reg_comp_3x3_blur_win_x0         :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_win_y0         :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950544 RW 0x00000000
	UINT32 reg_comp_3x3_blur_win_x1         :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_3x3_blur_win_y1         :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950548 RW 0x00002801
	UINT32 reg_sel_sync_gain                :2;	//(1:0,NA,0x1) //not use
	UINT32 resvd0                           :2;
	UINT32 reg_debug_test                   :1;	//(4:4,NA,0x0) //1 : test_pattern
	UINT32 resvd1                           :1;
	UINT32 reg_pic_init_sel                 :2;	//(7:6,NA,0x0) //blur(Y,sample,body map)init select	00 : VS falling	01 : VA falling	1x : external pic_init/pic_start
	UINT32 refine_num                       :12;	//(19:8,NA,0x28) //not use
	UINT32 pic_start_num                    :12;	//(31:20,NA,0x0) //after pic_init, pic_start delay : num*256
	};
}PE_O26_OBC_BODY_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95054C RW 0x00000000
	UINT32 reg_force_enable                 :1;	//(0:0,NA,0x0) //0 : off, 1 : on
	UINT32 resvd0                           :7;
	UINT32 reg_force_threshold              :8;	//(15:8,NA,0x0) //force threshold : 0~255
	UINT32 reg_force_value                  :8;	//(23:16,NA,0x0) //force value : 0~255
	UINT32 resvd1                           :8;
	};
}PE_O26_OBC_BODY_PSP_FORCE_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950570 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18:18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19:19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x12C) //reset cnt 12bit(0~4095)
	};
}PE_O26_OBC_BODY_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950574 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950578 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95057C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950580 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950584 RW 0xFFB43200
	UINT32 reg_refine_weight_obj_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_obj_x1         :8;	//(15:8,NA,0x32) //
	UINT32 reg_refine_weight_obj_x2         :8;	//(23:16,NA,0xB4) //
	UINT32 reg_refine_weight_obj_x3         :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950588 RW 0x04040101
	UINT32 reg_refine_weight_obj_y0         :8;	//(7:0,NA,0x01) //
	UINT32 reg_refine_weight_obj_y1         :8;	//(15:8,NA,0x01) //
	UINT32 reg_refine_weight_obj_y2         :8;	//(23:16,NA,0x04) //
	UINT32 reg_refine_weight_obj_y3         :8;	//(31:24,NA,0x04) //
	};
}PE_O26_OBC_BODY_REFINE_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95058C RW 0x00000002
	UINT32 reg_sam_obj_operation            :1;	//(0:0,NA,0) //operation between obj(after LUT) and sum of sample	0 : multiply	1 : add
	UINT32 reg_sum_obj_operation_en         :1;	//(1:1,NA,1) //after sum of sample, enable using operation with obj 	0 : only use sum of sample 	1 : use operation between obj and sum of sample
	UINT32 resvd                            :30;
	};
}PE_O26_OBC_BODY_REFINE_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950590 RW 0x0870_0780
	UINT32 reg_rgn_gain_width               :13;	//(12:0,NA,1920) //processing width (default : 3840/2 = 1920)
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_height              :13;	//(28:16,NA,2160) //processing height (default : 1080)
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950594 RW 0x0064_012C
	UINT32 reg_rgn_gain_position_x2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x1         :13;	//(28:16,NA,100) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950598 RW 0x027F_0354
	UINT32 reg_rgn_gain_position_x4         :13;	//(12:0,NA,852) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x3         :13;	//(28:16,NA,639) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95059C RW 0x0429_0519
	UINT32 reg_rgn_gain_position_x6         :13;	//(12:0,NA,1305) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x5         :13;	//(28:16,NA,1065) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505A0 RW 0x0609_06DE
	UINT32 reg_rgn_gain_position_x8         :13;	//(12:0,NA,1758) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x7         :13;	//(28:16,NA,1545) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505A4 RW 0x0096_012C
	UINT32 reg_rgn_gain_position_y2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y1         :13;	//(28:16,NA,150) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505A8 RW 0x039C_0514
	UINT32 reg_rgn_gain_position_y4         :13;	//(12:0,NA,1300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y3         :13;	//(28:16,NA,924) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505AC RW 0x0708_07D0
	UINT32 reg_rgn_gain_position_y6         :13;	//(12:0,NA,2000) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y5         :13;	//(28:16,NA,1800) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505B0 RW 0x6464_6464
	UINT32 reg_rgn_gain_41                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_31                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_21                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_11                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505B4 RW 0x6464_6464
	UINT32 reg_rgn_gain_81                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_71                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_61                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_51                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505B8 RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_42                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_32                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_22                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_12                  :8;	//(31:24,NA,110) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505BC RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_82                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_72                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_62                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_52                  :8;	//(31:24,NA,110) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505C0 RW 0x8080_8080
	UINT32 reg_rgn_gain_43                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_33                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_23                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_13                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505C4 RW 0x8080_8080
	UINT32 reg_rgn_gain_83                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_73                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_63                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_53                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505C8 RW 0x8080_8080
	UINT32 reg_rgn_gain_44                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_34                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_24                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_14                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505CC RW 0x8080_8080
	UINT32 reg_rgn_gain_84                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_74                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_64                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_54                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505D0 RW 0x6464_6464
	UINT32 reg_rgn_gain_45                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_35                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_25                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_15                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505D4 RW 0x6464_6464
	UINT32 reg_rgn_gain_85                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_75                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_65                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_55                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505D8 RW 0x5050_5050
	UINT32 reg_rgn_gain_46                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_36                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_26                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_16                  :8;	//(31:24,NA,80) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505DC RW 0x5050_5050
	UINT32 reg_rgn_gain_86                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_76                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_66                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_56                  :8;	//(31:24,NA,80) //
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505E0 RW 0x0000_8001
	UINT32 reg_rgn_gain_en                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :7;
	UINT32 reg_rgn_gain_bnd_gain            :8;	//(15:8,NA,128) //
	UINT32 resvd1                           :16;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505E4 RW 0x0000_077F
	UINT32 reg_rgn_gain_bnd_x1              :13;	//(12:0,NA,1919) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_x0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505E8 RW 0x0000_086F
	UINT32 reg_rgn_gain_bnd_y1              :13;	//(12:0,NA,2159) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_y0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9505F0 RW 0x87800870
	UINT32 reg_lm_vsize                     :13;	//(12:0,NA,0x870) //Vsize of 2P input	2160
	UINT32 resvd0                           :3;
	UINT32 reg_lm_hsize                     :13;	//(28:16,NA,0x780) //Hsize of 2P input	3840/2P = 1920
	UINT32 resvd1                           :2;
	UINT32 buffer_en                        :1;	//(31:31,NA,0x1) //
	};
}PE_O26_OBC_BODY_BUFFER_CTRL0_T;

typedef struct {
	PE_O26_OBC_BODY_PSP_CTRL00_T                                psp_ctrl00;	//0xCC950500
	PE_O26_OBC_BODY_PSP_CTRL01_T                                psp_ctrl01;	//0xCC950504
	PE_O26_OBC_BODY_PSP_CTRL02_T                                psp_ctrl02;	//0xCC950508
	PE_O26_OBC_BODY_L5_GAIN_LUT1_T                            l5_gain_lut1;	//0xCC95050C
	PE_O26_OBC_BODY_L5_GAIN_LUT2_T                            l5_gain_lut2;	//0xCC950510
	PE_O26_OBC_BODY_PSP_CTRL03_T                                psp_ctrl03;	//0xCC950514
	PE_O26_OBC_BODY_PSP_CTRL04_T                                psp_ctrl04;	//0xCC950518
	PE_O26_OBC_BODY_PSP_CTRL05_T                                psp_ctrl05;	//0xCC95051C
	PE_O26_OBC_BODY_PSP_CTRL06_T                                psp_ctrl06;	//0xCC950520
	PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_00_T            psp_roi_mask_ctrl_00;	//0xCC950524
	PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_01_T            psp_roi_mask_ctrl_01;	//0xCC950528
	PE_O26_OBC_BODY_PSP_ROI_MASK_CTRL_02_T            psp_roi_mask_ctrl_02;	//0xCC95052C
	PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_00_T              psp_3x3_blur_wgt_00;	//0xCC950530
	PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_01_T              psp_3x3_blur_wgt_01;	//0xCC950534
	PE_O26_OBC_BODY_PSP_3X3_BLUR_WGT_02_T              psp_3x3_blur_wgt_02;	//0xCC950538
	PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_00_T            psp_comp_3x3_blur_00;	//0xCC95053C
	PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_01_T            psp_comp_3x3_blur_01;	//0xCC950540
	PE_O26_OBC_BODY_PSP_COMP_3X3_BLUR_02_T            psp_comp_3x3_blur_02;	//0xCC950544
	PE_O26_OBC_BODY_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCC950548
	PE_O26_OBC_BODY_PSP_FORCE_VALUE_T                      psp_force_value;	//0xCC95054C
	UINT32                                                       reserved0;	//0xCC950550
	UINT32                                                       reserved1;	//0xCC950554
	UINT32                                                       reserved2;	//0xCC950558
	UINT32                                                       reserved3;	//0xCC95055C
	UINT32                                                       reserved4;	//0xCC950560
	UINT32                                                       reserved5;	//0xCC950564
	UINT32                                                       reserved6;	//0xCC950568
	UINT32                                                       reserved7;	//0xCC95056C
	PE_O26_OBC_BODY_REFINE_CTRL0_T                            refine_ctrl0;	//0xCC950570
	PE_O26_OBC_BODY_REFINE_CTRL1_T                            refine_ctrl1;	//0xCC950574
	PE_O26_OBC_BODY_REFINE_CTRL2_T                            refine_ctrl2;	//0xCC950578
	PE_O26_OBC_BODY_REFINE_CTRL3_T                            refine_ctrl3;	//0xCC95057C
	PE_O26_OBC_BODY_REFINE_CTRL4_T                            refine_ctrl4;	//0xCC950580
	PE_O26_OBC_BODY_REFINE_CTRL5_T                            refine_ctrl5;	//0xCC950584
	PE_O26_OBC_BODY_REFINE_CTRL6_T                            refine_ctrl6;	//0xCC950588
	PE_O26_OBC_BODY_REFINE_CTRL7_T                            refine_ctrl7;	//0xCC95058C
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_00_T obj_refine_body_gain_ctrl_00;	//0xCC950590
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_01_T obj_refine_body_gain_ctrl_01;	//0xCC950594
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_02_T obj_refine_body_gain_ctrl_02;	//0xCC950598
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_03_T obj_refine_body_gain_ctrl_03;	//0xCC95059C
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_04_T obj_refine_body_gain_ctrl_04;	//0xCC9505A0
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_05_T obj_refine_body_gain_ctrl_05;	//0xCC9505A4
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_06_T obj_refine_body_gain_ctrl_06;	//0xCC9505A8
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_07_T obj_refine_body_gain_ctrl_07;	//0xCC9505AC
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_08_T obj_refine_body_gain_ctrl_08;	//0xCC9505B0
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_09_T obj_refine_body_gain_ctrl_09;	//0xCC9505B4
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_10_T obj_refine_body_gain_ctrl_10;	//0xCC9505B8
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_11_T obj_refine_body_gain_ctrl_11;	//0xCC9505BC
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_12_T obj_refine_body_gain_ctrl_12;	//0xCC9505C0
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_13_T obj_refine_body_gain_ctrl_13;	//0xCC9505C4
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_14_T obj_refine_body_gain_ctrl_14;	//0xCC9505C8
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_15_T obj_refine_body_gain_ctrl_15;	//0xCC9505CC
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_16_T obj_refine_body_gain_ctrl_16;	//0xCC9505D0
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_17_T obj_refine_body_gain_ctrl_17;	//0xCC9505D4
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_18_T obj_refine_body_gain_ctrl_18;	//0xCC9505D8
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_19_T obj_refine_body_gain_ctrl_19;	//0xCC9505DC
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_20_T obj_refine_body_gain_ctrl_20;	//0xCC9505E0
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_21_T obj_refine_body_gain_ctrl_21;	//0xCC9505E4
	PE_O26_OBC_BODY_OBJ_REFINE_BODY_GAIN_CTRL_22_T obj_refine_body_gain_ctrl_22;	//0xCC9505E8
	UINT32                                                       reserved8;	//0xCC9505EC
	PE_O26_OBC_BODY_BUFFER_CTRL0_T                            buffer_ctrl0;	//0xCC9505F0
}PE_VSD_OBC_BODY_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950700 RW 0x08700F00
	UINT32 reg_img_wid                      :13;	//(12:0,NA,0xF00) //horizontal resolution 3840
	UINT32 resvd0                           :3;
	UINT32 reg_img_hei                      :13;	//(28:16,NA,0x870) //vertical resolution   2160
	UINT32 resvd1                           :2;
	UINT32 reg_psp_detour_en                :1;	//(31:31,NA,0x0) //not_use
	};
}PE_O26_OBC_HEAD_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950704 RW 0x87F01010
	UINT32 reg_blk_wid                      :6;	//(5:0,NA,0x10) //Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//(13:8,NA,0x10) //Block size       16
	UINT32 resvd1                           :18;
	};
}PE_O26_OBC_HEAD_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950708 RW 0x00000000
	UINT32 resvd0                           :1;
	UINT32 reg_psp_en                       :1;	//(1:1,NA,0x00) //1 : obc enable(obc : obc_res, video : delay in->out)	0 : obc_bypass(obc : value 0, video : delay in->out)
	UINT32 resvd1                           :30;
	};
}PE_O26_OBC_HEAD_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95070C RW 0x3F3F0000
	UINT32 y0_point                         :8;	//(7:0,NA,0x00) //control point of Y0
	UINT32 x0_point                         :8;	//(15:8,NA,0x00) //control point of X0
	UINT32 y1_point                         :8;	//(23:16,NA,0x3F) //control point of Y1
	UINT32 x1_point                         :8;	//(31:24,NA,0x3F) //control point of X1
	};
}PE_O26_OBC_HEAD_HEAD_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950710 RW 0x3F3F3F3F
	UINT32 y2_point                         :8;	//(7:0,NA,0x3F) //control point of Y2
	UINT32 x2_point                         :8;	//(15:8,NA,0x3F) //control point of X2
	UINT32 y3_point                         :8;	//(23:16,NA,0x3F) //control point of Y3
	UINT32 x3_point                         :8;	//(31:24,NA,0x3F) //control point of X3
	};
}PE_O26_OBC_HEAD_HEAD_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950714 RW 0x008700F0
	UINT32 reg_blk_wid                      :9;	//(8:0,NA,0xF0) //Number of hblock 240
	UINT32 resvd0                           :7;
	UINT32 reg_blk_hei                      :9;	//(24:16,NA,0x87) //Number of vblock 135
	UINT32 resvd1                           :7;
	};
}PE_O26_OBC_HEAD_PSP_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950718 RW 0x00000000
	UINT32 reg_comp_img_wid                 :13;	//(12:0,NA,0x00) //horizontal composition resolution
	UINT32 resvd0                           :3;
	UINT32 reg_comp_img_hei                 :13;	//(28:16,NA,0x00) //vertical composition resolution
	UINT32 resvd1                           :2;
	UINT32 reg_comp_en                      :1;	//(31:31,NA,0x0) //Composition enable
	};
}PE_O26_OBC_HEAD_PSP_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95071C RW 0x00000000
	UINT32 reg_comp_win_x0                  :13;	//(12:0,NA,0x0) //Composition window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y0                  :13;	//(28:16,NA,0x0) //Composition window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_PSP_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950720 RW 0x00000000
	UINT32 reg_comp_win_x1                  :13;	//(12:0,NA,0x0) //Composition window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_comp_win_y1                  :13;	//(28:16,NA,0x0) //Composition window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_PSP_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950724 RW 0x0000_0000
	UINT32 reg_roi_mask_en                  :1;	//(0:0,NA,0x0) //ROI mask enable
	UINT32 resvd0                           :7;
	UINT32 reg_roi_mask_pix_val_yy          :8;	//(15:8,NA,0x0) //ROI mask pixel value (Y)
	UINT32 reg_comp_value                   :8;	//(23:16,NA,0x0) //Composition pixel value (Y)
	UINT32 resvd1                           :8;
	};
}PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950728 RW 0x0000_0000
	UINT32 reg_roi_mask_win_x0              :13;	//(12:0,NA,0x0) //ROI mask window start position, x0
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y0              :13;	//(28:16,NA,0x0) //ROI mask window start position, y0
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95072C RW 0x0000_0000
	UINT32 reg_roi_mask_win_x1              :13;	//(12:0,NA,0x0) //ROI mask window end position, x1
	UINT32 resvd0                           :3;
	UINT32 reg_roi_mask_win_y1              :13;	//(28:16,NA,0x0) //ROI mask window end position, y1
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950748 RW 0x00002801
	UINT32 reg_sel_sync_gain                :2;	//(1:0,NA,0x1) //depth_map prfetch start ( internal lut/fifo init )  	00 : VA falling + refine_num * 256 	01 : VS falling	10 : VA falling	11 : external pic_init/pic_start
	UINT32 resvd0                           :2;
	UINT32 reg_debug_test                   :1;	//(4:4,NA,0x0) //1 : test_pattern
	UINT32 resvd1                           :3;
	UINT32 refine_num                       :12;	//(19:8,NA,0x28) //depth_map prfetch start : num*256
	UINT32 pic_start_num                    :12;	//(31:20,NA,0x0) //after prefetch start, pic_start delay : num*256
	};
}PE_O26_OBC_HEAD_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95074C RW 0x00000000
	UINT32 reg_force_enable                 :1;	//(0:0,NA,0x0) //0 : off, 1 : on
	UINT32 resvd0                           :7;
	UINT32 reg_force_threshold              :8;	//(15:8,NA,0x0) //force threshold : 0~255
	UINT32 reg_force_value                  :8;	//(23:16,NA,0x0) //force value : 0~255
	UINT32 resvd1                           :8;
	};
}PE_O26_OBC_HEAD_PSP_FORCE_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950770 RW 0x12C00080
	UINT32 reg_refine_diff_luma_a           :8;	//(7:0,NA,0x80) //
	UINT32 reg_refine_diff_chroma_b         :8;	//(15:8,NA,0x00) //
	UINT32 debug_map                        :2;	//(17:16,NA,0x00) //0 : obj_refine	1 : sample_yy	2 : sample_cb	3 : sample_cr
	UINT32 debug_map_en                     :1;	//(18:18,NA,0x00) //0 : debug_map off	1 : debug_map on
	UINT32 sel_picinit                      :1;	//(19:19,NA,0x00) //0 : vactive falling	1 : vsync falling
	UINT32 reg_reset_cnt                    :12;	//(31:20,NA,0x12C) //reset cnt 12bit(0~4095)
	};
}PE_O26_OBC_HEAD_REFINE_HEAD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950774 RW 0x20120400
	UINT32 reg_refine_weight_lux_x0         :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_weight_lux_x1         :8;	//(15:8,NA,0x04) //
	UINT32 reg_refine_weight_lux_x2         :8;	//(23:16,NA,0x12) //
	UINT32 reg_refine_weight_lux_x3         :8;	//(31:24,NA,0x20) //
	};
}PE_O26_OBC_HEAD_REFINE_HEAD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950778 RW 0x021034FF
	UINT32 reg_refine_weight_lux_y0         :8;	//(7:0,NA,0xFF) //
	UINT32 reg_refine_weight_lux_y1         :8;	//(15:8,NA,0x34) //
	UINT32 reg_refine_weight_lux_y2         :8;	//(23:16,NA,0x10) //
	UINT32 reg_refine_weight_lux_y3         :8;	//(31:24,NA,0x02) //
	};
}PE_O26_OBC_HEAD_REFINE_HEAD_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95077C RW 0xFF804000
	UINT32 reg_refine_post_lux_x0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_x1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_x2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_x3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_OBC_HEAD_REFINE_HEAD_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950780 RW 0xFF804000
	UINT32 reg_refine_post_lux_y0           :8;	//(7:0,NA,0x00) //
	UINT32 reg_refine_post_lux_y1           :8;	//(15:8,NA,0x40) //
	UINT32 reg_refine_post_lux_y2           :8;	//(23:16,NA,0x80) //
	UINT32 reg_refine_post_lux_y3           :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_OBC_HEAD_REFINE_HEAD_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950790 RW 0x0870_0780
	UINT32 reg_rgn_gain_width               :13;	//(12:0,NA,1920) //processing width (default : 3840/2 = 1920)
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_height              :13;	//(28:16,NA,2160) //processing height (default : 1080)
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950794 RW 0x0064_012C
	UINT32 reg_rgn_gain_position_x2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x1         :13;	//(28:16,NA,100) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950798 RW 0x027F_0354
	UINT32 reg_rgn_gain_position_x4         :13;	//(12:0,NA,852) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x3         :13;	//(28:16,NA,639) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95079C RW 0x0429_0519
	UINT32 reg_rgn_gain_position_x6         :13;	//(12:0,NA,1305) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x5         :13;	//(28:16,NA,1065) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507A0 RW 0x0609_06DE
	UINT32 reg_rgn_gain_position_x8         :13;	//(12:0,NA,1758) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_x7         :13;	//(28:16,NA,1545) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507A4 RW 0x0096_012C
	UINT32 reg_rgn_gain_position_y2         :13;	//(12:0,NA,300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y1         :13;	//(28:16,NA,150) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507A8 RW 0x039C_0514
	UINT32 reg_rgn_gain_position_y4         :13;	//(12:0,NA,1300) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y3         :13;	//(28:16,NA,924) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507AC RW 0x0708_07D0
	UINT32 reg_rgn_gain_position_y6         :13;	//(12:0,NA,2000) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_position_y5         :13;	//(28:16,NA,1800) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507B0 RW 0x6464_6464
	UINT32 reg_rgn_gain_41                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_31                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_21                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_11                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507B4 RW 0x6464_6464
	UINT32 reg_rgn_gain_81                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_71                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_61                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_51                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507B8 RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_42                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_32                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_22                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_12                  :8;	//(31:24,NA,110) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507BC RW 0x6E6E_6E6E
	UINT32 reg_rgn_gain_82                  :8;	//(7:0,NA,110) //
	UINT32 reg_rgn_gain_72                  :8;	//(15:8,NA,110) //
	UINT32 reg_rgn_gain_62                  :8;	//(23:16,NA,110) //
	UINT32 reg_rgn_gain_52                  :8;	//(31:24,NA,110) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507C0 RW 0x8080_8080
	UINT32 reg_rgn_gain_43                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_33                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_23                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_13                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507C4 RW 0x8080_8080
	UINT32 reg_rgn_gain_83                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_73                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_63                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_53                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507C8 RW 0x8080_8080
	UINT32 reg_rgn_gain_44                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_34                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_24                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_14                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507CC RW 0x8080_8080
	UINT32 reg_rgn_gain_84                  :8;	//(7:0,NA,128) //
	UINT32 reg_rgn_gain_74                  :8;	//(15:8,NA,128) //
	UINT32 reg_rgn_gain_64                  :8;	//(23:16,NA,128) //
	UINT32 reg_rgn_gain_54                  :8;	//(31:24,NA,128) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507D0 RW 0x6464_6464
	UINT32 reg_rgn_gain_45                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_35                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_25                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_15                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507D4 RW 0x6464_6464
	UINT32 reg_rgn_gain_85                  :8;	//(7:0,NA,100) //
	UINT32 reg_rgn_gain_75                  :8;	//(15:8,NA,100) //
	UINT32 reg_rgn_gain_65                  :8;	//(23:16,NA,100) //
	UINT32 reg_rgn_gain_55                  :8;	//(31:24,NA,100) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507D8 RW 0x5050_5050
	UINT32 reg_rgn_gain_46                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_36                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_26                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_16                  :8;	//(31:24,NA,80) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507DC RW 0x5050_5050
	UINT32 reg_rgn_gain_86                  :8;	//(7:0,NA,80) //
	UINT32 reg_rgn_gain_76                  :8;	//(15:8,NA,80) //
	UINT32 reg_rgn_gain_66                  :8;	//(23:16,NA,80) //
	UINT32 reg_rgn_gain_56                  :8;	//(31:24,NA,80) //
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507E0 RW 0x0000_8001
	UINT32 reg_rgn_gain_en                  :1;	//(0:0,NA,1) //
	UINT32 resvd0                           :7;
	UINT32 reg_rgn_gain_bnd_gain            :8;	//(15:8,NA,128) //
	UINT32 resvd1                           :16;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507E4 RW 0x0000_077F
	UINT32 reg_rgn_gain_bnd_x1              :13;	//(12:0,NA,1919) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_x0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9507E8 RW 0x0000_086F
	UINT32 reg_rgn_gain_bnd_y1              :13;	//(12:0,NA,2159) //
	UINT32 resvd0                           :3;
	UINT32 reg_rgn_gain_bnd_y0              :13;	//(28:16,NA,0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_22_T;

typedef struct {
	PE_O26_OBC_HEAD_PSP_CTRL00_T                                psp_ctrl00;	//0xCC950700
	PE_O26_OBC_HEAD_PSP_CTRL01_T                                psp_ctrl01;	//0xCC950704
	PE_O26_OBC_HEAD_PSP_CTRL02_T                                psp_ctrl02;	//0xCC950708
	PE_O26_OBC_HEAD_HEAD_L5_GAIN_LUT1_T                  head_l5_gain_lut1;	//0xCC95070C
	PE_O26_OBC_HEAD_HEAD_L5_GAIN_LUT2_T                  head_l5_gain_lut2;	//0xCC950710
	PE_O26_OBC_HEAD_PSP_CTRL03_T                                psp_ctrl03;	//0xCC950714
	PE_O26_OBC_HEAD_PSP_CTRL04_T                                psp_ctrl04;	//0xCC950718
	PE_O26_OBC_HEAD_PSP_CTRL05_T                                psp_ctrl05;	//0xCC95071C
	PE_O26_OBC_HEAD_PSP_CTRL06_T                                psp_ctrl06;	//0xCC950720
	PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_00_T            psp_roi_mask_ctrl_00;	//0xCC950724
	PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_01_T            psp_roi_mask_ctrl_01;	//0xCC950728
	PE_O26_OBC_HEAD_PSP_ROI_MASK_CTRL_02_T            psp_roi_mask_ctrl_02;	//0xCC95072C
	UINT32                                                       reserved0;	//0xCC950730
	UINT32                                                       reserved1;	//0xCC950734
	UINT32                                                       reserved2;	//0xCC950738
	UINT32                                                       reserved3;	//0xCC95073C
	UINT32                                                       reserved4;	//0xCC950740
	UINT32                                                       reserved5;	//0xCC950744
	PE_O26_OBC_HEAD_DISPLAY_DEBUG_MAP_T                  display_debug_map;	//0xCC950748
	PE_O26_OBC_HEAD_PSP_FORCE_VALUE_T                      psp_force_value;	//0xCC95074C
	UINT32                                                       reserved6;	//0xCC950750
	UINT32                                                       reserved7;	//0xCC950754
	UINT32                                                       reserved8;	//0xCC950758
	UINT32                                                       reserved9;	//0xCC95075C
	UINT32                                                      reserved10;	//0xCC950760
	UINT32                                                      reserved11;	//0xCC950764
	UINT32                                                      reserved12;	//0xCC950768
	UINT32                                                      reserved13;	//0xCC95076C
	PE_O26_OBC_HEAD_REFINE_HEAD_CTRL0_T                  refine_head_ctrl0;	//0xCC950770
	PE_O26_OBC_HEAD_REFINE_HEAD_CTRL1_T                  refine_head_ctrl1;	//0xCC950774
	PE_O26_OBC_HEAD_REFINE_HEAD_CTRL2_T                  refine_head_ctrl2;	//0xCC950778
	PE_O26_OBC_HEAD_REFINE_HEAD_CTRL3_T                  refine_head_ctrl3;	//0xCC95077C
	PE_O26_OBC_HEAD_REFINE_HEAD_CTRL4_T                  refine_head_ctrl4;	//0xCC950780
	UINT32                                                      reserved14;	//0xCC950784
	UINT32                                                      reserved15;	//0xCC950788
	UINT32                                                      reserved16;	//0xCC95078C
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_00_T obj_refine_head_gain_ctrl_00;	//0xCC950790
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_01_T obj_refine_head_gain_ctrl_01;	//0xCC950794
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_02_T obj_refine_head_gain_ctrl_02;	//0xCC950798
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_03_T obj_refine_head_gain_ctrl_03;	//0xCC95079C
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_04_T obj_refine_head_gain_ctrl_04;	//0xCC9507A0
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_05_T obj_refine_head_gain_ctrl_05;	//0xCC9507A4
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_06_T obj_refine_head_gain_ctrl_06;	//0xCC9507A8
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_07_T obj_refine_head_gain_ctrl_07;	//0xCC9507AC
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_08_T obj_refine_head_gain_ctrl_08;	//0xCC9507B0
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_09_T obj_refine_head_gain_ctrl_09;	//0xCC9507B4
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_10_T obj_refine_head_gain_ctrl_10;	//0xCC9507B8
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_11_T obj_refine_head_gain_ctrl_11;	//0xCC9507BC
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_12_T obj_refine_head_gain_ctrl_12;	//0xCC9507C0
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_13_T obj_refine_head_gain_ctrl_13;	//0xCC9507C4
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_14_T obj_refine_head_gain_ctrl_14;	//0xCC9507C8
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_15_T obj_refine_head_gain_ctrl_15;	//0xCC9507CC
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_16_T obj_refine_head_gain_ctrl_16;	//0xCC9507D0
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_17_T obj_refine_head_gain_ctrl_17;	//0xCC9507D4
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_18_T obj_refine_head_gain_ctrl_18;	//0xCC9507D8
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_19_T obj_refine_head_gain_ctrl_19;	//0xCC9507DC
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_20_T obj_refine_head_gain_ctrl_20;	//0xCC9507E0
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_21_T obj_refine_head_gain_ctrl_21;	//0xCC9507E4
	PE_O26_OBC_HEAD_OBJ_REFINE_HEAD_GAIN_CTRL_22_T obj_refine_head_gain_ctrl_22;	//0xCC9507E8
}PE_VSD_OBC_HEAD_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950200 RW 0x0240_0000
	UINT32 resvd0                           :16;
	UINT32 reg_debug_mode                   :4;	//(19:16,NA,0x0) //0: normal	1: RCE_P ( R,G,B )	2: RCE_L ( R,G,B )	3: head_gain (W = R&G&B )	4: body_gain (W = R&G&B ) 	5: txtr_bain (W = R&G&B ) 	6: FACE+BODY (R = head_gain , G = body gain, B = 0)	7: FACE+BODY+TXTR (R = head_gain , G = body gain, B = txtr_gain)	8:face_body_blend (W = R&G&B )	9:final_blend(W = R&G&B )
	UINT32 reg_use_ext_pic_init             :1;	//(20,NA,0x0) //pic_init MUX	0: internal pic_init	1: external pic_init (obs_mode)
	UINT32 reg_obe_obs_mode                 :1;	//(21,NA,0x0) //0: vsd_obe	1: obs_obe (out head/body_gain=0)
	UINT32 reg_sel_obe_imux                 :1;	//(22,NA,0x1) //O26, 0: YC, 1: RGB
	UINT32 reg_mcsc_en                      :1;	//(23,NA,0x0) //O26
	UINT32 reg_ocsc_en                      :1;	//(24,NA,0x0) //
	UINT32 reg_icsc_en                      :1;	//(25,NA,0x1) //
	UINT32 resvd1                           :5;
	UINT32 reg_obe_en                       :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_000_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950204 RW 0x0F00_0870
	UINT32 reg_heigt                        :16;	//(15:0,NA,0x870) //2160
	UINT32 reg_width                        :16;	//(31:16,NA,0xF00) //3840
	};
}PE_O26_VSD_OBE_CTRL_001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950208 RW 0x6250_3025
	UINT32 reg_bg_body_hist_th              :8;	//(7:0,NA,0x25) //
	UINT32 reg_bg_head_hist_th              :8;	//(15:8,NA,0x30) //
	UINT32 reg_body_hist_th                 :8;	//(23:16,NA,0x50) //
	UINT32 reg_head_hist_th                 :8;	//(31:24,NA,0x62) //
	};
}PE_O26_VSD_OBE_CTRL_002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95020C RW 0x5440_0000
	UINT32 resvd                            :16;
	UINT32 reg_bg_txtr_hist_th              :8;	//(23:16,NA,0x40) //
	UINT32 reg_txtr_hist_th                 :8;	//(31:24,NA,0x54) //
	};
}PE_O26_VSD_OBE_CTRL_003_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950210 RW 0x0003_8080
	UINT32 reg_sat_prsv_ratio               :8;	//(7:0,NA,0x80) //
	UINT32 reg_hue_prsv_ratio               :8;	//(15:8,NA,0x80) //
	UINT32 reg_sat_prsv_en                  :1;	//(16,NA,0x1) //
	UINT32 reg_hue_prsv_en                  :1;	//(17,NA,0x1) //
	UINT32 resvd                            :13;
	UINT32 reg_hsp_en                       :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_004_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950214 RW 0x0000_0000
	UINT32 reg_dither_enable                :1;	//(0,NA,0x00) //
	UINT32 resvd0                           :1;
	UINT32 reg_dither_freeze                :1;	//(2,NA,0x00) //
	UINT32 reg_dither_demo_tpg              :1;	//(3,NA,0x00) //
	UINT32 reg_bit_mode                     :2;	//(5:4,NA,0x00) //
	UINT32 reg_clock_gating_disable         :1;	//(6,NA,0x00) //
	UINT32 resvd1                           :1;
	UINT32 reg_max_delta_g                  :8;	//(15:8,NA,0x00) //
	UINT32 reg_max_delta_b                  :8;	//(23:16,NA,0x00) //
	UINT32 reg_max_delta_r                  :8;	//(31:24,NA,0x00) //
	};
}PE_O26_VSD_OBE_CTRL_005_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950218 RW 0x0000_0000
	UINT32 reg_ind_addr_ai                  :9;	//(8:0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_ind_ai                       :1;	//(12,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ind_load                     :1;	//(15,NA,0x0) //do not use
	UINT32 resvd2                           :16;
	};
}PE_O26_VSD_OBE_IND_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95021C RW 0x0000_0000
	UINT32 reg_ind_data_wr                  :32;	//(31:0,NA,0x0000_0000) //do not use
	};
}PE_O26_VSD_OBE_IND_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950220 RO 0x0000_0000
	UINT32 reg_ind_data_rd                  :32;	//(31:0,NA,0x0000_0000) //
	};
}PE_O26_VSD_OBE_IND_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950224 RW 0x1000_7D6D
	UINT32 reg_icsc_coef1                   :15;	//(14:0,NA,0x7D6D) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef0                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_009_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950228 RW 0x7710_1000
	UINT32 reg_icsc_coef3                   :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef2                   :15;	//(30:16,NA,0x7710) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_010_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95022C RW 0x1D6E_0000
	UINT32 reg_icsc_coef5                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef4                   :15;	//(30:16,NA,0x1D6E) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_011_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950230 RW 0x1000_0000
	UINT32 reg_icsc_coef7                   :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_icsc_coef6                   :15;	//(30:16,NA,0x1000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950234 RW 0x1711_0000
	UINT32 resvd0                           :16;
	UINT32 reg_icsc_coef8                   :15;	//(30:16,NA,0x1711) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_013_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950238 RW 0x0000_0600
	UINT32 reg_icsc_ofst1                   :11;	//(10:0,NA,0x0600) //
	UINT32 resvd0                           :5;
	UINT32 reg_icsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_014_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95023C RW 0x0600_0000
	UINT32 reg_icsc_ofst3                   :13;	//(12:0,NA,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_icsc_ofst2                   :11;	//(26:16,NA,0x0600) //
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_015_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950240 RW 0x0000_0000
	UINT32 reg_icsc_ofst5                   :13;	//(12:0,NA,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_icsc_ofst4                   :13;	//(28:16,NA,0x0000) //
	UINT32 resvd1                           :3;
	};
}PE_O26_VSD_OBE_CTRL_016_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950244 RW 0x0AD9_00F3
	UINT32 reg_ocsc_coef1                   :15;	//(14:0,NA,0x00F3) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef0                   :15;	//(30:16,NA,0x0AD9) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_017_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950248 RW 0x0434_7A1A
	UINT32 reg_ocsc_coef3                   :15;	//(14:0,NA,0x7A1A) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef2                   :15;	//(30:16,NA,0x0434) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_018_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95024C RW 0x082F_7DB7
	UINT32 reg_ocsc_coef5                   :15;	//(14:0,NA,0x7DB7) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef4                   :15;	//(30:16,NA,0x082F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_019_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950250 RW 0x787A_7F58
	UINT32 reg_ocsc_coef7                   :15;	//(14:0,NA,0x7F58) //
	UINT32 resvd0                           :1;
	UINT32 reg_ocsc_coef6                   :15;	//(30:16,NA,0x787A) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_020_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950254 RW 0x082F_0000
	UINT32 resvd0                           :16;
	UINT32 reg_ocsc_coef8                   :15;	//(30:16,NA,0x082F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_021_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950258 RW 0x0000_0000
	UINT32 reg_ocsc_ofst1                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst0                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_022_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95025C RW 0x0000_0000
	UINT32 reg_ocsc_ofst3                   :11;	//(10:0,NA,0x0000) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst2                   :11;	//(26:16,NA,0x0000) //
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_023_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950260 RW 0x0200_0200
	UINT32 reg_ocsc_ofst5                   :11;	//(10:0,NA,0x0200) //
	UINT32 resvd0                           :5;
	UINT32 reg_ocsc_ofst4                   :11;	//(26:16,NA,0x0200) //
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_024_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950264 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_txtr_master_gain             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x00) //
	};
}PE_O26_VSD_OBE_CTRL_025_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950268 RW 0xFFFF_7EFF
	UINT32 reg_final_blend_lut_y2           :8;	//(7:0,NA,0xFF) //
	UINT32 reg_final_blend_lut_x2           :8;	//(15:8,NA,0x7E) //
	UINT32 reg_final_blend_lut_y3           :8;	//(23:16,NA,0xFF) //
	UINT32 reg_final_blend_lut_x3           :8;	//(31:24,NA,0xFF) //for RCE_P, RCE_L blending
	};
}PE_O26_VSD_OBE_CTRL_026_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95026C RW 0x3FFF_00FF
	UINT32 reg_final_blend_lut_y0           :8;	//(7:0,NA,0xFF) //
	UINT32 reg_final_blend_lut_x0           :8;	//(15:8,NA,0x00) //
	UINT32 reg_final_blend_lut_y1           :8;	//(23:16,NA,0xFF) //
	UINT32 reg_final_blend_lut_x1           :8;	//(31:24,NA,0x3F) //for RCE_P, RCE_L blending
	};
}PE_O26_VSD_OBE_CTRL_027_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950270 RW 0x0000_0000
	UINT32 reg_head_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_028_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950274 RW 0x0040_0040
	UINT32 reg_head_r_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_029_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950278 RW 0x0080_0080
	UINT32 reg_head_r_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_030_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95027C RW 0x00FF_00FF
	UINT32 reg_head_r_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_031_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950280 RW 0x01FF_01FF
	UINT32 reg_head_r_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_032_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950284 RW 0x03FF_03FF
	UINT32 reg_head_r_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_r_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_033_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950288 RW 0x0000_0000
	UINT32 reg_head_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_034_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95028C RW 0x0040_0040
	UINT32 reg_head_g_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_035_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950290 RW 0x0080_0080
	UINT32 reg_head_g_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_036_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950294 RW 0x00FF_00FF
	UINT32 reg_head_g_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_037_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950298 RW 0x01FF_01FF
	UINT32 reg_head_g_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_038_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95029C RW 0x03FF_03FF
	UINT32 reg_head_g_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_g_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_039_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502A0 RW 0x0000_0000
	UINT32 reg_head_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_040_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502A4 RW 0x0040_0040
	UINT32 reg_head_b_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_041_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502A8 RW 0x0080_0080
	UINT32 reg_head_b_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_042_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502AC RW 0x00FF_00FF
	UINT32 reg_head_b_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_043_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502B0 RW 0x01FF_01FF
	UINT32 reg_head_b_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_044_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502B4 RW 0x03FF_03FF
	UINT32 reg_head_b_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_head_b_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_045_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502B8 RW 0x0000_0000
	UINT32 reg_body_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_046_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502BC RW 0x0040_0040
	UINT32 reg_body_r_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_047_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502C0 RW 0x0080_0080
	UINT32 reg_body_r_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_048_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502C4 RW 0x00FF_00FF
	UINT32 reg_body_r_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_049_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502C8 RW 0x01FF_01FF
	UINT32 reg_body_r_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_050_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502CC RW 0x03FF_03FF
	UINT32 reg_body_r_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_r_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_051_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502D0 RW 0x0000_0000
	UINT32 reg_body_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_052_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502D4 RW 0x0040_0040
	UINT32 reg_body_g_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_053_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502D8 RW 0x0080_0080
	UINT32 reg_body_g_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_054_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502DC RW 0x00FF_00FF
	UINT32 reg_body_g_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_055_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502E0 RW 0x01FF_01FF
	UINT32 reg_body_g_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_056_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502E4 RW 0x03FF_03FF
	UINT32 reg_body_g_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_g_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_057_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502E8 RW 0x0000_0000
	UINT32 reg_body_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_058_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502EC RW 0x0040_0040
	UINT32 reg_body_b_lut_y1                :10;	//(9:0,NA,0x040) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x1                :10;	//(25:16,NA,0x040) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_059_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502F0 RW 0x0080_0080
	UINT32 reg_body_b_lut_y2                :10;	//(9:0,NA,0x080) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x2                :10;	//(25:16,NA,0x080) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_060_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502F4 RW 0x00FF_00FF
	UINT32 reg_body_b_lut_y3                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x3                :10;	//(25:16,NA,0x0FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_061_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502F8 RW 0x01FF_01FF
	UINT32 reg_body_b_lut_y4                :10;	//(9:0,NA,0x1FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x4                :10;	//(25:16,NA,0x1FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_062_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9502FC RW 0x03FF_03FF
	UINT32 reg_body_b_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_body_b_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_063_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950348 RW 0xFFFF_80A0
	UINT32 reg_head_gain_lut_y2             :8;	//(7:0,NA,0xA0) //
	UINT32 reg_head_gain_lut_x2             :8;	//(15:8,NA,0x80) //
	UINT32 reg_head_gain_lut_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_head_gain_lut_x3             :8;	//(31:24,NA,0xFF) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_082_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95034C RW 0x4020_0000
	UINT32 reg_head_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_gain_lut_y1             :8;	//(23:16,NA,0x20) //
	UINT32 reg_head_gain_lut_x1             :8;	//(31:24,NA,0x40) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_083_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950350 RW 0xFFFF_80A0
	UINT32 reg_body_gain_lut_y2             :8;	//(7:0,NA,0xA0) //
	UINT32 reg_body_gain_lut_x2             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_gain_lut_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_body_gain_lut_x3             :8;	//(31:24,NA,0xFF) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_084_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950354 RW 0x4020_0000
	UINT32 reg_body_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_gain_lut_y1             :8;	//(23:16,NA,0x20) //
	UINT32 reg_body_gain_lut_x1             :8;	//(31:24,NA,0x40) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_085_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950358 RW 0x0000_0000
	UINT32 reg_body_head_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x3             :8;	//(31:24,NA,0x00) //body-head
	};
}PE_O26_VSD_OBE_CTRL_086_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95035C RW 0x0000_0000
	UINT32 reg_body_head_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_body_head_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_body_head_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_body_head_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O26_VSD_OBE_CTRL_087_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950360 RW 0x0000_0000
	UINT32 reg_head_body_lut_y2             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x2             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y3             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x3             :8;	//(31:24,NA,0x00) //head-body
	};
}PE_O26_VSD_OBE_CTRL_088_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950364 RW 0x0000_0000
	UINT32 reg_head_body_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_head_body_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_head_body_lut_y1             :8;	//(23:16,NA,0x00) //
	UINT32 reg_head_body_lut_x1             :8;	//(31:24,NA,0x00) //
	};
}PE_O26_VSD_OBE_CTRL_089_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950368 RW 0x0000_0000
	UINT32 reg_txtr_r_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_090_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95036C RW 0x017E_00FF
	UINT32 reg_txtr_r_lut_y1                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x1                :10;	//(25:16,NA,0x17E) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_091_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950370 RW 0x02FD_01FE
	UINT32 reg_txtr_r_lut_y2                :10;	//(9:0,NA,0x1FE) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x2                :10;	//(25:16,NA,0x2FD) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_092_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950374 RW 0x03FF_02FD
	UINT32 reg_txtr_r_lut_y3                :10;	//(9:0,NA,0x2FD) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x3                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_093_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950378 RW 0x03FF_0361
	UINT32 reg_txtr_r_lut_y4                :10;	//(9:0,NA,0x361) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x4                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_094_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95037C RW 0x03FF_03FF
	UINT32 reg_txtr_r_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_r_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_095_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950380 RW 0x0000_0000
	UINT32 reg_txtr_g_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_096_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950384 RW 0x0198_00FF
	UINT32 reg_txtr_g_lut_y1                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x1                :10;	//(25:16,NA,0x198) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_097_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950388 RW 0x0330_01FE
	UINT32 reg_txtr_g_lut_y2                :10;	//(9:0,NA,0x1FE) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x2                :10;	//(25:16,NA,0x330) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_098_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95038C RW 0x03FF_02FD
	UINT32 reg_txtr_g_lut_y3                :10;	//(9:0,NA,0x2FD) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x3                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_099_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950390 RW 0x03FF_0361
	UINT32 reg_txtr_g_lut_y4                :10;	//(9:0,NA,0x361) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x4                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950394 RW 0x03FF_03FF
	UINT32 reg_txtr_g_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_g_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950398 RW 0x0000_0000
	UINT32 reg_txtr_b_lut_y0                :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x0                :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95039C RW 0x01B1_00FF
	UINT32 reg_txtr_b_lut_y1                :10;	//(9:0,NA,0x0FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x1                :10;	//(25:16,NA,0x1B1) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503A0 RW 0x0363_01FE
	UINT32 reg_txtr_b_lut_y2                :10;	//(9:0,NA,0x1FE) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x2                :10;	//(25:16,NA,0x363) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503A4 RW 0x03FF_02FD
	UINT32 reg_txtr_b_lut_y3                :10;	//(9:0,NA,0x2FD) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x3                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503A8 RW 0x03FF_0361
	UINT32 reg_txtr_b_lut_y4                :10;	//(9:0,NA,0x361) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x4                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503AC RW 0x03FF_03FF
	UINT32 reg_txtr_b_lut_y5                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_txtr_b_lut_x5                :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_VSD_OBE_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503F8 RW 0xFFFF_7EC9
	UINT32 reg_txtr_gain_lut_y2             :8;	//(7:0,NA,0xC9) //
	UINT32 reg_txtr_gain_lut_x2             :8;	//(15:8,NA,0x7E) //
	UINT32 reg_txtr_gain_lut_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_txtr_gain_lut_x3             :8;	//(31:24,NA,0xFF) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9503FC RW 0x3F64_0000
	UINT32 reg_txtr_gain_lut_y0             :8;	//(7:0,NA,0x00) //
	UINT32 reg_txtr_gain_lut_x0             :8;	//(15:8,NA,0x00) //
	UINT32 reg_txtr_gain_lut_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_txtr_gain_lut_x1             :8;	//(31:24,NA,0x3F) //o22/f22 4pt
	};
}PE_O26_VSD_OBE_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950400 RW 0x03C0_021C
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x021C) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x03C0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950404 RW 0x0781_0439
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x439) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x781) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950408 RW 0x03E9_0321
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x0321) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x03E9) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95040C RW 0x0A29_0565
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x0565) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0x0A29) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950410 RW 0x03C0_021C
	UINT32 reg_win_w0_y0                    :13;	//(12:0,NA,0x021C) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x0                    :13;	//(28:16,NA,0x03C0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_enable                   :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950414 RW 0x0781_0439
	UINT32 reg_win_w0_y1                    :13;	//(12:0,NA,0x0439) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w0_x1                    :13;	//(28:16,NA,0x0781) //
	UINT32 resvd1                           :2;
	UINT32 reg_win0_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950418 RW 0x03E9_0321
	UINT32 reg_win_w1_y0                    :13;	//(12:0,NA,0x0321) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x0                    :13;	//(28:16,NA,0x03E9) //
	UINT32 resvd1                           :2;
	UINT32 reg_win1_enable                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95041C RW 0x0A29_0565
	UINT32 reg_win_w1_y1                    :13;	//(12:0,NA,0x0565) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_w1_x1                    :13;	//(28:16,NA,0x0A29) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_outside                  :1;	//(31,NA,0x0) //
	};
}PE_O26_VSD_OBE_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950420 RW 0xFFFF_80A0
	UINT32 reg_hist_body_gain_lut_y2        :8;	//(7:0,NA,0xA0) //
	UINT32 reg_hist_body_gain_lut_x2        :8;	//(15:8,NA,0x80) //
	UINT32 reg_hist_body_gain_lut_y3        :8;	//(23:16,NA,0xFF) //
	UINT32 reg_hist_body_gain_lut_x3        :8;	//(31:24,NA,0xFF) //o22/f22 4pt for hist
	};
}PE_O26_VSD_OBE_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950424 RW 0x4020_0000
	UINT32 reg_hist_body_gain_lut_y0        :8;	//(7:0,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_x0        :8;	//(15:8,NA,0x00) //
	UINT32 reg_hist_body_gain_lut_y1        :8;	//(23:16,NA,0x20) //
	UINT32 reg_hist_body_gain_lut_x1        :8;	//(31:24,NA,0x40) //o22/f22 4pt for hist
	};
}PE_O26_VSD_OBE_CTRL_137_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950428 RW 0x1000_7D6D
	UINT32 reg_mcsc_coef1                   :15;	//(14:0,NA,0x7D6D) //O26
	UINT32 resvd0                           :1;
	UINT32 reg_mcsc_coef0                   :15;	//(30:16,NA,0x1000) //O26
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_138_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95042C RW 0x7710_1000
	UINT32 reg_mcsc_coef3                   :15;	//(14:0,NA,0x1000) //O26
	UINT32 resvd0                           :1;
	UINT32 reg_mcsc_coef2                   :15;	//(30:16,NA,0x7710) //O26
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_139_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950430 RW 0x1D6E_0000
	UINT32 reg_mcsc_coef5                   :15;	//(14:0,NA,0x0000) //O26
	UINT32 resvd0                           :1;
	UINT32 reg_mcsc_coef4                   :15;	//(30:16,NA,0x1D6E) //O26
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_140_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950434 RW 0x1000_0000
	UINT32 reg_mcsc_coef7                   :15;	//(14:0,NA,0x0000) //O26
	UINT32 resvd0                           :1;
	UINT32 reg_mcsc_coef6                   :15;	//(30:16,NA,0x1000) //O26
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_141_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950438 RW 0x1711_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mcsc_coef8                   :15;	//(30:16,NA,0x1711) //O26
	UINT32 resvd1                           :1;
	};
}PE_O26_VSD_OBE_CTRL_142_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC95043C RW 0x0000_0600
	UINT32 reg_mcsc_ofst1                   :11;	//(10:0,NA,0x0600) //O26
	UINT32 resvd0                           :5;
	UINT32 reg_mcsc_ofst0                   :11;	//(26:16,NA,0x0000) //O26
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_143_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950440 RW 0x0600_0000
	UINT32 reg_mcsc_ofst3                   :11;	//(10:0,NA,0x0000) //O26
	UINT32 resvd0                           :5;
	UINT32 reg_mcsc_ofst2                   :11;	//(26:16,NA,0x0600) //O26
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_144_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950444 RW 0x0000_0000
	UINT32 reg_mcsc_ofst5                   :11;	//(10:0,NA,0x0000) //O26
	UINT32 resvd0                           :5;
	UINT32 reg_mcsc_ofst4                   :11;	//(26:16,NA,0x0000) //O26
	UINT32 resvd1                           :5;
	};
}PE_O26_VSD_OBE_CTRL_145_T;

typedef struct {
	PE_O26_VSD_OBE_CTRL_000_T                         reg_obe_ctrl_000;	//0xCC950200
	PE_O26_VSD_OBE_CTRL_001_T                         reg_obe_ctrl_001;	//0xCC950204
	PE_O26_VSD_OBE_CTRL_002_T                         reg_obe_ctrl_002;	//0xCC950208
	PE_O26_VSD_OBE_CTRL_003_T                         reg_obe_ctrl_003;	//0xCC95020C
	PE_O26_VSD_OBE_CTRL_004_T                         reg_obe_ctrl_004;	//0xCC950210
	PE_O26_VSD_OBE_CTRL_005_T                         reg_obe_ctrl_005;	//0xCC950214
	PE_O26_VSD_OBE_IND_CTRL_0_T                     reg_obe_ind_ctrl_0;	//0xCC950218
	PE_O26_VSD_OBE_IND_CTRL_1_T                     reg_obe_ind_ctrl_1;	//0xCC95021C
	PE_O26_VSD_OBE_IND_CTRL_2_T                     reg_obe_ind_ctrl_2;	//0xCC950220
	PE_O26_VSD_OBE_CTRL_009_T                         reg_obe_ctrl_009;	//0xCC950224
	PE_O26_VSD_OBE_CTRL_010_T                         reg_obe_ctrl_010;	//0xCC950228
	PE_O26_VSD_OBE_CTRL_011_T                         reg_obe_ctrl_011;	//0xCC95022C
	PE_O26_VSD_OBE_CTRL_012_T                         reg_obe_ctrl_012;	//0xCC950230
	PE_O26_VSD_OBE_CTRL_013_T                         reg_obe_ctrl_013;	//0xCC950234
	PE_O26_VSD_OBE_CTRL_014_T                         reg_obe_ctrl_014;	//0xCC950238
	PE_O26_VSD_OBE_CTRL_015_T                         reg_obe_ctrl_015;	//0xCC95023C
	PE_O26_VSD_OBE_CTRL_016_T                         reg_obe_ctrl_016;	//0xCC950240
	PE_O26_VSD_OBE_CTRL_017_T                         reg_obe_ctrl_017;	//0xCC950244
	PE_O26_VSD_OBE_CTRL_018_T                         reg_obe_ctrl_018;	//0xCC950248
	PE_O26_VSD_OBE_CTRL_019_T                         reg_obe_ctrl_019;	//0xCC95024C
	PE_O26_VSD_OBE_CTRL_020_T                         reg_obe_ctrl_020;	//0xCC950250
	PE_O26_VSD_OBE_CTRL_021_T                         reg_obe_ctrl_021;	//0xCC950254
	PE_O26_VSD_OBE_CTRL_022_T                         reg_obe_ctrl_022;	//0xCC950258
	PE_O26_VSD_OBE_CTRL_023_T                         reg_obe_ctrl_023;	//0xCC95025C
	PE_O26_VSD_OBE_CTRL_024_T                         reg_obe_ctrl_024;	//0xCC950260
	PE_O26_VSD_OBE_CTRL_025_T                         reg_obe_ctrl_025;	//0xCC950264
	PE_O26_VSD_OBE_CTRL_026_T                         reg_obe_ctrl_026;	//0xCC950268
	PE_O26_VSD_OBE_CTRL_027_T                         reg_obe_ctrl_027;	//0xCC95026C
	PE_O26_VSD_OBE_CTRL_028_T                         reg_obe_ctrl_028;	//0xCC950270
	PE_O26_VSD_OBE_CTRL_029_T                         reg_obe_ctrl_029;	//0xCC950274
	PE_O26_VSD_OBE_CTRL_030_T                         reg_obe_ctrl_030;	//0xCC950278
	PE_O26_VSD_OBE_CTRL_031_T                         reg_obe_ctrl_031;	//0xCC95027C
	PE_O26_VSD_OBE_CTRL_032_T                         reg_obe_ctrl_032;	//0xCC950280
	PE_O26_VSD_OBE_CTRL_033_T                         reg_obe_ctrl_033;	//0xCC950284
	PE_O26_VSD_OBE_CTRL_034_T                         reg_obe_ctrl_034;	//0xCC950288
	PE_O26_VSD_OBE_CTRL_035_T                         reg_obe_ctrl_035;	//0xCC95028C
	PE_O26_VSD_OBE_CTRL_036_T                         reg_obe_ctrl_036;	//0xCC950290
	PE_O26_VSD_OBE_CTRL_037_T                         reg_obe_ctrl_037;	//0xCC950294
	PE_O26_VSD_OBE_CTRL_038_T                         reg_obe_ctrl_038;	//0xCC950298
	PE_O26_VSD_OBE_CTRL_039_T                         reg_obe_ctrl_039;	//0xCC95029C
	PE_O26_VSD_OBE_CTRL_040_T                         reg_obe_ctrl_040;	//0xCC9502A0
	PE_O26_VSD_OBE_CTRL_041_T                         reg_obe_ctrl_041;	//0xCC9502A4
	PE_O26_VSD_OBE_CTRL_042_T                         reg_obe_ctrl_042;	//0xCC9502A8
	PE_O26_VSD_OBE_CTRL_043_T                         reg_obe_ctrl_043;	//0xCC9502AC
	PE_O26_VSD_OBE_CTRL_044_T                         reg_obe_ctrl_044;	//0xCC9502B0
	PE_O26_VSD_OBE_CTRL_045_T                         reg_obe_ctrl_045;	//0xCC9502B4
	PE_O26_VSD_OBE_CTRL_046_T                         reg_obe_ctrl_046;	//0xCC9502B8
	PE_O26_VSD_OBE_CTRL_047_T                         reg_obe_ctrl_047;	//0xCC9502BC
	PE_O26_VSD_OBE_CTRL_048_T                         reg_obe_ctrl_048;	//0xCC9502C0
	PE_O26_VSD_OBE_CTRL_049_T                         reg_obe_ctrl_049;	//0xCC9502C4
	PE_O26_VSD_OBE_CTRL_050_T                         reg_obe_ctrl_050;	//0xCC9502C8
	PE_O26_VSD_OBE_CTRL_051_T                         reg_obe_ctrl_051;	//0xCC9502CC
	PE_O26_VSD_OBE_CTRL_052_T                         reg_obe_ctrl_052;	//0xCC9502D0
	PE_O26_VSD_OBE_CTRL_053_T                         reg_obe_ctrl_053;	//0xCC9502D4
	PE_O26_VSD_OBE_CTRL_054_T                         reg_obe_ctrl_054;	//0xCC9502D8
	PE_O26_VSD_OBE_CTRL_055_T                         reg_obe_ctrl_055;	//0xCC9502DC
	PE_O26_VSD_OBE_CTRL_056_T                         reg_obe_ctrl_056;	//0xCC9502E0
	PE_O26_VSD_OBE_CTRL_057_T                         reg_obe_ctrl_057;	//0xCC9502E4
	PE_O26_VSD_OBE_CTRL_058_T                         reg_obe_ctrl_058;	//0xCC9502E8
	PE_O26_VSD_OBE_CTRL_059_T                         reg_obe_ctrl_059;	//0xCC9502EC
	PE_O26_VSD_OBE_CTRL_060_T                         reg_obe_ctrl_060;	//0xCC9502F0
	PE_O26_VSD_OBE_CTRL_061_T                         reg_obe_ctrl_061;	//0xCC9502F4
	PE_O26_VSD_OBE_CTRL_062_T                         reg_obe_ctrl_062;	//0xCC9502F8
	PE_O26_VSD_OBE_CTRL_063_T                         reg_obe_ctrl_063;	//0xCC9502FC
	UINT32                                               reserved0;	//0xCC950300
	UINT32                                               reserved1;	//0xCC950304
	UINT32                                               reserved2;	//0xCC950308
	UINT32                                               reserved3;	//0xCC95030C
	UINT32                                               reserved4;	//0xCC950310
	UINT32                                               reserved5;	//0xCC950314
	UINT32                                               reserved6;	//0xCC950318
	UINT32                                               reserved7;	//0xCC95031C
	UINT32                                               reserved8;	//0xCC950320
	UINT32                                               reserved9;	//0xCC950324
	UINT32                                              reserved10;	//0xCC950328
	UINT32                                              reserved11;	//0xCC95032C
	UINT32                                              reserved12;	//0xCC950330
	UINT32                                              reserved13;	//0xCC950334
	UINT32                                              reserved14;	//0xCC950338
	UINT32                                              reserved15;	//0xCC95033C
	UINT32                                              reserved16;	//0xCC950340
	UINT32                                              reserved17;	//0xCC950344
	PE_O26_VSD_OBE_CTRL_082_T                         reg_obe_ctrl_082;	//0xCC950348
	PE_O26_VSD_OBE_CTRL_083_T                         reg_obe_ctrl_083;	//0xCC95034C
	PE_O26_VSD_OBE_CTRL_084_T                         reg_obe_ctrl_084;	//0xCC950350
	PE_O26_VSD_OBE_CTRL_085_T                         reg_obe_ctrl_085;	//0xCC950354
	PE_O26_VSD_OBE_CTRL_086_T                         reg_obe_ctrl_086;	//0xCC950358
	PE_O26_VSD_OBE_CTRL_087_T                         reg_obe_ctrl_087;	//0xCC95035C
	PE_O26_VSD_OBE_CTRL_088_T                         reg_obe_ctrl_088;	//0xCC950360
	PE_O26_VSD_OBE_CTRL_089_T                         reg_obe_ctrl_089;	//0xCC950364
	PE_O26_VSD_OBE_CTRL_090_T                         reg_obe_ctrl_090;	//0xCC950368
	PE_O26_VSD_OBE_CTRL_091_T                         reg_obe_ctrl_091;	//0xCC95036C
	PE_O26_VSD_OBE_CTRL_092_T                         reg_obe_ctrl_092;	//0xCC950370
	PE_O26_VSD_OBE_CTRL_093_T                         reg_obe_ctrl_093;	//0xCC950374
	PE_O26_VSD_OBE_CTRL_094_T                         reg_obe_ctrl_094;	//0xCC950378
	PE_O26_VSD_OBE_CTRL_095_T                         reg_obe_ctrl_095;	//0xCC95037C
	PE_O26_VSD_OBE_CTRL_096_T                         reg_obe_ctrl_096;	//0xCC950380
	PE_O26_VSD_OBE_CTRL_097_T                         reg_obe_ctrl_097;	//0xCC950384
	PE_O26_VSD_OBE_CTRL_098_T                         reg_obe_ctrl_098;	//0xCC950388
	PE_O26_VSD_OBE_CTRL_099_T                         reg_obe_ctrl_099;	//0xCC95038C
	PE_O26_VSD_OBE_CTRL_100_T                         reg_obe_ctrl_100;	//0xCC950390
	PE_O26_VSD_OBE_CTRL_101_T                         reg_obe_ctrl_101;	//0xCC950394
	PE_O26_VSD_OBE_CTRL_102_T                         reg_obe_ctrl_102;	//0xCC950398
	PE_O26_VSD_OBE_CTRL_103_T                         reg_obe_ctrl_103;	//0xCC95039C
	PE_O26_VSD_OBE_CTRL_104_T                         reg_obe_ctrl_104;	//0xCC9503A0
	PE_O26_VSD_OBE_CTRL_105_T                         reg_obe_ctrl_105;	//0xCC9503A4
	PE_O26_VSD_OBE_CTRL_106_T                         reg_obe_ctrl_106;	//0xCC9503A8
	PE_O26_VSD_OBE_CTRL_107_T                         reg_obe_ctrl_107;	//0xCC9503AC
	UINT32                                              reserved18;	//0xCC9503B0
	UINT32                                              reserved19;	//0xCC9503B4
	UINT32                                              reserved20;	//0xCC9503B8
	UINT32                                              reserved21;	//0xCC9503BC
	UINT32                                              reserved22;	//0xCC9503C0
	UINT32                                              reserved23;	//0xCC9503C4
	UINT32                                              reserved24;	//0xCC9503C8
	UINT32                                              reserved25;	//0xCC9503CC
	UINT32                                              reserved26;	//0xCC9503D0
	UINT32                                              reserved27;	//0xCC9503D4
	UINT32                                              reserved28;	//0xCC9503D8
	UINT32                                              reserved29;	//0xCC9503DC
	UINT32                                              reserved30;	//0xCC9503E0
	UINT32                                              reserved31;	//0xCC9503E4
	UINT32                                              reserved32;	//0xCC9503E8
	UINT32                                              reserved33;	//0xCC9503EC
	UINT32                                              reserved34;	//0xCC9503F0
	UINT32                                              reserved35;	//0xCC9503F4
	PE_O26_VSD_OBE_CTRL_126_T                         reg_obe_ctrl_126;	//0xCC9503F8
	PE_O26_VSD_OBE_CTRL_127_T                         reg_obe_ctrl_127;	//0xCC9503FC
	PE_O26_VSD_OBE_CTRL_128_T                         reg_obe_ctrl_128;	//0xCC950400
	PE_O26_VSD_OBE_CTRL_129_T                         reg_obe_ctrl_129;	//0xCC950404
	PE_O26_VSD_OBE_CTRL_130_T                         reg_obe_ctrl_130;	//0xCC950408
	PE_O26_VSD_OBE_CTRL_131_T                         reg_obe_ctrl_131;	//0xCC95040C
	PE_O26_VSD_OBE_CTRL_132_T                         reg_obe_ctrl_132;	//0xCC950410
	PE_O26_VSD_OBE_CTRL_133_T                         reg_obe_ctrl_133;	//0xCC950414
	PE_O26_VSD_OBE_CTRL_134_T                         reg_obe_ctrl_134;	//0xCC950418
	PE_O26_VSD_OBE_CTRL_135_T                         reg_obe_ctrl_135;	//0xCC95041C
	PE_O26_VSD_OBE_CTRL_136_T                         reg_obe_ctrl_136;	//0xCC950420
	PE_O26_VSD_OBE_CTRL_137_T                         reg_obe_ctrl_137;	//0xCC950424
	PE_O26_VSD_OBE_CTRL_138_T                         reg_obe_ctrl_138;	//0xCC950428
	PE_O26_VSD_OBE_CTRL_139_T                         reg_obe_ctrl_139;	//0xCC95042C
	PE_O26_VSD_OBE_CTRL_140_T                         reg_obe_ctrl_140;	//0xCC950430
	PE_O26_VSD_OBE_CTRL_141_T                         reg_obe_ctrl_141;	//0xCC950434
	PE_O26_VSD_OBE_CTRL_142_T                         reg_obe_ctrl_142;	//0xCC950438
	PE_O26_VSD_OBE_CTRL_143_T                         reg_obe_ctrl_143;	//0xCC95043C
	PE_O26_VSD_OBE_CTRL_144_T                         reg_obe_ctrl_144;	//0xCC950440
	PE_O26_VSD_OBE_CTRL_145_T                         reg_obe_ctrl_145;	//0xCC950444
}PE_VSD_OBE_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E00 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0:0,NA,0x0) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1:1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2:2,NA,0x0) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O26_DTM_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E04 RW 0x0438_0780
	UINT32 width                            :14;	//(13:0,NA,0x780) //width
	UINT32 resvd0                           :2;
	UINT32 height                           :14;	//(29:16,NA,0x438) //height
	UINT32 resvd1                           :2;
	};
}PE_O26_DTM_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E08 RW 0x0100_0000
	UINT32 resvd0                           :1;
	UINT32 reg_va_cnt_en                    :1;	//(1:1,NA,0x0) //1: va count enable for DTM_TOP_CTRL_03
	UINT32 dtm_disp_detour                  :1;	//(2:2,NA,0x0) //1: display tone mapping detour
	UINT32 resvd1                           :1;
	UINT32 reg_use_own_lut_en               :1;	//(4:4,NA,0x0) //0:use luminanace LUT channel G hif	1:use own LUT hif(B/R)(WR only)
	UINT32 resvd2                           :19;
	UINT32 reg_master_en                    :1;	//(24:24,NA,0x1) //LUT master enable
	UINT32 resvd3                           :7;
	};
}PE_O26_DTM_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E0C RO 0x0000_0000
	UINT32 vcnt                             :14;	//(13:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(14:14,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(15:15,NA,0x0) //Vertical Active at PE1 output
	UINT32 vcnt2                            :14;	//(29:16,NA,0x0) //vertical line number
	UINT32 resvd                            :2;
	};
}PE_O26_DTM_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E10 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O26_DTM_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E14 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,NA,0x14) //vdpulse position for register loading
	};
}PE_O26_DTM_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E20 RW 0x0000_0000
	UINT32 dummy_00                         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DTM_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E24 RW 0x0000_0000
	UINT32 dummy_01                         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DTM_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E28 RW 0x0000_0000
	UINT32 dummy_02                         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DTM_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E2C RW 0x0000_0000
	UINT32 dummy_03                         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DTM_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E40 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0:0,NA,0x1) //
	UINT32 resvd                            :31;
	};
}PE_O26_DTM_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E44 RW 0x0AD9_00F3
	UINT32 r_csc1st_coef1                   :15;	//(14:0,NA,0x0F3) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,NA,0xAD9) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E48 RW 0x0434_0000
	UINT32 r_csc1st_coef3                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,NA,0x434) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E4C RW 0x0000_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E50 RW 0x0000_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E54 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E58 RW 0x0000_0000
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DTM_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E5C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DTM_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E60 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DTM_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E70 RW 0x0000_0000
	UINT32 luminance_lut_enable             :1;	//(0:0,NA,0x0) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,NA,0x0) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,NA,0x0) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,NA,0x0) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,NA,0x0) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,NA,0x0) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,NA,0x0) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :3;
	UINT32 window_cg_disable                :1;	//(20:20,NA,0x0) //clock gating disable
	UINT32 resvd3                           :11;
	};
}PE_O26_DTM_LLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E74 RW 0x0000_0000
	UINT32 win_w0_x0                        :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0                        :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E78 RW 0x0437_077F
	UINT32 win_w0_x1                        :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1                        :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E7C RW 0x0000_0000
	UINT32 win_w1_x0                        :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0                        :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E80 RW 0x0437_077F
	UINT32 win_w1_x1                        :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1                        :12;	//(27:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E84 RW 0x03FF_03FF
	UINT32 hif_llut_wdata_y_33rd            :10;	//(9:0,NA,0x3FF) //Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//(25:16,NA,0x3FF) //X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_LLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E88 RW 0x0000_8000
	UINT32 hif_llut0_address                :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut0_load                   :1;	//(8:8,NA,0x0) //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load            :1;	//(11:11,NA,0x0) //0 : LUT load at vactive falling, when hif_llut0_load = 1	1 : LUT load at "hif_llut0_load = 1"
	UINT32 hif_llut0_ai                     :1;	//(12:12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut0_enable                 :1;	//(15:15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O26_DTM_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E8C RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E90 RW 0x0000_8000
	UINT32 hif_llut1_address                :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut1_load                   :1;	//(8:8,NA,0x0) //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load            :1;	//(11:11,NA,0x0) //0 : LUT load at vactive falling, when hif_llut1_load = 1	1 : LUT load at "hif_llut1_load = 1"
	UINT32 hif_llut1_ai                     :1;	//(12:12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut1_enable                 :1;	//(15:15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O26_DTM_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E94 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut1_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E98 RW 0x0000_8000
	UINT32 hif_llut2_address                :4;	//(3:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//(8:8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load            :1;	//(11:11,NA,0x0) //0 : LUT load at vactive falling, when hif_dce_load = 1	1 : LUT load at "hif_dce_load = 1"
	UINT32 hif_llut2_ai                     :1;	//(12:12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut2_enable                 :1;	//(15:15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O26_DTM_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950E9C RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut2_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EA0 RW 0x0020_4060
	UINT32 reg_lut_lum_x3                   :8;	//(7:0,NA,0x60) //
	UINT32 reg_lut_lum_x2                   :8;	//(15:8,NA,0x40) //
	UINT32 reg_lut_lum_x1                   :8;	//(23:16,NA,0x20) //
	UINT32 reg_lut_lum_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EA4 RW 0x80A0_C0FF
	UINT32 reg_lut_lum_x7                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_lum_x6                   :8;	//(15:8,NA,0xC0) //
	UINT32 reg_lut_lum_x5                   :8;	//(23:16,NA,0xA0) //
	UINT32 reg_lut_lum_x4                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EA8 RW 0x80808080
	UINT32 reg_lut_lum_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EAC RW 0x80808080
	UINT32 reg_lut_lum_y7                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y6                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y5                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y4                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EB0 RW 0x0020_4060
	UINT32 reg_lut_sat_x3                   :8;	//(7:0,NA,0x60) //
	UINT32 reg_lut_sat_x2                   :8;	//(15:8,NA,0x40) //
	UINT32 reg_lut_sat_x1                   :8;	//(23:16,NA,0x20) //
	UINT32 reg_lut_sat_x0                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EB4 RW 0x80A0_C0FF
	UINT32 reg_lut_sat_x7                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_sat_x6                   :8;	//(15:8,NA,0xC0) //
	UINT32 reg_lut_sat_x5                   :8;	//(23:16,NA,0xA0) //
	UINT32 reg_lut_sat_x4                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EB8 RW 0x80808080
	UINT32 reg_lut_sat_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y0                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EBC RW 0x80808080
	UINT32 reg_lut_sat_y7                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y6                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y5                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y4                   :8;	//(31:24,NA,0x80) //
	};
}PE_O26_DTM_LUT_LUM_SAT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EE0 RW 0x0000_0000
	UINT32 reg_hue_prsv_en                  :1;	//(0:0,NA,0x0) //enable pin for hue restoration
	UINT32 resvd0                           :3;
	UINT32 reg_sat_prsv_en                  :1;	//(4:4,NA,0x0) //enable pin for saturation preserving
	UINT32 reg_hue_prsv_detour              :1;	//(5:5,NA,0x0) //preserving detour
	UINT32 resvd1                           :2;
	UINT32 reg_hsp_en                       :1;	//(8:8,NA,0x0) //hsp master en
	UINT32 resvd2                           :3;
	UINT32 reg_hue_prsv_cg_disable          :1;	//(12:12,NA,0x0) //clock gating disable
	UINT32 resvd3                           :3;
	UINT32 reg_lum_lut_input_sel            :1;	//(16:16,NA,0x0) //0:Y 1:max_rgb
	UINT32 resvd4                           :3;
	UINT32 reg_hue_lut_gain_sel             :1;	//(20:20,NA,0x0) //0:luma 1:saturation
	UINT32 resvd5                           :3;
	UINT32 reg_sat_lut_gain_sel             :1;	//(24:24,NA,0x0) //0:luma 1:saturation
	UINT32 resvd6                           :7;
	};
}PE_O26_DTM_HUE_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EE4 RW 0xFF00_FF00
	UINT32 reg_sat_prsv_ratio               :8;	//(7:0,NA,0x0) //0:bypass, 255:restored sat
	UINT32 reg_hue_prsv_ratio               :8;	//(15:8,NA,0xFF) //0:bypass, 255:restored hue
	UINT32 reg_tgt_sat_prsv_ratio           :8;	//(23:16,NA,0x0) //0:bypass, 255:restored sat
	UINT32 reg_tgt_hue_prsv_ratio           :8;	//(31:24,NA,0xFF) //0:bypass, 255:restored hue
	};
}PE_O26_DTM_HUE_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EE8 RW 0x0000_00FF
	UINT32 smooth_gain                      :8;	//(7:0,NA,0xFF) //smooth gain
	UINT32 smooth_dbg                       :1;	//(8:8,NA,0x0) //debug blur image
	UINT32 resvd                            :23;
	};
}PE_O26_DTM_SMT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EF0 RW 0x0000_0000
	UINT32 odd_win_w0_x0                    :12;	//(11:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y0                    :12;	//(27:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_ODD_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EF4 RW 0x0437_077F
	UINT32 odd_win_w0_x1                    :12;	//(11:0,NA,0x77F) //win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 odd_win_w0_y1                    :12;	//(27:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_ODD_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EF8 RW 0x0000_0000
	UINT32 odd_win_w1_x0                    :12;	//(11:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 odd_win_w1_y0                    :12;	//(27:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DTM_ODD_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950EFC RW 0x0437_077F
	UINT32 odd_win_w1_x1                    :12;	//(11:0,NA,0x77F) //win_w1_x1
	UINT32 resvd                            :20;
	};
}PE_O26_DTM_ODD_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F00 RW 0x0000_00FF
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F04 RW 0x0064_00FF
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x64) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F08 RW 0x011C_00FF
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x11C) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F0C RW 0x01AA_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x1AA) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F10 RW 0x0238_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x238) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F14 RW 0x02C6_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x2C6) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F18 RW 0x0354_00FF
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x354) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F1C RW 0x03FF_00FF
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DTM_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F20 RW 0x06FF_00FF
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x6) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F24 RW 0x12FF_0DFF
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0xD) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x12) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F28 RW 0x198C_14DC
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xDC) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x14) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x19) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F2C RW 0x2000_1D3C
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x1D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x20) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DTM_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F30 RW 0x6464_3C00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0x3C) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x64) //
	};
}PE_O26_DTM_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F34 RW 0x8CC8_7896
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0x96) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x78) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xC8) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x8C) //
	};
}PE_O26_DTM_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F38 RW 0xBEFF_A0E6
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xE6) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xA0) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xBE) //
	};
}PE_O26_DTM_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F3C RW 0xFFA0_FAFF
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xFA) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0xA0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_DTM_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950F40 RW 0x0000_0300
	UINT32 reg_yy_vv_sel                    :1;	//(0:0,NA,0x0) //0:Y 1:V
	UINT32 resvd0                           :2;
	UINT32 reg_clock_gating_disable         :1;	//(3:3,NA,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_hsv_hsl_sel                  :1;	//(8:8,NA,0x1) //0:HSL 1:HSV
	UINT32 reg_hsv_sat_sel                  :1;	//(9:9,NA,0x1) //1:reduce saturation value in dark area
	UINT32 resvd2                           :22;
	};
}PE_O26_DTM_CRGN_CTRL_16_T;

typedef struct {
	PE_O26_DTM_TOP_CTRL_00_T                           dtm_top_ctrl_00;	//0xCC950E00
	PE_O26_DTM_TOP_CTRL_01_T                           dtm_top_ctrl_01;	//0xCC950E04
	PE_O26_DTM_TOP_CTRL_02_T                           dtm_top_ctrl_02;	//0xCC950E08
	PE_O26_DTM_TOP_CTRL_03_T                           dtm_top_ctrl_03;	//0xCC950E0C
	PE_O26_DTM_TOP_CTRL_04_T                           dtm_top_ctrl_04;	//0xCC950E10
	PE_O26_DTM_TOP_CTRL_05_T                           dtm_top_ctrl_05;	//0xCC950E14
	UINT32                                                      reserved0;	//0xCC950E18
	UINT32                                                      reserved1;	//0xCC950E1C
	PE_O26_DTM_FSW_CTRL_00_T                           dtm_fsw_ctrl_00;	//0xCC950E20
	PE_O26_DTM_FSW_CTRL_01_T                           dtm_fsw_ctrl_01;	//0xCC950E24
	PE_O26_DTM_FSW_CTRL_02_T                           dtm_fsw_ctrl_02;	//0xCC950E28
	PE_O26_DTM_FSW_CTRL_03_T                           dtm_fsw_ctrl_03;	//0xCC950E2C
	UINT32                                                      reserved2;	//0xCC950E30
	UINT32                                                      reserved3;	//0xCC950E34
	UINT32                                                      reserved4;	//0xCC950E38
	UINT32                                                      reserved5;	//0xCC950E3C
	PE_O26_DTM_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0xCC950E40
	PE_O26_DTM_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0xCC950E44
	PE_O26_DTM_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0xCC950E48
	PE_O26_DTM_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0xCC950E4C
	PE_O26_DTM_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0xCC950E50
	PE_O26_DTM_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0xCC950E54
	PE_O26_DTM_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0xCC950E58
	PE_O26_DTM_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0xCC950E5C
	PE_O26_DTM_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0xCC950E60
	UINT32                                                      reserved6;	//0xCC950E64
	UINT32                                                      reserved7;	//0xCC950E68
	UINT32                                                      reserved8;	//0xCC950E6C
	PE_O26_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xCC950E70
	PE_O26_DTM_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0xCC950E74
	PE_O26_DTM_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0xCC950E78
	PE_O26_DTM_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0xCC950E7C
	PE_O26_DTM_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0xCC950E80
	PE_O26_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xCC950E84
	PE_O26_DTM_LLUT0_IA_CTRL_T                       dtm_llut0_ia_ctrl;	//0xCC950E88
	PE_O26_DTM_LLUT0_IA_DATA_T                       dtm_llut0_ia_data;	//0xCC950E8C
	PE_O26_DTM_LLUT1_IA_CTRL_T                       dtm_llut1_ia_ctrl;	//0xCC950E90
	PE_O26_DTM_LLUT1_IA_DATA_T                       dtm_llut1_ia_data;	//0xCC950E94
	PE_O26_DTM_LLUT2_IA_CTRL_T                       dtm_llut2_ia_ctrl;	//0xCC950E98
	PE_O26_DTM_LLUT2_IA_DATA_T                       dtm_llut2_ia_data;	//0xCC950E9C
	PE_O26_DTM_LUT_LUM_SAT_CTRL_00_T           dtm_lut_lum_sat_ctrl_00;	//0xCC950EA0
	PE_O26_DTM_LUT_LUM_SAT_CTRL_01_T           dtm_lut_lum_sat_ctrl_01;	//0xCC950EA4
	PE_O26_DTM_LUT_LUM_SAT_CTRL_02_T           dtm_lut_lum_sat_ctrl_02;	//0xCC950EA8
	PE_O26_DTM_LUT_LUM_SAT_CTRL_03_T           dtm_lut_lum_sat_ctrl_03;	//0xCC950EAC
	PE_O26_DTM_LUT_LUM_SAT_CTRL_04_T           dtm_lut_lum_sat_ctrl_04;	//0xCC950EB0
	PE_O26_DTM_LUT_LUM_SAT_CTRL_05_T           dtm_lut_lum_sat_ctrl_05;	//0xCC950EB4
	PE_O26_DTM_LUT_LUM_SAT_CTRL_06_T           dtm_lut_lum_sat_ctrl_06;	//0xCC950EB8
	PE_O26_DTM_LUT_LUM_SAT_CTRL_07_T           dtm_lut_lum_sat_ctrl_07;	//0xCC950EBC
	UINT32                                                      reserved9;	//0xCC950EC0
	UINT32                                                  reserved10;	//0xCC950EC4
	UINT32                                                  reserved11;	//0xCC950EC8
	UINT32                                                  reserved12;	//0xCC950ECC
	UINT32                                                  reserved13;	//0xCC950ED0
	UINT32                                                  reserved14;	//0xCC950ED4
	UINT32                                                  reserved15;	//0xCC950ED8
	UINT32                                                  reserved16;	//0xCC950EDC
	PE_O26_DTM_HUE_SAT_CTRL_00_T                   dtm_hue_sat_ctrl_00;	//0xCC950EE0
	PE_O26_DTM_HUE_SAT_CTRL_01_T                   dtm_hue_sat_ctrl_01;	//0xCC950EE4
	PE_O26_DTM_SMT_CTRL_00_T                           dtm_smt_ctrl_00;	//0xCC950EE8
	UINT32                                                  reserved17;	//0xCC950EEC
	PE_O26_DTM_ODD_LLUT_CTRL_01_T                 dtm_odd_llut_ctrl_01;	//0xCC950EF0
	PE_O26_DTM_ODD_LLUT_CTRL_02_T                 dtm_odd_llut_ctrl_02;	//0xCC950EF4
	PE_O26_DTM_ODD_LLUT_CTRL_03_T                 dtm_odd_llut_ctrl_03;	//0xCC950EF8
	PE_O26_DTM_ODD_LLUT_CTRL_04_T                 dtm_odd_llut_ctrl_04;	//0xCC950EFC
	PE_O26_DTM_CRGN_CTRL_00_T                         dtm_crgn_ctrl_00;	//0xCC950F00
	PE_O26_DTM_CRGN_CTRL_01_T                         dtm_crgn_ctrl_01;	//0xCC950F04
	PE_O26_DTM_CRGN_CTRL_02_T                         dtm_crgn_ctrl_02;	//0xCC950F08
	PE_O26_DTM_CRGN_CTRL_03_T                         dtm_crgn_ctrl_03;	//0xCC950F0C
	PE_O26_DTM_CRGN_CTRL_04_T                         dtm_crgn_ctrl_04;	//0xCC950F10
	PE_O26_DTM_CRGN_CTRL_05_T                         dtm_crgn_ctrl_05;	//0xCC950F14
	PE_O26_DTM_CRGN_CTRL_06_T                         dtm_crgn_ctrl_06;	//0xCC950F18
	PE_O26_DTM_CRGN_CTRL_07_T                         dtm_crgn_ctrl_07;	//0xCC950F1C
	PE_O26_DTM_CRGN_CTRL_08_T                         dtm_crgn_ctrl_08;	//0xCC950F20
	PE_O26_DTM_CRGN_CTRL_09_T                         dtm_crgn_ctrl_09;	//0xCC950F24
	PE_O26_DTM_CRGN_CTRL_10_T                         dtm_crgn_ctrl_10;	//0xCC950F28
	PE_O26_DTM_CRGN_CTRL_11_T                         dtm_crgn_ctrl_11;	//0xCC950F2C
	PE_O26_DTM_CRGN_CTRL_12_T                         dtm_crgn_ctrl_12;	//0xCC950F30
	PE_O26_DTM_CRGN_CTRL_13_T                         dtm_crgn_ctrl_13;	//0xCC950F34
	PE_O26_DTM_CRGN_CTRL_14_T                         dtm_crgn_ctrl_14;	//0xCC950F38
	PE_O26_DTM_CRGN_CTRL_15_T                         dtm_crgn_ctrl_15;	//0xCC950F3C
	PE_O26_DTM_CRGN_CTRL_16_T                         dtm_crgn_ctrl_16;	//0xCC950F40
}PE_VSD_DTM_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A00 RW 0x0009_5101
	UINT32 reg_amg_en                       :1;	//(0:0,NA,1) //AMG core enable
	UINT32 reg_set_pos_x2_mode              :1;	//(1:1,NA,0) //Position setting x2 mode (for BOX_SET, REGION_GAIN, GRM REGION)
	UINT32 reg_fix_mvf_mode_en              :1;	//(2:2,NA,0) //Fix MVF mode enable (forcing MVX/Y to 0, MV mode to 3)
	UINT32 resvd0                           :1;
	UINT32 reg_fsm_mode_sel                 :2;	//(5:4,NA,0) //FSM mode selection	0 : run core with 1-init	1 : run core with 2-init	2 : run core with 4-init
	UINT32 reg_fsm_rst                      :1;	//(6:6,NA,0) //Manual reset FSM
	UINT32 reg_fsm_auto_rst_en              :1;	//(7:7,NA,0) //Auto reset FSM enable (for abnormal init case)
	UINT32 reg_top_protocol_type            :1;	//(8:8,NA,1) //0: sync-based, 1: valid-based
	UINT32 reg_manual_run_cnt_en            :1;	//(9:9,NA,0) //Manual run count (run ID) enable
	UINT32 reg_manual_run_cnt               :2;	//(11:10,NA,0) //Manual run count (run ID)	0 : run state 0 (HEAD histogram)	1 : run state 1 (HEAD gen map)	2 : run state 2 (BODY histogram)	3 : run state 3 (BODY gen map)
	UINT32 reg_420to422_flt_en              :1;	//(12:12,NA,1) //420 to 422 filter enable	0 : repeatition mode	1 : 2-tab average mode
	UINT32 reg_420to422_buf_mode            :1;	//(13:13,NA,0) //420 to 422 ring-buffer mode
	UINT32 reg_420to422_rpt_cnt             :2;	//(15:14,NA,1) //420 to 422 vertical repeat count
	UINT32 reg_422to444_flt_en              :1;	//(16:16,NA,1) //422 to 444 filter enable	0 : repeatition mode	1 : 2-tab average mode
	UINT32 reg_grm_hist_rst                 :1;	//(17:17,NA,0) //Manual reset GRM histogram
	UINT32 reg_mtb_iir_off                  :1;	//(18:18,NA,0) //MTB IIR off (0: disable, 1: enable)
	UINT32 reg_buf_detour_test              :1;	//(19:19,NA,1) //Buffer detour enable (for test)
	UINT32 reg_mvf_vfast                    :1;	//(20:20,NA,0) //MV V-fast mode (0: off, 1: on)
	UINT32 resvd1                           :11;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A04 RW 0x0087_00F0
	UINT32 reg_wid                          :9;	//(8:0,NA,240) //processing width (default: 240)
	UINT32 resvd0                           :7;
	UINT32 reg_hei                          :9;	//(24:16,NA,135) //processing height (default: 135)
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A08 RW 0x0118_0001
	UINT32 reg_use_extern_valid             :1;	//(0:0,NA,1) //Use external valid as dummy valid
	UINT32 reg_use_blank_period_cnt         :1;	//(1:1,NA,0) //Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,280) //Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A0C RW 0x3210_0064
	UINT32 reg_pic_delay_d2i                :16;	//(15:0,NA,100) //Delay of done to next init
	UINT32 reg_pic_delay_i2s                :8;	//(23:16,NA,16) //Delay of init to start
	UINT32 reg_flush_cnt                    :8;	//(31:24,NA,50) //Flush counter
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A10 RW 0x0001_0000
	UINT32 reg_mif_urgency                  :1;	//(0:0,NA,0) //Urgency = mif_bundle[59]
	UINT32 resvd0                           :7;
	UINT32 reg_mif_prefetch_line            :8;	//(15:8,NA,0) //MV pre-fetch line count
	UINT32 reg_mvf_prec                     :1;	//(16:16,NA,1) //MV precision (0: L0, 1: L1)
	UINT32 resvd1                           :15;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A14 RW 0x0000_0000
	UINT32 reg_force_mvf_mv_x               :8;	//(7:0,NA,0) //Force MVF MVX
	UINT32 reg_force_mvf_mv_y               :8;	//(15:8,NA,0) //Force MVF MVY
	UINT32 reg_force_mvf_mv_mode            :2;	//(17:16,NA,0) //Force MVF MV mode
	UINT32 resvd                            :13;
	UINT32 reg_force_mvf_enable             :1;	//(31:31,NA,0) //Force MVF enable
	};
}PE_O26_AMG0_HEAD_AMG_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A18 RW 0x0000_0000
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
}PE_O26_AMG0_HEAD_PAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A20 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :21;
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0 : Y	1 : Cb	2 : Cr	3 : Depth
	UINT32 resvd                            :30;
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A28 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 reg_read_hist_00_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 0)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A2C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 reg_read_hist_01_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 1)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A30 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 reg_read_hist_02_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 2)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A34 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 reg_read_hist_03_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 3)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A38 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 reg_read_hist_04_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 4)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A3C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 reg_read_hist_05_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 5)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A40 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 reg_read_hist_06_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 6)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A44 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 reg_read_hist_07_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 7)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A48 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 reg_read_hist_08_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 8)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A4C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 reg_read_hist_09_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 9)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A50 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 reg_read_hist_10_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 10)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A54 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 reg_read_hist_11_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 11)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A58 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 reg_read_hist_12_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 12)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A5C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 reg_read_hist_13_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 13)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A60 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 reg_read_hist_14_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 14)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A64 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 reg_read_hist_15_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 15)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A68 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 reg_read_hist_16_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 16)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A6C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 reg_read_hist_17_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 17)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A70 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 reg_read_hist_18_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 18)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A74 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 reg_read_hist_19_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 19)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A78 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 reg_read_hist_20_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 20)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A7C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 reg_read_hist_21_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 21)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A80 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 reg_read_hist_22_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 22)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A84 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 reg_read_hist_23_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 23)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A88 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 reg_read_hist_24_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 24)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A8C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 reg_read_hist_25_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 25)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A90 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 reg_read_hist_26_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 26)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A94 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 reg_read_hist_27_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 27)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A98 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 reg_read_hist_28_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 28)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14A9C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 reg_read_hist_29_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 29)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AA0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 reg_read_hist_30_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 30)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AA4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 reg_read_hist_31_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 31)
	};
}PE_O26_AMG0_HEAD_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AB0 RW 0x0000_0101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0 : Probability map	1 : Ellipse gain map	2 : Probability map (FG)	3 : Probability map (BG)	4 : Probability map (diff)	5 : Box map	6 : Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,0) //Object map output mux selection	0 : HEAD/BODY	1 : Blending	2 : Depth only	3 : Adding
	UINT32 resvd3                           :18;
	};
}PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ABC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AC0 RW 0x0000_0000
	UINT32 resvd0                           :4;
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
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	0 : disable (default, replaced to optional box enable)	1 : enable
	UINT32 resvd1                           :15;
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AC4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ACC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ADC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14AF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O26_AMG0_HEAD_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B00 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 0) ellipse to rect disable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 1) ellipse to rect disable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 2) ellipse to rect disable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 3) ellipse to rect disable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O26_AMG0_HEAD_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O26_AMG0_HEAD_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O26_AMG0_HEAD_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14B80 RW 0x0000_00CC
	UINT32 reg_blur_vcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O26_AMG0_HEAD_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14C20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0 : use manual value	1 : use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0 : use IIR result	1 : use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O26_AMG0_HEAD_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14C24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O26_AMG0_HEAD_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14C30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O26_AMG0_HEAD_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14C34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O26_AMG0_HEAD_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14C38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O26_AMG0_HEAD_LUT_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CB0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :16;	//(15:0,NA,0) //Top input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :9;	//(24:16,NA,0) //Top input (pel, Y) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CB4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :16;	//(15:0,NA,0) //Top input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :9;	//(24:16,NA,0) //Top input (pel, C) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CB8 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :16;	//(15:0,NA,0) //Top input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :9;	//(24:16,NA,0) //Top input (depth map) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CBC RO 0x0000_0000
	UINT32 reg_mon_in_mc_sucfail            :16;	//(15:0,NA,0) //Top input (MC map) success/fail monitoring register
	UINT32 reg_mon_in_mc_fin_vert           :9;	//(24:16,NA,0) //Top input (MC map) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CC0 RO 0x0000_0000
	UINT32 reg_mon_in_basic_sucfail         :16;	//(15:0,NA,0) //Top input (Basic map) success/fail monitoring register
	UINT32 reg_mon_in_basic_fin_vert        :9;	//(24:16,NA,0) //Top input (Basic map) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CC4 RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :16;	//(15:0,NA,0) //Top input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :9;	//(24:16,NA,0) //Top input (IIR feedback) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CC8 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :16;	//(15:0,NA,0) //Top output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :9;	//(24:16,NA,0) //Top output (IIR out) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CCC RO 0x0000_0000
	UINT32 reg_run_1st_flag                 :1;	//(0:0,NA,0) //Top 1st-run processing flag
	UINT32 reg_run_2nd_flag                 :1;	//(1:1,NA,0) //Top 2nd-run processing flag
	UINT32 reg_run_3rd_flag                 :1;	//(2:2,NA,0) //Top 3rd-run processing flag
	UINT32 reg_run_4th_flag                 :1;	//(3:3,NA,0) //Top 4th-run processing flag
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
}PE_O26_AMG0_HEAD_AMG_TOP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CD0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_sucfail           :16;	//(15:0,NA,0) //Core input (pel) success/fail monitoring register
	UINT32 reg_mon_in_pel_fin_vert          :9;	//(24:16,NA,0) //Core input (pel) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CD4 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :16;	//(15:0,NA,0) //Core input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :9;	//(24:16,NA,0) //Core input (depth map) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CD8 RO 0x0000_0000
	UINT32 reg_mon_in_grm_sucfail           :16;	//(15:0,NA,0) //Core input (GRM) success/fail monitoring register
	UINT32 reg_mon_in_grm_fin_vert          :9;	//(24:16,NA,0) //Core input (GRM) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CDC RO 0x0000_0000
	UINT32 reg_mon_in_mtb_sucfail           :16;	//(15:0,NA,0) //Core input (MTB) success/fail monitoring register
	UINT32 reg_mon_in_mtb_fin_vert          :9;	//(24:16,NA,0) //Core input (MTB) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CE0 RO 0x0000_0000
	UINT32 reg_mon_in_iir_sucfail           :16;	//(15:0,NA,0) //Core input (IIR feedback) success/fail monitoring register
	UINT32 reg_mon_in_iir_fin_vert          :9;	//(24:16,NA,0) //Core input (IIR feedback) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CE4 RO 0x0000_0000
	UINT32 reg_mon_out_iir_sucfail          :16;	//(15:0,NA,0) //Core output (IIR out) success/fail monitoring register
	UINT32 reg_mon_out_iir_fin_vert         :9;	//(24:16,NA,0) //Core output (IIR out) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG0_HEAD_AMG_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CF0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_AMG_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CF4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_AMG_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CF8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_AMG_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14CFC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG0_HEAD_AMG_FSW_CTRL_03_T;

typedef struct {
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_00_T                     amg_top_ctrl_00;	//0xCCC14A00
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_01_T                     amg_top_ctrl_01;	//0xCCC14A04
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_02_T                     amg_top_ctrl_02;	//0xCCC14A08
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_03_T                     amg_top_ctrl_03;	//0xCCC14A0C
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_04_T                     amg_top_ctrl_04;	//0xCCC14A10
	PE_O26_AMG0_HEAD_AMG_TOP_CTRL_05_T                     amg_top_ctrl_05;	//0xCCC14A14
	PE_O26_AMG0_HEAD_PAT_CTRL_00_T                             pat_ctrl_00;	//0xCCC14A18
	UINT32                                                       reserved0;	//0xCCC14A1C
	PE_O26_AMG0_HEAD_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCCC14A20
	PE_O26_AMG0_HEAD_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCCC14A24
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_00_T                 histogram_stat_00;	//0xCCC14A28
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_01_T                 histogram_stat_01;	//0xCCC14A2C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_02_T                 histogram_stat_02;	//0xCCC14A30
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_03_T                 histogram_stat_03;	//0xCCC14A34
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_04_T                 histogram_stat_04;	//0xCCC14A38
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_05_T                 histogram_stat_05;	//0xCCC14A3C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_06_T                 histogram_stat_06;	//0xCCC14A40
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_07_T                 histogram_stat_07;	//0xCCC14A44
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_08_T                 histogram_stat_08;	//0xCCC14A48
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_09_T                 histogram_stat_09;	//0xCCC14A4C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_10_T                 histogram_stat_10;	//0xCCC14A50
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_11_T                 histogram_stat_11;	//0xCCC14A54
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_12_T                 histogram_stat_12;	//0xCCC14A58
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_13_T                 histogram_stat_13;	//0xCCC14A5C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_14_T                 histogram_stat_14;	//0xCCC14A60
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_15_T                 histogram_stat_15;	//0xCCC14A64
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_16_T                 histogram_stat_16;	//0xCCC14A68
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_17_T                 histogram_stat_17;	//0xCCC14A6C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_18_T                 histogram_stat_18;	//0xCCC14A70
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_19_T                 histogram_stat_19;	//0xCCC14A74
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_20_T                 histogram_stat_20;	//0xCCC14A78
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_21_T                 histogram_stat_21;	//0xCCC14A7C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_22_T                 histogram_stat_22;	//0xCCC14A80
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_23_T                 histogram_stat_23;	//0xCCC14A84
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_24_T                 histogram_stat_24;	//0xCCC14A88
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_25_T                 histogram_stat_25;	//0xCCC14A8C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_26_T                 histogram_stat_26;	//0xCCC14A90
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_27_T                 histogram_stat_27;	//0xCCC14A94
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_28_T                 histogram_stat_28;	//0xCCC14A98
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_29_T                 histogram_stat_29;	//0xCCC14A9C
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_30_T                 histogram_stat_30;	//0xCCC14AA0
	PE_O26_AMG0_HEAD_HISTOGRAM_STAT_31_T                 histogram_stat_31;	//0xCCC14AA4
	UINT32                                                       reserved1;	//0xCCC14AA8
	UINT32                                                       reserved2;	//0xCCC14AAC
	PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCCC14AB0
	PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCCC14AB4
	PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCCC14AB8
	PE_O26_AMG0_HEAD_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCCC14ABC
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCCC14AC0
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCCC14AC4
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCCC14AC8
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCCC14ACC
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCCC14AD0
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCCC14AD4
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCCC14AD8
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCCC14ADC
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCCC14AE0
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCCC14AE4
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCCC14AE8
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCCC14AEC
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCCC14AF0
	PE_O26_AMG0_HEAD_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCCC14AF4
	UINT32                                                       reserved3;	//0xCCC14AF8
	UINT32                                                       reserved4;	//0xCCC14AFC
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCCC14B00
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCCC14B04
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCCC14B08
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCCC14B0C
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCCC14B10
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCCC14B14
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCCC14B18
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCCC14B1C
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCCC14B20
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCCC14B24
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCCC14B28
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCCC14B2C
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCCC14B30
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCCC14B34
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCCC14B38
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCCC14B3C
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCCC14B40
	PE_O26_AMG0_HEAD_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCCC14B44
	UINT32                                                       reserved5;	//0xCCC14B48
	UINT32                                                       reserved6;	//0xCCC14B4C
	PE_O26_AMG0_HEAD_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCCC14B50
	PE_O26_AMG0_HEAD_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCCC14B54
	UINT32                                                       reserved7;	//0xCCC14B58
	UINT32                                                       reserved8;	//0xCCC14B5C
	PE_O26_AMG0_HEAD_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCCC14B60
	PE_O26_AMG0_HEAD_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCCC14B64
	PE_O26_AMG0_HEAD_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCCC14B68
	PE_O26_AMG0_HEAD_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCCC14B6C
	PE_O26_AMG0_HEAD_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCCC14B70
	PE_O26_AMG0_HEAD_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCCC14B74
	PE_O26_AMG0_HEAD_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCCC14B78
	PE_O26_AMG0_HEAD_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCCC14B7C
	PE_O26_AMG0_HEAD_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCCC14B80
	UINT32                                                       reserved9;	//0xCCC14B84
	UINT32                                                      reserved10;	//0xCCC14B88
	UINT32                                                      reserved11;	//0xCCC14B8C
	UINT32                                                      reserved12;	//0xCCC14B90
	UINT32                                                      reserved13;	//0xCCC14B94
	UINT32                                                      reserved14;	//0xCCC14B98
	UINT32                                                      reserved15;	//0xCCC14B9C
	UINT32                                                      reserved16;	//0xCCC14BA0
	UINT32                                                      reserved17;	//0xCCC14BA4
	UINT32                                                      reserved18;	//0xCCC14BA8
	UINT32                                                      reserved19;	//0xCCC14BAC
	UINT32                                                      reserved20;	//0xCCC14BB0
	UINT32                                                      reserved21;	//0xCCC14BB4
	UINT32                                                      reserved22;	//0xCCC14BB8
	UINT32                                                      reserved23;	//0xCCC14BBC
	UINT32                                                      reserved24;	//0xCCC14BC0
	UINT32                                                      reserved25;	//0xCCC14BC4
	UINT32                                                      reserved26;	//0xCCC14BC8
	UINT32                                                      reserved27;	//0xCCC14BCC
	UINT32                                                      reserved28;	//0xCCC14BD0
	UINT32                                                      reserved29;	//0xCCC14BD4
	UINT32                                                      reserved30;	//0xCCC14BD8
	UINT32                                                      reserved31;	//0xCCC14BDC
	UINT32                                                      reserved32;	//0xCCC14BE0
	UINT32                                                      reserved33;	//0xCCC14BE4
	UINT32                                                      reserved34;	//0xCCC14BE8
	UINT32                                                      reserved35;	//0xCCC14BEC
	UINT32                                                      reserved36;	//0xCCC14BF0
	UINT32                                                      reserved37;	//0xCCC14BF4
	UINT32                                                      reserved38;	//0xCCC14BF8
	UINT32                                                      reserved39;	//0xCCC14BFC
	UINT32                                                      reserved40;	//0xCCC14C00
	UINT32                                                      reserved41;	//0xCCC14C04
	UINT32                                                      reserved42;	//0xCCC14C08
	UINT32                                                      reserved43;	//0xCCC14C0C
	UINT32                                                      reserved44;	//0xCCC14C10
	UINT32                                                      reserved45;	//0xCCC14C14
	UINT32                                                      reserved46;	//0xCCC14C18
	UINT32                                                      reserved47;	//0xCCC14C1C
	PE_O26_AMG0_HEAD_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCCC14C20
	PE_O26_AMG0_HEAD_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCCC14C24
	UINT32                                                      reserved48;	//0xCCC14C28
	UINT32                                                      reserved49;	//0xCCC14C2C
	PE_O26_AMG0_HEAD_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCCC14C30
	PE_O26_AMG0_HEAD_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCCC14C34
	PE_O26_AMG0_HEAD_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCCC14C38
	UINT32                                                      reserved50;	//0xCCC14C3C
	UINT32                                                      reserved51;	//0xCCC14C40
	UINT32                                                      reserved52;	//0xCCC14C44
	UINT32                                                      reserved53;	//0xCCC14C48
	UINT32                                                      reserved54;	//0xCCC14C4C
	UINT32                                                      reserved55;	//0xCCC14C50
	UINT32                                                      reserved56;	//0xCCC14C54
	UINT32                                                      reserved57;	//0xCCC14C58
	UINT32                                                      reserved58;	//0xCCC14C5C
	UINT32                                                      reserved59;	//0xCCC14C60
	UINT32                                                      reserved60;	//0xCCC14C64
	UINT32                                                      reserved61;	//0xCCC14C68
	UINT32                                                      reserved62;	//0xCCC14C6C
	UINT32                                                      reserved63;	//0xCCC14C70
	UINT32                                                      reserved64;	//0xCCC14C74
	UINT32                                                      reserved65;	//0xCCC14C78
	UINT32                                                      reserved66;	//0xCCC14C7C
	UINT32                                                      reserved67;	//0xCCC14C80
	UINT32                                                      reserved68;	//0xCCC14C84
	UINT32                                                      reserved69;	//0xCCC14C88
	UINT32                                                      reserved70;	//0xCCC14C8C
	UINT32                                                      reserved71;	//0xCCC14C90
	UINT32                                                      reserved72;	//0xCCC14C94
	UINT32                                                      reserved73;	//0xCCC14C98
	UINT32                                                      reserved74;	//0xCCC14C9C
	UINT32                                                      reserved75;	//0xCCC14CA0
	UINT32                                                      reserved76;	//0xCCC14CA4
	UINT32                                                      reserved77;	//0xCCC14CA8
	UINT32                                                      reserved78;	//0xCCC14CAC
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_00_T                     amg_top_stat_00;	//0xCCC14CB0
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_01_T                     amg_top_stat_01;	//0xCCC14CB4
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_02_T                     amg_top_stat_02;	//0xCCC14CB8
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_03_T                     amg_top_stat_03;	//0xCCC14CBC
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_04_T                     amg_top_stat_04;	//0xCCC14CC0
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_05_T                     amg_top_stat_05;	//0xCCC14CC4
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_06_T                     amg_top_stat_06;	//0xCCC14CC8
	PE_O26_AMG0_HEAD_AMG_TOP_STAT_07_T                     amg_top_stat_07;	//0xCCC14CCC
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_00_T                   amg_core_stat_00;	//0xCCC14CD0
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_01_T                   amg_core_stat_01;	//0xCCC14CD4
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_02_T                   amg_core_stat_02;	//0xCCC14CD8
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_03_T                   amg_core_stat_03;	//0xCCC14CDC
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_04_T                   amg_core_stat_04;	//0xCCC14CE0
	PE_O26_AMG0_HEAD_AMG_CORE_STAT_05_T                   amg_core_stat_05;	//0xCCC14CE4
	UINT32                                                      reserved79;	//0xCCC14CE8
	UINT32                                                      reserved80;	//0xCCC14CEC
	PE_O26_AMG0_HEAD_AMG_FSW_CTRL_00_T                     amg_fsw_ctrl_00;	//0xCCC14CF0
	PE_O26_AMG0_HEAD_AMG_FSW_CTRL_01_T                     amg_fsw_ctrl_01;	//0xCCC14CF4
	PE_O26_AMG0_HEAD_AMG_FSW_CTRL_02_T                     amg_fsw_ctrl_02;	//0xCCC14CF8
	PE_O26_AMG0_HEAD_AMG_FSW_CTRL_03_T                     amg_fsw_ctrl_03;	//0xCCC14CFC
}PE_AMG_HEAD_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D20 RW 0x0242_0242
	UINT32 reg_hist_coef0_hb                :3;	//(2:0,NA,2) //Histogram coefficient, 0 (HEAD/BODY)
	UINT32 resvd0                           :1;
	UINT32 reg_hist_coef1_hb                :3;	//(6:4,NA,4) //Histogram coefficient, 1 (HEAD/BODY)
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef2_hb                :3;	//(10:8,NA,2) //Histogram coefficient, 2 (HEAD/BODY)
	UINT32 resvd2                           :21;
	};
}PE_O26_AMG1_BODY_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D24 RW 0x0000_0000
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection	0 : Y	1 : Cb	2 : Cr	3 : Depth
	UINT32 resvd                            :30;
	};
}PE_O26_AMG1_BODY_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D28 RO 0x0000_0000
	UINT32 reg_read_hist_00_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 0)
	UINT32 reg_read_hist_00_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 0)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D2C RO 0x0000_0000
	UINT32 reg_read_hist_01_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 1)
	UINT32 reg_read_hist_01_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 1)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D30 RO 0x0000_0000
	UINT32 reg_read_hist_02_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 2)
	UINT32 reg_read_hist_02_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 2)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D34 RO 0x0000_0000
	UINT32 reg_read_hist_03_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 3)
	UINT32 reg_read_hist_03_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 3)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D38 RO 0x0000_0000
	UINT32 reg_read_hist_04_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 4)
	UINT32 reg_read_hist_04_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 4)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D3C RO 0x0000_0000
	UINT32 reg_read_hist_05_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 5)
	UINT32 reg_read_hist_05_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 5)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D40 RO 0x0000_0000
	UINT32 reg_read_hist_06_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 6)
	UINT32 reg_read_hist_06_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 6)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D44 RO 0x0000_0000
	UINT32 reg_read_hist_07_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 7)
	UINT32 reg_read_hist_07_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 7)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D48 RO 0x0000_0000
	UINT32 reg_read_hist_08_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 8)
	UINT32 reg_read_hist_08_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 8)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D4C RO 0x0000_0000
	UINT32 reg_read_hist_09_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 9)
	UINT32 reg_read_hist_09_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 9)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D50 RO 0x0000_0000
	UINT32 reg_read_hist_10_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 10)
	UINT32 reg_read_hist_10_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 10)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D54 RO 0x0000_0000
	UINT32 reg_read_hist_11_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 11)
	UINT32 reg_read_hist_11_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 11)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D58 RO 0x0000_0000
	UINT32 reg_read_hist_12_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 12)
	UINT32 reg_read_hist_12_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 12)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D5C RO 0x0000_0000
	UINT32 reg_read_hist_13_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 13)
	UINT32 reg_read_hist_13_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 13)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D60 RO 0x0000_0000
	UINT32 reg_read_hist_14_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 14)
	UINT32 reg_read_hist_14_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 14)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D64 RO 0x0000_0000
	UINT32 reg_read_hist_15_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 15)
	UINT32 reg_read_hist_15_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 15)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D68 RO 0x0000_0000
	UINT32 reg_read_hist_16_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 16)
	UINT32 reg_read_hist_16_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 16)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D6C RO 0x0000_0000
	UINT32 reg_read_hist_17_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 17)
	UINT32 reg_read_hist_17_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 17)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D70 RO 0x0000_0000
	UINT32 reg_read_hist_18_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 18)
	UINT32 reg_read_hist_18_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 18)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D74 RO 0x0000_0000
	UINT32 reg_read_hist_19_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 19)
	UINT32 reg_read_hist_19_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 19)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D78 RO 0x0000_0000
	UINT32 reg_read_hist_20_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 20)
	UINT32 reg_read_hist_20_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 20)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D7C RO 0x0000_0000
	UINT32 reg_read_hist_21_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 21)
	UINT32 reg_read_hist_21_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 21)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D80 RO 0x0000_0000
	UINT32 reg_read_hist_22_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 22)
	UINT32 reg_read_hist_22_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 22)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D84 RO 0x0000_0000
	UINT32 reg_read_hist_23_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 23)
	UINT32 reg_read_hist_23_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 23)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D88 RO 0x0000_0000
	UINT32 reg_read_hist_24_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 24)
	UINT32 reg_read_hist_24_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 24)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D8C RO 0x0000_0000
	UINT32 reg_read_hist_25_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 25)
	UINT32 reg_read_hist_25_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 25)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D90 RO 0x0000_0000
	UINT32 reg_read_hist_26_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 26)
	UINT32 reg_read_hist_26_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 26)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D94 RO 0x0000_0000
	UINT32 reg_read_hist_27_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 27)
	UINT32 reg_read_hist_27_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 27)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D98 RO 0x0000_0000
	UINT32 reg_read_hist_28_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 28)
	UINT32 reg_read_hist_28_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 28)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14D9C RO 0x0000_0000
	UINT32 reg_read_hist_29_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 29)
	UINT32 reg_read_hist_29_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 29)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DA0 RO 0x0000_0000
	UINT32 reg_read_hist_30_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 30)
	UINT32 reg_read_hist_30_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 30)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DA4 RO 0x0000_0000
	UINT32 reg_read_hist_31_bg              :16;	//(15:0,NA,0) //Histogram read data (BG, bin 31)
	UINT32 reg_read_hist_31_fg              :16;	//(31:16,NA,0) //Histogram read data (FG, bin 31)
	};
}PE_O26_AMG1_BODY_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DB0 RW 0x0000_1101
	UINT32 reg_objt_map_en                  :1;	//(0:0,NA,1) //Object map enable
	UINT32 resvd0                           :3;
	UINT32 reg_dbg_map_ctrl                 :3;	//(6:4,NA,0) //Debug map selection	0 : Probability map	1 : Ellipse gain map	2 : Probability map (FG)	3 : Probability map (BG)	4 : Probability map (diff)	5 : Box map	6 : Pixel data (Y)
	UINT32 resvd1                           :1;
	UINT32 reg_fg_mul_ellipse_en            :1;	//(8:8,NA,1) //Reflect ellipse gain enable
	UINT32 resvd2                           :3;
	UINT32 reg_out_mux_sel                  :2;	//(13:12,NA,1) //Object map output mux selection	0 : HEAD/BODY	1 : Blending	2 : Depth only	3 : Adding
	UINT32 resvd3                           :18;
	};
}PE_O26_AMG1_BODY_OBJT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DB4 RW 0x0055_0055
	UINT32 reg_fg_prob_factor               :7;	//(6:0,NA,85) //FG probability map factor
	UINT32 resvd0                           :9;
	UINT32 reg_bg_prob_factor               :7;	//(22:16,NA,85) //BG probability map factor
	UINT32 resvd1                           :9;
	};
}PE_O26_AMG1_BODY_OBJT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DB8 RW 0x00C4_00C4
	UINT32 reg_fg_diff_mul                  :10;	//(9:0,NA,196) //FG factor for probability diff map (6.4bit)
	UINT32 resvd0                           :6;
	UINT32 reg_bg_diff_mul                  :10;	//(25:16,NA,196) //BG factor for probability diff map (6.4bit)
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_OBJT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DBC RW 0x0004_0004
	UINT32 reg_e_offset                     :8;	//(7:0,NA,4) //Ellipse gain offset
	UINT32 resvd0                           :8;
	UINT32 reg_p_offset                     :8;	//(23:16,NA,4) //Probability diff map offset
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG1_BODY_OBJT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DC0 RW 0x0000_0000
	UINT32 resvd0                           :4;
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
	UINT32 reg_additional_box_en            :1;	//(16:16,NA,0) //Additional box enable	0 : disable (default, replaced to optional box enable)	1 : enable
	UINT32 resvd1                           :15;
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DC4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DC8 RW 0x0000_0000
	UINT32 reg_box0_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 1) position, w, start
	UINT32 reg_box0_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 1) position, w, end
	UINT32 reg_box0_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 1) position, h, start
	UINT32 reg_box0_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 1) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DCC RW 0x0000_0000
	UINT32 reg_box1_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 1) position, w, start
	UINT32 reg_box1_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 1) position, w, end
	UINT32 reg_box1_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 1) position, h, start
	UINT32 reg_box1_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 1) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DD0 RW 0x0000_0000
	UINT32 reg_box2_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 1) position, w, start
	UINT32 reg_box2_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 1) position, w, end
	UINT32 reg_box2_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 1) position, h, start
	UINT32 reg_box2_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 1) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DD4 RW 0x0000_0000
	UINT32 reg_box3_add_set1_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 1) position, w, start
	UINT32 reg_box3_add_set1_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 1) position, w, end
	UINT32 reg_box3_add_set1_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 1) position, h, start
	UINT32 reg_box3_add_set1_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 1) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DD8 RW 0x0000_0000
	UINT32 reg_box0_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 0, set 2) position, w, start
	UINT32 reg_box0_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 0, set 2) position, w, end
	UINT32 reg_box0_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 0, set 2) position, h, start
	UINT32 reg_box0_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 0, set 2) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DDC RW 0x0000_0000
	UINT32 reg_box1_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 1, set 2) position, w, start
	UINT32 reg_box1_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 1, set 2) position, w, end
	UINT32 reg_box1_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 1, set 2) position, h, start
	UINT32 reg_box1_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 1, set 2) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DE0 RW 0x0000_0000
	UINT32 reg_box2_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 2, set 2) position, w, start
	UINT32 reg_box2_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 2, set 2) position, w, end
	UINT32 reg_box2_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 2, set 2) position, h, start
	UINT32 reg_box2_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 2, set 2) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DE4 RW 0x0000_0000
	UINT32 reg_box3_add_set2_w1             :8;	//(7:0,NA,0) //Box (additional box 3, set 2) position, w, start
	UINT32 reg_box3_add_set2_w2             :8;	//(15:8,NA,0) //Box (additional box 3, set 2) position, w, end
	UINT32 reg_box3_add_set2_h1             :8;	//(23:16,NA,0) //Box (additional box 3, set 2) position, h, start
	UINT32 reg_box3_add_set2_h2             :8;	//(31:24,NA,0) //Box (additional box 3, set 2) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DE8 RW 0x0000_0000
	UINT32 reg_box0_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 0) position, w, start
	UINT32 reg_box0_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 0) position, w, end
	UINT32 reg_box0_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 0) position, h, start
	UINT32 reg_box0_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 0) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DEC RW 0x0000_0000
	UINT32 reg_box1_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 1) position, w, start
	UINT32 reg_box1_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 1) position, w, end
	UINT32 reg_box1_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 1) position, h, start
	UINT32 reg_box1_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 1) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DF0 RW 0x0000_0000
	UINT32 reg_box2_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 2) position, w, start
	UINT32 reg_box2_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 2) position, w, end
	UINT32 reg_box2_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 2) position, h, start
	UINT32 reg_box2_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 2) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14DF4 RW 0x0000_0000
	UINT32 reg_box3_opt_w1                  :8;	//(7:0,NA,0) //Box (optional box 3) position, w, start
	UINT32 reg_box3_opt_w2                  :8;	//(15:8,NA,0) //Box (optional box 3) position, w, end
	UINT32 reg_box3_opt_h1                  :8;	//(23:16,NA,0) //Box (optional box 3) position, h, start
	UINT32 reg_box3_opt_h2                  :8;	//(31:24,NA,0) //Box (optional box 3) position, h, end
	};
}PE_O26_AMG1_BODY_BOX_SET_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E00 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E04 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E08 RW 0x002A_0026
	UINT32 reg_opt0_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 0) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 0) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 0) ellipse to rect disable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E0C RW 0x0040_00C0
	UINT32 reg_opt0_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 0) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt0_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 0) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E10 RW 0x00DE_0080
	UINT32 reg_opt0_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 0) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt0_sin_theta               :9;	//(24:16,NA,222) //Ellipse (optional box 0) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt0_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 0) rotation enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E14 RW 0x0000_0000
	UINT32 reg_opt0_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 0) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt0_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 0) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt0_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 0) manual box center position enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E18 RW 0x002A_0026
	UINT32 reg_opt1_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 1) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 1) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 1) ellipse to rect disable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E1C RW 0x0040_00C0
	UINT32 reg_opt1_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 1) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt1_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 1) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E20 RW 0x0122_0080
	UINT32 reg_opt1_cos_theta               :9;	//(8:0,NA,128) //Ellipse (optional box 1) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt1_sin_theta               :9;	//(24:16,NA,-222) //Ellipse (optional box 1) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt1_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 1) rotation enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E24 RW 0x0000_0000
	UINT32 reg_opt1_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 1) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt1_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 1) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt1_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 1) manual box center position enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E28 RW 0x002A_0026
	UINT32 reg_opt2_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 2) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 2) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 2) ellipse to rect disable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E2C RW 0x0040_00C0
	UINT32 reg_opt2_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 2) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt2_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 2) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E30 RW 0x00B5_00B5
	UINT32 reg_opt2_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 2) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt2_sin_theta               :9;	//(24:16,NA,181) //Ellipse (optional box 2) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt2_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 2) rotation enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E34 RW 0x0000_0000
	UINT32 reg_opt2_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 2) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt2_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 2) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt2_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 2) manual box center position enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E38 RW 0x002A_0026
	UINT32 reg_opt3_e_mul_a                 :9;	//(8:0,NA,38) //Ellipse (optional box 3) factor (H) (4.5bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_e_mul_b                 :9;	//(24:16,NA,42) //Ellipse (optional box 3) factor (V) (4.5bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_rect_disable            :1;	//(31:31,NA,0) //Ellipse (optional box 3) ellipse to rect disable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E3C RW 0x0040_00C0
	UINT32 reg_opt3_ellipse_master          :8;	//(7:0,NA,192) //Ellipse (optional box 3) master gain
	UINT32 resvd0                           :8;
	UINT32 reg_opt3_ellipse_offset          :8;	//(23:16,NA,64) //Ellipse (optional box 3) gain offset threshold
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E40 RW 0x014B_00B5
	UINT32 reg_opt3_cos_theta               :9;	//(8:0,NA,181) //Ellipse (optional box 3) cos value for rotation (1.8bit)
	UINT32 resvd0                           :7;
	UINT32 reg_opt3_sin_theta               :9;	//(24:16,NA,-181) //Ellipse (optional box 3) sin value for rotation (1.8bit)
	UINT32 resvd1                           :6;
	UINT32 reg_opt3_ellipse_rotation_en     :1;	//(31:31,NA,0) //Ellipse (optional box 3) rotation enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E44 RW 0x0000_0000
	UINT32 reg_opt3_ellipse_cen_pos_x       :10;	//(9:0,NA,0) //Ellipse (optional box 3) manual box center position (H)
	UINT32 resvd0                           :6;
	UINT32 reg_opt3_ellipse_cen_pos_y       :10;	//(25:16,NA,0) //Ellipse (optional box 3) manual box center position (V)
	UINT32 resvd1                           :5;
	UINT32 reg_opt3_ellipse_cen_pos_en      :1;	//(31:31,NA,0) //Ellipse (optional box 3) manual box center position enable
	};
}PE_O26_AMG1_BODY_ELLIPSE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E50 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y0              :8;	//(7:0,NA,255) //LUT (probability map) control point, y0
	UINT32 reg_lut_prob_map_x0              :8;	//(15:8,NA,255) //LUT (probability map) control point, x0
	UINT32 reg_lut_prob_map_y1              :8;	//(23:16,NA,255) //LUT (probability map) control point, y1
	UINT32 reg_lut_prob_map_x1              :8;	//(31:24,NA,255) //LUT (probability map) control point, x1
	};
}PE_O26_AMG1_BODY_LUT_PROB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E54 RW 0xFFFF_FFFF
	UINT32 reg_lut_prob_map_y2              :8;	//(7:0,NA,255) //LUT (probability map) control point, y2
	UINT32 reg_lut_prob_map_x2              :8;	//(15:8,NA,255) //LUT (probability map) control point, x2
	UINT32 reg_lut_prob_map_y3              :8;	//(23:16,NA,255) //LUT (probability map) control point, y3
	UINT32 reg_lut_prob_map_x3              :8;	//(31:24,NA,255) //LUT (probability map) control point, x3
	};
}PE_O26_AMG1_BODY_LUT_PROB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E60 RW 0x0000_0000
	UINT32 reg_blur_en                      :1;	//(0:0,NA,0) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E64 RW 0x0071_0071
	UINT32 reg_blur_hcoef0                  :10;	//(9:0,NA,113) //Blur filter coefficient, h0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef1                  :10;	//(25:16,NA,113) //Blur filter coefficient, h1
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E68 RW 0x0072_0072
	UINT32 reg_blur_hcoef2                  :10;	//(9:0,NA,114) //Blur filter coefficient, h2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef3                  :10;	//(25:16,NA,114) //Blur filter coefficient, h3
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E6C RW 0x0072_0074
	UINT32 reg_blur_hcoef4                  :10;	//(9:0,NA,116) //Blur filter coefficient, h4
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef5                  :10;	//(25:16,NA,114) //Blur filter coefficient, h5
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E70 RW 0x0071_0072
	UINT32 reg_blur_hcoef6                  :10;	//(9:0,NA,114) //Blur filter coefficient, h6
	UINT32 resvd0                           :6;
	UINT32 reg_blur_hcoef7                  :10;	//(25:16,NA,113) //Blur filter coefficient, h7
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E74 RW 0x0000_0071
	UINT32 reg_blur_hcoef8                  :10;	//(9:0,NA,113) //Blur filter coefficient, h8
	UINT32 resvd                            :22;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E78 RW 0x00CC_00CC
	UINT32 reg_blur_vcoef0                  :10;	//(9:0,NA,204) //Blur filter coefficient, v0
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef1                  :10;	//(25:16,NA,204) //Blur filter coefficient, v1
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E7C RW 0x00CC_00D0
	UINT32 reg_blur_vcoef2                  :10;	//(9:0,NA,208) //Blur filter coefficient, v2
	UINT32 resvd0                           :6;
	UINT32 reg_blur_vcoef3                  :10;	//(25:16,NA,204) //Blur filter coefficient, v3
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E80 RW 0x0000_00CC
	UINT32 reg_blur_vcoef4                  :10;	//(9:0,NA,204) //Blur filter coefficient, v4
	UINT32 resvd                            :22;
	};
}PE_O26_AMG1_BODY_BLUR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E90 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14E94 RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EA0 RW 0xC090_6030
	UINT32 reg_region_position_x1           :8;	//(7:0,NA,48) //Region gain position, x1
	UINT32 reg_region_position_x2           :8;	//(15:8,NA,96) //Region gain position, x2
	UINT32 reg_region_position_x3           :8;	//(23:16,NA,144) //Region gain position, x3
	UINT32 reg_region_position_x4           :8;	//(31:24,NA,192) //Region gain position, x4
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EA4 RW 0xEFEF_EFEF
	UINT32 reg_region_position_x5           :8;	//(7:0,NA,239) //Region gain position, x5
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EA8 RW 0x7D73_5A28
	UINT32 reg_region_position_y1           :8;	//(7:0,NA,40) //Region gain position, y1
	UINT32 reg_region_position_y2           :8;	//(15:8,NA,90) //Region gain position, y2
	UINT32 reg_region_position_y3           :8;	//(23:16,NA,115) //Region gain position, y3
	UINT32 reg_region_position_y4           :8;	//(31:24,NA,125) //Region gain position, y4
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EAC RW 0x0000_8686
	UINT32 reg_region_position_y5           :8;	//(7:0,NA,134) //Region gain position, y5
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EB0 RW 0x0000_0000
	UINT32 reg_region_gain_en_11            :2;	//(1:0,NA,0) //Region gain enable, 11
	UINT32 reg_region_gain_en_21            :2;	//(3:2,NA,0) //Region gain enable, 21
	UINT32 reg_region_gain_en_31            :2;	//(5:4,NA,0) //Region gain enable, 31
	UINT32 reg_region_gain_en_41            :2;	//(7:6,NA,0) //Region gain enable, 41
	UINT32 reg_region_gain_en_51            :2;	//(9:8,NA,0) //Region gain enable, 51
	UINT32 resvd0                           :6;
	UINT32 reg_region_gain_en_12            :2;	//(17:16,NA,0) //Region gain enable, 12
	UINT32 reg_region_gain_en_22            :2;	//(19:18,NA,0) //Region gain enable, 22
	UINT32 reg_region_gain_en_32            :2;	//(21:20,NA,0) //Region gain enable, 32
	UINT32 reg_region_gain_en_42            :2;	//(23:22,NA,0) //Region gain enable, 42
	UINT32 reg_region_gain_en_52            :2;	//(25:24,NA,0) //Region gain enable, 52
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EB4 RW 0x0000_0000
	UINT32 reg_region_gain_en_13            :2;	//(1:0,NA,0) //Region gain enable, 13
	UINT32 reg_region_gain_en_23            :2;	//(3:2,NA,0) //Region gain enable, 23
	UINT32 reg_region_gain_en_33            :2;	//(5:4,NA,0) //Region gain enable, 33
	UINT32 reg_region_gain_en_43            :2;	//(7:6,NA,0) //Region gain enable, 43
	UINT32 reg_region_gain_en_53            :2;	//(9:8,NA,0) //Region gain enable, 53
	UINT32 resvd0                           :6;
	UINT32 reg_region_gain_en_14            :2;	//(17:16,NA,0) //Region gain enable, 14
	UINT32 reg_region_gain_en_24            :2;	//(19:18,NA,0) //Region gain enable, 24
	UINT32 reg_region_gain_en_34            :2;	//(21:20,NA,0) //Region gain enable, 34
	UINT32 reg_region_gain_en_44            :2;	//(23:22,NA,0) //Region gain enable, 44
	UINT32 reg_region_gain_en_54            :2;	//(25:24,NA,0) //Region gain enable, 54
	UINT32 resvd1                           :6;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EB8 RW 0x0000_0000
	UINT32 reg_region_gain_en_15            :2;	//(1:0,NA,0) //Region gain enable, 15
	UINT32 reg_region_gain_en_25            :2;	//(3:2,NA,0) //Region gain enable, 25
	UINT32 reg_region_gain_en_35            :2;	//(5:4,NA,0) //Region gain enable, 35
	UINT32 reg_region_gain_en_45            :2;	//(7:6,NA,0) //Region gain enable, 45
	UINT32 reg_region_gain_en_55            :2;	//(9:8,NA,0) //Region gain enable, 55
	UINT32 resvd                            :22;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EBC RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,128) //Region gain, 11
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,128) //Region gain, 21
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,128) //Region gain, 31
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,128) //Region gain, 41
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EC0 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,128) //Region gain, 51
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EC4 RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,128) //Region gain, 12
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,128) //Region gain, 22
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,128) //Region gain, 32
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,128) //Region gain, 42
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EC8 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,128) //Region gain, 52
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ECC RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,128) //Region gain, 13
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,128) //Region gain, 23
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,128) //Region gain, 33
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,128) //Region gain, 43
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ED0 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,128) //Region gain, 53
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ED4 RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,128) //Region gain, 14
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,128) //Region gain, 24
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,128) //Region gain, 34
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,128) //Region gain, 44
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14ED8 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,128) //Region gain, 54
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EDC RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,128) //Region gain, 15
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,128) //Region gain, 25
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,128) //Region gain, 35
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,128) //Region gain, 45
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EE0 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,128) //Region gain, 55
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EE4 RW 0x8080_8080
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EE8 RW 0x8080_8080
	UINT32 tdata0                           :32;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EEC RW 0x8600_EF00
	UINT32 reg_region_bnd_x0                :8;	//(7:0,NA,0) //Region bound, x0
	UINT32 reg_region_bnd_x1                :8;	//(15:8,NA,239) //Region bound, x1
	UINT32 reg_region_bnd_y0                :8;	//(23:16,NA,0) //Region bound, y0
	UINT32 reg_region_bnd_y1                :8;	//(31:24,NA,134) //Region bound, y1
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EF0 RW 0x0000_0080
	UINT32 reg_region_bnd_gain              :8;	//(7:0,NA,128) //Region bound gain
	UINT32 resvd                            :24;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14EF4 RW 0x0000_0110
	UINT32 reg_region_gain_offset0          :8;	//(7:0,NA,16) //Region gain offset0
	UINT32 reg_region_gain_offset1          :8;	//(15:8,NA,1) //Region gain offset1
	UINT32 resvd                            :16;
	};
}PE_O26_AMG1_BODY_REGION_GAIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F00 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_u_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y0
	UINT32 reg_lut_depth_iir_u_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, up) control point, x0
	UINT32 reg_lut_depth_iir_u_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y1
	UINT32 reg_lut_depth_iir_u_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, up) control point, x1
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F04 RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_u_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, up) control point, y2
	UINT32 reg_lut_depth_iir_u_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, up) control point, x2
	UINT32 reg_lut_depth_iir_u_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, up) control point, y3
	UINT32 reg_lut_depth_iir_u_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, up) control point, x3
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F08 RW 0x40FF_00FF
	UINT32 reg_lut_depth_iir_d_y0           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y0
	UINT32 reg_lut_depth_iir_d_x0           :8;	//(15:8,NA,0) //LUT (depth map IIR, down) control point, x0
	UINT32 reg_lut_depth_iir_d_y1           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y1
	UINT32 reg_lut_depth_iir_d_x1           :8;	//(31:24,NA,64) //LUT (depth map IIR, down) control point, x1
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F0C RW 0xFFFF_80FF
	UINT32 reg_lut_depth_iir_d_y2           :8;	//(7:0,NA,255) //LUT (depth map IIR, down) control point, y2
	UINT32 reg_lut_depth_iir_d_x2           :8;	//(15:8,NA,128) //LUT (depth map IIR, down) control point, x2
	UINT32 reg_lut_depth_iir_d_y3           :8;	//(23:16,NA,255) //LUT (depth map IIR, down) control point, y3
	UINT32 reg_lut_depth_iir_d_x3           :8;	//(31:24,NA,255) //LUT (depth map IIR, down) control point, x3
	};
}PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F10 RW 0x3FFF_00FF
	UINT32 reg_lut_depth_body_y0            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y0
	UINT32 reg_lut_depth_body_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth>body), x0
	UINT32 reg_lut_depth_body_y1            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y1
	UINT32 reg_lut_depth_body_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth>body), x1
	};
}PE_O26_AMG1_BODY_LUT_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F14 RW 0xFFFF_7EFF
	UINT32 reg_lut_depth_body_y2            :8;	//(7:0,NA,255) //LUT (depth body blend) control point (for depth>body), y2
	UINT32 reg_lut_depth_body_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth>body), x2
	UINT32 reg_lut_depth_body_y3            :8;	//(23:16,NA,255) //LUT (depth body blend) control point (for depth>body), y3
	UINT32 reg_lut_depth_body_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth>body), x3
	};
}PE_O26_AMG1_BODY_LUT_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F18 RW 0x3F20_0000
	UINT32 reg_lut_body_depth_y0            :8;	//(7:0,NA,0) //LUT (depth body blend) control point (for depth<=body), y0
	UINT32 reg_lut_body_depth_x0            :8;	//(15:8,NA,0) //LUT (depth body blend) control point (for depth<=body), x0
	UINT32 reg_lut_body_depth_y1            :8;	//(23:16,NA,32) //LUT (depth body blend) control point (for depth<=body), y1
	UINT32 reg_lut_body_depth_x1            :8;	//(31:24,NA,63) //LUT (depth body blend) control point (for depth<=body), x1
	};
}PE_O26_AMG1_BODY_LUT_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F1C RW 0xFF58_7E58
	UINT32 reg_lut_body_depth_y2            :8;	//(7:0,NA,88) //LUT (depth body blend) control point (for depth<=body), y2
	UINT32 reg_lut_body_depth_x2            :8;	//(15:8,NA,126) //LUT (depth body blend) control point (for depth<=body), x2
	UINT32 reg_lut_body_depth_y3            :8;	//(23:16,NA,88) //LUT (depth body blend) control point (for depth<=body), y3
	UINT32 reg_lut_body_depth_x3            :8;	//(31:24,NA,255) //LUT (depth body blend) control point (for depth<=body), x3
	};
}PE_O26_AMG1_BODY_LUT_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F20 RW 0x0000_0010
	UINT32 reg_iir_en                       :1;	//(0:0,NA,0) //IIR filter enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_alpha_sel                :1;	//(4:4,NA,1) //Blending alpha selection	0 : use manual value	1 : use ABS diff value
	UINT32 resvd1                           :3;
	UINT32 reg_iir_alpha                    :8;	//(15:8,NA,0) //Blending alpha for IIR
	UINT32 reg_iir_gain_init                :1;	//(16:16,NA,0) //IIR gain init selection	0 : use IIR result	1 : use manual gain init value
	UINT32 resvd2                           :7;
	UINT32 reg_iir_gain_init_val            :8;	//(31:24,NA,0) //IIR gain init value
	};
}PE_O26_AMG1_BODY_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F24 RW 0x0018_0801
	UINT32 reg_iir_clipping_en              :1;	//(0:0,NA,1) //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 reg_iir_th_lower                 :8;	//(11:4,NA,128) //IIR value clipping lower threshold
	UINT32 reg_iir_th_upper                 :8;	//(19:12,NA,128) //IIR value clipping upper threshold
	UINT32 reg_iir_same_prot                :8;	//(27:20,NA,1) //IIR same value protection
	UINT32 resvd1                           :4;
	};
}PE_O26_AMG1_BODY_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F30 RW 0x10DC_00F0
	UINT32 reg_lut_iir_map_y0               :8;	//(7:0,NA,240) //LUT (IIR gain) control point, y0
	UINT32 reg_lut_iir_map_x0               :8;	//(15:8,NA,0) //LUT (IIR gain) control point, x0
	UINT32 reg_lut_iir_map_y1               :8;	//(23:16,NA,220) //LUT (IIR gain) control point, y1
	UINT32 reg_lut_iir_map_x1               :8;	//(31:24,NA,16) //LUT (IIR gain) control point, x1
	};
}PE_O26_AMG1_BODY_LUT_IIR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F34 RW 0x40B0_20C0
	UINT32 reg_lut_iir_map_y2               :8;	//(7:0,NA,192) //LUT (IIR gain) control point, y2
	UINT32 reg_lut_iir_map_x2               :8;	//(15:8,NA,32) //LUT (IIR gain) control point, x2
	UINT32 reg_lut_iir_map_y3               :8;	//(23:16,NA,176) //LUT (IIR gain) control point, y3
	UINT32 reg_lut_iir_map_x3               :8;	//(31:24,NA,64) //LUT (IIR gain) control point, x3
	};
}PE_O26_AMG1_BODY_LUT_IIR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC14F38 RW 0x8080_60A0
	UINT32 reg_lut_iir_map_y4               :8;	//(7:0,NA,160) //LUT (IIR gain) control point, y4
	UINT32 reg_lut_iir_map_x4               :8;	//(15:8,NA,96) //LUT (IIR gain) control point, x4
	UINT32 reg_lut_iir_map_y5               :8;	//(23:16,NA,128) //LUT (IIR gain) control point, y5
	UINT32 reg_lut_iir_map_x5               :8;	//(31:24,NA,128) //LUT (IIR gain) control point, x5
	};
}PE_O26_AMG1_BODY_LUT_IIR_CTRL_02_T;

typedef struct {
	PE_O26_AMG1_BODY_HISTOGRAM_CTRL_00_T                 histogram_ctrl_00;	//0xCCC14D20
	PE_O26_AMG1_BODY_HISTOGRAM_CTRL_01_T                 histogram_ctrl_01;	//0xCCC14D24
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_00_T                 histogram_stat_00;	//0xCCC14D28
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_01_T                 histogram_stat_01;	//0xCCC14D2C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_02_T                 histogram_stat_02;	//0xCCC14D30
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_03_T                 histogram_stat_03;	//0xCCC14D34
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_04_T                 histogram_stat_04;	//0xCCC14D38
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_05_T                 histogram_stat_05;	//0xCCC14D3C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_06_T                 histogram_stat_06;	//0xCCC14D40
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_07_T                 histogram_stat_07;	//0xCCC14D44
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_08_T                 histogram_stat_08;	//0xCCC14D48
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_09_T                 histogram_stat_09;	//0xCCC14D4C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_10_T                 histogram_stat_10;	//0xCCC14D50
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_11_T                 histogram_stat_11;	//0xCCC14D54
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_12_T                 histogram_stat_12;	//0xCCC14D58
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_13_T                 histogram_stat_13;	//0xCCC14D5C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_14_T                 histogram_stat_14;	//0xCCC14D60
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_15_T                 histogram_stat_15;	//0xCCC14D64
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_16_T                 histogram_stat_16;	//0xCCC14D68
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_17_T                 histogram_stat_17;	//0xCCC14D6C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_18_T                 histogram_stat_18;	//0xCCC14D70
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_19_T                 histogram_stat_19;	//0xCCC14D74
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_20_T                 histogram_stat_20;	//0xCCC14D78
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_21_T                 histogram_stat_21;	//0xCCC14D7C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_22_T                 histogram_stat_22;	//0xCCC14D80
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_23_T                 histogram_stat_23;	//0xCCC14D84
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_24_T                 histogram_stat_24;	//0xCCC14D88
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_25_T                 histogram_stat_25;	//0xCCC14D8C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_26_T                 histogram_stat_26;	//0xCCC14D90
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_27_T                 histogram_stat_27;	//0xCCC14D94
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_28_T                 histogram_stat_28;	//0xCCC14D98
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_29_T                 histogram_stat_29;	//0xCCC14D9C
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_30_T                 histogram_stat_30;	//0xCCC14DA0
	PE_O26_AMG1_BODY_HISTOGRAM_STAT_31_T                 histogram_stat_31;	//0xCCC14DA4
	UINT32                                                       reserved0;	//0xCCC14DA8
	UINT32                                                       reserved1;	//0xCCC14DAC
	PE_O26_AMG1_BODY_OBJT_MAP_CTRL_00_T                   objt_map_ctrl_00;	//0xCCC14DB0
	PE_O26_AMG1_BODY_OBJT_MAP_CTRL_01_T                   objt_map_ctrl_01;	//0xCCC14DB4
	PE_O26_AMG1_BODY_OBJT_MAP_CTRL_02_T                   objt_map_ctrl_02;	//0xCCC14DB8
	PE_O26_AMG1_BODY_OBJT_MAP_CTRL_03_T                   objt_map_ctrl_03;	//0xCCC14DBC
	PE_O26_AMG1_BODY_BOX_SET_CTRL_00_T                     box_set_ctrl_00;	//0xCCC14DC0
	PE_O26_AMG1_BODY_BOX_SET_CTRL_01_T                     box_set_ctrl_01;	//0xCCC14DC4
	PE_O26_AMG1_BODY_BOX_SET_CTRL_02_T                     box_set_ctrl_02;	//0xCCC14DC8
	PE_O26_AMG1_BODY_BOX_SET_CTRL_03_T                     box_set_ctrl_03;	//0xCCC14DCC
	PE_O26_AMG1_BODY_BOX_SET_CTRL_04_T                     box_set_ctrl_04;	//0xCCC14DD0
	PE_O26_AMG1_BODY_BOX_SET_CTRL_05_T                     box_set_ctrl_05;	//0xCCC14DD4
	PE_O26_AMG1_BODY_BOX_SET_CTRL_06_T                     box_set_ctrl_06;	//0xCCC14DD8
	PE_O26_AMG1_BODY_BOX_SET_CTRL_07_T                     box_set_ctrl_07;	//0xCCC14DDC
	PE_O26_AMG1_BODY_BOX_SET_CTRL_08_T                     box_set_ctrl_08;	//0xCCC14DE0
	PE_O26_AMG1_BODY_BOX_SET_CTRL_09_T                     box_set_ctrl_09;	//0xCCC14DE4
	PE_O26_AMG1_BODY_BOX_SET_CTRL_10_T                     box_set_ctrl_10;	//0xCCC14DE8
	PE_O26_AMG1_BODY_BOX_SET_CTRL_11_T                     box_set_ctrl_11;	//0xCCC14DEC
	PE_O26_AMG1_BODY_BOX_SET_CTRL_12_T                     box_set_ctrl_12;	//0xCCC14DF0
	PE_O26_AMG1_BODY_BOX_SET_CTRL_13_T                     box_set_ctrl_13;	//0xCCC14DF4
	UINT32                                                       reserved2;	//0xCCC14DF8
	UINT32                                                       reserved3;	//0xCCC14DFC
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_00_T                     ellipse_ctrl_00;	//0xCCC14E00
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_01_T                     ellipse_ctrl_01;	//0xCCC14E04
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_02_T                     ellipse_ctrl_02;	//0xCCC14E08
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_03_T                     ellipse_ctrl_03;	//0xCCC14E0C
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_04_T                     ellipse_ctrl_04;	//0xCCC14E10
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_05_T                     ellipse_ctrl_05;	//0xCCC14E14
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_06_T                     ellipse_ctrl_06;	//0xCCC14E18
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_07_T                     ellipse_ctrl_07;	//0xCCC14E1C
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_08_T                     ellipse_ctrl_08;	//0xCCC14E20
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_09_T                     ellipse_ctrl_09;	//0xCCC14E24
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_10_T                     ellipse_ctrl_10;	//0xCCC14E28
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_11_T                     ellipse_ctrl_11;	//0xCCC14E2C
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_12_T                     ellipse_ctrl_12;	//0xCCC14E30
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_13_T                     ellipse_ctrl_13;	//0xCCC14E34
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_14_T                     ellipse_ctrl_14;	//0xCCC14E38
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_15_T                     ellipse_ctrl_15;	//0xCCC14E3C
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_16_T                     ellipse_ctrl_16;	//0xCCC14E40
	PE_O26_AMG1_BODY_ELLIPSE_CTRL_17_T                     ellipse_ctrl_17;	//0xCCC14E44
	UINT32                                                       reserved4;	//0xCCC14E48
	UINT32                                                       reserved5;	//0xCCC14E4C
	PE_O26_AMG1_BODY_LUT_PROB_CTRL_00_T                   lut_prob_ctrl_00;	//0xCCC14E50
	PE_O26_AMG1_BODY_LUT_PROB_CTRL_01_T                   lut_prob_ctrl_01;	//0xCCC14E54
	UINT32                                                       reserved6;	//0xCCC14E58
	UINT32                                                       reserved7;	//0xCCC14E5C
	PE_O26_AMG1_BODY_BLUR_CTRL_00_T                           blur_ctrl_00;	//0xCCC14E60
	PE_O26_AMG1_BODY_BLUR_CTRL_01_T                           blur_ctrl_01;	//0xCCC14E64
	PE_O26_AMG1_BODY_BLUR_CTRL_02_T                           blur_ctrl_02;	//0xCCC14E68
	PE_O26_AMG1_BODY_BLUR_CTRL_03_T                           blur_ctrl_03;	//0xCCC14E6C
	PE_O26_AMG1_BODY_BLUR_CTRL_04_T                           blur_ctrl_04;	//0xCCC14E70
	PE_O26_AMG1_BODY_BLUR_CTRL_05_T                           blur_ctrl_05;	//0xCCC14E74
	PE_O26_AMG1_BODY_BLUR_CTRL_06_T                           blur_ctrl_06;	//0xCCC14E78
	PE_O26_AMG1_BODY_BLUR_CTRL_07_T                           blur_ctrl_07;	//0xCCC14E7C
	PE_O26_AMG1_BODY_BLUR_CTRL_08_T                           blur_ctrl_08;	//0xCCC14E80
	UINT32                                                       reserved8;	//0xCCC14E84
	UINT32                                                       reserved9;	//0xCCC14E88
	UINT32                                                      reserved10;	//0xCCC14E8C
	PE_O26_AMG1_BODY_LUT_DEPTH_CTRL_00_T                 lut_depth_ctrl_00;	//0xCCC14E90
	PE_O26_AMG1_BODY_LUT_DEPTH_CTRL_01_T                 lut_depth_ctrl_01;	//0xCCC14E94
	UINT32                                                      reserved11;	//0xCCC14E98
	UINT32                                                      reserved12;	//0xCCC14E9C
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_00_T             region_gain_ctrl_00;	//0xCCC14EA0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_01_T             region_gain_ctrl_01;	//0xCCC14EA4
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_02_T             region_gain_ctrl_02;	//0xCCC14EA8
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_03_T             region_gain_ctrl_03;	//0xCCC14EAC
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_04_T             region_gain_ctrl_04;	//0xCCC14EB0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_05_T             region_gain_ctrl_05;	//0xCCC14EB4
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_06_T             region_gain_ctrl_06;	//0xCCC14EB8
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_07_T             region_gain_ctrl_07;	//0xCCC14EBC
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_08_T             region_gain_ctrl_08;	//0xCCC14EC0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_09_T             region_gain_ctrl_09;	//0xCCC14EC4
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_10_T             region_gain_ctrl_10;	//0xCCC14EC8
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_11_T             region_gain_ctrl_11;	//0xCCC14ECC
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_12_T             region_gain_ctrl_12;	//0xCCC14ED0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_13_T             region_gain_ctrl_13;	//0xCCC14ED4
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_14_T             region_gain_ctrl_14;	//0xCCC14ED8
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_15_T             region_gain_ctrl_15;	//0xCCC14EDC
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_16_T             region_gain_ctrl_16;	//0xCCC14EE0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_17_T             region_gain_ctrl_17;	//0xCCC14EE4
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_18_T             region_gain_ctrl_18;	//0xCCC14EE8
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_19_T             region_gain_ctrl_19;	//0xCCC14EEC
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_20_T             region_gain_ctrl_20;	//0xCCC14EF0
	PE_O26_AMG1_BODY_REGION_GAIN_CTRL_21_T             region_gain_ctrl_21;	//0xCCC14EF4
	UINT32                                                      reserved13;	//0xCCC14EF8
	UINT32                                                      reserved14;	//0xCCC14EFC
	PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_00_T         lut_depth_iir_ctrl_00;	//0xCCC14F00
	PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_01_T         lut_depth_iir_ctrl_01;	//0xCCC14F04
	PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_02_T         lut_depth_iir_ctrl_02;	//0xCCC14F08
	PE_O26_AMG1_BODY_LUT_DEPTH_IIR_CTRL_03_T         lut_depth_iir_ctrl_03;	//0xCCC14F0C
	PE_O26_AMG1_BODY_LUT_BLD_CTRL_00_T                     lut_bld_ctrl_00;	//0xCCC14F10
	PE_O26_AMG1_BODY_LUT_BLD_CTRL_01_T                     lut_bld_ctrl_01;	//0xCCC14F14
	PE_O26_AMG1_BODY_LUT_BLD_CTRL_02_T                     lut_bld_ctrl_02;	//0xCCC14F18
	PE_O26_AMG1_BODY_LUT_BLD_CTRL_03_T                     lut_bld_ctrl_03;	//0xCCC14F1C
	PE_O26_AMG1_BODY_IIR_CTRL_00_T                             iir_ctrl_00;	//0xCCC14F20
	PE_O26_AMG1_BODY_IIR_CTRL_01_T                             iir_ctrl_01;	//0xCCC14F24
	UINT32                                                      reserved15;	//0xCCC14F28
	UINT32                                                      reserved16;	//0xCCC14F2C
	PE_O26_AMG1_BODY_LUT_IIR_CTRL_00_T                     lut_iir_ctrl_00;	//0xCCC14F30
	PE_O26_AMG1_BODY_LUT_IIR_CTRL_01_T                     lut_iir_ctrl_01;	//0xCCC14F34
	PE_O26_AMG1_BODY_LUT_IIR_CTRL_02_T                     lut_iir_ctrl_02;	//0xCCC14F38
}PE_AMG_BODY_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15900 RW 0xFFFF_C5BF
	UINT32 reg_ca_mc_prv_lut_y4             :8;	//(7:0,NA,191) //Contrast adjust LUT points (MC: PRV), y4
	UINT32 reg_ca_mc_prv_lut_x4             :8;	//(15:8,NA,197) //Contrast adjust LUT points (MC: PRV), x4
	UINT32 reg_ca_mc_prv_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: PRV), y5
	UINT32 reg_ca_mc_prv_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: PRV), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15904 RW 0x8B7F_503F
	UINT32 reg_ca_mc_prv_lut_y2             :8;	//(7:0,NA,63) //Contrast adjust LUT points (MC: PRV), y2
	UINT32 reg_ca_mc_prv_lut_x2             :8;	//(15:8,NA,80) //Contrast adjust LUT points (MC: PRV), x2
	UINT32 reg_ca_mc_prv_lut_y3             :8;	//(23:16,NA,127) //Contrast adjust LUT points (MC: PRV), y3
	UINT32 reg_ca_mc_prv_lut_x3             :8;	//(31:24,NA,139) //Contrast adjust LUT points (MC: PRV), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15908 RW 0x1900_0000
	UINT32 reg_ca_mc_prv_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: PRV), y0
	UINT32 reg_ca_mc_prv_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: PRV), x0
	UINT32 reg_ca_mc_prv_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: PRV), y1
	UINT32 reg_ca_mc_prv_lut_x1             :8;	//(31:24,NA,25) //Contrast adjust LUT points (MC: PRV), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1590C RW 0xFFFF_F7FF
	UINT32 reg_ca_mc_cur_lut_y4             :8;	//(7:0,NA,255) //Contrast adjust LUT points (MC: CUR), y4
	UINT32 reg_ca_mc_cur_lut_x4             :8;	//(15:8,NA,247) //Contrast adjust LUT points (MC: CUR), x4
	UINT32 reg_ca_mc_cur_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: CUR), y5
	UINT32 reg_ca_mc_cur_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: CUR), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15910 RW 0xA9AA_5B55
	UINT32 reg_ca_mc_cur_lut_y2             :8;	//(7:0,NA,85) //Contrast adjust LUT points (MC: CUR), y2
	UINT32 reg_ca_mc_cur_lut_x2             :8;	//(15:8,NA,91) //Contrast adjust LUT points (MC: CUR), x2
	UINT32 reg_ca_mc_cur_lut_y3             :8;	//(23:16,NA,170) //Contrast adjust LUT points (MC: CUR), y3
	UINT32 reg_ca_mc_cur_lut_x3             :8;	//(31:24,NA,169) //Contrast adjust LUT points (MC: CUR), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15914 RW 0x0E00_0000
	UINT32 reg_ca_mc_cur_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: CUR), y0
	UINT32 reg_ca_mc_cur_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: CUR), x0
	UINT32 reg_ca_mc_cur_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: CUR), y1
	UINT32 reg_ca_mc_cur_lut_x1             :8;	//(31:24,NA,14) //Contrast adjust LUT points (MC: CUR), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15918 RW 0xFFFF_F7FF
	UINT32 reg_ca_mc_res_lut_y4             :8;	//(7:0,NA,255) //Contrast adjust LUT points (MC: RES), y4
	UINT32 reg_ca_mc_res_lut_x4             :8;	//(15:8,NA,247) //Contrast adjust LUT points (MC: RES), x4
	UINT32 reg_ca_mc_res_lut_y5             :8;	//(23:16,NA,255) //Contrast adjust LUT points (MC: RES), y5
	UINT32 reg_ca_mc_res_lut_x5             :8;	//(31:24,NA,255) //Contrast adjust LUT points (MC: RES), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1591C RW 0xA9AA_5B55
	UINT32 reg_ca_mc_res_lut_y2             :8;	//(7:0,NA,85) //Contrast adjust LUT points (MC: RES), y2
	UINT32 reg_ca_mc_res_lut_x2             :8;	//(15:8,NA,91) //Contrast adjust LUT points (MC: RES), x2
	UINT32 reg_ca_mc_res_lut_y3             :8;	//(23:16,NA,170) //Contrast adjust LUT points (MC: RES), y3
	UINT32 reg_ca_mc_res_lut_x3             :8;	//(31:24,NA,169) //Contrast adjust LUT points (MC: RES), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15920 RW 0x0E00_0000
	UINT32 reg_ca_mc_res_lut_y0             :8;	//(7:0,NA,0) //Contrast adjust LUT points (MC: RES), y0
	UINT32 reg_ca_mc_res_lut_x0             :8;	//(15:8,NA,0) //Contrast adjust LUT points (MC: RES), x0
	UINT32 reg_ca_mc_res_lut_y1             :8;	//(23:16,NA,0) //Contrast adjust LUT points (MC: RES), y1
	UINT32 reg_ca_mc_res_lut_x1             :8;	//(31:24,NA,14) //Contrast adjust LUT points (MC: RES), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15924 RW 0xFFFF_C5BF
	UINT32 reg_ca_basic_prv_lut_y4          :8;	//(7:0,NA,191) //Contrast adjust LUT points (Basic: PRV), y4
	UINT32 reg_ca_basic_prv_lut_x4          :8;	//(15:8,NA,197) //Contrast adjust LUT points (Basic: PRV), x4
	UINT32 reg_ca_basic_prv_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: PRV), y5
	UINT32 reg_ca_basic_prv_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: PRV), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15928 RW 0x8B7F_503F
	UINT32 reg_ca_basic_prv_lut_y2          :8;	//(7:0,NA,63) //Contrast adjust LUT points (Basic: PRV), y2
	UINT32 reg_ca_basic_prv_lut_x2          :8;	//(15:8,NA,80) //Contrast adjust LUT points (Basic: PRV), x2
	UINT32 reg_ca_basic_prv_lut_y3          :8;	//(23:16,NA,127) //Contrast adjust LUT points (Basic: PRV), y3
	UINT32 reg_ca_basic_prv_lut_x3          :8;	//(31:24,NA,139) //Contrast adjust LUT points (Basic: PRV), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1592C RW 0x1900_0000
	UINT32 reg_ca_basic_prv_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: PRV), y0
	UINT32 reg_ca_basic_prv_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: PRV), x0
	UINT32 reg_ca_basic_prv_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: PRV), y1
	UINT32 reg_ca_basic_prv_lut_x1          :8;	//(31:24,NA,25) //Contrast adjust LUT points (Basic: PRV), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15930 RW 0xFFFF_F7FF
	UINT32 reg_ca_basic_cur_lut_y4          :8;	//(7:0,NA,255) //Contrast adjust LUT points (Basic: CUR), y4
	UINT32 reg_ca_basic_cur_lut_x4          :8;	//(15:8,NA,247) //Contrast adjust LUT points (Basic: CUR), x4
	UINT32 reg_ca_basic_cur_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: CUR), y5
	UINT32 reg_ca_basic_cur_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: CUR), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15934 RW 0xA9AA_5B55
	UINT32 reg_ca_basic_cur_lut_y2          :8;	//(7:0,NA,85) //Contrast adjust LUT points (Basic: CUR), y2
	UINT32 reg_ca_basic_cur_lut_x2          :8;	//(15:8,NA,91) //Contrast adjust LUT points (Basic: CUR), x2
	UINT32 reg_ca_basic_cur_lut_y3          :8;	//(23:16,NA,170) //Contrast adjust LUT points (Basic: CUR), y3
	UINT32 reg_ca_basic_cur_lut_x3          :8;	//(31:24,NA,169) //Contrast adjust LUT points (Basic: CUR), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15938 RW 0x0E00_0000
	UINT32 reg_ca_basic_cur_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: CUR), y0
	UINT32 reg_ca_basic_cur_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: CUR), x0
	UINT32 reg_ca_basic_cur_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: CUR), y1
	UINT32 reg_ca_basic_cur_lut_x1          :8;	//(31:24,NA,14) //Contrast adjust LUT points (Basic: CUR), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1593C RW 0xFFFF_F7FF
	UINT32 reg_ca_basic_res_lut_y4          :8;	//(7:0,NA,255) //Contrast adjust LUT points (Basic: RES), y4
	UINT32 reg_ca_basic_res_lut_x4          :8;	//(15:8,NA,247) //Contrast adjust LUT points (Basic: RES), x4
	UINT32 reg_ca_basic_res_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Basic: RES), y5
	UINT32 reg_ca_basic_res_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Basic: RES), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15940 RW 0xA9AA_5B55
	UINT32 reg_ca_basic_res_lut_y2          :8;	//(7:0,NA,85) //Contrast adjust LUT points (Basic: RES), y2
	UINT32 reg_ca_basic_res_lut_x2          :8;	//(15:8,NA,91) //Contrast adjust LUT points (Basic: RES), x2
	UINT32 reg_ca_basic_res_lut_y3          :8;	//(23:16,NA,170) //Contrast adjust LUT points (Basic: RES), y3
	UINT32 reg_ca_basic_res_lut_x3          :8;	//(31:24,NA,169) //Contrast adjust LUT points (Basic: RES), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15944 RW 0x0E00_0000
	UINT32 reg_ca_basic_res_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Basic: RES), y0
	UINT32 reg_ca_basic_res_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Basic: RES), x0
	UINT32 reg_ca_basic_res_lut_y1          :8;	//(23:16,NA,0) //Contrast adjust LUT points (Basic: RES), y1
	UINT32 reg_ca_basic_res_lut_x1          :8;	//(31:24,NA,14) //Contrast adjust LUT points (Basic: RES), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15948 RW 0xFFFF_C0C0
	UINT32 reg_ca_final_res_lut_y4          :8;	//(7:0,NA,192) //Contrast adjust LUT points (Final: RES), y4
	UINT32 reg_ca_final_res_lut_x4          :8;	//(15:8,NA,192) //Contrast adjust LUT points (Final: RES), x4
	UINT32 reg_ca_final_res_lut_y5          :8;	//(23:16,NA,255) //Contrast adjust LUT points (Final: RES), y5
	UINT32 reg_ca_final_res_lut_x5          :8;	//(31:24,NA,255) //Contrast adjust LUT points (Final: RES), x5
	};
}PE_O26_AMG2_MTB_CA_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1594C RW 0xA0A0_8080
	UINT32 reg_ca_final_res_lut_y2          :8;	//(7:0,NA,128) //Contrast adjust LUT points (Final: RES), y2
	UINT32 reg_ca_final_res_lut_x2          :8;	//(15:8,NA,128) //Contrast adjust LUT points (Final: RES), x2
	UINT32 reg_ca_final_res_lut_y3          :8;	//(23:16,NA,160) //Contrast adjust LUT points (Final: RES), y3
	UINT32 reg_ca_final_res_lut_x3          :8;	//(31:24,NA,160) //Contrast adjust LUT points (Final: RES), x3
	};
}PE_O26_AMG2_MTB_CA_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15950 RW 0x4040_0000
	UINT32 reg_ca_final_res_lut_y0          :8;	//(7:0,NA,0) //Contrast adjust LUT points (Final: RES), y0
	UINT32 reg_ca_final_res_lut_x0          :8;	//(15:8,NA,0) //Contrast adjust LUT points (Final: RES), x0
	UINT32 reg_ca_final_res_lut_y1          :8;	//(23:16,NA,64) //Contrast adjust LUT points (Final: RES), y1
	UINT32 reg_ca_final_res_lut_x1          :8;	//(31:24,NA,64) //Contrast adjust LUT points (Final: RES), x1
	};
}PE_O26_AMG2_MTB_CA_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15960 RW 0x0000_0000
	UINT32 reg_blend_inp_type_mc            :1;	//(0:0,NA,0) //Blending input type (MC , 0: ABS diff, 1: offset diff)
	UINT32 resvd0                           :3;
	UINT32 reg_blend_inp_type_basic         :1;	//(4:4,NA,0) //Blending input type (Basic, 0: ABS diff, 1: offset diff)
	UINT32 resvd1                           :3;
	UINT32 reg_blend_inp_type_final         :1;	//(8:8,NA,0) //Blending input type (Final, 0: ABS diff, 1: offset diff)
	UINT32 resvd2                           :23;
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15964 RW 0xFF80_46B0
	UINT32 reg_blend_mc_lut_wei4            :8;	//(7:0,NA,176) //Blending LUT points (MC), y4
	UINT32 reg_blend_mc_lut_dif4            :8;	//(15:8,NA,70) //Blending LUT points (MC), x4
	UINT32 reg_blend_mc_lut_wei5            :8;	//(23:16,NA,128) //Blending LUT points (MC), y5
	UINT32 reg_blend_mc_lut_dif5            :8;	//(31:24,NA,255) //Blending LUT points (MC), x5
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15968 RW 0x32C0_1EE0
	UINT32 reg_blend_mc_lut_wei2            :8;	//(7:0,NA,224) //Blending LUT points (MC), y2
	UINT32 reg_blend_mc_lut_dif2            :8;	//(15:8,NA,30) //Blending LUT points (MC), x2
	UINT32 reg_blend_mc_lut_wei3            :8;	//(23:16,NA,192) //Blending LUT points (MC), y3
	UINT32 reg_blend_mc_lut_dif3            :8;	//(31:24,NA,50) //Blending LUT points (MC), x3
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1596C RW 0x05F0_00F0
	UINT32 reg_blend_mc_lut_wei0            :8;	//(7:0,NA,240) //Blending LUT points (MC), y0
	UINT32 reg_blend_mc_lut_dif0            :8;	//(15:8,NA,0) //Blending LUT points (MC), x0
	UINT32 reg_blend_mc_lut_wei1            :8;	//(23:16,NA,240) //Blending LUT points (MC), y1
	UINT32 reg_blend_mc_lut_dif1            :8;	//(31:24,NA,5) //Blending LUT points (MC), x1
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15970 RW 0xFF00_4600
	UINT32 reg_blend_basic_lut_wei4         :8;	//(7:0,NA,0) //Blending LUT points (Basic), y4
	UINT32 reg_blend_basic_lut_dif4         :8;	//(15:8,NA,70) //Blending LUT points (Basic), x4
	UINT32 reg_blend_basic_lut_wei5         :8;	//(23:16,NA,0) //Blending LUT points (Basic), y5
	UINT32 reg_blend_basic_lut_dif5         :8;	//(31:24,NA,255) //Blending LUT points (Basic), x5
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15974 RW 0x32C0_1EE0
	UINT32 reg_blend_basic_lut_wei2         :8;	//(7:0,NA,224) //Blending LUT points (Basic), y2
	UINT32 reg_blend_basic_lut_dif2         :8;	//(15:8,NA,30) //Blending LUT points (Basic), x2
	UINT32 reg_blend_basic_lut_wei3         :8;	//(23:16,NA,192) //Blending LUT points (Basic), y3
	UINT32 reg_blend_basic_lut_dif3         :8;	//(31:24,NA,50) //Blending LUT points (Basic), x3
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15978 RW 0x05F0_00F0
	UINT32 reg_blend_basic_lut_wei0         :8;	//(7:0,NA,240) //Blending LUT points (Basic), y0
	UINT32 reg_blend_basic_lut_dif0         :8;	//(15:8,NA,0) //Blending LUT points (Basic), x0
	UINT32 reg_blend_basic_lut_wei1         :8;	//(23:16,NA,240) //Blending LUT points (Basic), y1
	UINT32 reg_blend_basic_lut_dif1         :8;	//(31:24,NA,5) //Blending LUT points (Basic), x1
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1597C RW 0xFFFF_46FF
	UINT32 reg_blend_final_lut_wei4         :8;	//(7:0,NA,255) //Blending LUT points (final), y4
	UINT32 reg_blend_final_lut_dif4         :8;	//(15:8,NA,70) //Blending LUT points (final), x4
	UINT32 reg_blend_final_lut_wei5         :8;	//(23:16,NA,255) //Blending LUT points (final), y5
	UINT32 reg_blend_final_lut_dif5         :8;	//(31:24,NA,255) //Blending LUT points (final), x5
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15980 RW 0x32F0_1EE0
	UINT32 reg_blend_final_lut_wei2         :8;	//(7:0,NA,224) //Blending LUT points (final), y2
	UINT32 reg_blend_final_lut_dif2         :8;	//(15:8,NA,30) //Blending LUT points (final), x2
	UINT32 reg_blend_final_lut_wei3         :8;	//(23:16,NA,240) //Blending LUT points (final), y3
	UINT32 reg_blend_final_lut_dif3         :8;	//(31:24,NA,50) //Blending LUT points (final), x3
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15984 RW 0x05C0_0080
	UINT32 reg_blend_final_lut_wei0         :8;	//(7:0,NA,128) //Blending LUT points (final), y0
	UINT32 reg_blend_final_lut_dif0         :8;	//(15:8,NA,0) //Blending LUT points (final), x0
	UINT32 reg_blend_final_lut_wei1         :8;	//(23:16,NA,192) //Blending LUT points (final), y1
	UINT32 reg_blend_final_lut_dif1         :8;	//(31:24,NA,5) //Blending LUT points (final), x1
	};
}PE_O26_AMG2_MTB_BLEND_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15988 RW 0x0000_0001
	UINT32 reg_warper_en                    :1;	//(0:0,NA,1) //Warper enable
	UINT32 resvd                            :31;
	};
}PE_O26_AMG2_MTB_WARP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15990 RW 0x0000_1111
	UINT32 reg_blf_en                       :1;	//(0:0,NA,1) //BLF enable
	UINT32 resvd0                           :3;
	UINT32 reg_blf_abs_diff_shift_yy        :2;	//(5:4,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), Y
	UINT32 resvd1                           :2;
	UINT32 reg_blf_abs_diff_shift_cb        :2;	//(9:8,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), CB
	UINT32 resvd2                           :2;
	UINT32 reg_blf_abs_diff_shift_cr        :2;	//(13:12,NA,1) //BLF pel weight LUT input control (ABS diff shift, 0~3 bits), CR
	UINT32 resvd3                           :18;
	};
}PE_O26_AMG2_MTB_BLF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15994 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_yy_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), Y
	UINT32 reg_blf_lut_val_yy_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), Y
	UINT32 reg_blf_lut_val_yy_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), Y
	UINT32 reg_blf_lut_val_yy_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15998 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_yy_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), Y
	UINT32 reg_blf_lut_val_yy_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), Y
	UINT32 reg_blf_lut_val_yy_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), Y
	UINT32 reg_blf_lut_val_yy_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1599C RW 0x181D_2126
	UINT32 reg_blf_lut_val_yy_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), Y
	UINT32 reg_blf_lut_val_yy_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), Y
	UINT32 reg_blf_lut_val_yy_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), Y
	UINT32 reg_blf_lut_val_yy_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159A0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_yy_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), Y
	UINT32 reg_blf_lut_val_yy_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), Y
	UINT32 reg_blf_lut_val_yy_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), Y
	UINT32 reg_blf_lut_val_yy_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159A4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_yy_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), Y
	UINT32 reg_blf_lut_val_yy_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), Y
	UINT32 reg_blf_lut_val_yy_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), Y
	UINT32 reg_blf_lut_val_yy_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159A8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_yy_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), Y
	UINT32 reg_blf_lut_val_yy_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), Y
	UINT32 reg_blf_lut_val_yy_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), Y
	UINT32 reg_blf_lut_val_yy_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159AC RW 0x0000_0000
	UINT32 reg_blf_lut_val_yy_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), Y
	UINT32 reg_blf_lut_val_yy_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), Y
	UINT32 reg_blf_lut_val_yy_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), Y
	UINT32 reg_blf_lut_val_yy_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159B0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_yy_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), Y
	UINT32 reg_blf_lut_val_yy_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), Y
	UINT32 reg_blf_lut_val_yy_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), Y
	UINT32 reg_blf_lut_val_yy_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), Y
	};
}PE_O26_AMG2_MTB_BLF_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159B4 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_cb_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), CB
	UINT32 reg_blf_lut_val_cb_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), CB
	UINT32 reg_blf_lut_val_cb_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), CB
	UINT32 reg_blf_lut_val_cb_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159B8 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_cb_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), CB
	UINT32 reg_blf_lut_val_cb_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), CB
	UINT32 reg_blf_lut_val_cb_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), CB
	UINT32 reg_blf_lut_val_cb_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159BC RW 0x181D_2126
	UINT32 reg_blf_lut_val_cb_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), CB
	UINT32 reg_blf_lut_val_cb_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), CB
	UINT32 reg_blf_lut_val_cb_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), CB
	UINT32 reg_blf_lut_val_cb_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159C0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_cb_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), CB
	UINT32 reg_blf_lut_val_cb_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), CB
	UINT32 reg_blf_lut_val_cb_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), CB
	UINT32 reg_blf_lut_val_cb_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159C4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_cb_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), CB
	UINT32 reg_blf_lut_val_cb_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), CB
	UINT32 reg_blf_lut_val_cb_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), CB
	UINT32 reg_blf_lut_val_cb_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159C8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_cb_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), CB
	UINT32 reg_blf_lut_val_cb_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), CB
	UINT32 reg_blf_lut_val_cb_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), CB
	UINT32 reg_blf_lut_val_cb_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159CC RW 0x0000_0000
	UINT32 reg_blf_lut_val_cb_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), CB
	UINT32 reg_blf_lut_val_cb_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), CB
	UINT32 reg_blf_lut_val_cb_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), CB
	UINT32 reg_blf_lut_val_cb_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159D0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_cb_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), CB
	UINT32 reg_blf_lut_val_cb_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), CB
	UINT32 reg_blf_lut_val_cb_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), CB
	UINT32 reg_blf_lut_val_cb_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), CB
	};
}PE_O26_AMG2_MTB_BLF_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159D4 RW 0x3B3E_3F3F
	UINT32 reg_blf_lut_val_cr_00            :8;	//(7:0,NA,63) //BLF pel weight LUT value, (00), CR
	UINT32 reg_blf_lut_val_cr_01            :8;	//(15:8,NA,63) //BLF pel weight LUT value, (01), CR
	UINT32 reg_blf_lut_val_cr_02            :8;	//(23:16,NA,62) //BLF pel weight LUT value, (02), CR
	UINT32 reg_blf_lut_val_cr_03            :8;	//(31:24,NA,59) //BLF pel weight LUT value, (03), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159D8 RW 0x2B30_3438
	UINT32 reg_blf_lut_val_cr_04            :8;	//(7:0,NA,56) //BLF pel weight LUT value, (04), CR
	UINT32 reg_blf_lut_val_cr_05            :8;	//(15:8,NA,52) //BLF pel weight LUT value, (05), CR
	UINT32 reg_blf_lut_val_cr_06            :8;	//(23:16,NA,48) //BLF pel weight LUT value, (06), CR
	UINT32 reg_blf_lut_val_cr_07            :8;	//(31:24,NA,43) //BLF pel weight LUT value, (07), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159DC RW 0x181D_2126
	UINT32 reg_blf_lut_val_cr_08            :8;	//(7:0,NA,38) //BLF pel weight LUT value, (08), CR
	UINT32 reg_blf_lut_val_cr_09            :8;	//(15:8,NA,33) //BLF pel weight LUT value, (09), CR
	UINT32 reg_blf_lut_val_cr_10            :8;	//(23:16,NA,29) //BLF pel weight LUT value, (10), CR
	UINT32 reg_blf_lut_val_cr_11            :8;	//(31:24,NA,24) //BLF pel weight LUT value, (11), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159E0 RW 0x0B0D_1114
	UINT32 reg_blf_lut_val_cr_12            :8;	//(7:0,NA,20) //BLF pel weight LUT value, (12), CR
	UINT32 reg_blf_lut_val_cr_13            :8;	//(15:8,NA,17) //BLF pel weight LUT value, (13), CR
	UINT32 reg_blf_lut_val_cr_14            :8;	//(23:16,NA,13) //BLF pel weight LUT value, (14), CR
	UINT32 reg_blf_lut_val_cr_15            :8;	//(31:24,NA,11) //BLF pel weight LUT value, (15), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159E4 RW 0x0305_0608
	UINT32 reg_blf_lut_val_cr_16            :8;	//(7:0,NA,8) //BLF pel weight LUT value, (16), CR
	UINT32 reg_blf_lut_val_cr_17            :8;	//(15:8,NA,6) //BLF pel weight LUT value, (17), CR
	UINT32 reg_blf_lut_val_cr_18            :8;	//(23:16,NA,5) //BLF pel weight LUT value, (18), CR
	UINT32 reg_blf_lut_val_cr_19            :8;	//(31:24,NA,3) //BLF pel weight LUT value, (19), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159E8 RW 0x0101_0202
	UINT32 reg_blf_lut_val_cr_20            :8;	//(7:0,NA,2) //BLF pel weight LUT value, (20), CR
	UINT32 reg_blf_lut_val_cr_21            :8;	//(15:8,NA,2) //BLF pel weight LUT value, (21), CR
	UINT32 reg_blf_lut_val_cr_22            :8;	//(23:16,NA,1) //BLF pel weight LUT value, (22), CR
	UINT32 reg_blf_lut_val_cr_23            :8;	//(31:24,NA,1) //BLF pel weight LUT value, (23), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159EC RW 0x0000_0000
	UINT32 reg_blf_lut_val_cr_24            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (24), CR
	UINT32 reg_blf_lut_val_cr_25            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (25), CR
	UINT32 reg_blf_lut_val_cr_26            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (26), CR
	UINT32 reg_blf_lut_val_cr_27            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (27), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159F0 RW 0x0000_0000
	UINT32 reg_blf_lut_val_cr_28            :8;	//(7:0,NA,0) //BLF pel weight LUT value, (28), CR
	UINT32 reg_blf_lut_val_cr_29            :8;	//(15:8,NA,0) //BLF pel weight LUT value, (29), CR
	UINT32 reg_blf_lut_val_cr_30            :8;	//(23:16,NA,0) //BLF pel weight LUT value, (30), CR
	UINT32 reg_blf_lut_val_cr_31            :8;	//(31:24,NA,0) //BLF pel weight LUT value, (31), CR
	};
}PE_O26_AMG2_MTB_BLF_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159F4 RW 0x353B_3E3F
	UINT32 reg_blf_lut_val_spa_00           :8;	//(7:0,NA,63) //BLF spatial weight LUT value, [y0][x0]
	UINT32 reg_blf_lut_val_spa_01           :8;	//(15:8,NA,62) //BLF spatial weight LUT value, [y0][x1]
	UINT32 reg_blf_lut_val_spa_02           :8;	//(23:16,NA,59) //BLF spatial weight LUT value, [y0][x2]
	UINT32 reg_blf_lut_val_spa_03           :8;	//(31:24,NA,53) //BLF spatial weight LUT value, [y0][x3]
	};
}PE_O26_AMG2_MTB_BLF_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159F8 RW 0x393D_3E2E
	UINT32 reg_blf_lut_val_spa_04           :8;	//(7:0,NA,46) //BLF spatial weight LUT value, [y0][x4]
	UINT32 reg_blf_lut_val_spa_05           :8;	//(15:8,NA,62) //BLF spatial weight LUT value, [y1][x0]
	UINT32 reg_blf_lut_val_spa_06           :8;	//(23:16,NA,61) //BLF spatial weight LUT value, [y1][x1]
	UINT32 reg_blf_lut_val_spa_07           :8;	//(31:24,NA,57) //BLF spatial weight LUT value, [y1][x2] (cen)
	};
}PE_O26_AMG2_MTB_BLF_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC159FC RW 0x393B_2D34
	UINT32 reg_blf_lut_val_spa_08           :8;	//(7:0,NA,52) //BLF spatial weight LUT value, [y1][x3]
	UINT32 reg_blf_lut_val_spa_09           :8;	//(15:8,NA,45) //BLF spatial weight LUT value, [y1][x4]
	UINT32 reg_blf_lut_val_spa_10           :8;	//(23:16,NA,59) //BLF spatial weight LUT value, [y2][x0]
	UINT32 reg_blf_lut_val_spa_11           :8;	//(31:24,NA,57) //BLF spatial weight LUT value, [y2][x1]
	};
}PE_O26_AMG2_MTB_BLF_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15A00 RW 0x002A_3136
	UINT32 reg_blf_lut_val_spa_12           :8;	//(7:0,NA,54) //BLF spatial weight LUT value, [y2][x2]
	UINT32 reg_blf_lut_val_spa_13           :8;	//(15:8,NA,49) //BLF spatial weight LUT value, [y2][x3]
	UINT32 reg_blf_lut_val_spa_14           :8;	//(23:16,NA,42) //BLF spatial weight LUT value, [y2][x4]
	UINT32 resvd                            :8;
	};
}PE_O26_AMG2_MTB_BLF_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15A10 RW 0x0000_0001
	UINT32 reg_median_filt_en               :1;	//(0:0,NA,1) //Median filter enable
	UINT32 resvd                            :31;
	};
}PE_O26_AMG2_MTB_MEDIAN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15A20 RW 0x0000_0000
	UINT32 reg_dbg_mtb_mode                 :2;	//(1:0,NA,0) //Debug mode	0 : Normal AMG output	1 : Debug MC	2 : Debug Basic	3 : Debug Final
	UINT32 resvd0                           :2;
	UINT32 reg_dbg_mtb_map                  :5;	//(8:4,NA,0) //Debug mode map selection	0 : Normal MTB output	1 : CUR map	2 : CUR map (CA)	3 : PRV map	4 : PRV map (CA)	5 : MV, x	6 : MV, y	7 : Warp map	8 : Warp mode	9 : BLF map	10: BLF mode	11: Blend map	12: Blend alpha	13: Median map
	UINT32 resvd1                           :3;
	UINT32 reg_dbg_mv_shift                 :2;	//(13:12,NA,0) //Debug mode MV shift	0 : MV shift 1 (<<1)	1 : MV shift 2 (<<2)	2 : MV shift 3 (<<3)	3 : MV shift 4 (<<4)
	UINT32 resvd2                           :18;
	};
}PE_O26_AMG2_MTB_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AD0 RO 0x0000_0000
	UINT32 reg_mon_in_mv_sucfail            :16;	//(15:0,NA,0) //Core input (MV) success/fail monitoring register
	UINT32 reg_mon_in_mv_fin_vert           :9;	//(24:16,NA,0) //Core input (MV) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AD4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :16;	//(15:0,NA,0) //Core input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :9;	//(24:16,NA,0) //Core input (pel, Y) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AD8 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :16;	//(15:0,NA,0) //Core input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :9;	//(24:16,NA,0) //Core input (pel, C) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15ADC RO 0x0000_0000
	UINT32 reg_mon_in_mc_prv_sucfail        :16;	//(15:0,NA,0) //Core input (MC, PRV) success/fail monitoring register
	UINT32 reg_mon_in_mc_prv_fin_vert       :9;	//(24:16,NA,0) //Core input (MC, PRV) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AE0 RO 0x0000_0000
	UINT32 reg_mon_in_mc_cur_sucfail        :16;	//(15:0,NA,0) //Core input (MC, CUR) success/fail monitoring register
	UINT32 reg_mon_in_mc_cur_fin_vert       :9;	//(24:16,NA,0) //Core input (MC, CUR) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AE4 RO 0x0000_0000
	UINT32 reg_mon_in_basic_prv_sucfail     :16;	//(15:0,NA,0) //Core input (Basic, PRV) success/fail monitoring register
	UINT32 reg_mon_in_basic_prv_fin_vert    :9;	//(24:16,NA,0) //Core input (Basic, PRV) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AE8 RO 0x0000_0000
	UINT32 reg_mon_in_basic_cur_sucfail     :16;	//(15:0,NA,0) //Core input (Basic, CUR) success/fail monitoring register
	UINT32 reg_mon_in_basic_cur_fin_vert    :9;	//(24:16,NA,0) //Core input (Basic, CUR) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AEC RO 0x0000_0000
	UINT32 reg_mon_in_final_mres_sucfail    :16;	//(15:0,NA,0) //Core input (Final, MC result) success/fail monitoring register
	UINT32 reg_mon_in_final_mres_fin_vert   :9;	//(24:16,NA,0) //Core input (Final, MC result) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AF0 RO 0x0000_0000
	UINT32 reg_mon_in_final_bres_sucfail    :16;	//(15:0,NA,0) //Core input (Final, Basic result) success/fail monitoring register
	UINT32 reg_mon_in_final_bres_fin_vert   :9;	//(24:16,NA,0) //Core input (Final, Basic result) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC15AF4 RO 0x0000_0000
	UINT32 reg_mon_out_sucfail              :16;	//(15:0,NA,0) //Core output success/fail monitoring register
	UINT32 reg_mon_out_fin_vert             :9;	//(24:16,NA,0) //Core output previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG2_MTB_MTB_CORE_STAT_09_T;

typedef struct {
	PE_O26_AMG2_MTB_CA_CTRL_00_T                                ca_ctrl_00;	//0xCCC15900
	PE_O26_AMG2_MTB_CA_CTRL_01_T                                ca_ctrl_01;	//0xCCC15904
	PE_O26_AMG2_MTB_CA_CTRL_02_T                                ca_ctrl_02;	//0xCCC15908
	PE_O26_AMG2_MTB_CA_CTRL_03_T                                ca_ctrl_03;	//0xCCC1590C
	PE_O26_AMG2_MTB_CA_CTRL_04_T                                ca_ctrl_04;	//0xCCC15910
	PE_O26_AMG2_MTB_CA_CTRL_05_T                                ca_ctrl_05;	//0xCCC15914
	PE_O26_AMG2_MTB_CA_CTRL_06_T                                ca_ctrl_06;	//0xCCC15918
	PE_O26_AMG2_MTB_CA_CTRL_07_T                                ca_ctrl_07;	//0xCCC1591C
	PE_O26_AMG2_MTB_CA_CTRL_08_T                                ca_ctrl_08;	//0xCCC15920
	PE_O26_AMG2_MTB_CA_CTRL_09_T                                ca_ctrl_09;	//0xCCC15924
	PE_O26_AMG2_MTB_CA_CTRL_10_T                                ca_ctrl_10;	//0xCCC15928
	PE_O26_AMG2_MTB_CA_CTRL_11_T                                ca_ctrl_11;	//0xCCC1592C
	PE_O26_AMG2_MTB_CA_CTRL_12_T                                ca_ctrl_12;	//0xCCC15930
	PE_O26_AMG2_MTB_CA_CTRL_13_T                                ca_ctrl_13;	//0xCCC15934
	PE_O26_AMG2_MTB_CA_CTRL_14_T                                ca_ctrl_14;	//0xCCC15938
	PE_O26_AMG2_MTB_CA_CTRL_15_T                                ca_ctrl_15;	//0xCCC1593C
	PE_O26_AMG2_MTB_CA_CTRL_16_T                                ca_ctrl_16;	//0xCCC15940
	PE_O26_AMG2_MTB_CA_CTRL_17_T                                ca_ctrl_17;	//0xCCC15944
	PE_O26_AMG2_MTB_CA_CTRL_18_T                                ca_ctrl_18;	//0xCCC15948
	PE_O26_AMG2_MTB_CA_CTRL_19_T                                ca_ctrl_19;	//0xCCC1594C
	PE_O26_AMG2_MTB_CA_CTRL_20_T                                ca_ctrl_20;	//0xCCC15950
	UINT32                                                       reserved0;	//0xCCC15954
	UINT32                                                       reserved1;	//0xCCC15958
	UINT32                                                       reserved2;	//0xCCC1595C
	PE_O26_AMG2_MTB_BLEND_CTRL_00_T                          blend_ctrl_00;	//0xCCC15960
	PE_O26_AMG2_MTB_BLEND_CTRL_01_T                          blend_ctrl_01;	//0xCCC15964
	PE_O26_AMG2_MTB_BLEND_CTRL_02_T                          blend_ctrl_02;	//0xCCC15968
	PE_O26_AMG2_MTB_BLEND_CTRL_03_T                          blend_ctrl_03;	//0xCCC1596C
	PE_O26_AMG2_MTB_BLEND_CTRL_04_T                          blend_ctrl_04;	//0xCCC15970
	PE_O26_AMG2_MTB_BLEND_CTRL_05_T                          blend_ctrl_05;	//0xCCC15974
	PE_O26_AMG2_MTB_BLEND_CTRL_06_T                          blend_ctrl_06;	//0xCCC15978
	PE_O26_AMG2_MTB_BLEND_CTRL_07_T                          blend_ctrl_07;	//0xCCC1597C
	PE_O26_AMG2_MTB_BLEND_CTRL_08_T                          blend_ctrl_08;	//0xCCC15980
	PE_O26_AMG2_MTB_BLEND_CTRL_09_T                          blend_ctrl_09;	//0xCCC15984
	PE_O26_AMG2_MTB_WARP_CTRL_00_T                            warp_ctrl_00;	//0xCCC15988
	UINT32                                                       reserved3;	//0xCCC1598C
	PE_O26_AMG2_MTB_BLF_CTRL_00_T                              blf_ctrl_00;	//0xCCC15990
	PE_O26_AMG2_MTB_BLF_CTRL_01_T                              blf_ctrl_01;	//0xCCC15994
	PE_O26_AMG2_MTB_BLF_CTRL_02_T                              blf_ctrl_02;	//0xCCC15998
	PE_O26_AMG2_MTB_BLF_CTRL_03_T                              blf_ctrl_03;	//0xCCC1599C
	PE_O26_AMG2_MTB_BLF_CTRL_04_T                              blf_ctrl_04;	//0xCCC159A0
	PE_O26_AMG2_MTB_BLF_CTRL_05_T                              blf_ctrl_05;	//0xCCC159A4
	PE_O26_AMG2_MTB_BLF_CTRL_06_T                              blf_ctrl_06;	//0xCCC159A8
	PE_O26_AMG2_MTB_BLF_CTRL_07_T                              blf_ctrl_07;	//0xCCC159AC
	PE_O26_AMG2_MTB_BLF_CTRL_08_T                              blf_ctrl_08;	//0xCCC159B0
	PE_O26_AMG2_MTB_BLF_CTRL_09_T                              blf_ctrl_09;	//0xCCC159B4
	PE_O26_AMG2_MTB_BLF_CTRL_10_T                              blf_ctrl_10;	//0xCCC159B8
	PE_O26_AMG2_MTB_BLF_CTRL_11_T                              blf_ctrl_11;	//0xCCC159BC
	PE_O26_AMG2_MTB_BLF_CTRL_12_T                              blf_ctrl_12;	//0xCCC159C0
	PE_O26_AMG2_MTB_BLF_CTRL_13_T                              blf_ctrl_13;	//0xCCC159C4
	PE_O26_AMG2_MTB_BLF_CTRL_14_T                              blf_ctrl_14;	//0xCCC159C8
	PE_O26_AMG2_MTB_BLF_CTRL_15_T                              blf_ctrl_15;	//0xCCC159CC
	PE_O26_AMG2_MTB_BLF_CTRL_16_T                              blf_ctrl_16;	//0xCCC159D0
	PE_O26_AMG2_MTB_BLF_CTRL_17_T                              blf_ctrl_17;	//0xCCC159D4
	PE_O26_AMG2_MTB_BLF_CTRL_18_T                              blf_ctrl_18;	//0xCCC159D8
	PE_O26_AMG2_MTB_BLF_CTRL_19_T                              blf_ctrl_19;	//0xCCC159DC
	PE_O26_AMG2_MTB_BLF_CTRL_20_T                              blf_ctrl_20;	//0xCCC159E0
	PE_O26_AMG2_MTB_BLF_CTRL_21_T                              blf_ctrl_21;	//0xCCC159E4
	PE_O26_AMG2_MTB_BLF_CTRL_22_T                              blf_ctrl_22;	//0xCCC159E8
	PE_O26_AMG2_MTB_BLF_CTRL_23_T                              blf_ctrl_23;	//0xCCC159EC
	PE_O26_AMG2_MTB_BLF_CTRL_24_T                              blf_ctrl_24;	//0xCCC159F0
	PE_O26_AMG2_MTB_BLF_CTRL_25_T                              blf_ctrl_25;	//0xCCC159F4
	PE_O26_AMG2_MTB_BLF_CTRL_26_T                              blf_ctrl_26;	//0xCCC159F8
	PE_O26_AMG2_MTB_BLF_CTRL_27_T                              blf_ctrl_27;	//0xCCC159FC
	PE_O26_AMG2_MTB_BLF_CTRL_28_T                              blf_ctrl_28;	//0xCCC15A00
	UINT32                                                       reserved4;	//0xCCC15A04
	UINT32                                                       reserved5;	//0xCCC15A08
	UINT32                                                       reserved6;	//0xCCC15A0C
	PE_O26_AMG2_MTB_MEDIAN_CTRL_00_T                        median_ctrl_00;	//0xCCC15A10
	UINT32                                                       reserved7;	//0xCCC15A14
	UINT32                                                       reserved8;	//0xCCC15A18
	UINT32                                                       reserved9;	//0xCCC15A1C
	PE_O26_AMG2_MTB_DEBUG_CTRL_00_T                          debug_ctrl_00;	//0xCCC15A20
	UINT32                                                      reserved10;	//0xCCC15A24
	UINT32                                                      reserved11;	//0xCCC15A28
	UINT32                                                      reserved12;	//0xCCC15A2C
	UINT32                                                      reserved13;	//0xCCC15A30
	UINT32                                                      reserved14;	//0xCCC15A34
	UINT32                                                      reserved15;	//0xCCC15A38
	UINT32                                                      reserved16;	//0xCCC15A3C
	UINT32                                                      reserved17;	//0xCCC15A40
	UINT32                                                      reserved18;	//0xCCC15A44
	UINT32                                                      reserved19;	//0xCCC15A48
	UINT32                                                      reserved20;	//0xCCC15A4C
	UINT32                                                      reserved21;	//0xCCC15A50
	UINT32                                                      reserved22;	//0xCCC15A54
	UINT32                                                      reserved23;	//0xCCC15A58
	UINT32                                                      reserved24;	//0xCCC15A5C
	UINT32                                                      reserved25;	//0xCCC15A60
	UINT32                                                      reserved26;	//0xCCC15A64
	UINT32                                                      reserved27;	//0xCCC15A68
	UINT32                                                      reserved28;	//0xCCC15A6C
	UINT32                                                      reserved29;	//0xCCC15A70
	UINT32                                                      reserved30;	//0xCCC15A74
	UINT32                                                      reserved31;	//0xCCC15A78
	UINT32                                                      reserved32;	//0xCCC15A7C
	UINT32                                                      reserved33;	//0xCCC15A80
	UINT32                                                      reserved34;	//0xCCC15A84
	UINT32                                                      reserved35;	//0xCCC15A88
	UINT32                                                      reserved36;	//0xCCC15A8C
	UINT32                                                      reserved37;	//0xCCC15A90
	UINT32                                                      reserved38;	//0xCCC15A94
	UINT32                                                      reserved39;	//0xCCC15A98
	UINT32                                                      reserved40;	//0xCCC15A9C
	UINT32                                                      reserved41;	//0xCCC15AA0
	UINT32                                                      reserved42;	//0xCCC15AA4
	UINT32                                                      reserved43;	//0xCCC15AA8
	UINT32                                                      reserved44;	//0xCCC15AAC
	UINT32                                                      reserved45;	//0xCCC15AB0
	UINT32                                                      reserved46;	//0xCCC15AB4
	UINT32                                                      reserved47;	//0xCCC15AB8
	UINT32                                                      reserved48;	//0xCCC15ABC
	UINT32                                                      reserved49;	//0xCCC15AC0
	UINT32                                                      reserved50;	//0xCCC15AC4
	UINT32                                                      reserved51;	//0xCCC15AC8
	UINT32                                                      reserved52;	//0xCCC15ACC
	PE_O26_AMG2_MTB_MTB_CORE_STAT_00_T                    mtb_core_stat_00;	//0xCCC15AD0
	PE_O26_AMG2_MTB_MTB_CORE_STAT_01_T                    mtb_core_stat_01;	//0xCCC15AD4
	PE_O26_AMG2_MTB_MTB_CORE_STAT_02_T                    mtb_core_stat_02;	//0xCCC15AD8
	PE_O26_AMG2_MTB_MTB_CORE_STAT_03_T                    mtb_core_stat_03;	//0xCCC15ADC
	PE_O26_AMG2_MTB_MTB_CORE_STAT_04_T                    mtb_core_stat_04;	//0xCCC15AE0
	PE_O26_AMG2_MTB_MTB_CORE_STAT_05_T                    mtb_core_stat_05;	//0xCCC15AE4
	PE_O26_AMG2_MTB_MTB_CORE_STAT_06_T                    mtb_core_stat_06;	//0xCCC15AE8
	PE_O26_AMG2_MTB_MTB_CORE_STAT_07_T                    mtb_core_stat_07;	//0xCCC15AEC
	PE_O26_AMG2_MTB_MTB_CORE_STAT_08_T                    mtb_core_stat_08;	//0xCCC15AF0
	PE_O26_AMG2_MTB_MTB_CORE_STAT_09_T                    mtb_core_stat_09;	//0xCCC15AF4
}PE_AMG_MTB_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16100 RW 0x0000_0001
	UINT32 reg_blur_filt_en                 :1;	//(0:0,NA,1) //Blur filter enable
	UINT32 resvd                            :31;
	};
}PE_O26_AMG3_GRM_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16104 RW 0x0007_0708
	UINT32 reg_blur_y_coef_0                :7;	//(6:0,NA,8) //Blur filter (Y) coefficient, [1][1] (center)
	UINT32 resvd0                           :1;
	UINT32 reg_blur_y_coef_1                :7;	//(14:8,NA,7) //Blur filter (Y) coefficient, [0][1],[1][0],[1][2],[2][1]
	UINT32 resvd1                           :1;
	UINT32 reg_blur_y_coef_2                :7;	//(22:16,NA,7) //Blur filter (Y) coefficient, [0][0],[0][2],[2][0],[2][2]
	UINT32 resvd2                           :9;
	};
}PE_O26_AMG3_GRM_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16108 RW 0x0007_0708
	UINT32 reg_blur_c_coef_0                :7;	//(6:0,NA,8) //Blur filter (C) coefficient, [1][1] (center)
	UINT32 resvd0                           :1;
	UINT32 reg_blur_c_coef_1                :7;	//(14:8,NA,7) //Blur filter (C) coefficient, [0][1],[1][0],[1][2],[2][1]
	UINT32 resvd1                           :1;
	UINT32 reg_blur_c_coef_2                :7;	//(22:16,NA,7) //Blur filter (C) coefficient, [0][0],[0][2],[2][0],[2][2]
	UINT32 resvd2                           :9;
	};
}PE_O26_AMG3_GRM_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16110 RW 0x7C98_12A0
	UINT32 reg_yc2rgb_coef0                 :15;	//(14:0,NA,4768) //YC2RGB coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef1                 :15;	//(30:16,NA,-872) //YC2RGB coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16114 RW 0x12A0_7775
	UINT32 reg_yc2rgb_coef2                 :15;	//(14:0,NA,-2187) //YC2RGB coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef3                 :15;	//(30:16,NA,4768) //YC2RGB coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16118 RW 0x0000_21D7
	UINT32 reg_yc2rgb_coef4                 :15;	//(14:0,NA,8663) //YC2RGB coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef5                 :15;	//(30:16,NA,0) //YC2RGB coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1611C RW 0x0000_12A0
	UINT32 reg_yc2rgb_coef6                 :15;	//(14:0,NA,4768) //YC2RGB coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_coef7                 :15;	//(30:16,NA,0) //YC2RGB coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16120 RW 0x0000_1CB0
	UINT32 reg_yc2rgb_coef8                 :15;	//(14:0,NA,7344) //YC2RGB coefficient 8
	UINT32 resvd                            :17;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16124 RW 0x0780_07F0
	UINT32 reg_yc2rgb_ofst0                 :11;	//(10:0,NA,-16) //YC2RGB offset 0
	UINT32 resvd0                           :5;
	UINT32 reg_yc2rgb_ofst1                 :11;	//(26:16,NA,-128) //YC2RGB offset 1
	UINT32 resvd1                           :5;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16128 RW 0x0000_0780
	UINT32 reg_yc2rgb_ofst2                 :11;	//(10:0,NA,-128) //YC2RGB offset 2
	UINT32 resvd0                           :5;
	UINT32 reg_yc2rgb_ofst3                 :11;	//(26:16,NA,0) //YC2RGB offset 3
	UINT32 resvd1                           :5;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1612C RW 0x0000_0000
	UINT32 reg_yc2rgb_ofst4                 :15;	//(14:0,NA,0) //YC2RGB offset 4
	UINT32 resvd0                           :1;
	UINT32 reg_yc2rgb_ofst5                 :15;	//(30:16,NA,0) //YC2RGB offset 5
	UINT32 resvd1                           :1;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16130 RW 0x0080_8001
	UINT32 reg_rgb2hsv_sat_sel              :1;	//(0:0,NA,1) //RGB2HSV saturation selection (0: div_mode, 1: simple_mode)
	UINT32 resvd0                           :7;
	UINT32 reg_rgb2hsv_sgain                :8;	//(15:8,NA,128) //RGB2HSV saturation gain
	UINT32 reg_rgb2hsv_vgain                :8;	//(23:16,NA,128) //RGB2HSV value gain
	UINT32 resvd1                           :8;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16134 RW 0x0080_8080
	UINT32 reg_rgb2hsv_hoffset              :8;	//(7:0,NA,128) //RGB2HSV hue offset
	UINT32 reg_rgb2hsv_soffset              :8;	//(15:8,NA,128) //RGB2HSV saturation offset
	UINT32 reg_rgb2hsv_voffset              :8;	//(23:16,NA,128) //RGB2HSV value offset
	UINT32 resvd                            :8;
	};
}PE_O26_AMG3_GRM_YC2HSV_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16138 RW 0x5014_0000
	UINT32 reg_lut_depth_map_y0             :8;	//(7:0,NA,0) //LUT (depth map) control point, y0
	UINT32 reg_lut_depth_map_x0             :8;	//(15:8,NA,0) //LUT (depth map) control point, x0
	UINT32 reg_lut_depth_map_y1             :8;	//(23:16,NA,20) //LUT (depth map) control point, y1
	UINT32 reg_lut_depth_map_x1             :8;	//(31:24,NA,80) //LUT (depth map) control point, x1
	};
}PE_O26_AMG3_GRM_DEPTH_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1613C RW 0xFFFF_6E6E
	UINT32 reg_lut_depth_map_y2             :8;	//(7:0,NA,110) //LUT (depth map) control point, y2
	UINT32 reg_lut_depth_map_x2             :8;	//(15:8,NA,110) //LUT (depth map) control point, x2
	UINT32 reg_lut_depth_map_y3             :8;	//(23:16,NA,255) //LUT (depth map) control point, y3
	UINT32 reg_lut_depth_map_x3             :8;	//(31:24,NA,255) //LUT (depth map) control point, x3
	};
}PE_O26_AMG3_GRM_DEPTH_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16140 RW 0x64B4_0000
	UINT32 reg_rgn_LU_x_stt                 :8;	//(7:0,NA,0) //Region position (LU), x stt
	UINT32 reg_rgn_LU_y_stt                 :8;	//(15:8,NA,0) //Region position (LU), x end
	UINT32 reg_rgn_LU_x_end                 :8;	//(23:16,NA,180) //Region position (LU), y stt
	UINT32 reg_rgn_LU_y_end                 :8;	//(31:24,NA,100) //Region position (LU), y end
	};
}PE_O26_AMG3_GRM_REGION_POS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16144 RW 0x64F0_003C
	UINT32 reg_rgn_RU_x_stt                 :8;	//(7:0,NA,60) //Region position (RU), x stt
	UINT32 reg_rgn_RU_y_stt                 :8;	//(15:8,NA,0) //Region position (RU), x end
	UINT32 reg_rgn_RU_x_end                 :8;	//(23:16,NA,240) //Region position (RU), y stt
	UINT32 reg_rgn_RU_y_end                 :8;	//(31:24,NA,100) //Region position (RU), y end
	};
}PE_O26_AMG3_GRM_REGION_POS_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16148 RW 0x87B4_2200
	UINT32 reg_rgn_LD_x_stt                 :8;	//(7:0,NA,0) //Region position (LD), x stt
	UINT32 reg_rgn_LD_y_stt                 :8;	//(15:8,NA,34) //Region position (LD), x end
	UINT32 reg_rgn_LD_x_end                 :8;	//(23:16,NA,180) //Region position (LD), y stt
	UINT32 reg_rgn_LD_y_end                 :8;	//(31:24,NA,135) //Region position (LD), y end
	};
}PE_O26_AMG3_GRM_REGION_POS_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1614C RW 0x87F0_223C
	UINT32 reg_rgn_RD_x_stt                 :8;	//(7:0,NA,60) //Region position (RD), x stt
	UINT32 reg_rgn_RD_y_stt                 :8;	//(15:8,NA,34) //Region position (RD), x end
	UINT32 reg_rgn_RD_x_end                 :8;	//(23:16,NA,240) //Region position (RD), y stt
	UINT32 reg_rgn_RD_y_end                 :8;	//(31:24,NA,135) //Region position (RD), y end
	};
}PE_O26_AMG3_GRM_REGION_POS_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16150 RW 0x0000_3200
	UINT32 reg_hist_sel                     :2;	//(1:0,NA,0) //Read histogram selection (0: LU, 1: RU, 2: LD, 3: RD)
	UINT32 resvd0                           :6;
	UINT32 reg_depth_hist_th                :8;	//(15:8,NA,50) //Depth map threshold for histogram
	UINT32 resvd1                           :16;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16154 RW 0xFFFF_281E
	UINT32 reg_sat_h_hist_th                :8;	//(7:0,NA,30) //Saturation threshold for HUE histogram
	UINT32 reg_val_h_hist_th                :8;	//(15:8,NA,40) //Value threshold for HUE histogram
	UINT32 reg_sat_v_hist_th                :8;	//(23:16,NA,255) //Saturation threshold for VAL histogram
	UINT32 reg_val_v_hist_th                :8;	//(31:24,NA,255) //Value threshold for VAL histogram
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16158 RW 0x0300_0301
	UINT32 reg_hist_frame_step              :8;	//(7:0,NA,1) //Histogram IIR frame step
	UINT32 reg_hist_step_size               :8;	//(15:8,NA,3) //Histogram IIR step size
	UINT32 reg_hist_fw_ctrl_en              :1;	//(16:16,NA,0) //Histogram IIR FW cotrol enable
	UINT32 resvd                            :7;
	UINT32 reg_hist_fw_step_size            :8;	//(31:24,NA,3) //Histogram IIR FW step size
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1615C RW 0x0033_0033
	UINT32 reg_hue_coef_0                   :9;	//(8:0,NA,51) //Histogram filter (HUE) coefficient, [ 6] (center)
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_1                   :9;	//(24:16,NA,51) //Histogram filter (HUE) coefficient, [ 5][ 7]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16160 RW 0x0000_0033
	UINT32 reg_hue_coef_2                   :9;	//(8:0,NA,51) //Histogram filter (HUE) coefficient, [ 4][ 8]
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_3                   :9;	//(24:16,NA,0) //Histogram filter (HUE) coefficient, [ 3][ 9]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16164 RW 0x0000_0000
	UINT32 reg_hue_coef_4                   :9;	//(8:0,NA,0) //Histogram filter (HUE) coefficient, [ 2][10]
	UINT32 resvd0                           :7;
	UINT32 reg_hue_coef_5                   :9;	//(24:16,NA,0) //Histogram filter (HUE) coefficient, [ 1][11]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16168 RW 0x0000_0000
	UINT32 reg_hue_coef_6                   :9;	//(8:0,NA,0) //Histogram filter (HUE) coefficient, [ 0][12]
	UINT32 resvd                            :23;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1616C RW 0x0033_0033
	UINT32 reg_val_coef_0                   :9;	//(8:0,NA,51) //Histogram filter (VAL) coefficient, [ 6] (center)
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_1                   :9;	//(24:16,NA,51) //Histogram filter (VAL) coefficient, [ 5][ 7]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16170 RW 0x0000_0033
	UINT32 reg_val_coef_2                   :9;	//(8:0,NA,51) //Histogram filter (VAL) coefficient, [ 4][ 8]
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_3                   :9;	//(24:16,NA,0) //Histogram filter (VAL) coefficient, [ 3][ 9]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16174 RW 0x0000_0000
	UINT32 reg_val_coef_4                   :9;	//(8:0,NA,0) //Histogram filter (VAL) coefficient, [ 2][10]
	UINT32 resvd0                           :7;
	UINT32 reg_val_coef_5                   :9;	//(24:16,NA,0) //Histogram filter (VAL) coefficient, [ 1][11]
	UINT32 resvd1                           :7;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16178 RW 0x0000_0000
	UINT32 reg_val_coef_6                   :9;	//(8:0,NA,0) //Histogram filter (VAL) coefficient, [ 0][12]
	UINT32 resvd                            :23;
	};
}PE_O26_AMG3_GRM_HISTOGRAM_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1617C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_00               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 0)
	UINT32 reg_hist_fg_hue_00               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 0)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16180 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_01               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 1)
	UINT32 reg_hist_fg_hue_01               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 1)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16184 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_02               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 2)
	UINT32 reg_hist_fg_hue_02               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 2)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16188 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_03               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 3)
	UINT32 reg_hist_fg_hue_03               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 3)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1618C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_04               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 4)
	UINT32 reg_hist_fg_hue_04               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 4)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16190 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_05               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 5)
	UINT32 reg_hist_fg_hue_05               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 5)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16194 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_06               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 6)
	UINT32 reg_hist_fg_hue_06               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 6)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16198 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_07               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 7)
	UINT32 reg_hist_fg_hue_07               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 7)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1619C RO 0x0000_0000
	UINT32 reg_hist_bg_hue_08               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 8)
	UINT32 reg_hist_fg_hue_08               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 8)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161A0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_09               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 9)
	UINT32 reg_hist_fg_hue_09               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 9)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161A4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_10               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 10)
	UINT32 reg_hist_fg_hue_10               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 10)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161A8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_11               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 11)
	UINT32 reg_hist_fg_hue_11               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 11)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161AC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_12               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 12)
	UINT32 reg_hist_fg_hue_12               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 12)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161B0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_13               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 13)
	UINT32 reg_hist_fg_hue_13               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 13)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161B4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_14               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 14)
	UINT32 reg_hist_fg_hue_14               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 14)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161B8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_15               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 15)
	UINT32 reg_hist_fg_hue_15               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 15)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161BC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_16               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 16)
	UINT32 reg_hist_fg_hue_16               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 16)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161C0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_17               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 17)
	UINT32 reg_hist_fg_hue_17               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 17)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161C4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_18               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 18)
	UINT32 reg_hist_fg_hue_18               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 18)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161C8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_19               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 19)
	UINT32 reg_hist_fg_hue_19               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 19)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161CC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_20               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 20)
	UINT32 reg_hist_fg_hue_20               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 20)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161D0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_21               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 21)
	UINT32 reg_hist_fg_hue_21               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 21)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161D4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_22               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 22)
	UINT32 reg_hist_fg_hue_22               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 22)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161D8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_23               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 23)
	UINT32 reg_hist_fg_hue_23               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 23)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161DC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_24               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 24)
	UINT32 reg_hist_fg_hue_24               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 24)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161E0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_25               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 25)
	UINT32 reg_hist_fg_hue_25               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 25)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161E4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_26               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 26)
	UINT32 reg_hist_fg_hue_26               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 26)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161E8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_27               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 27)
	UINT32 reg_hist_fg_hue_27               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 27)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161EC RO 0x0000_0000
	UINT32 reg_hist_bg_hue_28               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 28)
	UINT32 reg_hist_fg_hue_28               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 28)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161F0 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_29               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 29)
	UINT32 reg_hist_fg_hue_29               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 29)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161F4 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_30               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 30)
	UINT32 reg_hist_fg_hue_30               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 30)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161F8 RO 0x0000_0000
	UINT32 reg_hist_bg_hue_31               :16;	//(15:0,NA,0) //Histogram read data (BG, HUE, bin 31)
	UINT32 reg_hist_fg_hue_31               :16;	//(31:16,NA,0) //Histogram read data (FG, HUE, bin 31)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC161FC RO 0x0000_0000
	UINT32 reg_hist_bg_val_00               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 0)
	UINT32 reg_hist_fg_val_00               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 0)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16200 RO 0x0000_0000
	UINT32 reg_hist_bg_val_01               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 1)
	UINT32 reg_hist_fg_val_01               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 1)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16204 RO 0x0000_0000
	UINT32 reg_hist_bg_val_02               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 2)
	UINT32 reg_hist_fg_val_02               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 2)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16208 RO 0x0000_0000
	UINT32 reg_hist_bg_val_03               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 3)
	UINT32 reg_hist_fg_val_03               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 3)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1620C RO 0x0000_0000
	UINT32 reg_hist_bg_val_04               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 4)
	UINT32 reg_hist_fg_val_04               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 4)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16210 RO 0x0000_0000
	UINT32 reg_hist_bg_val_05               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 5)
	UINT32 reg_hist_fg_val_05               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 5)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16214 RO 0x0000_0000
	UINT32 reg_hist_bg_val_06               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 6)
	UINT32 reg_hist_fg_val_06               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 6)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16218 RO 0x0000_0000
	UINT32 reg_hist_bg_val_07               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 7)
	UINT32 reg_hist_fg_val_07               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 7)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1621C RO 0x0000_0000
	UINT32 reg_hist_bg_val_08               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 8)
	UINT32 reg_hist_fg_val_08               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 8)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16220 RO 0x0000_0000
	UINT32 reg_hist_bg_val_09               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 9)
	UINT32 reg_hist_fg_val_09               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 9)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16224 RO 0x0000_0000
	UINT32 reg_hist_bg_val_10               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 10)
	UINT32 reg_hist_fg_val_10               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 10)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16228 RO 0x0000_0000
	UINT32 reg_hist_bg_val_11               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 11)
	UINT32 reg_hist_fg_val_11               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 11)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1622C RO 0x0000_0000
	UINT32 reg_hist_bg_val_12               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 12)
	UINT32 reg_hist_fg_val_12               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 12)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16230 RO 0x0000_0000
	UINT32 reg_hist_bg_val_13               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 13)
	UINT32 reg_hist_fg_val_13               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 13)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16234 RO 0x0000_0000
	UINT32 reg_hist_bg_val_14               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 14)
	UINT32 reg_hist_fg_val_14               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 14)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16238 RO 0x0000_0000
	UINT32 reg_hist_bg_val_15               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 15)
	UINT32 reg_hist_fg_val_15               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 15)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1623C RO 0x0000_0000
	UINT32 reg_hist_bg_val_16               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 16)
	UINT32 reg_hist_fg_val_16               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 16)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16240 RO 0x0000_0000
	UINT32 reg_hist_bg_val_17               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 17)
	UINT32 reg_hist_fg_val_17               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 17)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16244 RO 0x0000_0000
	UINT32 reg_hist_bg_val_18               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 18)
	UINT32 reg_hist_fg_val_18               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 18)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16248 RO 0x0000_0000
	UINT32 reg_hist_bg_val_19               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 19)
	UINT32 reg_hist_fg_val_19               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 19)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1624C RO 0x0000_0000
	UINT32 reg_hist_bg_val_20               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 20)
	UINT32 reg_hist_fg_val_20               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 20)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16250 RO 0x0000_0000
	UINT32 reg_hist_bg_val_21               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 21)
	UINT32 reg_hist_fg_val_21               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 21)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16254 RO 0x0000_0000
	UINT32 reg_hist_bg_val_22               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 22)
	UINT32 reg_hist_fg_val_22               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 22)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16258 RO 0x0000_0000
	UINT32 reg_hist_bg_val_23               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 23)
	UINT32 reg_hist_fg_val_23               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 23)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1625C RO 0x0000_0000
	UINT32 reg_hist_bg_val_24               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 24)
	UINT32 reg_hist_fg_val_24               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 24)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16260 RO 0x0000_0000
	UINT32 reg_hist_bg_val_25               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 25)
	UINT32 reg_hist_fg_val_25               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 25)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16264 RO 0x0000_0000
	UINT32 reg_hist_bg_val_26               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 26)
	UINT32 reg_hist_fg_val_26               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 26)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16268 RO 0x0000_0000
	UINT32 reg_hist_bg_val_27               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 27)
	UINT32 reg_hist_fg_val_27               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 27)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1626C RO 0x0000_0000
	UINT32 reg_hist_bg_val_28               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 28)
	UINT32 reg_hist_fg_val_28               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 28)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16270 RO 0x0000_0000
	UINT32 reg_hist_bg_val_29               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 29)
	UINT32 reg_hist_fg_val_29               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 29)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16274 RO 0x0000_0000
	UINT32 reg_hist_bg_val_30               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 30)
	UINT32 reg_hist_fg_val_30               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 30)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16278 RO 0x0000_0000
	UINT32 reg_hist_bg_val_31               :16;	//(15:0,NA,0) //Histogram read data (BG, VAL, bin 31)
	UINT32 reg_hist_fg_val_31               :16;	//(31:16,NA,0) //Histogram read data (FG, VAL, bin 31)
	};
}PE_O26_AMG3_GRM_HISTOGRAM_STAT_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16280 RW 0x0000_0110
	UINT32 reg_sv_map_mode                  :1;	//(0:0,NA,0) //SV map mode
	UINT32 resvd0                           :3;
	UINT32 reg_sv_map_shift                 :2;	//(5:4,NA,1) //SV map shift (0: shift6, 1: shift7, 2: shift8, 3: shift9)
	UINT32 resvd1                           :2;
	UINT32 reg_sv_post_shift                :2;	//(9:8,NA,1) //SV post map shift (0: shift6, 1: shift7, 2: shift8, 3: shift9)
	UINT32 resvd2                           :22;
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16284 RW 0x64AD_1400
	UINT32 reg_sat_lut_y0                   :8;	//(7:0,NA,0) //SAT LUT points, y0
	UINT32 reg_sat_lut_x0                   :8;	//(15:8,NA,20) //SAT LUT points, x0
	UINT32 reg_sat_lut_y1                   :8;	//(23:16,NA,173) //SAT LUT points, y1
	UINT32 reg_sat_lut_x1                   :8;	//(31:24,NA,100) //SAT LUT points, x1
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16288 RW 0xFFFF_C7FF
	UINT32 reg_sat_lut_y2                   :8;	//(7:0,NA,255) //SAT LUT points, y2
	UINT32 reg_sat_lut_x2                   :8;	//(15:8,NA,199) //SAT LUT points, x2
	UINT32 reg_sat_lut_y3                   :8;	//(23:16,NA,255) //SAT LUT points, y3
	UINT32 reg_sat_lut_x3                   :8;	//(31:24,NA,255) //SAT LUT points, x3
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1628C RW 0x1E00_0000
	UINT32 reg_val_lut_y0                   :8;	//(7:0,NA,0) //VAL LUT points, y0
	UINT32 reg_val_lut_x0                   :8;	//(15:8,NA,0) //VAL LUT points, x0
	UINT32 reg_val_lut_y1                   :8;	//(23:16,NA,0) //VAL LUT points, y1
	UINT32 reg_val_lut_x1                   :8;	//(31:24,NA,30) //VAL LUT points, x1
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16290 RW 0xFFFF_8080
	UINT32 reg_val_lut_y2                   :8;	//(7:0,NA,128) //VAL LUT points, y2
	UINT32 reg_val_lut_x2                   :8;	//(15:8,NA,128) //VAL LUT points, x2
	UINT32 reg_val_lut_y3                   :8;	//(23:16,NA,255) //VAL LUT points, y3
	UINT32 reg_val_lut_x3                   :8;	//(31:24,NA,255) //VAL LUT points, x3
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16294 RW 0x3CFF_00C8
	UINT32 reg_sv_map_lut_y0                :8;	//(7:0,NA,200) //SV map LUT points, y0
	UINT32 reg_sv_map_lut_x0                :8;	//(15:8,NA,0) //SV map LUT points, x0
	UINT32 reg_sv_map_lut_y1                :8;	//(23:16,NA,255) //SV map LUT points, y1
	UINT32 reg_sv_map_lut_x1                :8;	//(31:24,NA,60) //SV map LUT points, x1
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC16298 RW 0xFFFF_80A0
	UINT32 reg_sv_map_lut_y2                :8;	//(7:0,NA,160) //SV map LUT points, y2
	UINT32 reg_sv_map_lut_x2                :8;	//(15:8,NA,128) //SV map LUT points, x2
	UINT32 reg_sv_map_lut_y3                :8;	//(23:16,NA,255) //SV map LUT points, y3
	UINT32 reg_sv_map_lut_x3                :8;	//(31:24,NA,255) //SV map LUT points, x3
	};
}PE_O26_AMG3_GRM_SV_BLEND_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162A0 RW 0x0000_12C1
	UINT32 reg_max_hue_clip                 :1;	//(0:0,NA,1) //Manual max clip enable, HUE
	UINT32 resvd0                           :3;
	UINT32 reg_max_hue                      :16;	//(19:4,NA,300) //Manual max clip value, HUE
	UINT32 resvd1                           :12;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162A4 RW 0x0000_2BC1
	UINT32 reg_max_val_clip                 :1;	//(0:0,NA,1) //Manual max clip enable, VAL
	UINT32 resvd0                           :3;
	UINT32 reg_max_val                      :16;	//(19:4,NA,700) //Manual max clip value, VAL
	UINT32 resvd1                           :12;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162A8 RW 0x0000_0100
	UINT32 reg_norm_hue_factor              :9;	//(8:0,NA,256) //Normalization factor, HUE
	UINT32 resvd0                           :3;
	UINT32 reg_norm_hue_offset              :10;	//(21:12,NA,0) //Normalization offset, HUE
	UINT32 resvd1                           :10;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162AC RW 0x0000_1080
	UINT32 reg_norm_val_factor              :9;	//(8:0,NA,128) //Normalization factor, VAL
	UINT32 resvd0                           :3;
	UINT32 reg_norm_val_offset              :10;	//(21:12,NA,1) //Normalization offset, VAL
	UINT32 resvd1                           :10;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162B0 RW 0x0800_1001
	UINT32 reg_ratio_hue_fg_offset          :10;	//(9:0,NA,1) //Gain ratio offset, FG, HUE
	UINT32 resvd0                           :2;
	UINT32 reg_ratio_hue_bg_offset          :10;	//(21:12,NA,1) //Gain ratio offset, BG, HUE
	UINT32 resvd1                           :2;
	UINT32 reg_ratio_hue_shift              :4;	//(27:24,NA,8) //Gain ratio shift, HUE
	UINT32 resvd2                           :4;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162B4 RW 0x0706_4001
	UINT32 reg_ratio_val_fg_offset          :10;	//(9:0,NA,1) //Gain ratio offset, FG, VAL
	UINT32 resvd0                           :2;
	UINT32 reg_ratio_val_bg_offset          :10;	//(21:12,NA,100) //Gain ratio offset, BG, VAL
	UINT32 resvd1                           :2;
	UINT32 reg_ratio_val_shift              :4;	//(27:24,NA,7) //Gain ratio shift, VAL
	UINT32 resvd2                           :4;
	};
}PE_O26_AMG3_GRM_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162C0 RW 0x4060_0028
	UINT32 reg_grm_lut_y0                   :8;	//(7:0,NA,40) //Final GRM LUT points, y0
	UINT32 reg_grm_lut_x0                   :8;	//(15:8,NA,0) //Final GRM LUT points, x0
	UINT32 reg_grm_lut_y1                   :8;	//(23:16,NA,96) //Final GRM LUT points, y1
	UINT32 reg_grm_lut_x1                   :8;	//(31:24,NA,64) //Final GRM LUT points, x1
	};
}PE_O26_AMG3_GRM_GRM_BLEND_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162C4 RW 0xFFFF_80A0
	UINT32 reg_grm_lut_y2                   :8;	//(7:0,NA,160) //Final GRM LUT points, y2
	UINT32 reg_grm_lut_x2                   :8;	//(15:8,NA,128) //Final GRM LUT points, x2
	UINT32 reg_grm_lut_y3                   :8;	//(23:16,NA,255) //Final GRM LUT points, y3
	UINT32 reg_grm_lut_x3                   :8;	//(31:24,NA,255) //Final GRM LUT points, x3
	};
}PE_O26_AMG3_GRM_GRM_BLEND_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162D0 RW 0x2800_0000
	UINT32 reg_lut_db_grm_y0                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y0
	UINT32 reg_lut_db_grm_x0                :8;	//(15:8,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), x0
	UINT32 reg_lut_db_grm_y1                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y1
	UINT32 reg_lut_db_grm_x1                :8;	//(31:24,NA,40) //LUT (DB GRM blend) control point (for DepthBody>GRM), x1
	};
}PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162D4 RW 0xFF00_5000
	UINT32 reg_lut_db_grm_y2                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y2
	UINT32 reg_lut_db_grm_x2                :8;	//(15:8,NA,80) //LUT (DB GRM blend) control point (for DepthBody>GRM), x2
	UINT32 reg_lut_db_grm_y3                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody>GRM), y3
	UINT32 reg_lut_db_grm_x3                :8;	//(31:24,NA,255) //LUT (DB GRM blend) control point (for DepthBody>GRM), x3
	};
}PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162D8 RW 0x2800_0000
	UINT32 reg_lut_grm_db_y0                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y0
	UINT32 reg_lut_grm_db_x0                :8;	//(15:8,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x0
	UINT32 reg_lut_grm_db_y1                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y1
	UINT32 reg_lut_grm_db_x1                :8;	//(31:24,NA,40) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x1
	};
}PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162DC RW 0xFF00_5000
	UINT32 reg_lut_grm_db_y2                :8;	//(7:0,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y2
	UINT32 reg_lut_grm_db_x2                :8;	//(15:8,NA,80) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x2
	UINT32 reg_lut_grm_db_y3                :8;	//(23:16,NA,0) //LUT (DB GRM blend) control point (for DepthBody<=GRM), y3
	UINT32 reg_lut_grm_db_x3                :8;	//(31:24,NA,255) //LUT (DB GRM blend) control point (for DepthBody<=GRM), x3
	};
}PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162E0 RW 0x2800_0000
	UINT32 reg_lut_dbg_mtb_y0               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y0
	UINT32 reg_lut_dbg_mtb_x0               :8;	//(15:8,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x0
	UINT32 reg_lut_dbg_mtb_y1               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y1
	UINT32 reg_lut_dbg_mtb_x1               :8;	//(31:24,NA,40) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x1
	};
}PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162E4 RW 0xFF00_5000
	UINT32 reg_lut_dbg_mtb_y2               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y2
	UINT32 reg_lut_dbg_mtb_x2               :8;	//(15:8,NA,80) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x2
	UINT32 reg_lut_dbg_mtb_y3               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), y3
	UINT32 reg_lut_dbg_mtb_x3               :8;	//(31:24,NA,255) //LUT (DG MTB blend) control point (for DepthBodyGRM>MTB), x3
	};
}PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162E8 RW 0x2800_0000
	UINT32 reg_lut_mtb_dbg_y0               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y0
	UINT32 reg_lut_mtb_dbg_x0               :8;	//(15:8,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x0
	UINT32 reg_lut_mtb_dbg_y1               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y1
	UINT32 reg_lut_mtb_dbg_x1               :8;	//(31:24,NA,40) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x1
	};
}PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162EC RW 0xFF00_5000
	UINT32 reg_lut_mtb_dbg_y2               :8;	//(7:0,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y2
	UINT32 reg_lut_mtb_dbg_x2               :8;	//(15:8,NA,80) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x2
	UINT32 reg_lut_mtb_dbg_y3               :8;	//(23:16,NA,0) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), y3
	UINT32 reg_lut_mtb_dbg_x3               :8;	//(31:24,NA,255) //LUT (DG MTB blend) control point (for DepthBodyGRM<=MTB), x3
	};
}PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC162F0 RW 0x0000_0000
	UINT32 reg_dbg_grm_mode                 :4;	//(3:0,NA,0) //Debug mode	0 : Normal GRM output	1 : HUE	2 : SAT	3 : VAL	4 : SV blend map (pre)	5 : SV blend map (post)	6 : Final gain, HUE	7 : Final gain, VAL	8 : GRM result
	UINT32 resvd0                           :4;
	UINT32 reg_dbg_grm_rgn                  :2;	//(9:8,NA,0) //Debug mode region selction (for debug mode 6~8)	0 : LU	1 : RU	2 : LD	3 : RD
	UINT32 resvd1                           :22;
	};
}PE_O26_AMG3_GRM_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC163F0 RO 0x0000_0000
	UINT32 reg_mon_in_pel_y_sucfail         :16;	//(15:0,NA,0) //Core input (pel, Y) success/fail monitoring register
	UINT32 reg_mon_in_pel_y_fin_vert        :9;	//(24:16,NA,0) //Core input (pel, Y) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG3_GRM_GRM_CORE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC163F4 RO 0x0000_0000
	UINT32 reg_mon_in_pel_c_sucfail         :16;	//(15:0,NA,0) //Core input (pel, C) success/fail monitoring register
	UINT32 reg_mon_in_pel_c_fin_vert        :9;	//(24:16,NA,0) //Core input (pel, C) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG3_GRM_GRM_CORE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC163F8 RO 0x0000_0000
	UINT32 reg_mon_in_depth_sucfail         :16;	//(15:0,NA,0) //Core input (depth map) success/fail monitoring register
	UINT32 reg_mon_in_depth_fin_vert        :9;	//(24:16,NA,0) //Core input (depth map) previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG3_GRM_GRM_CORE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC163FC RO 0x0000_0000
	UINT32 reg_mon_out_sucfail              :16;	//(15:0,NA,0) //Core output success/fail monitoring register
	UINT32 reg_mon_out_fin_vert             :9;	//(24:16,NA,0) //Core output previous frame vertical counter
	UINT32 resvd                            :7;
	};
}PE_O26_AMG3_GRM_GRM_CORE_STAT_03_T;

typedef struct {
	PE_O26_AMG3_GRM_BLUR_CTRL_00_T                            blur_ctrl_00;	//0xCCC16100
	PE_O26_AMG3_GRM_BLUR_CTRL_01_T                            blur_ctrl_01;	//0xCCC16104
	PE_O26_AMG3_GRM_BLUR_CTRL_02_T                            blur_ctrl_02;	//0xCCC16108
	UINT32                                                       reserved0;	//0xCCC1610C
	PE_O26_AMG3_GRM_YC2HSV_CTRL_00_T                        yc2hsv_ctrl_00;	//0xCCC16110
	PE_O26_AMG3_GRM_YC2HSV_CTRL_01_T                        yc2hsv_ctrl_01;	//0xCCC16114
	PE_O26_AMG3_GRM_YC2HSV_CTRL_02_T                        yc2hsv_ctrl_02;	//0xCCC16118
	PE_O26_AMG3_GRM_YC2HSV_CTRL_03_T                        yc2hsv_ctrl_03;	//0xCCC1611C
	PE_O26_AMG3_GRM_YC2HSV_CTRL_04_T                        yc2hsv_ctrl_04;	//0xCCC16120
	PE_O26_AMG3_GRM_YC2HSV_CTRL_05_T                        yc2hsv_ctrl_05;	//0xCCC16124
	PE_O26_AMG3_GRM_YC2HSV_CTRL_06_T                        yc2hsv_ctrl_06;	//0xCCC16128
	PE_O26_AMG3_GRM_YC2HSV_CTRL_07_T                        yc2hsv_ctrl_07;	//0xCCC1612C
	PE_O26_AMG3_GRM_YC2HSV_CTRL_08_T                        yc2hsv_ctrl_08;	//0xCCC16130
	PE_O26_AMG3_GRM_YC2HSV_CTRL_09_T                        yc2hsv_ctrl_09;	//0xCCC16134
	PE_O26_AMG3_GRM_DEPTH_CTRL_00_T                          depth_ctrl_00;	//0xCCC16138
	PE_O26_AMG3_GRM_DEPTH_CTRL_01_T                          depth_ctrl_01;	//0xCCC1613C
	PE_O26_AMG3_GRM_REGION_POS_CTRL_00_T                region_pos_ctrl_00;	//0xCCC16140
	PE_O26_AMG3_GRM_REGION_POS_CTRL_01_T                region_pos_ctrl_01;	//0xCCC16144
	PE_O26_AMG3_GRM_REGION_POS_CTRL_02_T                region_pos_ctrl_02;	//0xCCC16148
	PE_O26_AMG3_GRM_REGION_POS_CTRL_03_T                region_pos_ctrl_03;	//0xCCC1614C
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_00_T                  histogram_ctrl_00;	//0xCCC16150
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_01_T                  histogram_ctrl_01;	//0xCCC16154
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_02_T                  histogram_ctrl_02;	//0xCCC16158
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_03_T                  histogram_ctrl_03;	//0xCCC1615C
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_04_T                  histogram_ctrl_04;	//0xCCC16160
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_05_T                  histogram_ctrl_05;	//0xCCC16164
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_06_T                  histogram_ctrl_06;	//0xCCC16168
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_07_T                  histogram_ctrl_07;	//0xCCC1616C
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_08_T                  histogram_ctrl_08;	//0xCCC16170
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_09_T                  histogram_ctrl_09;	//0xCCC16174
	PE_O26_AMG3_GRM_HISTOGRAM_CTRL_10_T                  histogram_ctrl_10;	//0xCCC16178
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_00_T                  histogram_stat_00;	//0xCCC1617C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_01_T                  histogram_stat_01;	//0xCCC16180
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_02_T                  histogram_stat_02;	//0xCCC16184
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_03_T                  histogram_stat_03;	//0xCCC16188
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_04_T                  histogram_stat_04;	//0xCCC1618C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_05_T                  histogram_stat_05;	//0xCCC16190
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_06_T                  histogram_stat_06;	//0xCCC16194
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_07_T                  histogram_stat_07;	//0xCCC16198
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_08_T                  histogram_stat_08;	//0xCCC1619C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_09_T                  histogram_stat_09;	//0xCCC161A0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_10_T                  histogram_stat_10;	//0xCCC161A4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_11_T                  histogram_stat_11;	//0xCCC161A8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_12_T                  histogram_stat_12;	//0xCCC161AC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_13_T                  histogram_stat_13;	//0xCCC161B0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_14_T                  histogram_stat_14;	//0xCCC161B4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_15_T                  histogram_stat_15;	//0xCCC161B8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_16_T                  histogram_stat_16;	//0xCCC161BC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_17_T                  histogram_stat_17;	//0xCCC161C0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_18_T                  histogram_stat_18;	//0xCCC161C4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_19_T                  histogram_stat_19;	//0xCCC161C8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_20_T                  histogram_stat_20;	//0xCCC161CC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_21_T                  histogram_stat_21;	//0xCCC161D0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_22_T                  histogram_stat_22;	//0xCCC161D4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_23_T                  histogram_stat_23;	//0xCCC161D8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_24_T                  histogram_stat_24;	//0xCCC161DC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_25_T                  histogram_stat_25;	//0xCCC161E0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_26_T                  histogram_stat_26;	//0xCCC161E4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_27_T                  histogram_stat_27;	//0xCCC161E8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_28_T                  histogram_stat_28;	//0xCCC161EC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_29_T                  histogram_stat_29;	//0xCCC161F0
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_30_T                  histogram_stat_30;	//0xCCC161F4
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_31_T                  histogram_stat_31;	//0xCCC161F8
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_32_T                  histogram_stat_32;	//0xCCC161FC
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_33_T                  histogram_stat_33;	//0xCCC16200
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_34_T                  histogram_stat_34;	//0xCCC16204
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_35_T                  histogram_stat_35;	//0xCCC16208
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_36_T                  histogram_stat_36;	//0xCCC1620C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_37_T                  histogram_stat_37;	//0xCCC16210
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_38_T                  histogram_stat_38;	//0xCCC16214
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_39_T                  histogram_stat_39;	//0xCCC16218
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_40_T                  histogram_stat_40;	//0xCCC1621C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_41_T                  histogram_stat_41;	//0xCCC16220
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_42_T                  histogram_stat_42;	//0xCCC16224
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_43_T                  histogram_stat_43;	//0xCCC16228
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_44_T                  histogram_stat_44;	//0xCCC1622C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_45_T                  histogram_stat_45;	//0xCCC16230
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_46_T                  histogram_stat_46;	//0xCCC16234
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_47_T                  histogram_stat_47;	//0xCCC16238
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_48_T                  histogram_stat_48;	//0xCCC1623C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_49_T                  histogram_stat_49;	//0xCCC16240
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_50_T                  histogram_stat_50;	//0xCCC16244
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_51_T                  histogram_stat_51;	//0xCCC16248
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_52_T                  histogram_stat_52;	//0xCCC1624C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_53_T                  histogram_stat_53;	//0xCCC16250
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_54_T                  histogram_stat_54;	//0xCCC16254
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_55_T                  histogram_stat_55;	//0xCCC16258
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_56_T                  histogram_stat_56;	//0xCCC1625C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_57_T                  histogram_stat_57;	//0xCCC16260
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_58_T                  histogram_stat_58;	//0xCCC16264
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_59_T                  histogram_stat_59;	//0xCCC16268
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_60_T                  histogram_stat_60;	//0xCCC1626C
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_61_T                  histogram_stat_61;	//0xCCC16270
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_62_T                  histogram_stat_62;	//0xCCC16274
	PE_O26_AMG3_GRM_HISTOGRAM_STAT_63_T                  histogram_stat_63;	//0xCCC16278
	UINT32                                                       reserved1;	//0xCCC1627C
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_00_T                    sv_blend_ctrl_00;	//0xCCC16280
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_01_T                    sv_blend_ctrl_01;	//0xCCC16284
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_02_T                    sv_blend_ctrl_02;	//0xCCC16288
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_03_T                    sv_blend_ctrl_03;	//0xCCC1628C
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_04_T                    sv_blend_ctrl_04;	//0xCCC16290
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_05_T                    sv_blend_ctrl_05;	//0xCCC16294
	PE_O26_AMG3_GRM_SV_BLEND_CTRL_06_T                    sv_blend_ctrl_06;	//0xCCC16298
	UINT32                                                       reserved2;	//0xCCC1629C
	PE_O26_AMG3_GRM_GAIN_CTRL_00_T                            gain_ctrl_00;	//0xCCC162A0
	PE_O26_AMG3_GRM_GAIN_CTRL_01_T                            gain_ctrl_01;	//0xCCC162A4
	PE_O26_AMG3_GRM_GAIN_CTRL_02_T                            gain_ctrl_02;	//0xCCC162A8
	PE_O26_AMG3_GRM_GAIN_CTRL_03_T                            gain_ctrl_03;	//0xCCC162AC
	PE_O26_AMG3_GRM_GAIN_CTRL_04_T                            gain_ctrl_04;	//0xCCC162B0
	PE_O26_AMG3_GRM_GAIN_CTRL_05_T                            gain_ctrl_05;	//0xCCC162B4
	UINT32                                                       reserved3;	//0xCCC162B8
	UINT32                                                       reserved4;	//0xCCC162BC
	PE_O26_AMG3_GRM_GRM_BLEND_CTRL_00_T                  grm_blend_ctrl_00;	//0xCCC162C0
	PE_O26_AMG3_GRM_GRM_BLEND_CTRL_01_T                  grm_blend_ctrl_01;	//0xCCC162C4
	UINT32                                                       reserved5;	//0xCCC162C8
	UINT32                                                       reserved6;	//0xCCC162CC
	PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_00_T                lut_dg_bld_ctrl_00;	//0xCCC162D0
	PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_01_T                lut_dg_bld_ctrl_01;	//0xCCC162D4
	PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_02_T                lut_dg_bld_ctrl_02;	//0xCCC162D8
	PE_O26_AMG3_GRM_LUT_DG_BLD_CTRL_03_T                lut_dg_bld_ctrl_03;	//0xCCC162DC
	PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_00_T                lut_gm_bld_ctrl_00;	//0xCCC162E0
	PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_01_T                lut_gm_bld_ctrl_01;	//0xCCC162E4
	PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_02_T                lut_gm_bld_ctrl_02;	//0xCCC162E8
	PE_O26_AMG3_GRM_LUT_GM_BLD_CTRL_03_T                lut_gm_bld_ctrl_03;	//0xCCC162EC
	PE_O26_AMG3_GRM_DEBUG_CTRL_00_T                          debug_ctrl_00;	//0xCCC162F0
	UINT32                                                       reserved7;	//0xCCC162F4
	UINT32                                                       reserved8;	//0xCCC162F8
	UINT32                                                       reserved9;	//0xCCC162FC
	UINT32                                                      reserved10;	//0xCCC16300
	UINT32                                                      reserved11;	//0xCCC16304
	UINT32                                                      reserved12;	//0xCCC16308
	UINT32                                                      reserved13;	//0xCCC1630C
	UINT32                                                      reserved14;	//0xCCC16310
	UINT32                                                      reserved15;	//0xCCC16314
	UINT32                                                      reserved16;	//0xCCC16318
	UINT32                                                      reserved17;	//0xCCC1631C
	UINT32                                                      reserved18;	//0xCCC16320
	UINT32                                                      reserved19;	//0xCCC16324
	UINT32                                                      reserved20;	//0xCCC16328
	UINT32                                                      reserved21;	//0xCCC1632C
	UINT32                                                      reserved22;	//0xCCC16330
	UINT32                                                      reserved23;	//0xCCC16334
	UINT32                                                      reserved24;	//0xCCC16338
	UINT32                                                      reserved25;	//0xCCC1633C
	UINT32                                                      reserved26;	//0xCCC16340
	UINT32                                                      reserved27;	//0xCCC16344
	UINT32                                                      reserved28;	//0xCCC16348
	UINT32                                                      reserved29;	//0xCCC1634C
	UINT32                                                      reserved30;	//0xCCC16350
	UINT32                                                      reserved31;	//0xCCC16354
	UINT32                                                      reserved32;	//0xCCC16358
	UINT32                                                      reserved33;	//0xCCC1635C
	UINT32                                                      reserved34;	//0xCCC16360
	UINT32                                                      reserved35;	//0xCCC16364
	UINT32                                                      reserved36;	//0xCCC16368
	UINT32                                                      reserved37;	//0xCCC1636C
	UINT32                                                      reserved38;	//0xCCC16370
	UINT32                                                      reserved39;	//0xCCC16374
	UINT32                                                      reserved40;	//0xCCC16378
	UINT32                                                      reserved41;	//0xCCC1637C
	UINT32                                                      reserved42;	//0xCCC16380
	UINT32                                                      reserved43;	//0xCCC16384
	UINT32                                                      reserved44;	//0xCCC16388
	UINT32                                                      reserved45;	//0xCCC1638C
	UINT32                                                      reserved46;	//0xCCC16390
	UINT32                                                      reserved47;	//0xCCC16394
	UINT32                                                      reserved48;	//0xCCC16398
	UINT32                                                      reserved49;	//0xCCC1639C
	UINT32                                                      reserved50;	//0xCCC163A0
	UINT32                                                      reserved51;	//0xCCC163A4
	UINT32                                                      reserved52;	//0xCCC163A8
	UINT32                                                      reserved53;	//0xCCC163AC
	UINT32                                                      reserved54;	//0xCCC163B0
	UINT32                                                      reserved55;	//0xCCC163B4
	UINT32                                                      reserved56;	//0xCCC163B8
	UINT32                                                      reserved57;	//0xCCC163BC
	UINT32                                                      reserved58;	//0xCCC163C0
	UINT32                                                      reserved59;	//0xCCC163C4
	UINT32                                                      reserved60;	//0xCCC163C8
	UINT32                                                      reserved61;	//0xCCC163CC
	UINT32                                                      reserved62;	//0xCCC163D0
	UINT32                                                      reserved63;	//0xCCC163D4
	UINT32                                                      reserved64;	//0xCCC163D8
	UINT32                                                      reserved65;	//0xCCC163DC
	UINT32                                                      reserved66;	//0xCCC163E0
	UINT32                                                      reserved67;	//0xCCC163E4
	UINT32                                                      reserved68;	//0xCCC163E8
	UINT32                                                      reserved69;	//0xCCC163EC
	PE_O26_AMG3_GRM_GRM_CORE_STAT_00_T                    grm_core_stat_00;	//0xCCC163F0
	PE_O26_AMG3_GRM_GRM_CORE_STAT_01_T                    grm_core_stat_01;	//0xCCC163F4
	PE_O26_AMG3_GRM_GRM_CORE_STAT_02_T                    grm_core_stat_02;	//0xCCC163F8
	PE_O26_AMG3_GRM_GRM_CORE_STAT_03_T                    grm_core_stat_03;	//0xCCC163FC
}PE_AMG_GRM_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D00 RW 0x0000_0100
	UINT32 reg_drc_en                       :1;	//(0:0,NA,0x0) //drc enable; '0' : disable; '1' : enable
	UINT32 reg_drc_cg_disable               :1;	//(1:1,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_drc_txt_gain_en              :1;	//(4:4,NA,0x0) //texture,apl gaining en
	UINT32 resvd1                           :3;
	UINT32 reg_drc_rgb_sel                  :2;	//(9:8,NA,0x1) //"00" : luminance; "01" : MAX(r,g,b); others : AVG(r,g,b)
	UINT32 resvd2                           :2;
	UINT32 reg_drc_gm_mode                  :3;	//(14:12,NA,0x0) //gamma lut enable; "01" : enable; others : disable
	UINT32 resvd3                           :1;
	UINT32 reg_drc_lk_blf_apf               :1;	//(16:16,NA,0x0) //use bypass spatial filter coefficient for debugging; '0' : disable ; '1' : enable
	UINT32 resvd4                           :3;
	UINT32 reg_dbg_disp_apl_gain            :1;	//(20:20,NA,0x0) //display apl gain for debuging; '0' : disable; '1' : enable
	UINT32 resvd5                           :3;
	UINT32 reg_dbg_apl_gain_sel             :2;	//(25:24,NA,0x0) //0:selected 1:dark 2:bright
	UINT32 resvd6                           :2;
	UINT32 reg_dbg_disp_blf                 :1;	//(28:28,NA,0x0) //display blf image for debuging; '0' : disable; '1' : enable
	UINT32 reg_dbg_disp_lcont               :1;	//(29:29,NA,0x0) //display local contrast image for debugging; '0' : disable; '1' : enable
	UINT32 reg_dbg_disp_texture             :1;	//(30:30,NA,0x0) //texture gain image for debugging (must set reg_dbg_disp_blf to 1); '0' : disable; '1' : enable
	UINT32 resvd7                           :1;
	};
}PE_O26_LOC_PE1_DRC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D04 RW 0x0000_0001
	UINT32 reg_drc_gm_rw_sel                :1;	//(0:0,NA,0x1) //selecet a,b gamma lut for register r/w; '0' : a gamma lut ; '1' : b gamma lut
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4:4,NA,0x0) //selecet a,b gamma lut for operation; '0' : b gamma lut ; '1' : a gamma lut
	UINT32 resvd1                           :11;
	UINT32 reg_drc_gm_forced_sel            :1;	//(16:16,NA,0x0) //anytime rw_sel, op_sel transition
	UINT32 reg_drc_gm_protected_sel         :1;	//(17:17,NA,0x0) //Do not allow rw_sel, op_sel transition only in de active
	UINT32 resvd2                           :14;
	};
}PE_O26_LOC_PE1_DRC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D08 RW 0x0036_0060
	UINT32 reg_drc_bnh                      :7;	//(6:0,NA,0x60) //horizontal block size (min : 4, max : 96)
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bnv                      :6;	//(21:16,NA,0x36) //vertical block size (min : 3, max : 54)
	UINT32 resvd1                           :10;
	};
}PE_O26_LOC_PE1_DRC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D0C RW 0x0050_0050
	UINT32 reg_drc_bsh                      :9;	//(8:0,NA,0x50) //
	UINT32 resvd0                           :7;
	UINT32 reg_drc_bsv                      :9;	//(24:16,NA,0x50) //
	UINT32 resvd1                           :7;
	};
}PE_O26_LOC_PE1_DRC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D10 RW 0x0321_912C
	UINT32 reg_drc_gm_apl2                  :10;	//(9:0,NA,0x12C) //apl for gamma lut 2
	UINT32 reg_drc_gm_apl1                  :10;	//(19:10,NA,0x64) //apl for gamma lut 1
	UINT32 reg_drc_gm_apl0                  :10;	//(29:20,NA,0x32) //apl for gamma lut 0
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D14 RW 0x1F4A_F3B6
	UINT32 reg_drc_gm_apl5                  :10;	//(9:0,NA,0x3B6) //apl for gamma lut 5
	UINT32 reg_drc_gm_apl4                  :10;	//(19:10,NA,0x2BC) //apl for gamma lut 4
	UINT32 reg_drc_gm_apl3                  :10;	//(29:20,NA,0x1F4) //apl for gamma lut 3
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D18 RW 0x0000_0030
	UINT32 reg_drc_blf_wei_cen              :8;	//(7:0,NA,0x30) //center pixel weight for blf
	UINT32 resvd                            :24;
	};
}PE_O26_LOC_PE1_DRC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D1C RW 0x00000000
	UINT32 reg_drc_apl_lut_x1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x0               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D20 RW 0x00000000
	UINT32 reg_drc_apl_lut_x3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x2               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D24 RW 0x00000000
	UINT32 reg_drc_apl_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_apl_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_apl_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_apl_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D28 RW 0x00000000
	UINT32 reserved                         :32;	//(31:0,NA,0x00000000) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D2C RW 0x00000000
	UINT32 reserved                         :32;	//(31:0,NA,0x00000000) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D30 RW 0x00000000
	UINT32 reg_drc_dark_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D34 RW 0x00000000
	UINT32 reg_drc_dark_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D38 RW 0x00000000
	UINT32 reg_drc_bright_lut_x3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_x2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_x1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_x0            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D3C RW 0x00000000
	UINT32 reg_drc_bright_lut_y3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_y2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_y1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_y0            :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D40 RW 0x0000_0000
	UINT32 reg_drc_lut_addr_clr             :1;	//(0:0,NA,0x0) //lut address clear
	UINT32 resvd0                           :3;
	UINT32 reg_drc_hfc_rd_sel               :1;	//(4:4,NA,0x0) //blf h filter coefficient read select
	UINT32 resvd1                           :3;
	UINT32 reg_drc_vfc_rd_sel               :1;	//(8:8,NA,0x0) //blf v filter coefficient read select
	UINT32 resvd2                           :23;
	};
}PE_O26_LOC_PE1_DRC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D44 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_hfc_data          :10;	//(9:0,NA,0x0) //blf h filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D48 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_vfc_data          :10;	//(9:0,NA,0x0) //blf v filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D4C RW 0x0000_0000
	UINT32 reg_drc_hfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_hfc_rdata: blf h filter coefficient read data; WR [0]reg_drc_hfc_re : blf h filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D50 RW 0x0000_0000
	UINT32 reg_drc_vfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_vfc_rdata : blf v filter coefficient read data; WR [0]reg_drc_vfc_re : blf v filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D54 WO 0x0000_0000
	UINT32 reg_drc_blf_wei_wdata            :10;	//(9:0,NA,0x0) //blf photometric weight write data
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D58 RW 0x0000_0000
	UINT32 reg_drc_blf_wei_rdata            :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_blf_wei_rdata : blf photometric weight read data; WR [0]reg_drc_blf_wei_re : blf photometric weight read enable
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D5C WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data; [29:20] -> gamma lut 0; [19:10] -> gamma lut 1; [ 9: 0] -> gamma lut 2
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D60 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 0,[19:10] -> gamma lut 1,[ 9: 0] -> gamma lut 2; WR [1:0]reg_drc_gm_re : gamma lut 0, 1, 2 read enable ("01")
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D64 WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data; [29:20] -> gamma lut 3; [19:10] -> gamma lut 4; [ 9: 0] -> gamma lut 5
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D68 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 3,[19:10] -> gamma lut 4,[ 9: 0] -> gamma lut 5; WR [1:0]reg_drc_gm_re : gamma lut 3, 4, 5 read enable ("10")
	UINT32 resvd                            :2;
	};
}PE_O26_LOC_PE1_DRC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D6C RW 0x0000_0000
	UINT32 reg_drc_bl_apl_raddr_h           :7;	//(6:0,NA,0x0) //block apl read H address
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bl_apl_raddr_v           :6;	//(21:16,NA,0x0) //block apl read V address
	UINT32 resvd1                           :10;
	};
}PE_O26_LOC_PE1_DRC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D70 RO 0x0000_0000
	UINT32 reg_drc_bl_apl_rdata             :10;	//(9:0,NA,0x0) //block apl read data
	UINT32 resvd                            :22;
	};
}PE_O26_LOC_PE1_DRC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D74 RO 0x0000_0000
	UINT32 reg_drc_gm_rw_sel                :1;	//(0:0,NA,0x0) //Read rw_sel
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4:4,NA,0x0) //Read op_sel
	UINT32 resvd1                           :27;
	};
}PE_O26_LOC_PE1_DRC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D80 RW 0x0000_0000
	UINT32 reg_y_ma_sel                     :1;	//(0:0,NA,0x0) //0:max 1:max-avg
	UINT32 resvd0                           :3;
	UINT32 reg_t_ma_sel                     :1;	//(4:4,NA,0x0) //0:max 1:max-avg
	UINT32 resvd1                           :27;
	};
}PE_O26_LOC_PE1_DRC_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D84 RW 0x0000_0000
	UINT32 reg_bapp_y_lut_x2                :10;	//(9:0,NA,0x0) //luma lut
	UINT32 resvd0                           :6;
	UINT32 reg_bapp_y_lut_x3                :10;	//(25:16,NA,0x0) //luma lut
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D88 RW 0x0000_0000
	UINT32 reg_bapp_y_lut_x0                :10;	//(9:0,NA,0x0) //luma lut
	UINT32 resvd0                           :6;
	UINT32 reg_bapp_y_lut_x1                :10;	//(25:16,NA,0x0) //luma lut
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D8C RW 0x0000_0000
	UINT32 reg_bapp_y_lut_y2                :10;	//(9:0,NA,0x0) //luma lut
	UINT32 resvd0                           :6;
	UINT32 reg_bapp_y_lut_y3                :10;	//(25:16,NA,0x0) //luma lut
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D90 RW 0x0000_0000
	UINT32 reg_bapp_y_lut_y0                :10;	//(9:0,NA,0x0) //luma lut
	UINT32 resvd0                           :6;
	UINT32 reg_bapp_y_lut_y1                :10;	//(25:16,NA,0x0) //luma lut
	UINT32 resvd1                           :6;
	};
}PE_O26_LOC_PE1_DRC_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D94 RW 0x0000_0000
	UINT32 reg_bapp_t_lut_x0                :8;	//(7:0,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_x1                :8;	//(15:8,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_x2                :8;	//(23:16,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_x3                :8;	//(31:24,NA,0x0) //texture lut
	};
}PE_O26_LOC_PE1_DRC_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D98 RW 0x0000_0000
	UINT32 reg_bapp_t_lut_y0                :8;	//(7:0,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_y1                :8;	//(15:8,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_y2                :8;	//(23:16,NA,0x0) //texture lut
	UINT32 reg_bapp_t_lut_y3                :8;	//(31:24,NA,0x0) //texture lut
	};
}PE_O26_LOC_PE1_DRC_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950D9C RW 0x00204060
	UINT32 reg_ba_txt_lut_x3                :8;	//(7:0,NA,0x60) //
	UINT32 reg_ba_txt_lut_x2                :8;	//(15:8,NA,0x40) //
	UINT32 reg_ba_txt_lut_x1                :8;	//(23:16,NA,0x20) //
	UINT32 reg_ba_txt_lut_x0                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DA0 RW 0x80A0C0FF
	UINT32 reg_ba_txt_lut_x7                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_ba_txt_lut_x6                :8;	//(15:8,NA,0xC0) //
	UINT32 reg_ba_txt_lut_x5                :8;	//(23:16,NA,0xA0) //
	UINT32 reg_ba_txt_lut_x4                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DA4 RW 0x00204060
	UINT32 reg_ba_txt_lut_y3                :8;	//(7:0,NA,0x60) //
	UINT32 reg_ba_txt_lut_y2                :8;	//(15:8,NA,0x40) //
	UINT32 reg_ba_txt_lut_y1                :8;	//(23:16,NA,0x20) //
	UINT32 reg_ba_txt_lut_y0                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DA8 RW 0x80A0C0FF
	UINT32 reg_ba_txt_lut_y7                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_ba_txt_lut_y6                :8;	//(15:8,NA,0xC0) //
	UINT32 reg_ba_txt_lut_y5                :8;	//(23:16,NA,0xA0) //
	UINT32 reg_ba_txt_lut_y4                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DAC RW 0x00204060
	UINT32 reg_drc_txt_lut_x3               :8;	//(7:0,NA,0x60) //
	UINT32 reg_drc_txt_lut_x2               :8;	//(15:8,NA,0x40) //
	UINT32 reg_drc_txt_lut_x1               :8;	//(23:16,NA,0x20) //
	UINT32 reg_drc_txt_lut_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DB0 RW 0x80A0C0FF
	UINT32 reg_drc_txt_lut_x7               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_drc_txt_lut_x6               :8;	//(15:8,NA,0xC0) //
	UINT32 reg_drc_txt_lut_x5               :8;	//(23:16,NA,0xA0) //
	UINT32 reg_drc_txt_lut_x4               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DB4 RW 0x00204060
	UINT32 reg_drc_txt_lut_y3               :8;	//(7:0,NA,0x60) //
	UINT32 reg_drc_txt_lut_y2               :8;	//(15:8,NA,0x40) //
	UINT32 reg_drc_txt_lut_y1               :8;	//(23:16,NA,0x20) //
	UINT32 reg_drc_txt_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC950DB8 RW 0x80A0C0FF
	UINT32 reg_drc_txt_lut_y7               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_drc_txt_lut_y6               :8;	//(15:8,NA,0xC0) //
	UINT32 reg_drc_txt_lut_y5               :8;	//(23:16,NA,0xA0) //
	UINT32 reg_drc_txt_lut_y4               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_LOC_PE1_DRC_CTRL_46_T;

typedef struct {
	PE_O26_LOC_PE1_DRC_CTRL_00_T                           pe1_drc_ctrl_00;	//0xCC950D00
	PE_O26_LOC_PE1_DRC_CTRL_01_T                           pe1_drc_ctrl_01;	//0xCC950D04
	PE_O26_LOC_PE1_DRC_CTRL_02_T                           pe1_drc_ctrl_02;	//0xCC950D08
	PE_O26_LOC_PE1_DRC_CTRL_03_T                           pe1_drc_ctrl_03;	//0xCC950D0C
	PE_O26_LOC_PE1_DRC_CTRL_04_T                           pe1_drc_ctrl_04;	//0xCC950D10
	PE_O26_LOC_PE1_DRC_CTRL_05_T                           pe1_drc_ctrl_05;	//0xCC950D14
	PE_O26_LOC_PE1_DRC_CTRL_06_T                           pe1_drc_ctrl_06;	//0xCC950D18
	PE_O26_LOC_PE1_DRC_CTRL_07_T                           pe1_drc_ctrl_07;	//0xCC950D1C
	PE_O26_LOC_PE1_DRC_CTRL_08_T                           pe1_drc_ctrl_08;	//0xCC950D20
	PE_O26_LOC_PE1_DRC_CTRL_09_T                           pe1_drc_ctrl_09;	//0xCC950D24
	PE_O26_LOC_PE1_DRC_CTRL_10_T                           pe1_drc_ctrl_10;	//0xCC950D28
	PE_O26_LOC_PE1_DRC_CTRL_11_T                           pe1_drc_ctrl_11;	//0xCC950D2C
	PE_O26_LOC_PE1_DRC_CTRL_12_T                           pe1_drc_ctrl_12;	//0xCC950D30
	PE_O26_LOC_PE1_DRC_CTRL_13_T                           pe1_drc_ctrl_13;	//0xCC950D34
	PE_O26_LOC_PE1_DRC_CTRL_14_T                           pe1_drc_ctrl_14;	//0xCC950D38
	PE_O26_LOC_PE1_DRC_CTRL_15_T                           pe1_drc_ctrl_15;	//0xCC950D3C
	PE_O26_LOC_PE1_DRC_CTRL_16_T                           pe1_drc_ctrl_16;	//0xCC950D40
	PE_O26_LOC_PE1_DRC_CTRL_17_T                           pe1_drc_ctrl_17;	//0xCC950D44
	PE_O26_LOC_PE1_DRC_CTRL_18_T                           pe1_drc_ctrl_18;	//0xCC950D48
	PE_O26_LOC_PE1_DRC_CTRL_19_T                           pe1_drc_ctrl_19;	//0xCC950D4C
	PE_O26_LOC_PE1_DRC_CTRL_20_T                           pe1_drc_ctrl_20;	//0xCC950D50
	PE_O26_LOC_PE1_DRC_CTRL_21_T                           pe1_drc_ctrl_21;	//0xCC950D54
	PE_O26_LOC_PE1_DRC_CTRL_22_T                           pe1_drc_ctrl_22;	//0xCC950D58
	PE_O26_LOC_PE1_DRC_CTRL_23_T                           pe1_drc_ctrl_23;	//0xCC950D5C
	PE_O26_LOC_PE1_DRC_CTRL_24_T                           pe1_drc_ctrl_24;	//0xCC950D60
	PE_O26_LOC_PE1_DRC_CTRL_25_T                           pe1_drc_ctrl_25;	//0xCC950D64
	PE_O26_LOC_PE1_DRC_CTRL_26_T                           pe1_drc_ctrl_26;	//0xCC950D68
	PE_O26_LOC_PE1_DRC_CTRL_27_T                           pe1_drc_ctrl_27;	//0xCC950D6C
	PE_O26_LOC_PE1_DRC_CTRL_28_T                           pe1_drc_ctrl_28;	//0xCC950D70
	PE_O26_LOC_PE1_DRC_CTRL_29_T                           pe1_drc_ctrl_29;	//0xCC950D74
	UINT32                                                    reserved0;	//0xCC950D78
	UINT32                                                    reserved1;	//0xCC950D7C
	PE_O26_LOC_PE1_DRC_CTRL_32_T                           pe1_drc_ctrl_32;	//0xCC950D80
	PE_O26_LOC_PE1_DRC_CTRL_33_T                           pe1_drc_ctrl_33;	//0xCC950D84
	PE_O26_LOC_PE1_DRC_CTRL_34_T                           pe1_drc_ctrl_34;	//0xCC950D88
	PE_O26_LOC_PE1_DRC_CTRL_35_T                           pe1_drc_ctrl_35;	//0xCC950D8C
	PE_O26_LOC_PE1_DRC_CTRL_36_T                           pe1_drc_ctrl_36;	//0xCC950D90
	PE_O26_LOC_PE1_DRC_CTRL_37_T                           pe1_drc_ctrl_37;	//0xCC950D94
	PE_O26_LOC_PE1_DRC_CTRL_38_T                           pe1_drc_ctrl_38;	//0xCC950D98
	PE_O26_LOC_PE1_DRC_CTRL_39_T                           pe1_drc_ctrl_39;	//0xCC950D9C
	PE_O26_LOC_PE1_DRC_CTRL_40_T                           pe1_drc_ctrl_40;	//0xCC950DA0
	PE_O26_LOC_PE1_DRC_CTRL_41_T                           pe1_drc_ctrl_41;	//0xCC950DA4
	PE_O26_LOC_PE1_DRC_CTRL_42_T                           pe1_drc_ctrl_42;	//0xCC950DA8
	PE_O26_LOC_PE1_DRC_CTRL_43_T                           pe1_drc_ctrl_43;	//0xCC950DAC
	PE_O26_LOC_PE1_DRC_CTRL_44_T                           pe1_drc_ctrl_44;	//0xCC950DB0
	PE_O26_LOC_PE1_DRC_CTRL_45_T                           pe1_drc_ctrl_45;	//0xCC950DB4
	PE_O26_LOC_PE1_DRC_CTRL_46_T                           pe1_drc_ctrl_46;	//0xCC950DB8
}PE_LOC_REG_O26_T;

#endif
