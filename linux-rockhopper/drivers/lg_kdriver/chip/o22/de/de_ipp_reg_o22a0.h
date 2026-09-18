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

#ifndef _IPP_REG_O22A0_H_
#define _IPP_REG_O22A0_H_

/*-----------------------------------------------------------------------------
		0xc8001400L ipp_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                            : 3 ;  //  2: 0     
	UINT32 prew_rd_422                        : 1 ;  //     3     
	UINT32 i_c_fmt                            : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 hdmi420_on                         : 1 ;  //     8     
	UINT32 c_vsample_en                       : 1 ;  //     9     
	UINT32 c_hsample_en                       : 1 ;  //    10     
	UINT32 hsc_sw_en                          : 1 ;  //    11     
	UINT32 prew_mux_sel                       : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 cvi_mux_sel                        : 3 ;  // 18:16     
	UINT32                                    : 5 ;  // 23:19     reserved
	UINT32 wr_disalbe                         : 1 ;  //    24     
	UINT32                                    : 4 ;  // 28:25     reserved
	UINT32 set_mvi_val                        : 1 ;  //    29     
	UINT32                                    : 1 ;  //    30     reserved
	UINT32 pr_sq                              : 1 ;  //    31     
} O22A0_IPP_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xc8001404L ipp_ctrl1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 mifr_mode                          : 1 ;  //     0     
	UINT32                                    : 7 ;  //  7: 1     reserved
	UINT32 hsc_enable                         : 1 ;  //     8     
	UINT32 vsc_enable                         : 1 ;  //     9     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 gos_enable                         : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 line_diff_en                       : 1 ;  //    16     
	UINT32                                    : 3 ;  // 19:17     reserved
	UINT32 line_diff                          : 12;  // 31:20     
} O22A0_IPP_CTRL1_T;

/*-----------------------------------------------------------------------------
		0xc8001408L ipp_ctrl2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 prefetch_wr_lcnt                   : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 prefetch_rd_lcnt                   : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 wr_yoffset                         : 11;  // 18: 8     
	UINT32                                    : 1 ;  //    19     reserved
	UINT32 wr_xoffset                         : 12;  // 31:20     
} O22A0_IPP_CTRL2_T;

/*-----------------------------------------------------------------------------
		0xc800140cL ipp_ctrl3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 lr_switch_on                       : 1 ;  //     0     
	UINT32 lr_switch_mode                     : 1 ;  //     1     
	UINT32 lr_switch_auto                     : 1 ;  //     2     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 fifo_split                         : 1 ;  //     4     
	UINT32                                    : 3 ;  //  7: 5     reserved
	UINT32 lr_write_sel                       : 1 ;  //     8     
	UINT32 lr_write_mode                      : 1 ;  //     9     
	UINT32 lr_write_auto                      : 1 ;  //    10     
	UINT32                                    : 1 ;  //    11     reserved
	UINT32 dec3d_mux_sel                      : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 auto_3d_mode                       : 3 ;  // 18:16     
} O22A0_IPP_CTRL3_T;

/*-----------------------------------------------------------------------------
		0xc8001410L ipp_ctrlr ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 r_o_c_fmt                          : 3 ;  //  2: 0     
	UINT32                                    : 1 ;  //     3     reserved
	UINT32 r_i_c_fmt                          : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 rd_yoffset                         : 12;  // 19: 8     
	UINT32 rd_xoffset                         : 8 ;  // 27:20     
	UINT32                                    : 3 ;  // 30:28     reserved
	UINT32 r_pr_sq                            : 1 ;  //    31     
} O22A0_IPP_CTRLR_T;

/*-----------------------------------------------------------------------------
		0xc8001414L ipp_hsc_y_set_val_0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_y                     : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 aal_coef_0_y                       : 10;  // 21:12     
} O22A0_IPP_HSC_Y_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
		0xc8001418L ipp_hsc_y_set_val_1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_y                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_2_y                       : 10;  // 21:12     
} O22A0_IPP_HSC_Y_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
		0xc800141cL ipp_hsc_y_set_val_2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_y                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_4_y                       : 10;  // 21:12     
} O22A0_IPP_HSC_Y_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
		0xc8001420L ipp_hsc_y_set_val_3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_5_y                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_6_y                       : 10;  // 21:12     
} O22A0_IPP_HSC_Y_SET_VAL_3_T;

/*-----------------------------------------------------------------------------
		0xc8001424L ipp_hsc_c_set_val_0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 phase_offset_c                     : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 aal_coef_0_c                       : 10;  // 21:12     
} O22A0_IPP_HSC_C_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
		0xc8001428L ipp_hsc_c_set_val_1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_1_c                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_2_c                       : 10;  // 21:12     
} O22A0_IPP_HSC_C_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
		0xc800142cL ipp_hsc_c_set_val_2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_3_c                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_4_c                       : 10;  // 21:12     
} O22A0_IPP_HSC_C_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
		0xc8001430L ipp_hsc_c_set_val_3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 aal_coef_5_c                       : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 aal_coef_6_c                       : 10;  // 21:12     
} O22A0_IPP_HSC_C_SET_VAL_3_T;

/*-----------------------------------------------------------------------------
		0xc8001434L ipp_size_i ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vsize_i                            : 12;  // 27:16     
} O22A0_IPP_SIZE_I_T;

/*-----------------------------------------------------------------------------
		0xc8001438L ipp_size_o ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize                              : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vsize                              : 12;  // 27:16     
} O22A0_IPP_SIZE_O_T;

/*-----------------------------------------------------------------------------
		0xc800143cL ipp_size_r ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_r                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vsize_r                            : 12;  // 27:16     
} O22A0_IPP_SIZE_R_T;

/*-----------------------------------------------------------------------------
		0xc8001440L ipp_crop_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 voffset                            : 12;  // 27:16     
} O22A0_IPP_CROP_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc8001444L ipp_crop_active ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hactive                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vactive                            : 12;  // 27:16     
} O22A0_IPP_CROP_ACTIVE_T;

/*-----------------------------------------------------------------------------
		0xc8001448L ipp_pixel_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 cr                                 : 8 ;  //  7: 0     
	UINT32 cb                                 : 8 ;  // 15: 8     
	UINT32 y                                  : 8 ;  // 23:16     
	UINT32 pattern_data_en                    : 1 ;  //    24     
	UINT32                                    : 6 ;  // 30:25     reserved
	UINT32 pixel_data_en                      : 1 ;  //    31     
} O22A0_IPP_PIXEL_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc800144cL ipp_hsc_input_info ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsc_i_hsize                        : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 hsc_i_vsize                        : 12;  // 27:16     
} O22A0_IPP_HSC_INPUT_INFO_T;

/*-----------------------------------------------------------------------------
		0xc8001450L ipp_status ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 smux_ro_lcnt                       : 12;  // 11: 0
	UINT32 smux_pic_init_w_count              : 4 ;  // 19:16
	UINT32 smux_pic_init_r_count              : 4 ;  // 23:20
} O22A0_IPP_STATUS_T;

/*-----------------------------------------------------------------------------
		0xc8001454L ipp_status1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 smux_ro_w_lcnt                     : 12;  // 11: 0     
} O22A0_IPP_STATUS1_T;

/*-----------------------------------------------------------------------------
		0xc8001458L ipp_vsc_y_set_val_0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_phase_offset_y                 : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 vsc_aal_coef_0_y                   : 10;  // 21:12     
} O22A0_IPP_VSC_Y_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
		0xc800145cL ipp_vsc_y_set_val_1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_1_y                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_2_y                   : 10;  // 21:12     
} O22A0_IPP_VSC_Y_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
		0xc8001460L ipp_vsc_y_set_val_2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_3_y                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_4_y                   : 10;  // 21:12     
} O22A0_IPP_VSC_Y_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
		0xc8001464L ipp_vsc_y_set_val_3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_5_y                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_6_y                   : 10;  // 21:12     
} O22A0_IPP_VSC_Y_SET_VAL_3_T;

/*-----------------------------------------------------------------------------
		0xc8001468L ipp_vsc_c_set_val_0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_phase_offset_c                 : 9 ;  //  8: 0     
	UINT32                                    : 3 ;  // 11: 9     reserved
	UINT32 vsc_aal_coef_0_c                   : 10;  // 21:12     
} O22A0_IPP_VSC_C_SET_VAL_0_T;

/*-----------------------------------------------------------------------------
		0xc800146cL ipp_vsc_c_set_val_1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_1_c                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_2_c                   : 10;  // 21:12     
} O22A0_IPP_VSC_C_SET_VAL_1_T;

/*-----------------------------------------------------------------------------
		0xc8001470L ipp_vsc_c_set_val_2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_3_c                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_4_c                   : 10;  // 21:12     
} O22A0_IPP_VSC_C_SET_VAL_2_T;

/*-----------------------------------------------------------------------------
		0xc8001474L ipp_vsc_c_set_val_3 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 vsc_aal_coef_5_c                   : 10;  //  9: 0     
	UINT32                                    : 2 ;  // 11:10     reserved
	UINT32 vsc_aal_coef_6_c                   : 10;  // 21:12     
} O22A0_IPP_VSC_C_SET_VAL_3_T;

/*-----------------------------------------------------------------------------
		0xc8001478L ipp_vsc_y_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 denominator_y                      : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 numerator_y                        : 12;  // 27:16     
	UINT32                                    : 1 ;  //    28     reserved
	UINT32 vsc_config_y                       : 1 ;  //    29     
	UINT32 bilinear_y                         : 1 ;  //    30     
	UINT32 sampling_mode_y                    : 1 ;  //    31     
} O22A0_IPP_VSC_Y_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc800147cL ipp_vsc_c_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 denominator_c                      : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 numerator_c                        : 12;  // 27:16     
	UINT32                                    : 1 ;  //    28     reserved
	UINT32 vsc_config_c                       : 1 ;  //    29     
	UINT32 bilinear_c                         : 1 ;  //    30     
	UINT32 sampling_mode_c                    : 1 ;  //    31     
} O22A0_IPP_VSC_C_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001480L ipp_sc_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_sc_crtl                        : 32;  // 31: 0     
} O22A0_IPP_SC_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc8001484L ipp_sc_dectect ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 out_scene_change_mv                : 1 ;  //     0     
	UINT32 out_scene_change                   : 1 ;  //     1     
	UINT32                                    : 21;  // 22: 2     reserved
	UINT32 out_scd                            : 8 ;  // 30:23     
	UINT32 scd_done                           : 1 ;  //    31     
} O22A0_IPP_SC_DECTECT_T;

/*-----------------------------------------------------------------------------
		0xc8001488L ipp_sc_dectect1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 out_scd_23b                        : 23;  // 22: 0     
} O22A0_IPP_SC_DECTECT1_T;

/*-----------------------------------------------------------------------------
		0xc800148cL debug ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 status                             : 16;  // 15: 0     
	UINT32 y_px_out                           : 8 ;  // 23:16     
	UINT32 c_px_out                           : 8 ;  // 31:24     
} O22A0_DEBUG_T;

/*-----------------------------------------------------------------------------
		0xc8001490L dec3d_ctrl_0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 l_y_h_offset                       : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 l_y_h_width                        : 13;  // 28:16     
	UINT32 force_ready_r                      : 1 ;  //    29     
	UINT32 force_ready_l                      : 1 ;  //    30     
} O22A0_DEC3D_CTRL_0_T;

/*-----------------------------------------------------------------------------
		0xc8001494L dec3d_ctrl_1 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 l_y_v_offset                       : 12;  // 11: 0     
	UINT32                                    : 4 ;  // 15:12     reserved
	UINT32 l_y_v_height                       : 12;  // 27:16     
} O22A0_DEC3D_CTRL_1_T;

/*-----------------------------------------------------------------------------
		0xc8001498L dec3d_ctrl_2 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 frame_packing_active_space         : 8 ;  //  7: 0     
	UINT32 y_v_sub_sample_offset_en           : 1 ;  //     8     
	UINT32                                    : 7 ;  // 15: 9     reserved
	UINT32 c_v_sub_sample_offset_en           : 1 ;  //    16     
	UINT32 v_sub_sample_en                    : 1 ;  //    17     
	UINT32                                    : 2 ;  // 19:18     reserved
	UINT32 c_h_even_line_sub_sample_offset_en : 1 ;  //    20     
	UINT32 c_h_odd_line_sub_sample_offset_en  : 1 ;  //    21     
	UINT32                                    : 2 ;  // 23:22     reserved
	UINT32 h_sub_sample_en                    : 1 ;  //    24     
	UINT32                                    : 3 ;  // 27:25     reserved
	UINT32 y_h_even_line_sub_sample_offset_en : 1 ;  //    28     
	UINT32 y_h_odd_line_sub_sample_offset_en  : 1 ;  //    29     
} O22A0_DEC3D_CTRL_2_T;

/*-----------------------------------------------------------------------------
		0xc800149cL ipp_out_crop_offset ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hoffset                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 voffset                            : 12;  // 27:16     
	UINT32 out_gos_enable                     : 1 ;  //    28     
} O22A0_IPP_OUT_CROP_OFFSET_T;

/*-----------------------------------------------------------------------------
		0xc80014a0L ipp_out_crop_active ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hactive                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vactive                            : 12;  // 27:16     
} O22A0_IPP_OUT_CROP_ACTIVE_T;

typedef struct {
	O22A0_IPP_CTRL0_T                  	ipp_ctrl0;                    //0xc8001400L
	O22A0_IPP_CTRL1_T                  	ipp_ctrl1;                    //0xc8001404L
	O22A0_IPP_CTRL2_T                  	ipp_ctrl2;                    //0xc8001408L
	O22A0_IPP_CTRL3_T                  	ipp_ctrl3;                    //0xc800140cL
	O22A0_IPP_CTRLR_T                  	ipp_ctrlr;                    //0xc8001410L
	O22A0_IPP_HSC_Y_SET_VAL_0_T        	ipp_hsc_y_set_val_0;          //0xc8001414L
	O22A0_IPP_HSC_Y_SET_VAL_1_T        	ipp_hsc_y_set_val_1;          //0xc8001418L
	O22A0_IPP_HSC_Y_SET_VAL_2_T        	ipp_hsc_y_set_val_2;          //0xc800141cL
	O22A0_IPP_HSC_Y_SET_VAL_3_T        	ipp_hsc_y_set_val_3;          //0xc8001420L
	O22A0_IPP_HSC_C_SET_VAL_0_T        	ipp_hsc_c_set_val_0;          //0xc8001424L
	O22A0_IPP_HSC_C_SET_VAL_1_T        	ipp_hsc_c_set_val_1;          //0xc8001428L
	O22A0_IPP_HSC_C_SET_VAL_2_T        	ipp_hsc_c_set_val_2;          //0xc800142cL
	O22A0_IPP_HSC_C_SET_VAL_3_T        	ipp_hsc_c_set_val_3;          //0xc8001430L
	O22A0_IPP_SIZE_I_T                 	ipp_size_i;                   //0xc8001434L
	O22A0_IPP_SIZE_O_T                 	ipp_size_o;                   //0xc8001438L
	O22A0_IPP_SIZE_R_T                 	ipp_size_r;                   //0xc800143cL
	O22A0_IPP_CROP_OFFSET_T            	ipp_crop_offset;              //0xc8001440L
	O22A0_IPP_CROP_ACTIVE_T            	ipp_crop_active;              //0xc8001444L
	O22A0_IPP_PIXEL_CTRL_T             	ipp_pixel_ctrl;               //0xc8001448L
	O22A0_IPP_HSC_INPUT_INFO_T         	ipp_hsc_input_info;           //0xc800144cL
	O22A0_IPP_STATUS_T                 	ipp_status;                   //0xc8001450L
	O22A0_IPP_STATUS1_T                	ipp_status1;                  //0xc8001454L
	O22A0_IPP_VSC_Y_SET_VAL_0_T        	ipp_vsc_y_set_val_0;          //0xc8001458L
	O22A0_IPP_VSC_Y_SET_VAL_1_T        	ipp_vsc_y_set_val_1;          //0xc800145cL
	O22A0_IPP_VSC_Y_SET_VAL_2_T        	ipp_vsc_y_set_val_2;          //0xc8001460L
	O22A0_IPP_VSC_Y_SET_VAL_3_T        	ipp_vsc_y_set_val_3;          //0xc8001464L
	O22A0_IPP_VSC_C_SET_VAL_0_T        	ipp_vsc_c_set_val_0;          //0xc8001468L
	O22A0_IPP_VSC_C_SET_VAL_1_T        	ipp_vsc_c_set_val_1;          //0xc800146cL
	O22A0_IPP_VSC_C_SET_VAL_2_T        	ipp_vsc_c_set_val_2;          //0xc8001470L
	O22A0_IPP_VSC_C_SET_VAL_3_T        	ipp_vsc_c_set_val_3;          //0xc8001474L
	O22A0_IPP_VSC_Y_CTRL_T             	ipp_vsc_y_ctrl;               //0xc8001478L
	O22A0_IPP_VSC_C_CTRL_T             	ipp_vsc_c_ctrl;               //0xc800147cL
	O22A0_IPP_SC_CTRL_T                	ipp_sc_ctrl;                  //0xc8001480L
	O22A0_IPP_SC_DECTECT_T             	ipp_sc_dectect;               //0xc8001484L
	O22A0_IPP_SC_DECTECT1_T            	ipp_sc_dectect1;              //0xc8001488L
	O22A0_DEBUG_T                      	debug;                        //0xc800148cL
	O22A0_DEC3D_CTRL_0_T               	dec3d_ctrl_0;                 //0xc8001490L
	O22A0_DEC3D_CTRL_1_T               	dec3d_ctrl_1;                 //0xc8001494L
	O22A0_DEC3D_CTRL_2_T               	dec3d_ctrl_2;                 //0xc8001498L
	O22A0_IPP_OUT_CROP_OFFSET_T        	ipp_out_crop_offset;          //0xc800149cL
	O22A0_IPP_OUT_CROP_ACTIVE_T        	ipp_out_crop_active;          //0xc80014a0L
} DE_IPP_REG_O22A0_T;

#endif //#ifdef _IPP_REG_O22A0_H_
