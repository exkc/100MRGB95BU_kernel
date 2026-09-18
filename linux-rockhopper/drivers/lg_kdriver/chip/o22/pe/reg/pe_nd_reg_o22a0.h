#ifndef _PE_ND_REG_O22A0_H_
#define _PE_ND_REG_O22A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC800100 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,RW,0x00) //load_time	0 := load at pic_init	1 = load when reg. write
	UINT32 load_enable                      :1;	//(1,RW,0x00) //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O22_PE0_ND_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800104 RW 0x0000_0000
	UINT32 intr_enable                      :1;	//(0,RW,0x00) //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//(6:4,RW,0x00) //interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  tnr_end  	'001 =  ipc_end	'010 = tnrw_y_end	'011 = tnrw_c_end	'100 = NA	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//(8,RW,0x00) //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//(26:16,RW,0x00) //the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_O22_PE0_ND_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800108 RO 0x0000_0000
	UINT32 tnr_frame_id                     :4;	//(3:0,RO,0x00) //TNR_FRAME_ID	increment every tnr_end
	UINT32 ipc_frame_id                     :4;	//(7:4,RO,0x00) //IPC_FRAME_ID	increment every ipc_end
	UINT32 tnrw_y_frame_id                  :4;	//(11:8,RO,0x00) //TNRW_Y_FRAME_ID	increment every tnrw_y_end
	UINT32 tnrw_c_frame_id                  :4;	//(15:12,RO,0x00) //TNRW_C_FRAME_ID	increment every tnrw_c_end
	UINT32 dnr_frame_id                     :8;	//(23:16,RO,0x0) //IPC_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//(27:24,RO,0x00) //PIC_INIT_FRAME_ID
	UINT32 resvd                            :4;
	};
}PE_O22_PE0_ND_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80010C RO 0x0000_0000
	UINT32 line_cnt                         :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 timer_cnt                        :16;	//(31:16,RO,0x0) //timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_O22_PE0_ND_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800110 RW 0x0030_0000
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
	UINT32 resvd0                           :1;
	UINT32 tnr_m_en                         :1;	//(13,RW,0x00) //TNR_M (motion info) memory read&write enable
	UINT32 force_444_to_422                 :1;	//(14,RW,0x00) //Enable FORCE_422	If the chroma sampling type is 444 and this flag enabled, then	(1) TNR chroma data in 444 format is subsampled to be 422 before being written to the memory	(2) TNR_C, IPC_C read the data as 422 format
	UINT32 resvd1                           :1;
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
}PE_O22_PE0_ND_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800114 RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE: ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd0                           :1;
	UINT32 cs_type                          :3;	//(15:13,RW,0x0) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE: ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå	 (progressive format Í∏∞Ï?)
	UINT32 resvd1                           :3;
	UINT32 scan_type                        :1;	//(31,RW,0x00) //scan_type	1 : progressive	0 : interlaced
	};
}PE_O22_PE0_SRC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800118 RW 0x0006_0000
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
	UINT32 out_422_hsample_mode             :1;	//(20,RW,0x00) //0 := 0,2,4,6,??1 = 1,3,5,7,??
	UINT32 out_420_vsample_mode             :1;	//(21,RW,0x00) //0 := 0,3,4,7,??1 = 0,2,4,6,??
	UINT32 resvd5                           :10;
	};
}PE_O22_PE0_FIELD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80011C RW 0x0000_0000
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
}PE_O22_PE0_DEBUG_LEND_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800120 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_IN_SIZE -> in_hsize	1 = PE0_IN_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O22_PE0_ND_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800124 RW 0x0000_0000
	UINT32 hsize                            :12;	//(11:0,RW,0x00) //HSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x00) //VSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå	 (progressive format Í∏∞Ï?)
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_ND_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800128 RW 0x0000_0000
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
}PE_O22_FBC_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80012C RW 0x0000_0000
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
}PE_O22_FBC_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800130 RW 0x0000_0000
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
}PE_O22_PE0_MEM_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800134 RW 0x0000_0000
	UINT32 lreq_dly_c                       :11;	//(10:0,RW,0x00) //unit: 16 de_clk
	UINT32 lreq_dly_c_en                    :1;	//(11,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 lreq_dly_y                       :11;	//(26:16,RW,0x00) //
	UINT32 lreq_dly_y_en                    :1;	//(27,RW,0x00) //
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_DEBUG_LREQ_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800138 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_IN_SIZE -> in_hsize	1 = PE0_IN_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O22_TNRW_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80013C RW 0x0000_0000
	UINT32 hsize                            :12;	//(11:0,RW,0x000) //HSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x000) //VSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå	 (progressive format Í∏∞Ï?)
	UINT32 resvd1                           :4;
	};
}PE_O22_TNRW_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800140 RW 0x0000_0000
	UINT32 reg_tnr_en                       :1;	//(0:0,RW,0x00) //
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
	UINT32 reg_tnr_single_en                :1;	//(16:16,RW,0x00) //TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en               :1;	//(17,RW,0x0) //chg
	UINT32 reg_minfo_mode32                 :2;	//(19:18,RW,0x00) //
	UINT32 reg_minfo_mode74                 :4;	//(23:20,RW,0x00) //
	UINT32 reg_sad_8x3_iir_alpha            :8;	//(31:24,RW,0x0) //for TNR, DNR
	};
}PE_O22_TNR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800144 RW 0x0000_0000
	UINT32 reg_dbg_show                     :4;	//(3:0,RW,0x00) //
	UINT32 reg_ma_motion_iir_alpha          :8;	//(11:4,RW,0x00) //for decontour, new
	UINT32 reg_ma_motion_iir_en             :1;	//(12,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_chroma_en          :1;	//(13,RW,0x0) //for decontour, new
	UINT32 reg_ma_motion_res                :2;	//(15:14,RW,0x0) //for decontour, new
	UINT32 reg_dbg_tnrw                     :2;	//(17:16,RW,0x00) //TNR WriteÎ•??†ÌÉù?©Îãà?? 	0 = TNR Ï∂úÎ†• (T)	1 = TNR ?ÑÏû¨ ?ÖÎ†• (T)	2 = TNR ?¥Ï†Ñ ?ÖÎ†• (T-1)
	UINT32 reg_ma_motion_lsb6_sel           :1;	//(18,RW,0x0) //for decontour, new
	UINT32 reg_sad_8x3_lsb6_sel             :1;	//(19,RW,0x0) //new
	UINT32 reg_tnri_debug_mode              :2;	//(21:20,RW,0x00) //
	UINT32 resvd0                           :2;
	UINT32 reg_minfo_mode118                :4;	//(27:24,RW,0x00) //
	UINT32 reg_sc_scale2                    :3;	//(30:28,RW,0x00) //
	UINT32 resvd1                           :1;
	};
}PE_O22_TNR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800148 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80014C RW 0x0000_0000
	UINT32 show_dbg_bar_scale               :3;	//(2:0,RW,0x00) //debug bar scale
	UINT32 resvd0                           :1;
	UINT32 show_dbg_bar_en                  :4;	//(7:4,RW,0x00) //debug bar enable
	UINT32 resvd1                           :8;
	UINT32 show_dbg_bar0_mux                :4;	//(19:16,RW,0x00) //input mux for the lowest debug bar	0x0 := x_peak	0x1 = motion vector variance	0x2 = motion vector H	0x3 = motion vector V	0x4 = abs(NR-P2)	0x5 = abs(NR-CC)	0x6 = MA motion	0x7 = spatial variance	0x8 = scene change
	UINT32 show_dbg_bar1_mux                :4;	//(23:20,RW,0x00) //input mux for 2nd debug bar
	UINT32 show_dbg_bar2_mux                :4;	//(27:24,RW,0x00) //input mux for 3rd debug bar
	UINT32 show_dbg_bar3_mux                :4;	//(31:28,RW,0x00) //input mux for the highest debug bar
	};
}PE_O22_TNR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800150 RW 0x0000_0000
	UINT32 manual_debug_bar_09              :8;	//(7:0,RW,0x0) //for manual debug mode ( reg_mux : 1001)
	UINT32 manual_debug_bar_10              :8;	//(15:8,RW,0x0) //for manual debug mode ( reg_mux : 1010)
	UINT32 manual_debug_bar_11              :8;	//(23:16,RW,0x0) //for manual debug mode ( reg_mux : 1011)
	UINT32 manual_debug_bar_12              :8;	//(31:24,RW,0x0) //for manual debug mode ( reg_mux : 1100)
	};
}PE_O22_TNR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800154 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800158 RW 0x0000_0000
	UINT32 reg_me_lb_base                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_me_pv_base                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_me_lb_polarity               :1;	//(16,RW,0x00) //
	UINT32 resvd                            :15;
	};
}PE_O22_TNR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80015C RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_5x5_sad_cut                  :2;	//(5:4,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_sc_en                        :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :3;
	UINT32 reg_ma_gain_yc_sel               :1;	//(12,RW,0x00) //new
	UINT32 resvd3                           :19;
	};
}PE_O22_TNR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800160 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800164 RW 0x0000_0000
	UINT32 reg_sad_base                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lb_smooth_clip               :6;	//(13:8,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_pv_smooth_clip               :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :10;
	};
}PE_O22_TNR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800168 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80016C RW 0x8000_0000
	UINT32 lb_smooth_en                     :1;	//(0,RW,0x0) //
	UINT32 pv_smooth_en                     :1;	//(1,RW,0x0) //
	UINT32 pmv_hist_en                      :1;	//(2,RW,0x0) //new
	UINT32 reg_yonly_me_en                  :1;	//(3,RW,0x0) //new
	UINT32 resvd                            :27;
	UINT32 reg_me_n15_protection            :1;	//(31,RW,0x0) //
	};
}PE_O22_TNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800170 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800174 RW 0x0000_0000
	UINT32 reg_min_sad_ratio                :8;	//(7:0,RW,0x00) //new
	UINT32 reg_lb_cost_ratio                :8;	//(15:8,RW,0x00) //new
	UINT32 reg_zero_sad_ratio               :8;	//(23:16,RW,0x00) //new
	UINT32 reg_zero_mv_blk_mv_sel           :2;	//(25:24,RW,0x0) //chg
	UINT32 resvd0                           :2;
	UINT32 reg_zero_sad_adv                 :1;	//(28,RW,0x0) //chg
	UINT32 resvd1                           :3;
	};
}PE_O22_TNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800178 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80017C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800180 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800184 RW 0x0000_0000
	UINT32 reg_blk_vsize                    :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 reg_blk_hsize                    :12;	//(27:16,RW,0x00) //
	UINT32 resvd1                           :4;
	};
}PE_O22_TNR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800188 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80018C RW 0x0000_0000
	UINT32 bmv_coring_th                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tl_equal_off                 :1;	//(12,RW,0x0) //O22
	UINT32 resvd1                           :3;
	UINT32 gmv_0mv_tl                       :7;	//(22:16,RW,0x0) //0MV ?ÅÌñ•?•Ïùò Í∞ïÎèÑ Ï°∞Ï†à : x10??bypass?¥Í≥† ?íÏùÑ ?òÎ°ù Í∞ïÌïòÍ≤??ÅÌñ•??Ï§?
	UINT32 gmv_0mv_tl_en                    :1;	//(23,RW,0x00) //Global MV??0MV Î≥¥ÎÑà?§Î? Ï§?Í≤ÉÏù∏Í∞Ä?
	UINT32 bmv_0mv_tl                       :7;	//(30:24,RW,0x0) //0MV ?ÅÌñ•?•Ïùò Í∞ïÎèÑ Ï°∞Ï†à : x10??bypass?¥Í≥† ?íÏùÑ ?òÎ°ù Í∞ïÌïòÍ≤??ÅÌñ•??Ï§?
	UINT32 bmv_0mv_tl_en                    :1;	//(31,RW,0x00) //Large Block MV??0MV Î≥¥ÎÑà?§Î? Ï§?Í≤ÉÏù∏Í∞Ä?
	};
}PE_O22_TNR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800190 RW 0x0000_0000
	UINT32 reg_detail_beta_mul              :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_alpha_mul             :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_beta_mul                :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_alpha_mul               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800194 RW 0x0000_0000
	UINT32 reg_svar_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 reg_sad_8x3_res2                 :2;	//(9:8,RW,0x00) //
	UINT32 resvd1                           :22;
	};
}PE_O22_TNR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800198 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80019C RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,Rsvd,0x0000_0000) //
	};
}PE_O22_TNR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001A0 RW 0x0000_0000
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
}PE_O22_TNR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001A4 RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_skin_master_gain             :8;	//(31:24,RW,0xFF) //new
	};
}PE_O22_TNR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001A8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001AC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001B0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_yy_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_yy_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O22_TNR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001B4 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001B8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001BC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cb_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cb_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O22_TNR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001C0 RO 0x0000_0000
	UINT32 w_gsad                           :8;	//(7:0,RO,0x0) //
	UINT32 w_gmv_h                          :5;	//(12:8,RO,0x00)	//
	UINT32 w_gmv_v                          :4;	//(16:13,RO,0x00)	//
	UINT32 resvd                            :7;
	UINT32 w_apl_detail                     :8;	//(31:24,RO,0x0) //
	};
}PE_O22_TNR_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001C4 RO 0x0000_0000
	UINT32 w_apl_motion                     :8;	//(7:0,RO,0x0) //
	UINT32 w_apl_mc_sad                     :8;	//(15:8,RO,0x0) //
	UINT32 w_apl_var                        :8;	//(23:16,RO,0x0) //
	UINT32 w_apl_edge                       :8;	//(31:24,RO,0x0) //
	};
}PE_O22_TNR_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001C8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001CC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001D0 RW 0x0000_0000
	UINT32 main_lut_indir_addr              :6;	//(5:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 main_lut_ai_enable               :1;	//(12,RW,0x00) //TNR Main-LUT Ctrl. AI enable
	UINT32 resvd1                           :2;
	UINT32 main_lut_load                    :1;	//(15,RW,0x00) //
	UINT32 resvd2                           :16;
	};
}PE_O22_TNR_MAIN_LUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001D4 RW 0x0000_0000
	UINT32 main_lut_indir_data0             :32;	//(31:0,RW,0x0000_0000) //TNR Main-LUT Ctrl. Indirect Access Data 0 63:32 (MSB8u:Biggest, LSB8u:Smallest)
	};
}PE_O22_TNR_MAIN_LUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001DC RO 0x0000_0000
	UINT32 sc_measure                       :8;	//(7:0,RO,0x0) //scene change detection measure
	UINT32 apl_y                            :8;	//(15:8,RO,0x0) //
	UINT32 sc_measure_16                    :16;	//(31:16,RO,0x0) //scene change measure (16b)
	};
}PE_O22_TNR_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001E0 RW 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 reg_gf_gain                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_blur_coef                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001E4 RW 0x0000_0000
	UINT32 same_protection_en               :1;	//(0,RW,0x00) //
	UINT32 reg_p_mv0_only                   :1;	//(1,RW,0x00) //
	UINT32 reg_p_non_mv0_only               :1;	//(2,RW,0x00) //new
	UINT32 reg_final_lut_en                 :1;	//(3,RW,0x00) //new
	UINT32 resvd0                           :4;
	UINT32 reg_same_sad_th                  :8;	//(15:8,RW,0x00) //
	UINT32 reg_move_step                    :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}PE_O22_TNR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001E8 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_x2          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y3          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x3          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001EC RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y1          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x1          :10;	//(19:10,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_y2          :10;	//(29:20,RW,0x000) //new
	UINT32 resvd                            :2;
	};
}PE_O22_TNR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001F0 RW 0x0000_0000
	UINT32 reg_tnr_final_lut_cr_y0          :10;	//(9:0,RW,0x000) //new
	UINT32 reg_tnr_final_lut_cr_x0          :10;	//(19:10,RW,0x000) //new
	UINT32 resvd                            :12;
	};
}PE_O22_TNR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001F4 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O22_TNR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001F8 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O22_TNR_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8001FC RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O22_TNR_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800200 RW 0x0351_0006
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
}PE_O22_IPC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800204 RW 0x0311_04C1
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
}PE_O22_IPC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800208 RW 0x904C_702F
	UINT32 fuzzy_ctrl_point_x0              :8;	//(7:0,RW,0x2F) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x4              :8;	//(15:8,RW,0x70) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x1              :8;	//(23:16,RW,0x4C) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y1              :8;	//(31:24,RW,0x90) //control points for 2D/3D decision
	};
}PE_O22_IPC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80020C RW 0xF550_5038
	UINT32 fuzzy_ctrl_point_x2              :8;	//(7:0,RW,0x38) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y2              :8;	//(15:8,RW,0x50) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_x3              :8;	//(23:16,RW,0x50) //control points for 2D/3D decision
	UINT32 fuzzy_ctrl_point_y3              :8;	//(31:24,RW,0xF5) //control points for 2D/3D decision
	};
}PE_O22_IPC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800210 RW 0x6000_4000
	UINT32 et_offset__s7                    :8;	//(7:0,RW,0x0) //signed 7bit (F5 means -10)	Smaller > Weight to 3D	Bigger > Weight to 2D
	UINT32 motion_x_tearing_gain            :8;	//(15:8,RW,0x40) //Motion Area Tearing Gain	80 := x2.0	40 = x1.0
	UINT32 tearing_gain                     :8;	//(23:16,RW,0x0) //All Area Tearing Gain ( Difficult to Excuse Pattern Tearing )
	UINT32 motion_gain                      :8;	//(31:24,RW,0x60) //Motion Gain	40 := x1.0
	};
}PE_O22_IPC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800214 RW 0x6080_1010
	UINT32 resvd0                           :12;
	UINT32 cr_t_grad_weight                 :4;	//(15:12,RW,0x1) //Variance Normalize?êÏÑú VarianceÎ•?Íµ¨ÌïòÍ∏??ÑÌïú Gain
	UINT32 resvd1                           :4;
	UINT32 cr_v_grad_weight                 :4;	//(23:20,RW,0x8) //Variance Normalize?êÏÑú VarianceÎ•?Íµ¨ÌïòÍ∏??ÑÌïú Gain
	UINT32 resvd2                           :4;
	UINT32 cr_h_grad_weight                 :4;	//(31:28,RW,0x6) //Variance Normalize?êÏÑú VarianceÎ•?Íµ¨ÌïòÍ∏??ÑÌïú Gain
	};
}PE_O22_IPC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800218 RW 0x0070_109F
	UINT32 cr_normalize_en                  :1;	//(0,RW,0x1) //Motion??Normalize ?¨Ïö© ?†Î¨¥
	UINT32 cr_flat_only                     :1;	//(1,RW,0x1) //Normalize??x1.0?¥Ìïò??Í∞ïÎèÑ??x1.0?ºÎ°ú ÎßåÎì¶
	UINT32 cr_motion_iir_en                 :1;	//(2,RW,0x1) //IIR??TNR motion ??Blending??
	UINT32 resvd0                           :1;
	UINT32 cr_tearing_normalize_en          :1;	//(4,RW,0x1) //Tearing Score??Normalize ?¨Ïö© ?†Î¨¥
	UINT32 resvd1                           :3;
	UINT32 cr_normalize_base                :8;	//(15:8,RW,0x10) //x (Center + a) / (Variance + a) ?êÏÑú a???¥Îãπ?òÎäî Í∞?, ??ùÑ?òÎ°ù Í∞ïÌïòÍ≤?Normalize??
	UINT32 cr_normalize_center              :8;	//(23:16,RW,0x70) //Normalize??x1.0??Í∏∞Ï????òÎäî Variance
	UINT32 cr_motion_coring                 :8;	//(31:24,RW,0x0) //Motion???¥Í∞íÎ≥¥Îã§ ??≤å ?òÏò§Î©?Í∞ïÏ†úÎ°?3DÎ°??åÎ¶º
	};
}PE_O22_IPC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80021C RW 0x80E0_025C
	UINT32 resvd0                           :1;
	UINT32 cr_v_en                          :1;	//(1,RW,0x0) //vertical Tearing Check Enable
	UINT32 cr_45_en                         :1;	//(2,RW,0x1) //45 degree Tearing Check enable
	UINT32 cr_15_en                         :1;	//(3,RW,0x1) //15 degree Tearing check Enable
	UINT32 resvd1                           :20;
	UINT32 cr_iir_motion_gain               :8;	//(31:24,RW,0x80) //motion_IIR_alpha
	};
}PE_O22_IPC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800220 RW 0x0440_0320
	UINT32 fmd_caption_range_top            :12;	//(11:0,RW,0x320) //FMD, CaptionRange Top
	UINT32 resvd0                           :4;
	UINT32 fmd_caption_range_bot            :12;	//(27:16,RW,0x440) //FMD, CaptionRange Bottom
	UINT32 resvd1                           :2;
	UINT32 caption_flow_detected            :1;	//(30,RW,0x0) //Caption-Flow_Detected
	UINT32 hmc_when_cap_not_detected        :1;	//(31,RW,0x0) //Apply HMC Filter when "FilmDetected and CapFlowNotDetected and CaptionRange"	0 := apply HMC in CaptionRange only when capFlowDetected is 1	1 = apply HMC in CaptionRange even when capFlowDetected is 0
	};
}PE_O22_IPC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800224 RW 0x00FF_2814
	UINT32 pn_fmd_a_th                      :8;	//(7:0,RW,0x14) //FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pn_variance_th                   :8;	//(23:16,RW,0xFF) //
	UINT32 pn_fmd_motion_th                 :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800228 RW 0x2010_0428
	UINT32 pcnc_fmd_a_th                    :8;	//(7:0,RW,0x28) //FMD A-Th
	UINT32 resvd                            :8;
	UINT32 pcnc_variance_th                 :8;	//(23:16,RW,0x10) //
	UINT32 pcnc_fmd_motion_th               :8;	//(31:24,RW,0x20) //
	};
}PE_O22_IPC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80022C RW 0x1600_05A0
	UINT32 cr_pndiff_th                     :8;	//(7:0,RW,0xA0) //
	UINT32 cr_center_bound_ctrl             :8;	//(15:8,RW,0x5) //
	UINT32 cr_dn_bound_ctrl                 :8;	//(23:16,RW,0x0) //
	UINT32 cr_up_bound_ctrl                 :8;	//(31:24,RW,0x16) //
	};
}PE_O22_IPC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800230 RW 0xFF2A_100A
	UINT32 reg_still_pn_th                  :8;	//(7:0,RW,0xA) //FMD, threshold for still frame using pn_cnt (upper)
	UINT32 reg_fmd_ratio_th                 :8;	//(15:8,RW,0x10) //FMD, ratio of pc_cnt and nc_cnt (upper)
	UINT32 reg_fmd_max_th                   :8;	//(23:16,RW,0x2A) //FMD, max threshold for bigger value (pc_cnt/nc_cnt) (upper)
	UINT32 reg_fmd_min_th                   :8;	//(31:24,RW,0xFF) //FMD, min threshold for bigger value (pc_cnt/nc_cnt) (upper)
	};
}PE_O22_IPC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800234 RW 0x2000_1001
	UINT32 cr_tava_chroma_mul               :8;	//(7:0,RW,0x1) //
	UINT32 resvd                            :4;
	UINT32 cr_hmc_alpha_th                  :8;	//(19:12,RW,0x1) //
	UINT32 cr_hmc_debug_mode                :1;	//(20,RW,0x0) //
	UINT32 cr_hmc_debug_gain                :6;	//(26:21,RW,0x0) //
	UINT32 cr_hmc_debug_dir                 :5;	//(31:27,RW,0x4) //
	};
}PE_O22_IPC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800238 RW 0x0610_C019
	UINT32 reg_lockcnt_en                   :1;	//(0,RW,0x1) //FMD, Lockcnt enable (upper)
	UINT32 reserved                         :1;	//(1,Rsvd,0x0) //
	UINT32 reg_lock_speed                   :6;	//(7:2,RW,0x6) //FMD, Lockcnt increasing step (upper)
	UINT32 reg_lockcnt_th                   :8;	//(15:8,RW,0xC0) //FMD, Lockcnt threshold (upper)
	UINT32 reg_same_th                      :8;	//(23:16,RW,0x10) //FMD, threshold for same using pc_nc_same_cnt (upper)
	UINT32 reg_still_frame_limit            :8;	//(31:24,RW,0x6) //FMD, threshold for still (upper)
	};
}PE_O22_IPC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80023C RW 0x6B38_0404
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
}PE_O22_IPC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800240 RW 0x5020_3804
	UINT32 reg_still_pn_th2                 :8;	//(7:0,RW,0x4) //FMD, threshold for pndiff_cnt (upper)
	UINT32 reg_still_prev_ratio             :8;	//(15:8,RW,0x38) //FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (upper)
	UINT32 reg_lock_reducer                 :8;	//(23:16,RW,0x20) //FMD, Lockcnt decreasing step (upper)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//(31,RW,0x0) //FMD, badedit protect (upper)
	};
}PE_O22_IPC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800244 RW 0x5370_1030
	UINT32 cr_inv_resolution                :2;	//(1:0,RW,0x0) //
	UINT32 cr_field_manual_mode             :2;	//(3:2,RW,0x0) //
	UINT32 cr_field_inverse                 :1;	//(4,RW,0x1) //
	UINT32 resvd                            :19;
	UINT32 cr_tearing_a_th                  :8;	//(31:24,RW,0x53) //
	};
}PE_O22_IPC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800248 RW 0xFF50DFCD
	UINT32 cr_ud_gain                       :8;	//(7:0,RW,0xCD) //| U - D | to 2D confidence (s7)
	UINT32 cr_lr_gain                       :8;	//(15:8,RW,0xDF) //| L - R | to 2D confidence (s7)
	UINT32 cr_h_grad_gain                   :8;	//(23:16,RW,0x50) //Horizontal Gradient to 2D confidence (s7)
	UINT32 cr_v_grad_gain                   :8;	//(31:24,RW,0xFF) //Vertical Gradient to 2D confidence (s7)
	};
}PE_O22_IPC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80024C RW 0x0078_2438
	UINT32 reg_errs_gain                    :8;	//(7:0,RW,0x38) //
	UINT32 reg_confidence_gain              :8;	//(15:8,RW,0x24) //
	UINT32 reg_2d_offset                    :8;	//(23:16,RW,0x78) //
	UINT32 reg_flicker_gain                 :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800250 RO 0x0000_0000
	UINT32 r_pc_v_count                     :16;	//(15:0,RO,0x0) //FMD, vertical tearing count of pc (upper)
	UINT32 r_nc_v_count                     :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of nc (upper)
	};
}PE_O22_IPC_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800254 RO 0x0000_0000
	UINT32 r_pc_nc_same                     :16;	//(15:0,RO,0x0) //FMD, same count between pc and nc (upper)
	UINT32 r_pn_v_count                     :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of pn (upper)
	};
}PE_O22_IPC_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800258 RO 0x0000_0000
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
}PE_O22_IPC_STATUS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80025C RO 0x0000_0000
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
}PE_O22_IPC_STATUS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800260 RW 0xF88F_12F0
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
}PE_O22_CLC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800264 RW 0x3250_0225
	UINT32 cl_motion_a_th                   :8;	//(7:0,RW,0x25) //CL motion a threshold, motion a is calculated between in-phase frame
	UINT32 cl_motion_b_th                   :8;	//(15:8,RW,0x2) //CL motion b threshold, motion b is calculated between out-of-phase phase frame
	UINT32 cl_y_protect_th0                 :8;	//(23:16,RW,0x50) //CL Y protect threshold 0
	UINT32 cl_y_protect_th1                 :8;	//(31:24,RW,0x32) //CL Y protect threshold 1
	};
}PE_O22_CLC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800268 RW 0x1900_0985
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
}PE_O22_CLC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80026C RW 0xC030_F030
	UINT32 cl_sat_min                       :8;	//(7:0,RW,0x30) //CL saturation min value
	UINT32 resvd                            :2;
	UINT32 cl_var_measure_th1               :10;	//(19:10,RW,0x03C) //CL variance measure th
	UINT32 cl_var_measure_th2               :10;	//(29:20,RW,0x03) //CL motion P2N2 th for variance measure
	UINT32 cl_pt_enable                     :2;	//(31:30,RW,0x03) //CL protection enable	(31): variance protection enable	(30): tearing protection enable
	};
}PE_O22_CLC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800270 RW 0x0000_0020
	UINT32 cl_tearing_pt_th1                :12;	//(11:0,RW,0x020) //CL Tearing protection threshold(no CL filtering)
	UINT32 cl_motionp2n2_th_pal_low         :8;	//(19:12,RW,0x0) //CL_MotionP2N2_Th_PAL(7:0) : low bit
	UINT32 cl_frame_min                     :12;	//(31:20,RW,0x00) //CL min detection pixel count per frame
	};
}PE_O22_CLC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800274 RW 0x1FFD_8020
	UINT32 cl_data_line_switching_sel       :1;	//(0,RW,0x00) //0 = switching data line at [each line]	1 = switching data line at [each field]
	UINT32 resvd0                           :7;
	UINT32 clc_bin_flt_th                   :3;	//(10:8,RW,0x00) //CL_pt_map binary filtering(5x1) th
	UINT32 resvd1                           :4;
	UINT32 clc_bin_flt_en                   :1;	//(15,RW,0x01) //CL_pt_map binary filtering(1x3 -> 5x1) enable
	UINT32 clc_dbg_show_mask                :13;	//(28:16,RW,0x1FFD) //CLC Dbg Show Mask
	UINT32 resvd2                           :3;
	};
}PE_O22_CLC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800278 RW 0xC000_3E00
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
}PE_O22_CLC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80027C RO 0x0000_0000
	UINT32 resvd                            :16;
	UINT32 cl_detection_count               :16;	//(31:16,RO,0x0) //CL detection pixel count
	};
}PE_O22_CLC_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800280 RW 0x3EFF_3000
	UINT32 tava_v_diff_y0                   :8;	//(7:0,RW,0x0) //
	UINT32 tava_v_diff_x0                   :8;	//(15:8,RW,0x30) //
	UINT32 tava_v_diff_y1                   :8;	//(23:16,RW,0xFF) //
	UINT32 tava_v_diff_x1                   :8;	//(31:24,RW,0x3E) //
	};
}PE_O22_IPC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800284 RW 0x0000_0002
	UINT32 reg_div_en                       :1;	//(0,RW,0x0) //FMD, div mode enable
	UINT32 cr_bound_exp_en                  :1;	//(1,RW,0x1) //FMD, cr bound enable
	UINT32 resvd0                           :2;
	UINT32 cr_sub_main_sel                  :1;	//(4,RW,0x0) //(Ï§ëÏöî) FMD, 0:main path, 1:sub path
	UINT32 resvd1                           :11;
	UINT32 reg_manual_en                    :1;	//(16,RW,0x0) //FMD, manual mode enable
	UINT32 resvd2                           :3;
	UINT32 reg_manual_mode2                 :2;	//(21:20,RW,0x0) //FMD, manual mode COMB_MODE (under)
	UINT32 reg_manual_mode1                 :2;	//(23:22,RW,0x0) //FMD, manual mode COMB_MODE (upper)
	UINT32 reg_div_position                 :8;	//(31:24,RW,0x0) //FMD, div mode upper/under boundary position
	};
}PE_O22_IPC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800288 RW 0xFF28_1003
	UINT32 reg_still_pn_th                  :8;	//(7:0,RW,0x3) //FMD, threshold for still frame using pn_cnt (under)
	UINT32 reg_fmd_ratio_th                 :8;	//(15:8,RW,0x10) //FMD, ratio of pc_cnt and nc_cnt (under)
	UINT32 reg_fmd_max_th                   :8;	//(23:16,RW,0x28) //FMD, max threshold for bigger value (pc_cnt/nc_cnt) (under)
	UINT32 reg_fmd_min_th                   :8;	//(31:24,RW,0xFF) //FMD, min threshold for bigger value (pc_cnt/nc_cnt) (under)
	};
}PE_O22_IPC_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80028C RW 0x0752_C061
	UINT32 reg_lockcnt_en                   :1;	//(0,RW,0x1) //FMD, Lockcnt enable (under)
	UINT32 reserved                         :1;	//(1,Rsvd,0x0) //
	UINT32 reg_lock_speed                   :6;	//(7:2,RW,0x18) //FMD, Lockcnt increasing step (under)
	UINT32 reg_lockcnt_th                   :8;	//(15:8,RW,0xC0) //FMD, Lockcnt threshold (under)
	UINT32 reg_same_th                      :8;	//(23:16,RW,0x52) //FMD, threshold for same using pc_nc_same_cnt (under)
	UINT32 reg_still_frame_limit            :8;	//(31:24,RW,0x7) //FMD, threshold for still (under)
	};
}PE_O22_IPC_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800290 RW 0x6A38_0404
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
}PE_O22_IPC_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800294 RW 0x5370_0804
	UINT32 reg_still_pn_th2                 :8;	//(7:0,RW,0x4) //FMD, threshold for pndiff_cnt (under)
	UINT32 reg_still_prev_ratio             :8;	//(15:8,RW,0x8) //FMD, threshold for ratio of prev_pn_cnt and curr_pn_cnt (under)
	UINT32 reg_lock_reducer                 :8;	//(23:16,RW,0x70) //FMD, Lockcnt decreasing step (under)
	UINT32 resvd                            :7;
	UINT32 reg_badedit_protect              :1;	//(31,RW,0x0) //FMD, badedit protect (under)
	};
}PE_O22_IPC_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800298 RW 0x0000_3507
	UINT32 reg_toosmall_en                  :1;	//(0,RW,0x1) //FMD, toosmall mode enable (under)
	UINT32 reg_toosmall_min                 :7;	//(7:1,RW,0x3) //FMD, min value of toosmall condition (under)
	UINT32 reg_toosmall_max                 :8;	//(15:8,RW,0x35) //FMD, max value of toosmall condition (under)
	UINT32 reg_pndiff_disable               :1;	//(16,RW,0x0) //FMD, pndiff mode off (under)
	UINT32 resvd                            :15;
	};
}PE_O22_IPC_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80029C RW 0x0000_01E0
	UINT32 reg_fend_position                :11;	//(10:0,RW,0x1E0) //
	UINT32 resvd0                           :1;
	UINT32 cr_sc_length                     :3;	//(14:12,RW,0x0) //
	UINT32 resvd1                           :11;
	UINT32 cr_vmc_dir                       :3;	//(28:26,RW,0x0) //Force VMC
	UINT32 resvd2                           :2;
	UINT32 cr_vmc_en                        :1;	//(31,RW,0x0) //Force VMC
	};
}PE_O22_IPC_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002A0 RW 0x0000_3098
	UINT32 reg_yy_diff_gain                 :4;	//(3:0,RW,0x8) //Luma Motion Gain
	UINT32 reg_hv_add_gain                  :4;	//(7:4,RW,0x9) //HV Separable Motion Gain
	UINT32 reg_v_motion_gain                :4;	//(11:8,RW,0x0) //V Motion Gain
	UINT32 reg_h_motion_gain                :4;	//(15:12,RW,0x3) //H Motion Gain
	UINT32 reg_cc_diff_gain                 :4;	//(19:16,RW,0x0) //Chroma Motion Gain
	UINT32 resvd                            :12;
	};
}PE_O22_IPC_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002A4 RW 0x0000_0000
	UINT32 n1b_motion_gain_y0               :8;	//(7:0,RW,0x0) //
	UINT32 n1b_motion_gain_x0               :8;	//(15:8,RW,0x0) //
	UINT32 n1b_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 n1b_motion_gain_x1               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002A8 RW 0x0000_0000
	UINT32 n1b_variance_gain_y0             :8;	//(7:0,RW,0x0) //
	UINT32 n1b_variance_gain_x0             :8;	//(15:8,RW,0x0) //
	UINT32 n1b_variance_gain_y1             :8;	//(23:16,RW,0x0) //
	UINT32 n1b_variance_gain_x1             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002AC RW 0x0000_0000
	UINT32 reg_hmc_use_tnr_mv               :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 reg_cr_hmc_y_th                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 max_penalty                      :8;	//(23:16,RW,0x0) //
	UINT32 min_penalty                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002B0 RW 0x0000_0000
	UINT32 reg_min_diff_th                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_edi_va_blend_mul             :10;	//(17:8,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_edi_va_protect_mul           :10;	//(29:20,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_m16_edi_va_blend_en          :1;	//(31,RW,0x0) //
	};
}PE_O22_IPC_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002B4 RW 0x0000_0000
	UINT32 reg_max_va_diff_th               :8;	//(7:0,RW,0x0) //
	UINT32 reg_max_edi_diff_th              :8;	//(15:8,RW,0x0) //
	UINT32 reg_edi_va_protect_min           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edi_va_blend_min             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002B8 RW 0x0000_0000
	UINT32 reg_2d_top_lut_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_2d_top_lut_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_2d_top_lut_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_2d_top_lut_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002BC RW 0x0000_0000
	UINT32 cr_hmc_enable_1                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_1                     :7;	//(7:1,RW,0x0) //
	UINT32 cr_lr_ratio_th_1                 :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_expend_1                  :3;	//(18:16,RW,0x0) //
	UINT32 cr_lr_ratio_check_en_1           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_1                  :4;	//(23:20,RW,0x0) //
	UINT32 cr_center_weight_1               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002C0 RW 0x0000_0000
	UINT32 cr_hmc_enable_2                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_2                     :7;	//(7:1,RW,0x0) //
	UINT32 cr_lr_ratio_th_2                 :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_expend_2                  :3;	//(18:16,RW,0x0) //
	UINT32 cr_lr_ratio_check_en_2           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_2                  :4;	//(23:20,RW,0x0) //
	UINT32 cr_center_weight_2               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002C4 RW 0x0000_0000
	UINT32 line_cnt_th_0                    :12;	//(11:0,RW,0x0) //
	UINT32 line_cnt_th_1                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_IPC_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002C8 RW 0x0000_0000
	UINT32 cr_n1b_limit                     :9;	//(8:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 cr_n1b_resolution                :3;	//(14:12,RW,0x0) //
	UINT32 resvd1                           :9;
	UINT32 cr_pre_sc_th                     :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002CC RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_y0               :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x0               :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_IPC_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002D0 RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_y1               :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 cr_hmc_text_rgn_x1               :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_IPC_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002D4 RW 0x0000_0000
	UINT32 cr_hmc_text_rgn_en               :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 cr_hmc_text_rgn_sad_max          :8;	//(15:8,RW,0x0) //
	UINT32 cr_hmc_text_rgn_sad_min          :8;	//(23:16,RW,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O22_IPC_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002E0 RW 0x0000_0000
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
}PE_O22_MMD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002F0 RW 0x4040_18B0
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
}PE_O22_IPC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002F4 RW 0xCD51_991C
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
}PE_O22_IPC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002F8 RW 0xFFCC_2058
	UINT32 cr_vmc_v_diff_max                :8;	//(7:0,RW,0x58) //
	UINT32 cr_vmc_v_diff_protect_mul        :8;	//(15:8,RW,0x20) //
	UINT32 es_err_value                     :8;	//(23:16,RW,0xCC) //
	UINT32 et_err_value                     :8;	//(31:24,RW,0xFF) //
	};
}PE_O22_IPC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8002FC RW 0xB857_C010
	UINT32 cr_hmc_enable_0                  :1;	//(0,RW,0x0) //
	UINT32 cr_lock_th_0                     :7;	//(7:1,RW,0x8) //
	UINT32 cr_lr_ratio_th_0                 :8;	//(15:8,RW,0xC0) //
	UINT32 cr_hmc_expend_0                  :3;	//(18:16,RW,0x7) //
	UINT32 cr_lr_ratio_check_en_0           :1;	//(19,RW,0x0) //
	UINT32 cr_robustness_0                  :4;	//(23:20,RW,0x5) //
	UINT32 cr_center_weight_0               :8;	//(31:24,RW,0xB8) //
	};
}PE_O22_IPC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800300 RW 0x506B_0130
	UINT32 cr_noise_en                      :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :7;
	UINT32 cr_noise_th                      :8;	//(15:8,RW,0x1) //
	UINT32 cr_gds_resolution                :2;	//(17:16,RW,0x3) //
	UINT32 resvd1                           :2;
	UINT32 cr_hmc_h_range                   :12;	//(31:20,RW,0x506) //
	};
}PE_O22_IPC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800304 RW 0x6080_1010
	UINT32 reg_vdiff_en                     :1;	//(0,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 reg_vdiff_th                     :8;	//(15:8,RW,0x10) //
	UINT32 reg_hmc_err_max                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_hmc_err_min                  :8;	//(31:24,RW,0x60) //
	};
}PE_O22_IPC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800308 RW 0xE018_0818
	UINT32 cr_fmd_check_en                  :1;	//(0,RW,0x0) //FMD, chroma fmd mode enable
	UINT32 resvd0                           :7;
	UINT32 cr_fmd_ath                       :8;	//(15:8,RW,0x8) //FMD, A-Th for chroma fmd
	UINT32 resvd1                           :8;
	UINT32 cr_fmd_ratio_th                  :8;	//(31:24,RW,0xE0) //FMD, chroma fmd_ratio
	};
}PE_O22_IPC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80030C RW 0xE010_C010
	UINT32 chroma_st_flt_ctrl_x0            :8;	//(7:0,RW,0x10) //
	UINT32 chroma_st_flt_ctrl_x1            :8;	//(15:8,RW,0xC0) //
	UINT32 luma_st_flt_ctrl_x0              :8;	//(23:16,RW,0x10) //
	UINT32 luma_st_flt_ctrl_x1              :8;	//(31:24,RW,0xE0) //
	};
}PE_O22_IPC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800310 RW 0x0800_A40F
	UINT32 reg_hmc_bonus_es_en              :1;	//(0,RW,0x1) //
	UINT32 reg_hmc_bonus_et_en              :1;	//(1,RW,0x1) //
	UINT32 resvd                            :6;
	UINT32 reg_hmc_bonus_es                 :8;	//(15:8,RW,0xA4) //
	UINT32 reg_hmc_bonus_th                 :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_bonus_et                 :8;	//(31:24,RW,0x8) //
	};
}PE_O22_IPC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800314 RW 0x4008_401D
	UINT32 hmc_alpha_th                     :8;	//(7:0,RW,0x1D) //
	UINT32 resvd                            :8;
	UINT32 hmc_flt_ctrl_x0                  :8;	//(23:16,RW,0x8) //
	UINT32 hmc_st_flt_ctrl_x1               :8;	//(31:24,RW,0x40) //
	};
}PE_O22_IPC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800318 RW 0x6180_8318
	UINT32 reg_vmc_motion_th                :8;	//(7:0,RW,0x18) //VMC motion Th
	UINT32 reg_vmc_debug                    :1;	//(8,RW,0x1) //VMC ??Motion??0?ºÎ°ú ?∏ÌåÖ
	UINT32 reg_vmc_en                       :1;	//(9,RW,0x1) //VMC Enable
	UINT32 reg_vmc_still_check              :1;	//(10,RW,0x0) //P-C non motion ??VMC motion???îÌï†Í≤ÉÏù∏Í∞Ä?
	UINT32 resvd0                           :1;
	UINT32 reg_vmc_mul                      :2;	//(13:12,RW,0x0) //VMC*(2^n) vs normal Motion ??nÍ∞?
	UINT32 reg_vmc_out_mul                  :2;	//(15:14,RW,0x2) //ÍµêÏ≤¥??VMC motion??(2^n)Î∞∞Î? Í∞Ä??
	UINT32 reg_vmc_protect_th               :8;	//(23:16,RW,0x80) //Í∏∞Î≥∏ motion ???ºÎßà ?¥ÏÉÅ?ºÎïå VMC Î•??àÌïò??Protection Î™®Îìú
	UINT32 reg_protection_en                :1;	//(24,RW,0x1) //Í∏∞Î≥∏ motion ???ºÎßà ?¥ÏÉÅ?ºÎïå VMC Î•??àÌïò??Protection Th
	UINT32 reg_2filed_check_en              :1;	//(25,RW,0x0) //
	UINT32 reg_vmc_tnrmotion_dis            :1;	//(26,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_vmc_mm_ratio                 :4;	//(31:28,RW,0x6) //
	};
}PE_O22_IPC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80031C RW 0x0000_4503
	UINT32 reg_toosmall_en                  :1;	//(0,RW,0x1) //FMD, toosmall mode enable (upper)
	UINT32 reg_toosmall_min                 :7;	//(7:1,RW,0x1) //FMD, min value of toosmall condition (upper)
	UINT32 reg_toosmall_max                 :8;	//(15:8,RW,0x45) //FMD, max value of toosmall condition (upper)
	UINT32 reg_pndiff_disable               :1;	//(16,RW,0x0) //FMD, pndiff mode off (upper)
	UINT32 resvd                            :15;
	};
}PE_O22_IPC_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800320 RW 0x0000_0890
	UINT32 tava_errt_y2                     :8;	//(7:0,RW,0x90) //
	UINT32 tava_errt_x2                     :8;	//(15:8,RW,0x8) //
	UINT32 tava_errt_y3                     :8;	//(23:16,RW,0x0) //
	UINT32 tava_errt_x3                     :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IPC_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800324 RW 0x10B0_08FF
	UINT32 tava_errt_y0                     :8;	//(7:0,RW,0xFF) //
	UINT32 tava_errt_x0                     :8;	//(15:8,RW,0x8) //
	UINT32 tava_errt_y1                     :8;	//(23:16,RW,0xB0) //
	UINT32 tava_errt_x1                     :8;	//(31:24,RW,0x10) //
	};
}PE_O22_IPC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800328 RO 0x0000_0000
	UINT32 r_pc_v_count_d                   :16;	//(15:0,RO,0x0) //FMD, vertical tearing count of pc (under)
	UINT32 r_nc_v_count_d                   :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of nc (under)
	};
}PE_O22_IPC_STATUS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80032C RO 0x0000_0000
	UINT32 r_pc_nc_same_d                   :16;	//(15:0,RO,0x0) //FMD, same count between pc and nc (under)
	UINT32 r_pn_v_count_d                   :16;	//(31:16,RO,0x0) //FMD, vertical tearing count of pn (under)
	};
}PE_O22_IPC_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800330 RO 0x0000_0000
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
}PE_O22_IPC_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800334 RO 0x0000_0000
	UINT32 r_inv_inversed_cnt               :16;	//(15:0,RO,0x0) //
	UINT32 r_inv_original_cnt               :16;	//(31:16,RO,0x0) //
	};
}PE_O22_IPC_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800338 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IPC_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80033C RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IPC_STATUS_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800340 RW 0x00EC_1200
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
}PE_O22_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800344 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800348 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O22_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80034C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800350 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800354 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800358 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80035C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O22_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800360 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O22_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800364 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O22_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800368 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O22_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80036C RW 0x0000_04C8
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
}PE_O22_CLC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800370 RW 0x0010_2000
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
}PE_O22_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800374 RW 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RW,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O22_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800378 RW 0x0437_077F
	UINT32 x1                               :12;	//(11:0,RW,0x077F) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RW,0x0437) //y1
	UINT32 resvd1                           :4;
	};
}PE_O22_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80037C RO 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RO,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RO,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O22_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800380 RO 0x01DF_02CF
	UINT32 x1                               :12;	//(11:0,RO,0x02CF) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RO,0x01DF) //y1
	UINT32 resvd1                           :4;
	};
}PE_O22_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800384 RO 0x0000_0068
	UINT32 y_g_s_apl                        :10;	//(9:0,RO,0x068) //data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//(19:10,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//(29:20,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_O22_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800388 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O22_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80038C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O22_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800390 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	??"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//(12,RW,0x00) //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//(14:13,RW,0x00) //histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//(15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//(28,RW,0x00) //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	//30 //histogram read mode enable
	UINT32 hist_read_done                   :1;	//(31,RW,0x00) //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_O22_TPD_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800394 RO 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RO,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O22_TPD_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800398 RW 0x8080_2000
	UINT32 enable                           :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 y_offset                         :10;	//(13:4,RW,0x0200) //
	UINT32 resvd1                           :2;
	UINT32 center_position                  :8;	//(23:16,RW,0x80) //center position for Y gain control
	UINT32 y_gain                           :8;	//(31:24,RW,0x80) //
	};
}PE_O22_LVCRTL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80039C RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0000_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O22_TPD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003A0 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003A4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003A8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003AC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_TNR_STATUS_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003C0 RW 0x0000_0000
	UINT32 reg_gmv_rst                      :1;	//(0,RW,0x00) //
	UINT32 reg_bmv_rst                      :1;	//(1,RW,0x00) //
	UINT32 reg_me_rst                       :1;	//(2,RW,0x00) //
	UINT32 reg_mc_rst                       :1;	//(3,RW,0x00) //
	UINT32 reg_ma_rst                       :1;	//(4,RW,0x00) //
	UINT32 resvd                            :27;
	};
}PE_O22_TNR_RESET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003D0 RW 0x0000_0000
	UINT32 resvd0                           :2;
	UINT32 reg_a_normalize_en               :1;	//(2,RW,0x00) //
	UINT32 reg_t_normalize_en               :1;	//(3,RW,0x00) //
	UINT32 reg_t_cut_resolution             :2;	//(5:4,RW,0x00) //
	UINT32 reg_ne_normalize_en              :1;	//(6,RW,0x00) //
	UINT32 resvd1                           :9;
	UINT32 reg_cross_th_ne                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_cross_th                     :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003D4 RW 0x0000_0000
	UINT32 reg_mul_base_t                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_mul_base_e                   :8;	//(15:8,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O22_TNR_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003D8 RW 0x0000_0000
	UINT32 reg_a_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003DC RW 0x0000_0000
	UINT32 reg_a_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_a_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_a_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_a_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003E0 RW 0x0000_0000
	UINT32 reg_t_lut_edge_y0                :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_edge_x0                :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_edge_y1                :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_edge_x1                :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003E4 RW 0x0000_0000
	UINT32 reg_t_lut_detail_y0              :8;	//(7:0,RW,0x0) //
	UINT32 reg_t_lut_detail_x0              :8;	//(15:8,RW,0x0) //
	UINT32 reg_t_lut_detail_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_t_lut_detail_x1              :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003E8 RW 0x0000_0000
	UINT32 reg_edge_minmax_y0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_edge_minmax_x0               :8;	//(15:8,RW,0x0) //
	UINT32 reg_edge_minmax_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_minmax_x1               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003EC RW 0x0000_0000
	UINT32 reg_detail_minmax_y0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_detail_minmax_x0             :8;	//(15:8,RW,0x0) //
	UINT32 reg_detail_minmax_y1             :8;	//(23:16,RW,0x0) //
	UINT32 reg_detail_minmax_x1             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003F0 RW 0x0000_0000
	UINT32 reg_sel_ne_type                  :2;	//(1:0,RW,0x00) //0:(Y - TNR_Y), 1:(Y - SNR_Y), 2:(C - SNR_C)
	UINT32 reg_sel_re_type                  :1;	//(2,RW,0x00) //0:(still region), 1:(flat region)
	UINT32 resvd0                           :1;
	UINT32 reg_sel_at_mode                  :2;	//(5:4,RW,0x00) //0:(A), 1:(T), 2:(max(A,T)), 3:(A,T separate)
	UINT32 resvd1                           :2;
	UINT32 reg_hist_xscale                  :3;	//(10:8,RW,0x00) //histogram x-axi resolution ( 0: 0,1,2??, 1: 0,2,4??
	UINT32 resvd2                           :1;
	UINT32 reg_hist_yscale                  :2;	//(13:12,RW,0x00) //histogram cut resolution
	UINT32 resvd3                           :2;
	UINT32 reg_th_atmap                     :8;	//(23:16,RW,0x0) //at_map threshold ( flat rgion valid threshold )
	UINT32 reg_th_motion                    :8;	//(31:24,RW,0x0) //motion threshiold ( still region valid threshold )
	};
}PE_O22_TNR_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003F4 RW 0x0000_0000
	UINT32 nd0_hue_bin_6                      :8;  //  7: 0
	UINT32 nd0_hue_bin_7                      :8;  // 15: 8
	UINT32 nd0_hue_bin_8                      :8;  // 23:16
	UINT32 nd0_hue_bin_9                      :8;  // 31:24
	};
}PE_O22_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003F8 RW 0x0000_0000
	UINT32 nd1_hue_bin_6                      :8;  //  7: 0
	UINT32 nd1_hue_bin_7                      :8;  // 15: 8
	UINT32 nd1_hue_bin_8                      :8;  // 23:16
	UINT32 nd1_hue_bin_9                      :8;  // 31:24
	};
}PE_O22_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8003FC RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,RW,0x00) //
	};
}PE_O22_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800400 RO 0x0000_0000
	UINT32 valid_cnt                        :16;	//(15:0,RO,0x0) //# of valid region
	UINT32 resvd                            :16;
	};
}PE_O22_TNR_NE_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800404 RO 0x0000_0000
	UINT32 hist_1                           :16;	//(15:0,RO,0x0) //hist[1]
	UINT32 hist_0                           :16;	//(31:16,RO,0x0) //hist[0]
	};
}PE_O22_TNR_NE_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800408 RO 0x0000_0000
	UINT32 hist_3                           :16;	//(15:0,RO,0x0) //hist[3]
	UINT32 hist_2                           :16;	//(31:16,RO,0x0) //hist[2]
	};
}PE_O22_TNR_NE_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80040C RO 0x0000_0000
	UINT32 hist_5                           :16;	//(15:0,RO,0x0) //hist[5]
	UINT32 hist_4                           :16;	//(31:16,RO,0x0) //hist[4]
	};
}PE_O22_TNR_NE_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800410 RO 0x0000_0000
	UINT32 hist_7                           :16;	//(15:0,RO,0x0) //hist[7]
	UINT32 hist_6                           :16;	//(31:16,RO,0x0) //hist[6]
	};
}PE_O22_TNR_NE_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800414 RO 0x0000_0000
	UINT32 hist_9                           :16;	//(15:0,RO,0x0) //hist[9]
	UINT32 hist_8                           :16;	//(31:16,RO,0x0) //hist[8]
	};
}PE_O22_TNR_NE_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800418 RO 0x0000_0000
	UINT32 hist_11                          :16;	//(15:0,RO,0x0) //hist[11]
	UINT32 hist_10                          :16;	//(31:16,RO,0x0) //hist[10]
	};
}PE_O22_TNR_NE_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80041C RO 0x0000_0000
	UINT32 hist_13                          :16;	//(15:0,RO,0x0) //hist[13]
	UINT32 hist_12                          :16;	//(31:16,RO,0x0) //hist[12]
	};
}PE_O22_TNR_NE_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800420 RO 0x0000_0000
	UINT32 hist_15                          :16;	//(15:0,RO,0x0) //hist[15]
	UINT32 hist_14                          :16;	//(31:16,RO,0x0) //hist[14]
	};
}PE_O22_TNR_NE_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800440 RW 0x00EC_1200
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
}PE_O22_HIST2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800444 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_HIST2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800448 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O22_HIST2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80044C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_HIST2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800450 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_HIST2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800454 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_HIST2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800458 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_HIST2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80045C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O22_HIST2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800460 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O22_HIST2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800464 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O22_HIST2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800468 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O22_HIST2_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80046C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O22_HIST2_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800470 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	??"31" : 31st bin
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
}PE_O22_HIST2_HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800474 RO 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RO,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O22_HIST2_HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800478 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O22_HIST2_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800480 RW 0x0000_0000
	UINT32 chroma_st_flt_ctrl_x0	:8;	//7:0
	UINT32 chroma_st_flt_ctrl_x1	:8;	//15:8
	UINT32 luma_st_flt_ctrl_x0		:8;	//23:16
	UINT32 luma_st_flt_ctrl_x1		:8;	//31:24
	};
}PE_O22_ND_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800484 RW 0x0000_0000
	UINT32 motion_x_tearing_gain	:8;	//7:0
	UINT32 motion_gain				:8;	//15:8
	};
}PE_O22_ND_FSW_CTRL_01_T;

typedef union {/* dummy for ipc_ctrl_00 */
	UINT32 udata32;
	struct {						//0xCC800488 RW 0x0000_0000
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
}PE_O22_ND_FSW_CTRL_02_T;

typedef union { /* dummy for tnr_ctrl_00 */
	UINT32 udata32;
	struct {						//0xCC80048C RW 0x0000_0000
	UINT32 reg_tnr_en                       :1;	//(0:0,RW,0x00) //
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
	UINT32 reg_tnr_single_en                :1;	//(16:16,RW,0x00) //TNR half_rate	: This field must be '0' if half_rate of register PE0_OP_MODE(0x0010) is '0'	'0' - 8x1 ME, '1': 4x1 ME
	UINT32 reg_decon_blend_en               :1;	//(17,RW,0x0) //chg
	UINT32 reg_minfo_mode32                 :2;	//(19:18,RW,0x00) //
	UINT32 reg_minfo_mode74                 :4;	//(23:20,RW,0x00) //
	UINT32 reg_sad_8x3_iir_alpha            :8;	//(31:24,RW,0x0) //for TNR, DNR
	};
}PE_O22_ND_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800490 RW 0x0000_0000
	UINT32 win_y0                           :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 win_x0                           :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 win_mode                         :1;	//(30,RW,0x00) //0 := inside enabled	1 = outside enable
	UINT32 win_en                           :1;	//(31,RW,0x00) //
	};
}PE_O22_TNR_ETC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800494 RW 0x0000_0000
	UINT32 win_y1                           :12;	//(11:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 win_x1                           :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 win_tnrw_en                      :1;	//(31,RW,0x00) //this flag is valid only if "win_en = 1"
	};
}PE_O22_TNR_ETC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800498 RW 0x0000_0000
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
}PE_O22_TNR_ETC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80049C RW 0x0000_0000
	UINT32 reg_clc_minfo_dly                :3;	//(2:0,RW,0x0) //1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd0                           :1;
	UINT32 reg_clc_flt_dly                  :3;	//(6:4,RW,0x0) //1: -2	2: -4	3: +2	4: +4	dafault: +0
	UINT32 resvd1                           :25;
	};
}PE_O22_TNR_ETC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004A0 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004A4 RW 0x0000_0000
	UINT32 reg_sad_mc_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_mc_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004A8 RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004AC RW 0x0000_0000
	UINT32 reg_abs_mv_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_abs_mv_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004B0 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y0            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x0            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y1            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x1            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004B4 RW 0x0000_0000
	UINT32 reg_sad_ma_ctrl_pt_y2            :8;	//(7:0,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x2            :8;	//(15:8,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_y3            :8;	//(23:16,RW,0x0) //
	UINT32 reg_sad_ma_ctrl_pt_x3            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_TNR_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004B8 RW 0x0000_0000
	UINT32 mif_prefetch_ctrl                :8;	//(7:0,RW,0x0) //reg_en_pf_t1_m   = reg_mif_prefetch_ctrl[7];	reg_en_pf_t4_y   = reg_mif_prefetch_ctrl[6];	reg_en_pf_t3_c   = reg_mif_prefetch_ctrl[5];	reg_en_pf_t3_y   = reg_mif_prefetch_ctrl[4];	reg_en_pf_t2_c   = reg_mif_prefetch_ctrl[3];	reg_en_pf_t2_y   = reg_mif_prefetch_ctrl[2];	reg_en_pf_t1_c   = reg_mif_prefetch_ctrl[1];	reg_en_pf_t1_y   = reg_mif_prefetch_ctrl[0];
	UINT32 mif_vreverse_en                  :11;	//(18:8,RW,0x0) //reg_en_vreverse_tnrw_m  = reg_mif_vreverse_en[10];	reg_en_vreverse_tnrw_c  = reg_mif_vreverse_en[9];	reg_en_vreverse_tnrw_y  = reg_mif_vreverse_en[8];	reg_en_vreverse_t1_m  = reg_mif_vreverse_en[7];	reg_en_vreverse_t4_y  = reg_mif_vreverse_en[6];	reg_en_vreverse_t3_c  = reg_mif_vreverse_en[5];	reg_en_vreverse_t3_y  = reg_mif_vreverse_en[4];	reg_en_vreverse_t2_c  = reg_mif_vreverse_en[3];	reg_en_vreverse_t2_y  = reg_mif_vreverse_en[2];	reg_en_vreverse_t1_c  = reg_mif_vreverse_en[1];	reg_en_vreverse_t1_y  = reg_mif_vreverse_en[0];
	UINT32 resvd0                           :1;
	UINT32 global_cg_blk_off                :4;	//(23:20,RW,0x00) //[Debug] Global Clock Gating Sub Block Off	[0] : Global Clock Gating IPC Off	[1] : Global Clock Gating CLC Off	[2] : NA	[3] : NA
	UINT32 power_cg_blk_off                 :4;	//(27:24,RW,0x00) //[Debug] Power Clock Gating Sub Block Off	[0] : FIM Power Clock Gating Off	[1] : NA	[2] : NA	[3] : NA
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_DEBUG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004C0 RW 0x0000_0000
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
}PE_O22_FBC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004C4 RW 0x0000_0000
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
}PE_O22_FBC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004D0 RW 0xFF00_FF00
	UINT32 reg_gfd_h_th0_a                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_h_th1_a                  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_gfd_h_th0_b                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_gfd_h_th1_b                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O22_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004D4 RW 0x0000_0000
	UINT32 reg_gfd_s_th                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_v_th                     :8;	//(15:8,RW,0x00) //
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//(31:30,RW,0x0) //0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_O22_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004D8 RO 0x0000_0000
	UINT32 reg_gfd_count_a01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Top
	};
}PE_O22_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004DC RO 0x0000_0000
	UINT32 reg_gfd_count_a11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_O22_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004E0 RO 0x0000_0000
	UINT32 reg_gfd_count_b01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Top
	};
}PE_O22_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8004E4 RO 0x0000_0000
	UINT32 reg_gfd_count_b11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_O22_GFD_STAT_03_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC800500 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 load_enable                      :1;	//(1,RW,0x00) //load_enable	  enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //load_type	 0 := auto load:  load when reg. write	 1 = manual load: load w/ load_enable = '1'
	UINT32 resvd1                           :29;
	};
}PE_O22_PE0_LOAD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800504 RW 0x0000_0000
	UINT32 intr_enable                      :1;	//(0,RW,0x00) //interrupt enable
	UINT32 resvd0                           :3;
	UINT32 intr_src                         :3;	//(6:4,RW,0x00) //interrupt generation mode. Interrupt triggered by the following causes.	'000 :=  NA	'001 =  NA	'010 = NA	'011 = NA	'100 = dnr_end	'101 = line pos
	UINT32 resvd1                           :1;
	UINT32 timer_rst_sel                    :1;	//(8,RW,0x00) //0:= pic_init	1 = pic_start
	UINT32 resvd2                           :7;
	UINT32 intr_line_pos                    :11;	//(26:16,RW,0x00) //the line position on which the interrupt triggered
	UINT32 resvd3                           :5;
	};
}PE_O22_PE0_INTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800508 RO 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 dnr_frame_id                     :8;	//(23:16,RO,0x0) //DNR_FRAME_ID	increment every dnr_end
	UINT32 pic_init_frame_id                :4;	//(27:24,RO,0x00) //PIC_INIT_FRAME_ID
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_STATUS0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80050C RO 0x0000_0000
	UINT32 line_cnt                         :11;	//(10:0,RO,0x00) //
	UINT32 resvd                            :5;
	UINT32 timer_cnt                        :16;	//(31:16,RO,0x0) //timer count by de_clk from pic_init/pic_start to pic_end
	};
}PE_O22_PE0_STATUS1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800510 RW 0x0000_C000
	UINT32 resvd0                           :8;
	UINT32 reg_sd_5l_mode_en                :1;	//(8,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 dnr_out_420_vsample_mode         :1;	//(12,RW,0x00) //0 := 0,3,4,7,??1 = 0,2,4,6,??
	UINT32 dnr_out_cs_type                  :3;	//(15:13,RW,0x6) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 detour_enable                    :1;	//(16,RW,0x00) //
	UINT32 half_rate_en                     :1;	//(17,RW,0x00) //should be enabled for the interlaced source	should be enabled for running IFC
	UINT32 resvd2                           :2;
	UINT32 ibuf_en                          :2;	//(21:20,RW,0x0) //(20) input buffer enable Y 	(21) input buffer enable C
	UINT32 dnr_out_422_hsample_mode         :1;	//(22,RW,0x00) //0 := 0,2,4,6,??1 = 1,3,5,7,??
	UINT32 resvd3                           :1;
	UINT32 dnr_in_lsb_mode                  :2;	//(25:24,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 dnr_out_lsb_mode                 :2;	//(27:26,RW,0x00) //00 := bypass original	01 := bypass original	10 := "00"	11 := "11"
	UINT32 resvd4                           :2;
	UINT32 m_run_id                         :2;	//(31:30,RW,0x00) //
	};
}PE_O22_PE0_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800514 RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE: ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd0                           :1;
	UINT32 chroma_sampling_type             :3;	//(15:13,RW,0x00) //chroma_sampling_type	'000 := 420 (MPEG-2)	'001 = 420 (MPEG-1)	'100 =  420 (CVI)	'101 = 422 (CVI)	'110 = 444 (CVI)
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_IN_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800518 RW 0x0000_0000
	UINT32 hoffset                          :12;	//(11:0,RW,0x00) //ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd                            :18;
	UINT32 hsize_sel                        :1;	//(30,RW,0x00) //0 := PE0_OUT_SIZE -> in_hsize	1 = PE0_OUT_SIZE -> out_hsize
	UINT32 crop_en                          :1;	//(31,RW,0x00) //
	};
}PE_O22_PE0_IN_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80051C RW 0x0438_0780
	UINT32 hsize                            :12;	//(11:0,RW,0x0780) //HSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå
	UINT32 resvd0                           :4;
	UINT32 vsize                            :12;	//(27:16,RW,0x0438) //VSIZE : ÏßùÏàòÎß?Í∞Ä?? ?Ä?òÎäî ÏßÄ?êÌïòÏßÄ ?äÏùå	 (progressive format Í∏∞Ï?)
	UINT32 resvd1                           :4;
	};
}PE_O22_PE0_OUT_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800520 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 resvd1                           :4;
	};
}PE_O22_WIN_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800524 RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O22_WIN_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800528 RW 0x0000_0000
	UINT32 x0                               :11;	//(10:0,RW,0x00) //X0
	UINT32 resvd0                           :5;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //Y0
	UINT32 ac_bnr_feature_cal_mode          :2;	//(29:28,RW,0x00) //AC-BNR feature cal. mode	'00 := full-screen mode	'01 =  reserved	'10 = active window mode - manual window setting by 	        reg_win_ctrl_2 & reg_win_ctrl_3	'11 = active window mode - auto window setting by black	         boundary detection
	UINT32 resvd1                           :2;
	};
}PE_O22_WIN_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80052C RW 0x0438_0780
	UINT32 x1                               :11;	//(10:0,RW,0x0780) //X1
	UINT32 resvd0                           :5;
	UINT32 y1                               :12;	//(27:16,RW,0x0438) //Y1
	UINT32 resvd1                           :4;
	};
}PE_O22_WIN_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800530 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O22_CUP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800534 RW 0x0000_0001
	UINT32 bypass                           :1;	//(0,RW,0x1) //0 : chroma upsample enable	1 : bypass
	UINT32 reg_v_upsample_en                :1;	//(1,RW,0x0) //0 : vertical repeat 	1 : vertical interpolation enable
	UINT32 reg_h_upsample_en                :1;	//(2,RW,0x0) //0 : horizontal repeat 	1 : horizontal interpolation enable
	UINT32 reg_sd_mode                      :1;	//(3,RW,0x00) //0 : for HD source	1 : for SD source
	UINT32 resvd                            :28;
	};
}PE_O22_CUP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800538 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_CUP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800580 RW 0x0000_0000
	UINT32 reg_glb_tearing_th               :8;	//(7:0,RW,0x0) //
	UINT32 reg_glb_mode_th                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_tearing_strength             :1;	//(12,RW,0x00) //
	UINT32 reg_glb_tearing_cnt_normal       :3;	//(15:13,RW,0x00) //
	UINT32 reg_vf_a_th                      :8;	//(23:16,RW,0x0) //
	UINT32 resvd                            :6;
	UINT32 reg_vflt_force_en                :1;	//(30,RW,0x00) //
	UINT32 reg_vflt_en                      :1;	//(31,RW,0x00) //
	};
}PE_O22_VFILTER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800584 RW 0x0000_0000
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
}PE_O22_VFILTER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800588 RW 0x0000_0000
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
}PE_O22_VFILTER_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80058C RW 0x0000_1400
	UINT32 cti_en                           :1;	//(0,RW,0x00) //CTI enable
	UINT32 cti_clipping_mode                :1;	//(1,RW,0x00) //op mode	'0' : CTI	'1': peaking(for debug)
	UINT32 cti_pre_flt_mode                 :1;	//(2,RW,0x00) //pre-filtering	0 : off	1 : on
	UINT32 cti_tap                          :2;	//(4:3,RW,0x00) //CTI filter tap size	'0' : 7-tap	'1': 5-tap	'2': 3_2-tap	'3': 3-tap
	UINT32 resvd0                           :3;
	UINT32 cti_gain                         :8;	//(15:8,RW,0x14) //CTI gain(3.5u)
	UINT32 cti_debug_mode                   :3;	//(18:16,RW,0x00) //debug mode	"000" : normal display	"100" : coring map(cb)	"101" : coring map(cr)	"110" : avg(cb)	"111" : avg(cr)
	UINT32 resvd1                           :13;
	};
}PE_O22_CTI_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800590 RW 0x0020_2101
	UINT32 cti_coring_th0                   :8;	//(7:0,RW,0x1) //CTI coring th0
	UINT32 cti_coring_th1                   :8;	//(15:8,RW,0x21) //CTI coring th1
	UINT32 cti_coring_smooth                :3;	//(18:16,RW,0x0) //NOT USED
	UINT32 resvd0                           :1;
	UINT32 reg_cti_tap2                     :2;	//(21:20,RW,0x2) //CTI coring map size	"00" : 7-tap	"01" : 5-tap	"10" : 3-tap	o.w : 7-tap
	UINT32 resvd1                           :10;
	};
}PE_O22_CTI_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800594 RW 0x0000_0000
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
	UINT32 reg_face_obj_sel                 :1;	//(11,RW,0x0) //0: dnr obc(4K?¥Ìïò, internal), 1: nd obc(4K Ï¥àÍ≥º(8K), external)	Not used in O-series(Only E series)
	UINT32 resvd0                           :4;
	UINT32 reg_win_en                       :1;	//(16,RW,0x00) //win control enable	   debug_enable should be '0'
	UINT32 reg_bdr_en                       :1;	//(17,RW,0x00) //border enable
	UINT32 reg_win_inout                    :1;	//(18,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 reg_ipc_motion_en                :1;	//(21,RW,0x0) //hmc_flag ?Ä??=> 1: {[5:1],1'b0}, 0: [5:0]
	UINT32 reg_motion_bit_ctrl              :3;	//(24:22,RW,0x00) //0x0: no scale, 0x1: x2, 0x2, 0x4 ...
	UINT32 reg_delta_ifc_th                 :7;	//(31:25,RW,0x0) //applied ifc when delta is greater than th
	};
}PE_O22_DNR_MAX_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800598 RW 0x0000_0000
	UINT32 reg_dbg_en                       :1;	//(0,RW,0x00) //debug bar en
	UINT32 reg_show_f3d                     :1;	//(1,RW,0x00) //
	UINT32 reg_show_bnr                     :1;	//(2,RW,0x00) //show debug bar for bnr	(acness,acness gain, dc_gain)
	UINT32 reg_f3d_mode                     :1;	//(3,RW,0x00) //
	UINT32 reg_acness_or_acness_gain        :1;	//(4,RW,0x00) //0 : acness (blue, green)	1 : acness gain (yellow, red)
	UINT32 resvd                            :27;
	};
}PE_O22_DNR_DBAR_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80059C RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_detect_level_th              :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O22_REG_C420_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005A0 RW 0x0000_0000
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
}PE_O22_MNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005A4 RW 0x0000_0000
	UINT32 reg_mmd_y_max                    :8;	//(7:0,RW,0x0) //edge th, if(mmd > th) edge
	UINT32 reg_mmd_y_min                    :8;	//(15:8,RW,0x0) //reg_mnr_s2_ratio_min
	UINT32 reg_mmd_x_max                    :8;	//(23:16,RW,0x0) //reg_mnr_s2_ratio_max
	UINT32 reg_mmd_x_min                    :8;	//(31:24,RW,0x0) //reg_mnr_s2_mmd_min
	};
}PE_O22_MNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005A8 RW 0x0000_0000
	UINT32 reg_mnr_debug_mode               :4;	//(3:0,RW,0x00) //0: sel_mmd	1: final_sel_mmd	2: fil_diff_th_map	3: snr_rgn_flag	4: sel_mmd_gain	5: final_gain	6: pattern_flag	7: chroma_gain	8: dist_gain	9: prv mmd map	A: mmd var	B: O22 New, final gain
	UINT32 reg_mnr_debug_en                 :1;	//(4,RW,0x00) //
	UINT32 resvd                            :19;
	UINT32 reg_equal_snr_th                 :8;	//(31:24,RW,0x0) //
	};
}PE_O22_MNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005AC RW 0x0000_0000
	UINT32 reg_blur_sel                     :1;	//(0,RW,0x00) //
	UINT32 reg_pattern_en                   :1;	//(1,RW,0x00) //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_equal_th                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_scale                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_MNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005B0 RW 0x0000_0000
	UINT32 reg_mmd_fil_x_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_x_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_x_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_x_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_MNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005B4 RW 0x0000_0000
	UINT32 reg_mmd_fil_y_3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_fil_y_2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_mmd_fil_y_1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_mmd_fil_y_0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_MNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005B8 RW 0x0404_0A40
	UINT32 reg_bnr_ac_detail_max            :8;	//(7:0,RW,0x40) //detail gain th
	UINT32 reg_bnr_ac_detail_min            :8;	//(15:8,RW,0xA) //detail gain th
	UINT32 reg_bnr_diff_l                   :8;	//(23:16,RW,0x4) //th used to find big diff point
	UINT32 reg_bnr_diff_p                   :8;	//(31:24,RW,0x4) //th used to find point of inflection
	};
}PE_O22_DETAIL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005BC RW 0x0000_0000
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
}PE_O22_DC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005C0 RW 0x0000_0000
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
}PE_O22_DC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005C4 RW 0x0000_0000
	UINT32 reg_dc_var_en                    :1;	//(0,RW,0x0) //0x1
	UINT32 reg_dc_motion_en                 :1;	//(1,RW,0x0) //0x0
	UINT32 reg_dc_protection_en             :1;	//(2,RW,0x0) //0x1
	UINT32 resvd                            :7;
	UINT32 reg_dc_bnr_mastergain            :6;	//(15:10,RW,0x0) //0x20 is max.
	UINT32 reg_dc_bnr_chromagain            :8;	//(23:16,RW,0x0) //max value => x1 : 0x20, x2 : 0x40, x4 : 0x80
	UINT32 reg_dc_protection_th             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_DC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005C8 RW 0x0000_0000
	UINT32 reg_dc_bnr_var_th3               :8;	//(7:0,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th2               :8;	//(15:8,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th1               :8;	//(23:16,RW,0x0) //dc variance gain th
	UINT32 reg_dc_bnr_var_th0               :8;	//(31:24,RW,0x0) //dc variance gain th, if(reg_dc_var_en == 0) reg_dc_var_y_th0 = manual variance gain value
	};
}PE_O22_DC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005CC RW 0x0000_0000
	UINT32 reg_dc_motion_y_min              :8;	//(7:0,RW,0x0) //motion gain yÏ∂?
	UINT32 reg_dc_motion_y_max              :8;	//(15:8,RW,0x0) //motion gain yÏ∂?
	UINT32 resvd                            :16;
	};
}PE_O22_DC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005D0 RW 0x0000_0000
	UINT32 reg_dc_var_y_th0                 :8;	//(7:0,RW,0x0) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th1                 :8;	//(15:8,RW,0x0) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th2                 :8;	//(23:16,RW,0x0) //variance gain yÏ∂?
	UINT32 reg_dc_var_y_th3                 :8;	//(31:24,RW,0x0) //variance gain yÏ∂?
	};
}PE_O22_DC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005D4 RW 0xB30B_0B4F
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
}PE_O22_AC_BNR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005D8 RW 0x0F19_370B
	UINT32 reg_bnr_ac_global_motion_th      :8;	//(7:0,RW,0xB) //0x0B
	UINT32 reg_bnr_ac_h_acness_max          :8;	//(15:8,RW,0x37) //th for acness gain
	UINT32 reg_bnr_ac_h_acness_min          :8;	//(23:16,RW,0x19) //th for acness gain
	UINT32 reg_bnr_ac_bin_th                :8;	//(31:24,RW,0xF) //
	};
}PE_O22_AC_BNR_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005DC RW 0x0A20_4060
	UINT32 reg_bnr_ac_motion_3              :8;	//(7:0,RW,0x60) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_2              :8;	//(15:8,RW,0x40) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_1              :8;	//(23:16,RW,0x20) //motion gain xÏ∂?
	UINT32 reg_bnr_ac_motion_0              :8;	//(31:24,RW,0xA) //motion gain xÏ∂?
	};
}PE_O22_AC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005E0 RO 0x0000_0000
	UINT32 c420_tearing_cnt                 :16;	//(15:0,RO,0x0) //
	UINT32 global_motion_iir                :8;	//(23:16,RO,0x0) //
	UINT32 global_dc_gain                   :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005E4 RW 0x3060_A0FF
	UINT32 reg_bnr_ac_motion_y_3            :8;	//(7:0,RW,0xFF) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_2            :8;	//(15:8,RW,0xA0) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_1            :8;	//(23:16,RW,0x60) //motion gain yÏ∂?
	UINT32 reg_bnr_ac_motion_y_0            :8;	//(31:24,RW,0x30) //motion gain yÏ∂?
	};
}PE_O22_AC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005E8 RW 0x1937_5000
	UINT32 reg_bnr_ac_v_init_offset         :3;	//(2:0,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_h_init_offset         :3;	//(5:3,RW,0x00) //offset for init position
	UINT32 reg_bnr_ac_acness_resol_v        :2;	//(7:6,RW,0x00) //0x0 is original, 0x3 : /8
	UINT32 reg_bnr_ac_debug_mode            :4;	//(11:8,RW,0x00) //debug mode 	0 : bypass	1 : block line map	2 : motion	3 : motion gain	4 : pos_gain_H	5 : pos_gain_V	6 : AC BNR gain_H	7 : AC BNR gain_V	8 : Binary map	9 : detail map	10: detail gain	11: fil_motion_th	12: filter level map	13: AC final gain_H	14: AC final gain_V
	UINT32 reg_bnr_ac_hsy_mode              :4;	//(15:12,RW,0x05) //stable init position mode
	UINT32 reg_bnr_ac_v_acness_max          :8;	//(23:16,RW,0x37) //
	UINT32 reg_bnr_ac_v_acness_min          :8;	//(31:24,RW,0x19) //
	};
}PE_O22_AC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005EC RO 0x0000_0000
	UINT32 acness_v_l                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_g                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005F0 RW 0xFA96_3201
	UINT32 reg_bnr_ac_detail_th4            :8;	//(7:0,RW,0x1) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th3            :8;	//(15:8,RW,0x32) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th2            :8;	//(23:16,RW,0x96) //detail th used in AC-BNR final mux
	UINT32 reg_bnr_ac_detail_th1            :8;	//(31:24,RW,0xFA) //detail th used in AC-BNR final mux
	};
}PE_O22_AC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005F4 RW 0x00FF_C0C0
	UINT32 reg_bnr_ac_pos_gain_h2           :8;	//(7:0,RW,0xC0) //SD : 0x40, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h1           :8;	//(15:8,RW,0xC0) //SD : 0x80, HD : 0xC0
	UINT32 reg_bnr_ac_pos_gain_h0           :8;	//(23:16,RW,0xFF) //SD : 0xFF, HD : 0xFF
	UINT32 reg_bnr_ac_detail_gain_th        :8;	//(31:24,RW,0x0) //0x00
	};
}PE_O22_AC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005F8 RW 0x80FF_8040
	UINT32 reg_bnr_ac_pos_gain_l2           :8;	//(7:0,RW,0x40) //SD : 0x40, HD : 0x40
	UINT32 reg_bnr_ac_pos_gain_l1           :8;	//(15:8,RW,0x80) //SD : 0x80, HD : 0x80
	UINT32 reg_bnr_ac_pos_gain_l0           :8;	//(23:16,RW,0xFF) //SD : 0x80, HD : 0xFF
	UINT32 reg_bnr_ac_pos_gain_h3           :8;	//(31:24,RW,0x80) //SD : 0x00, HD : 0x80
	};
}PE_O22_AC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8005FC RO 0x0000_0000
	UINT32 h_init                           :8;	//(7:0,RO,0x0) //
	UINT32 v_init                           :8;	//(15:8,RO,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_vfilter_tearing_cnt          :12;	//(31:20,RO,0x00) //
	};
}PE_O22_DNR_STAT_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800600 RW 0x0000_0E20
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
}PE_O22_AC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800604 RW 0x0009_8000
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
}PE_O22_AC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800608 RW 0xFF00_FF00
	UINT32 reg_ac_detail_gain_y_min         :8;	//(7:0,RW,0x0) //detail gain yÏ∂?
	UINT32 reg_ac_detail_gain_y_max         :8;	//(15:8,RW,0xFF) //detail gain yÏ∂?
	UINT32 reg_bnr_ac_acness_y_min          :8;	//(23:16,RW,0x0) //acness gain y  Ï∂?
	UINT32 reg_bnr_ac_acness_y_max          :8;	//(31:24,RW,0xFF) //acness gain y  Ï∂?
	};
}PE_O22_AC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80060C RW 0xFF00_FF00
	UINT32 reg_ac_detail_alpha2_y_min       :8;	//(7:0,RW,0x0) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha2_y_max       :8;	//(15:8,RW,0xFF) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha4_y_min       :8;	//(23:16,RW,0x0) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	UINT32 reg_ac_detail_alpha4_y_max       :8;	//(31:24,RW,0xFF) //ac bnr final mux?êÏÑú ?∞Ïù¥??detail gain ??yÏ∂?
	};
}PE_O22_AC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800610 RW 0x0000_FFFF
	UINT32 reg_g_motion_manual              :8;	//(7:0,RW,0xFF) //
	UINT32 reg_acness_scale_mul             :8;	//(15:8,RW,0xFF) //
	UINT32 reg_bnr_ac_detail_max            :8;	//(23:16,RW,0x0) //
	UINT32 reg_bnr_ac_detail_min            :8;	//(31:24,RW,0x0) //
	};
}PE_O22_AC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800614 RW 0x00E8_D800
	UINT32 reg_y_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_y_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_y_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|Î°?[7:0] ?†ÌÉù	1: |y''|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd1                           :1;
	UINT32 reg_y_drvt2_hcoef_sel            :3;	//(10:8,RW,0x00) //5tap, h[0, 0, 8, 8, 0, -8, -8, -0, -0]/16	7tap, h[0, 4, 6, 6, 0, -6, -6, -4, -0]/16	9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_medge_meth                   :1;	//(11,RW,0x01) //0: 13x3 window (???ºÏù∏?¥Îùº???¥Îãπ?òÎ©¥ Î™®Îëê ?âÏπ†)	1 :13x3 window (?©ÏùÑ Íµ¨Ìï¥??coring)
	UINT32 reg_medge_th                     :8;	//(19:12,RW,0x8D) //diff??th
	UINT32 reg_medge_coring_th              :8;	//(27:20,RW,0xE) //?íÏù¥??th
	UINT32 reg_medge_ch_tap                 :2;	//(29:28,RW,0x00) //0: 13tap	1: 11tap	2: 9tap
	UINT32 reg_edge_meth                    :2;	//(31:30,RW,0x00) //diff??center?¨Ìï® on/off
	};
}PE_O22_IFC_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800618 RW 0x0C00_3820
	UINT32 reg_edge_ddrvt_gain_y1           :8;	//(7:0,RW,0x20) //
	UINT32 reg_edge_ddrvt_gain_x1           :8;	//(15:8,RW,0x38) //
	UINT32 reg_edge_ddrvt_gain_y0           :8;	//(23:16,RW,0x0) //
	UINT32 reg_edge_ddrvt_gain_x0           :8;	//(31:24,RW,0xC) //?êÎûò y edge gain
	};
}PE_O22_IFC_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80061C RW 0x0000_0000
	UINT32 reg_c_drvt_hcoef_sel             :3;	//(2:0,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 resvd0                           :1;
	UINT32 reg_c_ddrvt_hcoef_sel            :2;	//(5:4,RW,0x00) //0: 9tap, h[4, 4, 4, 4, 0, -4, -4, -4, -4]/16	1: 9tap, h[2, 2, 6, 6, 0, -6, -6, -2, -2]/16	2: 5tap, h[0, 0, 8, 8, 0, -8, -8, -0,  0]/16	3: 5tap, h[0, 0, 4, C, 0, -C, -4, -0,  0]/16
	UINT32 reg_c_edge_gain_res              :1;	//(6,RW,0x00) //0: |y''|Î°?[7:0] ?†ÌÉù	1: |y''|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd1                           :25;
	};
}PE_O22_IFC_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800620 RW 0x1100_6E20
	UINT32 reg_c_edge_gain_y1               :8;	//(7:0,RW,0x20) //
	UINT32 reg_c_edge_gain_x1               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_c_edge_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_c_edge_gain_x0               :8;	//(31:24,RW,0x11) //
	};
}PE_O22_IFC_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800624 RW 0x0003_1203
	UINT32 reg_crs_para_tap                 :2;	//(1:0,RW,0x03) //0 : 5tap, h[0, 1, 1, 1, 1 ,1]	1 : 4tap, h[0, 0, 1, 1, 1, 1]	2 : 4tap, h[0, 1, 1, 1, 1, 0]	3 : 6tap, h[1, 1, 1, 1, 1, 1]
	UINT32 reg_cdst_th                      :10;	//(11:2,RW,0x080) //Cb, Cr Ï∞®Ïù¥Í∞Ä ??Í∞??¥ÏÉÅ?¥Ïñ¥???†Ìö®
	UINT32 reg_crs_op_tap                   :2;	//(13:12,RW,0x01) //0 : 9 tap	1 : 7 tap	2 : 5 tap
	UINT32 reg_crs_gain_res                 :1;	//(14,RW,0x00) //0: |c diff|Î°?[7:0] ?†ÌÉù	1: |c diff|/4Î°?[9:2] ?†ÌÉù
	UINT32 resvd0                           :1;
	UINT32 reg_cdiff_hcoef_sel              :2;	//(17:16,RW,0x03) //left/right diff??coefficient (Ï¥??©Ï? 255)	0 : h[0x00, 0x08, 0x08, 0x0A, 0x1E, 0xC8]/256	1 : h[0x00, 0x10, 0x10, 0x14, 0x40, 0x8C]/256
	UINT32 resvd1                           :10;
	UINT32 reg_crs_point                    :2;	//(29:28,RW,0x00) //
	UINT32 reg_crs_meth                     :2;	//(31:30,RW,0x00) //0 : (1Ï°∞Í±¥) +  L/R Í∞ÅÍ∞Å ?¥Î? Î∂Ä?∏ÍπåÏßÄ Í∞ôÏ?Í∞Ä	1 : (2Ï°∞Í±¥) +  L/R ?úÎ°ú Î∂Ä?∏ÎèÑ Î∞òÎ??∏Í? 	2 : L/RÎ™®Îëê chroma diffÍ∞Ä thresholdÎ≥¥Îã§ ?∞Í?
	};
}PE_O22_IFC_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800628 RW 0x0000_6616
	UINT32 reg_crs_gain_y1                  :8;	//(7:0,RW,0x16) //
	UINT32 reg_crs_gain_x1                  :8;	//(15:8,RW,0x66) //
	UINT32 reg_crs_gain_y0                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IFC_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80062C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800630 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800634 RW 0x2400_0000
	UINT32 reg_ifc_en                       :1;	//(0,RW,0x00) //0 : 0ff / 1 : on
	UINT32 reg_clp_on                       :1;	//(1,RW,0x00) //0 : 0ff / 1 : Max clipping
	UINT32 resvd0                           :2;
	UINT32 reg_edge_en                      :1;	//(4,RW,0x00) //mmd en
	UINT32 resvd1                           :15;
	UINT32 reg_clp_tap                      :2;	//(21:20,RW,0x00) //0 : 13 tap	1 : 11 tap	2 : 9tap
	UINT32 reg_ifc_flt_sel                  :2;	//(23:22,RW,0x00) //3 : cross	2 : multi edge cedge	1 : yedge	0 : default
	UINT32 reg_debug_en                     :2;	//(25:24,RW,0x00) //0 : debug off	1 : blend debug on	2 : debug on
	UINT32 reg_debug_mode                   :4;	//(29:26,RW,0x09) //0 : operation mode	1 : cross check	2 : multi edge	3 : 	4 : cr edge gain	5 : cb edge gain	6 : y edge gain	7 : cross gain	8 : cross blend	9 : multi-edge blend	10 : 	11 : 2Ï∞®Î?Î∂?12 : 	13 : 1Ï∞®Î?Î∂?
	UINT32 reg_bld_tap                      :2;	//(31:30,RW,0x00) //0: ?ÜÏóê 2Í∞?average	1: ?ÜÏóê 1Í∞? center average
	};
}PE_O22_IFC_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800638 RW 0x0000_0000
	UINT32 reg_f0_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f0_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f0_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f1_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f0_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O22_ELLIPSE_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80063C RW 0x0000_0000
	UINT32 reg_f0_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_master               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_ELLIPSE_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800640 RW 0x0000_0000
	UINT32 reg_f1_h1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f0_w2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_ellipse_offset               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_ELLIPSE_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800644 RW 0x8004_0000
	UINT32 resvd                            :16;
	UINT32 reg_crs_zero_th                  :8;	//(23:16,RW,0x4) //cross point?êÏÑú cb-cr??0?ºÎ°ú Î≥¥Îäî ?ÅÌïúÍ∞?
	UINT32 reg_dst_cdst_th                  :8;	//(31:24,RW,0x80) //Ï¢åÏö∞ ?ÑÌÑ∞Í≥±Ìï¥Ïß?cdst ?©Ïùò Ï∞®Ïù¥
	};
}PE_O22_IFC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800648 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80064C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800650 RW 0x0640_11FF
	UINT32 reg_medge_gain_y1                :8;	//(7:0,RW,0xFF) //
	UINT32 reg_medge_gain_x1                :8;	//(15:8,RW,0x11) //
	UINT32 reg_medge_gain_y0                :8;	//(23:16,RW,0x40) //
	UINT32 reg_medge_gain_x0                :8;	//(31:24,RW,0x6) //1/3Î°?
	};
}PE_O22_IFC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800654 RW 0x0010_02A2
	UINT32 reg_crs_op_gain_isel             :2;	//(1:0,RW,0x02) //0 : max	1 : min	2 : average
	UINT32 reg_crs_op_gain_res              :1;	//(2,RW,0x00) //0: [7:0] ?†ÌÉù	1: [9:2] ?†ÌÉù
	UINT32 reg_crs_cdst_flt                 :3;	//(5:3,RW,0x04) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd0                           :1;
	UINT32 reg_crs_cdst_vmdn                :1;	//(7,RW,0x01) //5x5 median/max (v->h)
	UINT32 reg_crs_cdst_op_flt              :3;	//(10:8,RW,0x02) //0: off	1:  v-121	2: 5x3 average (diff)	3: median (v->h)	4: max
	UINT32 resvd1                           :5;
	UINT32 reg_op_wgain_coef1               :2;	//(17:16,RW,0x00) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef2               :2;	//(19:18,RW,0x00) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 reg_op_wgain_coef3               :2;	//(21:20,RW,0x01) //cross filter??Í≤ΩÏö∞,	0: gain x 1	1: gain x (1/2)	2: gain x (1/4)
	UINT32 resvd2                           :10;
	};
}PE_O22_IFC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800658 RW 0x8500_DCFF
	UINT32 reg_crs_op_gain_y1               :8;	//(7:0,RW,0xFF) //
	UINT32 reg_crs_op_gain_x1               :8;	//(15:8,RW,0xDC) //
	UINT32 reg_crs_op_gain_y0               :8;	//(23:16,RW,0x0) //
	UINT32 reg_crs_op_gain_x0               :8;	//(31:24,RW,0x85) //
	};
}PE_O22_IFC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80065C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800660 RW 0x2100_0000
	UINT32 resvd0                           :16;
	UINT32 reg_medge_op_th                  :8;	//(23:16,RW,0x0) //Î©Ä?∞Ïó£ÏßÄ ?ÅÏó≠ ?°ÎäîÍ≤?(3?ºÏù∏, Í∞?àò??
	UINT32 reg_mmd_gain_en                  :1;	//(24,RW,0x01) //
	UINT32 reg_mmd_gain_flt                 :2;	//(26:25,RW,0x00) //0: off	1: ?ÖÎ†•??21
	UINT32 reg_mmd_gain_tap                 :2;	//(28:27,RW,0x00) //0: 13	1: 11	2: 9
	UINT32 reg_mmd_gain_res                 :1;	//(29,RW,0x01) //0: [7:0] ?†ÌÉù	1: [9:2] ?†ÌÉù
	UINT32 resvd1                           :2;
	};
}PE_O22_IFC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800664 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_IFC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800668 RW 0x0080_B000
	UINT32 reg_mmd_gain_y1                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_mmd_gain_x1                  :8;	//(15:8,RW,0xB0) //
	UINT32 reg_mmd_gain_y0                  :8;	//(23:16,RW,0x80) //
	UINT32 reg_mmd_gain_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_IFC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80066C RW 0x0000_0000
	UINT32 reg_f1_w1_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f1_h2_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 reg_sel_output                   :1;	//(24,RW,0x0) //
	UINT32 resvd                            :7;
	};
}PE_O22_ELLIPSE_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800670 RW 0x0000_0000
	UINT32 reg_f1_el_mul_b                  :9;	//(8:0,RW,0x0) //
	UINT32 reg_f1_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f1_w2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 reg_f3_enable                    :1;	//(30,RW,0x0) //
	UINT32 reg_f2_enable                    :1;	//(31,RW,0x0) //
	};
}PE_O22_ELLIPSE_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800674 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_SC_BNR_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800678 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_x0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_x2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_SC_BNR_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80067C RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y4             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_SC_BNR_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800680 RW 0x0000_0000
	UINT32 reg_lowapl_dc_ptr_y0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y1             :10;	//(19:10,RW,0x0) //
	UINT32 reg_lowapl_dc_ptr_y2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_SC_BNR_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800684 RW 0x0000_0100
	UINT32 reg_f2_h2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_h1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_ELLIPSE_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800688 RW 0x0000_0000
	UINT32 pre_121_blur_en                  :1;	//(0,RW,0x00) //
	UINT32 pre_median_en                    :1;	//(1,RW,0x00) //
	UINT32 resvd                            :30;
	};
}PE_O22_C_PRE_BLUR_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80068C RW 0x0000_0000
	UINT32 reg_f2_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f2_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_ELLIPSE_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800690 RW 0x0000_0000
	UINT32 reg_f2_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f2_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h1_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_ELLIPSE_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800694 RW 0x0000_0000
	UINT32 reg_f3_w2_pos                    :12;	//(11:0,RW,0x0) //
	UINT32 reg_f3_w1_pos                    :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_ELLIPSE_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800698 RW 0x0000_0000
	UINT32 reg_f3_e_mul_b                   :9;	//(8:0,RW,0x0) //
	UINT32 reg_f3_e_mul_a                   :9;	//(17:9,RW,0x0) //
	UINT32 reg_f3_h2_pos                    :12;	//(29:18,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_ELLIPSE_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80069C RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_h_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_h_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_h                :8;	//(31:24,RW,0x0) //
	};
}PE_O22_AC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006A0 RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_acness_gain_v_l              :8;	//(15:8,RW,0x0) //
	UINT32 reg_acness_gain_v_g              :8;	//(23:16,RW,0x0) //
	UINT32 reg_acness_gain_v                :8;	//(31:24,RW,0x0) //
	};
}PE_O22_AC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006A4 RW 0x4030_2010
	UINT32 reg_fil_motion_x_th0             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th1             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th2             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th3             :8;	//(31:24,RW,0x40) //
	};
}PE_O22_DC_BNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006A8 RW 0xFF60_4020
	UINT32 reg_fil_motion_y_th0             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th1             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th2             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th3             :8;	//(31:24,RW,0xFF) //
	};
}PE_O22_DC_BNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006AC RW 0x3020_1001
	UINT32 reg_mmd_sel                      :2;	//(1:0,RW,0x01) //0: mmd_tnr, 1: mmd_mnr, 2: texture, 3: detail
	UINT32 resvd                            :6;
	UINT32 reg_hist_bin_th0                 :8;	//(15:8,RW,0x10) //
	UINT32 reg_hist_bin_th1                 :8;	//(23:16,RW,0x20) //
	UINT32 reg_hist_bin_th2                 :8;	//(31:24,RW,0x30) //
	};
}PE_O22_SQM_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006B0 RW 0x7060_5040
	UINT32 reg_hist_bin_th3                 :8;	//(7:0,RW,0x40) //
	UINT32 reg_hist_bin_th4                 :8;	//(15:8,RW,0x50) //
	UINT32 reg_hist_bin_th5                 :8;	//(23:16,RW,0x60) //
	UINT32 reg_hist_bin_th6                 :8;	//(31:24,RW,0x70) //
	};
}PE_O22_SQM_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006B4 RW 0x0461_E046
	UINT32 reg_trans_mmd_th                 :8;	//(7:0,RW,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_edge_a_th                    :10;	//(19:10,RW,0x78) //
	UINT32 reg_edf_mmd_th                   :8;	//(27:20,RW,0x46) //
	UINT32 resvd1                           :4;
	};
}PE_O22_SQM_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006B8 RW 0x0000_0000
	UINT32 reg_sqm_win_mode_x1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_x0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_sqm_win_mode_mode            :1;	//(30,RW,0x00) //
	UINT32 reg_sqm_win_mode_en              :1;	//(31,RW,0x00) //
	};
}PE_O22_SQM_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006BC RW 0x0000_0000
	UINT32 reg_sqm_win_mode_y1              :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sqm_win_mode_y0              :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_SQM_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006C0 RW 0x0000_0080
	UINT32 reg_tp_binary_th                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}PE_O22_TPD_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006C4 RW 0x0000_0000
	UINT32 reg_win_mode_x1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_x0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_win_mode_mode                :1;	//(30,RW,0x00) //0: inside, 1: outside
	UINT32 reg_win_mode_en                  :1;	//(31,RW,0x00) //
	};
}PE_O22_WINDOW_MODE_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006C8 RW 0x0000_0000
	UINT32 reg_win_mode_y1                  :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_win_mode_y0                  :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_WINDOW_MODE_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006D0 RO 0x0000_0000
	UINT32 acness_v_g                       :8;	//(7:0,RO,0x0) //
	UINT32 acness_h_g                       :8;	//(15:8,RO,0x0) //
	UINT32 acness_v                         :8;	//(23:16,RO,0x0) //
	UINT32 acness_h                         :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006D4 RO 0x0000_0000
	UINT32 bad_up_cnt                       :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :4;
	UINT32 acness_v_l                       :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_l                       :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006D8 RO 0x0000_0000
	UINT32 acness_gain_v_l                  :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h_l                  :8;	//(15:8,RO,0x0) //
	UINT32 acness_gain_v_g                  :8;	//(23:16,RO,0x0) //
	UINT32 acness_gain_h_g                  :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006DC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_DNR_STAT_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006E0 RO 0x0000_0000
	UINT32 acness_gain_v                    :8;	//(7:0,RO,0x0) //
	UINT32 acness_gain_h                    :8;	//(15:8,RO,0x0) //
	UINT32 acness_v_iir                     :8;	//(23:16,RO,0x0) //
	UINT32 acness_h_iir                     :8;	//(31:24,RO,0x0) //
	};
}PE_O22_DNR_STAT_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006E4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_DNR_STAT_8_SC_BNR0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006E8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_DNR_STAT_9_SC_BNR1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006EC RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_DNR_STAT_10_SC_BNR2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006F0 RO 0x0000_0000
	UINT32 e_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_11_SQM_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006F4 RO 0x0000_0000
	UINT32 e_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_12_SQM_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006F8 RO 0x0000_0000
	UINT32 e_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_13_SQM_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8006FC RO 0x0000_0000
	UINT32 e_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 e_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_14_SQM_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800700 RO 0x0000_0000
	UINT32 f_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_15_SQM_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800704 RO 0x0000_0000
	UINT32 f_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_16_SQM_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800708 RO 0x0000_0000
	UINT32 f_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_17_SQM_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80070C RO 0x0000_0000
	UINT32 f_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 f_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_18_SQM_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800710 RO 0x0000_0000
	UINT32 t_hist_1                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_0                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_19_SQM_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800714 RO 0x0000_0000
	UINT32 t_hist_3                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_2                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_20_SQM_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800718 RO 0x0000_0000
	UINT32 t_hist_5                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_4                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_21_SQM_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80071C RO 0x0000_0000
	UINT32 t_hist_7                         :16;	//(15:0,RO,0x0) //
	UINT32 t_hist_6                         :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_22_SQM_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800720 RO 0x0000_0000
	UINT32 res_h_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_23_TPD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800724 RO 0x0000_0000
	UINT32 res_v_cnt_2                      :16;	//(15:0,RO,0x0) //
	UINT32 res_v_cnt_1                      :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_24_TPD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800728 RO 0x0000_0000
	UINT32 res_v_cnt_3                      :16;	//(15:0,RO,0x0) //
	UINT32 res_h_cnt_3                      :16;	//(31:16,RO,0x0) //
	};
}PE_O22_DNR_STAT_25_TPD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800730 RW 0x40302010
	UINT32 reg_fil_motion_x_th3             :8;	//(7:0,RW,0x10) //
	UINT32 reg_fil_motion_x_th2             :8;	//(15:8,RW,0x20) //
	UINT32 reg_fil_motion_x_th1             :8;	//(23:16,RW,0x30) //
	UINT32 reg_fil_motion_x_th0             :8;	//(31:24,RW,0x40) //
	};
}PE_O22_AC_BNR_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800734 RW 0xFF604020
	UINT32 reg_fil_motion_y_th3             :8;	//(7:0,RW,0x20) //
	UINT32 reg_fil_motion_y_th2             :8;	//(15:8,RW,0x40) //
	UINT32 reg_fil_motion_y_th1             :8;	//(23:16,RW,0x60) //
	UINT32 reg_fil_motion_y_th0             :8;	//(31:24,RW,0xFF) //
	};
}PE_O22_AC_BNR_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800738 RW 0x0000_0000
	UINT32 reg_tearing_y_1                  :4;	//(3:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_tearing_y_0                  :4;	//(11:8,RW,0x0) //
	UINT32 resvd1                           :4;
	UINT32 reg_tearing_x_1                  :4;	//(19:16,RW,0x0) //
	UINT32 resvd2                           :4;
	UINT32 reg_tearing_x_0                  :4;	//(27:24,RW,0x0) //
	UINT32 resvd3                           :4;
	};
}PE_O22_VFILTER_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80073C RW 0x0000_0000
	UINT32 reg_motion_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800740 RW 0x0000_0000
	UINT32 reg_motion_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800744 RW 0x0000_0000
	UINT32 reg_global_x_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_x_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_x_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_x_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800748 RW 0x0000_0000
	UINT32 reg_global_y_3                   :8;	//(7:0,RW,0x0) //
	UINT32 reg_global_y_2                   :8;	//(15:8,RW,0x0) //
	UINT32 reg_global_y_1                   :8;	//(23:16,RW,0x0) //
	UINT32 reg_global_y_0                   :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80074C RW 0x0000_0000
	UINT32 reg_blend_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800750 RW 0x0000_0000
	UINT32 reg_blend_y_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_blend_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_blend_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_blend_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800754 RW 0x0000_0000
	UINT32 reg_hmc_x_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_x_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_x_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_x_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800758 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_hmc_y_2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_hmc_y_1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_hmc_y_0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80075C RW 0x0000_0000
	UINT32 reg_local_x_3                    :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_x_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_x_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_x_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800760 RW 0x0000_0000
	UINT32 reg_hmc_y_3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_local_y_2                    :8;	//(15:8,RW,0x0) //
	UINT32 reg_local_y_1                    :8;	//(23:16,RW,0x0) //
	UINT32 reg_local_y_0                    :8;	//(31:24,RW,0x0) //
	};
}PE_O22_VFILTER_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800764 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_master_bypass_en             :1;	//(1,RW,0x0) //
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //not used in O22
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ??ÎßûÏùå)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //not used in O22
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800768 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_REG_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80076C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_REG_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800770 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_REG_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800774 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800778 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80077C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800780 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800784 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800788 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_REG_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80078C RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O22_REG_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800790 RW 0x0000_0000
	UINT32 reg_gain_x3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DC_BNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800794 RW 0x0000_0000
	UINT32 reg_gain_x7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_x6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_x5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_x4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DC_BNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800798 RW 0x0000_0000
	UINT32 reg_gain_y3                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y2                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y1                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y0                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DC_BNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80079C RW 0x0000_0000
	UINT32 reg_gain_y7                      :8;	//(7:0,RW,0x0) //
	UINT32 reg_gain_y6                      :8;	//(15:8,RW,0x0) //
	UINT32 reg_gain_y5                      :8;	//(23:16,RW,0x0) //
	UINT32 reg_gain_y4                      :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DC_BNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007A0 RW 0x0000_0000
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
}PE_O22_REG_CTI_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007A4 RW 0x0000_0000
	UINT32 reg_lti_coring_th0               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lti_coring_th1               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lti_coring_sm                :3;	//(18:16,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_lti_tap2                     :2;	//(21:20,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_ycm_diff_th                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_CTI_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007A8 RW 0x0000_0000
	UINT32 reg_small_mmd_flat_th            :8;	//(7:0,NA,0x0) //
	UINT32 reg_large_mmd_flat_th            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :12;
	UINT32 reg_mmd_chroma_gain_en           :1;	//(28,NA,0x0) //
	UINT32 reg_mmd_dist_kernal_width        :2;	//(30:29,NA,0x0) //
	UINT32 reg_mmd_dist_gain_en             :1;	//(31,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007AC RW 0x0000_0000
	UINT32 reg_dist_gain_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007B0 RW 0x0000_0000
	UINT32 reg_dist_gain_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_dist_gain_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_dist_gain_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_dist_gain_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007B4 RW 0x0000_0000
	UINT32 reg_chroma_gain_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007B8 RW 0x0000_0000
	UINT32 reg_chroma_gain_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_chroma_gain_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_chroma_gain_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_chroma_gain_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007BC RW 0x0000_0000
	UINT32 reg_i_sel_mmd_x3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_x2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_x1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_x0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007C0 RW 0x0000_0000
	UINT32 reg_i_sel_mmd_y3                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_i_sel_mmd_y2                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_i_sel_mmd_y1                 :8;	//(23:16,NA,0x0) //
	UINT32 reg_i_sel_mmd_y0                 :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_MNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007C4 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007C8 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007CC RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007D0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007DC RW 0x0000_0000
	UINT32 resvd0                           :14;
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 resvd1                           :8;
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //Not used in O22
	UINT32 resvd2                           :1;
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :5;	//(30:26,RW,0x0) //0: final_gain	1: variance_gain	2: variance - dc frame input	3: variance - original var	4: variance - blur dc map	5: variance - blend dc map	6: variance - final dc map	7: rmmd - l0 mmd	8: rmmd - l0 luma	9: rmmd - refine	A : rmmd - final gain	B: blur map - mmd input luma	C: blur map - mmd gain	D: blur map output	E: PAI	F: RRD	10: diff gain	11: luma gain	12: sel_diff	13: motion shift	14: motion gain	15: skin gain	16: face gain	17: face-skin gain
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007E0 RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x0) //0: new_2x2, 1: new_3x3
	UINT32 resvd1                           :1;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x0) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x0) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20, O22
	UINT32 resvd2                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007E4 RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007E8 RW 0x0000_0000
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007EC RW 0x0000_0000
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007F0 RW 0x0000_0000
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007F4 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007F8 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8007FC RW 0x0000_0000
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800800 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800804 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800808 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80080C RW 0x0000_0000
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
}PE_O22_REG_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800810 RW 0x0000_0000
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
}PE_O22_REG_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800814 RW 0x0000_0000
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x0) //not used in m16p3, O20, O22
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x0) //not used in m16p3, O20, O22
	UINT32 resvd                            :4;
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800818 RW 0x0000_0000
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
}PE_O22_REG_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80081C RW 0x0000_0000
	UINT32 reg_120x68_last_block_size_v     :6;	//(5:0,RW,0x0) //
	UINT32 reg_120x68_last_block_size_h     :6;	//(11:6,RW,0x0) //
	UINT32 reg_120x68_block_size_v          :6;	//(17:12,RW,0x0) //
	UINT32 reg_120x68_block_size_h          :6;	//(23:18,RW,0x0) //
	UINT32 reg_120x68_block_no_v            :7;	//(30:24,RW,0x0) //
	UINT32 resvd                            :1;
	};
}PE_O22_REG_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800820 RW 0x0000_0000
	UINT32 resvd                            :20;
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x0) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x0) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800824 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800828 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80082C RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800830 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800834 RW 0x0000_0000
	UINT32 resvd                            :24;
	UINT32 reg_120x68_block_no_h            :7;	//(30:24,RW,0x0) //
	UINT32 reg_120x68_block_info_force_en   :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800838 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80083C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800840 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800844 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800848 RW 0x0000_0000
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80084C RW 0x0000_0000
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800850 RW 0x0000_0000
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800854 RW 0x0000_0000
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800858 RW 0x0000_0000
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80085C RW 0x0000_0000
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800860 RW 0x0000_0000
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800864 RW 0x0000_0000
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800868 RW 0x0000_0000
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80086C RW 0x0000_0000
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800870 RW 0x0000_0000
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800874 RW 0x0000_0000
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800878 RW 0x0000_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0x0) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80087C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800880 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800884 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800888 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80088C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800890 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800894 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800898 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DC_BNR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80089C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DC_BNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DC_BNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DC_BNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008A8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008AC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008B0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008B4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008BC RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_x2            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x1            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x0            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008C0 RW 0x0000_0000
	UINT32 reg_var_lowapl_lut_y1            :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y0            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_x3            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008C4 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x0          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y3            :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_lut_y2            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008C8 RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_x3          :10;	//(9:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x2          :10;	//(19:10,RW,0x0) //
	UINT32 reg_var_lowapl_blend_x1          :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008CC RW 0x0000_0000
	UINT32 reg_var_lowapl_blend_y3          :8;	//(7:0,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y2          :8;	//(15:8,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y1          :8;	//(23:16,RW,0x0) //
	UINT32 reg_var_lowapl_blend_y0          :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008D0 RW 0x0000_0000
	UINT32 reg_lowapl_master_blend          :8;	//(7:0,RW,0x0) //
	UINT32 reg_2x2_var_msb_sel              :1;	//(8,RW,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O22_REG_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008DC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008E0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008E4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008E8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008EC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008F0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008F4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O22_REG_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008F8 RW 0x0000_0000
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x1) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x1) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8008FC RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800900 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800904 RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd                            :12;
	};
}PE_O22_REG_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800908 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd                            :12;
	};
}PE_O22_REG_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80090C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800910 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800914 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800918 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80091C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800920 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //2nd rd?êÎèÑ ?ôÏùº?òÍ≤å ?¨Ïö©
	UINT32 resvd1                           :10;
	};
}PE_O22_REG_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800924 RW 0x0000_0000
	UINT32 reg_face_demo_x1                 :13;	//(12:0,NA,0x400) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_x0                 :13;	//(28:16,NA,0x1E0) //x0 < pos_x < x1 ?ºÎïå ?ôÏûë(2 Î∞∞ÏàòÎ°??§Ï†ï ?ÖÎ†•)
	UINT32 resvd1                           :2;
	UINT32 reg_face_demo_en                 :1;	//(31,NA,0x0) //face gain demo mode ?ôÏûë
	};
}PE_O22_REG_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800928 RW 0x0000_0000
	UINT32 reg_face_demo_y1                 :13;	//(12:0,NA,0x64) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd0                           :3;
	UINT32 reg_face_demo_y0                 :13;	//(28:16,NA,0xA) //y0 < pos_y < y1 ?ºÎïå ?ôÏûë
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80092C RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_x3              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800930 RW 0x0000_0000
	UINT32 reg_ref_mmd_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_ref_mmd_gain_y3              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800934 RW 0x0000_0000
	UINT32 reg_ref_filter_x1                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_x2                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x3                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_ref_mmd_sel                  :1;	//(31,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800938 RW 0x0000_0000
	UINT32 reg_ref_filter_y2                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y3                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_filter_x0                :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80093C RW 0x0000_0000
	UINT32 reg_ref_filter_y0                :10;	//(9:0,NA,0x0) //
	UINT32 reg_ref_filter_y1                :10;	//(19:10,NA,0x0) //
	UINT32 reg_ref_mmd_left_shift           :3;	//(22:20,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_mmd_right_shift              :2;	//(29:28,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O22_REG_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800940 RW 0x0000_0000
	UINT32 reg_margin_bit                   :3;	//(2:0,NA,0x0) //
	UINT32 reg_rand_shift                   :3;	//(5:3,NA,0x0) //
	UINT32 resvd                            :26;
	};
}PE_O22_REG_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800944 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_x3            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800948 RW 0x0000_0000
	UINT32 reg_msp_outer_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_outer_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_outer_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_outer_dist_y3            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80094C RW 0x0000_0000
	UINT32 reg_msp_inner_dist_x0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_x1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_x2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_x3            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800950 RW 0x0000_0000
	UINT32 reg_msp_inner_dist_y0            :8;	//(7:0,NA,0x0) //
	UINT32 reg_msp_inner_dist_y1            :8;	//(15:8,NA,0x0) //
	UINT32 reg_msp_inner_dist_y2            :8;	//(23:16,NA,0x0) //
	UINT32 reg_msp_inner_dist_y3            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800954 RW 0x0000_0000
	UINT32 reg_msp_rd_init_yy               :32;	//(31:0,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800958 RW 0x0000_0000
	UINT32 reg_msp_rd_init_cb               :32;	//(31:0,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80095C RW 0x0000_0000
	UINT32 reg_msp_rd_init_cr               :32;	//(31:0,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800960 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_x0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_x3                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800964 RW 0x0000_0000
	UINT32 reg_l6_itp_mmd_y0                :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y1                :8;	//(15:8,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y2                :8;	//(23:16,NA,0x0) //
	UINT32 reg_l6_itp_mmd_y3                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800968 RW 0x0000_0000
	UINT32 reg_mnr_var_gain_low             :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_pooling_th               :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_pooling_max              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_left_shift           :4;	//(27:24,NA,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_mmd_edge_chroma_gain_en      :1;	//(30,NA,0x0) //
	UINT32 reg_en_mmd_new                   :1;	//(31,NA,0x0) //O22 new
	};
}PE_O22_MNR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80096C RW 0x0000_0000
	UINT32 reg_mnr_var_gain_x0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_var_gain_x1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_var_gain_x2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_gain_x3              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_MNR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800970 RW 0x0000_0000
	UINT32 reg_mnr_var_gain_y0              :8;	//(7:0,NA,0x0) //
	UINT32 reg_mnr_var_gain_y1              :8;	//(15:8,NA,0x0) //
	UINT32 reg_mnr_var_gain_y2              :8;	//(23:16,NA,0x0) //
	UINT32 reg_mnr_var_gain_y3              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_MNR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800974 RW 0x0000_0000
	UINT32 reg_edge_chroma_gain_x0          :8;	//(7:0,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x1          :8;	//(15:8,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x2          :8;	//(23:16,NA,0x0) //
	UINT32 reg_edge_chroma_gain_x3          :8;	//(31:24,NA,0x0) //
	};
}PE_O22_MNR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800978 RW 0x0000_0000
	UINT32 reg_edge_chroma_gain_y0          :8;	//(7:0,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y1          :8;	//(15:8,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y2          :8;	//(23:16,NA,0x0) //
	UINT32 reg_edge_chroma_gain_y3          :8;	//(31:24,NA,0x0) //
	};
}PE_O22_MNR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80097C RW 0x0000_0000
	UINT32 reg_l6_blur_luma_ratio           :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_luma_mode            :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_luma_th              :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :11;
	UINT32 reg_amean_filter_en              :1;	//(31,NA,0x0) //a-mean filter en
	};
}PE_O22_REG_DECON_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800980 RW 0x0000_0000
	UINT32 reg_l6_blur_chroma_ratio         :8;	//(7:0,NA,0x0) //
	UINT32 reg_l6_blur_chroma_mode          :2;	//(9:8,NA,0x0) //
	UINT32 reg_l6_blur_chroma_th            :10;	//(19:10,NA,0x0) //
	UINT32 resvd                            :12;
	};
}PE_O22_REG_DECON_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800984 RW 0x0000_0000
	UINT32 reg_rd_blur_ratio_c              :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_ratio_y              :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :14;
	UINT32 reg_oai_repeat                   :1;	//(30,NA,0x0) //
	UINT32 reg_rd_blur_en                   :1;	//(31,NA,0x0) //O22 New : RRD enable
	};
}PE_O22_REG_DECON_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800988 RW 0x0000_0000
	UINT32 reg_rd_blur_x0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_x1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_x2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_x3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80098C RW 0x0000_0000
	UINT32 reg_rd_blur_y0                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_rd_blur_y1                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_rd_blur_y2                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_rd_blur_y3                   :8;	//(31:24,NA,0x0) //
	};
}PE_O22_REG_DECON_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800990 RW 0x1357_9753
	UINT32 reg_decon_rd_init_yy             :32;	//(31:0,NA,0x13579753) //Decon 1st RRD seed
	};
}PE_O22_REG_DECON_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800994 RW 0x2468_0864
	UINT32 reg_decon_rd_init_cb             :32;	//(31:0,NA,0x24680864) //Decon 1st RRD seed
	};
}PE_O22_REG_DECON_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC800998 RW 0x1470_3692
	UINT32 reg_decon_rd_init_cr             :32;	//(31:0,NA,0x14703692) //Decon 1st RRD seed
	};
}PE_O22_REG_DECON_CTRL_119_T;

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
}PE_O22_CTRL_CTRL_M0_Y_LEVEL_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC801100 copy from MNR_CTRL_0
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
}PE_O22_ND0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC801104 copy from MNR_CTRL_3
	UINT32 reg_blur_sel 					:1; //0 //
	UINT32 reg_pattern_en					:1; //1 //
	UINT32 resvd							:6;
	UINT32 reg_pattern_th					:8; //15:8	//
	UINT32 reg_equal_th 					:8; //23:16 //
	UINT32 reg_mmd_scale					:8; //31:24 //
	};
}PE_O22_ND0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC801108 copy from MNR_CTRL_11
	UINT32 reg_i_sel_mmd_x3 				:8; //7:0	//
	UINT32 reg_i_sel_mmd_x2 				:8; //15:8	//
	UINT32 reg_i_sel_mmd_x1 				:8; //23:16 //
	UINT32 reg_i_sel_mmd_x0 				:8; //31:24 //
	};
}PE_O22_ND0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC80110C copy from MNR_CTRL_12
	UINT32 reg_i_sel_mmd_y3 				:8; //7:0	//
	UINT32 reg_i_sel_mmd_y2 				:8; //15:8	//
	UINT32 reg_i_sel_mmd_y1 				:8; //23:16 //
	UINT32 reg_i_sel_mmd_y0 				:8; //31:24 //
	};
}PE_O22_ND0_VERI_SYS_VERI_3_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCCC01100 RW 0x0000_0000
	UINT32 reg_sys_veri_0                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_ND1_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC01104 RW 0x0000_0000
	UINT32 reg_sys_veri_1                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_ND1_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC01108 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_ND1_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC0110C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_ND1_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O22_ND0_VERI_SYS_VERI_0_T                                mnr_ctrl_0;	//0xCC801100
	PE_O22_ND0_VERI_SYS_VERI_1_T                                mnr_ctrl_3;	//0xCC801104
	PE_O22_ND0_VERI_SYS_VERI_2_T                                mnr_ctrl_11;	//0xCC801108
	PE_O22_ND0_VERI_SYS_VERI_3_T                                mnr_ctrl_12;	//0xCC80110C
}PE_ND0_VERI_REG_O22_T;

typedef struct {
	PE_O22_ND1_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xCCC01100
	PE_O22_ND1_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xCCC01104
	PE_O22_ND1_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xCCC01108
	PE_O22_ND1_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xCCC0110C
}PE_ND1_VERI_REG_O22_T;

typedef struct {
	PE_O22_PE0_ND_LOAD_T                                         pe0_load;	//0xCC800100
	PE_O22_PE0_ND_INTR_T                                         pe0_intr;	//0xCC800104
	PE_O22_PE0_ND_STATUS0_T                                   pe0_status0;	//0xCC800108
	PE_O22_PE0_ND_STATUS1_T                                   pe0_status1;	//0xCC80010C
	PE_O22_PE0_ND_OPMODE_T                                     pe0_opmode;	//0xCC800110
	PE_O22_PE0_SRC_SIZE_T                                 pe0_src_size;	//0xCC800114
	PE_O22_PE0_FIELD_T                                       pe0_field;	//0xCC800118
	PE_O22_PE0_DEBUG_LEND_CTRL_T                   pe0_debug_lend_ctrl;	//0xCC80011C
	PE_O22_PE0_ND_IN_OFFSET_T                               pe0_in_offset;	//0xCC800120
	PE_O22_PE0_ND_IN_SIZE_T                                   pe0_in_size;	//0xCC800124
	PE_O22_FBC_CTRL0_T                                       fbc_ctrl0;	//0xCC800128
	PE_O22_FBC_CTRL1_T                                       fbc_ctrl1;	//0xCC80012C
	PE_O22_PE0_MEM_REQ_T                                   pe0_mem_req;	//0xCC800130
	PE_O22_PE0_DEBUG_LREQ_DLY_T                     pe0_debug_lreq_dly;	//0xCC800134
	PE_O22_TNRW_IN_OFFSET_T                             tnrw_in_offset;	//0xCC800138
	PE_O22_TNRW_OUT_SIZE_T                               tnrw_out_size;	//0xCC80013C
	PE_O22_TNR_CTRL_00_T                                   tnr_ctrl_00;	//0xCC800140
	PE_O22_TNR_CTRL_01_T                                   tnr_ctrl_01;	//0xCC800144
	PE_O22_TNR_CTRL_02_T                                   tnr_ctrl_02;	//0xCC800148
	PE_O22_TNR_CTRL_03_T                                   tnr_ctrl_03;	//0xCC80014C
	PE_O22_TNR_CTRL_04_T                                   tnr_ctrl_04;	//0xCC800150
	PE_O22_TNR_CTRL_05_T                                   tnr_ctrl_05;	//0xCC800154
	PE_O22_TNR_CTRL_06_T                                   tnr_ctrl_06;	//0xCC800158
	PE_O22_TNR_CTRL_07_T                                   tnr_ctrl_07;	//0xCC80015C
	PE_O22_TNR_CTRL_08_T                                   tnr_ctrl_08;	//0xCC800160
	PE_O22_TNR_CTRL_09_T                                   tnr_ctrl_09;	//0xCC800164
	PE_O22_TNR_CTRL_10_T                                   tnr_ctrl_10;	//0xCC800168
	PE_O22_TNR_CTRL_11_T                                   tnr_ctrl_11;	//0xCC80016C
	PE_O22_TNR_CTRL_12_T                                   tnr_ctrl_12;	//0xCC800170
	PE_O22_TNR_CTRL_13_T                                   tnr_ctrl_13;	//0xCC800174
	PE_O22_TNR_CTRL_14_T                                   tnr_ctrl_14;	//0xCC800178
	PE_O22_TNR_CTRL_15_T                                   tnr_ctrl_15;	//0xCC80017C
	PE_O22_TNR_CTRL_16_T                                   tnr_ctrl_16;	//0xCC800180
	PE_O22_TNR_CTRL_17_T                                   tnr_ctrl_17;	//0xCC800184
	PE_O22_TNR_CTRL_18_T                                   tnr_ctrl_18;	//0xCC800188
	PE_O22_TNR_CTRL_19_T                                   tnr_ctrl_19;	//0xCC80018C
	PE_O22_TNR_CTRL_20_T                                   tnr_ctrl_20;	//0xCC800190
	PE_O22_TNR_CTRL_21_T                                   tnr_ctrl_21;	//0xCC800194
	PE_O22_TNR_CTRL_22_T                                   tnr_ctrl_22;	//0xCC800198
	PE_O22_TNR_CTRL_23_T                                   tnr_ctrl_23;	//0xCC80019C
	PE_O22_TNR_CTRL_24_T                                   tnr_ctrl_24;	//0xCC8001A0
	PE_O22_TNR_CTRL_25_T                                   tnr_ctrl_25;	//0xCC8001A4
	PE_O22_TNR_CTRL_26_T                                   tnr_ctrl_26;	//0xCC8001A8
	PE_O22_TNR_CTRL_27_T                                   tnr_ctrl_27;	//0xCC8001AC
	PE_O22_TNR_CTRL_28_T                                   tnr_ctrl_28;	//0xCC8001B0
	PE_O22_TNR_CTRL_29_T                                   tnr_ctrl_29;	//0xCC8001B4
	PE_O22_TNR_CTRL_30_T                                   tnr_ctrl_30;	//0xCC8001B8
	PE_O22_TNR_CTRL_31_T                                   tnr_ctrl_31;	//0xCC8001BC
	PE_O22_TNR_STATUS_00_T                               tnr_status_00;	//0xCC8001C0
	PE_O22_TNR_STATUS_01_T                               tnr_status_01;	//0xCC8001C4
	PE_O22_TNR_STATUS_02_T                               tnr_status_02;	//0xCC8001C8
	PE_O22_TNR_STATUS_03_T                               tnr_status_03;	//0xCC8001CC
	PE_O22_TNR_MAIN_LUT_00_T                           tnr_main_lut_00;	//0xCC8001D0
	PE_O22_TNR_MAIN_LUT_01_T                           tnr_main_lut_01;	//0xCC8001D4
	UINT32                                                    reserved0;	//0xCC8001D8
	PE_O22_TNR_STATUS_04_T                               tnr_status_04;	//0xCC8001DC
	PE_O22_TNR_CTRL_32_T                                   tnr_ctrl_32;	//0xCC8001E0
	PE_O22_TNR_CTRL_33_T                                   tnr_ctrl_33;	//0xCC8001E4
	PE_O22_TNR_CTRL_34_T                                   tnr_ctrl_34;	//0xCC8001E8
	PE_O22_TNR_CTRL_35_T                                   tnr_ctrl_35;	//0xCC8001EC
	PE_O22_TNR_CTRL_36_T                                   tnr_ctrl_36;	//0xCC8001F0
	PE_O22_TNR_CTRL_37_T                                   tnr_ctrl_37;	//0xCC8001F4
	PE_O22_TNR_CTRL_38_T                                   tnr_ctrl_38;	//0xCC8001F8
	PE_O22_TNR_CTRL_39_T                                   tnr_ctrl_39;	//0xCC8001FC
	PE_O22_IPC_CTRL_00_T                                   ipc_ctrl_00;	//0xCC800200
	PE_O22_IPC_CTRL_01_T                                   ipc_ctrl_01;	//0xCC800204
	PE_O22_IPC_CTRL_02_T                                   ipc_ctrl_02;	//0xCC800208
	PE_O22_IPC_CTRL_03_T                                   ipc_ctrl_03;	//0xCC80020C
	PE_O22_IPC_CTRL_04_T                                   ipc_ctrl_04;	//0xCC800210
	PE_O22_IPC_CTRL_05_T                                   ipc_ctrl_05;	//0xCC800214
	PE_O22_IPC_CTRL_06_T                                   ipc_ctrl_06;	//0xCC800218
	PE_O22_IPC_CTRL_07_T                                   ipc_ctrl_07;	//0xCC80021C
	PE_O22_IPC_CTRL_08_T                                   ipc_ctrl_08;	//0xCC800220
	PE_O22_IPC_CTRL_09_T                                   ipc_ctrl_09;	//0xCC800224
	PE_O22_IPC_CTRL_10_T                                   ipc_ctrl_10;	//0xCC800228
	PE_O22_IPC_CTRL_11_T                                   ipc_ctrl_11;	//0xCC80022C
	PE_O22_IPC_CTRL_12_T                                   ipc_ctrl_12;	//0xCC800230
	PE_O22_IPC_CTRL_13_T                                   ipc_ctrl_13;	//0xCC800234
	PE_O22_IPC_CTRL_14_T                                   ipc_ctrl_14;	//0xCC800238
	PE_O22_IPC_CTRL_15_T                                   ipc_ctrl_15;	//0xCC80023C
	PE_O22_IPC_CTRL_16_T                                   ipc_ctrl_16;	//0xCC800240
	PE_O22_IPC_CTRL_17_T                                   ipc_ctrl_17;	//0xCC800244
	PE_O22_IPC_CTRL_18_T                                   ipc_ctrl_18;	//0xCC800248
	PE_O22_IPC_CTRL_19_T                                   ipc_ctrl_19;	//0xCC80024C
	PE_O22_IPC_STATUS_00_T                               ipc_status_00;	//0xCC800250
	PE_O22_IPC_STATUS_01_T                               ipc_status_01;	//0xCC800254
	PE_O22_IPC_STATUS_02_T                               ipc_status_02;	//0xCC800258
	PE_O22_IPC_STATUS_03_T                               ipc_status_03;	//0xCC80025C
	PE_O22_CLC_CTRL_00_T                                   clc_ctrl_00;	//0xCC800260
	PE_O22_CLC_CTRL_01_T                                   clc_ctrl_01;	//0xCC800264
	PE_O22_CLC_CTRL_02_T                                   clc_ctrl_02;	//0xCC800268
	PE_O22_CLC_CTRL_03_T                                   clc_ctrl_03;	//0xCC80026C
	PE_O22_CLC_CTRL_04_T                                   clc_ctrl_04;	//0xCC800270
	PE_O22_CLC_CTRL_05_T                                   clc_ctrl_05;	//0xCC800274
	PE_O22_CLC_CTRL_06_T                                   clc_ctrl_06;	//0xCC800278
	PE_O22_CLC_STAT_00_T                                   clc_stat_00;	//0xCC80027C
	PE_O22_IPC_CTRL_34_T                                   ipc_ctrl_34;	//0xCC800280
	PE_O22_IPC_CTRL_35_T                                   ipc_ctrl_35;	//0xCC800284
	PE_O22_IPC_CTRL_36_T                                   ipc_ctrl_36;	//0xCC800288
	PE_O22_IPC_CTRL_37_T                                   ipc_ctrl_37;	//0xCC80028C
	PE_O22_IPC_CTRL_38_T                                   ipc_ctrl_38;	//0xCC800290
	PE_O22_IPC_CTRL_39_T                                   ipc_ctrl_39;	//0xCC800294
	PE_O22_IPC_CTRL_40_T                                   ipc_ctrl_40;	//0xCC800298
	PE_O22_IPC_CTRL_41_T                                   ipc_ctrl_41;	//0xCC80029C
	PE_O22_IPC_CTRL_42_T                                   ipc_ctrl_42;	//0xCC8002A0
	PE_O22_IPC_CTRL_43_T                                   ipc_ctrl_43;	//0xCC8002A4
	PE_O22_IPC_CTRL_44_T                                   ipc_ctrl_44;	//0xCC8002A8
	PE_O22_IPC_CTRL_45_T                                   ipc_ctrl_45;	//0xCC8002AC
	PE_O22_IPC_CTRL_46_T                                   ipc_ctrl_46;	//0xCC8002B0
	PE_O22_IPC_CTRL_47_T                                   ipc_ctrl_47;	//0xCC8002B4
	PE_O22_IPC_CTRL_48_T                                   ipc_ctrl_48;	//0xCC8002B8
	PE_O22_IPC_CTRL_49_T                                   ipc_ctrl_49;	//0xCC8002BC
	PE_O22_IPC_CTRL_50_T                                   ipc_ctrl_50;	//0xCC8002C0
	PE_O22_IPC_CTRL_51_T                                   ipc_ctrl_51;	//0xCC8002C4
	PE_O22_IPC_CTRL_52_T                                   ipc_ctrl_52;	//0xCC8002C8
	PE_O22_IPC_CTRL_53_T                                   ipc_ctrl_53;	//0xCC8002CC
	PE_O22_IPC_CTRL_54_T                                   ipc_ctrl_54;	//0xCC8002D0
	PE_O22_IPC_CTRL_55_T                                   ipc_ctrl_55;	//0xCC8002D4
	UINT32                                                    reserved1;	//0xCC8002D8
	UINT32                                                    reserved2;	//0xCC8002DC
	PE_O22_MMD_CTRL_T                                         mmd_ctrl;	//0xCC8002E0
	UINT32                                                    reserved3;	//0xCC8002E4
	UINT32                                                    reserved4;	//0xCC8002E8
	UINT32                                                    reserved5;	//0xCC8002EC
	PE_O22_IPC_CTRL_20_T                                   ipc_ctrl_20;	//0xCC8002F0
	PE_O22_IPC_CTRL_21_T                                   ipc_ctrl_21;	//0xCC8002F4
	PE_O22_IPC_CTRL_22_T                                   ipc_ctrl_22;	//0xCC8002F8
	PE_O22_IPC_CTRL_23_T                                   ipc_ctrl_23;	//0xCC8002FC
	PE_O22_IPC_CTRL_24_T                                   ipc_ctrl_24;	//0xCC800300
	PE_O22_IPC_CTRL_25_T                                   ipc_ctrl_25;	//0xCC800304
	PE_O22_IPC_CTRL_26_T                                   ipc_ctrl_26;	//0xCC800308
	PE_O22_IPC_CTRL_27_T                                   ipc_ctrl_27;	//0xCC80030C
	PE_O22_IPC_CTRL_28_T                                   ipc_ctrl_28;	//0xCC800310
	PE_O22_IPC_CTRL_29_T                                   ipc_ctrl_29;	//0xCC800314
	PE_O22_IPC_CTRL_30_T                                   ipc_ctrl_30;	//0xCC800318
	PE_O22_IPC_CTRL_31_T                                   ipc_ctrl_31;	//0xCC80031C
	PE_O22_IPC_CTRL_32_T                                   ipc_ctrl_32;	//0xCC800320
	PE_O22_IPC_CTRL_33_T                                   ipc_ctrl_33;	//0xCC800324
	PE_O22_IPC_STATUS_04_T                               ipc_status_04;	//0xCC800328
	PE_O22_IPC_STATUS_05_T                               ipc_status_05;	//0xCC80032C
	PE_O22_IPC_STATUS_06_T                               ipc_status_06;	//0xCC800330
	PE_O22_IPC_STATUS_07_T                               ipc_status_07;	//0xCC800334
	PE_O22_IPC_STATUS_08_T                               ipc_status_08;	//0xCC800338
	PE_O22_IPC_STATUS_09_T                               ipc_status_09;	//0xCC80033C
	PE_O22_TPD_CTRL_00_T                                   tpd_ctrl_00;	//0xCC800340
	PE_O22_TPD_CTRL_01_T                                   tpd_ctrl_01;	//0xCC800344
	PE_O22_TPD_CTRL_02_T                                   tpd_ctrl_02;	//0xCC800348
	PE_O22_TPD_CTRL_03_T                                   tpd_ctrl_03;	//0xCC80034C
	PE_O22_TPD_CTRL_04_T                                   tpd_ctrl_04;	//0xCC800350
	PE_O22_TPD_CTRL_05_T                                   tpd_ctrl_05;	//0xCC800354
	PE_O22_TPD_CTRL_06_T                                   tpd_ctrl_06;	//0xCC800358
	PE_O22_TPD_CTRL_07_T                                   tpd_ctrl_07;	//0xCC80035C
	PE_O22_TPD_CTRL_08_T                                   tpd_ctrl_08;	//0xCC800360
	PE_O22_TPD_CTRL_09_T                                   tpd_ctrl_09;	//0xCC800364
	PE_O22_TPD_STAT_00_T                                   tpd_stat_00;	//0xCC800368
	PE_O22_CLC_CTRL_07_T                                   clc_ctrl_07;	//0xCC80036C
	PE_O22_BBD_CTRL_00_T                                   bbd_ctrl_00;	//0xCC800370
	PE_O22_BBD_CTRL_01_T                                   bbd_ctrl_01;	//0xCC800374
	PE_O22_BBD_CTRL_02_T                                   bbd_ctrl_02;	//0xCC800378
	PE_O22_BBD_STAT_00_T                                   bbd_stat_00;	//0xCC80037C
	PE_O22_BBD_STAT_01_T                                   bbd_stat_01;	//0xCC800380
	PE_O22_APL_STAT_00_T                                   apl_stat_00;	//0xCC800384
	PE_O22_TPD_CTRL_0A_T                                   tpd_ctrl_0a;	//0xCC800388
	PE_O22_TPD_CTRL_0B_T                                   tpd_ctrl_0b;	//0xCC80038C
	PE_O22_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0xCC800390
	PE_O22_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0xCC800394
	PE_O22_LVCRTL_CTRL_00_T                             lvcrtl_ctrl_00;	//0xCC800398
	PE_O22_TPD_STAT_01_T                                   tpd_stat_01;	//0xCC80039C
	PE_O22_TNR_STATUS_05_T                               tnr_status_05;	//0xCC8003A0
	PE_O22_TNR_STATUS_06_T                               tnr_status_06;	//0xCC8003A4
	PE_O22_TNR_STATUS_07_T                               tnr_status_07;	//0xCC8003A8
	PE_O22_TNR_STATUS_08_T                               tnr_status_08;	//0xCC8003AC
	UINT32                                                    reserved6;	//0xCC8003B0
	UINT32                                                    reserved7;	//0xCC8003B4
	UINT32                                                    reserved8;	//0xCC8003B8
	UINT32                                                    reserved9;	//0xCC8003BC
	PE_O22_TNR_RESET_T                                       tnr_reset;	//0xCC8003C0
	UINT32                                                   reserved10;	//0xCC8003C4
	UINT32                                                   reserved11;	//0xCC8003C8
	UINT32                                                   reserved12;	//0xCC8003CC
	PE_O22_TNR_CTRL_40_T                                   tnr_ctrl_40;	//0xCC8003D0
	PE_O22_TNR_CTRL_41_T                                   tnr_ctrl_41;	//0xCC8003D4
	PE_O22_TNR_CTRL_42_T                                   tnr_ctrl_42;	//0xCC8003D8
	PE_O22_TNR_CTRL_43_T                                   tnr_ctrl_43;	//0xCC8003DC
	PE_O22_TNR_CTRL_44_T                                   tnr_ctrl_44;	//0xCC8003E0
	PE_O22_TNR_CTRL_45_T                                   tnr_ctrl_45;	//0xCC8003E4
	PE_O22_TNR_CTRL_46_T                                   tnr_ctrl_46;	//0xCC8003E8
	PE_O22_TNR_CTRL_47_T                                   tnr_ctrl_47;	//0xCC8003EC
	PE_O22_TNR_CTRL_48_T                                   tnr_ctrl_48;	//0xCC8003F0
	PE_O22_PE1_FSW_CTRL_00_T                          pe1_fsw_ctrl_00;	//0xCC8003F4
	PE_O22_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_01;	//0xCC8003F8
	PE_O22_PE1_FSW_CTRL_02_T                          pe1_fsw_ctrl_02;	//0xCC8003FC
	PE_O22_TNR_NE_STAT_00_T                             tnr_ne_stat_00;	//0xCC800400
	PE_O22_TNR_NE_STAT_01_T                             tnr_ne_stat_01;	//0xCC800404
	PE_O22_TNR_NE_STAT_02_T                             tnr_ne_stat_02;	//0xCC800408
	PE_O22_TNR_NE_STAT_03_T                             tnr_ne_stat_03;	//0xCC80040C
	PE_O22_TNR_NE_STAT_04_T                             tnr_ne_stat_04;	//0xCC800410
	PE_O22_TNR_NE_STAT_05_T                             tnr_ne_stat_05;	//0xCC800414
	PE_O22_TNR_NE_STAT_06_T                             tnr_ne_stat_06;	//0xCC800418
	PE_O22_TNR_NE_STAT_07_T                             tnr_ne_stat_07;	//0xCC80041C
	PE_O22_TNR_NE_STAT_08_T                             tnr_ne_stat_08;	//0xCC800420
	UINT32                                                   reserved16;	//0xCC800424
	UINT32                                                   reserved17;	//0xCC800428
	UINT32                                                   reserved18;	//0xCC80042C
	UINT32                                                   reserved19;	//0xCC800430
	UINT32                                                   reserved20;	//0xCC800434
	UINT32                                                   reserved21;	//0xCC800438
	UINT32                                                   reserved22;	//0xCC80043C
	PE_O22_HIST2_CTRL_00_T                               hist2_ctrl_00;	//0xCC800440
	PE_O22_HIST2_CTRL_01_T                               hist2_ctrl_01;	//0xCC800444
	PE_O22_HIST2_CTRL_02_T                               hist2_ctrl_02;	//0xCC800448
	PE_O22_HIST2_CTRL_03_T                               hist2_ctrl_03;	//0xCC80044C
	PE_O22_HIST2_CTRL_04_T                               hist2_ctrl_04;	//0xCC800450
	PE_O22_HIST2_CTRL_05_T                               hist2_ctrl_05;	//0xCC800454
	PE_O22_HIST2_CTRL_06_T                               hist2_ctrl_06;	//0xCC800458
	PE_O22_HIST2_CTRL_07_T                               hist2_ctrl_07;	//0xCC80045C
	PE_O22_HIST2_CTRL_08_T                               hist2_ctrl_08;	//0xCC800460
	PE_O22_HIST2_CTRL_09_T                               hist2_ctrl_09;	//0xCC800464
	PE_O22_HIST2_CTRL_0A_T                               hist2_ctrl_0a;	//0xCC800468
	PE_O22_HIST2_CTRL_0B_T                               hist2_ctrl_0b;	//0xCC80046C
	PE_O22_HIST2_HIST_AI_CTRL_T                     hist2_hist_ai_ctrl;	//0xCC800470
	PE_O22_HIST2_HIST_AI_DATA_T                     hist2_hist_ai_data;	//0xCC800474
	PE_O22_HIST2_STAT_00_T                               hist2_stat_00;	//0xCC800478
	UINT32                                                   reserved23;	//0xCC80047C
	PE_O22_ND_FSW_CTRL_00_T                             nd_fsw_ctrl_00;	//0xCC800480
	PE_O22_ND_FSW_CTRL_01_T                             nd_fsw_ctrl_01;	//0xCC800484
	PE_O22_ND_FSW_CTRL_02_T                             nd_fsw_ctrl_02;	//0xCC800488
	PE_O22_ND_FSW_CTRL_03_T                             nd_fsw_ctrl_03;	//0xCC80048C
	PE_O22_TNR_ETC_CTRL_00_T                           tnr_etc_ctrl_00;	//0xCC800490
	PE_O22_TNR_ETC_CTRL_01_T                           tnr_etc_ctrl_01;	//0xCC800494
	PE_O22_TNR_ETC_CTRL_02_T                           tnr_etc_ctrl_02;	//0xCC800498
	PE_O22_TNR_ETC_CTRL_03_T                           tnr_etc_ctrl_03;	//0xCC80049C
	PE_O22_TNR_CTRL_56_T                                   tnr_ctrl_56;	//0xCC8004A0
	PE_O22_TNR_CTRL_57_T                                   tnr_ctrl_57;	//0xCC8004A4
	PE_O22_TNR_CTRL_58_T                                   tnr_ctrl_58;	//0xCC8004A8
	PE_O22_TNR_CTRL_59_T                                   tnr_ctrl_59;	//0xCC8004AC
	PE_O22_TNR_CTRL_60_T                                   tnr_ctrl_60;	//0xCC8004B0
	PE_O22_TNR_CTRL_61_T                                   tnr_ctrl_61;	//0xCC8004B4
	PE_O22_PE0_DEBUG3_T                                     pe0_debug3;	//0xCC8004B8
	UINT32                                                   reserved24;	//0xCC8004BC
	PE_O22_FBC_CTRL_02_T                                   fbc_ctrl_02;	//0xCC8004C0
	PE_O22_FBC_CTRL_03_T                                   fbc_ctrl_03;	//0xCC8004C4
	UINT32                                                   reserved25;	//0xCC8004C8
	UINT32                                                   reserved26;	//0xCC8004CC
	PE_O22_GFD_CTRL_00_T                                   gfd_ctrl_00;	//0xCC8004D0
	PE_O22_GFD_CTRL_01_T                                   gfd_ctrl_01;	//0xCC8004D4
	PE_O22_GFD_STAT_00_T                                   gfd_stat_00;	//0xCC8004D8
	PE_O22_GFD_STAT_01_T                                   gfd_stat_01;	//0xCC8004DC
	PE_O22_GFD_STAT_02_T                                   gfd_stat_02;	//0xCC8004E0
	PE_O22_GFD_STAT_03_T                                   gfd_stat_03;	//0xCC8004E4
}PE_ND_ND0_REG_O22_T;

typedef struct {
	PE_O22_PE0_LOAD_T                                        pe0_load;	//0xCC800500
	PE_O22_PE0_INTR_T                                        pe0_intr;	//0xCC800504
	PE_O22_PE0_STATUS0_T                                  pe0_status0;	//0xCC800508
	PE_O22_PE0_STATUS1_T                                  pe0_status1;	//0xCC80050C
	PE_O22_PE0_OPMODE_T                                    pe0_opmode;	//0xCC800510
	PE_O22_PE0_IN_SIZE_T                                  pe0_in_size;	//0xCC800514
	PE_O22_PE0_IN_OFFSET_T                              pe0_in_offset;	//0xCC800518
	PE_O22_PE0_OUT_SIZE_T                                pe0_out_size;	//0xCC80051C
	PE_O22_WIN_CTRL_0_T                                    win_ctrl_0;	//0xCC800520
	PE_O22_WIN_CTRL_1_T                                    win_ctrl_1;	//0xCC800524
	PE_O22_WIN_CTRL_2_T                                    win_ctrl_2;	//0xCC800528
	PE_O22_WIN_CTRL_3_T                                    win_ctrl_3;	//0xCC80052C
	PE_O22_CUP_CTRL_00_T                                  cup_ctrl_00;	//0xCC800530
	PE_O22_CUP_CTRL_01_T                                  cup_ctrl_01;	//0xCC800534
	PE_O22_CUP_CTRL_02_T                                  cup_ctrl_02;	//0xCC800538
	UINT32                                                    reserved0;	//0xCC80053C
	UINT32                                                    reserved1;	//0xCC800540
	UINT32                                                    reserved2;	//0xCC800544
	UINT32                                                    reserved3;	//0xCC800548
	UINT32                                                    reserved4;	//0xCC80054C
	UINT32                                                    reserved5;	//0xCC800550
	UINT32                                                    reserved6;	//0xCC800554
	UINT32                                                    reserved7;	//0xCC800558
	UINT32                                                    reserved8;	//0xCC80055C
	UINT32                                                    reserved9;	//0xCC800560
	UINT32                                                   reserved10;	//0xCC800564
	UINT32                                                   reserved11;	//0xCC800568
	UINT32                                                   reserved12;	//0xCC80056C
	UINT32                                                   reserved13;	//0xCC800570
	UINT32                                                   reserved14;	//0xCC800574
	UINT32                                                   reserved15;	//0xCC800578
	UINT32                                                   reserved16;	//0xCC80057C
	PE_O22_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0xCC800580
	PE_O22_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0xCC800584
	PE_O22_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0xCC800588
	PE_O22_CTI_CTRL_0_T                                    cti_ctrl_0;	//0xCC80058C
	PE_O22_CTI_CTRL_1_T                                    cti_ctrl_1;	//0xCC800590
	PE_O22_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCC800594
	PE_O22_DNR_DBAR_CTRL_T                              dnr_dbar_ctrl;	//0xCC800598
	PE_O22_REG_C420_CTRL_T                              reg_c420_ctrl;	//0xCC80059C
	PE_O22_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCC8005A0
	PE_O22_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCC8005A4
	PE_O22_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCC8005A8
	PE_O22_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCC8005AC
	PE_O22_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCC8005B0
	PE_O22_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCC8005B4
	PE_O22_DETAIL_CTRL_T                                  detail_ctrl;	//0xCC8005B8
	PE_O22_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCC8005BC
	PE_O22_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCC8005C0
	PE_O22_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCC8005C4
	PE_O22_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCC8005C8
	PE_O22_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCC8005CC
	PE_O22_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCC8005D0
	PE_O22_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCC8005D4
	PE_O22_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCC8005D8
	PE_O22_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCC8005DC
	PE_O22_DNR_STAT_0_T                                    dnr_stat_0;	//0xCC8005E0
	PE_O22_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCC8005E4
	PE_O22_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCC8005E8
	PE_O22_DNR_STAT_1_T                                    dnr_stat_1;	//0xCC8005EC
	PE_O22_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCC8005F0
	PE_O22_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCC8005F4
	PE_O22_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCC8005F8
	PE_O22_DNR_STAT_2_T                                    dnr_stat_2;	//0xCC8005FC
	PE_O22_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCC800600
	PE_O22_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCC800604
	PE_O22_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCC800608
	PE_O22_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCC80060C
	PE_O22_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCC800610
	PE_O22_IFC_CTRL_0_T                                    ifc_ctrl_0;	//0xCC800614
	PE_O22_IFC_CTRL_1_T                                    ifc_ctrl_1;	//0xCC800618
	PE_O22_IFC_CTRL_2_T                                    ifc_ctrl_2;	//0xCC80061C
	PE_O22_IFC_CTRL_3_T                                    ifc_ctrl_3;	//0xCC800620
	PE_O22_IFC_CTRL_4_T                                    ifc_ctrl_4;	//0xCC800624
	PE_O22_IFC_CTRL_5_T                                    ifc_ctrl_5;	//0xCC800628
	PE_O22_IFC_CTRL_6_T                                    ifc_ctrl_6;	//0xCC80062C
	PE_O22_IFC_CTRL_7_T                                    ifc_ctrl_7;	//0xCC800630
	PE_O22_IFC_CTRL_8_T                                    ifc_ctrl_8;	//0xCC800634
	PE_O22_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCC800638
	PE_O22_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCC80063C
	PE_O22_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCC800640
	PE_O22_IFC_CTRL_12_T                                  ifc_ctrl_12;	//0xCC800644
	PE_O22_IFC_CTRL_13_T                                  ifc_ctrl_13;	//0xCC800648
	PE_O22_IFC_CTRL_14_T                                  ifc_ctrl_14;	//0xCC80064C
	PE_O22_IFC_CTRL_15_T                                  ifc_ctrl_15;	//0xCC800650
	PE_O22_IFC_CTRL_16_T                                  ifc_ctrl_16;	//0xCC800654
	PE_O22_IFC_CTRL_17_T                                  ifc_ctrl_17;	//0xCC800658
	PE_O22_IFC_CTRL_18_T                                  ifc_ctrl_18;	//0xCC80065C
	PE_O22_IFC_CTRL_19_T                                  ifc_ctrl_19;	//0xCC800660
	PE_O22_IFC_CTRL_20_T                                  ifc_ctrl_20;	//0xCC800664
	PE_O22_IFC_CTRL_21_T                                  ifc_ctrl_21;	//0xCC800668
	PE_O22_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCC80066C
	PE_O22_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCC800670
	PE_O22_SC_BNR_CTRL_2_T                              sc_bnr_ctrl_2;	//0xCC800674
	PE_O22_SC_BNR_CTRL_3_T                              sc_bnr_ctrl_3;	//0xCC800678
	PE_O22_SC_BNR_CTRL_4_T                              sc_bnr_ctrl_4;	//0xCC80067C
	PE_O22_SC_BNR_CTRL_5_T                              sc_bnr_ctrl_5;	//0xCC800680
	PE_O22_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCC800684
	PE_O22_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCC800688
	PE_O22_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCC80068C
	PE_O22_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCC800690
	PE_O22_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCC800694
	PE_O22_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCC800698
	PE_O22_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCC80069C
	PE_O22_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCC8006A0
	PE_O22_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCC8006A4
	PE_O22_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCC8006A8
	PE_O22_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCC8006AC
	PE_O22_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCC8006B0
	PE_O22_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCC8006B4
	PE_O22_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCC8006B8
	PE_O22_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCC8006BC
	PE_O22_TPD_CTRL_0_T                                    tpd_ctrl_0;	//0xCC8006C0
	PE_O22_WINDOW_MODE_0_T                              window_mode_0;	//0xCC8006C4
	PE_O22_WINDOW_MODE_1_T                              window_mode_1;	//0xCC8006C8
	UINT32                                                   reserved17;	//0xCC8006CC
	PE_O22_DNR_STAT_3_T                                    dnr_stat_3;	//0xCC8006D0
	PE_O22_DNR_STAT_4_T                                    dnr_stat_4;	//0xCC8006D4
	PE_O22_DNR_STAT_5_T                                    dnr_stat_5;	//0xCC8006D8
	PE_O22_DNR_STAT_6_T                                    dnr_stat_6;	//0xCC8006DC
	PE_O22_DNR_STAT_7_T                                    dnr_stat_7;	//0xCC8006E0
	PE_O22_DNR_STAT_8_SC_BNR0_T                    dnr_stat_8_sc_bnr0;	//0xCC8006E4
	PE_O22_DNR_STAT_9_SC_BNR1_T                    dnr_stat_9_sc_bnr1;	//0xCC8006E8
	PE_O22_DNR_STAT_10_SC_BNR2_T                  dnr_stat_10_sc_bnr2;	//0xCC8006EC
	PE_O22_DNR_STAT_11_SQM_00_T                    dnr_stat_11_sqm_00;	//0xCC8006F0
	PE_O22_DNR_STAT_12_SQM_01_T                    dnr_stat_12_sqm_01;	//0xCC8006F4
	PE_O22_DNR_STAT_13_SQM_02_T                    dnr_stat_13_sqm_02;	//0xCC8006F8
	PE_O22_DNR_STAT_14_SQM_03_T                    dnr_stat_14_sqm_03;	//0xCC8006FC
	PE_O22_DNR_STAT_15_SQM_04_T                    dnr_stat_15_sqm_04;	//0xCC800700
	PE_O22_DNR_STAT_16_SQM_05_T                    dnr_stat_16_sqm_05;	//0xCC800704
	PE_O22_DNR_STAT_17_SQM_06_T                    dnr_stat_17_sqm_06;	//0xCC800708
	PE_O22_DNR_STAT_18_SQM_07_T                    dnr_stat_18_sqm_07;	//0xCC80070C
	PE_O22_DNR_STAT_19_SQM_08_T                    dnr_stat_19_sqm_08;	//0xCC800710
	PE_O22_DNR_STAT_20_SQM_09_T                    dnr_stat_20_sqm_09;	//0xCC800714
	PE_O22_DNR_STAT_21_SQM_10_T                    dnr_stat_21_sqm_10;	//0xCC800718
	PE_O22_DNR_STAT_22_SQM_11_T                    dnr_stat_22_sqm_11;	//0xCC80071C
	PE_O22_DNR_STAT_23_TPD_0_T                      dnr_stat_23_tpd_0;	//0xCC800720
	PE_O22_DNR_STAT_24_TPD_1_T                      dnr_stat_24_tpd_1;	//0xCC800724
	PE_O22_DNR_STAT_25_TPD_2_T                      dnr_stat_25_tpd_2;	//0xCC800728
	UINT32                                                   reserved18;	//0xCC80072C
	PE_O22_AC_BNR_15_T                                      ac_bnr_15;	//0xCC800730
	PE_O22_AC_BNR_16_T                                      ac_bnr_16;	//0xCC800734
	PE_O22_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0xCC800738
	PE_O22_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0xCC80073C
	PE_O22_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0xCC800740
	PE_O22_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0xCC800744
	PE_O22_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0xCC800748
	PE_O22_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0xCC80074C
	PE_O22_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0xCC800750
	PE_O22_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0xCC800754
	PE_O22_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0xCC800758
	PE_O22_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0xCC80075C
	PE_O22_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0xCC800760
	PE_O22_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCC800764
	PE_O22_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCC800768
	PE_O22_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCC80076C
	PE_O22_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCC800770
	PE_O22_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCC800774
	PE_O22_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCC800778
	PE_O22_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCC80077C
	PE_O22_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCC800780
	PE_O22_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCC800784
	PE_O22_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCC800788
	PE_O22_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCC80078C
	PE_O22_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCC800790
	PE_O22_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCC800794
	PE_O22_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCC800798
	PE_O22_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCC80079C
	PE_O22_REG_CTI_CTRL_2_T                            reg_cti_ctrl_2;	//0xCC8007A0
	PE_O22_REG_CTI_CTRL_3_T                            reg_cti_ctrl_3;	//0xCC8007A4
	PE_O22_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCC8007A8
	PE_O22_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCC8007AC
	PE_O22_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCC8007B0
	PE_O22_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCC8007B4
	PE_O22_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCC8007B8
	PE_O22_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCC8007BC
	PE_O22_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCC8007C0
	PE_O22_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCC8007C4
	PE_O22_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCC8007C8
	PE_O22_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCC8007CC
	PE_O22_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCC8007D0
	PE_O22_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCC8007D4
	PE_O22_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCC8007D8
	PE_O22_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCC8007DC
	PE_O22_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCC8007E0
	PE_O22_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCC8007E4
	PE_O22_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCC8007E8
	PE_O22_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCC8007EC
	PE_O22_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCC8007F0
	PE_O22_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCC8007F4
	PE_O22_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCC8007F8
	PE_O22_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCC8007FC
	PE_O22_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCC800800
	PE_O22_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCC800804
	PE_O22_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCC800808
	PE_O22_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCC80080C
	PE_O22_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCC800810
	PE_O22_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCC800814
	PE_O22_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCC800818
	PE_O22_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCC80081C
	PE_O22_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCC800820
	PE_O22_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCC800824
	PE_O22_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCC800828
	PE_O22_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCC80082C
	PE_O22_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCC800830
	PE_O22_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCC800834
	PE_O22_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCC800838
	PE_O22_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCC80083C
	PE_O22_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCC800840
	PE_O22_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCC800844
	PE_O22_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCC800848
	PE_O22_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCC80084C
	PE_O22_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCC800850
	PE_O22_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCC800854
	PE_O22_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCC800858
	PE_O22_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCC80085C
	PE_O22_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCC800860
	PE_O22_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCC800864
	PE_O22_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCC800868
	PE_O22_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCC80086C
	PE_O22_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCC800870
	PE_O22_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCC800874
	PE_O22_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCC800878
	PE_O22_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCC80087C
	PE_O22_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCC800880
	PE_O22_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCC800884
	PE_O22_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCC800888
	PE_O22_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCC80088C
	PE_O22_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCC800890
	PE_O22_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCC800894
	PE_O22_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCC800898
	PE_O22_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCC80089C
	PE_O22_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCC8008A0
	PE_O22_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCC8008A4
	PE_O22_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCC8008A8
	PE_O22_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCC8008AC
	PE_O22_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCC8008B0
	PE_O22_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCC8008B4
	PE_O22_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCC8008B8
	PE_O22_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCC8008BC
	PE_O22_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCC8008C0
	PE_O22_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCC8008C4
	PE_O22_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCC8008C8
	PE_O22_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCC8008CC
	PE_O22_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCC8008D0
	PE_O22_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCC8008D4
	PE_O22_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCC8008D8
	PE_O22_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCC8008DC
	PE_O22_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCC8008E0
	PE_O22_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCC8008E4
	PE_O22_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCC8008E8
	PE_O22_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCC8008EC
	PE_O22_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCC8008F0
	PE_O22_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC8008F4
	PE_O22_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC8008F8
	PE_O22_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC8008FC
	PE_O22_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC800900
	PE_O22_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC800904
	PE_O22_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC800908
	PE_O22_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC80090C
	PE_O22_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC800910
	PE_O22_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC800914
	PE_O22_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC800918
	PE_O22_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC80091C
	PE_O22_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC800920
	PE_O22_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC800924
	PE_O22_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC800928
	PE_O22_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC80092C
	PE_O22_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC800930
	PE_O22_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC800934
	PE_O22_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC800938
	PE_O22_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC80093C
	PE_O22_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC800940
	PE_O22_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC800944
	PE_O22_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC800948
	PE_O22_REG_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xCC80094C
	PE_O22_REG_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xCC800950
	PE_O22_REG_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xCC800954
	PE_O22_REG_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xCC800958
	PE_O22_REG_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xCC80095C
	PE_O22_REG_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xCC800960
	PE_O22_REG_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xCC800964
	PE_O22_MNR_CTRL_13_T                                  mnr_ctrl_13;	//0xCC800968
	PE_O22_MNR_CTRL_14_T                                  mnr_ctrl_14;	//0xCC80096C
	PE_O22_MNR_CTRL_15_T                                  mnr_ctrl_15;	//0xCC800970
	PE_O22_MNR_CTRL_16_T                                  mnr_ctrl_16;	//0xCC800974
	PE_O22_MNR_CTRL_17_T                                  mnr_ctrl_17;	//0xCC800978
	PE_O22_REG_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xCC80097C
	PE_O22_REG_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xCC800980
	PE_O22_REG_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xCC800984
	PE_O22_REG_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xCC800988
	PE_O22_REG_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xCC80098C
	PE_O22_REG_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xCC800990
	PE_O22_REG_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xCC800994
	PE_O22_REG_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xCC800998
}PE_ND_DNR0_REG_O22_T;

typedef struct {
	PE_O22_CTRL_CTRL_M0_Y_LEVEL_CTRL_T         ctrl_m0_y_level_ctrl; //0xC90030B8
}PE_TOP_IMX_REG_O22_T;

#endif
