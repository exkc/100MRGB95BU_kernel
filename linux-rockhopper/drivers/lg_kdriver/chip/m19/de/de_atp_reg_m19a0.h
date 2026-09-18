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

#ifndef _ATP_REG_M19A0_H_
#define _ATP_REG_M19A0_H_

/*-----------------------------------------------------------------------------
		0xc8006600L ttx_ver_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_ovs                            : 8 ;  //  7: 0     
	UINT32 ttx_ove                            : 8 ;  // 15: 8     
	UINT32 ttx_evs                            : 8 ;  // 23:16     
	UINT32 ttx_eve                            : 8 ;  // 31:24     
} M19A0_TTX_VER_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xc8006604L ttx_ver_ctrl1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_ovs8                           : 1 ;  //     0     
	UINT32 ttx_ove8                           : 1 ;  //     1     
	UINT32 ttx_evs8                           : 1 ;  //     2     
	UINT32 ttx_eve8                           : 1 ;  //     3     
	UINT32 ttx_iter_cnt                       : 3 ;  //  6: 4     
	UINT32 ttx_adj                            : 1 ;  //     7     
	UINT32 ttx_err                            : 4 ;  // 11: 8     
	UINT32                                    : 2 ;  // 13:12     reserved
	UINT32 ttx_line                           : 18;  // 31:14     
} M19A0_TTX_VER_CTRL1_T;

/*-----------------------------------------------------------------------------
		0xc8006608L wss_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_hs                             : 11;  // 10: 0     
	UINT32 comp_c_delay                       : 5 ;  // 15:11     
	UINT32 wss_data                           : 14;  // 29:16     
	UINT32 comp_y_lpf                         : 1 ;  //    30     
} M19A0_WSS_DATA_T;

/*-----------------------------------------------------------------------------
		0xc800660cL cgms_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cgms_enc_data                      : 20;  // 19: 0     
	UINT32 secam_burst_blank_end              : 8 ;  // 27:20     
	UINT32 secam_preem_scaling                : 3 ;  // 30:28     
} M19A0_CGMS_DATA_T;

/*-----------------------------------------------------------------------------
		0xc8006610L cve_config ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 standard                           : 3 ;  //  2: 0     
	UINT32 enc_en                             : 1 ;  //     3     
	UINT32 color_bar_en                       : 1 ;  //     4     
	UINT32 c_filter                           : 2 ;  //  6: 5     
	UINT32 color_on                           : 1 ;  //     7     
	UINT32 y_filter                           : 2 ;  //  9: 8     
	UINT32 y_delay                            : 2 ;  // 11:10     
	UINT32 ttx_sys                            : 3 ;  // 14:12     
	UINT32 video_interface_sel                : 1 ;  //    15     
	UINT32 burst_amp                          : 8 ;  // 23:16     
	UINT32 secam_y_delay                      : 5 ;  // 28:24     
	UINT32 offset                             : 2 ;  // 30:29     
	UINT32 invert                             : 1 ;  //    31     
} M19A0_CVE_CONFIG_T;

/*-----------------------------------------------------------------------------
		0xc8006614L phase_incr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_incr                         : 32;  // 31: 0     
} M19A0_PHASE_INCR_T;

/*-----------------------------------------------------------------------------
		0xc8006618L denc_vbi_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset                       : 8 ;  //  7: 0     
	UINT32 secam_subcarrier_scaling           : 6 ;  // 13: 8     
	UINT32 secam_c_gain                       : 2 ;  // 15:14     
	UINT32 cc1_en                             : 1 ;  //    16     
	UINT32 cc2_en                             : 1 ;  //    17     
	UINT32 cc1_full                           : 1 ;  //    18     
	UINT32 cc2_full                           : 1 ;  //    19     
	UINT32 cgms_en                            : 1 ;  //    20     
	UINT32 wss_en                             : 1 ;  //    21     
	UINT32 reserved                           : 1 ;  //    22     
	UINT32 fm_reset_on                        : 1 ;  //    23     
	UINT32 fm_reset_initial                   : 1 ;  //    24     
	UINT32 burst_phase_reset_strt             : 5 ;  // 29:25     
	UINT32 comp_c_gain                        : 2 ;  // 31:30     
} M19A0_DENC_VBI_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc800661cL cc_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cc_data_f1                         : 16;  // 15: 0     
	UINT32 cc_data_f2                         : 16;  // 31:16     
} M19A0_CC_DATA_T;

/*-----------------------------------------------------------------------------
		0xc8006620L mv_n0_3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_n0                              : 6 ;  //  5: 0     
	UINT32                                    : 2 ;  //  7: 6     reserved
	UINT32 mv_n2                              : 6 ;  // 13: 8     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 mv_n1                              : 6 ;  // 21:16     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 mv_n3                              : 6 ;  // 29:24     
} M19A0_MV_N0_3_T;

/*-----------------------------------------------------------------------------
		0xc8006624L mv_n4_9 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_n4                              : 6 ;  //  5: 0     
	UINT32 mv_n22                             : 1 ;  //     6     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 mv_n8                              : 6 ;  // 13: 8     
	UINT32                                    : 2 ;  // 15:14     reserved
	UINT32 mv_n7                              : 2 ;  // 17:16     
	UINT32 mv_n6                              : 3 ;  // 20:18     
	UINT32 mv_n5                              : 3 ;  // 23:21     
	UINT32 mv_n9                              : 6 ;  // 29:24     
} M19A0_MV_N4_9_T;

/*-----------------------------------------------------------------------------
		0xc8006628L mv_n10_11 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_n10                             : 6 ;  //  5: 0     
	UINT32 mv_n21                             : 10;  // 15: 6     
	UINT32 mv_n11                             : 15;  // 30:16     
} M19A0_MV_N10_11_T;

/*-----------------------------------------------------------------------------
		0xc800662cL mv_n12_14 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_n12                             : 15;  // 14: 0     
	UINT32                                    : 1 ;  //    15     reserved
	UINT32 mv_n14                             : 8 ;  // 23:16     
	UINT32 mv_n13                             : 8 ;  // 31:24     
} M19A0_MV_N12_14_T;

/*-----------------------------------------------------------------------------
		0xc8006630L mv_n15_20 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mv_n15                             : 8 ;  //  7: 0     
	UINT32                                    : 8 ;  // 15: 8     reserved
	UINT32 mv_n20                             : 3 ;  // 18:16     
	UINT32 mv_n16                             : 1 ;  //    19     
	UINT32 mv_n19                             : 4 ;  // 23:20     
	UINT32 mv_n18                             : 4 ;  // 27:24     
	UINT32 mv_n17                             : 4 ;  // 31:28     
} M19A0_MV_N15_20_T;

/*-----------------------------------------------------------------------------
		0xc8006634L vps_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 index                              : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 lpf_bypass                         : 1 ;  //     4     
	UINT32 vbi_odd                            : 1 ;  //     5     
	UINT32 vbi_even                           : 1 ;  //     6     
	UINT32 vps_enable                         : 1 ;  //     7     
	UINT32 vps_wr_done                        : 1 ;  //     8     
	UINT32 c_data_delay                       : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 wss_odd_en                         : 1 ;  //    12     
	UINT32 wss_even_en                        : 1 ;  //    13     
	UINT32 v_pol                              : 1 ;  //    14     
	UINT32 h_pol                              : 1 ;  //    15     
	UINT32 vps_data                           : 16;  // 31:16     
} M19A0_VPS_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8006638L ttx_data ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_data                           : 32;  // 31: 0     
} M19A0_TTX_DATA_T;

/*-----------------------------------------------------------------------------
		0xc800663cL ttx_load ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_load                           : 1 ;  //     0     
	UINT32                                    : 7 ;  //  7: 1     reserved
	UINT32 ttx_write_addr                     : 8 ;  // 15: 8     
	UINT32 ttx_data_endian                    : 1 ;  //    16     
	UINT32 ttx_data_bit_order                 : 1 ;  //    17     
	UINT32 cve_clk_count                      : 12;  // 29:18     
	UINT32 cve_clk_valid                      : 1 ;  //    30     
} M19A0_TTX_LOAD_T;

/*-----------------------------------------------------------------------------
		0xc8006650L ttx_ddru ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 ttx_ddru_stride                    : 11;  // 10: 0     
	UINT32                                    : 5 ;  // 15:11     reserved
	UINT32 ttx_ddru_line_count                : 8 ;  // 23:16     
	UINT32                                    : 6 ;  // 29:24     reserved
	UINT32 ttx_ddru_endian_change             : 1 ;  //    30     
	UINT32 ttx_ddru_update_enable             : 1 ;  //    31     
} M19A0_TTX_DDRU_T;

/*-----------------------------------------------------------------------------
		0xc8006680L addr_dbg ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 interlaced_mode                    : 1 ;  //     0     
	UINT32 msb_sel                            : 1 ;  //     1     
	UINT32 output_disable                     : 1 ;  //     2     
	UINT32 fd_output_disable                  : 1 ;  //     3     
	UINT32 top_field                          : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 y_delay                            : 3 ;  // 10: 8     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 c_delay                            : 3 ;  // 14:12     
	UINT32 reg_load                           : 1 ;  //    15     
	UINT32 pic_init_field                     : 4 ;  // 19:16     
	UINT32 vfal_field                         : 4 ;  // 23:20     
	UINT32 cvbs_field                         : 4 ;  // 27:24     
	UINT32 timeout_cnt                        : 4 ;  // 31:28     
} M19A0_ADDR_DBG_T;

/*-----------------------------------------------------------------------------
		0xc8006684L a_top_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 y_status                           : 10;  //  9: 0     
	UINT32                                    : 6 ;  // 15:10     reserved
	UINT32 c_status                           : 10;  // 25:16     
} M19A0_A_TOP_STATUS_T;

typedef struct {
	M19A0_TTX_VER_CTRL0_T              	ttx_ver_ctrl0;                //0xc8006600L
	M19A0_TTX_VER_CTRL1_T              	ttx_ver_ctrl1;                //0xc8006604L
	M19A0_WSS_DATA_T                   	wss_data;                     //0xc8006608L
	M19A0_CGMS_DATA_T                  	cgms_data;                    //0xc800660cL
	M19A0_CVE_CONFIG_T                 	cve_config;                   //0xc8006610L
	M19A0_PHASE_INCR_T                 	phase_incr;                   //0xc8006614L
	M19A0_DENC_VBI_CTRL_T              	denc_vbi_ctrl;                //0xc8006618L
	M19A0_CC_DATA_T                    	cc_data;                      //0xc800661cL
	M19A0_MV_N0_3_T                    	mv_n0_3;                      //0xc8006620L
	M19A0_MV_N4_9_T                    	mv_n4_9;                      //0xc8006624L
	M19A0_MV_N10_11_T                  	mv_n10_11;                    //0xc8006628L
	M19A0_MV_N12_14_T                  	mv_n12_14;                    //0xc800662cL
	M19A0_MV_N15_20_T                  	mv_n15_20;                    //0xc8006630L
	M19A0_VPS_CTRL_T                   	vps_ctrl;                     //0xc8006634L
	M19A0_TTX_DATA_T                   	ttx_data;                     //0xc8006638L
	M19A0_TTX_LOAD_T                   	ttx_load;                     //0xc800663cL
	UINT32                             	reserved00[4];                //0xc8006640L~0xc800664cL
	M19A0_TTX_DDRU_T                   	ttx_ddru;                     //0xc8006650L
	UINT32                             	reserved01[11];               //0xc8006654L~0xc800667cL
	M19A0_ADDR_DBG_T                   	addr_dbg;                     //0xc8006680L
	M19A0_A_TOP_STATUS_T               	a_top_status;                 //0xc8006684L
} DE_ATP_REG_M19A0_T;

#endif
