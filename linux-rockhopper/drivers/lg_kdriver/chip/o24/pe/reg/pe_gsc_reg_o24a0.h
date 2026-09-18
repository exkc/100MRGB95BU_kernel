#ifndef _PE_GSC_REG_O24A0_1_H_
#define _PE_GSC_REG_O24A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC460600 RW 0x0000_0002
	UINT32 reg_mif_rd_on                    :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select FMC direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :1;	//(3,NA,0x0) //'0' : V8TAB filter (active width < 2048)	    '1' : V4TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on                  :1;	//(4,NA,0x0) //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 reg_th0                          :2;	//(7:6,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th1                          :2;	//(9:8,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th2                          :2;	//(11:10,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th3                          :2;	//(13:12,NA,0x0) //threshold of adaptive filter
	UINT32 resvd0                           :11;
	UINT32 reg_v_reverse_sm                 :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X2
	UINT32 v_repeat_mode                    :1;	//(27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2
	UINT32 resvd1                           :2;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC0_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460604 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460608 RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //height
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46060C RW 0x0000_0000
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
}PE_O24_OSC0_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460610 RW 0x0100_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input
	UINT32 resvd0                           :3;
	UINT32 reg_orbit_sel                    :1;	//(4,NA,0x0) //'0' : normal	 '1' : 4k orbit mode
	UINT32 resvd1                           :3;
	UINT32 reg_osc_8k_mode                  :1;	//(8,NA,0x0) //'0' : normal	 '1' : 8k processing (4097~8192)
	UINT32 resvd2                           :3;
	UINT32 reg_smth_mem_sel                 :1;	//(12,NA,0x0) //'0' : Line buffer processing	 '1' : SMTH use Line buffer memory
	UINT32 resvd3                           :4;
	UINT32 reg_mif_rd_ln_inc                :2;	//(18:17,NA,0x0) //Line number increment for MRD	Only use for 8k (8p, 2 line processing) sub samping mode	'0': 4k normal	'1': 4k 1/2 sub samgpling, 8k normal	'2': 4k 1/4 sub samgpling, 8k 1/2 sub sampling mode	'3': 8k 1/4 sub sampling mode
	UINT32 resvd4                           :2;
	UINT32 reg_mif_rd_ln_ch                 :2;	//(22:21,NA,0x0) //First read line number for L1 MRD	Only use for 8k sub samping mode	'0': 4k (4p, 1 line  processing)	     8k normal (8p, 2 line processing)	'1': 8k 1/2 sub sanpling mode	'2': 8k 1/4 sub sampling mode	'3': 8k 1/8 sub sampling mode
	UINT32 resvd5                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': manual mode (Only use 8k sub sampling)	     Do not use for 4k mode (4p/1line)	'1': 4k (4p, 1 line  processing)	         8k normal (8p, 2 line processing)	'2': 4k 1/2 sub sampling mode (4p/1 line)	'4': 4k 1/4 sub sampling mode (4p/1 line)
	UINT32 resvd6                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O24_OSC0_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460614 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460618 RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46061C RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460620 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC0_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460624 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460628 RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46062C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC0_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460630 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460634 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460638 RW 0x0000_0000
	UINT32 reg_mif_rd_voffset_l1            :14;	//(13:0,NA,0x0) //MRD V offset line 1
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_l0            :14;	//(29:16,NA,0x0) //MRD V offset line 2
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46063C RW 0x0000_0000
	UINT32 reg_frc_fail_timer               :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}PE_O24_OSC0_Y_OSC0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460644 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460648 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46064C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460650 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460654 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460658 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46065C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460660 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_V2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460664 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460668 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46066C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460670 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460674 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460678 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46067C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460680 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460684 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460688 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46068C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460690 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_H2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460694 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460698 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46069C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606A0 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606A4 RW 0x0000_0002
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :1;	//(3,NA,0x0) //'0' : V8TAB filter (active width < 2048)	    '1' : V4TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on                  :1;	//(4,NA,0x0) //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 reg_th0                          :2;	//(7:6,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th1                          :2;	//(9:8,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th2                          :2;	//(11:10,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th3                          :2;	//(13:12,NA,0x0) //threshold of adaptive filter
	UINT32 resvd1                           :11;
	UINT32 reg_v_reverse_sm                 :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X2
	UINT32 v_repeat_mode                    :1;	//(27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2
	UINT32 resvd2                           :2;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC0_Y_ORBIT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606AC RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //height
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606B0 RW 0x0000_0000
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
}PE_O24_OSC0_Y_ORBIT_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606B8 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606BC RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606C0 RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606C4 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC0_Y_ORBIT_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606C8 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606CC RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606D0 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606D4 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606D8 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606DC RW 0x0000_0000
	UINT32 reg_orbit_coeff_en               :1;	//(0,NA,0x0) //Set '1' when OSC0_Y_ORBIT_V1_FIR_COEF_CTRL setting
	UINT32 resvd                            :31;
	};
}PE_O24_OSC0_Y_ORBIT_COEFF_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606E8 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_ORBIT_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606EC RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606F0 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606F4 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606F8 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4606FC RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460700 RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460704 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_ORBIT_V2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460708 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46070C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460710 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460714 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460718 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_ORBIT_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46071C RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460720 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460724 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460728 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46072C RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460730 RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460734 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_Y_ORBIT_H2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460738 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46073C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460740 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460744 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA3_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460A00 RW 0x0000_0002
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :1;	//(3,NA,0x0) //'0' : V8TAB filter (active width < 2048)	    '1' : V4TAB filter (active width >= 2048)
	UINT32 reg_adaptive_on                  :1;	//(4,NA,0x0) //'0' : adaptive FIR filter disable	    '1' : adaptive FIR filter enable
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 reg_th0                          :2;	//(7:6,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th1                          :2;	//(9:8,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th2                          :2;	//(11:10,NA,0x0) //threshold of adaptive filter
	UINT32 reg_th3                          :2;	//(13:12,NA,0x0) //threshold of adaptive filter
	UINT32 resvd1                           :11;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X2
	UINT32 resvd2                           :3;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC1_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A04 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC1_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A08 RW 0x0870_0F00
	UINT32 reg_hosize                       :13;	//(12:0,NA,0xF00) //width
	UINT32 resvd0                           :3;
	UINT32 reg_vosize                       :13;	//(28:16,NA,0x870) //height
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A0C RW 0x0000_0000
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
}PE_O24_OSC1_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A10 RW VNA
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input
	UINT32 resvd0                           :7;
	UINT32 reg_osc_6k_mode                  :1;	//(8,NA,0x0) //'0' : normal	 '1' : 6k processing (4097~6144)
	UINT32 resvd1                           :7;
	UINT32 reg_ring_buffer_share            :1;	//(16,NA,0x0) //'0' : Line buffer processing	 '1' : Ring buffer use Line buffer memory for not 6k processing
	UINT32 resvd2                           :7;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd3                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O24_OSC1_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A14 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A18 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A1C RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A20 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC1_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A24 RW 0x0000_0000
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A28 RW 0x0000_0000
	UINT32 reg_denominator_v                :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A2C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC1_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A30 RW 0x0000_0000
	UINT32 reg_post_hactive                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A34 RW 0x0000_0000
	UINT32 reg_post_hisize                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize                  :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A38 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset               :14;	//(29:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC1_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A44 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_Y_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A48 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A4C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A50 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A54 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A58 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A5C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A60 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_Y_V2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A64 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A68 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A6C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A70 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A74 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_Y_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A78 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A7C RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A80 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A84 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A88 RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A8C RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A90 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_Y_H2_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A94 RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A98 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460A9C RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460AA0 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA3_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460800 RW 0x0000_0002
	UINT32 reg_mif_rd_on                    :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select FMC direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :2;	//(4:3,NA,0x0) //reg_hactive_ 기준으로 	0~1023 는 00, 01, 11 지원	1024~2047 는 01, 11	2048~ 는 11 만 지원	00 : V8T / 01: V4T / 11: V2T(bilinear)
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd0                           :14;
	UINT32 reg_v_cti_en                     :1;	//(20,NA,0x0) //
	UINT32 reg_v_cti_ratio                  :2;	//(22:21,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X2
	UINT32 v_repeat_mode                    :2;	//(28:27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2	     '2' : v repeat on. X4
	UINT32 resvd2                           :1;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC0_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460804 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460808 RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46080C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}PE_O24_OSC0_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460810 RW 0x0120_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input
	UINT32 resvd0                           :3;
	UINT32 reg_orbit_sel                    :1;	//(4,NA,0x0) //'0' : normal	 '1' : 4k orbit mode
	UINT32 resvd1                           :3;
	UINT32 reg_osc_8k_mode                  :1;	//(8,NA,0x0) //'0' : normal	 '1' : 8k processing (4097~8192)
	UINT32 resvd2                           :3;
	UINT32 reg_smth_mem_sel                 :1;	//(12,NA,0x0) //'0' : Line buffer processing	 '1' : SMTH use Line buffer memory
	UINT32 resvd3                           :3;
	UINT32 reg_dsc_4k_mode                  :1;	//(16,NA,0x0) //'0' : normal	 '1' : hsc detour, vsc off
	UINT32 reg_mif_rd_ln_inc                :2;	//(18:17,NA,0x0) //Line number increment for MRD	Only use for 8k (8p, 2 line processing) sub samping mode	'0': 4k normal	'1': 4k 1/2 sub samgpling, 8k normal	'2': 4k 1/4 sub samgpling, 8k 1/2 sub sampling mode	'3': 8k 1/4 sub sampling mode
	UINT32 resvd4                           :1;
	UINT32 reg_dsc_8k_mode                  :1;	//(20,NA,0x0) //'0' : normal	 '1' : hsc detour, osc_8k_mode, 8k ring buffer
	UINT32 reg_mif_rd_ln_ch                 :3;	//(23:21,NA,0x0) //First read line number for L1 MRD	Only use for 8k sub samping mode	'0': 4k (4p, 1 line  processing)	     8k normal (8p, 2 line processing)	'1': 8k 1/2 sub sanpling mode	'2': 8k 1/4 sub sampling mode	'3': 8k 1/8 sub sampling mode
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': manual mode (Only use 8k sub sampling)	     Do not use for 4k mode (4p/1line)	'1': 4k (4p, 1 line  processing)	         8k normal (8p, 2 line processing)	'2': 4k 1/2 sub sampling mode (4p/1 line)	'4': 4k 1/4 sub sampling mode (4p/1 line)
	UINT32 resvd5                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O24_OSC0_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460814 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //오프셋
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460818 RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //액티브
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46081C RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460820 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC0_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460824 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460828 RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46082C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC0_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460830 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460834 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460838 RW 0x0000_0000
	UINT32 reg_mif_rd_voffset_l1            :14;	//(13:0,NA,0x0) //MRD V offset line 1
	UINT32 resvd0                           :2;
	UINT32 reg_mif_rd_voffset_l0            :14;	//(29:16,NA,0x0) //MRD V offset line 2
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46083C RW 0x0000_0000
	UINT32 reg_frc_fail_timer               :32;	//(31:0,NA,0x0) //0 : fail timer off
	};
}PE_O24_OSC0_FRC_FAIL_TIMER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460844 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_C_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460848 RW 0x0000_0000
	UINT32 c_coefficient0_v1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient1_v1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46084C RW 0x0000_0000
	UINT32 c_coefficient2_v1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient3_v1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460850 RW 0x0000_0000
	UINT32 c_coefficient4_v1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient5_v1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460854 RW 0x0000_0000
	UINT32 c_coefficient6_v1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient7_v1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460858 RW 0x0000_0000
	UINT32 c_coefficient8_v1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient9_v1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46085C RW 0x0000_0000
	UINT32 c_coefficient10_v1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient11_v1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460874 WO 0x0000_0000
	UINT32 update_h1                        :1;	//(0:0,NA,0x0) //update
	UINT32 rnw_h1                           :1;	//(1:1,NA,0x0) //0: write	1: read
	UINT32 addr_h1                          :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_C_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460878 RW 0x0000_0000
	UINT32 c_coefficient0_h1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient1_h1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46087C RW 0x0000_0000
	UINT32 c_coefficient2_h1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient3_h1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460880 RW 0x0000_0000
	UINT32 c_coefficient4_h1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient5_h1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460884 RW 0x0000_0000
	UINT32 c_coefficient6_h1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient7_h1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460888 RW 0x0000_0000
	UINT32 c_coefficient8_h1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient9_h1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46088C RW 0x0000_0000
	UINT32 c_coefficient10_h1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient11_h1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608A4 RW 0x0000_0002
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :2;	//(4:3,NA,0x0) //reg_hactive_ 기준으로 	0~1023 는 00, 01, 11 지원	1024~2047 는 01, 11	2048~ 는 11 만 지원	00 : V8T / 01: V4T / 11: V2T(bilinear)
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :14;
	UINT32 reg_v_cti_en                     :1;	//(20,NA,0x0) //
	UINT32 reg_v_cti_ratio                  :2;	//(22:21,NA,0x0) //
	UINT32 resvd2                           :3;
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X2
	UINT32 v_repeat_mode                    :2;	//(28:27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2	     '2' : v repeat on. X4
	UINT32 resvd3                           :1;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC0_C_ORBIT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608AC RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608B0 RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}PE_O24_OSC0_C_ORBIT_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608B8 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //오프셋
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608BC RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //액티브
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608C0 RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608C4 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC0_C_ORBIT_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608C8 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608CC RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608D0 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608D4 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608D8 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608DC RW 0x0000_0000
	UINT32 reg_orbit_coeff_en               :1;	//(0,NA,0x0) //Set '1' when OSC0_Y_ORBIT_V1_FIR_COEF_CTRL setting
	UINT32 resvd                            :31;
	};
}PE_O24_OSC0_C_ORBIT_COEFF_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608E8 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_C_ORBIT_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608EC RW 0x0000_0000
	UINT32 c_coefficient0_v1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient1_v1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608F0 RW 0x0000_0000
	UINT32 c_coefficient2_v1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient3_v1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608F4 RW 0x0000_0000
	UINT32 c_coefficient4_v1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient5_v1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608F8 RW 0x0000_0000
	UINT32 c_coefficient6_v1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient7_v1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4608FC RW 0x0000_0000
	UINT32 c_coefficient8_v1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient9_v1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460900 RW 0x0000_0000
	UINT32 c_coefficient10_v1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient11_v1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460918 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC0_C_ORBIT_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46091C RW 0x0000_0000
	UINT32 y_coefficient0                   :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient1                   :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460920 RW 0x0000_0000
	UINT32 y_coefficient2                   :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient3                   :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460924 RW 0x0000_0000
	UINT32 y_coefficient4                   :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient5                   :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460928 RW 0x0000_0000
	UINT32 y_coefficient6                   :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient7                   :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46092C RW 0x0000_0000
	UINT32 y_coefficient8                   :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient9                   :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460930 RW 0x0000_0000
	UINT32 y_coefficient10                  :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 y_coefficient11                  :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA5_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460C00 RW 0x0000_0002
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :2;	//(4:3,NA,0x0) //reg_hactive_ 기준으로 	0~1023 는 00, 01, 11 지원	1024~2047 는 01, 11	2048~ 는 11 만 지원	00 : V8T / 01: V4T / 11: V2T(bilinear)
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :14;
	UINT32 reg_v_cti_en                     :1;	//(20,NA,0x0) //
	UINT32 reg_v_cti_ratio                  :2;	//(22:21,NA,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 h_repeat_mode                    :1;	//(26,NA,0x0) //'0' : normal	     '1' : h repeat on. X4
	UINT32 resvd3                           :3;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_OSC1_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C04 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 reg_vinc                         :2;	//(31:30,NA,0x0) //V increment for  MRD
	};
}PE_O24_OSC1_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C08 RW 0x0870_0F00
	UINT32 reg_hosize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vosize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C0C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}PE_O24_OSC1_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C10 RW VNA
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input
	UINT32 resvd0                           :7;
	UINT32 reg_osc_6k_mode                  :1;	//(8,NA,0x0) //'0' : normal	 '1' : 6k processing (4097~6144)
	UINT32 resvd1                           :7;
	UINT32 reg_ring_buffer_share            :1;	//(16,NA,0x0) //'0' : Line buffer processing	 '1' : Ring buffer use Line buffer memory for not 6k processing
	UINT32 resvd2                           :7;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd3                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O24_OSC1_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C14 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //오프셋
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C18 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //액티브
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C1C RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C20 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}PE_O24_OSC1_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C24 RW 0x0000_0000
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C28 RW 0x0000_0000
	UINT32 reg_denominator_v                :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C2C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O24_OSC1_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C30 RW 0x0000_0000
	UINT32 reg_post_hactive                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C34 RW 0x0000_0000
	UINT32 reg_post_hisize                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize                  :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC1_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C38 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset               :14;	//(29:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC1_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C44 WO 0x0000_0000
	UINT32 update                           :1;	//(0,NA,0x0) //update
	UINT32 rnw                              :1;	//(1,NA,0x0) //'0' : write	      '1' : read
	UINT32 addr                             :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_C_V1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C48 RW 0x0000_0000
	UINT32 c_coefficient0_v1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient1_v1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C4C RW 0x0000_0000
	UINT32 c_coefficient2_v1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient3_v1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C50 RW 0x0000_0000
	UINT32 c_coefficient4_v1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient5_v1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C54 RW 0x0000_0000
	UINT32 c_coefficient6_v1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient7_v1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C58 RW 0x0000_0000
	UINT32 c_coefficient8_v1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient9_v1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C5C RW 0x0000_0000
	UINT32 c_coefficient10_v1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient11_v1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C74 WO 0x0000_0000
	UINT32 update_h1                        :1;	//(0:0,NA,0x0) //update
	UINT32 rnw_h1                           :1;	//(1:1,NA,0x0) //0: write	1: read
	UINT32 addr_h1                          :8;	//(9:2,NA,0x0) //phase address 0~127
	UINT32 resvd                            :22;
	};
}PE_O24_OSC1_C_H1_FIR_COEF_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C78 RW 0x0000_0000
	UINT32 c_coefficient0_h1                :12;	//(11:0,NA,0x0) //0th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient1_h1                :12;	//(27:16,NA,0x0) //1st coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C7C RW 0x0000_0000
	UINT32 c_coefficient2_h1                :12;	//(11:0,NA,0x0) //2nd coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient3_h1                :12;	//(27:16,NA,0x0) //3rd coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C80 RW 0x0000_0000
	UINT32 c_coefficient4_h1                :12;	//(11:0,NA,0x0) //4th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient5_h1                :12;	//(27:16,NA,0x0) //5th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C84 RW 0x0000_0000
	UINT32 c_coefficient6_h1                :12;	//(11:0,NA,0x0) //6th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient7_h1                :12;	//(27:16,NA,0x0) //7th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C88 RW 0x0000_0000
	UINT32 c_coefficient8_h1                :12;	//(11:0,NA,0x0) //8th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient9_h1                :12;	//(27:16,NA,0x0) //9th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460C8C RW 0x0000_0000
	UINT32 c_coefficient10_h1               :12;	//(11:0,NA,0x0) //10th coefficient
	UINT32 resvd0                           :4;
	UINT32 c_coefficient11_h1               :12;	//(27:16,NA,0x0) //11th coefficient
	UINT32 resvd1                           :4;
	};
}PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA5_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC460E00 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O24_OSC2_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E04 RW 0x0000_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source
	UINT32 resvd                            :31;
	};
}PE_O24_OSC2_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E08 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O24_OSC2_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E0C RW 0x0000_0000
	UINT32 reg_hsize                        :13;	//(12:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :3;
	UINT32 reg_vsize                        :13;	//(28:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E10 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E14 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E18 RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E1C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :3;
	};
}PE_O24_OSC2_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E80 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O24_OSC2_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E84 RW 0x0000_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source
	UINT32 resvd                            :31;
	};
}PE_O24_OSC2_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E88 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :1;
	UINT32 reg_v_repeat                     :1;	//(27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2
	UINT32 resvd2                           :4;
	};
}PE_O24_OSC2_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E8C RW 0x0000_0000
	UINT32 reg_hsize                        :13;	//(12:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :3;
	UINT32 reg_vsize                        :13;	//(28:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E90 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E94 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E98 RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC2_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460E9C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :3;
	};
}PE_O24_OSC2_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC460EA0 RW 0x0000_0001
	UINT32 reg_buf_mode                     :1;	//(0,NA,0x1) //buffer_mode	0: 420 -> 422	1: buffer
	UINT32 resvd0                           :3;
	UINT32 reg_c_type                       :1;	//(4,NA,0x0) //0: y-c aligned 420 type (prev)	1: y-c not aligned 420 type (newly added))
	UINT32 resvd1                           :3;
	UINT32 reg_c_vfilt_en                   :1;	//(8,NA,0x0) //vertical filter enabled
	UINT32 resvd2                           :3;
	UINT32 reg_c_422to444                   :2;	//(13:12,NA,0x0) //c 422 to 444 mode	'0': disable	'1': 422 to 444 h repeat	'2': 422 to 444 h avg.
	UINT32 resvd3                           :18;
	};
}PE_O24_OSC2_C_CS_CTRL_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC461000 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O24_OSC3_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461004 RW 0x0000_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source
	UINT32 resvd                            :31;
	};
}PE_O24_OSC3_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461008 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O24_OSC3_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46100C RW 0x0000_0000
	UINT32 reg_hsize                        :13;	//(12:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :3;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC3_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461010 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461014 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461018 RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46101C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :14;	//(29:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :2;
	};
}PE_O24_OSC3_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461080 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O24_OSC3_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461084 RW 0x0000_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source
	UINT32 resvd                            :31;
	};
}PE_O24_OSC3_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461088 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :1;
	UINT32 reg_v_repeat                     :1;	//(27,NA,0x0) //'0' : normal	     '1' : v repeat on. X2
	UINT32 resvd2                           :4;
	};
}PE_O24_OSC3_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46108C RW 0x0000_0000
	UINT32 reg_hsize                        :13;	//(12:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :3;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O24_OSC3_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461090 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461094 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC461098 RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O24_OSC3_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC46109C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :13;	//(28:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :3;
	};
}PE_O24_OSC3_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4610A0 RW 0x0000_0001
	UINT32 reg_buf_mode                     :1;	//(0,NA,0x1) //buffer_mode	0: 420 -> 422	1: buffer
	UINT32 resvd0                           :3;
	UINT32 reg_c_type                       :1;	//(4,NA,0x0) //0: y-c aligned 420 type (prev)	1: y-c not aligned 420 type (newly added))
	UINT32 resvd1                           :3;
	UINT32 reg_c_vfilt_en                   :1;	//(8,NA,0x0) //vertical filter enabled
	UINT32 resvd2                           :3;
	UINT32 reg_c_422to444                   :2;	//(13:12,NA,0x0) //c 422 to 444 mode	'0': disable	'1': 422 to 444 h repeat	'2': 422 to 444 h avg.
	UINT32 resvd3                           :18;
	};
}PE_O24_OSC3_C_CS_CTRL_T;

typedef struct {
	PE_O24_OSC0_Y_CTRL_T                                osc0_y_ctrl;	//0xCC460600
	PE_O24_OSC0_Y_MIF_RD_SIZE_T                  osc0_y_mif_rd_size;	//0xCC460604
	PE_O24_OSC0_Y_OUTSIZE_T                          osc0_y_outsize;	//0xCC460608
	PE_O24_OSC0_Y_MIN_MAX_CTRL_T                osc0_y_min_max_ctrl;	//0xCC46060C
	PE_O24_OSC0_Y_CTRL1_T                              osc0_y_ctrl1;	//0xCC460610
	PE_O24_OSC0_Y_CROP_PARAM1_T                  osc0_y_crop_param1;	//0xCC460614
	PE_O24_OSC0_Y_CROP_PARAM2_T                  osc0_y_crop_param2;	//0xCC460618
	PE_O24_OSC0_Y_CROP_PARAM3_T                  osc0_y_crop_param3;	//0xCC46061C
	PE_O24_OSC0_Y_PHASE_OFFSET_T                osc0_y_phase_offset;	//0xCC460620
	PE_O24_OSC0_Y_SAMPLING_H_T                    osc0_y_sampling_h;	//0xCC460624
	PE_O24_OSC0_Y_SAMPLING_V_T                    osc0_y_sampling_v;	//0xCC460628
	PE_O24_OSC0_Y_POST_CROP_PARAM1_T        osc0_y_post_crop_param1;	//0xCC46062C
	PE_O24_OSC0_Y_POST_CROP_PARAM2_T        osc0_y_post_crop_param2;	//0xCC460630
	PE_O24_OSC0_Y_POST_CROP_PARAM3_T        osc0_y_post_crop_param3;	//0xCC460634
	PE_O24_OSC0_Y_MIF_RD_T                            osc0_y_mif_rd;	//0xCC460638
	PE_O24_OSC0_Y_OSC0_FRC_FAIL_TIMER_T                osc0_frc_fail_timer;	//0xCC46063C
	UINT32                                                    reserved0;	//0xCC460640
	PE_O24_OSC0_Y_V1_FIR_COEF_CTRL_T        osc0_y_v1_fir_coef_ctrl;	//0xCC460644
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA0_T  osc0_y_v1_y_fir_coef_data0;	//0xCC460648
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA1_T  osc0_y_v1_y_fir_coef_data1;	//0xCC46064C
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA2_T  osc0_y_v1_y_fir_coef_data2;	//0xCC460650
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA3_T  osc0_y_v1_y_fir_coef_data3;	//0xCC460654
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA4_T  osc0_y_v1_y_fir_coef_data4;	//0xCC460658
	PE_O24_OSC0_Y_V1_Y_FIR_COEF_DATA5_T  osc0_y_v1_y_fir_coef_data5;	//0xCC46065C
	PE_O24_OSC0_Y_V2_FIR_COEF_CTRL_T        osc0_y_v2_fir_coef_ctrl;	//0xCC460660
	PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA0_T  osc0_y_v2_y_fir_coef_data0;	//0xCC460664
	PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA1_T  osc0_y_v2_y_fir_coef_data1;	//0xCC460668
	PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA2_T  osc0_y_v2_y_fir_coef_data2;	//0xCC46066C
	PE_O24_OSC0_Y_V2_Y_FIR_COEF_DATA3_T  osc0_y_v2_y_fir_coef_data3;	//0xCC460670
	PE_O24_OSC0_Y_H1_FIR_COEF_CTRL_T        osc0_y_h1_fir_coef_ctrl;	//0xCC460674
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA0_T  osc0_y_h1_y_fir_coef_data0;	//0xCC460678
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA1_T  osc0_y_h1_y_fir_coef_data1;	//0xCC46067C
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA2_T  osc0_y_h1_y_fir_coef_data2;	//0xCC460680
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA3_T  osc0_y_h1_y_fir_coef_data3;	//0xCC460684
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA4_T  osc0_y_h1_y_fir_coef_data4;	//0xCC460688
	PE_O24_OSC0_Y_H1_Y_FIR_COEF_DATA5_T  osc0_y_h1_y_fir_coef_data5;	//0xCC46068C
	PE_O24_OSC0_Y_H2_FIR_COEF_CTRL_T        osc0_y_h2_fir_coef_ctrl;	//0xCC460690
	PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA0_T  osc0_y_h2_y_fir_coef_data0;	//0xCC460694
	PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA1_T  osc0_y_h2_y_fir_coef_data1;	//0xCC460698
	PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA2_T  osc0_y_h2_y_fir_coef_data2;	//0xCC46069C
	PE_O24_OSC0_Y_H2_Y_FIR_COEF_DATA3_T  osc0_y_h2_y_fir_coef_data3;	//0xCC4606A0
	PE_O24_OSC0_Y_ORBIT_CTRL_T                    osc0_y_orbit_ctrl;	//0xCC4606A4
	UINT32                                                    reserved1;	//0xCC4606A8
	PE_O24_OSC0_Y_ORBIT_OUTSIZE_T              osc0_y_orbit_outsize;	//0xCC4606AC
	PE_O24_OSC0_Y_ORBIT_MIN_MAX_CTRL_T    osc0_y_orbit_min_max_ctrl;	//0xCC4606B0
	UINT32                                                    reserved2;	//0xCC4606B4
	PE_O24_OSC0_Y_ORBIT_CROP_PARAM1_T      osc0_y_orbit_crop_param1;	//0xCC4606B8
	PE_O24_OSC0_Y_ORBIT_CROP_PARAM2_T      osc0_y_orbit_crop_param2;	//0xCC4606BC
	PE_O24_OSC0_Y_ORBIT_CROP_PARAM3_T      osc0_y_orbit_crop_param3;	//0xCC4606C0
	PE_O24_OSC0_Y_ORBIT_PHASE_OFFSET_T    osc0_y_orbit_phase_offset;	//0xCC4606C4
	PE_O24_OSC0_Y_ORBIT_SAMPLING_H_T        osc0_y_orbit_sampling_h;	//0xCC4606C8
	PE_O24_OSC0_Y_ORBIT_SAMPLING_V_T        osc0_y_orbit_sampling_v;	//0xCC4606CC
	PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM1_T osc0_y_orbit_post_crop_param1;	//0xCC4606D0
	PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM2_T osc0_y_orbit_post_crop_param2;	//0xCC4606D4
	PE_O24_OSC0_Y_ORBIT_POST_CROP_PARAM3_T osc0_y_orbit_post_crop_param3;	//0xCC4606D8
	PE_O24_OSC0_Y_ORBIT_COEFF_EN_T            osc0_y_orbit_coeff_en;	//0xCC4606DC
	UINT32                                                    reserved3;	//0xCC4606E0
	UINT32                                                    reserved4;	//0xCC4606E4
	PE_O24_OSC0_Y_ORBIT_V1_FIR_COEF_CTRL_T osc0_y_orbit_v1_fir_coef_ctrl;	//0xCC4606E8
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA0_T osc0_y_orbit_v1_y_fir_coef_data0;	//0xCC4606EC
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA1_T osc0_y_orbit_v1_y_fir_coef_data1;	//0xCC4606F0
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA2_T osc0_y_orbit_v1_y_fir_coef_data2;	//0xCC4606F4
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA3_T osc0_y_orbit_v1_y_fir_coef_data3;	//0xCC4606F8
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA4_T osc0_y_orbit_v1_y_fir_coef_data4;	//0xCC4606FC
	PE_O24_OSC0_Y_ORBIT_V1_Y_FIR_COEF_DATA5_T osc0_y_orbit_v1_y_fir_coef_data5;	//0xCC460700
	PE_O24_OSC0_Y_ORBIT_V2_FIR_COEF_CTRL_T osc0_y_orbit_v2_fir_coef_ctrl;	//0xCC460704
	PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA0_T osc0_y_orbit_v2_y_fir_coef_data0;	//0xCC460708
	PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA1_T osc0_y_orbit_v2_y_fir_coef_data1;	//0xCC46070C
	PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA2_T osc0_y_orbit_v2_y_fir_coef_data2;	//0xCC460710
	PE_O24_OSC0_Y_ORBIT_V2_Y_FIR_COEF_DATA3_T osc0_y_orbit_v2_y_fir_coef_data3;	//0xCC460714
	PE_O24_OSC0_Y_ORBIT_H1_FIR_COEF_CTRL_T osc0_y_orbit_h1_fir_coef_ctrl;	//0xCC460718
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA0_T osc0_y_orbit_h1_y_fir_coef_data0;	//0xCC46071C
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA1_T osc0_y_orbit_h1_y_fir_coef_data1;	//0xCC460720
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA2_T osc0_y_orbit_h1_y_fir_coef_data2;	//0xCC460724
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA3_T osc0_y_orbit_h1_y_fir_coef_data3;	//0xCC460728
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA4_T osc0_y_orbit_h1_y_fir_coef_data4;	//0xCC46072C
	PE_O24_OSC0_Y_ORBIT_H1_Y_FIR_COEF_DATA5_T osc0_y_orbit_h1_y_fir_coef_data5;	//0xCC460730
	PE_O24_OSC0_Y_ORBIT_H2_FIR_COEF_CTRL_T osc0_y_orbit_h2_fir_coef_ctrl;	//0xCC460734
	PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA0_T osc0_y_orbit_h2_y_fir_coef_data0;	//0xCC460738
	PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA1_T osc0_y_orbit_h2_y_fir_coef_data1;	//0xCC46073C
	PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA2_T osc0_y_orbit_h2_y_fir_coef_data2;	//0xCC460740
	PE_O24_OSC0_Y_ORBIT_H2_Y_FIR_COEF_DATA3_T osc0_y_orbit_h2_y_fir_coef_data3;	//0xCC460744
}PE_OSC0_Y_REG_O24_T;


typedef struct {
	PE_O24_OSC1_Y_CTRL_T                                osc1_y_ctrl;	//0xCC460A00
	PE_O24_OSC1_Y_MIF_RD_SIZE_T                  osc1_y_mif_rd_size;	//0xCC460A04
	PE_O24_OSC1_Y_OUTSIZE_T                          osc1_y_outsize;	//0xCC460A08
	PE_O24_OSC1_Y_MIN_MAX_CTRL_T                osc1_y_min_max_ctrl;	//0xCC460A0C
	PE_O24_OSC1_Y_CTRL1_T                              osc1_y_ctrl1;	//0xCC460A10
	PE_O24_OSC1_Y_CROP_PARAM1_T                  osc1_y_crop_param1;	//0xCC460A14
	PE_O24_OSC1_Y_CROP_PARAM2_T                  osc1_y_crop_param2;	//0xCC460A18
	PE_O24_OSC1_Y_CROP_PARAM3_T                  osc1_y_crop_param3;	//0xCC460A1C
	PE_O24_OSC1_Y_PHASE_OFFSET_T                osc1_y_phase_offset;	//0xCC460A20
	PE_O24_OSC1_Y_SAMPLING_H_T                    osc1_y_sampling_h;	//0xCC460A24
	PE_O24_OSC1_Y_SAMPLING_V_T                    osc1_y_sampling_v;	//0xCC460A28
	PE_O24_OSC1_Y_POST_CROP_PARAM1_T        osc1_y_post_crop_param1;	//0xCC460A2C
	PE_O24_OSC1_Y_POST_CROP_PARAM2_T        osc1_y_post_crop_param2;	//0xCC460A30
	PE_O24_OSC1_Y_POST_CROP_PARAM3_T        osc1_y_post_crop_param3;	//0xCC460A34
	PE_O24_OSC1_Y_MIF_RD_T                            osc1_y_mif_rd;	//0xCC460A38
	UINT32                                                    reserved0;	//0xCC460A3C
	UINT32                                                    reserved1;	//0xCC460A40
	PE_O24_OSC1_Y_V1_FIR_COEF_CTRL_T        osc1_y_v1_fir_coef_ctrl;	//0xCC460A44
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA0_T  osc1_y_v1_y_fir_coef_data0;	//0xCC460A48
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA1_T  osc1_y_v1_y_fir_coef_data1;	//0xCC460A4C
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA2_T  osc1_y_v1_y_fir_coef_data2;	//0xCC460A50
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA3_T  osc1_y_v1_y_fir_coef_data3;	//0xCC460A54
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA4_T  osc1_y_v1_y_fir_coef_data4;	//0xCC460A58
	PE_O24_OSC1_Y_V1_Y_FIR_COEF_DATA5_T  osc1_y_v1_y_fir_coef_data5;	//0xCC460A5C
	PE_O24_OSC1_Y_V2_FIR_COEF_CTRL_T        osc1_y_v2_fir_coef_ctrl;	//0xCC460A60
	PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA0_T  osc1_y_v2_y_fir_coef_data0;	//0xCC460A64
	PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA1_T  osc1_y_v2_y_fir_coef_data1;	//0xCC460A68
	PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA2_T  osc1_y_v2_y_fir_coef_data2;	//0xCC460A6C
	PE_O24_OSC1_Y_V2_Y_FIR_COEF_DATA3_T  osc1_y_v2_y_fir_coef_data3;	//0xCC460A70
	PE_O24_OSC1_Y_H1_FIR_COEF_CTRL_T        osc1_y_h1_fir_coef_ctrl;	//0xCC460A74
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA0_T  osc1_y_h1_y_fir_coef_data0;	//0xCC460A78
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA1_T  osc1_y_h1_y_fir_coef_data1;	//0xCC460A7C
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA2_T  osc1_y_h1_y_fir_coef_data2;	//0xCC460A80
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA3_T  osc1_y_h1_y_fir_coef_data3;	//0xCC460A84
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA4_T  osc1_y_h1_y_fir_coef_data4;	//0xCC460A88
	PE_O24_OSC1_Y_H1_Y_FIR_COEF_DATA5_T  osc1_y_h1_y_fir_coef_data5;	//0xCC460A8C
	PE_O24_OSC1_Y_H2_FIR_COEF_CTRL_T        osc1_y_h2_fir_coef_ctrl;	//0xCC460A90
	PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA0_T  osc1_y_h2_y_fir_coef_data0;	//0xCC460A94
	PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA1_T  osc1_y_h2_y_fir_coef_data1;	//0xCC460A98
	PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA2_T  osc1_y_h2_y_fir_coef_data2;	//0xCC460A9C
	PE_O24_OSC1_Y_H2_Y_FIR_COEF_DATA3_T  osc1_y_h2_y_fir_coef_data3;	//0xCC460AA0
}PE_OSC1_Y_REG_O24_T;


typedef struct {
	PE_O24_OSC0_C_CTRL_T                                osc0_c_ctrl;	//0xCC460800
	PE_O24_OSC0_C_MIF_RD_SIZE_T                  osc0_c_mif_rd_size;	//0xCC460804
	PE_O24_OSC0_C_OUTSIZE_T                          osc0_c_outsize;	//0xCC460808
	PE_O24_OSC0_C_MIN_MAX_CTRL_T                osc0_c_min_max_ctrl;	//0xCC46080C
	PE_O24_OSC0_C_CTRL1_T                              osc0_c_ctrl1;	//0xCC460810
	PE_O24_OSC0_C_CROP_PARAM1_T                  osc0_c_crop_param1;	//0xCC460814
	PE_O24_OSC0_C_CROP_PARAM2_T                  osc0_c_crop_param2;	//0xCC460818
	PE_O24_OSC0_C_CROP_PARAM3_T                  osc0_c_crop_param3;	//0xCC46081C
	PE_O24_OSC0_C_PHASE_OFFSET_T                osc0_c_phase_offset;	//0xCC460820
	PE_O24_OSC0_C_SAMPLING_H_T                    osc0_c_sampling_h;	//0xCC460824
	PE_O24_OSC0_C_SAMPLING_V_T                    osc0_c_sampling_v;	//0xCC460828
	PE_O24_OSC0_C_POST_CROP_PARAM1_T        osc0_c_post_crop_param1;	//0xCC46082C
	PE_O24_OSC0_C_POST_CROP_PARAM2_T        osc0_c_post_crop_param2;	//0xCC460830
	PE_O24_OSC0_C_POST_CROP_PARAM3_T        osc0_c_post_crop_param3;	//0xCC460834
	PE_O24_OSC0_C_MIF_RD_T                            osc0_c_mif_rd;	//0xCC460838
	PE_O24_OSC0_FRC_FAIL_TIMER_T                osc0_frc_fail_timer;	//0xCC46083C
	UINT32                                                    reserved0;	//0xCC460840
	PE_O24_OSC0_C_V1_FIR_COEF_CTRL_T        osc0_c_v1_fir_coef_ctrl;	//0xCC460844
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA0_T  osc0_c_v1_y_fir_coef_data0;	//0xCC460848
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA1_T  osc0_c_v1_y_fir_coef_data1;	//0xCC46084C
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA2_T  osc0_c_v1_y_fir_coef_data2;	//0xCC460850
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA3_T  osc0_c_v1_y_fir_coef_data3;	//0xCC460854
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA4_T  osc0_c_v1_y_fir_coef_data4;	//0xCC460858
	PE_O24_OSC0_C_V1_Y_FIR_COEF_DATA5_T  osc0_c_v1_y_fir_coef_data5;	//0xCC46085C
	UINT32                                                    reserved1;	//0xCC460860
	UINT32                                                    reserved2;	//0xCC460864
	UINT32                                                    reserved3;	//0xCC460868
	UINT32                                                    reserved4;	//0xCC46086C
	UINT32                                                    reserved5;	//0xCC460870
	PE_O24_OSC0_C_H1_FIR_COEF_CTRL_T        osc0_c_h1_fir_coef_ctrl;	//0xCC460874
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA0_T  osc0_c_h1_y_fir_coef_data0;	//0xCC460878
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA1_T  osc0_c_h1_y_fir_coef_data1;	//0xCC46087C
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA2_T  osc0_c_h1_y_fir_coef_data2;	//0xCC460880
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA3_T  osc0_c_h1_y_fir_coef_data3;	//0xCC460884
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA4_T  osc0_c_h1_y_fir_coef_data4;	//0xCC460888
	PE_O24_OSC0_C_H1_Y_FIR_COEF_DATA5_T  osc0_c_h1_y_fir_coef_data5;	//0xCC46088C
	UINT32                                                    reserved6;	//0xCC460890
	UINT32                                                    reserved7;	//0xCC460894
	UINT32                                                    reserved8;	//0xCC460898
	UINT32                                                    reserved9;	//0xCC46089C
	UINT32                                                   reserved10;	//0xCC4608A0
	PE_O24_OSC0_C_ORBIT_CTRL_T                    osc0_c_orbit_ctrl;	//0xCC4608A4
	UINT32                                                   reserved11;	//0xCC4608A8
	PE_O24_OSC0_C_ORBIT_OUTSIZE_T              osc0_c_orbit_outsize;	//0xCC4608AC
	PE_O24_OSC0_C_ORBIT_MIN_MAX_CTRL_T    osc0_c_orbit_min_max_ctrl;	//0xCC4608B0
	UINT32                                                   reserved12;	//0xCC4608B4
	PE_O24_OSC0_C_ORBIT_CROP_PARAM1_T      osc0_c_orbit_crop_param1;	//0xCC4608B8
	PE_O24_OSC0_C_ORBIT_CROP_PARAM2_T      osc0_c_orbit_crop_param2;	//0xCC4608BC
	PE_O24_OSC0_C_ORBIT_CROP_PARAM3_T      osc0_c_orbit_crop_param3;	//0xCC4608C0
	PE_O24_OSC0_C_ORBIT_PHASE_OFFSET_T    osc0_c_orbit_phase_offset;	//0xCC4608C4
	PE_O24_OSC0_C_ORBIT_SAMPLING_H_T        osc0_c_orbit_sampling_h;	//0xCC4608C8
	PE_O24_OSC0_C_ORBIT_SAMPLING_V_T        osc0_c_orbit_sampling_v;	//0xCC4608CC
	PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM1_T osc0_c_orbit_post_crop_param1;	//0xCC4608D0
	PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM2_T osc0_c_orbit_post_crop_param2;	//0xCC4608D4
	PE_O24_OSC0_C_ORBIT_POST_CROP_PARAM3_T osc0_c_orbit_post_crop_param3;	//0xCC4608D8
	PE_O24_OSC0_C_ORBIT_COEFF_EN_T            osc0_c_orbit_coeff_en;	//0xCC4608DC
	UINT32                                                   reserved13;	//0xCC4608E0
	UINT32                                                   reserved14;	//0xCC4608E4
	PE_O24_OSC0_C_ORBIT_V1_FIR_COEF_CTRL_T osc0_c_orbit_v1_fir_coef_ctrl;	//0xCC4608E8
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA0_T osc0_c_orbit_v1_y_fir_coef_data0;	//0xCC4608EC
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA1_T osc0_c_orbit_v1_y_fir_coef_data1;	//0xCC4608F0
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA2_T osc0_c_orbit_v1_y_fir_coef_data2;	//0xCC4608F4
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA3_T osc0_c_orbit_v1_y_fir_coef_data3;	//0xCC4608F8
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA4_T osc0_c_orbit_v1_y_fir_coef_data4;	//0xCC4608FC
	PE_O24_OSC0_C_ORBIT_V1_Y_FIR_COEF_DATA5_T osc0_c_orbit_v1_y_fir_coef_data5;	//0xCC460900
	UINT32                                                   reserved15;	//0xCC460904
	UINT32                                                   reserved16;	//0xCC460908
	UINT32                                                   reserved17;	//0xCC46090C
	UINT32                                                   reserved18;	//0xCC460910
	UINT32                                                   reserved19;	//0xCC460914
	PE_O24_OSC0_C_ORBIT_H1_FIR_COEF_CTRL_T osc0_c_orbit_h1_fir_coef_ctrl;	//0xCC460918
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA0_T osc0_c_orbit_h1_y_fir_coef_data0;	//0xCC46091C
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA1_T osc0_c_orbit_h1_y_fir_coef_data1;	//0xCC460920
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA2_T osc0_c_orbit_h1_y_fir_coef_data2;	//0xCC460924
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA3_T osc0_c_orbit_h1_y_fir_coef_data3;	//0xCC460928
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA4_T osc0_c_orbit_h1_y_fir_coef_data4;	//0xCC46092C
	PE_O24_OSC0_C_ORBIT_H1_Y_FIR_COEF_DATA5_T osc0_c_orbit_h1_y_fir_coef_data5;	//0xCC460930
}PE_OSC0_C_REG_O24_T;

typedef struct {
	PE_O24_OSC1_C_CTRL_T                                osc1_c_ctrl;	//0xCC460C00
	PE_O24_OSC1_C_MIF_RD_SIZE_T                  osc1_c_mif_rd_size;	//0xCC460C04
	PE_O24_OSC1_C_OUTSIZE_T                          osc1_c_outsize;	//0xCC460C08
	PE_O24_OSC1_C_MIN_MAX_CTRL_T                osc1_c_min_max_ctrl;	//0xCC460C0C
	PE_O24_OSC1_C_CTRL1_T                              osc1_c_ctrl1;	//0xCC460C10
	PE_O24_OSC1_C_CROP_PARAM1_T                  osc1_c_crop_param1;	//0xCC460C14
	PE_O24_OSC1_C_CROP_PARAM2_T                  osc1_c_crop_param2;	//0xCC460C18
	PE_O24_OSC1_C_CROP_PARAM3_T                  osc1_c_crop_param3;	//0xCC460C1C
	PE_O24_OSC1_C_PHASE_OFFSET_T                osc1_c_phase_offset;	//0xCC460C20
	PE_O24_OSC1_C_SAMPLING_H_T                    osc1_c_sampling_h;	//0xCC460C24
	PE_O24_OSC1_C_SAMPLING_V_T                    osc1_c_sampling_v;	//0xCC460C28
	PE_O24_OSC1_C_POST_CROP_PARAM1_T        osc1_c_post_crop_param1;	//0xCC460C2C
	PE_O24_OSC1_C_POST_CROP_PARAM2_T        osc1_c_post_crop_param2;	//0xCC460C30
	PE_O24_OSC1_C_POST_CROP_PARAM3_T        osc1_c_post_crop_param3;	//0xCC460C34
	PE_O24_OSC1_C_MIF_RD_T                            osc1_c_mif_rd;	//0xCC460C38
	UINT32                                                    reserved0;	//0xCC460C3C
	UINT32                                                    reserved1;	//0xCC460C40
	PE_O24_OSC1_C_V1_FIR_COEF_CTRL_T        osc1_c_v1_fir_coef_ctrl;	//0xCC460C44
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA0_T  osc1_c_v1_y_fir_coef_data0;	//0xCC460C48
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA1_T  osc1_c_v1_y_fir_coef_data1;	//0xCC460C4C
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA2_T  osc1_c_v1_y_fir_coef_data2;	//0xCC460C50
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA3_T  osc1_c_v1_y_fir_coef_data3;	//0xCC460C54
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA4_T  osc1_c_v1_y_fir_coef_data4;	//0xCC460C58
	PE_O24_OSC1_C_V1_Y_FIR_COEF_DATA5_T  osc1_c_v1_y_fir_coef_data5;	//0xCC460C5C
	UINT32                                                    reserved2;	//0xCC460C60
	UINT32                                                    reserved3;	//0xCC460C64
	UINT32                                                    reserved4;	//0xCC460C68
	UINT32                                                    reserved5;	//0xCC460C6C
	UINT32                                                    reserved6;	//0xCC460C70
	PE_O24_OSC1_C_H1_FIR_COEF_CTRL_T        osc1_c_h1_fir_coef_ctrl;	//0xCC460C74
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA0_T  osc1_c_h1_y_fir_coef_data0;	//0xCC460C78
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA1_T  osc1_c_h1_y_fir_coef_data1;	//0xCC460C7C
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA2_T  osc1_c_h1_y_fir_coef_data2;	//0xCC460C80
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA3_T  osc1_c_h1_y_fir_coef_data3;	//0xCC460C84
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA4_T  osc1_c_h1_y_fir_coef_data4;	//0xCC460C88
	PE_O24_OSC1_C_H1_Y_FIR_COEF_DATA5_T  osc1_c_h1_y_fir_coef_data5;	//0xCC460C8C
}PE_OSC1_C_REG_O24_T;


typedef struct {
	PE_O24_OSC2_Y_VCNT_IN_T                            osc2_y_vcnt_in;	//0xCC460E00
	PE_O24_OSC2_Y_CTRL0_T                                osc2_y_ctrl0;	//0xCC460E04
	PE_O24_OSC2_Y_CTRL1_T                                osc2_y_ctrl1;	//0xCC460E08
	PE_O24_OSC2_Y_MIF_RD_SIZE_T                    osc2_y_mif_rd_size;	//0xCC460E0C
	PE_O24_OSC2_Y_CROP_PARAM1_T                    osc2_y_crop_param1;	//0xCC460E10
	PE_O24_OSC2_Y_CROP_PARAM2_T                    osc2_y_crop_param2;	//0xCC460E14
	PE_O24_OSC2_Y_CROP_PARAM3_T                    osc2_y_crop_param3;	//0xCC460E18
	PE_O24_OSC2_Y_MIF_RD_T                              osc2_y_mif_rd;	//0xCC460E1C
	UINT32                                                    reserved0;	//0xCC460E20
	UINT32                                                    reserved1;	//0xCC460E24
	UINT32                                                    reserved2;	//0xCC460E28
	UINT32                                                    reserved3;	//0xCC460E2C
	UINT32                                                    reserved4;	//0xCC460E30
	UINT32                                                    reserved5;	//0xCC460E34
	UINT32                                                    reserved6;	//0xCC460E38
	UINT32                                                    reserved7;	//0xCC460E3C
	UINT32                                                    reserved8;	//0xCC460E40
	UINT32                                                    reserved9;	//0xCC460E44
	UINT32                                                   reserved10;	//0xCC460E48
	UINT32                                                   reserved11;	//0xCC460E4C
	UINT32                                                   reserved12;	//0xCC460E50
	UINT32                                                   reserved13;	//0xCC460E54
	UINT32                                                   reserved14;	//0xCC460E58
	UINT32                                                   reserved15;	//0xCC460E5C
	UINT32                                                   reserved16;	//0xCC460E60
	UINT32                                                   reserved17;	//0xCC460E64
	UINT32                                                   reserved18;	//0xCC460E68
	UINT32                                                   reserved19;	//0xCC460E6C
	UINT32                                                   reserved20;	//0xCC460E70
	UINT32                                                   reserved21;	//0xCC460E74
	UINT32                                                   reserved22;	//0xCC460E78
	UINT32                                                   reserved23;	//0xCC460E7C
	PE_O24_OSC2_C_VCNT_IN_T                            osc2_c_vcnt_in;	//0xCC460E80
	PE_O24_OSC2_C_CTRL0_T                                osc2_c_ctrl0;	//0xCC460E84
	PE_O24_OSC2_C_CTRL1_T                                osc2_c_ctrl1;	//0xCC460E88
	PE_O24_OSC2_C_MIF_RD_SIZE_T                    osc2_c_mif_rd_size;	//0xCC460E8C
	PE_O24_OSC2_C_CROP_PARAM1_T                    osc2_c_crop_param1;	//0xCC460E90
	PE_O24_OSC2_C_CROP_PARAM2_T                    osc2_c_crop_param2;	//0xCC460E94
	PE_O24_OSC2_C_CROP_PARAM3_T                    osc2_c_crop_param3;	//0xCC460E98
	PE_O24_OSC2_C_MIF_RD_T                              osc2_c_mif_rd;	//0xCC460E9C
	PE_O24_OSC2_C_CS_CTRL_T                            osc2_c_cs_ctrl;	//0xCC460EA0
}PE_OSC2_YC_REG_O24_T;


typedef struct {
	PE_O24_OSC3_Y_VCNT_IN_T                            osc3_y_vcnt_in;	//0xCC461000
	PE_O24_OSC3_Y_CTRL0_T                                osc3_y_ctrl0;	//0xCC461004
	PE_O24_OSC3_Y_CTRL1_T                                osc3_y_ctrl1;	//0xCC461008
	PE_O24_OSC3_Y_MIF_RD_SIZE_T                    osc3_y_mif_rd_size;	//0xCC46100C
	PE_O24_OSC3_Y_CROP_PARAM1_T                    osc3_y_crop_param1;	//0xCC461010
	PE_O24_OSC3_Y_CROP_PARAM2_T                    osc3_y_crop_param2;	//0xCC461014
	PE_O24_OSC3_Y_CROP_PARAM3_T                    osc3_y_crop_param3;	//0xCC461018
	PE_O24_OSC3_Y_MIF_RD_T                              osc3_y_mif_rd;	//0xCC46101C
	UINT32                                                    reserved0;	//0xCC461020
	UINT32                                                    reserved1;	//0xCC461024
	UINT32                                                    reserved2;	//0xCC461028
	UINT32                                                    reserved3;	//0xCC46102C
	UINT32                                                    reserved4;	//0xCC461030
	UINT32                                                    reserved5;	//0xCC461034
	UINT32                                                    reserved6;	//0xCC461038
	UINT32                                                    reserved7;	//0xCC46103C
	UINT32                                                    reserved8;	//0xCC461040
	UINT32                                                    reserved9;	//0xCC461044
	UINT32                                                   reserved10;	//0xCC461048
	UINT32                                                   reserved11;	//0xCC46104C
	UINT32                                                   reserved12;	//0xCC461050
	UINT32                                                   reserved13;	//0xCC461054
	UINT32                                                   reserved14;	//0xCC461058
	UINT32                                                   reserved15;	//0xCC46105C
	UINT32                                                   reserved16;	//0xCC461060
	UINT32                                                   reserved17;	//0xCC461064
	UINT32                                                   reserved18;	//0xCC461068
	UINT32                                                   reserved19;	//0xCC46106C
	UINT32                                                   reserved20;	//0xCC461070
	UINT32                                                   reserved21;	//0xCC461074
	UINT32                                                   reserved22;	//0xCC461078
	UINT32                                                   reserved23;	//0xCC46107C
	PE_O24_OSC3_C_VCNT_IN_T                            osc3_c_vcnt_in;	//0xCC461080
	PE_O24_OSC3_C_CTRL0_T                                osc3_c_ctrl0;	//0xCC461084
	PE_O24_OSC3_C_CTRL1_T                                osc3_c_ctrl1;	//0xCC461088
	PE_O24_OSC3_C_MIF_RD_SIZE_T                    osc3_c_mif_rd_size;	//0xCC46108C
	PE_O24_OSC3_C_CROP_PARAM1_T                    osc3_c_crop_param1;	//0xCC461090
	PE_O24_OSC3_C_CROP_PARAM2_T                    osc3_c_crop_param2;	//0xCC461094
	PE_O24_OSC3_C_CROP_PARAM3_T                    osc3_c_crop_param3;	//0xCC461098
	PE_O24_OSC3_C_MIF_RD_T                              osc3_c_mif_rd;	//0xCC46109C
	PE_O24_OSC3_C_CS_CTRL_T                            osc3_c_cs_ctrl;	//0xCC4610A0
}PE_OSC3_YC_REG_O24_T;


#endif
