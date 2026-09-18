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

#ifndef _PE_DPE_REG_O20A0_H_
#define _PE_DPE_REG_O20A0_H_

/*-----------------------------------------------------------------------------
		0xc8020540L ad_rp_hv_pos ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rp_v_pos                           : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 rp_h_pos                           : 12;  // 27:16     
} PE_LED_O20_AD_RP_HV_POS_T;

/*-----------------------------------------------------------------------------
		0xc8020544L ad_rp_make_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mark_en                            : 1 ;  //     0     
} PE_LED_O20_AD_RP_MAKE_EN_T;

/*-----------------------------------------------------------------------------
		0xc8020548L ad_rp_r_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_r                         : 14;  // 13: 0     
} PE_LED_O20_AD_RP_R_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc802054cL ad_rp_g_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_g                         : 14;  // 13: 0     
} PE_LED_O20_AD_RP_G_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc8020550L ad_rp_b_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_b                         : 14;  // 13: 0     
} PE_LED_O20_AD_RP_B_VALUE_T;

/*-----------------------------------------------------------------------------
                             0xc9023800L reg_decon_top_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hei                            :12,	// 11:0
	reserved01                         :1 ,	// reserved
	reh_mode_2ch                       :1 ,	// 13
	dither_temporal_en                 :1 ,	// 14
	dither_en                          :1 ,	// 15
	reg_wid                            :12,	// 27:16
	reserved02                         :1 ,	// reserved
	reg_decon_out_bit_opt              :1 ,	// 29
	reg_decon_in_bit_opt               :1 ,	// 30
	reg_decon_detour_en                :1 ;	// 31
}PE_O20_REG_LED_DECON_TOP_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9023804L reg_decon_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_use_osd_map         :1 ,	// 0 
	reg_2nd_out_rd_out_clip            :1 ,	// 1 
	reg_1st_out_rd_out_clip            :1 ,	// 2 
	reserved01                         :4 ,	// reserved
	reg_decon_dnr_motion_sel           :1 ,	// 7 
	reg_11bit_debug_mode_en            :1 ,	// 8 
	reg_out_bit_opt                    :1 ,	// 9 
	reg_tnr_decon_out_bit_sel          :1 ,	// 10
	reg_tnr_decon_in_bit_sel           :1 ,	// 11
	reg_1st_out_rd_max_alpha           :8 ,	// 19:12
	reg_1st_out_rd_min_alpha           :8 ,	// 27:20
	reg_1st_out_rd_bit                 :3 ,	// 30:28
	reg_1st_out_rd_on                  :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9023808L reg_decon_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_min_pel_cb          :12,	// 11:0
	reg_1st_out_rd_min_pel_yy          :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc902380cL reg_decon_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_yy          :12,	// 11:0
	reg_1st_out_rd_min_pel_cr          :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9023810L reg_decon_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_cr          :12,	// 11:0
	reg_1st_out_rd_max_pel_cb          :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9023814L reg_decon_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9023818L reg_decon_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc902381cL reg_decon_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9023820L reg_decon_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_bit                 :4 ,	// 7:4
	reserved02                         :3 ,	// reserved
	reg_2nd_out_rd_use_osd_map         :1 ,	// 11
	reg_2nd_out_rd_max_alpha           :8 ,	// 19:12
	reg_2nd_out_rd_min_alpha           :8 ,	// 27:20
	reserved03                         :3 ,	// reserved
	reg_2nd_out_rd_on                  :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9023824L reg_decon_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_min_pel_cb          :12,	// 11:0
	reg_2nd_out_rd_min_pel_yy          :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_max_lsb_2b          :2 ,	// 29:28
	reg_2nd_out_rd_min_lsb_2b          :2 ;	// 31:30
}PE_O20_REG_LED_DECON_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9023828L reg_decon_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_yy          :12,	// 11:0
	reg_2nd_out_rd_min_pel_cr          :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc902382cL reg_decon_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_cr          :12,	// 11:0
	reg_2nd_out_rd_max_pel_cb          :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9023830L reg_decon_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9023834L reg_decon_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9023838L reg_decon_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc902383cL reg_decon_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9023840L reg_decon_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9023844L reg_decon_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9023848L reg_decon_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_lb_var_cut_res            :4 ,	// 3:0
	reserved01                         :2 ,	// reserved
	reg_blur_lb_var_en                 :1 ,	// 6 
	reg_l6_var_2x2_bit                 :1 ,	// 7 
	reg_force_block_v                  :6 ,	// 13:8
	reg_1st_debug_en                   :1 ,	// 14
	reg_l6_var_csc_en                  :1 ,	// 15
	reg_force_block_no_h               :6 ,	// 21:16
	reg_4k_5x3_mode_en                 :1 ,	// 22
	reg_rd_simple_clip                 :1 ,	// 23
	reg_rd_clip                        :1 ,	// 24
	reg_input_csc_en                   :1 ,	// 25
	reg_1st_debug_mode                 :4 ,	// 29:26
	reg_force_block_no_en              :1 ,	// 30
	reg_decon_1st_en                   :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc902384cL reg_decon_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_var_chroma_en                  :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	reg_blur_final_size                :1 ,	// 2 
	reserved02                         :1 ,	// reserved
	reg_blur_div_zero                  :1 ,	// 4 
	reg_diff_hblur                     :2 ,	// 6:5
	reg_diff_vblur                     :2 ,	// 8:7
	reg_motion_shft                    :3 ,	// 11:9
	reg_motion_en                      :1 ,	// 12
	reg_led_10b_mode_blending          :1 ,	// 13
	reg_led_10b_mode_diff_pel          :1 ,	// 14
	reserved03                         :1 ,	// reserved
	reg_luma_bit_opt                   :1 ,	// 16
	reg_var_bit_opt                    :1 ,	// 17
	reg_l6_var_bit_opt                 :1 ,	// 18
	reg_l6_blur_bit_opt                :1 ,	// 19
	reg_var_v_gain                     :4 ,	// 23:20
	reg_var_h_gain                     :4 ,	// 27:24
	reg_var_cut_resolution             :4 ;	// 31:28
}PE_O20_REG_LED_DECON_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9023850L reg_decon_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_x_th0               :8 ,	// 7:0
	reg_decon_diff_x_th1               :8 ,	// 15:8
	reg_decon_diff_x_th2               :8 ,	// 23:16
	reg_decon_diff_x_th3               :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9023854L reg_decon_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_y_th0               :8 ,	// 7:0
	reg_decon_diff_y_th1               :8 ,	// 15:8
	reg_decon_diff_y_th2               :8 ,	// 23:16
	reg_decon_diff_y_th3               :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9023858L reg_decon_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_x_th2                :10,	// 9:0
	reg_decon_var_x_th1                :10,	// 19:10
	reg_decon_var_x_th0                :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc902385cL reg_decon_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_y_th1                :10,	// 9:0
	reg_decon_var_y_th0                :10,	// 19:10
	reg_decon_var_x_th3                :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc9023860L reg_decon_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th0               :10,	// 9:0
	reg_decon_var_y_th3                :10,	// 19:10
	reg_decon_var_y_th2                :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9023864L reg_dec_sync_2dly_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9023868L reg_dec_sync_2dly_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc902386cL reg_dec_sync_2dly_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9023870L reg_dec_sync_2dly_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc9023874L reg_dec_sync_2dly_ctrl4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	// 15:0
	sync_i_h_sel                       :1 ,	// 16
	sync_i_v_sel                       :1 ,	// 17
	sync_i_inv_ha                      :1 ,	// 18
	sync_i_inv_va                      :1 ,	// 19
	sync_o_sel_ha                      :1 ,	// 20
	sync_o_sel_va                      :1 ,	// 21
	sync_o_sel_hs                      :1 ,	// 22
	sync_o_sel_vs                      :1 ,	// 23
	tp_update_hv_zero                  :1 ,	// 24
	force_out_ha                       :1 ,	// 25
	force_out_va                       :1 ,	// 26
	force_out_hs                       :1 ,	// 27
	manual_cnt_h_value_en              :1 ,	// 28
	manual_cnt_v_value_en              :1 ,	// 29
	force_out_vs                       :1 ,	// 30
	update_force                       :1 ;	// 31
}PE_O20_REG_DEC_SYNC_2DLY_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc9023878L reg_dec_sync_2dly_ctrl5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc902387cL reg_dec_sync_2dly_ctrl6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc9023880L reg_dec_sync_2dly_ctrl7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_7;	// 31:0
}PE_O20_REG_DEC_SYNC_2DLY_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc9023884L reg_dec_sync_2dly_ctrl8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_8;	// 31:0
}PE_O20_REG_DEC_SYNC_2DLY_CTRL8_T;
/*-----------------------------------------------------------------------------
                             0xc9023888L reg_dec_sync_2dly_ctrl9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_normal_number                  :16;	// 15:0
}PE_O20_REG_DEC_SYNC_2DLY_CTRL9_T;
/*-----------------------------------------------------------------------------
                             0xc902388cL reg_dec_sync_2dly_ctrla                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rst_pos_cnt_h                      :16,	// 15:0
	rst_pos_cnt_v                      :16;	// 31:16
}PE_O20_REG_DEC_SYNC_2DLY_CTRLA_T;
/*-----------------------------------------------------------------------------
                             0xc9023890L reg_dec_sync_3dly_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9023894L reg_dec_sync_3dly_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9023898L reg_dec_sync_3dly_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc902389cL reg_dec_sync_3dly_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc90238a0L reg_dec_sync_3dly_ctrl4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	// 15:0
	sync_i_h_sel                       :1 ,	// 16
	sync_i_v_sel                       :1 ,	// 17
	sync_i_inv_ha                      :1 ,	// 18
	sync_i_inv_va                      :1 ,	// 19
	sync_o_sel_ha                      :1 ,	// 20
	sync_o_sel_va                      :1 ,	// 21
	sync_o_sel_hs                      :1 ,	// 22
	sync_o_sel_vs                      :1 ,	// 23
	tp_update_hv_zero                  :1 ,	// 24
	force_out_ha                       :1 ,	// 25
	force_out_va                       :1 ,	// 26
	force_out_hs                       :1 ,	// 27
	manual_cnt_h_value_en              :1 ,	// 28
	manual_cnt_v_value_en              :1 ,	// 29
	force_out_vs                       :1 ,	// 30
	update_force                       :1 ;	// 31
}PE_O20_REG_DEC_SYNC_3DLY_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc90238a4L reg_dec_sync_3dly_ctrl5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc90238a8L reg_dec_sync_3dly_ctrl6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc90238acL reg_dec_sync_3dly_ctrl7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_7;	// 31:0
}PE_O20_REG_DEC_SYNC_3DLY_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc90238b0L reg_dec_sync_3dly_ctrl8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_8;	// 31:0
}PE_O20_REG_DEC_SYNC_3DLY_CTRL8_T;
/*-----------------------------------------------------------------------------
                             0xc90238b4L reg_dec_sync_3dly_ctrl9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_normal_number                  :16;	// 15:0
}PE_O20_REG_DEC_SYNC_3DLY_CTRL9_T;
/*-----------------------------------------------------------------------------
                             0xc90238b8L reg_dec_sync_3dly_ctrla                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rst_pos_cnt_h                      :16,	// 15:0
	rst_pos_cnt_v                      :16;	// 31:16
}PE_O20_REG_DEC_SYNC_3DLY_CTRLA_T;
/*-----------------------------------------------------------------------------
                             0xc90238bcL reg_decon_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th3               :10,	// 9:0
	reg_decon_luma_x_th2               :10,	// 19:10
	reg_decon_luma_x_th1               :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90238c0L reg_decon_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th6               :10,	// 9:0
	reg_decon_luma_x_th5               :10,	// 19:10
	reg_decon_luma_x_th4               :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90238c4L reg_decon_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th1               :10,	// 9:0
	reg_decon_luma_y_th0               :10,	// 19:10
	reg_decon_luma_x_th7               :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90238c8L reg_decon_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th4               :10,	// 9:0
	reg_decon_luma_y_th3               :10,	// 19:10
	reg_decon_luma_y_th2               :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90238ccL reg_decon_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th7               :10,	// 9:0
	reg_decon_luma_y_th6               :10,	// 19:10
	reg_decon_luma_y_th5               :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90238d0L reg_decon_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_block_size_v                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_block_size_h                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_block_no_v                     :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_block_no_h                     :6 ,	// 29:24
	reserved04                         :1 ,	// reserved
	reg_block_info_force_en            :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90238d4L reg_decon_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_last_block_size_v              :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_last_block_size_h              :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_diff_mul_new                   :4 ,	// 19:16
	reg_diff_shift                     :3 ,	// 22:20
	reg_osd_run_mode                   :1 ,	// 23
	reg_alpha_blur_l6_var_sm           :1 ,	// 24
	reg_alpha_blur_mode                :2 ,	// 26:25
	reg_blending_alpha_use_l6_var      :2 ,	// 28:27
	reg_diff_use_seldiff               :1 ,	// 29
	reg_diff_calc_mode                 :2 ;	// 31:30
}PE_O20_REG_LED_DECON_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90238d8L reg_decon_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_alpha_blur_l6_var_th1          :10,	// 9:0
	reg_alpha_blur_l6_var_th0          :10,	// 19:10
	reg_lb_var_cut_res                 :4 ,	// 23:20
	reg_master_gain                    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90238dcL reg_decon_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_x_th2                   :10,	// 9:0
	reg_l6_var_x_th1                   :10,	// 19:10
	reg_l6_var_x_th0                   :10,	// 29:20
	reg_lb_var_opt                     :1 ,	// 30
	reg_lb_var_en                      :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90238e0L reg_decon_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th1                   :10,	// 9:0
	reg_l6_var_y_th0                   :10,	// 19:10
	reg_l6_var_x_th3                   :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_lb_var_lut_bit                 :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90238e4L reg_decon_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th3                   :10,	// 9:0
	reg_l6_var_y_th2                   :10,	// 19:10
	reg_l6_pel_trunc                   :2 ,	// 21:20
	reg_var_v_cut                      :2 ,	// 23:22
	reg_var_h_cut                      :2 ,	// 25:24
	reg_var_t7_offset                  :2 ,	// 27:26
	reg_decon_rd_simple_bit            :3 ,	// 30:28
	reg_decon_rd_simple_on             :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90238e8L reg_decon_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc90238ecL reg_decon_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc90238f0L reg_decon_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc90238f4L reg_decon_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_min_pel_cb                  :12,	// 11:0
	reg_rd_min_pel_yy                  :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_rd_bit                         :3 ,	// 30:28
	reg_decon_rd_on                    :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc90238f8L reg_decon_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_yy                  :12,	// 11:0
	reg_rd_min_pel_cr                  :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc90238fcL reg_decon_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_cr                  :12,	// 11:0
	reg_rd_max_pel_cb                  :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc9023900L reg_decon_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc9023904L reg_decon_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc9023908L reg_decon_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc902390cL reg_decon_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_x3                 :8 ,	// 7:0
	reg_motion_gain_x2                 :8 ,	// 15:8
	reg_motion_gain_x1                 :8 ,	// 23:16
	reg_motion_gain_x0                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc9023910L reg_decon_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_y3                 :8 ,	// 7:0
	reg_motion_gain_y2                 :8 ,	// 15:8
	reg_motion_gain_y1                 :8 ,	// 23:16
	reg_motion_gain_y0                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc9023914L reg_decon_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_y0                         :12,	// 11:0
	reg_bbd_x0                         :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_blur3_sim_en                   :1 ,	// 28
	reg_blur2_sim_en                   :1 ,	// 29
	reg_amf_lut_bit                    :1 ,	// 30
	reg_bbd_en                         :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc9023918L reg_decon_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_y1                         :12,	// 11:0
	reg_bbd_x1                         :12,	// 23:12
	reserved01                         :2 ,	// reserved
	reg_blur3_sim_ratio                :3 ,	// 28:26
	reg_blur2_sim_ratio                :3 ;	// 31:29
}PE_O20_REG_LED_DECON_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc902391cL reg_decon_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_blur_sim_x3                :8 ,	// 7:0
	reg_lut_blur_sim_x2                :8 ,	// 15:8
	reg_lut_blur_sim_x1                :8 ,	// 23:16
	reg_lut_blur_sim_x0                :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc9023920L reg_decon_ctrl_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_blur_sim_y3                :8 ,	// 7:0
	reg_lut_blur_sim_y2                :8 ,	// 15:8
	reg_lut_blur_sim_y1                :8 ,	// 23:16
	reg_lut_blur_sim_y0                :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc9023924L reg_decon_ctrl_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_yy_x3                 :8 ,	// 7:0
	reg_lut_skin_yy_x2                 :8 ,	// 15:8
	reg_lut_skin_yy_x1                 :8 ,	// 23:16
	reg_lut_skin_yy_x0                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc9023928L reg_decon_ctrl_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_cb_x3                 :8 ,	// 7:0
	reg_lut_skin_cb_x2                 :8 ,	// 15:8
	reg_lut_skin_cb_x1                 :8 ,	// 23:16
	reg_lut_skin_cb_x0                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc902392cL reg_decon_ctrl_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_cr_x3                 :8 ,	// 7:0
	reg_lut_skin_cr_x2                 :8 ,	// 15:8
	reg_lut_skin_cr_x1                 :8 ,	// 23:16
	reg_lut_skin_cr_x0                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc9023930L reg_decon_ctrl_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_y3                    :8 ,	// 7:0
	reg_lut_skin_y2                    :8 ,	// 15:8
	reg_lut_skin_y1                    :8 ,	// 23:16
	reg_lut_skin_y0                    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc9023934L reg_decon_ctrl_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_face_x3                    :8 ,	// 7:0
	reg_lut_face_x2                    :8 ,	// 15:8
	reg_lut_face_x1                    :8 ,	// 23:16
	reg_lut_face_x0                    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc9023938L reg_decon_ctrl_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_face_y3                    :8 ,	// 7:0
	reg_lut_face_y2                    :8 ,	// 15:8
	reg_lut_face_y1                    :8 ,	// 23:16
	reg_lut_face_y0                    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc902393cL reg_decon_ctrl_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :19,	// reserved
	reg_face_skin_opt                  :1 ,	// 19
	reg_face_master_gain               :8 ,	// 27:20
	reg_face_shft                      :2 ,	// 29:28
	reg_face_en                        :1 ,	// 30
	reg_skin_en                        :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc9023940L reg_decon_ctrl_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_dist_h             :4 ,	// 3:0
	reg_l6_var_diff_dist_w             :4 ;	// 7:4
}PE_O20_REG_LED_DECON_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc9023944L reg_decon_ctrl_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_cr              :10,	// 9:0
	reg_l6_var_diff_th_cb              :10,	// 19:10
	reg_l6_var_diff_th_yy              :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc9023948L reg_decon_ctrl_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_yy3             :10,	// 9:0
	reg_l6_var_diff_th_yy2             :10;	// 19:10
}PE_O20_REG_LED_DECON_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc902394cL reg_decon_ctrl_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_yy3         :10,	// 9:0
	reg_l6_var_diff_th_min_yy2         :10,	// 19:10
	reg_l6_var_diff_th_min_yy          :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc9023950L reg_decon_ctrl_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_cc3         :10,	// 9:0
	reg_l6_var_diff_th_min_cc2         :10,	// 19:10
	reg_l6_var_diff_th_min_cc          :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_l6_var_reshape_en              :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc9023954L reg_decon_ctrl_62                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_yy_cond_cb_adj_ratio  :8 ,	// 7:0
	reg_l6_var_v_yy_cond_yy_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_diff_yy_cond_ratio    :8 ,	// 23:16
	reg_l6_var_v_diff_yy_cond_ratio    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_62_T;
/*-----------------------------------------------------------------------------
                             0xc9023958L reg_decon_ctrl_63                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_yy_cond_cr_adj_ratio  :8 ,	// 7:0
	reg_l6_var_h_yy_cond_cb_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_yy_cond_yy_adj_ratio  :8 ,	// 23:16
	reg_l6_var_v_yy_cond_cr_adj_ratio  :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_63_T;
/*-----------------------------------------------------------------------------
                             0xc902395cL reg_decon_ctrl_64                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_l6_var_cc_cond_cr_adj_ratio    :8 ,	// 15:8
	reg_l6_var_cc_cond_cb_adj_ratio    :8 ,	// 23:16
	reg_l6_var_cc_cond_yy_adj_ratio    :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_64_T;
/*-----------------------------------------------------------------------------
                             0xc9023960L reg_decon_ctrl_65                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_diff_cut_value        :12,	// 11:0
	reg_l6_var_v_diff_th               :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_65_T;
/*-----------------------------------------------------------------------------
                             0xc9023964L reg_decon_ctrl_66                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_diff_cut_value        :12,	// 11:0
	reg_l6_var_h_diff_th               :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_66_T;
/*-----------------------------------------------------------------------------
                             0xc9023968L reg_decon_ctrl_67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_max_rep_value:12,	// 11:0
	reg_l6_var_total_diff_max_th       :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_67_T;
/*-----------------------------------------------------------------------------
                             0xc902396cL reg_decon_ctrl_68                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_low_rep_value:12,	// 11:0
	reg_l6_var_total_diff_low_th       :12;	// 23:12
}PE_O20_REG_LED_DECON_CTRL_68_T;
/*-----------------------------------------------------------------------------
                             0xc9023970L reg_decon_ctrl_69                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_diff_mul                       :4 ,	// 3:0
	reg_2nd_diff_shift                 :3 ,	// 6:4
	reg_2nd_alpha_blur_mode            :1 ,	// 7 
	reg_2nd_debug_mode                 :3 ,	// 10:8
	reg_odd_sel                        :1 ,	// 11
	reg_2nd_osd_run_mode               :1 ,	// 12
	reg_2nd_rd_simple_bit              :3 ,	// 15:13
	reg_2nd_rd_simple_on               :1 ,	// 16
	reg_input_csc_en                   :1 ,	// 17
	reg_2nd_var_v_gain                 :2 ,	// 19:18
	reg_2nd_var_h_gain                 :2 ,	// 21:20
	reg_2nd_var_cut_resolution         :3 ,	// 24:22
	reg_2nd_var_chroma_en              :1 ,	// 25
	reg_2nd_var_sel_tmp                :2 ,	// 27:26
	reg_2nd_fil_sel_tmp                :2 ,	// 29:28
	reg_2nd_debug_en                   :1 ,	// 30
	reg_decon_2nd_en                   :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_69_T;
/*-----------------------------------------------------------------------------
                             0xc9023974L reg_decon_ctrl_70                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th2                 :10,	// 9:0
	reg_2nd_luma_x_th1                 :10,	// 19:10
	reg_2nd_luma_x_th0                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_444_mode                       :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_70_T;
/*-----------------------------------------------------------------------------
                             0xc9023978L reg_decon_ctrl_71                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th5                 :10,	// 9:0
	reg_2nd_luma_x_th4                 :10,	// 19:10
	reg_2nd_luma_x_th3                 :10,	// 29:20
	reg_2nd_luma_bit_opt               :2 ;	// 31:30
}PE_O20_REG_LED_DECON_CTRL_71_T;
/*-----------------------------------------------------------------------------
                             0xc902397cL reg_decon_ctrl_72                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th0                 :10,	// 9:0
	reg_2nd_luma_x_th7                 :10,	// 19:10
	reg_2nd_luma_x_th6                 :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_72_T;
/*-----------------------------------------------------------------------------
                             0xc9023980L reg_decon_ctrl_73                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th3                 :10,	// 9:0
	reg_2nd_luma_y_th2                 :10,	// 19:10
	reg_2nd_luma_y_th1                 :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_73_T;
/*-----------------------------------------------------------------------------
                             0xc9023984L reg_decon_ctrl_74                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th6                 :10,	// 9:0
	reg_2nd_luma_y_th5                 :10,	// 19:10
	reg_2nd_luma_y_th4                 :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_74_T;
/*-----------------------------------------------------------------------------
                             0xc9023988L reg_decon_ctrl_75                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_x_th1                  :10,	// 9:0
	reg_2nd_var_x_th0                  :10,	// 19:10
	reg_2nd_luma_y_th7                 :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_75_T;
/*-----------------------------------------------------------------------------
                             0xc902398cL reg_decon_ctrl_76                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th0                  :10,	// 9:0
	reg_2nd_var_x_th3                  :10,	// 19:10
	reg_2nd_var_x_th2                  :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_76_T;
/*-----------------------------------------------------------------------------
                             0xc9023990L reg_decon_ctrl_77                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th3                  :10,	// 9:0
	reg_2nd_var_y_th2                  :10,	// 19:10
	reg_2nd_var_y_th1                  :10;	// 29:20
}PE_O20_REG_LED_DECON_CTRL_77_T;
/*-----------------------------------------------------------------------------
                             0xc9023994L reg_decon_ctrl_78                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_x_th0                 :8 ,	// 7:0
	reg_2nd_diff_x_th1                 :8 ,	// 15:8
	reg_2nd_diff_x_th2                 :8 ,	// 23:16
	reg_2nd_diff_x_th3                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_78_T;
/*-----------------------------------------------------------------------------
                             0xc9023998L reg_decon_ctrl_79                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_y_th0                 :8 ,	// 7:0
	reg_2nd_diff_y_th1                 :8 ,	// 15:8
	reg_2nd_diff_y_th2                 :8 ,	// 23:16
	reg_2nd_diff_y_th3                 :8 ;	// 31:24
}PE_O20_REG_LED_DECON_CTRL_79_T;
/*-----------------------------------------------------------------------------
                             0xc902399cL reg_decon_ctrl_80                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_yy;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_80_T;
/*-----------------------------------------------------------------------------
                             0xc90239a0L reg_decon_ctrl_81                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cb;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_81_T;
/*-----------------------------------------------------------------------------
                             0xc90239a4L reg_decon_ctrl_82                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cr;	// 31:0
}PE_O20_REG_LED_DECON_CTRL_82_T;
/*-----------------------------------------------------------------------------
                             0xc90239a8L reg_decon_ctrl_83                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_boundary_x_end                 :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_boundary_x_start               :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_boundary_side                  :1 ,	// 30
	reg_boundary_en                    :1 ;	// 31
}PE_O20_REG_LED_DECON_CTRL_83_T;

typedef struct {
	PE_LED_O20_AD_RP_HV_POS_T            	ad_rp_hv_pos;                 //0xc8020540L
	PE_LED_O20_AD_RP_MAKE_EN_T           	ad_rp_make_en;                //0xc8020544L
	PE_LED_O20_AD_RP_R_VALUE_T           	ad_rp_r_value;                //0xc8020548L
	PE_LED_O20_AD_RP_G_VALUE_T           	ad_rp_g_value;                //0xc802054cL
	PE_LED_O20_AD_RP_B_VALUE_T           	ad_rp_b_value;                //0xc8020550L
}PE_LED_RP_REG_O20_T;

/*********** exist in only F20 *************/
typedef struct {
	UINT32
	reg_2nd_rd_roi_cut_out           :2,	//1:0	//0: x1, 1: /2, 2: /4, 3: /8
	reg_2nd_rd_roi_cut_in            :2,	//3:2	//0: x1, 1: /2, 2: /4, 3: /8
	reg_1st_rd_roi_cut_out           :2,	//5:4	//0: x1, 1: /2, 2: /4, 3: /8
	reg_1st_rd_roi_cut_in            :2,	//7:6	//0: x1, 1: /2, 2: /4, 3: /8
	reg_2nd_rd_luma_cut              :2,	//9:8	//0: x1, 1: /2, 2: /4, 3: /8
	reg_1st_rd_luma_cut              :2,	//11:10	//0: x1, 1: /2, 2: /4, 3: /8
	resvd0                           :16,
	reg_2nd_rd_luma_en               :1,	//28 //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	reg_1st_rd_luma_en               :1,	//29 //0: 1st_rd_luma off, 1: 1st_rd_luma on
	reg_rd_roi_en                    :1,	//30 //0: rd_roi off, 1: rd_roi on
	resvd1                           :1;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_84_T;

typedef struct {
	UINT32
	reg_rd_roi_x1                    :12,	//11:0	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	resvd0                           :4,
	reg_rd_roi_x0                    :12,	//27:16	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	resvd1                           :4;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_85_T;

typedef struct {
	UINT32
	reg_rd_roi_y1                    :12,	//11:0	//
	resvd0                           :4,
	reg_rd_roi_y0                    :12,	//27:16	//
	resvd1                           :4;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_86_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_x1               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	reg_1st_rd_luma_x0               :10,	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	reg_out_prev_x                   :12;	//31:20	//Defualt: 30	이전 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_87_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_x3               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	reg_1st_rd_luma_x2               :10,	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	reg_out_next_x                   :12;	//31:20	//Defualt: 40	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_88_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_x5               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_x4               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :2,
	reg_out_prev_y                   :7,	//30:24	//Defualt: 120	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	resvd2                           :1;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_89_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_x7               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_x6               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :2,
	reg_out_next_y                   :7,	//30:24	//Defualt: 121	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	resvd2                           :1;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_90_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_y1               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_y0               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :10;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_91_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_y3               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_y2               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :10;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_92_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_y5               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_y4               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :10;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_93_T;

typedef struct {
	UINT32
	reg_1st_rd_luma_y7               :10,	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd0                           :2,
	reg_1st_rd_luma_y6               :10,	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	resvd1                           :10;
}PE_F20_REG_LED_DECONTOUR_0_REG_DECON_CTRL_94_T;

typedef struct
{ 
	PE_O20_REG_LED_DECON_TOP_CTRL_T                       reg_decon_top_ctrl;	//0x0000
	PE_O20_REG_LED_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0004
	PE_O20_REG_LED_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0008
	PE_O20_REG_LED_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x000C
	PE_O20_REG_LED_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0010
	PE_O20_REG_LED_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0014
	PE_O20_REG_LED_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0018
	PE_O20_REG_LED_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x001C
	PE_O20_REG_LED_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0020
	PE_O20_REG_LED_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0024
	PE_O20_REG_LED_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0028
	PE_O20_REG_LED_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x002C
	PE_O20_REG_LED_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x0030
	PE_O20_REG_LED_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x0034
	PE_O20_REG_LED_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x0038
	PE_O20_REG_LED_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x003C
	PE_O20_REG_LED_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x0040
	PE_O20_REG_LED_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x0044
	PE_O20_REG_LED_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x0048
	PE_O20_REG_LED_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x004C
	PE_O20_REG_LED_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x0050
	PE_O20_REG_LED_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x0054
	PE_O20_REG_LED_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x0058
	PE_O20_REG_LED_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x005C
	PE_O20_REG_LED_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x0060
	PE_O20_REG_DEC_SYNC_2DLY_CTRL0_T                  reg_dec_sync_2dly_ctrl0;	//0x0064
	PE_O20_REG_DEC_SYNC_2DLY_CTRL1_T                  reg_dec_sync_2dly_ctrl1;	//0x0068
	PE_O20_REG_DEC_SYNC_2DLY_CTRL2_T                  reg_dec_sync_2dly_ctrl2;	//0x006C
	PE_O20_REG_DEC_SYNC_2DLY_CTRL3_T                  reg_dec_sync_2dly_ctrl3;	//0x0070
	PE_O20_REG_DEC_SYNC_2DLY_CTRL4_T                  reg_dec_sync_2dly_ctrl4;	//0x0074
	PE_O20_REG_DEC_SYNC_2DLY_CTRL5_T                  reg_dec_sync_2dly_ctrl5;	//0x0078
	PE_O20_REG_DEC_SYNC_2DLY_CTRL6_T                  reg_dec_sync_2dly_ctrl6;	//0x007C
	PE_O20_REG_DEC_SYNC_2DLY_CTRL7_T                  reg_dec_sync_2dly_ctrl7;	//0x0080
	PE_O20_REG_DEC_SYNC_2DLY_CTRL8_T                  reg_dec_sync_2dly_ctrl8;	//0x0084
	PE_O20_REG_DEC_SYNC_2DLY_CTRL9_T                  reg_dec_sync_2dly_ctrl9;	//0x0088
	PE_O20_REG_DEC_SYNC_2DLY_CTRLA_T                  reg_dec_sync_2dly_ctrla;	//0x008C
	PE_O20_REG_DEC_SYNC_3DLY_CTRL0_T                  reg_dec_sync_3dly_ctrl0;	//0x0090
	PE_O20_REG_DEC_SYNC_3DLY_CTRL1_T                  reg_dec_sync_3dly_ctrl1;	//0x0094
	PE_O20_REG_DEC_SYNC_3DLY_CTRL2_T                  reg_dec_sync_3dly_ctrl2;	//0x0098
	PE_O20_REG_DEC_SYNC_3DLY_CTRL3_T                  reg_dec_sync_3dly_ctrl3;	//0x009C
	PE_O20_REG_DEC_SYNC_3DLY_CTRL4_T                  reg_dec_sync_3dly_ctrl4;	//0x00A0
	PE_O20_REG_DEC_SYNC_3DLY_CTRL5_T                  reg_dec_sync_3dly_ctrl5;	//0x00A4
	PE_O20_REG_DEC_SYNC_3DLY_CTRL6_T                  reg_dec_sync_3dly_ctrl6;	//0x00A8
	PE_O20_REG_DEC_SYNC_3DLY_CTRL7_T                  reg_dec_sync_3dly_ctrl7;	//0x00AC
	PE_O20_REG_DEC_SYNC_3DLY_CTRL8_T                  reg_dec_sync_3dly_ctrl8;	//0x00B0
	PE_O20_REG_DEC_SYNC_3DLY_CTRL9_T                  reg_dec_sync_3dly_ctrl9;	//0x00B4
	PE_O20_REG_DEC_SYNC_3DLY_CTRLA_T                  reg_dec_sync_3dly_ctrla;	//0x00B8
	PE_O20_REG_LED_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x00BC
	PE_O20_REG_LED_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x00C0
	PE_O20_REG_LED_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x00C4
	PE_O20_REG_LED_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x00C8
	PE_O20_REG_LED_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x00CC
	PE_O20_REG_LED_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x00D0
	PE_O20_REG_LED_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x00D4
	PE_O20_REG_LED_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x00D8
	PE_O20_REG_LED_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x00DC
	PE_O20_REG_LED_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x00E0
	PE_O20_REG_LED_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x00E4
	PE_O20_REG_LED_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x00E8
	PE_O20_REG_LED_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x00EC
	PE_O20_REG_LED_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x00F0
	PE_O20_REG_LED_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x00F4
	PE_O20_REG_LED_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x00F8
	PE_O20_REG_LED_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x00FC
	PE_O20_REG_LED_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x0100
	PE_O20_REG_LED_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x0104
	PE_O20_REG_LED_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0108
	PE_O20_REG_LED_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x010C
	PE_O20_REG_LED_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x0110
	PE_O20_REG_LED_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x0114
	PE_O20_REG_LED_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0118
	PE_O20_REG_LED_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x011C
	PE_O20_REG_LED_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x0120
	PE_O20_REG_LED_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x0124
	PE_O20_REG_LED_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0128
	PE_O20_REG_LED_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x012C
	PE_O20_REG_LED_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x0130
	PE_O20_REG_LED_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x0134
	PE_O20_REG_LED_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0138
	PE_O20_REG_LED_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x013C
	PE_O20_REG_LED_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x0140
	PE_O20_REG_LED_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x0144
	PE_O20_REG_LED_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0148
	PE_O20_REG_LED_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x014C
	PE_O20_REG_LED_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x0150
	PE_O20_REG_LED_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x0154
	PE_O20_REG_LED_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0158
	PE_O20_REG_LED_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x015C
	PE_O20_REG_LED_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x0160
	PE_O20_REG_LED_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x0164
	PE_O20_REG_LED_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x0168
	PE_O20_REG_LED_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x016C
	PE_O20_REG_LED_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x0170
	PE_O20_REG_LED_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x0174
	PE_O20_REG_LED_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x0178
	PE_O20_REG_LED_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x017C
	PE_O20_REG_LED_DECON_CTRL_73_T                        reg_decon_ctrl_73;	//0x0180
	PE_O20_REG_LED_DECON_CTRL_74_T                        reg_decon_ctrl_74;	//0x0184
	PE_O20_REG_LED_DECON_CTRL_75_T                        reg_decon_ctrl_75;	//0x0188
	PE_O20_REG_LED_DECON_CTRL_76_T                        reg_decon_ctrl_76;	//0x018C
	PE_O20_REG_LED_DECON_CTRL_77_T                        reg_decon_ctrl_77;	//0x0190
	PE_O20_REG_LED_DECON_CTRL_78_T                        reg_decon_ctrl_78;	//0x0194
	PE_O20_REG_LED_DECON_CTRL_79_T                        reg_decon_ctrl_79;	//0x0198
	PE_O20_REG_LED_DECON_CTRL_80_T                        reg_decon_ctrl_80;	//0x019C
	PE_O20_REG_LED_DECON_CTRL_81_T                        reg_decon_ctrl_81;	//0x01A0
	PE_O20_REG_LED_DECON_CTRL_82_T                        reg_decon_ctrl_82;	//0x01A4
	PE_O20_REG_LED_DECON_CTRL_83_T                        reg_decon_ctrl_83;	//0x01A8
}PE_LED_DCNT_REG_O20_T;

#endif

