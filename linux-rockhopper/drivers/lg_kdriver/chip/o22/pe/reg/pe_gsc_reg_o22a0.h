#ifndef _PE_GSC_REG_O22A0_1_H_
#define _PE_GSC_REG_O22A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC500500 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g0                 :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select FMC direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g0                 :1;	//(1,NA,0x0) //'0' : VCP out	    '1' : MIF write
	UINT32 reg_spectacle_en_g0              :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode_g0                  :1;	//(3,NA,0x0) //'0' : V12TAB filter (active width < 2048)	    '1' : V6TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on_g0               :1;	//(4,NA,0x0) //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on_g0               :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd0                           :2;
	UINT32 blending_range_g0                :2;	//(9:8,NA,0x0) //blending range of adaptive filter
	UINT32 reg_th0_g0                       :2;	//(11:10,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th1_g0                       :2;	//(13:12,NA,0x0) //threshold of adaptive filter
	UINT32 reg_blur_flag_debug_g0           :1;	//(14,NA,0x0) //for debug	1:data MSB flag swap out
	UINT32 reg_blur_flag_bypass_g0          :1;	//(15,NA,0x0) //'0' : normal operation 	     '1' : LSB 1bit blur flag enable mode
	UINT32 vsc_buffer_mode                  :1;	//(16,NA,0x0) //0: vsc_mode	1: buffer_mode
	UINT32 hsc_detour_mode                  :1;	//(17,NA,0x0) //0: hsc_mode	1: detour_mode
	UINT32 h_repeat_mode                    :2;	//(19:18,NA,0x0) //0: detour	1: 2 repeat	2: 4 repeat	3: 8 repeat
	UINT32 resvd1                           :5;
	UINT32 reg_v_reverse_sm_g0              :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd2                           :4;
	UINT32 reg_mode_32p_g0                  :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g0             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}REG_GSC_Y_GSC_G0_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500504 RW 0x0000_0000
	UINT32 reg_hsize_g0                     :14;	//(13:0,NA,0x0) //G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//(29:16,NA,0x0) //G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//(31:30,NA,0x0) //V increment for G0 MRD
	};
}REG_GSC_Y_GSC_G0_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500508 RW 0x0870_0F00
	UINT32 reg_hosize_g0                    :13;	//(12:0,NA,0xF00) //width
	UINT32 resvd0                           :3;
	UINT32 reg_vosize_g0                    :13;	//(28:16,NA,0x870) //height
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50050C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_min_max_th_l_h               :9;	//(12:4,NA,0x0) //
	UINT32 adaptive_fir_h_mode              :1;	//(13,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd1                           :2;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd3                           :1;
	UINT32 reg_v_min_max_extend             :1;	//(31,NA,0x0) //'0' : 1line window  	 '1' : 3line window
	};
}REG_GSC_Y_GSC_G0_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500510 RW VNA
	UINT32 lmux_sel                         :1;	//(0,NA,0x0) //Left input mux select	    '0': G0 MIF RD 	    '1': Disp FMC
	UINT32 rmux_sel                         :1;	//(1,NA,0x0) //Right input mux select	    '0': G1 MIF RD 	    '1': Disp FMC
	UINT32 inverse_en                       :1;	//(2,NA,0x0) //Input Switch reverse ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC1   /   Right MUX -> GSC0
	UINT32 l_share_en                       :1;	//(3,NA,0x0) //Input Switch share ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC0   /   Left  MUX -> GSC1
	UINT32 r_share_en                       :1;	//(4,NA,0x0) //Input Switch share ctrl	    '0': Left  MUX -> GSC0   /   Right MUX -> GSC1	    '1': Right MUX -> GSC0   /   Right MUX -> GSC1
	UINT32 share_flow_ctrl_en               :1;	//(5,NA,0x0) //flow control enable for share mode
	UINT32 lmux_sel2                        :1;	//(6,NA,0x0) //Left input mux2 select	    '0': output of lmux	    '1': gpd0
	UINT32 rmux_sel2                        :1;	//(7,NA,0x0) //Right input mux2 select	    '0': output of rmux	    '1': gpd1
	UINT32 resvd                            :24;
	};
}REG_GSC_Y_GSC_G0_Y_INPUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500514 RW 0x0000_0000
	UINT32 reg_hoffset_g0                   :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset_g0                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500518 RW 0x0870_0F00
	UINT32 reg_hactive_g0                   :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive_g0                   :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50051C RW 0x0870_0F00
	UINT32 reg_hisize_g0                    :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500520 RW 0x0000_0000
	UINT32 reg_phase_off_v_g0               :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}REG_GSC_Y_GSC_G0_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500524 RW 0x0000_0000
	UINT32 reg_denominator_h_g0             :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500528 RW 0x0000_0000
	UINT32 reg_denominator_v_g0             :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50052C RW 0x0000_0000
	UINT32 reg_post_hoffset_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en_g0              :1;	//(31,NA,0x0) //output crop enable
	};
}REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500530 RW 0x0000_0000
	UINT32 reg_post_hactive_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500534 RW 0x0000_0000
	UINT32 reg_post_hisize_g0               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize_g0               :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500538 RW 0x0000_0000
	UINT32 reg_mif_rd_hoffset_g0            :13;	//(12:0,NA,0x0) //MRD H offset
	UINT32 resvd0                           :3;
	UINT32 reg_mif_rd_voffset_g0            :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G0_Y_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50053C RW 0x0000_0000
	UINT32 reg_frc_fail_timer_g0            :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}REG_GSC_Y_GSC_G0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500540 WO 0x0000_0000
	UINT32 reg_8k_detour_en                 :1;	//(0,NA,0x0) //8k detour enable
	UINT32 reg_5k_scaler_en                 :1;	//(1,NA,0x0) //5120->3840 pre h scaler enable
	UINT32 resvd                            :3;
	UINT32 pre_filter_coef0                 :9;	//(13:5,NA,0x0) //pre filter coefficient0
	UINT32 pre_filter_coef1                 :9;	//(22:14,NA,0x0) //pre filter coefficient1 (center , sum of coefs should be 256)
	UINT32 pre_filter_coef2                 :9;	//(31:23,NA,0x0) //pre filter coefficient2
	};
}REG_GSC_Y_GSC_G0_Y_5K_8K_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500544 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_Y_GSC_G0_Y_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500548 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50054C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500550 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500554 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500558 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50055C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500560 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_Y_GSC_G0_Y_V2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500564 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500568 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50056C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500570 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500574 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_Y_GSC_G0_Y_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500578 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50057C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500580 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500584 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500588 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50058C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500590 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_Y_GSC_G0_Y_H2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500594 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500598 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50059C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5005A0 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5005A4 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g1                 :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select ND direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 reg_mif_wr_on_g1                 :1;	//(1,NA,0x0) //'0' : VCP out	    '1' : MIF write
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode_g1                  :1;	//(3,NA,0x0) //'0' : V12TAB filter (active width < 2048)	    '1' : V6TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on_g1               :1;	//(4,NA,0x0) //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on_g1               :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd0                           :10;
	UINT32 vsc_buffer_mode                  :1;	//(16,NA,0x0) //0: vsc_mode	1: buffer_mode
	UINT32 hsc_detour_mode                  :1;	//(17,NA,0x0) //0: hsc_mode	1: detour_mode
	UINT32 h_repeat_mode                    :2;	//(19:18,NA,0x0) //0: detour	1: 2 repeat	2: 4 repeat	3: 8 repeat
	UINT32 resvd1                           :5;
	UINT32 reg_v_reverse_sm_g1              :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd2                           :4;
	UINT32 reg_mode_32p_g1                  :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode_g1             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}REG_GSC_Y_GSC_G1_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5005A8 RW 0x0000_0000
	UINT32 reg_hsize_g1                     :14;	//(13:0,NA,0x0) //G1 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g1                     :14;	//(29:16,NA,0x0) //G1 MRd size info. V
	UINT32 reg_vinc_g1                      :2;	//(31:30,NA,0x0) //V increment for G1 MRD
	};
}REG_GSC_Y_GSC_G1_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5005AC RW 0x0870_0F00
	UINT32 reg_hosize_g1                    :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vosize_g1                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_Y_GSC_G1_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5005B0 RW 0x0000_0000
	UINT32 reg_h_min_max_en_g1              :1;	//(0,NA,0x0) //'0' : horizontal overshoot protection off	     '1' : horizontal overshoot protection on
	UINT32 resvd0                           :15;
	UINT32 reg_v_min_max_en_g1              :1;	//(16,NA,0x0) //'0' : vertical overshoot protection off	     '1' : vertical overshoot protection on
	UINT32 resvd1                           :15;
	};
}REG_GSC_Y_GSC_G1_Y_MIN_MAX_CTRL_T;

typedef struct {
	REG_GSC_Y_GSC_G0_Y_CTRL_T                             gsc_g0_y_ctrl;	//0xCC500500
	REG_GSC_Y_GSC_G0_Y_MIF_RD_SIZE_T               gsc_g0_y_mif_rd_size;	//0xCC500504
	REG_GSC_Y_GSC_G0_Y_OUTSIZE_T                       gsc_g0_y_outsize;	//0xCC500508
	REG_GSC_Y_GSC_G0_Y_MIN_MAX_CTRL_T             gsc_g0_y_min_max_ctrl;	//0xCC50050C
	REG_GSC_Y_GSC_G0_Y_INPUT_MUX_T                   gsc_g0_y_input_mux;	//0xCC500510
	REG_GSC_Y_GSC_G0_Y_CROP_PARAM1_T               gsc_g0_y_crop_param1;	//0xCC500514
	REG_GSC_Y_GSC_G0_Y_CROP_PARAM2_T               gsc_g0_y_crop_param2;	//0xCC500518
	REG_GSC_Y_GSC_G0_Y_CROP_PARAM3_T               gsc_g0_y_crop_param3;	//0xCC50051C
	REG_GSC_Y_GSC_G0_Y_PHASE_OFFSET_T             gsc_g0_y_phase_offset;	//0xCC500520
	REG_GSC_Y_GSC_G0_Y_SAMPLING_H_T                 gsc_g0_y_sampling_h;	//0xCC500524
	REG_GSC_Y_GSC_G0_Y_SAMPLING_V_T                 gsc_g0_y_sampling_v;	//0xCC500528
	REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM1_T     gsc_g0_y_post_crop_param1;	//0xCC50052C
	REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM2_T     gsc_g0_y_post_crop_param2;	//0xCC500530
	REG_GSC_Y_GSC_G0_Y_POST_CROP_PARAM3_T     gsc_g0_y_post_crop_param3;	//0xCC500534
	REG_GSC_Y_GSC_G0_Y_MIF_RD_HOFFSET_T         gsc_g0_y_mif_rd_hoffset;	//0xCC500538
	REG_GSC_Y_GSC_G0_FRC_FAIL_TIMER_T             gsc_g0_frc_fail_timer;	//0xCC50053C
	REG_GSC_Y_GSC_G0_Y_5K_8K_CTRL_T                 gsc_g0_y_5k_8k_ctrl;	//0xCC500540
	REG_GSC_Y_GSC_G0_Y_V1_FIR_COEF_CTRL_T     gsc_g0_y_v1_fir_coef_ctrl;	//0xCC500544
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA0_T gsc_g0_y_v1_y_fir_coef_data0;	//0xCC500548
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA1_T gsc_g0_y_v1_y_fir_coef_data1;	//0xCC50054C
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA2_T gsc_g0_y_v1_y_fir_coef_data2;	//0xCC500550
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA3_T gsc_g0_y_v1_y_fir_coef_data3;	//0xCC500554
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA4_T gsc_g0_y_v1_y_fir_coef_data4;	//0xCC500558
	REG_GSC_Y_GSC_G0_Y_V1_Y_FIR_COEF_DATA5_T gsc_g0_y_v1_y_fir_coef_data5;	//0xCC50055C
	REG_GSC_Y_GSC_G0_Y_V2_FIR_COEF_CTRL_T     gsc_g0_y_v2_fir_coef_ctrl;	//0xCC500560
	REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA0_T gsc_g0_y_v2_y_fir_coef_data0;	//0xCC500564
	REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA1_T gsc_g0_y_v2_y_fir_coef_data1;	//0xCC500568
	REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA2_T gsc_g0_y_v2_y_fir_coef_data2;	//0xCC50056C
	REG_GSC_Y_GSC_G0_Y_V2_Y_FIR_COEF_DATA3_T gsc_g0_y_v2_y_fir_coef_data3;	//0xCC500570
	REG_GSC_Y_GSC_G0_Y_H1_FIR_COEF_CTRL_T     gsc_g0_y_h1_fir_coef_ctrl;	//0xCC500574
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA0_T gsc_g0_y_h1_y_fir_coef_data0;	//0xCC500578
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA1_T gsc_g0_y_h1_y_fir_coef_data1;	//0xCC50057C
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA2_T gsc_g0_y_h1_y_fir_coef_data2;	//0xCC500580
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA3_T gsc_g0_y_h1_y_fir_coef_data3;	//0xCC500584
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA4_T gsc_g0_y_h1_y_fir_coef_data4;	//0xCC500588
	REG_GSC_Y_GSC_G0_Y_H1_Y_FIR_COEF_DATA5_T gsc_g0_y_h1_y_fir_coef_data5;	//0xCC50058C
	REG_GSC_Y_GSC_G0_Y_H2_FIR_COEF_CTRL_T     gsc_g0_y_h2_fir_coef_ctrl;	//0xCC500590
	REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA0_T gsc_g0_y_h2_y_fir_coef_data0;	//0xCC500594
	REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA1_T gsc_g0_y_h2_y_fir_coef_data1;	//0xCC500598
	REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA2_T gsc_g0_y_h2_y_fir_coef_data2;	//0xCC50059C
	REG_GSC_Y_GSC_G0_Y_H2_Y_FIR_COEF_DATA3_T gsc_g0_y_h2_y_fir_coef_data3;	//0xCC5005A0
	REG_GSC_Y_GSC_G1_Y_CTRL_T                             gsc_g1_y_ctrl;	//0xCC5005A4
	REG_GSC_Y_GSC_G1_Y_MIF_RD_SIZE_T               gsc_g1_y_mif_rd_size;	//0xCC5005A8
	REG_GSC_Y_GSC_G1_Y_OUTSIZE_T                       gsc_g1_y_outsize;	//0xCC5005AC
	REG_GSC_Y_GSC_G1_Y_MIN_MAX_CTRL_T             gsc_g1_y_min_max_ctrl;	//0xCC5005B0
}PE_GSC_Y_REG_O22_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC500800 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g0                 :1;	//(0,NA,0x0) //1이면 M1 MRd_2pel on & select mrd path (size 정보 필요)
	UINT32 reg_mif_wr_on_g0                 :1;	//(1,NA,0x0) //'0' : VCP out	    '1' : MIF write
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode_g0                  :2;	//(4:3,NA,0x0) //reg_hactive_g0 기준으로 	0~1023 는 00, 01, 11 지원	1024~2047 는 01, 11	2048~ 는 11 만 지원	00 : V12T / 01: V6T / 11: V2T(bilinear)
	UINT32 reg_bilinear_on_g0               :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 reg_mode_32p_g0                  :1;	//(6,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 resvd0                           :9;
	UINT32 vsc_buffer_mode                  :1;	//(16,NA,0x0) //0: vsc_mode	1: buffer_mode
	UINT32 hsc_detour_mode                  :1;	//(17,NA,0x0) //0: hsc_mode	1: detour_mode
	UINT32 h_repeat_mode                    :2;	//(19:18,NA,0x0) //0: detour	1: 2 repeat	2: 4 repeat	3: 8 repeat
	UINT32 resvd1                           :5;
	UINT32 reg_v_reverse_g0                 :1;	//(25,NA,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_v_cti_en_g0                  :1;	//(28,NA,0x0) //
	UINT32 reg_v_cti_ratio_g0               :2;	//(30:29,NA,0x0) //
	UINT32 reg_sampling_mode_g0             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}REG_GSC_C_GSC_G0_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500804 RW 0x0000_0000
	UINT32 reg_hsize_g0                     :14;	//(13:0,NA,0x0) //G0 MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize_g0                     :14;	//(29:16,NA,0x0) //G0 MRd size info. V
	UINT32 reg_vinc_g0                      :2;	//(31:30,NA,0x0) //V increment for G0 MRD
	};
}REG_GSC_C_GSC_G0_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500808 RW 0x0870_0F00
	UINT32 reg_hosize_g0                    :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vosize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50080C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}REG_GSC_C_GSC_G0_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500810 RW VNA
	UINT32 lmux_sel                         :1;	//(0,NA,0x0) //Left input mux select	    '0': G0 MIF RD 	    '1': Disp FMC
	UINT32 rmux_sel                         :1;	//(1,NA,0x0) //Right input mux select	    '0': G1 MIF RD 	    '1': Disp FMC
	UINT32 inverse_en                       :1;	//(2,NA,0x0) //Input Switch reverse ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC1   /   Right MUX -> GSC0
	UINT32 l_share_en                       :1;	//(3,NA,0x0) //Input Switch share ctrl	    '0': Left MUX -> GSC0   /   Right MUX -> GSC1	    '1': Left MUX -> GSC0   /   Left  MUX -> GSC1
	UINT32 r_share_en                       :1;	//(4,NA,0x0) //Input Switch share ctrl	    '0': Left  MUX -> GSC0   /   Right MUX -> GSC1	    '1': Right MUX -> GSC0   /   Right MUX -> GSC1
	UINT32 share_flow_ctrl_en               :1;	//(5,NA,0x0) //flow control enable for share mode
	UINT32 lmux_sel2                        :1;	//(6,NA,0x0) //Left input mux2 select	    '0': output of lmux	    '1': gpd0
	UINT32 rmux_sel2                        :1;	//(7,NA,0x0) //Right input mux2 select	    '0': output of rmux	    '1': gpd1
	UINT32 resvd                            :24;
	};
}REG_GSC_C_GSC_G0_C_INPUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500814 RW 0x0000_0000
	UINT32 reg_hoffset_g0                   :13;	//(12:0,NA,0x0) //오프셋
	UINT32 resvd0                           :3;
	UINT32 reg_voffset_g0                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500818 RW 0x0870_0F00
	UINT32 reg_hactive_g0                   :13;	//(12:0,NA,0xF00) //액티브
	UINT32 resvd0                           :3;
	UINT32 reg_vactive_g0                   :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50081C RW 0x0870_0F00
	UINT32 reg_hisize_g0                    :13;	//(12:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :3;
	UINT32 reg_visize_g0                    :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500820 RW 0x0000_0000
	UINT32 reg_phase_off_v_g0               :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h_g0               :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}REG_GSC_C_GSC_G0_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500824 RW 0x0000_0000
	UINT32 reg_denominator_h_g0             :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500828 RW 0x0000_0000
	UINT32 reg_denominator_v_g0             :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v_g0               :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50082C RW 0x0000_0000
	UINT32 reg_post_hoffset_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en_g0              :1;	//(31,NA,0x0) //output crop enable
	};
}REG_GSC_C_GSC_G0_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500830 RW 0x0000_0000
	UINT32 reg_post_hactive_g0              :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive_g0              :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500834 RW 0x0000_0000
	UINT32 reg_post_hisize_g0               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize_g0               :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500838 RW 0x0000_0000
	UINT32 reg_mif_rd_hoffset_g0            :13;	//(12:0,NA,0x0) //MRD H offset
	UINT32 resvd0                           :3;
	UINT32 reg_mif_rd_voffset_g0            :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :3;
	};
}REG_GSC_C_GSC_G0_C_MIF_RD_HOFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50083C RW 0x0000_0000
	UINT32 reg_frc_fail_timer_g0            :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}REG_GSC_C_GSC_G0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500840 WO 0x0000_0000
	UINT32 reg_8k_detour_en                 :1;	//(0,NA,0x0) //8k detour enable
	UINT32 reg_5k_scaler_en                 :1;	//(1,NA,0x0) //5120->3840 pre h scaler enable
	UINT32 resvd                            :3;
	UINT32 pre_filter_coef0                 :9;	//(13:5,NA,0x0) //pre filter coefficient0
	UINT32 pre_filter_coef1                 :9;	//(22:14,NA,0x0) //pre filter coefficient1 (center , sum of coefs should be 256)
	UINT32 pre_filter_coef2                 :9;	//(31:23,NA,0x0) //pre filter coefficient2
	};
}REG_GSC_C_GSC_G0_C_5K_8K_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500844 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_C_GSC_G0_C_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500848 RW 0x0000_0000
	UINT32 y_coefficient0_v1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1_v1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50084C RW 0x0000_0000
	UINT32 y_coefficient2_v1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3_v1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500850 RW 0x0000_0000
	UINT32 y_coefficient4_v1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5_v1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500854 RW 0x0000_0000
	UINT32 y_coefficient6_v1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7_v1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500858 RW 0x0000_0000
	UINT32 y_coefficient8_v1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9_v1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50085C RW 0x0000_0000
	UINT32 y_coefficient10_v1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11_v1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500874 WO 0x0000_0000
	UINT32 update_h1                        :1;	//(0:0,NA,0x0) //update
	UINT32 rnw_h1                           :1;	//(1:1,NA,0x0) //0: write	1: read
	UINT32 addr_h1                          :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}REG_GSC_C_GSC_G0_C_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500878 RW 0x0000_0000
	UINT32 y_coefficient0_h1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1_h1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50087C RW 0x0000_0000
	UINT32 y_coefficient2_h1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3_h1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500880 RW 0x0000_0000
	UINT32 y_coefficient4_h1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5_h1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500884 RW 0x0000_0000
	UINT32 y_coefficient6_h1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7_h1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC500888 RW 0x0000_0000
	UINT32 y_coefficient8_h1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9_h1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC50088C RW 0x0000_0000
	UINT32 y_coefficient10_h1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11_h1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC5008A4 RW 0x0000_0000
	UINT32 reg_mif_rd_on_g1                 :1;	//(0,NA,0x0) //1이면 M1 MRd_2pel on & select mrd path (size 정보 필요)
	UINT32 reg_mif_wr_on_g1                 :1;	//(1,NA,0x0) //'0' : VCP out	    '1' : MIF write
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode_g1                  :2;	//(4:3,NA,0x0) //reg_hactive_g1 기준으로 	0~1023 는 00, 01, 11 지원	1024~2047 는 01, 11	2048~ 는 11 만 지원	00 : V12T / 01: V6T / 11: V2T(bilinear)
	UINT32 reg_bilinear_on_g1               :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 reg_mode_32p_g1                  :1;	//(6,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 resvd0                           :9;
	UINT32 vsc_buffer_mode                  :1;	//(16,NA,0x0) //0: vsc_mode	1: buffer_mode
	UINT32 hsc_detour_mode                  :1;	//(17,NA,0x0) //0: hsc_mode	1: detour_mode
	UINT32 h_repeat_mode                    :2;	//(19:18,NA,0x0) //0: detour	1: 2 repeat	2: 4 repeat	3: 8 repeat
	UINT32 resvd1                           :5;
	UINT32 reg_v_reverse_g1                 :1;	//(25,NA,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_sampling_mode_g1             :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}REG_GSC_C_GSC_G1_C_CTRL_T;

typedef struct {
	REG_GSC_C_GSC_G0_C_CTRL_T                             gsc_g0_c_ctrl;	//0xCC500800
	REG_GSC_C_GSC_G0_C_MIF_RD_SIZE_T               gsc_g0_c_mif_rd_size;	//0xCC500804
	REG_GSC_C_GSC_G0_C_OUTSIZE_T                       gsc_g0_c_outsize;	//0xCC500808
	REG_GSC_C_GSC_G0_C_MIN_MAX_CTRL_T             gsc_g0_c_min_max_ctrl;	//0xCC50080C
	REG_GSC_C_GSC_G0_C_INPUT_MUX_T                   gsc_g0_c_input_mux;	//0xCC500810
	REG_GSC_C_GSC_G0_C_CROP_PARAM1_T               gsc_g0_c_crop_param1;	//0xCC500814
	REG_GSC_C_GSC_G0_C_CROP_PARAM2_T               gsc_g0_c_crop_param2;	//0xCC500818
	REG_GSC_C_GSC_G0_C_CROP_PARAM3_T               gsc_g0_c_crop_param3;	//0xCC50081C
	REG_GSC_C_GSC_G0_C_PHASE_OFFSET_T             gsc_g0_c_phase_offset;	//0xCC500820
	REG_GSC_C_GSC_G0_C_SAMPLING_H_T                 gsc_g0_c_sampling_h;	//0xCC500824
	REG_GSC_C_GSC_G0_C_SAMPLING_V_T                 gsc_g0_c_sampling_v;	//0xCC500828
	REG_GSC_C_GSC_G0_C_POST_CROP_PARAM1_T     gsc_g0_c_post_crop_param1;	//0xCC50082C
	REG_GSC_C_GSC_G0_C_POST_CROP_PARAM2_T     gsc_g0_c_post_crop_param2;	//0xCC500830
	REG_GSC_C_GSC_G0_C_POST_CROP_PARAM3_T     gsc_g0_c_post_crop_param3;	//0xCC500834
	REG_GSC_C_GSC_G0_C_MIF_RD_HOFFSET_T         gsc_g0_c_mif_rd_hoffset;	//0xCC500838
	REG_GSC_C_GSC_G0_FRC_FAIL_TIMER_T             gsc_g0_frc_fail_timer;	//0xCC50083C
	REG_GSC_C_GSC_G0_C_5K_8K_CTRL_T                 gsc_g0_c_5k_8k_ctrl;	//0xCC500840
	REG_GSC_C_GSC_G0_C_V1_FIR_COEF_CTRL_T     gsc_g0_c_v1_fir_coef_ctrl;	//0xCC500844
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA0_T gsc_g0_c_v1_y_fir_coef_data0;	//0xCC500848
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA1_T gsc_g0_c_v1_y_fir_coef_data1;	//0xCC50084C
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA2_T gsc_g0_c_v1_y_fir_coef_data2;	//0xCC500850
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA3_T gsc_g0_c_v1_y_fir_coef_data3;	//0xCC500854
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA4_T gsc_g0_c_v1_y_fir_coef_data4;	//0xCC500858
	REG_GSC_C_GSC_G0_C_V1_Y_FIR_COEF_DATA5_T gsc_g0_c_v1_y_fir_coef_data5;	//0xCC50085C
	UINT32                                                    reserved0;	//0xCC500860
	UINT32                                                    reserved1;	//0xCC500864
	UINT32                                                    reserved2;	//0xCC500868
	UINT32                                                    reserved3;	//0xCC50086C
	UINT32                                                    reserved4;	//0xCC500870
	REG_GSC_C_GSC_G0_C_H1_FIR_COEF_CTRL_T     gsc_g0_c_h1_fir_coef_ctrl;	//0xCC500874
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA0_T gsc_g0_c_h1_y_fir_coef_data0;	//0xCC500878
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA1_T gsc_g0_c_h1_y_fir_coef_data1;	//0xCC50087C
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA2_T gsc_g0_c_h1_y_fir_coef_data2;	//0xCC500880
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA3_T gsc_g0_c_h1_y_fir_coef_data3;	//0xCC500884
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA4_T gsc_g0_c_h1_y_fir_coef_data4;	//0xCC500888
	REG_GSC_C_GSC_G0_C_H1_Y_FIR_COEF_DATA5_T gsc_g0_c_h1_y_fir_coef_data5;	//0xCC50088C
	UINT32                                                    reserved5;	//0xCC500890
	UINT32                                                    reserved6;	//0xCC500894
	UINT32                                                    reserved7;	//0xCC500898
	UINT32                                                    reserved8;	//0xCC50089C
	UINT32                                                    reserved9;	//0xCC5008A0
	REG_GSC_C_GSC_G1_C_CTRL_T                             gsc_g1_c_ctrl;	//0xCC5008A4
}PE_GSC_C_REG_O22_T;
#endif
