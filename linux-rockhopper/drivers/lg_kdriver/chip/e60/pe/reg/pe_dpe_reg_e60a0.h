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

#ifndef _PE_DPE_REG_E60A0_H_
#define _PE_DPE_REG_E60A0_H_

typedef union {
	UINT32 udata32;
	struct {						//0xC9036940 RW
	UINT32 rp_v_pos                         :13;	//12:0	//vertical pixel position
	UINT32 resvd0                           :3;
	UINT32 rp_h_pos                         :13;	//28:16	//horizontal pixel position
	UINT32 resvd1                           :3;
	};
}PE_LED_E60_AD_RP_HV_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9036944 RW
	UINT32 mark_en                          :1;	//0 //mark enable for read a pixel
	UINT32 resvd                            :31;
	};
}PE_LED_E60_AD_RP_MAKE_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9036948 RO
	UINT32 rd_pixel_r                       :14;	//13:0	//R value for a pixel
	UINT32 resvd                            :18;
	};
}PE_LED_E60_AD_RP_R_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903694C RO
	UINT32 rd_pixel_g                       :14;	//13:0	//G value for a pixel
	UINT32 resvd                            :18;
	};
}PE_LED_E60_AD_RP_G_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9036950 RO
	UINT32 rd_pixel_b                       :14;	//13:0	//B value for a pixel
	UINT32 resvd                            :18;
	};
}PE_LED_E60_AD_RP_B_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD00 RW
	UINT32 reg_hei                          :13;	//12:0	//1B0 : 432	10E0 : 4320
	UINT32 reh_mode_2ch                     :1;	//13 //
	UINT32 dither_temporal_en               :1;	//14 //
	UINT32 dither_en                        :1;	//15 //input dither enable for 11b -> 10b	processing order: (input dither: dither_en) --> (11b -> 10b : reg_decon_in_bit_opt)
	UINT32 reg_wid                          :13;	//28:16	//split_width = W + 2*GB	3904 = 3840 + 2*32
	UINT32 reg_decon_out_bit_opt            :1;	//29 //1: [10:0] , 0: {1'b0, [10:1]}
	UINT32 reg_decon_in_bit_opt             :1;	//30 //11b -> 10b ( 1: [10:1] , 0: [9:0] )	should be 1 when dither_en = 1
	UINT32 reg_decon_detour_en              :1;	//31 //1: detour
	};
}PE_E60_REG_LED_DECON_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD04 RW
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//0 //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//1 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.	(F20 delete)
	UINT32 reg_1st_out_rd_out_clip          :1;	//2 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.	(F20 delete)
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//7 //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//8 //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//9 //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//10 //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//11 //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_1st_out_rd_min_alpha         :8;	//27:20	//
	UINT32 reg_1st_out_rd_bit               :3;	//30:28	//
	UINT32 reg_1st_out_rd_on                :1;	//31 //default = '0', RD off
	};
}PE_E60_REG_LED_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD08 RW
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD0C RW
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD10 RW
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD14 RW
	UINT32 reg_1st_out_rd_init_yy           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD18 RW
	UINT32 reg_1st_out_rd_init_cb           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD1C RW
	UINT32 reg_1st_out_rd_init_cr           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD20 RW
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//7:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//11 //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//27:20	//
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//31 //default = '0', RD off
	};
}PE_E60_REG_LED_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD24 RW
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//29:28	//
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//31:30	//
	};
}PE_E60_REG_LED_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD28 RW
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD2C RW
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD30 RW
	UINT32 reg_2nd_out_rd_init_yy           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD34 RW
	UINT32 reg_2nd_out_rd_init_cb           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD38 RW
	UINT32 reg_2nd_out_rd_init_cr           :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD3C RW
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//31:0	//Not used in F20
	};
}PE_E60_REG_LED_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD40 RW
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//31:0	//Not used in F20
	};
}PE_E60_REG_LED_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD44 RW
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//31:0	//Not used in F20
	};
}PE_E60_REG_LED_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD48 RW
	UINT32 reg_blur_lb_var_cut_res          :4;	//3:0	//>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//6 //
	UINT32 reg_l6_var_2x2_bit               :1;	//7 //1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//13:8	//Not used in F20
	UINT32 reg_1st_debug_en                 :1;	//14 //
	UINT32 reg_l6_var_csc_en                :1;	//15 //(Not used in F20, gate 문제로 제거)ND에선 사용 안 함
	UINT32 reg_force_block_no_h             :6;	//21:16	//Not used in F20
	UINT32 reg_4k_5x3_mode_en               :1;	//22 //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//23 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//24 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//25 //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//29:26	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: input_blur
	UINT32 reg_force_block_no_en            :1;	//30 //Not used in F20
	UINT32 reg_decon_1st_en                 :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD4C RW
	UINT32 reg_var_chroma_en                :1;	//0 //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//2 //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//4 //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//6:5	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//8:7	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//11:9	//0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//12 //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//13 //not used in O20 -> 신호 자체는 연결되어있음(F20)
	UINT32 reg_led_10b_mode_diff_pel        :1;	//14 //not used in O20
	UINT32 reg_l6_var_debug_en              :1;	//15 //reg_lb_var_en = 1 일때 동작
	UINT32 reg_luma_bit_opt                 :1;	//16 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//17 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//18 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//19 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//23:20	//
	UINT32 reg_var_h_gain                   :4;	//27:24	//
	UINT32 reg_var_cut_resolution           :4;	//31:28	//
	};
}PE_E60_REG_LED_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD50 RW
	UINT32 reg_decon_diff_x_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_x_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_x_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_x_th3             :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD54 RW
	UINT32 reg_decon_diff_y_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_y_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_y_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_y_th3             :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD58 RW
	UINT32 reg_decon_var_x_th2              :10;	//9:0	//
	UINT32 reg_decon_var_x_th1              :10;	//19:10	//
	UINT32 reg_decon_var_x_th0              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD5C RW
	UINT32 reg_decon_var_y_th1              :10;	//9:0	//
	UINT32 reg_decon_var_y_th0              :10;	//19:10	//
	UINT32 reg_decon_var_x_th3              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD60 RW
	UINT32 reg_decon_luma_x_th0             :10;	//9:0	//
	UINT32 reg_decon_var_y_th3              :10;	//19:10	//
	UINT32 reg_decon_var_y_th2              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD64 RW
	UINT32 vsync                            :16;	//15:0	//
	UINT32 vfp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD68 RW
	UINT32 va                               :16;	//15:0	//
	UINT32 vbp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD6C RW
	UINT32 hsync                            :16;	//15:0	//
	UINT32 hfp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD70 RW
	UINT32 ha                               :16;	//15:0	//
	UINT32 hbp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD74 RW
	UINT32 line_start_pos                   :16;	//15:0	//
	UINT32 sync_i_h_sel                     :1;	//16 //
	UINT32 sync_i_v_sel                     :1;	//17 //
	UINT32 sync_i_inv_ha                    :1;	//18 //
	UINT32 sync_i_inv_va                    :1;	//19 //
	UINT32 sync_o_sel_ha                    :1;	//20 //
	UINT32 sync_o_sel_va                    :1;	//21 //
	UINT32 sync_o_sel_hs                    :1;	//22 //
	UINT32 sync_o_sel_vs                    :1;	//23 //
	UINT32 tp_update_hv_zero                :1;	//24 //
	UINT32 force_out_ha                     :1;	//25 //
	UINT32 force_out_va                     :1;	//26 //
	UINT32 force_out_hs                     :1;	//27 //
	UINT32 manual_cnt_h_value_en            :1;	//28 //
	UINT32 manual_cnt_v_value_en            :1;	//29 //
	UINT32 force_out_vs                     :1;	//30 //
	UINT32 update_force                     :1;	//31 //
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD78 RW
	UINT32 sync_h_dly                       :16;	//15:0	//
	UINT32 sync_v_dly                       :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD7C RW
	UINT32 manual_cnt_h_value               :16;	//15:0	//
	UINT32 manual_cnt_v_value               :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD80 RW
	UINT32 reg_ctrl_sync_actv_dly_7         :32;	//31:0	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD84 RW
	UINT32 reg_ctrl_sync_actv_dly_8         :32;	//31:0	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD88 RW
	UINT32 reg_normal_number                :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD8C RW
	UINT32 rst_pos_cnt_h                    :16;	//15:0	//
	UINT32 rst_pos_cnt_v                    :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_2DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD90 RW
	UINT32 vsync                            :16;	//15:0	//
	UINT32 vfp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD94 RW
	UINT32 va                               :16;	//15:0	//
	UINT32 vbp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD98 RW
	UINT32 hsync                            :16;	//15:0	//
	UINT32 hfp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AD9C RW
	UINT32 ha                               :16;	//15:0	//
	UINT32 hbp                              :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADA0 RW
	UINT32 line_start_pos                   :16;	//15:0	//
	UINT32 sync_i_h_sel                     :1;	//16 //
	UINT32 sync_i_v_sel                     :1;	//17 //
	UINT32 sync_i_inv_ha                    :1;	//18 //
	UINT32 sync_i_inv_va                    :1;	//19 //
	UINT32 sync_o_sel_ha                    :1;	//20 //
	UINT32 sync_o_sel_va                    :1;	//21 //
	UINT32 sync_o_sel_hs                    :1;	//22 //
	UINT32 sync_o_sel_vs                    :1;	//23 //
	UINT32 tp_update_hv_zero                :1;	//24 //
	UINT32 force_out_ha                     :1;	//25 //
	UINT32 force_out_va                     :1;	//26 //
	UINT32 force_out_hs                     :1;	//27 //
	UINT32 manual_cnt_h_value_en            :1;	//28 //
	UINT32 manual_cnt_v_value_en            :1;	//29 //
	UINT32 force_out_vs                     :1;	//30 //
	UINT32 update_force                     :1;	//31 //
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADA4 RW
	UINT32 sync_h_dly                       :16;	//15:0	//
	UINT32 sync_v_dly                       :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADA8 RW
	UINT32 manual_cnt_h_value               :16;	//15:0	//
	UINT32 manual_cnt_v_value               :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADAC RW
	UINT32 reg_ctrl_sync_actv_dly_7         :32;	//31:0	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADB0 RW
	UINT32 reg_ctrl_sync_actv_dly_8         :32;	//31:0	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADB4 RW
	UINT32 reg_normal_number                :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADB8 RW
	UINT32 rst_pos_cnt_h                    :16;	//15:0	//
	UINT32 rst_pos_cnt_v                    :16;	//31:16	//
	};
}PE_E60_REG_LED_DEC_SYNC_3DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADBC RW
	UINT32 reg_decon_luma_x_th3             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th2             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th1             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADC0 RW
	UINT32 reg_decon_luma_x_th6             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th5             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th4             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADC4 RW
	UINT32 reg_decon_luma_y_th1             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th0             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th7             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADC8 RW
	UINT32 reg_decon_luma_y_th4             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th3             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th2             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADCC RW
	UINT32 reg_decon_luma_y_th7             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th6             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th5             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADD0 RW
	UINT32 reg_block_size_v                 :8;	//7:0	//
	UINT32 reg_block_size_h                 :8;	//15:8	//
	UINT32 reg_block_no_v                   :6;	//21:16	//
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//29:24	//
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADD4 RW
	UINT32 reg_last_block_size_v            :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//19:16	//
	UINT32 reg_diff_shift                   :3;	//22:20	//
	UINT32 reg_osd_run_mode                 :1;	//23 //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//24 //Not used in F20
	UINT32 reg_alpha_blur_mode              :2;	//26:25	//0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//28:27	//Not used in F20
	UINT32 reg_diff_use_seldiff             :1;	//29 //
	UINT32 reg_diff_calc_mode               :2;	//31:30	//
	};
}PE_E60_REG_LED_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADD8 RW
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//9:0	//Not used in F20
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//19:10	//Not used in F20
	UINT32 reg_lb_var_cut_res               :4;	//23:20	//
	UINT32 reg_master_gain                  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADDC RW
	UINT32 reg_l6_var_x_th2                 :10;	//9:0	//
	UINT32 reg_l6_var_x_th1                 :10;	//19:10	//
	UINT32 reg_l6_var_x_th0                 :10;	//29:20	//
	UINT32 reg_lb_var_opt                   :1;	//30 //
	UINT32 reg_lb_var_en                    :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADE0 RW
	UINT32 reg_l6_var_y_th1                 :10;	//9:0	//
	UINT32 reg_l6_var_y_th0                 :10;	//19:10	//
	UINT32 reg_l6_var_x_th3                 :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADE4 RW
	UINT32 reg_l6_var_y_th3                 :10;	//9:0	//
	UINT32 reg_l6_var_y_th2                 :10;	//19:10	//
	UINT32 reg_l6_pel_trunc                 :2;	//21:20	//
	UINT32 reg_var_v_cut                    :2;	//23:22	//
	UINT32 reg_var_h_cut                    :2;	//25:24	//
	UINT32 reg_var_t7_offset                :2;	//27:26	//
	UINT32 reg_decon_rd_simple_bit          :3;	//30:28	//
	UINT32 reg_decon_rd_simple_on           :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADE8 RW
	UINT32 reg_decon_rd_simple_init_yy      :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADEC RW
	UINT32 reg_decon_rd_simple_init_cb      :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADF0 RW
	UINT32 reg_decon_rd_simple_init_cr      :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADF4 RW
	UINT32 reg_rd_min_pel_cb                :12;	//11:0	//
	UINT32 reg_rd_min_pel_yy                :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//30:28	//
	UINT32 reg_decon_rd_on                  :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADF8 RW
	UINT32 reg_rd_max_pel_yy                :12;	//11:0	//
	UINT32 reg_rd_min_pel_cr                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903ADFC RW
	UINT32 reg_rd_max_pel_cr                :12;	//11:0	//
	UINT32 reg_rd_max_pel_cb                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE00 RW
	UINT32 reg_rd_init_yy                   :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE04 RW
	UINT32 reg_rd_init_cb                   :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE08 RW
	UINT32 reg_rd_init_cr                   :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE0C RW
	UINT32 reg_motion_gain_x3               :8;	//7:0	//
	UINT32 reg_motion_gain_x2               :8;	//15:8	//
	UINT32 reg_motion_gain_x1               :8;	//23:16	//
	UINT32 reg_motion_gain_x0               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE10 RW
	UINT32 reg_motion_gain_y3               :8;	//7:0	//
	UINT32 reg_motion_gain_y2               :8;	//15:8	//
	UINT32 reg_motion_gain_y1               :8;	//23:16	//
	UINT32 reg_motion_gain_y0               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE14 RW
	UINT32 reg_bbd_y0                       :12;	//11:0	//Operated on O20(4K)
	UINT32 reg_bbd_x0                       :12;	//23:12	//Operated on O20(4K)
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//28 //
	UINT32 reg_blur2_sim_en                 :1;	//29 //
	UINT32 reg_amf_lut_bit                  :1;	//30 //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE18 RW
	UINT32 reg_bbd_y1                       :12;	//11:0	//Operated on O20(4K)
	UINT32 reg_bbd_x1                       :12;	//23:12	//Operated on O20(4K)
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//28:26	//
	UINT32 reg_blur2_sim_ratio              :3;	//31:29	//
	};
}PE_E60_REG_LED_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE1C RW
	UINT32 reg_lut_blur_sim_x3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_x2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_x1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_x0              :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE20 RW
	UINT32 reg_lut_blur_sim_y3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_y2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_y1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_y0              :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE24 RW
	UINT32 reg_lut_skin_yy_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_yy_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_yy_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_yy_x0               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE28 RW
	UINT32 reg_lut_skin_cb_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cb_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cb_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cb_x0               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE2C RW
	UINT32 reg_lut_skin_cr_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cr_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cr_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cr_x0               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE30 RW
	UINT32 reg_lut_skin_y3                  :8;	//7:0	//
	UINT32 reg_lut_skin_y2                  :8;	//15:8	//
	UINT32 reg_lut_skin_y1                  :8;	//23:16	//
	UINT32 reg_lut_skin_y0                  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE34 RW
	UINT32 reg_lut_face_x3                  :8;	//7:0	//
	UINT32 reg_lut_face_x2                  :8;	//15:8	//
	UINT32 reg_lut_face_x1                  :8;	//23:16	//
	UINT32 reg_lut_face_x0                  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE38 RW
	UINT32 reg_lut_face_y3                  :8;	//7:0	//
	UINT32 reg_lut_face_y2                  :8;	//15:8	//
	UINT32 reg_lut_face_y1                  :8;	//23:16	//
	UINT32 reg_lut_face_y0                  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE3C RW
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//19 //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//27:20	//
	UINT32 reg_face_shft                    :2;	//29:28	//0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//30 //
	UINT32 reg_skin_en                      :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE40 RW
	UINT32 reg_l6_var_diff_dist_h           :4;	//3:0	//
	UINT32 reg_l6_var_diff_dist_w           :4;	//7:4	//
	UINT32 resvd                            :24;
	};
}PE_E60_REG_LED_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE44 RW
	UINT32 reg_l6_var_diff_th_cr            :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_cb            :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_yy            :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE48 RW
	UINT32 reg_l6_var_diff_th_yy3           :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_yy2           :10;	//19:10	//
	UINT32 resvd                            :12;
	};
}PE_E60_REG_LED_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE4C RW
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE50 RW
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE54 RW
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE58 RW
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//23:16	//
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE5C RW
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//15:8	//
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE60 RW
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_v_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE64 RW
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_h_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE68 RW
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_max_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE6C RW
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_low_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_LED_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE70 RW
	UINT32 reg_diff_mul                     :4;	//3:0	//
	UINT32 reg_2nd_diff_shift               :3;	//6:4	//Not used in F20
	UINT32 reg_2nd_alpha_blur_mode          :1;	//7 //0: no blur, 1: 5x1 blur
	UINT32 reg_2nd_debug_mode               :3;	//10:8	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: blur result	6: osd_flag	7: bypass
	UINT32 reg_odd_sel                      :1;	//11 //
	UINT32 reg_2nd_osd_run_mode             :1;	//12 //
	UINT32 reg_2nd_rd_simple_bit            :3;	//15:13	//
	UINT32 reg_2nd_rd_simple_on             :1;	//16 //
	UINT32 reg_input_csc_en                 :1;	//17 //
	UINT32 reg_2nd_var_v_gain               :2;	//19:18	//
	UINT32 reg_2nd_var_h_gain               :2;	//21:20	//
	UINT32 reg_2nd_var_cut_resolution       :3;	//24:22	//
	UINT32 reg_2nd_var_chroma_en            :1;	//25 //
	UINT32 reg_2nd_var_sel_tmp              :2;	//27:26	//0: 3x3, 1: 9x3, 2: 17x3, 3: 18x3
	UINT32 reg_2nd_fil_sel_tmp              :2;	//29:28	//0: 3x3, 1: 9x3, 2: 17x3
	UINT32 reg_2nd_debug_en                 :1;	//30 //
	UINT32 reg_decon_2nd_en                 :1;	//31 //
	};
}PE_E60_REG_LED_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE74 RW
	UINT32 reg_2nd_luma_x_th2               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th1               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th0               :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_444_mode                     :1;	//31 //0: repeat, 1: avg
	};
}PE_E60_REG_LED_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE78 RW
	UINT32 reg_2nd_luma_x_th5               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th4               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th3               :10;	//29:20	//
	UINT32 reg_2nd_luma_bit_opt             :2;	//31:30	//0: lower 10bit w/ clipping, 1: mid 10bit w/ clipping, 2: higher 10bit
	};
}PE_E60_REG_LED_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE7C RW
	UINT32 reg_2nd_luma_y_th0               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th7               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th6               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE80 RW
	UINT32 reg_2nd_luma_y_th3               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th2               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th1               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE84 RW
	UINT32 reg_2nd_luma_y_th6               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th5               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th4               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE88 RW
	UINT32 reg_2nd_var_x_th1                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th0                :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th7               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE8C RW
	UINT32 reg_2nd_var_y_th0                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th3                :10;	//19:10	//
	UINT32 reg_2nd_var_x_th2                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE90 RW
	UINT32 reg_2nd_var_y_th3                :10;	//9:0	//
	UINT32 reg_2nd_var_y_th2                :10;	//19:10	//
	UINT32 reg_2nd_var_y_th1                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_LED_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE94 RW
	UINT32 reg_2nd_diff_x_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_x_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_x_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_x_th3               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE98 RW
	UINT32 reg_2nd_diff_y_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_y_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_y_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_y_th3               :8;	//31:24	//
	};
}PE_E60_REG_LED_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AE9C RW
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEA0 RW
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEA4 RW
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//31:0	//
	};
}PE_E60_REG_LED_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEA8 RW
	UINT32 reg_overlap_hsize                :8;	//7:0	//* final release로 인해 RTL에서는 "reg_overlap"으로 사용중(다음버전에 명칭 업데이트 예정)	가용범위 : 4~128 (0~3 사이의 값 입력시 오류 발생)
	UINT32 reg_trans_pos                    :6;	//13:8	//h_block 개수보다 작아야 함
	UINT32 resvd0                           :10;
	UINT32 reg_original_size_set            :1;	//24 //block_info에서 ND의 split 이전의 오리지널 입력 영상에 대한 세팅(E60에서 8K 4split/4K 2split은 코어 입력이 동일하기 때문에 별도의 구분 필요)	0: 8K	1: 4K
	UINT32 resvd1                           :3;
	UINT32 reg_col_index                    :2;	//29:28	//* final release로 인해 RTL에서는 "reg_boundary_side"으로 사용중(다음버전에 명칭 업데이트 예정)	Split/Merger에 의해서 Decontour 모듈은 3 2 1 0 으로 인덱싱 되어있으나 설정은 아래의 숫자를 참조	내부 동작적인 측면에서 1과 2는 똑같은 형태(튜닝 등에 의해서 위치를 표시하기 위해 구별)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd2                           :1;
	UINT32 reg_col_mode_en                  :1;	//31 //* final release로 인해 RTL에서는 "reg_boundary_en"으로 사용중(다음버전에 명칭 업데이트 예정)	0 : col_mode off	1 : col_mode on
	};
}PE_E60_REG_LED_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEAC RW
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//1:0	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//3:2	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//5:4	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//7:6	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//9:8	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//11:10	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//28 //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//29 //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//30 //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_LED_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEB0 RW
	UINT32 reg_rd_roi_x1                    :12;	//11:0	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//27:16	//실제 좌표에서 /2를 한 값을 입력해야 함(다음 버전 업데이트)
	UINT32 resvd1                           :4;
	};
}PE_E60_REG_LED_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEB4 RW
	UINT32 reg_rd_roi_y1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_REG_LED_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEB8 RW
	UINT32 reg_1st_rd_luma_x1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x0               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_prev_x                   :12;	//31:20	//Defualt: 30	이전 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_E60_REG_LED_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEBC RW
	UINT32 reg_1st_rd_luma_x3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x2               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_next_x                   :12;	//31:20	//Defualt: 40	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_E60_REG_LED_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEC0 RW
	UINT32 reg_1st_rd_luma_x5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_prev_y                   :7;	//30:24	//Defualt: 120	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_E60_REG_LED_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEC4 RW
	UINT32 reg_1st_rd_luma_x7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_next_y                   :7;	//30:24	//Defualt: 121	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_E60_REG_LED_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEC8 RW
	UINT32 reg_1st_rd_luma_y1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_LED_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AECC RW
	UINT32 reg_1st_rd_luma_y3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_LED_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AED0 RW
	UINT32 reg_1st_rd_luma_y5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_LED_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AED4 RW
	UINT32 reg_1st_rd_luma_y7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_LED_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AED8 RW
	UINT32 reg_face_demo_x1                 :13;	//12:0	//x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//28:16	//x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//31 //face gain demo mode 동작
	};
}PE_E60_REG_LED_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903AEDC RW
	UINT32 reg_face_demo_y1                 :13;	//12:0	//y0 < pos_y < y1 일때 동작
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//28:16	//y0 < pos_y < y1 일때 동작
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_LED_DECON_CTRL_96_T;

typedef struct {
	PE_LED_E60_AD_RP_HV_POS_T							   ad_rp_hv_pos;	//0xC9036940
	PE_LED_E60_AD_RP_MAKE_EN_T 							  ad_rp_make_en;	//0xC9036944
	PE_LED_E60_AD_RP_R_VALUE_T 							  ad_rp_r_value;	//0xC9036948
	PE_LED_E60_AD_RP_G_VALUE_T 							  ad_rp_g_value;	//0xC903694C
	PE_LED_E60_AD_RP_B_VALUE_T 							  ad_rp_b_value;	//0xC9036950
}PE_LED_RP_REG_E60_T;

typedef struct {
	PE_E60_REG_LED_DECON_TOP_CTRL_T             reg_decon_top_ctrl;	//0xC903AD00
	PE_E60_REG_LED_DECON_CTRL_0_T                 reg_decon_ctrl_0;	//0xC903AD04
	PE_E60_REG_LED_DECON_CTRL_1_T                 reg_decon_ctrl_1;	//0xC903AD08
	PE_E60_REG_LED_DECON_CTRL_2_T                 reg_decon_ctrl_2;	//0xC903AD0C
	PE_E60_REG_LED_DECON_CTRL_3_T                 reg_decon_ctrl_3;	//0xC903AD10
	PE_E60_REG_LED_DECON_CTRL_4_T                 reg_decon_ctrl_4;	//0xC903AD14
	PE_E60_REG_LED_DECON_CTRL_5_T                 reg_decon_ctrl_5;	//0xC903AD18
	PE_E60_REG_LED_DECON_CTRL_6_T                 reg_decon_ctrl_6;	//0xC903AD1C
	PE_E60_REG_LED_DECON_CTRL_7_T                 reg_decon_ctrl_7;	//0xC903AD20
	PE_E60_REG_LED_DECON_CTRL_8_T                 reg_decon_ctrl_8;	//0xC903AD24
	PE_E60_REG_LED_DECON_CTRL_9_T                 reg_decon_ctrl_9;	//0xC903AD28
	PE_E60_REG_LED_DECON_CTRL_10_T               reg_decon_ctrl_10;	//0xC903AD2C
	PE_E60_REG_LED_DECON_CTRL_11_T               reg_decon_ctrl_11;	//0xC903AD30
	PE_E60_REG_LED_DECON_CTRL_12_T               reg_decon_ctrl_12;	//0xC903AD34
	PE_E60_REG_LED_DECON_CTRL_13_T               reg_decon_ctrl_13;	//0xC903AD38
	PE_E60_REG_LED_DECON_CTRL_14_T               reg_decon_ctrl_14;	//0xC903AD3C
	PE_E60_REG_LED_DECON_CTRL_15_T               reg_decon_ctrl_15;	//0xC903AD40
	PE_E60_REG_LED_DECON_CTRL_16_T               reg_decon_ctrl_16;	//0xC903AD44
	PE_E60_REG_LED_DECON_CTRL_17_T               reg_decon_ctrl_17;	//0xC903AD48
	PE_E60_REG_LED_DECON_CTRL_18_T               reg_decon_ctrl_18;	//0xC903AD4C
	PE_E60_REG_LED_DECON_CTRL_19_T               reg_decon_ctrl_19;	//0xC903AD50
	PE_E60_REG_LED_DECON_CTRL_20_T               reg_decon_ctrl_20;	//0xC903AD54
	PE_E60_REG_LED_DECON_CTRL_21_T               reg_decon_ctrl_21;	//0xC903AD58
	PE_E60_REG_LED_DECON_CTRL_22_T               reg_decon_ctrl_22;	//0xC903AD5C
	PE_E60_REG_LED_DECON_CTRL_23_T               reg_decon_ctrl_23;	//0xC903AD60
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL0_T    reg_dec_sync_2dly_ctrl0;	//0xC903AD64
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL1_T    reg_dec_sync_2dly_ctrl1;	//0xC903AD68
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL2_T    reg_dec_sync_2dly_ctrl2;	//0xC903AD6C
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL3_T    reg_dec_sync_2dly_ctrl3;	//0xC903AD70
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL4_T    reg_dec_sync_2dly_ctrl4;	//0xC903AD74
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL5_T    reg_dec_sync_2dly_ctrl5;	//0xC903AD78
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL6_T    reg_dec_sync_2dly_ctrl6;	//0xC903AD7C
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL7_T    reg_dec_sync_2dly_ctrl7;	//0xC903AD80
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL8_T    reg_dec_sync_2dly_ctrl8;	//0xC903AD84
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRL9_T    reg_dec_sync_2dly_ctrl9;	//0xC903AD88
	PE_E60_REG_LED_DEC_SYNC_2DLY_CTRLA_T    reg_dec_sync_2dly_ctrla;	//0xC903AD8C
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL0_T    reg_dec_sync_3dly_ctrl0;	//0xC903AD90
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL1_T    reg_dec_sync_3dly_ctrl1;	//0xC903AD94
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL2_T    reg_dec_sync_3dly_ctrl2;	//0xC903AD98
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL3_T    reg_dec_sync_3dly_ctrl3;	//0xC903AD9C
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL4_T    reg_dec_sync_3dly_ctrl4;	//0xC903ADA0
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL5_T    reg_dec_sync_3dly_ctrl5;	//0xC903ADA4
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL6_T    reg_dec_sync_3dly_ctrl6;	//0xC903ADA8
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL7_T    reg_dec_sync_3dly_ctrl7;	//0xC903ADAC
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL8_T    reg_dec_sync_3dly_ctrl8;	//0xC903ADB0
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRL9_T    reg_dec_sync_3dly_ctrl9;	//0xC903ADB4
	PE_E60_REG_LED_DEC_SYNC_3DLY_CTRLA_T    reg_dec_sync_3dly_ctrla;	//0xC903ADB8
	PE_E60_REG_LED_DECON_CTRL_24_T               reg_decon_ctrl_24;	//0xC903ADBC
	PE_E60_REG_LED_DECON_CTRL_25_T               reg_decon_ctrl_25;	//0xC903ADC0
	PE_E60_REG_LED_DECON_CTRL_26_T               reg_decon_ctrl_26;	//0xC903ADC4
	PE_E60_REG_LED_DECON_CTRL_27_T               reg_decon_ctrl_27;	//0xC903ADC8
	PE_E60_REG_LED_DECON_CTRL_28_T               reg_decon_ctrl_28;	//0xC903ADCC
	PE_E60_REG_LED_DECON_CTRL_29_T               reg_decon_ctrl_29;	//0xC903ADD0
	PE_E60_REG_LED_DECON_CTRL_30_T               reg_decon_ctrl_30;	//0xC903ADD4
	PE_E60_REG_LED_DECON_CTRL_31_T               reg_decon_ctrl_31;	//0xC903ADD8
	PE_E60_REG_LED_DECON_CTRL_32_T               reg_decon_ctrl_32;	//0xC903ADDC
	PE_E60_REG_LED_DECON_CTRL_33_T               reg_decon_ctrl_33;	//0xC903ADE0
	PE_E60_REG_LED_DECON_CTRL_34_T               reg_decon_ctrl_34;	//0xC903ADE4
	PE_E60_REG_LED_DECON_CTRL_35_T               reg_decon_ctrl_35;	//0xC903ADE8
	PE_E60_REG_LED_DECON_CTRL_36_T               reg_decon_ctrl_36;	//0xC903ADEC
	PE_E60_REG_LED_DECON_CTRL_37_T               reg_decon_ctrl_37;	//0xC903ADF0
	PE_E60_REG_LED_DECON_CTRL_38_T               reg_decon_ctrl_38;	//0xC903ADF4
	PE_E60_REG_LED_DECON_CTRL_39_T               reg_decon_ctrl_39;	//0xC903ADF8
	PE_E60_REG_LED_DECON_CTRL_40_T               reg_decon_ctrl_40;	//0xC903ADFC
	PE_E60_REG_LED_DECON_CTRL_41_T               reg_decon_ctrl_41;	//0xC903AE00
	PE_E60_REG_LED_DECON_CTRL_42_T               reg_decon_ctrl_42;	//0xC903AE04
	PE_E60_REG_LED_DECON_CTRL_43_T               reg_decon_ctrl_43;	//0xC903AE08
	PE_E60_REG_LED_DECON_CTRL_44_T               reg_decon_ctrl_44;	//0xC903AE0C
	PE_E60_REG_LED_DECON_CTRL_45_T               reg_decon_ctrl_45;	//0xC903AE10
	PE_E60_REG_LED_DECON_CTRL_46_T               reg_decon_ctrl_46;	//0xC903AE14
	PE_E60_REG_LED_DECON_CTRL_47_T               reg_decon_ctrl_47;	//0xC903AE18
	PE_E60_REG_LED_DECON_CTRL_48_T               reg_decon_ctrl_48;	//0xC903AE1C
	PE_E60_REG_LED_DECON_CTRL_49_T               reg_decon_ctrl_49;	//0xC903AE20
	PE_E60_REG_LED_DECON_CTRL_50_T               reg_decon_ctrl_50;	//0xC903AE24
	PE_E60_REG_LED_DECON_CTRL_51_T               reg_decon_ctrl_51;	//0xC903AE28
	PE_E60_REG_LED_DECON_CTRL_52_T               reg_decon_ctrl_52;	//0xC903AE2C
	PE_E60_REG_LED_DECON_CTRL_53_T               reg_decon_ctrl_53;	//0xC903AE30
	PE_E60_REG_LED_DECON_CTRL_54_T               reg_decon_ctrl_54;	//0xC903AE34
	PE_E60_REG_LED_DECON_CTRL_55_T               reg_decon_ctrl_55;	//0xC903AE38
	PE_E60_REG_LED_DECON_CTRL_56_T               reg_decon_ctrl_56;	//0xC903AE3C
	PE_E60_REG_LED_DECON_CTRL_57_T               reg_decon_ctrl_57;	//0xC903AE40
	PE_E60_REG_LED_DECON_CTRL_58_T               reg_decon_ctrl_58;	//0xC903AE44
	PE_E60_REG_LED_DECON_CTRL_59_T               reg_decon_ctrl_59;	//0xC903AE48
	PE_E60_REG_LED_DECON_CTRL_60_T               reg_decon_ctrl_60;	//0xC903AE4C
	PE_E60_REG_LED_DECON_CTRL_61_T               reg_decon_ctrl_61;	//0xC903AE50
	PE_E60_REG_LED_DECON_CTRL_62_T               reg_decon_ctrl_62;	//0xC903AE54
	PE_E60_REG_LED_DECON_CTRL_63_T               reg_decon_ctrl_63;	//0xC903AE58
	PE_E60_REG_LED_DECON_CTRL_64_T               reg_decon_ctrl_64;	//0xC903AE5C
	PE_E60_REG_LED_DECON_CTRL_65_T               reg_decon_ctrl_65;	//0xC903AE60
	PE_E60_REG_LED_DECON_CTRL_66_T               reg_decon_ctrl_66;	//0xC903AE64
	PE_E60_REG_LED_DECON_CTRL_67_T               reg_decon_ctrl_67;	//0xC903AE68
	PE_E60_REG_LED_DECON_CTRL_68_T               reg_decon_ctrl_68;	//0xC903AE6C
	PE_E60_REG_LED_DECON_CTRL_69_T               reg_decon_ctrl_69;	//0xC903AE70
	PE_E60_REG_LED_DECON_CTRL_70_T               reg_decon_ctrl_70;	//0xC903AE74
	PE_E60_REG_LED_DECON_CTRL_71_T               reg_decon_ctrl_71;	//0xC903AE78
	PE_E60_REG_LED_DECON_CTRL_72_T               reg_decon_ctrl_72;	//0xC903AE7C
	PE_E60_REG_LED_DECON_CTRL_73_T               reg_decon_ctrl_73;	//0xC903AE80
	PE_E60_REG_LED_DECON_CTRL_74_T               reg_decon_ctrl_74;	//0xC903AE84
	PE_E60_REG_LED_DECON_CTRL_75_T               reg_decon_ctrl_75;	//0xC903AE88
	PE_E60_REG_LED_DECON_CTRL_76_T               reg_decon_ctrl_76;	//0xC903AE8C
	PE_E60_REG_LED_DECON_CTRL_77_T               reg_decon_ctrl_77;	//0xC903AE90
	PE_E60_REG_LED_DECON_CTRL_78_T               reg_decon_ctrl_78;	//0xC903AE94
	PE_E60_REG_LED_DECON_CTRL_79_T               reg_decon_ctrl_79;	//0xC903AE98
	PE_E60_REG_LED_DECON_CTRL_80_T               reg_decon_ctrl_80;	//0xC903AE9C
	PE_E60_REG_LED_DECON_CTRL_81_T               reg_decon_ctrl_81;	//0xC903AEA0
	PE_E60_REG_LED_DECON_CTRL_82_T               reg_decon_ctrl_82;	//0xC903AEA4
	PE_E60_REG_LED_DECON_CTRL_83_T               reg_decon_ctrl_83;	//0xC903AEA8
	PE_E60_REG_LED_DECON_CTRL_84_T               reg_decon_ctrl_84;	//0xC903AEAC
	PE_E60_REG_LED_DECON_CTRL_85_T               reg_decon_ctrl_85;	//0xC903AEB0
	PE_E60_REG_LED_DECON_CTRL_86_T               reg_decon_ctrl_86;	//0xC903AEB4
	PE_E60_REG_LED_DECON_CTRL_87_T               reg_decon_ctrl_87;	//0xC903AEB8
	PE_E60_REG_LED_DECON_CTRL_88_T               reg_decon_ctrl_88;	//0xC903AEBC
	PE_E60_REG_LED_DECON_CTRL_89_T               reg_decon_ctrl_89;	//0xC903AEC0
	PE_E60_REG_LED_DECON_CTRL_90_T               reg_decon_ctrl_90;	//0xC903AEC4
	PE_E60_REG_LED_DECON_CTRL_91_T               reg_decon_ctrl_91;	//0xC903AEC8
	PE_E60_REG_LED_DECON_CTRL_92_T               reg_decon_ctrl_92;	//0xC903AECC
	PE_E60_REG_LED_DECON_CTRL_93_T               reg_decon_ctrl_93;	//0xC903AED0
	PE_E60_REG_LED_DECON_CTRL_94_T               reg_decon_ctrl_94;	//0xC903AED4
	PE_E60_REG_LED_DECON_CTRL_95_T               reg_decon_ctrl_95;	//0xC903AED8
	PE_E60_REG_LED_DECON_CTRL_96_T               reg_decon_ctrl_96;	//0xC903AEDC
}PE_LED_DCNT_REG_E60_T;

#endif

