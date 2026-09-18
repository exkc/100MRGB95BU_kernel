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

#ifndef _CVD_REG_O18A0_H_
#define _CVD_REG_O18A0_H_

/*-----------------------------------------------------------------------------
		0xc8000600L cvd_intr1_enable0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_enable0                  : 32;  // 31: 0     
} O18A0_CVD_INTR1_ENABLE0_T;

/*-----------------------------------------------------------------------------
		0xc8000604L cvd_intr1_intr0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_chromalock_fal                 : 1 ;  //     0     
	UINT32 cvd_chromalock_ris                 : 1 ;  //     1     
	UINT32 cvd_vlock_fal                      : 1 ;  //     2     
	UINT32 cvd_vlock_ris                      : 1 ;  //     3     
	UINT32 cvd_hlock_fal                      : 1 ;  //     4     
	UINT32 cvd_hlock_ris                      : 1 ;  //     5     
	UINT32 cvd_no_signal_fal                  : 1 ;  //     6     
	UINT32 cvd_no_signal_ris                  : 1 ;  //     7     
	UINT32 cvd_noburst_detected_fal           : 1 ;  //     8     
	UINT32 cvd_noburst_detected_ris           : 1 ;  //     9     
	UINT32 cvd_vnon_standard_fal              : 1 ;  //    10     
	UINT32 cvd_vnon_standard_ris              : 1 ;  //    11     
	UINT32 cvd_hnon_standard_fal              : 1 ;  //    12     
	UINT32 cvd_hnon_standard_ris              : 1 ;  //    13     
	UINT32 cvd_proscan_detected_fal           : 1 ;  //    14     
	UINT32 cvd_proscan_detected_ris           : 1 ;  //    15     
	UINT32 cvd_vcr_fal                        : 1 ;  //    16     
	UINT32 cvd_vcr_ris                        : 1 ;  //    17     
	UINT32 cvd_noisy_fal                      : 1 ;  //    18     
	UINT32 cvd_noisy_ris                      : 1 ;  //    19     
	UINT32 cvd_vline_625_detected_fal         : 1 ;  //    20     
	UINT32 cvd_vline_625_detected_ris         : 1 ;  //    21     
	UINT32 cvd_secam_detected_fal             : 1 ;  //    22     
	UINT32 cvd_secam_detected_ris             : 1 ;  //    23     
	UINT32 cvd_pal_detected_fal               : 1 ;  //    24     
	UINT32 cvd_pal_detected_ris               : 1 ;  //    25     
	UINT32 cvd_vs_fal                         : 1 ;  //    26     
	UINT32 cvd_vs_ris                         : 1 ;  //    27     
	UINT32 cvd_ext_locked_fal                 : 1 ;  //    28     
	UINT32 cvd_ext_locked_ris                 : 1 ;  //    29     
	UINT32 cvd_fine_hlock_fal                 : 1 ;  //    30     
	UINT32 resolved                           : 1 ;  //    31     
} O18A0_CVD_INTR1_INTR0_T;

/*-----------------------------------------------------------------------------
		0xc8000608L cvd_intr1_clear0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_clear0                   : 32;  // 31: 0     
} O18A0_CVD_INTR1_CLEAR0_T;

/*-----------------------------------------------------------------------------
		0xc800060cL cvd_intr1_enable1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_enable1                  : 32;  // 31: 0     
} O18A0_CVD_INTR1_ENABLE1_T;

/*-----------------------------------------------------------------------------
		0xc8000610L cvd_intr1_intr1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_wss_rdy                        : 1 ;  //     0     
	UINT32 vbi_cc_rdy                         : 1 ;  //     1     
	UINT32 vbi_data_in                        : 1 ;  //     2     
	UINT32 cvd_fb_rst                         : 1 ;  //     3     
	UINT32 cvd_mif_err                        : 1 ;  //     4     
	UINT32 cs_chromalock_fal                  : 1 ;  //     5     
	UINT32 cs_chromalock_ris                  : 1 ;  //     6     
	UINT32 cs_pal_detected_fal                : 1 ;  //     7     
	UINT32 cs_pal_detected_ris                : 1 ;  //     8     
	UINT32 cs_secam_detected_fal              : 1 ;  //     9     
	UINT32 cs_secam_detected_ris              : 1 ;  //    10     
	UINT32 cs1_chromalock_fal                 : 1 ;  //    11     
	UINT32 cs1_chromalock_ris                 : 1 ;  //    12     
	UINT32 cs1_pal_detected_fal               : 1 ;  //    13     
	UINT32 cs1_pal_detected_ris               : 1 ;  //    14     
	UINT32 cs1_secam_detected_fal             : 1 ;  //    15     
	UINT32 cs1_secam_detected_ris             : 1 ;  //    16     
	UINT32 estfrdp_err_flag_fal               : 1 ;  //    17     
	UINT32 estfrdp_err_flag_ris               : 1 ;  //    18     
	UINT32 vdetect_vcount_fal                 : 1 ;  //    19     
	UINT32 vdetect_vcount_ris                 : 1 ;  //    20     
	UINT32 cvd_mif_err_md                     : 1 ;  //    21     
	UINT32 ro_wbuf_read_req_cnt_mx_lvl_md     : 1 ;  //    22     
	UINT32 ro_read0_svid_cnt_mx_lvl_md        : 1 ;  //    23     
	UINT32 ro_wbuf_full_md                    : 1 ;  //    24     
	UINT32 ro_rbuf_empty_md                   : 1 ;  //    25     
	UINT32 ro_wbuf_read_req_cnt_mx_lvl        : 1 ;  //    26     
	UINT32 ro_read0_svid_cnt_mx_lvl           : 1 ;  //    27     
	UINT32 ro_wbuf_full                       : 1 ;  //    28     
	UINT32 ro_rbuf_empty                      : 1 ;  //    29     
	UINT32 status_comb3d_off                  : 1 ;  //    30     
	UINT32 cvd_fine_hlock_ris                 : 1 ;  //    31     
} O18A0_CVD_INTR1_INTR1_T;

/*-----------------------------------------------------------------------------
		0xc8000614L cvd_intr1_clear1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr1_clear1                   : 32;  // 31: 0     
} O18A0_CVD_INTR1_CLEAR1_T;

/*-----------------------------------------------------------------------------
		0xc8000618L cvd_intr2_enable0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_enable0                  : 32;  // 31: 0     
} O18A0_CVD_INTR2_ENABLE0_T;

/*-----------------------------------------------------------------------------
		0xc800061cL cvd_intr2_intr0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_chromalock_fal                 : 1 ;  //     0     
	UINT32 cvd_chromalock_ris                 : 1 ;  //     1     
	UINT32 cvd_vlock_fal                      : 1 ;  //     2     
	UINT32 cvd_vlock_ris                      : 1 ;  //     3     
	UINT32 cvd_hlock_fal                      : 1 ;  //     4     
	UINT32 cvd_hlock_ris                      : 1 ;  //     5     
	UINT32 cvd_no_signal_fal                  : 1 ;  //     6     
	UINT32 cvd_no_signal_ris                  : 1 ;  //     7     
	UINT32 cvd_noburst_detected_fal           : 1 ;  //     8     
	UINT32 cvd_noburst_detected_ris           : 1 ;  //     9     
	UINT32 cvd_vnon_standard_fal              : 1 ;  //    10     
	UINT32 cvd_vnon_standard_ris              : 1 ;  //    11     
	UINT32 cvd_hnon_standard_fal              : 1 ;  //    12     
	UINT32 cvd_hnon_standard_ris              : 1 ;  //    13     
	UINT32 cvd_proscan_detected_fal           : 1 ;  //    14     
	UINT32 cvd_proscan_detected_ris           : 1 ;  //    15     
	UINT32 cvd_vcr_fal                        : 1 ;  //    16     
	UINT32 cvd_vcr_ris                        : 1 ;  //    17     
	UINT32 cvd_noisy_fal                      : 1 ;  //    18     
	UINT32 cvd_noisy_ris                      : 1 ;  //    19     
	UINT32 cvd_vline_625_detected_fal         : 1 ;  //    20     
	UINT32 cvd_vline_625_detected_ris         : 1 ;  //    21     
	UINT32 cvd_secam_detected_fal             : 1 ;  //    22     
	UINT32 cvd_secam_detected_ris             : 1 ;  //    23     
	UINT32 cvd_pal_detected_fal               : 1 ;  //    24     
	UINT32 cvd_pal_detected_ris               : 1 ;  //    25     
	UINT32 cvd_vs_fal                         : 1 ;  //    26     
	UINT32 cvd_vs_ris                         : 1 ;  //    27     
	UINT32 cvd_ext_locked_fal                 : 1 ;  //    28     
	UINT32 cvd_ext_locked_ris                 : 1 ;  //    29     
	UINT32 cvd_fine_hlock_fal                 : 1 ;  //    30     
	UINT32 resolved                           : 1 ;  //    31     
} O18A0_CVD_INTR2_INTR0_T;

/*-----------------------------------------------------------------------------
		0xc8000620L cvd_intr2_clear0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_clear0                   : 32;  // 31: 0     
} O18A0_CVD_INTR2_CLEAR0_T;

/*-----------------------------------------------------------------------------
		0xc8000624L cvd_intr2_enable1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_enable1                  : 32;  // 31: 0     
} O18A0_CVD_INTR2_ENABLE1_T;

/*-----------------------------------------------------------------------------
		0xc8000628L cvd_intr2_intr1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vbi_wss_rdy                        : 1 ;  //     0     
	UINT32 vbi_cc_rdy                         : 1 ;  //     1     
	UINT32 vbi_data_in                        : 1 ;  //     2     
	UINT32 cvd_fb_rst                         : 1 ;  //     3     
	UINT32 cvd_mif_err                        : 1 ;  //     4     
	UINT32 cs_chromalock_fal                  : 1 ;  //     5     
	UINT32 cs_chromalock_ris                  : 1 ;  //     6     
	UINT32 cs_pal_detected_fal                : 1 ;  //     7     
	UINT32 cs_pal_detected_ris                : 1 ;  //     8     
	UINT32 cs_secam_detected_fal              : 1 ;  //     9     
	UINT32 cs_secam_detected_ris              : 1 ;  //    10     
	UINT32 cs1_chromalock_fal                 : 1 ;  //    11     
	UINT32 cs1_chromalock_ris                 : 1 ;  //    12     
	UINT32 cs1_pal_detected_fal               : 1 ;  //    13     
	UINT32 cs1_pal_detected_ris               : 1 ;  //    14     
	UINT32 cs1_secam_detected_fal             : 1 ;  //    15     
	UINT32 cs1_secam_detected_ris             : 1 ;  //    16     
	UINT32 estfrdp_err_flag_fal               : 1 ;  //    17     
	UINT32 estfrdp_err_flag_ris               : 1 ;  //    18     
	UINT32 vdetect_vcount_fal                 : 1 ;  //    19     
	UINT32 vdetect_vcount_ris                 : 1 ;  //    20     
	UINT32 cvd_mif_err_md                     : 1 ;  //    21     
	UINT32 ro_wbuf_read_req_cnt_mx_lvl_md     : 1 ;  //    22     
	UINT32 ro_read0_svid_cnt_mx_lvl_md        : 1 ;  //    23     
	UINT32 ro_wbuf_full_md                    : 1 ;  //    24     
	UINT32 ro_rbuf_empty_md                   : 1 ;  //    25     
	UINT32 ro_wbuf_read_req_cnt_mx_lvl        : 1 ;  //    26     
	UINT32 ro_read0_svid_cnt_mx_lvl           : 1 ;  //    27     
	UINT32 ro_wbuf_full                       : 1 ;  //    28     
	UINT32 ro_rbuf_empty                      : 1 ;  //    29     
	UINT32 status_comb3d_off                  : 1 ;  //    30     
	UINT32 cvd_fine_hlock_ris                 : 1 ;  //    31     
} O18A0_CVD_INTR2_INTR1_T;

/*-----------------------------------------------------------------------------
		0xc800062cL cvd_intr2_clear1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cvd_intr2_clear1                   : 32;  // 31: 0     
} O18A0_CVD_INTR2_CLEAR1_T;

/*-----------------------------------------------------------------------------
		0xc8000630L top_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 iris_ver                           : 32;  // 31: 0     
} O18A0_TOP_001_T;

/*-----------------------------------------------------------------------------
		0xc8000640L iris_mif_gmau_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_comb3_buffer_size              : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_001_T;

/*-----------------------------------------------------------------------------
		0xc8000644L iris_mif_gmau_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld1_init_rd_pel               : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_002_T;

/*-----------------------------------------------------------------------------
		0xc8000648L iris_mif_gmau_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld2_init_rd_pel               : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_003_T;

/*-----------------------------------------------------------------------------
		0xc800064cL iris_mif_gmau_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld3_init_rd_pel               : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_004_T;

/*-----------------------------------------------------------------------------
		0xc8000650L iris_mif_gmau_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld4_init_rd_pel               : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_005_T;

/*-----------------------------------------------------------------------------
		0xc8000654L iris_mif_gmau_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_to_cnt                    : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_gmau_cmd_dly_cnt               : 4 ;  // 15:12     
} O18A0_IRIS_MIF_GMAU_006_T;

/*-----------------------------------------------------------------------------
		0xc8000658L iris_mif_gmau_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_cmd_base                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_007_T;

/*-----------------------------------------------------------------------------
		0xc800065cL iris_mif_gmau_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mif_ctrl                       : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_008_T;

/*-----------------------------------------------------------------------------
		0xc8000660L iris_mif_gmau_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_endian_sw                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_gmau_cmd_pri2                  : 4 ;  //  7: 4     
	UINT32 reg_gmau_cmd_pri1                  : 4 ;  // 11: 8     
} O18A0_IRIS_MIF_GMAU_009_T;

/*-----------------------------------------------------------------------------
		0xc8000664L iris_mif_gmau_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_stride_size               : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_010_T;

/*-----------------------------------------------------------------------------
		0xc8000668L fastblank_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_latency                     : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_fb_blend_ratio                 : 5 ;  // 12: 8     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_fb_lmflag_off                  : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_fb_en                          : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_fb_pin                         : 1 ;  //    24     
} O18A0_FASTBLANK_001_T;

/*-----------------------------------------------------------------------------
		0xc800066cL fastblank_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_coef1                   : 15;  // 14: 0     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_fb_csc_coef0                   : 15;  // 30:16     
} O18A0_FASTBLANK_002_T;

/*-----------------------------------------------------------------------------
		0xc8000670L fastblank_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_coef3                   : 15;  // 14: 0     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_fb_csc_coef2                   : 15;  // 30:16     
} O18A0_FASTBLANK_003_T;

/*-----------------------------------------------------------------------------
		0xc8000674L fastblank_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_coef5                   : 15;  // 14: 0     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_fb_csc_coef4                   : 15;  // 30:16     
} O18A0_FASTBLANK_004_T;

/*-----------------------------------------------------------------------------
		0xc8000678L fastblank_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_coef7                   : 15;  // 14: 0     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_fb_csc_coef6                   : 15;  // 30:16     
} O18A0_FASTBLANK_005_T;

/*-----------------------------------------------------------------------------
		0xc800067cL fastblank_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_coef8                   : 15;  // 14: 0     
} O18A0_FASTBLANK_006_T;

/*-----------------------------------------------------------------------------
		0xc8000680L fastblank_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_ofst1                   : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_fb_csc_ofst0                   : 11;  // 22:12     
} O18A0_FASTBLANK_007_T;

/*-----------------------------------------------------------------------------
		0xc8000684L fastblank_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_csc_ofst3                   : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_fb_csc_ofst2                   : 11;  // 22:12     
} O18A0_FASTBLANK_008_T;

/*-----------------------------------------------------------------------------
		0xc8000688L fastblank_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_vstart_odd                  : 5 ;  //  4: 0     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_fb_csc_ofst5                   : 11;  // 18: 8     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_fb_csc_ofst4                   : 11;  // 30:20     
} O18A0_FASTBLANK_009_T;

/*-----------------------------------------------------------------------------
		0xc800068cL fastblank_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_hstart                      : 8 ;  //  7: 0     
	UINT32 reg_fb_height_half                 : 8 ;  // 15: 8     
	UINT32 reg_fb_vstart_even                 : 5 ;  // 20:16     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_fb_ch3_br_0th                  : 2 ;  // 25:24     
} O18A0_FASTBLANK_010_T;

/*-----------------------------------------------------------------------------
		0xc8000690L iris_de_ctrl_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_iris_hsout_width               : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_iris_static_de_start           : 12;  // 23:12     
	UINT32 reg_iris_static_de                 : 1 ;  //    24     
} O18A0_IRIS_DE_CTRL_001_T;

/*-----------------------------------------------------------------------------
		0xc8000694L vbi_ctrl_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_little_endian              : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vbi_bits_swap                  : 1 ;  //     4     
} O18A0_VBI_CTRL_001_T;

/*-----------------------------------------------------------------------------
		0xc8000698L vbi_ctrl_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi0_start_addr                : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_vbi0_data_cnt                  : 12;  // 23:12     
	UINT32 reg_vbi_buffer_number              : 2 ;  // 25:24     
} O18A0_VBI_CTRL_002_T;

/*-----------------------------------------------------------------------------
		0xc800069cL vbi_ctrl_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi0_end_addr                  : 10;  //  9: 0     
} O18A0_VBI_CTRL_003_T;

/*-----------------------------------------------------------------------------
		0xc80006a0L vbi_ctrl_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi1_start_addr                : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_vbi1_data_cnt                  : 12;  // 23:12     
} O18A0_VBI_CTRL_004_T;

/*-----------------------------------------------------------------------------
		0xc80006a4L vbi_ctrl_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi1_end_addr                  : 10;  //  9: 0     
} O18A0_VBI_CTRL_005_T;

/*-----------------------------------------------------------------------------
		0xc80006a8L vbi_ctrl_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi2_start_addr                : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_vbi2_data_cnt                  : 12;  // 23:12     
} O18A0_VBI_CTRL_006_T;

/*-----------------------------------------------------------------------------
		0xc80006acL vbi_ctrl_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi2_end_addr                  : 10;  //  9: 0     
} O18A0_VBI_CTRL_007_T;

/*-----------------------------------------------------------------------------
		0xc80006b0L vbi_ctrl_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi3_start_addr                : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_vbi3_data_cnt                  : 12;  // 23:12     
} O18A0_VBI_CTRL_008_T;

/*-----------------------------------------------------------------------------
		0xc80006b4L vbi_ctrl_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi3_end_addr                  : 10;  //  9: 0     
} O18A0_VBI_CTRL_009_T;

/*-----------------------------------------------------------------------------
		0xc80006b8L vbi_ctrl_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_intr_sel                   : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_vbi_even_vcount                : 10;  // 13: 4     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_vbi_odd_vcount                 : 10;  // 25:16     
} O18A0_VBI_CTRL_010_T;

/*-----------------------------------------------------------------------------
		0xc80006c0L fast_blank_status_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_state                       : 1 ;  //     0     
} O18A0_FAST_BLANK_STATUS_001_T;

/*-----------------------------------------------------------------------------
		0xc80006c4L cvbsafe_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cvbs2_gc_int                   : 4 ;  //  3: 0     
	UINT32 reg_cvbs1_gc_int                   : 4 ;  //  7: 4     
	UINT32 reg_iris_fix_gain                  : 1 ;  //     8     
} O18A0_CVBSAFE_001_T;

/*-----------------------------------------------------------------------------
		0xc80006c8L iris_mif_gmau_md_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_comb3_buffer_size_md           : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_MD_001_T;

/*-----------------------------------------------------------------------------
		0xc80006ccL iris_mif_gmau_md_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld1_init_rd_pel_md            : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_MD_002_T;

/*-----------------------------------------------------------------------------
		0xc80006d0L iris_mif_gmau_md_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld2_init_rd_pel_md            : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_MD_003_T;

/*-----------------------------------------------------------------------------
		0xc80006d4L iris_mif_gmau_md_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld3_init_rd_pel_md            : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_MD_004_T;

/*-----------------------------------------------------------------------------
		0xc80006d8L iris_mif_gmau_md_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fld4_init_rd_pel_md            : 23;  // 22: 0     
} O18A0_IRIS_MIF_GMAU_MD_005_T;

/*-----------------------------------------------------------------------------
		0xc80006dcL iris_mif_gmau_md_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_to_cnt_md                 : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_gmau_cmd_dly_cnt_md            : 4 ;  // 15:12     
} O18A0_IRIS_MIF_GMAU_MD_006_T;

/*-----------------------------------------------------------------------------
		0xc80006e0L iris_mif_gmau_md_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_cmd_base_md               : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_007_T;

/*-----------------------------------------------------------------------------
		0xc80006e4L iris_mif_gmau_md_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_endian_sw_md              : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_gmau_cmd_pri2_md               : 4 ;  //  7: 4     
	UINT32 reg_gmau_cmd_pri1_md               : 4 ;  // 11: 8     
} O18A0_IRIS_MIF_GMAU_MD_008_T;

/*-----------------------------------------------------------------------------
		0xc80006e8L iris_mif_gmau_md_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_stride_size_md            : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_009_T;

/*-----------------------------------------------------------------------------
		0xc80006ecL iris_mif_gmau_md_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mif_ctrl_md                    : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_010_T;

/*-----------------------------------------------------------------------------
		0xc80006f0L iris_mif_gmau_md_011 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lbadrgen_ctrl_md               : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_011_T;

/*-----------------------------------------------------------------------------
		0xc80006f4L iris_mif_gmau_md_012 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mif_ctrl1                      : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_012_T;

/*-----------------------------------------------------------------------------
		0xc80006f8L iris_mif_gmau_md_013 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mif_ctrl1_md                   : 32;  // 31: 0     
} O18A0_IRIS_MIF_GMAU_MD_013_T;

/*-----------------------------------------------------------------------------
		0xc8000700L iris_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_proscan_detected               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_mv_colourstripes               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_mv_vbi_detected                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_chromalock                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vlock                          : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_hlock                          : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_no_signal                      : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_status_vdetect_vcount_chg      : 1 ;  //    28     
} O18A0_IRIS_001_T;

/*-----------------------------------------------------------------------------
		0xc8000704L iris_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_noisy                          : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vline_625_detected             : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_secam_detected                 : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_pal_detected                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_status_comb3d_off              : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_noburst_detected               : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_vnon_standard                  : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_hnon_standard                  : 1 ;  //    28     
} O18A0_IRIS_002_T;

/*-----------------------------------------------------------------------------
		0xc8000708L iris_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vcr_rew                        : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vcr_ff                         : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vcr_trick                      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_vcr                            : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_fine_hlock                     : 1 ;  //    16     
} O18A0_IRIS_003_T;

/*-----------------------------------------------------------------------------
		0xc800070cL iris_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_burst_mag               : 16;  // 15: 0     
	UINT32 reg_status_hsync_width             : 8 ;  // 23:16     
} O18A0_IRIS_004_T;

/*-----------------------------------------------------------------------------
		0xc8000710L iris_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_hdto_inc                : 30;  // 29: 0     
} O18A0_IRIS_005_T;

/*-----------------------------------------------------------------------------
		0xc8000714L iris_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_cdto_inc                : 30;  // 29: 0     
} O18A0_IRIS_006_T;

/*-----------------------------------------------------------------------------
		0xc8000718L iris_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_cmag                    : 8 ;  //  7: 0     
	UINT32 reg_status_agc_gain                : 16;  // 23: 8     
} O18A0_IRIS_007_T;

/*-----------------------------------------------------------------------------
		0xc800071cL iris_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_sync_height             : 8 ;  //  7: 0     
	UINT32 reg_status_cordic_freq             : 8 ;  // 15: 8     
	UINT32 reg_status_cgain                   : 14;  // 29:16     
} O18A0_IRIS_008_T;

/*-----------------------------------------------------------------------------
		0xc8000720L iris_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_nstd                    : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_status_vbi_slicer_lvl          : 8 ;  // 19:12     
	UINT32 reg_status_noise                   : 10;  // 29:20     
} O18A0_IRIS_009_T;

/*-----------------------------------------------------------------------------
		0xc8000724L iris_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_diff_sync_blank         : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_status_peak_gain               : 13;  // 28:16     
} O18A0_IRIS_010_T;

/*-----------------------------------------------------------------------------
		0xc8000728L iris_011 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_cline_flag               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_status_blank_level_diff        : 12;  // 15: 4     
	UINT32 reg_status_sync_level_diff         : 12;  // 27:16     
} O18A0_IRIS_011_T;

/*-----------------------------------------------------------------------------
		0xc8000730L iris_012 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cvd_soft_reset                 : 1 ;  //     0     
} O18A0_IRIS_012_T;

/*-----------------------------------------------------------------------------
		0xc8000734L iris_013 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hv_delay                       : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_hpixel                         : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vline_625                      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_colour_mode                    : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_hs_delay                       : 1 ;  //    16     
} O18A0_IRIS_013_T;

/*-----------------------------------------------------------------------------
		0xc8000738L iris_014 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_014_0                      : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_rsv_014_4                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_luma_notch_bw                  : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_chroma_bw_lo                   : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_chroma_burst5or10              : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_ped                            : 1 ;  //    20     
} O18A0_IRIS_014_T;

/*-----------------------------------------------------------------------------
		0xc800073cL iris_015 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hagc_field_mode                : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_mv_hagc_mode                   : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_dc_clamp_mode                  : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_dagc_en                        : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_agc_half_en                    : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_cagc_en                        : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_hagc_en                        : 1 ;  //    24     
} O18A0_IRIS_015_T;

/*-----------------------------------------------------------------------------
		0xc8000740L iris_016 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_pal60_mode                     : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_ntsc443_mode                   : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_adaptive_3dcomb_mode           : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_rsv_016_12                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_adaptive_mode                  : 3 ;  // 18:16     
} O18A0_IRIS_016_T;

/*-----------------------------------------------------------------------------
		0xc8000744L iris_017 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_noise_thresh                   : 8 ;  //  7: 0     
	UINT32 reg_hagc                           : 8 ;  // 15: 8     
	UINT32 reg_agc_gain_update                : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_agc_lpfin_iir_gain             : 4 ;  // 23:20     
	UINT32 reg_agc_lpfin_div                  : 4 ;  // 27:24     
	UINT32 reg_agc_lpfin_sm_ctrl              : 4 ;  // 31:28     
} O18A0_IRIS_017_T;

/*-----------------------------------------------------------------------------
		0xc8000748L iris_018 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_force_vcr_en                   : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_force_vcr_rew                  : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_force_vcr_ff                   : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_force_vcr_trick                : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_force_vcr                      : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_agc_lpfout_div                 : 4 ;  // 23:20     
	UINT32 reg_agc_lpfin_noise_ctrl           : 2 ;  // 25:24     
} O18A0_IRIS_018_T;

/*-----------------------------------------------------------------------------
		0xc800074cL iris_019 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_adc_updn_swap                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_adc_input_swap                 : 1 ;  //     4     
} O18A0_IRIS_019_T;

/*-----------------------------------------------------------------------------
		0xc8000750L iris_020 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ccir656_en                     : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cbcr_swap                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_blue_mode                      : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_yc_delay                       : 4 ;  // 15:12     
} O18A0_IRIS_020_T;

/*-----------------------------------------------------------------------------
		0xc8000754L iris_021 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hue                            : 8 ;  //  7: 0     
	UINT32 reg_saturation                     : 8 ;  // 15: 8     
	UINT32 reg_brightness                     : 8 ;  // 23:16     
	UINT32 reg_contrast                       : 8 ;  // 31:24     
} O18A0_IRIS_021_T;

/*-----------------------------------------------------------------------------
		0xc8000758L iris_022 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cagc                           : 8 ;  //  7: 0     
} O18A0_IRIS_022_T;

/*-----------------------------------------------------------------------------
		0xc800075cL iris_023 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_user_ckill_mode                : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_vbi_ckill                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_hlock_ckill                    : 1 ;  //     8     
} O18A0_IRIS_023_T;

/*-----------------------------------------------------------------------------
		0xc8000760L iris_024 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_nstd_hysis                     : 4 ;  //  3: 0     
	UINT32 reg_disable_clamp_on_vsync         : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_bypass                         : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_noburst_ckill                  : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vnon_std_threshold             : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_hnon_std_threshold             : 6 ;  // 25:20     
} O18A0_IRIS_024_T;

/*-----------------------------------------------------------------------------
		0xc8000764L iris_025 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_agc_peak_en                    : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_agc_peak_cntl                  : 4 ;  //  7: 4     
	UINT32 reg_agc_peak_nominal               : 7 ;  // 14: 8     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_agc_peak_only                  : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_agc_peak_noise_ctrl            : 4 ;  // 23:20     
	UINT32 reg_blank_level_diff_div           : 1 ;  //    24     
} O18A0_IRIS_025_T;

/*-----------------------------------------------------------------------------
		0xc8000768L iris_026 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_blue_cr                        : 8 ;  //  7: 0     
	UINT32 reg_blue_cb                        : 8 ;  // 15: 8     
	UINT32 reg_blue_y                         : 8 ;  // 23:16     
} O18A0_IRIS_026_T;

/*-----------------------------------------------------------------------------
		0xc800076cL iris_027 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hstate_fixed                   : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_disable_hfine                  : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_hstate_unlocked                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_hstate_max                     : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_locked_count_noisy_max         : 4 ;  // 19:16     
	UINT32 reg_locked_count_clean_max         : 4 ;  // 23:20     
	UINT32 reg_hdetect_clamp_level            : 8 ;  // 31:24     
} O18A0_IRIS_027_T;

/*-----------------------------------------------------------------------------
		0xc8000770L iris_028 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hlock_vsync_mode               : 2 ;  //  1: 0     
} O18A0_IRIS_028_T;

/*-----------------------------------------------------------------------------
		0xc8000774L iris_029 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdto_inc                       : 32;  // 31: 0     
} O18A0_IRIS_029_T;

/*-----------------------------------------------------------------------------
		0xc8000778L iris_030 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdto_inc                       : 32;  // 31: 0     
} O18A0_IRIS_030_T;

/*-----------------------------------------------------------------------------
		0xc800077cL iris_031 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hsync_gate_end                 : 8 ;  //  7: 0     
	UINT32 reg_hsync_gate_start               : 8 ;  // 15: 8     
	UINT32 reg_hsync_phase_offset             : 8 ;  // 23:16     
	UINT32 reg_hsync_rising                   : 8 ;  // 31:24     
} O18A0_IRIS_031_T;

/*-----------------------------------------------------------------------------
		0xc8000780L iris_032 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hsync_similar                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_hsync_low                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_hdetect_noise_en               : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_hfine_lt_hcoarse               : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_hlpf_clamp_sel                 : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_hlpf_clamp_noisy_en            : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_hlpf_clamp_vbi_en              : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_hlpf_clamp_en                  : 1 ;  //    28     
} O18A0_IRIS_032_T;

/*-----------------------------------------------------------------------------
		0xc8000784L iris_033 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hsync_rising_end               : 8 ;  //  7: 0     
	UINT32 reg_hsync_rising_auto              : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_hsync_rising_start             : 6 ;  // 17:12     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_phase_diff_noise_ctrl          : 4 ;  // 23:20     
	UINT32 reg_hlpf_noise_ctrl                : 4 ;  // 27:24     
} O18A0_IRIS_033_T;

/*-----------------------------------------------------------------------------
		0xc8000788L iris_034 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hblank_end                     : 8 ;  //  7: 0     
	UINT32 reg_hblank_start                   : 8 ;  // 15: 8     
	UINT32 reg_hsync_rising_msk               : 4 ;  // 19:16     
	UINT32 reg_status_hslock                  : 5 ;  // 24:20     
} O18A0_IRIS_034_T;

/*-----------------------------------------------------------------------------
		0xc800078cL iris_035 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burst_gate_end                 : 8 ;  //  7: 0     
	UINT32 reg_burst_gate_start               : 8 ;  // 15: 8     
	UINT32 reg_vlock_debug                    : 4 ;  // 19:16     
	UINT32 reg_hlock_debug_pt                 : 4 ;  // 23:20     
	UINT32 reg_hlock_debug_en                 : 2 ;  // 25:24     
} O18A0_IRIS_035_T;

/*-----------------------------------------------------------------------------
		0xc8000790L iris_036 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hactive_width                  : 8 ;  //  7: 0     
	UINT32 reg_hactive_start                  : 8 ;  // 15: 8     
	UINT32 reg_hslock_debug_pt                : 4 ;  // 19:16     
	UINT32 reg_hslock_debug_en                : 5 ;  // 24:20     
} O18A0_IRIS_036_T;

/*-----------------------------------------------------------------------------
		0xc8000794L iris_037 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vactive_height                 : 8 ;  //  7: 0     
	UINT32 reg_vactive_start                  : 8 ;  // 15: 8     
	UINT32 reg_vslock_debug                   : 4 ;  // 19:16     
	UINT32 reg_status_vslock                  : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_vslock_hscnt_th                : 8 ;  // 31:24     
} O18A0_IRIS_037_T;

/*-----------------------------------------------------------------------------
		0xc8000798L iris_038 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vsync_h_max                    : 7 ;  //  6: 0     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_vsync_h_min                    : 7 ;  // 14: 8     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_vslock_hscnt                   : 8 ;  // 23:16     
	UINT32 reg_vslock_ctrl                    : 8 ;  // 31:24     
} O18A0_IRIS_038_T;

/*-----------------------------------------------------------------------------
		0xc800079cL iris_039 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vsync_agc_max                  : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vsync_agc_min                  : 7 ;  // 14: 8     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_vslock_offth                   : 8 ;  // 23:16     
	UINT32 reg_vslock_onth                    : 8 ;  // 31:24     
} O18A0_IRIS_039_T;

/*-----------------------------------------------------------------------------
		0xc80007a0L iris_040 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vsync_vbi_max                  : 7 ;  //  6: 0     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_vsync_vbi_min                  : 7 ;  // 14: 8     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_vslock_hscnt_margin            : 8 ;  // 23:16     
	UINT32 reg_vslock_vscnt_max               : 8 ;  // 31:24     
} O18A0_IRIS_040_T;

/*-----------------------------------------------------------------------------
		0xc80007a4L iris_041 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vlock_wide_range               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vsync_l_cnt                    : 4 ;  //  7: 4     
	UINT32 reg_vsync_threshold_cnt512         : 11;  // 18: 8     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_vsync_threshold_cnt304         : 11;  // 30:20     
} O18A0_IRIS_041_T;

/*-----------------------------------------------------------------------------
		0xc80007a8L iris_042 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_proscan_1field_mode            : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_vsync_cntl_noisy               : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vsync_cntl_ff_rew              : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_vsync_cntl_trick               : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vsync_cntl_vcr                 : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_vsync_cntl                     : 4 ;  // 23:20     
	UINT32 reg_vsync_lockout_cnt              : 7 ;  // 30:24     
} O18A0_IRIS_042_T;

/*-----------------------------------------------------------------------------
		0xc80007acL iris_043 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_field_polarity                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_flip_field                     : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_veven_delayed                  : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_vodd_delayed                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_field_detect_mode              : 4 ;  // 19:16     
	UINT32 reg_vloop_tc                       : 2 ;  // 21:20     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 reg_debug_digital                  : 8 ;  // 31:24     
} O18A0_IRIS_043_T;

/*-----------------------------------------------------------------------------
		0xc80007b0L iris_044 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_dbg_syncs                      : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_muxdigital                     : 4 ;  //  7: 4     
	UINT32 reg_muxanalogb                     : 4 ;  // 11: 8     
	UINT32 reg_muxanaloga                     : 4 ;  // 15:12     
	UINT32 reg_debug_analogb                  : 8 ;  // 23:16     
	UINT32 reg_debug_analoga                  : 8 ;  // 31:24     
} O18A0_IRIS_044_T;

/*-----------------------------------------------------------------------------
		0xc80007b4L iris_045 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_ybw                      : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_peak_range                     : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_peak_gain                      : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_peak_en                        : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vslock_hscnt_iir_alpha         : 8 ;  // 23:16     
	UINT32 reg_vslock_hscnt_ictrl             : 4 ;  // 27:24     
} O18A0_IRIS_045_T;

/*-----------------------------------------------------------------------------
		0xc80007b8L iris_046 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_auto_secam_level               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_rsv_046_4                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_secam_pll                      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_secam_sw_old                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_palsw_level                    : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_vslock_init_th                 : 4 ;  // 23:20     
} O18A0_IRIS_046_T;

/*-----------------------------------------------------------------------------
		0xc80007bcL iris_047 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lose_chromalock_mode           : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_lose_chromalock_count          : 4 ;  //  7: 4     
	UINT32 reg_lose_chromalock_level          : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_lose_chromalock_ckill          : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vslock_dly_cnt                 : 9 ;  // 24:16     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_vslock_dly_ctrl                : 4 ;  // 31:28     
} O18A0_IRIS_047_T;

/*-----------------------------------------------------------------------------
		0xc80007c0L iris_048 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cstripe_detect_control         : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 reg_cdct_demod_sel                 : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_hlocked_count_threshold        : 4 ;  // 11: 8     
	UINT32 reg_hlocked_max                    : 8 ;  // 19:12     
	UINT32 reg_hlocked_mode                   : 2 ;  // 21:20     
} O18A0_IRIS_048_T;

/*-----------------------------------------------------------------------------
		0xc80007c4L iris_049 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hfine_vcr_trick_en             : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_hfine_vcr_en                   : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_hresampler_2up                 : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cstate                         : 3 ;  // 14:12     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_fixed_cstate                   : 1 ;  //    16     
} O18A0_IRIS_049_T;

/*-----------------------------------------------------------------------------
		0xc80007c8L iris_050 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_pulse_ampl                 : 8 ;  //  7: 0     
} O18A0_IRIS_050_T;

/*-----------------------------------------------------------------------------
		0xc80007ccL iris_051 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_delay                    : 8 ;  //  7: 0     
	UINT32 reg_cpump_adjust                   : 8 ;  // 15: 8     
	UINT32 reg_cpump_adjust_polarity          : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_cpump_adjust_delay             : 6 ;  // 25:20     
} O18A0_IRIS_051_T;

/*-----------------------------------------------------------------------------
		0xc80007d0L iris_052 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mv_colourstripes_sel           : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_mv_vbi_sel                     : 1 ;  //     4     
} O18A0_IRIS_052_T;

/*-----------------------------------------------------------------------------
		0xc80007d4L iris_053 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_kill_cr                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cpump_kill_cb                  : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cpump_kill_y                   : 1 ;  //     8     
} O18A0_IRIS_053_T;

/*-----------------------------------------------------------------------------
		0xc80007d8L iris_054 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_auto_stip_nobp           : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cpump_auto_stip_unlocked       : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cpump_auto_stip_no_signal      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cpump_auto_stip_noisy          : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cpump_auto_stip_vactive        : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_cpump_auto_stip_mode           : 2 ;  // 21:20     
} O18A0_IRIS_054_T;

/*-----------------------------------------------------------------------------
		0xc80007dcL iris_055 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_accum_mode               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cpump_fixed_syncmid            : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cpump_level_filter_gain        : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cpump_noisy_filter_en          : 1 ;  //    12     
} O18A0_IRIS_055_T;

/*-----------------------------------------------------------------------------
		0xc80007e0L iris_056 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_dn_max                   : 7 ;  //  6: 0     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cpump_up_max                   : 7 ;  // 14: 8     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_cpump_vsync_blank_filter       : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_cpump_vsync_syncmid_filter     : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_cpump_vsync_mode               : 2 ;  // 25:24     
} O18A0_IRIS_056_T;

/*-----------------------------------------------------------------------------
		0xc80007e4L iris_057 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_diff_noisy_only          : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cpump_dn_diff_max              : 7 ;  // 10: 4     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cpump_diff_signal_only         : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cpump_up_diff_max              : 7 ;  // 22:16     
} O18A0_IRIS_057_T;

/*-----------------------------------------------------------------------------
		0xc80007e8L iris_058 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cpump_pr_override              : 8 ;  //  7: 0     
	UINT32 reg_cpump_pb_override              : 8 ;  // 15: 8     
	UINT32 reg_cpump_y_override               : 8 ;  // 23:16     
} O18A0_IRIS_058_T;

/*-----------------------------------------------------------------------------
		0xc80007ecL iris_059 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_db_freq                        : 12;  // 11: 0     
	UINT32 reg_dr_freq                        : 12;  // 23:12     
	UINT32 reg_cvbs_y_delay                   : 5 ;  // 28:24     
} O18A0_IRIS_059_T;

/*-----------------------------------------------------------------------------
		0xc80007f0L iris_060 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_060_0                      : 1 ;  //     0     
} O18A0_IRIS_060_T;

/*-----------------------------------------------------------------------------
		0xc80007f4L iris_061 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_061_0                      : 1 ;  //     0     
} O18A0_IRIS_061_T;

/*-----------------------------------------------------------------------------
		0xc80007f8L iris_062 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_062_0                      : 1 ;  //     0     
} O18A0_IRIS_062_T;

/*-----------------------------------------------------------------------------
		0xc80007fcL iris_063 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_063_0                      : 1 ;  //     0     
} O18A0_IRIS_063_T;

/*-----------------------------------------------------------------------------
		0xc8000800L iris_064 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_pal3dcomb_vactive_offset       : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_fb_sync                        : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_fb_hold                        : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_fb_ctl                         : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_field_latency                  : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_lbadrgen_rst                   : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_comb2d_only                    : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_fb_off                         : 2 ;  // 29:28     
} O18A0_IRIS_064_T;

/*-----------------------------------------------------------------------------
		0xc8000804L iris_065 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_065_0                      : 1 ;  //     0     
} O18A0_IRIS_065_T;

/*-----------------------------------------------------------------------------
		0xc8000808L iris_066 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_pal3dcomb_vactive_offset_md    : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_fb_sync_md                     : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_fb_hold_md                     : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_fb_ctl_md                      : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_field_latency_md               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_lbadrgen_rst_md                : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_comb2d_only_md                 : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_fb_off_md                      : 2 ;  // 29:28     
} O18A0_IRIS_066_T;

/*-----------------------------------------------------------------------------
		0xc800080cL iris_067 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ldpause_threshold              : 4 ;  //  3: 0     
	UINT32 reg_vf_nstd_en                     : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vcr_auto_switch_en             : 1 ;  //     8     
} O18A0_IRIS_067_T;

/*-----------------------------------------------------------------------------
		0xc8000810L iris_068 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_068_0                      : 1 ;  //     0     
} O18A0_IRIS_068_T;

/*-----------------------------------------------------------------------------
		0xc8000814L iris_069 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vactive_md_height              : 8 ;  //  7: 0     
	UINT32 reg_vactive_md_start               : 8 ;  // 15: 8     
} O18A0_IRIS_069_T;

/*-----------------------------------------------------------------------------
		0xc8000818L iris_070 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hsync_pulse_width              : 4 ;  //  3: 0     
} O18A0_IRIS_070_T;

/*-----------------------------------------------------------------------------
		0xc800081cL iris_071 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cagc_tc_ismall                 : 3 ;  //  2: 0     
} O18A0_IRIS_071_T;

/*-----------------------------------------------------------------------------
		0xc8000820L iris_072 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cagc_coring_threshold          : 4 ;  //  3: 0     
	UINT32 reg_cagc_unity_gain                : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cagc_coring                    : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cagc_tc_p                      : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_cagc_tc_ibig                   : 3 ;  // 18:16     
} O18A0_IRIS_072_T;

/*-----------------------------------------------------------------------------
		0xc8000824L iris_073 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_aaf_on                         : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_syncmidpt_lowblank_sel         : 4 ;  //  7: 4     
	UINT32 reg_syncmidpt_lowblank_ratio       : 6 ;  // 13: 8     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_syncmidpt_syncheight_sel       : 4 ;  // 19:16     
	UINT32 reg_syncmidpt_syncheight_ratio     : 1 ;  //    20     
} O18A0_IRIS_073_T;

/*-----------------------------------------------------------------------------
		0xc8000828L iris_074 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_dcrestore_accum_width          : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_dcrestore_no_bad_bp            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_dcrestore_kill_enable          : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_dcrestore_bp_delay             : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_syncmid_nobp_en                : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_syncmid_filter_en              : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_dcrestore_gain                 : 2 ;  // 29:28     
} O18A0_IRIS_074_T;

/*-----------------------------------------------------------------------------
		0xc800082cL iris_075 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_dcrestore_kill_enable_noisy    : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_sync_height_unclp              : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_sync_height_sel                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_sync_height_update             : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_syncmidpt_lowsync_sel          : 4 ;  // 19:16     
	UINT32 reg_syncmidpt_lowsync_ratio        : 6 ;  // 25:20     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 reg_syncmidpt_syncheight_iir_sel   : 4 ;  // 31:28     
} O18A0_IRIS_075_T;

/*-----------------------------------------------------------------------------
		0xc8000830L iris_076 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_dcrestore_hsync_mid            : 8 ;  //  7: 0     
	UINT32 reg_bp_kill_thresh                 : 8 ;  // 15: 8     
	UINT32 reg_hmgc                           : 8 ;  // 23:16     
	UINT32 reg_dcrestore_lpf_en               : 2 ;  // 25:24     
} O18A0_IRIS_076_T;

/*-----------------------------------------------------------------------------
		0xc8000834L iris_077 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_auto_min_sync_height           : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_min_sync_height                : 7 ;  // 10: 4     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_syncmidpt_offset               : 8 ;  // 19:12     
	UINT32 reg_syncmidpt_offset_sel           : 4 ;  // 23:20     
	UINT32 reg_clampagc_syncs_ctrl            : 8 ;  // 31:24     
} O18A0_IRIS_077_T;

/*-----------------------------------------------------------------------------
		0xc8000838L iris_078 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vcrtrick_proscan               : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_veven_early_delayed            : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vodd_early_delayed             : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_vfield_hoffset_fixed           : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vsync_no_signal_thresh         : 8 ;  // 23:16     
	UINT32 reg_vsync_signal_thresh            : 8 ;  // 31:24     
} O18A0_IRIS_078_T;

/*-----------------------------------------------------------------------------
		0xc800083cL iris_079 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vfield_hoffset                 : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_vactive_half_lines             : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vdetect_noise_en               : 1 ;  //    16     
} O18A0_IRIS_079_T;

/*-----------------------------------------------------------------------------
		0xc8000840L iris_080 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_dual_hedge_dis                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_dual_hedge_auto_width          : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_dual_fine_hedge_vbi            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_dual_coarse_hedge_vbi          : 2 ;  // 13:12     
} O18A0_IRIS_080_T;

/*-----------------------------------------------------------------------------
		0xc8000844L iris_081 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_mv_hsync_rising_end            : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vcr_state2_long                : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_slow_hdsw                      : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_mv_hsync_rising_start          : 6 ;  // 21:16     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 reg_no_hsyncs_mode                 : 2 ;  // 25:24     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 reg_many_hsyncs_mode               : 1 ;  //    28     
} O18A0_IRIS_081_T;

/*-----------------------------------------------------------------------------
		0xc8000848L iris_082 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_no_hsyncs_weak                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_disable_hdsw_weak              : 1 ;  //     4     
} O18A0_IRIS_082_T;

/*-----------------------------------------------------------------------------
		0xc800084cL iris_083 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vactive_hdsw_mode              : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_disable_hdsw_mode              : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_hsync_falling_filter           : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_no_hsyncs_noisy                : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_hloop_range                    : 2 ;  // 17:16     
} O18A0_IRIS_083_T;

/*-----------------------------------------------------------------------------
		0xc8000850L iris_084 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_084_0                      : 1 ;  //     0     
} O18A0_IRIS_084_T;

/*-----------------------------------------------------------------------------
		0xc8000854L iris_085 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_085_0                      : 1 ;  //     0     
} O18A0_IRIS_085_T;

/*-----------------------------------------------------------------------------
		0xc8000858L iris_086 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_086_0                      : 1 ;  //     0     
} O18A0_IRIS_086_T;

/*-----------------------------------------------------------------------------
		0xc800085cL iris_087 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_087_0                      : 1 ;  //     0     
} O18A0_IRIS_087_T;

/*-----------------------------------------------------------------------------
		0xc8000860L iris_088 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_088_0                      : 1 ;  //     0     
} O18A0_IRIS_088_T;

/*-----------------------------------------------------------------------------
		0xc8000864L iris_089 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_avg_freq_range                 : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_issecam_th                     : 6 ;  //  9: 4     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_freq_offset_range              : 8 ;  // 19:12     
} O18A0_IRIS_089_T;

/*-----------------------------------------------------------------------------
		0xc8000868L iris_090 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_090_0                      : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_rsv_090_4                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_rsv_090_8                      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_rsv_090_12                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_hactive_md_width               : 8 ;  // 23:16     
	UINT32 reg_hactive_md_start               : 8 ;  // 31:24     
} O18A0_IRIS_090_T;

/*-----------------------------------------------------------------------------
		0xc800086cL iris_091 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_091_0                      : 1 ;  //     0     
} O18A0_IRIS_091_T;

/*-----------------------------------------------------------------------------
		0xc8000870L iris_092 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_092_0                      : 1 ;  //     0     
} O18A0_IRIS_092_T;

/*-----------------------------------------------------------------------------
		0xc8000874L iris_093 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_093_0                      : 1 ;  //     0     
} O18A0_IRIS_093_T;

/*-----------------------------------------------------------------------------
		0xc8000878L iris_094 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cordic_gate_end                : 8 ;  //  7: 0     
	UINT32 reg_cordic_gate_start              : 8 ;  // 15: 8     
	UINT32 reg_ispal_th                       : 8 ;  // 23:16     
	UINT32 reg_phase_offset_range             : 8 ;  // 31:24     
} O18A0_IRIS_094_T;

/*-----------------------------------------------------------------------------
		0xc800087cL iris_095 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_095_0                      : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_rsv_095_4                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_adc_cpump_swap                 : 6 ;  // 13: 8     
} O18A0_IRIS_095_T;

/*-----------------------------------------------------------------------------
		0xc8000880L iris_096 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ckill                          : 16;  // 15: 0     
	UINT32 reg_cagc_gate_end                  : 8 ;  // 23:16     
	UINT32 reg_cagc_gate_start                : 8 ;  // 31:24     
} O18A0_IRIS_096_T;

/*-----------------------------------------------------------------------------
		0xc8000884L iris_097 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_icburst_half_ampl              : 10;  //  9: 0     
} O18A0_IRIS_097_T;

/*-----------------------------------------------------------------------------
		0xc8000888L iris_098 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_agc_bypass                     : 1 ;  //     0     
} O18A0_IRIS_098_T;

/*-----------------------------------------------------------------------------
		0xc800088cL iris_099 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_clampagc_inv                   : 4 ;  //  3: 0     
} O18A0_IRIS_099_T;

/*-----------------------------------------------------------------------------
		0xc8000890L iris_100 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vps_slicer_mode                : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_wss_slicer_mode                : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_tt_slicer_mode                 : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cc_slicer_mode                 : 2 ;  // 13:12     
} O18A0_IRIS_100_T;

/*-----------------------------------------------------------------------------
		0xc8000894L iris_101 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_perr_on                        : 1 ;  //     0     
} O18A0_IRIS_101_T;

/*-----------------------------------------------------------------------------
		0xc8000898L iris_102 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_perr_dnref                     : 32;  // 31: 0     
} O18A0_IRIS_102_T;

/*-----------------------------------------------------------------------------
		0xc800089cL iris_103 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfa_coeff0               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfa_on                   : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_iris_cresampler_on             : 1 ;  //    20     
} O18A0_IRIS_103_T;

/*-----------------------------------------------------------------------------
		0xc80008a0L iris_104 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfa_coeff2               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfa_coeff1               : 13;  // 28:16     
} O18A0_IRIS_104_T;

/*-----------------------------------------------------------------------------
		0xc80008a4L iris_105 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfa_coeff4               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfa_coeff3               : 13;  // 28:16     
} O18A0_IRIS_105_T;

/*-----------------------------------------------------------------------------
		0xc80008a8L iris_106 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfa_coeff5               : 13;  // 12: 0     
} O18A0_IRIS_106_T;

/*-----------------------------------------------------------------------------
		0xc80008acL iris_107 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfb_coeff0               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfb_on                   : 1 ;  //    16     
} O18A0_IRIS_107_T;

/*-----------------------------------------------------------------------------
		0xc80008b0L iris_108 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfb_coeff2               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfb_coeff1               : 13;  // 28:16     
} O18A0_IRIS_108_T;

/*-----------------------------------------------------------------------------
		0xc80008b4L iris_109 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_lpfb_coeff4               : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_lpfb_coeff3               : 13;  // 28:16     
} O18A0_IRIS_109_T;

/*-----------------------------------------------------------------------------
		0xc80008b8L iris_110 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_sel                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cres_blend_method              : 3 ;  //  6: 4     
} O18A0_IRIS_110_T;

/*-----------------------------------------------------------------------------
		0xc80008bcL iris_111 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_bcdefault           : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cres_0px_sel                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cres_clksel                    : 2 ;  // 17:16     
} O18A0_IRIS_111_T;

/*-----------------------------------------------------------------------------
		0xc80008c0L iris_112 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_bcpara1             : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cres_blend_bcpara0             : 11;  // 22:12     
} O18A0_IRIS_112_T;

/*-----------------------------------------------------------------------------
		0xc80008c4L iris_113 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_bcpara3             : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cres_blend_bcpara2             : 11;  // 22:12     
} O18A0_IRIS_113_T;

/*-----------------------------------------------------------------------------
		0xc80008c8L iris_114 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_bcpara5             : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cres_blend_bcpara4             : 11;  // 22:12     
} O18A0_IRIS_114_T;

/*-----------------------------------------------------------------------------
		0xc80008ccL iris_115 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_bcpara7             : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_cres_blend_bcpara6             : 11;  // 22:12     
} O18A0_IRIS_115_T;

/*-----------------------------------------------------------------------------
		0xc80008d0L iris_116 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_blend_diffth1             : 12;  // 11: 0     
	UINT32 reg_cres_blend_diffth0             : 12;  // 23:12     
} O18A0_IRIS_116_T;

/*-----------------------------------------------------------------------------
		0xc80008d4L iris_117 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cres_alpha_off                 : 8 ;  //  7: 0     
	UINT32 reg_cres_blend_diffth2             : 12;  // 19: 8     
} O18A0_IRIS_117_T;

/*-----------------------------------------------------------------------------
		0xc80008d8L iris_118 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hrscbld_dnoff                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_hrscbld_upoff                  : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_hrsybld_dnoff                  : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_hrsybld_upoff                  : 4 ;  // 15:12     
	UINT32 reg_dtrs_dlysel                    : 4 ;  // 19:16     
	UINT32 reg_dtrs_revalpha_sel              : 2 ;  // 21:20     
} O18A0_IRIS_118_T;

/*-----------------------------------------------------------------------------
		0xc80008dcL iris_119 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_oadj_y_offo                    : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_oadj_y_offi                    : 11;  // 22:12     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_oadj_yc_msk                    : 5 ;  // 28:24     
} O18A0_IRIS_119_T;

/*-----------------------------------------------------------------------------
		0xc80008e0L iris_120 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_oadj_y_coeff                   : 14;  // 13: 0     
} O18A0_IRIS_120_T;

/*-----------------------------------------------------------------------------
		0xc80008e4L iris_121 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_oadj_c_offo                    : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_oadj_c_offi                    : 11;  // 22:12     
} O18A0_IRIS_121_T;

/*-----------------------------------------------------------------------------
		0xc80008e8L iris_122 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_oadj_c_coeff                   : 14;  // 13: 0     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_oadj_cr_coeff                  : 14;  // 29:16     
} O18A0_IRIS_122_T;

/*-----------------------------------------------------------------------------
		0xc80008ecL iris_123 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_adc_unity_gain_value           : 4 ;  //  3: 0     
	UINT32 reg_oadj_cr_offo                   : 11;  // 14: 4     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 reg_oadj_cr_offi                   : 11;  // 26:16     
} O18A0_IRIS_123_T;

/*-----------------------------------------------------------------------------
		0xc80008f0L iris_124 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_124_0                      : 1 ;  //     0     
} O18A0_IRIS_124_T;

/*-----------------------------------------------------------------------------
		0xc80008f4L iris_125 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_iblank_half_lvl0               : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_isynctip_lvl0                  : 10;  // 21:12     
} O18A0_IRIS_125_T;

/*-----------------------------------------------------------------------------
		0xc80008f8L iris_126 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sync_int_blank_lvl0            : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_ipeak_chroma_m768_lvl0         : 10;  // 21:12     
} O18A0_IRIS_126_T;

/*-----------------------------------------------------------------------------
		0xc80008fcL iris_127 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sync_int_blank_vid_lvl0        : 8 ;  //  7: 0     
	UINT32 reg_int_black_ped_vid_lvl0         : 10;  // 17: 8     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_int_blank_vid_lvl0             : 10;  // 29:20     
} O18A0_IRIS_127_T;

/*-----------------------------------------------------------------------------
		0xc8000900L iris_128 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_int_vbi_blank_vid_lvl0         : 8 ;  //  7: 0     
} O18A0_IRIS_128_T;

/*-----------------------------------------------------------------------------
		0xc8000904L iris_129 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_internal_sync_midpt            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_internal_sync_level            : 13;  // 28:16     
} O18A0_IRIS_129_T;

/*-----------------------------------------------------------------------------
		0xc8000908L iris_130 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sync_internal_sync_midpt       : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_internal_blank_level           : 13;  // 24:12     
} O18A0_IRIS_130_T;

/*-----------------------------------------------------------------------------
		0xc800090cL iris_131 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_adc_blank_level                : 10;  //  9: 0     
} O18A0_IRIS_131_T;

/*-----------------------------------------------------------------------------
		0xc8000910L iris_132 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hrs_alpha_croff                : 8 ;  //  7: 0     
	UINT32 reg_hrs_alpha_cboff                : 8 ;  // 15: 8     
	UINT32 reg_hrs_alpha_yoff                 : 8 ;  // 23:16     
} O18A0_IRIS_132_T;

/*-----------------------------------------------------------------------------
		0xc8000914L iris_133 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cphase_adjust                  : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 reg_cphase_adjust_sel              : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cdct_actv_sel                  : 2 ;  //  9: 8     
} O18A0_IRIS_133_T;

/*-----------------------------------------------------------------------------
		0xc8000918L iris_134 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_adap_clf_mode                  : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 reg_cb_delay                       : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_yc444                          : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_ycadj_cr_p                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_ycadj_dly                      : 6 ;  // 21:16     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 reg_oadj_swap                      : 1 ;  //    24     
} O18A0_IRIS_134_T;

/*-----------------------------------------------------------------------------
		0xc800091cL iris_135 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lpf_tap_0_0                    : 16;  // 15: 0     
	UINT32 reg_lpf_0_en                       : 1 ;  //    16     
} O18A0_IRIS_135_T;

/*-----------------------------------------------------------------------------
		0xc8000920L iris_136 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lpf_tap_0_2                    : 16;  // 15: 0     
	UINT32 reg_lpf_tap_0_1                    : 16;  // 31:16     
} O18A0_IRIS_136_T;

/*-----------------------------------------------------------------------------
		0xc8000924L iris_137 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lpf_tap_0_4                    : 16;  // 15: 0     
	UINT32 reg_lpf_tap_0_3                    : 16;  // 31:16     
} O18A0_IRIS_137_T;

/*-----------------------------------------------------------------------------
		0xc8000928L iris_138 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lpf_tap_0_6                    : 16;  // 15: 0     
	UINT32 reg_lpf_tap_0_5                    : 16;  // 31:16     
} O18A0_IRIS_138_T;

/*-----------------------------------------------------------------------------
		0xc800092cL iris_139 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cpu2mcu_pe_param_changed           : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 cpu2mcu_status_rf_av               : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 cpu2mcu_status_color_system_0      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 cpu2mcu_status_color_system_1      : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 cpu2mcu_status_color_system_2      : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 cpu2mcu_signal_lock_flag           : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_status_pseudo_sync             : 4 ;  // 27:24     
} O18A0_IRIS_139_T;

/*-----------------------------------------------------------------------------
		0xc8000930L iris_140 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_140                        : 1 ;  //     0     
} O18A0_IRIS_140_T;

/*-----------------------------------------------------------------------------
		0xc8000934L iris_141 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_141                        : 1 ;  //     0     
} O18A0_IRIS_141_T;

/*-----------------------------------------------------------------------------
		0xc8000938L iris_142 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_142                        : 1 ;  //     0     
} O18A0_IRIS_142_T;

/*-----------------------------------------------------------------------------
		0xc800093cL iris_143 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_143                        : 1 ;  //     0     
} O18A0_IRIS_143_T;

/*-----------------------------------------------------------------------------
		0xc8000940L iris_144 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_144                        : 1 ;  //     0     
} O18A0_IRIS_144_T;

/*-----------------------------------------------------------------------------
		0xc8000944L iris_145 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_145                        : 1 ;  //     0     
} O18A0_IRIS_145_T;

/*-----------------------------------------------------------------------------
		0xc8000948L iris_146 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_146                        : 1 ;  //     0     
} O18A0_IRIS_146_T;

/*-----------------------------------------------------------------------------
		0xc800094cL iris_147 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_cnt_mode                    : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vs_sync_mode                   : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_rsv_147_8                      : 1 ;  //     8     
} O18A0_IRIS_147_T;

/*-----------------------------------------------------------------------------
		0xc8000950L iris_148 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_missing_max                 : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vs_match_max                   : 6 ;  // 13: 8     
} O18A0_IRIS_148_T;

/*-----------------------------------------------------------------------------
		0xc8000954L iris_149 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_prd_0                : 24;  // 23: 0     
} O18A0_IRIS_149_T;

/*-----------------------------------------------------------------------------
		0xc8000958L iris_150 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_prd_th_0             : 24;  // 23: 0     
} O18A0_IRIS_150_T;

/*-----------------------------------------------------------------------------
		0xc800095cL iris_151 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_pos_0                : 24;  // 23: 0     
} O18A0_IRIS_151_T;

/*-----------------------------------------------------------------------------
		0xc8000960L iris_152 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_pos_th_0             : 24;  // 23: 0     
} O18A0_IRIS_152_T;

/*-----------------------------------------------------------------------------
		0xc8000964L iris_153 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_prd_1                : 24;  // 23: 0     
} O18A0_IRIS_153_T;

/*-----------------------------------------------------------------------------
		0xc8000968L iris_154 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_prd_th_1             : 24;  // 23: 0     
} O18A0_IRIS_154_T;

/*-----------------------------------------------------------------------------
		0xc800096cL iris_155 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vs_length_pos_1                : 24;  // 23: 0     
} O18A0_IRIS_155_T;

/*-----------------------------------------------------------------------------
		0xc8000970L iris_156 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_156_0                      : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_rsv_156_4                      : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vs_length_pos_th_1             : 24;  // 31: 8     
} O18A0_IRIS_156_T;

/*-----------------------------------------------------------------------------
		0xc8000974L iris_157 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos0_ctrl0                : 32;  // 31: 0     
} O18A0_IRIS_157_T;

/*-----------------------------------------------------------------------------
		0xc8000978L iris_158 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos0_ctrl1                : 32;  // 31: 0     
} O18A0_IRIS_158_T;

/*-----------------------------------------------------------------------------
		0xc800097cL iris_159 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos1_ctrl0                : 32;  // 31: 0     
} O18A0_IRIS_159_T;

/*-----------------------------------------------------------------------------
		0xc8000980L iris_160 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos1_ctrl1                : 32;  // 31: 0     
} O18A0_IRIS_160_T;

/*-----------------------------------------------------------------------------
		0xc8000984L iris_161 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos2_ctrl0                : 32;  // 31: 0     
} O18A0_IRIS_161_T;

/*-----------------------------------------------------------------------------
		0xc8000988L iris_162 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos2_ctrl1                : 32;  // 31: 0     
} O18A0_IRIS_162_T;

/*-----------------------------------------------------------------------------
		0xc800098cL iris_163 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_burstpos0_togcnt        : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_status_burstpos1_togcnt        : 6 ;  // 13: 8     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_status_burstpos2_togcnt        : 6 ;  // 21:16     
} O18A0_IRIS_163_T;

/*-----------------------------------------------------------------------------
		0xc8000990L iris_164 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burstpos_cgain                 : 8 ;  //  7: 0     
} O18A0_IRIS_164_T;

/*-----------------------------------------------------------------------------
		0xc8000994L iris_165 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_165                        : 1 ;  //     0     
} O18A0_IRIS_165_T;

/*-----------------------------------------------------------------------------
		0xc8000998L iris_166 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_166                        : 1 ;  //     0     
} O18A0_IRIS_166_T;

/*-----------------------------------------------------------------------------
		0xc800099cL iris_167 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_167                        : 1 ;  //     0     
} O18A0_IRIS_167_T;

/*-----------------------------------------------------------------------------
		0xc80009a0L iris_168 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_168                        : 1 ;  //     0     
} O18A0_IRIS_168_T;

/*-----------------------------------------------------------------------------
		0xc80009a4L iris_169 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_169                        : 1 ;  //     0     
} O18A0_IRIS_169_T;

/*-----------------------------------------------------------------------------
		0xc80009a8L iris_170 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_170                        : 1 ;  //     0     
} O18A0_IRIS_170_T;

/*-----------------------------------------------------------------------------
		0xc80009acL iris_171 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_171                        : 1 ;  //     0     
} O18A0_IRIS_171_T;

/*-----------------------------------------------------------------------------
		0xc80009b0L iris_172 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_172                        : 1 ;  //     0     
} O18A0_IRIS_172_T;

/*-----------------------------------------------------------------------------
		0xc80009b4L iris_173 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_173                        : 1 ;  //     0     
} O18A0_IRIS_173_T;

/*-----------------------------------------------------------------------------
		0xc80009b8L iris_174 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_174                        : 1 ;  //     0     
} O18A0_IRIS_174_T;

/*-----------------------------------------------------------------------------
		0xc80009bcL iris_175 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sw_rst_blk                     : 8 ;  //  7: 0     
	UINT32 reg_hw_rst_blk                     : 8 ;  // 15: 8     
} O18A0_IRIS_175_T;

/*-----------------------------------------------------------------------------
		0xc80009c0L iris_176 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_cenable_f0cnt           : 20;  // 19: 0     
	UINT32 reg_status_cenable_ctrl            : 7 ;  // 26:20     
} O18A0_IRIS_176_T;

/*-----------------------------------------------------------------------------
		0xc80009c4L iris_177 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_cenable_lcnt            : 12;  // 11: 0     
	UINT32 reg_status_cenable_f1cnt           : 20;  // 31:12     
} O18A0_IRIS_177_T;

/*-----------------------------------------------------------------------------
		0xc80009c8L iris_178 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_updn_rst                : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_clampagc_updn                  : 5 ;  //  8: 4     
} O18A0_IRIS_178_T;

/*-----------------------------------------------------------------------------
		0xc80009ccL iris_179 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_updn                    : 32;  // 31: 0     
} O18A0_IRIS_179_T;

/*-----------------------------------------------------------------------------
		0xc80009d0L iris_180 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_secam_pll                   : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs_secam_sw_old                : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs_auto_secam_level            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_rsv_180_12                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_rsv_180_16                     : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_rsv_180_20                     : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_cs_sw_rst                      : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs_hw_rst                      : 1 ;  //    28     
} O18A0_IRIS_180_T;

/*-----------------------------------------------------------------------------
		0xc80009d4L iris_181 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_phase_offset_range          : 8 ;  //  7: 0     
	UINT32 reg_cs_avg_freq_range              : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cs_issecam_th                  : 6 ;  // 17:12     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_cs_freq_offset_range           : 8 ;  // 27:20     
} O18A0_IRIS_181_T;

/*-----------------------------------------------------------------------------
		0xc80009d8L iris_182 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_db_freq                     : 12;  // 11: 0     
	UINT32 reg_cs_dr_freq                     : 12;  // 23:12     
	UINT32 reg_cs_ispal_th                    : 8 ;  // 31:24     
} O18A0_IRIS_182_T;

/*-----------------------------------------------------------------------------
		0xc80009dcL iris_183 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_cagc_en                     : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs_chroma_burst5or10           : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs_pal60_mode                  : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs_ntsc443_mode                : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cs_colour_mode                 : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs_adaptive_mode               : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs_secam_ybw                   : 2 ;  // 25:24     
} O18A0_IRIS_183_T;

/*-----------------------------------------------------------------------------
		0xc80009e0L iris_184 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_cagc_coring_threshold       : 4 ;  //  3: 0     
	UINT32 reg_cs_cagc_coring                 : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs_cagc_unity_gain             : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs_cagc_tc_p                   : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_cs_cagc_tc_ibig                : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs_cagc_tc_ismall              : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs_cagc                        : 8 ;  // 31:24     
} O18A0_IRIS_184_T;

/*-----------------------------------------------------------------------------
		0xc80009e4L iris_185 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_chroma_bw_lo                : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_cs_ckill                       : 16;  // 19: 4     
	UINT32 reg_cs_hlock_ckill                 : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_cs_vbi_ckill                   : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs_noburst_ckill               : 1 ;  //    28     
} O18A0_IRIS_185_T;

/*-----------------------------------------------------------------------------
		0xc80009e8L iris_186 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_cdto_inc                    : 32;  // 31: 0     
} O18A0_IRIS_186_T;

/*-----------------------------------------------------------------------------
		0xc80009ecL iris_187 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_cstate                      : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 reg_cs_fixed_cstate                : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs_user_ckill_mode             : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cs_lose_chromalock_mode        : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_cs_lose_chromalock_count       : 4 ;  // 19:16     
	UINT32 reg_cs_lose_chromalock_level       : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs_lose_chromalock_ckill       : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs_palsw_level                 : 2 ;  // 29:28     
} O18A0_IRIS_187_T;

/*-----------------------------------------------------------------------------
		0xc80009f0L iris_188 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_chroma_sel                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs_cphase_adjust               : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs_cphase_adjust_sel           : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs_mv_colourstripes_sel        : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cs_cstripe_detect_control      : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs_cdct_demod_sel              : 2 ;  // 21:20     
} O18A0_IRIS_188_T;

/*-----------------------------------------------------------------------------
		0xc80009f4L iris_189 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_secam_detected              : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs_mv_colourstripes            : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs_status_cordic_freq          : 8 ;  // 15: 8     
	UINT32 reg_cs_status_burst_mag            : 16;  // 31:16     
} O18A0_IRIS_189_T;

/*-----------------------------------------------------------------------------
		0xc80009f8L iris_190 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_chromalock                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs_status_cgain                : 14;  // 17: 4     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_cs_status_cmag                 : 8 ;  // 27:20     
	UINT32 reg_cs_pal_detected                : 1 ;  //    28     
} O18A0_IRIS_190_T;

/*-----------------------------------------------------------------------------
		0xc80009fcL iris_191 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_secam_pll                  : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs1_secam_sw_old               : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs1_auto_secam_level           : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_rsv_191_12                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_rsv_191_16                     : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_rsv_191_20                     : 2 ;  // 21:20     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 reg_cs1_sw_rst                     : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs1_hw_rst                     : 1 ;  //    28     
} O18A0_IRIS_191_T;

/*-----------------------------------------------------------------------------
		0xc8000a00L iris_192 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_phase_offset_range         : 8 ;  //  7: 0     
	UINT32 reg_cs1_avg_freq_range             : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cs1_issecam_th                 : 6 ;  // 17:12     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_cs1_freq_offset_range          : 8 ;  // 27:20     
} O18A0_IRIS_192_T;

/*-----------------------------------------------------------------------------
		0xc8000a04L iris_193 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_db_freq                    : 12;  // 11: 0     
	UINT32 reg_cs1_dr_freq                    : 12;  // 23:12     
	UINT32 reg_cs1_ispal_th                   : 8 ;  // 31:24     
} O18A0_IRIS_193_T;

/*-----------------------------------------------------------------------------
		0xc8000a08L iris_194 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_cagc_en                    : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs1_chroma_burst5or10          : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs1_pal60_mode                 : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs1_ntsc443_mode               : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cs1_colour_mode                : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs1_adaptive_mode              : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs1_secam_ybw                  : 2 ;  // 25:24     
} O18A0_IRIS_194_T;

/*-----------------------------------------------------------------------------
		0xc8000a0cL iris_195 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_cagc_coring_threshold      : 4 ;  //  3: 0     
	UINT32 reg_cs1_cagc_coring                : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs1_cagc_unity_gain            : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs1_cagc_tc_p                  : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_cs1_cagc_tc_ibig               : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs1_cagc_tc_ismall             : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs1_cagc                       : 8 ;  // 31:24     
} O18A0_IRIS_195_T;

/*-----------------------------------------------------------------------------
		0xc8000a10L iris_196 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_chroma_bw_lo               : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_cs1_ckill                      : 16;  // 19: 4     
	UINT32 reg_cs1_hlock_ckill                : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 reg_cs1_vbi_ckill                  : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs1_noburst_ckill              : 1 ;  //    28     
} O18A0_IRIS_196_T;

/*-----------------------------------------------------------------------------
		0xc8000a14L iris_197 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_cdto_inc                   : 32;  // 31: 0     
} O18A0_IRIS_197_T;

/*-----------------------------------------------------------------------------
		0xc8000a18L iris_198 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_cstate                     : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 reg_cs1_fixed_cstate               : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_cs1_user_ckill_mode            : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_cs1_lose_chromalock_mode       : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_cs1_lose_chromalock_count      : 4 ;  // 19:16     
	UINT32 reg_cs1_lose_chromalock_level      : 3 ;  // 22:20     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cs1_lose_chromalock_ckill      : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 reg_cs1_palsw_level                : 2 ;  // 29:28     
} O18A0_IRIS_198_T;

/*-----------------------------------------------------------------------------
		0xc8000a1cL iris_199 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_chroma_sel                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs1_cphase_adjust              : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs1_cphase_adjust_sel          : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_cs1_mv_colourstripes_sel       : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_cs1_cstripe_detect_control     : 3 ;  // 18:16     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 reg_cs1_cdct_demod_sel             : 2 ;  // 21:20     
} O18A0_IRIS_199_T;

/*-----------------------------------------------------------------------------
		0xc8000a20L iris_200 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_secam_detected             : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs1_mv_colourstripes           : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 reg_cs1_status_cordic_freq         : 8 ;  // 15: 8     
	UINT32 reg_cs1_status_burst_mag           : 16;  // 31:16     
} O18A0_IRIS_200_T;

/*-----------------------------------------------------------------------------
		0xc8000a24L iris_201 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_chromalock                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cs1_status_cgain               : 14;  // 17: 4     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_cs1_status_cmag                : 8 ;  // 27:20     
	UINT32 reg_cs1_pal_detected               : 1 ;  //    28     
} O18A0_IRIS_201_T;

/*-----------------------------------------------------------------------------
		0xc8000a28L iris_202 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_ctrl                   : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_estfrdp_on                     : 1 ;  //     8     
} O18A0_IRIS_202_T;

/*-----------------------------------------------------------------------------
		0xc8000a2cL iris_203 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_tgt_cf0cnt             : 20;  // 19: 0     
} O18A0_IRIS_203_T;

/*-----------------------------------------------------------------------------
		0xc8000a30L iris_204 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_tgt_cf1cnt             : 20;  // 19: 0     
} O18A0_IRIS_204_T;

/*-----------------------------------------------------------------------------
		0xc8000a34L iris_205 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_err_win1_u             : 8 ;  //  7: 0     
	UINT32 reg_estfrdp_err_win1_l             : 8 ;  // 15: 8     
	UINT32 reg_estfrdp_err_win0_u             : 8 ;  // 23:16     
	UINT32 reg_estfrdp_err_win0_l             : 8 ;  // 31:24     
} O18A0_IRIS_205_T;

/*-----------------------------------------------------------------------------
		0xc8000a38L iris_206 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_err_flag_th            : 8 ;  //  7: 0     
} O18A0_IRIS_206_T;

/*-----------------------------------------------------------------------------
		0xc8000a3cL iris_207 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_estfrdp_err                    : 8 ;  //  7: 0     
	UINT32 reg_estfrdp_err_flag               : 1 ;  //     8     
} O18A0_IRIS_207_T;

/*-----------------------------------------------------------------------------
		0xc8000a40L iris_208 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vsync_width                    : 4 ;  //  3: 0     
} O18A0_IRIS_208_T;

/*-----------------------------------------------------------------------------
		0xc8000a44L iris_209 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl0                 : 32;  // 31: 0     
} O18A0_IRIS_209_T;

/*-----------------------------------------------------------------------------
		0xc8000a48L iris_210 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl1                 : 32;  // 31: 0     
} O18A0_IRIS_210_T;

/*-----------------------------------------------------------------------------
		0xc8000a4cL iris_211 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl2                 : 32;  // 31: 0     
} O18A0_IRIS_211_T;

/*-----------------------------------------------------------------------------
		0xc8000a50L iris_212 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl3                 : 32;  // 31: 0     
} O18A0_IRIS_212_T;

/*-----------------------------------------------------------------------------
		0xc8000a54L iris_213 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl4                 : 32;  // 31: 0     
} O18A0_IRIS_213_T;

/*-----------------------------------------------------------------------------
		0xc8000a58L iris_214 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl5                 : 32;  // 31: 0     
} O18A0_IRIS_214_T;

/*-----------------------------------------------------------------------------
		0xc8000a5cL iris_215 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl6                 : 32;  // 31: 0     
} O18A0_IRIS_215_T;

/*-----------------------------------------------------------------------------
		0xc8000a60L iris_216 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl7                 : 32;  // 31: 0     
} O18A0_IRIS_216_T;

/*-----------------------------------------------------------------------------
		0xc8000a64L iris_217 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl8                 : 32;  // 31: 0     
} O18A0_IRIS_217_T;

/*-----------------------------------------------------------------------------
		0xc8000a68L iris_218 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl9                 : 32;  // 31: 0     
} O18A0_IRIS_218_T;

/*-----------------------------------------------------------------------------
		0xc8000a6cL iris_219 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl10                : 32;  // 31: 0     
} O18A0_IRIS_219_T;

/*-----------------------------------------------------------------------------
		0xc8000a70L iris_220 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl0                 : 32;  // 31: 0     
} O18A0_IRIS_220_T;

/*-----------------------------------------------------------------------------
		0xc8000a74L iris_221 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl1                 : 32;  // 31: 0     
} O18A0_IRIS_221_T;

/*-----------------------------------------------------------------------------
		0xc8000a78L iris_222 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl2                 : 32;  // 31: 0     
} O18A0_IRIS_222_T;

/*-----------------------------------------------------------------------------
		0xc8000a7cL iris_223 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl3                 : 32;  // 31: 0     
} O18A0_IRIS_223_T;

/*-----------------------------------------------------------------------------
		0xc8000a80L iris_224 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl4                 : 32;  // 31: 0     
} O18A0_IRIS_224_T;

/*-----------------------------------------------------------------------------
		0xc8000a84L iris_225 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl5                 : 32;  // 31: 0     
} O18A0_IRIS_225_T;

/*-----------------------------------------------------------------------------
		0xc8000a88L iris_226 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl6                 : 32;  // 31: 0     
} O18A0_IRIS_226_T;

/*-----------------------------------------------------------------------------
		0xc8000a8cL iris_227 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_ctrl7                 : 32;  // 31: 0     
} O18A0_IRIS_227_T;

/*-----------------------------------------------------------------------------
		0xc8000a90L iris_228 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl0                 : 32;  // 31: 0     
} O18A0_IRIS_228_T;

/*-----------------------------------------------------------------------------
		0xc8000a94L iris_229 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl1                 : 32;  // 31: 0     
} O18A0_IRIS_229_T;

/*-----------------------------------------------------------------------------
		0xc8000a98L iris_230 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl2                 : 32;  // 31: 0     
} O18A0_IRIS_230_T;

/*-----------------------------------------------------------------------------
		0xc8000a9cL iris_231 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl3                 : 32;  // 31: 0     
} O18A0_IRIS_231_T;

/*-----------------------------------------------------------------------------
		0xc8000aa0L iris_232 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl4                 : 32;  // 31: 0     
} O18A0_IRIS_232_T;

/*-----------------------------------------------------------------------------
		0xc8000aa4L iris_233 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl5                 : 32;  // 31: 0     
} O18A0_IRIS_233_T;

/*-----------------------------------------------------------------------------
		0xc8000aa8L iris_234 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl6                 : 32;  // 31: 0     
} O18A0_IRIS_234_T;

/*-----------------------------------------------------------------------------
		0xc8000aacL iris_235 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl7                 : 32;  // 31: 0     
} O18A0_IRIS_235_T;

/*-----------------------------------------------------------------------------
		0xc8000ab0L iris_236 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_blend_ctrl0              : 32;  // 31: 0     
} O18A0_IRIS_236_T;

/*-----------------------------------------------------------------------------
		0xc8000ab4L iris_237 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl11                : 32;  // 31: 0     
} O18A0_IRIS_237_T;

/*-----------------------------------------------------------------------------
		0xc8000ab8L iris_238 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl12                : 32;  // 31: 0     
} O18A0_IRIS_238_T;

/*-----------------------------------------------------------------------------
		0xc8000abcL iris_239 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl13                : 32;  // 31: 0     
} O18A0_IRIS_239_T;

/*-----------------------------------------------------------------------------
		0xc8000ac0L iris_240 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl14                : 32;  // 31: 0     
} O18A0_IRIS_240_T;

/*-----------------------------------------------------------------------------
		0xc8000ac4L iris_241 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl15                : 32;  // 31: 0     
} O18A0_IRIS_241_T;

/*-----------------------------------------------------------------------------
		0xc8000ac8L iris_242 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl0                    : 32;  // 31: 0     
} O18A0_IRIS_242_T;

/*-----------------------------------------------------------------------------
		0xc8000accL iris_243 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl1                    : 32;  // 31: 0     
} O18A0_IRIS_243_T;

/*-----------------------------------------------------------------------------
		0xc8000ad0L iris_244 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl2                    : 32;  // 31: 0     
} O18A0_IRIS_244_T;

/*-----------------------------------------------------------------------------
		0xc8000ad4L iris_245 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl3                    : 32;  // 31: 0     
} O18A0_IRIS_245_T;

/*-----------------------------------------------------------------------------
		0xc8000ad8L iris_246 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl4                    : 32;  // 31: 0     
} O18A0_IRIS_246_T;

/*-----------------------------------------------------------------------------
		0xc8000adcL iris_247 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl5                    : 32;  // 31: 0     
} O18A0_IRIS_247_T;

/*-----------------------------------------------------------------------------
		0xc8000ae0L iris_248 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl6                    : 32;  // 31: 0     
} O18A0_IRIS_248_T;

/*-----------------------------------------------------------------------------
		0xc8000ae4L iris_249 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl7                    : 32;  // 31: 0     
} O18A0_IRIS_249_T;

/*-----------------------------------------------------------------------------
		0xc8000ae8L iris_250 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl8                    : 32;  // 31: 0     
} O18A0_IRIS_250_T;

/*-----------------------------------------------------------------------------
		0xc8000aecL iris_251 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl9                    : 32;  // 31: 0     
} O18A0_IRIS_251_T;

/*-----------------------------------------------------------------------------
		0xc8000af0L iris_252 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl10                   : 32;  // 31: 0     
} O18A0_IRIS_252_T;

/*-----------------------------------------------------------------------------
		0xc8000af4L iris_253 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_0             : 32;  // 31: 0     
} O18A0_IRIS_253_T;

/*-----------------------------------------------------------------------------
		0xc8000af8L iris_254 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_1             : 32;  // 31: 0     
} O18A0_IRIS_254_T;

/*-----------------------------------------------------------------------------
		0xc8000afcL iris_255 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_2             : 32;  // 31: 0     
} O18A0_IRIS_255_T;

/*-----------------------------------------------------------------------------
		0xc8000b00L iris_256 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_3             : 32;  // 31: 0     
} O18A0_IRIS_256_T;

/*-----------------------------------------------------------------------------
		0xc8000b04L iris_257 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_4             : 32;  // 31: 0     
} O18A0_IRIS_257_T;

/*-----------------------------------------------------------------------------
		0xc8000b08L iris_258 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_5             : 32;  // 31: 0     
} O18A0_IRIS_258_T;

/*-----------------------------------------------------------------------------
		0xc8000b0cL iris_259 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hrs_cx2_coef2                  : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_hrs_cx2_coef1                  : 11;  // 22:12     
} O18A0_IRIS_259_T;

/*-----------------------------------------------------------------------------
		0xc8000b10L iris_260 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hrs_cx2_coef4                  : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_hrs_cx2_coef3                  : 11;  // 22:12     
} O18A0_IRIS_260_T;

/*-----------------------------------------------------------------------------
		0xc8000b14L iris_261 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_261                        : 1 ;  //     0     
} O18A0_IRIS_261_T;

/*-----------------------------------------------------------------------------
		0xc8000b18L iris_262 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_rsv_262                        : 1 ;  //     0     
} O18A0_IRIS_262_T;

/*-----------------------------------------------------------------------------
		0xc8000b1cL iris_263 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hrs_ha_width                   : 8 ;  //  7: 0     
	UINT32 reg_hrs_ha_start                   : 8 ;  // 15: 8     
	UINT32 reg_hrs_va_start_field             : 2 ;  // 17:16     
} O18A0_IRIS_263_T;

/*-----------------------------------------------------------------------------
		0xc8000b20L iris_264 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cti_ctrl0                      : 32;  // 31: 0     
} O18A0_IRIS_264_T;

/*-----------------------------------------------------------------------------
		0xc8000b24L iris_265 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cti_ctrl1                      : 32;  // 31: 0     
} O18A0_IRIS_265_T;

/*-----------------------------------------------------------------------------
		0xc8000b30L iris_266 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_3d_status0               : 32;  // 31: 0     
} O18A0_IRIS_266_T;

/*-----------------------------------------------------------------------------
		0xc8000b34L iris_267 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_6             : 32;  // 31: 0     
} O18A0_IRIS_267_T;

/*-----------------------------------------------------------------------------
		0xc8000b38L iris_268 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_7             : 32;  // 31: 0     
} O18A0_IRIS_268_T;

/*-----------------------------------------------------------------------------
		0xc8000b3cL iris_269 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycadjust_sat_ctrl_0            : 32;  // 31: 0     
} O18A0_IRIS_269_T;

/*-----------------------------------------------------------------------------
		0xc8000b40L iris_270 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl16                : 32;  // 31: 0     
} O18A0_IRIS_270_T;

/*-----------------------------------------------------------------------------
		0xc8000b44L iris_271 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl17                : 32;  // 31: 0     
} O18A0_IRIS_271_T;

/*-----------------------------------------------------------------------------
		0xc8000b48L iris_272 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burst2_gate_end                : 8 ;  //  7: 0     
	UINT32 reg_burst2_gate_start              : 8 ;  // 15: 8     
	UINT32 reg_burst1_gate_end                : 8 ;  // 23:16     
	UINT32 reg_burst1_gate_start              : 8 ;  // 31:24     
} O18A0_IRIS_272_T;

/*-----------------------------------------------------------------------------
		0xc8000b4cL iris_273 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cordic2_gate_end               : 8 ;  //  7: 0     
	UINT32 reg_cordic2_gate_start             : 8 ;  // 15: 8     
	UINT32 reg_cordic1_gate_end               : 8 ;  // 23:16     
	UINT32 reg_cordic1_gate_start             : 8 ;  // 31:24     
} O18A0_IRIS_273_T;

/*-----------------------------------------------------------------------------
		0xc8000b50L iris_274 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_cbcr_ctrl                : 16;  // 15: 0     
	UINT32 reg_status_vdetect_vcount          : 10;  // 25:16     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 reg_vactive_height_auto            : 1 ;  //    28     
} O18A0_IRIS_274_T;

/*-----------------------------------------------------------------------------
		0xc8000b54L iris_275 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_1           : 17;  // 16: 0     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_secam_y_notch_mode             : 1 ;  //    20     
} O18A0_IRIS_275_T;

/*-----------------------------------------------------------------------------
		0xc8000b58L iris_276 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_2           : 17;  // 16: 0     
} O18A0_IRIS_276_T;

/*-----------------------------------------------------------------------------
		0xc8000b5cL iris_277 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_3           : 17;  // 16: 0     
} O18A0_IRIS_277_T;

/*-----------------------------------------------------------------------------
		0xc8000b60L iris_278 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_4           : 17;  // 16: 0     
} O18A0_IRIS_278_T;

/*-----------------------------------------------------------------------------
		0xc8000b64L iris_279 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_5           : 17;  // 16: 0     
} O18A0_IRIS_279_T;

/*-----------------------------------------------------------------------------
		0xc8000b68L iris_280 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_6           : 17;  // 16: 0     
} O18A0_IRIS_280_T;

/*-----------------------------------------------------------------------------
		0xc8000b6cL iris_281 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_7           : 17;  // 16: 0     
} O18A0_IRIS_281_T;

/*-----------------------------------------------------------------------------
		0xc8000b70L iris_282 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_8           : 17;  // 16: 0     
} O18A0_IRIS_282_T;

/*-----------------------------------------------------------------------------
		0xc8000b74L iris_283 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_y_notch_ctrl_9           : 17;  // 16: 0     
} O18A0_IRIS_283_T;

/*-----------------------------------------------------------------------------
		0xc8000b78L iris_284 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_1           : 17;  // 16: 0     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_secam_c_notch_sel              : 1 ;  //    20     
} O18A0_IRIS_284_T;

/*-----------------------------------------------------------------------------
		0xc8000b7cL iris_285 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_2           : 17;  // 16: 0     
} O18A0_IRIS_285_T;

/*-----------------------------------------------------------------------------
		0xc8000b80L iris_286 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_3           : 17;  // 16: 0     
} O18A0_IRIS_286_T;

/*-----------------------------------------------------------------------------
		0xc8000b84L iris_287 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_4           : 17;  // 16: 0     
} O18A0_IRIS_287_T;

/*-----------------------------------------------------------------------------
		0xc8000b88L iris_288 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_5           : 17;  // 16: 0     
} O18A0_IRIS_288_T;

/*-----------------------------------------------------------------------------
		0xc8000b8cL iris_289 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_6           : 17;  // 16: 0     
} O18A0_IRIS_289_T;

/*-----------------------------------------------------------------------------
		0xc8000b90L iris_290 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_7           : 17;  // 16: 0     
} O18A0_IRIS_290_T;

/*-----------------------------------------------------------------------------
		0xc8000b94L iris_291 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_8           : 17;  // 16: 0     
} O18A0_IRIS_291_T;

/*-----------------------------------------------------------------------------
		0xc8000b98L iris_292 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_c_notch_ctrl_9           : 17;  // 16: 0     
} O18A0_IRIS_292_T;

/*-----------------------------------------------------------------------------
		0xc8000b9cL iris_293 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_ctrl11                   : 32;  // 31: 0     
} O18A0_IRIS_293_T;

/*-----------------------------------------------------------------------------
		0xc8000ba0L iris_294 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_ybw2                     : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_secam_y_delay                  : 6 ;  //  9: 4     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_secam_dcr_passthrough          : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_v_valid_inv                    : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_secam_lb_en                    : 1 ;  //    20     
} O18A0_IRIS_294_T;

/*-----------------------------------------------------------------------------
		0xc8000ba4L iris_295 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_dcr_ctrl_0               : 32;  // 31: 0     
} O18A0_IRIS_295_T;

/*-----------------------------------------------------------------------------
		0xc8000ba8L iris_296 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_dcr_ctrl_1               : 32;  // 31: 0     
} O18A0_IRIS_296_T;

/*-----------------------------------------------------------------------------
		0xc8000bacL iris_297 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_secam_dcr_ctrl_2               : 32;  // 31: 0     
} O18A0_IRIS_297_T;

/*-----------------------------------------------------------------------------
		0xc8000bb0L iris_298 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_yup_rise                       : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_ydn_cnt                        : 8 ;  // 19:12     
	UINT32 reg_yup_cnt                        : 8 ;  // 27:20     
} O18A0_IRIS_298_T;

/*-----------------------------------------------------------------------------
		0xc8000bb4L iris_299 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ydn_rise                       : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 reg_yup_fall                       : 11;  // 22:12     
} O18A0_IRIS_299_T;

/*-----------------------------------------------------------------------------
		0xc8000bb8L iris_300 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_clamp_sel                      : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_ydn_fall                       : 11;  // 14: 4     
} O18A0_IRIS_300_T;

/*-----------------------------------------------------------------------------
		0xc8000bbcL iris_301 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl18                : 32;  // 31: 0     
} O18A0_IRIS_301_T;

/*-----------------------------------------------------------------------------
		0xc8000bc0L iris_302 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl19                : 32;  // 31: 0     
} O18A0_IRIS_302_T;

/*-----------------------------------------------------------------------------
		0xc8000bc4L iris_303 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl20                : 32;  // 31: 0     
} O18A0_IRIS_303_T;

/*-----------------------------------------------------------------------------
		0xc8000bc8L iris_304 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_wmask_ctrl_0                   : 32;  // 31: 0     
} O18A0_IRIS_304_T;

/*-----------------------------------------------------------------------------
		0xc8000bccL iris_305 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_wmask_ctrl_1                   : 32;  // 31: 0     
} O18A0_IRIS_305_T;

/*-----------------------------------------------------------------------------
		0xc8000bd0L iris_306 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdetect_lpf_ctrl_8             : 32;  // 31: 0     
} O18A0_IRIS_306_T;

/*-----------------------------------------------------------------------------
		0xc8000bd4L iris_307 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdct_ifcomp_ctrl_0             : 32;  // 31: 0     
} O18A0_IRIS_307_T;

/*-----------------------------------------------------------------------------
		0xc8000bd8L iris_308 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl21                : 32;  // 31: 0     
} O18A0_IRIS_308_T;

/*-----------------------------------------------------------------------------
		0xc8000bdcL iris_309 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl22                : 32;  // 31: 0     
} O18A0_IRIS_309_T;

/*-----------------------------------------------------------------------------
		0xc8000be0L iris_310 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl23                : 32;  // 31: 0     
} O18A0_IRIS_310_T;

/*-----------------------------------------------------------------------------
		0xc8000be4L iris_311 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl24                : 32;  // 31: 0     
} O18A0_IRIS_311_T;

/*-----------------------------------------------------------------------------
		0xc8000be8L iris_312 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl25                : 32;  // 31: 0     
} O18A0_IRIS_312_T;

/*-----------------------------------------------------------------------------
		0xc8000becL iris_313 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl26                : 32;  // 31: 0     
} O18A0_IRIS_313_T;

/*-----------------------------------------------------------------------------
		0xc8000bf0L iris_314 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl27                : 32;  // 31: 0     
} O18A0_IRIS_314_T;

/*-----------------------------------------------------------------------------
		0xc8000bf4L iris_315 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl28                : 32;  // 31: 0     
} O18A0_IRIS_315_T;

/*-----------------------------------------------------------------------------
		0xc8000bf8L iris_316 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl29                : 32;  // 31: 0     
} O18A0_IRIS_316_T;

/*-----------------------------------------------------------------------------
		0xc8000bfcL iris_317 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl30                : 32;  // 31: 0     
} O18A0_IRIS_317_T;

/*-----------------------------------------------------------------------------
		0xc8000c00L iris_318 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl31                : 32;  // 31: 0     
} O18A0_IRIS_318_T;

/*-----------------------------------------------------------------------------
		0xc8000c04L iris_319 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl32                : 32;  // 31: 0     
} O18A0_IRIS_319_T;

/*-----------------------------------------------------------------------------
		0xc8000c08L iris_320 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl33                : 32;  // 31: 0     
} O18A0_IRIS_320_T;

/*-----------------------------------------------------------------------------
		0xc8000c0cL iris_321 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl34                : 32;  // 31: 0     
} O18A0_IRIS_321_T;

/*-----------------------------------------------------------------------------
		0xc8000c10L iris_322 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl35                : 32;  // 31: 0     
} O18A0_IRIS_322_T;

/*-----------------------------------------------------------------------------
		0xc8000c14L iris_323 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl36                : 32;  // 31: 0     
} O18A0_IRIS_323_T;

/*-----------------------------------------------------------------------------
		0xc8000c18L iris_324 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl8                 : 32;  // 31: 0     
} O18A0_IRIS_324_T;

/*-----------------------------------------------------------------------------
		0xc8000c1cL iris_325 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl9                 : 32;  // 31: 0     
} O18A0_IRIS_325_T;

/*-----------------------------------------------------------------------------
		0xc8000c20L iris_326 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl10                : 32;  // 31: 0     
} O18A0_IRIS_326_T;

/*-----------------------------------------------------------------------------
		0xc8000c24L iris_327 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl11                : 32;  // 31: 0     
} O18A0_IRIS_327_T;

/*-----------------------------------------------------------------------------
		0xc8000c28L iris_328 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl12                : 32;  // 31: 0     
} O18A0_IRIS_328_T;

/*-----------------------------------------------------------------------------
		0xc8000c2cL iris_329 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl13                : 32;  // 31: 0     
} O18A0_IRIS_329_T;

/*-----------------------------------------------------------------------------
		0xc8000c30L iris_330 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl14                : 32;  // 31: 0     
} O18A0_IRIS_330_T;

/*-----------------------------------------------------------------------------
		0xc8000c34L iris_331 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl15                : 32;  // 31: 0     
} O18A0_IRIS_331_T;

/*-----------------------------------------------------------------------------
		0xc8000c38L iris_332 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl16                : 32;  // 31: 0     
} O18A0_IRIS_332_T;

/*-----------------------------------------------------------------------------
		0xc8000c3cL iris_333 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl17                : 32;  // 31: 0     
} O18A0_IRIS_333_T;

/*-----------------------------------------------------------------------------
		0xc8000c40L iris_334 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl37                : 32;  // 31: 0     
} O18A0_IRIS_334_T;

/*-----------------------------------------------------------------------------
		0xc8000c44L iris_335 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl38                : 32;  // 31: 0     
} O18A0_IRIS_335_T;

/*-----------------------------------------------------------------------------
		0xc8000c48L iris_336 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl39                : 32;  // 31: 0     
} O18A0_IRIS_336_T;

/*-----------------------------------------------------------------------------
		0xc8000c4cL iris_337 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl40                : 32;  // 31: 0     
} O18A0_IRIS_337_T;

/*-----------------------------------------------------------------------------
		0xc8000c50L iris_338 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl41                : 32;  // 31: 0     
} O18A0_IRIS_338_T;

/*-----------------------------------------------------------------------------
		0xc8000c54L iris_339 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl42                : 32;  // 31: 0     
} O18A0_IRIS_339_T;

/*-----------------------------------------------------------------------------
		0xc8000c58L iris_340 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl43                : 32;  // 31: 0     
} O18A0_IRIS_340_T;

/*-----------------------------------------------------------------------------
		0xc8000c5cL iris_341 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl44                : 32;  // 31: 0     
} O18A0_IRIS_341_T;

/*-----------------------------------------------------------------------------
		0xc8000c60L iris_342 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl45                : 32;  // 31: 0     
} O18A0_IRIS_342_T;

/*-----------------------------------------------------------------------------
		0xc8000c64L iris_343 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl46                : 32;  // 31: 0     
} O18A0_IRIS_343_T;

/*-----------------------------------------------------------------------------
		0xc8000c68L iris_344 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cordic_ctrl0                   : 32;  // 31: 0     
} O18A0_IRIS_344_T;

/*-----------------------------------------------------------------------------
		0xc8000c6cL iris_345 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs_cordic_ctrl0                : 32;  // 31: 0     
} O18A0_IRIS_345_T;

/*-----------------------------------------------------------------------------
		0xc8000c70L iris_346 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cs1_cordic_ctrl0               : 32;  // 31: 0     
} O18A0_IRIS_346_T;

/*-----------------------------------------------------------------------------
		0xc8000c74L iris_347 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl0               : 32;  // 31: 0     
} O18A0_IRIS_347_T;

/*-----------------------------------------------------------------------------
		0xc8000c78L iris_348 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl1               : 32;  // 31: 0     
} O18A0_IRIS_348_T;

/*-----------------------------------------------------------------------------
		0xc8000c7cL iris_349 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl2               : 32;  // 31: 0     
} O18A0_IRIS_349_T;

/*-----------------------------------------------------------------------------
		0xc8000c80L iris_350 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl3               : 32;  // 31: 0     
} O18A0_IRIS_350_T;

/*-----------------------------------------------------------------------------
		0xc8000c84L iris_351 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl47                : 32;  // 31: 0     
} O18A0_IRIS_351_T;

/*-----------------------------------------------------------------------------
		0xc8000c88L iris_352 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl48                : 32;  // 31: 0     
} O18A0_IRIS_352_T;

/*-----------------------------------------------------------------------------
		0xc8000c8cL iris_353 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl49                : 32;  // 31: 0     
} O18A0_IRIS_353_T;

/*-----------------------------------------------------------------------------
		0xc8000c90L iris_354 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl50                : 32;  // 31: 0     
} O18A0_IRIS_354_T;

/*-----------------------------------------------------------------------------
		0xc8000c94L iris_355 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_2d_ctrl51                : 32;  // 31: 0     
} O18A0_IRIS_355_T;

/*-----------------------------------------------------------------------------
		0xc8000c98L iris_356 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl4               : 32;  // 31: 0     
} O18A0_IRIS_356_T;

/*-----------------------------------------------------------------------------
		0xc8000c9cL iris_357 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl5               : 32;  // 31: 0     
} O18A0_IRIS_357_T;

/*-----------------------------------------------------------------------------
		0xc8000ca0L iris_358 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl6               : 32;  // 31: 0     
} O18A0_IRIS_358_T;

/*-----------------------------------------------------------------------------
		0xc8000ca4L iris_359 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_hdetect_nr_ctrl7               : 32;  // 31: 0     
} O18A0_IRIS_359_T;

/*-----------------------------------------------------------------------------
		0xc8000ca8L iris_360 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_clpf_ctrl0                  : 32;  // 31: 0     
} O18A0_IRIS_360_T;

/*-----------------------------------------------------------------------------
		0xc8000cacL iris_361 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_clpf_ctrl1                  : 32;  // 31: 0     
} O18A0_IRIS_361_T;

/*-----------------------------------------------------------------------------
		0xc8000cb0L iris_362 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_clpf_ctrl2                  : 32;  // 31: 0     
} O18A0_IRIS_362_T;

/*-----------------------------------------------------------------------------
		0xc8000cb4L iris_363 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_fb_clpf_ctrl3                  : 32;  // 31: 0     
} O18A0_IRIS_363_T;

/*-----------------------------------------------------------------------------
		0xc8000cb8L iris_364 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_fb_in_cnt               : 20;  // 19: 0     
} O18A0_IRIS_364_T;

/*-----------------------------------------------------------------------------
		0xc8000cbcL iris_365 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl18                : 32;  // 31: 0     
} O18A0_IRIS_365_T;

/*-----------------------------------------------------------------------------
		0xc8000cc0L iris_366 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl19                : 32;  // 31: 0     
} O18A0_IRIS_366_T;

/*-----------------------------------------------------------------------------
		0xc8000cc4L iris_367 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl20                : 32;  // 31: 0     
} O18A0_IRIS_367_T;

/*-----------------------------------------------------------------------------
		0xc8000cc8L iris_368 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl21                : 32;  // 31: 0     
} O18A0_IRIS_368_T;

/*-----------------------------------------------------------------------------
		0xc8000cccL iris_369 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl22                : 32;  // 31: 0     
} O18A0_IRIS_369_T;

/*-----------------------------------------------------------------------------
		0xc8000cd0L iris_370 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_st_ctrl23                : 32;  // 31: 0     
} O18A0_IRIS_370_T;

/*-----------------------------------------------------------------------------
		0xc8000cd4L iris_371 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cti_ctrl2                      : 32;  // 31: 0     
} O18A0_IRIS_371_T;

/*-----------------------------------------------------------------------------
		0xc8000cd8L iris_372 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cdct_ifcomp_ctrl_1             : 32;  // 31: 0     
} O18A0_IRIS_372_T;

/*-----------------------------------------------------------------------------
		0xc8000cdcL iris_373 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lbadrgen_ctrl                  : 32;  // 31: 0     
} O18A0_IRIS_373_T;

/*-----------------------------------------------------------------------------
		0xc8000ce0L iris_374 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_burst_gate2_end                : 8 ;  //  7: 0     
	UINT32 reg_burst_gate2_start              : 8 ;  // 15: 8     
	UINT32 reg_burst_gate1_end                : 8 ;  // 23:16     
	UINT32 reg_burst_gate1_start              : 8 ;  // 31:24     
} O18A0_IRIS_374_T;

/*-----------------------------------------------------------------------------
		0xc8000ce4L iris_375 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_burst2_mag              : 8 ;  //  7: 0     
	UINT32 reg_status_burst1_mag              : 8 ;  // 15: 8     
	UINT32 reg_status_burst0_mag              : 8 ;  // 23:16     
	UINT32 reg_burst_mag_ctrl                 : 8 ;  // 31:24     
} O18A0_IRIS_375_T;

/*-----------------------------------------------------------------------------
		0xc8000d00L vbi_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_wss625_rd_done                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cc_rd_done                     : 1 ;  //     4     
} O18A0_VBI_001_T;

/*-----------------------------------------------------------------------------
		0xc8000d04L vbi_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_rdy                         : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_cc_data0                       : 8 ;  // 11: 4     
	UINT32 reg_cc_data1                       : 8 ;  // 19:12     
} O18A0_VBI_002_T;

/*-----------------------------------------------------------------------------
		0xc8000d08L vbi_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_wssdata0                       : 8 ;  //  7: 0     
	UINT32 reg_wssdata1                       : 8 ;  // 15: 8     
	UINT32 reg_wssdata2                       : 8 ;  // 23:16     
	UINT32 reg_wss_rdy                        : 1 ;  //    24     
} O18A0_VBI_003_T;

/*-----------------------------------------------------------------------------
		0xc8000d0cL vbi_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_short_start                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_vbi_muxout                     : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vbi_hsyncout                   : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_adap_slvl_en                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vbi_st_err_ignored             : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_vbi_en                         : 1 ;  //    20     
} O18A0_VBI_004_T;

/*-----------------------------------------------------------------------------
		0xc8000d10L vbi_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_lpf_bw                     : 2 ;  //  1: 0     
} O18A0_VBI_005_T;

/*-----------------------------------------------------------------------------
		0xc8000d14L vbi_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_data_hlvl                  : 8 ;  //  7: 0     
	UINT32 reg_start_code                     : 8 ;  // 15: 8     
} O18A0_VBI_006_T;

/*-----------------------------------------------------------------------------
		0xc8000d18L vbi_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil9                          : 8 ;  //  7: 0     
	UINT32 reg_vbil8                          : 8 ;  // 15: 8     
	UINT32 reg_vbil7                          : 8 ;  // 23:16     
	UINT32 reg_vbil6                          : 8 ;  // 31:24     
} O18A0_VBI_007_T;

/*-----------------------------------------------------------------------------
		0xc8000d1cL vbi_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil13                         : 8 ;  //  7: 0     
	UINT32 reg_vbil12                         : 8 ;  // 15: 8     
	UINT32 reg_vbil11                         : 8 ;  // 23:16     
	UINT32 reg_vbil10                         : 8 ;  // 31:24     
} O18A0_VBI_008_T;

/*-----------------------------------------------------------------------------
		0xc8000d20L vbi_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil17                         : 8 ;  //  7: 0     
	UINT32 reg_vbil16                         : 8 ;  // 15: 8     
	UINT32 reg_vbil15                         : 8 ;  // 23:16     
	UINT32 reg_vbil14                         : 8 ;  // 31:24     
} O18A0_VBI_009_T;

/*-----------------------------------------------------------------------------
		0xc8000d24L vbi_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil21                         : 8 ;  //  7: 0     
	UINT32 reg_vbil20                         : 8 ;  // 15: 8     
	UINT32 reg_vbil19                         : 8 ;  // 23:16     
	UINT32 reg_vbil18                         : 8 ;  // 31:24     
} O18A0_VBI_010_T;

/*-----------------------------------------------------------------------------
		0xc8000d28L vbi_011 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil25                         : 8 ;  //  7: 0     
	UINT32 reg_vbil24                         : 8 ;  // 15: 8     
	UINT32 reg_vbil23                         : 8 ;  // 23:16     
	UINT32 reg_vbil22                         : 8 ;  // 31:24     
} O18A0_VBI_011_T;

/*-----------------------------------------------------------------------------
		0xc8000d2cL vbi_012 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbil26                         : 8 ;  //  7: 0     
	UINT32 reg_vbil5                          : 8 ;  // 15: 8     
} O18A0_VBI_012_T;

/*-----------------------------------------------------------------------------
		0xc8000d30L vbi_013 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_vps_lpfil_fine_gain        : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_vbi_wss625_lpfil_fine_gain     : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_vbi_tele_lpfil_fine_gain       : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_vbi_cc_lpfil_fine_gain         : 2 ;  // 13:12     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 reg_vbi_vps_slicer_mode            : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 reg_vbi_wss_slicer_mode            : 2 ;  // 21:20     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 reg_vbi_tt_slicer_mode             : 2 ;  // 25:24     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 reg_vbi_cc_slicer_mode             : 2 ;  // 29:28     
} O18A0_VBI_013_T;

/*-----------------------------------------------------------------------------
		0xc8000d34L vbi_014 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_teletext_dto                   : 16;  // 15: 0     
	UINT32 reg_caption_dto                    : 16;  // 31:16     
} O18A0_VBI_014_T;

/*-----------------------------------------------------------------------------
		0xc8000d38L vbi_015 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vps_dto                        : 16;  // 15: 0     
	UINT32 reg_wss625_dto                     : 16;  // 31:16     
} O18A0_VBI_015_T;

/*-----------------------------------------------------------------------------
		0xc8000d3cL vbi_016 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vps_frame_start                : 2 ;  //  1: 0     
	UINT32                                    : 2 ;  //  3: 2     reserved
	UINT32 reg_teletext_frame_start           : 2 ;  //  5: 4     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 reg_wss625_frame_start             : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_caption_frame_start            : 2 ;  // 13:12     
} O18A0_VBI_016_T;

/*-----------------------------------------------------------------------------
		0xc8000d40L vbi_017 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_tele_lpfil_track_gain      : 4 ;  //  3: 0     
	UINT32 reg_vbi_tele_lpfil_acq_gain        : 4 ;  //  7: 4     
	UINT32 reg_vbi_cc_lpfil_track_gain        : 4 ;  // 11: 8     
	UINT32 reg_vbi_cc_lpfil_acq_gain          : 4 ;  // 15:12     
	UINT32 reg_wssj_delta_ampl                : 8 ;  // 23:16     
} O18A0_VBI_017_T;

/*-----------------------------------------------------------------------------
		0xc8000d44L vbi_018 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_vps_lpfil_track_gain       : 4 ;  //  3: 0     
	UINT32 reg_vbi_vps_lpfil_acq_gain         : 4 ;  //  7: 4     
	UINT32 reg_vbi_wss625_lpfil_track_gain    : 4 ;  // 11: 8     
	UINT32 reg_vbi_wss625_lpfil_acq_gain      : 4 ;  // 15:12     
} O18A0_VBI_018_T;

/*-----------------------------------------------------------------------------
		0xc8000d48L vbi_019 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_teletext_runin_accum_ampl      : 8 ;  //  7: 0     
	UINT32 reg_caption_runin_accum_ampl       : 8 ;  // 15: 8     
} O18A0_VBI_019_T;

/*-----------------------------------------------------------------------------
		0xc8000d4cL vbi_020 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vps_start                      : 8 ;  //  7: 0     
	UINT32 reg_teletext_start                 : 8 ;  // 15: 8     
	UINT32 reg_wss625_start                   : 8 ;  // 23:16     
	UINT32 reg_caption_start                  : 8 ;  // 31:24     
} O18A0_VBI_020_T;

/*-----------------------------------------------------------------------------
		0xc8000d50L vbi_021 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_frame_en_cnt                   : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 reg_frame_en_adj                   : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_vbi_fixgate_en                 : 1 ;  //    16     
} O18A0_VBI_021_T;

/*-----------------------------------------------------------------------------
		0xc8000d54L vbi_022 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi1_detect_cnt                : 16;  // 15: 0     
	UINT32 reg_vbi_monitor_line               : 10;  // 25:16     
	UINT32                                    : 2 ;  // 27:26     reserved
	UINT32 reg_vbi_monitor_ctrl               : 3 ;  // 30:28     
} O18A0_VBI_022_T;

/*-----------------------------------------------------------------------------
		0xc8000d58L vbi_023 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl0                      : 32;  // 31: 0     
} O18A0_VBI_023_T;

/*-----------------------------------------------------------------------------
		0xc8000d5cL vbi_024 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl1                      : 32;  // 31: 0     
} O18A0_VBI_024_T;

/*-----------------------------------------------------------------------------
		0xc8000d60L vbi_025 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl2                      : 32;  // 31: 0     
} O18A0_VBI_025_T;

/*-----------------------------------------------------------------------------
		0xc8000d64L vbi_026 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl3                      : 32;  // 31: 0     
} O18A0_VBI_026_T;

/*-----------------------------------------------------------------------------
		0xc8000d68L vbi_027 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl4                      : 32;  // 31: 0     
} O18A0_VBI_027_T;

/*-----------------------------------------------------------------------------
		0xc8000d6cL vbi_028 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl5                      : 32;  // 31: 0     
} O18A0_VBI_028_T;

/*-----------------------------------------------------------------------------
		0xc8000d70L vbi_029 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl6                      : 32;  // 31: 0     
} O18A0_VBI_029_T;

/*-----------------------------------------------------------------------------
		0xc8000d74L vbi_030 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl7                      : 32;  // 31: 0     
} O18A0_VBI_030_T;

/*-----------------------------------------------------------------------------
		0xc8000d78L vbi_031 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl8                      : 32;  // 31: 0     
} O18A0_VBI_031_T;

/*-----------------------------------------------------------------------------
		0xc8000d7cL vbi_032 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl9                      : 32;  // 31: 0     
} O18A0_VBI_032_T;

/*-----------------------------------------------------------------------------
		0xc8000d80L vbi_033 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl10                     : 32;  // 31: 0     
} O18A0_VBI_033_T;

/*-----------------------------------------------------------------------------
		0xc8000d84L vbi_034 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl11                     : 32;  // 31: 0     
} O18A0_VBI_034_T;

/*-----------------------------------------------------------------------------
		0xc8000d88L vbi_035 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl12                     : 32;  // 31: 0     
} O18A0_VBI_035_T;

/*-----------------------------------------------------------------------------
		0xc8000d8cL vbi_036 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl13                     : 32;  // 31: 0     
} O18A0_VBI_036_T;

/*-----------------------------------------------------------------------------
		0xc8000d90L vbi_037 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl14                     : 32;  // 31: 0     
} O18A0_VBI_037_T;

/*-----------------------------------------------------------------------------
		0xc8000d94L vbi_038 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_ctrl15                     : 32;  // 31: 0     
} O18A0_VBI_038_T;

/*-----------------------------------------------------------------------------
		0xc8000d98L vbi_039 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure0                    : 32;  // 31: 0     
} O18A0_VBI_039_T;

/*-----------------------------------------------------------------------------
		0xc8000d9cL vbi_040 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure1                    : 32;  // 31: 0     
} O18A0_VBI_040_T;

/*-----------------------------------------------------------------------------
		0xc8000da0L vbi_041 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure_out0                : 32;  // 31: 0     
} O18A0_VBI_041_T;

/*-----------------------------------------------------------------------------
		0xc8000da4L vbi_042 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure_out1                : 32;  // 31: 0     
} O18A0_VBI_042_T;

/*-----------------------------------------------------------------------------
		0xc8000da8L vbi_043 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure_out2                : 32;  // 31: 0     
} O18A0_VBI_043_T;

/*-----------------------------------------------------------------------------
		0xc8000dacL vbi_044 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cc_measure_out3                : 32;  // 31: 0     
} O18A0_VBI_044_T;

/*-----------------------------------------------------------------------------
		0xc8000db0L agc_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sw_dgain                       : 12;  // 11: 0     
	UINT32 reg_sw_dgain_field_mode            : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_sw_dgain_on                    : 1 ;  //    16     
} O18A0_AGC_001_T;

/*-----------------------------------------------------------------------------
		0xc8000db4L lvl_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl0                : 32;  // 31: 0     
} O18A0_LVL_001_T;

/*-----------------------------------------------------------------------------
		0xc8000db8L lvl_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl1                : 32;  // 31: 0     
} O18A0_LVL_002_T;

/*-----------------------------------------------------------------------------
		0xc8000dbcL lvl_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl2                : 32;  // 31: 0     
} O18A0_LVL_003_T;

/*-----------------------------------------------------------------------------
		0xc8000dc0L lvl_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl3                : 32;  // 31: 0     
} O18A0_LVL_004_T;

/*-----------------------------------------------------------------------------
		0xc8000dc4L lvl_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl4                : 32;  // 31: 0     
} O18A0_LVL_005_T;

/*-----------------------------------------------------------------------------
		0xc8000dc8L lvl_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl5                : 32;  // 31: 0     
} O18A0_LVL_006_T;

/*-----------------------------------------------------------------------------
		0xc8000dccL lvl_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl6                : 32;  // 31: 0     
} O18A0_LVL_007_T;

/*-----------------------------------------------------------------------------
		0xc8000dd0L lvl_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl7                : 32;  // 31: 0     
} O18A0_LVL_008_T;

/*-----------------------------------------------------------------------------
		0xc8000dd4L lvl_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_ycsep_lvl_ctrl8                : 32;  // 31: 0     
} O18A0_LVL_009_T;

/*-----------------------------------------------------------------------------
		0xc8000dd8L lvl_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl0              : 32;  // 31: 0     
} O18A0_LVL_010_T;

/*-----------------------------------------------------------------------------
		0xc8000ddcL lvl_011 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl1              : 32;  // 31: 0     
} O18A0_LVL_011_T;

/*-----------------------------------------------------------------------------
		0xc8000de0L lvl_012 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl2              : 32;  // 31: 0     
} O18A0_LVL_012_T;

/*-----------------------------------------------------------------------------
		0xc8000de4L lvl_013 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl3              : 32;  // 31: 0     
} O18A0_LVL_013_T;

/*-----------------------------------------------------------------------------
		0xc8000de8L lvl_014 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl4              : 32;  // 31: 0     
} O18A0_LVL_014_T;

/*-----------------------------------------------------------------------------
		0xc8000decL lvl_015 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl5              : 32;  // 31: 0     
} O18A0_LVL_015_T;

/*-----------------------------------------------------------------------------
		0xc8000df0L lvl_016 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl6              : 32;  // 31: 0     
} O18A0_LVL_016_T;

/*-----------------------------------------------------------------------------
		0xc8000df4L lvl_017 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl7              : 32;  // 31: 0     
} O18A0_LVL_017_T;

/*-----------------------------------------------------------------------------
		0xc8000df8L lvl_018 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl8              : 32;  // 31: 0     
} O18A0_LVL_018_T;

/*-----------------------------------------------------------------------------
		0xc8000dfcL lvl_019 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl9              : 32;  // 31: 0     
} O18A0_LVL_019_T;

/*-----------------------------------------------------------------------------
		0xc8000e00L lvl_020 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl10             : 32;  // 31: 0     
} O18A0_LVL_020_T;

/*-----------------------------------------------------------------------------
		0xc8000e04L lvl_021 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_status_ycsep_lvl11             : 32;  // 31: 0     
} O18A0_LVL_021_T;

/*-----------------------------------------------------------------------------
		0xc8000e08L iris_mif_gmau_mon_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf2_pel_cnt                   : 12;  // 11: 0     
	UINT32 ro_rbuf2_empty                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_rbuf1_pel_cnt                   : 12;  // 27:16     
	UINT32 ro_rbuf1_empty                     : 1 ;  //    28     
} O18A0_IRIS_MIF_GMAU_MON_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e0cL iris_mif_gmau_mon_002 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf4_pel_cnt                   : 12;  // 11: 0     
	UINT32 ro_rbuf4_empty                     : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_rbuf3_pel_cnt                   : 12;  // 27:16     
	UINT32 ro_rbuf3_empty                     : 1 ;  //    28     
} O18A0_IRIS_MIF_GMAU_MON_002_T;

/*-----------------------------------------------------------------------------
		0xc8000e10L iris_mif_gmau_mon_003 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_word_cnt                   : 7 ;  //  6: 0     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 ro_wbuf_empty                      : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 ro_wbuf_full                       : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_gmau_write_state                : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 ro_gmau_read_state                 : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 ro_gmau_cmd_state                  : 3 ;  // 26:24     
	UINT32                                    : 1 ;  //    27     reserved
	UINT32 ro_rbuf_empty                      : 1 ;  //    28     
} O18A0_IRIS_MIF_GMAU_MON_003_T;

/*-----------------------------------------------------------------------------
		0xc8000e14L iris_mif_gmau_mon_004 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_read_req_cnt_mx_lvl        : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 ro_wbuf_read_req_cnt               : 6 ;  //  9: 4     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 ro_read0_svid_cnt_mx_lvl           : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_read0_svid_cnt                  : 10;  // 25:16     
} O18A0_IRIS_MIF_GMAU_MON_004_T;

/*-----------------------------------------------------------------------------
		0xc8000e18L iris_mif_gmau_mon_005 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf1_pel_cnt_md                : 12;  // 11: 0     
	UINT32 ro_rbuf1_empty_md                  : 1 ;  //    12     
} O18A0_IRIS_MIF_GMAU_MON_005_T;

/*-----------------------------------------------------------------------------
		0xc8000e1cL iris_mif_gmau_mon_006 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_word_cnt_md                : 7 ;  //  6: 0     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 ro_wbuf_empty_md                   : 1 ;  //     8     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 ro_wbuf_full_md                    : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_gmau_write_state_md             : 2 ;  // 17:16     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 ro_gmau_read_state_md              : 1 ;  //    20     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 ro_gmau_cmd_state_md               : 3 ;  // 26:24     
} O18A0_IRIS_MIF_GMAU_MON_006_T;

/*-----------------------------------------------------------------------------
		0xc8000e20L iris_mif_gmau_mon_007 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_read_req_cnt_mx_lvl_md     : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 ro_wbuf_read_req_cnt_md            : 6 ;  //  9: 4     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 ro_read0_svid_cnt_mx_lvl_md        : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_read0_svid_cnt_md               : 10;  // 25:16     
} O18A0_IRIS_MIF_GMAU_MON_007_T;

/*-----------------------------------------------------------------------------
		0xc8000e24L iris_mif_gmau_mon_008 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_que_write_req_head_gmau         : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 ro_que_write_req_tail              : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 ro_que_read0_rbuf_num_head         : 5 ;  // 12: 8     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 ro_que_read0_rbuf_num_tail         : 5 ;  // 20:16     
	UINT32                                    : 3 ;  // 23:21     reserved
	UINT32 ro_que_read0_rbuf_num_head_gmau    : 5 ;  // 28:24     
} O18A0_IRIS_MIF_GMAU_MON_008_T;

/*-----------------------------------------------------------------------------
		0xc8000e28L iris_mif_gmau_mon_009 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_write_sdata_cnt                 : 5 ;  //  4: 0     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 ro_read0_sdata_cnt                 : 5 ;  // 12: 8     
} O18A0_IRIS_MIF_GMAU_MON_009_T;

/*-----------------------------------------------------------------------------
		0xc8000e2cL iris_mif_gmau_mon_010 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_que_write_req_head_gmau_md      : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 ro_que_write_req_tail_md           : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 ro_que_read0_rbuf_num_head_md      : 4 ;  // 11: 8     
	UINT32 ro_que_read0_rbuf_num_tail_md      : 4 ;  // 15:12     
	UINT32 ro_que_read0_rbuf_num_head_gmau_md : 4 ;  // 19:16     
} O18A0_IRIS_MIF_GMAU_MON_010_T;

/*-----------------------------------------------------------------------------
		0xc8000e30L iris_mif_gmau_mon_011 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_write_sdata_cnt_md              : 5 ;  //  4: 0     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 ro_read0_sdata_cnt_md              : 5 ;  // 12: 8     
} O18A0_IRIS_MIF_GMAU_MON_011_T;

/*-----------------------------------------------------------------------------
		0xc8000e34L iris_mif_gmau_mon_012 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_end_cmd_y                       : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_end_cmd_x                       : 11;  // 22:12     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cmd_load                       : 1 ;  //    24     
} O18A0_IRIS_MIF_GMAU_MON_012_T;

/*-----------------------------------------------------------------------------
		0xc8000e38L iris_mif_gmau_mon_013 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_cmd_y                      : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_wbuf_cmd_x                      : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_013_T;

/*-----------------------------------------------------------------------------
		0xc8000e3cL iris_mif_gmau_mon_014 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf1_cmd_y                     : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_rbuf1_cmd_x                     : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_014_T;

/*-----------------------------------------------------------------------------
		0xc8000e40L iris_mif_gmau_mon_015 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf2_cmd_y                     : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_rbuf2_cmd_x                     : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_015_T;

/*-----------------------------------------------------------------------------
		0xc8000e44L iris_mif_gmau_mon_016 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf3_cmd_y                     : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_rbuf3_cmd_x                     : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_016_T;

/*-----------------------------------------------------------------------------
		0xc8000e48L iris_mif_gmau_mon_017 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf4_cmd_y                     : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_rbuf4_cmd_x                     : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_017_T;

/*-----------------------------------------------------------------------------
		0xc8000e4cL iris_mif_gmau_mon_018 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_end_cmd_y_md                    : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_end_cmd_x_md                    : 11;  // 22:12     
	UINT32                                    : 1 ;  //    23     reserved
	UINT32 reg_cmd_load_md                    : 1 ;  //    24     
} O18A0_IRIS_MIF_GMAU_MON_018_T;

/*-----------------------------------------------------------------------------
		0xc8000e50L iris_mif_gmau_mon_019 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_wbuf_cmd_y_md                   : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_wbuf_cmd_x_md                   : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_019_T;

/*-----------------------------------------------------------------------------
		0xc8000e54L iris_mif_gmau_mon_020 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_rbuf1_cmd_y_md                  : 11;  // 10: 0     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 ro_rbuf1_cmd_x_md                  : 11;  // 22:12     
} O18A0_IRIS_MIF_GMAU_MON_020_T;

/*-----------------------------------------------------------------------------
		0xc8000e58L iris_hif_ctrl0_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_pending_enable                 : 1 ;  //     0     
	UINT32                                    : 3 ;  //  3: 1     reserved
	UINT32 reg_pready_old                     : 1 ;  //     4     
} O18A0_IRIS_HIF_CTRL0_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e5cL iris_hif_ctrl1_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_cv_timer_ctrl                  : 9 ;  //  8: 0     
} O18A0_IRIS_HIF_CTRL1_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e60L iris_mif_vbi_ma_mon_00_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_vbi_maddr_latch_line           : 5 ;  //  4: 0     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 reg_vbi_maddr_latch_sel            : 3 ;  // 10: 8     
} O18A0_IRIS_MIF_VBI_MA_MON_00_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e64L iris_mif_vbi_ma_mon_01_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld0                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_01_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e68L iris_mif_vbi_ma_mon_02_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld1                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_02_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e6cL iris_mif_vbi_ma_mon_03_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld2                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_03_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e70L iris_mif_vbi_ma_mon_04_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld3                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_04_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e74L iris_mif_vbi_ma_mon_05_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld4                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_05_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e78L iris_mif_vbi_ma_mon_06_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld5                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_06_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e7cL iris_mif_vbi_ma_mon_07_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld6                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_07_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e80L iris_mif_vbi_ma_mon_08_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ro_vbi_maddr_fld7                  : 32;  // 31: 0     
} O18A0_IRIS_MIF_VBI_MA_MON_08_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e84L iris_gmau_cmd_qos_ctrl0_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_qos_urgent                : 8 ;  //  7: 0     
	UINT32 reg_gmau_qos_start_mode            : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_gmau_qos_mode                  : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_gmau_qos_en                    : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_gmau_qos_start_line            : 4 ;  // 23:20     
} O18A0_IRIS_GMAU_CMD_QOS_CTRL0_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e88L iris_gmau_cmd_qos_ref0_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_qos_period_value          : 16;  // 15: 0     
	UINT32 reg_gmau_qos_check_timer           : 16;  // 31:16     
} O18A0_IRIS_GMAU_CMD_QOS_REF0_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e8cL iris_gmau_cmd_qos_ctrl1_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_md_qos_urgent             : 8 ;  //  7: 0     
	UINT32 reg_gmau_md_qos_start_mode         : 2 ;  //  9: 8     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 reg_gmau_md_qos_mode               : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 reg_gmau_md_qos_en                 : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 reg_gmau_md_qos_start_line         : 4 ;  // 23:20     
} O18A0_IRIS_GMAU_CMD_QOS_CTRL1_001_T;

/*-----------------------------------------------------------------------------
		0xc8000e90L iris_gmau_cmd_qos_ref1_001 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_gmau_md_qos_period_value       : 16;  // 15: 0     
	UINT32 reg_gmau_md_qos_check_timer        : 16;  // 31:16     
} O18A0_IRIS_GMAU_CMD_QOS_REF1_001_T;

typedef struct {
	O18A0_CVD_INTR1_ENABLE0_T          	cvd_intr1_enable0;            //0xc8000600L
	O18A0_CVD_INTR1_INTR0_T            	cvd_intr1_intr0;              //0xc8000604L
	O18A0_CVD_INTR1_CLEAR0_T           	cvd_intr1_clear0;             //0xc8000608L
	O18A0_CVD_INTR1_ENABLE1_T          	cvd_intr1_enable1;            //0xc800060cL
	O18A0_CVD_INTR1_INTR1_T            	cvd_intr1_intr1;              //0xc8000610L
	O18A0_CVD_INTR1_CLEAR1_T           	cvd_intr1_clear1;             //0xc8000614L
	O18A0_CVD_INTR2_ENABLE0_T          	cvd_intr2_enable0;            //0xc8000618L
	O18A0_CVD_INTR2_INTR0_T            	cvd_intr2_intr0;              //0xc800061cL
	O18A0_CVD_INTR2_CLEAR0_T           	cvd_intr2_clear0;             //0xc8000620L
	O18A0_CVD_INTR2_ENABLE1_T          	cvd_intr2_enable1;            //0xc8000624L
	O18A0_CVD_INTR2_INTR1_T            	cvd_intr2_intr1;              //0xc8000628L
	O18A0_CVD_INTR2_CLEAR1_T           	cvd_intr2_clear1;             //0xc800062cL
	O18A0_TOP_001_T                    	top_001;                      //0xc8000630L
	UINT32                             	reserved00[3];                //0xc8000634L~0xc800063cL
	O18A0_IRIS_MIF_GMAU_001_T          	iris_mif_gmau_001;            //0xc8000640L
	O18A0_IRIS_MIF_GMAU_002_T          	iris_mif_gmau_002;            //0xc8000644L
	O18A0_IRIS_MIF_GMAU_003_T          	iris_mif_gmau_003;            //0xc8000648L
	O18A0_IRIS_MIF_GMAU_004_T          	iris_mif_gmau_004;            //0xc800064cL
	O18A0_IRIS_MIF_GMAU_005_T          	iris_mif_gmau_005;            //0xc8000650L
	O18A0_IRIS_MIF_GMAU_006_T          	iris_mif_gmau_006;            //0xc8000654L
	O18A0_IRIS_MIF_GMAU_007_T          	iris_mif_gmau_007;            //0xc8000658L
	O18A0_IRIS_MIF_GMAU_008_T          	iris_mif_gmau_008;            //0xc800065cL
	O18A0_IRIS_MIF_GMAU_009_T          	iris_mif_gmau_009;            //0xc8000660L
	O18A0_IRIS_MIF_GMAU_010_T          	iris_mif_gmau_010;            //0xc8000664L
	O18A0_FASTBLANK_001_T              	fastblank_001;                //0xc8000668L
	O18A0_FASTBLANK_002_T              	fastblank_002;                //0xc800066cL
	O18A0_FASTBLANK_003_T              	fastblank_003;                //0xc8000670L
	O18A0_FASTBLANK_004_T              	fastblank_004;                //0xc8000674L
	O18A0_FASTBLANK_005_T              	fastblank_005;                //0xc8000678L
	O18A0_FASTBLANK_006_T              	fastblank_006;                //0xc800067cL
	O18A0_FASTBLANK_007_T              	fastblank_007;                //0xc8000680L
	O18A0_FASTBLANK_008_T              	fastblank_008;                //0xc8000684L
	O18A0_FASTBLANK_009_T              	fastblank_009;                //0xc8000688L
	O18A0_FASTBLANK_010_T              	fastblank_010;                //0xc800068cL
	O18A0_IRIS_DE_CTRL_001_T           	iris_de_ctrl_001;             //0xc8000690L
	O18A0_VBI_CTRL_001_T               	vbi_ctrl_001;                 //0xc8000694L
	O18A0_VBI_CTRL_002_T               	vbi_ctrl_002;                 //0xc8000698L
	O18A0_VBI_CTRL_003_T               	vbi_ctrl_003;                 //0xc800069cL
	O18A0_VBI_CTRL_004_T               	vbi_ctrl_004;                 //0xc80006a0L
	O18A0_VBI_CTRL_005_T               	vbi_ctrl_005;                 //0xc80006a4L
	O18A0_VBI_CTRL_006_T               	vbi_ctrl_006;                 //0xc80006a8L
	O18A0_VBI_CTRL_007_T               	vbi_ctrl_007;                 //0xc80006acL
	O18A0_VBI_CTRL_008_T               	vbi_ctrl_008;                 //0xc80006b0L
	O18A0_VBI_CTRL_009_T               	vbi_ctrl_009;                 //0xc80006b4L
	O18A0_VBI_CTRL_010_T               	vbi_ctrl_010;                 //0xc80006b8L
	UINT32                             	reserved01;                   //0xc80006bcL
	O18A0_FAST_BLANK_STATUS_001_T      	fast_blank_status_001;        //0xc80006c0L
	O18A0_CVBSAFE_001_T                	cvbsafe_001;                  //0xc80006c4L
	O18A0_IRIS_MIF_GMAU_MD_001_T       	iris_mif_gmau_md_001;         //0xc80006c8L
	O18A0_IRIS_MIF_GMAU_MD_002_T       	iris_mif_gmau_md_002;         //0xc80006ccL
	O18A0_IRIS_MIF_GMAU_MD_003_T       	iris_mif_gmau_md_003;         //0xc80006d0L
	O18A0_IRIS_MIF_GMAU_MD_004_T       	iris_mif_gmau_md_004;         //0xc80006d4L
	O18A0_IRIS_MIF_GMAU_MD_005_T       	iris_mif_gmau_md_005;         //0xc80006d8L
	O18A0_IRIS_MIF_GMAU_MD_006_T       	iris_mif_gmau_md_006;         //0xc80006dcL
	O18A0_IRIS_MIF_GMAU_MD_007_T       	iris_mif_gmau_md_007;         //0xc80006e0L
	O18A0_IRIS_MIF_GMAU_MD_008_T       	iris_mif_gmau_md_008;         //0xc80006e4L
	O18A0_IRIS_MIF_GMAU_MD_009_T       	iris_mif_gmau_md_009;         //0xc80006e8L
	O18A0_IRIS_MIF_GMAU_MD_010_T       	iris_mif_gmau_md_010;         //0xc80006ecL
	O18A0_IRIS_MIF_GMAU_MD_011_T       	iris_mif_gmau_md_011;         //0xc80006f0L
	O18A0_IRIS_MIF_GMAU_MD_012_T       	iris_mif_gmau_md_012;         //0xc80006f4L
	O18A0_IRIS_MIF_GMAU_MD_013_T       	iris_mif_gmau_md_013;         //0xc80006f8L
	UINT32                             	reserved02;                   //0xc80006fcL
	O18A0_IRIS_001_T                   	iris_001;                     //0xc8000700L
	O18A0_IRIS_002_T                   	iris_002;                     //0xc8000704L
	O18A0_IRIS_003_T                   	iris_003;                     //0xc8000708L
	O18A0_IRIS_004_T                   	iris_004;                     //0xc800070cL
	O18A0_IRIS_005_T                   	iris_005;                     //0xc8000710L
	O18A0_IRIS_006_T                   	iris_006;                     //0xc8000714L
	O18A0_IRIS_007_T                   	iris_007;                     //0xc8000718L
	O18A0_IRIS_008_T                   	iris_008;                     //0xc800071cL
	O18A0_IRIS_009_T                   	iris_009;                     //0xc8000720L
	O18A0_IRIS_010_T                   	iris_010;                     //0xc8000724L
	O18A0_IRIS_011_T                   	iris_011;                     //0xc8000728L
	UINT32                             	reserved03;                   //0xc800072cL
	O18A0_IRIS_012_T                   	iris_012;                     //0xc8000730L
	O18A0_IRIS_013_T                   	iris_013;                     //0xc8000734L
	O18A0_IRIS_014_T                   	iris_014;                     //0xc8000738L
	O18A0_IRIS_015_T                   	iris_015;                     //0xc800073cL
	O18A0_IRIS_016_T                   	iris_016;                     //0xc8000740L
	O18A0_IRIS_017_T                   	iris_017;                     //0xc8000744L
	O18A0_IRIS_018_T                   	iris_018;                     //0xc8000748L
	O18A0_IRIS_019_T                   	iris_019;                     //0xc800074cL
	O18A0_IRIS_020_T                   	iris_020;                     //0xc8000750L
	O18A0_IRIS_021_T                   	iris_021;                     //0xc8000754L
	O18A0_IRIS_022_T                   	iris_022;                     //0xc8000758L
	O18A0_IRIS_023_T                   	iris_023;                     //0xc800075cL
	O18A0_IRIS_024_T                   	iris_024;                     //0xc8000760L
	O18A0_IRIS_025_T                   	iris_025;                     //0xc8000764L
	O18A0_IRIS_026_T                   	iris_026;                     //0xc8000768L
	O18A0_IRIS_027_T                   	iris_027;                     //0xc800076cL
	O18A0_IRIS_028_T                   	iris_028;                     //0xc8000770L
	O18A0_IRIS_029_T                   	iris_029;                     //0xc8000774L
	O18A0_IRIS_030_T                   	iris_030;                     //0xc8000778L
	O18A0_IRIS_031_T                   	iris_031;                     //0xc800077cL
	O18A0_IRIS_032_T                   	iris_032;                     //0xc8000780L
	O18A0_IRIS_033_T                   	iris_033;                     //0xc8000784L
	O18A0_IRIS_034_T                   	iris_034;                     //0xc8000788L
	O18A0_IRIS_035_T                   	iris_035;                     //0xc800078cL
	O18A0_IRIS_036_T                   	iris_036;                     //0xc8000790L
	O18A0_IRIS_037_T                   	iris_037;                     //0xc8000794L
	O18A0_IRIS_038_T                   	iris_038;                     //0xc8000798L
	O18A0_IRIS_039_T                   	iris_039;                     //0xc800079cL
	O18A0_IRIS_040_T                   	iris_040;                     //0xc80007a0L
	O18A0_IRIS_041_T                   	iris_041;                     //0xc80007a4L
	O18A0_IRIS_042_T                   	iris_042;                     //0xc80007a8L
	O18A0_IRIS_043_T                   	iris_043;                     //0xc80007acL
	O18A0_IRIS_044_T                   	iris_044;                     //0xc80007b0L
	O18A0_IRIS_045_T                   	iris_045;                     //0xc80007b4L
	O18A0_IRIS_046_T                   	iris_046;                     //0xc80007b8L
	O18A0_IRIS_047_T                   	iris_047;                     //0xc80007bcL
	O18A0_IRIS_048_T                   	iris_048;                     //0xc80007c0L
	O18A0_IRIS_049_T                   	iris_049;                     //0xc80007c4L
	O18A0_IRIS_050_T                   	iris_050;                     //0xc80007c8L
	O18A0_IRIS_051_T                   	iris_051;                     //0xc80007ccL
	O18A0_IRIS_052_T                   	iris_052;                     //0xc80007d0L
	O18A0_IRIS_053_T                   	iris_053;                     //0xc80007d4L
	O18A0_IRIS_054_T                   	iris_054;                     //0xc80007d8L
	O18A0_IRIS_055_T                   	iris_055;                     //0xc80007dcL
	O18A0_IRIS_056_T                   	iris_056;                     //0xc80007e0L
	O18A0_IRIS_057_T                   	iris_057;                     //0xc80007e4L
	O18A0_IRIS_058_T                   	iris_058;                     //0xc80007e8L
	O18A0_IRIS_059_T                   	iris_059;                     //0xc80007ecL
	O18A0_IRIS_060_T                   	iris_060;                     //0xc80007f0L
	O18A0_IRIS_061_T                   	iris_061;                     //0xc80007f4L
	O18A0_IRIS_062_T                   	iris_062;                     //0xc80007f8L
	O18A0_IRIS_063_T                   	iris_063;                     //0xc80007fcL
	O18A0_IRIS_064_T                   	iris_064;                     //0xc8000800L
	O18A0_IRIS_065_T                   	iris_065;                     //0xc8000804L
	O18A0_IRIS_066_T                   	iris_066;                     //0xc8000808L
	O18A0_IRIS_067_T                   	iris_067;                     //0xc800080cL
	O18A0_IRIS_068_T                   	iris_068;                     //0xc8000810L
	O18A0_IRIS_069_T                   	iris_069;                     //0xc8000814L
	O18A0_IRIS_070_T                   	iris_070;                     //0xc8000818L
	O18A0_IRIS_071_T                   	iris_071;                     //0xc800081cL
	O18A0_IRIS_072_T                   	iris_072;                     //0xc8000820L
	O18A0_IRIS_073_T                   	iris_073;                     //0xc8000824L
	O18A0_IRIS_074_T                   	iris_074;                     //0xc8000828L
	O18A0_IRIS_075_T                   	iris_075;                     //0xc800082cL
	O18A0_IRIS_076_T                   	iris_076;                     //0xc8000830L
	O18A0_IRIS_077_T                   	iris_077;                     //0xc8000834L
	O18A0_IRIS_078_T                   	iris_078;                     //0xc8000838L
	O18A0_IRIS_079_T                   	iris_079;                     //0xc800083cL
	O18A0_IRIS_080_T                   	iris_080;                     //0xc8000840L
	O18A0_IRIS_081_T                   	iris_081;                     //0xc8000844L
	O18A0_IRIS_082_T                   	iris_082;                     //0xc8000848L
	O18A0_IRIS_083_T                   	iris_083;                     //0xc800084cL
	O18A0_IRIS_084_T                   	iris_084;                     //0xc8000850L
	O18A0_IRIS_085_T                   	iris_085;                     //0xc8000854L
	O18A0_IRIS_086_T                   	iris_086;                     //0xc8000858L
	O18A0_IRIS_087_T                   	iris_087;                     //0xc800085cL
	O18A0_IRIS_088_T                   	iris_088;                     //0xc8000860L
	O18A0_IRIS_089_T                   	iris_089;                     //0xc8000864L
	O18A0_IRIS_090_T                   	iris_090;                     //0xc8000868L
	O18A0_IRIS_091_T                   	iris_091;                     //0xc800086cL
	O18A0_IRIS_092_T                   	iris_092;                     //0xc8000870L
	O18A0_IRIS_093_T                   	iris_093;                     //0xc8000874L
	O18A0_IRIS_094_T                   	iris_094;                     //0xc8000878L
	O18A0_IRIS_095_T                   	iris_095;                     //0xc800087cL
	O18A0_IRIS_096_T                   	iris_096;                     //0xc8000880L
	O18A0_IRIS_097_T                   	iris_097;                     //0xc8000884L
	O18A0_IRIS_098_T                   	iris_098;                     //0xc8000888L
	O18A0_IRIS_099_T                   	iris_099;                     //0xc800088cL
	O18A0_IRIS_100_T                   	iris_100;                     //0xc8000890L
	O18A0_IRIS_101_T                   	iris_101;                     //0xc8000894L
	O18A0_IRIS_102_T                   	iris_102;                     //0xc8000898L
	O18A0_IRIS_103_T                   	iris_103;                     //0xc800089cL
	O18A0_IRIS_104_T                   	iris_104;                     //0xc80008a0L
	O18A0_IRIS_105_T                   	iris_105;                     //0xc80008a4L
	O18A0_IRIS_106_T                   	iris_106;                     //0xc80008a8L
	O18A0_IRIS_107_T                   	iris_107;                     //0xc80008acL
	O18A0_IRIS_108_T                   	iris_108;                     //0xc80008b0L
	O18A0_IRIS_109_T                   	iris_109;                     //0xc80008b4L
	O18A0_IRIS_110_T                   	iris_110;                     //0xc80008b8L
	O18A0_IRIS_111_T                   	iris_111;                     //0xc80008bcL
	O18A0_IRIS_112_T                   	iris_112;                     //0xc80008c0L
	O18A0_IRIS_113_T                   	iris_113;                     //0xc80008c4L
	O18A0_IRIS_114_T                   	iris_114;                     //0xc80008c8L
	O18A0_IRIS_115_T                   	iris_115;                     //0xc80008ccL
	O18A0_IRIS_116_T                   	iris_116;                     //0xc80008d0L
	O18A0_IRIS_117_T                   	iris_117;                     //0xc80008d4L
	O18A0_IRIS_118_T                   	iris_118;                     //0xc80008d8L
	O18A0_IRIS_119_T                   	iris_119;                     //0xc80008dcL
	O18A0_IRIS_120_T                   	iris_120;                     //0xc80008e0L
	O18A0_IRIS_121_T                   	iris_121;                     //0xc80008e4L
	O18A0_IRIS_122_T                   	iris_122;                     //0xc80008e8L
	O18A0_IRIS_123_T                   	iris_123;                     //0xc80008ecL
	O18A0_IRIS_124_T                   	iris_124;                     //0xc80008f0L
	O18A0_IRIS_125_T                   	iris_125;                     //0xc80008f4L
	O18A0_IRIS_126_T                   	iris_126;                     //0xc80008f8L
	O18A0_IRIS_127_T                   	iris_127;                     //0xc80008fcL
	O18A0_IRIS_128_T                   	iris_128;                     //0xc8000900L
	O18A0_IRIS_129_T                   	iris_129;                     //0xc8000904L
	O18A0_IRIS_130_T                   	iris_130;                     //0xc8000908L
	O18A0_IRIS_131_T                   	iris_131;                     //0xc800090cL
	O18A0_IRIS_132_T                   	iris_132;                     //0xc8000910L
	O18A0_IRIS_133_T                   	iris_133;                     //0xc8000914L
	O18A0_IRIS_134_T                   	iris_134;                     //0xc8000918L
	O18A0_IRIS_135_T                   	iris_135;                     //0xc800091cL
	O18A0_IRIS_136_T                   	iris_136;                     //0xc8000920L
	O18A0_IRIS_137_T                   	iris_137;                     //0xc8000924L
	O18A0_IRIS_138_T                   	iris_138;                     //0xc8000928L
	O18A0_IRIS_139_T                   	iris_139;                     //0xc800092cL
	O18A0_IRIS_140_T                   	iris_140;                     //0xc8000930L
	O18A0_IRIS_141_T                   	iris_141;                     //0xc8000934L
	O18A0_IRIS_142_T                   	iris_142;                     //0xc8000938L
	O18A0_IRIS_143_T                   	iris_143;                     //0xc800093cL
	O18A0_IRIS_144_T                   	iris_144;                     //0xc8000940L
	O18A0_IRIS_145_T                   	iris_145;                     //0xc8000944L
	O18A0_IRIS_146_T                   	iris_146;                     //0xc8000948L
	O18A0_IRIS_147_T                   	iris_147;                     //0xc800094cL
	O18A0_IRIS_148_T                   	iris_148;                     //0xc8000950L
	O18A0_IRIS_149_T                   	iris_149;                     //0xc8000954L
	O18A0_IRIS_150_T                   	iris_150;                     //0xc8000958L
	O18A0_IRIS_151_T                   	iris_151;                     //0xc800095cL
	O18A0_IRIS_152_T                   	iris_152;                     //0xc8000960L
	O18A0_IRIS_153_T                   	iris_153;                     //0xc8000964L
	O18A0_IRIS_154_T                   	iris_154;                     //0xc8000968L
	O18A0_IRIS_155_T                   	iris_155;                     //0xc800096cL
	O18A0_IRIS_156_T                   	iris_156;                     //0xc8000970L
	O18A0_IRIS_157_T                   	iris_157;                     //0xc8000974L
	O18A0_IRIS_158_T                   	iris_158;                     //0xc8000978L
	O18A0_IRIS_159_T                   	iris_159;                     //0xc800097cL
	O18A0_IRIS_160_T                   	iris_160;                     //0xc8000980L
	O18A0_IRIS_161_T                   	iris_161;                     //0xc8000984L
	O18A0_IRIS_162_T                   	iris_162;                     //0xc8000988L
	O18A0_IRIS_163_T                   	iris_163;                     //0xc800098cL
	O18A0_IRIS_164_T                   	iris_164;                     //0xc8000990L
	O18A0_IRIS_165_T                   	iris_165;                     //0xc8000994L
	O18A0_IRIS_166_T                   	iris_166;                     //0xc8000998L
	O18A0_IRIS_167_T                   	iris_167;                     //0xc800099cL
	O18A0_IRIS_168_T                   	iris_168;                     //0xc80009a0L
	O18A0_IRIS_169_T                   	iris_169;                     //0xc80009a4L
	O18A0_IRIS_170_T                   	iris_170;                     //0xc80009a8L
	O18A0_IRIS_171_T                   	iris_171;                     //0xc80009acL
	O18A0_IRIS_172_T                   	iris_172;                     //0xc80009b0L
	O18A0_IRIS_173_T                   	iris_173;                     //0xc80009b4L
	O18A0_IRIS_174_T                   	iris_174;                     //0xc80009b8L
	O18A0_IRIS_175_T                   	iris_175;                     //0xc80009bcL
	O18A0_IRIS_176_T                   	iris_176;                     //0xc80009c0L
	O18A0_IRIS_177_T                   	iris_177;                     //0xc80009c4L
	O18A0_IRIS_178_T                   	iris_178;                     //0xc80009c8L
	O18A0_IRIS_179_T                   	iris_179;                     //0xc80009ccL
	O18A0_IRIS_180_T                   	iris_180;                     //0xc80009d0L
	O18A0_IRIS_181_T                   	iris_181;                     //0xc80009d4L
	O18A0_IRIS_182_T                   	iris_182;                     //0xc80009d8L
	O18A0_IRIS_183_T                   	iris_183;                     //0xc80009dcL
	O18A0_IRIS_184_T                   	iris_184;                     //0xc80009e0L
	O18A0_IRIS_185_T                   	iris_185;                     //0xc80009e4L
	O18A0_IRIS_186_T                   	iris_186;                     //0xc80009e8L
	O18A0_IRIS_187_T                   	iris_187;                     //0xc80009ecL
	O18A0_IRIS_188_T                   	iris_188;                     //0xc80009f0L
	O18A0_IRIS_189_T                   	iris_189;                     //0xc80009f4L
	O18A0_IRIS_190_T                   	iris_190;                     //0xc80009f8L
	O18A0_IRIS_191_T                   	iris_191;                     //0xc80009fcL
	O18A0_IRIS_192_T                   	iris_192;                     //0xc8000a00L
	O18A0_IRIS_193_T                   	iris_193;                     //0xc8000a04L
	O18A0_IRIS_194_T                   	iris_194;                     //0xc8000a08L
	O18A0_IRIS_195_T                   	iris_195;                     //0xc8000a0cL
	O18A0_IRIS_196_T                   	iris_196;                     //0xc8000a10L
	O18A0_IRIS_197_T                   	iris_197;                     //0xc8000a14L
	O18A0_IRIS_198_T                   	iris_198;                     //0xc8000a18L
	O18A0_IRIS_199_T                   	iris_199;                     //0xc8000a1cL
	O18A0_IRIS_200_T                   	iris_200;                     //0xc8000a20L
	O18A0_IRIS_201_T                   	iris_201;                     //0xc8000a24L
	O18A0_IRIS_202_T                   	iris_202;                     //0xc8000a28L
	O18A0_IRIS_203_T                   	iris_203;                     //0xc8000a2cL
	O18A0_IRIS_204_T                   	iris_204;                     //0xc8000a30L
	O18A0_IRIS_205_T                   	iris_205;                     //0xc8000a34L
	O18A0_IRIS_206_T                   	iris_206;                     //0xc8000a38L
	O18A0_IRIS_207_T                   	iris_207;                     //0xc8000a3cL
	O18A0_IRIS_208_T                   	iris_208;                     //0xc8000a40L
	O18A0_IRIS_209_T                   	iris_209;                     //0xc8000a44L
	O18A0_IRIS_210_T                   	iris_210;                     //0xc8000a48L
	O18A0_IRIS_211_T                   	iris_211;                     //0xc8000a4cL
	O18A0_IRIS_212_T                   	iris_212;                     //0xc8000a50L
	O18A0_IRIS_213_T                   	iris_213;                     //0xc8000a54L
	O18A0_IRIS_214_T                   	iris_214;                     //0xc8000a58L
	O18A0_IRIS_215_T                   	iris_215;                     //0xc8000a5cL
	O18A0_IRIS_216_T                   	iris_216;                     //0xc8000a60L
	O18A0_IRIS_217_T                   	iris_217;                     //0xc8000a64L
	O18A0_IRIS_218_T                   	iris_218;                     //0xc8000a68L
	O18A0_IRIS_219_T                   	iris_219;                     //0xc8000a6cL
	O18A0_IRIS_220_T                   	iris_220;                     //0xc8000a70L
	O18A0_IRIS_221_T                   	iris_221;                     //0xc8000a74L
	O18A0_IRIS_222_T                   	iris_222;                     //0xc8000a78L
	O18A0_IRIS_223_T                   	iris_223;                     //0xc8000a7cL
	O18A0_IRIS_224_T                   	iris_224;                     //0xc8000a80L
	O18A0_IRIS_225_T                   	iris_225;                     //0xc8000a84L
	O18A0_IRIS_226_T                   	iris_226;                     //0xc8000a88L
	O18A0_IRIS_227_T                   	iris_227;                     //0xc8000a8cL
	O18A0_IRIS_228_T                   	iris_228;                     //0xc8000a90L
	O18A0_IRIS_229_T                   	iris_229;                     //0xc8000a94L
	O18A0_IRIS_230_T                   	iris_230;                     //0xc8000a98L
	O18A0_IRIS_231_T                   	iris_231;                     //0xc8000a9cL
	O18A0_IRIS_232_T                   	iris_232;                     //0xc8000aa0L
	O18A0_IRIS_233_T                   	iris_233;                     //0xc8000aa4L
	O18A0_IRIS_234_T                   	iris_234;                     //0xc8000aa8L
	O18A0_IRIS_235_T                   	iris_235;                     //0xc8000aacL
	O18A0_IRIS_236_T                   	iris_236;                     //0xc8000ab0L
	O18A0_IRIS_237_T                   	iris_237;                     //0xc8000ab4L
	O18A0_IRIS_238_T                   	iris_238;                     //0xc8000ab8L
	O18A0_IRIS_239_T                   	iris_239;                     //0xc8000abcL
	O18A0_IRIS_240_T                   	iris_240;                     //0xc8000ac0L
	O18A0_IRIS_241_T                   	iris_241;                     //0xc8000ac4L
	O18A0_IRIS_242_T                   	iris_242;                     //0xc8000ac8L
	O18A0_IRIS_243_T                   	iris_243;                     //0xc8000accL
	O18A0_IRIS_244_T                   	iris_244;                     //0xc8000ad0L
	O18A0_IRIS_245_T                   	iris_245;                     //0xc8000ad4L
	O18A0_IRIS_246_T                   	iris_246;                     //0xc8000ad8L
	O18A0_IRIS_247_T                   	iris_247;                     //0xc8000adcL
	O18A0_IRIS_248_T                   	iris_248;                     //0xc8000ae0L
	O18A0_IRIS_249_T                   	iris_249;                     //0xc8000ae4L
	O18A0_IRIS_250_T                   	iris_250;                     //0xc8000ae8L
	O18A0_IRIS_251_T                   	iris_251;                     //0xc8000aecL
	O18A0_IRIS_252_T                   	iris_252;                     //0xc8000af0L
	O18A0_IRIS_253_T                   	iris_253;                     //0xc8000af4L
	O18A0_IRIS_254_T                   	iris_254;                     //0xc8000af8L
	O18A0_IRIS_255_T                   	iris_255;                     //0xc8000afcL
	O18A0_IRIS_256_T                   	iris_256;                     //0xc8000b00L
	O18A0_IRIS_257_T                   	iris_257;                     //0xc8000b04L
	O18A0_IRIS_258_T                   	iris_258;                     //0xc8000b08L
	O18A0_IRIS_259_T                   	iris_259;                     //0xc8000b0cL
	O18A0_IRIS_260_T                   	iris_260;                     //0xc8000b10L
	O18A0_IRIS_261_T                   	iris_261;                     //0xc8000b14L
	O18A0_IRIS_262_T                   	iris_262;                     //0xc8000b18L
	O18A0_IRIS_263_T                   	iris_263;                     //0xc8000b1cL
	O18A0_IRIS_264_T                   	iris_264;                     //0xc8000b20L
	O18A0_IRIS_265_T                   	iris_265;                     //0xc8000b24L
	UINT32                             	reserved04[2];                //0xc8000b28L~0xc8000b2cL
	O18A0_IRIS_266_T                   	iris_266;                     //0xc8000b30L
	O18A0_IRIS_267_T                   	iris_267;                     //0xc8000b34L
	O18A0_IRIS_268_T                   	iris_268;                     //0xc8000b38L
	O18A0_IRIS_269_T                   	iris_269;                     //0xc8000b3cL
	O18A0_IRIS_270_T                   	iris_270;                     //0xc8000b40L
	O18A0_IRIS_271_T                   	iris_271;                     //0xc8000b44L
	O18A0_IRIS_272_T                   	iris_272;                     //0xc8000b48L
	O18A0_IRIS_273_T                   	iris_273;                     //0xc8000b4cL
	O18A0_IRIS_274_T                   	iris_274;                     //0xc8000b50L
	O18A0_IRIS_275_T                   	iris_275;                     //0xc8000b54L
	O18A0_IRIS_276_T                   	iris_276;                     //0xc8000b58L
	O18A0_IRIS_277_T                   	iris_277;                     //0xc8000b5cL
	O18A0_IRIS_278_T                   	iris_278;                     //0xc8000b60L
	O18A0_IRIS_279_T                   	iris_279;                     //0xc8000b64L
	O18A0_IRIS_280_T                   	iris_280;                     //0xc8000b68L
	O18A0_IRIS_281_T                   	iris_281;                     //0xc8000b6cL
	O18A0_IRIS_282_T                   	iris_282;                     //0xc8000b70L
	O18A0_IRIS_283_T                   	iris_283;                     //0xc8000b74L
	O18A0_IRIS_284_T                   	iris_284;                     //0xc8000b78L
	O18A0_IRIS_285_T                   	iris_285;                     //0xc8000b7cL
	O18A0_IRIS_286_T                   	iris_286;                     //0xc8000b80L
	O18A0_IRIS_287_T                   	iris_287;                     //0xc8000b84L
	O18A0_IRIS_288_T                   	iris_288;                     //0xc8000b88L
	O18A0_IRIS_289_T                   	iris_289;                     //0xc8000b8cL
	O18A0_IRIS_290_T                   	iris_290;                     //0xc8000b90L
	O18A0_IRIS_291_T                   	iris_291;                     //0xc8000b94L
	O18A0_IRIS_292_T                   	iris_292;                     //0xc8000b98L
	O18A0_IRIS_293_T                   	iris_293;                     //0xc8000b9cL
	O18A0_IRIS_294_T                   	iris_294;                     //0xc8000ba0L
	O18A0_IRIS_295_T                   	iris_295;                     //0xc8000ba4L
	O18A0_IRIS_296_T                   	iris_296;                     //0xc8000ba8L
	O18A0_IRIS_297_T                   	iris_297;                     //0xc8000bacL
	O18A0_IRIS_298_T                   	iris_298;                     //0xc8000bb0L
	O18A0_IRIS_299_T                   	iris_299;                     //0xc8000bb4L
	O18A0_IRIS_300_T                   	iris_300;                     //0xc8000bb8L
	O18A0_IRIS_301_T                   	iris_301;                     //0xc8000bbcL
	O18A0_IRIS_302_T                   	iris_302;                     //0xc8000bc0L
	O18A0_IRIS_303_T                   	iris_303;                     //0xc8000bc4L
	O18A0_IRIS_304_T                   	iris_304;                     //0xc8000bc8L
	O18A0_IRIS_305_T                   	iris_305;                     //0xc8000bccL
	O18A0_IRIS_306_T                   	iris_306;                     //0xc8000bd0L
	O18A0_IRIS_307_T                   	iris_307;                     //0xc8000bd4L
	O18A0_IRIS_308_T                   	iris_308;                     //0xc8000bd8L
	O18A0_IRIS_309_T                   	iris_309;                     //0xc8000bdcL
	O18A0_IRIS_310_T                   	iris_310;                     //0xc8000be0L
	O18A0_IRIS_311_T                   	iris_311;                     //0xc8000be4L
	O18A0_IRIS_312_T                   	iris_312;                     //0xc8000be8L
	O18A0_IRIS_313_T                   	iris_313;                     //0xc8000becL
	O18A0_IRIS_314_T                   	iris_314;                     //0xc8000bf0L
	O18A0_IRIS_315_T                   	iris_315;                     //0xc8000bf4L
	O18A0_IRIS_316_T                   	iris_316;                     //0xc8000bf8L
	O18A0_IRIS_317_T                   	iris_317;                     //0xc8000bfcL
	O18A0_IRIS_318_T                   	iris_318;                     //0xc8000c00L
	O18A0_IRIS_319_T                   	iris_319;                     //0xc8000c04L
	O18A0_IRIS_320_T                   	iris_320;                     //0xc8000c08L
	O18A0_IRIS_321_T                   	iris_321;                     //0xc8000c0cL
	O18A0_IRIS_322_T                   	iris_322;                     //0xc8000c10L
	O18A0_IRIS_323_T                   	iris_323;                     //0xc8000c14L
	O18A0_IRIS_324_T                   	iris_324;                     //0xc8000c18L
	O18A0_IRIS_325_T                   	iris_325;                     //0xc8000c1cL
	O18A0_IRIS_326_T                   	iris_326;                     //0xc8000c20L
	O18A0_IRIS_327_T                   	iris_327;                     //0xc8000c24L
	O18A0_IRIS_328_T                   	iris_328;                     //0xc8000c28L
	O18A0_IRIS_329_T                   	iris_329;                     //0xc8000c2cL
	O18A0_IRIS_330_T                   	iris_330;                     //0xc8000c30L
	O18A0_IRIS_331_T                   	iris_331;                     //0xc8000c34L
	O18A0_IRIS_332_T                   	iris_332;                     //0xc8000c38L
	O18A0_IRIS_333_T                   	iris_333;                     //0xc8000c3cL
	O18A0_IRIS_334_T                   	iris_334;                     //0xc8000c40L
	O18A0_IRIS_335_T                   	iris_335;                     //0xc8000c44L
	O18A0_IRIS_336_T                   	iris_336;                     //0xc8000c48L
	O18A0_IRIS_337_T                   	iris_337;                     //0xc8000c4cL
	O18A0_IRIS_338_T                   	iris_338;                     //0xc8000c50L
	O18A0_IRIS_339_T                   	iris_339;                     //0xc8000c54L
	O18A0_IRIS_340_T                   	iris_340;                     //0xc8000c58L
	O18A0_IRIS_341_T                   	iris_341;                     //0xc8000c5cL
	O18A0_IRIS_342_T                   	iris_342;                     //0xc8000c60L
	O18A0_IRIS_343_T                   	iris_343;                     //0xc8000c64L
	O18A0_IRIS_344_T                   	iris_344;                     //0xc8000c68L
	O18A0_IRIS_345_T                   	iris_345;                     //0xc8000c6cL
	O18A0_IRIS_346_T                   	iris_346;                     //0xc8000c70L
	O18A0_IRIS_347_T                   	iris_347;                     //0xc8000c74L
	O18A0_IRIS_348_T                   	iris_348;                     //0xc8000c78L
	O18A0_IRIS_349_T                   	iris_349;                     //0xc8000c7cL
	O18A0_IRIS_350_T                   	iris_350;                     //0xc8000c80L
	O18A0_IRIS_351_T                   	iris_351;                     //0xc8000c84L
	O18A0_IRIS_352_T                   	iris_352;                     //0xc8000c88L
	O18A0_IRIS_353_T                   	iris_353;                     //0xc8000c8cL
	O18A0_IRIS_354_T                   	iris_354;                     //0xc8000c90L
	O18A0_IRIS_355_T                   	iris_355;                     //0xc8000c94L
	O18A0_IRIS_356_T                   	iris_356;                     //0xc8000c98L
	O18A0_IRIS_357_T                   	iris_357;                     //0xc8000c9cL
	O18A0_IRIS_358_T                   	iris_358;                     //0xc8000ca0L
	O18A0_IRIS_359_T                   	iris_359;                     //0xc8000ca4L
	O18A0_IRIS_360_T                   	iris_360;                     //0xc8000ca8L
	O18A0_IRIS_361_T                   	iris_361;                     //0xc8000cacL
	O18A0_IRIS_362_T                   	iris_362;                     //0xc8000cb0L
	O18A0_IRIS_363_T                   	iris_363;                     //0xc8000cb4L
	O18A0_IRIS_364_T                   	iris_364;                     //0xc8000cb8L
	O18A0_IRIS_365_T                   	iris_365;                     //0xc8000cbcL
	O18A0_IRIS_366_T                   	iris_366;                     //0xc8000cc0L
	O18A0_IRIS_367_T                   	iris_367;                     //0xc8000cc4L
	O18A0_IRIS_368_T                   	iris_368;                     //0xc8000cc8L
	O18A0_IRIS_369_T                   	iris_369;                     //0xc8000cccL
	O18A0_IRIS_370_T                   	iris_370;                     //0xc8000cd0L
	O18A0_IRIS_371_T                   	iris_371;                     //0xc8000cd4L
	O18A0_IRIS_372_T                   	iris_372;                     //0xc8000cd8L
	O18A0_IRIS_373_T                   	iris_373;                     //0xc8000cdcL
	O18A0_IRIS_374_T                   	iris_374;                     //0xc8000ce0L
	O18A0_IRIS_375_T                   	iris_375;                     //0xc8000ce4L
	UINT32                             	reserved05[6];                //0xc8000ce8L~0xc8000cfcL
	O18A0_VBI_001_T                    	vbi_001;                      //0xc8000d00L
	O18A0_VBI_002_T                    	vbi_002;                      //0xc8000d04L
	O18A0_VBI_003_T                    	vbi_003;                      //0xc8000d08L
	O18A0_VBI_004_T                    	vbi_004;                      //0xc8000d0cL
	O18A0_VBI_005_T                    	vbi_005;                      //0xc8000d10L
	O18A0_VBI_006_T                    	vbi_006;                      //0xc8000d14L
	O18A0_VBI_007_T                    	vbi_007;                      //0xc8000d18L
	O18A0_VBI_008_T                    	vbi_008;                      //0xc8000d1cL
	O18A0_VBI_009_T                    	vbi_009;                      //0xc8000d20L
	O18A0_VBI_010_T                    	vbi_010;                      //0xc8000d24L
	O18A0_VBI_011_T                    	vbi_011;                      //0xc8000d28L
	O18A0_VBI_012_T                    	vbi_012;                      //0xc8000d2cL
	O18A0_VBI_013_T                    	vbi_013;                      //0xc8000d30L
	O18A0_VBI_014_T                    	vbi_014;                      //0xc8000d34L
	O18A0_VBI_015_T                    	vbi_015;                      //0xc8000d38L
	O18A0_VBI_016_T                    	vbi_016;                      //0xc8000d3cL
	O18A0_VBI_017_T                    	vbi_017;                      //0xc8000d40L
	O18A0_VBI_018_T                    	vbi_018;                      //0xc8000d44L
	O18A0_VBI_019_T                    	vbi_019;                      //0xc8000d48L
	O18A0_VBI_020_T                    	vbi_020;                      //0xc8000d4cL
	O18A0_VBI_021_T                    	vbi_021;                      //0xc8000d50L
	O18A0_VBI_022_T                    	vbi_022;                      //0xc8000d54L
	O18A0_VBI_023_T                    	vbi_023;                      //0xc8000d58L
	O18A0_VBI_024_T                    	vbi_024;                      //0xc8000d5cL
	O18A0_VBI_025_T                    	vbi_025;                      //0xc8000d60L
	O18A0_VBI_026_T                    	vbi_026;                      //0xc8000d64L
	O18A0_VBI_027_T                    	vbi_027;                      //0xc8000d68L
	O18A0_VBI_028_T                    	vbi_028;                      //0xc8000d6cL
	O18A0_VBI_029_T                    	vbi_029;                      //0xc8000d70L
	O18A0_VBI_030_T                    	vbi_030;                      //0xc8000d74L
	O18A0_VBI_031_T                    	vbi_031;                      //0xc8000d78L
	O18A0_VBI_032_T                    	vbi_032;                      //0xc8000d7cL
	O18A0_VBI_033_T                    	vbi_033;                      //0xc8000d80L
	O18A0_VBI_034_T                    	vbi_034;                      //0xc8000d84L
	O18A0_VBI_035_T                    	vbi_035;                      //0xc8000d88L
	O18A0_VBI_036_T                    	vbi_036;                      //0xc8000d8cL
	O18A0_VBI_037_T                    	vbi_037;                      //0xc8000d90L
	O18A0_VBI_038_T                    	vbi_038;                      //0xc8000d94L
	O18A0_VBI_039_T                    	vbi_039;                      //0xc8000d98L
	O18A0_VBI_040_T                    	vbi_040;                      //0xc8000d9cL
	O18A0_VBI_041_T                    	vbi_041;                      //0xc8000da0L
	O18A0_VBI_042_T                    	vbi_042;                      //0xc8000da4L
	O18A0_VBI_043_T                    	vbi_043;                      //0xc8000da8L
	O18A0_VBI_044_T                    	vbi_044;                      //0xc8000dacL
	O18A0_AGC_001_T                    	agc_001;                      //0xc8000db0L
	O18A0_LVL_001_T                    	lvl_001;                      //0xc8000db4L
	O18A0_LVL_002_T                    	lvl_002;                      //0xc8000db8L
	O18A0_LVL_003_T                    	lvl_003;                      //0xc8000dbcL
	O18A0_LVL_004_T                    	lvl_004;                      //0xc8000dc0L
	O18A0_LVL_005_T                    	lvl_005;                      //0xc8000dc4L
	O18A0_LVL_006_T                    	lvl_006;                      //0xc8000dc8L
	O18A0_LVL_007_T                    	lvl_007;                      //0xc8000dccL
	O18A0_LVL_008_T                    	lvl_008;                      //0xc8000dd0L
	O18A0_LVL_009_T                    	lvl_009;                      //0xc8000dd4L
	O18A0_LVL_010_T                    	lvl_010;                      //0xc8000dd8L
	O18A0_LVL_011_T                    	lvl_011;                      //0xc8000ddcL
	O18A0_LVL_012_T                    	lvl_012;                      //0xc8000de0L
	O18A0_LVL_013_T                    	lvl_013;                      //0xc8000de4L
	O18A0_LVL_014_T                    	lvl_014;                      //0xc8000de8L
	O18A0_LVL_015_T                    	lvl_015;                      //0xc8000decL
	O18A0_LVL_016_T                    	lvl_016;                      //0xc8000df0L
	O18A0_LVL_017_T                    	lvl_017;                      //0xc8000df4L
	O18A0_LVL_018_T                    	lvl_018;                      //0xc8000df8L
	O18A0_LVL_019_T                    	lvl_019;                      //0xc8000dfcL
	O18A0_LVL_020_T                    	lvl_020;                      //0xc8000e00L
	O18A0_LVL_021_T                    	lvl_021;                      //0xc8000e04L
	O18A0_IRIS_MIF_GMAU_MON_001_T      	iris_mif_gmau_mon_001;        //0xc8000e08L
	O18A0_IRIS_MIF_GMAU_MON_002_T      	iris_mif_gmau_mon_002;        //0xc8000e0cL
	O18A0_IRIS_MIF_GMAU_MON_003_T      	iris_mif_gmau_mon_003;        //0xc8000e10L
	O18A0_IRIS_MIF_GMAU_MON_004_T      	iris_mif_gmau_mon_004;        //0xc8000e14L
	O18A0_IRIS_MIF_GMAU_MON_005_T      	iris_mif_gmau_mon_005;        //0xc8000e18L
	O18A0_IRIS_MIF_GMAU_MON_006_T      	iris_mif_gmau_mon_006;        //0xc8000e1cL
	O18A0_IRIS_MIF_GMAU_MON_007_T      	iris_mif_gmau_mon_007;        //0xc8000e20L
	O18A0_IRIS_MIF_GMAU_MON_008_T      	iris_mif_gmau_mon_008;        //0xc8000e24L
	O18A0_IRIS_MIF_GMAU_MON_009_T      	iris_mif_gmau_mon_009;        //0xc8000e28L
	O18A0_IRIS_MIF_GMAU_MON_010_T      	iris_mif_gmau_mon_010;        //0xc8000e2cL
	O18A0_IRIS_MIF_GMAU_MON_011_T      	iris_mif_gmau_mon_011;        //0xc8000e30L
	O18A0_IRIS_MIF_GMAU_MON_012_T      	iris_mif_gmau_mon_012;        //0xc8000e34L
	O18A0_IRIS_MIF_GMAU_MON_013_T      	iris_mif_gmau_mon_013;        //0xc8000e38L
	O18A0_IRIS_MIF_GMAU_MON_014_T      	iris_mif_gmau_mon_014;        //0xc8000e3cL
	O18A0_IRIS_MIF_GMAU_MON_015_T      	iris_mif_gmau_mon_015;        //0xc8000e40L
	O18A0_IRIS_MIF_GMAU_MON_016_T      	iris_mif_gmau_mon_016;        //0xc8000e44L
	O18A0_IRIS_MIF_GMAU_MON_017_T      	iris_mif_gmau_mon_017;        //0xc8000e48L
	O18A0_IRIS_MIF_GMAU_MON_018_T      	iris_mif_gmau_mon_018;        //0xc8000e4cL
	O18A0_IRIS_MIF_GMAU_MON_019_T      	iris_mif_gmau_mon_019;        //0xc8000e50L
	O18A0_IRIS_MIF_GMAU_MON_020_T      	iris_mif_gmau_mon_020;        //0xc8000e54L
	O18A0_IRIS_HIF_CTRL0_001_T         	iris_hif_ctrl0_001;           //0xc8000e58L
	O18A0_IRIS_HIF_CTRL1_001_T         	iris_hif_ctrl1_001;           //0xc8000e5cL
	O18A0_IRIS_MIF_VBI_MA_MON_00_001_T 	iris_mif_vbi_ma_mon_00_001;   //0xc8000e60L
	O18A0_IRIS_MIF_VBI_MA_MON_01_001_T 	iris_mif_vbi_ma_mon_01_001;   //0xc8000e64L
	O18A0_IRIS_MIF_VBI_MA_MON_02_001_T 	iris_mif_vbi_ma_mon_02_001;   //0xc8000e68L
	O18A0_IRIS_MIF_VBI_MA_MON_03_001_T 	iris_mif_vbi_ma_mon_03_001;   //0xc8000e6cL
	O18A0_IRIS_MIF_VBI_MA_MON_04_001_T 	iris_mif_vbi_ma_mon_04_001;   //0xc8000e70L
	O18A0_IRIS_MIF_VBI_MA_MON_05_001_T 	iris_mif_vbi_ma_mon_05_001;   //0xc8000e74L
	O18A0_IRIS_MIF_VBI_MA_MON_06_001_T 	iris_mif_vbi_ma_mon_06_001;   //0xc8000e78L
	O18A0_IRIS_MIF_VBI_MA_MON_07_001_T 	iris_mif_vbi_ma_mon_07_001;   //0xc8000e7cL
	O18A0_IRIS_MIF_VBI_MA_MON_08_001_T 	iris_mif_vbi_ma_mon_08_001;   //0xc8000e80L
	O18A0_IRIS_GMAU_CMD_QOS_CTRL0_001_T	iris_gmau_cmd_qos_ctrl0_001;  //0xc8000e84L
	O18A0_IRIS_GMAU_CMD_QOS_REF0_001_T 	iris_gmau_cmd_qos_ref0_001;   //0xc8000e88L
	O18A0_IRIS_GMAU_CMD_QOS_CTRL1_001_T	iris_gmau_cmd_qos_ctrl1_001;  //0xc8000e8cL
	O18A0_IRIS_GMAU_CMD_QOS_REF1_001_T 	iris_gmau_cmd_qos_ref1_001;   //0xc8000e90L
}DE_CVD_REG_O18A0_T;

#endif
