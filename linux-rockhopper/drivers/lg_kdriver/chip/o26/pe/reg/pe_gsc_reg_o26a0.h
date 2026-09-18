#ifndef _PE_GSC_REG_O26A0_1_H_
#define _PE_GSC_REG_O26A0_1_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70600 RW 0x0000_0002
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
	UINT32 resvd1                           :6;
	};
}PE_O26_OSC0_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70604 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70608 RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //width
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //height
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7060C RW 0x0000_0000
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
}PE_O26_OSC0_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70610 RW 0x0100_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input removed
	UINT32 resvd0                           :3;
	UINT32 reg_hsc_vsc_order                :1;	//(4,NA,0x0) //'0' : vsc -> hsc	 '1' : hsc -> vsc ( out width should be < 4096)
	UINT32 resvd1                           :12;
	UINT32 reg_mif_rd_ln_inc                :2;	//(18:17,NA,0x0) //Line number increment for MRD	Only use for 8k (8p, 2 line processing) sub samping mode	'0': 4k normal	'1': 4k 1/2 sub samgpling, 8k normal	'2': 4k 1/4 sub samgpling, 8k 1/2 sub sampling mode
	UINT32 resvd2                           :5;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd3                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O26_OSC0_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70614 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70618 RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7061C RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70620 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_O26_OSC0_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70624 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70628 RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7062C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC0_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70630 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70634 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70638 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset_l0            :14;	//(29:16,NA,0x0) //MRD V offset line 2
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70800 RW 0x0000_0002
	UINT32 reg_mif_rd_on                    :1;	//(0,NA,0x0) //'0' : MIF pre-read off (= select FMC direct source)	    '1' : MIF pre-read on  (= select MIF RD source )
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :2;	//(4:3,NA,0x0) //00 : (0       <= active width < 1024) : V8T 	01:  (1024 <= active width < 2048) : V4T 	11: (2048 <= active width               ) : V2T(bilinear)
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd0                           :14;
	UINT32 reg_v_cti_en                     :1;	//(20,NA,0x0) //
	UINT32 reg_v_cti_ratio                  :2;	//(22:21,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd2                           :4;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O26_OSC0_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70804 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70808 RW 0x0870_0F00
	UINT32 reg_hosize                       :14;	//(13:0,NA,0xF00) //
	UINT32 resvd0                           :2;
	UINT32 reg_vosize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7080C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}PE_O26_OSC0_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70810 RW 0x0100_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input removed
	UINT32 resvd0                           :3;
	UINT32 reg_hsc_vsc_order                :1;	//(4,NA,0x0) //'0' : vsc -> hsc	 '1' : hsc -> vsc ( out width should be < 4096)
	UINT32 resvd1                           :12;
	UINT32 reg_mif_rd_ln_inc                :2;	//(18:17,NA,0x0) //Line number increment for MRD	Only use for 8k (8p, 2 line processing) sub samping mode	'0': 4k normal	'1': 4k 1/2 sub samgpling, 8k normal	'2': 4k 1/4 sub samgpling, 8k 1/2 sub sampling mode
	UINT32 resvd2                           :5;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd3                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O26_OSC0_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70814 RW 0x0000_0000
	UINT32 reg_hoffset                      :14;	//(13:0,NA,0x0) //오프셋
	UINT32 resvd0                           :2;
	UINT32 reg_voffset                      :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70818 RW 0x0870_0F00
	UINT32 reg_hactive                      :14;	//(13:0,NA,0xF00) //액티브
	UINT32 resvd0                           :2;
	UINT32 reg_vactive                      :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7081C RW 0x0870_0F00
	UINT32 reg_hisize                       :14;	//(13:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :2;
	UINT32 reg_visize                       :14;	//(29:16,NA,0x870) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70820 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}PE_O26_OSC0_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70824 RW 0x0000_0000
	UINT32 reg_denominator_h                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_h                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70828 RW 0x0000_0000
	UINT32 reg_denominator_v                :14;	//(13:0,NA,0x0) //-
	UINT32 resvd0                           :2;
	UINT32 reg_numerator_v                  :14;	//(29:16,NA,0x0) //-
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7082C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_voffset                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC0_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70830 RW 0x0000_0000
	UINT32 reg_post_hactive                 :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_vactive                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70834 RW 0x0000_0000
	UINT32 reg_post_hisize                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_post_visize                  :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70838 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset_l0            :14;	//(29:16,NA,0x0) //MRD V offset line 2
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC0_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A00 RW 0x0000_0002
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
	UINT32 resvd2                           :4;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O26_OSC1_Y_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A04 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC1_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A08 RW 0x0870_0F00
	UINT32 reg_hosize                       :13;	//(12:0,NA,0xF00) //width
	UINT32 resvd0                           :3;
	UINT32 reg_vosize                       :13;	//(28:16,NA,0x870) //height
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A0C RW 0x0000_0000
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
}PE_O26_OSC1_Y_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A10 RW 0x0100_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input removed
	UINT32 resvd0                           :3;
	UINT32 reg_hsc_vsc_order                :1;	//(4,NA,0x0) //'0' : vsc -> hsc	 '1' : hsc -> vsc ( out width should be < 4096)
	UINT32 resvd1                           :19;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd2                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O26_OSC1_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A14 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A18 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A1C RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A20 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :7;
	};
}PE_O26_OSC1_Y_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A24 RW 0x0000_0000
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A28 RW 0x0000_0000
	UINT32 reg_denominator_v                :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A2C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC1_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A30 RW 0x0000_0000
	UINT32 reg_post_hactive                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A34 RW 0x0000_0000
	UINT32 reg_post_hisize                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize                  :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70A38 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset               :14;	//(29:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC1_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C00 RW 0x0000_0002
	UINT32 resvd0                           :1;
	UINT32 reg_vsc_en                       :1;	//(1,NA,0x1) //'0': v scaler off. Vsc buffer use as ring buffer	    '1': v scaler on
	UINT32 reg_spectacle_en                 :1;	//(2,NA,0x0) //'0': normal	    '1': spectacle mode enable
	UINT32 reg_vsc_mode                     :2;	//(4:3,NA,0x0) //00 : (0       <= active width < 1024) : V8T 	01:  (1024 <= active width < 2048) : V4T 	11: (2048 <= active width               ) : V2T(bilinear)
	UINT32 reg_bilinear_on                  :1;	//(5,NA,0x0) //'0' : polyphase filter	     '1' : bilinear
	UINT32 resvd1                           :14;
	UINT32 reg_v_cti_en                     :1;	//(20,NA,0x0) //
	UINT32 reg_v_cti_ratio                  :2;	//(22:21,NA,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd3                           :4;
	UINT32 reg_mode_32p                     :1;	//(30,NA,0x0) //'0' : 256 phase 	     '1' : 32 phase
	UINT32 reg_sampling_mode                :1;	//(31,NA,0x0) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O26_OSC1_C_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C04 RW 0x0000_0000
	UINT32 reg_hsize                        :14;	//(13:0,NA,0x0) //MRd size info. H
	UINT32 resvd                            :2;
	UINT32 reg_vsize                        :14;	//(29:16,NA,0x0) //MRd size info. V
	UINT32 reg_vinc                         :2;	//(31:30,NA,0x0) //V increment for  MRD
	};
}PE_O26_OSC1_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C08 RW 0x0870_0F00
	UINT32 reg_hosize                       :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_vosize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_OUTSIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C0C RW 0x0000_0000
	UINT32 reg_min_max_on_l_h               :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_min_max_on_l_v               :1;	//(16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_min_max_th_l_v               :9;	//(28:20,NA,0x0) //
	UINT32 adaptive_fir_v_mode              :1;	//(29,NA,0x0) //'0' : old alg ( M16PB0)	 '1' : new alg ( O18/M16PP )
	UINT32 resvd2                           :2;
	};
}PE_O26_OSC1_C_MIN_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C10 RW 0x0100_0000
	UINT32 reg_gpd_sel                      :1;	//(0,NA,0x0) //'0' : normal	 '1' : GPD input removed
	UINT32 resvd0                           :3;
	UINT32 reg_hsc_vsc_order                :1;	//(4,NA,0x0) //'0' : vsc -> hsc	 '1' : hsc -> vsc ( out width should be < 4096)
	UINT32 resvd1                           :19;
	UINT32 reg_mif_rd_v_inc                 :3;	//(26:24,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd2                           :2;
	UINT32 reg_mif_rd_v_repeat              :3;	//(31:29,NA,0x0) //V repeat for MRD
	};
}PE_O26_OSC1_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C14 RW 0x0000_0000
	UINT32 reg_hoffset                      :13;	//(12:0,NA,0x0) //오프셋
	UINT32 resvd0                           :3;
	UINT32 reg_voffset                      :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C18 RW 0x0870_0F00
	UINT32 reg_hactive                      :13;	//(12:0,NA,0xF00) //액티브
	UINT32 resvd0                           :3;
	UINT32 reg_vactive                      :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C1C RW 0x0870_0F00
	UINT32 reg_hisize                       :13;	//(12:0,NA,0xF00) //전체크기
	UINT32 resvd0                           :3;
	UINT32 reg_visize                       :13;	//(28:16,NA,0x870) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C20 RW 0x0000_0000
	UINT32 reg_phase_off_v                  :9;	//(8:0,NA,0x0) //-
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_h                  :9;	//(24:16,NA,0x0) //-
	UINT32 resvd1                           :7;
	};
}PE_O26_OSC1_C_PHASE_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C24 RW 0x0000_0000
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x0) //-
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_h                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_SAMPLING_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C28 RW 0x0000_0000
	UINT32 reg_denominator_v                :12;	//(11:0,NA,0x0) //-
	UINT32 resvd0                           :4;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x0) //-
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_SAMPLING_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C2C RW 0x0000_0000
	UINT32 reg_post_hoffset                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_voffset                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC1_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C30 RW 0x0000_0000
	UINT32 reg_post_hactive                 :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_vactive                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C34 RW 0x0000_0000
	UINT32 reg_post_hisize                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_post_visize                  :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_OSC1_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70C38 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_mif_rd_voffset               :14;	//(29:16,NA,0x0) //MRD V offset
	UINT32 resvd1                           :2;
	};
}PE_O26_OSC1_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E00 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O26_OSC2_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E04 RW 0x0000_0010
	UINT32 reg_input_sel                    :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source Removed	    '1': select GPU (ARFG, AYUV) source
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_disable                :1;	//(4,NA,0x1) //'0': ARGB data input (Graphic data)	    '1': YUV data input (Video data). Alpha path ready to "0"
	UINT32 resvd1                           :27;
	};
}PE_O26_OSC2_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E08 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O26_OSC2_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E0C RW 0x0000_0000
	UINT32 reg_hsize                        :12;	//(11:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :4;
	UINT32 reg_vsize                        :12;	//(27:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E10 RW 0x0000_0000
	UINT32 reg_hoffset                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_voffset                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E14 RW 0x0870_0F00
	UINT32 reg_hactive                      :12;	//(11:0,NA,0xF00) //
	UINT32 resvd0                           :4;
	UINT32 reg_vactive                      :12;	//(27:16,NA,0x870) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E18 RW 0x0870_0F00
	UINT32 reg_hisize                       :12;	//(11:0,NA,0xF00) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd0                           :4;
	UINT32 reg_visize                       :12;	//(27:16,NA,0x870) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E1C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :12;	//(27:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :4;
	};
}PE_O26_OSC2_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E20 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_voffset                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC2_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E24 RW 0x0000_0000
	UINT32 reg_post_hactive                 :12;	//(11:0,NA,0x0) //tpg width set
	UINT32 resvd0                           :4;
	UINT32 reg_post_vactive                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC70E28 RW 0x0000_0000
	UINT32 reg_post_hisize                  :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_visize                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71200 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O26_OSC2_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71204 RW 0x0000_0000
	UINT32 reg_input_sel                    :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source Removed	    '1': select GPU (ARFG, AYUV) source
	UINT32 resvd                            :31;
	};
}PE_O26_OSC2_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71208 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O26_OSC2_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7120C RW 0x0000_0000
	UINT32 reg_hsize                        :12;	//(11:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :4;
	UINT32 reg_vsize                        :12;	//(27:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71210 RW 0x0000_0000
	UINT32 reg_hoffset                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_voffset                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71214 RW 0x0870_0F00
	UINT32 reg_hactive                      :12;	//(11:0,NA,0xF00) //
	UINT32 resvd0                           :4;
	UINT32 reg_vactive                      :12;	//(27:16,NA,0x870) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71218 RW 0x0870_0F00
	UINT32 reg_hisize                       :12;	//(11:0,NA,0xF00) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd0                           :4;
	UINT32 reg_visize                       :12;	//(27:16,NA,0x870) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7121C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :12;	//(27:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :4;
	};
}PE_O26_OSC2_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71220 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_voffset                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC2_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71224 RW 0x0000_0000
	UINT32 reg_post_hactive                 :12;	//(11:0,NA,0x0) //tpg width set
	UINT32 resvd0                           :4;
	UINT32 reg_post_vactive                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71228 RW 0x0000_0000
	UINT32 reg_post_hisize                  :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_visize                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC2_C_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71600 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O26_OSC3_Y_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71604 RW 0x0000_0010
	UINT32 reg_input_sel                    :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source Removed	    '1': select GPU (ARFG, AYUV) source
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_disable                :1;	//(4,NA,0x1) //'0': ARGB data input (Graphic data)	    '1': YUV data input (Video data). Alpha path ready to "0"
	UINT32 resvd1                           :27;
	};
}PE_O26_OSC3_Y_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71608 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O26_OSC3_Y_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7160C RW 0x0000_0000
	UINT32 reg_hsize                        :12;	//(11:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :4;
	UINT32 reg_vsize                        :12;	//(27:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71610 RW 0x0000_0000
	UINT32 reg_hoffset                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_voffset                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71614 RW 0x0870_0F00
	UINT32 reg_hactive                      :12;	//(11:0,NA,0xF00) //
	UINT32 resvd0                           :4;
	UINT32 reg_vactive                      :12;	//(27:16,NA,0x870) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71618 RW 0x0870_0F00
	UINT32 reg_hisize                       :12;	//(11:0,NA,0xF00) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd0                           :4;
	UINT32 reg_visize                       :12;	//(27:16,NA,0x870) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC7161C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :12;	//(27:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :4;
	};
}PE_O26_OSC3_Y_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71620 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_voffset                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC3_Y_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71624 RW 0x0000_0000
	UINT32 reg_post_hactive                 :12;	//(11:0,NA,0x0) //tpg width set
	UINT32 resvd0                           :4;
	UINT32 reg_post_vactive                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71628 RW 0x0000_0000
	UINT32 reg_post_hisize                  :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_visize                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_Y_POST_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A00 RO 0x0000_0000
	UINT32 vcnt_in                          :12;	//(11:0,NA,0x0) //
	UINT32 resvd                            :20;
	};
}PE_O26_OSC3_C_VCNT_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A04 RW 0x0000_0000
	UINT32 reg_input_sel                    :1;	//(0,NA,0x0) //'0': normal	    '1': select GPD source Removed	    '1': select GPU (ARFG, AYUV) source
	UINT32 resvd                            :31;
	};
}PE_O26_OSC3_C_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A08 RW 0x0000_0000
	UINT32 reg_crop_en                      :1;	//(0,NA,0x0) //'0' : crop off	    '1' : crop on
	UINT32 resvd0                           :24;
	UINT32 reg_v_reverse                    :1;	//(25,NA,0x0) //'0' : v_reverse_off	     '1' : v_reverse_on
	UINT32 resvd1                           :6;
	};
}PE_O26_OSC3_C_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A0C RW 0x0000_0000
	UINT32 reg_hsize                        :12;	//(11:0,NA,0x0) //MRd size info. H
	UINT32 resvd0                           :4;
	UINT32 reg_vsize                        :12;	//(27:16,NA,0x0) //MRd size info. V
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_MIF_RD_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A10 RW 0x0000_0000
	UINT32 reg_hoffset                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_voffset                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A14 RW 0x0870_0F00
	UINT32 reg_hactive                      :12;	//(11:0,NA,0xF00) //
	UINT32 resvd0                           :4;
	UINT32 reg_vactive                      :12;	//(27:16,NA,0x870) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A18 RW 0x0870_0F00
	UINT32 reg_hisize                       :12;	//(11:0,NA,0xF00) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd0                           :4;
	UINT32 reg_visize                       :12;	//(27:16,NA,0x870) //Input of Post crop AND Output of Scaler OUT
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_CROP_PARAM3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A1C RW 0x0000_0010
	UINT32 reg_mif_rd_v_repeat              :3;	//(2:0,NA,0x0) //V repeat for MRD
	UINT32 resvd0                           :1;
	UINT32 reg_mif_rd_v_inc                 :3;	//(6:4,NA,0x1) //V increament for MRD	'0': Do not use	'1': normal mode	'2': 1/2 sub sampling mode	'4': 1/4 sub sampling mode
	UINT32 resvd1                           :9;
	UINT32 reg_mif_rd_voffset               :12;	//(27:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :4;
	};
}PE_O26_OSC3_C_MIF_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A20 RW 0x0000_0000
	UINT32 reg_post_hoffset                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_voffset                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_post_crop_en                 :1;	//(31,NA,0x0) //output crop enable
	};
}PE_O26_OSC3_C_POST_CROP_PARAM1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A24 RW 0x0000_0000
	UINT32 reg_post_hactive                 :12;	//(11:0,NA,0x0) //tpg width set
	UINT32 resvd0                           :4;
	UINT32 reg_post_vactive                 :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_POST_CROP_PARAM2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC71A28 RW 0x0000_0000
	UINT32 reg_post_hisize                  :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_post_visize                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_OSC3_C_POST_CROP_PARAM3_T;

typedef struct {
	PE_O26_OSC0_Y_CTRL_T                                osc0_y_ctrl;	//0xCCC70600
	PE_O26_OSC0_Y_MIF_RD_SIZE_T                  osc0_y_mif_rd_size;	//0xCCC70604
	PE_O26_OSC0_Y_OUTSIZE_T                          osc0_y_outsize;	//0xCCC70608
	PE_O26_OSC0_Y_MIN_MAX_CTRL_T                osc0_y_min_max_ctrl;	//0xCCC7060C
	PE_O26_OSC0_Y_CTRL1_T                              osc0_y_ctrl1;	//0xCCC70610
	PE_O26_OSC0_Y_CROP_PARAM1_T                  osc0_y_crop_param1;	//0xCCC70614
	PE_O26_OSC0_Y_CROP_PARAM2_T                  osc0_y_crop_param2;	//0xCCC70618
	PE_O26_OSC0_Y_CROP_PARAM3_T                  osc0_y_crop_param3;	//0xCCC7061C
	PE_O26_OSC0_Y_PHASE_OFFSET_T                osc0_y_phase_offset;	//0xCCC70620
	PE_O26_OSC0_Y_SAMPLING_H_T                    osc0_y_sampling_h;	//0xCCC70624
	PE_O26_OSC0_Y_SAMPLING_V_T                    osc0_y_sampling_v;	//0xCCC70628
	PE_O26_OSC0_Y_POST_CROP_PARAM1_T        osc0_y_post_crop_param1;	//0xCCC7062C
	PE_O26_OSC0_Y_POST_CROP_PARAM2_T        osc0_y_post_crop_param2;	//0xCCC70630
	PE_O26_OSC0_Y_POST_CROP_PARAM3_T        osc0_y_post_crop_param3;	//0xCCC70634
	PE_O26_OSC0_Y_MIF_RD_T                            osc0_y_mif_rd;	//0xCCC70638
}PE_OSC0_Y_REG_O26_T;

typedef struct {
	PE_O26_OSC0_C_CTRL_T                                osc0_c_ctrl;	//0xCCC70800
	PE_O26_OSC0_C_MIF_RD_SIZE_T                  osc0_c_mif_rd_size;	//0xCCC70804
	PE_O26_OSC0_C_OUTSIZE_T                          osc0_c_outsize;	//0xCCC70808
	PE_O26_OSC0_C_MIN_MAX_CTRL_T                osc0_c_min_max_ctrl;	//0xCCC7080C
	PE_O26_OSC0_C_CTRL1_T                              osc0_c_ctrl1;	//0xCCC70810
	PE_O26_OSC0_C_CROP_PARAM1_T                  osc0_c_crop_param1;	//0xCCC70814
	PE_O26_OSC0_C_CROP_PARAM2_T                  osc0_c_crop_param2;	//0xCCC70818
	PE_O26_OSC0_C_CROP_PARAM3_T                  osc0_c_crop_param3;	//0xCCC7081C
	PE_O26_OSC0_C_PHASE_OFFSET_T                osc0_c_phase_offset;	//0xCCC70820
	PE_O26_OSC0_C_SAMPLING_H_T                    osc0_c_sampling_h;	//0xCCC70824
	PE_O26_OSC0_C_SAMPLING_V_T                    osc0_c_sampling_v;	//0xCCC70828
	PE_O26_OSC0_C_POST_CROP_PARAM1_T        osc0_c_post_crop_param1;	//0xCCC7082C
	PE_O26_OSC0_C_POST_CROP_PARAM2_T        osc0_c_post_crop_param2;	//0xCCC70830
	PE_O26_OSC0_C_POST_CROP_PARAM3_T        osc0_c_post_crop_param3;	//0xCCC70834
	PE_O26_OSC0_C_MIF_RD_T                            osc0_c_mif_rd;	//0xCCC70838
}PE_OSC0_C_REG_O26_T;

typedef struct {
	PE_O26_OSC1_Y_CTRL_T                                osc1_y_ctrl;	//0xCCC70A00
	PE_O26_OSC1_Y_MIF_RD_SIZE_T                  osc1_y_mif_rd_size;	//0xCCC70A04
	PE_O26_OSC1_Y_OUTSIZE_T                          osc1_y_outsize;	//0xCCC70A08
	PE_O26_OSC1_Y_MIN_MAX_CTRL_T                osc1_y_min_max_ctrl;	//0xCCC70A0C
	PE_O26_OSC1_Y_CTRL1_T                              osc1_y_ctrl1;	//0xCCC70A10
	PE_O26_OSC1_Y_CROP_PARAM1_T                  osc1_y_crop_param1;	//0xCCC70A14
	PE_O26_OSC1_Y_CROP_PARAM2_T                  osc1_y_crop_param2;	//0xCCC70A18
	PE_O26_OSC1_Y_CROP_PARAM3_T                  osc1_y_crop_param3;	//0xCCC70A1C
	PE_O26_OSC1_Y_PHASE_OFFSET_T                osc1_y_phase_offset;	//0xCCC70A20
	PE_O26_OSC1_Y_SAMPLING_H_T                    osc1_y_sampling_h;	//0xCCC70A24
	PE_O26_OSC1_Y_SAMPLING_V_T                    osc1_y_sampling_v;	//0xCCC70A28
	PE_O26_OSC1_Y_POST_CROP_PARAM1_T        osc1_y_post_crop_param1;	//0xCCC70A2C
	PE_O26_OSC1_Y_POST_CROP_PARAM2_T        osc1_y_post_crop_param2;	//0xCCC70A30
	PE_O26_OSC1_Y_POST_CROP_PARAM3_T        osc1_y_post_crop_param3;	//0xCCC70A34
	PE_O26_OSC1_Y_MIF_RD_T                            osc1_y_mif_rd;	//0xCCC70A38
}PE_OSC1_Y_REG_O26_T;

typedef struct {
	PE_O26_OSC1_C_CTRL_T                                osc1_c_ctrl;	//0xCCC70C00
	PE_O26_OSC1_C_MIF_RD_SIZE_T                  osc1_c_mif_rd_size;	//0xCCC70C04
	PE_O26_OSC1_C_OUTSIZE_T                          osc1_c_outsize;	//0xCCC70C08
	PE_O26_OSC1_C_MIN_MAX_CTRL_T                osc1_c_min_max_ctrl;	//0xCCC70C0C
	PE_O26_OSC1_C_CTRL1_T                              osc1_c_ctrl1;	//0xCCC70C10
	PE_O26_OSC1_C_CROP_PARAM1_T                  osc1_c_crop_param1;	//0xCCC70C14
	PE_O26_OSC1_C_CROP_PARAM2_T                  osc1_c_crop_param2;	//0xCCC70C18
	PE_O26_OSC1_C_CROP_PARAM3_T                  osc1_c_crop_param3;	//0xCCC70C1C
	PE_O26_OSC1_C_PHASE_OFFSET_T                osc1_c_phase_offset;	//0xCCC70C20
	PE_O26_OSC1_C_SAMPLING_H_T                    osc1_c_sampling_h;	//0xCCC70C24
	PE_O26_OSC1_C_SAMPLING_V_T                    osc1_c_sampling_v;	//0xCCC70C28
	PE_O26_OSC1_C_POST_CROP_PARAM1_T        osc1_c_post_crop_param1;	//0xCCC70C2C
	PE_O26_OSC1_C_POST_CROP_PARAM2_T        osc1_c_post_crop_param2;	//0xCCC70C30
	PE_O26_OSC1_C_POST_CROP_PARAM3_T        osc1_c_post_crop_param3;	//0xCCC70C34
	PE_O26_OSC1_C_MIF_RD_T                            osc1_c_mif_rd;	//0xCCC70C38
}PE_OSC1_C_REG_O26_T;

typedef struct {
	PE_O26_OSC2_Y_VCNT_IN_T                          osc2_y_vcnt_in;	//0xCCC70E00
	PE_O26_OSC2_Y_CTRL0_T                              osc2_y_ctrl0;	//0xCCC70E04
	PE_O26_OSC2_Y_CTRL1_T                              osc2_y_ctrl1;	//0xCCC70E08
	PE_O26_OSC2_Y_MIF_RD_SIZE_T                  osc2_y_mif_rd_size;	//0xCCC70E0C
	PE_O26_OSC2_Y_CROP_PARAM1_T                  osc2_y_crop_param1;	//0xCCC70E10
	PE_O26_OSC2_Y_CROP_PARAM2_T                  osc2_y_crop_param2;	//0xCCC70E14
	PE_O26_OSC2_Y_CROP_PARAM3_T                  osc2_y_crop_param3;	//0xCCC70E18
	PE_O26_OSC2_Y_MIF_RD_T                            osc2_y_mif_rd;	//0xCCC70E1C
	PE_O26_OSC2_Y_POST_CROP_PARAM1_T        osc2_y_post_crop_param1;	//0xCCC70E20
	PE_O26_OSC2_Y_POST_CROP_PARAM2_T        osc2_y_post_crop_param2;	//0xCCC70E24
	PE_O26_OSC2_Y_POST_CROP_PARAM3_T        osc2_y_post_crop_param3;	//0xCCC70E28
}PE_OSC2_Y_REG_O26_T;

typedef struct {
	PE_O26_OSC2_C_VCNT_IN_T                          osc2_c_vcnt_in;	//0xCCC71200
	PE_O26_OSC2_C_CTRL0_T                              osc2_c_ctrl0;	//0xCCC71204
	PE_O26_OSC2_C_CTRL1_T                              osc2_c_ctrl1;	//0xCCC71208
	PE_O26_OSC2_C_MIF_RD_SIZE_T                  osc2_c_mif_rd_size;	//0xCCC7120C
	PE_O26_OSC2_C_CROP_PARAM1_T                  osc2_c_crop_param1;	//0xCCC71210
	PE_O26_OSC2_C_CROP_PARAM2_T                  osc2_c_crop_param2;	//0xCCC71214
	PE_O26_OSC2_C_CROP_PARAM3_T                  osc2_c_crop_param3;	//0xCCC71218
	PE_O26_OSC2_C_MIF_RD_T                            osc2_c_mif_rd;	//0xCCC7121C
	PE_O26_OSC2_C_POST_CROP_PARAM1_T        osc2_c_post_crop_param1;	//0xCCC71220
	PE_O26_OSC2_C_POST_CROP_PARAM2_T        osc2_c_post_crop_param2;	//0xCCC71224
	PE_O26_OSC2_C_POST_CROP_PARAM3_T        osc2_c_post_crop_param3;	//0xCCC71228
}PE_OSC2_C_REG_O26_T;

typedef struct {
	PE_O26_OSC3_Y_VCNT_IN_T                          osc3_y_vcnt_in;	//0xCCC71600
	PE_O26_OSC3_Y_CTRL0_T                              osc3_y_ctrl0;	//0xCCC71604
	PE_O26_OSC3_Y_CTRL1_T                              osc3_y_ctrl1;	//0xCCC71608
	PE_O26_OSC3_Y_MIF_RD_SIZE_T                  osc3_y_mif_rd_size;	//0xCCC7160C
	PE_O26_OSC3_Y_CROP_PARAM1_T                  osc3_y_crop_param1;	//0xCCC71610
	PE_O26_OSC3_Y_CROP_PARAM2_T                  osc3_y_crop_param2;	//0xCCC71614
	PE_O26_OSC3_Y_CROP_PARAM3_T                  osc3_y_crop_param3;	//0xCCC71618
	PE_O26_OSC3_Y_MIF_RD_T                            osc3_y_mif_rd;	//0xCCC7161C
	PE_O26_OSC3_Y_POST_CROP_PARAM1_T        osc3_y_post_crop_param1;	//0xCCC71620
	PE_O26_OSC3_Y_POST_CROP_PARAM2_T        osc3_y_post_crop_param2;	//0xCCC71624
	PE_O26_OSC3_Y_POST_CROP_PARAM3_T        osc3_y_post_crop_param3;	//0xCCC71628
}PE_OSC3_Y_REG_O26_T;

typedef struct {
	PE_O26_OSC3_C_VCNT_IN_T                          osc3_c_vcnt_in;	//0xCCC71A00
	PE_O26_OSC3_C_CTRL0_T                              osc3_c_ctrl0;	//0xCCC71A04
	PE_O26_OSC3_C_CTRL1_T                              osc3_c_ctrl1;	//0xCCC71A08
	PE_O26_OSC3_C_MIF_RD_SIZE_T                  osc3_c_mif_rd_size;	//0xCCC71A0C
	PE_O26_OSC3_C_CROP_PARAM1_T                  osc3_c_crop_param1;	//0xCCC71A10
	PE_O26_OSC3_C_CROP_PARAM2_T                  osc3_c_crop_param2;	//0xCCC71A14
	PE_O26_OSC3_C_CROP_PARAM3_T                  osc3_c_crop_param3;	//0xCCC71A18
	PE_O26_OSC3_C_MIF_RD_T                            osc3_c_mif_rd;	//0xCCC71A1C
	PE_O26_OSC3_C_POST_CROP_PARAM1_T        osc3_c_post_crop_param1;	//0xCCC71A20
	PE_O26_OSC3_C_POST_CROP_PARAM2_T        osc3_c_post_crop_param2;	//0xCCC71A24
	PE_O26_OSC3_C_POST_CROP_PARAM3_T        osc3_c_post_crop_param3;	//0xCCC71A28
}PE_OSC3_C_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41400  RW 0x0000_0000
	UINT32 use_vlb                          :1;	//(0:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 use_vcp                          :1;	//(4:4,NA,0x0) //
	UINT32 resvd1                           :3; //(7:5,NA,0x0) //
	UINT32 use_glb                          :1;	//(8:8,NA,0x0) //
	UINT32 resvd2                           :23;
	};
}PE_O26_FMC_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41404  RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_FMC_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC41408  RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_FMC_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC4140C  RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_FMC_VERI_SYS_VERI_3_T;


typedef struct {
	PE_O26_FMC_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCCC41400 
	PE_O26_FMC_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCCC41404
	PE_O26_FMC_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCCC41408
	PE_O26_FMC_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCCC4140C
}PE_FMC_VERI_REG_O26_T;

#endif
