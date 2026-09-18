#ifndef _PE_GSC_REG_E60A0_1_H_
#define _PE_GSC_REG_E60A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC9020200 RW
	UINT32 reg_mif_rd_on_g0                 :1;	//0 //'0' : MIF read off (= select FMC direct source)	    '1' : MIF read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g0                 :1;	//1 //'0' : VCP out	    '1' : MIF write
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_mode_g0                  :1;	//3 //'0' : V12TAB filter (active width < 4096)	    '1' : V6TAB filter (active width >= 4096)
	UINT32 reg_adaptive_on_g0               :1;	//4 //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on_g0               :1;	//5 //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :2;
	UINT32 blending_range_g0                :2;	//9:8	//blending range of adaptive filter
	UINT32 reg_th_g0                        :2;	//11:10	//threshold of adaptive filter
	UINT32 reg_th_g1                        :2;	//13:12	//threshold of adaptive filter
	UINT32 reg_blur_flag_debug              :1;	//14 //N.A
	UINT32 resvd2                           :10;
	UINT32 reg_v_reverse_sm_g0              :1;	//25 //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd3                           :3;
	UINT32 reg_blur_flag_bypass_g0          :1;	//29 //'0' : normal operation 	     '1' : LSB 1bit blur flag enable mode
	UINT32 reg_mode_32p_g0                  :1;	//30 //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g0             :1;	//31 //'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_GSC_G0_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020204 RW
	UINT32 reg_hsize_g0                     :14;	//13:0	//G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//29:16	//G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//31:30	//V increment for G0 MRD
	};
}PE_E60_GSC_G0_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020208 RW
	UINT32 reg_hosize_g0                    :14;	//13:0	//width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize_g0                    :14;	//29:16	//height
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902020C RW
	UINT32 reg_min_max_on_l_h               :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_min_max_th_l_h               :9;	//12:4	//
	UINT32 adaptive_fir_h_mode              :1;	//13 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd1                           :2;
	UINT32 reg_min_max_on_l_v               :1;	//16 //
	UINT32 resvd2                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//28:20	//
	UINT32 adaptive_fir_v_mode              :1;	//29 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd3                           :1;
	UINT32 reg_v_min_max_extend             :1;	//31 //'0' : 1line window  	 '1' : 3line window
	};
}PE_E60_GSC_G0_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020214 RW
	UINT32 reg_hoffset_g0                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_voffset_g0                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020218 RW
	UINT32 reg_hactive_g0                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_vactive_g0                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902021C RW
	UINT32 reg_hisize_g0                    :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_visize_g0                    :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020220 RW
	UINT32 reg_phase_off_v_g0               :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_E60_GSC_G0_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020224 RW
	UINT32 reg_denominator_h_g0             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h_g0               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020228 RW
	UINT32 reg_denominator_v_g0             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v_g0               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902022C RW
	UINT32 reg_post_hoffset_g0              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset_g0              :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en_g0              :1;	//31 //output crop enable
	};
}PE_E60_GSC_G0_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020230 RW
	UINT32 reg_post_hactive_g0              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive_g0              :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020234 RW
	UINT32 reg_post_hisize_g0               :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize_g0               :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020238 RW
	UINT32 reg_mif_rd_hoffset_g0            :14;	//13:0	//MRD H offset
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_g0            :14;	//29:16	//MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_Y_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902023C RW
	UINT32 reg_frc_fail_timer_g0            :32;	//31:0	//0 : fail timer off
	};
}PE_E60_GSC_G0_Y_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020244 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_Y_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020248 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902024C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020250 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020254 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020258 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902025C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020260 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_Y_V2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020264 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020268 RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902026C RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020270 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020274 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_Y_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020278 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902027C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020280 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020284 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020288 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902028C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020290 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_Y_H2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020294 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020298 RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902029C RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90202A0 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90202A4 RO
	UINT32 vcnt_out_g0                      :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G0_Y_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90202A8 RO
	UINT32 vcnt_in_g0                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G0_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90202AC RO
	UINT32 fmc_timer_g0                     :32;	//31:0	//clk count from GSC picinit to FMC first valid
	};
}PE_E60_GSC_G0_Y_FMC_TIMER_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020400 RW
	UINT32 reg_mif_rd_on_g1                 :1;	//0 //'0' : MIF read off (= select FMC direct source)	    '1' : MIF read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g1                 :1;	//1 //'0' : VCP out	    '1' : MIF write
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_mode_g1                  :1;	//3 //'0' : V12TAB filter (active width < 4096)	    '1' : V6TAB filter (active width >= 4096)
	UINT32 reg_adaptive_on_g1               :1;	//4 //N.A
	UINT32 reg_bilinear_on_g1               :1;	//5 //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :2;
	UINT32 blending_range_g1                :2;	//9:8	//N.A
	UINT32 reg_th_g0                        :2;	//11:10	//N.A
	UINT32 reg_th_g1                        :2;	//13:12	//N.A
	UINT32 reg_blur_flag_debug              :1;	//14 //N.A
	UINT32 resvd2                           :10;
	UINT32 reg_v_reverse_sm_g1              :1;	//25 //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd3                           :3;
	UINT32 reg_blur_flag_bypass_g1          :1;	//29 //N.A
	UINT32 reg_mode_32p_g1                  :1;	//30 //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g1             :1;	//31 //'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_GSC_G1_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020404 RW
	UINT32 reg_hsize_g1                     :14;	//13:0	//G1 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g1                     :14;	//29:16	//G1 MRd size info. V
	UINT32 reg_vinc_g1                      :2;	//31:30	//V increment for G1 MRD
	};
}PE_E60_GSC_G1_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020408 RW
	UINT32 reg_hosize_g1                    :14;	//13:0	//width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize_g1                    :14;	//29:16	//height
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902040C RW
	UINT32 reg_min_max_on_l_h               :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_min_max_th_l_h               :9;	//12:4	//
	UINT32 adaptive_fir_h_mode              :1;	//13 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd1                           :2;
	UINT32 reg_min_max_on_l_v               :1;	//16 //
	UINT32 resvd2                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//28:20	//
	UINT32 adaptive_fir_v_mode              :1;	//29 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd3                           :1;
	UINT32 reg_v_min_max_extend             :1;	//31 //'0' : 1line window  	 '1' : 3line window
	};
}PE_E60_GSC_G1_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020414 RW
	UINT32 reg_hoffset_g1                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_voffset_g1                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020418 RW
	UINT32 reg_hactive_g1                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_vactive_g1                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902041C RW
	UINT32 reg_hisize_g1                    :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_visize_g1                    :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020420 RW
	UINT32 reg_phase_off_v_g1               :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g1               :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_E60_GSC_G1_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020424 RW
	UINT32 reg_denominator_h_g1             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h_g1               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020428 RW
	UINT32 reg_denominator_v_g1             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v_g1               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902042C RW
	UINT32 reg_post_hoffset_g1              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset_g1              :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en_g1              :1;	//31 //output crop enable
	};
}PE_E60_GSC_G1_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020430 RW
	UINT32 reg_post_hactive_g1              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive_g1              :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020434 RW
	UINT32 reg_post_hisize_g1               :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize_g1               :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020438 RW
	UINT32 reg_mif_rd_hoffset_g1            :14;	//13:0	//MRD H offset
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_g1            :14;	//29:16	//MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_Y_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902043C RW
	UINT32 reg_frc_fail_timer_g1            :32;	//31:0	//0 : fail timer off
	};
}PE_E60_GSC_G1_Y_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020444 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G1_Y_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020448 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902044C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020450 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020454 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020458 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902045C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020474 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G1_Y_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020478 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902047C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020480 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020484 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9020488 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902048C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90204A4 RO
	UINT32 vcnt_out_g1                      :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G1_Y_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90204A8 RO
	UINT32 vcnt_in_g1                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G1_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90204AC RO
	UINT32 fmc_timer_g1                     :32;	//31:0	//clk count from GSC picinit to FMC first valid
	};
}PE_E60_GSC_G1_Y_FMC_TIMER_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E200 RW
	UINT32 reg_mif_rd_on_g0                 :1;	//0 //'0' : MIF read off (= select FMC direct source)	    '1' : MIF read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g0                 :1;	//1 //'0' : VCP out	    '1' : MIF write
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_mode_g0                  :1;	//3 //'0' : V12TAB filter (active width < 4096)	    '1' : V6TAB filter (active width >= 4096)
	UINT32 reg_adaptive_on_g0               :1;	//4 //N.A
	UINT32 reg_bilinear_on_g0               :1;	//5 //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :2;
	UINT32 blending_range_g0                :2;	//9:8	//N.A
	UINT32 reg_th_g0                        :2;	//11:10	//N.A
	UINT32 reg_th_g1                        :2;	//13:12	//N.A
	UINT32 reg_blur_flag_debug              :1;	//14 //N.A
	UINT32 resvd2                           :10;
	UINT32 reg_v_reverse_sm_g0              :1;	//25 //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd3                           :3;
	UINT32 reg_blur_flag_bypass_g0          :1;	//29 //'0' : normal operation 	     '1' : LSB 1bit blur flag enable mode
	UINT32 reg_mode_32p_g0                  :1;	//30 //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g0             :1;	//31 //'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_GSC_G0_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E204 RW
	UINT32 reg_hsize_g0                     :14;	//13:0	//G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//29:16	//G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//31:30	//V increment for G0 MRD
	};
}PE_E60_GSC_G0_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E208 RW
	UINT32 reg_hosize_g0                    :14;	//13:0	//width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize_g0                    :14;	//29:16	//height
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E20C RW
	UINT32 reg_min_max_on_l_h               :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_min_max_th_l_h               :9;	//12:4	//
	UINT32 adaptive_fir_h_mode              :1;	//13 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd1                           :2;
	UINT32 reg_min_max_on_l_v               :1;	//16 //
	UINT32 resvd2                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//28:20	//
	UINT32 adaptive_fir_v_mode              :1;	//29 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd3                           :1;
	UINT32 reg_v_min_max_extend             :1;	//31 //'0' : 1line window  	 '1' : 3line window
	};
}PE_E60_GSC_G0_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E214 RW
	UINT32 reg_hoffset_g0                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_voffset_g0                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E218 RW
	UINT32 reg_hactive_g0                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_vactive_g0                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E21C RW
	UINT32 reg_hisize_g0                    :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_visize_g0                    :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E220 RW
	UINT32 reg_phase_off_v_g0               :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_E60_GSC_G0_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E224 RW
	UINT32 reg_denominator_h_g0             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h_g0               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E228 RW
	UINT32 reg_denominator_v_g0             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v_g0               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E22C RW
	UINT32 reg_post_hoffset_g0              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset_g0              :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en_g0              :1;	//31 //output crop enable
	};
}PE_E60_GSC_G0_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E230 RW
	UINT32 reg_post_hactive_g0              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive_g0              :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E234 RW
	UINT32 reg_post_hisize_g0               :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize_g0               :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E238 RW
	UINT32 reg_mif_rd_hoffset_g0            :14;	//13:0	//MRD H offset
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_g0            :14;	//29:16	//MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G0_C_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E23C RW
	UINT32 reg_frc_fail_timer_g0            :32;	//31:0	//0 : fail timer off
	};
}PE_E60_GSC_G0_C_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E244 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_C_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E248 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E24C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E250 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E254 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E258 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E25C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E274 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G0_C_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E278 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E27C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E280 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E284 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E288 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E28C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E2A4 RO
	UINT32 vcnt_out_g0                      :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G0_C_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E2A8 RO
	UINT32 vcnt_in_g0                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G0_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E2AC RO
	UINT32 fmc_timer_g0                     :32;	//31:0	//clk count from GSC picinit to FMC first valid
	};
}PE_E60_GSC_G0_C_FMC_TIMER_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E400 RW
	UINT32 reg_mif_rd_on_g1                 :1;	//0 //'0' : MIF read off (= select FMC direct source)	    '1' : MIF read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g1                 :1;	//1 //'0' : VCP out	    '1' : MIF write
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_mode_g1                  :1;	//3 //'0' : V12TAB filter (active width < 2048)	    '1' : V6TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on_g1               :1;	//4 //N.A
	UINT32 reg_bilinear_on_g1               :1;	//5 //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :2;
	UINT32 blending_range_g1                :2;	//9:8	//N.A
	UINT32 reg_th_g0                        :2;	//11:10	//N.A
	UINT32 reg_th_g1                        :2;	//13:12	//N.A
	UINT32 reg_blur_flag_debug              :1;	//14 //N.A
	UINT32 resvd2                           :10;
	UINT32 reg_v_reverse_sm_g1              :1;	//25 //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd3                           :3;
	UINT32 reg_blur_flag_bypass_g1          :1;	//29 //N.A
	UINT32 reg_mode_32p_g1                  :1;	//30 //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g1             :1;	//31 //'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_GSC_G1_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E404 RW
	UINT32 reg_hsize_g1                     :14;	//13:0	//G1 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g1                     :14;	//29:16	//G1 MRd size info. V
	UINT32 reg_vinc_g1                      :2;	//31:30	//V increment for G1 MRD
	};
}PE_E60_GSC_G1_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E408 RW
	UINT32 reg_hosize_g1                    :14;	//13:0	//width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize_g1                    :14;	//29:16	//height
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E40C RW
	UINT32 reg_min_max_on_l_h               :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_min_max_th_l_h               :9;	//12:4	//
	UINT32 adaptive_fir_h_mode              :1;	//13 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd1                           :2;
	UINT32 reg_min_max_on_l_v               :1;	//16 //
	UINT32 resvd2                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//28:20	//
	UINT32 adaptive_fir_v_mode              :1;	//29 //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd3                           :1;
	UINT32 reg_v_min_max_extend             :1;	//31 //'0' : 1line window  	 '1' : 3line window
	};
}PE_E60_GSC_G1_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E414 RW
	UINT32 reg_hoffset_g1                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_voffset_g1                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E418 RW
	UINT32 reg_hactive_g1                   :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_vactive_g1                   :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E41C RW
	UINT32 reg_hisize_g1                    :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_visize_g1                    :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E420 RW
	UINT32 reg_phase_off_v_g1               :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g1               :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_E60_GSC_G1_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E424 RW
	UINT32 reg_denominator_h_g1             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h_g1               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E428 RW
	UINT32 reg_denominator_v_g1             :14;	//13:0	//-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v_g1               :14;	//29:16	//-
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E42C RW
	UINT32 reg_post_hoffset_g1              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset_g1              :14;	//29:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en_g1              :1;	//31 //output crop enable
	};
}PE_E60_GSC_G1_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E430 RW
	UINT32 reg_post_hactive_g1              :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive_g1              :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E434 RW
	UINT32 reg_post_hisize_g1               :14;	//13:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize_g1               :14;	//29:16	//
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E438 RW
	UINT32 reg_mif_rd_hoffset_g1            :14;	//13:0	//MRD H offset
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_g1            :14;	//29:16	//MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_E60_GSC_G1_C_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E43C RW
	UINT32 reg_frc_fail_timer_g1            :32;	//31:0	//0 : fail timer off
	};
}PE_E60_GSC_G1_C_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E444 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G1_C_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E448 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E44C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E450 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E454 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E458 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E45C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E474 WO
	UINT32 update                           :1;	//0 //update
	UINT32 rnw                              :1;	//1 //'0' : write	      '1' : read
	UINT32 addr                             :8;	//9:2	//phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_E60_GSC_G1_C_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E478 RW
	UINT32 y_coefficient0                   :12;	//11:0	//0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//27:16	//1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E47C RW
	UINT32 y_coefficient2                   :12;	//11:0	//2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//27:16	//3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E480 RW
	UINT32 y_coefficient4                   :12;	//11:0	//4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//27:16	//5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E484 RW
	UINT32 y_coefficient6                   :12;	//11:0	//6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//27:16	//7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E488 RW
	UINT32 y_coefficient8                   :12;	//11:0	//8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//27:16	//9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E48C RW
	UINT32 y_coefficient10                  :12;	//11:0	//10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//27:16	//11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E4A4 RO
	UINT32 vcnt_out_g1                      :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G1_C_VCNT_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E4A8 RO
	UINT32 vcnt_in_g1                       :13;	//12:0	//
	UINT32 resvd                            :19;
	};
}PE_E60_GSC_G1_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901E4AC RO
	UINT32 fmc_timer_g1                     :32;	//31:0	//clk count from GSC picinit to FMC first valid
	};
}PE_E60_GSC_G1_C_FMC_TIMER_CNT_T;

typedef struct {
	PE_E60_GSC_G0_Y_CTRL_T                            gsc_g0_y_ctrl;	//0xC9020200
	PE_E60_GSC_G0_Y_MIF_RD_SIZE_T              gsc_g0_y_mif_rd_size;	//0xC9020204
	PE_E60_GSC_G0_Y_OUTSIZE_T                      gsc_g0_y_outsize;	//0xC9020208
	PE_E60_GSC_G0_Y_MIN_MAX_CTRL_T            gsc_g0_y_min_max_ctrl;	//0xC902020C
	UINT32                                                    reserved0;	//0xC9020210
	PE_E60_GSC_G0_Y_CROP_PARAM1_T              gsc_g0_y_crop_param1;	//0xC9020214
	PE_E60_GSC_G0_Y_CROP_PARAM2_T              gsc_g0_y_crop_param2;	//0xC9020218
	PE_E60_GSC_G0_Y_CROP_PARAM3_T              gsc_g0_y_crop_param3;	//0xC902021C
	PE_E60_GSC_G0_Y_PHASE_OFFSET_T            gsc_g0_y_phase_offset;	//0xC9020220
	PE_E60_GSC_G0_Y_SAMPLING_H_T                gsc_g0_y_sampling_h;	//0xC9020224
	PE_E60_GSC_G0_Y_SAMPLING_V_T                gsc_g0_y_sampling_v;	//0xC9020228
	PE_E60_GSC_G0_Y_POST_CROP_PARAM1_T    gsc_g0_y_post_crop_param1;	//0xC902022C
	PE_E60_GSC_G0_Y_POST_CROP_PARAM2_T    gsc_g0_y_post_crop_param2;	//0xC9020230
	PE_E60_GSC_G0_Y_POST_CROP_PARAM3_T    gsc_g0_y_post_crop_param3;	//0xC9020234
	PE_E60_GSC_G0_Y_MIF_RD_HOFFSET_T        gsc_g0_y_mif_rd_hoffset;	//0xC9020238
	PE_E60_GSC_G0_Y_FRC_FAIL_TIMER_T            gsc_g0_frc_fail_timer;	//0xC902023C
	UINT32                                                    reserved1;	//0xC9020240
	PE_E60_GSC_G0_Y_V1_FIR_COEF_CTRL_T    gsc_g0_y_v1_fir_coef_ctrl;	//0xC9020244
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T gsc_g0_y_v1_y_fir_coef_data0;	//0xC9020248
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T gsc_g0_y_v1_y_fir_coef_data1;	//0xC902024C
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T gsc_g0_y_v1_y_fir_coef_data2;	//0xC9020250
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T gsc_g0_y_v1_y_fir_coef_data3;	//0xC9020254
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T gsc_g0_y_v1_y_fir_coef_data4;	//0xC9020258
	PE_E60_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T gsc_g0_y_v1_y_fir_coef_data5;	//0xC902025C
	PE_E60_GSC_G0_Y_V2_FIR_COEF_CTRL_T    gsc_g0_y_v2_fir_coef_ctrl;	//0xC9020260
	PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T gsc_g0_y_v2_y_fir_coef_data0;	//0xC9020264
	PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T gsc_g0_y_v2_y_fir_coef_data1;	//0xC9020268
	PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T gsc_g0_y_v2_y_fir_coef_data2;	//0xC902026C
	PE_E60_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T gsc_g0_y_v2_y_fir_coef_data3;	//0xC9020270
	PE_E60_GSC_G0_Y_H1_FIR_COEF_CTRL_T    gsc_g0_y_h1_fir_coef_ctrl;	//0xC9020274
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T gsc_g0_y_h1_y_fir_coef_data0;	//0xC9020278
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T gsc_g0_y_h1_y_fir_coef_data1;	//0xC902027C
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T gsc_g0_y_h1_y_fir_coef_data2;	//0xC9020280
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T gsc_g0_y_h1_y_fir_coef_data3;	//0xC9020284
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T gsc_g0_y_h1_y_fir_coef_data4;	//0xC9020288
	PE_E60_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T gsc_g0_y_h1_y_fir_coef_data5;	//0xC902028C
	PE_E60_GSC_G0_Y_H2_FIR_COEF_CTRL_T    gsc_g0_y_h2_fir_coef_ctrl;	//0xC9020290
	PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T gsc_g0_y_h2_y_fir_coef_data0;	//0xC9020294
	PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T gsc_g0_y_h2_y_fir_coef_data1;	//0xC9020298
	PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T gsc_g0_y_h2_y_fir_coef_data2;	//0xC902029C
	PE_E60_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T gsc_g0_y_h2_y_fir_coef_data3;	//0xC90202A0
	PE_E60_GSC_G0_Y_VCNT_OUT_T                    gsc_g0_y_vcnt_out;	//0xC90202A4
	PE_E60_GSC_G0_Y_VCNT_IN_T                      gsc_g0_y_vcnt_in;	//0xC90202A8
	PE_E60_GSC_G0_Y_FMC_TIMER_CNT_T          gsc_g0_y_fmc_timer_cnt;	//0xC90202AC
	UINT32                                             reserved[84];    //0xC90202B0~0xC90203FC
	PE_E60_GSC_G1_Y_CTRL_T                            gsc_g1_y_ctrl;	//0xC9020400
	PE_E60_GSC_G1_Y_MIF_RD_SIZE_T              gsc_g1_y_mif_rd_size;	//0xC9020404
	PE_E60_GSC_G1_Y_OUTSIZE_T                      gsc_g1_y_outsize;	//0xC9020408
	PE_E60_GSC_G1_Y_MIN_MAX_CTRL_T            gsc_g1_y_min_max_ctrl;	//0xC902040C
	UINT32                                                    reserved2;	//0xC9020410
	PE_E60_GSC_G1_Y_CROP_PARAM1_T              gsc_g1_y_crop_param1;	//0xC9020414
	PE_E60_GSC_G1_Y_CROP_PARAM2_T              gsc_g1_y_crop_param2;	//0xC9020418
	PE_E60_GSC_G1_Y_CROP_PARAM3_T              gsc_g1_y_crop_param3;	//0xC902041C
	PE_E60_GSC_G1_Y_PHASE_OFFSET_T            gsc_g1_y_phase_offset;	//0xC9020420
	PE_E60_GSC_G1_Y_SAMPLING_H_T                gsc_g1_y_sampling_h;	//0xC9020424
	PE_E60_GSC_G1_Y_SAMPLING_V_T                gsc_g1_y_sampling_v;	//0xC9020428
	PE_E60_GSC_G1_Y_POST_CROP_PARAM1_T    gsc_g1_y_post_crop_param1;	//0xC902042C
	PE_E60_GSC_G1_Y_POST_CROP_PARAM2_T    gsc_g1_y_post_crop_param2;	//0xC9020430
	PE_E60_GSC_G1_Y_POST_CROP_PARAM3_T    gsc_g1_y_post_crop_param3;	//0xC9020434
	PE_E60_GSC_G1_Y_MIF_RD_HOFFSET_T        gsc_g1_y_mif_rd_hoffset;	//0xC9020438
	PE_E60_GSC_G1_Y_FRC_FAIL_TIMER_T            gsc_g1_frc_fail_timer;	//0xC902043C
	UINT32                                                    reserved3;	//0xC9020440
	PE_E60_GSC_G1_Y_V1_FIR_COEF_CTRL_T    gsc_g1_y_v1_fir_coef_ctrl;	//0xC9020444
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA0_T gsc_g1_y_v1_y_fir_coef_data0;	//0xC9020448
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA1_T gsc_g1_y_v1_y_fir_coef_data1;	//0xC902044C
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA2_T gsc_g1_y_v1_y_fir_coef_data2;	//0xC9020450
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA3_T gsc_g1_y_v1_y_fir_coef_data3;	//0xC9020454
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA4_T gsc_g1_y_v1_y_fir_coef_data4;	//0xC9020458
	PE_E60_GSC_G1_Y_V1_Y_FIR_COEF_DATA5_T gsc_g1_y_v1_y_fir_coef_data5;	//0xC902045C
	UINT32                                                    reserved4;	//0xC9020460
	UINT32                                                    reserved5;	//0xC9020464
	UINT32                                                    reserved6;	//0xC9020468
	UINT32                                                    reserved7;	//0xC902046C
	UINT32                                                    reserved8;	//0xC9020470
	PE_E60_GSC_G1_Y_H1_FIR_COEF_CTRL_T    gsc_g1_y_h1_fir_coef_ctrl;	//0xC9020474
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA0_T gsc_g1_y_h1_y_fir_coef_data0;	//0xC9020478
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA1_T gsc_g1_y_h1_y_fir_coef_data1;	//0xC902047C
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA2_T gsc_g1_y_h1_y_fir_coef_data2;	//0xC9020480
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA3_T gsc_g1_y_h1_y_fir_coef_data3;	//0xC9020484
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA4_T gsc_g1_y_h1_y_fir_coef_data4;	//0xC9020488
	PE_E60_GSC_G1_Y_H1_Y_FIR_COEF_DATA5_T gsc_g1_y_h1_y_fir_coef_data5;	//0xC902048C
	UINT32                                                   reserved9;	//0xC9020490
	UINT32                                                   reserved10;	//0xC9020494
	UINT32                                                   reserved11;	//0xC9020498
	UINT32                                                   reserved12;	//0xC902049C
	UINT32                                                   reserved13;	//0xC90204A0
	PE_E60_GSC_G1_Y_VCNT_OUT_T                    gsc_g1_y_vcnt_out;	//0xC90204A4
	PE_E60_GSC_G1_Y_VCNT_IN_T                      gsc_g1_y_vcnt_in;	//0xC90204A8
	PE_E60_GSC_G1_Y_FMC_TIMER_CNT_T          gsc_g1_y_fmc_timer_cnt;	//0xC90204AC
}PE_GSC_Y_REG_E60_T;

typedef struct {
	PE_E60_GSC_G0_C_CTRL_T                            gsc_g0_c_ctrl;	//0xC901E200
	PE_E60_GSC_G0_C_MIF_RD_SIZE_T              gsc_g0_c_mif_rd_size;	//0xC901E204
	PE_E60_GSC_G0_C_OUTSIZE_T                      gsc_g0_c_outsize;	//0xC901E208
	PE_E60_GSC_G0_C_MIN_MAX_CTRL_T            gsc_g0_c_min_max_ctrl;	//0xC901E20C
	UINT32                                                    reserved0;	//0xC901E210
	PE_E60_GSC_G0_C_CROP_PARAM1_T              gsc_g0_c_crop_param1;	//0xC901E214
	PE_E60_GSC_G0_C_CROP_PARAM2_T              gsc_g0_c_crop_param2;	//0xC901E218
	PE_E60_GSC_G0_C_CROP_PARAM3_T              gsc_g0_c_crop_param3;	//0xC901E21C
	PE_E60_GSC_G0_C_PHASE_OFFSET_T            gsc_g0_c_phase_offset;	//0xC901E220
	PE_E60_GSC_G0_C_SAMPLING_H_T                gsc_g0_c_sampling_h;	//0xC901E224
	PE_E60_GSC_G0_C_SAMPLING_V_T                gsc_g0_c_sampling_v;	//0xC901E228
	PE_E60_GSC_G0_C_POST_CROP_PARAM1_T    gsc_g0_c_post_crop_param1;	//0xC901E22C
	PE_E60_GSC_G0_C_POST_CROP_PARAM2_T    gsc_g0_c_post_crop_param2;	//0xC901E230
	PE_E60_GSC_G0_C_POST_CROP_PARAM3_T    gsc_g0_c_post_crop_param3;	//0xC901E234
	PE_E60_GSC_G0_C_MIF_RD_HOFFSET_T        gsc_g0_c_mif_rd_hoffset;	//0xC901E238
	PE_E60_GSC_G0_C_FRC_FAIL_TIMER_T            gsc_g0_frc_fail_timer;	//0xC901E23C
	UINT32                                                    reserved1;	//0xC901E240
	PE_E60_GSC_G0_C_V1_FIR_COEF_CTRL_T    gsc_g0_c_v1_fir_coef_ctrl;	//0xC901E244
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T gsc_g0_c_v1_y_fir_coef_data0;	//0xC901E248
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T gsc_g0_c_v1_y_fir_coef_data1;	//0xC901E24C
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T gsc_g0_c_v1_y_fir_coef_data2;	//0xC901E250
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T gsc_g0_c_v1_y_fir_coef_data3;	//0xC901E254
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T gsc_g0_c_v1_y_fir_coef_data4;	//0xC901E258
	PE_E60_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T gsc_g0_c_v1_y_fir_coef_data5;	//0xC901E25C
	UINT32                                                    reserved2;	//0xC901E260
	UINT32                                                    reserved3;	//0xC901E264
	UINT32                                                    reserved4;	//0xC901E268
	UINT32                                                    reserved5;	//0xC901E26C
	UINT32                                                    reserved6;	//0xC901E270
	PE_E60_GSC_G0_C_H1_FIR_COEF_CTRL_T    gsc_g0_c_h1_fir_coef_ctrl;	//0xC901E274
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T gsc_g0_c_h1_y_fir_coef_data0;	//0xC901E278
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T gsc_g0_c_h1_y_fir_coef_data1;	//0xC901E27C
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T gsc_g0_c_h1_y_fir_coef_data2;	//0xC901E280
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T gsc_g0_c_h1_y_fir_coef_data3;	//0xC901E284
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T gsc_g0_c_h1_y_fir_coef_data4;	//0xC901E288
	PE_E60_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T gsc_g0_c_h1_y_fir_coef_data5;	//0xC901E28C
	UINT32                                                    reserved7;	//0xC901E290
	UINT32                                                    reserved8;	//0xC901E294
	UINT32                                                    reserved9;	//0xC901E298
	UINT32                                                   reserved10;	//0xC901E29C
	UINT32                                                   reserved11;	//0xC901E2A0
	PE_E60_GSC_G0_C_VCNT_OUT_T                    gsc_g0_c_vcnt_out;	//0xC901E2A4
	PE_E60_GSC_G0_C_VCNT_IN_T                      gsc_g0_c_vcnt_in;	//0xC901E2A8
	PE_E60_GSC_G0_C_FMC_TIMER_CNT_T          gsc_g0_c_fmc_timer_cnt;	//0xC901E2AC
	UINT32                                             reserved[84];	//0xC901E2B0~0xC901E3FC
	PE_E60_GSC_G1_C_CTRL_T                            gsc_g1_c_ctrl;	//0xC901E400
	PE_E60_GSC_G1_C_MIF_RD_SIZE_T              gsc_g1_c_mif_rd_size;	//0xC901E404
	PE_E60_GSC_G1_C_OUTSIZE_T                      gsc_g1_c_outsize;	//0xC901E408
	PE_E60_GSC_G1_C_MIN_MAX_CTRL_T            gsc_g1_c_min_max_ctrl;	//0xC901E40C
	UINT32                                                   reserved12;	//0xC901E410
	PE_E60_GSC_G1_C_CROP_PARAM1_T              gsc_g1_c_crop_param1;	//0xC901E414
	PE_E60_GSC_G1_C_CROP_PARAM2_T              gsc_g1_c_crop_param2;	//0xC901E418
	PE_E60_GSC_G1_C_CROP_PARAM3_T              gsc_g1_c_crop_param3;	//0xC901E41C
	PE_E60_GSC_G1_C_PHASE_OFFSET_T            gsc_g1_c_phase_offset;	//0xC901E420
	PE_E60_GSC_G1_C_SAMPLING_H_T                gsc_g1_c_sampling_h;	//0xC901E424
	PE_E60_GSC_G1_C_SAMPLING_V_T                gsc_g1_c_sampling_v;	//0xC901E428
	PE_E60_GSC_G1_C_POST_CROP_PARAM1_T    gsc_g1_c_post_crop_param1;	//0xC901E42C
	PE_E60_GSC_G1_C_POST_CROP_PARAM2_T    gsc_g1_c_post_crop_param2;	//0xC901E430
	PE_E60_GSC_G1_C_POST_CROP_PARAM3_T    gsc_g1_c_post_crop_param3;	//0xC901E434
	PE_E60_GSC_G1_C_MIF_RD_HOFFSET_T        gsc_g1_c_mif_rd_hoffset;	//0xC901E438
	PE_E60_GSC_G1_C_FRC_FAIL_TIMER_T            gsc_g1_frc_fail_timer;	//0xC901E43C
	UINT32                                                   reserved13;	//0xC901E440
	PE_E60_GSC_G1_C_V1_FIR_COEF_CTRL_T    gsc_g1_c_v1_fir_coef_ctrl;	//0xC901E444
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA0_T gsc_g1_c_v1_y_fir_coef_data0;	//0xC901E448
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA1_T gsc_g1_c_v1_y_fir_coef_data1;	//0xC901E44C
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA2_T gsc_g1_c_v1_y_fir_coef_data2;	//0xC901E450
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA3_T gsc_g1_c_v1_y_fir_coef_data3;	//0xC901E454
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA4_T gsc_g1_c_v1_y_fir_coef_data4;	//0xC901E458
	PE_E60_GSC_G1_C_V1_Y_FIR_COEF_DATA5_T gsc_g1_c_v1_y_fir_coef_data5;	//0xC901E45C
	UINT32                                                   reserved14;	//0xC901E460
	UINT32                                                   reserved15;	//0xC901E464
	UINT32                                                   reserved16;	//0xC901E468
	UINT32                                                   reserved17;	//0xC901E46C
	UINT32                                                   reserved18;	//0xC901E470
	PE_E60_GSC_G1_C_H1_FIR_COEF_CTRL_T    gsc_g1_c_h1_fir_coef_ctrl;	//0xC901E474
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA0_T gsc_g1_c_h1_y_fir_coef_data0;	//0xC901E478
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA1_T gsc_g1_c_h1_y_fir_coef_data1;	//0xC901E47C
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA2_T gsc_g1_c_h1_y_fir_coef_data2;	//0xC901E480
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA3_T gsc_g1_c_h1_y_fir_coef_data3;	//0xC901E484
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA4_T gsc_g1_c_h1_y_fir_coef_data4;	//0xC901E488
	PE_E60_GSC_G1_C_H1_Y_FIR_COEF_DATA5_T gsc_g1_c_h1_y_fir_coef_data5;	//0xC901E48C
	UINT32                                                   reserved19;	//0xC901E490
	UINT32                                                   reserved20;	//0xC901E494
	UINT32                                                   reserved21;	//0xC901E498
	UINT32                                                   reserved22;	//0xC901E49C
	UINT32                                                   reserved23;	//0xC901E4A0
	PE_E60_GSC_G1_C_VCNT_OUT_T                    gsc_g1_c_vcnt_out;	//0xC901E4A4
	PE_E60_GSC_G1_C_VCNT_IN_T                      gsc_g1_c_vcnt_in;	//0xC901E4A8
	PE_E60_GSC_G1_C_FMC_TIMER_CNT_T          gsc_g1_c_fmc_timer_cnt;	//0xC901E4AC
}PE_GSC_C_REG_E60_T;
#endif
