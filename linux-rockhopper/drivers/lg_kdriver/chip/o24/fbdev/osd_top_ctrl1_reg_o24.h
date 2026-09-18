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

#ifndef __OSD_TOP_CTRL1_REG_O24_H__
#define __OSD_TOP_CTRL1_REG_O24_H__

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
	0x0000 pic_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	g0_pic_init                     : 1,	//     0
	g1_pic_init                     : 1,	//     1
	g2_pic_init                     : 1,	//     2
	g3_pic_init                     : 1,	//     3
	g4_pic_init                     : 1,	//     4
	g5_pic_init                     : 1,	//     5
	g6_pic_init                     : 1,	//     6
	g7_pic_init                     : 1,	//     7
	                                : 8,	//  8:15 reserved
	g0_auto_init                    : 1,	//    16
	g1_auto_init                    : 1,	//    17
	g2_auto_init                    : 1,	//    18
	g3_auto_init                    : 1,	//    19
	g4_auto_init                    : 1,	//    20
	g5_auto_init                    : 1,	//    21
	g6_auto_init                    : 1,	//    22
	g7_auto_init                    : 1,	//    23
	g0_pic_init_mask                : 1,	//    24
	g1_pic_init_mask                : 1,	//    25
	g2_pic_init_mask                : 1,	//    26
	g3_pic_init_mask                : 1,	//    27
	g4_pic_init_mask                : 1,	//    28
	g5_pic_init_mask                : 1,	//    29
	g6_pic_init_mask                : 1,	//    30
	g7_pic_init_mask                : 1;	//    31
} PIC_INIT;

/*-----------------------------------------------------------------------------
	0x0004 pic_start ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	g0_pic_start                    : 1,	//     0
	g1_pic_start                    : 1,	//     1
	g2_pic_start                    : 1,	//     2
	g3_pic_start                    : 1,	//     3
	g4_pic_start                    : 1,	//     4
	g5_pic_start                    : 1,	//     5
	g6_pic_start                    : 1,	//     6
	g7_pic_start                    : 1,	//     7
	                                : 8,	//  8:15 reserved
	g0_auto_half_en                 : 1,	//    16
	g1_auto_half_en                 : 1,	//    17
	g2_auto_half_en                 : 1,	//    18
	g3_auto_half_en                 : 1,	//    19
	g4_auto_half_en                 : 1,	//    20
	g5_auto_half_en                 : 1,	//    21
	g6_auto_half_en                 : 1,	//    22
	g7_auto_half_en                 : 1,	//    23
	g0_pic_start_mask               : 1,	//    24
	g1_pic_start_mask               : 1,	//    25
	g2_pic_start_mask               : 1,	//    26
	g3_pic_start_mask               : 1,	//    27
	g4_pic_start_mask               : 1,	//    28
	g5_pic_start_mask               : 1,	//    29
	g6_pic_start_mask               : 1,	//    30
	g7_pic_start_mask               : 1;	//    31
} PIC_START;

/*-----------------------------------------------------------------------------
	0x0008 ctrl_auto_init ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	idx_src_g0_auto_init            : 3,	//  0: 2
	                                : 1,	//     3 reserved
	idx_src_g1_auto_init            : 3,	//  4: 6
	                                : 1,	//     7 reserved
	idx_src_g2_auto_init            : 3,	//  8:10
	                                : 1,	//    11 reserved
	idx_src_g3_auto_init            : 3,	// 12:14
	                                : 1,	//    15 reserved
	idx_src_g4_auto_init            : 3,	// 16:18
	                                : 1,	//    19 reserved
	idx_src_g5_auto_init            : 3,	// 20:22
	                                : 1,	//    23 reserved
	idx_src_g6_auto_init            : 3,	// 24:26
	                                : 1,	//    27 reserved
	idx_src_g7_auto_init            : 3;	// 28:30
} CTRL_AUTO_INIT;

/*-----------------------------------------------------------------------------
	0x000c ctrl_intr_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	idx_src_i0_intr_pulse           : 3,	//  0: 2
	sel_src_i0_intr_pulse           : 1,	//     3
	idx_src_i1_intr_pulse           : 3,	//  4: 6
	sel_src_i1_intr_pulse           : 1,	//     7
	idx_src_i2_intr_pulse           : 3,	//  8:10
	sel_src_i2_intr_pulse           : 1,	//    11
	idx_src_i3_intr_pulse           : 3,	// 12:14
	sel_src_i3_intr_pulse           : 1,	//    15
	idx_src_i4_intr_pulse           : 3,	// 16:18
	sel_src_i4_intr_pulse           : 1,	//    19
	idx_src_i5_intr_pulse           : 3,	// 20:22
	sel_src_i5_intr_pulse           : 1,	//    23
	idx_src_i6_intr_pulse           : 3,	// 24:26
	sel_src_i6_intr_pulse           : 1,	//    27
	idx_src_i7_intr_pulse           : 3,	// 28:30
	sel_src_i7_intr_pulse           : 1;	//    31
} CTRL_INTR_PULSE;

/*-----------------------------------------------------------------------------
	0x0010 intr_reg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	intr_i0_intr_pulse              : 1,	//     0
	intr_i1_intr_pulse              : 1,	//     1
	intr_i2_intr_pulse              : 1,	//     2
	intr_i3_intr_pulse              : 1,	//     3
	intr_i4_intr_pulse              : 1,	//     4
	intr_i5_intr_pulse              : 1,	//     5
	intr_i6_intr_pulse              : 1,	//     6
	intr_i7_intr_pulse              : 1,	//     7
	intr_g0_pic_end                 : 1,	//     8
	intr_g1_pic_end                 : 1,	//     9
	intr_g2_pic_end                 : 1,	//    10
	intr_g3_pic_end                 : 1,	//    11
	intr_g4_pic_end                 : 1,	//    12
	intr_g5_pic_end                 : 1,	//    13
	intr_g6_pic_end                 : 1,	//    14
	intr_g7_pic_end                 : 1,	//    15
	intr_osd                        : 1,	//    16
	intr_mif0_osd                   : 1,	//    17
	intr_mif1_osd                   : 1,	//    18
	                                : 4,	// 19:22 reserved
	intr_obc_pel                    : 1,	//    23
	intr_obc_map                    : 1;	//    24
} INTR_REG;

/*-----------------------------------------------------------------------------
	0x0014 intr_mask ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mask_i0_src_pulse               : 1,	//     0
	mask_i1_src_pulse               : 1,	//     1
	mask_i2_src_pulse               : 1,	//     2
	mask_i3_src_pulse               : 1,	//     3
	mask_i4_src_pulse               : 1,	//     4
	mask_i5_src_pulse               : 1,	//     5
	mask_i6_src_pulse               : 1,	//     6
	mask_i7_src_pulse               : 1,	//     7
	mask_g0_pic_end                 : 1,	//     8
	mask_g1_pic_end                 : 1,	//     9
	mask_g2_pic_end                 : 1,	//    10
	mask_g3_pic_end                 : 1,	//    11
	mask_g4_pic_end                 : 1,	//    12
	mask_g5_pic_end                 : 1,	//    13
	mask_g6_pic_end                 : 1,	//    14
	mask_g7_pic_end                 : 1,	//    15
	mask_osd                        : 1,	//    16
	mask_mif0_osd                   : 1,	//    17
	mask_mif1_osd                   : 1,	//    18
	                                : 4,	// 19:22 reserved
	mask_obc_pel                    : 1,	//    23
	mask_obc_map                    : 1;	//    24
} INTR_MASK;

/*-----------------------------------------------------------------------------
	0x0018 intr_mux ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	mux_i0_src_pulse                : 1,	//     0
	mux_i1_src_pulse                : 1,	//     1
	mux_i2_src_pulse                : 1,	//     2
	mux_i3_src_pulse                : 1,	//     3
	mux_i4_src_pulse                : 1,	//     4
	mux_i5_src_pulse                : 1,	//     5
	mux_i6_src_pulse                : 1,	//     6
	mux_i7_src_pulse                : 1,	//     7
	mux_g0_pic_end                  : 1,	//     8
	mux_g1_pic_end                  : 1,	//     9
	mux_g2_pic_end                  : 1,	//    10
	mux_g3_pic_end                  : 1,	//    11
	mux_g4_pic_end                  : 1,	//    12
	mux_g5_pic_end                  : 1,	//    13
	mux_g6_pic_end                  : 1,	//    14
	mux_g7_pic_end                  : 1,	//    15
	mux_osd                         : 1,	//    16
	mux_mif0_osd                    : 1,	//    17
	mux_mif1_osd                    : 1,	//    18
	                                : 4,	// 19:22 reserved
	mux_obc_pel                     : 1,	//    23
	mux_obc_map                     : 1;	//    24
} INTR_MUX;

/*-----------------------------------------------------------------------------
	0x001c intr_en ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	en_i0_src_pulse                 : 1,	//     0
	en_i1_src_pulse                 : 1,	//     1
	en_i2_src_pulse                 : 1,	//     2
	en_i3_src_pulse                 : 1,	//     3
	en_i4_src_pulse                 : 1,	//     4
	en_i5_src_pulse                 : 1,	//     5
	en_i6_src_pulse                 : 1,	//     6
	en_i7_src_pulse                 : 1,	//     7
	en_g0_pic_end                   : 1,	//     8
	en_g1_pic_end                   : 1,	//     9
	en_g2_pic_end                   : 1,	//    10
	en_g3_pic_end                   : 1,	//    11
	en_g4_pic_end                   : 1,	//    12
	en_g5_pic_end                   : 1,	//    13
	en_g6_pic_end                   : 1,	//    14
	en_g7_pic_end                   : 1,	//    15
	en_osd                          : 1,	//    16
	en_mif0_osd                     : 1,	//    17
	en_mif1_osd                     : 1,	//    18
	                                : 4,	// 19:22 reserved
	en_obc_pel                      : 1,	//    23
	en_obc_map                      : 1;	//    24
} INTR_EN;

/*-----------------------------------------------------------------------------
	0x0020 ctrl_info ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_chip_info_en                : 1;	//     0
} CTRL_INFO;

/*-----------------------------------------------------------------------------
	0x0024 ctrl_cc_data_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dly_body                    : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_dly_head                    : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_dly_text                    : 3,	//  8:10
	                                : 1,	//    11 reserved
	reg_dly_csr                     : 3;	// 12:14
} CTRL_CC_DATA_DLY;

#endif

/*-----------------------------------------------------------------------------
	0x0028 ctrl_osd_change ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_use_osd0_en                 : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_use_afbc_en                 : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_use_osd4_en                 : 1,	//     8
	                                : 7,	//  9:15 reserved
	reg_auto_reset_cnt              :16;	// 16:31
} CTRL_OSD_CHANGE;

#if 0

/*-----------------------------------------------------------------------------
	0x002c ctrl_osd_pip_merge ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_spip_dly                    : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_sosd_dly                    : 4,	//  8:11
	                                : 4,	// 12:15 reserved
	reg_pip_flag                    : 8,	// 16:23
	                                : 6,	// 24:29 reserved
	reg_merge_sel                   : 2;	// 30:31
} CTRL_OSD_PIP_MERGE;

/*-----------------------------------------------------------------------------
	0x0030 ctrl_data_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd_alpha_dly               : 4,	//  0: 3
	reg_osd_obj_dly                 : 4,	//  4: 7
	reg_mm_ld_dly                   : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	reg_gcf_obj_dly                 : 2,	// 16:17
	                                :13,	// 18:30 reserved
	reg_dly_cg_en_n                 : 1;	//    31
} CTRL_DATA_DLY;

/*-----------------------------------------------------------------------------
	0x0034 ctrl_osd_120_sync_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vsync                           :16,	//  0:15
	vfp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY0;

/*-----------------------------------------------------------------------------
	0x0038 ctrl_osd_120_sync_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	va                              :16,	//  0:15
	vbp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY1;

/*-----------------------------------------------------------------------------
	0x003c ctrl_osd_120_sync_dly2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hsync                           :16,	//  0:15
	hfp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY2;

/*-----------------------------------------------------------------------------
	0x0040 ctrl_osd_120_sync_dly3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ha                              :16,	//  0:15
	hbp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY3;

/*-----------------------------------------------------------------------------
	0x0044 ctrl_osd_120_sync_dly4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	line_start_pos                  :16,	//  0:15
	sel_in_h_src                    : 1,	//    16
	sel_in_v_src                    : 1,	//    17
	sel_in_h_inv                    : 1,	//    18
	sel_in_v_inv                    : 1,	//    19
	sel_out_ha                      : 1,	//    20
	sel_out_va                      : 1,	//    21
	sel_out_hs                      : 1,	//    22
	sel_out_vs                      : 1,	//    23
	tp_update_hv_zero               : 1,	//    24
	force_out_ha                    : 1,	//    25
	force_out_va                    : 1,	//    26
	force_out_hs                    : 1,	//    27
	manual_cnt_h_value_en           : 1,	//    28
	manual_cnt_v_value_en           : 1,	//    29
	force_out_vs                    : 1,	//    30
	force_update                    : 1;	//    31
} CTRL_OSD_120_SYNC_DLY4;

/*-----------------------------------------------------------------------------
	0x0048 ctrl_osd_120_sync_dly5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sync_h_dly                      :16,	//  0:15
	sync_v_dly                      :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY5;

/*-----------------------------------------------------------------------------
	0x004c ctrl_osd_120_sync_dly6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	manual_cnt_h_value              :16,	//  0:15
	manual_cnt_v_value              :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY6;

/*-----------------------------------------------------------------------------
	0x0050 ctrl_osd_120_sync_dly7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_ha_delay                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_va_delay                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_OSD_120_SYNC_DLY7;

/*-----------------------------------------------------------------------------
	0x0054 ctrl_osd_120_sync_dly8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_hs_delay                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_vs_delay                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_OSD_120_SYNC_DLY8;

/*-----------------------------------------------------------------------------
	0x0058 ctrl_osd_120_sync_dly9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	line_cnt_threshold              :16;	//  0:15
} CTRL_OSD_120_SYNC_DLY9;

/*-----------------------------------------------------------------------------
	0x005c ctrl_osd_120_sync_dlya ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rst_pos_cnt_h                   :16,	//  0:15
	rst_pos_cnt_v                   :16;	// 16:31
} CTRL_OSD_120_SYNC_DLYA;

/*-----------------------------------------------------------------------------
	0x0060 ctrl_cco_ppd_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_v_offset                    : 4,	//  0: 3
	reg_h_offset                    : 4,	//  4: 7
	reg_v_part_mode                 : 4,	//  8:11
	reg_h_part_mode                 : 4,	// 12:15
	                                :15,	// 16:30 reserved
	reg_ppd_en                      : 1;	//    31
} CTRL_CCO_PPD_CTRL0;

/*-----------------------------------------------------------------------------
	0x0064 ctrl_cco_ppd_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_v_offset                    : 4,	//  0: 3
	reg_h_offset                    : 4,	//  4: 7
	reg_v_part_mode                 : 4,	//  8:11
	reg_h_part_mode                 : 4,	// 12:15
	                                :15,	// 16:30 reserved
	reg_ppd_en                      : 1;	//    31
} CTRL_CCO_PPD_CTRL1;

/*-----------------------------------------------------------------------------
	0x0068 ctrl_bosd_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_disp_pulse_timer            :28,	//  0:27
	reg_disp_pulse_src_sel          : 1,	//    28
	reg_disp_pulse_src_inv          : 1;	//    29
} CTRL_BOSD_PULSE;

/*-----------------------------------------------------------------------------
	0x006c ctrl_sosd_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_disp_pulse_timer            :28,	//  0:27
	reg_disp_pulse_src_sel          : 1,	//    28
	reg_disp_pulse_src_inv          : 1;	//    29
} CTRL_SOSD_PULSE;

/*-----------------------------------------------------------------------------
	0x0070 ctrl_bosd_init_2nd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bosd_init_2nd_line              :16,	//  0:15
	                                :12,	// 16:27 reserved
	bosd_init_2nd_en                : 1;	//    28
} CTRL_BOSD_INIT_2ND;

/*-----------------------------------------------------------------------------
	0x0074 ctrl_sosd_init_2nd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bosd_init_2nd_line              :16,	//  0:15
	                                :12,	// 16:27 reserved
	bosd_init_2nd_en                : 1;	//    28
} CTRL_SOSD_INIT_2ND;

/*-----------------------------------------------------------------------------
	0x0080 ctrl_l3d_dma_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_l3d_dma_hsize               :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_l3d_dma_vsize               :15;	// 16:30
} CTRL_L3D_DMA_SIZE;

/*-----------------------------------------------------------------------------
	0x0084 ctrl_l3d_dma_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_l3d_dma_en                  : 1,	//     0
	reg_l3d_dma_manual_en           : 1,	//     1
	reg_l3d_dma_line_inc            : 2,	//  2: 3
	reg_l3d_dma_swap                : 4,	//  4: 7
	reg_l3d_data_sel                : 4;	//  8:11
} CTRL_L3D_DMA_CTRL;

/*-----------------------------------------------------------------------------
	0x0088 ctrl_ro_l3d_vcnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	l3d_line_count                  :15;	//  0:14
} CTRL_RO_L3D_VCNT;

/*-----------------------------------------------------------------------------
	0x008c ctrl_vr360_on ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sel_fal_sync_timer          :28,	//  0:27
	                                : 1,	//    28 reserved
	reg_sel_fal_sync                : 2,	// 29:30
	reg_vr360_on                    : 1;	//    31
} CTRL_VR360_ON;

/*-----------------------------------------------------------------------------
	0x0090 ctrl_cg_on ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cc_top_cg                   : 1,	//     0
	reg_lsr_l7_scaler_cg            : 1,	//     1
	reg_lsr_l3_scaler_cg            : 1,	//     2
	reg_lsr_blender_cg              : 1,	//     3
	reg_lsr_top_cg_off              : 1,	//     4
	reg_sosd_clk_cg                 : 1,	//     5
	reg_osd0_shp_cg                 : 1,	//     6
	reg_osd1_shp_cg                 : 1,	//     7
	reg_dsc_top_cg                  : 1,	//     8
	reg_decon_top_cg                : 1;	//     9
} CTRL_CG_ON;

/*-----------------------------------------------------------------------------
	0x0094 ctrl_cg_on_sync ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_cc_top_cg_vs_fal_sel        : 2,	//  0: 1
	reg_cc_top_cg_pulse             : 2,	//  2: 3
	reg_cc_top_cg_timer             :12,	//  4:15
	reg_dsc_top_cg_vs_fal_sel       : 2,	// 16:17
	reg_dsc_top_cg_pulse            : 2,	// 18:19
	reg_dsc_top_cg_timer            :12;	// 20:31
} CTRL_CG_ON_SYNC;

/*-----------------------------------------------------------------------------
	0x0098 ctrl_vr360_vid_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vr360_vid_b_evn             :10,	//  0: 9
	reg_vr360_vid_g_evn             :10,	// 10:19
	reg_vr360_vid_r_evn             :10;	// 20:29
} CTRL_VR360_VID_DATA0;

/*-----------------------------------------------------------------------------
	0x009c ctrl_vr360_vid_data1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vr360_vid_b_odd             :10,	//  0: 9
	reg_vr360_vid_g_odd             :10,	// 10:19
	reg_vr360_vid_r_odd             :10;	// 20:29
} CTRL_VR360_VID_DATA1;

/*-----------------------------------------------------------------------------
	0x00a0 ctrl_vx1_control_packet0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :20,	//  0:19 reserved
	reg_pkt_ready_force             : 1,	//    20
	                                : 3,	// 21:23 reserved
	reg_pkt_trns_mode               : 2,	// 24:25
	                                : 2,	// 26:27 reserved
	reg_pkt_trns_en                 : 1;	//    28
} CTRL_VX1_CONTROL_PACKET0;

/*-----------------------------------------------------------------------------
	0x00a4 ctrl_vx1_control_packet1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pkt_trns_line_cnt           ;   	// 31: 0
} CTRL_VX1_CONTROL_PACKET1;

/*-----------------------------------------------------------------------------
	0x00a8 ctrl_vx1_control_packet2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	end_id                          :16,	//  0:15
	start_id                        :16;	// 16:31
} CTRL_VX1_CONTROL_PACKET2;

/*-----------------------------------------------------------------------------
	0x00ac ctrl_vx1_control_packet3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vx1_packet_data_1           :16,	//  0:15
	reg_vx1_packet_data_0           :16;	// 16:31
} CTRL_VX1_CONTROL_PACKET3;

/*-----------------------------------------------------------------------------
	0x00b0 ctrl_vx1_control_packet4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vx1_packet_data_3           :16,	//  0:15
	reg_vx1_packet_data_2           :16;	// 16:31
} CTRL_VX1_CONTROL_PACKET4;

/*-----------------------------------------------------------------------------
	0x00b4 ctrl_vx1_control_packet5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vx1_packet_data_5           :16,	//  0:15
	reg_vx1_packet_data_4           :16;	// 16:31
} CTRL_VX1_CONTROL_PACKET5;

/*-----------------------------------------------------------------------------
	0x00b8 ctrl_vx1_control_packet6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_vx1_packet_data_7           :16,	//  0:15
	reg_vx1_packet_data_6           :16;	// 16:31
} CTRL_VX1_CONTROL_PACKET6;

/*-----------------------------------------------------------------------------
	0x00bc axi_user_cco ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cco0_aruser                     : 4,	//  0: 3
	                                : 4,	//  4: 7 reserved
	cco1_aruser                     : 4;	//  8:11
} AXI_USER_CCO;

/*-----------------------------------------------------------------------------
	0x00c0 pic_init_g0_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G0_TIMER;

/*-----------------------------------------------------------------------------
	0x00c4 pic_init_g1_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G1_TIMER;

/*-----------------------------------------------------------------------------
	0x00c8 pic_init_g2_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G2_TIMER;

/*-----------------------------------------------------------------------------
	0x00cc pic_init_g3_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G3_TIMER;

/*-----------------------------------------------------------------------------
	0x00d0 pic_init_g4_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G4_TIMER;

/*-----------------------------------------------------------------------------
	0x00d4 pic_init_g5_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G5_TIMER;

/*-----------------------------------------------------------------------------
	0x00d8 pic_init_g6_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G6_TIMER;

/*-----------------------------------------------------------------------------
	0x00dc pic_init_g7_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	pic_init_timer                  :24,	//  0:23
	start_interval_mode_en          : 1,	//    24
	start_interval_mode             : 3,	// 25:27
	pic_init_width_mode_en          : 1,	//    28
	pic_init_width_mode             : 2,	// 29:30
	wait_pic_end_en                 : 1;	//    31
} PIC_INIT_G7_TIMER;

/*-----------------------------------------------------------------------------
	0x00e4 dbg_timer_run ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	info_timer_run                  :24,	//  0:23
	idx_end_src                     : 3,	// 24:26
	sel_end_src                     : 1,	//    27
	idx_start_src                   : 3,	// 28:30
	sel_start_src                   : 1;	//    31
} DBG_TIMER_RUN;

/*-----------------------------------------------------------------------------
	0x00e8 gx_pic_start_end_proc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rw_gx_pic_start_end             : 1,	//     0
	dly_gx_pic_start_end            :23,	//  1:23
	ctrl_gx_pic_start_end           : 3,	// 24:26
	idx_gx_pic_start_end            : 5;	// 27:31
} GX_PIC_START_END_PROC;

/*-----------------------------------------------------------------------------
	0x00ec ctrl_monitor ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ctrl_monitor                    ;   	// 31: 0
} CTRL_MONITOR;

/*-----------------------------------------------------------------------------
	0x00f0 ctrl_pic_end ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	g0_pic_end_en                   : 1,	//     0
	g1_pic_end_en                   : 1,	//     1
	g2_pic_end_en                   : 1,	//     2
	g3_pic_end_en                   : 1,	//     3
	g4_pic_end_en                   : 1,	//     4
	g5_pic_end_en                   : 1,	//     5
	g6_pic_end_en                   : 1,	//     6
	g7_pic_end_en                   : 1,	//     7
	b0_pic_end_en                   : 1,	//     8
	b1_pic_end_en                   : 1,	//     9
	b2_pic_end_en                   : 1,	//    10
	b3_pic_end_en                   : 1,	//    11
	b4_pic_end_en                   : 1,	//    12
	b5_pic_end_en                   : 1,	//    13
	b6_pic_end_en                   : 1,	//    14
	b7_pic_end_en                   : 1,	//    15
	pic_end_g0_force_en             : 1,	//    16
	pic_end_g1_force_en             : 1,	//    17
	pic_end_g2_force_en             : 1,	//    18
	pic_end_g3_force_en             : 1,	//    19
	pic_end_g4_force_en             : 1,	//    20
	pic_end_g5_force_en             : 1,	//    21
	pic_end_g6_force_en             : 1,	//    22
	pic_end_g7_force_en             : 1,	//    23
	pic_end_g0_force_value          : 1,	//    24
	pic_end_g1_force_value          : 1,	//    25
	pic_end_g2_force_value          : 1,	//    26
	pic_end_g3_force_value          : 1,	//    27
	pic_end_g4_force_value          : 1,	//    28
	pic_end_g5_force_value          : 1,	//    29
	pic_end_g6_force_value          : 1,	//    30
	pic_end_g7_force_value          : 1;	//    31
} CTRL_PIC_END;

/*-----------------------------------------------------------------------------
	0x00f4 info_pic_end ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	g0_pic_end                      : 1,	//     0
	g1_pic_end                      : 1,	//     1
	g2_pic_end                      : 1,	//     2
	g3_pic_end                      : 1,	//     3
	g4_pic_end                      : 1,	//     4
	g5_pic_end                      : 1,	//     5
	g6_pic_end                      : 1,	//     6
	g7_pic_end                      : 1,	//     7
	                                : 8,	//  8:15 reserved
	g0_pic_end_init                 : 1,	//    16
	g1_pic_end_init                 : 1,	//    17
	g2_pic_end_init                 : 1,	//    18
	g3_pic_end_init                 : 1,	//    19
	g4_pic_end_init                 : 1,	//    20
	g5_pic_end_init                 : 1,	//    21
	g6_pic_end_init                 : 1,	//    22
	g7_pic_end_init                 : 1;	//    23
} INFO_PIC_END;

/*-----------------------------------------------------------------------------
	0x00f8 ctrl_gpio ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ctrl_gpio                   :24,	//  0:23
	sosd_clk                        : 1,	//    24
	spip_clk                        : 1,	//    25
	out_clk                         : 1,	//    26
	                                : 1,	//    27 reserved
	display_mode                    : 2;	// 28:29
} CTRL_GPIO;

/*-----------------------------------------------------------------------------
	0x00fc ctrl_gmau ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_ask_cmd_dly_cnt_r0         : 8,	//  0: 7
	osd1_ask_cmd_dly_cnt_r1         : 8,	//  8:15
	ask_to_cnt                      : 8;	// 16:23
} CTRL_GMAU;

#endif

typedef struct {
#if 1
	UINT32								__skip_00[10]					;	// 0x0000~0x0028
#else
	PIC_INIT                        	pic_init                        ;	// 0x0000 : ''
	PIC_START                       	pic_start                       ;	// 0x0004 : ''
	CTRL_AUTO_INIT                  	ctrl_auto_init                  ;	// 0x0008 : ''
	CTRL_INTR_PULSE                 	ctrl_intr_pulse                 ;	// 0x000c : ''
	INTR_REG                        	intr_reg                        ;	// 0x0010 : ''

	INTR_MASK                       	intr_mask                       ;	// 0x0014 : ''
	INTR_MUX                        	intr_mux                        ;	// 0x0018 : ''
	INTR_EN                         	intr_en                         ;	// 0x001c : ''
	CTRL_INFO                       	ctrl_info                       ;	// 0x0020 : ''
	CTRL_CC_DATA_DLY                	ctrl_cc_data_dly                ;	// 0x0024 : ''
#endif

	CTRL_OSD_CHANGE                 	ctrl_osd_change                 ;	// 0x0028 : ''

#if 1
	UINT32								__skip_01[53]					;	// 0x002c~0x0100
#else
	CTRL_OSD_PIP_MERGE              	ctrl_osd_pip_merge              ;	// 0x002c : ''
	CTRL_DATA_DLY                   	ctrl_data_dly                   ;	// 0x0030 : ''
	CTRL_OSD_120_SYNC_DLY0          	ctrl_osd_120_sync_dly0          ;	// 0x0034 : ''
	CTRL_OSD_120_SYNC_DLY1          	ctrl_osd_120_sync_dly1          ;	// 0x0038 : ''
	CTRL_OSD_120_SYNC_DLY2          	ctrl_osd_120_sync_dly2          ;	// 0x003c : ''
	CTRL_OSD_120_SYNC_DLY3          	ctrl_osd_120_sync_dly3          ;	// 0x0040 : ''
	CTRL_OSD_120_SYNC_DLY4          	ctrl_osd_120_sync_dly4          ;	// 0x0044 : ''
	CTRL_OSD_120_SYNC_DLY5          	ctrl_osd_120_sync_dly5          ;	// 0x0048 : ''
	CTRL_OSD_120_SYNC_DLY6          	ctrl_osd_120_sync_dly6          ;	// 0x004c : ''
	CTRL_OSD_120_SYNC_DLY7          	ctrl_osd_120_sync_dly7          ;	// 0x0050 : ''
	CTRL_OSD_120_SYNC_DLY8          	ctrl_osd_120_sync_dly8          ;	// 0x0054 : ''
	CTRL_OSD_120_SYNC_DLY9          	ctrl_osd_120_sync_dly9          ;	// 0x0058 : ''
	CTRL_OSD_120_SYNC_DLYA          	ctrl_osd_120_sync_dlya          ;	// 0x005c : ''
	CTRL_CCO_PPD_CTRL0              	ctrl_cco_ppd_ctrl0              ;	// 0x0060 : ''
	CTRL_CCO_PPD_CTRL1              	ctrl_cco_ppd_ctrl1              ;	// 0x0064 : ''
	CTRL_BOSD_PULSE                 	ctrl_bosd_pulse                 ;	// 0x0068 : ''
	CTRL_SOSD_PULSE                 	ctrl_sosd_pulse                 ;	// 0x006c : ''
	CTRL_BOSD_INIT_2ND              	ctrl_bosd_init_2nd              ;	// 0x0070 : ''
	CTRL_SOSD_INIT_2ND              	ctrl_sosd_init_2nd              ;	// 0x0074 : ''
	UINT32                          	                 __rsvd_00[   2];	// 0x0078 ~ 0x007c
	CTRL_L3D_DMA_SIZE               	ctrl_l3d_dma_size               ;	// 0x0080 : ''
	CTRL_L3D_DMA_CTRL               	ctrl_l3d_dma_ctrl               ;	// 0x0084 : ''
	CTRL_RO_L3D_VCNT                	ctrl_ro_l3d_vcnt                ;	// 0x0088 : ''
	CTRL_VR360_ON                   	ctrl_vr360_on                   ;	// 0x008c : ''
	CTRL_CG_ON                      	ctrl_cg_on                      ;	// 0x0090 : ''
	CTRL_CG_ON_SYNC                 	ctrl_cg_on_sync                 ;	// 0x0094 : ''
	CTRL_VR360_VID_DATA0            	ctrl_vr360_vid_data0            ;	// 0x0098 : ''
	CTRL_VR360_VID_DATA1            	ctrl_vr360_vid_data1            ;	// 0x009c : ''
	CTRL_VX1_CONTROL_PACKET0        	ctrl_vx1_control_packet0        ;	// 0x00a0 : ''
	CTRL_VX1_CONTROL_PACKET1        	ctrl_vx1_control_packet1        ;	// 0x00a4 : ''
	CTRL_VX1_CONTROL_PACKET2        	ctrl_vx1_control_packet2        ;	// 0x00a8 : ''
	CTRL_VX1_CONTROL_PACKET3        	ctrl_vx1_control_packet3        ;	// 0x00ac : ''
	CTRL_VX1_CONTROL_PACKET4        	ctrl_vx1_control_packet4        ;	// 0x00b0 : ''
	CTRL_VX1_CONTROL_PACKET5        	ctrl_vx1_control_packet5        ;	// 0x00b4 : ''
	CTRL_VX1_CONTROL_PACKET6        	ctrl_vx1_control_packet6        ;	// 0x00b8 : ''
	AXI_USER_CCO                    	axi_user_cco                    ;	// 0x00bc : ''
	PIC_INIT_G0_TIMER               	pic_init_g0_timer               ;	// 0x00c0 : ''
	PIC_INIT_G1_TIMER               	pic_init_g1_timer               ;	// 0x00c4 : ''
	PIC_INIT_G2_TIMER               	pic_init_g2_timer               ;	// 0x00c8 : ''
	PIC_INIT_G3_TIMER               	pic_init_g3_timer               ;	// 0x00cc : ''
	PIC_INIT_G4_TIMER               	pic_init_g4_timer               ;	// 0x00d0 : ''
	PIC_INIT_G5_TIMER               	pic_init_g5_timer               ;	// 0x00d4 : ''
	PIC_INIT_G6_TIMER               	pic_init_g6_timer               ;	// 0x00d8 : ''
	PIC_INIT_G7_TIMER               	pic_init_g7_timer               ;	// 0x00dc : ''
	UINT32                          	                 __rsvd_01[   1];	// 0x00e0
	DBG_TIMER_RUN                   	dbg_timer_run                   ;	// 0x00e4 : ''
	GX_PIC_START_END_PROC           	gx_pic_start_end_proc           ;	// 0x00e8 : ''
	CTRL_MONITOR                    	ctrl_monitor                    ;	// 0x00ec : ''
	CTRL_PIC_END                    	ctrl_pic_end                    ;	// 0x00f0 : ''
	INFO_PIC_END                    	info_pic_end                    ;	// 0x00f4 : ''
	CTRL_GPIO                       	ctrl_gpio                       ;	// 0x00f8 : ''
	CTRL_GMAU                       	ctrl_gmau                       ;	// 0x00fc : ''
#endif
} OSD_TOP_CTRL1_O24_REG_T;
/* 61 regs, 61 types */

/* 61 regs, 61 types in Total*/

// *INDENT-ON*

#define OSD_TOP_CTRL1_RdFL(_r)          ((g_osd_top_ctrl1_o24_reg_shadow->_r)=(g_osd_top_ctrl1_o24_reg->_r))
#define OSD_TOP_CTRL1_WrFL(_r)          ((g_osd_top_ctrl1_o24_reg->_r)=(g_osd_top_ctrl1_o24_reg_shadow->_r))

#define OSD_TOP_CTRL1_Rd(_r)            *((UINT32*)(&(g_osd_top_ctrl1_o24_reg_shadow->_r)))
#define OSD_TOP_CTRL1_Wr(_r,_v)         ((OSD_TOP_CTRL1_Rd(_r))=((UINT32)(_v)))

#define OSD_TOP_CTRL1_Rd01(_r,_f01,_v01)                                                \
                                do {                                                    \
                                    (_v01) = (g_osd_top_ctrl1_o24_reg_shadow->_r._f01); \
                                } while(0)

#define OSD_TOP_CTRL1_Rd02(_r,_f01,_v01,_f02,_v02)                                      \
                                do {                                                    \
                                    (_v01) = (g_osd_top_ctrl1_o24_reg_shadow->_r._f01); \
                                    (_v02) = (g_osd_top_ctrl1_o24_reg_shadow->_r._f02); \
                                } while(0)

#define OSD_TOP_CTRL1_Wr01(_r,_f01,_v01)                                                \
                                do {                                                    \
                                    (g_osd_top_ctrl1_o24_reg_shadow->_r._f01) = (_v01); \
                                } while(0)

#define OSD_TOP_CTRL1_Wr02(_r,_f01,_v01,_f02,_v02)                                      \
                                do {                                                    \
                                    (g_osd_top_ctrl1_o24_reg_shadow->_r._f01) = (_v01); \
                                    (g_osd_top_ctrl1_o24_reg_shadow->_r._f02) = (_v02); \
                                } while(0)

extern volatile OSD_TOP_CTRL1_O24_REG_T*    g_osd_top_ctrl1_o24_reg;
extern OSD_TOP_CTRL1_O24_REG_T*             g_osd_top_ctrl1_o24_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O24-A0_PQE_TopCTRL1_reg_man.csv' 20230407 14:48:35 KST by getregs v2.9 */
