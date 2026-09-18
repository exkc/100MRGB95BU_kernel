/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 

#ifndef _DE_CTR_REG_O26A0_H_
#define _DE_CTR_REG_O26A0_H_

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10010 RW 0x0000_0000
	UINT32 intr_i0_intr_pulse               :1;	//(0,RW,0x00) //[SRC_PULSE] s0_src_pulse
	UINT32 intr_i1_intr_pulse               :1;	//(1,RW,0x00) //[SRC_PULSE] s2_src_pulse
	UINT32 intr_i2_intr_pulse               :1;	//(2,RW,0x00) //[SRC_PULSE] s4_src_pulse
	UINT32 intr_i3_intr_pulse               :1;	//(3,RW,0x00) //[SRC_PULSE] s6_src_pulse
	UINT32 intr_i4_intr_pulse               :1;	//(4,RW,0x00) //[SRC_PULSE] s7_src_pulse
	UINT32 intr_i5_intr_pulse               :1;	//(5,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i6_intr_pulse               :1;	//(6,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i7_intr_pulse               :1;	//(7,RW,0x00) //[SRC_PULSE] SOSD_VA_FAL
	UINT32 intr_g0_pic_end                  :1;	//(8,RW,0x00) //[FRAME_END] IPP_M0_W
	UINT32 intr_g1_pic_end                  :1;	//(9,RW,0x00) //[FRAME_END] IPP_M0_R
	UINT32 intr_g2_pic_end                  :1;	//(10,RW,0x00) //[FRAME_END] FPP_F0_W
	UINT32 intr_g3_pic_end                  :1;	//(11,RW,0x00) //[FRAME_END] FPP_F0_R
	UINT32 intr_g4_pic_end                  :1;	//(12,RW,0x00) //[FRAME_END] IPP_S0_W
	UINT32 intr_g5_pic_end                  :1;	//(13,RW,0x00) //[NOT AVAILABLE]
	UINT32 intr_g6_pic_end                  :1;	//(14,RW,0x00) //[FRAME_END] IPP_C0_W
	UINT32 intr_g7_pic_end                  :1;	//(15,RW,0x00) //[NOT AVAILABLE]
	UINT32 intr_ipp_m0                      :1;	//(16,RW,0x00) //[IPP_M0] IPP_M0 Line Intr
	UINT32 intr_mif_imx0                    :1;	//(17,RW,0x00) //[MIF0] MIF_IMX0
	UINT32 intr_mif_imx1                    :1;	//(18,RW,0x00) //[MIF1] MIF_IMX1
	UINT32 intr_dolby_des_m1_ready          :1;	//(19,RW,0x00) //[HDMI Dolby META] M1 Path Dolby Meta Data Ready
	UINT32 intr_dolby_des_m0_ready          :1;	//(20,RW,0x00) //[HDMI Dolby META] M0 Path Dolby Meta Data Ready
	UINT32 intr_vdo                         :1;	//(21,RW,0x00) //[VDO] VDO
	UINT32 intr_dolby_des_m0_crc_error      :1;	//(22,RW,0x00) //[HDMI Dolby META] M0 Path Dolby Meta Data CRC ERR
	UINT32 intr_dolby_des_m1_crc_error      :1;	//(23,RW,0x00) //[HDMI Dolby META] M1 Path Dolby Meta Data CRC ERR
	UINT32 resvd                            :8;
	};
}O26A0_IMX_CTRL_INTR_REG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230050 RW 0x0000_0000
	UINT32 intr_i0_intr_pulse               :1;	//(0,RW,0x00) //[SRC_PULSE] s0_src_pulse
	UINT32 intr_i1_intr_pulse               :1;	//(1,RW,0x00) //[SRC_PULSE] s2_src_pulse
	UINT32 intr_i2_intr_pulse               :1;	//(2,RW,0x00) //[SRC_PULSE] s4_src_pulse
	UINT32 intr_i3_intr_pulse               :1;	//(3,RW,0x00) //[SRC_PULSE] s6_src_pulse
	UINT32 intr_i4_intr_pulse               :1;	//(4,RW,0x00) //[SRC_PULSE] s7_src_pulse
	UINT32 intr_i5_intr_pulse               :1;	//(5,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i6_intr_pulse               :1;	//(6,RW,0x00) //[SRC_PULSE] DISP_VA_FAL
	UINT32 intr_i7_intr_pulse               :1;	//(7,RW,0x00) //[SRC_PULSE] SOSD_VA_FAL
	UINT32 intr_g0_pic_end                  :1;	//(8,RW,0x00) //[FRAME_END] BL_Y_END
	UINT32 intr_g1_pic_end                  :1;	//(9,RW,0x00) //[FRAME_END] BL_C_END
	UINT32 intr_g2_pic_end                  :1;	//(10,RW,0x00) //[FRAME_END] EL_Y_END
	UINT32 intr_g3_pic_end                  :1;	//(11,RW,0x00) //[FRAME_END] EL_C_END
	UINT32 intr_g4_pic_end                  :1;	//(12,RW,0x00) //[FRAME_END]
	UINT32 intr_g5_pic_end                  :1;	//(13,RW,0x00) //[FRAME_END]
	UINT32 intr_g6_pic_end                  :1;	//(14,RW,0x00) //[FRAME_END]
	UINT32 intr_g7_pic_end                  :1;	//(15,RW,0x00) //[FRAME_END]
	UINT32 hdr_dolby_3d_lut_wr_done_intr    :1;	//(16,RW,0x00) //[INTERRUPT] manual copy over intr
	UINT32 hdr_md_ready_intr                :1;	//(17,RW,0x00) //[INTERRUPT] cpu can read metadata from HDR APB
	UINT32 hdr_dolby_bl_va_f_intr           :1;	//(18,RW,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_bl_va_r_intr           :1;	//(19,RW,0x00) //[INTERRUPT]
	UINT32 reserved                         :1;	//(20,Rsvd,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_el_va_r_intr           :1;	//(21,RW,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_el_va_f_intr           :1;	//(22,RW,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_out_va_r_intr          :1;	//(23,RW,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_out_va_f_intr          :1;	//(24,RW,0x00) //[INTERRUPT]
	UINT32 hdr_dolby_sync_end_intr          :1;	//(25,RW,0x00) //[INTERRUPT]
	UINT32 hdr_lg1_out_va_f_intr            :1;	//(26,RW,0x00) //[INTERRUPT]
	UINT32 hdr_lg0_out_va_r_intr            :1;	//(27,RW,0x00) //[INTERRUPT]
	UINT32 hdr_lg0_out_va_f_intr            :1;	//(28,RW,0x00) //[INTERRUPT]
	UINT32 hdr_tone_pic_end_intr            :1;	//(29,RW,0x00) //[INTERRUPT] completed set TC LUT from CPU to HDR
	UINT32 hdr_threed_pic_end_intr          :1;	//(30,RW,0x00) //[INTERRUPT] completed set 3D LUT from CPU to HDR
	UINT32 dolby_intr                       :1;	//(31,RW,0x00) //[INTERRUPT] dolby_intr. reference [dolby_hdr] tap at the HDR reg
	};
}O26A0_HDR_CTRL_INTR_CPU_REG_T;

#endif

