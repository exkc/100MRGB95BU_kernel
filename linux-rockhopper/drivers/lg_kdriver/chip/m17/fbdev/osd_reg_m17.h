/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2013 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/*
 *
 *  #MOD# register details. ( used only within kdriver )
 *
 *  author     user name (user_name@lge.com)
 *  version    1.0
 *  date       2010.xx.xx
 *
 */
#ifndef __OSD_REG_M17_H__
#define __OSD_REG_M17_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/
#define USE_OSD_REG_GROUP

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
	0x0000 osd_status_mon_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_cfg              : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_status_mon_osd_sel          : 2,	//  4: 5
	                                :10,	//  6:15 reserved
	scaler_status_th                :15,	// 16:30
	status_mon_datab_sel            : 1;	//    31
} OSD_STATUS_MON_CFG;

/*-----------------------------------------------------------------------------
	0x0004 osd_status_mon_pos ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_ypos             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_status_mon_xpos             :12;	// 16:27
} OSD_STATUS_MON_POS;

/*-----------------------------------------------------------------------------
	0x0008 osd_status_version ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_version              ;   	// 31: 0
} OSD_STATUS_VERSION;

/*-----------------------------------------------------------------------------
	0x000c osd_status_mixer_line ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mixer_line           :12,	//  0:11
	reg_status_pic_init_count       : 4,	// 12:15
	reg_60hz_status_mixer_line      :12,	// 16:27
	reg_60hz_status_pic_init_count  : 4;	// 28:31
} OSD_STATUS_MIXER_LINE;

/*-----------------------------------------------------------------------------
	0x0010~0x003F osd_status_mon_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data	            ;   	// 31: 0
} OSDX_STATUS_MON_DATA;

/*-----------------------------------------------------------------------------
	0x0040 osd_common_plte_sel ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lm_mode_osd01               : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_lm_mode_osd23               : 1,	//     4
	                                :11,	//  5:15 reserved
	reg_common_plte_sel             : 3,	// 16:18
	                                : 1,	//    19 reserved
	reg_sel_sosd_sync               : 6;	// 20:25
} OSD_COMMON_PLTE_SEL;

/*-----------------------------------------------------------------------------
	0x0044 osd_common_ctrl_irq ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_ctrl_irq_clear_osd0  : 1,	//     0
	reg_common_ctrl_irq_clear_osd1  : 1,	//     1
	reg_common_ctrl_irq_clear_osd2  : 1,	//     2
	reg_common_ctrl_irq_clear_osd3  : 1,	//     3
	reg_common_ctrl_irq_clear_osd4  : 1,	//     4
	reg_common_ctrl_irq_clear_osd5  : 1,	//     5
	reg_common_ctrl_irq_clear_osd6  : 1,	//     6
	reg_common_ctrl_irq_clear_osd7  : 1,	//     7
	reg_common_ctrl_irq_clear_bosd  : 1,	//     8
	reg_common_ctrl_irq_clear_sosd  : 1,	//     9
	                                : 6,	// 10:15 reserved
	reg_common_ctrl_irq_en_osd0     : 1,	//    16
	reg_common_ctrl_irq_en_osd1     : 1,	//    17
	reg_common_ctrl_irq_en_osd2     : 1,	//    18
	reg_common_ctrl_irq_en_osd3     : 1,	//    19
	reg_common_ctrl_irq_en_osd4     : 1,	//    20
	reg_common_ctrl_irq_en_osd5     : 1,	//    21
	reg_common_ctrl_irq_en_osd6     : 1,	//    22
	reg_common_ctrl_irq_en_osd7     : 1,	//    23
	reg_common_ctrl_irq_en_mixer_bos: 1,	//    24
	reg_common_ctrl_irq_en_mixer_sos: 1;	//    25
} OSD_COMMON_CTRL_IRQ;

/*-----------------------------------------------------------------------------
	0x0048 osd_common_ctrl_pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_pic_start_sel        : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_common_pic_init_sel         : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_common_self_init_src_sel    : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_common_60hz_init_src_sel    : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_common_2nd_pic_init_line    :12,	// 16:27
	reg_common_2nd_pic_init_en      : 1;	//    28
} OSD_COMMON_CTRL_PIC_INIT;

/*-----------------------------------------------------------------------------
	0x004c osd_common_ctrl_pic_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_pic_init_timer       ;   	// 31: 0
} OSD_COMMON_CTRL_PIC_TIMER;

/*-----------------------------------------------------------------------------
	0x0050 ~ 0x006f osdx_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSDX_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0070 osd_common_ctrl_osd_sr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_osd_sr_detour_en            : 1;	//    31
} OSD_COMMON_CTRL_OSD_SR;

/*-----------------------------------------------------------------------------
	0x0080 ctrl_sosd_mixer_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_disp_size_h            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_sosd_disp_size_w            :13;	// 16:28
} CTRL_SOSD_MIXER_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0084 ctrl_sosd_mixer_output ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_out_b                 : 8,	//  0: 7
	reg_mixer_out_g                 : 8,	//  8:15
	reg_mixer_out_r                 : 8,	// 16:23
	reg_mixer_out_fpr_mask_en       : 1,	//    24
	reg_mixer_out_fpr_mask_odd      : 1,	//    25
	                                : 2,	// 26:27 reserved
	reg_mixer_out_en                : 1,	//    28
	reg_mixer_out_valid_en          : 1,	//    29
	reg_mixer_out_vid_de_only       : 1,	//    30
	reg_mixer_out_vid_init_en       : 1;	//    31
} CTRL_SOSD_MIXER_OUTPUT;

/*-----------------------------------------------------------------------------
	0x0088 ctrl_sosd_mixer_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd3_mixer_awb_b            : 1,	//     0
	reg_osd3_mixer_awb_g            : 1,	//     1
	reg_osd3_mixer_awb_r            : 1,	//     2
	                                : 1,	//     3 reserved
	reg_osd2_mixer_awb_b            : 1,	//     4
	reg_osd2_mixer_awb_g            : 1,	//     5
	reg_osd2_mixer_awb_r            : 1,	//     6
	                                : 1,	//     7 reserved
	reg_osd1_mixer_awb_b            : 1,	//     8
	reg_osd1_mixer_awb_g            : 1,	//     9
	reg_osd1_mixer_awb_r            : 1,	//    10
	                                : 1,	//    11 reserved
	reg_osd0_mixer_awb_b            : 1,	//    12
	reg_osd0_mixer_awb_g            : 1,	//    13
	reg_osd0_mixer_awb_r            : 1;	//    14
} CTRL_SOSD_MIXER_AWB;

/*-----------------------------------------------------------------------------
	0x0090 ctrl_sosd_mixer_ctrl_alpha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ctrl_video_alhpa            : 8,	//  0: 7
	                                :23,	//  8:30 reserved
	reg_alpha_div_off               : 1;	//    31
} CTRL_SOSD_MIXER_CTRL_ALPHA;

/*-----------------------------------------------------------------------------
	0x0094 ctrl_sosd_mixer_force_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_coc_mode                    : 8,	//  0: 7
	                                :22,	//  8:29 reserved
	reg_coc_en                      : 1,	//    30
	reg_result_force_en             : 1;	//    31
} CTRL_SOSD_MIXER_FORCE_CTRL0;

/*-----------------------------------------------------------------------------
	0x0098 ctrl_sosd_mixer_force_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_force_b                     : 8,	//  0: 7
	reg_force_g                     : 8,	//  8:15
	reg_force_r                     : 8,	// 16:23
	reg_force_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_FORCE_CTRL1;

/*-----------------------------------------------------------------------------
	0x009c ctrl_sosd_mixer_hole ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_en                         : 1,	//     0
	osd0_hole_sel                   : 3,	//  1: 3
	osd1_en                         : 1,	//     4
	osd1_hole_sel                   : 3,	//  5: 7
	osd2_en                         : 1,	//     8
	osd2_hole_sel                   : 3,	//  9:11
	osd3_en                         : 1,	//    12
	osd3_hole_sel                   : 3,	// 13:15
	osd4_en                         : 1,	//    16
	osd4_hole_sel                   : 3,	// 17:19
	osd5_en                         : 1,	//    20
	osd5_hole_sel                   : 3,	// 21:23
	osd6_en                         : 1,	//    24
	osd6_hole_sel                   : 3,	// 25:27
	osd7_en                         : 1,	//    28
	osd7_hole_sel                   : 3;	// 29:31
} CTRL_SOSD_MIXER_HOLE;

/*-----------------------------------------------------------------------------
	0x00a0 ctrl_sosd_mixer_mux0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_mux_v                 : 4,	//  0: 3
	reg_mixer_0_off                 : 1,	//     4
	reg_mixer_1_off                 : 1,	//     5
	reg_mixer_2_off                 : 1,	//     6
	reg_mixer_3_off                 : 1,	//     7
	reg_mixer_4_off                 : 1,	//     8
	reg_mixer_5_off                 : 1,	//     9
	reg_mixer_6_off                 : 1,	//    10
	reg_mixer_7_off                 : 1,	//    11
	reg_mixer_v_off                 : 1,	//    12
	                                : 7,	// 13:19 reserved
	reg_mixer_tail                  : 2,	// 20:21
	                                : 2,	// 22:23 reserved
	reg_mixer_mux_a                 : 8;	// 24:31
} CTRL_SOSD_MIXER_MUX0;

/*-----------------------------------------------------------------------------
	0x00a4 ctrl_sosd_mixer_mux1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_mux_0                 : 4,	//  0: 3
	reg_mixer_mux_1                 : 4,	//  4: 7
	reg_mixer_mux_2                 : 4,	//  8:11
	reg_mixer_mux_3                 : 4,	// 12:15
	reg_mixer_mux_4                 : 4,	// 16:19
	reg_mixer_mux_5                 : 4,	// 20:23
	reg_mixer_mux_6                 : 4,	// 24:27
	reg_mixer_mux_7                 : 4;	// 28:31
} CTRL_SOSD_MIXER_MUX1;

/*-----------------------------------------------------------------------------
	0x00a8 ctrl_sosd_mixer_mux2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rsvd                            ;   	// 31: 0
} CTRL_SOSD_MIXER_MUX2;

/*-----------------------------------------------------------------------------
	0x00ac ctrl_sosd_mixer_mux3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_en                     : 1,	//     0
	window_1_en                     : 1,	//     1
	window_2_en                     : 1,	//     2
	                                : 5,	//  3: 7 reserved
	window_0_alpha                  : 8,	//  8:15
	window_1_alpha                  : 8,	// 16:23
	window_2_alpha                  : 8;	// 24:31
} CTRL_SOSD_MIXER_MUX3;

/*-----------------------------------------------------------------------------
	0x00b0 ctrl_sosd_mixer_mux4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX4;

/*-----------------------------------------------------------------------------
	0x00b4 ctrl_sosd_mixer_mux5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX5;

/*-----------------------------------------------------------------------------
	0x00b8 ctrl_sosd_mixer_mux6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX6;

/*-----------------------------------------------------------------------------
	0x00bc ctrl_sosd_mixer_mux7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX7;

/*-----------------------------------------------------------------------------
	0x00c0 ctrl_sosd_mixer_mux8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX8;

/*-----------------------------------------------------------------------------
	0x00c4 ctrl_sosd_mixer_mux9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX9;

/*-----------------------------------------------------------------------------
	0x00c8 ctrl_sosd_mixer_muxa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_w                     :13,	//  0:12
	reg_hole0_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole0_en                    : 1,	//    28
	reg_hole0_reverse_en            : 1;	//    29
} CTRL_SOSD_MIXER_MUXA;

/*-----------------------------------------------------------------------------
	0x00cc ctrl_sosd_mixer_muxb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_h                     :12,	//  0:11
	reg_hole0_y                     :12,	// 12:23
	reg_hole0_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXB;

/*-----------------------------------------------------------------------------
	0x00d0 ctrl_sosd_mixer_muxc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_w                     :13,	//  0:12
	reg_hole1_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole1_en                    : 1,	//    28
	reg_hole1_reverse_en            : 1;	//    29
} CTRL_SOSD_MIXER_MUXC;

/*-----------------------------------------------------------------------------
	0x00d4 ctrl_sosd_mixer_muxd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_h                     :12,	//  0:11
	reg_hole1_y                     :12,	// 12:23
	reg_hole1_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXD;

/*-----------------------------------------------------------------------------
	0x00d8 ctrl_sosd_mixer_muxe ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_w                     :13,	//  0:12
	reg_hole2_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole2_en                    : 1,	//    28
	reg_hole2_reverse_en            : 1;	//    29
} CTRL_SOSD_MIXER_MUXE;

/*-----------------------------------------------------------------------------
	0x00dc ctrl_sosd_mixer_muxf ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_h                     :12,	//  0:11
	reg_hole2_y                     :12,	// 12:23
	reg_hole2_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXF;

/*-----------------------------------------------------------------------------
	0x00e0 osd_common_sep_osd_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_sep_osd_hdr_en       : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_common_sep_osd_sync_sel     : 1,	//     4
	                                :26,	//  5:30 reserved
	reg_common_sep_osd_bypass       : 1;	//    31
} OSD_COMMON_SEP_OSD_CTRL;

/*-----------------------------------------------------------------------------
	0x00e4 osd_common_sep_osd_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_0                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR0;

/*-----------------------------------------------------------------------------
	0x00e8 osd_common_sep_osd_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_1                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR1;

/*-----------------------------------------------------------------------------
	0x00ec osd_common_sep_osd_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_2                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR2;

/*-----------------------------------------------------------------------------
	0x00f0 osd_common_sep_osd_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_3                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR3;

/*-----------------------------------------------------------------------------
	0x00f4 osd_common_sep_osd_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_4                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR4;

/*-----------------------------------------------------------------------------
	0x00f8 osd_common_sep_osd_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_5                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR5;

/*-----------------------------------------------------------------------------
	0x00fc osd_common_sep_osd_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_frc_hdr_6                   ;   	// 31: 0
} OSD_COMMON_SEP_OSD_HDR6;

/*-----------------------------------------------------------------------------
	0x0180 ctrl_bosd1_mixer_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bosd_disp_size_h            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_bosd_disp_size_w            :13;	// 16:28
} CTRL_BOSD_MIXER_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0184 ctrl_bosd1_mixer_output ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_out_b                 : 8,	//  0: 7
	reg_mixer_out_g                 : 8,	//  8:15
	reg_mixer_out_r                 : 8,	// 16:23
	reg_mixer_out_fpr_mask_en       : 1,	//    24
	reg_mixer_out_fpr_mask_odd      : 1,	//    25
	                                : 2,	// 26:27 reserved
	reg_mixer_out_en                : 1,	//    28
	reg_mixer_out_valid_en          : 1,	//    29
	reg_mixer_out_vid_de_only       : 1,	//    30
	reg_mixer_out_vid_init_en       : 1;	//    31
} CTRL_BOSD_MIXER_OUTPUT;

/*-----------------------------------------------------------------------------
	0x0188 ctrl_bosd1_mixer_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd3_mixer_awb_b            : 1,	//     0
	reg_osd3_mixer_awb_g            : 1,	//     1
	reg_osd3_mixer_awb_r            : 1,	//     2
	                                : 1,	//     3 reserved
	reg_osd2_mixer_awb_b            : 1,	//     4
	reg_osd2_mixer_awb_g            : 1,	//     5
	reg_osd2_mixer_awb_r            : 1,	//     6
	                                : 1,	//     7 reserved
	reg_osd1_mixer_awb_b            : 1,	//     8
	reg_osd1_mixer_awb_g            : 1,	//     9
	reg_osd1_mixer_awb_r            : 1,	//    10
	                                : 1,	//    11 reserved
	reg_osd0_mixer_awb_b            : 1,	//    12
	reg_osd0_mixer_awb_g            : 1,	//    13
	reg_osd0_mixer_awb_r            : 1;	//    14
} CTRL_BOSD_MIXER_AWB;

/*-----------------------------------------------------------------------------
	0x019c ctrl_bosd1_mixer_hole ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_en                         : 1,	//     0
	osd0_hole_sel                   : 3,	//  1: 3
	osd1_en                         : 1,	//     4
	osd1_hole_sel                   : 3,	//  5: 7
	osd2_en                         : 1,	//     8
	osd2_hole_sel                   : 3,	//  9:11
	osd3_en                         : 1,	//    12
	osd3_hole_sel                   : 3,	// 13:15
	osd4_en                         : 1,	//    16
	osd4_hole_sel                   : 3,	// 17:19
	osd5_en                         : 1,	//    20
	osd5_hole_sel                   : 3,	// 21:23
	osd6_en                         : 1,	//    24
	osd6_hole_sel                   : 3,	// 25:27
	osd7_en                         : 1,	//    28
	osd7_hole_sel                   : 3;	// 29:31
} CTRL_BOSD_MIXER_HOLE;

/*-----------------------------------------------------------------------------
	0x01a0 ctrl_bosd1_mixer_mux0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_mux_v                 : 4,	//  0: 3
	reg_mixer_0_off                 : 1,	//     4
	reg_mixer_1_off                 : 1,	//     5
	reg_mixer_2_off                 : 1,	//     6
	reg_mixer_3_off                 : 1,	//     7
	reg_mixer_4_off                 : 1,	//     8
	reg_mixer_5_off                 : 1,	//     9
	reg_mixer_6_off                 : 1,	//    10
	reg_mixer_7_off                 : 1,	//    11
	reg_mixer_v_off                 : 1,	//    12
	                                : 7,	// 13:19 reserved
	reg_mixer_tail                  : 2,	// 20:21
	                                : 2,	// 22:23 reserved
	reg_mixer_mux_a                 : 8;	// 24:31
} CTRL_BOSD_MIXER_MUX0;

/*-----------------------------------------------------------------------------
	0x01a4 ctrl_bosd1_mixer_mux1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_mux_0                 : 4,	//  0: 3
	reg_mixer_mux_1                 : 4,	//  4: 7
	reg_mixer_mux_2                 : 4,	//  8:11
	reg_mixer_mux_3                 : 4,	// 12:15
	reg_mixer_mux_4                 : 4,	// 16:19
	reg_mixer_mux_5                 : 4,	// 20:23
	reg_mixer_mux_6                 : 4,	// 24:27
	reg_mixer_mux_7                 : 4;	// 28:31
} CTRL_BOSD_MIXER_MUX1;

/*-----------------------------------------------------------------------------
	0x01a8 ctrl_bosd1_mixer_mux2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_rm_en                  : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd4_rm_en                  : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_osd0_rm_alpha               : 8,	//  8:15
	reg_osd4_rm_alpha               : 8,	// 16:23
	reg_video_rm_alpha              : 8;	// 24:31
} CTRL_BOSD_MIXER_MUX2;

/*-----------------------------------------------------------------------------
	0x01ac ctrl_bosd1_mixer_mux3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_en                     : 1,	//     0
	window_1_en                     : 1,	//     1
	window_2_en                     : 1,	//     2
	                                : 5,	//  3: 7 reserved
	window_0_alpha                  : 8,	//  8:15
	window_1_alpha                  : 8,	// 16:23
	window_2_alpha                  : 8;	// 24:31
} CTRL_BOSD_MIXER_MUX3;

/*-----------------------------------------------------------------------------
	0x01b0 ctrl_bosd1_mixer_mux4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_x                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX4;

/*-----------------------------------------------------------------------------
	0x01b4 ctrl_bosd1_mixer_mux5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_w                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX5;

/*-----------------------------------------------------------------------------
	0x01b8 ctrl_bosd1_mixer_mux6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_x                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX6;

/*-----------------------------------------------------------------------------
	0x01bc ctrl_bosd1_mixer_mux7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_w                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX7;

/*-----------------------------------------------------------------------------
	0x01c0 ctrl_bosd1_mixer_mux8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_x                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX8;

/*-----------------------------------------------------------------------------
	0x01c4 ctrl_bosd1_mixer_mux9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_w                      :13;	// 16:28
} CTRL_BOSD_MIXER_MUX9;

/*-----------------------------------------------------------------------------
	0x01c8 ctrl_bosd1_mixer_muxa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_w                     :13,	//  0:12
	reg_hole0_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole0_en                    : 1,	//    28
	reg_hole0_reverse_en            : 1;	//    29
} CTRL_BOSD_MIXER_MUXA;

/*-----------------------------------------------------------------------------
	0x01cc ctrl_bosd1_mixer_muxb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_h                     :12,	//  0:11
	reg_hole0_y                     :12,	// 12:23
	reg_hole0_a                     : 8;	// 24:31
} CTRL_BOSD_MIXER_MUXB;

/*-----------------------------------------------------------------------------
	0x01d0 ctrl_bosd1_mixer_muxc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_w                     :13,	//  0:12
	reg_hole1_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole1_en                    : 1,	//    28
	reg_hole1_reverse_en            : 1;	//    29
} CTRL_BOSD_MIXER_MUXC;

/*-----------------------------------------------------------------------------
	0x01d4 ctrl_bosd1_mixer_muxd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_h                     :12,	//  0:11
	reg_hole1_y                     :12,	// 12:23
	reg_hole1_a                     : 8;	// 24:31
} CTRL_BOSD_MIXER_MUXD;

/*-----------------------------------------------------------------------------
	0x01d8 ctrl_bosd1_mixer_muxe ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_w                     :13,	//  0:12
	reg_hole2_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole2_en                    : 1,	//    28
	reg_hole2_reverse_en            : 1;	//    29
} CTRL_BOSD_MIXER_MUXE;

/*-----------------------------------------------------------------------------
	0x01dc ctrl_bosd1_mixer_muxf ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_h                     :12,	//  0:11
	reg_hole2_y                     :12,	// 12:23
	reg_hole2_a                     : 8;	// 24:31
} CTRL_BOSD_MIXER_MUXF;

/*-----------------------------------------------------------------------------
	0x0200 osd0_ctrl_main ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_en                          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	osd_hdr_src_sel                 : 1,	//     4
	osd_unaligned_addr_en           : 1,	//     5
	osd_bitmap_only_mode_en         : 1,	//     6
	                                : 1,	//     7 reserved
	osd_v_reverse_en                : 1,	//     8
	                                : 3,	//  9:11 reserved
	osd_s3d_en                      : 1,	//    12
	osd_s3d_v_reverse_en            : 1,	//    13
	                                : 1,	//    14 reserved
	osd_req_urgency_en              : 1,	//    15
	osd_manual_line_inc             : 2,	// 16:17
	osd_manual_dlr                  : 2,	// 18:19
	                                : 4,	// 20:23 reserved
	osd_yuyv_mode_en                : 1,	//    24
	                                : 3,	// 25:27 reserved
	osd_hdr_ready_flag_en           : 1,	//    28
	osd_hdr_ready_flag              : 1;	//    29
} OSDX_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0204 osd0_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_base_addr                   ;   	// 31: 0
} OSDX_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x0208 osd0_ctrl_swap ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_bbs                         : 1,	//     0
	osd_bqws                        : 1,	//     1
	osd_bhws                        : 1,	//     2
	osd_bws                         : 1,	//     3
	osd_pbs                         : 1,	//     4
	osd_pqws                        : 1,	//     5
	osd_phws                        : 1,	//     6
	osd_pws                         : 1,	//     7
	osd_hbs                         : 1,	//     8
	osd_hqws                        : 1,	//     9
	osd_hhws                        : 1,	//    10
	osd_hws                         : 1;	//    11
} OSDX_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x020c osd0_ctrl_pdec ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_lfsr_seed                   :19,	//  0:18
	osd_pure_ck                     : 1,	//    19
	osd_round                       : 3,	// 20:22
	                                : 1,	//    23 reserved
	osd_ch_blue                     : 2,	// 24:25
	osd_ch_green                    : 2,	// 26:27
	osd_ch_red                      : 2,	// 28:29
	osd_ch_alpha                    : 2;	// 30:31
} OSDX_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0210 osd0_ctrl_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_crsr_v_x2_sel               : 1,	//     0
	reg_crsr_h_x2_sel               : 1,	//     1
	reg_osd_line_th_en              : 1,	//     2
	reg_osd_bilinear                : 1,	//     3
	reg_osd_odd_width_en            : 1,	//     4
	reg_osd_mode_32p                : 1,	//     5
	reg_osd_buf_mode_en             : 1,	//     6
	reg_osd_monitor_mode            : 1,	//     7
	reg_osd_sampling_mode           : 1,	//     8
	reg_crsr_v_x2_en                : 1,	//     9
	reg_osd_hsc_phase_off           : 9,	// 10:18
	reg_osd_vsc_phase_off           : 9,	// 19:27
	reg_osd_vcubic_filter_sel       : 2,	// 28:29
	reg_osd_post_buf_detour_en      : 1,	//    30
	reg_crsr_h_x2_en                : 1;	//    31
} OSDX_CTRL_SCALER;

/*-----------------------------------------------------------------------------
	0x0214 osd0_info_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	status_line_memory_ac           :16,	//  0:15
	status_line_memory_yg           :16;	// 16:31
} OSDX_INFO_SCALER;

/*-----------------------------------------------------------------------------
	0x0218 osd0_ctrl_path ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_direc                  : 1,	//     0
	                                : 3,	//  1: 3 reserved
	osd_ctrl_bosd_pos               : 1,	//     4
	                                : 3,	//  5: 7 reserved
	osd_ctrl_4to1                   : 1,	//     8
	                                : 7,	//  9:15 reserved
	reg_ctrl_path_width             :13;	// 16:28
} OSDX_CTRL_PATH;

/*-----------------------------------------------------------------------------
	0x021c osd0_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSDX_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0220 osd0_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSDX_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0224 osd0_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSDX_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0228 osd0_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSDX_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x022c osd0_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSDX_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0230 osd0_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSDX_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0234 osd0_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSDX_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0238 osd0_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSDX_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x023c osd0_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSDX_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0240 osd0_ctrl_sync0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_enable                 : 1,	//     0
	                                : 3,	//  1: 3 reserved
	osd_sync_hdouble_en             : 1,	//     4
	osd_sync_vdouble_en             : 1,	//     5
	osd_sync_v_pg_en                : 1,	//     6
	osd_sync_v_pg_sel               : 1,	//     7
	osd_sync_3dfp_en                : 1,	//     8
	                                : 1,	//     9 reserved
	osd_sync_3dtb_en                : 1,	//    10
	osd_sync_3dss_en                : 1,	//    11
	osd_sync_h_half_en              : 1,	//    12
	osd_sync_v_half_en              : 1,	//    13
	                                : 2,	// 14:15 reserved
	osd_sync_v_reverse              : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd_sync_tp_en                  : 1,	//    20
	osd_sync_tp_aa_en               : 1,	//    21
	                                : 2,	// 22:23 reserved
	osd_sync_tp_alpha               : 8;	// 24:31
} OSDX_CTRL_SYNC0;

/*-----------------------------------------------------------------------------
	0x0244 osd0_ctrl_sync1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_disp_h                 :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_disp_w                 :13;	// 16:28
} OSDX_CTRL_SYNC1;

/*-----------------------------------------------------------------------------
	0x0248 osd0_ctrl_sync2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_r_3d_disparity_value        : 8,	//  0: 7
	osd_r_3d_disparity_sign         : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd_l_3d_disparity_value        : 8,	// 16:23
	osd_l_3d_disparity_sign         : 1;	//    24
} OSDX_CTRL_SYNC2;

/*-----------------------------------------------------------------------------
	0x024c osd0_ctrl_sync3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_3d_blank               ;   	// 31: 0
} OSDX_CTRL_SYNC3;

/*-----------------------------------------------------------------------------
	0x0250 osd0_ctrl_sync4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_vact_video             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_vact_space             :12;	// 16:27
} OSDX_CTRL_SYNC4;

/*-----------------------------------------------------------------------------
	0x0254 osd0_ctrl_sync5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_reserved               ;   	// 31: 0
} OSDX_CTRL_SYNC5;

/*-----------------------------------------------------------------------------
	0x0258 osd0_bitmap_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cubic_coeff_0               :10,	//  0: 9
	reg_alpha_th                    : 8,	// 10:17
	                                : 9,	// 18:26 reserved
	reg_scaler_status_sel           : 1,	//    27
	reg_osd_sr_en                   : 1,	//    28
	reg_yc2rgb_sosd_csc_en          : 1,	//    29
	reg_yc2rgb_bosd_csc_en          : 1,	//    30
	reg_rgb2yc_csc_en               : 1;	//    31
} OSDX_BITMAP_CTRL0;

/*-----------------------------------------------------------------------------
	0x025c osd0_bitmap_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cubic_coeff_3               :10,	//  0: 9
	reg_cubic_coeff_2               :10,	// 10:19
	reg_cubic_coeff_1               :10;	// 20:29
} OSDX_BITMAP_CTRL1;

/*-----------------------------------------------------------------------------
	0x0260 osd0_vsp_bosd_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vspyc_en                    : 1,	//     0
	reg_graycolor_en                : 1,	//     1
	reg_coloronly_en                : 1,	//     2
	reg_cb_info                     : 1,	//     3
	reg_cr_info                     : 1,	//     4
	                                : 3,	//  5: 7 reserved
	r_center                        : 8,	//  8:15
	r_contrast                      :10;	// 16:25
} OSDX_VSP_BOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0264 osd0_vsp_bosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSDX_VSP_BOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0268 osd0_vsp_sosd_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vspyc_en                    : 1,	//     0
	reg_graycolor_en                : 1,	//     1
	reg_coloronly_en                : 1,	//     2
	reg_cb_info                     : 1,	//     3
	reg_cr_info                     : 1,	//     4
	                                : 3,	//  5: 7 reserved
	r_center                        : 8,	//  8:15
	r_contrast                      :10;	// 16:25
} OSDX_VSP_SOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x026c osd0_vsp_sosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSDX_VSP_SOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0270 osd0_status_alpha_apl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_apl_3                         : 8,	//  0: 7
	r_apl_2                         : 8,	//  8:15
	r_apl_1                         : 8,	// 16:23
	r_apl_0                         : 8;	// 24:31
} OSDX_STATUS_ALPHA_APL;

/*-----------------------------------------------------------------------------
	0x0274 osd0_status_alpha_cnt0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_cnt_1                         :16,	//  0:15
	r_cnt_0                         :16;	// 16:31
} OSDX_STATUS_ALPHA_CNT0;

/*-----------------------------------------------------------------------------
	0x0278 osd0_status_alpha_cnt1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_cnt_3                         :16,	//  0:15
	r_cnt_2                         :16;	// 16:31
} OSDX_STATUS_ALPHA_CNT1;


/*-----------------------------------------------------------------------------
	GROUP : OSDX_SEP_OSD_MIXER
------------------------------------------------------------------------------*/
typedef struct
{
	CTRL_SOSD_MIXER_DISP_SIZE       	ctrl_sosd_mixer_disp_size       ;	// 0x0080 : ''
	CTRL_SOSD_MIXER_OUTPUT          	ctrl_sosd_mixer_output          ;	// 0x0084 : ''
	CTRL_SOSD_MIXER_AWB             	ctrl_sosd_mixer_awb             ;	// 0x0088 : ''
	UINT32                          	                 __rsvd_01[   1];	// 0x008c
	CTRL_SOSD_MIXER_CTRL_ALPHA      	ctrl_sosd_mixer_ctrl_alpha      ;	// 0x0090 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL0     	ctrl_sosd_mixer_force_ctrl0     ;	// 0x0094 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL1     	ctrl_sosd_mixer_force_ctrl1     ;	// 0x0098 : ''
	CTRL_SOSD_MIXER_HOLE            	ctrl_sosd_mixer_hole            ;	// 0x009c : ''
	CTRL_SOSD_MIXER_MUX0            	ctrl_sosd_mixer_mux0            ;	// 0x00a0 : ''
	CTRL_SOSD_MIXER_MUX1            	ctrl_sosd_mixer_mux1            ;	// 0x00a4 : ''
	CTRL_SOSD_MIXER_MUX2            	ctrl_sosd_mixer_mux2            ;	// 0x00a8 : ''
	CTRL_SOSD_MIXER_MUX3            	ctrl_sosd_mixer_mux3            ;	// 0x00ac : ''
	CTRL_SOSD_MIXER_MUX4            	ctrl_sosd_mixer_mux4            ;	// 0x00b0 : ''
	CTRL_SOSD_MIXER_MUX5            	ctrl_sosd_mixer_mux5            ;	// 0x00b4 : ''
	CTRL_SOSD_MIXER_MUX6            	ctrl_sosd_mixer_mux6            ;	// 0x00b8 : ''
	CTRL_SOSD_MIXER_MUX7            	ctrl_sosd_mixer_mux7            ;	// 0x00bc : ''
	CTRL_SOSD_MIXER_MUX8            	ctrl_sosd_mixer_mux8            ;	// 0x00c0 : ''
	CTRL_SOSD_MIXER_MUX9            	ctrl_sosd_mixer_mux9            ;	// 0x00c4 : ''
	CTRL_SOSD_MIXER_MUXA            	ctrl_sosd_mixer_muxa            ;	// 0x00c8 : ''
	CTRL_SOSD_MIXER_MUXB            	ctrl_sosd_mixer_muxb            ;	// 0x00cc : ''
	CTRL_SOSD_MIXER_MUXC            	ctrl_sosd_mixer_muxc            ;	// 0x00d0 : ''
	CTRL_SOSD_MIXER_MUXD            	ctrl_sosd_mixer_muxd            ;	// 0x00d4 : ''
	CTRL_SOSD_MIXER_MUXE            	ctrl_sosd_mixer_muxe            ;	// 0x00d8 : ''
	CTRL_SOSD_MIXER_MUXF            	ctrl_sosd_mixer_muxf            ;	// 0x00dc : ''
}
OSDX_SEP_OSD_MIXER;

/*-----------------------------------------------------------------------------
	GROUP : OSDX_BLEND_OSD_MIXER
------------------------------------------------------------------------------*/
typedef struct
{
	CTRL_BOSD_MIXER_DISP_SIZE      	ctrl_bosd_mixer_disp_size      ;	// 0x0180 : ''
	CTRL_BOSD_MIXER_OUTPUT         	ctrl_bosd_mixer_output         ;	// 0x0184 : ''
	CTRL_BOSD_MIXER_AWB            	ctrl_bosd_mixer_awb            ;	// 0x0188 : ''
	UINT32                          	                 __rsvd_03[   4];	// 0x018c ~ 0x0198
	CTRL_BOSD_MIXER_HOLE           	ctrl_bosd_mixer_hole           ;	// 0x019c : ''
	CTRL_BOSD_MIXER_MUX0           	ctrl_bosd_mixer_mux0           ;	// 0x01a0 : ''
	CTRL_BOSD_MIXER_MUX1           	ctrl_bosd_mixer_mux1           ;	// 0x01a4 : ''
	CTRL_BOSD_MIXER_MUX2           	ctrl_bosd_mixer_mux2           ;	// 0x01a8 : ''
	CTRL_BOSD_MIXER_MUX3           	ctrl_bosd_mixer_mux3           ;	// 0x01ac : ''
	CTRL_BOSD_MIXER_MUX4           	ctrl_bosd_mixer_mux4           ;	// 0x01b0 : ''
	CTRL_BOSD_MIXER_MUX5           	ctrl_bosd_mixer_mux5           ;	// 0x01b4 : ''
	CTRL_BOSD_MIXER_MUX6           	ctrl_bosd_mixer_mux6           ;	// 0x01b8 : ''
	CTRL_BOSD_MIXER_MUX7           	ctrl_bosd_mixer_mux7           ;	// 0x01bc : ''
	CTRL_BOSD_MIXER_MUX8           	ctrl_bosd_mixer_mux8           ;	// 0x01c0 : ''
	CTRL_BOSD_MIXER_MUX9           	ctrl_bosd_mixer_mux9           ;	// 0x01c4 : ''
	CTRL_BOSD_MIXER_MUXA           	ctrl_bosd_mixer_muxa           ;	// 0x01c8 : ''
	CTRL_BOSD_MIXER_MUXB           	ctrl_bosd_mixer_muxb           ;	// 0x01cc : ''
	CTRL_BOSD_MIXER_MUXC           	ctrl_bosd_mixer_muxc           ;	// 0x01d0 : ''
	CTRL_BOSD_MIXER_MUXD           	ctrl_bosd_mixer_muxd           ;	// 0x01d4 : ''
	CTRL_BOSD_MIXER_MUXE           	ctrl_bosd_mixer_muxe           ;	// 0x01d8 : ''
	CTRL_BOSD_MIXER_MUXF           	ctrl_bosd_mixer_muxf           ;	// 0x01dc : ''
}
OSDX_BLEND_OSD_MIXER;

/*-----------------------------------------------------------------------------
	GROUP : OSDX_CTRL
------------------------------------------------------------------------------*/
typedef struct
{
	OSDX_CTRL_MAIN                  	osd_ctrl_main                  ;	// 0x0200 : ''
	OSDX_BASE_ADDR                  	osd_base_addr                  ;	// 0x0204 : ''
	OSDX_CTRL_SWAP                  	osd_ctrl_swap                  ;	// 0x0208 : ''
	OSDX_CTRL_PDEC                  	osd_ctrl_pdec                  ;	// 0x020c : ''
	OSDX_CTRL_SCALER                	osd_ctrl_scaler                ;	// 0x0210 : ''
	OSDX_INFO_SCALER                	osd_info_scaler                ;	// 0x0214 : ''
	OSDX_CTRL_PATH                  	osd_ctrl_path                  ;	// 0x0218 : ''
	OSDX_CTRL_CKEY_CTRL_0           	osd_ctrl_ckey_ctrl_0           ;	// 0x021c : ''

	OSDX_CTRL_HDR0                  	osd_ctrl_hdr0                  ;	// 0x0220 : ''
	OSDX_CTRL_HDR1                  	osd_ctrl_hdr1                  ;	// 0x0224 : ''
	OSDX_CTRL_HDR2                  	osd_ctrl_hdr2                  ;	// 0x0228 : ''
	OSDX_CTRL_HDR3                  	osd_ctrl_hdr3                  ;	// 0x022c : ''
	OSDX_CTRL_HDR4                  	osd_ctrl_hdr4                  ;	// 0x0230 : ''
	OSDX_CTRL_HDR5                  	osd_ctrl_hdr5                  ;	// 0x0234 : ''
	OSDX_CTRL_HDR6                  	osd_ctrl_hdr6                  ;	// 0x0238 : ''
	OSDX_CTRL_CKEY_CTRL_1           	osd_ctrl_ckey_ctrl_1           ;	// 0x023c : ''

	OSDX_CTRL_SYNC0                 	osd_ctrl_sync0                 ;	// 0x0240 : ''
	OSDX_CTRL_SYNC1                 	osd_ctrl_sync1                 ;	// 0x0244 : ''
	OSDX_CTRL_SYNC2                 	osd_ctrl_sync2                 ;	// 0x0248 : ''
	OSDX_CTRL_SYNC3                 	osd_ctrl_sync3                 ;	// 0x024c : ''
	OSDX_CTRL_SYNC4                 	osd_ctrl_sync4                 ;	// 0x0250 : ''
	OSDX_CTRL_SYNC5                 	osd_ctrl_sync5                 ;	// 0x0254 : ''

	OSDX_BITMAP_CTRL0               	osd_bitmap_ctrl0               ;	// 0x0258 : ''	(IMG only)
	OSDX_BITMAP_CTRL1               	osd_bitmap_ctrl1               ;	// 0x025c : ''	(IMG only)
	OSDX_VSP_BOSD_CTRL_0            	osd_vsp_bosd_ctrl_0            ;	// 0x0260 : ''	(IMG only)
	OSDX_VSP_BOSD_CTRL_1            	osd_vsp_bosd_ctrl_1            ;	// 0x0264 : ''	(IMG only)
	OSDX_VSP_SOSD_CTRL_0            	osd_vsp_sosd_ctrl_0            ;	// 0x0268 : ''	(IMG only)
	OSDX_VSP_SOSD_CTRL_1            	osd_vsp_sosd_ctrl_1            ;	// 0x026c : ''	(IMG only)
	OSDX_STATUS_ALPHA_APL           	osd_status_alpha_apl           ;	// 0x0270 : ''	(IMG only)
	OSDX_STATUS_ALPHA_CNT0          	osd_status_alpha_cnt0          ;	// 0x0274 : ''	(IMG only)
	OSDX_STATUS_ALPHA_CNT1          	osd_status_alpha_cnt1          ;	// 0x0278 : ''	(IMG only)

	UINT32                          	                 __rsvd[  1]	;	// 0x007c
}
OSDX_CTRL;

/*-----------------------------------------------------------------------------
	MAIN OSD_REG_T
------------------------------------------------------------------------------*/
typedef struct {
	OSD_STATUS_MON_CFG              	osd_status_mon_cfg              ;	// 0x0000 : ''
	OSD_STATUS_MON_POS              	osd_status_mon_pos              ;	// 0x0004 : ''
	OSD_STATUS_VERSION              	osd_status_version              ;	// 0x0008 : ''
	OSD_STATUS_MIXER_LINE           	osd_status_mixer_line           ;	// 0x000c : ''

	OSDX_STATUS_MON_DATA	           	osd_status_mon_data[12]         ;	// 0x0010 : ''

	OSD_COMMON_PLTE_SEL             	osd_common_plte_sel             ;	// 0x0040 : ''
	OSD_COMMON_CTRL_IRQ             	osd_common_ctrl_irq             ;	// 0x0044 : ''
	OSD_COMMON_CTRL_PIC_INIT        	osd_common_ctrl_pic_init        ;	// 0x0048 : ''
	OSD_COMMON_CTRL_PIC_TIMER       	osd_common_ctrl_pic_timer       ;	// 0x004c : ''

	OSDX_COMMON_DISP_SIZE           	osdx_common_disp_size[8]        ;	// 0x0050 : ''

	OSD_COMMON_CTRL_OSD_SR          	osd_common_ctrl_osd_sr          ;	// 0x0070 : ''
	UINT32                          	                 __rsvd_00[   3];	// 0x0074 ~ 0x007c

	/* S.OSD */
	OSDX_SEP_OSD_MIXER					osdx_sep_osd_mixer[1];

	/* SEP_CTRL */
	OSD_COMMON_SEP_OSD_CTRL         	osd_common_sep_osd_ctrl         ;	// 0x00e0 : ''
	OSD_COMMON_SEP_OSD_HDR0         	osd_common_sep_osd_hdr0         ;	// 0x00e4 : ''
	OSD_COMMON_SEP_OSD_HDR1         	osd_common_sep_osd_hdr1         ;	// 0x00e8 : ''
	OSD_COMMON_SEP_OSD_HDR2         	osd_common_sep_osd_hdr2         ;	// 0x00ec : ''
	OSD_COMMON_SEP_OSD_HDR3         	osd_common_sep_osd_hdr3         ;	// 0x00f0 : ''
	OSD_COMMON_SEP_OSD_HDR4         	osd_common_sep_osd_hdr4         ;	// 0x00f4 : ''
	OSD_COMMON_SEP_OSD_HDR5         	osd_common_sep_osd_hdr5         ;	// 0x00f8 : ''
	OSD_COMMON_SEP_OSD_HDR6         	osd_common_sep_osd_hdr6         ;	// 0x00fc : ''
	UINT32                          	                 __rsvd_02[  32];	// 0x0100 ~ 0x017c

	/* B.OSD */
	OSDX_BLEND_OSD_MIXER				osdx_blend_osd_mixer[1];


	UINT32                          	                 __rsvd_04[   8];	// 0x01e0 ~ 0x01fc

	OSDX_CTRL							osdx_ctrl[8];						// 0x2000 - OSD0, 0x400 - OSD4,

/* 133 regs, 133 types */

/* 133 regs, 133 types in Total*/

/* from 'M17-A0_PQE_OSD_reg_man.csv' 20160318 19:35:25 KST by getregs v2.9 */


#define OSDX_M17_Off(_g,_r)             ((UINT32)&(g_osd_m17_reg_shadow->_g._r) - (UINT32)(g_osd_m17_reg_shadow))

#define OSDX_M17_RdFL(_g,_r)            ((g_osd_m17_reg_shadow->_g._r)=(g_osd_m17_reg->_g._r))
#define OSDX_M17_WrFL(_g,_r)            ((g_osd_m17_reg->_g._r)=(g_osd_m17_reg_shadow->_g._r))

#define OSDX_M17_Rd(_g,_r)              *((UINT32*)(&(g_osd_m17_reg_shadow->_g._r)))
#define OSDX_M17_Wr(_g,_r,_v)           ((OSDX_M17_Rd(_g,_r))=((UINT32)(_v)))

#define OSDX_M17_Rd00(_g,_r,_f)         (g_osd_m17_reg_shadow->_g._r._f)
#define OSDX_M17_Rd01(_g,_r,_f01,_v01)  do {                                                \
                                            (_v01) = (g_osd_m17_reg_shadow->_g._r._f01);    \
                                        } while(0)
#define OSDX_M17_Wr01(_g,_r,_f01,_v01)  do {                                                \
                                            (g_osd_m17_reg_shadow->_g._r._f01) = (_v01);    \
                                        } while(0)
#define OSDX_M17_Wr02(_g,_r,_f01,_v01,_f02,_v02)    do {                                    \
                                            (g_osd_m17_reg_shadow->_g._r._f01) = (_v01);    \
                                            (g_osd_m17_reg_shadow->_g._r._f02) = (_v02);    \
                                        } while(0)

} OSD_M17_REG_T;

/*
 * @{
 * Naming for register pointer.
 * g_osd_m17_reg : real register of OSD.
 * g_osd_m17_reg_shadow     : shadow register.
 *
 * @def OSD_M17_RdFL: Read  FLushing : Shadow <- Real.
 * @def OSD_M17_WrFL: Write FLushing : Shadow -> Real.
 * @def OSD_M17_Rd  : Read  whole register(UINT32) from Shadow register.
 * @def OSD_M17_Wr  : Write whole register(UINT32) from Shadow register.
 * @def OSD_M17_Rd01 ~ OSD_M17_Rdnn: Read  given '01~nn' fields from Shadow register.
 * @def OSD_M17_Wr01 ~ OSD_M17_Wrnn: Write given '01~nn' fields to   Shadow register.
 * */
#define OSD_M17_RdFL(_r)			((g_osd_m17_reg_shadow->_r)=(g_osd_m17_reg->_r))
#define OSD_M17_WrFL(_r)			((g_osd_m17_reg->_r)=(g_osd_m17_reg_shadow->_r))

#define OSD_M17_Rd(_r)				*((UINT32*)(&(g_osd_m17_reg_shadow->_r)))
#define OSD_M17_Wr(_r,_v)			((OSD_M17_Rd(_r))=((UINT32)(_v)))

#define OSD_M17_Rd00(_r,_f)         (g_osd_m17_reg_shadow->_r._f)


#define OSD_M17_Rd01(_r,_f01,_v01)													\
								do { 											\
									(_v01) = (g_osd_m17_reg_shadow->_r._f01);				\
								} while(0)

#define OSD_M17_Rd02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(_v01) = (g_osd_m17_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_m17_reg_shadow->_r._f02);				\
								} while(0)

#define OSD_M17_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(_v01) = (g_osd_m17_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_m17_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_m17_reg_shadow->_r._f03);				\
								} while(0)

#define OSD_M17_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(_v01) = (g_osd_m17_reg_shadow->_r._f01);				\
									(_v02) = (g_osd_m17_reg_shadow->_r._f02);				\
									(_v03) = (g_osd_m17_reg_shadow->_r._f03);				\
									(_v04) = (g_osd_m17_reg_shadow->_r._f04);				\
								} while(0)

#define OSD_M17_Wr01(_r,_f01,_v01)													\
								do { 											\
									(g_osd_m17_reg_shadow->_r._f01) = (_v01);				\
								} while(0)

#define OSD_M17_Wr02(_r,_f01,_v01,_f02,_v02)										\
								do { 											\
									(g_osd_m17_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_m17_reg_shadow->_r._f02) = (_v02);				\
								} while(0)

#define OSD_M17_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)								\
								do { 											\
									(g_osd_m17_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_m17_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_m17_reg_shadow->_r._f03) = (_v03);				\
								} while(0)

#define OSD_M17_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)					\
								do { 											\
									(g_osd_m17_reg_shadow->_r._f01) = (_v01);				\
									(g_osd_m17_reg_shadow->_r._f02) = (_v02);				\
									(g_osd_m17_reg_shadow->_r._f03) = (_v03);				\
									(g_osd_m17_reg_shadow->_r._f04) = (_v04);				\
								} while(0)

/** @} *//* end of macro documentation */

extern volatile OSD_M17_REG_T*	g_osd_m17_reg;
extern OSD_M17_REG_T*			g_osd_m17_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif

/* from 'M17_PQE_OSD_reg_man.csv'  대한민국 표준시 by getregs v2.8 */
