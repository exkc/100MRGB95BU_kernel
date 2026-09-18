/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __OSD_MIF1_REG_O24_H__
#define __OSD_MIF1_REG_O24_H__

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

// *INDENT-OFF*

#if 0

/*-----------------------------------------------------------------------------
	0x0000 r_mif_osd0_gif_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_gif_disable                   : 1,	//     0
	r_gif_stvcnt_en                 : 1,	//     1
	                                : 2,	//  2: 3 reserved
	r_gif_status_sel                : 2,	//  4: 5
	                                :10,	//  6:15 reserved
	r_mif_mb_sel                    : 8;	// 16:23
} R_MIF_OSD0_GIF_EN;

/*-----------------------------------------------------------------------------
	0x0004 r_mif_osd0_reset ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mif_reset                     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	r_mif_reset_time_out_cnt        :12;	// 16:27
} R_MIF_OSD0_RESET;

/*-----------------------------------------------------------------------------
	0x0008 r_mif_osd0_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mif_fr_done_flag                : 8,	//  0: 7
	gif_stuck_svid                  : 4,	//  8:11
	gif_stuck_flag                  : 1;	//    12
} R_MIF_OSD0_STATUS;

/*-----------------------------------------------------------------------------
	0x000c r_mif_osd0_load ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mp01_load_pic_init            : 1,	//     0
	r_mp01_load_req_pri             : 1,	//     1
	r_mp01_load_req_stv             : 1,	//     2
	r_mp01_load_cmd_pri             : 1,	//     3
	r_mp01_load_cmd_pend            : 1,	//     4
	r_mp01_load_cmd_stride          : 1,	//     5
	r_mp01_load_cmd_saddr           : 1,	//     6
	r_mp01_load_fbcd                : 1,	//     7
	r_mp23_load_pic_init            : 1,	//     8
	r_mp23_load_req_pri             : 1,	//     9
	r_mp23_load_req_stv             : 1,	//    10
	r_mp23_load_cmd_pri             : 1,	//    11
	r_mp23_load_cmd_pend            : 1,	//    12
	r_mp23_load_cmd_stride          : 1,	//    13
	r_mp23_load_cmd_saddr           : 1,	//    14
	r_mp23_load_fbcd                : 1,	//    15
	r_mp45_load_pic_init            : 1,	//    16
	r_mp45_load_req_pri             : 1,	//    17
	r_mp45_load_req_stv             : 1,	//    18
	r_mp45_load_cmd_pri             : 1,	//    19
	r_mp45_load_cmd_pend            : 1,	//    20
	r_mp45_load_cmd_stride          : 1,	//    21
	r_mp45_load_cmd_saddr           : 1,	//    22
	r_mp45_load_fbcd                : 1,	//    23
	r_mp67_load_pic_init            : 1,	//    24
	r_mp67_load_req_pri             : 1,	//    25
	r_mp67_load_req_stv             : 1,	//    26
	r_mp67_load_cmd_pri             : 1,	//    27
	r_mp67_load_cmd_pend            : 1,	//    28
	r_mp67_load_cmd_stride          : 1,	//    29
	r_mp67_load_cmd_saddr           : 1,	//    30
	r_mp67_load_fbcd                : 1;	//    31
} R_MIF_OSD0_LOAD;

/*-----------------------------------------------------------------------------
	0x0010 r_mif_osd0_mb_status0_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mif_mb_status1                :16,	//  0:15
	r_mif_mb_status0                :16;	// 16:31
} R_MIF_OSD0_MB_STATUS0_1;

/*-----------------------------------------------------------------------------
	0x0014 r_mif_osd0_mb_status2_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mif_mb_status3                :16,	//  0:15
	r_mif_mb_status2                :16;	// 16:31
} R_MIF_OSD0_MB_STATUS2_3;

/*-----------------------------------------------------------------------------
	0x0018 r_mif_osd0_mb_status4_5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mif_mb_status5                :16,	//  0:15
	r_mif_mb_status4                :16;	// 16:31
} R_MIF_OSD0_MB_STATUS4_5;

/*-----------------------------------------------------------------------------
	0x001c r_mif_osd0_mb_status6_7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_mif_mb_status7                :16,	//  0:15
	r_mif_mb_status6                :16;	// 16:31
} R_MIF_OSD0_MB_STATUS6_7;

#endif

/*-----------------------------------------------------------------------------
	0x0020 r_osd1_mb_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	req_pri                         : 4,	//  0: 3
	req_stv                         : 4,	//  4: 7
	req_pend                        : 8,	//  8:15
	req_10bit                       : 1,	//    16
	req_rd_lsb                      : 2,	// 17:18
	reserved                        : 2,	// 19:20
	req_pend_load_sel               : 1,	//    21
	req_fifo_cfg                    : 2,	// 22:23
	req_msk_f_on                    : 1,	//    24
	req_pat_mode                    : 2,	// 25:26
	req_pic_init_dbg                : 1,	//    27
	req_status_sel                  : 4;	// 28:31
} R_OSD1_MB_REQ;

#if 0

/*-----------------------------------------------------------------------------
	0x0024 r_osd1_cmd_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_pri                         : 4,	//  0: 3
	cmd_pri_s                       : 4,	//  4: 7
	cmd_pend                        : 4,	//  8:11
	                                : 2,	// 12:13 reserved
	cmd_pri_load_sel                : 1,	//    14
	cmd_pend_load_sel               : 1,	//    15
	reserved                        :14;	// 16:29
} R_OSD1_CMD_REQ;

/*-----------------------------------------------------------------------------
	0x0028 r_osd1_cmd_stride ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_stride                      :15,	//  0:14
	                                : 1,	//    15 reserved
	cmd_linesize                    : 4,	// 16:19
	reserved                        : 4,	// 20:23
	cmd_linesize_man                : 1,	//    24
	                                : 1,	//    25 reserved
	cmd_stride_mod                  : 2,	// 26:27
	reserved_1                      : 2;	// 28:29
} R_OSD1_CMD_STRIDE;

/*-----------------------------------------------------------------------------
	0x002c r_osd1_cmd_saddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr                       ;   	// 31: 0
} R_OSD1_CMD_SADDR;

/*-----------------------------------------------------------------------------
	0x0030 r_osd1_cmd_canvas_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_canvas_r_y                  :12,	//  0:11
	                                :17,	// 12:28 reserved
	cmd_canvas_r_load               : 1,	//    29
	cmd_canvas_r_c_on               : 1,	//    30
	cmd_canvas_r_on                 : 1;	//    31
} R_OSD1_CMD_CANVAS_R;

/*-----------------------------------------------------------------------------
	0x0034 r_osd1_cmd_saddr_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr_8b_r                  ;   	// 31: 0
} R_OSD1_CMD_SADDR_R;

/*-----------------------------------------------------------------------------
	0x0038 r_osd1_fbc_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fbd50_ll_status                 :12;	//  0:11
} R_OSD1_FBC_STATUS;

/*-----------------------------------------------------------------------------
	0x003c r_osd1_fbc_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0040 r_obc_h_mb_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	req_pri                         : 4,	//  0: 3
	req_stv                         : 4,	//  4: 7
	req_pend                        : 8,	//  8:15
	req_10bit                       : 1,	//    16
	req_rd_lsb                      : 2,	// 17:18
	reserved                        : 2,	// 19:20
	req_pend_load_sel               : 1,	//    21
	req_fifo_cfg                    : 2,	// 22:23
	req_msk_f_on                    : 1,	//    24
	req_pat_mode                    : 2,	// 25:26
	req_pic_init_dbg                : 1,	//    27
	req_status_sel                  : 4;	// 28:31
} R_OBC_H_MB_REQ;

/*-----------------------------------------------------------------------------
	0x0044 r_obc_h_cmd_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_pri                         : 4,	//  0: 3
	cmd_pri_s                       : 4,	//  4: 7
	cmd_pend                        : 4,	//  8:11
	                                : 2,	// 12:13 reserved
	cmd_pri_load_sel                : 1,	//    14
	cmd_pend_load_sel               : 1,	//    15
	reserved                        :14;	// 16:29
} R_OBC_H_CMD_REQ;

/*-----------------------------------------------------------------------------
	0x0048 r_obc_h_cmd_stride ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_stride                      :15,	//  0:14
	                                : 1,	//    15 reserved
	cmd_linesize                    : 4,	// 16:19
	reserved                        : 4,	// 20:23
	cmd_linesize_man                : 1,	//    24
	                                : 1,	//    25 reserved
	cmd_stride_mod                  : 2,	// 26:27
	reserved_1                      : 2;	// 28:29
} R_OBC_H_CMD_STRIDE;

/*-----------------------------------------------------------------------------
	0x004c r_obc_h_cmd_saddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr                       ;   	// 31: 0
} R_OBC_H_CMD_SADDR;

/*-----------------------------------------------------------------------------
	0x0050 r_obc_h_cmd_canvas_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_canvas_r_y                  :12,	//  0:11
	                                :17,	// 12:28 reserved
	cmd_canvas_r_load               : 1,	//    29
	cmd_canvas_r_c_on               : 1,	//    30
	cmd_canvas_r_on                 : 1;	//    31
} R_OBC_H_CMD_CANVAS_R;

/*-----------------------------------------------------------------------------
	0x0054 r_obc_h_cmd_saddr_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr_8b_r                  ;   	// 31: 0
} R_OBC_H_CMD_SADDR_R;

/*-----------------------------------------------------------------------------
	0x0058 r_obc_h_fbc_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fbd50_ll_status                 :12;	//  0:11
} R_OBC_H_FBC_STATUS;

/*-----------------------------------------------------------------------------
	0x005c r_obc_h_fbc_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0060 osd1_reserved0 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0064 osd1_reserved1 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0068 osd1_reserved2 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x006c osd1_reserved3 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0070 osd1_reserved4 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0074 osd1_reserved5 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0078 osd1_reserved6 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x007c osd1_reserved7 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0080 r_obc_b_mb_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	req_pri                         : 4,	//  0: 3
	req_stv                         : 4,	//  4: 7
	req_pend                        : 8,	//  8:15
	req_10bit                       : 1,	//    16
	req_rd_lsb                      : 2,	// 17:18
	reserved                        : 2,	// 19:20
	req_pend_load_sel               : 1,	//    21
	req_fifo_cfg                    : 2,	// 22:23
	req_msk_f_on                    : 1,	//    24
	req_pat_mode                    : 2,	// 25:26
	req_pic_init_dbg                : 1,	//    27
	req_status_sel                  : 4;	// 28:31
} R_OBC_B_MB_REQ;

/*-----------------------------------------------------------------------------
	0x0084 r_obc_b_cmd_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_pri                         : 4,	//  0: 3
	cmd_pri_s                       : 4,	//  4: 7
	cmd_pend                        : 4,	//  8:11
	                                : 2,	// 12:13 reserved
	cmd_pri_load_sel                : 1,	//    14
	cmd_pend_load_sel               : 1,	//    15
	reserved                        :14;	// 16:29
} R_OBC_B_CMD_REQ;

/*-----------------------------------------------------------------------------
	0x0088 r_obc_b_cmd_stride ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_stride                      :15,	//  0:14
	                                : 1,	//    15 reserved
	cmd_linesize                    : 4,	// 16:19
	reserved                        : 4,	// 20:23
	cmd_linesize_man                : 1,	//    24
	                                : 1,	//    25 reserved
	cmd_stride_mod                  : 2,	// 26:27
	reserved_1                      : 2;	// 28:29
} R_OBC_B_CMD_STRIDE;

/*-----------------------------------------------------------------------------
	0x008c r_obc_b_cmd_saddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr                       ;   	// 31: 0
} R_OBC_B_CMD_SADDR;

/*-----------------------------------------------------------------------------
	0x0090 r_obc_b_cmd_canvas_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_canvas_r_y                  :12,	//  0:11
	                                :17,	// 12:28 reserved
	cmd_canvas_r_load               : 1,	//    29
	cmd_canvas_r_c_on               : 1,	//    30
	cmd_canvas_r_on                 : 1;	//    31
} R_OBC_B_CMD_CANVAS_R;

/*-----------------------------------------------------------------------------
	0x0094 r_obc_b_cmd_saddr_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr_8b_r                  ;   	// 31: 0
} R_OBC_B_CMD_SADDR_R;

/*-----------------------------------------------------------------------------
	0x0098 r_obc_b_fbc_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fbd50_ll_status                 :12;	//  0:11
} R_OBC_B_FBC_STATUS;

/*-----------------------------------------------------------------------------
	0x009c r_obc_b_fbc_ctrl_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x00a0 r_obc_y_mb_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	req_pri                         : 4,	//  0: 3
	req_stv                         : 4,	//  4: 7
	req_pend                        : 8,	//  8:15
	req_10bit                       : 1,	//    16
	req_rd_lsb                      : 2,	// 17:18
	reserved                        : 2,	// 19:20
	req_pend_load_sel               : 1,	//    21
	req_fifo_cfg                    : 2,	// 22:23
	req_msk_f_on                    : 1,	//    24
	req_pat_mode                    : 2,	// 25:26
	req_pic_init_dbg                : 1,	//    27
	req_status_sel                  : 4;	// 28:31
} R_OBC_Y_MB_REQ;

/*-----------------------------------------------------------------------------
	0x00a4 r_obc_y_cmd_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_pri                         : 4,	//  0: 3
	cmd_pri_s                       : 4,	//  4: 7
	cmd_pend                        : 4,	//  8:11
	                                : 2,	// 12:13 reserved
	cmd_pri_load_sel                : 1,	//    14
	cmd_pend_load_sel               : 1,	//    15
	reserved                        :14;	// 16:29
} R_OBC_Y_CMD_REQ;

/*-----------------------------------------------------------------------------
	0x00a8 r_obc_y_cmd_stride ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_stride                      :15,	//  0:14
	                                : 1,	//    15 reserved
	cmd_linesize                    : 4,	// 16:19
	reserved                        : 4,	// 20:23
	cmd_linesize_man                : 1,	//    24
	                                : 1,	//    25 reserved
	cmd_stride_mod                  : 2,	// 26:27
	reserved_1                      : 2;	// 28:29
} R_OBC_Y_CMD_STRIDE;

/*-----------------------------------------------------------------------------
	0x00ac r_obc_y_cmd_saddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr                       ;   	// 31: 0
} R_OBC_Y_CMD_SADDR;

/*-----------------------------------------------------------------------------
	0x00b0 r_obc_y_cmd_canvas_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_canvas_r_y                  :12,	//  0:11
	                                :17,	// 12:28 reserved
	cmd_canvas_r_load               : 1,	//    29
	cmd_canvas_r_c_on               : 1,	//    30
	cmd_canvas_r_on                 : 1;	//    31
} R_OBC_Y_CMD_CANVAS_R;

/*-----------------------------------------------------------------------------
	0x00b4 r_obc_y_cmd_saddr_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr_8b_r                  ;   	// 31: 0
} R_OBC_Y_CMD_SADDR_R;

/*-----------------------------------------------------------------------------
	0x00b8 r_obc_y_fbc_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fbd50_ll_status                 :12;	//  0:11
} R_OBC_Y_FBC_STATUS;

/*-----------------------------------------------------------------------------
	0x00bc r_obc_y_fbc_ctrl_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x00c0 r_obc_c_mb_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	req_pri                         : 4,	//  0: 3
	req_stv                         : 4,	//  4: 7
	req_pend                        : 8,	//  8:15
	req_10bit                       : 1,	//    16
	req_rd_lsb                      : 2,	// 17:18
	reserved                        : 2,	// 19:20
	req_pend_load_sel               : 1,	//    21
	req_fifo_cfg                    : 2,	// 22:23
	req_msk_f_on                    : 1,	//    24
	req_pat_mode                    : 2,	// 25:26
	req_pic_init_dbg                : 1,	//    27
	req_status_sel                  : 4;	// 28:31
} R_OBC_C_MB_REQ;

/*-----------------------------------------------------------------------------
	0x00c4 r_obc_c_cmd_req ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_pri                         : 4,	//  0: 3
	cmd_pri_s                       : 4,	//  4: 7
	cmd_pend                        : 4,	//  8:11
	                                : 2,	// 12:13 reserved
	cmd_pri_load_sel                : 1,	//    14
	cmd_pend_load_sel               : 1,	//    15
	reserved                        :14;	// 16:29
} R_OBC_C_CMD_REQ;

/*-----------------------------------------------------------------------------
	0x00c8 r_obc_c_cmd_stride ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_stride                      :15,	//  0:14
	                                : 1,	//    15 reserved
	cmd_linesize                    : 4,	// 16:19
	reserved                        : 4,	// 20:23
	cmd_linesize_man                : 1,	//    24
	                                : 1,	//    25 reserved
	cmd_stride_mod                  : 2,	// 26:27
	reserved_1                      : 2;	// 28:29
} R_OBC_C_CMD_STRIDE;

/*-----------------------------------------------------------------------------
	0x00cc r_obc_c_cmd_saddr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr                       ;   	// 31: 0
} R_OBC_C_CMD_SADDR;

/*-----------------------------------------------------------------------------
	0x00d0 r_obc_c_cmd_canvas_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_canvas_r_y                  :12,	//  0:11
	                                :17,	// 12:28 reserved
	cmd_canvas_r_load               : 1,	//    29
	cmd_canvas_r_c_on               : 1,	//    30
	cmd_canvas_r_on                 : 1;	//    31
} R_OBC_C_CMD_CANVAS_R;

/*-----------------------------------------------------------------------------
	0x00d4 r_obc_c_cmd_saddr_r ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_saddr_8b_r                  ;   	// 31: 0
} R_OBC_C_CMD_SADDR_R;

/*-----------------------------------------------------------------------------
	0x00d8 r_obc_c_fbc_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	fbd50_ll_status                 :12;	//  0:11
} R_OBC_C_FBC_STATUS;

/*-----------------------------------------------------------------------------
	0x00dc r_obc_c_fbc_ctrl_reserved ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x00e0 r_osd1_cmd_qos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_qos_urgent                  : 8,	//  0: 7
	cmd_qos_start_mode              : 2,	//  8: 9
	cmd_qos_info                    : 2,	// 10:11
	cmd_qos_info_mode               : 2,	// 12:13
	cmd_qos_mode                    : 2,	// 14:15
	cmd_qos_dly_cnt                 : 8,	// 16:23
	cmd_qos_start_line              : 4,	// 24:27
	                                : 2,	// 28:29 reserved
	cmd_qos_en                      : 1,	//    30
	cmd_qos_reg_sel                 : 1;	//    31
} R_OSD1_CMD_QOS_CTRL;

/*-----------------------------------------------------------------------------
	0x00e4 r_obc_h_cmd_qos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_qos_urgent                  : 8,	//  0: 7
	cmd_qos_start_mode              : 2,	//  8: 9
	cmd_qos_info                    : 2,	// 10:11
	cmd_qos_info_mode               : 2,	// 12:13
	cmd_qos_mode                    : 2,	// 14:15
	cmd_qos_dly_cnt                 : 8,	// 16:23
	cmd_qos_start_line              : 4,	// 24:27
	                                : 2,	// 28:29 reserved
	cmd_qos_en                      : 1,	//    30
	cmd_qos_reg_sel                 : 1;	//    31
} R_OBC_H_CMD_QOS_CTRL;

/*-----------------------------------------------------------------------------
	0x00e8 r_obc_b_cmd_qos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_qos_urgent                  : 8,	//  0: 7
	cmd_qos_start_mode              : 2,	//  8: 9
	cmd_qos_info                    : 2,	// 10:11
	cmd_qos_info_mode               : 2,	// 12:13
	cmd_qos_mode                    : 2,	// 14:15
	cmd_qos_dly_cnt                 : 8,	// 16:23
	cmd_qos_start_line              : 4,	// 24:27
	                                : 2,	// 28:29 reserved
	cmd_qos_en                      : 1,	//    30
	cmd_qos_reg_sel                 : 1;	//    31
} R_OBC_B_CMD_QOS_CTRL;

/*-----------------------------------------------------------------------------
	0x00ec r_obc_y_cmd_qos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_qos_urgent                  : 8,	//  0: 7
	cmd_qos_start_mode              : 2,	//  8: 9
	cmd_qos_info                    : 2,	// 10:11
	cmd_qos_info_mode               : 2,	// 12:13
	cmd_qos_mode                    : 2,	// 14:15
	cmd_qos_dly_cnt                 : 8,	// 16:23
	cmd_qos_start_line              : 4,	// 24:27
	                                : 2,	// 28:29 reserved
	cmd_qos_en                      : 1,	//    30
	cmd_qos_reg_sel                 : 1;	//    31
} R_OBC_Y_CMD_QOS_CTRL;

/*-----------------------------------------------------------------------------
	0x00f0 r_obc_c_cmd_qos_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cmd_qos_urgent                  : 8,	//  0: 7
	cmd_qos_start_mode              : 2,	//  8: 9
	cmd_qos_info                    : 2,	// 10:11
	cmd_qos_info_mode               : 2,	// 12:13
	cmd_qos_mode                    : 2,	// 14:15
	cmd_qos_dly_cnt                 : 8,	// 16:23
	cmd_qos_start_line              : 4,	// 24:27
	                                : 2,	// 28:29 reserved
	cmd_qos_en                      : 1,	//    30
	cmd_qos_reg_sel                 : 1;	//    31
} R_OBC_C_CMD_QOS_CTRL;

/*-----------------------------------------------------------------------------
	0x00f4 r_mif_osd0_intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mif_intr_en                     ;   	// 31: 0
} R_MIF_OSD0_INTR_EN;

/*-----------------------------------------------------------------------------
	0x00f8 r_mif_osd0_intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mif_intr_mask                   ;   	// 31: 0
} R_MIF_OSD0_INTR_MASK;

/*-----------------------------------------------------------------------------
	0x00fc r_mif_osd0_intr_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mif_intr_status                 ;   	// 31: 0
} R_MIF_OSD0_INTR_STATUS;

/*-----------------------------------------------------------------------------
	0x0100 r_mif_osd0_intr_clear ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mif_intr_clear                  ;   	// 31: 0
} R_MIF_OSD0_INTR_CLEAR;

#endif

typedef struct {
#if 1
	UINT32								__skip_00[8]					;	// 0x0000~0x20
#else
	R_MIF_OSD0_GIF_EN               	r_mif_osd0_gif_en               ;	// 0x0000 : ''
	R_MIF_OSD0_RESET                	r_mif_osd0_reset                ;	// 0x0004 : ''
	R_MIF_OSD0_STATUS               	r_mif_osd0_status               ;	// 0x0008 : ''
	R_MIF_OSD0_LOAD                 	r_mif_osd0_load                 ;	// 0x000c : ''
	R_MIF_OSD0_MB_STATUS0_1         	r_mif_osd0_mb_status0_1         ;	// 0x0010 : ''
	R_MIF_OSD0_MB_STATUS2_3         	r_mif_osd0_mb_status2_3         ;	// 0x0014 : ''
	R_MIF_OSD0_MB_STATUS4_5         	r_mif_osd0_mb_status4_5         ;	// 0x0018 : ''
	R_MIF_OSD0_MB_STATUS6_7         	r_mif_osd0_mb_status6_7         ;	// 0x001c : ''
#endif
	R_OSD1_MB_REQ                   	r_osd1_mb_req                   ;	// 0x0020 : ''

#if 1
	UINT32								__skip_01[55]					;	// 0x0024~0x100
#else
	R_OSD1_CMD_REQ                  	r_osd1_cmd_req                  ;	// 0x0024 : ''
	R_OSD1_CMD_STRIDE               	r_osd1_cmd_stride               ;	// 0x0028 : ''
	R_OSD1_CMD_SADDR                	r_osd1_cmd_saddr                ;	// 0x002c : ''
	R_OSD1_CMD_CANVAS_R             	r_osd1_cmd_canvas_r             ;	// 0x0030 : ''
	R_OSD1_CMD_SADDR_R              	r_osd1_cmd_saddr_r              ;	// 0x0034 : ''
	R_OSD1_FBC_STATUS               	r_osd1_fbc_status               ;	// 0x0038 : ''
	UINT32                          	r_osd1_fbc_reserved             ;	// 0x003c : ''
	R_OBC_H_MB_REQ                  	r_obc_h_mb_req                  ;	// 0x0040 : ''
	R_OBC_H_CMD_REQ                 	r_obc_h_cmd_req                 ;	// 0x0044 : ''
	R_OBC_H_CMD_STRIDE              	r_obc_h_cmd_stride              ;	// 0x0048 : ''
	R_OBC_H_CMD_SADDR               	r_obc_h_cmd_saddr               ;	// 0x004c : ''
	R_OBC_H_CMD_CANVAS_R            	r_obc_h_cmd_canvas_r            ;	// 0x0050 : ''
	R_OBC_H_CMD_SADDR_R             	r_obc_h_cmd_saddr_r             ;	// 0x0054 : ''
	R_OBC_H_FBC_STATUS              	r_obc_h_fbc_status              ;	// 0x0058 : ''
	UINT32                          	r_obc_h_fbc_reserved            ;	// 0x005c : ''
	UINT32                          	osd1_reserved0                  ;	// 0x0060 : ''
	UINT32                          	osd1_reserved1                  ;	// 0x0064 : ''
	UINT32                          	osd1_reserved2                  ;	// 0x0068 : ''
	UINT32                          	osd1_reserved3                  ;	// 0x006c : ''
	UINT32                          	osd1_reserved4                  ;	// 0x0070 : ''
	UINT32                          	osd1_reserved5                  ;	// 0x0074 : ''
	UINT32                          	osd1_reserved6                  ;	// 0x0078 : ''
	UINT32                          	osd1_reserved7                  ;	// 0x007c : ''
	R_OBC_B_MB_REQ                  	r_obc_b_mb_req                  ;	// 0x0080 : ''
	R_OBC_B_CMD_REQ                 	r_obc_b_cmd_req                 ;	// 0x0084 : ''
	R_OBC_B_CMD_STRIDE              	r_obc_b_cmd_stride              ;	// 0x0088 : ''
	R_OBC_B_CMD_SADDR               	r_obc_b_cmd_saddr               ;	// 0x008c : ''
	R_OBC_B_CMD_CANVAS_R            	r_obc_b_cmd_canvas_r            ;	// 0x0090 : ''
	R_OBC_B_CMD_SADDR_R             	r_obc_b_cmd_saddr_r             ;	// 0x0094 : ''
	R_OBC_B_FBC_STATUS              	r_obc_b_fbc_status              ;	// 0x0098 : ''
	UINT32                          	r_obc_b_fbc_ctrl_reserved       ;	// 0x009c : ''
	R_OBC_Y_MB_REQ                  	r_obc_y_mb_req                  ;	// 0x00a0 : ''
	R_OBC_Y_CMD_REQ                 	r_obc_y_cmd_req                 ;	// 0x00a4 : ''
	R_OBC_Y_CMD_STRIDE              	r_obc_y_cmd_stride              ;	// 0x00a8 : ''
	R_OBC_Y_CMD_SADDR               	r_obc_y_cmd_saddr               ;	// 0x00ac : ''
	R_OBC_Y_CMD_CANVAS_R            	r_obc_y_cmd_canvas_r            ;	// 0x00b0 : ''
	R_OBC_Y_CMD_SADDR_R             	r_obc_y_cmd_saddr_r             ;	// 0x00b4 : ''
	R_OBC_Y_FBC_STATUS              	r_obc_y_fbc_status              ;	// 0x00b8 : ''
	UINT32                          	r_obc_y_fbc_ctrl_reserved       ;	// 0x00bc : ''
	R_OBC_C_MB_REQ                  	r_obc_c_mb_req                  ;	// 0x00c0 : ''
	R_OBC_C_CMD_REQ                 	r_obc_c_cmd_req                 ;	// 0x00c4 : ''
	R_OBC_C_CMD_STRIDE              	r_obc_c_cmd_stride              ;	// 0x00c8 : ''
	R_OBC_C_CMD_SADDR               	r_obc_c_cmd_saddr               ;	// 0x00cc : ''
	R_OBC_C_CMD_CANVAS_R            	r_obc_c_cmd_canvas_r            ;	// 0x00d0 : ''
	R_OBC_C_CMD_SADDR_R             	r_obc_c_cmd_saddr_r             ;	// 0x00d4 : ''
	R_OBC_C_FBC_STATUS              	r_obc_c_fbc_status              ;	// 0x00d8 : ''
	UINT32                          	r_obc_c_fbc_ctrl_reserved       ;	// 0x00dc : ''
	R_OSD1_CMD_QOS_CTRL             	r_osd1_cmd_qos_ctrl             ;	// 0x00e0 : ''
	R_OBC_H_CMD_QOS_CTRL            	r_obc_h_cmd_qos_ctrl            ;	// 0x00e4 : ''
	R_OBC_B_CMD_QOS_CTRL            	r_obc_b_cmd_qos_ctrl            ;	// 0x00e8 : ''
	R_OBC_Y_CMD_QOS_CTRL            	r_obc_y_cmd_qos_ctrl            ;	// 0x00ec : ''
	R_OBC_C_CMD_QOS_CTRL            	r_obc_c_cmd_qos_ctrl            ;	// 0x00f0 : ''
	R_MIF_OSD0_INTR_EN              	r_mif_osd0_intr_en              ;	// 0x00f4 : ''
	R_MIF_OSD0_INTR_MASK            	r_mif_osd0_intr_mask            ;	// 0x00f8 : ''
	R_MIF_OSD0_INTR_STATUS          	r_mif_osd0_intr_status          ;	// 0x00fc : ''
	R_MIF_OSD0_INTR_CLEAR           	r_mif_osd0_intr_clear           ;	// 0x0100 : ''
#endif
} OSD_MIF1_CTRL_O24_REG_T;
/* 65 regs, 65 types */

/* 65 regs, 65 types in Total*/

// *INDENT-ON*

#define OSD_MIF1_CTRL_RdFL(_r)                  ((g_osd_mif1_o24_reg_shadow->_r)=(g_osd_mif1_o24_reg->_r))
#define OSD_MIF1_CTRL_WrFL(_r)                  ((g_osd_mif1_o24_reg->_r)=(g_osd_mif1_o24_reg_shadow->_r))

#define OSD_MIF1_CTRL_Rd(_r)                    *((UINT32*)(&(g_osd_mif1_o24_reg_shadow->_r)))
#define OSD_MIF1_CTRL_Wr(_r,_v)                 ((OSD_MIF1_CTRL_Rd(_r))=((UINT32)(_v)))

#define OSD_MIF1_CTRL_Rd01(_r,_f01,_v01)                                            \
                                do {                                                \
                                    (_v01) = (g_osd_mif1_o24_reg_shadow->_r._f01);  \
                                } while(0)

#define OSD_MIF1_CTRL_Rd02(_r,_f01,_v01,_f02,_v02)                                  \
                                do {                                                \
                                    (_v01) = (g_osd_mif1_o24_reg_shadow->_r._f01);  \
                                    (_v02) = (g_osd_mif1_o24_reg_shadow->_r._f02);  \
                                } while(0)

#define OSD_MIF1_CTRL_Wr01(_r,_f01,_v01)                                            \
                                do {                                                \
                                    (g_osd_mif1_o24_reg_shadow->_r._f01) = (_v01);  \
                                } while(0)

#define OSD_MIF1_CTRL_Wr02(_r,_f01,_v01,_f02,_v02)                                  \
                                do {                                                \
                                    (g_osd_mif1_o24_reg_shadow->_r._f01) = (_v01);  \
                                    (g_osd_mif1_o24_reg_shadow->_r._f02) = (_v02);  \
                                } while(0)

/** @} *//* end of macro documentation */

extern volatile OSD_MIF1_CTRL_O24_REG_T*     g_osd_mif1_o24_reg;
extern OSD_MIF1_CTRL_O24_REG_T*              g_osd_mif1_o24_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O24-A0_PQE_MIF1_reg_man.csv' 20230407 17:27:54 KST by getregs v2.9 */
