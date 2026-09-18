#ifndef __OSD_TOO_CCO1_CTRL1_E60_H__
#define __OSD_TOO_CCO1_CTRL1_E60_H__

/* this register is generated from TopCTRL_D.CCO1_CTRL1 */
/* this register is generated from TopCTRL_D.CCO2_CTRL1 */

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
	0x0020 ctrl_data_dly ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_osd_alpha_dly               : 4,	//  0: 3
	                                : 4,	//  4: 7 reserved
	reg_lsr_gain_dly                : 7,	//  8:14
	                                :16,	// 15:30 reserved
	reg_dly_cg_en_n                 : 1;	//    31
} CTRL_DATA_DLY;

/*-----------------------------------------------------------------------------
	0x0024 ctrl_osd_120_sync_dly0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	vsync                           :16,	//  0:15
	vfp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY0;

/*-----------------------------------------------------------------------------
	0x0028 ctrl_osd_120_sync_dly1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	va                              :16,	//  0:15
	vbp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY1;

/*-----------------------------------------------------------------------------
	0x002c ctrl_osd_120_sync_dly2 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	hsync                           :16,	//  0:15
	hfp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY2;

/*-----------------------------------------------------------------------------
	0x0030 ctrl_osd_120_sync_dly3 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	ha                              :16,	//  0:15
	hbp                             :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY3;

/*-----------------------------------------------------------------------------
	0x0034 ctrl_osd_120_sync_dly4 ''
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
	0x0038 ctrl_osd_120_sync_dly5 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	sync_h_dly                      :16,	//  0:15
	sync_v_dly                      :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY5;

/*-----------------------------------------------------------------------------
	0x003c ctrl_osd_120_sync_dly6 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	manual_cnt_h_value              :16,	//  0:15
	manual_cnt_v_value              :16;	// 16:31
} CTRL_OSD_120_SYNC_DLY6;

/*-----------------------------------------------------------------------------
	0x0040 ctrl_osd_120_sync_dly7 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_ha_delay                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_va_delay                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_OSD_120_SYNC_DLY7;

/*-----------------------------------------------------------------------------
	0x0044 ctrl_osd_120_sync_dly8 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	auto_hs_delay                   :15,	//  0:14
	auto_general_en                 : 1,	//    15
	auto_vs_delay                   :15,	// 16:30
	auto_seamless                   : 1;	//    31
} CTRL_OSD_120_SYNC_DLY8;

/*-----------------------------------------------------------------------------
	0x0048 ctrl_osd_120_sync_dly9 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	line_cnt_threshold              :16;	//  0:15
} CTRL_OSD_120_SYNC_DLY9;

/*-----------------------------------------------------------------------------
	0x004c ctrl_osd_120_sync_dlya ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	rst_pos_cnt_h                   :16,	//  0:15
	rst_pos_cnt_v                   :16;	// 16:31
} CTRL_OSD_120_SYNC_DLYA;

/*-----------------------------------------------------------------------------
	0x0050 ctrl_cco_ppd_ctrl0 ''
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
	0x0054 ctrl_cco_ppd_ctrl1 ''
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
	0x0058 ctrl_mplus0_spr_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_detour                      : 1,	//     0
	reg_en                          : 1,	//     1
	reg_odd                         : 1,	//     2
	reg_eo_line                     : 1,	//     3
	reg_cg_ptn                      : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_input_resolution            : 2,	//  8: 9
	reg_cut_resolution              : 3,	// 10:12
	                                : 3,	// 13:15 reserved
	reg_spr_max_th                  : 8,	// 16:23
	reg_spr_dif_th                  : 8;	// 24:31
} CTRL_MPLUS0_SPR_CTRL0;

/*-----------------------------------------------------------------------------
	0x005c ctrl_mplus0_spr_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_prv_b_mod_odd_line          : 2,	//  0: 1
	reg_prv_b_mod_evn_line          : 2,	//  2: 3
	reg_prv_g_mod_odd_line          : 2,	//  4: 5
	reg_prv_g_mod_evn_line          : 2,	//  6: 7
	reg_prv_r_mod_odd_line          : 2,	//  8: 9
	reg_prv_r_mod_evn_line          : 2,	// 10:11
	reg_cur_b_mod_odd_line          : 2,	// 12:13
	reg_cur_b_mod_evn_line          : 2,	// 14:15
	reg_cur_g_mod_odd_line          : 2,	// 16:17
	reg_cur_g_mod_evn_line          : 2,	// 18:19
	reg_cur_r_mod_odd_line          : 2,	// 20:21
	reg_cur_r_mod_evn_line          : 2,	// 22:23
	reg_spr_min_th                  : 8;	// 24:31
} CTRL_MPLUS0_SPR_CTRL1;

/*-----------------------------------------------------------------------------
	0x0060 ctrl_mplus1_spr_ctrl0 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_detour                      : 1,	//     0
	reg_en                          : 1,	//     1
	reg_odd                         : 1,	//     2
	reg_eo_line                     : 1,	//     3
	reg_cg_ptn                      : 1,	//     4
	                                : 3,	//  5: 7 reserved
	reg_input_resolution            : 2,	//  8: 9
	reg_cut_resolution              : 3,	// 10:12
	                                : 3,	// 13:15 reserved
	reg_spr_max_th                  : 8,	// 16:23
	reg_spr_dif_th                  : 8;	// 24:31
} CTRL_MPLUS1_SPR_CTRL0;

/*-----------------------------------------------------------------------------
	0x0064 ctrl_mplus1_spr_ctrl1 ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_prv_b_mod_odd_line          : 2,	//  0: 1
	reg_prv_b_mod_evn_line          : 2,	//  2: 3
	reg_prv_g_mod_odd_line          : 2,	//  4: 5
	reg_prv_g_mod_evn_line          : 2,	//  6: 7
	reg_prv_r_mod_odd_line          : 2,	//  8: 9
	reg_prv_r_mod_evn_line          : 2,	// 10:11
	reg_cur_b_mod_odd_line          : 2,	// 12:13
	reg_cur_b_mod_evn_line          : 2,	// 14:15
	reg_cur_g_mod_odd_line          : 2,	// 16:17
	reg_cur_g_mod_evn_line          : 2,	// 18:19
	reg_cur_r_mod_odd_line          : 2,	// 20:21
	reg_cur_r_mod_evn_line          : 2,	// 22:23
	reg_spr_min_th                  : 8;	// 24:31
} CTRL_MPLUS1_SPR_CTRL1;

/*-----------------------------------------------------------------------------
	0x0068 ctrl_mplus0_r_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_r                     :16,	//  0:15
	pattern_cnt_r                   :16;	// 16:31
} CTRL_MPLUS0_R_STAT;

/*-----------------------------------------------------------------------------
	0x006c ctrl_mplus0_g_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_g                     :16,	//  0:15
	pattern_cnt_g                   :16;	// 16:31
} CTRL_MPLUS0_G_STAT;

/*-----------------------------------------------------------------------------
	0x0070 ctrl_mplus0_b_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_b                     :16,	//  0:15
	pattern_cnt_b                   :16;	// 16:31
} CTRL_MPLUS0_B_STAT;

/*-----------------------------------------------------------------------------
	0x0074 ctrl_mplus1_r_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_r                     :16,	//  0:15
	pattern_cnt_r                   :16;	// 16:31
} CTRL_MPLUS1_R_STAT;

/*-----------------------------------------------------------------------------
	0x0078 ctrl_mplus1_g_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_g                     :16,	//  0:15
	pattern_cnt_g                   :16;	// 16:31
} CTRL_MPLUS1_G_STAT;

/*-----------------------------------------------------------------------------
	0x007c ctrl_mplus1_b_stat ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	total_cnt_b                     :16,	//  0:15
	pattern_cnt_b                   :16;	// 16:31
} CTRL_MPLUS1_B_STAT;

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
	reg_osd0_srm_a_cg               : 1,	//     6
	reg_osd0_srm_y_cg               : 1,	//     7
	reg_dsc_top_cg                  : 1,	//     8
	reg_osd_est_layer_cg            : 1,	//     9
	reg_osd_est_shp_cg              : 1,	//    10
	reg_sosd_est_clk_cg             : 1,	//    11
	reg_afbc0_cg                    : 1,	//    12
	reg_afbc1_cg                    : 1;	//    13
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
	0x00a0 ctrl_gate_ctrl ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	reg_gate_tx_img_cr_en           : 1,	//     0
	reg_gate_tx_img_cr_dp_sel       : 3,	//  1: 3
	reg_gate_tx_img_cb_en           : 1,	//     4
	reg_gate_tx_img_cb_dp_sel       : 3,	//  5: 7
	reg_gate_tx_img_yy_en           : 1,	//     8
	reg_gate_tx_img_yy_dp_sel       : 3,	//  9:11
	reg_gate_tx_img_aa_en           : 1,	//    12
	reg_gate_tx_img_aa_dp_sel       : 3,	// 13:15
	reg_gate_tx_osdysr0_en          : 1,	//    16
	reg_gate_tx_osdysr0_dp_sel      : 3,	// 17:19
	reg_gate_tx_osdysr1_en          : 1,	//    20
	reg_gate_tx_osdysr1_dp_sel      : 3,	// 21:23
	reg_gate_tx_osdasr0_en          : 1,	//    24
	reg_gate_tx_osdasr0_dp_sel      : 3,	// 25:27
	reg_gate_tx_osdasr1_en          : 1,	//    28
	reg_gate_tx_osdasr1_dp_sel      : 3;	// 29:31
} CTRL_GATE_CTRL;

/*-----------------------------------------------------------------------------
	0x00bc axi_user_cco ''
------------------------------------------------------------------------------*/
typedef struct {
	UINT32
	cco0_aruser                     : 4,	//  0: 3
	                                : 4,	//  4: 7 reserved
	cco1_aruser                     : 4;	//  8:11
} AXI_USER_CCO;

typedef struct {
	UINT32                          	                 __rsvd_00[   8];	// 0x0000 ~ 0x001c
	CTRL_DATA_DLY                   	ctrl_data_dly                   ;	// 0x0020 : ''
	CTRL_OSD_120_SYNC_DLY0          	ctrl_osd_120_sync_dly0          ;	// 0x0024 : ''
	CTRL_OSD_120_SYNC_DLY1          	ctrl_osd_120_sync_dly1          ;	// 0x0028 : ''
	CTRL_OSD_120_SYNC_DLY2          	ctrl_osd_120_sync_dly2          ;	// 0x002c : ''
	CTRL_OSD_120_SYNC_DLY3          	ctrl_osd_120_sync_dly3          ;	// 0x0030 : ''
	CTRL_OSD_120_SYNC_DLY4          	ctrl_osd_120_sync_dly4          ;	// 0x0034 : ''
	CTRL_OSD_120_SYNC_DLY5          	ctrl_osd_120_sync_dly5          ;	// 0x0038 : ''
	CTRL_OSD_120_SYNC_DLY6          	ctrl_osd_120_sync_dly6          ;	// 0x003c : ''
	CTRL_OSD_120_SYNC_DLY7          	ctrl_osd_120_sync_dly7          ;	// 0x0040 : ''
	CTRL_OSD_120_SYNC_DLY8          	ctrl_osd_120_sync_dly8          ;	// 0x0044 : ''
	CTRL_OSD_120_SYNC_DLY9          	ctrl_osd_120_sync_dly9          ;	// 0x0048 : ''
	CTRL_OSD_120_SYNC_DLYA          	ctrl_osd_120_sync_dlya          ;	// 0x004c : ''
	CTRL_CCO_PPD_CTRL0              	ctrl_cco_ppd_ctrl0              ;	// 0x0050 : ''
	CTRL_CCO_PPD_CTRL1              	ctrl_cco_ppd_ctrl1              ;	// 0x0054 : ''
	CTRL_MPLUS0_SPR_CTRL0           	ctrl_mplus0_spr_ctrl0           ;	// 0x0058 : ''
	CTRL_MPLUS0_SPR_CTRL1           	ctrl_mplus0_spr_ctrl1           ;	// 0x005c : ''
	CTRL_MPLUS1_SPR_CTRL0           	ctrl_mplus1_spr_ctrl0           ;	// 0x0060 : ''
	CTRL_MPLUS1_SPR_CTRL1           	ctrl_mplus1_spr_ctrl1           ;	// 0x0064 : ''
	CTRL_MPLUS0_R_STAT              	ctrl_mplus0_r_stat              ;	// 0x0068 : ''
	CTRL_MPLUS0_G_STAT              	ctrl_mplus0_g_stat              ;	// 0x006c : ''
	CTRL_MPLUS0_B_STAT              	ctrl_mplus0_b_stat              ;	// 0x0070 : ''
	CTRL_MPLUS1_R_STAT              	ctrl_mplus1_r_stat              ;	// 0x0074 : ''
	CTRL_MPLUS1_G_STAT              	ctrl_mplus1_g_stat              ;	// 0x0078 : ''
	CTRL_MPLUS1_B_STAT              	ctrl_mplus1_b_stat              ;	// 0x007c : ''
	CTRL_L3D_DMA_SIZE               	ctrl_l3d_dma_size               ;	// 0x0080 : ''
	CTRL_L3D_DMA_CTRL               	ctrl_l3d_dma_ctrl               ;	// 0x0084 : ''
	CTRL_RO_L3D_VCNT                	ctrl_ro_l3d_vcnt                ;	// 0x0088 : ''
	CTRL_VR360_ON                   	ctrl_vr360_on                   ;	// 0x008c : ''
	CTRL_CG_ON                      	ctrl_cg_on                      ;	// 0x0090 : ''
	CTRL_CG_ON_SYNC                 	ctrl_cg_on_sync                 ;	// 0x0094 : ''
	CTRL_VR360_VID_DATA0            	ctrl_vr360_vid_data0            ;	// 0x0098 : ''
	CTRL_VR360_VID_DATA1            	ctrl_vr360_vid_data1            ;	// 0x009c : ''
	CTRL_GATE_CTRL                  	ctrl_gate_ctrl                  ;	// 0x00a0 : ''
	UINT32                          	                 __rsvd_01[   6];	// 0x00a4 ~ 0x00b8
	AXI_USER_CCO                    	axi_user_cco                    ;	// 0x00bc : ''
}
OSD_CCO_TOP1_E60_REG_T, OSD_CCO1_TOP1_E60_REG_T, OSD_CCO2_TOP1_E60_REG_T; /* 59 regs, 59 types */
/* 34 regs, 34 types */

/* 34 regs, 34 types in Total*/

#ifdef __cplusplus
}
#endif

#endif	/* _#MOD#_REG_H_ */

/* from 'E60-A0_PQE_TopCTRL_D_reg_man.csv' 20200806 19:10:36 KST by getregs v2.9 */
