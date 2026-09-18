#ifndef _PE_ND_REG_E60A0_H_
#define _PE_ND_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC900E100 RW
	UINT32 load_time                        :1;	//0 //load_time	0 := load at pic_init	1 = load when reg. write
	UINT32 load_enable                      :1;	//1 //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_E60_ND0_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E104 RW
	UINT32 intr_enable                      :1;	//0 //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//6:4	//interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  tnr_end  	'001 =  ipc_end	'010 = tnrw_y_end	'011 = tnrw_c_end	'100 = NA	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//8 //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//26:16	//the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_E60_ND0_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E108 RO
	UINT32 tnr_frame_id                     :4;	//3:0	//TNR_FRAME_ID	increment every tnr_end
	UINT32 ipc_frame_id                     :4;	//7:4	//IPC_FRAME_ID	increment every ipc_end
	UINT32 tnrw_y_frame_id                  :4;	//11:8	//TNRW_Y_FRAME_ID	increment every tnrw_y_end
	UINT32 tnrw_c_frame_id                  :4;	//15:12	//TNRW_C_FRAME_ID	increment every tnrw_c_end
	UINT32 dnr_frame_id                     :8;	//23:16	//IPC_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//27:24	//PIC_INIT_FRAME_ID
	UINT32 resvd                            :4;
	};
}PE_E60_ND0_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E10C RO
	UINT32 line_cnt                         :12;	//11:0	//
	UINT32 resvd                            :4;
	UINT32 timer_cnt                        :16;	//31:16	//timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_E60_ND0_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E110 RW
	UINT32 tnr_c_en                         :1;	//0 //TNR_C_enable	TNR_C memory read&write enable
	UINT32 tnr_y_en                         :1;	//1 //TNR_Y_enable	TNR_Y memory read&write enable
	UINT32 ipc_c_en                         :1;	//2 //IPC_C_enable	IPC_C memory read enable
	UINT32 ipc_y_en                         :1;	//3 //IPC_Y_enable	IPC_Y memory read enable
	UINT32 tnr_c_444_as_420                 :1;	//4 //Enable TNR_C(T1,T3)_422_AS_420	TNR_C behaves as if 420 mode even if the data in the memory 422 format	TNR_C reads only even line: 0,2,4,8 ...
	UINT32 tnr_y2_en                        :1;	//5 //Enable TNR_Y2	It should be enabled for CLC
	UINT32 force_422_to_420                 :1;	//6 //Enable FORCE_420	If the chroma sampling type is 422 and this flag enabled, then	(1) TNR chroma data in 422 format is subsampled to be 420 before being written to the memory	(2) TNR_C(T2), IPC_C(T1) read the data as 420 format	This flag might be used to reduce memory bandwidth for chroma data of TNR & IPC
	UINT32 ipc0_y_en_prog                   :1;	//7 //mem port ipc0_y enable
	UINT32 mif_last_mode                    :3;	//10:8	//you should set this value to 0x7 if you want MIF to work correctly in case of abnormal-pic_init
	UINT32 tnrw_off                         :1;	//11 //TNR write OFF
	UINT32 resvd0                           :1;
	UINT32 tnr_m_en                         :1;	//13 //TNR_M (motion info) memory read&write enable
	UINT32 force_444_to_422                 :1;	//14 //Enable FORCE_422	If the chroma sampling type is 444 and this flag enabled, then	(1) TNR chroma data in 444 format is subsampled to be 422 before being written to the memory	(2) TNR_C, IPC_C read the data as 422 format
	UINT32 resvd1                           :1;
	UINT32 detour_enable                    :1;	//16 //
	UINT32 half_rate_en                     :1;	//17 //should be enabled for the interlaced source
	UINT32 ibuf_en                          :2;	//19:18	//(19) input buffer enable Y 	(18) input buffer enable C
	UINT32 minfo_hsample_mode               :3;	//22:20	//* this flag valid only if "tnr_m_en" = 1	* minfo_hsample_mode and minfo_qurt_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 4K or 1080p would be typical case for it   If this mode ON, It reduces hsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 = minfo hhalf mode disable	1 = minfo hhalf mode enable	2 = minfo hqurt mode enable	3 = reserved
	UINT32 minfo_vsample_mode               :3;	//25:23	//* this flag valid only if "tnr_m_en" = 1	* minfo_vsample_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 1080p would be typical case for it   If this mode ON, It reduces vsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 := minfo vhalf mode disable	1 = minfo vhalf mode enable (V subsampling: 0,2,4,6,...)	2 = minfo vqurt mode enable (V subsampling: 0,4,8,12,...)	5 = minfo vhalf mode enable (V subsampling: 0,3,4,7,...)	6 = minfo vqurt mode enable (V subsampling: 2,6,10,14,...)
	UINT32 o_line_ctrl_mode                 :1;	//26 //0:= select odd line for Top field, even line for Bottom field	1 = select even line for Top field, odd line for Bottom field
	UINT32 o_line_ctrl_en                   :1;	//27 //output line subsample enable
	UINT32 tnr_in_lsb_mode                  :2;	//29:28	//00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 m_run_id                         :2;	//31:30	//
	};
}PE_E60_ND0_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E114 RW
	UINT32 hsize                            :12;	//11:0	//HSIZE: 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :1;
	UINT32 cs_type                          :3;	//15:13	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :13;	//28:16	//VSIZE: 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :2;
	UINT32 scan_type                        :1;	//31 //scan_type	1 : progressive	0 : interlaced
	};
}PE_E60_ND0_PE0_SRC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E118 RW
	UINT32 field_id                         :1;	//0 //FIELD_ID	0 := top	1 = bottom
	UINT32 resvd0                           :3;
	UINT32 field_mode                       :2;	//5:4	//0 := manual field setting	1 = field auto-inversion	2 = use detected field 	3 = use detected field: inversion
	UINT32 field_inv                        :1;	//6 //field inversion enable: valid only if field_mode = 0
	UINT32 resvd1                           :1;
	UINT32 secam_line                       :1;	//8 //0 := Cb-line first	1 = Cr-line first
	UINT32 resvd2                           :3;
	UINT32 secam_line_mode                  :2;	//13:12	//0 := manual secam_cline	1 = manual secam_cline (inversion)	2 = use detected secam line	3 = use detected secam line(inversion)
	UINT32 resvd3                           :2;
	UINT32 out_cs_type                      :3;	//18:16	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 resvd4                           :1;
	UINT32 out_422_hsample_mode             :1;	//20 //0 := 0,2,4,6,…	1 = 1,3,5,7,…
	UINT32 out_420_vsample_mode             :1;	//21 //0 := 0,3,4,7,…	1 = 0,2,4,6,…
	UINT32 resvd5                           :10;
	};
}PE_E60_ND0_PE0_FIELD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E11C RW
	UINT32 in_hsize                         :12;	//11:0	//
	UINT32 resvd0                           :1;
	UINT32 ptn_en_c                         :1;	//13 //
	UINT32 lend_manual_vsize                :1;	//14 //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_vsize	1 = internal line_end generated by in_vsize [11:0]
	UINT32 resvd1                           :1;
	UINT32 in_vsize                         :13;	//28:16	//
	UINT32 ptn_en_y                         :1;	//29 //
	UINT32 lend_manual_hsize                :1;	//30 //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_hsize	1 = internal line_end generated by in_hsize [11:0]
	UINT32 lend_ctrl_en                     :1;	//31 //0 := use internla line_end	1 = use external line end
	};
}PE_E60_ND0_PE0_DEBUG_LEND_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E120 RW
	UINT32 hoffset                          :13;	//12:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :17;
	UINT32 hsize_sel                        :1;	//30 //0 : PE0_IN_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  PE0_IN_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND0_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E124 RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND0_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E128 RW
	UINT32 fbc_reserved                     :32;	//31:0	//
	};
}PE_E60_ND0_FBC_CTRL0_RESERVED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E12C RW
	UINT32 fbc_reserved                     :32;	//31:0	//
	};
}PE_E60_ND0_FBC_CTRL1_RESERVED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E130 RW
	UINT32 en_rd_t1_y                       :1;	//0 //Read T-1 Y Enable for IPC
	UINT32 en_rd_t1_c                       :1;	//1 //Read T-1 C Enable for IPC
	UINT32 en_rd_t2_y                       :1;	//2 //Read T-2 Y Enable for IPC, TNR
	UINT32 en_rd_t2_c                       :1;	//3 //Read T-2 C Enable for IPC, TNR
	UINT32 en_rd_t3_y                       :1;	//4 //Read T-3 Y Enable for IPC
	UINT32 en_rd_t3_c                       :1;	//5 //Read T-3 C Enable for IPC
	UINT32 en_rd_t4_y                       :1;	//6 //Read T-4 Y Enable for IPC, CLC
	UINT32 en_rd_t1_m                       :1;	//7 //Read Minfo Enable
	UINT32 en_wr_tnrw_y                     :1;	//8 //Write IPC, TNR, CLC Y Enable
	UINT32 en_wr_tnrw_c                     :1;	//9 //Write IPC, TNR, CLC C Enable
	UINT32 en_wr_tnrw_m                     :1;	//10 //Write Minfo Enable
	UINT32 resvd0                           :4;
	UINT32 manual_mem_off                   :1;	//15 //manual memory port off
	UINT32 resvd1                           :16;
	};
}PE_E60_ND0_PE0_MEM_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E134 RW
	UINT32 lreq_dly_c                       :11;	//10:0	//unit: 16 de_clk
	UINT32 lreq_dly_c_en                    :1;	//11 //
	UINT32 resvd0                           :4;
	UINT32 lreq_dly_y                       :11;	//26:16	//
	UINT32 lreq_dly_y_en                    :1;	//27 //
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_PE0_DEBUG_LREQ_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E138 RW
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 : TNRW_OUT_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  TNRW_OUT_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND0_TNRW_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E13C RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND0_TNRW_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E140 RW
	UINT32 reg_tnr_en                       :1;	//0:0	//
	UINT32 reg_hw_col_data_copy_en          :1;	//1:1	//E20
	UINT32 reg_sc_detect_hres               :1;	//2:2	//
	UINT32 reg_clc_nt_pal                   :1;	//3:3	//
	UINT32 reg_clc_mem_wr_mode              :2;	//5:4	//
	UINT32 reg_sad_8x3_res                  :2;	//7:6	//
	UINT32 reg_sad_8x3_iir_en               :1;	//8:8	//
	UINT32 reg_sad_8x3_chroma_en            :1;	//9:9	//
	UINT32 reg_minfo_sw                     :2;	//11:10	//
	UINT32 reg_minfo_mode10                 :2;	//13:12	//[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt                    :2;	//15:14	//
	UINT32 reg_tnr_single_en                :1;	//16:16	//TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en               :1;	//17 //chg
	UINT32 reg_minfo_mode32                 :2;	//19:18	//
	UINT32 reg_minfo_mode74                 :4;	//23:20	//
	UINT32 reg_sad_8x3_iir_alpha            :8;	//31:24	//for TNR, DNR
	};
}PE_E60_ND0_TNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E144 RW
	UINT32 reg_dbg_show                     :4;	//3:0	//
	UINT32 reg_ma_motion_iir_alpha          :8;	//11:4	//for decontour, new
	UINT32 reg_ma_motion_iir_en             :1;	//12 //for decontour, new
	UINT32 reg_ma_motion_chroma_en          :1;	//13 //for decontour, new
	UINT32 reg_ma_motion_res                :2;	//15:14	//for decontour, new
	UINT32 reg_dbg_tnrw                     :2;	//17:16	//TNR Write를 선택합니다. 	0 = TNR 출력 (T)	1 = TNR 현재 입력 (T)	2 = TNR 이전 입력 (T-1)
	UINT32 reg_ma_motion_lsb6_sel           :1;	//18 //for decontour, new
	UINT32 reg_sad_8x3_lsb6_sel             :1;	//19 //new
	UINT32 reg_tnri_debug_mode              :2;	//21:20	//
	UINT32 resvd0                           :2;
	UINT32 reg_minfo_mode118                :4;	//27:24	//
	UINT32 reg_sc_scale2                    :3;	//30:28	//
	UINT32 resvd1                           :1;
	};
}PE_E60_ND0_TNR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E148 RW
	UINT32 sc_en                            :1;	//0 //scene change detection enable
	UINT32 sc_max_flt_en                    :1;	//1 //scene change: temporal max filter enable
	UINT32 sc_calc_prev_hist                :1;	//2 //scene change: calculation mode for previous histogram	0:= delay current histogram	1 = compute histogram for previous data
	UINT32 sc_chroma_en                     :1;	//3 //scene change: use of chroma histogram difference
	UINT32 sc_scale                         :3;	//6:4	//bit-select from 21bit scene change measure to 8-bit measure	0 := sc_measure[21 -1 :21-8]	1 = sc_measure [21 -3 :21-10]	2 = sc_measure [21 -5 :21-12]	3 = sc_measure [21 -7 :21-14]	4 = sc_measure [21 -9 :21-16]	5 = sc_measure [21-11:21-18]	6 = sc_measure [21-13:21-20]	7 = sc_measure [21-141:21-21]
	UINT32 resvd0                           :1;
	UINT32 sc_max_flt_tap                   :3;	//10:8	//scene change: temporal max filter tap
	UINT32 resvd1                           :1;
	UINT32 sc_chroma_gain                   :3;	//14:12	//scene change: gain of chroma histogram difference	0 := x1	1 = x1/2	2 = x1/4	3 = x1/8	4 = x1/16	5 = x1/32
	UINT32 sc_out_mode                      :1;	//15 //TNR_STATUS_04: scene change measure update mode	0:= update every frame	1 = update only if the scene_measure is larger than "sc_th_memc"
	UINT32 sc_th_ma                         :8;	//23:16	//scene change threshold for MA
	UINT32 sc_th_memc                       :8;	//31:24	//scene change threshold for MEMC
	};
}PE_E60_ND0_TNR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E14C RW
	UINT32 show_dbg_bar_scale               :3;	//2:0	//debug bar scale
	UINT32 resvd0                           :1;
	UINT32 show_dbg_bar_en                  :4;	//7:4	//debug bar enable
	UINT32 resvd1                           :8;
	UINT32 show_dbg_bar0_mux                :4;	//19:16	//input mux for the lowest debug bar	0x0 := x_peak	0x1 = motion vector variance	0x2 = motion vector H	0x3 = motion vector V	0x4 = abs(NR-P2)	0x5 = abs(NR-CC)	0x6 = MA motion	0x7 = spatial variance	0x8 = scene change
	UINT32 show_dbg_bar1_mux                :4;	//23:20	//input mux for 2nd debug bar
	UINT32 show_dbg_bar2_mux                :4;	//27:24	//input mux for 3rd debug bar
	UINT32 show_dbg_bar3_mux                :4;	//31:28	//input mux for the highest debug bar
	};
}PE_E60_ND0_TNR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E150 RW
	UINT32 manual_debug_bar_09              :8;	//7:0	//for manual debug mode ( reg_mux : 1001)
	UINT32 manual_debug_bar_10              :8;	//15:8	//for manual debug mode ( reg_mux : 1010)
	UINT32 manual_debug_bar_11              :8;	//23:16	//for manual debug mode ( reg_mux : 1011)
	UINT32 manual_debug_bar_12              :8;	//31:24	//for manual debug mode ( reg_mux : 1100)
	};
}PE_E60_ND0_TNR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E154 RW
	UINT32 reg_mamc_blend_mode              :2;	//1:0	//
	UINT32 reg_mamc_blend_mv_max_or_sum     :1;	//2 //0: max, 1: sum
	UINT32 reg_mamc_ma_sad_cut              :1;	//3 //0: 6b, 1:2b
	UINT32 reg_mamc_mc_sad_cut              :1;	//4 //0: 6b, 1:2b
	UINT32 resvd0                           :11;
	UINT32 reg_mv_pv_fix_v                  :4;	//19:16	//
	UINT32 reg_mv_pv_fix_h                  :5;	//24:20	//
	UINT32 resvd1                           :6;
	UINT32 reg_mv_pv_fix_en                 :1;	//31 //
	};
}PE_E60_ND0_TNR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E158 RW
	UINT32 reg_me_lb_base                   :8;	//7:0	//
	UINT32 reg_me_pv_base                   :8;	//15:8	//
	UINT32 reg_me_lb_polarity               :1;	//16 //
	UINT32 resvd                            :15;
	};
}PE_E60_ND0_TNR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E15C RW
	UINT32 resvd0                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//5:4	//
	UINT32 resvd1                           :2;
	UINT32 reg_sc_en                        :1;	//8 //
	UINT32 resvd2                           :23;
	};
}PE_E60_ND0_TNR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E160 RW
	UINT32 reg_mv_h_fix_val                 :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_mv_v_fix_val                 :4;	//11:8	//
	UINT32 reg_mv_h_fix_fb_val              :5;	//16:12	//
	UINT32 resvd1                           :3;
	UINT32 reg_mv_v_fix_fb_val              :4;	//23:20	//
	UINT32 reg_debug_sel                    :4;	//27:24	//
	UINT32 reg_lb_monitor_sel               :2;	//29:28	//
	UINT32 reg_mv_fb_fix                    :1;	//30 //
	UINT32 reg_mv_fix                       :1;	//31 //
	};
}PE_E60_ND0_TNR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E164 RW
	UINT32 reg_sad_base                     :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_lb_smooth_clip               :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_pv_smooth_clip               :6;	//21:16	//
	UINT32 resvd2                           :10;
	};
}PE_E60_ND0_TNR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E168 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E16C RW
	UINT32 lb_smooth_en                     :1;	//0 //
	UINT32 pv_smooth_en                     :1;	//1 //
	UINT32 pmv_hist_en                      :1;	//2 //new
	UINT32 resvd                            :28;
	UINT32 reg_me_n15_protection            :1;	//31 //
	};
}PE_E60_ND0_TNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E170 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E174 RW
	UINT32 reg_min_sad_ratio                :8;	//7:0	//new
	UINT32 reg_lb_cost_ratio                :8;	//15:8	//new
	UINT32 reg_zero_sad_ratio               :8;	//23:16	//new
	UINT32 reg_zero_mv_blk_mv_sel           :2;	//25:24	//chg
	UINT32 resvd0                           :2;
	UINT32 reg_zero_sad_adv                 :1;	//28 //chg
	UINT32 resvd1                           :3;
	};
}PE_E60_ND0_TNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E178 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E17C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E180 RW
	UINT32 reg_sad_acc_mode                 :2;	//1:0	//
	UINT32 reg_bmv_fix_en                   :1;	//2 //
	UINT32 resvd0                           :1;
	UINT32 reg_bmv_fix_v                    :4;	//7:4	//
	UINT32 reg_bmv_fix_h                    :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_n_hblk                       :4;	//19:16	//
	UINT32 reg_n_vblk                       :5;	//24:20	//
	UINT32 resvd2                           :4;
	UINT32 reg_use_fw_gmv_en                :1;	//29 //new
	UINT32 reg_col_overlap_en               :1;	//30 //new
	UINT32 reg_col_data_share_en            :1;	//31 //new
	};
}PE_E60_ND0_TNR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E184 RW
	UINT32 reg_blk_vsize                    :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_blk_hsize                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_TNR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E188 RW
	UINT32 reg_bsad_scale                   :3;	//2:0	//
	UINT32 reg_bmv_rst_mode                 :1;	//3 //
	UINT32 reg_gsad_scale                   :3;	//6:4	//
	UINT32 resvd                            :1;
	UINT32 reg_gmv_gmv_tl                   :7;	//14:8	//
	UINT32 reg_gmv_gmv_tl_en                :1;	//15 //
	UINT32 reg_bmv_gmv_tl                   :7;	//22:16	//
	UINT32 reg_bmv_gmv_tl_en                :1;	//23 //
	UINT32 reg_bmv_pmv_tl                   :7;	//30:24	//
	UINT32 reg_bmv_pmv_tl_en                :1;	//31 //
	};
}PE_E60_ND0_TNR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E18C RW
	UINT32 bmv_coring_th                    :8;	//7:0	//
	UINT32 reg_col_overlap_mode             :2;	//9:8	//new
	UINT32 resvd                            :6;
	UINT32 gmv_0mv_tl                       :7;	//22:16	//0MV 영향력의 강도 조절 : x10이 bypass이고 높을 수록 강하게 영향을 줌
	UINT32 gmv_0mv_tl_en                    :1;	//23 //Global MV에 0MV 보너스를 줄 것인가?
	UINT32 bmv_0mv_tl                       :7;	//30:24	//0MV 영향력의 강도 조절 : x10이 bypass이고 높을 수록 강하게 영향을 줌
	UINT32 bmv_0mv_tl_en                    :1;	//31 //Large Block MV에 0MV 보너스를 줄 것인가?
	};
}PE_E60_ND0_TNR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E190 RW
	UINT32 reg_detail_beta_mul              :8;	//7:0	//
	UINT32 reg_detail_alpha_mul             :8;	//15:8	//
	UINT32 reg_edge_beta_mul                :8;	//23:16	//
	UINT32 reg_edge_alpha_mul               :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E194 RW
	UINT32 reg_svar_scale                   :3;	//2:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_sad_8x3_res2                 :2;	//9:8	//
	UINT32 resvd1                           :22;
	};
}PE_E60_ND0_TNR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E198 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E19C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1A0 RW
	UINT32 resvd0                           :1;
	UINT32 reg_ombc_en                      :1;	//1 //
	UINT32 resvd1                           :2;
	UINT32 reg_luma_gain_en                 :1;	//4 //
	UINT32 reg_crgn_gain_en                 :1;	//5 //
	UINT32 reg_chroma_sad_res               :2;	//7:6	//
	UINT32 resvd2                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//13:12	//
	UINT32 resvd3                           :2;
	UINT32 reg_avg_cmp_en                   :1;	//16 //
	UINT32 reg_avg_cmp_res                  :3;	//19:17	//
	UINT32 reg_debug_sel                    :4;	//23:20	//
	UINT32 resvd4                           :4;
	UINT32 reg_cnt_mode                     :3;	//30:28	//
	UINT32 reg_chroma_sad_en                :1;	//31 //
	};
}PE_E60_ND0_TNR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1A4 RW
	UINT32 resvd                            :24;
	UINT32 reg_skin_master_gain             :8;	//31:24	//new
	};
}PE_E60_ND0_TNR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1A8 RW
	UINT32 reg_tnr_final_lut_yy_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_yy_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1AC RW
	UINT32 reg_tnr_final_lut_yy_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_yy_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1B0 RW
	UINT32 reg_tnr_final_lut_yy_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND0_TNR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1B4 RW
	UINT32 reg_tnr_final_lut_cb_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cb_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1B8 RW
	UINT32 reg_tnr_final_lut_cb_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cb_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1BC RW
	UINT32 reg_tnr_final_lut_cb_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND0_TNR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1C0 RO
	UINT32 w_gsad                           :8;	//7:0	//
	UINT32 w_gmv                            :9;	//16:8	//
	UINT32 resvd                            :7;
	UINT32 w_apl_detail                     :8;	//31:24	//
	};
}PE_E60_ND0_TNR_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1C4 RO
	UINT32 w_apl_motion                     :8;	//7:0	//
	UINT32 w_apl_mc_sad                     :8;	//15:8	//
	UINT32 w_apl_var                        :8;	//23:16	//
	UINT32 w_apl_edge                       :8;	//31:24	//
	};
}PE_E60_ND0_TNR_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1C8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1CC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1D0 RW
	UINT32 main_lut_indir_addr              :6;	//5:0	//
	UINT32 resvd0                           :6;
	UINT32 main_lut_ai_enable               :1;	//12 //TNR Main-LUT Ctrl. AI enable
	UINT32 resvd1                           :2;
	UINT32 main_lut_load                    :1;	//15 //
	UINT32 resvd2                           :16;
	};
}PE_E60_ND0_TNR_MAIN_LUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1D4 RW
	UINT32 main_lut_indir_data0             :32;	//31:0	//TNR Main-LUT Ctrl. Indirect Access Data 0 63:32 (MSB8u:Biggest, LSB8u:Smallest)
	};
}PE_E60_ND0_TNR_MAIN_LUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1DC RO
	UINT32 sc_measure                       :8;	//7:0	//scene change detection measure
	UINT32 apl_y                            :8;	//15:8	//
	UINT32 sc_measure_16                    :16;	//31:16	//scene change measure (16b)
	};
}PE_E60_ND0_TNR_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1E0 RW
	UINT32 resvd                            :16;
	UINT32 reg_gf_gain                      :8;	//23:16	//
	UINT32 reg_blur_coef                    :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1E4 RW
	UINT32 same_protection_en               :1;	//0 //
	UINT32 reg_p_mv0_only                   :1;	//1 //
	UINT32 reg_p_non_mv0_only               :1;	//2 //new
	UINT32 reg_final_lut_en                 :1;	//3 //new
	UINT32 resvd0                           :4;
	UINT32 reg_same_sad_th                  :8;	//15:8	//
	UINT32 reg_move_step                    :8;	//23:16	//
	UINT32 resvd1                           :8;
	};
}PE_E60_ND0_TNR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1E8 RW
	UINT32 reg_tnr_final_lut_cr_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cr_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1EC RW
	UINT32 reg_tnr_final_lut_cr_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cr_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_TNR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1F0 RW
	UINT32 reg_tnr_final_lut_cr_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND0_TNR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1F4 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1F8 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E1FC RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND0_TNR_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E200 RW
	UINT32 cr_luma_mode                     :2;	//1:0	//Luma Operation Mode	'00 = Spatial Operation Only	'01 = Temporal Average Only	'1x := Motion Adaptive De-interlacing
	UINT32 resvd                            :1;
	UINT32 cr_n1_cc_blend_en                :1;	//3 //
	UINT32 cr_chroma_mode                   :2;	//5:4	//Chroma Operation Mode	'00 = Spatial Operation Only	'01 = Temporal Average Only	'1x := Motion Adaptive De-interlacing
	UINT32 cr_integer_edi                   :1;	//6 //
	UINT32 cr_chroma_edi                    :1;	//7 //
	UINT32 cr_st_2d_v_flt_range2            :4;	//11:8	//
	UINT32 cr_st_2d_v_flt_range             :4;	//15:12	//
	UINT32 cr_ori_3d_blur_y                 :2;	//17:16	//
	UINT32 cr_ori_3d_blur_c                 :2;	//19:18	//
	UINT32 cr_tava_v_edge_adap              :1;	//20 //
	UINT32 cr_tava_debug_mode               :1;	//21 //
	UINT32 cr_tava_st_adap                  :1;	//22 //
	UINT32 cr_tava_en                       :1;	//23 //
	UINT32 cr_hmc_force_fmd                 :1;	//24 //
	UINT32 cr_st_2d_v_flt_en                :1;	//25 //
	UINT32 cr_clc_fmd_off                   :1;	//26 //
	UINT32 cr_chroma_tava_only              :1;	//27 //
	UINT32 cr_film_auto_gain                :1;	//28 //
	UINT32 cr_film_apply_c                  :1;	//29 //
	UINT32 cr_film_apply_y                  :1;	//30 //
	UINT32 cr_film_mode_enable              :1;	//31 //
	};
}PE_E60_ND0_IPC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E204 RW
	UINT32 cr_hmc_en_sel1                   :2;	//1:0	//HMC, Enabled Input ID 1
	UINT32 cr_hmc_en_sel2                   :2;	//3:2	//HMC, Enabled Input ID 2
	UINT32 st_flt_mode                      :1;	//4 //0 : old , 1 : new
	UINT32 resvd0                           :1;
	UINT32 cr_fmd_vfilter_en                :1;	//6 //FMD, use hmc vfilter for FMD artifact reduce
	UINT32 cr_fend_auto                     :1;	//7 //FMD, frame_end position auto detect
	UINT32 cr_st_iir_dec_gain               :4;	//11:8	//
	UINT32 cr_st_iir_inc_gain               :4;	//15:12	//ST_IIR_alpha
	UINT32 cr_st_flt_enable                 :1;	//16 //
	UINT32 cr_st_iir_en                     :1;	//17 //
	UINT32 cr_hmc_flt_enable                :1;	//18 //
	UINT32 cr_game_mode                     :1;	//19 //
	UINT32 cr_st_2d_v_flt_range             :4;	//23:20	//
	UINT32 resvd1                           :1;
	UINT32 cr_black_mask                    :1;	//25 //
	UINT32 cr_ipc_debug_show                :5;	//30:26	//
	UINT32 cr_5f_mode                       :1;	//31 //
	};
}PE_E60_ND0_IPC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E208 RW
	UINT32 fuzzy_ctrl_point_x0              :8;	//7:0	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x4              :8;	//15:8	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x1              :8;	//23:16	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y1              :8;	//31:24	//control points for 2D/3D decision
	};
}PE_E60_ND0_IPC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E20C RW
	UINT32 fuzzy_ctrl_point_x2              :8;	//7:0	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y2              :8;	//15:8	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x3              :8;	//23:16	//control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y3              :8;	//31:24	//control points for 2D/3D decision
	};
}PE_E60_ND0_IPC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E210 RW
	UINT32 et_offset__s7                    :8;	//7:0	//signed 7bit (F5 means -10)	Smaller > Weight to 3D	Bigger > Weight to 2D
	UINT32 motion_x_tearing_gain            :8;	//15:8	//Motion Area Tearing Gain	80 := x2.0	40 = x1.0
	UINT32 tearing_gain                     :8;	//23:16	//All Area Tearing Gain ( Difficult to Excuse Pattern Tearing )
	UINT32 motion_gain                      :8;	//31:24	//Motion Gain	40 := x1.0
	};
}PE_E60_ND0_IPC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E214 RW
	UINT32 resvd0                           :12;
	UINT32 cr_t_grad_weight                 :4;	//15:12	//Variance Normalize에서 Variance를 구하기 위한 Gain
	UINT32 resvd1                           :4;
	UINT32 cr_v_grad_weight                 :4;	//23:20	//Variance Normalize에서 Variance를 구하기 위한 Gain
	UINT32 resvd2                           :4;
	UINT32 cr_h_grad_weight                 :4;	//31:28	//Variance Normalize에서 Variance를 구하기 위한 Gain
	};
}PE_E60_ND0_IPC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E218 RW
	UINT32 cr_normalize_en                  :1;	//0 //Motion에 Normalize 사용 유무
	UINT32 cr_flat_only                     :1;	//1 //Normalize시 x1.0이하의 강도는 x1.0으로 만듦
	UINT32 cr_motion_iir_en                 :1;	//2 //IIR된 TNR motion 을 Blending함
	UINT32 resvd0                           :1;
	UINT32 cr_tearing_normalize_en          :1;	//4 //Tearing Score에 Normalize 사용 유무
	UINT32 resvd1                           :3;
	UINT32 cr_normalize_base                :8;	//15:8	//x (Center + a) / (Variance + a) 에서 a에 해당하는 값 , 낮을수록 강하게 Normalize함
	UINT32 cr_normalize_center              :8;	//23:16	//Normalize시 x1.0의 기준이 되는 Variance
	UINT32 cr_motion_coring                 :8;	//31:24	//Motion이 이값보다 낮게 나오면 강제로 3D로 돌림
	};
}PE_E60_ND0_IPC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E21C RW
	UINT32 resvd0                           :1;
	UINT32 cr_v_en                          :1;	//1 //vertical Tearing Check Enable
	UINT32 cr_45_en                         :1;	//2 //45 degree Tearing Check enable
	UINT32 cr_15_en                         :1;	//3 //15 degree Tearing check Enable
	UINT32 resvd1                           :20;
	UINT32 cr_iir_motion_gain               :8;	//31:24	//motion_IIR_alpha
	};
}PE_E60_ND0_IPC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E220 RW
	UINT32 fmd_caption_range_top            :12;	//11:0	//FMD, CaptionRange Top
	UINT32 resvd0                           :4;
	UINT32 fmd_caption_range_bot            :12;	//27:16	//FMD, CaptionRange Bottom
	UINT32 resvd1                           :2;
	UINT32 caption_flow_detected            :1;	//30 //Caption-Flow_Detected
	UINT32 hmc_when_cap_not_detected        :1;	//31 //Apply HMC Filter when "FilmDetected and CapFlowNotDetected and CaptionRange"	0 := apply HMC in CaptionRange only when capFlowDetected is 1	1 = apply HMC in CaptionRange even when capFlowDetected is 0
	};
}PE_E60_ND0_IPC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E224 RW
	UINT32 pn_fmd_a_th                      :8;	//7:0	//FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pn_variance_th                   :8;	//23:16	//
	UINT32 pn_fmd_motion_th                 :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E228 RW
	UINT32 pcnc_fmd_a_th                    :8;	//7:0	//FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pcnc_variance_th                 :8;	//23:16	//
	UINT32 pcnc_fmd_motion_th               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E22C RW
	UINT32 cr_pndiff_th                     :8;	//7:0	//
	UINT32 cr_center_bound_ctrl             :8;	//15:8	//
	UINT32 cr_dn_bound_ctrl                 :8;	//23:16	//
	UINT32 cr_up_bound_ctrl                 :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E230 RW
	UINT32 reg_still_pn_th                  :8;	//7:0	//FMD, threshold for still frame using pn_cnt (upper)
	UINT32 reg_fmd_ratio_th                 :8;	//15:8	//FMD, ratio of pc_cnt and nc_cnt (upper)
	UINT32 reg_fmd_max_th                   :8;	//23:16	//FMD, max threshold for bigger value (pc_cnt/nc_cnt) (upper)
	UINT32 reg_fmd_min_th                   :8;	//31:24	//FMD, min threshold for bigger value (pc_cnt/nc_cnt) (upper)
	};
}PE_E60_ND0_IPC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E234 RW
	UINT32 cr_tava_chroma_mul               :8;	//7:0	//
	UINT32 resvd                            :4;
	UINT32 cr_hmc_alpha_th                  :8;	//19:12	//
	UINT32 cr_hmc_debug_mode                :1;	//20 //
	UINT32 cr_hmc_debug_gain                :6;	//26:21	//
	UINT32 cr_hmc_debug_dir                 :5;	//31:27	//
	};
}PE_E60_ND0_IPC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E238 RW
	UINT32 reg_lockcnt_en                   :1;	//0 //FMD, Lockcnt enable (upper)
	UINT32 reserved                         :1;	//1 //
	UINT32 reg_lock_speed                   :6;	//7:2	//FMD, Lockcnt increasing step (upper)
	UINT32 reg_lockcnt_th                   :8;	//15:8	//FMD, Lockcnt threshold (upper)
	UINT32 reg_same_th                      :8;	//23:16	//FMD, threshold for same using pc_nc_same_cnt (upper)
	UINT32 reg_still_frame_limit            :8;	//31:24	//FMD, threshold for still (upper)
	};
}PE_E60_ND0_IPC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E23C RW
	UINT32 reg_3_2_detect_en                :1;	//0 //FMD, 3:2 detection mode enable (combinate with fmd decision result)(upper)
	UINT32 reg_3_2_detect_only              :1;	//1 //FMD, 3:2 detection mode enable (discard fmd decision result)(upper)
	UINT32 reg_3_2_lockcnt_255_en           :1;	//2 //FMD, lockcnt force increase enable when 3:2 detected(upper)
	UINT32 reg_3_2_pndiff_disable           :1;	//3 //FMD, 3:2 detection mode pndiff disable (upper)
	UINT32 reg_hd_mode                      :1;	//4 //Make Tearing Counts to 1/4 of SD (upper)
	UINT32 resvd                            :3;
	UINT32 reg_3_2_pndiff_th                :8;	//15:8	//FMD, 3:2 detection mode pndiff th (upper)
	UINT32 reg_3_2_pn_ratio_max_th          :8;	//23:16	//FMD, max threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper)
	UINT32 reg_3_2_pn_ratio_min_th          :8;	//31:24	//FMD, min threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper
	};
}PE_E60_ND0_IPC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E240 RW
	UINT32 reg_still_pn_th2                 :8;	//7:0	//FMD, threshold for pndiff_cnt (upper)
	UINT32 reg_still_prev_ratio             :8;	//15:8	//FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper)
	UINT32 reg_lock_reducer                 :8;	//23:16	//FMD, Lockcnt decreasing step (upper)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//31 //FMD, badedit protect (upper)
	};
}PE_E60_ND0_IPC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E244 RW
	UINT32 cr_inv_resolution                :2;	//1:0	//
	UINT32 cr_field_manual_mode             :2;	//3:2	//
	UINT32 cr_field_inverse                 :1;	//4 //
	UINT32 resvd                            :19;
	UINT32 cr_tearing_a_th                  :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E248 RW
	UINT32 cr_ud_gain                       :8;	//7:0	//| U - D | to 2D confidence (s7)
	UINT32 cr_lr_gain                       :8;	//15:8	//| L - R | to 2D confidence (s7)
	UINT32 cr_h_grad_gain                   :8;	//23:16	//Horizontal Gradient to 2D confidence (s7)
	UINT32 cr_v_grad_gain                   :8;	//31:24	//Vertical Gradient to 2D confidence (s7)
	};
}PE_E60_ND0_IPC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E24C RW
	UINT32 reg_errs_gain                    :8;	//7:0	//
	UINT32 reg_confidence_gain              :8;	//15:8	//
	UINT32 reg_2d_offset                    :8;	//23:16	//
	UINT32 reg_flicker_gain                 :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E250 RO
	UINT32 r_pc_v_count                     :16;	//15:0	//FMD, vertical tearing count of pc (upper)
	UINT32 r_nc_v_count                     :16;	//31:16	//FMD, vertical tearing count of nc (upper)
	};
}PE_E60_ND0_IPC_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E254 RO
	UINT32 r_pc_nc_same                     :16;	//15:0	//FMD, same count between pc and nc (upper)
	UINT32 r_pn_v_count                     :16;	//31:16	//FMD, vertical tearing count of pn (upper)
	};
}PE_E60_ND0_IPC_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E258 RO
	UINT32 reserved                         :6;	//5:0	//
	UINT32 r_fmd_32_min_th_flag_u           :1;	//6 //FMD, 3:2 detector min_th flag(upper)
	UINT32 r_fmd_32_max_th_flag_u           :1;	//7 //FMD, 3:2 detector max_th flag(upper)
	UINT32 r_fmd_still_limit_flag_u         :1;	//8 //FMD, still_limit flag(upper)
	UINT32 r_fmd_still_pn_th2_flag_u        :1;	//9 //FMD, still_pn_th2 flag(upper)
	UINT32 r_fmd_still_pn_th_flag_u         :1;	//10 //FMD, still_pn_th flag(upper)
	UINT32 r_fmd_still_prev_ratio_flag_u    :1;	//11 //FMD, still_prev_ratio flag(upper)
	UINT32 r_fmd_bigger_flag_u              :1;	//12 //FMD, bigger flag(upper)
	UINT32 r_fmd_smaller_flag_u             :1;	//13 //FMD, smaller flag(upper)
	UINT32 r_fmd_3_2_fmd_comb_mode_u        :2;	//15:14	//FMD, comb_flag of 3_2 mode (upper)
	UINT32 r_pn_diff_count                  :16;	//31:16	//FMD, pndiff count (upper)
	};
}PE_E60_ND0_IPC_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E25C RO
	UINT32 same_ng_flag_d                   :1;	//0 //FMD, same condition but comb_flag is not NOTT(under)
	UINT32 too_small_flag_d                 :1;	//1 //FMD, meet toosmall condition (under)
	UINT32 r_fmd_still_flag_d               :1;	//2 //FMD, 1 : detect still (under)
	UINT32 r_fmd_possibility_flag_d         :1;	//3 //FMD, possibility flag of 3_2 mode(under)
	UINT32 base_pn_ratio_flag_d             :1;	//4 //FMD, meet reg_fmd_ratio_th condition (under)
	UINT32 r_32_detected_flag_d             :1;	//5 //FMD, 3:2 detect flag (under)
	UINT32 r_fmd_comb_mode_d                :2;	//7:6	//FMD, COMB_MODE of FMD Decision (under)
	UINT32 r_fmd_lock_count_d               :8;	//15:8	//FMD, LockCnt (under)
	UINT32 same_ng_flag_u                   :1;	//16 //FMD, same condition but comb_flag is not NOTT(upper)
	UINT32 too_small_flag_u                 :1;	//17 //FMD, meet toosmall condition (upper)
	UINT32 r_fmd_still_flag_u               :1;	//18 //FMD, 1 : detect still (upper)
	UINT32 r_fmd_possibility_flag_u         :1;	//19 //FMD, possibility flag of 3_2 mode(upper)
	UINT32 base_pn_ratio_flag_u             :1;	//20 //FMD, meet reg_fmd_ratio_th condition (upper)
	UINT32 r_32_uetected_flag_u             :1;	//21 //FMD, 3:2 detect flag (upper)
	UINT32 r_fmd_comb_mode_u                :2;	//23:22	//FMD, COMB_MODE of FMD Decision (upper)
	UINT32 r_fmd_lock_count_u               :8;	//31:24	//FMD, LockCnt (upper)
	};
}PE_E60_ND0_IPC_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E260 RW
	UINT32 resvd0                           :1;
	UINT32 cl_filter_enable                 :1;	//1 //CL filter enable
	UINT32 clc_detection_enable             :1;	//2 //CL/CC detection enable
	UINT32 resvd1                           :1;
	UINT32 motion_window                    :2;	//5:4	//motion window	0 := 5x3	1 = 9x3	2 = 11x3	3 = 15x3
	UINT32 cl_pattern_dist                  :2;	//7:6	//CL pattern detection distance	0 := 2 (for SD, 480i/p)	1 = 4	2 = 5	3 = 6 (for HD, 1080i/p)
	UINT32 resvd2                           :4;
	UINT32 cl_ab_ratio                      :4;	//15:12	//CL motion a and b ratio(u2.2) : cl_ab_ratio * motion a < motion b
	UINT32 cl_y_hdistance                   :2;	//17:16	//CL horizontal distance for Y
	UINT32 cl_c_hdistance                   :2;	//19:18	//CL horizontal distance for C
	UINT32 cl_y_protect_en                  :1;	//20 //CL: Y level protection enable
	UINT32 resvd3                           :7;
	UINT32 cl_motion_a_filter               :1;	//28 //Filtering for motion a value for cl
	UINT32 cl_motion_b_filter               :1;	//29 //Filtering for motion b value for cl
	UINT32 cl_motion_a_mode                 :1;	//30 //Motion A mode '0' = NTSC/ '1' = PAL
	UINT32 resvd4                           :1;
	};
}PE_E60_ND0_CLC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E264 RW
	UINT32 cl_motion_a_th                   :8;	//7:0	//CL motion a threshold, motion a is calculated between in-phase frame
	UINT32 cl_motion_b_th                   :8;	//15:8	//CL motion b threshold, motion b is calculated between out-of-phase phase frame
	UINT32 cl_y_protect_th0                 :8;	//23:16	//CL Y protect threshold 0
	UINT32 cl_y_protect_th1                 :8;	//31:24	//CL Y protect threshold 1
	};
}PE_E60_ND0_CLC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E268 RW
	UINT32 cl_y_bound_th                    :7;	//6:0	//CL y boundary threshold
	UINT32 cl_c_bound_use_4line             :1;	//7 //0: use chroma 3 line	1: use chroma 4 line
	UINT32 cl_c_bound_th                    :7;	//14:8	//CL c boundary threshold
	UINT32 cl_c_bound_type                  :1;	//15 //CL c boundary type in calculation of c boundary	0 := Sum of h and v difference	1  = 2*Max of  h and v difference
	UINT32 cl_y_bound_width_chroma          :2;	//17:16	//CL y difference combination  with chroma for boundary detection	'00 = y only	'01 := Max(y,c)	'10 = y+c	'11 = y+c/2
	UINT32 cl_y_bound_ignore_cc             :1;	//18 //CL y boundary without considering CC(current frame)
	UINT32 cl_y_bound_ignore_p2             :1;	//19 //CL y boundary without considering P2(2 frame earlier)
	UINT32 cl_y_bound_ignore_p4             :1;	//20 //CL y boundary without considering P4(4 frame earlier)
	UINT32 reg_bin3x1_flt_en                :1;	//21 //CL binary filter for variance protection flag
	UINT32 resvd                            :2;
	UINT32 reg_bin5x1_flt_en                :1;	//24 //CL binary filter for variance protection flag
	UINT32 reg_bin5x1_flt_th                :3;	//27:25	//5x1 binary filter threshold
	UINT32 reg_vm_original_mode             :1;	//28 //variance measure original line select	'0' : CC only	'1' : MAX(P2CCN2)
	UINT32 reg_vm_other_mode                :1;	//29 //variance measure other field line select	'0' : vm original line only	'1' : MAX(vm_ori, P1N1)
	UINT32 cl_motionp2n2_th_pal_high        :2;	//31:30	//CL_MotionP2N2_Th_PAL(9:8) : high bit
	};
}PE_E60_ND0_CLC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E26C RW
	UINT32 cl_sat_min                       :8;	//7:0	//CL saturation min value
	UINT32 resvd                            :2;
	UINT32 cl_var_measure_th1               :10;	//19:10	//CL variance measure th
	UINT32 cl_var_measure_th2               :10;	//29:20	//CL motion P2N2 th for variance measure
	UINT32 cl_pt_enable                     :2;	//31:30	//CL protection enable	(31): variance protection enable	(30): tearing protection enable
	};
}PE_E60_ND0_CLC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E270 RW
	UINT32 cl_tearing_pt_th1                :12;	//11:0	//CL Tearing protection threshold(no CL filtering)
	UINT32 cl_motionp2n2_th_pal_low         :8;	//19:12	//CL_MotionP2N2_Th_PAL(7:0) : low bit
	UINT32 cl_frame_min                     :12;	//31:20	//CL min detection pixel count per frame
	};
}PE_E60_ND0_CLC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E274 RW
	UINT32 cl_data_line_switching_sel       :1;	//0 //0 = switching data line at [each line]	1 = switching data line at [each field]
	UINT32 resvd0                           :7;
	UINT32 clc_bin_flt_th                   :3;	//10:8	//CL_pt_map binary filtering(5x1) th
	UINT32 resvd1                           :4;
	UINT32 clc_bin_flt_en                   :1;	//15 //CL_pt_map binary filtering(1x3 -> 5x1) enable
	UINT32 clc_dbg_show_mask                :13;	//28:16	//CLC Dbg Show Mask
	UINT32 resvd2                           :3;
	};
}PE_E60_ND0_CLC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E278 RW
	UINT32 cc_c_filter_gain                 :8;	//7:0	//CC ChromaFilter Gain
	UINT32 cc_y_filter_when_cc_detected     :1;	//8 //CC YFilter When CC Detected	0 = IPC(deinterlacer) output	1 = Average(n,n-2), n means frame index.
	UINT32 resvd0                           :1;
	UINT32 cl_cc_original_en                :1;	//10 //
	UINT32 clc_force_non_fmd                :1;	//11 //1: force FMD off when CL_pt_map = '1'	(if CL_pt_map = '0' FMD on)
	UINT32 cl_c_filter_when_cl_detected     :1;	//12 //0': IPC result(normal)	'1': Chroma temporal filtering((CC+N2)/2) by CL_pt_map
	UINT32 cl_y_filter_when_cl_detected     :1;	//13 //0': IPC result(normal)	'1': Luminance temporal filtering by CL_pt_map	should be OFF when 4K input
	UINT32 clc_filter_mode                  :2;	//15:14	//CLC filter select	11:(P2 + 2*CC + N2 )/4	10:(P2 + CC)/2	01:(P2 + N2)/2	00:(CC + N2)/2
	UINT32 resvd1                           :8;
	UINT32 cl_cc_protection_th              :8;	//31:24	//
	};
}PE_E60_ND0_CLC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E27C RO
	UINT32 resvd                            :16;
	UINT32 cl_detection_count               :16;	//31:16	//CL detection pixel count
	};
}PE_E60_ND0_CLC_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E280 RW
	UINT32 tava_v_diff_y0                   :8;	//7:0	//
	UINT32 tava_v_diff_x0                   :8;	//15:8	//
	UINT32 tava_v_diff_y1                   :8;	//23:16	//
	UINT32 tava_v_diff_x1                   :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E284 RW
	UINT32 reg_div_en                       :1;	//0 //FMD, div mode enable
	UINT32 cr_bound_exp_en                  :1;	//1 //FMD, cr bound enable
	UINT32 resvd0                           :2;
	UINT32 cr_sub_main_sel                  :1;	//4 //(중요) FMD, 0:main path, 1:sub path
	UINT32 resvd1                           :11;
	UINT32 reg_manual_en                    :1;	//16 //FMD, manual mode enable
	UINT32 resvd2                           :3;
	UINT32 reg_manual_mode2                 :2;	//21:20	//FMD, manual mode COMB_MODE (under)
	UINT32 reg_manual_mode1                 :2;	//23:22	//FMD, manual mode COMB_MODE (upper)
	UINT32 reg_div_position                 :8;	//31:24	//FMD, div mode upper/under boundary position
	};
}PE_E60_ND0_IPC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E288 RW
	UINT32 reg_still_pn_th                  :8;	//7:0	//FMD, threshold for still frame using pn_cnt (under)
	UINT32 reg_fmd_ratio_th                 :8;	//15:8	//FMD, ratio of pc_cnt and nc_cnt (under)
	UINT32 reg_fmd_max_th                   :8;	//23:16	//FMD, max threshold for bigger value (pc_cnt/nc_cnt) (under)
	UINT32 reg_fmd_min_th                   :8;	//31:24	//FMD, min threshold for bigger value (pc_cnt/nc_cnt) (under)
	};
}PE_E60_ND0_IPC_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E28C RW
	UINT32 reg_lockcnt_en                   :1;	//0 //FMD, Lockcnt enable (under)
	UINT32 reserved                         :1;	//1 //
	UINT32 reg_lock_speed                   :6;	//7:2	//FMD, Lockcnt increasing step (under)
	UINT32 reg_lockcnt_th                   :8;	//15:8	//FMD, Lockcnt threshold (under)
	UINT32 reg_same_th                      :8;	//23:16	//FMD, threshold for same using pc_nc_same_cnt (under)
	UINT32 reg_still_frame_limit            :8;	//31:24	//FMD, threshold for still (under)
	};
}PE_E60_ND0_IPC_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E290 RW
	UINT32 reg_3_2_detect_en                :1;	//0 //FMD, 3:2 detection mode enable (combinate with fmd decision result) (under)
	UINT32 reg_3_2_detect_only              :1;	//1 //FMD, 3:2 detection mode enable (discard fmd decision result) (under)
	UINT32 reg_3_2_lockcnt_255_en           :1;	//2 //FMD, lockcnt force increase enable when 3:2 detected(under)
	UINT32 reg_3_2_pndiff_disable           :1;	//3 //FMD, 3:2 detection mode pndiff disable (under)
	UINT32 reg_hd_mode                      :1;	//4 //Make Tearing Counts to 1/4 of SD (under)
	UINT32 resvd                            :3;
	UINT32 reg_3_2_pndiff_th                :8;	//15:8	//FMD, 3:2 detection mode pndiff th (under)
	UINT32 reg_3_2_pn_ratio_max_th          :8;	//23:16	//FMD, max threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	UINT32 reg_3_2_pn_ratio_min_th          :8;	//31:24	//FMD, min threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	};
}PE_E60_ND0_IPC_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E294 RW
	UINT32 reg_still_pn_th2                 :8;	//7:0	//FMD, threshold for pndiff_cnt (under)
	UINT32 reg_still_prev_ratio             :8;	//15:8	//FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	UINT32 reg_lock_reducer                 :8;	//23:16	//FMD, Lockcnt decreasing step (under)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//31 //FMD, badedit protect (under)
	};
}PE_E60_ND0_IPC_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E298 RW
	UINT32 reg_toosmall_en                  :1;	//0 //FMD, toosmall mode enable (under)
	UINT32 reg_toosmall_min                 :7;	//7:1	//FMD, min value of toosmall condition (under)
	UINT32 reg_toosmall_max                 :8;	//15:8	//FMD, max value of toosmall condition (under)
	UINT32 reg_pndiff_disable               :1;	//16 //FMD, pndiff mode off (under)
	UINT32 resvd                            :15;
	};
}PE_E60_ND0_IPC_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E29C RW
	UINT32 reg_fend_position                :11;	//10:0	//
	UINT32 resvd0                           :1;
	UINT32 cr_sc_length                     :3;	//14:12	//
	UINT32 resvd1                           :11;
	UINT32 cr_vmc_dir                       :3;	//28:26	//Force VMC
	UINT32 resvd2                           :2;
	UINT32 cr_vmc_en                        :1;	//31 //Force VMC
	};
}PE_E60_ND0_IPC_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2A0 RW
	UINT32 reg_yy_diff_gain                 :4;	//3:0	//Luma Motion Gain
	UINT32 reg_hv_add_gain                  :4;	//7:4	//HV Separable Motion Gain
	UINT32 reg_v_motion_gain                :4;	//11:8	//V Motion Gain
	UINT32 reg_h_motion_gain                :4;	//15:12	//H Motion Gain
	UINT32 reg_cc_diff_gain                 :4;	//19:16	//Chroma Motion Gain
	UINT32 resvd                            :12;
	};
}PE_E60_ND0_IPC_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2A4 RW
	UINT32 n1b_motion_gain_y0               :8;	//7:0	//
	UINT32 n1b_motion_gain_x0               :8;	//15:8	//
	UINT32 n1b_motion_gain_y1               :8;	//23:16	//
	UINT32 n1b_motion_gain_x1               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2A8 RW
	UINT32 n1b_variance_gain_y0             :8;	//7:0	//
	UINT32 n1b_variance_gain_x0             :8;	//15:8	//
	UINT32 n1b_variance_gain_y1             :8;	//23:16	//
	UINT32 n1b_variance_gain_x1             :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2AC RW
	UINT32 reg_hmc_use_tnr_mv               :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 reg_cr_hmc_y_th                  :4;	//11:8	//
	UINT32 resvd1                           :4;
	UINT32 max_penalty                      :8;	//23:16	//
	UINT32 min_penalty                      :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2B0 RW
	UINT32 reg_min_diff_th                  :8;	//7:0	//
	UINT32 reg_edi_va_blend_mul             :10;	//17:8	//
	UINT32 resvd0                           :2;
	UINT32 reg_edi_va_protect_mul           :10;	//29:20	//
	UINT32 resvd1                           :1;
	UINT32 reg_m16_edi_va_blend_en          :1;	//31 //
	};
}PE_E60_ND0_IPC_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2B4 RW
	UINT32 reg_max_va_diff_th               :8;	//7:0	//
	UINT32 reg_max_edi_diff_th              :8;	//15:8	//
	UINT32 reg_edi_va_protect_min           :8;	//23:16	//
	UINT32 reg_edi_va_blend_min             :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2B8 RW
	UINT32 reg_2d_top_lut_y0                :8;	//7:0	//
	UINT32 reg_2d_top_lut_x0                :8;	//15:8	//
	UINT32 reg_2d_top_lut_y1                :8;	//23:16	//
	UINT32 reg_2d_top_lut_x1                :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2BC RW
	UINT32 cr_hmc_enable_1                  :1;	//0 //
	UINT32 cr_lock_th_1                     :7;	//7:1	//
	UINT32 cr_lr_ratio_th_1                 :8;	//15:8	//
	UINT32 cr_hmc_expend_1                  :3;	//18:16	//
	UINT32 cr_lr_ratio_check_en_1           :1;	//19 //
	UINT32 cr_robustness_1                  :4;	//23:20	//
	UINT32 cr_center_weight_1               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2C0 RW
	UINT32 cr_hmc_enable_2                  :1;	//0 //
	UINT32 cr_lock_th_2                     :7;	//7:1	//
	UINT32 cr_lr_ratio_th_2                 :8;	//15:8	//
	UINT32 cr_hmc_expend_2                  :3;	//18:16	//
	UINT32 cr_lr_ratio_check_en_2           :1;	//19 //
	UINT32 cr_robustness_2                  :4;	//23:20	//
	UINT32 cr_center_weight_2               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2C4 RW
	UINT32 line_cnt_th_0                    :12;	//11:0	//
	UINT32 line_cnt_th_1                    :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_ND0_IPC_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2C8 RW
	UINT32 cr_n1b_limit                     :9;	//8:0	//
	UINT32 resvd0                           :3;
	UINT32 cr_n1b_resolution                :3;	//14:12	//
	UINT32 resvd1                           :9;
	UINT32 cr_pre_sc_th                     :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2CC RW
	UINT32 cr_hmc_text_rgn_y0               :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x0               :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_ND0_IPC_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2D0 RW
	UINT32 cr_hmc_text_rgn_y1               :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x1               :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_ND0_IPC_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2D4 RW
	UINT32 cr_hmc_text_rgn_en               :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 cr_hmc_text_rgn_sad_max          :8;	//15:8	//
	UINT32 cr_hmc_text_rgn_sad_min          :8;	//23:16	//
	UINT32 resvd1                           :8;
	};
}PE_E60_ND0_IPC_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2E0 RW
	UINT32 mmd_vtap_yy                      :2;	//1:0	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd0                           :2;
	UINT32 mmd_htap_yy                      :2;	//5:4	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd1                           :2;
	UINT32 mmd_vtap_cc                      :2;	//9:8	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd2                           :2;
	UINT32 mmd_htap_cc                      :2;	//13:12	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd3                           :2;
	UINT32 reg_chroma_mmd_en                :1;	//16 //0 := off	1 := on
	UINT32 resvd4                           :15;
	};
}PE_E60_ND0_MMD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2F0 RW
	UINT32 reg_cubic_coef0                  :8;	//7:0	//
	UINT32 reg_cubic_coef1                  :8;	//15:8	//
	UINT32 reg_va_blending_ctrl_lv1         :3;	//18:16	//
	UINT32 resvd0                           :1;
	UINT32 reg_va_blending_ctrl_lv2         :3;	//22:20	//
	UINT32 resvd1                           :1;
	UINT32 reg_va_blending_ctrl_lv3         :3;	//26:24	//
	UINT32 resvd2                           :1;
	UINT32 reg_va_blending_ctrl_lv4         :3;	//30:28	//
	UINT32 resvd3                           :1;
	};
}PE_E60_ND0_IPC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2F4 RW
	UINT32 reg_va_cubic                     :1;	//0 //
	UINT32 reg_boundary_window              :1;	//1 //
	UINT32 reg_force_va                     :1;	//2 //
	UINT32 reg_half_pel_va                  :1;	//3 //
	UINT32 reg_dir_med_tap                  :2;	//5:4	//
	UINT32 reg_diff_med_tap                 :2;	//7:6	//
	UINT32 reg_va_blending_ctrl1            :3;	//10:8	//
	UINT32 reg_wide_angle_protection_1      :1;	//11 //
	UINT32 reg_va_blending_ctrl2            :3;	//14:12	//
	UINT32 reg_wide_angle_protection_2      :1;	//15 //
	UINT32 reg_errs_chroma_blend_coef       :8;	//23:16	//
	UINT32 reg_strong_global_th             :6;	//29:24	//
	UINT32 narrow_angle_week                :1;	//30 //
	UINT32 narrow_angle_protection          :1;	//31 //
	};
}PE_E60_ND0_IPC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2F8 RW
	UINT32 cr_vmc_v_diff_max                :8;	//7:0	//
	UINT32 cr_vmc_v_diff_protect_mul        :8;	//15:8	//
	UINT32 es_err_value                     :8;	//23:16	//
	UINT32 et_err_value                     :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E2FC RW
	UINT32 cr_hmc_enable_0                  :1;	//0 //
	UINT32 cr_lock_th_0                     :7;	//7:1	//
	UINT32 cr_lr_ratio_th_0                 :8;	//15:8	//
	UINT32 cr_hmc_expend_0                  :3;	//18:16	//
	UINT32 cr_lr_ratio_check_en_0           :1;	//19 //
	UINT32 cr_robustness_0                  :4;	//23:20	//
	UINT32 cr_center_weight_0               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E300 RW
	UINT32 cr_noise_en                      :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 cr_noise_th                      :8;	//15:8	//
	UINT32 cr_gds_resolution                :2;	//17:16	//
	UINT32 resvd1                           :2;
	UINT32 cr_hmc_h_range                   :12;	//31:20	//
	};
}PE_E60_ND0_IPC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E304 RW
	UINT32 reg_vdiff_en                     :1;	//0 //
	UINT32 resvd                            :7;
	UINT32 reg_vdiff_th                     :8;	//15:8	//
	UINT32 reg_hmc_err_max                  :8;	//23:16	//
	UINT32 reg_hmc_err_min                  :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E308 RW
	UINT32 cr_fmd_check_en                  :1;	//0 //FMD, chroma fmd mode enable
	UINT32 resvd0                           :7;
	UINT32 cr_fmd_ath                       :8;	//15:8	//FMD, A-Th for chroma fmd
	UINT32 resvd1                           :8;
	UINT32 cr_fmd_ratio_th                  :8;	//31:24	//FMD, chroma fmd_ratio
	};
}PE_E60_ND0_IPC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E30C RW
	UINT32 chroma_st_flt_ctrl_x0            :8;	//7:0	//
	UINT32 chroma_st_flt_ctrl_x1            :8;	//15:8	//
	UINT32 luma_st_flt_ctrl_x0              :8;	//23:16	//
	UINT32 luma_st_flt_ctrl_x1              :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E310 RW
	UINT32 reg_hmc_bonus_es_en              :1;	//0 //
	UINT32 reg_hmc_bonus_et_en              :1;	//1 //
	UINT32 resvd                            :6;
	UINT32 reg_hmc_bonus_es                 :8;	//15:8	//
	UINT32 reg_hmc_bonus_th                 :8;	//23:16	//
	UINT32 reg_hmc_bonus_et                 :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E314 RW
	UINT32 hmc_alpha_th                     :8;	//7:0	//
	UINT32 resvd                            :8;
	UINT32 hmc_flt_ctrl_x0                  :8;	//23:16	//
	UINT32 hmc_st_flt_ctrl_x1               :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E318 RW
	UINT32 reg_vmc_motion_th                :8;	//7:0	//VMC motion Th
	UINT32 reg_vmc_debug                    :1;	//8 //VMC 된 Motion을 0으로 세팅
	UINT32 reg_vmc_en                       :1;	//9 //VMC Enable
	UINT32 reg_vmc_still_check              :1;	//10 //P-C non motion 을 VMC motion에 더할것인가?
	UINT32 resvd0                           :1;
	UINT32 reg_vmc_mul                      :2;	//13:12	//VMC*(2^n) vs normal Motion 의 n값
	UINT32 reg_vmc_out_mul                  :2;	//15:14	//교체할 VMC motion에 (2^n)배를 가함.
	UINT32 reg_vmc_protect_th               :8;	//23:16	//기본 motion 이 얼마 이상일때 VMC 를 안하는 Protection 모드
	UINT32 reg_protection_en                :1;	//24 //기본 motion 이 얼마 이상일때 VMC 를 안하는 Protection Th
	UINT32 reg_2filed_check_en              :1;	//25 //
	UINT32 reg_vmc_tnrmotion_dis            :1;	//26 //
	UINT32 resvd1                           :1;
	UINT32 reg_vmc_mm_ratio                 :4;	//31:28	//
	};
}PE_E60_ND0_IPC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E31C RW
	UINT32 reg_toosmall_en                  :1;	//0 //FMD, toosmall mode enable (upper)
	UINT32 reg_toosmall_min                 :7;	//7:1	//FMD, min value of toosmall condition (upper)
	UINT32 reg_toosmall_max                 :8;	//15:8	//FMD, max value of toosmall condition (upper)
	UINT32 reg_pndiff_disable               :1;	//16 //FMD, pndiff mode off (upper)
	UINT32 resvd                            :15;
	};
}PE_E60_ND0_IPC_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E320 RW
	UINT32 tava_errt_y2                     :8;	//7:0	//
	UINT32 tava_errt_x2                     :8;	//15:8	//
	UINT32 tava_errt_y3                     :8;	//23:16	//
	UINT32 tava_errt_x3                     :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E324 RW
	UINT32 tava_errt_y0                     :8;	//7:0	//
	UINT32 tava_errt_x0                     :8;	//15:8	//
	UINT32 tava_errt_y1                     :8;	//23:16	//
	UINT32 tava_errt_x1                     :8;	//31:24	//
	};
}PE_E60_ND0_IPC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E328 RO
	UINT32 r_pc_v_count_d                   :16;	//15:0	//FMD, vertical tearing count of pc (under)
	UINT32 r_nc_v_count_d                   :16;	//31:16	//FMD, vertical tearing count of nc (under)
	};
}PE_E60_ND0_IPC_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E32C RO
	UINT32 r_pc_nc_same_d                   :16;	//15:0	//FMD, same count between pc and nc (under)
	UINT32 r_pn_v_count_d                   :16;	//31:16	//FMD, vertical tearing count of pn (under)
	};
}PE_E60_ND0_IPC_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E330 RO
	UINT32 reserved                         :6;	//5:0	//
	UINT32 r_fmd_32_min_th_flag_d           :1;	//6 //FMD, 3:2 detector min_th flag(under)
	UINT32 r_fmd_32_max_th_flag_d           :1;	//7 //FMD, 3:2 detector max_th flag(under)
	UINT32 r_fmd_still_limit_flag_d         :1;	//8 //FMD, still_limit flag(under)
	UINT32 r_fmd_still_pn_th2_flag_d        :1;	//9 //FMD, still_pn_th2 flag(under)
	UINT32 r_fmd_still_pn_th_flag_d         :1;	//10 //FMD, still_pn_th flag(under)
	UINT32 r_fmd_still_prev_ratio_flag_d    :1;	//11 //FMD, still_prev_ratio flag(under)
	UINT32 r_fmd_bigger_flag_d              :1;	//12 //FMD, bigger flag(under)
	UINT32 r_fmd_smaller_flag_d             :1;	//13 //FMD, smaller flag(under)
	UINT32 r_fmd_3_2_fmd_comb_mode_d        :2;	//15:14	//FMD, comb_flag of 3_2 mode (under)
	UINT32 r_pn_diff_count_d                :16;	//31:16	//FMD, pndiff count (under)
	};
}PE_E60_ND0_IPC_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E334 RO
	UINT32 r_inv_inversed_cnt               :16;	//15:0	//
	UINT32 r_inv_original_cnt               :16;	//31:16	//
	};
}PE_E60_ND0_IPC_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E338 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_IPC_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E33C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_IPC_STATUS_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E340 RW
	UINT32 reg_show_scale                   :3;	//2:0	//
	UINT32 reg_bbd_show                     :1;	//3 //display BBD result
	UINT32 reg_show_bar_1                   :1;	//4 //
	UINT32 reg_show_bar_2                   :1;	//5 //
	UINT32 reg_show_bar_3                   :1;	//6 //
	UINT32 reg_bar1_data_mux                :2;	//8:7	//bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//10:9	//
	UINT32 reg_bar3_data_mux                :2;	//12:11	//
	UINT32 reg_hist0_data_mux               :4;	//16:13	//bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//20:17	//
	UINT32 reg_hist2_data_mux               :4;	//24:21	//
	UINT32 reg_hist0_win_sel                :2;	//26:25	//hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//28:27	//hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//30:29	//hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 hist_rd_en                       :1;	//31 //histogram read mode enable
	};
}PE_E60_ND0_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E344 RW
	UINT32 wina_x0                          :12;	//11:0	//winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//27:16	//winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E348 RW
	UINT32 wina_x1                          :12;	//11:0	//winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//27:16	//winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//30 //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//31 //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_E60_ND0_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E34C RW
	UINT32 winb_x0                          :12;	//11:0	//winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//27:16	//winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E350 RW
	UINT32 winb_x1                          :12;	//11:0	//winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//27:16	//winB_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E354 RW
	UINT32 winc_x0                          :12;	//11:0	//winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//27:16	//winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E358 RW
	UINT32 winc_x1                          :12;	//11:0	//winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//27:16	//winC_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E35C RW
	UINT32 reg_force_y                      :10;	//9:0	//force Y value
	UINT32 reg_force_y_max_th               :10;	//19:10	//forcing range max th
	UINT32 reg_force_y_min_th               :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//31 //force Y enable
	};
}PE_E60_ND0_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E360 RW
	UINT32 reg_force_cb                     :10;	//9:0	//force Cb value
	UINT32 reg_force_cb_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//31 //force Cb enable(with Y range)
	};
}PE_E60_ND0_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E364 RW
	UINT32 reg_force_cr                     :10;	//9:0	//force Cr value
	UINT32 reg_force_cr_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//31 //force Cr enable(with Y range)
	};
}PE_E60_ND0_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E368 RO
	UINT32 hist_pixel_count                 :22;	//21:0	//histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_E60_ND0_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E36C RW
	UINT32 cl_lcount_enable                 :1;	//0 //1: use CL Lock count(Temporal filter)	should be OFF when 4K input
	UINT32 cl_lcnt_mode                     :2;	//2:1	//"00":VA 2 lcnt, "01":VA 4 lcnt, "10"/"11":VA 6 lcnt
	UINT32 cl_scene_change_enable           :1;	//3 //1:reset CL Lock count when Scene changed
	UINT32 cl_scene_change_mode             :1;	//4 //0:Auto(from TNR scene change flag), 1:Manual(from Host)
	UINT32 cl_scene_change_manual           :1;	//5 //1:reset CL Lock count manually
	UINT32 cl_lcnt_th                       :4;	//9:6	//Temporal filtering threshold
	UINT32 cl_plus_lcount                   :3;	//12:10	//plus count when CL final flag = '1'
	UINT32 cl_minus_lcount                  :2;	//14:13	//minus count when CL final flag = '0'
	UINT32 cl_scene_change_protect          :1;	//15 //1': remain current CL flag when reset Lock count
	UINT32 resvd                            :4;
	UINT32 cl_tearing_pt_th2                :12;	//31:20	//CL Original Tearing protection threshold(CL filtering)
	};
}PE_E60_ND0_CLC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E370 RW
	UINT32 reg_bbd_en                       :1;	//0 //enable
	UINT32 reg_hys_mode                     :5;	//5:1	//frame count for temporal smoothing of BBD result
	UINT32 reg_op_mode                      :1;	//6 //BBD operation mode 0 : auto detection, 1 : manual setting
	UINT32 resvd                            :1;
	UINT32 reg_cnt_th                       :8;	//15:8	//continuous Black pixel's count threshold for recognizing Black Boundary
	UINT32 reg_diff_th                      :8;	//23:16	//threshold for Black decision
	UINT32 reg_bbd_mux                      :3;	//26:24	//data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
	UINT32 reg_apl_mux                      :3;	//29:27	//data select for APL, 0 : YCbCr, 1 : GBR, 2 : HSV, 3 : YSV, others : YCbCr
	UINT32 reg_apl_win_sel                  :2;	//31:30	//apl window selection 0 : BBD status, 1 : Win_A, 2 : Win_B, 3 : Win_C
	};
}PE_E60_ND0_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E374 RW
	UINT32 x0                               :12;	//11:0	//x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//27:16	//y0
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E378 RW
	UINT32 x1                               :12;	//11:0	//x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//27:16	//y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E37C RO
	UINT32 x0                               :12;	//11:0	//x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//27:16	//y0
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E380 RO
	UINT32 x1                               :12;	//11:0	//x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//27:16	//y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E384 RO
	UINT32 y_g_s_apl                        :10;	//9:0	//data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//19:10	//data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//29:20	//data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_E60_ND0_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E388 RW
	UINT32 reg_s_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//25:16	//threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_E60_ND0_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E38C RW
	UINT32 reg_y_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_ND0_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E390 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	…	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//14:13	//histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//28 //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	// 30
	UINT32 hist_read_done                   :1;	//31 //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_E60_ND0_TPD_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E394 RO
	UINT32 hist_status                      :22;	//21:0	//histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_E60_ND0_TPD_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E398 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 y_offset                         :10;	//13:4	//
	UINT32 resvd1                           :2;
	UINT32 center_position                  :8;	//23:16	//center position for Y gain control
	UINT32 y_gain                           :8;	//31:24	//
	};
}PE_E60_ND0_LVCRTL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E39C RO
	UINT32 hist_pixel_count                 :22;	//21:0	//histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_E60_ND0_TPD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3A0 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3A4 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3A8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3AC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_TNR_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3C0 RW
	UINT32 reg_gmv_rst                      :1;	//0 //
	UINT32 reg_bmv_rst                      :1;	//1 //
	UINT32 reg_me_rst                       :1;	//2 //
	UINT32 reg_mc_rst                       :1;	//3 //
	UINT32 reg_ma_rst                       :1;	//4 //
	UINT32 resvd                            :27;
	};
}PE_E60_ND0_TNR_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3D0 RW
	UINT32 resvd0                           :2;
	UINT32 reg_a_normalize_en               :1;	//2 //
	UINT32 reg_t_normalize_en               :1;	//3 //
	UINT32 reg_t_cut_resolution             :2;	//5:4	//
	UINT32 reg_ne_normalize_en              :1;	//6 //
	UINT32 resvd1                           :9;
	UINT32 reg_cross_th_ne                  :8;	//23:16	//
	UINT32 reg_cross_th                     :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3D4 RW
	UINT32 reg_mul_base_t                   :8;	//7:0	//
	UINT32 reg_mul_base_e                   :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_ND0_TNR_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3D8 RW
	UINT32 reg_a_lut_edge_y0                :8;	//7:0	//
	UINT32 reg_a_lut_edge_x0                :8;	//15:8	//
	UINT32 reg_a_lut_edge_y1                :8;	//23:16	//
	UINT32 reg_a_lut_edge_x1                :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3DC RW
	UINT32 reg_a_lut_detail_y0              :8;	//7:0	//
	UINT32 reg_a_lut_detail_x0              :8;	//15:8	//
	UINT32 reg_a_lut_detail_y1              :8;	//23:16	//
	UINT32 reg_a_lut_detail_x1              :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3E0 RW
	UINT32 reg_t_lut_edge_y0                :8;	//7:0	//
	UINT32 reg_t_lut_edge_x0                :8;	//15:8	//
	UINT32 reg_t_lut_edge_y1                :8;	//23:16	//
	UINT32 reg_t_lut_edge_x1                :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3E4 RW
	UINT32 reg_t_lut_detail_y0              :8;	//7:0	//
	UINT32 reg_t_lut_detail_x0              :8;	//15:8	//
	UINT32 reg_t_lut_detail_y1              :8;	//23:16	//
	UINT32 reg_t_lut_detail_x1              :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3E8 RW
	UINT32 reg_edge_minmax_y0               :8;	//7:0	//
	UINT32 reg_edge_minmax_x0               :8;	//15:8	//
	UINT32 reg_edge_minmax_y1               :8;	//23:16	//
	UINT32 reg_edge_minmax_x1               :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3EC RW
	UINT32 reg_detail_minmax_y0             :8;	//7:0	//
	UINT32 reg_detail_minmax_x0             :8;	//15:8	//
	UINT32 reg_detail_minmax_y1             :8;	//23:16	//
	UINT32 reg_detail_minmax_x1             :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3F0 RW
	UINT32 reg_sel_ne_type                  :2;	//1:0	//0:(Y - TNR_Y), 1:(Y - SNR_Y), 2:(C - SNR_C)
	UINT32 reg_sel_re_type                  :1;	//2 //0:(still region), 1:(flat region)
	UINT32 resvd0                           :1;
	UINT32 reg_sel_at_mode                  :2;	//5:4	//0:(A), 1:(T), 2:(max(A,T)), 3:(A,T separate)
	UINT32 resvd1                           :2;
	UINT32 reg_hist_xscale                  :3;	//10:8	//histogram x-axi resolution ( 0: 0,1,2… , 1: 0,2,4…)
	UINT32 resvd2                           :1;
	UINT32 reg_hist_yscale                  :2;	//13:12	//histogram cut resolution
	UINT32 resvd3                           :2;
	UINT32 reg_th_atmap                     :8;	//23:16	//at_map threshold ( flat rgion valid threshold )
	UINT32 reg_th_motion                    :8;	//31:24	//motion threshiold ( still region valid threshold )
	};
}PE_E60_ND0_TNR_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3F4
	UINT32 nd0_hue_bin_6                      :8;  //  7: 0
	UINT32 nd0_hue_bin_7                      :8;  // 15: 8
	UINT32 nd0_hue_bin_8                      :8;  // 23:16
	UINT32 nd0_hue_bin_9                      :8;  // 31:24
	};
} PE_E60_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3F8
	UINT32 nd1_hue_bin_6                      :8;  //  7: 0
	UINT32 nd1_hue_bin_7                      :8;  // 15: 8
	UINT32 nd1_hue_bin_8                      :8;  // 23:16
	UINT32 nd1_hue_bin_9                      :8;  // 31:24
	};
} PE_E60_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E3FC
	UINT32 tdata0                           :32;
	};
} PE_E60_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E400 RO
	UINT32 valid_cnt                        :16;	//15:0	//# of valid region
	UINT32 resvd                            :16;
	};
}PE_E60_ND0_TNR_NE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E404 RO
	UINT32 hist_1                           :16;	//15:0	//hist[1]
	UINT32 hist_0                           :16;	//31:16	//hist[0]
	};
}PE_E60_ND0_TNR_NE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E408 RO
	UINT32 hist_3                           :16;	//15:0	//hist[3]
	UINT32 hist_2                           :16;	//31:16	//hist[2]
	};
}PE_E60_ND0_TNR_NE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E40C RO
	UINT32 hist_5                           :16;	//15:0	//hist[5]
	UINT32 hist_4                           :16;	//31:16	//hist[4]
	};
}PE_E60_ND0_TNR_NE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E410 RO
	UINT32 hist_7                           :16;	//15:0	//hist[7]
	UINT32 hist_6                           :16;	//31:16	//hist[6]
	};
}PE_E60_ND0_TNR_NE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E414 RO
	UINT32 hist_9                           :16;	//15:0	//hist[9]
	UINT32 hist_8                           :16;	//31:16	//hist[8]
	};
}PE_E60_ND0_TNR_NE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E418 RO
	UINT32 hist_11                          :16;	//15:0	//hist[11]
	UINT32 hist_10                          :16;	//31:16	//hist[10]
	};
}PE_E60_ND0_TNR_NE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E41C RO
	UINT32 hist_13                          :16;	//15:0	//hist[13]
	UINT32 hist_12                          :16;	//31:16	//hist[12]
	};
}PE_E60_ND0_TNR_NE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E420 RO
	UINT32 hist_15                          :16;	//15:0	//hist[15]
	UINT32 hist_14                          :16;	//31:16	//hist[14]
	};
}PE_E60_ND0_TNR_NE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E440 RW
	UINT32 reg_show_scale                   :3;	//2:0	//
	UINT32 reg_bbd_show                     :1;	//3 //display BBD result
	UINT32 reg_show_bar_1                   :1;	//4 //
	UINT32 reg_show_bar_2                   :1;	//5 //
	UINT32 reg_show_bar_3                   :1;	//6 //
	UINT32 reg_bar1_data_mux                :2;	//8:7	//bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//10:9	//
	UINT32 reg_bar3_data_mux                :2;	//12:11	//
	UINT32 reg_hist0_data_mux               :4;	//16:13	//bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//20:17	//
	UINT32 reg_hist2_data_mux               :4;	//24:21	//
	UINT32 reg_hist0_win_sel                :2;	//26:25	//hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//28:27	//hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//30:29	//hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 hist_rd_en                       :1;	//31 //histogram read mode enable
	};
}PE_E60_ND0_HIST2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E444 RW
	UINT32 wina_x0                          :12;	//11:0	//winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//27:16	//winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_HIST2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E448 RW
	UINT32 wina_x1                          :12;	//11:0	//winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//27:16	//winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//30 //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//31 //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_E60_ND0_HIST2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E44C RW
	UINT32 winb_x0                          :12;	//11:0	//winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//27:16	//winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_HIST2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E450 RW
	UINT32 winb_x1                          :12;	//11:0	//winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//27:16	//winB_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_HIST2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E454 RW
	UINT32 winc_x0                          :12;	//11:0	//winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//27:16	//winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND0_HIST2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E458 RW
	UINT32 winc_x1                          :12;	//11:0	//winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//27:16	//winC_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND0_HIST2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E45C RW
	UINT32 reg_force_y                      :10;	//9:0	//force Y value
	UINT32 reg_force_y_max_th               :10;	//19:10	//forcing range max th
	UINT32 reg_force_y_min_th               :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//31 //force Y enable
	};
}PE_E60_ND0_HIST2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E460 RW
	UINT32 reg_force_cb                     :10;	//9:0	//force Cb value
	UINT32 reg_force_cb_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//31 //force Cb enable(with Y range)
	};
}PE_E60_ND0_HIST2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E464 RW
	UINT32 reg_force_cr                     :10;	//9:0	//force Cr value
	UINT32 reg_force_cr_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//31 //force Cr enable(with Y range)
	};
}PE_E60_ND0_HIST2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E468 RW
	UINT32 reg_s_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//25:16	//threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_E60_ND0_HIST2_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E46C RW
	UINT32 reg_y_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_ND0_HIST2_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E470 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	…	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//14:13	//histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//28 //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	//30 //histogram read mode enable
	UINT32 hist_read_done                   :1;	//31 //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_E60_ND0_HIST2_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E474 RO
	UINT32 hist_status                      :22;	//21:0	//histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_E60_ND0_HIST2_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E478 RO
	UINT32 hist_pixel_count                 :22;	//21:0	//histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_E60_ND0_HIST2_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E480 RW
	UINT32 chroma_st_flt_ctrl_x0              : 8 ;  //  7: 0     
	UINT32 chroma_st_flt_ctrl_x1              : 8 ;  // 15: 8     
	UINT32 luma_st_flt_ctrl_x0                : 8 ;  // 23:16     
	UINT32 luma_st_flt_ctrl_x1                : 8 ;  // 31:24     
	};
}PE_E60_ND0_ND_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E484 RW
	UINT32 motion_x_tearing_gain              : 8 ;  //  7: 0     
	UINT32 motion_gain                        : 8 ;  // 15: 8     
	};
}PE_E60_ND0_ND_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E488 RW
	UINT32 cr_luma_mode                       :2 ;	// 1:0
	UINT32 reserved01                         :1 ;	// reserved
	UINT32 cr_n1_cc_blend_en                  :1 ;	// 3 
	UINT32 cr_chroma_mode                     :2 ;	// 5:4
	UINT32 cr_integer_edi                     :1 ;	// 6 
	UINT32 cr_chroma_edi                      :1 ;	// 7 
	UINT32 cr_st_2d_v_flt_range2              :4 ;	// 11:8
	UINT32 cr_st_2d_v_flt_range               :4 ;	// 15:12
	UINT32 cr_ori_3d_blur_y                   :2 ;	// 17:16
	UINT32 cr_ori_3d_blur_c                   :2 ;	// 19:18
	UINT32 cr_tava_v_edge_adap                :1 ;	// 20
	UINT32 cr_tava_debug_mode                 :1 ;	// 21
	UINT32 cr_tava_st_adap                    :1 ;	// 22
	UINT32 cr_tava_en                         :1 ;	// 23
	UINT32 cr_hmc_force_fmd                   :1 ;	// 24
	UINT32 cr_st_2d_v_flt_en                  :1 ;	// 25
	UINT32 cr_clc_fmd_off                     :1 ;	// 26
	UINT32 cr_chroma_tava_only                :1 ;	// 27
	UINT32 cr_film_auto_gain                  :1 ;	// 28
	UINT32 cr_film_apply_c                    :1 ;	// 29
	UINT32 cr_film_apply_y                    :1 ;	// 30
	UINT32 cr_film_mode_enable                :1 ;	// 31
	};
}PE_E60_ND0_ND_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E48C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_ND0_ND_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E490 RW
	UINT32 win_y0                           :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 win_x0                           :13;	//28:16	//
	UINT32 resvd1                           :1;
	UINT32 win_mode                         :1;	//30 //0 := inside enabled	1 = outside enable
	UINT32 win_en                           :1;	//31 //
	};
}PE_E60_ND0_TNR_ETC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E494 RW
	UINT32 win_y1                           :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 win_x1                           :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 win_tnrw_en                      :1;	//31 //this flag is valid only if "win_en = 1"
	};
}PE_E60_ND0_TNR_ETC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E498 RW
	UINT32 minfo_tnr_rd_m_delay             :4;	//3:0	//0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd0                           :4;
	UINT32 minfo_tnr_rd_mv_delay            :4;	//11:8	//0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd1                           :4;
	UINT32 minfo_tnr_wr_m_delay             :4;	//19:16	//0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	UINT32 minfo_lstart_delay               :4;	//23:20	//0 := delay (-4)	1 = delay (-3)	2 = delay (-2)	3 = delay (-1)	4 = delay ( 0)	5 = delay (+1)	6 = delay (+2)	7 = delay (+3)
	UINT32 minfo_clc_offset                 :2;	//25:24	//
	UINT32 resvd2                           :2;
	UINT32 minfo_tnr_wr_mv_delay            :4;	//31:28	//0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	};
}PE_E60_ND0_TNR_ETC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E49C RW
	UINT32 reg_clc_minfo_dly                :3;	//2:0	//1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd0                           :1;
	UINT32 reg_clc_flt_dly                  :3;	//6:4	//1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd1                           :1;
	UINT32 fw_tnr_sc_flag_sel               :2;	//9:8	//new
	UINT32 resvd2                           :2;
	UINT32 fw_tnr_sc_flag                   :1;	//12 //new
	UINT32 resvd3                           :3;
	UINT32 fw_tnr_gmv                       :9;	//24:16	//new
	UINT32 resvd4                           :7;
	};
}PE_E60_ND0_TNR_ETC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4A0 RW
	UINT32 reg_sad_mc_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_sad_mc_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_sad_mc_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_sad_mc_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4A4 RW
	UINT32 reg_sad_mc_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_sad_mc_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_sad_mc_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_sad_mc_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4A8 RW
	UINT32 reg_abs_mv_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_abs_mv_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_abs_mv_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_abs_mv_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4AC RW
	UINT32 reg_abs_mv_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_abs_mv_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_abs_mv_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_abs_mv_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4B0 RW
	UINT32 reg_sad_ma_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_sad_ma_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_sad_ma_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_sad_ma_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4B4 RW
	UINT32 reg_sad_ma_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_sad_ma_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_sad_ma_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_sad_ma_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND0_TNR_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4B8 RW
	UINT32 mif_prefetch_ctrl                :8;	//7:0	//reg_en_pf_t1_m   = reg_mif_prefetch_ctrl[7];	reg_en_pf_t4_y   = reg_mif_prefetch_ctrl[6];	reg_en_pf_t3_c   = reg_mif_prefetch_ctrl[5];	reg_en_pf_t3_y   = reg_mif_prefetch_ctrl[4];	reg_en_pf_t2_c   = reg_mif_prefetch_ctrl[3];	reg_en_pf_t2_y   = reg_mif_prefetch_ctrl[2];	reg_en_pf_t1_c   = reg_mif_prefetch_ctrl[1];	reg_en_pf_t1_y   = reg_mif_prefetch_ctrl[0];
	UINT32 mif_vreverse_en                  :11;	//18:8	//reg_en_vreverse_tnrw_m  = reg_mif_vreverse_en[10];	reg_en_vreverse_tnrw_c  = reg_mif_vreverse_en[9];	reg_en_vreverse_tnrw_y  = reg_mif_vreverse_en[8];	reg_en_vreverse_t1_m  = reg_mif_vreverse_en[7];	reg_en_vreverse_t4_y  = reg_mif_vreverse_en[6];	reg_en_vreverse_t3_c  = reg_mif_vreverse_en[5];	reg_en_vreverse_t3_y  = reg_mif_vreverse_en[4];	reg_en_vreverse_t2_c  = reg_mif_vreverse_en[3];	reg_en_vreverse_t2_y  = reg_mif_vreverse_en[2];	reg_en_vreverse_t1_c  = reg_mif_vreverse_en[1];	reg_en_vreverse_t1_y  = reg_mif_vreverse_en[0];
	UINT32 resvd0                           :1;
	UINT32 global_cg_blk_off                :4;	//23:20	//[Debug] Global Clock Gating Sub Block Off	[0] : Global Clock Gating IPC Off	[1] : Global Clock Gating CLC Off	[2] : NA	[3] : NA
	UINT32 power_cg_blk_off                 :4;	//27:24	//[Debug] Power Clock Gating Sub Block Off	[0] : FIM Power Clock Gating Off	[1] : NA	[2] : NA	[3] : NA
	UINT32 reg_dbg_obc                      :2;	//29:28	//[Debug] OBC Out Debug	[0] : Off	[1] : Y = {object,   face}, C = {512, 512}	[2] : Y = {object, object}, C = {512, 512}	[3] : Y = {face  ,   face}, C = {512, 512}
	UINT32 resvd1                           :2;
	};
}PE_E60_ND0_PE0_DEBUG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4C0 RW
	UINT32 reg_dcof_off                     :1;	//0 //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//1 //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//2 //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//3 //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//8 //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//15:10	//reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_E60_ND0_FBC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4C4 RW
	UINT32 reg_dcof_off                     :1;	//0 //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//1 //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//2 //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//3 //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//8 //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//15:10	//reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_E60_ND0_FBC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4C8
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 : TNRW_OUT_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  TNRW_OUT_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND0_TNRW_M_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4CC RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND0_TNRW_M_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4D0 RW
	UINT32 reg_gfd_h_th0_a                  :8;	//7:0	//
	UINT32 reg_gfd_h_th1_a                  :8;	//15:8	//
	UINT32 reg_gfd_h_th0_b                  :8;	//23:16	//
	UINT32 reg_gfd_h_th1_b                  :8;	//31:24	//
	};
}PE_E60_ND0_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4D4 RW
	UINT32 reg_gfd_s_th                     :8;	//7:0	//
	UINT32 reg_gfd_v_th                     :8;	//15:8	//
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//31:30	//0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_E60_ND0_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4D8 RO
	UINT32 reg_gfd_count_a01                :16;	//15:0	//the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//31:16	//the number of pixels inside the HSV color region A, Left-Top
	};
}PE_E60_ND0_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4DC RO
	UINT32 reg_gfd_count_a11                :16;	//15:0	//the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//31:16	//the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_E60_ND0_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4E0 RO
	UINT32 reg_gfd_count_b01                :16;	//15:0	//the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//31:16	//the number of pixels inside the HSV color region B, Left-Top
	};
}PE_E60_ND0_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E4E4 RO
	UINT32 reg_gfd_count_b11                :16;	//15:0	//the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//31:16	//the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_E60_ND0_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010100 RW
	UINT32 load_time                        :1;	//0 //load_time	0 := load at pic_init	1 = load when reg. write
	UINT32 load_enable                      :1;	//1 //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_E60_ND1_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010104 RW
	UINT32 intr_enable                      :1;	//0 //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//6:4	//interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  tnr_end  	'001 =  ipc_end	'010 = tnrw_y_end	'011 = tnrw_c_end	'100 = NA	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//8 //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//26:16	//the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_E60_ND1_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010108 RO
	UINT32 tnr_frame_id                     :4;	//3:0	//TNR_FRAME_ID	increment every tnr_end
	UINT32 ipc_frame_id                     :4;	//7:4	//IPC_FRAME_ID	increment every ipc_end
	UINT32 tnrw_y_frame_id                  :4;	//11:8	//TNRW_Y_FRAME_ID	increment every tnrw_y_end
	UINT32 tnrw_c_frame_id                  :4;	//15:12	//TNRW_C_FRAME_ID	increment every tnrw_c_end
	UINT32 dnr_frame_id                     :8;	//23:16	//IPC_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//27:24	//PIC_INIT_FRAME_ID
	UINT32 resvd                            :4;
	};
}PE_E60_ND1_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901010C RO
	UINT32 line_cnt                         :12;	//11:0	//
	UINT32 resvd                            :4;
	UINT32 timer_cnt                        :16;	//31:16	//timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_E60_ND1_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010110 RW
	UINT32 tnr_c_en                         :1;	//0 //TNR_C_enable	TNR_C memory read&write enable
	UINT32 tnr_y_en                         :1;	//1 //TNR_Y_enable	TNR_Y memory read&write enable
	UINT32 ipc_c_en                         :1;	//2 //IPC_C_enable	IPC_C memory read enable
	UINT32 ipc_y_en                         :1;	//3 //IPC_Y_enable	IPC_Y memory read enable
	UINT32 tnr_c_444_as_420                 :1;	//4 //Enable TNR_C(T1,T3)_422_AS_420	TNR_C behaves as if 420 mode even if the data in the memory 422 format	TNR_C reads only even line: 0,2,4,8 ...
	UINT32 tnr_y2_en                        :1;	//5 //Enable TNR_Y2	It should be enabled for CLC
	UINT32 force_422_to_420                 :1;	//6 //Enable FORCE_420	If the chroma sampling type is 422 and this flag enabled, then	(1) TNR chroma data in 422 format is subsampled to be 420 before being written to the memory	(2) TNR_C(T2), IPC_C(T1) read the data as 420 format	This flag might be used to reduce memory bandwidth for chroma data of TNR & IPC
	UINT32 ipc0_y_en_prog                   :1;	//7 //mem port ipc0_y enable
	UINT32 mif_last_mode                    :3;	//10:8	//you should set this value to 0x7 if you want MIF to work correctly in case of abnormal-pic_init
	UINT32 tnrw_off                         :1;	//11 //TNR write OFF
	UINT32 resvd0                           :1;
	UINT32 tnr_m_en                         :1;	//13 //TNR_M (motion info) memory read&write enable
	UINT32 force_444_to_422                 :1;	//14 //Enable FORCE_422	If the chroma sampling type is 444 and this flag enabled, then	(1) TNR chroma data in 444 format is subsampled to be 422 before being written to the memory	(2) TNR_C, IPC_C read the data as 422 format
	UINT32 resvd1                           :1;
	UINT32 detour_enable                    :1;	//16 //
	UINT32 half_rate_en                     :1;	//17 //should be enabled for the interlaced source
	UINT32 ibuf_en                          :2;	//19:18	//(19) input buffer enable Y 	(18) input buffer enable C
	UINT32 minfo_hsample_mode               :3;	//22:20	//* this flag valid only if "tnr_m_en" = 1	* minfo_hsample_mode and minfo_qurt_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 4K or 1080p would be typical case for it   If this mode ON, It reduces hsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 = minfo hhalf mode disable	1 = minfo hhalf mode enable	2 = minfo hqurt mode enable	3 = reserved
	UINT32 minfo_vsample_mode               :3;	//25:23	//* this flag valid only if "tnr_m_en" = 1	* minfo_vsample_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 1080p would be typical case for it   If this mode ON, It reduces vsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 := minfo vhalf mode disable	1 = minfo vhalf mode enable (V subsampling: 0,2,4,6,...)	2 = minfo vqurt mode enable (V subsampling: 0,4,8,12,...)	5 = minfo vhalf mode enable (V subsampling: 0,3,4,7,...)	6 = minfo vqurt mode enable (V subsampling: 2,6,10,14,...)
	UINT32 o_line_ctrl_mode                 :1;	//26 //0:= select odd line for Top field, even line for Bottom field	1 = select even line for Top field, odd line for Bottom field
	UINT32 o_line_ctrl_en                   :1;	//27 //output line subsample enable
	UINT32 tnr_in_lsb_mode                  :2;	//29:28	//00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 m_run_id                         :2;	//31:30	//
	};
}PE_E60_ND1_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010114 RW
	UINT32 hsize                            :12;	//11:0	//HSIZE: 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :1;
	UINT32 cs_type                          :3;	//15:13	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :13;	//28:16	//VSIZE: 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :2;
	UINT32 scan_type                        :1;	//31 //scan_type	1 : progressive	0 : interlaced
	};
}PE_E60_ND1_PE0_SRC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010118 RW
	UINT32 field_id                         :1;	//0 //FIELD_ID	0 := top	1 = bottom
	UINT32 resvd0                           :3;
	UINT32 field_mode                       :2;	//5:4	//0 := manual field setting	1 = field auto-inversion	2 = use detected field 	3 = use detected field: inversion
	UINT32 field_inv                        :1;	//6 //field inversion enable: valid only if field_mode = 0
	UINT32 resvd1                           :1;
	UINT32 secam_line                       :1;	//8 //0 := Cb-line first	1 = Cr-line first
	UINT32 resvd2                           :3;
	UINT32 secam_line_mode                  :2;	//13:12	//0 := manual secam_cline	1 = manual secam_cline (inversion)	2 = use detected secam line	3 = use detected secam line(inversion)
	UINT32 resvd3                           :2;
	UINT32 out_cs_type                      :3;	//18:16	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 resvd4                           :1;
	UINT32 out_422_hsample_mode             :1;	//20 //0 := 0,2,4,6,…	1 = 1,3,5,7,…
	UINT32 out_420_vsample_mode             :1;	//21 //0 := 0,3,4,7,…	1 = 0,2,4,6,…
	UINT32 resvd5                           :10;
	};
}PE_E60_ND1_PE0_FIELD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901011C RW
	UINT32 in_hsize                         :12;	//11:0	//
	UINT32 resvd0                           :1;
	UINT32 ptn_en_c                         :1;	//13 //
	UINT32 lend_manual_vsize                :1;	//14 //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_vsize	1 = internal line_end generated by in_vsize [11:0]
	UINT32 resvd1                           :1;
	UINT32 in_vsize                         :13;	//28:16	//
	UINT32 ptn_en_y                         :1;	//29 //
	UINT32 lend_manual_hsize                :1;	//30 //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_hsize	1 = internal line_end generated by in_hsize [11:0]
	UINT32 lend_ctrl_en                     :1;	//31 //0 := use internla line_end	1 = use external line end
	};
}PE_E60_ND1_PE0_DEBUG_LEND_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010120 RW
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 : PE0_IN_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  PE0_IN_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND1_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010124 RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND1_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010128 RW
	UINT32 fbc_reserved                     :32;	//31:0	//
	};
}PE_E60_ND1_FBC_CTRL0_RESERVED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901012C RW
	UINT32 fbc_reserved                     :32;	//31:0	//
	};
}PE_E60_ND1_FBC_CTRL1_RESERVED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010130 RW
	UINT32 en_rd_t1_y                       :1;	//0 //[NA] Read T-1 Y Enable for IPC
	UINT32 en_rd_t1_c                       :1;	//1 //[NA] Read T-1 C Enable for IPC
	UINT32 en_rd_t2_y                       :1;	//2 //Read T-2 Y Enable for IPC, TNR
	UINT32 en_rd_t2_c                       :1;	//3 //Read T-2 C Enable for IPC, TNR
	UINT32 en_rd_t3_y                       :1;	//4 //[NA] Read T-3 Y Enable for IPC
	UINT32 en_rd_t3_c                       :1;	//5 //[NA] Read T-3 C Enable for IPC
	UINT32 en_rd_t4_y                       :1;	//6 //[NA] Read T-4 Y Enable for IPC, CLC
	UINT32 en_rd_t1_m                       :1;	//7 //Read Minfo Enable
	UINT32 en_wr_tnrw_y                     :1;	//8 //Write IPC, TNR, CLC Y Enable
	UINT32 en_wr_tnrw_c                     :1;	//9 //Write IPC, TNR, CLC C Enable
	UINT32 en_wr_tnrw_m                     :1;	//10 //Write Minfo Enable
	UINT32 resvd0                           :4;
	UINT32 manual_mem_off                   :1;	//15 //manual memory port off
	UINT32 resvd1                           :16;
	};
}PE_E60_ND1_PE0_MEM_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010134 RW
	UINT32 lreq_dly_c                       :11;	//10:0	//unit: 16 de_clk
	UINT32 lreq_dly_c_en                    :1;	//11 //
	UINT32 resvd0                           :4;
	UINT32 lreq_dly_y                       :11;	//26:16	//
	UINT32 lreq_dly_y_en                    :1;	//27 //
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_PE0_DEBUG_LREQ_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010138 RW
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 : TNRW_OUT_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  TNRW_OUT_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND1_TNRW_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901013C RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND1_TNRW_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010140 RW
	UINT32 reg_tnr_en                       :1;	//0:0	//
	UINT32 reg_hw_col_data_copy_en          :1;	//1:1	//E20
	UINT32 reg_sc_detect_hres               :1;	//2:2	//
	UINT32 reg_clc_nt_pal                   :1;	//3:3	//
	UINT32 reg_clc_mem_wr_mode              :2;	//5:4	//
	UINT32 reg_sad_8x3_res                  :2;	//7:6	//
	UINT32 reg_sad_8x3_iir_en               :1;	//8:8	//
	UINT32 reg_sad_8x3_chroma_en            :1;	//9:9	//
	UINT32 reg_minfo_sw                     :2;	//11:10	//
	UINT32 reg_minfo_mode10                 :2;	//13:12	//[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt                    :2;	//15:14	//
	UINT32 reg_tnr_single_en                :1;	//16:16	//TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en               :1;	//17 //O20
	UINT32 reg_minfo_mode32                 :2;	//19:18	//
	UINT32 reg_minfo_mode74                 :4;	//23:20	//
	UINT32 reg_sad_8x3_iir_alpha            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010144 RW
	UINT32 reg_dbg_show                     :4;	//3:0	//
	UINT32 reg_ma_motion_iir_alpha          :8;	//11:4	//for decontour, new
	UINT32 reg_ma_motion_iir_en             :1;	//12 //for decontour, new
	UINT32 reg_ma_motion_chroma_en          :1;	//13 //for decontour, new
	UINT32 reg_ma_motion_res                :2;	//15:14	//for decontour, new
	UINT32 reg_dbg_tnrw                     :2;	//17:16	//TNR Write를 선택합니다. 	0 = TNR 출력 (T)	1 = TNR 현재 입력 (T)	2 = TNR 이전 입력 (T-1)
	UINT32 reg_ma_motion_lsb6_sel           :1;	//18 //for decontour, new
	UINT32 reg_sad_8x3_lsb6_sel             :1;	//19 //new
	UINT32 reg_tnri_debug_mode              :2;	//21:20	//
	UINT32 resvd0                           :2;
	UINT32 reg_minfo_mode118                :4;	//27:24	//
	UINT32 reg_sc_scale2                    :3;	//30:28	//
	UINT32 resvd1                           :1;
	};
}PE_E60_ND1_TNR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010148 RW
	UINT32 sc_en                            :1;	//0 //scene change detection enable
	UINT32 sc_max_flt_en                    :1;	//1 //scene change: temporal max filter enable
	UINT32 sc_calc_prev_hist                :1;	//2 //scene change: calculation mode for previous histogram	0:= delay current histogram	1 = compute histogram for previous data
	UINT32 sc_chroma_en                     :1;	//3 //scene change: use of chroma histogram difference
	UINT32 sc_scale                         :3;	//6:4	//bit-select from 21bit scene change measure to 8-bit measure	0 := sc_measure[21 -1 :21-8]	1 = sc_measure [21 -3 :21-10]	2 = sc_measure [21 -5 :21-12]	3 = sc_measure [21 -7 :21-14]	4 = sc_measure [21 -9 :21-16]	5 = sc_measure [21-11:21-18]	6 = sc_measure [21-13:21-20]	7 = sc_measure [21-141:21-21]
	UINT32 resvd0                           :1;
	UINT32 sc_max_flt_tap                   :3;	//10:8	//scene change: temporal max filter tap
	UINT32 resvd1                           :1;
	UINT32 sc_chroma_gain                   :3;	//14:12	//scene change: gain of chroma histogram difference	0 := x1	1 = x1/2	2 = x1/4	3 = x1/8	4 = x1/16	5 = x1/32
	UINT32 sc_out_mode                      :1;	//15 //TNR_STATUS_04: scene change measure update mode	0:= update every frame	1 = update only if the scene_measure is larger than "sc_th_memc"
	UINT32 sc_th_ma                         :8;	//23:16	//scene change threshold for MA
	UINT32 sc_th_memc                       :8;	//31:24	//scene change threshold for MEMC
	};
}PE_E60_ND1_TNR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901014C RW
	UINT32 show_dbg_bar_scale               :3;	//2:0	//debug bar scale
	UINT32 resvd0                           :1;
	UINT32 show_dbg_bar_en                  :4;	//7:4	//debug bar enable
	UINT32 resvd1                           :8;
	UINT32 show_dbg_bar0_mux                :4;	//19:16	//input mux for the lowest debug bar	0x0 := x_peak	0x1 = motion vector variance	0x2 = motion vector H	0x3 = motion vector V	0x4 = abs(NR-P2)	0x5 = abs(NR-CC)	0x6 = MA motion	0x7 = spatial variance	0x8 = scene change
	UINT32 show_dbg_bar1_mux                :4;	//23:20	//input mux for 2nd debug bar
	UINT32 show_dbg_bar2_mux                :4;	//27:24	//input mux for 3rd debug bar
	UINT32 show_dbg_bar3_mux                :4;	//31:28	//input mux for the highest debug bar
	};
}PE_E60_ND1_TNR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010150 RW
	UINT32 manual_debug_bar_09              :8;	//7:0	//for manual debug mode ( reg_mux : 1001)
	UINT32 manual_debug_bar_10              :8;	//15:8	//for manual debug mode ( reg_mux : 1010)
	UINT32 manual_debug_bar_11              :8;	//23:16	//for manual debug mode ( reg_mux : 1011)
	UINT32 manual_debug_bar_12              :8;	//31:24	//for manual debug mode ( reg_mux : 1100)
	};
}PE_E60_ND1_TNR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010154 RW
	UINT32 reg_mamc_blend_mode              :2;	//1:0	//
	UINT32 reg_mamc_blend_mv_max_or_sum     :1;	//2 //0: max, 1: sum
	UINT32 reg_mamc_ma_sad_cut              :1;	//3 //0: 6b, 1:2b
	UINT32 reg_mamc_mc_sad_cut              :1;	//4 //0: 6b, 1:2b
	UINT32 resvd0                           :11;
	UINT32 reg_mv_pv_fix_v                  :4;	//19:16	//
	UINT32 reg_mv_pv_fix_h                  :5;	//24:20	//
	UINT32 resvd1                           :6;
	UINT32 reg_mv_pv_fix_en                 :1;	//31 //
	};
}PE_E60_ND1_TNR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010158 RW
	UINT32 reg_me_lb_base                   :8;	//7:0	//
	UINT32 reg_me_pv_base                   :8;	//15:8	//
	UINT32 reg_me_lb_polarity               :1;	//16 //
	UINT32 resvd                            :15;
	};
}PE_E60_ND1_TNR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901015C RW
	UINT32 resvd0                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//5:4	//
	UINT32 resvd1                           :2;
	UINT32 reg_sc_en                        :1;	//8 //
	UINT32 resvd2                           :23;
	};
}PE_E60_ND1_TNR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010160 RW
	UINT32 reg_mv_h_fix_val                 :5;	//4:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_mv_v_fix_val                 :4;	//11:8	//
	UINT32 reg_mv_h_fix_fb_val              :5;	//16:12	//
	UINT32 resvd1                           :3;
	UINT32 reg_mv_v_fix_fb_val              :4;	//23:20	//
	UINT32 reg_debug_sel                    :4;	//27:24	//
	UINT32 reg_lb_monitor_sel               :2;	//29:28	//
	UINT32 reg_mv_fb_fix                    :1;	//30 //
	UINT32 reg_mv_fix                       :1;	//31 //
	};
}PE_E60_ND1_TNR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010164 RW
	UINT32 reg_sad_base                     :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_lb_smooth_clip               :6;	//13:8	//
	UINT32 resvd1                           :2;
	UINT32 reg_pv_smooth_clip               :6;	//21:16	//
	UINT32 resvd2                           :10;
	};
}PE_E60_ND1_TNR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010168 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901016C RW
	UINT32 lb_smooth_en                     :1;	//0 //
	UINT32 pv_smooth_en                     :1;	//1 //
	UINT32 pmv_hist_en                      :1;	//2 //new
	UINT32 resvd                            :28;
	UINT32 reg_me_n15_protection            :1;	//31 //
	};
}PE_E60_ND1_TNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010170 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010174 RW
	UINT32 reg_min_sad_ratio                :8;	//7:0	//new
	UINT32 reg_lb_cost_ratio                :8;	//15:8	//new
	UINT32 reg_zero_sad_ratio               :8;	//23:16	//new
	UINT32 reg_zero_mv_blk_mv_sel           :2;	//25:24	//chg
	UINT32 resvd0                           :2;
	UINT32 reg_zero_sad_adv                 :1;	//28 //chg
	UINT32 resvd1                           :3;
	};
}PE_E60_ND1_TNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010178 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901017C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010180 RW
	UINT32 reg_sad_acc_mode                 :2;	//1:0	//
	UINT32 reg_bmv_fix_en                   :1;	//2 //
	UINT32 resvd0                           :1;
	UINT32 reg_bmv_fix_v                    :4;	//7:4	//
	UINT32 reg_bmv_fix_h                    :5;	//12:8	//
	UINT32 resvd1                           :3;
	UINT32 reg_n_hblk                       :4;	//19:16	//
	UINT32 reg_n_vblk                       :5;	//24:20	//
	UINT32 resvd2                           :4;
	UINT32 reg_use_fw_gmv_en                :1;	//29 //new
	UINT32 reg_col_overlap_en               :1;	//30 //new
	UINT32 reg_col_data_share_en            :1;	//31 //new
	};
}PE_E60_ND1_TNR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010184 RW
	UINT32 reg_blk_vsize                    :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_blk_hsize                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_TNR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010188 RW
	UINT32 reg_bsad_scale                   :3;	//2:0	//
	UINT32 reg_bmv_rst_mode                 :1;	//3 //
	UINT32 reg_gsad_scale                   :3;	//6:4	//
	UINT32 resvd                            :1;
	UINT32 reg_gmv_gmv_tl                   :7;	//14:8	//
	UINT32 reg_gmv_gmv_tl_en                :1;	//15 //
	UINT32 reg_bmv_gmv_tl                   :7;	//22:16	//
	UINT32 reg_bmv_gmv_tl_en                :1;	//23 //
	UINT32 reg_bmv_pmv_tl                   :7;	//30:24	//
	UINT32 reg_bmv_pmv_tl_en                :1;	//31 //
	};
}PE_E60_ND1_TNR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901018C RW
	UINT32 bmv_coring_th                    :8;	//7:0	//
	UINT32 reg_col_overlap_mode             :2;	//9:8	//new
	UINT32 resvd                            :6;
	UINT32 gmv_0mv_tl                       :7;	//22:16	//0MV 영향력의 강도 조절 : x10이 bypass이고 높을 수록 강하게 영향을 줌
	UINT32 gmv_0mv_tl_en                    :1;	//23 //Global MV에 0MV 보너스를 줄 것인가?
	UINT32 bmv_0mv_tl                       :7;	//30:24	//0MV 영향력의 강도 조절 : x10이 bypass이고 높을 수록 강하게 영향을 줌
	UINT32 bmv_0mv_tl_en                    :1;	//31 //Large Block MV에 0MV 보너스를 줄 것인가?
	};
}PE_E60_ND1_TNR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010190 RW
	UINT32 reg_detail_beta_mul              :8;	//7:0	//
	UINT32 reg_detail_alpha_mul             :8;	//15:8	//
	UINT32 reg_edge_beta_mul                :8;	//23:16	//
	UINT32 reg_edge_alpha_mul               :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010194 RW
	UINT32 reg_svar_scale                   :3;	//2:0	//
	UINT32 resvd                            :29;
	};
}PE_E60_ND1_TNR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010198 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901019C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101A0 RW
	UINT32 resvd0                           :1;
	UINT32 reg_ombc_en                      :1;	//1 //
	UINT32 resvd1                           :2;
	UINT32 reg_luma_gain_en                 :1;	//4 //
	UINT32 reg_crgn_gain_en                 :1;	//5 //
	UINT32 reg_chroma_sad_res               :2;	//7:6	//
	UINT32 resvd2                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//13:12	//
	UINT32 resvd3                           :2;
	UINT32 reg_avg_cmp_en                   :1;	//16 //
	UINT32 reg_avg_cmp_res                  :3;	//19:17	//
	UINT32 reg_debug_sel                    :4;	//23:20	//
	UINT32 resvd4                           :4;
	UINT32 reg_cnt_mode                     :3;	//30:28	//
	UINT32 reg_chroma_sad_en                :1;	//31 //
	};
}PE_E60_ND1_TNR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101A4 RW
	UINT32 resvd                            :24;
	UINT32 reg_skin_master_gain             :8;	//31:24	//new
	};
}PE_E60_ND1_TNR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101A8 RW
	UINT32 reg_tnr_final_lut_yy_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_yy_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101AC RW
	UINT32 reg_tnr_final_lut_yy_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_yy_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101B0 RW
	UINT32 reg_tnr_final_lut_yy_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_yy_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND1_TNR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101B4 RW
	UINT32 reg_tnr_final_lut_cb_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cb_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101B8 RW
	UINT32 reg_tnr_final_lut_cb_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cb_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101BC RW
	UINT32 reg_tnr_final_lut_cb_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cb_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND1_TNR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101C0 RO
	UINT32 w_gsad                           :8;	//7:0	//
	UINT32 w_gmv                            :9;	//16:8	//
	UINT32 resvd                            :7;
	UINT32 w_apl_detail                     :8;	//31:24	//
	};
}PE_E60_ND1_TNR_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101C4 RO
	UINT32 w_apl_motion                     :8;	//7:0	//
	UINT32 w_apl_mc_sad                     :8;	//15:8	//
	UINT32 w_apl_var                        :8;	//23:16	//
	UINT32 w_apl_edge                       :8;	//31:24	//
	};
}PE_E60_ND1_TNR_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101C8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101CC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101D0 RW
	UINT32 main_lut_indir_addr              :6;	//5:0	//
	UINT32 resvd0                           :6;
	UINT32 main_lut_ai_enable               :1;	//12 //TNR Main-LUT Ctrl. AI enable
	UINT32 resvd1                           :2;
	UINT32 main_lut_load                    :1;	//15 //
	UINT32 resvd2                           :16;
	};
}PE_E60_ND1_TNR_MAIN_LUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101D4 RW
	UINT32 main_lut_indir_data0             :32;	//31:0	//TNR Main-LUT Ctrl. Indirect Access Data 0 63:32 (MSB8u:Biggest, LSB8u:Smallest)
	};
}PE_E60_ND1_TNR_MAIN_LUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101DC RO
	UINT32 sc_measure                       :8;	//7:0	//scene change detection measure
	UINT32 apl_y                            :8;	//15:8	//
	UINT32 sc_measure_16                    :16;	//31:16	//scene change measure (16b)
	};
}PE_E60_ND1_TNR_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101E0 RW
	UINT32 resvd                            :16;
	UINT32 reg_gf_gain                      :8;	//23:16	//
	UINT32 reg_blur_coef                    :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101E4 RW
	UINT32 same_protection_en               :1;	//0 //
	UINT32 reg_p_mv0_only                   :1;	//1 //
	UINT32 reg_p_non_mv0_only               :1;	//2 //new
	UINT32 reg_final_lut_en                 :1;	//3 //new
	UINT32 resvd0                           :4;
	UINT32 reg_same_sad_th                  :8;	//15:8	//
	UINT32 reg_move_step                    :8;	//23:16	//
	UINT32 resvd1                           :8;
	};
}PE_E60_ND1_TNR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101E8 RW
	UINT32 reg_tnr_final_lut_cr_x2          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_y3          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cr_x3          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101EC RW
	UINT32 reg_tnr_final_lut_cr_y1          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_x1          :10;	//19:10	//new
	UINT32 reg_tnr_final_lut_cr_y2          :10;	//29:20	//new
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_TNR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101F0 RW
	UINT32 reg_tnr_final_lut_cr_y0          :10;	//9:0	//new
	UINT32 reg_tnr_final_lut_cr_x0          :10;	//19:10	//new
	UINT32 resvd                            :12;
	};
}PE_E60_ND1_TNR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101F4 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101F8 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90101FC RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_ND1_TNR_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010250 RO
	UINT32 r_pc_v_count                     :16;	//15:0	//FMD, vertical tearing count of pc (upper)
	UINT32 r_nc_v_count                     :16;	//31:16	//FMD, vertical tearing count of nc (upper)
	};
}PE_E60_ND1_IPC_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010254 RO
	UINT32 r_pc_nc_same                     :16;	//15:0	//FMD, same count between pc and nc (upper)
	UINT32 r_pn_v_count                     :16;	//31:16	//FMD, vertical tearing count of pn (upper)
	};
}PE_E60_ND1_IPC_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010258 RO
	UINT32 reserved                         :6;	//5:0	//
	UINT32 r_fmd_32_min_th_flag_u           :1;	//6 //FMD, 3:2 detector min_th flag(upper)
	UINT32 r_fmd_32_max_th_flag_u           :1;	//7 //FMD, 3:2 detector max_th flag(upper)
	UINT32 r_fmd_still_limit_flag_u         :1;	//8 //FMD, still_limit flag(upper)
	UINT32 r_fmd_still_pn_th2_flag_u        :1;	//9 //FMD, still_pn_th2 flag(upper)
	UINT32 r_fmd_still_pn_th_flag_u         :1;	//10 //FMD, still_pn_th flag(upper)
	UINT32 r_fmd_still_prev_ratio_flag_u    :1;	//11 //FMD, still_prev_ratio flag(upper)
	UINT32 r_fmd_bigger_flag_u              :1;	//12 //FMD, bigger flag(upper)
	UINT32 r_fmd_smaller_flag_u             :1;	//13 //FMD, smaller flag(upper)
	UINT32 r_fmd_3_2_fmd_comb_mode_u        :2;	//15:14	//FMD, comb_flag of 3_2 mode (upper)
	UINT32 r_pn_diff_count                  :16;	//31:16	//FMD, pndiff count (upper)
	};
}PE_E60_ND1_IPC_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901025C RO
	UINT32 same_ng_flag_d                   :1;	//0 //FMD, same condition but comb_flag is not NOTT(under)
	UINT32 too_small_flag_d                 :1;	//1 //FMD, meet toosmall condition (under)
	UINT32 r_fmd_still_flag_d               :1;	//2 //FMD, 1 : detect still (under)
	UINT32 r_fmd_possibility_flag_d         :1;	//3 //FMD, possibility flag of 3_2 mode(under)
	UINT32 base_pn_ratio_flag_d             :1;	//4 //FMD, meet reg_fmd_ratio_th condition (under)
	UINT32 r_32_detected_flag_d             :1;	//5 //FMD, 3:2 detect flag (under)
	UINT32 r_fmd_comb_mode_d                :2;	//7:6	//FMD, COMB_MODE of FMD Decision (under)
	UINT32 r_fmd_lock_count_d               :8;	//15:8	//FMD, LockCnt (under)
	UINT32 same_ng_flag_u                   :1;	//16 //FMD, same condition but comb_flag is not NOTT(upper)
	UINT32 too_small_flag_u                 :1;	//17 //FMD, meet toosmall condition (upper)
	UINT32 r_fmd_still_flag_u               :1;	//18 //FMD, 1 : detect still (upper)
	UINT32 r_fmd_possibility_flag_u         :1;	//19 //FMD, possibility flag of 3_2 mode(upper)
	UINT32 base_pn_ratio_flag_u             :1;	//20 //FMD, meet reg_fmd_ratio_th condition (upper)
	UINT32 r_32_uetected_flag_u             :1;	//21 //FMD, 3:2 detect flag (upper)
	UINT32 r_fmd_comb_mode_u                :2;	//23:22	//FMD, COMB_MODE of FMD Decision (upper)
	UINT32 r_fmd_lock_count_u               :8;	//31:24	//FMD, LockCnt (upper)
	};
}PE_E60_ND1_IPC_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90102E0 RW
	UINT32 mmd_vtap_yy                      :2;	//1:0	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd0                           :2;
	UINT32 mmd_htap_yy                      :2;	//5:4	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd1                           :2;
	UINT32 mmd_vtap_cc                      :2;	//9:8	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd2                           :2;
	UINT32 mmd_htap_cc                      :2;	//13:12	//// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd3                           :2;
	UINT32 reg_chroma_mmd_en                :1;	//16 //0 := off	1 := on
	UINT32 resvd4                           :15;
	};
}PE_E60_ND1_MMD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010328 RO
	UINT32 r_pc_v_count_d                   :16;	//15:0	//FMD, vertical tearing count of pc (under)
	UINT32 r_nc_v_count_d                   :16;	//31:16	//FMD, vertical tearing count of nc (under)
	};
}PE_E60_ND1_IPC_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901032C RO
	UINT32 r_pc_nc_same_d                   :16;	//15:0	//FMD, same count between pc and nc (under)
	UINT32 r_pn_v_count_d                   :16;	//31:16	//FMD, vertical tearing count of pn (under)
	};
}PE_E60_ND1_IPC_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010330 RO
	UINT32 reserved                         :6;	//5:0	//
	UINT32 r_fmd_32_min_th_flag_d           :1;	//6 //FMD, 3:2 detector min_th flag(under)
	UINT32 r_fmd_32_max_th_flag_d           :1;	//7 //FMD, 3:2 detector max_th flag(under)
	UINT32 r_fmd_still_limit_flag_d         :1;	//8 //FMD, still_limit flag(under)
	UINT32 r_fmd_still_pn_th2_flag_d        :1;	//9 //FMD, still_pn_th2 flag(under)
	UINT32 r_fmd_still_pn_th_flag_d         :1;	//10 //FMD, still_pn_th flag(under)
	UINT32 r_fmd_still_prev_ratio_flag_d    :1;	//11 //FMD, still_prev_ratio flag(under)
	UINT32 r_fmd_bigger_flag_d              :1;	//12 //FMD, bigger flag(under)
	UINT32 r_fmd_smaller_flag_d             :1;	//13 //FMD, smaller flag(under)
	UINT32 r_fmd_3_2_fmd_comb_mode_d        :2;	//15:14	//FMD, comb_flag of 3_2 mode (under)
	UINT32 r_pn_diff_count_d                :16;	//31:16	//FMD, pndiff count (under)
	};
}PE_E60_ND1_IPC_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010334 RO
	UINT32 r_inv_inversed_cnt               :16;	//15:0	//
	UINT32 r_inv_original_cnt               :16;	//31:16	//
	};
}PE_E60_ND1_IPC_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010338 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_IPC_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901033C RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_IPC_STATUS_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010340 RW
	UINT32 reg_show_scale                   :3;	//2:0	//
	UINT32 reg_bbd_show                     :1;	//3 //display BBD result
	UINT32 reg_show_bar_1                   :1;	//4 //
	UINT32 reg_show_bar_2                   :1;	//5 //
	UINT32 reg_show_bar_3                   :1;	//6 //
	UINT32 reg_bar1_data_mux                :2;	//8:7	//bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//10:9	//
	UINT32 reg_bar3_data_mux                :2;	//12:11	//
	UINT32 reg_hist0_data_mux               :4;	//16:13	//bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//20:17	//
	UINT32 reg_hist2_data_mux               :4;	//24:21	//
	UINT32 reg_hist0_win_sel                :2;	//26:25	//hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//28:27	//hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//30:29	//hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_status_eo_sel                :1;	//31 //0:use even data, 1:use odd data
	};
}PE_E60_ND1_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010344 RW
	UINT32 wina_x0                          :12;	//11:0	//winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//27:16	//winA_y0
	UINT32 resvd1                           :2;
	UINT32 reg_sy_limited_en_wina           :1;	//30 //use s/y min/max th
	UINT32 reg_wina_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND1_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010348 RW
	UINT32 wina_x1                          :12;	//11:0	//winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//27:16	//winA_y1
	UINT32 resvd1                           :1;
	UINT32 reg_601_709_sel                  :1;	//29 //0:709YC2RGB, 1:601YC2RGB
	UINT32 reg_hist_hsv_hsl_sel             :1;	//30 //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//31 //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_E60_ND1_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901034C RW
	UINT32 winb_x0                          :12;	//11:0	//winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//27:16	//winB_y0
	UINT32 resvd1                           :2;
	UINT32 reg_sy_limited_en_winb           :1;	//30 //use s/y min/max th
	UINT32 reg_winb_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND1_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010350 RW
	UINT32 winb_x1                          :12;	//11:0	//winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//27:16	//winB_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010354 RW
	UINT32 winc_x0                          :12;	//11:0	//winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//15 //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//27:16	//winC_y0
	UINT32 resvd1                           :2;
	UINT32 reg_sy_limited_en_winc           :1;	//30 //use s/y min/max th
	UINT32 reg_winc_ven                     :1;	//31 //(vertical) window mode enable
	};
}PE_E60_ND1_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010358 RW
	UINT32 winc_x1                          :12;	//11:0	//winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//27:16	//winC_y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901035C RW
	UINT32 reg_force_y                      :10;	//9:0	//force Y value
	UINT32 reg_force_y_max_th               :10;	//19:10	//forcing range max th
	UINT32 reg_force_y_min_th               :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//31 //force Y enable
	};
}PE_E60_ND1_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010360 RW
	UINT32 reg_force_cb                     :10;	//9:0	//force Cb value
	UINT32 reg_force_cb_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//31 //force Cb enable(with Y range)
	};
}PE_E60_ND1_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010364 RW
	UINT32 reg_force_cr                     :10;	//9:0	//force Cr value
	UINT32 reg_force_cr_max_th              :10;	//19:10	//forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//29:20	//forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//31 //force Cr enable(with Y range)
	};
}PE_E60_ND1_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010368 RO
	UINT32 hist_pixel_count                 :22;	//21:0	//histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_E60_ND1_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901036C RW
	UINT32 cl_lcount_enable                 :1;	//0 //1: use CL Lock count(Temporal filter)	should be OFF when 4K input
	UINT32 cl_lcnt_mode                     :2;	//2:1	//"00":VA 2 lcnt, "01":VA 4 lcnt, "10"/"11":VA 6 lcnt
	UINT32 cl_scene_change_enable           :1;	//3 //1:reset CL Lock count when Scene changed
	UINT32 cl_scene_change_mode             :1;	//4 //0:Auto(from TNR scene change flag), 1:Manual(from Host)
	UINT32 cl_scene_change_manual           :1;	//5 //1:reset CL Lock count manually
	UINT32 cl_lcnt_th                       :4;	//9:6	//Temporal filtering threshold
	UINT32 cl_plus_lcount                   :3;	//12:10	//plus count when CL final flag = '1'
	UINT32 cl_minus_lcount                  :2;	//14:13	//minus count when CL final flag = '0'
	UINT32 cl_scene_change_protect          :1;	//15 //1': remain current CL flag when reset Lock count
	UINT32 resvd                            :4;
	UINT32 cl_tearing_pt_th2                :12;	//31:20	//CL Original Tearing protection threshold(CL filtering)
	};
}PE_E60_ND1_CLC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010370 RW
	UINT32 reg_bbd_en                       :1;	//0 //enable
	UINT32 reg_hys_mode                     :5;	//5:1	//frame count for temporal smoothing of BBD result
	UINT32 reg_op_mode                      :1;	//6 //BBD operation mode 0 : auto detection, 1 : manual setting
	UINT32 resvd                            :1;
	UINT32 reg_cnt_th                       :8;	//15:8	//continuous Black pixel's count threshold for recognizing Black Boundary
	UINT32 reg_diff_th                      :8;	//23:16	//threshold for Black decision
	UINT32 reg_bbd_mux                      :3;	//26:24	//data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
	UINT32 reg_apl_mux                      :3;	//29:27	//data select for APL, 0 : YCbCr, 1 : GBR, 2 : HSV, 3 : YSV, others : YCbCr
	UINT32 reg_apl_win_sel                  :2;	//31:30	//apl window selection 0 : BBD status, 1 : Win_A, 2 : Win_B, 3 : Win_C
	};
}PE_E60_ND1_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010374 RW
	UINT32 x0                               :12;	//11:0	//x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//27:16	//y0
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010378 RW
	UINT32 x1                               :12;	//11:0	//x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//27:16	//y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901037C RO
	UINT32 x0                               :12;	//11:0	//x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//27:16	//y0
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010380 RO
	UINT32 x1                               :12;	//11:0	//x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//27:16	//y1
	UINT32 resvd1                           :4;
	};
}PE_E60_ND1_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010384 RO
	UINT32 y_g_s_apl                        :10;	//9:0	//data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//19:10	//data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//29:20	//data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_E60_ND1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010388 RW
	UINT32 reg_s_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//25:16	//threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_E60_ND1_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901038C RW
	UINT32 reg_y_th_max                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_ND1_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010390 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	…	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//14:13	//histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//28 //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	//30 //histogram read mode enable
	UINT32 hist_read_done                   :1;	//31 //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_E60_ND1_TPD_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010394 RO
	UINT32 hist_status                      :22;	//21:0	//histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_E60_ND1_TPD_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010398 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 y_offset                         :10;	//13:4	//
	UINT32 resvd1                           :2;
	UINT32 center_position                  :8;	//23:16	//center position for Y gain control
	UINT32 y_gain                           :8;	//31:24	//
	};
}PE_E60_ND1_LVCRTL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901039C RO
	UINT32 hist_pixel_count                 :22;	//21:0	//histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_E60_ND1_TPD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103A0 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103A4 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103A8 RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103AC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_TNR_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103C0 RW
	UINT32 reg_gmv_rst                      :1;	//0 //
	UINT32 reg_bmv_rst                      :1;	//1 //
	UINT32 reg_me_rst                       :1;	//2 //
	UINT32 reg_mc_rst                       :1;	//3 //
	UINT32 reg_ma_rst                       :1;	//4 //
	UINT32 resvd                            :27;
	};
}PE_E60_ND1_TNR_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103D0 RW
	UINT32 resvd0                           :2;
	UINT32 reg_a_normalize_en               :1;	//2 //
	UINT32 reg_t_normalize_en               :1;	//3 //
	UINT32 reg_t_cut_resolution             :2;	//5:4	//
	UINT32 reg_ne_normalize_en              :1;	//6 //
	UINT32 resvd1                           :9;
	UINT32 reg_cross_th_ne                  :8;	//23:16	//
	UINT32 reg_cross_th                     :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103D4 RW
	UINT32 reg_mul_base_t                   :8;	//7:0	//
	UINT32 reg_mul_base_e                   :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_ND1_TNR_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103D8 RW
	UINT32 reg_a_lut_edge_y0                :8;	//7:0	//
	UINT32 reg_a_lut_edge_x0                :8;	//15:8	//
	UINT32 reg_a_lut_edge_y1                :8;	//23:16	//
	UINT32 reg_a_lut_edge_x1                :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103DC RW
	UINT32 reg_a_lut_detail_y0              :8;	//7:0	//
	UINT32 reg_a_lut_detail_x0              :8;	//15:8	//
	UINT32 reg_a_lut_detail_y1              :8;	//23:16	//
	UINT32 reg_a_lut_detail_x1              :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103E0 RW
	UINT32 reg_t_lut_edge_y0                :8;	//7:0	//
	UINT32 reg_t_lut_edge_x0                :8;	//15:8	//
	UINT32 reg_t_lut_edge_y1                :8;	//23:16	//
	UINT32 reg_t_lut_edge_x1                :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103E4 RW
	UINT32 reg_t_lut_detail_y0              :8;	//7:0	//
	UINT32 reg_t_lut_detail_x0              :8;	//15:8	//
	UINT32 reg_t_lut_detail_y1              :8;	//23:16	//
	UINT32 reg_t_lut_detail_x1              :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103E8 RW
	UINT32 reg_edge_minmax_y0               :8;	//7:0	//
	UINT32 reg_edge_minmax_x0               :8;	//15:8	//
	UINT32 reg_edge_minmax_y1               :8;	//23:16	//
	UINT32 reg_edge_minmax_x1               :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103EC RW
	UINT32 reg_detail_minmax_y0             :8;	//7:0	//
	UINT32 reg_detail_minmax_x0             :8;	//15:8	//
	UINT32 reg_detail_minmax_y1             :8;	//23:16	//
	UINT32 reg_detail_minmax_x1             :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90103F0 RW
	UINT32 reg_sel_ne_type                  :2;	//1:0	//0:(Y - TNR_Y), 1:(Y - SNR_Y), 2:(C - SNR_C)
	UINT32 reg_sel_re_type                  :1;	//2 //0:(still region), 1:(flat region)
	UINT32 resvd0                           :1;
	UINT32 reg_sel_at_mode                  :2;	//5:4	//0:(A), 1:(T), 2:(max(A,T)), 3:(A,T separate)
	UINT32 resvd1                           :2;
	UINT32 reg_hist_xscale                  :3;	//10:8	//histogram x-axi resolution ( 0: 0,1,2… , 1: 0,2,4…)
	UINT32 resvd2                           :1;
	UINT32 reg_hist_yscale                  :2;	//13:12	//histogram cut resolution
	UINT32 resvd3                           :2;
	UINT32 reg_th_atmap                     :8;	//23:16	//at_map threshold ( flat rgion valid threshold )
	UINT32 reg_th_motion                    :8;	//31:24	//motion threshiold ( still region valid threshold )
	};
}PE_E60_ND1_TNR_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010400 RO
	UINT32 valid_cnt                        :16;	//15:0	//# of valid region
	UINT32 resvd                            :16;
	};
}PE_E60_ND1_TNR_NE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010404 RO
	UINT32 hist_1                           :16;	//15:0	//hist[1]
	UINT32 hist_0                           :16;	//31:16	//hist[0]
	};
}PE_E60_ND1_TNR_NE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010408 RO
	UINT32 hist_3                           :16;	//15:0	//hist[3]
	UINT32 hist_2                           :16;	//31:16	//hist[2]
	};
}PE_E60_ND1_TNR_NE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901040C RO
	UINT32 hist_5                           :16;	//15:0	//hist[5]
	UINT32 hist_4                           :16;	//31:16	//hist[4]
	};
}PE_E60_ND1_TNR_NE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010410 RO
	UINT32 hist_7                           :16;	//15:0	//hist[7]
	UINT32 hist_6                           :16;	//31:16	//hist[6]
	};
}PE_E60_ND1_TNR_NE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010414 RO
	UINT32 hist_9                           :16;	//15:0	//hist[9]
	UINT32 hist_8                           :16;	//31:16	//hist[8]
	};
}PE_E60_ND1_TNR_NE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010418 RO
	UINT32 hist_11                          :16;	//15:0	//hist[11]
	UINT32 hist_10                          :16;	//31:16	//hist[10]
	};
}PE_E60_ND1_TNR_NE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901041C RO
	UINT32 hist_13                          :16;	//15:0	//hist[13]
	UINT32 hist_12                          :16;	//31:16	//hist[12]
	};
}PE_E60_ND1_TNR_NE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010420 RO
	UINT32 hist_15                          :16;	//15:0	//hist[15]
	UINT32 hist_14                          :16;	//31:16	//hist[14]
	};
}PE_E60_ND1_TNR_NE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010480 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_ND_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010484 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_ND_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010488 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_ND_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901048C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_ND1_ND_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010490 RW
	UINT32 win_y0                           :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 win_x0                           :13;	//28:16	//
	UINT32 resvd1                           :1;
	UINT32 win_mode                         :1;	//30 //0 := inside enabled	1 = outside enable
	UINT32 win_en                           :1;	//31 //
	};
}PE_E60_ND1_TNR_ETC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010494 RW
	UINT32 win_y1                           :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 win_x1                           :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 win_tnrw_en                      :1;	//31 //this flag is valid only if "win_en = 1"
	};
}PE_E60_ND1_TNR_ETC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9010498 RW
	UINT32 minfo_tnr_rd_m_delay             :4;	//3:0	//0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd0                           :4;
	UINT32 minfo_tnr_rd_mv_delay            :4;	//11:8	//0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd1                           :4;
	UINT32 minfo_tnr_wr_m_delay             :4;	//19:16	//0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	UINT32 minfo_lstart_delay               :4;	//23:20	//0 := delay (-4)	1 = delay (-3)	2 = delay (-2)	3 = delay (-1)	4 = delay ( 0)	5 = delay (+1)	6 = delay (+2)	7 = delay (+3)
	UINT32 minfo_clc_offset                 :2;	//25:24	//
	UINT32 resvd2                           :2;
	UINT32 minfo_tnr_wr_mv_delay            :4;	//31:28	//0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	};
}PE_E60_ND1_TNR_ETC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901049C RW
	UINT32 reg_clc_minfo_dly                :3;	//2:0	//1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd0                           :1;
	UINT32 reg_clc_flt_dly                  :3;	//6:4	//1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd1                           :1;
	UINT32 fw_tnr_sc_flag_sel               :2;	//9:8	//new
	UINT32 resvd2                           :2;
	UINT32 fw_tnr_sc_flag                   :1;	//12 //new
	UINT32 resvd3                           :3;
	UINT32 fw_tnr_gmv                       :9;	//24:16	//new
	UINT32 resvd4                           :7;
	};
}PE_E60_ND1_TNR_ETC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104A0 RW
	UINT32 reg_sad_mc_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_sad_mc_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_sad_mc_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_sad_mc_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104A4 RW
	UINT32 reg_sad_mc_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_sad_mc_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_sad_mc_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_sad_mc_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104A8 RW
	UINT32 reg_abs_mv_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_abs_mv_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_abs_mv_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_abs_mv_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104AC RW
	UINT32 reg_abs_mv_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_abs_mv_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_abs_mv_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_abs_mv_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104B0 RW
	UINT32 reg_sad_ma_ctrl_pt_y0            :8;	//7:0	//
	UINT32 reg_sad_ma_ctrl_pt_x0            :8;	//15:8	//
	UINT32 reg_sad_ma_ctrl_pt_y1            :8;	//23:16	//
	UINT32 reg_sad_ma_ctrl_pt_x1            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104B4 RW
	UINT32 reg_sad_ma_ctrl_pt_y2            :8;	//7:0	//
	UINT32 reg_sad_ma_ctrl_pt_x2            :8;	//15:8	//
	UINT32 reg_sad_ma_ctrl_pt_y3            :8;	//23:16	//
	UINT32 reg_sad_ma_ctrl_pt_x3            :8;	//31:24	//
	};
}PE_E60_ND1_TNR_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104B8 RW
	UINT32 mif_prefetch_ctrl                :8;	//7:0	//reg_en_pf_t1_m   = reg_mif_prefetch_ctrl[7];	reg_en_pf_t4_y   = reg_mif_prefetch_ctrl[6];	reg_en_pf_t3_c   = reg_mif_prefetch_ctrl[5];	reg_en_pf_t3_y   = reg_mif_prefetch_ctrl[4];	reg_en_pf_t2_c   = reg_mif_prefetch_ctrl[3];	reg_en_pf_t2_y   = reg_mif_prefetch_ctrl[2];	reg_en_pf_t1_c   = reg_mif_prefetch_ctrl[1];	reg_en_pf_t1_y   = reg_mif_prefetch_ctrl[0];
	UINT32 mif_vreverse_en                  :11;	//18:8	//reg_en_vreverse_tnrw_m  = reg_mif_vreverse_en[10];	reg_en_vreverse_tnrw_c  = reg_mif_vreverse_en[9];	reg_en_vreverse_tnrw_y  = reg_mif_vreverse_en[8];	reg_en_vreverse_t1_m  = reg_mif_vreverse_en[7];	reg_en_vreverse_t4_y  = reg_mif_vreverse_en[6];	reg_en_vreverse_t3_c  = reg_mif_vreverse_en[5];	reg_en_vreverse_t3_y  = reg_mif_vreverse_en[4];	reg_en_vreverse_t2_c  = reg_mif_vreverse_en[3];	reg_en_vreverse_t2_y  = reg_mif_vreverse_en[2];	reg_en_vreverse_t1_c  = reg_mif_vreverse_en[1];	reg_en_vreverse_t1_y  = reg_mif_vreverse_en[0];
	UINT32 resvd0                           :1;
	UINT32 global_cg_blk_off                :4;	//23:20	//[Debug] Global Clock Gating Sub Block Off	[0] : Global Clock Gating IPC Off	[1] : Global Clock Gating CLC Off	[2] : NA	[3] : NA
	UINT32 power_cg_blk_off                 :4;	//27:24	//[Debug] Power Clock Gating Sub Block Off	[0] : FIM Power Clock Gating Off	[1] : NA	[2] : NA	[3] : NA
	UINT32 reg_dbg_obc                      :2;	//29:28	//[Debug] OBC Out Debug	[0] : Off	[1] : Y = {object,   face}, C = {512, 512}	[2] : Y = {object, object}, C = {512, 512}	[3] : Y = {face  ,   face}, C = {512, 512}
	UINT32 resvd1                           :2;
	};
}PE_E60_ND1_PE0_DEBUG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104C0 RW
	UINT32 reg_dcof_off                     :1;	//0 //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//1 //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//2 //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//3 //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//8 //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//15:10	//reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_E60_ND1_FBC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104C4 RW
	UINT32 reg_dcof_off                     :1;	//0 //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//1 //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//2 //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//3 //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//8 //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//15:10	//reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_E60_ND1_FBC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104C8
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 : TNRW_OUT_SIZE.hsize = in_hsize, PE0_SRC_SIZE.hsize = out_hsize	1 : PE0_SRC_SIZE.hsize = in_hsize,  TNRW_OUT_SIZE.hsize = out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_ND1_TNRW_M_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104CC RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_ND1_TNRW_M_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104D0 RW
	UINT32 reg_gfd_h_th0_a                  :8;	//7:0	//
	UINT32 reg_gfd_h_th1_a                  :8;	//15:8	//
	UINT32 reg_gfd_h_th0_b                  :8;	//23:16	//
	UINT32 reg_gfd_h_th1_b                  :8;	//31:24	//
	};
}PE_E60_ND1_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104D4 RW
	UINT32 reg_gfd_s_th                     :8;	//7:0	//
	UINT32 reg_gfd_v_th                     :8;	//15:8	//
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//31:30	//0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_E60_ND1_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104D8 RO
	UINT32 reg_gfd_count_a01                :16;	//15:0	//the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//31:16	//the number of pixels inside the HSV color region A, Left-Top
	};
}PE_E60_ND1_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104DC RO
	UINT32 reg_gfd_count_a11                :16;	//15:0	//the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//31:16	//the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_E60_ND1_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104E0 RO
	UINT32 reg_gfd_count_b01                :16;	//15:0	//the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//31:16	//the number of pixels inside the HSV color region B, Left-Top
	};
}PE_E60_ND1_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90104E4 RO
	UINT32 reg_gfd_count_b11                :16;	//15:0	//the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//31:16	//the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_E60_ND1_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E500 RW
	UINT32 resvd0                           :1;
	UINT32 load_enable                      :1;	//1 //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd1                           :29;
	};
}PE_E60_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E504 RW
	UINT32 intr_enable                      :1;	//0 //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//6:4	//interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  NA	'001 =  NA	'010 = NA	'011 = NA	'100 = dnr_end	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//8 //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//26:16	//the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_E60_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E508 RO
	UINT32 resvd0                           :16;
	UINT32 dnr_frame_id                     :8;	//23:16	//DNR_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//27:24	//PIC_INIT_FRAME_ID
	UINT32 resvd1                           :4;
	};
}PE_E60_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E50C RO
	UINT32 line_cnt                         :11;	//10:0	//
	UINT32 resvd                            :5;
	UINT32 timer_cnt                        :16;	//31:16	//timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_E60_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E510 RW
	UINT32 resvd0                           :8;
	UINT32 reg_sd_5l_mode_en                :1;	//8 //
	UINT32 resvd1                           :3;
	UINT32 dnr_out_420_vsample_mode         :1;	//12 //0 := 0,3,4,7,…	1 = 0,2,4,6,…
	UINT32 dnr_out_cs_type                  :3;	//15:13	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 detour_enable                    :1;	//16 //
	UINT32 half_rate_en                     :1;	//17 //should be enabled for the interlaced source	should be enabled for running IFC
	UINT32 resvd2                           :2;
	UINT32 ibuf_en                          :2;	//21:20	//(20) input buffer enable Y 	(21) input buffer enable C
	UINT32 dnr_out_422_hsample_mode         :1;	//22 //0 := 0,2,4,6,…	1 = 1,3,5,7,…
	UINT32 resvd3                           :1;
	UINT32 dnr_in_lsb_mode                  :2;	//25:24	//00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 dnr_out_lsb_mode                 :2;	//27:26	//00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 resvd4                           :2;
	UINT32 m_run_id                         :2;	//31:30	//
	};
}PE_E60_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E514 RW
	UINT32 hsize                            :12;	//11:0	//HSIZE: 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :1;
	UINT32 chroma_sampling_type             :3;	//15:13	//chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :13;	//28:16	//VSIZE
	UINT32 resvd1                           :3;
	};
}PE_E60_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E518 RW
	UINT32 hoffset                          :12;	//11:0	//짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//30 //0 := PE0_OUT_SIZE -> in_hsize	1 = PE0_OUT_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//31 //
	};
}PE_E60_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E51C RW
	UINT32 hsize                            :12;	//11:0	//HSIZE : 짝수만 가능. 홀수는 지원하지 않음
	UINT32 resvd0                           :4;
	UINT32 vsize                            :13;	//28:16	//VSIZE : 짝수만 가능. 홀수는 지원하지 않음	 (progressive format 기준)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE0_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E520 RW
	UINT32 x0                               :11;	//10:0	//X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :13;	//28:16	//Y0
	UINT32 resvd1                           :3;
	};
}PE_E60_WIN_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E524 RW
	UINT32 x1                               :11;	//10:0	//X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :13;	//28:16	//Y1
	UINT32 resvd1                           :3;
	};
}PE_E60_WIN_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E528 RW
	UINT32 x0                               :11;	//10:0	//X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :13;	//28:16	//Y0
	UINT32 ac_bnr_en                        :1;	//29 //0 : AC-BNR feature off	1 : AC-BNR feature on
	UINT32 resvd1                           :2;
	};
}PE_E60_WIN_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E52C RW
	UINT32 x1                               :11;	//10:0	//X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :13;	//28:16	//Y1
	UINT32 resvd1                           :3;
	};
}PE_E60_WIN_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E530 RW
	UINT32 bypass                           :1;	//0 //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//1 //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//2 //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//3 //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_E60_CUP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E534 RW
	UINT32 bypass                           :1;	//0 //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//1 //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//2 //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//3 //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_E60_CUP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E538 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_CUP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E580 RW
	UINT32 reg_glb_tearing_th               :8;	//7:0	//
	UINT32 reg_glb_mode_th                  :4;	//11:8	//
	UINT32 reg_tearing_strength             :1;	//12 //
	UINT32 reg_glb_tearing_cnt_normal       :3;	//15:13	//
	UINT32 reg_vf_a_th                      :8;	//23:16	//
	UINT32 resvd                            :6;
	UINT32 reg_vflt_force_en                :1;	//30 //
	UINT32 reg_vflt_en                      :1;	//31 //
	};
}PE_E60_VFILTER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E584 RW
	UINT32 reg_vflt_debug_en                :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_fmd_mode                     :1;	//4 //
	UINT32 resvd1                           :3;
	UINT32 reg_glb_mode                     :1;	//8 //
	UINT32 resvd2                           :3;
	UINT32 reg_glb_mode_fw_en               :1;	//12 //
	UINT32 resvd3                           :3;
	UINT32 reg_glb_vflt_en                  :1;	//16 //
	UINT32 resvd4                           :3;
	UINT32 reg_fmd_vflt_en                  :1;	//20 //
	UINT32 resvd5                           :3;
	UINT32 reg_fmd_tearing_cnt_en           :1;	//24 //
	UINT32 resvd6                           :3;
	UINT32 reg_fmd_motion_en                :1;	//28 //
	UINT32 resvd7                           :3;
	};
}PE_E60_VFILTER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E588 RW
	UINT32 reg_hmc_vflt_en                  :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_hmc_tearing_cnt_en           :1;	//4 //
	UINT32 resvd1                           :3;
	UINT32 reg_hmc_motion_en                :1;	//8 //
	UINT32 resvd2                           :3;
	UINT32 reg_loc_vflt_en                  :1;	//12 //
	UINT32 resvd3                           :3;
	UINT32 reg_loc_tearing_cnt_en           :1;	//16 //
	UINT32 resvd4                           :3;
	UINT32 reg_loc_motion_en_               :1;	//20 //
	UINT32 resvd5                           :3;
	UINT32 reg_alpha_sel_mode               :2;	//25:24	//
	UINT32 resvd6                           :2;
	UINT32 reg_alpha_sel_mode_en            :2;	//29:28	//
	UINT32 resvd7                           :2;
	};
}PE_E60_VFILTER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E58C RW
	UINT32 cti_en                           :1;	//0 //CTI enable
	UINT32 cti_clipping_mode                :1;	//1 //op mode	'0' : CTI	'1': peaking(for debug)
	UINT32 cti_pre_flt_mode                 :1;	//2 //pre-filtering	0 : off	1 : on
	UINT32 cti_tap                          :2;	//4:3	//CTI filter tap size	'0' : 7-tap	'1': 5-tap	'2': 3_2-tap	'3': 3-tap
	UINT32 resvd0                           :3;
	UINT32 cti_gain                         :8;	//15:8	//CTI gain(3.5u)
	UINT32 cti_debug_mode                   :3;	//18:16	//debug mode	"000" : normal display	"100" : coring map(cb)	"101" : coring map(cr)	"110" : avg(cb)	"111" : avg(cr)
	UINT32 resvd1                           :13;
	};
}PE_E60_CTI_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E590 RW
	UINT32 cti_coring_th0                   :8;	//7:0	//CTI coring th0
	UINT32 cti_coring_th1                   :8;	//15:8	//CTI coring th1
	UINT32 cti_coring_smooth                :3;	//18:16	//NOT USED
	UINT32 resvd0                           :1;
	UINT32 reg_cti_tap2                     :2;	//21:20	//CTI coring map size	"00" : 7-tap	"01" : 5-tap	"10" : 3-tap	o.w : 7-tap
	UINT32 resvd1                           :10;
	};
}PE_E60_CTI_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E594 RW
	UINT32 reg_dnr_max_enable               :1;	//0 //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable               :1;	//1 //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel                  :1;	//2 //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel            :1;	//3 //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel                :1;	//4 //0: original, 1: v_filter
	UINT32 reg_decon_max_enable             :1;	//5 //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en             :1;	//6 //
	UINT32 reg_half_rate_cg_n               :1;	//7 //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en                   :1;	//8 //ac : black, dc : white, mnr : green
	UINT32 reg_dnr_motion_sel               :1;	//9 //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 reg_tnr_decon_en                 :1;	//10 //1: tnr_decon, 0: dnr_decon
	UINT32 reg_obc_gain_sel                 :1;	//11 //0: dnr obc(4K이하, internal), 1: nd obc(4K 초과(8K), external)
	UINT32 resvd0                           :4;
	UINT32 reg_win_en                       :1;	//16 //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//17 //border enable
	UINT32 reg_win_inout                    :1;	//18 //
	UINT32 resvd1                           :2;
	UINT32 reg_ipc_motion_en                :1;	//21 //hmc_flag 대응 => 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//24:22	//0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//31:25	//applied ifc when delta is greater than th
	};
}PE_E60_DNR_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E598 RW
	UINT32 reg_dbg_en                       :1;	//0 //debug bar en
	UINT32 reg_show_f3d                     :1;	//1 //
	UINT32 reg_show_bnr                     :1;	//2 //show debug bar for bnr	(acness,acness gain, dc_gain)
	UINT32 reg_f3d_mode                     :1;	//3 //
	UINT32 reg_acness_or_acness_gain        :1;	//4 //0 : acness (blue, green)	1 : acness gain (yellow, red)
	UINT32 resvd                            :27;
	};
}PE_E60_DNR_DBAR_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E59C RW
	UINT32 resvd0                           :16;
	UINT32 reg_detect_level_th              :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_REG_C420_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5A0 RW
	UINT32 reg_mnr_enable                   :1;	//0 //
	UINT32 reg_mnr_debug                    :1;	//1 //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//2 //
	UINT32 reg_mnr_chroma_en                :1;	//3 //
	UINT32 reg_h_expand                     :2;	//5:4	//0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//7:6	//0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//15:8	//
	UINT32 reg_snr_th                       :8;	//23:16	//
	UINT32 reg_th_max                       :8;	//31:24	//
	};
}PE_E60_MNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5A4 RW
	UINT32 reg_mmd_y_max                    :8;	//7:0	//edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//15:8	//reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//23:16	//reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//31:24	//reg_mnr_s2_mmd_min
	};
}PE_E60_MNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5A8 RW
	UINT32 reg_mnr_debug_mode               :4;	//3:0	//0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain
	UINT32 reg_mnr_debug_en                 :1;	//4 //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//31:24	//
	};
}PE_E60_MNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5AC RW
	UINT32 reg_blur_sel                     :1;	//0 //
	UINT32 reg_pattern_en                   :1;	//1 //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//15:8	//
	UINT32 reg_equal_th                     :8;	//23:16	//
	UINT32 reg_mmd_scale                    :8;	//31:24	//
	};
}PE_E60_MNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5B0 RW
	UINT32 reg_mmd_fil_x_3                  :8;	//7:0	//
	UINT32 reg_mmd_fil_x_2                  :8;	//15:8	//
	UINT32 reg_mmd_fil_x_1                  :8;	//23:16	//
	UINT32 reg_mmd_fil_x_0                  :8;	//31:24	//
	};
}PE_E60_MNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5B4 RW
	UINT32 reg_mmd_fil_y_3                  :8;	//7:0	//
	UINT32 reg_mmd_fil_y_2                  :8;	//15:8	//
	UINT32 reg_mmd_fil_y_1                  :8;	//23:16	//
	UINT32 reg_mmd_fil_y_0                  :8;	//31:24	//
	};
}PE_E60_MNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5B8 RW
	UINT32 reg_bnr_ac_detail_max            :8;	//7:0	//detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//15:8	//detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//23:16	//th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//31:24	//th used to find point of inflection
	};
}PE_E60_DETAIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5BC RW
	UINT32 reg_dc_bnr_enable                :1;	//0 //DC BNR enable	0 := off ( output debug mode )	1  = on
	UINT32 reg_dc_blur_debug_mode           :1;	//1 //0: blur, 1: white
	UINT32 reg_dc_blur_sel                  :2;	//3:2	//DC blur sel => 0 : 3x3, 1 : 5x5, 2 : 9x5
	UINT32 reg_dc_output_debug_mode         :4;	//7:4	//0: bypass	1: motion	2: motion gain	3: sum of variance	4: variance gain	5: edge protection map	6: DC gain without edge protection	7: DC gain with edge protection	8: chroma gain without edge protection	9: chroma gain with edge protection	10: fil_diff_th
	UINT32 reg_en_obj_amf_ctrl              :1;	//8 //
	UINT32 resvd                            :4;
	UINT32 reg_obj_gain_mul                 :2;	//14:13	//
	UINT32 reg_obj_gain_en                  :1;	//15 //
	UINT32 reg_dc_motion_max                :8;	//23:16	//dc motion gain th
	UINT32 reg_dc_motion_min                :8;	//31:24	//dc motion gain th, if(reg_dc_motion_en == 0) reg_dc_motion_y_max = manual motion gain value
	};
}PE_E60_DC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5C0 RW
	UINT32 resvd                            :8;
	UINT32 reg_manual_fil_motion_gain       :8;	//15:8	//
	UINT32 reg_var_chroma_en                :1;	//16 //
	UINT32 reg_fil_manual_en                :1;	//17 //
	UINT32 reg_dc_pattern_en                :1;	//18 //
	UINT32 reg_luma_gain_en                 :1;	//19 //
	UINT32 reg_var_v_gain                   :4;	//23:20	//0x5
	UINT32 reg_var_h_gain                   :4;	//27:24	//0x2
	UINT32 reg_var_cut_resolution           :4;	//31:28	//0x5
	};
}PE_E60_DC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5C4 RW
	UINT32 reg_dc_var_en                    :1;	//0 //0x1
	UINT32 reg_dc_motion_en                 :1;	//1 //0x0
	UINT32 reg_dc_protection_en             :1;	//2 //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//15:10	//0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//23:16	//max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//31:24	//
	};
}PE_E60_DC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5C8 RW
	UINT32 reg_dc_bnr_var_th3               :8;	//7:0	//dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//15:8	//dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//23:16	//dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//31:24	//dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
}PE_E60_DC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5CC RW
	UINT32 reg_dc_motion_y_min              :8;	//7:0	//motion gain y축
	UINT32 reg_dc_motion_y_max              :8;	//15:8	//motion gain y축
	UINT32 resvd                            :16;
	};
}PE_E60_DC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5D0 RW
	UINT32 reg_dc_var_y_th0                 :8;	//7:0	//variance gain y축
	UINT32 reg_dc_var_y_th1                 :8;	//15:8	//variance gain y축
	UINT32 reg_dc_var_y_th2                 :8;	//23:16	//variance gain y축
	UINT32 reg_dc_var_y_th3                 :8;	//31:24	//variance gain y축
	};
}PE_E60_DC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5D4 RW
	UINT32 reg_bnr_ac_h_en                  :1;	//0 //
	UINT32 reg_bnr_ac_v_en                  :1;	//1 //
	UINT32 reg_bnr_ac_h_chroma_en           :1;	//2 //
	UINT32 reg_bnr_ac_v_chroma_en           :1;	//3 //
	UINT32 reg_bnr_ac_acness_resol_h        :2;	//5:4	//1: /2, 2: /4, 3:/ 8
	UINT32 reg_multi_run_mode               :1;	//6 //
	UINT32 reg_ac_bnr_gain_yc_sel           :1;	//7 //
	UINT32 reg_bnr_ac_diff_min_v_th         :8;	//15:8	//minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_diff_min_h_th         :8;	//23:16	//minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_iir_gain              :8;	//31:24	//alpha value used in IIR
	};
}PE_E60_AC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5D8 RW
	UINT32 reg_bnr_ac_global_motion_th      :8;	//7:0	//0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//15:8	//th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//23:16	//th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5DC RW
	UINT32 reg_bnr_ac_motion_3              :8;	//7:0	//motion gain x축
	UINT32 reg_bnr_ac_motion_2              :8;	//15:8	//motion gain x축
	UINT32 reg_bnr_ac_motion_1              :8;	//23:16	//motion gain x축
	UINT32 reg_bnr_ac_motion_0              :8;	//31:24	//motion gain x축
	};
}PE_E60_AC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5E0 RO
	UINT32 c420_tearing_cnt                 :16;	//15:0	//
	UINT32 global_motion_iir                :8;	//23:16	//
	UINT32 global_dc_gain                   :8;	//31:24	//
	};
}PE_E60_DNR_STAT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5E4 RW
	UINT32 reg_bnr_ac_motion_y_3            :8;	//7:0	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_2            :8;	//15:8	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_1            :8;	//23:16	//motion gain y축
	UINT32 reg_bnr_ac_motion_y_0            :8;	//31:24	//motion gain y축
	};
}PE_E60_AC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5E8 RW
	UINT32 reg_bnr_ac_v_init_offset         :3;	//2:0	//offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//5:3	//offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//7:6	//0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//11:8	//debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//15:12	//stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//23:16	//
	UINT32 reg_bnr_ac_v_acness_min          :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5EC RO
	UINT32 acness_v_l                       :8;	//7:0	//
	UINT32 acness_h_l                       :8;	//15:8	//
	UINT32 acness_v_g                       :8;	//23:16	//
	UINT32 acness_h_g                       :8;	//31:24	//
	};
}PE_E60_DNR_STAT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5F0 RW
	UINT32 reg_bnr_ac_detail_th4            :8;	//7:0	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//15:8	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//23:16	//detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//31:24	//detail th used in AC-BNR final mux
	};
}PE_E60_AC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5F4 RW
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//7:0	//SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//15:8	//SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//23:16	//SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//31:24	//0x00
	};
}PE_E60_AC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5F8 RW
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//7:0	//SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//15:8	//SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//23:16	//SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//31:24	//SD : 0x00, HD : 0x80
	};
}PE_E60_AC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E5FC RO
	UINT32 h_init                           :8;	//7:0	//
	UINT32 v_init                           :8;	//15:8	//
	UINT32 resvd                            :4;
	UINT32 reg_vfilter_tearing_cnt          :12;	//31:20	//
	};
}PE_E60_DNR_STAT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E600 RW
	UINT32 reg_ac_master_c_gain             :8;	//7:0	//max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_ac_bnr_enable                :1;	//8 //0 : debug mode, 1 : ac result
	UINT32 reg_ac_bnr_motion_en             :1;	//9 //1 : motion gain enable	0 : reg_bnr_ac_motion_y_max = manual motion gain value
	UINT32 reg_ac_bnr_acness_en             :1;	//10 //1 : acness gain enable	0 : reg_bnr_ac_acness_y_max = manual acness gain value
	UINT32 reg_ac_bnr_position_en           :1;	//11 //1 : position gain enable	0 : reg_bnr_ac_pos_gain_H0_7 = manual position gain value
	UINT32 reg_detail_sel                   :1;	//12 //0: old, 1: new
	UINT32 resvd                            :3;
	UINT32 reg_bnr_ac_manual_init_v         :3;	//18:16	//force the specific init position for debug
	UINT32 reg_ac_manual_init_en_v          :1;	//19 //0 : off, 1 : on
	UINT32 reg_bnr_ac_manual_init_h         :3;	//22:20	//force the specific init position for debug
	UINT32 reg_ac_manual_init_en_h          :1;	//23 //0 : off, 1 : on
	UINT32 reg_bnr_ac_pos_gain_l3           :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E604 RW
	UINT32 reg_acness_sel                   :1;	//0 //
	UINT32 reg_g_motion_manual_en           :1;	//1 //
	UINT32 resvd0                           :6;
	UINT32 reg_ac_bnr_debug_h_en            :1;	//8 //
	UINT32 reg_ac_bnr_debug_v_en            :1;	//9 //
	UINT32 reg_ac_master_y_gain             :6;	//15:10	//0x20 is max
	UINT32 reg_g_motion_scale               :3;	//18:16	//
	UINT32 reg_g_motion_div                 :2;	//20:19	//
	UINT32 resvd1                           :10;
	UINT32 reg_ac_flt_level_sel             :1;	//31 //0 : weak, 1 : strong
	};
}PE_E60_AC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E608 RW
	UINT32 reg_ac_detail_gain_y_min         :8;	//7:0	//detail gain y축
	UINT32 reg_ac_detail_gain_y_max         :8;	//15:8	//detail gain y축
	UINT32 reg_bnr_ac_acness_y_min          :8;	//23:16	//acness gain y  축
	UINT32 reg_bnr_ac_acness_y_max          :8;	//31:24	//acness gain y  축
	};
}PE_E60_AC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E60C RW
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//7:0	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//15:8	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//23:16	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//31:24	//ac bnr final mux에서 쓰이는 detail gain 의 y축
	};
}PE_E60_AC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E610 RW
	UINT32 reg_g_motion_manual              :8;	//7:0	//
	UINT32 reg_acness_scale_mul             :8;	//15:8	//
	UINT32 reg_bnr_ac_detail_max            :8;	//23:16	//
	UINT32 reg_bnr_ac_detail_min            :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E614 RW
	UINT32 reg_y_drvt_hcoef_sel             :3;	//2:0	//0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_y_ddrvt_hcoef_sel            :2;	//5:4	//0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_y_edge_gain_res              :1;	//6 //0: |y''|로 [7:0] 선택	1: |y''|/4로 [9:2] 선택
	UINT32 resvd1                           :1;
	UINT32 reg_y_drvt2_hcoef_sel            :3;	//10:8	//5tap, h[0, 0, 8, 8, 0, -8, -8, -0, -0]/16	7tap, h[0, 4, 6, 6, 0, -6, -6, -4, -0]/16	9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_medge_meth                   :1;	//11 //0: 13x3 window (한 라인이라도 해당되면 모두 색칠)	1 :13x3 window (합을 구해서 coring)
	UINT32 reg_medge_th                     :8;	//19:12	//diff의 th
	UINT32 reg_medge_coring_th              :8;	//27:20	//높이의 th
	UINT32 reg_medge_ch_tap                 :2;	//29:28	//0: 13tap	1: 11tap	2: 9tap
	UINT32 reg_edge_meth                    :2;	//31:30	//diff시 center포함 on/off
	};
}PE_E60_IFC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E618 RW
	UINT32 reg_edge_ddrvt_gain_y1           :8;	//7:0	//
	UINT32 reg_edge_ddrvt_gain_x1           :8;	//15:8	//
	UINT32 reg_edge_ddrvt_gain_y0           :8;	//23:16	//
	UINT32 reg_edge_ddrvt_gain_x0           :8;	//31:24	//원래 y edge gain
	};
}PE_E60_IFC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E61C RW
	UINT32 reg_c_drvt_hcoef_sel             :3;	//2:0	//0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_c_ddrvt_hcoef_sel            :2;	//5:4	//0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_c_edge_gain_res              :1;	//6 //0: |y''|로 [7:0] 선택	1: |y''|/4로 [9:2] 선택
	UINT32 resvd1                           :25;
	};
}PE_E60_IFC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E620 RW
	UINT32 reg_c_edge_gain_y1               :8;	//7:0	//
	UINT32 reg_c_edge_gain_x1               :8;	//15:8	//
	UINT32 reg_c_edge_gain_y0               :8;	//23:16	//
	UINT32 reg_c_edge_gain_x0               :8;	//31:24	//
	};
}PE_E60_IFC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E624 RW
	UINT32 reg_crs_para_tap                 :2;	//1:0	//0 : 5tap, h[0, 1, 1, 1, 1 ,1]	1 : 4tap, h[0, 0, 1, 1, 1, 1]	2 : 4tap, h[0, 1, 1, 1, 1, 0]	3 : 6tap, h[1, 1, 1, 1, 1, 1]
	UINT32 reg_cdst_th                      :10;	//11:2	//Cb, Cr 차이가 이 값 이상이어야 유효
	UINT32 reg_crs_op_tap                   :2;	//13:12	//0 : 9 tap	1 : 7 tap	2 : 5 tap
	UINT32 reg_crs_gain_res                 :1;	//14 //0: |c diff|로 [7:0] 선택	1: |c diff|/4로 [9:2] 선택
	UINT32 resvd0                           :1;
	UINT32 reg_cdiff_hcoef_sel              :2;	//17:16	//left/right diff의 coefficient (총 합은 255)	0 : h[0x00, 0x08, 0x08, 0x0A, 0x1E, 0xC8]/256	1 : h[0x00, 0x10, 0x10, 0x14, 0x40, 0x8C]/256
	UINT32 resvd1                           :10;
	UINT32 reg_crs_point                    :2;	//29:28	//
	UINT32 reg_crs_meth                     :2;	//31:30	//0 : (1조건) +  L/R 각각 내부 부호까지 같은가	1 : (2조건) +  L/R 서로 부호도 반대인가 	2 : L/R모두 chroma diff가 threshold보다 큰가
	};
}PE_E60_IFC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E628 RW
	UINT32 reg_crs_gain_y1                  :8;	//7:0	//
	UINT32 reg_crs_gain_x1                  :8;	//15:8	//
	UINT32 reg_crs_gain_y0                  :8;	//23:16	//
	UINT32 reg_crs_gain_x0                  :8;	//31:24	//
	};
}PE_E60_IFC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E62C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E630 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E634 RW
	UINT32 reg_ifc_en                       :1;	//0 //0 : 0ff / 1 : on
	UINT32 reg_clp_on                       :1;	//1 //0 : 0ff / 1 : Max clipping
	UINT32 resvd0                           :2;
	UINT32 reg_edge_en                      :1;	//4 //mmd en
	UINT32 resvd1                           :15;
	UINT32 reg_clp_tap                      :2;	//21:20	//0 : 13 tap	1 : 11 tap	2 : 9tap
	UINT32 reg_ifc_flt_sel                  :2;	//23:22	//3 : cross	2 : multi edge cedge	1 : yedge	0 : default
	UINT32 reg_debug_en                     :2;	//25:24	//0 : debug off	1 : blend debug on	2 : debug on
	UINT32 reg_debug_mode                   :4;	//29:26	//0 : operation mode	1 : cross check	2 : multi edge	3 : 	4 : cr edge gain	5 : cb edge gain	6 : y edge gain	7 : cross gain	8 : cross blend	9 : multi-edge blend	10 : 	11 : 2차미분	12 : 	13 : 1차미분
	UINT32 reg_bld_tap                      :2;	//31:30	//0: 옆에 2개 average	1: 옆에 1개, center average
	};
}PE_E60_IFC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E638 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E63C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E640 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E644 RW
	UINT32 resvd                            :16;
	UINT32 reg_crs_zero_th                  :8;	//23:16	//cross point에서 cb-cr을 0으로 보는 상한값
	UINT32 reg_dst_cdst_th                  :8;	//31:24	//좌우 필터곱해진 cdst 합의 차이
	};
}PE_E60_IFC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E648 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E64C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E650 RW
	UINT32 reg_medge_gain_y1                :8;	//7:0	//
	UINT32 reg_medge_gain_x1                :8;	//15:8	//
	UINT32 reg_medge_gain_y0                :8;	//23:16	//
	UINT32 reg_medge_gain_x0                :8;	//31:24	//1/3로
	};
}PE_E60_IFC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E654 RW
	UINT32 reg_crs_op_gain_isel             :2;	//1:0	//0 : max	1 : min	2 : average
	UINT32 reg_crs_op_gain_res              :1;	//2 //0: [7:0] 선택	1: [9:2] 선택
	UINT32 reg_crs_cdst_flt                 :3;	//5:3	//0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd0                           :1;
	UINT32 reg_crs_cdst_vmdn                :1;	//7 //5x5 median/max (v->h)
	UINT32 reg_crs_cdst_op_flt              :3;	//10:8	//0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd1                           :5;
	UINT32 reg_op_wgain_coef1               :2;	//17:16	//cross filter인 경우,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef2               :2;	//19:18	//cross filter인 경우,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef3               :2;	//21:20	//cross filter인 경우,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 resvd2                           :10;
	};
}PE_E60_IFC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E658 RW
	UINT32 reg_crs_op_gain_y1               :8;	//7:0	//
	UINT32 reg_crs_op_gain_x1               :8;	//15:8	//
	UINT32 reg_crs_op_gain_y0               :8;	//23:16	//
	UINT32 reg_crs_op_gain_x0               :8;	//31:24	//
	};
}PE_E60_IFC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E65C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E660 RW
	UINT32 resvd0                           :16;
	UINT32 reg_medge_op_th                  :8;	//23:16	//멀티엣지 영역 잡는것 (3라인, 갯수합)
	UINT32 reg_mmd_gain_en                  :1;	//24 //
	UINT32 reg_mmd_gain_flt                 :2;	//26:25	//0: off	1: 입력이121
	UINT32 reg_mmd_gain_tap                 :2;	//28:27	//0: 13	1: 11	2: 9
	UINT32 reg_mmd_gain_res                 :1;	//29 //0: [7:0] 선택	1: [9:2] 선택
	UINT32 resvd1                           :2;
	};
}PE_E60_IFC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E664 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_IFC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E668 RW
	UINT32 reg_mmd_gain_y1                  :8;	//7:0	//
	UINT32 reg_mmd_gain_x1                  :8;	//15:8	//
	UINT32 reg_mmd_gain_y0                  :8;	//23:16	//
	UINT32 reg_mmd_gain_x0                  :8;	//31:24	//
	};
}PE_E60_IFC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E66C RW
	UINT32 reg_sc_bnr_en                    :1;	//0 //
	UINT32 reg_sc_bnr_manual_h_en           :1;	//1 //
	UINT32 reg_scene_ch_flag                :1;	//2 //
	UINT32 reg_iir_en                       :1;	//3 //
	UINT32 reg_scale_mul_h                  :9;	//12:4	//
	UINT32 reg_scale_div_h                  :4;	//16:13	//
	UINT32 reg_sc_bnr_manual_v_en           :1;	//17 //
	UINT32 reg_sc_bnr_en_h                  :1;	//18 //
	UINT32 reg_sc_bnr_en_v                  :1;	//19 //
	UINT32 resvd                            :2;
	UINT32 reg_avg_scale_mul_h              :4;	//25:22	//
	UINT32 reg_avg_scale_div_h              :3;	//28:26	//
	UINT32 reg_max_index_diff_th            :3;	//31:29	//
	};
}PE_E60_SC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E670 RW
	UINT32 reg_post2_iir_gain               :8;	//7:0	//
	UINT32 reg_frm_cnt_th                   :8;	//15:8	//
	UINT32 reg_bin_ratio_th                 :8;	//23:16	//
	UINT32 reg_detect_th                    :8;	//31:24	//
	};
}PE_E60_SC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E674 RW
	UINT32 reg_bin_ratio_div                :8;	//7:0	//
	UINT32 reg_bin_ratio_mul                :8;	//15:8	//
	UINT32 reg_min_bin_th                   :8;	//23:16	//
	UINT32 reg_detector_iir_gain            :8;	//31:24	//
	};
}PE_E60_SC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E678 RW
	UINT32 reg_grid_th1                     :8;	//7:0	//
	UINT32 reg_grid_th2                     :8;	//15:8	//
	UINT32 reg_grid_th3                     :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_SC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E67C RW
	UINT32 reg_pos_gain_th                  :8;	//7:0	//
	UINT32 resvd                            :11;
	UINT32 reg_scale_div_v                  :4;	//22:19	//
	UINT32 reg_scale_mul_v                  :9;	//31:23	//
	};
}PE_E60_SC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E680 RW
	UINT32 reg_pos_gain_3                   :8;	//7:0	//block line 에서 +3 떨어진 지점의 gain
	UINT32 reg_pos_gain_2                   :8;	//15:8	//누적 diff_sum에 대한 scaling 값_분자
	UINT32 reg_pos_gain_1                   :8;	//23:16	//block line 에서 +1 떨어진 지점의 gain
	UINT32 reg_pos_gain_0                   :8;	//31:24	//block line 에서 +2 떨어진 지점의 gain
	};
}PE_E60_SC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E684 RW
	UINT32 reg_sc_bnr_debug_en              :1;	//0 //
	UINT32 reg_sc_bnr_debug_mode            :3;	//3:1	//
	UINT32 reg_avg_scale_div_v              :3;	//6:4	//
	UINT32 reg_avg_scale_mul_v              :4;	//10:7	//
	UINT32 resvd                            :13;
	UINT32 reg_acness_th                    :8;	//31:24	//
	};
}PE_E60_SC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E688 RW
	UINT32 pre_121_blur_en                  :1;	//0 //
	UINT32 pre_median_en                    :1;	//1 //
	UINT32 resvd                            :30;
	};
}PE_E60_C_PRE_BLUR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E69C RW
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//15:8	//
	UINT32 reg_acness_gain_h_g              :8;	//23:16	//
	UINT32 reg_acness_gain_h                :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6A0 RW
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//15:8	//
	UINT32 reg_acness_gain_v_g              :8;	//23:16	//
	UINT32 reg_acness_gain_v                :8;	//31:24	//
	};
}PE_E60_AC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6A4 RW
	UINT32 reg_fil_motion_x_th0             :8;	//7:0	//
	UINT32 reg_fil_motion_x_th1             :8;	//15:8	//
	UINT32 reg_fil_motion_x_th2             :8;	//23:16	//
	UINT32 reg_fil_motion_x_th3             :8;	//31:24	//
	};
}PE_E60_DC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6A8 RW
	UINT32 reg_fil_motion_y_th0             :8;	//7:0	//
	UINT32 reg_fil_motion_y_th1             :8;	//15:8	//
	UINT32 reg_fil_motion_y_th2             :8;	//23:16	//
	UINT32 reg_fil_motion_y_th3             :8;	//31:24	//
	};
}PE_E60_DC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6AC RW
	UINT32 reg_mmd_sel                      :2;	//1:0	//0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//15:8	//
	UINT32 reg_hist_bin_th1                 :8;	//23:16	//
	UINT32 reg_hist_bin_th2                 :8;	//31:24	//
	};
}PE_E60_SQM_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6B0 RW
	UINT32 reg_hist_bin_th3                 :8;	//7:0	//
	UINT32 reg_hist_bin_th4                 :8;	//15:8	//
	UINT32 reg_hist_bin_th5                 :8;	//23:16	//
	UINT32 reg_hist_bin_th6                 :8;	//31:24	//
	};
}PE_E60_SQM_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6B4 RW
	UINT32 reg_trans_mmd_th                 :8;	//7:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//19:10	//
	UINT32 reg_edf_mmd_th                   :8;	//27:20	//
	UINT32 resvd1                           :4;
	};
}PE_E60_SQM_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6B8 RW
	UINT32 reg_sqm_win_mode_x1              :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//28:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//30 //
	UINT32 reg_sqm_win_mode_en              :1;	//31 //
	};
}PE_E60_SQM_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6BC RW
	UINT32 reg_sqm_win_mode_y1              :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_SQM_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6C0 RW
	UINT32 reg_tp_binary_th                 :8;	//7:0	//
	UINT32 resvd                            :24;
	};
}PE_E60_TPD_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6C4 RW
	UINT32 reg_win_mode_x1                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_x0                  :13;	//28:16	//
	UINT32 resvd1                           :1;
	UINT32 reg_win_mode_mode                :1;	//30 //0: inside, 1: outside
	UINT32 reg_win_mode_en                  :1;	//31 //
	};
}PE_E60_WINDOW_MODE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6C8 RW
	UINT32 reg_win_mode_y1                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_y0                  :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_WINDOW_MODE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6D0 RO
	UINT32 acness_v_g                       :8;	//7:0	//
	UINT32 acness_h_g                       :8;	//15:8	//
	UINT32 acness_v                         :8;	//23:16	//
	UINT32 acness_h                         :8;	//31:24	//
	};
}PE_E60_DNR_STAT_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6D4 RO
	UINT32 bad_up_cnt                       :12;	//11:0	//
	UINT32 resvd                            :4;
	UINT32 acness_v_l                       :8;	//23:16	//
	UINT32 acness_h_l                       :8;	//31:24	//
	};
}PE_E60_DNR_STAT_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6D8 RO
	UINT32 acness_gain_v_l                  :8;	//7:0	//
	UINT32 acness_gain_h_l                  :8;	//15:8	//
	UINT32 acness_gain_v_g                  :8;	//23:16	//
	UINT32 acness_gain_h_g                  :8;	//31:24	//
	};
}PE_E60_DNR_STAT_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6DC RO
	UINT32 tdata0                           :32;
	};
}PE_E60_DNR_STAT_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6E0 RO
	UINT32 acness_gain_v                    :8;	//7:0	//
	UINT32 acness_gain_h                    :8;	//15:8	//
	UINT32 acness_v_iir                     :8;	//23:16	//
	UINT32 acness_h_iir                     :8;	//31:24	//
	};
}PE_E60_DNR_STAT_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6E4 RO
	UINT32 bin_ratio_iir_h                  :8;	//7:0	//
	UINT32 bin_ratio_v                      :8;	//15:8	//
	UINT32 bin_ratio_h                      :8;	//23:16	//
	UINT32 hys_cnt_v                        :3;	//26:24	//
	UINT32 hys_cnt_h                        :3;	//29:27	//
	UINT32 sc_bnr_flag_v                    :1;	//30 //
	UINT32 sc_bnr_flag_h                    :1;	//31 //
	};
}PE_E60_DNR_STAT_8_SC_BNR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6E8 RO
	UINT32 max_index_iir_h                  :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 max_index_v                      :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 max_index_h                      :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 bin_ratio_iir_v                  :8;	//31:24	//
	};
}PE_E60_DNR_STAT_9_SC_BNR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6EC RO
	UINT32 w_max_index_iir_v                :7;	//6:0	//
	UINT32 resvd                            :25;
	};
}PE_E60_DNR_STAT_10_SC_BNR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6F0 RO
	UINT32 e_hist_1                         :16;	//15:0	//
	UINT32 e_hist_0                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_11_SQM_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6F4 RO
	UINT32 e_hist_3                         :16;	//15:0	//
	UINT32 e_hist_2                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_12_SQM_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6F8 RO
	UINT32 e_hist_5                         :16;	//15:0	//
	UINT32 e_hist_4                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_13_SQM_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E6FC RO
	UINT32 e_hist_7                         :16;	//15:0	//
	UINT32 e_hist_6                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_14_SQM_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E700 RO
	UINT32 f_hist_1                         :16;	//15:0	//
	UINT32 f_hist_0                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_15_SQM_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E704 RO
	UINT32 f_hist_3                         :16;	//15:0	//
	UINT32 f_hist_2                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_16_SQM_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E708 RO
	UINT32 f_hist_5                         :16;	//15:0	//
	UINT32 f_hist_4                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_17_SQM_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E70C RO
	UINT32 f_hist_7                         :16;	//15:0	//
	UINT32 f_hist_6                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_18_SQM_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E710 RO
	UINT32 t_hist_1                         :16;	//15:0	//
	UINT32 t_hist_0                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_19_SQM_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E714 RO
	UINT32 t_hist_3                         :16;	//15:0	//
	UINT32 t_hist_2                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_20_SQM_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E718 RO
	UINT32 t_hist_5                         :16;	//15:0	//
	UINT32 t_hist_4                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_21_SQM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E71C RO
	UINT32 t_hist_7                         :16;	//15:0	//
	UINT32 t_hist_6                         :16;	//31:16	//
	};
}PE_E60_DNR_STAT_22_SQM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E720 RO
	UINT32 res_h_cnt_2                      :16;	//15:0	//
	UINT32 res_h_cnt_1                      :16;	//31:16	//
	};
}PE_E60_DNR_STAT_23_TPD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E724 RO
	UINT32 res_v_cnt_2                      :16;	//15:0	//
	UINT32 res_v_cnt_1                      :16;	//31:16	//
	};
}PE_E60_DNR_STAT_24_TPD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E728 RO
	UINT32 res_v_cnt_3                      :16;	//15:0	//
	UINT32 res_h_cnt_3                      :16;	//31:16	//
	};
}PE_E60_DNR_STAT_25_TPD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E730 RW
	UINT32 reg_fil_motion_x_th3             :8;	//7:0	//
	UINT32 reg_fil_motion_x_th2             :8;	//15:8	//
	UINT32 reg_fil_motion_x_th1             :8;	//23:16	//
	UINT32 reg_fil_motion_x_th0             :8;	//31:24	//
	};
}PE_E60_AC_BNR_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E734 RW
	UINT32 reg_fil_motion_y_th3             :8;	//7:0	//
	UINT32 reg_fil_motion_y_th2             :8;	//15:8	//
	UINT32 reg_fil_motion_y_th1             :8;	//23:16	//
	UINT32 reg_fil_motion_y_th0             :8;	//31:24	//
	};
}PE_E60_AC_BNR_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E738 RW
	UINT32 reg_tearing_y_1                  :4;	//3:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_tearing_y_0                  :4;	//11:8	//
	UINT32 resvd1                           :4;
	UINT32 reg_tearing_x_1                  :4;	//19:16	//
	UINT32 resvd2                           :4;
	UINT32 reg_tearing_x_0                  :4;	//27:24	//
	UINT32 resvd3                           :4;
	};
}PE_E60_VFILTER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E73C RW
	UINT32 reg_motion_x_3                   :8;	//7:0	//
	UINT32 reg_motion_x_2                   :8;	//15:8	//
	UINT32 reg_motion_x_1                   :8;	//23:16	//
	UINT32 reg_motion_x_0                   :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E740 RW
	UINT32 reg_motion_y_3                   :8;	//7:0	//
	UINT32 reg_motion_y_2                   :8;	//15:8	//
	UINT32 reg_motion_y_1                   :8;	//23:16	//
	UINT32 reg_motion_y_0                   :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E744 RW
	UINT32 reg_global_x_3                   :8;	//7:0	//
	UINT32 reg_global_x_2                   :8;	//15:8	//
	UINT32 reg_global_x_1                   :8;	//23:16	//
	UINT32 reg_global_x_0                   :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E748 RW
	UINT32 reg_global_y_3                   :8;	//7:0	//
	UINT32 reg_global_y_2                   :8;	//15:8	//
	UINT32 reg_global_y_1                   :8;	//23:16	//
	UINT32 reg_global_y_0                   :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E74C RW
	UINT32 reg_blend_x_3                    :8;	//7:0	//
	UINT32 reg_blend_x_2                    :8;	//15:8	//
	UINT32 reg_blend_x_1                    :8;	//23:16	//
	UINT32 reg_blend_x_0                    :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E750 RW
	UINT32 reg_blend_y_3                    :8;	//7:0	//
	UINT32 reg_blend_y_2                    :8;	//15:8	//
	UINT32 reg_blend_y_1                    :8;	//23:16	//
	UINT32 reg_blend_y_0                    :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E754 RW
	UINT32 reg_hmc_x_3                      :8;	//7:0	//
	UINT32 reg_hmc_x_2                      :8;	//15:8	//
	UINT32 reg_hmc_x_1                      :8;	//23:16	//
	UINT32 reg_hmc_x_0                      :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E758 RW
	UINT32 reg_hmc_y_3                      :8;	//7:0	//
	UINT32 reg_hmc_y_2                      :8;	//15:8	//
	UINT32 reg_hmc_y_1                      :8;	//23:16	//
	UINT32 reg_hmc_y_0                      :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E75C RW
	UINT32 reg_local_x_3                    :8;	//7:0	//
	UINT32 reg_local_x_2                    :8;	//15:8	//
	UINT32 reg_local_x_1                    :8;	//23:16	//
	UINT32 reg_local_x_0                    :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E760 RW
	UINT32 reg_hmc_y_3                      :8;	//7:0	//
	UINT32 reg_local_y_2                    :8;	//15:8	//
	UINT32 reg_local_y_1                    :8;	//23:16	//
	UINT32 reg_local_y_0                    :8;	//31:24	//
	};
}PE_E60_VFILTER_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E764 RW
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//0 //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//1 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_1st_out_rd_out_clip          :1;	//2 //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//7 //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//8 //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//9 //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//10 //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//11 //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_1st_out_rd_min_alpha         :8;	//27:20	//
	UINT32 reg_1st_out_rd_bit               :3;	//30:28	//
	UINT32 reg_1st_out_rd_on                :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E768 RW
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E76C RW
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E770 RW
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E774 RW
	UINT32 reg_1st_out_rd_init_yy           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E778 RW
	UINT32 reg_1st_out_rd_init_cb           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E77C RW
	UINT32 reg_1st_out_rd_init_cr           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E780 RW
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//7:4	//
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//11 //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//19:12	//
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//27:20	//
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E784 RW
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//29:28	//
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//31:30	//
	};
}PE_E60_REG_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E788 RW
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E78C RW
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//11:0	//
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E790 RW
	UINT32 reg_gain_x3                      :8;	//7:0	//
	UINT32 reg_gain_x2                      :8;	//15:8	//
	UINT32 reg_gain_x1                      :8;	//23:16	//
	UINT32 reg_gain_x0                      :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E794 RW
	UINT32 reg_gain_x7                      :8;	//7:0	//
	UINT32 reg_gain_x6                      :8;	//15:8	//
	UINT32 reg_gain_x5                      :8;	//23:16	//
	UINT32 reg_gain_x4                      :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E798 RW
	UINT32 reg_gain_y3                      :8;	//7:0	//
	UINT32 reg_gain_y2                      :8;	//15:8	//
	UINT32 reg_gain_y1                      :8;	//23:16	//
	UINT32 reg_gain_y0                      :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E79C RW
	UINT32 reg_gain_y7                      :8;	//7:0	//
	UINT32 reg_gain_y6                      :8;	//15:8	//
	UINT32 reg_gain_y5                      :8;	//23:16	//
	UINT32 reg_gain_y4                      :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7A0 RW
	UINT32 reg_lti_en                       :1;	//0 //
	UINT32 reg_lti_clipping_mode            :1;	//1 //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap                      :2;	//4:3	//
	UINT32 resvd1                           :3;
	UINT32 reg_lti_gain                     :8;	//15:8	//
	UINT32 resvd2                           :4;
	UINT32 reg_ycm_c_gain                   :4;	//23:20	//
	UINT32 reg_ycm_y_gain                   :4;	//27:24	//
	UINT32 reg_ycm_band_sel                 :3;	//30:28	//
	UINT32 reg_ycm_en                       :1;	//31 //
	};
}PE_E60_REG_CTI_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7A4 RW
	UINT32 reg_lti_coring_th0               :8;	//7:0	//
	UINT32 reg_lti_coring_th1               :8;	//15:8	//
	UINT32 reg_lti_coring_sm                :3;	//18:16	//
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//21:20	//
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//31:24	//
	};
}PE_E60_REG_CTI_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7A8 RW
	UINT32 reg_small_mmd_flat_th            :8;	//7:0	//
	UINT32 reg_large_mmd_flat_th            :8;	//15:8	//
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//28 //
	UINT32 reg_mmd_dist_kernal_width        :2;	//30:29	//
	UINT32 reg_mmd_dist_gain_en             :1;	//31 //
	};
}PE_E60_REG_MNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7AC RW
	UINT32 reg_dist_gain_x3                 :8;	//7:0	//
	UINT32 reg_dist_gain_x2                 :8;	//15:8	//
	UINT32 reg_dist_gain_x1                 :8;	//23:16	//
	UINT32 reg_dist_gain_x0                 :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7B0 RW
	UINT32 reg_dist_gain_y3                 :8;	//7:0	//
	UINT32 reg_dist_gain_y2                 :8;	//15:8	//
	UINT32 reg_dist_gain_y1                 :8;	//23:16	//
	UINT32 reg_dist_gain_y0                 :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7B4 RW
	UINT32 reg_chroma_gain_x3               :8;	//7:0	//
	UINT32 reg_chroma_gain_x2               :8;	//15:8	//
	UINT32 reg_chroma_gain_x1               :8;	//23:16	//
	UINT32 reg_chroma_gain_x0               :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7B8 RW
	UINT32 reg_chroma_gain_y3               :8;	//7:0	//
	UINT32 reg_chroma_gain_y2               :8;	//15:8	//
	UINT32 reg_chroma_gain_y1               :8;	//23:16	//
	UINT32 reg_chroma_gain_y0               :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7BC RW
	UINT32 reg_i_sel_mmd_x3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_x2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_x1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_x0                 :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7C0 RW
	UINT32 reg_i_sel_mmd_y3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_y2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_y1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_y0                 :8;	//31:24	//
	};
}PE_E60_REG_MNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7C4 RW
	UINT32 reg_2nd_out_rd_init_yy           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7C8 RW
	UINT32 reg_2nd_out_rd_init_cb           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7CC RW
	UINT32 reg_2nd_out_rd_init_cr           :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7D0 RW
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7D4 RW
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7D8 RW
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7DC RW
	UINT32 reg_blur_lb_var_cut_res          :4;	//3:0	//>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//6 //
	UINT32 reg_l6_var_2x2_bit               :1;	//7 //12b인 L6_var를 10b으로 cut할 때, 1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//13:8	//
	UINT32 reg_1st_debug_en                 :1;	//14 //
	UINT32 reg_l6_var_csc_en                :1;	//15 //ND에선 사용 안 함
	UINT32 reg_force_block_no_h             :6;	//21:16	//
	UINT32 reg_4k_5x3_mode_en               :1;	//22 //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//23 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//24 //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//25 //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//29:26	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_2x2_blur	11: skin_gain	12: face_gain	13: face_skin_gain	14: input_blur
	UINT32 reg_force_block_no_en            :1;	//30 //
	UINT32 reg_decon_1st_en                 :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7E0 RW
	UINT32 reg_var_chroma_en                :1;	//0 //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//2 //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//4 //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//6:5	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//8:7	//0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//11:9	//0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//12 //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//13 //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//14 //not used in O20
	UINT32 resvd2                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//16 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//17 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//18 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//19 //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//23:20	//
	UINT32 reg_var_h_gain                   :4;	//27:24	//
	UINT32 reg_var_cut_resolution           :4;	//31:28	//
	};
}PE_E60_REG_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7E4 RW
	UINT32 reg_decon_diff_x_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_x_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_x_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_x_th3             :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7E8 RW
	UINT32 reg_decon_diff_y_th0             :8;	//7:0	//
	UINT32 reg_decon_diff_y_th1             :8;	//15:8	//
	UINT32 reg_decon_diff_y_th2             :8;	//23:16	//
	UINT32 reg_decon_diff_y_th3             :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7EC RW
	UINT32 reg_decon_var_x_th2              :10;	//9:0	//
	UINT32 reg_decon_var_x_th1              :10;	//19:10	//
	UINT32 reg_decon_var_x_th0              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7F0 RW
	UINT32 reg_decon_var_y_th1              :10;	//9:0	//
	UINT32 reg_decon_var_y_th0              :10;	//19:10	//
	UINT32 reg_decon_var_x_th3              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7F4 RW
	UINT32 reg_decon_luma_x_th0             :10;	//9:0	//
	UINT32 reg_decon_var_y_th3              :10;	//19:10	//
	UINT32 reg_decon_var_y_th2              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7F8 RW
	UINT32 reg_decon_luma_x_th3             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th2             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th1             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E7FC RW
	UINT32 reg_decon_luma_x_th6             :10;	//9:0	//
	UINT32 reg_decon_luma_x_th5             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th4             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E800 RW
	UINT32 reg_decon_luma_y_th1             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th0             :10;	//19:10	//
	UINT32 reg_decon_luma_x_th7             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E804 RW
	UINT32 reg_decon_luma_y_th4             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th3             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th2             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E808 RW
	UINT32 reg_decon_luma_y_th7             :10;	//9:0	//
	UINT32 reg_decon_luma_y_th6             :10;	//19:10	//
	UINT32 reg_decon_luma_y_th5             :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E80C RW
	UINT32 reg_block_size_v                 :8;	//7:0	//
	UINT32 reg_block_size_h                 :8;	//15:8	//
	UINT32 reg_block_no_v                   :6;	//21:16	//
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//29:24	//
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E810 RW
	UINT32 reg_last_block_size_v            :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//19:16	//
	UINT32 reg_diff_shift                   :3;	//22:20	//
	UINT32 reg_osd_run_mode                 :1;	//23 //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//24 //
	UINT32 reg_alpha_blur_mode              :2;	//26:25	//0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//28:27	//
	UINT32 reg_diff_use_seldiff             :1;	//29 //
	UINT32 reg_diff_calc_mode               :2;	//31:30	//
	};
}PE_E60_REG_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E814 RW
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//9:0	//not used in m16p3
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//19:10	//not used in m16p3
	UINT32 reg_lb_var_cut_res               :4;	//23:20	//cut resolution after (var * LB_var)
	UINT32 reg_master_gain                  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E818 RW
	UINT32 reg_l6_var_x_th2                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_x_th1                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_var_x_th0                 :10;	//29:20	//revived in O20
	UINT32 reg_lb_var_opt                   :1;	//30 //0: L6_var, 1: L6_var 2x2smooth
	UINT32 reg_lb_var_en                    :1;	//31 //use L6_var when making var map
	};
}PE_E60_REG_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E81C RW
	UINT32 reg_l6_var_y_th1                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_y_th0                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_var_x_th3                 :10;	//29:20	//revived in O20
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E820 RW
	UINT32 reg_l6_var_y_th3                 :10;	//9:0	//revived in O20
	UINT32 reg_l6_var_y_th2                 :10;	//19:10	//revived in O20
	UINT32 reg_l6_pel_trunc                 :2;	//21:20	//
	UINT32 reg_var_v_cut                    :2;	//23:22	//
	UINT32 reg_var_h_cut                    :2;	//25:24	//
	UINT32 reg_var_t7_offset                :2;	//27:26	//
	UINT32 reg_decon_rd_simple_bit          :3;	//30:28	//
	UINT32 reg_decon_rd_simple_on           :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E824 RW
	UINT32 reg_decon_rd_simple_init_yy      :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E828 RW
	UINT32 reg_decon_rd_simple_init_cb      :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E82C RW
	UINT32 reg_decon_rd_simple_init_cr      :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E830 RW
	UINT32 reg_rd_min_pel_cb                :12;	//11:0	//
	UINT32 reg_rd_min_pel_yy                :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//30:28	//
	UINT32 reg_decon_rd_on                  :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E834 RW
	UINT32 reg_rd_max_pel_yy                :12;	//11:0	//
	UINT32 reg_rd_min_pel_cr                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E838 RW
	UINT32 reg_rd_max_pel_cr                :12;	//11:0	//
	UINT32 reg_rd_max_pel_cb                :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E83C RW
	UINT32 reg_rd_init_yy                   :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E840 RW
	UINT32 reg_rd_init_cb                   :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E844 RW
	UINT32 reg_rd_init_cr                   :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E848 RW
	UINT32 reg_motion_gain_x3               :8;	//7:0	//
	UINT32 reg_motion_gain_x2               :8;	//15:8	//
	UINT32 reg_motion_gain_x1               :8;	//23:16	//
	UINT32 reg_motion_gain_x0               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E84C RW
	UINT32 reg_motion_gain_y3               :8;	//7:0	//
	UINT32 reg_motion_gain_y2               :8;	//15:8	//
	UINT32 reg_motion_gain_y1               :8;	//23:16	//
	UINT32 reg_motion_gain_y0               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E850 RW
	UINT32 reg_bbd_y0                       :12;	//11:0	//
	UINT32 reg_bbd_x0                       :12;	//23:12	//
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//28 //
	UINT32 reg_blur2_sim_en                 :1;	//29 //
	UINT32 reg_amf_lut_bit                  :1;	//30 //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E854 RW
	UINT32 reg_bbd_y1                       :12;	//11:0	//
	UINT32 reg_bbd_x1                       :12;	//23:12	//
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//28:26	//
	UINT32 reg_blur2_sim_ratio              :3;	//31:29	//
	};
}PE_E60_REG_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E858 RW
	UINT32 reg_lut_blur_sim_x3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_x2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_x1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_x0              :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E85C RW
	UINT32 reg_lut_blur_sim_y3              :8;	//7:0	//
	UINT32 reg_lut_blur_sim_y2              :8;	//15:8	//
	UINT32 reg_lut_blur_sim_y1              :8;	//23:16	//
	UINT32 reg_lut_blur_sim_y0              :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E860 RW
	UINT32 reg_lut_skin_yy_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_yy_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_yy_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_yy_x0               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E864 RW
	UINT32 reg_lut_skin_cb_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cb_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cb_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cb_x0               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E868 RW
	UINT32 reg_lut_skin_cr_x3               :8;	//7:0	//
	UINT32 reg_lut_skin_cr_x2               :8;	//15:8	//
	UINT32 reg_lut_skin_cr_x1               :8;	//23:16	//
	UINT32 reg_lut_skin_cr_x0               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E86C RW
	UINT32 reg_lut_skin_y3                  :8;	//7:0	//
	UINT32 reg_lut_skin_y2                  :8;	//15:8	//
	UINT32 reg_lut_skin_y1                  :8;	//23:16	//
	UINT32 reg_lut_skin_y0                  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E870 RW
	UINT32 reg_lut_face_x3                  :8;	//7:0	//
	UINT32 reg_lut_face_x2                  :8;	//15:8	//
	UINT32 reg_lut_face_x1                  :8;	//23:16	//
	UINT32 reg_lut_face_x0                  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E874 RW
	UINT32 reg_lut_face_y3                  :8;	//7:0	//
	UINT32 reg_lut_face_y2                  :8;	//15:8	//
	UINT32 reg_lut_face_y1                  :8;	//23:16	//
	UINT32 reg_lut_face_y0                  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E878 RW
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//19 //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//27:20	//
	UINT32 reg_face_shft                    :2;	//29:28	//0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//30 //
	UINT32 reg_skin_en                      :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E87C RW
	UINT32 reg_l6_var_diff_dist_h           :4;	//3:0	//
	UINT32 reg_l6_var_diff_dist_w           :4;	//7:4	//
	UINT32 resvd                            :24;
	};
}PE_E60_REG_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E880 RW
	UINT32 reg_l6_var_diff_th_cr            :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_cb            :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_yy            :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E884 RW
	UINT32 reg_l6_var_diff_th_yy3           :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_yy2           :10;	//19:10	//
	UINT32 resvd                            :12;
	};
}PE_E60_REG_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E888 RW
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E88C RW
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//9:0	//
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//19:10	//
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E890 RW
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E894 RW
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//7:0	//
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//15:8	//
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//23:16	//
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E898 RW
	UINT32 reg_psp_blur_y_max               :8;	//7:0	//
	UINT32 reg_psp_blur_y_min               :8;	//15:8	//
	UINT32 reg_psp_blur_x_max               :8;	//23:16	//
	UINT32 reg_psp_blur_x_min               :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E89C RW
	UINT32 reg_psp_blend_x_th3              :8;	//7:0	//
	UINT32 reg_psp_blend_x_th2              :8;	//15:8	//
	UINT32 reg_psp_blend_x_th1              :8;	//23:16	//
	UINT32 reg_psp_blend_x_th0              :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8A0 RW
	UINT32 reg_psp_blend_y_th1              :8;	//7:0	//
	UINT32 reg_psp_blend_y_th0              :8;	//15:8	//
	UINT32 reg_psp_blend_x_th5              :8;	//23:16	//
	UINT32 reg_psp_blend_x_th4              :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8A4 RW
	UINT32 reg_psp_blend_y_th5              :8;	//7:0	//
	UINT32 reg_psp_blend_y_th4              :8;	//15:8	//
	UINT32 reg_psp_blend_y_th3              :8;	//23:16	//
	UINT32 reg_psp_blend_y_th2              :8;	//31:24	//
	};
}PE_E60_REG_DC_BNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8A8 RW
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//15:8	//
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//23:16	//
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8AC RW
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_v_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8B0 RW
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//11:0	//
	UINT32 reg_l6_var_h_diff_th             :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8B4 RW
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_max_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8B8 RW
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//11:0	//
	UINT32 reg_l6_var_total_diff_low_th     :12;	//23:12	//
	UINT32 resvd                            :8;
	};
}PE_E60_REG_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8BC RW
	UINT32 reg_diff_mul                     :4;	//3:0	//
	UINT32 reg_2nd_diff_shift               :3;	//6:4	//
	UINT32 reg_2nd_alpha_blur_mode          :1;	//7 //0: no blur, 1: 5x1 blur
	UINT32 reg_2nd_debug_mode               :3;	//10:8	//0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: blur result	6: osd_flag	7: bypass
	UINT32 reg_odd_sel                      :1;	//11 //
	UINT32 reg_2nd_osd_run_mode             :1;	//12 //
	UINT32 reg_2nd_rd_simple_bit            :3;	//15:13	//
	UINT32 reg_2nd_rd_simple_on             :1;	//16 //
	UINT32 reg_input_csc_en                 :1;	//17 //
	UINT32 reg_2nd_var_v_gain               :2;	//19:18	//
	UINT32 reg_2nd_var_h_gain               :2;	//21:20	//
	UINT32 reg_2nd_var_cut_resolution       :3;	//24:22	//
	UINT32 reg_2nd_var_chroma_en            :1;	//25 //
	UINT32 reg_2nd_var_sel_tmp              :2;	//27:26	//0: 3x3, 1: 9x3, 2: 17x3, 3: 18x3
	UINT32 reg_2nd_fil_sel_tmp              :2;	//29:28	//0: 3x3, 1: 9x3, 2: 17x3
	UINT32 reg_2nd_debug_en                 :1;	//30 //
	UINT32 reg_decon_2nd_en                 :1;	//31 //
	};
}PE_E60_REG_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8C0 RW
	UINT32 reg_2nd_luma_x_th2               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th1               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th0               :10;	//29:20	//
	UINT32 resvd                            :1;
	UINT32 reg_444_mode                     :1;	//31 //0: repeat, 1: avg
	};
}PE_E60_REG_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8C4 RW
	UINT32 reg_2nd_luma_x_th5               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th4               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th3               :10;	//29:20	//
	UINT32 reg_2nd_luma_bit_opt             :2;	//31:30	//0: lower 10bit w/ clipping, 1: mid 10bit w/ clipping, 2: higher 10bit
	};
}PE_E60_REG_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8C8 RW
	UINT32 reg_2nd_luma_y_th0               :10;	//9:0	//
	UINT32 reg_2nd_luma_x_th7               :10;	//19:10	//
	UINT32 reg_2nd_luma_x_th6               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8CC RW
	UINT32 reg_2nd_luma_y_th3               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th2               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th1               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8D0 RW
	UINT32 reg_2nd_luma_y_th6               :10;	//9:0	//
	UINT32 reg_2nd_luma_y_th5               :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th4               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8D4 RW
	UINT32 reg_2nd_var_x_th1                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th0                :10;	//19:10	//
	UINT32 reg_2nd_luma_y_th7               :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8D8 RW
	UINT32 reg_2nd_var_y_th0                :10;	//9:0	//
	UINT32 reg_2nd_var_x_th3                :10;	//19:10	//
	UINT32 reg_2nd_var_x_th2                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8DC RW
	UINT32 reg_2nd_var_y_th3                :10;	//9:0	//
	UINT32 reg_2nd_var_y_th2                :10;	//19:10	//
	UINT32 reg_2nd_var_y_th1                :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8E0 RW
	UINT32 reg_2nd_diff_x_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_x_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_x_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_x_th3               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8E4 RW
	UINT32 reg_2nd_diff_y_th0               :8;	//7:0	//
	UINT32 reg_2nd_diff_y_th1               :8;	//15:8	//
	UINT32 reg_2nd_diff_y_th2               :8;	//23:16	//
	UINT32 reg_2nd_diff_y_th3               :8;	//31:24	//
	};
}PE_E60_REG_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8E8 RW
	UINT32 reg_2nd_rd_simple_init_yy        :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8EC RW
	UINT32 reg_2nd_rd_simple_init_cb        :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8F0 RW
	UINT32 reg_2nd_rd_simple_init_cr        :32;	//31:0	//
	};
}PE_E60_REG_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8F4 RW
	UINT32 reg_overlap_hsize                :8;	//7:0	//* final release로 인해 RTL에서는 "reg_overlap"으로 사용중(다음버전에 명칭 업데이트 예정)	가용범위 : 4~128 (0~3 사이의 값 입력시 오류 발생)
	UINT32 reg_trans_pos                    :6;	//13:8	//h_block 개수보다 작아야 함
	UINT32 resvd0                           :10;
	UINT32 reg_original_size_set            :1;	//24 //block_info에서 ND의 split 이전의 오리지널 입력 영상에 대한 세팅(E60에서 8K 4split/4K 2split은 코어 입력이 동일하기 때문에 별도의 구분 필요)	0: 8K	1: 4K
	UINT32 resvd1                           :3;
	UINT32 reg_col_index                    :2;	//29:28	//* final release로 인해 RTL에서는 "reg_boundary_side"으로 사용중(다음버전에 명칭 업데이트 예정)	Split/Merger에 의해서 Decontour 모듈은 3 2 1 0 으로 인덱싱 되어있으나 설정은 아래의 숫자를 참조	내부 동작적인 측면에서 1과 2는 똑같은 형태(튜닝 등에 의해서 위치를 표시하기 위해 구별)	0 : Core 0(Left side)	1 : Core 1(Middle side)	2 : Core 2(Middle side)	3 : Core 3 (Right side)
	UINT32 resvd2                           :1;
	UINT32 reg_col_mode_en                  :1;	//31 //* final release로 인해 RTL에서는 "reg_boundary_en"으로 사용중(다음버전에 명칭 업데이트 예정)	0 : col_mode off	1 : col_mode on
	};
}PE_E60_REG_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8F8 RW
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//1:0	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//3:2	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//5:4	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//7:6	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//9:8	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//11:10	//0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//28 //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//29 //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//30 //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E8FC RW
	UINT32 reg_rd_roi_x1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_REG_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E900 RW
	UINT32 reg_rd_roi_y1                    :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_REG_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E904 RW
	UINT32 reg_1st_rd_luma_x1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x0               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_prev_x                   :12;	//31:20	//Defualt: 30	이전 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_E60_REG_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E908 RW
	UINT32 reg_1st_rd_luma_x3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_1st_rd_luma_x2               :10;	//19:10	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 reg_out_next_x                   :12;	//31:20	//Defualt: 40	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	};
}PE_E60_REG_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E90C RW
	UINT32 reg_1st_rd_luma_x5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_prev_y                   :7;	//30:24	//Defualt: 120	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_E60_REG_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E910 RW
	UINT32 reg_1st_rd_luma_x7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :2;
	UINT32 reg_out_next_y                   :7;	//30:24	//Defualt: 121	다음 코어애 보낼 값을 read 하는 위치(active 영역에 대한 좌표)
	UINT32 resvd2                           :1;
	};
}PE_E60_REG_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E914 RW
	UINT32 reg_1st_rd_luma_y1               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E918 RW
	UINT32 reg_1st_rd_luma_y3               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E91C RW
	UINT32 reg_1st_rd_luma_y5               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E920 RW
	UINT32 reg_1st_rd_luma_y7               :10;	//9:0	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//21:12	//1st의 이 값을 2nd_rd_luma와 공유(final release로 인해서 명칭 수정 불가. 다음 버전 업데이트)
	UINT32 resvd1                           :10;
	};
}PE_E60_REG_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E924 RW
	UINT32 reg_face_demo_x1                 :13;	//12:0	//x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//28:16	//x0 < pos_x < x1 일때 동작(2 배수로 설정 입력)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//31 //face gain demo mode 동작
	};
}PE_E60_REG_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900E928 RW
	UINT32 reg_face_demo_y1                 :13;	//12:0	//y0 < pos_y < y1 일때 동작
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//28:16	//y0 < pos_y < y1 일때 동작
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED00 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
}PE_E60_PSP_CTRL00_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED04 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
}PE_E60_PSP_CTRL01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED08 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 reg_cg_disp_clk                  :1;	//9 //clock gating on disp_clk
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
}PE_E60_PSP_CTRL02_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED0C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
}PE_E60_EDGE_TH_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED10 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
}PE_E60_FG_POSITION_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED14 RW
	UINT32 reg_perspect_lut_x_0             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_X0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED18 RW
	UINT32 reg_perspect_lut_x_1             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_X1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED1C RW
	UINT32 reg_perspect_lut_x_2             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_X2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED20 RW
	UINT32 reg_perspect_lut_x_3             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_X3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED24 RW
	UINT32 reg_perspect_lut_y_0             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_Y0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED28 RW
	UINT32 reg_perspect_lut_y_1             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_Y1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED2C RW
	UINT32 reg_perspect_lut_y_2             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_Y2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED30 RW
	UINT32 reg_perspect_lut_y_3             :32;	//31:0	//
	};
}PE_E60_PERSPECT_LUT_Y3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED34 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
}PE_E60_PROB_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED38 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (1)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
}PE_E60_ELLIPS_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED3C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
}PE_E60_PROB_DIFF_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED40 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
}PE_E60_OBJECT_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED44 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
}PE_E60_BLUR_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED48 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain의 출력 중 psp_gain을 display로 전환
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain 적용
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound 를 enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound 를 disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound 를 disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :5;	//20:16	//debug (SYNC_DLY + 4)
	UINT32 resvd4                           :11;
	};
}PE_E60_DISPLAY_DEBUG_MAP_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED4C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
}PE_E60_PSP_IIR_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED50 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
}PE_E60_PSP_GAIN_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED54 RO
	UINT32 h1_pos                           :7;	//6:0	//
	UINT32 h2_pos                           :7;	//13:7	//
	UINT32 w1_pos                           :7;	//20:14	//
	UINT32 w2_pos                           :7;	//27:21	//
	UINT32 r_edge_total_lsb                 :4;	//31:28	//r_edge_total[4:1]
	};
}PE_E60_PSP_DBG_MON00_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED58 RO
	UINT32 out_max_flat_length_h            :7;	//6:0	//
	UINT32 out_max_flat_length_w            :7;	//13:7	//
	UINT32 r_edge_total_msb                 :18;	//31:14	//r_edge_total[22:5]
	};
}PE_E60_PSP_DBG_MON01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED5C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
}PE_E60_VRTX_CPC_CTRL_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED60 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED64 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED68 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF45_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED6C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF67_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED70 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_BLUR_HCOEF8_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED74 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_VCOEF01_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED78 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_VCOEF23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED7C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_BLUR_VCOEF4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED80 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED84 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED88 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED8C RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED90 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED94 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_5_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED98 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_6_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900ED9C RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_7_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDA0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_8_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDA4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_9_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDA8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_10_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDAC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_11_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDB0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_12_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDB4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_13_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDB8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_14_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDBC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_15_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDC0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_16_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDC4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_17_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDC8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_18_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDCC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_19_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDD0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_20_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDD4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_21_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDD8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_22_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDDC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_23_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDE0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_24_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDE4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_25_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDE8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_26_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDEC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_27_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDF0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_28_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDF4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_29_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDF8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_30_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EDFC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_31_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE00 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_L5_GAIN_LUT1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE04 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_L5_GAIN_LUT2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE08 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_L0_GAIN_LUT1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE0C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_L0_GAIN_LUT2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE10 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
}PE_E60_EDGE_WIN_H_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE14 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
}PE_E60_EDGE_WIN_V_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE18 RO
	UINT32 edge0_fg                         :23;	//22:0	//FG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE0_FG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE1C RO
	UINT32 edge0_bg                         :23;	//22:0	//BG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE0_BG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE20 RO
	UINT32 edge1_fg                         :23;	//22:0	//FG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE1_FG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE24 RO
	UINT32 edge1_bg                         :23;	//22:0	//BG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE1_BG_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE28 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
}PE_E60_PSP_IIR1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE2C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
}PE_E60_BG_MEASURE_CTRL_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE30 RO
	UINT32 line_unit0                       :16;	//15:0	//
	UINT32 line_unit1                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ0_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE34 RO
	UINT32 line_unit2                       :16;	//15:0	//
	UINT32 line_unit3                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ1_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE38 RO
	UINT32 line_unit4                       :16;	//15:0	//
	UINT32 line_unit5                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ2_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE3C RO
	UINT32 line_unit6                       :16;	//15:0	//
	UINT32 line_unit7                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ3_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EE40 RO
	UINT32 line_unit8                       :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_BG_MEASURE_READ4_O_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF00 RW
	UINT32 reg_img_wid                      :12;	//11:0	//horizontal resolution
	UINT32 resvd0                           :4;
	UINT32 reg_img_hei                      :12;	//27:16	//vertical resolution
	UINT32 resvd1                           :4;
	};
}PE_E60_PSP_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF04 RW
	UINT32 reg_blk_wid                      :6;	//5:0	//Block size
	UINT32 resvd0                           :2;
	UINT32 reg_blk_hei                      :6;	//13:8	//Block size
	UINT32 resvd1                           :2;
	UINT32 reg_l5_wid                       :7;	//22:16	//Number of hblock
	UINT32 resvd2                           :1;
	UINT32 reg_l5_hei                       :7;	//30:24	//Number of vblock
	UINT32 resvd3                           :1;
	};
}PE_E60_PSP_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF08 RW
	UINT32 reg_vs_inv                       :1;	//0 //vs inversion
	UINT32 reg_psp_en                       :1;	//1 //psp enable : 전체 enable
	UINT32 reg_hist_sel                     :2;	//3:2	//histogram selection	00 : YG	01 : CB	10 : CR
	UINT32 reg_repeat_h_num                 :5;	//8:4	//line 경계에서 repeat 시킬 h pixel 개수
	UINT32 resvd                            :1;
	UINT32 reg_repeat_v_num                 :5;	//14:10	//frame 경계에서 repeat 시킬 v line 개수
	UINT32 reserved                         :1;	//15 //fg memory의 mee off
	UINT32 reg_margin_hei                   :8;	//23:16	//edge extraction의 V margin
	UINT32 reg_margin_wid                   :8;	//31:24	//edge extraction의 H margin
	};
}PE_E60_PSP_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF0C RW
	UINT32 reg_edge_th                      :13;	//12:0	//threshold value for edge  : Edge threshold difference
	UINT32 resvd                            :3;
	UINT32 reg_w_box_th                     :8;	//23:16	//threshold value for w box : 후보 box 영역에 대한 threshold
	UINT32 reg_h_box_th                     :8;	//31:24	//threshold value for h box : 후보 box 영역에 대한 threshold
	};
}PE_E60_EDGE_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF10 RW
	UINT32 reg_force_w1_pos                 :7;	//6:0	//(w1, h1)
	UINT32 resvd0                           :1;
	UINT32 reg_force_h1_pos                 :7;	//14:8	//(w1, h1)
	UINT32 resvd1                           :1;
	UINT32 reg_force_w2_pos                 :7;	//22:16	//(w2, h2)
	UINT32 resvd2                           :1;
	UINT32 reg_force_h2_pos                 :7;	//30:24	//(w2, h2)
	UINT32 reg_force_pos_en                 :1;	//31 //forced FG box posotion
	};
}PE_E60_FG_POSITION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF14 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF18 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF1C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF20 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF24 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF28 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF2C RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF30 RW
	UINT32 reserved                         :32;	//31:0	//
	};
}PE_E60_RESERVED7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF34 RW
	UINT32 reg_bg_prob_factor               :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_fg_prob_factor               :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_stat_flat_w_mul              :4;	//19:16	//
	UINT32 reg_stat_flat_h_mul              :4;	//23:20	//
	UINT32 resvd2                           :8;
	};
}PE_E60_PROB_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF38 RW
	UINT32 reg_ellipse_master               :8;	//7:0	//gain * master
	UINT32 reg_e_mul_a                      :9;	//16:8	//4.5bit
	UINT32 resvd0                           :3;
	UINT32 reg_e_mul_b                      :9;	//28:20	//4.5bit
	UINT32 resvd1                           :1;
	UINT32 reg_ellipse_disable              :1;	//30 //ellipse_gain disable (only face mode on)
	UINT32 reg_fg_mul_ellipse_en            :1;	//31 //enable
	};
}PE_E60_ELLIPS_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF3C RW
	UINT32 reg_ellipse_offset               :8;	//7:0	//parameter of ellipse offset
	UINT32 reg_bg_diff_mul                  :10;	//17:8	//6.4bit
	UINT32 resvd0                           :2;
	UINT32 reg_fg_diff_mul                  :10;	//29:20	//6.4bit
	UINT32 resvd1                           :2;
	};
}PE_E60_PROB_DIFF_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF40 RW
	UINT32 reg_p_offset                     :8;	//7:0	//p offset (알고리즘 parameter)
	UINT32 reg_e_offset                     :8;	//15:8	//e offset (알고리즘 parameter)
	UINT32 reg_dbg_map_sel                  :3;	//18:16	//map selection	0 : prob_map	1 : ellips_gain	2 : prob_fg_map	3 : prob_bg_map	4 : prob_diff_map	5 : candidate box	6 : L5 image
	UINT32 resvd                            :13;
	};
}PE_E60_OBJECT_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF44 RW
	UINT32 reg_blur_en                      :1;	//0 //9x5 spatial filter enable
	UINT32 resvd                            :31;
	};
}PE_E60_BLUR_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF48 RW
	UINT32 reg_disp_gain_l0                 :1;	//0 //psp_make_L0_gain의 출력 중 psp_gain을 display로 전환
	UINT32 resvd0                           :3;
	UINT32 reg_disp_gain_vrtx               :1;	//4 //vertex cpc gain 적용
	UINT32 resvd1                           :3;
	UINT32 reg_bot_bnd_enable               :1;	//8 //bottom bound 를 enable
	UINT32 reg_left_bnd_disable             :1;	//9 //left bound 를 disable
	UINT32 reg_top_bnd_disable              :1;	//10 //top bound 를 disable
	UINT32 resvd2                           :1;
	UINT32 reg_fifo_detour                  :1;	//12 //debug
	UINT32 resvd3                           :2;
	UINT32 reg_pic_end_status               :1;	//15 //debug
	UINT32 reg_dst_valid_count              :5;	//20:16	//debug (SYNC_DLY + 4)
	UINT32 resvd4                           :11;
	};
}PE_E60_DISPLAY_DEBUG_MAP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF4C RW
	UINT32 reg_psp_iir_alpha                :6;	//5:0	//IIR Alpha blending rate (0 ~ 1) 	6bit 기준이고 3A = 90%
	UINT32 resvd                            :25;
	UINT32 reg_psp_gain_init                :1;	//31 //IIR initial시 사용( data reset)
	};
}PE_E60_PSP_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF50 RW
	UINT32 psp_gain                         :1;	//0 //no use
	UINT32 psp_gain_dbg                     :1;	//1 //no use
	UINT32 resvd                            :30;
	};
}PE_E60_PSP_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF54 RO
	UINT32 h1_pos                           :7;	//6:0	//
	UINT32 h2_pos                           :7;	//13:7	//
	UINT32 w1_pos                           :7;	//20:14	//
	UINT32 w2_pos                           :7;	//27:21	//
	UINT32 r_edge_total_lsb                 :4;	//31:28	//r_edge_total[4:1]
	};
}PE_E60_PSP_DBG_MON00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF58 RO
	UINT32 out_max_flat_length_h            :7;	//6:0	//
	UINT32 out_max_flat_length_w            :7;	//13:7	//
	UINT32 r_edge_total_msb                 :18;	//31:14	//r_edge_total[22:5]
	};
}PE_E60_PSP_DBG_MON01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF5C RW
	UINT32 reg_vrtx_gain_tl_i               :8;	//7:0	//
	UINT32 reg_vrtx_gain_tr_i               :8;	//15:8	//
	UINT32 reg_vrtx_gain_bl_i               :8;	//23:16	//
	UINT32 reg_vrtx_gain_br_i               :8;	//31:24	//
	};
}PE_E60_VRTX_CPC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF60 RW
	UINT32 hcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF64 RW
	UINT32 hcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF68 RW
	UINT32 hcoef4                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef5                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF6C RW
	UINT32 hcoef6                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hcoef7                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_HCOEF67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF70 RW
	UINT32 hcoef8                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_BLUR_HCOEF8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF74 RW
	UINT32 vcoef0                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef1                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_VCOEF01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF78 RW
	UINT32 vcoef2                           :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 vcoef3                           :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_BLUR_VCOEF23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF7C RW
	UINT32 vcoef4                           :10;	//9:0	//
	UINT32 resvd                            :22;
	};
}PE_E60_BLUR_VCOEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF80 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF84 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF88 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF8C RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF90 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF94 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF98 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EF9C RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFA0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFA4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFA8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFAC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFB0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFB4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFB8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFBC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFC0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFC4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFC8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFCC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFD0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFD4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFD8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFDC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFE0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFE4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFE8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFEC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFF0 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFF4 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFF8 RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EFFC RO
	UINT32 data_bg                          :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 data_fg                          :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_HISTOGRAM_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F000 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_L5_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F004 RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_L5_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F008 RW
	UINT32 y0_point                         :8;	//7:0	//control point of Y0
	UINT32 x0_point                         :8;	//15:8	//control point of X0
	UINT32 y1_point                         :8;	//23:16	//control point of Y1
	UINT32 x1_point                         :8;	//31:24	//control point of X1
	};
}PE_E60_L0_GAIN_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F00C RW
	UINT32 y2_point                         :8;	//7:0	//control point of Y2
	UINT32 x2_point                         :8;	//15:8	//control point of X2
	UINT32 y3_point                         :8;	//23:16	//control point of Y3
	UINT32 x3_point                         :8;	//31:24	//control point of X3
	};
}PE_E60_L0_GAIN_LUT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F010 RW
	UINT32 h_str                            :12;	//11:0	//window start h position
	UINT32 resvd0                           :4;
	UINT32 h_end                            :12;	//27:16	//window end h position
	UINT32 resvd1                           :4;
	};
}PE_E60_EDGE_WIN_H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F014 RW
	UINT32 v_str                            :12;	//11:0	//window start v position
	UINT32 resvd0                           :4;
	UINT32 v_end                            :12;	//27:16	//window end v position
	UINT32 resvd1                           :4;
	};
}PE_E60_EDGE_WIN_V_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F018 RO
	UINT32 edge0_fg                         :23;	//22:0	//FG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE0_FG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F01C RO
	UINT32 edge0_bg                         :23;	//22:0	//BG edge0 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE0_BG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F020 RO
	UINT32 edge1_fg                         :23;	//22:0	//FG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE1_FG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F024 RO
	UINT32 edge1_bg                         :23;	//22:0	//BG edge1 summation
	UINT32 resvd                            :9;
	};
}PE_E60_EDGE1_BG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F028 RW
	UINT32 cliping_en                       :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 th_lower                         :6;	//9:4	//threshold of lower
	UINT32 resvd1                           :2;
	UINT32 th_upper                         :6;	//17:12	//threshold of upper
	UINT32 resvd2                           :2;
	UINT32 prc_step                         :6;	//25:20	//same protection step
	UINT32 resvd3                           :6;
	};
}PE_E60_PSP_IIR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F02C RW
	UINT32 bg_measure_en                    :1;	//0 //IIR value cliping enable
	UINT32 resvd0                           :3;
	UINT32 h_num                            :4;	//7:4	//divide hsize
	UINT32 v_num                            :4;	//11:8	//divide vsize
	UINT32 obj_th0                          :6;	//17:12	//threshold of minimum gain
	UINT32 resvd1                           :2;
	UINT32 obj_th1                          :8;	//27:20	//threshold of bin counting
	UINT32 resvd2                           :4;
	};
}PE_E60_BG_MEASURE_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F030 RO
	UINT32 line_unit0                       :16;	//15:0	//
	UINT32 line_unit1                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F034 RO
	UINT32 line_unit2                       :16;	//15:0	//
	UINT32 line_unit3                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F038 RO
	UINT32 line_unit4                       :16;	//15:0	//
	UINT32 line_unit5                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F03C RO
	UINT32 line_unit6                       :16;	//15:0	//
	UINT32 line_unit7                       :16;	//31:16	//
	};
}PE_E60_BG_MEASURE_READ3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F040 RO
	UINT32 line_unit8                       :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_BG_MEASURE_READ4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F044 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
}PE_E60_FACE0_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F048 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
}PE_E60_FACE1_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F04C RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
}PE_E60_FACE2_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F050 RW
	UINT32 reg_w2_pos                       :7;	//6:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_w1_pos                       :7;	//14:8	//
	UINT32 resvd1                           :1;
	UINT32 reg_h2_pos                       :7;	//22:16	//
	UINT32 resvd2                           :1;
	UINT32 reg_h1_pos                       :7;	//30:24	//
	UINT32 face0_en                         :1;	//31 //
	};
}PE_E60_FACE3_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F054 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
}PE_E60_ELLIPS0_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F058 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
}PE_E60_ELLIPS1_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F05C RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
}PE_E60_ELLIPS2_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900F060 RW
	UINT32 reg_e_mul_a                      :9;	//8:0	//4.5bit
	UINT32 resvd0                           :7;
	UINT32 reg_e_mul_b                      :9;	//24:16	//4.5bit
	UINT32 resvd1                           :7;
	};
}PE_E60_ELLIPS3_SET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90030B8 RW
	UINT32 reg_lvctrl_en                    :1;	//0 //'0' := DISABLE	 '1'  = ENABLE
	UINT32 reg_lvctrl_detour                :1;	//1 //'0' := NORMAL	 '1'  = DETOUR
	UINT32 resvd0                           :2;
	UINT32 level_offset                     :10;	//13:4	//
	UINT32 resvd1                           :2;
	UINT32 level_center                     :8;	//23:16	//
	UINT32 level_gain                       :8;	//31:24	//
	};
}PE_E60_CTRL_CTRL_M0_Y_LEVEL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EC00 RW 0x0000_0000
	UINT32 reg_tnr_en						:1; //0:0	//
	UINT32 reg_hw_col_data_copy_en			:1; //1:1	//E20
	UINT32 reg_sc_detect_hres				:1; //2:2	//
	UINT32 reg_clc_nt_pal					:1; //3:3	//
	UINT32 reg_clc_mem_wr_mode				:2; //5:4	//
	UINT32 reg_sad_8x3_res					:2; //7:6	//
	UINT32 reg_sad_8x3_iir_en				:1; //8:8	//
	UINT32 reg_sad_8x3_chroma_en			:1; //9:9	//
	UINT32 reg_minfo_sw 					:2; //11:10 //
	UINT32 reg_minfo_mode10 				:2; //13:12 //[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt					:2; //15:14 //
	UINT32 reg_tnr_single_en				:1; //16:16 //TNR half_rate : This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en				:1; //17 //chg
	UINT32 reg_minfo_mode32 				:2; //19:18 //
	UINT32 reg_minfo_mode74 				:4; //23:20 //
	UINT32 reg_sad_8x3_iir_alpha			:8; //31:24 //for TNR, DNR
	};
}PE_E60_ND0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029804 RW 0x0000_0000
	UINT32 resvd0							:1;
	UINT32 reg_ombc_en						:1; //1 //
	UINT32 resvd1							:2;
	UINT32 reg_luma_gain_en 				:1; //4 //
	UINT32 reg_crgn_gain_en 				:1; //5 //
	UINT32 reg_chroma_sad_res				:2; //7:6	//
	UINT32 resvd2							:4;
	UINT32 reg_5x5_sad_cut					:2; //13:12 //
	UINT32 resvd3							:2;
	UINT32 reg_avg_cmp_en					:1; //16 //
	UINT32 reg_avg_cmp_res					:3; //19:17 //
	UINT32 reg_debug_sel					:4; //23:20 //
	UINT32 resvd4							:4;
	UINT32 reg_cnt_mode 					:3; //30:28 //
	UINT32 reg_chroma_sad_en				:1; //31 //
	};
}PE_E60_ND0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9029808 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_ND0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902980C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_ND0_VERI_SYS_VERI_3_T;

typedef struct {
	PE_E60_ND0_VERI_SYS_VERI_0_T                          nd0_veri_tnr_00;	//0xC900EC00
	PE_E60_ND0_VERI_SYS_VERI_1_T                          nd0_veri_tnr_24;	//0xC900EC04
	PE_E60_ND0_VERI_SYS_VERI_2_T                               sys_veri_2;	//0xC900EC08
	PE_E60_ND0_VERI_SYS_VERI_3_T                               sys_veri_3;	//0xC900EC0C
}PE_ND0_VERI_REG_E60_T;

typedef struct {
	PE_E60_ND0_PE0_LOAD_T                                         pe0_load;	//0xC900E100
	PE_E60_ND0_PE0_INTR_T                                         pe0_intr;	//0xC900E104
	PE_E60_ND0_PE0_STATUS0_T                                   pe0_status0;	//0xC900E108
	PE_E60_ND0_PE0_STATUS1_T                                   pe0_status1;	//0xC900E10C
	PE_E60_ND0_PE0_OPMODE_T                                     pe0_opmode;	//0xC900E110
	PE_E60_ND0_PE0_SRC_SIZE_T                                 pe0_src_size;	//0xC900E114
	PE_E60_ND0_PE0_FIELD_T                                       pe0_field;	//0xC900E118
	PE_E60_ND0_PE0_DEBUG_LEND_CTRL_T                   pe0_debug_lend_ctrl;	//0xC900E11C
	PE_E60_ND0_PE0_IN_OFFSET_T                               pe0_in_offset;	//0xC900E120
	PE_E60_ND0_PE0_IN_SIZE_T                                   pe0_in_size;	//0xC900E124
	PE_E60_ND0_FBC_CTRL0_RESERVED_T                     fbc_ctrl0_reserved;	//0xC900E128
	PE_E60_ND0_FBC_CTRL1_RESERVED_T                     fbc_ctrl1_reserved;	//0xC900E12C
	PE_E60_ND0_PE0_MEM_REQ_T                                   pe0_mem_req;	//0xC900E130
	PE_E60_ND0_PE0_DEBUG_LREQ_DLY_T                     pe0_debug_lreq_dly;	//0xC900E134
	PE_E60_ND0_TNRW_IN_OFFSET_T                             tnrw_in_offset;	//0xC900E138
	PE_E60_ND0_TNRW_OUT_SIZE_T                               tnrw_out_size;	//0xC900E13C
	PE_E60_ND0_TNR_CTRL_00_T                                   tnr_ctrl_00;	//0xC900E140
	PE_E60_ND0_TNR_CTRL_01_T                                   tnr_ctrl_01;	//0xC900E144
	PE_E60_ND0_TNR_CTRL_02_T                                   tnr_ctrl_02;	//0xC900E148
	PE_E60_ND0_TNR_CTRL_03_T                                   tnr_ctrl_03;	//0xC900E14C
	PE_E60_ND0_TNR_CTRL_04_T                                   tnr_ctrl_04;	//0xC900E150
	PE_E60_ND0_TNR_CTRL_05_T                                   tnr_ctrl_05;	//0xC900E154
	PE_E60_ND0_TNR_CTRL_06_T                                   tnr_ctrl_06;	//0xC900E158
	PE_E60_ND0_TNR_CTRL_07_T                                   tnr_ctrl_07;	//0xC900E15C
	PE_E60_ND0_TNR_CTRL_08_T                                   tnr_ctrl_08;	//0xC900E160
	PE_E60_ND0_TNR_CTRL_09_T                                   tnr_ctrl_09;	//0xC900E164
	PE_E60_ND0_TNR_CTRL_10_T                                   tnr_ctrl_10;	//0xC900E168
	PE_E60_ND0_TNR_CTRL_11_T                                   tnr_ctrl_11;	//0xC900E16C
	PE_E60_ND0_TNR_CTRL_12_T                                   tnr_ctrl_12;	//0xC900E170
	PE_E60_ND0_TNR_CTRL_13_T                                   tnr_ctrl_13;	//0xC900E174
	PE_E60_ND0_TNR_CTRL_14_T                                   tnr_ctrl_14;	//0xC900E178
	PE_E60_ND0_TNR_CTRL_15_T                                   tnr_ctrl_15;	//0xC900E17C
	PE_E60_ND0_TNR_CTRL_16_T                                   tnr_ctrl_16;	//0xC900E180
	PE_E60_ND0_TNR_CTRL_17_T                                   tnr_ctrl_17;	//0xC900E184
	PE_E60_ND0_TNR_CTRL_18_T                                   tnr_ctrl_18;	//0xC900E188
	PE_E60_ND0_TNR_CTRL_19_T                                   tnr_ctrl_19;	//0xC900E18C
	PE_E60_ND0_TNR_CTRL_20_T                                   tnr_ctrl_20;	//0xC900E190
	PE_E60_ND0_TNR_CTRL_21_T                                   tnr_ctrl_21;	//0xC900E194
	PE_E60_ND0_TNR_CTRL_22_T                                   tnr_ctrl_22;	//0xC900E198
	PE_E60_ND0_TNR_CTRL_23_T                                   tnr_ctrl_23;	//0xC900E19C
	PE_E60_ND0_TNR_CTRL_24_T                                   tnr_ctrl_24;	//0xC900E1A0
	PE_E60_ND0_TNR_CTRL_25_T                                   tnr_ctrl_25;	//0xC900E1A4
	PE_E60_ND0_TNR_CTRL_26_T                                   tnr_ctrl_26;	//0xC900E1A8
	PE_E60_ND0_TNR_CTRL_27_T                                   tnr_ctrl_27;	//0xC900E1AC
	PE_E60_ND0_TNR_CTRL_28_T                                   tnr_ctrl_28;	//0xC900E1B0
	PE_E60_ND0_TNR_CTRL_29_T                                   tnr_ctrl_29;	//0xC900E1B4
	PE_E60_ND0_TNR_CTRL_30_T                                   tnr_ctrl_30;	//0xC900E1B8
	PE_E60_ND0_TNR_CTRL_31_T                                   tnr_ctrl_31;	//0xC900E1BC
	PE_E60_ND0_TNR_STATUS_00_T                               tnr_status_00;	//0xC900E1C0
	PE_E60_ND0_TNR_STATUS_01_T                               tnr_status_01;	//0xC900E1C4
	PE_E60_ND0_TNR_STATUS_02_T                               tnr_status_02;	//0xC900E1C8
	PE_E60_ND0_TNR_STATUS_03_T                               tnr_status_03;	//0xC900E1CC
	PE_E60_ND0_TNR_MAIN_LUT_00_T                           tnr_main_lut_00;	//0xC900E1D0
	PE_E60_ND0_TNR_MAIN_LUT_01_T                           tnr_main_lut_01;	//0xC900E1D4
	UINT32                                                    reserved0;	//0xC900E1D8
	PE_E60_ND0_TNR_STATUS_04_T                               tnr_status_04;	//0xC900E1DC
	PE_E60_ND0_TNR_CTRL_32_T                                   tnr_ctrl_32;	//0xC900E1E0
	PE_E60_ND0_TNR_CTRL_33_T                                   tnr_ctrl_33;	//0xC900E1E4
	PE_E60_ND0_TNR_CTRL_34_T                                   tnr_ctrl_34;	//0xC900E1E8
	PE_E60_ND0_TNR_CTRL_35_T                                   tnr_ctrl_35;	//0xC900E1EC
	PE_E60_ND0_TNR_CTRL_36_T                                   tnr_ctrl_36;	//0xC900E1F0
	PE_E60_ND0_TNR_CTRL_37_T                                   tnr_ctrl_37;	//0xC900E1F4
	PE_E60_ND0_TNR_CTRL_38_T                                   tnr_ctrl_38;	//0xC900E1F8
	PE_E60_ND0_TNR_CTRL_39_T                                   tnr_ctrl_39;	//0xC900E1FC
	PE_E60_ND0_IPC_CTRL_00_T                                   ipc_ctrl_00;	//0xC900E200
	PE_E60_ND0_IPC_CTRL_01_T                                   ipc_ctrl_01;	//0xC900E204
	PE_E60_ND0_IPC_CTRL_02_T                                   ipc_ctrl_02;	//0xC900E208
	PE_E60_ND0_IPC_CTRL_03_T                                   ipc_ctrl_03;	//0xC900E20C
	PE_E60_ND0_IPC_CTRL_04_T                                   ipc_ctrl_04;	//0xC900E210
	PE_E60_ND0_IPC_CTRL_05_T                                   ipc_ctrl_05;	//0xC900E214
	PE_E60_ND0_IPC_CTRL_06_T                                   ipc_ctrl_06;	//0xC900E218
	PE_E60_ND0_IPC_CTRL_07_T                                   ipc_ctrl_07;	//0xC900E21C
	PE_E60_ND0_IPC_CTRL_08_T                                   ipc_ctrl_08;	//0xC900E220
	PE_E60_ND0_IPC_CTRL_09_T                                   ipc_ctrl_09;	//0xC900E224
	PE_E60_ND0_IPC_CTRL_10_T                                   ipc_ctrl_10;	//0xC900E228
	PE_E60_ND0_IPC_CTRL_11_T                                   ipc_ctrl_11;	//0xC900E22C
	PE_E60_ND0_IPC_CTRL_12_T                                   ipc_ctrl_12;	//0xC900E230
	PE_E60_ND0_IPC_CTRL_13_T                                   ipc_ctrl_13;	//0xC900E234
	PE_E60_ND0_IPC_CTRL_14_T                                   ipc_ctrl_14;	//0xC900E238
	PE_E60_ND0_IPC_CTRL_15_T                                   ipc_ctrl_15;	//0xC900E23C
	PE_E60_ND0_IPC_CTRL_16_T                                   ipc_ctrl_16;	//0xC900E240
	PE_E60_ND0_IPC_CTRL_17_T                                   ipc_ctrl_17;	//0xC900E244
	PE_E60_ND0_IPC_CTRL_18_T                                   ipc_ctrl_18;	//0xC900E248
	PE_E60_ND0_IPC_CTRL_19_T                                   ipc_ctrl_19;	//0xC900E24C
	PE_E60_ND0_IPC_STATUS_00_T                               ipc_status_00;	//0xC900E250
	PE_E60_ND0_IPC_STATUS_01_T                               ipc_status_01;	//0xC900E254
	PE_E60_ND0_IPC_STATUS_02_T                               ipc_status_02;	//0xC900E258
	PE_E60_ND0_IPC_STATUS_03_T                               ipc_status_03;	//0xC900E25C
	PE_E60_ND0_CLC_CTRL_00_T                                   clc_ctrl_00;	//0xC900E260
	PE_E60_ND0_CLC_CTRL_01_T                                   clc_ctrl_01;	//0xC900E264
	PE_E60_ND0_CLC_CTRL_02_T                                   clc_ctrl_02;	//0xC900E268
	PE_E60_ND0_CLC_CTRL_03_T                                   clc_ctrl_03;	//0xC900E26C
	PE_E60_ND0_CLC_CTRL_04_T                                   clc_ctrl_04;	//0xC900E270
	PE_E60_ND0_CLC_CTRL_05_T                                   clc_ctrl_05;	//0xC900E274
	PE_E60_ND0_CLC_CTRL_06_T                                   clc_ctrl_06;	//0xC900E278
	PE_E60_ND0_CLC_STAT_00_T                                   clc_stat_00;	//0xC900E27C
	PE_E60_ND0_IPC_CTRL_34_T                                   ipc_ctrl_34;	//0xC900E280
	PE_E60_ND0_IPC_CTRL_35_T                                   ipc_ctrl_35;	//0xC900E284
	PE_E60_ND0_IPC_CTRL_36_T                                   ipc_ctrl_36;	//0xC900E288
	PE_E60_ND0_IPC_CTRL_37_T                                   ipc_ctrl_37;	//0xC900E28C
	PE_E60_ND0_IPC_CTRL_38_T                                   ipc_ctrl_38;	//0xC900E290
	PE_E60_ND0_IPC_CTRL_39_T                                   ipc_ctrl_39;	//0xC900E294
	PE_E60_ND0_IPC_CTRL_40_T                                   ipc_ctrl_40;	//0xC900E298
	PE_E60_ND0_IPC_CTRL_41_T                                   ipc_ctrl_41;	//0xC900E29C
	PE_E60_ND0_IPC_CTRL_42_T                                   ipc_ctrl_42;	//0xC900E2A0
	PE_E60_ND0_IPC_CTRL_43_T                                   ipc_ctrl_43;	//0xC900E2A4
	PE_E60_ND0_IPC_CTRL_44_T                                   ipc_ctrl_44;	//0xC900E2A8
	PE_E60_ND0_IPC_CTRL_45_T                                   ipc_ctrl_45;	//0xC900E2AC
	PE_E60_ND0_IPC_CTRL_46_T                                   ipc_ctrl_46;	//0xC900E2B0
	PE_E60_ND0_IPC_CTRL_47_T                                   ipc_ctrl_47;	//0xC900E2B4
	PE_E60_ND0_IPC_CTRL_48_T                                   ipc_ctrl_48;	//0xC900E2B8
	PE_E60_ND0_IPC_CTRL_49_T                                   ipc_ctrl_49;	//0xC900E2BC
	PE_E60_ND0_IPC_CTRL_50_T                                   ipc_ctrl_50;	//0xC900E2C0
	PE_E60_ND0_IPC_CTRL_51_T                                   ipc_ctrl_51;	//0xC900E2C4
	PE_E60_ND0_IPC_CTRL_52_T                                   ipc_ctrl_52;	//0xC900E2C8
	PE_E60_ND0_IPC_CTRL_53_T                                   ipc_ctrl_53;	//0xC900E2CC
	PE_E60_ND0_IPC_CTRL_54_T                                   ipc_ctrl_54;	//0xC900E2D0
	PE_E60_ND0_IPC_CTRL_55_T                                   ipc_ctrl_55;	//0xC900E2D4
	UINT32                                                    reserved1;	//0xC900E2D8
	UINT32                                                    reserved2;	//0xC900E2DC
	PE_E60_ND0_MMD_CTRL_T                                         mmd_ctrl;	//0xC900E2E0
	UINT32                                                    reserved3;	//0xC900E2E4
	UINT32                                                    reserved4;	//0xC900E2E8
	UINT32                                                    reserved5;	//0xC900E2EC
	PE_E60_ND0_IPC_CTRL_20_T                                   ipc_ctrl_20;	//0xC900E2F0
	PE_E60_ND0_IPC_CTRL_21_T                                   ipc_ctrl_21;	//0xC900E2F4
	PE_E60_ND0_IPC_CTRL_22_T                                   ipc_ctrl_22;	//0xC900E2F8
	PE_E60_ND0_IPC_CTRL_23_T                                   ipc_ctrl_23;	//0xC900E2FC
	PE_E60_ND0_IPC_CTRL_24_T                                   ipc_ctrl_24;	//0xC900E300
	PE_E60_ND0_IPC_CTRL_25_T                                   ipc_ctrl_25;	//0xC900E304
	PE_E60_ND0_IPC_CTRL_26_T                                   ipc_ctrl_26;	//0xC900E308
	PE_E60_ND0_IPC_CTRL_27_T                                   ipc_ctrl_27;	//0xC900E30C
	PE_E60_ND0_IPC_CTRL_28_T                                   ipc_ctrl_28;	//0xC900E310
	PE_E60_ND0_IPC_CTRL_29_T                                   ipc_ctrl_29;	//0xC900E314
	PE_E60_ND0_IPC_CTRL_30_T                                   ipc_ctrl_30;	//0xC900E318
	PE_E60_ND0_IPC_CTRL_31_T                                   ipc_ctrl_31;	//0xC900E31C
	PE_E60_ND0_IPC_CTRL_32_T                                   ipc_ctrl_32;	//0xC900E320
	PE_E60_ND0_IPC_CTRL_33_T                                   ipc_ctrl_33;	//0xC900E324
	PE_E60_ND0_IPC_STATUS_04_T                               ipc_status_04;	//0xC900E328
	PE_E60_ND0_IPC_STATUS_05_T                               ipc_status_05;	//0xC900E32C
	PE_E60_ND0_IPC_STATUS_06_T                               ipc_status_06;	//0xC900E330
	PE_E60_ND0_IPC_STATUS_07_T                               ipc_status_07;	//0xC900E334
	PE_E60_ND0_IPC_STATUS_08_T                               ipc_status_08;	//0xC900E338
	PE_E60_ND0_IPC_STATUS_09_T                               ipc_status_09;	//0xC900E33C
	PE_E60_ND0_TPD_CTRL_00_T                                   tpd_ctrl_00;	//0xC900E340
	PE_E60_ND0_TPD_CTRL_01_T                                   tpd_ctrl_01;	//0xC900E344
	PE_E60_ND0_TPD_CTRL_02_T                                   tpd_ctrl_02;	//0xC900E348
	PE_E60_ND0_TPD_CTRL_03_T                                   tpd_ctrl_03;	//0xC900E34C
	PE_E60_ND0_TPD_CTRL_04_T                                   tpd_ctrl_04;	//0xC900E350
	PE_E60_ND0_TPD_CTRL_05_T                                   tpd_ctrl_05;	//0xC900E354
	PE_E60_ND0_TPD_CTRL_06_T                                   tpd_ctrl_06;	//0xC900E358
	PE_E60_ND0_TPD_CTRL_07_T                                   tpd_ctrl_07;	//0xC900E35C
	PE_E60_ND0_TPD_CTRL_08_T                                   tpd_ctrl_08;	//0xC900E360
	PE_E60_ND0_TPD_CTRL_09_T                                   tpd_ctrl_09;	//0xC900E364
	PE_E60_ND0_TPD_STAT_00_T                                   tpd_stat_00;	//0xC900E368
	PE_E60_ND0_CLC_CTRL_07_T                                   clc_ctrl_07;	//0xC900E36C
	PE_E60_ND0_BBD_CTRL_00_T                                   bbd_ctrl_00;	//0xC900E370
	PE_E60_ND0_BBD_CTRL_01_T                                   bbd_ctrl_01;	//0xC900E374
	PE_E60_ND0_BBD_CTRL_02_T                                   bbd_ctrl_02;	//0xC900E378
	PE_E60_ND0_BBD_STAT_00_T                                   bbd_stat_00;	//0xC900E37C
	PE_E60_ND0_BBD_STAT_01_T                                   bbd_stat_01;	//0xC900E380
	PE_E60_ND0_APL_STAT_00_T                                   apl_stat_00;	//0xC900E384
	PE_E60_ND0_TPD_CTRL_0A_T                                   tpd_ctrl_0a;	//0xC900E388
	PE_E60_ND0_TPD_CTRL_0B_T                                   tpd_ctrl_0b;	//0xC900E38C
	PE_E60_ND0_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0xC900E390
	PE_E60_ND0_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0xC900E394
	PE_E60_ND0_LVCRTL_CTRL_00_T                             lvcrtl_ctrl_00;	//0xC900E398
	PE_E60_ND0_TPD_STAT_01_T                                   tpd_stat_01;	//0xC900E39C
	PE_E60_ND0_TNR_STATUS_05_T                               tnr_status_05;	//0xC900E3A0
	PE_E60_ND0_TNR_STATUS_06_T                               tnr_status_06;	//0xC900E3A4
	PE_E60_ND0_TNR_STATUS_07_T                               tnr_status_07;	//0xC900E3A8
	PE_E60_ND0_TNR_STATUS_08_T                               tnr_status_08;	//0xC900E3AC
	UINT32                                                    reserved6;	//0xC900E3B0
	UINT32                                                    reserved7;	//0xC900E3B4
	UINT32                                                    reserved8;	//0xC900E3B8
	UINT32                                                    reserved9;	//0xC900E3BC
	PE_E60_ND0_TNR_RESET_T                                       tnr_reset;	//0xC900E3C0
	UINT32                                                   reserved10;	//0xC900E3C4
	UINT32                                                   reserved11;	//0xC900E3C8
	UINT32                                                   reserved12;	//0xC900E3CC
	PE_E60_ND0_TNR_CTRL_40_T                                   tnr_ctrl_40;	//0xC900E3D0
	PE_E60_ND0_TNR_CTRL_41_T                                   tnr_ctrl_41;	//0xC900E3D4
	PE_E60_ND0_TNR_CTRL_42_T                                   tnr_ctrl_42;	//0xC900E3D8
	PE_E60_ND0_TNR_CTRL_43_T                                   tnr_ctrl_43;	//0xC900E3DC
	PE_E60_ND0_TNR_CTRL_44_T                                   tnr_ctrl_44;	//0xC900E3E0
	PE_E60_ND0_TNR_CTRL_45_T                                   tnr_ctrl_45;	//0xC900E3E4
	PE_E60_ND0_TNR_CTRL_46_T                                   tnr_ctrl_46;	//0xC900E3E8
	PE_E60_ND0_TNR_CTRL_47_T                                   tnr_ctrl_47;	//0xC900E3EC
	PE_E60_ND0_TNR_CTRL_48_T                                   tnr_ctrl_48;	//0xC900E3F0
	PE_E60_PE1_FSW_CTRL_00_T                                pe1_fsw_ctrl_00;//0xC900E3F4
	PE_E60_PE1_FSW_CTRL_01_T                                pe1_fsw_ctrl_01;//0xC900E3F8
	PE_E60_PE1_FSW_CTRL_01_T                                pe1_fsw_ctrl_02;//0xC900E3FC
	PE_E60_ND0_TNR_NE_STAT_00_T                             tnr_ne_stat_00;	//0xC900E400
	PE_E60_ND0_TNR_NE_STAT_01_T                             tnr_ne_stat_01;	//0xC900E404
	PE_E60_ND0_TNR_NE_STAT_02_T                             tnr_ne_stat_02;	//0xC900E408
	PE_E60_ND0_TNR_NE_STAT_03_T                             tnr_ne_stat_03;	//0xC900E40C
	PE_E60_ND0_TNR_NE_STAT_04_T                             tnr_ne_stat_04;	//0xC900E410
	PE_E60_ND0_TNR_NE_STAT_05_T                             tnr_ne_stat_05;	//0xC900E414
	PE_E60_ND0_TNR_NE_STAT_06_T                             tnr_ne_stat_06;	//0xC900E418
	PE_E60_ND0_TNR_NE_STAT_07_T                             tnr_ne_stat_07;	//0xC900E41C
	PE_E60_ND0_TNR_NE_STAT_08_T                             tnr_ne_stat_08;	//0xC900E420
	UINT32                                                   reserved16;	//0xC900E424
	UINT32                                                   reserved17;	//0xC900E428
	UINT32                                                   reserved18;	//0xC900E42C
	UINT32                                                   reserved19;	//0xC900E430
	UINT32                                                   reserved20;	//0xC900E434
	UINT32                                                   reserved21;	//0xC900E438
	UINT32                                                   reserved22;	//0xC900E43C
	PE_E60_ND0_HIST2_CTRL_00_T                               hist2_ctrl_00;	//0xC900E440
	PE_E60_ND0_HIST2_CTRL_01_T                               hist2_ctrl_01;	//0xC900E444
	PE_E60_ND0_HIST2_CTRL_02_T                               hist2_ctrl_02;	//0xC900E448
	PE_E60_ND0_HIST2_CTRL_03_T                               hist2_ctrl_03;	//0xC900E44C
	PE_E60_ND0_HIST2_CTRL_04_T                               hist2_ctrl_04;	//0xC900E450
	PE_E60_ND0_HIST2_CTRL_05_T                               hist2_ctrl_05;	//0xC900E454
	PE_E60_ND0_HIST2_CTRL_06_T                               hist2_ctrl_06;	//0xC900E458
	PE_E60_ND0_HIST2_CTRL_07_T                               hist2_ctrl_07;	//0xC900E45C
	PE_E60_ND0_HIST2_CTRL_08_T                               hist2_ctrl_08;	//0xC900E460
	PE_E60_ND0_HIST2_CTRL_09_T                               hist2_ctrl_09;	//0xC900E464
	PE_E60_ND0_HIST2_CTRL_0A_T                               hist2_ctrl_0a;	//0xC900E468
	PE_E60_ND0_HIST2_CTRL_0B_T                               hist2_ctrl_0b;	//0xC900E46C
	PE_E60_ND0_HIST2_HIST_AI_CTRL_T                     hist2_hist_ai_ctrl;	//0xC900E470
	PE_E60_ND0_HIST2_HIST_AI_DATA_T                     hist2_hist_ai_data;	//0xC900E474
	PE_E60_ND0_HIST2_STAT_00_T                               hist2_stat_00;	//0xC900E478
	UINT32                                                   reserved23;	//0xC900E47C
	PE_E60_ND0_ND_FSW_CTRL_00_T                             nd_fsw_ctrl_00;	//0xC900E480
	PE_E60_ND0_ND_FSW_CTRL_01_T                             nd_fsw_ctrl_01;	//0xC900E484
	PE_E60_ND0_ND_FSW_CTRL_02_T                             nd_fsw_ctrl_02;	//0xC900E488
	PE_E60_ND0_ND_FSW_CTRL_03_T                             nd_fsw_ctrl_03;	//0xC900E48C
	PE_E60_ND0_TNR_ETC_CTRL_00_T                           tnr_etc_ctrl_00;	//0xC900E490
	PE_E60_ND0_TNR_ETC_CTRL_01_T                           tnr_etc_ctrl_01;	//0xC900E494
	PE_E60_ND0_TNR_ETC_CTRL_02_T                           tnr_etc_ctrl_02;	//0xC900E498
	PE_E60_ND0_TNR_ETC_CTRL_03_T                           tnr_etc_ctrl_03;	//0xC900E49C
	PE_E60_ND0_TNR_CTRL_56_T                                   tnr_ctrl_56;	//0xC900E4A0
	PE_E60_ND0_TNR_CTRL_57_T                                   tnr_ctrl_57;	//0xC900E4A4
	PE_E60_ND0_TNR_CTRL_58_T                                   tnr_ctrl_58;	//0xC900E4A8
	PE_E60_ND0_TNR_CTRL_59_T                                   tnr_ctrl_59;	//0xC900E4AC
	PE_E60_ND0_TNR_CTRL_60_T                                   tnr_ctrl_60;	//0xC900E4B0
	PE_E60_ND0_TNR_CTRL_61_T                                   tnr_ctrl_61;	//0xC900E4B4
	PE_E60_ND0_PE0_DEBUG3_T                                     pe0_debug3;	//0xC900E4B8
	UINT32                                                   reserved24;	//0xC900E4BC
	PE_E60_ND0_FBC_CTRL_02_T                                   fbc_ctrl_02;	//0xC900E4C0
	PE_E60_ND0_FBC_CTRL_03_T                                   fbc_ctrl_03;	//0xC900E4C4
	PE_E60_ND0_TNRW_M_IN_OFFSET_T                         tnrw_m_in_offset;	//0xC900E4C8
	PE_E60_ND0_TNRW_M_OUT_SIZE_T                           tnrw_m_out_size;	//0xC900E4CC
	PE_E60_ND0_GFD_CTRL_00_T                                   gfd_ctrl_00;	//0xC900E4D0
	PE_E60_ND0_GFD_CTRL_01_T                                   gfd_ctrl_01;	//0xC900E4D4
	PE_E60_ND0_GFD_STAT_00_T                                   gfd_stat_00;	//0xC900E4D8
	PE_E60_ND0_GFD_STAT_01_T                                   gfd_stat_01;	//0xC900E4DC
	PE_E60_ND0_GFD_STAT_02_T                                   gfd_stat_02;	//0xC900E4E0
	PE_E60_ND0_GFD_STAT_03_T                                   gfd_stat_03;	//0xC900E4E4
}PE_ND_ND0_REG_E60_T;

typedef struct {
	PE_E60_ND1_PE0_LOAD_T                                         pe0_load;	//0xC9010100
	PE_E60_ND1_PE0_INTR_T                                         pe0_intr;	//0xC9010104
	PE_E60_ND1_PE0_STATUS0_T                                   pe0_status0;	//0xC9010108
	PE_E60_ND1_PE0_STATUS1_T                                   pe0_status1;	//0xC901010C
	PE_E60_ND1_PE0_OPMODE_T                                     pe0_opmode;	//0xC9010110
	PE_E60_ND1_PE0_SRC_SIZE_T                                 pe0_src_size;	//0xC9010114
	PE_E60_ND1_PE0_FIELD_T                                       pe0_field;	//0xC9010118
	PE_E60_ND1_PE0_DEBUG_LEND_CTRL_T                   pe0_debug_lend_ctrl;	//0xC901011C
	PE_E60_ND1_PE0_IN_OFFSET_T                               pe0_in_offset;	//0xC9010120
	PE_E60_ND1_PE0_IN_SIZE_T                                   pe0_in_size;	//0xC9010124
	PE_E60_ND1_FBC_CTRL0_RESERVED_T                     fbc_ctrl0_reserved;	//0xC9010128
	PE_E60_ND1_FBC_CTRL1_RESERVED_T                     fbc_ctrl1_reserved;	//0xC901012C
	PE_E60_ND1_PE0_MEM_REQ_T                                   pe0_mem_req;	//0xC9010130
	PE_E60_ND1_PE0_DEBUG_LREQ_DLY_T                     pe0_debug_lreq_dly;	//0xC9010134
	PE_E60_ND1_TNRW_IN_OFFSET_T                             tnrw_in_offset;	//0xC9010138
	PE_E60_ND1_TNRW_OUT_SIZE_T                               tnrw_out_size;	//0xC901013C
	PE_E60_ND1_TNR_CTRL_00_T                                   tnr_ctrl_00;	//0xC9010140
	PE_E60_ND1_TNR_CTRL_01_T                                   tnr_ctrl_01;	//0xC9010144
	PE_E60_ND1_TNR_CTRL_02_T                                   tnr_ctrl_02;	//0xC9010148
	PE_E60_ND1_TNR_CTRL_03_T                                   tnr_ctrl_03;	//0xC901014C
	PE_E60_ND1_TNR_CTRL_04_T                                   tnr_ctrl_04;	//0xC9010150
	PE_E60_ND1_TNR_CTRL_05_T                                   tnr_ctrl_05;	//0xC9010154
	PE_E60_ND1_TNR_CTRL_06_T                                   tnr_ctrl_06;	//0xC9010158
	PE_E60_ND1_TNR_CTRL_07_T                                   tnr_ctrl_07;	//0xC901015C
	PE_E60_ND1_TNR_CTRL_08_T                                   tnr_ctrl_08;	//0xC9010160
	PE_E60_ND1_TNR_CTRL_09_T                                   tnr_ctrl_09;	//0xC9010164
	PE_E60_ND1_TNR_CTRL_10_T                                   tnr_ctrl_10;	//0xC9010168
	PE_E60_ND1_TNR_CTRL_11_T                                   tnr_ctrl_11;	//0xC901016C
	PE_E60_ND1_TNR_CTRL_12_T                                   tnr_ctrl_12;	//0xC9010170
	PE_E60_ND1_TNR_CTRL_13_T                                   tnr_ctrl_13;	//0xC9010174
	PE_E60_ND1_TNR_CTRL_14_T                                   tnr_ctrl_14;	//0xC9010178
	PE_E60_ND1_TNR_CTRL_15_T                                   tnr_ctrl_15;	//0xC901017C
	PE_E60_ND1_TNR_CTRL_16_T                                   tnr_ctrl_16;	//0xC9010180
	PE_E60_ND1_TNR_CTRL_17_T                                   tnr_ctrl_17;	//0xC9010184
	PE_E60_ND1_TNR_CTRL_18_T                                   tnr_ctrl_18;	//0xC9010188
	PE_E60_ND1_TNR_CTRL_19_T                                   tnr_ctrl_19;	//0xC901018C
	PE_E60_ND1_TNR_CTRL_20_T                                   tnr_ctrl_20;	//0xC9010190
	PE_E60_ND1_TNR_CTRL_21_T                                   tnr_ctrl_21;	//0xC9010194
	PE_E60_ND1_TNR_CTRL_22_T                                   tnr_ctrl_22;	//0xC9010198
	PE_E60_ND1_TNR_CTRL_23_T                                   tnr_ctrl_23;	//0xC901019C
	PE_E60_ND1_TNR_CTRL_24_T                                   tnr_ctrl_24;	//0xC90101A0
	PE_E60_ND1_TNR_CTRL_25_T                                   tnr_ctrl_25;	//0xC90101A4
	PE_E60_ND1_TNR_CTRL_26_T                                   tnr_ctrl_26;	//0xC90101A8
	PE_E60_ND1_TNR_CTRL_27_T                                   tnr_ctrl_27;	//0xC90101AC
	PE_E60_ND1_TNR_CTRL_28_T                                   tnr_ctrl_28;	//0xC90101B0
	PE_E60_ND1_TNR_CTRL_29_T                                   tnr_ctrl_29;	//0xC90101B4
	PE_E60_ND1_TNR_CTRL_30_T                                   tnr_ctrl_30;	//0xC90101B8
	PE_E60_ND1_TNR_CTRL_31_T                                   tnr_ctrl_31;	//0xC90101BC
	PE_E60_ND1_TNR_STATUS_00_T                               tnr_status_00;	//0xC90101C0
	PE_E60_ND1_TNR_STATUS_01_T                               tnr_status_01;	//0xC90101C4
	PE_E60_ND1_TNR_STATUS_02_T                               tnr_status_02;	//0xC90101C8
	PE_E60_ND1_TNR_STATUS_03_T                               tnr_status_03;	//0xC90101CC
	PE_E60_ND1_TNR_MAIN_LUT_00_T                           tnr_main_lut_00;	//0xC90101D0
	PE_E60_ND1_TNR_MAIN_LUT_01_T                           tnr_main_lut_01;	//0xC90101D4
	UINT32                                                    reserved0;	//0xC90101D8
	PE_E60_ND1_TNR_STATUS_04_T                               tnr_status_04;	//0xC90101DC
	PE_E60_ND1_TNR_CTRL_32_T                                   tnr_ctrl_32;	//0xC90101E0
	PE_E60_ND1_TNR_CTRL_33_T                                   tnr_ctrl_33;	//0xC90101E4
	PE_E60_ND1_TNR_CTRL_34_T                                   tnr_ctrl_34;	//0xC90101E8
	PE_E60_ND1_TNR_CTRL_35_T                                   tnr_ctrl_35;	//0xC90101EC
	PE_E60_ND1_TNR_CTRL_36_T                                   tnr_ctrl_36;	//0xC90101F0
	PE_E60_ND1_TNR_CTRL_37_T                                   tnr_ctrl_37;	//0xC90101F4
	PE_E60_ND1_TNR_CTRL_38_T                                   tnr_ctrl_38;	//0xC90101F8
	PE_E60_ND1_TNR_CTRL_39_T                                   tnr_ctrl_39;	//0xC90101FC
	UINT32                                                    reserved1;	//0xC9010200
	UINT32                                                    reserved2;	//0xC9010204
	UINT32                                                    reserved3;	//0xC9010208
	UINT32                                                    reserved4;	//0xC901020C
	UINT32                                                    reserved5;	//0xC9010210
	UINT32                                                    reserved6;	//0xC9010214
	UINT32                                                    reserved7;	//0xC9010218
	UINT32                                                    reserved8;	//0xC901021C
	UINT32                                                    reserved9;	//0xC9010220
	UINT32                                                   reserved10;	//0xC9010224
	UINT32                                                   reserved11;	//0xC9010228
	UINT32                                                   reserved12;	//0xC901022C
	UINT32                                                   reserved13;	//0xC9010230
	UINT32                                                   reserved14;	//0xC9010234
	UINT32                                                   reserved15;	//0xC9010238
	UINT32                                                   reserved16;	//0xC901023C
	UINT32                                                   reserved17;	//0xC9010240
	UINT32                                                   reserved18;	//0xC9010244
	UINT32                                                   reserved19;	//0xC9010248
	UINT32                                                   reserved20;	//0xC901024C
	PE_E60_ND1_IPC_STATUS_00_T                               ipc_status_00;	//0xC9010250
	PE_E60_ND1_IPC_STATUS_01_T                               ipc_status_01;	//0xC9010254
	PE_E60_ND1_IPC_STATUS_02_T                               ipc_status_02;	//0xC9010258
	PE_E60_ND1_IPC_STATUS_03_T                               ipc_status_03;	//0xC901025C
	UINT32                                                   reserved21;	//0xC9010260
	UINT32                                                   reserved22;	//0xC9010264
	UINT32                                                   reserved23;	//0xC9010268
	UINT32                                                   reserved24;	//0xC901026C
	UINT32                                                   reserved25;	//0xC9010270
	UINT32                                                   reserved26;	//0xC9010274
	UINT32                                                   reserved27;	//0xC9010278
	UINT32                                                   reserved28;	//0xC901027C
	UINT32                                                   reserved29;	//0xC9010280
	UINT32                                                   reserved30;	//0xC9010284
	UINT32                                                   reserved31;	//0xC9010288
	UINT32                                                   reserved32;	//0xC901028C
	UINT32                                                   reserved33;	//0xC9010290
	UINT32                                                   reserved34;	//0xC9010294
	UINT32                                                   reserved35;	//0xC9010298
	UINT32                                                   reserved36;	//0xC901029C
	UINT32                                                   reserved37;	//0xC90102A0
	UINT32                                                   reserved38;	//0xC90102A4
	UINT32                                                   reserved39;	//0xC90102A8
	UINT32                                                   reserved40;	//0xC90102AC
	UINT32                                                   reserved41;	//0xC90102B0
	UINT32                                                   reserved42;	//0xC90102B4
	UINT32                                                   reserved43;	//0xC90102B8
	UINT32                                                   reserved44;	//0xC90102BC
	UINT32                                                   reserved45;	//0xC90102C0
	UINT32                                                   reserved46;	//0xC90102C4
	UINT32                                                   reserved47;	//0xC90102C8
	UINT32                                                   reserved48;	//0xC90102CC
	UINT32                                                   reserved49;	//0xC90102D0
	UINT32                                                   reserved50;	//0xC90102D4
	UINT32                                                   reserved51;	//0xC90102D8
	UINT32                                                   reserved52;	//0xC90102DC
	PE_E60_ND1_MMD_CTRL_T                                         mmd_ctrl;	//0xC90102E0
	UINT32                                                   reserved53;	//0xC90102E4
	UINT32                                                   reserved54;	//0xC90102E8
	UINT32                                                   reserved55;	//0xC90102EC
	UINT32                                                   reserved56;	//0xC90102F0
	UINT32                                                   reserved57;	//0xC90102F4
	UINT32                                                   reserved58;	//0xC90102F8
	UINT32                                                   reserved59;	//0xC90102FC
	UINT32                                                   reserved60;	//0xC9010300
	UINT32                                                   reserved61;	//0xC9010304
	UINT32                                                   reserved62;	//0xC9010308
	UINT32                                                   reserved63;	//0xC901030C
	UINT32                                                   reserved64;	//0xC9010310
	UINT32                                                   reserved65;	//0xC9010314
	UINT32                                                   reserved66;	//0xC9010318
	UINT32                                                   reserved67;	//0xC901031C
	UINT32                                                   reserved68;	//0xC9010320
	UINT32                                                   reserved69;	//0xC9010324
	PE_E60_ND1_IPC_STATUS_04_T                               ipc_status_04;	//0xC9010328
	PE_E60_ND1_IPC_STATUS_05_T                               ipc_status_05;	//0xC901032C
	PE_E60_ND1_IPC_STATUS_06_T                               ipc_status_06;	//0xC9010330
	PE_E60_ND1_IPC_STATUS_07_T                               ipc_status_07;	//0xC9010334
	PE_E60_ND1_IPC_STATUS_08_T                               ipc_status_08;	//0xC9010338
	PE_E60_ND1_IPC_STATUS_09_T                               ipc_status_09;	//0xC901033C
	PE_E60_ND1_TPD_CTRL_00_T                                   tpd_ctrl_00;	//0xC9010340
	PE_E60_ND1_TPD_CTRL_01_T                                   tpd_ctrl_01;	//0xC9010344
	PE_E60_ND1_TPD_CTRL_02_T                                   tpd_ctrl_02;	//0xC9010348
	PE_E60_ND1_TPD_CTRL_03_T                                   tpd_ctrl_03;	//0xC901034C
	PE_E60_ND1_TPD_CTRL_04_T                                   tpd_ctrl_04;	//0xC9010350
	PE_E60_ND1_TPD_CTRL_05_T                                   tpd_ctrl_05;	//0xC9010354
	PE_E60_ND1_TPD_CTRL_06_T                                   tpd_ctrl_06;	//0xC9010358
	PE_E60_ND1_TPD_CTRL_07_T                                   tpd_ctrl_07;	//0xC901035C
	PE_E60_ND1_TPD_CTRL_08_T                                   tpd_ctrl_08;	//0xC9010360
	PE_E60_ND1_TPD_CTRL_09_T                                   tpd_ctrl_09;	//0xC9010364
	PE_E60_ND1_TPD_STAT_00_T                                   tpd_stat_00;	//0xC9010368
	PE_E60_ND1_CLC_CTRL_07_T                                   clc_ctrl_07;	//0xC901036C
	PE_E60_ND1_BBD_CTRL_00_T                                   bbd_ctrl_00;	//0xC9010370
	PE_E60_ND1_BBD_CTRL_01_T                                   bbd_ctrl_01;	//0xC9010374
	PE_E60_ND1_BBD_CTRL_02_T                                   bbd_ctrl_02;	//0xC9010378
	PE_E60_ND1_BBD_STAT_00_T                                   bbd_stat_00;	//0xC901037C
	PE_E60_ND1_BBD_STAT_01_T                                   bbd_stat_01;	//0xC9010380
	PE_E60_ND1_APL_STAT_00_T                                   apl_stat_00;	//0xC9010384
	PE_E60_ND1_TPD_CTRL_0A_T                                   tpd_ctrl_0a;	//0xC9010388
	PE_E60_ND1_TPD_CTRL_0B_T                                   tpd_ctrl_0b;	//0xC901038C
	PE_E60_ND1_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0xC9010390
	PE_E60_ND1_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0xC9010394
	PE_E60_ND1_LVCRTL_CTRL_00_T                             lvcrtl_ctrl_00;	//0xC9010398
	PE_E60_ND1_TPD_STAT_01_T                                   tpd_stat_01;	//0xC901039C
	PE_E60_ND1_TNR_STATUS_05_T                               tnr_status_05;	//0xC90103A0
	PE_E60_ND1_TNR_STATUS_06_T                               tnr_status_06;	//0xC90103A4
	PE_E60_ND1_TNR_STATUS_07_T                               tnr_status_07;	//0xC90103A8
	PE_E60_ND1_TNR_STATUS_08_T                               tnr_status_08;	//0xC90103AC
	UINT32                                                   reserved70;	//0xC90103B0
	UINT32                                                   reserved71;	//0xC90103B4
	UINT32                                                   reserved72;	//0xC90103B8
	UINT32                                                   reserved73;	//0xC90103BC
	PE_E60_ND1_TNR_RESET_T                                       tnr_reset;	//0xC90103C0
	UINT32                                                   reserved74;	//0xC90103C4
	UINT32                                                   reserved75;	//0xC90103C8
	UINT32                                                   reserved76;	//0xC90103CC
	PE_E60_ND1_TNR_CTRL_40_T                                   tnr_ctrl_40;	//0xC90103D0
	PE_E60_ND1_TNR_CTRL_41_T                                   tnr_ctrl_41;	//0xC90103D4
	PE_E60_ND1_TNR_CTRL_42_T                                   tnr_ctrl_42;	//0xC90103D8
	PE_E60_ND1_TNR_CTRL_43_T                                   tnr_ctrl_43;	//0xC90103DC
	PE_E60_ND1_TNR_CTRL_44_T                                   tnr_ctrl_44;	//0xC90103E0
	PE_E60_ND1_TNR_CTRL_45_T                                   tnr_ctrl_45;	//0xC90103E4
	PE_E60_ND1_TNR_CTRL_46_T                                   tnr_ctrl_46;	//0xC90103E8
	PE_E60_ND1_TNR_CTRL_47_T                                   tnr_ctrl_47;	//0xC90103EC
	PE_E60_ND1_TNR_CTRL_48_T                                   tnr_ctrl_48;	//0xC90103F0
	UINT32                                                   reserved77;	//0xC90103F4
	UINT32                                                   reserved78;	//0xC90103F8
	UINT32                                                   reserved79;	//0xC90103FC
	PE_E60_ND1_TNR_NE_STAT_00_T                             tnr_ne_stat_00;	//0xC9010400
	PE_E60_ND1_TNR_NE_STAT_01_T                             tnr_ne_stat_01;	//0xC9010404
	PE_E60_ND1_TNR_NE_STAT_02_T                             tnr_ne_stat_02;	//0xC9010408
	PE_E60_ND1_TNR_NE_STAT_03_T                             tnr_ne_stat_03;	//0xC901040C
	PE_E60_ND1_TNR_NE_STAT_04_T                             tnr_ne_stat_04;	//0xC9010410
	PE_E60_ND1_TNR_NE_STAT_05_T                             tnr_ne_stat_05;	//0xC9010414
	PE_E60_ND1_TNR_NE_STAT_06_T                             tnr_ne_stat_06;	//0xC9010418
	PE_E60_ND1_TNR_NE_STAT_07_T                             tnr_ne_stat_07;	//0xC901041C
	PE_E60_ND1_TNR_NE_STAT_08_T                             tnr_ne_stat_08;	//0xC9010420
	UINT32                                                   reserved80;	//0xC9010424
	UINT32                                                   reserved81;	//0xC9010428
	UINT32                                                   reserved82;	//0xC901042C
	UINT32                                                   reserved83;	//0xC9010430
	UINT32                                                   reserved84;	//0xC9010434
	UINT32                                                   reserved85;	//0xC9010438
	UINT32                                                   reserved86;	//0xC901043C
	UINT32                                                   reserved87;	//0xC9010440
	UINT32                                                   reserved88;	//0xC9010444
	UINT32                                                   reserved89;	//0xC9010448
	UINT32                                                   reserved90;	//0xC901044C
	UINT32                                                   reserved91;	//0xC9010450
	UINT32                                                   reserved92;	//0xC9010454
	UINT32                                                   reserved93;	//0xC9010458
	UINT32                                                   reserved94;	//0xC901045C
	UINT32                                                   reserved95;	//0xC9010460
	UINT32                                                   reserved96;	//0xC9010464
	UINT32                                                   reserved97;	//0xC9010468
	UINT32                                                   reserved98;	//0xC901046C
	UINT32                                                   reserved99;	//0xC9010470
	UINT32                                                  reserved100;	//0xC9010474
	UINT32                                                  reserved101;	//0xC9010478
	UINT32                                                  reserved102;	//0xC901047C
	PE_E60_ND1_ND_FSW_CTRL_00_T                             nd_fsw_ctrl_00;	//0xC9010480
	PE_E60_ND1_ND_FSW_CTRL_01_T                             nd_fsw_ctrl_01;	//0xC9010484
	PE_E60_ND1_ND_FSW_CTRL_02_T                             nd_fsw_ctrl_02;	//0xC9010488
	PE_E60_ND1_ND_FSW_CTRL_03_T                             nd_fsw_ctrl_03;	//0xC901048C
	PE_E60_ND1_TNR_ETC_CTRL_00_T                           tnr_etc_ctrl_00;	//0xC9010490
	PE_E60_ND1_TNR_ETC_CTRL_01_T                           tnr_etc_ctrl_01;	//0xC9010494
	PE_E60_ND1_TNR_ETC_CTRL_02_T                           tnr_etc_ctrl_02;	//0xC9010498
	PE_E60_ND1_TNR_ETC_CTRL_03_T                           tnr_etc_ctrl_03;	//0xC901049C
	PE_E60_ND1_TNR_CTRL_56_T                                   tnr_ctrl_56;	//0xC90104A0
	PE_E60_ND1_TNR_CTRL_57_T                                   tnr_ctrl_57;	//0xC90104A4
	PE_E60_ND1_TNR_CTRL_58_T                                   tnr_ctrl_58;	//0xC90104A8
	PE_E60_ND1_TNR_CTRL_59_T                                   tnr_ctrl_59;	//0xC90104AC
	PE_E60_ND1_TNR_CTRL_60_T                                   tnr_ctrl_60;	//0xC90104B0
	PE_E60_ND1_TNR_CTRL_61_T                                   tnr_ctrl_61;	//0xC90104B4
	PE_E60_ND1_PE0_DEBUG3_T                                     pe0_debug3;	//0xC90104B8
	UINT32                                                  reserved103;	//0xC90104BC
	PE_E60_ND1_FBC_CTRL_02_T                                   fbc_ctrl_02;	//0xC90104C0
	PE_E60_ND1_FBC_CTRL_03_T                                   fbc_ctrl_03;	//0xC90104C4
	PE_E60_ND1_TNRW_M_IN_OFFSET_T                         tnrw_m_in_offset;	//0xC90104C8
	PE_E60_ND1_TNRW_M_OUT_SIZE_T                           tnrw_m_out_size;	//0xC90104CC
	PE_E60_ND1_GFD_CTRL_00_T                                   gfd_ctrl_00;	//0xC90104D0
	PE_E60_ND1_GFD_CTRL_01_T                                   gfd_ctrl_01;	//0xC90104D4
	PE_E60_ND1_GFD_STAT_00_T                                   gfd_stat_00;	//0xC90104D8
	PE_E60_ND1_GFD_STAT_01_T                                   gfd_stat_01;	//0xC90104DC
	PE_E60_ND1_GFD_STAT_02_T                                   gfd_stat_02;	//0xC90104E0
	PE_E60_ND1_GFD_STAT_03_T                                   gfd_stat_03;	//0xC90104E4
}PE_ND_ND1_REG_E60_T;

typedef struct {
	PE_E60_PE0_LOAD_T                                        pe0_load;	//0xC900E500
	PE_E60_PE0_INTR_T                                        pe0_intr;	//0xC900E504
	PE_E60_PE0_STATUS0_T                                  pe0_status0;	//0xC900E508
	PE_E60_PE0_STATUS1_T                                  pe0_status1;	//0xC900E50C
	PE_E60_PE0_OPMODE_T                                    pe0_opmode;	//0xC900E510
	PE_E60_PE0_IN_SIZE_T                                  pe0_in_size;	//0xC900E514
	PE_E60_PE0_IN_OFFSET_T                              pe0_in_offset;	//0xC900E518
	PE_E60_PE0_OUT_SIZE_T                                pe0_out_size;	//0xC900E51C
	PE_E60_WIN_CTRL_0_T                                    win_ctrl_0;	//0xC900E520
	PE_E60_WIN_CTRL_1_T                                    win_ctrl_1;	//0xC900E524
	PE_E60_WIN_CTRL_2_T                                    win_ctrl_2;	//0xC900E528
	PE_E60_WIN_CTRL_3_T                                    win_ctrl_3;	//0xC900E52C
	PE_E60_CUP_CTRL_00_T                                  cup_ctrl_00;	//0xC900E530
	PE_E60_CUP_CTRL_01_T                                  cup_ctrl_01;	//0xC900E534
	PE_E60_CUP_CTRL_02_T                                  cup_ctrl_02;	//0xC900E538
	UINT32                                                    reserved0;	//0xC900E53C
	UINT32                                                    reserved1;	//0xC900E540
	UINT32                                                    reserved2;	//0xC900E544
	UINT32                                                    reserved3;	//0xC900E548
	UINT32                                                    reserved4;	//0xC900E54C
	UINT32                                                    reserved5;	//0xC900E550
	UINT32                                                    reserved6;	//0xC900E554
	UINT32                                                    reserved7;	//0xC900E558
	UINT32                                                    reserved8;	//0xC900E55C
	UINT32                                                    reserved9;	//0xC900E560
	UINT32                                                   reserved10;	//0xC900E564
	UINT32                                                   reserved11;	//0xC900E568
	UINT32                                                   reserved12;	//0xC900E56C
	UINT32                                                   reserved13;	//0xC900E570
	UINT32                                                   reserved14;	//0xC900E574
	UINT32                                                   reserved15;	//0xC900E578
	UINT32                                                   reserved16;	//0xC900E57C
	PE_E60_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0xC900E580
	PE_E60_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0xC900E584
	PE_E60_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0xC900E588
	PE_E60_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xC900E58C
	PE_E60_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xC900E590
	PE_E60_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xC900E594
	PE_E60_DNR_DBAR_CTRL_T                              dnr_dbar_ctrl;	//0xC900E598
	PE_E60_REG_C420_CTRL_T                              reg_c420_ctrl;	//0xC900E59C
	PE_E60_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xC900E5A0
	PE_E60_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xC900E5A4
	PE_E60_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xC900E5A8
	PE_E60_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xC900E5AC
	PE_E60_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xC900E5B0
	PE_E60_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xC900E5B4
	PE_E60_DETAIL_CTRL_T                                  detail_ctrl;	//0xC900E5B8
	PE_E60_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xC900E5BC
	PE_E60_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xC900E5C0
	PE_E60_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xC900E5C4
	PE_E60_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xC900E5C8
	PE_E60_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xC900E5CC
	PE_E60_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xC900E5D0
	PE_E60_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xC900E5D4
	PE_E60_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xC900E5D8
	PE_E60_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xC900E5DC
	PE_E60_DNR_STAT_0_T                                    dnr_stat_0;	//0xC900E5E0
	PE_E60_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xC900E5E4
	PE_E60_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xC900E5E8
	PE_E60_DNR_STAT_1_T                                    dnr_stat_1;	//0xC900E5EC
	PE_E60_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xC900E5F0
	PE_E60_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xC900E5F4
	PE_E60_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xC900E5F8
	PE_E60_DNR_STAT_2_T                                    dnr_stat_2;	//0xC900E5FC
	PE_E60_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xC900E600
	PE_E60_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xC900E604
	PE_E60_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xC900E608
	PE_E60_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xC900E60C
	PE_E60_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xC900E610
	PE_E60_IFC_CTRL_0_T                                    ifc_ctrl_0;	//0xC900E614
	PE_E60_IFC_CTRL_1_T                                    ifc_ctrl_1;	//0xC900E618
	PE_E60_IFC_CTRL_2_T                                    ifc_ctrl_2;	//0xC900E61C
	PE_E60_IFC_CTRL_3_T                                    ifc_ctrl_3;	//0xC900E620
	PE_E60_IFC_CTRL_4_T                                    ifc_ctrl_4;	//0xC900E624
	PE_E60_IFC_CTRL_5_T                                    ifc_ctrl_5;	//0xC900E628
	PE_E60_IFC_CTRL_6_T                                    ifc_ctrl_6;	//0xC900E62C
	PE_E60_IFC_CTRL_7_T                                    ifc_ctrl_7;	//0xC900E630
	PE_E60_IFC_CTRL_8_T                                    ifc_ctrl_8;	//0xC900E634
	PE_E60_IFC_CTRL_9_T                                    ifc_ctrl_9;	//0xC900E638
	PE_E60_IFC_CTRL_10_T                                  ifc_ctrl_10;	//0xC900E63C
	PE_E60_IFC_CTRL_11_T                                  ifc_ctrl_11;	//0xC900E640
	PE_E60_IFC_CTRL_12_T                                  ifc_ctrl_12;	//0xC900E644
	PE_E60_IFC_CTRL_13_T                                  ifc_ctrl_13;	//0xC900E648
	PE_E60_IFC_CTRL_14_T                                  ifc_ctrl_14;	//0xC900E64C
	PE_E60_IFC_CTRL_15_T                                  ifc_ctrl_15;	//0xC900E650
	PE_E60_IFC_CTRL_16_T                                  ifc_ctrl_16;	//0xC900E654
	PE_E60_IFC_CTRL_17_T                                  ifc_ctrl_17;	//0xC900E658
	PE_E60_IFC_CTRL_18_T                                  ifc_ctrl_18;	//0xC900E65C
	PE_E60_IFC_CTRL_19_T                                  ifc_ctrl_19;	//0xC900E660
	PE_E60_IFC_CTRL_20_T                                  ifc_ctrl_20;	//0xC900E664
	PE_E60_IFC_CTRL_21_T                                  ifc_ctrl_21;	//0xC900E668
	PE_E60_SC_BNR_CTRL_0_T                              sc_bnr_ctrl_0;	//0xC900E66C
	PE_E60_SC_BNR_CTRL_1_T                              sc_bnr_ctrl_1;	//0xC900E670
	PE_E60_SC_BNR_CTRL_2_T                              sc_bnr_ctrl_2;	//0xC900E674
	PE_E60_SC_BNR_CTRL_3_T                              sc_bnr_ctrl_3;	//0xC900E678
	PE_E60_SC_BNR_CTRL_4_T                              sc_bnr_ctrl_4;	//0xC900E67C
	PE_E60_SC_BNR_CTRL_5_T                              sc_bnr_ctrl_5;	//0xC900E680
	PE_E60_SC_BNR_CTRL_6_T                              sc_bnr_ctrl_6;	//0xC900E684
	PE_E60_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xC900E688
	UINT32                                                   reserved17;	//0xC900E68C
	UINT32                                                   reserved18;	//0xC900E690
	UINT32                                                   reserved19;	//0xC900E694
	UINT32                                                   reserved20;	//0xC900E698
	PE_E60_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xC900E69C
	PE_E60_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xC900E6A0
	PE_E60_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xC900E6A4
	PE_E60_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xC900E6A8
	PE_E60_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xC900E6AC
	PE_E60_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xC900E6B0
	PE_E60_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xC900E6B4
	PE_E60_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xC900E6B8
	PE_E60_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xC900E6BC
	PE_E60_TPD_CTRL_0_T                                    tpd_ctrl_0;	//0xC900E6C0
	PE_E60_WINDOW_MODE_0_T                              window_mode_0;	//0xC900E6C4
	PE_E60_WINDOW_MODE_1_T                              window_mode_1;	//0xC900E6C8
	UINT32                                                   reserved21;	//0xC900E6CC
	PE_E60_DNR_STAT_3_T                                    dnr_stat_3;	//0xC900E6D0
	PE_E60_DNR_STAT_4_T                                    dnr_stat_4;	//0xC900E6D4
	PE_E60_DNR_STAT_5_T                                    dnr_stat_5;	//0xC900E6D8
	PE_E60_DNR_STAT_6_T                                    dnr_stat_6;	//0xC900E6DC
	PE_E60_DNR_STAT_7_T                                    dnr_stat_7;	//0xC900E6E0
	PE_E60_DNR_STAT_8_SC_BNR0_T                    dnr_stat_8_sc_bnr0;	//0xC900E6E4
	PE_E60_DNR_STAT_9_SC_BNR1_T                    dnr_stat_9_sc_bnr1;	//0xC900E6E8
	PE_E60_DNR_STAT_10_SC_BNR2_T                  dnr_stat_10_sc_bnr2;	//0xC900E6EC
	PE_E60_DNR_STAT_11_SQM_00_T                    dnr_stat_11_sqm_00;	//0xC900E6F0
	PE_E60_DNR_STAT_12_SQM_01_T                    dnr_stat_12_sqm_01;	//0xC900E6F4
	PE_E60_DNR_STAT_13_SQM_02_T                    dnr_stat_13_sqm_02;	//0xC900E6F8
	PE_E60_DNR_STAT_14_SQM_03_T                    dnr_stat_14_sqm_03;	//0xC900E6FC
	PE_E60_DNR_STAT_15_SQM_04_T                    dnr_stat_15_sqm_04;	//0xC900E700
	PE_E60_DNR_STAT_16_SQM_05_T                    dnr_stat_16_sqm_05;	//0xC900E704
	PE_E60_DNR_STAT_17_SQM_06_T                    dnr_stat_17_sqm_06;	//0xC900E708
	PE_E60_DNR_STAT_18_SQM_07_T                    dnr_stat_18_sqm_07;	//0xC900E70C
	PE_E60_DNR_STAT_19_SQM_08_T                    dnr_stat_19_sqm_08;	//0xC900E710
	PE_E60_DNR_STAT_20_SQM_09_T                    dnr_stat_20_sqm_09;	//0xC900E714
	PE_E60_DNR_STAT_21_SQM_10_T                    dnr_stat_21_sqm_10;	//0xC900E718
	PE_E60_DNR_STAT_22_SQM_11_T                    dnr_stat_22_sqm_11;	//0xC900E71C
	PE_E60_DNR_STAT_23_TPD_0_T                      dnr_stat_23_tpd_0;	//0xC900E720
	PE_E60_DNR_STAT_24_TPD_1_T                      dnr_stat_24_tpd_1;	//0xC900E724
	PE_E60_DNR_STAT_25_TPD_2_T                      dnr_stat_25_tpd_2;	//0xC900E728
	UINT32                                                   reserved22;	//0xC900E72C
	PE_E60_AC_BNR_15_T                                      ac_bnr_15;	//0xC900E730
	PE_E60_AC_BNR_16_T                                      ac_bnr_16;	//0xC900E734
	PE_E60_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0xC900E738
	PE_E60_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0xC900E73C
	PE_E60_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0xC900E740
	PE_E60_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0xC900E744
	PE_E60_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0xC900E748
	PE_E60_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0xC900E74C
	PE_E60_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0xC900E750
	PE_E60_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0xC900E754
	PE_E60_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0xC900E758
	PE_E60_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0xC900E75C
	PE_E60_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0xC900E760
	PE_E60_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xC900E764
	PE_E60_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xC900E768
	PE_E60_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xC900E76C
	PE_E60_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xC900E770
	PE_E60_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xC900E774
	PE_E60_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xC900E778
	PE_E60_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xC900E77C
	PE_E60_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xC900E780
	PE_E60_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xC900E784
	PE_E60_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xC900E788
	PE_E60_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xC900E78C
	PE_E60_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xC900E790
	PE_E60_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xC900E794
	PE_E60_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xC900E798
	PE_E60_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xC900E79C
	PE_E60_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xC900E7A0
	PE_E60_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xC900E7A4
	PE_E60_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xC900E7A8
	PE_E60_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xC900E7AC
	PE_E60_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xC900E7B0
	PE_E60_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xC900E7B4
	PE_E60_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xC900E7B8
	PE_E60_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xC900E7BC
	PE_E60_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xC900E7C0
	PE_E60_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xC900E7C4
	PE_E60_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xC900E7C8
	PE_E60_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xC900E7CC
	PE_E60_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xC900E7D0
	PE_E60_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xC900E7D4
	PE_E60_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xC900E7D8
	PE_E60_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xC900E7DC
	PE_E60_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xC900E7E0
	PE_E60_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xC900E7E4
	PE_E60_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xC900E7E8
	PE_E60_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xC900E7EC
	PE_E60_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xC900E7F0
	PE_E60_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xC900E7F4
	PE_E60_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xC900E7F8
	PE_E60_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xC900E7FC
	PE_E60_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xC900E800
	PE_E60_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xC900E804
	PE_E60_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xC900E808
	PE_E60_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xC900E80C
	PE_E60_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xC900E810
	PE_E60_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xC900E814
	PE_E60_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xC900E818
	PE_E60_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xC900E81C
	PE_E60_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xC900E820
	PE_E60_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xC900E824
	PE_E60_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xC900E828
	PE_E60_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xC900E82C
	PE_E60_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xC900E830
	PE_E60_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xC900E834
	PE_E60_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xC900E838
	PE_E60_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xC900E83C
	PE_E60_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xC900E840
	PE_E60_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xC900E844
	PE_E60_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xC900E848
	PE_E60_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xC900E84C
	PE_E60_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xC900E850
	PE_E60_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xC900E854
	PE_E60_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xC900E858
	PE_E60_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xC900E85C
	PE_E60_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xC900E860
	PE_E60_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xC900E864
	PE_E60_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xC900E868
	PE_E60_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xC900E86C
	PE_E60_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xC900E870
	PE_E60_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xC900E874
	PE_E60_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xC900E878
	PE_E60_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xC900E87C
	PE_E60_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xC900E880
	PE_E60_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xC900E884
	PE_E60_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xC900E888
	PE_E60_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xC900E88C
	PE_E60_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xC900E890
	PE_E60_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xC900E894
	PE_E60_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xC900E898
	PE_E60_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xC900E89C
	PE_E60_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xC900E8A0
	PE_E60_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xC900E8A4
	PE_E60_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xC900E8A8
	PE_E60_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xC900E8AC
	PE_E60_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xC900E8B0
	PE_E60_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xC900E8B4
	PE_E60_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xC900E8B8
	PE_E60_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xC900E8BC
	PE_E60_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xC900E8C0
	PE_E60_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xC900E8C4
	PE_E60_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xC900E8C8
	PE_E60_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xC900E8CC
	PE_E60_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xC900E8D0
	PE_E60_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xC900E8D4
	PE_E60_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xC900E8D8
	PE_E60_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xC900E8DC
	PE_E60_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xC900E8E0
	PE_E60_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xC900E8E4
	PE_E60_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xC900E8E8
	PE_E60_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xC900E8EC
	PE_E60_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xC900E8F0
	PE_E60_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xC900E8F4
	PE_E60_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xC900E8F8
	PE_E60_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xC900E8FC
	PE_E60_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xC900E900
	PE_E60_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xC900E904
	PE_E60_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xC900E908
	PE_E60_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xC900E90C
	PE_E60_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xC900E910
	PE_E60_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xC900E914
	PE_E60_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xC900E918
	PE_E60_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xC900E91C
	PE_E60_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xC900E920
	PE_E60_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xC900E924
	PE_E60_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xC900E928
}PE_ND_DNR0_REG_E60_T;

typedef struct {
	PE_E60_PSP_CTRL00_O_T                           psp_ctrl00;	//0xC900ED00
	PE_E60_PSP_CTRL01_O_T                           psp_ctrl01;	//0xC900ED04
	PE_E60_PSP_CTRL02_O_T                           psp_ctrl02;	//0xC900ED08
	PE_E60_EDGE_TH_O_T                                 edge_th;	//0xC900ED0C
	PE_E60_FG_POSITION_O_T                         fg_position;	//0xC900ED10
	PE_E60_PERSPECT_LUT_X0_O_T                 perspect_lut_x0;	//0xC900ED14
	PE_E60_PERSPECT_LUT_X1_O_T                 perspect_lut_x1;	//0xC900ED18
	PE_E60_PERSPECT_LUT_X2_O_T                 perspect_lut_x2;	//0xC900ED1C
	PE_E60_PERSPECT_LUT_X3_O_T                 perspect_lut_x3;	//0xC900ED20
	PE_E60_PERSPECT_LUT_Y0_O_T                 perspect_lut_y0;	//0xC900ED24
	PE_E60_PERSPECT_LUT_Y1_O_T                 perspect_lut_y1;	//0xC900ED28
	PE_E60_PERSPECT_LUT_Y2_O_T                 perspect_lut_y2;	//0xC900ED2C
	PE_E60_PERSPECT_LUT_Y3_O_T                 perspect_lut_y3;	//0xC900ED30
	PE_E60_PROB_MAP_O_T                               prob_map;	//0xC900ED34
	PE_E60_ELLIPS_MAP_O_T                           ellips_map;	//0xC900ED38
	PE_E60_PROB_DIFF_MAP_O_T                     prob_diff_map;	//0xC900ED3C
	PE_E60_OBJECT_MAP_O_T                           object_map;	//0xC900ED40
	PE_E60_BLUR_MAP_O_T                               blur_map;	//0xC900ED44
	PE_E60_DISPLAY_DEBUG_MAP_O_T             display_debug_map;	//0xC900ED48
	PE_E60_PSP_IIR_O_T                                 psp_iir;	//0xC900ED4C
	PE_E60_PSP_GAIN_O_T                               psp_gain;	//0xC900ED50
	PE_E60_PSP_DBG_MON00_O_T                     psp_dbg_mon00;	//0xC900ED54
	PE_E60_PSP_DBG_MON01_O_T                     psp_dbg_mon01;	//0xC900ED58
	PE_E60_VRTX_CPC_CTRL_O_T                     vrtx_cpc_ctrl;	//0xC900ED5C
	PE_E60_BLUR_HCOEF01_O_T                       blur_hcoef01;	//0xC900ED60
	PE_E60_BLUR_HCOEF23_O_T                       blur_hcoef23;	//0xC900ED64
	PE_E60_BLUR_HCOEF45_O_T                       blur_hcoef45;	//0xC900ED68
	PE_E60_BLUR_HCOEF67_O_T                       blur_hcoef67;	//0xC900ED6C
	PE_E60_BLUR_HCOEF8_O_T                         blur_hcoef8;	//0xC900ED70
	PE_E60_BLUR_VCOEF01_O_T                       blur_vcoef01;	//0xC900ED74
	PE_E60_BLUR_VCOEF23_O_T                       blur_vcoef23;	//0xC900ED78
	PE_E60_BLUR_VCOEF4_O_T                         blur_vcoef4;	//0xC900ED7C
	PE_E60_HISTOGRAM_0_O_T                         histogram_0;	//0xC900ED80
	PE_E60_HISTOGRAM_1_O_T                         histogram_1;	//0xC900ED84
	PE_E60_HISTOGRAM_2_O_T                         histogram_2;	//0xC900ED88
	PE_E60_HISTOGRAM_3_O_T                         histogram_3;	//0xC900ED8C
	PE_E60_HISTOGRAM_4_O_T                         histogram_4;	//0xC900ED90
	PE_E60_HISTOGRAM_5_O_T                         histogram_5;	//0xC900ED94
	PE_E60_HISTOGRAM_6_O_T                         histogram_6;	//0xC900ED98
	PE_E60_HISTOGRAM_7_O_T                         histogram_7;	//0xC900ED9C
	PE_E60_HISTOGRAM_8_O_T                         histogram_8;	//0xC900EDA0
	PE_E60_HISTOGRAM_9_O_T                         histogram_9;	//0xC900EDA4
	PE_E60_HISTOGRAM_10_O_T                       histogram_10;	//0xC900EDA8
	PE_E60_HISTOGRAM_11_O_T                       histogram_11;	//0xC900EDAC
	PE_E60_HISTOGRAM_12_O_T                       histogram_12;	//0xC900EDB0
	PE_E60_HISTOGRAM_13_O_T                       histogram_13;	//0xC900EDB4
	PE_E60_HISTOGRAM_14_O_T                       histogram_14;	//0xC900EDB8
	PE_E60_HISTOGRAM_15_O_T                       histogram_15;	//0xC900EDBC
	PE_E60_HISTOGRAM_16_O_T                       histogram_16;	//0xC900EDC0
	PE_E60_HISTOGRAM_17_O_T                       histogram_17;	//0xC900EDC4
	PE_E60_HISTOGRAM_18_O_T                       histogram_18;	//0xC900EDC8
	PE_E60_HISTOGRAM_19_O_T                       histogram_19;	//0xC900EDCC
	PE_E60_HISTOGRAM_20_O_T                       histogram_20;	//0xC900EDD0
	PE_E60_HISTOGRAM_21_O_T                       histogram_21;	//0xC900EDD4
	PE_E60_HISTOGRAM_22_O_T                       histogram_22;	//0xC900EDD8
	PE_E60_HISTOGRAM_23_O_T                       histogram_23;	//0xC900EDDC
	PE_E60_HISTOGRAM_24_O_T                       histogram_24;	//0xC900EDE0
	PE_E60_HISTOGRAM_25_O_T                       histogram_25;	//0xC900EDE4
	PE_E60_HISTOGRAM_26_O_T                       histogram_26;	//0xC900EDE8
	PE_E60_HISTOGRAM_27_O_T                       histogram_27;	//0xC900EDEC
	PE_E60_HISTOGRAM_28_O_T                       histogram_28;	//0xC900EDF0
	PE_E60_HISTOGRAM_29_O_T                       histogram_29;	//0xC900EDF4
	PE_E60_HISTOGRAM_30_O_T                       histogram_30;	//0xC900EDF8
	PE_E60_HISTOGRAM_31_O_T                       histogram_31;	//0xC900EDFC
	PE_E60_L5_GAIN_LUT1_O_T                       l5_gain_lut1;	//0xC900EE00
	PE_E60_L5_GAIN_LUT2_O_T                       l5_gain_lut2;	//0xC900EE04
	PE_E60_L0_GAIN_LUT1_O_T                       l0_gain_lut1;	//0xC900EE08
	PE_E60_L0_GAIN_LUT2_O_T                       l0_gain_lut2;	//0xC900EE0C
	PE_E60_EDGE_WIN_H_O_T                           edge_win_h;	//0xC900EE10
	PE_E60_EDGE_WIN_V_O_T                           edge_win_v;	//0xC900EE14
	PE_E60_EDGE0_FG_O_T                               edge0_fg;	//0xC900EE18
	PE_E60_EDGE0_BG_O_T                               edge0_bg;	//0xC900EE1C
	PE_E60_EDGE1_FG_O_T                               edge1_fg;	//0xC900EE20
	PE_E60_EDGE1_BG_O_T                               edge1_bg;	//0xC900EE24
	PE_E60_PSP_IIR1_O_T                               psp_iir1;	//0xC900EE28
	PE_E60_BG_MEASURE_CTRL_O_T                 bg_measure_ctrl;	//0xC900EE2C
	PE_E60_BG_MEASURE_READ0_O_T               bg_measure_read0;	//0xC900EE30
	PE_E60_BG_MEASURE_READ1_O_T               bg_measure_read1;	//0xC900EE34
	PE_E60_BG_MEASURE_READ2_O_T               bg_measure_read2;	//0xC900EE38
	PE_E60_BG_MEASURE_READ3_O_T               bg_measure_read3;	//0xC900EE3C
	PE_E60_BG_MEASURE_READ4_O_T               bg_measure_read4;	//0xC900EE40
}PE_DNR0_OBC_OBJT_REG_E60_T;

typedef struct {
	PE_E60_PSP_CTRL00_T                           psp_ctrl00;	//0xC900EF00
	PE_E60_PSP_CTRL01_T                           psp_ctrl01;	//0xC900EF04
	PE_E60_PSP_CTRL02_T                           psp_ctrl02;	//0xC900EF08
	PE_E60_EDGE_TH_T                                 edge_th;	//0xC900EF0C
	PE_E60_FG_POSITION_T                         fg_position;	//0xC900EF10
	PE_E60_RESERVED0_T                             reserved0;	//0xC900EF14
	PE_E60_RESERVED1_T                             reserved1;	//0xC900EF18
	PE_E60_RESERVED2_T                             reserved2;	//0xC900EF1C
	PE_E60_RESERVED3_T                             reserved3;	//0xC900EF20
	PE_E60_RESERVED4_T                             reserved4;	//0xC900EF24
	PE_E60_RESERVED5_T                             reserved5;	//0xC900EF28
	PE_E60_RESERVED6_T                             reserved6;	//0xC900EF2C
	PE_E60_RESERVED7_T                             reserved7;	//0xC900EF30
	PE_E60_PROB_MAP_T                               prob_map;	//0xC900EF34
	PE_E60_ELLIPS_MAP_T                           ellips_map;	//0xC900EF38
	PE_E60_PROB_DIFF_MAP_T                     prob_diff_map;	//0xC900EF3C
	PE_E60_OBJECT_MAP_T                           object_map;	//0xC900EF40
	PE_E60_BLUR_MAP_T                               blur_map;	//0xC900EF44
	PE_E60_DISPLAY_DEBUG_MAP_T             display_debug_map;	//0xC900EF48
	PE_E60_PSP_IIR_T                                 psp_iir;	//0xC900EF4C
	PE_E60_PSP_GAIN_T                               psp_gain;	//0xC900EF50
	PE_E60_PSP_DBG_MON00_T                     psp_dbg_mon00;	//0xC900EF54
	PE_E60_PSP_DBG_MON01_T                     psp_dbg_mon01;	//0xC900EF58
	PE_E60_VRTX_CPC_CTRL_T                     vrtx_cpc_ctrl;	//0xC900EF5C
	PE_E60_BLUR_HCOEF01_T                       blur_hcoef01;	//0xC900EF60
	PE_E60_BLUR_HCOEF23_T                       blur_hcoef23;	//0xC900EF64
	PE_E60_BLUR_HCOEF45_T                       blur_hcoef45;	//0xC900EF68
	PE_E60_BLUR_HCOEF67_T                       blur_hcoef67;	//0xC900EF6C
	PE_E60_BLUR_HCOEF8_T                         blur_hcoef8;	//0xC900EF70
	PE_E60_BLUR_VCOEF01_T                       blur_vcoef01;	//0xC900EF74
	PE_E60_BLUR_VCOEF23_T                       blur_vcoef23;	//0xC900EF78
	PE_E60_BLUR_VCOEF4_T                         blur_vcoef4;	//0xC900EF7C
	PE_E60_HISTOGRAM_0_T                         histogram_0;	//0xC900EF80
	PE_E60_HISTOGRAM_1_T                         histogram_1;	//0xC900EF84
	PE_E60_HISTOGRAM_2_T                         histogram_2;	//0xC900EF88
	PE_E60_HISTOGRAM_3_T                         histogram_3;	//0xC900EF8C
	PE_E60_HISTOGRAM_4_T                         histogram_4;	//0xC900EF90
	PE_E60_HISTOGRAM_5_T                         histogram_5;	//0xC900EF94
	PE_E60_HISTOGRAM_6_T                         histogram_6;	//0xC900EF98
	PE_E60_HISTOGRAM_7_T                         histogram_7;	//0xC900EF9C
	PE_E60_HISTOGRAM_8_T                         histogram_8;	//0xC900EFA0
	PE_E60_HISTOGRAM_9_T                         histogram_9;	//0xC900EFA4
	PE_E60_HISTOGRAM_10_T                       histogram_10;	//0xC900EFA8
	PE_E60_HISTOGRAM_11_T                       histogram_11;	//0xC900EFAC
	PE_E60_HISTOGRAM_12_T                       histogram_12;	//0xC900EFB0
	PE_E60_HISTOGRAM_13_T                       histogram_13;	//0xC900EFB4
	PE_E60_HISTOGRAM_14_T                       histogram_14;	//0xC900EFB8
	PE_E60_HISTOGRAM_15_T                       histogram_15;	//0xC900EFBC
	PE_E60_HISTOGRAM_16_T                       histogram_16;	//0xC900EFC0
	PE_E60_HISTOGRAM_17_T                       histogram_17;	//0xC900EFC4
	PE_E60_HISTOGRAM_18_T                       histogram_18;	//0xC900EFC8
	PE_E60_HISTOGRAM_19_T                       histogram_19;	//0xC900EFCC
	PE_E60_HISTOGRAM_20_T                       histogram_20;	//0xC900EFD0
	PE_E60_HISTOGRAM_21_T                       histogram_21;	//0xC900EFD4
	PE_E60_HISTOGRAM_22_T                       histogram_22;	//0xC900EFD8
	PE_E60_HISTOGRAM_23_T                       histogram_23;	//0xC900EFDC
	PE_E60_HISTOGRAM_24_T                       histogram_24;	//0xC900EFE0
	PE_E60_HISTOGRAM_25_T                       histogram_25;	//0xC900EFE4
	PE_E60_HISTOGRAM_26_T                       histogram_26;	//0xC900EFE8
	PE_E60_HISTOGRAM_27_T                       histogram_27;	//0xC900EFEC
	PE_E60_HISTOGRAM_28_T                       histogram_28;	//0xC900EFF0
	PE_E60_HISTOGRAM_29_T                       histogram_29;	//0xC900EFF4
	PE_E60_HISTOGRAM_30_T                       histogram_30;	//0xC900EFF8
	PE_E60_HISTOGRAM_31_T                       histogram_31;	//0xC900EFFC
	PE_E60_L5_GAIN_LUT1_T                       l5_gain_lut1;	//0xC900F000
	PE_E60_L5_GAIN_LUT2_T                       l5_gain_lut2;	//0xC900F004
	PE_E60_L0_GAIN_LUT1_T                       l0_gain_lut1;	//0xC900F008
	PE_E60_L0_GAIN_LUT2_T                       l0_gain_lut2;	//0xC900F00C
	PE_E60_EDGE_WIN_H_T                           edge_win_h;	//0xC900F010
	PE_E60_EDGE_WIN_V_T                           edge_win_v;	//0xC900F014
	PE_E60_EDGE0_FG_T                               edge0_fg;	//0xC900F018
	PE_E60_EDGE0_BG_T                               edge0_bg;	//0xC900F01C
	PE_E60_EDGE1_FG_T                               edge1_fg;	//0xC900F020
	PE_E60_EDGE1_BG_T                               edge1_bg;	//0xC900F024
	PE_E60_PSP_IIR1_T                               psp_iir1;	//0xC900F028
	PE_E60_BG_MEASURE_CTRL_T                 bg_measure_ctrl;	//0xC900F02C
	PE_E60_BG_MEASURE_READ0_T               bg_measure_read0;	//0xC900F030
	PE_E60_BG_MEASURE_READ1_T               bg_measure_read1;	//0xC900F034
	PE_E60_BG_MEASURE_READ2_T               bg_measure_read2;	//0xC900F038
	PE_E60_BG_MEASURE_READ3_T               bg_measure_read3;	//0xC900F03C
	PE_E60_BG_MEASURE_READ4_T               bg_measure_read4;	//0xC900F040
	PE_E60_FACE0_SET_T                             face0_set;	//0xC900F044
	PE_E60_FACE1_SET_T                             face1_set;	//0xC900F048
	PE_E60_FACE2_SET_T                             face2_set;	//0xC900F04C
	PE_E60_FACE3_SET_T                             face3_set;	//0xC900F050
	PE_E60_ELLIPS0_SET_T                         ellips0_set;	//0xC900F054
	PE_E60_ELLIPS1_SET_T                         ellips1_set;	//0xC900F058
	PE_E60_ELLIPS2_SET_T                         ellips2_set;	//0xC900F05C
	PE_E60_ELLIPS3_SET_T                         ellips3_set;	//0xC900F060
}PE_DNR0_OBC_FACE_REG_E60_T;

typedef struct {
	PE_E60_CTRL_CTRL_M0_Y_LEVEL_CTRL_T         ctrl_m0_y_level_ctrl; //0xC90030B8
}PE_TOP_IMX_REG_E60_T;

#endif
