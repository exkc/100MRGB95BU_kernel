#ifndef __PQE_GSC_OSD_PRE_REG_H__
#define __PQE_GSC_OSD_PRE_REG_H__

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
	0x0000 osd0_ctrl_main ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_en                          : 1,	//     0
	                                : 1,	//     1 reserved
	osd_8bit_low0_en                : 1,	//     2
	osd_10bit_mode_en               : 1,	//     3
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
} OSD_PRE_OSD0_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0004 osd0_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	base_addr                       ;   	// 31: 0
} OSD_PRE_OSD0_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x0008 osd0_ctrl_swap ''
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
} OSD_PRE_OSD0_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x000c osd0_ctrl_pdec ''
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
} OSD_PRE_OSD0_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0010 osd0_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD_PRE_OSD0_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0014 osd0_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD_PRE_OSD0_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0018 osd0_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD_PRE_OSD0_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x001c osd0_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD_PRE_OSD0_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0020 osd0_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD_PRE_OSD0_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0024 osd0_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD_PRE_OSD0_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0028 osd0_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD_PRE_OSD0_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x002c osd0_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD_PRE_OSD0_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0030 osd0_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD_PRE_OSD0_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0034 osd0_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD_PRE_OSD0_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0038 osd0_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD_PRE_OSD0_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x003c osd0_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD_PRE_OSD0_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0060 osd0_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD_PRE_OSD0_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0064 osd0_status_mon_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_cfg              : 3,	//  0: 2
	                                : 5,	//  3: 7 reserved
	reg_4k_status_sel               : 1,	//     8
	                                : 7,	//  9:15 reserved
	reg_pre_mul0_alpha_en           : 1;	//    16
} OSD_PRE_OSD0_STATUS_MON_CFG;

/*-----------------------------------------------------------------------------
	0x0068 osd0_status_mon_pos ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_ypos             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_status_mon_xpos             :12;	// 16:27
} OSD_PRE_OSD0_STATUS_MON_POS;

/*-----------------------------------------------------------------------------
	0x006c osd0_test_pgen ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	tpg_en                          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_mute_en                     : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_force_vld_en                : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_mode                        : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_mute_data_0                 : 8,	// 16:23
	reg_mute_data_1                 : 8;	// 24:31
} OSD_PRE_OSD0_TEST_PGEN;

/*-----------------------------------------------------------------------------
	0x0080 osd1_ctrl_main ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_en                          : 1,	//     0
	                                : 2,	//  1: 2 reserved
	osd_10bit_mode_en               : 1,	//     3
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
} OSD_PRE_OSD1_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0084 osd1_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	base_addr                       ;   	// 31: 0
} OSD_PRE_OSD1_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x0088 osd1_ctrl_swap ''
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
} OSD_PRE_OSD1_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x008c osd1_ctrl_pdec ''
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
} OSD_PRE_OSD1_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0090 osd1_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD_PRE_OSD1_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0094 osd1_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD_PRE_OSD1_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0098 osd1_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD_PRE_OSD1_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x009c osd1_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD_PRE_OSD1_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x00a0 osd1_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD_PRE_OSD1_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x00a4 osd1_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD_PRE_OSD1_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x00a8 osd1_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD_PRE_OSD1_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x00ac osd1_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD_PRE_OSD1_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00b0 osd1_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD_PRE_OSD1_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00b4 osd1_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD_PRE_OSD1_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00b8 osd1_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD_PRE_OSD1_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00bc osd1_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD_PRE_OSD1_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00c0 osd1_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD_PRE_OSD1_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x00c4 osd1_status_mon_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_cfg              : 3,	//  0: 2
	                                :13,	//  3:15 reserved
	reg_pre_mul1_alpha_en           : 1;	//    16
} OSD_PRE_OSD1_STATUS_MON_CFG;

/*-----------------------------------------------------------------------------
	0x00c8 osd1_status_mon_pos ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_ypos             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_status_mon_xpos             :12;	// 16:27
} OSD_PRE_OSD1_STATUS_MON_POS;

/*-----------------------------------------------------------------------------
	0x00cc osd1_test_pgen ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	tpg_en                          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_mute_en                     : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_force_vld_en                : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_mode                        : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_mute_data_0                 : 8,	// 16:23
	reg_mute_data_1                 : 8;	// 24:31
} OSD_PRE_OSD1_TEST_PGEN;

/*-----------------------------------------------------------------------------
	0x0100 osd_status_state_line ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sc_req_line_i                   :16,	//  0:15
	statecur                        :16;	// 16:31
} OSD_PRE_OSD_STATUS_STATE_LINE;

/*-----------------------------------------------------------------------------
	0x0104 osd_status_mon_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data0            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA0;

/*-----------------------------------------------------------------------------
	0x0108 osd_status_mon_data1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data1            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA1;

/*-----------------------------------------------------------------------------
	0x010c osd_status_mon_data2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data2            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA2;

/*-----------------------------------------------------------------------------
	0x0110 osd_status_mon_data3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data3            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA3;

/*-----------------------------------------------------------------------------
	0x0114 osd_status_mon_data4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data4            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA4;

/*-----------------------------------------------------------------------------
	0x0118 osd_status_mon_data5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data5            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA5;

/*-----------------------------------------------------------------------------
	0x011c osd_status_mon_data6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data6            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA6;

/*-----------------------------------------------------------------------------
	0x0120 osd_status_mon_data7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data7            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA7;

/*-----------------------------------------------------------------------------
	0x0124 osd_status_mon_data8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data8            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA8;

/*-----------------------------------------------------------------------------
	0x0128 osd_status_mon_data9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data9            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATA9;

/*-----------------------------------------------------------------------------
	0x012c osd_status_mon_dataa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_dataa            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATAA;

/*-----------------------------------------------------------------------------
	0x01c0 osd_status_mon_datab ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_datab            ;   	// 31: 0
} OSD_PRE_OSD_STATUS_MON_DATAB;

typedef struct {
	OSD_PRE_OSD0_CTRL_MAIN                  	osd0_ctrl_main                  ;	// 0x0000 : ''
	OSD_PRE_OSD0_BASE_ADDR                  	osd0_base_addr                  ;	// 0x0004 : ''
	OSD_PRE_OSD0_CTRL_SWAP                  	osd0_ctrl_swap                  ;	// 0x0008 : ''
	OSD_PRE_OSD0_CTRL_PDEC                  	osd0_ctrl_pdec                  ;	// 0x000c : ''
	OSD_PRE_OSD0_CTRL_HDR0                  	osd0_ctrl_hdr0                  ;	// 0x0010 : ''
	OSD_PRE_OSD0_CTRL_HDR1                  	osd0_ctrl_hdr1                  ;	// 0x0014 : ''
	OSD_PRE_OSD0_CTRL_HDR2                  	osd0_ctrl_hdr2                  ;	// 0x0018 : ''
	OSD_PRE_OSD0_CTRL_HDR3                  	osd0_ctrl_hdr3                  ;	// 0x001c : ''
	OSD_PRE_OSD0_CTRL_HDR4                  	osd0_ctrl_hdr4                  ;	// 0x0020 : ''
	OSD_PRE_OSD0_CTRL_HDR5                  	osd0_ctrl_hdr5                  ;	// 0x0024 : ''
	OSD_PRE_OSD0_CTRL_HDR6                  	osd0_ctrl_hdr6                  ;	// 0x0028 : ''
	OSD_PRE_OSD0_CTRL_CKEY_CTRL_0           	osd0_ctrl_ckey_ctrl_0           ;	// 0x002c : ''
	OSD_PRE_OSD0_CTRL_CKEY_CTRL_1           	osd0_ctrl_ckey_ctrl_1           ;	// 0x0030 : ''
	OSD_PRE_OSD0_CROP_CTRL_0                	osd0_crop_ctrl_0                ;	// 0x0034 : ''
	OSD_PRE_OSD0_CROP_CTRL_1                	osd0_crop_ctrl_1                ;	// 0x0038 : ''
	OSD_PRE_OSD0_CROP_CTRL_2                	osd0_crop_ctrl_2                ;	// 0x003c : ''
	UINT32                          	                         __rsvd_00[   8];	// 0x0040 ~ 0x005c
	OSD_PRE_OSD0_COMMON_DISP_SIZE           	osd0_common_disp_size           ;	// 0x0060 : ''
	OSD_PRE_OSD0_STATUS_MON_CFG             	osd0_status_mon_cfg             ;	// 0x0064 : ''
	OSD_PRE_OSD0_STATUS_MON_POS             	osd0_status_mon_pos             ;	// 0x0068 : ''
	OSD_PRE_OSD0_TEST_PGEN                  	osd0_test_pgen                  ;	// 0x006c : ''
	UINT32                          	                         __rsvd_01[   4];	// 0x0070 ~ 0x007c

	OSD_PRE_OSD1_CTRL_MAIN                  	osd1_ctrl_main                  ;	// 0x0080 : ''
	OSD_PRE_OSD1_BASE_ADDR                  	osd1_base_addr                  ;	// 0x0084 : ''
	OSD_PRE_OSD1_CTRL_SWAP                  	osd1_ctrl_swap                  ;	// 0x0088 : ''
	OSD_PRE_OSD1_CTRL_PDEC                  	osd1_ctrl_pdec                  ;	// 0x008c : ''
	OSD_PRE_OSD1_CTRL_HDR0                  	osd1_ctrl_hdr0                  ;	// 0x0090 : ''
	OSD_PRE_OSD1_CTRL_HDR1                  	osd1_ctrl_hdr1                  ;	// 0x0094 : ''
	OSD_PRE_OSD1_CTRL_HDR2                  	osd1_ctrl_hdr2                  ;	// 0x0098 : ''
	OSD_PRE_OSD1_CTRL_HDR3                  	osd1_ctrl_hdr3                  ;	// 0x009c : ''
	OSD_PRE_OSD1_CTRL_HDR4                  	osd1_ctrl_hdr4                  ;	// 0x00a0 : ''
	OSD_PRE_OSD1_CTRL_HDR5                  	osd1_ctrl_hdr5                  ;	// 0x00a4 : ''
	OSD_PRE_OSD1_CTRL_HDR6                  	osd1_ctrl_hdr6                  ;	// 0x00a8 : ''
	OSD_PRE_OSD1_CTRL_CKEY_CTRL_0           	osd1_ctrl_ckey_ctrl_0           ;	// 0x00ac : ''
	OSD_PRE_OSD1_CTRL_CKEY_CTRL_1           	osd1_ctrl_ckey_ctrl_1           ;	// 0x00b0 : ''
	OSD_PRE_OSD1_CROP_CTRL_0                	osd1_crop_ctrl_0                ;	// 0x00b4 : ''
	OSD_PRE_OSD1_CROP_CTRL_1                	osd1_crop_ctrl_1                ;	// 0x00b8 : ''
	OSD_PRE_OSD1_CROP_CTRL_2                	osd1_crop_ctrl_2                ;	// 0x00bc : ''
	OSD_PRE_OSD1_COMMON_DISP_SIZE           	osd1_common_disp_size           ;	// 0x00c0 : ''
	OSD_PRE_OSD1_STATUS_MON_CFG             	osd1_status_mon_cfg             ;	// 0x00c4 : ''
	OSD_PRE_OSD1_STATUS_MON_POS             	osd1_status_mon_pos             ;	// 0x00c8 : ''
	OSD_PRE_OSD1_TEST_PGEN                  	osd1_test_pgen                  ;	// 0x00cc : ''
	UINT32                          	                         __rsvd_02[  12];	// 0x00d0 ~ 0x00fc
	OSD_PRE_OSD_STATUS_STATE_LINE           	osd_status_state_line           ;	// 0x0100 : ''
	OSD_PRE_OSD_STATUS_MON_DATA0            	osd_status_mon_data0            ;	// 0x0104 : ''
	OSD_PRE_OSD_STATUS_MON_DATA1            	osd_status_mon_data1            ;	// 0x0108 : ''
	OSD_PRE_OSD_STATUS_MON_DATA2            	osd_status_mon_data2            ;	// 0x010c : ''
	OSD_PRE_OSD_STATUS_MON_DATA3            	osd_status_mon_data3            ;	// 0x0110 : ''
	OSD_PRE_OSD_STATUS_MON_DATA4            	osd_status_mon_data4            ;	// 0x0114 : ''
	OSD_PRE_OSD_STATUS_MON_DATA5            	osd_status_mon_data5            ;	// 0x0118 : ''
	OSD_PRE_OSD_STATUS_MON_DATA6            	osd_status_mon_data6            ;	// 0x011c : ''
	OSD_PRE_OSD_STATUS_MON_DATA7            	osd_status_mon_data7            ;	// 0x0120 : ''
	OSD_PRE_OSD_STATUS_MON_DATA8            	osd_status_mon_data8            ;	// 0x0124 : ''
	OSD_PRE_OSD_STATUS_MON_DATA9            	osd_status_mon_data9            ;	// 0x0128 : ''
	OSD_PRE_OSD_STATUS_MON_DATAA            	osd_status_mon_dataa            ;	// 0x012c : ''
	UINT32                          	                         __rsvd_03[  36];	// 0x0130 ~ 0x01bc
	OSD_PRE_OSD_STATUS_MON_DATAB            	osd_status_mon_datab            ;	// 0x01c0 : ''
} OSD_PRE_O26_REG_T;
/* 53 regs, 53 types */

/* 53 regs, 53 types in Total*/

// *INDENT-ON*

#define OSD_PRE_RdFL(_r)           ((g_osd_pre_o26_reg_shadow->_r)=(g_osd_pre_o26_reg->_r))
#define OSD_PRE_WrFL(_r)           ((g_osd_pre_o26_reg->_r)=(g_osd_pre_o26_reg_shadow->_r))

#define OSD_PRE_Rd(_r)             *((UINT32*)(&(g_osd_pre_o26_reg_shadow->_r)))
#define OSD_PRE_Wr(_r,_v)          ((OSD_PRE_Rd(_r))=((UINT32)(_v)))

#define OSD_PRE_RdBlk(_r,_v)       (*((UINT32*)(&(_v)))) = OSD_PRE_Rd(_r)
#define OSD_PRE_WrBlk(_r,_v)       (OSD_PRE_Rd(_r))=(*((UINT32*)(&(_v))))

#define OSD_PRE_Rd01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (_v01) = (g_osd_pre_o26_reg_shadow->_r._f01);  \
                                } while(0)

#define OSD_PRE_Rd02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (_v01) = (g_osd_pre_o26_reg_shadow->_r._f01);  \
                                    (_v02) = (g_osd_pre_o26_reg_shadow->_r._f02);  \
                                } while(0)

#define OSD_PRE_Wr01(_r,_f01,_v01)                                                 \
                                do {                                                    \
                                    (g_osd_pre_o26_reg_shadow->_r._f01) = (_v01);  \
                                } while(0)

#define OSD_PRE_Wr02(_r,_f01,_v01,_f02,_v02)                                       \
                                do {                                                    \
                                    (g_osd_pre_o26_reg_shadow->_r._f01) = (_v01);  \
                                    (g_osd_pre_o26_reg_shadow->_r._f02) = (_v02);  \
                                } while(0)

extern volatile OSD_PRE_O26_REG_T* g_osd_pre_o26_reg;
extern OSD_PRE_O26_REG_T*          g_osd_pre_o26_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O26-A0_PQE_GSC_reg_man_OSD_PRE.csv' 20241210 17:59:06 KST by getregs v2.9 */
