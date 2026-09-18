#ifndef _PE_CVI_REG_E60A0_H_
#define _PE_CVI_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC9000500 RW
	UINT32 scan_type                        :1;	//0 //0 := interlaced	1  = progressive
	UINT32 field_gen_mode                   :2;	//2:1	//00  = Auto field	01  = Inverse of Auto field	10 := Input field	11  = Inverse of Input field
	UINT32 auto_field_gen                   :2;	//4:3	//00 := use input hsync	01  = use pseudo hsync1	10  = use pseudo hsync2
	UINT32 reserved                         :1;	//5 //
	UINT32 chroma_sampling                  :1;	//6 //Chroma up-sampling method when data_bit_mode = '0'	0 := mean filter	1  = pixel repetition
	UINT32 aspect_ratio                     :1;	//7 //0 := 4:3	1  = 16:9
	UINT32 yc_delay_mode_r                  :2;	//9:8	//00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 yc_delay_mode_b                  :2;	//11:10	//00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 yc_delay_mode_g                  :2;	//13:12	//00 := bypass	01  = 1 pixel delay	10  = 2 pixel delay	11  = 3 pixel delay
	UINT32 data_in_sel                      :4;	//17:14	//0000 := HDMI_A	0010  = HDMI_B	0100  = HDMI_C	0110  = HDMI_D	1000  = CVD	1001  = Component	1100  = DSC	1110  = FEC
	UINT32 resvd                            :1;
	UINT32 auto_sync_polarity               :1;	//19 //0 = disable	1 := enable
	UINT32 manual_sync_polarity             :2;	//21:20	//00 := H = negative sync(active_high), V = negative sync(active_high)	01 =  H = negative sync(active_high), V = positive sync(active_low)	10 =  H =  positive sync(active_low), V = negative sync(active_high)	11 =  H =  positive sync(active_low), V =  positive sync(active_low)
	UINT32 adc_cut_direction                :1;	//22 //this bit is just only valid when adc_bit_sel = '1'	0 := MSB 8bit 	1  = LSB 8bit
	UINT32 adc_bit_sel                      :1;	//23 //0 := 10bit data	1  = 8 bit data (LSB 2bit's numbering is selected by bit_numbering_lsb2)
	UINT32 br_port_swap                     :1;	//24 //This bit swaps the B and R port	0 := normal	1  = B and R port swap
	UINT32 r_port_swap                      :1;	//25 //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 b_port_swap                      :1;	//26 //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 g_port_swap                      :1;	//27 //This bit swaps the MSB and LSB.	0 := normal bit order	1  = inverse bit order
	UINT32 bit_numbering_lsb2               :3;	//30:28	//This function is just only valid when adc_bit_sel = '1'.	000 := LSB 2bit is "00"	001  = LSB 2bit is "01"	010  = LSB 2bit is "10"	011  = LSB 2bit is "11"	100  = LSB 2bit is rotating on "00", "01", "10", "11"	101  = LSB 2bit is repeat own data(1 downto 0)
	UINT32 data_en_mode                     :1;	//31 //0 := Internal Hactive is made by hsync and de	1  = Internal Hactive is made by de (Hoffset & Voffset should be 0x0000)
	};
}PE_E60_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000504 RW
	UINT32 offset_h                         :13;	//12:0	//pixel number [Max 4095]
	UINT32 resvd0                           :3;
	UINT32 offset_v                         :13;	//28:16	//line number [Max 4095]
	UINT32 resvd1                           :3;
	};
}PE_E60_OFFSET_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000508 RW
	UINT32 size_h                           :13;	//12:0	//pixel number [Max 4095]
	UINT32 resvd0                           :3;
	UINT32 size_v                           :13;	//28:16	//line number [Max 4095]
	UINT32 resvd1                           :3;
	};
}PE_E60_SIZE_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900050C RW
	UINT32 res_hsync                        :10;	//9:0	//For debug horizontal reshape sync timing
	UINT32 resvd0                           :6;
	UINT32 res_hfp                          :10;	//25:16	//For debug horizontal reshape front porch timing
	UINT32 resvd1                           :6;
	};
}PE_E60_INT_SYNC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000510 RW
	UINT32 res_vfp                          :5;	//4:0	//For Debug vertical reshape front porch timing
	UINT32 resvd0                           :3;
	UINT32 res_vsync                        :5;	//12:8	//For Debug vertical reshape sync timing
	UINT32 res_field_add_line               :2;	//14:13	//adding line number
	UINT32 res_field_sel                    :1;	//15 //For debug reshape field selection	0 := Top	1  = Bottom
	UINT32 res_sync_sel                     :1;	//16 //For debug Reshape Sync Selection bit	0  = use internal reshape sync (debug mode)	1 := use input sync
	UINT32 resvd1                           :15;
	};
}PE_E60_INT_SYNC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000514 RW
	UINT32 mask_ext_db                      :1;	//0 //0: disable,  1 : masking
	UINT32 mask_ext_dg                      :1;	//1 //0: disable,  1 : masking
	UINT32 mask_ext_dr                      :1;	//2 //0: disable,  1 : masking
	UINT32 mask_ext_field                   :1;	//3 //0: disable,  1 : masking
	UINT32 mask_ext_hd                      :1;	//4 //0: disable,  1 : masking
	UINT32 mask_ext_vd                      :1;	//5 //0: disable,  1 : masking
	UINT32 mask_ext_de                      :1;	//6 //0: disable,  1 : masking
	UINT32 mask_ext                         :1;	//7 //0: disable,  1 : masking
	UINT32 data_mux_r                       :2;	//9:8	//00 := R	01  = G	10  = B	11  = 0
	UINT32 data_mux_b                       :2;	//11:10	//00 := B	01  = R	10  = G	11  = 0
	UINT32 data_mux_g                       :2;	//13:12	//00 := G	01  = B	10  = R	11  = 0
	UINT32 input_reverse                    :1;	//14 //0 : bypass,  1 : reverse
	UINT32 reserved                         :1;	//15 //0 : always on, 1 : only de (note! Component)
	UINT32 dither_en                        :1;	//16 //dither enable	0 : dither block bypass (12 to 10 truncation)	1 : dither path enable (12 to 10 dithering)
	UINT32 dither_temporal_en               :1;	//17 //temporal dither enable
	UINT32 hdr_tunnel_mode                  :2;	//19:18	//0: bypass,   1 : tunneled mode,	              3 : tunnel reverse mode
	UINT32 mask_reset_pop                   :1;	//20 //0: disable,  1 : masking
	UINT32 mask_pop                         :1;	//21 //0: disable,  1 : masking
	UINT32 mask_reset_push                  :1;	//22 //0: disable,  1 : masking
	UINT32 mask_push                        :1;	//23 //0: disable,  1 : masking
	UINT32 mask_memory                      :1;	//24 //0: disable,  1 : masking
	UINT32 resvd                            :3;
	UINT32 dolby_crc_error_intr_en          :1;	//28 //
	UINT32 dolby_crc_error_intr_clr         :1;	//29 //
	UINT32 dolby_md_intr_en                 :1;	//30 //
	UINT32 dolby_md_intr_clr                :1;	//31 //
	};
}PE_E60_CV_MASK_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000518 RW
	UINT32 y_delay                          :2;	//1:0	//00 := No delay	01  = Pre delay	10  = Post delay
	UINT32 reserved0                        :2;	//31:0	//
	UINT32 cb_delay                         :2;	//5:4	//00 := No delay	01  = Pre delay ( not available )	10  = Post delay
	UINT32 cr_delay                         :2;	//7:6	//00 := No delay	01  = Pre delay ( not available )	10  = Post delay
	UINT32 y_swap                           :1;	//8 //0 := no swap	1  = Even and Odd output swap
	UINT32 c_swap                           :1;	//9 //0 := no swap	1  = Cb and Cr output swap
	UINT32 yn1_swap                         :1;	//10 //0 := Yn1 : Cb 	1  = Yn1 : Cr
	UINT32 reserved1                        :1;	//31:0	//
	UINT32 ctrl420_en                       :1;	//12 //0 := disable	 1  = 420 to 444 enable
	UINT32 reserved2                        :3;	//31:0	//
	UINT32 dolby_video_format               :1;	//16 //
	UINT32 dolby_422remap_manual            :1;	//17 //
	UINT32 dolby_422remap_disable           :1;	//18 //
	UINT32 reserved3                        :1;	//31:0	//
	UINT32 dolby_hs_pol                     :1;	//20 //
	UINT32 dolby_vs_pol                     :1;	//21 //
	UINT32 dolby_sdr_force                  :1;	//22 //
	UINT32 reserved4                        :9;	//31:0	//
	};
}PE_E60_CV_420_INCTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900051C RO
	UINT32 dolby_md_info                    :32;	//31:0	//
	};
}PE_E60_CV_HDMI_MD_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000520
	UINT32 reserved                         :32;	//0 //
	};
}PE_E60_RESERVED001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000524 RW
	UINT32 csc_coefficient1                 :15;	//14:0	//default : 2515	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient0                 :15;	//30:16	//default : 254	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_E60_CSC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000528 RW
	UINT32 csc_coefficient3                 :15;	//14:0	//default : -1384	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient2                 :15;	//30:16	//default : 750	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_E60_CSC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900052C RW
	UINT32 csc_coefficient5                 :15;	//14:0	//default : -414	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient4                 :15;	//30:16	//default : 1798	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_E60_CSC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000530 RW
	UINT32 csc_coefficient7                 :15;	//14:0	//default : -165	Range -16384~16383
	UINT32 resvd0                           :1;
	UINT32 csc_coefficient6                 :15;	//30:16	//default : -1634	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_E60_CSC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000534 RW
	UINT32 csc_offset0                      :11;	//10:0	//Pre add offset a	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 csc_coefficient8                 :15;	//30:16	//default : 1798	Range -16384~16383
	UINT32 resvd1                           :1;
	};
}PE_E60_CSC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000538 RW
	UINT32 csc_offset2                      :11;	//10:0	//Pre add offset c	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 csc_offset1                      :11;	//26:16	//Pre add offset b	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_E60_CSC_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900053C RW
	UINT32 csc_offset4                      :11;	//10:0	//Post add offset y	Range -1024~1023
	UINT32 resvd0                           :5;
	UINT32 csc_offset3                      :11;	//26:16	//Post add offset x	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_E60_CSC_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000540 RW
	UINT32 csc_coeff_load                   :1;	//0 //this bit is auto cleared
	UINT32 csc_en                           :1;	//1 //1  = CSC enable	0 := bypass CSC
	UINT32 reserved                         :1;	//2 //
	UINT32 resvd0                           :13;
	UINT32 csc_offset5                      :11;	//26:16	//Post add offset z	Range -1024~1023
	UINT32 resvd1                           :5;
	};
}PE_E60_CSC_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000544 RW
	UINT32 pattern_type                     :3;	//2:0	//type of pattern	000 := bypass	001  = one color pattern	010  = horizontal color bar pattern 	011  = vertical color bar pattern	(Note! the first pixel's color of vertical line is different)	100  = cross hatch pattern	101  = moving horizontal color bar pattern	110  = moving vertical color bar pattern	111  = moving cross hatch pattern
	UINT32 pattern_csc                      :1;	//3 //0 := Y/Cb/Cr color pattern gen	1  = G/B/R color pattern gen
	UINT32 pattern_detail                   :4;	//7:4	//when pattern_type is 001	0000  = white	0001  = yellow	0010  = cyan	0011  = green	0100  = magenta	0101  = red	0110 := blue	0111  = black	1000  = horizontal gradation	1001  = vertical gradation	1010  = color gradation	1011  = Y/C gradation	1100  = black and white for deinter test	when pattern_type is 010 or 101	0000  = 2 pixel width	0001  = 4 pixel width	0010  = 8 pixel width	0011  = 16 pixel width	0100  = 32 pixel width	0101  = 64 pixel width	0110 := 128 pixel width	when pattern_type is 011 or 110	0000  = 1 line height	0001  = 2 line height	0010  = 4 line height	0011  = 8 line height	0100  = 16 line height	0101  = 32 line height	0110 := 64 line height
	UINT32 reg_update_pulse                 :1;	//8 //Vpulse generation at no vsync only for simulation (auto clear)
	UINT32 field_fix_mode                   :2;	//10:9	//00 := bypass field	01  = fix high	10  = fix low	11  = forcing field at every vsync
	UINT32 black_sel                        :1;	//11 //selection of black 	0 : YC black	1 : RGB black
	UINT32 write_inhibit                    :1;	//12 //0 := normal	1  = inhibit transfer CVI to Scaler
	UINT32 sim_mode                         :1;	//13 //0:= normal	1 = simulation mode only
	UINT32 black_off                        :1;	//14 //fill it black screen for over offset	0:= black screen	1 = screen bypass
	UINT32 field_edge                       :1;	//15 //when field detection in use of vsync's edge against hsync	0:= falling edge of vsync	1 = rising edge of vsync
	UINT32 ha_gen                           :1;	//16 //when de_mode is enable, hactive is made during vactive low	0 := dvi_hoffset read value apply	1  = ha is not generated during vactive low
	UINT32 monitor_on                       :1;	//17 //output of cvi xsize is divided by below value.	0 := default	1  = divide2	2  = divide4
	UINT32 force_update                     :1;	//18 //host force update
	UINT32 resvd                            :1;
	UINT32 yc_delay_mode_r                  :2;	//21:20	//00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 yc_delay_mode_b                  :2;	//23:22	//00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 yc_delay_mode_g                  :2;	//25:24	//00 := bypass	01  = 2 pixel pull	10  = 1 pixel pull	11  = 1 pixel delay
	UINT32 field_detect_vris                :1;	//26 //
	UINT32 sub_sample_mode                  :1;	//27 //
	UINT32 reg_update_position              :4;	//31:28	//register's update position after Vsync falling	0~15 line
	};
}PE_E60_MISC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000548 RO
	UINT32 hoffset_read                     :13;	//12:0	//Horizontal sync offset read
	UINT32 resvd0                           :3;
	UINT32 voffset_read                     :13;	//28:16	//Vertical sync offset read
	UINT32 resvd1                           :3;
	};
}PE_E60_OFFSET_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900054C RW
	UINT32 cv_4p_manual_en                  :1;	//0 //0 := auto mode all mode is 4p except component(1p) and CVD(1p)	1 : manual mode
	UINT32 cv_4p_mode                       :1;	//1 //when cv_4p_manual_en = 1	0 := 1p	1  = 4p
	UINT32 reserved0                        :2;	//2 //
	UINT32 hs_bypass                        :1;	//4 //0 := CDC throughout sync	1  = original delayed sync
	UINT32 vs_bypass                        :1;	//5 //0 := CDC throughout sync	1  = original delayed sync
	UINT32 fd_bypass                        :1;	//6 //0 := CDC throughout sync	1  = original delayed sync
	UINT32 sync_bypass                      :1;	//7 //0 := hs,vs,fd 's changing, => sync chaning	1  = hs,vs,fd is not changing during no data period
	UINT32 fal_sel_v                        :1;	//8 //0 := fal_ext_vs	1 =  fal_ext_ha
	UINT32 reserved1                        :1;	//31:0	//
	UINT32 reg_frl_420                      :1;	//10 //0 : default	1 : buffer mode
	UINT32 reserved2                        :21;	//31:0	//
	};
}PE_E60_MISC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000550
	UINT32 reserved                         :32;	//0 //
	};
}PE_E60_RESERVED002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000554 RO
	UINT32 vd_line_count_curr               :16;	//15:0	//Line count of Total VD sync in one frame (current frame)
	UINT32 vd_front_porch                   :16;	//31:16	//Front porch line
	};
}PE_E60_SIZE_STATUS7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000558 RO
	UINT32 sd_hoffset_indurance_read        :8;	//7:0	//This register is increasing and then maintains Max value, when previous and current frame's hoffset is the same. At the normal condition this value should be 255	[Max 255]
	UINT32 sd_voffset_indurance_read        :8;	//15:8	//This register is increasing and then maintain Max value, when previous and current frame's voffset is the same. At the normal condition this value should be 255	[Max 255]
	UINT32 sd_hsync_fault_flag_read         :1;	//16 //0 = normal	1 = when de signal is high, hsync is low
	UINT32 sd_vsync_fault_flag_read         :1;	//17 //0 = normal	1 = when de signal is high, vsync is low
	UINT32 h_sync_polarity                  :1;	//18 //Detecion of poarity of Hsync	0 = positive sync(active_low)	1 = negative sync(active_high)
	UINT32 v_sync_polarity                  :1;	//19 //Detection of polarity of Vsync	0 = positive sync(active_low)	1 = negative sync(active_high)
	UINT32 field_signal                     :4;	//23:20	//accumluated field signal detect at V sync falling[LSB bit is current detected field polarity]
	UINT32 hsync_at_vsync_fall              :4;	//27:24	//accumulated hsync signal detect at V sync falling[LSB bit is current detected field polarity]
	UINT32 outfield_at_vactive_fall         :2;	//29:28	//accumulated out field signal detect at V active falling[LSB bit is current detected field polarity]
	UINT32 hoffset_over                     :1;	//30 //h offset value exceed over hsync size, no more higher h offset value will not be applied. Detected hsize is smaller than hoffset	0 = Normal state	1 = Abnormal state
	UINT32 v_offset_over                    :1;	//31 //v offset value exceed over vsync size, no more higher v offset value will not be applied. Detected vsize is smaller than voffset	0 = Normal state	1 = Abnormal state
	};
}PE_E60_SIZE_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900055C RO
	UINT32 de_line_size                     :13;	//12:0	//Pixel size of one line de	This line number is selected by line_count_sel register
	UINT32 resvd0                           :3;
	UINT32 de_line_count                    :13;	//28:16	//de line count size of one frame
	UINT32 resvd1                           :3;
	};
}PE_E60_SIZE_STATUS2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000560 RO
	UINT32 hd_sync_size                     :13;	//12:0	//Pixel size of sync duration in HD sync
	UINT32 resvd0                           :3;
	UINT32 hd_line_size                     :13;	//28:16	//Pixel size of Total HD sync in one line
	UINT32 resvd1                           :3;
	};
}PE_E60_SIZE_STATUS3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000564 RO
	UINT32 vd_sync_count                    :13;	//12:0	//Line count of sync duration in VD sync
	UINT32 resvd0                           :3;
	UINT32 vd_line_count                    :13;	//28:16	//Line count of Total VD sync in one frame
	UINT32 resvd1                           :3;
	};
}PE_E60_SIZE_STATUS4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000568 RW
	UINT32 start_pos_x                      :13;	//12:0	//Start position of X range
	UINT32 resvd                            :2;
	UINT32 pix_sum_enable                   :1;	//15 //Pixel sum enable	0:= disable	1 = enable
	UINT32 end_pos_x                        :13;	//28:16	//End position of X range
	UINT32 field_selection                  :2;	//30:29	//field selection	00:= each field detection	01 = odd field detect only	10 = even field detect only	11 = alternative field
	UINT32 debug_enable                     :1;	//31 //debug display enable	0:= disable	1 = enable
	};
}PE_E60_PIX_SUM_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900056C RW
	UINT32 start_pos_y                      :13;	//12:0	//Start position of Y range
	UINT32 resvd0                           :3;
	UINT32 end_pos_y                        :13;	//28:16	//End position of Y range
	UINT32 resvd1                           :3;
	};
}PE_E60_PIX_SUM_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000570
	UINT32 fill_color_r                     :10;	//9:0	//debug color R
	UINT32 fill_color_b                     :10;	//19:10	//debug color B
	UINT32 fill_color_g                     :10;	//29:20	//debug color G
	UINT32 reserved                         :1;	//31:0	//
	UINT32 fill_en                          :1;	//31 //debug color fill enable
	};
}PE_E60_PIX_SUM_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000574 RO
	UINT32 pix_sum_g0                       :32;	//31:0	//G port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000578 RO
	UINT32 pix_sum_b0                       :32;	//31:0	//B port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900057C RO
	UINT32 pix_sum_r0                       :32;	//31:0	//R port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000580 RO
	UINT32 pix_sum_g1                       :32;	//31:0	//G port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000584 RO
	UINT32 pix_sum_b1                       :32;	//31:0	//B port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000588 RO
	UINT32 pix_sum_r1                       :32;	//31:0	//R port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900058C RO
	UINT32 pix_sum_g2                       :32;	//31:0	//G port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000590 RO
	UINT32 pix_sum_b2                       :32;	//31:0	//B port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000594 RO
	UINT32 pix_sum_r2                       :32;	//31:0	//R port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9000598 RO
	UINT32 pix_sum_g3                       :32;	//31:0	//G port pixel sum read
	};
}PE_E60_PIX_SUM_STATUS9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900059C RO
	UINT32 pix_sum_b3                       :32;	//31:0	//B port pixel sum read
	};
}PE_E60_PIX_SUM_STATUSA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005A0 RO
	UINT32 pix_sum_r3                       :32;	//31:0	//R port pixel sum read
	};
}PE_E60_PIX_SUM_STATUSB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005A4 RW
	UINT32 hsync_fil_en                     :1;	//0 //Hsync filter enable
	UINT32 hsync_counter_en                 :1;	//1 //Counter enable for happened glitch or spike at Hsync
	UINT32 vsync_fil_en                     :1;	//2 //Vsync filter enable
	UINT32 vsync_counter_en                 :1;	//3 //Counter enable for happened glitch or spike at Vsync
	UINT32 de_fil_en                        :1;	//4 //DE filter enable
	UINT32 de_counter_en                    :1;	//5 //Counter enable for happened glitch or spike at DE
	UINT32 field_fil_en                     :1;	//6 //Field filter enable
	UINT32 field_counter_en                 :1;	//7 //Counter enable for happened glitch or spike at Field
	UINT32 resvd0                           :8;
	UINT32 line_count_sel                   :13;	//28:16	//actual line count when reading de_line_size	default : 200th line
	UINT32 resvd1                           :3;
	};
}PE_E60_SYNC_FIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005A8 RO
	UINT32 hsync_coutner                    :8;	//7:0	//Glitch or Spike number at Hsync	Max 255
	UINT32 vsync_counter                    :8;	//15:8	//Glitch or Spike number at Vsync	Max 255
	UINT32 de_counter                       :8;	//23:16	//Glitch or Spike number at DE	Max 255
	UINT32 field_counter                    :8;	//31:24	//Glitch or Spike number at Field	Max 255
	};
}PE_E60_SYNC_FIL_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005AC
	UINT32 hdn_y_coef2                      :10;	//9:0	//
	UINT32 hdn_y_coef1                      :10;	//19:10	//
	UINT32 hdn_y_coef0                      :10;	//29:20	//
	UINT32 hdn_y_reset                      :1;	//30 //
	UINT32 down_enable                      :1;	//31 //
	};
}PE_E60_H_DOWN_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005B0
	UINT32 hdn_c_coef2                      :10;	//9:0	//
	UINT32 hdn_c_coef1                      :10;	//19:10	//max size 256
	UINT32 hdn_c_coef0                      :10;	//29:20	//
	UINT32 hdn_c_reset                      :1;	//30 //
	UINT32 reserved                         :1;	//31 //
	};
}PE_E60_H_DOWN_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005B4
	UINT32 vdn_y_coef2                      :10;	//9:0	//
	UINT32 vdn_y_coef1                      :10;	//19:10	//
	UINT32 vdn_y_coef0                      :10;	//29:20	//
	UINT32 vdn_y_reset                      :1;	//30 //
	UINT32 i_down_420                       :1;	//31 //0 : 444 down mode	1 : 420 down mode
	};
}PE_E60_V_DOWN_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005B8
	UINT32 vdn_c_coef2                      :10;	//9:0	//
	UINT32 vdn_c_coef1                      :10;	//19:10	//
	UINT32 vdn_c_coef0                      :10;	//29:20	//
	UINT32 vdn_c_reset                      :1;	//30 //
	UINT32 reserved                         :1;	//31 //
	};
}PE_E60_V_DOWN_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005BC
	UINT32 reserved                         :32;	//0 //
	};
}PE_E60_RESERVED012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005C0 RW
	UINT32 sd_vd_range                      :2;	//1:0	//VD line range	00  = 8	01  = 16	10 := 32	11  = 64
	UINT32 sd_ext_range                     :2;	//3:2	//External Line range	00  = 1	01 := 2	10  = 4	11  = 8
	UINT32 intr_mask_node                   :1;	//4 //DE interrupt mask	0 := interrupt enable	1  = interrupt disable (masking)
	UINT32 intr_mask_nohsync                :1;	//5 //Hsync interrupt mask
	UINT32 intrl_mask_novsync               :1;	//6 //Vsync interrupt mask
	UINT32 intr_mask_abnormal               :1;	//7 //Abnormal condition interrupt mask
	UINT32 intr_mask_invalid                :1;	//8 //Invalid input interrupt mask
	UINT32 intr_mask_de                     :1;	//9 //Normal DE interrupt mask
	UINT32 intr_mask_hsync                  :1;	//10 //Normal Hsync interrupt mask
	UINT32 intr_mask_vsync                  :1;	//11 //Normal Vsync interrupt mask
	UINT32 intr_mask_normal                 :1;	//12 //Normal condition interrupt mask
	UINT32 intr_mask_valid                  :1;	//13 //Valid input interrupt mask
	UINT32 intr_mask_h_cnahge               :1;	//14 //To fast change of Hsync
	UINT32 sd_en                            :1;	//15 //Size detection enable	0  = disable	1 := enable
	UINT32 sd_frame_cnt                     :3;	//18:16	//over 3 frame has to maintain same line number
	UINT32 resvd0                           :1;
	UINT32 sd_novald_duration               :2;	//21:20	//duration of no valid time, the smaller this value go to low, the faster no valid signal happen	00  = 13896 unit h	01 := 8192 unit h	10  = 4096 unit h	11  = 2048 unit h
	UINT32 resvd1                           :1;
	UINT32 sd_one_field                     :1;	//23 //when SD read size of two field, it restrict only one field.	0 := 2 field read	1  = 1 field read
	UINT32 reserved                         :2;	//25:24	//debug interrup enable, source clock selection(200/400Mhz)
	UINT32 nosig_duration_de                :2;	//27:26	//Duration of DE signal's absence to detect DE no signal	00 := 5.17us over	01  = 10.34us over	10  = 20.68us over	11  = 41.37us over
	UINT32 nosig_duration_hsync             :2;	//29:28	//Duration of Hsync signal's absence to detect Hsync no signal	00 := 5.17us over	01  = 10.34us over	10  = 20.68us over	11  = 41.37us over
	UINT32 nosig_duration_vsync             :2;	//31:30	//Duration of Vsync signal's absence to detect Vsync no signal	00 := 21.17ms over (60Hz available)	01  = 42.35ms over (30Hz available)	10  = 84.70ms over (24Hz available) 	11  = 169.41ms over
	};
}PE_E60_SIZE_DETECT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005C4 RO
	UINT32 line_num_read                    :16;	//15:0	//line number of one frame(field) (using fixed clock)	Frame rate(Hz) = {1 / { (read_data * 2048 )} * de_clk_(396MHz)
	UINT32 line_width_read                  :16;	//31:16	//width of one line (using fixed clock)	pixel number = (read_data * input_source_clk_Mhz )/de_clk_396MHz
	};
}PE_E60_SIZE_DETECT_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005C8 RO
	UINT32 current_line_number_read         :12;	//11:0	//[Max 4095]
	UINT32 de_signal_detect                 :1;	//12 //0 = No DE signal	1 = DE signal is detected
	UINT32 hsync_signal_detect              :1;	//13 //0 = No Hsync signal	1 = Hsync signal is detected
	UINT32 vsync_signal_detect              :1;	//14 //0 = No Vsync signal	1 = Vsync signal is detected
	UINT32 source_valid                     :1;	//15 //0 = Source sync is not valid yet.	1 = Source sync is valid
	UINT32 sd_line_num                      :12;	//27:16	//line number of one frame(field) by de_clk, so this value may vary �1 count => see the vd_line_count(SIZE_STATUS4)
	UINT32 field_at_vactive_fall            :4;	//31:28	//accumluated out field signal detect at V active falling[LSB bit is current detected field polarity]
	};
}PE_E60_SIZE_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005CC RO
	UINT32 sd_2field_size                   :26;	//25:0	//size of two field by de_clk	60hz => 16.67ms x 2field = 33.33ms / (1/396M) = 13,200,000	30Hz => 26,400,000	24Hz => 33,000,000
	UINT32 resvd                            :6;
	};
}PE_E60_SIZE_STATUS5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005D0 RO
	UINT32 diff_vd_vcnt                     :16;	//15:0	//different vcount between current vd_vcnt and previous vd_vcnt
	UINT32 diff_ext_vcnt                    :12;	//27:16	//different vcount between current ext_vcnt and previous ext_vcnt
	UINT32 resvd                            :3;
	UINT32 vd_intr                          :1;	//31 //0 = Source sync is not valid yet.	1 = Source sync is valid
	};
}PE_E60_SIZE_STATUS6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005D4 RW/RO
	UINT32 abnormal0_en                     :1;	//0 //0 := do not apply to make abnormal flag	1  = apply to make abnormal flag
	UINT32 abnormal1_en                     :1;	//1 //
	UINT32 abnormal2_en                     :1;	//2 //
	UINT32 abnormal3_en                     :1;	//3 //
	UINT32 abnormal4_en                     :1;	//4 //
	UINT32 abnormal5_en                     :1;	//5 //
	UINT32 abnormal6_en                     :1;	//6 //
	UINT32 abnormal7_en                     :1;	//7 //
	UINT32 abnormal0_flag                   :1;	//8 //High period of V sync is too short so that is abnormal
	UINT32 abnormal1_flag                   :1;	//9 //Low period of V sync is too short so that is abnormal
	UINT32 abnormal2_flag                   :1;	//10 //High period of H sync is too short so that is abnormal
	UINT32 abnormal3_flag                   :1;	//11 //Low period of H sync is too short so that is abnormal
	UINT32 abnormal4_flag                   :1;	//12 //Periodic Vsync is not detected so that is abnormal
	UINT32 abnormal5_flag                   :1;	//13 //DE sync is not detected so that is abnormal
	UINT32 abnormal6_flag                   :1;	//14 //Hsync is not detected so that is abnormal
	UINT32 abnormal7_flag                   :1;	//15 //Vsync is not detected so that is abnormal
	UINT32 ext_clk_valid_count              :15;	//30:16	//counter value of 512 ext clk measured by de_clk(400Mhz) 512*396/count 	for ex : 297Mhz count 682
	UINT32 ext_clk_valid                    :1;	//31 //valid of ext_clk (if no ext_clk state is over 165us then this signal goes to zero)
	};
}PE_E60_SIZE_DETECT_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005D8 RW
	UINT32 abnormal_in_h                    :8;	//7:0	//H Threshold width from normal to abnormal
	UINT32 abnormal_out_h                   :8;	//15:8	//H Threshold width from abnormal to normal
	UINT32 abnormal_in_v                    :8;	//23:16	//V Threshold width from normal to abnormal
	UINT32 abnormal_out_v                   :8;	//31:24	//V Threshold width from abnormal to normal
	};
}PE_E60_SIZE_DETECT_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005DC RW
	UINT32 resvd0                           :3;
	UINT32 field_sel                        :1;	//3 //0 := Original sync select	1  = Pseudo sync select
	UINT32 hsync_sel                        :1;	//4 //0 := Original sync select	1  = Pseudo sync select
	UINT32 vsync_sel                        :1;	//5 //0 := Original sync select	1  = Pseudo sync select
	UINT32 de_sel                           :1;	//6 //0 := Original sync select	1  = Pseudo sync select
	UINT32 resvd1                           :1;
	UINT32 cr_sel                           :1;	//8 //0 := Original Cr selec	1  = Pseudo Cr select
	UINT32 resvd2                           :1;
	UINT32 cb_sel                           :1;	//10 //0 := Original Cb select	1  = Pseudo Cb select
	UINT32 resvd3                           :1;
	UINT32 y_sel                            :1;	//12 //0 := Original Y select	1  = Pseudo Y select
	UINT32 resvd4                           :7;
	UINT32 c_valid_sel                      :1;	//20 //0 := Normal condition (cvalid = yvalid)	1  = 420 mode (cvalid = 1/4 valid for 420)
	UINT32 resvd5                           :2;
	UINT32 auto_pseudo_sync_en              :1;	//23 //Automatically Pseudo sync is selected to SMUX's input until Capture input's abnormal flag is disappeared.
	UINT32 resvd6                           :8;
	};
}PE_E60_CV_OUT_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005E0 RW
	UINT32 pseudo_sync_ctrl_en              :1;	//0 //1  = enable of pseudo sync ctrl	0 := disable of pseudo sync ctrl
	UINT32 pseudo_y_data_sel                :1;	//1 //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Y
	UINT32 pseudo_cb_data_sel               :1;	//2 //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Cb
	UINT32 pseudo_cr_data_sel               :1;	//3 //0 := Y,Cb increasing, Cr decreasing	1  = designated value of pseudo_data of Cr
	UINT32 pseudo_hfp                       :14;	//17:4	//size of horizontal front porch [de_clk]
	UINT32 pseudo_hsync                     :14;	//31:18	//size of hsync [de_clk]
	};
}PE_E60_PSEUDO_SYNC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005E4 RW
	UINT32 pseudo_y                         :4;	//3:0	//MSB 4bit (default 960)
	UINT32 pseudo_hblk                      :14;	//17:4	//size of horizontal blank [de_clk]
	UINT32 pseudo_hn                        :14;	//31:18	//size of horizontal line [de_clk]
	};
}PE_E60_PSEUDO_SYNC_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005E8 RW
	UINT32 pseudo_cb                        :4;	//3:0	//MSB 4bit (default 512)
	UINT32 pseudo_vfp                       :14;	//17:4	//line number of vertical front porch
	UINT32 pseudo_vsync                     :14;	//31:18	//line number of vertical sync
	};
}PE_E60_PSEUDO_SYNC_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005EC RW
	UINT32 pseudo_cr                        :4;	//3:0	//MSB 4bit (default 512)
	UINT32 pseudo_vblk                      :14;	//17:4	//line number of vertical blank
	UINT32 pseudo_vn                        :14;	//31:18	//line number of whole frame
	};
}PE_E60_PSEUDO_SYNC_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90005F0 RW
	UINT32 interrupt_mask_method            :1;	//0 //interrupt mask method	0 : periodic mask	1 : cascade mask
	UINT32 resvd0                           :3;
	UINT32 interrupt_mask_count             :12;	//15:4	//minimum mask count (5.3ms = 1024*1/198*mask_count)
	UINT32 diff_hsize                       :14;	//29:16	//To detect fast hsync change, minimum change range
	UINT32 resvd1                           :2;
	};
}PE_E60_SIZE_DETECT_CTRL3_T;

typedef struct {
	PE_E60_TOP_CTRL_T                                       top_ctrl;	//0xC9000500
	PE_E60_OFFSET_CTRL_T                                 offset_ctrl;	//0xC9000504
	PE_E60_SIZE_CTRL_T                                     size_ctrl;	//0xC9000508
	PE_E60_INT_SYNC_CTRL0_T                           int_sync_ctrl0;	//0xC900050C
	PE_E60_INT_SYNC_CTRL1_T                           int_sync_ctrl1;	//0xC9000510
	PE_E60_CV_MASK_CTRL_T                               cv_mask_ctrl;	//0xC9000514
	PE_E60_CV_420_INCTRL_T                             cv_420_inctrl;	//0xC9000518
	PE_E60_CV_HDMI_MD_INFO_T                         cv_hdmi_md_info;	//0xC900051C
	PE_E60_RESERVED001_T                                 reserved001;	//0xC9000520
	PE_E60_CSC_CTRL0_T                                     csc_ctrl0;	//0xC9000524
	PE_E60_CSC_CTRL1_T                                     csc_ctrl1;	//0xC9000528
	PE_E60_CSC_CTRL2_T                                     csc_ctrl2;	//0xC900052C
	PE_E60_CSC_CTRL3_T                                     csc_ctrl3;	//0xC9000530
	PE_E60_CSC_CTRL4_T                                     csc_ctrl4;	//0xC9000534
	PE_E60_CSC_CTRL5_T                                     csc_ctrl5;	//0xC9000538
	PE_E60_CSC_CTRL6_T                                     csc_ctrl6;	//0xC900053C
	PE_E60_CSC_CTRL7_T                                     csc_ctrl7;	//0xC9000540
	PE_E60_MISC_CTRL_T                                     misc_ctrl;	//0xC9000544
	PE_E60_OFFSET_READ_T                                 offset_read;	//0xC9000548
	PE_E60_MISC_CTRL1_T                                   misc_ctrl1;	//0xC900054C
	PE_E60_RESERVED002_T                                 reserved002;	//0xC9000550
	PE_E60_SIZE_STATUS7_T                               size_status7;	//0xC9000554
	PE_E60_SIZE_STATUS1_T                               size_status1;	//0xC9000558
	PE_E60_SIZE_STATUS2_T                               size_status2;	//0xC900055C
	PE_E60_SIZE_STATUS3_T                               size_status3;	//0xC9000560
	PE_E60_SIZE_STATUS4_T                               size_status4;	//0xC9000564
	PE_E60_PIX_SUM_CTRL0_T                             pix_sum_ctrl0;	//0xC9000568
	PE_E60_PIX_SUM_CTRL1_T                             pix_sum_ctrl1;	//0xC900056C
	PE_E60_PIX_SUM_CTRL2_T                             pix_sum_ctrl2;	//0xC9000570
	PE_E60_PIX_SUM_STATUS0_T                         pix_sum_status0;	//0xC9000574
	PE_E60_PIX_SUM_STATUS1_T                         pix_sum_status1;	//0xC9000578
	PE_E60_PIX_SUM_STATUS2_T                         pix_sum_status2;	//0xC900057C
	PE_E60_PIX_SUM_STATUS3_T                         pix_sum_status3;	//0xC9000580
	PE_E60_PIX_SUM_STATUS4_T                         pix_sum_status4;	//0xC9000584
	PE_E60_PIX_SUM_STATUS5_T                         pix_sum_status5;	//0xC9000588
	PE_E60_PIX_SUM_STATUS6_T                         pix_sum_status6;	//0xC900058C
	PE_E60_PIX_SUM_STATUS7_T                         pix_sum_status7;	//0xC9000590
	PE_E60_PIX_SUM_STATUS8_T                         pix_sum_status8;	//0xC9000594
	PE_E60_PIX_SUM_STATUS9_T                         pix_sum_status9;	//0xC9000598
	PE_E60_PIX_SUM_STATUSA_T                         pix_sum_statusa;	//0xC900059C
	PE_E60_PIX_SUM_STATUSB_T                         pix_sum_statusb;	//0xC90005A0
	PE_E60_SYNC_FIL_CTRL_T                             sync_fil_ctrl;	//0xC90005A4
	PE_E60_SYNC_FIL_STATUS_T                         sync_fil_status;	//0xC90005A8
	PE_E60_H_DOWN_CTRL0_T                               h_down_ctrl0;	//0xC90005AC
	PE_E60_H_DOWN_CTRL1_T                               h_down_ctrl1;	//0xC90005B0
	PE_E60_V_DOWN_CTRL0_T                               v_down_ctrl0;	//0xC90005B4
	PE_E60_V_DOWN_CTRL1_T                               v_down_ctrl1;	//0xC90005B8
	PE_E60_RESERVED012_T                                 reserved012;	//0xC90005BC
	PE_E60_SIZE_DETECT_CTRL_T                       size_detect_ctrl;	//0xC90005C0
	PE_E60_SIZE_DETECT_READ_T                       size_detect_read;	//0xC90005C4
	PE_E60_SIZE_STATUS0_T                               size_status0;	//0xC90005C8
	PE_E60_SIZE_STATUS5_T                               size_status5;	//0xC90005CC
	PE_E60_SIZE_STATUS6_T                               size_status6;	//0xC90005D0
	PE_E60_SIZE_DETECT_CTRL1_T                     size_detect_ctrl1;	//0xC90005D4
	PE_E60_SIZE_DETECT_CTRL2_T                     size_detect_ctrl2;	//0xC90005D8
	PE_E60_CV_OUT_MUX_T                                   cv_out_mux;	//0xC90005DC
	PE_E60_PSEUDO_SYNC_CTRL1_T                     pseudo_sync_ctrl1;	//0xC90005E0
	PE_E60_PSEUDO_SYNC_CTRL2_T                     pseudo_sync_ctrl2;	//0xC90005E4
	PE_E60_PSEUDO_SYNC_CTRL3_T                     pseudo_sync_ctrl3;	//0xC90005E8
	PE_E60_PSEUDO_SYNC_CTRL4_T                     pseudo_sync_ctrl4;	//0xC90005EC
	PE_E60_SIZE_DETECT_CTRL3_T                     size_detect_ctrl3;	//0xC90005F0
}PE_CVI_REG_E60_T;

#endif