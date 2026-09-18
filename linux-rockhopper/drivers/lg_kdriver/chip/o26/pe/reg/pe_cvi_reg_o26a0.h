#ifndef _PE_CVI_REG_O26A0_H_
#define _PE_CVI_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0200 RW 0x0008_0024
	UINT32 scan_type                        :1;	//(0,RW,0x00) //0 := interlaced	1  = progressive
	UINT32 field_gen_mode                   :2;	//(2:1,RW,0x02) //00  = Auto field	01  = Inverse of Auto field	10 := Input field	11  = Inverse of Input field
	UINT32 auto_field_gen                   :2;	//(4:3,RW,0x00) //00 := use input hsync	01  = use pseudo hsync1	10  = use pseudo hsync2
	UINT32 reserved                         :1;	//(5,RW,0x01) //
	UINT32 chroma_sampling                  :1;	//(6,RW,0x00) //Chroma up-sampling method when data_bit_mode = '0'	0 := mean filter	1  = pixel repetition
	UINT32 aspect_ratio                     :1;	//(7,RW,0x00) //0 := 4:3	1  = 16:9
	UINT32 yc_delay_mode_r                  :2;	//(9:8,RW,0x00) //00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 yc_delay_mode_b                  :2;	//(11:10,RW,0x00) //00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 yc_delay_mode_g                  :2;	//(13:12,RW,0x00) //00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 data_in_sel                      :4;	//(17:14,RW,0x00) //0000 := HDMI_A	0010  = HDMI_B	0100  = HDMI_C	0110  = HDMI_D	1000  = CVD	1001  = Component	1010  = HDMI_E	1100  = DSC	1110  = FEC
	UINT32 resvd                            :1;
	UINT32 auto_sync_polarity               :1;	//(19,RW,0x01) //0 = disable	1 := enable
	UINT32 manual_sync_polarity             :2;	//(21:20,RW,0x00) //00 := H = negative sync(active_high), V = negative sync(active_high)	01 =  H = negative sync(active_high), V = positive sync(active_low)	10 =  H =  positive sync(active_low), V = negative sync(active_high)	11 =  H =  positive sync(active_low), V =  positive sync(active_low)
	UINT32 adc_cut_direction                :1;	//(22,RW,0x00) //this bit is just only valid when adc_bit_sel = '1'	0 := MSB 8bit 	1  = LSB 8bit
	UINT32 adc_bit_sel                      :1;	//(23,RW,0x00) //0 := 10bit data	1  = 8 bit data (LSB 2bit's numbering is selected by bit_numbering_lsb2)
	UINT32 br_port_swap                     :1;	//(24,RW,0x00) //This bit swaps the B and R port	0 := normal	1  = B and R port swap
	UINT32 r_port_swap                      :1;	//(25,RW,0x00) //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 b_port_swap                      :1;	//(26,RW,0x00) //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 g_port_swap                      :1;	//(27,RW,0x00) //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 bit_numbering_lsb2               :3;	//(30:28,RW,0x00) //This function is just only valid when adc_bit_sel = '1'.	000 := LSB 2bit is "00"	001  = LSB 2bit is "01"	010  = LSB 2bit is "10"	011  = LSB 2bit is "11"	100  = LSB 2bit is rotating on "00", "01", "10", "11"	101  = LSB 2bit is repeat own data(1 downto 0)
	UINT32 data_en_mode                     :1;	//(31,RW,0x00) //0 := Internal Hactive is made by hsync and de	1  = Internal Hactive is made by de (Hoffset & Voffset should be 0x0000)
	};
}PE_O26_CVI_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0204 RW 0x0026_0094
	UINT32 offset_h                         :16;	//(15:0,RW,0x94) //pixel number [Max 4095]
	UINT32 offset_v                         :16;	//(31:16,RW,0x26) //line number [Max 4095]
	};
}PE_O26_CVI_OFFSET_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0208 RW 0x0438_0780
	UINT32 size_h                           :16;	//(15:0,RW,0x780) //pixel number [Max 4095]
	UINT32 size_v                           :16;	//(31:16,RW,0x438) //line number [Max 4095]
	};
}PE_O26_CVI_SIZE_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E020C RW 0x0010_003E
	UINT32 res_hsync                        :10;	//(9:0,RW,0x03E) //For debug horizontal reshape sync timing
	UINT32 resvd0                           :6;
	UINT32 res_hfp                          :10;	//(25:16,RW,0x010) //For debug horizontal reshape front porch timing
	UINT32 resvd1                           :6;
	};
}PE_O26_CVI_INT_SYNC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0210 RW 0x0001_0700
	UINT32 res_vfp                          :5;	//(4:0,RW,0x0) //For Debug vertical reshape front porch timing
	UINT32 resvd0                           :3;
	UINT32 res_vsync                        :5;	//(12:8,RW,0x7) //For Debug vertical reshape sync timing
	UINT32 res_field_add_line               :2;	//(14:13,RW,0x00) //adding line number
	UINT32 res_field_sel                    :1;	//(15,RW,0x00) //For debug reshape field selection	0 := Top	1  = Bottom
	UINT32 res_sync_sel                     :1;	//(16,RW,0x01) //For debug Reshape Sync Selection bit	0  = use internal reshape sync (debug mode)	1 := use input sync
	UINT32 resvd1                           :15;
	};
}PE_O26_CVI_INT_SYNC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0214 RW 0x0100_0000
	UINT32 mask_ext_db                      :1;	//(0,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_dg                      :1;	//(1,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_dr                      :1;	//(2,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_field                   :1;	//(3,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_hd                      :1;	//(4,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_vd                      :1;	//(5,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext_de                      :1;	//(6,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_ext                         :1;	//(7,RW,0x00) //0: disable,  1 : masking
	UINT32 data_mux_r                       :2;	//(9:8,RW,0x00) //00 := R	01  = G	10  = B	11  = 0
	UINT32 data_mux_b                       :2;	//(11:10,RW,0x00) //00 := B	01  = R	10  = G	11  = 0
	UINT32 data_mux_g                       :2;	//(13:12,RW,0x00) //00 := G	01  = B	10  = R	11  = 0
	UINT32 input_reverse                    :1;	//(14,RW,0x00) //0 : bypass,  1 : reverse
	UINT32 reserved                         :1;	//(15,RW,0x00) //0 : always on, 1 : only de (note! Component)
	UINT32 dither_en                        :1;	//(16,RW,0x00) //dither enable	0 : dither block bypass (12 to 10 truncation)	1 : dither path enable (12 to 10 dithering)
	UINT32 dither_temporal_en               :1;	//(17,RW,0x00) //temporal dither enable
	UINT32 hdr_tunnel_mode                  :2;	//(19:18,RW,0x00) //tunneled mode is on and dither_en should be off	 0: bypass,   1 : tunneled mode,	              3 : tunnel reverse mode
	UINT32 mask_reset_pop                   :1;	//(20,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_pop                         :1;	//(21,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_reset_push                  :1;	//(22,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_push                        :1;	//(23,RW,0x00) //0: disable,  1 : masking
	UINT32 mask_memory                      :1;	//(24,RW,0x01) //0: disable,  1 : masking
	UINT32 resvd                            :3;
	UINT32 dolby_crc_error_intr_en          :1;	//(28,RW,0x00) //interrupt enable
	UINT32 dolby_crc_error_intr_clr         :1;	//(29,RW,0x00) //interrupt clear
	UINT32 dolby_md_intr_en                 :1;	//(30,RW,0x00) //interrupt enable
	UINT32 dolby_md_intr_clr                :1;	//(31,RW,0x00) //interrupt clear
	};
}PE_O26_CVI_CV_MASK_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0218 RW 0x0000_0000
	UINT32 y_delay                          :2;	//(1:0,RW,0x00) //00 := No delay	01  = Pre delay	10  = Post delay
	UINT32 sub_line_420_mode                :2;	//(3:2,RW,0x00) //00 := bypass	01 :  even line pass, odd line disable	10 :  even line pass, odd line disable, Cb/Cr repeated	11 :  odd line pass, even line disable
	UINT32 cb_delay                         :2;	//(5:4,RW,0x00) //00 := No delay	01  = Pre delay ( not available )	10  = Post delay
	UINT32 cr_delay                         :2;	//(7:6,RW,0x00) //00 := No delay	01  = Pre delay ( not available )	10  = Post delay
	UINT32 y_swap                           :1;	//(8,RW,0x00) //0 := no swap	1  = Even and Odd output swap
	UINT32 c_swap                           :1;	//(9,RW,0x00) //0 := no swap	1  = Even and Odd output swap
	UINT32 yn1_swap                         :1;	//(10,RW,0x00) //0 := Yn1 : Cb 	1  = Yn1 : Cr
	UINT32 reserved0                        :1;	//(31:0,,) //
	UINT32 ctrl420_en                       :1;	//(12,RW,0x00) //0 := disable	 1  = 420 to 444 enable
	UINT32 reserved1                        :3;	//(31:0,,) //
	UINT32 dolby_video_format               :1;	//(16,RW,0x00) //turn on  	1: enable
	UINT32 dolby_422remap_manual            :1;	//(17,RW,0x00) //default
	UINT32 dolby_422remap_disable           :1;	//(18,RW,0x00) //default
	UINT32 reserved2                        :1;	//(31:0,,) //
	UINT32 dolby_hs_pol                     :1;	//(20,RW,0x00) //default
	UINT32 dolby_vs_pol                     :1;	//(21,RW,0x00) //default
	UINT32 dolby_sdr_force                  :1;	//(22,RW,0x00) //default
	UINT32 reserved3                        :1;	//(31:0,,) //
	UINT32 hd_line_size_sel                 :1;	//(24,RW,0x00) //0x0 = normal, 0x1 = average  (hd_line_size)
	UINT32 reserved4                        :7;	//(31:0,,) //
	};
}PE_O26_CVI_CV_420_INCTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E021C RO 0x0000_0000
	UINT32 dolby_md_info                    :32;	//(31:0,RO,0x00) //
	};
}PE_O26_CVI_CV_HDMI_MD_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0220 RO 0x0000_0000
	UINT32 tot_vsize                        :32;	//(31:0,RO,0x00) //avg_sel = 0 tot_vsize [27:0] h_avg = tot_vsize / vd_line_count_curr	avg_sel = 1 min[15:0], max[15:0]
	};
}PE_O26_CVI_HD_LINE_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0224 RW 0x09D3_00FE
	UINT32 csc_coefficient1                 :15;	//(14:0,RW,0xFE) //default : 2515	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient0                 :15;	//(30:16,RW,0x9D3) //default : 254	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_O26_CVI_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0228 RW 0x02EE_7A98
	UINT32 csc_coefficient3                 :15;	//(14:0,RW,0x7A98) //default : -1384	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient2                 :15;	//(30:16,RW,0x2EE) //default : 750	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_O26_CVI_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E022C RW 0x0706_7E62
	UINT32 csc_coefficient5                 :15;	//(14:0,RW,0x7E62) //default : -414	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient4                 :15;	//(30:16,RW,0x706) //default : 1798	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_O26_CVI_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0230 RW 0x799E_7F5C
	UINT32 csc_coefficient7                 :15;	//(14:0,RW,0x7F5C) //default : -165	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient6                 :15;	//(30:16,RW,0x799E) //default : -1634	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_O26_CVI_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0234 RW 0x0706_0000
	UINT32 csc_offset0                      :13;	//(12:0,RW,0x00) //Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :3;
	UINT32 csc_coefficient8                 :15;	//(30:16,RW,0x706) //default : 1798	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_O26_CVI_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0238 RW 0x0000_0000
	UINT32 csc_offset2                      :13;	//(12:0,RW,0x00) //Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :3;
	UINT32 csc_offset1                      :13;	//(28:16,RW,0x00) //Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E023C RW 0x0100_0800
	UINT32 csc_offset4                      :13;	//(12:0,RW,0x0800) //Post add offset y	Range -1024~1023
	UINT32 resvd0                           :3;
	UINT32 csc_offset3                      :13;	//(28:16,RW,0x0100) //Post add offset x	Range -1024~1023
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0240 RW 0x0800_0000
	UINT32 csc_coeff_load                   :1;	//(0,RW,0x00) //this bit is auto cleared
	UINT32 csc_en                           :1;	//(1,RW,0x00) //1  = CSC enable	0 := bypass CSC
	UINT32 resvd0                           :1;
	UINT32 reg_skip                         :2;	//(4:3,RW,0x00) //0: bypass	1 : 1 line of 2 line	2 : 1 line of 4 line	3 : 1 line of 8 line
	UINT32 resvd1                           :11;
	UINT32 csc_offset5                      :11;	//(26:16,RW,0x0800) //Post add offset z	Range -1024~1023
	UINT32 resvd2                           :5;
	};
}PE_O26_CVI_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0244 RW 0x0000_0000
	UINT32 pattern_type                     :3;	//(2:0,RW,0x00) //type of pattern	000 := bypass	001  = one color pattern	010  = horizontal color bar pattern 	011  = vertical color bar pattern	(Note! the first pixel's color of vertical line is different)	100  = cross hatch pattern	101  = moving horizontal color bar pattern	110  = moving vertical color bar pattern	111  = moving cross hatch pattern
	UINT32 pattern_csc                      :1;	//(3,RW,0x00) //0 := Y/Cb/Cr color pattern gen	1  = G/B/R color pattern gen
	UINT32 pattern_detail                   :4;	//(7:4,RW,0x00) //when pattern_type is 001	0000  = white	0001  = yellow	0010  = cyan	0011  = green	0100  = magenta	0101  = red	0110 := blue	0111  = black	1000  = horizontal gradation	1001  = vertical gradation	1010  = color gradation (step size 1 )	1011  = Y/C gradation	1100  = black and white for deinter test	1101  = horizontal gradation (step size 1 )	1110  = vertical gradation (step size 1 )	when pattern_type is 010 or 101	0000  = 2 pixel width	0001  = 4 pixel width	0010  = 8 pixel width	0011  = 16 pixel width	0100  = 32 pixel width	0101  = 64 pixel width	0110 := 128 pixel width	when pattern_type is 011 or 110	0000  = 1 line height	0001  = 2 line height	0010  = 4 line height	0011  = 8 line height	0100  = 16 line height	0101  = 32 line height	0110 := 64 line height
	UINT32 reg_update_pulse                 :1;	//(8,RW,0x00) //Vpulse generation at no vsync only for simulation (auto clear)
	UINT32 field_fix_mode                   :2;	//(10:9,RW,0x00) //00 := bypass field	01  = fix high	10  = fix low	11  = forcing field at every vsync
	UINT32 black_sel                        :1;	//(11,RW,0x00) //selection of black 	0 : YC black	1 : RGB black
	UINT32 write_inhibit                    :1;	//(12,RW,0x00) //0 := normal	1  = inhibit transfer CVI to Scaler
	UINT32 sim_mode                         :1;	//(13,RW,0x00) //0:= normal	1 = simulation mode only
	UINT32 black_off                        :1;	//(14,RW,0x00) //fill it black screen for over offset	0:= black screen	1 = screen bypass
	UINT32 field_edge                       :1;	//(15,RW,0x00) //when field detection in use of vsync's edge against hsync	0:= falling edge of vsync	1 = rising edge of vsync
	UINT32 ha_gen                           :1;	//(16,RW,0x00) //when de_mode is enable, hactive is made during vactive low	0 := dvi_hoffset read value apply	1  = ha is not generated during vactive low
	UINT32 monitor_on                       :1;	//(17,RW,0x00) //output of cvi xsize is divided by below value.	0 := default	1  = divide2	2  = divide4
	UINT32 force_update                     :1;	//(18,RW,0x00) //host force update
	UINT32 avg_sel                          :1;	//(19,NA,0x00) //0 := V total size	1  = max[15:0], min[15:0] hsize
	UINT32 yc_delay_mode_r                  :2;	//(21:20,RW,0x00) //00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 yc_delay_mode_b                  :2;	//(23:22,RW,0x00) //00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 yc_delay_mode_g                  :2;	//(25:24,RW,0x00) //00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 field_detect_vris                :1;	//(26,RW,0x00) //
	UINT32 reg_vcnt_reset                   :1;	//(27,RW,0x00) //1 : internal vcount reset when offset/size is changing
	UINT32 reg_update_position              :4;	//(31:28,RW,0x00) //register's update position after Vsync falling	0~15 line
	};
}PE_O26_CVI_MISC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0248 RO 0x0000_0000
	UINT32 hoffset_read                     :13;	//(12:0,RO,0x0) //Horizontal sync offset read HBP (DE rising update)
	UINT32 resvd0                           :3;
	UINT32 voffset_read                     :13;	//(28:16,RO,0x0) //Vertical sync offset read  VBP (VA rising update)
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_OFFSET_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E024C RW 0x0000_0000
	UINT32 cv_4p_manual_en                  :1;	//(0,RW,0x00) //0 := auto mode all mode is 4p except component(1p) and CVD(1p)	1 : manual mode
	UINT32 cv_4p_mode                       :1;	//(1,RW,0x00) //when cv_4p_manual_en = 1	0 := 1p	1  = 4p
	UINT32 sub_line_mode                    :2;	//(3:2,RW,0x00) //00 := bypass	01 :  even line pass, odd line disable	11 :  odd line pass, even line disable
	UINT32 hs_bypass                        :1;	//(4,RW,0x00) //0 := CDC throughout sync	1  = original delayed sync
	UINT32 vs_bypass                        :1;	//(5,RW,0x00) //0 := CDC throughout sync	1  = original delayed sync
	UINT32 fd_bypass                        :1;	//(6,RW,0x00) //0 := CDC throughout sync	1  = original delayed sync
	UINT32 sync_bypass                      :1;	//(7,RW,0x00) //0 := hs,vs,fd 's changing, => sync chaning	1  = hs,vs,fd is not changing during no data period
	UINT32 fal_sel_v                        :1;	//(8,RW,0x00) //0 := fal_ext_vs	1 =  fal_ext_ha
	UINT32 debug                            :1;	//(9,RW,0x00) //0 := fal_ext_vs	1 =  fal_ext_ha
	UINT32 active_gen_offset                :1;	//(10,RW,0x0) //0 := protect offset value	1  = mode against abnormal hsync input
	UINT32 reserved0                        :1;	//(31:0,,) //
	UINT32 reg_clip_size                    :3;	//(14:12,RW,0x0) //debug
	UINT32 reserved1                        :1;	//(31:0,,) //
	UINT32 manual_m0                        :2;	//(17:16,RW,0x0) //debug
	UINT32 manual_m1                        :2;	//(19:18,RW,0x0) //debug
	UINT32 manual_m2                        :3;	//(22:20,RW,0x0) //debug
	UINT32 manual_m3                        :1;	//(23,RW,0x0) //debug
	UINT32 manual_meb                       :4;	//(27:24,RW,0x0) //debug
	UINT32 manual_addr                      :4;	//(31:28,RW,0x0) //debug
	};
}PE_O26_CVI_MISC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0250 RW/RO 0x021C_0000
	UINT32 pre3d_sync_enable                :1;	//(0,RW,0x00) //0 := bypass	1  = sync modify
	UINT32 pre3d_sync_mode                  :2;	//(2:1,RW,0x00) //00 := bypass	01  = Frame Packing (2 frame separate)	10  = Frame Packing (4 frame separate)	11  = Field Alternative
	UINT32 pre3d_field_mode                 :1;	//(3,RW,0x00) //0 := normal	1  = inverse
	UINT32 pre3d_frame_lr_mode              :1;	//(4,RW,0x00) //0 := normal	1  = inverse
	UINT32 pre3d_mid_vsync_bypass           :1;	//(5,RW,0x00) //0 := Mid Vsync Insert	1  = Mid Vsync Bypass
	UINT32 pre3d_field_bypass               :1;	//(6,RW,0x00) //0 := internal generated field use	1  = field bypass
	UINT32 va_ris_field                     :1;	//(7,RO,0x00) //
	UINT32 va_ris_lr                        :1;	//(8,RO,0x00) //
	UINT32 vd_ris_field                     :1;	//(9,RO,0x00) //
	UINT32 vd_ris_lr                        :1;	//(10,RO,0x00) //
	UINT32 va_fal_field                     :1;	//(11,RO,0x00) //
	UINT32 va_fal_lr                        :1;	//(12,RO,0x00) //
	UINT32 vd_fal_field                     :1;	//(13,RO,0x00) //
	UINT32 vd_fal_lr                        :1;	//(14,RO,0x00) //
	UINT32 field                            :1;	//(15,RO,0x00) //
	UINT32 pre3d_active_line_num            :13;	//(28:16,RW,0x21C) //line number [Max 4095]
	UINT32 resvd                            :3;
	};
}PE_O26_CVI_PRE3D_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0254 RO 0x0000_0000
	UINT32 vd_line_count_curr               :16;	//(15:0,RO,0x00) //Line count of Total VD sync in one frame (current frame) / VTOTAL (VS falling)
	UINT32 vd_front_porch                   :16;	//(31:16,RO,0x00) //Front porch line / VFP (VS falling)
	};
}PE_O26_CVI_SIZE_STATUS7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0258 RO 0x0000_0000
	UINT32 sd_hoffset_indurance_read        :8;	//(7:0,RO,0x0) //This register is increasing and then maintains Max value, when previous and current frame's hoffset is the same. At the normal condition this value should be 255	[Max 255]
	UINT32 sd_voffset_indurance_read        :8;	//(15:8,RO,0x0) //This register is increasing and then maintain Max value, when previous and current frame's voffset is the same. At the normal condition this value should be 255	[Max 255]
	UINT32 sd_hsync_fault_flag_read         :1;	//(16,RO,0x00) //0 = normal	1 = when de signal is high, hsync is low
	UINT32 sd_vsync_fault_flag_read         :1;	//(17,RO,0x00) //0 = normal	1 = when de signal is high, vsync is low
	UINT32 h_sync_polarity                  :1;	//(18,RO,0x00) //Detecion of poarity of Hsync	0 = positive sync(active_low)	1 = negative sync(active_high)
	UINT32 v_sync_polarity                  :1;	//(19,RO,0x00) //Detection of polarity of Vsync	0 = positive sync(active_low)	1 = negative sync(active_high)
	UINT32 field_signal                     :4;	//(23:20,RO,0x00) //accumluated field signal detect at V sync falling[LSB bit is current detected field polarity]
	UINT32 hsync_at_vsync_fall              :4;	//(27:24,RO,0x00) //accumulated hsync signal detect at V sync falling[LSB bit is current detected field polarity]
	UINT32 outfield_at_vactive_fall         :2;	//(29:28,RO,0x00) //accumulated out field signal detect at V active falling[LSB bit is current detected field polarity]
	UINT32 hoffset_over                     :1;	//(30,RO,0x00) //h offset value exceed over hsync size, no more higher h offset value will not be applied. Detected hsize is smaller than hoffset	0 = Normal state	1 = Abnormal state
	UINT32 v_offset_over                    :1;	//(31,RO,0x00) //v offset value exceed over vsync size, no more higher v offset value will not be applied. Detected vsize is smaller than voffset	0 = Normal state	1 = Abnormal state
	};
}PE_O26_CVI_SIZE_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E025C RO 0x0000_0000
	UINT32 de_line_size                     :13;	//(12:0,RO,0x0) //Pixel size of one line de / HA (at reg_pre_cnt)	This line number is selected by line_count_sel register
	UINT32 resvd0                           :3;
	UINT32 de_line_count                    :13;	//(28:16,RO,0x0) //de line count size of one frame / VA (VS falling)
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_SIZE_STATUS2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0260 RO 0x0000_0000
	UINT32 hd_sync_size                     :13;	//(12:0,RO,0x0) //Pixel size of sync duration in HD sync / HSYN = hd_line_size - hd_sync_size
	UINT32 resvd0                           :3;
	UINT32 hd_line_size                     :13;	//(28:16,RO,0x0) //Pixel size of Total HD sync in one line / HTOTAL
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_SIZE_STATUS3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0264 RO 0x0000_0000
	UINT32 vd_sync_count                    :13;	//(12:0,RO,0x0) //Line count of sync duration in VD sync / VSYN = vd_line_count_curr-vd_sync_count
	UINT32 resvd0                           :3;
	UINT32 vd_line_count                    :13;	//(28:16,RO,0x0) //Line count of Total VD sync in one frame (previous frame)
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_SIZE_STATUS4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0268 RW 0x0200_0100
	UINT32 start_pos_x                      :13;	//(12:0,RW,0x100) //Start position of X range
	UINT32 pixel_read                       :1;	//(13,RW,0x00) //pixel read enable (8 pixel)
	UINT32 resvd                            :1;
	UINT32 pix_sum_enable                   :1;	//(15,RW,0x00) //Pixel sum enable	0:= disable	1 = enable
	UINT32 end_pos_x                        :13;	//(28:16,RW,0x200) //End position of X range
	UINT32 field_selection                  :2;	//(30:29,RW,0x00) //field selection	00:= each field detection	01 = odd field detect only	10 = even field detect only	11 = alternative field
	UINT32 debug_enable                     :1;	//(31,RW,0x00) //debug display enable	0:= disable	1 = enable
	};
}PE_O26_CVI_PIX_SUM_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E026C RW 0x0080_0040
	UINT32 start_pos_y                      :13;	//(12:0,RW,0x40) //Start position of Y range
	UINT32 resvd0                           :3;
	UINT32 end_pos_y                        :13;	//(28:16,RW,0x80) //End position of Y range
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_PIX_SUM_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0270 NA 0x3004_0100
	UINT32 fill_color_r                     :10;	//(9:0,RW,0x100) //debug color R
	UINT32 fill_color_b                     :10;	//(19:10,RW,0x100) //debug color B
	UINT32 fill_color_g                     :10;	//(29:20,RW,0x300) //debug color G
	UINT32 sync_sel                         :1;	//(30,RW,0x00) //0 : hsync 1: de
	UINT32 fill_en                          :1;	//(31,RW,0x00) //debug color fill enable
	};
}PE_O26_CVI_PIX_SUM_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0274 RO 0x0000_0000
	UINT32 pix_sum_g0                       :32;	//(31:0,RO,0x0000_0000) //G port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0278 RO 0x0000_0000
	UINT32 pix_sum_b0                       :32;	//(31:0,RO,0x0000_0000) //B port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E027C RO 0x0000_0000
	UINT32 pix_sum_r0                       :32;	//(31:0,RO,0x0000_0000) //R port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0280 RO 0x0000_0000
	UINT32 pix_sum_g1                       :32;	//(31:0,RO,0x0000_0000) //G port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0284 RO 0x0000_0000
	UINT32 pix_sum_b1                       :32;	//(31:0,RO,0x0000_0000) //B port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0288 RO 0x0000_0000
	UINT32 pix_sum_r1                       :32;	//(31:0,RO,0x0000_0000) //R port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E028C RO 0x0000_0000
	UINT32 pix_sum_g2                       :32;	//(31:0,RO,0x0000_0000) //G port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0290 RO 0x0000_0000
	UINT32 pix_sum_b2                       :32;	//(31:0,RO,0x0000_0000) //B port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0294 RO 0x0000_0000
	UINT32 pix_sum_r2                       :32;	//(31:0,RO,0x0000_0000) //R port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0298 RO 0x0000_0000
	UINT32 pix_sum_g3                       :32;	//(31:0,RO,0x0000_0000) //G port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUS9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E029C RO 0x0000_0000
	UINT32 pix_sum_b3                       :32;	//(31:0,RO,0x0000_0000) //B port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUSA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02A0 RO 0x0000_0000
	UINT32 pix_sum_r3                       :32;	//(31:0,RO,0x0000_0000) //R port pixel sum read
	};
}PE_O26_CVI_PIX_SUM_STATUSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02A4 RW 0x0040_0000
	UINT32 hsync_fil_en                     :1;	//(0,RW,0x00) //Hsync filter enable
	UINT32 hsync_counter_en                 :1;	//(1,RW,0x00) //Counter enable for happened glitch or spike at Hsync
	UINT32 vsync_fil_en                     :1;	//(2,RW,0x00) //Vsync filter enable
	UINT32 vsync_counter_en                 :1;	//(3,RW,0x00) //Counter enable for happened glitch or spike at Vsync
	UINT32 de_fil_en                        :1;	//(4,RW,0x00) //DE filter enable
	UINT32 de_counter_en                    :1;	//(5,RW,0x00) //Counter enable for happened glitch or spike at DE
	UINT32 field_fil_en                     :1;	//(6,RW,0x00) //Field filter enable
	UINT32 field_counter_en                 :1;	//(7,RW,0x00) //Counter enable for happened glitch or spike at Field
	UINT32 resvd0                           :8;
	UINT32 reg_pre_count                    :13;	//(28:16,RW,0x40) //actual line count when reading de_line_size	default : 200th line
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_SYNC_FIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02A8 RO 0x0000_0000
	UINT32 hsync_coutner                    :8;	//(7:0,RO,0x0) //Glitch or Spike number at Hsync	Max 255
	UINT32 vsync_counter                    :8;	//(15:8,RO,0x0) //Glitch or Spike number at Vsync	Max 255
	UINT32 de_counter                       :8;	//(23:16,RO,0x0) //Glitch or Spike number at DE	Max 255
	UINT32 field_counter                    :8;	//(31:24,RO,0x0) //Glitch or Spike number at Field	Max 255
	};
}PE_O26_CVI_SYNC_FIL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02AC NA 0x0203_0020
	UINT32 hdn_y_coef3                      :10;	//(9:0,RW,0x20) //
	UINT32 hdn_y_coef2                      :10;	//(19:10,RW,0xC0) //
	UINT32 hdn_y_coef1                      :10;	//(29:20,RW,0x20) //
	UINT32 hdn_y_reset                      :1;	//(30,RW,0x00) //
	UINT32 hdn_enable                       :1;	//(31,RW,0x00) //
	};
}PE_O26_CVI_H_DOWN_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02B0 NA 0x0203_0020
	UINT32 hdn_c_coef3                      :10;	//(9:0,RW,0x20) //0x0
	UINT32 hdn_c_coef2                      :10;	//(19:10,RW,0xC0) //0x100
	UINT32 hdn_c_coef1                      :10;	//(29:20,RW,0x20) //0x0
	UINT32 hdn_c_reset                      :1;	//(30,RW,0x00) //when 420 mode
	UINT32 h_tunnel_en                      :1;	//(31,RW,0x00) //for tunnel mode
	};
}PE_O26_CVI_H_DOWN_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02B4 NA 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x00) //
	};
}PE_O26_CVI_V_DOWN_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02B8 NA 0x0000_0000
	UINT32 reserved                         :31;	//(30:0,Rsvd,0x00) //
	UINT32 i_down_420                       :1;	//(31,RW,0x00) //0 : 444 down mode	1 : 420 down mode
	};
}PE_O26_CVI_V_DOWN_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02BC NA 0x0000_0000
	UINT32 hdn_y_coef4                      :10;	//(9:0,RW,0x00) //
	UINT32 resvd0                           :6;
	UINT32 hdn_y_coef0                      :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CVI_H_DOWN_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02C0 RW 0xC012_8006
	UINT32 sd_vd_range                      :2;	//(1:0,RW,0x02) //VD line range	00  = 8	01  = 16	10 := 32	11  = 64
	UINT32 sd_ext_range                     :2;	//(3:2,RW,0x01) //External Line range	00  = 1	01 := 2	10  = 4	11  = 8
	UINT32 intr_mask_node                   :1;	//(4,RW,0x00) //DE interrupt mask	0 := interrupt enable	1  = interrupt disable (masking)
	UINT32 intr_mask_nohsync                :1;	//(5,RW,0x00) //Hsync interrupt mask
	UINT32 intrl_mask_novsync               :1;	//(6,RW,0x00) //Vsync interrupt mask
	UINT32 intr_mask_abnormal               :1;	//(7,RW,0x00) //Abnormal condition interrupt mask
	UINT32 intr_mask_invalid                :1;	//(8,RW,0x00) //Invalid input interrupt mask
	UINT32 intr_mask_de                     :1;	//(9,RW,0x00) //Normal DE interrupt mask
	UINT32 intr_mask_hsync                  :1;	//(10,RW,0x00) //Normal Hsync interrupt mask
	UINT32 intr_mask_vsync                  :1;	//(11,RW,0x00) //Normal Vsync interrupt mask
	UINT32 intr_mask_normal                 :1;	//(12,RW,0x00) //Normal condition interrupt mask
	UINT32 intr_mask_valid                  :1;	//(13,RW,0x00) //Valid input interrupt mask
	UINT32 intr_mask_h_cnahge               :1;	//(14,RW,0x00) //To fast change of Hsync
	UINT32 sd_en                            :1;	//(15,RW,0x01) //Size detection enable	0  = disable	1 := enable
	UINT32 sd_frame_cnt                     :3;	//(18:16,RW,0x02) //over 3 frame has to maintain same line number
	UINT32 clk1024                          :1;	//(19,RW,0x0) //1 : ext_clk_cnt = 1024
	UINT32 sd_novald_duration               :2;	//(21:20,RW,0x01) //duration of no valid time, the smaller this value go to low, the faster no valid signal happen	00  = 13896 unit h	01 := 8192 unit h	10  = 4096 unit h	11  = 2048 unit h
	UINT32 clk2048                          :1;	//(22,RW,0x0) //1 : ext_clk_cnt = 2048
	UINT32 sd_one_field                     :1;	//(23,RW,0x00) //when SD read size of two field, it restrict only one field.	0 := 2 field read	1  = 1 field read
	UINT32 reserved                         :2;	//(25:24,NA,0x00) //debug interrup enable, source clock selection(200/400Mhz)
	UINT32 nosig_duration_de                :2;	//(27:26,RW,0x00) //Duration of DE signal's absence to detect DE no signal	00 := 5.17us over	01  = 10.34us over	10  = 20.68us over	11  = 41.37us over
	UINT32 nosig_duration_hsync             :2;	//(29:28,RW,0x00) //Duration of Hsync signal's absence to detect Hsync no signal	00 := 5.17us over	01  = 10.34us over	10  = 20.68us over	11  = 41.37us over
	UINT32 nosig_duration_vsync             :2;	//(31:30,RW,0x03) //Duration of Vsync signal's absence to detect Vsync no signal	00 := 21.17ms over (60Hz available)	01  = 42.35ms over (30Hz available)	10  = 84.70ms over (24Hz available) 	11  = 169.41ms over
	};
}PE_O26_CVI_SIZE_DETECT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02C4 RO 0x0000_0000
	UINT32 line_num_read                    :16;	//(15:0,RO,0x0) //line number of one frame(field) (using fixed clock)	Frame rate(Hz) = {1 / { (read_data * 2048 )} * de_clk_(396MHz)
	UINT32 line_width_read                  :16;	//(31:16,RO,0x0) //width of one line (using fixed clock)	pixel number = (read_data * input_source_clk_Mhz )/de_clk_396MHz
	};
}PE_O26_CVI_SIZE_DETECT_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02C8 RO 0x0000_0000
	UINT32 current_line_number_read         :12;	//(11:0,RO,0x00) //[Max 16383]
	UINT32 de_signal_detect                 :1;	//(12,RO,0x00) //0 = No DE signal	1 = DE signal is detected
	UINT32 hsync_signal_detect              :1;	//(13,RO,0x00) //0 = No Hsync signal	1 = Hsync signal is detected
	UINT32 vsync_signal_detect              :1;	//(14,RO,0x00) //0 = No Vsync signal	1 = Vsync signal is detected
	UINT32 source_valid                     :1;	//(15,RO,0x00) //0 = Source sync is not valid yet.	1 = Source sync is valid
	UINT32 sd_line_num                      :14;	//(29:16,RO,0x00) //line number of one frame(field) by de_clk, so this value may vary �1 count => see the vd_line_count(SIZE_STATUS4)
	UINT32 current_line_number_read_msb     :2;	//(31:30,RO,0x00) //current_line_number_read_msb
	};
}PE_O26_CVI_SIZE_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02CC RO 0x0000_0000
	UINT32 sd_2field_size                   :28;	//(27:0,RO,0x0000_0000) //size of two field by de_clk	60hz => 16.67ms x 2field = 33.33ms / (1/396M) = 13,200,000	30Hz => 26,400,000	24Hz => 33,000,000
	UINT32 resvd                            :1;
	UINT32 field_at_vactive_fall            :3;	//(31:29,RO,0x00) //accumluated out field signal detect at V active falling[LSB bit is current detected field polarity]
	};
}PE_O26_CVI_SIZE_STATUS5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02D0 RO 0x0000_0000
	UINT32 diff_vd_vcnt                     :16;	//(15:0,RO,0x0) //different vcount between current vd_vcnt and previous vd_vcnt
	UINT32 diff_ext_vcnt                    :12;	//(27:16,RO,0x00) //different vcount between current ext_vcnt and previous ext_vcnt
	UINT32 resvd                            :3;
	UINT32 vd_intr                          :1;	//(31,RO,0x00) //0 = Source sync is not valid yet.	1 = Source sync is valid
	};
}PE_O26_CVI_SIZE_STATUS6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02D4 RW/RO 0x0000_0000
	UINT32 abnormal0_en                     :1;	//(0,RW,0x00) //0 := do not apply to make abnormal flag	1  = apply to make abnormal flag
	UINT32 abnormal1_en                     :1;	//(1,RW,0x00) //
	UINT32 abnormal2_en                     :1;	//(2,RW,0x00) //
	UINT32 abnormal3_en                     :1;	//(3,RW,0x00) //
	UINT32 abnormal4_en                     :1;	//(4,RW,0x00) //
	UINT32 abnormal5_en                     :1;	//(5,RW,0x00) //
	UINT32 abnormal6_en                     :1;	//(6,RW,0x00) //
	UINT32 abnormal7_en                     :1;	//(7,RW,0x00) //
	UINT32 abnormal0_flag                   :1;	//(8,RO,0x00) //High period of V sync is too short so that is abnormal
	UINT32 abnormal1_flag                   :1;	//(9,RO,0x00) //Low period of V sync is too short so that is abnormal
	UINT32 abnormal2_flag                   :1;	//(10,RO,0x00) //High period of H sync is too short so that is abnormal
	UINT32 abnormal3_flag                   :1;	//(11,RO,0x00) //Low period of H sync is too short so that is abnormal
	UINT32 abnormal4_flag                   :1;	//(12,RO,0x00) //Periodic Vsync is not detected so that is abnormal
	UINT32 abnormal5_flag                   :1;	//(13,RO,0x00) //DE sync is not detected so that is abnormal
	UINT32 abnormal6_flag                   :1;	//(14,RO,0x00) //Hsync is not detected so that is abnormal
	UINT32 abnormal7_flag                   :1;	//(15,RO,0x00) //Vsync is not detected so that is abnormal
	UINT32 ext_clk_valid_count              :15;	//(30:16,RO,0x0) //counter value of 512 ext clk measured by de_clk(400Mhz) 512*396/count 	for ex : 297Mhz count 682
	UINT32 ext_clk_valid                    :1;	//(31,RO,0x00) //valid of ext_clk (if no ext_clk state is over 165us then this signal goes to zero)
	};
}PE_O26_CVI_SIZE_DETECT_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02D8 RW 0x0301_0905
	UINT32 abnormal_in_h                    :8;	//(7:0,RW,0x5) //H Threshold width from normal to abnormal
	UINT32 abnormal_out_h                   :8;	//(15:8,RW,0x9) //H Threshold width from abnormal to normal
	UINT32 abnormal_in_v                    :8;	//(23:16,RW,0x1) //V Threshold width from normal to abnormal
	UINT32 abnormal_out_v                   :8;	//(31:24,RW,0x3) //V Threshold width from abnormal to normal
	};
}PE_O26_CVI_SIZE_DETECT_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02DC RW 0x0000_0000
	UINT32 resvd0                           :3;
	UINT32 field_sel                        :1;	//(3,RW,0x00) //0 := Original sync select	1  = Pseudo sync select
	UINT32 hsync_sel                        :1;	//(4,RW,0x00) //0 := Original sync select	1  = Pseudo sync select
	UINT32 vsync_sel                        :1;	//(5,RW,0x00) //0 := Original sync select	1  = Pseudo sync select
	UINT32 de_sel                           :1;	//(6,RW,0x00) //0 := Original sync select	1  = Pseudo sync select
	UINT32 resvd1                           :1;
	UINT32 cr_sel                           :1;	//(8,RW,0x00) //0 := Original Cr selec	1  = Pseudo Cr select
	UINT32 resvd2                           :1;
	UINT32 cb_sel                           :1;	//(10,RW,0x00) //0 := Original Cb select	1  = Pseudo Cb select
	UINT32 resvd3                           :1;
	UINT32 y_sel                            :1;	//(12,RW,0x00) //0 := Original Y select	1  = Pseudo Y select
	UINT32 resvd4                           :7;
	UINT32 c_valid_sel                      :2;	//(21:20,RW,0x00) //00 := Normal condition (cvalid = yvalid)	01  = 420 mode (cvalid = 1/4 valid for 420)	10  = 420 mode (cvalid = 1/2 valid for 420 , Even_odd mode)	11  = 420 mode YC align
	UINT32 c_valid_sel1                     :1;	//(22,RW,0x00) //When HDMI 420, H down 	0 := normal	1 = H down 420 mode
	UINT32 auto_pseudo_sync_en              :1;	//(23,RW,0x00) //Automatically Pseudo sync is selected to SMUX's input until Capture input's abnormal flag is disappeared.
	UINT32 c_valid_sel2                     :2;	//(25:24,RW,0x00) //00 := Normal condition (cvalid = c_valid_sel)	01  = even line C valid / no odd line C valid	11  = odd line C valid / no even line C valid
	UINT32 resvd5                           :6;
	};
}PE_O26_CVI_CV_OUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02E0 RW 0x0058_02C0
	UINT32 pseudo_sync_ctrl_en              :1;	//(0,RW,0x00) //1  = enable of pseudo sync ctrl	0 := disable of pseudo sync ctrl
	UINT32 pseudo_y_data_sel                :1;	//(1,RW,0x00) //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Y
	UINT32 pseudo_cb_data_sel               :1;	//(2,RW,0x00) //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Cb
	UINT32 pseudo_cr_data_sel               :1;	//(3,RW,0x00) //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Cr
	UINT32 pseudo_hfp                       :14;	//(17:4,RW,0x2C) //size of horizontal front porch 44 (176/4)
	UINT32 pseudo_hsync                     :14;	//(31:18,RW,0x16) //size of hsync 22 (88/4 )
	};
}PE_O26_CVI_PSEUDO_SYNC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02E4 RW 0x1130_08CF
	UINT32 pseudo_y                         :4;	//(3:0,RW,0x0F) //MSB 4bit (default 960)
	UINT32 pseudo_hblk                      :14;	//(17:4,RW,0x8C) //size of horizontal blank 140(560/4)
	UINT32 pseudo_hn                        :14;	//(31:18,RW,0x44C) //size of horizontal line 1100(4400/4)
	};
}PE_O26_CVI_PSEUDO_SYNC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02E8 RW 0x0028_0088
	UINT32 pseudo_cb                        :4;	//(3:0,RW,0x08) //MSB 4bit (default 512)
	UINT32 pseudo_vfp                       :14;	//(17:4,RW,0x8) //line number of vertical front porch
	UINT32 pseudo_vsync                     :14;	//(31:18,RW,0xA) //line number of vertical sync
	};
}PE_O26_CVI_PSEUDO_SYNC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02EC RW 0x2328_05A8
	UINT32 pseudo_cr                        :4;	//(3:0,RW,0x08) //MSB 4bit (default 512)
	UINT32 pseudo_vblk                      :14;	//(17:4,RW,0x5A) //line number of vertical blank 90
	UINT32 pseudo_vn                        :14;	//(31:18,RW,0x8CA) //line number of whole frame 2250
	};
}PE_O26_CVI_PSEUDO_SYNC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02F0 RW 0x000A_4000
	UINT32 interrupt_mask_method            :1;	//(0,RW,0x00) //interrupt mask method	0 : periodic mask	1 : cascade mask
	UINT32 vd_v_vrr                         :1;	//(1,RW,0x00) //line_num_read
	UINT32 ext_v_vrr                        :1;	//(2,RW,0x00) //sd_line_num
	UINT32 resvd0                           :1;
	UINT32 interrupt_mask_count             :12;	//(15:4,RW,0x0400) //minimum mask count (5.3ms = 1024*1/198*mask_count)
	UINT32 diff_hsize                       :14;	//(29:16,RW,0xA) //To detect fast hsync change, minimum change range
	UINT32 resvd1                           :2;
	};
}PE_O26_CVI_SIZE_DETECT_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02F4 NA 0x0000_0000
	UINT32 hdn_c_coef4                      :10;	//(9:0,RW,0x00) //
	UINT32 resvd0                           :6;
	UINT32 hdn_c_coef0                      :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :5;
	UINT32 hdn_c_420                        :1;	//(31,RW,0x00) //H down when 420
	};
}PE_O26_CVI_H_DOWN_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02F8 RW 0x0016_0017
	UINT32 pre3d_active_space1_line_num     :13;	//(12:0,RW,0x17) //line number [Max 4095]
	UINT32 resvd0                           :3;
	UINT32 pre3d_active_space2_line_num     :13;	//(28:16,RW,0x16) //line number [Max 4095]
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_PRE3D_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E02FC RW 0x0005_0002
	UINT32 pre3d_front_porch_line_num       :13;	//(12:0,RW,0x2) //line number [Max 4095]
	UINT32 resvd0                           :3;
	UINT32 pre3d_sync_line_num              :13;	//(28:16,RW,0x5) //line number [Max 4095]
	UINT32 resvd1                           :3;
	};
}PE_O26_CVI_PRE3D_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0300 RW 0x0000_0080
	UINT32 read_en                          :1;	//(0,RW,0x0) //pixel read enable (8 pixel)
	UINT32 read_line                        :1;	//(1,RW,0x0) //cross hatch enable of pixel read start position
	UINT32 reg_patt_en                      :1;	//(2,RW,0x0) //rectangle pattern enable
	UINT32 reg_patt_fill                    :1;	//(3,RW,0x0) //rectangle pattern full fill enable
	UINT32 reg_line_alt                     :1;	//(4,RW,0x0) //line alternative pattern enable
	UINT32 reg_one_dot                      :1;	//(5,RW,0x0) //One Dot pattern enable
	UINT32 reg_pix_mode                     :2;	//(7:6,RW,0x2) //pixel mode	0 : 1p	1 : 2p	2 :=4p (fix)
	UINT32 reg_pattern_read                 :1;	//(8,RW,0x0) //0 := no use	1 :  read value = reg_yg/cb/cr_data8
	UINT32 ext_pic_init_en                  :1;	//(9,RW,0x0) //0 := pic_init = vsync	1 :  pic_init = 0
	UINT32 reg_update_disable               :1;	//(10,RW,0x0) //0 := reg_update	1 :  no reg_update
	UINT32 resvd                            :21;
	};
}PE_O26_CVI_PIX_PAT_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0304 RW 0x0000_0000
	UINT32 reg_cb_white                     :12;	//(11:0,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_yg_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_PAT_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0308 RW 0x0000_0000
	UINT32 reg_yg_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cr_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_PAT_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E030C RW 0x0000_0000
	UINT32 reg_cr_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cb_black                     :12;	//(27:16,RW,0x0000) //2nd color of one dot
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_PAT_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0310 RW 0x0000_0000
	UINT32 y_size                           :16;	//(15:0,RW,0x0000) //input vertical   size
	UINT32 x_size                           :16;	//(31:16,RW,0x0000) //input horizontal size	actual hsize / 4
	};
}PE_O26_CVI_PIX_PAT_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0314 RW 0x0000_0000
	UINT32 y_read_pos                       :16;	//(15:0,RW,0x0000) //vertical read position
	UINT32 x_read_pos                       :16;	//(31:16,RW,0x0000) //horizontal read position
	};
}PE_O26_CVI_PIX_PAT_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0318 RW 0x0000_0000
	UINT32 x_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's horizontal end position
	UINT32 x_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's horizontal start position
	};
}PE_O26_CVI_PIX_PAT_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E031C RW 0x0000_0000
	UINT32 y_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's vertical end position
	UINT32 y_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's vertical start position
	};
}PE_O26_CVI_PIX_PAT_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0320 RO 0x0000_0000
	UINT32 pix0_cb_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix0_yg_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0324 RO 0x0000_0000
	UINT32 pix1_yg_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix0_cr_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0328 RO 0x0000_0000
	UINT32 pix1_cr_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix1_cb_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E032C RO 0x0000_0000
	UINT32 pix2_cb_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix2_yg_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0330 RO 0x0000_0000
	UINT32 pix3_yg_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix2_cr_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0334 RO 0x0000_0000
	UINT32 pix3_cr_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix3_cb_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0338 RO 0x0000_0000
	UINT32 pix4_cb_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix4_yg_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E033C RO 0x0000_0000
	UINT32 pix5_yg_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix4_cr_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0340 RO 0x0000_0000
	UINT32 pix5_cr_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix5_cb_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0344 RO 0x0000_0000
	UINT32 pix6_cb_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix6_yg_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E0348 RO 0x0000_0000
	UINT32 pix7_yg_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix6_cr_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4E034C RO 0x0000_0000
	UINT32 pix7_cr_read                     :12;	//(11:0,RO,0x0000) //
	UINT32 resvd0                           :4;
	UINT32 pix7_cb_read                     :12;	//(27:16,RO,0x0000) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CVI_PIX_READ11_T;

typedef struct {
	PE_O26_CVI_TOP_CTRL_T                                       top_ctrl;	//0xCC4E0200
	PE_O26_CVI_OFFSET_CTRL_T                                 offset_ctrl;	//0xCC4E0204
	PE_O26_CVI_SIZE_CTRL_T                                     size_ctrl;	//0xCC4E0208
	PE_O26_CVI_INT_SYNC_CTRL0_T                           int_sync_ctrl0;	//0xCC4E020C
	PE_O26_CVI_INT_SYNC_CTRL1_T                           int_sync_ctrl1;	//0xCC4E0210
	PE_O26_CVI_CV_MASK_CTRL_T                               cv_mask_ctrl;	//0xCC4E0214
	PE_O26_CVI_CV_420_INCTRL_T                             cv_420_inctrl;	//0xCC4E0218
	PE_O26_CVI_CV_HDMI_MD_INFO_T                         cv_hdmi_md_info;	//0xCC4E021C
	PE_O26_CVI_HD_LINE_INFO_T                               hd_line_info;	//0xCC4E0220
	PE_O26_CVI_CSC_CTRL0_T                                     csc_ctrl0;	//0xCC4E0224
	PE_O26_CVI_CSC_CTRL1_T                                     csc_ctrl1;	//0xCC4E0228
	PE_O26_CVI_CSC_CTRL2_T                                     csc_ctrl2;	//0xCC4E022C
	PE_O26_CVI_CSC_CTRL3_T                                     csc_ctrl3;	//0xCC4E0230
	PE_O26_CVI_CSC_CTRL4_T                                     csc_ctrl4;	//0xCC4E0234
	PE_O26_CVI_CSC_CTRL5_T                                     csc_ctrl5;	//0xCC4E0238
	PE_O26_CVI_CSC_CTRL6_T                                     csc_ctrl6;	//0xCC4E023C
	PE_O26_CVI_CSC_CTRL7_T                                     csc_ctrl7;	//0xCC4E0240
	PE_O26_CVI_MISC_CTRL_T                                     misc_ctrl;	//0xCC4E0244
	PE_O26_CVI_OFFSET_READ_T                                 offset_read;	//0xCC4E0248
	PE_O26_CVI_MISC_CTRL1_T                                   misc_ctrl1;	//0xCC4E024C
	PE_O26_CVI_PRE3D_CTRL0_T                                 pre3d_ctrl0;	//0xCC4E0250
	PE_O26_CVI_SIZE_STATUS7_T                               size_status7;	//0xCC4E0254
	PE_O26_CVI_SIZE_STATUS1_T                               size_status1;	//0xCC4E0258
	PE_O26_CVI_SIZE_STATUS2_T                               size_status2;	//0xCC4E025C
	PE_O26_CVI_SIZE_STATUS3_T                               size_status3;	//0xCC4E0260
	PE_O26_CVI_SIZE_STATUS4_T                               size_status4;	//0xCC4E0264
	PE_O26_CVI_PIX_SUM_CTRL0_T                             pix_sum_ctrl0;	//0xCC4E0268
	PE_O26_CVI_PIX_SUM_CTRL1_T                             pix_sum_ctrl1;	//0xCC4E026C
	PE_O26_CVI_PIX_SUM_CTRL2_T                             pix_sum_ctrl2;	//0xCC4E0270
	PE_O26_CVI_PIX_SUM_STATUS0_T                         pix_sum_status0;	//0xCC4E0274
	PE_O26_CVI_PIX_SUM_STATUS1_T                         pix_sum_status1;	//0xCC4E0278
	PE_O26_CVI_PIX_SUM_STATUS2_T                         pix_sum_status2;	//0xCC4E027C
	PE_O26_CVI_PIX_SUM_STATUS3_T                         pix_sum_status3;	//0xCC4E0280
	PE_O26_CVI_PIX_SUM_STATUS4_T                         pix_sum_status4;	//0xCC4E0284
	PE_O26_CVI_PIX_SUM_STATUS5_T                         pix_sum_status5;	//0xCC4E0288
	PE_O26_CVI_PIX_SUM_STATUS6_T                         pix_sum_status6;	//0xCC4E028C
	PE_O26_CVI_PIX_SUM_STATUS7_T                         pix_sum_status7;	//0xCC4E0290
	PE_O26_CVI_PIX_SUM_STATUS8_T                         pix_sum_status8;	//0xCC4E0294
	PE_O26_CVI_PIX_SUM_STATUS9_T                         pix_sum_status9;	//0xCC4E0298
	PE_O26_CVI_PIX_SUM_STATUSA_T                         pix_sum_statusa;	//0xCC4E029C
	PE_O26_CVI_PIX_SUM_STATUSB_T                         pix_sum_statusb;	//0xCC4E02A0
	PE_O26_CVI_SYNC_FIL_CTRL_T                             sync_fil_ctrl;	//0xCC4E02A4
	PE_O26_CVI_SYNC_FIL_STATUS_T                         sync_fil_status;	//0xCC4E02A8
	PE_O26_CVI_H_DOWN_CTRL0_T                               h_down_ctrl0;	//0xCC4E02AC
	PE_O26_CVI_H_DOWN_CTRL1_T                               h_down_ctrl1;	//0xCC4E02B0
	PE_O26_CVI_V_DOWN_CTRL0_T                               v_down_ctrl0;	//0xCC4E02B4
	PE_O26_CVI_V_DOWN_CTRL1_T                               v_down_ctrl1;	//0xCC4E02B8
	PE_O26_CVI_H_DOWN_CTRL2_T                               h_down_ctrl2;	//0xCC4E02BC
	PE_O26_CVI_SIZE_DETECT_CTRL_T                       size_detect_ctrl;	//0xCC4E02C0
	PE_O26_CVI_SIZE_DETECT_READ_T                       size_detect_read;	//0xCC4E02C4
	PE_O26_CVI_SIZE_STATUS0_T                               size_status0;	//0xCC4E02C8
	PE_O26_CVI_SIZE_STATUS5_T                               size_status5;	//0xCC4E02CC
	PE_O26_CVI_SIZE_STATUS6_T                               size_status6;	//0xCC4E02D0
	PE_O26_CVI_SIZE_DETECT_CTRL1_T                     size_detect_ctrl1;	//0xCC4E02D4
	PE_O26_CVI_SIZE_DETECT_CTRL2_T                     size_detect_ctrl2;	//0xCC4E02D8
	PE_O26_CVI_CV_OUT_MUX_T                                   cv_out_mux;	//0xCC4E02DC
	PE_O26_CVI_PSEUDO_SYNC_CTRL1_T                     pseudo_sync_ctrl1;	//0xCC4E02E0
	PE_O26_CVI_PSEUDO_SYNC_CTRL2_T                     pseudo_sync_ctrl2;	//0xCC4E02E4
	PE_O26_CVI_PSEUDO_SYNC_CTRL3_T                     pseudo_sync_ctrl3;	//0xCC4E02E8
	PE_O26_CVI_PSEUDO_SYNC_CTRL4_T                     pseudo_sync_ctrl4;	//0xCC4E02EC
	PE_O26_CVI_SIZE_DETECT_CTRL3_T                     size_detect_ctrl3;	//0xCC4E02F0
	PE_O26_CVI_H_DOWN_CTRL3_T                               h_down_ctrl3;	//0xCC4E02F4
	PE_O26_CVI_PRE3D_CTRL1_T                                 pre3d_ctrl1;	//0xCC4E02F8
	PE_O26_CVI_PRE3D_CTRL2_T                                 pre3d_ctrl2;	//0xCC4E02FC
	PE_O26_CVI_PIX_PAT_CTRL0_T                             pix_pat_ctrl0;	//0xCC4E0300
	PE_O26_CVI_PIX_PAT_CTRL1_T                             pix_pat_ctrl1;	//0xCC4E0304
	PE_O26_CVI_PIX_PAT_CTRL2_T                             pix_pat_ctrl2;	//0xCC4E0308
	PE_O26_CVI_PIX_PAT_CTRL3_T                             pix_pat_ctrl3;	//0xCC4E030C
	PE_O26_CVI_PIX_PAT_CTRL4_T                             pix_pat_ctrl4;	//0xCC4E0310
	PE_O26_CVI_PIX_PAT_CTRL5_T                             pix_pat_ctrl5;	//0xCC4E0314
	PE_O26_CVI_PIX_PAT_CTRL6_T                             pix_pat_ctrl6;	//0xCC4E0318
	PE_O26_CVI_PIX_PAT_CTRL7_T                             pix_pat_ctrl7;	//0xCC4E031C
	PE_O26_CVI_PIX_READ0_T                                     pix_read0;	//0xCC4E0320
	PE_O26_CVI_PIX_READ1_T                                     pix_read1;	//0xCC4E0324
	PE_O26_CVI_PIX_READ2_T                                     pix_read2;	//0xCC4E0328
	PE_O26_CVI_PIX_READ3_T                                     pix_read3;	//0xCC4E032C
	PE_O26_CVI_PIX_READ4_T                                     pix_read4;	//0xCC4E0330
	PE_O26_CVI_PIX_READ5_T                                     pix_read5;	//0xCC4E0334
	PE_O26_CVI_PIX_READ6_T                                     pix_read6;	//0xCC4E0338
	PE_O26_CVI_PIX_READ7_T                                     pix_read7;	//0xCC4E033C
	PE_O26_CVI_PIX_READ8_T                                     pix_read8;	//0xCC4E0340
	PE_O26_CVI_PIX_READ9_T                                     pix_read9;	//0xCC4E0344
	PE_O26_CVI_PIX_READ10_T                                   pix_read10;	//0xCC4E0348
	PE_O26_CVI_PIX_READ11_T                                   pix_read11;	//0xCC4E034C
}PE_CVI_REG_O26_T;

#endif
