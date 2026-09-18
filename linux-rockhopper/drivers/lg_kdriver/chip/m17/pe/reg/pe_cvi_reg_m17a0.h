#ifndef _PE_CVI_REG_M17A0_H_
#define _PE_CVI_REG_M17A0_H_
/*-----------------------------------------------------------------------------
                             0xc9000100L HDMI_MUX_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 src_sel_e                          :2 ;	//1:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 src_sel_o                          :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 pre_mux_sel                        :2 ;	//9:8
	UINT32 reserved03                         :6 ;	//reserved
	UINT32 pre_out_mux_l_sel                  :2 ;	//17:16
	UINT32 reserved04                         :2 ;	//reserved
	UINT32 pre_out_mux_r_sel                  :2 ;	//21:20
	UINT32 reserved05                         :2 ;	//reserved
	UINT32 reserved                           :8 ;	//31:24
}PE_M17_HDMI_MUX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000104L HDMI_420IN_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 yin_delay                          :2 ;	//1:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 cbin_delay                         :2 ;	//5:4
	UINT32 cin_delay                          :2 ;	//7:6
	UINT32 y_swap                             :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 c_swap                             :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 input_8k_en                        :1 ;	//15
}PE_M17_HDMI_420IN_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000114L HDMI_FIR_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fir_y_en                           :1 ;	//0 
	UINT32 fir_c_en                           :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 sum_sample_en                      :1 ;	//4 
	UINT32 reserved02                         :11;	//reserved
	UINT32 reserved                           :10;	//25:16
}PE_M17_HDMI_FIR_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000118L HDMI_FIR_Y_COEF0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fir_y_coef0                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 fir_y_coef1                        :10;	//25:16
}PE_M17_HDMI_FIR_Y_COEF0_T;
/*-----------------------------------------------------------------------------
                             0xc900011cL HDMI_FIR_Y_COEF1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fir_y_coef2                        :10;	//9:0
}PE_M17_HDMI_FIR_Y_COEF1_T;
/*-----------------------------------------------------------------------------
                             0xc9000120L HDMI_FIR_C_COEF0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fir_y_coef0                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 fir_y_coef1                        :10;	//25:16
}PE_M17_HDMI_FIR_C_COEF0_T;
/*-----------------------------------------------------------------------------
                             0xc9000124L HDMI_FIR_C_COEF1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fir_y_coef2                        :10;	//9:0
	UINT32 reserved01                         :21;	//reserved
	UINT32 coef_load                          :1 ;	//31
}PE_M17_HDMI_FIR_C_COEF1_T;
/*-----------------------------------------------------------------------------
                             0xc900012cL HDMI_RX_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 data_mux_r                         :2 ;	//1:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 data_mux_b                         :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 data_mux_g                         :2 ;	//9:8
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 dither_ctrl                        :2 ;	//13:12
	UINT32 dither_pass_en                     :1 ;	//14
}PE_M17_HDMI_RX_CTRL_T;


/*-----------------------------------------------------------------------------
                             0xc9000200L TOP_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 scan_type                          :1 ;	//0 
	UINT32 field_gen_mode                     :2 ;	//2:1
	UINT32 auto_field_gen                     :2 ;	//4:3
	UINT32 data_bit_mode                      :1 ;	//5 
	UINT32 chroma_sampling                    :1 ;	//6 
	UINT32 aspect_ratio                       :1 ;	//7 
	UINT32 yc_delay_mode_r                    :2 ;	//9:8
	UINT32 yc_delay_mode_b                    :2 ;	//11:10
	UINT32 yc_delay_mode_g                    :2 ;	//13:12
	UINT32 data_in_sel                        :4 ;	//17:14
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 auto_sync_polarity                 :1 ;	//19
	UINT32 manual_sync_polarity               :2 ;	//21:20
	UINT32 adc_cut_direction                  :1 ;	//22
	UINT32 adc_bit_sel                        :1 ;	//23
	UINT32 br_port_swap                       :1 ;	//24
	UINT32 r_port_swap                        :1 ;	//25
	UINT32 b_port_swap                        :1 ;	//26
	UINT32 g_port_swap                        :1 ;	//27
	UINT32 bit_numbering_lsb2                 :3 ;	//30:28
	UINT32 data_en_mode                       :1 ;	//31
}PE_M17_TOP_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000204L OFFSET_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 offset_h                           :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 offset_v                           :13;	//28:16
}PE_M17_OFFSET_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000208L SIZE_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 size_h                             :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 size_v                             :13;	//28:16
}PE_M17_SIZE_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900020cL INT_SYNC_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 res_hsync                          :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 res_hfp                            :10;	//25:16
}PE_M17_INT_SYNC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9000210L INT_SYNC_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 res_vfp                            :5 ;	//12:8
	UINT32 res_vsync                          :2 ;	//14:13
	UINT32 res_field_add_line                 :1 ;	//15
	UINT32 res_field_sel                      :1 ;	//16
}PE_M17_INT_SYNC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000214L RESERVED000                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED000_T;
/*-----------------------------------------------------------------------------
                             0xc9000218L RESERVED001                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED001_T;
/*-----------------------------------------------------------------------------
                             0xc900021cL RESERVED002                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED002_T;
/*-----------------------------------------------------------------------------
                             0xc9000220L RESERVED003                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED003_T;
/*-----------------------------------------------------------------------------
                             0xc9000224L CSC_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_coefficient1                   :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 csc_coefficient0                   :15;	//30:16
}PE_M17_CSC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9000228L CSC_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_coefficient3                   :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 csc_coefficient2                   :15;	//30:16
}PE_M17_CSC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900022cL CSC_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_coefficient5                   :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 csc_coefficient4                   :15;	//30:16
}PE_M17_CSC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9000230L CSC_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_coefficient7                   :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 csc_coefficient6                   :15;	//30:16
}PE_M17_CSC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc9000234L CSC_CTRL4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_offset0                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 csc_coefficient8                   :15;	//30:16
}PE_M17_CSC_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc9000238L CSC_CTRL5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_offset2                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 csc_offset1                        :11;	//26:16
}PE_M17_CSC_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc900023cL CSC_CTRL6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_offset4                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 csc_offset3                        :11;	//26:16
}PE_M17_CSC_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc9000240L CSC_CTRL7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 csc_coeff_load                     :1 ;	//0 
	UINT32 csc_en                             :1 ;	//1 
	UINT32 csc_msb_4b_only_mode               :1 ;	//2 
	UINT32 reserved01                         :13;	//reserved
	UINT32 csc_offset5                        :11;	//26:16
}PE_M17_CSC_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc9000244L MISC_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pattern_type                       :3 ;	//2:0
	UINT32 pattern_csc                        :1 ;	//3 
	UINT32 pattern_detail                     :4 ;	//7:4
	UINT32 reg_update_pulse                   :1 ;	//8 
	UINT32 field_fix_mode                     :2 ;	//10:9
	UINT32 black_sel                          :1 ;	//11
	UINT32 write_inhibit                      :1 ;	//12
	UINT32 sim_mode                           :1 ;	//13
	UINT32 black_off                          :1 ;	//14
	UINT32 field_edge                         :1 ;	//15
	UINT32 ha_gen                             :1 ;	//16
	UINT32 monitor_on                         :1 ;	//17
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 yc_delay_mode_r                    :2 ;	//21:20
	UINT32 yc_delay_mode_b                    :2 ;	//23:22
	UINT32 yc_delay_mode_g                    :2 ;	//25:24
	UINT32 field_detect_vris                  :1 ;	//26
	UINT32 sub_sample_mode                    :1 ;	//27
	UINT32 reg_update_position                :4 ;	//31:28
}PE_M17_MISC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000248L OFFSET_READ                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hoffset_read                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 voffset_read                       :13;	//28:16
}PE_M17_OFFSET_READ_T;
/*-----------------------------------------------------------------------------
                             0xc900024cL PRE3D_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre3d_sync_enable                  :1 ;	//0 
	UINT32 pre3d_sync_mode                    :2 ;	//2:1
	UINT32 pre3d_field_mode                   :1 ;	//3 
	UINT32 pre3d_frame_lr_mode                :1 ;	//4 
	UINT32 pre3d_mid_vsync_bypass             :1 ;	//5 
	UINT32 pre3d_field_bypass                 :1 ;	//6 
	UINT32 reserved                           :1 ;	//7 
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 pre3d_active_line_num              :13;	//28:16
}PE_M17_PRE3D_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9000250L PRE3D_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre3d_active_space1_line_num       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 pre3d_active_space2_line_num       :13;	//28:16
}PE_M17_PRE3D_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000254L PRE3D_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre3d_front_porch_line_num         :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 pre3d_sync_line_num                :13;	//28:16
}PE_M17_PRE3D_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9000258L SIZE_STATUS1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 sd_hoffset_indurance_read          :8 ;	//7:0
	UINT32 sd_voffset_indurance_read          :8 ;	//15:8
	UINT32 sd_hsync_fault_flag_read           :1 ;	//16
	UINT32 sd_vsync_fault_flag_read           :1 ;	//17
	UINT32 h_sync_polarity                    :1 ;	//18
	UINT32 v_sync_polarity                    :1 ;	//19
	UINT32 field_signal                       :4 ;	//23:20
	UINT32 hsync_at_vsync_fall                :4 ;	//27:24
	UINT32 outfield_at_vactive_fall           :2 ;	//29:28
	UINT32 hoffset_over                       :1 ;	//30
	UINT32 v_offset_over                      :1 ;	//31
}PE_M17_SIZE_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc900025cL SIZE_STATUS2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 de_line_size                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 de_line_count                      :13;	//28:16
}PE_M17_SIZE_STATUS2_T;
/*-----------------------------------------------------------------------------
                             0xc9000260L SIZE_STATUS3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hd_sync_size                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hd_line_size                       :13;	//28:16
}PE_M17_SIZE_STATUS3_T;
/*-----------------------------------------------------------------------------
                             0xc9000264L SIZE_STATUS4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vd_sync_count                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 vd_line_count                      :13;	//28:16
}PE_M17_SIZE_STATUS4_T;
/*-----------------------------------------------------------------------------
                             0xc9000268L PIX_SUM_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 start_pos_x                        :13;	//12:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 pix_sum_enable                     :1 ;	//15
	UINT32 end_pos_x                          :13;	//28:16
	UINT32 field_selection                    :2 ;	//30:29
	UINT32 debug_enable                       :1 ;	//31
}PE_M17_PIX_SUM_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900026cL PIX_SUM_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 start_pos_y                        :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 end_pos_y                          :13;	//28:16
}PE_M17_PIX_SUM_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000270L PIX_SUM_STATUS0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pix_sum_g                          :32;	//31:0
}PE_M17_PIX_SUM_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc9000274L PIX_SUM_STATUS1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pix_sum_b                          :32;	//31:0
}PE_M17_PIX_SUM_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9000278L PIX_SUM_STATUS2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pix_sum_r                          :32;	//31:0
}PE_M17_PIX_SUM_STATUS2_T;
/*-----------------------------------------------------------------------------
                             0xc900027cL SYNC_FIL_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsync_fil_en                       :1 ;	//0 
	UINT32 hsync_counter_en                   :1 ;	//1 
	UINT32 vsync_fil_en                       :1 ;	//2 
	UINT32 vsync_counter_en                   :1 ;	//3 
	UINT32 de_fil_en                          :1 ;	//4 
	UINT32 de_counter_en                      :1 ;	//5 
	UINT32 field_fil_en                       :1 ;	//6 
	UINT32 field_counter_en                   :1 ;	//7 
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 line_count_sel                     :13;	//28:16
}PE_M17_SYNC_FIL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000280L SYNC_FIL_STATUS                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :8 ;	//7:0
	UINT32 hsync_coutner                      :8 ;	//15:8
	UINT32 vsync_counter                      :8 ;	//23:16
	UINT32 de_counter                         :8 ;	//31:24
}PE_M17_SYNC_FIL_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc9000284L RESERVED004                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED004_T;
/*-----------------------------------------------------------------------------
                             0xc9000288L RESERVED005                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED005_T;
/*-----------------------------------------------------------------------------
                             0xc900028cL RESERVED006                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED006_T;
/*-----------------------------------------------------------------------------
                             0xc9000290L SYNC_REPEAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 repeat_y_en                        :1 ;	//0 
	UINT32 repeat_cb_en                       :1 ;	//1 
	UINT32 repeat_cr_en                       :1 ;	//2 
	UINT32 repeat_pixel_odd                   :1 ;	//3 
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 repeat_threshold_y                 :6 ;	//13:8
	UINT32 avg_threshold_y                    :6 ;	//19:14
	UINT32 repeat_threshold_c                 :6 ;	//25:20
	UINT32 avg_threshold_c                    :6 ;	//31:26
}PE_M17_SYNC_REPEAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000294L SYNC_REPEAT_SIZE0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 repeat_pixel_y                     :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE0_T;
/*-----------------------------------------------------------------------------
                             0xc9000298L SYNC_REPEAT_SIZE1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 avg_pixel_y                        :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE1_T;
/*-----------------------------------------------------------------------------
                             0xc900029cL SYNC_REPEAT_SIZE2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 repeat_pixel_cb                    :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE2_T;
/*-----------------------------------------------------------------------------
                             0xc90002a0L SYNC_REPEAT_SIZE3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 avg_pixel_cb                       :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE3_T;
/*-----------------------------------------------------------------------------
                             0xc90002a4L SYNC_REPEAT_SIZE4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 repeat_pixel_cr                    :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE4_T;
/*-----------------------------------------------------------------------------
                             0xc90002a8L SYNC_REPEAT_SIZE5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :21;	//20:0
}PE_M17_SYNC_REPEAT_SIZE5_T;
/*-----------------------------------------------------------------------------
                             0xc90002acL RESERVED007                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED007_T;
/*-----------------------------------------------------------------------------
                             0xc90002b0L RESERVED008                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED008_T;
/*-----------------------------------------------------------------------------
                             0xc90002b4L RESERVED009                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :32 ;	//reserved
}PE_M17_RESERVED009_T;
/*-----------------------------------------------------------------------------
                             0xc90002c0L SIZE_DETECT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 sd_vd_range                        :2 ;	//1:0
	UINT32 sd_ext_range                       :2 ;	//3:2
	UINT32 intr_mask_node                     :1 ;	//4 
	UINT32 intr_mask_nohsync                  :1 ;	//5 
	UINT32 intrl_mask_novsync                 :1 ;	//6 
	UINT32 intr_mask_abnormal                 :1 ;	//7 
	UINT32 intr_mask_invalid                  :1 ;	//8 
	UINT32 intr_mask_de                       :1 ;	//9 
	UINT32 intr_mask_hsync                    :1 ;	//10
	UINT32 intr_mask_vsync                    :1 ;	//11
	UINT32 intr_mask_normal                   :1 ;	//12
	UINT32 intr_mask_valid                    :1 ;	//13
	UINT32 intr_mask_h_cnahge                 :1 ;	//14
	UINT32 sd_en                              :1 ;	//15
	UINT32 sd_frame_cnt                       :3 ;	//18:16
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 sd_novald_duration                 :2 ;	//21:20
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 sd_one_field                       :1 ;	//23
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 nosig_duration_de                  :2 ;	//27:26
	UINT32 nosig_duration_hsync               :2 ;	//29:28
	UINT32 nosig_duration_vsync               :2 ;	//31:30
}PE_M17_SIZE_DETECT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90002c4L SIZE_DETECT_READ                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 line_num_read                      :16;	//15:0
	UINT32 line_width_read                    :16;	//31:16
}PE_M17_SIZE_DETECT_READ_T;
/*-----------------------------------------------------------------------------
                             0xc90002c8L SIZE_STATUS0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 current_line_number_read           :12;	//11:0
	UINT32 de_signal_detect                   :1 ;	//12
	UINT32 hsync_signal_detect                :1 ;	//13
	UINT32 vsync_signal_detect                :1 ;	//14
	UINT32 source_valid                       :1 ;	//15
	UINT32 sd_line_num                        :12;	//27:16
	UINT32 field_at_vactive_fall              :4 ;	//31:28
}PE_M17_SIZE_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc90002ccL SIZE_STATUS5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 sd_2field_size                     :26;	//25:0
}PE_M17_SIZE_STATUS5_T;
/*-----------------------------------------------------------------------------
                             0xc90002d0L SIZE_STATUS6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 diff_vd_vcnt                       :16;	//15:0
	UINT32 diff_ext_vcnt                      :12;	//27:16
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 vd_intr                            :1 ;	//31
}PE_M17_SIZE_STATUS6_T;
/*-----------------------------------------------------------------------------
                             0xc90002d4L SIZE_DETECT_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 abnormal0_en                       :1 ;	//0 
	UINT32 abnormal1_en                       :1 ;	//1 
	UINT32 abnormal2_en                       :1 ;	//2 
	UINT32 abnormal3_en                       :1 ;	//3 
	UINT32 abnormal4_en                       :1 ;	//4 
	UINT32 abnormal5_en                       :1 ;	//5 
	UINT32 abnormal6_en                       :1 ;	//6 
	UINT32 abnormal7_en                       :1 ;	//7 
	UINT32 abnormal0_flag                     :1 ;	//8 
	UINT32 abnormal1_flag                     :1 ;	//9 
	UINT32 abnormal2_flag                     :1 ;	//10
	UINT32 abnormal3_flag                     :1 ;	//11
	UINT32 abnormal4_flag                     :1 ;	//12
	UINT32 abnormal5_flag                     :1 ;	//13
	UINT32 abnormal6_flag                     :1 ;	//14
	UINT32 abnormal7_flag                     :1 ;	//15
	UINT32 ext_clk_valid_count                :15;	//30:16
	UINT32 ext_clk_valid                      :1 ;	//31
}PE_M17_SIZE_DETECT_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc90002d8L SIZE_DETECT_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 abnormal_in_h                      :8 ;	//7:0
	UINT32 abnormal_out_h                     :8 ;	//15:8
	UINT32 abnormal_in_v                      :8 ;	//23:16
	UINT32 abnormal_out_v                     :8 ;	//31:24
}PE_M17_SIZE_DETECT_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc90002dcL CV_OUT_MUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vsync_sel                          :2 ;	//1:0
	UINT32 hsync_sel                          :2 ;	//3:2
	UINT32 vactive_sel                        :2 ;	//5:4
	UINT32 hactive_sel                        :2 ;	//7:6
	UINT32 field_sel                          :2 ;	//9:8
	UINT32 frame_lr_sel                       :2 ;	//11:10
	UINT32 valid_sel                          :2 ;	//13:12
	UINT32 y_sel                              :3 ;	//16:14
	UINT32 cb_sel                             :3 ;	//19:17
	UINT32 cr_sel                             :3 ;	//22:20
	UINT32 auto_pseudo_sync_en                :1 ;	//23
	UINT32 ud0_even_in_sel                    :2 ;	//25:24
	UINT32 ud0_odd_in_sel                     :2 ;	//27:26
	UINT32 ud0_sync_in_sel                    :2 ;	//29:28
}PE_M17_CV_OUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc90002e0L PSEUDO_SYNC_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pseudo_sync_ctrl_en                :1 ;	//0 
	UINT32 pseudo_y_data_sel                  :1 ;	//1 
	UINT32 pseudo_cb_data_sel                 :1 ;	//2 
	UINT32 pseudo_cr_data_sel                 :1 ;	//3 
	UINT32 pseudo_hfp                         :14;	//17:4
	UINT32 pseudo_hsync                       :14;	//31:18
}PE_M17_PSEUDO_SYNC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc90002e4L PSEUDO_SYNC_CTRL2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pseudo_y                           :4 ;	//3:0
	UINT32 pseudo_hblk                        :14;	//17:4
	UINT32 pseudo_hn                          :14;	//31:18
}PE_M17_PSEUDO_SYNC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc90002e8L PSEUDO_SYNC_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pseudo_cb                          :4 ;	//3:0
	UINT32 pseudo_vfp                         :14;	//17:4
	UINT32 pseudo_vsync                       :14;	//31:18
}PE_M17_PSEUDO_SYNC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc90002ecL PSEUDO_SYNC_CTRL4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pseudo_cr                          :4 ;	//3:0
	UINT32 pseudo_vblk                        :14;	//17:4
	UINT32 pseudo_vn                          :14;	//31:18
}PE_M17_PSEUDO_SYNC_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc90002f0L SIZE_DETECT_CTRL3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 interrupt_mask_method              :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 interrupt_mask_count               :12;	//15:4
	UINT32 diff_hsize                         :14;	//29:16
}PE_M17_SIZE_DETECT_CTRL3_T;


typedef struct
{ 
	PE_M17_HDMI_MUX_CTRL_T                           hdmi_mux_ctrl;	//0x0000
	PE_M17_HDMI_420IN_CTRL_T                         hdmi_420in_ctrl;	//0x0004
	UINT32                                            reserved2[3];	//0x8-0x10
	PE_M17_HDMI_FIR_CTRL_T                           hdmi_fir_ctrl;	//0x0014
	PE_M17_HDMI_FIR_Y_COEF0_T                        hdmi_fir_y_coef0;	//0x0018
	PE_M17_HDMI_FIR_Y_COEF1_T                        hdmi_fir_y_coef1;	//0x001C
	PE_M17_HDMI_FIR_C_COEF0_T                        hdmi_fir_c_coef0;	//0x0020
	PE_M17_HDMI_FIR_C_COEF1_T                        hdmi_fir_c_coef1;	//0x0024
	UINT32                                            reserved7;	//0x28
	PE_M17_HDMI_RX_CTRL_T                            hdmi_rx_ctrl;	//0x002C
}PE_HDMI_REG_M17_T;

typedef struct
{ 
	PE_M17_TOP_CTRL_T                                top_ctrl;	//0x0000
	PE_M17_OFFSET_CTRL_T                             offset_ctrl;	//0x0004
	PE_M17_SIZE_CTRL_T                               size_ctrl;	//0x0008
	PE_M17_INT_SYNC_CTRL0_T                          int_sync_ctrl0;	//0x000C
	PE_M17_INT_SYNC_CTRL1_T                          int_sync_ctrl1;	//0x0010
	PE_M17_RESERVED000_T                             reserved000;	//0x0014
	PE_M17_RESERVED001_T                             reserved001;	//0x0018
	PE_M17_RESERVED002_T                             reserved002;	//0x001C
	PE_M17_RESERVED003_T                             reserved003;	//0x0020
	PE_M17_CSC_CTRL0_T                               csc_ctrl0;	//0x0024
	PE_M17_CSC_CTRL1_T                               csc_ctrl1;	//0x0028
	PE_M17_CSC_CTRL2_T                               csc_ctrl2;	//0x002C
	PE_M17_CSC_CTRL3_T                               csc_ctrl3;	//0x0030
	PE_M17_CSC_CTRL4_T                               csc_ctrl4;	//0x0034
	PE_M17_CSC_CTRL5_T                               csc_ctrl5;	//0x0038
	PE_M17_CSC_CTRL6_T                               csc_ctrl6;	//0x003C
	PE_M17_CSC_CTRL7_T                               csc_ctrl7;	//0x0040
	PE_M17_MISC_CTRL_T                               misc_ctrl;	//0x0044
	PE_M17_OFFSET_READ_T                             offset_read;	//0x0048
	PE_M17_PRE3D_CTRL0_T                             pre3d_ctrl0;	//0x004C
	PE_M17_PRE3D_CTRL1_T                             pre3d_ctrl1;	//0x0050
	PE_M17_PRE3D_CTRL2_T                             pre3d_ctrl2;	//0x0054
	PE_M17_SIZE_STATUS1_T                            size_status1;	//0x0058
	PE_M17_SIZE_STATUS2_T                            size_status2;	//0x005C
	PE_M17_SIZE_STATUS3_T                            size_status3;	//0x0060
	PE_M17_SIZE_STATUS4_T                            size_status4;	//0x0064
	PE_M17_PIX_SUM_CTRL0_T                           pix_sum_ctrl0;	//0x0068
	PE_M17_PIX_SUM_CTRL1_T                           pix_sum_ctrl1;	//0x006C
	PE_M17_PIX_SUM_STATUS0_T                         pix_sum_status0;	//0x0070
	PE_M17_PIX_SUM_STATUS1_T                         pix_sum_status1;	//0x0074
	PE_M17_PIX_SUM_STATUS2_T                         pix_sum_status2;	//0x0078
	PE_M17_SYNC_FIL_CTRL_T                           sync_fil_ctrl;	//0x007C
	PE_M17_SYNC_FIL_STATUS_T                         sync_fil_status;	//0x0080
	PE_M17_RESERVED004_T                             reserved004;	//0x0084
	PE_M17_RESERVED005_T                             reserved005;	//0x0088
	PE_M17_RESERVED006_T                             reserved006;	//0x008C
	PE_M17_SYNC_REPEAT_CTRL_T                        sync_repeat_ctrl;	//0x0090
	PE_M17_SYNC_REPEAT_SIZE0_T                       sync_repeat_size0;	//0x0094
	PE_M17_SYNC_REPEAT_SIZE1_T                       sync_repeat_size1;	//0x0098
	PE_M17_SYNC_REPEAT_SIZE2_T                       sync_repeat_size2;	//0x009C
	PE_M17_SYNC_REPEAT_SIZE3_T                       sync_repeat_size3;	//0x00A0
	PE_M17_SYNC_REPEAT_SIZE4_T                       sync_repeat_size4;	//0x00A4
	PE_M17_SYNC_REPEAT_SIZE5_T                       sync_repeat_size5;	//0x00A8
	PE_M17_RESERVED007_T                             reserved007;	//0x00AC
	PE_M17_RESERVED008_T                             reserved008;	//0x00B0
	PE_M17_RESERVED009_T                             reserved009;	//0x00B4
	UINT32                                            reserved46[2];	//0xb8-0xbc
	PE_M17_SIZE_DETECT_CTRL_T                        size_detect_ctrl;	//0x00C0
	PE_M17_SIZE_DETECT_READ_T                        size_detect_read;	//0x00C4
	PE_M17_SIZE_STATUS0_T                            size_status0;	//0x00C8
	PE_M17_SIZE_STATUS5_T                            size_status5;	//0x00CC
	PE_M17_SIZE_STATUS6_T                            size_status6;	//0x00D0
	PE_M17_SIZE_DETECT_CTRL1_T                       size_detect_ctrl1;	//0x00D4
	PE_M17_SIZE_DETECT_CTRL2_T                       size_detect_ctrl2;	//0x00D8
	PE_M17_CV_OUT_MUX_T                              cv_out_mux;	//0x00DC
	PE_M17_PSEUDO_SYNC_CTRL1_T                       pseudo_sync_ctrl1;	//0x00E0
	PE_M17_PSEUDO_SYNC_CTRL2_T                       pseudo_sync_ctrl2;	//0x00E4
	PE_M17_PSEUDO_SYNC_CTRL3_T                       pseudo_sync_ctrl3;	//0x00E8
	PE_M17_PSEUDO_SYNC_CTRL4_T                       pseudo_sync_ctrl4;	//0x00EC
	PE_M17_SIZE_DETECT_CTRL3_T                       size_detect_ctrl3;	//0x00F0
}PE_CVI_REG_M17_T;
#endif