#ifndef _PE_SHP_REG_O20A0_H_
#define _PE_SHP_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc900d000L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_actv_sel                   :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_top_core_detour                :1 ,	// 4:4
	reg_top_core_bypass                :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_protocol_type              :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ,	// 12:12
	reserved04                         :11,	// reserved
	reg_top_422to444_mode              :1 ,	// 24:24
	reserved05                         :3 ,	// reserved
	reg_top_mode_444                   :1 ,	// 28:28
	reserved06                         :1 ,	// reserved
	reg_obc_debug                      :2 ;	// 31:30
}PE_O20_SHP_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d004L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :16,	// 15:0
	reg_top_height                     :16;	// 31:16
}PE_O20_SHP_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d008L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O20_SHP_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d00cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_pic_init_latency           :12;	// 11:0
}PE_O20_SHP_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d010L shp_core_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_update_ctrl                :5 ;	// 4:0
}PE_O20_SHP_CORE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d040L shp_pat_gen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pat_en                         :1 ,	// 0:0
	reg_pat_thickness                  :2 ,	// 2:1
	reserved01                         :5 ,	// reserved
	reg_pat_pix_val_yy                 :8 ,	// 15:8
	reg_pat_pix_val_cb                 :8 ,	// 23:16
	reg_pat_pix_val_cr                 :8 ;	// 31:24
}PE_O20_SHP_PAT_GEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d050L shp_gos_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hgos_head_crop_ptr         :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_out_hgos_tail_crop_ptr         :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_out_hgos_head_en               :1 ,	// 30:30
	reg_out_hgos_tail_en               :1 ;	// 31:31
}PE_O20_SHP_GOS_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d060L shp_sync_dly_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_vsync                 :16,	// 15:0
	reg_sync_dly_vfp                   :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d064L shp_sync_dly_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_va                    :16,	// 15:0
	reg_sync_dly_vbp                   :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d068L shp_sync_dly_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_hsync                 :16,	// 15:0
	reg_sync_dly_hfp                   :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d06cL shp_sync_dly_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_ha                    :16,	// 15:0
	reg_sync_dly_hbp                   :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d070L shp_sync_dly_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_line_start            :16,	// 15:0
	reg_sync_dly_actv_sel_in_h_src     :1 ,	// 16:16
	reg_sync_dly_actv_sel_in_v_src     :1 ,	// 17:17
	reg_sync_dly_actv_sel_in_h_inv     :1 ,	// 18:18
	reg_sync_dly_actv_sel_in_v_inv     :1 ,	// 19:19
	reg_sync_dly_actv_sel_out_ha       :1 ,	// 20:20
	reg_sync_dly_actv_sel_out_va       :1 ,	// 21:21
	reg_sync_dly_actv_sel_out_hs       :1 ,	// 22:22
	reg_sync_dly_actv_sel_out_vs       :1 ,	// 23:23
	reg_sync_dly_tp_update_hv_zero     :1 ,	// 24:24
	reg_sync_dly_force_out_ha          :1 ,	// 25:25
	reg_sync_dly_force_out_va          :1 ,	// 26:26
	reg_sync_dly_force_out_hs          :1 ,	// 27:27
	reg_sync_dly_cnt_rst_h_value_en    :1 ,	// 28:28
	reg_sync_dly_cnt_rst_v_value_en    :1 ,	// 29:29
	reg_sync_dly_force_out_vs          :1 ,	// 30:30
	reg_sync_dly_force_update          :1 ;	// 31:31
}PE_O20_SHP_SYNC_DLY_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d074L shp_sync_dly_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_sync_h_dly            :16,	// 15:0
	reg_sync_dly_sync_v_dly            :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d078L shp_sync_dly_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_rst_h_value       :16,	// 15:0
	reg_sync_dly_cnt_rst_v_value       :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d07cL shp_sync_dly_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_actv_h_dly       :15,	// 14:0
	reg_sync_dly_auto_actv_gen_en      :1 ,	// 15:15
	reg_sync_dly_auto_actv_v_dly       :15,	// 30:16
	reg_sync_dly_auto_actv_seam_en     :1 ;	// 31:31
}PE_O20_SHP_SYNC_DLY_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d080L shp_sync_dly_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_sync_h_dly       :15,	// 14:0
	reg_sync_dly_auto_sync_gen_en      :1 ,	// 15:15
	reg_sync_dly_auto_sync_v_dly       :15,	// 30:16
	reg_sync_dly_auto_sync_seam_en     :1 ;	// 31:31
}PE_O20_SHP_SYNC_DLY_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d084L shp_sync_dly_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_normal_number         :16;	// 15:0
}PE_O20_SHP_SYNC_DLY_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d088L shp_sync_dly_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_h_rst_position    :16,	// 15:0
	reg_sync_dly_cnt_v_rst_position    :16;	// 31:16
}PE_O20_SHP_SYNC_DLY_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d090L shp_roi_mask_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_roi_mask_en                    :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_roi_mask_pix_val_yy            :8 ,	// 15:8
	reg_roi_mask_pix_val_cb            :8 ,	// 23:16
	reg_roi_mask_pix_val_cr            :8 ;	// 31:24
}PE_O20_SHP_ROI_MASK_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d094L shp_roi_mask_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_roi_mask_win_x0                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_roi_mask_win_y0                :12;	// 27:16
}PE_O20_SHP_ROI_MASK_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d098L shp_roi_mask_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_roi_mask_win_x1                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_roi_mask_win_y1                :12;	// 27:16
}PE_O20_SHP_ROI_MASK_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d0a0L shp_esf_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_detour_mode                :1 ,	// 0:0
	reg_esf_buffer_detour_en           :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_esf_en                         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_esf_dbg_en                     :1 ;	// 8:8
}PE_O20_SHP_ESF_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d0a4L shp_esf_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_min_ratio                  :8 ,	// 7:0
	reg_esf_base                       :8 ,	// 15:8
	reg_esf_max_clip                   :8 ,	// 23:16
	reg_esf_master_gain                :8 ;	// 31:24
}PE_O20_SHP_ESF_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d0a8L shp_esf_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_ltv_offset                 :8 ,	// 7:0
	reg_esf_ltv_mul                    :8 ;	// 15:8
}PE_O20_SHP_ESF_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b0L shp_esf_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win0_en                :1 ,	// 0:0
	reg_win_esf_win1_en                :1 ,	// 1:1
	reg_win_esf_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_esf_win_outside            :1 ,	// 6:6
	reg_win_esf_win_en                 :1 ,	// 7:7
	reg_win_esf_bdr_alpha              :5 ,	// 12:8
	reg_win_esf_bdr_wid                :2 ,	// 14:13
	reg_win_esf_bdr_en                 :1 ,	// 15:15
	reg_win_esf_cr5                    :5 ,	// 20:16
	reg_win_esf_cb5                    :5 ,	// 25:21
	reg_win_esf_yy6                    :6 ;	// 31:26
}PE_O20_SHP_ESF_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b4L shp_esf_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_ESF_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b8L shp_esf_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_ESF_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d0bcL shp_esf_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_ESF_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d0c0L shp_esf_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_ESF_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d0f0L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_O20_SHP_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d100L shp_fd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_map_h_size                :2 ,	// 1:0
	reg_fd_a_nomalize_en               :1 ,	// 2:2
	reg_fd_t_nomalize_en               :1 ,	// 3:3
	reg_fd_t_cut_resolution            :2 ,	// 5:4
	reserved01                         :2 ,	// reserved
	reg_fd_a_map_post_filter_en        :1 ,	// 8:8
	reg_fd_t_cross_check               :1 ,	// 9:9
	reserved02                         :6 ,	// reserved
	reg_fd_pre_a_map_h_size            :3 ,	// 18:16
	reg_fd_pre_a_map_v_size            :2 ,	// 20:19
	reg_fd_pre_a_cut_resolution        :3 ,	// 23:21
	reg_fd_cross_th                    :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d104L shp_fd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mul_base_t                  :8 ,	// 7:0
	reg_fd_mul_base_e                  :8 ;	// 15:8
}PE_O20_SHP_FD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d108L shp_fd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d10cL shp_fd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d110L shp_fd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d114L shp_fd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d118L shp_fd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d11cL shp_fd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d120L shp_fd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y2              :8 ,	// 7:0
	reg_fd_edge_minmax_x2              :8 ,	// 15:8
	reg_fd_edge_minmax_y3              :8 ,	// 23:16
	reg_fd_edge_minmax_x3              :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d124L shp_fd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d128L shp_fd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y2            :8 ,	// 7:0
	reg_fd_detail_minmax_x2            :8 ,	// 15:8
	reg_fd_detail_minmax_y3            :8 ,	// 23:16
	reg_fd_detail_minmax_x3            :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d12cL shp_fd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_O20_SHP_FD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d130L shp_fd_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_fd_mnr_s2_ratio_max            :8 ;	// 23:16
}PE_O20_SHP_FD_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d134L shp_fd_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_x0                 :8 ,	// 7:0
	reg_fd_mnr_gain_x1                 :8 ,	// 15:8
	reg_fd_mnr_gain_y0                 :8 ,	// 23:16
	reg_fd_mnr_gain_y1                 :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d138L shp_fd_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y0                :8 ,	// 7:0
	reg_fd_dct_t_lut_x0                :8 ,	// 15:8
	reg_fd_dct_t_lut_y1                :8 ,	// 23:16
	reg_fd_dct_t_lut_x1                :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d13cL shp_fd_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y2                :8 ,	// 7:0
	reg_fd_dct_t_lut_x2                :8 ,	// 15:8
	reg_fd_dct_t_lut_y3                :8 ,	// 23:16
	reg_fd_dct_t_lut_x3                :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900d140L shp_fd_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_dct_t_lut_y4                :8 ,	// 7:0
	reg_fd_dct_t_lut_x4                :8 ,	// 15:8
	reg_fd_dct_t_lut_y5                :8 ,	// 23:16
	reg_fd_dct_t_lut_x5                :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900d144L shp_fd_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_gain_e_en              :1 ,	// 0:0
	reg_fd_soft_gain_t_en              :1 ;	// 1:1
}PE_O20_SHP_FD_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900d148L shp_fd_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_ratio                  :8 ,	// 7:0
	reg_fd_soft_offset                 :8 ;	// 15:8
}PE_O20_SHP_FD_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900d14cL shp_fd_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_x0               :8 ,	// 7:0
	reg_fd_soft_score_x1               :8 ,	// 15:8
	reg_fd_soft_score_x2               :8 ,	// 23:16
	reg_fd_soft_score_x3               :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900d150L shp_fd_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_soft_score_y0               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_fd_soft_score_y1               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_fd_soft_score_y2               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_fd_soft_score_y3               :6 ;	// 29:24
}PE_O20_SHP_FD_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900d154L shp_fd_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_input_sel              :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	reg_fd_flat_protect_e_en           :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_fd_flat_protect_t_en           :1 ;	// 8:8
}PE_O20_SHP_FD_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900d158L shp_fd_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_flat_lut_y0                 :8 ,	// 7:0
	reg_fd_flat_lut_x0                 :8 ,	// 15:8
	reg_fd_flat_lut_y1                 :8 ,	// 23:16
	reg_fd_flat_lut_x1                 :8 ;	// 31:24
}PE_O20_SHP_FD_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900d160L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ;	// 0:0
}PE_O20_SHP_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d164L shp_mp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_im_gain_h                   :8 ,	// 23:16
	reg_mp_im_gain_v                   :8 ;	// 31:24
}PE_O20_SHP_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d168L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_lap_weight                  :8 ;	// 15:8
}PE_O20_SHP_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d16cL shp_mp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_mp_lap_gain_v_7                :4 ,	// 7:4
	reg_mp_lap_gain_v_5                :4 ,	// 11:8
	reg_mp_lap_gain_v_3                :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	reg_mp_lap_gain_h_7                :4 ,	// 23:20
	reg_mp_lap_gain_h_5                :4 ,	// 27:24
	reg_mp_lap_gain_h_3                :4 ;	// 31:28
}PE_O20_SHP_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d170L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ;	// 11:8
}PE_O20_SHP_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d174L shp_mp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_mp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_mp_gb_x1                       :8 ,	// 15:8
	reg_mp_gb_y1                       :8 ;	// 23:16
}PE_O20_SHP_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d178L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_O20_SHP_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d17cL shp_mp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_O20_SHP_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d180L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_O20_SHP_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d184L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_O20_SHP_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d188L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_O20_SHP_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d18cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_en                   :1 ,	// 0:0
	reg_mp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_mp_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d190L shp_mp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_mp_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d194L shp_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_apl_iir_en                     :1 ,	// 0:0
	reserved01                         :7 ,	// reserved
	reg_apl_iir_gain                   :8 ;	// 15:8
}PE_O20_SHP_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d1a0L shp_lc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_shp_en                      :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_lc_gb_en                       :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lc_center_target               :8 ,	// 15:8
	reg_lc_center_gain                 :8 ,	// 23:16
	reg_lc_local_gain                  :8 ;	// 31:24
}PE_O20_SHP_LC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d1a4L shp_lc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_O20_SHP_LC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d1a8L shp_lc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_O20_SHP_LC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d1acL shp_lc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_lc_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_LC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d1b0L shp_lc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lc_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_lc_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_lc_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_LC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c0L shp_der_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_csft_gain                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_th_gain_edge              :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_derh_th_manual_th              :7 ,	// 30:24
	reg_derh_th_manual_en              :1 ;	// 31:31
}PE_O20_SHP_DER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c4L shp_der_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_bflt_tap_size             :3 ,	// 2:0
	reserved01                         :21,	// reserved
	reg_derh_amean_en                  :1 ,	// 24:24
	reserved02                         :1 ,	// reserved
	reg_derh_edge_filter_v_tap         :2 ,	// 27:26
	reserved03                         :3 ,	// reserved
	reg_derh_edge_y_filter_en          :1 ;	// 31:31
}PE_O20_SHP_DER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c8L shp_der_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ;	// 21:16
}PE_O20_SHP_DER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d1ccL shp_der_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_en                        :1 ,	// 0:0
	reserved01                         :2 ,	// reserved
	reg_derv_bif_en                    :1 ,	// 3:3
	reg_derv_output_mux                :4 ,	// 7:4
	reg_derv_bif_manual_th             :8 ,	// 15:8
	reg_derv_th_gain                   :6 ,	// 21:16
	reserved02                         :2 ,	// reserved
	reg_derv_th_mode                   :1 ;	// 24:24
}PE_O20_SHP_DER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d1d0L shp_der_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_O20_SHP_DER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d1d4L shp_der_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_O20_SHP_DER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d1d8L shp_der_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y0                   :8 ,	// 7:0
	reg_der_a_lut_x0                   :8 ,	// 15:8
	reg_der_a_lut_y1                   :8 ,	// 23:16
	reg_der_a_lut_x1                   :8 ;	// 31:24
}PE_O20_SHP_DER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d1dcL shp_der_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_a_lut_y2                   :8 ,	// 7:0
	reg_der_a_lut_x2                   :8 ,	// 15:8
	reg_der_a_lut_y3                   :8 ,	// 23:16
	reg_der_a_lut_x3                   :8 ;	// 31:24
}PE_O20_SHP_DER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d1e0L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ;	// 0:0
}PE_O20_SHP_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d1e4L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ;	// 23:16
}PE_O20_SHP_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d1e8L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_lap_weight                  :8 ;	// 15:8
}PE_O20_SHP_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d1ecL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_O20_SHP_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d1f0L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ;	// 11:8
}PE_O20_SHP_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d1f4L shp_sp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_sp_gb_mode                     :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_sp_gb_x1                       :8 ,	// 15:8
	reg_sp_gb_y1                       :8 ;	// 23:16
}PE_O20_SHP_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d1f8L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_O20_SHP_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d1fcL shp_sp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_O20_SHP_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d200L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_O20_SHP_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d204L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_O20_SHP_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d208L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_O20_SHP_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d20cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_en                   :1 ,	// 0:0
	reg_sp_coring_mode                 :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_sp_coring_input_sel            :2 ;	// 5:4
}PE_O20_SHP_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d210L shp_sp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_coring_gain_e_b             :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_coring_gain_e_w             :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_coring_gain_t_b             :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_sp_coring_gain_t_w             :7 ;	// 30:24
}PE_O20_SHP_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d220L shp_pti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptiv_enable                    :1 ,	// 0:0
	reg_ptiv_debug_map_en              :1 ,	// 1:1
	reg_ptiv_mm_tap_size               :2 ,	// 3:2
	reg_ptiv_avg_tap_size              :2 ,	// 5:4
	reg_ptiv_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptiv_master_gain               :8 ;	// 15:8
}PE_O20_SHP_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d224L shp_pti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptih_enable                    :1 ,	// 0:0
	reg_ptih_debug_map_en              :1 ,	// 1:1
	reg_ptih_mm_tap_size               :2 ,	// 3:2
	reg_ptih_avg_tap_size              :2 ,	// 5:4
	reg_ptih_ti_mode                   :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_ptih_master_gain               :8 ;	// 15:8
}PE_O20_SHP_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d228L shp_pti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_en                  :1 ,	// 0:0
	reg_pti_coring_mode                :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_pti_coring_input_sel           :2 ;	// 5:4
}PE_O20_SHP_PTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d22cL shp_pti_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pti_coring_gain_e_b            :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_pti_coring_gain_e_w            :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_pti_coring_gain_t_b            :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_pti_coring_gain_t_w            :7 ;	// 30:24
}PE_O20_SHP_PTI_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d230L shp_sti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sti_enable                     :1 ,	// 0:0
	reg_sti_debug_map_en               :1 ,	// 1:1
	reg_sti_mm_tap_size                :2 ,	// 3:2
	reg_sti_avg_tap_size               :2 ,	// 5:4
	reg_sti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_sti_master_gain                :8 ,	// 15:8
	reg_sti_texture_gain               :8 ,	// 23:16
	reg_sti_edge_gain                  :8 ;	// 31:24
}PE_O20_SHP_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d240L shp_tgen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_on_off                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tgen_initial_seed_mode         :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tgen_dbg_en                    :1 ,	// 8:8
	reserved03                         :7 ,	// reserved
	reg_tgen_table_sel                 :4 ,	// 19:16
	reserved04                         :4 ,	// reserved
	reg_tgen_master_gain               :8 ;	// 31:24
}PE_O20_SHP_TGEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d244L shp_tgen_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_delta_h_bound             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_delta_l_bound             :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_delta_max                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_delta_scale               :3 ;	// 26:24
}PE_O20_SHP_TGEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d248L shp_tgen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rnd_th                    :8 ,	// 7:0
	reg_tgen_delta_wcurr               :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_tgen_lc_ldr_th                 :6 ;	// 21:16
}PE_O20_SHP_TGEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d24cL shp_tgen_ctrl_03_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_init_val_c0;	// 31:0
}PE_O20_SHP_TGEN_CTRL_03_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d250L shp_tgen_ctrl_03_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_rand_init_val_c1;	// 31:0
}PE_O20_SHP_TGEN_CTRL_03_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d254L shp_tgen_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_dr_ratio                  :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_tgen_dr_th                     :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_tgen_mm_offset                 :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	reg_tgen_mm_sel_mode               :2 ;	// 25:24
}PE_O20_SHP_TGEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d258L shp_tgen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_tgen_gs_rnd                    :5 ,	// 20:16
	reserved02                         :3 ,	// reserved
	reg_tgen_gs_mm                     :5 ;	// 28:24
}PE_O20_SHP_TGEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d25cL shp_tgen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_x2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_x1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_x0              :6 ;	// 29:24
}PE_O20_SHP_TGEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d260L shp_tgen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_blur_coef_y2              :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_tgen_blur_coef_y1              :6 ,	// 13:8
	reserved02                         :10,	// reserved
	reg_tgen_blur_coef_y0              :6 ;	// 29:24
}PE_O20_SHP_TGEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d264L shp_tgen_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_map_edge_gain             :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_tgen_map_detail_gain           :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_tgen_map_offset                :8 ,	// 23:16
	reg_tgen_gs_noise                  :6 ;	// 29:24
}PE_O20_SHP_TGEN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d268L shp_tgen_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_gain7                     :4 ,	// 3:0
	reg_tgen_gain6                     :4 ,	// 7:4
	reg_tgen_gain5                     :4 ,	// 11:8
	reg_tgen_gain4                     :4 ,	// 15:12
	reg_tgen_gain3                     :4 ,	// 19:16
	reg_tgen_gain2                     :4 ,	// 23:20
	reg_tgen_gain1                     :4 ,	// 27:24
	reg_tgen_gain0                     :4 ;	// 31:28
}PE_O20_SHP_TGEN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d26cL shp_tgen_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_en                 :1 ,	// 0:0
	reg_tgen_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_TGEN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d270L shp_tgen_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgen_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_tgen_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_tgen_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgen_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_TGEN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d274L shp_snr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ,	// 15:8
	reg_snr_blur_mode                  :3 ;	// 18:16
}PE_O20_SHP_SNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d280L shp_dctp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_en                        :1 ;	// 0:0
}PE_O20_SHP_DCTP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d284L shp_dctp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d288L shp_dctp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d28cL shp_dctp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d290L shp_dctp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt0_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt0_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d294L shp_dctp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d298L shp_dctp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d29cL shp_dctp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d2a0L shp_dctp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt1_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt1_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d2a4L shp_dctp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d2a8L shp_dctp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d2acL shp_dctp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d2b0L shp_dctp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt2_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt2_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d2b4L shp_dctp_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d2b8L shp_dctp_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d2bcL shp_dctp_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900d2c0L shp_dctp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt3_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt3_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900d2c4L shp_dctp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900d2c8L shp_dctp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900d2ccL shp_dctp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d0L shp_dctp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt4_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt4_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d4L shp_dctp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_1              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d8L shp_dctp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_2              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_3              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900d2dcL shp_dctp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_4              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_5              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900d2e0L shp_dctp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_filt5_coef_6              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_dctp_filt5_coef_7              :12;	// 27:16
}PE_O20_SHP_DCTP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900d2e4L shp_dctp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x0               :8 ,	// 7:0
	reg_dctp_text_lut_x1               :8 ,	// 15:8
	reg_dctp_text_lut_x2               :8 ,	// 23:16
	reg_dctp_text_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_DCTP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900d2e8L shp_dctp_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_text_lut_x4               :8 ,	// 7:0
	reg_dctp_text_lut_x5               :8 ;	// 15:8
}PE_O20_SHP_DCTP_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc900d2ecL shp_dctp_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y0               :8 ,	// 7:0
	reg_dctp_edge_lut_x0               :8 ,	// 15:8
	reg_dctp_edge_lut_y1               :8 ,	// 23:16
	reg_dctp_edge_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_DCTP_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc900d2f0L shp_dctp_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_edge_lut_y2               :8 ,	// 7:0
	reg_dctp_edge_lut_x2               :8 ,	// 15:8
	reg_dctp_edge_lut_y3               :8 ,	// 23:16
	reg_dctp_edge_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_DCTP_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc900d2f4L shp_dctp_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_gain                      :8 ;	// 7:0
}PE_O20_SHP_DCTP_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc900d2f8L shp_dctp_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_en                 :1 ,	// 0:0
	reg_dctp_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_dtcp_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_DCTP_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc900d2fcL shp_dctp_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dctp_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_dctp_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_dctp_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_dctp_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_DCTP_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc900d300L shp_nntg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_en                        :1 ,	// 0:0
	reserved01                         :3 , // reserved
	reg_nntg_debug_mode                :2 ;	// 5:4
}PE_O20_SHP_NNTG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d304L shp_nntg_ctrl_01_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st_c0;	// 31:0
}PE_O20_SHP_NNTG_CTRL_01_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d308L shp_nntg_ctrl_02_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd_c0;	// 31:0
}PE_O20_SHP_NNTG_CTRL_02_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d30cL shp_nntg_ctrl_03_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd_c0;	// 31:0
}PE_O20_SHP_NNTG_CTRL_03_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d310L shp_nntg_ctrl_04_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th_c0;	// 31:0
}PE_O20_SHP_NNTG_CTRL_04_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d314L shp_nntg_ctrl_05_c0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th_c0;	// 31:0
}PE_O20_SHP_NNTG_CTRL_05_C0_T;
/*-----------------------------------------------------------------------------
                             0xc900d318L shp_nntg_ctrl_01_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_1st_c1;	// 31:0
}PE_O20_SHP_NNTG_CTRL_01_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d31cL shp_nntg_ctrl_02_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_2nd_c1;	// 31:0
}PE_O20_SHP_NNTG_CTRL_02_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d320L shp_nntg_ctrl_03_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_3rd_c1;	// 31:0
}PE_O20_SHP_NNTG_CTRL_03_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d324L shp_nntg_ctrl_04_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_4th_c1;	// 31:0
}PE_O20_SHP_NNTG_CTRL_04_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d328L shp_nntg_ctrl_05_c1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_lsfr_init_5th_c1;	// 31:0
}PE_O20_SHP_NNTG_CTRL_05_C1_T;
/*-----------------------------------------------------------------------------
                             0xc900d32cL shp_nntg_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_ratio                :8 ,	// 7:0
	reg_nntg_rand_max                  :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_nntg_rand_sum_max              :8 ;	// 23:16
}PE_O20_SHP_NNTG_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d330L shp_nntg_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g00             :4 ,	// 3:0
	reg_nntg_rand_coef_g01             :4 ,	// 7:4
	reg_nntg_rand_coef_g02             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_rand_coef_g10             :4 ,	// 19:16
	reg_nntg_rand_coef_g11             :4 ,	// 23:20
	reg_nntg_rand_coef_g12             :4 ;	// 27:24
}PE_O20_SHP_NNTG_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d334L shp_nntg_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_rand_coef_g20             :4 ,	// 3:0
	reg_nntg_rand_coef_g21             :4 ,	// 7:4
	reg_nntg_rand_coef_g22             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g00             :4 ,	// 19:16
	reg_nntg_nano_coef_g01             :4 ,	// 23:20
	reg_nntg_nano_coef_g02             :4 ;	// 27:24
}PE_O20_SHP_NNTG_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d338L shp_nntg_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_nano_coef_g10             :4 ,	// 3:0
	reg_nntg_nano_coef_g11             :4 ,	// 7:4
	reg_nntg_nano_coef_g12             :4 ,	// 11:8
	reserved01                         :4 ,	// reserved
	reg_nntg_nano_coef_g20             :4 ,	// 19:16
	reg_nntg_nano_coef_g21             :4 ,	// 23:20
	reg_nntg_nano_coef_g22             :4 ;	// 27:24
}PE_O20_SHP_NNTG_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d33cL shp_nntg_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y0               :8 ,	// 7:0
	reg_nntg_diff_lut_x0               :8 ,	// 15:8
	reg_nntg_diff_lut_y1               :8 ,	// 23:16
	reg_nntg_diff_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_NNTG_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d340L shp_nntg_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_diff_lut_y2               :8 ,	// 7:0
	reg_nntg_diff_lut_x2               :8 ,	// 15:8
	reg_nntg_diff_lut_y3               :8 ,	// 23:16
	reg_nntg_diff_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_NNTG_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d344L shp_nntg_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y0               :8 ,	// 7:0
	reg_nntg_edge_lut_x0               :8 ,	// 15:8
	reg_nntg_edge_lut_y1               :8 ,	// 23:16
	reg_nntg_edge_lut_x1               :8 ;	// 31:24
}PE_O20_SHP_NNTG_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d348L shp_nntg_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_edge_lut_y2               :8 ,	// 7:0
	reg_nntg_edge_lut_x2               :8 ,	// 15:8
	reg_nntg_edge_lut_y3               :8 ,	// 23:16
	reg_nntg_edge_lut_x3               :8 ;	// 31:24
}PE_O20_SHP_NNTG_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d34cL shp_nntg_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_random_gain               :8 ,	// 7:0
	reg_nntg_pattern_gain              :8 ,	// 15:8
	reg_nntg_local_gain                :8 ,	// 23:16
	reg_nntg_denoise_gain              :8 ;	// 31:24
}PE_O20_SHP_NNTG_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d350L shp_nntg_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_en                 :1 ,	// 0:0
	reg_nntg_coring_mode               :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_input_sel          :2 ;	// 5:4
}PE_O20_SHP_NNTG_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900d354L shp_nntg_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nntg_coring_gain_e_b           :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_nntg_coring_gain_e_w           :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_nntg_coring_gain_t_b           :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_nntg_coring_gain_t_w           :7 ;	// 30:24
}PE_O20_SHP_NNTG_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900d360L shp_dp_sum_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ,	// 7:0
	reg_dp_sum_lut_mode                :2 ;	// 9:8
}PE_O20_SHP_DP_SUM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d364L shp_dp_sum_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y0                  :8 ,	// 7:0
	reg_dp_sum_lut_x0                  :8 ,	// 15:8
	reg_dp_sum_lut_y1                  :8 ,	// 23:16
	reg_dp_sum_lut_x1                  :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d368L shp_dp_sum_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_lut_y2                  :8 ,	// 7:0
	reg_dp_sum_lut_x2                  :8 ,	// 15:8
	reg_dp_sum_lut_y3                  :8 ,	// 23:16
	reg_dp_sum_lut_x3                  :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d36cL shp_dp_sum_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_dct_delta_lut_y0           :8 ,	// 7:0
	reg_obj_dct_delta_lut_x0           :8 ,	// 15:8
	reg_obj_dct_delta_lut_y1           :8 ,	// 23:16
	reg_obj_dct_delta_lut_x1           :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d370L shp_dp_sum_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_dct_delta_lut_y2           :8 ,	// 7:0
	reg_obj_dct_delta_lut_x2           :8 ,	// 15:8
	reg_obj_dct_delta_lut_y3           :8 ,	// 23:16
	reg_obj_dct_delta_lut_x3           :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d374L shp_dp_sum_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_tgen_delta_lut_y0          :8 ,	// 7:0
	reg_obj_tgen_delta_lut_x0          :8 ,	// 15:8
	reg_obj_tgen_delta_lut_y1          :8 ,	// 23:16
	reg_obj_tgen_delta_lut_x1          :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d378L shp_dp_sum_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_tgen_delta_lut_y2          :8 ,	// 7:0
	reg_obj_tgen_delta_lut_x2          :8 ,	// 15:8
	reg_obj_tgen_delta_lut_y3          :8 ,	// 23:16
	reg_obj_tgen_delta_lut_x3          :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d37cL shp_dp_sum_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_lc_delta_lut_y0            :8 ,	// 7:0
	reg_obj_lc_delta_lut_x0            :8 ,	// 15:8
	reg_obj_lc_delta_lut_y1            :8 ,	// 23:16
	reg_obj_lc_delta_lut_x1            :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d380L shp_dp_sum_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_lc_delta_lut_y2            :8 ,	// 7:0
	reg_obj_lc_delta_lut_x2            :8 ,	// 15:8
	reg_obj_lc_delta_lut_y3            :8 ,	// 23:16
	reg_obj_lc_delta_lut_x3            :8 ;	// 31:24
}PE_O20_SHP_DP_SUM_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d390L shp_psp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_obj_en                     :1 ;	// 0:0
}PE_O20_SHP_PSP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a0L shp_dp_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win0_en                 :1 ,	// 0:0
	reg_win_dp_win1_en                 :1 ,	// 1:1
	reg_win_dp_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_win_outside             :1 ,	// 6:6
	reg_win_dp_win_en                  :1 ,	// 7:7
	reg_win_dp_bdr_alpha               :5 ,	// 12:8
	reg_win_dp_bdr_wid                 :2 ,	// 14:13
	reg_win_dp_bdr_en                  :1 ,	// 15:15
	reg_win_dp_cr5                     :5 ,	// 20:16
	reg_win_dp_cb5                     :5 ,	// 25:21
	reg_win_dp_yy6                     :6 ;	// 31:26
}PE_O20_SHP_DP_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a4L shp_dp_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_DP_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a8L shp_dp_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_DP_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d3acL shp_dp_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_DP_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d3b0L shp_dp_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_DP_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d3c0L shp_fd_region_text_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_en                 :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_region_text_cutres             :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_region_text_add_offset         :8 ,	// 15:8
	reg_region_text_add_max            :8 ,	// 23:16
	reg_region_text_cuthif             :3 ;	// 26:24
}PE_O20_SHP_FD_REGION_TEXT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3c4L shp_fd_region_text_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y0             :8 ,	// 7:0
	reg_region_text_lut_x0             :8 ,	// 15:8
	reg_region_text_lut_y1             :8 ,	// 23:16
	reg_region_text_lut_x1             :8 ;	// 31:24
}PE_O20_SHP_FD_REGION_TEXT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3c8L shp_fd_region_text_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_text_lut_y2             :8 ,	// 7:0
	reg_region_text_lut_x2             :8 ,	// 15:8
	reg_region_text_lut_y3             :8 ,	// 23:16
	reg_region_text_lut_x3             :8 ;	// 31:24
}PE_O20_SHP_FD_REGION_TEXT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d3ccL shp_fd_tmap_temp_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_en               :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_tmap_temp_init_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_tmap_temp_init_val             :8 ,	// 15:8
	reserved03                         :8 ,	// reserved
	reg_tmap_stat_sel                  :1 ;	// 24:24
}PE_O20_SHP_FD_TMAP_TEMP_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3d0L shp_fd_tmap_temp_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y0          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x0          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y1          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x1          :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3d4L shp_fd_tmap_temp_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_prev_lut_y2          :8 ,	// 7:0
	reg_tmap_temp_prev_lut_x2          :8 ,	// 15:8
	reg_tmap_temp_prev_lut_y3          :8 ,	// 23:16
	reg_tmap_temp_prev_lut_x3          :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d3d8L shp_fd_tmap_temp_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x1       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d3dcL shp_fd_tmap_temp_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x3       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d3e0L shp_fd_tmap_temp_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_pos_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_pos_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_pos_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_pos_lut_x5       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d3e4L shp_fd_tmap_temp_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y0       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x0       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y1       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x1       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d3e8L shp_fd_tmap_temp_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y2       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x2       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y3       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x3       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d3ecL shp_fd_tmap_temp_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_temp_iir_neg_lut_y4       :8 ,	// 7:0
	reg_tmap_temp_iir_neg_lut_x4       :8 ,	// 15:8
	reg_tmap_temp_iir_neg_lut_y5       :8 ,	// 23:16
	reg_tmap_temp_iir_neg_lut_x5       :8 ;	// 31:24
}PE_O20_SHP_FD_TMAP_TEMP_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f0L shp_fd_tmap_temp_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_start_y         :12;	// 27:16
}PE_O20_SHP_FD_TMAP_TEMP_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f4L shp_fd_tmap_temp_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win0_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win0_end_y           :12;	// 27:16
}PE_O20_SHP_FD_TMAP_TEMP_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f8L shp_fd_tmap_temp_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_start_x         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_start_y         :12;	// 27:16
}PE_O20_SHP_FD_TMAP_TEMP_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d3fcL shp_fd_tmap_temp_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tmap_stat_win1_end_x           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_tmap_stat_win1_end_y           :12;	// 27:16
}PE_O20_SHP_FD_TMAP_TEMP_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d400L shp_dj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_edf_en                      :1 ,	// 0:0
	reg_dj_hv_filter_en                :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_dj_edge_adaptive_en            :1 ,	// 3:3
	reg_dj_line_variation_mode         :1 ,	// 4:4
	reg_dj_l_type_protection           :1 ,	// 5:5
	reg_dj_soft_en                     :1 ,	// 6:6
	reserved02                         :1 ,	// reserved
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_O20_SHP_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d404L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_O20_SHP_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d408L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_O20_SHP_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d40cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_O20_SHP_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d410L shp_dj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_dir_sel_c1                  :1 ,	// 0:0
	reg_dj_dir_sel_c2                  :1 ,	// 1:1
	reg_dj_dir_sel_c3                  :1 ,	// 2:2
	reg_dj_dir_sel_c4                  :1 ;	// 3:3
}PE_O20_SHP_DJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d414L shp_dj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_0_00               :2 ,	// 1:0
	reg_dj_pattern0_0_01               :2 ,	// 3:2
	reg_dj_pattern0_0_02               :2 ,	// 5:4
	reg_dj_pattern0_0_03               :2 ,	// 7:6
	reg_dj_pattern0_0_04               :2 ,	// 9:8
	reg_dj_pattern0_0_05               :2 ,	// 11:10
	reg_dj_pattern0_0_06               :2 ,	// 13:12
	reg_dj_pattern0_0_07               :2 ,	// 15:14
	reg_dj_pattern0_0_08               :2 ,	// 17:16
	reg_dj_pattern0_0_09               :2 ,	// 19:18
	reg_dj_pattern0_0_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d418L shp_dj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_1_00               :2 ,	// 1:0
	reg_dj_pattern0_1_01               :2 ,	// 3:2
	reg_dj_pattern0_1_02               :2 ,	// 5:4
	reg_dj_pattern0_1_03               :2 ,	// 7:6
	reg_dj_pattern0_1_04               :2 ,	// 9:8
	reg_dj_pattern0_1_05               :2 ,	// 11:10
	reg_dj_pattern0_1_06               :2 ,	// 13:12
	reg_dj_pattern0_1_07               :2 ,	// 15:14
	reg_dj_pattern0_1_08               :2 ,	// 17:16
	reg_dj_pattern0_1_09               :2 ,	// 19:18
	reg_dj_pattern0_1_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d41cL shp_dj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_2_00               :2 ,	// 1:0
	reg_dj_pattern0_2_01               :2 ,	// 3:2
	reg_dj_pattern0_2_02               :2 ,	// 5:4
	reg_dj_pattern0_2_03               :2 ,	// 7:6
	reg_dj_pattern0_2_04               :2 ,	// 9:8
	reg_dj_pattern0_2_05               :2 ,	// 11:10
	reg_dj_pattern0_2_06               :2 ,	// 13:12
	reg_dj_pattern0_2_07               :2 ,	// 15:14
	reg_dj_pattern0_2_08               :2 ,	// 17:16
	reg_dj_pattern0_2_09               :2 ,	// 19:18
	reg_dj_pattern0_2_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d420L shp_dj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_3_00               :2 ,	// 1:0
	reg_dj_pattern0_3_01               :2 ,	// 3:2
	reg_dj_pattern0_3_02               :2 ,	// 5:4
	reg_dj_pattern0_3_03               :2 ,	// 7:6
	reg_dj_pattern0_3_04               :2 ,	// 9:8
	reg_dj_pattern0_3_05               :2 ,	// 11:10
	reg_dj_pattern0_3_06               :2 ,	// 13:12
	reg_dj_pattern0_3_07               :2 ,	// 15:14
	reg_dj_pattern0_3_08               :2 ,	// 17:16
	reg_dj_pattern0_3_09               :2 ,	// 19:18
	reg_dj_pattern0_3_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d424L shp_dj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_4_00               :2 ,	// 1:0
	reg_dj_pattern0_4_01               :2 ,	// 3:2
	reg_dj_pattern0_4_02               :2 ,	// 5:4
	reg_dj_pattern0_4_03               :2 ,	// 7:6
	reg_dj_pattern0_4_04               :2 ,	// 9:8
	reg_dj_pattern0_4_05               :2 ,	// 11:10
	reg_dj_pattern0_4_06               :2 ,	// 13:12
	reg_dj_pattern0_4_07               :2 ,	// 15:14
	reg_dj_pattern0_4_08               :2 ,	// 17:16
	reg_dj_pattern0_4_09               :2 ,	// 19:18
	reg_dj_pattern0_4_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d428L shp_dj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_5_00               :2 ,	// 1:0
	reg_dj_pattern0_5_01               :2 ,	// 3:2
	reg_dj_pattern0_5_02               :2 ,	// 5:4
	reg_dj_pattern0_5_03               :2 ,	// 7:6
	reg_dj_pattern0_5_04               :2 ,	// 9:8
	reg_dj_pattern0_5_05               :2 ,	// 11:10
	reg_dj_pattern0_5_06               :2 ,	// 13:12
	reg_dj_pattern0_5_07               :2 ,	// 15:14
	reg_dj_pattern0_5_08               :2 ,	// 17:16
	reg_dj_pattern0_5_09               :2 ,	// 19:18
	reg_dj_pattern0_5_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d42cL shp_dj_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_6_00               :2 ,	// 1:0
	reg_dj_pattern0_6_01               :2 ,	// 3:2
	reg_dj_pattern0_6_02               :2 ,	// 5:4
	reg_dj_pattern0_6_03               :2 ,	// 7:6
	reg_dj_pattern0_6_04               :2 ,	// 9:8
	reg_dj_pattern0_6_05               :2 ,	// 11:10
	reg_dj_pattern0_6_06               :2 ,	// 13:12
	reg_dj_pattern0_6_07               :2 ,	// 15:14
	reg_dj_pattern0_6_08               :2 ,	// 17:16
	reg_dj_pattern0_6_09               :2 ,	// 19:18
	reg_dj_pattern0_6_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d430L shp_dj_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern0_flip0_h            :1 ,	// 0:0
	reg_dj_pattern0_flip0_v            :1 ,	// 1:1
	reg_dj_pattern0_flip1_h            :1 ,	// 2:2
	reg_dj_pattern0_flip1_v            :1 ,	// 3:3
	reg_dj_pattern0_flip2_h            :1 ,	// 4:4
	reg_dj_pattern0_flip2_v            :1 ,	// 5:5
	reg_dj_pattern0_flip3_h            :1 ,	// 6:6
	reg_dj_pattern0_flip3_v            :1 ;	// 7:7
}PE_O20_SHP_DJ_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d434L shp_dj_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_0_00               :2 ,	// 1:0
	reg_dj_pattern1_0_01               :2 ,	// 3:2
	reg_dj_pattern1_0_02               :2 ,	// 5:4
	reg_dj_pattern1_0_03               :2 ,	// 7:6
	reg_dj_pattern1_0_04               :2 ,	// 9:8
	reg_dj_pattern1_0_05               :2 ,	// 11:10
	reg_dj_pattern1_0_06               :2 ,	// 13:12
	reg_dj_pattern1_0_07               :2 ,	// 15:14
	reg_dj_pattern1_0_08               :2 ,	// 17:16
	reg_dj_pattern1_0_09               :2 ,	// 19:18
	reg_dj_pattern1_0_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d438L shp_dj_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_1_00               :2 ,	// 1:0
	reg_dj_pattern1_1_01               :2 ,	// 3:2
	reg_dj_pattern1_1_02               :2 ,	// 5:4
	reg_dj_pattern1_1_03               :2 ,	// 7:6
	reg_dj_pattern1_1_04               :2 ,	// 9:8
	reg_dj_pattern1_1_05               :2 ,	// 11:10
	reg_dj_pattern1_1_06               :2 ,	// 13:12
	reg_dj_pattern1_1_07               :2 ,	// 15:14
	reg_dj_pattern1_1_08               :2 ,	// 17:16
	reg_dj_pattern1_1_09               :2 ,	// 19:18
	reg_dj_pattern1_1_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d43cL shp_dj_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_2_00               :2 ,	// 1:0
	reg_dj_pattern1_2_01               :2 ,	// 3:2
	reg_dj_pattern1_2_02               :2 ,	// 5:4
	reg_dj_pattern1_2_03               :2 ,	// 7:6
	reg_dj_pattern1_2_04               :2 ,	// 9:8
	reg_dj_pattern1_2_05               :2 ,	// 11:10
	reg_dj_pattern1_2_06               :2 ,	// 13:12
	reg_dj_pattern1_2_07               :2 ,	// 15:14
	reg_dj_pattern1_2_08               :2 ,	// 17:16
	reg_dj_pattern1_2_09               :2 ,	// 19:18
	reg_dj_pattern1_2_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc900d440L shp_dj_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_3_00               :2 ,	// 1:0
	reg_dj_pattern1_3_01               :2 ,	// 3:2
	reg_dj_pattern1_3_02               :2 ,	// 5:4
	reg_dj_pattern1_3_03               :2 ,	// 7:6
	reg_dj_pattern1_3_04               :2 ,	// 9:8
	reg_dj_pattern1_3_05               :2 ,	// 11:10
	reg_dj_pattern1_3_06               :2 ,	// 13:12
	reg_dj_pattern1_3_07               :2 ,	// 15:14
	reg_dj_pattern1_3_08               :2 ,	// 17:16
	reg_dj_pattern1_3_09               :2 ,	// 19:18
	reg_dj_pattern1_3_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900d444L shp_dj_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_4_00               :2 ,	// 1:0
	reg_dj_pattern1_4_01               :2 ,	// 3:2
	reg_dj_pattern1_4_02               :2 ,	// 5:4
	reg_dj_pattern1_4_03               :2 ,	// 7:6
	reg_dj_pattern1_4_04               :2 ,	// 9:8
	reg_dj_pattern1_4_05               :2 ,	// 11:10
	reg_dj_pattern1_4_06               :2 ,	// 13:12
	reg_dj_pattern1_4_07               :2 ,	// 15:14
	reg_dj_pattern1_4_08               :2 ,	// 17:16
	reg_dj_pattern1_4_09               :2 ,	// 19:18
	reg_dj_pattern1_4_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900d448L shp_dj_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_5_00               :2 ,	// 1:0
	reg_dj_pattern1_5_01               :2 ,	// 3:2
	reg_dj_pattern1_5_02               :2 ,	// 5:4
	reg_dj_pattern1_5_03               :2 ,	// 7:6
	reg_dj_pattern1_5_04               :2 ,	// 9:8
	reg_dj_pattern1_5_05               :2 ,	// 11:10
	reg_dj_pattern1_5_06               :2 ,	// 13:12
	reg_dj_pattern1_5_07               :2 ,	// 15:14
	reg_dj_pattern1_5_08               :2 ,	// 17:16
	reg_dj_pattern1_5_09               :2 ,	// 19:18
	reg_dj_pattern1_5_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900d44cL shp_dj_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_6_00               :2 ,	// 1:0
	reg_dj_pattern1_6_01               :2 ,	// 3:2
	reg_dj_pattern1_6_02               :2 ,	// 5:4
	reg_dj_pattern1_6_03               :2 ,	// 7:6
	reg_dj_pattern1_6_04               :2 ,	// 9:8
	reg_dj_pattern1_6_05               :2 ,	// 11:10
	reg_dj_pattern1_6_06               :2 ,	// 13:12
	reg_dj_pattern1_6_07               :2 ,	// 15:14
	reg_dj_pattern1_6_08               :2 ,	// 17:16
	reg_dj_pattern1_6_09               :2 ,	// 19:18
	reg_dj_pattern1_6_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900d450L shp_dj_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern1_flip0_h            :1 ,	// 0:0
	reg_dj_pattern1_flip0_v            :1 ,	// 1:1
	reg_dj_pattern1_flip1_h            :1 ,	// 2:2
	reg_dj_pattern1_flip1_v            :1 ;	// 3:3
}PE_O20_SHP_DJ_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900d454L shp_dj_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_0_00               :2 ,	// 1:0
	reg_dj_pattern2_0_01               :2 ,	// 3:2
	reg_dj_pattern2_0_02               :2 ,	// 5:4
	reg_dj_pattern2_0_03               :2 ,	// 7:6
	reg_dj_pattern2_0_04               :2 ,	// 9:8
	reg_dj_pattern2_0_05               :2 ,	// 11:10
	reg_dj_pattern2_0_06               :2 ,	// 13:12
	reg_dj_pattern2_0_07               :2 ,	// 15:14
	reg_dj_pattern2_0_08               :2 ,	// 17:16
	reg_dj_pattern2_0_09               :2 ,	// 19:18
	reg_dj_pattern2_0_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900d458L shp_dj_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_1_00               :2 ,	// 1:0
	reg_dj_pattern2_1_01               :2 ,	// 3:2
	reg_dj_pattern2_1_02               :2 ,	// 5:4
	reg_dj_pattern2_1_03               :2 ,	// 7:6
	reg_dj_pattern2_1_04               :2 ,	// 9:8
	reg_dj_pattern2_1_05               :2 ,	// 11:10
	reg_dj_pattern2_1_06               :2 ,	// 13:12
	reg_dj_pattern2_1_07               :2 ,	// 15:14
	reg_dj_pattern2_1_08               :2 ,	// 17:16
	reg_dj_pattern2_1_09               :2 ,	// 19:18
	reg_dj_pattern2_1_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900d45cL shp_dj_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_2_00               :2 ,	// 1:0
	reg_dj_pattern2_2_01               :2 ,	// 3:2
	reg_dj_pattern2_2_02               :2 ,	// 5:4
	reg_dj_pattern2_2_03               :2 ,	// 7:6
	reg_dj_pattern2_2_04               :2 ,	// 9:8
	reg_dj_pattern2_2_05               :2 ,	// 11:10
	reg_dj_pattern2_2_06               :2 ,	// 13:12
	reg_dj_pattern2_2_07               :2 ,	// 15:14
	reg_dj_pattern2_2_08               :2 ,	// 17:16
	reg_dj_pattern2_2_09               :2 ,	// 19:18
	reg_dj_pattern2_2_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900d460L shp_dj_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_3_00               :2 ,	// 1:0
	reg_dj_pattern2_3_01               :2 ,	// 3:2
	reg_dj_pattern2_3_02               :2 ,	// 5:4
	reg_dj_pattern2_3_03               :2 ,	// 7:6
	reg_dj_pattern2_3_04               :2 ,	// 9:8
	reg_dj_pattern2_3_05               :2 ,	// 11:10
	reg_dj_pattern2_3_06               :2 ,	// 13:12
	reg_dj_pattern2_3_07               :2 ,	// 15:14
	reg_dj_pattern2_3_08               :2 ,	// 17:16
	reg_dj_pattern2_3_09               :2 ,	// 19:18
	reg_dj_pattern2_3_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900d464L shp_dj_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_4_00               :2 ,	// 1:0
	reg_dj_pattern2_4_01               :2 ,	// 3:2
	reg_dj_pattern2_4_02               :2 ,	// 5:4
	reg_dj_pattern2_4_03               :2 ,	// 7:6
	reg_dj_pattern2_4_04               :2 ,	// 9:8
	reg_dj_pattern2_4_05               :2 ,	// 11:10
	reg_dj_pattern2_4_06               :2 ,	// 13:12
	reg_dj_pattern2_4_07               :2 ,	// 15:14
	reg_dj_pattern2_4_08               :2 ,	// 17:16
	reg_dj_pattern2_4_09               :2 ,	// 19:18
	reg_dj_pattern2_4_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900d468L shp_dj_ctrl_1a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_5_00               :2 ,	// 1:0
	reg_dj_pattern2_5_01               :2 ,	// 3:2
	reg_dj_pattern2_5_02               :2 ,	// 5:4
	reg_dj_pattern2_5_03               :2 ,	// 7:6
	reg_dj_pattern2_5_04               :2 ,	// 9:8
	reg_dj_pattern2_5_05               :2 ,	// 11:10
	reg_dj_pattern2_5_06               :2 ,	// 13:12
	reg_dj_pattern2_5_07               :2 ,	// 15:14
	reg_dj_pattern2_5_08               :2 ,	// 17:16
	reg_dj_pattern2_5_09               :2 ,	// 19:18
	reg_dj_pattern2_5_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc900d46cL shp_dj_ctrl_1b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_6_00               :2 ,	// 1:0
	reg_dj_pattern2_6_01               :2 ,	// 3:2
	reg_dj_pattern2_6_02               :2 ,	// 5:4
	reg_dj_pattern2_6_03               :2 ,	// 7:6
	reg_dj_pattern2_6_04               :2 ,	// 9:8
	reg_dj_pattern2_6_05               :2 ,	// 11:10
	reg_dj_pattern2_6_06               :2 ,	// 13:12
	reg_dj_pattern2_6_07               :2 ,	// 15:14
	reg_dj_pattern2_6_08               :2 ,	// 17:16
	reg_dj_pattern2_6_09               :2 ,	// 19:18
	reg_dj_pattern2_6_10               :2 ;	// 21:20
}PE_O20_SHP_DJ_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc900d470L shp_dj_ctrl_1c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_pattern2_flip0_h            :1 ,	// 0:0
	reg_dj_pattern2_flip0_v            :1 ,	// 1:1
	reg_dj_pattern2_flip1_h            :1 ,	// 2:2
	reg_dj_pattern2_flip1_v            :1 ;	// 3:3
}PE_O20_SHP_DJ_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc900d474L shp_dj_ctrl_1d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g0_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g0_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g0_max                 :8 ;	// 23:16
}PE_O20_SHP_DJ_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc900d478L shp_dj_ctrl_1e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g1_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g1_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g1_max                 :8 ;	// 23:16
}PE_O20_SHP_DJ_CTRL_1E_T;
/*-----------------------------------------------------------------------------
                             0xc900d47cL shp_dj_ctrl_1f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_g2_mul                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_dj_soft_g2_offset              :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_dj_soft_g2_max                 :8 ;	// 23:16
}PE_O20_SHP_DJ_CTRL_1F_T;
/*-----------------------------------------------------------------------------
                             0xc900d480L shp_dj_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_soft_base                   :8 ,	// 7:0
	reg_dj_soft_sel_1357_gain          :8 ,	// 15:8
	reg_dj_soft_single_match_en        :1 ;	// 16:16
}PE_O20_SHP_DJ_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc900d490L shp_db_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_O20_SHP_DB_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d494L shp_db_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_O20_SHP_DB_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d4a0L shp_dj_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win0_en                 :1 ,	// 0:0
	reg_win_dj_win1_en                 :1 ,	// 1:1
	reg_win_dj_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_win_outside             :1 ,	// 6:6
	reg_win_dj_win_en                  :1 ,	// 7:7
	reg_win_dj_bdr_alpha               :5 ,	// 12:8
	reg_win_dj_bdr_wid                 :2 ,	// 14:13
	reg_win_dj_bdr_en                  :1 ,	// 15:15
	reg_win_dj_cr5                     :5 ,	// 20:16
	reg_win_dj_cb5                     :5 ,	// 25:21
	reg_win_dj_yy6                     :6 ;	// 31:26
}PE_O20_SHP_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d4a4L shp_dj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d4a8L shp_dj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d4acL shp_dj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d4b0L shp_dj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d500L shp_chroma_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_color_region_en                :1 ,	// 0:0
	reg_color_region_debug_en          :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_chr_protection_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_chr_compensation_en            :1 ;	// 8:8
}PE_O20_SHP_CHROMA_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d504L shp_chroma_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_y_y0               :8 ,	// 7:0
	reg_chr_gain_r0_y_x0               :8 ,	// 15:8
	reg_chr_gain_r0_y_y1               :8 ,	// 23:16
	reg_chr_gain_r0_y_x1               :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d508L shp_chroma_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_y_y2               :8 ,	// 7:0
	reg_chr_gain_r0_y_x2               :8 ,	// 15:8
	reg_chr_gain_r0_y_y3               :8 ,	// 23:16
	reg_chr_gain_r0_y_x3               :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d50cL shp_chroma_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_cb_y0              :8 ,	// 7:0
	reg_chr_gain_r0_cb_x0              :8 ,	// 15:8
	reg_chr_gain_r0_cb_y1              :8 ,	// 23:16
	reg_chr_gain_r0_cb_x1              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d510L shp_chroma_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_cb_y2              :8 ,	// 7:0
	reg_chr_gain_r0_cb_x2              :8 ,	// 15:8
	reg_chr_gain_r0_cb_y3              :8 ,	// 23:16
	reg_chr_gain_r0_cb_x3              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d514L shp_chroma_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_cr_y0              :8 ,	// 7:0
	reg_chr_gain_r0_cr_x0              :8 ,	// 15:8
	reg_chr_gain_r0_cr_y1              :8 ,	// 23:16
	reg_chr_gain_r0_cr_x1              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d518L shp_chroma_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_cr_y2              :8 ,	// 7:0
	reg_chr_gain_r0_cr_x2              :8 ,	// 15:8
	reg_chr_gain_r0_cr_y3              :8 ,	// 23:16
	reg_chr_gain_r0_cr_x3              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d51cL shp_chroma_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_y_y0               :8 ,	// 7:0
	reg_chr_gain_r1_y_x0               :8 ,	// 15:8
	reg_chr_gain_r1_y_y1               :8 ,	// 23:16
	reg_chr_gain_r1_y_x1               :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d520L shp_chroma_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_y_y2               :8 ,	// 7:0
	reg_chr_gain_r1_y_x2               :8 ,	// 15:8
	reg_chr_gain_r1_y_y3               :8 ,	// 23:16
	reg_chr_gain_r1_y_x3               :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d524L shp_chroma_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_cb_y0              :8 ,	// 7:0
	reg_chr_gain_r1_cb_x0              :8 ,	// 15:8
	reg_chr_gain_r1_cb_y1              :8 ,	// 23:16
	reg_chr_gain_r1_cb_x1              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d528L shp_chroma_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_cb_y2              :8 ,	// 7:0
	reg_chr_gain_r1_cb_x2              :8 ,	// 15:8
	reg_chr_gain_r1_cb_y3              :8 ,	// 23:16
	reg_chr_gain_r1_cb_x3              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d52cL shp_chroma_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_cr_y0              :8 ,	// 7:0
	reg_chr_gain_r1_cr_x0              :8 ,	// 15:8
	reg_chr_gain_r1_cr_y1              :8 ,	// 23:16
	reg_chr_gain_r1_cr_x1              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d530L shp_chroma_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r1_cr_y2              :8 ,	// 7:0
	reg_chr_gain_r1_cr_x2              :8 ,	// 15:8
	reg_chr_gain_r1_cr_y3              :8 ,	// 23:16
	reg_chr_gain_r1_cr_x3              :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d534L shp_chroma_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_gain_r0_gain               :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_chr_gain_r1_gain               :8 ,	// 23:16
	reg_chr_gain_sel                   :1 ;	// 24:24
}PE_O20_SHP_CHROMA_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d538L shp_chroma_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_comp_y0                    :8 ,	// 7:0
	reg_chr_comp_x0                    :8 ,	// 15:8
	reg_chr_comp_y1                    :8 ,	// 23:16
	reg_chr_comp_x1                    :8 ;	// 31:24
}PE_O20_SHP_CHROMA_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d550L shp_cti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_en                         :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cti_filter_tap_size            :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_cti_gain                       :8 ;	// 15:8
}PE_O20_SHP_CTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d554L shp_cti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_coring_th0                 :8 ,	// 7:0
	reg_cti_coring_th1                 :8 ,	// 15:8
	reg_cti_coring_map_filter          :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_cti_coring_tap_size            :3 ,	// 22:20
	reserved02                         :1 ,	// reserved
	reg_cti_debug_mode                 :2 ;	// 25:24
}PE_O20_SHP_CTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d558L shp_cti_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_ycm_en                     :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cti_ycm_band_sel               :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_cti_ycm_diff_th                :8 ,	// 15:8
	reg_cti_ycm_y_gain                 :4 ,	// 19:16
	reg_cti_ycm_c_gain                 :4 ;	// 23:20
}PE_O20_SHP_CTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d560L shp_frc_flick_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_flick_en                       :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_flick_motion_sel               :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_flick_blur_type                :2 ;	// 9:8
}PE_O20_SHP_FRC_FLICK_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d564L shp_frc_flick_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_flick_motion_lut_y0            :8 ,	// 7:0
	reg_flick_motion_lut_x0            :8 ,	// 15:8
	reg_flick_motion_lut_y1            :8 ,	// 23:16
	reg_flick_motion_lut_x1            :8 ;	// 31:24
}PE_O20_SHP_FRC_FLICK_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d568L shp_frc_flick_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_flick_motion_lut_y2            :8 ,	// 7:0
	reg_flick_motion_lut_x2            :8 ,	// 15:8
	reg_flick_motion_lut_y3            :8 ,	// 23:16
	reg_flick_motion_lut_x3            :8 ;	// 31:24
}PE_O20_SHP_FRC_FLICK_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d56cL shp_frc_flick_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_flick_master_gain              :8 ;	// 7:0
}PE_O20_SHP_FRC_FLICK_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d570L shp_frc_blur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_en                    :1 ,	// 0:0
	reg_frc_blur_debug_en              :1 ;	// 1:1
}PE_O20_SHP_FRC_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d574L shp_frc_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_cnt_th0               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_blur_cnt_th1               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_blur_cnt_th2               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_blur_cnt_th3               :6 ;	// 29:24
}PE_O20_SHP_FRC_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d578L shp_frc_blur_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_cnt_th4               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_blur_cnt_th5               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_blur_cnt_th6               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_blur_cnt_th7               :6 ;	// 29:24
}PE_O20_SHP_FRC_BLUR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d57cL shp_frc_blur_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_val0                  :4 ,	// 3:0
	reg_frc_blur_val1                  :4 ,	// 7:4
	reg_frc_blur_val2                  :4 ,	// 11:8
	reg_frc_blur_val3                  :4 ,	// 15:12
	reg_frc_blur_val4                  :4 ,	// 19:16
	reg_frc_blur_val5                  :4 ,	// 23:20
	reg_frc_blur_val6                  :4 ,	// 27:24
	reg_frc_blur_val7                  :4 ;	// 31:28
}PE_O20_SHP_FRC_BLUR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d580L shp_frc_blur_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_coef_x8               :4 ;	// 3:0
}PE_O20_SHP_FRC_BLUR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d584L shp_frc_blur_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_coef_x0               :4 ,	// 3:0
	reg_frc_blur_coef_x1               :4 ,	// 7:4
	reg_frc_blur_coef_x2               :4 ,	// 11:8
	reg_frc_blur_coef_x3               :4 ,	// 15:12
	reg_frc_blur_coef_x4               :4 ,	// 19:16
	reg_frc_blur_coef_x5               :4 ,	// 23:20
	reg_frc_blur_coef_x6               :4 ,	// 27:24
	reg_frc_blur_coef_x7               :4 ;	// 31:28
}PE_O20_SHP_FRC_BLUR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d588L shp_frc_blur_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_coef_y0               :4 ,	// 3:0
	reg_frc_blur_coef_y1               :4 ,	// 7:4
	reg_frc_blur_coef_y2               :4 ;	// 11:8
}PE_O20_SHP_FRC_BLUR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d590L shp_frc_halo_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_halo_en                    :1 ,	// 0:0
	reg_frc_halo_debug_en              :1 ;	// 1:1
}PE_O20_SHP_FRC_HALO_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d594L shp_frc_halo_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_halo_cnt_th0               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_halo_cnt_th1               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_halo_cnt_th2               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_halo_cnt_th3               :6 ;	// 29:24
}PE_O20_SHP_FRC_HALO_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d598L shp_frc_halo_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_halo_cnt_th4               :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_halo_cnt_th5               :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_halo_cnt_th6               :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_halo_cnt_th7               :6 ;	// 29:24
}PE_O20_SHP_FRC_HALO_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d59cL shp_frc_halo_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_halo_val0                  :4 ,	// 3:0
	reg_frc_halo_val1                  :4 ,	// 7:4
	reg_frc_halo_val2                  :4 ,	// 11:8
	reg_frc_halo_val3                  :4 ,	// 15:12
	reg_frc_halo_val4                  :4 ,	// 19:16
	reg_frc_halo_val5                  :4 ,	// 23:20
	reg_frc_halo_val6                  :4 ,	// 27:24
	reg_frc_halo_val7                  :4 ;	// 31:28
}PE_O20_SHP_FRC_HALO_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d5a0L shp_frc_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_frc_win0_en                :1 ,	// 0:0
	reg_win_frc_win1_en                :1 ,	// 1:1
	reg_win_frc_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_frc_win_outside            :1 ,	// 6:6
	reg_win_frc_win_en                 :1 ,	// 7:7
	reg_win_frc_bdr_alpha              :5 ,	// 12:8
	reg_win_frc_bdr_wid                :2 ,	// 14:13
	reg_win_frc_bdr_en                 :1 ,	// 15:15
	reg_win_frc_cr5                    :5 ,	// 20:16
	reg_win_frc_cb5                    :5 ,	// 25:21
	reg_win_frc_yy6                    :6 ;	// 31:26
}PE_O20_SHP_FRC_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d5a4L shp_frc_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_frc_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_frc_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_FRC_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d5a8L shp_frc_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_frc_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_frc_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_FRC_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d5acL shp_frc_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_frc_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_frc_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_FRC_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d5b0L shp_frc_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_frc_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_frc_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_FRC_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d600L shp_motion_gain_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_pic_rptr_man       :2 ,	// 1:0
	reserved01                         :1 ,	// reserved
	reg_motion_gain_pic_rptr_man_en    :1 ,	// 3:3
	reg_motion_gain_pic_wptr_man       :2 ,	// 5:4
	reserved02                         :1 ,	// reserved
	reg_motion_gain_pic_wptr_man_en    :1 ,	// 7:7
	reg_motion_gain_pic_data_man       :2 ,	// 9:8
	reg_motion_gain_pic_rptr_on        :1 ,	// 10:10
	reg_motion_gain_pic_wptr_on        :1 ,	// 11:11
	reg_motion_gain_pic_wd_man         :4 ,	// 15:12
	reg_motion_gain_pic_wd_man_on      :1 ,	// 16:16
	reg_motion_gain_pic_rd_lsb_man     :2 ,	// 18:17
	reg_motion_gain_ro_buf_wrcnt       :10,	// 28:19
	reg_motion_gain_ro_buf_wrsel       :1 ;	// 29:29
}PE_O20_SHP_MOTION_GAIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d604L shp_motion_gain_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_in_hoffset         :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_in_voffset         :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d608L shp_motion_gain_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_in_hactive         :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_in_vactive         :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d60cL shp_motion_gain_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_in_hsize           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_in_vsize           :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d610L shp_motion_gain_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_out_pic_width      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_out_pic_height     :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d614L shp_motion_gain_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_phase_off_h        :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_motion_gain_phase_off_v        :6 ,	// 13:8
	reserved02                         :17,	// reserved
	reg_motion_gain_sampling_mode      :1 ;	// 31:31
}PE_O20_SHP_MOTION_GAIN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d618L shp_motion_gain_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_numerator_h        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_numerator_v        :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d61cL shp_motion_gain_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_denominator_h      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_denominator_v      :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d620L shp_motion_gain_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_win0_en            :1 ,	// 0:0
	reg_motion_gain_win1_en            :1 ,	// 1:1
	reg_motion_gain_win01_en           :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_motion_gain_win_outside        :1 ,	// 6:6
	reg_motion_gain_win_en             :1 ,	// 7:7
	reg_motion_gain_bdr_alpha          :5 ,	// 12:8
	reg_motion_gain_bdr_wid            :2 ,	// 14:13
	reg_motion_gain_bdr_en             :1 ,	// 15:15
	reg_motion_gain_cr5                :5 ,	// 20:16
	reg_motion_gain_cb5                :5 ,	// 25:21
	reg_motion_gain_yy6                :6 ;	// 31:26
}PE_O20_SHP_MOTION_GAIN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d624L shp_motion_gain_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_win_w0_x0          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_motion_gain_win_w0_y0          :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d628L shp_motion_gain_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_win_w0_x1          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_motion_gain_win_w0_y1          :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d62cL shp_motion_gain_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_out_hoffset        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_out_voffset        :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d630L shp_motion_gain_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_out_hactive        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_out_vactive        :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d640L shp_motion_prot_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_prot_adaptive_en        :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_motion_prot_debug_en           :1 ;	// 4:4
}PE_O20_SHP_MOTION_PROT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d644L shp_motion_prot_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_prot_lut_a_y0           :8 ,	// 7:0
	reg_motion_prot_lut_a_x0           :8 ,	// 15:8
	reg_motion_prot_lut_a_y1           :8 ,	// 23:16
	reg_motion_prot_lut_a_x1           :8 ;	// 31:24
}PE_O20_SHP_MOTION_PROT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d648L shp_motion_prot_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_prot_lut_a_y2           :8 ,	// 7:0
	reg_motion_prot_lut_a_x2           :8 ,	// 15:8
	reg_motion_prot_lut_a_y3           :8 ,	// 23:16
	reg_motion_prot_lut_a_x3           :8 ;	// 31:24
}PE_O20_SHP_MOTION_PROT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d64cL shp_motion_prot_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_prot_lut_t_y0           :8 ,	// 7:0
	reg_motion_prot_lut_t_x0           :8 ,	// 15:8
	reg_motion_prot_lut_t_y1           :8 ,	// 23:16
	reg_motion_prot_lut_t_x1           :8 ;	// 31:24
}PE_O20_SHP_MOTION_PROT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d650L shp_motion_prot_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_prot_lut_t_y2           :8 ,	// 7:0
	reg_motion_prot_lut_t_x2           :8 ,	// 15:8
	reg_motion_prot_lut_t_y3           :8 ,	// 23:16
	reg_motion_prot_lut_t_x3           :8 ;	// 31:24
}PE_O20_SHP_MOTION_PROT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d670L shp_mot_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mot_win0_en                :1 ,	// 0:0
	reg_win_mot_win1_en                :1 ,	// 1:1
	reg_win_mot_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_mot_win_outside            :1 ,	// 6:6
	reg_win_mot_win_en                 :1 ,	// 7:7
	reg_win_mot_bdr_alpha              :5 ,	// 12:8
	reg_win_mot_bdr_wid                :2 ,	// 14:13
	reg_win_mot_bdr_en                 :1 ,	// 15:15
	reg_win_mot_cr5                    :5 ,	// 20:16
	reg_win_mot_cb5                    :5 ,	// 25:21
	reg_win_mot_yy6                    :6 ;	// 31:26
}PE_O20_SHP_MOT_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d674L shp_mot_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mot_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_mot_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_MOT_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d678L shp_mot_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mot_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_mot_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_MOT_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d67cL shp_mot_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mot_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_mot_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_MOT_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d680L shp_mot_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mot_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_mot_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_MOT_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d690L shp_obj_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_shp_en                     :1 ;	// 0:0
}PE_O20_SHP_OBJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d694L shp_obj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_face_gain_lut_y0           :8 ,	// 7:0
	reg_obj_face_gain_lut_x0           :8 ,	// 15:8
	reg_obj_face_gain_lut_y1           :8 ,	// 23:16
	reg_obj_face_gain_lut_x1           :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d698L shp_obj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_face_gain_lut_y2           :8 ,	// 7:0
	reg_obj_face_gain_lut_x2           :8 ,	// 15:8
	reg_obj_face_gain_lut_y3           :8 ,	// 23:16
	reg_obj_face_gain_lut_x3           :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d69cL shp_obj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_obj_gain_lut_y0            :8 ,	// 7:0
	reg_obj_obj_gain_lut_x0            :8 ,	// 15:8
	reg_obj_obj_gain_lut_y1            :8 ,	// 23:16
	reg_obj_obj_gain_lut_x1            :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a0L shp_obj_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_obj_gain_lut_y2            :8 ,	// 7:0
	reg_obj_obj_gain_lut_x2            :8 ,	// 15:8
	reg_obj_obj_gain_lut_y3            :8 ,	// 23:16
	reg_obj_obj_gain_lut_x3            :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a4L shp_obj_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_final_blend_obj_lut_y0     :8 ,	// 7:0
	reg_obj_final_blend_obj_lut_x0     :8 ,	// 15:8
	reg_obj_final_blend_obj_lut_y1     :8 ,	// 23:16
	reg_obj_final_blend_obj_lut_x1     :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a8L shp_obj_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_final_blend_obj_lut_y2     :8 ,	// 7:0
	reg_obj_final_blend_obj_lut_x2     :8 ,	// 15:8
	reg_obj_final_blend_obj_lut_y3     :8 ,	// 23:16
	reg_obj_final_blend_obj_lut_x3     :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d6acL shp_obj_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_final_blend_face_lut_y0    :8 ,	// 7:0
	reg_obj_final_blend_face_lut_x0    :8 ,	// 15:8
	reg_obj_final_blend_face_lut_y1    :8 ,	// 23:16
	reg_obj_final_blend_face_lut_x1    :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b0L shp_obj_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_final_blend_face_lut_y2    :8 ,	// 7:0
	reg_obj_final_blend_face_lut_x2    :8 ,	// 15:8
	reg_obj_final_blend_face_lut_y3    :8 ,	// 23:16
	reg_obj_final_blend_face_lut_x3    :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b4L shp_obj_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_master_gain_lut_y0         :8 ,	// 7:0
	reg_obj_master_gain_lut_x0         :8 ,	// 15:8
	reg_obj_master_gain_lut_y1         :8 ,	// 23:16
	reg_obj_master_gain_lut_x1         :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b8L shp_obj_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obj_master_gain_lut_y2         :8 ,	// 7:0
	reg_obj_master_gain_lut_x2         :8 ,	// 15:8
	reg_obj_master_gain_lut_y3         :8 ,	// 23:16
	reg_obj_master_gain_lut_x3         :8 ;	// 31:24
}PE_O20_SHP_OBJ_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d7a0L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core_fin_out_vert_cnt      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core_fin_in_vert_cnt       :12;	// 27:16
}PE_O20_SHP_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d7a4L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O20_SHP_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d7a8L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O20_SHP_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d7acL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O20_SHP_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d7b0L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O20_SHP_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d7b4L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O20_SHP_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d7d0L shp_core_fd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CORE_FD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d7d4L shp_core_fd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CORE_FD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d7d8L shp_core_fd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CORE_FD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d7dcL shp_core_fd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_CORE_FD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d7e0L shp_motion_gain_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_buf_rptr                        :2 ,	// 1:0
	ro_buf_wptr_d                      :2 ,	// 3:2
	ro_core_wd_ptr                     :2 ,	// 5:4
	ro_buf_rcnt                        :10,	// 15:6
	ro_buf_wcnt                        :10,	// 25:16
	ro_buf_wre_cnt                     :4 ;	// 29:26
}PE_O20_SHP_MOTION_GAIN_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d7e4L shp_motion_gain_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_out_v_line                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	ro_in_v_line                       :12;	// 27:16
}PE_O20_SHP_MOTION_GAIN_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d800L shp_core_tmap_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window0;	// 31:0
}PE_O20_SHP_CORE_TMAP_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d804L shp_core_tmap_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_window1;	// 31:0
}PE_O20_SHP_CORE_TMAP_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d808L shp_core_tmap_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_0                   :16,	// 15:0
	ro_tmap_status_1                   :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d80cL shp_core_tmap_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_2                   :16,	// 15:0
	ro_tmap_status_3                   :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d810L shp_core_tmap_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_4                   :16,	// 15:0
	ro_tmap_status_5                   :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d814L shp_core_tmap_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_6                   :16,	// 15:0
	ro_tmap_status_7                   :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d818L shp_core_tmap_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_8                   :16,	// 15:0
	ro_tmap_status_9                   :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d81cL shp_core_tmap_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ro_tmap_status_10                  :16,	// 15:0
	ro_tmap_status_11                  :16;	// 31:16
}PE_O20_SHP_CORE_TMAP_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d8f0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	drc_apb_write_cont                 :2 ,	//1:0
	dnr_decont                         :1 ,  //2:2
	drc_write_cont                     :2 ,  //4:3
	reserved                           :3 ,  //7:5
	reg_pre_norm                       :8 ,	//15:8
	reg_cur_norm                       :8 ,	//23:16
	reg_pre_sc    	                   :8 ;	//31:24
}PE_O20_SHP_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d8f4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cur_sc 	                       : 8,  // 7: 0  
	reg_ui_gain_w                      : 8,  // 15:8
	reg_ui_gain_b                      : 8,  // 23:16
	reg_vy_mode 	                   : 8;  // 31:24
}PE_O20_SHP_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d8f8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_obc_debug                      : 2;  // 1:0, 0: shp result   1 : face map   2 : object map
}PE_O20_SHP_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d8fcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_FSW_CTRL_03_T;

 /*-----------------------------------------------------------------------------
                              0xc900b300L psp_ctrl00                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_img_wid                        :12,	// 11:0
 	reserved01                         :4 ,	// reserved
 	reg_img_hei                        :12;	// 27:16
 }PE_O20_VSD_PSP_CTRL00_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b304L psp_ctrl01                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_blk_wid                        :6 ,	// 5:0
 	reserved01                         :2 ,	// reserved
 	reg_blk_hei                        :6 ,	// 13:8
 	reserved02                         :2 ,	// reserved
 	reg_l5_wid                         :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_l5_hei                         :7 ;	// 30:24
 }PE_O20_VSD_PSP_CTRL01_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b308L psp_ctrl02                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_vs_inv                         :1 ,	// 0 
 	reg_psp_en                         :1 ,	// 1 
 	reg_hist_sel                       :2 ,	// 3:2
 	reg_repeat_h_num                   :5 ,	// 8:4
 	reg_cg_disp_clk                    :1 ,	// 9 
 	reg_repeat_v_num                   :5 ,	// 14:10
 	reserved                           :1 ,	// 15
 	reg_margin_hei                     :8 ,	// 23:16
 	reg_margin_wid                     :8 ;	// 31:24
 }PE_O20_VSD_PSP_CTRL02_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b30cL edge_th                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_edge_th                        :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	reg_w_box_th                       :8 ,	// 23:16
 	reg_h_box_th                       :8 ;	// 31:24
 }PE_O20_VSD_EDGE_TH_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b310L fg_position                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_force_w1_pos                   :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_force_h1_pos                   :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_force_w2_pos                   :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_force_h2_pos                   :7 ,	// 30:24
 	reg_force_pos_en                   :1 ;	// 31
 }PE_O20_VSD_FG_POSITION_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b314L perspect_lut_x0                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_x_0;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_X0_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b318L perspect_lut_x1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_x_1;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_X1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b31cL perspect_lut_x2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_x_2;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_X2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b320L perspect_lut_x3                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_x_3;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_X3_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b324L perspect_lut_y0                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_y_0;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_Y0_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b328L perspect_lut_y1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_y_1;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_Y1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b32cL perspect_lut_y2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_y_2;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_Y2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b330L perspect_lut_y3                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_perspect_lut_y_3;	// 31:0
 }PE_O20_VSD_PERSPECT_LUT_Y3_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b334L prob_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_bg_prob_factor                 :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_fg_prob_factor                 :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_stat_flat_w_mul                :4 ,	// 19:16
 	reg_stat_flat_h_mul                :4 ;	// 23:20
 }PE_O20_VSD_PROB_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b338L ellips_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_ellipse_master                 :8 ,	// 7:0
 	reg_e_mul_a                        :9 ,	// 16:8
 	reserved01                         :3 ,	// reserved
 	reg_e_mul_b                        :9 ,	// 28:20
 	reserved02                         :1 ,	// reserved
 	reg_ellipse_disable                :1 ,	// 30
 	reg_fg_mul_ellipse_en              :1 ;	// 31
 }PE_O20_VSD_ELLIPS_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b33cL prob_diff_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_ellipse_offset                 :8 ,	// 7:0
 	reg_bg_diff_mul                    :10,	// 17:8
 	reserved01                         :2 ,	// reserved
 	reg_fg_diff_mul                    :10;	// 29:20
 }PE_O20_VSD_PROB_DIFF_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b340L object_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_p_offset                       :8 ,	// 7:0
 	reg_e_offset                       :8 ,	// 15:8
 	reg_dbg_map_sel                    :3 ;	// 18:16
 }PE_O20_VSD_OBJECT_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b344L blur_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_blur_en                        :1 ;	// 0 
 }PE_O20_VSD_BLUR_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b348L display_debug_map                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_disp_gain_l0                   :1 ,	// 0 
 	reserved01                         :3 ,	// reserved
 	reg_disp_gain_vrtx                 :1 ,	// 4 
 	reserved02                         :3 ,	// reserved
 	reg_bot_bnd_enable                 :1 ,	// 8 
 	reg_left_bnd_disable               :1 ,	// 9 
 	reg_top_bnd_disable                :1 ,	// 10
 	reserved03                         :1 ,	// reserved
 	reg_fifo_detour                    :1 ,	// 12
 	reserved04                         :2 ,	// reserved
 	reg_pic_end_status                 :1 ,	// 15
 	reg_dst_valid_count                :5 ,	// 20:16
 	reserved05                         :3 ,	// reserved
 	valid_expand                       :1 ,	// 24
 	shp_mode_edge                      :1 ,	// 25
 	shp_mode_l0gen                     :1 ;	// 26
 }PE_O20_VSD_DISPLAY_DEBUG_MAP_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b34cL psp_iir                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_psp_iir_alpha                  :6 ,	// 5:0
 	reserved01                         :25,	// reserved
 	reg_psp_gain_init                  :1 ;	// 31
 }PE_O20_VSD_PSP_IIR_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b350L psp_gain                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	psp_gain                           :1 ,	// 0 
 	psp_gain_dbg                       :1 ;	// 1 
 }PE_O20_VSD_PSP_GAIN_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b354L psp_dbg_mon00                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	h1_pos                             :7 ,	// 6:0
 	h2_pos                             :7 ,	// 13:7
 	w1_pos                             :7 ,	// 20:14
 	w2_pos                             :7 ,	// 27:21
 	r_edge_total_lsb                   :4 ;	// 31:28
 }PE_O20_VSD_PSP_DBG_MON00_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b358L psp_dbg_mon01                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	out_max_flat_length_h              :7 ,	// 6:0
 	out_max_flat_length_w              :7 ,	// 13:7
 	r_edge_total_msb                   :18;	// 31:14
 }PE_O20_VSD_PSP_DBG_MON01_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b35cL vrtx_cpc_ctrl                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_vrtx_gain_tl_i                 :8 ,	// 7:0
 	reg_vrtx_gain_tr_i                 :8 ,	// 15:8
 	reg_vrtx_gain_bl_i                 :8 ,	// 23:16
 	reg_vrtx_gain_br_i                 :8 ;	// 31:24
 }PE_O20_VSD_VRTX_CPC_CTRL_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b360L blur_hcoef01                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	hcoef0                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	hcoef1                             :10;	// 25:16
 }PE_O20_VSD_BLUR_HCOEF01_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b364L blur_hcoef23                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	hcoef2                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	hcoef3                             :10;	// 25:16
 }PE_O20_VSD_BLUR_HCOEF23_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b368L blur_hcoef45                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	hcoef4                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	hcoef5                             :10;	// 25:16
 }PE_O20_VSD_BLUR_HCOEF45_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b36cL blur_hcoef67                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	hcoef6                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	hcoef7                             :10;	// 25:16
 }PE_O20_VSD_BLUR_HCOEF67_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b370L blur_hcoef8                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	hcoef8                             :10;	// 9:0
 }PE_O20_VSD_BLUR_HCOEF8_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b374L blur_vcoef01                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	vcoef0                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	vcoef1                             :10;	// 25:16
 }PE_O20_VSD_BLUR_VCOEF01_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b378L blur_vcoef23                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	vcoef2                             :10,	// 9:0
 	reserved01                         :6 ,	// reserved
 	vcoef3                             :10;	// 25:16
 }PE_O20_VSD_BLUR_VCOEF23_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b37cL blur_vcoef4                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	vcoef4                             :10;	// 9:0
 }PE_O20_VSD_BLUR_VCOEF4_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b380L histogram_0                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_0_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b384L histogram_1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b388L histogram_2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b38cL histogram_3                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_3_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b390L histogram_4                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_4_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b394L histogram_5                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_5_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b398L histogram_6                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_6_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b39cL histogram_7                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_7_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3a0L histogram_8                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_8_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3a4L histogram_9                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_9_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3a8L histogram_10                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_10_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3acL histogram_11                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_11_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3b0L histogram_12                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_12_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3b4L histogram_13                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_13_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3b8L histogram_14                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_14_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3bcL histogram_15                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_15_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3c0L histogram_16                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_16_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3c4L histogram_17                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_17_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3c8L histogram_18                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_18_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3ccL histogram_19                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_19_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3d0L histogram_20                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_20_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3d4L histogram_21                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_21_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3d8L histogram_22                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_22_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3dcL histogram_23                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_23_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3e0L histogram_24                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_24_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3e4L histogram_25                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_25_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3e8L histogram_26                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_26_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3ecL histogram_27                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_27_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3f0L histogram_28                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_28_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3f4L histogram_29                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_29_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3f8L histogram_30                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_30_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b3fcL histogram_31                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	data_bg                            :13,	// 12:0
 	reserved01                         :3 ,	// reserved
 	data_fg                            :13;	// 28:16
 }PE_O20_VSD_HISTOGRAM_31_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b400L l5_gain_lut1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	y0_point                           :6 ,	// 5:0
 	reserved01                         :2 ,	// reserved
 	x0_point                           :6 ,	// 13:8
 	reserved02                         :2 ,	// reserved
 	y1_point                           :6 ,	// 21:16
 	reserved03                         :2 ,	// reserved
 	x1_point                           :6 ;	// 29:24
 }PE_O20_VSD_L5_GAIN_LUT1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b404L l5_gain_lut2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	y2_point                           :6 ,	// 5:0
 	reserved01                         :2 ,	// reserved
 	x2_point                           :6 ,	// 13:8
 	reserved02                         :2 ,	// reserved
 	y3_point                           :6 ,	// 21:16
 	reserved03                         :2 ,	// reserved
 	x3_point                           :6 ;	// 29:24
 }PE_O20_VSD_L5_GAIN_LUT2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b408L l0_gain_lut1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	y0_point                           :8 ,	// 7:0
 	x0_point                           :8 ,	// 15:8
 	y1_point                           :8 ,	// 23:16
 	x1_point                           :8 ;	// 31:24
 }PE_O20_VSD_L0_GAIN_LUT1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b40cL l0_gain_lut2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	y2_point                           :8 ,	// 7:0
 	x2_point                           :8 ,	// 15:8
 	y3_point                           :8 ,	// 23:16
 	x3_point                           :8 ;	// 31:24
 }PE_O20_VSD_L0_GAIN_LUT2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b410L edge_win_h                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	h_str                              :12,	// 11:0
 	reserved01                         :4 ,	// reserved
 	h_end                              :12;	// 27:16
 }PE_O20_VSD_EDGE_WIN_H_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b414L edge_win_v                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	v_str                              :12,	// 11:0
 	reserved01                         :4 ,	// reserved
 	v_end                              :12;	// 27:16
 }PE_O20_VSD_EDGE_WIN_V_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b418L edge0_fg                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	edge0_fg                           :23;	// 22:0
 }PE_O20_VSD_EDGE0_FG_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b41cL edge0_bg                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	edge0_bg                           :23;	// 22:0
 }PE_O20_VSD_EDGE0_BG_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b420L edge1_fg                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	edge1_fg                           :23;	// 22:0
 }PE_O20_VSD_EDGE1_FG_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b424L edge1_bg                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	edge1_bg                           :23;	// 22:0
 }PE_O20_VSD_EDGE1_BG_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b428L psp_iir1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	cliping_en                         :1 ,	// 0 
 	reserved01                         :3 ,	// reserved
 	th_lower                           :6 ,	// 9:4
 	reserved02                         :2 ,	// reserved
 	th_upper                           :6 ,	// 17:12
 	reserved03                         :2 ,	// reserved
 	prc_step                           :6 ;	// 25:20
 }PE_O20_VSD_PSP_IIR1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b42cL bg_measure_ctrl                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	bg_measure_en                      :1 ,	// 0 
 	reserved01                         :3 ,	// reserved
 	h_num                              :4 ,	// 7:4
 	v_num                              :4 ,	// 11:8
 	obj_th0                            :6 ,	// 17:12
 	reserved02                         :2 ,	// reserved
 	obj_th1                            :8 ;	// 27:20
 }PE_O20_VSD_BG_MEASURE_CTRL_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b430L bg_measure_read0                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	line_unit0                         :16,	// 15:0
 	line_unit1                         :16;	// 31:16
 }PE_O20_VSD_BG_MEASURE_READ0_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b434L bg_measure_read1                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	line_unit2                         :16,	// 15:0
 	line_unit3                         :16;	// 31:16
 }PE_O20_VSD_BG_MEASURE_READ1_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b438L bg_measure_read2                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	line_unit4                         :16,	// 15:0
 	line_unit5                         :16;	// 31:16
 }PE_O20_VSD_BG_MEASURE_READ2_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b43cL bg_measure_read3                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	line_unit6                         :16,	// 15:0
 	line_unit7                         :16;	// 31:16
 }PE_O20_VSD_BG_MEASURE_READ3_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b440L bg_measure_read4                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	line_unit8                         :16;	// 15:0
 }PE_O20_VSD_BG_MEASURE_READ4_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b444L face0_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_w2_pos                         :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_w1_pos                         :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_h2_pos                         :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_h1_pos                         :7 ,	// 30:24
 	face_en                            :1 ;	// 31
 }PE_O20_VSD_FACE0_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b448L face1_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_w2_pos                         :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_w1_pos                         :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_h2_pos                         :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_h1_pos                         :7 ,	// 30:24
 	face_en                            :1 ;	// 31
 }PE_O20_VSD_FACE1_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b44cL face2_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_w2_pos                         :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_w1_pos                         :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_h2_pos                         :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_h1_pos                         :7 ,	// 30:24
 	face_en                            :1 ;	// 31
 }PE_O20_VSD_FACE2_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b450L face3_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_w2_pos                         :7 ,	// 6:0
 	reserved01                         :1 ,	// reserved
 	reg_w1_pos                         :7 ,	// 14:8
 	reserved02                         :1 ,	// reserved
 	reg_h2_pos                         :7 ,	// 22:16
 	reserved03                         :1 ,	// reserved
 	reg_h1_pos                         :7 ,	// 30:24
 	face_en                            :1 ;	// 31
 }PE_O20_VSD_FACE3_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b454L ellips0_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_e_mul_a                        :9 ,	// 8:0
 	reserved01                         :7 ,	// reserved
 	reg_e_mul_b                        :9 ;	// 24:16
 }PE_O20_VSD_ELLIPS0_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b458L ellips1_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_e_mul_a                        :9 ,	// 8:0
 	reserved01                         :7 ,	// reserved
 	reg_e_mul_b                        :9 ;	// 24:16
 }PE_O20_VSD_ELLIPS1_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b45cL ellips2_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_e_mul_a                        :9 ,	// 8:0
 	reserved01                         :7 ,	// reserved
 	reg_e_mul_b                        :9 ;	// 24:16
 }PE_O20_VSD_ELLIPS2_SET_O_T;
 /*-----------------------------------------------------------------------------
                              0xc900b460L ellips3_set                             
 -----------------------------------------------------------------------------*/
 typedef struct
 {
 	UINT32
 	reg_e_mul_a                        :9 ,	// 8:0
 	reserved01                         :7 ,	// reserved
 	reg_e_mul_b                        :9 ;	// 24:16
 }PE_O20_VSD_ELLIPS3_SET_O_T;

/*-----------------------------------------------------------------------------
                             0xc900b500L psp_ctrl00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_img_wid                        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_img_hei                        :12;	// 27:16
}PE_O20_VSD_PSP_CTRL00_T;
/*-----------------------------------------------------------------------------
                             0xc900b504L psp_ctrl01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blk_wid                        :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_blk_hei                        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_l5_wid                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_l5_hei                         :7 ;	// 30:24
}PE_O20_VSD_PSP_CTRL01_T;
/*-----------------------------------------------------------------------------
                             0xc900b508L psp_ctrl02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vs_inv                         :1 ,	// 0 
	reg_psp_en                         :1 ,	// 1 
	reg_hist_sel                       :2 ,	// 3:2
	reg_repeat_h_num                   :5 ,	// 8:4
	reserved01                         :1 ,	// reserved
	reg_repeat_v_num                   :5 ,	// 14:10
	reserved                           :1 ,	// 15
	reg_margin_hei                     :8 ,	// 23:16
	reg_margin_wid                     :8 ;	// 31:24
}PE_O20_VSD_PSP_CTRL02_T;
/*-----------------------------------------------------------------------------
                             0xc900b50cL edge_th                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_th                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_w_box_th                       :8 ,	// 23:16
	reg_h_box_th                       :8 ;	// 31:24
}PE_O20_VSD_EDGE_TH_T;
/*-----------------------------------------------------------------------------
                             0xc900b510L fg_position                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_w1_pos                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_force_h1_pos                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_force_w2_pos                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_force_h2_pos                   :7 ,	// 30:24
	reg_force_pos_en                   :1 ;	// 31
}PE_O20_VSD_FG_POSITION_T;
/*-----------------------------------------------------------------------------
                             0xc900b514L reg_perspect_gain_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01						   :24 ,	// reserved
	object_relibility				   :8 ; 	// 31:24
}PE_O20_VSD_REG_PERSPECT_GAIN_CTRL_0_T;

/*-----------------------------------------------------------------------------
                             0xc900b518L reg_perspect_lut_x_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved						 :6 ,	// reserved
	object_fg_pel_num				 :16,	//21:6
	object_fg_apl					 :10;	//31:22
}PE_O20_VSD_REG_PERSPECT_LUT_X_0_T;
/*-----------------------------------------------------------------------------
                             0xc900b51cL reg_perspect_lut_x_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved						 :6 ,	// reserved
	object_bg_pel_num				 :16,	//21:6
	object_bg_apl					 :10;	//31:22
}PE_O20_VSD_REG_PERSPECT_LUT_X_1_T;
/*-----------------------------------------------------------------------------
                             0xc900b520L reg_perspect_lut_x_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	object_boxh1					 :8 ,	// 7:0
	object_boxh2					 :8 ,	// 15:8
	object_boxw1					 :8 ,	// 23:16
	object_boxw2					 :8 ;	// 31:24
}PE_O20_VSD_REG_PERSPECT_LUT_X_2_T;
/*-----------------------------------------------------------------------------
                             0xc900b524L reserved4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_VSD_RESERVED4_T;
/*-----------------------------------------------------------------------------
                             0xc900b528L reserved5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_VSD_RESERVED5_T;
/*-----------------------------------------------------------------------------
                             0xc900b52cL reserved6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_VSD_RESERVED6_T;
/*-----------------------------------------------------------------------------
                             0xc900b530L reserved7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_VSD_RESERVED7_T;
/*-----------------------------------------------------------------------------
                             0xc900b534L prob_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bg_prob_factor                 :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_fg_prob_factor                 :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_stat_flat_w_mul                :4 ,	// 19:16
	reg_stat_flat_h_mul                :4 ;	// 23:20
}PE_O20_VSD_PROB_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b538L ellips_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_master                 :8 ,	// 7:0
	reg_e_mul_a                        :9 ,	// 16:8
	reserved01                         :3 ,	// reserved
	reg_e_mul_b                        :9 ,	// 28:20
	reserved02                         :1 ,	// reserved
	reg_ellipse_disable                :1 ,	// 30
	reg_fg_mul_ellipse_en              :1 ;	// 31
}PE_O20_VSD_ELLIPS_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b53cL prob_diff_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_offset                 :8 ,	// 7:0
	reg_bg_diff_mul                    :10,	// 17:8
	reserved01                         :2 ,	// reserved
	reg_fg_diff_mul                    :10;	// 29:20
}PE_O20_VSD_PROB_DIFF_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b540L object_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_p_offset                       :8 ,	// 7:0
	reg_e_offset                       :8 ,	// 15:8
	reg_dbg_map_sel                    :3 ;	// 18:16
}PE_O20_VSD_OBJECT_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b544L blur_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_en                        :1 ;	// 0 
}PE_O20_VSD_BLUR_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b548L display_debug_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_disp_gain_l0                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_disp_gain_vrtx                 :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_bot_bnd_enable                 :1 ,	// 8 
	reg_left_bnd_disable               :1 ,	// 9 
	reg_top_bnd_disable                :1 ,	// 10
	reserved03                         :1 ,	// reserved
	reg_fifo_detour                    :1 ,	// 12
	reserved04                         :2 ,	// reserved
	reg_pic_end_status                 :1 ,	// 15
	reg_dst_valid_count                :5 ,	// 20:16
	reserved05                         :3 ,	// reserved
	valid_expand                       :1 ,	// 24
	shp_mode_edge                      :1 ,	// 25
	shp_mode_l0gen                     :1 ;	// 26
}PE_O20_VSD_DISPLAY_DEBUG_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc900b54cL psp_iir                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_iir_alpha                  :6 ,	// 5:0
	reserved01                         :25,	// reserved
	reg_psp_gain_init                  :1 ;	// 31
}PE_O20_VSD_PSP_IIR_T;
/*-----------------------------------------------------------------------------
                             0xc900b550L psp_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	psp_gain                           :1 ,	// 0 
	psp_gain_dbg                       :1 ;	// 1 
}PE_O20_VSD_PSP_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc900b554L psp_dbg_mon00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h1_pos                             :7 ,	// 6:0
	h2_pos                             :7 ,	// 13:7
	w1_pos                             :7 ,	// 20:14
	w2_pos                             :7 ,	// 27:21
	r_edge_total_lsb                   :4 ;	// 31:28
}PE_O20_VSD_PSP_DBG_MON00_T;
/*-----------------------------------------------------------------------------
                             0xc900b558L psp_dbg_mon01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_max_flat_length_h              :7 ,	// 6:0
	out_max_flat_length_w              :7 ,	// 13:7
	r_edge_total_msb                   :18;	// 31:14
}PE_O20_VSD_PSP_DBG_MON01_T;
/*-----------------------------------------------------------------------------
                             0xc900b55cL vrtx_cpc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vrtx_gain_tl_i                 :8 ,	// 7:0
	reg_vrtx_gain_tr_i                 :8 ,	// 15:8
	reg_vrtx_gain_bl_i                 :8 ,	// 23:16
	reg_vrtx_gain_br_i                 :8 ;	// 31:24
}PE_O20_VSD_VRTX_CPC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900b560L blur_hcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef1                             :10;	// 25:16
}PE_O20_VSD_BLUR_HCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc900b564L blur_hcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef3                             :10;	// 25:16
}PE_O20_VSD_BLUR_HCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc900b568L blur_hcoef45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef4                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef5                             :10;	// 25:16
}PE_O20_VSD_BLUR_HCOEF45_T;
/*-----------------------------------------------------------------------------
                             0xc900b56cL blur_hcoef67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef6                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef7                             :10;	// 25:16
}PE_O20_VSD_BLUR_HCOEF67_T;
/*-----------------------------------------------------------------------------
                             0xc900b570L blur_hcoef8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef8                             :10;	// 9:0
}PE_O20_VSD_BLUR_HCOEF8_T;
/*-----------------------------------------------------------------------------
                             0xc900b574L blur_vcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef1                             :10;	// 25:16
}PE_O20_VSD_BLUR_VCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc900b578L blur_vcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef3                             :10;	// 25:16
}PE_O20_VSD_BLUR_VCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc900b57cL blur_vcoef4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef4                             :10;	// 9:0
}PE_O20_VSD_BLUR_VCOEF4_T;
/*-----------------------------------------------------------------------------
                             0xc900b580L histogram_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_0_T;
/*-----------------------------------------------------------------------------
                             0xc900b584L histogram_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_1_T;
/*-----------------------------------------------------------------------------
                             0xc900b588L histogram_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_2_T;
/*-----------------------------------------------------------------------------
                             0xc900b58cL histogram_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_3_T;
/*-----------------------------------------------------------------------------
                             0xc900b590L histogram_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_4_T;
/*-----------------------------------------------------------------------------
                             0xc900b594L histogram_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_5_T;
/*-----------------------------------------------------------------------------
                             0xc900b598L histogram_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_6_T;
/*-----------------------------------------------------------------------------
                             0xc900b59cL histogram_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_7_T;
/*-----------------------------------------------------------------------------
                             0xc900b5a0L histogram_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_8_T;
/*-----------------------------------------------------------------------------
                             0xc900b5a4L histogram_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_9_T;
/*-----------------------------------------------------------------------------
                             0xc900b5a8L histogram_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_10_T;
/*-----------------------------------------------------------------------------
                             0xc900b5acL histogram_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_11_T;
/*-----------------------------------------------------------------------------
                             0xc900b5b0L histogram_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_12_T;
/*-----------------------------------------------------------------------------
                             0xc900b5b4L histogram_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_13_T;
/*-----------------------------------------------------------------------------
                             0xc900b5b8L histogram_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_14_T;
/*-----------------------------------------------------------------------------
                             0xc900b5bcL histogram_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_15_T;
/*-----------------------------------------------------------------------------
                             0xc900b5c0L histogram_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_16_T;
/*-----------------------------------------------------------------------------
                             0xc900b5c4L histogram_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_17_T;
/*-----------------------------------------------------------------------------
                             0xc900b5c8L histogram_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_18_T;
/*-----------------------------------------------------------------------------
                             0xc900b5ccL histogram_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_19_T;
/*-----------------------------------------------------------------------------
                             0xc900b5d0L histogram_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_20_T;
/*-----------------------------------------------------------------------------
                             0xc900b5d4L histogram_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_21_T;
/*-----------------------------------------------------------------------------
                             0xc900b5d8L histogram_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_22_T;
/*-----------------------------------------------------------------------------
                             0xc900b5dcL histogram_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_23_T;
/*-----------------------------------------------------------------------------
                             0xc900b5e0L histogram_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_24_T;
/*-----------------------------------------------------------------------------
                             0xc900b5e4L histogram_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_25_T;
/*-----------------------------------------------------------------------------
                             0xc900b5e8L histogram_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_26_T;
/*-----------------------------------------------------------------------------
                             0xc900b5ecL histogram_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_27_T;
/*-----------------------------------------------------------------------------
                             0xc900b5f0L histogram_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_28_T;
/*-----------------------------------------------------------------------------
                             0xc900b5f4L histogram_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_29_T;
/*-----------------------------------------------------------------------------
                             0xc900b5f8L histogram_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_30_T;
/*-----------------------------------------------------------------------------
                             0xc900b5fcL histogram_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_VSD_HISTOGRAM_31_T;
/*-----------------------------------------------------------------------------
                             0xc900b600L l5_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	x0_point                           :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	y1_point                           :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	x1_point                           :6 ;	// 29:24
}PE_O20_VSD_L5_GAIN_LUT1_T;
/*-----------------------------------------------------------------------------
                             0xc900b604L l5_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	x2_point                           :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	y3_point                           :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	x3_point                           :6 ;	// 29:24
}PE_O20_VSD_L5_GAIN_LUT2_T;
/*-----------------------------------------------------------------------------
                             0xc900b608L l0_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :8 ,	// 7:0
	x0_point                           :8 ,	// 15:8
	y1_point                           :8 ,	// 23:16
	x1_point                           :8 ;	// 31:24
}PE_O20_VSD_L0_GAIN_LUT1_T;
/*-----------------------------------------------------------------------------
                             0xc900b60cL l0_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :8 ,	// 7:0
	x2_point                           :8 ,	// 15:8
	y3_point                           :8 ,	// 23:16
	x3_point                           :8 ;	// 31:24
}PE_O20_VSD_L0_GAIN_LUT2_T;
/*-----------------------------------------------------------------------------
                             0xc900b610L edge_win_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	h_end                              :12;	// 27:16
}PE_O20_VSD_EDGE_WIN_H_T;
/*-----------------------------------------------------------------------------
                             0xc900b614L edge_win_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	v_end                              :12;	// 27:16
}PE_O20_VSD_EDGE_WIN_V_T;
/*-----------------------------------------------------------------------------
                             0xc900b618L edge0_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_fg                           :23;	// 22:0
}PE_O20_VSD_EDGE0_FG_T;
/*-----------------------------------------------------------------------------
                             0xc900b61cL edge0_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_bg                           :23;	// 22:0
}PE_O20_VSD_EDGE0_BG_T;
/*-----------------------------------------------------------------------------
                             0xc900b620L edge1_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_fg                           :23;	// 22:0
}PE_O20_VSD_EDGE1_FG_T;
/*-----------------------------------------------------------------------------
                             0xc900b624L edge1_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_bg                           :23;	// 22:0
}PE_O20_VSD_EDGE1_BG_T;
/*-----------------------------------------------------------------------------
                             0xc900b628L psp_iir1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cliping_en                         :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	th_lower                           :6 ,	// 9:4
	reserved02                         :2 ,	// reserved
	th_upper                           :6 ,	// 17:12
	reserved03                         :2 ,	// reserved
	prc_step                           :6 ;	// 25:20
}PE_O20_VSD_PSP_IIR1_T;
/*-----------------------------------------------------------------------------
                             0xc900b62cL bg_measure_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_measure_en                      :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	h_num                              :4 ,	// 7:4
	v_num                              :4 ,	// 11:8
	obj_th0                            :6 ,	// 17:12
	reserved02                         :2 ,	// reserved
	obj_th1                            :8 ;	// 27:20
}PE_O20_VSD_BG_MEASURE_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900b630L bg_measure_read0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit0                         :16,	// 15:0
	line_unit1                         :16;	// 31:16
}PE_O20_VSD_BG_MEASURE_READ0_T;
/*-----------------------------------------------------------------------------
                             0xc900b634L bg_measure_read1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit2                         :16,	// 15:0
	line_unit3                         :16;	// 31:16
}PE_O20_VSD_BG_MEASURE_READ1_T;
/*-----------------------------------------------------------------------------
                             0xc900b638L bg_measure_read2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit4                         :16,	// 15:0
	line_unit5                         :16;	// 31:16
}PE_O20_VSD_BG_MEASURE_READ2_T;
/*-----------------------------------------------------------------------------
                             0xc900b63cL bg_measure_read3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit6                         :16,	// 15:0
	line_unit7                         :16;	// 31:16
}PE_O20_VSD_BG_MEASURE_READ3_T;
/*-----------------------------------------------------------------------------
                             0xc900b640L bg_measure_read4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit8                         :16;	// 15:0
}PE_O20_VSD_BG_MEASURE_READ4_T;
/*-----------------------------------------------------------------------------
                             0xc900b644L face0_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face_en                            :1 ;	// 31
}PE_O20_VSD_FACE0_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b648L face1_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face_en                            :1 ;	// 31
}PE_O20_VSD_FACE1_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b64cL face2_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face_en                            :1 ;	// 31
}PE_O20_VSD_FACE2_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b650L face3_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face_en                            :1 ;	// 31
}PE_O20_VSD_FACE3_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b654L ellips0_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_VSD_ELLIPS0_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b658L ellips1_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_VSD_ELLIPS1_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b65cL ellips2_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_VSD_ELLIPS2_SET_T;
/*-----------------------------------------------------------------------------
                             0xc900b660L ellips3_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_VSD_ELLIPS3_SET_T;

/*-----------------------------------------------------------------------------
                             0xc900b200L reg_rce_objt_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_en                         :1 ,	// 0 
	reg_psp_debug_en                   :1 ,	// 1 
	reg_chroma_protection_en           :1 ,	// 2 
	reg_cbst_en                        :1 ,	// 3 
	reg_sat_gain_en                    :1 ,	// 4 
	reg_sat_gain_mode                  :1 ,	// 5 
	reserved01                         :25,	// reserved
	reg_cg_disable                     :1 ;	// 31
}PE_O20_REG_RCE_OBJT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900b204L reg_rce_objt_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_map_master_gain            :8 ;	// 7:0
}PE_O20_REG_RCE_OBJT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900b208L reg_rce_objt_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cb_offset_gain                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_cr_offset_gain                 :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900b20cL reg_rce_objt_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y0                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x0                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900b210L reg_rce_objt_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y1                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x1                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900b214L reg_rce_objt_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y2                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x2                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900b218L reg_rce_objt_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y3                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x3                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900b21cL reg_rce_objt_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y4                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x4                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900b220L reg_rce_objt_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y5                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x5                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900b224L reg_rce_objt_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y6                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x6                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900b228L reg_rce_objt_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y7                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x7                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900b22cL reg_rce_objt_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y0                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x0                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900b230L reg_rce_objt_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y1                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x1                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900b234L reg_rce_objt_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y2                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x2                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900b238L reg_rce_objt_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y3                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x3                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900b23cL reg_rce_objt_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y4                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x4                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900b240L reg_rce_objt_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y5                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x5                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900b244L reg_rce_objt_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y6                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x6                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900b248L reg_rce_objt_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y7                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x7                    :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900b24cL reg_rce_objt_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_gain_lut0_y0               :8 ,	// 7:0
	reg_psp_gain_lut0_x0               :8 ,	// 15:8
	reg_psp_gain_lut0_y1               :8 ,	// 23:16
	reg_psp_gain_lut0_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900b250L reg_rce_objt_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_gain_lut1_y0               :8 ,	// 7:0
	reg_psp_gain_lut1_x0               :8 ,	// 15:8
	reg_psp_gain_lut1_y1               :8 ,	// 23:16
	reg_psp_gain_lut1_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc900b254L reg_rce_objt_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_x1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_yy_lut_pts_x0                  :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc900b258L reg_rce_objt_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_x3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_yy_lut_pts_x2                  :10;	// 25:16
}PE_O20_REG_RCE_OBJT_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc900b25cL reg_rce_objt_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_y3                  :8 ,	// 7:0
	reg_yy_lut_pts_y2                  :8 ,	// 15:8
	reg_yy_lut_pts_y1                  :8 ,	// 23:16
	reg_yy_lut_pts_y0                  :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc900b260L reg_rce_objt_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_lut_pts_y1                  :8 ,	// 7:0
	reg_cc_lut_pts_x1                  :8 ,	// 15:8
	reg_cc_lut_pts_y0                  :8 ,	// 23:16
	reg_cc_lut_pts_x0                  :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc900b264L reg_rce_objt_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_lut_pts_y3                  :8 ,	// 7:0
	reg_cc_lut_pts_x3                  :8 ,	// 15:8
	reg_cc_lut_pts_y2                  :8 ,	// 23:16
	reg_cc_lut_pts_x2                  :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc900b268L reg_rce_objt_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cbst_lut_pts_y1                :8 ,	// 7:0
	reg_cbst_lut_pts_x1                :8 ,	// 15:8
	reg_cbst_lut_pts_y0                :8 ,	// 23:16
	reg_cbst_lut_pts_x0                :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc900b26cL reg_rce_objt_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cbst_lut_pts_y3                :8 ,	// 7:0
	reg_cbst_lut_pts_x3                :8 ,	// 15:8
	reg_cbst_lut_pts_y2                :8 ,	// 23:16
	reg_cbst_lut_pts_x2                :8 ;	// 31:24
}PE_O20_REG_RCE_OBJT_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc900b270L reg_rce_objt_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_y0                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w0_x0                      :12,	// 27:16
	reg_win_enable                     :1 ,	// 28
	reg_win0_enable                    :1 ,	// 29
	reg_win1_enable                    :1 ,	// 30
	reg_win_outside                    :1 ;	// 31
}PE_O20_REG_RCE_OBJT_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc900b274L reg_rce_objt_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_y1                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w0_x1                      :12;	// 27:16
}PE_O20_REG_RCE_OBJT_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc900b278L reg_rce_objt_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_y0                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w1_x0                      :12;	// 27:16
}PE_O20_REG_RCE_OBJT_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc900b27cL reg_rce_objt_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_y1                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w1_x1                      :12;	// 27:16
}PE_O20_REG_RCE_OBJT_CTRL_31_T;

/*-----------------------------------------------------------------------------
                             0xc900b280L reg_rce_face_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_en                         :1 ,	// 0 
	reg_psp_debug_en                   :1 ,	// 1 
	reg_chroma_protection_en           :1 ,	// 2 
	reg_cbst_en                        :1 ,	// 3 
	reg_sat_gain_en                    :1 ,	// 4 
	reg_sat_gain_mode                  :1 ,	// 5 
	reserved01                         :25,	// reserved
	reg_cg_disable                     :1 ;	// 31
}PE_O20_REG_RCE_FACE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900b284L reg_rce_face_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_map_master_gain            :8 ;	// 7:0
}PE_O20_REG_RCE_FACE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900b288L reg_rce_face_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cb_offset_gain                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_cr_offset_gain                 :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900b28cL reg_rce_face_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y0                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x0                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900b290L reg_rce_face_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y1                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x1                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900b294L reg_rce_face_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y2                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x2                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900b298L reg_rce_face_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y3                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x3                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900b29cL reg_rce_face_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y4                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x4                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900b2a0L reg_rce_face_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y5                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x5                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900b2a4L reg_rce_face_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y6                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x6                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900b2a8L reg_rce_face_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut0_y7                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut0_x7                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900b2acL reg_rce_face_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y0                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x0                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900b2b0L reg_rce_face_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y1                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x1                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900b2b4L reg_rce_face_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y2                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x2                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900b2b8L reg_rce_face_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y3                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x3                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900b2bcL reg_rce_face_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y4                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x4                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900b2c0L reg_rce_face_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y5                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x5                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900b2c4L reg_rce_face_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y6                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x6                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900b2c8L reg_rce_face_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut1_y7                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut1_x7                    :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900b2ccL reg_rce_face_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_gain_lut0_y0               :8 ,	// 7:0
	reg_psp_gain_lut0_x0               :8 ,	// 15:8
	reg_psp_gain_lut0_y1               :8 ,	// 23:16
	reg_psp_gain_lut0_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900b2d0L reg_rce_face_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_gain_lut1_y0               :8 ,	// 7:0
	reg_psp_gain_lut1_x0               :8 ,	// 15:8
	reg_psp_gain_lut1_y1               :8 ,	// 23:16
	reg_psp_gain_lut1_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc900b2d4L reg_rce_face_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_x1                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_yy_lut_pts_x0                  :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc900b2d8L reg_rce_face_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_x3                  :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_yy_lut_pts_x2                  :10;	// 25:16
}PE_O20_REG_RCE_FACE_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc900b2dcL reg_rce_face_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lut_pts_y3                  :8 ,	// 7:0
	reg_yy_lut_pts_y2                  :8 ,	// 15:8
	reg_yy_lut_pts_y1                  :8 ,	// 23:16
	reg_yy_lut_pts_y0                  :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc900b2e0L reg_rce_face_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_lut_pts_y1                  :8 ,	// 7:0
	reg_cc_lut_pts_x1                  :8 ,	// 15:8
	reg_cc_lut_pts_y0                  :8 ,	// 23:16
	reg_cc_lut_pts_x0                  :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc900b2e4L reg_rce_face_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_lut_pts_y3                  :8 ,	// 7:0
	reg_cc_lut_pts_x3                  :8 ,	// 15:8
	reg_cc_lut_pts_y2                  :8 ,	// 23:16
	reg_cc_lut_pts_x2                  :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc900b2e8L reg_rce_face_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cbst_lut_pts_y1                :8 ,	// 7:0
	reg_cbst_lut_pts_x1                :8 ,	// 15:8
	reg_cbst_lut_pts_y0                :8 ,	// 23:16
	reg_cbst_lut_pts_x0                :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc900b2ecL reg_rce_face_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cbst_lut_pts_y3                :8 ,	// 7:0
	reg_cbst_lut_pts_x3                :8 ,	// 15:8
	reg_cbst_lut_pts_y2                :8 ,	// 23:16
	reg_cbst_lut_pts_x2                :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc900b2f0L reg_rce_face_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_face_objt_lut_y2               :8 ,	// 7:0
	reg_face_objt_lut_x2               :8 ,	// 15:8
	reg_face_objt_lut_y3               :8 ,	// 23:16
	reg_face_objt_lut_x3               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc900b2f4L reg_rce_face_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_face_objt_lut_y0               :8 ,	// 7:0
	reg_face_objt_lut_x0               :8 ,	// 15:8
	reg_face_objt_lut_y1               :8 ,	// 23:16
	reg_face_objt_lut_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc900b2f8L reg_rce_face_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_objt_face_lut_y2               :8 ,	// 7:0
	reg_objt_face_lut_x2               :8 ,	// 15:8
	reg_objt_face_lut_y3               :8 ,	// 23:16
	reg_objt_face_lut_x3               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc900b2fcL reg_rce_face_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_objt_face_lut_y0               :8 ,	// 7:0
	reg_objt_face_lut_x0               :8 ,	// 15:8
	reg_objt_face_lut_y1               :8 ,	// 23:16
	reg_objt_face_lut_x1               :8 ;	// 31:24
}PE_O20_REG_RCE_FACE_CTRL_31_T;


/*-----------------------------------------------------------------------------
                             0xc900bc00L dtm_top_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	load_time                          :1 ,	// 0 
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_O20_DTM_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900bc04L dtm_top_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	width                              :12,	// 11:0
	reserved01                         :4 , // reserved
	height                             :12;	// 27:16
}PE_O20_DTM_TOP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bc08L dtm_top_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_lsb_detour_en               :1 ,	// 0 
	reg_va_cnt_en                      :1 ,	// 1 
	dtm_disp_detour                    :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	reg_use_own_lut_en                 :1 ,	// 4 
	reserved02                         :19, // reserved
	reg_master_en                      :1 ;	// 24
}PE_O20_DTM_TOP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bc0cL dtm_top_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt                               :12,	// 11:0
	va_pe1_in                          :1 ,	// 12
	va_pe1_out                         :1 ,	// 13
	reserved01                         :2 , // reserved
	vcnt2                              :12;	// 27:16
}PE_O20_DTM_TOP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bc10L dtm_top_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_to_cnt                           :12;	// 11:0
}PE_O20_DTM_TOP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900bc14L dtm_top_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vdpulse_pos;	// 31:0
}PE_O20_DTM_TOP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900bc20L dtm_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dummy_00;	// 31:0
}PE_O20_DTM_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900bc24L dtm_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dummy_01;	// 31:0
}PE_O20_DTM_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bc28L dtm_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dummy_02;	// 31:0
}PE_O20_DTM_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bc2cL dtm_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dummy_03;	// 31:0
}PE_O20_DTM_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bc40L dtm_csc1_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc1st_en                      :1 ;	// 0 
}PE_O20_DTM_CSC1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900bc44L dtm_csc1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef1                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc1st_coef0                     :15;	// 30:16
}PE_O20_DTM_CSC1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bc48L dtm_csc1_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef3                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc1st_coef2                     :15;	// 30:16
}PE_O20_DTM_CSC1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bc4cL dtm_csc1_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef5                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc1st_coef4                     :15;	// 30:16
}PE_O20_DTM_CSC1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bc50L dtm_csc1_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef7                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc1st_coef6                     :15;	// 30:16
}PE_O20_DTM_CSC1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900bc54L dtm_csc1_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16, // reserved
	r_csc1st_coef8                     :15;	// 30:16
}PE_O20_DTM_CSC1_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900bc58L dtm_csc1_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst1                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc1st_ofst0                     :11;	// 26:16
}PE_O20_DTM_CSC1_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900bc5cL dtm_csc1_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst3                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc1st_ofst2                     :11;	// 26:16
}PE_O20_DTM_CSC1_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900bc60L dtm_csc1_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst5                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc1st_ofst4                     :11;	// 26:16
}PE_O20_DTM_CSC1_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900bc70L dtm_llut_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut_enable               :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ,	// 16
	reserved03                         :3 , // reserved
	window_cg_disable                  :1 ;	// 20
}PE_O20_DTM_LLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900bc74L dtm_llut_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :12,	// 11:0
	reserved01                         :4 , // reserved
	win_w0_y0                          :12;	// 27:16
}PE_O20_DTM_LLUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bc78L dtm_llut_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :12,	// 11:0
	reserved01                         :4 , // reserved
	win_w0_y1                          :12;	// 27:16
}PE_O20_DTM_LLUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bc7cL dtm_llut_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :12,	// 11:0
	reserved01                         :4 , // reserved
	win_w1_y0                          :12;	// 27:16
}PE_O20_DTM_LLUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bc80L dtm_llut_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :12,	// 11:0
	reserved01                         :4 , // reserved
	win_w1_y1                          :12;	// 27:16
}PE_O20_DTM_LLUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900bc84L dtm_llut_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut_wdata_y_33rd              :10,	// 9:0
	reserved01                         :6 , // reserved
	hif_llut_wdata_x_33rd              :10;	// 25:16
}PE_O20_DTM_LLUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900bc88L dtm_llut0_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_address                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	hif_llut0_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut0_manual_load              :1 ,	// 11
	hif_llut0_ai                       :1 ,	// 12
	reserved03                         :2 , // reserved
	hif_llut0_enable                   :1 ;	// 15
}PE_O20_DTM_LLUT0_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900bc8cL dtm_llut0_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_wdata_y                  :10,	// 9:0
	reserved01                         :6 , // reserved
	hif_llut0_wdata_x                  :10;	// 25:16
}PE_O20_DTM_LLUT0_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc900bc90L dtm_llut1_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_address                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	hif_llut1_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut1_manual_load              :1 ,	// 11
	hif_llut1_ai                       :1 ,	// 12
	reserved03                         :2 , // reserved
	hif_llut1_enable                   :1 ;	// 15
}PE_O20_DTM_LLUT1_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900bc94L dtm_llut1_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_wdata_y                  :10,	// 9:0
	reserved01                         :6 , // reserved
	hif_llut1_wdata_x                  :10;	// 25:16
}PE_O20_DTM_LLUT1_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc900bc98L dtm_llut2_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut2_address                  :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_llut2_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut2_manual_load              :1 ,	// 11
	hif_llut2_ai                       :1 ,	// 12
	reserved03                         :2 , // reserved
	hif_llut2_enable                   :1 ;	// 15
}PE_O20_DTM_LLUT2_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900bc9cL dtm_llut2_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut2_wdata_y                  :10,	// 9:0
	reserved01                         :6 , // reserved
	hif_llut2_wdata_x                  :10;	// 25:16
}PE_O20_DTM_LLUT2_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc900bcb0L dtm_csc3_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc2nd_en                      :1 ;	// 0 
}PE_O20_DTM_CSC3_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900bcb4L dtm_csc3_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_coef1                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc2nd_coef0                     :15;	// 30:16
}PE_O20_DTM_CSC3_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bcb8L dtm_csc3_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_coef3                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc2nd_coef2                     :15;	// 30:16
}PE_O20_DTM_CSC3_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bcbcL dtm_csc3_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_coef5                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc2nd_coef4                     :15;	// 30:16
}PE_O20_DTM_CSC3_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bcc0L dtm_csc3_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_coef7                     :15,	// 14:0
	reserved01                         :1 , // reserved
	r_csc2nd_coef6                     :15;	// 30:16
}PE_O20_DTM_CSC3_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900bcc4L dtm_csc3_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16, // reserved
	r_csc2nd_coef8                     :15;	// 30:16
}PE_O20_DTM_CSC3_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900bcc8L dtm_csc3_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_ofst1                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc2nd_ofst0                     :11;	// 26:16
}PE_O20_DTM_CSC3_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900bcccL dtm_csc3_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_ofst3                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc2nd_ofst2                     :11;	// 26:16
}PE_O20_DTM_CSC3_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900bcd0L dtm_csc3_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc2nd_ofst5                     :11,	// 10:0
	reserved01                         :5 , // reserved
	r_csc2nd_ofst4                     :11;	// 26:16
}PE_O20_DTM_CSC3_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900bce0L dtm_hue_sat_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hue_prsv_en                    :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_sat_prsv_en                    :1 ,	// 4 
	reg_hue_prsv_detour                :1 ,	// 5 
	reserved02                         :6 ,	// reserved
	reg_hue_prsv_cg_disable            :1 ,	// 12
	reserved03                         :3 ,	// reserved
	reg_sat_prsv_ratio                 :8 ,	// 23:16
	reg_hue_prsv_ratio                 :8 ;	// 31:24
}PE_O20_DTM_HUE_SAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900bcf0L dtm_odd_llut_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_win_w0_x0                      :12,	// 11:0
	reserved01                         :4 , // reserved
	odd_win_w0_y0                      :12;	// 27:16
}PE_O20_DTM_ODD_LLUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900bcf4L dtm_odd_llut_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_win_w0_x1                      :12,	// 11:0
	reserved01                         :4 , // reserved
	odd_win_w0_y1                      :12;	// 27:16
}PE_O20_DTM_ODD_LLUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900bcf8L dtm_odd_llut_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_win_w1_x0                      :12,	// 11:0
	reserved01                         :4 , // reserved
	odd_win_w1_y0                      :12;	// 27:16
}PE_O20_DTM_ODD_LLUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900bcfcL dtm_odd_llut_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_win_w1_x1                      :12,	// 11:0
	reserved01                         :4 , // reserved
	odd_win_w1_y1                      :12;	// 27:16
}PE_O20_DTM_ODD_LLUT_CTRL_04_T;


typedef struct
{ 
	PE_O20_SHP_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O20_SHP_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O20_SHP_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	PE_O20_SHP_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0x000C
	PE_O20_SHP_CORE_CTRL_04_T                         shp_core_ctrl_04;	//0x0010
	UINT32                                            reserved5[11];	//0x14-0x3c
	PE_O20_SHP_PAT_GEN_CTRL_00_T                      shp_pat_gen_ctrl_00;	//0x0040
	UINT32                                            reserved6[3];	//0x44-0x4c
	PE_O20_SHP_GOS_CTRL_00_T                          shp_gos_ctrl_00;	//0x0050
	UINT32                                            reserved7[3];	//0x54-0x5c
	PE_O20_SHP_SYNC_DLY_CTRL_00_T                     shp_sync_dly_ctrl_00;	//0x0060
	PE_O20_SHP_SYNC_DLY_CTRL_01_T                     shp_sync_dly_ctrl_01;	//0x0064
	PE_O20_SHP_SYNC_DLY_CTRL_02_T                     shp_sync_dly_ctrl_02;	//0x0068
	PE_O20_SHP_SYNC_DLY_CTRL_03_T                     shp_sync_dly_ctrl_03;	//0x006C
	PE_O20_SHP_SYNC_DLY_CTRL_04_T                     shp_sync_dly_ctrl_04;	//0x0070
	PE_O20_SHP_SYNC_DLY_CTRL_05_T                     shp_sync_dly_ctrl_05;	//0x0074
	PE_O20_SHP_SYNC_DLY_CTRL_06_T                     shp_sync_dly_ctrl_06;	//0x0078
	PE_O20_SHP_SYNC_DLY_CTRL_07_T                     shp_sync_dly_ctrl_07;	//0x007C
	PE_O20_SHP_SYNC_DLY_CTRL_08_T                     shp_sync_dly_ctrl_08;	//0x0080
	PE_O20_SHP_SYNC_DLY_CTRL_09_T                     shp_sync_dly_ctrl_09;	//0x0084
	PE_O20_SHP_SYNC_DLY_CTRL_0A_T                     shp_sync_dly_ctrl_0a;	//0x0088
	UINT32                                            reserved18;	//0x8c
	PE_O20_SHP_ROI_MASK_CTRL_00_T                     shp_roi_mask_ctrl_00;	//0x0090
	PE_O20_SHP_ROI_MASK_CTRL_01_T                     shp_roi_mask_ctrl_01;	//0x0094
	PE_O20_SHP_ROI_MASK_CTRL_02_T                     shp_roi_mask_ctrl_02;	//0x0098
	UINT32                                            reserved21;	//0x9c
	PE_O20_SHP_ESF_CTRL_00_T                          shp_esf_ctrl_00;	//0x00A0
	PE_O20_SHP_ESF_CTRL_01_T                          shp_esf_ctrl_01;	//0x00A4
	PE_O20_SHP_ESF_CTRL_02_T                          shp_esf_ctrl_02;	//0x00A8
	UINT32                                            reserved24;	//0xac
	PE_O20_SHP_ESF_WIN_CTRL_00_T                      shp_esf_win_ctrl_00;	//0x00B0
	PE_O20_SHP_ESF_WIN_CTRL_01_T                      shp_esf_win_ctrl_01;	//0x00B4
	PE_O20_SHP_ESF_WIN_CTRL_02_T                      shp_esf_win_ctrl_02;	//0x00B8
	PE_O20_SHP_ESF_WIN_CTRL_03_T                      shp_esf_win_ctrl_03;	//0x00BC
	PE_O20_SHP_ESF_WIN_CTRL_04_T                      shp_esf_win_ctrl_04;	//0x00C0
	UINT32                                            reserved29[11];	//0xc4-0xec
	PE_O20_SHP_DP_CTRL_00_T                           shp_dp_ctrl_00;	//0x00F0
	UINT32                                            reserved30[3];	//0xf4-0xfc
	PE_O20_SHP_FD_CTRL_00_T                           shp_fd_ctrl_00;	//0x0100
	PE_O20_SHP_FD_CTRL_01_T                           shp_fd_ctrl_01;	//0x0104
	PE_O20_SHP_FD_CTRL_02_T                           shp_fd_ctrl_02;	//0x0108
	PE_O20_SHP_FD_CTRL_03_T                           shp_fd_ctrl_03;	//0x010C
	PE_O20_SHP_FD_CTRL_04_T                           shp_fd_ctrl_04;	//0x0110
	PE_O20_SHP_FD_CTRL_05_T                           shp_fd_ctrl_05;	//0x0114
	PE_O20_SHP_FD_CTRL_06_T                           shp_fd_ctrl_06;	//0x0118
	PE_O20_SHP_FD_CTRL_07_T                           shp_fd_ctrl_07;	//0x011C
	PE_O20_SHP_FD_CTRL_08_T                           shp_fd_ctrl_08;	//0x0120
	PE_O20_SHP_FD_CTRL_09_T                           shp_fd_ctrl_09;	//0x0124
	PE_O20_SHP_FD_CTRL_0A_T                           shp_fd_ctrl_0a;	//0x0128
	PE_O20_SHP_FD_CTRL_0B_T                           shp_fd_ctrl_0b;	//0x012C
	PE_O20_SHP_FD_CTRL_0C_T                           shp_fd_ctrl_0c;	//0x0130
	PE_O20_SHP_FD_CTRL_0D_T                           shp_fd_ctrl_0d;	//0x0134
	PE_O20_SHP_FD_CTRL_0E_T                           shp_fd_ctrl_0e;	//0x0138
	PE_O20_SHP_FD_CTRL_0F_T                           shp_fd_ctrl_0f;	//0x013C
	PE_O20_SHP_FD_CTRL_10_T                           shp_fd_ctrl_10;	//0x0140
	PE_O20_SHP_FD_CTRL_11_T                           shp_fd_ctrl_11;	//0x0144
	PE_O20_SHP_FD_CTRL_12_T                           shp_fd_ctrl_12;	//0x0148
	PE_O20_SHP_FD_CTRL_13_T                           shp_fd_ctrl_13;	//0x014C
	PE_O20_SHP_FD_CTRL_14_T                           shp_fd_ctrl_14;	//0x0150
	PE_O20_SHP_FD_CTRL_15_T                           shp_fd_ctrl_15;	//0x0154
	PE_O20_SHP_FD_CTRL_16_T                           shp_fd_ctrl_16;	//0x0158
	UINT32                                            reserved53;	//0x15c
	PE_O20_SHP_MP_CTRL_00_T                           shp_mp_ctrl_00;	//0x0160
	PE_O20_SHP_MP_CTRL_01_T                           shp_mp_ctrl_01;	//0x0164
	PE_O20_SHP_MP_CTRL_02_T                           shp_mp_ctrl_02;	//0x0168
	PE_O20_SHP_MP_CTRL_03_T                           shp_mp_ctrl_03;	//0x016C
	PE_O20_SHP_MP_CTRL_04_T                           shp_mp_ctrl_04;	//0x0170
	PE_O20_SHP_MP_CTRL_05_T                           shp_mp_ctrl_05;	//0x0174
	PE_O20_SHP_MP_CTRL_06_T                           shp_mp_ctrl_06;	//0x0178
	PE_O20_SHP_MP_CTRL_07_T                           shp_mp_ctrl_07;	//0x017C
	PE_O20_SHP_MP_CTRL_08_T                           shp_mp_ctrl_08;	//0x0180
	PE_O20_SHP_MP_CTRL_09_T                           shp_mp_ctrl_09;	//0x0184
	PE_O20_SHP_MP_CTRL_0A_T                           shp_mp_ctrl_0a;	//0x0188
	PE_O20_SHP_MP_CTRL_0B_T                           shp_mp_ctrl_0b;	//0x018C
	PE_O20_SHP_MP_CTRL_0C_T                           shp_mp_ctrl_0c;	//0x0190
	PE_O20_SHP_APL_CTRL_00_T                          shp_apl_ctrl_00;	//0x0194
	UINT32                                            reserved67[2];	//0x198-0x19c
	PE_O20_SHP_LC_CTRL_00_T                           shp_lc_ctrl_00;	//0x01A0
	PE_O20_SHP_LC_CTRL_01_T                           shp_lc_ctrl_01;	//0x01A4
	PE_O20_SHP_LC_CTRL_02_T                           shp_lc_ctrl_02;	//0x01A8
	PE_O20_SHP_LC_CTRL_03_T                           shp_lc_ctrl_03;	//0x01AC
	PE_O20_SHP_LC_CTRL_04_T                           shp_lc_ctrl_04;	//0x01B0
	UINT32                                            reserved72[3];	//0x1b4-0x1bc
	PE_O20_SHP_DER_CTRL_00_T                          shp_der_ctrl_00;	//0x01C0
	PE_O20_SHP_DER_CTRL_01_T                          shp_der_ctrl_01;	//0x01C4
	PE_O20_SHP_DER_CTRL_02_T                          shp_der_ctrl_02;	//0x01C8
	PE_O20_SHP_DER_CTRL_03_T                          shp_der_ctrl_03;	//0x01CC
	PE_O20_SHP_DER_CTRL_04_T                          shp_der_ctrl_04;	//0x01D0
	PE_O20_SHP_DER_CTRL_05_T                          shp_der_ctrl_05;	//0x01D4
	PE_O20_SHP_DER_CTRL_06_T                          shp_der_ctrl_06;	//0x01D8
	PE_O20_SHP_DER_CTRL_07_T                          shp_der_ctrl_07;	//0x01DC
	PE_O20_SHP_SP_CTRL_00_T                           shp_sp_ctrl_00;	//0x01E0
	PE_O20_SHP_SP_CTRL_01_T                           shp_sp_ctrl_01;	//0x01E4
	PE_O20_SHP_SP_CTRL_02_T                           shp_sp_ctrl_02;	//0x01E8
	PE_O20_SHP_SP_CTRL_03_T                           shp_sp_ctrl_03;	//0x01EC
	PE_O20_SHP_SP_CTRL_04_T                           shp_sp_ctrl_04;	//0x01F0
	PE_O20_SHP_SP_CTRL_05_T                           shp_sp_ctrl_05;	//0x01F4
	PE_O20_SHP_SP_CTRL_06_T                           shp_sp_ctrl_06;	//0x01F8
	PE_O20_SHP_SP_CTRL_07_T                           shp_sp_ctrl_07;	//0x01FC
	PE_O20_SHP_SP_CTRL_08_T                           shp_sp_ctrl_08;	//0x0200
	PE_O20_SHP_SP_CTRL_09_T                           shp_sp_ctrl_09;	//0x0204
	PE_O20_SHP_SP_CTRL_0A_T                           shp_sp_ctrl_0a;	//0x0208
	PE_O20_SHP_SP_CTRL_0B_T                           shp_sp_ctrl_0b;	//0x020C
	PE_O20_SHP_SP_CTRL_0C_T                           shp_sp_ctrl_0c;	//0x0210
	UINT32                                            reserved93[3];	//0x214-0x21c
	PE_O20_SHP_PTI_CTRL_00_T                          shp_pti_ctrl_00;	//0x0220
	PE_O20_SHP_PTI_CTRL_01_T                          shp_pti_ctrl_01;	//0x0224
	PE_O20_SHP_PTI_CTRL_02_T                          shp_pti_ctrl_02;	//0x0228
	PE_O20_SHP_PTI_CTRL_03_T                          shp_pti_ctrl_03;	//0x022C
	PE_O20_SHP_STI_CTRL_00_T                          shp_sti_ctrl_00;	//0x0230
	UINT32                                            reserved98[3];	//0x234-0x23c
	PE_O20_SHP_TGEN_CTRL_00_T                         shp_tgen_ctrl_00;	//0x0240
	PE_O20_SHP_TGEN_CTRL_01_T                         shp_tgen_ctrl_01;	//0x0244
	PE_O20_SHP_TGEN_CTRL_02_T                         shp_tgen_ctrl_02;	//0x0248
	PE_O20_SHP_TGEN_CTRL_03_C0_T                      shp_tgen_ctrl_03_c0;	//0x024C
	PE_O20_SHP_TGEN_CTRL_03_C1_T                      shp_tgen_ctrl_03_c1;	//0x0250
	PE_O20_SHP_TGEN_CTRL_04_T                         shp_tgen_ctrl_04;	//0x0254
	PE_O20_SHP_TGEN_CTRL_05_T                         shp_tgen_ctrl_05;	//0x0258
	PE_O20_SHP_TGEN_CTRL_06_T                         shp_tgen_ctrl_06;	//0x025C
	PE_O20_SHP_TGEN_CTRL_07_T                         shp_tgen_ctrl_07;	//0x0260
	PE_O20_SHP_TGEN_CTRL_08_T                         shp_tgen_ctrl_08;	//0x0264
	PE_O20_SHP_TGEN_CTRL_09_T                         shp_tgen_ctrl_09;	//0x0268
	PE_O20_SHP_TGEN_CTRL_0A_T                         shp_tgen_ctrl_0a;	//0x026C
	PE_O20_SHP_TGEN_CTRL_0B_T                         shp_tgen_ctrl_0b;	//0x0270
	PE_O20_SHP_SNR_CTRL_00_T                          shp_snr_ctrl_00;	//0x0274
	UINT32                                            reserved112[2];	//0x278-0x27c
	PE_O20_SHP_DCTP_CTRL_00_T                         shp_dctp_ctrl_00;	//0x0280
	PE_O20_SHP_DCTP_CTRL_01_T                         shp_dctp_ctrl_01;	//0x0284
	PE_O20_SHP_DCTP_CTRL_02_T                         shp_dctp_ctrl_02;	//0x0288
	PE_O20_SHP_DCTP_CTRL_03_T                         shp_dctp_ctrl_03;	//0x028C
	PE_O20_SHP_DCTP_CTRL_04_T                         shp_dctp_ctrl_04;	//0x0290
	PE_O20_SHP_DCTP_CTRL_05_T                         shp_dctp_ctrl_05;	//0x0294
	PE_O20_SHP_DCTP_CTRL_06_T                         shp_dctp_ctrl_06;	//0x0298
	PE_O20_SHP_DCTP_CTRL_07_T                         shp_dctp_ctrl_07;	//0x029C
	PE_O20_SHP_DCTP_CTRL_08_T                         shp_dctp_ctrl_08;	//0x02A0
	PE_O20_SHP_DCTP_CTRL_09_T                         shp_dctp_ctrl_09;	//0x02A4
	PE_O20_SHP_DCTP_CTRL_0A_T                         shp_dctp_ctrl_0a;	//0x02A8
	PE_O20_SHP_DCTP_CTRL_0B_T                         shp_dctp_ctrl_0b;	//0x02AC
	PE_O20_SHP_DCTP_CTRL_0C_T                         shp_dctp_ctrl_0c;	//0x02B0
	PE_O20_SHP_DCTP_CTRL_0D_T                         shp_dctp_ctrl_0d;	//0x02B4
	PE_O20_SHP_DCTP_CTRL_0E_T                         shp_dctp_ctrl_0e;	//0x02B8
	PE_O20_SHP_DCTP_CTRL_0F_T                         shp_dctp_ctrl_0f;	//0x02BC
	PE_O20_SHP_DCTP_CTRL_10_T                         shp_dctp_ctrl_10;	//0x02C0
	PE_O20_SHP_DCTP_CTRL_11_T                         shp_dctp_ctrl_11;	//0x02C4
	PE_O20_SHP_DCTP_CTRL_12_T                         shp_dctp_ctrl_12;	//0x02C8
	PE_O20_SHP_DCTP_CTRL_13_T                         shp_dctp_ctrl_13;	//0x02CC
	PE_O20_SHP_DCTP_CTRL_14_T                         shp_dctp_ctrl_14;	//0x02D0
	PE_O20_SHP_DCTP_CTRL_15_T                         shp_dctp_ctrl_15;	//0x02D4
	PE_O20_SHP_DCTP_CTRL_16_T                         shp_dctp_ctrl_16;	//0x02D8
	PE_O20_SHP_DCTP_CTRL_17_T                         shp_dctp_ctrl_17;	//0x02DC
	PE_O20_SHP_DCTP_CTRL_18_T                         shp_dctp_ctrl_18;	//0x02E0
	PE_O20_SHP_DCTP_CTRL_19_T                         shp_dctp_ctrl_19;	//0x02E4
	PE_O20_SHP_DCTP_CTRL_1A_T                         shp_dctp_ctrl_1a;	//0x02E8
	PE_O20_SHP_DCTP_CTRL_1B_T                         shp_dctp_ctrl_1b;	//0x02EC
	PE_O20_SHP_DCTP_CTRL_1C_T                         shp_dctp_ctrl_1c;	//0x02F0
	PE_O20_SHP_DCTP_CTRL_1D_T                         shp_dctp_ctrl_1d;	//0x02F4
	PE_O20_SHP_DCTP_CTRL_1E_T                         shp_dctp_ctrl_1e;	//0x02F8
	PE_O20_SHP_DCTP_CTRL_1F_T                         shp_dctp_ctrl_1f;	//0x02FC
	PE_O20_SHP_NNTG_CTRL_00_T                         shp_nntg_ctrl_00;	//0x0300
	PE_O20_SHP_NNTG_CTRL_01_C0_T                      shp_nntg_ctrl_01_c0;	//0x0304
	PE_O20_SHP_NNTG_CTRL_02_C0_T                      shp_nntg_ctrl_02_c0;	//0x0308
	PE_O20_SHP_NNTG_CTRL_03_C0_T                      shp_nntg_ctrl_03_c0;	//0x030C
	PE_O20_SHP_NNTG_CTRL_04_C0_T                      shp_nntg_ctrl_04_c0;	//0x0310
	PE_O20_SHP_NNTG_CTRL_05_C0_T                      shp_nntg_ctrl_05_c0;	//0x0314
	PE_O20_SHP_NNTG_CTRL_01_C1_T                      shp_nntg_ctrl_01_c1;	//0x0318
	PE_O20_SHP_NNTG_CTRL_02_C1_T                      shp_nntg_ctrl_02_c1;	//0x031C
	PE_O20_SHP_NNTG_CTRL_03_C1_T                      shp_nntg_ctrl_03_c1;	//0x0320
	PE_O20_SHP_NNTG_CTRL_04_C1_T                      shp_nntg_ctrl_04_c1;	//0x0324
	PE_O20_SHP_NNTG_CTRL_05_C1_T                      shp_nntg_ctrl_05_c1;	//0x0328
	PE_O20_SHP_NNTG_CTRL_06_T                         shp_nntg_ctrl_06;	//0x032C
	PE_O20_SHP_NNTG_CTRL_07_T                         shp_nntg_ctrl_07;	//0x0330
	PE_O20_SHP_NNTG_CTRL_08_T                         shp_nntg_ctrl_08;	//0x0334
	PE_O20_SHP_NNTG_CTRL_09_T                         shp_nntg_ctrl_09;	//0x0338
	PE_O20_SHP_NNTG_CTRL_0A_T                         shp_nntg_ctrl_0a;	//0x033C
	PE_O20_SHP_NNTG_CTRL_0B_T                         shp_nntg_ctrl_0b;	//0x0340
	PE_O20_SHP_NNTG_CTRL_0C_T                         shp_nntg_ctrl_0c;	//0x0344
	PE_O20_SHP_NNTG_CTRL_0D_T                         shp_nntg_ctrl_0d;	//0x0348
	PE_O20_SHP_NNTG_CTRL_0E_T                         shp_nntg_ctrl_0e;	//0x034C
	PE_O20_SHP_NNTG_CTRL_0F_T                         shp_nntg_ctrl_0f;	//0x0350
	PE_O20_SHP_NNTG_CTRL_10_T                         shp_nntg_ctrl_10;	//0x0354
	UINT32                                            reserved166[2];	//0x358-0x35c
	PE_O20_SHP_DP_SUM_CTRL_00_T                       shp_dp_sum_ctrl_00;	//0x0360
	PE_O20_SHP_DP_SUM_CTRL_01_T                       shp_dp_sum_ctrl_01;	//0x0364
	PE_O20_SHP_DP_SUM_CTRL_02_T                       shp_dp_sum_ctrl_02;	//0x0368
	PE_O20_SHP_DP_SUM_CTRL_03_T                       shp_dp_sum_ctrl_03;	//0x036C
	PE_O20_SHP_DP_SUM_CTRL_04_T                       shp_dp_sum_ctrl_04;	//0x0370
	PE_O20_SHP_DP_SUM_CTRL_05_T                       shp_dp_sum_ctrl_05;	//0x0374
	PE_O20_SHP_DP_SUM_CTRL_06_T                       shp_dp_sum_ctrl_06;	//0x0378
	PE_O20_SHP_DP_SUM_CTRL_07_T                       shp_dp_sum_ctrl_07;	//0x037C
	PE_O20_SHP_DP_SUM_CTRL_08_T                       shp_dp_sum_ctrl_08;	//0x0380
	UINT32                                            reserved175[3];	//0x384-0x38c
	PE_O20_SHP_PSP_CTRL_00_T                          shp_psp_ctrl_00;	//0x0390
	UINT32                                            reserved176[3];	//0x394-0x39c
	PE_O20_SHP_DP_WIN_CTRL_00_T                       shp_dp_win_ctrl_00;	//0x03A0
	PE_O20_SHP_DP_WIN_CTRL_01_T                       shp_dp_win_ctrl_01;	//0x03A4
	PE_O20_SHP_DP_WIN_CTRL_02_T                       shp_dp_win_ctrl_02;	//0x03A8
	PE_O20_SHP_DP_WIN_CTRL_03_T                       shp_dp_win_ctrl_03;	//0x03AC
	PE_O20_SHP_DP_WIN_CTRL_04_T                       shp_dp_win_ctrl_04;	//0x03B0
	UINT32                                            reserved181[3];	//0x3b4-0x3bc
	PE_O20_SHP_FD_REGION_TEXT_00_T                    shp_fd_region_text_00;	//0x03C0
	PE_O20_SHP_FD_REGION_TEXT_01_T                    shp_fd_region_text_01;	//0x03C4
	PE_O20_SHP_FD_REGION_TEXT_02_T                    shp_fd_region_text_02;	//0x03C8
	PE_O20_SHP_FD_TMAP_TEMP_00_T                      shp_fd_tmap_temp_00;	//0x03CC
	PE_O20_SHP_FD_TMAP_TEMP_01_T                      shp_fd_tmap_temp_01;	//0x03D0
	PE_O20_SHP_FD_TMAP_TEMP_02_T                      shp_fd_tmap_temp_02;	//0x03D4
	PE_O20_SHP_FD_TMAP_TEMP_03_T                      shp_fd_tmap_temp_03;	//0x03D8
	PE_O20_SHP_FD_TMAP_TEMP_04_T                      shp_fd_tmap_temp_04;	//0x03DC
	PE_O20_SHP_FD_TMAP_TEMP_05_T                      shp_fd_tmap_temp_05;	//0x03E0
	PE_O20_SHP_FD_TMAP_TEMP_06_T                      shp_fd_tmap_temp_06;	//0x03E4
	PE_O20_SHP_FD_TMAP_TEMP_07_T                      shp_fd_tmap_temp_07;	//0x03E8
	PE_O20_SHP_FD_TMAP_TEMP_08_T                      shp_fd_tmap_temp_08;	//0x03EC
	PE_O20_SHP_FD_TMAP_TEMP_09_T                      shp_fd_tmap_temp_09;	//0x03F0
	PE_O20_SHP_FD_TMAP_TEMP_0A_T                      shp_fd_tmap_temp_0a;	//0x03F4
	PE_O20_SHP_FD_TMAP_TEMP_0B_T                      shp_fd_tmap_temp_0b;	//0x03F8
	PE_O20_SHP_FD_TMAP_TEMP_0C_T                      shp_fd_tmap_temp_0c;	//0x03FC
	PE_O20_SHP_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0400
	PE_O20_SHP_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0404
	PE_O20_SHP_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0408
	PE_O20_SHP_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x040C
	PE_O20_SHP_DJ_CTRL_04_T                           shp_dj_ctrl_04;	//0x0410
	PE_O20_SHP_DJ_CTRL_05_T                           shp_dj_ctrl_05;	//0x0414
	PE_O20_SHP_DJ_CTRL_06_T                           shp_dj_ctrl_06;	//0x0418
	PE_O20_SHP_DJ_CTRL_07_T                           shp_dj_ctrl_07;	//0x041C
	PE_O20_SHP_DJ_CTRL_08_T                           shp_dj_ctrl_08;	//0x0420
	PE_O20_SHP_DJ_CTRL_09_T                           shp_dj_ctrl_09;	//0x0424
	PE_O20_SHP_DJ_CTRL_0A_T                           shp_dj_ctrl_0a;	//0x0428
	PE_O20_SHP_DJ_CTRL_0B_T                           shp_dj_ctrl_0b;	//0x042C
	PE_O20_SHP_DJ_CTRL_0C_T                           shp_dj_ctrl_0c;	//0x0430
	PE_O20_SHP_DJ_CTRL_0D_T                           shp_dj_ctrl_0d;	//0x0434
	PE_O20_SHP_DJ_CTRL_0E_T                           shp_dj_ctrl_0e;	//0x0438
	PE_O20_SHP_DJ_CTRL_0F_T                           shp_dj_ctrl_0f;	//0x043C
	PE_O20_SHP_DJ_CTRL_10_T                           shp_dj_ctrl_10;	//0x0440
	PE_O20_SHP_DJ_CTRL_11_T                           shp_dj_ctrl_11;	//0x0444
	PE_O20_SHP_DJ_CTRL_12_T                           shp_dj_ctrl_12;	//0x0448
	PE_O20_SHP_DJ_CTRL_13_T                           shp_dj_ctrl_13;	//0x044C
	PE_O20_SHP_DJ_CTRL_14_T                           shp_dj_ctrl_14;	//0x0450
	PE_O20_SHP_DJ_CTRL_15_T                           shp_dj_ctrl_15;	//0x0454
	PE_O20_SHP_DJ_CTRL_16_T                           shp_dj_ctrl_16;	//0x0458
	PE_O20_SHP_DJ_CTRL_17_T                           shp_dj_ctrl_17;	//0x045C
	PE_O20_SHP_DJ_CTRL_18_T                           shp_dj_ctrl_18;	//0x0460
	PE_O20_SHP_DJ_CTRL_19_T                           shp_dj_ctrl_19;	//0x0464
	PE_O20_SHP_DJ_CTRL_1A_T                           shp_dj_ctrl_1a;	//0x0468
	PE_O20_SHP_DJ_CTRL_1B_T                           shp_dj_ctrl_1b;	//0x046C
	PE_O20_SHP_DJ_CTRL_1C_T                           shp_dj_ctrl_1c;	//0x0470
	PE_O20_SHP_DJ_CTRL_1D_T                           shp_dj_ctrl_1d;	//0x0474
	PE_O20_SHP_DJ_CTRL_1E_T                           shp_dj_ctrl_1e;	//0x0478
	PE_O20_SHP_DJ_CTRL_1F_T                           shp_dj_ctrl_1f;	//0x047C
	PE_O20_SHP_DJ_CTRL_20_T                           shp_dj_ctrl_20;	//0x0480
	UINT32                                            reserved230[3];	//0x484-0x48c
	PE_O20_SHP_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0490
	PE_O20_SHP_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0494
	UINT32                                            reserved232[2];	//0x498-0x49c
	PE_O20_SHP_DJ_WIN_CTRL_00_T                       shp_dj_win_ctrl_00;	//0x04A0
	PE_O20_SHP_DJ_WIN_CTRL_01_T                       shp_dj_win_ctrl_01;	//0x04A4
	PE_O20_SHP_DJ_WIN_CTRL_02_T                       shp_dj_win_ctrl_02;	//0x04A8
	PE_O20_SHP_DJ_WIN_CTRL_03_T                       shp_dj_win_ctrl_03;	//0x04AC
	PE_O20_SHP_DJ_WIN_CTRL_04_T                       shp_dj_win_ctrl_04;	//0x04B0
	UINT32                                            reserved237[19];	//0x4b4-0x4fc
	PE_O20_SHP_CHROMA_CTRL_00_T                       shp_chroma_ctrl_00;	//0x0500
	PE_O20_SHP_CHROMA_CTRL_01_T                       shp_chroma_ctrl_01;	//0x0504
	PE_O20_SHP_CHROMA_CTRL_02_T                       shp_chroma_ctrl_02;	//0x0508
	PE_O20_SHP_CHROMA_CTRL_03_T                       shp_chroma_ctrl_03;	//0x050C
	PE_O20_SHP_CHROMA_CTRL_04_T                       shp_chroma_ctrl_04;	//0x0510
	PE_O20_SHP_CHROMA_CTRL_05_T                       shp_chroma_ctrl_05;	//0x0514
	PE_O20_SHP_CHROMA_CTRL_06_T                       shp_chroma_ctrl_06;	//0x0518
	PE_O20_SHP_CHROMA_CTRL_07_T                       shp_chroma_ctrl_07;	//0x051C
	PE_O20_SHP_CHROMA_CTRL_08_T                       shp_chroma_ctrl_08;	//0x0520
	PE_O20_SHP_CHROMA_CTRL_09_T                       shp_chroma_ctrl_09;	//0x0524
	PE_O20_SHP_CHROMA_CTRL_0A_T                       shp_chroma_ctrl_0a;	//0x0528
	PE_O20_SHP_CHROMA_CTRL_0B_T                       shp_chroma_ctrl_0b;	//0x052C
	PE_O20_SHP_CHROMA_CTRL_0C_T                       shp_chroma_ctrl_0c;	//0x0530
	PE_O20_SHP_CHROMA_CTRL_0D_T                       shp_chroma_ctrl_0d;	//0x0534
	PE_O20_SHP_CHROMA_CTRL_0E_T                       shp_chroma_ctrl_0e;	//0x0538
	UINT32                                            reserved252[5];	//0x53c-0x54c
	PE_O20_SHP_CTI_CTRL_00_T                          shp_cti_ctrl_00;	//0x0550
	PE_O20_SHP_CTI_CTRL_01_T                          shp_cti_ctrl_01;	//0x0554
	PE_O20_SHP_CTI_CTRL_02_T                          shp_cti_ctrl_02;	//0x0558
	UINT32                                            reserved255;	//0x55c
	PE_O20_SHP_FRC_FLICK_CTRL_00_T                    shp_frc_flick_ctrl_00;	//0x0560
	PE_O20_SHP_FRC_FLICK_CTRL_01_T                    shp_frc_flick_ctrl_01;	//0x0564
	PE_O20_SHP_FRC_FLICK_CTRL_02_T                    shp_frc_flick_ctrl_02;	//0x0568
	PE_O20_SHP_FRC_FLICK_CTRL_03_T                    shp_frc_flick_ctrl_03;	//0x056C
	PE_O20_SHP_FRC_BLUR_CTRL_00_T                     shp_frc_blur_ctrl_00;	//0x0570
	PE_O20_SHP_FRC_BLUR_CTRL_01_T                     shp_frc_blur_ctrl_01;	//0x0574
	PE_O20_SHP_FRC_BLUR_CTRL_02_T                     shp_frc_blur_ctrl_02;	//0x0578
	PE_O20_SHP_FRC_BLUR_CTRL_03_T                     shp_frc_blur_ctrl_03;	//0x057C
	PE_O20_SHP_FRC_BLUR_CTRL_04_T                     shp_frc_blur_ctrl_04;	//0x0580
	PE_O20_SHP_FRC_BLUR_CTRL_05_T                     shp_frc_blur_ctrl_05;	//0x0584
	PE_O20_SHP_FRC_BLUR_CTRL_06_T                     shp_frc_blur_ctrl_06;	//0x0588
	UINT32                                            reserved266;	//0x58c
	PE_O20_SHP_FRC_HALO_CTRL_00_T                     shp_frc_halo_ctrl_00;	//0x0590
	PE_O20_SHP_FRC_HALO_CTRL_01_T                     shp_frc_halo_ctrl_01;	//0x0594
	PE_O20_SHP_FRC_HALO_CTRL_02_T                     shp_frc_halo_ctrl_02;	//0x0598
	PE_O20_SHP_FRC_HALO_CTRL_03_T                     shp_frc_halo_ctrl_03;	//0x059C
	PE_O20_SHP_FRC_WIN_CTRL_00_T                      shp_frc_win_ctrl_00;	//0x05A0
	PE_O20_SHP_FRC_WIN_CTRL_01_T                      shp_frc_win_ctrl_01;	//0x05A4
	PE_O20_SHP_FRC_WIN_CTRL_02_T                      shp_frc_win_ctrl_02;	//0x05A8
	PE_O20_SHP_FRC_WIN_CTRL_03_T                      shp_frc_win_ctrl_03;	//0x05AC
	PE_O20_SHP_FRC_WIN_CTRL_04_T                      shp_frc_win_ctrl_04;	//0x05B0
	UINT32                                            reserved275[19];	//0x5b4-0x5fc
	PE_O20_SHP_MOTION_GAIN_CTRL_00_T                  shp_motion_gain_ctrl_00;	//0x0600
	PE_O20_SHP_MOTION_GAIN_CTRL_01_T                  shp_motion_gain_ctrl_01;	//0x0604
	PE_O20_SHP_MOTION_GAIN_CTRL_02_T                  shp_motion_gain_ctrl_02;	//0x0608
	PE_O20_SHP_MOTION_GAIN_CTRL_03_T                  shp_motion_gain_ctrl_03;	//0x060C
	PE_O20_SHP_MOTION_GAIN_CTRL_04_T                  shp_motion_gain_ctrl_04;	//0x0610
	PE_O20_SHP_MOTION_GAIN_CTRL_05_T                  shp_motion_gain_ctrl_05;	//0x0614
	PE_O20_SHP_MOTION_GAIN_CTRL_06_T                  shp_motion_gain_ctrl_06;	//0x0618
	PE_O20_SHP_MOTION_GAIN_CTRL_07_T                  shp_motion_gain_ctrl_07;	//0x061C
	PE_O20_SHP_MOTION_GAIN_CTRL_08_T                  shp_motion_gain_ctrl_08;	//0x0620
	PE_O20_SHP_MOTION_GAIN_CTRL_09_T                  shp_motion_gain_ctrl_09;	//0x0624
	PE_O20_SHP_MOTION_GAIN_CTRL_0A_T                  shp_motion_gain_ctrl_0a;	//0x0628
	PE_O20_SHP_MOTION_GAIN_CTRL_0B_T                  shp_motion_gain_ctrl_0b;	//0x062C
	PE_O20_SHP_MOTION_GAIN_CTRL_0C_T                  shp_motion_gain_ctrl_0c;	//0x0630
	UINT32                                            reserved288[3];	//0x634-0x63c
	PE_O20_SHP_MOTION_PROT_CTRL_00_T                  shp_motion_prot_ctrl_00;	//0x0640
	PE_O20_SHP_MOTION_PROT_CTRL_01_T                  shp_motion_prot_ctrl_01;	//0x0644
	PE_O20_SHP_MOTION_PROT_CTRL_02_T                  shp_motion_prot_ctrl_02;	//0x0648
	PE_O20_SHP_MOTION_PROT_CTRL_03_T                  shp_motion_prot_ctrl_03;	//0x064C
	PE_O20_SHP_MOTION_PROT_CTRL_04_T                  shp_motion_prot_ctrl_04;	//0x0650
	UINT32                                            reserved293[7];	//0x654-0x66c
	PE_O20_SHP_MOT_WIN_CTRL_00_T                      shp_mot_win_ctrl_00;	//0x0670
	PE_O20_SHP_MOT_WIN_CTRL_01_T                      shp_mot_win_ctrl_01;	//0x0674
	PE_O20_SHP_MOT_WIN_CTRL_02_T                      shp_mot_win_ctrl_02;	//0x0678
	PE_O20_SHP_MOT_WIN_CTRL_03_T                      shp_mot_win_ctrl_03;	//0x067C
	PE_O20_SHP_MOT_WIN_CTRL_04_T                      shp_mot_win_ctrl_04;	//0x0680
	UINT32                                            reserved298[3];	//0x684-0x68c
	PE_O20_SHP_OBJ_CTRL_00_T                          shp_obj_ctrl_00;	//0x0690
	PE_O20_SHP_OBJ_CTRL_01_T                          shp_obj_ctrl_01;	//0x0694
	PE_O20_SHP_OBJ_CTRL_02_T                          shp_obj_ctrl_02;	//0x0698
	PE_O20_SHP_OBJ_CTRL_03_T                          shp_obj_ctrl_03;	//0x069C
	PE_O20_SHP_OBJ_CTRL_04_T                          shp_obj_ctrl_04;	//0x06A0
	PE_O20_SHP_OBJ_CTRL_05_T                          shp_obj_ctrl_05;	//0x06A4
	PE_O20_SHP_OBJ_CTRL_06_T                          shp_obj_ctrl_06;	//0x06A8
	PE_O20_SHP_OBJ_CTRL_07_T                          shp_obj_ctrl_07;	//0x06AC
	PE_O20_SHP_OBJ_CTRL_08_T                          shp_obj_ctrl_08;	//0x06B0
	PE_O20_SHP_OBJ_CTRL_09_T                          shp_obj_ctrl_09;	//0x06B4
	PE_O20_SHP_OBJ_CTRL_0A_T                          shp_obj_ctrl_0a;	//0x06B8
	UINT32                                            reserved309[57];	//0x6bc-0x79c
	PE_O20_SHP_CORE_STAT_00_T                         shp_core_stat_00;	//0x07A0
	PE_O20_SHP_CORE_STAT_01_T                         shp_core_stat_01;	//0x07A4
	PE_O20_SHP_CORE_STAT_02_T                         shp_core_stat_02;	//0x07A8
	PE_O20_SHP_CORE_STAT_03_T                         shp_core_stat_03;	//0x07AC
	PE_O20_SHP_CORE_STAT_04_T                         shp_core_stat_04;	//0x07B0
	PE_O20_SHP_CORE_STAT_05_T                         shp_core_stat_05;	//0x07B4
	UINT32                                            reserved315[6];	//0x7b8-0x7cc
	PE_O20_SHP_CORE_FD_STAT_00_T                      shp_core_fd_stat_00;	//0x07D0
	PE_O20_SHP_CORE_FD_STAT_01_T                      shp_core_fd_stat_01;	//0x07D4
	PE_O20_SHP_CORE_FD_STAT_02_T                      shp_core_fd_stat_02;	//0x07D8
	PE_O20_SHP_CORE_FD_STAT_03_T                      shp_core_fd_stat_03;	//0x07DC
	PE_O20_SHP_MOTION_GAIN_STAT_00_T                  shp_motion_gain_stat_00;	//0x07E0
	PE_O20_SHP_MOTION_GAIN_STAT_01_T                  shp_motion_gain_stat_01;	//0x07E4
	UINT32                                            reserved321[6];	//0x7e8-0x7fc
	PE_O20_SHP_CORE_TMAP_STAT_00_T                    shp_core_tmap_stat_00;	//0x0800
	PE_O20_SHP_CORE_TMAP_STAT_01_T                    shp_core_tmap_stat_01;	//0x0804
	PE_O20_SHP_CORE_TMAP_STAT_02_T                    shp_core_tmap_stat_02;	//0x0808
	PE_O20_SHP_CORE_TMAP_STAT_03_T                    shp_core_tmap_stat_03;	//0x080C
	PE_O20_SHP_CORE_TMAP_STAT_04_T                    shp_core_tmap_stat_04;	//0x0810
	PE_O20_SHP_CORE_TMAP_STAT_05_T                    shp_core_tmap_stat_05;	//0x0814
	PE_O20_SHP_CORE_TMAP_STAT_06_T                    shp_core_tmap_stat_06;	//0x0818
	PE_O20_SHP_CORE_TMAP_STAT_07_T                    shp_core_tmap_stat_07;	//0x081C
	UINT32                                            reserved329[52];	//0x820-0x8ec
	PE_O20_SHP_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x08F0
	PE_O20_SHP_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x08F4
	PE_O20_SHP_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x08F8
	PE_O20_SHP_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x08FC
}PE_SHP_REG_O20_T;



typedef struct
{ 
	PE_O20_VSD_PSP_CTRL00_O_T                               psp_ctrl00;	//0x0000
	PE_O20_VSD_PSP_CTRL01_O_T                               psp_ctrl01;	//0x0004
	PE_O20_VSD_PSP_CTRL02_O_T                               psp_ctrl02;	//0x0008
	PE_O20_VSD_EDGE_TH_O_T                                  edge_th;	//0x000C
	PE_O20_VSD_FG_POSITION_O_T                              fg_position;	//0x0010
	PE_O20_VSD_PERSPECT_LUT_X0_O_T                          perspect_lut_x0;	//0x0014
	PE_O20_VSD_PERSPECT_LUT_X1_O_T                          perspect_lut_x1;	//0x0018
	PE_O20_VSD_PERSPECT_LUT_X2_O_T                          perspect_lut_x2;	//0x001C
	PE_O20_VSD_PERSPECT_LUT_X3_O_T                          perspect_lut_x3;	//0x0020
	PE_O20_VSD_PERSPECT_LUT_Y0_O_T                          perspect_lut_y0;	//0x0024
	PE_O20_VSD_PERSPECT_LUT_Y1_O_T                          perspect_lut_y1;	//0x0028
	PE_O20_VSD_PERSPECT_LUT_Y2_O_T                          perspect_lut_y2;	//0x002C
	PE_O20_VSD_PERSPECT_LUT_Y3_O_T                          perspect_lut_y3;	//0x0030
	PE_O20_VSD_PROB_MAP_O_T                                 prob_map;	//0x0034
	PE_O20_VSD_ELLIPS_MAP_O_T                               ellips_map;	//0x0038
	PE_O20_VSD_PROB_DIFF_MAP_O_T                            prob_diff_map;	//0x003C
	PE_O20_VSD_OBJECT_MAP_O_T                               object_map;	//0x0040
	PE_O20_VSD_BLUR_MAP_O_T                                 blur_map;	//0x0044
	PE_O20_VSD_DISPLAY_DEBUG_MAP_O_T                        display_debug_map;	//0x0048
	PE_O20_VSD_PSP_IIR_O_T                                  psp_iir;	//0x004C
	PE_O20_VSD_PSP_GAIN_O_T                                 psp_gain;	//0x0050
	PE_O20_VSD_PSP_DBG_MON00_O_T                            psp_dbg_mon00;	//0x0054
	PE_O20_VSD_PSP_DBG_MON01_O_T                            psp_dbg_mon01;	//0x0058
	PE_O20_VSD_VRTX_CPC_CTRL_O_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_VSD_BLUR_HCOEF01_O_T                             blur_hcoef01;	//0x0060
	PE_O20_VSD_BLUR_HCOEF23_O_T                             blur_hcoef23;	//0x0064
	PE_O20_VSD_BLUR_HCOEF45_O_T                             blur_hcoef45;	//0x0068
	PE_O20_VSD_BLUR_HCOEF67_O_T                             blur_hcoef67;	//0x006C
	PE_O20_VSD_BLUR_HCOEF8_O_T                              blur_hcoef8;	//0x0070
	PE_O20_VSD_BLUR_VCOEF01_O_T                             blur_vcoef01;	//0x0074
	PE_O20_VSD_BLUR_VCOEF23_O_T                             blur_vcoef23;	//0x0078
	PE_O20_VSD_BLUR_VCOEF4_O_T                              blur_vcoef4;	//0x007C
	PE_O20_VSD_HISTOGRAM_0_O_T                              histogram_0;	//0x0080
	PE_O20_VSD_HISTOGRAM_1_O_T                              histogram_1;	//0x0084
	PE_O20_VSD_HISTOGRAM_2_O_T                              histogram_2;	//0x0088
	PE_O20_VSD_HISTOGRAM_3_O_T                              histogram_3;	//0x008C
	PE_O20_VSD_HISTOGRAM_4_O_T                              histogram_4;	//0x0090
	PE_O20_VSD_HISTOGRAM_5_O_T                              histogram_5;	//0x0094
	PE_O20_VSD_HISTOGRAM_6_O_T                              histogram_6;	//0x0098
	PE_O20_VSD_HISTOGRAM_7_O_T                              histogram_7;	//0x009C
	PE_O20_VSD_HISTOGRAM_8_O_T                              histogram_8;	//0x00A0
	PE_O20_VSD_HISTOGRAM_9_O_T                              histogram_9;	//0x00A4
	PE_O20_VSD_HISTOGRAM_10_O_T                             histogram_10;	//0x00A8
	PE_O20_VSD_HISTOGRAM_11_O_T                             histogram_11;	//0x00AC
	PE_O20_VSD_HISTOGRAM_12_O_T                             histogram_12;	//0x00B0
	PE_O20_VSD_HISTOGRAM_13_O_T                             histogram_13;	//0x00B4
	PE_O20_VSD_HISTOGRAM_14_O_T                             histogram_14;	//0x00B8
	PE_O20_VSD_HISTOGRAM_15_O_T                             histogram_15;	//0x00BC
	PE_O20_VSD_HISTOGRAM_16_O_T                             histogram_16;	//0x00C0
	PE_O20_VSD_HISTOGRAM_17_O_T                             histogram_17;	//0x00C4
	PE_O20_VSD_HISTOGRAM_18_O_T                             histogram_18;	//0x00C8
	PE_O20_VSD_HISTOGRAM_19_O_T                             histogram_19;	//0x00CC
	PE_O20_VSD_HISTOGRAM_20_O_T                             histogram_20;	//0x00D0
	PE_O20_VSD_HISTOGRAM_21_O_T                             histogram_21;	//0x00D4
	PE_O20_VSD_HISTOGRAM_22_O_T                             histogram_22;	//0x00D8
	PE_O20_VSD_HISTOGRAM_23_O_T                             histogram_23;	//0x00DC
	PE_O20_VSD_HISTOGRAM_24_O_T                             histogram_24;	//0x00E0
	PE_O20_VSD_HISTOGRAM_25_O_T                             histogram_25;	//0x00E4
	PE_O20_VSD_HISTOGRAM_26_O_T                             histogram_26;	//0x00E8
	PE_O20_VSD_HISTOGRAM_27_O_T                             histogram_27;	//0x00EC
	PE_O20_VSD_HISTOGRAM_28_O_T                             histogram_28;	//0x00F0
	PE_O20_VSD_HISTOGRAM_29_O_T                             histogram_29;	//0x00F4
	PE_O20_VSD_HISTOGRAM_30_O_T                             histogram_30;	//0x00F8
	PE_O20_VSD_HISTOGRAM_31_O_T                             histogram_31;	//0x00FC
	PE_O20_VSD_L5_GAIN_LUT1_O_T                             l5_gain_lut1;	//0x0100
	PE_O20_VSD_L5_GAIN_LUT2_O_T                             l5_gain_lut2;	//0x0104
	PE_O20_VSD_L0_GAIN_LUT1_O_T                             l0_gain_lut1;	//0x0108
	PE_O20_VSD_L0_GAIN_LUT2_O_T                             l0_gain_lut2;	//0x010C
	PE_O20_VSD_EDGE_WIN_H_O_T                               edge_win_h;	//0x0110
	PE_O20_VSD_EDGE_WIN_V_O_T                               edge_win_v;	//0x0114
	PE_O20_VSD_EDGE0_FG_O_T                                 edge0_fg;	//0x0118
	PE_O20_VSD_EDGE0_BG_O_T                                 edge0_bg;	//0x011C
	PE_O20_VSD_EDGE1_FG_O_T                                 edge1_fg;	//0x0120
	PE_O20_VSD_EDGE1_BG_O_T                                 edge1_bg;	//0x0124
	PE_O20_VSD_PSP_IIR1_O_T                                 psp_iir1;	//0x0128
	PE_O20_VSD_BG_MEASURE_CTRL_O_T                          bg_measure_ctrl;	//0x012C
	PE_O20_VSD_BG_MEASURE_READ0_O_T                         bg_measure_read0;	//0x0130
	PE_O20_VSD_BG_MEASURE_READ1_O_T                         bg_measure_read1;	//0x0134
	PE_O20_VSD_BG_MEASURE_READ2_O_T                         bg_measure_read2;	//0x0138
	PE_O20_VSD_BG_MEASURE_READ3_O_T                         bg_measure_read3;	//0x013C
	PE_O20_VSD_BG_MEASURE_READ4_O_T                         bg_measure_read4;	//0x0140
	PE_O20_VSD_FACE0_SET_O_T                                face0_set;	//0x0144
	PE_O20_VSD_FACE1_SET_O_T                                face1_set;	//0x0148
	PE_O20_VSD_FACE2_SET_O_T                                face2_set;	//0x014C
	PE_O20_VSD_FACE3_SET_O_T                                face3_set;	//0x0150
	PE_O20_VSD_ELLIPS0_SET_O_T                              ellips0_set;	//0x0154
	PE_O20_VSD_ELLIPS1_SET_O_T                              ellips1_set;	//0x0158
	PE_O20_VSD_ELLIPS2_SET_O_T                              ellips2_set;	//0x015C
	PE_O20_VSD_ELLIPS3_SET_O_T                              ellips3_set;	//0x0160
}PE_VSD_OBC_OBJT_REG_O20_T;

typedef struct
{ 
	PE_O20_VSD_PSP_CTRL00_T                               psp_ctrl00;	//0x0000
	PE_O20_VSD_PSP_CTRL01_T                               psp_ctrl01;	//0x0004
	PE_O20_VSD_PSP_CTRL02_T                               psp_ctrl02;	//0x0008
	PE_O20_VSD_EDGE_TH_T                                  edge_th;	//0x000C
	PE_O20_VSD_FG_POSITION_T                              fg_position;	//0x0010
	PE_O20_VSD_REG_PERSPECT_GAIN_CTRL_0_T                 reg_perspect_gain_ctrl_0;	//0x0014
	PE_O20_VSD_REG_PERSPECT_LUT_X_0_T                     reg_perspect_lut_x_0;	//0x0018
	PE_O20_VSD_REG_PERSPECT_LUT_X_1_T                     reg_perspect_lut_x_1;	//0x001C
	PE_O20_VSD_REG_PERSPECT_LUT_X_2_T                     reg_perspect_lut_x_2;	//0x0020
	PE_O20_VSD_RESERVED4_T                                reserved4;	//0x0024
	PE_O20_VSD_RESERVED5_T                                reserved5;	//0x0028
	PE_O20_VSD_RESERVED6_T                                reserved6;	//0x002C
	PE_O20_VSD_RESERVED7_T                                reserved7;	//0x0030
	PE_O20_VSD_PROB_MAP_T                                 prob_map;	//0x0034
	PE_O20_VSD_ELLIPS_MAP_T                               ellips_map;	//0x0038
	PE_O20_VSD_PROB_DIFF_MAP_T                            prob_diff_map;	//0x003C
	PE_O20_VSD_OBJECT_MAP_T                               object_map;	//0x0040
	PE_O20_VSD_BLUR_MAP_T                                 blur_map;	//0x0044
	PE_O20_VSD_DISPLAY_DEBUG_MAP_T                        display_debug_map;	//0x0048
	PE_O20_VSD_PSP_IIR_T                                  psp_iir;	//0x004C
	PE_O20_VSD_PSP_GAIN_T                                 psp_gain;	//0x0050
	PE_O20_VSD_PSP_DBG_MON00_T                            psp_dbg_mon00;	//0x0054
	PE_O20_VSD_PSP_DBG_MON01_T                            psp_dbg_mon01;	//0x0058
	PE_O20_VSD_VRTX_CPC_CTRL_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_VSD_BLUR_HCOEF01_T                             blur_hcoef01;	//0x0060
	PE_O20_VSD_BLUR_HCOEF23_T                             blur_hcoef23;	//0x0064
	PE_O20_VSD_BLUR_HCOEF45_T                             blur_hcoef45;	//0x0068
	PE_O20_VSD_BLUR_HCOEF67_T                             blur_hcoef67;	//0x006C
	PE_O20_VSD_BLUR_HCOEF8_T                              blur_hcoef8;	//0x0070
	PE_O20_VSD_BLUR_VCOEF01_T                             blur_vcoef01;	//0x0074
	PE_O20_VSD_BLUR_VCOEF23_T                             blur_vcoef23;	//0x0078
	PE_O20_VSD_BLUR_VCOEF4_T                              blur_vcoef4;	//0x007C
	PE_O20_VSD_HISTOGRAM_0_T                              histogram_0;	//0x0080
	PE_O20_VSD_HISTOGRAM_1_T                              histogram_1;	//0x0084
	PE_O20_VSD_HISTOGRAM_2_T                              histogram_2;	//0x0088
	PE_O20_VSD_HISTOGRAM_3_T                              histogram_3;	//0x008C
	PE_O20_VSD_HISTOGRAM_4_T                              histogram_4;	//0x0090
	PE_O20_VSD_HISTOGRAM_5_T                              histogram_5;	//0x0094
	PE_O20_VSD_HISTOGRAM_6_T                              histogram_6;	//0x0098
	PE_O20_VSD_HISTOGRAM_7_T                              histogram_7;	//0x009C
	PE_O20_VSD_HISTOGRAM_8_T                              histogram_8;	//0x00A0
	PE_O20_VSD_HISTOGRAM_9_T                              histogram_9;	//0x00A4
	PE_O20_VSD_HISTOGRAM_10_T                             histogram_10;	//0x00A8
	PE_O20_VSD_HISTOGRAM_11_T                             histogram_11;	//0x00AC
	PE_O20_VSD_HISTOGRAM_12_T                             histogram_12;	//0x00B0
	PE_O20_VSD_HISTOGRAM_13_T                             histogram_13;	//0x00B4
	PE_O20_VSD_HISTOGRAM_14_T                             histogram_14;	//0x00B8
	PE_O20_VSD_HISTOGRAM_15_T                             histogram_15;	//0x00BC
	PE_O20_VSD_HISTOGRAM_16_T                             histogram_16;	//0x00C0
	PE_O20_VSD_HISTOGRAM_17_T                             histogram_17;	//0x00C4
	PE_O20_VSD_HISTOGRAM_18_T                             histogram_18;	//0x00C8
	PE_O20_VSD_HISTOGRAM_19_T                             histogram_19;	//0x00CC
	PE_O20_VSD_HISTOGRAM_20_T                             histogram_20;	//0x00D0
	PE_O20_VSD_HISTOGRAM_21_T                             histogram_21;	//0x00D4
	PE_O20_VSD_HISTOGRAM_22_T                             histogram_22;	//0x00D8
	PE_O20_VSD_HISTOGRAM_23_T                             histogram_23;	//0x00DC
	PE_O20_VSD_HISTOGRAM_24_T                             histogram_24;	//0x00E0
	PE_O20_VSD_HISTOGRAM_25_T                             histogram_25;	//0x00E4
	PE_O20_VSD_HISTOGRAM_26_T                             histogram_26;	//0x00E8
	PE_O20_VSD_HISTOGRAM_27_T                             histogram_27;	//0x00EC
	PE_O20_VSD_HISTOGRAM_28_T                             histogram_28;	//0x00F0
	PE_O20_VSD_HISTOGRAM_29_T                             histogram_29;	//0x00F4
	PE_O20_VSD_HISTOGRAM_30_T                             histogram_30;	//0x00F8
	PE_O20_VSD_HISTOGRAM_31_T                             histogram_31;	//0x00FC
	PE_O20_VSD_L5_GAIN_LUT1_T                             l5_gain_lut1;	//0x0100
	PE_O20_VSD_L5_GAIN_LUT2_T                             l5_gain_lut2;	//0x0104
	PE_O20_VSD_L0_GAIN_LUT1_T                             l0_gain_lut1;	//0x0108
	PE_O20_VSD_L0_GAIN_LUT2_T                             l0_gain_lut2;	//0x010C
	PE_O20_VSD_EDGE_WIN_H_T                               edge_win_h;	//0x0110
	PE_O20_VSD_EDGE_WIN_V_T                               edge_win_v;	//0x0114
	PE_O20_VSD_EDGE0_FG_T                                 edge0_fg;	//0x0118
	PE_O20_VSD_EDGE0_BG_T                                 edge0_bg;	//0x011C
	PE_O20_VSD_EDGE1_FG_T                                 edge1_fg;	//0x0120
	PE_O20_VSD_EDGE1_BG_T                                 edge1_bg;	//0x0124
	PE_O20_VSD_PSP_IIR1_T                                 psp_iir1;	//0x0128
	PE_O20_VSD_BG_MEASURE_CTRL_T                          bg_measure_ctrl;	//0x012C
	PE_O20_VSD_BG_MEASURE_READ0_T                         bg_measure_read0;	//0x0130
	PE_O20_VSD_BG_MEASURE_READ1_T                         bg_measure_read1;	//0x0134
	PE_O20_VSD_BG_MEASURE_READ2_T                         bg_measure_read2;	//0x0138
	PE_O20_VSD_BG_MEASURE_READ3_T                         bg_measure_read3;	//0x013C
	PE_O20_VSD_BG_MEASURE_READ4_T                         bg_measure_read4;	//0x0140
	PE_O20_VSD_FACE0_SET_T                                face0_set;	//0x0144
	PE_O20_VSD_FACE1_SET_T                                face1_set;	//0x0148
	PE_O20_VSD_FACE2_SET_T                                face2_set;	//0x014C
	PE_O20_VSD_FACE3_SET_T                                face3_set;	//0x0150
	PE_O20_VSD_ELLIPS0_SET_T                              ellips0_set;	//0x0154
	PE_O20_VSD_ELLIPS1_SET_T                              ellips1_set;	//0x0158
	PE_O20_VSD_ELLIPS2_SET_T                              ellips2_set;	//0x015C
	PE_O20_VSD_ELLIPS3_SET_T                              ellips3_set;	//0x0160
}PE_VSD_OBC_FACE_REG_O20_T;

typedef struct
{ 
	PE_O20_REG_RCE_OBJT_CTRL_00_T                     reg_rce_objt_ctrl_00;	//0x0000
	PE_O20_REG_RCE_OBJT_CTRL_01_T                     reg_rce_objt_ctrl_01;	//0x0004
	PE_O20_REG_RCE_OBJT_CTRL_02_T                     reg_rce_objt_ctrl_02;	//0x0008
	PE_O20_REG_RCE_OBJT_CTRL_03_T                     reg_rce_objt_ctrl_03;	//0x000C
	PE_O20_REG_RCE_OBJT_CTRL_04_T                     reg_rce_objt_ctrl_04;	//0x0010
	PE_O20_REG_RCE_OBJT_CTRL_05_T                     reg_rce_objt_ctrl_05;	//0x0014
	PE_O20_REG_RCE_OBJT_CTRL_06_T                     reg_rce_objt_ctrl_06;	//0x0018
	PE_O20_REG_RCE_OBJT_CTRL_07_T                     reg_rce_objt_ctrl_07;	//0x001C
	PE_O20_REG_RCE_OBJT_CTRL_08_T                     reg_rce_objt_ctrl_08;	//0x0020
	PE_O20_REG_RCE_OBJT_CTRL_09_T                     reg_rce_objt_ctrl_09;	//0x0024
	PE_O20_REG_RCE_OBJT_CTRL_10_T                     reg_rce_objt_ctrl_10;	//0x0028
	PE_O20_REG_RCE_OBJT_CTRL_11_T                     reg_rce_objt_ctrl_11;	//0x002C
	PE_O20_REG_RCE_OBJT_CTRL_12_T                     reg_rce_objt_ctrl_12;	//0x0030
	PE_O20_REG_RCE_OBJT_CTRL_13_T                     reg_rce_objt_ctrl_13;	//0x0034
	PE_O20_REG_RCE_OBJT_CTRL_14_T                     reg_rce_objt_ctrl_14;	//0x0038
	PE_O20_REG_RCE_OBJT_CTRL_15_T                     reg_rce_objt_ctrl_15;	//0x003C
	PE_O20_REG_RCE_OBJT_CTRL_16_T                     reg_rce_objt_ctrl_16;	//0x0040
	PE_O20_REG_RCE_OBJT_CTRL_17_T                     reg_rce_objt_ctrl_17;	//0x0044
	PE_O20_REG_RCE_OBJT_CTRL_18_T                     reg_rce_objt_ctrl_18;	//0x0048
	PE_O20_REG_RCE_OBJT_CTRL_19_T                     reg_rce_objt_ctrl_19;	//0x004C
	PE_O20_REG_RCE_OBJT_CTRL_20_T                     reg_rce_objt_ctrl_20;	//0x0050
	PE_O20_REG_RCE_OBJT_CTRL_21_T                     reg_rce_objt_ctrl_21;	//0x0054
	PE_O20_REG_RCE_OBJT_CTRL_22_T                     reg_rce_objt_ctrl_22;	//0x0058
	PE_O20_REG_RCE_OBJT_CTRL_23_T                     reg_rce_objt_ctrl_23;	//0x005C
	PE_O20_REG_RCE_OBJT_CTRL_24_T                     reg_rce_objt_ctrl_24;	//0x0060
	PE_O20_REG_RCE_OBJT_CTRL_25_T                     reg_rce_objt_ctrl_25;	//0x0064
	PE_O20_REG_RCE_OBJT_CTRL_26_T                     reg_rce_objt_ctrl_26;	//0x0068
	PE_O20_REG_RCE_OBJT_CTRL_27_T                     reg_rce_objt_ctrl_27;	//0x006C
	PE_O20_REG_RCE_OBJT_CTRL_28_T                     reg_rce_objt_ctrl_28;	//0x0070
	PE_O20_REG_RCE_OBJT_CTRL_29_T                     reg_rce_objt_ctrl_29;	//0x0074
	PE_O20_REG_RCE_OBJT_CTRL_30_T                     reg_rce_objt_ctrl_30;	//0x0078
	PE_O20_REG_RCE_OBJT_CTRL_31_T                     reg_rce_objt_ctrl_31;	//0x007C
}PE_VSD_RCE_OBJT_REG_O20_T;

typedef struct
{ 
	PE_O20_REG_RCE_FACE_CTRL_00_T                     reg_rce_face_ctrl_00;	//0x0000
	PE_O20_REG_RCE_FACE_CTRL_01_T                     reg_rce_face_ctrl_01;	//0x0004
	PE_O20_REG_RCE_FACE_CTRL_02_T                     reg_rce_face_ctrl_02;	//0x0008
	PE_O20_REG_RCE_FACE_CTRL_03_T                     reg_rce_face_ctrl_03;	//0x000C
	PE_O20_REG_RCE_FACE_CTRL_04_T                     reg_rce_face_ctrl_04;	//0x0010
	PE_O20_REG_RCE_FACE_CTRL_05_T                     reg_rce_face_ctrl_05;	//0x0014
	PE_O20_REG_RCE_FACE_CTRL_06_T                     reg_rce_face_ctrl_06;	//0x0018
	PE_O20_REG_RCE_FACE_CTRL_07_T                     reg_rce_face_ctrl_07;	//0x001C
	PE_O20_REG_RCE_FACE_CTRL_08_T                     reg_rce_face_ctrl_08;	//0x0020
	PE_O20_REG_RCE_FACE_CTRL_09_T                     reg_rce_face_ctrl_09;	//0x0024
	PE_O20_REG_RCE_FACE_CTRL_10_T                     reg_rce_face_ctrl_10;	//0x0028
	PE_O20_REG_RCE_FACE_CTRL_11_T                     reg_rce_face_ctrl_11;	//0x002C
	PE_O20_REG_RCE_FACE_CTRL_12_T                     reg_rce_face_ctrl_12;	//0x0030
	PE_O20_REG_RCE_FACE_CTRL_13_T                     reg_rce_face_ctrl_13;	//0x0034
	PE_O20_REG_RCE_FACE_CTRL_14_T                     reg_rce_face_ctrl_14;	//0x0038
	PE_O20_REG_RCE_FACE_CTRL_15_T                     reg_rce_face_ctrl_15;	//0x003C
	PE_O20_REG_RCE_FACE_CTRL_16_T                     reg_rce_face_ctrl_16;	//0x0040
	PE_O20_REG_RCE_FACE_CTRL_17_T                     reg_rce_face_ctrl_17;	//0x0044
	PE_O20_REG_RCE_FACE_CTRL_18_T                     reg_rce_face_ctrl_18;	//0x0048
	PE_O20_REG_RCE_FACE_CTRL_19_T                     reg_rce_face_ctrl_19;	//0x004C
	PE_O20_REG_RCE_FACE_CTRL_20_T                     reg_rce_face_ctrl_20;	//0x0050
	PE_O20_REG_RCE_FACE_CTRL_21_T                     reg_rce_face_ctrl_21;	//0x0054
	PE_O20_REG_RCE_FACE_CTRL_22_T                     reg_rce_face_ctrl_22;	//0x0058
	PE_O20_REG_RCE_FACE_CTRL_23_T                     reg_rce_face_ctrl_23;	//0x005C
	PE_O20_REG_RCE_FACE_CTRL_24_T                     reg_rce_face_ctrl_24;	//0x0060
	PE_O20_REG_RCE_FACE_CTRL_25_T                     reg_rce_face_ctrl_25;	//0x0064
	PE_O20_REG_RCE_FACE_CTRL_26_T                     reg_rce_face_ctrl_26;	//0x0068
	PE_O20_REG_RCE_FACE_CTRL_27_T                     reg_rce_face_ctrl_27;	//0x006C
	PE_O20_REG_RCE_FACE_CTRL_28_T                     reg_rce_face_ctrl_28;	//0x0070
	PE_O20_REG_RCE_FACE_CTRL_29_T                     reg_rce_face_ctrl_29;	//0x0074
	PE_O20_REG_RCE_FACE_CTRL_30_T                     reg_rce_face_ctrl_30;	//0x0078
	PE_O20_REG_RCE_FACE_CTRL_31_T                     reg_rce_face_ctrl_31;	//0x007C
}PE_VSD_RCE_FACE_REG_O20_T;

typedef struct
{ 
	PE_O20_DTM_TOP_CTRL_00_T                          dtm_top_ctrl_00;	//0x0000
	PE_O20_DTM_TOP_CTRL_01_T                          dtm_top_ctrl_01;	//0x0004
	PE_O20_DTM_TOP_CTRL_02_T                          dtm_top_ctrl_02;	//0x0008
	PE_O20_DTM_TOP_CTRL_03_T                          dtm_top_ctrl_03;	//0x000C
	PE_O20_DTM_TOP_CTRL_04_T                          dtm_top_ctrl_04;	//0x0010
	PE_O20_DTM_TOP_CTRL_05_T                          dtm_top_ctrl_05;	//0x0014
	UINT32                                            reserved6[2];	//0x18-0x1c
	PE_O20_DTM_FSW_CTRL_00_T                          dtm_fsw_ctrl_00;	//0x0020
	PE_O20_DTM_FSW_CTRL_01_T                          dtm_fsw_ctrl_01;	//0x0024
	PE_O20_DTM_FSW_CTRL_02_T                          dtm_fsw_ctrl_02;	//0x0028
	PE_O20_DTM_FSW_CTRL_03_T                          dtm_fsw_ctrl_03;	//0x002C
	UINT32                                            reserved10[4];	//0x30-0x3c
	PE_O20_DTM_CSC1_CTRL_00_T                         dtm_csc1_ctrl_00;	//0x0040
	PE_O20_DTM_CSC1_CTRL_01_T                         dtm_csc1_ctrl_01;	//0x0044
	PE_O20_DTM_CSC1_CTRL_02_T                         dtm_csc1_ctrl_02;	//0x0048
	PE_O20_DTM_CSC1_CTRL_03_T                         dtm_csc1_ctrl_03;	//0x004C
	PE_O20_DTM_CSC1_CTRL_04_T                         dtm_csc1_ctrl_04;	//0x0050
	PE_O20_DTM_CSC1_CTRL_05_T                         dtm_csc1_ctrl_05;	//0x0054
	PE_O20_DTM_CSC1_CTRL_06_T                         dtm_csc1_ctrl_06;	//0x0058
	PE_O20_DTM_CSC1_CTRL_07_T                         dtm_csc1_ctrl_07;	//0x005C
	PE_O20_DTM_CSC1_CTRL_08_T                         dtm_csc1_ctrl_08;	//0x0060
	UINT32                                            reserved19[3];	//0x64-0x6c
	PE_O20_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0x0070
	PE_O20_DTM_LLUT_CTRL_01_T                         dtm_llut_ctrl_01;	//0x0074
	PE_O20_DTM_LLUT_CTRL_02_T                         dtm_llut_ctrl_02;	//0x0078
	PE_O20_DTM_LLUT_CTRL_03_T                         dtm_llut_ctrl_03;	//0x007C
	PE_O20_DTM_LLUT_CTRL_04_T                         dtm_llut_ctrl_04;	//0x0080
	PE_O20_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0x0084
	PE_O20_DTM_LLUT0_IA_CTRL_T                        dtm_llut0_ia_ctrl;	//0x0088
	PE_O20_DTM_LLUT0_IA_DATA_T                        dtm_llut0_ia_data;	//0x008C
	PE_O20_DTM_LLUT1_IA_CTRL_T                        dtm_llut1_ia_ctrl;	//0x0090
	PE_O20_DTM_LLUT1_IA_DATA_T                        dtm_llut1_ia_data;	//0x0094
	PE_O20_DTM_LLUT2_IA_CTRL_T                        dtm_llut2_ia_ctrl;	//0x0098
	PE_O20_DTM_LLUT2_IA_DATA_T                        dtm_llut2_ia_data;	//0x009C
	UINT32                                            reserved31[4];	//0xa0-0xac
	PE_O20_DTM_CSC3_CTRL_00_T                         dtm_csc3_ctrl_00;	//0x00B0
	PE_O20_DTM_CSC3_CTRL_01_T                         dtm_csc3_ctrl_01;	//0x00B4
	PE_O20_DTM_CSC3_CTRL_02_T                         dtm_csc3_ctrl_02;	//0x00B8
	PE_O20_DTM_CSC3_CTRL_03_T                         dtm_csc3_ctrl_03;	//0x00BC
	PE_O20_DTM_CSC3_CTRL_04_T                         dtm_csc3_ctrl_04;	//0x00C0
	PE_O20_DTM_CSC3_CTRL_05_T                         dtm_csc3_ctrl_05;	//0x00C4
	PE_O20_DTM_CSC3_CTRL_06_T                         dtm_csc3_ctrl_06;	//0x00C8
	PE_O20_DTM_CSC3_CTRL_07_T                         dtm_csc3_ctrl_07;	//0x00CC
	PE_O20_DTM_CSC3_CTRL_08_T                         dtm_csc3_ctrl_08;	//0x00D0
	UINT32                                            reserved40[3];	//0xd4-0xdc
	PE_O20_DTM_HUE_SAT_CTRL_T                         dtm_hue_sat_ctrl;	//0x00E0
	UINT32                                            reserved41[3];	//0xe4-0xec
	PE_O20_DTM_ODD_LLUT_CTRL_01_T                     dtm_odd_llut_ctrl_01;	//0x00F0
	PE_O20_DTM_ODD_LLUT_CTRL_02_T                     dtm_odd_llut_ctrl_02;	//0x00F4
	PE_O20_DTM_ODD_LLUT_CTRL_03_T                     dtm_odd_llut_ctrl_03;	//0x00F8
	PE_O20_DTM_ODD_LLUT_CTRL_04_T                     dtm_odd_llut_ctrl_04;	//0x00FC
}PE_VSD_DTM_REG_O20_T;


#endif
