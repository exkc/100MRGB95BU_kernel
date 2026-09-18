#ifndef __OSD_SHP_REG_M19__
#define __OSD_SHP_REG_M19__

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
	                                : 3,	// 13:15 reserved
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
	0x0008 shp_core_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_use_extern_valid        : 1,	//     0
	reg_top_use_blank_preiod_cnt    : 1,	//     1
	                                :14,	//  2:15 reserved
	reg_top_manual_blank_cnt        :16;	// 16:31
} SHP_CORE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x000c shp_core_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_prefetch_cnt            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_top_flush_cnt               :12;	// 16:27
} SHP_CORE_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0040 shp_pat_gen_ctrl_00 ''
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
	0x0070 shp_hti_win_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_win0_en             : 1,	//     0
	reg_win_hti_win1_en             : 1,	//     1
	reg_win_hti_win01_en            : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_hti_win_outside         : 1,	//     6
	reg_win_hti_win_en              : 1,	//     7
	reg_win_hti_bdr_alpha           : 5,	//  8:12
	reg_win_hti_bdr_wid             : 2,	// 13:14
	reg_win_hti_bdr_en              : 1,	//    15
	reg_win_hti_cr5                 : 5,	// 16:20
	reg_win_hti_cb5                 : 5,	// 21:25
	reg_win_hti_yy6                 : 6;	// 26:31
} SHP_HTI_WIN_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0074 shp_hti_win_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_win_w0_x0           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_win_w0_y0           :12;	// 16:27
} SHP_HTI_WIN_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0078 shp_hti_win_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_win_w0_x1           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_win_w0_y1           :12;	// 16:27
} SHP_HTI_WIN_CTRL_02;

/*-----------------------------------------------------------------------------
	0x007c shp_hti_win_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_win_w1_x0           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_win_w1_y0           :12;	// 16:27
} SHP_HTI_WIN_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0080 shp_hti_win_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_hti_win_w1_x1           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_hti_win_w1_y1           :12;	// 16:27
} SHP_HTI_WIN_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0090 shp_vti_ctrl_00 ''
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
	0x00a0 shp_lti_ctrl_00 ''
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
	0x00a4 shp_lti_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lti_coring_lut_y0           : 8,	//  0: 7
	reg_lti_coring_lut_x0           : 8,	//  8:15
	reg_lti_coring_lut_y1           : 8,	// 16:23
	reg_lti_coring_lut_x1           : 8;	// 24:31
} SHP_LTI_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0100 shp_dj_ctrl_00 ''
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
	0x0104 shp_dj_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_level_th                 : 8,	//  0: 7
	                                : 8,	//  8:15 reserved
	reg_dj_n_avg_gain               : 8;	// 16:23
} SHP_DJ_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0108 shp_dj_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dj_g0_cnt_min               : 5,	//  0: 4
	                                : 3,	//  5: 7 reserved
	reg_dj_g0_mul                   : 5;	//  8:12
} SHP_DJ_CTRL_02;

/*-----------------------------------------------------------------------------
	0x010c shp_dj_ctrl_03 ''
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
	0x0120 shp_db_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dir_blur_detour             : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_dir_blur_buf_detour         : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_dir_blur_en                 : 1;	//     8
} SHP_DB_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0124 shp_db_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dir_blur_base               : 8,	//  0: 7
	                                : 8,	//  8:15 reserved
	reg_dir_blur_gain               : 8;	// 16:23
} SHP_DB_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0140 shp_dj_win_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_win0_en              : 1,	//     0
	reg_win_dj_win1_en              : 1,	//     1
	reg_win_dj_win01_en             : 1,	//     2
	                                : 3,	//  3: 5 reserved
	reg_win_dj_win_outside          : 1,	//     6
	reg_win_dj_win_en               : 1,	//     7
	reg_win_dj_bdr_alpha            : 5,	//  8:12
	reg_win_dj_bdr_wid              : 2,	// 13:14
	reg_win_dj_bdr_en               : 1,	//    15
	reg_win_dj_cr5                  : 5,	// 16:20
	reg_win_dj_cb5                  : 5,	// 21:25
	reg_win_dj_yy6                  : 6;	// 26:31
} SHP_DJ_WIN_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0144 shp_dj_win_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_win_w0_x0            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_win_w0_y0            :12;	// 16:27
} SHP_DJ_WIN_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0148 shp_dj_win_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_win_w0_x1            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_win_w0_y1            :12;	// 16:27
} SHP_DJ_WIN_CTRL_02;

/*-----------------------------------------------------------------------------
	0x014c shp_dj_win_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_win_w1_x0            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_win_w1_y0            :12;	// 16:27
} SHP_DJ_WIN_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0150 shp_dj_win_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_win_dj_win_w1_x1            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_win_dj_win_w1_y1            :12;	// 16:27
} SHP_DJ_WIN_CTRL_04;

/*-----------------------------------------------------------------------------
	0x01c0 shp_cc_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cc_en                       : 1;	//     0
} SHP_CC_CTRL_00;

/*-----------------------------------------------------------------------------
	0x01c4 shp_cc_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cc_contrast_center          : 8,	//  0: 7
	reg_cc_contrast                 : 8,	//  8:15
	reg_cc_saturation               : 8,	// 16:23
	reg_cc_gain                     : 8;	// 24:31
} SHP_CC_CTRL_01;

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
	0x02f0 shp_fsw_ctrl_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02f4 shp_fsw_ctrl_01 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02f8 shp_fsw_ctrl_02 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x02fc shp_fsw_ctrl_03 ''
------------------------------------------------------------------------------*/
/*	no field */

typedef struct {
	SHP_CORE_CTRL_00                	shp_core_ctrl_00                ;	// 0x0000 : ''
	SHP_CORE_CTRL_01                	shp_core_ctrl_01                ;	// 0x0004 : ''
	SHP_CORE_CTRL_02                	shp_core_ctrl_02                ;	// 0x0008 : ''
	SHP_CORE_CTRL_03                	shp_core_ctrl_03                ;	// 0x000c : ''
	UINT32                          	                 __rsvd_00[  12];	// 0x0010 ~ 0x003c
	SHP_PAT_GEN_CTRL_00             	shp_pat_gen_ctrl_00             ;	// 0x0040 : ''
	UINT32                          	                 __rsvd_01[   7];	// 0x0044 ~ 0x005c
	SHP_HTI_CTRL_00                 	shp_hti_ctrl_00                 ;	// 0x0060 : ''
	SHP_HTI_CTRL_01                 	shp_hti_ctrl_01                 ;	// 0x0064 : ''
	UINT32                          	                 __rsvd_02[   2];	// 0x0068 ~ 0x006c
	SHP_HTI_WIN_CTRL_00             	shp_hti_win_ctrl_00             ;	// 0x0070 : ''
	SHP_HTI_WIN_CTRL_01             	shp_hti_win_ctrl_01             ;	// 0x0074 : ''
	SHP_HTI_WIN_CTRL_02             	shp_hti_win_ctrl_02             ;	// 0x0078 : ''
	SHP_HTI_WIN_CTRL_03             	shp_hti_win_ctrl_03             ;	// 0x007c : ''
	SHP_HTI_WIN_CTRL_04             	shp_hti_win_ctrl_04             ;	// 0x0080 : ''
	UINT32                          	                 __rsvd_03[   3];	// 0x0084 ~ 0x008c
	SHP_VTI_CTRL_00                 	shp_vti_ctrl_00                 ;	// 0x0090 : ''
	UINT32                          	                 __rsvd_04[   3];	// 0x0094 ~ 0x009c
	SHP_LTI_CTRL_00                 	shp_lti_ctrl_00                 ;	// 0x00a0 : ''
	SHP_LTI_CTRL_01                 	shp_lti_ctrl_01                 ;	// 0x00a4 : ''
	UINT32                          	                 __rsvd_05[  22];	// 0x00a8 ~ 0x00fc
	SHP_DJ_CTRL_00                  	shp_dj_ctrl_00                  ;	// 0x0100 : ''
	SHP_DJ_CTRL_01                  	shp_dj_ctrl_01                  ;	// 0x0104 : ''
	SHP_DJ_CTRL_02                  	shp_dj_ctrl_02                  ;	// 0x0108 : ''
	SHP_DJ_CTRL_03                  	shp_dj_ctrl_03                  ;	// 0x010c : ''
	UINT32                          	                 __rsvd_06[   4];	// 0x0110 ~ 0x011c
	SHP_DB_CTRL_00                  	shp_db_ctrl_00                  ;	// 0x0120 : ''
	SHP_DB_CTRL_01                  	shp_db_ctrl_01                  ;	// 0x0124 : ''
	UINT32                          	                 __rsvd_07[   6];	// 0x0128 ~ 0x013c
	SHP_DJ_WIN_CTRL_00              	shp_dj_win_ctrl_00              ;	// 0x0140 : ''
	SHP_DJ_WIN_CTRL_01              	shp_dj_win_ctrl_01              ;	// 0x0144 : ''
	SHP_DJ_WIN_CTRL_02              	shp_dj_win_ctrl_02              ;	// 0x0148 : ''
	SHP_DJ_WIN_CTRL_03              	shp_dj_win_ctrl_03              ;	// 0x014c : ''
	SHP_DJ_WIN_CTRL_04              	shp_dj_win_ctrl_04              ;	// 0x0150 : ''
	UINT32                          	                 __rsvd_08[  27];	// 0x0154 ~ 0x01bc
	SHP_CC_CTRL_00                  	shp_cc_ctrl_00                  ;	// 0x01c0 : ''
	SHP_CC_CTRL_01                  	shp_cc_ctrl_01                  ;	// 0x01c4 : ''
	UINT32                          	                 __rsvd_09[  14];	// 0x01c8 ~ 0x01fc
	UINT32                          	shp_core_stat_00                ;	// 0x0200 : ''
	SHP_CORE_STAT_01                	shp_core_stat_01                ;	// 0x0204 : ''
	SHP_CORE_STAT_02                	shp_core_stat_02                ;	// 0x0208 : ''
	SHP_CORE_STAT_03                	shp_core_stat_03                ;	// 0x020c : ''
	SHP_CORE_STAT_04                	shp_core_stat_04                ;	// 0x0210 : ''
	SHP_CORE_STAT_05                	shp_core_stat_05                ;	// 0x0214 : ''
	UINT32                          	                 __rsvd_10[  54];	// 0x0218 ~ 0x02ec
	UINT32                          	shp_fsw_ctrl_00                 ;	// 0x02f0 : ''
	UINT32                          	shp_fsw_ctrl_01                 ;	// 0x02f4 : ''
	UINT32                          	shp_fsw_ctrl_02                 ;	// 0x02f8 : ''
	UINT32                          	shp_fsw_ctrl_03                 ;	// 0x02fc : ''
}
OSD_SHP_M19_REG_T;

/* 38 regs, 38 types */

/* 38 regs, 38 types in Total*/

/* from 'M16P3-A0_PQE_OSD_SHP_reg_man.csv' 20180327 20:19:41 KST by getregs v2.9 */

/*
 * @{
 * Naming for register pointer.
 * g_osd_shp_m19_reg : real register of AFBC0_CTRL.
 * g_osd_shp_m19_reg_shadow     : shadow register.
 *
 * @def OSD_SHP_RdFL: Read  FLushing : Shadow <- Real.
 * @def OSD_SHP_WrFL: Write FLushing : Shadow -> Real.
 * @def OSD_SHP_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def OSD_SHP_Wr  : Write whole register(UINT32) from Shadow register.
 * @def OSD_SHP_Rd01 ~ OSD_SHP_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def OSD_SHP_Wr01 ~ OSD_SHP_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define OSD_SHP_RdFL(_r)			((g_osd_shp_m19_reg_shadow->_r)=(g_osd_shp_m19_reg->_r))
#define OSD_SHP_WrFL(_r)			((g_osd_shp_m19_reg->_r)=(g_osd_shp_m19_reg_shadow->_r))

#define OSD_SHP_Rd(_r)			*((UINT32*)(&(g_osd_shp_m19_reg_shadow->_r)))
#define OSD_SHP_Wr(_r,_v)			((OSD_SHP_Rd(_r))=((UINT32)(_v)))

#define OSD_SHP_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
								} while(0)

#define OSD_SHP_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
								} while(0)

#define OSD_SHP_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
								} while(0)

#define OSD_SHP_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
								} while(0)

#define OSD_SHP_Rd05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
								} while(0)

#define OSD_SHP_Rd06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
								} while(0)

#define OSD_SHP_Rd07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
								} while(0)

#define OSD_SHP_Rd08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
								} while(0)

#define OSD_SHP_Rd09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
								} while(0)

#define OSD_SHP_Rd10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
								} while(0)

#define OSD_SHP_Rd11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
								} while(0)

#define OSD_SHP_Rd12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
									(_v12) = (g_osd_shp_m19_reg_shadow->_r._f12);				\
								} while(0)

#define OSD_SHP_Rd13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
									(_v12) = (g_osd_shp_m19_reg_shadow->_r._f12);				\
									(_v13) = (g_osd_shp_m19_reg_shadow->_r._f13);				\
								} while(0)

#define OSD_SHP_Rd14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
									(_v12) = (g_osd_shp_m19_reg_shadow->_r._f12);				\
									(_v13) = (g_osd_shp_m19_reg_shadow->_r._f13);				\
									(_v14) = (g_osd_shp_m19_reg_shadow->_r._f14);				\
								} while(0)

#define OSD_SHP_Rd15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
									(_v12) = (g_osd_shp_m19_reg_shadow->_r._f12);				\
									(_v13) = (g_osd_shp_m19_reg_shadow->_r._f13);				\
									(_v14) = (g_osd_shp_m19_reg_shadow->_r._f14);				\
									(_v15) = (g_osd_shp_m19_reg_shadow->_r._f15);				\
								} while(0)

#define OSD_SHP_Rd16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(_v01) = (g_osd_shp_m19_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_shp_m19_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_shp_m19_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_shp_m19_reg_shadow->_r._f04);				\
									(_v05) = (g_osd_shp_m19_reg_shadow->_r._f05);				\
									(_v06) = (g_osd_shp_m19_reg_shadow->_r._f06);				\
									(_v07) = (g_osd_shp_m19_reg_shadow->_r._f07);				\
									(_v08) = (g_osd_shp_m19_reg_shadow->_r._f08);				\
									(_v09) = (g_osd_shp_m19_reg_shadow->_r._f09);				\
									(_v10) = (g_osd_shp_m19_reg_shadow->_r._f10);				\
									(_v11) = (g_osd_shp_m19_reg_shadow->_r._f11);				\
									(_v12) = (g_osd_shp_m19_reg_shadow->_r._f12);				\
									(_v13) = (g_osd_shp_m19_reg_shadow->_r._f13);				\
									(_v14) = (g_osd_shp_m19_reg_shadow->_r._f14);				\
									(_v15) = (g_osd_shp_m19_reg_shadow->_r._f15);				\
									(_v16) = (g_osd_shp_m19_reg_shadow->_r._f16);				\
								} while(0)


#define OSD_SHP_Wr01(_r,_f01,_v01)													\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
								} while(0)

#define OSD_SHP_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
								} while(0)

#define OSD_SHP_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
								} while(0)

#define OSD_SHP_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
								} while(0)

#define OSD_SHP_Wr05(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05)													\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
								} while(0)

#define OSD_SHP_Wr06(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06)										\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
								} while(0)

#define OSD_SHP_Wr07(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07)								\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
								} while(0)

#define OSD_SHP_Wr08(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08)					\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
								} while(0)

#define OSD_SHP_Wr09(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09)													\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
								} while(0)

#define OSD_SHP_Wr10(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10)										\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
								} while(0)

#define OSD_SHP_Wr11(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11)								\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
								} while(0)

#define OSD_SHP_Wr12(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12)					\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
									(g_osd_shp_m19_reg_shadow->_r._f12) = (_v12);				\
								} while(0)

#define OSD_SHP_Wr13(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13)													\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
									(g_osd_shp_m19_reg_shadow->_r._f12) = (_v12);				\
									(g_osd_shp_m19_reg_shadow->_r._f13) = (_v13);				\
								} while(0)

#define OSD_SHP_Wr14(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14)										\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
									(g_osd_shp_m19_reg_shadow->_r._f12) = (_v12);				\
									(g_osd_shp_m19_reg_shadow->_r._f13) = (_v13);				\
									(g_osd_shp_m19_reg_shadow->_r._f14) = (_v14);				\
								} while(0)

#define OSD_SHP_Wr15(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15)								\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
									(g_osd_shp_m19_reg_shadow->_r._f12) = (_v12);				\
									(g_osd_shp_m19_reg_shadow->_r._f13) = (_v13);				\
									(g_osd_shp_m19_reg_shadow->_r._f14) = (_v14);				\
									(g_osd_shp_m19_reg_shadow->_r._f15) = (_v15);				\
								} while(0)

#define OSD_SHP_Wr16(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04,					\
					_f05,_v05,_f06,_v06,_f07,_v07,_f08,_v08,					\
					_f09,_v09,_f10,_v10,_f11,_v11,_f12,_v12,					\
					_f13,_v13,_f14,_v14,_f15,_v15,_f16,_v16)					\
								do { 											\
									(g_osd_shp_m19_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_shp_m19_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_shp_m19_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_shp_m19_reg_shadow->_r._f04) = (_v04);				\
									(g_osd_shp_m19_reg_shadow->_r._f05) = (_v05);				\
									(g_osd_shp_m19_reg_shadow->_r._f06) = (_v06);				\
									(g_osd_shp_m19_reg_shadow->_r._f07) = (_v07);				\
									(g_osd_shp_m19_reg_shadow->_r._f08) = (_v08);				\
									(g_osd_shp_m19_reg_shadow->_r._f09) = (_v09);				\
									(g_osd_shp_m19_reg_shadow->_r._f10) = (_v10);				\
									(g_osd_shp_m19_reg_shadow->_r._f11) = (_v11);				\
									(g_osd_shp_m19_reg_shadow->_r._f12) = (_v12);				\
									(g_osd_shp_m19_reg_shadow->_r._f13) = (_v13);				\
									(g_osd_shp_m19_reg_shadow->_r._f14) = (_v14);				\
									(g_osd_shp_m19_reg_shadow->_r._f15) = (_v15);				\
									(g_osd_shp_m19_reg_shadow->_r._f16) = (_v16);				\
								} while(0)

/** @} *//* end of macro documentation */

extern volatile OSD_SHP_M19_REG_T*	g_osd_shp_m19_reg;
extern OSD_SHP_M19_REG_T*  			g_osd_shp_m19_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'M19_PQE_OSD_SHP_reg_man.csv' 20170609 18:24:26 KST by getregs v2.9 */
