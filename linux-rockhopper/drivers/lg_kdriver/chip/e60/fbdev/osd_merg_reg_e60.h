#ifndef __OSD_MERG_REG_E60_H_
#define __OSD_MERG_REG_E60_H_

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
	0x0000 sr_merge_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_en                 : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_sr_merge_demo_mode_en       : 1,	//     4
	reg_sr_merge_demo_mode          : 1,	//     5
	                                : 2,	//  6: 7 reserved
	reg_sr_merge_master_gain        : 8,	//  8:15
	reg_sr_merge_ti_en              : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_sr_merge_ti_gain            : 8,	// 20:27
	reg_sr_merge_debug_mode         : 3;	// 28:30
} SR_MERGE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0004 sr_merge_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_width              :16,	//  0:15
	reg_sr_merge_height             :16;	// 16:31
} SR_MERGE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0008 sr_merge_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_top_update_ctrl             : 5,	//  0: 4
	                                :23,	//  5:27 reserved
	reg_top_in_val_check            : 1,	//    28
	reg_top_in_rdy_check            : 1,	//    29
	reg_top_out_val_check           : 1,	//    30
	reg_top_out_rdy_check           : 1;	//    31
} SR_MERGE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0010 sr_merge_core0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_core0_width        :16,	//  0:15
	reg_sr_merge_core0_height       :16;	// 16:31
} SR_MERGE_CORE0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0014 sr_merge_core1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_core1_width        :16,	//  0:15
	reg_sr_merge_core1_height       :16;	// 16:31
} SR_MERGE_CORE1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0018 sr_merge_core2_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_core2_width        :16,	//  0:15
	reg_sr_merge_core2_height       :16;	// 16:31
} SR_MERGE_CORE2_CTRL_01;

/*-----------------------------------------------------------------------------
	0x001c sr_merge_core3_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_core3_width        :16,	//  0:15
	reg_sr_merge_core3_height       :16;	// 16:31
} SR_MERGE_CORE3_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0030 sr_merge_core0_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core0_start_pts_x0:16,	//  0:15
	reg_sr_merge_demo_core0_start_pts_y0:16;	// 16:31
} SR_MERGE_CORE0_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0034 sr_merge_core0_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core0_end_pts_x1:16,	//  0:15
	reg_sr_merge_demo_core0_end_pts_y1:16;	// 16:31
} SR_MERGE_CORE0_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0038 sr_merge_core1_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core1_start_pts_x0:16,	//  0:15
	reg_sr_merge_demo_core1_start_pts_y0:16;	// 16:31
} SR_MERGE_CORE1_CTRL_02;

/*-----------------------------------------------------------------------------
	0x003c sr_merge_core1_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core1_end_pts_x1:16,	//  0:15
	reg_sr_merge_demo_core1_end_pts_y1:16;	// 16:31
} SR_MERGE_CORE1_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0040 sr_merge_core2_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core2_start_pts_x0:16,	//  0:15
	reg_sr_merge_demo_core2_start_pts_y0:16;	// 16:31
} SR_MERGE_CORE2_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0044 sr_merge_core2_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core2_end_pts_x1:16,	//  0:15
	reg_sr_merge_demo_core2_end_pts_y1:16;	// 16:31
} SR_MERGE_CORE2_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0048 sr_merge_core3_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core3_start_pts_x0:16,	//  0:15
	reg_sr_merge_demo_core3_start_pts_y0:16;	// 16:31
} SR_MERGE_CORE3_CTRL_02;

/*-----------------------------------------------------------------------------
	0x004c sr_merge_core3_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sr_merge_demo_core3_end_pts_x1:16,	//  0:15
	reg_sr_merge_demo_core3_end_pts_y1:16;	// 16:31
} SR_MERGE_CORE3_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0080 sr_merge_ups_split_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ups_split_pmode_out         : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_ups_split_pmode_in          : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_ups_split_split_mode        : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	reg_ups_split_sync_mode         : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_ups_split_hsize             :13;	// 16:28
} SR_MERGE_UPS_SPLIT_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0084 sr_merge_ups_split_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ups_split_split_size        :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_ups_split_guardband         :13;	// 16:28
} SR_MERGE_UPS_SPLIT_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0088 sr_merge_ups_split_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ups_split_split_ctrl_02     ;   	// 31: 0
} SR_MERGE_UPS_SPLIT_CTRL_02;

/*-----------------------------------------------------------------------------
	0x008c sr_merge_ups_split_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ups_split_split_ctrl_03     ;   	// 31: 0
} SR_MERGE_UPS_SPLIT_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0090 sr_merge_res_split_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_res_split_pmode_out         : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_res_split_pmode_in          : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_res_split_split_mode        : 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	reg_res_split_sync_mode         : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_res_split_hsize             :13;	// 16:28
} SR_MERGE_RES_SPLIT_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0094 sr_merge_res_split_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_res_split_split_size        :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_res_split_guardband         :13;	// 16:28
} SR_MERGE_RES_SPLIT_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0098 sr_merge_res_split_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_res_split_split_ctrl_02     ;   	// 31: 0
} SR_MERGE_RES_SPLIT_CTRL_02;

/*-----------------------------------------------------------------------------
	0x009c sr_merge_res_split_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_res_split_split_ctrl_03     ;   	// 31: 0
} SR_MERGE_RES_SPLIT_CTRL_03;

/*-----------------------------------------------------------------------------
	0x00b0 sr_merge_merge_ctrl_00 ''
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
} SR_MERGE_MERGE_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00b4 sr_merge_merge_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_split_size            :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_merge_guardband             :13;	// 16:28
} SR_MERGE_MERGE_CTRL_01;

/*-----------------------------------------------------------------------------
	0x00b8 sr_merge_merge_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_fifo_th               : 9,	//  0: 8
	                                : 7,	//  9:15 reserved
	reg_merge_fifo_sel              : 3;	// 16:18
} SR_MERGE_MERGE_CTRL_02;

/*-----------------------------------------------------------------------------
	0x00bc sr_merge_merge_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_merge_ctrl_03               ;   	// 31: 0
} SR_MERGE_MERGE_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0100 sr_merge_spatial_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_residual_blur_en            : 1;	//     0
} SR_MERGE_SPATIAL_00;

/*-----------------------------------------------------------------------------
	0x0104 sr_merge_spatial_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_residual_blur_filt_00       : 4,	//  0: 3
	reg_residual_blur_filt_01       : 4,	//  4: 7
	reg_residual_blur_filt_02       : 4,	//  8:11
	reg_residual_blur_filt_10       : 4,	// 12:15
	reg_residual_blur_filt_11       : 4,	// 16:19
	reg_residual_blur_filt_12       : 4;	// 20:23
} SR_MERGE_SPATIAL_01;

/*-----------------------------------------------------------------------------
	0x0110 sr_merge_mmd_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mmd_en                      : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_mmd_tap_size                : 4;	//  4: 7
} SR_MERGE_MMD_00;

/*-----------------------------------------------------------------------------
	0x0114 sr_merge_mmd_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mmd_diff_lut_y0             : 8,	//  0: 7
	reg_mmd_diff_lut_x0             : 8,	//  8:15
	reg_mmd_diff_lut_y1             : 8,	// 16:23
	reg_mmd_diff_lut_x1             : 8;	// 24:31
} SR_MERGE_MMD_01;

/*-----------------------------------------------------------------------------
	0x0118 sr_merge_mmd_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mmd_diff_lut_y2             : 8,	//  0: 7
	reg_mmd_diff_lut_x2             : 8,	//  8:15
	reg_mmd_diff_lut_y3             : 8,	// 16:23
	reg_mmd_diff_lut_x3             : 8;	// 24:31
} SR_MERGE_MMD_02;

/*-----------------------------------------------------------------------------
	0x011c sr_merge_mmd_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mmd_diff_lut_y4             : 8,	//  0: 7
	reg_mmd_diff_lut_x4             : 8,	//  8:15
	reg_mmd_diff_lut_y5             : 8,	// 16:23
	reg_mmd_diff_lut_x5             : 8;	// 24:31
} SR_MERGE_MMD_03;

/*-----------------------------------------------------------------------------
	0x0120 sr_merge_mmd_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mmd_diff_lut_y6             : 8,	//  0: 7
	reg_mmd_diff_lut_x6             : 8,	//  8:15
	reg_mmd_diff_lut_y7             : 8,	// 16:23
	reg_mmd_diff_lut_x7             : 8;	// 24:31
} SR_MERGE_MMD_04;

/*-----------------------------------------------------------------------------
	0x0124 sr_merge_mmd_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ti_gain_lut_y0              : 8,	//  0: 7
	reg_ti_gain_lut_x0              : 8,	//  8:15
	reg_ti_gain_lut_y1              : 8,	// 16:23
	reg_ti_gain_lut_x1              : 8;	// 24:31
} SR_MERGE_MMD_05;

/*-----------------------------------------------------------------------------
	0x0128 sr_merge_mmd_06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ti_gain_lut_y2              : 8,	//  0: 7
	reg_ti_gain_lut_x2              : 8,	//  8:15
	reg_ti_gain_lut_y3              : 8,	// 16:23
	reg_ti_gain_lut_x3              : 8;	// 24:31
} SR_MERGE_MMD_06;

/*-----------------------------------------------------------------------------
	0x0130 sr_merge_sobel_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sobel_mode                  : 4;	//  0: 3
} SR_MERGE_SOBEL_00;

/*-----------------------------------------------------------------------------
	0x0134 sr_merge_sobel_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sobel_lut_y0                : 8,	//  0: 7
	reg_sobel_lut_x0                : 8,	//  8:15
	reg_sobel_lut_y1                : 8,	// 16:23
	reg_sobel_lut_x1                : 8;	// 24:31
} SR_MERGE_SOBEL_01;

/*-----------------------------------------------------------------------------
	0x0138 sr_merge_sobel_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sobel_lut_y2                : 8,	//  0: 7
	reg_sobel_lut_x2                : 8,	//  8:15
	reg_sobel_lut_y3                : 8,	// 16:23
	reg_sobel_lut_x3                : 8;	// 24:31
} SR_MERGE_SOBEL_02;

/*-----------------------------------------------------------------------------
	0x0140 sr_merge_nr_gain_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_nr_gain_en                  : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_nr_gain_th                  :10;	//  4:13
} SR_MERGE_NR_GAIN_00;

/*-----------------------------------------------------------------------------
	0x0144 sr_merge_nr_gain_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_nr_gain_lut_y0              : 8,	//  0: 7
	reg_nr_gain_lut_x0              : 8,	//  8:15
	reg_nr_gain_lut_y1              : 8,	// 16:23
	reg_nr_gain_lut_x1              : 8;	// 24:31
} SR_MERGE_NR_GAIN_01;

/*-----------------------------------------------------------------------------
	0x0148 sr_merge_nr_gain_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_nr_gain_lut_y2              : 8,	//  0: 7
	reg_nr_gain_lut_x2              : 8,	//  8:15
	reg_nr_gain_lut_y3              : 8,	// 16:23
	reg_nr_gain_lut_x3              : 8;	// 24:31
} SR_MERGE_NR_GAIN_02;

/*-----------------------------------------------------------------------------
	0x0150 sr_merge_blend_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blend_lut_en                : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_blend_flat_threshold        : 4,	//  4: 7
	                                :12,	//  8:19 reserved
	reg_blend_amp_weight            :12;	// 20:31
} SR_MERGE_BLEND_00;

/*-----------------------------------------------------------------------------
	0x0154 sr_merge_blend_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blend_lut_y1                :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_blend_lut_x1                :10;	// 16:25
} SR_MERGE_BLEND_01;

/*-----------------------------------------------------------------------------
	0x0158 sr_merge_blend_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blend_lut_y0                :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_blend_lut_x0                :10;	// 16:25
} SR_MERGE_BLEND_02;

/*-----------------------------------------------------------------------------
	0x015c sr_merge_blend_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blend_lut_y3                :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_blend_lut_x3                :10;	// 16:25
} SR_MERGE_BLEND_03;

/*-----------------------------------------------------------------------------
	0x0160 sr_merge_blend_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blend_lut_y2                :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_blend_lut_x2                :10;	// 16:25
} SR_MERGE_BLEND_04;

/*-----------------------------------------------------------------------------
	0x0200 sr_merge_core_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0204 sr_merge_core_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core_in_vert_cnt        :16,	//  0:15
	reg_mon_core_in_hori_cnt        :16;	// 16:31
} SR_MERGE_CORE_STAT_01;

/*-----------------------------------------------------------------------------
	0x0208 sr_merge_core_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core_out_vert_cnt       :16,	//  0:15
	reg_mon_core_out_hori_cnt       :16;	// 16:31
} SR_MERGE_CORE_STAT_02;

/*-----------------------------------------------------------------------------
	0x020c sr_merge_core_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core_fin_out_vert_cnt   :16,	//  0:15
	reg_mon_core_fin_in_vert_cnt    :16;	// 16:31
} SR_MERGE_CORE_STAT_03;

/*-----------------------------------------------------------------------------
	0x0210 sr_merge_core_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core_shp_i_sucfail      ;   	// 31: 0
} SR_MERGE_CORE_STAT_04;

/*-----------------------------------------------------------------------------
	0x0214 sr_merge_core_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core_shp_o_sucfail      ;   	// 31: 0
} SR_MERGE_CORE_STAT_05;

/*-----------------------------------------------------------------------------
	0x0218 sr_merge_core0_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x021c sr_merge_core0_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_in_vert_cnt       :16,	//  0:15
	reg_mon_core0_in_hori_cnt       :16;	// 16:31
} SR_MERGE_CORE0_STAT_01;

/*-----------------------------------------------------------------------------
	0x0220 sr_merge_core0_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_out_vert_cnt      :16,	//  0:15
	reg_mon_core0_out_hori_cnt      :16;	// 16:31
} SR_MERGE_CORE0_STAT_02;

/*-----------------------------------------------------------------------------
	0x0224 sr_merge_core0_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_fin_out_vert_cnt  :16,	//  0:15
	reg_mon_core0_fin_in_vert_cnt   :16;	// 16:31
} SR_MERGE_CORE0_STAT_03;

/*-----------------------------------------------------------------------------
	0x0228 sr_merge_core0_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_shp_i_sucfail     ;   	// 31: 0
} SR_MERGE_CORE0_STAT_04;

/*-----------------------------------------------------------------------------
	0x022c sr_merge_core0_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core0_shp_o_sucfail     ;   	// 31: 0
} SR_MERGE_CORE0_STAT_05;

/*-----------------------------------------------------------------------------
	0x0230 sr_merge_core1_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0234 sr_merge_core1_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_in_vert_cnt       :16,	//  0:15
	reg_mon_core1_in_hori_cnt       :16;	// 16:31
} SR_MERGE_CORE1_STAT_01;

/*-----------------------------------------------------------------------------
	0x0238 sr_merge_core1_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_out_vert_cnt      :16,	//  0:15
	reg_mon_core1_out_hori_cnt      :16;	// 16:31
} SR_MERGE_CORE1_STAT_02;

/*-----------------------------------------------------------------------------
	0x023c sr_merge_core1_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_fin_out_vert_cnt  :16,	//  0:15
	reg_mon_core1_fin_in_vert_cnt   :16;	// 16:31
} SR_MERGE_CORE1_STAT_03;

/*-----------------------------------------------------------------------------
	0x0240 sr_merge_core1_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_shp_i_sucfail     ;   	// 31: 0
} SR_MERGE_CORE1_STAT_04;

/*-----------------------------------------------------------------------------
	0x0244 sr_merge_core1_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core1_shp_o_sucfail     ;   	// 31: 0
} SR_MERGE_CORE1_STAT_05;

/*-----------------------------------------------------------------------------
	0x0248 sr_merge_core2_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x024c sr_merge_core2_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core2_in_vert_cnt       :16,	//  0:15
	reg_mon_core2_in_hori_cnt       :16;	// 16:31
} SR_MERGE_CORE2_STAT_01;

/*-----------------------------------------------------------------------------
	0x0250 sr_merge_core2_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core2_out_vert_cnt      :16,	//  0:15
	reg_mon_core2_out_hori_cnt      :16;	// 16:31
} SR_MERGE_CORE2_STAT_02;

/*-----------------------------------------------------------------------------
	0x0254 sr_merge_core2_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core2_fin_out_vert_cnt  :16,	//  0:15
	reg_mon_core2_fin_in_vert_cnt   :16;	// 16:31
} SR_MERGE_CORE2_STAT_03;

/*-----------------------------------------------------------------------------
	0x0258 sr_merge_core2_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core2_shp_i_sucfail     ;   	// 31: 0
} SR_MERGE_CORE2_STAT_04;

/*-----------------------------------------------------------------------------
	0x025c sr_merge_core2_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core2_shp_o_sucfail     ;   	// 31: 0
} SR_MERGE_CORE2_STAT_05;

/*-----------------------------------------------------------------------------
	0x0260 sr_merge_core3_stat_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0264 sr_merge_core3_stat_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core3_in_vert_cnt       :16,	//  0:15
	reg_mon_core3_in_hori_cnt       :16;	// 16:31
} SR_MERGE_CORE3_STAT_01;

/*-----------------------------------------------------------------------------
	0x0268 sr_merge_core3_stat_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core3_out_vert_cnt      :16,	//  0:15
	reg_mon_core3_out_hori_cnt      :16;	// 16:31
} SR_MERGE_CORE3_STAT_02;

/*-----------------------------------------------------------------------------
	0x026c sr_merge_core3_stat_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core3_fin_out_vert_cnt  :16,	//  0:15
	reg_mon_core3_fin_in_vert_cnt   :16;	// 16:31
} SR_MERGE_CORE3_STAT_03;

/*-----------------------------------------------------------------------------
	0x0270 sr_merge_core3_stat_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core3_shp_i_sucfail     ;   	// 31: 0
} SR_MERGE_CORE3_STAT_04;

/*-----------------------------------------------------------------------------
	0x0274 sr_merge_core3_stat_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mon_core3_shp_o_sucfail     ;   	// 31: 0
} SR_MERGE_CORE3_STAT_05;

/*-----------------------------------------------------------------------------
	0x0300 sr_merge_fsw_ctrl_00 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0304 sr_merge_fsw_ctrl_01 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0308 sr_merge_fsw_ctrl_02 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x030c sr_merge_fsw_ctrl_03 ''
------------------------------------------------------------------------------*/
/*	no field */

typedef struct {
	SR_MERGE_CTRL_00                	sr_merge_ctrl_00                ;	// 0x0000 : ''
	SR_MERGE_CTRL_01                	sr_merge_ctrl_01                ;	// 0x0004 : ''
	SR_MERGE_CTRL_02                	sr_merge_ctrl_02                ;	// 0x0008 : ''
	UINT32                          	                 __rsvd_00[   1];	// 0x000c
	SR_MERGE_CORE0_CTRL_01          	sr_merge_core0_ctrl_01          ;	// 0x0010 : ''
	SR_MERGE_CORE1_CTRL_01          	sr_merge_core1_ctrl_01          ;	// 0x0014 : ''
	SR_MERGE_CORE2_CTRL_01          	sr_merge_core2_ctrl_01          ;	// 0x0018 : ''
	SR_MERGE_CORE3_CTRL_01          	sr_merge_core3_ctrl_01          ;	// 0x001c : ''
	UINT32                          	                 __rsvd_01[   4];	// 0x0020 ~ 0x002c
	SR_MERGE_CORE0_CTRL_02          	sr_merge_core0_ctrl_02          ;	// 0x0030 : ''
	SR_MERGE_CORE0_CTRL_03          	sr_merge_core0_ctrl_03          ;	// 0x0034 : ''
	SR_MERGE_CORE1_CTRL_02          	sr_merge_core1_ctrl_02          ;	// 0x0038 : ''
	SR_MERGE_CORE1_CTRL_03          	sr_merge_core1_ctrl_03          ;	// 0x003c : ''
	SR_MERGE_CORE2_CTRL_02          	sr_merge_core2_ctrl_02          ;	// 0x0040 : ''
	SR_MERGE_CORE2_CTRL_03          	sr_merge_core2_ctrl_03          ;	// 0x0044 : ''
	SR_MERGE_CORE3_CTRL_02          	sr_merge_core3_ctrl_02          ;	// 0x0048 : ''
	SR_MERGE_CORE3_CTRL_03          	sr_merge_core3_ctrl_03          ;	// 0x004c : ''
	UINT32                          	                 __rsvd_02[  12];	// 0x0050 ~ 0x007c
	SR_MERGE_UPS_SPLIT_CTRL_00      	sr_merge_ups_split_ctrl_00      ;	// 0x0080 : ''
	SR_MERGE_UPS_SPLIT_CTRL_01      	sr_merge_ups_split_ctrl_01      ;	// 0x0084 : ''
	SR_MERGE_UPS_SPLIT_CTRL_02      	sr_merge_ups_split_ctrl_02      ;	// 0x0088 : ''
	SR_MERGE_UPS_SPLIT_CTRL_03      	sr_merge_ups_split_ctrl_03      ;	// 0x008c : ''
	SR_MERGE_RES_SPLIT_CTRL_00      	sr_merge_res_split_ctrl_00      ;	// 0x0090 : ''
	SR_MERGE_RES_SPLIT_CTRL_01      	sr_merge_res_split_ctrl_01      ;	// 0x0094 : ''
	SR_MERGE_RES_SPLIT_CTRL_02      	sr_merge_res_split_ctrl_02      ;	// 0x0098 : ''
	SR_MERGE_RES_SPLIT_CTRL_03      	sr_merge_res_split_ctrl_03      ;	// 0x009c : ''
	UINT32                          	                 __rsvd_03[   4];	// 0x00a0 ~ 0x00ac
	SR_MERGE_MERGE_CTRL_00          	sr_merge_merge_ctrl_00          ;	// 0x00b0 : ''
	SR_MERGE_MERGE_CTRL_01          	sr_merge_merge_ctrl_01          ;	// 0x00b4 : ''
	SR_MERGE_MERGE_CTRL_02          	sr_merge_merge_ctrl_02          ;	// 0x00b8 : ''
	SR_MERGE_MERGE_CTRL_03          	sr_merge_merge_ctrl_03          ;	// 0x00bc : ''
	UINT32                          	                 __rsvd_04[  16];	// 0x00c0 ~ 0x00fc
	SR_MERGE_SPATIAL_00             	sr_merge_spatial_00             ;	// 0x0100 : ''
	SR_MERGE_SPATIAL_01             	sr_merge_spatial_01             ;	// 0x0104 : ''
	UINT32                          	                 __rsvd_05[   2];	// 0x0108 ~ 0x010c
	SR_MERGE_MMD_00                 	sr_merge_mmd_00                 ;	// 0x0110 : ''
	SR_MERGE_MMD_01                 	sr_merge_mmd_01                 ;	// 0x0114 : ''
	SR_MERGE_MMD_02                 	sr_merge_mmd_02                 ;	// 0x0118 : ''
	SR_MERGE_MMD_03                 	sr_merge_mmd_03                 ;	// 0x011c : ''
	SR_MERGE_MMD_04                 	sr_merge_mmd_04                 ;	// 0x0120 : ''
	SR_MERGE_MMD_05                 	sr_merge_mmd_05                 ;	// 0x0124 : ''
	SR_MERGE_MMD_06                 	sr_merge_mmd_06                 ;	// 0x0128 : ''
	UINT32                          	                 __rsvd_06[   1];	// 0x012c
	SR_MERGE_SOBEL_00               	sr_merge_sobel_00               ;	// 0x0130 : ''
	SR_MERGE_SOBEL_01               	sr_merge_sobel_01               ;	// 0x0134 : ''
	SR_MERGE_SOBEL_02               	sr_merge_sobel_02               ;	// 0x0138 : ''
	UINT32                          	                 __rsvd_07[   1];	// 0x013c
	SR_MERGE_NR_GAIN_00             	sr_merge_nr_gain_00             ;	// 0x0140 : ''
	SR_MERGE_NR_GAIN_01             	sr_merge_nr_gain_01             ;	// 0x0144 : ''
	SR_MERGE_NR_GAIN_02             	sr_merge_nr_gain_02             ;	// 0x0148 : ''
	UINT32                          	                 __rsvd_08[   1];	// 0x014c
	SR_MERGE_BLEND_00               	sr_merge_blend_00               ;	// 0x0150 : ''
	SR_MERGE_BLEND_01               	sr_merge_blend_01               ;	// 0x0154 : ''
	SR_MERGE_BLEND_02               	sr_merge_blend_02               ;	// 0x0158 : ''
	SR_MERGE_BLEND_03               	sr_merge_blend_03               ;	// 0x015c : ''
	SR_MERGE_BLEND_04               	sr_merge_blend_04               ;	// 0x0160 : ''
	UINT32                          	                 __rsvd_09[  39];	// 0x0164 ~ 0x01fc
	UINT32                          	sr_merge_core_stat_00           ;	// 0x0200 : ''
	SR_MERGE_CORE_STAT_01           	sr_merge_core_stat_01           ;	// 0x0204 : ''
	SR_MERGE_CORE_STAT_02           	sr_merge_core_stat_02           ;	// 0x0208 : ''
	SR_MERGE_CORE_STAT_03           	sr_merge_core_stat_03           ;	// 0x020c : ''
	SR_MERGE_CORE_STAT_04           	sr_merge_core_stat_04           ;	// 0x0210 : ''
	SR_MERGE_CORE_STAT_05           	sr_merge_core_stat_05           ;	// 0x0214 : ''
	UINT32                          	sr_merge_core0_stat_00          ;	// 0x0218 : ''
	SR_MERGE_CORE0_STAT_01          	sr_merge_core0_stat_01          ;	// 0x021c : ''
	SR_MERGE_CORE0_STAT_02          	sr_merge_core0_stat_02          ;	// 0x0220 : ''
	SR_MERGE_CORE0_STAT_03          	sr_merge_core0_stat_03          ;	// 0x0224 : ''
	SR_MERGE_CORE0_STAT_04          	sr_merge_core0_stat_04          ;	// 0x0228 : ''
	SR_MERGE_CORE0_STAT_05          	sr_merge_core0_stat_05          ;	// 0x022c : ''
	UINT32                          	sr_merge_core1_stat_00          ;	// 0x0230 : ''
	SR_MERGE_CORE1_STAT_01          	sr_merge_core1_stat_01          ;	// 0x0234 : ''
	SR_MERGE_CORE1_STAT_02          	sr_merge_core1_stat_02          ;	// 0x0238 : ''
	SR_MERGE_CORE1_STAT_03          	sr_merge_core1_stat_03          ;	// 0x023c : ''
	SR_MERGE_CORE1_STAT_04          	sr_merge_core1_stat_04          ;	// 0x0240 : ''
	SR_MERGE_CORE1_STAT_05          	sr_merge_core1_stat_05          ;	// 0x0244 : ''
	UINT32                          	sr_merge_core2_stat_00          ;	// 0x0248 : ''
	SR_MERGE_CORE2_STAT_01          	sr_merge_core2_stat_01          ;	// 0x024c : ''
	SR_MERGE_CORE2_STAT_02          	sr_merge_core2_stat_02          ;	// 0x0250 : ''
	SR_MERGE_CORE2_STAT_03          	sr_merge_core2_stat_03          ;	// 0x0254 : ''
	SR_MERGE_CORE2_STAT_04          	sr_merge_core2_stat_04          ;	// 0x0258 : ''
	SR_MERGE_CORE2_STAT_05          	sr_merge_core2_stat_05          ;	// 0x025c : ''
	UINT32                          	sr_merge_core3_stat_00          ;	// 0x0260 : ''
	SR_MERGE_CORE3_STAT_01          	sr_merge_core3_stat_01          ;	// 0x0264 : ''
	SR_MERGE_CORE3_STAT_02          	sr_merge_core3_stat_02          ;	// 0x0268 : ''
	SR_MERGE_CORE3_STAT_03          	sr_merge_core3_stat_03          ;	// 0x026c : ''
	SR_MERGE_CORE3_STAT_04          	sr_merge_core3_stat_04          ;	// 0x0270 : ''
	SR_MERGE_CORE3_STAT_05          	sr_merge_core3_stat_05          ;	// 0x0274 : ''
	UINT32                          	                 __rsvd_10[  34];	// 0x0278 ~ 0x02fc
	UINT32                          	sr_merge_fsw_ctrl_00            ;	// 0x0300 : ''
	UINT32                          	sr_merge_fsw_ctrl_01            ;	// 0x0304 : ''
	UINT32                          	sr_merge_fsw_ctrl_02            ;	// 0x0308 : ''
	UINT32                          	sr_merge_fsw_ctrl_03            ;	// 0x030c : ''
}
OSD_MERG_E60_REG_T;
/* 81 regs, 81 types */

/* 81 regs, 81 types in Total*/

#define MERG_E60_Off(id,_r) 			((UINT64)&(g_osd_merg_e60_reg_shadow[id]->_r) - (UINT64)(g_osd_merg_e60_reg_shadow[id]))
#define MERG_E60_RdFL(id,_r)           ((g_osd_merg_e60_reg_shadow[id]->_r)=(g_osd_merg_e60_reg[id]->_r))
#ifdef FBDEV_E60_USE_REG_DEBUG
#define MERG_E60_WrFL(id,_r) \
								do { \
									FBDEV_E60_CMN_RegDebug((id==0)? CCO_OSD_MERG0_BASE:CCO_OSD_MERG1_BASE, MERG_E60_Off(id,_r), MERG_E60_Rd(id,_r)); \
						           ((g_osd_merg_e60_reg[id]->_r)=(g_osd_merg_e60_reg_shadow[id]->_r)); \
								} while(0)
#else
#define MERG_E60_WrFL(id,_r)           ((g_osd_merg_e60_reg[id]->_r)=(g_osd_merg_e60_reg_shadow[id]->_r))
#endif

#define MERG_E60_Rd(id,_r)             *((UINT32*)(&(g_osd_merg_e60_reg_shadow[id]->_r)))
#define MERG_E60_Wr(id,_r,_v)          ((MERG_E60_Rd(id,_r))=((UINT32)(_v)))

#define MERG_E60_Rd01(id,_r,_f01,_v01) \
                                do { \
                                    (_v01) = (g_osd_merg_e60_reg_shadow[id]->_r._f01); \
                                } while(0)

#define MERG_E60_Rd02(id,_r,_f01,_v01,_f02,_v02) \
                                do { \
                                    (_v01) = (g_osd_merg_e60_reg_shadow[id]->_r._f01); \
                                    (_v02) = (g_osd_merg_e60_reg_shadow[id]->_r._f02); \
                                } while(0)


#define MERG_E60_Wr01(id,_r,_f01,_v01) \
                                do { \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f01) = (_v01); \
                                } while(0)

#define MERG_E60_Wr02(id,_r,_f01,_v01,_f02,_v02) \
                                do { \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f01) = (_v01); \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f02) = (_v02); \
                                } while(0)
#define MERG_E60_Wr03(id,_r,_f01,_v01,_f02,_v02,_f03,_v03) \
                                do { \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f01) = (_v01); \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f02) = (_v02); \
                                    (g_osd_merg_e60_reg_shadow[id]->_r._f03) = (_v03); \
                                } while(0)

#define osdx_merg_y   0
#define osdx_merg_a   1

extern volatile OSD_MERG_E60_REG_T*  g_osd_merg_e60_reg[2];
extern OSD_MERG_E60_REG_T*           g_osd_merg_e60_reg_shadow[2];


#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'E60-A0_PQE_OSD_MERG_reg_man.csv' 20191216 21:25:50 KST by getregs v2.9 */
