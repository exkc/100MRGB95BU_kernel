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
	0x0000 osd0_status_alpha_apl0_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_0_3                         : 8,	//  0: 7
	apl_0_2                         : 8,	//  8:15
	apl_0_1                         : 8,	// 16:23
	apl_0_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL0_AA;

/*-----------------------------------------------------------------------------
	0x0004 osd0_status_alpha_apl1_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_1_3                         : 8,	//  0: 7
	apl_1_2                         : 8,	//  8:15
	apl_1_1                         : 8,	// 16:23
	apl_1_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL1_AA;

/*-----------------------------------------------------------------------------
	0x0008 osd0_status_alpha_apl2_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_2_3                         : 8,	//  0: 7
	apl_2_2                         : 8,	//  8:15
	apl_2_1                         : 8,	// 16:23
	apl_2_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL2_AA;

/*-----------------------------------------------------------------------------
	0x000c osd0_status_alpha_apl3_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_3_3                         : 8,	//  0: 7
	apl_3_2                         : 8,	//  8:15
	apl_3_1                         : 8,	// 16:23
	apl_3_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL3_AA;

/*-----------------------------------------------------------------------------
	0x0010 osd0_status_alpha_cnt0_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_1                         :16,	//  0:15
	cnt_0_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT0_AA;

/*-----------------------------------------------------------------------------
	0x0014 osd0_status_alpha_cnt1_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_3                         :16,	//  0:15
	cnt_0_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT1_AA;

/*-----------------------------------------------------------------------------
	0x0018 osd0_status_alpha_cnt2_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_1                         :16,	//  0:15
	cnt_1_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT2_AA;

/*-----------------------------------------------------------------------------
	0x001c osd0_status_alpha_cnt3_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_3                         :16,	//  0:15
	cnt_1_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT3_AA;

/*-----------------------------------------------------------------------------
	0x0020 osd0_status_alpha_cnt4_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_1                         :16,	//  0:15
	cnt_2_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT4_AA;

/*-----------------------------------------------------------------------------
	0x0024 osd0_status_alpha_cnt5_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_3                         :16,	//  0:15
	cnt_2_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT5_AA;

/*-----------------------------------------------------------------------------
	0x0028 osd0_status_alpha_cnt6_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_1                         :16,	//  0:15
	cnt_3_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT6_AA;

/*-----------------------------------------------------------------------------
	0x002c osd0_status_alpha_cnt7_aa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_3                         :16,	//  0:15
	cnt_3_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT7_AA;

/*-----------------------------------------------------------------------------
	0x0030 osd0_status_alpha_apl0_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_0_3                         : 8,	//  0: 7
	apl_0_2                         : 8,	//  8:15
	apl_0_1                         : 8,	// 16:23
	apl_0_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL0_RR;

/*-----------------------------------------------------------------------------
	0x0034 osd0_status_alpha_apl1_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_1_3                         : 8,	//  0: 7
	apl_1_2                         : 8,	//  8:15
	apl_1_1                         : 8,	// 16:23
	apl_1_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL1_RR;

/*-----------------------------------------------------------------------------
	0x0038 osd0_status_alpha_apl2_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_2_3                         : 8,	//  0: 7
	apl_2_2                         : 8,	//  8:15
	apl_2_1                         : 8,	// 16:23
	apl_2_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL2_RR;

/*-----------------------------------------------------------------------------
	0x003c osd0_status_alpha_apl3_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_3_3                         : 8,	//  0: 7
	apl_3_2                         : 8,	//  8:15
	apl_3_1                         : 8,	// 16:23
	apl_3_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL3_RR;

/*-----------------------------------------------------------------------------
	0x0040 osd0_status_alpha_cnt0_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_1                         :16,	//  0:15
	cnt_0_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT0_RR;

/*-----------------------------------------------------------------------------
	0x0044 osd0_status_alpha_cnt1_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_3                         :16,	//  0:15
	cnt_0_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT1_RR;

/*-----------------------------------------------------------------------------
	0x0048 osd0_status_alpha_cnt2_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_1                         :16,	//  0:15
	cnt_1_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT2_RR;

/*-----------------------------------------------------------------------------
	0x004c osd0_status_alpha_cnt3_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_3                         :16,	//  0:15
	cnt_1_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT3_RR;

/*-----------------------------------------------------------------------------
	0x0050 osd0_status_alpha_cnt4_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_1                         :16,	//  0:15
	cnt_2_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT4_RR;

/*-----------------------------------------------------------------------------
	0x0054 osd0_status_alpha_cnt5_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_3                         :16,	//  0:15
	cnt_2_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT5_RR;

/*-----------------------------------------------------------------------------
	0x0058 osd0_status_alpha_cnt6_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_1                         :16,	//  0:15
	cnt_3_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT6_RR;

/*-----------------------------------------------------------------------------
	0x005c osd0_status_alpha_cnt7_rr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_3                         :16,	//  0:15
	cnt_3_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT7_RR;

/*-----------------------------------------------------------------------------
	0x0060 osd0_status_alpha_apl0_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_0_3                         : 8,	//  0: 7
	apl_0_2                         : 8,	//  8:15
	apl_0_1                         : 8,	// 16:23
	apl_0_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL0_GG;

/*-----------------------------------------------------------------------------
	0x0064 osd0_status_alpha_apl1_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_1_3                         : 8,	//  0: 7
	apl_1_2                         : 8,	//  8:15
	apl_1_1                         : 8,	// 16:23
	apl_1_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL1_GG;

/*-----------------------------------------------------------------------------
	0x0068 osd0_status_alpha_apl2_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_2_3                         : 8,	//  0: 7
	apl_2_2                         : 8,	//  8:15
	apl_2_1                         : 8,	// 16:23
	apl_2_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL2_GG;

/*-----------------------------------------------------------------------------
	0x006c osd0_status_alpha_apl3_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_3_3                         : 8,	//  0: 7
	apl_3_2                         : 8,	//  8:15
	apl_3_1                         : 8,	// 16:23
	apl_3_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL3_GG;

/*-----------------------------------------------------------------------------
	0x0070 osd0_status_alpha_cnt0_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_1                         :16,	//  0:15
	cnt_0_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT0_GG;

/*-----------------------------------------------------------------------------
	0x0074 osd0_status_alpha_cnt1_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_3                         :16,	//  0:15
	cnt_0_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT1_GG;

/*-----------------------------------------------------------------------------
	0x0078 osd0_status_alpha_cnt2_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_1                         :16,	//  0:15
	cnt_1_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT2_GG;

/*-----------------------------------------------------------------------------
	0x007c osd0_status_alpha_cnt3_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_3                         :16,	//  0:15
	cnt_1_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT3_GG;

/*-----------------------------------------------------------------------------
	0x0080 osd0_status_alpha_cnt4_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_1                         :16,	//  0:15
	cnt_2_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT4_GG;

/*-----------------------------------------------------------------------------
	0x0084 osd0_status_alpha_cnt5_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_3                         :16,	//  0:15
	cnt_2_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT5_GG;

/*-----------------------------------------------------------------------------
	0x0088 osd0_status_alpha_cnt6_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_1                         :16,	//  0:15
	cnt_3_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT6_GG;

/*-----------------------------------------------------------------------------
	0x008c osd0_status_alpha_cnt7_gg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_3                         :16,	//  0:15
	cnt_3_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT7_GG;

/*-----------------------------------------------------------------------------
	0x0090 osd0_status_alpha_apl0_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_0_3                         : 8,	//  0: 7
	apl_0_2                         : 8,	//  8:15
	apl_0_1                         : 8,	// 16:23
	apl_0_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL0_BB;

/*-----------------------------------------------------------------------------
	0x0094 osd0_status_alpha_apl1_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_1_3                         : 8,	//  0: 7
	apl_1_2                         : 8,	//  8:15
	apl_1_1                         : 8,	// 16:23
	apl_1_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL1_BB;

/*-----------------------------------------------------------------------------
	0x0098 osd0_status_alpha_apl2_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_2_3                         : 8,	//  0: 7
	apl_2_2                         : 8,	//  8:15
	apl_2_1                         : 8,	// 16:23
	apl_2_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL2_BB;

/*-----------------------------------------------------------------------------
	0x009c osd0_status_alpha_apl3_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	apl_3_3                         : 8,	//  0: 7
	apl_3_2                         : 8,	//  8:15
	apl_3_1                         : 8,	// 16:23
	apl_3_0                         : 8;	// 24:31
} OSD0_STATUS_ALPHA_APL3_BB;

/*-----------------------------------------------------------------------------
	0x00a0 osd0_status_alpha_cnt0_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_1                         :16,	//  0:15
	cnt_0_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT0_BB;

/*-----------------------------------------------------------------------------
	0x00a4 osd0_status_alpha_cnt1_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_0_3                         :16,	//  0:15
	cnt_0_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT1_BB;

/*-----------------------------------------------------------------------------
	0x00a8 osd0_status_alpha_cnt2_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_1                         :16,	//  0:15
	cnt_1_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT2_BB;

/*-----------------------------------------------------------------------------
	0x00ac osd0_status_alpha_cnt3_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_1_3                         :16,	//  0:15
	cnt_1_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT3_BB;

/*-----------------------------------------------------------------------------
	0x00b0 osd0_status_alpha_cnt4_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_1                         :16,	//  0:15
	cnt_2_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT4_BB;

/*-----------------------------------------------------------------------------
	0x00b4 osd0_status_alpha_cnt5_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_2_3                         :16,	//  0:15
	cnt_2_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT5_BB;

/*-----------------------------------------------------------------------------
	0x00b8 osd0_status_alpha_cnt6_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_1                         :16,	//  0:15
	cnt_3_0                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT6_BB;

/*-----------------------------------------------------------------------------
	0x00bc osd0_status_alpha_cnt7_bb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cnt_3_3                         :16,	//  0:15
	cnt_3_2                         :16;	// 16:31
} OSD0_STATUS_ALPHA_CNT7_BB;

/*-----------------------------------------------------------------------------
	0x00c0 osd0_bitmap_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_alpha_50x50_th              : 8,	//  0: 7
	reg_pos_v_offset                : 3,	//  8:10
	                                : 1,	//    11 reserved
	reg_pos_h_offset                : 3;	// 12:14
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

typedef struct {
	OSD0_STATUS_ALPHA_APL0_AA       	osd0_status_alpha_apl0_aa       ;	// 0x0000 : ''
	OSD0_STATUS_ALPHA_APL1_AA       	osd0_status_alpha_apl1_aa       ;	// 0x0004 : ''
	OSD0_STATUS_ALPHA_APL2_AA       	osd0_status_alpha_apl2_aa       ;	// 0x0008 : ''
	OSD0_STATUS_ALPHA_APL3_AA       	osd0_status_alpha_apl3_aa       ;	// 0x000c : ''
	OSD0_STATUS_ALPHA_CNT0_AA       	osd0_status_alpha_cnt0_aa       ;	// 0x0010 : ''
	OSD0_STATUS_ALPHA_CNT1_AA       	osd0_status_alpha_cnt1_aa       ;	// 0x0014 : ''
	OSD0_STATUS_ALPHA_CNT2_AA       	osd0_status_alpha_cnt2_aa       ;	// 0x0018 : ''
	OSD0_STATUS_ALPHA_CNT3_AA       	osd0_status_alpha_cnt3_aa       ;	// 0x001c : ''
	OSD0_STATUS_ALPHA_CNT4_AA       	osd0_status_alpha_cnt4_aa       ;	// 0x0020 : ''
	OSD0_STATUS_ALPHA_CNT5_AA       	osd0_status_alpha_cnt5_aa       ;	// 0x0024 : ''
	OSD0_STATUS_ALPHA_CNT6_AA       	osd0_status_alpha_cnt6_aa       ;	// 0x0028 : ''
	OSD0_STATUS_ALPHA_CNT7_AA       	osd0_status_alpha_cnt7_aa       ;	// 0x002c : ''
	OSD0_STATUS_ALPHA_APL0_RR       	osd0_status_alpha_apl0_rr       ;	// 0x0030 : ''
	OSD0_STATUS_ALPHA_APL1_RR       	osd0_status_alpha_apl1_rr       ;	// 0x0034 : ''
	OSD0_STATUS_ALPHA_APL2_RR       	osd0_status_alpha_apl2_rr       ;	// 0x0038 : ''
	OSD0_STATUS_ALPHA_APL3_RR       	osd0_status_alpha_apl3_rr       ;	// 0x003c : ''
	OSD0_STATUS_ALPHA_CNT0_RR       	osd0_status_alpha_cnt0_rr       ;	// 0x0040 : ''
	OSD0_STATUS_ALPHA_CNT1_RR       	osd0_status_alpha_cnt1_rr       ;	// 0x0044 : ''
	OSD0_STATUS_ALPHA_CNT2_RR       	osd0_status_alpha_cnt2_rr       ;	// 0x0048 : ''
	OSD0_STATUS_ALPHA_CNT3_RR       	osd0_status_alpha_cnt3_rr       ;	// 0x004c : ''
	OSD0_STATUS_ALPHA_CNT4_RR       	osd0_status_alpha_cnt4_rr       ;	// 0x0050 : ''
	OSD0_STATUS_ALPHA_CNT5_RR       	osd0_status_alpha_cnt5_rr       ;	// 0x0054 : ''
	OSD0_STATUS_ALPHA_CNT6_RR       	osd0_status_alpha_cnt6_rr       ;	// 0x0058 : ''
	OSD0_STATUS_ALPHA_CNT7_RR       	osd0_status_alpha_cnt7_rr       ;	// 0x005c : ''
	OSD0_STATUS_ALPHA_APL0_GG       	osd0_status_alpha_apl0_gg       ;	// 0x0060 : ''
	OSD0_STATUS_ALPHA_APL1_GG       	osd0_status_alpha_apl1_gg       ;	// 0x0064 : ''
	OSD0_STATUS_ALPHA_APL2_GG       	osd0_status_alpha_apl2_gg       ;	// 0x0068 : ''
	OSD0_STATUS_ALPHA_APL3_GG       	osd0_status_alpha_apl3_gg       ;	// 0x006c : ''
	OSD0_STATUS_ALPHA_CNT0_GG       	osd0_status_alpha_cnt0_gg       ;	// 0x0070 : ''
	OSD0_STATUS_ALPHA_CNT1_GG       	osd0_status_alpha_cnt1_gg       ;	// 0x0074 : ''
	OSD0_STATUS_ALPHA_CNT2_GG       	osd0_status_alpha_cnt2_gg       ;	// 0x0078 : ''
	OSD0_STATUS_ALPHA_CNT3_GG       	osd0_status_alpha_cnt3_gg       ;	// 0x007c : ''
	OSD0_STATUS_ALPHA_CNT4_GG       	osd0_status_alpha_cnt4_gg       ;	// 0x0080 : ''
	OSD0_STATUS_ALPHA_CNT5_GG       	osd0_status_alpha_cnt5_gg       ;	// 0x0084 : ''
	OSD0_STATUS_ALPHA_CNT6_GG       	osd0_status_alpha_cnt6_gg       ;	// 0x0088 : ''
	OSD0_STATUS_ALPHA_CNT7_GG       	osd0_status_alpha_cnt7_gg       ;	// 0x008c : ''
	OSD0_STATUS_ALPHA_APL0_BB       	osd0_status_alpha_apl0_bb       ;	// 0x0090 : ''
	OSD0_STATUS_ALPHA_APL1_BB       	osd0_status_alpha_apl1_bb       ;	// 0x0094 : ''
	OSD0_STATUS_ALPHA_APL2_BB       	osd0_status_alpha_apl2_bb       ;	// 0x0098 : ''
	OSD0_STATUS_ALPHA_APL3_BB       	osd0_status_alpha_apl3_bb       ;	// 0x009c : ''
	OSD0_STATUS_ALPHA_CNT0_BB       	osd0_status_alpha_cnt0_bb       ;	// 0x00a0 : ''
	OSD0_STATUS_ALPHA_CNT1_BB       	osd0_status_alpha_cnt1_bb       ;	// 0x00a4 : ''
	OSD0_STATUS_ALPHA_CNT2_BB       	osd0_status_alpha_cnt2_bb       ;	// 0x00a8 : ''
	OSD0_STATUS_ALPHA_CNT3_BB       	osd0_status_alpha_cnt3_bb       ;	// 0x00ac : ''
	OSD0_STATUS_ALPHA_CNT4_BB       	osd0_status_alpha_cnt4_bb       ;	// 0x00b0 : ''
	OSD0_STATUS_ALPHA_CNT5_BB       	osd0_status_alpha_cnt5_bb       ;	// 0x00b4 : ''
	OSD0_STATUS_ALPHA_CNT6_BB       	osd0_status_alpha_cnt6_bb       ;	// 0x00b8 : ''
	OSD0_STATUS_ALPHA_CNT7_BB       	osd0_status_alpha_cnt7_bb       ;	// 0x00bc : ''
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
}
OSD_SCAN_O18_REG_T;
/* 59 regs, 59 types */

/* 59 regs, 59 types in Total*/

extern volatile OSD_SCAN_O18_REG_T*  g_osd_scan_o18_reg;
extern OSD_SCAN_O18_REG_T*           g_osd_scan_o18_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'O18_PQE_OSD_STATUS_reg_man.csv' 20170603 20:32:59 KST by getregs v2.9 */
