#ifndef __OSD_SCAN_REG_O18_H__
#define __OSD_SCAN_REG_O18_H__

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
	0x00c0 osd0_bitmap_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_alpha_50x50_th              : 8,	//  0: 7
	reg_pos_v_offset                : 3,	//  8:10
	                                : 1,	//    11 reserved
	reg_pos_h_offset                : 3,	// 12:14
	                                : 6,	// 15:20 reserved
	reg_gsr_rgb_sel                 : 1,	//    21
	reg_gsr_i_data_sel              : 2,	// 22:23
	reg_gsr_i_aa_th                 : 8;	// 24:31
} OSD0_BITMAP_CTRL2;

/*-----------------------------------------------------------------------------
	0x00c4 osd0_status_alpha_50x50 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	alpha_50x50_cnt                 ;   	// 31: 0
} OSD0_STATUS_ALPHA_50X50;

/*-----------------------------------------------------------------------------
	0x00c8 osd0_lsr_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_master_gain             : 8,	//  0: 7
	                                :22,	//  8:29 reserved
	reg_osd_lsr_debug_en            : 1,	//    30
	reg_osd_lsr_en                  : 1;	//    31
} OSD0_LSR_CTRL0;

/*-----------------------------------------------------------------------------
	0x00cc osd0_lsr_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_x3                      : 8,	//  0: 7
	reg_lut_x2                      : 8,	//  8:15
	reg_lut_x1                      : 8,	// 16:23
	reg_lut_x0                      : 8;	// 24:31
} OSD0_LSR_CTRL1;

/*-----------------------------------------------------------------------------
	0x00d0 osd0_lsr_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_y3                      : 8,	//  0: 7
	reg_lut_y2                      : 8,	//  8:15
	reg_lut_y1                      : 8,	// 16:23
	reg_lut_y0                      : 8;	// 24:31
} OSD0_LSR_CTRL2;

/*-----------------------------------------------------------------------------
	0x00d4 osd0_lsr_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v0_h3             : 8,	//  0: 7
	reg_lsr_alpha_v0_h2             : 8,	//  8:15
	reg_lsr_alpha_v0_h1             : 8,	// 16:23
	reg_lsr_alpha_v0_h0             : 8;	// 24:31
} OSD0_LSR_CTRL3;

/*-----------------------------------------------------------------------------
	0x00d8 osd0_lsr_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v1_h3             : 8,	//  0: 7
	reg_lsr_alpha_v1_h2             : 8,	//  8:15
	reg_lsr_alpha_v1_h1             : 8,	// 16:23
	reg_lsr_alpha_v1_h0             : 8;	// 24:31
} OSD0_LSR_CTRL4;

/*-----------------------------------------------------------------------------
	0x00dc osd0_lsr_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v2_h3             : 8,	//  0: 7
	reg_lsr_alpha_v2_h2             : 8,	//  8:15
	reg_lsr_alpha_v2_h1             : 8,	// 16:23
	reg_lsr_alpha_v2_h0             : 8;	// 24:31
} OSD0_LSR_CTRL5;

/*-----------------------------------------------------------------------------
	0x00e0 osd0_lsr_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v3_h3             : 8,	//  0: 7
	reg_lsr_alpha_v3_h2             : 8,	//  8:15
	reg_lsr_alpha_v3_h1             : 8,	// 16:23
	reg_lsr_alpha_v3_h0             : 8;	// 24:31
} OSD0_LSR_CTRL6;

/*-----------------------------------------------------------------------------
	0x00e4 osd0_out_buf_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	out_buf_status                  :16,	//  0:15
	out_buf_urgency                 : 1;	//    16
} OSD0_OUT_BUF_STATUS;

/*-----------------------------------------------------------------------------
	0x00e8 osd0_osd_shp_cg_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_osd_shp_cg_on               : 1;	//    31
} OSD0_OSD_SHP_CG_CTRL;

/*-----------------------------------------------------------------------------
	0x00ec osd0_osd_post_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD0_OSD_POST_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00f0 osd0_osd_post_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD0_OSD_POST_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00f4 osd0_osd_post_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD0_OSD_POST_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00f8 osd0_osd_post_crop_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crop_mixer_ypos                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	crop_mixer_xpos                 :13;	// 16:28
} OSD0_OSD_POST_CROP_CTRL_3;

/*-----------------------------------------------------------------------------
	0x00fc osd0_osd_gsr_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7,	//  8:14
	                                : 1,	//    15 reserved
	reg_block_no_v                  : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_block_no_v_1                : 6,	// 24:29
	                                : 1,	//    30 reserved
	reg_block_info_force_en         : 1;	//    31
} OSD0_OSD_GSR_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0100 osd0_osd_gsr_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7;	//  8:14
} OSD0_OSD_GSR_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0104 osd0_osd_gsr_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gsr_th_last                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_gsr_th                      :13;	// 16:28
} OSD0_OSD_GSR_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0108 osd0_osd_gsr_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_toggle_mode                 : 1,	//     0
	reg_mem_sel                     : 1,	//     1
	                                : 2,	//  2: 3 reserved
	reg_mem_auto_toggle_on          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_apb_data_merge              : 1;	//     8
} OSD0_OSD_GSR_CTRL_3;

/*-----------------------------------------------------------------------------
	0x010c osd0_osd_gsr_ind_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD0_OSD_GSR_IND_CTRL;

/*-----------------------------------------------------------------------------
	0x0110 osd0_osd_gsr_ind_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_gsr_ind_data                ;   	// 31: 0
} OSD0_OSD_GSR_IND_DATA;

typedef struct {
	UINT32                          	                 __rsvd_00[  48];	// 0x0000 ~ 0x00bc
	OSD0_BITMAP_CTRL2               	osd0_bitmap_ctrl2               ;	// 0x00c0 : ''
	OSD0_STATUS_ALPHA_50X50         	osd0_status_alpha_50x50         ;	// 0x00c4 : ''
	OSD0_LSR_CTRL0                  	osd0_lsr_ctrl0                  ;	// 0x00c8 : ''
	OSD0_LSR_CTRL1                  	osd0_lsr_ctrl1                  ;	// 0x00cc : ''
	OSD0_LSR_CTRL2                  	osd0_lsr_ctrl2                  ;	// 0x00d0 : ''
	OSD0_LSR_CTRL3                  	osd0_lsr_ctrl3                  ;	// 0x00d4 : ''
	OSD0_LSR_CTRL4                  	osd0_lsr_ctrl4                  ;	// 0x00d8 : ''
	OSD0_LSR_CTRL5                  	osd0_lsr_ctrl5                  ;	// 0x00dc : ''
	OSD0_LSR_CTRL6                  	osd0_lsr_ctrl6                  ;	// 0x00e0 : ''
	OSD0_OUT_BUF_STATUS             	osd0_out_buf_status             ;	// 0x00e4 : ''
	OSD0_OSD_SHP_CG_CTRL            	osd0_osd_shp_cg_ctrl            ;	// 0x00e8 : ''
	OSD0_OSD_POST_CROP_CTRL_0       	osd0_osd_post_crop_ctrl_0       ;	// 0x00ec : ''
	OSD0_OSD_POST_CROP_CTRL_1       	osd0_osd_post_crop_ctrl_1       ;	// 0x00f0 : ''
	OSD0_OSD_POST_CROP_CTRL_2       	osd0_osd_post_crop_ctrl_2       ;	// 0x00f4 : ''
	OSD0_OSD_POST_CROP_CTRL_3       	osd0_osd_post_crop_ctrl_3       ;	// 0x00f8 : ''

	/* raxis.lim (2018/04/27)
	 *
	 * while accessing osd0_osd_gsr_ind_data without any configuration, system always hangs.
	 * sungmin0215.hong says that OSD_GSR should be access with indirect address mode.
	 * I will remove OSD_GSR becuase it's not used at OSD kdriver.
	 * refer to SICDTV-5148
	 */
#if 0
	OSD0_OSD_GSR_CTRL_0             	osd0_osd_gsr_ctrl_0             ;	// 0x00fc : ''
	OSD0_OSD_GSR_CTRL_1             	osd0_osd_gsr_ctrl_1             ;	// 0x0100 : ''
	OSD0_OSD_GSR_CTRL_2             	osd0_osd_gsr_ctrl_2             ;	// 0x0104 : ''
	OSD0_OSD_GSR_CTRL_3             	osd0_osd_gsr_ctrl_3             ;	// 0x0108 : ''
	OSD0_OSD_GSR_IND_CTRL           	osd0_osd_gsr_ind_ctrl           ;	// 0x010c : ''
	OSD0_OSD_GSR_IND_DATA           	osd0_osd_gsr_ind_data           ;	// 0x0110 : ''
#endif
}
OSD_IMG0_M19_REG_T;

extern volatile OSD_IMG0_M19_REG_T*  g_osd_img0_m19_reg;
extern OSD_IMG0_M19_REG_T*           g_osd_img0_m19_reg_shadow;


/* 21 regs, 21 types in Total*/

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'M16P3-A0_PQE_OSD_reg_man_one_sheet.csv' 20180328 20:21:05 KST by getregs v2.9 */
