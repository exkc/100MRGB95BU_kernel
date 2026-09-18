#ifndef _PE_OSD_REG_O20A0_H_
#define _PE_OSD_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

/*-----------------------------------------------------------------------------
                             0xc9011c00L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_detour                     :1 ,	// 4:4
	reg_top_bypass                     :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_protocol_type              :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ,	// 12:12
	reserved04                         :11,	// reserved
	reg_osd_size_sel                   :1 ;	// 24:24
}PE_O20_SHP_OSD0_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c04L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :16,	// 15:0
	reg_top_height                     :16;	// 31:16
}PE_O20_SHP_OSD0_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c08L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O20_SHP_OSD0_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011c0cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_prefetch_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_flush_cnt                  :12;	// 27:16
}PE_O20_SHP_OSD0_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011c10L shp_core_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_update_ctrl                :5 ;	// 4:0
}PE_O20_SHP_OSD0_CORE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011c40L shp_pat_gen_ctrl_00                             
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
}PE_O20_SHP_OSD0_PAT_GEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c60L shp_hti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hti_enable                     :1 ,	// 0:0
	reg_hti_debug_map_en               :1 ,	// 1:1
	reg_hti_mm_tap_size                :2 ,	// 3:2
	reg_hti_avg_tap_size               :2 ,	// 5:4
	reg_hti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_hti_master_gain                :8 ,	// 15:8
	reg_hti_coring_en                  :1 ;	// 16:16
}PE_O20_SHP_OSD0_HTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c64L shp_hti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hti_coring_lut_y0              :8 ,	// 7:0
	reg_hti_coring_lut_x0              :8 ,	// 15:8
	reg_hti_coring_lut_y1              :8 ,	// 23:16
	reg_hti_coring_lut_x1              :8 ;	// 31:24
}PE_O20_SHP_OSD0_HTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c70L shp_hti_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win0_en                :1 ,	// 0:0
	reg_win_hti_win1_en                :1 ,	// 1:1
	reg_win_hti_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_hti_win_outside            :1 ,	// 6:6
	reg_win_hti_win_en                 :1 ,	// 7:7
	reg_win_hti_bdr_alpha              :5 ,	// 12:8
	reg_win_hti_bdr_wid                :2 ,	// 14:13
	reg_win_hti_bdr_en                 :1 ,	// 15:15
	reg_win_hti_cr5                    :5 ,	// 20:16
	reg_win_hti_cb5                    :5 ,	// 25:21
	reg_win_hti_yy6                    :6 ;	// 31:26
}PE_O20_SHP_OSD0_HTI_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c74L shp_hti_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_OSD0_HTI_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c78L shp_hti_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_OSD0_HTI_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011c7cL shp_hti_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_OSD0_HTI_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011c80L shp_hti_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_OSD0_HTI_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011c90L shp_vti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vti_enable                     :1 ,	// 0:0
	reg_vti_debug_map_en               :1 ,	// 1:1
	reg_vti_mm_tap_size                :2 ,	// 3:2
	reg_vti_avg_tap_size               :2 ,	// 5:4
	reg_vti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_vti_master_gain                :8 ;	// 15:8
}PE_O20_SHP_OSD0_VTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011ca0L shp_lti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_2d_en                      :1 ,	// 0:0
	reg_lti_tap_size                   :2 ,	// 2:1
	reserved01                         :1 ,	// reserved
	reg_lti_coring_en                  :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_lti_2d_gain                    :8 ,	// 15:8
	reg_lti_2d_limit                   :10;	// 25:16
}PE_O20_SHP_OSD0_LTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011ca4L shp_lti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_coring_lut_y0              :8 ,	// 7:0
	reg_lti_coring_lut_x0              :8 ,	// 15:8
	reg_lti_coring_lut_y1              :8 ,	// 23:16
	reg_lti_coring_lut_x1              :8 ;	// 31:24
}PE_O20_SHP_OSD0_LTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb0L shp_ti_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_ti_win0_en                 :1 ,	// 0:0
	reg_win_ti_win1_en                 :1 ,	// 1:1
	reg_win_ti_win01_en                :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_ti_win_outside             :1 ,	// 6:6
	reg_win_ti_win_en                  :1 ,	// 7:7
	reg_win_ti_bdr_alpha               :5 ,	// 12:8
	reg_win_ti_bdr_wid                 :2 ,	// 14:13
	reg_win_ti_bdr_en                  :1 ,	// 15:15
	reg_win_ti_cr5                     :5 ,	// 20:16
	reg_win_ti_cb5                     :5 ,	// 25:21
	reg_win_ti_yy6                     :6 ;	// 31:26
}PE_O20_SHP_OSD0_TI_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb4L shp_ti_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_ti_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_ti_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_OSD0_TI_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011cb8L shp_ti_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_ti_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_ti_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_OSD0_TI_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011cbcL shp_ti_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_ti_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_ti_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_OSD0_TI_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011cc0L shp_ti_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_ti_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_ti_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_OSD0_TI_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011cd0L shp_ti_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ti_edf_en                      :1 ,	// 0:0
	reg_ti_hv_filter_en                :1 ,	// 1:1
	reserved01                         :1 ,	// reserved
	reg_ti_edge_adaptive_en            :1 ,	// 3:3
	reg_ti_line_variation_mode         :1 ,	// 4:4
	reg_ti_l_type_protection           :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_ti_count_diff_th               :5 ,	// 12:8
	reserved03                         :3 ,	// reserved
	reg_ti_output_mux                  :3 ,	// 18:16
	reg_ti_buffer_detour_en            :1 ,	// 19:19
	reg_ti_center_blur_mode            :2 ,	// 21:20
	reg_ti_n_avg_mode                  :1 ,	// 22:22
	reg_ti_detour_en                   :1 ,	// 23:23
	reg_ti_line_variation_diff_th      :8 ;	// 31:24
}PE_O20_SHP_OSD0_TI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d00L shp_dj_ctrl_00                             
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
	reg_dj_buffer_detour_en            :1 ,	// 19:19
	reg_dj_center_blur_mode            :2 ,	// 21:20
	reg_dj_n_avg_mode                  :1 ,	// 22:22
	reg_dj_detour_en                   :1 ,	// 23:23
	reg_dj_line_variation_diff_th      :8 ;	// 31:24
}PE_O20_SHP_OSD0_DJ_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d04L shp_dj_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_level_th                    :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dj_n_avg_gain                  :8 ;	// 23:16
}PE_O20_SHP_OSD0_DJ_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d08L shp_dj_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g0_cnt_min                  :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_dj_g0_mul                      :5 ;	// 12:8
}PE_O20_SHP_OSD0_DJ_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011d0cL shp_dj_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dj_g1_protect_min              :8 ,	// 7:0
	reg_dj_g1_mul                      :7 ,	// 14:8
	reserved01                         :1 ,	// reserved
	reg_dj_edge_min                    :8 ,	// 23:16
	reg_dj_edge_mul                    :8 ;	// 31:24
}PE_O20_SHP_OSD0_DJ_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011d20L shp_db_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_detour                :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	reg_dir_blur_buf_detour            :1 ,	// 4:4
	reserved02                         :3 ,	// reserved
	reg_dir_blur_en                    :1 ;	// 8:8
}PE_O20_SHP_OSD0_DB_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d24L shp_db_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dir_blur_base                  :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	reg_dir_blur_gain                  :8 ;	// 23:16
}PE_O20_SHP_OSD0_DB_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d40L shp_dj_win_ctrl_00                             
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
}PE_O20_SHP_OSD0_DJ_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011d44L shp_dj_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y0               :12;	// 27:16
}PE_O20_SHP_OSD0_DJ_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011d48L shp_dj_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w0_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w0_y1               :12;	// 27:16
}PE_O20_SHP_OSD0_DJ_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011d4cL shp_dj_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x0               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y0               :12;	// 27:16
}PE_O20_SHP_OSD0_DJ_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011d50L shp_dj_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_dj_win_w1_x1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_dj_win_w1_y1               :12;	// 27:16
}PE_O20_SHP_OSD0_DJ_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011dc0L shp_cc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_en                          :1 ;	// 0:0
}PE_O20_SHP_OSD0_CC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011dc4L shp_cc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_contrast_center             :8 ,	// 7:0
	reg_cc_contrast                    :8 ,	// 15:8
	reg_cc_saturation                  :8 ,	// 23:16
	reg_cc_gain                        :8 ;	// 31:24
}PE_O20_SHP_OSD0_CC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011e00L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD0_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011e04L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O20_SHP_OSD0_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011e08L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O20_SHP_OSD0_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011e0cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O20_SHP_OSD0_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011e10L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O20_SHP_OSD0_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011e14L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O20_SHP_OSD0_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD0_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD0_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011ef8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD0_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011efcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD0_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011c00L shp_core_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_top_detour                     :1 ,	// 4:4
	reg_top_bypass                     :1 ,	// 5:5
	reserved02                         :2 ,	// reserved
	reg_top_protocol_type              :1 ,	// 8:8
	reserved03                         :3 ,	// reserved
	reg_top_mode_3d                    :1 ,	// 12:12
	reserved04                         :11,	// reserved
	reg_osd_size_sel                   :1 ;	// 24:24
}PE_O20_SHP_OSD1_CORE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011c04L shp_core_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_width                      :16,	// 15:0
	reg_top_height                     :16;	// 31:16
}PE_O20_SHP_OSD1_CORE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011c08L shp_core_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_use_extern_valid           :1 ,	// 0:0
	reg_top_use_blank_preiod_cnt       :1 ,	// 1:1
	reserved01                         :14,	// reserved
	reg_top_manual_blank_cnt           :16;	// 31:16
}PE_O20_SHP_OSD1_CORE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011c0cL shp_core_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_prefetch_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_top_flush_cnt                  :12;	// 27:16
}PE_O20_SHP_OSD1_CORE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011c10L shp_core_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_top_update_ctrl                :5 ;	// 4:0
}PE_O20_SHP_OSD1_CORE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011c40L shp_pat_gen_ctrl_00                             
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
}PE_O20_SHP_OSD1_PAT_GEN_CTRL_00_T;

typedef struct
{
	UINT32
	reg_hti_enable                     :1 ,	// 0:0
	reg_hti_debug_map_en               :1 ,	// 1:1
	reg_hti_mm_tap_size                :2 ,	// 3:2
	reg_hti_avg_tap_size               :2 ,	// 5:4
	reg_hti_ti_mode                    :1 ,	// 6:6
	reserved01                         :1 ,	// reserved
	reg_hti_master_gain                :8 ,	// 15:8
	reg_hti_coring_en                  :1 ;	// 16:16
}PE_O20_SHP_OSD1_HTI_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9012364L shp_hti_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hti_coring_lut_y0              :8 ,	// 7:0
	reg_hti_coring_lut_x0              :8 ,	// 15:8
	reg_hti_coring_lut_y1              :8 ,	// 23:16
	reg_hti_coring_lut_x1              :8 ;	// 31:24
}PE_O20_SHP_OSD1_HTI_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9012370L shp_hti_win_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win0_en                :1 ,	// 0:0
	reg_win_hti_win1_en                :1 ,	// 1:1
	reg_win_hti_win01_en               :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	reg_win_hti_win_outside            :1 ,	// 6:6
	reg_win_hti_win_en                 :1 ,	// 7:7
	reg_win_hti_bdr_alpha              :5 ,	// 12:8
	reg_win_hti_bdr_wid                :2 ,	// 14:13
	reg_win_hti_bdr_en                 :1 ,	// 15:15
	reg_win_hti_cr5                    :5 ,	// 20:16
	reg_win_hti_cb5                    :5 ,	// 25:21
	reg_win_hti_yy6                    :6 ;	// 31:26
}PE_O20_SHP_OSD1_HTI_WIN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9012374L shp_hti_win_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w0_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w0_y0              :12;	// 27:16
}PE_O20_SHP_OSD1_HTI_WIN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9012378L shp_hti_win_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w0_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w0_y1              :12;	// 27:16
}PE_O20_SHP_OSD1_HTI_WIN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901237cL shp_hti_win_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w1_x0              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w1_y0              :12;	// 27:16
}PE_O20_SHP_OSD1_HTI_WIN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9012380L shp_hti_win_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_hti_win_w1_x1              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_win_hti_win_w1_y1              :12;	// 27:16
}PE_O20_SHP_OSD1_HTI_WIN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90124c0L shp_cc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_en                          :1 ;	// 0:0
}PE_O20_SHP_OSD1_CC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90124c4L shp_cc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cc_contrast_center             :8 ,	// 7:0
	reg_cc_contrast                    :8 ,	// 15:8
	reg_cc_saturation                  :8 ,	// 23:16
	reg_cc_gain                        :8 ;	// 31:24
}PE_O20_SHP_OSD1_CC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9012500L shp_core_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD1_CORE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9012504L shp_core_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_in_vert_cnt                :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_in_hori_cnt                :12;	// 27:16
}PE_O20_SHP_OSD1_CORE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9012508L shp_core_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_out_vert_cnt               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_out_hori_cnt               :12;	// 27:16
}PE_O20_SHP_OSD1_CORE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc901250cL shp_core_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_fin_out_vert_cnt           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_mon_fin_in_vert_cnt            :12;	// 27:16
}PE_O20_SHP_OSD1_CORE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9012510L shp_core_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_i_sucfail;	// 31:0
}PE_O20_SHP_OSD1_CORE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9012514L shp_core_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mon_shp_o_sucfail;	// 31:0
}PE_O20_SHP_OSD1_CORE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc90125f0L shp_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD1_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90125f4L shp_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90125f8L shp_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90125fcL shp_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_SHP_OSD1_FSW_CTRL_03_T;


typedef struct
{ 
	PE_O20_SHP_OSD0_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O20_SHP_OSD0_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O20_SHP_OSD0_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	PE_O20_SHP_OSD0_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0x000C
	PE_O20_SHP_OSD0_CORE_CTRL_04_T                         shp_core_ctrl_04;	//0x0010
	UINT32                                            		reserved5[11];	//0x14-0x3c
	PE_O20_SHP_OSD0_PAT_GEN_CTRL_00_T                      shp_pat_gen_ctrl_00;	//0x0040
	UINT32                                            		reserved6[7];	//0x44-0x5c
	PE_O20_SHP_OSD0_HTI_CTRL_00_T                          shp_hti_ctrl_00;	//0x0060
	PE_O20_SHP_OSD0_HTI_CTRL_01_T                          shp_hti_ctrl_01;	//0x0064
	UINT32                                            		reserved8[2];	//0x68-0x6c
	PE_O20_SHP_OSD0_HTI_WIN_CTRL_00_T                      shp_hti_win_ctrl_00;	//0x0070
	PE_O20_SHP_OSD0_HTI_WIN_CTRL_01_T                      shp_hti_win_ctrl_01;	//0x0074
	PE_O20_SHP_OSD0_HTI_WIN_CTRL_02_T                      shp_hti_win_ctrl_02;	//0x0078
	PE_O20_SHP_OSD0_HTI_WIN_CTRL_03_T                      shp_hti_win_ctrl_03;	//0x007C
	PE_O20_SHP_OSD0_HTI_WIN_CTRL_04_T                      shp_hti_win_ctrl_04;	//0x0080
	UINT32                                            		reserved13[3];	//0x84-0x8c
	PE_O20_SHP_OSD0_VTI_CTRL_00_T                          shp_vti_ctrl_00;	//0x0090
	UINT32                                            		reserved14[3];	//0x94-0x9c
	PE_O20_SHP_OSD0_LTI_CTRL_00_T                          shp_lti_ctrl_00;	//0x00A0
	PE_O20_SHP_OSD0_LTI_CTRL_01_T                          shp_lti_ctrl_01;	//0x00A4
	UINT32                                            		reserved16[2];	//0xa8-0xac
	PE_O20_SHP_OSD0_TI_WIN_CTRL_00_T                       shp_ti_win_ctrl_00;	//0x00B0
	PE_O20_SHP_OSD0_TI_WIN_CTRL_01_T                       shp_ti_win_ctrl_01;	//0x00B4
	PE_O20_SHP_OSD0_TI_WIN_CTRL_02_T                       shp_ti_win_ctrl_02;	//0x00B8
	PE_O20_SHP_OSD0_TI_WIN_CTRL_03_T                       shp_ti_win_ctrl_03;	//0x00BC
	PE_O20_SHP_OSD0_TI_WIN_CTRL_04_T                       shp_ti_win_ctrl_04;	//0x00C0
	UINT32                                            		reserved21[3];	//0xc4-0xcc
	PE_O20_SHP_OSD0_TI_CTRL_00_T                           shp_ti_ctrl_00;	//0x00D0
	UINT32                                            		reserved22[11];	//0xd4-0xfc
	PE_O20_SHP_OSD0_DJ_CTRL_00_T                           shp_dj_ctrl_00;	//0x0100
	PE_O20_SHP_OSD0_DJ_CTRL_01_T                           shp_dj_ctrl_01;	//0x0104
	PE_O20_SHP_OSD0_DJ_CTRL_02_T                           shp_dj_ctrl_02;	//0x0108
	PE_O20_SHP_OSD0_DJ_CTRL_03_T                           shp_dj_ctrl_03;	//0x010C
	UINT32                                            		reserved26[4];	//0x110-0x11c
	PE_O20_SHP_OSD0_DB_CTRL_00_T                           shp_db_ctrl_00;	//0x0120
	PE_O20_SHP_OSD0_DB_CTRL_01_T                           shp_db_ctrl_01;	//0x0124
	UINT32                                            		reserved28[6];	//0x128-0x13c
	PE_O20_SHP_OSD0_DJ_WIN_CTRL_00_T                       shp_dj_win_ctrl_00;	//0x0140
	PE_O20_SHP_OSD0_DJ_WIN_CTRL_01_T                       shp_dj_win_ctrl_01;	//0x0144
	PE_O20_SHP_OSD0_DJ_WIN_CTRL_02_T                       shp_dj_win_ctrl_02;	//0x0148
	PE_O20_SHP_OSD0_DJ_WIN_CTRL_03_T                       shp_dj_win_ctrl_03;	//0x014C
	PE_O20_SHP_OSD0_DJ_WIN_CTRL_04_T                       shp_dj_win_ctrl_04;	//0x0150
	UINT32                                            		reserved33[27];	//0x154-0x1bc
	PE_O20_SHP_OSD0_CC_CTRL_00_T                           shp_cc_ctrl_00;	//0x01C0
	PE_O20_SHP_OSD0_CC_CTRL_01_T                           shp_cc_ctrl_01;	//0x01C4
	UINT32                                            		reserved35[14];	//0x1c8-0x1fc
	PE_O20_SHP_OSD0_CORE_STAT_00_T                         shp_core_stat_00;	//0x0200
	PE_O20_SHP_OSD0_CORE_STAT_01_T                         shp_core_stat_01;	//0x0204
	PE_O20_SHP_OSD0_CORE_STAT_02_T                         shp_core_stat_02;	//0x0208
	PE_O20_SHP_OSD0_CORE_STAT_03_T                         shp_core_stat_03;	//0x020C
	PE_O20_SHP_OSD0_CORE_STAT_04_T                         shp_core_stat_04;	//0x0210
	PE_O20_SHP_OSD0_CORE_STAT_05_T                         shp_core_stat_05;	//0x0214
	UINT32                                            		reserved41[54];	//0x218-0x2ec
	PE_O20_SHP_OSD0_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x02F0
	PE_O20_SHP_OSD0_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x02F4
	PE_O20_SHP_OSD0_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x02F8
	PE_O20_SHP_OSD0_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x02FC
}PE_SHP_OSD0_REG_O20_T;


typedef struct
{ 
	PE_O20_SHP_OSD1_CORE_CTRL_00_T                         shp_core_ctrl_00;	//0x0000
	PE_O20_SHP_OSD1_CORE_CTRL_01_T                         shp_core_ctrl_01;	//0x0004
	PE_O20_SHP_OSD1_CORE_CTRL_02_T                         shp_core_ctrl_02;	//0x0008
	PE_O20_SHP_OSD1_CORE_CTRL_03_T                         shp_core_ctrl_03;	//0x000C
	PE_O20_SHP_OSD1_CORE_CTRL_04_T                         shp_core_ctrl_04;	//0x0010
	UINT32                                            		reserved5[11];	//0x14-0x3c
	PE_O20_SHP_OSD1_PAT_GEN_CTRL_00_T                      shp_pat_gen_ctrl_00;	//0x0040
	UINT32                                            		reserved6[7];	//0x44-0x5c
	PE_O20_SHP_OSD1_HTI_CTRL_00_T                          shp_hti_ctrl_00;	//0x0060
	PE_O20_SHP_OSD1_HTI_CTRL_01_T                          shp_hti_ctrl_01;	//0x0064
	UINT32                                            		reserved8[2];	//0x68-0x6c
	PE_O20_SHP_OSD1_HTI_WIN_CTRL_00_T                      shp_hti_win_ctrl_00;	//0x0070
	PE_O20_SHP_OSD1_HTI_WIN_CTRL_01_T                      shp_hti_win_ctrl_01;	//0x0074
	PE_O20_SHP_OSD1_HTI_WIN_CTRL_02_T                      shp_hti_win_ctrl_02;	//0x0078
	PE_O20_SHP_OSD1_HTI_WIN_CTRL_03_T                      shp_hti_win_ctrl_03;	//0x007C
	PE_O20_SHP_OSD1_HTI_WIN_CTRL_04_T                      shp_hti_win_ctrl_04;	//0x0080
	UINT32                                            		reserved13[79];	//0x84-0x1bc
	PE_O20_SHP_OSD1_CC_CTRL_00_T                           shp_cc_ctrl_00;	//0x01C0
	PE_O20_SHP_OSD1_CC_CTRL_01_T                           shp_cc_ctrl_01;	//0x01C4
	UINT32                                            		reserved15[14];	//0x1c8-0x1fc
	PE_O20_SHP_OSD1_CORE_STAT_00_T                         shp_core_stat_00;	//0x0200
	PE_O20_SHP_OSD1_CORE_STAT_01_T                         shp_core_stat_01;	//0x0204
	PE_O20_SHP_OSD1_CORE_STAT_02_T                         shp_core_stat_02;	//0x0208
	PE_O20_SHP_OSD1_CORE_STAT_03_T                         shp_core_stat_03;	//0x020C
	PE_O20_SHP_OSD1_CORE_STAT_04_T                         shp_core_stat_04;	//0x0210
	PE_O20_SHP_OSD1_CORE_STAT_05_T                         shp_core_stat_05;	//0x0214
	UINT32                                            		reserved21[54];	//0x218-0x2ec
	PE_O20_SHP_OSD1_FSW_CTRL_00_T                          shp_fsw_ctrl_00;	//0x02F0
	PE_O20_SHP_OSD1_FSW_CTRL_01_T                          shp_fsw_ctrl_01;	//0x02F4
	PE_O20_SHP_OSD1_FSW_CTRL_02_T                          shp_fsw_ctrl_02;	//0x02F8
	PE_O20_SHP_OSD1_FSW_CTRL_03_T                          shp_fsw_ctrl_03;	//0x02FC
}PE_SHP_OSD1_REG_O20_T;
#endif