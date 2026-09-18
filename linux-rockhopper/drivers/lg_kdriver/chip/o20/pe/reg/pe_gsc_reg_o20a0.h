#ifndef _PE_GSC_REG_O20A0_1_H_
#define _PE_GSC_REG_O20A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

/*-----------------------------------------------------------------------------
                             0xc9007500L gsc_g0_y_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_on_g0                   :1 ,	// 0 
	reg_mif_wr_on_g0                   :1 ,	// 1 
	reg_spectacle_en_g0                :1 ,	// 2 
	reg_vsc_mode_g0                    :1 ,	// 3 
	reg_adaptive_on_g0                 :1 ,	// 4 
	reg_bilinear_on_g0                 :1 ,	// 5 
	reg_th_g0                          :4 ,	// 9:6
	blending_range_g0                  :2 ,	// 11:10
	reserved01                         :13,	// reserved
	reg_v_reverse_sm_g0                :1 ,	// 25
	reserved02                         :3 ,	// reserved
	reg_blur_flag_bypass_g0            :1 ,	// 29
	reg_mode_32p_g0                    :1 ,	// 30
	reg_sampling_mode_g0               :1 ;	// 31
}PE_O20_GSC_G0_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007504L gsc_g0_y_mif_rd_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hsize_g0                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	reg_vsize_g0                       :14,	// 29:16
	reg_vinc_g0                        :2 ;	// 31:30
}PE_O20_GSC_G0_Y_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007508L gsc_g0_y_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vosize_g0                      :12;	// 27:16
}PE_O20_GSC_G0_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900750cL gsc_g0_y_min_max_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_min_max_on_l_h                 :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_min_max_th_l_h                 :9 ,	// 12:4
	adaptive_fir_h_mode                :1 ,	// 13
	reserved02                         :2 ,	// reserved
	reg_min_max_on_l_v                 :1 ,	// 16
	reserved03                         :3 ,	// reserved
	reg_min_max_th_l_v                 :9 ,	// 28:20
	adaptive_fir_v_mode                :1 ,	// 29
	reserved04                         :1 , // reserved
	reg_v_min_max_extend               :1 ;	// 31
}PE_O20_GSC_G0_Y_MIN_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007510L gsc_g0_y_input_mux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lmux_sel                           :1 ,	// 0 
	rmux_sel                           :1 ,	// 1 
	inverse_en                         :1 ,	// 2 
	l_share_en                         :1 ,	// 3 
	r_share_en                         :1 ,	// 4 
	share_flow_ctrl_en                 :1 ,	// 5 
	lmux_sel2                          :1 ,	// 6 
	rmux_sel2                          :1 ;	// 7 
}PE_O20_GSC_G0_Y_INPUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc9007514L gsc_g0_y_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hoffset_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_voffset_g0                     :12;	// 27:16
}PE_O20_GSC_G0_Y_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007518L gsc_g0_y_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hactive_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vactive_g0                     :12;	// 27:16
}PE_O20_GSC_G0_Y_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc900751cL gsc_g0_y_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_visize_g0                      :12;	// 27:16
}PE_O20_GSC_G0_Y_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007520L gsc_g0_y_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_g0                 :9 ,	// 8:0
	reserved01                         :7 , // reserved
	reg_phase_off_h_g0                 :9 ;	// 24:16
}PE_O20_GSC_G0_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9007524L gsc_g0_y_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_g0               :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_h_g0                 :13;	// 28:16
}PE_O20_GSC_G0_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc9007528L gsc_g0_y_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_g0               :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_numerator_v_g0                 :12;	// 27:16
}PE_O20_GSC_G0_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900752cL gsc_g0_y_post_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hoffset_g0                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_post_voffset_g0                :12,	// 27:16
	reserved02                         :3 , // reserved
	reg_post_crop_en_g0                :1 ;	// 31
}PE_O20_GSC_G0_Y_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007530L gsc_g0_y_post_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hactive_g0                :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_vactive_g0                :12;	// 27:16
}PE_O20_GSC_G0_Y_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc9007534L gsc_g0_y_post_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hisize_g0                 :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_visize_g0                 :12;	// 27:16
}PE_O20_GSC_G0_Y_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007538L gsc_g0_y_mif_rd_hoffset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_hoffset_g0              :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_mif_rd_voffset_g0              :12;	// 27:16
}PE_O20_GSC_G0_Y_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900753cL gsc_g0_frc_fail_timer                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_fail_timer_g0;	// 31:0
}PE_O20_GSC_G0_Y_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc9007540L gsc_g0_y_5k_8k_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_8k_detour_en                   :1 ,	// 0 
	reg_5k_scaler_en                   :1 ,	// 1 
	reserved01                         :3 ,	// reserved
	pre_filter_coef0                   :9 ,	// 13:5
	pre_filter_coef1                   :9 ,	// 22:14
	pre_filter_coef2                   :9 ;	// 31:23
}PE_O20_GSC_G0_Y_5K_8K_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007544L gsc_g0_y_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G0_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007548L gsc_g0_y_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900754cL gsc_g0_y_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007550L gsc_g0_y_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007554L gsc_g0_y_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007558L gsc_g0_y_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient9                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900755cL gsc_g0_y_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10                    :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient11                    :12;	// 27:16
}PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc9007560L gsc_g0_y_v2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G0_Y_V2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007564L gsc_g0_y_v2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007568L gsc_g0_y_v2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900756cL gsc_g0_y_v2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007570L gsc_g0_y_v2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007574L gsc_g0_y_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G0_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007578L gsc_g0_y_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900757cL gsc_g0_y_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007580L gsc_g0_y_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007584L gsc_g0_y_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007588L gsc_g0_y_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient9                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900758cL gsc_g0_y_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10                    :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient11                    :12;	// 27:16
}PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc9007590L gsc_g0_y_h2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G0_Y_H2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007594L gsc_g0_y_h2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007598L gsc_g0_y_h2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900759cL gsc_g0_y_h2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc90075a0L gsc_g0_y_h2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc90075a4L gsc_g1_y_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_on_g1                   :1 ,	// 0 
	reg_mif_wr_on_g1                   :1 ,	// 1 
	reg_spectacle_en                   :1 ,	// 2 
	reg_vsc_mode_g1                    :1 ,	// 3 
	reg_adaptive_on_g1                 :1 ,	// 4 
	reg_bilinear_on_g1                 :1 ,	// 5 
	reg_th                             :4 ,	// 9:6
	blending_range                     :2 ,	// 11:10
	reserved01                         :2 ,	// reserved
	reg_min_max_on_g1                  :1 ,	// 14
	reg_min_max_th_g1                  :10,	// 24:15
	reg_v_reverse_sm_g1                :1 ,	// 25
	reserved02                         :4 ,	// reserved
	reg_mode_32p_g1                    :1 ,	// 30
	reg_sampling_mode_g1               :1 ;	// 31
}PE_O20_GSC_G1_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90075a8L gsc_g1_y_mif_rd_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hsize_g1                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	reg_vsize_g1                       :14,	// 29:16
	reg_vinc_g1                        :2 ;	// 31:30
}PE_O20_GSC_G1_Y_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90075acL gsc_g1_y_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_g1                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vosize_g1                      :12;	// 27:16
}PE_O20_GSC_G1_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90075b8L gsc_g1_y_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hoffset_g1                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_voffset_g1                     :12;	// 27:16
}PE_O20_GSC_G1_Y_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90075bcL gsc_g1_y_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hactive_g1                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vactive_g1                     :12;	// 27:16
}PE_O20_GSC_G1_Y_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90075c0L gsc_g1_y_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_g1                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_visize_g1                      :12;	// 27:16
}PE_O20_GSC_G1_Y_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90075c4L gsc_g1_y_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_g1                 :9 ,	// 8:0
	reserved01                         :7 , // reserved
	reg_phase_off_h_g1                 :9 ;	// 24:16
}PE_O20_GSC_G1_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90075c8L gsc_g1_y_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_g1               :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_h_g1                 :13;	// 28:16
}PE_O20_GSC_G1_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc90075ccL gsc_g1_y_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_g1               :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_numerator_v_g1                 :12;	// 27:16
}PE_O20_GSC_G1_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc90075d0L gsc_g1_y_post_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hoffset_g1                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_post_voffset_g1                :12,	// 27:16
	reserved02                         :3 , // reserved
	reg_post_crop_en_g1                :1 ;	// 31
}PE_O20_GSC_G1_Y_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90075d4L gsc_g1_y_post_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hactive_g1                :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_vactive_g1                :12;	// 27:16
}PE_O20_GSC_G1_Y_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90075d8L gsc_g1_y_post_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hisize_g1                 :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_visize_g1                 :12;	// 27:16
}PE_O20_GSC_G1_Y_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90075dcL gsc_g1_y_mif_rd_hoffset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_hoffset_g1              :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_mif_rd_voffset_g1              :12;	// 27:16
}PE_O20_GSC_G1_Y_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90075e0L gsc_g1_frc_fail_timer                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_fail_timer_g1;	// 31:0
}PE_O20_GSC_G1_Y_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90075e4L gsc_g1_y_mif_prefatch_sign                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pg_mode_en                         :2 ,	// 1:0
	reserved01                         :6 ,	// reserved
	mif_prefetch_sign_lcnt             :6 ;	// 13:8
}PE_O20_GSC_G1_Y_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc90075e8L gsc_g1_y_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G1_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90075ecL gsc_g1_y_v1_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc90075f0L gsc_g1_y_v1_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc90075f4L gsc_g1_y_v1_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc90075f8L gsc_g1_y_v1_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007618L gsc_g1_y_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G1_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900761cL gsc_g1_y_h1_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007620L gsc_g1_y_h1_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007624L gsc_g1_y_h1_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007628L gsc_g1_y_h1_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc90076e0L gsc_g0_vcnt_out                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_out_g0                        :12;	// 11:0
}PE_O20_GSC_G0_Y_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90076e4L gsc_g1_vcnt_out                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_out_g1                        :12;	// 11:0
}PE_O20_GSC_G1_Y_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90076e8L gsc_g0_fmc_timer_cnt                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fmc_timer_g0;	// 31:0
}PE_O20_GSC_G0_Y_FMC_TIMER_CNT_T;
/*-----------------------------------------------------------------------------
                             0xc90076ecL gsc_g0_vcnt_in                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_in_g0                         :12;	// 11:0
}PE_O20_GSC_G0_Y_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90076f0L gsc_g1_vcnt_in                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_in_g1                         :12;	// 11:0
}PE_O20_GSC_G1_Y_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90076f4L gsc_g1_fmc_timer_cnt                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fmc_timer_g1;	// 31:0
}PE_O20_GSC_G1_Y_FMC_TIMER_CNT_T;

/*-----------------------------------------------------------------------------
                             0xc9007700L gsc_g0_c_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_on_g0                   :1 ,	// 0 
	reg_mif_wr_on_g0                   :1 ,	// 1 
	reg_spectacle_en                   :1 ,	// 2 
	reg_vsc_mode_g0                    :2 ,	// 4:3
	reg_bilinear_on_g0                 :1 ,	// 5 
	reg_mode_32p_g0                    :1 ,	// 6 
	reserved01                         :7 ,	// reserved
	reg_min_max_on_g0                  :1 ,	// 14
	reg_min_max_th_g0                  :10,	// 24:15
	reg_v_reverse_g0                   :1 ,	// 25
	reserved02                         :1 ,	// reserved
	reg_min_max_on_h_g0                :1 ,	// 27
	reg_v_cti_en_g0                    :1 ,	// 28
	reg_v_cti_ratio_g0                 :2 ,	// 30:29
	reg_sampling_mode_g0               :1 ;	// 31
}PE_O20_GSC_G0_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007704L gsc_g0_c_mif_rd_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hsize_g0                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	reg_vsize_g0                       :14,	// 29:16
	reg_vinc_g0                        :2 ;	// 31:30
}PE_O20_GSC_G0_C_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007708L gsc_g0_c_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vosize_g0                      :12;	// 27:16
}PE_O20_GSC_G0_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007710L gsc_g0_c_input_mux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lmux_sel                           :1 ,	// 0 
	rmux_sel                           :1 ,	// 1 
	inverse_en                         :1 ,	// 2 
	l_share_en                         :1 ,	// 3 
	r_share_en                         :1 ,	// 4 
	share_flow_ctrl_en                 :1 ,	// 5 
	lmux_sel2                          :1 ,	// 6 
	rmux_sel2                          :1 ;	// 7 
}PE_O20_GSC_G0_C_INPUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc9007714L gsc_g0_c_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hoffset_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_voffset_g0                     :12;	// 27:16
}PE_O20_GSC_G0_C_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007718L gsc_g0_c_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hactive_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vactive_g0                     :12;	// 27:16
}PE_O20_GSC_G0_C_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc900771cL gsc_g0_c_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_visize_g0                      :12;	// 27:16
}PE_O20_GSC_G0_C_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007720L gsc_g0_c_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_g0                 :9 ,	// 8:0
	reserved01                         :7 , // reserved
	reg_phase_off_h_g0                 :9 ;	// 24:16
}PE_O20_GSC_G0_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9007724L gsc_g0_c_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_g0               :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_h_g0                 :13;	// 28:16
}PE_O20_GSC_G0_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc9007728L gsc_g0_c_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_g0               :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_numerator_v_g0                 :12;	// 27:16
}PE_O20_GSC_G0_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900772cL gsc_g0_c_post_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hoffset_g0                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_post_voffset_g0                :12,	// 27:16
	reserved02                         :3 , // reserved
	reg_post_crop_en_g0                :1 ;	// 31
}PE_O20_GSC_G0_C_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007730L gsc_g0_c_post_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hactive_g0                :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_vactive_g0                :12;	// 27:16
}PE_O20_GSC_G0_C_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc9007734L gsc_g0_c_post_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hisize_g0                 :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_visize_g0                 :12;	// 27:16
}PE_O20_GSC_G0_C_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007738L gsc_g0_c_mif_rd_hoffset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_hoffset_g0              :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_mif_rd_voffset_g0              :12;	// 27:16
}PE_O20_GSC_G0_C_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900773cL gsc_g0_frc_fail_timer                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_fail_timer_g0;	// 31:0
}PE_O20_GSC_G0_C_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc9007740L gsc_g0_c_5k_8k_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_8k_detour_en                   :1 ,	// 0 
	reg_5k_scaler_en                   :1 ,	// 1 
	reserved01                         :3 ,	// reserved
	pre_filter_coef0                   :9 ,	// 13:5
	pre_filter_coef1                   :9 ,	// 22:14
	pre_filter_coef2                   :9 ;	// 31:23
}PE_O20_GSC_G0_C_5K_8K_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007744L gsc_g0_c_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G0_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007748L gsc_g0_c_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v1                  :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900774cL gsc_g0_c_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v1                  :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007750L gsc_g0_c_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v1                  :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007754L gsc_g0_c_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v1                  :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007758L gsc_g0_c_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_v1                  :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900775cL gsc_g0_c_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_v1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_v1                 :12;	// 27:16
}PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc9007774L gsc_g0_c_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h1                          :1 ,	// 0:0
	rnw_h1                             :1 ,	// 1:1
	addr_h1                            :8 ;	// 9:2
}PE_O20_GSC_G0_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007778L gsc_g0_c_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h1                  :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900777cL gsc_g0_c_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h1                  :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007780L gsc_g0_c_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h1                  :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007784L gsc_g0_c_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h1                  :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007788L gsc_g0_c_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_h1                  :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900778cL gsc_g0_c_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_h1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_h1                 :12;	// 27:16
}PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc90077a4L gsc_g1_c_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_on_g1                   :1 ,	// 0 
	reg_mif_wr_on_g1                   :1 ,	// 1 
	reg_spectacle_en                   :1 ,	// 2 
	reg_vsc_mode_g1                    :2 ,	// 4:3
	reg_bilinear_on_g1                 :1 ,	// 5 
	reg_mode_32p_g1                    :1 ,	// 6 
	reserved01                         :7 ,	// reserved
	reg_min_max_on_g1                  :1 ,	// 14
	reg_min_max_th_g1                  :10,	// 24:15
	reg_v_reverse_g1                   :1 ,	// 25
	reserved02                         :1 ,	// reserved
	reg_min_max_on_h_g1                :1 ,	// 27
	reg_v_cti_en_g1                    :1 ,	// 28
	reg_v_cti_ratio_g1                 :2 ,	// 30:29
	reg_sampling_mode_g1               :1 ;	// 31
}PE_O20_GSC_G1_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90077a8L gsc_g1_c_mif_rd_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hsize_g1                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	reg_vsize_g1                       :14,	// 29:16
	reg_vinc_g1                        :2 ;	// 31:30
}PE_O20_GSC_G1_C_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90077acL gsc_g1_c_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_g1                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vosize_g1                      :12;	// 27:16
}PE_O20_GSC_G1_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90077b0L gsc_g1_c_canvas_write                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_canvas_xoffset_g1              :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_canvas_yoffset_g1              :11;	// 26:16
}PE_O20_GSC_G1_C_CANVAS_WRITE_T;
/*-----------------------------------------------------------------------------
                             0xc90077b4L gsc_g1_c_merge_param                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_active_merge_g1                :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_overlap_merge_g1               :13;	// 28:16
}PE_O20_GSC_G1_C_MERGE_PARAM_T;
/*-----------------------------------------------------------------------------
                             0xc90077b8L gsc_g1_c_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hoffset_g1                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_voffset_g1                     :12;	// 27:16
}PE_O20_GSC_G1_C_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90077bcL gsc_g1_c_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hactive_g1                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vactive_g1                     :12;	// 27:16
}PE_O20_GSC_G1_C_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90077c0L gsc_g1_c_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_g1                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_visize_g1                      :12;	// 27:16
}PE_O20_GSC_G1_C_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90077c4L gsc_g1_c_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_g1                 :9 ,	// 8:0
	reserved01                         :7 , // reserved
	reg_phase_off_h_g1                 :9 ;	// 24:16
}PE_O20_GSC_G1_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90077c8L gsc_g1_c_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_g1               :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_h_g1                 :13;	// 28:16
}PE_O20_GSC_G1_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc90077ccL gsc_g1_c_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_g1               :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_numerator_v_g1                 :12;	// 27:16
}PE_O20_GSC_G1_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc90077d0L gsc_g1_c_post_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hoffset_g1                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_post_voffset_g1                :12,	// 27:16
	reserved02                         :3 , // reserved
	reg_post_crop_en_g1                :1 ;	// 31
}PE_O20_GSC_G1_C_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90077d4L gsc_g1_c_post_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hactive_g1                :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_vactive_g1                :12;	// 27:16
}PE_O20_GSC_G1_C_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90077d8L gsc_g1_c_post_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post_hisize_g1                 :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_post_visize_g1                 :12;	// 27:16
}PE_O20_GSC_G1_C_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90077dcL gsc_g1_c_mif_rd_hoffset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_hoffset_g1              :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_mif_rd_voffset_g1              :12;	// 27:16
}PE_O20_GSC_G1_C_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90077e0L gsc_g1_frc_fail_timer                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_frc_fail_timer_g1;	// 31:0
}PE_O20_GSC_G1_C_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90077e4L gsc_g1_c_mif_prefatch_sign                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pg_mode_en                         :2 ,	// 1:0
	reserved01                         :6 ,	// reserved
	mif_prefetch_sign_lcnt             :6 ;	// 13:8
}PE_O20_GSC_G1_C_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc90077e8L gsc_g1_c_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G1_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90077ecL gsc_g1_c_v1_c_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	c_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G1_C_V1_C_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc90077f0L gsc_g1_c_v1_c_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	c_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G1_C_V1_C_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007818L gsc_g1_c_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O20_GSC_G1_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900781cL gsc_g1_c_h1_c_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	c_coefficient1                     :12;	// 27:16
}PE_O20_GSC_G1_C_H1_C_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007820L gsc_g1_c_h1_c_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	c_coefficient3                     :12;	// 27:16
}PE_O20_GSC_G1_C_H1_C_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc90078e0L gsc_g0_vcnt_out                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_out_g0                        :12;	// 11:0
}PE_O20_GSC_G0_C_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90078e4L gsc_g1_vcnt_out                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_out_g1                        :12;	// 11:0
}PE_O20_GSC_G1_C_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90078e8L gsc_g0_fmc_timer_cnt                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fmc_timer_g0;	// 31:0
}PE_O20_GSC_G0_C_FMC_TIMER_CNT_T;
/*-----------------------------------------------------------------------------
                             0xc90078ecL gsc_g0_vcnt_in                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_in_g0                         :12;	// 11:0
}PE_O20_GSC_G0_C_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90078f0L gsc_g1_vcnt_in                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_in_g1                         :12;	// 11:0
}PE_O20_GSC_G1_C_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90078f4L gsc_g1_fmc_timer_cnt                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fmc_timer_g1;	// 31:0
}PE_O20_GSC_G1_C_FMC_TIMER_CNT_T;


typedef struct
{ 
	PE_O20_GSC_G0_Y_CTRL_T                            gsc_g0_y_ctrl;	//0x0000
	PE_O20_GSC_G0_Y_MIF_RD_SIZE_T                     gsc_g0_y_mif_rd_size;	//0x0004
	PE_O20_GSC_G0_Y_OUTSIZE_T                         gsc_g0_y_outsize;	//0x0008
	PE_O20_GSC_G0_Y_MIN_MAX_CTRL_T                    gsc_g0_y_min_max_ctrl;	//0x000C
	PE_O20_GSC_G0_Y_INPUT_MUX_T                       gsc_g0_y_input_mux;	//0x0010
	PE_O20_GSC_G0_Y_CROP_PARAM1_T                     gsc_g0_y_crop_param1;	//0x0014
	PE_O20_GSC_G0_Y_CROP_PARAM2_T                     gsc_g0_y_crop_param2;	//0x0018
	PE_O20_GSC_G0_Y_CROP_PARAM3_T                     gsc_g0_y_crop_param3;	//0x001C
	PE_O20_GSC_G0_Y_PHASE_OFFSET_T                    gsc_g0_y_phase_offset;	//0x0020
	PE_O20_GSC_G0_Y_SAMPLING_H_T                      gsc_g0_y_sampling_h;	//0x0024
	PE_O20_GSC_G0_Y_SAMPLING_V_T                      gsc_g0_y_sampling_v;	//0x0028
	PE_O20_GSC_G0_Y_POST_CROP_PARAM1_T                gsc_g0_y_post_crop_param1;	//0x002C
	PE_O20_GSC_G0_Y_POST_CROP_PARAM2_T                gsc_g0_y_post_crop_param2;	//0x0030
	PE_O20_GSC_G0_Y_POST_CROP_PARAM3_T                gsc_g0_y_post_crop_param3;	//0x0034
	PE_O20_GSC_G0_Y_MIF_RD_HOFFSET_T                  gsc_g0_y_mif_rd_hoffset;	//0x0038
	PE_O20_GSC_G0_Y_FRC_FAIL_TIMER_T                    gsc_g0_frc_fail_timer;	//0x003C
	PE_O20_GSC_G0_Y_5K_8K_CTRL_T                      gsc_g0_y_5k_8k_ctrl;	//0x0040
	PE_O20_GSC_G0_Y_V1_FIR_COEF_CTRL_T                gsc_g0_y_v1_fir_coef_ctrl;	//0x0044
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T             gsc_g0_y_v1_y_fir_coef_data0;	//0x0048
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T             gsc_g0_y_v1_y_fir_coef_data1;	//0x004C
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T             gsc_g0_y_v1_y_fir_coef_data2;	//0x0050
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T             gsc_g0_y_v1_y_fir_coef_data3;	//0x0054
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T             gsc_g0_y_v1_y_fir_coef_data4;	//0x0058
	PE_O20_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T             gsc_g0_y_v1_y_fir_coef_data5;	//0x005C
	PE_O20_GSC_G0_Y_V2_FIR_COEF_CTRL_T                gsc_g0_y_v2_fir_coef_ctrl;	//0x0060
	PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T             gsc_g0_y_v2_y_fir_coef_data0;	//0x0064
	PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T             gsc_g0_y_v2_y_fir_coef_data1;	//0x0068
	PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T             gsc_g0_y_v2_y_fir_coef_data2;	//0x006C
	PE_O20_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T             gsc_g0_y_v2_y_fir_coef_data3;	//0x0070
	PE_O20_GSC_G0_Y_H1_FIR_COEF_CTRL_T                gsc_g0_y_h1_fir_coef_ctrl;	//0x0074
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T             gsc_g0_y_h1_y_fir_coef_data0;	//0x0078
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T             gsc_g0_y_h1_y_fir_coef_data1;	//0x007C
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T             gsc_g0_y_h1_y_fir_coef_data2;	//0x0080
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T             gsc_g0_y_h1_y_fir_coef_data3;	//0x0084
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T             gsc_g0_y_h1_y_fir_coef_data4;	//0x0088
	PE_O20_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T             gsc_g0_y_h1_y_fir_coef_data5;	//0x008C
	PE_O20_GSC_G0_Y_H2_FIR_COEF_CTRL_T                gsc_g0_y_h2_fir_coef_ctrl;	//0x0090
	PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T             gsc_g0_y_h2_y_fir_coef_data0;	//0x0094
	PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T             gsc_g0_y_h2_y_fir_coef_data1;	//0x0098
	PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T             gsc_g0_y_h2_y_fir_coef_data2;	//0x009C
	PE_O20_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T             gsc_g0_y_h2_y_fir_coef_data3;	//0x00A0
	PE_O20_GSC_G1_Y_CTRL_T                            gsc_g1_y_ctrl;	//0x00A4
	PE_O20_GSC_G1_Y_MIF_RD_SIZE_T                     gsc_g1_y_mif_rd_size;	//0x00A8
	PE_O20_GSC_G1_Y_OUTSIZE_T                         gsc_g1_y_outsize;	//0x00AC
	UINT32                                            reserved44[2];	//0xb0-0xb4
	PE_O20_GSC_G1_Y_CROP_PARAM1_T                     gsc_g1_y_crop_param1;	//0x00B8
	PE_O20_GSC_G1_Y_CROP_PARAM2_T                     gsc_g1_y_crop_param2;	//0x00BC
	PE_O20_GSC_G1_Y_CROP_PARAM3_T                     gsc_g1_y_crop_param3;	//0x00C0
	PE_O20_GSC_G1_Y_PHASE_OFFSET_T                    gsc_g1_y_phase_offset;	//0x00C4
	PE_O20_GSC_G1_Y_SAMPLING_H_T                      gsc_g1_y_sampling_h;	//0x00C8
	PE_O20_GSC_G1_Y_SAMPLING_V_T                      gsc_g1_y_sampling_v;	//0x00CC
	PE_O20_GSC_G1_Y_POST_CROP_PARAM1_T                gsc_g1_y_post_crop_param1;	//0x00D0
	PE_O20_GSC_G1_Y_POST_CROP_PARAM2_T                gsc_g1_y_post_crop_param2;	//0x00D4
	PE_O20_GSC_G1_Y_POST_CROP_PARAM3_T                gsc_g1_y_post_crop_param3;	//0x00D8
	PE_O20_GSC_G1_Y_MIF_RD_HOFFSET_T                  gsc_g1_y_mif_rd_hoffset;	//0x00DC
	PE_O20_GSC_G1_Y_FRC_FAIL_TIMER_T                    gsc_g1_frc_fail_timer;	//0x00E0
	PE_O20_GSC_G1_Y_MIF_PREFATCH_SIGN_T               gsc_g1_y_mif_prefatch_sign;	//0x00E4
	PE_O20_GSC_G1_Y_V1_FIR_COEF_CTRL_T                gsc_g1_y_v1_fir_coef_ctrl;	//0x00E8
	PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA0_T               gsc_g1_y_v1_fir_coef_data0;	//0x00EC
	PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA1_T               gsc_g1_y_v1_fir_coef_data1;	//0x00F0
	PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA2_T               gsc_g1_y_v1_fir_coef_data2;	//0x00F4
	PE_O20_GSC_G1_Y_V1_FIR_COEF_DATA3_T               gsc_g1_y_v1_fir_coef_data3;	//0x00F8
	UINT32                                            reserved61[7];	//0xfc-0x114
	PE_O20_GSC_G1_Y_H1_FIR_COEF_CTRL_T                gsc_g1_y_h1_fir_coef_ctrl;	//0x0118
	PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA0_T               gsc_g1_y_h1_fir_coef_data0;	//0x011C
	PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA1_T               gsc_g1_y_h1_fir_coef_data1;	//0x0120
	PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA2_T               gsc_g1_y_h1_fir_coef_data2;	//0x0124
	PE_O20_GSC_G1_Y_H1_FIR_COEF_DATA3_T               gsc_g1_y_h1_fir_coef_data3;	//0x0128
	UINT32                                            reserved66[45];	//0x12c-0x1dc
	PE_O20_GSC_G0_Y_VCNT_OUT_T                          gsc_g0_vcnt_out;	//0x01E0
	PE_O20_GSC_G1_Y_VCNT_OUT_T                          gsc_g1_vcnt_out;	//0x01E4
	PE_O20_GSC_G0_Y_FMC_TIMER_CNT_T                     gsc_g0_fmc_timer_cnt;	//0x01E8
	PE_O20_GSC_G0_Y_VCNT_IN_T                           gsc_g0_vcnt_in;	//0x01EC
	PE_O20_GSC_G1_Y_VCNT_IN_T                           gsc_g1_vcnt_in;	//0x01F0
	PE_O20_GSC_G1_Y_FMC_TIMER_CNT_T                     gsc_g1_fmc_timer_cnt;	//0x01F4
}PE_GSC_Y_REG_O20_T;

typedef struct
{ 
	PE_O20_GSC_G0_C_CTRL_T                            gsc_g0_c_ctrl;	//0x0000
	PE_O20_GSC_G0_C_MIF_RD_SIZE_T                     gsc_g0_c_mif_rd_size;	//0x0004
	PE_O20_GSC_G0_C_OUTSIZE_T                         gsc_g0_c_outsize;	//0x0008
	UINT32                                            reserved3;	//0xc
	PE_O20_GSC_G0_C_INPUT_MUX_T                       gsc_g0_c_input_mux;	//0x0010
	PE_O20_GSC_G0_C_CROP_PARAM1_T                     gsc_g0_c_crop_param1;	//0x0014
	PE_O20_GSC_G0_C_CROP_PARAM2_T                     gsc_g0_c_crop_param2;	//0x0018
	PE_O20_GSC_G0_C_CROP_PARAM3_T                     gsc_g0_c_crop_param3;	//0x001C
	PE_O20_GSC_G0_C_PHASE_OFFSET_T                    gsc_g0_c_phase_offset;	//0x0020
	PE_O20_GSC_G0_C_SAMPLING_H_T                      gsc_g0_c_sampling_h;	//0x0024
	PE_O20_GSC_G0_C_SAMPLING_V_T                      gsc_g0_c_sampling_v;	//0x0028
	PE_O20_GSC_G0_C_POST_CROP_PARAM1_T                gsc_g0_c_post_crop_param1;	//0x002C
	PE_O20_GSC_G0_C_POST_CROP_PARAM2_T                gsc_g0_c_post_crop_param2;	//0x0030
	PE_O20_GSC_G0_C_POST_CROP_PARAM3_T                gsc_g0_c_post_crop_param3;	//0x0034
	PE_O20_GSC_G0_C_MIF_RD_HOFFSET_T                  gsc_g0_c_mif_rd_hoffset;	//0x0038
	PE_O20_GSC_G0_C_FRC_FAIL_TIMER_T                    gsc_g0_frc_fail_timer;	//0x003C
	PE_O20_GSC_G0_C_5K_8K_CTRL_T                      gsc_g0_c_5k_8k_ctrl;	//0x0040
	PE_O20_GSC_G0_C_V1_FIR_COEF_CTRL_T                gsc_g0_c_v1_fir_coef_ctrl;	//0x0044
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T             gsc_g0_c_v1_y_fir_coef_data0;	//0x0048
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T             gsc_g0_c_v1_y_fir_coef_data1;	//0x004C
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T             gsc_g0_c_v1_y_fir_coef_data2;	//0x0050
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T             gsc_g0_c_v1_y_fir_coef_data3;	//0x0054
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T             gsc_g0_c_v1_y_fir_coef_data4;	//0x0058
	PE_O20_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T             gsc_g0_c_v1_y_fir_coef_data5;	//0x005C
	UINT32                                            reserved23[5];	//0x60-0x70
	PE_O20_GSC_G0_C_H1_FIR_COEF_CTRL_T                gsc_g0_c_h1_fir_coef_ctrl;	//0x0074
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T             gsc_g0_c_h1_y_fir_coef_data0;	//0x0078
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T             gsc_g0_c_h1_y_fir_coef_data1;	//0x007C
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T             gsc_g0_c_h1_y_fir_coef_data2;	//0x0080
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T             gsc_g0_c_h1_y_fir_coef_data3;	//0x0084
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T             gsc_g0_c_h1_y_fir_coef_data4;	//0x0088
	PE_O20_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T             gsc_g0_c_h1_y_fir_coef_data5;	//0x008C
	UINT32                                            reserved30[5];	//0x90-0xa0
	PE_O20_GSC_G1_C_CTRL_T                            gsc_g1_c_ctrl;	//0x00A4
	PE_O20_GSC_G1_C_MIF_RD_SIZE_T                     gsc_g1_c_mif_rd_size;	//0x00A8
	PE_O20_GSC_G1_C_OUTSIZE_T                         gsc_g1_c_outsize;	//0x00AC
	PE_O20_GSC_G1_C_CANVAS_WRITE_T                    gsc_g1_c_canvas_write;	//0x00B0
	PE_O20_GSC_G1_C_MERGE_PARAM_T                     gsc_g1_c_merge_param;	//0x00B4
	PE_O20_GSC_G1_C_CROP_PARAM1_T                     gsc_g1_c_crop_param1;	//0x00B8
	PE_O20_GSC_G1_C_CROP_PARAM2_T                     gsc_g1_c_crop_param2;	//0x00BC
	PE_O20_GSC_G1_C_CROP_PARAM3_T                     gsc_g1_c_crop_param3;	//0x00C0
	PE_O20_GSC_G1_C_PHASE_OFFSET_T                    gsc_g1_c_phase_offset;	//0x00C4
	PE_O20_GSC_G1_C_SAMPLING_H_T                      gsc_g1_c_sampling_h;	//0x00C8
	PE_O20_GSC_G1_C_SAMPLING_V_T                      gsc_g1_c_sampling_v;	//0x00CC
	PE_O20_GSC_G1_C_POST_CROP_PARAM1_T                gsc_g1_c_post_crop_param1;	//0x00D0
	PE_O20_GSC_G1_C_POST_CROP_PARAM2_T                gsc_g1_c_post_crop_param2;	//0x00D4
	PE_O20_GSC_G1_C_POST_CROP_PARAM3_T                gsc_g1_c_post_crop_param3;	//0x00D8
	PE_O20_GSC_G1_C_MIF_RD_HOFFSET_T                  gsc_g1_c_mif_rd_hoffset;	//0x00DC
	PE_O20_GSC_G1_C_FRC_FAIL_TIMER_T                    gsc_g1_frc_fail_timer;	//0x00E0
	PE_O20_GSC_G1_C_MIF_PREFATCH_SIGN_T               gsc_g1_c_mif_prefatch_sign;	//0x00E4
	PE_O20_GSC_G1_C_V1_FIR_COEF_CTRL_T                gsc_g1_c_v1_fir_coef_ctrl;	//0x00E8
	PE_O20_GSC_G1_C_V1_C_FIR_COEF_DATA0_T             gsc_g1_c_v1_c_fir_coef_data0;	//0x00EC
	PE_O20_GSC_G1_C_V1_C_FIR_COEF_DATA1_T             gsc_g1_c_v1_c_fir_coef_data1;	//0x00F0
	UINT32                                            reserved50[9];	//0xf4-0x114
	PE_O20_GSC_G1_C_H1_FIR_COEF_CTRL_T                gsc_g1_c_h1_fir_coef_ctrl;	//0x0118
	PE_O20_GSC_G1_C_H1_C_FIR_COEF_DATA0_T             gsc_g1_c_h1_c_fir_coef_data0;	//0x011C
	PE_O20_GSC_G1_C_H1_C_FIR_COEF_DATA1_T             gsc_g1_c_h1_c_fir_coef_data1;	//0x0120
	UINT32                                            reserved53[47];	//0x124-0x1dc
	PE_O20_GSC_G0_C_VCNT_OUT_T                          gsc_g0_vcnt_out;	//0x01E0
	PE_O20_GSC_G1_C_VCNT_OUT_T                          gsc_g1_vcnt_out;	//0x01E4
	PE_O20_GSC_G0_C_FMC_TIMER_CNT_T                     gsc_g0_fmc_timer_cnt;	//0x01E8
	PE_O20_GSC_G0_C_VCNT_IN_T                           gsc_g0_vcnt_in;	//0x01EC
	PE_O20_GSC_G1_C_VCNT_IN_T                           gsc_g1_vcnt_in;	//0x01F0
	PE_O20_GSC_G1_C_FMC_TIMER_CNT_T                     gsc_g1_fmc_timer_cnt;	//0x01F4
}PE_GSC_C_REG_O20_T;
#endif