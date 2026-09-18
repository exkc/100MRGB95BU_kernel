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

#ifndef __OSD_TOP_CTRL_REG_O24_H__
#define __OSD_TOP_CTRL_REG_O24_H__

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
	0x0020 ctrl_dpath ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ccout_dpath                 : 1,	//     0
	reg_mm_test_en                  : 1,	//     1
	reg_ld_en                       : 1,	//     2
	reg_8k_bypass_en                : 1,	//     3
	reg_rgb2yc_o_en                 : 1,	//     4
	reg_rgb2yc_e_en                 : 1,	//     5
	reg_yc2rgb_o_en                 : 1,	//     6
	reg_yc2rgb_e_en                 : 1,	//     7
	reg_mm_test_sel                 : 2,	//  8: 9
	reg_gate_cmd_len1               : 1,	//    10
	reg_gate_cmd_len0               : 1,	//    11
	reg_dds_detour_en               : 1,	//    12
	reg_mpip_merge_en               : 1,	//    13
	sel_osd_src_bosd1               : 1,	//    14
	sel_osd_src_sosd                : 2,	// 15:16
	mon_sync_mv_off                 : 1,	//    17
	mon_sync_so_on                  : 1,	//    18
	unaligned_addr_en               : 1,	//    19
	osd0_afbc_en                    : 1,	//    20
	reg_bosd1_detour_en             : 1,	//    21
	reg_bosd0_detour_en_n           : 1,	//    22
	                                : 1,	//    23 reserved
	osd1_afbc_en                    : 1,	//    24
	reg_sync_mon_sel                : 3,	// 25:27
	detour_en                       : 1,	//    28
	reg_sel_mif_cmd_dly             : 1,	//    29
	reg_sel_mif_axuser              : 2;	// 30:31
} CTRL_DPATH;

/*-----------------------------------------------------------------------------
	0x0024 ctrl_spath ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cco_dpe_o_vs_sel                : 3,	//  0: 2
	cco_dpe_o_hs_sel                : 3,	//  3: 5
	cco_dpe_o_va_sel                : 3,	//  6: 8
	cco_dpe_o_ha_sel                : 3,	//  9:11
	ctrl_vid_src_va                 : 1,	//    12
	ctrl_bosd_src_vs                : 2,	// 13:14
	ctrl_bosd_src_va                : 2,	// 15:16
	ctrl_bosd_src_de                : 2,	// 17:18
	ctrl_sosd_src_vs                : 1,	//    19
	ctrl_sosd_src_va                : 1,	//    20
	ctrl_sosd_src_de                : 1,	//    21
	osd_sync_gen_vs_in              : 1,	//    22
	osd_sync_gen_hs_in              : 1,	//    23
	osd_sync_gen_va_in              : 1,	//    24
	osd_sync_gen_ha_in              : 1,	//    25
	gcf_sync_mask_en                : 1,	//    26
	mof_sync_mask_sel               : 2,	// 27:28
	ctrl_vid_src_vs                 : 1,	//    29
	gcf_vs_sel                      : 2;	// 30:31
} CTRL_SPATH;

/*-----------------------------------------------------------------------------
	0x0028 ctrl_3d_flag ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_flag_3d_lr_force_value      : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_flag_3d_lr_force_en         : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_flag_3d_force_value         : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_flag_3d_force_en            : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_8k_bypass_pip_dly_num       : 6;	// 16:21
} CTRL_3D_FLAG;

/*-----------------------------------------------------------------------------
	0x002c ctrl_block ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_path_reset_en_vid           : 1,	//     0
	reg_path_reset_en_obc           : 1,	//     1
	reg_path_reset_en_mt            : 1,	//     2
	reg_path_reset_en_pkt           : 1,	//     3
	reg_bosd1_insel                 : 2,	//  4: 5
	                                : 2,	//  6: 7 reserved
	reg_afbc_afrc_sel               : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_sasync_ccpathen             : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_8k_bypass_dly_num           : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_sosd_out_mask               : 3,	// 24:26
	                                : 4,	// 27:30 reserved
	reg_isync_pluse_sel             : 1;	//    31
} CTRL_BLOCK;

/*-----------------------------------------------------------------------------
	0x0030 ctrl_bosd_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_disp_pulse_timer            :28,	//  0:27
	reg_disp_pulse_src_sel          : 1,	//    28
	reg_disp_pulse_src_inv          : 1;	//    29
} CTRL_BOSD_PULSE;

/*-----------------------------------------------------------------------------
	0x0034 ctrl_sosd_pulse ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_disp_pulse_timer            :28,	//  0:27
	reg_disp_pulse_src_sel          : 1,	//    28
	reg_disp_pulse_src_inv          : 1;	//    29
} CTRL_SOSD_PULSE;

/*-----------------------------------------------------------------------------
	0x0038 ctrl_auto_init_afbc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_afbc0_init_en               : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_afbc0_auto_init_en          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_afbc0_auto_init_src         : 1,	//     8
	                                : 3,	//  9:11 reserved
	idx_afbc0_pic_init_src          : 3,	// 12:14
	reg_afbc0_partial_ack_en        : 1,	//    15
	reg_afbc1_init_en               : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_afbc1_auto_init_en          : 1,	//    20
	                                : 3,	// 21:23 reserved
	reg_afbc1_auto_init_src         : 1,	//    24
	                                : 3,	// 25:27 reserved
	idx_afbc1_pic_init_src          : 3,	// 28:30
	reg_afbc1_partial_ack_en        : 1;	//    31
} CTRL_AUTO_INIT_AFBC;

/*-----------------------------------------------------------------------------
	0x003c ctrl_auto_init_lencon ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lencon0_init_en             : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_lencon0_auto_init_en        : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_lencon0_auto_init_src       : 1,	//     8
	                                : 3,	//  9:11 reserved
	idx_lencon0_pic_init_src        : 3,	// 12:14
	sel_lencon0_pic_init_src        : 1,	//    15
	reg_lencon1_init_en             : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_lencon1_auto_init_en        : 1,	//    20
	                                : 3,	// 21:23 reserved
	reg_lencon1_auto_init_src       : 1,	//    24
	                                : 3,	// 25:27 reserved
	idx_lencon1_pic_init_src        : 3,	// 28:30
	sel_lencon1_pic_init_src        : 1;	//    31
} CTRL_AUTO_INIT_LENCON;

/*-----------------------------------------------------------------------------
	0x0044 ctrl_osd_init_2nd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd0_init_2nd_en                : 1,	//     0
	osd0_init_2nd_sel               : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd1_init_2nd_en                : 1,	//     4
	osd1_init_2nd_sel               : 1,	//     5
	                                : 2,	//  6: 7 reserved
	osd2_init_2nd_en                : 1,	//     8
	osd2_init_2nd_sel               : 1,	//     9
	                                : 2,	// 10:11 reserved
	osd3_init_2nd_en                : 1,	//    12
	osd3_init_2nd_sel               : 1,	//    13
	                                : 2,	// 14:15 reserved
	osd4_init_2nd_en                : 1,	//    16
	osd4_init_2nd_sel               : 1,	//    17
	                                : 2,	// 18:19 reserved
	osd5_init_2nd_en                : 1,	//    20
	osd5_init_2nd_sel               : 1,	//    21
	                                : 2,	// 22:23 reserved
	osd6_init_2nd_en                : 1,	//    24
	osd6_init_2nd_sel               : 1,	//    25
	                                : 2,	// 26:27 reserved
	osd7_init_2nd_en                : 1,	//    28
	osd7_init_2nd_sel               : 1;	//    29
} CTRL_OSD_INIT_2ND;

/*-----------------------------------------------------------------------------
	0x0048 ctrl_bosd_init_2nd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bosd_init_2nd_line              :16,	//  0:15
	                                :12,	// 16:27 reserved
	bosd_init_2nd_en                : 1;	//    28
} CTRL_BOSD_INIT_2ND;

/*-----------------------------------------------------------------------------
	0x004c ctrl_sosd_init_2nd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	bosd_init_2nd_line              :16,	//  0:15
	                                :12,	// 16:27 reserved
	bosd_init_2nd_en                : 1;	//    28
} CTRL_SOSD_INIT_2ND;

/*-----------------------------------------------------------------------------
	0x0050 ctrl_cc_top ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 4,	//  0: 3 reserved
	reg_cc_detour                   : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_cc_8k_en                    : 1;	//     8
} CTRL_CC_TOP;

/*-----------------------------------------------------------------------------
	0x0054 ctrl_dco_gcf_fb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cco_fb_mux                      : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_gcf_rgb2yc_o_en             : 1,	//     4
	reg_gcf_rgb2yc_e_en             : 1,	//     5
	enable_dco_dfc_on_gcf           : 1,	//     6
	sel_src_dco_dfc                 : 2;	//  7: 8
} CTRL_DCO_GCF_FB;

/*-----------------------------------------------------------------------------
	0x0060 ctrl_fbdc0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_1x2_bypass_en          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd0_1x2_sel_id             : 4,	//  4: 7
	reg_fbdc0_ctrl_path             : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_fbdc0_ctrl_comp             : 4,	// 12:15
	reg_fbdc0_ctrl_alpha            : 4,	// 16:19
	                                : 4,	// 20:23 reserved
	reg_fbdc0_ctrl_dbg_sel          : 6;	// 24:29
} CTRL_FBDC0;

/*-----------------------------------------------------------------------------
	0x0064 info_fbdc0_dbg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :24,	//  0:23 reserved
	info_fbdc0_dbg                  : 6;	// 24:29
} INFO_FBDC0_DBG;

/*-----------------------------------------------------------------------------
	0x0068 ctrl_fbdc1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd1_1x2_bypass_en          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd1_1x2_sel_id             : 4,	//  4: 7
	reg_fbdc1_ctrl_path             : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_fbdc1_ctrl_comp             : 4,	// 12:15
	reg_fbdc1_ctrl_alpha            : 4,	// 16:19
	                                : 4,	// 20:23 reserved
	reg_fbdc1_ctrl_dbg_sel          : 6;	// 24:29
} CTRL_FBDC1;

/*-----------------------------------------------------------------------------
	0x006c info_fbdc1_dbg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :24,	//  0:23 reserved
	info_fbdc1_dbg                  : 6;	// 24:29
} INFO_FBDC1_DBG;

/*-----------------------------------------------------------------------------
	0x0070 ctrl_dly_disp_sync_param0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vsync                           :16,	//  0:15
	vfp                             :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM0;

/*-----------------------------------------------------------------------------
	0x0074 ctrl_dly_disp_sync_param1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	va                              :16,	//  0:15
	vbp                             :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM1;

/*-----------------------------------------------------------------------------
	0x0078 ctrl_dly_disp_sync_param2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hsync                           :16,	//  0:15
	hfp                             :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM2;

/*-----------------------------------------------------------------------------
	0x007c ctrl_dly_disp_sync_param3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ha                              :16,	//  0:15
	hbp                             :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM3;

/*-----------------------------------------------------------------------------
	0x0080 ctrl_dly_disp_sync_param4 ''
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
} CTRL_DLY_DISP_SYNC_PARAM4;

/*-----------------------------------------------------------------------------
	0x0084 ctrl_dly_disp_sync_param5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sync_h_dly                      :16,	//  0:15
	sync_v_dly                      :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM5;

/*-----------------------------------------------------------------------------
	0x0088 ctrl_dly_disp_sync_param6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	manual_cnt_h_value              :16,	//  0:15
	manual_cnt_v_value              :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAM6;

/*-----------------------------------------------------------------------------
	0x008c ctrl_dly_disp_sync_param7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_delay_ha                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_delay_va                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_DLY_DISP_SYNC_PARAM7;

/*-----------------------------------------------------------------------------
	0x0090 ctrl_dly_disp_sync_param8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_delay_hs                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_delay_vs                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_DLY_DISP_SYNC_PARAM8;

/*-----------------------------------------------------------------------------
	0x0094 ctrl_dly_disp_sync_param9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	line_cnt_threshold              :16;	//  0:15
} CTRL_DLY_DISP_SYNC_PARAM9;

/*-----------------------------------------------------------------------------
	0x0098 ctrl_dly_disp_sync_parama ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rst_pos_cnt_h                   :16,	//  0:15
	rst_pos_cnt_v                   :16;	// 16:31
} CTRL_DLY_DISP_SYNC_PARAMA;

/*-----------------------------------------------------------------------------
	0x00a0 osd_sync_gen_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vsync                           :16,	//  0:15
	vfp                             :16;	// 16:31
} OSD_SYNC_GEN_CTRL0;

/*-----------------------------------------------------------------------------
	0x00a4 osd_sync_gen_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	va                              :16,	//  0:15
	vbp                             :16;	// 16:31
} OSD_SYNC_GEN_CTRL1;

/*-----------------------------------------------------------------------------
	0x00a8 osd_sync_gen_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hsync                           :16,	//  0:15
	hfp                             :16;	// 16:31
} OSD_SYNC_GEN_CTRL2;

/*-----------------------------------------------------------------------------
	0x00ac osd_sync_gen_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ha                              :16,	//  0:15
	hbp                             :16;	// 16:31
} OSD_SYNC_GEN_CTRL3;

/*-----------------------------------------------------------------------------
	0x00b0 osd_sync_gen_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	prev_vsync                      :16,	//  0:15
	prev_vfp                        :16;	// 16:31
} OSD_SYNC_GEN_CTRL4;

/*-----------------------------------------------------------------------------
	0x00b4 osd_sync_gen_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	prev_va                         :16,	//  0:15
	prev_vbp                        :16;	// 16:31
} OSD_SYNC_GEN_CTRL5;

/*-----------------------------------------------------------------------------
	0x00b8 osd_sync_gen_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	line_start_pos                  :16,	//  0:15
	reg_free_run_mode_en            : 1,	//    16
	reg_sync_i_vs_edge_sel          : 1,	//    17
	reg_sync_i_hs_edge_sel          : 1,	//    18
	                                : 2,	// 19:20 reserved
	update_use_vs_i                 : 1,	//    21
	update_at_vs_rise               : 1,	//    22
	reg_h_cnt_reset_by_snyc         : 1,	//    23
	update_use_va_i                 : 1,	//    24
	update_use_ha_i                 : 1,	//    25
	                                : 2,	// 26:27 reserved
	manual_cnt_reset_h_value_en     : 1,	//    28
	manual_cnt_reset_v_value_en     : 1,	//    29
	                                : 1,	//    30 reserved
	force_update                    : 1;	//    31
} OSD_SYNC_GEN_CTRL6;

/*-----------------------------------------------------------------------------
	0x00bc osd_sync_gen_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	manual_h                        :16,	//  0:15
	manual_v                        :16;	// 16:31
} OSD_SYNC_GEN_CTRL7;

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
	spip_clk                        : 2,	// 24:25
	display_mode                    : 1,	//    26
	out1_clk                        : 2;	// 27:28
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

typedef struct {
	PIC_INIT                        	pic_init                        ;	// 0x0000 : ''
	PIC_START                       	pic_start                       ;	// 0x0004 : ''
	CTRL_AUTO_INIT                  	ctrl_auto_init                  ;	// 0x0008 : ''
	CTRL_INTR_PULSE                 	ctrl_intr_pulse                 ;	// 0x000c : ''
	INTR_REG                        	intr_reg                        ;	// 0x0010 : ''
	INTR_MASK                       	intr_mask                       ;	// 0x0014 : ''
	INTR_MUX                        	intr_mux                        ;	// 0x0018 : ''
	INTR_EN                         	intr_en                         ;	// 0x001c : ''
	CTRL_DPATH                      	ctrl_dpath                      ;	// 0x0020 : ''
	CTRL_SPATH                      	ctrl_spath                      ;	// 0x0024 : ''
	CTRL_3D_FLAG                    	ctrl_3d_flag                    ;	// 0x0028 : ''
	CTRL_BLOCK                      	ctrl_block                      ;	// 0x002c : ''
	CTRL_BOSD_PULSE                 	ctrl_bosd_pulse                 ;	// 0x0030 : ''
	CTRL_SOSD_PULSE                 	ctrl_sosd_pulse                 ;	// 0x0034 : ''
	CTRL_AUTO_INIT_AFBC             	ctrl_auto_init_afbc             ;	// 0x0038 : ''
	CTRL_AUTO_INIT_LENCON           	ctrl_auto_init_lencon           ;	// 0x003c : ''
	UINT32                          	                 __rsvd_00[   1];	// 0x0040
	CTRL_OSD_INIT_2ND               	ctrl_osd_init_2nd               ;	// 0x0044 : ''
	CTRL_BOSD_INIT_2ND              	ctrl_bosd_init_2nd              ;	// 0x0048 : ''
	CTRL_SOSD_INIT_2ND              	ctrl_sosd_init_2nd              ;	// 0x004c : ''
	CTRL_CC_TOP                     	ctrl_cc_top                     ;	// 0x0050 : ''
	CTRL_DCO_GCF_FB                 	ctrl_dco_gcf_fb                 ;	// 0x0054 : ''
	UINT32                          	                 __rsvd_01[   2];	// 0x0058 ~ 0x005c
	CTRL_FBDC0                      	ctrl_fbdc0                      ;	// 0x0060 : ''
	INFO_FBDC0_DBG                  	info_fbdc0_dbg                  ;	// 0x0064 : ''
	CTRL_FBDC1                      	ctrl_fbdc1                      ;	// 0x0068 : ''
	INFO_FBDC1_DBG                  	info_fbdc1_dbg                  ;	// 0x006c : ''
	CTRL_DLY_DISP_SYNC_PARAM0       	ctrl_dly_disp_sync_param0       ;	// 0x0070 : ''
	CTRL_DLY_DISP_SYNC_PARAM1       	ctrl_dly_disp_sync_param1       ;	// 0x0074 : ''
	CTRL_DLY_DISP_SYNC_PARAM2       	ctrl_dly_disp_sync_param2       ;	// 0x0078 : ''
	CTRL_DLY_DISP_SYNC_PARAM3       	ctrl_dly_disp_sync_param3       ;	// 0x007c : ''
	CTRL_DLY_DISP_SYNC_PARAM4       	ctrl_dly_disp_sync_param4       ;	// 0x0080 : ''
	CTRL_DLY_DISP_SYNC_PARAM5       	ctrl_dly_disp_sync_param5       ;	// 0x0084 : ''
	CTRL_DLY_DISP_SYNC_PARAM6       	ctrl_dly_disp_sync_param6       ;	// 0x0088 : ''
	CTRL_DLY_DISP_SYNC_PARAM7       	ctrl_dly_disp_sync_param7       ;	// 0x008c : ''
	CTRL_DLY_DISP_SYNC_PARAM8       	ctrl_dly_disp_sync_param8       ;	// 0x0090 : ''
	CTRL_DLY_DISP_SYNC_PARAM9       	ctrl_dly_disp_sync_param9       ;	// 0x0094 : ''
	CTRL_DLY_DISP_SYNC_PARAMA       	ctrl_dly_disp_sync_parama       ;	// 0x0098 : ''
	UINT32                          	                 __rsvd_02[   1];	// 0x009c
	OSD_SYNC_GEN_CTRL0              	osd_sync_gen_ctrl0              ;	// 0x00a0 : ''
	OSD_SYNC_GEN_CTRL1              	osd_sync_gen_ctrl1              ;	// 0x00a4 : ''
	OSD_SYNC_GEN_CTRL2              	osd_sync_gen_ctrl2              ;	// 0x00a8 : ''
	OSD_SYNC_GEN_CTRL3              	osd_sync_gen_ctrl3              ;	// 0x00ac : ''
	OSD_SYNC_GEN_CTRL4              	osd_sync_gen_ctrl4              ;	// 0x00b0 : ''
	OSD_SYNC_GEN_CTRL5              	osd_sync_gen_ctrl5              ;	// 0x00b4 : ''
	OSD_SYNC_GEN_CTRL6              	osd_sync_gen_ctrl6              ;	// 0x00b8 : ''
	OSD_SYNC_GEN_CTRL7              	osd_sync_gen_ctrl7              ;	// 0x00bc : ''
	PIC_INIT_G0_TIMER               	pic_init_g0_timer               ;	// 0x00c0 : ''
	PIC_INIT_G1_TIMER               	pic_init_g1_timer               ;	// 0x00c4 : ''
	PIC_INIT_G2_TIMER               	pic_init_g2_timer               ;	// 0x00c8 : ''
	PIC_INIT_G3_TIMER               	pic_init_g3_timer               ;	// 0x00cc : ''
	PIC_INIT_G4_TIMER               	pic_init_g4_timer               ;	// 0x00d0 : ''
	PIC_INIT_G5_TIMER               	pic_init_g5_timer               ;	// 0x00d4 : ''
	PIC_INIT_G6_TIMER               	pic_init_g6_timer               ;	// 0x00d8 : ''
	PIC_INIT_G7_TIMER               	pic_init_g7_timer               ;	// 0x00dc : ''
	UINT32                          	                 __rsvd_03[   1];	// 0x00e0
	DBG_TIMER_RUN                   	dbg_timer_run                   ;	// 0x00e4 : ''
	GX_PIC_START_END_PROC           	gx_pic_start_end_proc           ;	// 0x00e8 : ''
	CTRL_MONITOR                    	ctrl_monitor                    ;	// 0x00ec : ''
	CTRL_PIC_END                    	ctrl_pic_end                    ;	// 0x00f0 : ''
	INFO_PIC_END                    	info_pic_end                    ;	// 0x00f4 : ''
	CTRL_GPIO                       	ctrl_gpio                       ;	// 0x00f8 : ''
	CTRL_GMAU                       	ctrl_gmau                       ;	// 0x00fc : ''
} OSD_TOP_CTRL_O24_REG_T;
/* 59 regs, 59 types */

/* 59 regs, 59 types in Total*/

// *INDENT-ON*

#define OSD_TOP_CTRL_RdFL(_r)           ((g_osd_top_ctrl_o24_reg_shadow->_r)=(g_osd_top_ctrl_o24_reg->_r))
#define OSD_TOP_CTRL_WrFL(_r)           ((g_osd_top_ctrl_o24_reg->_r)=(g_osd_top_ctrl_o24_reg_shadow->_r))

#define OSD_TOP_CTRL_Rd(_r)             *((UINT32*)(&(g_osd_top_ctrl_o24_reg_shadow->_r)))
#define OSD_TOP_CTRL_Wr(_r,_v)          ((OSD_TOP_CTRL_Rd(_r))=((UINT32)(_v)))

#define OSD_TOP_CTRL_Rd01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (_v01) = (g_osd_top_ctrl_o24_reg_shadow->_r._f01);  \
                                } while(0)

#define OSD_TOP_CTRL_Rd02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (_v01) = (g_osd_top_ctrl_o24_reg_shadow->_r._f01);  \
                                    (_v02) = (g_osd_top_ctrl_o24_reg_shadow->_r._f02);  \
                                } while(0)

#define OSD_TOP_CTRL_Wr01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (g_osd_top_ctrl_o24_reg_shadow->_r._f01) = (_v01);  \
                                } while(0)

#define OSD_TOP_CTRL_Wr02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (g_osd_top_ctrl_o24_reg_shadow->_r._f01) = (_v01);  \
                                    (g_osd_top_ctrl_o24_reg_shadow->_r._f02) = (_v02);  \
                                } while(0)

extern volatile OSD_TOP_CTRL_O24_REG_T* g_osd_top_ctrl_o24_reg;
extern OSD_TOP_CTRL_O24_REG_T*          g_osd_top_ctrl_o24_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O24-A0_PQE_TopCTRL_reg_man.csv' 20230407 14:48:29 KST by getregs v2.9 */
