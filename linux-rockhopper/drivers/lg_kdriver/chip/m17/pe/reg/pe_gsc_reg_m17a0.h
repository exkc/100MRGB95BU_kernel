#ifndef _PE_GSC_REG_M17A0_H_
#define _PE_GSC_REG_M17A0_H_
/*-----------------------------------------------------------------------------
                             0xc9007500L GSC_G0_Y_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_on_g0                   :1 ;	//0 
	UINT32 reg_mif_wr_on_g0                   :1 ;	//1 
	UINT32 reg_spectacle_en                   :1 ;	//2 
	UINT32 reg_vsc_mode_g0                    :1 ;	//3 
	UINT32 reg_adaptive_on_g0                 :1 ;	//4 
	UINT32 reg_bilinear_on_g0                 :1 ;	//5 
	UINT32 reg_th                             :4 ;	//9:6
	UINT32 blending_range                     :2 ;	//11:10
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_min_max_on_g0                  :1 ;	//14
	UINT32 reg_min_max_th_g0                  :10;	//24:15
	UINT32 reg_v_reverse_sm_g0                :1 ;	//25
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 reg_mode_32p_g0                    :1 ;	//30
	UINT32 reg_sampling_mode_g0               :1 ;	//31
}PE_M17_GSC_G0_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007504L GSC_G0_Y_MIF_RD_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hsize_g0                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vsize_g0                       :12;	//27:16
	UINT32 reg_vinc_g0                        :4 ;	//31:28
}PE_M17_GSC_G0_Y_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007508L GSC_G0_Y_OUTSIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hosize_g0                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vosize_g0                      :12;	//27:16
}PE_M17_GSC_G0_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007510L GSC_G0_Y_INPUT_MUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 lmux_sel                           :1 ;	//0 
	UINT32 rmux_sel                           :1 ;	//1 
	UINT32 inverse_en                         :1 ;	//2 
	UINT32 l_share_en                         :1 ;	//3 
	UINT32 r_share_en                         :1 ;	//4 
	UINT32 share_flow_ctrl_en                 :1 ;	//5 
	UINT32 lmux_sel2                          :1 ;	//6 
	UINT32 rmux_sel2                          :1 ;	//7 
}PE_M17_GSC_G0_Y_INPUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc9007514L GSC_G0_Y_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hoffset_g0                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_voffset_g0                     :12;	//27:16
}PE_M17_GSC_G0_Y_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007518L GSC_G0_Y_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hactive_g0                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vactive_g0                     :12;	//27:16
}PE_M17_GSC_G0_Y_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc900751cL GSC_G0_Y_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hisize_g0                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_visize_g0                      :12;	//27:16
}PE_M17_GSC_G0_Y_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007520L GSC_G0_Y_PHASE_OFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_phase_off_v_g0                 :9 ;	//8:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_phase_off_h_g0                 :9 ;	//24:16
}PE_M17_GSC_G0_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9007524L GSC_G0_Y_SAMPLING_H                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_h_g0               :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_numerator_h_g0                 :13;	//28:16
}PE_M17_GSC_G0_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc9007528L GSC_G0_Y_SAMPLING_V                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_v_g0               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_numerator_v_g0                 :12;	//27:16
}PE_M17_GSC_G0_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900752cL GSC_G0_Y_POST_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hoffset_g0                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_voffset_g0                :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_post_crop_en_g0                :1 ;	//31
}PE_M17_GSC_G0_Y_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007530L GSC_G0_Y_POST_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hactive_g0                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_vactive_g0                :12;	//27:16
}PE_M17_GSC_G0_Y_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc9007534L GSC_G0_Y_POST_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hisize_g0                 :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_visize_g0                 :12;	//27:16
}PE_M17_GSC_G0_Y_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007538L GSC_G0_Y_MIF_RD_HOFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_hoffset_g0              :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_mif_rd_voffset_g0              :12;	//27:16
}PE_M17_GSC_G0_Y_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900753cL GSC_G0_FRC_FAIL_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_frc_fail_timer_g0              :32;	//31:0
}PE_M17_GSC_G0_Y_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc9007540L GSC_G0_Y_MIF_PREFATCH_SIGN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pg_mode_en                         :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 mif_prefetch_sign_lcnt             :6 ;	//13:8
}PE_M17_GSC_G0_Y_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc9007544L GSC_G0_Y_V1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G0_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007548L GSC_G0_Y_V1_Y_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient1                     :12;	//27:16
}PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900754cL GSC_G0_Y_V1_Y_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient3                     :12;	//27:16
}PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007550L GSC_G0_Y_V1_Y_FIR_COEF_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient4                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient5                     :12;	//27:16
}PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007554L GSC_G0_Y_V1_Y_FIR_COEF_DATA3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient6                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient7                     :12;	//27:16
}PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007574L GSC_G0_Y_H1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G0_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007578L GSC_G0_Y_H1_Y_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient1                     :12;	//27:16
}PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900757cL GSC_G0_Y_H1_Y_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient3                     :12;	//27:16
}PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007580L GSC_G0_Y_H1_Y_FIR_COEF_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient4                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient5                     :12;	//27:16
}PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007584L GSC_G0_Y_H1_Y_FIR_COEF_DATA3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient6                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient7                     :12;	//27:16
}PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc90075a4L GSC_G1_Y_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_on_g1                   :1 ;	//0 
	UINT32 reg_mif_wr_on_g1                   :1 ;	//1 
	UINT32 reg_spectacle_en                   :1 ;	//2 
	UINT32 reg_vsc_mode_g1                    :1 ;	//3 
	UINT32 reg_adaptive_on_g1                 :1 ;	//4 
	UINT32 reg_bilinear_on_g1                 :1 ;	//5 
	UINT32 reg_th                             :4 ;	//9:6
	UINT32 blending_range                     :2 ;	//11:10
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_min_max_on_g1                  :1 ;	//14
	UINT32 reg_min_max_th_g1                  :10;	//24:15
	UINT32 reg_v_reverse_sm_g1                :1 ;	//25
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 reg_mode_32p_g1                    :1 ;	//30
	UINT32 reg_sampling_mode_g1               :1 ;	//31
}PE_M17_GSC_G1_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90075a8L GSC_G1_Y_MIF_RD_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hsize_g1                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vsize_g1                       :12;	//27:16
	UINT32 reg_vinc_g1                        :4 ;	//31:28
}PE_M17_GSC_G1_Y_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90075acL GSC_G1_Y_OUTSIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hosize_g1                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vosize_g1                      :12;	//27:16
}PE_M17_GSC_G1_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90075b8L GSC_G1_Y_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hoffset_g1                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_voffset_g1                     :12;	//27:16
}PE_M17_GSC_G1_Y_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90075bcL GSC_G1_Y_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hactive_g1                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vactive_g1                     :12;	//27:16
}PE_M17_GSC_G1_Y_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90075c0L GSC_G1_Y_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hisize_g1                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_visize_g1                      :12;	//27:16
}PE_M17_GSC_G1_Y_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90075c4L GSC_G1_Y_PHASE_OFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_phase_off_v_g1                 :9 ;	//8:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_phase_off_h_g1                 :9 ;	//24:16
}PE_M17_GSC_G1_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90075c8L GSC_G1_Y_SAMPLING_H                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_h_g1               :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_numerator_h_g1                 :13;	//28:16
}PE_M17_GSC_G1_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc90075ccL GSC_G1_Y_SAMPLING_V                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_v_g1               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_numerator_v_g1                 :12;	//27:16
}PE_M17_GSC_G1_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc90075d0L GSC_G1_Y_POST_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hoffset_g1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_voffset_g1                :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_post_crop_en_g1                :1 ;	//31
}PE_M17_GSC_G1_Y_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90075d4L GSC_G1_Y_POST_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hactive_g1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_vactive_g1                :12;	//27:16
}PE_M17_GSC_G1_Y_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90075d8L GSC_G1_Y_POST_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hisize_g1                 :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_visize_g1                 :12;	//27:16
}PE_M17_GSC_G1_Y_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90075dcL GSC_G1_Y_MIF_RD_HOFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_hoffset_g1              :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_mif_rd_voffset_g1              :12;	//27:16
}PE_M17_GSC_G1_Y_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90075e0L GSC_G1_FRC_FAIL_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_frc_fail_timer_g1              :32;	//31:0
}PE_M17_GSC_G1_Y_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90075e4L GSC_G1_Y_MIF_PREFATCH_SIGN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pg_mode_en                         :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 mif_prefetch_sign_lcnt             :6 ;	//13:8
}PE_M17_GSC_G1_Y_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc90075e8L GSC_G1_Y_V1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G1_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90075ecL GSC_G1_Y_V1_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient1                     :12;	//27:16
}PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc90075f0L GSC_G1_Y_V1_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient3                     :12;	//27:16
}PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc90075f4L GSC_G1_Y_V1_FIR_COEF_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient4                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient5                     :12;	//27:16
}PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc90075f8L GSC_G1_Y_V1_FIR_COEF_DATA3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient6                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient7                     :12;	//27:16
}PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007618L GSC_G1_Y_H1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G1_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900761cL GSC_G1_Y_H1_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient1                     :12;	//27:16
}PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007620L GSC_G1_Y_H1_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient3                     :12;	//27:16
}PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007624L GSC_G1_Y_H1_FIR_COEF_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient4                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient5                     :12;	//27:16
}PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9007628L GSC_G1_Y_H1_FIR_COEF_DATA3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_coefficient6                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y_coefficient7                     :12;	//27:16
}PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9007648L GSC_G0_Y_SPECTACLE_LUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 wr_rd                              :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 adr                                :10;	//13:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 data                               :13;	//28:16
}PE_M17_GSC_G0_Y_SPECTACLE_LUT_T;
/*-----------------------------------------------------------------------------
                             0xc900764cL GSC_G1_Y_SPECTACLE_LUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 wr_rd                              :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 adr                                :10;	//13:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 data                               :13;	//28:16
}PE_M17_GSC_G1_Y_SPECTACLE_LUT_T;
/*-----------------------------------------------------------------------------
                             0xc90076e0L GSC_G0_VCNT_OUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_out                           :12;	//11:0
}PE_M17_GSC_G0_Y_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90076e4L GSC_G1_VCNT_OUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_out                           :12;	//11:0
}PE_M17_GSC_G1_Y_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90076ecL GSC_G0_VCNT_IN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_in                            :12;	//11:0
}PE_M17_GSC_G0_Y_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90076f0L GSC_G1_VCNT_IN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_in                            :12;	//11:0
}PE_M17_GSC_G1_Y_VCNT_IN_T;


/*-----------------------------------------------------------------------------
                             0xc9007700L GSC_G0_C_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_on_g0                   :1 ;	//0 
	UINT32 reg_mif_wr_on_g0                   :1 ;	//1 
	UINT32 reg_spectacle_en                   :1 ;	//2 
	UINT32 reg_vsc_mode_g0                    :2 ;	//4:3
	UINT32 reg_bilinear_on_g0                 :1 ;	//5 
	UINT32 reg_mode_32p_g0                    :1 ;	//6 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_min_max_on_g0                  :1 ;	//14
	UINT32 reg_min_max_th_g0                  :10;	//24:15
	UINT32 reg_v_reverse_g0                   :1 ;	//25
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_min_max_on_h_g0                :1 ;	//27
	UINT32 reg_v_cti_en_g0                    :1 ;	//28
	UINT32 reg_v_cti_ratio_g0                 :2 ;	//30:29
	UINT32 reg_sampling_mode_g0               :1 ;	//31
}PE_M17_GSC_G0_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007704L GSC_G0_C_MIF_RD_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hsize_g0                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vsize_g0                       :12;	//27:16
	UINT32 reg_vinc_g0                        :4 ;	//31:28
}PE_M17_GSC_G0_C_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007708L GSC_G0_C_OUTSIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hosize_g0                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vosize_g0                      :12;	//27:16
}PE_M17_GSC_G0_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9007710L GSC_G0_C_INPUT_MUX                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 lmux_sel                           :1 ;	//0 
	UINT32 rmux_sel                           :1 ;	//1 
	UINT32 inverse_en                         :1 ;	//2 
	UINT32 l_share_en                         :1 ;	//3 
	UINT32 r_share_en                         :1 ;	//4 
	UINT32 share_flow_ctrl_en                 :1 ;	//5 
	UINT32 lmux_sel2                          :1 ;	//6 
	UINT32 rmux_sel2                          :1 ;	//7 
}PE_M17_GSC_G0_C_INPUT_MUX_T;
/*-----------------------------------------------------------------------------
                             0xc9007714L GSC_G0_C_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hoffset_g0                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_voffset_g0                     :12;	//27:16
}PE_M17_GSC_G0_C_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007718L GSC_G0_C_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hactive_g0                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vactive_g0                     :12;	//27:16
}PE_M17_GSC_G0_C_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc900771cL GSC_G0_C_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hisize_g0                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_visize_g0                      :12;	//27:16
}PE_M17_GSC_G0_C_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007720L GSC_G0_C_PHASE_OFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_phase_off_v_g0                 :9 ;	//8:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_phase_off_h_g0                 :9 ;	//24:16
}PE_M17_GSC_G0_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9007724L GSC_G0_C_SAMPLING_H                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_h_g0               :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_numerator_h_g0                 :13;	//28:16
}PE_M17_GSC_G0_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc9007728L GSC_G0_C_SAMPLING_V                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_v_g0               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_numerator_v_g0                 :12;	//27:16
}PE_M17_GSC_G0_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900772cL GSC_G0_C_POST_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hoffset_g0                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_voffset_g0                :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_post_crop_en_g0                :1 ;	//31
}PE_M17_GSC_G0_C_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9007730L GSC_G0_C_POST_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hactive_g0                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_vactive_g0                :12;	//27:16
}PE_M17_GSC_G0_C_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc9007734L GSC_G0_C_POST_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hisize_g0                 :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_visize_g0                 :12;	//27:16
}PE_M17_GSC_G0_C_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9007738L GSC_G0_C_MIF_RD_HOFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_hoffset_g0              :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_mif_rd_voffset_g0              :12;	//27:16
}PE_M17_GSC_G0_C_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900773cL GSC_G0_FRC_FAIL_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_frc_fail_timer_g0              :32;	//31:0
}PE_M17_GSC_G0_C_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc9007740L GSC_G0_C_MIF_PREFATCH_SIGN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pg_mode_en                         :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 mif_prefetch_sign_lcnt             :6 ;	//13:8
}PE_M17_GSC_G0_C_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc9007744L GSC_G0_C_V1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G0_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007748L GSC_G0_C_V1_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient1                     :12;	//27:16
}PE_M17_GSC_G0_C_V1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900774cL GSC_G0_C_V1_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient3                     :12;	//27:16
}PE_M17_GSC_G0_C_V1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007774L GSC_G0_C_H1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G0_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9007778L GSC_G0_C_H1_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient1                     :12;	//27:16
}PE_M17_GSC_G0_C_H1_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900777cL GSC_G0_C_H1_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient3                     :12;	//27:16
}PE_M17_GSC_G0_C_H1_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc90077a4L GSC_G1_C_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_on_g1                   :1 ;	//0 
	UINT32 reg_mif_wr_on_g1                   :1 ;	//1 
	UINT32 reg_spectacle_en                   :1 ;	//2 
	UINT32 reg_vsc_mode_g1                    :2 ;	//4:3
	UINT32 reg_bilinear_on_g1                 :1 ;	//5 
	UINT32 reg_mode_32p_g1                    :1 ;	//6 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_min_max_on_g1                  :1 ;	//14
	UINT32 reg_min_max_th_g1                  :10;	//24:15
	UINT32 reg_v_reverse_g1                   :1 ;	//25
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_min_max_on_h_g1                :1 ;	//27
	UINT32 reg_v_cti_en_g1                    :1 ;	//28
	UINT32 reg_v_cti_ratio_g1                 :2 ;	//30:29
	UINT32 reg_sampling_mode_g1               :1 ;	//31
}PE_M17_GSC_G1_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90077a8L GSC_G1_C_MIF_RD_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hsize_g1                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vsize_g1                       :12;	//27:16
	UINT32 reg_vinc_g1                        :4 ;	//31:28
}PE_M17_GSC_G1_C_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90077acL GSC_G1_C_OUTSIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hosize_g1                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vosize_g1                      :12;	//27:16
}PE_M17_GSC_G1_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc90077b0L GSC_G1_C_CANVAS_WRITE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_canvas_xoffset_g1              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_canvas_yoffset_g1              :11;	//26:16
}PE_M17_GSC_G1_C_CANVAS_WRITE_T;
/*-----------------------------------------------------------------------------
                             0xc90077b4L GSC_G1_C_MERGE_PARAM                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_active_merge_g1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_overlap_merge_g1               :13;	//28:16
}PE_M17_GSC_G1_C_MERGE_PARAM_T;
/*-----------------------------------------------------------------------------
                             0xc90077b8L GSC_G1_C_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hoffset_g1                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_voffset_g1                     :12;	//27:16
}PE_M17_GSC_G1_C_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90077bcL GSC_G1_C_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hactive_g1                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_vactive_g1                     :12;	//27:16
}PE_M17_GSC_G1_C_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90077c0L GSC_G1_C_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hisize_g1                      :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_visize_g1                      :12;	//27:16
}PE_M17_GSC_G1_C_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90077c4L GSC_G1_C_PHASE_OFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_phase_off_v_g1                 :9 ;	//8:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_phase_off_h_g1                 :9 ;	//24:16
}PE_M17_GSC_G1_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90077c8L GSC_G1_C_SAMPLING_H                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_h_g1               :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_numerator_h_g1                 :13;	//28:16
}PE_M17_GSC_G1_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc90077ccL GSC_G1_C_SAMPLING_V                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_v_g1               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_numerator_v_g1                 :12;	//27:16
}PE_M17_GSC_G1_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc90077d0L GSC_G1_C_POST_CROP_PARAM1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hoffset_g1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_voffset_g1                :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_post_crop_en_g1                :1 ;	//31
}PE_M17_GSC_G1_C_POST_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc90077d4L GSC_G1_C_POST_CROP_PARAM2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hactive_g1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_vactive_g1                :12;	//27:16
}PE_M17_GSC_G1_C_POST_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc90077d8L GSC_G1_C_POST_CROP_PARAM3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post_hisize_g1                 :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_post_visize_g1                 :12;	//27:16
}PE_M17_GSC_G1_C_POST_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc90077dcL GSC_G1_C_MIF_RD_HOFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mif_rd_hoffset_g1              :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_mif_rd_voffset_g1              :12;	//27:16
}PE_M17_GSC_G1_C_MIF_RD_HOFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc90077e0L GSC_G1_FRC_FAIL_TIMER                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_frc_fail_timer_g1              :32;	//31:0
}PE_M17_GSC_G1_C_FRC_FAIL_TIMER_T;
/*-----------------------------------------------------------------------------
                             0xc90077e4L GSC_G1_C_MIF_PREFATCH_SIGN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pg_mode_en                         :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 mif_prefetch_sign_lcnt             :6 ;	//13:8
}PE_M17_GSC_G1_C_MIF_PREFATCH_SIGN_T;
/*-----------------------------------------------------------------------------
                             0xc90077e8L GSC_G1_C_V1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G1_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90077ecL GSC_G1_C_V1_C_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient1                     :12;	//27:16
}PE_M17_GSC_G1_C_V1_C_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc90077f0L GSC_G1_C_V1_C_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient3                     :12;	//27:16
}PE_M17_GSC_G1_C_V1_C_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007818L GSC_G1_C_H1_FIR_COEF_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 rnw                                :1 ;	//1 
	UINT32 addr                               :8 ;	//9:2
}PE_M17_GSC_G1_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900781cL GSC_G1_C_H1_C_FIR_COEF_DATA0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient0                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient1                     :12;	//27:16
}PE_M17_GSC_G1_C_H1_C_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9007820L GSC_G1_C_H1_C_FIR_COEF_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c_coefficient2                     :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 c_coefficient3                     :12;	//27:16
}PE_M17_GSC_G1_C_H1_C_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9007848L GSC_G0_C_SPECTACLE_LUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 wr_rd                              :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 adr                                :10;	//13:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 data                               :13;	//28:16
}PE_M17_GSC_G0_C_SPECTACLE_LUT_T;
/*-----------------------------------------------------------------------------
                             0xc900784cL GSC_G1_C_SPECTACLE_LUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 update                             :1 ;	//0 
	UINT32 wr_rd                              :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 adr                                :10;	//13:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 data                               :13;	//28:16
}PE_M17_GSC_G1_C_SPECTACLE_LUT_T;
/*-----------------------------------------------------------------------------
                             0xc90078e0L GSC_G0_VCNT_OUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_out                           :12;	//11:0
}PE_M17_GSC_G0_C_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90078e4L GSC_G1_VCNT_OUT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_out                           :12;	//11:0
}PE_M17_GSC_G1_C_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90078ecL GSC_G0_VCNT_IN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_in                            :12;	//11:0
}PE_M17_GSC_G0_C_VCNT_IN_T;
/*-----------------------------------------------------------------------------
                             0xc90078f0L GSC_G1_VCNT_IN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt_in                            :12;	//11:0
}PE_M17_GSC_G1_C_VCNT_IN_T;

typedef struct
{ 
	PE_M17_GSC_G0_Y_CTRL_T                           gsc_g0_y_ctrl;	//0x0000
	PE_M17_GSC_G0_Y_MIF_RD_SIZE_T                    gsc_g0_y_mif_rd_size;	//0x0004
	PE_M17_GSC_G0_Y_OUTSIZE_T                        gsc_g0_y_outsize;	//0x0008
	UINT32                                            reserved3;	//0xc
	PE_M17_GSC_G0_Y_INPUT_MUX_T                      gsc_g0_y_input_mux;	//0x0010
	PE_M17_GSC_G0_Y_CROP_PARAM1_T                    gsc_g0_y_crop_param1;	//0x0014
	PE_M17_GSC_G0_Y_CROP_PARAM2_T                    gsc_g0_y_crop_param2;	//0x0018
	PE_M17_GSC_G0_Y_CROP_PARAM3_T                    gsc_g0_y_crop_param3;	//0x001C
	PE_M17_GSC_G0_Y_PHASE_OFFSET_T                   gsc_g0_y_phase_offset;	//0x0020
	PE_M17_GSC_G0_Y_SAMPLING_H_T                     gsc_g0_y_sampling_h;	//0x0024
	PE_M17_GSC_G0_Y_SAMPLING_V_T                     gsc_g0_y_sampling_v;	//0x0028
	PE_M17_GSC_G0_Y_POST_CROP_PARAM1_T               gsc_g0_y_post_crop_param1;	//0x002C
	PE_M17_GSC_G0_Y_POST_CROP_PARAM2_T               gsc_g0_y_post_crop_param2;	//0x0030
	PE_M17_GSC_G0_Y_POST_CROP_PARAM3_T               gsc_g0_y_post_crop_param3;	//0x0034
	PE_M17_GSC_G0_Y_MIF_RD_HOFFSET_T                 gsc_g0_y_mif_rd_hoffset;	//0x0038
	PE_M17_GSC_G0_Y_FRC_FAIL_TIMER_T                 gsc_g0_y_frc_fail_timer;	//0x003C
	PE_M17_GSC_G0_Y_MIF_PREFATCH_SIGN_T              gsc_g0_y_mif_prefatch_sign;	//0x0040
	PE_M17_GSC_G0_Y_V1_FIR_COEF_CTRL_T               gsc_g0_y_v1_fir_coef_ctrl;	//0x0044
	PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T            gsc_g0_y_v1_y_fir_coef_data0;	//0x0048
	PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T            gsc_g0_y_v1_y_fir_coef_data1;	//0x004C
	PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T            gsc_g0_y_v1_y_fir_coef_data2;	//0x0050
	PE_M17_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T            gsc_g0_y_v1_y_fir_coef_data3;	//0x0054
	UINT32                                            reserved21[7];	//0x58-0x70
	PE_M17_GSC_G0_Y_H1_FIR_COEF_CTRL_T               gsc_g0_y_h1_fir_coef_ctrl;	//0x0074
	PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T            gsc_g0_y_h1_y_fir_coef_data0;	//0x0078
	PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T            gsc_g0_y_h1_y_fir_coef_data1;	//0x007C
	PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T            gsc_g0_y_h1_y_fir_coef_data2;	//0x0080
	PE_M17_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T            gsc_g0_y_h1_y_fir_coef_data3;	//0x0084
	UINT32                                            reserved26[7];	//0x88-0xa0
	PE_M17_GSC_G1_Y_CTRL_T                           gsc_g1_y_ctrl;	//0x00A4
	PE_M17_GSC_G1_Y_MIF_RD_SIZE_T                    gsc_g1_y_mif_rd_size;	//0x00A8
	PE_M17_GSC_G1_Y_OUTSIZE_T                        gsc_g1_y_outsize;	//0x00AC
	UINT32                                            reserved29[2];	//0xb0-0xb4
	PE_M17_GSC_G1_Y_CROP_PARAM1_T                    gsc_g1_y_crop_param1;	//0x00B8
	PE_M17_GSC_G1_Y_CROP_PARAM2_T                    gsc_g1_y_crop_param2;	//0x00BC
	PE_M17_GSC_G1_Y_CROP_PARAM3_T                    gsc_g1_y_crop_param3;	//0x00C0
	PE_M17_GSC_G1_Y_PHASE_OFFSET_T                   gsc_g1_y_phase_offset;	//0x00C4
	PE_M17_GSC_G1_Y_SAMPLING_H_T                     gsc_g1_y_sampling_h;	//0x00C8
	PE_M17_GSC_G1_Y_SAMPLING_V_T                     gsc_g1_y_sampling_v;	//0x00CC
	PE_M17_GSC_G1_Y_POST_CROP_PARAM1_T               gsc_g1_y_post_crop_param1;	//0x00D0
	PE_M17_GSC_G1_Y_POST_CROP_PARAM2_T               gsc_g1_y_post_crop_param2;	//0x00D4
	PE_M17_GSC_G1_Y_POST_CROP_PARAM3_T               gsc_g1_y_post_crop_param3;	//0x00D8
	PE_M17_GSC_G1_Y_MIF_RD_HOFFSET_T                 gsc_g1_y_mif_rd_hoffset;	//0x00DC
	PE_M17_GSC_G1_Y_FRC_FAIL_TIMER_T                 gsc_g1_y_frc_fail_timer;	//0x00E0
	PE_M17_GSC_G1_Y_MIF_PREFATCH_SIGN_T              gsc_g1_y_mif_prefatch_sign;	//0x00E4
	PE_M17_GSC_G1_Y_V1_FIR_COEF_CTRL_T               gsc_g1_y_v1_fir_coef_ctrl;	//0x00E8
	PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA0_T              gsc_g1_y_v1_fir_coef_data0;	//0x00EC
	PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA1_T              gsc_g1_y_v1_fir_coef_data1;	//0x00F0
	PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA2_T              gsc_g1_y_v1_fir_coef_data2;	//0x00F4
	PE_M17_GSC_G1_Y_V1_FIR_COEF_DATA3_T              gsc_g1_y_v1_fir_coef_data3;	//0x00F8
	UINT32                                            reserved46[7];	//0xfc-0x114
	PE_M17_GSC_G1_Y_H1_FIR_COEF_CTRL_T               gsc_g1_y_h1_fir_coef_ctrl;	//0x0118
	PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA0_T              gsc_g1_y_h1_fir_coef_data0;	//0x011C
	PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA1_T              gsc_g1_y_h1_fir_coef_data1;	//0x0120
	PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA2_T              gsc_g1_y_h1_fir_coef_data2;	//0x0124
	PE_M17_GSC_G1_Y_H1_FIR_COEF_DATA3_T              gsc_g1_y_h1_fir_coef_data3;	//0x0128
	UINT32                                            reserved51[7];	//0x12c-0x144
	PE_M17_GSC_G0_Y_SPECTACLE_LUT_T                  gsc_g0_y_spectacle_lut;	//0x0148
	PE_M17_GSC_G1_Y_SPECTACLE_LUT_T                  gsc_g1_y_spectacle_lut;	//0x014C
	UINT32                                            reserved53[36];	//0x150-0x1dc
	PE_M17_GSC_G0_Y_VCNT_OUT_T                       gsc_g0_y_vcnt_out;	//0x01E0
	PE_M17_GSC_G1_Y_VCNT_OUT_T                       gsc_g1_y_vcnt_out;	//0x01E4
	UINT32                                            reserved55;	//0x1e8
	PE_M17_GSC_G0_Y_VCNT_IN_T                        gsc_g0_y_vcnt_in;	//0x01EC
	PE_M17_GSC_G1_Y_VCNT_IN_T                        gsc_g1_y_vcnt_in;	//0x01F0
}PE_GSC_Y_REG_M17_T;

typedef struct
{ 
	PE_M17_GSC_G0_C_CTRL_T                           gsc_g0_c_ctrl;	//0x0000
	PE_M17_GSC_G0_C_MIF_RD_SIZE_T                    gsc_g0_c_mif_rd_size;	//0x0004
	PE_M17_GSC_G0_C_OUTSIZE_T                        gsc_g0_c_outsize;	//0x0008
	UINT32                                            reserved3;	//0xc
	PE_M17_GSC_G0_C_INPUT_MUX_T                      gsc_g0_c_input_mux;	//0x0010
	PE_M17_GSC_G0_C_CROP_PARAM1_T                    gsc_g0_c_crop_param1;	//0x0014
	PE_M17_GSC_G0_C_CROP_PARAM2_T                    gsc_g0_c_crop_param2;	//0x0018
	PE_M17_GSC_G0_C_CROP_PARAM3_T                    gsc_g0_c_crop_param3;	//0x001C
	PE_M17_GSC_G0_C_PHASE_OFFSET_T                   gsc_g0_c_phase_offset;	//0x0020
	PE_M17_GSC_G0_C_SAMPLING_H_T                     gsc_g0_c_sampling_h;	//0x0024
	PE_M17_GSC_G0_C_SAMPLING_V_T                     gsc_g0_c_sampling_v;	//0x0028
	PE_M17_GSC_G0_C_POST_CROP_PARAM1_T               gsc_g0_c_post_crop_param1;	//0x002C
	PE_M17_GSC_G0_C_POST_CROP_PARAM2_T               gsc_g0_c_post_crop_param2;	//0x0030
	PE_M17_GSC_G0_C_POST_CROP_PARAM3_T               gsc_g0_c_post_crop_param3;	//0x0034
	PE_M17_GSC_G0_C_MIF_RD_HOFFSET_T                 gsc_g0_c_mif_rd_hoffset;	//0x0038
	PE_M17_GSC_G0_C_FRC_FAIL_TIMER_T                 gsc_g0_c_frc_fail_timer;	//0x003C
	PE_M17_GSC_G0_C_MIF_PREFATCH_SIGN_T              gsc_g0_c_mif_prefatch_sign;	//0x0040
	PE_M17_GSC_G0_C_V1_FIR_COEF_CTRL_T               gsc_g0_c_v1_fir_coef_ctrl;	//0x0044
	PE_M17_GSC_G0_C_V1_FIR_COEF_DATA0_T              gsc_g0_c_v1_fir_coef_data0;	//0x0048
	PE_M17_GSC_G0_C_V1_FIR_COEF_DATA1_T              gsc_g0_c_v1_fir_coef_data1;	//0x004C
	UINT32                                            reserved19[9];	//0x50-0x70
	PE_M17_GSC_G0_C_H1_FIR_COEF_CTRL_T               gsc_g0_c_h1_fir_coef_ctrl;	//0x0074
	PE_M17_GSC_G0_C_H1_FIR_COEF_DATA0_T              gsc_g0_c_h1_fir_coef_data0;	//0x0078
	PE_M17_GSC_G0_C_H1_FIR_COEF_DATA1_T              gsc_g0_c_h1_fir_coef_data1;	//0x007C
	UINT32                                            reserved22[9];	//0x80-0xa0
	PE_M17_GSC_G1_C_CTRL_T                           gsc_g1_c_ctrl;	//0x00A4
	PE_M17_GSC_G1_C_MIF_RD_SIZE_T                    gsc_g1_c_mif_rd_size;	//0x00A8
	PE_M17_GSC_G1_C_OUTSIZE_T                        gsc_g1_c_outsize;	//0x00AC
	PE_M17_GSC_G1_C_CANVAS_WRITE_T                   gsc_g1_c_canvas_write;	//0x00B0
	PE_M17_GSC_G1_C_MERGE_PARAM_T                    gsc_g1_c_merge_param;	//0x00B4
	PE_M17_GSC_G1_C_CROP_PARAM1_T                    gsc_g1_c_crop_param1;	//0x00B8
	PE_M17_GSC_G1_C_CROP_PARAM2_T                    gsc_g1_c_crop_param2;	//0x00BC
	PE_M17_GSC_G1_C_CROP_PARAM3_T                    gsc_g1_c_crop_param3;	//0x00C0
	PE_M17_GSC_G1_C_PHASE_OFFSET_T                   gsc_g1_c_phase_offset;	//0x00C4
	PE_M17_GSC_G1_C_SAMPLING_H_T                     gsc_g1_c_sampling_h;	//0x00C8
	PE_M17_GSC_G1_C_SAMPLING_V_T                     gsc_g1_c_sampling_v;	//0x00CC
	PE_M17_GSC_G1_C_POST_CROP_PARAM1_T               gsc_g1_c_post_crop_param1;	//0x00D0
	PE_M17_GSC_G1_C_POST_CROP_PARAM2_T               gsc_g1_c_post_crop_param2;	//0x00D4
	PE_M17_GSC_G1_C_POST_CROP_PARAM3_T               gsc_g1_c_post_crop_param3;	//0x00D8
	PE_M17_GSC_G1_C_MIF_RD_HOFFSET_T                 gsc_g1_c_mif_rd_hoffset;	//0x00DC
	PE_M17_GSC_G1_C_FRC_FAIL_TIMER_T                 gsc_g1_c_frc_fail_timer;	//0x00E0
	PE_M17_GSC_G1_C_MIF_PREFATCH_SIGN_T              gsc_g1_c_mif_prefatch_sign;	//0x00E4
	PE_M17_GSC_G1_C_V1_FIR_COEF_CTRL_T               gsc_g1_c_v1_fir_coef_ctrl;	//0x00E8
	PE_M17_GSC_G1_C_V1_C_FIR_COEF_DATA0_T            gsc_g1_c_v1_c_fir_coef_data0;	//0x00EC
	PE_M17_GSC_G1_C_V1_C_FIR_COEF_DATA1_T            gsc_g1_c_v1_c_fir_coef_data1;	//0x00F0
	UINT32                                            reserved42[9];	//0xf4-0x114
	PE_M17_GSC_G1_C_H1_FIR_COEF_CTRL_T               gsc_g1_c_h1_fir_coef_ctrl;	//0x0118
	PE_M17_GSC_G1_C_H1_C_FIR_COEF_DATA0_T            gsc_g1_c_h1_c_fir_coef_data0;	//0x011C
	PE_M17_GSC_G1_C_H1_C_FIR_COEF_DATA1_T            gsc_g1_c_h1_c_fir_coef_data1;	//0x0120
	UINT32                                            reserved45[9];	//0x124-0x144
	PE_M17_GSC_G0_C_SPECTACLE_LUT_T                  gsc_g0_c_spectacle_lut;	//0x0148
	PE_M17_GSC_G1_C_SPECTACLE_LUT_T                  gsc_g1_c_spectacle_lut;	//0x014C
	UINT32                                            reserved47[36];	//0x150-0x1dc
	PE_M17_GSC_G0_C_VCNT_OUT_T                       gsc_g0_c_vcnt_out;	//0x01E0
	PE_M17_GSC_G1_C_VCNT_OUT_T                       gsc_g1_c_vcnt_out;	//0x01E4
	UINT32                                            reserved49;	//0x1e8
	PE_M17_GSC_G0_C_VCNT_IN_T                        gsc_g0_c_vcnt_in;	//0x01EC
	PE_M17_GSC_G1_C_VCNT_IN_T                        gsc_g1_c_vcnt_in;	//0x01F0
}PE_GSC_C_REG_M17_T;
#endif

