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

#ifndef _PE_DPE_REG_O18A0_H_
#define _PE_DPE_REG_O18A0_H_

/*-----------------------------------------------------------------------------
		0xc8020540L ad_rp_hv_pos ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rp_v_pos                           : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 rp_h_pos                           : 12;  // 27:16     
} PE_LED_O18_AD_RP_HV_POS_T;

/*-----------------------------------------------------------------------------
		0xc8020544L ad_rp_make_en ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mark_en                            : 1 ;  //     0     
} PE_LED_O18_AD_RP_MAKE_EN_T;

/*-----------------------------------------------------------------------------
		0xc8020548L ad_rp_r_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_r                         : 14;  // 13: 0     
} PE_LED_O18_AD_RP_R_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc802054cL ad_rp_g_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_g                         : 14;  // 13: 0     
} PE_LED_O18_AD_RP_G_VALUE_T;

/*-----------------------------------------------------------------------------
		0xc8020550L ad_rp_b_value ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 rd_pixel_b                         : 14;  // 13: 0     
} PE_LED_O18_AD_RP_B_VALUE_T;

/*-----------------------------------------------------------------------------
                             0xc9023800L REG_LED_DECON_TOP_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hei                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_wid                            :12,	// 27:16
	reserved02                         :3 ,	// reserved
	reg_decon_detour_en                :1 ;	// 31
}PE_O18_REG_LED_DECON_TOP_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9023804L REG_LED_DECON_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_use_osd_map         :1 ,	// 0 
	reg_2nd_out_rd_out_clip            :1 ,	// 1 
	reg_1st_out_rd_out_clip            :1 ,	// 2 
	reserved01                         :3 ,	// reserved
	reg_2nd_out_rd_osd_rev             :1 ,	// 6 
	reg_1st_out_rd_osd_rev             :1 ,	// 7 
	reg_11bit_debug_mode_en            :1 ,	// 8 
	reg_out_bit_opt                    :1 ,	// 9 
	reg_tnr_decon_out_bit_sel          :1 ,	// 10
	reg_tnr_decon_in_bit_sel           :1 ,	// 11
	reg_1st_out_rd_max_alpha           :8 ,	// 19:12
	reg_1st_out_rd_min_alpha           :8 ,	// 27:20
	reg_1st_out_rd_bit                 :3 ,	// 30:28
	reg_1st_out_rd_on                  :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9023808L REG_LED_DECON_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_min_pel_cb          :12,	// 11:0
	reg_1st_out_rd_min_pel_yy          :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc902380cL REG_LED_DECON_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_yy          :12,	// 11:0
	reg_1st_out_rd_min_pel_cr          :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9023810L REG_LED_DECON_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_cr          :12,	// 11:0
	reg_1st_out_rd_max_pel_cb          :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9023814L REG_LED_DECON_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9023818L REG_LED_DECON_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc902381cL REG_LED_DECON_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9023820L REG_LED_DECON_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_on           :1 ,	// 0 
	reg_err_out_rd_simple_bit          :3 ,	// 3:1
	reg_2nd_out_rd_bit                 :4 ,	// 7:4
	reserved01                         :3 ,	// reserved
	reg_2nd_out_rd_use_osd_map         :1 ,	// 11
	reg_2nd_out_rd_max_alpha           :8 ,	// 19:12
	reg_2nd_out_rd_min_alpha           :8 ,	// 27:20
	reserved02                         :3 ,	// reserved
	reg_2nd_out_rd_on                  :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9023824L REG_LED_DECON_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_min_pel_cb          :12,	// 11:0
	reg_2nd_out_rd_min_pel_yy          :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_max_lsb_2b          :2 ,	// 29:28
	reg_2nd_out_rd_min_lsb_2b          :2 ;	// 31:30
}PE_O18_REG_LED_DECON_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9023828L REG_LED_DECON_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_yy          :12,	// 11:0
	reg_2nd_out_rd_min_pel_cr          :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc902382cL REG_LED_DECON_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_cr          :12,	// 11:0
	reg_2nd_out_rd_max_pel_cb          :12,	// 23:12
	reserved01                         :7 ,	// reserved
	reg_err_out_rd_simple_clip         :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9023830L REG_LED_DECON_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9023834L REG_LED_DECON_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9023838L REG_LED_DECON_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc902383cL REG_LED_DECON_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9023840L REG_LED_DECON_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9023844L REG_LED_DECON_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9023848L REG_LED_DECON_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_diff_mul_old                   :8 ,	// 7:0
	reg_force_block_v                  :6 ,	// 13:8
	reg_1st_debug_en                   :1 ,	// 14
	reg_l6_var_csc_en                  :1 ,	// 15
	reg_force_block_no_h               :6 ,	// 21:16
	reserved01                         :1 ,	// reserved
	reg_rd_simple_clip                 :1 ,	// 23
	reg_rd_clip                        :1 ,	// 24
	reg_input_csc_en                   :1 ,	// 25
	reg_1st_debug_mode                 :4 ,	// 29:26
	reg_force_block_no_en              :1 ,	// 30
	reg_decon_1st_en                   :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc902384cL REG_LED_DECON_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_var_chroma_en                  :1 ,	// 0 
	reg_diff_sel                       :1 ,	// 1 
	reg_ups_sel                        :1 ,	// 2 
	reserved01                         :12,	// reserved
	reg_old_luma_bit_opt               :1 ,	// 15
	reg_luma_bit_opt                   :1 ,	// 16
	reg_var_bit_opt                    :1 ,	// 17
	reg_l6_var_bit_opt                 :1 ,	// 18
	reg_l6_blur_bit_opt                :1 ,	// 19
	reg_var_v_gain                     :4 ,	// 23:20
	reg_var_h_gain                     :4 ,	// 27:24
	reg_var_cut_resolution             :4 ;	// 31:28
}PE_O18_REG_LED_DECON_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9023850L REG_LED_DECON_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_x_th0               :8 ,	// 7:0
	reg_decon_diff_x_th1               :8 ,	// 15:8
	reg_decon_diff_x_th2               :8 ,	// 23:16
	reg_decon_diff_x_th3               :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9023854L REG_LED_DECON_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_y_th0               :8 ,	// 7:0
	reg_decon_diff_y_th1               :8 ,	// 15:8
	reg_decon_diff_y_th2               :8 ,	// 23:16
	reg_decon_diff_y_th3               :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9023858L REG_LED_DECON_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_x_th2                :10,	// 9:0
	reg_decon_var_x_th1                :10,	// 19:10
	reg_decon_var_x_th0                :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc902385cL REG_LED_DECON_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_y_th1                :10,	// 9:0
	reg_decon_var_y_th0                :10,	// 19:10
	reg_decon_var_x_th3                :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc9023860L REG_LED_DECON_CTRL_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th0               :10,	// 9:0
	reg_decon_var_y_th3                :10,	// 19:10
	reg_decon_var_y_th2                :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9023864L REG_DEC_SYNC_2DLY_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9023868L REG_DEC_SYNC_2DLY_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc902386cL REG_DEC_SYNC_2DLY_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9023870L REG_DEC_SYNC_2DLY_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc9023874L REG_DEC_SYNC_2DLY_CTRL4                             
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
}PE_O18_REG_DEC_SYNC_2DLY_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc9023878L REG_DEC_SYNC_2DLY_CTRL5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc902387cL REG_DEC_SYNC_2DLY_CTRL6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc9023880L REG_DEC_SYNC_2DLY_CTRL7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_7;	// 31:0
}PE_O18_REG_DEC_SYNC_2DLY_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc9023884L REG_DEC_SYNC_2DLY_CTRL8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_8;	// 31:0
}PE_O18_REG_DEC_SYNC_2DLY_CTRL8_T;
/*-----------------------------------------------------------------------------
                             0xc9023888L REG_DEC_SYNC_2DLY_CTRL9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_normal_number                  :16;	// 15:0
}PE_O18_REG_DEC_SYNC_2DLY_CTRL9_T;
/*-----------------------------------------------------------------------------
                             0xc902388cL REG_DEC_SYNC_2DLY_CTRLA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rst_pos_cnt_h                      :16,	// 15:0
	rst_pos_cnt_v                      :16;	// 31:16
}PE_O18_REG_DEC_SYNC_2DLY_CTRLA_T;
/*-----------------------------------------------------------------------------
                             0xc9023890L REG_DEC_SYNC_3DLY_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9023894L REG_DEC_SYNC_3DLY_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9023898L REG_DEC_SYNC_3DLY_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc902389cL REG_DEC_SYNC_3DLY_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc90238a0L REG_DEC_SYNC_3DLY_CTRL4                             
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
}PE_O18_REG_DEC_SYNC_3DLY_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc90238a4L REG_DEC_SYNC_3DLY_CTRL5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc90238a8L REG_DEC_SYNC_3DLY_CTRL6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc90238acL REG_DEC_SYNC_3DLY_CTRL7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_7;	// 31:0
}PE_O18_REG_DEC_SYNC_3DLY_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc90238b0L REG_DEC_SYNC_3DLY_CTRL8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ctrl_sync_actv_dly_8;	// 31:0
}PE_O18_REG_DEC_SYNC_3DLY_CTRL8_T;
/*-----------------------------------------------------------------------------
                             0xc90238b4L REG_DEC_SYNC_3DLY_CTRL9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_normal_number                  :16;	// 15:0
}PE_O18_REG_DEC_SYNC_3DLY_CTRL9_T;
/*-----------------------------------------------------------------------------
                             0xc90238b8L REG_DEC_SYNC_3DLY_CTRLA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rst_pos_cnt_h                      :16,	// 15:0
	rst_pos_cnt_v                      :16;	// 31:16
}PE_O18_REG_DEC_SYNC_3DLY_CTRLA_T;
/*-----------------------------------------------------------------------------
                             0xc90238bcL REG_LED_DECON_CTRL_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th3               :10,	// 9:0
	reg_decon_luma_x_th2               :10,	// 19:10
	reg_decon_luma_x_th1               :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90238c0L REG_LED_DECON_CTRL_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th6               :10,	// 9:0
	reg_decon_luma_x_th5               :10,	// 19:10
	reg_decon_luma_x_th4               :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90238c4L REG_LED_DECON_CTRL_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th1               :10,	// 9:0
	reg_decon_luma_y_th0               :10,	// 19:10
	reg_decon_luma_x_th7               :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90238c8L REG_LED_DECON_CTRL_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th4               :10,	// 9:0
	reg_decon_luma_y_th3               :10,	// 19:10
	reg_decon_luma_y_th2               :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_err_out_rd_simple_clip         :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90238ccL REG_LED_DECON_CTRL_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th7               :10,	// 9:0
	reg_decon_luma_y_th6               :10,	// 19:10
	reg_decon_luma_y_th5               :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90238d0L REG_LED_DECON_CTRL_29                             
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
}PE_O18_REG_LED_DECON_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90238d4L REG_LED_DECON_CTRL_30                             
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
}PE_O18_REG_LED_DECON_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90238d8L REG_LED_DECON_CTRL_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_alpha_blur_l6_var_th1          :10,	// 9:0
	reg_alpha_blur_l6_var_th0          :10;	// 19:10
}PE_O18_REG_LED_DECON_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90238dcL REG_LED_DECON_CTRL_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_x_th2                   :10,	// 9:0
	reg_l6_var_x_th1                   :10,	// 19:10
	reg_l6_var_x_th0                   :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90238e0L REG_LED_DECON_CTRL_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th1                   :10,	// 9:0
	reg_l6_var_y_th0                   :10,	// 19:10
	reg_l6_var_x_th3                   :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90238e4L REG_LED_DECON_CTRL_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th3                   :10,	// 9:0
	reg_l6_var_y_th2                   :10,	// 19:10
	reserved01                         :8 ,	// reserved
	reg_decon_rd_simple_bit            :3 ,	// 30:28
	reg_decon_rd_simple_on             :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90238e8L REG_LED_DECON_CTRL_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc90238ecL REG_LED_DECON_CTRL_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc90238f0L REG_LED_DECON_CTRL_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc90238f4L REG_LED_DECON_CTRL_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_min_pel_cb                  :12,	// 11:0
	reg_rd_min_pel_yy                  :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_rd_bit                         :3 ,	// 30:28
	reg_decon_rd_on                    :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc90238f8L REG_LED_DECON_CTRL_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_yy                  :12,	// 11:0
	reg_rd_min_pel_cr                  :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc90238fcL REG_LED_DECON_CTRL_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_cr                  :12,	// 11:0
	reg_rd_max_pel_cb                  :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc9023900L REG_LED_DECON_CTRL_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc9023904L REG_LED_DECON_CTRL_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc9023908L REG_LED_DECON_CTRL_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc902390cL REG_LED_DECON_CTRL_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_dist_h             :4 ,	// 3:0
	reg_l6_var_diff_dist_w             :4 ,	// 7:4
	reg_l6_var_max_cut_value           :12,	// 19:8
	reg_l6_var_max_th                  :12;	// 31:20
}PE_O18_REG_LED_DECON_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc9023910L REG_LED_DECON_CTRL_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_cr              :10,	// 9:0
	reg_l6_var_diff_th_cb              :10,	// 19:10
	reg_l6_var_diff_th_yy              :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc9023914L REG_LED_DECON_CTRL_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_yy3             :10,	// 9:0
	reg_l6_var_diff_th_yy2             :10;	// 19:10
}PE_O18_REG_LED_DECON_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc9023918L REG_LED_DECON_CTRL_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_t_min_yy3          :10,	// 9:0
	reg_l6_var_diff_t_min_yy2          :10,	// 19:10
	reg_l6_var_diff_t_min_yy           :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc902391cL REG_LED_DECON_CTRL_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_cc3         :10,	// 9:0
	reg_l6_var_diff_th_min_cc2         :10,	// 19:10
	reg_l6_var_diff_th_min_cc          :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_l6_var_reshape_en              :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc9023920L REG_LED_DECON_CTRL_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_yy_cond_cb_adj_ratio  :8 ,	// 7:0
	reg_l6_var_v_yy_cond_yy_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_diff_yy_cond_ratio    :8 ,	// 23:16
	reg_l6_var_v_diff_yy_cond_ratio    :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc9023924L REG_LED_DECON_CTRL_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_yy_cond_cr_adj_ratio  :8 ,	// 7:0
	reg_l6_var_h_yy_cond_cb_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_yy_cond_yy_adj_ratio  :8 ,	// 23:16
	reg_l6_var_v_yy_cond_cr_adj_ratio  :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc9023928L REG_LED_DECON_CTRL_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_l6_var_cc_cond_cr_adj_ratio    :8 ,	// 15:8
	reg_l6_var_cc_cond_cb_adj_ratio    :8 ,	// 23:16
	reg_l6_var_cc_cond_yy_adj_ratio    :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc902392cL REG_LED_DECON_CTRL_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_diff_cut_value        :12,	// 11:0
	reg_l6_var_v_diff_th               :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc9023930L REG_LED_DECON_CTRL_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_diff_cut_value        :12,	// 11:0
	reg_l6_var_h_diff_th               :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc9023934L REG_LED_DECON_CTRL_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_max_rep_value:12,	// 11:0
	reg_l6_var_total_diff_max_th       :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc9023938L REG_LED_DECON_CTRL_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_low_rep_value:12,	// 11:0
	reg_l6_var_total_diff_low_th       :12,	// 23:12
	reserved01                         :2 ,	// reserved
	reg_l6_var_mopology_3rd_sel        :2 ,	// 27:26
	reg_l6_var_mopology_2nd_sel        :2 ,	// 29:28
	reg_l6_var_mopology_1st_sel        :2 ;	// 31:30
}PE_O18_REG_LED_DECON_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc902393cL REG_LED_DECON_CTRL_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_mopology_2nd_cut_th     :12,	// 11:0
	reg_l6_var_mopology_1st_cut_th     :12;	// 23:12
}PE_O18_REG_LED_DECON_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc9023940L REG_LED_DECON_CTRL_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_mopology_3rd_cut_th     :12;	// 11:0
}PE_O18_REG_LED_DECON_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc9023944L REG_LED_DECON_CTRL_58                             
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
}PE_O18_REG_LED_DECON_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc9023948L REG_LED_DECON_CTRL_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th2                 :10,	// 9:0
	reg_2nd_luma_x_th1                 :10,	// 19:10
	reg_2nd_luma_x_th0                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_444_mode                       :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc902394cL REG_LED_DECON_CTRL_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th5                 :10,	// 9:0
	reg_2nd_luma_x_th4                 :10,	// 19:10
	reg_2nd_luma_x_th3                 :10,	// 29:20
	reg_2nd_luma_bit_opt               :2 ;	// 31:30
}PE_O18_REG_LED_DECON_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc9023950L REG_LED_DECON_CTRL_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th0                 :10,	// 9:0
	reg_2nd_luma_x_th7                 :10,	// 19:10
	reg_2nd_luma_x_th6                 :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc9023954L REG_LED_DECON_CTRL_62                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th3                 :10,	// 9:0
	reg_2nd_luma_y_th2                 :10,	// 19:10
	reg_2nd_luma_y_th1                 :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_62_T;
/*-----------------------------------------------------------------------------
                             0xc9023958L REG_LED_DECON_CTRL_63                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th6                 :10,	// 9:0
	reg_2nd_luma_y_th5                 :10,	// 19:10
	reg_2nd_luma_y_th4                 :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_63_T;
/*-----------------------------------------------------------------------------
                             0xc902395cL REG_LED_DECON_CTRL_64                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_x_th1                  :10,	// 9:0
	reg_2nd_var_x_th0                  :10,	// 19:10
	reg_2nd_luma_y_th7                 :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_64_T;
/*-----------------------------------------------------------------------------
                             0xc9023960L REG_LED_DECON_CTRL_65                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th0                  :10,	// 9:0
	reg_2nd_var_x_th3                  :10,	// 19:10
	reg_2nd_var_x_th2                  :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_65_T;
/*-----------------------------------------------------------------------------
                             0xc9023964L REG_LED_DECON_CTRL_66                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th3                  :10,	// 9:0
	reg_2nd_var_y_th2                  :10,	// 19:10
	reg_2nd_var_y_th1                  :10;	// 29:20
}PE_O18_REG_LED_DECON_CTRL_66_T;
/*-----------------------------------------------------------------------------
                             0xc9023968L REG_LED_DECON_CTRL_67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_x_th0                 :8 ,	// 7:0
	reg_2nd_diff_x_th1                 :8 ,	// 15:8
	reg_2nd_diff_x_th2                 :8 ,	// 23:16
	reg_2nd_diff_x_th3                 :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_67_T;
/*-----------------------------------------------------------------------------
                             0xc902396cL REG_LED_DECON_CTRL_68                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_y_th0                 :8 ,	// 7:0
	reg_2nd_diff_y_th1                 :8 ,	// 15:8
	reg_2nd_diff_y_th2                 :8 ,	// 23:16
	reg_2nd_diff_y_th3                 :8 ;	// 31:24
}PE_O18_REG_LED_DECON_CTRL_68_T;
/*-----------------------------------------------------------------------------
                             0xc9023970L REG_LED_DECON_CTRL_69                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_yy;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_69_T;
/*-----------------------------------------------------------------------------
                             0xc9023974L REG_LED_DECON_CTRL_70                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cb;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_70_T;
/*-----------------------------------------------------------------------------
                             0xc9023978L REG_LED_DECON_CTRL_71                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cr;	// 31:0
}PE_O18_REG_LED_DECON_CTRL_71_T;
/*-----------------------------------------------------------------------------
                             0xc902397cL REG_LED_DECON_CTRL_72                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_diff_ker_dl                :5 ,	// 4:0
	reg_err_diff_ker_ur                :5 ,	// 9:5
	reg_err_diff_ker_um                :5 ,	// 14:10
	reg_err_diff_ker_ul                :5 ,	// 19:15
	reserved01                         :10,	// reserved
	reg_err_out_clip                   :1 ,	// 30
	reg_err_diff_en                    :1 ;	// 31
}PE_O18_REG_LED_DECON_CTRL_72_T;

typedef struct {
	PE_LED_O18_AD_RP_HV_POS_T            	ad_rp_hv_pos;                 //0xc8020540L
	PE_LED_O18_AD_RP_MAKE_EN_T           	ad_rp_make_en;                //0xc8020544L
	PE_LED_O18_AD_RP_R_VALUE_T           	ad_rp_r_value;                //0xc8020548L
	PE_LED_O18_AD_RP_G_VALUE_T           	ad_rp_g_value;                //0xc802054cL
	PE_LED_O18_AD_RP_B_VALUE_T           	ad_rp_b_value;                //0xc8020550L
}PE_LED_RP_REG_O18_T;
typedef struct
{ 
	PE_O18_REG_LED_DECON_TOP_CTRL_T                       reg_decon_top_ctrl;	//0x0000
	PE_O18_REG_LED_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0004
	PE_O18_REG_LED_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0008
	PE_O18_REG_LED_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x000C
	PE_O18_REG_LED_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0010
	PE_O18_REG_LED_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0014
	PE_O18_REG_LED_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0018
	PE_O18_REG_LED_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x001C
	PE_O18_REG_LED_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0020
	PE_O18_REG_LED_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0024
	PE_O18_REG_LED_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0028
	PE_O18_REG_LED_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x002C
	PE_O18_REG_LED_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x0030
	PE_O18_REG_LED_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x0034
	PE_O18_REG_LED_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x0038
	PE_O18_REG_LED_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x003C
	PE_O18_REG_LED_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x0040
	PE_O18_REG_LED_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x0044
	PE_O18_REG_LED_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x0048
	PE_O18_REG_LED_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x004C
	PE_O18_REG_LED_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x0050
	PE_O18_REG_LED_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x0054
	PE_O18_REG_LED_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x0058
	PE_O18_REG_LED_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x005C
	PE_O18_REG_LED_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x0060
	PE_O18_REG_DEC_SYNC_2DLY_CTRL0_T                  reg_dec_sync_2dly_ctrl0;	//0x0064
	PE_O18_REG_DEC_SYNC_2DLY_CTRL1_T                  reg_dec_sync_2dly_ctrl1;	//0x0068
	PE_O18_REG_DEC_SYNC_2DLY_CTRL2_T                  reg_dec_sync_2dly_ctrl2;	//0x006C
	PE_O18_REG_DEC_SYNC_2DLY_CTRL3_T                  reg_dec_sync_2dly_ctrl3;	//0x0070
	PE_O18_REG_DEC_SYNC_2DLY_CTRL4_T                  reg_dec_sync_2dly_ctrl4;	//0x0074
	PE_O18_REG_DEC_SYNC_2DLY_CTRL5_T                  reg_dec_sync_2dly_ctrl5;	//0x0078
	PE_O18_REG_DEC_SYNC_2DLY_CTRL6_T                  reg_dec_sync_2dly_ctrl6;	//0x007C
	PE_O18_REG_DEC_SYNC_2DLY_CTRL7_T                  reg_dec_sync_2dly_ctrl7;	//0x0080
	PE_O18_REG_DEC_SYNC_2DLY_CTRL8_T                  reg_dec_sync_2dly_ctrl8;	//0x0084
	PE_O18_REG_DEC_SYNC_2DLY_CTRL9_T                  reg_dec_sync_2dly_ctrl9;	//0x0088
	PE_O18_REG_DEC_SYNC_2DLY_CTRLA_T                  reg_dec_sync_2dly_ctrla;	//0x008C
	PE_O18_REG_DEC_SYNC_3DLY_CTRL0_T                  reg_dec_sync_3dly_ctrl0;	//0x0090
	PE_O18_REG_DEC_SYNC_3DLY_CTRL1_T                  reg_dec_sync_3dly_ctrl1;	//0x0094
	PE_O18_REG_DEC_SYNC_3DLY_CTRL2_T                  reg_dec_sync_3dly_ctrl2;	//0x0098
	PE_O18_REG_DEC_SYNC_3DLY_CTRL3_T                  reg_dec_sync_3dly_ctrl3;	//0x009C
	PE_O18_REG_DEC_SYNC_3DLY_CTRL4_T                  reg_dec_sync_3dly_ctrl4;	//0x00A0
	PE_O18_REG_DEC_SYNC_3DLY_CTRL5_T                  reg_dec_sync_3dly_ctrl5;	//0x00A4
	PE_O18_REG_DEC_SYNC_3DLY_CTRL6_T                  reg_dec_sync_3dly_ctrl6;	//0x00A8
	PE_O18_REG_DEC_SYNC_3DLY_CTRL7_T                  reg_dec_sync_3dly_ctrl7;	//0x00AC
	PE_O18_REG_DEC_SYNC_3DLY_CTRL8_T                  reg_dec_sync_3dly_ctrl8;	//0x00B0
	PE_O18_REG_DEC_SYNC_3DLY_CTRL9_T                  reg_dec_sync_3dly_ctrl9;	//0x00B4
	PE_O18_REG_DEC_SYNC_3DLY_CTRLA_T                  reg_dec_sync_3dly_ctrla;	//0x00B8
	PE_O18_REG_LED_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x00BC
	PE_O18_REG_LED_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x00C0
	PE_O18_REG_LED_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x00C4
	PE_O18_REG_LED_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x00C8
	PE_O18_REG_LED_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x00CC
	PE_O18_REG_LED_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x00D0
	PE_O18_REG_LED_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x00D4
	PE_O18_REG_LED_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x00D8
	PE_O18_REG_LED_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x00DC
	PE_O18_REG_LED_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x00E0
	PE_O18_REG_LED_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x00E4
	PE_O18_REG_LED_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x00E8
	PE_O18_REG_LED_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x00EC
	PE_O18_REG_LED_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x00F0
	PE_O18_REG_LED_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x00F4
	PE_O18_REG_LED_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x00F8
	PE_O18_REG_LED_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x00FC
	PE_O18_REG_LED_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x0100
	PE_O18_REG_LED_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x0104
	PE_O18_REG_LED_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0108
	PE_O18_REG_LED_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x010C
	PE_O18_REG_LED_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x0110
	PE_O18_REG_LED_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x0114
	PE_O18_REG_LED_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0118
	PE_O18_REG_LED_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x011C
	PE_O18_REG_LED_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x0120
	PE_O18_REG_LED_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x0124
	PE_O18_REG_LED_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0128
	PE_O18_REG_LED_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x012C
	PE_O18_REG_LED_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x0130
	PE_O18_REG_LED_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x0134
	PE_O18_REG_LED_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0138
	PE_O18_REG_LED_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x013C
	PE_O18_REG_LED_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x0140
	PE_O18_REG_LED_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x0144
	PE_O18_REG_LED_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0148
	PE_O18_REG_LED_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x014C
	PE_O18_REG_LED_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x0150
	PE_O18_REG_LED_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x0154
	PE_O18_REG_LED_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0158
	PE_O18_REG_LED_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x015C
	PE_O18_REG_LED_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x0160
	PE_O18_REG_LED_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x0164
	PE_O18_REG_LED_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x0168
	PE_O18_REG_LED_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x016C
	PE_O18_REG_LED_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x0170
	PE_O18_REG_LED_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x0174
	PE_O18_REG_LED_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x0178
	PE_O18_REG_LED_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x017C
}PE_LED_DCNT_REG_O18_T;

#endif

