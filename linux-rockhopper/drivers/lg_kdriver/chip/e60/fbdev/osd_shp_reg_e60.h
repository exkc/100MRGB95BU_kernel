#ifndef __OSD_SHP_E60_REG_H_
#define __OSD_SHP_E60_REG_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 shp_core_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 4,	//  0: 3 reserved
	reg_top_detour                  : 1,	//     4
	reg_top_bypass                  : 1,	//     5
	                                : 2,	//  6: 7 reserved
	reg_top_protocol_type           : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_top_mode_3d                 : 1,	//    12
	                                :11,	// 13:23 reserved
	reg_osd_size_sel                : 1;	//    24
} SHP_CORE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0004 shp_core_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core_width                  :16,	//  0:15
	reg_core_height                 :16;	// 16:31
} SHP_CORE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0008 shp_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_width                 :16,	//  0:15
	reg_core0_height                :16;	// 16:31
} SHP_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x000c shp_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_width                 :16,	//  0:15
	reg_core1_height                :16;	// 16:31
} SHP_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0018 shp_core_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_use_extern_valid        : 1,	//     0
	reg_top_use_blank_preiod_cnt    : 1,	//     1
	                                :14,	//  2:15 reserved
	reg_top_manual_blank_cnt        :16;	// 16:31
} SHP_CORE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x001c shp_core_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_prefetch_cnt            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_flush_cnt               :12;	// 16:27
} SHP_CORE_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0020 shp_core_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_update_ctrl             : 5;	//  0: 4
} SHP_CORE_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0030 shp_split_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_split_pmode_out             : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_split_pmode_in              : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_split_split_mode            : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	reg_split_sync_mode             : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_split_hsize                 :13;	// 16:28
} SHP_SPLIT_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0034 shp_split_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_split_split_size            :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_split_guardband             :13;	// 16:28
} SHP_SPLIT_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0038 shp_split_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_split_split_ctrl_02         ;   	// 31: 0
} SHP_SPLIT_CTRL_02;

/*-----------------------------------------------------------------------------
	0x003c shp_split_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_split_split_ctrl_03         ;   	// 31: 0
} SHP_SPLIT_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0040 shp_merge_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_pmode_out             : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_merge_pmode_in              : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_merge_split_mode            : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	reg_merge_sync_mode             : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_merge_hsize                 :13;	// 16:28
} SHP_MERGE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0044 shp_merge_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_split_size            :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_merge_guardband             :13;	// 16:28
} SHP_MERGE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0048 shp_merge_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_fifo_th               : 9,	//  0: 8
	                                : 7,	//  9:15 reserved
	reg_merge_fifo_sel              : 3;	// 16:18
} SHP_MERGE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x004c shp_merge_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_ctrl_03               ;   	// 31: 0
} SHP_MERGE_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0050 shp_pat_gen_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pat_en                      : 1,	//     0
	reg_pat_thickness               : 2,	//  1: 2
	                                : 5,	//  3: 7 reserved
	reg_pat_pix_val_yy              : 8,	//  8:15
	reg_pat_pix_val_cb              : 8,	// 16:23
	reg_pat_pix_val_cr              : 8;	// 24:31
} SHP_PAT_GEN_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0060 shp_hti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hti_enable                  : 1,	//     0
	reg_hti_debug_map_en            : 1,	//     1
	reg_hti_mm_tap_size             : 2,	//  2: 3
	reg_hti_avg_tap_size            : 2,	//  4: 5
	reg_hti_ti_mode                 : 1,	//     6
	                                : 1,	//     7 reserved
	reg_hti_master_gain             : 8,	//  8:15
	reg_hti_coring_en               : 1;	//    16
} SHP_HTI_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0064 shp_hti_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hti_coring_lut_y0           : 8,	//  0: 7
	reg_hti_coring_lut_x0           : 8,	//  8:15
	reg_hti_coring_lut_y1           : 8,	// 16:23
	reg_hti_coring_lut_x1           : 8;	// 24:31
} SHP_HTI_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0068 shp_hti_win_core0_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core0_win0_en       : 1,	//     0
	reg_win_hti_core0_win1_en       : 1,	//     1
	reg_win_hti_core0_win01_en      : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_hti_core0_win_outside   : 1,	//     6
	reg_win_hti_core0_win_en        : 1,	//     7
	reg_win_hti_core0_bdr_alpha     : 5,	//  8:12
	reg_win_hti_core0_bdr_wid       : 2,	// 13:14
	reg_win_hti_core0_bdr_en        : 1,	//    15
	reg_win_hti_core0_cr5           : 5,	// 16:20
	reg_win_hti_core0_cb5           : 5,	// 21:25
	reg_win_hti_core0_yy6           : 6;	// 26:31
} SHP_HTI_WIN_CORE0_CTRL_00;

/*-----------------------------------------------------------------------------
	0x006c shp_hti_win_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core0_win_w0_x0     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core0_win_w0_y0     :12;	// 16:27
} SHP_HTI_WIN_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0070 shp_hti_win_core0_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core0_win_w0_x1     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core0_win_w0_y1     :12;	// 16:27
} SHP_HTI_WIN_CORE0_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0074 shp_hti_win_core0_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core0_win_w1_x0     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core0_win_w1_y0     :12;	// 16:27
} SHP_HTI_WIN_CORE0_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0078 shp_hti_win_core0_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core0_win_w1_x1     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core0_win_w1_y1     :12;	// 16:27
} SHP_HTI_WIN_CORE0_CTRL_04;

/*-----------------------------------------------------------------------------
	0x007c shp_hti_win_core1_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core1_win0_en       : 1,	//     0
	reg_win_hti_core1_win1_en       : 1,	//     1
	reg_win_hti_core1_win01_en      : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_hti_core1_win_outside   : 1,	//     6
	reg_win_hti_core1_win_en        : 1,	//     7
	reg_win_hti_core1_bdr_alpha     : 5,	//  8:12
	reg_win_hti_core1_bdr_wid       : 2,	// 13:14
	reg_win_hti_core1_bdr_en        : 1,	//    15
	reg_win_hti_core1_cr5           : 5,	// 16:20
	reg_win_hti_core1_cb5           : 5,	// 21:25
	reg_win_hti_core1_yy6           : 6;	// 26:31
} SHP_HTI_WIN_CORE1_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0080 shp_hti_win_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core1_win_w0_x0     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core1_win_w0_y0     :12;	// 16:27
} SHP_HTI_WIN_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0084 shp_hti_win_core1_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core1_win_w0_x1     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core1_win_w0_y1     :12;	// 16:27
} SHP_HTI_WIN_CORE1_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0088 shp_hti_win_core1_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core1_win_w1_x0     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core1_win_w1_y0     :12;	// 16:27
} SHP_HTI_WIN_CORE1_CTRL_03;

/*-----------------------------------------------------------------------------
	0x008c shp_hti_win_core1_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_core1_win_w1_x1     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_core1_win_w1_y1     :12;	// 16:27
} SHP_HTI_WIN_CORE1_CTRL_04;

/*-----------------------------------------------------------------------------
	0x00c0 shp_vti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vti_enable                  : 1,	//     0
	reg_vti_debug_map_en            : 1,	//     1
	reg_vti_mm_tap_size             : 2,	//  2: 3
	reg_vti_avg_tap_size            : 2,	//  4: 5
	reg_vti_ti_mode                 : 1,	//     6
	                                : 1,	//     7 reserved
	reg_vti_master_gain             : 8;	//  8:15
} SHP_VTI_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00d0 shp_lti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lti_2d_en                   : 1,	//     0
	reg_lti_tap_size                : 2,	//  1: 2
	                                : 1,	//     3 reserved
	reg_lti_coring_en               : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_lti_2d_gain                 : 8,	//  8:15
	reg_lti_2d_limit                :10;	// 16:25
} SHP_LTI_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00d4 shp_lti_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lti_coring_lut_y0           : 8,	//  0: 7
	reg_lti_coring_lut_x0           : 8,	//  8:15
	reg_lti_coring_lut_y1           : 8,	// 16:23
	reg_lti_coring_lut_x1           : 8;	// 24:31
} SHP_LTI_CTRL_01;

/*-----------------------------------------------------------------------------
	0x00e0 shp_ti_win_core0_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core0_win0_en        : 1,	//     0
	reg_win_ti_core0_win1_en        : 1,	//     1
	reg_win_ti_core0_win01_en       : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_ti_core0_win_outside    : 1,	//     6
	reg_win_ti_core0_win_en         : 1,	//     7
	reg_win_ti_core0_bdr_alpha      : 5,	//  8:12
	reg_win_ti_core0_bdr_wid        : 2,	// 13:14
	reg_win_ti_core0_bdr_en         : 1,	//    15
	reg_win_ti_core0_cr5            : 5,	// 16:20
	reg_win_ti_core0_cb5            : 5,	// 21:25
	reg_win_ti_core0_yy6            : 6;	// 26:31
} SHP_TI_WIN_CORE0_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00e4 shp_ti_win_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core0_win_w0_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core0_win_w0_y0      :12;	// 16:27
} SHP_TI_WIN_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x00e8 shp_ti_win_core0_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core0_win_w0_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core0_win_w0_y1      :12;	// 16:27
} SHP_TI_WIN_CORE0_CTRL_02;

/*-----------------------------------------------------------------------------
	0x00ec shp_ti_win_core0_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core0_win_w1_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core0_win_w1_y0      :12;	// 16:27
} SHP_TI_WIN_CORE0_CTRL_03;

/*-----------------------------------------------------------------------------
	0x00f0 shp_ti_win_core0_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core0_win_w1_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core0_win_w1_y1      :12;	// 16:27
} SHP_TI_WIN_CORE0_CTRL_04;

/*-----------------------------------------------------------------------------
	0x00f4 shp_ti_win_core1_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core1_win0_en        : 1,	//     0
	reg_win_ti_core1_win1_en        : 1,	//     1
	reg_win_ti_core1_win01_en       : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_ti_core1_win_outside    : 1,	//     6
	reg_win_ti_core1_win_en         : 1,	//     7
	reg_win_ti_core1_bdr_alpha      : 5,	//  8:12
	reg_win_ti_core1_bdr_wid        : 2,	// 13:14
	reg_win_ti_core1_bdr_en         : 1,	//    15
	reg_win_ti_core1_cr5            : 5,	// 16:20
	reg_win_ti_core1_cb5            : 5,	// 21:25
	reg_win_ti_core1_yy6            : 6;	// 26:31
} SHP_TI_WIN_CORE1_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00f8 shp_ti_win_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core1_win_w0_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core1_win_w0_y0      :12;	// 16:27
} SHP_TI_WIN_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x00fc shp_ti_win_core1_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core1_win_w0_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core1_win_w0_y1      :12;	// 16:27
} SHP_TI_WIN_CORE1_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0100 shp_ti_win_core1_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core1_win_w1_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core1_win_w1_y0      :12;	// 16:27
} SHP_TI_WIN_CORE1_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0104 shp_ti_win_core1_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_ti_core1_win_w1_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_ti_core1_win_w1_y1      :12;	// 16:27
} SHP_TI_WIN_CORE1_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0130 shp_ti_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ti_edf_en                   : 1,	//     0
	reg_ti_hv_filter_en             : 1,	//     1
	                                : 1,	//     2 reserved
	reg_ti_edge_adaptive_en         : 1,	//     3
	reg_ti_line_variation_mode      : 1,	//     4
	reg_ti_l_type_protection        : 1,	//     5
	                                : 2,	//  6: 7 reserved
	reg_ti_count_diff_th            : 5,	//  8:12
	                                : 3,	// 13:15 reserved
	reg_ti_output_mux               : 3,	// 16:18
	reg_ti_buffer_detour_en         : 1,	//    19
	reg_ti_center_blur_mode         : 2,	// 20:21
	reg_ti_n_avg_mode               : 1,	//    22
	reg_ti_detour_en                : 1,	//    23
	reg_ti_line_variation_diff_th   : 8;	// 24:31
} SHP_TI_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0140 shp_dj_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_edf_en                   : 1,	//     0
	reg_dj_hv_filter_en             : 1,	//     1
	                                : 1,	//     2 reserved
	reg_dj_edge_adaptive_en         : 1,	//     3
	reg_dj_line_variation_mode      : 1,	//     4
	reg_dj_l_type_protection        : 1,	//     5
	                                : 2,	//  6: 7 reserved
	reg_dj_count_diff_th            : 5,	//  8:12
	                                : 3,	// 13:15 reserved
	reg_dj_output_mux               : 3,	// 16:18
	reg_dj_buffer_detour_en         : 1,	//    19
	reg_dj_center_blur_mode         : 2,	// 20:21
	reg_dj_n_avg_mode               : 1,	//    22
	reg_dj_detour_en                : 1,	//    23
	reg_dj_line_variation_diff_th   : 8;	// 24:31
} SHP_DJ_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0144 shp_dj_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_level_th                 : 8,	//  0: 7
	                                : 8,	//  8:15 reserved
	reg_dj_n_avg_gain               : 8;	// 16:23
} SHP_DJ_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0148 shp_dj_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_g0_cnt_min               : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	reg_dj_g0_mul                   : 5;	//  8:12
} SHP_DJ_CTRL_02;

/*-----------------------------------------------------------------------------
	0x014c shp_dj_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_g1_protect_min           : 8,	//  0: 7
	reg_dj_g1_mul                   : 7,	//  8:14
	                                : 1,	//    15 reserved
	reg_dj_edge_min                 : 8,	// 16:23
	reg_dj_edge_mul                 : 8;	// 24:31
} SHP_DJ_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0150 shp_dj_win_core0_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core0_win0_en        : 1,	//     0
	reg_win_dj_core0_win1_en        : 1,	//     1
	reg_win_dj_core0_win01_en       : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_dj_core0_win_outside    : 1,	//     6
	reg_win_dj_core0_win_en         : 1,	//     7
	reg_win_dj_core0_bdr_alpha      : 5,	//  8:12
	reg_win_dj_core0_bdr_wid        : 2,	// 13:14
	reg_win_dj_core0_bdr_en         : 1,	//    15
	reg_win_dj_core0_cr5            : 5,	// 16:20
	reg_win_dj_core0_cb5            : 5,	// 21:25
	reg_win_dj_core0_yy6            : 6;	// 26:31
} SHP_DJ_WIN_CORE0_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0154 shp_dj_win_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core0_win_w0_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core0_win_w0_y0      :12;	// 16:27
} SHP_DJ_WIN_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0158 shp_dj_win_core0_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core0_win_w0_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core0_win_w0_y1      :12;	// 16:27
} SHP_DJ_WIN_CORE0_CTRL_02;

/*-----------------------------------------------------------------------------
	0x015c shp_dj_win_core0_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core0_win_w1_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core0_win_w1_y0      :12;	// 16:27
} SHP_DJ_WIN_CORE0_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0160 shp_dj_win_core0_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core0_win_w1_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core0_win_w1_y1      :12;	// 16:27
} SHP_DJ_WIN_CORE0_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0164 shp_dj_win_core1_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core1_win0_en        : 1,	//     0
	reg_win_dj_core1_win1_en        : 1,	//     1
	reg_win_dj_core1_win01_en       : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_dj_core1_win_outside    : 1,	//     6
	reg_win_dj_core1_win_en         : 1,	//     7
	reg_win_dj_core1_bdr_alpha      : 5,	//  8:12
	reg_win_dj_core1_bdr_wid        : 2,	// 13:14
	reg_win_dj_core1_bdr_en         : 1,	//    15
	reg_win_dj_core1_cr5            : 5,	// 16:20
	reg_win_dj_core1_cb5            : 5,	// 21:25
	reg_win_dj_core1_yy6            : 6;	// 26:31
} SHP_DJ_WIN_CORE1_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0168 shp_dj_win_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core1_win_w0_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core1_win_w0_y0      :12;	// 16:27
} SHP_DJ_WIN_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x016c shp_dj_win_core1_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core1_win_w0_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core1_win_w0_y1      :12;	// 16:27
} SHP_DJ_WIN_CORE1_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0170 shp_dj_win_core1_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core1_win_w1_x0      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core1_win_w1_y0      :12;	// 16:27
} SHP_DJ_WIN_CORE1_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0174 shp_dj_win_core1_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_core1_win_w1_x1      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_core1_win_w1_y1      :12;	// 16:27
} SHP_DJ_WIN_CORE1_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0200 shp_core_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0204 shp_core_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_in_vert_cnt             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_in_hori_cnt             :12;	// 16:27
} SHP_CORE_STAT_01;

/*-----------------------------------------------------------------------------
	0x0208 shp_core_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_out_vert_cnt            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_out_hori_cnt            :12;	// 16:27
} SHP_CORE_STAT_02;

/*-----------------------------------------------------------------------------
	0x020c shp_core_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_fin_out_vert_cnt        :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_fin_in_vert_cnt         :12;	// 16:27
} SHP_CORE_STAT_03;

/*-----------------------------------------------------------------------------
	0x0210 shp_core_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_shp_i_sucfail           ;   	// 31: 0
} SHP_CORE_STAT_04;

/*-----------------------------------------------------------------------------
	0x0214 shp_core_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_shp_o_sucfail           ;   	// 31: 0
} SHP_CORE_STAT_05;

/*-----------------------------------------------------------------------------
	0x0218 shp_core0_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x021c shp_core0_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_mon_in_vert_cnt       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core0_mon_in_hori_cnt       :12;	// 16:27
} SHP_CORE0_STAT_01;

/*-----------------------------------------------------------------------------
	0x0220 shp_core0_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_mon_out_vert_cnt      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core0_mon_out_hori_cnt      :12;	// 16:27
} SHP_CORE0_STAT_02;

/*-----------------------------------------------------------------------------
	0x0224 shp_core0_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_mon_fin_out_vert_cnt  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core0_mon_fin_in_vert_cnt   :12;	// 16:27
} SHP_CORE0_STAT_03;

/*-----------------------------------------------------------------------------
	0x0228 shp_core0_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_mon_shp_i_sucfail     ;   	// 31: 0
} SHP_CORE0_STAT_04;

/*-----------------------------------------------------------------------------
	0x022c shp_core0_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core0_mon_shp_o_sucfail     ;   	// 31: 0
} SHP_CORE0_STAT_05;

/*-----------------------------------------------------------------------------
	0x0230 shp_core1_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0234 shp_core1_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_mon_in_vert_cnt       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core1_mon_in_hori_cnt       :12;	// 16:27
} SHP_CORE1_STAT_01;

/*-----------------------------------------------------------------------------
	0x0238 shp_core1_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_mon_out_vert_cnt      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core1_mon_out_hori_cnt      :12;	// 16:27
} SHP_CORE1_STAT_02;

/*-----------------------------------------------------------------------------
	0x023c shp_core1_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_mon_fin_out_vert_cnt  :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_core1_mon_fin_in_vert_cnt   :12;	// 16:27
} SHP_CORE1_STAT_03;

/*-----------------------------------------------------------------------------
	0x0240 shp_core1_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_mon_shp_i_sucfail     ;   	// 31: 0
} SHP_CORE1_STAT_04;

/*-----------------------------------------------------------------------------
	0x0244 shp_core1_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_core1_mon_shp_o_sucfail     ;   	// 31: 0
} SHP_CORE1_STAT_05;

/*-----------------------------------------------------------------------------
	0x0280 shp_fsw_ctrl_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0284 shp_fsw_ctrl_01 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0288 shp_fsw_ctrl_02 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x028c shp_fsw_ctrl_03 ''
------------------------------------------------------------------------------*/
/*	no field */

typedef struct {
	SHP_CORE_CTRL_00                	shp_core_ctrl_00                ;	// 0x0000 : ''
	SHP_CORE_CTRL_01                	shp_core_ctrl_01                ;	// 0x0004 : ''
	SHP_CORE0_CTRL_01               	shp_core0_ctrl_01               ;	// 0x0008 : ''
	SHP_CORE1_CTRL_01               	shp_core1_ctrl_01               ;	// 0x000c : ''
	UINT32                          	                 __rsvd_00[   2];	// 0x0010 ~ 0x0014
	SHP_CORE_CTRL_02                	shp_core_ctrl_02                ;	// 0x0018 : ''
	SHP_CORE_CTRL_03                	shp_core_ctrl_03                ;	// 0x001c : ''
	SHP_CORE_CTRL_04                	shp_core_ctrl_04                ;	// 0x0020 : ''
	UINT32                          	                 __rsvd_01[   3];	// 0x0024 ~ 0x002c
	SHP_SPLIT_CTRL_00               	shp_split_ctrl_00               ;	// 0x0030 : ''
	SHP_SPLIT_CTRL_01               	shp_split_ctrl_01               ;	// 0x0034 : ''
	SHP_SPLIT_CTRL_02               	shp_split_ctrl_02               ;	// 0x0038 : ''
	SHP_SPLIT_CTRL_03               	shp_split_ctrl_03               ;	// 0x003c : ''
	SHP_MERGE_CTRL_00               	shp_merge_ctrl_00               ;	// 0x0040 : ''
	SHP_MERGE_CTRL_01               	shp_merge_ctrl_01               ;	// 0x0044 : ''
	SHP_MERGE_CTRL_02               	shp_merge_ctrl_02               ;	// 0x0048 : ''
	SHP_MERGE_CTRL_03               	shp_merge_ctrl_03               ;	// 0x004c : ''
	SHP_PAT_GEN_CTRL_00             	shp_pat_gen_ctrl_00             ;	// 0x0050 : ''
	UINT32                          	                 __rsvd_02[   3];	// 0x0054 ~ 0x005c
	SHP_HTI_CTRL_00                 	shp_hti_ctrl_00                 ;	// 0x0060 : ''
	SHP_HTI_CTRL_01                 	shp_hti_ctrl_01                 ;	// 0x0064 : ''
	SHP_HTI_WIN_CORE0_CTRL_00       	shp_hti_win_core0_ctrl_00       ;	// 0x0068 : ''
	SHP_HTI_WIN_CORE0_CTRL_01       	shp_hti_win_core0_ctrl_01       ;	// 0x006c : ''
	SHP_HTI_WIN_CORE0_CTRL_02       	shp_hti_win_core0_ctrl_02       ;	// 0x0070 : ''
	SHP_HTI_WIN_CORE0_CTRL_03       	shp_hti_win_core0_ctrl_03       ;	// 0x0074 : ''
	SHP_HTI_WIN_CORE0_CTRL_04       	shp_hti_win_core0_ctrl_04       ;	// 0x0078 : ''
	SHP_HTI_WIN_CORE1_CTRL_00       	shp_hti_win_core1_ctrl_00       ;	// 0x007c : ''
	SHP_HTI_WIN_CORE1_CTRL_01       	shp_hti_win_core1_ctrl_01       ;	// 0x0080 : ''
	SHP_HTI_WIN_CORE1_CTRL_02       	shp_hti_win_core1_ctrl_02       ;	// 0x0084 : ''
	SHP_HTI_WIN_CORE1_CTRL_03       	shp_hti_win_core1_ctrl_03       ;	// 0x0088 : ''
	SHP_HTI_WIN_CORE1_CTRL_04       	shp_hti_win_core1_ctrl_04       ;	// 0x008c : ''
	UINT32                          	                 __rsvd_03[  12];	// 0x0090 ~ 0x00bc
	SHP_VTI_CTRL_00                 	shp_vti_ctrl_00                 ;	// 0x00c0 : ''
	UINT32                          	                 __rsvd_04[   3];	// 0x00c4 ~ 0x00cc
	SHP_LTI_CTRL_00                 	shp_lti_ctrl_00                 ;	// 0x00d0 : ''
	SHP_LTI_CTRL_01                 	shp_lti_ctrl_01                 ;	// 0x00d4 : ''
	UINT32                          	                 __rsvd_05[   2];	// 0x00d8 ~ 0x00dc
	SHP_TI_WIN_CORE0_CTRL_00        	shp_ti_win_core0_ctrl_00        ;	// 0x00e0 : ''
	SHP_TI_WIN_CORE0_CTRL_01        	shp_ti_win_core0_ctrl_01        ;	// 0x00e4 : ''
	SHP_TI_WIN_CORE0_CTRL_02        	shp_ti_win_core0_ctrl_02        ;	// 0x00e8 : ''
	SHP_TI_WIN_CORE0_CTRL_03        	shp_ti_win_core0_ctrl_03        ;	// 0x00ec : ''
	SHP_TI_WIN_CORE0_CTRL_04        	shp_ti_win_core0_ctrl_04        ;	// 0x00f0 : ''
	SHP_TI_WIN_CORE1_CTRL_00        	shp_ti_win_core1_ctrl_00        ;	// 0x00f4 : ''
	SHP_TI_WIN_CORE1_CTRL_01        	shp_ti_win_core1_ctrl_01        ;	// 0x00f8 : ''
	SHP_TI_WIN_CORE1_CTRL_02        	shp_ti_win_core1_ctrl_02        ;	// 0x00fc : ''
	SHP_TI_WIN_CORE1_CTRL_03        	shp_ti_win_core1_ctrl_03        ;	// 0x0100 : ''
	SHP_TI_WIN_CORE1_CTRL_04        	shp_ti_win_core1_ctrl_04        ;	// 0x0104 : ''
	UINT32                          	                 __rsvd_06[  10];	// 0x0108 ~ 0x012c
	SHP_TI_CTRL_00                  	shp_ti_ctrl_00                  ;	// 0x0130 : ''
	UINT32                          	                 __rsvd_07[   3];	// 0x0134 ~ 0x013c
	SHP_DJ_CTRL_00                  	shp_dj_ctrl_00                  ;	// 0x0140 : ''
	SHP_DJ_CTRL_01                  	shp_dj_ctrl_01                  ;	// 0x0144 : ''
	SHP_DJ_CTRL_02                  	shp_dj_ctrl_02                  ;	// 0x0148 : ''
	SHP_DJ_CTRL_03                  	shp_dj_ctrl_03                  ;	// 0x014c : ''
	SHP_DJ_WIN_CORE0_CTRL_00        	shp_dj_win_core0_ctrl_00        ;	// 0x0150 : ''
	SHP_DJ_WIN_CORE0_CTRL_01        	shp_dj_win_core0_ctrl_01        ;	// 0x0154 : ''
	SHP_DJ_WIN_CORE0_CTRL_02        	shp_dj_win_core0_ctrl_02        ;	// 0x0158 : ''
	SHP_DJ_WIN_CORE0_CTRL_03        	shp_dj_win_core0_ctrl_03        ;	// 0x015c : ''
	SHP_DJ_WIN_CORE0_CTRL_04        	shp_dj_win_core0_ctrl_04        ;	// 0x0160 : ''
	SHP_DJ_WIN_CORE1_CTRL_00        	shp_dj_win_core1_ctrl_00        ;	// 0x0164 : ''
	SHP_DJ_WIN_CORE1_CTRL_01        	shp_dj_win_core1_ctrl_01        ;	// 0x0168 : ''
	SHP_DJ_WIN_CORE1_CTRL_02        	shp_dj_win_core1_ctrl_02        ;	// 0x016c : ''
	SHP_DJ_WIN_CORE1_CTRL_03        	shp_dj_win_core1_ctrl_03        ;	// 0x0170 : ''
	SHP_DJ_WIN_CORE1_CTRL_04        	shp_dj_win_core1_ctrl_04        ;	// 0x0174 : ''
	UINT32                          	                 __rsvd_08[  34];	// 0x0178 ~ 0x01fc
	UINT32                          	shp_core_stat_00                ;	// 0x0200 : ''
	SHP_CORE_STAT_01                	shp_core_stat_01                ;	// 0x0204 : ''
	SHP_CORE_STAT_02                	shp_core_stat_02                ;	// 0x0208 : ''
	SHP_CORE_STAT_03                	shp_core_stat_03                ;	// 0x020c : ''
	SHP_CORE_STAT_04                	shp_core_stat_04                ;	// 0x0210 : ''
	SHP_CORE_STAT_05                	shp_core_stat_05                ;	// 0x0214 : ''
	UINT32                          	shp_core0_stat_00               ;	// 0x0218 : ''
	SHP_CORE0_STAT_01               	shp_core0_stat_01               ;	// 0x021c : ''
	SHP_CORE0_STAT_02               	shp_core0_stat_02               ;	// 0x0220 : ''
	SHP_CORE0_STAT_03               	shp_core0_stat_03               ;	// 0x0224 : ''
	SHP_CORE0_STAT_04               	shp_core0_stat_04               ;	// 0x0228 : ''
	SHP_CORE0_STAT_05               	shp_core0_stat_05               ;	// 0x022c : ''
	UINT32                          	shp_core1_stat_00               ;	// 0x0230 : ''
	SHP_CORE1_STAT_01               	shp_core1_stat_01               ;	// 0x0234 : ''
	SHP_CORE1_STAT_02               	shp_core1_stat_02               ;	// 0x0238 : ''
	SHP_CORE1_STAT_03               	shp_core1_stat_03               ;	// 0x023c : ''
	SHP_CORE1_STAT_04               	shp_core1_stat_04               ;	// 0x0240 : ''
	SHP_CORE1_STAT_05               	shp_core1_stat_05               ;	// 0x0244 : ''
	UINT32                          	                 __rsvd_09[  14];	// 0x0248 ~ 0x027c
	UINT32                          	shp_fsw_ctrl_00                 ;	// 0x0280 : ''
	UINT32                          	shp_fsw_ctrl_01                 ;	// 0x0284 : ''
	UINT32                          	shp_fsw_ctrl_02                 ;	// 0x0288 : ''
	UINT32                          	shp_fsw_ctrl_03                 ;	// 0x028c : ''
}
OSD_SHP_E60_REG_T;

/* 78 regs, 78 types */

/* 78 regs, 78 types in Total*/

#define SHP_CTRL_Off(idx,_r)			 ((UINT64)&(g_osd_shp_e60_reg_shadow[idx]->_r) - (UINT64)(g_osd_shp_e60_reg_shadow[idx]))
#define SHP_CTRL_RdFL(idx,_r)			((g_osd_shp_e60_reg_shadow[idx]->_r)=(g_osd_shp_e60_reg[idx]->_r))
#ifdef	FBDEV_E60_USE_REG_DEBUG
#define SHP_CTRL_WrFL(idx,_r) \
									do { \
										FBDEV_E60_CMN_RegDebug((idx==0)? CCO_OSD_SHP0_BASE:CCO_OSD_SHP1_BASE, SHP_CTRL_Off(idx,_r), SHP_CTRL_Rd(idx,_r)); \
										((g_osd_shp_e60_reg[idx]->_r)=(g_osd_shp_e60_reg_shadow[idx]->_r)); \
									} while(0)
#else
#define SHP_CTRL_WrFL(idx,_r)			((g_osd_shp_e60_reg[idx]->_r)=(g_osd_shp_e60_reg_shadow[idx]->_r))
#endif

#define SHP_CTRL_Rd(idx,_r)				*((UINT32*)(&(g_osd_shp_e60_reg_shadow[idx]->_r)))
#define SHP_CTRL_Wr(idx,_r,_v)			((SHP_CTRL_Rd(idx,_r))=((UINT32)(_v)))

#define SHP_CTRL_Rd01(idx,_r,_f01,_v01) \
								do { \
									(_v01) = (g_osd_shp_e60_reg_shadow[idx]->_r._f01); \
								} while(0)

#define SHP_CTRL_Rd02(idx,_r,_f01,_v01,_f02,_v02) \
								do { \
									(_v01) = (g_osd_shp_e60_reg_shadow[idx]->_r._f01); \
									(_v02) = (g_osd_shp_e60_reg_shadow[idx]->_r._f02); \
								} while(0)


#define SHP_CTRL_Wr01(idx,_r,_f01,_v01) \
								do { \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f01) = (_v01); \
								} while(0)

#define SHP_CTRL_Wr02(idx,_r,_f01,_v01,_f02,_v02) \
								do { \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f01) = (_v01); \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f02) = (_v02); \
								} while(0)
#define SHP_CTRL_Wr03(idx,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
								do { \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f01) = (_v01); \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f02) = (_v02); \
									(g_osd_shp_e60_reg_shadow[idx]->_r._f03) = (_v03); \
								} while(0)

#define	osd_shp_y	0
#define	osd_shp_a	1

extern volatile OSD_SHP_E60_REG_T*	g_osd_shp_e60_reg[2];
extern OSD_SHP_E60_REG_T*  			g_osd_shp_e60_reg_shadow[2];

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'E60-A0_PQE_OSD_SHP_reg_man0.csv' 20191215 00:56:42 KST by getregs v2.9 */
