#ifndef _PE_CVI_REG_O20A0_H_
#define _PE_CVI_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9000200L top_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	scan_type                          :1 ,	// 0 
	field_gen_mode                     :2 ,	// 2:1
	auto_field_gen                     :2 ,	// 4:3
	reserved                           :1 ,	// 5 
	chroma_sampling                    :1 ,	// 6 
	aspect_ratio                       :1 ,	// 7 
	yc_delay_mode_r                    :2 ,	// 9:8
	yc_delay_mode_b                    :2 ,	// 11:10
	yc_delay_mode_g                    :2 ,	// 13:12
	data_in_sel                        :4 ,	// 17:14
	reserved01                         :1 ,	// reserved
	auto_sync_polarity                 :1 ,	// 19
	manual_sync_polarity               :2 ,	// 21:20
	adc_cut_direction                  :1 ,	// 22
	adc_bit_sel                        :1 ,	// 23
	br_port_swap                       :1 ,	// 24
	r_port_swap                        :1 ,	// 25
	b_port_swap                        :1 ,	// 26
	g_port_swap                        :1 ,	// 27
	bit_numbering_lsb2                 :3 ,	// 30:28
	data_en_mode                       :1 ;	// 31
}PE_O20_TOP_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000204L offset_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	offset_h                           :13,	// 12:0
	reserved01                         :3 ,	// reserved
	offset_v                           :13;	// 28:16
}PE_O20_OFFSET_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000208L size_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	size_h                             :13,	// 12:0
	reserved01                         :3 ,	// reserved
	size_v                             :13;	// 28:16
}PE_O20_SIZE_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900020cL int_sync_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_hsync                          :10,	// 9:0
	reserved01                         :6 ,	// reserved
	res_hfp                            :10;	// 25:16
}PE_O20_INT_SYNC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9000210L int_sync_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_vfp                            :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	res_vsync                          :5 ,	// 12:8
	res_field_add_line                 :2 ,	// 14:13
	res_field_sel                      :1 ,	// 15
	res_sync_sel                       :1 ;	// 16
}PE_O20_INT_SYNC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000214L cv_mask_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mask_ext_db                        :1 ,	// 0 
	mask_ext_dg                        :1 ,	// 1 
	mask_ext_dr                        :1 ,	// 2 
	mask_ext_field                     :1 ,	// 3 
	mask_ext_hd                        :1 ,	// 4 
	mask_ext_vd                        :1 ,	// 5 
	mask_ext_de                        :1 ,	// 6 
	mask_ext                           :1 ,	// 7 
	data_mux_r                         :2 ,	// 9:8
	data_mux_b                         :2 ,	// 11:10
	data_mux_g                         :2 ,	// 13:12
	input_reverse                      :1 ,	// 14
	reserved                           :1 ,	// 15
	dither_en                          :1 ,	// 16
	dither_temporal_en                 :1 ,	// 17
	hdr_tunnel_mode                    :2 ,	// 19:18
	mask_reset_pop                     :1 ,	// 20
	mask_pop                           :1 ,	// 21
	mask_reset_push                    :1 ,	// 22
	mask_push                          :1 ,	// 23
	mask_memory                        :1 ,	// 24
	reserved01                         :3 ,	// reserved
	dolby_crc_error_intr_en            :1 ,	// 28
	dolby_crc_error_intr_clr           :1 ,	// 29
	dolby_md_intr_en                   :1 ,	// 30
	dolby_md_intr_clr                  :1 ;	// 31
}PE_O20_CV_MASK_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000218L cv_420_inctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_delay                            :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	cb_delay                           :2 ,	// 5:4
	cr_delay                           :2 ,	// 7:6
	y_swap                             :1 ,	// 8 
	c_swap                             :1 ,	// 9 
	yn1_swap                           :1 ,	// 10
	reserved02                         :1 ,	// reserved
	ctrl420_en                         :1 ,	// 12
	reserved03                         :3 ,	// reserved
	dolby_video_format                 :1 ,	// 16
	dolby_422remap_manual              :1 ,	// 17
	dolby_422remap_disable             :1 ,	// 18
	reserved04                         :1 ,	// reserved
	dolby_hs_pol                       :1 ,	// 20
	dolby_vs_pol                       :1 ,	// 21
	dolby_sdr_force                    :1 ;	// 22
}PE_O20_CV_420_INCTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900021cL cv_hdmi_md_info                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dolby_md_info;	// 31:0
}PE_O20_CV_HDMI_MD_INFO_T;
/*-----------------------------------------------------------------------------
                             0xc9000220L reserved001                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED001_T;
/*-----------------------------------------------------------------------------
                             0xc9000224L csc_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_coefficient1                   :15,	// 14:0
	reserved01                         :1 ,	// reserved
	csc_coefficient0                   :15;	// 30:16
}PE_O20_CSC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc9000228L csc_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_coefficient3                   :15,	// 14:0
	reserved01                         :1 ,	// reserved
	csc_coefficient2                   :15;	// 30:16
}PE_O20_CSC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900022cL csc_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_coefficient5                   :15,	// 14:0
	reserved01                         :1 ,	// reserved
	csc_coefficient4                   :15;	// 30:16
}PE_O20_CSC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9000230L csc_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_coefficient7                   :15,	// 14:0
	reserved01                         :1 ,	// reserved
	csc_coefficient6                   :15;	// 30:16
}PE_O20_CSC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc9000234L csc_ctrl4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_offset0                        :11,	// 10:0
	reserved01                         :5 ,	// reserved
	csc_coefficient8                   :15;	// 30:16
}PE_O20_CSC_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc9000238L csc_ctrl5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_offset2                        :11,	// 10:0
	reserved01                         :5 ,	// reserved
	csc_offset1                        :11;	// 26:16
}PE_O20_CSC_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc900023cL csc_ctrl6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_offset4                        :11,	// 10:0
	reserved01                         :5 ,	// reserved
	csc_offset3                        :11;	// 26:16
}PE_O20_CSC_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc9000240L csc_ctrl7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	csc_coeff_load                     :1 ,	// 0 
	csc_en                             :1 ,	// 1 
	reserved                           :1 ,	// 2 
	reserved01                         :13,	// reserved
	csc_offset5                        :11;	// 26:16
}PE_O20_CSC_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc9000244L misc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pattern_type                       :3 ,	// 2:0
	pattern_csc                        :1 ,	// 3 
	pattern_detail                     :4 ,	// 7:4
	reg_update_pulse                   :1 ,	// 8 
	field_fix_mode                     :2 ,	// 10:9
	black_sel                          :1 ,	// 11
	write_inhibit                      :1 ,	// 12
	sim_mode                           :1 ,	// 13
	black_off                          :1 ,	// 14
	field_edge                         :1 ,	// 15
	ha_gen                             :1 ,	// 16
	monitor_on                         :1 ,	// 17
	force_update                       :1 ,	// 18
	reserved01                         :1 ,	// reserved
	yc_delay_mode_r                    :2 ,	// 21:20
	yc_delay_mode_b                    :2 ,	// 23:22
	yc_delay_mode_g                    :2 ,	// 25:24
	field_detect_vris                  :1 ,	// 26
	reg_vcnt_reset                     :1 ,	// 27
	reg_update_position                :4 ;	// 31:28
}PE_O20_MISC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9000248L offset_read                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset_read                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	voffset_read                       :13;	// 28:16
}PE_O20_OFFSET_READ_T;
/*-----------------------------------------------------------------------------
                             0xc900024cL misc_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cv_4p_manual_en                    :1 ,	// 0 
	cv_4p_mode                         :1 ,	// 1 
	reserved                           :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	hs_bypass                          :1 ,	// 4 
	vs_bypass                          :1 ,	// 5 
	fd_bypass                          :1 ,	// 6 
	sync_bypass                        :1 ,	// 7 
	fal_sel_v                          :1 ;	// 8 
}PE_O20_MISC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000250L reserved002                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED002_T;
/*-----------------------------------------------------------------------------
                             0xc9000254L size_status7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vd_line_count_curr                 :16,	// 15:0
	vd_front_porch                     :16;	// 31:16
}PE_O20_SIZE_STATUS7_T;
/*-----------------------------------------------------------------------------
                             0xc9000258L size_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sd_hoffset_indurance_read          :8 ,	// 7:0
	sd_voffset_indurance_read          :8 ,	// 15:8
	sd_hsync_fault_flag_read           :1 ,	// 16
	sd_vsync_fault_flag_read           :1 ,	// 17
	h_sync_polarity                    :1 ,	// 18
	v_sync_polarity                    :1 ,	// 19
	field_signal                       :4 ,	// 23:20
	hsync_at_vsync_fall                :4 ,	// 27:24
	outfield_at_vactive_fall           :2 ,	// 29:28
	hoffset_over                       :1 ,	// 30
	v_offset_over                      :1 ;	// 31
}PE_O20_SIZE_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc900025cL size_status2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	de_line_size                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	de_line_count                      :13;	// 28:16
}PE_O20_SIZE_STATUS2_T;
/*-----------------------------------------------------------------------------
                             0xc9000260L size_status3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hd_sync_size                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	hd_line_size                       :13;	// 28:16
}PE_O20_SIZE_STATUS3_T;
/*-----------------------------------------------------------------------------
                             0xc9000264L size_status4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vd_sync_count                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vd_line_count                      :13;	// 28:16
}PE_O20_SIZE_STATUS4_T;
/*-----------------------------------------------------------------------------
                             0xc9000268L pix_sum_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	start_pos_x                        :13,	// 12:0
	reserved01                         :2 ,	// reserved
	pix_sum_enable                     :1 ,	// 15
	end_pos_x                          :13,	// 28:16
	field_selection                    :2 ,	// 30:29
	debug_enable                       :1 ;	// 31
}PE_O20_PIX_SUM_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900026cL pix_sum_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	start_pos_y                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	end_pos_y                          :13;	// 28:16
}PE_O20_PIX_SUM_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9000270L pix_sum_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fill_color_r                       :10,	// 9:0
	fill_color_b                       :10,	// 19:10
	fill_color_g                       :10,	// 29:20
	reserved01                         :1 ,	// reserved
	fill_en                            :1 ;	// 31
}PE_O20_PIX_SUM_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc9000274L pix_sum_status0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_g0;	// 31:0
}PE_O20_PIX_SUM_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc9000278L pix_sum_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_b0;	// 31:0
}PE_O20_PIX_SUM_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc900027cL pix_sum_status2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_r0;	// 31:0
}PE_O20_PIX_SUM_STATUS2_T;
/*-----------------------------------------------------------------------------
                             0xc9000280L pix_sum_status3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_g1;	// 31:0
}PE_O20_PIX_SUM_STATUS3_T;
/*-----------------------------------------------------------------------------
                             0xc9000284L pix_sum_status4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_b1;	// 31:0
}PE_O20_PIX_SUM_STATUS4_T;
/*-----------------------------------------------------------------------------
                             0xc9000288L pix_sum_status5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_r1;	// 31:0
}PE_O20_PIX_SUM_STATUS5_T;
/*-----------------------------------------------------------------------------
                             0xc900028cL pix_sum_status6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_g2;	// 31:0
}PE_O20_PIX_SUM_STATUS6_T;
/*-----------------------------------------------------------------------------
                             0xc9000290L pix_sum_status7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_b2;	// 31:0
}PE_O20_PIX_SUM_STATUS7_T;
/*-----------------------------------------------------------------------------
                             0xc9000294L pix_sum_status8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_r2;	// 31:0
}PE_O20_PIX_SUM_STATUS8_T;
/*-----------------------------------------------------------------------------
                             0xc9000298L pix_sum_status9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_g3;	// 31:0
}PE_O20_PIX_SUM_STATUS9_T;
/*-----------------------------------------------------------------------------
                             0xc900029cL pix_sum_statusa                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_b3;	// 31:0
}PE_O20_PIX_SUM_STATUSA_T;
/*-----------------------------------------------------------------------------
                             0xc90002a0L pix_sum_statusb                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pix_sum_r3;	// 31:0
}PE_O20_PIX_SUM_STATUSB_T;
/*-----------------------------------------------------------------------------
                             0xc90002a4L sync_fil_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync_fil_en                       :1 ,	// 0 
	hsync_counter_en                   :1 ,	// 1 
	vsync_fil_en                       :1 ,	// 2 
	vsync_counter_en                   :1 ,	// 3 
	de_fil_en                          :1 ,	// 4 
	de_counter_en                      :1 ,	// 5 
	field_fil_en                       :1 ,	// 6 
	field_counter_en                   :1 ,	// 7 
	reserved01                         :8 ,	// reserved
	line_count_sel                     :13;	// 28:16
}PE_O20_SYNC_FIL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90002a8L sync_fil_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync_coutner                      :8 ,	// 7:0
	vsync_counter                      :8 ,	// 15:8
	de_counter                         :8 ,	// 23:16
	field_counter                      :8 ;	// 31:24
}PE_O20_SYNC_FIL_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc90002acL reserved00e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED00E_T;
/*-----------------------------------------------------------------------------
                             0xc90002b0L reserved00f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED00F_T;
/*-----------------------------------------------------------------------------
                             0xc90002b4L reserved010                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED010_T;
/*-----------------------------------------------------------------------------
                             0xc90002b8L reserved011                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED011_T;
/*-----------------------------------------------------------------------------
                             0xc90002bcL reserved012                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ;	// 0 
}PE_O20_RESERVED012_T;
/*-----------------------------------------------------------------------------
                             0xc90002c0L size_detect_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sd_vd_range                        :2 ,	// 1:0
	sd_ext_range                       :2 ,	// 3:2
	intr_mask_node                     :1 ,	// 4 
	intr_mask_nohsync                  :1 ,	// 5 
	intrl_mask_novsync                 :1 ,	// 6 
	intr_mask_abnormal                 :1 ,	// 7 
	intr_mask_invalid                  :1 ,	// 8 
	intr_mask_de                       :1 ,	// 9 
	intr_mask_hsync                    :1 ,	// 10
	intr_mask_vsync                    :1 ,	// 11
	intr_mask_normal                   :1 ,	// 12
	intr_mask_valid                    :1 ,	// 13
	intr_mask_h_cnahge                 :1 ,	// 14
	sd_en                              :1 ,	// 15
	sd_frame_cnt                       :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	sd_novald_duration                 :2 ,	// 21:20
	reserved02                         :1 ,	// reserved
	sd_one_field                       :1 ,	// 23
	reserved                           :2 ,	// 25:24
	nosig_duration_de                  :2 ,	// 27:26
	nosig_duration_hsync               :2 ,	// 29:28
	nosig_duration_vsync               :2 ;	// 31:30
}PE_O20_SIZE_DETECT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90002c4L size_detect_read                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_num_read                      :16,	// 15:0
	line_width_read                    :16;	// 31:16
}PE_O20_SIZE_DETECT_READ_T;
/*-----------------------------------------------------------------------------
                             0xc90002c8L size_status0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	current_line_number_read           :12,	// 11:0
	de_signal_detect                   :1 ,	// 12
	hsync_signal_detect                :1 ,	// 13
	vsync_signal_detect                :1 ,	// 14
	source_valid                       :1 ,	// 15
	sd_line_num                        :12,	// 27:16
	field_at_vactive_fall              :4 ;	// 31:28
}PE_O20_SIZE_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc90002ccL size_status5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sd_2field_size                     :26;	// 25:0
}PE_O20_SIZE_STATUS5_T;
/*-----------------------------------------------------------------------------
                             0xc90002d0L size_status6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	diff_vd_vcnt                       :16,	// 15:0
	diff_ext_vcnt                      :12,	// 27:16
	reserved01                         :3 ,	// reserved
	vd_intr                            :1 ;	// 31
}PE_O20_SIZE_STATUS6_T;
/*-----------------------------------------------------------------------------
                             0xc90002d4L size_detect_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	abnormal0_en                       :1 ,	// 0 
	abnormal1_en                       :1 ,	// 1 
	abnormal2_en                       :1 ,	// 2 
	abnormal3_en                       :1 ,	// 3 
	abnormal4_en                       :1 ,	// 4 
	abnormal5_en                       :1 ,	// 5 
	abnormal6_en                       :1 ,	// 6 
	abnormal7_en                       :1 ,	// 7 
	abnormal0_flag                     :1 ,	// 8 
	abnormal1_flag                     :1 ,	// 9 
	abnormal2_flag                     :1 ,	// 10
	abnormal3_flag                     :1 ,	// 11
	abnormal4_flag                     :1 ,	// 12
	abnormal5_flag                     :1 ,	// 13
	abnormal6_flag                     :1 ,	// 14
	abnormal7_flag                     :1 ,	// 15
	ext_clk_valid_count                :15,	// 30:16
	ext_clk_valid                      :1 ;	// 31
}PE_O20_SIZE_DETECT_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc90002d8L size_detect_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	abnormal_in_h                      :8 ,	// 7:0
	abnormal_out_h                     :8 ,	// 15:8
	abnormal_in_v                      :8 ,	// 23:16
	abnormal_out_v                     :8 ;	// 31:24
}PE_O20_SIZE_DETECT_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc90002dcL cv_out_mux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :3 ,	// reserved
	field_sel                          :1 ,	// 3 
	hsync_sel                          :1 ,	// 4 
	vsync_sel                          :1 ,	// 5 
	de_sel                             :1 ,	// 6 
	reserved02                         :1 ,	// reserved
	cr_sel                             :1 ,	// 8 
	reserved03                         :1 ,	// reserved
	cb_sel                             :1 ,	// 10
	reserved04                         :1 ,	// reserved
	y_sel                              :1 ,	// 12
	reserved05                         :7 ,	// reserved
	c_valid_sel                        :1 ,	// 20
	reserved06                         :2 ,	// reserved
	auto_pseudo_sync_en                :1 ;	// 23
}PE_O20_CV_OUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc90002e0L pseudo_sync_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pseudo_sync_ctrl_en                :1 ,	// 0 
	pseudo_y_data_sel                  :1 ,	// 1 
	pseudo_cb_data_sel                 :1 ,	// 2 
	pseudo_cr_data_sel                 :1 ,	// 3 
	pseudo_hfp                         :14,	// 17:4
	pseudo_hsync                       :14;	// 31:18
}PE_O20_PSEUDO_SYNC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc90002e4L pseudo_sync_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pseudo_y                           :4 ,	// 3:0
	pseudo_hblk                        :14,	// 17:4
	pseudo_hn                          :14;	// 31:18
}PE_O20_PSEUDO_SYNC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc90002e8L pseudo_sync_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pseudo_cb                          :4 ,	// 3:0
	pseudo_vfp                         :14,	// 17:4
	pseudo_vsync                       :14;	// 31:18
}PE_O20_PSEUDO_SYNC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc90002ecL pseudo_sync_ctrl4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pseudo_cr                          :4 ,	// 3:0
	pseudo_vblk                        :14,	// 17:4
	pseudo_vn                          :14;	// 31:18
}PE_O20_PSEUDO_SYNC_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc90002f0L size_detect_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	interrupt_mask_method              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	interrupt_mask_count               :12,	// 15:4
	diff_hsize                         :14;	// 29:16
}PE_O20_SIZE_DETECT_CTRL3_T;


typedef struct
{ 
	PE_O20_TOP_CTRL_T                                 top_ctrl;	//0x0000
	PE_O20_OFFSET_CTRL_T                              offset_ctrl;	//0x0004
	PE_O20_SIZE_CTRL_T                                size_ctrl;	//0x0008
	PE_O20_INT_SYNC_CTRL0_T                           int_sync_ctrl0;	//0x000C
	PE_O20_INT_SYNC_CTRL1_T                           int_sync_ctrl1;	//0x0010
	PE_O20_CV_MASK_CTRL_T                             cv_mask_ctrl;	//0x0014
	PE_O20_CV_420_INCTRL_T                            cv_420_inctrl;	//0x0018
	PE_O20_CV_HDMI_MD_INFO_T                          cv_hdmi_md_info;	//0x001C
	PE_O20_RESERVED001_T                              reserved001;	//0x0020
	PE_O20_CSC_CTRL0_T                                csc_ctrl0;	//0x0024
	PE_O20_CSC_CTRL1_T                                csc_ctrl1;	//0x0028
	PE_O20_CSC_CTRL2_T                                csc_ctrl2;	//0x002C
	PE_O20_CSC_CTRL3_T                                csc_ctrl3;	//0x0030
	PE_O20_CSC_CTRL4_T                                csc_ctrl4;	//0x0034
	PE_O20_CSC_CTRL5_T                                csc_ctrl5;	//0x0038
	PE_O20_CSC_CTRL6_T                                csc_ctrl6;	//0x003C
	PE_O20_CSC_CTRL7_T                                csc_ctrl7;	//0x0040
	PE_O20_MISC_CTRL_T                                misc_ctrl;	//0x0044
	PE_O20_OFFSET_READ_T                              offset_read;	//0x0048
	PE_O20_MISC_CTRL1_T                               misc_ctrl1;	//0x004C
	PE_O20_RESERVED002_T                              reserved002;	//0x0050
	PE_O20_SIZE_STATUS7_T                             size_status7;	//0x0054
	PE_O20_SIZE_STATUS1_T                             size_status1;	//0x0058
	PE_O20_SIZE_STATUS2_T                             size_status2;	//0x005C
	PE_O20_SIZE_STATUS3_T                             size_status3;	//0x0060
	PE_O20_SIZE_STATUS4_T                             size_status4;	//0x0064
	PE_O20_PIX_SUM_CTRL0_T                            pix_sum_ctrl0;	//0x0068
	PE_O20_PIX_SUM_CTRL1_T                            pix_sum_ctrl1;	//0x006C
	PE_O20_PIX_SUM_CTRL2_T                            pix_sum_ctrl2;	//0x0070
	PE_O20_PIX_SUM_STATUS0_T                          pix_sum_status0;	//0x0074
	PE_O20_PIX_SUM_STATUS1_T                          pix_sum_status1;	//0x0078
	PE_O20_PIX_SUM_STATUS2_T                          pix_sum_status2;	//0x007C
	PE_O20_PIX_SUM_STATUS3_T                          pix_sum_status3;	//0x0080
	PE_O20_PIX_SUM_STATUS4_T                          pix_sum_status4;	//0x0084
	PE_O20_PIX_SUM_STATUS5_T                          pix_sum_status5;	//0x0088
	PE_O20_PIX_SUM_STATUS6_T                          pix_sum_status6;	//0x008C
	PE_O20_PIX_SUM_STATUS7_T                          pix_sum_status7;	//0x0090
	PE_O20_PIX_SUM_STATUS8_T                          pix_sum_status8;	//0x0094
	PE_O20_PIX_SUM_STATUS9_T                          pix_sum_status9;	//0x0098
	PE_O20_PIX_SUM_STATUSA_T                          pix_sum_statusa;	//0x009C
	PE_O20_PIX_SUM_STATUSB_T                          pix_sum_statusb;	//0x00A0
	PE_O20_SYNC_FIL_CTRL_T                            sync_fil_ctrl;	//0x00A4
	PE_O20_SYNC_FIL_STATUS_T                          sync_fil_status;	//0x00A8
	PE_O20_RESERVED00E_T                              reserved00e;	//0x00AC
	PE_O20_RESERVED00F_T                              reserved00f;	//0x00B0
	PE_O20_RESERVED010_T                              reserved010;	//0x00B4
	PE_O20_RESERVED011_T                              reserved011;	//0x00B8
	PE_O20_RESERVED012_T                              reserved012;	//0x00BC
	PE_O20_SIZE_DETECT_CTRL_T                         size_detect_ctrl;	//0x00C0
	PE_O20_SIZE_DETECT_READ_T                         size_detect_read;	//0x00C4
	PE_O20_SIZE_STATUS0_T                             size_status0;	//0x00C8
	PE_O20_SIZE_STATUS5_T                             size_status5;	//0x00CC
	PE_O20_SIZE_STATUS6_T                             size_status6;	//0x00D0
	PE_O20_SIZE_DETECT_CTRL1_T                        size_detect_ctrl1;	//0x00D4
	PE_O20_SIZE_DETECT_CTRL2_T                        size_detect_ctrl2;	//0x00D8
	PE_O20_CV_OUT_MUX_T                               cv_out_mux;	//0x00DC
	PE_O20_PSEUDO_SYNC_CTRL1_T                        pseudo_sync_ctrl1;	//0x00E0
	PE_O20_PSEUDO_SYNC_CTRL2_T                        pseudo_sync_ctrl2;	//0x00E4
	PE_O20_PSEUDO_SYNC_CTRL3_T                        pseudo_sync_ctrl3;	//0x00E8
	PE_O20_PSEUDO_SYNC_CTRL4_T                        pseudo_sync_ctrl4;	//0x00EC
	PE_O20_SIZE_DETECT_CTRL3_T                        size_detect_ctrl3;	//0x00F0
}PE_CVI_REG_O20_T;
#endif