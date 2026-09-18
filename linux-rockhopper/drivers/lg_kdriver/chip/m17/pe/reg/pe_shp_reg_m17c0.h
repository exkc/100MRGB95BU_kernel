#ifndef _PE_SHP_REG_M17C0_H_
#define _PE_SHP_REG_M17C0_H_
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
	reg_top_detour                     :1 ,	// 4:4
	reg_top_bypass                     :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_cg_disable                 :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ,	// 12:12
	reserved04                         :3 ,	// reserved
	reg_top_update_ctrl                :5 ,	// 20:16
	reserved05                         :3 ,	// reserved
	reg_top_422to444_mode              :1 ,	// 24:24
	reserved06                         :3 ,	// reserved
	reg_top_mode_444                   :1 ;	// 28:28
}PE_M17C0_SHP_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d004L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_M17C0_SHP_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d008L shp_core0_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_core0_width                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_core0_height               :12;	// 27:16
}PE_M17C0_SHP_CORE0_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d00cL shp_core1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_core1_width                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_core1_height               :12;	// 27:16
}PE_M17C0_SHP_CORE1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d018L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_va_ris_cnt                 :16,	// 15:0
	reg_top_va_fal_cnt                 :16;	// 31:16
}PE_M17C0_SHP_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d01cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_pic_init_latency           :12;	// 11:0
}PE_M17C0_SHP_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d040L split_ctrl00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_core0_max                :13,	// 12:0
	reserved01                         :18,	// reserved
	reg_split_y_detour_en              :1 ;	// 31:31
}PE_M17C0_SPLIT_CTRL00_T;
/*-----------------------------------------------------------------------------
                             0xc900d044L split_ctrl01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_core1_max                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_split_core1_min                :13;	// 28:16
}PE_M17C0_SPLIT_CTRL01_T;
/*-----------------------------------------------------------------------------
                             0xc900d048L split_ctrl02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_split_padding_st_pos           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_split_padding_ed_pos           :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_split_padding_ed_en            :1 ,	// 30:30
	reg_split_padding_st_en            :1 ;	// 31:31
}PE_M17C0_SPLIT_CTRL02_T;
/*-----------------------------------------------------------------------------
                             0xc900d054L merg_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_merg_line_end_pos              :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_merg_boundary_size             :8 ,	// 23:16
	reserved02                         :7 ,	// reserved
	reg_merg_detour_en                 :1 ;	// 31:31
}PE_M17C0_MERG_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900d058L out_hgos_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hgos_head_crop_ptr         :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_out_hgos_tail_crop_ptr         :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_out_hgos_tail_en               :1 ,	// 30:30
	reg_out_hgos_head_en               :1 ;	// 31:31
}PE_M17C0_OUT_HGOS_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900d05cL out_vgos_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_vgos_head_crop_ptr         :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_out_vgos_tail_crop_ptr         :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_out_vgos_tail_en               :1 ,	// 30:30
	reg_out_vgos_head_en               :1 ;	// 31:31
}PE_M17C0_OUT_VGOS_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900d060L disp_sync_dly_addr00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_vsync                 :16,	// 15:0
	reg_sync_dly_vfp                   :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR00_T;
/*-----------------------------------------------------------------------------
                             0xc900d064L disp_sync_dly_addr01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_va                    :16,	// 15:0
	reg_sync_dly_vbp                   :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR01_T;
/*-----------------------------------------------------------------------------
                             0xc900d068L disp_sync_dly_addr02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_hsync                 :16,	// 15:0
	reg_sync_dly_hfp                   :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR02_T;
/*-----------------------------------------------------------------------------
                             0xc900d06cL disp_sync_dly_addr03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_ha                    :16,	// 15:0
	reg_sync_dly_hbp                   :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR03_T;
/*-----------------------------------------------------------------------------
                             0xc900d070L disp_sync_dly_addr04                             
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
	reserved01                         :3 ,	// reserved
	reg_sync_dly_cnt_rst_h_value_en    :1 ,	// 28:28
	reg_sync_dly_cnt_rst_v_value_en    :1 ,	// 29:29
	reserved02                         :1 ,	// reserved
	reg_sync_dly_force_update          :1 ;	// 31:31
}PE_M17C0_DISP_SYNC_DLY_ADDR04_T;
/*-----------------------------------------------------------------------------
                             0xc900d074L disp_sync_dly_addr05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_sync_h_dly            :16,	// 15:0
	reg_sync_dly_sync_v_dly            :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR05_T;
/*-----------------------------------------------------------------------------
                             0xc900d078L disp_sync_dly_addr06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_rst_h_value       :16,	// 15:0
	reg_sync_dly_cnt_rst_v_value       :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR06_T;
/*-----------------------------------------------------------------------------
                             0xc900d07cL disp_sync_dly_addr07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_actv_h_dly       :16,	// 15:0
	reg_sync_dly_auto_actv_v_dly       :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR07_T;
/*-----------------------------------------------------------------------------
                             0xc900d080L disp_sync_dly_addr08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_sync_h_dly       :16,	// 15:0
	reg_sync_dly_auto_sync_v_dly       :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR08_T;
/*-----------------------------------------------------------------------------
                             0xc900d084L disp_sync_dly_addr09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_normal_number         :16;	// 15:0
}PE_M17C0_DISP_SYNC_DLY_ADDR09_T;
/*-----------------------------------------------------------------------------
                             0xc900d088L disp_sync_dly_addr0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_h_rst_position    :16,	// 15:0
	reg_sync_dly_cnt_v_rst_position    :16;	// 31:16
}PE_M17C0_DISP_SYNC_DLY_ADDR0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d0a0L shp_esf_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_detour_en                  :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_esf_edge_shift_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_esf_dbg_en                     :1 ;	// 8:8
}PE_M17C0_SHP_ESF_CTRL_00_T;
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
}PE_M17C0_SHP_ESF_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d0a8L shp_esf_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_esf_ltv_offset                 :8 ,	// 7:0
	reg_esf_ltv_mul                    :8 ;	// 15:8
}PE_M17C0_SHP_ESF_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b0L shp_derh_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b4L shp_derh_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d0b8L shp_derh_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d0bcL shp_derh_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d0c0L shp_derh_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d0c4L shp_derh_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_derh_csft_gain                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_th_gain_edge              :6 ,	// 21:16
	reg_derh_th_gain_flat              :2 ,	// 23:22
	reg_derh_th_manual_th              :7 ,	// 30:24
	reg_derh_th_manual_en              :1 ;	// 31:31
}PE_M17C0_SHP_DERH_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d0c8L shp_derh_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_bflt_tap_size             :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_derh_edge_filter_gain_w        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_derh_edge_filter_gain_b        :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_derh_amean_en                  :1 ,	// 24:24
	reserved04                         :1 ,	// reserved
	reg_derh_edge_filter_v_tap         :2 ,	// 27:26
	reserved05                         :3 ,	// reserved
	reg_derh_edge_y_filter_en          :1 ;	// 31:31
}PE_M17C0_SHP_DERH_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d0ccL shp_derh_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derh_avg_filter_tap            :2 ,	// 1:0
	reserved01                         :22,	// reserved
	reg_derh_flat_filter_gain          :6 ,	// 29:24
	reg_derh_flat_filter_type          :1 ,	// 30:30
	reg_derh_flat_filter_en            :1 ;	// 31:31
}PE_M17C0_SHP_DERH_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d0d0L shp_derh_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d0d4L shp_derh_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d0d8L shp_derh_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d0dcL shp_derh_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d0e0L shp_derh_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERH_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d0f0L shp_derv_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_en                        :1 ,	// 0:0
	reg_derv_w_sel                     :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_derv_bif_en                    :1 ,	// 3:3
	reg_derv_output_mux                :4 ,	// 7:4
	reg_derv_bif_manual_th             :8 ,	// 15:8
	reg_derv_th_gain                   :6 ,	// 21:16
	reserved02                         :2 ,	// reserved
	reg_derv_th_mode                   :1 ;	// 24:24
}PE_M17C0_SHP_DERV_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900d0f4L shp_derv_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_csft_gain                 :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_derv_csft_mode                 :1 ;	// 8:8
}PE_M17C0_SHP_DERV_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900d0f8L shp_derv_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_DERV_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900d0fcL shp_derv_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_derv_gain_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_derv_gain_w                    :7 ;	// 14:8
}PE_M17C0_SHP_DERV_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900d110L shp_dp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_debug_display               :4 ,	// 3:0
	reg_dp_detour_en                   :1 ,	// 4:4
	reserved01                         :3 ,	// reserved
	reg_dp_buffer_detour_en            :1 ;	// 8:8
}PE_M17C0_SHP_DP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d114L shp_dp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_spc_gain_e_b                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_spc_gain_e_w                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_spc_gain_t_b                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_spc_gain_t_w                   :7 ;	// 30:24
}PE_M17C0_SHP_DP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d118L shp_dp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ptic_gain_e_b                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_ptic_gain_e_w                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_ptic_gain_t_b                  :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_ptic_gain_t_w                  :7 ;	// 30:24
}PE_M17C0_SHP_DP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d11cL shp_dp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tgenc_gain_e_b                 :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_tgenc_gain_e_w                 :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_tgenc_gain_t_b                 :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_tgenc_gain_t_w                 :7 ;	// 30:24
}PE_M17C0_SHP_DP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d120L shp_dp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_snr_blur_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_snr_blur_sel                   :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_snr_bilateral_th               :8 ;	// 15:8
}PE_M17C0_SHP_DP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d124L shp_dp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_y0                         :8 ,	// 7:0
	reg_der_x0                         :8 ,	// 15:8
	reg_der_y1                         :8 ,	// 23:16
	reg_der_x1                         :8 ;	// 31:24
}PE_M17C0_SHP_DP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d128L shp_dp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_der_y2                         :8 ,	// 7:0
	reg_der_x2                         :8 ,	// 15:8
	reg_der_y3                         :8 ,	// 23:16
	reg_der_x3                         :8 ;	// 31:24
}PE_M17C0_SHP_DP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d12cL shp_dp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dp_sum_gain                    :8 ;	// 7:0
}PE_M17C0_SHP_DP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d130L shp_sp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_shp_en                      :1 ,	// 0:0
	reserved01                         :11,	// reserved
	reg_sp_sobel_sel                   :2 ;	// 13:12
}PE_M17C0_SHP_SP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d134L shp_sp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_im_os_gain                  :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_sp_im_us_gain                  :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_sp_im_gain_h                   :8 ,	// 23:16
	reg_sp_im_gain_v                   :8 ;	// 31:24
}PE_M17C0_SHP_SP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d138L shp_sp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_sobel_weight                :8 ,	// 7:0
	reg_sp_lap_weight                  :8 ,	// 15:8
	reg_sp_sobel_man_en                :1 ,	// 16:16
	reserved01                         :7 ,	// reserved
	reg_sp_sobel_man_gain              :8 ;	// 31:24
}PE_M17C0_SHP_SP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d13cL shp_sp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :20,	// reserved
	reg_sp_lap_gain_h_7                :4 ,	// 23:20
	reg_sp_lap_gain_h_5                :4 ,	// 27:24
	reg_sp_lap_gain_h_3                :4 ;	// 31:28
}PE_M17C0_SHP_SP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d140L shp_sp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sp_dbg_sel                     :4 ,	// 11:8
	reg_sp_sobel_gx_manual_en          :1 ,	// 12:12
	reserved02                         :3 ,	// reserved
	reg_sp_sobel_gx_manual_gain        :8 ;	// 23:16
}PE_M17C0_SHP_SP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d144L shp_sp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_SP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d148L shp_sp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lap_h_mode                  :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_sp_lap_v_mode                  :3 ;	// 6:4
}PE_M17C0_SHP_SP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d14cL shp_sp_ctrl_07                             
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
}PE_M17C0_SHP_SP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d150L shp_sp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_gb_x2                       :8 ,	// 7:0
	reg_sp_gb_y2                       :8 ,	// 15:8
	reg_sp_gb_y3                       :8 ;	// 23:16
}PE_M17C0_SHP_SP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d154L shp_sp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_x_l0                   :8 ,	// 7:0
	reg_sp_lum1_x_l1                   :8 ,	// 15:8
	reg_sp_lum1_x_h0                   :8 ,	// 23:16
	reg_sp_lum1_x_h1                   :8 ;	// 31:24
}PE_M17C0_SHP_SP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d158L shp_sp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum1_y0                     :8 ,	// 7:0
	reg_sp_lum1_y1                     :8 ,	// 15:8
	reg_sp_lum1_y2                     :8 ,	// 23:16
	reg_sp_lum2_x_l0                   :8 ;	// 31:24
}PE_M17C0_SHP_SP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d15cL shp_sp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_x_l1                   :8 ,	// 7:0
	reg_sp_lum2_x_h0                   :8 ,	// 15:8
	reg_sp_lum2_x_h1                   :8 ,	// 23:16
	reg_sp_lum2_y0                     :8 ;	// 31:24
}PE_M17C0_SHP_SP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d160L shp_sp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sp_lum2_y1                     :8 ,	// 7:0
	reg_sp_lum2_y2                     :8 ;	// 15:8
}PE_M17C0_SHP_SP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d170L shp_mp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_shp_en                      :1 ,	// 0:0
	reserved01                         :11,	// reserved
	reg_mp_sobel_sel                   :2 ;	// 13:12
}PE_M17C0_SHP_MP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d174L shp_mp_ctrl_01                             
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
}PE_M17C0_SHP_MP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d178L shp_mp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_sobel_weight                :8 ,	// 7:0
	reg_mp_lap_weight                  :8 ,	// 15:8
	reg_mp_sobel_man_en                :1 ,	// 16:16
	reserved01                         :7 ,	// reserved
	reg_mp_sobel_man_gain              :8 ;	// 31:24
}PE_M17C0_SHP_MP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d17cL shp_mp_ctrl_03                             
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
}PE_M17C0_SHP_MP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d180L shp_mp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_mp_dbg_sel                     :4 ,	// 11:8
	reg_mp_sobel_gx_manual_en          :1 ,	// 12:12
	reserved02                         :3 ,	// reserved
	reg_mp_sobel_gx_manual_gain        :8 ,	// 23:16
	reg_mp_par_out_sel                 :3 ;	// 26:24
}PE_M17C0_SHP_MP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d184L shp_mp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_MP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d188L shp_mp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lap_h_mode                  :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_mp_lap_v_mode                  :3 ;	// 6:4
}PE_M17C0_SHP_MP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d18cL shp_mp_ctrl_07                             
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
}PE_M17C0_SHP_MP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d190L shp_mp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_gb_x2                       :8 ,	// 7:0
	reg_mp_gb_y2                       :8 ,	// 15:8
	reg_mp_gb_y3                       :8 ;	// 23:16
}PE_M17C0_SHP_MP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d194L shp_mp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_x_l0                   :8 ,	// 7:0
	reg_mp_lum1_x_l1                   :8 ,	// 15:8
	reg_mp_lum1_x_h0                   :8 ,	// 23:16
	reg_mp_lum1_x_h1                   :8 ;	// 31:24
}PE_M17C0_SHP_MP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d198L shp_mp_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum1_y0                     :8 ,	// 7:0
	reg_mp_lum1_y1                     :8 ,	// 15:8
	reg_mp_lum1_y2                     :8 ,	// 23:16
	reg_mp_lum2_x_l0                   :8 ;	// 31:24
}PE_M17C0_SHP_MP_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d19cL shp_mp_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_x_l1                   :8 ,	// 7:0
	reg_mp_lum2_x_h0                   :8 ,	// 15:8
	reg_mp_lum2_x_h1                   :8 ,	// 23:16
	reg_mp_lum2_y0                     :8 ;	// 31:24
}PE_M17C0_SHP_MP_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d1a0L shp_mp_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mp_lum2_y1                     :8 ,	// 7:0
	reg_mp_lum2_y2                     :8 ;	// 15:8
}PE_M17C0_SHP_MP_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d1b0L shp_coring_ctrl_00                             
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
}PE_M17C0_SHP_CORING_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d1b4L shp_coring_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_beta_mul             :8 ,	// 7:0
	reg_fd_detail_alpha_mul            :8 ,	// 15:8
	reg_fd_edge_beta_mul               :8 ,	// 23:16
	reg_fd_edge_alpha_mul              :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d1b8L shp_coring_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_edge_y0               :8 ,	// 7:0
	reg_fd_a_lut_edge_x0               :8 ,	// 15:8
	reg_fd_a_lut_edge_y1               :8 ,	// 23:16
	reg_fd_a_lut_edge_x1               :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d1bcL shp_coring_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_a_lut_detail_y0             :8 ,	// 7:0
	reg_fd_a_lut_detail_x0             :8 ,	// 15:8
	reg_fd_a_lut_detail_y1             :8 ,	// 23:16
	reg_fd_a_lut_detail_x1             :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c0L shp_coring_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_edge_y0               :8 ,	// 7:0
	reg_fd_t_lut_edge_x0               :8 ,	// 15:8
	reg_fd_t_lut_edge_y1               :8 ,	// 23:16
	reg_fd_t_lut_edge_x1               :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c4L shp_coring_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_t_lut_detail_y0             :8 ,	// 7:0
	reg_fd_t_lut_detail_x0             :8 ,	// 15:8
	reg_fd_t_lut_detail_y1             :8 ,	// 23:16
	reg_fd_t_lut_detail_x1             :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d1c8L shp_coring_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_edge_minmax_y0              :8 ,	// 7:0
	reg_fd_edge_minmax_x0              :8 ,	// 15:8
	reg_fd_edge_minmax_y1              :8 ,	// 23:16
	reg_fd_edge_minmax_x1              :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d1ccL shp_coring_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_detail_minmax_y0            :8 ,	// 7:0
	reg_fd_detail_minmax_x0            :8 ,	// 15:8
	reg_fd_detail_minmax_y1            :8 ,	// 23:16
	reg_fd_detail_minmax_x1            :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d1d0L shp_coring_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mpc_coring_mode                :2 ,	// 1:0
	reg_spc_coring_mode                :2 ,	// 3:2
	reg_mpc_coring_en                  :1 ,	// 4:4
	reg_spc_coring_en                  :1 ,	// 5:5
	reg_ptic_coring_en                 :1 ,	// 6:6
	reg_ptic_coring_mode               :2 ,	// 8:7
	reg_tgenc_coring_en                :1 ,	// 9:9
	reg_tgenc_coring_mode              :2 ,	// 11:10
	reserved01                         :4 ,	// reserved
	reg_fd_mul_base_t                  :8 ,	// 23:16
	reg_fd_mul_base_e                  :8 ;	// 31:24
}PE_M17C0_SHP_CORING_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d1d4L shp_coring_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mpc_gain_e_b                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_mpc_gain_e_w                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_mpc_gain_t_b                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_mpc_gain_t_w                   :7 ;	// 30:24
}PE_M17C0_SHP_CORING_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d200L shp_pti_ctrl_00                             
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
}PE_M17C0_SHP_PTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d204L shp_pti_ctrl_01                             
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
}PE_M17C0_SHP_PTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d208L shp_sti_ctrl_00                             
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
}PE_M17C0_SHP_STI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d20cL shp_sti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_STI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d210L shp_psp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_edge_th                    :8 ;	// 7:0
}PE_M17C0_SHP_PSP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d220L shp_dj_ctrl_00                             
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
	reserved02                         :1 ,	// reserved
	reg_dj_direction_type_mode         :1 ,	// 7:7
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_M17C0_SHP_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d224L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_M17C0_SHP_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d228L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_M17C0_SHP_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d22cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_M17C0_SHP_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d260L shp_sqm_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_outmux_debugmap_enable     :4 ,	// 3:0
	reg_sqm_iir                        :4 ,	// 7:4
	reg_sqm_i_score                    :8 ,	// 15:8
	reg_sqm_v_score                    :8 ,	// 23:16
	reg_sqm_l_score                    :8 ;	// 31:24
}PE_M17C0_SHP_SQM_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d264L shp_sqm_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_v_limit                    :8 ,	// 7:0
	reg_sqm_l_limit                    :8 ,	// 15:8
	reg_sqm_score_threshold            :8 ,	// 23:16
	reg_sqm_flat_threshold             :8 ;	// 31:24
}PE_M17C0_SHP_SQM_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d268L shp_sqm_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pip_win_x0                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_sqm_pip_win_y0                 :11;	// 26:16
}PE_M17C0_SHP_SQM_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d26cL shp_sqm_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pip_win_x1                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	reg_sqm_pip_win_y1                 :11;	// 26:16
}PE_M17C0_SHP_SQM_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d270L shp_sqm_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_charcter_delta_limit       :8 ,	// 7:0
	reg_sqm_boundary_width             :8 ,	// 15:8
	reg_sqm_video_height               :8 ;	// 23:16
}PE_M17C0_SHP_SQM_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d274L shp_sqm_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_pc_threshold               :8 ,	// 7:0
	reg_sqm_pc_delta_limit             :8 ,	// 15:8
	reg_sqm_pc_pixel_minimal_limit     :8 ;	// 23:16
}PE_M17C0_SHP_SQM_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d280L shp_bbd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_en                         :1 ,	// 0:0
	reg_bbd_hys_mode                   :5 ,	// 5:1
	reg_bbd_op_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_bbd_cnt_th                     :8 ,	// 15:8
	reg_bbd_diff_th                    :8 ;	// 23:16
}PE_M17C0_SHP_BBD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d284L shp_bbd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_x0                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_bbd_y0                         :12;	// 27:16
}PE_M17C0_SHP_BBD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d288L shp_bbd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_x1                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_bbd_y1                         :12;	// 27:16
}PE_M17C0_SHP_BBD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d2c8L shp_contrast_ctrl_00                             
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
}PE_M17C0_SHP_CONTRAST_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d2ccL shp_contrast_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gb_y2                       :8 ,	// 7:0
	reg_lc_gb_x2                       :8 ,	// 15:8
	reg_lc_gb_y1                       :8 ,	// 23:16
	reg_lc_gb_x1                       :8 ;	// 31:24
}PE_M17C0_SHP_CONTRAST_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d0L shp_contrast_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_lc_lap_weight                  :8 ,	// 15:8
	reg_lc_gb_y3                       :8 ,	// 23:16
	reg_lc_gb_x3                       :8 ;	// 31:24
}PE_M17C0_SHP_CONTRAST_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d4L shp_contrast_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_gain_e_b                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lc_gain_e_w                    :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_lc_gain_t_b                    :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_lc_gain_t_w                    :7 ;	// 30:24
}PE_M17C0_SHP_CONTRAST_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d2d8L shp_contrast_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lc_coring_en                   :1 ,	// 0:0
	reg_lc_apl_iir_en                  :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_lc_coring_mode                 :2 ,	// 5:4
	reserved02                         :10,	// reserved
	reg_lc_apl_iir_gain                :8 ;	// 23:16
}PE_M17C0_SHP_CONTRAST_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d2dcL shp_mnr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_gain_e_en               :1 ,	// 0:0
	reg_fd_mnr_gain_t_en               :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_fd_mnr_s1_h_expand             :2 ;	// 5:4
}PE_M17C0_SHP_MNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d2e0L shp_mnr_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_mnr_s1_mmd_min              :8 ,	// 7:0
	reg_fd_mnr_s2_ratio_min            :8 ,	// 15:8
	reg_fd_mnr_s2_ratio_max            :8 ,	// 23:16
	reg_fd_mnr_s2_mmd_min              :8 ;	// 31:24
}PE_M17C0_SHP_MNR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d2e4L shp_mnr_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fd_gain_x0                     :8 ,	// 7:0
	reg_fd_gain_x1                     :8 ,	// 15:8
	reg_fd_gain_y0                     :8 ,	// 23:16
	reg_fd_gain_y1                     :8 ;	// 31:24
}PE_M17C0_SHP_MNR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d300L shp_core0_win1_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core0_win0_en          :1 ,	// 0:0
	reg_win_esf_core0_win1_en          :1 ,	// 1:1
	reg_win_esf_core0_win01_en         :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_esf_core0_win_outside      :1 ,	// 6:6
	reg_win_esf_core0_win_en           :1 ,	// 7:7
	reg_win_esf_core0_bdr_alpha        :5 ,	// 12:8
	reg_win_esf_core0_bdr_wid          :2 ,	// 14:13
	reg_win_esf_core0_bdr_en           :1 ,	// 15:15
	reg_win_esf_core0_cr5              :5 ,	// 20:16
	reg_win_esf_core0_cb5              :5 ,	// 25:21
	reg_win_esf_core0_yy6              :6 ;	// 31:26
}PE_M17C0_SHP_CORE0_WIN1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d304L shp_core0_win1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core0_win_w0_x0        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core0_win_w0_y0        :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d308L shp_core0_win1_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core0_win_w0_x1        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core0_win_w0_y1        :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d30cL shp_core0_win1_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core0_win_w1_x0        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core0_win_w1_y0        :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d310L shp_core0_win1_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core0_win_w1_x1        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core0_win_w1_y1        :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d314L shp_core1_win1_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core1_win0_en          :1 ,	// 0:0
	reg_win_esf_core1_win1_en          :1 ,	// 1:1
	reg_win_esf_core1_win01_en         :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_esf_core1_win_outside      :1 ,	// 6:6
	reg_win_esf_core1_win_en           :1 ,	// 7:7
	reg_win_esf_core1_bdr_alpha        :5 ,	// 12:8
	reg_win_esf_core1_bdr_wid          :2 ,	// 14:13
	reg_win_esf_core1_bdr_en           :1 ,	// 15:15
	reg_win_esf_core1_cr5              :5 ,	// 20:16
	reg_win_esf_core1_cb5              :5 ,	// 25:21
	reg_win_esf_core1_yy6              :6 ;	// 31:26
}PE_M17C0_SHP_CORE1_WIN1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d318L shp_core1_win1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core1_win_w0_x0        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core1_win_w0_y0        :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d31cL shp_core1_win1_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core1_win_w0_x1        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core1_win_w0_y1        :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d320L shp_core1_win1_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core1_win_w1_x0        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core1_win_w1_y0        :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d324L shp_core1_win1_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_esf_core1_win_w1_x1        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_esf_core1_win_w1_y1        :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d350L shp_core0_win2_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core0_win0_en           :1 ,	// 0:0
	reg_win_dp_core0_win1_en           :1 ,	// 1:1
	reg_win_dp_core0_win01_en          :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_core0_win_outside       :1 ,	// 6:6
	reg_win_dp_core0_win_en            :1 ,	// 7:7
	reg_win_dp_core0_bdr_alpha         :5 ,	// 12:8
	reg_win_dp_core0_bdr_wid           :2 ,	// 14:13
	reg_win_dp_core0_bdr_en            :1 ,	// 15:15
	reg_win_dp_core0_cr5               :5 ,	// 20:16
	reg_win_dp_core0_cb5               :5 ,	// 25:21
	reg_win_dp_core0_yy6               :6 ;	// 31:26
}PE_M17C0_SHP_CORE0_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d354L shp_core0_win2_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core0_win_w0_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core0_win_w0_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d358L shp_core0_win2_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core0_win_w0_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core0_win_w0_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d35cL shp_core0_win2_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core0_win_w1_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core0_win_w1_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d360L shp_core0_win2_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core0_win_w1_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core0_win_w1_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d364L shp_core1_win2_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core1_win0_en           :1 ,	// 0:0
	reg_win_dp_core1_win1_en           :1 ,	// 1:1
	reg_win_dp_core1_win01_en          :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dp_core1_win_outside       :1 ,	// 6:6
	reg_win_dp_core1_win_en            :1 ,	// 7:7
	reg_win_dp_core1_bdr_alpha         :5 ,	// 12:8
	reg_win_dp_core1_bdr_wid           :2 ,	// 14:13
	reg_win_dp_core1_bdr_en            :1 ,	// 15:15
	reg_win_dp_core1_cr5               :5 ,	// 20:16
	reg_win_dp_core1_cb5               :5 ,	// 25:21
	reg_win_dp_core1_yy6               :6 ;	// 31:26
}PE_M17C0_SHP_CORE1_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d368L shp_core1_win2_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core1_win_w0_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core1_win_w0_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d36cL shp_core1_win2_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core1_win_w0_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core1_win_w0_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d370L shp_core1_win2_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core1_win_w1_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core1_win_w1_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d374L shp_core1_win2_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dp_core1_win_w1_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dp_core1_win_w1_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a0L shp_core0_win3_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core0_win0_en           :1 ,	// 0:0
	reg_win_dj_core0_win1_en           :1 ,	// 1:1
	reg_win_dj_core0_win01_en          :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_core0_win_outside       :1 ,	// 6:6
	reg_win_dj_core0_win_en            :1 ,	// 7:7
	reg_win_dj_core0_bdr_alpha         :5 ,	// 12:8
	reg_win_dj_core0_bdr_wid           :2 ,	// 14:13
	reg_win_dj_core0_bdr_en            :1 ,	// 15:15
	reg_win_dj_core0_cr5               :5 ,	// 20:16
	reg_win_dj_core0_cb5               :5 ,	// 25:21
	reg_win_dj_core0_yy6               :6 ;	// 31:26
}PE_M17C0_SHP_CORE0_WIN3_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a4L shp_core0_win3_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core0_win_w0_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core0_win_w0_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN3_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3a8L shp_core0_win3_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core0_win_w0_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core0_win_w0_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN3_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d3acL shp_core0_win3_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core0_win_w1_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core0_win_w1_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN3_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d3b0L shp_core0_win3_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core0_win_w1_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core0_win_w1_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE0_WIN3_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d3b4L shp_core1_win3_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core1_win0_en           :1 ,	// 0:0
	reg_win_dj_core1_win1_en           :1 ,	// 1:1
	reg_win_dj_core1_win01_en          :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_dj_core1_win_outside       :1 ,	// 6:6
	reg_win_dj_core1_win_en            :1 ,	// 7:7
	reg_win_dj_core1_bdr_alpha         :5 ,	// 12:8
	reg_win_dj_core1_bdr_wid           :2 ,	// 14:13
	reg_win_dj_core1_bdr_en            :1 ,	// 15:15
	reg_win_dj_core1_cr5               :5 ,	// 20:16
	reg_win_dj_core1_cb5               :5 ,	// 25:21
	reg_win_dj_core1_yy6               :6 ;	// 31:26
}PE_M17C0_SHP_CORE1_WIN3_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3b8L shp_core1_win3_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core1_win_w0_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core1_win_w0_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN3_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3bcL shp_core1_win3_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core1_win_w0_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core1_win_w0_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN3_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d3c0L shp_core1_win3_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core1_win_w1_x0         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core1_win_w1_y0         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN3_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d3c4L shp_core1_win3_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_core1_win_w1_x1         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_core1_win_w1_y1         :12;	// 27:16
}PE_M17C0_SHP_CORE1_WIN3_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f0L shp_debug_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_enable_debug_mode     :1 ,	// 0:0
	reg_dbg_disp_status_enable         :1 ,	// 1:1
	reg_dbg_disp_debug_mode            :1 ,	// 2:2
	reg_dbg_disp_show_dce_blur         :1 ,	// 3:3
	reserved01                         :5 ,	// reserved
	reg_dbg_disp_show_sqm2             :1 ,	// 9:9
	reg_dbg_disp_sqm2_debug_image      :4 ,	// 13:10
	reserved02                         :1 ,	// reserved
	reg_dbg_disp_show_bbd              :2 ,	// 16:15
	reg_dbg_disp_bbd_line_width        :3 ,	// 19:17
	reg_dbg_disp_show_apl              :1 ;	// 20:20
}PE_M17C0_SHP_DEBUG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f4L shp_debug_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_yc_debug_en           :1 ,	// 0:0
	reg_dbg_disp_force_yy_enable       :1 ,	// 1:1
	reg_dbg_disp_force_cb_enable       :1 ,	// 2:2
	reg_dbg_disp_force_cr_enable       :1 ,	// 3:3
	reg_dbg_disp_yc_debug_mode_sel     :3 ;	// 6:4
}PE_M17C0_SHP_DEBUG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d3f8L shp_debug_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_disp_force_yy              :10,	// 9:0
	reg_dbg_disp_force_cb              :10,	// 19:10
	reg_dbg_disp_force_cr              :10;	// 29:20
}PE_M17C0_SHP_DEBUG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d400L shp_chroma_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_color_region_en            :1 ,	// 0:0
	reg_color_region_debug_en          :1 ,	// 1:1
	reserved01                         :2 ,	// reserved
	reg_chr_protection_en              :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_chr_compensation_en            :1 ;	// 8:8
}PE_M17C0_SHP_CHROMA_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d404L shp_chroma_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_y_y0                    :8 ,	// 7:0
	reg_chr_r0_y_x0                    :8 ,	// 15:8
	reg_chr_r0_y_y1                    :8 ,	// 23:16
	reg_chr_r0_y_x1                    :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d408L shp_chroma_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_y_y2                    :8 ,	// 7:0
	reg_chr_r0_y_x2                    :8 ,	// 15:8
	reg_chr_r0_y_y3                    :8 ,	// 23:16
	reg_chr_r0_y_x3                    :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d40cL shp_chroma_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_cb_y0                   :8 ,	// 7:0
	reg_chr_r0_cb_x0                   :8 ,	// 15:8
	reg_chr_r0_cb_y1                   :8 ,	// 23:16
	reg_chr_r0_cb_x1                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d410L shp_chroma_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_cb_y2                   :8 ,	// 7:0
	reg_chr_r0_cb_x2                   :8 ,	// 15:8
	reg_chr_r0_cb_y3                   :8 ,	// 23:16
	reg_chr_r0_cb_x3                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d414L shp_chroma_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_cr_y0                   :8 ,	// 7:0
	reg_chr_r0_cr_x0                   :8 ,	// 15:8
	reg_chr_r0_cr_y1                   :8 ,	// 23:16
	reg_chr_r0_cr_x1                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d418L shp_chroma_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r0_cr_y2                   :8 ,	// 7:0
	reg_chr_r0_cr_x2                   :8 ,	// 15:8
	reg_chr_r0_cr_y3                   :8 ,	// 23:16
	reg_chr_r0_cr_x3                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d41cL shp_chroma_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_y_y0                    :8 ,	// 7:0
	reg_chr_r1_y_x0                    :8 ,	// 15:8
	reg_chr_r1_y_y1                    :8 ,	// 23:16
	reg_chr_r1_y_x1                    :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d420L shp_chroma_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_y_y2                    :8 ,	// 7:0
	reg_chr_r1_y_x2                    :8 ,	// 15:8
	reg_chr_r1_y_y3                    :8 ,	// 23:16
	reg_chr_r1_y_x3                    :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d424L shp_chroma_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_cb_y0                   :8 ,	// 7:0
	reg_chr_r1_cb_x0                   :8 ,	// 15:8
	reg_chr_r1_cb_y1                   :8 ,	// 23:16
	reg_chr_r1_cb_x1                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d428L shp_chroma_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_cb_y2                   :8 ,	// 7:0
	reg_chr_r1_cb_x2                   :8 ,	// 15:8
	reg_chr_r1_cb_y3                   :8 ,	// 23:16
	reg_chr_r1_cb_x3                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d42cL shp_chroma_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_cr_y0                   :8 ,	// 7:0
	reg_chr_r1_cr_x0                   :8 ,	// 15:8
	reg_chr_r1_cr_y1                   :8 ,	// 23:16
	reg_chr_r1_cr_x1                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d430L shp_chroma_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_cr_y2                   :8 ,	// 7:0
	reg_chr_r1_cr_x2                   :8 ,	// 15:8
	reg_chr_r1_cr_y3                   :8 ,	// 23:16
	reg_chr_r1_cr_x3                   :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d434L shp_chroma_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_r1_gain                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_chr_r0_gain                    :8 ;	// 23:16
}PE_M17C0_SHP_CHROMA_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc900d438L shp_chroma_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chr_comp_y0                    :8 ,	// 7:0
	reg_chr_comp_x0                    :8 ,	// 15:8
	reg_chr_comp_y1                    :8 ,	// 23:16
	reg_chr_comp_x1                    :8 ;	// 31:24
}PE_M17C0_SHP_CHROMA_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc900d440L shp_motion_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_adaptive_en             :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_debug_en           :1 ;	// 4:4
}PE_M17C0_SHP_MOTION_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d444L shp_motion_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_lut_a_y0                :8 ,	// 7:0
	reg_motion_lut_a_x0                :8 ,	// 15:8
	reg_motion_lut_a_y1                :8 ,	// 23:16
	reg_motion_lut_a_x1                :8 ;	// 31:24
}PE_M17C0_SHP_MOTION_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d448L shp_motion_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_lut_a_y2                :8 ,	// 7:0
	reg_motion_lut_a_x2                :8 ,	// 15:8
	reg_motion_lut_a_y3                :8 ,	// 23:16
	reg_motion_lut_a_x3                :8 ;	// 31:24
}PE_M17C0_SHP_MOTION_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d44cL shp_motion_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_lut_t_y0                :8 ,	// 7:0
	reg_motion_lut_t_x0                :8 ,	// 15:8
	reg_motion_lut_t_y1                :8 ,	// 23:16
	reg_motion_lut_t_x1                :8 ;	// 31:24
}PE_M17C0_SHP_MOTION_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d450L shp_motion_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_lut_t_y2                :8 ,	// 7:0
	reg_motion_lut_t_x2                :8 ,	// 15:8
	reg_motion_lut_t_y3                :8 ,	// 23:16
	reg_motion_lut_t_x3                :8 ;	// 31:24
}PE_M17C0_SHP_MOTION_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d500L motion_gain_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_pic_rptr_man            :2 ,	// 1:0
	reserved01                         :1 ,	// reserved
	reg_motion_pic_rptr_man_en         :1 ,	// 3:3
	reg_motion_pic_wptr_man            :2 ,	// 5:4
	reserved02                         :1 ,	// reserved
	reg_motion_pic_wptr_man_en         :1 ,	// 7:7
	reg_motion_pic_data_man            :2 ,	// 9:8
	reg_motion_pic_rptr_on             :1 ,	// 10:10
	reg_motion_pic_wptr_on             :1 ,	// 11:11
	reg_motion_pic_wd_man              :4 ,	// 15:12
	reg_motion_pic_wd_man_on           :1 ,	// 16:16
	reg_motion_pic_rd_lsb_man          :2 ,	// 18:17
	reg_motion_ro_buf_wrcnt            :10,	// 28:19
	reg_motion_ro_buf_wrsel            :1 ;	// 29:29
}PE_M17C0_MOTION_GAIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d504L motion_gain_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_in_hoffset              :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_in_voffset              :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d508L motion_gain_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_in_hactive              :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_in_vactive              :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d50cL motion_gain_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_in_hsize                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_in_vsize                :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d510L motion_gain_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_out_pic_width           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_out_pic_height          :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d514L motion_gain_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_phase_off_h             :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_motion_phase_off_v             :6 ,	// 13:8
	reserved02                         :17,	// reserved
	reg_motion_sampling_mode           :1 ;	// 31:31
}PE_M17C0_MOTION_GAIN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d518L motion_gain_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_numerator_h             :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_numerator_v             :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d51cL motion_gain_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_denominator_h           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_denominator_v           :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d520L motion_gain_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_win0_en                 :1 ,	// 0:0
	reg_motion_win1_en                 :1 ,	// 1:1
	reg_motion_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_motion_win_outside             :1 ,	// 6:6
	reg_motion_win_en                  :1 ,	// 7:7
	reg_motion_bdr_alpha               :5 ,	// 12:8
	reg_motion_bdr_wid                 :2 ,	// 14:13
	reg_motion_bdr_en                  :1 ,	// 15:15
	reg_motion_cr5                     :5 ,	// 20:16
	reg_motion_cb5                     :5 ,	// 25:21
	reg_motion_yy6                     :6 ;	// 31:26
}PE_M17C0_MOTION_GAIN_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900d524L motion_gain_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_motion_win_w0_y0               :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900d528L motion_gain_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_motion_win_w0_y1               :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc900d52cL motion_gain_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_out_hoffset        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_out_voffset        :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc900d530L motion_gain_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_out_hactive        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_motion_gain_out_vactive        :12;	// 27:16
}PE_M17C0_MOTION_GAIN_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc900d540L shp_cti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cti_en                         :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_cti_filter_tap_size            :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	reg_cti_gain                       :8 ;	// 15:8
}PE_M17C0_SHP_CTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d544L shp_cti_ctrl_01                             
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
}PE_M17C0_SHP_CTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d548L shp_cti_ctrl_02                             
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
}PE_M17C0_SHP_CTI_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d560L shp_frc_blur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_en                    :1 ,	// 0:0
	reg_frc_blur_debug_en              :1 ;	// 1:1
}PE_M17C0_SHP_FRC_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d564L shp_frc_blur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_wgt_sm_cnt_th0        :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th1        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th2        :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th3        :6 ;	// 29:24
}PE_M17C0_SHP_FRC_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d568L shp_frc_blur_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_wgt_sm_cnt_th4        :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th5        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th6        :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_frc_blur_wgt_sm_cnt_th7        :6 ;	// 29:24
}PE_M17C0_SHP_FRC_BLUR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d56cL shp_frc_blur_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_coef_x0               :4 ,	// 3:0
	reg_frc_blur_coef_x1               :4 ,	// 7:4
	reg_frc_blur_coef_x2               :4 ,	// 11:8
	reg_frc_blur_coef_x3               :4 ,	// 15:12
	reg_frc_blur_coef_x4               :4 ;	// 19:16
}PE_M17C0_SHP_FRC_BLUR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d570L shp_frc_blur_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_blur_coef_y0               :4 ,	// 3:0
	reg_frc_blur_coef_y1               :4 ,	// 7:4
	reg_frc_blur_coef_y2               :4 ;	// 11:8
}PE_M17C0_SHP_FRC_BLUR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d600L shp_top_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_TOP_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d604L shp_top_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_M17C0_SHP_TOP_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d608L shp_top_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_M17C0_SHP_TOP_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d60cL shp_top_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_vert_cnt               :12;	// 11:0
}PE_M17C0_SHP_TOP_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d610L shp_top_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_M17C0_SHP_TOP_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d614L shp_top_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_M17C0_SHP_TOP_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d618L shp_top_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_TOP_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d61cL shp_top_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_TOP_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d620L shp_core0_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_vcnt                 :12,	// 11:0
	reg_mon_core0_va_pe1_in            :1 ,	// 12:12
	reg_mon_core0_va_pe1_out           :1 ,	// 13:13
	reserved01                         :2 ,	// reserved
	reg_mon_core0_vcnt2                :12;	// 27:16
}PE_M17C0_SHP_CORE0_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d624L shp_core0_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_in_vert_cnt          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core0_in_hori_cnt          :12;	// 27:16
}PE_M17C0_SHP_CORE0_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d628L shp_core0_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_out_vert_cnt         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core0_out_hori_cnt         :12;	// 27:16
}PE_M17C0_SHP_CORE0_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d62cL shp_core0_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_fin_vert_cnt         :12;	// 11:0
}PE_M17C0_SHP_CORE0_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d630L shp_core0_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_i_sucfail;	// 31:0
}PE_M17C0_SHP_CORE0_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d634L shp_core0_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_o_sucfail;	// 31:0
}PE_M17C0_SHP_CORE0_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d638L shp_core0_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d63cL shp_core0_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d640L shp_core1_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_vcnt                 :12,	// 11:0
	reg_mon_core1_va_pe1_in            :1 ,	// 12:12
	reg_mon_core1_va_pe1_out           :1 ,	// 13:13
	reserved01                         :2 ,	// reserved
	reg_mon_core1_vcnt2                :12;	// 27:16
}PE_M17C0_SHP_CORE1_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d644L shp_core1_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_in_vert_cnt          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core1_in_hori_cnt          :12;	// 27:16
}PE_M17C0_SHP_CORE1_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d648L shp_core1_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_out_vert_cnt         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core1_out_hori_cnt         :12;	// 27:16
}PE_M17C0_SHP_CORE1_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d64cL shp_core1_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_fin_vert_cnt         :12;	// 11:0
}PE_M17C0_SHP_CORE1_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d650L shp_core1_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_i_sucfail;	// 31:0
}PE_M17C0_SHP_CORE1_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc900d654L shp_core1_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_o_sucfail;	// 31:0
}PE_M17C0_SHP_CORE1_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc900d658L shp_core1_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900d65cL shp_core1_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a0L shp_core0_coring_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_CORING_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a4L shp_core0_coring_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_CORING_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d6a8L shp_core0_coring_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_CORING_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d6acL shp_core0_coring_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE0_CORING_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b0L shp_core1_coring_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_CORING_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b4L shp_core1_coring_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_CORING_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d6b8L shp_core1_coring_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_CORING_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d6bcL shp_core1_coring_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_CORE1_CORING_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc900d6e0L shp_core0_sqm_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_sqm_blur_pixel       :10,	// 9:0
	reg_mon_core0_sqm_sharp_pixel      :10,	// 19:10
	reg_mon_core0_sqm_output           :10,	// 29:20
	reg_mon_core0_sqm_pc_detect        :1 ;	// 30:30
}PE_M17C0_SHP_CORE0_SQM_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6e4L shp_core1_sqm_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_sqm_blur_pixel       :10,	// 9:0
	reg_mon_core1_sqm_sharp_pixel      :10,	// 19:10
	reg_mon_core1_sqm_output           :10,	// 29:20
	reg_mon_core1_sqm_pc_detect        :1 ;	// 30:30
}PE_M17C0_SHP_CORE1_SQM_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6f0L shp_core0_bbd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_bbd_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core0_bbd_y0               :12;	// 27:16
}PE_M17C0_SHP_CORE0_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6f4L shp_core0_bbd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core0_bbd_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core0_bbd_y1               :12;	// 27:16
}PE_M17C0_SHP_CORE0_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d6f8L shp_core1_bbd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_bbd_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core1_bbd_y0               :12;	// 27:16
}PE_M17C0_SHP_CORE1_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d6fcL shp_core1_bbd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_core1_bbd_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_core1_bbd_y1               :12;	// 27:16
}PE_M17C0_SHP_CORE1_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d710L motion_gain_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_motion_buf_rptr            :2 ,	// 1:0
	reg_mon_motion_buf_wptr_d          :2 ,	// 3:2
	reg_mon_motion_core_wd_ptr         :2 ,	// 5:4
	reg_mon_motion_buf_rcnt            :10,	// 15:6
	reg_mon_motion_buf_wcnt            :10,	// 25:16
	reg_mon_motion_buf_wre_cnt         :4 ;	// 29:26
}PE_M17C0_MOTION_GAIN_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d714L motion_gain_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_motion_out_v_line          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_motion_in_v_line           :12;	// 27:16
}PE_M17C0_MOTION_GAIN_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d7e0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_read_cont                      :2 ,	//1:0
	dnr_decont                         :1 ,  //2:2
	drc_write_cont                     :2 ,  //4:3
	reserved                           :3 ,  //7:5
	reg_pre_norm                       :8 ,	//15:8
	reg_cur_norm                       :8 ,	//23:16
	reg_pre_sc    	                   :8 ;	//31:24
}PE_M17C0_SHP_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900d7e4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cur_sc 	                       : 8,  // 7: 0  
	reg_ui_gain_w                      : 8,  // 15:8
	reg_ui_gain_b                      : 8,  // 23:16
	reg_vy_mode 	                   : 8;  // 31:24
}PE_M17C0_SHP_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900d7e8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_buf_num                        :1 ,	//0:0
	reserved                           :31;  // 31: 1     reserved
}PE_M17C0_SHP_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900d7ecL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_SHP_FSW_CTRL_03_T;


/*-----------------------------------------------------------------------------
                             0xc900b200L psp_top_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	width                              :13,	// 12:0
	reserved01                         :3 ,	// reserved
	height                             :12;	// 27:16
}PE_M17C0_PSP_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900b26cL reg_perspect_gain_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	iir_en                             :1 ,	// 0 
	edge_flag_show_mode                :1 ,	// 1 
	reg_force_mode                     :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	sc_flag                            :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_set_h_gain_max                 :1 ,	// 8 
	reg_set_v_gain_max                 :1 ,	// 9 
	reserved03                         :2 ,	// reserved
	reg_valid_sel                      :1 ,	// 12
	reserved04                         :1 ,	// reserved
	reg_reverse_mode                   :1 ,	// 14
	reserved05                         :1 ,	// reserved
	reg_force_gain                     :8 ,	// 23:16
	iir_gain                           :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_GAIN_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900b270L reg_perspect_lut_x_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_x_12              :8 ,	// 7:0
	reg_position_lut_x_13              :8 ,	// 15:8
	reg_position_lut_x_14              :8 ,	// 23:16
	reg_position_lut_x_15              :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_X_0_T;
/*-----------------------------------------------------------------------------
                             0xc900b274L reg_perspect_lut_x_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_x_8               :8 ,	// 7:0
	reg_position_lut_x_9               :8 ,	// 15:8
	reg_position_lut_x_10              :8 ,	// 23:16
	reg_position_lut_x_11              :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_X_1_T;
/*-----------------------------------------------------------------------------
                             0xc900b278L reg_perspect_lut_x_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_x_4               :8 ,	// 7:0
	reg_position_lut_x_5               :8 ,	// 15:8
	reg_position_lut_x_6               :8 ,	// 23:16
	reg_position_lut_x_7               :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_X_2_T;
/*-----------------------------------------------------------------------------
                             0xc900b27cL reg_perspect_lut_x_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_x_0               :8 ,	// 7:0
	reg_position_lut_x_1               :8 ,	// 15:8
	reg_position_lut_x_2               :8 ,	// 23:16
	reg_position_lut_x_3               :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_X_3_T;
/*-----------------------------------------------------------------------------
                             0xc900b280L reg_perspect_lut_y_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_y_12              :8 ,	// 7:0
	reg_position_lut_y_13              :8 ,	// 15:8
	reg_position_lut_y_14              :8 ,	// 23:16
	reg_position_lut_y_15              :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_Y_0_T;
/*-----------------------------------------------------------------------------
                             0xc900b284L reg_perspect_lut_y_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_y_8               :8 ,	// 7:0
	reg_position_lut_y_9               :8 ,	// 15:8
	reg_position_lut_y_10              :8 ,	// 23:16
	reg_position_lut_y_11              :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_Y_1_T;
/*-----------------------------------------------------------------------------
                             0xc900b288L reg_perspect_lut_y_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_y_4               :8 ,	// 7:0
	reg_position_lut_y_5               :8 ,	// 15:8
	reg_position_lut_y_6               :8 ,	// 23:16
	reg_position_lut_y_7               :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_Y_2_T;
/*-----------------------------------------------------------------------------
                             0xc900b28cL reg_perspect_lut_y_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_position_lut_y_0               :8 ,	// 7:0
	reg_position_lut_y_1               :8 ,	// 15:8
	reg_position_lut_y_2               :8 ,	// 23:16
	reg_position_lut_y_3               :8 ;	// 31:24
}PE_M17C0_REG_PERSPECT_LUT_Y_3_T;
/*-----------------------------------------------------------------------------
                             0xc900b290L reg_psp_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_en                         :1 ,	// 0 
	reg_psp_debug_en                   :1 ,	// 1 
	reg_chroma_protection_en           :1 ,	// 2 
	reserved01                         :28,	// reserved
	reg_cg_disable                     :1 ;	// 31
}PE_M17C0_REG_PSP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900b294L reg_psp_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_map_master_gain            :8 ;	// 7:0
}PE_M17C0_REG_PSP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900b298L reg_psp_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cb_offset_gain                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_cr_offset_gain                 :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900b29cL reg_psp_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_REG_PSP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900b2a0L reg_psp_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_M17C0_REG_PSP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc900b2a4L reg_psp_status_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	total_edge_sum                     :25;	// 24:0
}PE_M17C0_REG_PSP_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc900b300L reg_psp_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y0                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x0                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc900b304L reg_psp_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y1                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x1                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900b308L reg_psp_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y2                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x2                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900b30cL reg_psp_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y3                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x3                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc900b310L reg_psp_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y4                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x4                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc900b314L reg_psp_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y5                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x5                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900b318L reg_psp_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y6                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x6                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900b31cL reg_psp_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y7                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x7                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900b320L reg_psp_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y8                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x8                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900b324L reg_psp_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y9                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x9                     :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900b328L reg_psp_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y10                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x10                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc900b32cL reg_psp_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y11                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x11                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc900b330L reg_psp_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y12                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x12                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900b334L reg_psp_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y13                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x13                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900b338L reg_psp_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y14                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x14                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc900b33cL reg_psp_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y15                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x15                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc900b340L reg_psp_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_lut_y16                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_psp_lut_x16                    :10;	// 25:16
}PE_M17C0_REG_PSP_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc900b400L reg_psp_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_en                         :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_win01_enable                   :1 ,	// 4 
	reg_win0_enable                    :1 ,	// 5 
	reg_win1_enable                    :1 ,	// 6 
	reg_win_size_acq                   :1 ,	// 7 
	reg_win_enable                     :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	reg_win_outside                    :1 ;	// 16
}PE_M17C0_REG_PSP_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc900b404L reg_psp_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_x0                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w0_y0                      :12;	// 27:16
}PE_M17C0_REG_PSP_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc900b408L reg_psp_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w0_x1                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w0_y1                      :12;	// 27:16
}PE_M17C0_REG_PSP_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc900b40cL reg_psp_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_x0                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w1_y0                      :12;	// 27:16
}PE_M17C0_REG_PSP_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc900b410L reg_psp_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_w1_x1                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_w1_y1                      :12;	// 27:16
}PE_M17C0_REG_PSP_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc900b4fcL update_pin                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	write                              :1 ,	// 0:0
	read                               :1 ;	// 1:1
}PE_M17C0_UPDATE_PIN_T;

typedef struct
{ 
	PE_M17C0_SHP_CORE_CTRL_00_T                       shp_core_ctrl_00;	//0x0000
	PE_M17C0_SHP_CORE_CTRL_01_T                       shp_core_ctrl_01;	//0x0004
	PE_M17C0_SHP_CORE0_CTRL_01_T                      shp_core0_ctrl_01;	//0x0008
	PE_M17C0_SHP_CORE1_CTRL_01_T                      shp_core1_ctrl_01;	//0x000C
	UINT32                                            reserved4[2];	//0x10-0x14
	PE_M17C0_SHP_CORE_CTRL_02_T                       shp_core_ctrl_02;	//0x0018
	PE_M17C0_SHP_CORE_CTRL_03_T                       shp_core_ctrl_03;	//0x001C
	UINT32                                            reserved6[8];	//0x20-0x3c
	PE_M17C0_SPLIT_CTRL00_T                           split_ctrl00;	//0x0040
	PE_M17C0_SPLIT_CTRL01_T                           split_ctrl01;	//0x0044
	PE_M17C0_SPLIT_CTRL02_T                           split_ctrl02;	//0x0048
	UINT32                                            reserved9[2];	//0x4c-0x50
	PE_M17C0_MERG_CTRL_T                              merg_ctrl;	//0x0054
	PE_M17C0_OUT_HGOS_CTRL_T                          out_hgos_ctrl;	//0x0058
	PE_M17C0_OUT_VGOS_CTRL_T                          out_vgos_ctrl;	//0x005C
	PE_M17C0_DISP_SYNC_DLY_ADDR00_T                   disp_sync_dly_addr00;	//0x0060
	PE_M17C0_DISP_SYNC_DLY_ADDR01_T                   disp_sync_dly_addr01;	//0x0064
	PE_M17C0_DISP_SYNC_DLY_ADDR02_T                   disp_sync_dly_addr02;	//0x0068
	PE_M17C0_DISP_SYNC_DLY_ADDR03_T                   disp_sync_dly_addr03;	//0x006C
	PE_M17C0_DISP_SYNC_DLY_ADDR04_T                   disp_sync_dly_addr04;	//0x0070
	PE_M17C0_DISP_SYNC_DLY_ADDR05_T                   disp_sync_dly_addr05;	//0x0074
	PE_M17C0_DISP_SYNC_DLY_ADDR06_T                   disp_sync_dly_addr06;	//0x0078
	PE_M17C0_DISP_SYNC_DLY_ADDR07_T                   disp_sync_dly_addr07;	//0x007C
	PE_M17C0_DISP_SYNC_DLY_ADDR08_T                   disp_sync_dly_addr08;	//0x0080
	PE_M17C0_DISP_SYNC_DLY_ADDR09_T                   disp_sync_dly_addr09;	//0x0084
	PE_M17C0_DISP_SYNC_DLY_ADDR0A_T                   disp_sync_dly_addr0a;	//0x0088
	UINT32                                            reserved23[5];	//0x8c-0x9c
	PE_M17C0_SHP_ESF_CTRL_00_T                        shp_esf_ctrl_00;	//0x00A0
	PE_M17C0_SHP_ESF_CTRL_01_T                        shp_esf_ctrl_01;	//0x00A4
	PE_M17C0_SHP_ESF_CTRL_02_T                        shp_esf_ctrl_02;	//0x00A8
	UINT32                                            reserved26;	//0xac
	PE_M17C0_SHP_DERH_CTRL_00_T                       shp_derh_ctrl_00;	//0x00B0
	PE_M17C0_SHP_DERH_CTRL_01_T                       shp_derh_ctrl_01;	//0x00B4
	PE_M17C0_SHP_DERH_CTRL_02_T                       shp_derh_ctrl_02;	//0x00B8
	PE_M17C0_SHP_DERH_CTRL_03_T                       shp_derh_ctrl_03;	//0x00BC
	PE_M17C0_SHP_DERH_CTRL_04_T                       shp_derh_ctrl_04;	//0x00C0
	PE_M17C0_SHP_DERH_CTRL_05_T                       shp_derh_ctrl_05;	//0x00C4
	PE_M17C0_SHP_DERH_CTRL_06_T                       shp_derh_ctrl_06;	//0x00C8
	PE_M17C0_SHP_DERH_CTRL_07_T                       shp_derh_ctrl_07;	//0x00CC
	PE_M17C0_SHP_DERH_CTRL_08_T                       shp_derh_ctrl_08;	//0x00D0
	PE_M17C0_SHP_DERH_CTRL_09_T                       shp_derh_ctrl_09;	//0x00D4
	PE_M17C0_SHP_DERH_CTRL_0A_T                       shp_derh_ctrl_0a;	//0x00D8
	PE_M17C0_SHP_DERH_CTRL_0B_T                       shp_derh_ctrl_0b;	//0x00DC
	PE_M17C0_SHP_DERH_CTRL_0C_T                       shp_derh_ctrl_0c;	//0x00E0
	UINT32                                            reserved39[3];	//0xe4-0xec
	PE_M17C0_SHP_DERV_CTRL_0_T                        shp_derv_ctrl_0;	//0x00F0
	PE_M17C0_SHP_DERV_CTRL_1_T                        shp_derv_ctrl_1;	//0x00F4
	PE_M17C0_SHP_DERV_CTRL_2_T                        shp_derv_ctrl_2;	//0x00F8
	PE_M17C0_SHP_DERV_CTRL_3_T                        shp_derv_ctrl_3;	//0x00FC
	UINT32                                            reserved43[4];	//0x100-0x10c
	PE_M17C0_SHP_DP_CTRL_00_T                         shp_dp_ctrl_00;	//0x0110
	PE_M17C0_SHP_DP_CTRL_01_T                         shp_dp_ctrl_01;	//0x0114
	PE_M17C0_SHP_DP_CTRL_02_T                         shp_dp_ctrl_02;	//0x0118
	PE_M17C0_SHP_DP_CTRL_03_T                         shp_dp_ctrl_03;	//0x011C
	PE_M17C0_SHP_DP_CTRL_04_T                         shp_dp_ctrl_04;	//0x0120
	PE_M17C0_SHP_DP_CTRL_05_T                         shp_dp_ctrl_05;	//0x0124
	PE_M17C0_SHP_DP_CTRL_06_T                         shp_dp_ctrl_06;	//0x0128
	PE_M17C0_SHP_DP_CTRL_07_T                         shp_dp_ctrl_07;	//0x012C
	PE_M17C0_SHP_SP_CTRL_00_T                         shp_sp_ctrl_00;	//0x0130
	PE_M17C0_SHP_SP_CTRL_01_T                         shp_sp_ctrl_01;	//0x0134
	PE_M17C0_SHP_SP_CTRL_02_T                         shp_sp_ctrl_02;	//0x0138
	PE_M17C0_SHP_SP_CTRL_03_T                         shp_sp_ctrl_03;	//0x013C
	PE_M17C0_SHP_SP_CTRL_04_T                         shp_sp_ctrl_04;	//0x0140
	PE_M17C0_SHP_SP_CTRL_05_T                         shp_sp_ctrl_05;	//0x0144
	PE_M17C0_SHP_SP_CTRL_06_T                         shp_sp_ctrl_06;	//0x0148
	PE_M17C0_SHP_SP_CTRL_07_T                         shp_sp_ctrl_07;	//0x014C
	PE_M17C0_SHP_SP_CTRL_08_T                         shp_sp_ctrl_08;	//0x0150
	PE_M17C0_SHP_SP_CTRL_09_T                         shp_sp_ctrl_09;	//0x0154
	PE_M17C0_SHP_SP_CTRL_0A_T                         shp_sp_ctrl_0a;	//0x0158
	PE_M17C0_SHP_SP_CTRL_0B_T                         shp_sp_ctrl_0b;	//0x015C
	PE_M17C0_SHP_SP_CTRL_0C_T                         shp_sp_ctrl_0c;	//0x0160
	UINT32                                            reserved64[3];	//0x164-0x16c
	PE_M17C0_SHP_MP_CTRL_00_T                         shp_mp_ctrl_00;	//0x0170
	PE_M17C0_SHP_MP_CTRL_01_T                         shp_mp_ctrl_01;	//0x0174
	PE_M17C0_SHP_MP_CTRL_02_T                         shp_mp_ctrl_02;	//0x0178
	PE_M17C0_SHP_MP_CTRL_03_T                         shp_mp_ctrl_03;	//0x017C
	PE_M17C0_SHP_MP_CTRL_04_T                         shp_mp_ctrl_04;	//0x0180
	PE_M17C0_SHP_MP_CTRL_05_T                         shp_mp_ctrl_05;	//0x0184
	PE_M17C0_SHP_MP_CTRL_06_T                         shp_mp_ctrl_06;	//0x0188
	PE_M17C0_SHP_MP_CTRL_07_T                         shp_mp_ctrl_07;	//0x018C
	PE_M17C0_SHP_MP_CTRL_08_T                         shp_mp_ctrl_08;	//0x0190
	PE_M17C0_SHP_MP_CTRL_09_T                         shp_mp_ctrl_09;	//0x0194
	PE_M17C0_SHP_MP_CTRL_0A_T                         shp_mp_ctrl_0a;	//0x0198
	PE_M17C0_SHP_MP_CTRL_0B_T                         shp_mp_ctrl_0b;	//0x019C
	PE_M17C0_SHP_MP_CTRL_0C_T                         shp_mp_ctrl_0c;	//0x01A0
	UINT32                                            reserved77[3];	//0x1a4-0x1ac
	PE_M17C0_SHP_CORING_CTRL_00_T                     shp_coring_ctrl_00;	//0x01B0
	PE_M17C0_SHP_CORING_CTRL_01_T                     shp_coring_ctrl_01;	//0x01B4
	PE_M17C0_SHP_CORING_CTRL_02_T                     shp_coring_ctrl_02;	//0x01B8
	PE_M17C0_SHP_CORING_CTRL_03_T                     shp_coring_ctrl_03;	//0x01BC
	PE_M17C0_SHP_CORING_CTRL_04_T                     shp_coring_ctrl_04;	//0x01C0
	PE_M17C0_SHP_CORING_CTRL_05_T                     shp_coring_ctrl_05;	//0x01C4
	PE_M17C0_SHP_CORING_CTRL_06_T                     shp_coring_ctrl_06;	//0x01C8
	PE_M17C0_SHP_CORING_CTRL_07_T                     shp_coring_ctrl_07;	//0x01CC
	PE_M17C0_SHP_CORING_CTRL_08_T                     shp_coring_ctrl_08;	//0x01D0
	PE_M17C0_SHP_CORING_CTRL_09_T                     shp_coring_ctrl_09;	//0x01D4
	UINT32                                            reserved87[10];	//0x1d8-0x1fc
	PE_M17C0_SHP_PTI_CTRL_00_T                        shp_pti_ctrl_00;	//0x0200
	PE_M17C0_SHP_PTI_CTRL_01_T                        shp_pti_ctrl_01;	//0x0204
	PE_M17C0_SHP_STI_CTRL_00_T                        shp_sti_ctrl_00;	//0x0208
	PE_M17C0_SHP_STI_CTRL_01_T                        shp_sti_ctrl_01;	//0x020C
	PE_M17C0_SHP_PSP_CTRL_00_T                        shp_psp_ctrl_00;	//0x0210
	UINT32                                            reserved92[3];	//0x214-0x21c
	PE_M17C0_SHP_DJ_CTRL_00_T                         shp_dj_ctrl_00;	//0x0220
	PE_M17C0_SHP_DJ_CTRL_01_T                         shp_dj_ctrl_01;	//0x0224
	PE_M17C0_SHP_DJ_CTRL_02_T                         shp_dj_ctrl_02;	//0x0228
	PE_M17C0_SHP_DJ_CTRL_03_T                         shp_dj_ctrl_03;	//0x022C
	UINT32                                            reserved96[12];	//0x230-0x25c
	PE_M17C0_SHP_SQM_CTRL_00_T                        shp_sqm_ctrl_00;	//0x0260
	PE_M17C0_SHP_SQM_CTRL_01_T                        shp_sqm_ctrl_01;	//0x0264
	PE_M17C0_SHP_SQM_CTRL_02_T                        shp_sqm_ctrl_02;	//0x0268
	PE_M17C0_SHP_SQM_CTRL_03_T                        shp_sqm_ctrl_03;	//0x026C
	PE_M17C0_SHP_SQM_CTRL_04_T                        shp_sqm_ctrl_04;	//0x0270
	PE_M17C0_SHP_SQM_CTRL_05_T                        shp_sqm_ctrl_05;	//0x0274
	UINT32                                            reserved102;	//0x278
	UINT32                                            reserved00;	//0x027C-0x027C
	PE_M17C0_SHP_BBD_CTRL_00_T                        shp_bbd_ctrl_00;	//0x0280
	PE_M17C0_SHP_BBD_CTRL_01_T                        shp_bbd_ctrl_01;	//0x0284
	PE_M17C0_SHP_BBD_CTRL_02_T                        shp_bbd_ctrl_02;	//0x0288
	UINT32                                            reserved106[15];	//0x28c-0x2c4
	PE_M17C0_SHP_CONTRAST_CTRL_00_T                   shp_contrast_ctrl_00;	//0x02C8
	PE_M17C0_SHP_CONTRAST_CTRL_01_T                   shp_contrast_ctrl_01;	//0x02CC
	PE_M17C0_SHP_CONTRAST_CTRL_02_T                   shp_contrast_ctrl_02;	//0x02D0
	PE_M17C0_SHP_CONTRAST_CTRL_03_T                   shp_contrast_ctrl_03;	//0x02D4
	PE_M17C0_SHP_CONTRAST_CTRL_04_T                   shp_contrast_ctrl_04;	//0x02D8
	PE_M17C0_SHP_MNR_CTRL_00_T                        shp_mnr_ctrl_00;	//0x02DC
	PE_M17C0_SHP_MNR_CTRL_01_T                        shp_mnr_ctrl_01;	//0x02E0
	PE_M17C0_SHP_MNR_CTRL_02_T                        shp_mnr_ctrl_02;	//0x02E4
	UINT32                                            reserved114[6];	//0x2e8-0x2fc
	PE_M17C0_SHP_CORE0_WIN1_CTRL_00_T                 shp_core0_win1_ctrl_00;	//0x0300
	PE_M17C0_SHP_CORE0_WIN1_CTRL_01_T                 shp_core0_win1_ctrl_01;	//0x0304
	PE_M17C0_SHP_CORE0_WIN1_CTRL_02_T                 shp_core0_win1_ctrl_02;	//0x0308
	PE_M17C0_SHP_CORE0_WIN1_CTRL_03_T                 shp_core0_win1_ctrl_03;	//0x030C
	PE_M17C0_SHP_CORE0_WIN1_CTRL_04_T                 shp_core0_win1_ctrl_04;	//0x0310
	PE_M17C0_SHP_CORE1_WIN1_CTRL_00_T                 shp_core1_win1_ctrl_00;	//0x0314
	PE_M17C0_SHP_CORE1_WIN1_CTRL_01_T                 shp_core1_win1_ctrl_01;	//0x0318
	PE_M17C0_SHP_CORE1_WIN1_CTRL_02_T                 shp_core1_win1_ctrl_02;	//0x031C
	PE_M17C0_SHP_CORE1_WIN1_CTRL_03_T                 shp_core1_win1_ctrl_03;	//0x0320
	PE_M17C0_SHP_CORE1_WIN1_CTRL_04_T                 shp_core1_win1_ctrl_04;	//0x0324
	UINT32                                            reserved124[10];	//0x328-0x34c
	PE_M17C0_SHP_CORE0_WIN2_CTRL_00_T                 shp_core0_win2_ctrl_00;	//0x0350
	PE_M17C0_SHP_CORE0_WIN2_CTRL_01_T                 shp_core0_win2_ctrl_01;	//0x0354
	PE_M17C0_SHP_CORE0_WIN2_CTRL_02_T                 shp_core0_win2_ctrl_02;	//0x0358
	PE_M17C0_SHP_CORE0_WIN2_CTRL_03_T                 shp_core0_win2_ctrl_03;	//0x035C
	PE_M17C0_SHP_CORE0_WIN2_CTRL_04_T                 shp_core0_win2_ctrl_04;	//0x0360
	PE_M17C0_SHP_CORE1_WIN2_CTRL_00_T                 shp_core1_win2_ctrl_00;	//0x0364
	PE_M17C0_SHP_CORE1_WIN2_CTRL_01_T                 shp_core1_win2_ctrl_01;	//0x0368
	PE_M17C0_SHP_CORE1_WIN2_CTRL_02_T                 shp_core1_win2_ctrl_02;	//0x036C
	PE_M17C0_SHP_CORE1_WIN2_CTRL_03_T                 shp_core1_win2_ctrl_03;	//0x0370
	PE_M17C0_SHP_CORE1_WIN2_CTRL_04_T                 shp_core1_win2_ctrl_04;	//0x0374
	UINT32                                            reserved134[10];	//0x378-0x39c
	PE_M17C0_SHP_CORE0_WIN3_CTRL_00_T                 shp_core0_win3_ctrl_00;	//0x03A0
	PE_M17C0_SHP_CORE0_WIN3_CTRL_01_T                 shp_core0_win3_ctrl_01;	//0x03A4
	PE_M17C0_SHP_CORE0_WIN3_CTRL_02_T                 shp_core0_win3_ctrl_02;	//0x03A8
	PE_M17C0_SHP_CORE0_WIN3_CTRL_03_T                 shp_core0_win3_ctrl_03;	//0x03AC
	PE_M17C0_SHP_CORE0_WIN3_CTRL_04_T                 shp_core0_win3_ctrl_04;	//0x03B0
	PE_M17C0_SHP_CORE1_WIN3_CTRL_00_T                 shp_core1_win3_ctrl_00;	//0x03B4
	PE_M17C0_SHP_CORE1_WIN3_CTRL_01_T                 shp_core1_win3_ctrl_01;	//0x03B8
	PE_M17C0_SHP_CORE1_WIN3_CTRL_02_T                 shp_core1_win3_ctrl_02;	//0x03BC
	PE_M17C0_SHP_CORE1_WIN3_CTRL_03_T                 shp_core1_win3_ctrl_03;	//0x03C0
	PE_M17C0_SHP_CORE1_WIN3_CTRL_04_T                 shp_core1_win3_ctrl_04;	//0x03C4
	UINT32                                            reserved144[10];	//0x3c8-0x3ec
	PE_M17C0_SHP_DEBUG_CTRL_00_T                      shp_debug_ctrl_00;	//0x03F0
	PE_M17C0_SHP_DEBUG_CTRL_01_T                      shp_debug_ctrl_01;	//0x03F4
	PE_M17C0_SHP_DEBUG_CTRL_02_T                      shp_debug_ctrl_02;	//0x03F8
	UINT32                                            reserved147;	//0x3fc
	PE_M17C0_SHP_CHROMA_CTRL_00_T                     shp_chroma_ctrl_00;	//0x0400
	PE_M17C0_SHP_CHROMA_CTRL_01_T                     shp_chroma_ctrl_01;	//0x0404
	PE_M17C0_SHP_CHROMA_CTRL_02_T                     shp_chroma_ctrl_02;	//0x0408
	PE_M17C0_SHP_CHROMA_CTRL_03_T                     shp_chroma_ctrl_03;	//0x040C
	PE_M17C0_SHP_CHROMA_CTRL_04_T                     shp_chroma_ctrl_04;	//0x0410
	PE_M17C0_SHP_CHROMA_CTRL_05_T                     shp_chroma_ctrl_05;	//0x0414
	PE_M17C0_SHP_CHROMA_CTRL_06_T                     shp_chroma_ctrl_06;	//0x0418
	PE_M17C0_SHP_CHROMA_CTRL_07_T                     shp_chroma_ctrl_07;	//0x041C
	PE_M17C0_SHP_CHROMA_CTRL_08_T                     shp_chroma_ctrl_08;	//0x0420
	PE_M17C0_SHP_CHROMA_CTRL_09_T                     shp_chroma_ctrl_09;	//0x0424
	PE_M17C0_SHP_CHROMA_CTRL_0A_T                     shp_chroma_ctrl_0a;	//0x0428
	PE_M17C0_SHP_CHROMA_CTRL_0B_T                     shp_chroma_ctrl_0b;	//0x042C
	PE_M17C0_SHP_CHROMA_CTRL_0C_T                     shp_chroma_ctrl_0c;	//0x0430
	PE_M17C0_SHP_CHROMA_CTRL_0D_T                     shp_chroma_ctrl_0d;	//0x0434
	PE_M17C0_SHP_CHROMA_CTRL_0E_T                     shp_chroma_ctrl_0e;	//0x0438
	UINT32                                            reserved162;	//0x43c
	PE_M17C0_SHP_MOTION_CTRL_00_T                     shp_motion_ctrl_00;	//0x0440
	PE_M17C0_SHP_MOTION_CTRL_01_T                     shp_motion_ctrl_01;	//0x0444
	PE_M17C0_SHP_MOTION_CTRL_02_T                     shp_motion_ctrl_02;	//0x0448
	PE_M17C0_SHP_MOTION_CTRL_03_T                     shp_motion_ctrl_03;	//0x044C
	PE_M17C0_SHP_MOTION_CTRL_04_T                     shp_motion_ctrl_04;	//0x0450
	UINT32                                            reserved167[43];	//0x454-0x4fc
	PE_M17C0_MOTION_GAIN_CTRL_00_T                    motion_gain_ctrl_00;	//0x0500
	PE_M17C0_MOTION_GAIN_CTRL_01_T                    motion_gain_ctrl_01;	//0x0504
	PE_M17C0_MOTION_GAIN_CTRL_02_T                    motion_gain_ctrl_02;	//0x0508
	PE_M17C0_MOTION_GAIN_CTRL_03_T                    motion_gain_ctrl_03;	//0x050C
	PE_M17C0_MOTION_GAIN_CTRL_04_T                    motion_gain_ctrl_04;	//0x0510
	PE_M17C0_MOTION_GAIN_CTRL_05_T                    motion_gain_ctrl_05;	//0x0514
	PE_M17C0_MOTION_GAIN_CTRL_06_T                    motion_gain_ctrl_06;	//0x0518
	PE_M17C0_MOTION_GAIN_CTRL_07_T                    motion_gain_ctrl_07;	//0x051C
	PE_M17C0_MOTION_GAIN_CTRL_08_T                    motion_gain_ctrl_08;	//0x0520
	PE_M17C0_MOTION_GAIN_CTRL_09_T                    motion_gain_ctrl_09;	//0x0524
	PE_M17C0_MOTION_GAIN_CTRL_0A_T                    motion_gain_ctrl_0a;	//0x0528
	PE_M17C0_MOTION_GAIN_CTRL_0B_T                    motion_gain_ctrl_0b;	//0x052C
	PE_M17C0_MOTION_GAIN_CTRL_0C_T                    motion_gain_ctrl_0c;	//0x0530
	UINT32                                            reserved180[3];	//0x534-0x53c
	PE_M17C0_SHP_CTI_CTRL_00_T                        shp_cti_ctrl_00;	//0x0540
	PE_M17C0_SHP_CTI_CTRL_01_T                        shp_cti_ctrl_01;	//0x0544
	PE_M17C0_SHP_CTI_CTRL_02_T                        shp_cti_ctrl_02;	//0x0548
	UINT32                                            reserved183[5];	//0x54c-0x55c
	PE_M17C0_SHP_FRC_BLUR_CTRL_00_T                   shp_frc_blur_ctrl_00;	//0x0560
	PE_M17C0_SHP_FRC_BLUR_CTRL_01_T                   shp_frc_blur_ctrl_01;	//0x0564
	PE_M17C0_SHP_FRC_BLUR_CTRL_02_T                   shp_frc_blur_ctrl_02;	//0x0568
	PE_M17C0_SHP_FRC_BLUR_CTRL_03_T                   shp_frc_blur_ctrl_03;	//0x056C
	PE_M17C0_SHP_FRC_BLUR_CTRL_04_T                   shp_frc_blur_ctrl_04;	//0x0570
	UINT32                                            reserved188[35];	//0x574-0x5fc
	PE_M17C0_SHP_TOP_STAT_00_T                        shp_top_stat_00;	//0x0600
	PE_M17C0_SHP_TOP_STAT_01_T                        shp_top_stat_01;	//0x0604
	PE_M17C0_SHP_TOP_STAT_02_T                        shp_top_stat_02;	//0x0608
	PE_M17C0_SHP_TOP_STAT_03_T                        shp_top_stat_03;	//0x060C
	PE_M17C0_SHP_TOP_STAT_04_T                        shp_top_stat_04;	//0x0610
	PE_M17C0_SHP_TOP_STAT_05_T                        shp_top_stat_05;	//0x0614
	PE_M17C0_SHP_TOP_STAT_06_T                        shp_top_stat_06;	//0x0618
	PE_M17C0_SHP_TOP_STAT_07_T                        shp_top_stat_07;	//0x061C
	PE_M17C0_SHP_CORE0_STAT_00_T                      shp_core0_stat_00;	//0x0620
	PE_M17C0_SHP_CORE0_STAT_01_T                      shp_core0_stat_01;	//0x0624
	PE_M17C0_SHP_CORE0_STAT_02_T                      shp_core0_stat_02;	//0x0628
	PE_M17C0_SHP_CORE0_STAT_03_T                      shp_core0_stat_03;	//0x062C
	PE_M17C0_SHP_CORE0_STAT_04_T                      shp_core0_stat_04;	//0x0630
	PE_M17C0_SHP_CORE0_STAT_05_T                      shp_core0_stat_05;	//0x0634
	PE_M17C0_SHP_CORE0_STAT_06_T                      shp_core0_stat_06;	//0x0638
	PE_M17C0_SHP_CORE0_STAT_07_T                      shp_core0_stat_07;	//0x063C
	PE_M17C0_SHP_CORE1_STAT_00_T                      shp_core1_stat_00;	//0x0640
	PE_M17C0_SHP_CORE1_STAT_01_T                      shp_core1_stat_01;	//0x0644
	PE_M17C0_SHP_CORE1_STAT_02_T                      shp_core1_stat_02;	//0x0648
	PE_M17C0_SHP_CORE1_STAT_03_T                      shp_core1_stat_03;	//0x064C
	PE_M17C0_SHP_CORE1_STAT_04_T                      shp_core1_stat_04;	//0x0650
	PE_M17C0_SHP_CORE1_STAT_05_T                      shp_core1_stat_05;	//0x0654
	PE_M17C0_SHP_CORE1_STAT_06_T                      shp_core1_stat_06;	//0x0658
	PE_M17C0_SHP_CORE1_STAT_07_T                      shp_core1_stat_07;	//0x065C
	UINT32                                            reserved212[16];	//0x660-0x69c
	PE_M17C0_SHP_CORE0_CORING_STAT_00_T               shp_core0_coring_stat_00;	//0x06A0
	PE_M17C0_SHP_CORE0_CORING_STAT_01_T               shp_core0_coring_stat_01;	//0x06A4
	PE_M17C0_SHP_CORE0_CORING_STAT_02_T               shp_core0_coring_stat_02;	//0x06A8
	PE_M17C0_SHP_CORE0_CORING_STAT_03_T               shp_core0_coring_stat_03;	//0x06AC
	PE_M17C0_SHP_CORE1_CORING_STAT_00_T               shp_core1_coring_stat_00;	//0x06B0
	PE_M17C0_SHP_CORE1_CORING_STAT_01_T               shp_core1_coring_stat_01;	//0x06B4
	PE_M17C0_SHP_CORE1_CORING_STAT_02_T               shp_core1_coring_stat_02;	//0x06B8
	PE_M17C0_SHP_CORE1_CORING_STAT_03_T               shp_core1_coring_stat_03;	//0x06BC
	UINT32                                            reserved220[8];	//0x6c0-0x6dc
	PE_M17C0_SHP_CORE0_SQM_STAT_00_T                  shp_core0_sqm_stat_00;	//0x06E0
	PE_M17C0_SHP_CORE1_SQM_STAT_00_T                  shp_core1_sqm_stat_00;	//0x06E4
	UINT32                                            reserved222[2];	//0x6e8-0x6ec
	PE_M17C0_SHP_CORE0_BBD_STAT_00_T                  shp_core0_bbd_stat_00;	//0x06F0
	PE_M17C0_SHP_CORE0_BBD_STAT_01_T                  shp_core0_bbd_stat_01;	//0x06F4
	PE_M17C0_SHP_CORE1_BBD_STAT_00_T                  shp_core1_bbd_stat_00;	//0x06F8
	PE_M17C0_SHP_CORE1_BBD_STAT_01_T                  shp_core1_bbd_stat_01;	//0x06FC
	UINT32                                            reserved226[4];	//0x700-0x70c
	PE_M17C0_MOTION_GAIN_STAT_00_T                    motion_gain_stat_00;	//0x0710
	PE_M17C0_MOTION_GAIN_STAT_01_T                    motion_gain_stat_01;	//0x0714
	UINT32                                            reserved228[50];	//0x718-0x7dc
	PE_M17C0_SHP_FSW_CTRL_00_T                        shp_fsw_ctrl_00;	//0x07E0
	PE_M17C0_SHP_FSW_CTRL_01_T                        shp_fsw_ctrl_01;	//0x07E4
	PE_M17C0_SHP_FSW_CTRL_02_T                        shp_fsw_ctrl_02;	//0x07E8
	PE_M17C0_SHP_FSW_CTRL_03_T                        shp_fsw_ctrl_03;	//0x07EC
}PE_SHP_REG_M17C0_T;

typedef struct
{ 
	PE_M17C0_PSP_TOP_CTRL_00_T                        psp_top_ctrl_00;	//0x0000
	UINT32                                            reserved1[26];	//0x4-0x68
	PE_M17C0_REG_PERSPECT_GAIN_CTRL_0_T               reg_perspect_gain_ctrl_0;	//0x006C
	PE_M17C0_REG_PERSPECT_LUT_X_0_T                   reg_perspect_lut_x_0;	//0x0070
	PE_M17C0_REG_PERSPECT_LUT_X_1_T                   reg_perspect_lut_x_1;	//0x0074
	PE_M17C0_REG_PERSPECT_LUT_X_2_T                   reg_perspect_lut_x_2;	//0x0078
	PE_M17C0_REG_PERSPECT_LUT_X_3_T                   reg_perspect_lut_x_3;	//0x007C
	PE_M17C0_REG_PERSPECT_LUT_Y_0_T                   reg_perspect_lut_y_0;	//0x0080
	PE_M17C0_REG_PERSPECT_LUT_Y_1_T                   reg_perspect_lut_y_1;	//0x0084
	PE_M17C0_REG_PERSPECT_LUT_Y_2_T                   reg_perspect_lut_y_2;	//0x0088
	PE_M17C0_REG_PERSPECT_LUT_Y_3_T                   reg_perspect_lut_y_3;	//0x008C
	PE_M17C0_REG_PSP_CTRL_00_T                        reg_psp_ctrl_00;	//0x0090
	PE_M17C0_REG_PSP_CTRL_01_T                        reg_psp_ctrl_01;	//0x0094
	PE_M17C0_REG_PSP_CTRL_02_T                        reg_psp_ctrl_02;	//0x0098
	PE_M17C0_REG_PSP_CTRL_03_T                        reg_psp_ctrl_03;	//0x009C
	PE_M17C0_REG_PSP_CTRL_04_T                        reg_psp_ctrl_04;	//0x00A0
	PE_M17C0_REG_PSP_STATUS_00_T                      reg_psp_status_00;	//0x00A4
	UINT32                                            reserved16[22];	//0xa8-0xfc
	PE_M17C0_REG_PSP_CTRL_05_T                        reg_psp_ctrl_05;	//0x0100
	PE_M17C0_REG_PSP_CTRL_06_T                        reg_psp_ctrl_06;	//0x0104
	PE_M17C0_REG_PSP_CTRL_07_T                        reg_psp_ctrl_07;	//0x0108
	PE_M17C0_REG_PSP_CTRL_08_T                        reg_psp_ctrl_08;	//0x010C
	PE_M17C0_REG_PSP_CTRL_09_T                        reg_psp_ctrl_09;	//0x0110
	PE_M17C0_REG_PSP_CTRL_10_T                        reg_psp_ctrl_10;	//0x0114
	PE_M17C0_REG_PSP_CTRL_11_T                        reg_psp_ctrl_11;	//0x0118
	PE_M17C0_REG_PSP_CTRL_12_T                        reg_psp_ctrl_12;	//0x011C
	PE_M17C0_REG_PSP_CTRL_13_T                        reg_psp_ctrl_13;	//0x0120
	PE_M17C0_REG_PSP_CTRL_14_T                        reg_psp_ctrl_14;	//0x0124
	PE_M17C0_REG_PSP_CTRL_15_T                        reg_psp_ctrl_15;	//0x0128
	PE_M17C0_REG_PSP_CTRL_16_T                        reg_psp_ctrl_16;	//0x012C
	PE_M17C0_REG_PSP_CTRL_17_T                        reg_psp_ctrl_17;	//0x0130
	PE_M17C0_REG_PSP_CTRL_18_T                        reg_psp_ctrl_18;	//0x0134
	PE_M17C0_REG_PSP_CTRL_19_T                        reg_psp_ctrl_19;	//0x0138
	PE_M17C0_REG_PSP_CTRL_20_T                        reg_psp_ctrl_20;	//0x013C
	PE_M17C0_REG_PSP_CTRL_21_T                        reg_psp_ctrl_21;	//0x0140
	UINT32                                            reserved33[47];	//0x144-0x1fc
	PE_M17C0_REG_PSP_CTRL_22_T                        reg_psp_ctrl_22;	//0x0200
	PE_M17C0_REG_PSP_CTRL_23_T                        reg_psp_ctrl_23;	//0x0204
	PE_M17C0_REG_PSP_CTRL_24_T                        reg_psp_ctrl_24;	//0x0208
	PE_M17C0_REG_PSP_CTRL_25_T                        reg_psp_ctrl_25;	//0x020C
	PE_M17C0_REG_PSP_CTRL_26_T                        reg_psp_ctrl_26;	//0x0210
	UINT32                                            reserved38[58];	//0x214-0x2f8
	PE_M17C0_UPDATE_PIN_T                             update_pin;	//0x02FC
}PE_SHP_PSP_REG_M17C0_T;
#endif