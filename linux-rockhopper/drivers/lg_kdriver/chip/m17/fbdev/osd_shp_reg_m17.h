#ifndef __OSD_SHP_REG_M17_H__
#define __OSD_SHP_REG_M17_H__

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
	reg_top_cg_disable              : 1,	//     8
	                                : 7,	//  9:15 reserved
	reg_top_update_ctrl             : 5;	// 16:20
} SHP_CORE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0004 shp_core_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_width                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_height                  :12;	// 16:27
} SHP_CORE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0008 shp_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_core0_width             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_core0_height            :12;	// 16:27
} SHP_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x000c shp_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_core1_width             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_core1_height            :12;	// 16:27
} SHP_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0020 out_hgos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_out_hgos_head_crop_ptr      :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_out_hgos_tail_crop_ptr      :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_out_hgos_tail_en            : 1,	//    30
	reg_out_hgos_head_en            : 1;	//    31
} OUT_HGOS_CTRL;

/*-----------------------------------------------------------------------------
	0x0024 out_vgos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_out_vgos_head_crop_ptr      :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_out_vgos_tail_crop_ptr      :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_out_vgos_tail_en            : 1,	//    30
	reg_out_vgos_head_en            : 1;	//    31
} OUT_VGOS_CTRL;

/*-----------------------------------------------------------------------------
	0x0030 shp_dj_ctrl_00 ''
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
	                                : 1,	//    19 reserved
	reg_dj_center_blur_mode         : 2,	// 20:21
	reg_dj_n_avg_mode               : 1,	//    22
	                                : 1,	//    23 reserved
	reg_dj_line_variation_diff_th   : 8;	// 24:31
} SHP_DJ_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0034 shp_dj_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_level_th                 : 8,	//  0: 7
	                                : 8,	//  8:15 reserved
	reg_dj_n_avg_gain               : 8;	// 16:23
} SHP_DJ_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0038 shp_dj_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_g0_cnt_min               : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	reg_dj_g0_mul                   : 5;	//  8:12
} SHP_DJ_CTRL_02;

/*-----------------------------------------------------------------------------
	0x003c shp_dj_ctrl_03 ''
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
	0x0040 shp_dj_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_ti_gain                  : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	reg_dj_dj_normal_gain           : 4,	//  8:11
	                                : 4,	// 12:15 reserved
	reg_dj_clipping_max             : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_dj_clipping_min             : 6;	// 24:29
} SHP_DJ_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0060 shp_core0_win_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core0_win0_en           : 1,	//     0
	reg_win_core0_win1_en           : 1,	//     1
	reg_win_core0_win01_en          : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_core0_win_outside       : 1,	//     6
	reg_win_core0_win_en            : 1,	//     7
	reg_win_core0_bdr_alpha         : 5,	//  8:12
	reg_win_core0_bdr_wid           : 2,	// 13:14
	reg_win_core0_bdr_en            : 1,	//    15
	reg_win_core0_cr5               : 5,	// 16:20
	reg_win_core0_cb5               : 5,	// 21:25
	reg_win_core0_yy6               : 6;	// 26:31
} SHP_CORE0_WIN_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0064 shp_core0_win_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core0_win_w0_x0         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core0_win_w0_y0         :12;	// 16:27
} SHP_CORE0_WIN_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0068 shp_core0_win_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core0_win_w0_x1         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core0_win_w0_y1         :12;	// 16:27
} SHP_CORE0_WIN_CTRL_02;

/*-----------------------------------------------------------------------------
	0x006c shp_core0_win_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core0_win_w1_x0         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core0_win_w1_y0         :12;	// 16:27
} SHP_CORE0_WIN_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0070 shp_core0_win_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core0_win_w1_x1         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core0_win_w1_y1         :12;	// 16:27
} SHP_CORE0_WIN_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0074 shp_core1_win_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core1_win0_en           : 1,	//     0
	reg_win_core1_win1_en           : 1,	//     1
	reg_win_core1_win01_en          : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_core1_win_outside       : 1,	//     6
	reg_win_core1_win_en            : 1,	//     7
	reg_win_core1_bdr_alpha         : 5,	//  8:12
	reg_win_core1_bdr_wid           : 2,	// 13:14
	reg_win_core1_bdr_en            : 1,	//    15
	reg_win_core1_cr5               : 5,	// 16:20
	reg_win_core1_cb5               : 5,	// 21:25
	reg_win_core1_yy6               : 6;	// 26:31
} SHP_CORE1_WIN_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0078 shp_core1_win_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core1_win_w0_x0         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core1_win_w0_y0         :12;	// 16:27
} SHP_CORE1_WIN_CTRL_01;

/*-----------------------------------------------------------------------------
	0x007c shp_core1_win_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core1_win_w0_x1         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core1_win_w0_y1         :12;	// 16:27
} SHP_CORE1_WIN_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0080 shp_core1_win_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core1_win_w1_x0         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core1_win_w1_y0         :12;	// 16:27
} SHP_CORE1_WIN_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0084 shp_core1_win_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_core1_win_w1_x1         :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_core1_win_w1_y1         :12;	// 16:27
} SHP_CORE1_WIN_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0090 shp_debug_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dbg_disp_enable_debug_mode  : 1,	//     0
	reg_dbg_disp_status_enable      : 1,	//     1
	reg_dbg_disp_debug_mode         : 1,	//     2
	reg_dbg_disp_show_dce_blur      : 1,	//     3
	                                : 5,	//  4: 8 reserved
	reg_dbg_disp_show_sqm2          : 1,	//     9
	reg_dbg_disp_sqm2_debug_image   : 4,	// 10:13
	                                : 1,	//    14 reserved
	reg_dbg_disp_show_bbd           : 2,	// 15:16
	reg_dbg_disp_bbd_line_width     : 3,	// 17:19
	reg_dbg_disp_show_apl           : 1;	//    20
} SHP_DEBUG_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0094 shp_debug_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dbg_disp_yc_debug_en        : 1,	//     0
	reg_dbg_disp_force_yy_enable    : 1,	//     1
	reg_dbg_disp_force_cb_enable    : 1,	//     2
	reg_dbg_disp_force_cr_enable    : 1,	//     3
	reg_dbg_disp_yc_debug_mode_sel  : 3;	//  4: 6
} SHP_DEBUG_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0098 shp_debug_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dbg_disp_force_yy           :10,	//  0: 9
	reg_dbg_disp_force_cb           :10,	// 10:19
	reg_dbg_disp_force_cr           :10;	// 20:29
} SHP_DEBUG_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0100 shp_top_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0104 shp_top_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_in_vert_cnt             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_in_hori_cnt             :12;	// 16:27
} SHP_TOP_STAT_01;

/*-----------------------------------------------------------------------------
	0x0108 shp_top_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_out_vert_cnt            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_out_hori_cnt            :12;	// 16:27
} SHP_TOP_STAT_02;

/*-----------------------------------------------------------------------------
	0x010c shp_top_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_fin_vert_cnt            :12;	//  0:11
} SHP_TOP_STAT_03;

/*-----------------------------------------------------------------------------
	0x0110 shp_top_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_shp_i_sucfail           ;   	// 31: 0
} SHP_TOP_STAT_04;

/*-----------------------------------------------------------------------------
	0x0114 shp_top_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_shp_o_sucfail           ;   	// 31: 0
} SHP_TOP_STAT_05;

/*-----------------------------------------------------------------------------
	0x0118 shp_top_stat_06 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x011c shp_top_stat_07 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0120 shp_core0_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_vcnt              :12,	//  0:11
	reg_mon_core0_va_pe1_in         : 1,	//    12
	reg_mon_core0_va_pe1_out        : 1,	//    13
	                                : 2,	// 14:15 reserved
	reg_mon_core0_vcnt2             :12;	// 16:27
} SHP_CORE0_STAT_00;

/*-----------------------------------------------------------------------------
	0x0124 shp_core0_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_in_vert_cnt       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_core0_in_hori_cnt       :12;	// 16:27
} SHP_CORE0_STAT_01;

/*-----------------------------------------------------------------------------
	0x0128 shp_core0_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_out_vert_cnt      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_core0_out_hori_cnt      :12;	// 16:27
} SHP_CORE0_STAT_02;

/*-----------------------------------------------------------------------------
	0x012c shp_core0_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_fin_vert_cnt      :12;	//  0:11
} SHP_CORE0_STAT_03;

/*-----------------------------------------------------------------------------
	0x0130 shp_core0_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_i_sucfail         ;   	// 31: 0
} SHP_CORE0_STAT_04;

/*-----------------------------------------------------------------------------
	0x0134 shp_core0_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_o_sucfail         ;   	// 31: 0
} SHP_CORE0_STAT_05;

/*-----------------------------------------------------------------------------
	0x0138 shp_core0_stat_06 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x013c shp_core0_stat_07 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0140 shp_core1_stat_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_vcnt              :12,	//  0:11
	reg_mon_core1_va_pe1_in         : 1,	//    12
	reg_mon_core1_va_pe1_out        : 1,	//    13
	                                : 2,	// 14:15 reserved
	reg_mon_core1_vcnt2             :12;	// 16:27
} SHP_CORE1_STAT_00;

/*-----------------------------------------------------------------------------
	0x0144 shp_core1_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_in_vert_cnt       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_core1_in_hori_cnt       :12;	// 16:27
} SHP_CORE1_STAT_01;

/*-----------------------------------------------------------------------------
	0x0148 shp_core1_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_out_vert_cnt      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_mon_core1_out_hori_cnt      :12;	// 16:27
} SHP_CORE1_STAT_02;

/*-----------------------------------------------------------------------------
	0x014c shp_core1_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_fin_vert_cnt      :12;	//  0:11
} SHP_CORE1_STAT_03;

/*-----------------------------------------------------------------------------
	0x0150 shp_core1_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_i_sucfail         ;   	// 31: 0
} SHP_CORE1_STAT_04;

/*-----------------------------------------------------------------------------
	0x0154 shp_core1_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_o_sucfail         ;   	// 31: 0
} SHP_CORE1_STAT_05;

/*-----------------------------------------------------------------------------
	0x0158 shp_core1_stat_06 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x015c shp_core1_stat_07 ''
------------------------------------------------------------------------------*/
/*	no field */

typedef struct {
	SHP_CORE_CTRL_00                	shp_core_ctrl_00                ;	// 0x0000 : ''
	SHP_CORE_CTRL_01                	shp_core_ctrl_01                ;	// 0x0004 : ''
	SHP_CORE0_CTRL_01               	shp_core0_ctrl_01               ;	// 0x0008 : ''
	SHP_CORE1_CTRL_01               	shp_core1_ctrl_01               ;	// 0x000c : ''
	UINT32                          	                 __rsvd_00[   4];	// 0x0010 ~ 0x001c
	OUT_HGOS_CTRL                   	out_hgos_ctrl                   ;	// 0x0020 : ''
	OUT_VGOS_CTRL                   	out_vgos_ctrl                   ;	// 0x0024 : ''
	UINT32                          	                 __rsvd_01[   2];	// 0x0028 ~ 0x002c
	SHP_DJ_CTRL_00                  	shp_dj_ctrl_00                  ;	// 0x0030 : ''
	SHP_DJ_CTRL_01                  	shp_dj_ctrl_01                  ;	// 0x0034 : ''
	SHP_DJ_CTRL_02                  	shp_dj_ctrl_02                  ;	// 0x0038 : ''
	SHP_DJ_CTRL_03                  	shp_dj_ctrl_03                  ;	// 0x003c : ''
	SHP_DJ_CTRL_04                  	shp_dj_ctrl_04                  ;	// 0x0040 : ''
	UINT32                          	                 __rsvd_02[   7];	// 0x0044 ~ 0x005c
	SHP_CORE0_WIN_CTRL_00           	shp_core0_win_ctrl_00           ;	// 0x0060 : ''
	SHP_CORE0_WIN_CTRL_01           	shp_core0_win_ctrl_01           ;	// 0x0064 : ''
	SHP_CORE0_WIN_CTRL_02           	shp_core0_win_ctrl_02           ;	// 0x0068 : ''
	SHP_CORE0_WIN_CTRL_03           	shp_core0_win_ctrl_03           ;	// 0x006c : ''
	SHP_CORE0_WIN_CTRL_04           	shp_core0_win_ctrl_04           ;	// 0x0070 : ''
	SHP_CORE1_WIN_CTRL_00           	shp_core1_win_ctrl_00           ;	// 0x0074 : ''
	SHP_CORE1_WIN_CTRL_01           	shp_core1_win_ctrl_01           ;	// 0x0078 : ''
	SHP_CORE1_WIN_CTRL_02           	shp_core1_win_ctrl_02           ;	// 0x007c : ''
	SHP_CORE1_WIN_CTRL_03           	shp_core1_win_ctrl_03           ;	// 0x0080 : ''
	SHP_CORE1_WIN_CTRL_04           	shp_core1_win_ctrl_04           ;	// 0x0084 : ''
	UINT32                          	                 __rsvd_03[   2];	// 0x0088 ~ 0x008c
	SHP_DEBUG_CTRL_00               	shp_debug_ctrl_00               ;	// 0x0090 : ''
	SHP_DEBUG_CTRL_01               	shp_debug_ctrl_01               ;	// 0x0094 : ''
	SHP_DEBUG_CTRL_02               	shp_debug_ctrl_02               ;	// 0x0098 : ''
	UINT32                          	                 __rsvd_04[  25];	// 0x009c ~ 0x00fc
	UINT32                          	shp_top_stat_00                 ;	// 0x0100 : ''
	SHP_TOP_STAT_01                 	shp_top_stat_01                 ;	// 0x0104 : ''
	SHP_TOP_STAT_02                 	shp_top_stat_02                 ;	// 0x0108 : ''
	SHP_TOP_STAT_03                 	shp_top_stat_03                 ;	// 0x010c : ''
	SHP_TOP_STAT_04                 	shp_top_stat_04                 ;	// 0x0110 : ''
	SHP_TOP_STAT_05                 	shp_top_stat_05                 ;	// 0x0114 : ''
	UINT32                          	shp_top_stat_06                 ;	// 0x0118 : ''
	UINT32                          	shp_top_stat_07                 ;	// 0x011c : ''
	SHP_CORE0_STAT_00               	shp_core0_stat_00               ;	// 0x0120 : ''
	SHP_CORE0_STAT_01               	shp_core0_stat_01               ;	// 0x0124 : ''
	SHP_CORE0_STAT_02               	shp_core0_stat_02               ;	// 0x0128 : ''
	SHP_CORE0_STAT_03               	shp_core0_stat_03               ;	// 0x012c : ''
	SHP_CORE0_STAT_04               	shp_core0_stat_04               ;	// 0x0130 : ''
	SHP_CORE0_STAT_05               	shp_core0_stat_05               ;	// 0x0134 : ''
	UINT32                          	shp_core0_stat_06               ;	// 0x0138 : ''
	UINT32                          	shp_core0_stat_07               ;	// 0x013c : ''
	SHP_CORE1_STAT_00               	shp_core1_stat_00               ;	// 0x0140 : ''
	SHP_CORE1_STAT_01               	shp_core1_stat_01               ;	// 0x0144 : ''
	SHP_CORE1_STAT_02               	shp_core1_stat_02               ;	// 0x0148 : ''
	SHP_CORE1_STAT_03               	shp_core1_stat_03               ;	// 0x014c : ''
	SHP_CORE1_STAT_04               	shp_core1_stat_04               ;	// 0x0150 : ''
	SHP_CORE1_STAT_05               	shp_core1_stat_05               ;	// 0x0154 : ''
	UINT32                          	shp_core1_stat_06               ;	// 0x0158 : ''
	UINT32                          	shp_core1_stat_07               ;	// 0x015c : ''
}
OSD_SHP_M17_REG_T;
/* 48 regs, 48 types */

/* 48 regs, 48 types in Total*/
/*
 * @{
 * Naming for register pointer.
 * g_osd_shp_m17_reg : real register of OSD.
 * g_osd_shp_m17_reg_shadow     : shadow register.
 *
 * @def OSD_M17_RdFL: Read  FLushing : Shadow <- Real.
 * @def OSD_M17_WrFL: Write FLushing : Shadow -> Real.
 * @def OSD_M17_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def OSD_M17_Wr  : Write whole register(UINT32) from Shadow register.
 * @def OSD_M17_Rd01 ~ OSD_M17_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def OSD_M17_Wr01 ~ OSD_M17_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define OSD_SHP_RdFL(_r)			((g_osd_shp_m17_reg_shadow->_r)=(g_osd_shp_m17_reg->_r))
#define OSD_SHP_WrFL(_r)			((g_osd_shp_m17_reg->_r)=(g_osd_shp_m17_reg_shadow->_r))

#define OSD_SHP_Rd(_r)				*((UINT32*)(&(g_osd_shp_m17_reg_shadow->_r)))
#define OSD_SHP_Wr(_r,_v)			((OSD_M17_Rd(_r))=((UINT32)(_v)))

#define OSD_SHP_Rd00(_r,_f)         (g_osd_shp_m17_reg_shadow->_r._f)


#define OSD_SHP_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_osd_shp_m17_reg_shadow->_r._f01);				\
								} while(0)

#define OSD_SHP_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_osd_shp_m17_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m17_reg_shadow->_r._f02);				\
								} while(0)

#define OSD_SHP_Wr01(_r,_f01,_v01)													\
								do { 											\
									(g_osd_shp_m17_reg_shadow->_r._f01) = (_v01);				\
								} while(0)

#define OSD_SHP_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_osd_shp_m17_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m17_reg_shadow->_r._f02) = (_v02);				\
								} while(0)

/** @} *//* end of macro documentation */

extern volatile OSD_SHP_M17_REG_T*     g_osd_shp_m17_reg;
extern OSD_SHP_M17_REG_T*                      g_osd_shp_m17_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'M16PP-A0_PQE_OSD_SHP_reg_man.csv' 20170921 10:34:31 KST by getregs v2.9 */
