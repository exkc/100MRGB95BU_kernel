#ifndef _PE_OSD_REG_O18A0_H_
#define _PE_OSD_REG_O18A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9011c00L SHP_CORE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_actv_sel                   :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_top_detour                     :1 ,	// 4:4
	reg_top_bypass                     :1 ,	// 5:5
	reserved02                         :10,	// reserved
	reg_top_update_ctrl                :5 ;	// 20:16
}PE_O18_SHP_OSD_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c04L SHP_CORE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_height                     :12;	// 27:16
}PE_O18_SHP_OSD_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c08L SHP_CORE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O18_SHP_OSD_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011c50L SHP_GOS_CTRL_00                             
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
}PE_O18_SHP_OSD_GOS_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c60L SHP_SYNC_DLY_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_vsync                 :16,	// 15:0
	reg_sync_dly_vfp                   :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c64L SHP_SYNC_DLY_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_va                    :16,	// 15:0
	reg_sync_dly_vbp                   :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c68L SHP_SYNC_DLY_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_hsync                 :16,	// 15:0
	reg_sync_dly_hfp                   :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011c6cL SHP_SYNC_DLY_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_ha                    :16,	// 15:0
	reg_sync_dly_hbp                   :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011c70L SHP_SYNC_DLY_CTRL_04                             
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
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011c74L SHP_SYNC_DLY_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_sync_h_dly            :16,	// 15:0
	reg_sync_dly_sync_v_dly            :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011c78L SHP_SYNC_DLY_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_rst_h_value       :16,	// 15:0
	reg_sync_dly_cnt_rst_v_value       :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9011c7cL SHP_SYNC_DLY_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_actv_h_dly       :16,	// 15:0
	reg_sync_dly_auto_actv_v_dly       :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011c80L SHP_SYNC_DLY_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_auto_sync_h_dly       :16,	// 15:0
	reg_sync_dly_auto_sync_v_dly       :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011c84L SHP_SYNC_DLY_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_normal_number         :16;	// 15:0
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011c88L SHP_SYNC_DLY_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sync_dly_cnt_h_rst_position    :16,	// 15:0
	reg_sync_dly_cnt_v_rst_position    :16;	// 31:16
}PE_O18_SHP_OSD_SYNC_DLY_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc9011ca0L SHP_LTI_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_2d_en                      :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_lti_coring_en                  :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lti_2d_gain                    :8 ,	// 15:8
	reg_lti_2d_limit                   :10;	// 25:16
}PE_O18_SHP_OSD_LTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011ca4L SHP_LTI_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_coring_lut_y0              :8 ,	// 7:0
	reg_lti_coring_lut_x0              :8 ,	// 15:8
	reg_lti_coring_lut_y1              :8 ,	// 23:16
	reg_lti_coring_lut_x1              :8 ;	// 31:24
}PE_O18_SHP_OSD_LTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb0L SHP_CORE0_LTI_WIN_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win0_en                :1 ,	// 0:0
	reg_win_lti_win1_en                :1 ,	// 1:1
	reg_win_lti_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_lti_win_outside            :1 ,	// 6:6
	reg_win_lti_win_en                 :1 ,	// 7:7
	reg_win_lti_bdr_alpha              :5 ,	// 12:8
	reg_win_lti_bdr_wid                :2 ,	// 14:13
	reg_win_lti_bdr_en                 :1 ,	// 15:15
	reg_win_lti_cr5                    :5 ,	// 20:16
	reg_win_lti_cb5                    :5 ,	// 25:21
	reg_win_lti_yy6                    :6 ;	// 31:26
}PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb4L SHP_CORE0_LTI_WIN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w0_y0              :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb8L SHP_CORE0_LTI_WIN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w0_y1              :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011cbcL SHP_CORE0_LTI_WIN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w1_y0              :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011cc0L SHP_CORE0_LTI_WIN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w1_y1              :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011cd0L SHP_CORE1_LTI_WIN_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win0_en                :1 ,	// 0:0
	reg_win_lti_win1_en                :1 ,	// 1:1
	reg_win_lti_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_lti_win_outside            :1 ,	// 6:6
	reg_win_lti_win_en                 :1 ,	// 7:7
	reg_win_lti_bdr_alpha              :5 ,	// 12:8
	reg_win_lti_bdr_wid                :2 ,	// 14:13
	reg_win_lti_bdr_en                 :1 ,	// 15:15
	reg_win_lti_cr5                    :5 ,	// 20:16
	reg_win_lti_cb5                    :5 ,	// 25:21
	reg_win_lti_yy6                    :6 ;	// 31:26
}PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011cd4L SHP_CORE1_LTI_WIN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w0_y0              :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011cd8L SHP_CORE1_LTI_WIN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w0_y1              :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011cdcL SHP_CORE1_LTI_WIN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w1_y0              :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011ce0L SHP_CORE1_LTI_WIN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_lti_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_lti_win_w1_y1              :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011d00L SHP_DJ_CTRL_00                             
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
	reserved02                         :2 ,	// reserved
	reg_dj_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_dj_output_mux                  :3 ,	// 18:16
	reserved04                         :1 ,	// reserved
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reserved05                         :1 ,	// reserved
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_O18_SHP_OSD_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d04L SHP_DJ_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_O18_SHP_OSD_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d08L SHP_DJ_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_O18_SHP_OSD_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011d0cL SHP_DJ_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_O18_SHP_OSD_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011d20L SHP_DIR_BLUR_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_O18_SHP_OSD_DIR_BLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d24L SHP_DIR_BLUR_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_O18_SHP_OSD_DIR_BLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d40L SHP_CORE0_DJ_WIN_CTRL_00                             
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
}PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d44L SHP_CORE0_DJ_WIN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d48L SHP_CORE0_DJ_WIN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011d4cL SHP_CORE0_DJ_WIN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011d50L SHP_CORE0_DJ_WIN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011d60L SHP_CORE1_DJ_WIN_CTRL_00                             
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
}PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d64L SHP_CORE1_DJ_WIN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d68L SHP_CORE1_DJ_WIN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011d6cL SHP_CORE1_DJ_WIN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011d70L SHP_CORE1_DJ_WIN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011dc0L SHP_CC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_en                          :1 ;	// 0:0
}PE_O18_SHP_OSD_CC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011dc4L SHP_CC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_contrast_center             :8 ,	// 7:0
	reg_cc_contrast                    :8 ,	// 15:8
	reg_cc_saturation                  :8 ,	// 23:16
	reg_cc_gain                        :8 ;	// 31:24
}PE_O18_SHP_OSD_CC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011e00L SHP_CORE_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011e04L SHP_CORE_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O18_SHP_OSD_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011e08L SHP_CORE_STAT_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O18_SHP_OSD_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011e0cL SHP_CORE_STAT_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O18_SHP_OSD_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011e10L SHP_CORE_STAT_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O18_SHP_OSD_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011e14L SHP_CORE_STAT_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O18_SHP_OSD_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011e18L SHP_CORE_STAT_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_CORE_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc9011e1cL SHP_CORE_STAT_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_CORE_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef0L SHP_FSW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef4L SHP_FSW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef8L SHP_FSW_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011efcL SHP_FSW_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_SHP_OSD_FSW_CTRL_03_T;


typedef struct
{ 
	PE_O18_SHP_OSD_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O18_SHP_OSD_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O18_SHP_OSD_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	UINT32                                            reserved3[17];	//0xc-0x4c
	PE_O18_SHP_OSD_GOS_CTRL_00_T                          shp_gos_ctrl_00;	//0x0050
	UINT32                                            reserved4[3];	//0x54-0x5c
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_00_T                     shp_sync_dly_ctrl_00;	//0x0060
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_01_T                     shp_sync_dly_ctrl_01;	//0x0064
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_02_T                     shp_sync_dly_ctrl_02;	//0x0068
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_03_T                     shp_sync_dly_ctrl_03;	//0x006C
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_04_T                     shp_sync_dly_ctrl_04;	//0x0070
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_05_T                     shp_sync_dly_ctrl_05;	//0x0074
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_06_T                     shp_sync_dly_ctrl_06;	//0x0078
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_07_T                     shp_sync_dly_ctrl_07;	//0x007C
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_08_T                     shp_sync_dly_ctrl_08;	//0x0080
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_09_T                     shp_sync_dly_ctrl_09;	//0x0084
	PE_O18_SHP_OSD_SYNC_DLY_CTRL_0A_T                     shp_sync_dly_ctrl_0a;	//0x0088
	UINT32                                            reserved15[5];	//0x8c-0x9c
	PE_O18_SHP_OSD_LTI_CTRL_00_T                          shp_lti_ctrl_00;	//0x00A0
	PE_O18_SHP_OSD_LTI_CTRL_01_T                          shp_lti_ctrl_01;	//0x00A4
	UINT32                                            reserved17[2];	//0xa8-0xac
	PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_00_T                shp_core0_lti_win_ctrl_00;	//0x00B0
	PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_01_T                shp_core0_lti_win_ctrl_01;	//0x00B4
	PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_02_T                shp_core0_lti_win_ctrl_02;	//0x00B8
	PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_03_T                shp_core0_lti_win_ctrl_03;	//0x00BC
	PE_O18_SHP_OSD_CORE0_LTI_WIN_CTRL_04_T                shp_core0_lti_win_ctrl_04;	//0x00C0
	UINT32                                            reserved22[3];	//0xc4-0xcc
	PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_00_T                shp_core1_lti_win_ctrl_00;	//0x00D0
	PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_01_T                shp_core1_lti_win_ctrl_01;	//0x00D4
	PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_02_T                shp_core1_lti_win_ctrl_02;	//0x00D8
	PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_03_T                shp_core1_lti_win_ctrl_03;	//0x00DC
	PE_O18_SHP_OSD_CORE1_LTI_WIN_CTRL_04_T                shp_core1_lti_win_ctrl_04;	//0x00E0
	UINT32                                            reserved27[7];	//0xe4-0xfc
	PE_O18_SHP_OSD_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0100
	PE_O18_SHP_OSD_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0104
	PE_O18_SHP_OSD_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0108
	PE_O18_SHP_OSD_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x010C
	UINT32                                            reserved31[4];	//0x110-0x11c
	PE_O18_SHP_OSD_DIR_BLUR_CTRL_00_T                     shp_dir_blur_ctrl_00;	//0x0120
	PE_O18_SHP_OSD_DIR_BLUR_CTRL_01_T                     shp_dir_blur_ctrl_01;	//0x0124
	UINT32                                            reserved33[6];	//0x128-0x13c
	PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_00_T                 shp_core0_dj_win_ctrl_00;	//0x0140
	PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_01_T                 shp_core0_dj_win_ctrl_01;	//0x0144
	PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_02_T                 shp_core0_dj_win_ctrl_02;	//0x0148
	PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_03_T                 shp_core0_dj_win_ctrl_03;	//0x014C
	PE_O18_SHP_OSD_CORE0_DJ_WIN_CTRL_04_T                 shp_core0_dj_win_ctrl_04;	//0x0150
	UINT32                                            reserved38[3];	//0x154-0x15c
	PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_00_T                 shp_core1_dj_win_ctrl_00;	//0x0160
	PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_01_T                 shp_core1_dj_win_ctrl_01;	//0x0164
	PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_02_T                 shp_core1_dj_win_ctrl_02;	//0x0168
	PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_03_T                 shp_core1_dj_win_ctrl_03;	//0x016C
	PE_O18_SHP_OSD_CORE1_DJ_WIN_CTRL_04_T                 shp_core1_dj_win_ctrl_04;	//0x0170
	UINT32                                            reserved43[19];	//0x174-0x1bc
	PE_O18_SHP_OSD_CC_CTRL_00_T                           shp_cc_ctrl_00;	//0x01C0
	PE_O18_SHP_OSD_CC_CTRL_01_T                           shp_cc_ctrl_01;	//0x01C4
	UINT32                                            reserved45[14];	//0x1c8-0x1fc
	PE_O18_SHP_OSD_CORE_STAT_00_T                         shp_core_stat_00;	//0x0200
	PE_O18_SHP_OSD_CORE_STAT_01_T                         shp_core_stat_01;	//0x0204
	PE_O18_SHP_OSD_CORE_STAT_02_T                         shp_core_stat_02;	//0x0208
	PE_O18_SHP_OSD_CORE_STAT_03_T                         shp_core_stat_03;	//0x020C
	PE_O18_SHP_OSD_CORE_STAT_04_T                         shp_core_stat_04;	//0x0210
	PE_O18_SHP_OSD_CORE_STAT_05_T                         shp_core_stat_05;	//0x0214
	PE_O18_SHP_OSD_CORE_STAT_06_T                         shp_core_stat_06;	//0x0218
	PE_O18_SHP_OSD_CORE_STAT_07_T                         shp_core_stat_07;	//0x021C
	UINT32                                            reserved53[52];	//0x220-0x2ec
	PE_O18_SHP_OSD_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x02F0
	PE_O18_SHP_OSD_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x02F4
	PE_O18_SHP_OSD_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x02F8
	PE_O18_SHP_OSD_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x02FC
}PE_SHP_OSD_REG_O18_T;
#endif