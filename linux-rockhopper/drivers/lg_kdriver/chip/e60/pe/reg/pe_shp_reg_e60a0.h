#ifndef _PE_SHP_REG_E60A0_H_
#define _PE_SHP_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC902C000 RW
	UINT32 reg_top_actv_sel                 :1;	//0:0	//0: use core pass-through active	1: use active sync delay active
	UINT32 resvd0                           :3;
	UINT32 reg_top_core_detour              :1;	//4:4	//SHP core detour enable
	UINT32 reg_top_core_bypass              :1;	//5:5	//SHP core bypass enable
	UINT32 resvd1                           :2;
	UINT32 reg_top_protocol_type            :1;	//8:8	//0: sync-based, 1: valid-based
	UINT32 resvd2                           :3;
	UINT32 reg_top_mode_3d                  :1;	//12:12	//Line memory mode	0: 2D mode	1: 3D mode(L/R interleave)
	UINT32 resvd3                           :11;
	UINT32 reg_top_422to444_mode            :1;	//24:24	//0: H-average mode	1: repeatition mode
	UINT32 resvd4                           :3;
	UINT32 reg_top_mode_444                 :1;	//28:28	//0: 422 mode	1: 444 mode
	UINT32 resvd5                           :1;
	UINT32 reg_obc_debug                    :2;	//31:30	//0: shp result 	1 : face map	2 : object map
	};
}PE_E60_SHP_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C004 RW
	UINT32 reg_core0_width                  :16;	//15:0	//processing width (imaeg_width + overlap)
	UINT32 reg_core0_height                 :16;	//31:16	//processing height (default : 2160)
	};
}PE_E60_SHP_CORE0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C008 RW
	UINT32 reg_core1_width                  :16;	//15:0	//processing width (imaeg_width + overlap)
	UINT32 reg_core1_height                 :16;	//31:16	//processing height (default : 2160)
	};
}PE_E60_SHP_CORE1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C00C RW
	UINT32 reg_top_use_extern_valid         :1;	//0:0	//Use external valid as dummy valid
	UINT32 reg_top_use_blank_preiod_cnt     :1;	//1:1	//Use blank period count for dummy valid
	UINT32 resvd                            :14;
	UINT32 reg_top_manual_blank_cnt         :16;	//31:16	//Manual latency cycles for dummy valid	(= H_SYNC+H_F_PORCH+H_B_PORCH-overlap)
	};
}PE_E60_SHP_CORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C010 RW
	UINT32 reg_top_pic_init_latency         :12;	//11:0	//pic init latency
	UINT32 resvd                            :20;
	};
}PE_E60_SHP_CORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C014 RW
	UINT32 reg_top_update_ctrl              :5;	//4:0	//[0]: master_select	[1]: update_force_r	[2]: update_force_w	[3]: update_flag_r	[4]: update_flag_w
	UINT32 resvd0                           :11;
	UINT32 reg_top_rst_async_bridge         :8;	//23:16	//pqe_vsd_top control register
	UINT32 resvd1                           :8;
	};
}PE_E60_SHP_CORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C040 RW
	UINT32 reg_pat_en                       :1;	//0:0	//pattern enable
	UINT32 reg_pat_thickness                :2;	//2:1	//pattern thickness (0: 1pix, 1: 2pix, 2: 4pix, 3: 8pix)
	UINT32 resvd                            :5;
	UINT32 reg_pat_pix_val_yy               :8;	//15:8	//pattern pixel value (Y)
	UINT32 reg_pat_pix_val_cb               :8;	//23:16	//pattern pixel value (Cb)
	UINT32 reg_pat_pix_val_cr               :8;	//31:24	//pattern pixel value (Cr)
	};
}PE_E60_SHP_PAT_GEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C044 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_GOS_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C048 RW
	UINT32 reg_new_fd_detail_beta_mul       :8;	//7:0	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_detail_alpha_mul      :8;	//15:8	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_new_fd_edge_beta_mul         :8;	//23:16	//get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_new_fd_edge_alpha_mul        :8;	//31:24	//get_t_map (alpha*t_map - beta*a_map)
	};
}PE_E60_SHP_NEW_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C04C RW
	UINT32 reg_new_fd_edge_minmax_y0        :8;	//7:0	//Final edge LUT, y0
	UINT32 reg_new_fd_edge_minmax_x0        :8;	//15:8	//Final edge LUT, x0
	UINT32 reg_new_fd_edge_minmax_y1        :8;	//23:16	//Final edge LUT, y1
	UINT32 reg_new_fd_edge_minmax_x1        :8;	//31:24	//Final edge LUT, x1
	};
}PE_E60_SHP_NEW_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C050 RW
	UINT32 reg_new_fd_edge_minmax_y2        :8;	//7:0	//Final edge LUT, y2
	UINT32 reg_new_fd_edge_minmax_x2        :8;	//15:8	//Final edge LUT, x2
	UINT32 reg_new_fd_edge_minmax_y3        :8;	//23:16	//Final edge LUT, y3
	UINT32 reg_new_fd_edge_minmax_x3        :8;	//31:24	//Final edge LUT, x3
	};
}PE_E60_SHP_NEW_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C054 RW
	UINT32 reg_new_fd_detail_minmax_y0      :8;	//7:0	//Final detail LUT, y0
	UINT32 reg_new_fd_detail_minmax_x0      :8;	//15:8	//Final detail LUT, x0
	UINT32 reg_new_fd_detail_minmax_y1      :8;	//23:16	//Final detail LUT, y1
	UINT32 reg_new_fd_detail_minmax_x1      :8;	//31:24	//Final detail LUT, x1
	};
}PE_E60_SHP_NEW_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C058 RW
	UINT32 reg_new_fd_detail_minmax_y2      :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_new_fd_detail_minmax_x2      :8;	//15:8	//Final detail LUT, x2
	UINT32 reg_new_fd_detail_minmax_y3      :8;	//23:16	//Final detail LUT, y3
	UINT32 reg_new_fd_detail_minmax_x3      :8;	//31:24	//Final detail LUT, x3
	};
}PE_E60_SHP_NEW_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C05C RW
	UINT32 reg_texture_region_alpha         :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_region_text_en_aux           :1;	//8:8	//Final detail LUT, y2
	UINT32 reg_obj_shp_en_aux               :1;	//9:9	//Final detail LUT, y2
	UINT32 resvd                            :22;
	};
}PE_E60_SHP_TEXT_REGION_MAP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C060 RW
	UINT32 reg_core0_sync_dly_vsync         :16;	//15:0	//v sync (2K
	UINT32 reg_core0_sync_dly_vfp           :16;	//31:16	//v front porch (2K
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C064 RW
	UINT32 reg_core0_sync_dly_va            :16;	//15:0	//v active (2K
	UINT32 reg_core0_sync_dly_vbp           :16;	//31:16	//v back porch (2K
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C068 RW
	UINT32 reg_core0_sync_dly_hsync         :16;	//15:0	//h sync (2K
	UINT32 reg_core0_sync_dly_hfp           :16;	//31:16	//h front porch (2K
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C06C RW
	UINT32 reg_core0_sync_dly_ha            :16;	//15:0	//h active (2K
	UINT32 reg_core0_sync_dly_hbp           :16;	//31:16	//h back porch (2K
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C070 RW
	UINT32 reg_core0_sync_dly_line_start    :16;	//15:0	//line increase position
	UINT32 reg_core0_sync_dly_actv_sel_in_h_src :1;	//16:16	//select inverse in ha source
	UINT32 reg_core0_sync_dly_actv_sel_in_v_src :1;	//17:17	//select inverse in va source
	UINT32 reg_core0_sync_dly_actv_sel_in_h_inv :1;	//18:18	//inverse in ha
	UINT32 reg_core0_sync_dly_actv_sel_in_v_inv :1;	//19:19	//inverse in va
	UINT32 reg_core0_sync_dly_actv_sel_out_ha :1;	//20:20	//select out ha
	UINT32 reg_core0_sync_dly_actv_sel_out_va :1;	//21:21	//select out va
	UINT32 reg_core0_sync_dly_actv_sel_out_hs :1;	//22:22	//select out hs
	UINT32 reg_core0_sync_dly_actv_sel_out_vs :1;	//23:23	//select out vs
	UINT32 reg_core0_sync_dly_tp_update_hv_zero :1;	//24:24	//sync parameter update
	UINT32 reg_core0_sync_dly_force_out_ha  :1;	//25:25	//force out ha
	UINT32 reg_core0_sync_dly_force_out_va  :1;	//26:26	//force out va
	UINT32 reg_core0_sync_dly_force_out_hs  :1;	//27:27	//force out hs
	UINT32 reg_core0_sync_dly_cnt_rst_h_value_en :1;	//28:28	//manual cnt h value enable
	UINT32 reg_core0_sync_dly_cnt_rst_v_value_en :1;	//29:29	//manual cnt v value enable
	UINT32 reg_core0_sync_dly_force_out_vs  :1;	//30:30	//force out vs
	UINT32 reg_core0_sync_dly_force_update  :1;	//31:31	//force update
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C074 RW
	UINT32 reg_core0_sync_dly_sync_h_dly    :16;	//15:0	//pixel delay
	UINT32 reg_core0_sync_dly_sync_v_dly    :16;	//31:16	//line delay
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C078 RW
	UINT32 reg_core0_sync_dly_cnt_rst_h_value :16;	//15:0	//disp_pulse_dly Delay
	UINT32 reg_core0_sync_dly_cnt_rst_v_value :16;	//31:16	//[RO] disp_pulse_dly Counter
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C07C RW
	UINT32 reg_core0_sync_dly_auto_actv_h_dly :15;	//14:0	//auto actv pixel delay
	UINT32 reg_core0_sync_dly_auto_actv_gen_en :1;	//15:15	//auto actv gen enable
	UINT32 reg_core0_sync_dly_auto_actv_v_dly :15;	//30:16	//auto actv line delay
	UINT32 reg_core0_sync_dly_auto_actv_seam_en :1;	//31:31	//auto actv seam enable
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C080 RW
	UINT32 reg_core0_sync_dly_auto_sync_h_dly :15;	//14:0	//auto sync pixel delay
	UINT32 reg_core0_sync_dly_auto_sync_gen_en :1;	//15:15	//auto sync gen enable
	UINT32 reg_core0_sync_dly_auto_sync_v_dly :15;	//30:16	//auto sync line delay
	UINT32 reg_core0_sync_dly_auto_sync_seam_en :1;	//31:31	//auto sync seam enable
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C084 RW
	UINT32 reg_core0_sync_dly_normal_number :16;	//15:0	//protection mode
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C088 RW
	UINT32 reg_core0_sync_dly_cnt_h_rst_position :16;	//15:0	//manual cnt h value position
	UINT32 reg_core0_sync_dly_cnt_v_rst_position :16;	//31:16	//manual cnt v value position
	};
}PE_E60_SHP_CORE0_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C090 RW
	UINT32 reg_core1_sync_dly_vsync         :16;	//15:0	//v sync (2K
	UINT32 reg_core1_sync_dly_vfp           :16;	//31:16	//v front porch (2K
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C094 RW
	UINT32 reg_core1_sync_dly_va            :16;	//15:0	//v active (2K
	UINT32 reg_core1_sync_dly_vbp           :16;	//31:16	//v back porch (2K
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C098 RW
	UINT32 reg_core1_sync_dly_hsync         :16;	//15:0	//h sync (2K
	UINT32 reg_core1_sync_dly_hfp           :16;	//31:16	//h front porch (2K
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C09C RW
	UINT32 reg_core1_sync_dly_ha            :16;	//15:0	//h active (2K
	UINT32 reg_core1_sync_dly_hbp           :16;	//31:16	//h back porch (2K
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0A0 RW
	UINT32 reg_core1_sync_dly_line_start    :16;	//15:0	//line increase position
	UINT32 reg_core1_sync_dly_actv_sel_in_h_src :1;	//16:16	//select inverse in ha source
	UINT32 reg_core1_sync_dly_actv_sel_in_v_src :1;	//17:17	//select inverse in va source
	UINT32 reg_core1_sync_dly_actv_sel_in_h_inv :1;	//18:18	//inverse in ha
	UINT32 reg_core1_sync_dly_actv_sel_in_v_inv :1;	//19:19	//inverse in va
	UINT32 reg_core1_sync_dly_actv_sel_out_ha :1;	//20:20	//select out ha
	UINT32 reg_core1_sync_dly_actv_sel_out_va :1;	//21:21	//select out va
	UINT32 reg_core1_sync_dly_actv_sel_out_hs :1;	//22:22	//select out hs
	UINT32 reg_core1_sync_dly_actv_sel_out_vs :1;	//23:23	//select out vs
	UINT32 reg_core1_sync_dly_tp_update_hv_zero :1;	//24:24	//sync parameter update
	UINT32 reg_core1_sync_dly_force_out_ha  :1;	//25:25	//force out ha
	UINT32 reg_core1_sync_dly_force_out_va  :1;	//26:26	//force out va
	UINT32 reg_core1_sync_dly_force_out_hs  :1;	//27:27	//force out hs
	UINT32 reg_core1_sync_dly_cnt_rst_h_value_en :1;	//28:28	//manual cnt h value enable
	UINT32 reg_core1_sync_dly_cnt_rst_v_value_en :1;	//29:29	//manual cnt v value enable
	UINT32 reg_core1_sync_dly_force_out_vs  :1;	//30:30	//force out vs
	UINT32 reg_core1_sync_dly_force_update  :1;	//31:31	//force update
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0A4 RW
	UINT32 reg_core1_sync_dly_sync_h_dly    :16;	//15:0	//pixel delay
	UINT32 reg_core1_sync_dly_sync_v_dly    :16;	//31:16	//line delay
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0A8 RW
	UINT32 reg_core1_sync_dly_cnt_rst_h_value :16;	//15:0	//disp_pulse_dly Delay
	UINT32 reg_core1_sync_dly_cnt_rst_v_value :16;	//31:16	//[RO] disp_pulse_dly Counter
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0AC RW
	UINT32 reg_core1_sync_dly_auto_actv_h_dly :15;	//14:0	//auto actv pixel delay
	UINT32 reg_core1_sync_dly_auto_actv_gen_en :1;	//15:15	//auto actv gen enable
	UINT32 reg_core1_sync_dly_auto_actv_v_dly :15;	//30:16	//auto actv line delay
	UINT32 reg_core1_sync_dly_auto_actv_seam_en :1;	//31:31	//auto actv seam enable
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0B0 RW
	UINT32 reg_core1_sync_dly_auto_sync_h_dly :15;	//14:0	//auto sync pixel delay
	UINT32 reg_core1_sync_dly_auto_sync_gen_en :1;	//15:15	//auto sync gen enable
	UINT32 reg_core1_sync_dly_auto_sync_v_dly :15;	//30:16	//auto sync line delay
	UINT32 reg_core1_sync_dly_auto_sync_seam_en :1;	//31:31	//auto sync seam enable
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0B4 RW
	UINT32 reg_core1_sync_dly_normal_number :16;	//15:0	//protection mode
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0B8 RW
	UINT32 reg_core1_sync_dly_cnt_h_rst_position :16;	//15:0	//manual cnt h value position
	UINT32 reg_core1_sync_dly_cnt_v_rst_position :16;	//31:16	//manual cnt v value position
	};
}PE_E60_SHP_CORE1_SYNC_DLY_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0C0 RW
	UINT32 reg_core0_roi_mask_en            :1;	//0:0	//ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_core0_roi_mask_pix_val_yy    :8;	//15:8	//ROI mask pixel value (Y)
	UINT32 reg_core0_roi_mask_pix_val_cb    :8;	//23:16	//ROI mask pixel value (Cb)
	UINT32 reg_core0_roi_mask_pix_val_cr    :8;	//31:24	//ROI mask pixel value (Cr)
	};
}PE_E60_SHP_CORE0_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0C4 RW
	UINT32 reg_core0_roi_mask_win_x0        :12;	//11:0	//ROI mask window start position, x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_roi_mask_win_y0        :12;	//27:16	//ROI mask window start position, y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0C8 RW
	UINT32 reg_core0_roi_mask_win_x1        :12;	//11:0	//ROI mask window end position, x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_roi_mask_win_y1        :12;	//27:16	//ROI mask window end position, y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0D0 RW
	UINT32 reg_core1_roi_mask_en            :1;	//0:0	//ROI mask enable
	UINT32 resvd                            :7;
	UINT32 reg_core1_roi_mask_pix_val_yy    :8;	//15:8	//ROI mask pixel value (Y)
	UINT32 reg_core1_roi_mask_pix_val_cb    :8;	//23:16	//ROI mask pixel value (Cb)
	UINT32 reg_core1_roi_mask_pix_val_cr    :8;	//31:24	//ROI mask pixel value (Cr)
	};
}PE_E60_SHP_CORE1_ROI_MASK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0D4 RW
	UINT32 reg_core1_roi_mask_win_x0        :12;	//11:0	//ROI mask window start position, x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_roi_mask_win_y0        :12;	//27:16	//ROI mask window start position, y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_ROI_MASK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C0D8 RW
	UINT32 reg_core1_roi_mask_win_x1        :12;	//11:0	//ROI mask window end position, x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_roi_mask_win_y1        :12;	//27:16	//ROI mask window end position, y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_ROI_MASK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C100 RW
	UINT32 reg_esf_detour_mode              :1;	//0:0	//edge shift filter detour enable
	UINT32 reg_esf_buffer_detour_en         :1;	//1:1	//edge shift filter buffer detour enable
	UINT32 resvd0                           :2;
	UINT32 reg_esf_en                       :1;	//4:4	//edge shift filter enable
	UINT32 resvd1                           :3;
	UINT32 reg_esf_dbg_en                   :1;	//8:8	//edge shift filter debug enable
	UINT32 resvd2                           :23;
	};
}PE_E60_SHP_ESF_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C104 RW
	UINT32 reg_esf_min_ratio                :8;	//7:0	//edge shift filter min ratio
	UINT32 reg_esf_base                     :8;	//15:8	//edge shift filter base
	UINT32 reg_esf_max_clip                 :8;	//23:16	//edge shift filter max clipping
	UINT32 reg_esf_master_gain              :8;	//31:24	//edge shift filter master gain
	};
}PE_E60_SHP_ESF_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C108 RW
	UINT32 reg_esf_ltv_offset               :8;	//7:0	//edge shift filter ltv offset
	UINT32 reg_esf_ltv_mul                  :8;	//15:8	//edge shift filter ltv mul
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_ESF_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C110 RW
	UINT32 reg_core0_win_esf_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_esf_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_esf_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_esf_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_esf_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_esf_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_esf_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core0_win_esf_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core0_win_esf_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_esf_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_esf_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C114 RW
	UINT32 reg_core0_win_esf_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_esf_win_w0_y0      :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE0_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C118 RW
	UINT32 reg_core0_win_esf_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_esf_win_w0_y1      :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE0_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C11C RW
	UINT32 reg_core0_win_esf_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_esf_win_w1_y0      :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE0_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C120 RW
	UINT32 reg_core0_win_esf_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_esf_win_w1_y1      :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE0_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C130 RW
	UINT32 reg_core1_win_esf_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_esf_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_esf_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_esf_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_esf_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_esf_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_esf_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core1_win_esf_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core1_win_esf_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_esf_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_esf_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_ESF_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C134 RW
	UINT32 reg_core1_win_esf_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_esf_win_w0_y0      :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE1_ESF_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C138 RW
	UINT32 reg_core1_win_esf_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_esf_win_w0_y1      :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE1_ESF_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C13C RW
	UINT32 reg_core1_win_esf_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_esf_win_w1_y0      :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE1_ESF_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C140 RW
	UINT32 reg_core1_win_esf_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_esf_win_w1_y1      :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE1_ESF_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C150 RW
	UINT32 reg_dp_debug_display             :4;	//3:0	//0000: normal display (output 1)	0001: normal display (output 2)	0010: tgen only	0011: bypass	0100: weight(A)	0101: weight(Texture)	0110: A-map	0111: T-map	1000: soft edge gain map	1001: A-map for der	1010: Motion map	1011: Gain A-map	1100: Gain T-map	1101: Texture region map	1110: object map	1111: face map
	UINT32 reg_dp_detour_en                 :1;	//4:4	//dp detour enable
	UINT32 resvd0                           :3;
	UINT32 reg_dp_buffer_detour_en          :1;	//8:8	//dp buffer detour enable
	UINT32 resvd1                           :23;
	};
}PE_E60_SHP_DP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C160 RW
	UINT32 reg_fd_a_map_h_size              :2;	//1:0	//A-map h size
	UINT32 resvd0                           :6;
	UINT32 reg_fd_a_map_post_filter_en      :1;	//8:8	//post-mmd enable
	UINT32 resvd1                           :7;
	UINT32 reg_fd_pre_a_map_h_size          :3;	//18:16	//pre-mmd h size
	UINT32 reg_fd_pre_a_map_v_size          :2;	//20:19	//pre-mmd v size
	UINT32 reg_fd_pre_a_cut_resolution      :3;	//23:21	//pre-mmd cut resolution
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_FD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C164 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_FD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C168 RW
	UINT32 reg_fd_detail_beta_mul           :8;	//7:0	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_detail_alpha_mul          :8;	//15:8	//get e_map (alpha*a_map - beta*t_map)
	UINT32 reg_fd_edge_beta_mul             :8;	//23:16	//get_t_map (alpha*t_map - beta*a_map)
	UINT32 reg_fd_edge_alpha_mul            :8;	//31:24	//get_t_map (alpha*t_map - beta*a_map)
	};
}PE_E60_SHP_FD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C16C RW
	UINT32 reg_fd_a_lut_edge_y0             :8;	//7:0	//A-map edge LUT, y0
	UINT32 reg_fd_a_lut_edge_x0             :8;	//15:8	//A-map edge LUT, x0
	UINT32 reg_fd_a_lut_edge_y1             :8;	//23:16	//A-map edge LUT, y1
	UINT32 reg_fd_a_lut_edge_x1             :8;	//31:24	//A-map edge LUT, x1
	};
}PE_E60_SHP_FD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C170 RW
	UINT32 reg_fd_a_lut_detail_y0           :8;	//7:0	//A-map detail LUT, y0
	UINT32 reg_fd_a_lut_detail_x0           :8;	//15:8	//A-map detail LUT, x0
	UINT32 reg_fd_a_lut_detail_y1           :8;	//23:16	//A-map detail LUT, y1
	UINT32 reg_fd_a_lut_detail_x1           :8;	//31:24	//A-map detail LUT, x1
	};
}PE_E60_SHP_FD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C174 RW
	UINT32 reg_fd_t_lut_edge_y0             :8;	//7:0	//T-map edge LUT, y0
	UINT32 reg_fd_t_lut_edge_x0             :8;	//15:8	//T-map edge LUT, x0
	UINT32 reg_fd_t_lut_edge_y1             :8;	//23:16	//T-map edge LUT, y1
	UINT32 reg_fd_t_lut_edge_x1             :8;	//31:24	//T-map edge LUT, x1
	};
}PE_E60_SHP_FD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C178 RW
	UINT32 reg_fd_t_lut_detail_y0           :8;	//7:0	//T-map detail LUT, y0
	UINT32 reg_fd_t_lut_detail_x0           :8;	//15:8	//T-map detail LUT, x0
	UINT32 reg_fd_t_lut_detail_y1           :8;	//23:16	//T-map detail LUT, y1
	UINT32 reg_fd_t_lut_detail_x1           :8;	//31:24	//T-map detail LUT, x1
	};
}PE_E60_SHP_FD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C17C RW
	UINT32 reg_fd_edge_minmax_y0            :8;	//7:0	//Final edge LUT, y0
	UINT32 reg_fd_edge_minmax_x0            :8;	//15:8	//Final edge LUT, x0
	UINT32 reg_fd_edge_minmax_y1            :8;	//23:16	//Final edge LUT, y1
	UINT32 reg_fd_edge_minmax_x1            :8;	//31:24	//Final edge LUT, x1
	};
}PE_E60_SHP_FD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C180 RW
	UINT32 reg_fd_edge_minmax_y2            :8;	//7:0	//Final edge LUT, y2
	UINT32 reg_fd_edge_minmax_x2            :8;	//15:8	//Final edge LUT, x2
	UINT32 reg_fd_edge_minmax_y3            :8;	//23:16	//Final edge LUT, y3
	UINT32 reg_fd_edge_minmax_x3            :8;	//31:24	//Final edge LUT, x3
	};
}PE_E60_SHP_FD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C184 RW
	UINT32 reg_fd_detail_minmax_y0          :8;	//7:0	//Final detail LUT, y0
	UINT32 reg_fd_detail_minmax_x0          :8;	//15:8	//Final detail LUT, x0
	UINT32 reg_fd_detail_minmax_y1          :8;	//23:16	//Final detail LUT, y1
	UINT32 reg_fd_detail_minmax_x1          :8;	//31:24	//Final detail LUT, x1
	};
}PE_E60_SHP_FD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C188 RW
	UINT32 reg_fd_detail_minmax_y2          :8;	//7:0	//Final detail LUT, y2
	UINT32 reg_fd_detail_minmax_x2          :8;	//15:8	//Final detail LUT, x2
	UINT32 reg_fd_detail_minmax_y3          :8;	//23:16	//Final detail LUT, y3
	UINT32 reg_fd_detail_minmax_x3          :8;	//31:24	//Final detail LUT, x3
	};
}PE_E60_SHP_FD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C18C RW
	UINT32 reg_fd_mnr_gain_e_en             :1;	//0:0	//MNR gain for edge gain enable
	UINT32 reg_fd_mnr_gain_t_en             :1;	//1:1	//MNR gain for texture gain enable
	UINT32 resvd0                           :2;
	UINT32 reg_fd_mnr_s1_h_expand           :2;	//5:4	//s1 h expand
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_FD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C190 RW
	UINT32 reg_fd_mnr_s1_mmd_min            :8;	//7:0	//s1 mmd min
	UINT32 resvd0                           :8;
	UINT32 reg_fd_mnr_s2_ratio_max          :8;	//23:16	//s1 ratio max
	UINT32 resvd1                           :8;
	};
}PE_E60_SHP_FD_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C194 RW
	UINT32 reg_fd_mnr_gain_x0               :8;	//7:0	//MNR gain LUT, x0
	UINT32 reg_fd_mnr_gain_x1               :8;	//15:8	//MNR gain LUT, x1
	UINT32 reg_fd_mnr_gain_y0               :8;	//23:16	//MNR gain LUT, y0
	UINT32 reg_fd_mnr_gain_y1               :8;	//31:24	//MNR gain LUT, y1
	};
}PE_E60_SHP_FD_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C198 RW
	UINT32 reg_fd_dct_t_lut_y0              :8;	//7:0	//DCT T-map LUT, y0
	UINT32 reg_fd_dct_t_lut_x0              :8;	//15:8	//DCT T-map LUT, x0
	UINT32 reg_fd_dct_t_lut_y1              :8;	//23:16	//DCT T-map LUT, y1
	UINT32 reg_fd_dct_t_lut_x1              :8;	//31:24	//DCT T-map LUT, x1
	};
}PE_E60_SHP_FD_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C19C RW
	UINT32 reg_fd_dct_t_lut_y2              :8;	//7:0	//DCT T-map LUT, y2
	UINT32 reg_fd_dct_t_lut_x2              :8;	//15:8	//DCT T-map LUT, x2
	UINT32 reg_fd_dct_t_lut_y3              :8;	//23:16	//DCT T-map LUT, y3
	UINT32 reg_fd_dct_t_lut_x3              :8;	//31:24	//DCT T-map LUT, x3
	};
}PE_E60_SHP_FD_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1A0 RW
	UINT32 reg_fd_dct_t_lut_y4              :8;	//7:0	//DCT T-map LUT, y4
	UINT32 reg_fd_dct_t_lut_x4              :8;	//15:8	//DCT T-map LUT, x4
	UINT32 reg_fd_dct_t_lut_y5              :8;	//23:16	//DCT T-map LUT, y5
	UINT32 reg_fd_dct_t_lut_x5              :8;	//31:24	//DCT T-map LUT, x5
	};
}PE_E60_SHP_FD_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1A4 RW
	UINT32 reg_fd_soft_gain_e_en            :1;	//0:0	//Soft edge for edge gain enable
	UINT32 reg_fd_soft_gain_t_en            :1;	//1:1	//Soft edge for texture gain enable
	UINT32 resvd                            :30;
	};
}PE_E60_SHP_FD_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1A8 RW
	UINT32 reg_fd_soft_ratio                :8;	//7:0	//Soft edge A-map to mmd ratio
	UINT32 reg_fd_soft_offset               :8;	//15:8	//Soft edge offset
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_FD_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1AC RW
	UINT32 reg_fd_soft_score_x0             :8;	//7:0	//Soft edge score, x0
	UINT32 reg_fd_soft_score_x1             :8;	//15:8	//Soft edge score, x1
	UINT32 reg_fd_soft_score_x2             :8;	//23:16	//Soft edge score, x2
	UINT32 reg_fd_soft_score_x3             :8;	//31:24	//Soft edge score, x3
	};
}PE_E60_SHP_FD_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1B0 RW
	UINT32 reg_fd_soft_score_y0             :6;	//5:0	//Soft edge score, y0
	UINT32 resvd0                           :2;
	UINT32 reg_fd_soft_score_y1             :6;	//13:8	//Soft edge score, y1
	UINT32 resvd1                           :2;
	UINT32 reg_fd_soft_score_y2             :6;	//21:16	//Soft edge score, y2
	UINT32 resvd2                           :2;
	UINT32 reg_fd_soft_score_y3             :6;	//29:24	//Soft edge score, y3
	UINT32 resvd3                           :2;
	};
}PE_E60_SHP_FD_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1B4 RW
	UINT32 reg_fd_flat_input_sel            :2;	//1:0	//input selection for flat region lut	0 : a_map	1 : t_map	2 : max(a_map, t_map)	3 (default) : min (255, a_map + t_map)
	UINT32 resvd0                           :2;
	UINT32 reg_fd_flat_protect_e_en         :1;	//4:4	//1 : add a flat gain to a_map
	UINT32 resvd1                           :3;
	UINT32 reg_fd_flat_protect_t_en         :1;	//8:8	//1 : add a flat gain to t_map
	UINT32 resvd2                           :23;
	};
}PE_E60_SHP_FD_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1B8 RW
	UINT32 reg_fd_flat_lut_y0               :8;	//7:0	//Flat region LUT, y0
	UINT32 reg_fd_flat_lut_x0               :8;	//15:8	//Flat region LUT, x0
	UINT32 reg_fd_flat_lut_y1               :8;	//23:16	//Flat region LUT, y1
	UINT32 reg_fd_flat_lut_x1               :8;	//31:24	//Flat region LUT, x1
	};
}PE_E60_SHP_FD_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1C0 RW
	UINT32 reg_mp_shp_en                    :1;	//0:0	//MP enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_MP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1C4 RW
	UINT32 reg_mp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 reg_mp_im_gain_v                 :8;	//31:24	//im gain v
	};
}PE_E60_SHP_MP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1C8 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_E60_SHP_MP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1CC RW
	UINT32 resvd0                           :4;
	UINT32 reg_mp_lap_gain_v_7              :4;	//7:4	//Laplacian gain v 7
	UINT32 reg_mp_lap_gain_v_5              :4;	//11:8	//Laplacian gain v 5
	UINT32 reg_mp_lap_gain_v_3              :4;	//15:12	//Laplacian gain v 3
	UINT32 resvd1                           :4;
	UINT32 reg_mp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_mp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_mp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}PE_E60_SHP_MP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1D0 RW
	UINT32 resvd0                           :8;
	UINT32 reg_mp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_E60_SHP_MP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1D4 RW
	UINT32 reg_mp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_mp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_mp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_mp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_MP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1D8 RW
	UINT32 reg_mp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_mp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_mp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_E60_SHP_MP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1DC RW
	UINT32 reg_mp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_mp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_mp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_mp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}PE_E60_SHP_MP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1E0 RW
	UINT32 reg_mp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_mp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_mp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_mp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}PE_E60_SHP_MP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1E4 RW
	UINT32 reg_mp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_mp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_mp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_mp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}PE_E60_SHP_MP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1E8 RW
	UINT32 reg_mp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_mp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_MP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1EC RW
	UINT32 reg_mp_coring_en                 :1;	//0:0	//[MP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_mp_coring_mode               :2;	//2:1	//[MP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_MP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1F0 RW
	UINT32 reg_mp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_mp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_mp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_mp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_MP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C1F4 RW
	UINT32 reg_apl_iir_en                   :1;	//0:0	//APL IIR enable
	UINT32 resvd0                           :7;
	UINT32 reg_apl_iir_gain                 :8;	//15:8	//APL gain
	UINT32 resvd1                           :16;
	};
}PE_E60_SHP_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C200 RW
	UINT32 reg_lc_shp_en                      :1 ;	// 0:0
	UINT32 reserved01                         :3 ;	// reserved
	UINT32 reg_lc_gb_en                       :1 ;	// 4:4
	UINT32 reserved02                         :3 ;	// reserved
	UINT32 reg_lc_center_target             :8;	//15:8	//center target
	UINT32 reg_lc_center_gain               :8;	//23:16	//center gain
	UINT32 reg_lc_local_gain                :8;	//31:24	//local gain
	};
}PE_E60_SHP_LC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C204 RW
	UINT32 reg_lc_gb_y2                     :8;	//7:0	//gain balancing, y2
	UINT32 reg_lc_gb_x2                     :8;	//15:8	//gain balancing, x2
	UINT32 reg_lc_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 reg_lc_gb_x1                     :8;	//31:24	//gain balancing, x1
	};
}PE_E60_SHP_LC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C208 RW
	UINT32 resvd                            :8;
	UINT32 reg_lc_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 reg_lc_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 reg_lc_gb_x3                     :8;	//31:24	//gain balancing, x3
	};
}PE_E60_SHP_LC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C20C RW
	UINT32 reg_lc_coring_en                 :1;	//0:0	//[LC]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_lc_coring_mode               :2;	//2:1	//[LC]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_LC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C210 RW
	UINT32 reg_lc_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_lc_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_lc_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_lc_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_LC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C220 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_csft_gain               :6;	//13:8	//reg_csft_gain: center shift gain(1.5u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_th_gain_edge            :6;	//21:16	//reg_th_gain_Edge: BiFLT threshold gain(1.5u)
	UINT32 resvd2                           :2;
	UINT32 reg_derh_th_manual_th            :7;	//30:24	//reg_th_manual_th
	UINT32 reg_derh_th_manual_en            :1;	//31:31	//reg_th_manual_en
	};
}PE_E60_SHP_DER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C224 RW
	UINT32 reg_derh_bflt_tap_size           :3;	//2:0	//bflt_tap_size
	UINT32 resvd0                           :21;
	UINT32 reg_derh_amean_en                :1;	//24:24	//reg_amean_en
	UINT32 resvd1                           :1;
	UINT32 reg_derh_edge_filter_v_tap       :2;	//27:26	//edge filter V tap	0: 5tap	1: 3tap	others: 1tap
	UINT32 resvd2                           :3;
	UINT32 reg_derh_edge_y_filter_en        :1;	//31:31	//edge_Y_filter en
	};
}PE_E60_SHP_DER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C228 RW
	UINT32 resvd0                           :8;
	UINT32 reg_derh_edge_filter_gain_w      :6;	//13:8	//edge filter white gain (2.4u)
	UINT32 resvd1                           :2;
	UINT32 reg_derh_edge_filter_gain_b      :6;	//21:16	//edge filter black gain (2.4u)
	UINT32 resvd2                           :10;
	};
}PE_E60_SHP_DER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C22C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_DER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C230 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_DER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C234 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_DER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C238 RW
	UINT32 reg_der_a_lut_y0                 :8;	//7:0	//A-map for der LUT, y0
	UINT32 reg_der_a_lut_x0                 :8;	//15:8	//A-map for der LUT, x0
	UINT32 reg_der_a_lut_y1                 :8;	//23:16	//A-map for der LUT, y1
	UINT32 reg_der_a_lut_x1                 :8;	//31:24	//A-map for der LUT, x1
	};
}PE_E60_SHP_DER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C23C RW
	UINT32 reg_der_a_lut_y2                 :8;	//7:0	//A-map for de-rining LUT, y2
	UINT32 reg_der_a_lut_x2                 :8;	//15:8	//A-map for de-rining LUT, x2
	UINT32 reg_der_a_lut_y3                 :8;	//23:16	//A-map for de-rining LUT, y3
	UINT32 reg_der_a_lut_x3                 :8;	//31:24	//A-map for de-rining LUT, x3
	};
}PE_E60_SHP_DER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C240 RW
	UINT32 reg_sp_shp_en                    :1;	//0:0	//SP enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_SP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C244 RW
	UINT32 reg_sp_im_os_gain                :7;	//6:0	//im os gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_im_us_gain                :7;	//14:8	//im us gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_im_gain_h                 :8;	//23:16	//im gain h
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_SP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C248 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_lap_weight                :8;	//15:8	//Laplacian weight
	UINT32 resvd1                           :16;
	};
}PE_E60_SHP_SP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C24C RW
	UINT32 resvd                            :20;
	UINT32 reg_sp_lap_gain_h_7              :4;	//23:20	//Laplacian gain h 7
	UINT32 reg_sp_lap_gain_h_5              :4;	//27:24	//Laplacian gain h 5
	UINT32 reg_sp_lap_gain_h_3              :4;	//31:28	//Laplacian gain h 3
	};
}PE_E60_SHP_SP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C250 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sp_dbg_sel                   :4;	//11:8	//display mode	0000: normal display	1000: lum1 gain	1001: lum2 gain	o.w : reserved
	UINT32 resvd1                           :20;
	};
}PE_E60_SHP_SP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C254 RW
	UINT32 reg_sp_gb_en                     :1;	//0:0	//0: disable	1: enable
	UINT32 resvd0                           :3;
	UINT32 reg_sp_gb_mode                   :1;	//4:4	//delta(x-axis) resolution	0: 8bit	1: 10bit
	UINT32 resvd1                           :3;
	UINT32 reg_sp_gb_x1                     :8;	//15:8	//gain balancing, x1
	UINT32 reg_sp_gb_y1                     :8;	//23:16	//gain balancing, y1
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_SP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C258 RW
	UINT32 reg_sp_gb_x2                     :8;	//7:0	//gain balancing, x2
	UINT32 reg_sp_gb_y2                     :8;	//15:8	//gain balancing, y2
	UINT32 reg_sp_gb_y3                     :8;	//23:16	//gain balancing, y3
	UINT32 resvd                            :8;
	};
}PE_E60_SHP_SP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C25C RW
	UINT32 reg_sp_lum1_x_l0                 :8;	//7:0	//level-balancing, lum1_x_L0
	UINT32 reg_sp_lum1_x_l1                 :8;	//15:8	//level-balancing, lum1_x_L1
	UINT32 reg_sp_lum1_x_h0                 :8;	//23:16	//level-balancing, lum1_x_H0
	UINT32 reg_sp_lum1_x_h1                 :8;	//31:24	//level-balancing, lum1_x_H1
	};
}PE_E60_SHP_SP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C260 RW
	UINT32 reg_sp_lum1_y0                   :8;	//7:0	//level-balancing, lum1_y0
	UINT32 reg_sp_lum1_y1                   :8;	//15:8	//level-balancing, lum1_y1
	UINT32 reg_sp_lum1_y2                   :8;	//23:16	//level-balancing, lum1_y2
	UINT32 reg_sp_lum2_x_l0                 :8;	//31:24	//level-balancing, lum2_x_L0
	};
}PE_E60_SHP_SP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C264 RW
	UINT32 reg_sp_lum2_x_l1                 :8;	//7:0	//level-balancing, lum2_x_L1
	UINT32 reg_sp_lum2_x_h0                 :8;	//15:8	//level-balancing, lum2_x_H0
	UINT32 reg_sp_lum2_x_h1                 :8;	//23:16	//level-balancing, lum2_x_H1
	UINT32 reg_sp_lum2_y0                   :8;	//31:24	//level-balancing, lum2_y0
	};
}PE_E60_SHP_SP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C268 RW
	UINT32 reg_sp_lum2_y1                   :8;	//7:0	//level-balancing, lum2_y1
	UINT32 reg_sp_lum2_y2                   :8;	//15:8	//level-balancing, lum2_y2
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_SP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C26C RW
	UINT32 reg_sp_coring_en                 :1;	//0:0	//[SP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_sp_coring_mode               :2;	//2:1	//[SP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_input_sel          :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_SP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C270 RW
	UINT32 reg_sp_coring_gain_e_b           :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_sp_coring_gain_e_w           :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_sp_coring_gain_t_b           :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_sp_coring_gain_t_w           :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_SP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C280 RW
	UINT32 reg_ptiv_enable                  :1;	//0:0	//PTI-V enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptiv_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptiv_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptiv_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptiv_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}PE_E60_SHP_PTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C284 RW
	UINT32 reg_ptih_enable                  :1;	//0:0	//PTI-H enable
	UINT32 resvd0                           :1;
	UINT32 reg_ptih_mm_tap_size             :2;	//3:2	//mm tap size
	UINT32 reg_ptih_avg_tap_size            :2;	//5:4	//avg tap size
	UINT32 reg_ptih_ti_mode                 :1;	//6:6	//ti mode
	UINT32 resvd1                           :1;
	UINT32 reg_ptih_master_gain             :8;	//15:8	//master gain
	UINT32 resvd2                           :16;
	};
}PE_E60_SHP_PTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C288 RW
	UINT32 reg_pti_coring_en                :1;	//0:0	//[PTI]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_pti_coring_mode              :2;	//2:1	//[PTI]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_input_sel         :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_PTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C28C RW
	UINT32 reg_pti_coring_gain_e_b          :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_pti_coring_gain_e_w          :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_pti_coring_gain_t_b          :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_pti_coring_gain_t_w          :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_PTI_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C290 RW
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
}PE_E60_SHP_STI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2A0 RW
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
}PE_E60_SHP_TGEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2A4 RW
	UINT32 reg_tgen_delta_h_bound           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_delta_l_bound           :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_delta_max               :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_delta_scale             :3;	//26:24	//
	UINT32 resvd3                           :5;
	};
}PE_E60_SHP_TGEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2A8 RW
	UINT32 reg_tgen_rnd_th                  :8;	//7:0	//
	UINT32 reg_tgen_delta_wcurr             :4;	//11:8	//
	UINT32 resvd0                           :4;
	UINT32 reg_tgen_lc_ldr_th               :6;	//21:16	//
	UINT32 resvd1                           :10;
	};
}PE_E60_SHP_TGEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2AC RW
	UINT32 reg_core0_tgen_rand_init_val_c0  :32;	//31:0	//
	};
}PE_E60_SHP_CORE0_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2B0 RW
	UINT32 reg_core0_tgen_rand_init_val_c1  :32;	//31:0	//
	};
}PE_E60_SHP_CORE0_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2B4 RW
	UINT32 reg_core1_tgen_rand_init_val_c0  :32;	//31:0	//
	};
}PE_E60_SHP_CORE1_TGEN_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2B8 RW
	UINT32 reg_core1_tgen_rand_init_val_c1  :32;	//31:0	//
	};
}PE_E60_SHP_CORE1_TGEN_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2BC RW
	UINT32 reg_tgen_dr_ratio                :3;	//2:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_tgen_dr_th                   :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_tgen_mm_offset               :5;	//20:16	//
	UINT32 resvd2                           :3;
	UINT32 reg_tgen_mm_sel_mode             :2;	//25:24	//
	UINT32 resvd3                           :6;
	};
}PE_E60_SHP_TGEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2C0 RW
	UINT32 resvd0                           :16;
	UINT32 reg_tgen_gs_rnd                  :5;	//20:16	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_gs_mm                   :5;	//28:24	//
	UINT32 resvd2                           :3;
	};
}PE_E60_SHP_TGEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2C4 RW
	UINT32 reg_tgen_blur_coef_x2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_x1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_x0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}PE_E60_SHP_TGEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2C8 RW
	UINT32 reg_tgen_blur_coef_y2            :6;	//5:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_tgen_blur_coef_y1            :6;	//13:8	//
	UINT32 resvd1                           :10;
	UINT32 reg_tgen_blur_coef_y0            :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}PE_E60_SHP_TGEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2CC RW
	UINT32 reg_tgen_map_edge_gain           :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_tgen_map_detail_gain         :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_tgen_map_offset              :8;	//23:16	//
	UINT32 reg_tgen_gs_noise                :6;	//29:24	//
	UINT32 resvd2                           :2;
	};
}PE_E60_SHP_TGEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2D0 RW
	UINT32 reg_tgen_gain7                   :4;	//3:0	//
	UINT32 reg_tgen_gain6                   :4;	//7:4	//
	UINT32 reg_tgen_gain5                   :4;	//11:8	//
	UINT32 reg_tgen_gain4                   :4;	//15:12	//
	UINT32 reg_tgen_gain3                   :4;	//19:16	//
	UINT32 reg_tgen_gain2                   :4;	//23:20	//
	UINT32 reg_tgen_gain1                   :4;	//27:24	//
	UINT32 reg_tgen_gain0                   :4;	//31:28	//
	};
}PE_E60_SHP_TGEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2D4 RW
	UINT32 reg_tgen_coring_en               :1;	//0:0	//[TGEN]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_tgen_coring_mode             :2;	//2:1	//[TGEN]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_TGEN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2D8 RW
	UINT32 reg_tgen_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_tgen_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_tgen_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_tgen_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_TGEN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2E0 RW
	UINT32 reg_snr_blur_en                  :1;	//0:0	//SNR enable
	UINT32 resvd0                           :3;
	UINT32 reg_snr_blur_sel                 :2;	//5:4	//filter tap	00: 3x3	01: 5x5	10: 9x5
	UINT32 resvd1                           :2;
	UINT32 reg_snr_bilateral_th             :8;	//15:8	//Diff threshold
	UINT32 reg_snr_blur_mode                :3;	//18:16	//SNR blur mode 	00: flat_gain from fd_top	01: softedge gain	10: max(flat_gain, softedge gain)	11: default min(255, flat_gain + softedge gain)
	UINT32 resvd2                           :13;
	};
}PE_E60_SHP_SNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2F0 RW
	UINT32 reg_dctp_en                      :1;	//0:0	//DCT peaking enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_DCTP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2F4 RW
	UINT32 reg_dctp_filt0_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 0, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 0, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2F8 RW
	UINT32 reg_dctp_filt0_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 0, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 0, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C2FC RW
	UINT32 reg_dctp_filt0_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 0, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 0, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C300 RW
	UINT32 reg_dctp_filt0_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 0, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt0_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 0, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C304 RW
	UINT32 reg_dctp_filt1_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 1, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 1, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C308 RW
	UINT32 reg_dctp_filt1_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 1, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 1, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C30C RW
	UINT32 reg_dctp_filt1_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 1, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 1, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C310 RW
	UINT32 reg_dctp_filt1_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 1, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt1_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 1, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C314 RW
	UINT32 reg_dctp_filt2_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 2, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 2, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C318 RW
	UINT32 reg_dctp_filt2_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 2, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 2, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C31C RW
	UINT32 reg_dctp_filt2_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 2, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 2, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C320 RW
	UINT32 reg_dctp_filt2_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 2, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt2_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 2, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C324 RW
	UINT32 reg_dctp_filt3_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 3, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 3, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C328 RW
	UINT32 reg_dctp_filt3_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 3, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 3, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C32C RW
	UINT32 reg_dctp_filt3_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 3, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 3, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C330 RW
	UINT32 reg_dctp_filt3_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 3, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt3_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 3, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C334 RW
	UINT32 reg_dctp_filt4_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 4, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 4, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C338 RW
	UINT32 reg_dctp_filt4_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 4, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 4, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C33C RW
	UINT32 reg_dctp_filt4_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 4, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 4, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C340 RW
	UINT32 reg_dctp_filt4_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 4, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt4_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 4, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C344 RW
	UINT32 reg_dctp_filt5_coef_0            :12;	//11:0	//DCT filter coefficient set (kernel 5, [0])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_1            :12;	//27:16	//DCT filter coefficient set (kernel 5, [1])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C348 RW
	UINT32 reg_dctp_filt5_coef_2            :12;	//11:0	//DCT filter coefficient set (kernel 5, [2])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_3            :12;	//27:16	//DCT filter coefficient set (kernel 5, [3])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C34C RW
	UINT32 reg_dctp_filt5_coef_4            :12;	//11:0	//DCT filter coefficient set (kernel 5, [6])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_5            :12;	//27:16	//DCT filter coefficient set (kernel 5, [7])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C350 RW
	UINT32 reg_dctp_filt5_coef_6            :12;	//11:0	//DCT filter coefficient set (kernel 5, [4])
	UINT32 resvd0                           :4;
	UINT32 reg_dctp_filt5_coef_7            :12;	//27:16	//DCT filter coefficient set (kernel 5, [5])
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_DCTP_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C354 RW
	UINT32 reg_dctp_text_lut_x0             :8;	//7:0	//DCT peaking texture LUT point, x0
	UINT32 reg_dctp_text_lut_x1             :8;	//15:8	//DCT peaking texture LUT point, x1
	UINT32 reg_dctp_text_lut_x2             :8;	//23:16	//DCT peaking texture LUT point, x2
	UINT32 reg_dctp_text_lut_x3             :8;	//31:24	//DCT peaking texture LUT point, x3
	};
}PE_E60_SHP_DCTP_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C358 RW
	UINT32 reg_dctp_text_lut_x4             :8;	//7:0	//DCT peaking texture LUT point, x4
	UINT32 reg_dctp_text_lut_x5             :8;	//15:8	//DCT peaking texture LUT point, x5
	UINT32 resvd                            :16;
	};
}PE_E60_SHP_DCTP_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C35C RW
	UINT32 reg_dctp_edge_lut_y0             :8;	//7:0	//DCT peaking edge LUT point, y0
	UINT32 reg_dctp_edge_lut_x0             :8;	//15:8	//DCT peaking edge LUT point, x0
	UINT32 reg_dctp_edge_lut_y1             :8;	//23:16	//DCT peaking edge LUT point, y1
	UINT32 reg_dctp_edge_lut_x1             :8;	//31:24	//DCT peaking edge LUT point, x1
	};
}PE_E60_SHP_DCTP_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C360 RW
	UINT32 reg_dctp_edge_lut_y2             :8;	//7:0	//DCT peaking edge LUT point, y2
	UINT32 reg_dctp_edge_lut_x2             :8;	//15:8	//DCT peaking edge LUT point, x2
	UINT32 reg_dctp_edge_lut_y3             :8;	//23:16	//DCT peaking edge LUT point, y3
	UINT32 reg_dctp_edge_lut_x3             :8;	//31:24	//DCT peaking edge LUT point, x3
	};
}PE_E60_SHP_DCTP_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C364 RW
	UINT32 reg_dctp_gain                    :8;	//7:0	//DCT peaking master gain
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_DCTP_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C368 RW
	UINT32 reg_dctp_coring_en               :1;	//0:0	//[DCTP]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_dctp_coring_mode             :2;	//2:1	//[DCTP]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_dtcp_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_DCTP_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C36C RW
	UINT32 reg_dctp_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_dctp_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_dctp_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_dctp_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_DCTP_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C370 RW
	UINT32 reg_nntg_en                      :1;	//0:0	//4K nano-noise TGEN enable
	UINT32 resvd0                           :3;
	UINT32 reg_nntg_debug_mode              :2;	//5:4	//4K nano-noise debug mode	0: Normal	1: Diff gain	2: Edge gain	3: ABS diff
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_NNTG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C374 RW
	UINT32 reg_core0_nntg_lsfr_init_1st_c0  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C378 RW
	UINT32 reg_core0_nntg_lsfr_init_2nd_c0  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C37C RW
	UINT32 reg_core0_nntg_lsfr_init_3rd_c0  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C380 RW
	UINT32 reg_core0_nntg_lsfr_init_4th_c0  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C384 RW
	UINT32 reg_core0_nntg_lsfr_init_5th_c0  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C388 RW
	UINT32 reg_core0_nntg_lsfr_init_1st_c1  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C38C RW
	UINT32 reg_core0_nntg_lsfr_init_2nd_c1  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C390 RW
	UINT32 reg_core0_nntg_lsfr_init_3rd_c1  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C394 RW
	UINT32 reg_core0_nntg_lsfr_init_4th_c1  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C398 RW
	UINT32 reg_core0_nntg_lsfr_init_5th_c1  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}PE_E60_SHP_CORE0_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C39C RW
	UINT32 reg_core1_nntg_lsfr_init_1st_c0  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_01_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3A0 RW
	UINT32 reg_core1_nntg_lsfr_init_2nd_c0  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_02_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3A4 RW
	UINT32 reg_core1_nntg_lsfr_init_3rd_c0  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_03_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3A8 RW
	UINT32 reg_core1_nntg_lsfr_init_4th_c0  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_04_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3AC RW
	UINT32 reg_core1_nntg_lsfr_init_5th_c0  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_05_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3B0 RW
	UINT32 reg_core1_nntg_lsfr_init_1st_c1  :32;	//31:0	//4K nano-noise LSFR init (1st)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_01_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3B4 RW
	UINT32 reg_core1_nntg_lsfr_init_2nd_c1  :32;	//31:0	//4K nano-noise LSFR init (2nd)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_02_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3B8 RW
	UINT32 reg_core1_nntg_lsfr_init_3rd_c1  :32;	//31:0	//4K nano-noise LSFR init (3rd)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_03_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3BC RW
	UINT32 reg_core1_nntg_lsfr_init_4th_c1  :32;	//31:0	//4K nano-noise LSFR init (4th)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_04_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3C0 RW
	UINT32 reg_core1_nntg_lsfr_init_5th_c1  :32;	//31:0	//4K nano-noise LSFR init (5th)
	};
}PE_E60_SHP_CORE1_NNTG_CTRL_05_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3C4 RW
	UINT32 reg_nntg_rand_ratio              :8;	//7:0	//4K nano-noise random ratio
	UINT32 reg_nntg_rand_max                :7;	//14:8	//4K nano-noise random max
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_rand_sum_max            :8;	//23:16	//4K nano-noise random sum clip
	UINT32 resvd1                           :8;
	};
}PE_E60_SHP_NNTG_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3C8 RW
	UINT32 reg_nntg_rand_coef_g00           :4;	//3:0	//4K nano-noise random filter coefficient, G00
	UINT32 reg_nntg_rand_coef_g01           :4;	//7:4	//4K nano-noise random filter coefficient, G01
	UINT32 reg_nntg_rand_coef_g02           :4;	//11:8	//4K nano-noise random filter coefficient, G02
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_rand_coef_g10           :4;	//19:16	//4K nano-noise random filter coefficient, G10
	UINT32 reg_nntg_rand_coef_g11           :4;	//23:20	//4K nano-noise random filter coefficient, G11
	UINT32 reg_nntg_rand_coef_g12           :4;	//27:24	//4K nano-noise random filter coefficient, G12
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_NNTG_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3CC RW
	UINT32 reg_nntg_rand_coef_g20           :4;	//3:0	//4K nano-noise random filter coefficient, G20
	UINT32 reg_nntg_rand_coef_g21           :4;	//7:4	//4K nano-noise random filter coefficient, G21
	UINT32 reg_nntg_rand_coef_g22           :4;	//11:8	//4K nano-noise random filter coefficient, G22
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g00           :4;	//19:16	//4K nano-noise nano filter coefficient, G00
	UINT32 reg_nntg_nano_coef_g01           :4;	//23:20	//4K nano-noise nano filter coefficient, G01
	UINT32 reg_nntg_nano_coef_g02           :4;	//27:24	//4K nano-noise nano filter coefficient, G02
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_NNTG_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3D0 RW
	UINT32 reg_nntg_nano_coef_g10           :4;	//3:0	//4K nano-noise nano filter coefficient, G10
	UINT32 reg_nntg_nano_coef_g11           :4;	//7:4	//4K nano-noise nano filter coefficient, G11
	UINT32 reg_nntg_nano_coef_g12           :4;	//11:8	//4K nano-noise nano filter coefficient, G12
	UINT32 resvd0                           :4;
	UINT32 reg_nntg_nano_coef_g20           :4;	//19:16	//4K nano-noise nano filter coefficient, G20
	UINT32 reg_nntg_nano_coef_g21           :4;	//23:20	//4K nano-noise nano filter coefficient, G21
	UINT32 reg_nntg_nano_coef_g22           :4;	//27:24	//4K nano-noise nano filter coefficient, G22
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_NNTG_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3D4 RW
	UINT32 reg_nntg_diff_lut_y0             :8;	//7:0	//4K nano-noise diff LUT point, y0
	UINT32 reg_nntg_diff_lut_x0             :8;	//15:8	//4K nano-noise diff LUT point, x0
	UINT32 reg_nntg_diff_lut_y1             :8;	//23:16	//4K nano-noise diff LUT point, y1
	UINT32 reg_nntg_diff_lut_x1             :8;	//31:24	//4K nano-noise diff LUT point, x1
	};
}PE_E60_SHP_NNTG_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3D8 RW
	UINT32 reg_nntg_diff_lut_y2             :8;	//7:0	//4K nano-noise diff LUT point, y2
	UINT32 reg_nntg_diff_lut_x2             :8;	//15:8	//4K nano-noise diff LUT point, x2
	UINT32 reg_nntg_diff_lut_y3             :8;	//23:16	//4K nano-noise diff LUT point, y3
	UINT32 reg_nntg_diff_lut_x3             :8;	//31:24	//4K nano-noise diff LUT point, x3
	};
}PE_E60_SHP_NNTG_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3DC RW
	UINT32 reg_nntg_edge_lut_y0             :8;	//7:0	//4K nano-noise edge LUT point, y0
	UINT32 reg_nntg_edge_lut_x0             :8;	//15:8	//4K nano-noise edge LUT point, x0
	UINT32 reg_nntg_edge_lut_y1             :8;	//23:16	//4K nano-noise edge LUT point, y1
	UINT32 reg_nntg_edge_lut_x1             :8;	//31:24	//4K nano-noise edge LUT point, x1
	};
}PE_E60_SHP_NNTG_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3E0 RW
	UINT32 reg_nntg_edge_lut_y2             :8;	//7:0	//4K nano-noise edge LUT point, y2
	UINT32 reg_nntg_edge_lut_x2             :8;	//15:8	//4K nano-noise edge LUT point, x2
	UINT32 reg_nntg_edge_lut_y3             :8;	//23:16	//4K nano-noise edge LUT point, y3
	UINT32 reg_nntg_edge_lut_x3             :8;	//31:24	//4K nano-noise edge LUT point, x3
	};
}PE_E60_SHP_NNTG_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3E4 RW
	UINT32 reg_nntg_random_gain             :8;	//7:0	//4K nano-noise random gain
	UINT32 reg_nntg_pattern_gain            :8;	//15:8	//4K nano-noise pattern gain
	UINT32 reg_nntg_local_gain              :8;	//23:16	//4K nano-noise local gain
	UINT32 reg_nntg_denoise_gain            :8;	//31:24	//4K nano-noise denoise gain
	};
}PE_E60_SHP_NNTG_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3E8 RW
	UINT32 reg_nntg_coring_en               :1;	//0:0	//[NNTG]	0: do not apply edge/texture map to peaking filter	1: apply edge/texture map to peaking filter
	UINT32 reg_nntg_coring_mode             :2;	//2:1	//[NNTG]	00: disable edge/texture peaking	01: enable edge peaking only	10: enable texture peaking only	11: enable both edge/texture peaking
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_input_sel        :2;	//5:4	//00 : weight_a, weight_t	01 : a_map, weight_t	10 : weight_a, t_map	11 : a_amp, t_map (default)
	UINT32 resvd1                           :26;
	};
}PE_E60_SHP_NNTG_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3EC RW
	UINT32 reg_nntg_coring_gain_e_b         :7;	//6:0	//edge black gain
	UINT32 resvd0                           :1;
	UINT32 reg_nntg_coring_gain_e_w         :7;	//14:8	//edge white gain
	UINT32 resvd1                           :1;
	UINT32 reg_nntg_coring_gain_t_b         :7;	//22:16	//texture black gain
	UINT32 resvd2                           :1;
	UINT32 reg_nntg_coring_gain_t_w         :7;	//30:24	//texture white gain
	UINT32 resvd3                           :1;
	};
}PE_E60_SHP_NNTG_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3F0 RW
	UINT32 reg_dp_sum_gain                  :8;	//7:0	//DP sum gain
	UINT32 reg_dp_sum_lut_mode              :2;	//9:8	//0: 8bit mode 	1: 9bit mode 	2: 10bit mode (default)
	UINT32 resvd                            :22;
	};
}PE_E60_SHP_DP_SUM_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3F4 RW
	UINT32 reg_dp_sum_lut_y0                :8;	//7:0	//dp_sum LUT for delta control, y0
	UINT32 reg_dp_sum_lut_x0                :8;	//15:8	//dp_sum LUT for delta control, x0
	UINT32 reg_dp_sum_lut_y1                :8;	//23:16	//dp_sum LUT for delta control, y1
	UINT32 reg_dp_sum_lut_x1                :8;	//31:24	//dp_sum LUT for delta control, x1
	};
}PE_E60_SHP_DP_SUM_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3F8 RW
	UINT32 reg_dp_sum_lut_y2                :8;	//7:0	//dp_sum LUT for delta control, y2
	UINT32 reg_dp_sum_lut_x2                :8;	//15:8	//dp_sum LUT for delta control, x2
	UINT32 reg_dp_sum_lut_y3                :8;	//23:16	//dp_sum LUT for delta control, y3
	UINT32 reg_dp_sum_lut_x3                :8;	//31:24	//dp_sum LUT for delta control, x3
	};
}PE_E60_SHP_DP_SUM_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C3FC RW
	UINT32 reg_obj_dct_delta_lut_y0         :8;	//7:0	//object dct LUT for delta control, y0
	UINT32 reg_obj_dct_delta_lut_x0         :8;	//15:8	//object dct LUT for delta control, x0
	UINT32 reg_obj_dct_delta_lut_y1         :8;	//23:16	//object dct LUT for delta control, y1
	UINT32 reg_obj_dct_delta_lut_x1         :8;	//31:24	//object dct LUT for delta control, x1
	};
}PE_E60_SHP_DP_SUM_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C400 RW
	UINT32 reg_obj_dct_delta_lut_y2         :8;	//7:0	//object dct LUT for delta control, y2
	UINT32 reg_obj_dct_delta_lut_x2         :8;	//15:8	//object dct LUT for delta control, x2
	UINT32 reg_obj_dct_delta_lut_y3         :8;	//23:16	//object dct LUT for delta control, y3
	UINT32 reg_obj_dct_delta_lut_x3         :8;	//31:24	//object dct LUT for delta control, x3
	};
}PE_E60_SHP_DP_SUM_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C404 RW
	UINT32 reg_obj_tgen_delta_lut_y0        :8;	//7:0	//object tgen LUT for delta control, y0
	UINT32 reg_obj_tgen_delta_lut_x0        :8;	//15:8	//object tgen LUT for delta control, x0
	UINT32 reg_obj_tgen_delta_lut_y1        :8;	//23:16	//object tgen LUT for delta control, y1
	UINT32 reg_obj_tgen_delta_lut_x1        :8;	//31:24	//object tgen LUT for delta control, x1
	};
}PE_E60_SHP_DP_SUM_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C408 RW
	UINT32 reg_obj_tgen_delta_lut_y2        :8;	//7:0	//object tgen LUT for delta control, y2
	UINT32 reg_obj_tgen_delta_lut_x2        :8;	//15:8	//object tgen LUT for delta control, x2
	UINT32 reg_obj_tgen_delta_lut_y3        :8;	//23:16	//object tgen LUT for delta control, y3
	UINT32 reg_obj_tgen_delta_lut_x3        :8;	//31:24	//object tgen LUT for delta control, x3
	};
}PE_E60_SHP_DP_SUM_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C40C RW
	UINT32 reg_obj_lc_delta_lut_y0          :8;	//7:0	//object local contrast LUT for delta control, y0
	UINT32 reg_obj_lc_delta_lut_x0          :8;	//15:8	//object local contrast LUT for delta control, x0
	UINT32 reg_obj_lc_delta_lut_y1          :8;	//23:16	//object local contrast LUT for delta control, y1
	UINT32 reg_obj_lc_delta_lut_x1          :8;	//31:24	//object local contrast LUT for delta control, x1
	};
}PE_E60_SHP_DP_SUM_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C410 RW
	UINT32 reg_obj_lc_delta_lut_y2          :8;	//7:0	//object local contrast LUT for delta control, y2
	UINT32 reg_obj_lc_delta_lut_x2          :8;	//15:8	//object local contrast LUT for delta control, x2
	UINT32 reg_obj_lc_delta_lut_y3          :8;	//23:16	//object local contrast LUT for delta control, y3
	UINT32 reg_obj_lc_delta_lut_x3          :8;	//31:24	//object local contrast LUT for delta control, x3
	};
}PE_E60_SHP_DP_SUM_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C420 RW
	UINT32 reg_psp_obj_en                   :1;	//0:0	//PSP object contrast enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_PSP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C430 RW
	UINT32 reg_core0_core0win_dp_win0_en    :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_core0win_dp_win1_en    :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_core0win_dp_win01_en   :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_core0win_dp_win_outside :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_core0win_dp_win_en     :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_core0win_dp_bdr_alpha  :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_core0win_dp_bdr_wid    :2;	//14:13	//border width
	UINT32 reg_core0_core0win_dp_bdr_en     :1;	//15:15	//border enable
	UINT32 reg_core0_core0win_dp_cr5        :5;	//20:16	//border color: cr5
	UINT32 reg_core0_core0win_dp_cb5        :5;	//25:21	//border color: cb5
	UINT32 reg_core0_core0win_dp_yy6        :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C434 RW
	UINT32 reg_core0_core0win_dp_win_w0_x0  :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_core0win_dp_win_w0_y0  :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE0_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C438 RW
	UINT32 reg_core0_core0win_dp_win_w0_x1  :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_core0win_dp_win_w0_y1  :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE0_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C43C RW
	UINT32 reg_core0_core0win_dp_win_w1_x0  :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_core0win_dp_win_w1_y0  :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE0_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C440 RW
	UINT32 reg_core0_win_dp_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_dp_win_w1_y1       :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE0_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C444 RW
	UINT32 reg_core1_core1win_dp_win0_en    :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_core1win_dp_win1_en    :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_core1win_dp_win01_en   :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_core1win_dp_win_outside :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_core1win_dp_win_en     :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_core1win_dp_bdr_alpha  :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_core1win_dp_bdr_wid    :2;	//14:13	//border width
	UINT32 reg_core1_core1win_dp_bdr_en     :1;	//15:15	//border enable
	UINT32 reg_core1_core1win_dp_cr5        :5;	//20:16	//border color: cr5
	UINT32 reg_core1_core1win_dp_cb5        :5;	//25:21	//border color: cb5
	UINT32 reg_core1_core1win_dp_yy6        :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_DP_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C448 RW
	UINT32 reg_core1_core1win_dp_win_w0_x0  :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_core1win_dp_win_w0_y0  :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE1_DP_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C44C RW
	UINT32 reg_core1_core1win_dp_win_w0_x1  :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_core1win_dp_win_w0_y1  :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE1_DP_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C450 RW
	UINT32 reg_core1_core1win_dp_win_w1_x0  :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_core1win_dp_win_w1_y0  :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE1_DP_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C454 RW
	UINT32 reg_core1_win_dp_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_dp_win_w1_y1       :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE1_DP_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C460 RW
	UINT32 reg_region_text_en               :1;	//0:0	//region texture enable
	UINT32 resvd0                           :3;
	UINT32 reg_region_text_cutres           :3;	//6:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_region_text_add_offset       :8;	//15:8	//
	UINT32 reg_region_text_add_max          :8;	//23:16	//
	UINT32 reg_region_text_cuthif           :3;	//26:24	//
	UINT32 resvd2                           :5;
	};
}PE_E60_SHP_FD_REGION_TEXT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C464 RW
	UINT32 reg_region_text_lut_y0           :8;	//7:0	//region texture LUT , y0
	UINT32 reg_region_text_lut_x0           :8;	//15:8	//region texture LUT , x0
	UINT32 reg_region_text_lut_y1           :8;	//23:16	//region texture LUT , y1
	UINT32 reg_region_text_lut_x1           :8;	//31:24	//region texture LUT , x1
	};
}PE_E60_SHP_FD_REGION_TEXT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C468 RW
	UINT32 reg_region_text_lut_y2           :8;	//7:0	//region texture LUT , y2
	UINT32 reg_region_text_lut_x2           :8;	//15:8	//region texture LUT , x2
	UINT32 reg_region_text_lut_y3           :8;	//23:16	//region texture LUT , y3
	UINT32 reg_region_text_lut_x3           :8;	//31:24	//region texture LUT , x3
	};
}PE_E60_SHP_FD_REGION_TEXT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C46C RW
	UINT32 reg_tmap_temp_iir_en             :1;	//0:0	//TMAP temporal process enable
	UINT32 resvd0                           :3;
	UINT32 reg_tmap_temp_init_en            :1;	//4:4	//TMAP temporal process initial value setting enable
	UINT32 resvd1                           :3;
	UINT32 reg_tmap_temp_init_val           :8;	//15:8	//TMAP temporal process initial value
	UINT32 resvd2                           :8;
	UINT32 reg_tmap_stat_sel                :1;	//24:24	//TMAP temporal process status selection	0 : original tmap status	1 : iir tmap status
	UINT32 resvd3                           :7;
	};
}PE_E60_SHP_FD_TMAP_TEMP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C470 RW
	UINT32 reg_tmap_temp_prev_lut_y0        :8;	//7:0	//tmap temporal previous blend LUT , y0
	UINT32 reg_tmap_temp_prev_lut_x0        :8;	//15:8	//tmap temporal previous blend LUT , x0
	UINT32 reg_tmap_temp_prev_lut_y1        :8;	//23:16	//tmap temporal previous blend LUT , y1
	UINT32 reg_tmap_temp_prev_lut_x1        :8;	//31:24	//tmap temporal previous blend LUT , x1
	};
}PE_E60_SHP_FD_TMAP_TEMP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C474 RW
	UINT32 reg_tmap_temp_prev_lut_y2        :8;	//7:0	//tmap temporal previous blend LUT , y2
	UINT32 reg_tmap_temp_prev_lut_x2        :8;	//15:8	//tmap temporal previous blend LUT , x2
	UINT32 reg_tmap_temp_prev_lut_y3        :8;	//23:16	//tmap temporal previous blend LUT , y3
	UINT32 reg_tmap_temp_prev_lut_x3        :8;	//31:24	//tmap temporal previous blend LUT , x3
	};
}PE_E60_SHP_FD_TMAP_TEMP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C478 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y0     :8;	//7:0	//tmap temporal iir positive LUT , y0
	UINT32 reg_tmap_temp_iir_pos_lut_x0     :8;	//15:8	//tmap temporal iir positive LUT , x0
	UINT32 reg_tmap_temp_iir_pos_lut_y1     :8;	//23:16	//tmap temporal iir positive LUT , y1
	UINT32 reg_tmap_temp_iir_pos_lut_x1     :8;	//31:24	//tmap temporal iir positive LUT , x1
	};
}PE_E60_SHP_FD_TMAP_TEMP_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C47C RW
	UINT32 reg_tmap_temp_iir_pos_lut_y2     :8;	//7:0	//tmap temporal iir positive LUT , y2
	UINT32 reg_tmap_temp_iir_pos_lut_x2     :8;	//15:8	//tmap temporal iir positive LUT , x2
	UINT32 reg_tmap_temp_iir_pos_lut_y3     :8;	//23:16	//tmap temporal iir positive LUT , y3
	UINT32 reg_tmap_temp_iir_pos_lut_x3     :8;	//31:24	//tmap temporal iir positive LUT , x3
	};
}PE_E60_SHP_FD_TMAP_TEMP_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C480 RW
	UINT32 reg_tmap_temp_iir_pos_lut_y4     :8;	//7:0	//tmap temporal iir positive LUT , y4
	UINT32 reg_tmap_temp_iir_pos_lut_x4     :8;	//15:8	//tmap temporal iir positive LUT , x4
	UINT32 reg_tmap_temp_iir_pos_lut_y5     :8;	//23:16	//tmap temporal iir positive LUT , y5
	UINT32 reg_tmap_temp_iir_pos_lut_x5     :8;	//31:24	//tmap temporal iir positive LUT , x5
	};
}PE_E60_SHP_FD_TMAP_TEMP_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C484 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y0     :8;	//7:0	//tmap temporal iir negative LUT , y0
	UINT32 reg_tmap_temp_iir_neg_lut_x0     :8;	//15:8	//tmap temporal iir negative LUT , x0
	UINT32 reg_tmap_temp_iir_neg_lut_y1     :8;	//23:16	//tmap temporal iir negative LUT , y1
	UINT32 reg_tmap_temp_iir_neg_lut_x1     :8;	//31:24	//tmap temporal iir negative LUT , x1
	};
}PE_E60_SHP_FD_TMAP_TEMP_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C488 RW
	UINT32 reg_tmap_temp_iir_neg_lut_y2     :8;	//7:0	//tmap temporal iir negative LUT , y2
	UINT32 reg_tmap_temp_iir_neg_lut_x2     :8;	//15:8	//tmap temporal iir negative LUT , x2
	UINT32 reg_tmap_temp_iir_neg_lut_y3     :8;	//23:16	//tmap temporal iir negative LUT , y3
	UINT32 reg_tmap_temp_iir_neg_lut_x3     :8;	//31:24	//tmap temporal iir negative LUT , x3
	};
}PE_E60_SHP_FD_TMAP_TEMP_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C48C RW
	UINT32 reg_tmap_temp_iir_neg_lut_y4     :8;	//7:0	//tmap temporal iir negative LUT , y4
	UINT32 reg_tmap_temp_iir_neg_lut_x4     :8;	//15:8	//tmap temporal iir negative LUT , x4
	UINT32 reg_tmap_temp_iir_neg_lut_y5     :8;	//23:16	//tmap temporal iir negative LUT , y5
	UINT32 reg_tmap_temp_iir_neg_lut_x5     :8;	//31:24	//tmap temporal iir negative LUT , x5
	};
}PE_E60_SHP_FD_TMAP_TEMP_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C490 RW
	UINT32 reg_tmap_stat_win0_start_x       :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_start_y       :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_FD_TMAP_TEMP_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C494 RW
	UINT32 reg_tmap_stat_win0_end_x         :12;	//11:0	//tmap temporal texture status window position (window0)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win0_end_y         :12;	//27:16	//tmap temporal texture status window position (window0)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_FD_TMAP_TEMP_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C498 RW
	UINT32 reg_tmap_stat_win1_start_x       :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_start_y       :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_FD_TMAP_TEMP_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C49C RW
	UINT32 reg_tmap_stat_win1_end_x         :12;	//11:0	//tmap temporal texture status window position (window1)
	UINT32 resvd0                           :4;
	UINT32 reg_tmap_stat_win1_end_y         :12;	//27:16	//tmap temporal texture status window position (window1)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_FD_TMAP_TEMP_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4A0 RW
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
}PE_E60_SHP_DJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4A4 RW
	UINT32 reg_dj_level_th                  :8;	//7:0	//g0: level threshold
	UINT32 resvd0                           :8;
	UINT32 reg_dj_n_avg_gain                :8;	//23:16	//neighborhood pixel averaing : gain
	UINT32 resvd1                           :8;
	};
}PE_E60_SHP_DJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4A8 RW
	UINT32 reg_dj_g0_cnt_min                :5;	//4:0	//g0: edf_count_min
	UINT32 resvd0                           :3;
	UINT32 reg_dj_g0_mul                    :5;	//12:8	//g0: n x ( Count - min_cnt_th )
	UINT32 resvd1                           :19;
	};
}PE_E60_SHP_DJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4AC RW
	UINT32 reg_dj_g1_protect_min            :8;	//7:0	//g1: Min diff th - LR Diff
	UINT32 reg_dj_g1_mul                    :7;	//14:8	//g1: n x ( th - LR_Diff )
	UINT32 resvd                            :1;
	UINT32 reg_dj_edge_min                  :8;	//23:16	//edge adaptive filter min value
	UINT32 reg_dj_edge_mul                  :8;	//31:24	//edge adaptive filter multiplication value
	};
}PE_E60_SHP_DJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4B0 RW
	UINT32 reg_dj_dir_sel_c1                :1;	//0:0	//DJ core directional sel, 1
	UINT32 reg_dj_dir_sel_c2                :1;	//1:1	//DJ core directional sel, 2
	UINT32 reg_dj_dir_sel_c3                :1;	//2:2	//DJ core directional sel, 3
	UINT32 reg_dj_dir_sel_c4                :1;	//3:3	//DJ core directional sel, 4
	UINT32 resvd                            :28;
	};
}PE_E60_SHP_DJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4B4 RW
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
}PE_E60_SHP_DJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4B8 RW
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
}PE_E60_SHP_DJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4BC RW
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
}PE_E60_SHP_DJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4C0 RW
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
}PE_E60_SHP_DJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4C4 RW
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
}PE_E60_SHP_DJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4C8 RW
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
}PE_E60_SHP_DJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4CC RW
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
}PE_E60_SHP_DJ_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4D0 RW
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
}PE_E60_SHP_DJ_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4D4 RW
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
}PE_E60_SHP_DJ_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4D8 RW
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
}PE_E60_SHP_DJ_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4DC RW
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
}PE_E60_SHP_DJ_CTRL_0F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4E0 RW
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
}PE_E60_SHP_DJ_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4E4 RW
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
}PE_E60_SHP_DJ_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4E8 RW
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
}PE_E60_SHP_DJ_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4EC RW
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
}PE_E60_SHP_DJ_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4F0 RW
	UINT32 reg_dj_pattern1_flip0_h          :1;	//0:0	//DJ protect pattern1 flip0, H
	UINT32 reg_dj_pattern1_flip0_v          :1;	//1:1	//DJ protect pattern1 flip0, V
	UINT32 reg_dj_pattern1_flip1_h          :1;	//2:2	//DJ protect pattern1 flip1, H
	UINT32 reg_dj_pattern1_flip1_v          :1;	//3:3	//DJ protect pattern1 flip1, V
	UINT32 resvd                            :28;
	};
}PE_E60_SHP_DJ_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4F4 RW
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
}PE_E60_SHP_DJ_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4F8 RW
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
}PE_E60_SHP_DJ_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C4FC RW
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
}PE_E60_SHP_DJ_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C500 RW
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
}PE_E60_SHP_DJ_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C504 RW
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
}PE_E60_SHP_DJ_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C508 RW
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
}PE_E60_SHP_DJ_CTRL_1A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C50C RW
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
}PE_E60_SHP_DJ_CTRL_1B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C510 RW
	UINT32 reg_dj_pattern2_flip0_h          :1;	//0:0	//DJ protect pattern2 flip0, H
	UINT32 reg_dj_pattern2_flip0_v          :1;	//1:1	//DJ protect pattern2 flip0, V
	UINT32 reg_dj_pattern2_flip1_h          :1;	//2:2	//DJ protect pattern2 flip1, H
	UINT32 reg_dj_pattern2_flip1_v          :1;	//3:3	//DJ protect pattern2 flip1, V
	UINT32 resvd                            :28;
	};
}PE_E60_SHP_DJ_CTRL_1C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C514 RW
	UINT32 reg_dj_soft_g0_mul               :6;	//5:0	//Soft DJ G0 (matchness gain) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g0_offset            :5;	//12:8	//Soft DJ G0 (matchness gain) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g0_max               :8;	//23:16	//Soft DJ G0 (matchness gain) max
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_DJ_CTRL_1D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C518 RW
	UINT32 reg_dj_soft_g1_mul               :6;	//5:0	//Soft DJ G1 (anti-dir) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g1_offset            :5;	//12:8	//Soft DJ G1 (anti-dir) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g1_max               :8;	//23:16	//Soft DJ G1 (anti-dir) max
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_DJ_CTRL_1E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C51C RW
	UINT32 reg_dj_soft_g2_mul               :6;	//5:0	//Soft DJ G2 (L protection) mul
	UINT32 resvd0                           :2;
	UINT32 reg_dj_soft_g2_offset            :5;	//12:8	//Soft DJ G2 (L protection) offset
	UINT32 resvd1                           :3;
	UINT32 reg_dj_soft_g2_max               :8;	//23:16	//Soft DJ G2 (L protection) max
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_DJ_CTRL_1F_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C520 RW
	UINT32 reg_dj_soft_base                 :8;	//7:0	//Soft DJ base
	UINT32 reg_dj_soft_sel_1357_gain        :8;	//15:8	//Soft DJ 1357 gain penalty
	UINT32 reg_dj_soft_single_match_en      :1;	//16:16	//Soft DJ single match check enable
	UINT32 resvd                            :15;
	};
}PE_E60_SHP_DJ_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C524 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_DB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C528 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_DB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C530 RW
	UINT32 reg_core0_win_dj_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_dj_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_dj_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_dj_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_dj_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_dj_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_dj_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_core0_win_dj_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_core0_win_dj_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_dj_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_dj_yy6             :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C534 RW
	UINT32 reg_core0_win_dj_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_dj_win_w0_y0       :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE0_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C538 RW
	UINT32 reg_core0_win_dj_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_dj_win_w0_y1       :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE0_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C53C RW
	UINT32 reg_core0_win_dj_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_dj_win_w1_y0       :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE0_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C540 RW
	UINT32 reg_core0_win_dj_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_dj_win_w1_y1       :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE0_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C544 RW
	UINT32 reg_core1_win_dj_win0_en         :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_dj_win1_en         :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_dj_win01_en        :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_dj_win_outside     :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_dj_win_en          :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_dj_bdr_alpha       :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_dj_bdr_wid         :2;	//14:13	//border width
	UINT32 reg_core1_win_dj_bdr_en          :1;	//15:15	//border enable
	UINT32 reg_core1_win_dj_cr5             :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_dj_cb5             :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_dj_yy6             :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_DJ_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C548 RW
	UINT32 reg_core1_win_dj_win_w0_x0       :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_dj_win_w0_y0       :16;	//27:16	//win_w0_y0
	};
}PE_E60_SHP_CORE1_DJ_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C54C RW
	UINT32 reg_core1_win_dj_win_w0_x1       :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_dj_win_w0_y1       :16;	//27:16	//win_w0_y1
	};
}PE_E60_SHP_CORE1_DJ_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C550 RW
	UINT32 reg_core1_win_dj_win_w1_x0       :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_dj_win_w1_y0       :16;	//27:16	//win_w1_y0
	};
}PE_E60_SHP_CORE1_DJ_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C554 RW
	UINT32 reg_core1_win_dj_win_w1_x1       :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_dj_win_w1_y1       :16;	//27:16	//win_w1_y1
	};
}PE_E60_SHP_CORE1_DJ_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C560 RW
	UINT32 reg_color_region_en              :1;	//0:0	//color region processing enable
	UINT32 reg_color_region_debug_en        :1;	//1:1	//color region debug map enable
	UINT32 resvd0                           :2;
	UINT32 reg_chr_protection_en            :1;	//4:4	//chroma protection enable
	UINT32 resvd1                           :3;
	UINT32 reg_chr_compensation_en          :1;	//8:8	//chroma compensation enable
	UINT32 resvd2                           :23;
	};
}PE_E60_SHP_CHROMA_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C564 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CHROMA_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C568 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CHROMA_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C56C RW
	UINT32 reg_chr_gain_r0_cb_y0            :8;	//7:0	//chroma gain LUT, R0, Cb, y0
	UINT32 reg_chr_gain_r0_cb_x0            :8;	//15:8	//chroma gain LUT, R0, Cb, x0
	UINT32 reg_chr_gain_r0_cb_y1            :8;	//23:16	//chroma gain LUT, R0, Cb, y1
	UINT32 reg_chr_gain_r0_cb_x1            :8;	//31:24	//chroma gain LUT, R0, Cb, x1
	};
}PE_E60_SHP_CHROMA_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C570 RW
	UINT32 reg_chr_gain_r0_cb_y2            :8;	//7:0	//chroma gain LUT, R0, Cb, y2
	UINT32 reg_chr_gain_r0_cb_x2            :8;	//15:8	//chroma gain LUT, R0, Cb, x2
	UINT32 reg_chr_gain_r0_cb_y3            :8;	//23:16	//chroma gain LUT, R0, Cb, y3
	UINT32 reg_chr_gain_r0_cb_x3            :8;	//31:24	//chroma gain LUT, R0, Cb, x3
	};
}PE_E60_SHP_CHROMA_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C574 RW
	UINT32 reg_chr_gain_r0_cr_y0            :8;	//7:0	//chroma gain LUT, R0, Cr, y0
	UINT32 reg_chr_gain_r0_cr_x0            :8;	//15:8	//chroma gain LUT, R0, Cr, x0
	UINT32 reg_chr_gain_r0_cr_y1            :8;	//23:16	//chroma gain LUT, R0, Cr, y1
	UINT32 reg_chr_gain_r0_cr_x1            :8;	//31:24	//chroma gain LUT, R0, Cr, x1
	};
}PE_E60_SHP_CHROMA_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C578 RW
	UINT32 reg_chr_gain_r0_cr_y2            :8;	//7:0	//chroma gain LUT, R0, Cr, y2
	UINT32 reg_chr_gain_r0_cr_x2            :8;	//15:8	//chroma gain LUT, R0, Cr, x2
	UINT32 reg_chr_gain_r0_cr_y3            :8;	//23:16	//chroma gain LUT, R0, Cr, y3
	UINT32 reg_chr_gain_r0_cr_x3            :8;	//31:24	//chroma gain LUT, R0, Cr, x3
	};
}PE_E60_SHP_CHROMA_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C57C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CHROMA_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C580 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CHROMA_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C584 RW
	UINT32 reg_chr_gain_r1_cb_y0            :8;	//7:0	//chroma gain LUT, R1, Cb, y0
	UINT32 reg_chr_gain_r1_cb_x0            :8;	//15:8	//chroma gain LUT, R1, Cb, x0
	UINT32 reg_chr_gain_r1_cb_y1            :8;	//23:16	//chroma gain LUT, R1, Cb, y1
	UINT32 reg_chr_gain_r1_cb_x1            :8;	//31:24	//chroma gain LUT, R1, Cb, x1
	};
}PE_E60_SHP_CHROMA_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C588 RW
	UINT32 reg_chr_gain_r1_cb_y2            :8;	//7:0	//chroma gain LUT, R1, Cb, y2
	UINT32 reg_chr_gain_r1_cb_x2            :8;	//15:8	//chroma gain LUT, R1, Cb, x2
	UINT32 reg_chr_gain_r1_cb_y3            :8;	//23:16	//chroma gain LUT, R1, Cb, y3
	UINT32 reg_chr_gain_r1_cb_x3            :8;	//31:24	//chroma gain LUT, R1, Cb, x3
	};
}PE_E60_SHP_CHROMA_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C58C RW
	UINT32 reg_chr_gain_r1_cr_y0            :8;	//7:0	//chroma gain LUT, R1, Cr, y0
	UINT32 reg_chr_gain_r1_cr_x0            :8;	//15:8	//chroma gain LUT, R1, Cr, x0
	UINT32 reg_chr_gain_r1_cr_y1            :8;	//23:16	//chroma gain LUT, R1, Cr, y1
	UINT32 reg_chr_gain_r1_cr_x1            :8;	//31:24	//chroma gain LUT, R1, Cr, x1
	};
}PE_E60_SHP_CHROMA_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C590 RW
	UINT32 reg_chr_gain_r1_cr_y2            :8;	//7:0	//chroma gain LUT, R1, Cr, y2
	UINT32 reg_chr_gain_r1_cr_x2            :8;	//15:8	//chroma gain LUT, R1, Cr, x2
	UINT32 reg_chr_gain_r1_cr_y3            :8;	//23:16	//chroma gain LUT, R1, Cr, y3
	UINT32 reg_chr_gain_r1_cr_x3            :8;	//31:24	//chroma gain LUT, R1, Cr, x3
	};
}PE_E60_SHP_CHROMA_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C594 RW
	UINT32 reg_chr_gain_r0_gain             :8;	//7:0	//chroma gain alpha, R0
	UINT32 resvd0                           :8;
	UINT32 reg_chr_gain_r1_gain             :8;	//23:16	//chroma gain alpha, R1
	UINT32 reg_chr_gain_sel                 :1;	//24:24	//0: {3'd0,region_gain}	1: {region_gain,3'd0}
	UINT32 resvd1                           :7;
	};
}PE_E60_SHP_CHROMA_CTRL_0D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C598 RW
	UINT32 reg_chr_comp_y0                  :8;	//7:0	//chroma comp. linear mapping, y0
	UINT32 reg_chr_comp_x0                  :8;	//15:8	//chroma comp. linear mapping, x0
	UINT32 reg_chr_comp_y1                  :8;	//23:16	//chroma comp. linear mapping, y1
	UINT32 reg_chr_comp_x1                  :8;	//31:24	//chroma comp. linear mapping, x1
	};
}PE_E60_SHP_CHROMA_CTRL_0E_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5A0 RW
	UINT32 reg_cti_en                       :1;	//0:0	//cti enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_filter_tap_size          :3;	//6:4	//000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_gain                     :8;	//15:8	//gain (3.5u)
	UINT32 resvd2                           :16;
	};
}PE_E60_SHP_CTI_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5A4 RW
	UINT32 reg_cti_coring_th0               :8;	//7:0	//coring th0
	UINT32 reg_cti_coring_th1               :8;	//15:8	//coring_th1
	UINT32 reg_cti_coring_map_filter        :3;	//18:16	//000: no filtering	001: 5-tap filtering	010: 7-tap filtering	011: 9-tap filtering	100: 11-tap filtering	101: 13-tap filtering
	UINT32 resvd0                           :1;
	UINT32 reg_cti_coring_tap_size          :3;	//22:20	//000: 21 tap	001: 19 tap	010: 17 tap	011: 15 tap	100: 13 tap	101: 11 tap	110:  9 tap
	UINT32 resvd1                           :1;
	UINT32 reg_cti_debug_mode               :2;	//25:24	//00: normal display	10: coring_map(cb)	11: coring_map(cr)
	UINT32 resvd2                           :6;
	};
}PE_E60_SHP_CTI_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5A8 RW
	UINT32 reg_cti_ycm_en                   :1;	//0:0	//y/c merge enable
	UINT32 resvd0                           :3;
	UINT32 reg_cti_ycm_band_sel             :3;	//6:4	//y/c merge band sel
	UINT32 resvd1                           :1;
	UINT32 reg_cti_ycm_diff_th              :8;	//15:8	//y/c merge diff threshold
	UINT32 reg_cti_ycm_y_gain               :4;	//19:16	//y/c merge gain, Y
	UINT32 reg_cti_ycm_c_gain               :4;	//23:20	//y/c merge gain, C
	UINT32 resvd2                           :8;
	};
}PE_E60_SHP_CTI_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5B0 RW
	UINT32 reg_flick_en                     :1;	//0:0	//frc flicker blur enable
	UINT32 resvd0                           :3;
	UINT32 reg_flick_motion_sel             :2;	//5:4	//SHP FRC flicker blur motion map position	422 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+7][x]	1: blur: motion_map[y-3][x] / core: motion_map[y+4][x]	2: blur: motion_map[y-7][x] / core: motion_map[y  ][x]	444 mode	0: blur: motion_map[y  ][x] / core: motion_map[y+4][x]	1: blur: motion_map[y-2][x] / core: motion_map[y+2][x]	2: blur: motion_map[y-4][x] / core: motion_map[y  ][x]
	UINT32 resvd1                           :2;
	UINT32 reg_flick_blur_type              :2;	//9:8	//frc flicker blur pel selection	0: cur pel[y][x+1]	1: cur pel[y][x-1]	2: average
	UINT32 resvd2                           :22;
	};
}PE_E60_SHP_FRC_FLICK_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5B4 RW
	UINT32 reg_flick_motion_lut_y0          :8;	//7:0	//frc flicker blur motion LUT point, y0
	UINT32 reg_flick_motion_lut_x0          :8;	//15:8	//frc flicker blur motion LUT point, x0
	UINT32 reg_flick_motion_lut_y1          :8;	//23:16	//frc flicker blur motion LUT point, y1
	UINT32 reg_flick_motion_lut_x1          :8;	//31:24	//frc flicker blur motion LUT point, x1
	};
}PE_E60_SHP_FRC_FLICK_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5B8 RW
	UINT32 reg_flick_motion_lut_y2          :8;	//7:0	//frcflicker blur motion LUT point, y2
	UINT32 reg_flick_motion_lut_x2          :8;	//15:8	//frc flicker blur motion LUT point, x2
	UINT32 reg_flick_motion_lut_y3          :8;	//23:16	//frc flicker blur motion LUT point, y3
	UINT32 reg_flick_motion_lut_x3          :8;	//31:24	//frc flicker blur motion LUT point, x3
	};
}PE_E60_SHP_FRC_FLICK_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5BC RW
	UINT32 reg_flick_master_gain            :8;	//7:0	//frc flicker blur master gain
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_FRC_FLICK_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5C0 RW
	UINT32 reg_frc_blur_en                  :1;	//0:0	//frc blur enable
	UINT32 reg_frc_blur_debug_en            :1;	//1:1	//frc blur debug en
	UINT32 resvd                            :30;
	};
}PE_E60_SHP_FRC_BLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5C4 RW
	UINT32 reg_frc_blur_cnt_th0             :6;	//5:0	//frc blur weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th1             :6;	//13:8	//frc blur weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th2             :6;	//21:16	//frc blur weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th3             :6;	//29:24	//frc blur weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_E60_SHP_FRC_BLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5C8 RW
	UINT32 reg_frc_blur_cnt_th4             :6;	//5:0	//frc blur weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_blur_cnt_th5             :6;	//13:8	//frc blur weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_blur_cnt_th6             :6;	//21:16	//frc blur weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_blur_cnt_th7             :6;	//29:24	//frc blur weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_E60_SHP_FRC_BLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5CC RW
	UINT32 reg_frc_blur_val0                :4;	//3:0	//frc blur weight smoothing count value, 0
	UINT32 reg_frc_blur_val1                :4;	//7:4	//frc blur weight smoothing count value, 1
	UINT32 reg_frc_blur_val2                :4;	//11:8	//frc blur weight smoothing count value, 2
	UINT32 reg_frc_blur_val3                :4;	//15:12	//frc blur weight smoothing count value, 3
	UINT32 reg_frc_blur_val4                :4;	//19:16	//frc blur weight smoothing count value, 4
	UINT32 reg_frc_blur_val5                :4;	//23:20	//frc blur weight smoothing count value, 5
	UINT32 reg_frc_blur_val6                :4;	//27:24	//frc blur weight smoothing count value, 6
	UINT32 reg_frc_blur_val7                :4;	//31:28	//frc blur weight smoothing count value, 7
	};
}PE_E60_SHP_FRC_BLUR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5D0 RW
	UINT32 reg_frc_blur_coef_x8             :4;	//3:0	//frc blur filter coeff, x, [8]
	UINT32 resvd                            :28;
	};
}PE_E60_SHP_FRC_BLUR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5D4 RW
	UINT32 reg_frc_blur_coef_x0             :4;	//3:0	//frc blur filter coeff, x, [0]/[16]
	UINT32 reg_frc_blur_coef_x1             :4;	//7:4	//frc blur filter coeff, x, [1]/[15]
	UINT32 reg_frc_blur_coef_x2             :4;	//11:8	//frc blur filter coeff, x, [2]/[14]
	UINT32 reg_frc_blur_coef_x3             :4;	//15:12	//frc blur filter coeff, x, [3]/[13]
	UINT32 reg_frc_blur_coef_x4             :4;	//19:16	//frc blur filter coeff, x, [4]/[12]
	UINT32 reg_frc_blur_coef_x5             :4;	//23:20	//frc blur filter coeff, x, [5]/[11]
	UINT32 reg_frc_blur_coef_x6             :4;	//27:24	//frc blur filter coeff, x, [6]/[10]
	UINT32 reg_frc_blur_coef_x7             :4;	//31:28	//frc blur filter coeff, x, [7]/[9]
	};
}PE_E60_SHP_FRC_BLUR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5D8 RW
	UINT32 reg_frc_blur_coef_y0             :4;	//3:0	//frc blur filter coeff, y, [0]/[4]
	UINT32 reg_frc_blur_coef_y1             :4;	//7:4	//frc blur filter coeff, y, [1]/[3]
	UINT32 reg_frc_blur_coef_y2             :4;	//11:8	//frc blur filter coeff, y, [2]
	UINT32 resvd                            :20;
	};
}PE_E60_SHP_FRC_BLUR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5E0 RW
	UINT32 reg_frc_halo_en                  :1;	//0:0	//frc halo enable
	UINT32 reg_frc_halo_debug_en            :1;	//1:1	//frc halo debug en
	UINT32 resvd                            :30;
	};
}PE_E60_SHP_FRC_HALO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5E4 RW
	UINT32 reg_frc_halo_cnt_th0             :6;	//5:0	//frc halo weight smoothing count threshold, 0
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th1             :6;	//13:8	//frc halo weight smoothing count threshold, 1
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th2             :6;	//21:16	//frc halo weight smoothing count threshold, 2
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th3             :6;	//29:24	//frc halo weight smoothing count threshold, 3
	UINT32 resvd3                           :2;
	};
}PE_E60_SHP_FRC_HALO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5E8 RW
	UINT32 reg_frc_halo_cnt_th4             :6;	//5:0	//frc halo weight smoothing count threshold, 4
	UINT32 resvd0                           :2;
	UINT32 reg_frc_halo_cnt_th5             :6;	//13:8	//frc halo weight smoothing count threshold, 5
	UINT32 resvd1                           :2;
	UINT32 reg_frc_halo_cnt_th6             :6;	//21:16	//frc halo weight smoothing count threshold, 6
	UINT32 resvd2                           :2;
	UINT32 reg_frc_halo_cnt_th7             :6;	//29:24	//frc halo weight smoothing count threshold, 7
	UINT32 resvd3                           :2;
	};
}PE_E60_SHP_FRC_HALO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5EC RW
	UINT32 reg_frc_halo_val0                :4;	//3:0	//frc halo weight smoothing count value, 0
	UINT32 reg_frc_halo_val1                :4;	//7:4	//frc halo weight smoothing count value, 1
	UINT32 reg_frc_halo_val2                :4;	//11:8	//frc halo weight smoothing count value, 2
	UINT32 reg_frc_halo_val3                :4;	//15:12	//frc halo weight smoothing count value, 3
	UINT32 reg_frc_halo_val4                :4;	//19:16	//frc halo weight smoothing count value, 4
	UINT32 reg_frc_halo_val5                :4;	//23:20	//frc halo weight smoothing count value, 5
	UINT32 reg_frc_halo_val6                :4;	//27:24	//frc halo weight smoothing count value, 6
	UINT32 reg_frc_halo_val7                :4;	//31:28	//frc halo weight smoothing count value, 7
	};
}PE_E60_SHP_FRC_HALO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5F0 RW
	UINT32 reg_core0_win_frc_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_frc_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_frc_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_frc_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_frc_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_frc_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_frc_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core0_win_frc_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core0_win_frc_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_frc_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_frc_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5F4 RW
	UINT32 reg_core0_win_frc_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_frc_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5F8 RW
	UINT32 reg_core0_win_frc_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_frc_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C5FC RW
	UINT32 reg_core0_win_frc_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_frc_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C600 RW
	UINT32 reg_core0_win_frc_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_frc_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C604 RW
	UINT32 reg_core1_win_frc_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_frc_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_frc_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_frc_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_frc_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_frc_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_frc_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core1_win_frc_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core1_win_frc_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_frc_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_frc_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_FRC_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C608 RW
	UINT32 reg_core1_win_frc_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_frc_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FRC_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C60C RW
	UINT32 reg_core1_win_frc_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_frc_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FRC_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C610 RW
	UINT32 reg_core1_win_frc_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_frc_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FRC_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C614 RW
	UINT32 reg_core1_win_frc_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_frc_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FRC_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C620 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C624 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C628 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C62C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C630 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C634 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C638 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C63C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C640 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C644 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C648 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C64C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C650 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_CTRL_0C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C660 RW
	UINT32 reg_motion_prot_adaptive_en      :1;	//0:0	//motion protection enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_MOTION_PROT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C664 RW
	UINT32 reg_motion_prot_lut_a_y0         :8;	//7:0	//motion gain LUT, A, y0
	UINT32 reg_motion_prot_lut_a_x0         :8;	//15:8	//motion gain LUT, A, x0
	UINT32 reg_motion_prot_lut_a_y1         :8;	//23:16	//motion gain LUT, A, y1
	UINT32 reg_motion_prot_lut_a_x1         :8;	//31:24	//motion gain LUT, A, x1
	};
}PE_E60_SHP_MOTION_PROT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C668 RW
	UINT32 reg_motion_prot_lut_a_y2         :8;	//7:0	//motion gain LUT, A, y2
	UINT32 reg_motion_prot_lut_a_x2         :8;	//15:8	//motion gain LUT, A, x2
	UINT32 reg_motion_prot_lut_a_y3         :8;	//23:16	//motion gain LUT, A, y3
	UINT32 reg_motion_prot_lut_a_x3         :8;	//31:24	//motion gain LUT, A, x3
	};
}PE_E60_SHP_MOTION_PROT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C66C RW
	UINT32 reg_motion_prot_lut_t_y0         :8;	//7:0	//motion gain LUT, T, y0
	UINT32 reg_motion_prot_lut_t_x0         :8;	//15:8	//motion gain LUT, T, x0
	UINT32 reg_motion_prot_lut_t_y1         :8;	//23:16	//motion gain LUT, T, y1
	UINT32 reg_motion_prot_lut_t_x1         :8;	//31:24	//motion gain LUT, T, x1
	};
}PE_E60_SHP_MOTION_PROT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C670 RW
	UINT32 reg_motion_prot_lut_t_y2         :8;	//7:0	//motion gain LUT, T, y2
	UINT32 reg_motion_prot_lut_t_x2         :8;	//15:8	//motion gain LUT, T, x2
	UINT32 reg_motion_prot_lut_t_y3         :8;	//23:16	//motion gain LUT, T, y3
	UINT32 reg_motion_prot_lut_t_x3         :8;	//31:24	//motion gain LUT, T, x3
	};
}PE_E60_SHP_MOTION_PROT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C680 RW
	UINT32 reg_core0_win_mot_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_mot_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_mot_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_mot_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_mot_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_mot_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_mot_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core0_win_mot_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core0_win_mot_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_mot_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_mot_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C684 RW
	UINT32 reg_core0_win_mot_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_mot_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C688 RW
	UINT32 reg_core0_win_mot_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_mot_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C68C RW
	UINT32 reg_core0_win_mot_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_mot_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C690 RW
	UINT32 reg_core0_win_mot_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_mot_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6A0 RW
	UINT32 reg_core1_win_mot_win0_en        :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_mot_win1_en        :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_mot_win01_en       :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_mot_win_outside    :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_mot_win_en         :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_mot_bdr_alpha      :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_mot_bdr_wid        :2;	//14:13	//border width
	UINT32 reg_core1_win_mot_bdr_en         :1;	//15:15	//border enable
	UINT32 reg_core1_win_mot_cr5            :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_mot_cb5            :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_mot_yy6            :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_MOT_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6A4 RW
	UINT32 reg_core1_win_mot_win_w0_x0      :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_mot_win_w0_y0      :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_MOT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6A8 RW
	UINT32 reg_core1_win_mot_win_w0_x1      :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_mot_win_w0_y1      :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_MOT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6AC RW
	UINT32 reg_core1_win_mot_win_w1_x0      :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_mot_win_w1_y0      :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_MOT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6B0 RW
	UINT32 reg_core1_win_mot_win_w1_x1      :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_mot_win_w1_y1      :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_MOT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6C0 RW
	UINT32 reg_obj_shp_en                   :1;	//0:0	//0 : disable	1 : enable
	UINT32 resvd                            :31;
	};
}PE_E60_SHP_OBJ_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6C4 RW
	UINT32 reg_obj_face_gain_lut_y0         :8;	//7:0	//object face gain LUT , y2
	UINT32 reg_obj_face_gain_lut_x0         :8;	//15:8	//object face gain LUT , x2
	UINT32 reg_obj_face_gain_lut_y1         :8;	//23:16	//object face gain LUT , y3
	UINT32 reg_obj_face_gain_lut_x1         :8;	//31:24	//object face gain LUT , x3
	};
}PE_E60_SHP_OBJ_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6C8 RW
	UINT32 reg_obj_face_gain_lut_y2         :8;	//7:0	//object face gain LUT , y0
	UINT32 reg_obj_face_gain_lut_x2         :8;	//15:8	//object face gain LUT , x0
	UINT32 reg_obj_face_gain_lut_y3         :8;	//23:16	//object face gain LUT , y1
	UINT32 reg_obj_face_gain_lut_x3         :8;	//31:24	//object face gain LUT , x1
	};
}PE_E60_SHP_OBJ_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6CC RW
	UINT32 reg_obj_obj_gain_lut_y0          :8;	//7:0	//object object gain LUT , y2
	UINT32 reg_obj_obj_gain_lut_x0          :8;	//15:8	//object object gain LUT , x2
	UINT32 reg_obj_obj_gain_lut_y1          :8;	//23:16	//object object gain LUT , y3
	UINT32 reg_obj_obj_gain_lut_x1          :8;	//31:24	//object object gain LUT , x3
	};
}PE_E60_SHP_OBJ_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6D0 RW
	UINT32 reg_obj_obj_gain_lut_y2          :8;	//7:0	//object object gain LUT , y0
	UINT32 reg_obj_obj_gain_lut_x2          :8;	//15:8	//object object gain LUT , x0
	UINT32 reg_obj_obj_gain_lut_y3          :8;	//23:16	//object object gain LUT , y1
	UINT32 reg_obj_obj_gain_lut_x3          :8;	//31:24	//object object gain LUT , x1
	};
}PE_E60_SHP_OBJ_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6D4 RW
	UINT32 reg_obj_final_blend_obj_lut_y0   :8;	//7:0	//object final_blend_obj LUT , y2
	UINT32 reg_obj_final_blend_obj_lut_x0   :8;	//15:8	//object final_blend_obj LUT , x2
	UINT32 reg_obj_final_blend_obj_lut_y1   :8;	//23:16	//object final_blend_obj LUT , y3
	UINT32 reg_obj_final_blend_obj_lut_x1   :8;	//31:24	//object final_blend_obj LUT , x3
	};
}PE_E60_SHP_OBJ_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6D8 RW
	UINT32 reg_obj_final_blend_obj_lut_y2   :8;	//7:0	//object final_blend_obj LUT , y0
	UINT32 reg_obj_final_blend_obj_lut_x2   :8;	//15:8	//object final_blend_obj LUT , x0
	UINT32 reg_obj_final_blend_obj_lut_y3   :8;	//23:16	//object final_blend_obj LUT , y1
	UINT32 reg_obj_final_blend_obj_lut_x3   :8;	//31:24	//object final_blend_obj LUT , x1
	};
}PE_E60_SHP_OBJ_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6DC RW
	UINT32 reg_obj_final_blend_face_lut_y0  :8;	//7:0	//object final_blend_face LUT , y2
	UINT32 reg_obj_final_blend_face_lut_x0  :8;	//15:8	//object final_blend_face LUT , x2
	UINT32 reg_obj_final_blend_face_lut_y1  :8;	//23:16	//object final_blend_face LUT , y3
	UINT32 reg_obj_final_blend_face_lut_x1  :8;	//31:24	//object final_blend_face LUT , x3
	};
}PE_E60_SHP_OBJ_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6E0 RW
	UINT32 reg_obj_final_blend_face_lut_y2  :8;	//7:0	//object final_blend_face LUT , y0
	UINT32 reg_obj_final_blend_face_lut_x2  :8;	//15:8	//object final_blend_face LUT , x0
	UINT32 reg_obj_final_blend_face_lut_y3  :8;	//23:16	//object final_blend_face LUT , y1
	UINT32 reg_obj_final_blend_face_lut_x3  :8;	//31:24	//object final_blend_face LUT , x1
	};
}PE_E60_SHP_OBJ_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6E4 RW
	UINT32 reg_obj_master_gain_lut_y0       :8;	//7:0	//object master_gain LUT , y2
	UINT32 reg_obj_master_gain_lut_x0       :8;	//15:8	//object master_gain LUT , x2
	UINT32 reg_obj_master_gain_lut_y1       :8;	//23:16	//object master_gain LUT , y3
	UINT32 reg_obj_master_gain_lut_x1       :8;	//31:24	//object master_gain LUT , x3
	};
}PE_E60_SHP_OBJ_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C6E8 RW
	UINT32 reg_obj_master_gain_lut_y2       :8;	//7:0	//object master_gain LUT , y0
	UINT32 reg_obj_master_gain_lut_x2       :8;	//15:8	//object master_gain LUT , x0
	UINT32 reg_obj_master_gain_lut_y3       :8;	//23:16	//object master_gain LUT , y1
	UINT32 reg_obj_master_gain_lut_x3       :8;	//31:24	//object master_gain LUT , x1
	};
}PE_E60_SHP_OBJ_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7A0 RO
	UINT32 reg_core0_mon_core_fin_out_vert_cnt :12;	//11:0	//Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_core_fin_in_vert_cnt :12;	//27:16	//Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7A4 RO
	UINT32 reg_core0_mon_in_vert_cnt        :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_in_hori_cnt        :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7A8 RO
	UINT32 reg_core0_mon_out_vert_cnt       :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_out_hori_cnt       :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7AC RO
	UINT32 reg_core0_mon_fin_out_vert_cnt   :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core0_mon_fin_in_vert_cnt    :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7B0 RO
	UINT32 reg_core0_mon_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}PE_E60_SHP_CORE0_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7B4 RO
	UINT32 reg_core0_mon_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}PE_E60_SHP_CORE0_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7D0 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE0_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7D4 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE0_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7D8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE0_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7DC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE0_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7E0 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C7E4 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_MOTION_GAIN_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C800 RO
	UINT32 reg_core0_tmap_status_window0    :32;	//31:0	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C804 RO
	UINT32 reg_core0_tmap_status_window1    :32;	//31:0	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C808 RO
	UINT32 reg_core0_tmap_status_0          :16;	//15:0	//
	UINT32 reg_core0_tmap_status_1          :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C80C RO
	UINT32 reg_core0_tmap_status_2          :16;	//15:0	//
	UINT32 reg_core0_tmap_status_3          :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C810 RO
	UINT32 reg_core0_tmap_status_4          :16;	//15:0	//
	UINT32 reg_core0_tmap_status_5          :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C814 RO
	UINT32 reg_core0_tmap_status_6          :16;	//15:0	//
	UINT32 reg_core0_tmap_status_7          :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C818 RO
	UINT32 reg_core0_tmap_status_8          :16;	//15:0	//
	UINT32 reg_core0_tmap_status_9          :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C81C RO
	UINT32 reg_core0_tmap_status_10         :16;	//15:0	//
	UINT32 reg_core0_tmap_status_11         :16;	//31:16	//
	};
}PE_E60_SHP_CORE0_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9A0 RO
	UINT32 reg_core1_mon_core_fin_out_vert_cnt :12;	//11:0	//Output previous frame vertical counter (core)
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_core_fin_in_vert_cnt :12;	//27:16	//Input previous frame vertical counter (core)
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9A4 RO
	UINT32 reg_core1_mon_in_vert_cnt        :12;	//11:0	//Input vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_in_hori_cnt        :12;	//27:16	//Input horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9A8 RO
	UINT32 reg_core1_mon_out_vert_cnt       :12;	//11:0	//Output vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_out_hori_cnt       :12;	//27:16	//Output horizontal counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9AC RO
	UINT32 reg_core1_mon_fin_out_vert_cnt   :12;	//11:0	//Output previous frame vertical counter
	UINT32 resvd0                           :4;
	UINT32 reg_core1_mon_fin_in_vert_cnt    :12;	//27:16	//Input previous frame vertical counter
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9B0 RO
	UINT32 reg_core1_mon_shp_i_sucfail      :32;	//31:0	//Input success/fail monitoring register
	};
}PE_E60_SHP_CORE1_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9B4 RO
	UINT32 reg_core1_mon_shp_o_sucfail      :32;	//31:0	//Output success/fail monitoring register
	};
}PE_E60_SHP_CORE1_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9D0 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE1_FD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9D4 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE1_FD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9D8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE1_FD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902C9DC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_CORE1_FD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA00 RO
	UINT32 reg_core1_tmap_status_window0    :32;	//31:0	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA04 RO
	UINT32 reg_core1_tmap_status_window1    :32;	//31:0	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA08 RO
	UINT32 reg_core1_tmap_status_0          :16;	//15:0	//
	UINT32 reg_core1_tmap_status_1          :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA0C RO
	UINT32 reg_core1_tmap_status_2          :16;	//15:0	//
	UINT32 reg_core1_tmap_status_3          :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA10 RO
	UINT32 reg_core1_tmap_status_4          :16;	//15:0	//
	UINT32 reg_core1_tmap_status_5          :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA14 RO
	UINT32 reg_core1_tmap_status_6          :16;	//15:0	//
	UINT32 reg_core1_tmap_status_7          :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA18 RO
	UINT32 reg_core1_tmap_status_8          :16;	//15:0	//
	UINT32 reg_core1_tmap_status_9          :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CA1C RO
	UINT32 reg_core1_tmap_status_10         :16;	//15:0	//
	UINT32 reg_core1_tmap_status_11         :16;	//31:16	//
	};
}PE_E60_SHP_CORE1_TMAP_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB00 RW
	UINT32 reg_core0_win_face_win0_en       :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_face_win1_en       :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_face_win01_en      :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_face_win_outside   :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_face_win_en        :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_face_bdr_alpha     :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_face_bdr_wid       :2;	//14:13	//border width
	UINT32 reg_core0_win_face_bdr_en        :1;	//15:15	//border enable
	UINT32 reg_core0_win_face_cr5           :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_face_cb5           :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_face_yy6           :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB04 RW
	UINT32 reg_core0_win_face_win_w0_x0     :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y0     :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB08 RW
	UINT32 reg_core0_win_face_win_w0_x1     :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w0_y1     :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB0C RW
	UINT32 reg_core0_win_face_win_w1_x0     :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y0     :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB10 RW
	UINT32 reg_core0_win_face_win_w1_x1     :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_face_win_w1_y1     :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB14 RW
	UINT32 reg_core0_win_face_value         :8;	//7:0	//win_w1_y1
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_CORE0_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB18 RW
	UINT32 reg_core1_win_face_win0_en       :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_face_win1_en       :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_face_win01_en      :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_face_win_outside   :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_face_win_en        :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_face_bdr_alpha     :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_face_bdr_wid       :2;	//14:13	//border width
	UINT32 reg_core1_win_face_bdr_en        :1;	//15:15	//border enable
	UINT32 reg_core1_win_face_cr5           :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_face_cb5           :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_face_yy6           :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB1C RW
	UINT32 reg_core1_win_face_win_w0_x0     :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_face_win_w0_y0     :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB20 RW
	UINT32 reg_core1_win_face_win_w0_x1     :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_face_win_w0_y1     :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB24 RW
	UINT32 reg_core1_win_face_win_w1_x0     :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_face_win_w1_y0     :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB28 RW
	UINT32 reg_core1_win_face_win_w1_x1     :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_face_win_w1_y1     :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB2C RW
	UINT32 reg_core1_win_face_value         :8;	//7:0	//win_w1_y1
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_CORE1_FACE_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB30 RW
	UINT32 reg_core0_win_body_win0_en       :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core0_win_body_win1_en       :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core0_win_body_win01_en      :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core0_win_body_win_outside   :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core0_win_body_win_en        :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core0_win_body_bdr_alpha     :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core0_win_body_bdr_wid       :2;	//14:13	//border width
	UINT32 reg_core0_win_body_bdr_en        :1;	//15:15	//border enable
	UINT32 reg_core0_win_body_cr5           :5;	//20:16	//border color: cr5
	UINT32 reg_core0_win_body_cb5           :5;	//25:21	//border color: cb5
	UINT32 reg_core0_win_body_yy6           :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB34 RW
	UINT32 reg_core0_win_body_win_w0_x0     :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y0     :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB38 RW
	UINT32 reg_core0_win_body_win_w0_x1     :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w0_y1     :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB3C RW
	UINT32 reg_core0_win_body_win_w1_x0     :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y0     :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB40 RW
	UINT32 reg_core0_win_body_win_w1_x1     :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core0_win_body_win_w1_y1     :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB44 RW
	UINT32 reg_core0_win_body_value         :8;	//7:0	//win_w1_y1
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_CORE0_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB48 RW
	UINT32 reg_core1_win_body_win0_en       :1;	//0:0	//1: select only window0 as active area
	UINT32 reg_core1_win_body_win1_en       :1;	//1:1	//1: select only window1 as active area
	UINT32 reg_core1_win_body_win01_en      :1;	//2:2	//1: select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 reg_core1_win_body_win_outside   :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 reg_core1_win_body_win_en        :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 reg_core1_win_body_bdr_alpha     :5;	//12:8	//border alpha for alpha-blending
	UINT32 reg_core1_win_body_bdr_wid       :2;	//14:13	//border width
	UINT32 reg_core1_win_body_bdr_en        :1;	//15:15	//border enable
	UINT32 reg_core1_win_body_cr5           :5;	//20:16	//border color: cr5
	UINT32 reg_core1_win_body_cb5           :5;	//25:21	//border color: cb5
	UINT32 reg_core1_win_body_yy6           :6;	//31:26	//border color: yy6
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB4C RW
	UINT32 reg_core1_win_body_win_w0_x0     :12;	//11:0	//win_w0_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_body_win_w0_y0     :12;	//27:16	//win_w0_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB50 RW
	UINT32 reg_core1_win_body_win_w0_x1     :12;	//11:0	//win_w0_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_body_win_w0_y1     :12;	//27:16	//win_w0_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB54 RW
	UINT32 reg_core1_win_body_win_w1_x0     :12;	//11:0	//win_w1_x0
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_body_win_w1_y0     :12;	//27:16	//win_w1_y0
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB58 RW
	UINT32 reg_core1_win_body_win_w1_x1     :12;	//11:0	//win_w1_x1
	UINT32 resvd0                           :4;
	UINT32 reg_core1_win_body_win_w1_y1     :12;	//27:16	//win_w1_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CB5C RW
	UINT32 reg_core1_win_body_value         :8;	//7:0	//win_w1_y1
	UINT32 resvd                            :24;
	};
}PE_E60_SHP_CORE1_BODY_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CBF0 RW
	UINT32 drc_apb_write_cont                 :2;  //1:0
	UINT32 dnr_decont                         :1;  //2:2
	UINT32 drc_write_cont                     :2;  //4:3
	UINT32 reserved                           :3;  //7:5
	UINT32 reg_pre_norm                       :8;  //15:8
	UINT32 reg_cur_norm                       :8;  //23:16
	UINT32 reg_pre_sc    	                  :8;  //31:24
	};
}PE_E60_SHP_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CBF4 RW
	UINT32 reg_cur_sc 	                   :8;  // 7: 0  
	UINT32 reg_ui_gain_w                   :8;  // 15:8
	UINT32 reg_ui_gain_b                   :8;  // 23:16
	UINT32 reg_vy_mode 	                   :8;  // 31:24
	};
}PE_E60_SHP_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CBF8 RW
	UINT32 reg_obc_debug                      :2;  // 1:0, 0: shp result   1 : face map   2 : object map
	};
}PE_E60_SHP_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902CBFC RW
	UINT32 tdata0                           :32;
	};
}PE_E60_SHP_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029300 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution 3840
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution   2160
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_PSP_CTRL00_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029304 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//23:16	//Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//31:24	//Number of vblock 135
	};
}PE_E60_VSD_PSP_CTRL01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029308 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : ?ÑÏ≤¥ enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line Í≤ΩÍ≥Ñ?êÏÑú repeat ?úÌÇ¨ h pixel Í∞úÏàò
	UINT32 reg_cg_disp_clk                  :1;	//9 //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame Í≤ΩÍ≥Ñ?êÏÑú repeat ?úÌÇ¨ v line Í∞úÏàò
	UINT32 reserved                         :1;	//15 //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction??H margin
	};
}PE_E60_VSD_PSP_CTRL02_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902930C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :2;
	UINT32 reg_force_pos_en                 :1;	//15 //forced FG box posotion
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : ?ÑÎ≥¥ box ?ÅÏó≠???Ä??threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : ?ÑÎ≥¥ box ?ÅÏó≠???Ä??threshold
	};
}PE_E60_VSD_EDGE_TH_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029310 RW
	UINT32 reg_force_w1_pos                 :8;	//7:0	//(w1, h1)
	UINT32 reg_force_h1_pos                 :8;	//15:8	//(w1, h1)
	UINT32 reg_force_w2_pos                 :8;	//23:16	//(w2, h2)
	UINT32 reg_force_h2_pos                 :8;	//31:24	//(w2, h2)
	};
}PE_E60_VSD_FG_POSITION_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029314 RW
	UINT32 reg_perspect_lut_x_0             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029318 RW
	UINT32 reg_perspect_lut_x_1             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902931C RW
	UINT32 reg_perspect_lut_x_2             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029320 RW
	UINT32 reg_perspect_lut_x_3             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029324 RW
	UINT32 reg_perspect_lut_y_0             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029328 RW
	UINT32 reg_perspect_lut_y_1             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902932C RW
	UINT32 reg_perspect_lut_y_2             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029330 RW
	UINT32 reg_perspect_lut_y_3             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029334 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
}PE_E60_VSD_PROB_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029338 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
}PE_E60_VSD_ELLIPS_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902933C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
}PE_E60_VSD_PROB_DIFF_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029340 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (?åÍ≥†Î¶¨Ï¶ò parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (?åÍ≥†Î¶¨Ï¶ò parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
}PE_E60_VSD_OBJECT_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029344 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd0                           :15;
	UINT32 reg_hist_coef2                   :3;	//18:16	//total sum 8
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef1                   :3;	//22:20	//total sum 8
	UINT32 resvd2                           :1;
	UINT32 reg_hist_coef0                   :3;	//26:24	//total sum 8
	UINT32 resvd3                           :5;
	};
}PE_E60_VSD_BLUR_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029348 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain??Ï∂úÎ†• Ï§?psp_gain??displayÎ°??ÑÌôò
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain ?ÅÏö©
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound Î•?enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound Î•?disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound Î•?disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :3;	//18:16	//debug (SYNC_DLY + 4) (DNR 0x19, SHP 0x0)
	UINT32 resvd4                           :5;
	UINT32 valid_expand                     :1;	//24 //shp mode only (sync index)
	UINT32 reg_sync_ready_mode              :1;	//25 //VSD sync mode 0
	UINT32 resvd5                           :5;
	UINT32 reg_l4_blank                     :1;	//31 //0 : 4, 1 : 3
	};
}PE_E60_VSD_DISPLAY_DEBUG_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902934C RW
	UINT32 reg_psp_iir_alpha                :8;	//7:0	//IIR Alpha blending rate (0 ~ 1) 	8bit Í∏∞Ï?
	UINT32 alpha_sel                        :1;	//8 //1 : LUT alpha
	UINT32 resvd                            :22;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial???¨Ïö©( data reset)
	};
}PE_E60_VSD_PSP_IIR_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029350 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
}PE_E60_VSD_PSP_GAIN_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029354 RO
	UINT32 h1_pos                           :7;	//6:0	//
	UINT32 h2_pos                           :7;	//13:7	//
	UINT32 w1_pos                           :7;	//20:14	//
	UINT32 w2_pos                           :7;	//27:21	//
	UINT32 r_edge_total_lsb                 :4;	//31:28	//r_edge_total[4:1]
	};
}PE_E60_VSD_PSP_DBG_MON00_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029358 RO
	UINT32 out_max_flat_length_h            :7;	//6:0	//
	UINT32 out_max_flat_length_w            :7;	//13:7	//
	UINT32 r_edge_total_msb                 :18;	//31:14	//r_edge_total[22:5]
	};
}PE_E60_VSD_PSP_DBG_MON01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902935C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_VSD_RESERVED00_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029360 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029364 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029368 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF45_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902936C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF67_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029370 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_VSD_BLUR_HCOEF8_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029374 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_VCOEF01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029378 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_VCOEF23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902937C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_VSD_BLUR_VCOEF4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029380 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029384 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029388 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902938C RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029390 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029394 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_5_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029398 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_6_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902939C RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_7_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293A0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_8_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293A4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_9_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293A8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_10_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293AC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_11_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293B0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_12_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293B4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_13_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293B8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_14_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293BC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_15_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293C0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_16_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293C4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_17_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293C8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_18_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293CC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_19_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293D0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_20_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293D4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_21_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293D8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_22_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293DC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293E0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_24_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293E4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_25_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293E8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_26_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293EC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_27_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293F0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_28_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293F4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_29_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293F8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_30_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90293FC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_31_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029400 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_L5_GAIN_LUT1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029404 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_L5_GAIN_LUT2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029408 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_FG_GAIN_LUT1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902940C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_FG_GAIN_LUT2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029410 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_EDGE_WIN_H_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029414 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_EDGE_WIN_V_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029418 RO
	UINT32 edge0_fg                         :23;	//22:0	//FG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE0_FG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902941C RO
	UINT32 edge0_bg                         :23;	//22:0	//BG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE0_BG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029420 RO
	UINT32 edge1_fg                         :23;	//22:0	//FG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE1_FG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029424 RO
	UINT32 edge1_bg                         :23;	//22:0	//BG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE1_BG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029428 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :8;	//11:4	//threshold of lower
	UINT32 th_upper                         :8;	//19:12	//threshold of upper
	UINT32 prc_step                         :8;	//27:20	//same protection step
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_PSP_IIR1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029444 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE0_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029448 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902944C RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029450 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029454 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS0_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029458 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS1_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902945C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS2_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029460 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS3_SET_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902946C RW
	UINT32 buf_mem_en                       :1;	//0 //
	UINT32 buf_mem_rd                       :1;	//1 //
	UINT32 map_mode                         :1;	//2 //
	UINT32 seed_mode                        :1;	//3 //
	UINT32 refine_off                       :1;	//4 //
	UINT32 resvd0                           :7;
	UINT32 wr_done_read                     :4;	//15:12	//
	UINT32 fg_num                           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_PSP_MEM_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029470 RW
	UINT32 reg_refine_diff_luma_a           :8;	//7:0	//
	UINT32 reg_refine_diff_chroma_b         :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_VSD_REFINE_CTRL0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029474 RW
	UINT32 reg_refine_weight_lux_x0         :8;	//7:0	//
	UINT32 reg_refine_weight_lux_x1         :8;	//15:8	//
	UINT32 reg_refine_weight_lux_x2         :8;	//23:16	//
	UINT32 reg_refine_weight_lux_x3         :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029478 RW
	UINT32 reg_refine_weight_lux_y0         :8;	//7:0	//
	UINT32 reg_refine_weight_lux_y1         :8;	//15:8	//
	UINT32 reg_refine_weight_lux_y2         :8;	//23:16	//
	UINT32 reg_refine_weight_lux_y3         :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902947C RW
	UINT32 reg_refine_post_lux_x0           :8;	//7:0	//
	UINT32 reg_refine_post_lux_x1           :8;	//15:8	//
	UINT32 reg_refine_post_lux_x2           :8;	//23:16	//
	UINT32 reg_refine_post_lux_x3           :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029480 RW
	UINT32 reg_refine_post_lux_y0           :8;	//7:0	//
	UINT32 reg_refine_post_lux_y1           :8;	//15:8	//
	UINT32 reg_refine_post_lux_y2           :8;	//23:16	//
	UINT32 reg_refine_post_lux_y3           :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029484 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_ALPHA_GAIN_LUT1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029488 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_ALPHA_GAIN_LUT2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902948C RW
	UINT32 y4_point                         :8;	//7:0	//control point of Y4
	UINT32 x4_point                         :8;	//15:8	//control point of X4
	UINT32 y5_point                         :8;	//23:16	//control point of Y5
	UINT32 x5_point                         :8;	//31:24	//control point of X5
	};
}PE_E60_VSD_ALPHA_GAIN_LUT3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029490 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS0_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029494 RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS0_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029498 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS1_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902949C RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS1_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294A0 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS2_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294A4 RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS2_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294A8 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS3_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294AC RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS3_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294B0 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//H end
	UINT32 reg_w1_pos                       :8;	//15:8	//H start
	UINT32 reg_h2_pos                       :8;	//23:16	//V end
	UINT32 reg_h1_pos                       :8;	//31:24	//V start
	};
}PE_E60_VSD_FACE0_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294B4 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294B8 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294BC RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294C0 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE0_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294C4 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294C8 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294CC RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90294D0 RW
	UINT32 face0_set1_en                    :1;	//0 //
	UINT32 face1_set1_en                    :1;	//1 //
	UINT32 face2_set1_en                    :1;	//2 //
	UINT32 face3_set1_en                    :1;	//3 //
	UINT32 face0_set2_en                    :1;	//4 //
	UINT32 face1_set2_en                    :1;	//5 //
	UINT32 face2_set2_en                    :1;	//6 //
	UINT32 face3_set2_en                    :1;	//7 //
	UINT32 additional_box_en                :1;	//8 //0 : 4 box	1 : 8 box
	UINT32 resvd                            :23;
	};
}PE_E60_VSD_FACE_SET_CTRL_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029500 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution 3840
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution   2160
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029504 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size       16
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size       16
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :8;	//23:16	//Number of hblock 240
	UINT32 reg_l5_hei                       :8;	//31:24	//Number of vblock 135
	};
}PE_E60_VSD_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029508 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : ?ÑÏ≤¥ enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line Í≤ΩÍ≥Ñ?êÏÑú repeat ?úÌÇ¨ h pixel Í∞úÏàò
	UINT32 reg_cg_disp_clk                  :1;	//9 //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame Í≤ΩÍ≥Ñ?êÏÑú repeat ?úÌÇ¨ v line Í∞úÏàò
	UINT32 reserved                         :1;	//15 //fg memory??mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction??V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction??H margin
	};
}PE_E60_VSD_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902950C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :2;
	UINT32 reg_force_pos_en                 :1;	//15 //forced FG box posotion
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : ?ÑÎ≥¥ box ?ÅÏó≠???Ä??threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : ?ÑÎ≥¥ box ?ÅÏó≠???Ä??threshold
	};
}PE_E60_VSD_EDGE_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029510 RW
	UINT32 reg_force_w1_pos                 :8;	//7:0	//(w1, h1)
	UINT32 reg_force_h1_pos                 :8;	//15:8	//(w1, h1)
	UINT32 reg_force_w2_pos                 :8;	//23:16	//(w2, h2)
	UINT32 reg_force_h2_pos                 :8;	//31:24	//(w2, h2)
	};
}PE_E60_VSD_FG_POSITION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029514 RW
	UINT32 reg_perspect_lut_x_0             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902955C RW
	UINT32 head_apl                         :16;	//15:0	//
	UINT32 body_apl                         :16;	//16:31	//
	};
}PE_E60_VSD_PERSPECT_LUT_X1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902951C RW
	UINT32 reg_perspect_lut_x_2             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029520 RW
	UINT32 reg_perspect_lut_x_3             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_X3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029524 RW
	UINT32 reg_perspect_lut_y_0             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029528 RW
	UINT32 reg_perspect_lut_y_1             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902952C RW
	UINT32 reg_perspect_lut_y_2             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029530 RW
	UINT32 reg_perspect_lut_y_3             :32;	//31:0	//
	};
}PE_E60_VSD_PERSPECT_LUT_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029534 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
}PE_E60_VSD_PROB_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029538 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
}PE_E60_VSD_ELLIPS_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902953C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
}PE_E60_VSD_PROB_DIFF_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029540 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (?åÍ≥†Î¶¨Ï¶ò parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (?åÍ≥†Î¶¨Ï¶ò parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
}PE_E60_VSD_OBJECT_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029544 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd0                           :15;
	UINT32 reg_hist_coef2                   :3;	//18:16	//total sum 8
	UINT32 resvd1                           :1;
	UINT32 reg_hist_coef1                   :3;	//22:20	//total sum 8
	UINT32 resvd2                           :1;
	UINT32 reg_hist_coef0                   :3;	//26:24	//total sum 8
	UINT32 resvd3                           :5;
	};
}PE_E60_VSD_BLUR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029548 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain??Ï∂úÎ†• Ï§?psp_gain??displayÎ°??ÑÌôò
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain ?ÅÏö©
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound Î•?enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound Î•?disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound Î•?disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :3;	//18:16	//debug (SYNC_DLY + 4) (DNR 0x19, SHP 0x0)
	UINT32 resvd4                           :5;
	UINT32 valid_expand                     :1;	//24 //shp mode only (sync index)
	UINT32 reg_sync_ready_mode              :1;	//25 //VSD sync mode 0
	UINT32 resvd5                           :5;
	UINT32 reg_l4_blank                     :1;	//31 //0 : 4, 1 : 3
	};
}PE_E60_VSD_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902954C RW
	UINT32 reg_psp_iir_alpha                :8;	//7:0	//IIR Alpha blending rate (0 ~ 1) 	8bit Í∏∞Ï?
	UINT32 alpha_sel                        :1;	//8 //1 : LUT alpha
	UINT32 resvd                            :22;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial???¨Ïö©( data reset)
	};
}PE_E60_VSD_PSP_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029550 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
}PE_E60_VSD_PSP_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029554 RO
	UINT32 h1_pos                           :7;	//6:0	//
	UINT32 h2_pos                           :7;	//13:7	//
	UINT32 w1_pos                           :7;	//20:14	//
	UINT32 w2_pos                           :7;	//27:21	//
	UINT32 r_edge_total_lsb                 :4;	//31:28	//r_edge_total[4:1]
	};
}PE_E60_VSD_PSP_DBG_MON00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029558 RO
	UINT32 out_max_flat_length_h            :7;	//6:0	//
	UINT32 out_max_flat_length_w            :7;	//13:7	//
	UINT32 r_edge_total_msb                 :18;	//31:14	//r_edge_total[22:5]
	};
}PE_E60_VSD_PSP_DBG_MON01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902955C RW
	UINT32 head_apl                         :16;	//15:0	//
	UINT32 body_apl                         :16;	//16:31	//
	};
}PE_E60_VSD_RESERVED00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029560 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029564 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029568 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902956C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_HCOEF67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029570 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_VSD_BLUR_HCOEF8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029574 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_VCOEF01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029578 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_VSD_BLUR_VCOEF23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902957C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_VSD_BLUR_VCOEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029580 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029584 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029588 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902958C RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029590 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029594 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029598 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902959C RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295A0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295A4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295A8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295AC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295B0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295B4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295B8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295BC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295C0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295C4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295C8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295CC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295D0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295D4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295D8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295DC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295E0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295E4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295E8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295EC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295F0 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295F4 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295F8 RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90295FC RO
	UINT32 data_bg                          :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 data_fg                          :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_HISTOGRAM_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029600 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029604 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029608 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_FG_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902960C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_FG_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029610 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_EDGE_WIN_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029614 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_EDGE_WIN_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029618 RO
	UINT32 edge0_fg                         :23;	//22:0	//FG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE0_FG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902961C RO
	UINT32 edge0_bg                         :23;	//22:0	//BG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE0_BG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029620 RO
	UINT32 edge1_fg                         :23;	//22:0	//FG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE1_FG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029624 RO
	UINT32 edge1_bg                         :23;	//22:0	//BG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_VSD_EDGE1_BG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029628 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :8;	//11:4	//threshold of lower
	UINT32 th_upper                         :8;	//19:12	//threshold of upper
	UINT32 prc_step                         :8;	//27:20	//same protection step
	UINT32 resvd1                           :4;
	};
}PE_E60_VSD_PSP_IIR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029644 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE0_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029648 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902964C RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029650 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029654 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS0_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029658 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS1_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902965C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS2_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029660 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//20:12	//4.5bit
	UINT32 resvd1                           :2;
	UINT32 face_en                          :1;	//23 //
	UINT32 reg_ellipse_master               :8;	//31:24	//gain * master
	};
}PE_E60_VSD_ELLIPS3_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029664 RW
	UINT32 reg_lm_vsize                     :13;	//12:0	//Vsize of 8P input	4320
	UINT32 resvd0                           :3;
	UINT32 reserved                         :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_VSD_BUFFER_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029668 RW
	UINT32 resvd0                           :2;
	UINT32 reg_hs_toggle                    :1;	//2 //make hsync method
	UINT32 resvd1                           :4;
	UINT32 reg_2ch_hblank                   :9;	//15:7	//blank count between Hsize 280 (2ch)
	UINT32 reg_ds_hsize                     :13;	//28:16	//Core gen's input hsize	1920(dual pixel of 3840)
	UINT32 resvd2                           :3;
	};
}PE_E60_VSD_BUFFER_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902966C RW
	UINT32 buf_mem_en                       :1;	//0 //
	UINT32 buf_mem_rd                       :1;	//1 //
	UINT32 map_mode                         :1;	//2 //
	UINT32 seed_mode                        :1;	//3 //
	UINT32 refine_off                       :1;	//4 //
	UINT32 resvd0                           :7;
	UINT32 wr_done_read                     :4;	//15:12	//
	UINT32 fg_num                           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_VSD_PSP_MEM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029670 RW
	UINT32 reg_refine_diff_luma_a           :8;	//7:0	//
	UINT32 reg_refine_diff_chroma_b         :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_VSD_REFINE_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029674 RW
	UINT32 reg_refine_weight_lux_x0         :8;	//7:0	//
	UINT32 reg_refine_weight_lux_x1         :8;	//15:8	//
	UINT32 reg_refine_weight_lux_x2         :8;	//23:16	//
	UINT32 reg_refine_weight_lux_x3         :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029678 RW
	UINT32 reg_refine_weight_lux_y0         :8;	//7:0	//
	UINT32 reg_refine_weight_lux_y1         :8;	//15:8	//
	UINT32 reg_refine_weight_lux_y2         :8;	//23:16	//
	UINT32 reg_refine_weight_lux_y3         :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902967C RW
	UINT32 reg_refine_post_lux_x0           :8;	//7:0	//
	UINT32 reg_refine_post_lux_x1           :8;	//15:8	//
	UINT32 reg_refine_post_lux_x2           :8;	//23:16	//
	UINT32 reg_refine_post_lux_x3           :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029680 RW
	UINT32 reg_refine_post_lux_y0           :8;	//7:0	//
	UINT32 reg_refine_post_lux_y1           :8;	//15:8	//
	UINT32 reg_refine_post_lux_y2           :8;	//23:16	//
	UINT32 reg_refine_post_lux_y3           :8;	//31:24	//
	};
}PE_E60_VSD_REFINE_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029684 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_VSD_ALPHA_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029688 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_VSD_ALPHA_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902968C RW
	UINT32 y4_point                         :8;	//7:0	//control point of Y4
	UINT32 x4_point                         :8;	//15:8	//control point of X4
	UINT32 y5_point                         :8;	//23:16	//control point of Y5
	UINT32 x5_point                         :8;	//31:24	//control point of X5
	};
}PE_E60_VSD_ALPHA_GAIN_LUT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029690 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS0_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029694 RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS0_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029698 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS1_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902969C RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS1_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296A0 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS2_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296A4 RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS2_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296A8 RW
	UINT32 reg_sin_theta                    :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_cos_theta                    :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_rotation_en          :1;	//31 //
	};
}PE_E60_VSD_ELLIPS3_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296AC RW
	UINT32 reg_ellipse_cen_pos_y            :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_ellipse_cen_pos_x            :9;	//20:12	//
	UINT32 resvd1                           :10;
	UINT32 reg_ellipse_cen_pos_en           :1;	//31 //
	};
}PE_E60_VSD_ELLIPS3_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296B0 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE0_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296B4 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296B8 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296BC RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296C0 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE0_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296C4 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE1_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296C8 RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE2_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296CC RW
	UINT32 reg_w2_pos                       :8;	//7:0	//
	UINT32 reg_w1_pos                       :8;	//15:8	//
	UINT32 reg_h2_pos                       :8;	//23:16	//
	UINT32 reg_h1_pos                       :8;	//31:24	//
	};
}PE_E60_VSD_FACE3_SET2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90296D0 RW
	UINT32 face0_set1_en                    :1;	//0 //
	UINT32 face1_set1_en                    :1;	//1 //
	UINT32 face2_set1_en                    :1;	//2 //
	UINT32 face3_set1_en                    :1;	//3 //
	UINT32 face0_set2_en                    :1;	//4 //
	UINT32 face1_set2_en                    :1;	//5 //
	UINT32 face2_set2_en                    :1;	//6 //
	UINT32 face3_set2_en                    :1;	//7 //
	UINT32 additional_box_en                :1;	//8 //0 : 4 box	1 : 8 box
	UINT32 resvd                            :23;
	};
}PE_E60_VSD_FACE_SET_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C00 RW
	UINT32 load_time                        :1;	//0 //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//1 //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_E60_DTM_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C04 RW
	UINT32 width                            :13;	//12:0	//width
	UINT32 resvd0                           :3;
	UINT32 height                           :13;	//28:16	//height
	UINT32 resvd1                           :3;
	};
}PE_E60_DTM_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C08 RW
	UINT32 reg_yy_lsb_detour_en             :1;	//0 //1: y channel LSB detour enable for Halo blur(FRC/SHP)
	UINT32 reg_va_cnt_en                    :1;	//1 //1: va count enable for DTM_TOP_CTRL_03
	UINT32 dtm_disp_detour                  :1;	//2 //1: display tone mapping detour
	UINT32 resvd0                           :1;
	UINT32 reg_use_own_lut_en               :1;	//4 //0:use luminanace LUT channel G hif	1:use own LUT hif(B/R)(WR only)
	UINT32 resvd1                           :19;
	UINT32 reg_master_en                    :1;	//24 //LUT master enable
	UINT32 resvd2                           :7;
	};
}PE_E60_DTM_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C0C RO
	UINT32 vcnt                             :13;	//12:0	//vertical line count
	UINT32 va_pe1_in                        :1;	//13 //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//14 //Vertical Active at PE1 output
	UINT32 resvd0                           :1;
	UINT32 vcnt2                            :13;	//28:16	//vertical line number
	UINT32 resvd1                           :3;
	};
}PE_E60_DTM_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C10 RW
	UINT32 r_to_cnt                         :12;	//11:0	//apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_E60_DTM_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C14 RW
	UINT32 vdpulse_pos                      :32;	//31:0	//vdpulse position for register loading
	};
}PE_E60_DTM_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C20 RW
	UINT32 dummy_00                         :32;	//31:0	//
	};
}PE_E60_DTM_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C24 RW
	UINT32 dummy_01                         :32;	//31:0	//
	};
}PE_E60_DTM_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C28 RW
	UINT32 dummy_02                         :32;	//31:0	//
	};
}PE_E60_DTM_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C2C RW
	UINT32 dummy_03                         :32;	//31:0	//
	};
}PE_E60_DTM_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C40 RW
	UINT32 reg_csc1st_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_E60_DTM_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C44 RW
	UINT32 r_csc1st_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C48 RW
	UINT32 r_csc1st_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C4C RW
	UINT32 r_csc1st_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C50 RW
	UINT32 r_csc1st_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C54 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C58 RW
	UINT32 r_csc1st_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C5C RW
	UINT32 r_csc1st_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C60 RW
	UINT32 r_csc1st_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C70 RW
	UINT32 luminance_lut_enable             :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :3;
	UINT32 window_cg_disable                :1;	//20 //clock gating disable
	UINT32 resvd3                           :11;
	};
}PE_E60_DTM_LLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C74 RW
	UINT32 win_w0_x0_e0                     :12;	//11:0	//win_w0_x0_e0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_e0                     :12;	//27:16	//win_w0_y0_e0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C78 RW
	UINT32 win_w0_x1_e0                     :12;	//11:0	//win_w0_x1_e0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_e0                     :12;	//27:16	//win_w0_y1_e0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C7C RW
	UINT32 win_w1_x0_e0                     :12;	//11:0	//win_w1_x0_e0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_e0                     :12;	//27:16	//win_w1_y0_e0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C80 RW
	UINT32 win_w1_x1_e0                     :12;	//11:0	//win_w1_x1_e0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_e0                     :12;	//27:16	//win_w1_y1_e0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C84 RW
	UINT32 hif_llut_wdata_y_33rd            :10;	//9:0	//Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//25:16	//X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
}PE_E60_DTM_LLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C88 RW
	UINT32 hif_llut0_address                :5;	//4:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut0_load                   :1;	//8 //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load            :1;	//11 //0 : LUT load at vactive falling, when hif_llut0_load = 1	1 : LUT load at "hif_llut0_load = 1"
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_E60_DTM_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C8C RW
	UINT32 hif_llut0_wdata_y                :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_E60_DTM_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C90 RW
	UINT32 hif_llut1_address                :5;	//4:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut1_load                   :1;	//8 //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load            :1;	//11 //0 : LUT load at vactive falling, when hif_llut1_load = 1	1 : LUT load at "hif_llut1_load = 1"
	UINT32 hif_llut1_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut1_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_E60_DTM_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C94 RW
	UINT32 hif_llut1_wdata_y                :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut1_wdata_x                :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_E60_DTM_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C98 RW
	UINT32 hif_llut2_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load            :1;	//11 //0 : LUT load at vactive falling, when hif_dce_load = 1	1 : LUT load at "hif_dce_load = 1"
	UINT32 hif_llut2_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut2_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_E60_DTM_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029C9C RW
	UINT32 hif_llut2_wdata_y                :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut2_wdata_x                :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_E60_DTM_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CB0 RW
	UINT32 reg_csc2nd_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_E60_DTM_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CB4 RW
	UINT32 r_csc2nd_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc2nd_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CB8 RW
	UINT32 r_csc2nd_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc2nd_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CBC RW
	UINT32 r_csc2nd_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc2nd_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CC0 RW
	UINT32 r_csc2nd_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc2nd_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CC4 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc2nd_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_DTM_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CC8 RW
	UINT32 r_csc2nd_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc2nd_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CCC RW
	UINT32 r_csc2nd_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc2nd_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CD0 RW
	UINT32 r_csc2nd_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc2nd_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_DTM_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CE0 RW
	UINT32 reg_hue_prsv_en                  :1;	//0 //enable pin for hue restoration
	UINT32 resvd0                           :3;
	UINT32 reg_sat_prsv_en                  :1;	//4 //enable pin for saturation preserving
	UINT32 reg_hue_prsv_detour              :1;	//5 //preserving detour
	UINT32 resvd1                           :6;
	UINT32 reg_hue_prsv_cg_disable          :1;	//12 //clock gating disable
	UINT32 resvd2                           :3;
	UINT32 reg_sat_prsv_ratio               :8;	//23:16	//0:bypass, 255:restored sat
	UINT32 reg_hue_prsv_ratio               :8;	//31:24	//0:bypass, 255:restored hue
	};
}PE_E60_DTM_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CF0 RW
	UINT32 win_w0_x0_o0                     :12;	//11:0	//win_w0_x0_o0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_o0                     :12;	//27:16	//win_w0_y0_o0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CF4 RW
	UINT32 win_w0_x1_o0                     :12;	//11:0	//win_w0_x1_o0
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_o0                     :12;	//27:16	//win_w0_y1_o0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CF8 RW
	UINT32 win_w1_x0_o0                     :12;	//11:0	//win_w1_x0_o0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_o0                     :12;	//27:16	//win_w1_y0_o0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029CFC RW
	UINT32 win_w1_x1_o0                     :12;	//11:0	//win_w1_x1_o0
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_o0                     :12;	//27:16	//win_w1_y1_o0
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D00 RW
	UINT32 win_w0_x0_e1                     :12;	//11:0	//win_w0_x0_e1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_e1                     :12;	//27:16	//win_w0_y0_e1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D04 RW
	UINT32 win_w0_x1_e1                     :12;	//11:0	//win_w0_x1_e1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_e1                     :12;	//27:16	//win_w0_y1_e1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D08 RW
	UINT32 win_w1_x0_e1                     :12;	//11:0	//win_w1_x0_e1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_e1                     :12;	//27:16	//win_w1_y0_e1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D0C RW
	UINT32 win_w1_x1_e1                     :12;	//11:0	//win_w1_x1_e1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_e1                     :12;	//27:16	//win_w1_y1_e1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D10 RW
	UINT32 win_w0_x0_o1                     :12;	//11:0	//win_w0_x0_o1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_o1                     :12;	//27:16	//win_w0_y0_o1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D14 RW
	UINT32 win_w0_x1_o1                     :12;	//11:0	//win_w0_x1_o1
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_o1                     :12;	//27:16	//win_w0_y1_o1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D18 RW
	UINT32 win_w1_x0_o1                     :12;	//11:0	//win_w1_x0_o1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_o1                     :12;	//27:16	//win_w1_y0_o1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D1C RW
	UINT32 win_w1_x1_o1                     :12;	//11:0	//win_w1_x1_o1
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_o1                     :12;	//27:16	//win_w1_y1_o1
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D20 RW
	UINT32 win_w0_x0_e2                     :12;	//11:0	//win_w0_x0_e2
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_e2                     :12;	//27:16	//win_w0_y0_e2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D24 RW
	UINT32 win_w0_x1_e2                     :12;	//11:0	//win_w0_x1_e2
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_e2                     :12;	//27:16	//win_w0_y1_e2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D28 RW
	UINT32 win_w1_x0_e2                     :12;	//11:0	//win_w1_x0_e2
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_e2                     :12;	//27:16	//win_w1_y0_e2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D2C RW
	UINT32 win_w1_x1_e2                     :12;	//11:0	//win_w1_x1_e2
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_e2                     :12;	//27:16	//win_w1_y1_e2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D30 RW
	UINT32 win_w0_x0_o2                     :12;	//11:0	//win_w0_x0_o2
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_o2                     :12;	//27:16	//win_w0_y0_o2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D34 RW
	UINT32 win_w0_x1_o2                     :12;	//11:0	//win_w0_x1_o2
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_o2                     :12;	//27:16	//win_w0_y1_o2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D38 RW
	UINT32 win_w1_x0_o2                     :12;	//11:0	//win_w1_x0_o2
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_o2                     :12;	//27:16	//win_w1_y0_o2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D3C RW
	UINT32 win_w1_x1_o2                     :12;	//11:0	//win_w1_x1_o2
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_o2                     :12;	//27:16	//win_w1_y1_o2
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D40 RW
	UINT32 win_w0_x0_e3                     :12;	//11:0	//win_w0_x0_e3
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_e3                     :12;	//27:16	//win_w0_y0_e3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D44 RW
	UINT32 win_w0_x1_e3                     :12;	//11:0	//win_w0_x1_e3
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_e3                     :12;	//27:16	//win_w0_y1_e3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D48 RW
	UINT32 win_w1_x0_e3                     :12;	//11:0	//win_w1_x0_e3
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_e3                     :12;	//27:16	//win_w1_y0_e3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D4C RW
	UINT32 win_w1_x1_e3                     :12;	//11:0	//win_w1_x1_e3
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_e3                     :12;	//27:16	//win_w1_y1_e3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D50 RW
	UINT32 win_w0_x0_o3                     :12;	//11:0	//win_w0_x0_o3
	UINT32 resvd0                           :4;
	UINT32 win_w0_y0_o3                     :12;	//27:16	//win_w0_y0_o3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D54 RW
	UINT32 win_w0_x1_o3                     :12;	//11:0	//win_w0_x1_o3
	UINT32 resvd0                           :4;
	UINT32 win_w0_y1_o3                     :12;	//27:16	//win_w0_y1_o3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D58 RW
	UINT32 win_w1_x0_o3                     :12;	//11:0	//win_w1_x0_o3
	UINT32 resvd0                           :4;
	UINT32 win_w1_y0_o3                     :12;	//27:16	//win_w1_y0_o3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029D5C RW
	UINT32 win_w1_x1_o3                     :12;	//11:0	//win_w1_x1_o3
	UINT32 resvd0                           :4;
	UINT32 win_w1_y1_o3                     :12;	//27:16	//win_w1_y1_o3
	UINT32 resvd1                           :4;
	};
}PE_E60_DTM_LLUT_WIN_CTRL_28_T;

/*-----------------------------------------------------------------------------
                             0xc902b000L reg_obe_ctrl_000                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_debug_mode                     :4 ,	// 19:16
	reserved02                         :4 ,	// reserved
	reg_ocsc_en                        :1 ,	// 24
	reg_icsc_en                        :1 ,	// 25
	reserved03                         :5 ,	// reserved
	reg_obe_en                         :1 ;	// 31
}PE_E60_REG_OBE_CTRL_000_T;
/*-----------------------------------------------------------------------------
                             0xc902b004L reg_obe_ctrl_001                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_heigt                          :16,	// 15:0
	reg_width                          :16;	// 31:16
}PE_E60_REG_OBE_CTRL_001_T;
/*-----------------------------------------------------------------------------
                             0xc902b008L reg_obe_ctrl_002                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bg_body_hist_th                :8 ,	// 7:0
	reg_bg_head_hist_th                :8 ,	// 15:8
	reg_body_hist_th                   :8 ,	// 23:16
	reg_head_hist_th                   :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_002_T;
/*-----------------------------------------------------------------------------
                             0xc902b00cL reg_obe_ctrl_003                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_bg_txtr_hist_th                :8 ,	// 23:16
	reg_txtr_hist_th                   :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_003_T;
/*-----------------------------------------------------------------------------
                             0xc902b010L reg_obe_ctrl_004                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_prsv_ratio                 :8 ,	// 7:0
	reg_hue_prsv_ratio                 :8 ,	// 15:8
	reg_sat_prsv_en                    :1 ,	// 16
	reg_hue_prsv_en                    :1 ,	// 17
	reserved01                         :13,	// reserved
	reg_hsp_en                         :1 ;	// 31
}PE_E60_REG_OBE_CTRL_004_T;
/*-----------------------------------------------------------------------------
                             0xc902b014L reg_obe_ctrl_005                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_E60_REG_OBE_CTRL_005_T;
/*-----------------------------------------------------------------------------
                             0xc902b018L reg_obe_ind_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ind_addr_ai                    :9 ,	// 8:0
	reserved01                         :3 ,	// reserved
	reg_ind_ai                         :1 ,	// 12
	reserved02                         :2 ,	// reserved
	reg_ind_load                       :1 ;	// 15
}PE_E60_REG_OBE_IND_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc902b01cL reg_obe_ind_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ind_data_wr;	// 31:0
}PE_E60_REG_OBE_IND_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc902b020L reg_obe_ind_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ind_data_rd;	// 31:0
}PE_E60_REG_OBE_IND_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc902b024L reg_obe_ctrl_009                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_coef1                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_icsc_coef0                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_009_T;
/*-----------------------------------------------------------------------------
                             0xc902b028L reg_obe_ctrl_010                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_coef3                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_icsc_coef2                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_010_T;
/*-----------------------------------------------------------------------------
                             0xc902b02cL reg_obe_ctrl_011                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_coef5                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_icsc_coef4                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_011_T;
/*-----------------------------------------------------------------------------
                             0xc902b030L reg_obe_ctrl_012                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_coef7                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_icsc_coef6                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_012_T;
/*-----------------------------------------------------------------------------
                             0xc902b034L reg_obe_ctrl_013                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_icsc_coef8                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_013_T;
/*-----------------------------------------------------------------------------
                             0xc902b038L reg_obe_ctrl_014                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_ofst1                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_icsc_ofst0                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_014_T;
/*-----------------------------------------------------------------------------
                             0xc902b03cL reg_obe_ctrl_015                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_ofst3                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_icsc_ofst2                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_015_T;
/*-----------------------------------------------------------------------------
                             0xc902b040L reg_obe_ctrl_016                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_icsc_ofst5                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_icsc_ofst4                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_016_T;
/*-----------------------------------------------------------------------------
                             0xc902b044L reg_obe_ctrl_017                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_coef1                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_ocsc_coef0                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_017_T;
/*-----------------------------------------------------------------------------
                             0xc902b048L reg_obe_ctrl_018                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_coef3                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_ocsc_coef2                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_018_T;
/*-----------------------------------------------------------------------------
                             0xc902b04cL reg_obe_ctrl_019                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_coef5                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_ocsc_coef4                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_019_T;
/*-----------------------------------------------------------------------------
                             0xc902b050L reg_obe_ctrl_020                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_coef7                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_ocsc_coef6                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_020_T;
/*-----------------------------------------------------------------------------
                             0xc902b054L reg_obe_ctrl_021                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_ocsc_coef8                     :15;	// 30:16
}PE_E60_REG_OBE_CTRL_021_T;
/*-----------------------------------------------------------------------------
                             0xc902b058L reg_obe_ctrl_022                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_ofst1                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_ocsc_ofst0                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_022_T;
/*-----------------------------------------------------------------------------
                             0xc902b05cL reg_obe_ctrl_023                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_ofst3                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_ocsc_ofst2                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_023_T;
/*-----------------------------------------------------------------------------
                             0xc902b060L reg_obe_ctrl_024                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ocsc_ofst5                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_ocsc_ofst4                     :11;	// 26:16
}PE_E60_REG_OBE_CTRL_024_T;
/*-----------------------------------------------------------------------------
                             0xc902b064L reg_obe_ctrl_025                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_txtr_master_gain               :8 ,	// 15:8
	reg_body_master_gain               :8 ,	// 23:16
	reg_head_master_gain               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_025_T;
/*-----------------------------------------------------------------------------
                             0xc902b068L reg_obe_ctrl_026                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_final_blend_lut_y2             :8 ,	// 7:0
	reg_final_blend_lut_x2             :8 ,	// 15:8
	reg_final_blend_lut_y3             :8 ,	// 23:16
	reg_final_blend_lut_x3             :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_026_T;
/*-----------------------------------------------------------------------------
                             0xc902b06cL reg_obe_ctrl_027                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_final_blend_lut_y0             :8 ,	// 7:0
	reg_final_blend_lut_x0             :8 ,	// 15:8
	reg_final_blend_lut_y1             :8 ,	// 23:16
	reg_final_blend_lut_x1             :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_027_T;
/*-----------------------------------------------------------------------------
                             0xc902b070L reg_obe_ctrl_028                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_028_T;
/*-----------------------------------------------------------------------------
                             0xc902b074L reg_obe_ctrl_029                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_029_T;
/*-----------------------------------------------------------------------------
                             0xc902b078L reg_obe_ctrl_030                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_030_T;
/*-----------------------------------------------------------------------------
                             0xc902b07cL reg_obe_ctrl_031                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_031_T;
/*-----------------------------------------------------------------------------
                             0xc902b080L reg_obe_ctrl_032                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_032_T;
/*-----------------------------------------------------------------------------
                             0xc902b084L reg_obe_ctrl_033                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_r_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_r_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_033_T;
/*-----------------------------------------------------------------------------
                             0xc902b088L reg_obe_ctrl_034                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_034_T;
/*-----------------------------------------------------------------------------
                             0xc902b08cL reg_obe_ctrl_035                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_035_T;
/*-----------------------------------------------------------------------------
                             0xc902b090L reg_obe_ctrl_036                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_036_T;
/*-----------------------------------------------------------------------------
                             0xc902b094L reg_obe_ctrl_037                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_037_T;
/*-----------------------------------------------------------------------------
                             0xc902b098L reg_obe_ctrl_038                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_038_T;
/*-----------------------------------------------------------------------------
                             0xc902b09cL reg_obe_ctrl_039                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_g_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_g_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_039_T;
/*-----------------------------------------------------------------------------
                             0xc902b0a0L reg_obe_ctrl_040                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_040_T;
/*-----------------------------------------------------------------------------
                             0xc902b0a4L reg_obe_ctrl_041                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_041_T;
/*-----------------------------------------------------------------------------
                             0xc902b0a8L reg_obe_ctrl_042                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_042_T;
/*-----------------------------------------------------------------------------
                             0xc902b0acL reg_obe_ctrl_043                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_043_T;
/*-----------------------------------------------------------------------------
                             0xc902b0b0L reg_obe_ctrl_044                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_044_T;
/*-----------------------------------------------------------------------------
                             0xc902b0b4L reg_obe_ctrl_045                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_b_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_head_b_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_045_T;
/*-----------------------------------------------------------------------------
                             0xc902b0b8L reg_obe_ctrl_046                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_046_T;
/*-----------------------------------------------------------------------------
                             0xc902b0bcL reg_obe_ctrl_047                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_047_T;
/*-----------------------------------------------------------------------------
                             0xc902b0c0L reg_obe_ctrl_048                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_048_T;
/*-----------------------------------------------------------------------------
                             0xc902b0c4L reg_obe_ctrl_049                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_049_T;
/*-----------------------------------------------------------------------------
                             0xc902b0c8L reg_obe_ctrl_050                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_050_T;
/*-----------------------------------------------------------------------------
                             0xc902b0ccL reg_obe_ctrl_051                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_r_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_r_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_051_T;
/*-----------------------------------------------------------------------------
                             0xc902b0d0L reg_obe_ctrl_052                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_052_T;
/*-----------------------------------------------------------------------------
                             0xc902b0d4L reg_obe_ctrl_053                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_053_T;
/*-----------------------------------------------------------------------------
                             0xc902b0d8L reg_obe_ctrl_054                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_054_T;
/*-----------------------------------------------------------------------------
                             0xc902b0dcL reg_obe_ctrl_055                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_055_T;
/*-----------------------------------------------------------------------------
                             0xc902b0e0L reg_obe_ctrl_056                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_056_T;
/*-----------------------------------------------------------------------------
                             0xc902b0e4L reg_obe_ctrl_057                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_g_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_g_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_057_T;
/*-----------------------------------------------------------------------------
                             0xc902b0e8L reg_obe_ctrl_058                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_058_T;
/*-----------------------------------------------------------------------------
                             0xc902b0ecL reg_obe_ctrl_059                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_059_T;
/*-----------------------------------------------------------------------------
                             0xc902b0f0L reg_obe_ctrl_060                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_060_T;
/*-----------------------------------------------------------------------------
                             0xc902b0f4L reg_obe_ctrl_061                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_061_T;
/*-----------------------------------------------------------------------------
                             0xc902b0f8L reg_obe_ctrl_062                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_062_T;
/*-----------------------------------------------------------------------------
                             0xc902b0fcL reg_obe_ctrl_063                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_b_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_body_b_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_063_T;
/*-----------------------------------------------------------------------------
                             0xc902b100L reg_obe_ctrl_064                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_064_T;
/*-----------------------------------------------------------------------------
                             0xc902b104L reg_obe_ctrl_065                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_065_T;
/*-----------------------------------------------------------------------------
                             0xc902b108L reg_obe_ctrl_066                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_066_T;
/*-----------------------------------------------------------------------------
                             0xc902b10cL reg_obe_ctrl_067                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_067_T;
/*-----------------------------------------------------------------------------
                             0xc902b110L reg_obe_ctrl_068                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_068_T;
/*-----------------------------------------------------------------------------
                             0xc902b114L reg_obe_ctrl_069                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_r_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_r_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_069_T;
/*-----------------------------------------------------------------------------
                             0xc902b118L reg_obe_ctrl_070                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_070_T;
/*-----------------------------------------------------------------------------
                             0xc902b11cL reg_obe_ctrl_071                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_071_T;
/*-----------------------------------------------------------------------------
                             0xc902b120L reg_obe_ctrl_072                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_072_T;
/*-----------------------------------------------------------------------------
                             0xc902b124L reg_obe_ctrl_073                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_073_T;
/*-----------------------------------------------------------------------------
                             0xc902b128L reg_obe_ctrl_074                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_074_T;
/*-----------------------------------------------------------------------------
                             0xc902b12cL reg_obe_ctrl_075                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_g_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_g_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_075_T;
/*-----------------------------------------------------------------------------
                             0xc902b130L reg_obe_ctrl_076                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_076_T;
/*-----------------------------------------------------------------------------
                             0xc902b134L reg_obe_ctrl_077                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_077_T;
/*-----------------------------------------------------------------------------
                             0xc902b138L reg_obe_ctrl_078                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_078_T;
/*-----------------------------------------------------------------------------
                             0xc902b13cL reg_obe_ctrl_079                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_079_T;
/*-----------------------------------------------------------------------------
                             0xc902b140L reg_obe_ctrl_080                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_080_T;
/*-----------------------------------------------------------------------------
                             0xc902b144L reg_obe_ctrl_081                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_potr_bg_b_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_potr_bg_b_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_081_T;
/*-----------------------------------------------------------------------------
                             0xc902b148L reg_obe_ctrl_082                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_gain_lut_y0               :8 ,	// 7:0
	reg_head_gain_lut_x0               :8 ,	// 15:8
	reg_head_gain_lut_y1               :8 ,	// 23:16
	reg_head_gain_lut_x1               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_082_T;
/*-----------------------------------------------------------------------------
                             0xc902b14cL reg_obe_ctrl_083                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_bg_gain_lut_y0            :8 ,	// 7:0
	reg_head_bg_gain_lut_x0            :8 ,	// 15:8
	reg_head_bg_gain_lut_y1            :8 ,	// 23:16
	reg_head_bg_gain_lut_x1            :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_083_T;
/*-----------------------------------------------------------------------------
                             0xc902b150L reg_obe_ctrl_084                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_gain_lut_y0               :8 ,	// 7:0
	reg_body_gain_lut_x0               :8 ,	// 15:8
	reg_body_gain_lut_y1               :8 ,	// 23:16
	reg_body_gain_lut_x1               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_084_T;
/*-----------------------------------------------------------------------------
                             0xc902b154L reg_obe_ctrl_085                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_bg_gain_lut_y0            :8 ,	// 7:0
	reg_body_bg_gain_lut_x0            :8 ,	// 15:8
	reg_body_bg_gain_lut_y1            :8 ,	// 23:16
	reg_body_bg_gain_lut_x1            :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_085_T;
/*-----------------------------------------------------------------------------
                             0xc902b158L reg_obe_ctrl_086                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_head_lut_y2               :8 ,	// 7:0
	reg_body_head_lut_x2               :8 ,	// 15:8
	reg_body_head_lut_y3               :8 ,	// 23:16
	reg_body_head_lut_x3               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_086_T;
/*-----------------------------------------------------------------------------
                             0xc902b15cL reg_obe_ctrl_087                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_body_head_lut_y0               :8 ,	// 7:0
	reg_body_head_lut_x0               :8 ,	// 15:8
	reg_body_head_lut_y1               :8 ,	// 23:16
	reg_body_head_lut_x1               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_087_T;
/*-----------------------------------------------------------------------------
                             0xc902b160L reg_obe_ctrl_088                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_body_lut_y2               :8 ,	// 7:0
	reg_head_body_lut_x2               :8 ,	// 15:8
	reg_head_body_lut_y3               :8 ,	// 23:16
	reg_head_body_lut_x3               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_088_T;
/*-----------------------------------------------------------------------------
                             0xc902b164L reg_obe_ctrl_089                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_head_body_lut_y0               :8 ,	// 7:0
	reg_head_body_lut_x0               :8 ,	// 15:8
	reg_head_body_lut_y1               :8 ,	// 23:16
	reg_head_body_lut_x1               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_089_T;
/*-----------------------------------------------------------------------------
                             0xc902b168L reg_obe_ctrl_090                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_090_T;
/*-----------------------------------------------------------------------------
                             0xc902b16cL reg_obe_ctrl_091                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_091_T;
/*-----------------------------------------------------------------------------
                             0xc902b170L reg_obe_ctrl_092                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_092_T;
/*-----------------------------------------------------------------------------
                             0xc902b174L reg_obe_ctrl_093                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_093_T;
/*-----------------------------------------------------------------------------
                             0xc902b178L reg_obe_ctrl_094                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_094_T;
/*-----------------------------------------------------------------------------
                             0xc902b17cL reg_obe_ctrl_095                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_r_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_r_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_095_T;
/*-----------------------------------------------------------------------------
                             0xc902b180L reg_obe_ctrl_096                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_096_T;
/*-----------------------------------------------------------------------------
                             0xc902b184L reg_obe_ctrl_097                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_097_T;
/*-----------------------------------------------------------------------------
                             0xc902b188L reg_obe_ctrl_098                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_098_T;
/*-----------------------------------------------------------------------------
                             0xc902b18cL reg_obe_ctrl_099                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_099_T;
/*-----------------------------------------------------------------------------
                             0xc902b190L reg_obe_ctrl_100                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_100_T;
/*-----------------------------------------------------------------------------
                             0xc902b194L reg_obe_ctrl_101                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_g_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_g_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_101_T;
/*-----------------------------------------------------------------------------
                             0xc902b198L reg_obe_ctrl_102                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y0                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x0                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_102_T;
/*-----------------------------------------------------------------------------
                             0xc902b19cL reg_obe_ctrl_103                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x1                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_103_T;
/*-----------------------------------------------------------------------------
                             0xc902b1a0L reg_obe_ctrl_104                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y2                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x2                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_104_T;
/*-----------------------------------------------------------------------------
                             0xc902b1a4L reg_obe_ctrl_105                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x3                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_105_T;
/*-----------------------------------------------------------------------------
                             0xc902b1a8L reg_obe_ctrl_106                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y4                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x4                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_106_T;
/*-----------------------------------------------------------------------------
                             0xc902b1acL reg_obe_ctrl_107                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_b_lut_y5                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_txtr_b_lut_x5                  :10;	// 25:16
}PE_E60_REG_OBE_CTRL_107_T;
/*-----------------------------------------------------------------------------
                             0xc902b1b0L reg_obe_ctrl_108                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_108_T;
/*-----------------------------------------------------------------------------
                             0xc902b1b4L reg_obe_ctrl_109                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_109_T;
/*-----------------------------------------------------------------------------
                             0xc902b1b8L reg_obe_ctrl_110                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_110_T;
/*-----------------------------------------------------------------------------
                             0xc902b1bcL reg_obe_ctrl_111                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_111_T;
/*-----------------------------------------------------------------------------
                             0xc902b1c0L reg_obe_ctrl_112                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_112_T;
/*-----------------------------------------------------------------------------
                             0xc902b1c4L reg_obe_ctrl_113                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_r_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_r_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_113_T;
/*-----------------------------------------------------------------------------
                             0xc902b1c8L reg_obe_ctrl_114                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_114_T;
/*-----------------------------------------------------------------------------
                             0xc902b1ccL reg_obe_ctrl_115                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_115_T;
/*-----------------------------------------------------------------------------
                             0xc902b1d0L reg_obe_ctrl_116                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_116_T;
/*-----------------------------------------------------------------------------
                             0xc902b1d4L reg_obe_ctrl_117                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_117_T;
/*-----------------------------------------------------------------------------
                             0xc902b1d8L reg_obe_ctrl_118                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_118_T;
/*-----------------------------------------------------------------------------
                             0xc902b1dcL reg_obe_ctrl_119                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_g_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_g_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_119_T;
/*-----------------------------------------------------------------------------
                             0xc902b1e0L reg_obe_ctrl_120                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y0               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x0               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_120_T;
/*-----------------------------------------------------------------------------
                             0xc902b1e4L reg_obe_ctrl_121                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y1               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x1               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_121_T;
/*-----------------------------------------------------------------------------
                             0xc902b1e8L reg_obe_ctrl_122                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y2               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x2               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_122_T;
/*-----------------------------------------------------------------------------
                             0xc902b1ecL reg_obe_ctrl_123                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y3               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x3               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_123_T;
/*-----------------------------------------------------------------------------
                             0xc902b1f0L reg_obe_ctrl_124                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y4               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x4               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_124_T;
/*-----------------------------------------------------------------------------
                             0xc902b1f4L reg_obe_ctrl_125                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lnds_bg_b_lut_y5               :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_lnds_bg_b_lut_x5               :10;	// 25:16
}PE_E60_REG_OBE_CTRL_125_T;
/*-----------------------------------------------------------------------------
                             0xc902b1f8L reg_obe_ctrl_126                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_gain_lut_y0               :8 ,	// 7:0
	reg_txtr_gain_lut_x0               :8 ,	// 15:8
	reg_txtr_gain_lut_y1               :8 ,	// 23:16
	reg_txtr_gain_lut_x1               :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_126_T;
/*-----------------------------------------------------------------------------
                             0xc902b1fcL reg_obe_ctrl_127                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_txtr_bg_gain_lut_y0            :8 ,	// 7:0
	reg_txtr_bg_gain_lut_x0            :8 ,	// 15:8
	reg_txtr_bg_gain_lut_y1            :8 ,	// 23:16
	reg_txtr_bg_gain_lut_x1            :8 ;	// 31:24
}PE_E60_REG_OBE_CTRL_127_T;
/*-----------------------------------------------------------------------------
                             0xc902b200L reg_obe_ctrl_128                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_y0                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_w0_x0                      :13,	// 28:16
	reserved02                         :2 ,	// reserved
	reg_win_enable                     :1 ;	// 31
}PE_E60_REG_OBE_CTRL_128_T;
/*-----------------------------------------------------------------------------
                             0xc902b204L reg_obe_ctrl_129                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_y1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_w0_x1                      :13,	// 28:16
	reserved02                         :2 ,	// reserved
	reg_win0_enable                    :1 ;	// 31
}PE_E60_REG_OBE_CTRL_129_T;
/*-----------------------------------------------------------------------------
                             0xc902b208L reg_obe_ctrl_130                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_y0                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_w1_x0                      :13,	// 28:16
	reserved02                         :2 ,	// reserved
	reg_win1_enable                    :1 ;	// 31
}PE_E60_REG_OBE_CTRL_130_T;
/*-----------------------------------------------------------------------------
                             0xc902b20cL reg_obe_ctrl_131                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_y1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_w1_x1                      :13,	// 28:16
	reserved02                         :2 ,	// reserved
	reg_win_outside                    :1 ;	// 31
}PE_E60_REG_OBE_CTRL_131_T;

typedef struct {
	PE_E60_SHP_CORE_CTRL_00_T                    shp_core_ctrl_00;	//0xC902C000
	PE_E60_SHP_CORE0_CTRL_01_T                  shp_core0_ctrl_01;	//0xC902C004
	PE_E60_SHP_CORE1_CTRL_01_T                  shp_core1_ctrl_01;	//0xC902C008
	PE_E60_SHP_CORE_CTRL_02_T                    shp_core_ctrl_02;	//0xC902C00C
	PE_E60_SHP_CORE_CTRL_03_T                    shp_core_ctrl_03;	//0xC902C010
	PE_E60_SHP_CORE_CTRL_04_T                    shp_core_ctrl_04;	//0xC902C014
	UINT32                                                    reserved0;	//0xC902C018
	UINT32                                                    reserved1;	//0xC902C01C
	UINT32                                                    reserved2;	//0xC902C020
	UINT32                                                    reserved3;	//0xC902C024
	UINT32                                                    reserved4;	//0xC902C028
	UINT32                                                    reserved5;	//0xC902C02C
	UINT32                                                    reserved6;	//0xC902C030
	UINT32                                                    reserved7;	//0xC902C034
	UINT32                                                    reserved8;	//0xC902C038
	UINT32                                                    reserved9;	//0xC902C03C
	PE_E60_SHP_PAT_GEN_CTRL_00_T              shp_pat_gen_ctrl_00;	//0xC902C040
	PE_E60_SHP_GOS_CTRL_00_T                      shp_gos_ctrl_00;	//0xC902C044
	PE_E60_SHP_NEW_FD_CTRL_00_T                shp_new_fd_ctrl_00;	//0xC902C048
	PE_E60_SHP_NEW_FD_CTRL_01_T                shp_new_fd_ctrl_01;	//0xC902C04C
	PE_E60_SHP_NEW_FD_CTRL_02_T                shp_new_fd_ctrl_02;	//0xC902C050
	PE_E60_SHP_NEW_FD_CTRL_03_T                shp_new_fd_ctrl_03;	//0xC902C054
	PE_E60_SHP_NEW_FD_CTRL_04_T                shp_new_fd_ctrl_04;	//0xC902C058
	PE_E60_SHP_TEXT_REGION_MAP_00_T        shp_text_region_map_00;	//0xC902C05C
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_00_T shp_core0_sync_dly_ctrl_00;	//0xC902C060
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_01_T shp_core0_sync_dly_ctrl_01;	//0xC902C064
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_02_T shp_core0_sync_dly_ctrl_02;	//0xC902C068
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_03_T shp_core0_sync_dly_ctrl_03;	//0xC902C06C
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_04_T shp_core0_sync_dly_ctrl_04;	//0xC902C070
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_05_T shp_core0_sync_dly_ctrl_05;	//0xC902C074
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_06_T shp_core0_sync_dly_ctrl_06;	//0xC902C078
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_07_T shp_core0_sync_dly_ctrl_07;	//0xC902C07C
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_08_T shp_core0_sync_dly_ctrl_08;	//0xC902C080
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_09_T shp_core0_sync_dly_ctrl_09;	//0xC902C084
	PE_E60_SHP_CORE0_SYNC_DLY_CTRL_0A_T shp_core0_sync_dly_ctrl_0a;	//0xC902C088
	UINT32                                                   reserved10;	//0xC902C08C
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_00_T shp_core1_sync_dly_ctrl_00;	//0xC902C090
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_01_T shp_core1_sync_dly_ctrl_01;	//0xC902C094
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_02_T shp_core1_sync_dly_ctrl_02;	//0xC902C098
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_03_T shp_core1_sync_dly_ctrl_03;	//0xC902C09C
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_04_T shp_core1_sync_dly_ctrl_04;	//0xC902C0A0
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_05_T shp_core1_sync_dly_ctrl_05;	//0xC902C0A4
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_06_T shp_core1_sync_dly_ctrl_06;	//0xC902C0A8
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_07_T shp_core1_sync_dly_ctrl_07;	//0xC902C0AC
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_08_T shp_core1_sync_dly_ctrl_08;	//0xC902C0B0
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_09_T shp_core1_sync_dly_ctrl_09;	//0xC902C0B4
	PE_E60_SHP_CORE1_SYNC_DLY_CTRL_0A_T shp_core1_sync_dly_ctrl_0a;	//0xC902C0B8
	UINT32                                                   reserved11;	//0xC902C0BC
	PE_E60_SHP_CORE0_ROI_MASK_CTRL_00_T shp_core0_roi_mask_ctrl_00;	//0xC902C0C0
	PE_E60_SHP_CORE0_ROI_MASK_CTRL_01_T shp_core0_roi_mask_ctrl_01;	//0xC902C0C4
	PE_E60_SHP_CORE0_ROI_MASK_CTRL_02_T shp_core0_roi_mask_ctrl_02;	//0xC902C0C8
	UINT32                                                   reserved12;	//0xC902C0CC
	PE_E60_SHP_CORE1_ROI_MASK_CTRL_00_T shp_core1_roi_mask_ctrl_00;	//0xC902C0D0
	PE_E60_SHP_CORE1_ROI_MASK_CTRL_01_T shp_core1_roi_mask_ctrl_01;	//0xC902C0D4
	PE_E60_SHP_CORE1_ROI_MASK_CTRL_02_T shp_core1_roi_mask_ctrl_02;	//0xC902C0D8
	UINT32                                                   reserved13;	//0xC902C0DC
	UINT32                                                   reserved14;	//0xC902C0E0
	UINT32                                                   reserved15;	//0xC902C0E4
	UINT32                                                   reserved16;	//0xC902C0E8
	UINT32                                                   reserved17;	//0xC902C0EC
	UINT32                                                   reserved18;	//0xC902C0F0
	UINT32                                                   reserved19;	//0xC902C0F4
	UINT32                                                   reserved20;	//0xC902C0F8
	UINT32                                                   reserved21;	//0xC902C0FC
	PE_E60_SHP_ESF_CTRL_00_T                      shp_esf_ctrl_00;	//0xC902C100
	PE_E60_SHP_ESF_CTRL_01_T                      shp_esf_ctrl_01;	//0xC902C104
	PE_E60_SHP_ESF_CTRL_02_T                      shp_esf_ctrl_02;	//0xC902C108
	UINT32                                                   reserved22;	//0xC902C10C
	PE_E60_SHP_CORE0_ESF_WIN_CTRL_00_T  shp_core0_esf_win_ctrl_00;	//0xC902C110
	PE_E60_SHP_CORE0_ESF_WIN_CTRL_01_T  shp_core0_esf_win_ctrl_01;	//0xC902C114
	PE_E60_SHP_CORE0_ESF_WIN_CTRL_02_T  shp_core0_esf_win_ctrl_02;	//0xC902C118
	PE_E60_SHP_CORE0_ESF_WIN_CTRL_03_T  shp_core0_esf_win_ctrl_03;	//0xC902C11C
	PE_E60_SHP_CORE0_ESF_WIN_CTRL_04_T  shp_core0_esf_win_ctrl_04;	//0xC902C120
	UINT32                                                   reserved23;	//0xC902C124
	UINT32                                                   reserved24;	//0xC902C128
	UINT32                                                   reserved25;	//0xC902C12C
	PE_E60_SHP_CORE1_ESF_WIN_CTRL_00_T  shp_core1_esf_win_ctrl_00;	//0xC902C130
	PE_E60_SHP_CORE1_ESF_WIN_CTRL_01_T  shp_core1_esf_win_ctrl_01;	//0xC902C134
	PE_E60_SHP_CORE1_ESF_WIN_CTRL_02_T  shp_core1_esf_win_ctrl_02;	//0xC902C138
	PE_E60_SHP_CORE1_ESF_WIN_CTRL_03_T  shp_core1_esf_win_ctrl_03;	//0xC902C13C
	PE_E60_SHP_CORE1_ESF_WIN_CTRL_04_T  shp_core1_esf_win_ctrl_04;	//0xC902C140
	UINT32                                                   reserved26;	//0xC902C144
	UINT32                                                   reserved27;	//0xC902C148
	UINT32                                                   reserved28;	//0xC902C14C
	PE_E60_SHP_DP_CTRL_00_T                        shp_dp_ctrl_00;	//0xC902C150
	UINT32                                                   reserved29;	//0xC902C154
	UINT32                                                   reserved30;	//0xC902C158
	UINT32                                                   reserved31;	//0xC902C15C
	PE_E60_SHP_FD_CTRL_00_T                        shp_fd_ctrl_00;	//0xC902C160
	PE_E60_SHP_FD_CTRL_01_T                        shp_fd_ctrl_01;	//0xC902C164
	PE_E60_SHP_FD_CTRL_02_T                        shp_fd_ctrl_02;	//0xC902C168
	PE_E60_SHP_FD_CTRL_03_T                        shp_fd_ctrl_03;	//0xC902C16C
	PE_E60_SHP_FD_CTRL_04_T                        shp_fd_ctrl_04;	//0xC902C170
	PE_E60_SHP_FD_CTRL_05_T                        shp_fd_ctrl_05;	//0xC902C174
	PE_E60_SHP_FD_CTRL_06_T                        shp_fd_ctrl_06;	//0xC902C178
	PE_E60_SHP_FD_CTRL_07_T                        shp_fd_ctrl_07;	//0xC902C17C
	PE_E60_SHP_FD_CTRL_08_T                        shp_fd_ctrl_08;	//0xC902C180
	PE_E60_SHP_FD_CTRL_09_T                        shp_fd_ctrl_09;	//0xC902C184
	PE_E60_SHP_FD_CTRL_0A_T                        shp_fd_ctrl_0a;	//0xC902C188
	PE_E60_SHP_FD_CTRL_0B_T                        shp_fd_ctrl_0b;	//0xC902C18C
	PE_E60_SHP_FD_CTRL_0C_T                        shp_fd_ctrl_0c;	//0xC902C190
	PE_E60_SHP_FD_CTRL_0D_T                        shp_fd_ctrl_0d;	//0xC902C194
	PE_E60_SHP_FD_CTRL_0E_T                        shp_fd_ctrl_0e;	//0xC902C198
	PE_E60_SHP_FD_CTRL_0F_T                        shp_fd_ctrl_0f;	//0xC902C19C
	PE_E60_SHP_FD_CTRL_10_T                        shp_fd_ctrl_10;	//0xC902C1A0
	PE_E60_SHP_FD_CTRL_11_T                        shp_fd_ctrl_11;	//0xC902C1A4
	PE_E60_SHP_FD_CTRL_12_T                        shp_fd_ctrl_12;	//0xC902C1A8
	PE_E60_SHP_FD_CTRL_13_T                        shp_fd_ctrl_13;	//0xC902C1AC
	PE_E60_SHP_FD_CTRL_14_T                        shp_fd_ctrl_14;	//0xC902C1B0
	PE_E60_SHP_FD_CTRL_15_T                        shp_fd_ctrl_15;	//0xC902C1B4
	PE_E60_SHP_FD_CTRL_16_T                        shp_fd_ctrl_16;	//0xC902C1B8
	UINT32                                                   reserved32;	//0xC902C1BC
	PE_E60_SHP_MP_CTRL_00_T                        shp_mp_ctrl_00;	//0xC902C1C0
	PE_E60_SHP_MP_CTRL_01_T                        shp_mp_ctrl_01;	//0xC902C1C4
	PE_E60_SHP_MP_CTRL_02_T                        shp_mp_ctrl_02;	//0xC902C1C8
	PE_E60_SHP_MP_CTRL_03_T                        shp_mp_ctrl_03;	//0xC902C1CC
	PE_E60_SHP_MP_CTRL_04_T                        shp_mp_ctrl_04;	//0xC902C1D0
	PE_E60_SHP_MP_CTRL_05_T                        shp_mp_ctrl_05;	//0xC902C1D4
	PE_E60_SHP_MP_CTRL_06_T                        shp_mp_ctrl_06;	//0xC902C1D8
	PE_E60_SHP_MP_CTRL_07_T                        shp_mp_ctrl_07;	//0xC902C1DC
	PE_E60_SHP_MP_CTRL_08_T                        shp_mp_ctrl_08;	//0xC902C1E0
	PE_E60_SHP_MP_CTRL_09_T                        shp_mp_ctrl_09;	//0xC902C1E4
	PE_E60_SHP_MP_CTRL_0A_T                        shp_mp_ctrl_0a;	//0xC902C1E8
	PE_E60_SHP_MP_CTRL_0B_T                        shp_mp_ctrl_0b;	//0xC902C1EC
	PE_E60_SHP_MP_CTRL_0C_T                        shp_mp_ctrl_0c;	//0xC902C1F0
	PE_E60_SHP_APL_CTRL_00_T                      shp_apl_ctrl_00;	//0xC902C1F4
	UINT32                                                   reserved33;	//0xC902C1F8
	UINT32                                                   reserved34;	//0xC902C1FC
	PE_E60_SHP_LC_CTRL_00_T                        shp_lc_ctrl_00;	//0xC902C200
	PE_E60_SHP_LC_CTRL_01_T                        shp_lc_ctrl_01;	//0xC902C204
	PE_E60_SHP_LC_CTRL_02_T                        shp_lc_ctrl_02;	//0xC902C208
	PE_E60_SHP_LC_CTRL_03_T                        shp_lc_ctrl_03;	//0xC902C20C
	PE_E60_SHP_LC_CTRL_04_T                        shp_lc_ctrl_04;	//0xC902C210
	UINT32                                                   reserved35;	//0xC902C214
	UINT32                                                   reserved36;	//0xC902C218
	UINT32                                                   reserved37;	//0xC902C21C
	PE_E60_SHP_DER_CTRL_00_T                      shp_der_ctrl_00;	//0xC902C220
	PE_E60_SHP_DER_CTRL_01_T                      shp_der_ctrl_01;	//0xC902C224
	PE_E60_SHP_DER_CTRL_02_T                      shp_der_ctrl_02;	//0xC902C228
	PE_E60_SHP_DER_CTRL_03_T                      shp_der_ctrl_03;	//0xC902C22C
	PE_E60_SHP_DER_CTRL_04_T                      shp_der_ctrl_04;	//0xC902C230
	PE_E60_SHP_DER_CTRL_05_T                      shp_der_ctrl_05;	//0xC902C234
	PE_E60_SHP_DER_CTRL_06_T                      shp_der_ctrl_06;	//0xC902C238
	PE_E60_SHP_DER_CTRL_07_T                      shp_der_ctrl_07;	//0xC902C23C
	PE_E60_SHP_SP_CTRL_00_T                        shp_sp_ctrl_00;	//0xC902C240
	PE_E60_SHP_SP_CTRL_01_T                        shp_sp_ctrl_01;	//0xC902C244
	PE_E60_SHP_SP_CTRL_02_T                        shp_sp_ctrl_02;	//0xC902C248
	PE_E60_SHP_SP_CTRL_03_T                        shp_sp_ctrl_03;	//0xC902C24C
	PE_E60_SHP_SP_CTRL_04_T                        shp_sp_ctrl_04;	//0xC902C250
	PE_E60_SHP_SP_CTRL_05_T                        shp_sp_ctrl_05;	//0xC902C254
	PE_E60_SHP_SP_CTRL_06_T                        shp_sp_ctrl_06;	//0xC902C258
	PE_E60_SHP_SP_CTRL_07_T                        shp_sp_ctrl_07;	//0xC902C25C
	PE_E60_SHP_SP_CTRL_08_T                        shp_sp_ctrl_08;	//0xC902C260
	PE_E60_SHP_SP_CTRL_09_T                        shp_sp_ctrl_09;	//0xC902C264
	PE_E60_SHP_SP_CTRL_0A_T                        shp_sp_ctrl_0a;	//0xC902C268
	PE_E60_SHP_SP_CTRL_0B_T                        shp_sp_ctrl_0b;	//0xC902C26C
	PE_E60_SHP_SP_CTRL_0C_T                        shp_sp_ctrl_0c;	//0xC902C270
	UINT32                                                   reserved38;	//0xC902C274
	UINT32                                                   reserved39;	//0xC902C278
	UINT32                                                   reserved40;	//0xC902C27C
	PE_E60_SHP_PTI_CTRL_00_T                      shp_pti_ctrl_00;	//0xC902C280
	PE_E60_SHP_PTI_CTRL_01_T                      shp_pti_ctrl_01;	//0xC902C284
	PE_E60_SHP_PTI_CTRL_02_T                      shp_pti_ctrl_02;	//0xC902C288
	PE_E60_SHP_PTI_CTRL_03_T                      shp_pti_ctrl_03;	//0xC902C28C
	PE_E60_SHP_STI_CTRL_00_T                      shp_sti_ctrl_00;	//0xC902C290
	UINT32                                                   reserved41;	//0xC902C294
	UINT32                                                   reserved42;	//0xC902C298
	UINT32                                                   reserved43;	//0xC902C29C
	PE_E60_SHP_TGEN_CTRL_00_T                    shp_tgen_ctrl_00;	//0xC902C2A0
	PE_E60_SHP_TGEN_CTRL_01_T                    shp_tgen_ctrl_01;	//0xC902C2A4
	PE_E60_SHP_TGEN_CTRL_02_T                    shp_tgen_ctrl_02;	//0xC902C2A8
	PE_E60_SHP_CORE0_TGEN_CTRL_03_C0_T  shp_core0_tgen_ctrl_03_c0;	//0xC902C2AC
	PE_E60_SHP_CORE0_TGEN_CTRL_03_C1_T  shp_core0_tgen_ctrl_03_c1;	//0xC902C2B0
	PE_E60_SHP_CORE1_TGEN_CTRL_03_C0_T  shp_core1_tgen_ctrl_03_c0;	//0xC902C2B4
	PE_E60_SHP_CORE1_TGEN_CTRL_03_C1_T  shp_core1_tgen_ctrl_03_c1;	//0xC902C2B8
	PE_E60_SHP_TGEN_CTRL_04_T                    shp_tgen_ctrl_04;	//0xC902C2BC
	PE_E60_SHP_TGEN_CTRL_05_T                    shp_tgen_ctrl_05;	//0xC902C2C0
	PE_E60_SHP_TGEN_CTRL_06_T                    shp_tgen_ctrl_06;	//0xC902C2C4
	PE_E60_SHP_TGEN_CTRL_07_T                    shp_tgen_ctrl_07;	//0xC902C2C8
	PE_E60_SHP_TGEN_CTRL_08_T                    shp_tgen_ctrl_08;	//0xC902C2CC
	PE_E60_SHP_TGEN_CTRL_09_T                    shp_tgen_ctrl_09;	//0xC902C2D0
	PE_E60_SHP_TGEN_CTRL_0A_T                    shp_tgen_ctrl_0a;	//0xC902C2D4
	PE_E60_SHP_TGEN_CTRL_0B_T                    shp_tgen_ctrl_0b;	//0xC902C2D8
	UINT32                                                   reserved44;	//0xC902C2DC
	PE_E60_SHP_SNR_CTRL_00_T                      shp_snr_ctrl_00;	//0xC902C2E0
	UINT32                                                   reserved45;	//0xC902C2E4
	UINT32                                                   reserved46;	//0xC902C2E8
	UINT32                                                   reserved47;	//0xC902C2EC
	PE_E60_SHP_DCTP_CTRL_00_T                    shp_dctp_ctrl_00;	//0xC902C2F0
	PE_E60_SHP_DCTP_CTRL_01_T                    shp_dctp_ctrl_01;	//0xC902C2F4
	PE_E60_SHP_DCTP_CTRL_02_T                    shp_dctp_ctrl_02;	//0xC902C2F8
	PE_E60_SHP_DCTP_CTRL_03_T                    shp_dctp_ctrl_03;	//0xC902C2FC
	PE_E60_SHP_DCTP_CTRL_04_T                    shp_dctp_ctrl_04;	//0xC902C300
	PE_E60_SHP_DCTP_CTRL_05_T                    shp_dctp_ctrl_05;	//0xC902C304
	PE_E60_SHP_DCTP_CTRL_06_T                    shp_dctp_ctrl_06;	//0xC902C308
	PE_E60_SHP_DCTP_CTRL_07_T                    shp_dctp_ctrl_07;	//0xC902C30C
	PE_E60_SHP_DCTP_CTRL_08_T                    shp_dctp_ctrl_08;	//0xC902C310
	PE_E60_SHP_DCTP_CTRL_09_T                    shp_dctp_ctrl_09;	//0xC902C314
	PE_E60_SHP_DCTP_CTRL_0A_T                    shp_dctp_ctrl_0a;	//0xC902C318
	PE_E60_SHP_DCTP_CTRL_0B_T                    shp_dctp_ctrl_0b;	//0xC902C31C
	PE_E60_SHP_DCTP_CTRL_0C_T                    shp_dctp_ctrl_0c;	//0xC902C320
	PE_E60_SHP_DCTP_CTRL_0D_T                    shp_dctp_ctrl_0d;	//0xC902C324
	PE_E60_SHP_DCTP_CTRL_0E_T                    shp_dctp_ctrl_0e;	//0xC902C328
	PE_E60_SHP_DCTP_CTRL_0F_T                    shp_dctp_ctrl_0f;	//0xC902C32C
	PE_E60_SHP_DCTP_CTRL_10_T                    shp_dctp_ctrl_10;	//0xC902C330
	PE_E60_SHP_DCTP_CTRL_11_T                    shp_dctp_ctrl_11;	//0xC902C334
	PE_E60_SHP_DCTP_CTRL_12_T                    shp_dctp_ctrl_12;	//0xC902C338
	PE_E60_SHP_DCTP_CTRL_13_T                    shp_dctp_ctrl_13;	//0xC902C33C
	PE_E60_SHP_DCTP_CTRL_14_T                    shp_dctp_ctrl_14;	//0xC902C340
	PE_E60_SHP_DCTP_CTRL_15_T                    shp_dctp_ctrl_15;	//0xC902C344
	PE_E60_SHP_DCTP_CTRL_16_T                    shp_dctp_ctrl_16;	//0xC902C348
	PE_E60_SHP_DCTP_CTRL_17_T                    shp_dctp_ctrl_17;	//0xC902C34C
	PE_E60_SHP_DCTP_CTRL_18_T                    shp_dctp_ctrl_18;	//0xC902C350
	PE_E60_SHP_DCTP_CTRL_19_T                    shp_dctp_ctrl_19;	//0xC902C354
	PE_E60_SHP_DCTP_CTRL_1A_T                    shp_dctp_ctrl_1a;	//0xC902C358
	PE_E60_SHP_DCTP_CTRL_1B_T                    shp_dctp_ctrl_1b;	//0xC902C35C
	PE_E60_SHP_DCTP_CTRL_1C_T                    shp_dctp_ctrl_1c;	//0xC902C360
	PE_E60_SHP_DCTP_CTRL_1D_T                    shp_dctp_ctrl_1d;	//0xC902C364
	PE_E60_SHP_DCTP_CTRL_1E_T                    shp_dctp_ctrl_1e;	//0xC902C368
	PE_E60_SHP_DCTP_CTRL_1F_T                    shp_dctp_ctrl_1f;	//0xC902C36C
	PE_E60_SHP_NNTG_CTRL_00_T                    shp_nntg_ctrl_00;	//0xC902C370
	PE_E60_SHP_CORE0_NNTG_CTRL_01_C0_T  shp_core0_nntg_ctrl_01_c0;	//0xC902C374
	PE_E60_SHP_CORE0_NNTG_CTRL_02_C0_T  shp_core0_nntg_ctrl_02_c0;	//0xC902C378
	PE_E60_SHP_CORE0_NNTG_CTRL_03_C0_T  shp_core0_nntg_ctrl_03_c0;	//0xC902C37C
	PE_E60_SHP_CORE0_NNTG_CTRL_04_C0_T  shp_core0_nntg_ctrl_04_c0;	//0xC902C380
	PE_E60_SHP_CORE0_NNTG_CTRL_05_C0_T  shp_core0_nntg_ctrl_05_c0;	//0xC902C384
	PE_E60_SHP_CORE0_NNTG_CTRL_01_C1_T  shp_core0_nntg_ctrl_01_c1;	//0xC902C388
	PE_E60_SHP_CORE0_NNTG_CTRL_02_C1_T  shp_core0_nntg_ctrl_02_c1;	//0xC902C38C
	PE_E60_SHP_CORE0_NNTG_CTRL_03_C1_T  shp_core0_nntg_ctrl_03_c1;	//0xC902C390
	PE_E60_SHP_CORE0_NNTG_CTRL_04_C1_T  shp_core0_nntg_ctrl_04_c1;	//0xC902C394
	PE_E60_SHP_CORE0_NNTG_CTRL_05_C1_T  shp_core0_nntg_ctrl_05_c1;	//0xC902C398
	PE_E60_SHP_CORE1_NNTG_CTRL_01_C0_T  shp_core1_nntg_ctrl_01_c0;	//0xC902C39C
	PE_E60_SHP_CORE1_NNTG_CTRL_02_C0_T  shp_core1_nntg_ctrl_02_c0;	//0xC902C3A0
	PE_E60_SHP_CORE1_NNTG_CTRL_03_C0_T  shp_core1_nntg_ctrl_03_c0;	//0xC902C3A4
	PE_E60_SHP_CORE1_NNTG_CTRL_04_C0_T  shp_core1_nntg_ctrl_04_c0;	//0xC902C3A8
	PE_E60_SHP_CORE1_NNTG_CTRL_05_C0_T  shp_core1_nntg_ctrl_05_c0;	//0xC902C3AC
	PE_E60_SHP_CORE1_NNTG_CTRL_01_C1_T  shp_core1_nntg_ctrl_01_c1;	//0xC902C3B0
	PE_E60_SHP_CORE1_NNTG_CTRL_02_C1_T  shp_core1_nntg_ctrl_02_c1;	//0xC902C3B4
	PE_E60_SHP_CORE1_NNTG_CTRL_03_C1_T  shp_core1_nntg_ctrl_03_c1;	//0xC902C3B8
	PE_E60_SHP_CORE1_NNTG_CTRL_04_C1_T  shp_core1_nntg_ctrl_04_c1;	//0xC902C3BC
	PE_E60_SHP_CORE1_NNTG_CTRL_05_C1_T  shp_core1_nntg_ctrl_05_c1;	//0xC902C3C0
	PE_E60_SHP_NNTG_CTRL_06_T                    shp_nntg_ctrl_06;	//0xC902C3C4
	PE_E60_SHP_NNTG_CTRL_07_T                    shp_nntg_ctrl_07;	//0xC902C3C8
	PE_E60_SHP_NNTG_CTRL_08_T                    shp_nntg_ctrl_08;	//0xC902C3CC
	PE_E60_SHP_NNTG_CTRL_09_T                    shp_nntg_ctrl_09;	//0xC902C3D0
	PE_E60_SHP_NNTG_CTRL_0A_T                    shp_nntg_ctrl_0a;	//0xC902C3D4
	PE_E60_SHP_NNTG_CTRL_0B_T                    shp_nntg_ctrl_0b;	//0xC902C3D8
	PE_E60_SHP_NNTG_CTRL_0C_T                    shp_nntg_ctrl_0c;	//0xC902C3DC
	PE_E60_SHP_NNTG_CTRL_0D_T                    shp_nntg_ctrl_0d;	//0xC902C3E0
	PE_E60_SHP_NNTG_CTRL_0E_T                    shp_nntg_ctrl_0e;	//0xC902C3E4
	PE_E60_SHP_NNTG_CTRL_0F_T                    shp_nntg_ctrl_0f;	//0xC902C3E8
	PE_E60_SHP_NNTG_CTRL_10_T                    shp_nntg_ctrl_10;	//0xC902C3EC
	PE_E60_SHP_DP_SUM_CTRL_00_T                shp_dp_sum_ctrl_00;	//0xC902C3F0
	PE_E60_SHP_DP_SUM_CTRL_01_T                shp_dp_sum_ctrl_01;	//0xC902C3F4
	PE_E60_SHP_DP_SUM_CTRL_02_T                shp_dp_sum_ctrl_02;	//0xC902C3F8
	PE_E60_SHP_DP_SUM_CTRL_03_T                shp_dp_sum_ctrl_03;	//0xC902C3FC
	PE_E60_SHP_DP_SUM_CTRL_04_T                shp_dp_sum_ctrl_04;	//0xC902C400
	PE_E60_SHP_DP_SUM_CTRL_05_T                shp_dp_sum_ctrl_05;	//0xC902C404
	PE_E60_SHP_DP_SUM_CTRL_06_T                shp_dp_sum_ctrl_06;	//0xC902C408
	PE_E60_SHP_DP_SUM_CTRL_07_T                shp_dp_sum_ctrl_07;	//0xC902C40C
	PE_E60_SHP_DP_SUM_CTRL_08_T                shp_dp_sum_ctrl_08;	//0xC902C410
	UINT32                                                   reserved48;	//0xC902C414
	UINT32                                                   reserved49;	//0xC902C418
	UINT32                                                   reserved50;	//0xC902C41C
	PE_E60_SHP_PSP_CTRL_00_T                      shp_psp_ctrl_00;	//0xC902C420
	UINT32                                                   reserved51;	//0xC902C424
	UINT32                                                   reserved52;	//0xC902C428
	UINT32                                                   reserved53;	//0xC902C42C
	PE_E60_SHP_CORE0_DP_WIN_CTRL_00_T    shp_core0_dp_win_ctrl_00;	//0xC902C430
	PE_E60_SHP_CORE0_DP_WIN_CTRL_01_T    shp_core0_dp_win_ctrl_01;	//0xC902C434
	PE_E60_SHP_CORE0_DP_WIN_CTRL_02_T    shp_core0_dp_win_ctrl_02;	//0xC902C438
	PE_E60_SHP_CORE0_DP_WIN_CTRL_03_T    shp_core0_dp_win_ctrl_03;	//0xC902C43C
	PE_E60_SHP_CORE0_DP_WIN_CTRL_04_T    shp_core0_dp_win_ctrl_04;	//0xC902C440
	PE_E60_SHP_CORE1_DP_WIN_CTRL_00_T    shp_core1_dp_win_ctrl_00;	//0xC902C444
	PE_E60_SHP_CORE1_DP_WIN_CTRL_01_T    shp_core1_dp_win_ctrl_01;	//0xC902C448
	PE_E60_SHP_CORE1_DP_WIN_CTRL_02_T    shp_core1_dp_win_ctrl_02;	//0xC902C44C
	PE_E60_SHP_CORE1_DP_WIN_CTRL_03_T    shp_core1_dp_win_ctrl_03;	//0xC902C450
	PE_E60_SHP_CORE1_DP_WIN_CTRL_04_T    shp_core1_dp_win_ctrl_04;	//0xC902C454
	UINT32                                                   reserved54;	//0xC902C458
	UINT32                                                   reserved55;	//0xC902C45C
	PE_E60_SHP_FD_REGION_TEXT_00_T          shp_fd_region_text_00;	//0xC902C460
	PE_E60_SHP_FD_REGION_TEXT_01_T          shp_fd_region_text_01;	//0xC902C464
	PE_E60_SHP_FD_REGION_TEXT_02_T          shp_fd_region_text_02;	//0xC902C468
	PE_E60_SHP_FD_TMAP_TEMP_00_T              shp_fd_tmap_temp_00;	//0xC902C46C
	PE_E60_SHP_FD_TMAP_TEMP_01_T              shp_fd_tmap_temp_01;	//0xC902C470
	PE_E60_SHP_FD_TMAP_TEMP_02_T              shp_fd_tmap_temp_02;	//0xC902C474
	PE_E60_SHP_FD_TMAP_TEMP_03_T              shp_fd_tmap_temp_03;	//0xC902C478
	PE_E60_SHP_FD_TMAP_TEMP_04_T              shp_fd_tmap_temp_04;	//0xC902C47C
	PE_E60_SHP_FD_TMAP_TEMP_05_T              shp_fd_tmap_temp_05;	//0xC902C480
	PE_E60_SHP_FD_TMAP_TEMP_06_T              shp_fd_tmap_temp_06;	//0xC902C484
	PE_E60_SHP_FD_TMAP_TEMP_07_T              shp_fd_tmap_temp_07;	//0xC902C488
	PE_E60_SHP_FD_TMAP_TEMP_08_T              shp_fd_tmap_temp_08;	//0xC902C48C
	PE_E60_SHP_FD_TMAP_TEMP_09_T              shp_fd_tmap_temp_09;	//0xC902C490
	PE_E60_SHP_FD_TMAP_TEMP_0A_T              shp_fd_tmap_temp_0a;	//0xC902C494
	PE_E60_SHP_FD_TMAP_TEMP_0B_T              shp_fd_tmap_temp_0b;	//0xC902C498
	PE_E60_SHP_FD_TMAP_TEMP_0C_T              shp_fd_tmap_temp_0c;	//0xC902C49C
	PE_E60_SHP_DJ_CTRL_00_T                        shp_dj_ctrl_00;	//0xC902C4A0
	PE_E60_SHP_DJ_CTRL_01_T                        shp_dj_ctrl_01;	//0xC902C4A4
	PE_E60_SHP_DJ_CTRL_02_T                        shp_dj_ctrl_02;	//0xC902C4A8
	PE_E60_SHP_DJ_CTRL_03_T                        shp_dj_ctrl_03;	//0xC902C4AC
	PE_E60_SHP_DJ_CTRL_04_T                        shp_dj_ctrl_04;	//0xC902C4B0
	PE_E60_SHP_DJ_CTRL_05_T                        shp_dj_ctrl_05;	//0xC902C4B4
	PE_E60_SHP_DJ_CTRL_06_T                        shp_dj_ctrl_06;	//0xC902C4B8
	PE_E60_SHP_DJ_CTRL_07_T                        shp_dj_ctrl_07;	//0xC902C4BC
	PE_E60_SHP_DJ_CTRL_08_T                        shp_dj_ctrl_08;	//0xC902C4C0
	PE_E60_SHP_DJ_CTRL_09_T                        shp_dj_ctrl_09;	//0xC902C4C4
	PE_E60_SHP_DJ_CTRL_0A_T                        shp_dj_ctrl_0a;	//0xC902C4C8
	PE_E60_SHP_DJ_CTRL_0B_T                        shp_dj_ctrl_0b;	//0xC902C4CC
	PE_E60_SHP_DJ_CTRL_0C_T                        shp_dj_ctrl_0c;	//0xC902C4D0
	PE_E60_SHP_DJ_CTRL_0D_T                        shp_dj_ctrl_0d;	//0xC902C4D4
	PE_E60_SHP_DJ_CTRL_0E_T                        shp_dj_ctrl_0e;	//0xC902C4D8
	PE_E60_SHP_DJ_CTRL_0F_T                        shp_dj_ctrl_0f;	//0xC902C4DC
	PE_E60_SHP_DJ_CTRL_10_T                        shp_dj_ctrl_10;	//0xC902C4E0
	PE_E60_SHP_DJ_CTRL_11_T                        shp_dj_ctrl_11;	//0xC902C4E4
	PE_E60_SHP_DJ_CTRL_12_T                        shp_dj_ctrl_12;	//0xC902C4E8
	PE_E60_SHP_DJ_CTRL_13_T                        shp_dj_ctrl_13;	//0xC902C4EC
	PE_E60_SHP_DJ_CTRL_14_T                        shp_dj_ctrl_14;	//0xC902C4F0
	PE_E60_SHP_DJ_CTRL_15_T                        shp_dj_ctrl_15;	//0xC902C4F4
	PE_E60_SHP_DJ_CTRL_16_T                        shp_dj_ctrl_16;	//0xC902C4F8
	PE_E60_SHP_DJ_CTRL_17_T                        shp_dj_ctrl_17;	//0xC902C4FC
	PE_E60_SHP_DJ_CTRL_18_T                        shp_dj_ctrl_18;	//0xC902C500
	PE_E60_SHP_DJ_CTRL_19_T                        shp_dj_ctrl_19;	//0xC902C504
	PE_E60_SHP_DJ_CTRL_1A_T                        shp_dj_ctrl_1a;	//0xC902C508
	PE_E60_SHP_DJ_CTRL_1B_T                        shp_dj_ctrl_1b;	//0xC902C50C
	PE_E60_SHP_DJ_CTRL_1C_T                        shp_dj_ctrl_1c;	//0xC902C510
	PE_E60_SHP_DJ_CTRL_1D_T                        shp_dj_ctrl_1d;	//0xC902C514
	PE_E60_SHP_DJ_CTRL_1E_T                        shp_dj_ctrl_1e;	//0xC902C518
	PE_E60_SHP_DJ_CTRL_1F_T                        shp_dj_ctrl_1f;	//0xC902C51C
	PE_E60_SHP_DJ_CTRL_20_T                        shp_dj_ctrl_20;	//0xC902C520
	PE_E60_SHP_DB_CTRL_00_T                        shp_db_ctrl_00;	//0xC902C524
	PE_E60_SHP_DB_CTRL_01_T                        shp_db_ctrl_01;	//0xC902C528
	UINT32                                                   reserved56;	//0xC902C52C
	PE_E60_SHP_CORE0_DJ_WIN_CTRL_00_T    shp_core0_dj_win_ctrl_00;	//0xC902C530
	PE_E60_SHP_CORE0_DJ_WIN_CTRL_01_T    shp_core0_dj_win_ctrl_01;	//0xC902C534
	PE_E60_SHP_CORE0_DJ_WIN_CTRL_02_T    shp_core0_dj_win_ctrl_02;	//0xC902C538
	PE_E60_SHP_CORE0_DJ_WIN_CTRL_03_T    shp_core0_dj_win_ctrl_03;	//0xC902C53C
	PE_E60_SHP_CORE0_DJ_WIN_CTRL_04_T    shp_core0_dj_win_ctrl_04;	//0xC902C540
	PE_E60_SHP_CORE1_DJ_WIN_CTRL_00_T    shp_core1_dj_win_ctrl_00;	//0xC902C544
	PE_E60_SHP_CORE1_DJ_WIN_CTRL_01_T    shp_core1_dj_win_ctrl_01;	//0xC902C548
	PE_E60_SHP_CORE1_DJ_WIN_CTRL_02_T    shp_core1_dj_win_ctrl_02;	//0xC902C54C
	PE_E60_SHP_CORE1_DJ_WIN_CTRL_03_T    shp_core1_dj_win_ctrl_03;	//0xC902C550
	PE_E60_SHP_CORE1_DJ_WIN_CTRL_04_T    shp_core1_dj_win_ctrl_04;	//0xC902C554
	UINT32                                                   reserved57;	//0xC902C558
	UINT32                                                   reserved58;	//0xC902C55C
	PE_E60_SHP_CHROMA_CTRL_00_T                shp_chroma_ctrl_00;	//0xC902C560
	PE_E60_SHP_CHROMA_CTRL_01_T                shp_chroma_ctrl_01;	//0xC902C564
	PE_E60_SHP_CHROMA_CTRL_02_T                shp_chroma_ctrl_02;	//0xC902C568
	PE_E60_SHP_CHROMA_CTRL_03_T                shp_chroma_ctrl_03;	//0xC902C56C
	PE_E60_SHP_CHROMA_CTRL_04_T                shp_chroma_ctrl_04;	//0xC902C570
	PE_E60_SHP_CHROMA_CTRL_05_T                shp_chroma_ctrl_05;	//0xC902C574
	PE_E60_SHP_CHROMA_CTRL_06_T                shp_chroma_ctrl_06;	//0xC902C578
	PE_E60_SHP_CHROMA_CTRL_07_T                shp_chroma_ctrl_07;	//0xC902C57C
	PE_E60_SHP_CHROMA_CTRL_08_T                shp_chroma_ctrl_08;	//0xC902C580
	PE_E60_SHP_CHROMA_CTRL_09_T                shp_chroma_ctrl_09;	//0xC902C584
	PE_E60_SHP_CHROMA_CTRL_0A_T                shp_chroma_ctrl_0a;	//0xC902C588
	PE_E60_SHP_CHROMA_CTRL_0B_T                shp_chroma_ctrl_0b;	//0xC902C58C
	PE_E60_SHP_CHROMA_CTRL_0C_T                shp_chroma_ctrl_0c;	//0xC902C590
	PE_E60_SHP_CHROMA_CTRL_0D_T                shp_chroma_ctrl_0d;	//0xC902C594
	PE_E60_SHP_CHROMA_CTRL_0E_T                shp_chroma_ctrl_0e;	//0xC902C598
	UINT32                                                   reserved59;	//0xC902C59C
	PE_E60_SHP_CTI_CTRL_00_T                      shp_cti_ctrl_00;	//0xC902C5A0
	PE_E60_SHP_CTI_CTRL_01_T                      shp_cti_ctrl_01;	//0xC902C5A4
	PE_E60_SHP_CTI_CTRL_02_T                      shp_cti_ctrl_02;	//0xC902C5A8
	UINT32                                                   reserved60;	//0xC902C5AC
	PE_E60_SHP_FRC_FLICK_CTRL_00_T          shp_frc_flick_ctrl_00;	//0xC902C5B0
	PE_E60_SHP_FRC_FLICK_CTRL_01_T          shp_frc_flick_ctrl_01;	//0xC902C5B4
	PE_E60_SHP_FRC_FLICK_CTRL_02_T          shp_frc_flick_ctrl_02;	//0xC902C5B8
	PE_E60_SHP_FRC_FLICK_CTRL_03_T          shp_frc_flick_ctrl_03;	//0xC902C5BC
	PE_E60_SHP_FRC_BLUR_CTRL_00_T            shp_frc_blur_ctrl_00;	//0xC902C5C0
	PE_E60_SHP_FRC_BLUR_CTRL_01_T            shp_frc_blur_ctrl_01;	//0xC902C5C4
	PE_E60_SHP_FRC_BLUR_CTRL_02_T            shp_frc_blur_ctrl_02;	//0xC902C5C8
	PE_E60_SHP_FRC_BLUR_CTRL_03_T            shp_frc_blur_ctrl_03;	//0xC902C5CC
	PE_E60_SHP_FRC_BLUR_CTRL_04_T            shp_frc_blur_ctrl_04;	//0xC902C5D0
	PE_E60_SHP_FRC_BLUR_CTRL_05_T            shp_frc_blur_ctrl_05;	//0xC902C5D4
	PE_E60_SHP_FRC_BLUR_CTRL_06_T            shp_frc_blur_ctrl_06;	//0xC902C5D8
	UINT32                                                   reserved61;	//0xC902C5DC
	PE_E60_SHP_FRC_HALO_CTRL_00_T            shp_frc_halo_ctrl_00;	//0xC902C5E0
	PE_E60_SHP_FRC_HALO_CTRL_01_T            shp_frc_halo_ctrl_01;	//0xC902C5E4
	PE_E60_SHP_FRC_HALO_CTRL_02_T            shp_frc_halo_ctrl_02;	//0xC902C5E8
	PE_E60_SHP_FRC_HALO_CTRL_03_T            shp_frc_halo_ctrl_03;	//0xC902C5EC
	PE_E60_SHP_CORE0_FRC_WIN_CTRL_00_T  shp_core0_frc_win_ctrl_00;	//0xC902C5F0
	PE_E60_SHP_CORE0_FRC_WIN_CTRL_01_T  shp_core0_frc_win_ctrl_01;	//0xC902C5F4
	PE_E60_SHP_CORE0_FRC_WIN_CTRL_02_T  shp_core0_frc_win_ctrl_02;	//0xC902C5F8
	PE_E60_SHP_CORE0_FRC_WIN_CTRL_03_T  shp_core0_frc_win_ctrl_03;	//0xC902C5FC
	PE_E60_SHP_CORE0_FRC_WIN_CTRL_04_T  shp_core0_frc_win_ctrl_04;	//0xC902C600
	PE_E60_SHP_CORE1_FRC_WIN_CTRL_00_T  shp_core1_frc_win_ctrl_00;	//0xC902C604
	PE_E60_SHP_CORE1_FRC_WIN_CTRL_01_T  shp_core1_frc_win_ctrl_01;	//0xC902C608
	PE_E60_SHP_CORE1_FRC_WIN_CTRL_02_T  shp_core1_frc_win_ctrl_02;	//0xC902C60C
	PE_E60_SHP_CORE1_FRC_WIN_CTRL_03_T  shp_core1_frc_win_ctrl_03;	//0xC902C610
	PE_E60_SHP_CORE1_FRC_WIN_CTRL_04_T  shp_core1_frc_win_ctrl_04;	//0xC902C614
	UINT32                                                   reserved62;	//0xC902C618
	UINT32                                                   reserved63;	//0xC902C61C
	PE_E60_SHP_MOTION_GAIN_CTRL_00_T      shp_motion_gain_ctrl_00;	//0xC902C620
	PE_E60_SHP_MOTION_GAIN_CTRL_01_T      shp_motion_gain_ctrl_01;	//0xC902C624
	PE_E60_SHP_MOTION_GAIN_CTRL_02_T      shp_motion_gain_ctrl_02;	//0xC902C628
	PE_E60_SHP_MOTION_GAIN_CTRL_03_T      shp_motion_gain_ctrl_03;	//0xC902C62C
	PE_E60_SHP_MOTION_GAIN_CTRL_04_T      shp_motion_gain_ctrl_04;	//0xC902C630
	PE_E60_SHP_MOTION_GAIN_CTRL_05_T      shp_motion_gain_ctrl_05;	//0xC902C634
	PE_E60_SHP_MOTION_GAIN_CTRL_06_T      shp_motion_gain_ctrl_06;	//0xC902C638
	PE_E60_SHP_MOTION_GAIN_CTRL_07_T      shp_motion_gain_ctrl_07;	//0xC902C63C
	PE_E60_SHP_MOTION_GAIN_CTRL_08_T      shp_motion_gain_ctrl_08;	//0xC902C640
	PE_E60_SHP_MOTION_GAIN_CTRL_09_T      shp_motion_gain_ctrl_09;	//0xC902C644
	PE_E60_SHP_MOTION_GAIN_CTRL_0A_T      shp_motion_gain_ctrl_0a;	//0xC902C648
	PE_E60_SHP_MOTION_GAIN_CTRL_0B_T      shp_motion_gain_ctrl_0b;	//0xC902C64C
	PE_E60_SHP_MOTION_GAIN_CTRL_0C_T      shp_motion_gain_ctrl_0c;	//0xC902C650
	UINT32                                                   reserved64;	//0xC902C654
	UINT32                                                   reserved65;	//0xC902C658
	UINT32                                                   reserved66;	//0xC902C65C
	PE_E60_SHP_MOTION_PROT_CTRL_00_T      shp_motion_prot_ctrl_00;	//0xC902C660
	PE_E60_SHP_MOTION_PROT_CTRL_01_T      shp_motion_prot_ctrl_01;	//0xC902C664
	PE_E60_SHP_MOTION_PROT_CTRL_02_T      shp_motion_prot_ctrl_02;	//0xC902C668
	PE_E60_SHP_MOTION_PROT_CTRL_03_T      shp_motion_prot_ctrl_03;	//0xC902C66C
	PE_E60_SHP_MOTION_PROT_CTRL_04_T      shp_motion_prot_ctrl_04;	//0xC902C670
	UINT32                                                   reserved67;	//0xC902C674
	UINT32                                                   reserved68;	//0xC902C678
	UINT32                                                   reserved69;	//0xC902C67C
	PE_E60_SHP_CORE0_MOT_WIN_CTRL_00_T  shp_core0_mot_win_ctrl_00;	//0xC902C680
	PE_E60_SHP_CORE0_MOT_WIN_CTRL_01_T  shp_core0_mot_win_ctrl_01;	//0xC902C684
	PE_E60_SHP_CORE0_MOT_WIN_CTRL_02_T  shp_core0_mot_win_ctrl_02;	//0xC902C688
	PE_E60_SHP_CORE0_MOT_WIN_CTRL_03_T  shp_core0_mot_win_ctrl_03;	//0xC902C68C
	PE_E60_SHP_CORE0_MOT_WIN_CTRL_04_T  shp_core0_mot_win_ctrl_04;	//0xC902C690
	UINT32                                                   reserved70;	//0xC902C694
	UINT32                                                   reserved71;	//0xC902C698
	UINT32                                                   reserved72;	//0xC902C69C
	PE_E60_SHP_CORE1_MOT_WIN_CTRL_00_T  shp_core1_mot_win_ctrl_00;	//0xC902C6A0
	PE_E60_SHP_CORE1_MOT_WIN_CTRL_01_T  shp_core1_mot_win_ctrl_01;	//0xC902C6A4
	PE_E60_SHP_CORE1_MOT_WIN_CTRL_02_T  shp_core1_mot_win_ctrl_02;	//0xC902C6A8
	PE_E60_SHP_CORE1_MOT_WIN_CTRL_03_T  shp_core1_mot_win_ctrl_03;	//0xC902C6AC
	PE_E60_SHP_CORE1_MOT_WIN_CTRL_04_T  shp_core1_mot_win_ctrl_04;	//0xC902C6B0
	UINT32                                                   reserved73;	//0xC902C6B4
	UINT32                                                   reserved74;	//0xC902C6B8
	UINT32                                                   reserved75;	//0xC902C6BC
	PE_E60_SHP_OBJ_CTRL_00_T                      shp_obj_ctrl_00;	//0xC902C6C0
	PE_E60_SHP_OBJ_CTRL_01_T                      shp_obj_ctrl_01;	//0xC902C6C4
	PE_E60_SHP_OBJ_CTRL_02_T                      shp_obj_ctrl_02;	//0xC902C6C8
	PE_E60_SHP_OBJ_CTRL_03_T                      shp_obj_ctrl_03;	//0xC902C6CC
	PE_E60_SHP_OBJ_CTRL_04_T                      shp_obj_ctrl_04;	//0xC902C6D0
	PE_E60_SHP_OBJ_CTRL_05_T                      shp_obj_ctrl_05;	//0xC902C6D4
	PE_E60_SHP_OBJ_CTRL_06_T                      shp_obj_ctrl_06;	//0xC902C6D8
	PE_E60_SHP_OBJ_CTRL_07_T                      shp_obj_ctrl_07;	//0xC902C6DC
	PE_E60_SHP_OBJ_CTRL_08_T                      shp_obj_ctrl_08;	//0xC902C6E0
	PE_E60_SHP_OBJ_CTRL_09_T                      shp_obj_ctrl_09;	//0xC902C6E4
	PE_E60_SHP_OBJ_CTRL_0A_T                      shp_obj_ctrl_0a;	//0xC902C6E8
	UINT32                                                   reserved76;	//0xC902C6EC
	UINT32                                                   reserved77;	//0xC902C6F0
	UINT32                                                   reserved78;	//0xC902C6F4
	UINT32                                                   reserved79;	//0xC902C6F8
	UINT32                                                   reserved80;	//0xC902C6FC
	UINT32                                                   reserved81;	//0xC902C700
	UINT32                                                   reserved82;	//0xC902C704
	UINT32                                                   reserved83;	//0xC902C708
	UINT32                                                   reserved84;	//0xC902C70C
	UINT32                                                   reserved85;	//0xC902C710
	UINT32                                                   reserved86;	//0xC902C714
	UINT32                                                   reserved87;	//0xC902C718
	UINT32                                                   reserved88;	//0xC902C71C
	UINT32                                                   reserved89;	//0xC902C720
	UINT32                                                   reserved90;	//0xC902C724
	UINT32                                                   reserved91;	//0xC902C728
	UINT32                                                   reserved92;	//0xC902C72C
	UINT32                                                   reserved93;	//0xC902C730
	UINT32                                                   reserved94;	//0xC902C734
	UINT32                                                   reserved95;	//0xC902C738
	UINT32                                                   reserved96;	//0xC902C73C
	UINT32                                                   reserved97;	//0xC902C740
	UINT32                                                   reserved98;	//0xC902C744
	UINT32                                                   reserved99;	//0xC902C748
	UINT32                                                  reserved100;	//0xC902C74C
	UINT32                                                  reserved101;	//0xC902C750
	UINT32                                                  reserved102;	//0xC902C754
	UINT32                                                  reserved103;	//0xC902C758
	UINT32                                                  reserved104;	//0xC902C75C
	UINT32                                                  reserved105;	//0xC902C760
	UINT32                                                  reserved106;	//0xC902C764
	UINT32                                                  reserved107;	//0xC902C768
	UINT32                                                  reserved108;	//0xC902C76C
	UINT32                                                  reserved109;	//0xC902C770
	UINT32                                                  reserved110;	//0xC902C774
	UINT32                                                  reserved111;	//0xC902C778
	UINT32                                                  reserved112;	//0xC902C77C
	UINT32                                                  reserved113;	//0xC902C780
	UINT32                                                  reserved114;	//0xC902C784
	UINT32                                                  reserved115;	//0xC902C788
	UINT32                                                  reserved116;	//0xC902C78C
	UINT32                                                  reserved117;	//0xC902C790
	UINT32                                                  reserved118;	//0xC902C794
	UINT32                                                  reserved119;	//0xC902C798
	UINT32                                                  reserved120;	//0xC902C79C
	PE_E60_SHP_CORE0_STAT_00_T                  shp_core0_stat_00;	//0xC902C7A0
	PE_E60_SHP_CORE0_STAT_01_T                  shp_core0_stat_01;	//0xC902C7A4
	PE_E60_SHP_CORE0_STAT_02_T                  shp_core0_stat_02;	//0xC902C7A8
	PE_E60_SHP_CORE0_STAT_03_T                  shp_core0_stat_03;	//0xC902C7AC
	PE_E60_SHP_CORE0_STAT_04_T                  shp_core0_stat_04;	//0xC902C7B0
	PE_E60_SHP_CORE0_STAT_05_T                  shp_core0_stat_05;	//0xC902C7B4
	UINT32                                                  reserved121;	//0xC902C7B8
	UINT32                                                  reserved122;	//0xC902C7BC
	UINT32                                                  reserved123;	//0xC902C7C0
	UINT32                                                  reserved124;	//0xC902C7C4
	UINT32                                                  reserved125;	//0xC902C7C8
	UINT32                                                  reserved126;	//0xC902C7CC
	PE_E60_SHP_CORE0_FD_STAT_00_T            shp_core0_fd_stat_00;	//0xC902C7D0
	PE_E60_SHP_CORE0_FD_STAT_01_T            shp_core0_fd_stat_01;	//0xC902C7D4
	PE_E60_SHP_CORE0_FD_STAT_02_T            shp_core0_fd_stat_02;	//0xC902C7D8
	PE_E60_SHP_CORE0_FD_STAT_03_T            shp_core0_fd_stat_03;	//0xC902C7DC
	PE_E60_SHP_MOTION_GAIN_STAT_00_T      shp_motion_gain_stat_00;	//0xC902C7E0
	PE_E60_SHP_MOTION_GAIN_STAT_01_T      shp_motion_gain_stat_01;	//0xC902C7E4
	UINT32                                                  reserved127;	//0xC902C7E8
	UINT32                                                  reserved128;	//0xC902C7EC
	UINT32                                                  reserved129;	//0xC902C7F0
	UINT32                                                  reserved130;	//0xC902C7F4
	UINT32                                                  reserved131;	//0xC902C7F8
	UINT32                                                  reserved132;	//0xC902C7FC
	PE_E60_SHP_CORE0_TMAP_STAT_00_T        shp_core0_tmap_stat_00;	//0xC902C800
	PE_E60_SHP_CORE0_TMAP_STAT_01_T        shp_core0_tmap_stat_01;	//0xC902C804
	PE_E60_SHP_CORE0_TMAP_STAT_02_T        shp_core0_tmap_stat_02;	//0xC902C808
	PE_E60_SHP_CORE0_TMAP_STAT_03_T        shp_core0_tmap_stat_03;	//0xC902C80C
	PE_E60_SHP_CORE0_TMAP_STAT_04_T        shp_core0_tmap_stat_04;	//0xC902C810
	PE_E60_SHP_CORE0_TMAP_STAT_05_T        shp_core0_tmap_stat_05;	//0xC902C814
	PE_E60_SHP_CORE0_TMAP_STAT_06_T        shp_core0_tmap_stat_06;	//0xC902C818
	PE_E60_SHP_CORE0_TMAP_STAT_07_T        shp_core0_tmap_stat_07;	//0xC902C81C
	UINT32                                                  reserved133;	//0xC902C820
	UINT32                                                  reserved134;	//0xC902C824
	UINT32                                                  reserved135;	//0xC902C828
	UINT32                                                  reserved136;	//0xC902C82C
	UINT32                                                  reserved137;	//0xC902C830
	UINT32                                                  reserved138;	//0xC902C834
	UINT32                                                  reserved139;	//0xC902C838
	UINT32                                                  reserved140;	//0xC902C83C
	UINT32                                                  reserved141;	//0xC902C840
	UINT32                                                  reserved142;	//0xC902C844
	UINT32                                                  reserved143;	//0xC902C848
	UINT32                                                  reserved144;	//0xC902C84C
	UINT32                                                  reserved145;	//0xC902C850
	UINT32                                                  reserved146;	//0xC902C854
	UINT32                                                  reserved147;	//0xC902C858
	UINT32                                                  reserved148;	//0xC902C85C
	UINT32                                                  reserved149;	//0xC902C860
	UINT32                                                  reserved150;	//0xC902C864
	UINT32                                                  reserved151;	//0xC902C868
	UINT32                                                  reserved152;	//0xC902C86C
	UINT32                                                  reserved153;	//0xC902C870
	UINT32                                                  reserved154;	//0xC902C874
	UINT32                                                  reserved155;	//0xC902C878
	UINT32                                                  reserved156;	//0xC902C87C
	UINT32                                                  reserved157;	//0xC902C880
	UINT32                                                  reserved158;	//0xC902C884
	UINT32                                                  reserved159;	//0xC902C888
	UINT32                                                  reserved160;	//0xC902C88C
	UINT32                                                  reserved161;	//0xC902C890
	UINT32                                                  reserved162;	//0xC902C894
	UINT32                                                  reserved163;	//0xC902C898
	UINT32                                                  reserved164;	//0xC902C89C
	UINT32                                                  reserved165;	//0xC902C8A0
	UINT32                                                  reserved166;	//0xC902C8A4
	UINT32                                                  reserved167;	//0xC902C8A8
	UINT32                                                  reserved168;	//0xC902C8AC
	UINT32                                                  reserved169;	//0xC902C8B0
	UINT32                                                  reserved170;	//0xC902C8B4
	UINT32                                                  reserved171;	//0xC902C8B8
	UINT32                                                  reserved172;	//0xC902C8BC
	UINT32                                                  reserved173;	//0xC902C8C0
	UINT32                                                  reserved174;	//0xC902C8C4
	UINT32                                                  reserved175;	//0xC902C8C8
	UINT32                                                  reserved176;	//0xC902C8CC
	UINT32                                                  reserved177;	//0xC902C8D0
	UINT32                                                  reserved178;	//0xC902C8D4
	UINT32                                                  reserved179;	//0xC902C8D8
	UINT32                                                  reserved180;	//0xC902C8DC
	UINT32                                                  reserved181;	//0xC902C8E0
	UINT32                                                  reserved182;	//0xC902C8E4
	UINT32                                                  reserved183;	//0xC902C8E8
	UINT32                                                  reserved184;	//0xC902C8EC
	UINT32                                                  reserved185;	//0xC902C8F0
	UINT32                                                  reserved186;	//0xC902C8F4
	UINT32                                                  reserved187;	//0xC902C8F8
	UINT32                                                  reserved188;	//0xC902C8FC
	UINT32                                                  reserved189;	//0xC902C900
	UINT32                                                  reserved190;	//0xC902C904
	UINT32                                                  reserved191;	//0xC902C908
	UINT32                                                  reserved192;	//0xC902C90C
	UINT32                                                  reserved193;	//0xC902C910
	UINT32                                                  reserved194;	//0xC902C914
	UINT32                                                  reserved195;	//0xC902C918
	UINT32                                                  reserved196;	//0xC902C91C
	UINT32                                                  reserved197;	//0xC902C920
	UINT32                                                  reserved198;	//0xC902C924
	UINT32                                                  reserved199;	//0xC902C928
	UINT32                                                  reserved200;	//0xC902C92C
	UINT32                                                  reserved201;	//0xC902C930
	UINT32                                                  reserved202;	//0xC902C934
	UINT32                                                  reserved203;	//0xC902C938
	UINT32                                                  reserved204;	//0xC902C93C
	UINT32                                                  reserved205;	//0xC902C940
	UINT32                                                  reserved206;	//0xC902C944
	UINT32                                                  reserved207;	//0xC902C948
	UINT32                                                  reserved208;	//0xC902C94C
	UINT32                                                  reserved209;	//0xC902C950
	UINT32                                                  reserved210;	//0xC902C954
	UINT32                                                  reserved211;	//0xC902C958
	UINT32                                                  reserved212;	//0xC902C95C
	UINT32                                                  reserved213;	//0xC902C960
	UINT32                                                  reserved214;	//0xC902C964
	UINT32                                                  reserved215;	//0xC902C968
	UINT32                                                  reserved216;	//0xC902C96C
	UINT32                                                  reserved217;	//0xC902C970
	UINT32                                                  reserved218;	//0xC902C974
	UINT32                                                  reserved219;	//0xC902C978
	UINT32                                                  reserved220;	//0xC902C97C
	UINT32                                                  reserved221;	//0xC902C980
	UINT32                                                  reserved222;	//0xC902C984
	UINT32                                                  reserved223;	//0xC902C988
	UINT32                                                  reserved224;	//0xC902C98C
	UINT32                                                  reserved225;	//0xC902C990
	UINT32                                                  reserved226;	//0xC902C994
	UINT32                                                  reserved227;	//0xC902C998
	UINT32                                                  reserved228;	//0xC902C99C
	PE_E60_SHP_CORE1_STAT_00_T                  shp_core1_stat_00;	//0xC902C9A0
	PE_E60_SHP_CORE1_STAT_01_T                  shp_core1_stat_01;	//0xC902C9A4
	PE_E60_SHP_CORE1_STAT_02_T                  shp_core1_stat_02;	//0xC902C9A8
	PE_E60_SHP_CORE1_STAT_03_T                  shp_core1_stat_03;	//0xC902C9AC
	PE_E60_SHP_CORE1_STAT_04_T                  shp_core1_stat_04;	//0xC902C9B0
	PE_E60_SHP_CORE1_STAT_05_T                  shp_core1_stat_05;	//0xC902C9B4
	UINT32                                                  reserved229;	//0xC902C9B8
	UINT32                                                  reserved230;	//0xC902C9BC
	UINT32                                                  reserved231;	//0xC902C9C0
	UINT32                                                  reserved232;	//0xC902C9C4
	UINT32                                                  reserved233;	//0xC902C9C8
	UINT32                                                  reserved234;	//0xC902C9CC
	PE_E60_SHP_CORE1_FD_STAT_00_T            shp_core1_fd_stat_00;	//0xC902C9D0
	PE_E60_SHP_CORE1_FD_STAT_01_T            shp_core1_fd_stat_01;	//0xC902C9D4
	PE_E60_SHP_CORE1_FD_STAT_02_T            shp_core1_fd_stat_02;	//0xC902C9D8
	PE_E60_SHP_CORE1_FD_STAT_03_T            shp_core1_fd_stat_03;	//0xC902C9DC
	UINT32                                                  reserved235;	//0xC902C9E0
	UINT32                                                  reserved236;	//0xC902C9E4
	UINT32                                                  reserved237;	//0xC902C9E8
	UINT32                                                  reserved238;	//0xC902C9EC
	UINT32                                                  reserved239;	//0xC902C9F0
	UINT32                                                  reserved240;	//0xC902C9F4
	UINT32                                                  reserved241;	//0xC902C9F8
	UINT32                                                  reserved242;	//0xC902C9FC
	PE_E60_SHP_CORE1_TMAP_STAT_00_T        shp_core1_tmap_stat_00;	//0xC902CA00
	PE_E60_SHP_CORE1_TMAP_STAT_01_T        shp_core1_tmap_stat_01;	//0xC902CA04
	PE_E60_SHP_CORE1_TMAP_STAT_02_T        shp_core1_tmap_stat_02;	//0xC902CA08
	PE_E60_SHP_CORE1_TMAP_STAT_03_T        shp_core1_tmap_stat_03;	//0xC902CA0C
	PE_E60_SHP_CORE1_TMAP_STAT_04_T        shp_core1_tmap_stat_04;	//0xC902CA10
	PE_E60_SHP_CORE1_TMAP_STAT_05_T        shp_core1_tmap_stat_05;	//0xC902CA14
	PE_E60_SHP_CORE1_TMAP_STAT_06_T        shp_core1_tmap_stat_06;	//0xC902CA18
	PE_E60_SHP_CORE1_TMAP_STAT_07_T        shp_core1_tmap_stat_07;	//0xC902CA1C
	UINT32                                                  reserved243;	//0xC902CA20
	UINT32                                                  reserved244;	//0xC902CA24
	UINT32                                                  reserved245;	//0xC902CA28
	UINT32                                                  reserved246;	//0xC902CA2C
	UINT32                                                  reserved247;	//0xC902CA30
	UINT32                                                  reserved248;	//0xC902CA34
	UINT32                                                  reserved249;	//0xC902CA38
	UINT32                                                  reserved250;	//0xC902CA3C
	UINT32                                                  reserved251;	//0xC902CA40
	UINT32                                                  reserved252;	//0xC902CA44
	UINT32                                                  reserved253;	//0xC902CA48
	UINT32                                                  reserved254;	//0xC902CA4C
	UINT32                                                  reserved255;	//0xC902CA50
	UINT32                                                  reserved256;	//0xC902CA54
	UINT32                                                  reserved257;	//0xC902CA58
	UINT32                                                  reserved258;	//0xC902CA5C
	UINT32                                                  reserved259;	//0xC902CA60
	UINT32                                                  reserved260;	//0xC902CA64
	UINT32                                                  reserved261;	//0xC902CA68
	UINT32                                                  reserved262;	//0xC902CA6C
	UINT32                                                  reserved263;	//0xC902CA70
	UINT32                                                  reserved264;	//0xC902CA74
	UINT32                                                  reserved265;	//0xC902CA78
	UINT32                                                  reserved266;	//0xC902CA7C
	UINT32                                                  reserved267;	//0xC902CA80
	UINT32                                                  reserved268;	//0xC902CA84
	UINT32                                                  reserved269;	//0xC902CA88
	UINT32                                                  reserved270;	//0xC902CA8C
	UINT32                                                  reserved271;	//0xC902CA90
	UINT32                                                  reserved272;	//0xC902CA94
	UINT32                                                  reserved273;	//0xC902CA98
	UINT32                                                  reserved274;	//0xC902CA9C
	UINT32                                                  reserved275;	//0xC902CAA0
	UINT32                                                  reserved276;	//0xC902CAA4
	UINT32                                                  reserved277;	//0xC902CAA8
	UINT32                                                  reserved278;	//0xC902CAAC
	UINT32                                                  reserved279;	//0xC902CAB0
	UINT32                                                  reserved280;	//0xC902CAB4
	UINT32                                                  reserved281;	//0xC902CAB8
	UINT32                                                  reserved282;	//0xC902CABC
	UINT32                                                  reserved283;	//0xC902CAC0
	UINT32                                                  reserved284;	//0xC902CAC4
	UINT32                                                  reserved285;	//0xC902CAC8
	UINT32                                                  reserved286;	//0xC902CACC
	UINT32                                                  reserved287;	//0xC902CAD0
	UINT32                                                  reserved288;	//0xC902CAD4
	UINT32                                                  reserved289;	//0xC902CAD8
	UINT32                                                  reserved290;	//0xC902CADC
	UINT32                                                  reserved291;	//0xC902CAE0
	UINT32                                                  reserved292;	//0xC902CAE4
	UINT32                                                  reserved293;	//0xC902CAE8
	UINT32                                                  reserved294;	//0xC902CAEC
	UINT32                                                  reserved295;	//0xC902CAF0
	UINT32                                                  reserved296;	//0xC902CAF4
	UINT32                                                  reserved297;	//0xC902CAF8
	UINT32                                                  reserved298;	//0xC902CAFC
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_00_T shp_core0_face_win_ctrl_00;	//0xC902CB00
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_01_T shp_core0_face_win_ctrl_01;	//0xC902CB04
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_02_T shp_core0_face_win_ctrl_02;	//0xC902CB08
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_03_T shp_core0_face_win_ctrl_03;	//0xC902CB0C
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_04_T shp_core0_face_win_ctrl_04;	//0xC902CB10
	PE_E60_SHP_CORE0_FACE_WIN_CTRL_05_T shp_core0_face_win_ctrl_05;	//0xC902CB14
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_00_T shp_core1_face_win_ctrl_00;	//0xC902CB18
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_01_T shp_core1_face_win_ctrl_01;	//0xC902CB1C
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_02_T shp_core1_face_win_ctrl_02;	//0xC902CB20
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_03_T shp_core1_face_win_ctrl_03;	//0xC902CB24
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_04_T shp_core1_face_win_ctrl_04;	//0xC902CB28
	PE_E60_SHP_CORE1_FACE_WIN_CTRL_05_T shp_core1_face_win_ctrl_05;	//0xC902CB2C
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_00_T shp_core0_body_win_ctrl_00;	//0xC902CB30
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_01_T shp_core0_body_win_ctrl_01;	//0xC902CB34
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_02_T shp_core0_body_win_ctrl_02;	//0xC902CB38
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_03_T shp_core0_body_win_ctrl_03;	//0xC902CB3C
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_04_T shp_core0_body_win_ctrl_04;	//0xC902CB40
	PE_E60_SHP_CORE0_BODY_WIN_CTRL_05_T shp_core0_body_win_ctrl_05;	//0xC902CB44
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_00_T shp_core1_body_win_ctrl_00;	//0xC902CB48
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_01_T shp_core1_body_win_ctrl_01;	//0xC902CB4C
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_02_T shp_core1_body_win_ctrl_02;	//0xC902CB50
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_03_T shp_core1_body_win_ctrl_03;	//0xC902CB54
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_04_T shp_core1_body_win_ctrl_04;	//0xC902CB58
	PE_E60_SHP_CORE1_BODY_WIN_CTRL_05_T shp_core1_body_win_ctrl_05;	//0xC902CB5C
	UINT32                                                  reserved299;	//0xC902CB60
	UINT32                                                  reserved300;	//0xC902CB64
	UINT32                                                  reserved301;	//0xC902CB68
	UINT32                                                  reserved302;	//0xC902CB6C
	UINT32                                                  reserved303;	//0xC902CB70
	UINT32                                                  reserved304;	//0xC902CB74
	UINT32                                                  reserved305;	//0xC902CB78
	UINT32                                                  reserved306;	//0xC902CB7C
	UINT32                                                  reserved307;	//0xC902CB80
	UINT32                                                  reserved308;	//0xC902CB84
	UINT32                                                  reserved309;	//0xC902CB88
	UINT32                                                  reserved310;	//0xC902CB8C
	UINT32                                                  reserved311;	//0xC902CB90
	UINT32                                                  reserved312;	//0xC902CB94
	UINT32                                                  reserved313;	//0xC902CB98
	UINT32                                                  reserved314;	//0xC902CB9C
	UINT32                                                  reserved315;	//0xC902CBA0
	UINT32                                                  reserved316;	//0xC902CBA4
	UINT32                                                  reserved317;	//0xC902CBA8
	UINT32                                                  reserved318;	//0xC902CBAC
	UINT32                                                  reserved319;	//0xC902CBB0
	UINT32                                                  reserved320;	//0xC902CBB4
	UINT32                                                  reserved321;	//0xC902CBB8
	UINT32                                                  reserved322;	//0xC902CBBC
	UINT32                                                  reserved323;	//0xC902CBC0
	UINT32                                                  reserved324;	//0xC902CBC4
	UINT32                                                  reserved325;	//0xC902CBC8
	UINT32                                                  reserved326;	//0xC902CBCC
	UINT32                                                  reserved327;	//0xC902CBD0
	UINT32                                                  reserved328;	//0xC902CBD4
	UINT32                                                  reserved329;	//0xC902CBD8
	UINT32                                                  reserved330;	//0xC902CBDC
	UINT32                                                  reserved331;	//0xC902CBE0
	UINT32                                                  reserved332;	//0xC902CBE4
	UINT32                                                  reserved333;	//0xC902CBE8
	UINT32                                                  reserved334;	//0xC902CBEC
	PE_E60_SHP_FSW_CTRL_00_T                      shp_fsw_ctrl_00;	//0xC902CBF0
	PE_E60_SHP_FSW_CTRL_01_T                      shp_fsw_ctrl_01;	//0xC902CBF4
	PE_E60_SHP_FSW_CTRL_02_T                      shp_fsw_ctrl_02;	//0xC902CBF8
	PE_E60_SHP_FSW_CTRL_03_T                      shp_fsw_ctrl_03;	//0xC902CBFC
}PE_SHP_REG_E60_T;

typedef struct {
	PE_E60_VSD_PSP_CTRL00_O_T                            psp_ctrl00;	//0xC9029300
	PE_E60_VSD_PSP_CTRL01_O_T                            psp_ctrl01;	//0xC9029304
	PE_E60_VSD_PSP_CTRL02_O_T                            psp_ctrl02;	//0xC9029308
	PE_E60_VSD_EDGE_TH_O_T                                  edge_th;	//0xC902930C
	PE_E60_VSD_FG_POSITION_O_T                          fg_position;	//0xC9029310
	PE_E60_VSD_PERSPECT_LUT_X0_O_T                  perspect_lut_x0;	//0xC9029314
	PE_E60_VSD_PERSPECT_LUT_X1_O_T                  perspect_lut_x1;	//0xC9029318
	PE_E60_VSD_PERSPECT_LUT_X2_O_T                  perspect_lut_x2;	//0xC902931C
	PE_E60_VSD_PERSPECT_LUT_X3_O_T                  perspect_lut_x3;	//0xC9029320
	PE_E60_VSD_PERSPECT_LUT_Y0_O_T                  perspect_lut_y0;	//0xC9029324
	PE_E60_VSD_PERSPECT_LUT_Y1_O_T                  perspect_lut_y1;	//0xC9029328
	PE_E60_VSD_PERSPECT_LUT_Y2_O_T                  perspect_lut_y2;	//0xC902932C
	PE_E60_VSD_PERSPECT_LUT_Y3_O_T                  perspect_lut_y3;	//0xC9029330
	PE_E60_VSD_PROB_MAP_O_T                                prob_map;	//0xC9029334
	PE_E60_VSD_ELLIPS_MAP_O_T                            ellips_map;	//0xC9029338
	PE_E60_VSD_PROB_DIFF_MAP_O_T                      prob_diff_map;	//0xC902933C
	PE_E60_VSD_OBJECT_MAP_O_T                            object_map;	//0xC9029340
	PE_E60_VSD_BLUR_MAP_O_T                                blur_map;	//0xC9029344
	PE_E60_VSD_DISPLAY_DEBUG_MAP_O_T              display_debug_map;	//0xC9029348
	PE_E60_VSD_PSP_IIR_O_T                                  psp_iir;	//0xC902934C
	PE_E60_VSD_PSP_GAIN_O_T                                psp_gain;	//0xC9029350
	PE_E60_VSD_PSP_DBG_MON00_O_T                      psp_dbg_mon00;	//0xC9029354
	PE_E60_VSD_PSP_DBG_MON01_O_T                      psp_dbg_mon01;	//0xC9029358
	PE_E60_VSD_RESERVED00_O_T                            reserved00;	//0xC902935C
	PE_E60_VSD_BLUR_HCOEF01_O_T                        blur_hcoef01;	//0xC9029360
	PE_E60_VSD_BLUR_HCOEF23_O_T                        blur_hcoef23;	//0xC9029364
	PE_E60_VSD_BLUR_HCOEF45_O_T                        blur_hcoef45;	//0xC9029368
	PE_E60_VSD_BLUR_HCOEF67_O_T                        blur_hcoef67;	//0xC902936C
	PE_E60_VSD_BLUR_HCOEF8_O_T                          blur_hcoef8;	//0xC9029370
	PE_E60_VSD_BLUR_VCOEF01_O_T                        blur_vcoef01;	//0xC9029374
	PE_E60_VSD_BLUR_VCOEF23_O_T                        blur_vcoef23;	//0xC9029378
	PE_E60_VSD_BLUR_VCOEF4_O_T                          blur_vcoef4;	//0xC902937C
	PE_E60_VSD_HISTOGRAM_0_O_T                          histogram_0;	//0xC9029380
	PE_E60_VSD_HISTOGRAM_1_O_T                          histogram_1;	//0xC9029384
	PE_E60_VSD_HISTOGRAM_2_O_T                          histogram_2;	//0xC9029388
	PE_E60_VSD_HISTOGRAM_3_O_T                          histogram_3;	//0xC902938C
	PE_E60_VSD_HISTOGRAM_4_O_T                          histogram_4;	//0xC9029390
	PE_E60_VSD_HISTOGRAM_5_O_T                          histogram_5;	//0xC9029394
	PE_E60_VSD_HISTOGRAM_6_O_T                          histogram_6;	//0xC9029398
	PE_E60_VSD_HISTOGRAM_7_O_T                          histogram_7;	//0xC902939C
	PE_E60_VSD_HISTOGRAM_8_O_T                          histogram_8;	//0xC90293A0
	PE_E60_VSD_HISTOGRAM_9_O_T                          histogram_9;	//0xC90293A4
	PE_E60_VSD_HISTOGRAM_10_O_T                        histogram_10;	//0xC90293A8
	PE_E60_VSD_HISTOGRAM_11_O_T                        histogram_11;	//0xC90293AC
	PE_E60_VSD_HISTOGRAM_12_O_T                        histogram_12;	//0xC90293B0
	PE_E60_VSD_HISTOGRAM_13_O_T                        histogram_13;	//0xC90293B4
	PE_E60_VSD_HISTOGRAM_14_O_T                        histogram_14;	//0xC90293B8
	PE_E60_VSD_HISTOGRAM_15_O_T                        histogram_15;	//0xC90293BC
	PE_E60_VSD_HISTOGRAM_16_O_T                        histogram_16;	//0xC90293C0
	PE_E60_VSD_HISTOGRAM_17_O_T                        histogram_17;	//0xC90293C4
	PE_E60_VSD_HISTOGRAM_18_O_T                        histogram_18;	//0xC90293C8
	PE_E60_VSD_HISTOGRAM_19_O_T                        histogram_19;	//0xC90293CC
	PE_E60_VSD_HISTOGRAM_20_O_T                        histogram_20;	//0xC90293D0
	PE_E60_VSD_HISTOGRAM_21_O_T                        histogram_21;	//0xC90293D4
	PE_E60_VSD_HISTOGRAM_22_O_T                        histogram_22;	//0xC90293D8
	PE_E60_VSD_HISTOGRAM_23_O_T                        histogram_23;	//0xC90293DC
	PE_E60_VSD_HISTOGRAM_24_O_T                        histogram_24;	//0xC90293E0
	PE_E60_VSD_HISTOGRAM_25_O_T                        histogram_25;	//0xC90293E4
	PE_E60_VSD_HISTOGRAM_26_O_T                        histogram_26;	//0xC90293E8
	PE_E60_VSD_HISTOGRAM_27_O_T                        histogram_27;	//0xC90293EC
	PE_E60_VSD_HISTOGRAM_28_O_T                        histogram_28;	//0xC90293F0
	PE_E60_VSD_HISTOGRAM_29_O_T                        histogram_29;	//0xC90293F4
	PE_E60_VSD_HISTOGRAM_30_O_T                        histogram_30;	//0xC90293F8
	PE_E60_VSD_HISTOGRAM_31_O_T                        histogram_31;	//0xC90293FC
	PE_E60_VSD_L5_GAIN_LUT1_O_T                        l5_gain_lut1;	//0xC9029400
	PE_E60_VSD_L5_GAIN_LUT2_O_T                        l5_gain_lut2;	//0xC9029404
	PE_E60_VSD_FG_GAIN_LUT1_O_T                        fg_gain_lut1;	//0xC9029408
	PE_E60_VSD_FG_GAIN_LUT2_O_T                        fg_gain_lut2;	//0xC902940C
	PE_E60_VSD_EDGE_WIN_H_O_T                            edge_win_h;	//0xC9029410
	PE_E60_VSD_EDGE_WIN_V_O_T                            edge_win_v;	//0xC9029414
	PE_E60_VSD_EDGE0_FG_O_T                                edge0_fg;	//0xC9029418
	PE_E60_VSD_EDGE0_BG_O_T                                edge0_bg;	//0xC902941C
	PE_E60_VSD_EDGE1_FG_O_T                                edge1_fg;	//0xC9029420
	PE_E60_VSD_EDGE1_BG_O_T                                edge1_bg;	//0xC9029424
	PE_E60_VSD_PSP_IIR1_O_T                                psp_iir1;	//0xC9029428
	UINT32                                                    reserved0;	//0xC902942C
	UINT32                                                    reserved1;	//0xC9029430
	UINT32                                                    reserved2;	//0xC9029434
	UINT32                                                    reserved3;	//0xC9029438
	UINT32                                                    reserved4;	//0xC902943C
	UINT32                                                    reserved5;	//0xC9029440
	PE_E60_VSD_FACE0_SET_O_T                              face0_set;	//0xC9029444
	PE_E60_VSD_FACE1_SET_O_T                              face1_set;	//0xC9029448
	PE_E60_VSD_FACE2_SET_O_T                              face2_set;	//0xC902944C
	PE_E60_VSD_FACE3_SET_O_T                              face3_set;	//0xC9029450
	PE_E60_VSD_ELLIPS0_SET_O_T                          ellips0_set;	//0xC9029454
	PE_E60_VSD_ELLIPS1_SET_O_T                          ellips1_set;	//0xC9029458
	PE_E60_VSD_ELLIPS2_SET_O_T                          ellips2_set;	//0xC902945C
	PE_E60_VSD_ELLIPS3_SET_O_T                          ellips3_set;	//0xC9029460
	UINT32                                                    reserved6;	//0xC9029464
	UINT32                                                    reserved7;	//0xC9029468
	PE_E60_VSD_PSP_MEM_O_T                                  psp_mem;	//0xC902946C
	PE_E60_VSD_REFINE_CTRL0_O_T                        refine_ctrl0;	//0xC9029470
	PE_E60_VSD_REFINE_CTRL1_O_T                        refine_ctrl1;	//0xC9029474
	PE_E60_VSD_REFINE_CTRL2_O_T                        refine_ctrl2;	//0xC9029478
	PE_E60_VSD_REFINE_CTRL3_O_T                        refine_ctrl3;	//0xC902947C
	PE_E60_VSD_REFINE_CTRL4_O_T                        refine_ctrl4;	//0xC9029480
	PE_E60_VSD_ALPHA_GAIN_LUT1_O_T                  alpha_gain_lut1;	//0xC9029484
	PE_E60_VSD_ALPHA_GAIN_LUT2_O_T                  alpha_gain_lut2;	//0xC9029488
	PE_E60_VSD_ALPHA_GAIN_LUT3_O_T                  alpha_gain_lut3;	//0xC902948C
	PE_E60_VSD_ELLIPS0_SET1_O_T                        ellips0_set1;	//0xC9029490
	PE_E60_VSD_ELLIPS0_SET2_O_T                        ellips0_set2;	//0xC9029494
	PE_E60_VSD_ELLIPS1_SET1_O_T                        ellips1_set1;	//0xC9029498
	PE_E60_VSD_ELLIPS1_SET2_O_T                        ellips1_set2;	//0xC902949C
	PE_E60_VSD_ELLIPS2_SET1_O_T                        ellips2_set1;	//0xC90294A0
	PE_E60_VSD_ELLIPS2_SET2_O_T                        ellips2_set2;	//0xC90294A4
	PE_E60_VSD_ELLIPS3_SET1_O_T                        ellips3_set1;	//0xC90294A8
	PE_E60_VSD_ELLIPS3_SET2_O_T                        ellips3_set2;	//0xC90294AC
	PE_E60_VSD_FACE0_SET1_O_T                            face0_set1;	//0xC90294B0
	PE_E60_VSD_FACE1_SET1_O_T                            face1_set1;	//0xC90294B4
	PE_E60_VSD_FACE2_SET1_O_T                            face2_set1;	//0xC90294B8
	PE_E60_VSD_FACE3_SET1_O_T                            face3_set1;	//0xC90294BC
	PE_E60_VSD_FACE0_SET2_O_T                            face0_set2;	//0xC90294C0
	PE_E60_VSD_FACE1_SET2_O_T                            face1_set2;	//0xC90294C4
	PE_E60_VSD_FACE2_SET2_O_T                            face2_set2;	//0xC90294C8
	PE_E60_VSD_FACE3_SET2_O_T                            face3_set2;	//0xC90294CC
	PE_E60_VSD_FACE_SET_CTRL_O_T                      face_set_ctrl;	//0xC90294D0
}PE_VSD_OBC_OBJT_REG_E60_T;

typedef struct {
	PE_E60_VSD_PSP_CTRL00_T                            psp_ctrl00;	//0xC9029500
	PE_E60_VSD_PSP_CTRL01_T                            psp_ctrl01;	//0xC9029504
	PE_E60_VSD_PSP_CTRL02_T                            psp_ctrl02;	//0xC9029508
	PE_E60_VSD_EDGE_TH_T                                  edge_th;	//0xC902950C
	PE_E60_VSD_FG_POSITION_T                          fg_position;	//0xC9029510
	PE_E60_VSD_PERSPECT_LUT_X0_T                  perspect_lut_x0;	//0xC9029514
	PE_E60_VSD_PERSPECT_LUT_X1_T                  perspect_lut_x1;	//0xC9029518
	PE_E60_VSD_PERSPECT_LUT_X2_T                  perspect_lut_x2;	//0xC902951C
	PE_E60_VSD_PERSPECT_LUT_X3_T                  perspect_lut_x3;	//0xC9029520
	PE_E60_VSD_PERSPECT_LUT_Y0_T                  perspect_lut_y0;	//0xC9029524
	PE_E60_VSD_PERSPECT_LUT_Y1_T                  perspect_lut_y1;	//0xC9029528
	PE_E60_VSD_PERSPECT_LUT_Y2_T                  perspect_lut_y2;	//0xC902952C
	PE_E60_VSD_PERSPECT_LUT_Y3_T                  perspect_lut_y3;	//0xC9029530
	PE_E60_VSD_PROB_MAP_T                                prob_map;	//0xC9029534
	PE_E60_VSD_ELLIPS_MAP_T                            ellips_map;	//0xC9029538
	PE_E60_VSD_PROB_DIFF_MAP_T                      prob_diff_map;	//0xC902953C
	PE_E60_VSD_OBJECT_MAP_T                            object_map;	//0xC9029540
	PE_E60_VSD_BLUR_MAP_T                                blur_map;	//0xC9029544
	PE_E60_VSD_DISPLAY_DEBUG_MAP_T              display_debug_map;	//0xC9029548
	PE_E60_VSD_PSP_IIR_T                                  psp_iir;	//0xC902954C
	PE_E60_VSD_PSP_GAIN_T                                psp_gain;	//0xC9029550
	PE_E60_VSD_PSP_DBG_MON00_T                      psp_dbg_mon00;	//0xC9029554
	PE_E60_VSD_PSP_DBG_MON01_T                      psp_dbg_mon01;	//0xC9029558
	PE_E60_VSD_RESERVED00_T                            reserved00;	//0xC902955C
	PE_E60_VSD_BLUR_HCOEF01_T                        blur_hcoef01;	//0xC9029560
	PE_E60_VSD_BLUR_HCOEF23_T                        blur_hcoef23;	//0xC9029564
	PE_E60_VSD_BLUR_HCOEF45_T                        blur_hcoef45;	//0xC9029568
	PE_E60_VSD_BLUR_HCOEF67_T                        blur_hcoef67;	//0xC902956C
	PE_E60_VSD_BLUR_HCOEF8_T                          blur_hcoef8;	//0xC9029570
	PE_E60_VSD_BLUR_VCOEF01_T                        blur_vcoef01;	//0xC9029574
	PE_E60_VSD_BLUR_VCOEF23_T                        blur_vcoef23;	//0xC9029578
	PE_E60_VSD_BLUR_VCOEF4_T                          blur_vcoef4;	//0xC902957C
	PE_E60_VSD_HISTOGRAM_0_T                          histogram_0;	//0xC9029580
	PE_E60_VSD_HISTOGRAM_1_T                          histogram_1;	//0xC9029584
	PE_E60_VSD_HISTOGRAM_2_T                          histogram_2;	//0xC9029588
	PE_E60_VSD_HISTOGRAM_3_T                          histogram_3;	//0xC902958C
	PE_E60_VSD_HISTOGRAM_4_T                          histogram_4;	//0xC9029590
	PE_E60_VSD_HISTOGRAM_5_T                          histogram_5;	//0xC9029594
	PE_E60_VSD_HISTOGRAM_6_T                          histogram_6;	//0xC9029598
	PE_E60_VSD_HISTOGRAM_7_T                          histogram_7;	//0xC902959C
	PE_E60_VSD_HISTOGRAM_8_T                          histogram_8;	//0xC90295A0
	PE_E60_VSD_HISTOGRAM_9_T                          histogram_9;	//0xC90295A4
	PE_E60_VSD_HISTOGRAM_10_T                        histogram_10;	//0xC90295A8
	PE_E60_VSD_HISTOGRAM_11_T                        histogram_11;	//0xC90295AC
	PE_E60_VSD_HISTOGRAM_12_T                        histogram_12;	//0xC90295B0
	PE_E60_VSD_HISTOGRAM_13_T                        histogram_13;	//0xC90295B4
	PE_E60_VSD_HISTOGRAM_14_T                        histogram_14;	//0xC90295B8
	PE_E60_VSD_HISTOGRAM_15_T                        histogram_15;	//0xC90295BC
	PE_E60_VSD_HISTOGRAM_16_T                        histogram_16;	//0xC90295C0
	PE_E60_VSD_HISTOGRAM_17_T                        histogram_17;	//0xC90295C4
	PE_E60_VSD_HISTOGRAM_18_T                        histogram_18;	//0xC90295C8
	PE_E60_VSD_HISTOGRAM_19_T                        histogram_19;	//0xC90295CC
	PE_E60_VSD_HISTOGRAM_20_T                        histogram_20;	//0xC90295D0
	PE_E60_VSD_HISTOGRAM_21_T                        histogram_21;	//0xC90295D4
	PE_E60_VSD_HISTOGRAM_22_T                        histogram_22;	//0xC90295D8
	PE_E60_VSD_HISTOGRAM_23_T                        histogram_23;	//0xC90295DC
	PE_E60_VSD_HISTOGRAM_24_T                        histogram_24;	//0xC90295E0
	PE_E60_VSD_HISTOGRAM_25_T                        histogram_25;	//0xC90295E4
	PE_E60_VSD_HISTOGRAM_26_T                        histogram_26;	//0xC90295E8
	PE_E60_VSD_HISTOGRAM_27_T                        histogram_27;	//0xC90295EC
	PE_E60_VSD_HISTOGRAM_28_T                        histogram_28;	//0xC90295F0
	PE_E60_VSD_HISTOGRAM_29_T                        histogram_29;	//0xC90295F4
	PE_E60_VSD_HISTOGRAM_30_T                        histogram_30;	//0xC90295F8
	PE_E60_VSD_HISTOGRAM_31_T                        histogram_31;	//0xC90295FC
	PE_E60_VSD_L5_GAIN_LUT1_T                        l5_gain_lut1;	//0xC9029600
	PE_E60_VSD_L5_GAIN_LUT2_T                        l5_gain_lut2;	//0xC9029604
	PE_E60_VSD_FG_GAIN_LUT1_T                        fg_gain_lut1;	//0xC9029608
	PE_E60_VSD_FG_GAIN_LUT2_T                        fg_gain_lut2;	//0xC902960C
	PE_E60_VSD_EDGE_WIN_H_T                            edge_win_h;	//0xC9029610
	PE_E60_VSD_EDGE_WIN_V_T                            edge_win_v;	//0xC9029614
	PE_E60_VSD_EDGE0_FG_T                                edge0_fg;	//0xC9029618
	PE_E60_VSD_EDGE0_BG_T                                edge0_bg;	//0xC902961C
	PE_E60_VSD_EDGE1_FG_T                                edge1_fg;	//0xC9029620
	PE_E60_VSD_EDGE1_BG_T                                edge1_bg;	//0xC9029624
	PE_E60_VSD_PSP_IIR1_T                                psp_iir1;	//0xC9029628
	UINT32                                                    reserved0;	//0xC902962C
	UINT32                                                    reserved1;	//0xC9029630
	UINT32                                                    reserved2;	//0xC9029634
	UINT32                                                    reserved3;	//0xC9029638
	UINT32                                                    reserved4;	//0xC902963C
	UINT32                                                    reserved5;	//0xC9029640
	PE_E60_VSD_FACE0_SET_T                              face0_set;	//0xC9029644
	PE_E60_VSD_FACE1_SET_T                              face1_set;	//0xC9029648
	PE_E60_VSD_FACE2_SET_T                              face2_set;	//0xC902964C
	PE_E60_VSD_FACE3_SET_T                              face3_set;	//0xC9029650
	PE_E60_VSD_ELLIPS0_SET_T                          ellips0_set;	//0xC9029654
	PE_E60_VSD_ELLIPS1_SET_T                          ellips1_set;	//0xC9029658
	PE_E60_VSD_ELLIPS2_SET_T                          ellips2_set;	//0xC902965C
	PE_E60_VSD_ELLIPS3_SET_T                          ellips3_set;	//0xC9029660
	PE_E60_VSD_BUFFER_CTRL0_T                        buffer_ctrl0;	//0xC9029664
	PE_E60_VSD_BUFFER_CTRL1_T                        buffer_ctrl1;	//0xC9029668
	PE_E60_VSD_PSP_MEM_T                                  psp_mem;	//0xC902966C
	PE_E60_VSD_REFINE_CTRL0_T                        refine_ctrl0;	//0xC9029670
	PE_E60_VSD_REFINE_CTRL1_T                        refine_ctrl1;	//0xC9029674
	PE_E60_VSD_REFINE_CTRL2_T                        refine_ctrl2;	//0xC9029678
	PE_E60_VSD_REFINE_CTRL3_T                        refine_ctrl3;	//0xC902967C
	PE_E60_VSD_REFINE_CTRL4_T                        refine_ctrl4;	//0xC9029680
	PE_E60_VSD_ALPHA_GAIN_LUT1_T                  alpha_gain_lut1;	//0xC9029684
	PE_E60_VSD_ALPHA_GAIN_LUT2_T                  alpha_gain_lut2;	//0xC9029688
	PE_E60_VSD_ALPHA_GAIN_LUT3_T                  alpha_gain_lut3;	//0xC902968C
	PE_E60_VSD_ELLIPS0_SET1_T                        ellips0_set1;	//0xC9029690
	PE_E60_VSD_ELLIPS0_SET2_T                        ellips0_set2;	//0xC9029694
	PE_E60_VSD_ELLIPS1_SET1_T                        ellips1_set1;	//0xC9029698
	PE_E60_VSD_ELLIPS1_SET2_T                        ellips1_set2;	//0xC902969C
	PE_E60_VSD_ELLIPS2_SET1_T                        ellips2_set1;	//0xC90296A0
	PE_E60_VSD_ELLIPS2_SET2_T                        ellips2_set2;	//0xC90296A4
	PE_E60_VSD_ELLIPS3_SET1_T                        ellips3_set1;	//0xC90296A8
	PE_E60_VSD_ELLIPS3_SET2_T                        ellips3_set2;	//0xC90296AC
	PE_E60_VSD_FACE0_SET1_T                            face0_set1;	//0xC90296B0
	PE_E60_VSD_FACE1_SET1_T                            face1_set1;	//0xC90296B4
	PE_E60_VSD_FACE2_SET1_T                            face2_set1;	//0xC90296B8
	PE_E60_VSD_FACE3_SET1_T                            face3_set1;	//0xC90296BC
	PE_E60_VSD_FACE0_SET2_T                            face0_set2;	//0xC90296C0
	PE_E60_VSD_FACE1_SET2_T                            face1_set2;	//0xC90296C4
	PE_E60_VSD_FACE2_SET2_T                            face2_set2;	//0xC90296C8
	PE_E60_VSD_FACE3_SET2_T                            face3_set2;	//0xC90296CC
	PE_E60_VSD_FACE_SET_CTRL_T                      face_set_ctrl;	//0xC90296D0
}PE_VSD_OBC_FACE_REG_E60_T;

typedef struct {
	PE_E60_DTM_TOP_CTRL_00_T                           dtm_top_ctrl_00;	//0xC9029C00
	PE_E60_DTM_TOP_CTRL_01_T                           dtm_top_ctrl_01;	//0xC9029C04
	PE_E60_DTM_TOP_CTRL_02_T                           dtm_top_ctrl_02;	//0xC9029C08
	PE_E60_DTM_TOP_CTRL_03_T                           dtm_top_ctrl_03;	//0xC9029C0C
	PE_E60_DTM_TOP_CTRL_04_T                           dtm_top_ctrl_04;	//0xC9029C10
	PE_E60_DTM_TOP_CTRL_05_T                           dtm_top_ctrl_05;	//0xC9029C14
	UINT32                                                    reserved0;	//0xC9029C18
	UINT32                                                    reserved1;	//0xC9029C1C
	PE_E60_DTM_FSW_CTRL_00_T                           dtm_fsw_ctrl_00;	//0xC9029C20
	PE_E60_DTM_FSW_CTRL_01_T                           dtm_fsw_ctrl_01;	//0xC9029C24
	PE_E60_DTM_FSW_CTRL_02_T                           dtm_fsw_ctrl_02;	//0xC9029C28
	PE_E60_DTM_FSW_CTRL_03_T                           dtm_fsw_ctrl_03;	//0xC9029C2C
	UINT32                                                    reserved2;	//0xC9029C30
	UINT32                                                    reserved3;	//0xC9029C34
	UINT32                                                    reserved4;	//0xC9029C38
	UINT32                                                    reserved5;	//0xC9029C3C
	PE_E60_DTM_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0xC9029C40
	PE_E60_DTM_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0xC9029C44
	PE_E60_DTM_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0xC9029C48
	PE_E60_DTM_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0xC9029C4C
	PE_E60_DTM_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0xC9029C50
	PE_E60_DTM_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0xC9029C54
	PE_E60_DTM_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0xC9029C58
	PE_E60_DTM_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0xC9029C5C
	PE_E60_DTM_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0xC9029C60
	UINT32                                                    reserved6;	//0xC9029C64
	UINT32                                                    reserved7;	//0xC9029C68
	UINT32                                                    reserved8;	//0xC9029C6C
	PE_E60_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xC9029C70
	PE_E60_DTM_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0xC9029C74
	PE_E60_DTM_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0xC9029C78
	PE_E60_DTM_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0xC9029C7C
	PE_E60_DTM_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0xC9029C80
	PE_E60_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xC9029C84
	PE_E60_DTM_LLUT0_IA_CTRL_T                       dtm_llut0_ia_ctrl;	//0xC9029C88
	PE_E60_DTM_LLUT0_IA_DATA_T                       dtm_llut0_ia_data;	//0xC9029C8C
	PE_E60_DTM_LLUT1_IA_CTRL_T                       dtm_llut1_ia_ctrl;	//0xC9029C90
	PE_E60_DTM_LLUT1_IA_DATA_T                       dtm_llut1_ia_data;	//0xC9029C94
	PE_E60_DTM_LLUT2_IA_CTRL_T                       dtm_llut2_ia_ctrl;	//0xC9029C98
	PE_E60_DTM_LLUT2_IA_DATA_T                       dtm_llut2_ia_data;	//0xC9029C9C
	UINT32                                                    reserved9;	//0xC9029CA0
	UINT32                                                   reserved10;	//0xC9029CA4
	UINT32                                                   reserved11;	//0xC9029CA8
	UINT32                                                   reserved12;	//0xC9029CAC
	PE_E60_DTM_CSC3_CTRL_00_T                         dtm_csc3_ctrl_00;	//0xC9029CB0
	PE_E60_DTM_CSC3_CTRL_01_T                         dtm_csc3_ctrl_01;	//0xC9029CB4
	PE_E60_DTM_CSC3_CTRL_02_T                         dtm_csc3_ctrl_02;	//0xC9029CB8
	PE_E60_DTM_CSC3_CTRL_03_T                         dtm_csc3_ctrl_03;	//0xC9029CBC
	PE_E60_DTM_CSC3_CTRL_04_T                         dtm_csc3_ctrl_04;	//0xC9029CC0
	PE_E60_DTM_CSC3_CTRL_05_T                         dtm_csc3_ctrl_05;	//0xC9029CC4
	PE_E60_DTM_CSC3_CTRL_06_T                         dtm_csc3_ctrl_06;	//0xC9029CC8
	PE_E60_DTM_CSC3_CTRL_07_T                         dtm_csc3_ctrl_07;	//0xC9029CCC
	PE_E60_DTM_CSC3_CTRL_08_T                         dtm_csc3_ctrl_08;	//0xC9029CD0
	UINT32                                                   reserved13;	//0xC9029CD4
	UINT32                                                   reserved14;	//0xC9029CD8
	UINT32                                                   reserved15;	//0xC9029CDC
	PE_E60_DTM_HUE_SAT_CTRL_T                         dtm_hue_sat_ctrl;	//0xC9029CE0
	UINT32                                                   reserved16;	//0xC9029CE4
	UINT32                                                   reserved17;	//0xC9029CE8
	UINT32                                                   reserved18;	//0xC9029CEC
	PE_E60_DTM_LLUT_WIN_CTRL_01_T                 dtm_llut_win_ctrl_01;	//0xC9029CF0
	PE_E60_DTM_LLUT_WIN_CTRL_02_T                 dtm_llut_win_ctrl_02;	//0xC9029CF4
	PE_E60_DTM_LLUT_WIN_CTRL_03_T                 dtm_llut_win_ctrl_03;	//0xC9029CF8
	PE_E60_DTM_LLUT_WIN_CTRL_04_T                 dtm_llut_win_ctrl_04;	//0xC9029CFC
	PE_E60_DTM_LLUT_WIN_CTRL_05_T                 dtm_llut_win_ctrl_05;	//0xC9029D00
	PE_E60_DTM_LLUT_WIN_CTRL_06_T                 dtm_llut_win_ctrl_06;	//0xC9029D04
	PE_E60_DTM_LLUT_WIN_CTRL_07_T                 dtm_llut_win_ctrl_07;	//0xC9029D08
	PE_E60_DTM_LLUT_WIN_CTRL_08_T                 dtm_llut_win_ctrl_08;	//0xC9029D0C
	PE_E60_DTM_LLUT_WIN_CTRL_09_T                 dtm_llut_win_ctrl_09;	//0xC9029D10
	PE_E60_DTM_LLUT_WIN_CTRL_10_T                 dtm_llut_win_ctrl_10;	//0xC9029D14
	PE_E60_DTM_LLUT_WIN_CTRL_11_T                 dtm_llut_win_ctrl_11;	//0xC9029D18
	PE_E60_DTM_LLUT_WIN_CTRL_12_T                 dtm_llut_win_ctrl_12;	//0xC9029D1C
	PE_E60_DTM_LLUT_WIN_CTRL_13_T                 dtm_llut_win_ctrl_13;	//0xC9029D20
	PE_E60_DTM_LLUT_WIN_CTRL_14_T                 dtm_llut_win_ctrl_14;	//0xC9029D24
	PE_E60_DTM_LLUT_WIN_CTRL_15_T                 dtm_llut_win_ctrl_15;	//0xC9029D28
	PE_E60_DTM_LLUT_WIN_CTRL_16_T                 dtm_llut_win_ctrl_16;	//0xC9029D2C
	PE_E60_DTM_LLUT_WIN_CTRL_17_T                 dtm_llut_win_ctrl_17;	//0xC9029D30
	PE_E60_DTM_LLUT_WIN_CTRL_18_T                 dtm_llut_win_ctrl_18;	//0xC9029D34
	PE_E60_DTM_LLUT_WIN_CTRL_19_T                 dtm_llut_win_ctrl_19;	//0xC9029D38
	PE_E60_DTM_LLUT_WIN_CTRL_20_T                 dtm_llut_win_ctrl_20;	//0xC9029D3C
	PE_E60_DTM_LLUT_WIN_CTRL_21_T                 dtm_llut_win_ctrl_21;	//0xC9029D40
	PE_E60_DTM_LLUT_WIN_CTRL_22_T                 dtm_llut_win_ctrl_22;	//0xC9029D44
	PE_E60_DTM_LLUT_WIN_CTRL_23_T                 dtm_llut_win_ctrl_23;	//0xC9029D48
	PE_E60_DTM_LLUT_WIN_CTRL_24_T                 dtm_llut_win_ctrl_24;	//0xC9029D4C
	PE_E60_DTM_LLUT_WIN_CTRL_25_T                 dtm_llut_win_ctrl_25;	//0xC9029D50
	PE_E60_DTM_LLUT_WIN_CTRL_26_T                 dtm_llut_win_ctrl_26;	//0xC9029D54
	PE_E60_DTM_LLUT_WIN_CTRL_27_T                 dtm_llut_win_ctrl_27;	//0xC9029D58
	PE_E60_DTM_LLUT_WIN_CTRL_28_T                 dtm_llut_win_ctrl_28;	//0xC9029D5C
}PE_VSD_DTM_REG_E60_T;

typedef struct
{ 
	PE_E60_REG_OBE_CTRL_000_T                        reg_obe_ctrl_000;	//0x0000
	PE_E60_REG_OBE_CTRL_001_T                        reg_obe_ctrl_001;	//0x0004
	PE_E60_REG_OBE_CTRL_002_T                        reg_obe_ctrl_002;	//0x0008
	PE_E60_REG_OBE_CTRL_003_T                        reg_obe_ctrl_003;	//0x000C
	PE_E60_REG_OBE_CTRL_004_T                        reg_obe_ctrl_004;	//0x0010
	PE_E60_REG_OBE_CTRL_005_T                        reg_obe_ctrl_005;	//0x0014
	PE_E60_REG_OBE_IND_CTRL_0_T                      reg_obe_ind_ctrl_0;	//0x0018
	PE_E60_REG_OBE_IND_CTRL_1_T                      reg_obe_ind_ctrl_1;	//0x001C
	PE_E60_REG_OBE_IND_CTRL_2_T                      reg_obe_ind_ctrl_2;	//0x0020
	PE_E60_REG_OBE_CTRL_009_T                        reg_obe_ctrl_009;	//0x0024
	PE_E60_REG_OBE_CTRL_010_T                        reg_obe_ctrl_010;	//0x0028
	PE_E60_REG_OBE_CTRL_011_T                        reg_obe_ctrl_011;	//0x002C
	PE_E60_REG_OBE_CTRL_012_T                        reg_obe_ctrl_012;	//0x0030
	PE_E60_REG_OBE_CTRL_013_T                        reg_obe_ctrl_013;	//0x0034
	PE_E60_REG_OBE_CTRL_014_T                        reg_obe_ctrl_014;	//0x0038
	PE_E60_REG_OBE_CTRL_015_T                        reg_obe_ctrl_015;	//0x003C
	PE_E60_REG_OBE_CTRL_016_T                        reg_obe_ctrl_016;	//0x0040
	PE_E60_REG_OBE_CTRL_017_T                        reg_obe_ctrl_017;	//0x0044
	PE_E60_REG_OBE_CTRL_018_T                        reg_obe_ctrl_018;	//0x0048
	PE_E60_REG_OBE_CTRL_019_T                        reg_obe_ctrl_019;	//0x004C
	PE_E60_REG_OBE_CTRL_020_T                        reg_obe_ctrl_020;	//0x0050
	PE_E60_REG_OBE_CTRL_021_T                        reg_obe_ctrl_021;	//0x0054
	PE_E60_REG_OBE_CTRL_022_T                        reg_obe_ctrl_022;	//0x0058
	PE_E60_REG_OBE_CTRL_023_T                        reg_obe_ctrl_023;	//0x005C
	PE_E60_REG_OBE_CTRL_024_T                        reg_obe_ctrl_024;	//0x0060
	PE_E60_REG_OBE_CTRL_025_T                        reg_obe_ctrl_025;	//0x0064
	PE_E60_REG_OBE_CTRL_026_T                        reg_obe_ctrl_026;	//0x0068
	PE_E60_REG_OBE_CTRL_027_T                        reg_obe_ctrl_027;	//0x006C
	PE_E60_REG_OBE_CTRL_028_T                        reg_obe_ctrl_028;	//0x0070
	PE_E60_REG_OBE_CTRL_029_T                        reg_obe_ctrl_029;	//0x0074
	PE_E60_REG_OBE_CTRL_030_T                        reg_obe_ctrl_030;	//0x0078
	PE_E60_REG_OBE_CTRL_031_T                        reg_obe_ctrl_031;	//0x007C
	PE_E60_REG_OBE_CTRL_032_T                        reg_obe_ctrl_032;	//0x0080
	PE_E60_REG_OBE_CTRL_033_T                        reg_obe_ctrl_033;	//0x0084
	PE_E60_REG_OBE_CTRL_034_T                        reg_obe_ctrl_034;	//0x0088
	PE_E60_REG_OBE_CTRL_035_T                        reg_obe_ctrl_035;	//0x008C
	PE_E60_REG_OBE_CTRL_036_T                        reg_obe_ctrl_036;	//0x0090
	PE_E60_REG_OBE_CTRL_037_T                        reg_obe_ctrl_037;	//0x0094
	PE_E60_REG_OBE_CTRL_038_T                        reg_obe_ctrl_038;	//0x0098
	PE_E60_REG_OBE_CTRL_039_T                        reg_obe_ctrl_039;	//0x009C
	PE_E60_REG_OBE_CTRL_040_T                        reg_obe_ctrl_040;	//0x00A0
	PE_E60_REG_OBE_CTRL_041_T                        reg_obe_ctrl_041;	//0x00A4
	PE_E60_REG_OBE_CTRL_042_T                        reg_obe_ctrl_042;	//0x00A8
	PE_E60_REG_OBE_CTRL_043_T                        reg_obe_ctrl_043;	//0x00AC
	PE_E60_REG_OBE_CTRL_044_T                        reg_obe_ctrl_044;	//0x00B0
	PE_E60_REG_OBE_CTRL_045_T                        reg_obe_ctrl_045;	//0x00B4
	PE_E60_REG_OBE_CTRL_046_T                        reg_obe_ctrl_046;	//0x00B8
	PE_E60_REG_OBE_CTRL_047_T                        reg_obe_ctrl_047;	//0x00BC
	PE_E60_REG_OBE_CTRL_048_T                        reg_obe_ctrl_048;	//0x00C0
	PE_E60_REG_OBE_CTRL_049_T                        reg_obe_ctrl_049;	//0x00C4
	PE_E60_REG_OBE_CTRL_050_T                        reg_obe_ctrl_050;	//0x00C8
	PE_E60_REG_OBE_CTRL_051_T                        reg_obe_ctrl_051;	//0x00CC
	PE_E60_REG_OBE_CTRL_052_T                        reg_obe_ctrl_052;	//0x00D0
	PE_E60_REG_OBE_CTRL_053_T                        reg_obe_ctrl_053;	//0x00D4
	PE_E60_REG_OBE_CTRL_054_T                        reg_obe_ctrl_054;	//0x00D8
	PE_E60_REG_OBE_CTRL_055_T                        reg_obe_ctrl_055;	//0x00DC
	PE_E60_REG_OBE_CTRL_056_T                        reg_obe_ctrl_056;	//0x00E0
	PE_E60_REG_OBE_CTRL_057_T                        reg_obe_ctrl_057;	//0x00E4
	PE_E60_REG_OBE_CTRL_058_T                        reg_obe_ctrl_058;	//0x00E8
	PE_E60_REG_OBE_CTRL_059_T                        reg_obe_ctrl_059;	//0x00EC
	PE_E60_REG_OBE_CTRL_060_T                        reg_obe_ctrl_060;	//0x00F0
	PE_E60_REG_OBE_CTRL_061_T                        reg_obe_ctrl_061;	//0x00F4
	PE_E60_REG_OBE_CTRL_062_T                        reg_obe_ctrl_062;	//0x00F8
	PE_E60_REG_OBE_CTRL_063_T                        reg_obe_ctrl_063;	//0x00FC
	PE_E60_REG_OBE_CTRL_064_T                        reg_obe_ctrl_064;	//0x0100
	PE_E60_REG_OBE_CTRL_065_T                        reg_obe_ctrl_065;	//0x0104
	PE_E60_REG_OBE_CTRL_066_T                        reg_obe_ctrl_066;	//0x0108
	PE_E60_REG_OBE_CTRL_067_T                        reg_obe_ctrl_067;	//0x010C
	PE_E60_REG_OBE_CTRL_068_T                        reg_obe_ctrl_068;	//0x0110
	PE_E60_REG_OBE_CTRL_069_T                        reg_obe_ctrl_069;	//0x0114
	PE_E60_REG_OBE_CTRL_070_T                        reg_obe_ctrl_070;	//0x0118
	PE_E60_REG_OBE_CTRL_071_T                        reg_obe_ctrl_071;	//0x011C
	PE_E60_REG_OBE_CTRL_072_T                        reg_obe_ctrl_072;	//0x0120
	PE_E60_REG_OBE_CTRL_073_T                        reg_obe_ctrl_073;	//0x0124
	PE_E60_REG_OBE_CTRL_074_T                        reg_obe_ctrl_074;	//0x0128
	PE_E60_REG_OBE_CTRL_075_T                        reg_obe_ctrl_075;	//0x012C
	PE_E60_REG_OBE_CTRL_076_T                        reg_obe_ctrl_076;	//0x0130
	PE_E60_REG_OBE_CTRL_077_T                        reg_obe_ctrl_077;	//0x0134
	PE_E60_REG_OBE_CTRL_078_T                        reg_obe_ctrl_078;	//0x0138
	PE_E60_REG_OBE_CTRL_079_T                        reg_obe_ctrl_079;	//0x013C
	PE_E60_REG_OBE_CTRL_080_T                        reg_obe_ctrl_080;	//0x0140
	PE_E60_REG_OBE_CTRL_081_T                        reg_obe_ctrl_081;	//0x0144
	PE_E60_REG_OBE_CTRL_082_T                        reg_obe_ctrl_082;	//0x0148
	PE_E60_REG_OBE_CTRL_083_T                        reg_obe_ctrl_083;	//0x014C
	PE_E60_REG_OBE_CTRL_084_T                        reg_obe_ctrl_084;	//0x0150
	PE_E60_REG_OBE_CTRL_085_T                        reg_obe_ctrl_085;	//0x0154
	PE_E60_REG_OBE_CTRL_086_T                        reg_obe_ctrl_086;	//0x0158
	PE_E60_REG_OBE_CTRL_087_T                        reg_obe_ctrl_087;	//0x015C
	PE_E60_REG_OBE_CTRL_088_T                        reg_obe_ctrl_088;	//0x0160
	PE_E60_REG_OBE_CTRL_089_T                        reg_obe_ctrl_089;	//0x0164
	PE_E60_REG_OBE_CTRL_090_T                        reg_obe_ctrl_090;	//0x0168
	PE_E60_REG_OBE_CTRL_091_T                        reg_obe_ctrl_091;	//0x016C
	PE_E60_REG_OBE_CTRL_092_T                        reg_obe_ctrl_092;	//0x0170
	PE_E60_REG_OBE_CTRL_093_T                        reg_obe_ctrl_093;	//0x0174
	PE_E60_REG_OBE_CTRL_094_T                        reg_obe_ctrl_094;	//0x0178
	PE_E60_REG_OBE_CTRL_095_T                        reg_obe_ctrl_095;	//0x017C
	PE_E60_REG_OBE_CTRL_096_T                        reg_obe_ctrl_096;	//0x0180
	PE_E60_REG_OBE_CTRL_097_T                        reg_obe_ctrl_097;	//0x0184
	PE_E60_REG_OBE_CTRL_098_T                        reg_obe_ctrl_098;	//0x0188
	PE_E60_REG_OBE_CTRL_099_T                        reg_obe_ctrl_099;	//0x018C
	PE_E60_REG_OBE_CTRL_100_T                        reg_obe_ctrl_100;	//0x0190
	PE_E60_REG_OBE_CTRL_101_T                        reg_obe_ctrl_101;	//0x0194
	PE_E60_REG_OBE_CTRL_102_T                        reg_obe_ctrl_102;	//0x0198
	PE_E60_REG_OBE_CTRL_103_T                        reg_obe_ctrl_103;	//0x019C
	PE_E60_REG_OBE_CTRL_104_T                        reg_obe_ctrl_104;	//0x01A0
	PE_E60_REG_OBE_CTRL_105_T                        reg_obe_ctrl_105;	//0x01A4
	PE_E60_REG_OBE_CTRL_106_T                        reg_obe_ctrl_106;	//0x01A8
	PE_E60_REG_OBE_CTRL_107_T                        reg_obe_ctrl_107;	//0x01AC
	PE_E60_REG_OBE_CTRL_108_T                        reg_obe_ctrl_108;	//0x01B0
	PE_E60_REG_OBE_CTRL_109_T                        reg_obe_ctrl_109;	//0x01B4
	PE_E60_REG_OBE_CTRL_110_T                        reg_obe_ctrl_110;	//0x01B8
	PE_E60_REG_OBE_CTRL_111_T                        reg_obe_ctrl_111;	//0x01BC
	PE_E60_REG_OBE_CTRL_112_T                        reg_obe_ctrl_112;	//0x01C0
	PE_E60_REG_OBE_CTRL_113_T                        reg_obe_ctrl_113;	//0x01C4
	PE_E60_REG_OBE_CTRL_114_T                        reg_obe_ctrl_114;	//0x01C8
	PE_E60_REG_OBE_CTRL_115_T                        reg_obe_ctrl_115;	//0x01CC
	PE_E60_REG_OBE_CTRL_116_T                        reg_obe_ctrl_116;	//0x01D0
	PE_E60_REG_OBE_CTRL_117_T                        reg_obe_ctrl_117;	//0x01D4
	PE_E60_REG_OBE_CTRL_118_T                        reg_obe_ctrl_118;	//0x01D8
	PE_E60_REG_OBE_CTRL_119_T                        reg_obe_ctrl_119;	//0x01DC
	PE_E60_REG_OBE_CTRL_120_T                        reg_obe_ctrl_120;	//0x01E0
	PE_E60_REG_OBE_CTRL_121_T                        reg_obe_ctrl_121;	//0x01E4
	PE_E60_REG_OBE_CTRL_122_T                        reg_obe_ctrl_122;	//0x01E8
	PE_E60_REG_OBE_CTRL_123_T                        reg_obe_ctrl_123;	//0x01EC
	PE_E60_REG_OBE_CTRL_124_T                        reg_obe_ctrl_124;	//0x01F0
	PE_E60_REG_OBE_CTRL_125_T                        reg_obe_ctrl_125;	//0x01F4
	PE_E60_REG_OBE_CTRL_126_T                        reg_obe_ctrl_126;	//0x01F8
	PE_E60_REG_OBE_CTRL_127_T                        reg_obe_ctrl_127;	//0x01FC
	PE_E60_REG_OBE_CTRL_128_T                        reg_obe_ctrl_128;	//0x0200
	PE_E60_REG_OBE_CTRL_129_T                        reg_obe_ctrl_129;	//0x0204
	PE_E60_REG_OBE_CTRL_130_T                        reg_obe_ctrl_130;	//0x0208
	PE_E60_REG_OBE_CTRL_131_T                        reg_obe_ctrl_131;	//0x020C
}PE_VSD_OBE_REG_E60_T;

#endif
