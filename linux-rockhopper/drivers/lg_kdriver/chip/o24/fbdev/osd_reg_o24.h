#ifndef _OSD_REG_O24_H_
#define _OSD_REG_O24_H_

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
	0x0000 osd_status_mon_cfg ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_cfg              : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_status_mon_osd_sel          : 2,	//  4: 5
	reg_status_crsr_sel             : 2,	//  6: 7
	                                : 4,	//  8:11 reserved
	reg_4k_status_sel               : 1,	//    12
	reg_pic_cnt_sel_de              : 2,	// 13:14
	reg_pic_cnt_in_sync             : 1,	//    15
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
	0x0008 osd_status_pic_cnt ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd4_pic_cnt                :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_osd0_pic_cnt                :12;	// 16:27
} OSD_STATUS_PIC_CNT;

/*-----------------------------------------------------------------------------
	0x000c osd_status_mixer_line ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_mixer_line             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_bosd_mixer_line             :12;	// 16:27
} OSD_STATUS_MIXER_LINE;

/*-----------------------------------------------------------------------------
	0x0010 osd_status_mon_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data0            ;   	// 31: 0
} OSD_STATUS_MON_DATA0;

/*-----------------------------------------------------------------------------
	0x0014 osd_status_mon_data1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data1            ;   	// 31: 0
} OSD_STATUS_MON_DATA1;

/*-----------------------------------------------------------------------------
	0x0018 osd_status_mon_data2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data2            ;   	// 31: 0
} OSD_STATUS_MON_DATA2;

/*-----------------------------------------------------------------------------
	0x001c osd_status_mon_data3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data3            ;   	// 31: 0
} OSD_STATUS_MON_DATA3;

/*-----------------------------------------------------------------------------
	0x0020 osd_status_mon_data4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data4            ;   	// 31: 0
} OSD_STATUS_MON_DATA4;

/*-----------------------------------------------------------------------------
	0x0024 osd_status_mon_data5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data5            ;   	// 31: 0
} OSD_STATUS_MON_DATA5;

/*-----------------------------------------------------------------------------
	0x0028 osd_status_mon_data6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data6            ;   	// 31: 0
} OSD_STATUS_MON_DATA6;

/*-----------------------------------------------------------------------------
	0x002c osd_status_mon_data7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data7            ;   	// 31: 0
} OSD_STATUS_MON_DATA7;

/*-----------------------------------------------------------------------------
	0x0030 osd_status_mon_data8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data8            ;   	// 31: 0
} OSD_STATUS_MON_DATA8;

/*-----------------------------------------------------------------------------
	0x0034 osd_status_mon_data9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_data9            ;   	// 31: 0
} OSD_STATUS_MON_DATA9;

/*-----------------------------------------------------------------------------
	0x0038 osd_status_mon_dataa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_dataa            ;   	// 31: 0
} OSD_STATUS_MON_DATAA;

/*-----------------------------------------------------------------------------
	0x003c osd_status_mon_datab ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_status_mon_datab            ;   	// 31: 0
} OSD_STATUS_MON_DATAB;

/*-----------------------------------------------------------------------------
	0x0000 osd_common_plte_sel ''
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
	0x0004 osd_common_ctrl_irq ''
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
	reg_common_ctrl_irq_en_mixer_bosd: 1,	//    24
	reg_common_ctrl_irq_en_mixer_sosd: 1;	//    25
} OSD_COMMON_CTRL_IRQ;

/*-----------------------------------------------------------------------------
	0x0008 osd_common_ctrl_pic_init ''
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
	0x000c osd_common_ctrl_pic_timer ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_pic_init_timer       ;   	// 31: 0
} OSD_COMMON_CTRL_PIC_TIMER;

/*-----------------------------------------------------------------------------
	0x0010 osd0_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD0_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0014 osd1_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD1_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0018 osd2_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD2_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x001c osd3_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD3_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0020 osd4_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD4_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0024 osd5_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD5_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0028 osd6_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD6_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x002c osd7_common_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSD7_COMMON_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0030 osd_cg_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mm_test                     : 2,	//  0: 1
	                                :27,	//  2:28 reserved
	reg_sosd_cg_on_n                : 1,	//    29
	reg_bosd1_cg_on_n               : 1,	//    30
	reg_bosd0_cg_on_n               : 1;	//    31
} OSD_CG_CTRL;

/*-----------------------------------------------------------------------------
	0x0000 ctrl_sosd_mixer_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_disp_size_h            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_sosd_disp_size_w            :13;	// 16:28
} CTRL_SOSD_MIXER_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0004 ctrl_sosd_mixer_output ''
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
	0x0008 ctrl_sosd_mixer_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_mixer_awb_red          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd4_mixer_awb_red          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_osd0_mixer_awb_green        : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_osd4_mixer_awb_green        : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_osd0_mixer_awb_blue         : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_osd4_mixer_awb_blue         : 1,	//    20
	                                :10,	// 21:30 reserved
	reg_mixer_ctrl_cg_en_n          : 1;	//    31
} CTRL_SOSD_MIXER_AWB;

/*-----------------------------------------------------------------------------
	0x000c ctrl_sosd_mixer_miracast_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_sosd_miracast_vid_b   : 8,	//  0: 7
	reg_mixer_sosd_miracast_vid_g   : 8,	//  8:15
	reg_mixer_sosd_miracast_vid_r   : 8,	// 16:23
	                                : 6,	// 24:29 reserved
	reg_mixer_sosd_debug_en         : 1,	//    30
	reg_mixer_sosd_vid_force_en     : 1;	//    31
} CTRL_SOSD_MIXER_MIRACAST_CTRL;

/*-----------------------------------------------------------------------------
	0x0010 ctrl_sosd_mixer_ctrl_alpha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ctrl_video_alhpa            : 8,	//  0: 7
	                                :23,	//  8:30 reserved
	reg_alpha_div_off               : 1;	//    31
} CTRL_SOSD_MIXER_CTRL_ALPHA;

/*-----------------------------------------------------------------------------
	0x0014 ctrl_sosd_mixer_force_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_coc_mode                    : 8,	//  0: 7
	                                :22,	//  8:29 reserved
	reg_coc_en                      : 1,	//    30
	reg_result_force_en             : 1;	//    31
} CTRL_SOSD_MIXER_FORCE_CTRL0;

/*-----------------------------------------------------------------------------
	0x0018 ctrl_sosd_mixer_force_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_force_b                     : 8,	//  0: 7
	reg_force_g                     : 8,	//  8:15
	reg_force_r                     : 8,	// 16:23
	reg_force_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_FORCE_CTRL1;

/*-----------------------------------------------------------------------------
	0x001c ctrl_sosd_mixer_hole ''
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
	0x0020 ctrl_sosd_mixer_mux0 ''
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
	0x0024 ctrl_sosd_mixer_mux1 ''
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
	0x0028 ctrl_sosd_mixer_mux2 ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x002c ctrl_sosd_mixer_mux3 ''
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
	0x0030 ctrl_sosd_mixer_mux4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX4;

/*-----------------------------------------------------------------------------
	0x0034 ctrl_sosd_mixer_mux5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX5;

/*-----------------------------------------------------------------------------
	0x0038 ctrl_sosd_mixer_mux6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX6;

/*-----------------------------------------------------------------------------
	0x003c ctrl_sosd_mixer_mux7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX7;

/*-----------------------------------------------------------------------------
	0x0040 ctrl_sosd_mixer_mux8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_x                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX8;

/*-----------------------------------------------------------------------------
	0x0044 ctrl_sosd_mixer_mux9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_w                      :13;	// 16:28
} CTRL_SOSD_MIXER_MUX9;

/*-----------------------------------------------------------------------------
	0x0048 ctrl_sosd_mixer_muxa ''
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
	0x004c ctrl_sosd_mixer_muxb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_h                     :12,	//  0:11
	reg_hole0_y                     :12,	// 12:23
	reg_hole0_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXB;

/*-----------------------------------------------------------------------------
	0x0050 ctrl_sosd_mixer_muxc ''
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
	0x0054 ctrl_sosd_mixer_muxd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_h                     :12,	//  0:11
	reg_hole1_y                     :12,	// 12:23
	reg_hole1_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXD;

/*-----------------------------------------------------------------------------
	0x0058 ctrl_sosd_mixer_muxe ''
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
	0x005c ctrl_sosd_mixer_muxf ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_h                     :12,	//  0:11
	reg_hole2_y                     :12,	// 12:23
	reg_hole2_a                     : 8;	// 24:31
} CTRL_SOSD_MIXER_MUXF;

/*-----------------------------------------------------------------------------
	0x0000 ctrl_bosd0_mixer_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bosd_disp_size_h            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_bosd_disp_size_w            :13;	// 16:28
} CTRL_BOSD0_MIXER_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0004 ctrl_bosd0_mixer_output ''
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
} CTRL_BOSD0_MIXER_OUTPUT;

/*-----------------------------------------------------------------------------
	0x0008 ctrl_bosd0_mixer_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_mixer_awb_red          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd4_mixer_awb_red          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_osd0_mixer_awb_green        : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_osd4_mixer_awb_green        : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_osd0_mixer_awb_blue         : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_osd4_mixer_awb_blue         : 1,	//    20
	                                :10,	// 21:30 reserved
	reg_mixer_ctrl_cg_en_n          : 1;	//    31
} CTRL_BOSD0_MIXER_AWB;

/*-----------------------------------------------------------------------------
	0x001c ctrl_bosd0_mixer_hole ''
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
} CTRL_BOSD0_MIXER_HOLE;

/*-----------------------------------------------------------------------------
	0x0020 ctrl_bosd0_mixer_mux0 ''
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
} CTRL_BOSD0_MIXER_MUX0;

/*-----------------------------------------------------------------------------
	0x0024 ctrl_bosd0_mixer_mux1 ''
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
} CTRL_BOSD0_MIXER_MUX1;

/*-----------------------------------------------------------------------------
	0x0028 ctrl_bosd0_mixer_mux2 ''
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
} CTRL_BOSD0_MIXER_MUX2;

/*-----------------------------------------------------------------------------
	0x002c ctrl_bosd0_mixer_mux3 ''
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
} CTRL_BOSD0_MIXER_MUX3;

/*-----------------------------------------------------------------------------
	0x0030 ctrl_bosd0_mixer_mux4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_x                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX4;

/*-----------------------------------------------------------------------------
	0x0034 ctrl_bosd0_mixer_mux5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_w                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX5;

/*-----------------------------------------------------------------------------
	0x0038 ctrl_bosd0_mixer_mux6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_x                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX6;

/*-----------------------------------------------------------------------------
	0x003c ctrl_bosd0_mixer_mux7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_w                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX7;

/*-----------------------------------------------------------------------------
	0x0040 ctrl_bosd0_mixer_mux8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_x                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX8;

/*-----------------------------------------------------------------------------
	0x0044 ctrl_bosd0_mixer_mux9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_w                      :13;	// 16:28
} CTRL_BOSD0_MIXER_MUX9;

/*-----------------------------------------------------------------------------
	0x0048 ctrl_bosd0_mixer_muxa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_w                     :13,	//  0:12
	reg_hole0_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole0_en                    : 1,	//    28
	reg_hole0_reverse_en            : 1;	//    29
} CTRL_BOSD0_MIXER_MUXA;

/*-----------------------------------------------------------------------------
	0x004c ctrl_bosd0_mixer_muxb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_h                     :12,	//  0:11
	reg_hole0_y                     :12,	// 12:23
	reg_hole0_a                     : 8;	// 24:31
} CTRL_BOSD0_MIXER_MUXB;

/*-----------------------------------------------------------------------------
	0x0050 ctrl_bosd0_mixer_muxc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_w                     :13,	//  0:12
	reg_hole1_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole1_en                    : 1,	//    28
	reg_hole1_reverse_en            : 1;	//    29
} CTRL_BOSD0_MIXER_MUXC;

/*-----------------------------------------------------------------------------
	0x0054 ctrl_bosd0_mixer_muxd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_h                     :12,	//  0:11
	reg_hole1_y                     :12,	// 12:23
	reg_hole1_a                     : 8;	// 24:31
} CTRL_BOSD0_MIXER_MUXD;

/*-----------------------------------------------------------------------------
	0x0058 ctrl_bosd0_mixer_muxe ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_w                     :13,	//  0:12
	reg_hole2_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole2_en                    : 1,	//    28
	reg_hole2_reverse_en            : 1;	//    29
} CTRL_BOSD0_MIXER_MUXE;

/*-----------------------------------------------------------------------------
	0x005c ctrl_bosd0_mixer_muxf ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_h                     :12,	//  0:11
	reg_hole2_y                     :12,	// 12:23
	reg_hole2_a                     : 8;	// 24:31
} CTRL_BOSD0_MIXER_MUXF;

/*-----------------------------------------------------------------------------
	0x0060 ctrl_bosd0_mixer_led_alpha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_alpha_debug_en              : 1;	//    31
} CTRL_BOSD0_MIXER_LED_ALPHA;

/*-----------------------------------------------------------------------------
	0x0080 ctrl_bosd1_mixer_disp_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bosd_disp_size_h            :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_bosd_disp_size_w            :13;	// 16:28
} CTRL_BOSD1_MIXER_DISP_SIZE;

/*-----------------------------------------------------------------------------
	0x0084 ctrl_bosd1_mixer_output ''
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
} CTRL_BOSD1_MIXER_OUTPUT;

/*-----------------------------------------------------------------------------
	0x0088 ctrl_bosd1_mixer_awb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_mixer_awb_red          : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_osd4_mixer_awb_red          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_osd0_mixer_awb_green        : 1,	//     8
	                                : 3,	//  9:11 reserved
	reg_osd4_mixer_awb_green        : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_osd0_mixer_awb_blue         : 1,	//    16
	                                : 3,	// 17:19 reserved
	reg_osd4_mixer_awb_blue         : 1,	//    20
	                                :10,	// 21:30 reserved
	reg_mixer_ctrl_cg_en_n          : 1;	//    31
} CTRL_BOSD1_MIXER_AWB;

/*-----------------------------------------------------------------------------
	0x008c ctrl_bosd1_mixer_miracast_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_mixer_bosd_miracast_vid_b   : 8,	//  0: 7
	reg_mixer_bosd_miracast_vid_g   : 8,	//  8:15
	reg_mixer_bosd_miracast_vid_r   : 8,	// 16:23
	                                : 6,	// 24:29 reserved
	reg_mixer_bosd_debug_en         : 1,	//    30
	reg_mixer_bosd_vid_force_en     : 1;	//    31
} CTRL_BOSD1_MIXER_MIRACAST_CTRL;

/*-----------------------------------------------------------------------------
	0x009c ctrl_bosd1_mixer_hole ''
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
} CTRL_BOSD1_MIXER_HOLE;

/*-----------------------------------------------------------------------------
	0x00a0 ctrl_bosd1_mixer_mux0 ''
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
} CTRL_BOSD1_MIXER_MUX0;

/*-----------------------------------------------------------------------------
	0x00a4 ctrl_bosd1_mixer_mux1 ''
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
} CTRL_BOSD1_MIXER_MUX1;

/*-----------------------------------------------------------------------------
	0x00a8 ctrl_bosd1_mixer_mux2 ''
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
} CTRL_BOSD1_MIXER_MUX2;

/*-----------------------------------------------------------------------------
	0x00ac ctrl_bosd1_mixer_mux3 ''
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
} CTRL_BOSD1_MIXER_MUX3;

/*-----------------------------------------------------------------------------
	0x00b0 ctrl_bosd1_mixer_mux4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_x                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX4;

/*-----------------------------------------------------------------------------
	0x00b4 ctrl_bosd1_mixer_mux5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_0_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_0_w                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX5;

/*-----------------------------------------------------------------------------
	0x00b8 ctrl_bosd1_mixer_mux6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_x                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX6;

/*-----------------------------------------------------------------------------
	0x00bc ctrl_bosd1_mixer_mux7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_1_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_1_w                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX7;

/*-----------------------------------------------------------------------------
	0x00c0 ctrl_bosd1_mixer_mux8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_y                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_x                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX8;

/*-----------------------------------------------------------------------------
	0x00c4 ctrl_bosd1_mixer_mux9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	window_2_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	window_2_w                      :13;	// 16:28
} CTRL_BOSD1_MIXER_MUX9;

/*-----------------------------------------------------------------------------
	0x00c8 ctrl_bosd1_mixer_muxa ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_w                     :13,	//  0:12
	reg_hole0_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole0_en                    : 1,	//    28
	reg_hole0_reverse_en            : 1;	//    29
} CTRL_BOSD1_MIXER_MUXA;

/*-----------------------------------------------------------------------------
	0x00cc ctrl_bosd1_mixer_muxb ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole0_h                     :12,	//  0:11
	reg_hole0_y                     :12,	// 12:23
	reg_hole0_a                     : 8;	// 24:31
} CTRL_BOSD1_MIXER_MUXB;

/*-----------------------------------------------------------------------------
	0x00d0 ctrl_bosd1_mixer_muxc ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_w                     :13,	//  0:12
	reg_hole1_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole1_en                    : 1,	//    28
	reg_hole1_reverse_en            : 1;	//    29
} CTRL_BOSD1_MIXER_MUXC;

/*-----------------------------------------------------------------------------
	0x00d4 ctrl_bosd1_mixer_muxd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole1_h                     :12,	//  0:11
	reg_hole1_y                     :12,	// 12:23
	reg_hole1_a                     : 8;	// 24:31
} CTRL_BOSD1_MIXER_MUXD;

/*-----------------------------------------------------------------------------
	0x00d8 ctrl_bosd1_mixer_muxe ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_w                     :13,	//  0:12
	reg_hole2_x                     :13,	// 13:25
	                                : 2,	// 26:27 reserved
	reg_hole2_en                    : 1,	//    28
	reg_hole2_reverse_en            : 1;	//    29
} CTRL_BOSD1_MIXER_MUXE;

/*-----------------------------------------------------------------------------
	0x00dc ctrl_bosd1_mixer_muxf ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hole2_h                     :12,	//  0:11
	reg_hole2_y                     :12,	// 12:23
	reg_hole2_a                     : 8;	// 24:31
} CTRL_BOSD1_MIXER_MUXF;

/*-----------------------------------------------------------------------------
	0x00e0 ctrl_bosd1_mixer_led_alpha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_alpha_debug_en              : 1;	//    31
} CTRL_BOSD1_MIXER_LED_ALPHA;

/*-----------------------------------------------------------------------------
	0x00e4 ctrl_bosd1_mixer_obj_alpha ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_obj_map_en                  : 1,	//     0
	reg_obj_map_sel                 : 1,	//     1
	reg_obj_map_hscale_tap          : 1,	//     2
	reg_obj_map_hscale_repeat_en    : 1,	//     3
	reg_vid_delay                   : 6,	//  4: 9
	                                : 2,	// 10:11 reserved
	reg_obj_alpha_sel               : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_obj_delay                   : 6;	// 16:21
} CTRL_BOSD1_MIXER_OBJ_ALPHA;

/*-----------------------------------------------------------------------------
	0x0000 osd0_ctrl_main ''
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
} OSD0_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0004 osd0_base_addr ''
------------------------------------------------------------------------------*/
/*	no field */

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
} OSD0_CTRL_SWAP;

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
} OSD0_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0010 osd0_ctrl_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	reg_osd_line_th_en              : 1,	//     2
	reg_osd_bilinear                : 1,	//     3
	reg_osd_odd_width_en            : 1,	//     4
	reg_osd_mode_32p                : 1,	//     5
	reg_osd_buf_mode_en_n           : 1,	//     6
	                                : 1,	//     7 reserved
	reg_osd_sampling_mode           : 1,	//     8
	                                : 1,	//     9 reserved
	reg_osd_hsc_phase_off           : 9,	// 10:18
	reg_osd_vsc_phase_off           : 9,	// 19:27
	reg_osd_vcubic_filter_sel       : 2;	// 28:29
} OSD0_CTRL_SCALER;

/*-----------------------------------------------------------------------------
	0x0014 osd0_info_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	status_line_memory_ac           :16,	//  0:15
	status_line_memory_yg           :16;	// 16:31
} OSD0_INFO_SCALER;

/*-----------------------------------------------------------------------------
	0x0018 osd0_ctrl_path ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_direc                  : 1,	//     0
	reg_sosd_cg_on                  : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd_ctrl_bosd_pos               : 1,	//     4
	                                : 3,	//  5: 7 reserved
	osd_ctrl_eo2s                   : 1,	//     8
	osd_ctrl_eo2s_turn              : 1,	//     9
	                                : 2,	// 10:11 reserved
	osd_ctrl_eo2eeoo                : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_ctrl_path_width             :13;	// 16:28
} OSD0_CTRL_PATH;

/*-----------------------------------------------------------------------------
	0x001c osd0_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD0_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0020 osd0_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD0_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0024 osd0_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD0_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0028 osd0_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD0_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x002c osd0_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD0_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0030 osd0_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD0_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0034 osd0_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD0_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0038 osd0_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD0_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x003c osd0_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD0_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0040 osd0_ctrl_sync0 ''
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
} OSD0_CTRL_SYNC0;

/*-----------------------------------------------------------------------------
	0x0044 osd0_ctrl_sync1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_disp_h                 :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_disp_w                 :13;	// 16:28
} OSD0_CTRL_SYNC1;

/*-----------------------------------------------------------------------------
	0x0048 osd0_ctrl_sync2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_r_3d_disparity_value        : 8,	//  0: 7
	osd_r_3d_disparity_sign         : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd_l_3d_disparity_value        : 8,	// 16:23
	osd_l_3d_disparity_sign         : 1;	//    24
} OSD0_CTRL_SYNC2;

/*-----------------------------------------------------------------------------
	0x004c osd0_ctrl_sync3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_3d_blank               ;   	// 31: 0
} OSD0_CTRL_SYNC3;

/*-----------------------------------------------------------------------------
	0x0050 osd0_ctrl_sync4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_vact_video             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_vact_space             :12;	// 16:27
} OSD0_CTRL_SYNC4;

/*-----------------------------------------------------------------------------
	0x0054 osd0_ctrl_sync5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_force_disp_area_h           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_force_disp_area_w           :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_v_force_en                  : 1,	//    30
	reg_h_force_en                  : 1;	//    31
} OSD0_CTRL_SYNC5;

/*-----------------------------------------------------------------------------
	0x0058 osd0_bitmap_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_dtm_detour_en               : 1,	//     0
	reg_dither_detour_en            : 1,	//     1
	reg_rgb2yc_p_detour_en          : 1,	//     2
	reg_ord_detour_en               : 1,	//     3
	reg_yc2rgb_f_detour_en          : 1,	//     4
	reg_pre_mul_alpha_detour_en     : 1,	//     5
	                                : 4,	//  6: 9 reserved
	reg_alpha_th                    : 8,	// 10:17
	reg_bitmap_status_sel           : 2,	// 18:19
	reg_4x4_sampling_on             : 1,	//    20
	reg_yc2rgb_csc_coef_mux         : 1,	//    21
	reg_yc2rgb_csc_en               : 1,	//    22
	reg_rgb2yc_csc_coef_mux         : 1,	//    23
	                                : 1,	//    24 reserved
	reg_vsp_yc_detour_en            : 1,	//    25
	reg_osd_rgb_inverse_sosd_en     : 1,	//    26
	reg_osd_rgb_inverse_bosd_en     : 1,	//    27
	reg_osd_shp_detour_en           : 1,	//    28
	                                : 1,	//    29 reserved
	reg_rgb2yc_csc_p_en_oclk        : 1,	//    30
	reg_rgb2yc_csc_en_de_clk        : 1;	//    31
} OSD0_BITMAP_CTRL0;

/*-----------------------------------------------------------------------------
	0x005c osd0_bitmap_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd0_premul_alpha_en        : 1,	//     0
	                                : 7,	//  1: 7 reserved
	reg_out_buf_monitor_line_th     :16,	//  8:23
	                                : 5,	// 24:28 reserved
	reg_out_buf_monitor_line_th_en  : 1,	//    29
	reg_out_buf_monitor_mode        : 1,	//    30
	reg_rgb2yc_fifo_en              : 1;	//    31
} OSD0_BITMAP_CTRL1;

/*-----------------------------------------------------------------------------
	0x0060 osd0_vsp_bosd_ctrl_0 ''
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
} OSD0_VSP_BOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0064 osd0_vsp_bosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSD0_VSP_BOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0068 osd0_vsp_sosd_ctrl_0 ''
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
} OSD0_VSP_SOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x006c osd0_vsp_sosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSD0_VSP_SOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0070 osd0_bitmap_ctrl2 ''
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
	0x0074 osd0_status_alpha_50x50 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	alpha_50x50_cnt                 ;   	// 31: 0
} OSD0_STATUS_ALPHA_50X50;

/*-----------------------------------------------------------------------------
	0x0078 osd0_scaler_status_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sc_status_scaler_ac         : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_sc_status_scaler_yg         : 3,	//  4: 6
	                                :23,	//  7:29 reserved
	reg_sc_status_monitor_mode      : 1,	//    30
	reg_sc_status_scaler_on         : 1;	//    31
} OSD0_SCALER_STATUS_CTRL;

/*-----------------------------------------------------------------------------
	0x007c osd0_out_buf_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	out_buf_status                  :16,	//  0:15
	out_buf_urgency                 : 1;	//    16
} OSD0_OUT_BUF_STATUS;

/*-----------------------------------------------------------------------------
	0x0080 osd0_cdc_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_crop_manual_en              : 1,	//    30
	reg_crop_en                     : 1;	//    31
} OSD0_CDC_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0084 osd0_cdc_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD0_CDC_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0088 osd0_cdc_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD0_CDC_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x008c osd0_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD0_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0090 osd0_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD0_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0094 osd0_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD0_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0098 osd0_crop_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crop_mixer_ypos                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	crop_mixer_xpos                 :13;	// 16:28
} OSD0_CROP_CTRL_3;

/*-----------------------------------------------------------------------------
	0x009c osd0_lsr_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_master_gain             : 8,	//  0: 7
	                                :22,	//  8:29 reserved
	reg_osd_lsr_debug_en            : 1,	//    30
	reg_osd_lsr_en                  : 1;	//    31
} OSD0_LSR_CTRL0;

/*-----------------------------------------------------------------------------
	0x00a0 osd0_lsr_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_x3                      : 8,	//  0: 7
	reg_lut_x2                      : 8,	//  8:15
	reg_lut_x1                      : 8,	// 16:23
	reg_lut_x0                      : 8;	// 24:31
} OSD0_LSR_CTRL1;

/*-----------------------------------------------------------------------------
	0x00a4 osd0_lsr_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_y3                      : 8,	//  0: 7
	reg_lut_y2                      : 8,	//  8:15
	reg_lut_y1                      : 8,	// 16:23
	reg_lut_y0                      : 8;	// 24:31
} OSD0_LSR_CTRL2;

/*-----------------------------------------------------------------------------
	0x00a8 osd0_lsr_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v0_h3             : 8,	//  0: 7
	reg_lsr_alpha_v0_h2             : 8,	//  8:15
	reg_lsr_alpha_v0_h1             : 8,	// 16:23
	reg_lsr_alpha_v0_h0             : 8;	// 24:31
} OSD0_LSR_CTRL3;

/*-----------------------------------------------------------------------------
	0x00ac osd0_lsr_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v1_h3             : 8,	//  0: 7
	reg_lsr_alpha_v1_h2             : 8,	//  8:15
	reg_lsr_alpha_v1_h1             : 8,	// 16:23
	reg_lsr_alpha_v1_h0             : 8;	// 24:31
} OSD0_LSR_CTRL4;

/*-----------------------------------------------------------------------------
	0x00b0 osd0_lsr_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v2_h3             : 8,	//  0: 7
	reg_lsr_alpha_v2_h2             : 8,	//  8:15
	reg_lsr_alpha_v2_h1             : 8,	// 16:23
	reg_lsr_alpha_v2_h0             : 8;	// 24:31
} OSD0_LSR_CTRL5;

/*-----------------------------------------------------------------------------
	0x00b4 osd0_lsr_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v3_h3             : 8,	//  0: 7
	reg_lsr_alpha_v3_h2             : 8,	//  8:15
	reg_lsr_alpha_v3_h1             : 8,	// 16:23
	reg_lsr_alpha_v3_h0             : 8;	// 24:31
} OSD0_LSR_CTRL6;

/*-----------------------------------------------------------------------------
	0x00b8 osd0_post_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD0_POST_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00bc osd0_post_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD0_POST_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00c0 osd0_post_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD0_POST_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00c4 osd0_post_crop_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crop_mixer_ypos                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	crop_mixer_xpos                 :13;	// 16:28
} OSD0_POST_CROP_CTRL_3;

/*-----------------------------------------------------------------------------
	0x00c8 osd0_gsr_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7,	//  8:14
	                                : 1,	//    15 reserved
	reg_block_no_v                  : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_block_no_h                  : 6,	// 24:29
	                                : 1,	//    30 reserved
	reg_block_info_force_en         : 1;	//    31
} OSD0_GSR_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00cc osd0_gsr_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7;	//  8:14
} OSD0_GSR_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00d0 osd0_gsr_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gsr_th_last                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_gsr_th                      :13;	// 16:28
} OSD0_GSR_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00d4 osd0_gsr_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_toggle_mode                 : 1,	//     0
	reg_mem_sel                     : 1,	//     1
	                                : 2,	//  2: 3 reserved
	reg_mem_auto_toggle_on          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_apb_data_merge              : 1;	//     8
} OSD0_GSR_CTRL_3;

/*-----------------------------------------------------------------------------
	0x00d8 osd0_gsr_ind_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD0_GSR_IND_CTRL;

/*-----------------------------------------------------------------------------
	0x00dc osd0_gsr_ind_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_gsr_ind_data                ;   	// 31: 0
} OSD0_GSR_IND_DATA;

/*-----------------------------------------------------------------------------
	0x00e0 osd0_shp_cg_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_osd_shp_cg_on               : 1;	//    31
} OSD0_SHP_CG_CTRL;

/*-----------------------------------------------------------------------------
	0x00e4 osd0_local_alpha_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_out_alpha                   :10,	//  0: 9
	reg_in_alpha                    :10,	// 10:19
	reg_coc_mode_b                  : 2,	// 20:21
	reg_coc_mode_g                  : 2,	// 22:23
	reg_coc_mode_r                  : 2,	// 24:25
	reg_coc_mode_a                  : 2,	// 26:27
	reg_coc_en                      : 1,	//    28
	reg_reverse_en                  : 1,	//    29
	reg_local_alpha_en              : 1,	//    30
	reg_local_alpha_detour          : 1;	//    31
} OSD0_LOCAL_ALPHA_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00e8 osd0_local_alpha_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_x_end                       :16,	//  0:15
	reg_x_start                     :16;	// 16:31
} OSD0_LOCAL_ALPHA_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00ec osd0_local_alpha_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_y_end                       :16,	//  0:15
	reg_y_start                     :16;	// 16:31
} OSD0_LOCAL_ALPHA_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0000 osd0_1_ctrl_main ''
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
} OSD0_1_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0004 osd0_1_base_addr ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0008 osd0_1_ctrl_swap ''
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
} OSD0_1_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x000c osd0_1_ctrl_pdec ''
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
} OSD0_1_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x001c osd0_1_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD0_1_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0020 osd0_1_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD0_1_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0024 osd0_1_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD0_1_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0028 osd0_1_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD0_1_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x002c osd0_1_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD0_1_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0030 osd0_1_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD0_1_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0034 osd0_1_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD0_1_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0038 osd0_1_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD0_1_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x003c osd0_1_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD0_1_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0040 reg_4k_osd_main_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_4k_mode_en                  : 1;	//    31
} REG_4K_OSD_MAIN_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0044 reg_4k_osd_main_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_4k_ypos                     :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_4k_xpos                     :12;	// 16:27
} REG_4K_OSD_MAIN_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0048 reg_4k_osd_main_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sc_i_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_sc_i_w                      :12;	// 16:27
} REG_4K_OSD_MAIN_CTRL_2;

/*-----------------------------------------------------------------------------
	0x004c reg_4k_osd_main_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sc_o_h                      :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_sc_o_w                      :12;	// 16:27
} REG_4K_OSD_MAIN_CTRL_3;

/*-----------------------------------------------------------------------------
	0x0050 reg_osd0_gsr_ctrl00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gsr_blend_en                : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_gsr_debug_sel               : 4,	//  4: 7
	                                : 8,	//  8:15 reserved
	reg_gsr_master_gain             :10;	// 16:25
} REG_OSD0_GSR_CTRL00;

/*-----------------------------------------------------------------------------
	0x0054 reg_osd0_gsr_ctrl01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_crnt_x3_i                   :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_crnt_x2_i                   :10;	// 16:25
} REG_OSD0_GSR_CTRL01;

/*-----------------------------------------------------------------------------
	0x0058 reg_osd0_gsr_ctrl02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_crnt_x1_i                   :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_crnt_x0_i                   :10;	// 16:25
} REG_OSD0_GSR_CTRL02;

/*-----------------------------------------------------------------------------
	0x005c reg_osd0_gsr_ctrl03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_crnt_y3_i                   : 8,	//  0: 7
	reg_crnt_y2_i                   : 8,	//  8:15
	reg_crnt_y1_i                   : 8,	// 16:23
	reg_crnt_y0_i                   : 8;	// 24:31
} REG_OSD0_GSR_CTRL03;

/*-----------------------------------------------------------------------------
	0x0060 reg_osd0_gsr_ctrl04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_value_x3_i                  :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_value_x2_i                  :10;	// 16:25
} REG_OSD0_GSR_CTRL04;

/*-----------------------------------------------------------------------------
	0x0064 reg_osd0_gsr_ctrl05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_value_x1_i                  :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_value_x0_i                  :10;	// 16:25
} REG_OSD0_GSR_CTRL05;

/*-----------------------------------------------------------------------------
	0x0068 reg_osd0_gsr_ctrl06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_value_y3_i                  : 8,	//  0: 7
	reg_value_y2_i                  : 8,	//  8:15
	reg_value_y1_i                  : 8,	// 16:23
	reg_value_y0_i                  : 8;	// 24:31
} REG_OSD0_GSR_CTRL06;

/*-----------------------------------------------------------------------------
	0x006c reg_osd0_gsr_ctrl07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sat_x3_i                    :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_sat_x2_i                    :10;	// 16:25
} REG_OSD0_GSR_CTRL07;

/*-----------------------------------------------------------------------------
	0x0070 reg_osd0_gsr_ctrl08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sat_x1_i                    :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	reg_sat_x0_i                    :10;	// 16:25
} REG_OSD0_GSR_CTRL08;

/*-----------------------------------------------------------------------------
	0x0074 reg_osd0_gsr_ctrl09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sat_y3_i                    : 8,	//  0: 7
	reg_sat_y2_i                    : 8,	//  8:15
	reg_sat_y1_i                    : 8,	// 16:23
	reg_sat_y0_i                    : 8;	// 24:31
} REG_OSD0_GSR_CTRL09;

/*-----------------------------------------------------------------------------
	0x0078 reg_osd0_gsr_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pxl_x0                      :12,	//  0:11
	                                : 3,	// 12:14 reserved
	reg_win_in_disable              : 1,	//    15
	reg_pxl_y0                      :12,	// 16:27
	                                : 3,	// 28:30 reserved
	reg_win_out_disable             : 1;	//    31
} REG_OSD0_GSR_CTRL10;

/*-----------------------------------------------------------------------------
	0x007c reg_osd0_gsr_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pxl_width                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_pxl_height                  :12;	// 16:27
} REG_OSD0_GSR_CTRL11;

/*-----------------------------------------------------------------------------
	0x0080 reg_osd0_ord_ctrl00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ord_en                      : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_ord_rand_en                 : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_blend_alpha                 : 8,	//  8:15
	reg_round_shift                 : 4,	// 16:19
	                                : 4,	// 20:23 reserved
	reg_resi_max                    : 6;	// 24:29
} REG_OSD0_ORD_CTRL00;

/*-----------------------------------------------------------------------------
	0x0084 reg_osd0_ord_ctrl01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_v_shift                     : 3,	//  0: 2
	                                : 1,	//     3 reserved
	reg_h_shift                     : 3,	//  4: 6
	                                : 1,	//     7 reserved
	reg_resi_v_over                 : 6,	//  8:13
	                                : 2,	// 14:15 reserved
	reg_resi_h_over                 : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_rand_number                 : 6;	// 24:29
} REG_OSD0_ORD_CTRL01;

/*-----------------------------------------------------------------------------
	0x0088 reg_osd0_ord_ctrl02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_eve_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL02;

/*-----------------------------------------------------------------------------
	0x008c reg_osd0_ord_ctrl03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_eve_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL03;

/*-----------------------------------------------------------------------------
	0x0090 reg_osd0_ord_ctrl04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_eve_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL04;

/*-----------------------------------------------------------------------------
	0x0094 reg_osd0_ord_ctrl05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_eve_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL05;

/*-----------------------------------------------------------------------------
	0x0098 reg_osd0_ord_ctrl06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_eve_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL06;

/*-----------------------------------------------------------------------------
	0x009c reg_osd0_ord_ctrl07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_eve_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL07;

/*-----------------------------------------------------------------------------
	0x00a0 reg_osd0_ord_ctrl08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_eve_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL08;

/*-----------------------------------------------------------------------------
	0x00a4 reg_osd0_ord_ctrl09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_eve_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL09;

/*-----------------------------------------------------------------------------
	0x00a8 reg_osd0_ord_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_eve_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL10;

/*-----------------------------------------------------------------------------
	0x00ac reg_osd0_ord_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_odd_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL11;

/*-----------------------------------------------------------------------------
	0x00b0 reg_osd0_ord_ctrl12 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_odd_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL12;

/*-----------------------------------------------------------------------------
	0x00b4 reg_osd0_ord_ctrl13 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gyy_odd_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL13;

/*-----------------------------------------------------------------------------
	0x00b8 reg_osd0_ord_ctrl14 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_odd_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL14;

/*-----------------------------------------------------------------------------
	0x00bc reg_osd0_ord_ctrl15 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_odd_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL15;

/*-----------------------------------------------------------------------------
	0x00c0 reg_osd0_ord_ctrl16 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_bcb_odd_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL16;

/*-----------------------------------------------------------------------------
	0x00c4 reg_osd0_ord_ctrl17 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_odd_hpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL17;

/*-----------------------------------------------------------------------------
	0x00c8 reg_osd0_ord_ctrl18 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_odd_vpel_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL18;

/*-----------------------------------------------------------------------------
	0x00cc reg_osd0_ord_ctrl19 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_rcr_odd_rand_lsfr_seed      ;   	// 31: 0
} REG_OSD0_ORD_CTRL19;

/*-----------------------------------------------------------------------------
	0x00d0 reg_osd0_pdf_ctrl00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_heigt                       :12,	//  0:11
	reg_width                       :12,	// 12:23
	                                : 7,	// 24:30 reserved
	reg_pdf_en                      : 1;	//    31
} REG_OSD0_PDF_CTRL00;

/*-----------------------------------------------------------------------------
	0x00d4 reg_osd0_pdf_ctrl01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_blk_heigt                   :12,	//  0:11
	reg_blk_width                   :12,	// 12:23
	                                : 6,	// 24:29 reserved
	reg_pdf_pel_sel                 : 2;	// 30:31
} REG_OSD0_PDF_CTRL01;

/*-----------------------------------------------------------------------------
	0x00d8 reg_osd0_pdf_ctrl02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_qh_th                       :21,	//  0:20
	                                : 1,	//    21 reserved
	reg_qh_scale                    : 2,	// 22:23
	                                : 7,	// 24:30 reserved
	reg_hd_cut_lsb3                 : 1;	//    31
} REG_OSD0_PDF_CTRL02;

/*-----------------------------------------------------------------------------
	0x00dc reg_osd0_pdf_ctrl03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pc_diff_th                  :10,	//  0: 9
	reg_pc_same_th                  :10,	// 10:19
	reg_pc_same_th_dc               :10;	// 20:29
} REG_OSD0_PDF_CTRL03;

/*-----------------------------------------------------------------------------
	0x00e0 reg_osd0_pdf_ctrl04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pm_min_sad_th               :10,	//  0: 9
	reg_pm_gmmd_th                  :10;	// 10:19
} REG_OSD0_PDF_CTRL04;

/*-----------------------------------------------------------------------------
	0x00e4 reg_osd0_pdf_ctrl05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pdf_ch_sel                  : 2;	//  0: 1
} REG_OSD0_PDF_CTRL05;

/*-----------------------------------------------------------------------------
	0x00e8 reg_osd0_pdf_ind_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pdf_ind_ctrl                ;   	// 31: 0
} REG_OSD0_PDF_IND_CTRL;

/*-----------------------------------------------------------------------------
	0x00ec reg_osd0_pdf_ind_data_rd ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_pdf_ind_data_rd             ;   	// 31: 0
} REG_OSD0_PDF_IND_DATA_RD;

/*-----------------------------------------------------------------------------
	0x0000 osd1_ctrl_main ''
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
} OSD1_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0004 osd1_base_addr ''
------------------------------------------------------------------------------*/
/*	no field */

/*-----------------------------------------------------------------------------
	0x0008 osd1_ctrl_swap ''
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
} OSD1_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x000c osd1_ctrl_pdec ''
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
} OSD1_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0010 osd1_ctrl_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 2,	//  0: 1 reserved
	reg_osd_line_th_en              : 1,	//     2
	reg_osd_bilinear                : 1,	//     3
	reg_osd_odd_width_en            : 1,	//     4
	reg_osd_mode_32p                : 1,	//     5
	reg_osd_buf_mode_en_n           : 1,	//     6
	                                : 1,	//     7 reserved
	reg_osd_sampling_mode           : 1,	//     8
	                                : 1,	//     9 reserved
	reg_osd_hsc_phase_off           : 9,	// 10:18
	reg_osd_vsc_phase_off           : 9,	// 19:27
	reg_osd_vcubic_filter_sel       : 2;	// 28:29
} OSD1_CTRL_SCALER;

/*-----------------------------------------------------------------------------
	0x0014 osd1_info_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_stat_filled3                : 8,	//  0: 7
	reg_stat_filled2                : 8,	//  8:15
	reg_stat_filled1                : 8,	// 16:23
	reg_stat_filled0                : 8;	// 24:31
} OSD1_INFO_SCALER;

/*-----------------------------------------------------------------------------
	0x0018 osd1_ctrl_path ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_direc                  : 1,	//     0
	reg_sosd_cg_on                  : 1,	//     1
	                                : 2,	//  2: 3 reserved
	osd_ctrl_bosd_pos               : 1,	//     4
	                                : 3,	//  5: 7 reserved
	osd_ctrl_eo2s                   : 1,	//     8
	osd_ctrl_eo2s_turn              : 1,	//     9
	                                : 2,	// 10:11 reserved
	osd_ctrl_eo2eeoo                : 1,	//    12
	                                : 3,	// 13:15 reserved
	reg_ctrl_path_width             :13;	// 16:28
} OSD1_CTRL_PATH;

/*-----------------------------------------------------------------------------
	0x001c osd1_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD1_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0020 osd1_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD1_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0024 osd1_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD1_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0028 osd1_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD1_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x002c osd1_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD1_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0030 osd1_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD1_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0034 osd1_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD1_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0038 osd1_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD1_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x003c osd1_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD1_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0040 osd1_ctrl_sync0 ''
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
} OSD1_CTRL_SYNC0;

/*-----------------------------------------------------------------------------
	0x0044 osd1_ctrl_sync1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_disp_h                 :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_disp_w                 :13;	// 16:28
} OSD1_CTRL_SYNC1;

/*-----------------------------------------------------------------------------
	0x0048 osd1_ctrl_sync2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_r_3d_disparity_value        : 8,	//  0: 7
	osd_r_3d_disparity_sign         : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd_l_3d_disparity_value        : 8,	// 16:23
	osd_l_3d_disparity_sign         : 1;	//    24
} OSD1_CTRL_SYNC2;

/*-----------------------------------------------------------------------------
	0x004c osd1_ctrl_sync3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_3d_blank               ;   	// 31: 0
} OSD1_CTRL_SYNC3;

/*-----------------------------------------------------------------------------
	0x0050 osd1_ctrl_sync4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_vact_video             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_vact_space             :12;	// 16:27
} OSD1_CTRL_SYNC4;

/*-----------------------------------------------------------------------------
	0x0054 osd1_ctrl_sync5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_force_disp_area_h           :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_force_disp_area_w           :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_v_force_en                  : 1,	//    30
	reg_h_force_en                  : 1;	//    31
} OSD1_CTRL_SYNC5;

/*-----------------------------------------------------------------------------
	0x0058 osd1_bitmap_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :10,	//  0: 9 reserved
	reg_alpha_th                    : 8,	// 10:17
	reg_bitmap_status_sel           : 2,	// 18:19
	reg_4x4_sampling_on             : 1,	//    20
	                                : 3,	// 21:23 reserved
	reg_gsr_sosd_detour             : 1,	//    24
	reg_gsr_bosd_detour             : 1,	//    25
	reg_osd_rgb_inverse_sosd_en     : 1,	//    26
	reg_osd_rgb_inverse_bosd_en     : 1,	//    27
	reg_osd_shp_detour_en           : 1,	//    28
	reg_yc2rgb_sosd_csc_en          : 1,	//    29
	reg_yc2rgb_bosd_csc_en          : 1,	//    30
	reg_rgb2yc_csc_en               : 1;	//    31
} OSD1_BITMAP_CTRL0;

/*-----------------------------------------------------------------------------
	0x005c osd1_bitmap_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	reg_out_buf_monitor_line_th     :16,	//  8:23
	                                : 5,	// 24:28 reserved
	reg_out_buf_monitor_line_th_en  : 1,	//    29
	reg_out_buf_monitor_mode        : 1,	//    30
	reg_rgb2yc_fifo_en              : 1;	//    31
} OSD1_BITMAP_CTRL1;

/*-----------------------------------------------------------------------------
	0x0060 osd1_vsp_bosd_ctrl_0 ''
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
} OSD1_VSP_BOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0064 osd1_vsp_bosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSD1_VSP_BOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0068 osd1_vsp_sosd_ctrl_0 ''
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
} OSD1_VSP_SOSD_CTRL_0;

/*-----------------------------------------------------------------------------
	0x006c osd1_vsp_sosd_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                : 8,	//  0: 7 reserved
	r_saturation                    : 8,	//  8:15
	r_offset                        :10;	// 16:25
} OSD1_VSP_SOSD_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0070 osd1_bitmap_ctrl2 ''
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
} OSD1_BITMAP_CTRL2;

/*-----------------------------------------------------------------------------
	0x0074 osd1_status_alpha_50x50 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	alpha_50x50_cnt                 ;   	// 31: 0
} OSD1_STATUS_ALPHA_50X50;

/*-----------------------------------------------------------------------------
	0x0078 osd1_scaler_status_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_buf_pic_width               :13,	//  0:12
	                                : 2,	// 13:14 reserved
	reg_stat_sel                    : 1,	//    15
	reg_lrepeat_hsize               : 8,	// 16:23
	                                : 4,	// 24:27 reserved
	reg_lrepeat_num                 : 3,	// 28:30
	reg_lrepeat_en                  : 1;	//    31
} OSD1_SCALER_STATUS_CTRL;

/*-----------------------------------------------------------------------------
	0x007c osd1_out_buf_status ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	out_buf_status                  :16,	//  0:15
	out_buf_urgency                 : 1;	//    16
} OSD1_OUT_BUF_STATUS;

/*-----------------------------------------------------------------------------
	0x0080 osd1_cdc_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 1,	//    29 reserved
	reg_crop_manual_en              : 1,	//    30
	reg_crop_en                     : 1;	//    31
} OSD1_CDC_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0084 osd1_cdc_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD1_CDC_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0088 osd1_cdc_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD1_CDC_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x008c osd1_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD1_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0090 osd1_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD1_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0094 osd1_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD1_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0098 osd1_crop_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crop_mixer_ypos                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	crop_mixer_xpos                 :13;	// 16:28
} OSD1_CROP_CTRL_3;

/*-----------------------------------------------------------------------------
	0x009c osd1_lsr_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_master_gain             : 8,	//  0: 7
	                                :22,	//  8:29 reserved
	reg_osd_lsr_debug_en            : 1,	//    30
	reg_osd_lsr_en                  : 1;	//    31
} OSD1_LSR_CTRL0;

/*-----------------------------------------------------------------------------
	0x00a0 osd1_lsr_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_x3                      : 8,	//  0: 7
	reg_lut_x2                      : 8,	//  8:15
	reg_lut_x1                      : 8,	// 16:23
	reg_lut_x0                      : 8;	// 24:31
} OSD1_LSR_CTRL1;

/*-----------------------------------------------------------------------------
	0x00a4 osd1_lsr_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lut_y3                      : 8,	//  0: 7
	reg_lut_y2                      : 8,	//  8:15
	reg_lut_y1                      : 8,	// 16:23
	reg_lut_y0                      : 8;	// 24:31
} OSD1_LSR_CTRL2;

/*-----------------------------------------------------------------------------
	0x00a8 osd1_lsr_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v0_h3             : 8,	//  0: 7
	reg_lsr_alpha_v0_h2             : 8,	//  8:15
	reg_lsr_alpha_v0_h1             : 8,	// 16:23
	reg_lsr_alpha_v0_h0             : 8;	// 24:31
} OSD1_LSR_CTRL3;

/*-----------------------------------------------------------------------------
	0x00ac osd1_lsr_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v1_h3             : 8,	//  0: 7
	reg_lsr_alpha_v1_h2             : 8,	//  8:15
	reg_lsr_alpha_v1_h1             : 8,	// 16:23
	reg_lsr_alpha_v1_h0             : 8;	// 24:31
} OSD1_LSR_CTRL4;

/*-----------------------------------------------------------------------------
	0x00b0 osd1_lsr_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v2_h3             : 8,	//  0: 7
	reg_lsr_alpha_v2_h2             : 8,	//  8:15
	reg_lsr_alpha_v2_h1             : 8,	// 16:23
	reg_lsr_alpha_v2_h0             : 8;	// 24:31
} OSD1_LSR_CTRL5;

/*-----------------------------------------------------------------------------
	0x00b4 osd1_lsr_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_lsr_alpha_v3_h3             : 8,	//  0: 7
	reg_lsr_alpha_v3_h2             : 8,	//  8:15
	reg_lsr_alpha_v3_h1             : 8,	// 16:23
	reg_lsr_alpha_v3_h0             : 8;	// 24:31
} OSD1_LSR_CTRL6;

/*-----------------------------------------------------------------------------
	0x00b8 osd1_post_crop_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_in_pic_height               :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_in_pic_width                :13,	// 16:28
	                                : 2,	// 29:30 reserved
	reg_crop_en                     : 1;	//    31
} OSD1_POST_CROP_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00bc osd1_post_crop_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	hoffset                         :13;	// 16:28
} OSD1_POST_CROP_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00c0 osd1_post_crop_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vactive                         :13,	//  0:12
	                                : 3,	// 13:15 reserved
	voffset                         :13;	// 16:28
} OSD1_POST_CROP_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00c4 osd1_post_crop_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	crop_mixer_ypos                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	crop_mixer_xpos                 :13;	// 16:28
} OSD1_POST_CROP_CTRL_3;

/*-----------------------------------------------------------------------------
	0x00c8 osd1_gsr_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7,	//  8:14
	                                : 1,	//    15 reserved
	reg_block_no_v                  : 6,	// 16:21
	                                : 2,	// 22:23 reserved
	reg_block_no_h                  : 6,	// 24:29
	                                : 1,	//    30 reserved
	reg_block_info_force_en         : 1;	//    31
} OSD1_GSR_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00cc osd1_gsr_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_block_size_v                : 7,	//  0: 6
	                                : 1,	//     7 reserved
	reg_block_size_h                : 7;	//  8:14
} OSD1_GSR_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00d0 osd1_gsr_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gsr_th_last                 :13,	//  0:12
	                                : 3,	// 13:15 reserved
	reg_gsr_th                      :13;	// 16:28
} OSD1_GSR_CTRL_2;

/*-----------------------------------------------------------------------------
	0x00d4 osd1_gsr_ctrl_3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_toggle_mode                 : 1,	//     0
	reg_mem_sel                     : 1,	//     1
	                                : 2,	//  2: 3 reserved
	reg_mem_auto_toggle_on          : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_apb_data_merge              : 1;	//     8
} OSD1_GSR_CTRL_3;

/*-----------------------------------------------------------------------------
	0x00d8 osd1_gsr_ind_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD1_GSR_IND_CTRL;

/*-----------------------------------------------------------------------------
	0x00dc osd1_gsr_ind_data ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_gsr_ind_data                ;   	// 31: 0
} OSD1_GSR_IND_DATA;

/*-----------------------------------------------------------------------------
	0x00e0 osd1_shp_cg_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :31,	//  0:30 reserved
	reg_osd_shp_cg_on               : 1;	//    31
} OSD1_SHP_CG_CTRL;

/*-----------------------------------------------------------------------------
	0x00e4 osd1_local_alpha_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_out_alpha                   : 8,	//  0: 7
	reg_in_alpha                    : 8,	//  8:15
	                                : 4,	// 16:19 reserved
	reg_coc_mode_b                  : 2,	// 20:21
	reg_coc_mode_g                  : 2,	// 22:23
	reg_coc_mode_r                  : 2,	// 24:25
	reg_coc_mode_a                  : 2,	// 26:27
	reg_coc_en                      : 1,	//    28
	reg_reverse_en                  : 1,	//    29
	reg_local_alpha_en              : 1,	//    30
	reg_local_alpha_detour          : 1;	//    31
} OSD1_LOCAL_ALPHA_CTRL_0;

/*-----------------------------------------------------------------------------
	0x00e8 osd1_local_alpha_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_x_end                       :16,	//  0:15
	reg_x_start                     :16;	// 16:31
} OSD1_LOCAL_ALPHA_CTRL_1;

/*-----------------------------------------------------------------------------
	0x00ec osd1_local_alpha_ctrl_2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_y_end                       :16,	//  0:15
	reg_y_start                     :16;	// 16:31
} OSD1_LOCAL_ALPHA_CTRL_2;

/*-----------------------------------------------------------------------------
	0x0000 osd4_ctrl_main ''
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
	                                : 2,	// 14:15 reserved
	osd_manual_line_inc             : 2,	// 16:17
	osd_manual_dlr                  : 2,	// 18:19
	osd_manual_line_inc_en          : 1,	//    20
	line_repeat                     : 3,	// 21:23
	osd_yuyv_mode_en                : 1,	//    24
	                                : 3,	// 25:27 reserved
	osd_hdr_ready_flag_en           : 1,	//    28
	osd_hdr_ready_flag              : 1;	//    29
} OSD4_CTRL_MAIN;

/*-----------------------------------------------------------------------------
	0x0004 osd4_base_addr ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_base_addr                   ;   	// 31: 0
} OSD4_BASE_ADDR;

/*-----------------------------------------------------------------------------
	0x0008 osd4_ctrl_swap ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_bbs                         : 1,	//     0
	osd_bqws                        : 1,	//     1
	osd_bhws                        : 1,	//     2
	                                : 1,	//     3 reserved
	osd_pbs                         : 1,	//     4
	osd_pqws                        : 1,	//     5
	osd_phws                        : 1,	//     6
	                                : 1,	//     7 reserved
	osd_hbs                         : 1,	//     8
	osd_hqws                        : 1,	//     9
	osd_hhws                        : 1;	//    10
} OSD4_CTRL_SWAP;

/*-----------------------------------------------------------------------------
	0x000c osd4_ctrl_pdec ''
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
} OSD4_CTRL_PDEC;

/*-----------------------------------------------------------------------------
	0x0010 osd4_ctrl_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_crsr_v_x2_sel               : 1,	//     0
	reg_crsr_h_x2_sel               : 1,	//     1
	reg_crsr_v_x2_en                : 1,	//     2
	reg_crsr_h_x2_en                : 1,	//     3
	                                : 1,	//     4 reserved
	reg_monitor_mode                : 1,	//     5
	                                : 9,	//  6:14 reserved
	reg_cursor_urgency_th           :16,	// 15:30
	reg_cursor_urgency_th_en        : 1;	//    31
} OSD4_CTRL_SCALER;

/*-----------------------------------------------------------------------------
	0x0014 osd4_info_scaler ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	status_line_memory              :16;	//  0:15
} OSD4_INFO_SCALER;

/*-----------------------------------------------------------------------------
	0x0018 osd4_ctrl_path ''
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
} OSD4_CTRL_PATH;

/*-----------------------------------------------------------------------------
	0x001c osd4_ctrl_ckey_ctrl_0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_r_th1                  : 8,	//  0: 7
	reg_ckey_r_th0                  : 8,	//  8:15
	reg_ckey_a_th1                  : 8,	// 16:23
	reg_ckey_a_th0                  : 8;	// 24:31
} OSD4_CTRL_CKEY_CTRL_0;

/*-----------------------------------------------------------------------------
	0x0020 osd4_ctrl_hdr0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ypos                    :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_xpos                    :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_color_key_en            : 1;	//    31
} OSD4_CTRL_HDR0;

/*-----------------------------------------------------------------------------
	0x0024 osd4_ctrl_hdr1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_mem                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_mem                   :12;	// 16:27
} OSD4_CTRL_HDR1;

/*-----------------------------------------------------------------------------
	0x0028 osd4_ctrl_hdr2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_h_out                   :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_hdr_w_out                   :12,	// 16:27
	                                : 3,	// 28:30 reserved
	osd_hdr_pixel_order             : 1;	//    31
} OSD4_CTRL_HDR2;

/*-----------------------------------------------------------------------------
	0x002c osd4_ctrl_hdr3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_wpl                     :16,	//  0:15
	osd_hdr_global_alpha            : 8,	// 16:23
	osd_hdr_format                  : 4,	// 24:27
	osd_hdr_depth                   : 3,	// 28:30
	osd_hdr_global_alpha_en         : 1;	//    31
} OSD4_CTRL_HDR3;

/*-----------------------------------------------------------------------------
	0x0030 osd4_ctrl_hdr4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_data_b                 : 8,	//  0: 7
	reg_ckey_data_g                 : 8,	//  8:15
	reg_ckey_data_r                 : 8,	// 16:23
	reg_ckey_data_a                 : 8;	// 24:31
} OSD4_CTRL_HDR4;

/*-----------------------------------------------------------------------------
	0x0034 osd4_ctrl_hdr5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_plte                ;   	// 31: 0
} OSD4_CTRL_HDR5;

/*-----------------------------------------------------------------------------
	0x0038 osd4_ctrl_hdr6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdr_ptr_bmp                 ;   	// 31: 0
} OSD4_CTRL_HDR6;

/*-----------------------------------------------------------------------------
	0x003c osd4_ctrl_ckey_ctrl_1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_ckey_b_th1                  : 8,	//  0: 7
	reg_ckey_b_th0                  : 8,	//  8:15
	reg_ckey_g_th1                  : 8,	// 16:23
	reg_ckey_g_th0                  : 8;	// 24:31
} OSD4_CTRL_CKEY_CTRL_1;

/*-----------------------------------------------------------------------------
	0x0040 osd4_ctrl_sync0 ''
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
} OSD4_CTRL_SYNC0;

/*-----------------------------------------------------------------------------
	0x0044 osd4_ctrl_sync1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_disp_h                 :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_disp_w                 :13;	// 16:28
} OSD4_CTRL_SYNC1;

/*-----------------------------------------------------------------------------
	0x0048 osd4_ctrl_sync2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_r_3d_disparity_value        : 8,	//  0: 7
	osd_r_3d_disparity_sign         : 1,	//     8
	                                : 7,	//  9:15 reserved
	osd_l_3d_disparity_value        : 8,	// 16:23
	osd_l_3d_disparity_sign         : 1;	//    24
} OSD4_CTRL_SYNC2;

/*-----------------------------------------------------------------------------
	0x004c osd4_ctrl_sync3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_ctrl_3d_blank               ;   	// 31: 0
} OSD4_CTRL_SYNC3;

/*-----------------------------------------------------------------------------
	0x0050 osd4_ctrl_sync4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_vact_video             :12,	//  0:11
	                                : 4,	// 12:15 reserved
	osd_sync_vact_space             :12;	// 16:27
} OSD4_CTRL_SYNC4;

/*-----------------------------------------------------------------------------
	0x0054 osd4_ctrl_sync5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_sync_reserved               ;   	// 31: 0
} OSD4_CTRL_SYNC5;

/*-----------------------------------------------------------------------------
	0x0060 reg_osd0_csc_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef1                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef0                   :15;	// 16:30
} REG_OSD0_CSC_CTRL0;

/*-----------------------------------------------------------------------------
	0x0064 reg_osd0_csc_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef3                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef2                   :15;	// 16:30
} REG_OSD0_CSC_CTRL1;

/*-----------------------------------------------------------------------------
	0x0068 reg_osd0_csc_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef5                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef4                   :15;	// 16:30
} REG_OSD0_CSC_CTRL2;

/*-----------------------------------------------------------------------------
	0x006c reg_osd0_csc_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef7                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef6                   :15;	// 16:30
} REG_OSD0_CSC_CTRL3;

/*-----------------------------------------------------------------------------
	0x0070 reg_osd0_csc_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reg_1x3_coef8                   :15;	// 16:30
} REG_OSD0_CSC_CTRL4;

/*-----------------------------------------------------------------------------
	0x0074 reg_osd0_csc_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst1                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst0                   :11;	// 16:26
} REG_OSD0_CSC_CTRL5;

/*-----------------------------------------------------------------------------
	0x0078 reg_osd0_csc_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst3                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst2                   :11;	// 16:26
} REG_OSD0_CSC_CTRL6;

/*-----------------------------------------------------------------------------
	0x007c reg_osd0_csc_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst5                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst4                   :11;	// 16:26
} REG_OSD0_CSC_CTRL7;

/*-----------------------------------------------------------------------------
	0x0080 reg_osd1_csc_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef1                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef0                   :15;	// 16:30
} REG_OSD1_CSC_CTRL0;

/*-----------------------------------------------------------------------------
	0x0084 reg_osd1_csc_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef3                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef2                   :15;	// 16:30
} REG_OSD1_CSC_CTRL1;

/*-----------------------------------------------------------------------------
	0x0088 reg_osd1_csc_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef5                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef4                   :15;	// 16:30
} REG_OSD1_CSC_CTRL2;

/*-----------------------------------------------------------------------------
	0x008c reg_osd1_csc_ctrl3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_coef7                   :15,	//  0:14
	                                : 1,	//    15 reserved
	reg_1x3_coef6                   :15;	// 16:30
} REG_OSD1_CSC_CTRL3;

/*-----------------------------------------------------------------------------
	0x0090 reg_osd1_csc_ctrl4 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reg_1x3_coef8                   :15;	// 16:30
} REG_OSD1_CSC_CTRL4;

/*-----------------------------------------------------------------------------
	0x0094 reg_osd1_csc_ctrl5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst1                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst0                   :11;	// 16:26
} REG_OSD1_CSC_CTRL5;

/*-----------------------------------------------------------------------------
	0x0098 reg_osd1_csc_ctrl6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst3                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst2                   :11;	// 16:26
} REG_OSD1_CSC_CTRL6;

/*-----------------------------------------------------------------------------
	0x009c reg_osd1_csc_ctrl7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_1x3_ofst5                   :11,	//  0:10
	                                : 5,	// 11:15 reserved
	reg_1x3_ofst4                   :11;	// 16:26
} REG_OSD1_CSC_CTRL7;

/*-----------------------------------------------------------------------------
	0x00a0 osd_sosd_csc_ctrl00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_en                 : 1;	//     0
} OSD_SOSD_CSC_CTRL00;

/*-----------------------------------------------------------------------------
	0x00a4 osd_sosd_csc_ctrl01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_coef1              :16,	//  0:15
	reg_sosd_csc_coef0              :16;	// 16:31
} OSD_SOSD_CSC_CTRL01;

/*-----------------------------------------------------------------------------
	0x00a8 osd_sosd_csc_ctrl02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_coef3              :16,	//  0:15
	reg_sosd_csc_coef2              :16;	// 16:31
} OSD_SOSD_CSC_CTRL02;

/*-----------------------------------------------------------------------------
	0x00ac osd_sosd_csc_ctrl03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_coef5              :16,	//  0:15
	reg_sosd_csc_coef4              :16;	// 16:31
} OSD_SOSD_CSC_CTRL03;

/*-----------------------------------------------------------------------------
	0x00b0 osd_sosd_csc_ctrl04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_coef7              :16,	//  0:15
	reg_sosd_csc_coef6              :16;	// 16:31
} OSD_SOSD_CSC_CTRL04;

/*-----------------------------------------------------------------------------
	0x00b4 osd_sosd_csc_ctrl05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reg_sosd_csc_coef8              :16;	// 16:31
} OSD_SOSD_CSC_CTRL05;

/*-----------------------------------------------------------------------------
	0x00b8 osd_sosd_csc_ctrl06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst0              :17;	//  0:16
} OSD_SOSD_CSC_CTRL06;

/*-----------------------------------------------------------------------------
	0x00bc osd_sosd_csc_ctrl07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst1              :17;	//  0:16
} OSD_SOSD_CSC_CTRL07;

/*-----------------------------------------------------------------------------
	0x00c0 osd_sosd_csc_ctrl08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst2              :17;	//  0:16
} OSD_SOSD_CSC_CTRL08;

/*-----------------------------------------------------------------------------
	0x00c4 osd_sosd_csc_ctrl09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst3              :17;	//  0:16
} OSD_SOSD_CSC_CTRL09;

/*-----------------------------------------------------------------------------
	0x00c8 osd_sosd_csc_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst4              :17;	//  0:16
} OSD_SOSD_CSC_CTRL10;

/*-----------------------------------------------------------------------------
	0x00cc osd_sosd_csc_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_sosd_csc_ofst5              :17;	//  0:16
} OSD_SOSD_CSC_CTRL11;

/*-----------------------------------------------------------------------------
	0x0000 osd_hdrui_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_dtm_en                : 1;	//     0
} OSD_HDRUI_CTRL;

/*-----------------------------------------------------------------------------
	0x0020 osd_hdrui_hue_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_hue_prsv_en                 : 1,	//     0
	                                : 3,	//  1: 3 reserved
	reg_sat_prsv_en                 : 1,	//     4
	                                :11,	//  5:15 reserved
	reg_sat_prsv_ratio              : 8,	// 16:23
	reg_hue_prsv_ratio              : 8;	// 24:31
} OSD_HDRUI_HUE_CTRL;

/*-----------------------------------------------------------------------------
	0x0024 osd_hdrui_size ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_height                :13,	//  0:12
	                                : 3,	// 13:15 reserved
	osd_hdrui_width                 :13;	// 16:28
} OSD_HDRUI_SIZE;

/*-----------------------------------------------------------------------------
	0x0028 osd_hdrui_dither_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_dither_8to10_en       : 1,	//     0
	                                : 3,	//  1: 3 reserved
	osd_hdrui_dither_10to12_debug_en: 1,	//     4
	                                : 3,	//  5: 7 reserved
	osd_hdrui_dither_10to12_debug_va: 2,	//  8: 9
	                                : 2,	// 10:11 reserved
	osd_hdrui_dither_8to10_mode     : 2,	// 12:13
	                                : 2,	// 14:15 reserved
	osd_hdrui_dither_8to10_debug_en : 1,	//    16
	                                : 3,	// 17:19 reserved
	osd_hdrui_dither_8to10_debug_val: 2;	// 20:21
} OSD_HDRUI_DITHER_CTRL0;

/*-----------------------------------------------------------------------------
	0x0030 osd_hdrui_dither_ctrl2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_dither_12to10_dither_e: 1,	//     0
	                                : 1,	//     1 reserved
	osd_hdrui_dither_12to10_dither_f: 1,	//     2
	osd_hdrui_dither_12to10_dither_d: 1,	//     3
	osd_hdrui_dither_12to10_bit_mode: 2,	//  4: 5
	osd_hdrui_dither_12to10_clock_ga: 1;	//     6
} OSD_HDRUI_DITHER_CTRL2;

/*-----------------------------------------------------------------------------
	0x0034 osd_hdrui_lut0_ind_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD_HDRUI_LUT0_IND_CTRL0;

/*-----------------------------------------------------------------------------
	0x0038 osd_hdrui_lut0_ind_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_lut0_ind_data         ;   	// 31: 0
} OSD_HDRUI_LUT0_IND_DATA0;

/*-----------------------------------------------------------------------------
	0x003c osd_hdrui_lut1_ind_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD_HDRUI_LUT1_IND_CTRL0;

/*-----------------------------------------------------------------------------
	0x0040 osd_hdrui_lut1_ind_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_lut1_ind_data         ;   	// 31: 0
} OSD_HDRUI_LUT1_IND_DATA0;

/*-----------------------------------------------------------------------------
	0x0044 osd_hdrui_lut2_ind_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	r_ind_addr_ai                   :11,	//  0:10
	                                : 1,	//    11 reserved
	r_ind_ai                        : 1,	//    12
	                                : 2,	// 13:14 reserved
	r_ind_load                      : 1;	//    15
} OSD_HDRUI_LUT2_IND_CTRL0;

/*-----------------------------------------------------------------------------
	0x0048 osd_hdrui_lut2_ind_data0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	osd_hdrui_lut2_ind_data         ;   	// 31: 0
} OSD_HDRUI_LUT2_IND_DATA0;

/*-----------------------------------------------------------------------------
	0x0064 osd_hdrui_lut0_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	luminance_lut_enable            : 1,	//     0
	                                : 3,	//  1: 3 reserved
	window01_enable                 : 1,	//     4
	window0_enable                  : 1,	//     5
	window1_enable                  : 1,	//     6
	window_acquire                  : 1,	//     7
	window_mode_enable              : 1,	//     8
	                                : 7,	//  9:15 reserved
	window_inout_sel                : 1,	//    16
	                                : 3,	// 17:19 reserved
	window_cg_disable               : 1;	//    20
} OSD_HDRUI_LUT0_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0068 osd_hdrui_lut0_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w0_x0                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w0_y0                       :12;	// 16:27
} OSD_HDRUI_LUT0_CTRL_01;

/*-----------------------------------------------------------------------------
	0x006c osd_hdrui_lut0_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w0_x1                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w0_y1                       :12;	// 16:27
} OSD_HDRUI_LUT0_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0070 osd_hdrui_lut0_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w1_x0                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w1_y0                       :12;	// 16:27
} OSD_HDRUI_LUT0_CTRL_03;

/*-----------------------------------------------------------------------------
	0x0074 osd_hdrui_lut0_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w1_x1                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w1_y1                       :12;	// 16:27
} OSD_HDRUI_LUT0_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0078 osd_hdrui_lut0_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hif_llut_wdata_y_33rd           :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	hif_llut_wdata_x_33rd           :10;	// 16:25
} OSD_HDRUI_LUT0_CTRL_05;

/*-----------------------------------------------------------------------------
	0x007c osd_hdrui_lut1_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	luminance_lut_enable            : 1,	//     0
	                                : 3,	//  1: 3 reserved
	window01_enable                 : 1,	//     4
	window0_enable                  : 1,	//     5
	window1_enable                  : 1,	//     6
	window_acquire                  : 1,	//     7
	window_mode_enable              : 1,	//     8
	                                : 7,	//  9:15 reserved
	window_inout_sel                : 1,	//    16
	                                : 3,	// 17:19 reserved
	window_cg_disable               : 1;	//    20
} OSD_HDRUI_LUT1_CTRL_00;

/*-----------------------------------------------------------------------------
	0x0080 osd_hdrui_lut1_ctrl_01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w0_x0                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w0_y0                       :12;	// 16:27
} OSD_HDRUI_LUT1_CTRL_01;

/*-----------------------------------------------------------------------------
	0x0084 osd_hdrui_lut1_ctrl_02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w0_x1                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w0_y1                       :12;	// 16:27
} OSD_HDRUI_LUT1_CTRL_02;

/*-----------------------------------------------------------------------------
	0x0088 osd_hdrui_lut1_ctrl_03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w1_x0                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w1_y0                       :12;	// 16:27
} OSD_HDRUI_LUT1_CTRL_03;

/*-----------------------------------------------------------------------------
	0x008c osd_hdrui_lut1_ctrl_04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	win_w1_x1                       :12,	//  0:11
	                                : 4,	// 12:15 reserved
	win_w1_y1                       :12;	// 16:27
} OSD_HDRUI_LUT1_CTRL_04;

/*-----------------------------------------------------------------------------
	0x0090 osd_hdrui_lut1_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hif_llut_wdata_y_33rd           :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	hif_llut_wdata_x_33rd           :10;	// 16:25
} OSD_HDRUI_LUT1_CTRL_05;

/*-----------------------------------------------------------------------------
	0x0094 osd_hdrui_lut2_ctrl_00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	luminance_lut_enable            : 1,	//     0
	                                : 3,	//  1: 3 reserved
	window01_enable                 : 1,	//     4
	window0_enable                  : 1,	//     5
	window1_enable                  : 1,	//     6
	window_acquire                  : 1,	//     7
	window_mode_enable              : 1,	//     8
	                                : 7,	//  9:15 reserved
	window_inout_sel                : 1,	//    16
	                                : 3,	// 17:19 reserved
	window_cg_disable               : 1;	//    20
} OSD_HDRUI_LUT2_CTRL_00;

/*-----------------------------------------------------------------------------
	0x00a8 osd_hdrui_lut2_ctrl_05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hif_llut_wdata_y_33rd           :10,	//  0: 9
	                                : 6,	// 10:15 reserved
	hif_llut_wdata_x_33rd           :10;	// 16:25
} OSD_HDRUI_LUT2_CTRL_05;

/*-----------------------------------------------------------------------------
	0x00ac osd_hdrui_yc2rgb_ctrl00 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_en                  : 1;	//     0
} OSD_HDRUI_YC2RGB_CTRL00;

/*-----------------------------------------------------------------------------
	0x00b0 osd_hdrui_yc2rgb_ctrl01 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_coef1               :16,	//  0:15
	reg_yuv2rgb_coef0               :16;	// 16:31
} OSD_HDRUI_YC2RGB_CTRL01;

/*-----------------------------------------------------------------------------
	0x00b4 osd_hdrui_yc2rgb_ctrl02 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_coef3               :16,	//  0:15
	reg_yuv2rgb_coef2               :16;	// 16:31
} OSD_HDRUI_YC2RGB_CTRL02;

/*-----------------------------------------------------------------------------
	0x00b8 osd_hdrui_yc2rgb_ctrl03 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_coef5               :16,	//  0:15
	reg_yuv2rgb_coef4               :16;	// 16:31
} OSD_HDRUI_YC2RGB_CTRL03;

/*-----------------------------------------------------------------------------
	0x00bc osd_hdrui_yc2rgb_ctrl04 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_coef7               :16,	//  0:15
	reg_yuv2rgb_coef6               :16;	// 16:31
} OSD_HDRUI_YC2RGB_CTRL04;

/*-----------------------------------------------------------------------------
	0x00c0 osd_hdrui_yc2rgb_ctrl05 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	                                :16,	//  0:15 reserved
	reg_yuv2rgb_coef8               :16;	// 16:31
} OSD_HDRUI_YC2RGB_CTRL05;

/*-----------------------------------------------------------------------------
	0x00c4 osd_hdrui_yc2rgb_ctrl06 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst0               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL06;

/*-----------------------------------------------------------------------------
	0x00c8 osd_hdrui_yc2rgb_ctrl07 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst1               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL07;

/*-----------------------------------------------------------------------------
	0x00cc osd_hdrui_yc2rgb_ctrl08 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst2               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL08;

/*-----------------------------------------------------------------------------
	0x00d0 osd_hdrui_yc2rgb_ctrl09 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst3               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL09;

/*-----------------------------------------------------------------------------
	0x00d4 osd_hdrui_yc2rgb_ctrl10 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst4               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL10;

/*-----------------------------------------------------------------------------
	0x00d8 osd_hdrui_yc2rgb_ctrl11 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_yuv2rgb_ofst5               :17;	//  0:16
} OSD_HDRUI_YC2RGB_CTRL11;


// (NOTE) 아래 자동 생성된 레지스터 그룹은 참조만 할것
#if 0
typedef struct {
	OSD_STATUS_MON_CFG              	osd_status_mon_cfg              ;	// 0x0000 : ''
	OSD_STATUS_MON_POS              	osd_status_mon_pos              ;	// 0x0004 : ''
	OSD_STATUS_PIC_CNT              	osd_status_pic_cnt              ;	// 0x0008 : ''
	OSD_STATUS_MIXER_LINE           	osd_status_mixer_line           ;	// 0x000c : ''
	OSD_STATUS_MON_DATA0            	osd_status_mon_data0            ;	// 0x0010 : ''
	OSD_STATUS_MON_DATA1            	osd_status_mon_data1            ;	// 0x0014 : ''
	OSD_STATUS_MON_DATA2            	osd_status_mon_data2            ;	// 0x0018 : ''
	OSD_STATUS_MON_DATA3            	osd_status_mon_data3            ;	// 0x001c : ''
	OSD_STATUS_MON_DATA4            	osd_status_mon_data4            ;	// 0x0020 : ''
	OSD_STATUS_MON_DATA5            	osd_status_mon_data5            ;	// 0x0024 : ''
	OSD_STATUS_MON_DATA6            	osd_status_mon_data6            ;	// 0x0028 : ''
	OSD_STATUS_MON_DATA7            	osd_status_mon_data7            ;	// 0x002c : ''
	OSD_STATUS_MON_DATA8            	osd_status_mon_data8            ;	// 0x0030 : ''
	OSD_STATUS_MON_DATA9            	osd_status_mon_data9            ;	// 0x0034 : ''
	OSD_STATUS_MON_DATAA            	osd_status_mon_dataa            ;	// 0x0038 : ''
	OSD_STATUS_MON_DATAB            	osd_status_mon_datab            ;	// 0x003c : ''
} OSD_STATUS_REG_T;
/* 16 regs, 16 types */

typedef struct {
	OSD_COMMON_PLTE_SEL             	osd_common_plte_sel             ;	// 0x0000 : ''
	OSD_COMMON_CTRL_IRQ             	osd_common_ctrl_irq             ;	// 0x0004 : ''
	OSD_COMMON_CTRL_PIC_INIT        	osd_common_ctrl_pic_init        ;	// 0x0008 : ''
	OSD_COMMON_CTRL_PIC_TIMER       	osd_common_ctrl_pic_timer       ;	// 0x000c : ''
	OSD0_COMMON_DISP_SIZE           	osd0_common_disp_size           ;	// 0x0010 : ''
	OSD1_COMMON_DISP_SIZE           	osd1_common_disp_size           ;	// 0x0014 : ''
	OSD2_COMMON_DISP_SIZE           	osd2_common_disp_size           ;	// 0x0018 : ''
	OSD3_COMMON_DISP_SIZE           	osd3_common_disp_size           ;	// 0x001c : ''
	OSD4_COMMON_DISP_SIZE           	osd4_common_disp_size           ;	// 0x0020 : ''
	OSD5_COMMON_DISP_SIZE           	osd5_common_disp_size           ;	// 0x0024 : ''
	OSD6_COMMON_DISP_SIZE           	osd6_common_disp_size           ;	// 0x0028 : ''
	OSD7_COMMON_DISP_SIZE           	osd7_common_disp_size           ;	// 0x002c : ''
	OSD_CG_CTRL                     	osd_cg_ctrl                     ;	// 0x0030 : ''
} OSD_COMMON_REG_T;
/* 13 regs, 13 types */

typedef struct {
	CTRL_SOSD_MIXER_DISP_SIZE       	ctrl_sosd_mixer_disp_size       ;	// 0x0000 : ''
	CTRL_SOSD_MIXER_OUTPUT          	ctrl_sosd_mixer_output          ;	// 0x0004 : ''
	CTRL_SOSD_MIXER_AWB             	ctrl_sosd_mixer_awb             ;	// 0x0008 : ''
	CTRL_SOSD_MIXER_MIRACAST_CTRL   	ctrl_sosd_mixer_miracast_ctrl   ;	// 0x000c : ''
	CTRL_SOSD_MIXER_CTRL_ALPHA      	ctrl_sosd_mixer_ctrl_alpha      ;	// 0x0010 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL0     	ctrl_sosd_mixer_force_ctrl0     ;	// 0x0014 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL1     	ctrl_sosd_mixer_force_ctrl1     ;	// 0x0018 : ''
	CTRL_SOSD_MIXER_HOLE            	ctrl_sosd_mixer_hole            ;	// 0x001c : ''
	CTRL_SOSD_MIXER_MUX0            	ctrl_sosd_mixer_mux0            ;	// 0x0020 : ''
	CTRL_SOSD_MIXER_MUX1            	ctrl_sosd_mixer_mux1            ;	// 0x0024 : ''
	UINT32                          	ctrl_sosd_mixer_mux2            ;	// 0x0028 : ''
	CTRL_SOSD_MIXER_MUX3            	ctrl_sosd_mixer_mux3            ;	// 0x002c : ''
	CTRL_SOSD_MIXER_MUX4            	ctrl_sosd_mixer_mux4            ;	// 0x0030 : ''
	CTRL_SOSD_MIXER_MUX5            	ctrl_sosd_mixer_mux5            ;	// 0x0034 : ''
	CTRL_SOSD_MIXER_MUX6            	ctrl_sosd_mixer_mux6            ;	// 0x0038 : ''
	CTRL_SOSD_MIXER_MUX7            	ctrl_sosd_mixer_mux7            ;	// 0x003c : ''
	CTRL_SOSD_MIXER_MUX8            	ctrl_sosd_mixer_mux8            ;	// 0x0040 : ''
	CTRL_SOSD_MIXER_MUX9            	ctrl_sosd_mixer_mux9            ;	// 0x0044 : ''
	CTRL_SOSD_MIXER_MUXA            	ctrl_sosd_mixer_muxa            ;	// 0x0048 : ''
	CTRL_SOSD_MIXER_MUXB            	ctrl_sosd_mixer_muxb            ;	// 0x004c : ''
	CTRL_SOSD_MIXER_MUXC            	ctrl_sosd_mixer_muxc            ;	// 0x0050 : ''
	CTRL_SOSD_MIXER_MUXD            	ctrl_sosd_mixer_muxd            ;	// 0x0054 : ''
	CTRL_SOSD_MIXER_MUXE            	ctrl_sosd_mixer_muxe            ;	// 0x0058 : ''
	CTRL_SOSD_MIXER_MUXF            	ctrl_sosd_mixer_muxf            ;	// 0x005c : ''
} OSD_SOSD_REG_T;
/* 24 regs, 24 types */

typedef struct {
	CTRL_BOSD0_MIXER_DISP_SIZE      	ctrl_bosd0_mixer_disp_size      ;	// 0x0000 : ''
	CTRL_BOSD0_MIXER_OUTPUT         	ctrl_bosd0_mixer_output         ;	// 0x0004 : ''
	CTRL_BOSD0_MIXER_AWB            	ctrl_bosd0_mixer_awb            ;	// 0x0008 : ''
	UINT32                          	                 __rsvd_00[   4];	// 0x000c ~ 0x0018
	CTRL_BOSD0_MIXER_HOLE           	ctrl_bosd0_mixer_hole           ;	// 0x001c : ''
	CTRL_BOSD0_MIXER_MUX0           	ctrl_bosd0_mixer_mux0           ;	// 0x0020 : ''
	CTRL_BOSD0_MIXER_MUX1           	ctrl_bosd0_mixer_mux1           ;	// 0x0024 : ''
	CTRL_BOSD0_MIXER_MUX2           	ctrl_bosd0_mixer_mux2           ;	// 0x0028 : ''
	CTRL_BOSD0_MIXER_MUX3           	ctrl_bosd0_mixer_mux3           ;	// 0x002c : ''
	CTRL_BOSD0_MIXER_MUX4           	ctrl_bosd0_mixer_mux4           ;	// 0x0030 : ''
	CTRL_BOSD0_MIXER_MUX5           	ctrl_bosd0_mixer_mux5           ;	// 0x0034 : ''
	CTRL_BOSD0_MIXER_MUX6           	ctrl_bosd0_mixer_mux6           ;	// 0x0038 : ''
	CTRL_BOSD0_MIXER_MUX7           	ctrl_bosd0_mixer_mux7           ;	// 0x003c : ''
	CTRL_BOSD0_MIXER_MUX8           	ctrl_bosd0_mixer_mux8           ;	// 0x0040 : ''
	CTRL_BOSD0_MIXER_MUX9           	ctrl_bosd0_mixer_mux9           ;	// 0x0044 : ''
	CTRL_BOSD0_MIXER_MUXA           	ctrl_bosd0_mixer_muxa           ;	// 0x0048 : ''
	CTRL_BOSD0_MIXER_MUXB           	ctrl_bosd0_mixer_muxb           ;	// 0x004c : ''
	CTRL_BOSD0_MIXER_MUXC           	ctrl_bosd0_mixer_muxc           ;	// 0x0050 : ''
	CTRL_BOSD0_MIXER_MUXD           	ctrl_bosd0_mixer_muxd           ;	// 0x0054 : ''
	CTRL_BOSD0_MIXER_MUXE           	ctrl_bosd0_mixer_muxe           ;	// 0x0058 : ''
	CTRL_BOSD0_MIXER_MUXF           	ctrl_bosd0_mixer_muxf           ;	// 0x005c : ''
	CTRL_BOSD0_MIXER_LED_ALPHA      	ctrl_bosd0_mixer_led_alpha      ;	// 0x0060 : ''
	UINT32                          	                 __rsvd_01[   7];	// 0x0064 ~ 0x007c
	CTRL_BOSD1_MIXER_DISP_SIZE      	ctrl_bosd1_mixer_disp_size      ;	// 0x0080 : ''
	CTRL_BOSD1_MIXER_OUTPUT         	ctrl_bosd1_mixer_output         ;	// 0x0084 : ''
	CTRL_BOSD1_MIXER_AWB            	ctrl_bosd1_mixer_awb            ;	// 0x0088 : ''
	CTRL_BOSD1_MIXER_MIRACAST_CTRL  	ctrl_bosd1_mixer_miracast_ctrl  ;	// 0x008c : ''
	UINT32                          	                 __rsvd_02[   3];	// 0x0090 ~ 0x0098
	CTRL_BOSD1_MIXER_HOLE           	ctrl_bosd1_mixer_hole           ;	// 0x009c : ''
	CTRL_BOSD1_MIXER_MUX0           	ctrl_bosd1_mixer_mux0           ;	// 0x00a0 : ''
	CTRL_BOSD1_MIXER_MUX1           	ctrl_bosd1_mixer_mux1           ;	// 0x00a4 : ''
	CTRL_BOSD1_MIXER_MUX2           	ctrl_bosd1_mixer_mux2           ;	// 0x00a8 : ''
	CTRL_BOSD1_MIXER_MUX3           	ctrl_bosd1_mixer_mux3           ;	// 0x00ac : ''
	CTRL_BOSD1_MIXER_MUX4           	ctrl_bosd1_mixer_mux4           ;	// 0x00b0 : ''
	CTRL_BOSD1_MIXER_MUX5           	ctrl_bosd1_mixer_mux5           ;	// 0x00b4 : ''
	CTRL_BOSD1_MIXER_MUX6           	ctrl_bosd1_mixer_mux6           ;	// 0x00b8 : ''
	CTRL_BOSD1_MIXER_MUX7           	ctrl_bosd1_mixer_mux7           ;	// 0x00bc : ''
	CTRL_BOSD1_MIXER_MUX8           	ctrl_bosd1_mixer_mux8           ;	// 0x00c0 : ''
	CTRL_BOSD1_MIXER_MUX9           	ctrl_bosd1_mixer_mux9           ;	// 0x00c4 : ''
	CTRL_BOSD1_MIXER_MUXA           	ctrl_bosd1_mixer_muxa           ;	// 0x00c8 : ''
	CTRL_BOSD1_MIXER_MUXB           	ctrl_bosd1_mixer_muxb           ;	// 0x00cc : ''
	CTRL_BOSD1_MIXER_MUXC           	ctrl_bosd1_mixer_muxc           ;	// 0x00d0 : ''
	CTRL_BOSD1_MIXER_MUXD           	ctrl_bosd1_mixer_muxd           ;	// 0x00d4 : ''
	CTRL_BOSD1_MIXER_MUXE           	ctrl_bosd1_mixer_muxe           ;	// 0x00d8 : ''
	CTRL_BOSD1_MIXER_MUXF           	ctrl_bosd1_mixer_muxf           ;	// 0x00dc : ''
	CTRL_BOSD1_MIXER_LED_ALPHA      	ctrl_bosd1_mixer_led_alpha      ;	// 0x00e0 : ''
	CTRL_BOSD1_MIXER_OBJ_ALPHA      	ctrl_bosd1_mixer_obj_alpha      ;	// 0x00e4 : ''
} OSD_BOSD_REG_T;
/* 44 regs, 44 types */

typedef struct {
	OSD0_CTRL_MAIN                  	osd0_ctrl_main                  ;	// 0x0000 : ''
	UINT32                          	osd0_base_addr                  ;	// 0x0004 : ''
	OSD0_CTRL_SWAP                  	osd0_ctrl_swap                  ;	// 0x0008 : ''
	OSD0_CTRL_PDEC                  	osd0_ctrl_pdec                  ;	// 0x000c : ''
	OSD0_CTRL_SCALER                	osd0_ctrl_scaler                ;	// 0x0010 : ''
	OSD0_INFO_SCALER                	osd0_info_scaler                ;	// 0x0014 : ''
	OSD0_CTRL_PATH                  	osd0_ctrl_path                  ;	// 0x0018 : ''
	OSD0_CTRL_CKEY_CTRL_0           	osd0_ctrl_ckey_ctrl_0           ;	// 0x001c : ''
	OSD0_CTRL_HDR0                  	osd0_ctrl_hdr0                  ;	// 0x0020 : ''
	OSD0_CTRL_HDR1                  	osd0_ctrl_hdr1                  ;	// 0x0024 : ''
	OSD0_CTRL_HDR2                  	osd0_ctrl_hdr2                  ;	// 0x0028 : ''
	OSD0_CTRL_HDR3                  	osd0_ctrl_hdr3                  ;	// 0x002c : ''
	OSD0_CTRL_HDR4                  	osd0_ctrl_hdr4                  ;	// 0x0030 : ''
	OSD0_CTRL_HDR5                  	osd0_ctrl_hdr5                  ;	// 0x0034 : ''
	OSD0_CTRL_HDR6                  	osd0_ctrl_hdr6                  ;	// 0x0038 : ''
	OSD0_CTRL_CKEY_CTRL_1           	osd0_ctrl_ckey_ctrl_1           ;	// 0x003c : ''

	OSD0_CTRL_SYNC0                 	osd0_ctrl_sync0                 ;	// 0x0040 : ''
	OSD0_CTRL_SYNC1                 	osd0_ctrl_sync1                 ;	// 0x0044 : ''
	OSD0_CTRL_SYNC2                 	osd0_ctrl_sync2                 ;	// 0x0048 : ''
	OSD0_CTRL_SYNC3                 	osd0_ctrl_sync3                 ;	// 0x004c : ''
	OSD0_CTRL_SYNC4                 	osd0_ctrl_sync4                 ;	// 0x0050 : ''
	OSD0_CTRL_SYNC5                 	osd0_ctrl_sync5                 ;	// 0x0054 : ''

	OSD0_BITMAP_CTRL0               	osd0_bitmap_ctrl0               ;	// 0x0058 : ''
	OSD0_BITMAP_CTRL1               	osd0_bitmap_ctrl1               ;	// 0x005c : ''
	OSD0_VSP_BOSD_CTRL_0            	osd0_vsp_bosd_ctrl_0            ;	// 0x0060 : ''
	OSD0_VSP_BOSD_CTRL_1            	osd0_vsp_bosd_ctrl_1            ;	// 0x0064 : ''
	OSD0_VSP_SOSD_CTRL_0            	osd0_vsp_sosd_ctrl_0            ;	// 0x0068 : ''
	OSD0_VSP_SOSD_CTRL_1            	osd0_vsp_sosd_ctrl_1            ;	// 0x006c : ''
	OSD0_BITMAP_CTRL2               	osd0_bitmap_ctrl2               ;	// 0x0070 : ''
	OSD0_STATUS_ALPHA_50X50         	osd0_status_alpha_50x50         ;	// 0x0074 : ''
	OSD0_SCALER_STATUS_CTRL         	osd0_scaler_status_ctrl         ;	// 0x0078 : ''
	OSD0_OUT_BUF_STATUS             	osd0_out_buf_status             ;	// 0x007c : ''
	OSD0_CDC_CROP_CTRL_0            	osd0_cdc_crop_ctrl_0            ;	// 0x0080 : ''
	OSD0_CDC_CROP_CTRL_1            	osd0_cdc_crop_ctrl_1            ;	// 0x0084 : ''
	OSD0_CDC_CROP_CTRL_2            	osd0_cdc_crop_ctrl_2            ;	// 0x0088 : ''
	OSD0_CROP_CTRL_0                	osd0_crop_ctrl_0                ;	// 0x008c : ''
	OSD0_CROP_CTRL_1                	osd0_crop_ctrl_1                ;	// 0x0090 : ''
	OSD0_CROP_CTRL_2                	osd0_crop_ctrl_2                ;	// 0x0094 : ''
	OSD0_CROP_CTRL_3                	osd0_crop_ctrl_3                ;	// 0x0098 : ''
	OSD0_LSR_CTRL0                  	osd0_lsr_ctrl0                  ;	// 0x009c : ''
	OSD0_LSR_CTRL1                  	osd0_lsr_ctrl1                  ;	// 0x00a0 : ''
	OSD0_LSR_CTRL2                  	osd0_lsr_ctrl2                  ;	// 0x00a4 : ''
	OSD0_LSR_CTRL3                  	osd0_lsr_ctrl3                  ;	// 0x00a8 : ''
	OSD0_LSR_CTRL4                  	osd0_lsr_ctrl4                  ;	// 0x00ac : ''
	OSD0_LSR_CTRL5                  	osd0_lsr_ctrl5                  ;	// 0x00b0 : ''
	OSD0_LSR_CTRL6                  	osd0_lsr_ctrl6                  ;	// 0x00b4 : ''
	OSD0_POST_CROP_CTRL_0           	osd0_post_crop_ctrl_0           ;	// 0x00b8 : ''
	OSD0_POST_CROP_CTRL_1           	osd0_post_crop_ctrl_1           ;	// 0x00bc : ''
	OSD0_POST_CROP_CTRL_2           	osd0_post_crop_ctrl_2           ;	// 0x00c0 : ''
	OSD0_POST_CROP_CTRL_3           	osd0_post_crop_ctrl_3           ;	// 0x00c4 : ''
	OSD0_GSR_CTRL_0                 	osd0_gsr_ctrl_0                 ;	// 0x00c8 : ''
	OSD0_GSR_CTRL_1                 	osd0_gsr_ctrl_1                 ;	// 0x00cc : ''
	OSD0_GSR_CTRL_2                 	osd0_gsr_ctrl_2                 ;	// 0x00d0 : ''
	OSD0_GSR_CTRL_3                 	osd0_gsr_ctrl_3                 ;	// 0x00d4 : ''
	OSD0_GSR_IND_CTRL               	osd0_gsr_ind_ctrl               ;	// 0x00d8 : ''
	OSD0_GSR_IND_DATA               	osd0_gsr_ind_data               ;	// 0x00dc : ''
	OSD0_SHP_CG_CTRL                	osd0_shp_cg_ctrl                ;	// 0x00e0 : ''
	OSD0_LOCAL_ALPHA_CTRL_0         	osd0_local_alpha_ctrl_0         ;	// 0x00e4 : ''
	OSD0_LOCAL_ALPHA_CTRL_1         	osd0_local_alpha_ctrl_1         ;	// 0x00e8 : ''
	OSD0_LOCAL_ALPHA_CTRL_2         	osd0_local_alpha_ctrl_2         ;	// 0x00ec : ''
} OSD_IMAGE0_REG_T;
/* 60 regs, 60 types */

typedef struct {
	OSD0_1_CTRL_MAIN                	osd0_1_ctrl_main                ;	// 0x0000 : ''
	UINT32                          	osd0_1_base_addr                ;	// 0x0004 : ''
	OSD0_1_CTRL_SWAP                	osd0_1_ctrl_swap                ;	// 0x0008 : ''
	OSD0_1_CTRL_PDEC                	osd0_1_ctrl_pdec                ;	// 0x000c : ''
	UINT32                          	                 __rsvd_00[   3];	// 0x0010 ~ 0x0018
	OSD0_1_CTRL_CKEY_CTRL_0         	osd0_1_ctrl_ckey_ctrl_0         ;	// 0x001c : ''
	OSD0_1_CTRL_HDR0                	osd0_1_ctrl_hdr0                ;	// 0x0020 : ''
	OSD0_1_CTRL_HDR1                	osd0_1_ctrl_hdr1                ;	// 0x0024 : ''
	OSD0_1_CTRL_HDR2                	osd0_1_ctrl_hdr2                ;	// 0x0028 : ''
	OSD0_1_CTRL_HDR3                	osd0_1_ctrl_hdr3                ;	// 0x002c : ''
	OSD0_1_CTRL_HDR4                	osd0_1_ctrl_hdr4                ;	// 0x0030 : ''
	OSD0_1_CTRL_HDR5                	osd0_1_ctrl_hdr5                ;	// 0x0034 : ''
	OSD0_1_CTRL_HDR6                	osd0_1_ctrl_hdr6                ;	// 0x0038 : ''
	OSD0_1_CTRL_CKEY_CTRL_1         	osd0_1_ctrl_ckey_ctrl_1         ;	// 0x003c : ''

	REG_4K_OSD_MAIN_CTRL_0          	reg_4k_osd_main_ctrl_0          ;	// 0x0040 : ''
	REG_4K_OSD_MAIN_CTRL_1          	reg_4k_osd_main_ctrl_1          ;	// 0x0044 : ''
	REG_4K_OSD_MAIN_CTRL_2          	reg_4k_osd_main_ctrl_2          ;	// 0x0048 : ''
	REG_4K_OSD_MAIN_CTRL_3          	reg_4k_osd_main_ctrl_3          ;	// 0x004c : ''
	REG_OSD0_GSR_CTRL00             	reg_osd0_gsr_ctrl00             ;	// 0x0050 : ''
	REG_OSD0_GSR_CTRL01             	reg_osd0_gsr_ctrl01             ;	// 0x0054 : ''
	REG_OSD0_GSR_CTRL02             	reg_osd0_gsr_ctrl02             ;	// 0x0058 : ''
	REG_OSD0_GSR_CTRL03             	reg_osd0_gsr_ctrl03             ;	// 0x005c : ''
	REG_OSD0_GSR_CTRL04             	reg_osd0_gsr_ctrl04             ;	// 0x0060 : ''
	REG_OSD0_GSR_CTRL05             	reg_osd0_gsr_ctrl05             ;	// 0x0064 : ''
	REG_OSD0_GSR_CTRL06             	reg_osd0_gsr_ctrl06             ;	// 0x0068 : ''
	REG_OSD0_GSR_CTRL07             	reg_osd0_gsr_ctrl07             ;	// 0x006c : ''
	REG_OSD0_GSR_CTRL08             	reg_osd0_gsr_ctrl08             ;	// 0x0070 : ''
	REG_OSD0_GSR_CTRL09             	reg_osd0_gsr_ctrl09             ;	// 0x0074 : ''
	REG_OSD0_GSR_CTRL10             	reg_osd0_gsr_ctrl10             ;	// 0x0078 : ''
	REG_OSD0_GSR_CTRL11             	reg_osd0_gsr_ctrl11             ;	// 0x007c : ''
	REG_OSD0_ORD_CTRL00             	reg_osd0_ord_ctrl00             ;	// 0x0080 : ''
	REG_OSD0_ORD_CTRL01             	reg_osd0_ord_ctrl01             ;	// 0x0084 : ''
	REG_OSD0_ORD_CTRL02             	reg_osd0_ord_ctrl02             ;	// 0x0088 : ''
	REG_OSD0_ORD_CTRL03             	reg_osd0_ord_ctrl03             ;	// 0x008c : ''
	REG_OSD0_ORD_CTRL04             	reg_osd0_ord_ctrl04             ;	// 0x0090 : ''
	REG_OSD0_ORD_CTRL05             	reg_osd0_ord_ctrl05             ;	// 0x0094 : ''
	REG_OSD0_ORD_CTRL06             	reg_osd0_ord_ctrl06             ;	// 0x0098 : ''
	REG_OSD0_ORD_CTRL07             	reg_osd0_ord_ctrl07             ;	// 0x009c : ''
	REG_OSD0_ORD_CTRL08             	reg_osd0_ord_ctrl08             ;	// 0x00a0 : ''
	REG_OSD0_ORD_CTRL09             	reg_osd0_ord_ctrl09             ;	// 0x00a4 : ''
	REG_OSD0_ORD_CTRL10             	reg_osd0_ord_ctrl10             ;	// 0x00a8 : ''
	REG_OSD0_ORD_CTRL11             	reg_osd0_ord_ctrl11             ;	// 0x00ac : ''
	REG_OSD0_ORD_CTRL12             	reg_osd0_ord_ctrl12             ;	// 0x00b0 : ''
	REG_OSD0_ORD_CTRL13             	reg_osd0_ord_ctrl13             ;	// 0x00b4 : ''
	REG_OSD0_ORD_CTRL14             	reg_osd0_ord_ctrl14             ;	// 0x00b8 : ''
	REG_OSD0_ORD_CTRL15             	reg_osd0_ord_ctrl15             ;	// 0x00bc : ''
	REG_OSD0_ORD_CTRL16             	reg_osd0_ord_ctrl16             ;	// 0x00c0 : ''
	REG_OSD0_ORD_CTRL17             	reg_osd0_ord_ctrl17             ;	// 0x00c4 : ''
	REG_OSD0_ORD_CTRL18             	reg_osd0_ord_ctrl18             ;	// 0x00c8 : ''
	REG_OSD0_ORD_CTRL19             	reg_osd0_ord_ctrl19             ;	// 0x00cc : ''
	REG_OSD0_PDF_CTRL00             	reg_osd0_pdf_ctrl00             ;	// 0x00d0 : ''
	REG_OSD0_PDF_CTRL01             	reg_osd0_pdf_ctrl01             ;	// 0x00d4 : ''
	REG_OSD0_PDF_CTRL02             	reg_osd0_pdf_ctrl02             ;	// 0x00d8 : ''
	REG_OSD0_PDF_CTRL03             	reg_osd0_pdf_ctrl03             ;	// 0x00dc : ''
	REG_OSD0_PDF_CTRL04             	reg_osd0_pdf_ctrl04             ;	// 0x00e0 : ''
	REG_OSD0_PDF_CTRL05             	reg_osd0_pdf_ctrl05             ;	// 0x00e4 : ''
	REG_OSD0_PDF_IND_CTRL           	reg_osd0_pdf_ind_ctrl           ;	// 0x00e8 : ''
	REG_OSD0_PDF_IND_DATA_RD        	reg_osd0_pdf_ind_data_rd        ;	// 0x00ec : ''
} OSD_IMAGE0_1_REG_T;
/* 57 regs, 57 types */

typedef struct {
	OSD1_CTRL_MAIN                  	osd1_ctrl_main                  ;	// 0x0000 : ''
	UINT32                          	osd1_base_addr                  ;	// 0x0004 : ''
	OSD1_CTRL_SWAP                  	osd1_ctrl_swap                  ;	// 0x0008 : ''
	OSD1_CTRL_PDEC                  	osd1_ctrl_pdec                  ;	// 0x000c : ''
	OSD1_CTRL_SCALER                	osd1_ctrl_scaler                ;	// 0x0010 : ''
	OSD1_INFO_SCALER                	osd1_info_scaler                ;	// 0x0014 : ''
	OSD1_CTRL_PATH                  	osd1_ctrl_path                  ;	// 0x0018 : ''
	OSD1_CTRL_CKEY_CTRL_0           	osd1_ctrl_ckey_ctrl_0           ;	// 0x001c : ''
	OSD1_CTRL_HDR0                  	osd1_ctrl_hdr0                  ;	// 0x0020 : ''
	OSD1_CTRL_HDR1                  	osd1_ctrl_hdr1                  ;	// 0x0024 : ''
	OSD1_CTRL_HDR2                  	osd1_ctrl_hdr2                  ;	// 0x0028 : ''
	OSD1_CTRL_HDR3                  	osd1_ctrl_hdr3                  ;	// 0x002c : ''
	OSD1_CTRL_HDR4                  	osd1_ctrl_hdr4                  ;	// 0x0030 : ''
	OSD1_CTRL_HDR5                  	osd1_ctrl_hdr5                  ;	// 0x0034 : ''
	OSD1_CTRL_HDR6                  	osd1_ctrl_hdr6                  ;	// 0x0038 : ''
	OSD1_CTRL_CKEY_CTRL_1           	osd1_ctrl_ckey_ctrl_1           ;	// 0x003c : ''

	OSD1_CTRL_SYNC0                 	osd1_ctrl_sync0                 ;	// 0x0040 : ''
	OSD1_CTRL_SYNC1                 	osd1_ctrl_sync1                 ;	// 0x0044 : ''
	OSD1_CTRL_SYNC2                 	osd1_ctrl_sync2                 ;	// 0x0048 : ''
	OSD1_CTRL_SYNC3                 	osd1_ctrl_sync3                 ;	// 0x004c : ''
	OSD1_CTRL_SYNC4                 	osd1_ctrl_sync4                 ;	// 0x0050 : ''
	OSD1_CTRL_SYNC5                 	osd1_ctrl_sync5                 ;	// 0x0054 : ''

	OSD1_BITMAP_CTRL0               	osd1_bitmap_ctrl0               ;	// 0x0058 : ''
	OSD1_BITMAP_CTRL1               	osd1_bitmap_ctrl1               ;	// 0x005c : ''
	OSD1_VSP_BOSD_CTRL_0            	osd1_vsp_bosd_ctrl_0            ;	// 0x0060 : ''
	OSD1_VSP_BOSD_CTRL_1            	osd1_vsp_bosd_ctrl_1            ;	// 0x0064 : ''
	OSD1_VSP_SOSD_CTRL_0            	osd1_vsp_sosd_ctrl_0            ;	// 0x0068 : ''
	OSD1_VSP_SOSD_CTRL_1            	osd1_vsp_sosd_ctrl_1            ;	// 0x006c : ''
	OSD1_BITMAP_CTRL2               	osd1_bitmap_ctrl2               ;	// 0x0070 : ''
	OSD1_STATUS_ALPHA_50X50         	osd1_status_alpha_50x50         ;	// 0x0074 : ''
	OSD1_SCALER_STATUS_CTRL         	osd1_scaler_status_ctrl         ;	// 0x0078 : ''
	OSD1_OUT_BUF_STATUS             	osd1_out_buf_status             ;	// 0x007c : ''
	OSD1_CDC_CROP_CTRL_0            	osd1_cdc_crop_ctrl_0            ;	// 0x0080 : ''
	OSD1_CDC_CROP_CTRL_1            	osd1_cdc_crop_ctrl_1            ;	// 0x0084 : ''
	OSD1_CDC_CROP_CTRL_2            	osd1_cdc_crop_ctrl_2            ;	// 0x0088 : ''
	OSD1_CROP_CTRL_0                	osd1_crop_ctrl_0                ;	// 0x008c : ''
	OSD1_CROP_CTRL_1                	osd1_crop_ctrl_1                ;	// 0x0090 : ''
	OSD1_CROP_CTRL_2                	osd1_crop_ctrl_2                ;	// 0x0094 : ''
	OSD1_CROP_CTRL_3                	osd1_crop_ctrl_3                ;	// 0x0098 : ''
	OSD1_LSR_CTRL0                  	osd1_lsr_ctrl0                  ;	// 0x009c : ''
	OSD1_LSR_CTRL1                  	osd1_lsr_ctrl1                  ;	// 0x00a0 : ''
	OSD1_LSR_CTRL2                  	osd1_lsr_ctrl2                  ;	// 0x00a4 : ''
	OSD1_LSR_CTRL3                  	osd1_lsr_ctrl3                  ;	// 0x00a8 : ''
	OSD1_LSR_CTRL4                  	osd1_lsr_ctrl4                  ;	// 0x00ac : ''
	OSD1_LSR_CTRL5                  	osd1_lsr_ctrl5                  ;	// 0x00b0 : ''
	OSD1_LSR_CTRL6                  	osd1_lsr_ctrl6                  ;	// 0x00b4 : ''
	OSD1_POST_CROP_CTRL_0           	osd1_post_crop_ctrl_0           ;	// 0x00b8 : ''
	OSD1_POST_CROP_CTRL_1           	osd1_post_crop_ctrl_1           ;	// 0x00bc : ''
	OSD1_POST_CROP_CTRL_2           	osd1_post_crop_ctrl_2           ;	// 0x00c0 : ''
	OSD1_POST_CROP_CTRL_3           	osd1_post_crop_ctrl_3           ;	// 0x00c4 : ''
	OSD1_GSR_CTRL_0                 	osd1_gsr_ctrl_0                 ;	// 0x00c8 : ''
	OSD1_GSR_CTRL_1                 	osd1_gsr_ctrl_1                 ;	// 0x00cc : ''
	OSD1_GSR_CTRL_2                 	osd1_gsr_ctrl_2                 ;	// 0x00d0 : ''
	OSD1_GSR_CTRL_3                 	osd1_gsr_ctrl_3                 ;	// 0x00d4 : ''
	OSD1_GSR_IND_CTRL               	osd1_gsr_ind_ctrl               ;	// 0x00d8 : ''
	OSD1_GSR_IND_DATA               	osd1_gsr_ind_data               ;	// 0x00dc : ''
	OSD1_SHP_CG_CTRL                	osd1_shp_cg_ctrl                ;	// 0x00e0 : ''
	OSD1_LOCAL_ALPHA_CTRL_0         	osd1_local_alpha_ctrl_0         ;	// 0x00e4 : ''
	OSD1_LOCAL_ALPHA_CTRL_1         	osd1_local_alpha_ctrl_1         ;	// 0x00e8 : ''
	OSD1_LOCAL_ALPHA_CTRL_2         	osd1_local_alpha_ctrl_2         ;	// 0x00ec : ''
} OSD_IMAGE1_REG_T;
/* 60 regs, 60 types */

typedef struct {
	OSD4_CTRL_MAIN                  	osd4_ctrl_main                  ;	// 0x0000 : ''
	OSD4_BASE_ADDR                  	osd4_base_addr                  ;	// 0x0004 : ''
	OSD4_CTRL_SWAP                  	osd4_ctrl_swap                  ;	// 0x0008 : ''
	OSD4_CTRL_PDEC                  	osd4_ctrl_pdec                  ;	// 0x000c : ''
	OSD4_CTRL_SCALER                	osd4_ctrl_scaler                ;	// 0x0010 : ''
	OSD4_INFO_SCALER                	osd4_info_scaler                ;	// 0x0014 : ''
	OSD4_CTRL_PATH                  	osd4_ctrl_path                  ;	// 0x0018 : ''
	OSD4_CTRL_CKEY_CTRL_0           	osd4_ctrl_ckey_ctrl_0           ;	// 0x001c : ''
	OSD4_CTRL_HDR0                  	osd4_ctrl_hdr0                  ;	// 0x0020 : ''
	OSD4_CTRL_HDR1                  	osd4_ctrl_hdr1                  ;	// 0x0024 : ''
	OSD4_CTRL_HDR2                  	osd4_ctrl_hdr2                  ;	// 0x0028 : ''
	OSD4_CTRL_HDR3                  	osd4_ctrl_hdr3                  ;	// 0x002c : ''
	OSD4_CTRL_HDR4                  	osd4_ctrl_hdr4                  ;	// 0x0030 : ''
	OSD4_CTRL_HDR5                  	osd4_ctrl_hdr5                  ;	// 0x0034 : ''
	OSD4_CTRL_HDR6                  	osd4_ctrl_hdr6                  ;	// 0x0038 : ''
	OSD4_CTRL_CKEY_CTRL_1           	osd4_ctrl_ckey_ctrl_1           ;	// 0x003c : ''

	OSD4_CTRL_SYNC0                 	osd4_ctrl_sync0                 ;	// 0x0040 : ''
	OSD4_CTRL_SYNC1                 	osd4_ctrl_sync1                 ;	// 0x0044 : ''
	OSD4_CTRL_SYNC2                 	osd4_ctrl_sync2                 ;	// 0x0048 : ''
	OSD4_CTRL_SYNC3                 	osd4_ctrl_sync3                 ;	// 0x004c : ''
	OSD4_CTRL_SYNC4                 	osd4_ctrl_sync4                 ;	// 0x0050 : ''
	OSD4_CTRL_SYNC5                 	osd4_ctrl_sync5                 ;	// 0x0054 : ''
	UINT32                          	                 __rsvd_00[   2];	// 0x0058 ~ 0x005c
	REG_OSD0_CSC_CTRL0              	reg_osd0_csc_ctrl0              ;	// 0x0060 : ''
	REG_OSD0_CSC_CTRL1              	reg_osd0_csc_ctrl1              ;	// 0x0064 : ''
	REG_OSD0_CSC_CTRL2              	reg_osd0_csc_ctrl2              ;	// 0x0068 : ''
	REG_OSD0_CSC_CTRL3              	reg_osd0_csc_ctrl3              ;	// 0x006c : ''
	REG_OSD0_CSC_CTRL4              	reg_osd0_csc_ctrl4              ;	// 0x0070 : ''
	REG_OSD0_CSC_CTRL5              	reg_osd0_csc_ctrl5              ;	// 0x0074 : ''
	REG_OSD0_CSC_CTRL6              	reg_osd0_csc_ctrl6              ;	// 0x0078 : ''
	REG_OSD0_CSC_CTRL7              	reg_osd0_csc_ctrl7              ;	// 0x007c : ''
	REG_OSD1_CSC_CTRL0              	reg_osd1_csc_ctrl0              ;	// 0x0080 : ''
	REG_OSD1_CSC_CTRL1              	reg_osd1_csc_ctrl1              ;	// 0x0084 : ''
	REG_OSD1_CSC_CTRL2              	reg_osd1_csc_ctrl2              ;	// 0x0088 : ''
	REG_OSD1_CSC_CTRL3              	reg_osd1_csc_ctrl3              ;	// 0x008c : ''
	REG_OSD1_CSC_CTRL4              	reg_osd1_csc_ctrl4              ;	// 0x0090 : ''
	REG_OSD1_CSC_CTRL5              	reg_osd1_csc_ctrl5              ;	// 0x0094 : ''
	REG_OSD1_CSC_CTRL6              	reg_osd1_csc_ctrl6              ;	// 0x0098 : ''
	REG_OSD1_CSC_CTRL7              	reg_osd1_csc_ctrl7              ;	// 0x009c : ''
	OSD_SOSD_CSC_CTRL00             	osd_sosd_csc_ctrl00             ;	// 0x00a0 : ''
	OSD_SOSD_CSC_CTRL01             	osd_sosd_csc_ctrl01             ;	// 0x00a4 : ''
	OSD_SOSD_CSC_CTRL02             	osd_sosd_csc_ctrl02             ;	// 0x00a8 : ''
	OSD_SOSD_CSC_CTRL03             	osd_sosd_csc_ctrl03             ;	// 0x00ac : ''
	OSD_SOSD_CSC_CTRL04             	osd_sosd_csc_ctrl04             ;	// 0x00b0 : ''
	OSD_SOSD_CSC_CTRL05             	osd_sosd_csc_ctrl05             ;	// 0x00b4 : ''
	OSD_SOSD_CSC_CTRL06             	osd_sosd_csc_ctrl06             ;	// 0x00b8 : ''
	OSD_SOSD_CSC_CTRL07             	osd_sosd_csc_ctrl07             ;	// 0x00bc : ''
	OSD_SOSD_CSC_CTRL08             	osd_sosd_csc_ctrl08             ;	// 0x00c0 : ''
	OSD_SOSD_CSC_CTRL09             	osd_sosd_csc_ctrl09             ;	// 0x00c4 : ''
	OSD_SOSD_CSC_CTRL10             	osd_sosd_csc_ctrl10             ;	// 0x00c8 : ''
	OSD_SOSD_CSC_CTRL11             	osd_sosd_csc_ctrl11             ;	// 0x00cc : ''
} OSD_CURSOR_REG_T;
/* 50 regs, 50 types */

typedef struct {
	OSD_HDRUI_CTRL                  	osd_hdrui_ctrl                  ;	// 0x0000 : ''
	UINT32                          	                 __rsvd_00[   7];	// 0x0004 ~ 0x001c
	OSD_HDRUI_HUE_CTRL              	osd_hdrui_hue_ctrl              ;	// 0x0020 : ''
	OSD_HDRUI_SIZE                  	osd_hdrui_size                  ;	// 0x0024 : ''
	OSD_HDRUI_DITHER_CTRL0          	osd_hdrui_dither_ctrl0          ;	// 0x0028 : ''
	UINT32                          	                 __rsvd_01[   1];	// 0x002c
	OSD_HDRUI_DITHER_CTRL2          	osd_hdrui_dither_ctrl2          ;	// 0x0030 : ''
	OSD_HDRUI_LUT0_IND_CTRL0        	osd_hdrui_lut0_ind_ctrl0        ;	// 0x0034 : ''
	OSD_HDRUI_LUT0_IND_DATA0        	osd_hdrui_lut0_ind_data0        ;	// 0x0038 : ''
	OSD_HDRUI_LUT1_IND_CTRL0        	osd_hdrui_lut1_ind_ctrl0        ;	// 0x003c : ''
	OSD_HDRUI_LUT1_IND_DATA0        	osd_hdrui_lut1_ind_data0        ;	// 0x0040 : ''
	OSD_HDRUI_LUT2_IND_CTRL0        	osd_hdrui_lut2_ind_ctrl0        ;	// 0x0044 : ''
	OSD_HDRUI_LUT2_IND_DATA0        	osd_hdrui_lut2_ind_data0        ;	// 0x0048 : ''
	UINT32                          	                 __rsvd_02[   6];	// 0x004c ~ 0x0060
	OSD_HDRUI_LUT0_CTRL_00          	osd_hdrui_lut0_ctrl_00          ;	// 0x0064 : ''
	OSD_HDRUI_LUT0_CTRL_01          	osd_hdrui_lut0_ctrl_01          ;	// 0x0068 : ''
	OSD_HDRUI_LUT0_CTRL_02          	osd_hdrui_lut0_ctrl_02          ;	// 0x006c : ''
	OSD_HDRUI_LUT0_CTRL_03          	osd_hdrui_lut0_ctrl_03          ;	// 0x0070 : ''
	OSD_HDRUI_LUT0_CTRL_04          	osd_hdrui_lut0_ctrl_04          ;	// 0x0074 : ''
	OSD_HDRUI_LUT0_CTRL_05          	osd_hdrui_lut0_ctrl_05          ;	// 0x0078 : ''
	OSD_HDRUI_LUT1_CTRL_00          	osd_hdrui_lut1_ctrl_00          ;	// 0x007c : ''
	OSD_HDRUI_LUT1_CTRL_01          	osd_hdrui_lut1_ctrl_01          ;	// 0x0080 : ''
	OSD_HDRUI_LUT1_CTRL_02          	osd_hdrui_lut1_ctrl_02          ;	// 0x0084 : ''
	OSD_HDRUI_LUT1_CTRL_03          	osd_hdrui_lut1_ctrl_03          ;	// 0x0088 : ''
	OSD_HDRUI_LUT1_CTRL_04          	osd_hdrui_lut1_ctrl_04          ;	// 0x008c : ''
	OSD_HDRUI_LUT1_CTRL_05          	osd_hdrui_lut1_ctrl_05          ;	// 0x0090 : ''
	OSD_HDRUI_LUT2_CTRL_00          	osd_hdrui_lut2_ctrl_00          ;	// 0x0094 : ''
	UINT32                          	                 __rsvd_03[   4];	// 0x0098 ~ 0x00a4
	OSD_HDRUI_LUT2_CTRL_05          	osd_hdrui_lut2_ctrl_05          ;	// 0x00a8 : ''
	OSD_HDRUI_YC2RGB_CTRL00         	osd_hdrui_yc2rgb_ctrl00         ;	// 0x00ac : ''
	OSD_HDRUI_YC2RGB_CTRL01         	osd_hdrui_yc2rgb_ctrl01         ;	// 0x00b0 : ''
	OSD_HDRUI_YC2RGB_CTRL02         	osd_hdrui_yc2rgb_ctrl02         ;	// 0x00b4 : ''
	OSD_HDRUI_YC2RGB_CTRL03         	osd_hdrui_yc2rgb_ctrl03         ;	// 0x00b8 : ''
	OSD_HDRUI_YC2RGB_CTRL04         	osd_hdrui_yc2rgb_ctrl04         ;	// 0x00bc : ''
	OSD_HDRUI_YC2RGB_CTRL05         	osd_hdrui_yc2rgb_ctrl05         ;	// 0x00c0 : ''
	OSD_HDRUI_YC2RGB_CTRL06         	osd_hdrui_yc2rgb_ctrl06         ;	// 0x00c4 : ''
	OSD_HDRUI_YC2RGB_CTRL07         	osd_hdrui_yc2rgb_ctrl07         ;	// 0x00c8 : ''
	OSD_HDRUI_YC2RGB_CTRL08         	osd_hdrui_yc2rgb_ctrl08         ;	// 0x00cc : ''
	OSD_HDRUI_YC2RGB_CTRL09         	osd_hdrui_yc2rgb_ctrl09         ;	// 0x00d0 : ''
	OSD_HDRUI_YC2RGB_CTRL10         	osd_hdrui_yc2rgb_ctrl10         ;	// 0x00d4 : ''
	OSD_HDRUI_YC2RGB_CTRL11         	osd_hdrui_yc2rgb_ctrl11         ;	// 0x00d8 : ''
} OSD_HDRUI_REG_T;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////
// OSD REG GROUP
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
	UINT32
	reg_status_mon_data            ;   	// 31: 0
} OSDX_STATUS_MON_DATA;

typedef struct {
	UINT32
	reg_common_disp_size_h          :12,	//  0:11
	                                : 4,	// 12:15 reserved
	reg_common_disp_size_w          :12;	// 16:27
} OSDX_COMMON_DISP_SIZE;

// 128 Byte
typedef struct {
	CTRL_SOSD_MIXER_DISP_SIZE       	ctrl_sosd_mixer_disp_size       ;	// 0x0000 : ''
	CTRL_SOSD_MIXER_OUTPUT          	ctrl_sosd_mixer_output          ;	// 0x0004 : ''
	CTRL_SOSD_MIXER_AWB             	ctrl_sosd_mixer_awb             ;	// 0x0008 : ''
	CTRL_SOSD_MIXER_MIRACAST_CTRL   	ctrl_sosd_mixer_miracast_ctrl   ;	// 0x000c : ''
	CTRL_SOSD_MIXER_CTRL_ALPHA      	ctrl_sosd_mixer_ctrl_alpha      ;	// 0x0010 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL0     	ctrl_sosd_mixer_force_ctrl0     ;	// 0x0014 : ''
	CTRL_SOSD_MIXER_FORCE_CTRL1     	ctrl_sosd_mixer_force_ctrl1     ;	// 0x0018 : ''
	CTRL_SOSD_MIXER_HOLE            	ctrl_sosd_mixer_hole            ;	// 0x001c : ''
	CTRL_SOSD_MIXER_MUX0            	ctrl_sosd_mixer_mux0            ;	// 0x0020 : ''
	CTRL_SOSD_MIXER_MUX1            	ctrl_sosd_mixer_mux1            ;	// 0x0024 : ''
	UINT32                          	ctrl_sosd_mixer_mux2            ;	// 0x0028 : ''
	CTRL_SOSD_MIXER_MUX3            	ctrl_sosd_mixer_mux3            ;	// 0x002c : ''
	CTRL_SOSD_MIXER_MUX4            	ctrl_sosd_mixer_mux4            ;	// 0x0030 : ''
	CTRL_SOSD_MIXER_MUX5            	ctrl_sosd_mixer_mux5            ;	// 0x0034 : ''
	CTRL_SOSD_MIXER_MUX6            	ctrl_sosd_mixer_mux6            ;	// 0x0038 : ''
	CTRL_SOSD_MIXER_MUX7            	ctrl_sosd_mixer_mux7            ;	// 0x003c : ''
	CTRL_SOSD_MIXER_MUX8            	ctrl_sosd_mixer_mux8            ;	// 0x0040 : ''
	CTRL_SOSD_MIXER_MUX9            	ctrl_sosd_mixer_mux9            ;	// 0x0044 : ''
	CTRL_SOSD_MIXER_MUXA            	ctrl_sosd_mixer_muxa            ;	// 0x0048 : ''
	CTRL_SOSD_MIXER_MUXB            	ctrl_sosd_mixer_muxb            ;	// 0x004c : ''
	CTRL_SOSD_MIXER_MUXC            	ctrl_sosd_mixer_muxc            ;	// 0x0050 : ''
	CTRL_SOSD_MIXER_MUXD            	ctrl_sosd_mixer_muxd            ;	// 0x0054 : ''
	CTRL_SOSD_MIXER_MUXE            	ctrl_sosd_mixer_muxe            ;	// 0x0058 : ''
	CTRL_SOSD_MIXER_MUXF            	ctrl_sosd_mixer_muxf            ;	// 0x005c : ''

	UINT32                          	                 __rsvd_00[   8];	// 0x0060 ~ 0x0080
}
OSDX_SEP_OSD_MIXER;

// 128 Byte
typedef struct {
	CTRL_BOSD0_MIXER_DISP_SIZE      	ctrl_bosd_mixer_disp_size      ;	// 0x0000 : ''
	CTRL_BOSD0_MIXER_OUTPUT         	ctrl_bosd_mixer_output         ;	// 0x0004 : ''
	CTRL_BOSD0_MIXER_AWB            	ctrl_bosd_mixer_awb            ;	// 0x0008 : ''
	UINT32                          	                 __rsvd_00[   4];	// 0x000c ~ 0x0018
	CTRL_BOSD0_MIXER_HOLE           	ctrl_bosd_mixer_hole           ;	// 0x001c : ''
	CTRL_BOSD0_MIXER_MUX0           	ctrl_bosd_mixer_mux0           ;	// 0x0020 : ''
	CTRL_BOSD0_MIXER_MUX1           	ctrl_bosd_mixer_mux1           ;	// 0x0024 : ''
	CTRL_BOSD0_MIXER_MUX2           	ctrl_bosd_mixer_mux2           ;	// 0x0028 : ''
	CTRL_BOSD0_MIXER_MUX3           	ctrl_bosd_mixer_mux3           ;	// 0x002c : ''
	CTRL_BOSD0_MIXER_MUX4           	ctrl_bosd_mixer_mux4           ;	// 0x0030 : ''
	CTRL_BOSD0_MIXER_MUX5           	ctrl_bosd_mixer_mux5           ;	// 0x0034 : ''
	CTRL_BOSD0_MIXER_MUX6           	ctrl_bosd_mixer_mux6           ;	// 0x0038 : ''
	CTRL_BOSD0_MIXER_MUX7           	ctrl_bosd_mixer_mux7           ;	// 0x003c : ''
	CTRL_BOSD0_MIXER_MUX8           	ctrl_bosd_mixer_mux8           ;	// 0x0040 : ''
	CTRL_BOSD0_MIXER_MUX9           	ctrl_bosd_mixer_mux9           ;	// 0x0044 : ''
	CTRL_BOSD0_MIXER_MUXA           	ctrl_bosd_mixer_muxa           ;	// 0x0048 : ''
	CTRL_BOSD0_MIXER_MUXB           	ctrl_bosd_mixer_muxb           ;	// 0x004c : ''
	CTRL_BOSD0_MIXER_MUXC           	ctrl_bosd_mixer_muxc           ;	// 0x0050 : ''
	CTRL_BOSD0_MIXER_MUXD           	ctrl_bosd_mixer_muxd           ;	// 0x0054 : ''
	CTRL_BOSD0_MIXER_MUXE           	ctrl_bosd_mixer_muxe           ;	// 0x0058 : ''
	CTRL_BOSD0_MIXER_MUXF           	ctrl_bosd_mixer_muxf           ;	// 0x005c : ''
	CTRL_BOSD0_MIXER_LED_ALPHA      	ctrl_bosd_mixer_led_alpha      ;	// 0x0060 : ''
	UINT32                          	                 __rsvd_01[   7];	// 0x0064 ~ 0x007c
}
OSDX_BLEND_OSD_MIXER;

typedef union
{
	// OSD0_CTRL_SCALER
	UINT32
									: 2,	//  0: 1 reserved
	reg_osd_line_th_en              : 1,	//     2
	reg_osd_bilinear                : 1,	//     3
	reg_osd_odd_width_en            : 1,	//     4
	reg_osd_mode_32p                : 1,	//     5
	reg_osd_buf_mode_en_n           : 1,	//     6
									: 1,	//     7 reserved
	reg_osd_sampling_mode           : 1,	//     8
									: 1,	//     9 reserved
	reg_osd_hsc_phase_off           : 9,	// 10:18
	reg_osd_vsc_phase_off           : 9,	// 19:27
	reg_osd_vcubic_filter_sel       : 2;	// 28:29

	// OSD4_CTRL_SCALER
	UINT32
	reg_crsr_v_x2_sel               : 1,	//     0
	reg_crsr_h_x2_sel               : 1,	//     1
	reg_crsr_v_x2_en                : 1,	//     2
	reg_crsr_h_x2_en                : 1,	//     3
									: 1,	//     4 reserved
	reg_monitor_mode                : 1,	//     5
									: 9,	//  6:14 reserved
	reg_cursor_urgency_th           :16,	// 15:30
	reg_cursor_urgency_th_en        : 1;	//    31
}
OSDX_CTRL_SCALER;

typedef struct
{
	union
	{
		// OSD0, OSD0_1, OSD1, OSD3 shared
		struct
		{
			OSD0_CTRL_MAIN                  	osd_ctrl_main                  ;	// 0x0000 : ''
			UINT32                          	osd_base_addr                  ;	// 0x0004 : ''
			OSD0_CTRL_SWAP                  	osd_ctrl_swap                  ;	// 0x0008 : ''
			OSD0_CTRL_PDEC                  	osd_ctrl_pdec                  ;	// 0x000c : ''

			/* OSD0, OSD1 & OSD3 only. OSD0_1 has below 3 registers as blank */
			OSDX_CTRL_SCALER                	osd_ctrl_scaler                ;	// 0x0010 : ''
			OSD0_INFO_SCALER                	osd_info_scaler                ;	// 0x0014 : ''
			OSD0_CTRL_PATH                  	osd_ctrl_path                  ;	// 0x0018 : ''

			OSD0_CTRL_CKEY_CTRL_0           	osd_ctrl_ckey_ctrl_0           ;	// 0x001c : ''
			OSD0_CTRL_HDR0                  	osd_ctrl_hdr0                  ;	// 0x0020 : ''
			OSD0_CTRL_HDR1                  	osd_ctrl_hdr1                  ;	// 0x0024 : ''
			OSD0_CTRL_HDR2                  	osd_ctrl_hdr2                  ;	// 0x0028 : ''
			OSD0_CTRL_HDR3                  	osd_ctrl_hdr3                  ;	// 0x002c : ''
			OSD0_CTRL_HDR4                  	osd_ctrl_hdr4                  ;	// 0x0030 : ''
			OSD0_CTRL_HDR5                  	osd_ctrl_hdr5                  ;	// 0x0034 : ''
			OSD0_CTRL_HDR6                  	osd_ctrl_hdr6                  ;	// 0x0038 : ''
			OSD0_CTRL_CKEY_CTRL_1           	osd_ctrl_ckey_ctrl_1           ;	// 0x003c : ''

			/* OSD0, OSD1 & OSD3 only. OSD0_1 has below registers as 4k_osd and other data */
			OSD0_CTRL_SYNC0                 	osd_ctrl_sync0                 ;	// 0x0040 : ''
			OSD0_CTRL_SYNC1                 	osd_ctrl_sync1                 ;	// 0x0044 : ''
			OSD0_CTRL_SYNC2                 	osd_ctrl_sync2                 ;	// 0x0048 : ''
			OSD0_CTRL_SYNC3                 	osd_ctrl_sync3                 ;	// 0x004c : ''
			OSD0_CTRL_SYNC4                 	osd_ctrl_sync4                 ;	// 0x0050 : ''
			OSD0_CTRL_SYNC5                 	osd_ctrl_sync5                 ;	// 0x0054 : ''
		};

		// OSD0, OSD1 shared. access through osdx_ctrl[0], osdx_ctrl[2]
		struct
		{
			UINT32								_skip_00[22]					;	// 0x0000~0x0058
			OSD0_BITMAP_CTRL0               	osd_bitmap_ctrl0               ;	// 0x0058 : ''
			OSD0_BITMAP_CTRL1               	osd_bitmap_ctrl1               ;	// 0x005c : ''
			OSD0_VSP_BOSD_CTRL_0            	osd_vsp_bosd_ctrl_0            ;	// 0x0060 : ''
			OSD0_VSP_BOSD_CTRL_1            	osd_vsp_bosd_ctrl_1            ;	// 0x0064 : ''
			OSD0_VSP_SOSD_CTRL_0            	osd_vsp_sosd_ctrl_0            ;	// 0x0068 : ''
			OSD0_VSP_SOSD_CTRL_1            	osd_vsp_sosd_ctrl_1            ;	// 0x006c : ''
			OSD0_BITMAP_CTRL2               	osd_bitmap_ctrl2               ;	// 0x0070 : ''
			OSD0_STATUS_ALPHA_50X50         	osd_status_alpha_50x50         ;	// 0x0074 : ''
			OSD0_SCALER_STATUS_CTRL         	osd_scaler_status_ctrl         ;	// 0x0078 : ''
			OSD0_OUT_BUF_STATUS             	osd_out_buf_status             ;	// 0x007c : ''
			OSD0_CDC_CROP_CTRL_0            	osd_cdc_crop_ctrl_0            ;	// 0x0080 : ''
			OSD0_CDC_CROP_CTRL_1            	osd_cdc_crop_ctrl_1            ;	// 0x0084 : ''
			OSD0_CDC_CROP_CTRL_2            	osd_cdc_crop_ctrl_2            ;	// 0x0088 : ''
			OSD0_CROP_CTRL_0                	osd_crop_ctrl_0                ;	// 0x008c : ''
			OSD0_CROP_CTRL_1                	osd_crop_ctrl_1                ;	// 0x0090 : ''
			OSD0_CROP_CTRL_2                	osd_crop_ctrl_2                ;	// 0x0094 : ''
			OSD0_CROP_CTRL_3                	osd_crop_ctrl_3                ;	// 0x0098 : ''
			OSD0_LSR_CTRL0                  	osd_lsr_ctrl0                  ;	// 0x009c : ''
			OSD0_LSR_CTRL1                  	osd_lsr_ctrl1                  ;	// 0x00a0 : ''
			OSD0_LSR_CTRL2                  	osd_lsr_ctrl2                  ;	// 0x00a4 : ''
			OSD0_LSR_CTRL3                  	osd_lsr_ctrl3                  ;	// 0x00a8 : ''
			OSD0_LSR_CTRL4                  	osd_lsr_ctrl4                  ;	// 0x00ac : ''
			OSD0_LSR_CTRL5                  	osd_lsr_ctrl5                  ;	// 0x00b0 : ''
			OSD0_LSR_CTRL6                  	osd_lsr_ctrl6                  ;	// 0x00b4 : ''
			OSD0_POST_CROP_CTRL_0           	osd_post_crop_ctrl_0           ;	// 0x00b8 : ''
			OSD0_POST_CROP_CTRL_1           	osd_post_crop_ctrl_1           ;	// 0x00bc : ''
			OSD0_POST_CROP_CTRL_2           	osd_post_crop_ctrl_2           ;	// 0x00c0 : ''
			OSD0_POST_CROP_CTRL_3           	osd_post_crop_ctrl_3           ;	// 0x00c4 : ''
			OSD0_GSR_CTRL_0                 	osd_gsr_ctrl_0                 ;	// 0x00c8 : ''
			OSD0_GSR_CTRL_1                 	osd_gsr_ctrl_1                 ;	// 0x00cc : ''
			OSD0_GSR_CTRL_2                 	osd_gsr_ctrl_2                 ;	// 0x00d0 : ''
			OSD0_GSR_CTRL_3                 	osd_gsr_ctrl_3                 ;	// 0x00d4 : ''
			OSD0_GSR_IND_CTRL               	osd_gsr_ind_ctrl               ;	// 0x00d8 : ''
			OSD0_GSR_IND_DATA               	osd_gsr_ind_data               ;	// 0x00dc : ''
			OSD0_SHP_CG_CTRL                	osd_shp_cg_ctrl                ;	// 0x00e0 : ''
			OSD0_LOCAL_ALPHA_CTRL_0         	osd_local_alpha_ctrl_0         ;	// 0x00e4 : ''
			OSD0_LOCAL_ALPHA_CTRL_1         	osd_local_alpha_ctrl_1         ;	// 0x00e8 : ''
			OSD0_LOCAL_ALPHA_CTRL_2         	osd_local_alpha_ctrl_2         ;	// 0x00ec : ''
		};

		// OSD0_1 only. access through osdx_ctrl[1]
		struct
		{
			UINT32								__skip_01[16]					; 	// 0x0000~0x0040

			REG_4K_OSD_MAIN_CTRL_0          	reg_4k_osd_main_ctrl_0          ;	// 0x0040 : ''
			REG_4K_OSD_MAIN_CTRL_1          	reg_4k_osd_main_ctrl_1          ;	// 0x0044 : ''
			REG_4K_OSD_MAIN_CTRL_2          	reg_4k_osd_main_ctrl_2          ;	// 0x0048 : ''
			REG_4K_OSD_MAIN_CTRL_3          	reg_4k_osd_main_ctrl_3          ;	// 0x004c : ''

			REG_OSD0_GSR_CTRL00             	reg_osd0_gsr_ctrl00             ;	// 0x0050 : ''
			REG_OSD0_GSR_CTRL01             	reg_osd0_gsr_ctrl01             ;	// 0x0054 : ''
			REG_OSD0_GSR_CTRL02             	reg_osd0_gsr_ctrl02             ;	// 0x0058 : ''
			REG_OSD0_GSR_CTRL03             	reg_osd0_gsr_ctrl03             ;	// 0x005c : ''
			REG_OSD0_GSR_CTRL04             	reg_osd0_gsr_ctrl04             ;	// 0x0060 : ''
			REG_OSD0_GSR_CTRL05             	reg_osd0_gsr_ctrl05             ;	// 0x0064 : ''
			REG_OSD0_GSR_CTRL06             	reg_osd0_gsr_ctrl06             ;	// 0x0068 : ''
			REG_OSD0_GSR_CTRL07             	reg_osd0_gsr_ctrl07             ;	// 0x006c : ''
			REG_OSD0_GSR_CTRL08             	reg_osd0_gsr_ctrl08             ;	// 0x0070 : ''
			REG_OSD0_GSR_CTRL09             	reg_osd0_gsr_ctrl09             ;	// 0x0074 : ''
			REG_OSD0_GSR_CTRL10             	reg_osd0_gsr_ctrl10             ;	// 0x0078 : ''
			REG_OSD0_GSR_CTRL11             	reg_osd0_gsr_ctrl11             ;	// 0x007c : ''
			REG_OSD0_ORD_CTRL00             	reg_osd0_ord_ctrl00             ;	// 0x0080 : ''
			REG_OSD0_ORD_CTRL01             	reg_osd0_ord_ctrl01             ;	// 0x0084 : ''
			REG_OSD0_ORD_CTRL02             	reg_osd0_ord_ctrl02             ;	// 0x0088 : ''
			REG_OSD0_ORD_CTRL03             	reg_osd0_ord_ctrl03             ;	// 0x008c : ''
			REG_OSD0_ORD_CTRL04             	reg_osd0_ord_ctrl04             ;	// 0x0090 : ''
			REG_OSD0_ORD_CTRL05             	reg_osd0_ord_ctrl05             ;	// 0x0094 : ''
			REG_OSD0_ORD_CTRL06             	reg_osd0_ord_ctrl06             ;	// 0x0098 : ''
			REG_OSD0_ORD_CTRL07             	reg_osd0_ord_ctrl07             ;	// 0x009c : ''
			REG_OSD0_ORD_CTRL08             	reg_osd0_ord_ctrl08             ;	// 0x00a0 : ''
			REG_OSD0_ORD_CTRL09             	reg_osd0_ord_ctrl09             ;	// 0x00a4 : ''
			REG_OSD0_ORD_CTRL10             	reg_osd0_ord_ctrl10             ;	// 0x00a8 : ''
			REG_OSD0_ORD_CTRL11             	reg_osd0_ord_ctrl11             ;	// 0x00ac : ''
			REG_OSD0_ORD_CTRL12             	reg_osd0_ord_ctrl12             ;	// 0x00b0 : ''
			REG_OSD0_ORD_CTRL13             	reg_osd0_ord_ctrl13             ;	// 0x00b4 : ''
			REG_OSD0_ORD_CTRL14             	reg_osd0_ord_ctrl14             ;	// 0x00b8 : ''
			REG_OSD0_ORD_CTRL15             	reg_osd0_ord_ctrl15             ;	// 0x00bc : ''
			REG_OSD0_ORD_CTRL16             	reg_osd0_ord_ctrl16             ;	// 0x00c0 : ''
			REG_OSD0_ORD_CTRL17             	reg_osd0_ord_ctrl17             ;	// 0x00c4 : ''
			REG_OSD0_ORD_CTRL18             	reg_osd0_ord_ctrl18             ;	// 0x00c8 : ''
			REG_OSD0_ORD_CTRL19             	reg_osd0_ord_ctrl19             ;	// 0x00cc : ''
			REG_OSD0_PDF_CTRL00             	reg_osd0_pdf_ctrl00             ;	// 0x00d0 : ''
			REG_OSD0_PDF_CTRL01             	reg_osd0_pdf_ctrl01             ;	// 0x00d4 : ''
			REG_OSD0_PDF_CTRL02             	reg_osd0_pdf_ctrl02             ;	// 0x00d8 : ''
			REG_OSD0_PDF_CTRL03             	reg_osd0_pdf_ctrl03             ;	// 0x00dc : ''
			REG_OSD0_PDF_CTRL04             	reg_osd0_pdf_ctrl04             ;	// 0x00e0 : ''
			REG_OSD0_PDF_CTRL05             	reg_osd0_pdf_ctrl05             ;	// 0x00e4 : ''
			REG_OSD0_PDF_IND_CTRL           	reg_osd0_pdf_ind_ctrl           ;	// 0x00e8 : ''
			REG_OSD0_PDF_IND_DATA_RD        	reg_osd0_pdf_ind_data_rd        ;	// 0x00ec : ''
		};

		// OSD3 only. access through osdx_ctrl[3]
		struct
		{
			UINT32								__skip_03[24]					; 	// 0x0000~0x0060

			REG_OSD0_CSC_CTRL0              	reg_osd0_csc_ctrl0              ;	// 0x0060 : ''
			REG_OSD0_CSC_CTRL1              	reg_osd0_csc_ctrl1              ;	// 0x0064 : ''
			REG_OSD0_CSC_CTRL2              	reg_osd0_csc_ctrl2              ;	// 0x0068 : ''
			REG_OSD0_CSC_CTRL3              	reg_osd0_csc_ctrl3              ;	// 0x006c : ''
			REG_OSD0_CSC_CTRL4              	reg_osd0_csc_ctrl4              ;	// 0x0070 : ''
			REG_OSD0_CSC_CTRL5              	reg_osd0_csc_ctrl5              ;	// 0x0074 : ''
			REG_OSD0_CSC_CTRL6              	reg_osd0_csc_ctrl6              ;	// 0x0078 : ''
			REG_OSD0_CSC_CTRL7              	reg_osd0_csc_ctrl7              ;	// 0x007c : ''
			REG_OSD1_CSC_CTRL0              	reg_osd1_csc_ctrl0              ;	// 0x0080 : ''
			REG_OSD1_CSC_CTRL1              	reg_osd1_csc_ctrl1              ;	// 0x0084 : ''
			REG_OSD1_CSC_CTRL2              	reg_osd1_csc_ctrl2              ;	// 0x0088 : ''
			REG_OSD1_CSC_CTRL3              	reg_osd1_csc_ctrl3              ;	// 0x008c : ''
			REG_OSD1_CSC_CTRL4              	reg_osd1_csc_ctrl4              ;	// 0x0090 : ''
			REG_OSD1_CSC_CTRL5              	reg_osd1_csc_ctrl5              ;	// 0x0094 : ''
			REG_OSD1_CSC_CTRL6              	reg_osd1_csc_ctrl6              ;	// 0x0098 : ''
			REG_OSD1_CSC_CTRL7              	reg_osd1_csc_ctrl7              ;	// 0x009c : ''
			OSD_SOSD_CSC_CTRL00             	osd_sosd_csc_ctrl00             ;	// 0x00a0 : ''
			OSD_SOSD_CSC_CTRL01             	osd_sosd_csc_ctrl01             ;	// 0x00a4 : ''
			OSD_SOSD_CSC_CTRL02             	osd_sosd_csc_ctrl02             ;	// 0x00a8 : ''
			OSD_SOSD_CSC_CTRL03             	osd_sosd_csc_ctrl03             ;	// 0x00ac : ''
			OSD_SOSD_CSC_CTRL04             	osd_sosd_csc_ctrl04             ;	// 0x00b0 : ''
			OSD_SOSD_CSC_CTRL05             	osd_sosd_csc_ctrl05             ;	// 0x00b4 : ''
			OSD_SOSD_CSC_CTRL06             	osd_sosd_csc_ctrl06             ;	// 0x00b8 : ''
			OSD_SOSD_CSC_CTRL07             	osd_sosd_csc_ctrl07             ;	// 0x00bc : ''
			OSD_SOSD_CSC_CTRL08             	osd_sosd_csc_ctrl08             ;	// 0x00c0 : ''
			OSD_SOSD_CSC_CTRL09             	osd_sosd_csc_ctrl09             ;	// 0x00c4 : ''
			OSD_SOSD_CSC_CTRL10             	osd_sosd_csc_ctrl10             ;	// 0x00c8 : ''
			OSD_SOSD_CSC_CTRL11             	osd_sosd_csc_ctrl11             ;	// 0x00cc : ''
		};

		UINT32  __sizer[64];    /* each plane has 256 bytes (64 registers) */
	};
}
OSDX_CTRL;

/////////////////////////////////////////////////////////////////////////////////////////////////
// INTEGRATED OSD REGS
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
	// 0x0000 ~ 0x0040
	struct
	{
		OSD_STATUS_MON_CFG              	osd_status_mon_cfg              ;	// 0x0000 : ''
		OSD_STATUS_MON_POS              	osd_status_mon_pos              ;	// 0x0004 : ''
		OSD_STATUS_PIC_CNT              	osd_status_pic_cnt              ;	// 0x0008 : ''
		OSD_STATUS_MIXER_LINE           	osd_status_mixer_line           ;	// 0x000c : ''
#if 1
		OSDX_STATUS_MON_DATA            	osd_status_mon_data[12]         ;	// 0x0010~0x40
#else
		OSD_STATUS_MON_DATA0            	osd_status_mon_data0            ;	// 0x0010 : ''
		OSD_STATUS_MON_DATA1            	osd_status_mon_data1            ;	// 0x0014 : ''
		OSD_STATUS_MON_DATA2            	osd_status_mon_data2            ;	// 0x0018 : ''
		OSD_STATUS_MON_DATA3            	osd_status_mon_data3            ;	// 0x001c : ''
		OSD_STATUS_MON_DATA4            	osd_status_mon_data4            ;	// 0x0020 : ''
		OSD_STATUS_MON_DATA5            	osd_status_mon_data5            ;	// 0x0024 : ''
		OSD_STATUS_MON_DATA6            	osd_status_mon_data6            ;	// 0x0028 : ''
		OSD_STATUS_MON_DATA7            	osd_status_mon_data7            ;	// 0x002c : ''
		OSD_STATUS_MON_DATA8            	osd_status_mon_data8            ;	// 0x0030 : ''
		OSD_STATUS_MON_DATA9            	osd_status_mon_data9            ;	// 0x0034 : ''
		OSD_STATUS_MON_DATAA            	osd_status_mon_dataa            ;	// 0x0038 : ''
		OSD_STATUS_MON_DATAB            	osd_status_mon_datab            ;	// 0x003c : ''
#endif
	};

	// 0x0040 ~ 0x0080
	struct
	{
		OSD_COMMON_PLTE_SEL             	osd_common_plte_sel             ;	// 0x0000 : ''
		OSD_COMMON_CTRL_IRQ             	osd_common_ctrl_irq             ;	// 0x0004 : ''
		OSD_COMMON_CTRL_PIC_INIT        	osd_common_ctrl_pic_init        ;	// 0x0008 : ''
		OSD_COMMON_CTRL_PIC_TIMER       	osd_common_ctrl_pic_timer       ;	// 0x000c : ''
		OSDX_COMMON_DISP_SIZE				osdx_common_disp_size[8]		;	// 0x0010 ~ 0x0030
		OSD_CG_CTRL                     	osd_cg_ctrl                     ;	// 0x0030 : ''

		UINT32                         	    __sep_00[3]						;	// 0x0064 ~ 0x007c
	};

	// 0x0080 ~ 0x0200
	struct
	{
		OSDX_SEP_OSD_MIXER					osdx_sep_osd_mixer[1]			;	// 0x0080 ~ 0x0100
		OSDX_BLEND_OSD_MIXER				osdx_blend_osd_mixer[2]			;	// 0x0100 ~ 0x0200
	};

	// 0x0200 ~ 0x0600
	// OSD0   = UI Left
	// OSD0_1 = UI Right
	// OSD1   = E-Streamer
	// CURSOR = cursor
	struct
	{
		OSDX_CTRL							osdx_ctrl[4]					;
	};

	// 0x0600 ~ 0x700
	struct
	{
		OSD_HDRUI_CTRL                  	osd_hdrui_ctrl                  ;	// 0x0000 : ''
		UINT32                          	                 __rsvd_00[   7];	// 0x0004 ~ 0x001c
		OSD_HDRUI_HUE_CTRL              	osd_hdrui_hue_ctrl              ;	// 0x0020 : ''
		OSD_HDRUI_SIZE                  	osd_hdrui_size                  ;	// 0x0024 : ''
		OSD_HDRUI_DITHER_CTRL0          	osd_hdrui_dither_ctrl0          ;	// 0x0028 : ''
		UINT32                          	                 __rsvd_01[   1];	// 0x002c
		OSD_HDRUI_DITHER_CTRL2          	osd_hdrui_dither_ctrl2          ;	// 0x0030 : ''
		OSD_HDRUI_LUT0_IND_CTRL0        	osd_hdrui_lut0_ind_ctrl0        ;	// 0x0034 : ''
		OSD_HDRUI_LUT0_IND_DATA0        	osd_hdrui_lut0_ind_data0        ;	// 0x0038 : ''
		OSD_HDRUI_LUT1_IND_CTRL0        	osd_hdrui_lut1_ind_ctrl0        ;	// 0x003c : ''
		OSD_HDRUI_LUT1_IND_DATA0        	osd_hdrui_lut1_ind_data0        ;	// 0x0040 : ''
		OSD_HDRUI_LUT2_IND_CTRL0        	osd_hdrui_lut2_ind_ctrl0        ;	// 0x0044 : ''
		OSD_HDRUI_LUT2_IND_DATA0        	osd_hdrui_lut2_ind_data0        ;	// 0x0048 : ''
		UINT32                          	                 __rsvd_02[   6];	// 0x004c ~ 0x0060
		OSD_HDRUI_LUT0_CTRL_00          	osd_hdrui_lut0_ctrl_00          ;	// 0x0064 : ''
		OSD_HDRUI_LUT0_CTRL_01          	osd_hdrui_lut0_ctrl_01          ;	// 0x0068 : ''
		OSD_HDRUI_LUT0_CTRL_02          	osd_hdrui_lut0_ctrl_02          ;	// 0x006c : ''
		OSD_HDRUI_LUT0_CTRL_03          	osd_hdrui_lut0_ctrl_03          ;	// 0x0070 : ''
		OSD_HDRUI_LUT0_CTRL_04          	osd_hdrui_lut0_ctrl_04          ;	// 0x0074 : ''
		OSD_HDRUI_LUT0_CTRL_05          	osd_hdrui_lut0_ctrl_05          ;	// 0x0078 : ''
		OSD_HDRUI_LUT1_CTRL_00          	osd_hdrui_lut1_ctrl_00          ;	// 0x007c : ''
		OSD_HDRUI_LUT1_CTRL_01          	osd_hdrui_lut1_ctrl_01          ;	// 0x0080 : ''
		OSD_HDRUI_LUT1_CTRL_02          	osd_hdrui_lut1_ctrl_02          ;	// 0x0084 : ''
		OSD_HDRUI_LUT1_CTRL_03          	osd_hdrui_lut1_ctrl_03          ;	// 0x0088 : ''
		OSD_HDRUI_LUT1_CTRL_04          	osd_hdrui_lut1_ctrl_04          ;	// 0x008c : ''
		OSD_HDRUI_LUT1_CTRL_05          	osd_hdrui_lut1_ctrl_05          ;	// 0x0090 : ''
		OSD_HDRUI_LUT2_CTRL_00          	osd_hdrui_lut2_ctrl_00          ;	// 0x0094 : ''
		UINT32                          	                 __rsvd_03[   4];	// 0x0098 ~ 0x00a4
		OSD_HDRUI_LUT2_CTRL_05          	osd_hdrui_lut2_ctrl_05          ;	// 0x00a8 : ''
		OSD_HDRUI_YC2RGB_CTRL00         	osd_hdrui_yc2rgb_ctrl00         ;	// 0x00ac : ''
		OSD_HDRUI_YC2RGB_CTRL01         	osd_hdrui_yc2rgb_ctrl01         ;	// 0x00b0 : ''
		OSD_HDRUI_YC2RGB_CTRL02         	osd_hdrui_yc2rgb_ctrl02         ;	// 0x00b4 : ''
		OSD_HDRUI_YC2RGB_CTRL03         	osd_hdrui_yc2rgb_ctrl03         ;	// 0x00b8 : ''
		OSD_HDRUI_YC2RGB_CTRL04         	osd_hdrui_yc2rgb_ctrl04         ;	// 0x00bc : ''
		OSD_HDRUI_YC2RGB_CTRL05         	osd_hdrui_yc2rgb_ctrl05         ;	// 0x00c0 : ''
		OSD_HDRUI_YC2RGB_CTRL06         	osd_hdrui_yc2rgb_ctrl06         ;	// 0x00c4 : ''
		OSD_HDRUI_YC2RGB_CTRL07         	osd_hdrui_yc2rgb_ctrl07         ;	// 0x00c8 : ''
		OSD_HDRUI_YC2RGB_CTRL08         	osd_hdrui_yc2rgb_ctrl08         ;	// 0x00cc : ''
		OSD_HDRUI_YC2RGB_CTRL09         	osd_hdrui_yc2rgb_ctrl09         ;	// 0x00d0 : ''
		OSD_HDRUI_YC2RGB_CTRL10         	osd_hdrui_yc2rgb_ctrl10         ;	// 0x00d4 : ''
		OSD_HDRUI_YC2RGB_CTRL11         	osd_hdrui_yc2rgb_ctrl11         ;	// 0x00d8 : ''

		UINT32                          	                 __rsvd_04[   9];	// 0x00dc ~ 0x0100
	}
	hdr_ui;

} OSD_O24_REG_T;

/* 37 regs, 37 types */

/* 361 regs, 361 types in Total*/

// *INDENT-ON*

#define OSDX_CTRL_Off(_g,_r)             ((UINT32)&(g_osd_o24_reg_shadow->_g._r) - (UINT32)(g_osd_o24_reg_shadow))

#define OSDX_CTRL_RdFL(_g,_r)            ((g_osd_o24_reg_shadow->_g._r)=(g_osd_o24_reg->_g._r))
#define OSDX_CTRL_WrFL(_g,_r)            ((g_osd_o24_reg->_g._r)=(g_osd_o24_reg_shadow->_g._r))

#define OSDX_CTRL_Rd(_g,_r)              *((UINT32*)(&(g_osd_o24_reg_shadow->_g._r)))
#define OSDX_CTRL_Wr(_g,_r,_v)           ((OSDX_CTRL_Rd(_g,_r))=((UINT32)(_v)))

#define OSDX_CTRL_Rd00(_g,_r,_f)         (g_osd_o24_reg_shadow->_g._r._f)

#define OSDX_CTRL_Rd01(_g,_r,_f01,_v01)  do {                                               \
                                            (_v01) = (g_osd_o24_reg_shadow->_g._r._f01);    \
                                        } while(0)

#define OSDX_CTRL_Wr01(_g,_r,_f01,_v01)  do {                                               \
                                            (g_osd_o24_reg_shadow->_g._r._f01) = (_v01);    \
                                        } while(0)

#define OSDX_CTRL_Wr02(_g,_r,_f01,_v01,_f02,_v02)    do {                                   \
                                            (g_osd_o24_reg_shadow->_g._r._f01) = (_v01);    \
                                            (g_osd_o24_reg_shadow->_g._r._f02) = (_v02);    \
                                        } while(0)


#define OSD_CTRL_RdFL(_r)               ((g_osd_o24_reg_shadow->_r)=(g_osd_o24_reg->_r))
#define OSD_CTRL_WrFL(_r)               ((g_osd_o24_reg->_r)=(g_osd_o24_reg_shadow->_r))

#define OSD_CTRL_Rd(_r)                 *((UINT32*)(&(g_osd_o24_reg_shadow->_r)))
#define OSD_CTRL_Wr(_r,_v)              ((OSD_CTRL_Rd(_r))=((UINT32)(_v)))

#define OSD_CTRL_Rd00(_r,_f)            (g_osd_o24_reg_shadow->_r._f)

#define OSD_CTRL_Rd01(_r,_f01,_v01)                                                         \
                                do {                                                        \
                                    (_v01) = (g_osd_o24_reg_shadow->_r._f01);               \
                                } while(0)

#define OSD_CTRL_Rd02(_r,_f01,_v01,_f02,_v02)                                               \
                                do {                                                        \
                                    (_v01) = (g_osd_o24_reg_shadow->_r._f01);               \
                                    (_v02) = (g_osd_o24_reg_shadow->_r._f02);               \
                                } while(0)

#define OSD_CTRL_Rd03(_r,_f01,_v01,_f02,_v02,_f03,_v03)                                     \
                                do {                                                        \
                                    (_v01) = (g_osd_o24_reg_shadow->_r._f01);               \
                                    (_v02) = (g_osd_o24_reg_shadow->_r._f02);               \
                                    (_v03) = (g_osd_o24_reg_shadow->_r._f03);               \
                                } while(0)

#define OSD_CTRL_Rd04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)                           \
                                do {                                                        \
                                    (_v01) = (g_osd_o24_reg_shadow->_r._f01);               \
                                    (_v02) = (g_osd_o24_reg_shadow->_r._f02);               \
                                    (_v03) = (g_osd_o24_reg_shadow->_r._f03);               \
                                    (_v04) = (g_osd_o24_reg_shadow->_r._f04);               \
                                } while(0)

#define OSD_CTRL_Wr01(_r,_f01,_v01)                                                         \
                                do {                                                        \
                                    (g_osd_o24_reg_shadow->_r._f01) = (_v01);               \
                                } while(0)

#define OSD_CTRL_Wr02(_r,_f01,_v01,_f02,_v02)                                               \
                                do {                                                        \
                                    (g_osd_o24_reg_shadow->_r._f01) = (_v01);               \
                                    (g_osd_o24_reg_shadow->_r._f02) = (_v02);               \
                                } while(0)

#define OSD_CTRL_Wr03(_r,_f01,_v01,_f02,_v02,_f03,_v03)                                     \
                                do {                                                        \
                                    (g_osd_o24_reg_shadow->_r._f01) = (_v01);               \
                                    (g_osd_o24_reg_shadow->_r._f02) = (_v02);               \
                                    (g_osd_o24_reg_shadow->_r._f03) = (_v03);               \
                                } while(0)

#define OSD_CTRL_Wr04(_r,_f01,_v01,_f02,_v02,_f03,_v03,_f04,_v04)                           \
                                do {                                                        \
                                    (g_osd_o24_reg_shadow->_r._f01) = (_v01);               \
                                    (g_osd_o24_reg_shadow->_r._f02) = (_v02);               \
                                    (g_osd_o24_reg_shadow->_r._f03) = (_v03);               \
                                    (g_osd_o24_reg_shadow->_r._f04) = (_v04);               \
                                } while(0)

extern volatile OSD_O24_REG_T*  g_osd_o24_reg;
extern OSD_O24_REG_T*           g_osd_o24_reg_shadow;

#ifdef __cplusplus
}
#endif

#endif  /* _#MOD#_REG_H_ */

/* from 'O24-A0_PQE_OSD_reg_all.csv' 20230407 15:04:25 KST by getregs v2.9 */
