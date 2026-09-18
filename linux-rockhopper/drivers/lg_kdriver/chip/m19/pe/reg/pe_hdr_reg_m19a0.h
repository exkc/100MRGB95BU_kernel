/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef _PE_HDR_REG_M19A0_H_
#define _PE_HDR_REG_M19A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9005800L HDR_TOP_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	load_time                          :1 ,	// 0 
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_M19_HDR_LG_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005804L HDR_TOP_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	width                              :16,	// 15:0
	height                             :16;	// 31:16
}PE_M19_HDR_LG_TOP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005808L HDR_TOP_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vdpulse_pos;	// 31:0
}PE_M19_HDR_LG_TOP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900580cL HDR_TOP_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt                               :16,	// 15:0
	vcnt2                              :16;	// 31:16
}PE_M19_HDR_LG_TOP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005810L HDR_TOP_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_to_cnt                           :12,	// 11:0
	reserved01                         :18,	// reserved
	va_pe1_in                          :1 ,	// 30
	va_pe1_out                         :1 ;	// 31
}PE_M19_HDR_LG_TOP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005814L HDR_TOP_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hue_sat_prsv_ref               :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_tcm_inp_src                    :1 ,	// 4 
	reserved02                         :11,	// reserved
	reg_hue_sat_prsv_src               :2 ,	// 17:16
	reserved03                         :2 ,	// reserved
	reg_hist_src                       :4 ,	// 23:20
	reg_eotf_en                        :1 ,	// 24
	reg_oetf_en                        :1 ,	// 25
	reserved04                         :2 ,	// reserved
	reg_hdr10p_mode                    :1 ,	// 28
	reg_use_equal_llut_en              :1 ,	// 29
	reg_hdr_mode                       :2 ;	// 31:30
}PE_M19_HDR_LG_TOP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005818L HDR_TOP_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hdr_eotf_120hz_mode            :1 ,	// 0 
	reg_eotf_same_write_mode           :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	reg_eotf_dbuf_mode                 :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_eotf_dbuf_wptr                 :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	reg_eotf_dbuf_rptr                 :1 ,	// 12
	reserved04                         :3 ,	// reserved
	reg_eotf_dbuf_ptr_imode            :1 ,	// 16
	reserved05                         :7 ,	// reserved
	reg_eotf_ra_mode                   :1 ;	// 24
}PE_M19_HDR_LG_TOP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900581cL HDR_TOP_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hdr_oetf_120hz_mode            :1 ,	// 0 
	reg_oetf_same_write_mode           :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	reg_oetf_dbuf_mode                 :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_oetf_dbuf_wptr                 :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	reg_oetf_dbuf_rptr                 :1 ,	// 12
	reserved04                         :3 ,	// reserved
	reg_oetf_dbuf_ptr_imode            :1 ,	// 16
	reserved05                         :7 ,	// reserved
	reg_oetf_ra_mode                   :1 ;	// 24
}PE_M19_HDR_LG_TOP_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005850L HDR_CSC1_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc1st_en                      :1 ;	// 0 
}PE_M19_HDR_LG_CSC1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005854L HDR_CSC1_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef1                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc1st_coef0                     :15;	// 30:16
}PE_M19_HDR_LG_CSC1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005858L HDR_CSC1_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef3                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc1st_coef2                     :15;	// 30:16
}PE_M19_HDR_LG_CSC1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900585cL HDR_CSC1_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef5                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc1st_coef4                     :15;	// 30:16
}PE_M19_HDR_LG_CSC1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005860L HDR_CSC1_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_coef7                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc1st_coef6                     :15;	// 30:16
}PE_M19_HDR_LG_CSC1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005864L HDR_CSC1_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_csc1st_coef8                     :15;	// 30:16
}PE_M19_HDR_LG_CSC1_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005868L HDR_CSC1_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst1                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc1st_ofst0                     :11;	// 26:16
}PE_M19_HDR_LG_CSC1_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900586cL HDR_CSC1_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst3                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc1st_ofst2                     :11;	// 26:16
}PE_M19_HDR_LG_CSC1_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005870L HDR_CSC1_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_ofst5                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc1st_ofst4                     :11;	// 26:16
}PE_M19_HDR_LG_CSC1_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005874L HDR_CSC1_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc1st_dbg_en                    :1 ,	// 0:0
	reserved01                         :3 ,	// reserved
	r_csc1st_dbg_ugy                   :4 ,	// 7:4
	r_csc1st_dbg_ucb                   :4 ,	// 11:8
	r_csc1st_dbg_ucr                   :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	r_csc1st_dbg_ogy                   :4 ,	// 23:20
	r_csc1st_dbg_ocb                   :4 ,	// 11:8
	r_csc1st_dbg_ocr                   :4 ;	// 15:12
}PE_M19_HDR_LG_CSC1_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005878L HDR_CSC1_ERR_CNT                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ireg_csc_cnt_under                 :16,	// 15:0
	ireg_csc_cnt_over                  :16;	// 31:16
}PE_M19_HDR_LG_CSC1_ERR_CNT_T;
/*-----------------------------------------------------------------------------
                             0xc9005890L HDR_EOTF_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lut_addr                           :10,	// 9:0
	reserved01                         :2 ,	// reserved
	lut_ai                             :1 ,	// 12
	reserved02                         :14,	// reserved
	reg_use_own_lut_hif                :1 ,	// 27
	eotf_lut_color_type                :2 ;	// 29:28
}PE_M19_HDR_LG_EOTF_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005894L HDR_EOTF_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	eotf_lut_data;	// 31:0
}PE_M19_HDR_LG_EOTF_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005898L HDR_OETF_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lut_addr                           :10,	// 9:0
	reserved01                         :2 ,	// reserved
	lut_ai                             :1 ,	// 12
	reserved02                         :14,	// reserved
	reg_use_own_lut_hif                :1 ,	// 27
	oetf_lut_color_type                :2 ;	// 29:28
}PE_M19_HDR_LG_OETF_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900589cL HDR_OETF_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	oetf_lut_data_o                    :16,	// 15:0
	oetf_lut_data_e                    :16;	// 31:16
}PE_M19_HDR_LG_OETF_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90058a0L HDR_PCC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_en                         :1 ;	// 0 
}PE_M19_HDR_LG_PCC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90058a4L HDR_PCC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pcc_coef1                        :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_pcc_coef0                        :15;	// 30:16
}PE_M19_HDR_LG_PCC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90058a8L HDR_PCC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pcc_coef3                        :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_pcc_coef2                        :15;	// 30:16
}PE_M19_HDR_LG_PCC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90058acL HDR_PCC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pcc_coef5                        :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_pcc_coef4                        :15;	// 30:16
}PE_M19_HDR_LG_PCC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90058b0L HDR_PCC_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pcc_coef7                        :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_pcc_coef6                        :15;	// 30:16
}PE_M19_HDR_LG_PCC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90058b4L HDR_PCC_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_pcc_coef8                        :15;	// 30:16
}PE_M19_HDR_LG_PCC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90058d0L HDR_HUE_SAT_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hue_prsv_en                    :1 ,	// 0 
	reg_sat_prsv_en                    :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	reg_hue_prsv_ratio                 :10,	// 13:4
	reserved02                         :2 ,	// reserved
	reg_sat_prsv_ratio                 :10;	// 25:16
}PE_M19_HDR_LG_HUE_SAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90058d4L HDR_HUE_SAT_ALPHA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_inp_l_sel                      :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_inp_s_sel                      :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_out_lgain_sel                  :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	reg_out_sgain_sel                  :1 ;	// 12
}PE_M19_HDR_LG_HUE_SAT_ALPHA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90058e0L HDR_TCM_PREP_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_tone_map_rgb2y_coef1             :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_tone_map_rgb2y_coef0             :15;	// 30:16
}PE_M19_HDR_LG_TCM_PREP_00_T;
/*-----------------------------------------------------------------------------
                             0xc90058e4L HDR_TCM_PREP_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_tone_map_rgbymax_sel             :3 ,	// 2:0
	reserved01                         :13,	// reserved
	r_tone_map_rgb2y_coef2             :15;	// 30:16
}PE_M19_HDR_LG_TCM_PREP_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005990L HDR_CLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_clut_65th_data                 :11;	// 10:0
}PE_M19_HDR_LG_CLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005994L HDR_CLUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clut_addr                          :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	clut_ai                            :1 ,	// 12
	reserved02                         :16,	// reserved
	clut_manual_load_en                :1 ,	// 29
	reg_write_mode_en                  :1 ,	// 30
	reg_lut_wr_done                    :1 ;	// 31
}PE_M19_HDR_LG_CLUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005998L HDR_CLUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clut_data                          :11;	// 10:0
}PE_M19_HDR_LG_CLUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc900599cL HDR_PLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_plut_65th_data                 :14;	// 13:0
}PE_M19_HDR_LG_PLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90059a0L HDR_PLUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	plut_addr                          :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	plut_ai                            :1 ,	// 12
	reserved02                         :16,	// reserved
	plut_manual_load_en                :1 ,	// 29
	reg_write_mode_en                  :1 ,	// 30
	reg_lut_wr_done                    :1 ;	// 31
}PE_M19_HDR_LG_PLUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90059a4L HDR_PLUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	plut_data                          :14;	// 13:0
}PE_M19_HDR_LG_PLUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90059a8L HDR_SLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_slut_65th_data                 :10;	// 9:0
}PE_M19_HDR_LG_SLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90059acL HDR_SLUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	slut_addr                          :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	slut_ai                            :1 ,	// 12
	reserved02                         :16,	// reserved
	slut_manual_load_en                :1 ,	// 29
	reg_write_mode_en                  :1 ,	// 30
	reg_lut_wr_done                    :1 ;	// 31
}PE_M19_HDR_LG_SLUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90059b0L HDR_SLUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	slut_data                          :10;	// 9:0
}PE_M19_HDR_LG_SLUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90059b4L HDR_ILUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ilut_65th_data                 :8 ;	// 7:0
}PE_M19_HDR_LG_ILUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90059b8L HDR_ILUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ilut_addr                          :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	ilut_ai                            :1 ,	// 12
	reserved02                         :16,	// reserved
	ilut_manual_load_en                :1 ,	// 29
	reg_write_mode_en                  :1 ,	// 30
	reg_lut_wr_done                    :1 ;	// 31
}PE_M19_HDR_LG_ILUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90059bcL HDR_ILUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ilut_data                          :8 ;	// 7:0
}PE_M19_HDR_LG_ILUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90059c0L HDR_DLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dlut_65th_data                 :12,	// 11:0
	reserved01                         :4 , // reserved
	reg_dlut_threshold_0               :13;	// 28:16
}PE_M19_HDR_LG_DLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90059c4L HDR_DLUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dlut_threshold_1               :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_dlut_threshold_2               :13;	// 28:16
}PE_M19_HDR_LG_DLUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90059c8L HDR_DLUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dlut_step_0                    :4 ,	// 3:0
	reg_dlut_step_1                    :4 ,	// 7:4
	reg_dlut_step_2                    :4 ,	// 11:8
	reg_dlut_step_3                    :4 ;	// 15:12
}PE_M19_HDR_LG_DLUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90059ccL HDR_DLUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dlut_addr                          :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	dlut_ai                            :1 ,	// 12
	reserved02                         :16,	// reserved
	dlut_manual_load_en                :1 ,	// 29
	reg_write_mode_en                  :1 ,	// 30
	reg_lut_wr_done                    :1 ;	// 31
}PE_M19_HDR_LG_DLUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90059d0L HDR_DLUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dlut_data                          :8 ;	// 7:0
}PE_M19_HDR_LG_DLUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90059d4L HDR_TC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_technicolor_detour_en          :1 ,	// 0 
	reserved01                         :3 , // reserved
	reg_range_sel                      :1 ;	// 4 
}PE_M19_HDR_LG_TC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90059d8L HDR_TC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_alpha_a                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_alpha_b                        :13;	// 28:16
}PE_M19_HDR_LG_TC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90059dcL HDR_TC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_oct_0                          :6 ,	// 5:0
	reserved01                         :4 ,	// reserved
	reg_oct_1                          :8 ,	// 17:10
	reserved02                         :2 ,	// reserved
	reg_oct_2                          :9 ;	// 28:20
}PE_M19_HDR_LG_TC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90059e0L HDR_TC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_oct_3                          :10,	// 9:0
	reg_oct_4                          :10,	// 19:10
	reg_oct_5                          :10;	// 29:20
}PE_M19_HDR_LG_TC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90059e4L HDR_TC_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_oct_6                          :10;	// 9:0
}PE_M19_HDR_LG_TC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005a30L HDR_HIST_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_bin_mode                      :2 ,	// 1:0
	histogram_mode                     :2 ,	// 3:2
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved01                         :7 ,	// reserved
	window_inout_sel                   :1 ,	// 16
	reserved02                         :6 ,	// reserved
	hist_clear                         :1 ;	// 23
}PE_M19_HDR_LG_HIST_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005a34L HDR_HIST_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_HDR_LG_HIST_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005a38L HDR_HIST_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_HDR_LG_HIST_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005a3cL HDR_HIST_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_HDR_LG_HIST_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005a40L HDR_HIST_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_HDR_LG_HIST_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005a44L HDR_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status0                       :5 ,	// 4:0
	reserved01                         :7 ,	// reserved
	hif_hist_address                   :1 ,	// 12
	reserved02                         :2 ,	// reserved
	hif_hist_ai                        :1 ,	// 15
	hif_hist_enable                    :3 ,	// 18:16
	reserved03                         :9 ,	// reserved
	hif_status_address                 :1 ,	// 28
	hif_status_ai                      :1 ;	// 29
}PE_M19_HDR_LG_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005a48L HDR_HIST_IA_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status0                       :23;	//22:0
}PE_M19_HDR_LG_HIST_IA_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9005a4cL HDR_HIST_IA_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_v_min                         :16,	// 15:0
	hist_v_max                         :16;	// 31:16
}PE_M19_HDR_LG_HIST_IA_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9005a50L HDR_LLUT0_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut0_enable              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ;	// 16
}PE_M19_HDR_LG_LLUT0_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005a54L HDR_LLUT0_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT0_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005a58L HDR_LLUT0_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT0_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005a5cL HDR_LLUT0_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT0_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005a60L HDR_LLUT0_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT0_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005a64L HDR_LLUT0_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_wdata_x_33rd;	// 31:0
}PE_M19_HDR_LG_LLUT0_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005a68L HDR_LLUT0_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_wdata_y_33rd             :16;	// 15:0
}PE_M19_HDR_LG_LLUT0_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005a70L HDR_LLUT0_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_address                  :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_llut0_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut0_manual_load_en           :1 ,	// 11
	hif_llut0_ai                       :1 ,	// 12
	hif_llut0_write_x                  :1 ,	// 13
	hif_llut0_read_x                   :1 ,	// 14
	hif_llut0_enable                   :1 ;	// 15
}PE_M19_HDR_LG_LLUT0_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005a74L HDR_LLUT0_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_wdata_y                  :16,	// 15:0
	hif_llut0_wdata_x                  :16;	// 31:16
}PE_M19_HDR_LG_LLUT0_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005a80L HDR_LLUT1_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut1_enable              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ;	// 16
}PE_M19_HDR_LG_LLUT1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005a84L HDR_LLUT1_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005a88L HDR_LLUT1_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005a8cL HDR_LLUT1_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005a90L HDR_LLUT1_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005a94L HDR_LLUT1_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_wdata_x_33rd;	// 31:0
}PE_M19_HDR_LG_LLUT1_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005a98L HDR_LLUT1_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_wdata_y_33rd             :16;	// 15:0
}PE_M19_HDR_LG_LLUT1_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005aa0L HDR_LLUT1_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_address                  :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_llut1_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut1_manual_load_en           :1 ,	// 11
	hif_llut1_ai                       :1 ,	// 12
	hif_llut1_write_x                  :1 ,	// 13
	hif_llut1_read_x                   :1 ,	// 14
	hif_llut1_enable                   :1 ;	// 15
}PE_M19_HDR_LG_LLUT1_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005aa4L HDR_LLUT1_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_wdata_y                  :16,	// 15:0
	hif_llut1_wdata_x                  :16;	// 31:16
}PE_M19_HDR_LG_LLUT1_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005ab0L HDR_LLUT2_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut2_enable              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ;	// 16
}PE_M19_HDR_LG_LLUT2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005ab4L HDR_LLUT2_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005ab8L HDR_LLUT2_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005abcL HDR_LLUT2_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005ac0L HDR_LLUT2_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005ac4L HDR_LLUT2_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	hif_llut2_wdata_x_33rd             :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005ac8L HDR_LLUT2_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut2_wdata_y_33rd             :16;	// 15:0
}PE_M19_HDR_LG_LLUT2_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005ad0L HDR_LLUT2_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut2_address                  :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_llut2_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut2_manual_load_en           :1 ,	// 11
	hif_llut2_ai                       :1 ,	// 12
	hif_llut2_write_x                  :1 ,	// 13
	hif_llut2_read_x                   :1 ,	// 14
	hif_llut2_enable                   :1 ;	// 15
}PE_M19_HDR_LG_LLUT2_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005ad4L HDR_LLUT2_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut2_wdata_y                  :16,	// 15:0
	hif_llut2_wdata_x                  :16;	// 31:16
}PE_M19_HDR_LG_LLUT2_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005ae0L HDR_GAMMA045_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	gamma045_enable                    :1 ,	// 0
	reserved01                         :3 ,	// reserved
	gamma045_mode                      :1 ,	// 4
	reserved02                         :3 ,	// reserved
	gamma045_mux                       :1 ;	// 8
}PE_M19_HDR_LG_GAMMA045_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005ae8L HDR_DITHER_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dither_en                          :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	dither_random_freeze_en            :1 ,	// 2 
	demo_pattern_enable                :1 ,	// 3 
	bit_mode                           :2 ;	// 5:4
}PE_M19_HDR_LG_DITHER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005aecL HDR_PCC32_GAIN_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_pcc32_ygain_shift              :1 ;	// 0 
}PE_M19_HDR_LG_PCC32_GAIN_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005b00L HDR_3DLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_out_g_mux               :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	reg_3d_lut_out_b_mux               :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_3d_lut_out_r_mux               :2 ,	// 9:8
	reserved03                         :2 ,	// reserved
	reg_3d_lut_in_b_mux                :2 ,	// 13:12
	reserved04                         :2 ,	// reserved
	reg_3d_lut_in_g_mux                :2 ,	// 17:16
	reserved05                         :2 ,	// reserved
	reg_3d_lut_in_r_mux                :2 ,	// 21:20
	reserved06                         :2 ,	// reserved
	reg_3d_lut_in_gb_lshft             :4 ,	// 27:24
	reg_3d_lut_input_mux               :2 ,	// 29:28
	reserved07                         :1 ,	// reserved
	reg_3d_lut_en                      :1 ;	// 31
}PE_M19_HDR_LG_3DLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005b04L HDR_3DLUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_th_min0                 :16;	// 15:0
}PE_M19_HDR_LG_3DLUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005b08L HDR_3DLUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_th_min1                 :16,	// 15:0
	reg_3d_lut_th_min2                 :16;	// 31:16
}PE_M19_HDR_LG_3DLUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005b0cL HDR_3DLUT_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_th_max0                 :16,	// 15:0
	reg_3d_lut_th_max1                 :16;	// 31:16
}PE_M19_HDR_LG_3DLUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005b10L HDR_3DLUT_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_diff_maxmin0            :20;	// 19:0
}PE_M19_HDR_LG_3DLUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005b14L HDR_3DLUT_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_diff_maxmin1            :20;	// 19:0
}PE_M19_HDR_LG_3DLUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005b18L HDR_3DLUT_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_diff_maxmin2            :20;	// 19:0
}PE_M19_HDR_LG_3DLUT_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005b1cL HDR_3DLUT_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3d_lut_manual_qtt              :21;	// 20:0
}PE_M19_HDR_LG_3DLUT_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005b20L HDR_YGAIN_LUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut2_enable              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ;	// 16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005b24L HDR_YGAIN_LUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005b28L HDR_YGAIN_LUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005b2cL HDR_YGAIN_LUT_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005b30L HDR_YGAIN_LUT_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005b34L HDR_YGAIN_LUT_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_ygain_lut_wdata_y_33rd         :16,	// 15:0
	hif_ygain_lut_wdata_x_33rd         :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005b38L HDR_YGAIN_LUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_ygain_lut_address              :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_ygain_lut_load                 :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_ygain_lut_manual_load_en       :1 ,	// 11
	hif_ygain_lut_ai                   :1 ,	// 12
	reserved03                         :2 ,	// reserved
	hif_ygain_lut_enable               :1 ;	// 15
}PE_M19_HDR_LG_YGAIN_LUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005b3cL HDR_YGAIN_LUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_ygain_lut_wdata_y              :16,	// 15:0
	hif_ygain_lut_wdata_x              :16;	// 31:16
}PE_M19_HDR_LG_YGAIN_LUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005b40L HDR_RGB2Y_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rgb2yrd_en                     :1 ,	// 0 
	reserved01                         :15,	// reserved
	r_rgb2yrd_coef0                    :15;	// 30:16
}PE_M19_HDR_LG_RGB2Y_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005b44L HDR_RGB2Y_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_coef1                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_rgb2yrd_coef2                    :16;	// 31:16
}PE_M19_HDR_LG_RGB2Y_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005b48L HDR_RGB2Y_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_ofst0                    :17;	// 16:0
}PE_M19_HDR_LG_RGB2Y_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005b4cL HDR_RGB2Y_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_ofst3                    :17;	// 16:0
}PE_M19_HDR_LG_RGB2Y_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005b60L HDR_LGAIN_LUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y0                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x0                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005b64L HDR_LGAIN_LUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y1                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x1                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005b68L HDR_LGAIN_LUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y2                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x2                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005b6cL HDR_LGAIN_LUT_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y3                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x3                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005b70L HDR_LGAIN_LUT_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y4                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x4                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005b74L HDR_LGAIN_LUT_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y5                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x5                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005b78L HDR_LGAIN_LUT_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y6                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x6                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005b7cL HDR_LGAIN_LUT_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lgain_lut_y7                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	lgain_lut_x7                       :16;	// 31:16
}PE_M19_HDR_LG_LGAIN_LUT_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005b80L HDR_SGAIN_LUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y0                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x0                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005b84L HDR_SGAIN_LUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y1                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x1                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005b88L HDR_SGAIN_LUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y2                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x2                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005b8cL HDR_SGAIN_LUT_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y3                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x3                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005b90L HDR_SGAIN_LUT_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y4                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x4                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005b94L HDR_SGAIN_LUT_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y5                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x5                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005b98L HDR_SGAIN_LUT_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y6                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x6                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005b9cL HDR_SGAIN_LUT_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sgain_lut_y7                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	sgain_lut_x7                       :16;	// 31:16
}PE_M19_HDR_LG_SGAIN_LUT_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005ba0L HDR_RGB2Y2_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rgb2yrd_en                     :1 ,	// 0 
	reserved01                         :15,	// reserved
	r_rgb2yrd_coef0                    :15;	// 30:16
}PE_M19_HDR_LG_RGB2Y2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005ba4L HDR_RGB2Y2_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_coef1                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_rgb2yrd_coef2                    :16;	// 31:16
}PE_M19_HDR_LG_RGB2Y2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005ba8L HDR_RGB2Y2_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_ofst0                    :17;	// 16:0
}PE_M19_HDR_LG_RGB2Y2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005bacL HDR_RGB2Y2_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_rgb2yrd_ofst3                    :17;	// 16:0
}PE_M19_HDR_LG_RGB2Y2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005bb0L HDR_CSC3_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc3rd_en                      :1 ;	// 0 
}PE_M19_HDR_LG_CSC3_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005bb4L HDR_CSC3_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_coef1                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc3rd_coef0                     :15;	// 30:16
}PE_M19_HDR_LG_CSC3_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005bb8L HDR_CSC3_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_coef3                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc3rd_coef2                     :15;	// 30:16
}PE_M19_HDR_LG_CSC3_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005bbcL HDR_CSC3_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_coef5                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc3rd_coef4                     :15;	// 30:16
}PE_M19_HDR_LG_CSC3_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005bc0L HDR_CSC3_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_coef7                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc3rd_coef6                     :15;	// 30:16
}PE_M19_HDR_LG_CSC3_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005bc4L HDR_CSC3_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_csc3rd_coef8                     :15;	// 30:16
}PE_M19_HDR_LG_CSC3_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005bc8L HDR_CSC3_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_ofst1                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc3rd_ofst0                     :11;	// 26:16
}PE_M19_HDR_LG_CSC3_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005bccL HDR_CSC3_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_ofst3                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc3rd_ofst2                     :11;	// 26:16
}PE_M19_HDR_LG_CSC3_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005bd0L HDR_CSC3_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc3rd_ofst5                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc3rd_ofst4                     :11;	// 26:16
}PE_M19_HDR_LG_CSC3_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005c00L HDR_SDR2HDR_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ha_length                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_va_length                      :12,	// 27:16
	reserved02                         :2 ,	// reserved
	reg_sdr2hdr_enable                 :1 ,	// 30
	reg_dbg_brm_map                    :1 ;	// 31
}PE_M19_HDR_LG_SDR2HDR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005c04L HDR_SDR2HDR_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ihsv_vgain                     :8 ,	// 07:00
	reg_ihsv_sgain                     :8 ,	// 15:08
	reserved01                         :14,	// reserved
	reg_hsv_scaler_en                  :1 ,	// 30
	reg_hsv_hsl_sel                    :1 ;	// 31
}PE_M19_HDR_LG_SDR2HDR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005c08L HDR_SDR2HDR_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ihsv_voffset                   :8 ,	// 7:0
	reg_ihsv_soffset                   :8 ,	// 15:8
	reg_ihsv_hoffset                   :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005c0cL HDR_SDR2HDR_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cdt_dcp_mean                   :8 ,	// 7:0
	reg_cdt_dcp_eta                    :8 ;	// 15:8
}PE_M19_HDR_LG_SDR2HDR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005c10L HDR_SDR2HDR_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_y_max                      :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_fbs_ybs_scale                  :7 ,	// 22:16
	reserved02                         :5 ,	// reserved
	reg_fbs_bs_exp_s_wei               :2 ;	// 29:28
}PE_M19_HDR_LG_SDR2HDR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005c14L HDR_SDR2HDR_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_00                :8 ,	// 7:0
	reg_fbs_yy_lut_y_00                :8 ,	// 15:8
	reg_fbs_yy_lut_x_01                :8 ,	// 23:16
	reg_fbs_yy_lut_y_01                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005c18L HDR_SDR2HDR_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_02                :8 ,	// 7:0
	reg_fbs_yy_lut_y_02                :8 ,	// 15:8
	reg_fbs_yy_lut_x_03                :8 ,	// 23:16
	reg_fbs_yy_lut_y_03                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005c1cL HDR_SDR2HDR_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_04                :8 ,	// 7:0
	reg_fbs_yy_lut_y_04                :8 ,	// 15:8
	reg_fbs_yy_lut_x_05                :8 ,	// 23:16
	reg_fbs_yy_lut_y_05                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005c20L HDR_SDR2HDR_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_06                :8 ,	// 7:0
	reg_fbs_yy_lut_y_06                :8 ,	// 15:8
	reg_fbs_yy_lut_x_07                :8 ,	// 23:16
	reg_fbs_yy_lut_y_07                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005c24L HDR_SDR2HDR_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_08                :8 ,	// 7:0
	reg_fbs_yy_lut_y_08                :8 ,	// 15:8
	reg_fbs_yy_lut_x_09                :8 ,	// 23:16
	reg_fbs_yy_lut_y_09                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005c28L HDR_SDR2HDR_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_10                :8 ,	// 7:0
	reg_fbs_yy_lut_y_10                :8 ,	// 15:8
	reg_fbs_yy_lut_x_11                :8 ,	// 23:16
	reg_fbs_yy_lut_y_11                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9005c2cL HDR_SDR2HDR_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_12                :8 ,	// 7:0
	reg_fbs_yy_lut_y_12                :8 ,	// 15:8
	reg_fbs_yy_lut_x_13                :8 ,	// 23:16
	reg_fbs_yy_lut_y_13                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9005c30L HDR_SDR2HDR_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_yy_lut_x_14                :8 ,	// 7:0
	reg_fbs_yy_lut_y_14                :8 ,	// 15:8
	reg_fbs_yy_lut_x_15                :8 ,	// 23:16
	reg_fbs_yy_lut_y_15                :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9005c34L HDR_SDR2HDR_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_dcp_tv                     :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_bs_cnt                     :12;	// 27:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9005c38L HDR_SDR2HDR_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_0                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_0                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9005c3cL HDR_SDR2HDR_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_1                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_1                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9005c40L HDR_SDR2HDR_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_2                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_2                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9005c44L HDR_SDR2HDR_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_3                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_3                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9005c48L HDR_SDR2HDR_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_4                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_4                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9005c4cL HDR_SDR2HDR_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_5                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_5                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9005c50L HDR_SDR2HDR_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_6                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_6                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9005c54L HDR_SDR2HDR_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_7                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_7                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc9005c58L HDR_SDR2HDR_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_8                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_8                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc9005c5cL HDR_SDR2HDR_CTRL_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_9                 :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_9                 :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9005c60L HDR_SDR2HDR_CTRL_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_10                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_10                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc9005c64L HDR_SDR2HDR_CTRL_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_11                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_11                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc9005c68L HDR_SDR2HDR_CTRL_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_12                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_12                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc9005c6cL HDR_SDR2HDR_CTRL_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_13                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_13                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc9005c70L HDR_SDR2HDR_CTRL_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_14                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_14                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc9005c74L HDR_SDR2HDR_CTRL_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_brm_br_lut_x_15                :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_brm_br_lut_y_15                :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc9005c78L HDR_SDR2HDR_CTRL_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_cnt0                    :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_fbs_bs_cnt1                    :12;	// 27:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc9005c7cL HDR_SDR2HDR_CTRL_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_cnt2                    :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_fbs_bs_cnt3                    :12;	// 27:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc9005c80L HDR_SDR2HDR_CTRL_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_cnt4                    :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_fbs_bs_cnt5                    :12;	// 27:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc9005c84L HDR_SDR2HDR_CTRL_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_cnt6                    :12;	// 11:0
}PE_M19_HDR_LG_SDR2HDR_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc9005c88L HDR_SDR2HDR_CTRL_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_y_ofs_0             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_fbs_bs_exp_y_ofs_1             :10;	// 25:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9005c8cL HDR_SDR2HDR_CTRL_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_y_ofs_2             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_fbs_bs_exp_y_ofs_3             :10;	// 25:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9005c90L HDR_SDR2HDR_CTRL_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_y_ofs_4             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_fbs_bs_exp_y_ofs_5             :10;	// 25:16
}PE_M19_HDR_LG_SDR2HDR_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc9005c94L HDR_SDR2HDR_CTRL_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_y_ofs_6             :10;	// 9:0
}PE_M19_HDR_LG_SDR2HDR_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9005c98L HDR_SDR2HDR_CTRL_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_s_ofs_0             :8 ,	// 7:0
	reg_fbs_bs_exp_s_ofs_1             :8 ,	// 15:8
	reg_fbs_bs_exp_s_ofs_2             :8 ,	// 23:16
	reg_fbs_bs_exp_s_ofs_3             :8 ;	// 31:24
}PE_M19_HDR_LG_SDR2HDR_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9005c9cL HDR_SDR2HDR_CTRL_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bs_exp_s_ofs_4             :8 ,	// 7:0
	reg_fbs_bs_exp_s_ofs_5             :8 ,	// 15:8
	reg_fbs_bs_exp_s_ofs_6             :8 ,	// 23:16
	reserved01                         :4 ,	// reserved
	reg_brm_exp_wei                    :4 ;	// 31:28
}PE_M19_HDR_LG_SDR2HDR_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9005ca0L HDR_SDR2HDR_CTRL_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cc_en                              :1 ;	// 0:0
}PE_M19_HDR_LG_SDR2HDR_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc9005ca4L SDR2HDR_HIST_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_bin_mode                      :2 ,	// 1:0
	histogram_mode                     :2 ,	// 3:2
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved01                         :7 ,	// reserved
	window_inout_sel                   :1 ,	// 16
	reserved02                         :6 ,	// reserved
	hist_clear                         :1 ,	// 23
	hist_brm_th                        :8 ;	// 31:24
}PE_M19_SDR2HDR_HIST_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005ca8L SDR2HDR_HIST_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_SDR2HDR_HIST_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005cacL SDR2HDR_HIST_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_SDR2HDR_HIST_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005cb0L SDR2HDR_HIST_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_SDR2HDR_HIST_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005cb4L SDR2HDR_HIST_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_SDR2HDR_HIST_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005cb8L SDR2HDR_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :7 ,	// 6:0
	reserved01                         :5 ,	// reserved
	hif_hist_ai                        :1 ,	// 12
	reserved02                         :2 ,	// reserved
	hif_hist_enable                    :1 ,	// 15
	hif_status_address                 :3 ,	// 18:16
	reserved03                         :9 ,	// reserved
	hif_status_ai                      :1 ,	// 28
	hif_mask                           :1 ;	// 29
}PE_M19_SDR2HDR_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005cbcL SDR2HDR_HIST_IA_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status0                       :23;	// 22:0
}PE_M19_SDR2HDR_HIST_IA_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9005cc0L SDR2HDR_HIST_IA_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_v_min                         :16,	// 15:0
	hist_v_max                         :16;	// 31:16
}PE_M19_SDR2HDR_HIST_IA_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9005cc4L SDR2HDR_FBSLUT_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	luminance_lut0_enable              :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	window01_enable                    :1 ,	// 4 
	window0_enable                     :1 ,	// 5 
	window1_enable                     :1 ,	// 6 
	window_acquire                     :1 ,	// 7 
	window_mode_enable                 :1 ,	// 8 
	reserved02                         :7 ,	// reserved
	window_inout_sel                   :1 ;	// 16
}PE_M19_SDR2HDR_FBSLUT_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005cc8L SDR2HDR_FBSLUT_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :16,	// 15:0
	win_w0_y0                          :16;	// 31:16
}PE_M19_SDR2HDR_FBSLUT_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005cccL SDR2HDR_FBSLUT_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :16,	// 15:0
	win_w0_y1                          :16;	// 31:16
}PE_M19_SDR2HDR_FBSLUT_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005cd0L SDR2HDR_FBSLUT_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :16,	// 15:0
	win_w1_y0                          :16;	// 31:16
}PE_M19_SDR2HDR_FBSLUT_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005cd4L SDR2HDR_FBSLUT_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :16,	// 15:0
	win_w1_y1                          :16;	// 31:16
}PE_M19_SDR2HDR_FBSLUT_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005cd8L SDR2HDR_FBSLUT_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut1_wdata_y_33rd             :16,	// 15:0
	hif_llut0_wdata_x_33rd             :16;	// 31:16
}PE_M19_SDR2HDR_FBSLUT_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005cdcL SDR2HDR_FBSLUT_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_address                  :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	hif_llut0_load                     :1 ,	// 8 
	reserved02                         :2 ,	// reserved
	hif_llut0_manual_load_en           :1 ,	// 11
	hif_llut0_ai                       :1 ,	// 12
	hif_llut0_write_x                  :1 ,	// 13
	hif_llut0_read_x                   :1 ,	// 14
	hif_llut0_enable                   :1 ;	// 15
}PE_M19_SDR2HDR_FBSLUT_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9005ce0L HDR_FBS_LUT_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_llut0_wdata_y                  :16,	// 15:0
	hif_llut0_wdata_x                  :16;	// 31:16
}PE_M19_HDR_LG_FBS_LUT_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9005d00L HDR_SDR2HDR_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_st_max_luma                    :10,	// 9:0
	reserved01                         :6 ,	// reserved
	dcp_out_mean                       :10;	// 25:16
}PE_M19_HDR_LG_SDR2HDR_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005d04L HDR_SDR2HDR_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fbs_bb_yy                      :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_cdt_sdt                        :8 ;	// 23:16
}PE_M19_HDR_LG_SDR2HDR_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005d08L HDR_SDR2HDR_STAT_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt0                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005d0cL HDR_SDR2HDR_STAT_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt1                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005d10L HDR_SDR2HDR_STAT_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt2                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005d14L HDR_SDR2HDR_STAT_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt3                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005d18L HDR_SDR2HDR_STAT_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt4                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005d1cL HDR_SDR2HDR_STAT_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt5                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005d20L HDR_SDR2HDR_STAT_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt6                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005d24L HDR_SDR2HDR_STAT_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_bs_cnt7                        :23;	// 22:0
}PE_M19_HDR_LG_SDR2HDR_STAT_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005d50L HDR_TCM_HDR10P_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_tcm_org_sel                      :1 ;	// 0:0
}PE_M19_HDR_LG_TCM_HDR10P_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005d54L HDR_TCM_SLUT0_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x0;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005d58L HDR_TCM_SLUT0_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x1;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005d5cL HDR_TCM_SLUT0_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x2;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005d60L HDR_TCM_SLUT0_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x3;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005d64L HDR_TCM_SLUT0_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x4;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005d68L HDR_TCM_SLUT0_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x5;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005d6cL HDR_TCM_SLUT0_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x6;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005d70L HDR_TCM_SLUT0_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_x7;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT0_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005d74L HDR_TCM_SLUT0_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_y0                         :8 ,	// 7:0
	r_slut0_y1                         :8 ,	// 15:8
	r_slut0_y2                         :8 ,	// 23:16
	r_slut0_y3                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT0_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005d78L HDR_TCM_SLUT0_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut0_y4                         :8 ,	// 7:0
	r_slut0_y5                         :8 ,	// 15:8
	r_slut0_y6                         :8 ,	// 23:16
	r_slut0_y7                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT0_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005d7cL HDR_TCM_SLUT1_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x0;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005d80L HDR_TCM_SLUT1_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x1;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005d84L HDR_TCM_SLUT1_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x2;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005d88L HDR_TCM_SLUT1_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x3;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005d8cL HDR_TCM_SLUT1_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x4;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005d90L HDR_TCM_SLUT1_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x5;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005d94L HDR_TCM_SLUT1_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x6;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005d98L HDR_TCM_SLUT1_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_x7;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT1_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005d9cL HDR_TCM_SLUT1_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_y0                         :8 ,	// 7:0
	r_slut1_y1                         :8 ,	// 15:8
	r_slut1_y2                         :8 ,	// 23:16
	r_slut1_y3                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT1_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005da0L HDR_TCM_SLUT1_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut1_y4                         :8 ,	// 7:0
	r_slut1_y5                         :8 ,	// 15:8
	r_slut1_y6                         :8 ,	// 23:16
	r_slut1_y7                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT1_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005da4L HDR_TCM_SLUT2_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x0;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005da8L HDR_TCM_SLUT2_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x1;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005dacL HDR_TCM_SLUT2_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x2;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005db0L HDR_TCM_SLUT2_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x3;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005db4L HDR_TCM_SLUT2_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x4;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005db8L HDR_TCM_SLUT2_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x5;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005dbcL HDR_TCM_SLUT2_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x6;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005dc0L HDR_TCM_SLUT2_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_x7;	// 31:00
}PE_M19_HDR_LG_TCM_SLUT2_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005dc4L HDR_TCM_SLUT2_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_y0                         :8 ,	// 7:0
	r_slut2_y1                         :8 ,	// 15:8
	r_slut2_y2                         :8 ,	// 23:16
	r_slut2_y3                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT2_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005dc8L HDR_TCM_SLUT2_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_slut2_y4                         :8 ,	// 7:0
	r_slut2_y5                         :8 ,	// 15:8
	r_slut2_y6                         :8 ,	// 23:16
	r_slut2_y7                         :8 ;	// 31:24
}PE_M19_HDR_LG_TCM_SLUT2_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005dccL HDR_SAT_MAP_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tm1_dither_en                      :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	tm1_dither_random_freeze_en        :1 ,	// 2 
	tm1_demo_pattern_enable            :1 ,	// 3 
	tm1_bit_mode                       :2 ,	// 5:4
	reserved02                         :1 ,	// reserved
	tm1_gamma_en                       :1 ,	// 7 
	reserved03                         :8 ,	// reserved
	tm2_dither_en                      :1 ,	// 16
	reserved04                         :1 ,	// reserved
	tm2_dither_random_freeze_en        :1 ,	// 18
	tm2_demo_pattern_enable            :1 ,	// 19
	tm2_bit_mode                       :2 ,	// 21:20
	reserved05                         :1 ,	// reserved
	tm2_gamma_en                       :1 ,	// 23
	window_0_saturation_gain_enable    :1 ,	// 24
	window_1_saturation_gain_enable    :1 ,	// 25
	window_2_saturation_gain_enable    :1 ,	// 26
	reserved06                         :1 ,	// reserved
	reg_win01_blend_en                 :1 ,	// 28
	reg_win012_blend_en                :1 ,	// 29
	reg_win01_alpha_view_en            :1 ,	// 30
	reg_win012_alpha_view_en           :1 ;	// 31
}PE_M19_HDR_LG_SAT_MAP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005dd0L HDR_SAT_MAP_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm0_m2020_coef13               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm0_m2020_coef22               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005dd4L HDR_SAT_MAP_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm0_m2020_coef23               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm0_m2020_coef32               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005dd8L HDR_SAT_MAP_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm1_m2020_coef13               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm1_m2020_coef22               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005ddcL HDR_SAT_MAP_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm1_m2020_coef23               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm1_m2020_coef32               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005de0L HDR_SAT_MAP_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm2_m2020_coef13               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm2_m2020_coef22               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005de4L HDR_SAT_MAP_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tm2_m2020_coef23               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	reg_tm2_m2020_coef32               :15;	// 30:16
}PE_M19_HDR_LG_SAT_MAP_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005e00L HDR_ELLIPSE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w1_y0                  :16,	// 15:0
	reg_ellipse_w1_x0                  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005e04L HDR_ELLIPSE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w1_y1                  :16,	// 15:0
	reg_ellipse_w1_x1                  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005e08L HDR_ELLIPSE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w2_y0                  :16,	// 15:0
	reg_ellipse_w2_x0                  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005e0cL HDR_ELLIPSE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w2_y1                  :16,	// 15:0
	reg_ellipse_w2_x1                  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005e10L HDR_ELLIPSE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w1_center_y            :16,	// 15:0
	reg_ellipse_w1_center_x            :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005e14L HDR_ELLIPSE_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_axis_internal          :16,	// 15:0
	reg_ellipse_w1_rotation_angle      :8 ,	// 23:16
	reg_ellipse_w1_mode                :1 ;	// 24
}PE_M19_HDR_LG_ELLIPSE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005e18L HDR_ELLIPSE_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w1_axis_ext_semiminor  :16,	// 15:0
	reg_ellipse_w1_axis_ext_semimajor  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005e1cL HDR_ELLIPSE_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w2_center_y            :16,	// 15:0
	reg_ellipse_w2_center_x            :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005e20L HDR_ELLIPSE_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_axis_internal          :16,	// 15:0
	reg_ellipse_w2_rotation_angle      :8 ,	// 23:16
	reg_ellipse_w2_mode                :1 ;	// 24
}PE_M19_HDR_LG_ELLIPSE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005e24L HDR_ELLIPSE_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_w2_axis_ext_semiminor  :16,	// 15:0
	reg_ellipse_w2_axis_ext_semimajor  :16;	// 31:16
}PE_M19_HDR_LG_ELLIPSE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9005e30L HDR_CSC_TM1_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc_tm1_en                     :1 ;	// 0 
}PE_M19_HDR_LG_CSC_TM1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005e34L HDR_CSC_TM1_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_coef1                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm1_coef0                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005e38L HDR_CSC_TM1_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_coef3                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm1_coef2                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005e3cL HDR_CSC_TM1_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_coef5                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm1_coef4                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005e40L HDR_CSC_TM1_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_coef7                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm1_coef6                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005e44L HDR_CSC_TM1_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_csc_tm1_coef8                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005e48L HDR_CSC_TM1_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_ofst1                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm1_ofst0                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005e4cL HDR_CSC_TM1_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_ofst3                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm1_ofst2                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005e50L HDR_CSC_TM1_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm1_ofst5                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm1_ofst4                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM1_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005e54L HDR_CSC_TM2_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc_tm2_en                     :1 ;	// 0 
}PE_M19_HDR_LG_CSC_TM2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005e58L HDR_CSC_TM2_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_coef1                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm2_coef0                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005e5cL HDR_CSC_TM2_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_coef3                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm2_coef2                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005e60L HDR_CSC_TM2_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_coef5                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm2_coef4                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005e64L HDR_CSC_TM2_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_coef7                    :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc_tm2_coef6                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005e68L HDR_CSC_TM2_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_csc_tm2_coef8                    :15;	// 30:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005e6cL HDR_CSC_TM2_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_ofst1                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm2_ofst0                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005e70L HDR_CSC_TM2_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_ofst3                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm2_ofst2                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005e74L HDR_CSC_TM2_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc_tm2_ofst5                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc_tm2_ofst4                    :11;	// 26:16
}PE_M19_HDR_LG_CSC_TM2_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9005e80L HDR_CSC4_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc4th_en                      :1 ;	// 0 
}PE_M19_HDR_LG_CSC4_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9005e84L HDR_CSC4_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_coef1                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc4th_coef0                     :15;	// 30:16
}PE_M19_HDR_LG_CSC4_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9005e88L HDR_CSC4_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_coef3                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc4th_coef2                     :15;	// 30:16
}PE_M19_HDR_LG_CSC4_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9005e8cL HDR_CSC4_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_coef5                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc4th_coef4                     :15;	// 30:16
}PE_M19_HDR_LG_CSC4_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9005e90L HDR_CSC4_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_coef7                     :15,	// 14:0
	reserved01                         :1 ,	// reserved
	r_csc4th_coef6                     :15;	// 30:16
}PE_M19_HDR_LG_CSC4_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9005e94L HDR_CSC4_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	r_csc4th_coef8                     :15;	// 30:16
}PE_M19_HDR_LG_CSC4_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9005e98L HDR_CSC4_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_ofst1                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc4th_ofst0                     :11;	// 26:16
}PE_M19_HDR_LG_CSC4_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9005e9cL HDR_CSC4_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_ofst3                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc4th_ofst2                     :11;	// 26:16
}PE_M19_HDR_LG_CSC4_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9005ea0L HDR_CSC4_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_csc4th_ofst5                     :11,	// 10:0
	reserved01                         :5 ,	// reserved
	r_csc4th_ofst4                     :11;	// 26:16
}PE_M19_HDR_LG_CSC4_CTRL_08_T;


typedef struct
{ 
	PE_M19_HDR_LG_TOP_CTRL_00_T                     hdr_top_ctrl_00;	//0x0000
	PE_M19_HDR_LG_TOP_CTRL_01_T                     hdr_top_ctrl_01;	//0x0004
	PE_M19_HDR_LG_TOP_CTRL_02_T                     hdr_top_ctrl_02;	//0x0008
	PE_M19_HDR_LG_TOP_CTRL_03_T                     hdr_top_ctrl_03;	//0x000C
	PE_M19_HDR_LG_TOP_CTRL_04_T                     hdr_top_ctrl_04;	//0x0010
	PE_M19_HDR_LG_TOP_CTRL_05_T                     hdr_top_ctrl_05;	//0x0014
	PE_M19_HDR_LG_TOP_CTRL_06_T                     hdr_top_ctrl_06;	//0x0018
	PE_M19_HDR_LG_TOP_CTRL_07_T                     hdr_top_ctrl_07;	//0x001C
	UINT32                                            reserved8[12];	//0x20-0x4c
	PE_M19_HDR_LG_CSC1_CTRL_00_T                    hdr_csc1_ctrl_00;	//0x0050
	PE_M19_HDR_LG_CSC1_CTRL_01_T                    hdr_csc1_ctrl_01;	//0x0054
	PE_M19_HDR_LG_CSC1_CTRL_02_T                    hdr_csc1_ctrl_02;	//0x0058
	PE_M19_HDR_LG_CSC1_CTRL_03_T                    hdr_csc1_ctrl_03;	//0x005C
	PE_M19_HDR_LG_CSC1_CTRL_04_T                    hdr_csc1_ctrl_04;	//0x0060
	PE_M19_HDR_LG_CSC1_CTRL_05_T                    hdr_csc1_ctrl_05;	//0x0064
	PE_M19_HDR_LG_CSC1_CTRL_06_T                    hdr_csc1_ctrl_06;	//0x0068
	PE_M19_HDR_LG_CSC1_CTRL_07_T                    hdr_csc1_ctrl_07;	//0x006C
	PE_M19_HDR_LG_CSC1_CTRL_08_T                    hdr_csc1_ctrl_08;	//0x0070
	PE_M19_HDR_LG_CSC1_CTRL_09_T                    hdr_csc1_ctrl_09;	//0x0074
	PE_M19_HDR_LG_CSC1_ERR_CNT_T                    hdr_csc1_err_cnt;	//0x0078
	UINT32                                            reserved19[5];	//0x7c-0x8c
	PE_M19_HDR_LG_EOTF_IA_CTRL_T                    hdr_eotf_ia_ctrl;	//0x0090
	PE_M19_HDR_LG_EOTF_IA_DATA_T                    hdr_eotf_ia_data;	//0x0094
	PE_M19_HDR_LG_OETF_IA_CTRL_T                    hdr_oetf_ia_ctrl;	//0x0098
	PE_M19_HDR_LG_OETF_IA_DATA_T                    hdr_oetf_ia_data;	//0x009C
	PE_M19_HDR_LG_PCC_CTRL_00_T                     hdr_pcc_ctrl_00;	//0x00A0
	PE_M19_HDR_LG_PCC_CTRL_01_T                     hdr_pcc_ctrl_01;	//0x00A4
	PE_M19_HDR_LG_PCC_CTRL_02_T                     hdr_pcc_ctrl_02;	//0x00A8
	PE_M19_HDR_LG_PCC_CTRL_03_T                     hdr_pcc_ctrl_03;	//0x00AC
	PE_M19_HDR_LG_PCC_CTRL_04_T                     hdr_pcc_ctrl_04;	//0x00B0
	PE_M19_HDR_LG_PCC_CTRL_05_T                     hdr_pcc_ctrl_05;	//0x00B4
	UINT32                                            reserved29[6];	//0xb8-0xcc
	PE_M19_HDR_LG_HUE_SAT_CTRL_T                    hdr_hue_sat_ctrl;	//0x00D0
	PE_M19_HDR_LG_HUE_SAT_ALPHA_CTRL_T              hdr_hue_sat_alpha_ctrl;	//0x00D4
	UINT32                                            reserved31[2];	//0xd8-0xdc
	PE_M19_HDR_LG_TCM_PREP_00_T                     hdr_tcm_prep_00;	//0x00E0
	PE_M19_HDR_LG_TCM_PREP_01_T                     hdr_tcm_prep_01;	//0x00E4
	UINT32                                            reserved33[42];	//0xe8-0x18c
	PE_M19_HDR_LG_CLUT_CTRL_00_T                    hdr_clut_ctrl_00;	//0x0190
	PE_M19_HDR_LG_CLUT_IA_CTRL_T                    hdr_clut_ia_ctrl;	//0x0194
	PE_M19_HDR_LG_CLUT_IA_DATA_T                    hdr_clut_ia_data;	//0x0198
	PE_M19_HDR_LG_PLUT_CTRL_00_T                    hdr_plut_ctrl_00;	//0x019C
	PE_M19_HDR_LG_PLUT_IA_CTRL_T                    hdr_plut_ia_ctrl;	//0x01A0
	PE_M19_HDR_LG_PLUT_IA_DATA_T                    hdr_plut_ia_data;	//0x01A4
	PE_M19_HDR_LG_SLUT_CTRL_00_T                    hdr_slut_ctrl_00;	//0x01A8
	PE_M19_HDR_LG_SLUT_IA_CTRL_T                    hdr_slut_ia_ctrl;	//0x01AC
	PE_M19_HDR_LG_SLUT_IA_DATA_T                    hdr_slut_ia_data;	//0x01B0
	PE_M19_HDR_LG_ILUT_CTRL_00_T                    hdr_ilut_ctrl_00;	//0x01B4
	PE_M19_HDR_LG_ILUT_IA_CTRL_T                    hdr_ilut_ia_ctrl;	//0x01B8
	PE_M19_HDR_LG_ILUT_IA_DATA_T                    hdr_ilut_ia_data;	//0x01BC
	PE_M19_HDR_LG_DLUT_CTRL_00_T                    hdr_dlut_ctrl_00;	//0x01C0
	PE_M19_HDR_LG_DLUT_CTRL_01_T                    hdr_dlut_ctrl_01;	//0x01C4
	PE_M19_HDR_LG_DLUT_CTRL_02_T                    hdr_dlut_ctrl_02;	//0x01C8
	PE_M19_HDR_LG_DLUT_IA_CTRL_T                    hdr_dlut_ia_ctrl;	//0x01CC
	PE_M19_HDR_LG_DLUT_IA_DATA_T                    hdr_dlut_ia_data;	//0x01D0
	PE_M19_HDR_LG_TC_CTRL_00_T                      hdr_tc_ctrl_00;	//0x01D4
	PE_M19_HDR_LG_TC_CTRL_01_T                      hdr_tc_ctrl_01;	//0x01D8
	PE_M19_HDR_LG_TC_CTRL_02_T                      hdr_tc_ctrl_02;	//0x01DC
	PE_M19_HDR_LG_TC_CTRL_03_T                      hdr_tc_ctrl_03;	//0x01E0
	PE_M19_HDR_LG_TC_CTRL_04_T                      hdr_tc_ctrl_04;	//0x01E4
	UINT32                                            reserved55[18];	//0x1e8-0x22c
	PE_M19_HDR_LG_HIST_CTRL_00_T                    hdr_hist_ctrl_00;	//0x0230
	PE_M19_HDR_LG_HIST_CTRL_01_T                    hdr_hist_ctrl_01;	//0x0234
	PE_M19_HDR_LG_HIST_CTRL_02_T                    hdr_hist_ctrl_02;	//0x0238
	PE_M19_HDR_LG_HIST_CTRL_03_T                    hdr_hist_ctrl_03;	//0x023C
	PE_M19_HDR_LG_HIST_CTRL_04_T                    hdr_hist_ctrl_04;	//0x0240
	PE_M19_HDR_LG_HIST_IA_CTRL_T                    hdr_hist_ia_ctrl;	//0x0244
	PE_M19_HDR_LG_HIST_IA_DATA1_T                   hdr_hist_ia_data1;	//0x0248
	PE_M19_HDR_LG_HIST_IA_DATA2_T                   hdr_hist_ia_data2;	//0x024C
	PE_M19_HDR_LG_LLUT0_CTRL_00_T                   hdr_llut0_ctrl_00;	//0x0250
	PE_M19_HDR_LG_LLUT0_CTRL_01_T                   hdr_llut0_ctrl_01;	//0x0254
	PE_M19_HDR_LG_LLUT0_CTRL_02_T                   hdr_llut0_ctrl_02;	//0x0258
	PE_M19_HDR_LG_LLUT0_CTRL_03_T                   hdr_llut0_ctrl_03;	//0x025C
	PE_M19_HDR_LG_LLUT0_CTRL_04_T                   hdr_llut0_ctrl_04;	//0x0260
	PE_M19_HDR_LG_LLUT0_CTRL_05_T                   hdr_llut0_ctrl_05;	//0x0264
	PE_M19_HDR_LG_LLUT0_CTRL_06_T                   hdr_llut0_ctrl_06;	//0x0268
	UINT32                                            reserved70;	//0x26c
	PE_M19_HDR_LG_LLUT0_IA_CTRL_T                   hdr_llut0_ia_ctrl;	//0x0270
	PE_M19_HDR_LG_LLUT0_IA_DATA_T                   hdr_llut0_ia_data;	//0x0274
	UINT32                                            reserved72[2];	//0x278-0x27c
	PE_M19_HDR_LG_LLUT1_CTRL_00_T                   hdr_llut1_ctrl_00;	//0x0280
	PE_M19_HDR_LG_LLUT1_CTRL_01_T                   hdr_llut1_ctrl_01;	//0x0284
	PE_M19_HDR_LG_LLUT1_CTRL_02_T                   hdr_llut1_ctrl_02;	//0x0288
	PE_M19_HDR_LG_LLUT1_CTRL_03_T                   hdr_llut1_ctrl_03;	//0x028C
	PE_M19_HDR_LG_LLUT1_CTRL_04_T                   hdr_llut1_ctrl_04;	//0x0290
	PE_M19_HDR_LG_LLUT1_CTRL_05_T                   hdr_llut1_ctrl_05;	//0x0294
	PE_M19_HDR_LG_LLUT1_CTRL_06_T                   hdr_llut1_ctrl_06;	//0x0298
	UINT32                                            reserved79;	//0x29c
	PE_M19_HDR_LG_LLUT1_IA_CTRL_T                   hdr_llut1_ia_ctrl;	//0x02A0
	PE_M19_HDR_LG_LLUT1_IA_DATA_T                   hdr_llut1_ia_data;	//0x02A4
	UINT32                                            reserved81[2];	//0x2a8-0x2ac
	PE_M19_HDR_LG_LLUT2_CTRL_00_T                   hdr_llut2_ctrl_00;	//0x02B0
	PE_M19_HDR_LG_LLUT2_CTRL_01_T                   hdr_llut2_ctrl_01;	//0x02B4
	PE_M19_HDR_LG_LLUT2_CTRL_02_T                   hdr_llut2_ctrl_02;	//0x02B8
	PE_M19_HDR_LG_LLUT2_CTRL_03_T                   hdr_llut2_ctrl_03;	//0x02BC
	PE_M19_HDR_LG_LLUT2_CTRL_04_T                   hdr_llut2_ctrl_04;	//0x02C0
	PE_M19_HDR_LG_LLUT2_CTRL_05_T                   hdr_llut2_ctrl_05;	//0x02C4
	PE_M19_HDR_LG_LLUT2_CTRL_06_T                   hdr_llut2_ctrl_06;	//0x02C8
	UINT32                                            reserved88;	//0x2cc
	PE_M19_HDR_LG_LLUT2_IA_CTRL_T                   hdr_llut2_ia_ctrl;	//0x02D0
	PE_M19_HDR_LG_LLUT2_IA_DATA_T                   hdr_llut2_ia_data;	//0x02D4
	UINT32                                            reserved90[2];	//0x2d8-0x2dc
	PE_M19_HDR_LG_GAMMA045_CTRL_00_T                hdr_gamma045_ctrl_00;	//0x02E0
	UINT32                                            reserved91;	//0x2e4
	PE_M19_HDR_LG_DITHER_CTRL_00_T                  hdr_dither_ctrl_00;	//0x02E8
	PE_M19_HDR_LG_PCC32_GAIN_CTRL_T                 hdr_pcc32_gain_ctrl;	//0x02EC
	UINT32                                            reserved93[4];	//0x2f0-0x2fc
	PE_M19_HDR_LG_3DLUT_CTRL_00_T                   hdr_3dlut_ctrl_00;	//0x0300
	PE_M19_HDR_LG_3DLUT_CTRL_01_T                   hdr_3dlut_ctrl_01;	//0x0304
	PE_M19_HDR_LG_3DLUT_CTRL_02_T                   hdr_3dlut_ctrl_02;	//0x0308
	PE_M19_HDR_LG_3DLUT_CTRL_03_T                   hdr_3dlut_ctrl_03;	//0x030C
	PE_M19_HDR_LG_3DLUT_CTRL_04_T                   hdr_3dlut_ctrl_04;	//0x0310
	PE_M19_HDR_LG_3DLUT_CTRL_05_T                   hdr_3dlut_ctrl_05;	//0x0314
	PE_M19_HDR_LG_3DLUT_CTRL_06_T                   hdr_3dlut_ctrl_06;	//0x0318
	PE_M19_HDR_LG_3DLUT_CTRL_07_T                   hdr_3dlut_ctrl_07;	//0x031C
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_00_T               hdr_ygain_lut_ctrl_00;	//0x0320
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_01_T               hdr_ygain_lut_ctrl_01;	//0x0324
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_02_T               hdr_ygain_lut_ctrl_02;	//0x0328
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_03_T               hdr_ygain_lut_ctrl_03;	//0x032C
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_04_T               hdr_ygain_lut_ctrl_04;	//0x0330
	PE_M19_HDR_LG_YGAIN_LUT_CTRL_05_T               hdr_ygain_lut_ctrl_05;	//0x0334
	PE_M19_HDR_LG_YGAIN_LUT_IA_CTRL_T               hdr_ygain_lut_ia_ctrl;	//0x0338
	PE_M19_HDR_LG_YGAIN_LUT_IA_DATA_T               hdr_ygain_lut_ia_data;	//0x033C
	PE_M19_HDR_LG_RGB2Y_CTRL_00_T                   hdr_rgb2y_ctrl_00;	//0x0340
	PE_M19_HDR_LG_RGB2Y_CTRL_01_T                   hdr_rgb2y_ctrl_01;	//0x0344
	PE_M19_HDR_LG_RGB2Y_CTRL_02_T                   hdr_rgb2y_ctrl_02;	//0x0348
	PE_M19_HDR_LG_RGB2Y_CTRL_03_T                   hdr_rgb2y_ctrl_03;	//0x034C
	UINT32                                            reserved113[4];	//0x350-0x35c
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_00_T               hdr_lgain_lut_ctrl_00;	//0x0360
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_01_T               hdr_lgain_lut_ctrl_01;	//0x0364
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_02_T               hdr_lgain_lut_ctrl_02;	//0x0368
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_03_T               hdr_lgain_lut_ctrl_03;	//0x036C
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_04_T               hdr_lgain_lut_ctrl_04;	//0x0370
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_05_T               hdr_lgain_lut_ctrl_05;	//0x0374
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_06_T               hdr_lgain_lut_ctrl_06;	//0x0378
	PE_M19_HDR_LG_LGAIN_LUT_CTRL_07_T               hdr_lgain_lut_ctrl_07;	//0x037C
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_00_T               hdr_sgain_lut_ctrl_00;	//0x0380
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_01_T               hdr_sgain_lut_ctrl_01;	//0x0384
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_02_T               hdr_sgain_lut_ctrl_02;	//0x0388
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_03_T               hdr_sgain_lut_ctrl_03;	//0x038C
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_04_T               hdr_sgain_lut_ctrl_04;	//0x0390
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_05_T               hdr_sgain_lut_ctrl_05;	//0x0394
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_06_T               hdr_sgain_lut_ctrl_06;	//0x0398
	PE_M19_HDR_LG_SGAIN_LUT_CTRL_07_T               hdr_sgain_lut_ctrl_07;	//0x039C
	PE_M19_HDR_LG_RGB2Y2_CTRL_00_T                  hdr_rgb2y2_ctrl_00;	//0x03A0
	PE_M19_HDR_LG_RGB2Y2_CTRL_01_T                  hdr_rgb2y2_ctrl_01;	//0x03A4
	PE_M19_HDR_LG_RGB2Y2_CTRL_02_T                  hdr_rgb2y2_ctrl_02;	//0x03A8
	PE_M19_HDR_LG_RGB2Y2_CTRL_03_T                  hdr_rgb2y2_ctrl_03;	//0x03AC
	PE_M19_HDR_LG_CSC3_CTRL_00_T                    hdr_csc3_ctrl_00;	//0x03B0
	PE_M19_HDR_LG_CSC3_CTRL_01_T                    hdr_csc3_ctrl_01;	//0x03B4
	PE_M19_HDR_LG_CSC3_CTRL_02_T                    hdr_csc3_ctrl_02;	//0x03B8
	PE_M19_HDR_LG_CSC3_CTRL_03_T                    hdr_csc3_ctrl_03;	//0x03BC
	PE_M19_HDR_LG_CSC3_CTRL_04_T                    hdr_csc3_ctrl_04;	//0x03C0
	PE_M19_HDR_LG_CSC3_CTRL_05_T                    hdr_csc3_ctrl_05;	//0x03C4
	PE_M19_HDR_LG_CSC3_CTRL_06_T                    hdr_csc3_ctrl_06;	//0x03C8
	PE_M19_HDR_LG_CSC3_CTRL_07_T                    hdr_csc3_ctrl_07;	//0x03CC
	PE_M19_HDR_LG_CSC3_CTRL_08_T                    hdr_csc3_ctrl_08;	//0x03D0
	UINT32                                            reserved142[11];	//0x3d4-0x3fc
	PE_M19_HDR_LG_SDR2HDR_CTRL_00_T                 hdr_sdr2hdr_ctrl_00;	//0x0400
	PE_M19_HDR_LG_SDR2HDR_CTRL_01_T                 hdr_sdr2hdr_ctrl_01;	//0x0404
	PE_M19_HDR_LG_SDR2HDR_CTRL_02_T                 hdr_sdr2hdr_ctrl_02;	//0x0408
	PE_M19_HDR_LG_SDR2HDR_CTRL_03_T                 hdr_sdr2hdr_ctrl_03;	//0x040C
	PE_M19_HDR_LG_SDR2HDR_CTRL_04_T                 hdr_sdr2hdr_ctrl_04;	//0x0410
	PE_M19_HDR_LG_SDR2HDR_CTRL_05_T                 hdr_sdr2hdr_ctrl_05;	//0x0414
	PE_M19_HDR_LG_SDR2HDR_CTRL_06_T                 hdr_sdr2hdr_ctrl_06;	//0x0418
	PE_M19_HDR_LG_SDR2HDR_CTRL_07_T                 hdr_sdr2hdr_ctrl_07;	//0x041C
	PE_M19_HDR_LG_SDR2HDR_CTRL_08_T                 hdr_sdr2hdr_ctrl_08;	//0x0420
	PE_M19_HDR_LG_SDR2HDR_CTRL_09_T                 hdr_sdr2hdr_ctrl_09;	//0x0424
	PE_M19_HDR_LG_SDR2HDR_CTRL_10_T                 hdr_sdr2hdr_ctrl_10;	//0x0428
	PE_M19_HDR_LG_SDR2HDR_CTRL_11_T                 hdr_sdr2hdr_ctrl_11;	//0x042C
	PE_M19_HDR_LG_SDR2HDR_CTRL_12_T                 hdr_sdr2hdr_ctrl_12;	//0x0430
	PE_M19_HDR_LG_SDR2HDR_CTRL_13_T                 hdr_sdr2hdr_ctrl_13;	//0x0434
	PE_M19_HDR_LG_SDR2HDR_CTRL_14_T                 hdr_sdr2hdr_ctrl_14;	//0x0438
	PE_M19_HDR_LG_SDR2HDR_CTRL_15_T                 hdr_sdr2hdr_ctrl_15;	//0x043C
	PE_M19_HDR_LG_SDR2HDR_CTRL_16_T                 hdr_sdr2hdr_ctrl_16;	//0x0440
	PE_M19_HDR_LG_SDR2HDR_CTRL_17_T                 hdr_sdr2hdr_ctrl_17;	//0x0444
	PE_M19_HDR_LG_SDR2HDR_CTRL_18_T                 hdr_sdr2hdr_ctrl_18;	//0x0448
	PE_M19_HDR_LG_SDR2HDR_CTRL_19_T                 hdr_sdr2hdr_ctrl_19;	//0x044C
	PE_M19_HDR_LG_SDR2HDR_CTRL_20_T                 hdr_sdr2hdr_ctrl_20;	//0x0450
	PE_M19_HDR_LG_SDR2HDR_CTRL_21_T                 hdr_sdr2hdr_ctrl_21;	//0x0454
	PE_M19_HDR_LG_SDR2HDR_CTRL_22_T                 hdr_sdr2hdr_ctrl_22;	//0x0458
	PE_M19_HDR_LG_SDR2HDR_CTRL_23_T                 hdr_sdr2hdr_ctrl_23;	//0x045C
	PE_M19_HDR_LG_SDR2HDR_CTRL_24_T                 hdr_sdr2hdr_ctrl_24;	//0x0460
	PE_M19_HDR_LG_SDR2HDR_CTRL_25_T                 hdr_sdr2hdr_ctrl_25;	//0x0464
	PE_M19_HDR_LG_SDR2HDR_CTRL_26_T                 hdr_sdr2hdr_ctrl_26;	//0x0468
	PE_M19_HDR_LG_SDR2HDR_CTRL_27_T                 hdr_sdr2hdr_ctrl_27;	//0x046C
	PE_M19_HDR_LG_SDR2HDR_CTRL_28_T                 hdr_sdr2hdr_ctrl_28;	//0x0470
	PE_M19_HDR_LG_SDR2HDR_CTRL_29_T                 hdr_sdr2hdr_ctrl_29;	//0x0474
	PE_M19_HDR_LG_SDR2HDR_CTRL_30_T                 hdr_sdr2hdr_ctrl_30;	//0x0478
	PE_M19_HDR_LG_SDR2HDR_CTRL_31_T                 hdr_sdr2hdr_ctrl_31;	//0x047C
	PE_M19_HDR_LG_SDR2HDR_CTRL_32_T                 hdr_sdr2hdr_ctrl_32;	//0x0480
	PE_M19_HDR_LG_SDR2HDR_CTRL_33_T                 hdr_sdr2hdr_ctrl_33;	//0x0484
	PE_M19_HDR_LG_SDR2HDR_CTRL_34_T                 hdr_sdr2hdr_ctrl_34;	//0x0488
	PE_M19_HDR_LG_SDR2HDR_CTRL_35_T                 hdr_sdr2hdr_ctrl_35;	//0x048C
	PE_M19_HDR_LG_SDR2HDR_CTRL_36_T                 hdr_sdr2hdr_ctrl_36;	//0x0490
	PE_M19_HDR_LG_SDR2HDR_CTRL_37_T                 hdr_sdr2hdr_ctrl_37;	//0x0494
	PE_M19_HDR_LG_SDR2HDR_CTRL_38_T                 hdr_sdr2hdr_ctrl_38;	//0x0498
	PE_M19_HDR_LG_SDR2HDR_CTRL_39_T                 hdr_sdr2hdr_ctrl_39;	//0x049C
	PE_M19_HDR_LG_SDR2HDR_CTRL_40_T                 hdr_sdr2hdr_ctrl_40;	//0x04A0
	PE_M19_SDR2HDR_HIST_CTRL_00_T                sdr2hdr_hist_ctrl_00;	//0x04A4
	PE_M19_SDR2HDR_HIST_CTRL_01_T                sdr2hdr_hist_ctrl_01;	//0x04A8
	PE_M19_SDR2HDR_HIST_CTRL_02_T                sdr2hdr_hist_ctrl_02;	//0x04AC
	PE_M19_SDR2HDR_HIST_CTRL_03_T                sdr2hdr_hist_ctrl_03;	//0x04B0
	PE_M19_SDR2HDR_HIST_CTRL_04_T                sdr2hdr_hist_ctrl_04;	//0x04B4
	PE_M19_SDR2HDR_HIST_IA_CTRL_T                sdr2hdr_hist_ia_ctrl;	//0x04B8
	PE_M19_SDR2HDR_HIST_IA_DATA1_T               sdr2hdr_hist_ia_data1;	//0x04BC
	PE_M19_SDR2HDR_HIST_IA_DATA2_T               sdr2hdr_hist_ia_data2;	//0x04C0
	PE_M19_SDR2HDR_FBSLUT_CTRL_00_T              sdr2hdr_fbslut_ctrl_00;	//0x04C4
	PE_M19_SDR2HDR_FBSLUT_CTRL_01_T              sdr2hdr_fbslut_ctrl_01;	//0x04C8
	PE_M19_SDR2HDR_FBSLUT_CTRL_02_T              sdr2hdr_fbslut_ctrl_02;	//0x04CC
	PE_M19_SDR2HDR_FBSLUT_CTRL_03_T              sdr2hdr_fbslut_ctrl_03;	//0x04D0
	PE_M19_SDR2HDR_FBSLUT_CTRL_04_T              sdr2hdr_fbslut_ctrl_04;	//0x04D4
	PE_M19_SDR2HDR_FBSLUT_CTRL_05_T              sdr2hdr_fbslut_ctrl_05;	//0x04D8
	PE_M19_SDR2HDR_FBSLUT_IA_CTRL_T              sdr2hdr_fbslut_ia_ctrl;	//0x04DC
	PE_M19_HDR_LG_FBS_LUT_IA_DATA_T                 hdr_fbs_lut_ia_data;	//0x04E0
	UINT32                                            reserved199[7];	//0x4e4-0x4fc
	PE_M19_HDR_LG_SDR2HDR_STAT_00_T                 hdr_sdr2hdr_stat_00;	//0x0500
	PE_M19_HDR_LG_SDR2HDR_STAT_01_T                 hdr_sdr2hdr_stat_01;	//0x0504
	PE_M19_HDR_LG_SDR2HDR_STAT_02_T                 hdr_sdr2hdr_stat_02;	//0x0508
	PE_M19_HDR_LG_SDR2HDR_STAT_03_T                 hdr_sdr2hdr_stat_03;	//0x050C
	PE_M19_HDR_LG_SDR2HDR_STAT_04_T                 hdr_sdr2hdr_stat_04;	//0x0510
	PE_M19_HDR_LG_SDR2HDR_STAT_05_T                 hdr_sdr2hdr_stat_05;	//0x0514
	PE_M19_HDR_LG_SDR2HDR_STAT_06_T                 hdr_sdr2hdr_stat_06;	//0x0518
	PE_M19_HDR_LG_SDR2HDR_STAT_07_T                 hdr_sdr2hdr_stat_07;	//0x051C
	PE_M19_HDR_LG_SDR2HDR_STAT_08_T                 hdr_sdr2hdr_stat_08;	//0x0520
	PE_M19_HDR_LG_SDR2HDR_STAT_09_T                 hdr_sdr2hdr_stat_09;	//0x0524
	UINT32                                            reserved209[10];	//0x528-0x54c
	PE_M19_HDR_LG_TCM_HDR10P_CTRL_01_T              hdr_tcm_hdr10p_ctrl_01;	//0x0550
	PE_M19_HDR_LG_TCM_SLUT0_00_T                    hdr_tcm_slut0_00;	//0x0554
	PE_M19_HDR_LG_TCM_SLUT0_01_T                    hdr_tcm_slut0_01;	//0x0558
	PE_M19_HDR_LG_TCM_SLUT0_02_T                    hdr_tcm_slut0_02;	//0x055C
	PE_M19_HDR_LG_TCM_SLUT0_03_T                    hdr_tcm_slut0_03;	//0x0560
	PE_M19_HDR_LG_TCM_SLUT0_04_T                    hdr_tcm_slut0_04;	//0x0564
	PE_M19_HDR_LG_TCM_SLUT0_05_T                    hdr_tcm_slut0_05;	//0x0568
	PE_M19_HDR_LG_TCM_SLUT0_06_T                    hdr_tcm_slut0_06;	//0x056C
	PE_M19_HDR_LG_TCM_SLUT0_07_T                    hdr_tcm_slut0_07;	//0x0570
	PE_M19_HDR_LG_TCM_SLUT0_08_T                    hdr_tcm_slut0_08;	//0x0574
	PE_M19_HDR_LG_TCM_SLUT0_09_T                    hdr_tcm_slut0_09;	//0x0578
	PE_M19_HDR_LG_TCM_SLUT1_00_T                    hdr_tcm_slut1_00;	//0x057C
	PE_M19_HDR_LG_TCM_SLUT1_01_T                    hdr_tcm_slut1_01;	//0x0580
	PE_M19_HDR_LG_TCM_SLUT1_02_T                    hdr_tcm_slut1_02;	//0x0584
	PE_M19_HDR_LG_TCM_SLUT1_03_T                    hdr_tcm_slut1_03;	//0x0588
	PE_M19_HDR_LG_TCM_SLUT1_04_T                    hdr_tcm_slut1_04;	//0x058C
	PE_M19_HDR_LG_TCM_SLUT1_05_T                    hdr_tcm_slut1_05;	//0x0590
	PE_M19_HDR_LG_TCM_SLUT1_06_T                    hdr_tcm_slut1_06;	//0x0594
	PE_M19_HDR_LG_TCM_SLUT1_07_T                    hdr_tcm_slut1_07;	//0x0598
	PE_M19_HDR_LG_TCM_SLUT1_08_T                    hdr_tcm_slut1_08;	//0x059C
	PE_M19_HDR_LG_TCM_SLUT1_09_T                    hdr_tcm_slut1_09;	//0x05A0
	PE_M19_HDR_LG_TCM_SLUT2_00_T                    hdr_tcm_slut2_00;	//0x05A4
	PE_M19_HDR_LG_TCM_SLUT2_01_T                    hdr_tcm_slut2_01;	//0x05A8
	PE_M19_HDR_LG_TCM_SLUT2_02_T                    hdr_tcm_slut2_02;	//0x05AC
	PE_M19_HDR_LG_TCM_SLUT2_03_T                    hdr_tcm_slut2_03;	//0x05B0
	PE_M19_HDR_LG_TCM_SLUT2_04_T                    hdr_tcm_slut2_04;	//0x05B4
	PE_M19_HDR_LG_TCM_SLUT2_05_T                    hdr_tcm_slut2_05;	//0x05B8
	PE_M19_HDR_LG_TCM_SLUT2_06_T                    hdr_tcm_slut2_06;	//0x05BC
	PE_M19_HDR_LG_TCM_SLUT2_07_T                    hdr_tcm_slut2_07;	//0x05C0
	PE_M19_HDR_LG_TCM_SLUT2_08_T                    hdr_tcm_slut2_08;	//0x05C4
	PE_M19_HDR_LG_TCM_SLUT2_09_T                    hdr_tcm_slut2_09;	//0x05C8
	PE_M19_HDR_LG_SAT_MAP_CTRL_00_T                 hdr_sat_map_ctrl_00;	//0x05CC
	PE_M19_HDR_LG_SAT_MAP_CTRL_01_T                 hdr_sat_map_ctrl_01;	//0x05D0
	PE_M19_HDR_LG_SAT_MAP_CTRL_02_T                 hdr_sat_map_ctrl_02;	//0x05D4
	PE_M19_HDR_LG_SAT_MAP_CTRL_03_T                 hdr_sat_map_ctrl_03;	//0x05D8
	PE_M19_HDR_LG_SAT_MAP_CTRL_04_T                 hdr_sat_map_ctrl_04;	//0x05DC
	PE_M19_HDR_LG_SAT_MAP_CTRL_05_T                 hdr_sat_map_ctrl_05;	//0x05E0
	PE_M19_HDR_LG_SAT_MAP_CTRL_06_T                 hdr_sat_map_ctrl_06;	//0x05E4
	UINT32                                            reserved247[6];	//0x5e8-0x5fc
	PE_M19_HDR_LG_ELLIPSE_CTRL_00_T                 hdr_ellipse_ctrl_00;	//0x0600
	PE_M19_HDR_LG_ELLIPSE_CTRL_01_T                 hdr_ellipse_ctrl_01;	//0x0604
	PE_M19_HDR_LG_ELLIPSE_CTRL_02_T                 hdr_ellipse_ctrl_02;	//0x0608
	PE_M19_HDR_LG_ELLIPSE_CTRL_03_T                 hdr_ellipse_ctrl_03;	//0x060C
	PE_M19_HDR_LG_ELLIPSE_CTRL_04_T                 hdr_ellipse_ctrl_04;	//0x0610
	PE_M19_HDR_LG_ELLIPSE_CTRL_05_T                 hdr_ellipse_ctrl_05;	//0x0614
	PE_M19_HDR_LG_ELLIPSE_CTRL_06_T                 hdr_ellipse_ctrl_06;	//0x0618
	PE_M19_HDR_LG_ELLIPSE_CTRL_07_T                 hdr_ellipse_ctrl_07;	//0x061C
	PE_M19_HDR_LG_ELLIPSE_CTRL_08_T                 hdr_ellipse_ctrl_08;	//0x0620
	PE_M19_HDR_LG_ELLIPSE_CTRL_09_T                 hdr_ellipse_ctrl_09;	//0x0624
	UINT32                                            reserved257[2];	//0x628-0x62c
	PE_M19_HDR_LG_CSC_TM1_CTRL_00_T                 hdr_csc_tm1_ctrl_00;	//0x0630
	PE_M19_HDR_LG_CSC_TM1_CTRL_01_T                 hdr_csc_tm1_ctrl_01;	//0x0634
	PE_M19_HDR_LG_CSC_TM1_CTRL_02_T                 hdr_csc_tm1_ctrl_02;	//0x0638
	PE_M19_HDR_LG_CSC_TM1_CTRL_03_T                 hdr_csc_tm1_ctrl_03;	//0x063C
	PE_M19_HDR_LG_CSC_TM1_CTRL_04_T                 hdr_csc_tm1_ctrl_04;	//0x0640
	PE_M19_HDR_LG_CSC_TM1_CTRL_05_T                 hdr_csc_tm1_ctrl_05;	//0x0644
	PE_M19_HDR_LG_CSC_TM1_CTRL_06_T                 hdr_csc_tm1_ctrl_06;	//0x0648
	PE_M19_HDR_LG_CSC_TM1_CTRL_07_T                 hdr_csc_tm1_ctrl_07;	//0x064C
	PE_M19_HDR_LG_CSC_TM1_CTRL_08_T                 hdr_csc_tm1_ctrl_08;	//0x0650
	PE_M19_HDR_LG_CSC_TM2_CTRL_00_T                 hdr_csc_tm2_ctrl_00;	//0x0654
	PE_M19_HDR_LG_CSC_TM2_CTRL_01_T                 hdr_csc_tm2_ctrl_01;	//0x0658
	PE_M19_HDR_LG_CSC_TM2_CTRL_02_T                 hdr_csc_tm2_ctrl_02;	//0x065C
	PE_M19_HDR_LG_CSC_TM2_CTRL_03_T                 hdr_csc_tm2_ctrl_03;	//0x0660
	PE_M19_HDR_LG_CSC_TM2_CTRL_04_T                 hdr_csc_tm2_ctrl_04;	//0x0664
	PE_M19_HDR_LG_CSC_TM2_CTRL_05_T                 hdr_csc_tm2_ctrl_05;	//0x0668
	PE_M19_HDR_LG_CSC_TM2_CTRL_06_T                 hdr_csc_tm2_ctrl_06;	//0x066C
	PE_M19_HDR_LG_CSC_TM2_CTRL_07_T                 hdr_csc_tm2_ctrl_07;	//0x0670
	PE_M19_HDR_LG_CSC_TM2_CTRL_08_T                 hdr_csc_tm2_ctrl_08;	//0x0674
	UINT32                                            reserved275[2];	//0x678-0x67c
	PE_M19_HDR_LG_CSC4_CTRL_00_T                    hdr_csc4_ctrl_00;	//0x0680
	PE_M19_HDR_LG_CSC4_CTRL_01_T                    hdr_csc4_ctrl_01;	//0x0684
	PE_M19_HDR_LG_CSC4_CTRL_02_T                    hdr_csc4_ctrl_02;	//0x0688
	PE_M19_HDR_LG_CSC4_CTRL_03_T                    hdr_csc4_ctrl_03;	//0x068C
	PE_M19_HDR_LG_CSC4_CTRL_04_T                    hdr_csc4_ctrl_04;	//0x0690
	PE_M19_HDR_LG_CSC4_CTRL_05_T                    hdr_csc4_ctrl_05;	//0x0694
	PE_M19_HDR_LG_CSC4_CTRL_06_T                    hdr_csc4_ctrl_06;	//0x0698
	PE_M19_HDR_LG_CSC4_CTRL_07_T                    hdr_csc4_ctrl_07;	//0x069C
	PE_M19_HDR_LG_CSC4_CTRL_08_T                    hdr_csc4_ctrl_08;	//0x06A0
}PE_HDR_LG_REG_M19_T;

#endif

