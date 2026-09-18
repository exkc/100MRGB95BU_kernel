#ifndef _PE_SR_MSC_REG_O18A0_H_
#define _PE_SR_MSC_REG_O18A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc900a000L sr_psc_y_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :31,	// reserved
	reg_sampling_mode_m1               :1 ,	// 31:31
	reg_th                             :4 ,	// 9:6
	reg_bilinear_on_m1                 :1 ,	// 5:5
	reg_adaptive_on_m1                 :1 ,	// 4:4
	reg_vsc_mode_m1                    :1 ,	// 3:3
	reserved02                         :6 , // reserved
	blending_range                     :2 ;	// 11:10
}PE_O18_SR_PSC_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a008L sr_psc_y_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_vosize_m1                      :12;	// 27:16
}PE_O18_SR_PSC_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a018L sr_psc_y_insize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_visize_m1                      :12;	// 27:16
}PE_O18_SR_PSC_Y_INSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a020L sr_psc_y_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_m1                 :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_phase_off_h_m1                 :9 ;	// 24:16
}PE_O18_SR_PSC_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900a024L sr_psc_y_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_m1               :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_numerator_h_m1                 :13;	// 28:16
}PE_O18_SR_PSC_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc900a028L sr_psc_y_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_m1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_numerator_v_m1                 :12;	// 27:16
}PE_O18_SR_PSC_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900a02cL sr_psc_y_min_max_ctrl                             
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
}PE_O18_SR_PSC_Y_MIN_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a044L sr_psc_y_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v1                          :1 ,	// 0:0
	rnw_v1                             :1 ,	// 1:1
	addr_v1                            :8 ;	// 9:2
}PE_O18_SR_PSC_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a048L sr_psc_y_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a04cL sr_psc_y_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a050L sr_psc_y_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a054L sr_psc_y_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a058L sr_psc_y_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_v1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a05cL sr_psc_y_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_v1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_v1                 :12;	// 27:16
}PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a060L sr_psc_y_v2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v2                          :1 ,	// 0:0
	rnw_v2                             :1 ,	// 1:1
	addr_v2                            :8 ;	// 9:2
}PE_O18_SR_PSC_Y_V2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a064L sr_psc_y_v2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a068L sr_psc_y_v2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a06cL sr_psc_y_v2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a070L sr_psc_y_v2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a074L sr_psc_y_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h1                          :1 ,	// 0:0
	rnw_h1                             :1 ,	// 1:1
	addr_h1                            :8 ;	// 9:2
}PE_O18_SR_PSC_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a078L sr_psc_y_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a07cL sr_psc_y_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a080L sr_psc_y_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a084L sr_psc_y_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a088L sr_psc_y_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_h1                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a08cL sr_psc_y_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_h1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_h1                 :12;	// 27:16
}PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a090L sr_psc_y_h2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h2                          :1 ,	// 0:0
	rnw_h2                             :1 ,	// 1:1
	addr_h2                            :8 ;	// 9:2
}PE_O18_SR_PSC_Y_H2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a094L sr_psc_y_h2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a098L sr_psc_y_h2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a09cL sr_psc_y_h2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a0a0L sr_psc_y_h2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h2                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h2                  :12;	// 27:16
}PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA3_T;


/*-----------------------------------------------------------------------------
                             0xc900a100L sr_psc_c_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :3 ,	// reserved
	reg_vsc_mode_g0                    :2 ,	// 4:3
	reg_bilinear_on_g0                 :1 ,	// 5:5
	reg_mode_32p_g0                    :1 ,	// 6:6
	reserved02                         :7 ,	// reserved
	reg_min_max_on_g0                  :1 ,	// 14:14
	reg_min_max_th_g0                  :10,	// 24:15
	reg_v_reverse_g0                   :1 ,	// 25:25
	reserved03                         :1 ,	// reserved
	reg_min_max_on_h_g0                :1 ,	// 27:27
	reg_v_cti_en_g0                    :1 ,	// 28:28
	reg_v_cti_ratio_g0                 :2 ,	// 30:29
	reg_sampling_mode_g0               :1 ;	// 31:31
}PE_O18_SR_PSC_C_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a108L sr_psc_c_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_vosize_m1                      :12;	// 27:16
}PE_O18_SR_PSC_C_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a118L sr_psc_c_insize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_m1                      :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_visize_m1                      :12;	// 27:16
}PE_O18_SR_PSC_C_INSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900a120L sr_psc_c_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_m1                 :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_phase_off_h_m1                 :9 ;	// 24:16
}PE_O18_SR_PSC_C_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900a124L sr_psc_c_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_m1               :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_numerator_h_m1                 :13;	// 28:16
}PE_O18_SR_PSC_C_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc900a128L sr_psc_c_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_m1               :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_numerator_v_m1                 :12;	// 27:16
}PE_O18_SR_PSC_C_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900a144L sr_psc_c_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_v1                          :1 ,	// 0:0
	rnw_v1                             :1 ,	// 1:1
	addr_v1                            :8 ;	// 9:2
}PE_O18_SR_PSC_C_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a148L sr_psc_c_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_v1                  :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a14cL sr_psc_c_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_v1                  :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a150L sr_psc_c_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_v1                  :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a154L sr_psc_c_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_v1                  :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a158L sr_psc_c_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_v1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_v1                  :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a15cL sr_psc_c_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_v1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_v1                 :12;	// 27:16
}PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc900a174L sr_psc_c_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update_h1                          :1 ,	// 0:0
	rnw_h1                             :1 ,	// 1:1
	addr_h1                            :8 ;	// 9:2
}PE_O18_SR_PSC_C_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900a178L sr_psc_c_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient1_h1                  :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900a17cL sr_psc_c_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient3_h1                  :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900a180L sr_psc_c_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient5_h1                  :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc900a184L sr_psc_c_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient7_h1                  :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc900a188L sr_psc_c_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8_h1                  :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient9_h1                  :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900a18cL sr_psc_c_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10_h1                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y_coefficient11_h1                 :12;	// 27:16
}PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA5_T;


/*-----------------------------------------------------------------------------
                             0xc9008600L sre_2k_y_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mif_rd_on_g0                   :1 ,	// 0 
	reg_mif_wr_on_g0                   :1 ,	// 1 
	reserved01                         :1 ,	// reserved
	reg_vsc_mode_g0                    :1 ,	// 3 
	reg_adaptive_en_g0                 :1 ,	// 4 
	reg_bilinear_on_g0                 :1 ,	// 5 
	reg_th_g0                          :4 ,	// 9:6
	blending_range_g0                  :2 ,	// 11:10
	reserved02                         :18,	// reserved
	reg_mode_32p_g0                    :1 ,	// 30
	reg_sampling_mode_g0               :1 ;	// 31
}PE_O18_SRE_2K_Y_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008604L sre_2k_y_mif_rd_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hsize_g0                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_vsize_g0                       :12,	// 27:16
	reg_vinc_g0                        :4 ;	// 31:28
}PE_O18_SRE_2K_Y_MIF_RD_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9008608L sre_2k_y_outsize                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hosize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vosize_g0                      :12;	// 27:16
}PE_O18_SRE_2K_Y_OUTSIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9008614L sre_2k_y_crop_param1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hoffset_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_voffset_g0                     :12;	// 27:16
}PE_O18_SRE_2K_Y_CROP_PARAM1_T;
/*-----------------------------------------------------------------------------
                             0xc9008618L sre_2k_y_crop_param2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hactive_g0                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_vactive_g0                     :12;	// 27:16
}PE_O18_SRE_2K_Y_CROP_PARAM2_T;
/*-----------------------------------------------------------------------------
                             0xc900861cL sre_2k_y_crop_param3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hisize_g0                      :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_visize_g0                      :12;	// 27:16
}PE_O18_SRE_2K_Y_CROP_PARAM3_T;
/*-----------------------------------------------------------------------------
                             0xc9008620L sre_2k_y_phase_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_v_g0                 :9 ,	// 8:0
	reserved01                         :7 , // reserved
	reg_phase_off_h_g0                 :9 ;	// 24:16
}PE_O18_SRE_2K_Y_PHASE_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9008624L sre_2k_y_sampling_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h_g0               :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_h_g0                 :13;	// 28:16
}PE_O18_SRE_2K_Y_SAMPLING_H_T;
/*-----------------------------------------------------------------------------
                             0xc9008628L sre_2k_y_sampling_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_v_g0               :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_numerator_v_g0                 :12;	// 27:16
}PE_O18_SRE_2K_Y_SAMPLING_V_T;
/*-----------------------------------------------------------------------------
                             0xc900862cL sre_2k_y_min_max_ctrl                             
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
}PE_O18_SRE_2K_Y_MIN_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008644L sre_2k_y_v1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O18_SRE_2K_Y_V1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008648L sre_2k_y_v1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900864cL sre_2k_y_v1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9008650L sre_2k_y_v1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9008654L sre_2k_y_v1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9008658L sre_2k_y_v1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient9                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900865cL sre_2k_y_v1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10                    :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient11                    :12;	// 27:16
}PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc9008660L sre_2k_y_v2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O18_SRE_2K_Y_V2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008664L sre_2k_y_v2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9008668L sre_2k_y_v2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900866cL sre_2k_y_v2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9008670L sre_2k_y_v2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9008674L sre_2k_y_h1_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O18_SRE_2K_Y_H1_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008678L sre_2k_y_h1_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc900867cL sre_2k_y_h1_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9008680L sre_2k_y_h1_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9008684L sre_2k_y_h1_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc9008688L sre_2k_y_h1_y_fir_coef_data4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient8                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient9                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA4_T;
/*-----------------------------------------------------------------------------
                             0xc900868cL sre_2k_y_h1_y_fir_coef_data5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient10                    :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient11                    :12;	// 27:16
}PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA5_T;
/*-----------------------------------------------------------------------------
                             0xc9008690L sre_2k_y_h2_fir_coef_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	update                             :1 ,	// 0 
	rnw                                :1 ,	// 1 
	addr                               :8 ;	// 9:2
}PE_O18_SRE_2K_Y_H2_FIR_COEF_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008694L sre_2k_y_h2_y_fir_coef_data0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient0                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient1                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA0_T;
/*-----------------------------------------------------------------------------
                             0xc9008698L sre_2k_y_h2_y_fir_coef_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient2                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient3                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc900869cL sre_2k_y_h2_y_fir_coef_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient4                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient5                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc90086a0L sre_2k_y_h2_y_fir_coef_data3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_coefficient6                     :12,	// 11:0
	reserved01                         :4 , // reserved
	y_coefficient7                     :12;	// 27:16
}PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA3_T;
/*-----------------------------------------------------------------------------
                             0xc90086a4L sre_2k_y_nd_mif_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nd_mif_width                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	nd_mif_height                      :12,	// 27:16
	reserved02                         :3 ,	// reserved
	nd_mif_wr_on                       :1 ;	// 31
}PE_O18_SRE_2K_Y_ND_MIF_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc90087e0L sre_2k_vcnt_out                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_out_g0                        :12;	// 11:0
}PE_O18_SRE_2K_VCNT_OUT_T;
/*-----------------------------------------------------------------------------
                             0xc90087ecL sre_2k_vcnt_in                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt_in_g0                         :12;	// 11:0
}PE_O18_SRE_2K_VCNT_IN_T;

typedef struct
{ 
	PE_O18_SR_PSC_Y_CTRL_T                            sr_psc_y_ctrl;	//0x0000
	UINT32                                            reserved1;	//0x4
	PE_O18_SR_PSC_Y_OUTSIZE_T                         sr_psc_y_outsize;	//0x0008
	UINT32                                            reserved2[3];	//0xc-0x14
	PE_O18_SR_PSC_Y_INSIZE_T                          sr_psc_y_insize;	//0x0018
	UINT32                                            reserved3;	//0x1c
	PE_O18_SR_PSC_Y_PHASE_OFFSET_T                    sr_psc_y_phase_offset;	//0x0020
	PE_O18_SR_PSC_Y_SAMPLING_H_T                      sr_psc_y_sampling_h;	//0x0024
	PE_O18_SR_PSC_Y_SAMPLING_V_T                      sr_psc_y_sampling_v;	//0x0028
	PE_O18_SR_PSC_Y_MIN_MAX_CTRL_T                    sr_psc_y_min_max_ctrl;	//0x002C
	UINT32                                            reserved7[5];	//0x30-0x40
	PE_O18_SR_PSC_Y_V1_FIR_COEF_CTRL_T                sr_psc_y_v1_fir_coef_ctrl;	//0x0044
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA0_T             sr_psc_y_v1_y_fir_coef_data0;	//0x0048
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA1_T             sr_psc_y_v1_y_fir_coef_data1;	//0x004C
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA2_T             sr_psc_y_v1_y_fir_coef_data2;	//0x0050
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA3_T             sr_psc_y_v1_y_fir_coef_data3;	//0x0054
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA4_T             sr_psc_y_v1_y_fir_coef_data4;	//0x0058
	PE_O18_SR_PSC_Y_V1_Y_FIR_COEF_DATA5_T             sr_psc_y_v1_y_fir_coef_data5;	//0x005C
	PE_O18_SR_PSC_Y_V2_FIR_COEF_CTRL_T                sr_psc_y_v2_fir_coef_ctrl;	//0x0060
	PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA0_T             sr_psc_y_v2_y_fir_coef_data0;	//0x0064
	PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA1_T             sr_psc_y_v2_y_fir_coef_data1;	//0x0068
	PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA2_T             sr_psc_y_v2_y_fir_coef_data2;	//0x006C
	PE_O18_SR_PSC_Y_V2_Y_FIR_COEF_DATA3_T             sr_psc_y_v2_y_fir_coef_data3;	//0x0070
	PE_O18_SR_PSC_Y_H1_FIR_COEF_CTRL_T                sr_psc_y_h1_fir_coef_ctrl;	//0x0074
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA0_T             sr_psc_y_h1_y_fir_coef_data0;	//0x0078
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA1_T             sr_psc_y_h1_y_fir_coef_data1;	//0x007C
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA2_T             sr_psc_y_h1_y_fir_coef_data2;	//0x0080
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA3_T             sr_psc_y_h1_y_fir_coef_data3;	//0x0084
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA4_T             sr_psc_y_h1_y_fir_coef_data4;	//0x0088
	PE_O18_SR_PSC_Y_H1_Y_FIR_COEF_DATA5_T             sr_psc_y_h1_y_fir_coef_data5;	//0x008C
	PE_O18_SR_PSC_Y_H2_FIR_COEF_CTRL_T                sr_psc_y_h2_fir_coef_ctrl;	//0x0090
	PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA0_T             sr_psc_y_h2_y_fir_coef_data0;	//0x0094
	PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA1_T             sr_psc_y_h2_y_fir_coef_data1;	//0x0098
	PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA2_T             sr_psc_y_h2_y_fir_coef_data2;	//0x009C
	PE_O18_SR_PSC_Y_H2_Y_FIR_COEF_DATA3_T             sr_psc_y_h2_y_fir_coef_data3;	//0x00A0
}PE_SR_MSC_Y_REG_O18_T;

typedef struct
{ 
	PE_O18_SR_PSC_C_CTRL_T                            sr_psc_c_ctrl;	//0x0000
	UINT32                                            reserved1;	//0x4
	PE_O18_SR_PSC_C_OUTSIZE_T                         sr_psc_c_outsize;	//0x0008
	UINT32                                            reserved2[3];	//0xc-0x14
	PE_O18_SR_PSC_C_INSIZE_T                          sr_psc_c_insize;	//0x0018
	UINT32                                            reserved3;	//0x1c
	PE_O18_SR_PSC_C_PHASE_OFFSET_T                    sr_psc_c_phase_offset;	//0x0020
	PE_O18_SR_PSC_C_SAMPLING_H_T                      sr_psc_c_sampling_h;	//0x0024
	PE_O18_SR_PSC_C_SAMPLING_V_T                      sr_psc_c_sampling_v;	//0x0028
	UINT32                                            reserved6[6];	//0x2c-0x40
	PE_O18_SR_PSC_C_V1_FIR_COEF_CTRL_T                sr_psc_c_v1_fir_coef_ctrl;	//0x0044
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA0_T             sr_psc_c_v1_y_fir_coef_data0;	//0x0048
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA1_T             sr_psc_c_v1_y_fir_coef_data1;	//0x004C
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA2_T             sr_psc_c_v1_y_fir_coef_data2;	//0x0050
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA3_T             sr_psc_c_v1_y_fir_coef_data3;	//0x0054
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA4_T             sr_psc_c_v1_y_fir_coef_data4;	//0x0058
	PE_O18_SR_PSC_C_V1_Y_FIR_COEF_DATA5_T             sr_psc_c_v1_y_fir_coef_data5;	//0x005C
	UINT32                                            reserved13[5];	//0x60-0x70
	PE_O18_SR_PSC_C_H1_FIR_COEF_CTRL_T                sr_psc_c_h1_fir_coef_ctrl;	//0x0074
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA0_T             sr_psc_c_h1_y_fir_coef_data0;	//0x0078
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA1_T             sr_psc_c_h1_y_fir_coef_data1;	//0x007C
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA2_T             sr_psc_c_h1_y_fir_coef_data2;	//0x0080
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA3_T             sr_psc_c_h1_y_fir_coef_data3;	//0x0084
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA4_T             sr_psc_c_h1_y_fir_coef_data4;	//0x0088
	PE_O18_SR_PSC_C_H1_Y_FIR_COEF_DATA5_T             sr_psc_c_h1_y_fir_coef_data5;	//0x008C
}PE_SR_MSC_C_REG_O18_T;

typedef struct
{ 
	PE_O18_SRE_2K_Y_CTRL_T                            sre_2k_y_ctrl;	//0x0000
	PE_O18_SRE_2K_Y_MIF_RD_SIZE_T                     sre_2k_y_mif_rd_size;	//0x0004
	PE_O18_SRE_2K_Y_OUTSIZE_T                         sre_2k_y_outsize;	//0x0008
	UINT32                                            reserved3[2];	//0xc-0x10
	PE_O18_SRE_2K_Y_CROP_PARAM1_T                     sre_2k_y_crop_param1;	//0x0014
	PE_O18_SRE_2K_Y_CROP_PARAM2_T                     sre_2k_y_crop_param2;	//0x0018
	PE_O18_SRE_2K_Y_CROP_PARAM3_T                     sre_2k_y_crop_param3;	//0x001C
	PE_O18_SRE_2K_Y_PHASE_OFFSET_T                    sre_2k_y_phase_offset;	//0x0020
	PE_O18_SRE_2K_Y_SAMPLING_H_T                      sre_2k_y_sampling_h;	//0x0024
	PE_O18_SRE_2K_Y_SAMPLING_V_T                      sre_2k_y_sampling_v;	//0x0028
	PE_O18_SRE_2K_Y_MIN_MAX_CTRL_T                    sre_2k_y_min_max_ctrl;	//0x002C
	UINT32                                            reserved10[5];	//0x30-0x40
	PE_O18_SRE_2K_Y_V1_FIR_COEF_CTRL_T                sre_2k_y_v1_fir_coef_ctrl;	//0x0044
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA0_T             sre_2k_y_v1_y_fir_coef_data0;	//0x0048
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA1_T             sre_2k_y_v1_y_fir_coef_data1;	//0x004C
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA2_T             sre_2k_y_v1_y_fir_coef_data2;	//0x0050
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA3_T             sre_2k_y_v1_y_fir_coef_data3;	//0x0054
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA4_T             sre_2k_y_v1_y_fir_coef_data4;	//0x0058
	PE_O18_SRE_2K_Y_V1_Y_FIR_COEF_DATA5_T             sre_2k_y_v1_y_fir_coef_data5;	//0x005C
	PE_O18_SRE_2K_Y_V2_FIR_COEF_CTRL_T                sre_2k_y_v2_fir_coef_ctrl;	//0x0060
	PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA0_T             sre_2k_y_v2_y_fir_coef_data0;	//0x0064
	PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA1_T             sre_2k_y_v2_y_fir_coef_data1;	//0x0068
	PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA2_T             sre_2k_y_v2_y_fir_coef_data2;	//0x006C
	PE_O18_SRE_2K_Y_V2_Y_FIR_COEF_DATA3_T             sre_2k_y_v2_y_fir_coef_data3;	//0x0070
	PE_O18_SRE_2K_Y_H1_FIR_COEF_CTRL_T                sre_2k_y_h1_fir_coef_ctrl;	//0x0074
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA0_T             sre_2k_y_h1_y_fir_coef_data0;	//0x0078
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA1_T             sre_2k_y_h1_y_fir_coef_data1;	//0x007C
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA2_T             sre_2k_y_h1_y_fir_coef_data2;	//0x0080
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA3_T             sre_2k_y_h1_y_fir_coef_data3;	//0x0084
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA4_T             sre_2k_y_h1_y_fir_coef_data4;	//0x0088
	PE_O18_SRE_2K_Y_H1_Y_FIR_COEF_DATA5_T             sre_2k_y_h1_y_fir_coef_data5;	//0x008C
	PE_O18_SRE_2K_Y_H2_FIR_COEF_CTRL_T                sre_2k_y_h2_fir_coef_ctrl;	//0x0090
	PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA0_T             sre_2k_y_h2_y_fir_coef_data0;	//0x0094
	PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA1_T             sre_2k_y_h2_y_fir_coef_data1;	//0x0098
	PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA2_T             sre_2k_y_h2_y_fir_coef_data2;	//0x009C
	PE_O18_SRE_2K_Y_H2_Y_FIR_COEF_DATA3_T             sre_2k_y_h2_y_fir_coef_data3;	//0x00A0
	PE_O18_SRE_2K_Y_ND_MIF_CTRL0_T                    sre_2k_y_nd_mif_ctrl0;	//0x00A4
	UINT32                                            reserved35[78];	//0xa8-0x1dc
	PE_O18_SRE_2K_VCNT_OUT_T                          sre_2k_vcnt_out;	//0x01E0
	UINT32                                            reserved36[2];	//0x1e4-0x1e8
	PE_O18_SRE_2K_VCNT_IN_T                           sre_2k_vcnt_in;	//0x01EC
}PE_SR_2K_MSC_Y_REG_O18_T;
#endif