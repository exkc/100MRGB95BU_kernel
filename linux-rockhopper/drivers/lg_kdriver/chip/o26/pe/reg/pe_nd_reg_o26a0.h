#ifndef _PE_ND_REG_O26A0_H_
#define _PE_ND_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC290100 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,RW,0x00) //load_time	0 := load at pic_init	1 = load when reg. write
	UINT32 load_enable                      :1;	//(1,RW,0x00) //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O26_ND_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290104 RW 0x0000_0000
	UINT32 intr_enable                      :1;	//(0,RW,0x00) //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//(6:4,RW,0x00) //interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  tnr_end  	'001 =  ipc_end	'010 = tnrw_y_end	'011 = tnrw_c_end	'100 = NA	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//(8,RW,0x00) //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//(26:16,RW,0x00) //the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_O26_ND_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290108 RO 0x0000_0000
	UINT32 tnr_frame_id                     :4;	//(3:0,RO,0x00) //TNR_FRAME_ID	increment every tnr_end
	UINT32 ipc_frame_id                     :4;	//(7:4,RO,0x00) //IPC_FRAME_ID	increment every ipc_end
	UINT32 tnrw_y_frame_id                  :4;	//(11:8,RO,0x00) //TNRW_Y_FRAME_ID	increment every tnrw_y_end
	UINT32 tnrw_c_frame_id                  :4;	//(15:12,RO,0x00) //TNRW_C_FRAME_ID	increment every tnrw_c_end
	UINT32 dnr_frame_id                     :8;	//(23:16,RO,0x0) //IPC_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//(27:24,RO,0x00) //PIC_INIT_FRAME_ID
	UINT32 resvd                            :4;
	};
}PE_O26_ND_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29010C RO 0x0000_0000
	UINT32 line_cnt                         :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 timer_cnt                        :16;	//(31:16,RO,0x0) //timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_O26_ND_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290110 RW 0x0030_0000
	UINT32 tnr_c_en                         :1;	//(0,RW,0x00) //TNR_C_enable	TNR_C memory read&write enable
	UINT32 tnr_y_en                         :1;	//(1,RW,0x00) //TNR_Y_enable	TNR_Y memory read&write enable
	UINT32 ipc_c_en                         :1;	//(2,RW,0x00) //IPC_C_enable	IPC_C memory read enable
	UINT32 ipc_y_en                         :1;	//(3,RW,0x00) //IPC_Y_enable	IPC_Y memory read enable
	UINT32 tnr_c_444_as_420                 :1;	//(4,RW,0x00) //Enable TNR_C(T1,T3)_422_AS_420	TNR_C behaves as if 420 mode even if the data in the memory 422 format	TNR_C reads only even line: 0,2,4,8 ...
	UINT32 tnr_y2_en                        :1;	//(5,RW,0x00) //Enable TNR_Y2	It should be enabled for CLC
	UINT32 force_422_to_420                 :1;	//(6,RW,0x00) //Enable FORCE_420	If the chroma sampling type is 422 and this flag enabled, then	(1) TNR chroma data in 422 format is subsampled to be 420 before being written to the memory	(2) TNR_C(T2), IPC_C(T1) read the data as 420 format	This flag might be used to reduce memory bandwidth for chroma data of TNR & IPC
	UINT32 ipc0_y_en_prog                   :1;	//(7,RW,0x00) //mem port ipc0_y enable
	UINT32 mif_last_mode                    :3;	//(10:8,RW,0x00) //you should set this value to 0x7 if you want MIF to work correctly in case of abnormal-pic_init
	UINT32 tnrw_off                         :1;	//(11,RW,0x00) //TNR write OFF
	UINT32 reg_tnr_single_en                :1;	//(12,RW,0x00) //TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 tnr_m_en                         :1;	//(13,RW,0x00) //TNR_M (motion info) memory read&write enable
	UINT32 force_444_to_422                 :1;	//(14,RW,0x00) //Enable FORCE_422	If the chroma sampling type is 444 and this flag enabled, then	(1) TNR chroma data in 444 format is subsampled to be 422 before being written to the memory	(2) TNR_C, IPC_C read the data as 422 format
	UINT32 resvd                            :1;
	UINT32 detour_enable                    :1;	//(16,RW,0x00) //
	UINT32 half_rate_en                     :1;	//(17,RW,0x00) //should be enabled for the interlaced source
	UINT32 ibuf_en                          :2;	//(19:18,RW,0x00) //(19) input buffer enable Y 	(18) input buffer enable C
	UINT32 minfo_hsample_mode               :3;	//(22:20,RW,0x03) //* this flag valid only if "tnr_m_en" = 1	* minfo_hsample_mode and minfo_qurt_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 4K or 1080p would be typical case for it   If this mode ON, It reduces hsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 = minfo hhalf mode disable	1 = minfo hhalf mode enable	2 = minfo hqurt mode enable	3 = reserved
	UINT32 minfo_vsample_mode               :3;	//(25:23,RW,0x00) //* this flag valid only if "tnr_m_en" = 1	* minfo_vsample_mode should be ON only if the input source is progressive and memory bandwidth is insufficient. 1080p would be typical case for it   If this mode ON, It reduces vsize of the minfo, which leads to the saving of the memory bandwidth when you turn "tnr_m_en" ON	0 := minfo vhalf mode disable	1 = minfo vhalf mode enable (V subsampling: 0,2,4,6,...)	2 = minfo vqurt mode enable (V subsampling: 0,4,8,12,...)	5 = minfo vhalf mode enable (V subsampling: 0,3,4,7,...)	6 = minfo vqurt mode enable (V subsampling: 2,6,10,14,...)
	UINT32 o_line_ctrl_mode                 :1;	//(26,RW,0x00) //0:= select odd line for Top field, even line for Bottom field	1 = select even line for Top field, odd line for Bottom field
	UINT32 o_line_ctrl_en                   :1;	//(27,RW,0x00) //output line subsample enable
	UINT32 tnr_in_lsb_mode                  :2;	//(29:28,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 m_run_id                         :2;	//(31:30,RW,0x00) //
	};
}PE_O26_ND_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290114 RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE: ??? ??. ??? ???? ??
	UINT32 resvd0                           :1;
	UINT32 cs_type                          :3;	//(15:13,RW,0x0) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE: ??? ??. ??? ???? ??	 (progressive format ??)
	UINT32 resvd1                           :3;
	UINT32 scan_type                        :1;	//(31,RW,0x00) //scan_type	1 : progressive	0 : interlaced
	};
}PE_O26_ND_PE0_SRC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290118 RW 0x0006_0000
	UINT32 field_id                         :1;	//(0,RW,0x00) //FIELD_ID	0 := top	1 = bottom
	UINT32 resvd0                           :3;
	UINT32 field_mode                       :2;	//(5:4,RW,0x00) //0 := manual field setting	1 = field auto-inversion	2 = use detected field 	3 = use detected field: inversion
	UINT32 field_inv                        :1;	//(6,RW,0x00) //field inversion enable: valid only if field_mode = 0
	UINT32 resvd1                           :1;
	UINT32 secam_line                       :1;	//(8,RW,0x00) //0 := Cb-line first	1 = Cr-line first
	UINT32 resvd2                           :3;
	UINT32 secam_line_mode                  :2;	//(13:12,RW,0x00) //0 := manual secam_cline	1 = manual secam_cline (inversion)	2 = use detected secam line	3 = use detected secam line(inversion)
	UINT32 resvd3                           :2;
	UINT32 out_cs_type                      :3;	//(18:16,RW,0x06) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 resvd4                           :1;
	UINT32 out_422_hsample_mode             :1;	//(20,RW,0x00) //0 := 0,2,4,6,?	1 = 1,3,5,7,?
	UINT32 out_420_vsample_mode             :1;	//(21,RW,0x00) //0 := 0,3,4,7,?	1 = 0,2,4,6,?
	UINT32 resvd5                           :10;
	};
}PE_O26_ND_PE0_FIELD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29011C RW 0x0000_0000
	UINT32 in_hsize                         :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 lend_manual_vsize                :1;	//(14,RW,0x00) //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_vsize	1 = internal line_end generated by in_vsize [11:0]
	UINT32 resvd1                           :1;
	UINT32 in_vsize                         :12;	//(27:16,RW,0x00) //
	UINT32 ptn_en_c                         :1;	//(28,RW,0x00) //
	UINT32 ptn_en_y                         :1;	//(29,RW,0x00) //
	UINT32 lend_manual_hsize                :1;	//(30,RW,0x00) //this flag is valid only if lend_ctrl_en = 0	0 := internal line_end generated by ND_hsize	1 = internal line_end generated by in_hsize [11:0]
	UINT32 lend_ctrl_en                     :1;	//(31,RW,0x00) //0 := use internla line_end	1 = use external line end
	};
}PE_O26_ND_PE0_DEBUG_LEND_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290120 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //??? ??. ??? ???? ??
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_IN_SIZE -> in_hsize	1 = PE0_IN_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290124 RW 0x0000_0000
	UINT32 hsize                            :12;	//(11:0,RW,0x00) //HSIZE : ??? ??. ??? ???? ??
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x00) //VSIZE : ??? ??. ??? ???? ??	 (progressive format ??)
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290128 RW 0x0000_0000
	UINT32 fbc_core_en_y                    :1;	//(0,RW,0x00) //
	UINT32 fbc_core_20p_y                   :1;	//(1,RW,0x00) //0 := 40% mode	1 = 20% mode
	UINT32 resvd0                           :2;
	UINT32 fbc_dual_haar_th_y               :4;	//(7:4,RW,0x00) //
	UINT32 resvd1                           :8;
	UINT32 fbc_dpcm_reset_mode_y            :2;	//(17:16,RW,0x00) //
	UINT32 resvd2                           :5;
	UINT32 fbc_en_y                         :1;	//(23,RW,0x00) //
	UINT32 resvd3                           :8;
	};
}PE_O26_ND_FBC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29012C RW 0x0000_0000
	UINT32 fbc_core_en_c                    :1;	//(0,RW,0x00) //
	UINT32 fbc_core_20p_c                   :1;	//(1,RW,0x00) //0 := 40% mode	1 = 20% mode
	UINT32 resvd0                           :2;
	UINT32 fbc_dual_haar_th_c               :4;	//(7:4,RW,0x00) //
	UINT32 resvd1                           :8;
	UINT32 fbc_dpcm_reset_mode_c            :2;	//(17:16,RW,0x00) //
	UINT32 resvd2                           :5;
	UINT32 fbc_en_c                         :1;	//(23,RW,0x00) //
	UINT32 resvd3                           :8;
	};
}PE_O26_ND_FBC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290130 RW 0x0000_0000
	UINT32 en_rd_t1_y                       :1;	//(0,RW,0x00) //Read T-1 Y Enable for IPC
	UINT32 en_rd_t1_c                       :1;	//(1,RW,0x00) //Read T-1 C Enable for IPC
	UINT32 en_rd_t2_y                       :1;	//(2,RW,0x00) //Read T-2 Y Enable for IPC, TNR
	UINT32 en_rd_t2_c                       :1;	//(3,RW,0x00) //Read T-2 C Enable for IPC, TNR
	UINT32 en_rd_t3_y                       :1;	//(4,RW,0x00) //Read T-3 Y Enable for IPC
	UINT32 en_rd_t3_c                       :1;	//(5,RW,0x00) //Read T-3 C Enable for IPC
	UINT32 en_rd_t4_y                       :1;	//(6,RW,0x00) //Read T-4 Y Enable for IPC, CLC
	UINT32 en_rd_t1_m                       :1;	//(7,RW,0x00) //Read Minfo Enable
	UINT32 en_wr_tnrw_y                     :1;	//(8,RW,0x00) //Write IPC, TNR, CLC Y Enable
	UINT32 en_wr_tnrw_c                     :1;	//(9,RW,0x00) //Write IPC, TNR, CLC C Enable
	UINT32 en_wr_tnrw_m                     :1;	//(10,RW,0x00) //Write Minfo Enable
	UINT32 resvd0                           :4;
	UINT32 manual_mem_off                   :1;	//(15,RW,0x00) //manual memory port off
	UINT32 resvd1                           :16;
	};
}PE_O26_ND_PE0_MEM_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290134 RW 0x0000_0000
	UINT32 lreq_dly_c                       :11;	//(10:0,RW,0x00) //unit: 16 de_clk
	UINT32 lreq_dly_c_en                    :1;	//(11,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 lreq_dly_y                       :11;	//(26:16,RW,0x00) //
	UINT32 lreq_dly_y_en                    :1;	//(27,RW,0x00) //
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_PE0_DEBUG_LREQ_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290138 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //??? ??. ??? ???? ??
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_IN_SIZE -> in_hsize	1 = PE0_IN_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_TNRW_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29013C RW 0x0000_0000
	UINT32 hsize                            :12;	//(11:0,RW,0x000) //HSIZE : ??? ??. ??? ???? ??
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x000) //VSIZE : ??? ??. ??? ???? ??	 (progressive format ??)
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_TNRW_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290140 RW 0x0000_0000
	UINT32 reg_tnr_en                       :1;	//(0:0,RW,0x00) //
	UINT32 resvd                            :31;
	};
}PE_O26_ND_TNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290144 RW 0x0000_0000
	UINT32 reg_dbg_show                     :4;	//(3:0,RW,0x00) //
	UINT32 reg_ma_motion_iir_alpha          :8;	//(11:4,RW,0x00) //for decontour, new
	UINT32 reg_ma_motion_iir_en             :1;	//(12,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_chroma_en          :1;	//(13,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_res                :2;	//(15:14,RW,0x0) //for decontour, new
	UINT32 reg_dbg_tnrw                     :2;	//(17:16,RW,0x00) //TNR Write? ?????. 	0 = TNR ?? (T)	1 = TNR ?? ?? (T)	2 = TNR ?? ?? (T-1)
	UINT32 reg_ma_motion_lsb6_sel           :1;	//(18,RW,0x0) //for decontour, new
	UINT32 reg_sad_8x3_lsb6_sel             :1;	//(19,RW,0x0) //new
	UINT32 reg_tnri_debug_mode              :2;	//(21:20,RW,0x00) //
	UINT32 reg_tnr_dbg_gain_sel             :2;	//(23:22,RW,0x00) //O24 New	00 : mamc gain	01 : sad mc	10 : sad ma	11 : abs_mv
	UINT32 reg_minfo_mode118                :4;	//(27:24,RW,0x00) //
	UINT32 reg_sc_scale2                    :3;	//(30:28,RW,0x00) //
	UINT32 resvd                            :1;
	};
}PE_O26_ND_TNR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290148 RW 0x0000_0000
	UINT32 sc_en                            :1;	//(0,RW,0x0) //scene change detection enable
	UINT32 sc_max_flt_en                    :1;	//(1,RW,0x0) //scene change: temporal max filter enable
	UINT32 sc_calc_prev_hist                :1;	//(2,RW,0x0) //scene change: calculation mode for previous histogram	0:= delay current histogram	1 = compute histogram for previous data
	UINT32 sc_chroma_en                     :1;	//(3,RW,0x00) //scene change: use of chroma histogram difference
	UINT32 sc_scale                         :3;	//(6:4,RW,0x0) //bit-select from 21bit scene change measure to 8-bit measure	0 := sc_measure[21 -1 :21-8]	1 = sc_measure [21 -3 :21-10]	2 = sc_measure [21 -5 :21-12]	3 = sc_measure [21 -7 :21-14]	4 = sc_measure [21 -9 :21-16]	5 = sc_measure [21-11:21-18]	6 = sc_measure [21-13:21-20]	7 = sc_measure [21-141:21-21]
	UINT32 resvd0                           :1;
	UINT32 sc_max_flt_tap                   :3;	//(10:8,RW,0x0) //scene change: temporal max filter tap
	UINT32 resvd1                           :1;
	UINT32 sc_chroma_gain                   :3;	//(14:12,RW,0x0) //scene change: gain of chroma histogram difference	0 := x1	1 = x1/2	2 = x1/4	3 = x1/8	4 = x1/16	5 = x1/32
	UINT32 sc_out_mode                      :1;	//(15,RW,0x00) //TNR_STATUS_04: scene change measure update mode	0:= update every frame	1 = update only if the scene_measure is larger than "sc_th_memc"
	UINT32 sc_th_ma                         :8;	//(23:16,RW,0x00) //scene change threshold for MA
	UINT32 sc_th_memc                       :8;	//(31:24,RW,0x00) //scene change threshold for MEMC
	};
}PE_O26_ND_TNR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29014C RW 0x0000_0000
	UINT32 show_dbg_bar_scale               :3;	//(2:0,RW,0x00) //debug bar scale
	UINT32 resvd0                           :1;
	UINT32 show_dbg_bar_en                  :4;	//(7:4,RW,0x00) //debug bar enable
	UINT32 resvd1                           :8;
	UINT32 show_dbg_bar0_mux                :4;	//(19:16,RW,0x00) //input mux for the lowest debug bar	0x0 := x_peak	0x1 = motion vector variance	0x2 = motion vector H	0x3 = motion vector V	0x4 = abs(NR-P2)	0x5 = abs(NR-CC)	0x6 = MA motion	0x7 = spatial variance	0x8 = scene change
	UINT32 show_dbg_bar1_mux                :4;	//(23:20,RW,0x00) //input mux for 2nd debug bar
	UINT32 show_dbg_bar2_mux                :4;	//(27:24,RW,0x00) //input mux for 3rd debug bar
	UINT32 show_dbg_bar3_mux                :4;	//(31:28,RW,0x00) //input mux for the highest debug bar
	};
}PE_O26_ND_TNR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290150 RW 0x0000_0000
	UINT32 manual_debug_bar_09              :8;	//(7:0,RW,0x0) //for manual debug mode ( reg_mux : 1001)
	UINT32 manual_debug_bar_10              :8;	//(15:8,RW,0x0) //for manual debug mode ( reg_mux : 1010)
	UINT32 manual_debug_bar_11              :8;	//(23:16,RW,0x0) //for manual debug mode ( reg_mux : 1011)
	UINT32 manual_debug_bar_12              :8;	//(31:24,RW,0x0) //for manual debug mode ( reg_mux : 1100)
	};
}PE_O26_ND_TNR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290154 RW 0x0000_0000
	UINT32 reg_mamc_blend_mode              :2;	//(1:0,RW,0x00) //
	UINT32 reg_mamc_blend_mv_max_or_sum     :1;	//(2,RW,0x00) //0: max, 1: sum
	UINT32 reg_mamc_ma_sad_cut              :1;	//(3,RW,0x00) //0: 6b, 1:2b
	UINT32 reg_mamc_mc_sad_cut              :1;	//(4,RW,0x00) //0: 6b, 1:2b
	UINT32 resvd0                           :11;
	UINT32 reg_mv_pv_fix_v                  :4;	//(19:16,RW,0x00) //
	UINT32 reg_mv_pv_fix_h                  :5;	//(24:20,RW,0x0) //
	UINT32 resvd1                           :6;
	UINT32 reg_mv_pv_fix_en                 :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_TNR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290158 RW 0x0000_0000
	UINT32 reg_me_lb_base                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_me_pv_base                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_me_lb_polarity               :1;	//(16,RW,0x00) //
	UINT32 resvd                            :15;
	};
}PE_O26_ND_TNR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29015C RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//(5:4,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_sc_en                        :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_ma_gain_yc_sel               :1;	//(12,RW,0x00) //new
	UINT32 resvd3                           :19;
	};
}PE_O26_ND_TNR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290160 RW 0x0000_0000
	UINT32 reg_mv_h_fix_val                 :5;	//(4:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_mv_v_fix_val                 :4;	//(11:8,RW,0x00) //
	UINT32 reg_mv_h_fix_fb_val              :5;	//(16:12,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_mv_v_fix_fb_val              :4;	//(23:20,RW,0x00) //
	UINT32 reg_debug_sel                    :4;	//(27:24,RW,0x00) //
	UINT32 reg_lb_monitor_sel               :2;	//(29:28,RW,0x00) //
	UINT32 reg_mv_fb_fix                    :1;	//(30,RW,0x00) //
	UINT32 reg_mv_fix                       :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_TNR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290164 RW 0x0000_0000
	UINT32 reg_sad_base                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lb_smooth_clip               :6;	//(13:8,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_pv_smooth_clip               :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :10;
	};
}PE_O26_ND_TNR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290168 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O26_ND_TNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29016C RW 0x8000_0000
	UINT32 lb_smooth_en                     :1;	//(0,RW,0x0) //
	UINT32 pv_smooth_en                     :1;	//(1,RW,0x0) //
	UINT32 pmv_hist_en                      :1;	//(2,RW,0x0) //new
	UINT32 reg_yonly_me_en                  :1;	//(3,RW,0x0) //new
	UINT32 resvd                            :27;
	UINT32 reg_me_n15_protection            :1;	//(31,RW,0x1) //
	};
}PE_O26_ND_TNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290170 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O26_ND_TNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290174 RW 0x0000_0000
	UINT32 reg_min_sad_ratio                :8;	//(7:0,RW,0x00) //new
	UINT32 reg_lb_cost_ratio                :8;	//(15:8,RW,0x00) //new
	UINT32 reg_zero_sad_ratio               :8;	//(23:16,RW,0x00) //new
	UINT32 reg_zero_mv_blk_mv_sel           :2;	//(25:24,RW,0x0) //chg
	UINT32 resvd0                           :2;
	UINT32 reg_zero_sad_adv                 :1;	//(28,RW,0x0) //chg
	UINT32 resvd1                           :3;
	};
}PE_O26_ND_TNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290178 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O26_ND_TNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29017C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O26_ND_TNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290180 RW 0x0000_0000
	UINT32 reg_sad_acc_mode                 :2;	//(1:0,RW,0x00) //
	UINT32 reg_bmv_fix_en                   :1;	//(2,RW,0x00) //
	UINT32 resvd0                           :1;
	UINT32 reg_bmv_fix_v                    :4;	//(7:4,RW,0x00) //
	UINT32 reg_bmv_fix_h                    :5;	//(12:8,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_n_hblk                       :4;	//(19:16,RW,0x00) //
	UINT32 reg_n_vblk                       :5;	//(24:20,RW,0x0) //
	UINT32 resvd2                           :7;
	};
}PE_O26_ND_TNR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290184 RW 0x0000_0000
	UINT32 reg_blk_vsize                    :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 reg_blk_hsize                    :12;	//(27:16,RW,0x00) //
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_TNR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290188 RW 0x0000_0000
	UINT32 reg_bsad_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 reg_bmv_rst_mode                 :1;	//(3,RW,0x00) //
	UINT32 reg_gsad_scale                   :3;	//(6:4,RW,0x00) //
	UINT32 resvd                            :1;
	UINT32 reg_gmv_gmv_tl                   :7;	//(14:8,RW,0x0) //
	UINT32 reg_gmv_gmv_tl_en                :1;	//(15,RW,0x0) //
	UINT32 reg_bmv_gmv_tl                   :7;	//(22:16,RW,0x0) //
	UINT32 reg_bmv_gmv_tl_en                :1;	//(23,RW,0x0) //
	UINT32 reg_bmv_pmv_tl                   :7;	//(30:24,RW,0x0) //
	UINT32 reg_bmv_pmv_tl_en                :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29018C RW 0x0000_0000
	UINT32 bmv_coring_th                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tl_equal_off                 :1;	//(12,RW,0x0) //O22
	UINT32 resvd1                           :3;
	UINT32 gmv_0mv_tl                       :7;	//(22:16,RW,0x0) //0MV ???? ?? ?? : x10? bypass?? ?? ?? ??? ??? ?
	UINT32 gmv_0mv_tl_en                    :1;	//(23,RW,0x00) //Global MV? 0MV ???? ? ????
	UINT32 bmv_0mv_tl                       :7;	//(30:24,RW,0x0) //0MV ???? ?? ?? : x10? bypass?? ?? ?? ??? ??? ?
	UINT32 bmv_0mv_tl_en                    :1;	//(31,RW,0x00) //Large Block MV? 0MV ???? ? ????
	};
}PE_O26_ND_TNR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290190 RW 0x0000_0000
	UINT32 reg_detail_beta_mul              :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_alpha_mul             :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_beta_mul                :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_alpha_mul               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290194 RW 0x0000_0000
	UINT32 reg_svar_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 reg_sad_8x3_res2                 :2;	//(9:8,RW,0x00) //
	UINT32 resvd1                           :22;
	};
}PE_O26_ND_TNR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290198 RW 0x0000_0000
	UINT32 resvd                            :1;
	UINT32 reg_nlvl_input_sel               :1;	//(1:1,RW,0x00) //
	UINT32 reg_sc_detect_hres               :1;	//(2:2,RW,0x00) //
	UINT32 reg_clc_nt_pal                   :1;	//(3:3,RW,0x00) //
	UINT32 reg_clc_mem_wr_mode              :2;	//(5:4,RW,0x00) //
	UINT32 reg_sad_8x3_res                  :2;	//(7:6,RW,0x00) //
	UINT32 reg_sad_8x3_iir_en               :1;	//(8:8,RW,0x00) //
	UINT32 reg_sad_8x3_chroma_en            :1;	//(9:9,RW,0x00) //
	UINT32 reg_minfo_sw                     :2;	//(11:10,RW,0x00) //
	UINT32 reg_minfo_mode10                 :2;	//(13:12,RW,0x00) //[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt                    :2;	//(15:14,RW,0x00) //
	UINT32 reg_hfr_mask_en                  :1;	//(16,RW,0x0) //
	UINT32 reg_decon_blend_en               :1;	//(17,RW,0x0) //chg
	UINT32 reg_minfo_mode32                 :2;	//(19:18,RW,0x00) //
	UINT32 reg_minfo_mode74                 :4;	//(23:20,RW,0x00) //
	UINT32 reg_sad_8x3_iir_alpha            :8;	//(31:24,RW,0x0) //for TNR, DNR
	};
}PE_O26_ND_TNR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29019C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O26_ND_TNR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901A0 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 reg_ombc_en                      :1;	//(1,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_luma_gain_en                 :1;	//(4,RW,0x00) //
	UINT32 reg_crgn_gain_en                 :1;	//(5,RW,0x00) //
	UINT32 reg_chroma_sad_res               :2;	//(7:6,RW,0x00) //
	UINT32 resvd2                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//(13:12,RW,0x00) //
	UINT32 resvd3                           :2;
	UINT32 reg_avg_cmp_en                   :1;	//(16,RW,0x00) //
	UINT32 reg_avg_cmp_res                  :3;	//(19:17,RW,0x00) //
	UINT32 reg_debug_sel                    :4;	//(23:20,RW,0x00) //
	UINT32 resvd4                           :4;
	UINT32 reg_cnt_mode                     :3;	//(30:28,RW,0x00) //
	UINT32 reg_chroma_sad_en                :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_TNR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901A4 RW 0xFF00_0000
	UINT32 resvd                            :24;
	UINT32 reg_skin_master_gain             :8;	//(31:24,RW,0xFF) //new
	};
}PE_O26_ND_TNR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901A8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901AC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901B0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O26_ND_TNR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901B4 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901B8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901BC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O26_ND_TNR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901C0 RO 0x0000_0000
	UINT32 w_gsad                           :8;	//(7:0,RO,0x0) //
	UINT32 w_gmv                            :9;	//(16:8,RO,0x00) //
	UINT32 resvd                            :7;
	UINT32 w_apl_detail                     :8;	//(31:24,RO,0x0) //
	};
}PE_O26_ND_TNR_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901C4 RO 0x0000_0000
	UINT32 w_apl_motion                     :8;	//(7:0,RO,0x0) //
	UINT32 w_apl_mc_sad                     :8;	//(15:8,RO,0x0) //
	UINT32 w_apl_var                        :8;	//(23:16,RO,0x0) //
	UINT32 w_apl_edge                       :8;	//(31:24,RO,0x0) //
	};
}PE_O26_ND_TNR_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901C8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901CC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901D0 RW 0x0000_0000
	UINT32 main_lut_indir_addr              :6;	//(5:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 main_lut_ai_enable               :1;	//(12,RW,0x00) //TNR Main-LUT Ctrl. AI enable
	UINT32 resvd1                           :2;
	UINT32 main_lut_load                    :1;	//(15,RW,0x00) //
	UINT32 resvd2                           :16;
	};
}PE_O26_ND_TNR_MAIN_LUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901D4 RW 0x0000_0000
	UINT32 main_lut_indir_data0             :32;	//(31:0,RW,0x0000_0000) //TNR Main-LUT Ctrl. Indirect Access Data 0 63:32 (MSB8u:Biggest, LSB8u:Smallest)
	};
}PE_O26_ND_TNR_MAIN_LUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901DC RO 0x0000_0000
	UINT32 sc_measure                       :8;	//(7:0,RO,0x0) //scene change detection measure
	UINT32 apl_y                            :8;	//(15:8,RO,0x0) //
	UINT32 sc_measure_16                    :16;	//(31:16,RO,0x0) //scene change measure (16b)
	};
}PE_O26_ND_TNR_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901E0 RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_gf_gain                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_blur_coef                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901E4 RW 0x0000_0000
	UINT32 same_protection_en               :1;	//(0,RW,0x00) //
	UINT32 reg_p_mv0_only                   :1;	//(1,RW,0x00) //
	UINT32 reg_p_non_mv0_only               :1;	//(2,RW,0x00) //new
	UINT32 reg_final_lut_y_en               :1;	//(3,RW,0x00) //new
	UINT32 reg_final_lut_c_en               :1;	//(4,RW,0x00) //new
	UINT32 reg_final_lut_clip_en            :1;	//(5,RW,0x00) //new
	UINT32 resvd0                           :2;
	UINT32 reg_same_sad_th                  :8;	//(15:8,RW,0x00) //
	UINT32 reg_move_step                    :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}PE_O26_ND_TNR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901E4 RW 0x0000_0000
	UINT32 same_protection_en               :1;	//(0,RW,0x00) //
	UINT32 reg_p_mv0_only                   :1;	//(1,RW,0x00) //
	UINT32 reg_p_non_mv0_only               :1;	//(2,RW,0x00) //new
	UINT32 reg_final_lut_en                 :1;	//(3,RW,0x00) //new
	UINT32 resvd0                           :4;
	UINT32 reg_same_sad_th                  :8;	//(15:8,RW,0x00) //
	UINT32 reg_move_step                    :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}PE_O26_ND1_TNR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901E8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901EC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901F0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O26_ND_TNR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901F4 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O26_ND_TNR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901F8 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O26_ND_TNR_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2901FC RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_blk_vhalf_en                 :1;	//(4,RW,0x00) //
	UINT32 reg_param_shift                  :2;	//(6:5,RW,0x00) //0 : SHR 7 / 1 : SHR 6 / 2 : SHR 5 / 3 : SHR 4
	UINT32 resvd1                           :1;
	UINT32 reg_init_motion                  :8;	//(15:8,RW,0x00) //1st frame init motion
	UINT32 reg_smg_force_motion             :8;	//(23:16,RW,0x00) //force sample motion data
	UINT32 resvd2                           :4;
	UINT32 reg_smg_pattern_en               :1;	//(28,RW,0x00) //ramp pattern sampled motion
	UINT32 reg_smg_force_en                 :1;	//(29,RW,0x00) //force sample motion - all motion is out as reg_smg_force_motion
	UINT32 resvd3                           :2;
	};
}PE_O26_ND_TNR_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290200 RW 0x0351_0006
	UINT32 cr_luma_mode                     :2;	//(1:0,RW,0x2) //Luma Operation Mode	'00 = Spatial Operation Only	'01 = Temporal Average Only	'1x := Motion Adaptive De-interlacing
	UINT32 resvd                            :1;
	UINT32 cr_n1_cc_blend_en                :1;	//(3,RW,0x0) //
	UINT32 cr_chroma_mode                   :2;	//(5:4,RW,0x0) //Chroma Operation Mode	'00 = Spatial Operation Only	'01 = Temporal Average Only	'1x := Motion Adaptive De-interlacing
	UINT32 cr_integer_edi                   :1;	//(6,RW,0x0) //
	UINT32 cr_chroma_edi                    :1;	//(7,RW,0x0) //
	UINT32 cr_st_2d_v_flt_range2            :4;	//(11:8,RW,0x0) //
	UINT32 cr_st_2d_v_flt_range             :4;	//(15:12,RW,0x0) //
	UINT32 cr_ori_3d_blur_y                 :2;	//(17:16,RW,0x1) //
	UINT32 cr_ori_3d_blur_c                 :2;	//(19:18,RW,0x0) //
	UINT32 cr_tava_v_edge_adap              :1;	//(20,RW,0x1) //
	UINT32 cr_tava_debug_mode               :1;	//(21,RW,0x0) //
	UINT32 cr_tava_st_adap                  :1;	//(22,RW,0x1) //
	UINT32 cr_tava_en                       :1;	//(23,RW,0x0) //
	UINT32 cr_hmc_force_fmd                 :1;	//(24,RW,0x1) //
	UINT32 cr_st_2d_v_flt_en                :1;	//(25,RW,0x1) //
	UINT32 cr_clc_fmd_off                   :1;	//(26,RW,0x0) //
	UINT32 cr_chroma_tava_only              :1;	//(27,RW,0x0) //
	UINT32 cr_film_auto_gain                :1;	//(28,RW,0x0) //
	UINT32 cr_film_apply_c                  :1;	//(29,RW,0x0) //
	UINT32 cr_film_apply_y                  :1;	//(30,RW,0x0) //
	UINT32 cr_film_mode_enable              :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290204 RW 0x0311_04C1
	UINT32 cr_hmc_en_sel1                   :2;	//(1:0,RW,0x1) //HMC, Enabled Input ID 1
	UINT32 cr_hmc_en_sel2                   :2;	//(3:2,RW,0x0) //HMC, Enabled Input ID 2
	UINT32 st_flt_mode                      :1;	//(4,RW,0x0) //0 : old , 1 : new
	UINT32 resvd0                           :1;
	UINT32 cr_fmd_vfilter_en                :1;	//(6,RW,0x1) //FMD, use hmc vfilter for FMD artifact reduce
	UINT32 cr_fend_auto                     :1;	//(7,RW,0x1) //FMD, frame_end position auto detect
	UINT32 cr_st_iir_dec_gain               :4;	//(11:8,RW,0x4) //
	UINT32 cr_st_iir_inc_gain               :4;	//(15:12,RW,0x0) //ST_IIR_alpha
	UINT32 cr_st_flt_enable                 :1;	//(16,RW,0x1) //
	UINT32 cr_st_iir_en                     :1;	//(17,RW,0x0) //
	UINT32 cr_hmc_flt_enable                :1;	//(18,RW,0x0) //
	UINT32 cr_game_mode                     :1;	//(19,RW,0x0) //
	UINT32 cr_st_2d_v_flt_range             :4;	//(23:20,RW,0x1) //
	UINT32 resvd1                           :1;
	UINT32 cr_black_mask                    :1;	//(25,RW,0x1) //
	UINT32 cr_ipc_debug_show                :5;	//(30:26,RW,0x0) //
	UINT32 cr_5f_mode                       :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290208 RW 0x904C_702F
	UINT32 fuzzy_ctrl_point_x0              :8;	//(7:0,RW,0x2F) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x4              :8;	//(15:8,RW,0x70) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x1              :8;	//(23:16,RW,0x4C) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y1              :8;	//(31:24,RW,0x90) //control points for 2D/3D decision
	};
}PE_O26_ND_IPC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29020C RW 0xF550_5038
	UINT32 fuzzy_ctrl_point_x2              :8;	//(7:0,RW,0x38) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y2              :8;	//(15:8,RW,0x50) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x3              :8;	//(23:16,RW,0x50) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y3              :8;	//(31:24,RW,0xF5) //control points for 2D/3D decision
	};
}PE_O26_ND_IPC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290210 RW 0x6000_4000
	UINT32 et_offset__s7                    :8;	//(7:0,RW,0x0) //signed 7bit (F5 means -10)	Smaller > Weight to 3D	Bigger > Weight to 2D
	UINT32 motion_x_tearing_gain            :8;	//(15:8,RW,0x40) //Motion Area Tearing Gain	80 := x2.0	40 = x1.0
	UINT32 tearing_gain                     :8;	//(23:16,RW,0x0) //All Area Tearing Gain ( Difficult to Excuse Pattern Tearing )
	UINT32 motion_gain                      :8;	//(31:24,RW,0x60) //Motion Gain	40 := x1.0
	};
}PE_O26_ND_IPC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290214 RW 0x6080_1010
	UINT32 resvd0                           :12;
	UINT32 cr_t_grad_weight                 :4;	//(15:12,RW,0x1) //Variance Normalize?? Variance? ??? ?? Gain
	UINT32 resvd1                           :4;
	UINT32 cr_v_grad_weight                 :4;	//(23:20,RW,0x8) //Variance Normalize?? Variance? ??? ?? Gain
	UINT32 resvd2                           :4;
	UINT32 cr_h_grad_weight                 :4;	//(31:28,RW,0x6) //Variance Normalize?? Variance? ??? ?? Gain
	};
}PE_O26_ND_IPC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290218 RW 0x0070_109F
	UINT32 cr_normalize_en                  :1;	//(0,RW,0x1) //Motion? Normalize ?? ??
	UINT32 cr_flat_only                     :1;	//(1,RW,0x1) //Normalize? x1.0??? ??? x1.0?? ??
	UINT32 cr_motion_iir_en                 :1;	//(2,RW,0x1) //IIR? TNR motion ? Blending?
	UINT32 resvd0                           :1;
	UINT32 cr_tearing_normalize_en          :1;	//(4,RW,0x1) //Tearing Score? Normalize ?? ??
	UINT32 resvd1                           :3;
	UINT32 cr_normalize_base                :8;	//(15:8,RW,0x10) //x (Center + a) / (Variance + a) ?? a? ???? ? , ???? ??? Normalize?
	UINT32 cr_normalize_center              :8;	//(23:16,RW,0x70) //Normalize? x1.0? ??? ?? Variance
	UINT32 cr_motion_coring                 :8;	//(31:24,RW,0x0) //Motion? ???? ?? ??? ??? 3D? ??
	};
}PE_O26_ND_IPC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29021C RW 0x80E0_025C
	UINT32 resvd0                           :1;
	UINT32 cr_v_en                          :1;	//(1,RW,0x0) //vertical Tearing Check Enable
	UINT32 cr_45_en                         :1;	//(2,RW,0x1) //45 degree Tearing Check enable
	UINT32 cr_15_en                         :1;	//(3,RW,0x1) //15 degree Tearing check Enable
	UINT32 resvd1                           :20;
	UINT32 cr_iir_motion_gain               :8;	//(31:24,RW,0x80) //motion_IIR_alpha
	};
}PE_O26_ND_IPC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290220 RW 0x0440_0320
	UINT32 fmd_caption_range_top            :12;	//(11:0,RW,0x320) //FMD, CaptionRange Top
	UINT32 resvd0                           :4;
	UINT32 fmd_caption_range_bot            :12;	//(27:16,RW,0x440) //FMD, CaptionRange Bottom
	UINT32 resvd1                           :2;
	UINT32 caption_flow_detected            :1;	//(30,RW,0x0) //Caption-Flow_Detected
	UINT32 hmc_when_cap_not_detected        :1;	//(31,RW,0x0) //Apply HMC Filter when "FilmDetected and CapFlowNotDetected and CaptionRange"	0 := apply HMC in CaptionRange only when capFlowDetected is 1	1 = apply HMC in CaptionRange even when capFlowDetected is 0
	};
}PE_O26_ND_IPC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290224 RW 0x00FF_2814
	UINT32 pn_fmd_a_th                      :8;	//(7:0,RW,0x14) //FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pn_variance_th                   :8;	//(23:16,RW,0xFF) //
	UINT32 pn_fmd_motion_th                 :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290228 RW 0x2010_0428
	UINT32 pcnc_fmd_a_th                    :8;	//(7:0,RW,0x28) //FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pcnc_variance_th                 :8;	//(23:16,RW,0x10) //
	UINT32 pcnc_fmd_motion_th               :8;	//(31:24,RW,0x20) //
	};
}PE_O26_ND_IPC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29022C RW 0x1600_05A0
	UINT32 cr_pndiff_th                     :8;	//(7:0,RW,0xA0) //
	UINT32 cr_center_bound_ctrl             :8;	//(15:8,RW,0x5) //
	UINT32 cr_dn_bound_ctrl                 :8;	//(23:16,RW,0x0) //
	UINT32 cr_up_bound_ctrl                 :8;	//(31:24,RW,0x16) //
	};
}PE_O26_ND_IPC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290230 RW 0xFF2A_100A
	UINT32 reg_still_pn_th                  :8;	//(7:0,RW,0xA) //FMD, threshold for still frame using pn_cnt (upper)
	UINT32 reg_fmd_ratio_th                 :8;	//(15:8,RW,0x10) //FMD, ratio of pc_cnt and nc_cnt (upper)
	UINT32 reg_fmd_max_th                   :8;	//(23:16,RW,0x2A) //FMD, max threshold for bigger value (pc_cnt/nc_cnt) (upper)
	UINT32 reg_fmd_min_th                   :8;	//(31:24,RW,0xFF) //FMD, min threshold for bigger value (pc_cnt/nc_cnt) (upper)
	};
}PE_O26_ND_IPC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290234 RW 0x2000_1001
	UINT32 cr_tava_chroma_mul               :8;	//(7:0,RW,0x1) //
	UINT32 resvd                            :4;
	UINT32 cr_hmc_alpha_th                  :8;	//(19:12,RW,0x1) //
	UINT32 cr_hmc_debug_mode                :1;	//(20,RW,0x0) //
	UINT32 cr_hmc_debug_gain                :6;	//(26:21,RW,0x0) //
	UINT32 cr_hmc_debug_dir                 :5;	//(31:27,RW,0x4) //
	};
}PE_O26_ND_IPC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290238 RW 0x0610_C019
	UINT32 reg_lockcnt_en                   :1;	//(0,RW,0x1) //FMD, Lockcnt enable (upper)
	UINT32 reserved                         :1;	//(1,Rsvd,0x0) //
	UINT32 reg_lock_speed                   :6;	//(7:2,RW,0x6) //FMD, Lockcnt increasing step (upper)
	UINT32 reg_lockcnt_th                   :8;	//(15:8,RW,0xC0) //FMD, Lockcnt threshold (upper)
	UINT32 reg_same_th                      :8;	//(23:16,RW,0x10) //FMD, threshold for same using pc_nc_same_cnt (upper)
	UINT32 reg_still_frame_limit            :8;	//(31:24,RW,0x6) //FMD, threshold for still (upper)
	};
}PE_O26_ND_IPC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29023C RW 0x6B38_0404
	UINT32 reg_3_2_detect_en                :1;	//(0,RW,0x0) //FMD, 3:2 detection mode enable (combinate with fmd decision result)(upper)
	UINT32 reg_3_2_detect_only              :1;	//(1,RW,0x0) //FMD, 3:2 detection mode enable (discard fmd decision result)(upper)
	UINT32 reg_3_2_lockcnt_255_en           :1;	//(2,RW,0x1) //FMD, lockcnt force increase enable when 3:2 detected(upper)
	UINT32 reg_3_2_pndiff_disable           :1;	//(3,RW,0x0) //FMD, 3:2 detection mode pndiff disable (upper)
	UINT32 reg_hd_mode                      :1;	//(4,RW,0x0) //Make Tearing Counts to 1/4 of SD (upper)
	UINT32 resvd                            :3;
	UINT32 reg_3_2_pndiff_th                :8;	//(15:8,RW,0x4) //FMD, 3:2 detection mode pndiff th (upper)
	UINT32 reg_3_2_pn_ratio_max_th          :8;	//(23:16,RW,0x38) //FMD, max threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper)
	UINT32 reg_3_2_pn_ratio_min_th          :8;	//(31:24,RW,0x6B) //FMD, min threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper
	};
}PE_O26_ND_IPC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290240 RW 0x5020_3804
	UINT32 reg_still_pn_th2                 :8;	//(7:0,RW,0x4) //FMD, threshold for pndiff_cnt (upper)
	UINT32 reg_still_prev_ratio             :8;	//(15:8,RW,0x38) //FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper)
	UINT32 reg_lock_reducer                 :8;	//(23:16,RW,0x20) //FMD, Lockcnt decreasing step (upper)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//(31,RW,0x0) //FMD, badedit protect (upper)
	};
}PE_O26_ND_IPC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290244 RW 0x5370_1030
	UINT32 cr_inv_resolution                :2;	//(1:0,RW,0x0) //
	UINT32 cr_field_manual_mode             :2;	//(3:2,RW,0x0) //
	UINT32 cr_field_inverse                 :1;	//(4,RW,0x1) //
	UINT32 resvd                            :19;
	UINT32 cr_tearing_a_th                  :8;	//(31:24,RW,0x53) //
	};
}PE_O26_ND_IPC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290248 RW 0xFF50DFCD
	UINT32 cr_ud_gain                       :8;	//(7:0,RW,0xCD) //| U - D | to 2D confidence (s7)
	UINT32 cr_lr_gain                       :8;	//(15:8,RW,0xDF) //| L - R | to 2D confidence (s7)
	UINT32 cr_h_grad_gain                   :8;	//(23:16,RW,0x50) //Horizontal Gradient to 2D confidence (s7)
	UINT32 cr_v_grad_gain                   :8;	//(31:24,RW,0xFF) //Vertical Gradient to 2D confidence (s7)
	};
}PE_O26_ND_IPC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29024C RW 0x0078_2438
	UINT32 reg_errs_gain                    :8;	//(7:0,RW,0x38) //
	UINT32 reg_confidence_gain              :8;	//(15:8,RW,0x24) //
	UINT32 reg_2d_offset                    :8;	//(23:16,RW,0x78) //
	UINT32 reg_flicker_gain                 :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290250 RO 0x0000_0000
	UINT32 r_pc_v_count                     :16;	//(15:0,RO,0x0) //FMD, vertical tearing count of pc (upper)
	UINT32 r_nc_v_count                     :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of nc (upper)
	};
}PE_O26_ND_IPC_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290254 RO 0x0000_0000
	UINT32 r_pc_nc_same                     :16;	//(15:0,RO,0x0) //FMD, same count between pc and nc (upper)
	UINT32 r_pn_v_count                     :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of pn (upper)
	};
}PE_O26_ND_IPC_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290258 RO 0x0000_0000
	UINT32 reserved                         :6;	//(5:0,Rsvd,0x0) //
	UINT32 r_fmd_32_min_th_flag_u           :1;	//(6,RO,0x00) //FMD, 3:2 detector min_th flag(upper)
	UINT32 r_fmd_32_max_th_flag_u           :1;	//(7,RO,0x00) //FMD, 3:2 detector max_th flag(upper)
	UINT32 r_fmd_still_limit_flag_u         :1;	//(8,RO,0x00) //FMD, still_limit flag(upper)
	UINT32 r_fmd_still_pn_th2_flag_u        :1;	//(9,RO,0x00) //FMD, still_pn_th2 flag(upper)
	UINT32 r_fmd_still_pn_th_flag_u         :1;	//(10,RO,0x00) //FMD, still_pn_th flag(upper)
	UINT32 r_fmd_still_prev_ratio_flag_u    :1;	//(11,RO,0x00) //FMD, still_prev_ratio flag(upper)
	UINT32 r_fmd_bigger_flag_u              :1;	//(12,RO,0x00) //FMD, bigger flag(upper)
	UINT32 r_fmd_smaller_flag_u             :1;	//(13,RO,0x00) //FMD, smaller flag(upper)
	UINT32 r_fmd_3_2_fmd_comb_mode_u        :2;	//(15:14,RO,0x00) //FMD, comb_flag of 3_2 mode (upper)
	UINT32 r_pn_diff_count                  :16;	//(31:16,RO,0x0) //FMD, pndiff count (upper)
	};
}PE_O26_ND_IPC_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29025C RO 0x0000_0000
	UINT32 same_ng_flag_d                   :1;	//(0,RO,0x00) //FMD, same condition but comb_flag is not NOTT(under)
	UINT32 too_small_flag_d                 :1;	//(1,RO,0x00) //FMD, meet toosmall condition (under)
	UINT32 r_fmd_still_flag_d               :1;	//(2,RO,0x00) //FMD, 1 : detect still (under)
	UINT32 r_fmd_possibility_flag_d         :1;	//(3,RO,0x00) //FMD, possibility flag of 3_2 mode(under)
	UINT32 base_pn_ratio_flag_d             :1;	//(4,RO,0x00) //FMD, meet reg_fmd_ratio_th condition (under)
	UINT32 r_32_detected_flag_d             :1;	//(5,RO,0x00) //FMD, 3:2 detect flag (under)
	UINT32 r_fmd_comb_mode_d                :2;	//(7:6,RO,0x00) //FMD, COMB_MODE of FMD Decision (under)
	UINT32 r_fmd_lock_count_d               :8;	//(15:8,RO,0x0) //FMD, LockCnt (under)
	UINT32 same_ng_flag_u                   :1;	//(16,RO,0x00) //FMD, same condition but comb_flag is not NOTT(upper)
	UINT32 too_small_flag_u                 :1;	//(17,RO,0x00) //FMD, meet toosmall condition (upper)
	UINT32 r_fmd_still_flag_u               :1;	//(18,RO,0x00) //FMD, 1 : detect still (upper)
	UINT32 r_fmd_possibility_flag_u         :1;	//(19,RO,0x00) //FMD, possibility flag of 3_2 mode(upper)
	UINT32 base_pn_ratio_flag_u             :1;	//(20,RO,0x00) //FMD, meet reg_fmd_ratio_th condition (upper)
	UINT32 r_32_uetected_flag_u             :1;	//(21,RO,0x00) //FMD, 3:2 detect flag (upper)
	UINT32 r_fmd_comb_mode_u                :2;	//(23:22,RO,0x00) //FMD, COMB_MODE of FMD Decision (upper)
	UINT32 r_fmd_lock_count_u               :8;	//(31:24,RO,0x0) //FMD, LockCnt (upper)
	};
}PE_O26_ND_IPC_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290260 RW 0xF88F_12F0
	UINT32 resvd0                           :1;
	UINT32 cl_filter_enable                 :1;	//(1,RW,0x00) //CL filter enable
	UINT32 clc_detection_enable             :1;	//(2,RW,0x00) //CL/CC detection enable
	UINT32 resvd1                           :1;
	UINT32 motion_window                    :2;	//(5:4,RW,0x03) //motion window	0 := 5x3	1 = 9x3	2 = 11x3	3 = 15x3
	UINT32 cl_pattern_dist                  :2;	//(7:6,RW,0x03) //CL pattern detection distance	0 := 2 (for SD, 480i/p)	1 = 4	2 = 5	3 = 6 (for HD, 1080i/p)
	UINT32 resvd2                           :4;
	UINT32 cl_ab_ratio                      :4;	//(15:12,RW,0x01) //CL motion a and b ratio(u2.2) : cl_ab_ratio * motion a < motion b
	UINT32 cl_y_hdistance                   :2;	//(17:16,RW,0x03) //CL horizontal distance for Y
	UINT32 cl_c_hdistance                   :2;	//(19:18,RW,0x03) //CL horizontal distance for C
	UINT32 cl_y_protect_en                  :1;	//(20,RW,0x00) //CL: Y level protection enable
	UINT32 resvd3                           :7;
	UINT32 cl_motion_a_filter               :1;	//(28,RW,0x01) //Filtering for motion a value for cl
	UINT32 cl_motion_b_filter               :1;	//(29,RW,0x01) //Filtering for motion b value for cl
	UINT32 cl_motion_a_mode                 :1;	//(30,RW,0x01) //Motion A mode '0' = NTSC/ '1' = PAL
	UINT32 resvd4                           :1;
	};
}PE_O26_ND_CLC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290264 RW 0x3250_0225
	UINT32 cl_motion_a_th                   :8;	//(7:0,RW,0x25) //CL motion a threshold, motion a is calculated between in-phase frame
	UINT32 cl_motion_b_th                   :8;	//(15:8,RW,0x2) //CL motion b threshold, motion b is calculated between out-of-phase phase frame
	UINT32 cl_y_protect_th0                 :8;	//(23:16,RW,0x50) //CL Y protect threshold 0
	UINT32 cl_y_protect_th1                 :8;	//(31:24,RW,0x32) //CL Y protect threshold 1
	};
}PE_O26_ND_CLC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290268 RW 0x1900_0985
	UINT32 cl_y_bound_th                    :7;	//(6:0,RW,0x5) //CL y boundary threshold
	UINT32 cl_c_bound_use_4line             :1;	//(7,RW,0x01) //0: use chroma 3 line	1: use chroma 4 line
	UINT32 cl_c_bound_th                    :7;	//(14:8,RW,0x9) //CL c boundary threshold
	UINT32 cl_c_bound_type                  :1;	//(15,RW,0x00) //CL c boundary type in calculation of c boundary	0 := Sum of h and v difference	1  = 2*Max of  h and v difference
	UINT32 cl_y_bound_width_chroma          :2;	//(17:16,RW,0x00) //CL y difference combination  with chroma for boundary detection	'00 = y only	'01 := Max(y,c)	'10 = y+c	'11 = y+c/2
	UINT32 cl_y_bound_ignore_cc             :1;	//(18,RW,0x00) //CL y boundary without considering CC(current frame)
	UINT32 cl_y_bound_ignore_p2             :1;	//(19,RW,0x00) //CL y boundary without considering P2(2 frame earlier)
	UINT32 cl_y_bound_ignore_p4             :1;	//(20,RW,0x00) //CL y boundary without considering P4(4 frame earlier)
	UINT32 reg_bin3x1_flt_en                :1;	//(21,RW,0x00) //CL binary filter for variance protection flag
	UINT32 resvd                            :2;
	UINT32 reg_bin5x1_flt_en                :1;	//(24,RW,0x01) //CL binary filter for variance protection flag
	UINT32 reg_bin5x1_flt_th                :3;	//(27:25,RW,0x04) //5x1 binary filter threshold
	UINT32 reg_vm_original_mode             :1;	//(28,RW,0x01) //variance measure original line select	'0' : CC only	'1' : MAX(P2CCN2)
	UINT32 reg_vm_other_mode                :1;	//(29,RW,0x00) //variance measure other field line select	'0' : vm original line only	'1' : MAX(vm_ori, P1N1)
	UINT32 cl_motionp2n2_th_pal_high        :2;	//(31:30,RW,0x00) //CL_MotionP2N2_Th_PAL(9:8) : high bit
	};
}PE_O26_ND_CLC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29026C RW 0xC030_F030
	UINT32 cl_sat_min                       :8;	//(7:0,RW,0x30) //CL saturation min value
	UINT32 resvd                            :2;
	UINT32 cl_var_measure_th1               :10;	//(19:10,RW,0x03C) //CL variance measure th
	UINT32 cl_var_measure_th2               :10;	//(29:20,RW,0x03) //CL motion P2N2 th for variance measure
	UINT32 cl_pt_enable                     :2;	//(31:30,RW,0x03) //CL protection enable	(31): variance protection enable	(30): tearing protection enable
	};
}PE_O26_ND_CLC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290270 RW 0x0000_0020
	UINT32 cl_tearing_pt_th1                :12;	//(11:0,RW,0x020) //CL Tearing protection threshold(no CL filtering)
	UINT32 cl_motionp2n2_th_pal_low         :8;	//(19:12,RW,0x0) //CL_MotionP2N2_Th_PAL(7:0) : low bit
	UINT32 cl_frame_min                     :12;	//(31:20,RW,0x00) //CL min detection pixel count per frame
	};
}PE_O26_ND_CLC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290274 RW 0x1FFD_8020
	UINT32 cl_data_line_switching_sel       :1;	//(0,RW,0x00) //0 = switching data line at [each line]	1 = switching data line at [each field]
	UINT32 resvd0                           :7;
	UINT32 clc_bin_flt_th                   :3;	//(10:8,RW,0x00) //CL_pt_map binary filtering(5x1) th
	UINT32 resvd1                           :4;
	UINT32 clc_bin_flt_en                   :1;	//(15,RW,0x01) //CL_pt_map binary filtering(1x3 -> 5x1) enable
	UINT32 clc_dbg_show_mask                :13;	//(28:16,RW,0x1FFD) //CLC Dbg Show Mask
	UINT32 resvd2                           :3;
	};
}PE_O26_ND_CLC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290278 RW 0xC000_3E00
	UINT32 cc_c_filter_gain                 :8;	//(7:0,RW,0x0) //CC ChromaFilter Gain
	UINT32 cc_y_filter_when_cc_detected     :1;	//(8,RW,0x0) //CC YFilter When CC Detected	0 = IPC(deinterlacer) output	1 = Average(n,n-2), n means frame index.
	UINT32 resvd0                           :1;
	UINT32 cl_cc_original_en                :1;	//(10,RW,0x1) //
	UINT32 clc_force_non_fmd                :1;	//(11,RW,0x1) //1: force FMD off when CL_pt_map = '1'	(if CL_pt_map = '0' FMD on)
	UINT32 cl_c_filter_when_cl_detected     :1;	//(12,RW,0x1) //0': IPC result(normal)	'1': Chroma temporal filtering((CC+N2)/2) by CL_pt_map
	UINT32 cl_y_filter_when_cl_detected     :1;	//(13,RW,0x1) //0': IPC result(normal)	'1': Luminance temporal filtering by CL_pt_map	should be OFF when 4K input
	UINT32 clc_filter_mode                  :2;	//(15:14,RW,0x0) //CLC filter select	11:(P2 + 2*CC + N2 )/4	10:(P2 + CC)/2	01:(P2 + N2)/2	00:(CC + N2)/2
	UINT32 resvd1                           :8;
	UINT32 cl_cc_protection_th              :8;	//(31:24,RW,0xC0) //
	};
}PE_O26_ND_CLC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29027C RO 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 cl_detection_count               :16;	//(31:16,RO,0x0) //CL detection pixel count
	};
}PE_O26_ND_CLC_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290280 RW 0x3EFF_3000
	UINT32 tava_v_diff_y0                   :8;	//(7:0,RW,0x0) //
	UINT32 tava_v_diff_x0                   :8;	//(15:8,RW,0x30) //
	UINT32 tava_v_diff_y1                   :8;	//(23:16,RW,0xFF) //
	UINT32 tava_v_diff_x1                   :8;	//(31:24,RW,0x3E) //
	};
}PE_O26_ND_IPC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290284 RW 0x0000_0002
	UINT32 reg_div_en                       :1;	//(0,RW,0x0) //FMD, div mode enable
	UINT32 cr_bound_exp_en                  :1;	//(1,RW,0x1) //FMD, cr bound enable
	UINT32 resvd0                           :2;
	UINT32 cr_sub_main_sel                  :1;	//(4,RW,0x0) //(??) FMD, 0:main path, 1:sub path
	UINT32 resvd1                           :11;
	UINT32 reg_manual_en                    :1;	//(16,RW,0x0) //FMD, manual mode enable
	UINT32 resvd2                           :3;
	UINT32 reg_manual_mode2                 :2;	//(21:20,RW,0x0) //FMD, manual mode COMB_MODE (under)
	UINT32 reg_manual_mode1                 :2;	//(23:22,RW,0x0) //FMD, manual mode COMB_MODE (upper)
	UINT32 reg_div_position                 :8;	//(31:24,RW,0x0) //FMD, div mode upper/under boundary position
	};
}PE_O26_ND_IPC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290288 RW 0xFF28_1003
	UINT32 reg_still_pn_th                  :8;	//(7:0,RW,0x3) //FMD, threshold for still frame using pn_cnt (under)
	UINT32 reg_fmd_ratio_th                 :8;	//(15:8,RW,0x10) //FMD, ratio of pc_cnt and nc_cnt (under)
	UINT32 reg_fmd_max_th                   :8;	//(23:16,RW,0x28) //FMD, max threshold for bigger value (pc_cnt/nc_cnt) (under)
	UINT32 reg_fmd_min_th                   :8;	//(31:24,RW,0xFF) //FMD, min threshold for bigger value (pc_cnt/nc_cnt) (under)
	};
}PE_O26_ND_IPC_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29028C RW 0x0752_C061
	UINT32 reg_lockcnt_en                   :1;	//(0,RW,0x1) //FMD, Lockcnt enable (under)
	UINT32 reserved                         :1;	//(1,Rsvd,0x0) //
	UINT32 reg_lock_speed                   :6;	//(7:2,RW,0x18) //FMD, Lockcnt increasing step (under)
	UINT32 reg_lockcnt_th                   :8;	//(15:8,RW,0xC0) //FMD, Lockcnt threshold (under)
	UINT32 reg_same_th                      :8;	//(23:16,RW,0x52) //FMD, threshold for same using pc_nc_same_cnt (under)
	UINT32 reg_still_frame_limit            :8;	//(31:24,RW,0x7) //FMD, threshold for still (under)
	};
}PE_O26_ND_IPC_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290290 RW 0x6A38_0404
	UINT32 reg_3_2_detect_en                :1;	//(0,RW,0x0) //FMD, 3:2 detection mode enable (combinate with fmd decision result) (under)
	UINT32 reg_3_2_detect_only              :1;	//(1,RW,0x0) //FMD, 3:2 detection mode enable (discard fmd decision result) (under)
	UINT32 reg_3_2_lockcnt_255_en           :1;	//(2,RW,0x1) //FMD, lockcnt force increase enable when 3:2 detected(under)
	UINT32 reg_3_2_pndiff_disable           :1;	//(3,RW,0x0) //FMD, 3:2 detection mode pndiff disable (under)
	UINT32 reg_hd_mode                      :1;	//(4,RW,0x0) //Make Tearing Counts to 1/4 of SD (under)
	UINT32 resvd                            :3;
	UINT32 reg_3_2_pndiff_th                :8;	//(15:8,RW,0x4) //FMD, 3:2 detection mode pndiff th (under)
	UINT32 reg_3_2_pn_ratio_max_th          :8;	//(23:16,RW,0x38) //FMD, max threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	UINT32 reg_3_2_pn_ratio_min_th          :8;	//(31:24,RW,0x6A) //FMD, min threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	};
}PE_O26_ND_IPC_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290294 RW 0x5370_0804
	UINT32 reg_still_pn_th2                 :8;	//(7:0,RW,0x4) //FMD, threshold for pndiff_cnt (under)
	UINT32 reg_still_prev_ratio             :8;	//(15:8,RW,0x8) //FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	UINT32 reg_lock_reducer                 :8;	//(23:16,RW,0x70) //FMD, Lockcnt decreasing step (under)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//(31,RW,0x0) //FMD, badedit protect (under)
	};
}PE_O26_ND_IPC_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290298 RW 0x0000_3507
	UINT32 reg_toosmall_en                  :1;	//(0,RW,0x1) //FMD, toosmall mode enable (under)
	UINT32 reg_toosmall_min                 :7;	//(7:1,RW,0x3) //FMD, min value of toosmall condition (under)
	UINT32 reg_toosmall_max                 :8;	//(15:8,RW,0x35) //FMD, max value of toosmall condition (under)
	UINT32 reg_pndiff_disable               :1;	//(16,RW,0x0) //FMD, pndiff mode off (under)
	UINT32 resvd                            :15;
	};
}PE_O26_ND_IPC_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29029C RW 0x0000_01E0
	UINT32 reg_fend_position                :11;	//(10:0,RW,0x1E0) //
	UINT32 resvd0                           :1;
	UINT32 cr_sc_length                     :3;	//(14:12,RW,0x0) //
	UINT32 resvd1                           :11;
	UINT32 cr_vmc_dir                       :3;	//(28:26,RW,0x0) //Force VMC
	UINT32 resvd2                           :2;
	UINT32 cr_vmc_en                        :1;	//(31,RW,0x0) //Force VMC
	};
}PE_O26_ND_IPC_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902A0 RW 0x0000_3098
	UINT32 reg_yy_diff_gain                 :4;	//(3:0,RW,0x8) //Luma Motion Gain
	UINT32 reg_hv_add_gain                  :4;	//(7:4,RW,0x9) //HV Separable Motion Gain
	UINT32 reg_v_motion_gain                :4;	//(11:8,RW,0x0) //V Motion Gain
	UINT32 reg_h_motion_gain                :4;	//(15:12,RW,0x3) //H Motion Gain
	UINT32 reg_cc_diff_gain                 :4;	//(19:16,RW,0x0) //Chroma Motion Gain
	UINT32 resvd                            :12;
	};
}PE_O26_ND_IPC_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902A4 RW 0x0000_0000
	UINT32 n1b_motion_gain_y0               :8;	//(7:0,RW,0x0) //
	UINT32 n1b_motion_gain_x0               :8;	//(15:8,RW,0x0) //
	UINT32 n1b_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 n1b_motion_gain_x1               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902A8 RW 0x0000_0000
	UINT32 n1b_variance_gain_y0             :8;	//(7:0,RW,0x0) //
	UINT32 n1b_variance_gain_x0             :8;	//(15:8,RW,0x0) //
	UINT32 n1b_variance_gain_y1             :8;	//(23:16,RW,0x0) //
	UINT32 n1b_variance_gain_x1             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902AC RW 0x0000_0000
	UINT32 reg_hmc_use_tnr_mv               :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 reg_cr_hmc_y_th                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 max_penalty                      :8;	//(23:16,RW,0x0) //
	UINT32 min_penalty                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902B0 RW 0x0000_0000
	UINT32 reg_min_diff_th                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_edi_va_blend_mul             :10;	//(17:8,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_edi_va_protect_mul           :10;	//(29:20,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_m16_edi_va_blend_en          :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902B4 RW 0x0000_0000
	UINT32 reg_max_va_diff_th               :8;	//(7:0,RW,0x0) //
	UINT32 reg_max_edi_diff_th              :8;	//(15:8,RW,0x0) //
	UINT32 reg_edi_va_protect_min           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edi_va_blend_min             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902B8 RW 0x0000_0000
	UINT32 reg_2d_top_lut_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_2d_top_lut_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_2d_top_lut_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_2d_top_lut_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902BC RW 0x0000_0000
	UINT32 cr_hmc_enable_1                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_1                     :7;	//(7:1,RW,0x0) //
	UINT32 cr_lr_ratio_th_1                 :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_expend_1                  :3;	//(18:16,RW,0x0) //
	UINT32 cr_lr_ratio_check_en_1           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_1                  :4;	//(23:20,RW,0x0) //
	UINT32 cr_center_weight_1               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902C0 RW 0x0000_0000
	UINT32 cr_hmc_enable_2                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_2                     :7;	//(7:1,RW,0x0) //
	UINT32 cr_lr_ratio_th_2                 :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_expend_2                  :3;	//(18:16,RW,0x0) //
	UINT32 cr_lr_ratio_check_en_2           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_2                  :4;	//(23:20,RW,0x0) //
	UINT32 cr_center_weight_2               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902C4 RW 0x0000_0000
	UINT32 line_cnt_th_0                    :12;	//(11:0,RW,0x0) //
	UINT32 line_cnt_th_1                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_ND_IPC_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902C8 RW 0x0000_0000
	UINT32 cr_n1b_limit                     :9;	//(8:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 cr_n1b_resolution                :3;	//(14:12,RW,0x0) //
	UINT32 resvd1                           :9;
	UINT32 cr_pre_sc_th                     :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902CC RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_y0               :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x0               :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_ND_IPC_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902D0 RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_y1               :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x1               :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_ND_IPC_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902D4 RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_en               :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 cr_hmc_text_rgn_sad_max          :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_text_rgn_sad_min          :8;	//(23:16,RW,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O26_ND_IPC_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902E0 RW 0x0000_0000
	UINT32 mmd_vtap_yy                      :2;	//(1:0,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd0                           :2;
	UINT32 mmd_htap_yy                      :2;	//(5:4,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd1                           :2;
	UINT32 mmd_vtap_cc                      :2;	//(9:8,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd2                           :2;
	UINT32 mmd_htap_cc                      :2;	//(13:12,RW,0x00) //// 0: 9-tap,  1: 13-tap,  2: 15-tap,  3: 17-tap,
	UINT32 resvd3                           :2;
	UINT32 reg_chroma_mmd_en                :1;	//(16,RW,0x00) //0 := off	1 := on
	UINT32 resvd4                           :15;
	};
}PE_O26_ND_MMD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902F0 RW 0x4040_18B0
	UINT32 reg_cubic_coef0                  :8;	//(7:0,RW,0xB0) //
	UINT32 reg_cubic_coef1                  :8;	//(15:8,RW,0x18) //
	UINT32 reg_va_blending_ctrl_lv1         :3;	//(18:16,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_va_blending_ctrl_lv2         :3;	//(22:20,RW,0x4) //
	UINT32 resvd1                           :1;
	UINT32 reg_va_blending_ctrl_lv3         :3;	//(26:24,RW,0x0) //
	UINT32 resvd2                           :1;
	UINT32 reg_va_blending_ctrl_lv4         :3;	//(30:28,RW,0x4) //
	UINT32 resvd3                           :1;
	};
}PE_O26_ND_IPC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902F4 RW 0xCD51_991C
	UINT32 reg_va_cubic                     :1;	//(0,RW,0x0) //
	UINT32 reg_boundary_window              :1;	//(1,RW,0x0) //
	UINT32 reg_force_va                     :1;	//(2,RW,0x1) //
	UINT32 reg_half_pel_va                  :1;	//(3,RW,0x1) //
	UINT32 reg_dir_med_tap                  :2;	//(5:4,RW,0x1) //
	UINT32 reg_diff_med_tap                 :2;	//(7:6,RW,0x0) //
	UINT32 reg_va_blending_ctrl1            :3;	//(10:8,RW,0x1) //
	UINT32 reg_wide_angle_protection_1      :1;	//(11,RW,0x1) //
	UINT32 reg_va_blending_ctrl2            :3;	//(14:12,RW,0x1) //
	UINT32 reg_wide_angle_protection_2      :1;	//(15,RW,0x1) //
	UINT32 reg_errs_chroma_blend_coef       :8;	//(23:16,RW,0x51) //
	UINT32 reg_strong_global_th             :6;	//(29:24,RW,0xD) //
	UINT32 narrow_angle_week                :1;	//(30,RW,0x1) //
	UINT32 narrow_angle_protection          :1;	//(31,RW,0x1) //
	};
}PE_O26_ND_IPC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902F8 RW 0xFFCC_2058
	UINT32 cr_vmc_v_diff_max                :8;	//(7:0,RW,0x58) //
	UINT32 cr_vmc_v_diff_protect_mul        :8;	//(15:8,RW,0x20) //
	UINT32 es_err_value                     :8;	//(23:16,RW,0xCC) //
	UINT32 et_err_value                     :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_ND_IPC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2902FC RW 0xB857_C010
	UINT32 cr_hmc_enable_0                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_0                     :7;	//(7:1,RW,0x8) //
	UINT32 cr_lr_ratio_th_0                 :8;	//(15:8,RW,0xC0) //
	UINT32 cr_hmc_expend_0                  :3;	//(18:16,RW,0x7) //
	UINT32 cr_lr_ratio_check_en_0           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_0                  :4;	//(23:20,RW,0x5) //
	UINT32 cr_center_weight_0               :8;	//(31:24,RW,0xB8) //
	};
}PE_O26_ND_IPC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290300 RW 0x506B_0130
	UINT32 cr_noise_en                      :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 cr_noise_th                      :8;	//(15:8,RW,0x1) //
	UINT32 cr_gds_resolution                :2;	//(17:16,RW,0x3) //
	UINT32 resvd1                           :2;
	UINT32 cr_hmc_h_range                   :12;	//(31:20,RW,0x506) //
	};
}PE_O26_ND_IPC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290304 RW 0x6080_1010
	UINT32 reg_vdiff_en                     :1;	//(0,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 reg_vdiff_th                     :8;	//(15:8,RW,0x10) //
	UINT32 reg_hmc_err_max                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_hmc_err_min                  :8;	//(31:24,RW,0x60) //
	};
}PE_O26_ND_IPC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290308 RW 0xE018_0818
	UINT32 cr_fmd_check_en                  :1;	//(0,RW,0x0) //FMD, chroma fmd mode enable
	UINT32 resvd0                           :7;
	UINT32 cr_fmd_ath                       :8;	//(15:8,RW,0x8) //FMD, A-Th for chroma fmd
	UINT32 resvd1                           :8;
	UINT32 cr_fmd_ratio_th                  :8;	//(31:24,RW,0xE0) //FMD, chroma fmd_ratio
	};
}PE_O26_ND_IPC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29030C RW 0xE010_C010
	UINT32 chroma_st_flt_ctrl_x0            :8;	//(7:0,RW,0x10) //
	UINT32 chroma_st_flt_ctrl_x1            :8;	//(15:8,RW,0xC0) //
	UINT32 luma_st_flt_ctrl_x0              :8;	//(23:16,RW,0x10) //
	UINT32 luma_st_flt_ctrl_x1              :8;	//(31:24,RW,0xE0) //
	};
}PE_O26_ND_IPC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290310 RW 0x0800_A40F
	UINT32 reg_hmc_bonus_es_en              :1;	//(0,RW,0x1) //
	UINT32 reg_hmc_bonus_et_en              :1;	//(1,RW,0x1) //
	UINT32 resvd                            :6;
	UINT32 reg_hmc_bonus_es                 :8;	//(15:8,RW,0xA4) //
	UINT32 reg_hmc_bonus_th                 :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_bonus_et                 :8;	//(31:24,RW,0x8) //
	};
}PE_O26_ND_IPC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290314 RW 0x4008_401D
	UINT32 hmc_alpha_th                     :8;	//(7:0,RW,0x1D) //
	UINT32 resvd                            :8;
	UINT32 hmc_flt_ctrl_x0                  :8;	//(23:16,RW,0x8) //
	UINT32 hmc_st_flt_ctrl_x1               :8;	//(31:24,RW,0x40) //
	};
}PE_O26_ND_IPC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290318 RW 0x6180_8318
	UINT32 reg_vmc_motion_th                :8;	//(7:0,RW,0x18) //VMC motion Th
	UINT32 reg_vmc_debug                    :1;	//(8,RW,0x1) //VMC ? Motion? 0?? ??
	UINT32 reg_vmc_en                       :1;	//(9,RW,0x1) //VMC Enable
	UINT32 reg_vmc_still_check              :1;	//(10,RW,0x0) //P-C non motion ? VMC motion? ??????
	UINT32 resvd0                           :1;
	UINT32 reg_vmc_mul                      :2;	//(13:12,RW,0x0) //VMC*(2^n) vs normal Motion ? n?
	UINT32 reg_vmc_out_mul                  :2;	//(15:14,RW,0x2) //??? VMC motion? (2^n)?? ??.
	UINT32 reg_vmc_protect_th               :8;	//(23:16,RW,0x80) //?? motion ? ?? ???? VMC ? ??? Protection ??
	UINT32 reg_protection_en                :1;	//(24,RW,0x1) //?? motion ? ?? ???? VMC ? ??? Protection Th
	UINT32 reg_2filed_check_en              :1;	//(25,RW,0x0) //
	UINT32 reg_vmc_tnrmotion_dis            :1;	//(26,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_vmc_mm_ratio                 :4;	//(31:28,RW,0x6) //
	};
}PE_O26_ND_IPC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29031C RW 0x0000_4503
	UINT32 reg_toosmall_en                  :1;	//(0,RW,0x1) //FMD, toosmall mode enable (upper)
	UINT32 reg_toosmall_min                 :7;	//(7:1,RW,0x1) //FMD, min value of toosmall condition (upper)
	UINT32 reg_toosmall_max                 :8;	//(15:8,RW,0x45) //FMD, max value of toosmall condition (upper)
	UINT32 reg_pndiff_disable               :1;	//(16,RW,0x0) //FMD, pndiff mode off (upper)
	UINT32 resvd                            :15;
	};
}PE_O26_ND_IPC_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290320 RW 0x0000_0890
	UINT32 tava_errt_y2                     :8;	//(7:0,RW,0x90) //
	UINT32 tava_errt_x2                     :8;	//(15:8,RW,0x8) //
	UINT32 tava_errt_y3                     :8;	//(23:16,RW,0x0) //
	UINT32 tava_errt_x3                     :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_IPC_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290324 RW 0x10B0_08FF
	UINT32 tava_errt_y0                     :8;	//(7:0,RW,0xFF) //
	UINT32 tava_errt_x0                     :8;	//(15:8,RW,0x8) //
	UINT32 tava_errt_y1                     :8;	//(23:16,RW,0xB0) //
	UINT32 tava_errt_x1                     :8;	//(31:24,RW,0x10) //
	};
}PE_O26_ND_IPC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290328 RO 0x0000_0000
	UINT32 r_pc_v_count_d                   :16;	//(15:0,RO,0x0) //FMD, vertical tearing count of pc (under)
	UINT32 r_nc_v_count_d                   :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of nc (under)
	};
}PE_O26_ND_IPC_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29032C RO 0x0000_0000
	UINT32 r_pc_nc_same_d                   :16;	//(15:0,RO,0x0) //FMD, same count between pc and nc (under)
	UINT32 r_pn_v_count_d                   :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of pn (under)
	};
}PE_O26_ND_IPC_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290330 RO 0x0000_0000
	UINT32 reserved                         :6;	//(5:0,Rsvd,0x0) //
	UINT32 r_fmd_32_min_th_flag_d           :1;	//(6,RO,0x00) //FMD, 3:2 detector min_th flag(under)
	UINT32 r_fmd_32_max_th_flag_d           :1;	//(7,RO,0x00) //FMD, 3:2 detector max_th flag(under)
	UINT32 r_fmd_still_limit_flag_d         :1;	//(8,RO,0x00) //FMD, still_limit flag(under)
	UINT32 r_fmd_still_pn_th2_flag_d        :1;	//(9,RO,0x00) //FMD, still_pn_th2 flag(under)
	UINT32 r_fmd_still_pn_th_flag_d         :1;	//(10,RO,0x00) //FMD, still_pn_th flag(under)
	UINT32 r_fmd_still_prev_ratio_flag_d    :1;	//(11,RO,0x00) //FMD, still_prev_ratio flag(under)
	UINT32 r_fmd_bigger_flag_d              :1;	//(12,RO,0x00) //FMD, bigger flag(under)
	UINT32 r_fmd_smaller_flag_d             :1;	//(13,RO,0x00) //FMD, smaller flag(under)
	UINT32 r_fmd_3_2_fmd_comb_mode_d        :2;	//(15:14,RO,0x00) //FMD, comb_flag of 3_2 mode (under)
	UINT32 r_pn_diff_count_d                :16;	//(31:16,RO,0x0) //FMD, pndiff count (under)
	};
}PE_O26_ND_IPC_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290334 RO 0x0000_0000
	UINT32 r_inv_inversed_cnt               :16;	//(15:0,RO,0x0) //
	UINT32 r_inv_original_cnt               :16;	//(31:16,RO,0x0) //
	};
}PE_O26_ND_IPC_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290338 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_IPC_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29033C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_IPC_STATUS_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290340 RW 0x00EC_1200
	UINT32 reg_show_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 reg_bbd_show                     :1;	//(3,RW,0x00) //display BBD result
	UINT32 reg_show_bar_1                   :1;	//(4,RW,0x00) //
	UINT32 reg_show_bar_2                   :1;	//(5,RW,0x00) //
	UINT32 reg_show_bar_3                   :1;	//(6,RW,0x00) //
	UINT32 reg_bar1_data_mux                :2;	//(8:7,RW,0x00) //bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//(10:9,RW,0x01) //
	UINT32 reg_bar3_data_mux                :2;	//(12:11,RW,0x02) //
	UINT32 reg_hist0_data_mux               :4;	//(16:13,RW,0x00) //bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//(20:17,RW,0x06) //
	UINT32 reg_hist2_data_mux               :4;	//(24:21,RW,0x07) //
	UINT32 reg_hist0_win_sel                :2;	//(26:25,RW,0x00) //hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//(28:27,RW,0x00) //hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//(30:29,RW,0x00) //hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 hist_rd_en                       :1;	//(31,RW,0x00) //histogram read mode enable
	};
}PE_O26_ND_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290344 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290348 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O26_ND_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29034C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290350 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290354 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290358 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29035C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O26_ND_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290360 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O26_ND_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290364 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O26_ND_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290368 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O26_ND_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29036C RW 0x0000_04C8
	UINT32 cl_lcount_enable                 :1;	//(0,RW,0x00) //1: use CL Lock count(Temporal filter)	should be OFF when 4K input
	UINT32 cl_lcnt_mode                     :2;	//(2:1,RW,0x00) //"00":VA 2 lcnt, "01":VA 4 lcnt, "10"/"11":VA 6 lcnt
	UINT32 cl_scene_change_enable           :1;	//(3,RW,0x01) //1:reset CL Lock count when Scene changed
	UINT32 cl_scene_change_mode             :1;	//(4,RW,0x00) //0:Auto(from TNR scene change flag), 1:Manual(from Host)
	UINT32 cl_scene_change_manual           :1;	//(5,RW,0x00) //1:reset CL Lock count manually
	UINT32 cl_lcnt_th                       :4;	//(9:6,RW,0x03) //Temporal filtering threshold
	UINT32 cl_plus_lcount                   :3;	//(12:10,RW,0x01) //plus count when CL final flag = '1'
	UINT32 cl_minus_lcount                  :2;	//(14:13,RW,0x00) //minus count when CL final flag = '0'
	UINT32 cl_scene_change_protect          :1;	//(15,RW,0x00) //1': remain current CL flag when reset Lock count
	UINT32 resvd                            :4;
	UINT32 cl_tearing_pt_th2                :12;	//(31:20,RW,0x00) //CL Original Tearing protection threshold(CL filtering)
	};
}PE_O26_ND_CLC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290370 RW 0x0010_2000
	UINT32 reg_bbd_en                       :1;	//(0,RW,0x00) //enable
	UINT32 reg_hys_mode                     :5;	//(5:1,RW,0x0) //frame count for temporal smoothing of BBD result
	UINT32 reg_op_mode                      :1;	//(6,RW,0x00) //BBD operation mode 0 : auto detection, 1 : manual setting
	UINT32 resvd                            :1;
	UINT32 reg_cnt_th                       :8;	//(15:8,RW,0x20) //continuous Black pixel's count threshold for recognizing Black Boundary
	UINT32 reg_diff_th                      :8;	//(23:16,RW,0x10) //threshold for Black decision
	UINT32 reg_bbd_mux                      :3;	//(26:24,RW,0x00) //data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
	UINT32 reg_apl_mux                      :3;	//(29:27,RW,0x00) //data select for APL, 0 : YCbCr, 1 : GBR, 2 : HSV, 3 : YSV, others : YCbCr
	UINT32 reg_apl_win_sel                  :2;	//(31:30,RW,0x00) //apl window selection 0 : BBD status, 1 : Win_A, 2 : Win_B, 3 : Win_C
	};
}PE_O26_ND_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290374 RW 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RW,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290378 RW 0x0437_077F
	UINT32 x1                               :12;	//(11:0,RW,0x077F) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RW,0x0437) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29037C RO 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RO,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RO,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290380 RO 0x01DF_02CF
	UINT32 x1                               :12;	//(11:0,RO,0x02CF) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RO,0x01DF) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290384 RO 0x0000_0068
	UINT32 y_g_s_apl                        :10;	//(9:0,RO,0x068) //data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//(19:10,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//(29:20,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_O26_ND_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290388 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O26_ND_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29038C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_ND_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290390 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	?	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//(12,RW,0x00) //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//(14:13,RW,0x00) //histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//(15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//(28,RW,0x00) //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	// only ND1 (30,RW,0x00) //histogram read mode enable
	UINT32 hist_read_done                   :1;	//(31,RW,0x00) //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_O26_ND_TPD_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290394 RO 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RO,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O26_ND_TPD_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290398 RW 0x8080_2000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 y_offset                         :10;	//(13:4,RW,0x0200) //
	UINT32 resvd1                           :2;
	UINT32 center_position                  :8;	//(23:16,RW,0x80) //center position for Y gain control
	UINT32 y_gain                           :8;	//(31:24,RW,0x80) //
	};
}PE_O26_ND_LVCRTL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29039C RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,histogram pixel count sum,) //
	UINT32 resvd                            :10;
	};
}PE_O26_ND_TPD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903A0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903A4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903A8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903AC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_ND_TNR_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903B0 RW 0x0000_0000
	UINT32 reg_f0_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f0_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f1_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f0_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903B4 RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_master               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903B8 RW 0x0000_0000
	UINT32 reg_f1_h1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_w2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_offset               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903BC RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_sel_output                   :1;	//(24,RW,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_ND_TNR_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903C0 RW 0x0000_0000
	UINT32 reg_gmv_rst                      :1;	//(0,RW,0x00) //
	UINT32 reg_bmv_rst                      :1;	//(1,RW,0x00) //
	UINT32 reg_me_rst                       :1;	//(2,RW,0x00) //
	UINT32 reg_mc_rst                       :1;	//(3,RW,0x00) //
	UINT32 reg_ma_rst                       :1;	//(4,RW,0x00) //
	UINT32 resvd                            :27;
	};
}PE_O26_ND_TNR_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903C4 RW 0x0000_0000
	UINT32 reg_f1_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f1_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f1_w2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f3_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f2_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903C8 RW 0x0000_0000
	UINT32 reg_f2_h2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_ND_TNR_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903CC RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_ND_TNR_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903D0 RW 0x0000_0000
	UINT32 resvd0                           :2;
	UINT32 reg_a_normalize_en               :1;	//(2,RW,0x00) //
	UINT32 reg_t_normalize_en               :1;	//(3,RW,0x00) //
	UINT32 reg_t_cut_resolution             :2;	//(5:4,RW,0x00) //
	UINT32 reg_ne_normalize_en              :1;	//(6,RW,0x00) //
	UINT32 resvd1                           :9;
	UINT32 reg_cross_th_ne                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_cross_th                     :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903D4 RW 0x0000_0000
	UINT32 reg_mul_base_t                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_mul_base_e                   :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O26_ND_TNR_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903D8 RW 0x0000_0000
	UINT32 reg_a_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903DC RW 0x0000_0000
	UINT32 reg_a_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903E0 RW 0x0000_0000
	UINT32 reg_t_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903E4 RW 0x0000_0000
	UINT32 reg_t_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903E8 RW 0x0000_0000
	UINT32 reg_edge_minmax_y0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_edge_minmax_x0               :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_minmax_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_minmax_x1               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903EC RW 0x0000_0000
	UINT32 reg_detail_minmax_y0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_minmax_x0             :8;	//(15:8,RW,0x0) //
	UINT32 reg_detail_minmax_y1             :8;	//(23:16,RW,0x0) //
	UINT32 reg_detail_minmax_x1             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903F0 RW 0x0000_0000
	UINT32 reg_sel_ne_type                  :2;	//(1:0,RW,0x00) //0:(Y - TNR_Y), 1:(Y - SNR_Y), 2:(C - SNR_C)
	UINT32 reg_sel_re_type                  :1;	//(2,RW,0x00) //0:(still region), 1:(flat region)
	UINT32 resvd0                           :1;
	UINT32 reg_sel_at_mode                  :2;	//(5:4,RW,0x00) //0:(A), 1:(T), 2:(max(A,T)), 3:(A,T separate)
	UINT32 resvd1                           :2;
	UINT32 reg_hist_xscale                  :3;	//(10:8,RW,0x00) //histogram x-axi resolution ( 0: 0,1,2? , 1: 0,2,4?)
	UINT32 resvd2                           :1;
	UINT32 reg_hist_yscale                  :2;	//(13:12,RW,0x00) //histogram cut resolution
	UINT32 resvd3                           :2;
	UINT32 reg_th_atmap                     :8;	//(23:16,RW,0x0) //at_map threshold ( flat rgion valid threshold )
	UINT32 reg_th_motion                    :8;	//(31:24,RW,0x0) //motion threshiold ( still region valid threshold )
	};
}PE_O26_ND_TNR_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903F4 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f2_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903F8 RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f3_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_ND_TNR_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2903FC RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f3_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_ND_TNR_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290400 RO 0x0000_0000
	UINT32 valid_cnt                        :16;	//(15:0,RO,0x0) //# of valid region
	UINT32 resvd                            :16;
	};
}PE_O26_ND_TNR_NE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290404 RO 0x0000_0000
	UINT32 hist_1                           :16;	//(15:0,RO,0x0) //hist[1]
	UINT32 hist_0                           :16;	//(31:16,RO,0x0) //hist[0]
	};
}PE_O26_ND_TNR_NE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290408 RO 0x0000_0000
	UINT32 hist_3                           :16;	//(15:0,RO,0x0) //hist[3]
	UINT32 hist_2                           :16;	//(31:16,RO,0x0) //hist[2]
	};
}PE_O26_ND_TNR_NE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29040C RO 0x0000_0000
	UINT32 hist_5                           :16;	//(15:0,RO,0x0) //hist[5]
	UINT32 hist_4                           :16;	//(31:16,RO,0x0) //hist[4]
	};
}PE_O26_ND_TNR_NE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290410 RO 0x0000_0000
	UINT32 hist_7                           :16;	//(15:0,RO,0x0) //hist[7]
	UINT32 hist_6                           :16;	//(31:16,RO,0x0) //hist[6]
	};
}PE_O26_ND_TNR_NE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290414 RO 0x0000_0000
	UINT32 hist_9                           :16;	//(15:0,RO,0x0) //hist[9]
	UINT32 hist_8                           :16;	//(31:16,RO,0x0) //hist[8]
	};
}PE_O26_ND_TNR_NE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290418 RO 0x0000_0000
	UINT32 hist_11                          :16;	//(15:0,RO,0x0) //hist[11]
	UINT32 hist_10                          :16;	//(31:16,RO,0x0) //hist[10]
	};
}PE_O26_ND_TNR_NE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29041C RO 0x0000_0000
	UINT32 hist_13                          :16;	//(15:0,RO,0x0) //hist[13]
	UINT32 hist_12                          :16;	//(31:16,RO,0x0) //hist[12]
	};
}PE_O26_ND_TNR_NE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290420 RO 0x0000_0000
	UINT32 hist_15                          :16;	//(15:0,RO,0x0) //hist[15]
	UINT32 hist_14                          :16;	//(31:16,RO,0x0) //hist[14]
	};
}PE_O26_ND_TNR_NE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290424 RW 0x0000_0000
	UINT32 reg_smg_gain_lut_x3              :8;	//(7:0,NA,0x00) //
	UINT32 reg_smg_gain_lut_x2              :8;	//(15:8,NA,0x00) //
	UINT32 reg_smg_gain_lut_x1              :8;	//(23:16,NA,0x00) //
	UINT32 reg_smg_gain_lut_x0              :8;	//(31:24,NA,0x00) //
	};
}PE_O26_ND_TNR_SMG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290428 RW 0x0000_0000
	UINT32 reg_smg_gain_lut_y3              :8;	//(7:0,NA,0x00) //
	UINT32 reg_smg_gain_lut_y2              :8;	//(15:8,NA,0x00) //
	UINT32 reg_smg_gain_lut_y1              :8;	//(23:16,NA,0x00) //
	UINT32 reg_smg_gain_lut_y0              :8;	//(31:24,NA,0x00) //
	};
}PE_O26_ND_TNR_SMG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29042C RW 0x0000_0000
	UINT32 reg_smg_iir_lut_x3               :8;	//(7:0,NA,0x00) //
	UINT32 reg_smg_iir_lut_x2               :8;	//(15:8,NA,0x00) //
	UINT32 reg_smg_iir_lut_x1               :8;	//(23:16,NA,0x00) //
	UINT32 reg_smg_iir_lut_x0               :8;	//(31:24,NA,0x00) //
	};
}PE_O26_ND_TNR_SMG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290430 RW 0x0000_0000
	UINT32 reg_smg_iir_lut_y3               :8;	//(7:0,NA,0x00) //
	UINT32 reg_smg_iir_lut_y2               :8;	//(15:8,NA,0x00) //
	UINT32 reg_smg_iir_lut_y1               :8;	//(23:16,NA,0x00) //
	UINT32 reg_smg_iir_lut_y0               :8;	//(31:24,NA,0x00) //
	};
}PE_O26_ND_TNR_SMG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290440 RW 0x00EC_1200
	UINT32 reg_show_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 reg_bbd_show                     :1;	//(3,RW,0x00) //display BBD result
	UINT32 reg_show_bar_1                   :1;	//(4,RW,0x00) //
	UINT32 reg_show_bar_2                   :1;	//(5,RW,0x00) //
	UINT32 reg_show_bar_3                   :1;	//(6,RW,0x00) //
	UINT32 reg_bar1_data_mux                :2;	//(8:7,RW,0x00) //bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//(10:9,RW,0x01) //
	UINT32 reg_bar3_data_mux                :2;	//(12:11,RW,0x02) //
	UINT32 reg_hist0_data_mux               :4;	//(16:13,RW,0x00) //bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//(20:17,RW,0x06) //
	UINT32 reg_hist2_data_mux               :4;	//(24:21,RW,0x07) //
	UINT32 reg_hist0_win_sel                :2;	//(26:25,RW,0x00) //hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//(28:27,RW,0x00) //hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//(30:29,RW,0x00) //hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 hist_rd_en                       :1;	//(31,RW,0x00) //histogram read mode enable
	};
}PE_O26_ND_HIST2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290444 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_HIST2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290448 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O26_ND_HIST2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29044C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_HIST2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290450 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_HIST2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290454 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_ND_HIST2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290458 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_HIST2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29045C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O26_ND_HIST2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290460 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O26_ND_HIST2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290464 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O26_ND_HIST2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290468 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O26_ND_HIST2_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29046C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_ND_HIST2_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290470 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	?	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//(12,RW,0x00) //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//(14:13,RW,0x00) //histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//(15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//(28,RW,0x00) //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	//(30,RW,0x00) //histogram read mode enable
	UINT32 hist_read_done                   :1;	//(31,RW,0x00) //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_O26_ND_HIST2_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290474 RO 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RO,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O26_ND_HIST2_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290478 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O26_ND_HIST2_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC60480 RW 0x0000_0000
	UINT32 chroma_st_flt_ctrl_x0	:8;	//7:0
	UINT32 chroma_st_flt_ctrl_x1	:8;	//15:8
	UINT32 luma_st_flt_ctrl_x0		:8;	//23:16
	UINT32 luma_st_flt_ctrl_x1		:8;	//31:24
	};
}PE_O26_ND_ND_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC60484 RW 0x0000_0000
	UINT32 motion_x_tearing_gain	:8;	//7:0
	UINT32 motion_gain				:8;	//15:8
	};
}PE_O26_ND_ND_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC60488 RW 0x0000_0000
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
}PE_O26_ND_ND_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC6048C RW 0x0000_0000
	UINT32 resvd                            :1;
	UINT32 reg_nlvl_input_sel				:1; //(1:1,RW,0x00) //
	UINT32 reg_sc_detect_hres				:1; //(2:2,RW,0x00) //
	UINT32 reg_clc_nt_pal					:1; //(3:3,RW,0x00) //
	UINT32 reg_clc_mem_wr_mode				:2; //(5:4,RW,0x00) //
	UINT32 reg_sad_8x3_res					:2; //(7:6,RW,0x00) //
	UINT32 reg_sad_8x3_iir_en				:1; //(8:8,RW,0x00) //
	UINT32 reg_sad_8x3_chroma_en			:1; //(9:9,RW,0x00) //
	UINT32 reg_minfo_sw 					:2; //(11:10,RW,0x00) //
	UINT32 reg_minfo_mode10 				:2; //(13:12,RW,0x00) //[0] minfo debug enable : ipc_m, ipc_st, tnr_m, tnr_mv, clc
	UINT32 reg_minfo_flt					:2; //(15:14,RW,0x00) //
	UINT32 reg_hfr_mask_en					:1; //only ND0 (16,RW,0x0) //
	UINT32 reg_decon_blend_en				:1; //(17,RW,0x0) //chg
	UINT32 reg_minfo_mode32 				:2; //(19:18,RW,0x00) //
	UINT32 reg_minfo_mode74 				:4; //(23:20,RW,0x00) //
	UINT32 reg_sad_8x3_iir_alpha			:8; //(31:24,RW,0x0) //for TNR, DNR
	};
}PE_O26_ND_ND_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290490 RW 0x0000_0000
	UINT32 win_y0                           :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 win_x0                           :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 win_mode                         :1;	//(30,RW,0x00) //0 := inside enabled	1 = outside enable
	UINT32 win_en                           :1;	//(31,RW,0x00) //
	};
}PE_O26_ND_TNR_ETC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290494 RW 0x0000_0000
	UINT32 win_y1                           :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 win_x1                           :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 win_tnrw_en                      :1;	//(31,RW,0x00) //this flag is valid only if "win_en = 1"
	};
}PE_O26_ND_TNR_ETC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290498 RW 0x0000_0000
	UINT32 minfo_tnr_rd_m_delay             :4;	//(3:0,RW,0x00) //0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd0                           :4;
	UINT32 minfo_tnr_rd_mv_delay            :4;	//(11:8,RW,0x00) //0 := no delay	1~7 = delay  ~ delay 7
	UINT32 resvd1                           :4;
	UINT32 minfo_tnr_wr_m_delay             :4;	//(19:16,RW,0x00) //0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	UINT32 minfo_lstart_delay               :4;	//(23:20,RW,0x00) //0 := delay (-4)	1 = delay (-3)	2 = delay (-2)	3 = delay (-1)	4 = delay ( 0)	5 = delay (+1)	6 = delay (+2)	7 = delay (+3)
	UINT32 minfo_clc_offset                 :2;	//(25:24,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 minfo_tnr_wr_mv_delay            :4;	//(31:28,RW,0x00) //0 := delay (-6)	1 = delay (-5)	2 = delay (-4)	3 = delay (-3)	4 = delay (-2)	5 = delay (-1)	6 = delay ( 0)	7 = delay (+1)	8 = delay (+2)	9 = delay (+3)	10 = delay (+4)	11 = delay (+5)	12 = delay (+6)
	};
}PE_O26_ND_TNR_ETC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29049C RW 0x0000_0000
	UINT32 reg_clc_minfo_dly                :3;	//(2:0,RW,0x0) //1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd0                           :1;
	UINT32 reg_clc_flt_dly                  :3;	//(6:4,RW,0x0) //1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd1                           :25;
	};
}PE_O26_ND_TNR_ETC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904A0 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904A4 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904A8 RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904AC RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904B0 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904B4 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904B8 RW 0x0000_0000
	UINT32 mif_prefetch_ctrl                :8;	//(7:0,RW,0x0) //reg_en_pf_t1_m   = reg_mif_prefetch_ctrl[7];	reg_en_pf_t4_y   = reg_mif_prefetch_ctrl[6];	reg_en_pf_t3_c   = reg_mif_prefetch_ctrl[5];	reg_en_pf_t3_y   = reg_mif_prefetch_ctrl[4];	reg_en_pf_t2_c   = reg_mif_prefetch_ctrl[3];	reg_en_pf_t2_y   = reg_mif_prefetch_ctrl[2];	reg_en_pf_t1_c   = reg_mif_prefetch_ctrl[1];	reg_en_pf_t1_y   = reg_mif_prefetch_ctrl[0];
	UINT32 mif_vreverse_en                  :11;	//(18:8,RW,0x0) //reg_en_vreverse_tnrw_m  = reg_mif_vreverse_en[10];	reg_en_vreverse_tnrw_c  = reg_mif_vreverse_en[9];	reg_en_vreverse_tnrw_y  = reg_mif_vreverse_en[8];	reg_en_vreverse_t1_m  = reg_mif_vreverse_en[7];	reg_en_vreverse_t4_y  = reg_mif_vreverse_en[6];	reg_en_vreverse_t3_c  = reg_mif_vreverse_en[5];	reg_en_vreverse_t3_y  = reg_mif_vreverse_en[4];	reg_en_vreverse_t2_c  = reg_mif_vreverse_en[3];	reg_en_vreverse_t2_y  = reg_mif_vreverse_en[2];	reg_en_vreverse_t1_c  = reg_mif_vreverse_en[1];	reg_en_vreverse_t1_y  = reg_mif_vreverse_en[0];
	UINT32 resvd0                           :1;
	UINT32 global_cg_blk_off                :4;	//(23:20,RW,0x00) //[Debug] Global Clock Gating Sub Block Off	[0] : Global Clock Gating IPC Off	[1] : Global Clock Gating CLC Off	[2] : NA	[3] : NA
	UINT32 power_cg_blk_off                 :4;	//(27:24,RW,0x00) //[Debug] Power Clock Gating Sub Block Off	[0] : FIM Power Clock Gating Off	[1] : NA	[2] : NA	[3] : NA
	UINT32 resvd1                           :4;
	};
}PE_O26_ND_PE0_DEBUG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904C0 RW 0x0000_0000
	UINT32 reg_dcof_off                     :1;	//(0,NA,0x00) //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//(1,NA,0x00) //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//(2,NA,0x00) //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//(3,NA,0x00) //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//(8,NA,0x00) //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//(15:10,NA,0x00) //reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_O26_ND_FBC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904C4 RW 0x0000_0000
	UINT32 reg_dcof_off                     :1;	//(0,NA,0x00) //reg_dcof_off = (fbc20)? 1: reg_fbc_ctrl1_y[0];
	UINT32 reg_abab_pr_off                  :1;	//(1,NA,0x00) //reg_abab_pr_off = (fbc20)? 1: reg_fbc_ctrl1_y[1];
	UINT32 reg_abab_ls_off                  :1;	//(2,NA,0x00) //reg_abab_ls_off = (fbc20)? 1: reg_fbc_ctrl1_y[2];
	UINT32 reg_aabb_off                     :1;	//(3,NA,0x00) //reg_aabb_off = (fbc20)? 1: reg_fbc_ctrl1_y[3];
	UINT32 resvd0                           :4;
	UINT32 reg_abba_off                     :1;	//(8,NA,0x00) //reg_abba_off = (fbc20)? 1: reg_fbc_ctrl1_y[8];
	UINT32 resvd1                           :1;
	UINT32 reg_abab_th                      :6;	//(15:10,NA,0x00) //reg_abab_th = (fbc20)? 0: reg_fbc_ctrl1_y[15:10];
	UINT32 resvd2                           :16;
	};
}PE_O26_ND_FBC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904D0 RW 0xFF00_FF00
	UINT32 reg_gfd_h_th0_a                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_h_th1_a                  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_gfd_h_th0_b                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_gfd_h_th1_b                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_ND_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904D4 RW 0x0000_0000
	UINT32 reg_gfd_s_th                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_v_th                     :8;	//(15:8,RW,0x00) //
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//(31:30,RW,0x0) //0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_O26_ND_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904D8 RO 0x0000_0000
	UINT32 reg_gfd_count_a01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Top
	};
}PE_O26_ND_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904DC RO 0x0000_0000
	UINT32 reg_gfd_count_a11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_O26_ND_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904E0 RO 0x0000_0000
	UINT32 reg_gfd_count_b01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Top
	};
}PE_O26_ND_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904E4 RO 0x0000_0000
	UINT32 reg_gfd_count_b11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_O26_ND_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904E8 RW 0x0000_0000
	UINT32 reg_face_gain_y_en               :1;	//(0,RW,0x0) //
	UINT32 reg_face_gain_c_en               :1;	//(1,RW,0x0) //
	UINT32 resvd                            :30;
	};
}PE_O26_ND_TNR_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904EC RW 0x0000_0000
	UINT32 reg_face_gain_pts_y2             :8;	//(7:0,RW,0x0) //
	UINT32 reg_face_gain_pts_x2             :8;	//(15:8,RW,0x0) //
	UINT32 reg_face_gain_pts_y3             :8;	//(23:16,RW,0x0) //
	UINT32 reg_face_gain_pts_x3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2904F0 RW 0x0000_0000
	UINT32 reg_face_gain_pts_y0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_face_gain_pts_x0             :8;	//(15:8,RW,0x0) //
	UINT32 reg_face_gain_pts_y1             :8;	//(23:16,RW,0x0) //
	UINT32 reg_face_gain_pts_x1             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND_TNR_CTRL_68_T;

typedef struct {
	PE_O26_ND_PE0_LOAD_T                                         pe0_load;	//0xCC290100
	PE_O26_ND_PE0_INTR_T                                         pe0_intr;	//0xCC290104
	PE_O26_ND_PE0_STATUS0_T                                   pe0_status0;	//0xCC290108
	PE_O26_ND_PE0_STATUS1_T                                   pe0_status1;	//0xCC29010C
	PE_O26_ND_PE0_OPMODE_T                                     pe0_opmode;	//0xCC290110
	PE_O26_ND_PE0_SRC_SIZE_T                                 pe0_src_size;	//0xCC290114
	PE_O26_ND_PE0_FIELD_T                                       pe0_field;	//0xCC290118
	PE_O26_ND_PE0_DEBUG_LEND_CTRL_T                   pe0_debug_lend_ctrl;	//0xCC29011C
	PE_O26_ND_PE0_IN_OFFSET_T                               pe0_in_offset;	//0xCC290120
	PE_O26_ND_PE0_IN_SIZE_T                                   pe0_in_size;	//0xCC290124
	PE_O26_ND_FBC_CTRL0_T                                       fbc_ctrl0;	//0xCC290128
	PE_O26_ND_FBC_CTRL1_T                                       fbc_ctrl1;	//0xCC29012C
	PE_O26_ND_PE0_MEM_REQ_T                                   pe0_mem_req;	//0xCC290130
	PE_O26_ND_PE0_DEBUG_LREQ_DLY_T                     pe0_debug_lreq_dly;	//0xCC290134
	PE_O26_ND_TNRW_IN_OFFSET_T                             tnrw_in_offset;	//0xCC290138
	PE_O26_ND_TNRW_OUT_SIZE_T                               tnrw_out_size;	//0xCC29013C
	PE_O26_ND_TNR_CTRL_00_T                                   tnr_ctrl_00;	//0xCC290140
	PE_O26_ND_TNR_CTRL_01_T                                   tnr_ctrl_01;	//0xCC290144
	PE_O26_ND_TNR_CTRL_02_T                                   tnr_ctrl_02;	//0xCC290148
	PE_O26_ND_TNR_CTRL_03_T                                   tnr_ctrl_03;	//0xCC29014C
	PE_O26_ND_TNR_CTRL_04_T                                   tnr_ctrl_04;	//0xCC290150
	PE_O26_ND_TNR_CTRL_05_T                                   tnr_ctrl_05;	//0xCC290154
	PE_O26_ND_TNR_CTRL_06_T                                   tnr_ctrl_06;	//0xCC290158
	PE_O26_ND_TNR_CTRL_07_T                                   tnr_ctrl_07;	//0xCC29015C
	PE_O26_ND_TNR_CTRL_08_T                                   tnr_ctrl_08;	//0xCC290160
	PE_O26_ND_TNR_CTRL_09_T                                   tnr_ctrl_09;	//0xCC290164
	PE_O26_ND_TNR_CTRL_10_T                                   tnr_ctrl_10;	//0xCC290168
	PE_O26_ND_TNR_CTRL_11_T                                   tnr_ctrl_11;	//0xCC29016C
	PE_O26_ND_TNR_CTRL_12_T                                   tnr_ctrl_12;	//0xCC290170
	PE_O26_ND_TNR_CTRL_13_T                                   tnr_ctrl_13;	//0xCC290174
	PE_O26_ND_TNR_CTRL_14_T                                   tnr_ctrl_14;	//0xCC290178
	PE_O26_ND_TNR_CTRL_15_T                                   tnr_ctrl_15;	//0xCC29017C
	PE_O26_ND_TNR_CTRL_16_T                                   tnr_ctrl_16;	//0xCC290180
	PE_O26_ND_TNR_CTRL_17_T                                   tnr_ctrl_17;	//0xCC290184
	PE_O26_ND_TNR_CTRL_18_T                                   tnr_ctrl_18;	//0xCC290188
	PE_O26_ND_TNR_CTRL_19_T                                   tnr_ctrl_19;	//0xCC29018C
	PE_O26_ND_TNR_CTRL_20_T                                   tnr_ctrl_20;	//0xCC290190
	PE_O26_ND_TNR_CTRL_21_T                                   tnr_ctrl_21;	//0xCC290194
	PE_O26_ND_TNR_CTRL_22_T                                   tnr_ctrl_22;	//0xCC290198
	PE_O26_ND_TNR_CTRL_23_T                                   tnr_ctrl_23;	//0xCC29019C
	PE_O26_ND_TNR_CTRL_24_T                                   tnr_ctrl_24;	//0xCC2901A0
	PE_O26_ND_TNR_CTRL_25_T                                   tnr_ctrl_25;	//0xCC2901A4
	PE_O26_ND_TNR_CTRL_26_T                                   tnr_ctrl_26;	//0xCC2901A8
	PE_O26_ND_TNR_CTRL_27_T                                   tnr_ctrl_27;	//0xCC2901AC
	PE_O26_ND_TNR_CTRL_28_T                                   tnr_ctrl_28;	//0xCC2901B0
	PE_O26_ND_TNR_CTRL_29_T                                   tnr_ctrl_29;	//0xCC2901B4
	PE_O26_ND_TNR_CTRL_30_T                                   tnr_ctrl_30;	//0xCC2901B8
	PE_O26_ND_TNR_CTRL_31_T                                   tnr_ctrl_31;	//0xCC2901BC
	PE_O26_ND_TNR_STATUS_00_T                               tnr_status_00;	//0xCC2901C0
	PE_O26_ND_TNR_STATUS_01_T                               tnr_status_01;	//0xCC2901C4
	PE_O26_ND_TNR_STATUS_02_T                               tnr_status_02;	//0xCC2901C8
	PE_O26_ND_TNR_STATUS_03_T                               tnr_status_03;	//0xCC2901CC
	PE_O26_ND_TNR_MAIN_LUT_00_T                           tnr_main_lut_00;	//0xCC2901D0
	PE_O26_ND_TNR_MAIN_LUT_01_T                           tnr_main_lut_01;	//0xCC2901D4
	UINT32                                                      reserved0;	//0xCC2901D8
	PE_O26_ND_TNR_STATUS_04_T                               tnr_status_04;	//0xCC2901DC
	PE_O26_ND_TNR_CTRL_32_T                                   tnr_ctrl_32;	//0xCC2901E0
	PE_O26_ND_TNR_CTRL_33_T                                   tnr_ctrl_33;	//0xCC2901E4
	PE_O26_ND_TNR_CTRL_34_T                                   tnr_ctrl_34;	//0xCC2901E8
	PE_O26_ND_TNR_CTRL_35_T                                   tnr_ctrl_35;	//0xCC2901EC
	PE_O26_ND_TNR_CTRL_36_T                                   tnr_ctrl_36;	//0xCC2901F0
	PE_O26_ND_TNR_CTRL_37_T                                   tnr_ctrl_37;	//0xCC2901F4
	PE_O26_ND_TNR_CTRL_38_T                                   tnr_ctrl_38;	//0xCC2901F8
	PE_O26_ND_TNR_CTRL_39_T                                   tnr_ctrl_39;	//0xCC2901FC
	PE_O26_ND_IPC_CTRL_00_T                                   ipc_ctrl_00;	//0xCC290200
	PE_O26_ND_IPC_CTRL_01_T                                   ipc_ctrl_01;	//0xCC290204
	PE_O26_ND_IPC_CTRL_02_T                                   ipc_ctrl_02;	//0xCC290208
	PE_O26_ND_IPC_CTRL_03_T                                   ipc_ctrl_03;	//0xCC29020C
	PE_O26_ND_IPC_CTRL_04_T                                   ipc_ctrl_04;	//0xCC290210
	PE_O26_ND_IPC_CTRL_05_T                                   ipc_ctrl_05;	//0xCC290214
	PE_O26_ND_IPC_CTRL_06_T                                   ipc_ctrl_06;	//0xCC290218
	PE_O26_ND_IPC_CTRL_07_T                                   ipc_ctrl_07;	//0xCC29021C
	PE_O26_ND_IPC_CTRL_08_T                                   ipc_ctrl_08;	//0xCC290220
	PE_O26_ND_IPC_CTRL_09_T                                   ipc_ctrl_09;	//0xCC290224
	PE_O26_ND_IPC_CTRL_10_T                                   ipc_ctrl_10;	//0xCC290228
	PE_O26_ND_IPC_CTRL_11_T                                   ipc_ctrl_11;	//0xCC29022C
	PE_O26_ND_IPC_CTRL_12_T                                   ipc_ctrl_12;	//0xCC290230
	PE_O26_ND_IPC_CTRL_13_T                                   ipc_ctrl_13;	//0xCC290234
	PE_O26_ND_IPC_CTRL_14_T                                   ipc_ctrl_14;	//0xCC290238
	PE_O26_ND_IPC_CTRL_15_T                                   ipc_ctrl_15;	//0xCC29023C
	PE_O26_ND_IPC_CTRL_16_T                                   ipc_ctrl_16;	//0xCC290240
	PE_O26_ND_IPC_CTRL_17_T                                   ipc_ctrl_17;	//0xCC290244
	PE_O26_ND_IPC_CTRL_18_T                                   ipc_ctrl_18;	//0xCC290248
	PE_O26_ND_IPC_CTRL_19_T                                   ipc_ctrl_19;	//0xCC29024C
	PE_O26_ND_IPC_STATUS_00_T                               ipc_status_00;	//0xCC290250
	PE_O26_ND_IPC_STATUS_01_T                               ipc_status_01;	//0xCC290254
	PE_O26_ND_IPC_STATUS_02_T                               ipc_status_02;	//0xCC290258
	PE_O26_ND_IPC_STATUS_03_T                               ipc_status_03;	//0xCC29025C
	PE_O26_ND_CLC_CTRL_00_T                                   clc_ctrl_00;	//0xCC290260
	PE_O26_ND_CLC_CTRL_01_T                                   clc_ctrl_01;	//0xCC290264
	PE_O26_ND_CLC_CTRL_02_T                                   clc_ctrl_02;	//0xCC290268
	PE_O26_ND_CLC_CTRL_03_T                                   clc_ctrl_03;	//0xCC29026C
	PE_O26_ND_CLC_CTRL_04_T                                   clc_ctrl_04;	//0xCC290270
	PE_O26_ND_CLC_CTRL_05_T                                   clc_ctrl_05;	//0xCC290274
	PE_O26_ND_CLC_CTRL_06_T                                   clc_ctrl_06;	//0xCC290278
	PE_O26_ND_CLC_STAT_00_T                                   clc_stat_00;	//0xCC29027C
	PE_O26_ND_IPC_CTRL_34_T                                   ipc_ctrl_34;	//0xCC290280
	PE_O26_ND_IPC_CTRL_35_T                                   ipc_ctrl_35;	//0xCC290284
	PE_O26_ND_IPC_CTRL_36_T                                   ipc_ctrl_36;	//0xCC290288
	PE_O26_ND_IPC_CTRL_37_T                                   ipc_ctrl_37;	//0xCC29028C
	PE_O26_ND_IPC_CTRL_38_T                                   ipc_ctrl_38;	//0xCC290290
	PE_O26_ND_IPC_CTRL_39_T                                   ipc_ctrl_39;	//0xCC290294
	PE_O26_ND_IPC_CTRL_40_T                                   ipc_ctrl_40;	//0xCC290298
	PE_O26_ND_IPC_CTRL_41_T                                   ipc_ctrl_41;	//0xCC29029C
	PE_O26_ND_IPC_CTRL_42_T                                   ipc_ctrl_42;	//0xCC2902A0
	PE_O26_ND_IPC_CTRL_43_T                                   ipc_ctrl_43;	//0xCC2902A4
	PE_O26_ND_IPC_CTRL_44_T                                   ipc_ctrl_44;	//0xCC2902A8
	PE_O26_ND_IPC_CTRL_45_T                                   ipc_ctrl_45;	//0xCC2902AC
	PE_O26_ND_IPC_CTRL_46_T                                   ipc_ctrl_46;	//0xCC2902B0
	PE_O26_ND_IPC_CTRL_47_T                                   ipc_ctrl_47;	//0xCC2902B4
	PE_O26_ND_IPC_CTRL_48_T                                   ipc_ctrl_48;	//0xCC2902B8
	PE_O26_ND_IPC_CTRL_49_T                                   ipc_ctrl_49;	//0xCC2902BC
	PE_O26_ND_IPC_CTRL_50_T                                   ipc_ctrl_50;	//0xCC2902C0
	PE_O26_ND_IPC_CTRL_51_T                                   ipc_ctrl_51;	//0xCC2902C4
	PE_O26_ND_IPC_CTRL_52_T                                   ipc_ctrl_52;	//0xCC2902C8
	PE_O26_ND_IPC_CTRL_53_T                                   ipc_ctrl_53;	//0xCC2902CC
	PE_O26_ND_IPC_CTRL_54_T                                   ipc_ctrl_54;	//0xCC2902D0
	PE_O26_ND_IPC_CTRL_55_T                                   ipc_ctrl_55;	//0xCC2902D4
	UINT32                                                      reserved1;	//0xCC2902D8
	UINT32                                                      reserved2;	//0xCC2902DC
	PE_O26_ND_MMD_CTRL_T                                         mmd_ctrl;	//0xCC2902E0
	UINT32                                                      reserved3;	//0xCC2902E4
	UINT32                                                      reserved4;	//0xCC2902E8
	UINT32                                                      reserved5;	//0xCC2902EC
	PE_O26_ND_IPC_CTRL_20_T                                   ipc_ctrl_20;	//0xCC2902F0
	PE_O26_ND_IPC_CTRL_21_T                                   ipc_ctrl_21;	//0xCC2902F4
	PE_O26_ND_IPC_CTRL_22_T                                   ipc_ctrl_22;	//0xCC2902F8
	PE_O26_ND_IPC_CTRL_23_T                                   ipc_ctrl_23;	//0xCC2902FC
	PE_O26_ND_IPC_CTRL_24_T                                   ipc_ctrl_24;	//0xCC290300
	PE_O26_ND_IPC_CTRL_25_T                                   ipc_ctrl_25;	//0xCC290304
	PE_O26_ND_IPC_CTRL_26_T                                   ipc_ctrl_26;	//0xCC290308
	PE_O26_ND_IPC_CTRL_27_T                                   ipc_ctrl_27;	//0xCC29030C
	PE_O26_ND_IPC_CTRL_28_T                                   ipc_ctrl_28;	//0xCC290310
	PE_O26_ND_IPC_CTRL_29_T                                   ipc_ctrl_29;	//0xCC290314
	PE_O26_ND_IPC_CTRL_30_T                                   ipc_ctrl_30;	//0xCC290318
	PE_O26_ND_IPC_CTRL_31_T                                   ipc_ctrl_31;	//0xCC29031C
	PE_O26_ND_IPC_CTRL_32_T                                   ipc_ctrl_32;	//0xCC290320
	PE_O26_ND_IPC_CTRL_33_T                                   ipc_ctrl_33;	//0xCC290324
	PE_O26_ND_IPC_STATUS_04_T                               ipc_status_04;	//0xCC290328
	PE_O26_ND_IPC_STATUS_05_T                               ipc_status_05;	//0xCC29032C
	PE_O26_ND_IPC_STATUS_06_T                               ipc_status_06;	//0xCC290330
	PE_O26_ND_IPC_STATUS_07_T                               ipc_status_07;	//0xCC290334
	PE_O26_ND_IPC_STATUS_08_T                               ipc_status_08;	//0xCC290338
	PE_O26_ND_IPC_STATUS_09_T                               ipc_status_09;	//0xCC29033C
	PE_O26_ND_TPD_CTRL_00_T                                   tpd_ctrl_00;	//0xCC290340
	PE_O26_ND_TPD_CTRL_01_T                                   tpd_ctrl_01;	//0xCC290344
	PE_O26_ND_TPD_CTRL_02_T                                   tpd_ctrl_02;	//0xCC290348
	PE_O26_ND_TPD_CTRL_03_T                                   tpd_ctrl_03;	//0xCC29034C
	PE_O26_ND_TPD_CTRL_04_T                                   tpd_ctrl_04;	//0xCC290350
	PE_O26_ND_TPD_CTRL_05_T                                   tpd_ctrl_05;	//0xCC290354
	PE_O26_ND_TPD_CTRL_06_T                                   tpd_ctrl_06;	//0xCC290358
	PE_O26_ND_TPD_CTRL_07_T                                   tpd_ctrl_07;	//0xCC29035C
	PE_O26_ND_TPD_CTRL_08_T                                   tpd_ctrl_08;	//0xCC290360
	PE_O26_ND_TPD_CTRL_09_T                                   tpd_ctrl_09;	//0xCC290364
	PE_O26_ND_TPD_STAT_00_T                                   tpd_stat_00;	//0xCC290368
	PE_O26_ND_CLC_CTRL_07_T                                   clc_ctrl_07;	//0xCC29036C
	PE_O26_ND_BBD_CTRL_00_T                                   bbd_ctrl_00;	//0xCC290370
	PE_O26_ND_BBD_CTRL_01_T                                   bbd_ctrl_01;	//0xCC290374
	PE_O26_ND_BBD_CTRL_02_T                                   bbd_ctrl_02;	//0xCC290378
	PE_O26_ND_BBD_STAT_00_T                                   bbd_stat_00;	//0xCC29037C
	PE_O26_ND_BBD_STAT_01_T                                   bbd_stat_01;	//0xCC290380
	PE_O26_ND_APL_STAT_00_T                                   apl_stat_00;	//0xCC290384
	PE_O26_ND_TPD_CTRL_0A_T                                   tpd_ctrl_0a;	//0xCC290388
	PE_O26_ND_TPD_CTRL_0B_T                                   tpd_ctrl_0b;	//0xCC29038C
	PE_O26_ND_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0xCC290390
	PE_O26_ND_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0xCC290394
	PE_O26_ND_LVCRTL_CTRL_00_T                             lvcrtl_ctrl_00;	//0xCC290398
	PE_O26_ND_TPD_STAT_01_T                                   tpd_stat_01;	//0xCC29039C
	PE_O26_ND_TNR_STATUS_05_T                               tnr_status_05;	//0xCC2903A0
	PE_O26_ND_TNR_STATUS_06_T                               tnr_status_06;	//0xCC2903A4
	PE_O26_ND_TNR_STATUS_07_T                               tnr_status_07;	//0xCC2903A8
	PE_O26_ND_TNR_STATUS_08_T                               tnr_status_08;	//0xCC2903AC
	PE_O26_ND_TNR_CTRL_69_T                                   tnr_ctrl_69;	//0xCC2903B0
	PE_O26_ND_TNR_CTRL_70_T                                   tnr_ctrl_70;	//0xCC2903B4
	PE_O26_ND_TNR_CTRL_71_T                                   tnr_ctrl_71;	//0xCC2903B8
	PE_O26_ND_TNR_CTRL_72_T                                   tnr_ctrl_72;	//0xCC2903BC
	PE_O26_ND_TNR_RESET_T                                       tnr_reset;	//0xCC2903C0
	PE_O26_ND_TNR_CTRL_73_T                                   tnr_ctrl_73;	//0xCC2903C4
	PE_O26_ND_TNR_CTRL_74_T                                   tnr_ctrl_74;	//0xCC2903C8
	PE_O26_ND_TNR_CTRL_75_T                                   tnr_ctrl_75;	//0xCC2903CC
	PE_O26_ND_TNR_CTRL_40_T                                   tnr_ctrl_40;	//0xCC2903D0
	PE_O26_ND_TNR_CTRL_41_T                                   tnr_ctrl_41;	//0xCC2903D4
	PE_O26_ND_TNR_CTRL_42_T                                   tnr_ctrl_42;	//0xCC2903D8
	PE_O26_ND_TNR_CTRL_43_T                                   tnr_ctrl_43;	//0xCC2903DC
	PE_O26_ND_TNR_CTRL_44_T                                   tnr_ctrl_44;	//0xCC2903E0
	PE_O26_ND_TNR_CTRL_45_T                                   tnr_ctrl_45;	//0xCC2903E4
	PE_O26_ND_TNR_CTRL_46_T                                   tnr_ctrl_46;	//0xCC2903E8
	PE_O26_ND_TNR_CTRL_47_T                                   tnr_ctrl_47;	//0xCC2903EC
	PE_O26_ND_TNR_CTRL_48_T                                   tnr_ctrl_48;	//0xCC2903F0
	PE_O26_ND_TNR_CTRL_49_T                                   tnr_ctrl_49;	//0xCC2903F4
	PE_O26_ND_TNR_CTRL_50_T                                   tnr_ctrl_50;	//0xCC2903F8
	PE_O26_ND_TNR_CTRL_51_T                                   tnr_ctrl_51;	//0xCC2903FC
	PE_O26_ND_TNR_NE_STAT_00_T                             tnr_ne_stat_00;	//0xCC290400
	PE_O26_ND_TNR_NE_STAT_01_T                             tnr_ne_stat_01;	//0xCC290404
	PE_O26_ND_TNR_NE_STAT_02_T                             tnr_ne_stat_02;	//0xCC290408
	PE_O26_ND_TNR_NE_STAT_03_T                             tnr_ne_stat_03;	//0xCC29040C
	PE_O26_ND_TNR_NE_STAT_04_T                             tnr_ne_stat_04;	//0xCC290410
	PE_O26_ND_TNR_NE_STAT_05_T                             tnr_ne_stat_05;	//0xCC290414
	PE_O26_ND_TNR_NE_STAT_06_T                             tnr_ne_stat_06;	//0xCC290418
	PE_O26_ND_TNR_NE_STAT_07_T                             tnr_ne_stat_07;	//0xCC29041C
	PE_O26_ND_TNR_NE_STAT_08_T                             tnr_ne_stat_08;	//0xCC290420
	PE_O26_ND_TNR_SMG_CTRL_01_T                           tnr_smg_ctrl_01;	//0xCC290424
	PE_O26_ND_TNR_SMG_CTRL_02_T                           tnr_smg_ctrl_02;	//0xCC290428
	PE_O26_ND_TNR_SMG_CTRL_03_T                           tnr_smg_ctrl_03;	//0xCC29042C
	PE_O26_ND_TNR_SMG_CTRL_04_T                           tnr_smg_ctrl_04;	//0xCC290430
	UINT32                                                      reserved6;	//0xCC290434
	UINT32                                                      reserved7;	//0xCC290438
	UINT32                                                      reserved8;	//0xCC29043C
	PE_O26_ND_HIST2_CTRL_00_T                               hist2_ctrl_00;	//0xCC290440
	PE_O26_ND_HIST2_CTRL_01_T                               hist2_ctrl_01;	//0xCC290444
	PE_O26_ND_HIST2_CTRL_02_T                               hist2_ctrl_02;	//0xCC290448
	PE_O26_ND_HIST2_CTRL_03_T                               hist2_ctrl_03;	//0xCC29044C
	PE_O26_ND_HIST2_CTRL_04_T                               hist2_ctrl_04;	//0xCC290450
	PE_O26_ND_HIST2_CTRL_05_T                               hist2_ctrl_05;	//0xCC290454
	PE_O26_ND_HIST2_CTRL_06_T                               hist2_ctrl_06;	//0xCC290458
	PE_O26_ND_HIST2_CTRL_07_T                               hist2_ctrl_07;	//0xCC29045C
	PE_O26_ND_HIST2_CTRL_08_T                               hist2_ctrl_08;	//0xCC290460
	PE_O26_ND_HIST2_CTRL_09_T                               hist2_ctrl_09;	//0xCC290464
	PE_O26_ND_HIST2_CTRL_0A_T                               hist2_ctrl_0a;	//0xCC290468
	PE_O26_ND_HIST2_CTRL_0B_T                               hist2_ctrl_0b;	//0xCC29046C
	PE_O26_ND_HIST2_HIST_AI_CTRL_T                     hist2_hist_ai_ctrl;	//0xCC290470
	PE_O26_ND_HIST2_HIST_AI_DATA_T                     hist2_hist_ai_data;	//0xCC290474
	PE_O26_ND_HIST2_STAT_00_T                               hist2_stat_00;	//0xCC290478
	UINT32                                                      reserved9;	//0xCC29047C
	PE_O26_ND_ND_FSW_CTRL_00_T                             nd_fsw_ctrl_00;	//0xCC290480
	PE_O26_ND_ND_FSW_CTRL_01_T                             nd_fsw_ctrl_01;	//0xCC290484
	PE_O26_ND_ND_FSW_CTRL_02_T                             nd_fsw_ctrl_02;	//0xCC290488
	PE_O26_ND_ND_FSW_CTRL_03_T                             nd_fsw_ctrl_03;	//0xCC29048C
	PE_O26_ND_TNR_ETC_CTRL_00_T                           tnr_etc_ctrl_00;	//0xCC290490
	PE_O26_ND_TNR_ETC_CTRL_01_T                           tnr_etc_ctrl_01;	//0xCC290494
	PE_O26_ND_TNR_ETC_CTRL_02_T                           tnr_etc_ctrl_02;	//0xCC290498
	PE_O26_ND_TNR_ETC_CTRL_03_T                           tnr_etc_ctrl_03;	//0xCC29049C
	PE_O26_ND_TNR_CTRL_56_T                                   tnr_ctrl_56;	//0xCC2904A0
	PE_O26_ND_TNR_CTRL_57_T                                   tnr_ctrl_57;	//0xCC2904A4
	PE_O26_ND_TNR_CTRL_58_T                                   tnr_ctrl_58;	//0xCC2904A8
	PE_O26_ND_TNR_CTRL_59_T                                   tnr_ctrl_59;	//0xCC2904AC
	PE_O26_ND_TNR_CTRL_60_T                                   tnr_ctrl_60;	//0xCC2904B0
	PE_O26_ND_TNR_CTRL_61_T                                   tnr_ctrl_61;	//0xCC2904B4
	PE_O26_ND_PE0_DEBUG3_T                                     pe0_debug3;	//0xCC2904B8
	UINT32                                                     reserved10;	//0xCC2904BC
	PE_O26_ND_FBC_CTRL_02_T                                   fbc_ctrl_02;	//0xCC2904C0
	PE_O26_ND_FBC_CTRL_03_T                                   fbc_ctrl_03;	//0xCC2904C4
	UINT32                                                     reserved11;	//0xCC2904C8
	UINT32                                                     reserved12;	//0xCC2904CC
	PE_O26_ND_GFD_CTRL_00_T                                   gfd_ctrl_00;	//0xCC2904D0
	PE_O26_ND_GFD_CTRL_01_T                                   gfd_ctrl_01;	//0xCC2904D4
	PE_O26_ND_GFD_STAT_00_T                                   gfd_stat_00;	//0xCC2904D8
	PE_O26_ND_GFD_STAT_01_T                                   gfd_stat_01;	//0xCC2904DC
	PE_O26_ND_GFD_STAT_02_T                                   gfd_stat_02;	//0xCC2904E0
	PE_O26_ND_GFD_STAT_03_T                                   gfd_stat_03;	//0xCC2904E4
	PE_O26_ND_TNR_CTRL_66_T                                   tnr_ctrl_66;	//0xCC2904E8
	PE_O26_ND_TNR_CTRL_67_T                                   tnr_ctrl_67;	//0xCC2904EC
	PE_O26_ND_TNR_CTRL_68_T                                   tnr_ctrl_68;	//0xCC2904F0
}PE_ND_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290500 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 load_enable                      :1;	//(1,RW,0x00) //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd1                           :29;
	};
}PE_O26_DNR0_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290504 RW 0x0000_0000
	UINT32 intr_enable                      :1;	//(0,RW,0x00) //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//(6:4,RW,0x00) //interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  NA	'001 =  NA	'010 = NA	'011 = NA	'100 = dnr_end	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//(8,RW,0x00) //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//(26:16,RW,0x00) //the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_O26_DNR0_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290508 RO 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 dnr_frame_id                     :8;	//(23:16,RO,0x0) //DNR_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//(27:24,RO,0x00) //PIC_INIT_FRAME_ID
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29050C RO 0x0000_0000
	UINT32 line_cnt                         :11;	//(10:0,RO,0x00) //
	UINT32 resvd                            :5;
	UINT32 timer_cnt                        :16;	//(31:16,RO,0x0) //timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_O26_DNR0_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290510 RW 0x0000_C000
	UINT32 dec_out_cs_type                  :3;	//(2:0,RW,0x0) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 resvd0                           :5;
	UINT32 reg_sd_5l_mode_en                :1;	//(8,RW,0x00) //
	UINT32 reg_dec_sd_444_en                :1;	//(9,RW,0x0) //Decontour SD( under 960 width) 444 mode enable
	UINT32 resvd1                           :1;
	UINT32 reg_line_cnt_sel                 :1;	//(11,RW,0x0) //Line count info sel.	0 : dnr_line_cnt	1 : dec_line_cnt
	UINT32 dnr_out_420_vsample_mode         :1;	//(12,RW,0x00) //0 := 0,3,4,7,?	1 = 0,2,4,6,?
	UINT32 dnr_out_cs_type                  :3;	//(15:13,RW,0x6) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 detour_enable                    :1;	//(16,RW,0x00) //dnr+decontour detour
	UINT32 half_rate_en                     :1;	//(17,RW,0x00) //should be enabled for the interlaced source	should be enabled for running IFC
	UINT32 reg_dnr_detour                   :1;	//(18,RW,0x0) //
	UINT32 reg_dec_detour                   :1;	//(19,RW,0x0) //
	UINT32 ibuf_en                          :2;	//(21:20,RW,0x0) //(20) input buffer enable Y 	(21) input buffer enable C
	UINT32 dnr_out_422_hsample_mode         :1;	//(22,RW,0x00) //0 := 0,2,4,6,?	1 = 1,3,5,7,?
	UINT32 resvd2                           :1;
	UINT32 dnr_in_lsb_mode                  :2;	//(25:24,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 dnr_out_lsb_mode                 :2;	//(27:26,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 resvd3                           :2;
	UINT32 m_run_id                         :2;	//(31:30,RW,0x00) //
	};
}PE_O26_DNR0_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290514 RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE: ??? ??. ??? ???? ??
	UINT32 resvd0                           :1;
	UINT32 chroma_sampling_type             :3;	//(15:13,RW,0x00) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE
	UINT32 chroma_sampling_type_dec         :3;	//(30:28,RW,0x00) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 resvd1                           :1;
	};
}PE_O26_DNR0_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290518 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //??? ??. ??? ???? ??
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_OUT_SIZE -> in_hsize	1 = PE0_OUT_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR0_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29051C RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE : ??? ??. ??? ???? ??
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE : ??? ??. ??? ???? ??	 (progressive format ??)
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_PE0_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290520 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_WIN_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290524 RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_WIN_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290528 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 ac_bnr_feature_cal_mode          :2;	//(29:28,RW,0x00) //AC-BNR feature cal. mode	'00 := full-screen mode	'01 =  reserved	'10 = active window mode - manual window setting by 	        reg_win_ctrl_2 & reg_win_ctrl_3	'11 = active window mode - auto window setting by black	         boundary detection
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR0_WIN_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29052C RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_WIN_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290530 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O26_DNR0_CUP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290534 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O26_DNR0_CUP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290538 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_CUP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290580 RW 0x0000_0000
	UINT32 reg_glb_tearing_th               :8;	//(7:0,RW,0x0) //
	UINT32 reg_glb_mode_th                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_tearing_strength             :1;	//(12,RW,0x00) //
	UINT32 reg_glb_tearing_cnt_normal       :3;	//(15:13,RW,0x00) //
	UINT32 reg_vf_a_th                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :6;
	UINT32 reg_vflt_force_en                :1;	//(30,RW,0x00) //
	UINT32 reg_vflt_en                      :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR0_VFILTER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290584 RW 0x0000_0000
	UINT32 reg_vflt_debug_en                :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_fmd_mode                     :1;	//(4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_glb_mode                     :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_glb_mode_fw_en               :1;	//(12,RW,0x00) //
	UINT32 resvd3                           :3;
	UINT32 reg_glb_vflt_en                  :1;	//(16,RW,0x00) //
	UINT32 resvd4                           :3;
	UINT32 reg_fmd_vflt_en                  :1;	//(20,RW,0x00) //
	UINT32 resvd5                           :3;
	UINT32 reg_fmd_tearing_cnt_en           :1;	//(24,RW,0x00) //
	UINT32 resvd6                           :3;
	UINT32 reg_fmd_motion_en                :1;	//(28,RW,0x00) //
	UINT32 resvd7                           :3;
	};
}PE_O26_DNR0_VFILTER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290588 RW 0x0000_0000
	UINT32 reg_hmc_vflt_en                  :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_hmc_tearing_cnt_en           :1;	//(4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_hmc_motion_en                :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_loc_vflt_en                  :1;	//(12,RW,0x00) //
	UINT32 resvd3                           :3;
	UINT32 reg_loc_tearing_cnt_en           :1;	//(16,RW,0x00) //
	UINT32 resvd4                           :3;
	UINT32 reg_loc_motion_en_               :1;	//(20,RW,0x00) //
	UINT32 resvd5                           :3;
	UINT32 reg_alpha_sel_mode               :2;	//(25:24,RW,0x00) //
	UINT32 resvd6                           :2;
	UINT32 reg_alpha_sel_mode_en            :2;	//(29:28,RW,0x00) //
	UINT32 resvd7                           :2;
	};
}PE_O26_DNR0_VFILTER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29058C RW 0x0000_1400
	UINT32 cti_en                           :1;	//(0,RW,0x00) //CTI enable
	UINT32 cti_clipping_mode                :1;	//(1,RW,0x00) //op mode	'0' : CTI	'1': peaking(for debug)
	UINT32 cti_pre_flt_mode                 :1;	//(2,RW,0x00) //pre-filtering	0 : off	1 : on
	UINT32 cti_tap                          :2;	//(4:3,RW,0x00) //CTI filter tap size	'0' : 7-tap	'1': 5-tap	'2': 3_2-tap	'3': 3-tap
	UINT32 resvd0                           :3;
	UINT32 cti_gain                         :8;	//(15:8,RW,0x14) //CTI gain(3.5u)
	UINT32 cti_debug_mode                   :3;	//(18:16,RW,0x00) //debug mode	"000" : normal display	"100" : coring map(cb)	"101" : coring map(cr)	"110" : avg(cb)	"111" : avg(cr)
	UINT32 resvd1                           :13;
	};
}PE_O26_DNR0_CTI_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290590 RW 0x0020_2101
	UINT32 cti_coring_th0                   :8;	//(7:0,RW,0x1) //CTI coring th0
	UINT32 cti_coring_th1                   :8;	//(15:8,RW,0x21) //CTI coring th1
	UINT32 cti_coring_smooth                :3;	//(18:16,RW,0x0) //NOT USED
	UINT32 resvd0                           :1;
	UINT32 reg_cti_tap2                     :2;	//(21:20,RW,0x2) //CTI coring map size	"00" : 7-tap	"01" : 5-tap	"10" : 3-tap	o.w : 7-tap
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_CTI_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290594 RW 0x0000_0000
	UINT32 reg_dnr_max_enable               :1;	//(0,RW,0x00) //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable               :1;	//(1,RW,0x00) //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel                  :1;	//(2,RW,0x00) //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel            :1;	//(3,RW,0x00) //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel                :1;	//(4,RW,0x0) //0: original, 1: v_filter
	UINT32 reg_decon_max_enable             :1;	//(5,RW,0x0) //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en             :1;	//(6,RW,0x0) //
	UINT32 reg_half_rate_cg_n               :1;	//(7,RW,0x0) //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en                   :1;	//(8,RW,0x00) //ac : black, dc : white, mnr : green
	UINT32 reg_dnr_motion_sel               :1;	//(9,RW,0x00) //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 resvd0                           :1;
	UINT32 reg_face_obj_sel                 :1;	//(11,RW,0x0) //0: dnr obc(4K??, internal), 1: nd obc(4K ??(8K), external)	Not used in O-series(Only E series)
	UINT32 resvd1                           :4;
	UINT32 reg_win_en                       :1;	//(16,RW,0x00) //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//(17,RW,0x00) //border enable
	UINT32 reg_win_inout                    :1;	//(18,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 reg_ipc_motion_en                :1;	//(21,RW,0x0) //hmc_flag ?? => 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//(24:22,RW,0x00) //0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//(31:25,RW,0x0) //applied ifc when delta is greater than th
	};
}PE_O26_DNR0_DNR_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290598 RW 0x0000_0000
	UINT32 reg_dbg_en                       :1;	//(0,RW,0x00) //debug bar en
	UINT32 reg_show_f3d                     :1;	//(1,RW,0x00) //
	UINT32 reg_show_bnr                     :1;	//(2,RW,0x00) //show debug bar for bnr	(acness,acness gain, dc_gain)
	UINT32 reg_f3d_mode                     :1;	//(3,RW,0x00) //
	UINT32 reg_acness_or_acness_gain        :1;	//(4,RW,0x00) //0 : acness (blue, green)	1 : acness gain (yellow, red)
	UINT32 resvd                            :27;
	};
}PE_O26_DNR0_DNR_DBAR_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29059C RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_detect_level_th              :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DNR0_REG_C420_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905A0 RW 0x0000_0000
	UINT32 reg_mnr_enable                   :1;	//(0,RW,0x00) //
	UINT32 reg_mnr_debug                    :1;	//(1,RW,0x00) //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//(2,RW,0x00) //
	UINT32 reg_mnr_chroma_en                :1;	//(3,RW,0x00) //
	UINT32 reg_h_expand                     :2;	//(5:4,RW,0x0) //0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//(7:6,RW,0x00) //0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//(15:8,RW,0x0) //
	UINT32 reg_snr_th                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_th_max                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_MNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905A4 RW 0x0000_0000
	UINT32 reg_mmd_y_max                    :8;	//(7:0,RW,0x0) //edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//(15:8,RW,0x0) //reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//(23:16,RW,0x0) //reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//(31:24,RW,0x0) //reg_mnr_s2_mmd_min
	};
}PE_O26_DNR0_MNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905A8 RW 0x0000_0000
	UINT32 reg_mnr_debug_mode               :4;	//(3:0,RW,0x00) //0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain	9: prv mmd map	A: mmd var	B: O22 New, final gain
	UINT32 reg_mnr_debug_en                 :1;	//(4,RW,0x00) //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_MNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905AC RW 0x0000_0000
	UINT32 reg_blur_sel                     :1;	//(0,RW,0x00) //
	UINT32 reg_pattern_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_equal_th                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_scale                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_MNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905B0 RW 0x0000_0000
	UINT32 reg_mmd_fil_x_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_x_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_x_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_x_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_MNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905B4 RW 0x0000_0000
	UINT32 reg_mmd_fil_y_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_y_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_y_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_y_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_MNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905B8 RW 0x0404_0A40
	UINT32 reg_bnr_ac_detail_max            :8;	//(7:0,RW,0x40) //detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//(15:8,RW,0xA) //detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//(23:16,RW,0x4) //th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//(31:24,RW,0x4) //th used to find point of inflection
	};
}PE_O26_DNR0_DETAIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905BC RW 0x0000_0000
	UINT32 reg_dc_bnr_enable                :1;	//(0,RW,0x0) //DC BNR enable	0 := off ( output debug mode )	1  = on
	UINT32 reg_dc_blur_debug_mode           :1;	//(1,RW,0x0) //0: blur, 1: white
	UINT32 reg_dc_blur_sel                  :2;	//(3:2,RW,0x0) //DC blur sel => 0 : 3x3, 1 : 5x5, 2 : 9x5
	UINT32 reg_dc_output_debug_mode         :4;	//(7:4,RW,0x0) //0: bypass	1: motion	2: motion gain	3: sum of variance	4: variance gain	5: edge protection map	6: DC gain without edge protection	7: DC gain with edge protection	8: chroma gain without edge protection	9: chroma gain with edge protection	10: fil_diff_th
	UINT32 reg_en_obj_amf_ctrl              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_obj_gain_mul                 :2;	//(14:13,RW,0x0) //
	UINT32 reg_obj_gain_en                  :1;	//(15,RW,0x0) //
	UINT32 reg_dc_motion_max                :8;	//(23:16,RW,0x0) //dc motion gain th
	UINT32 reg_dc_motion_min                :8;	//(31:24,RW,0x0) //dc motion gain th, if(reg_dc_motion_en == 0) reg_dc_motion_y_max = manual motion gain value
	};
}PE_O26_DNR0_DC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905C0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_manual_fil_motion_gain       :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_chroma_en                :1;	//(16,RW,0x0) //
	UINT32 reg_fil_manual_en                :1;	//(17,RW,0x0) //
	UINT32 reg_dc_pattern_en                :1;	//(18,RW,0x0) //
	UINT32 reg_luma_gain_en                 :1;	//(19,RW,0x0) //
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //0x5
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //0x2
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //0x5
	};
}PE_O26_DNR0_DC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905C4 RW 0x0000_0000
	UINT32 reg_dc_var_en                    :1;	//(0,RW,0x0) //0x1
	UINT32 reg_dc_motion_en                 :1;	//(1,RW,0x0) //0x0
	UINT32 reg_dc_protection_en             :1;	//(2,RW,0x0) //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//(15:10,RW,0x0) //0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//(23:16,RW,0x0) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_DC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905C8 RW 0x0000_0000
	UINT32 reg_dc_bnr_var_th3               :8;	//(7:0,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//(15:8,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//(23:16,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//(31:24,RW,0x0) //dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
}PE_O26_DNR0_DC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905CC RW 0x0000_0000
	UINT32 reg_dc_motion_y_min              :8;	//(7:0,RW,0x0) //motion gain y?
	UINT32 reg_dc_motion_y_max              :8;	//(15:8,RW,0x0) //motion gain y?
	UINT32 resvd                            :16;
	};
}PE_O26_DNR0_DC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905D0 RW 0x0000_0000
	UINT32 reg_dc_var_y_th0                 :8;	//(7:0,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th1                 :8;	//(15:8,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th2                 :8;	//(23:16,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th3                 :8;	//(31:24,RW,0x0) //variance gain y?
	};
}PE_O26_DNR0_DC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905D4 RW 0xB30B_0B4F
	UINT32 reg_bnr_ac_h_en                  :1;	//(0,RW,0x1) //
	UINT32 reg_bnr_ac_v_en                  :1;	//(1,RW,0x1) //
	UINT32 reg_bnr_ac_h_chroma_en           :1;	//(2,RW,0x1) //
	UINT32 reg_bnr_ac_v_chroma_en           :1;	//(3,RW,0x1) //
	UINT32 reg_bnr_ac_acness_resol_h        :2;	//(5:4,RW,0x0) //1: /2, 2: /4, 3:/ 8
	UINT32 reg_multi_run_mode               :1;	//(6,RW,0x1) //
	UINT32 reg_ac_bnr_gain_yc_sel           :1;	//(7,RW,0x0) //
	UINT32 reg_bnr_ac_diff_min_v_th         :8;	//(15:8,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_diff_min_h_th         :8;	//(23:16,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_iir_gain              :8;	//(31:24,RW,0xB3) //alpha value used in IIR
	};
}PE_O26_DNR0_AC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905D8 RW 0x0F19_370B
	UINT32 reg_bnr_ac_global_motion_th      :8;	//(7:0,RW,0xB) //0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//(15:8,RW,0x37) //th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//(23:16,RW,0x19) //th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//(31:24,RW,0xF) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905DC RW 0x0A20_4060
	UINT32 reg_bnr_ac_motion_3              :8;	//(7:0,RW,0x60) //motion gain x?
	UINT32 reg_bnr_ac_motion_2              :8;	//(15:8,RW,0x40) //motion gain x?
	UINT32 reg_bnr_ac_motion_1              :8;	//(23:16,RW,0x20) //motion gain x?
	UINT32 reg_bnr_ac_motion_0              :8;	//(31:24,RW,0xA) //motion gain x?
	};
}PE_O26_DNR0_AC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905E0 RO 0x0000_0000
	UINT32 c420_tearing_cnt                 :16;	//(15:0,RO,0x0) //
	UINT32 global_motion_iir                :8;	//(23:16,RO,0x0) //
	UINT32 global_dc_gain                   :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905E4 RW 0x3060_A0FF
	UINT32 reg_bnr_ac_motion_y_3            :8;	//(7:0,RW,0xFF) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_2            :8;	//(15:8,RW,0xA0) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_1            :8;	//(23:16,RW,0x60) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_0            :8;	//(31:24,RW,0x30) //motion gain y?
	};
}PE_O26_DNR0_AC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905E8 RW 0x1937_5000
	UINT32 reg_bnr_ac_v_init_offset         :3;	//(2:0,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//(5:3,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//(7:6,RW,0x00) //0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//(11:8,RW,0x00) //debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//(15:12,RW,0x05) //stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//(23:16,RW,0x37) //
	UINT32 reg_bnr_ac_v_acness_min          :8;	//(31:24,RW,0x19) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905EC RO 0x0000_0000
	UINT32 acness_v_l                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_g                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905F0 RW 0xFA96_3201
	UINT32 reg_bnr_ac_detail_th4            :8;	//(7:0,RW,0x1) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//(15:8,RW,0x32) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//(23:16,RW,0x96) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//(31:24,RW,0xFA) //detail th used in AC-BNR final mux
	};
}PE_O26_DNR0_AC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905F4 RW 0x00FF_C0C0
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//(7:0,RW,0xC0) //SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//(15:8,RW,0xC0) //SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//(23:16,RW,0xFF) //SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//(31:24,RW,0x0) //0x00
	};
}PE_O26_DNR0_AC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905F8 RW 0x80FF_8040
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//(7:0,RW,0x40) //SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//(15:8,RW,0x80) //SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//(23:16,RW,0xFF) //SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//(31:24,RW,0x80) //SD : 0x00, HD : 0x80
	};
}PE_O26_DNR0_AC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2905FC RO 0x0000_0000
	UINT32 h_init                           :8;	//(7:0,RO,0x0) //
	UINT32 v_init                           :8;	//(15:8,RO,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_vfilter_tearing_cnt          :12;	//(31:20,RO,0x00) //
	};
}PE_O26_DNR0_DNR_STAT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290600 RW 0x0000_0E20
	UINT32 reg_ac_master_c_gain             :8;	//(7:0,RW,0x20) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_ac_bnr_enable                :1;	//(8,RW,0x00) //0 : debug mode, 1 : ac result
	UINT32 reg_ac_bnr_motion_en             :1;	//(9,RW,0x01) //1 : motion gain enable	0 : reg_bnr_ac_motion_y_max = manual motion gain value
	UINT32 reg_ac_bnr_acness_en             :1;	//(10,RW,0x01) //1 : acness gain enable	0 : reg_bnr_ac_acness_y_max = manual acness gain value
	UINT32 reg_ac_bnr_position_en           :1;	//(11,RW,0x01) //1 : position gain enable	0 : reg_bnr_ac_pos_gain_H0_7 = manual position gain value
	UINT32 reg_detail_sel                   :1;	//(12,RW,0x00) //0: old, 1: new
	UINT32 resvd                            :3;
	UINT32 reg_bnr_ac_manual_init_v         :3;	//(18:16,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_v          :1;	//(19,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_manual_init_h         :3;	//(22:20,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_h          :1;	//(23,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_pos_gain_l3           :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290604 RW 0x0009_8000
	UINT32 reg_acness_sel                   :1;	//(0,RW,0x00) //
	UINT32 reg_g_motion_manual_en           :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :6;
	UINT32 reg_ac_bnr_debug_h_en            :1;	//(8,RW,0x00) //
	UINT32 reg_ac_bnr_debug_v_en            :1;	//(9,RW,0x00) //
	UINT32 reg_ac_master_y_gain             :6;	//(15:10,RW,0x20) //0x20 is max
	UINT32 reg_g_motion_scale               :3;	//(18:16,RW,0x1) //
	UINT32 reg_g_motion_div                 :2;	//(20:19,RW,0x1) //
	UINT32 resvd1                           :10;
	UINT32 reg_ac_flt_level_sel             :1;	//(31,RW,0x0) //0 : weak, 1 : strong
	};
}PE_O26_DNR0_AC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290608 RW 0xFF00_FF00
	UINT32 reg_ac_detail_gain_y_min         :8;	//(7:0,RW,0x0) //detail gain y?
	UINT32 reg_ac_detail_gain_y_max         :8;	//(15:8,RW,0xFF) //detail gain y?
	UINT32 reg_bnr_ac_acness_y_min          :8;	//(23:16,RW,0x0) //acness gain y  ?
	UINT32 reg_bnr_ac_acness_y_max          :8;	//(31:24,RW,0xFF) //acness gain y  ?
	};
}PE_O26_DNR0_AC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29060C RW 0xFF00_FF00
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//(7:0,RW,0x0) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//(15:8,RW,0xFF) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//(23:16,RW,0x0) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//(31:24,RW,0xFF) //ac bnr final mux?? ??? detail gain ? y?
	};
}PE_O26_DNR0_AC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290610 RW 0x0000_FFFF
	UINT32 reg_g_motion_manual              :8;	//(7:0,RW,0xFF) //
	UINT32 reg_acness_scale_mul             :8;	//(15:8,RW,0xFF) //
	UINT32 reg_bnr_ac_detail_max            :8;	//(23:16,RW,0x0) //
	UINT32 reg_bnr_ac_detail_min            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290614 RW 0x00E8_D800
	UINT32 reg_y_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_y_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_y_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|? [7:0] ??	1: |y''|/4? [9:2] ??
	UINT32 resvd1                           :1;
	UINT32 reg_y_drvt2_hcoef_sel            :3;	//(10:8,RW,0x00) //5tap, h[0, 0, 8, 8, 0, -8, -8, -0, -0]/16	7tap, h[0, 4, 6, 6, 0, -6, -6, -4, -0]/16	9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_medge_meth                   :1;	//(11,RW,0x01) //0: 13x3 window (? ????? ???? ?? ??)	1 :13x3 window (?? ??? coring)
	UINT32 reg_medge_th                     :8;	//(19:12,RW,0x8D) //diff? th
	UINT32 reg_medge_coring_th              :8;	//(27:20,RW,0xE) //??? th
	UINT32 reg_medge_ch_tap                 :2;	//(29:28,RW,0x00) //0: 13tap	1: 11tap	2: 9tap
	UINT32 reg_edge_meth                    :2;	//(31:30,RW,0x00) //diff? center?? on/off
	};
}PE_O26_DNR0_IFC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290618 RW 0x0C00_3820
	UINT32 reg_edge_ddrvt_gain_y1           :8;	//(7:0,RW,0x20) //
	UINT32 reg_edge_ddrvt_gain_x1           :8;	//(15:8,RW,0x38) //
	UINT32 reg_edge_ddrvt_gain_y0           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_ddrvt_gain_x0           :8;	//(31:24,RW,0xC) //?? y edge gain
	};
}PE_O26_DNR0_IFC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29061C RW 0x0000_0000
	UINT32 reg_c_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_c_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_c_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|? [7:0] ??	1: |y''|/4? [9:2] ??
	UINT32 resvd1                           :25;
	};
}PE_O26_DNR0_IFC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290620 RW 0x1100_6E20
	UINT32 reg_c_edge_gain_y1               :8;	//(7:0,RW,0x20) //
	UINT32 reg_c_edge_gain_x1               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_c_edge_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_c_edge_gain_x0               :8;	//(31:24,RW,0x11) //
	};
}PE_O26_DNR0_IFC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290624 RW 0x0003_1203
	UINT32 reg_crs_para_tap                 :2;	//(1:0,RW,0x03) //0 : 5tap, h[0, 1, 1, 1, 1 ,1]	1 : 4tap, h[0, 0, 1, 1, 1, 1]	2 : 4tap, h[0, 1, 1, 1, 1, 0]	3 : 6tap, h[1, 1, 1, 1, 1, 1]
	UINT32 reg_cdst_th                      :10;	//(11:2,RW,0x080) //Cb, Cr ??? ? ? ????? ??
	UINT32 reg_crs_op_tap                   :2;	//(13:12,RW,0x01) //0 : 9 tap	1 : 7 tap	2 : 5 tap
	UINT32 reg_crs_gain_res                 :1;	//(14,RW,0x00) //0: |c diff|? [7:0] ??	1: |c diff|/4? [9:2] ??
	UINT32 resvd0                           :1;
	UINT32 reg_cdiff_hcoef_sel              :2;	//(17:16,RW,0x03) //left/right diff? coefficient (? ?? 255)	0 : h[0x00, 0x08, 0x08, 0x0A, 0x1E, 0xC8]/256	1 : h[0x00, 0x10, 0x10, 0x14, 0x40, 0x8C]/256
	UINT32 resvd1                           :10;
	UINT32 reg_crs_point                    :2;	//(29:28,RW,0x00) //
	UINT32 reg_crs_meth                     :2;	//(31:30,RW,0x00) //0 : (1??) +  L/R ?? ?? ???? ???	1 : (2??) +  L/R ?? ??? ???? 	2 : L/R?? chroma diff? threshold?? ??
	};
}PE_O26_DNR0_IFC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290628 RW 0x0000_6616
	UINT32 reg_crs_gain_y1                  :8;	//(7:0,RW,0x16) //
	UINT32 reg_crs_gain_x1                  :8;	//(15:8,RW,0x66) //
	UINT32 reg_crs_gain_y0                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_IFC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29062C RW 0x0000_0000
	UINT32 reg_sm_pre_lut_y0                :8;	//(7:0,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x0                :8;	//(15:8,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y1                :8;	//(23:16,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x1                :8;	//(31:24,RW,0) //SM Blend LUT
	};
}PE_O26_DNR0_DNR_SMG_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290630 RW 0x0000_0000
	UINT32 reg_sm_pre_lut_y2                :8;	//(7:0,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x2                :8;	//(15:8,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y3                :8;	//(23:16,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x3                :8;	//(31:24,RW,0) //SM Blend LUT
	};
}PE_O26_DNR0_DNR_SMG_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290634 RW 0x2400_0000
	UINT32 reg_ifc_en                       :1;	//(0,RW,0x00) //0 : 0ff / 1 : on
	UINT32 reg_clp_on                       :1;	//(1,RW,0x00) //0 : 0ff / 1 : Max clipping
	UINT32 resvd0                           :2;
	UINT32 reg_edge_en                      :1;	//(4,RW,0x00) //mmd en
	UINT32 resvd1                           :15;
	UINT32 reg_clp_tap                      :2;	//(21:20,RW,0x00) //0 : 13 tap	1 : 11 tap	2 : 9tap
	UINT32 reg_ifc_flt_sel                  :2;	//(23:22,RW,0x00) //3 : cross	2 : multi edge cedge	1 : yedge	0 : default
	UINT32 reg_debug_en                     :2;	//(25:24,RW,0x00) //0 : debug off	1 : blend debug on	2 : debug on
	UINT32 reg_debug_mode                   :4;	//(29:26,RW,0x09) //0 : operation mode	1 : cross check	2 : multi edge	3 : 	4 : cr edge gain	5 : cb edge gain	6 : y edge gain	7 : cross gain	8 : cross blend	9 : multi-edge blend	10 : 	11 : 2???	12 : 	13 : 1???
	UINT32 reg_bld_tap                      :2;	//(31:30,RW,0x00) //0: ?? 2? average	1: ?? 1?, center average
	};
}PE_O26_DNR0_IFC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290638 RW 0x0000_0000
	UINT32 reg_f0_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f0_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f1_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f0_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_ELLIPSE_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29063C RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_master               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_ELLIPSE_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290640 RW 0x0000_0000
	UINT32 reg_f1_h1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_w2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_offset               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_ELLIPSE_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290644 RW 0x8004_0000
	UINT32 resvd                            :16;
	UINT32 reg_crs_zero_th                  :8;	//(23:16,RW,0x4) //cross point?? cb-cr? 0?? ?? ???
	UINT32 reg_dst_cdst_th                  :8;	//(31:24,RW,0x80) //?? ????? cdst ?? ??
	};
}PE_O26_DNR0_IFC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290648 RW 0x0000_0000
	UINT32 reg_smg_dbg_mode                 :2;	//(1:0,RW,0x0) //0: blur pel	1: Cur pel	2: Blend	3: SMG map
	UINT32 resvd0                           :1;
	UINT32 reg_smg_dbg_en                   :1;	//(3,RW,0x0) //
	UINT32 resvd1                           :12;
	UINT32 reg_sm_force_data                :8;	//(23:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_sm_pattern_en                :1;	//(28,RW,0x0) //
	UINT32 reg_sm_force_en                  :1;	//(29,RW,0x0) //
	UINT32 reg_sm_blend_cc_en               :1;	//(30,RW,0x0) //
	UINT32 reg_sm_blend_yy_en               :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_DNR_SMG_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29064C RW 0x0000_0000
	UINT32 reg_sm_pre_lut_y0                :8;	//(7:0,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x0                :8;	//(15:8,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y1                :8;	//(23:16,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x1                :8;	//(31:24,RW,0) //SM Blend LUT
	};
}PE_O26_DNR0_DEC_SMG_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290650 RW 0x0640_11FF
	UINT32 reg_medge_gain_y1                :8;	//(7:0,RW,0xFF) //
	UINT32 reg_medge_gain_x1                :8;	//(15:8,RW,0x11) //
	UINT32 reg_medge_gain_y0                :8;	//(23:16,RW,0x40) //
	UINT32 reg_medge_gain_x0                :8;	//(31:24,RW,0x6) //1/3?
	};
}PE_O26_DNR0_IFC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290654 RW 0x0010_02A2
	UINT32 reg_crs_op_gain_isel             :2;	//(1:0,RW,0x02) //0 : max	1 : min	2 : average
	UINT32 reg_crs_op_gain_res              :1;	//(2,RW,0x00) //0: [7:0] ??	1: [9:2] ??
	UINT32 reg_crs_cdst_flt                 :3;	//(5:3,RW,0x04) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd0                           :1;
	UINT32 reg_crs_cdst_vmdn                :1;	//(7,RW,0x01) //5x5 median/max (v->h)
	UINT32 reg_crs_cdst_op_flt              :3;	//(10:8,RW,0x02) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd1                           :5;
	UINT32 reg_op_wgain_coef1               :2;	//(17:16,RW,0x00) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef2               :2;	//(19:18,RW,0x00) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef3               :2;	//(21:20,RW,0x01) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 resvd2                           :10;
	};
}PE_O26_DNR0_IFC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290658 RW 0x8500_DCFF
	UINT32 reg_crs_op_gain_y1               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_crs_op_gain_x1               :8;	//(15:8,RW,0xDC) //
	UINT32 reg_crs_op_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_op_gain_x0               :8;	//(31:24,RW,0x85) //
	};
}PE_O26_DNR0_IFC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29065C RW 0x0000_0000
	UINT32 reg_sm_pre_lut_y2                :8;	//(7:0,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x2                :8;	//(15:8,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_y3                :8;	//(23:16,RW,0) //SM Blend LUT
	UINT32 reg_sm_pre_lut_x3                :8;	//(31:24,RW,0) //SM Blend LUT
	};
}PE_O26_DNR0_DEC_SMG_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290660 RW 0x2100_0000
	UINT32 resvd0                           :16;
	UINT32 reg_medge_op_th                  :8;	//(23:16,RW,0x0) //???? ?? ??? (3??, ???)
	UINT32 reg_mmd_gain_en                  :1;	//(24,RW,0x01) //
	UINT32 reg_mmd_gain_flt                 :2;	//(26:25,RW,0x00) //0: off	1: ???121
	UINT32 reg_mmd_gain_tap                 :2;	//(28:27,RW,0x00) //0: 13	1: 11	2: 9
	UINT32 reg_mmd_gain_res                 :1;	//(29,RW,0x01) //0: [7:0] ??	1: [9:2] ??
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR0_IFC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290664 RW 0x0000_0000
	UINT32 reg_smg_dbg_mode                 :2;	//(1:0,RW,0x0) //0: blur pel	1: Cur pel	2: Blend	3: SMG map
	UINT32 resvd0                           :1;
	UINT32 reg_smg_dbg_en                   :1;	//(3,RW,0x0) //
	UINT32 resvd1                           :12;
	UINT32 reg_sm_force_data                :8;	//(23:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_sm_pattern_en                :1;	//(28,RW,0x0) //
	UINT32 reg_sm_force_en                  :1;	//(29,RW,0x0) //
	UINT32 reg_sm_blend_cc_en               :1;	//(30,RW,0x0) //
	UINT32 reg_sm_blend_yy_en               :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_DEC_SMG_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290668 RW 0x0080_B000
	UINT32 reg_mmd_gain_y1                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_gain_x1                  :8;	//(15:8,RW,0xB0) //
	UINT32 reg_mmd_gain_y0                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_mmd_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_IFC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29066C RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_sel_output                   :1;	//(24,RW,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290670 RW 0x0000_0000
	UINT32 reg_f1_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f1_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f1_w2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f3_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f2_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_ELLIPSE_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290674 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_DEC_LOWAPL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290678 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_DEC_LOWAPL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29067C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_DEC_LOWAPL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290680 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_DEC_LOWAPL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290684 RW 0x0000_0000
	UINT32 reg_f2_h2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290688 RW 0x0000_0000
	UINT32 pre_121_blur_en                  :1;	//(0,RW,0x00) //
	UINT32 pre_median_en                    :1;	//(1,RW,0x00) //
	UINT32 resvd                            :30;
	};
}PE_O26_DNR0_C_PRE_BLUR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29068C RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290690 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f2_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290694 RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f3_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290698 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f3_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_ELLIPSE_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29069C RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_h_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_h                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906A0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_v_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_v                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_AC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906A4 RW 0x4030_2010
	UINT32 reg_fil_motion_x_th0             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th1             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th2             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th3             :8;	//(31:24,RW,0x40) //
	};
}PE_O26_DNR0_DC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906A8 RW 0xFF60_4020
	UINT32 reg_fil_motion_y_th0             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th1             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th2             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th3             :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_DNR0_DC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906AC RW 0x3020_1001
	UINT32 reg_mmd_sel                      :2;	//(1:0,RW,0x01) //0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//(15:8,RW,0x10) //
	UINT32 reg_hist_bin_th1                 :8;	//(23:16,RW,0x20) //
	UINT32 reg_hist_bin_th2                 :8;	//(31:24,RW,0x30) //
	};
}PE_O26_DNR0_SQM_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906B0 RW 0x7060_5040
	UINT32 reg_hist_bin_th3                 :8;	//(7:0,RW,0x40) //
	UINT32 reg_hist_bin_th4                 :8;	//(15:8,RW,0x50) //
	UINT32 reg_hist_bin_th5                 :8;	//(23:16,RW,0x60) //
	UINT32 reg_hist_bin_th6                 :8;	//(31:24,RW,0x70) //
	};
}PE_O26_DNR0_SQM_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906B4 RW 0x0461_E046
	UINT32 reg_trans_mmd_th                 :8;	//(7:0,RW,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//(19:10,RW,0x78) //
	UINT32 reg_edf_mmd_th                   :8;	//(27:20,RW,0x46) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_SQM_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906B8 RW 0x0000_0000
	UINT32 reg_sqm_win_mode_x1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//(30,RW,0x00) //
	UINT32 reg_sqm_win_mode_en              :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR0_SQM_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906BC RW 0x0000_0000
	UINT32 reg_sqm_win_mode_y1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR0_SQM_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906C0 RW 0x0000_0080
	UINT32 reg_tp_binary_th                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}PE_O26_DNR0_TPD_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906C4 RW 0x0000_0000
	UINT32 reg_win_mode_x1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_x0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_win_mode_mode                :1;	//(30,RW,0x00) //0: inside, 1: outside
	UINT32 reg_win_mode_en                  :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR0_WINDOW_MODE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906C8 RW 0x0000_0000
	UINT32 reg_win_mode_y1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_y0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR0_WINDOW_MODE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906D0 RO 0x0000_0000
	UINT32 acness_v_g                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v                         :8;	//(23:16,RO,0x0) //
	UINT32 acness_h                         :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906D4 RO 0x0000_0000
	UINT32 bad_up_cnt                       :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 acness_v_l                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906D8 RO 0x0000_0000
	UINT32 acness_gain_v_l                  :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h_l                  :8;	//(15:8,RO,0x0) //
	UINT32 acness_gain_v_g                  :8;	//(23:16,RO,0x0) //
	UINT32 acness_gain_h_g                  :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906DC RO 0x0000_0000
	UINT32 s_apl_val                        :8;	//(7:0,RO,0x0) //
	UINT32 resvd0                           :8;
	UINT32 s_apl_alpha                      :8;	//(23:16,RO,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_DNR_STAT_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906E0 RO 0x0000_0000
	UINT32 acness_gain_v                    :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h                    :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_iir                     :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_iir                     :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906E4 RO 0x0000_0000
	UINT32 oled_apl_tcon                    :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 oled_apl_hdr                     :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :2;
	UINT32 oled_apl_de                      :1;	//(28,RO,0x0) //
	UINT32 resvd2                           :3;
	};
}PE_O26_DNR0_APL_STAT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906E8 RO 0x0000_0000
	UINT32 naive_apl_tcon_mux               :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_tcon                    :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DNR0_APL_STAT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906EC RO 0x0000_0000
	UINT32 naive_apl_hdr_mux                :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_hdr                     :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DNR0_APL_STAT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906F0 RO 0x0000_0000
	UINT32 e_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_11_SQM_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906F4 RO 0x0000_0000
	UINT32 e_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_12_SQM_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906F8 RO 0x0000_0000
	UINT32 e_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_13_SQM_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2906FC RO 0x0000_0000
	UINT32 e_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_14_SQM_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290700 RO 0x0000_0000
	UINT32 f_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_15_SQM_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290704 RO 0x0000_0000
	UINT32 f_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_16_SQM_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290708 RO 0x0000_0000
	UINT32 f_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_17_SQM_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29070C RO 0x0000_0000
	UINT32 f_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_18_SQM_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290710 RO 0x0000_0000
	UINT32 t_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_19_SQM_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290714 RO 0x0000_0000
	UINT32 t_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_20_SQM_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290718 RO 0x0000_0000
	UINT32 t_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_21_SQM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29071C RO 0x0000_0000
	UINT32 t_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_22_SQM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290720 RO 0x0000_0000
	UINT32 res_h_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_23_TPD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290724 RO 0x0000_0000
	UINT32 res_v_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_v_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_24_TPD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290728 RO 0x0000_0000
	UINT32 res_v_cnt_3                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_3                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR0_DNR_STAT_25_TPD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290730 RW 0x40302010
	UINT32 reg_fil_motion_x_th3             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th2             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th1             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th0             :8;	//(31:24,RW,0x40) //
	};
}PE_O26_DNR0_AC_BNR_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290734 RW 0xFF604020
	UINT32 reg_fil_motion_y_th3             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th2             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th1             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th0             :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_DNR0_AC_BNR_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290738 RW 0x0000_0000
	UINT32 reg_tearing_y_1                  :4;	//(3:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tearing_y_0                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_tearing_x_1                  :4;	//(19:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_tearing_x_0                  :4;	//(27:24,RW,0x0) //
	UINT32 resvd3                           :4;
	};
}PE_O26_DNR0_VFILTER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29073C RW 0x0000_0000
	UINT32 reg_motion_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290740 RW 0x0000_0000
	UINT32 reg_motion_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290744 RW 0x0000_0000
	UINT32 reg_global_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290748 RW 0x0000_0000
	UINT32 reg_global_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29074C RW 0x0000_0000
	UINT32 reg_blend_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290750 RW 0x0000_0000
	UINT32 reg_blend_y_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290754 RW 0x0000_0000
	UINT32 reg_hmc_x_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_x_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_x_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_x_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290758 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_y_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_y_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_y_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29075C RW 0x0000_0000
	UINT32 reg_local_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290760 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_VFILTER_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290764 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_master_bypass_en             :1;	//(1,RW,0x0) //
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //not used in O22
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ? ??)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //not used in O22
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290768 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29076C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290770 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290774 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290778 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29077C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290780 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290784 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290788 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29078C RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290790 RW 0x0000_0000
	UINT32 reg_gain_x3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290794 RW 0x0000_0000
	UINT32 reg_gain_x7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290798 RW 0x0000_0000
	UINT32 reg_gain_y3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29079C RW 0x0000_0000
	UINT32 reg_gain_y7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907A0 RW 0x0000_0000
	UINT32 reg_lti_en                       :1;	//(0,RW,0x0) //
	UINT32 reg_lti_clipping_mode            :1;	//(1,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap                      :2;	//(4:3,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_lti_gain                     :8;	//(15:8,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_ycm_c_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_ycm_y_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_ycm_band_sel                 :3;	//(30:28,RW,0x0) //
	UINT32 reg_ycm_en                       :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_CTI_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907A4 RW 0x0000_0000
	UINT32 reg_lti_coring_th0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lti_coring_th1               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lti_coring_sm                :3;	//(18:16,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//(21:20,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_CTI_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907A8 RW 0x0000_0000
	UINT32 reg_small_mmd_flat_th            :8;	//(7:0,NA,0x0) //
	UINT32 reg_large_mmd_flat_th            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//(28,NA,0x0) //
	UINT32 reg_mmd_dist_kernal_width        :2;	//(30:29,NA,0x0) //
	UINT32 reg_mmd_dist_gain_en             :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907AC RW 0x0000_0000
	UINT32 reg_dist_gain_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907B0 RW 0x0000_0000
	UINT32 reg_dist_gain_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907B4 RW 0x0000_0000
	UINT32 reg_chroma_gain_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907B8 RW 0x0000_0000
	UINT32 reg_chroma_gain_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907BC RW 0x0000_0000
	UINT32 reg_i_sel_mmd_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907C0 RW 0x0000_0000
	UINT32 reg_i_sel_mmd_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_MNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907C4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907C8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907CC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907DC RW 0x0000_0000
	UINT32 resvd0                           :14;
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 resvd1                           :8;
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //Not used in O22
	UINT32 resvd2                           :1;
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :5;	//(30:26,RW,0x0) //0: final_gain	1: variance_gain	2: variance - dc frame input	3: variance - original var	4: variance - blur dc map	5: variance - blend dc map	6: variance - final dc map	7: rmmd - l0 mmd	8: rmmd - l0 luma	9: rmmd - refine	A : rmmd - final gain	B: blur map - mmd input luma	C: blur map - mmd gain	D: blur map output	E: PAI	F: RRD	10: diff gain	11: luma gain	12: sel_diff <-- Remove(O24)	13: motion shift <-- Remove(O24)	14: motion gain <-- Remove(O24)	15: skin gain	16: face gain	17: face-skin gain	18: SCR blur map
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907E0 RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x0) //
	UINT32 reg_sel_blur_filter              :1;	//(1,RW,0x0) //0: O24 DWT blur map , 1: O22 blur map
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x0) //0: new_2x2, 1: new_3x3
	UINT32 reg_oai_en                       :1;	//(3,RW,0x0) //
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x0) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x0) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20, O22
	UINT32 resvd                            :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907E4 RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907E8 RW 0x0000_0000
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907EC RW 0x0000_0000
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907F0 RW 0x0000_0000
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907F4 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907F8 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2907FC RW 0x0000_0000
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290800 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290804 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290808 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29080C RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //
	UINT32 resvd3                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290810 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//(19:16,RW,0x0) //
	UINT32 reg_diff_shift                   :3;	//(22:20,RW,0x0) //
	UINT32 reg_osd_run_mode                 :1;	//(23,RW,0x0) //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//(24,RW,0x0) //not used in m16p3, O20, O22
	UINT32 reg_alpha_blur_mode              :2;	//(26:25,RW,0x0) //0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//(28:27,RW,0x0) //not used in m16p3, O20, O22
	UINT32 reg_diff_use_seldiff             :1;	//(29,RW,0x0) //
	UINT32 reg_diff_calc_mode               :2;	//(31:30,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290814 RW 0x0000_0000
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x0) //not used in m16p3, O20, O22
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x0) //not used in m16p3, O20, O22
	UINT32 resvd                            :4;
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290818 RW 0x0000_0000
	UINT32 reg_var_lowapl_v_cut             :2;	//(1:0,RW,0x0) //
	UINT32 reg_var_lowapl_h_cut             :2;	//(3:2,RW,0x0) //
	UINT32 reg_var_lowapl_t7_offset         :2;	//(5:4,RW,0x0) //
	UINT32 reg_var_lowapl_bit_opt           :1;	//(6,RW,0x0) //
	UINT32 reg_var_lowapl_chroma_en         :1;	//(7,RW,0x0) //
	UINT32 reg_var_lowapl_v_gain            :4;	//(11:8,RW,0x0) //
	UINT32 reg_var_lowapl_h_gain            :4;	//(15:12,RW,0x0) //
	UINT32 reg_var_lowapl_cut_resolution    :4;	//(19:16,RW,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29081C RW 0x0000_0000
	UINT32 reg_120x68_last_block_size_v     :6;	//(5:0,RW,0x0) //
	UINT32 reg_120x68_last_block_size_h     :6;	//(11:6,RW,0x0) //
	UINT32 reg_120x68_block_size_v          :6;	//(17:12,RW,0x0) //
	UINT32 reg_120x68_block_size_h          :6;	//(23:18,RW,0x0) //
	UINT32 reg_120x68_block_no_v            :7;	//(30:24,RW,0x0) //
	UINT32 resvd                            :1;
	};
}PE_O26_DNR0_REG_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290820 RW 0x0000_0000
	UINT32 resvd                            :20;
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x0) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x0) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290824 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290828 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29082C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290830 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290834 RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_120x68_block_no_h            :7;	//(30:24,RW,0x0) //
	UINT32 reg_120x68_block_info_force_en   :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290838 RW 0x0000_0000
	UINT32 reg_sdc_flat_var_h               :8;	//(7:0,RW,0x0) //
	UINT32 reg_sdc_flat_var_l               :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :15;
	UINT32 reg_sdc_gain_en                  :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29083C RW 0x0000_0000
	UINT32 reg_sdc_gain_x0                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_sdc_gain_x1                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_sdc_gain_x2                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_sdc_gain_x3                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290840 RW 0x0000_0000
	UINT32 reg_sdc_gain_y0                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_sdc_gain_y1                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_sdc_gain_y2                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_sdc_gain_y3                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290844 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290848 RW 0x0000_0000
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29084C RW 0x0000_0000
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290850 RW 0x0000_0000
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :3;
	UINT32 reg_intp_avg_en                  :1;	//(27,RW,0x0) //
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x0) //
	UINT32 reg_wgt_avg_en                   :1;	//(29,RW,0x0) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290854 RW 0x0000_0000
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR0_REG_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290858 RW 0x0000_0000
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29085C RW 0x0000_0000
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290860 RW 0x0000_0000
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290864 RW 0x0000_0000
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290868 RW 0x0000_0000
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29086C RW 0x0000_0000
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290870 RW 0x0000_0000
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290874 RW 0x0000_0000
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290878 RW 0x0000_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0x0) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29087C RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0_c          :8;	//(7:0,RW,0x0) //
	UINT32 reg_msp_outer_dist_x1_c          :8;	//(15:8,RW,0x0) //
	UINT32 reg_msp_outer_dist_x2_c          :8;	//(23:16,RW,0x0) //
	UINT32 reg_msp_outer_dist_x3_c          :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290880 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0_c          :8;	//(7:0,RW,0x0) //
	UINT32 reg_msp_outer_dist_y1_c          :8;	//(15:8,RW,0x0) //
	UINT32 reg_msp_outer_dist_y2_c          :8;	//(23:16,RW,0x0) //
	UINT32 reg_msp_outer_dist_y3_c          :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290884 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0_c          :8;	//(7:0,RW,0x0) //
	UINT32 reg_msp_inner_dist_x1_c          :8;	//(15:8,RW,0x0) //
	UINT32 reg_msp_inner_dist_x2_c          :8;	//(23:16,RW,0x0) //
	UINT32 reg_msp_inner_dist_x3_c          :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290888 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0_c          :8;	//(7:0,RW,0x0) //
	UINT32 reg_msp_inner_dist_y1_c          :8;	//(15:8,RW,0x0) //
	UINT32 reg_msp_inner_dist_y2_c          :8;	//(23:16,RW,0x0) //
	UINT32 reg_msp_inner_dist_y3_c          :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29088C RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_init_yy        :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290890 RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_init_cb        :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290894 RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_init_cr        :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290898 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29089C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DC_BNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908A8 RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_min_pel_cb     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l0_rd_min_pel_yy     :12;	//(23:12,NA,0x0) //
	UINT32 reg_bds_out_l0_rd_bit            :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_bds_out_l0_rd_out_clip       :1;	//(30,NA,0x0) //
	UINT32 reg_bds_out_l0_rd_on             :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908AC RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_max_pel_yy     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l0_rd_min_pel_cr     :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908B0 RW 0x0000_0000
	UINT32 reg_bds_out_l0_rd_max_pel_cr     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l0_rd_max_pel_cb     :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908B4 RW 0x0000_0000
	UINT32 reg_bds_out_l1_rd_init_yy        :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908B8 RW 0x0000_0000
	UINT32 reg_bds_out_1_rd_init_cb         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908BC RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_x2            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x1            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x0            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908C0 RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_y1            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y0            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x3            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908C4 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x0          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y3            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y2            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908C8 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x3          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x2          :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x1          :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908CC RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_y3          :8;	//(7:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y2          :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y1          :8;	//(23:16,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y0          :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908D0 RW 0x0000_0000
	UINT32 reg_lowapl_master_blend          :8;	//(7:0,RW,0x0) //
	UINT32 reg_2x2_var_msb_sel              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O26_DNR0_REG_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908D4 RW 0x0000_0000
	UINT32 reg_bds_out_l1_rd_init_cr        :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908D8 RW 0x0000_0000
	UINT32 reg_bds_out_l1_rd_min_pel_cb     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l1_rd_min_pel_yy     :12;	//(23:12,NA,0x0) //
	UINT32 reg_bds_out_l1_rd_bit            :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_bds_out_l1_rd_out_clip       :1;	//(30,NA,0x0) //
	UINT32 reg_bds_out_l1_rd_on             :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908DC RW 0x0000_0000
	UINT32 reg_bds_out_l1_rd_max_pel_yy     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l1_rd_min_pel_cr     :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908E0 RW 0x0000_0000
	UINT32 reg_bds_out_l1_rd_max_pel_cr     :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_out_l1_rd_max_pel_cb     :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908E4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908E8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908EC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR0_REG_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908F4 RW 0x0000_0000
	UINT32 tdata0                           :32;	//(31:0,NA,0x0) //RESERVED: F20, E60
	};
}PE_O26_DNR0_REG_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908F8 RW 0x0000_0000
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x0) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x0) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x0) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_O26_DNR0_REG_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2908FC RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_REG_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290900 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_REG_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290904 RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290908 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29090C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290910 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290914 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290918 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29091C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290920 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR0_REG_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290924 RW 0x0000_0000
	UINT32 reg_face_demo_x1                 :13;	//(12:0,NA,0x0) //x0 < pos_x < x1 ?? ??(2 ??? ?? ??)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//(28:16,NA,0x0) //x0 < pos_x < x1 ?? ??(2 ??? ?? ??)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//(31,NA,0x0) //face gain demo mode ??
	};
}PE_O26_DNR0_REG_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290928 RW 0x0000_0000
	UINT32 reg_face_demo_y1                 :13;	//(12:0,NA,0x0) //y0 < pos_y < y1 ?? ??
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//(28:16,NA,0x0) //y0 < pos_y < y1 ?? ??
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR0_REG_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29092C RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x3              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290930 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y3              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290934 RW 0x0000_0000
	UINT32 reg_ref_filter_x1                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_x2                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x3                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ref_mmd_sel                  :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290938 RW 0x0000_0000
	UINT32 reg_ref_filter_y2                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y3                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x0                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29093C RW 0x0000_0000
	UINT32 reg_ref_filter_y0                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y1                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_mmd_left_shift           :3;	//(22:20,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_mmd_right_shift              :2;	//(29:28,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290940 RW 0x0000_0000
	UINT32 reg_margin_bit                   :3;	//(2:0,NA,0x0) //
	UINT32 reg_rand_shift                   :3;	//(5:3,NA,0x0) //
	UINT32 resvd                            :25;
	UINT32 reg_blur_rand_en                 :1;	//(31,NA,0x0) //L6 interpolation ?? rand? ?? enable
	};
}PE_O26_DNR0_REG_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290944 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0_y          :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_x1_y          :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_x2_y          :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_x3_y          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290948 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0_y          :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_y1_y          :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_y2_y          :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_y3_y          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29094C RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0_y          :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_x1_y          :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_x2_y          :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_x3_y          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290950 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0_y          :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_y1_y          :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_y2_y          :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_y3_y          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290954 RW 0x0000_0000
	UINT32 reg_msp_rd_init_yy               :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290958 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cb               :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29095C RW 0x0000_0000
	UINT32 reg_msp_rd_init_cr               :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290960 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_x0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x3                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290964 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_y0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y3                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29097C RW 0x0000_0000
	UINT32 reg_l6_blur_luma_ratio           :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_luma_mode            :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_luma_th              :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_amean_filter_en              :1;	//(31,NA,0x0) //a-mean filter en
	};
}PE_O26_DNR0_REG_DECON_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290980 RW 0x0000_0000
	UINT32 reg_l6_blur_chroma_ratio         :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_chroma_mode          :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_chroma_th            :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290984 RW 0x0000_0000
	UINT32 reg_rd_blur_ratio_c              :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_ratio_y              :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :14;
	UINT32 reg_oai_repeat                   :1;	//(30,NA,0x0) //
	UINT32 reg_rd_blur_en                   :1;	//(31,NA,0x0) //O22 New : RRD enable
	};
}PE_O26_DNR0_REG_DECON_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290988 RW 0x0000_0000
	UINT32 reg_rd_blur_x0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_x1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_x2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_x3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29098C RW 0x0000_0000
	UINT32 reg_rd_blur_y0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_y1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_y2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_y3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290990 RW 0x1357_9753
	UINT32 reg_decon_rd_init_yy             :32;	//(31:0,NA,0x13579753) //Decon 1st RRD seed
	};
}PE_O26_DNR0_REG_DECON_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290994 RW 0x2468_0864
	UINT32 reg_decon_rd_init_cb             :32;	//(31:0,NA,0x24680864) //Decon 1st RRD seed
	};
}PE_O26_DNR0_REG_DECON_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290998 RW 0x1470_3692
	UINT32 reg_decon_rd_init_cr             :32;	//(31:0,NA,0x14703692) //Decon 1st RRD seed
	};
}PE_O26_DNR0_REG_DECON_CTRL_119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29099C RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_yy_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_yy_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv2_lut_yy_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 reg_bds_lv2_blur_sel             :2;	//(31:30,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_120_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909A0 RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_yy_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_yy_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv2_lut_yy_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_121_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909A4 RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_yy_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_yy_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :9;
	UINT32 reg_bds_lv2_dbg_pattern_protect  :1;	//(29,NA,0x0) //
	UINT32 reg_bds_lv2_band_force_0         :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv2_amf_th_force_0       :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_122_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909A8 RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_cc_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_cc_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv2_lut_cc_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_123_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909AC RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_cc_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_cc_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv2_lut_cc_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_124_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909B0 RW 0x0000_0000
	UINT32 reg_bds_lv2_lut_cc_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv2_lut_cc_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_125_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909B4 RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_init_yy     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909B8 RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_init_cb     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909BC RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_init_cr     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909C0 RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_min_pel_cb  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv2_decon_rd_min_pel_yy  :12;	//(23:12,NA,0x0) //
	UINT32 reg_bds_lv2_decon_rd_bit         :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_bds_lv2_decon_rd_out_clip    :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv2_decon_rd_on          :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909C4 RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_max_pel_yy  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv2_decon_rd_min_pel_cr  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909C8 RW 0x0000_0000
	UINT32 reg_bds_lv2_decon_rd_max_pel_cr  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv2_decon_rd_max_pel_cb  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909CC RW 0x0000_0000
	UINT32 reg_bds_lv2_pattern_coner_th     :10;	//(9:0,NA,0x0) //
	UINT32 resvd                            :21;
	UINT32 reg_bds_lv2_pattern_blend_en     :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909D0 RW 0x0000_0000
	UINT32 reg_bds_lv2_pattern_blend_x3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_x2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_x1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_x0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909D4 RW 0x0000_0000
	UINT32 reg_bds_lv2_pattern_blend_y3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_y2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_y1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv2_pattern_blend_y0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909D8 RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_yy_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_yy_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv1_lut_yy_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 reg_bds_lv1_blur_sel             :2;	//(31:30,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909DC RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_yy_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_yy_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv1_lut_yy_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909E0 RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_yy_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_yy_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :9;
	UINT32 reg_bds_lv1_dbg_pattern_protect  :1;	//(29,NA,0x0) //
	UINT32 reg_bds_lv1_band_force_0         :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv1_amf_th_force_0       :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_137_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909E4 RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_cc_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_cc_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv1_lut_cc_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_138_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909E8 RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_cc_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_cc_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv1_lut_cc_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_139_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909EC RW 0x0000_0000
	UINT32 reg_bds_lv1_lut_cc_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv1_lut_cc_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_140_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909F0 RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_init_yy     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_141_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909F4 RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_init_cb     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_142_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909F8 RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_init_cr     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_143_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2909FC RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_min_pel_cb  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv1_decon_rd_min_pel_yy  :12;	//(23:12,NA,0x0) //
	UINT32 reg_bds_lv1_decon_rd_bit         :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_bds_lv1_decon_rd_out_clip    :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv1_decon_rd_on          :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_144_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A00 RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_max_pel_yy  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv1_decon_rd_min_pel_cr  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_145_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A04 RW 0x0000_0000
	UINT32 reg_bds_lv1_decon_rd_max_pel_cr  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv1_decon_rd_max_pel_cb  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_146_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A08 RW 0x0000_0000
	UINT32 reg_bds_lv1_pattern_coner_th     :10;	//(9:0,NA,0x0) //
	UINT32 resvd                            :21;
	UINT32 reg_bds_lv1_pattern_blend_en     :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_147_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A0C RW 0x0000_0000
	UINT32 reg_bds_lv1_pattern_blend_x3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_x2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_x1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_x0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_148_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A10 RW 0x0000_0000
	UINT32 reg_bds_lv1_pattern_blend_y3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_y2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_y1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv1_pattern_blend_y0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_149_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A14 RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_yy_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_yy_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv0_lut_yy_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 reg_bds_lv0_blur_sel             :2;	//(31:30,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_150_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A18 RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_yy_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_yy_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv0_lut_yy_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_151_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A1C RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_yy_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_yy_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :9;
	UINT32 reg_bds_lv0_dbg_pattern_protect  :1;	//(29,NA,0x0) //
	UINT32 reg_bds_lv0_band_force_0         :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv0_amf_th_force_0       :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_152_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A20 RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_cc_th_x2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_cc_th_x1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv0_lut_cc_th_x0         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_153_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A24 RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_cc_th_y1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_cc_th_y0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_bds_lv0_lut_cc_th_x3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR0_REG_DECON_CTRL_154_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A28 RW 0x0000_0000
	UINT32 reg_bds_lv0_lut_cc_th_y3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_bds_lv0_lut_cc_th_y2         :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR0_REG_DECON_CTRL_155_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A2C RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_init_yy     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_156_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A30 RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_init_cb     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_157_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A34 RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_init_cr     :32;	//(31:0,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_158_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A38 RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_min_pel_cb  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv0_decon_rd_min_pel_yy  :12;	//(23:12,NA,0x0) //
	UINT32 reg_bds_lv0_decon_rd_bit         :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_bds_lv0_decon_rd_out_clip    :1;	//(30,NA,0x0) //
	UINT32 reg_bds_lv0_decon_rd_on          :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_159_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A3C RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_max_pel_yy  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv0_decon_rd_min_pel_cr  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_160_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A40 RW 0x0000_0000
	UINT32 reg_bds_lv0_decon_rd_max_pel_cr  :12;	//(11:0,NA,0x0) //
	UINT32 reg_bds_lv0_decon_rd_max_pel_cb  :12;	//(23:12,NA,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR0_REG_DECON_CTRL_161_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A44 RW 0x0000_0000
	UINT32 reg_bds_lv0_pattern_coner_th     :10;	//(9:0,NA,0x0) //
	UINT32 resvd                            :21;
	UINT32 reg_bds_lv0_pattern_blend_en     :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_162_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A48 RW 0x0000_0000
	UINT32 reg_bds_lv0_pattern_blend_x3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_x2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_x1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_x0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_163_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A4C RW 0x0000_0000
	UINT32 reg_bds_lv0_pattern_blend_y3     :8;	//(7:0,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_y2     :8;	//(15:8,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_y1     :8;	//(23:16,NA,0x0) //
	UINT32 reg_bds_lv0_pattern_blend_y0     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_164_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A50 RW 0x0000_0000
	UINT32 resvd0                           :25;
	UINT32 reg_dbg_b2g_mode                 :2;	//(26:25,NA,0x0) //
	UINT32 reg_dbg_b2g_en                   :1;	//(27,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_pattern_blend_en             :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_165_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A54 RW 0x0000_0000
	UINT32 reg_b2g_luma_gain_x0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_b2g_luma_gain_x1             :8;	//(15:8,NA,0x0) //
	UINT32 reg_b2g_luma_gain_x2             :8;	//(23:16,NA,0x0) //
	UINT32 reg_b2g_luma_gain_x3             :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_166_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A58 RW 0x0000_0000
	UINT32 reg_b2g_luma_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_b2g_luma_gain_y1             :8;	//(15:8,NA,0x0) //
	UINT32 reg_b2g_luma_gain_y2             :8;	//(23:16,NA,0x0) //
	UINT32 reg_b2g_luma_gain_y3             :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_167_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A5C RW 0x0000_0000
	UINT32 reg_b2g_chroma_gain_x0           :8;	//(7:0,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_x1           :8;	//(15:8,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_x2           :8;	//(23:16,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_x3           :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_168_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A60 RW 0x0000_0000
	UINT32 reg_b2g_chroma_gain_y0           :8;	//(7:0,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_y1           :8;	//(15:8,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_y2           :8;	//(23:16,NA,0x0) //
	UINT32 reg_b2g_chroma_gain_y3           :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_169_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A64 RW 0x0000_0000
	UINT32 reg_lhmgs_y_th                   :10;	//(9:0,NA,0x0) //
	UINT32 reg_lhmgs_mmd_cut                :8;	//(17:10,NA,0x0) //
	UINT32 reg_ddp_mmd_scale                :8;	//(25:18,NA,0x0) //
	UINT32 reg_dbg_ddp_mode                 :3;	//(28:26,NA,0x0) //0: luma intp.	1: IIR intp.	2: final lhmgs score	3: mmd intp.	4: vfp gain	5: ddp alpha
	UINT32 reg_dbg_ddp_en                   :1;	//(29,NA,0x0) //
	UINT32 reg_ddp_iir_en                   :1;	//(30,NA,0x0) //
	UINT32 reg_ddp_acc_mmd_sel              :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_170_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A68 RW 0x0000_0000
	UINT32 reg_decon_ddp_iir_x_th3          :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_iir_x_th2          :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_iir_x_th1          :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_iir_x_th0          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_171_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A6C RW 0x0000_0000
	UINT32 reg_decon_ddp_iir_y_th3          :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_iir_y_th2          :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_iir_y_th1          :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_iir_y_th0          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_172_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A70 RW 0x0000_0000
	UINT32 reg_blend_yy_ratio               :8;	//(7:0,NA,0x0) //
	UINT32 reg_hmgs_iir_stp_dwn             :8;	//(15:8,NA,0x0) //
	UINT32 reg_hmgs_iir_stp_upp             :8;	//(23:16,NA,0x0) //
	UINT32 resvd                            :7;
	UINT32 reg_hmgs_iir_stp_protect         :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_173_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A74 RW 0x0000_0000
	UINT32 reg_decon_ddp_weight_y_th3       :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_weight_y_th2       :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_weight_y_th1       :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_weight_y_th0       :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_174_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A78 RW 0x0000_0000
	UINT32 reg_decon_ddp_weight_x_th3       :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_weight_x_th2       :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_weight_x_th1       :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_weight_x_th0       :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_175_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A7C RW 0x0000_0000
	UINT32 reg_decon_ddp_lhmgs_gain_y_th3   :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_y_th2   :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_y_th1   :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_y_th0   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_176_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A80 RW 0x0000_0000
	UINT32 reg_decon_ddp_lhmgs_gain_x_th3   :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_x_th2   :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_x_th1   :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_lhmgs_gain_x_th0   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_177_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A84 RW 0x0000_0000
	UINT32 reg_vfp_luma_mode                :2;	//(1:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_vfp_mmd_th                   :10;	//(13:4,NA,0x0) //
	UINT32 resvd1                           :16;
	UINT32 reg_vfp_en                       :1;	//(30,NA,0x0) //
	UINT32 reg_ddp_preserve_en              :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_178_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A88 RW 0x0000_0000
	UINT32 reg_decon_ddp_vfp_y_th3          :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_y_th2          :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_y_th1          :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_y_th0          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_179_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A8C RW 0x0000_0000
	UINT32 reg_decon_ddp_vfp_x_th3          :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_x_th2          :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_x_th1          :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_vfp_x_th0          :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_180_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A90 RW 0x0000_0000
	UINT32 reg_decon_ddp_luma_blend_y_th3   :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_y_th2   :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_y_th1   :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_y_th0   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_181_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A94 RW 0x0000_0000
	UINT32 reg_decon_ddp_luma_blend_x_th3   :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_x_th2   :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_x_th1   :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_ddp_luma_blend_x_th0   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR0_REG_DECON_CTRL_182_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A98 RW 0x0000_003C
	UINT32 reg_eotf_en                      :1;	//(0,RW,0x0) //note : apl_eotf lut wr/rd controled by led_hif(0x780~0x788)
	UINT32 resvd0                           :3;
	UINT32 reg_eotf_rdata_sel               :1;	//(4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_bit_extension_mode      :2;	//(9:8,RW,0x0) //
	UINT32 resvd2                           :22;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290A9C RW 0x0000_0000
	UINT32 reg_curr_peak_level              :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_wg_ratio                     :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AA0 RW 0x0000_0010
	UINT32 reg_apl_filt_init                :1;	//(0,RW,0x0) //note : set '1' at least 1 frame
	UINT32 resvd0                           :3;
	UINT32 reg_apl_filt_mode                :1;	//(4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_apl_filt_window_size         :3;	//(10:8,RW,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_apl_iir_gain                 :8;	//(23:16,RW,0x0) //
	UINT32 resvd3                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AA4 RW 0x0000_0180
	UINT32 reg_s_apl_val                    :8;	//(7:0,RW,0x80) //
	UINT32 reg_s_apl_val_mux                :1;	//(8,RW,0x1) //0:manual 1: S_APL
	UINT32 resvd                            :23;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AA8 RW 0x0000_0000
	UINT32 reg_s_apl_alpha_lut_y00          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x00          :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AAC RW 0x0024_0000
	UINT32 reg_s_apl_alpha_lut_y01          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x01          :8;	//(23:16,RW,0x24) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AB0 RW 0x0048_0000
	UINT32 reg_s_apl_alpha_lut_y02          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x02          :8;	//(23:16,RW,0x48) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AB4 RW 0x006C_0000
	UINT32 reg_s_apl_alpha_lut_y03          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x03          :8;	//(23:16,RW,0x6c) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AB8 RW 0x0090_00FF
	UINT32 reg_s_apl_alpha_lut_y04          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x04          :8;	//(23:16,RW,0x90) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290ABC RW 0x00B4_00FF
	UINT32 reg_s_apl_alpha_lut_y05          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x05          :8;	//(23:16,RW,0xB4) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AC0 RW 0x00D8_00FF
	UINT32 reg_s_apl_alpha_lut_y06          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x06          :8;	//(23:16,RW,0xD8) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AC4 RW 0x00FF_00FF
	UINT32 reg_s_apl_alpha_lut_y07          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x07          :8;	//(23:16,RW,0xFF) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AC8 RW 0x0596_00C8
	UINT32 reg_oapl_offset_phdr             :12;	//(11:0,RW,0x00C8) //
	UINT32 resvd0                           :4;
	UINT32 reg_oapl_offset_tcon             :12;	//(27:16,RW,0x0596) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290ACC RW 0x0000_0001
	UINT32 reg_oapl_rgb2yc_en               :1;	//(0,RW,0x1) //
	UINT32 resvd                            :31;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AD0 RW 0x094A_00D0
	UINT32 reg_oapl_rgb2yc_coef1            :15;	//(14:0,RW,0x00D0) //
	UINT32 resvd0                           :1;
	UINT32 reg_oapl_rgb2yc_coef0            :15;	//(30:16,RW,0x094A) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AD4 RW 0x0399_0000
	UINT32 resvd0                           :16;
	UINT32 reg_oapl_rgb2yc_coef2            :15;	//(30:16,RW,0x0399) //
	UINT32 resvd1                           :1;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AD8 RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst0            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290ADC RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst3            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AF0 RW 0x0000_0000
	UINT32 reg_hsv_hsl_sel                  :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sat_en                       :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :27;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AF4 RW 0x0080_0080
	UINT32 reg_ihsv_sgain                   :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_vgain                   :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AF8 RW 0x0080_0080
	UINT32 reg_ihsv_soffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_hoffset                 :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290AFC RW 0x0000_0080
	UINT32 reg_ihsv_voffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}PE_O26_DNR0_REG_OAPL_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B00 RW 0x0000_0000
	UINT32 reg_forcing_decon_only           :1;	//(0,RW,0x0) //forcing dec result to DEC-SMR blender output
	UINT32 resvd0                           :7;
	UINT32 reg_smr_dbg_mode                 :3;	//(10:8,RW,0x0) //smr debug mode	3'd0 : mmd_local_evn       	3'd1 : mmd_large_evn       	3'd2 : flat_feature_evn    	3'd3 : diff_score_evn      	3'd4 : divider_evn         	3'd5 : pre_blur_th_evn     	else : smr_blend_alpha_evn
	UINT32 resvd1                           :1;
	UINT32 reg_smr_dbg_en                   :1;	//(12,RW,0x0) //smr debug mode enable
	UINT32 resvd2                           :3;
	UINT32 reg_mmd_v_shrink_step            :2;	//(17:16,RW,0x0) //v axis shrink step size	large MMD range	2'h0 : 17	2'h1 : 15	2'h2 : 13	2'h3 : 11
	UINT32 resvd3                           :2;
	UINT32 reg_mmd_h_shrink_step            :2;	//(21:20,RW,0x0) //h axis shrink step size	large MMD range	2'h0 : 17	2'h1 : 15	2'h2 : 13	2'h3 : 11
	UINT32 resvd4                           :2;
	UINT32 reg_smr_master_en_cc             :1;	//(24,RW,0x0) //CbCr channel SMR 	 1'b1 : active, 1'b0 : bypas
	UINT32 resvd5                           :3;
	UINT32 reg_smr_master_en_yy             :1;	//(28,RW,0x0) //Y channel SMR 	 1'b1 : active, 1'b0 : bypas
	UINT32 resvd6                           :3;
	};
}PE_O26_DNR0_REG_SMR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B04 RW 0xffff_0005
	UINT32 reg_flat_th                      :8;	//(7:0,RW,0x05) //threshold for 3x3MMD to flat score
	UINT32 resvd                            :8;
	UINT32 reg_smr_master_gain_cc           :8;	//(23:16,RW,0xff) //gain for cbcr channel, weigh blending ratio gain for blured cb,cr and original cb,cr
	UINT32 reg_smr_master_gain_yy           :8;	//(31:24,RW,0xff) //gain for yy channel,  weigh blending ratio gain for blured yy and original yy
	};
}PE_O26_DNR0_REG_SMR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B08 RW 0x0008_0080
	UINT32 reg_flat_scale                   :9;	//(8:0,RW,0x80) //MMD-FLAT, Flat socre scale	Flat_remap = Flat_sclae*(Flat_feature - Flat_offset)
	UINT32 resvd0                           :3;
	UINT32 reg_flat_offset                  :9;	//(20:12,RW,0x80) //MMD-FLAT, Flat score offset 	Flat_feature- Flat_offset
	UINT32 resvd1                           :7;
	UINT32 reg_flat_remap_en                :1;	//(28,RW,0x0) //MMD-FLAT_SC, select flat feature	1'b0 : out <= Flat_feature	1'b1 : out <= Flat_remap
	UINT32 resvd2                           :3;
	};
}PE_O26_DNR0_REG_SMR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B0C RW 0x0180_0000
	UINT32 reg_blur_blend_ratio_cc          :8;	//(7:0,RW,0x00) //blending ratio for CbCr channel
	UINT32 reg_blur_blend_ratio_yy          :8;	//(15:8,RW,0x00) //blending ratio for Y channel
	UINT32 reg_mmd_val_div_by_zero          :8;	//(23:16,RW,0x80) //module divider output if Large MMD==0
	UINT32 reg_lut_input_mode               :1;	//(24,RW,0x1) //DEC-SMR blender LUT input mode	1'b0 : diff_delta_mag	1'b1 : diff_delta_ratio
	UINT32 resvd0                           :3;
	UINT32 reg_mmd_div_mode                 :1;	//(28,RW,0x0) //divider mode select	1'b1 : reg_div_mmd = 256* local_mmd? large_mmd	1'b0 : reg_div_mmd =  256*( local_mmd+1)?( large_mmd+1)
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR0_REG_SMR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B10 RW 0x2040_70a0
	UINT32 reg_mmd_remap_x3                 :8;	//(7:0,RW,0xa0) //4th point
	UINT32 reg_mmd_remap_x2                 :8;	//(15:8,RW,0x70) //3rd point
	UINT32 reg_mmd_remap_x1                 :8;	//(23:16,RW,0x40) //2nd point
	UINT32 reg_mmd_remap_x0                 :8;	//(31:24,RW,0x20) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B14 RW 0xffc0_2000
	UINT32 reg_mmd_remap_y3                 :8;	//(7:0,RW,0x00) //4th point
	UINT32 reg_mmd_remap_y2                 :8;	//(15:8,RW,0x20) //3rd point
	UINT32 reg_mmd_remap_y1                 :8;	//(23:16,RW,0xc0) //2nd point
	UINT32 reg_mmd_remap_y0                 :8;	//(31:24,RW,0xff) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B18 RW 0x263a_b2c6
	UINT32 reg_other_gain_yy_x3             :8;	//(7:0,RW,0xc6) //4th point
	UINT32 reg_other_gain_yy_x2             :8;	//(15:8,RW,0xb2) //3rd point
	UINT32 reg_other_gain_yy_x1             :8;	//(23:16,RW,0x3a) //2nd point
	UINT32 reg_other_gain_yy_x0             :8;	//(31:24,RW,0x26) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B1C RW 0x3044_6c8a
	UINT32 reg_other_gain_cb_x3             :8;	//(7:0,RW,0x8a) //4th point
	UINT32 reg_other_gain_cb_x2             :8;	//(15:8,RW,0x6c) //3rd point
	UINT32 reg_other_gain_cb_x1             :8;	//(23:16,RW,0x44) //2nd point
	UINT32 reg_other_gain_cb_x0             :8;	//(31:24,RW,0x30) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B20 RW 0x535d_8f99
	UINT32 reg_other_gain_cr_x3             :8;	//(7:0,RW,0x99) //4th point
	UINT32 reg_other_gain_cr_x2             :8;	//(15:8,RW,0x8f) //3rd point
	UINT32 reg_other_gain_cr_x1             :8;	//(23:16,RW,0x5d) //2nd point
	UINT32 reg_other_gain_cr_x0             :8;	//(31:24,RW,0x53) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B24 RW 0x1000_4032
	UINT32 reg_difference_sft               :3;	//(2:0,RW,0x2) //DIFF_SC, difference score shift(>>) value
	UINT32 resvd0                           :1;
	UINT32 reg_diff_step_mode               :2;	//(5:4,RW,0x3) //DIFF_SC, difference score step mode	Step size of pixel to be referred to for calculation of differnce score based on cc (8 directions in total)	1'b3 : step size=8	1'b2 : step size=6	1'b1 : step size=4	1'b0 : step size=2
	UINT32 resvd1                           :2;
	UINT32 reg_target_color_gain            :8;	//(15:8,RW,0x40) //YCbCr gain
	UINT32 resvd2                           :12;
	UINT32 reg_color_gain_en                :1;	//(28,RW,0x01) //color gain active 	1'b1 : CRG output <= div_remap_val * color_gain_val_clip	1'b0 : CRG output <= div_remap_val
	UINT32 resvd3                           :3;
	};
}PE_O26_DNR0_REG_SMR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B28 NA 0x0004_0820
	UINT32 reg_diff_remap_x3                :8;	//(7:0,RW,0x20) //4th point
	UINT32 reg_diff_remap_x2                :8;	//(15:8,RW,0x08) //3rd point
	UINT32 reg_diff_remap_x1                :8;	//(23:16,RW,0x04) //2nd point
	UINT32 reg_diff_remap_x0                :8;	//(31:24,RW,0x00) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B2C NA 0x2008_0400
	UINT32 reg_diff_remap_y3                :8;	//(7:0,RW,0x00) //4th point
	UINT32 reg_diff_remap_y2                :8;	//(15:8,RW,0x04) //3rd point
	UINT32 reg_diff_remap_y1                :8;	//(23:16,RW,0x08) //2nd point
	UINT32 reg_diff_remap_y0                :8;	//(31:24,RW,0x20) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B30 NA 0x0020_3040
	UINT32 reg_mmd_blur_x3                  :8;	//(7:0,RW,0x40) //4th point
	UINT32 reg_mmd_blur_x2                  :8;	//(15:8,RW,0x30) //3rd point
	UINT32 reg_mmd_blur_x1                  :8;	//(23:16,RW,0x20) //2nd point
	UINT32 reg_mmd_blur_x0                  :8;	//(31:24,RW,0x00) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B34 NA 0x6080_0000
	UINT32 reg_mmd_blur_y1                  :8;	//(7:0,RW,0x00) //2nd point
	UINT32 reg_mmd_blur_y0                  :8;	//(15:8,RW,0x00) //1st point
	UINT32 reg_mmd_blur_x5                  :8;	//(23:16,RW,0x80) //6nd point
	UINT32 reg_mmd_blur_x4                  :8;	//(31:24,RW,0x60) //5st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B38 NA 0x040a_3660
	UINT32 reg_mmd_blur_y5                  :8;	//(7:0,RW,0x60) //6nd point
	UINT32 reg_mmd_blur_y4                  :8;	//(15:8,RW,0x36) //5st point
	UINT32 reg_mmd_blur_y3                  :8;	//(23:16,RW,0x0a) //4th point
	UINT32 reg_mmd_blur_y2                  :8;	//(31:24,RW,0x04) //3rd point
	};
}PE_O26_DNR0_REG_SMR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B3C NA 0x0020_60a0
	UINT32 reg_blur_gain_by_flat_x3         :8;	//(7:0,RW,0xa0) //4th point
	UINT32 reg_blur_gain_by_flat_x2         :8;	//(15:8,RW,0x60) //3rd point
	UINT32 reg_blur_gain_by_flat_x1         :8;	//(23:16,RW,0x20) //2nd point
	UINT32 reg_blur_gain_by_flat_x0         :8;	//(31:24,RW,0x00) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B40 NA 0x1020_5080
	UINT32 reg_blur_gain_by_flat_y3         :8;	//(7:0,RW,0x80) //4th point
	UINT32 reg_blur_gain_by_flat_y2         :8;	//(15:8,RW,0x50) //3rd point
	UINT32 reg_blur_gain_by_flat_y1         :8;	//(23:16,RW,0x20) //2nd point
	UINT32 reg_blur_gain_by_flat_y0         :8;	//(31:24,RW,0x10) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B44 NA 0x181e_3c60
	UINT32 reg_blur_gain_by_diff_x3         :8;	//(7:0,RW,0x60) //4th point
	UINT32 reg_blur_gain_by_diff_x2         :8;	//(15:8,RW,0x3c) //3rd point
	UINT32 reg_blur_gain_by_diff_x1         :8;	//(23:16,RW,0x1e) //2nd point
	UINT32 reg_blur_gain_by_diff_x0         :8;	//(31:24,RW,0x18) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B48 NA 0xb0ff_ff80
	UINT32 reg_blur_gain_by_diff_y1         :8;	//(7:0,RW,0x80) //2nd point
	UINT32 reg_blur_gain_by_diff_y0         :8;	//(15:8,RW,0xff) //1st point
	UINT32 reg_blur_gain_by_diff_x5         :8;	//(23:16,RW,0xff) //6nd point
	UINT32 reg_blur_gain_by_diff_x4         :8;	//(31:24,RW,0xb0) //5st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B4C NA 0x60a0_c0ff
	UINT32 reg_blur_gain_by_diff_y5         :8;	//(7:0,RW,0xff) //6nd point
	UINT32 reg_blur_gain_by_diff_y4         :8;	//(15:8,RW,0xc0) //5st point
	UINT32 reg_blur_gain_by_diff_y3         :8;	//(23:16,RW,0xa0) //4th point
	UINT32 reg_blur_gain_by_diff_y2         :8;	//(31:24,RW,0x60) //3rd point
	};
}PE_O26_DNR0_REG_SMR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B50 NA 0x0020_4080
	UINT32 reg_bld_dec_remap_x3             :8;	//(7:0,RW,0x80) //4th point
	UINT32 reg_bld_dec_remap_x2             :8;	//(15:8,RW,0x40) //3rd point
	UINT32 reg_bld_dec_remap_x1             :8;	//(23:16,RW,0x20) //2nd point
	UINT32 reg_bld_dec_remap_x0             :8;	//(31:24,RW,0x00) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B54 NA 0x8040_1000
	UINT32 reg_bld_dec_remap_y3             :8;	//(7:0,RW,0x00) //4th point
	UINT32 reg_bld_dec_remap_y2             :8;	//(15:8,RW,0x10) //3rd point
	UINT32 reg_bld_dec_remap_y1             :8;	//(23:16,RW,0x40) //2nd point
	UINT32 reg_bld_dec_remap_y0             :8;	//(31:24,RW,0x80) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B58 NA 0x0020_4080
	UINT32 reg_bld_smr_remap_x3             :8;	//(7:0,RW,0x80) //4th point
	UINT32 reg_bld_smr_remap_x2             :8;	//(15:8,RW,0x40) //3rd point
	UINT32 reg_bld_smr_remap_x1             :8;	//(23:16,RW,0x20) //2nd point
	UINT32 reg_bld_smr_remap_x0             :8;	//(31:24,RW,0x00) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC290B5C NA 0x80c0_ffff
	UINT32 reg_bld_smr_remap_y3             :8;	//(7:0,RW,0xff) //4th point
	UINT32 reg_bld_smr_remap_y2             :8;	//(15:8,RW,0xff) //3rd point
	UINT32 reg_bld_smr_remap_y1             :8;	//(23:16,RW,0xc0) //2nd point
	UINT32 reg_bld_smr_remap_y0             :8;	//(31:24,RW,0x80) //1st point
	};
}PE_O26_DNR0_REG_SMR_CTRL_23_T;

typedef struct {
	PE_O26_DNR0_PE0_LOAD_T                                        pe0_load;	//0xCC290500
	PE_O26_DNR0_PE0_INTR_T                                        pe0_intr;	//0xCC290504
	PE_O26_DNR0_PE0_STATUS0_T                                  pe0_status0;	//0xCC290508
	PE_O26_DNR0_PE0_STATUS1_T                                  pe0_status1;	//0xCC29050C
	PE_O26_DNR0_PE0_OPMODE_T                                    pe0_opmode;	//0xCC290510
	PE_O26_DNR0_PE0_IN_SIZE_T                                  pe0_in_size;	//0xCC290514
	PE_O26_DNR0_PE0_IN_OFFSET_T                              pe0_in_offset;	//0xCC290518
	PE_O26_DNR0_PE0_OUT_SIZE_T                                pe0_out_size;	//0xCC29051C
	PE_O26_DNR0_WIN_CTRL_0_T                                    win_ctrl_0;	//0xCC290520
	PE_O26_DNR0_WIN_CTRL_1_T                                    win_ctrl_1;	//0xCC290524
	PE_O26_DNR0_WIN_CTRL_2_T                                    win_ctrl_2;	//0xCC290528
	PE_O26_DNR0_WIN_CTRL_3_T                                    win_ctrl_3;	//0xCC29052C
	PE_O26_DNR0_CUP_CTRL_00_T                                  cup_ctrl_00;	//0xCC290530
	PE_O26_DNR0_CUP_CTRL_01_T                                  cup_ctrl_01;	//0xCC290534
	PE_O26_DNR0_CUP_CTRL_02_T                                  cup_ctrl_02;	//0xCC290538
	UINT32                                                       reserved0;	//0xCC29053C
	UINT32                                                       reserved1;	//0xCC290540
	UINT32                                                       reserved2;	//0xCC290544
	UINT32                                                       reserved3;	//0xCC290548
	UINT32                                                       reserved4;	//0xCC29054C
	UINT32                                                       reserved5;	//0xCC290550
	UINT32                                                       reserved6;	//0xCC290554
	UINT32                                                       reserved7;	//0xCC290558
	UINT32                                                       reserved8;	//0xCC29055C
	UINT32                                                       reserved9;	//0xCC290560
	UINT32                                                      reserved10;	//0xCC290564
	UINT32                                                      reserved11;	//0xCC290568
	UINT32                                                      reserved12;	//0xCC29056C
	UINT32                                                      reserved13;	//0xCC290570
	UINT32                                                      reserved14;	//0xCC290574
	UINT32                                                      reserved15;	//0xCC290578
	UINT32                                                      reserved16;	//0xCC29057C
	PE_O26_DNR0_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0xCC290580
	PE_O26_DNR0_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0xCC290584
	PE_O26_DNR0_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0xCC290588
	PE_O26_DNR0_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xCC29058C
	PE_O26_DNR0_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xCC290590
	PE_O26_DNR0_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCC290594
	PE_O26_DNR0_DNR_DBAR_CTRL_T                              dnr_dbar_ctrl;	//0xCC290598
	PE_O26_DNR0_REG_C420_CTRL_T                              reg_c420_ctrl;	//0xCC29059C
	PE_O26_DNR0_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCC2905A0
	PE_O26_DNR0_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCC2905A4
	PE_O26_DNR0_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCC2905A8
	PE_O26_DNR0_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCC2905AC
	PE_O26_DNR0_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCC2905B0
	PE_O26_DNR0_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCC2905B4
	PE_O26_DNR0_DETAIL_CTRL_T                                  detail_ctrl;	//0xCC2905B8
	PE_O26_DNR0_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCC2905BC
	PE_O26_DNR0_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCC2905C0
	PE_O26_DNR0_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCC2905C4
	PE_O26_DNR0_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCC2905C8
	PE_O26_DNR0_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCC2905CC
	PE_O26_DNR0_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCC2905D0
	PE_O26_DNR0_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCC2905D4
	PE_O26_DNR0_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCC2905D8
	PE_O26_DNR0_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCC2905DC
	PE_O26_DNR0_DNR_STAT_0_T                                    dnr_stat_0;	//0xCC2905E0
	PE_O26_DNR0_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCC2905E4
	PE_O26_DNR0_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCC2905E8
	PE_O26_DNR0_DNR_STAT_1_T                                    dnr_stat_1;	//0xCC2905EC
	PE_O26_DNR0_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCC2905F0
	PE_O26_DNR0_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCC2905F4
	PE_O26_DNR0_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCC2905F8
	PE_O26_DNR0_DNR_STAT_2_T                                    dnr_stat_2;	//0xCC2905FC
	PE_O26_DNR0_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCC290600
	PE_O26_DNR0_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCC290604
	PE_O26_DNR0_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCC290608
	PE_O26_DNR0_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCC29060C
	PE_O26_DNR0_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCC290610
	PE_O26_DNR0_IFC_CTRL_0_T                                    ifc_ctrl_0;	//0xCC290614
	PE_O26_DNR0_IFC_CTRL_1_T                                    ifc_ctrl_1;	//0xCC290618
	PE_O26_DNR0_IFC_CTRL_2_T                                    ifc_ctrl_2;	//0xCC29061C
	PE_O26_DNR0_IFC_CTRL_3_T                                    ifc_ctrl_3;	//0xCC290620
	PE_O26_DNR0_IFC_CTRL_4_T                                    ifc_ctrl_4;	//0xCC290624
	PE_O26_DNR0_IFC_CTRL_5_T                                    ifc_ctrl_5;	//0xCC290628
	PE_O26_DNR0_DNR_SMG_CTRL_0_T                            dnr_smg_ctrl_0;	//0xCC29062C
	PE_O26_DNR0_DNR_SMG_CTRL_1_T                            dnr_smg_ctrl_1;	//0xCC290630
	PE_O26_DNR0_IFC_CTRL_8_T                                    ifc_ctrl_8;	//0xCC290634
	PE_O26_DNR0_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCC290638
	PE_O26_DNR0_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCC29063C
	PE_O26_DNR0_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCC290640
	PE_O26_DNR0_IFC_CTRL_12_T                                  ifc_ctrl_12;	//0xCC290644
	PE_O26_DNR0_DNR_SMG_CTRL_2_T                            dnr_smg_ctrl_2;	//0xCC290648
	PE_O26_DNR0_DEC_SMG_CTRL_0_T                            dec_smg_ctrl_0;	//0xCC29064C
	PE_O26_DNR0_IFC_CTRL_15_T                                  ifc_ctrl_15;	//0xCC290650
	PE_O26_DNR0_IFC_CTRL_16_T                                  ifc_ctrl_16;	//0xCC290654
	PE_O26_DNR0_IFC_CTRL_17_T                                  ifc_ctrl_17;	//0xCC290658
	PE_O26_DNR0_DEC_SMG_CTRL_1_T                            dec_smg_ctrl_1;	//0xCC29065C
	PE_O26_DNR0_IFC_CTRL_19_T                                  ifc_ctrl_19;	//0xCC290660
	PE_O26_DNR0_DEC_SMG_CTRL_2_T                            dec_smg_ctrl_2;	//0xCC290664
	PE_O26_DNR0_IFC_CTRL_21_T                                  ifc_ctrl_21;	//0xCC290668
	PE_O26_DNR0_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCC29066C
	PE_O26_DNR0_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCC290670
	PE_O26_DNR0_DEC_LOWAPL_0_T                                dec_lowapl_0;	//0xCC290674
	PE_O26_DNR0_DEC_LOWAPL_1_T                                dec_lowapl_1;	//0xCC290678
	PE_O26_DNR0_DEC_LOWAPL_2_T                                dec_lowapl_2;	//0xCC29067C
	PE_O26_DNR0_DEC_LOWAPL_3_T                                dec_lowapl_3;	//0xCC290680
	PE_O26_DNR0_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCC290684
	PE_O26_DNR0_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCC290688
	PE_O26_DNR0_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCC29068C
	PE_O26_DNR0_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCC290690
	PE_O26_DNR0_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCC290694
	PE_O26_DNR0_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCC290698
	PE_O26_DNR0_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCC29069C
	PE_O26_DNR0_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCC2906A0
	PE_O26_DNR0_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCC2906A4
	PE_O26_DNR0_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCC2906A8
	PE_O26_DNR0_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCC2906AC
	PE_O26_DNR0_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCC2906B0
	PE_O26_DNR0_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCC2906B4
	PE_O26_DNR0_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCC2906B8
	PE_O26_DNR0_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCC2906BC
	PE_O26_DNR0_TPD_CTRL_0_T                                    tpd_ctrl_0;	//0xCC2906C0
	PE_O26_DNR0_WINDOW_MODE_0_T                              window_mode_0;	//0xCC2906C4
	PE_O26_DNR0_WINDOW_MODE_1_T                              window_mode_1;	//0xCC2906C8
	UINT32                                                      reserved17;	//0xCC2906CC
	PE_O26_DNR0_DNR_STAT_3_T                                    dnr_stat_3;	//0xCC2906D0
	PE_O26_DNR0_DNR_STAT_4_T                                    dnr_stat_4;	//0xCC2906D4
	PE_O26_DNR0_DNR_STAT_5_T                                    dnr_stat_5;	//0xCC2906D8
	PE_O26_DNR0_DNR_STAT_6_T                                    dnr_stat_6;	//0xCC2906DC
	PE_O26_DNR0_DNR_STAT_7_T                                    dnr_stat_7;	//0xCC2906E0
	PE_O26_DNR0_APL_STAT_0_T                                    apl_stat_0;	//0xCC2906E4
	PE_O26_DNR0_APL_STAT_1_T                                    apl_stat_1;	//0xCC2906E8
	PE_O26_DNR0_APL_STAT_2_T                                    apl_stat_2;	//0xCC2906EC
	PE_O26_DNR0_DNR_STAT_11_SQM_00_T                    dnr_stat_11_sqm_00;	//0xCC2906F0
	PE_O26_DNR0_DNR_STAT_12_SQM_01_T                    dnr_stat_12_sqm_01;	//0xCC2906F4
	PE_O26_DNR0_DNR_STAT_13_SQM_02_T                    dnr_stat_13_sqm_02;	//0xCC2906F8
	PE_O26_DNR0_DNR_STAT_14_SQM_03_T                    dnr_stat_14_sqm_03;	//0xCC2906FC
	PE_O26_DNR0_DNR_STAT_15_SQM_04_T                    dnr_stat_15_sqm_04;	//0xCC290700
	PE_O26_DNR0_DNR_STAT_16_SQM_05_T                    dnr_stat_16_sqm_05;	//0xCC290704
	PE_O26_DNR0_DNR_STAT_17_SQM_06_T                    dnr_stat_17_sqm_06;	//0xCC290708
	PE_O26_DNR0_DNR_STAT_18_SQM_07_T                    dnr_stat_18_sqm_07;	//0xCC29070C
	PE_O26_DNR0_DNR_STAT_19_SQM_08_T                    dnr_stat_19_sqm_08;	//0xCC290710
	PE_O26_DNR0_DNR_STAT_20_SQM_09_T                    dnr_stat_20_sqm_09;	//0xCC290714
	PE_O26_DNR0_DNR_STAT_21_SQM_10_T                    dnr_stat_21_sqm_10;	//0xCC290718
	PE_O26_DNR0_DNR_STAT_22_SQM_11_T                    dnr_stat_22_sqm_11;	//0xCC29071C
	PE_O26_DNR0_DNR_STAT_23_TPD_0_T                      dnr_stat_23_tpd_0;	//0xCC290720
	PE_O26_DNR0_DNR_STAT_24_TPD_1_T                      dnr_stat_24_tpd_1;	//0xCC290724
	PE_O26_DNR0_DNR_STAT_25_TPD_2_T                      dnr_stat_25_tpd_2;	//0xCC290728
	UINT32                                                      reserved18;	//0xCC29072C
	PE_O26_DNR0_AC_BNR_15_T                                      ac_bnr_15;	//0xCC290730
	PE_O26_DNR0_AC_BNR_16_T                                      ac_bnr_16;	//0xCC290734
	PE_O26_DNR0_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0xCC290738
	PE_O26_DNR0_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0xCC29073C
	PE_O26_DNR0_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0xCC290740
	PE_O26_DNR0_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0xCC290744
	PE_O26_DNR0_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0xCC290748
	PE_O26_DNR0_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0xCC29074C
	PE_O26_DNR0_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0xCC290750
	PE_O26_DNR0_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0xCC290754
	PE_O26_DNR0_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0xCC290758
	PE_O26_DNR0_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0xCC29075C
	PE_O26_DNR0_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0xCC290760
	PE_O26_DNR0_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCC290764
	PE_O26_DNR0_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCC290768
	PE_O26_DNR0_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCC29076C
	PE_O26_DNR0_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCC290770
	PE_O26_DNR0_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCC290774
	PE_O26_DNR0_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCC290778
	PE_O26_DNR0_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCC29077C
	PE_O26_DNR0_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCC290780
	PE_O26_DNR0_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCC290784
	PE_O26_DNR0_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCC290788
	PE_O26_DNR0_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCC29078C
	PE_O26_DNR0_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCC290790
	PE_O26_DNR0_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCC290794
	PE_O26_DNR0_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCC290798
	PE_O26_DNR0_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCC29079C
	PE_O26_DNR0_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xCC2907A0
	PE_O26_DNR0_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xCC2907A4
	PE_O26_DNR0_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCC2907A8
	PE_O26_DNR0_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCC2907AC
	PE_O26_DNR0_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCC2907B0
	PE_O26_DNR0_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCC2907B4
	PE_O26_DNR0_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCC2907B8
	PE_O26_DNR0_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCC2907BC
	PE_O26_DNR0_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCC2907C0
	PE_O26_DNR0_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCC2907C4
	PE_O26_DNR0_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCC2907C8
	PE_O26_DNR0_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCC2907CC
	PE_O26_DNR0_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCC2907D0
	PE_O26_DNR0_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCC2907D4
	PE_O26_DNR0_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCC2907D8
	PE_O26_DNR0_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCC2907DC
	PE_O26_DNR0_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCC2907E0
	PE_O26_DNR0_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCC2907E4
	PE_O26_DNR0_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCC2907E8
	PE_O26_DNR0_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCC2907EC
	PE_O26_DNR0_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCC2907F0
	PE_O26_DNR0_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCC2907F4
	PE_O26_DNR0_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCC2907F8
	PE_O26_DNR0_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCC2907FC
	PE_O26_DNR0_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCC290800
	PE_O26_DNR0_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCC290804
	PE_O26_DNR0_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCC290808
	PE_O26_DNR0_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCC29080C
	PE_O26_DNR0_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCC290810
	PE_O26_DNR0_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCC290814
	PE_O26_DNR0_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCC290818
	PE_O26_DNR0_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCC29081C
	PE_O26_DNR0_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCC290820
	PE_O26_DNR0_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCC290824
	PE_O26_DNR0_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCC290828
	PE_O26_DNR0_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCC29082C
	PE_O26_DNR0_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCC290830
	PE_O26_DNR0_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCC290834
	PE_O26_DNR0_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCC290838
	PE_O26_DNR0_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCC29083C
	PE_O26_DNR0_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCC290840
	PE_O26_DNR0_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCC290844
	PE_O26_DNR0_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCC290848
	PE_O26_DNR0_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCC29084C
	PE_O26_DNR0_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCC290850
	PE_O26_DNR0_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCC290854
	PE_O26_DNR0_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCC290858
	PE_O26_DNR0_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCC29085C
	PE_O26_DNR0_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCC290860
	PE_O26_DNR0_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCC290864
	PE_O26_DNR0_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCC290868
	PE_O26_DNR0_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCC29086C
	PE_O26_DNR0_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCC290870
	PE_O26_DNR0_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCC290874
	PE_O26_DNR0_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCC290878
	PE_O26_DNR0_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCC29087C
	PE_O26_DNR0_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCC290880
	PE_O26_DNR0_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCC290884
	PE_O26_DNR0_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCC290888
	PE_O26_DNR0_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCC29088C
	PE_O26_DNR0_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCC290890
	PE_O26_DNR0_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCC290894
	PE_O26_DNR0_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCC290898
	PE_O26_DNR0_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCC29089C
	PE_O26_DNR0_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCC2908A0
	PE_O26_DNR0_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCC2908A4
	PE_O26_DNR0_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCC2908A8
	PE_O26_DNR0_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCC2908AC
	PE_O26_DNR0_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCC2908B0
	PE_O26_DNR0_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCC2908B4
	PE_O26_DNR0_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCC2908B8
	PE_O26_DNR0_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCC2908BC
	PE_O26_DNR0_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCC2908C0
	PE_O26_DNR0_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCC2908C4
	PE_O26_DNR0_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCC2908C8
	PE_O26_DNR0_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCC2908CC
	PE_O26_DNR0_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCC2908D0
	PE_O26_DNR0_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCC2908D4
	PE_O26_DNR0_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCC2908D8
	PE_O26_DNR0_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCC2908DC
	PE_O26_DNR0_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCC2908E0
	PE_O26_DNR0_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCC2908E4
	PE_O26_DNR0_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCC2908E8
	PE_O26_DNR0_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCC2908EC
	PE_O26_DNR0_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCC2908F0
	PE_O26_DNR0_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC2908F4
	PE_O26_DNR0_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC2908F8
	PE_O26_DNR0_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC2908FC
	PE_O26_DNR0_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC290900
	PE_O26_DNR0_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC290904
	PE_O26_DNR0_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC290908
	PE_O26_DNR0_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC29090C
	PE_O26_DNR0_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC290910
	PE_O26_DNR0_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC290914
	PE_O26_DNR0_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC290918
	PE_O26_DNR0_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC29091C
	PE_O26_DNR0_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC290920
	PE_O26_DNR0_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC290924
	PE_O26_DNR0_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC290928
	PE_O26_DNR0_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC29092C
	PE_O26_DNR0_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC290930
	PE_O26_DNR0_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC290934
	PE_O26_DNR0_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC290938
	PE_O26_DNR0_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC29093C
	PE_O26_DNR0_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC290940
	PE_O26_DNR0_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC290944
	PE_O26_DNR0_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC290948
	PE_O26_DNR0_REG_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xCC29094C
	PE_O26_DNR0_REG_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xCC290950
	PE_O26_DNR0_REG_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xCC290954
	PE_O26_DNR0_REG_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xCC290958
	PE_O26_DNR0_REG_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xCC29095C
	PE_O26_DNR0_REG_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xCC290960
	PE_O26_DNR0_REG_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xCC290964
	UINT32                                                      reserved19;	//0xCC290968
	UINT32                                                      reserved20;	//0xCC29096C
	UINT32                                                      reserved21;	//0xCC290970
	UINT32                                                      reserved22;	//0xCC290974
	UINT32                                                      reserved23;	//0xCC290978
	PE_O26_DNR0_REG_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xCC29097C
	PE_O26_DNR0_REG_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xCC290980
	PE_O26_DNR0_REG_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xCC290984
	PE_O26_DNR0_REG_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xCC290988
	PE_O26_DNR0_REG_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xCC29098C
	PE_O26_DNR0_REG_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xCC290990
	PE_O26_DNR0_REG_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xCC290994
	PE_O26_DNR0_REG_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xCC290998
	PE_O26_DNR0_REG_DECON_CTRL_120_T                    reg_decon_ctrl_120;	//0xCC29099C
	PE_O26_DNR0_REG_DECON_CTRL_121_T                    reg_decon_ctrl_121;	//0xCC2909A0
	PE_O26_DNR0_REG_DECON_CTRL_122_T                    reg_decon_ctrl_122;	//0xCC2909A4
	PE_O26_DNR0_REG_DECON_CTRL_123_T                    reg_decon_ctrl_123;	//0xCC2909A8
	PE_O26_DNR0_REG_DECON_CTRL_124_T                    reg_decon_ctrl_124;	//0xCC2909AC
	PE_O26_DNR0_REG_DECON_CTRL_125_T                    reg_decon_ctrl_125;	//0xCC2909B0
	PE_O26_DNR0_REG_DECON_CTRL_126_T                    reg_decon_ctrl_126;	//0xCC2909B4
	PE_O26_DNR0_REG_DECON_CTRL_127_T                    reg_decon_ctrl_127;	//0xCC2909B8
	PE_O26_DNR0_REG_DECON_CTRL_128_T                    reg_decon_ctrl_128;	//0xCC2909BC
	PE_O26_DNR0_REG_DECON_CTRL_129_T                    reg_decon_ctrl_129;	//0xCC2909C0
	PE_O26_DNR0_REG_DECON_CTRL_130_T                    reg_decon_ctrl_130;	//0xCC2909C4
	PE_O26_DNR0_REG_DECON_CTRL_131_T                    reg_decon_ctrl_131;	//0xCC2909C8
	PE_O26_DNR0_REG_DECON_CTRL_132_T                    reg_decon_ctrl_132;	//0xCC2909CC
	PE_O26_DNR0_REG_DECON_CTRL_133_T                    reg_decon_ctrl_133;	//0xCC2909D0
	PE_O26_DNR0_REG_DECON_CTRL_134_T                    reg_decon_ctrl_134;	//0xCC2909D4
	PE_O26_DNR0_REG_DECON_CTRL_135_T                    reg_decon_ctrl_135;	//0xCC2909D8
	PE_O26_DNR0_REG_DECON_CTRL_136_T                    reg_decon_ctrl_136;	//0xCC2909DC
	PE_O26_DNR0_REG_DECON_CTRL_137_T                    reg_decon_ctrl_137;	//0xCC2909E0
	PE_O26_DNR0_REG_DECON_CTRL_138_T                    reg_decon_ctrl_138;	//0xCC2909E4
	PE_O26_DNR0_REG_DECON_CTRL_139_T                    reg_decon_ctrl_139;	//0xCC2909E8
	PE_O26_DNR0_REG_DECON_CTRL_140_T                    reg_decon_ctrl_140;	//0xCC2909EC
	PE_O26_DNR0_REG_DECON_CTRL_141_T                    reg_decon_ctrl_141;	//0xCC2909F0
	PE_O26_DNR0_REG_DECON_CTRL_142_T                    reg_decon_ctrl_142;	//0xCC2909F4
	PE_O26_DNR0_REG_DECON_CTRL_143_T                    reg_decon_ctrl_143;	//0xCC2909F8
	PE_O26_DNR0_REG_DECON_CTRL_144_T                    reg_decon_ctrl_144;	//0xCC2909FC
	PE_O26_DNR0_REG_DECON_CTRL_145_T                    reg_decon_ctrl_145;	//0xCC290A00
	PE_O26_DNR0_REG_DECON_CTRL_146_T                    reg_decon_ctrl_146;	//0xCC290A04
	PE_O26_DNR0_REG_DECON_CTRL_147_T                    reg_decon_ctrl_147;	//0xCC290A08
	PE_O26_DNR0_REG_DECON_CTRL_148_T                    reg_decon_ctrl_148;	//0xCC290A0C
	PE_O26_DNR0_REG_DECON_CTRL_149_T                    reg_decon_ctrl_149;	//0xCC290A10
	PE_O26_DNR0_REG_DECON_CTRL_150_T                    reg_decon_ctrl_150;	//0xCC290A14
	PE_O26_DNR0_REG_DECON_CTRL_151_T                    reg_decon_ctrl_151;	//0xCC290A18
	PE_O26_DNR0_REG_DECON_CTRL_152_T                    reg_decon_ctrl_152;	//0xCC290A1C
	PE_O26_DNR0_REG_DECON_CTRL_153_T                    reg_decon_ctrl_153;	//0xCC290A20
	PE_O26_DNR0_REG_DECON_CTRL_154_T                    reg_decon_ctrl_154;	//0xCC290A24
	PE_O26_DNR0_REG_DECON_CTRL_155_T                    reg_decon_ctrl_155;	//0xCC290A28
	PE_O26_DNR0_REG_DECON_CTRL_156_T                    reg_decon_ctrl_156;	//0xCC290A2C
	PE_O26_DNR0_REG_DECON_CTRL_157_T                    reg_decon_ctrl_157;	//0xCC290A30
	PE_O26_DNR0_REG_DECON_CTRL_158_T                    reg_decon_ctrl_158;	//0xCC290A34
	PE_O26_DNR0_REG_DECON_CTRL_159_T                    reg_decon_ctrl_159;	//0xCC290A38
	PE_O26_DNR0_REG_DECON_CTRL_160_T                    reg_decon_ctrl_160;	//0xCC290A3C
	PE_O26_DNR0_REG_DECON_CTRL_161_T                    reg_decon_ctrl_161;	//0xCC290A40
	PE_O26_DNR0_REG_DECON_CTRL_162_T                    reg_decon_ctrl_162;	//0xCC290A44
	PE_O26_DNR0_REG_DECON_CTRL_163_T                    reg_decon_ctrl_163;	//0xCC290A48
	PE_O26_DNR0_REG_DECON_CTRL_164_T                    reg_decon_ctrl_164;	//0xCC290A4C
	PE_O26_DNR0_REG_DECON_CTRL_165_T                    reg_decon_ctrl_165;	//0xCC290A50
	PE_O26_DNR0_REG_DECON_CTRL_166_T                    reg_decon_ctrl_166;	//0xCC290A54
	PE_O26_DNR0_REG_DECON_CTRL_167_T                    reg_decon_ctrl_167;	//0xCC290A58
	PE_O26_DNR0_REG_DECON_CTRL_168_T                    reg_decon_ctrl_168;	//0xCC290A5C
	PE_O26_DNR0_REG_DECON_CTRL_169_T                    reg_decon_ctrl_169;	//0xCC290A60
	PE_O26_DNR0_REG_DECON_CTRL_170_T                    reg_decon_ctrl_170;	//0xCC290A64
	PE_O26_DNR0_REG_DECON_CTRL_171_T                    reg_decon_ctrl_171;	//0xCC290A68
	PE_O26_DNR0_REG_DECON_CTRL_172_T                    reg_decon_ctrl_172;	//0xCC290A6C
	PE_O26_DNR0_REG_DECON_CTRL_173_T                    reg_decon_ctrl_173;	//0xCC290A70
	PE_O26_DNR0_REG_DECON_CTRL_174_T                    reg_decon_ctrl_174;	//0xCC290A74
	PE_O26_DNR0_REG_DECON_CTRL_175_T                    reg_decon_ctrl_175;	//0xCC290A78
	PE_O26_DNR0_REG_DECON_CTRL_176_T                    reg_decon_ctrl_176;	//0xCC290A7C
	PE_O26_DNR0_REG_DECON_CTRL_177_T                    reg_decon_ctrl_177;	//0xCC290A80
	PE_O26_DNR0_REG_DECON_CTRL_178_T                    reg_decon_ctrl_178;	//0xCC290A84
	PE_O26_DNR0_REG_DECON_CTRL_179_T                    reg_decon_ctrl_179;	//0xCC290A88
	PE_O26_DNR0_REG_DECON_CTRL_180_T                    reg_decon_ctrl_180;	//0xCC290A8C
	PE_O26_DNR0_REG_DECON_CTRL_181_T                    reg_decon_ctrl_181;	//0xCC290A90
	PE_O26_DNR0_REG_DECON_CTRL_182_T                    reg_decon_ctrl_182;	//0xCC290A94
	PE_O26_DNR0_REG_OAPL_CTRL_0_T                          reg_oapl_ctrl_0;	//0xCC290A98
	PE_O26_DNR0_REG_OAPL_CTRL_1_T                          reg_oapl_ctrl_1;	//0xCC290A9C
	PE_O26_DNR0_REG_OAPL_CTRL_26_T                        reg_oapl_ctrl_26;	//0xCC290AA0
	PE_O26_DNR0_REG_OAPL_CTRL_27_T                        reg_oapl_ctrl_27;	//0xCC290AA4
	PE_O26_DNR0_REG_OAPL_CTRL_28_T                        reg_oapl_ctrl_28;	//0xCC290AA8
	PE_O26_DNR0_REG_OAPL_CTRL_29_T                        reg_oapl_ctrl_29;	//0xCC290AAC
	PE_O26_DNR0_REG_OAPL_CTRL_30_T                        reg_oapl_ctrl_30;	//0xCC290AB0
	PE_O26_DNR0_REG_OAPL_CTRL_31_T                        reg_oapl_ctrl_31;	//0xCC290AB4
	PE_O26_DNR0_REG_OAPL_CTRL_32_T                        reg_oapl_ctrl_32;	//0xCC290AB8
	PE_O26_DNR0_REG_OAPL_CTRL_33_T                        reg_oapl_ctrl_33;	//0xCC290ABC
	PE_O26_DNR0_REG_OAPL_CTRL_34_T                        reg_oapl_ctrl_34;	//0xCC290AC0
	PE_O26_DNR0_REG_OAPL_CTRL_35_T                        reg_oapl_ctrl_35;	//0xCC290AC4
	PE_O26_DNR0_REG_OAPL_CTRL_36_T                        reg_oapl_ctrl_36;	//0xCC290AC8
	PE_O26_DNR0_REG_OAPL_CTRL_44_T                        reg_oapl_ctrl_44;	//0xCC290ACC
	PE_O26_DNR0_REG_OAPL_CTRL_45_T                        reg_oapl_ctrl_45;	//0xCC290AD0
	PE_O26_DNR0_REG_OAPL_CTRL_46_T                        reg_oapl_ctrl_46;	//0xCC290AD4
	PE_O26_DNR0_REG_OAPL_CTRL_47_T                        reg_oapl_ctrl_47;	//0xCC290AD8
	PE_O26_DNR0_REG_OAPL_CTRL_48_T                        reg_oapl_ctrl_48;	//0xCC290ADC
	UINT32                                                      reserved24;	//0xCC290AE0
	UINT32                                                      reserved25;	//0xCC290AE4
	UINT32                                                      reserved26;	//0xCC290AE8
	UINT32                                                      reserved27;	//0xCC290AEC
	PE_O26_DNR0_REG_OAPL_CTRL_49_T                        reg_oapl_ctrl_49;	//0xCC290AF0
	PE_O26_DNR0_REG_OAPL_CTRL_50_T                        reg_oapl_ctrl_50;	//0xCC290AF4
	PE_O26_DNR0_REG_OAPL_CTRL_51_T                        reg_oapl_ctrl_51;	//0xCC290AF8
	PE_O26_DNR0_REG_OAPL_CTRL_52_T                        reg_oapl_ctrl_52;	//0xCC290AFC
	PE_O26_DNR0_REG_SMR_CTRL_00_T                          reg_smr_ctrl_00;	//0xCC290B00
	PE_O26_DNR0_REG_SMR_CTRL_01_T                          reg_smr_ctrl_01;	//0xCC290B04
	PE_O26_DNR0_REG_SMR_CTRL_02_T                          reg_smr_ctrl_02;	//0xCC290B08
	PE_O26_DNR0_REG_SMR_CTRL_03_T                          reg_smr_ctrl_03;	//0xCC290B0C
	PE_O26_DNR0_REG_SMR_CTRL_04_T                          reg_smr_ctrl_04;	//0xCC290B10
	PE_O26_DNR0_REG_SMR_CTRL_05_T                          reg_smr_ctrl_05;	//0xCC290B14
	PE_O26_DNR0_REG_SMR_CTRL_06_T                          reg_smr_ctrl_06;	//0xCC290B18
	PE_O26_DNR0_REG_SMR_CTRL_07_T                          reg_smr_ctrl_07;	//0xCC290B1C
	PE_O26_DNR0_REG_SMR_CTRL_08_T                          reg_smr_ctrl_08;	//0xCC290B20
	PE_O26_DNR0_REG_SMR_CTRL_09_T                          reg_smr_ctrl_09;	//0xCC290B24
	PE_O26_DNR0_REG_SMR_CTRL_10_T                          reg_smr_ctrl_10;	//0xCC290B28
	PE_O26_DNR0_REG_SMR_CTRL_11_T                          reg_smr_ctrl_11;	//0xCC290B2C
	PE_O26_DNR0_REG_SMR_CTRL_12_T                          reg_smr_ctrl_12;	//0xCC290B30
	PE_O26_DNR0_REG_SMR_CTRL_13_T                          reg_smr_ctrl_13;	//0xCC290B34
	PE_O26_DNR0_REG_SMR_CTRL_14_T                          reg_smr_ctrl_14;	//0xCC290B38
	PE_O26_DNR0_REG_SMR_CTRL_15_T                          reg_smr_ctrl_15;	//0xCC290B3C
	PE_O26_DNR0_REG_SMR_CTRL_16_T                          reg_smr_ctrl_16;	//0xCC290B40
	PE_O26_DNR0_REG_SMR_CTRL_17_T                          reg_smr_ctrl_17;	//0xCC290B44
	PE_O26_DNR0_REG_SMR_CTRL_18_T                          reg_smr_ctrl_18;	//0xCC290B48
	PE_O26_DNR0_REG_SMR_CTRL_19_T                          reg_smr_ctrl_19;	//0xCC290B4C
	PE_O26_DNR0_REG_SMR_CTRL_20_T                          reg_smr_ctrl_20;	//0xCC290B50
	PE_O26_DNR0_REG_SMR_CTRL_21_T                          reg_smr_ctrl_21;	//0xCC290B54
	PE_O26_DNR0_REG_SMR_CTRL_22_T                          reg_smr_ctrl_22;	//0xCC290B58
	PE_O26_DNR0_REG_SMR_CTRL_23_T                          reg_smr_ctrl_23;	//0xCC290B5C
}PE_DNR0_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0500 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 load_enable                      :1;	//(1,RW,0x00) //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd1                           :29;
	};
}PE_O26_DNR1_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0504 RW 0x0000_0000
	UINT32 intr_enable                      :1;	//(0,RW,0x00) //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//(6:4,RW,0x00) //interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  NA	'001 =  NA	'010 = NA	'011 = NA	'100 = dnr_end	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//(8,RW,0x00) //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//(26:16,RW,0x00) //the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_O26_DNR1_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0508 RO 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 dnr_frame_id                     :8;	//(23:16,RO,0x0) //DNR_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//(27:24,RO,0x00) //PIC_INIT_FRAME_ID
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C050C RO 0x0000_0000
	UINT32 line_cnt                         :11;	//(10:0,RO,0x00) //
	UINT32 resvd                            :5;
	UINT32 timer_cnt                        :16;	//(31:16,RO,0x0) //timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_O26_DNR1_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0510 RW 0x0000_C000
	UINT32 resvd0                           :8;
	UINT32 reg_sd_5l_mode_en                :1;	//(8,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 dnr_out_420_vsample_mode         :1;	//(12,RW,0x00) //0 := 0,3,4,7,?	1 = 0,2,4,6,?
	UINT32 dnr_out_cs_type                  :3;	//(15:13,RW,0x6) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 detour_enable                    :1;	//(16,RW,0x00) //
	UINT32 half_rate_en                     :1;	//(17,RW,0x00) //should be enabled for the interlaced source	should be enabled for running IFC
	UINT32 resvd2                           :2;
	UINT32 ibuf_en                          :2;	//(21:20,RW,0x0) //(20) input buffer enable Y 	(21) input buffer enable C
	UINT32 dnr_out_422_hsample_mode         :1;	//(22,RW,0x00) //0 := 0,2,4,6,?	1 = 1,3,5,7,?
	UINT32 resvd3                           :1;
	UINT32 dnr_in_lsb_mode                  :2;	//(25:24,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 dnr_out_lsb_mode                 :2;	//(27:26,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 resvd4                           :2;
	UINT32 m_run_id                         :2;	//(31:30,RW,0x00) //
	};
}PE_O26_DNR1_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0514 RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE: ??? ??. ??? ???? ??
	UINT32 resvd0                           :1;
	UINT32 chroma_sampling_type             :3;	//(15:13,RW,0x00) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0518 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //??? ??. ??? ???? ??
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_OUT_SIZE -> in_hsize	1 = PE0_OUT_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR1_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C051C RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE : ??? ??. ??? ???? ??
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE : ??? ??. ??? ???? ??	 (progressive format ??)
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_PE0_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0520 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_WIN_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0524 RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_WIN_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0528 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 ac_bnr_feature_cal_mode          :2;	//(29:28,RW,0x00) //AC-BNR feature cal. mode	'00 := full-screen mode	'01 =  reserved	'10 = active window mode - manual window setting by 	        reg_win_ctrl_2 & reg_win_ctrl_3	'11 = active window mode - auto window setting by black	         boundary detection
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR1_WIN_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C052C RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_WIN_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0530 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O26_DNR1_CUP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0534 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O26_DNR1_CUP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0538 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_CUP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0580 RW 0x0000_0000
	UINT32 reg_glb_tearing_th               :8;	//(7:0,RW,0x0) //
	UINT32 reg_glb_mode_th                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_tearing_strength             :1;	//(12,RW,0x00) //
	UINT32 reg_glb_tearing_cnt_normal       :3;	//(15:13,RW,0x00) //
	UINT32 reg_vf_a_th                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :6;
	UINT32 reg_vflt_force_en                :1;	//(30,RW,0x00) //
	UINT32 reg_vflt_en                      :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR1_VFILTER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0584 RW 0x0000_0000
	UINT32 reg_vflt_debug_en                :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_fmd_mode                     :1;	//(4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_glb_mode                     :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_glb_mode_fw_en               :1;	//(12,RW,0x00) //
	UINT32 resvd3                           :3;
	UINT32 reg_glb_vflt_en                  :1;	//(16,RW,0x00) //
	UINT32 resvd4                           :3;
	UINT32 reg_fmd_vflt_en                  :1;	//(20,RW,0x00) //
	UINT32 resvd5                           :3;
	UINT32 reg_fmd_tearing_cnt_en           :1;	//(24,RW,0x00) //
	UINT32 resvd6                           :3;
	UINT32 reg_fmd_motion_en                :1;	//(28,RW,0x00) //
	UINT32 resvd7                           :3;
	};
}PE_O26_DNR1_VFILTER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0588 RW 0x0000_0000
	UINT32 reg_hmc_vflt_en                  :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_hmc_tearing_cnt_en           :1;	//(4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_hmc_motion_en                :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_loc_vflt_en                  :1;	//(12,RW,0x00) //
	UINT32 resvd3                           :3;
	UINT32 reg_loc_tearing_cnt_en           :1;	//(16,RW,0x00) //
	UINT32 resvd4                           :3;
	UINT32 reg_loc_motion_en_               :1;	//(20,RW,0x00) //
	UINT32 resvd5                           :3;
	UINT32 reg_alpha_sel_mode               :2;	//(25:24,RW,0x00) //
	UINT32 resvd6                           :2;
	UINT32 reg_alpha_sel_mode_en            :2;	//(29:28,RW,0x00) //
	UINT32 resvd7                           :2;
	};
}PE_O26_DNR1_VFILTER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C058C RW 0x0000_1400
	UINT32 cti_en                           :1;	//(0,RW,0x00) //CTI enable
	UINT32 cti_clipping_mode                :1;	//(1,RW,0x00) //op mode	'0' : CTI	'1': peaking(for debug)
	UINT32 cti_pre_flt_mode                 :1;	//(2,RW,0x00) //pre-filtering	0 : off	1 : on
	UINT32 cti_tap                          :2;	//(4:3,RW,0x00) //CTI filter tap size	'0' : 7-tap	'1': 5-tap	'2': 3_2-tap	'3': 3-tap
	UINT32 resvd0                           :3;
	UINT32 cti_gain                         :8;	//(15:8,RW,0x14) //CTI gain(3.5u)
	UINT32 cti_debug_mode                   :3;	//(18:16,RW,0x00) //debug mode	"000" : normal display	"100" : coring map(cb)	"101" : coring map(cr)	"110" : avg(cb)	"111" : avg(cr)
	UINT32 resvd1                           :13;
	};
}PE_O26_DNR1_CTI_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0590 RW 0x0020_2101
	UINT32 cti_coring_th0                   :8;	//(7:0,RW,0x1) //CTI coring th0
	UINT32 cti_coring_th1                   :8;	//(15:8,RW,0x21) //CTI coring th1
	UINT32 cti_coring_smooth                :3;	//(18:16,RW,0x0) //NOT USED
	UINT32 resvd0                           :1;
	UINT32 reg_cti_tap2                     :2;	//(21:20,RW,0x2) //CTI coring map size	"00" : 7-tap	"01" : 5-tap	"10" : 3-tap	o.w : 7-tap
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_CTI_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0594 RW 0x0000_0000
	UINT32 reg_dnr_max_enable               :1;	//(0,RW,0x00) //0 : bypass(or ifc result), 1 : dnr_mux
	UINT32 reg_ifc_max_enable               :1;	//(1,RW,0x00) //0 : dnr result, 1 : ifc_mux
	UINT32 reg_dnr_ifc_sel                  :1;	//(2,RW,0x00) //0 : dnr result, 1 : ifc result
	UINT32 reg_decon_max_sum_sel            :1;	//(3,RW,0x00) //0 : sum, 1 : max
	UINT32 reg_decon_ori_sel                :1;	//(4,RW,0x0) //0: original, 1: v_filter
	UINT32 reg_decon_max_enable             :1;	//(5,RW,0x0) //0: dnr only, 1: dnr+decon
	UINT32 reg_max_decon_dbg_en             :1;	//(6,RW,0x0) //
	UINT32 reg_half_rate_cg_n               :1;	//(7,RW,0x0) //0: cg_on, 1: cg_off
	UINT32 reg_max_dbg_en                   :1;	//(8,RW,0x00) //ac : black, dc : white, mnr : green
	UINT32 reg_dnr_motion_sel               :1;	//(9,RW,0x00) //0: 1:2:1 blurred motion 1: 5x5 blurred motion
	UINT32 reg_tnr_decon_en                 :1;	//(10,RW,0x0) //1: tnr_decon, 0: dnr_decon
	UINT32 reg_face_obj_sel                 :1;	//(11,RW,0x0) //0: dnr obc(4K??, internal), 1: nd obc(4K ??(8K), external)	Not used in O-series(Only E series)
	UINT32 resvd0                           :4;
	UINT32 reg_win_en                       :1;	//(16,RW,0x00) //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//(17,RW,0x00) //border enable
	UINT32 reg_win_inout                    :1;	//(18,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_ipc_motion_en                :1;	//(21,RW,0x0) //hmc_flag ?? => 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//(24:22,RW,0x00) //0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//(31:25,RW,0x0) //applied ifc when delta is greater than th
	};
}PE_O26_DNR1_DNR_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0598 RW 0x0000_0000
	UINT32 reg_dbg_en                       :1;	//(0,RW,0x00) //debug bar en
	UINT32 reg_show_f3d                     :1;	//(1,RW,0x00) //
	UINT32 reg_show_bnr                     :1;	//(2,RW,0x00) //show debug bar for bnr	(acness,acness gain, dc_gain)
	UINT32 reg_f3d_mode                     :1;	//(3,RW,0x00) //
	UINT32 reg_acness_or_acness_gain        :1;	//(4,RW,0x00) //0 : acness (blue, green)	1 : acness gain (yellow, red)
	UINT32 resvd                            :27;
	};
}PE_O26_DNR1_DNR_DBAR_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C059C RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_detect_level_th              :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_DNR1_REG_C420_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05A0 RW 0x0000_0000
	UINT32 reg_mnr_enable                   :1;	//(0,RW,0x00) //
	UINT32 reg_mnr_debug                    :1;	//(1,RW,0x00) //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//(2,RW,0x00) //
	UINT32 reg_mnr_chroma_en                :1;	//(3,RW,0x00) //
	UINT32 reg_h_expand                     :2;	//(5:4,RW,0x0) //0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//(7:6,RW,0x00) //0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//(15:8,RW,0x0) //
	UINT32 reg_snr_th                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_th_max                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_MNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05A4 RW 0x0000_0000
	UINT32 reg_mmd_y_max                    :8;	//(7:0,RW,0x0) //edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//(15:8,RW,0x0) //reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//(23:16,RW,0x0) //reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//(31:24,RW,0x0) //reg_mnr_s2_mmd_min
	};
}PE_O26_DNR1_MNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05A8 RW 0x0000_0000
	UINT32 reg_mnr_debug_mode               :4;	//(3:0,RW,0x00) //0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain	9: prv mmd map	A: mmd var	B: O22 New, final gain
	UINT32 reg_mnr_debug_en                 :1;	//(4,RW,0x00) //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_MNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05AC RW 0x0000_0000
	UINT32 reg_blur_sel                     :1;	//(0,RW,0x00) //
	UINT32 reg_pattern_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_equal_th                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_scale                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_MNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05B0 RW 0x0000_0000
	UINT32 reg_mmd_fil_x_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_x_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_x_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_x_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_MNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05B4 RW 0x0000_0000
	UINT32 reg_mmd_fil_y_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_y_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_y_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_y_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_MNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05B8 RW 0x0404_0A40
	UINT32 reg_bnr_ac_detail_max            :8;	//(7:0,RW,0x40) //detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//(15:8,RW,0xA) //detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//(23:16,RW,0x4) //th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//(31:24,RW,0x4) //th used to find point of inflection
	};
}PE_O26_DNR1_DETAIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05BC RW 0x0000_0000
	UINT32 reg_dc_bnr_enable                :1;	//(0,RW,0x0) //DC BNR enable	0 := off ( output debug mode )	1  = on
	UINT32 reg_dc_blur_debug_mode           :1;	//(1,RW,0x0) //0: blur, 1: white
	UINT32 reg_dc_blur_sel                  :2;	//(3:2,RW,0x0) //DC blur sel => 0 : 3x3, 1 : 5x5, 2 : 9x5
	UINT32 reg_dc_output_debug_mode         :4;	//(7:4,RW,0x0) //0: bypass	1: motion	2: motion gain	3: sum of variance	4: variance gain	5: edge protection map	6: DC gain without edge protection	7: DC gain with edge protection	8: chroma gain without edge protection	9: chroma gain with edge protection	10: fil_diff_th
	UINT32 reg_en_obj_amf_ctrl              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_obj_gain_mul                 :2;	//(14:13,RW,0x0) //
	UINT32 reg_obj_gain_en                  :1;	//(15,RW,0x0) //
	UINT32 reg_dc_motion_max                :8;	//(23:16,RW,0x0) //dc motion gain th
	UINT32 reg_dc_motion_min                :8;	//(31:24,RW,0x0) //dc motion gain th, if(reg_dc_motion_en == 0) reg_dc_motion_y_max = manual motion gain value
	};
}PE_O26_DNR1_DC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05C0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_manual_fil_motion_gain       :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_chroma_en                :1;	//(16,RW,0x0) //
	UINT32 reg_fil_manual_en                :1;	//(17,RW,0x0) //
	UINT32 reg_dc_pattern_en                :1;	//(18,RW,0x0) //
	UINT32 reg_luma_gain_en                 :1;	//(19,RW,0x0) //
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //0x5
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //0x2
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //0x5
	};
}PE_O26_DNR1_DC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05C4 RW 0x0000_0000
	UINT32 reg_dc_var_en                    :1;	//(0,RW,0x0) //0x1
	UINT32 reg_dc_motion_en                 :1;	//(1,RW,0x0) //0x0
	UINT32 reg_dc_protection_en             :1;	//(2,RW,0x0) //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//(15:10,RW,0x0) //0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//(23:16,RW,0x0) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_DC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05C8 RW 0x0000_0000
	UINT32 reg_dc_bnr_var_th3               :8;	//(7:0,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//(15:8,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//(23:16,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//(31:24,RW,0x0) //dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
}PE_O26_DNR1_DC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05CC RW 0x0000_0000
	UINT32 reg_dc_motion_y_min              :8;	//(7:0,RW,0x0) //motion gain y?
	UINT32 reg_dc_motion_y_max              :8;	//(15:8,RW,0x0) //motion gain y?
	UINT32 resvd                            :16;
	};
}PE_O26_DNR1_DC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05D0 RW 0x0000_0000
	UINT32 reg_dc_var_y_th0                 :8;	//(7:0,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th1                 :8;	//(15:8,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th2                 :8;	//(23:16,RW,0x0) //variance gain y?
	UINT32 reg_dc_var_y_th3                 :8;	//(31:24,RW,0x0) //variance gain y?
	};
}PE_O26_DNR1_DC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05D4 RW 0xB30B_0B4F
	UINT32 reg_bnr_ac_h_en                  :1;	//(0,RW,0x1) //
	UINT32 reg_bnr_ac_v_en                  :1;	//(1,RW,0x1) //
	UINT32 reg_bnr_ac_h_chroma_en           :1;	//(2,RW,0x1) //
	UINT32 reg_bnr_ac_v_chroma_en           :1;	//(3,RW,0x1) //
	UINT32 reg_bnr_ac_acness_resol_h        :2;	//(5:4,RW,0x0) //1: /2, 2: /4, 3:/ 8
	UINT32 reg_multi_run_mode               :1;	//(6,RW,0x1) //
	UINT32 reg_ac_bnr_gain_yc_sel           :1;	//(7,RW,0x0) //
	UINT32 reg_bnr_ac_diff_min_v_th         :8;	//(15:8,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_diff_min_h_th         :8;	//(23:16,RW,0xB) //minimum value to accumulate line position histogram
	UINT32 reg_bnr_ac_iir_gain              :8;	//(31:24,RW,0xB3) //alpha value used in IIR
	};
}PE_O26_DNR1_AC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05D8 RW 0x0F19_370B
	UINT32 reg_bnr_ac_global_motion_th      :8;	//(7:0,RW,0xB) //0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//(15:8,RW,0x37) //th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//(23:16,RW,0x19) //th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//(31:24,RW,0xF) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05DC RW 0x0A20_4060
	UINT32 reg_bnr_ac_motion_3              :8;	//(7:0,RW,0x60) //motion gain x?
	UINT32 reg_bnr_ac_motion_2              :8;	//(15:8,RW,0x40) //motion gain x?
	UINT32 reg_bnr_ac_motion_1              :8;	//(23:16,RW,0x20) //motion gain x?
	UINT32 reg_bnr_ac_motion_0              :8;	//(31:24,RW,0xA) //motion gain x?
	};
}PE_O26_DNR1_AC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05E0 RO 0x0000_0000
	UINT32 c420_tearing_cnt                 :16;	//(15:0,RO,0x0) //
	UINT32 global_motion_iir                :8;	//(23:16,RO,0x0) //
	UINT32 global_dc_gain                   :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05E4 RW 0x3060_A0FF
	UINT32 reg_bnr_ac_motion_y_3            :8;	//(7:0,RW,0xFF) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_2            :8;	//(15:8,RW,0xA0) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_1            :8;	//(23:16,RW,0x60) //motion gain y?
	UINT32 reg_bnr_ac_motion_y_0            :8;	//(31:24,RW,0x30) //motion gain y?
	};
}PE_O26_DNR1_AC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05E8 RW 0x1937_5000
	UINT32 reg_bnr_ac_v_init_offset         :3;	//(2:0,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//(5:3,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//(7:6,RW,0x00) //0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//(11:8,RW,0x00) //debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//(15:12,RW,0x05) //stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//(23:16,RW,0x37) //
	UINT32 reg_bnr_ac_v_acness_min          :8;	//(31:24,RW,0x19) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05EC RO 0x0000_0000
	UINT32 acness_v_l                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_g                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05F0 RW 0xFA96_3201
	UINT32 reg_bnr_ac_detail_th4            :8;	//(7:0,RW,0x1) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//(15:8,RW,0x32) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//(23:16,RW,0x96) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//(31:24,RW,0xFA) //detail th used in AC-BNR final mux
	};
}PE_O26_DNR1_AC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05F4 RW 0x00FF_C0C0
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//(7:0,RW,0xC0) //SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//(15:8,RW,0xC0) //SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//(23:16,RW,0xFF) //SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//(31:24,RW,0x0) //0x00
	};
}PE_O26_DNR1_AC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05F8 RW 0x80FF_8040
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//(7:0,RW,0x40) //SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//(15:8,RW,0x80) //SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//(23:16,RW,0xFF) //SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//(31:24,RW,0x80) //SD : 0x00, HD : 0x80
	};
}PE_O26_DNR1_AC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C05FC RO 0x0000_0000
	UINT32 h_init                           :8;	//(7:0,RO,0x0) //
	UINT32 v_init                           :8;	//(15:8,RO,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_vfilter_tearing_cnt          :12;	//(31:20,RO,0x00) //
	};
}PE_O26_DNR1_DNR_STAT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0600 RW 0x0000_0E20
	UINT32 reg_ac_master_c_gain             :8;	//(7:0,RW,0x20) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_ac_bnr_enable                :1;	//(8,RW,0x00) //0 : debug mode, 1 : ac result
	UINT32 reg_ac_bnr_motion_en             :1;	//(9,RW,0x01) //1 : motion gain enable	0 : reg_bnr_ac_motion_y_max = manual motion gain value
	UINT32 reg_ac_bnr_acness_en             :1;	//(10,RW,0x01) //1 : acness gain enable	0 : reg_bnr_ac_acness_y_max = manual acness gain value
	UINT32 reg_ac_bnr_position_en           :1;	//(11,RW,0x01) //1 : position gain enable	0 : reg_bnr_ac_pos_gain_H0_7 = manual position gain value
	UINT32 reg_detail_sel                   :1;	//(12,RW,0x00) //0: old, 1: new
	UINT32 resvd                            :3;
	UINT32 reg_bnr_ac_manual_init_v         :3;	//(18:16,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_v          :1;	//(19,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_manual_init_h         :3;	//(22:20,RW,0x00) //force the specific init position for debug
	UINT32 reg_ac_manual_init_en_h          :1;	//(23,RW,0x00) //0 : off, 1 : on
	UINT32 reg_bnr_ac_pos_gain_l3           :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0604 RW 0x0009_8000
	UINT32 reg_acness_sel                   :1;	//(0,RW,0x00) //
	UINT32 reg_g_motion_manual_en           :1;	//(1,RW,0x00) //
	UINT32 resvd0                           :6;
	UINT32 reg_ac_bnr_debug_h_en            :1;	//(8,RW,0x00) //
	UINT32 reg_ac_bnr_debug_v_en            :1;	//(9,RW,0x00) //
	UINT32 reg_ac_master_y_gain             :6;	//(15:10,RW,0x20) //0x20 is max
	UINT32 reg_g_motion_scale               :3;	//(18:16,RW,0x1) //
	UINT32 reg_g_motion_div                 :2;	//(20:19,RW,0x1) //
	UINT32 resvd1                           :10;
	UINT32 reg_ac_flt_level_sel             :1;	//(31,RW,0x0) //0 : weak, 1 : strong
	};
}PE_O26_DNR1_AC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0608 RW 0xFF00_FF00
	UINT32 reg_ac_detail_gain_y_min         :8;	//(7:0,RW,0x0) //detail gain y?
	UINT32 reg_ac_detail_gain_y_max         :8;	//(15:8,RW,0xFF) //detail gain y?
	UINT32 reg_bnr_ac_acness_y_min          :8;	//(23:16,RW,0x0) //acness gain y  ?
	UINT32 reg_bnr_ac_acness_y_max          :8;	//(31:24,RW,0xFF) //acness gain y  ?
	};
}PE_O26_DNR1_AC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C060C RW 0xFF00_FF00
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//(7:0,RW,0x0) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//(15:8,RW,0xFF) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//(23:16,RW,0x0) //ac bnr final mux?? ??? detail gain ? y?
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//(31:24,RW,0xFF) //ac bnr final mux?? ??? detail gain ? y?
	};
}PE_O26_DNR1_AC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0610 RW 0x0000_FFFF
	UINT32 reg_g_motion_manual              :8;	//(7:0,RW,0xFF) //
	UINT32 reg_acness_scale_mul             :8;	//(15:8,RW,0xFF) //
	UINT32 reg_bnr_ac_detail_max            :8;	//(23:16,RW,0x0) //
	UINT32 reg_bnr_ac_detail_min            :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0614 RW 0x00E8_D800
	UINT32 reg_y_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_y_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_y_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|? [7:0] ??	1: |y''|/4? [9:2] ??
	UINT32 resvd1                           :1;
	UINT32 reg_y_drvt2_hcoef_sel            :3;	//(10:8,RW,0x00) //5tap, h[0, 0, 8, 8, 0, -8, -8, -0, -0]/16	7tap, h[0, 4, 6, 6, 0, -6, -6, -4, -0]/16	9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_medge_meth                   :1;	//(11,RW,0x01) //0: 13x3 window (? ????? ???? ?? ??)	1 :13x3 window (?? ??? coring)
	UINT32 reg_medge_th                     :8;	//(19:12,RW,0x8D) //diff? th
	UINT32 reg_medge_coring_th              :8;	//(27:20,RW,0xE) //??? th
	UINT32 reg_medge_ch_tap                 :2;	//(29:28,RW,0x00) //0: 13tap	1: 11tap	2: 9tap
	UINT32 reg_edge_meth                    :2;	//(31:30,RW,0x00) //diff? center?? on/off
	};
}PE_O26_DNR1_IFC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0618 RW 0x0C00_3820
	UINT32 reg_edge_ddrvt_gain_y1           :8;	//(7:0,RW,0x20) //
	UINT32 reg_edge_ddrvt_gain_x1           :8;	//(15:8,RW,0x38) //
	UINT32 reg_edge_ddrvt_gain_y0           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_ddrvt_gain_x0           :8;	//(31:24,RW,0xC) //?? y edge gain
	};
}PE_O26_DNR1_IFC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C061C RW 0x0000_0000
	UINT32 reg_c_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_c_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_c_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|? [7:0] ??	1: |y''|/4? [9:2] ??
	UINT32 resvd1                           :25;
	};
}PE_O26_DNR1_IFC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0620 RW 0x1100_6E20
	UINT32 reg_c_edge_gain_y1               :8;	//(7:0,RW,0x20) //
	UINT32 reg_c_edge_gain_x1               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_c_edge_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_c_edge_gain_x0               :8;	//(31:24,RW,0x11) //
	};
}PE_O26_DNR1_IFC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0624 RW 0x0003_1203
	UINT32 reg_crs_para_tap                 :2;	//(1:0,RW,0x03) //0 : 5tap, h[0, 1, 1, 1, 1 ,1]	1 : 4tap, h[0, 0, 1, 1, 1, 1]	2 : 4tap, h[0, 1, 1, 1, 1, 0]	3 : 6tap, h[1, 1, 1, 1, 1, 1]
	UINT32 reg_cdst_th                      :10;	//(11:2,RW,0x080) //Cb, Cr ??? ? ? ????? ??
	UINT32 reg_crs_op_tap                   :2;	//(13:12,RW,0x01) //0 : 9 tap	1 : 7 tap	2 : 5 tap
	UINT32 reg_crs_gain_res                 :1;	//(14,RW,0x00) //0: |c diff|? [7:0] ??	1: |c diff|/4? [9:2] ??
	UINT32 resvd0                           :1;
	UINT32 reg_cdiff_hcoef_sel              :2;	//(17:16,RW,0x03) //left/right diff? coefficient (? ?? 255)	0 : h[0x00, 0x08, 0x08, 0x0A, 0x1E, 0xC8]/256	1 : h[0x00, 0x10, 0x10, 0x14, 0x40, 0x8C]/256
	UINT32 resvd1                           :10;
	UINT32 reg_crs_point                    :2;	//(29:28,RW,0x00) //
	UINT32 reg_crs_meth                     :2;	//(31:30,RW,0x00) //0 : (1??) +  L/R ?? ?? ???? ???	1 : (2??) +  L/R ?? ??? ???? 	2 : L/R?? chroma diff? threshold?? ??
	};
}PE_O26_DNR1_IFC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0628 RW 0x0000_6616
	UINT32 reg_crs_gain_y1                  :8;	//(7:0,RW,0x16) //
	UINT32 reg_crs_gain_x1                  :8;	//(15:8,RW,0x66) //
	UINT32 reg_crs_gain_y0                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_IFC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C062C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0630 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0634 RW 0x2400_0000
	UINT32 reg_ifc_en                       :1;	//(0,RW,0x00) //0 : 0ff / 1 : on
	UINT32 reg_clp_on                       :1;	//(1,RW,0x00) //0 : 0ff / 1 : Max clipping
	UINT32 resvd0                           :2;
	UINT32 reg_edge_en                      :1;	//(4,RW,0x00) //mmd en
	UINT32 resvd1                           :15;
	UINT32 reg_clp_tap                      :2;	//(21:20,RW,0x00) //0 : 13 tap	1 : 11 tap	2 : 9tap
	UINT32 reg_ifc_flt_sel                  :2;	//(23:22,RW,0x00) //3 : cross	2 : multi edge cedge	1 : yedge	0 : default
	UINT32 reg_debug_en                     :2;	//(25:24,RW,0x00) //0 : debug off	1 : blend debug on	2 : debug on
	UINT32 reg_debug_mode                   :4;	//(29:26,RW,0x09) //0 : operation mode	1 : cross check	2 : multi edge	3 : 	4 : cr edge gain	5 : cb edge gain	6 : y edge gain	7 : cross gain	8 : cross blend	9 : multi-edge blend	10 : 	11 : 2???	12 : 	13 : 1???
	UINT32 reg_bld_tap                      :2;	//(31:30,RW,0x00) //0: ?? 2? average	1: ?? 1?, center average
	};
}PE_O26_DNR1_IFC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0638 RW 0x0000_0000
	UINT32 reg_f0_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f0_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f1_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f0_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_ELLIPSE_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C063C RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_master               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_ELLIPSE_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0640 RW 0x0000_0000
	UINT32 reg_f1_h1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_w2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_offset               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_ELLIPSE_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0644 RW 0x8004_0000
	UINT32 resvd                            :16;
	UINT32 reg_crs_zero_th                  :8;	//(23:16,RW,0x4) //cross point?? cb-cr? 0?? ?? ???
	UINT32 reg_dst_cdst_th                  :8;	//(31:24,RW,0x80) //?? ????? cdst ?? ??
	};
}PE_O26_DNR1_IFC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0648 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C064C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0650 RW 0x0640_11FF
	UINT32 reg_medge_gain_y1                :8;	//(7:0,RW,0xFF) //
	UINT32 reg_medge_gain_x1                :8;	//(15:8,RW,0x11) //
	UINT32 reg_medge_gain_y0                :8;	//(23:16,RW,0x40) //
	UINT32 reg_medge_gain_x0                :8;	//(31:24,RW,0x6) //1/3?
	};
}PE_O26_DNR1_IFC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0654 RW 0x0010_02A2
	UINT32 reg_crs_op_gain_isel             :2;	//(1:0,RW,0x02) //0 : max	1 : min	2 : average
	UINT32 reg_crs_op_gain_res              :1;	//(2,RW,0x00) //0: [7:0] ??	1: [9:2] ??
	UINT32 reg_crs_cdst_flt                 :3;	//(5:3,RW,0x04) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd0                           :1;
	UINT32 reg_crs_cdst_vmdn                :1;	//(7,RW,0x01) //5x5 median/max (v->h)
	UINT32 reg_crs_cdst_op_flt              :3;	//(10:8,RW,0x02) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd1                           :5;
	UINT32 reg_op_wgain_coef1               :2;	//(17:16,RW,0x00) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef2               :2;	//(19:18,RW,0x00) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef3               :2;	//(21:20,RW,0x01) //cross filter? ??,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 resvd2                           :10;
	};
}PE_O26_DNR1_IFC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0658 RW 0x8500_DCFF
	UINT32 reg_crs_op_gain_y1               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_crs_op_gain_x1               :8;	//(15:8,RW,0xDC) //
	UINT32 reg_crs_op_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_op_gain_x0               :8;	//(31:24,RW,0x85) //
	};
}PE_O26_DNR1_IFC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C065C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0660 RW 0x2100_0000
	UINT32 resvd0                           :16;
	UINT32 reg_medge_op_th                  :8;	//(23:16,RW,0x0) //???? ?? ??? (3??, ???)
	UINT32 reg_mmd_gain_en                  :1;	//(24,RW,0x01) //
	UINT32 reg_mmd_gain_flt                 :2;	//(26:25,RW,0x00) //0: off	1: ???121
	UINT32 reg_mmd_gain_tap                 :2;	//(28:27,RW,0x00) //0: 13	1: 11	2: 9
	UINT32 reg_mmd_gain_res                 :1;	//(29,RW,0x01) //0: [7:0] ??	1: [9:2] ??
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR1_IFC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0664 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_IFC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0668 RW 0x0080_B000
	UINT32 reg_mmd_gain_y1                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_gain_x1                  :8;	//(15:8,RW,0xB0) //
	UINT32 reg_mmd_gain_y0                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_mmd_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_IFC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C066C RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_sel_output                   :1;	//(24,RW,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0670 RW 0x0000_0000
	UINT32 reg_f1_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f1_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f1_w2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f3_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f2_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_ELLIPSE_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0674 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_SC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0678 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_SC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C067C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_SC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0680 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_SC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0684 RW 0x0000_0100
	UINT32 reg_f2_h2_pos                    :12;	//(11:0,RW,0x100) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0688 RW 0x0000_0000
	UINT32 pre_121_blur_en                  :1;	//(0,RW,0x00) //
	UINT32 pre_median_en                    :1;	//(1,RW,0x00) //
	UINT32 resvd                            :30;
	};
}PE_O26_DNR1_C_PRE_BLUR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C068C RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0690 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f2_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0694 RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f3_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0698 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f3_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_ELLIPSE_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C069C RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_h_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_h                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06A0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_v_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_v                :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_AC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06A4 RW 0x4030_2010
	UINT32 reg_fil_motion_x_th0             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th1             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th2             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th3             :8;	//(31:24,RW,0x40) //
	};
}PE_O26_DNR1_DC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06A8 RW 0xFF60_4020
	UINT32 reg_fil_motion_y_th0             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th1             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th2             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th3             :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_DNR1_DC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06AC RW 0x3020_1001
	UINT32 reg_mmd_sel                      :2;	//(1:0,RW,0x01) //0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//(15:8,RW,0x10) //
	UINT32 reg_hist_bin_th1                 :8;	//(23:16,RW,0x20) //
	UINT32 reg_hist_bin_th2                 :8;	//(31:24,RW,0x30) //
	};
}PE_O26_DNR1_SQM_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06B0 RW 0x7060_5040
	UINT32 reg_hist_bin_th3                 :8;	//(7:0,RW,0x40) //
	UINT32 reg_hist_bin_th4                 :8;	//(15:8,RW,0x50) //
	UINT32 reg_hist_bin_th5                 :8;	//(23:16,RW,0x60) //
	UINT32 reg_hist_bin_th6                 :8;	//(31:24,RW,0x70) //
	};
}PE_O26_DNR1_SQM_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06B4 RW 0x0461_E046
	UINT32 reg_trans_mmd_th                 :8;	//(7:0,RW,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//(19:10,RW,0x78) //
	UINT32 reg_edf_mmd_th                   :8;	//(27:20,RW,0x46) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_SQM_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06B8 RW 0x0000_0000
	UINT32 reg_sqm_win_mode_x1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//(30,RW,0x00) //
	UINT32 reg_sqm_win_mode_en              :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR1_SQM_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06BC RW 0x0000_0000
	UINT32 reg_sqm_win_mode_y1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR1_SQM_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06C0 RW 0x0000_0080
	UINT32 reg_tp_binary_th                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}PE_O26_DNR1_TPD_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06C4 RW 0x0000_0000
	UINT32 reg_win_mode_x1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_x0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_win_mode_mode                :1;	//(30,RW,0x00) //0: inside, 1: outside
	UINT32 reg_win_mode_en                  :1;	//(31,RW,0x00) //
	};
}PE_O26_DNR1_WINDOW_MODE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06C8 RW 0x0000_0000
	UINT32 reg_win_mode_y1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_y0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_DNR1_WINDOW_MODE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06D0 RO 0x0000_0000
	UINT32 acness_v_g                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v                         :8;	//(23:16,RO,0x0) //
	UINT32 acness_h                         :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06D4 RO 0x0000_0000
	UINT32 bad_up_cnt                       :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 acness_v_l                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06D8 RO 0x0000_0000
	UINT32 acness_gain_v_l                  :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h_l                  :8;	//(15:8,RO,0x0) //
	UINT32 acness_gain_v_g                  :8;	//(23:16,RO,0x0) //
	UINT32 acness_gain_h_g                  :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_DNR_STAT_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06E0 RO 0x0000_0000
	UINT32 acness_gain_v                    :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h                    :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_iir                     :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_iir                     :8;	//(31:24,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06E4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_DNR_STAT_8_SC_BNR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06E8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_DNR_STAT_9_SC_BNR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06EC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_DNR_STAT_10_SC_BNR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06F0 RO 0x0000_0000
	UINT32 e_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_11_SQM_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06F4 RO 0x0000_0000
	UINT32 e_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_12_SQM_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06F8 RO 0x0000_0000
	UINT32 e_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_13_SQM_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C06FC RO 0x0000_0000
	UINT32 e_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_14_SQM_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0700 RO 0x0000_0000
	UINT32 f_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_15_SQM_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0704 RO 0x0000_0000
	UINT32 f_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_16_SQM_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0708 RO 0x0000_0000
	UINT32 f_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_17_SQM_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C070C RO 0x0000_0000
	UINT32 f_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_18_SQM_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0710 RO 0x0000_0000
	UINT32 t_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_19_SQM_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0714 RO 0x0000_0000
	UINT32 t_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_20_SQM_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0718 RO 0x0000_0000
	UINT32 t_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_21_SQM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C071C RO 0x0000_0000
	UINT32 t_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_22_SQM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0720 RO 0x0000_0000
	UINT32 res_h_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_23_TPD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0724 RO 0x0000_0000
	UINT32 res_v_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_v_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_24_TPD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0728 RO 0x0000_0000
	UINT32 res_v_cnt_3                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_3                      :16;	//(31:16,RO,0x0) //
	};
}PE_O26_DNR1_DNR_STAT_25_TPD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0730 RW 0x40302010
	UINT32 reg_fil_motion_x_th3             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th2             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th1             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th0             :8;	//(31:24,RW,0x40) //
	};
}PE_O26_DNR1_AC_BNR_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0734 RW 0xFF604020
	UINT32 reg_fil_motion_y_th3             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th2             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th1             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th0             :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_DNR1_AC_BNR_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0738 RW 0x0000_0000
	UINT32 reg_tearing_y_1                  :4;	//(3:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tearing_y_0                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_tearing_x_1                  :4;	//(19:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_tearing_x_0                  :4;	//(27:24,RW,0x0) //
	UINT32 resvd3                           :4;
	};
}PE_O26_DNR1_VFILTER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C073C RW 0x0000_0000
	UINT32 reg_motion_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0740 RW 0x0000_0000
	UINT32 reg_motion_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0744 RW 0x0000_0000
	UINT32 reg_global_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0748 RW 0x0000_0000
	UINT32 reg_global_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C074C RW 0x0000_0000
	UINT32 reg_blend_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0750 RW 0x0000_0000
	UINT32 reg_blend_y_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0754 RW 0x0000_0000
	UINT32 reg_hmc_x_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_x_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_x_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_x_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0758 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_y_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_y_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_y_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C075C RW 0x0000_0000
	UINT32 reg_local_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0760 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_VFILTER_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0764 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//(1,RW,0x0) //(not used in m16p3), 11b mode?? 10b ???, ?? ?.
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //(not used in m16p3), 11b mode?? 10b ???, ?? ?.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ? ??)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //0: 12-bit full	1: 1st_out_rd ?? /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0768 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C076C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0770 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0774 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0778 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C077C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0780 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0784 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0788 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C078C RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0790 RW 0x0000_0000
	UINT32 reg_gain_x3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0794 RW 0x0000_0000
	UINT32 reg_gain_x7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0798 RW 0x0000_0000
	UINT32 reg_gain_y3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C079C RW 0x0000_0000
	UINT32 reg_gain_y7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07A0 RW 0x0000_0000
	UINT32 reg_lti_en                       :1;	//(0,RW,0x0) //
	UINT32 reg_lti_clipping_mode            :1;	//(1,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap                      :2;	//(4:3,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_lti_gain                     :8;	//(15:8,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_ycm_c_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_ycm_y_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_ycm_band_sel                 :3;	//(30:28,RW,0x0) //
	UINT32 reg_ycm_en                       :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_CTI_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07A4 RW 0x0000_0000
	UINT32 reg_lti_coring_th0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lti_coring_th1               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lti_coring_sm                :3;	//(18:16,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//(21:20,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_CTI_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07A8 RW 0x0000_0000
	UINT32 reg_small_mmd_flat_th            :8;	//(7:0,NA,0x0) //
	UINT32 reg_large_mmd_flat_th            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//(28,NA,0x0) //
	UINT32 reg_mmd_dist_kernal_width        :2;	//(30:29,NA,0x0) //
	UINT32 reg_mmd_dist_gain_en             :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07AC RW 0x0000_0000
	UINT32 reg_dist_gain_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07B0 RW 0x0000_0000
	UINT32 reg_dist_gain_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07B4 RW 0x0000_0000
	UINT32 reg_chroma_gain_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07B8 RW 0x0000_0000
	UINT32 reg_chroma_gain_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07BC RW 0x0000_0000
	UINT32 reg_i_sel_mmd_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07C0 RW 0x0000_0000
	UINT32 reg_i_sel_mmd_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_MNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07C4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07C8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07CC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07D0 RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07D4 RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07D8 RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07DC RW 0x0000_0000
	UINT32 reg_blur_lb_var_cut_res          :4;	//(3:0,RW,0x0) //>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//(6,RW,0x0) //
	UINT32 reg_l6_var_2x2_bit               :1;	//(7,RW,0x0) //12b? L6_var? 10b?? cut? ?, 1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//(13:8,RW,0x0) //
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 reg_l6_var_csc_en                :1;	//(15,RW,0x0) //ND?? ?? ? ?
	UINT32 reg_force_block_no_h             :6;	//(21:16,RW,0x0) //
	UINT32 reg_4k_5x3_mode_en               :1;	//(22,RW,0x0) //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode?? 10b ???, ?? ?.
	UINT32 reg_rd_clip                      :1;	//(24,RW,0x0) //11b mode?? 10b ???, ?? ?.
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//(29:26,RW,0x0) //0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: aux_luma	15: input_blur
	UINT32 reg_force_block_no_en            :1;	//(30,RW,0x0) //
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07E0 RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x0) //
	UINT32 reg_low_gain_en                  :1;	//(1,RW,0x0) //O24 New	Low gain(var, diff, var, aux_luma) enable	Debug mode is same
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x0) //0: new_2x2, 1: new_3x3
	UINT32 resvd0                           :1;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x0) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x0) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20
	UINT32 resvd1                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07E4 RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07E8 RW 0x0000_0000
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07EC RW 0x0000_0000
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07F0 RW 0x0000_0000
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07F4 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07F8 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C07FC RW 0x0000_0000
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0800 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0804 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0808 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C080C RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //
	UINT32 resvd3                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0810 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//(19:16,RW,0x0) //
	UINT32 reg_diff_shift                   :3;	//(22:20,RW,0x0) //
	UINT32 reg_osd_run_mode                 :1;	//(23,RW,0x0) //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//(24,RW,0x0) //
	UINT32 reg_alpha_blur_mode              :2;	//(26:25,RW,0x0) //0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//(28:27,RW,0x0) //
	UINT32 reg_diff_use_seldiff             :1;	//(29,RW,0x0) //
	UINT32 reg_diff_calc_mode               :2;	//(31:30,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0814 RW 0x0000_0000
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x0) //not used in m16p3
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x0) //not used in m16p3
	UINT32 reg_lb_var_cut_res               :4;	//(23:20,RW,0x0) //cut resolution after (var * LB_var)
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0818 RW 0x0000_0000
	UINT32 reg_l6_var_x_th2                 :10;	//(9:0,RW,0x0) //revived in O20
	UINT32 reg_l6_var_x_th1                 :10;	//(19:10,RW,0x0) //revived in O20
	UINT32 reg_l6_var_x_th0                 :10;	//(29:20,RW,0x0) //revived in O20
	UINT32 reg_lb_var_opt                   :1;	//(30,RW,0x0) //0: L6_var, 1: L6_var 2x2smooth
	UINT32 reg_lb_var_en                    :1;	//(31,RW,0x0) //use L6_var when making var map
	};
}PE_O26_DNR1_REG_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C081C RW 0x0000_0000
	UINT32 reg_l6_var_y_th1                 :10;	//(9:0,RW,0x0) //revived in O20
	UINT32 reg_l6_var_y_th0                 :10;	//(19:10,RW,0x0) //revived in O20
	UINT32 reg_l6_var_x_th3                 :10;	//(29:20,RW,0x0) //revived in O20
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0820 RW 0x0000_0000
	UINT32 reg_l6_var_y_th3                 :10;	//(9:0,RW,0x0) //revived in O20
	UINT32 reg_l6_var_y_th2                 :10;	//(19:10,RW,0x0) //revived in O20
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x0) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x0) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0824 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0828 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C082C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0830 RW 0x0000_0000
	UINT32 reg_rd_min_pel_cb                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_min_pel_yy                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_on                  :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0834 RW 0x0000_0000
	UINT32 reg_rd_max_pel_yy                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_min_pel_cr                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0838 RW 0x0000_0000
	UINT32 reg_rd_max_pel_cr                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_max_pel_cb                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C083C RW 0x0000_0000
	UINT32 reg_rd_init_yy                   :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0840 RW 0x0000_0000
	UINT32 reg_rd_init_cb                   :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0844 RW 0x0000_0000
	UINT32 reg_rd_init_cr                   :32;	//(31:0,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0848 RW 0x0000_0000
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C084C RW 0x0000_0000
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0850 RW 0x0000_0000
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x0) //
	UINT32 reg_blur2_sim_en                 :1;	//(29,RW,0x0) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0854 RW 0x0000_0000
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x0) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0858 RW 0x0000_0000
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C085C RW 0x0000_0000
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0860 RW 0x0000_0000
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0864 RW 0x0000_0000
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0868 RW 0x0000_0000
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C086C RW 0x0000_0000
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0870 RW 0x0000_0000
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0874 RW 0x0000_0000
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0878 RW 0x0000_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0x0) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C087C RW 0x0000_0000
	UINT32 reg_l6_var_diff_dist_h           :4;	//(3:0,RW,0x0) //
	UINT32 reg_l6_var_diff_dist_w           :4;	//(7:4,RW,0x0) //
	UINT32 resvd                            :24;
	};
}PE_O26_DNR1_REG_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0880 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_cr            :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_cb            :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_yy            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0884 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_yy3           :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_yy2           :10;	//(19:10,RW,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O26_DNR1_REG_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0888 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C088C RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//(31,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0890 RW 0x0000_0000
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//(7:0,RW,0x0) //
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0894 RW 0x0000_0000
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//(7:0,RW,0x0) //
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0898 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C089C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DC_BNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08A8 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08AC RW 0x0000_0000
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_v_diff_th             :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08B0 RW 0x0000_0000
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_h_diff_th             :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08B4 RW 0x0000_0000
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_max_th     :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08B8 RW 0x0000_0000
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_low_th     :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_DNR1_REG_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08BC RW 0x0000_0000
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x0) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x0) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x0) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_O26_DNR1_REG_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08C0 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_REG_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08C4 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_DNR1_REG_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08C8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x0) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}PE_O26_DNR1_REG_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08CC RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x0) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}PE_O26_DNR1_REG_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08D0 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08D4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08D8 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08DC RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08E0 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08E4 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}PE_O26_DNR1_REG_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08E8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08EC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_DNR1_REG_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08F4 RW 0x0000_0000
	UINT32 reg_boundary_x_end               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_boundary_x_start             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_boundary_side                :1;	//(30,NA,0x0) //0: left, 1: right
	UINT32 reg_boundary_en                  :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08F8 RW 0x0000_0000
	UINT32 reg_decon_low_diff_x_th0         :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th1         :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th2         :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th3         :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C08FC RW 0x0000_0000
	UINT32 reg_decon_low_diff_y_th0         :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th1         :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th2         :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th3         :8;	//(31:24,NA,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0900 RW 0x0000_0000
	UINT32 reg_decon_low_var_x_th2          :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_x_th1          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_x_th0          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0904 RW 0x0000_0000
	UINT32 reg_decon_low_var_y_th1          :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_y_th0          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_x_th3          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0908 RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th0         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_y_th3          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_y_th2          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C090C RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th2         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th1         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0910 RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th6         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th5         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th4         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0914 RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th7         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0918 RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th4         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th3         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th2         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C091C RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th7         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th6         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th5         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0920 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,NA,0x0) //
	UINT32 reg_low_aux_luma_en              :1;	//(30,NA,0x0) //
	UINT32 reg_aux_luma_en                  :1;	//(31,NA,0x0) //
	};
}PE_O26_DNR1_REG_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0924 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0928 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C092C RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0930 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0934 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th1     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th0     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0938 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th4     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th3     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th2     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C093C RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th7     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th6     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th5     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0940 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_y_th2     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th1     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th0     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0944 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_y_th5     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th4     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th3     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C0948 RW 0x0000_0000
	UINT32 reg_low_master_gain              :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_decon_low_aux_luma_y_th7     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th6     :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_DNR1_REG_DECON_CTRL_104_T;

typedef struct {
	PE_O26_DNR1_PE0_LOAD_T                                        pe0_load;	//0xCC2C0500
	PE_O26_DNR1_PE0_INTR_T                                        pe0_intr;	//0xCC2C0504
	PE_O26_DNR1_PE0_STATUS0_T                                  pe0_status0;	//0xCC2C0508
	PE_O26_DNR1_PE0_STATUS1_T                                  pe0_status1;	//0xCC2C050C
	PE_O26_DNR1_PE0_OPMODE_T                                    pe0_opmode;	//0xCC2C0510
	PE_O26_DNR1_PE0_IN_SIZE_T                                  pe0_in_size;	//0xCC2C0514
	PE_O26_DNR1_PE0_IN_OFFSET_T                              pe0_in_offset;	//0xCC2C0518
	PE_O26_DNR1_PE0_OUT_SIZE_T                                pe0_out_size;	//0xCC2C051C
	PE_O26_DNR1_WIN_CTRL_0_T                                    win_ctrl_0;	//0xCC2C0520
	PE_O26_DNR1_WIN_CTRL_1_T                                    win_ctrl_1;	//0xCC2C0524
	PE_O26_DNR1_WIN_CTRL_2_T                                    win_ctrl_2;	//0xCC2C0528
	PE_O26_DNR1_WIN_CTRL_3_T                                    win_ctrl_3;	//0xCC2C052C
	PE_O26_DNR1_CUP_CTRL_00_T                                  cup_ctrl_00;	//0xCC2C0530
	PE_O26_DNR1_CUP_CTRL_01_T                                  cup_ctrl_01;	//0xCC2C0534
	PE_O26_DNR1_CUP_CTRL_02_T                                  cup_ctrl_02;	//0xCC2C0538
	UINT32                                                       reserved0;	//0xCC2C053C
	UINT32                                                       reserved1;	//0xCC2C0540
	UINT32                                                       reserved2;	//0xCC2C0544
	UINT32                                                       reserved3;	//0xCC2C0548
	UINT32                                                       reserved4;	//0xCC2C054C
	UINT32                                                       reserved5;	//0xCC2C0550
	UINT32                                                       reserved6;	//0xCC2C0554
	UINT32                                                       reserved7;	//0xCC2C0558
	UINT32                                                       reserved8;	//0xCC2C055C
	UINT32                                                       reserved9;	//0xCC2C0560
	UINT32                                                       reserved10;	//0xCC2C0564
	UINT32                                                       reserved11;	//0xCC2C0568
	UINT32                                                       reserved12;	//0xCC2C056C
	UINT32                                                       reserved13;	//0xCC2C0570
	UINT32                                                       reserved14;	//0xCC2C0574
	UINT32                                                       reserved15;	//0xCC2C0578
	UINT32                                                       reserved16;	//0xCC2C057C
	PE_O26_DNR1_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0xCC2C0580
	PE_O26_DNR1_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0xCC2C0584
	PE_O26_DNR1_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0xCC2C0588
	PE_O26_DNR1_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xCC2C058C
	PE_O26_DNR1_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xCC2C0590
	PE_O26_DNR1_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCC2C0594
	PE_O26_DNR1_DNR_DBAR_CTRL_T                              dnr_dbar_ctrl;	//0xCC2C0598
	PE_O26_DNR1_REG_C420_CTRL_T                              reg_c420_ctrl;	//0xCC2C059C
	PE_O26_DNR1_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCC2C05A0
	PE_O26_DNR1_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCC2C05A4
	PE_O26_DNR1_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCC2C05A8
	PE_O26_DNR1_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCC2C05AC
	PE_O26_DNR1_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCC2C05B0
	PE_O26_DNR1_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCC2C05B4
	PE_O26_DNR1_DETAIL_CTRL_T                                  detail_ctrl;	//0xCC2C05B8
	PE_O26_DNR1_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCC2C05BC
	PE_O26_DNR1_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCC2C05C0
	PE_O26_DNR1_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCC2C05C4
	PE_O26_DNR1_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCC2C05C8
	PE_O26_DNR1_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCC2C05CC
	PE_O26_DNR1_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCC2C05D0
	PE_O26_DNR1_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCC2C05D4
	PE_O26_DNR1_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCC2C05D8
	PE_O26_DNR1_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCC2C05DC
	PE_O26_DNR1_DNR_STAT_0_T                                    dnr_stat_0;	//0xCC2C05E0
	PE_O26_DNR1_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCC2C05E4
	PE_O26_DNR1_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCC2C05E8
	PE_O26_DNR1_DNR_STAT_1_T                                    dnr_stat_1;	//0xCC2C05EC
	PE_O26_DNR1_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCC2C05F0
	PE_O26_DNR1_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCC2C05F4
	PE_O26_DNR1_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCC2C05F8
	PE_O26_DNR1_DNR_STAT_2_T                                    dnr_stat_2;	//0xCC2C05FC
	PE_O26_DNR1_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCC2C0600
	PE_O26_DNR1_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCC2C0604
	PE_O26_DNR1_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCC2C0608
	PE_O26_DNR1_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCC2C060C
	PE_O26_DNR1_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCC2C0610
	PE_O26_DNR1_IFC_CTRL_0_T                                    ifc_ctrl_0;	//0xCC2C0614
	PE_O26_DNR1_IFC_CTRL_1_T                                    ifc_ctrl_1;	//0xCC2C0618
	PE_O26_DNR1_IFC_CTRL_2_T                                    ifc_ctrl_2;	//0xCC2C061C
	PE_O26_DNR1_IFC_CTRL_3_T                                    ifc_ctrl_3;	//0xCC2C0620
	PE_O26_DNR1_IFC_CTRL_4_T                                    ifc_ctrl_4;	//0xCC2C0624
	PE_O26_DNR1_IFC_CTRL_5_T                                    ifc_ctrl_5;	//0xCC2C0628
	PE_O26_DNR1_IFC_CTRL_6_T                                    ifc_ctrl_6;	//0xCC2C062C
	PE_O26_DNR1_IFC_CTRL_7_T                                    ifc_ctrl_7;	//0xCC2C0630
	PE_O26_DNR1_IFC_CTRL_8_T                                    ifc_ctrl_8;	//0xCC2C0634
	PE_O26_DNR1_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCC2C0638
	PE_O26_DNR1_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCC2C063C
	PE_O26_DNR1_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCC2C0640
	PE_O26_DNR1_IFC_CTRL_12_T                                  ifc_ctrl_12;	//0xCC2C0644
	PE_O26_DNR1_IFC_CTRL_13_T                                  ifc_ctrl_13;	//0xCC2C0648
	PE_O26_DNR1_IFC_CTRL_14_T                                  ifc_ctrl_14;	//0xCC2C064C
	PE_O26_DNR1_IFC_CTRL_15_T                                  ifc_ctrl_15;	//0xCC2C0650
	PE_O26_DNR1_IFC_CTRL_16_T                                  ifc_ctrl_16;	//0xCC2C0654
	PE_O26_DNR1_IFC_CTRL_17_T                                  ifc_ctrl_17;	//0xCC2C0658
	PE_O26_DNR1_IFC_CTRL_18_T                                  ifc_ctrl_18;	//0xCC2C065C
	PE_O26_DNR1_IFC_CTRL_19_T                                  ifc_ctrl_19;	//0xCC2C0660
	PE_O26_DNR1_IFC_CTRL_20_T                                  ifc_ctrl_20;	//0xCC2C0664
	PE_O26_DNR1_IFC_CTRL_21_T                                  ifc_ctrl_21;	//0xCC2C0668
	PE_O26_DNR1_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCC2C066C
	PE_O26_DNR1_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCC2C0670
	PE_O26_DNR1_SC_BNR_CTRL_2_T                              sc_bnr_ctrl_2;	//0xCC2C0674
	PE_O26_DNR1_SC_BNR_CTRL_3_T                              sc_bnr_ctrl_3;	//0xCC2C0678
	PE_O26_DNR1_SC_BNR_CTRL_4_T                              sc_bnr_ctrl_4;	//0xCC2C067C
	PE_O26_DNR1_SC_BNR_CTRL_5_T                              sc_bnr_ctrl_5;	//0xCC2C0680
	PE_O26_DNR1_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCC2C0684
	PE_O26_DNR1_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCC2C0688
	PE_O26_DNR1_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCC2C068C
	PE_O26_DNR1_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCC2C0690
	PE_O26_DNR1_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCC2C0694
	PE_O26_DNR1_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCC2C0698
	PE_O26_DNR1_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCC2C069C
	PE_O26_DNR1_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCC2C06A0
	PE_O26_DNR1_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCC2C06A4
	PE_O26_DNR1_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCC2C06A8
	PE_O26_DNR1_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCC2C06AC
	PE_O26_DNR1_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCC2C06B0
	PE_O26_DNR1_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCC2C06B4
	PE_O26_DNR1_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCC2C06B8
	PE_O26_DNR1_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCC2C06BC
	PE_O26_DNR1_TPD_CTRL_0_T                                    tpd_ctrl_0;	//0xCC2C06C0
	PE_O26_DNR1_WINDOW_MODE_0_T                              window_mode_0;	//0xCC2C06C4
	PE_O26_DNR1_WINDOW_MODE_1_T                              window_mode_1;	//0xCC2C06C8
	UINT32                                                       reserved17;	//0xCC2C06CC
	PE_O26_DNR1_DNR_STAT_3_T                                    dnr_stat_3;	//0xCC2C06D0
	PE_O26_DNR1_DNR_STAT_4_T                                    dnr_stat_4;	//0xCC2C06D4
	PE_O26_DNR1_DNR_STAT_5_T                                    dnr_stat_5;	//0xCC2C06D8
	PE_O26_DNR1_DNR_STAT_6_T                                    dnr_stat_6;	//0xCC2C06DC
	PE_O26_DNR1_DNR_STAT_7_T                                    dnr_stat_7;	//0xCC2C06E0
	PE_O26_DNR1_DNR_STAT_8_SC_BNR0_T                    dnr_stat_8_sc_bnr0;	//0xCC2C06E4
	PE_O26_DNR1_DNR_STAT_9_SC_BNR1_T                    dnr_stat_9_sc_bnr1;	//0xCC2C06E8
	PE_O26_DNR1_DNR_STAT_10_SC_BNR2_T                  dnr_stat_10_sc_bnr2;	//0xCC2C06EC
	PE_O26_DNR1_DNR_STAT_11_SQM_00_T                    dnr_stat_11_sqm_00;	//0xCC2C06F0
	PE_O26_DNR1_DNR_STAT_12_SQM_01_T                    dnr_stat_12_sqm_01;	//0xCC2C06F4
	PE_O26_DNR1_DNR_STAT_13_SQM_02_T                    dnr_stat_13_sqm_02;	//0xCC2C06F8
	PE_O26_DNR1_DNR_STAT_14_SQM_03_T                    dnr_stat_14_sqm_03;	//0xCC2C06FC
	PE_O26_DNR1_DNR_STAT_15_SQM_04_T                    dnr_stat_15_sqm_04;	//0xCC2C0700
	PE_O26_DNR1_DNR_STAT_16_SQM_05_T                    dnr_stat_16_sqm_05;	//0xCC2C0704
	PE_O26_DNR1_DNR_STAT_17_SQM_06_T                    dnr_stat_17_sqm_06;	//0xCC2C0708
	PE_O26_DNR1_DNR_STAT_18_SQM_07_T                    dnr_stat_18_sqm_07;	//0xCC2C070C
	PE_O26_DNR1_DNR_STAT_19_SQM_08_T                    dnr_stat_19_sqm_08;	//0xCC2C0710
	PE_O26_DNR1_DNR_STAT_20_SQM_09_T                    dnr_stat_20_sqm_09;	//0xCC2C0714
	PE_O26_DNR1_DNR_STAT_21_SQM_10_T                    dnr_stat_21_sqm_10;	//0xCC2C0718
	PE_O26_DNR1_DNR_STAT_22_SQM_11_T                    dnr_stat_22_sqm_11;	//0xCC2C071C
	PE_O26_DNR1_DNR_STAT_23_TPD_0_T                      dnr_stat_23_tpd_0;	//0xCC2C0720
	PE_O26_DNR1_DNR_STAT_24_TPD_1_T                      dnr_stat_24_tpd_1;	//0xCC2C0724
	PE_O26_DNR1_DNR_STAT_25_TPD_2_T                      dnr_stat_25_tpd_2;	//0xCC2C0728
	UINT32                                                       reserved18;	//0xCC2C072C
	PE_O26_DNR1_AC_BNR_15_T                                      ac_bnr_15;	//0xCC2C0730
	PE_O26_DNR1_AC_BNR_16_T                                      ac_bnr_16;	//0xCC2C0734
	PE_O26_DNR1_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0xCC2C0738
	PE_O26_DNR1_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0xCC2C073C
	PE_O26_DNR1_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0xCC2C0740
	PE_O26_DNR1_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0xCC2C0744
	PE_O26_DNR1_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0xCC2C0748
	PE_O26_DNR1_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0xCC2C074C
	PE_O26_DNR1_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0xCC2C0750
	PE_O26_DNR1_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0xCC2C0754
	PE_O26_DNR1_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0xCC2C0758
	PE_O26_DNR1_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0xCC2C075C
	PE_O26_DNR1_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0xCC2C0760
	PE_O26_DNR1_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCC2C0764
	PE_O26_DNR1_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCC2C0768
	PE_O26_DNR1_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCC2C076C
	PE_O26_DNR1_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCC2C0770
	PE_O26_DNR1_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCC2C0774
	PE_O26_DNR1_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCC2C0778
	PE_O26_DNR1_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCC2C077C
	PE_O26_DNR1_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCC2C0780
	PE_O26_DNR1_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCC2C0784
	PE_O26_DNR1_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCC2C0788
	PE_O26_DNR1_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCC2C078C
	PE_O26_DNR1_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCC2C0790
	PE_O26_DNR1_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCC2C0794
	PE_O26_DNR1_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCC2C0798
	PE_O26_DNR1_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCC2C079C
	PE_O26_DNR1_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xCC2C07A0
	PE_O26_DNR1_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xCC2C07A4
	PE_O26_DNR1_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCC2C07A8
	PE_O26_DNR1_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCC2C07AC
	PE_O26_DNR1_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCC2C07B0
	PE_O26_DNR1_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCC2C07B4
	PE_O26_DNR1_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCC2C07B8
	PE_O26_DNR1_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCC2C07BC
	PE_O26_DNR1_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCC2C07C0
	PE_O26_DNR1_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCC2C07C4
	PE_O26_DNR1_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCC2C07C8
	PE_O26_DNR1_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCC2C07CC
	PE_O26_DNR1_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCC2C07D0
	PE_O26_DNR1_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCC2C07D4
	PE_O26_DNR1_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCC2C07D8
	PE_O26_DNR1_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCC2C07DC
	PE_O26_DNR1_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCC2C07E0
	PE_O26_DNR1_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCC2C07E4
	PE_O26_DNR1_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCC2C07E8
	PE_O26_DNR1_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCC2C07EC
	PE_O26_DNR1_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCC2C07F0
	PE_O26_DNR1_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCC2C07F4
	PE_O26_DNR1_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCC2C07F8
	PE_O26_DNR1_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCC2C07FC
	PE_O26_DNR1_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCC2C0800
	PE_O26_DNR1_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCC2C0804
	PE_O26_DNR1_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCC2C0808
	PE_O26_DNR1_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCC2C080C
	PE_O26_DNR1_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCC2C0810
	PE_O26_DNR1_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCC2C0814
	PE_O26_DNR1_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCC2C0818
	PE_O26_DNR1_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCC2C081C
	PE_O26_DNR1_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCC2C0820
	PE_O26_DNR1_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCC2C0824
	PE_O26_DNR1_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCC2C0828
	PE_O26_DNR1_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCC2C082C
	PE_O26_DNR1_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCC2C0830
	PE_O26_DNR1_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCC2C0834
	PE_O26_DNR1_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCC2C0838
	PE_O26_DNR1_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCC2C083C
	PE_O26_DNR1_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCC2C0840
	PE_O26_DNR1_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCC2C0844
	PE_O26_DNR1_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCC2C0848
	PE_O26_DNR1_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCC2C084C
	PE_O26_DNR1_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCC2C0850
	PE_O26_DNR1_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCC2C0854
	PE_O26_DNR1_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCC2C0858
	PE_O26_DNR1_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCC2C085C
	PE_O26_DNR1_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCC2C0860
	PE_O26_DNR1_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCC2C0864
	PE_O26_DNR1_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCC2C0868
	PE_O26_DNR1_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCC2C086C
	PE_O26_DNR1_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCC2C0870
	PE_O26_DNR1_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCC2C0874
	PE_O26_DNR1_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCC2C0878
	PE_O26_DNR1_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCC2C087C
	PE_O26_DNR1_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCC2C0880
	PE_O26_DNR1_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCC2C0884
	PE_O26_DNR1_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCC2C0888
	PE_O26_DNR1_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCC2C088C
	PE_O26_DNR1_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCC2C0890
	PE_O26_DNR1_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCC2C0894
	PE_O26_DNR1_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCC2C0898
	PE_O26_DNR1_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCC2C089C
	PE_O26_DNR1_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCC2C08A0
	PE_O26_DNR1_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCC2C08A4
	PE_O26_DNR1_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCC2C08A8
	PE_O26_DNR1_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCC2C08AC
	PE_O26_DNR1_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCC2C08B0
	PE_O26_DNR1_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCC2C08B4
	PE_O26_DNR1_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCC2C08B8
	PE_O26_DNR1_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCC2C08BC
	PE_O26_DNR1_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCC2C08C0
	PE_O26_DNR1_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCC2C08C4
	PE_O26_DNR1_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCC2C08C8
	PE_O26_DNR1_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCC2C08CC
	PE_O26_DNR1_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCC2C08D0
	PE_O26_DNR1_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCC2C08D4
	PE_O26_DNR1_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCC2C08D8
	PE_O26_DNR1_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCC2C08DC
	PE_O26_DNR1_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCC2C08E0
	PE_O26_DNR1_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCC2C08E4
	PE_O26_DNR1_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCC2C08E8
	PE_O26_DNR1_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCC2C08EC
	PE_O26_DNR1_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCC2C08F0
	PE_O26_DNR1_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC2C08F4
	PE_O26_DNR1_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC2C08F8
	PE_O26_DNR1_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC2C08FC
	PE_O26_DNR1_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC2C0900
	PE_O26_DNR1_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC2C0904
	PE_O26_DNR1_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC2C0908
	PE_O26_DNR1_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC2C090C
	PE_O26_DNR1_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC2C0910
	PE_O26_DNR1_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC2C0914
	PE_O26_DNR1_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC2C0918
	PE_O26_DNR1_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC2C091C
	PE_O26_DNR1_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC2C0920
	PE_O26_DNR1_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC2C0924
	PE_O26_DNR1_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC2C0928
	PE_O26_DNR1_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC2C092C
	PE_O26_DNR1_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC2C0930
	PE_O26_DNR1_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC2C0934
	PE_O26_DNR1_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC2C0938
	PE_O26_DNR1_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC2C093C
	PE_O26_DNR1_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC2C0940
	PE_O26_DNR1_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC2C0944
	PE_O26_DNR1_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC2C0948
}PE_DNR1_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2911-- RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291104 copy from MNR_CTRL_0
	UINT32 reg_mnr_enable                   :1;	//(0,RW,0x00) //
	UINT32 reg_mnr_debug                    :1;	//(1,RW,0x00) //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//(2,RW,0x00) //
	UINT32 reg_mnr_chroma_en                :1;	//(3,RW,0x00) //
	UINT32 reg_h_expand                     :2;	//(5:4,RW,0x0) //0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//(7:6,RW,0x00) //0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//(15:8,RW,0x0) //
	UINT32 reg_snr_th                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_th_max                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291108 copy from MNR_CTRL_3
	UINT32 reg_blur_sel 					:1; //0 //
	UINT32 reg_pattern_en					:1; //1 //
	UINT32 resvd							:6;
	UINT32 reg_pattern_th					:8; //15:8	//
	UINT32 reg_equal_th 					:8; //23:16 //
	UINT32 reg_mmd_scale					:8; //31:24 //
	};
}PE_O26_ND0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29110C copy from MNR_CTRL_11
	UINT32 reg_i_sel_mmd_x3 				:8; //7:0	//
	UINT32 reg_i_sel_mmd_x2 				:8; //15:8	//
	UINT32 reg_i_sel_mmd_x1 				:8; //23:16 //
	UINT32 reg_i_sel_mmd_x0 				:8; //31:24 //
	};
}PE_O26_ND0_VERI_SYS_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291110 copy from MNR_CTRL_12
	UINT32 reg_i_sel_mmd_y3 				:8; //7:0	//
	UINT32 reg_i_sel_mmd_y2 				:8; //15:8	//
	UINT32 reg_i_sel_mmd_y1 				:8; //23:16 //
	UINT32 reg_i_sel_mmd_y0 				:8; //31:24 //
	};
}PE_O26_ND0_VERI_SYS_VERI_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291114 RW 0x0000_0000
	UINT32 reg_sys_veri_5                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND0_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291118 RW 0x0000_0000
	UINT32 reg_sys_veri_6                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND0_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC29111C RW 0x0000_0000
	UINT32 reg_sys_veri_7                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND0_VERI_SYS_VERI_7_T;

typedef struct {
	PE_O26_ND0_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCC291100
	PE_O26_ND0_VERI_SYS_VERI_1_T                                mnr_ctrl_0;//0xCC291104
	PE_O26_ND0_VERI_SYS_VERI_2_T                                mnr_ctrl_3;//0xCC291108
	PE_O26_ND0_VERI_SYS_VERI_3_T                                mnr_ctrl_11;//0xCC29110C
	PE_O26_ND0_VERI_SYS_VERI_4_T                                mnr_ctrl_12;//0xCC291110
	PE_O26_ND0_VERI_SYS_VERI_5_T                                sys_veri_5;	//0xCC291114
	PE_O26_ND0_VERI_SYS_VERI_6_T                                sys_veri_6;	//0xCC291118
	PE_O26_ND0_VERI_SYS_VERI_7_T                                sys_veri_7;	//0xCC29111C
}PE_ND0_VERI_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291100 copy from MNR_CTRL_0
	UINT32 reg_mnr_enable                   :1;	//(0,RW,0x00) //
	UINT32 reg_mnr_debug                    :1;	//(1,RW,0x00) //
	UINT32 reg_mnr_mmd_chroma_en            :1;	//(2,RW,0x00) //
	UINT32 reg_mnr_chroma_en                :1;	//(3,RW,0x00) //
	UINT32 reg_h_expand                     :2;	//(5:4,RW,0x0) //0: 9-tap, 1: 13-tap, 2: 17-tap
	UINT32 reg_sel_mmd                      :2;	//(7:6,RW,0x00) //0: tnr, 1: mnr, 2: max_mmd
	UINT32 reg_mnr_master_gain              :8;	//(15:8,RW,0x0) //
	UINT32 reg_snr_th                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_th_max                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_ND1_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC291104 copy from MNR_CTRL_3
	UINT32 reg_blur_sel 					:1; //0 //
	UINT32 reg_pattern_en					:1; //1 //
	UINT32 resvd							:6;
	UINT32 reg_pattern_th					:8; //15:8	//
	UINT32 reg_equal_th 					:8; //23:16 //
	UINT32 reg_mmd_scale					:8; //31:24 //
	};
}PE_O26_ND1_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C1608 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND1_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2C160C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_ND1_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O26_ND1_VERI_SYS_VERI_0_T                                mnr_ctrl_0;	//0xCC2C1600
	PE_O26_ND1_VERI_SYS_VERI_1_T                                mnr_ctrl_3;	//0xCC2C1604
	PE_O26_ND1_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCC2C1608
	PE_O26_ND1_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCC2C160C
}PE_ND1_VERI_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC100B8 RW 0x0000_0000
	UINT32 reg_lvctrl_en                    :1;	//(0,RW,0x00) //'0' := DISABLE	 '1'  = ENABLE
	UINT32 reg_lvctrl_detour                :1;	//(1,RW,0x00) //'0' := NORMAL	 '1'  = DETOUR
	UINT32 resvd0                           :2;
	UINT32 level_offset                     :10;	//(13:4,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 level_center                     :8;	//(23:16,RW,0x0) //
	UINT32 level_gain                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CTRL_CTRL_M0_Y_LEVEL_CTRL_T;

typedef struct {
	PE_O26_CTRL_CTRL_M0_Y_LEVEL_CTRL_T            ctrl_m0_y_level_ctrl;	//0xCCC100B8
}PE_TOP_IMX_REG_O26_T;

#endif
