#ifndef _PE_CCO_REG_O18A0_H_
#define _PE_CCO_REG_O18A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9011000L pe1_top_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	load_time                          :1 ,	//0 
	load_enable                        :1 ,	//1 
	load_type                          :1 ;	//2 
}PE_O18_PE1_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011004L pe1_top_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	width                              :12,	//11:0
	reserved01                         :4 , //reserved
	height                             :12;	//27:16
}PE_O18_PE1_TOP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011008L pe1_top_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tpg_position                       :1 ,	//0 
	reg_pe1_cg_disable                 :1 ,	//1 
	pe1_detour                         :1 ,	//2 
	reserved01                         :2 ,	//reserved
	async_delay_mode                   :1 ,	//5 
	reserved02                         :1 ,	//reserved
	mode_3d                            :1 ,	//7 
	vdpulse_pos                        :12,	//19:8
	line_masking_mode                  :2 ,	//21:20
	reserved03                         :2 , //reserved
	master_en                          :1 ;	//24
}PE_O18_PE1_TOP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901100cL pe1_top_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcnt                               :12,	//11:0
	va_pe1_in                          :1 ,	//12
	va_pe1_out                         :1 ,	//13
	reserved01                         :2 , //reserved
	vcnt2                              :12;	//27:16
}PE_O18_PE1_TOP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011010L pe1_top_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_to_cnt                           :12;	//11:0
}PE_O18_PE1_TOP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011020L pe1_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_s_status_0                     : 8 ,  //  7: 0
	reg_s_status_1                     : 8 ,  // 15: 8
	reg_s_apl_0                        : 8 ,  // 23:16
	reg_fmd_en_0                       : 1 ,  //    24
	reg_fmd_en_1                       : 1 ,  //    25
	reg_tnr_auto_en                    : 1 ,  //    26
	cl_filter_en_stat                  : 1 ,  //    27
	clc_detection_en_stat              : 1 ,  //    28
	reg_color_filter_status            : 2 ,  // 30:29
	reg_shp_fw_en                      : 1 ;  //    31
}PE_O18_CE_PE1_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011024L pe1_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_histo_fw_en                    : 1 ,  //     0
	reg_drc_dc_mode                    : 2 ,  //  2: 1
	reg_drc_dc_bypass                  : 1 ,  //     3
	reg_drc_dc_sc_cnt                  : 4 ,  //  7: 4
	pre_121_blur_en                    : 1 ,  //     8
	pre_median_en                      : 1 ,  //     9
	tnr_sc_measure_en                  : 1 ,  //    10
	reg_is_oled                        : 1 ,  //    11
	reserved                           : 2 ,  // 13:12     reserved
	reg_hdr_effect                     : 2 ,  // 15:14
	tnr_sc_measure_th                  : 16;  // 31:16
}PE_O18_CE_PE1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011028L pe1_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_src_info                       : 6 ,  //  5: 0
	reg_src_freeze                     : 1 ;  //     6
}PE_O18_CE_PE1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901102cL pe1_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_nt_lvl                         : 8 ,  //  7: 0
	reg_s_status                       : 8 ,  // 15: 8
	reg_s_apl                          : 8 ;  // 23:16
}PE_O18_CE_PE1_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025520L PE1_FSW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	m0_y_h_12t_m_idx                   : 8 ,  //  7: 0
	m0_y_v_12t_m_idx                   : 8 ,  // 15: 8
	m0_y_h_12t_h_idx                   : 8 ,  // 23:16
	m0_y_v_12t_h_idx                   : 8 ;  // 31:24
}PE_O18_CO_PE1_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025524L PE1_FSW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	m0_y_h_08t_f_idx                   : 8 ,  //  7: 0
	m0_y_v_08t_f_idx                   : 8 ,  // 15: 8
	reserved0                          : 8 ,  // 23:16
	reserved1                          : 8 ;  // 31:24
}PE_O18_CO_PE1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025528L PE1_FSW_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	m0_c_h_12t_m_idx                   : 8 ,  //  7: 0
	m0_c_v_12t_m_idx                   : 8 ,  // 15: 8
	m0_c_h_12t_h_idx                   : 8 ,  // 23:16
	m0_c_v_12t_h_idx                   : 8 ;  // 31:24
}PE_O18_CO_PE1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902552cL PE1_FSW_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	g0_y_vh_08t_m_idx                   : 8 ,  //  7: 0
	g0_c_vh_04t_h_idx                   : 8 ,  // 15: 8
	g1_y_vh_08t_m_idx                   : 8 ,  // 23:16
	g1_c_vh_04t_h_idx                   : 8 ;  // 31:24
}PE_O18_CO_PE1_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011034L pe1_win2_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win0_en                            :1 ,	//0 
	win1_en                            :1 ,	//1 
	win01_en                           :1 ,	//2 
	reserved01                         :3 ,	//reserved
	win_outside                        :1 ,	//6 
	win_en                             :1 ,	//7 
	bdr_alpha                          :5 ,	//12:8
	bdr_wid                            :2 ,	//14:13
	bdr_en                             :1 ,	//15
	cr5                                :5 ,	//20:16
	cb5                                :5 ,	//25:21
	yy6                                :6 ;	//31:26
}PE_O18_PE1_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011038L pe1_win2_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :12,	//11:0
	reserved01                         :4 , //reserved
	win_w0_y0                          :12;	//27:16
}PE_O18_PE1_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc901103cL pe1_win2_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :12,	//11:0
	reserved01                         :4 , //reserved
	win_w0_y1                          :12;	//27:16
}PE_O18_PE1_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011040L pe1_win2_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x0                          :12,	//11:0
	reserved01                         :4 , //reserved
	win_w1_y0                          :12;	//27:16
}PE_O18_PE1_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011044L pe1_win2_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w1_x1                          :12,	//11:0
	reserved01                         :4 , //reserved
	win_w1_y1                          :12;	//27:16
}PE_O18_PE1_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011050L pe1_apl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_win_ctrl_x0                    :12,	//11:0
	reserved01                         :4 , //reserved
	apl_win_ctrl_y0                    :12;	//27:16
}PE_O18_PE1_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011054L pe1_apl_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_win_ctrl_x1                    :12,	//11:0
	reserved01                         :4 , //reserved
	apl_win_ctrl_y1                    :12;	//27:16
}PE_O18_PE1_APL_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011058L pe1_apl_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_position                       :2 ,	//1:0
	reserved01                         :6 , //reserved
	act_win_mode                       :1 ;	//8 
}PE_O18_PE1_APL_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901105cL pe1_apl_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_cb                             :10,	//9:0
	apl_yg                             :10,	//19:10
	apl_cr                             :10;	//29:20
}PE_O18_PE1_APL_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011060L pe1_apl_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	apl_cb_other_side                  :10,	//9:0
	apl_yg_other_side                  :10,	//19:10
	apl_cr_other_side                  :10;	//29:20
}PE_O18_PE1_APL_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011070L pe1_tpg_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tpg_enable                         :1 ,	//0 
	pattern_type                       :2 ,	//2:1
	reserved01                         :1 ,	//reserved
	blend_alpha                        :4 ,	//7:4
	blt_size_x                         :12,	//19:8
	blt_size_y                         :12;	//31:20
}PE_O18_PE1_TPG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011074L pe1_tpg_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	gradation_stride                   :7 ,	//6:0
	gradation_direction                :1 ,	//7 
	gradation_bar_0_en                 :1 ,	//8 
	gradation_bar_1_en                 :1 ,	//9 
	gradation_bar_2_en                 :1 ,	//10
	gradation_bar_3_en                 :1 ;	//11
}PE_O18_PE1_TPG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011078L pe1_tpg_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	patch_0_en                         :1 ,	//0 
	patch_1_en                         :1 ,	//1 
	patch_2_en                         :1 ,	//2 
	patch_3_en                         :1 ,	//3 
	patch_4_en                         :1 ,	//4 
	patch_5_en                         :1 ,	//5 
	patch_6_en                         :1 ,	//6 
	patch_7_en                         :1 ,	//7 
	patch_8_en                         :1 ,	//8 
	patch_9_en                         :1 ,	//9 
	patch_10_en                        :1 ,	//10
	patch_11_en                        :1 ,	//11
	patch_12_en                        :1 ,	//12
	patch_13_en                        :1 ,	//13
	patch_14_en                        :1 ,	//14
	patch_15_en                        :1 ;	//15
}PE_O18_PE1_TPG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901107cL pe1_tpg_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	patch_0_inout_sel                  :1 ,	//0 
	patch_1_inout_sel                  :1 ,	//1 
	patch_2_inout_sel                  :1 ,	//2 
	patch_3_inout_sel                  :1 ,	//3 
	patch_4_inout_sel                  :1 ,	//4 
	patch_5_inout_sel                  :1 ,	//5 
	patch_6_inout_sel                  :1 ,	//6 
	patch_7_inout_sel                  :1 ,	//7 
	patch_8_inout_sel                  :1 ,	//8 
	patch_9_inout_sel                  :1 ,	//9 
	patch_10_inout_sel                 :1 ,	//10
	patch_11_inout_sel                 :1 ,	//11
	patch_12_inout_sel                 :1 ,	//12
	patch_13_inout_sel                 :1 ,	//13
	patch_14_inout_sel                 :1 ,	//14
	patch_15_inout_sel                 :1 ;	//15
}PE_O18_PE1_TPG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011080L pe1_tpg_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_color_r                         :10,	//9:0
	bg_color_b                         :10,	//19:10
	bg_color_g                         :10;	//29:20
}PE_O18_PE1_TPG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011084L pe1_tpg_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tpg_indir_addr                     :7 ,	//6:0
	reserved01                         :5 , //reserved
	tpg_indir_ai_en                    :1 ;	//12
}PE_O18_PE1_TPG_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9011088L pe1_tpg_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tpg_indir_data;	//31:0
}PE_O18_PE1_TPG_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011090L pe1_vspyc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	graycolor_enable                   :1 ,	//1 
	color_only_enable                  :1 ,	//2 
	cb_info                            :1 ,	//3 
	cr_info                            :1 ,	//4 
	reserved01                         :1 ,	//reserved
	r_yc2rgb_en                        :1 ,	//6 
	reserved02                         :1 ,	//reserved
	center_position                    :8 ,	//15:8
	contrast                           :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011094L pe1_vspyc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	//reserved
	saturation                         :8 ,	//15:8
	brightness                         :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011098L pe1_vspyc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_coef1                     :15,	//14:0
	reserved01                         :1 , //reserved
	r_yc2rgb_coef0                     :15;	//30:16
}PE_O18_PE1_VSPYC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901109cL pe1_vspyc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_coef3                     :15,	//14:0
	reserved01                         :1 , //reserved
	r_yc2rgb_coef2                     :15;	//30:16
}PE_O18_PE1_VSPYC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90110a0L pe1_vspyc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_coef5                     :15,	//14:0
	reserved01                         :1 , //reserved
	r_yc2rgb_coef4                     :15;	//30:16
}PE_O18_PE1_VSPYC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90110a4L pe1_vspyc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_coef7                     :15,	//14:0
	reserved01                         :1 , //reserved
	r_yc2rgb_coef6                     :15;	//30:16
}PE_O18_PE1_VSPYC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90110a8L pe1_vspyc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16, //reserved
	r_yc2rgb_coef8                     :15;	//30:16
}PE_O18_PE1_VSPYC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90110acL pe1_vspyc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_ofst1                     :11,	//10:0
	reserved01                         :5 , //reserved
	r_yc2rgb_ofst0                     :11;	//26:16
}PE_O18_PE1_VSPYC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90110b0L pe1_vspyc_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_ofst3                     :11,	//10:0
	reserved01                         :5 , //reserved
	r_yc2rgb_ofst2                     :11;	//26:16
}PE_O18_PE1_VSPYC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90110b4L pe1_vspyc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_yc2rgb_ofst5                     :11,	//10:0
	reserved01                         :5 , //reserved
	r_yc2rgb_ofst4                     :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90110b8L pe1_vspyc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y8              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x8              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90110bcL pe1_vspyc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y7              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x7              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90110c0L pe1_vspyc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y6              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x6              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90110c4L pe1_vspyc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y5              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x5              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90110c8L pe1_vspyc_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y4              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x4              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90110ccL pe1_vspyc_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y3              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x3              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90110d0L pe1_vspyc_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y2              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x2              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90110d4L pe1_vspyc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y1              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x1              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90110d8L pe1_vspyc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_vsp_sat_gain_lut_y0              :8 ,	//7:0
	reserved01                         :8 , //reserved
	r_vsp_sat_gain_lut_x0              :10;	//25:16
}PE_O18_PE1_VSPYC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90110e0L pe1_cen_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cen_detour                         :1 ,	//0 
	reserved01                         :1 ,	//reserved
	select_hsv                         :1 ,	//2 
	select_rgb                         :1 ,	//3 
	reserved02                         :1 ,	//reserved
	vsp_sel                            :1 ,	//5 
	reserved03                         :1 ,	//reserved
	reg_cen_bypass                     :1 ,	//7 
	reg_cen_debug_mode                 :1 ,	//8 
	reserved04                         :1 ,	//reserved
	core_1st__gain_disable             :1 ,	//10
	core_2nd_gain_disable              :1 ,	//11
	reserved05                         :1 ,	//reserved
	debugging_mode_core                :2 ,	//14:13
	reserved06                         :1 ,	//reserved
	demo_mode                          :8 ,	//23:16
	reserved07                         :7 , //reserved
	win_control_mode                   :1 ;	//31
}PE_O18_PE1_CEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90110e4L pe1_cen_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	show_color_region0                 :1 ,	//0 
	show_color_region1                 :1 ,	//1 
	show_color_region2                 :1 ,	//2 
	show_color_region3                 :1 ,	//3 
	show_color_region4                 :1 ,	//4 
	show_color_region5                 :1 ,	//5 
	show_color_region6                 :1 ,	//6 
	show_color_region7                 :1 ,	//7 
	show_color_region8                 :1 ,	//8 
	show_color_region9                 :1 ,	//9 
	show_color_region10                :1 ,	//10
	show_color_region11                :1 ,	//11
	show_color_region12                :1 ,	//12
	show_color_region13                :1 ,	//13
	show_color_region14                :1 ,	//14
	show_color_region15                :1 ,	//15
	color_region_en0                   :1 ,	//16
	color_region_en1                   :1 ,	//17
	color_region_en2                   :1 ,	//18
	color_region_en3                   :1 ,	//19
	color_region_en4                   :1 ,	//20
	color_region_en5                   :1 ,	//21
	color_region_en6                   :1 ,	//22
	color_region_en7                   :1 ,	//23
	color_region_en8                   :1 ,	//24
	color_region_en9                   :1 ,	//25
	color_region_en10                  :1 ,	//26
	color_region_en11                  :1 ,	//27
	color_region_en12                  :1 ,	//28
	color_region_en13                  :1 ,	//29
	color_region_en14                  :1 ,	//30
	color_region_en15                  :1 ;	//31
}PE_O18_PE1_CEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90110e8L pe1_cen_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ihsv_sgain                         :8 ,	//7:0
	ihsv_vgain                         :8 ;	//15:8
}PE_O18_PE1_CEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90110ecL pe1_cen_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ihsv_hoffset                       :8 ,	//7:0
	ihsv_soffset                       :8 ,	//15:8
	ihsv_voffset                       :8 ;	//23:16
}PE_O18_PE1_CEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90110f0L pe1_cen_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_master_gain_cr0                :8 ,	//7:0
	reg_master_gain_cr1                :8 ,	//15:8
	reg_master_gain_cr2                :8 ,	//23:16
	reg_master_gain_cr3                :8 ;	//31:24
}PE_O18_PE1_CEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90110f4L pe1_cen_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_master_gain_cr4                :8 ,	//7:0
	reg_master_gain_cr5                :8 ,	//15:8
	reg_master_gain_cr6                :8 ,	//23:16
	reg_master_gain_cr7                :8 ;	//31:24
}PE_O18_PE1_CEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90110f8L pe1_cen_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_master_gain_cr8                :8 ,	//7:0
	reg_master_gain_cr9                :8 ,	//15:8
	reg_master_gain_cr10               :8 ,	//23:16
	reg_master_gain_cr11               :8 ;	//31:24
}PE_O18_PE1_CEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90110fcL pe1_cen_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_master_gain_cr12               :8 ,	//7:0
	reg_master_gain_cr13               :8 ,	//15:8
	reg_master_gain_cr14               :8 ,	//23:16
	reg_master_gain_cr15               :8 ;	//31:24
}PE_O18_PE1_CEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011110L pe1_cen_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_cen_address                    :8 ,	//7:0
	hif_cen_ai_sel                     :3 ,	//10:8
	reserved01                         :1 ,	//reserved
	hif_cen_ai                         :1 ,	//12
	reserved02                         :1 ,	//reserved
	hif_mem_off                        :1 ,	//14
	hif_cen_enable                     :1 ;	//15
}PE_O18_PE1_CEN_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9011114L pe1_cen_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_cen_y_wdata                    :10,	//9:0
	reserved01                         :6 , //reserved
	hif_cen_x_wdata                    :10;	//25:16
}PE_O18_PE1_CEN_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011118L pe1_cen_delta_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_cen_delta_address              :5 ,	//4:0
	reserved01                         :7 ,	//reserved
	hif_cen_delta_ai                   :1 ,	//12
	reserved02                         :2 , //reserved
	hif_cen_delta_enable               :1 ;	//15
}PE_O18_PE1_CEN_DELTA_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc901111cL pe1_cen_delta_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_cen_vr_data                    :8 ,	//7:0
	hif_cen_sb_data                    :8 ,	//15:8
	hif_cen_hg_data                    :8 ;	//23:16
}PE_O18_PE1_CEN_DELTA_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011120L pe1_dce_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dynamic_contrast_en                :1 ,	//0 
	hist_bin_mode                      :2 ,	//2:1
	hist_clear                         :1 ,	//3 
	window01_enable                    :1 ,	//4 
	window0_enable                     :1 ,	//5 
	window1_enable                     :1 ,	//6 
	window_acquire                     :1 ,	//7 
	color_region0_sel                  :1 ,	//8 
	color_region1_sel                  :1 ,	//9 
	color_region2_sel                  :1 ,	//10
	color_region3_sel                  :1 ,	//11
	color_region4_sel                  :1 ,	//12
	color_region5_sel                  :1 ,	//13
	color_region6_sel                  :1 ,	//14
	color_region7_sel                  :1 ,	//15
	color_region8_sel                  :1 ,	//16
	color_region9_sel                  :1 ,	//17
	color_region10_sel                 :1 ,	//18
	color_region11_sel                 :1 ,	//19
	color_region12_sel                 :1 ,	//20
	color_region13_sel                 :1 ,	//21
	color_region14_sel                 :1 ,	//22
	color_region15_sel                 :1 ,	//23
	dce_domain_sel                     :1 ,	//24
	reserved01                         :1 ,	//reserved
	window_mode_enable                 :1 ,	//26
	window_inout_sel                   :1 ,	//27
	histogram_mode                     :2 ;	//29:28
}PE_O18_PE1_DCE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011124L pe1_dce_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	chroma_comp_color_region_gain      :8 ,	//7:0
	reserved01                         :8 , //reserved
	color_region_gain                  :8 ;	//23:16
}PE_O18_PE1_DCE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011128L pe1_dce_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	color_region_en                    :1 ,	//0 
	color_debug_en                     :1 ,	//1 
	reserved01                         :2 ,	//reserved
	y_grad_gain                        :2 ,	//5:4
	reserved02                         :2 ,	//reserved
	cb_grad_gain                       :2 ,	//9:8
	reserved03                         :2 , //reserved
	cr_grad_gain                       :2 ;	//13:12
}PE_O18_PE1_DCE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901112cL pe1_dce_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_range_min                        :10,	//9:0
	reserved01                         :6 , //reserved
	y_range_max                        :10;	//25:16
}PE_O18_PE1_DCE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011130L pe1_dce_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cb_range_min                       :10,	//9:0
	reserved01                         :6 , //reserved
	cb_range_max                       :10;	//25:16
}PE_O18_PE1_DCE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011134L pe1_dce_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_range_min                       :10,	//9:0
	reserved01                         :6 , //reserved
	cr_range_max                       :10;	//25:16
}PE_O18_PE1_DCE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011138L pe1_dce_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dyc_address                    :5 ,	//4:0
	reserved01                         :3 ,	//reserved
	hif_dce_load                       :1 ,	//8 
	reserved02                         :3 ,	//reserved
	hif_dce_ai                         :1 ,	//12
	reserved03                         :2 , //reserved
	hif_dce_enable                     :1 ;	//15
}PE_O18_PE1_DCE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc901113cL pe1_dce_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dyc_wdata_y                    :10,	//9:0
	reserved01                         :6 , //reserved
	hif_dyc_wdata_x                    :10;	//25:16
}PE_O18_PE1_DCE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011140L pe1_dce_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dyc_wdata_y_32nd               :10,	//9:0
	reserved01                         :6 , //reserved
	hif_dyc_wdata_x_32nd               :10;	//25:16
}PE_O18_PE1_DCE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011144L pe1_dce_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 , //reserved
	dce_ktd_csc_sel                    :1 ;	//1 
}PE_O18_PE1_DCE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011148L pe1_dce_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :5 ,	//4:0
	reserved01                         :7 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 ,	//reserved
	hif_hist_enable                    :1 ,	//15
	hif_status_address                 :3 ,	//18:16
	reserved03                         :9 ,	//reserved
	hif_status_ai                      :1 ,	//28
	hif_mask                           :1 ;	//29
}PE_O18_PE1_DCE_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc901114cL pe1_dce_hist_ia_data1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status0                       :23;	//22:0
}PE_O18_PE1_DCE_HIST_IA_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9011150L pe1_dce_hist_ia_data2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status1                       :29;	//28:0
}PE_O18_PE1_DCE_HIST_IA_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9011154L pe1_dce_chr_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dce_chr_gain2                      :10,	//9:0
	reserved01                         :6 ,	//reserved
	dce_chr_gain1                      :10,	//25:16
	reserved02                         :2 , //reserved
	chroma_gain_enable                 :1 ;	//28
}PE_O18_PE1_DCE_CHR_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc9011158L pe1_dce_chr_alpha                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dce_chr_alpha2                     :10,	//9:0
	reserved01                         :6 , //reserved
	dce_chr_alpha1                     :10;	//25:16
}PE_O18_PE1_DCE_CHR_ALPHA_T;
/*-----------------------------------------------------------------------------
                             0xc9011160L pe1_dse_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dynamic_saturation_en              :1 ,	//0 
	window_mode_enable                 :1 ,	//1 
	window_inout_sel                   :1 ,	//2 
	reserved01                         :1 ,	//reserved
	window01_enable                    :1 ,	//4 
	window0_enable                     :1 ,	//5 
	window1_enable                     :1 ,	//6 
	window_acquire                     :1 ,	//7 
	color_region0_sel                  :1 ,	//8 
	color_region1_sel                  :1 ,	//9 
	color_region2_sel                  :1 ,	//10
	color_region3_sel                  :1 ,	//11
	color_region4_sel                  :1 ,	//12
	color_region5_sel                  :1 ,	//13
	color_region6_sel                  :1 ,	//14
	color_region7_sel                  :1 ,	//15
	color_region8_sel                  :1 ,	//16
	color_region9_sel                  :1 ,	//17
	color_region10_sel                 :1 ,	//18
	color_region11_sel                 :1 ,	//19
	color_region12_sel                 :1 ,	//20
	color_region13_sel                 :1 ,	//21
	color_region14_sel                 :1 ,	//22
	color_region15_sel                 :1 ;	//23
}PE_O18_PE1_DSE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011164L pe1_dse_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dse_cr_mode_sel                :1 ,	//0 
	reg_yh_cr_en                       :1 ,	//1 
	reg_yh_debug                       :1 ,	//2 
	reserved01                         :1 ,	//reserved
	r_dse_y_grad                       :2 ,	//5:4
	reserved02                         :2 ,	//reserved
	r_dse_h_grad                       :2 ,	//9:8
	reserved03                         :14, //reserved
	color_region_gain                  :8 ;	//31:24
}PE_O18_PE1_DSE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011168L pe1_dse_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dse_wdata_y_32nd               :10,	//9:0
	reserved01                         :6 , //reserved
	hif_dse_wdata_x_32nd               :10;	//25:16
}PE_O18_PE1_DSE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901116cL pe1_dse_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dse_address                    :5 ,	//4:0
	reserved01                         :3 ,	//reserved
	hif_dse_load                       :1 ,	//8 
	reserved02                         :3 ,	//reserved
	hif_dse_ai                         :1 ,	//12
	reserved03                         :2 , //reserved
	hif_dse_enable                     :1 ;	//15
}PE_O18_PE1_DSE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9011170L pe1_dse_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_dse_wdata_y                    :10,	//9:0
	reserved01                         :6 , //reserved
	hif_dse_wdata_x                    :10;	//25:16
}PE_O18_PE1_DSE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011174L pe1_dse_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_range_min                        :10,	//9:0
	reserved01                         :6 , //reserved
	y_range_max                        :10;	//25:16
}PE_O18_PE1_DSE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011178L pe1_dse_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_range_min                        :10,	//9:0
	reserved01                         :6 , //reserved
	h_range_max                        :10;	//25:16
}PE_O18_PE1_DSE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011180L pe1_cw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cw_en                              :1 ;	//0 
}PE_O18_PE1_CW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011184L pe1_cw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	user_ctrl_g_gain                   :8 ,	//7:0
	user_ctrl_b_gain                   :8 ,	//15:8
	user_ctrl_r_gain                   :8 ;	//23:16
}PE_O18_PE1_CW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011190L pe1_cw_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	color_region0_sel                  :1 ,	//0 
	color_region1_sel                  :1 ,	//1 
	color_region2_sel                  :1 ,	//2 
	color_region3_sel                  :1 ,	//3 
	color_region4_sel                  :1 ,	//4 
	color_region5_sel                  :1 ,	//5 
	color_region6_sel                  :1 ,	//6 
	color_region7_sel                  :1 ,	//7 
	color_region8_sel                  :1 ,	//8 
	color_region9_sel                  :1 ,	//9 
	color_region10_sel                 :1 ,	//10
	color_region11_sel                 :1 ,	//11
	color_region12_sel                 :1 ,	//12
	color_region13_sel                 :1 ,	//13
	color_region14_sel                 :1 ,	//14
	color_region15_sel                 :1 ,	//15
	color_region_gain                  :8 ;	//23:16
}PE_O18_PE1_CW_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011194L pe1_lblur_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	display_height                     :12,	//11:0
	reserved01                         :4 , //reserved
	display_width                      :12;	//27:16
}PE_O18_PE1_LBLUR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011198L pe1_lblur_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_block_size_v                   :7 ,	//6:0
	reserved01                         :1 ,	//reserved
	reg_block_size_h                   :7 ,	//14:8
	reserved02                         :1 ,	//reserved
	reg_block_no_v                     :6 ,	//21:16
	reserved03                         :2 ,	//reserved
	reg_block_no_h                     :6 ,	//29:24
	reserved04                         :1 , //reserved
	reg_block_info_force_en            :1 ;	//31
}PE_O18_PE1_LBLUR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc901119cL pe1_lblur_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_last_block_size_v              :7 ,	//6:0
	reserved01                         :1 , //reserved
	reg_last_block_size_h              :7 ;	//14:8
}PE_O18_PE1_LBLUR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90111a0L pe1_conv_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	conv_3d_r_en                       :1 ,	//0 
	fpacking_r_en                      :1 ,	//1 
	ffmode_r_en                        :1 ,	//2 
	load_parity_r                      :1 ,	//3 
	conv_3d_l_en                       :1 ,	//4 
	fpacking_l_en                      :1 ,	//5 
	ffmode_l_en                        :1 ,	//6 
	load_parity_l                      :1 ,	//7 
	reserved01                         :8 ,	//reserved
	start_parity_r                     :1 ,	//16
	start_parity_l                     :1 ,	//17
	reserved02                         :13, //reserved
	reg_3dconv_disable                 :1 ;	//31
}PE_O18_PE1_CONV_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90111a4L pe1_conv_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	offset_r                           :8 ,	//7:0
	reserved01                         :8 , //reserved
	offset_l                           :8 ;	//23:16
}PE_O18_PE1_CONV_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90111a8L pe1_conv_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_color_grey                      :8 ;	//7:0
}PE_O18_PE1_CONV_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90111acL pe1_conv_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_xpos                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	pxl_rep_ypos                       :12,	//27:16
	pxl_rep_in                         :1 ,	//28
	pxl_rep_out                        :1 ;	//29
}PE_O18_PE1_CONV_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90111b0L pe1_conv_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_width                      :12,	//11:0
	reserved01                         :4 , //reserved
	pxl_rep_height                     :12;	//27:16
}PE_O18_PE1_CONV_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90111b4L pe1_conv_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_CONV_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90111b8L pe1_conv_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_CONV_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90111bcL pe1_conv_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_col_fil_g_valid                :1 ,	//0 
	reg_col_fil_b_valid                :1 ,	//1 
	reg_col_fil_r_valid                :1 ,	//2 
	reg_col_fil_g_nvalid               :1 ,	//3 
	reg_col_fil_b_nvalid               :1 ,	//4 
	reg_col_fil_r_nvalid               :1 ;	//5 
}PE_O18_PE1_CONV_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90111c0L pe1_conv_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_xpos                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	pxl_rep_ypos                       :12,	//27:16
	pxl_rep_in                         :1 ,	//28
	pxl_rep_out                        :1 ;	//29
}PE_O18_PE1_CONV_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90111c4L pe1_conv_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_width                      :12,	//11:0
	reserved01                         :4 , //reserved
	pxl_rep_height                     :12;	//27:16
}PE_O18_PE1_CONV_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90111c8L pe1_conv_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_CONV_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90111ccL pe1_conv_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_CONV_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90111d0L pe1_conv_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_col_fil_g_valid                :1 ,	//0 
	reg_col_fil_b_valid                :1 ,	//1 
	reg_col_fil_r_valid                :1 ,	//2 
	reg_col_fil_g_nvalid               :1 ,	//3 
	reg_col_fil_b_nvalid               :1 ,	//4 
	reg_col_fil_r_nvalid               :1 ;	//5 
}PE_O18_PE1_CONV_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90111d4L pe1_conv_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mux3d_en                           :1 ,	//0 
	reserved01                         :3 ,	//reserved
	reg_out_mux                        :2 ,	//5:4
	start_parity                       :1 ,	//6 
	load_parity                        :1 ,	//7 
	reserved02                         :8 ,	//reserved
	alpha1_gain                        :8 ,	//23:16
	alpha0_gain                        :8 ;	//31:24
}PE_O18_PE1_CONV_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90111d8L pe1_conv_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	mux_l_window_h_en                  :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	mux_l_window_v_en                  :1 ;	//31
}PE_O18_PE1_CONV_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90111dcL pe1_conv_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_CONV_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90111e0L pe1_conv_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	mux_r_window_h_en                  :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	mux_r_window_v_en                  :1 ;	//31
}PE_O18_PE1_CONV_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90111e4L pe1_conv_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_CONV_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90111e8L pe1_conv_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_color_r                         :8 ,	//7:0
	bg_color_b                         :8 ,	//15:8
	bg_color_g                         :8 ;	//23:16
}PE_O18_PE1_CONV_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90111f0L pe1_mute_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_xpos                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	pxl_rep_ypos                       :12,	//27:16
	pxl_rep_in                         :1 ,	//28
	pxl_rep_out                        :1 ;	//29
}PE_O18_PE1_MUTE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90111f4L pe1_mute_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_width                      :12,	//11:0
	reserved01                         :4 , //reserved
	pxl_rep_height                     :12;	//27:16
}PE_O18_PE1_MUTE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90111f8L pe1_mute_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_MUTE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90111fcL pe1_mute_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_MUTE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011200L pe1_mute_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_col_fil_g_valid                :1 ,	//0 
	reg_col_fil_b_valid                :1 ,	//1 
	reg_col_fil_r_valid                :1 ,	//2 
	reg_col_fil_g_nvalid               :1 ,	//3 
	reg_col_fil_b_nvalid               :1 ,	//4 
	reg_col_fil_r_nvalid               :1 ;	//5 
}PE_O18_PE1_MUTE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011204L pe1_mute_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_xpos                       :12,	//11:0
	reserved01                         :4 ,	//reserved
	pxl_rep_ypos                       :12,	//27:16
	pxl_rep_in                         :1 ,	//28
	pxl_rep_out                        :1 ;	//29
}PE_O18_PE1_MUTE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011208L pe1_mute_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_width                      :12,	//11:0
	reserved01                         :4 , //reserved
	pxl_rep_height                     :12;	//27:16
}PE_O18_PE1_MUTE_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901120cL pe1_mute_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_MUTE_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011210L pe1_mute_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pxl_rep_value_g                    :10,	//9:0
	pxl_rep_value_b                    :10,	//19:10
	pxl_rep_value_r                    :10;	//29:20
}PE_O18_PE1_MUTE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011214L pe1_mute_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_col_fil_g_valid                :1 ,	//0 
	reg_col_fil_b_valid                :1 ,	//1 
	reg_col_fil_r_valid                :1 ,	//2 
	reg_col_fil_g_nvalid               :1 ,	//3 
	reg_col_fil_b_nvalid               :1 ,	//4 
	reg_col_fil_r_nvalid               :1 ;	//5 
}PE_O18_PE1_MUTE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011218L pe1_mute_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mux3d_en                           :1 ,	//0 
	reserved01                         :3 ,	//reserved
	reg_out_mux                        :2 ,	//5:4
	start_parity                       :1 ,	//6 
	reserved02                         :9 ,	//reserved
	alpha1_gain                        :8 ,	//23:16
	alpha0_gain                        :8 ;	//31:24
}PE_O18_PE1_MUTE_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc901121cL pe1_mute_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	mux_l_window_h_en                  :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	mux_l_window_v_en                  :1 ;	//31
}PE_O18_PE1_MUTE_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9011220L pe1_mute_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_MUTE_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9011224L pe1_mute_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	mux_r_window_h_en                  :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	mux_r_window_v_en                  :1 ;	//31
}PE_O18_PE1_MUTE_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9011228L pe1_mute_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_MUTE_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc901122cL pe1_mute_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_color_r                         :8 ,	//7:0
	bg_color_b                         :8 ,	//15:8
	bg_color_g                         :8 ;	//23:16
}PE_O18_PE1_MUTE_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9011230L pe_pcc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pcc_eotf_en                        :1 ,	//0 
	pcc_eotf_bit_extection_mode        :2 ,	//2:1
	reserved01                         :1 ,	//reserved
	reg_gamma045_en                    :1 ,	//4 
	pcc_oetf_en                        :1 ,	//5 
	pcc_oetf_output_mux                :1 ,	//6 
	reserved02                         :1 ,	//reserved
	reg_pcc_en                         :1 ,	//8 
	reserved03                         :3 ,	//reserved
	reg_dither_en                      :1 ,	//12
	reserved04                         :3 ,	//reserved
	reg_dither_temporal_en             :1 ,	//16
	reserved05                         :3 ,	//reserved
	reg_sat_lut_in_mux                 :1 ,	//20
	reg_l3d_in_mux                     :1 ,	//21
	reg_sat_blend_in_mux               :1 ;	//22
}PE_O18_PE_PCC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9011234L pe1_pcc_coef0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_coef0                      :15,	//14:0
	reserved01                         :1 , //reserved
	reg_pcc_coef1                      :15;	//30:16
}PE_O18_PE1_PCC_COEF0_T;
/*-----------------------------------------------------------------------------
                             0xc9011238L pe1_pcc_coef1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_coef2                      :15,	//14:0
	reserved01                         :1 , //reserved
	reg_pcc_coef3                      :15;	//30:16
}PE_O18_PE1_PCC_COEF1_T;
/*-----------------------------------------------------------------------------
                             0xc901123cL pe1_pcc_coef2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_coef4                      :15,	//14:0
	reserved01                         :1 , //reserved
	reg_pcc_coef5                      :15;	//30:16
}PE_O18_PE1_PCC_COEF2_T;
/*-----------------------------------------------------------------------------
                             0xc9011240L pe1_pcc_coef3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_coef6                      :15,	//14:0
	reserved01                         :1 , //reserved
	reg_pcc_coef7                      :15;	//30:16
}PE_O18_PE1_PCC_COEF3_T;
/*-----------------------------------------------------------------------------
                             0xc9011244L pe1_pcc_coef4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pcc_coef8                      :15;	//14:0
}PE_O18_PE1_PCC_COEF4_T;
/*-----------------------------------------------------------------------------
                             0xc9011248L pe1_pcc_coef5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_x3_i                       :10,	//9:0
	reserved01                         :6 , //reserved
	reg_sat_x2_i                       :10;	//25:16
}PE_O18_PE1_PCC_COEF5_T;
/*-----------------------------------------------------------------------------
                             0xc901124cL pe1_pcc_coef6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_x1_i                       :10,	//9:0
	reserved01                         :6 , //reserved
	reg_sat_x0_i                       :10;	//25:16
}PE_O18_PE1_PCC_COEF6_T;
/*-----------------------------------------------------------------------------
                             0xc9011250L pe1_pcc_coef7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_y3_i                       :8 ,	//7:0
	reg_sat_y2_i                       :8 ,	//15:8
	reg_sat_y1_i                       :8 ,	//23:16
	reg_sat_y0_i                       :8 ;	//31:24
}PE_O18_PE1_PCC_COEF7_T;
/*-----------------------------------------------------------------------------
                             0xc9011254L pe1_oetf_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	oetf_addr                          :11,	//10:0
	reserved01                         :1 ,	//reserved
	oetf_ai                            :1 ,	//12
	reserved02                         :14,	//reserved
	reg_use_own_lut_hif                :1 ,	//27
	oetf_lut_color_type                :2 ,	//29:28
	reg_oetf_en_mux                    :1 ,	//30
	reg_oetf_en_direct                 :1 ;	//31
}PE_O18_PE1_OETF_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9011258L pe1_oetf_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	oetf_lut_data_o                    :12,	//11:0
	oetf_lut_data_e                    :12;	//23:12
}PE_O18_PE1_OETF_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc901125cL pe1_eotf_wdata                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	eotf_wdata                         :15,	//14:0
	reserved01                         :1 ,	//reserved
	eotf_waddr                         :10,	//25:16
	reserved02                         :2 , //reserved
	eotf_we                            :3 ;	//30:28
}PE_O18_PE1_EOTF_WDATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011260L pe1_eotf_wdone                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	eotf_lut_wr_done                   :1 ,	//0 
	reserved01                         :3 , //reserved
	eotf_lut_wr_status                 :1 ;	//4 
}PE_O18_PE1_EOTF_WDONE_T;
/*-----------------------------------------------------------------------------
                             0xc9011264L pe1_eotf_rdata                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	eotf_rdata                         :15,	//14:0
	reserved01                         :1 ,	//reserved
	eotf_raddr                         :10,	//25:16
	reserved02                         :2 ,	//reserved
	eotf_re                            :3 ,	//30:28
	eotf_rdata_sel                     :1 ;	//31
}PE_O18_PE1_EOTF_RDATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011268L pe1_logo_l7sc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pic_rptr_man                   :2 ,	//1:0
	reserved01                         :1 ,	//reserved
	reg_pic_rptr_man_en                :1 ,	//3 
	reg_pic_wptr_man                   :2 ,	//5:4
	reserved02                         :1 ,	//reserved
	reg_pic_wptr_man_en                :1 ,	//7 
	reg_pic_data_man                   :2 ,	//9:8
	reg_pic_rptr_on                    :1 ,	//10
	reg_pic_wptr_on                    :1 ,	//11
	reg_pic_wd_man                     :4 ,	//15:12
	reg_pic_wd_man_on                  :1 ,	//16
	reg_pic_rd_lsb_man                 :2 ,	//18:17
	reg_ro_buf_wrcnt                   :10,	//28:19
	reg_ro_buf_wrsel                   :1 ,	//29
	disp_clk_cg_on                     :1 ,	//30:30
	de_clk_cg_on                       :1 ;	//31:31
}PE_O18_PE1_LOGO_L7SC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc901126cL pe1_logo_l7sc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hoffset                     :13,	//12:0
	reserved01                         :3 , //reserved
	reg_in_voffset                     :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011270L pe1_logo_l7sc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hactive                     :13,	//12:0
	reserved01                         :3 , //reserved
	reg_in_vactive                     :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011274L pe1_logo_l7sc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hsize                       :13,	//12:0
	reserved01                         :3 , //reserved
	reg_in_vsize                       :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011278L pe1_logo_l7sc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_pic_width                  :13,	//12:0
	reserved01                         :3 , //reserved
	reg_out_pic_height                 :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc901127cL pe1_logo_l7sc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_h                    :6 ,	//5:0
	reserved01                         :2 ,	//reserved
	reg_phase_off_v                    :6 ,	//13:8
	reserved02                         :17, //reserved
	reg_sampling_mode                  :1 ;	//31
}PE_O18_PE1_LOGO_L7SC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011280L pe1_logo_l7sc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_numerator_h                    :13,	//12:0
	reserved01                         :3 , //reserved
	reg_numerator_v                    :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9011284L pe1_logo_l7sc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h                  :13,	//12:0
	reserved01                         :3 , //reserved
	reg_denominator_v                  :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011288L pe1_logo_l7sc_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win0_en                            :1 ,	//0:0
	win1_en                            :1 ,	//1:1
	win01_en                           :1 ,	//2:2
	reserved01                         :3 ,	//reserved
	win_outside                        :1 ,	//6:6
	win_en                             :1 ,	//7:7
	bdr_alpha                          :5 ,	//12:8
	bdr_wid                            :2 ,	//14:13
	bdr_en                             :1 ,	//15:15
	cr5                                :5 ,	//20:16
	cb5                                :5 ,	//25:21
	yy6                                :6 ;	//31:26
}PE_O18_PE1_LOGO_L7SC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc901128cL pe1_logo_l7sc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :12,	//11:0
	reserved01                         :4 ,	//reserved
	win_w0_y0                          :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011290L pe1_logo_l7sc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :12,	//11:0
	reserved01                         :4 ,	//reserved
	win_w0_y1                          :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9011294L pe1_logo_l7sc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hoffset                    :13,	//12:0
	reserved01                         :3 , //reserved
	reg_out_voffset                    :12;	//27:16
}PE_O18_PE1_LOGO_L7SC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9011298L pe1_logo_l7sc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hactive                    :13,	//12:0
	reserved01                         :3 ,	//reserved
	reg_out_vactive                    :12,	//27:16
	reserved02                         :2 , //reserved
	logo_l7sc_out_sel                  :2 ;	//31:30
}PE_O18_PE1_LOGO_L7SC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc901129cL pe1_logo_l7sc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_logo_blend_alpha_l7_delay      :8 ,	//7:0
	reg_logo_blend_alpha_l3_delay      :8 ;	//15:8
}PE_O18_PE1_LOGO_L7SC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90112a0L pe1_lrcr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	adjust_en                          :1 ,	//1 
	protection_en                      :1 ,	//2 
	adjust_en2                         :1 ,	//3 
	reserved01                         :4 ,	//reserved
	ff_mode_en                         :1 ,	//8 
	ff_mode_parity                     :1 ,	//9 
	ll_mode_enable                     :1 ,	//10
	line_parity_select                 :1 ,	//11
	lrcr_out_mux                       :1 ,	//12
	reserved02                         :3 ,	//reserved
	reg_lrcr_gain                      :4 ,	//19:16
	reserved03                         :2 , //reserved
	hist_mode                          :2 ;	//23:22
}PE_O18_PE1_LRCR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90112a4L pe1_lrcr_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	th_max_hist                        :8 ,	//7:0
	th_valid_bins                      :8 ,	//15:8
	th1                                :8 ,	//23:16
	th0                                :8 ;	//31:24
}PE_O18_PE1_LRCR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90112a8L pe1_lrcr_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	hist_l_window_h_en                 :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	hist_l_window_v_en                 :1 ;	//31
}PE_O18_PE1_LRCR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90112acL pe1_lrcr_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_LRCR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90112b0L pe1_lrcr_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	hist_r_window_h_en                 :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	hist_r_window_v_en                 :1 ;	//31
}PE_O18_PE1_LRCR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90112b4L pe1_lrcr_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_LRCR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90112b8L pe1_lrcr_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	//11:0
	reserved01                         :3 ,	//reserved
	active_window_h_en                 :1 ,	//15
	y0                                 :12,	//27:16
	reserved02                         :3 , //reserved
	active_window_v_en                 :1 ;	//31
}PE_O18_PE1_LRCR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90112bcL pe1_lrcr_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	//11:0
	reserved01                         :4 , //reserved
	y1                                 :12;	//27:16
}PE_O18_PE1_LRCR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90112c0L g_adj_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	clock_gating_disable               :1 ,	//1 
	reserved01                         :2 ,	//reserved
	bright                             :10,	//13:4
	contrast                           :10,	//23:14
	center_position                    :8 ;	//31:24
}PE_O18_G_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90112c4L b_adj_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	clock_gating_disable               :1 ,	//1 
	reserved01                         :2 ,	//reserved
	bright                             :10,	//13:4
	contrast                           :10,	//23:14
	center_position                    :8 ;	//31:24
}PE_O18_B_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90112c8L r_adj_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	//0 
	clock_gating_disable               :1 ,	//1 
	reserved01                         :2 ,	//reserved
	bright                             :10,	//13:4
	contrast                           :10,	//23:14
	center_position                    :8 ;	//31:24
}PE_O18_R_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90112ccL hist_ctrl_mode                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bin_mode                           :2 ,	//1:0
	histo_ctrl                         :2 ,	//3:2
	reserved01                         :19,	//reserved
	histo_clear                        :1 ,	//23
	reserved02                         :7 , //reserved
	histo_disable                      :1 ;	//31
}PE_O18_HIST_CTRL_MODE_T;
/*-----------------------------------------------------------------------------
                             0xc90112d0L pe1_l_g_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_L_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112d4L pe1_l_g_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_L_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90112d8L pe1_l_b_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_L_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112dcL pe1_l_b_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_L_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90112e0L pe1_l_r_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_L_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112e4L pe1_l_r_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_L_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90112e8L pe1_r_g_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_R_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112ecL pe1_r_g_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_R_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90112f0L pe1_r_b_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_R_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112f4L pe1_r_b_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_R_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90112f8L pe1_r_r_hist_ia_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :8 ,	//7:0
	reserved01                         :4 ,	//reserved
	hif_hist_ai                        :1 ,	//12
	reserved02                         :2 , //reserved
	hif_hist_enable                    :1 ;	//15
}PE_O18_PE1_R_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90112fcL pe1_r_r_hist_ia_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status;	//31:0
}PE_O18_PE1_R_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9011300L pe1_debug_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable_debug_mode                  :1 ,	//0 
	status_enable                      :1 ,	//1 
	debug_mode                         :1 ,	//2 
	reserved01                         :17, //reserved
	show_apl                           :1 ;	//20
}PE_O18_PE1_DEBUG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011304L pe1_debug_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	yc_debug_en                        :1 ,	//0 
	force_yy_enable                    :1 ,	//1 
	force_cb_enable                    :1 ,	//2 
	force_cr_enable                    :1 ,	//3 
	yc_debug_mode_sel                  :3 ;	//6:4
}PE_O18_PE1_DEBUG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011308L pe1_debug_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	force_yy                           :10,	//9:0
	force_cb                           :10,	//19:10
	force_cr                           :10;	//29:20
}PE_O18_PE1_DEBUG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011310L pe1_bt20_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef1                        :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef0                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011314L pe1_bt20_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef3a                       :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef2                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011318L pe1_bt20_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef5a                       :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef4a                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901131cL pe1_bt20_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef7a                       :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef6a                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011320L pe1_bt20_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_ofst0                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_2x3_coef8a                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011324L pe1_bt20_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_ofst2                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_2x3_ofst1                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011328L pe1_bt20_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_ofst3                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_2x3_ofst4                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901132cL pe1_bt20_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_en                           :1 ,	//0 
	reserved01                         :3 ,	//reserved
	r_degamma_en                       :1 ,	//4 
	reserved02                         :3 ,	//reserved
	r_1x3_en                           :1 ,	//8 
	reserved03                         :7 , //reserved
	r_2x3_ofst5                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011330L pe1_bt20_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dither_en                          :1 ,	//0 
	decontour_en                       :1 ,	//1 
	dither_random_freeze_en            :1 ,	//2 
	demo_pattern_enable                :1 ,	//3 
	bit_mode                           :2 ,	//5:4
	reserved01                         :2 ,	//reserved
	decontour_gain_r                   :8 ,	//15:8
	decontour_gain_g                   :8 ,	//23:16
	decontour_gain_b                   :8 ;	//31:24
}PE_O18_PE1_BT20_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011334L pe1_bt20_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef3b                       :15,	//14:0
	reserved01                         :1 , //reserved
	reg_csc_cb_th                      :10;	//25:16
}PE_O18_PE1_BT20_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011338L pe1_bt20_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef5b                       :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef4b                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc901133cL pe1_bt20_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_2x3_coef7b                       :15,	//14:0
	reserved01                         :1 , //reserved
	r_2x3_coef6b                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9011340L pe1_bt20_ctrl_0c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_csc_cr_th                      :10,	//9:0
	reserved01                         :6 , //reserved
	r_2x3_coef8b                       :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9011344L pe1_bt20_ctrl_0d                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_coef1                        :15,	//14:0
	reserved01                         :1 , //reserved
	r_1x3_coef0                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9011348L pe1_bt20_ctrl_0e                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_coef3                        :15,	//14:0
	reserved01                         :1 , //reserved
	r_1x3_coef2                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc901134cL pe1_bt20_ctrl_0f                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_coef5                        :15,	//14:0
	reserved01                         :1 , //reserved
	r_1x3_coef4                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9011350L pe1_bt20_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_coef7                        :15,	//14:0
	reserved01                         :1 , //reserved
	r_1x3_coef6                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9011354L pe1_bt20_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16, //reserved
	r_1x3_coef8                        :15;	//30:16
}PE_O18_PE1_BT20_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9011358L pe1_bt20_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_ofst1                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_1x3_ofst0                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc901135cL pe1_bt20_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_ofst3                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_1x3_ofst2                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9011360L pe1_bt20_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_ofst5                        :11,	//10:0
	reserved01                         :5 , //reserved
	r_1x3_ofst4                        :11;	//26:16
}PE_O18_PE1_BT20_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9011364L pe1_bt20_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_dbg_en                       :1 ,	//0 
	reserved01                         :3 ,	//reserved
	r_1x3_dbg_ugy                      :4 ,	//7:4
	r_1x3_dbg_ucb                      :4 ,	//11:8
	r_1x3_dbg_ucr                      :4 ,	//15:12
	r_1x3_dbg_ogy                      :4 ,	//19:16
	r_1x3_dbg_ocb                      :4 ,	//23:20
	r_1x3_dbg_obr                      :4 ;	//27:24
}PE_O18_PE1_BT20_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9011368L pe1_bt20_ctrl_stat                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_1x3_over_count                   :16,	//15:0
	r_1x3_under_count                  :16;	//31:16
}PE_O18_PE1_BT20_CTRL_STAT_T;
/*-----------------------------------------------------------------------------
                             0xc9011370L pe1_logo_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_logo_blend_en                  :1 ,	//0 
	reserved01                         :3 ,	//reserved
	reg_logo_blend_l7_en               :1 ,	//4 
	reserved02                         :3 ,	//reserved
	reg_logo_blend_l3_en               :1 ,	//8 
	reserved03                         :3 ,	//reserved
	reg_logo_debug_sel                 :4 ,	//15:12
	reg_region_gain_en                 :1 ,	//16
	reserved04                         :7 , //reserved
	reg_bound_proc_en                  :1 ;	//24
}PE_O18_PE1_LOGO_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011374L pe1_logo_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7_gain_drop                   :8 ,	//7:0
	reg_l3_gain_drop                   :8 ,	//15:8
	reg_l7_gain_contrast               :8 ,	//23:16
	reg_l3_gain_contrast               :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011378L pe1_logo_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	//reserved
	bound_proc_logocheck               :1 ,	//1 
	bound_proc_gain                    :8 ,	//9:2
	bound_proc_range_x                 :11,	//20:10
	bound_proc_range_y                 :11;	//31:21
}PE_O18_PE1_LOGO_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901137cL pe1_logo_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	boundary_position_x0               :12,	//11:0
	reserved01                         :4 , //reserved
	boundary_position_x1               :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011380L pe1_logo_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	boundary_position_y0               :12,	//11:0
	reserved01                         :4 , //reserved
	boundary_position_y1               :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011384L pe1_logo_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_bnd_gain                :8 ,	//7:0
	reg_region_bnd_x0                  :12,	//19:8
	reg_region_bnd_x1                  :12;	//31:20
}PE_O18_PE1_LOGO_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011388L pe1_logo_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_x1             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_x2             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901138cL pe1_logo_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_x3             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_x4             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011390L pe1_logo_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_x5             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_x6             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011394L pe1_logo_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_x7             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_x8             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011398L pe1_logo_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_y1             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_y2             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901139cL pe1_logo_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_y3             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_y4             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90113a0L pe1_logo_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_position_y5             :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_position_y6             :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90113a4L pe1_logo_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_11                 :8 ,	//7:0
	reg_region_gain_21                 :8 ,	//15:8
	reg_region_gain_31                 :8 ,	//23:16
	reg_region_gain_41                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90113a8L pe1_logo_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_51                 :8 ,	//7:0
	reg_region_gain_61                 :8 ,	//15:8
	reg_region_gain_71                 :8 ,	//23:16
	reg_region_gain_81                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90113acL pe1_logo_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_12                 :8 ,	//7:0
	reg_region_gain_22                 :8 ,	//15:8
	reg_region_gain_32                 :8 ,	//23:16
	reg_region_gain_42                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90113b0L pe1_logo_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_52                 :8 ,	//7:0
	reg_region_gain_62                 :8 ,	//15:8
	reg_region_gain_72                 :8 ,	//23:16
	reg_region_gain_82                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90113b4L pe1_logo_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_13                 :8 ,	//7:0
	reg_region_gain_23                 :8 ,	//15:8
	reg_region_gain_33                 :8 ,	//23:16
	reg_region_gain_43                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90113b8L pe1_logo_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_53                 :8 ,	//7:0
	reg_region_gain_63                 :8 ,	//15:8
	reg_region_gain_73                 :8 ,	//23:16
	reg_region_gain_83                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90113bcL pe1_logo_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_14                 :8 ,	//7:0
	reg_region_gain_24                 :8 ,	//15:8
	reg_region_gain_34                 :8 ,	//23:16
	reg_region_gain_44                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90113c0L pe1_logo_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_54                 :8 ,	//7:0
	reg_region_gain_64                 :8 ,	//15:8
	reg_region_gain_74                 :8 ,	//23:16
	reg_region_gain_84                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90113c4L pe1_logo_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_15                 :8 ,	//7:0
	reg_region_gain_25                 :8 ,	//15:8
	reg_region_gain_35                 :8 ,	//23:16
	reg_region_gain_45                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90113c8L pe1_logo_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_55                 :8 ,	//7:0
	reg_region_gain_65                 :8 ,	//15:8
	reg_region_gain_75                 :8 ,	//23:16
	reg_region_gain_85                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90113ccL pe1_logo_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_16                 :8 ,	//7:0
	reg_region_gain_26                 :8 ,	//15:8
	reg_region_gain_36                 :8 ,	//23:16
	reg_region_gain_46                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90113d0L pe1_logo_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_gain_56                 :8 ,	//7:0
	reg_region_gain_66                 :8 ,	//15:8
	reg_region_gain_76                 :8 ,	//23:16
	reg_region_gain_86                 :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90113d4L pe1_logo_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_x3_i                       :10,	//9:0
	reserved01                         :6 , //reserved
	reg_sat_x2_i                       :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90113d8L pe1_logo_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_x1_i                       :10,	//9:0
	reserved01                         :6 , //reserved
	reg_sat_x0_i                       :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90113dcL pe1_logo_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sat_y3_i                       :8 ,	//7:0
	reg_sat_y2_i                       :8 ,	//15:8
	reg_sat_y1_i                       :8 ,	//23:16
	reg_sat_y0_i                       :8 ;	//31:24
}PE_O18_PE1_LOGO_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90113e0L pe1_logo_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_x7_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_x6_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90113e4L pe1_logo_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_x5_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_x4_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90113e8L pe1_logo_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_x3_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_x2_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90113ecL pe1_logo_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_x1_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_x0_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90113f0L pe1_logo_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_y7_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_y6_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90113f4L pe1_logo_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_y5_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_y4_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90113f8L pe1_logo_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_y3_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_y2_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90113fcL pe1_logo_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l7drop_y1_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l7drop_y0_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9011400L pe1_logo_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_x7_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_x6_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc9011404L pe1_logo_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_x5_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_x4_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9011408L pe1_logo_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_x3_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_x2_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc901140cL pe1_logo_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_x1_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_x0_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9011410L pe1_logo_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_y7_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_y6_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc9011414L pe1_logo_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_y5_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_y4_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc9011418L pe1_logo_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_y3_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_y2_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc901141cL pe1_logo_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l3drop_y1_i                    :10,	//9:0
	reserved01                         :6 , //reserved
	reg_l3drop_y0_i                    :10;	//25:16
}PE_O18_PE1_LOGO_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc9011420L pe1_logo_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ibuf_logo_gain_vcnt                :9 ;	//8:0
}PE_O18_PE1_LOGO_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011424L pe1_logo_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	current_out_line                   :12,	//11:0
	reserved01                         :4 , //reserved
	current_in_line                    :12;	//27:16
}PE_O18_PE1_LOGO_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011428L pe1_logo_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_region_bnd_y0                  :12,	//11:0
	reserved01                         :4 , //reserved
	reg_region_bnd_y1                  :12;	//27:16
}PE_O18_PE1_LOGO_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc9011430L pe_dse_y_region_pt0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt0_y                 :8 ,	//7:0
	reg_y_region_pt0_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9011434L pe_dse_y_region_pt1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt1_y                 :8 ,	//7:0
	reg_y_region_pt1_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9011438L pe_dse_y_region_pt2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt2_y                 :8 ,	//7:0
	reg_y_region_pt2_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc901143cL pe_dse_y_region_pt3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt3_y                 :8 ,	//7:0
	reg_y_region_pt3_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9011440L pe_dse_y_region_pt4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt4_y                 :8 ,	//7:0
	reg_y_region_pt4_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9011444L pe_dse_y_region_pt5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt5_y                 :8 ,	//7:0
	reg_y_region_pt5_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9011448L pe_dse_y_region_pt6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt6_y                 :8 ,	//7:0
	reg_y_region_pt6_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc901144cL pe_dse_y_region_pt7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_region_pt7_y                 :8 ,	//7:0
	reg_y_region_pt7_x                 :10;	//17:8
}PE_O18_PE_DSE_Y_REGION_PT7_T;
/*-----------------------------------------------------------------------------
                             0xc9011450L pe_dse_h_region_pt0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt0_y                 :8 ,	//7:0
	reg_h_region_pt0_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9011454L pe_dse_h_region_pt1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt1_y                 :8 ,	//7:0
	reg_h_region_pt1_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9011458L pe_dse_h_region_pt2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt2_y                 :8 ,	//7:0
	reg_h_region_pt2_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc901145cL pe_dse_h_region_pt3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt3_y                 :8 ,	//7:0
	reg_h_region_pt3_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9011460L pe_dse_h_region_pt4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt4_y                 :8 ,	//7:0
	reg_h_region_pt4_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9011464L pe_dse_h_region_pt5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt5_y                 :8 ,	//7:0
	reg_h_region_pt5_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9011468L pe_dse_h_region_pt6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt6_y                 :8 ,	//7:0
	reg_h_region_pt6_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc901146cL pe_dse_h_region_pt7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_region_pt7_y                 :8 ,	//7:0
	reg_h_region_pt7_x                 :10;	//17:8
}PE_O18_PE_DSE_H_REGION_PT7_T;
/*-----------------------------------------------------------------------------
                             0xc9011470L pe1_drc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_en                         :1 ,	//0 
	reg_drc_cg_disable                 :1 ,	//1 
	reserved01                         :2 ,	//reserved
	reg_drc_shp_apl_sel                :1 ,	//4 
	reserved02                         :3 ,	//reserved
	reg_drc_rgb_sel                    :2 ,	//9:8
	reserved03                         :2 ,	//reserved
	reg_drc_gm_mode                    :3 ,	//14:12
	reserved04                         :1 ,	//reserved
	reg_drc_lk_blf_apf                 :1 ,	//16
	reserved05                         :3 ,	//reserved
	reg_mode_2ch                       :1 ,	//20
	reserved06                         :7 ,	//reserved
	reg_dbg_disp_blf                   :1 ,	//28
	reg_dbg_disp_lcont                 :1 ,	//29
	reg_dbg_disp_reflect               :1 ;	//30
}PE_O18_PE1_DRC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9011474L pe1_drc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_rw_sel                  :1 ,	//0 
	reserved01                         :3 ,	//reserved
	reg_drc_gm_op_sel                  :1 ,	//4 
	reserved02                         :11,	//reserved
	reg_drc_gm_forced_sel              :1 ,	//16
	reg_drc_gm_protected_sel           :1 ;	//17
}PE_O18_PE1_DRC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011478L pe1_drc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_bnh                        :7 ,	//6:0
	reserved01                         :9 , //reserved
	reg_drc_bnv                        :6 ;	//21:16
}PE_O18_PE1_DRC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901147cL pe1_drc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_bsh                        :9 ,	//8:0
	reserved01                         :7 , //reserved
	reg_drc_bsv                        :9 ;	//24:16
}PE_O18_PE1_DRC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011480L pe1_drc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_apl2                    :10,	//9:0
	reg_drc_gm_apl1                    :10,	//19:10
	reg_drc_gm_apl0                    :10;	//29:20
}PE_O18_PE1_DRC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9011484L pe1_drc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_apl5                    :10,	//9:0
	reg_drc_gm_apl4                    :10,	//19:10
	reg_drc_gm_apl3                    :10;	//29:20
}PE_O18_PE1_DRC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011488L pe1_drc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_blf_wei_cen                :8 ,	//7:0
	reserved01                         :8 , //reserved
	reg_drc_apl_iir                    :7 ;	//22:16
}PE_O18_PE1_DRC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901148cL pe1_drc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_shp_clip_n                 :12,	//11:0
	reserved01                         :4 , //reserved
	reg_drc_shp_clip_p                 :12;	//27:16
}PE_O18_PE1_DRC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011490L pe1_drc_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_gn                     :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_th                     :10;	//25:16
}PE_O18_PE1_DRC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9011494L pe1_drc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_adj_l                  :8 ,	//7:0
	reserved01                         :8 , //reserved
	reg_drc_apl_adj_h                  :8 ;	//23:16
}PE_O18_PE1_DRC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011498L pe1_drc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_x2_p                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_x1_p                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901149cL pe1_drc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_x4_p                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_x3_p                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90114a0L pe1_drc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y1_p                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y0_p                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90114a4L pe1_drc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y3_p                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y2_p                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90114a8L pe1_drc_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y5_p                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y4_p                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90114acL pe1_drc_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_x2_n                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_x1_n                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90114b0L pe1_drc_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_x4_n                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_x3_n                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90114b4L pe1_drc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y1_n                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y0_n                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90114b8L pe1_drc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y3_n                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y2_n                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90114bcL pe1_drc_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_apl_y5_n                   :10,	//9:0
	reserved01                         :6 , //reserved
	reg_drc_apl_y4_n                   :10;	//25:16
}PE_O18_PE1_DRC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90114c0L pe1_drc_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_lut_addr_clr               :1 ,	//0 
	reserved01                         :3 ,	//reserved
	reg_drc_hfc_rd_sel                 :1 ,	//4 
	reserved02                         :3 , //reserved
	reg_drc_vfc_rd_sel                 :1 ;	//8 
}PE_O18_PE1_DRC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90114c4L pe1_drc_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_lk_blf_hfc_data            :10;	//9:0
}PE_O18_PE1_DRC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90114c8L pe1_drc_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_lk_blf_vfc_data            :10;	//9:0
}PE_O18_PE1_DRC_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90114ccL pe1_drc_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_hfc_rdata                  :10;	//9:0
}PE_O18_PE1_DRC_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90114d0L pe1_drc_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_vfc_rdata                  :10;	//9:0
}PE_O18_PE1_DRC_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90114d4L pe1_drc_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_blf_wei_wdata              :10;	//9:0
}PE_O18_PE1_DRC_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90114d8L pe1_drc_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_blf_wei_rdata              :10;	//9:0
}PE_O18_PE1_DRC_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90114dcL pe1_drc_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_wdata                   :30;	//29:0
}PE_O18_PE1_DRC_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90114e0L pe1_drc_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_rdata                   :30;	//29:0
}PE_O18_PE1_DRC_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90114e4L pe1_drc_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_wdata                   :30;	//29:0
}PE_O18_PE1_DRC_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90114e8L pe1_drc_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_rdata                   :30;	//29:0
}PE_O18_PE1_DRC_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90114ecL pe1_drc_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_hpf_wei_wdata              :10;	//9:0
}PE_O18_PE1_DRC_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90114f0L pe1_drc_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_hpf_wei_rdata              :10;	//9:0
}PE_O18_PE1_DRC_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90114f4L pe1_drc_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_bl_apl_raddr_h             :7 ,	//6:0
	reserved01                         :9 , //reserved
	reg_drc_bl_apl_raddr_v             :6 ;	//21:16
}PE_O18_PE1_DRC_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90114f8L pe1_drc_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_bl_apl_rdata               :10;	//9:0
}PE_O18_PE1_DRC_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90114fcL pe1_drc_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_drc_gm_rw_sel                  :1 ,	//0 
	reserved01                         :3 , //reserved
	reg_drc_gm_op_sel                  :1 ;	//4 
}PE_O18_PE1_DRC_CTRL_35_T;


/*-----------------------------------------------------------------------------
                             0xc9011768L pe1_logo_l3sc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mif_r_logo_gain_line_inc           :2 ,	// 1:0
	mif_r_logo_gain_pf_flag_en         :1 ,	// 2:2
	mif_r_logo_gain_manual_en          :1 ,	// 3:3
	mif_r_logo_gain_en                 :1 ,	// 4:4
	mif_r_logo_vreverse                :1 ,	// 5:5
	reserved01                         :2 ,	// reserved
	logo_l3sc_out_sel                  :2 ,	// 9:8
	reserved02                         :6 ,	// reserved
	mif_r_logo_gain_voffset            :9 ,	// 24:16
	reserved03                         :5 ,	// reserved
	disp_clk_cg_on                     :1 ,	// 30:30
	de_clk_cg_on                       :1 ;	// 31:31
}PE_O18_PE1_LOGO_L3SC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc901176cL pe1_logo_l3sc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hoffset                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_in_voffset                     :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9011770L pe1_logo_l3sc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hactive                     :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_in_vactive                     :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9011774L pe1_logo_l3sc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_in_hsize                       :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_in_vsize                       :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9011778L pe1_logo_l3sc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_pic_width                  :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_out_pic_height                 :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc901177cL pe1_logo_l3sc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_phase_off_h                    :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_phase_off_v                    :6 ,	// 13:8
	reserved02                         :17, // reserved
	reg_sampling_mode                  :1 ;	// 31
}PE_O18_PE1_LOGO_L3SC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9011780L pe1_logo_l3sc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_numerator_h                    :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_numerator_v                    :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9011784L pe1_logo_l3sc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denominator_h                  :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_denominator_v                  :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9011788L pe1_logo_l3sc_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win0_en                            :1 ,	// 0:0
	win1_en                            :1 ,	// 1:1
	win01_en                           :1 ,	// 2:2
	reserved01                         :3 ,	// reserved
	win_outside                        :1 ,	// 6:6
	win_en                             :1 ,	// 7:7
	bdr_alpha                          :5 ,	// 12:8
	bdr_wid                            :2 ,	// 14:13
	bdr_en                             :1 ,	// 15:15
	cr5                                :5 ,	// 20:16
	cb5                                :5 ,	// 25:21
	yy6                                :6 ;	// 31:26
}PE_O18_PE1_LOGO_L3SC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc901178cL pe1_logo_l3sc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x0                          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	win_w0_y0                          :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9011790L pe1_logo_l3sc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_w0_x1                          :12,	// 11:0
	reserved01                         :4 ,	// reserved
	win_w0_y1                          :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9011794L pe1_logo_l3sc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hoffset                    :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_out_voffset                    :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9011798L pe1_logo_l3sc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_out_hactive                    :13,	// 12:0
	reserved01                         :3 , // reserved
	reg_out_vactive                    :12;	// 27:16
}PE_O18_PE1_LOGO_L3SC_CTRL_12_T;
typedef struct
{ 
	PE_O18_PE1_TOP_CTRL_00_T                          pe1_top_ctrl_00;	//0x0000
	PE_O18_PE1_TOP_CTRL_01_T                          pe1_top_ctrl_01;	//0x0004
	PE_O18_PE1_TOP_CTRL_02_T                          pe1_top_ctrl_02;	//0x0008
	PE_O18_PE1_TOP_CTRL_03_T                          pe1_top_ctrl_03;	//0x000C
	PE_O18_PE1_TOP_CTRL_04_T                          pe1_top_ctrl_04;	//0x0010
	UINT32                                            reserved5[3];	//0x14-0x1c
	PE_O18_CE_PE1_FSW_CTRL_00_T                          pe1_fsw_ctrl_00;	//0x0020
	PE_O18_CE_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_01;	//0x0024
	PE_O18_CE_PE1_FSW_CTRL_02_T                          pe1_fsw_ctrl_02;	//0x0028
	PE_O18_CE_PE1_FSW_CTRL_03_T                          pe1_fsw_ctrl_03;	//0x002C
	UINT32                                            reserved9;	//0x30
	PE_O18_PE1_WIN2_CTRL_00_T                         pe1_win2_ctrl_00;	//0x0034
	PE_O18_PE1_WIN2_CTRL_01_T                         pe1_win2_ctrl_01;	//0x0038
	PE_O18_PE1_WIN2_CTRL_02_T                         pe1_win2_ctrl_02;	//0x003C
	PE_O18_PE1_WIN2_CTRL_03_T                         pe1_win2_ctrl_03;	//0x0040
	PE_O18_PE1_WIN2_CTRL_04_T                         pe1_win2_ctrl_04;	//0x0044
	UINT32                                            reserved14[2];	//0x48-0x4c
	PE_O18_PE1_APL_CTRL_00_T                          pe1_apl_ctrl_00;	//0x0050
	PE_O18_PE1_APL_CTRL_01_T                          pe1_apl_ctrl_01;	//0x0054
	PE_O18_PE1_APL_CTRL_02_T                          pe1_apl_ctrl_02;	//0x0058
	PE_O18_PE1_APL_STAT_00_T                          pe1_apl_stat_00;	//0x005C
	PE_O18_PE1_APL_STAT_01_T                          pe1_apl_stat_01;	//0x0060
	UINT32                                            reserved19[3];	//0x64-0x6c
	PE_O18_PE1_TPG_CTRL_00_T                          pe1_tpg_ctrl_00;	//0x0070
	PE_O18_PE1_TPG_CTRL_01_T                          pe1_tpg_ctrl_01;	//0x0074
	PE_O18_PE1_TPG_CTRL_02_T                          pe1_tpg_ctrl_02;	//0x0078
	PE_O18_PE1_TPG_CTRL_03_T                          pe1_tpg_ctrl_03;	//0x007C
	PE_O18_PE1_TPG_CTRL_04_T                          pe1_tpg_ctrl_04;	//0x0080
	PE_O18_PE1_TPG_IA_CTRL_T                          pe1_tpg_ia_ctrl;	//0x0084
	PE_O18_PE1_TPG_IA_DATA_T                          pe1_tpg_ia_data;	//0x0088
	UINT32                                            reserved26;	//0x8c
	PE_O18_PE1_VSPYC_CTRL_00_T                        pe1_vspyc_ctrl_00;	//0x0090
	PE_O18_PE1_VSPYC_CTRL_01_T                        pe1_vspyc_ctrl_01;	//0x0094
	PE_O18_PE1_VSPYC_CTRL_02_T                        pe1_vspyc_ctrl_02;	//0x0098
	PE_O18_PE1_VSPYC_CTRL_03_T                        pe1_vspyc_ctrl_03;	//0x009C
	PE_O18_PE1_VSPYC_CTRL_04_T                        pe1_vspyc_ctrl_04;	//0x00A0
	PE_O18_PE1_VSPYC_CTRL_05_T                        pe1_vspyc_ctrl_05;	//0x00A4
	PE_O18_PE1_VSPYC_CTRL_06_T                        pe1_vspyc_ctrl_06;	//0x00A8
	PE_O18_PE1_VSPYC_CTRL_07_T                        pe1_vspyc_ctrl_07;	//0x00AC
	PE_O18_PE1_VSPYC_CTRL_08_T                        pe1_vspyc_ctrl_08;	//0x00B0
	PE_O18_PE1_VSPYC_CTRL_09_T                        pe1_vspyc_ctrl_09;	//0x00B4
	PE_O18_PE1_VSPYC_CTRL_10_T                        pe1_vspyc_ctrl_10;	//0x00B8
	PE_O18_PE1_VSPYC_CTRL_11_T                        pe1_vspyc_ctrl_11;	//0x00BC
	PE_O18_PE1_VSPYC_CTRL_12_T                        pe1_vspyc_ctrl_12;	//0x00C0
	PE_O18_PE1_VSPYC_CTRL_13_T                        pe1_vspyc_ctrl_13;	//0x00C4
	PE_O18_PE1_VSPYC_CTRL_14_T                        pe1_vspyc_ctrl_14;	//0x00C8
	PE_O18_PE1_VSPYC_CTRL_15_T                        pe1_vspyc_ctrl_15;	//0x00CC
	PE_O18_PE1_VSPYC_CTRL_16_T                        pe1_vspyc_ctrl_16;	//0x00D0
	PE_O18_PE1_VSPYC_CTRL_17_T                        pe1_vspyc_ctrl_17;	//0x00D4
	PE_O18_PE1_VSPYC_CTRL_18_T                        pe1_vspyc_ctrl_18;	//0x00D8
	UINT32                                            reserved45;	//0xdc
	PE_O18_PE1_CEN_CTRL_00_T                          pe1_cen_ctrl_00;	//0x00E0
	PE_O18_PE1_CEN_CTRL_01_T                          pe1_cen_ctrl_01;	//0x00E4
	PE_O18_PE1_CEN_CTRL_02_T                          pe1_cen_ctrl_02;	//0x00E8
	PE_O18_PE1_CEN_CTRL_03_T                          pe1_cen_ctrl_03;	//0x00EC
	PE_O18_PE1_CEN_CTRL_04_T                          pe1_cen_ctrl_04;	//0x00F0
	PE_O18_PE1_CEN_CTRL_05_T                          pe1_cen_ctrl_05;	//0x00F4
	PE_O18_PE1_CEN_CTRL_06_T                          pe1_cen_ctrl_06;	//0x00F8
	PE_O18_PE1_CEN_CTRL_07_T                          pe1_cen_ctrl_07;	//0x00FC
	UINT32                                            reserved53[4];	//0x100-0x10c
	PE_O18_PE1_CEN_IA_CTRL_T                          pe1_cen_ia_ctrl;	//0x0110
	PE_O18_PE1_CEN_IA_DATA_T                          pe1_cen_ia_data;	//0x0114
	PE_O18_PE1_CEN_DELTA_IA_CTRL_T                    pe1_cen_delta_ia_ctrl;	//0x0118
	PE_O18_PE1_CEN_DELTA_IA_DATA_T                    pe1_cen_delta_ia_data;	//0x011C
	PE_O18_PE1_DCE_CTRL_00_T                          pe1_dce_ctrl_00;	//0x0120
	PE_O18_PE1_DCE_CTRL_01_T                          pe1_dce_ctrl_01;	//0x0124
	PE_O18_PE1_DCE_CTRL_02_T                          pe1_dce_ctrl_02;	//0x0128
	PE_O18_PE1_DCE_CTRL_03_T                          pe1_dce_ctrl_03;	//0x012C
	PE_O18_PE1_DCE_CTRL_04_T                          pe1_dce_ctrl_04;	//0x0130
	PE_O18_PE1_DCE_CTRL_05_T                          pe1_dce_ctrl_05;	//0x0134
	PE_O18_PE1_DCE_IA_CTRL_T                          pe1_dce_ia_ctrl;	//0x0138
	PE_O18_PE1_DCE_IA_DATA_T                          pe1_dce_ia_data;	//0x013C
	PE_O18_PE1_DCE_CTRL_08_T                          pe1_dce_ctrl_08;	//0x0140
	PE_O18_PE1_DCE_CTRL_09_T                          pe1_dce_ctrl_09;	//0x0144
	PE_O18_PE1_DCE_HIST_IA_CTRL_T                     pe1_dce_hist_ia_ctrl;	//0x0148
	PE_O18_PE1_DCE_HIST_IA_DATA1_T                    pe1_dce_hist_ia_data1;	//0x014C
	PE_O18_PE1_DCE_HIST_IA_DATA2_T                    pe1_dce_hist_ia_data2;	//0x0150
	PE_O18_PE1_DCE_CHR_GAIN_T                         pe1_dce_chr_gain;	//0x0154
	PE_O18_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0x0158
	UINT32                                            reserved72;	//0x15c
	PE_O18_PE1_DSE_CTRL_00_T                          pe1_dse_ctrl_00;	//0x0160
	PE_O18_PE1_DSE_CTRL_01_T                          pe1_dse_ctrl_01;	//0x0164
	PE_O18_PE1_DSE_CTRL_02_T                          pe1_dse_ctrl_02;	//0x0168
	PE_O18_PE1_DSE_IA_CTRL_T                          pe1_dse_ia_ctrl;	//0x016C
	PE_O18_PE1_DSE_IA_DATA_T                          pe1_dse_ia_data;	//0x0170
	PE_O18_PE1_DSE_CTRL_03_T                          pe1_dse_ctrl_03;	//0x0174
	PE_O18_PE1_DSE_CTRL_04_T                          pe1_dse_ctrl_04;	//0x0178
	UINT32                                            reserved79;	//0x17c
	PE_O18_PE1_CW_CTRL_00_T                           pe1_cw_ctrl_00;	//0x0180
	PE_O18_PE1_CW_CTRL_01_T                           pe1_cw_ctrl_01;	//0x0184
	UINT32                                            reserved81[2];	//0x188-0x18c
	PE_O18_PE1_CW_CTRL_04_T                           pe1_cw_ctrl_04;	//0x0190
	PE_O18_PE1_LBLUR_CTRL_00_T                        pe1_lblur_ctrl_00;	//0x0194
	PE_O18_PE1_LBLUR_CTRL_01_T                        pe1_lblur_ctrl_01;	//0x0198
	PE_O18_PE1_LBLUR_CTRL_02_T                        pe1_lblur_ctrl_02;	//0x019C
	PE_O18_PE1_CONV_CTRL_00_T                         pe1_conv_ctrl_00;	//0x01A0
	PE_O18_PE1_CONV_CTRL_01_T                         pe1_conv_ctrl_01;	//0x01A4
	PE_O18_PE1_CONV_CTRL_02_T                         pe1_conv_ctrl_02;	//0x01A8
	PE_O18_PE1_CONV_CTRL_03_T                         pe1_conv_ctrl_03;	//0x01AC
	PE_O18_PE1_CONV_CTRL_04_T                         pe1_conv_ctrl_04;	//0x01B0
	PE_O18_PE1_CONV_CTRL_05_T                         pe1_conv_ctrl_05;	//0x01B4
	PE_O18_PE1_CONV_CTRL_06_T                         pe1_conv_ctrl_06;	//0x01B8
	PE_O18_PE1_CONV_CTRL_07_T                         pe1_conv_ctrl_07;	//0x01BC
	PE_O18_PE1_CONV_CTRL_08_T                         pe1_conv_ctrl_08;	//0x01C0
	PE_O18_PE1_CONV_CTRL_09_T                         pe1_conv_ctrl_09;	//0x01C4
	PE_O18_PE1_CONV_CTRL_0A_T                         pe1_conv_ctrl_0a;	//0x01C8
	PE_O18_PE1_CONV_CTRL_0B_T                         pe1_conv_ctrl_0b;	//0x01CC
	PE_O18_PE1_CONV_CTRL_0C_T                         pe1_conv_ctrl_0c;	//0x01D0
	PE_O18_PE1_CONV_CTRL_0D_T                         pe1_conv_ctrl_0d;	//0x01D4
	PE_O18_PE1_CONV_CTRL_0E_T                         pe1_conv_ctrl_0e;	//0x01D8
	PE_O18_PE1_CONV_CTRL_0F_T                         pe1_conv_ctrl_0f;	//0x01DC
	PE_O18_PE1_CONV_CTRL_10_T                         pe1_conv_ctrl_10;	//0x01E0
	PE_O18_PE1_CONV_CTRL_11_T                         pe1_conv_ctrl_11;	//0x01E4
	PE_O18_PE1_CONV_CTRL_12_T                         pe1_conv_ctrl_12;	//0x01E8
	UINT32                                            reserved104;	//0x1ec
	PE_O18_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0x01F0
	PE_O18_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0x01F4
	PE_O18_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0x01F8
	PE_O18_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0x01FC
	PE_O18_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0x0200
	PE_O18_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0x0204
	PE_O18_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0x0208
	PE_O18_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0x020C
	PE_O18_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0x0210
	PE_O18_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0x0214
	PE_O18_PE1_MUTE_CTRL_0A_T                         pe1_mute_ctrl_0a;	//0x0218
	PE_O18_PE1_MUTE_CTRL_0B_T                         pe1_mute_ctrl_0b;	//0x021C
	PE_O18_PE1_MUTE_CTRL_0C_T                         pe1_mute_ctrl_0c;	//0x0220
	PE_O18_PE1_MUTE_CTRL_0D_T                         pe1_mute_ctrl_0d;	//0x0224
	PE_O18_PE1_MUTE_CTRL_0E_T                         pe1_mute_ctrl_0e;	//0x0228
	PE_O18_PE1_MUTE_CTRL_0F_T                         pe1_mute_ctrl_0f;	//0x022C
	PE_O18_PE_PCC_CTRL_T                              pe_pcc_ctrl;	//0x0230
	PE_O18_PE1_PCC_COEF0_T                            pe1_pcc_coef0;	//0x0234
	PE_O18_PE1_PCC_COEF1_T                            pe1_pcc_coef1;	//0x0238
	PE_O18_PE1_PCC_COEF2_T                            pe1_pcc_coef2;	//0x023C
	PE_O18_PE1_PCC_COEF3_T                            pe1_pcc_coef3;	//0x0240
	PE_O18_PE1_PCC_COEF4_T                            pe1_pcc_coef4;	//0x0244
	PE_O18_PE1_PCC_COEF5_T                            pe1_pcc_coef5;	//0x0248
	PE_O18_PE1_PCC_COEF6_T                            pe1_pcc_coef6;	//0x024C
	PE_O18_PE1_PCC_COEF7_T                            pe1_pcc_coef7;	//0x0250
	PE_O18_PE1_OETF_IA_CTRL_T                         pe1_oetf_ia_ctrl;	//0x0254
	PE_O18_PE1_OETF_IA_DATA_T                         pe1_oetf_ia_data;	//0x0258
	PE_O18_PE1_EOTF_WDATA_T                           pe1_eotf_wdata;	//0x025C
	PE_O18_PE1_EOTF_WDONE_T                           pe1_eotf_wdone;	//0x0260
	PE_O18_PE1_EOTF_RDATA_T                           pe1_eotf_rdata;	//0x0264
	PE_O18_PE1_LOGO_L7SC_CTRL_00_T                    pe1_logo_l7sc_ctrl_00;	//0x0268
	PE_O18_PE1_LOGO_L7SC_CTRL_01_T                    pe1_logo_l7sc_ctrl_01;	//0x026C
	PE_O18_PE1_LOGO_L7SC_CTRL_02_T                    pe1_logo_l7sc_ctrl_02;	//0x0270
	PE_O18_PE1_LOGO_L7SC_CTRL_03_T                    pe1_logo_l7sc_ctrl_03;	//0x0274
	PE_O18_PE1_LOGO_L7SC_CTRL_04_T                    pe1_logo_l7sc_ctrl_04;	//0x0278
	PE_O18_PE1_LOGO_L7SC_CTRL_05_T                    pe1_logo_l7sc_ctrl_05;	//0x027C
	PE_O18_PE1_LOGO_L7SC_CTRL_06_T                    pe1_logo_l7sc_ctrl_06;	//0x0280
	PE_O18_PE1_LOGO_L7SC_CTRL_07_T                    pe1_logo_l7sc_ctrl_07;	//0x0284
	PE_O18_PE1_LOGO_L7SC_CTRL_08_T                    pe1_logo_l7sc_ctrl_08;	//0x0288
	PE_O18_PE1_LOGO_L7SC_CTRL_09_T                    pe1_logo_l7sc_ctrl_09;	//0x028C
	PE_O18_PE1_LOGO_L7SC_CTRL_10_T                    pe1_logo_l7sc_ctrl_10;	//0x0290
	PE_O18_PE1_LOGO_L7SC_CTRL_11_T                    pe1_logo_l7sc_ctrl_11;	//0x0294
	PE_O18_PE1_LOGO_L7SC_CTRL_12_T                    pe1_logo_l7sc_ctrl_12;	//0x0298
	PE_O18_PE1_LOGO_L7SC_CTRL_13_T                    pe1_logo_l7sc_ctrl_13;	//0x029C
	PE_O18_PE1_LRCR_CTRL_00_T                         pe1_lrcr_ctrl_00;	//0x02A0
	PE_O18_PE1_LRCR_CTRL_01_T                         pe1_lrcr_ctrl_01;	//0x02A4
	PE_O18_PE1_LRCR_CTRL_02_T                         pe1_lrcr_ctrl_02;	//0x02A8
	PE_O18_PE1_LRCR_CTRL_03_T                         pe1_lrcr_ctrl_03;	//0x02AC
	PE_O18_PE1_LRCR_CTRL_04_T                         pe1_lrcr_ctrl_04;	//0x02B0
	PE_O18_PE1_LRCR_CTRL_05_T                         pe1_lrcr_ctrl_05;	//0x02B4
	PE_O18_PE1_LRCR_CTRL_06_T                         pe1_lrcr_ctrl_06;	//0x02B8
	PE_O18_PE1_LRCR_CTRL_07_T                         pe1_lrcr_ctrl_07;	//0x02BC
	PE_O18_G_ADJ_GAIN_T                               g_adj_gain;	//0x02C0
	PE_O18_B_ADJ_GAIN_T                               b_adj_gain;	//0x02C4
	PE_O18_R_ADJ_GAIN_T                               r_adj_gain;	//0x02C8
	PE_O18_HIST_CTRL_MODE_T                           hist_ctrl_mode;	//0x02CC
	PE_O18_PE1_L_G_HIST_IA_CTRL_T                     pe1_l_g_hist_ia_ctrl;	//0x02D0
	PE_O18_PE1_L_G_HIST_IA_DATA_T                     pe1_l_g_hist_ia_data;	//0x02D4
	PE_O18_PE1_L_B_HIST_IA_CTRL_T                     pe1_l_b_hist_ia_ctrl;	//0x02D8
	PE_O18_PE1_L_B_HIST_IA_DATA_T                     pe1_l_b_hist_ia_data;	//0x02DC
	PE_O18_PE1_L_R_HIST_IA_CTRL_T                     pe1_l_r_hist_ia_ctrl;	//0x02E0
	PE_O18_PE1_L_R_HIST_IA_DATA_T                     pe1_l_r_hist_ia_data;	//0x02E4
	PE_O18_PE1_R_G_HIST_IA_CTRL_T                     pe1_r_g_hist_ia_ctrl;	//0x02E8
	PE_O18_PE1_R_G_HIST_IA_DATA_T                     pe1_r_g_hist_ia_data;	//0x02EC
	PE_O18_PE1_R_B_HIST_IA_CTRL_T                     pe1_r_b_hist_ia_ctrl;	//0x02F0
	PE_O18_PE1_R_B_HIST_IA_DATA_T                     pe1_r_b_hist_ia_data;	//0x02F4
	PE_O18_PE1_R_R_HIST_IA_CTRL_T                     pe1_r_r_hist_ia_ctrl;	//0x02F8
	PE_O18_PE1_R_R_HIST_IA_DATA_T                     pe1_r_r_hist_ia_data;	//0x02FC
	PE_O18_PE1_DEBUG_CTRL_00_T                        pe1_debug_ctrl_00;	//0x0300
	PE_O18_PE1_DEBUG_CTRL_01_T                        pe1_debug_ctrl_01;	//0x0304
	PE_O18_PE1_DEBUG_CTRL_02_T                        pe1_debug_ctrl_02;	//0x0308
	UINT32                                            reserved175;	//0x30c
	PE_O18_PE1_BT20_CTRL_00_T                         pe1_bt20_ctrl_00;	//0x0310
	PE_O18_PE1_BT20_CTRL_01_T                         pe1_bt20_ctrl_01;	//0x0314
	PE_O18_PE1_BT20_CTRL_02_T                         pe1_bt20_ctrl_02;	//0x0318
	PE_O18_PE1_BT20_CTRL_03_T                         pe1_bt20_ctrl_03;	//0x031C
	PE_O18_PE1_BT20_CTRL_04_T                         pe1_bt20_ctrl_04;	//0x0320
	PE_O18_PE1_BT20_CTRL_05_T                         pe1_bt20_ctrl_05;	//0x0324
	PE_O18_PE1_BT20_CTRL_06_T                         pe1_bt20_ctrl_06;	//0x0328
	PE_O18_PE1_BT20_CTRL_07_T                         pe1_bt20_ctrl_07;	//0x032C
	PE_O18_PE1_BT20_CTRL_08_T                         pe1_bt20_ctrl_08;	//0x0330
	PE_O18_PE1_BT20_CTRL_09_T                         pe1_bt20_ctrl_09;	//0x0334
	PE_O18_PE1_BT20_CTRL_0A_T                         pe1_bt20_ctrl_0a;	//0x0338
	PE_O18_PE1_BT20_CTRL_0B_T                         pe1_bt20_ctrl_0b;	//0x033C
	PE_O18_PE1_BT20_CTRL_0C_T                         pe1_bt20_ctrl_0c;	//0x0340
	PE_O18_PE1_BT20_CTRL_0D_T                         pe1_bt20_ctrl_0d;	//0x0344
	PE_O18_PE1_BT20_CTRL_0E_T                         pe1_bt20_ctrl_0e;	//0x0348
	PE_O18_PE1_BT20_CTRL_0F_T                         pe1_bt20_ctrl_0f;	//0x034C
	PE_O18_PE1_BT20_CTRL_10_T                         pe1_bt20_ctrl_10;	//0x0350
	PE_O18_PE1_BT20_CTRL_11_T                         pe1_bt20_ctrl_11;	//0x0354
	PE_O18_PE1_BT20_CTRL_12_T                         pe1_bt20_ctrl_12;	//0x0358
	PE_O18_PE1_BT20_CTRL_13_T                         pe1_bt20_ctrl_13;	//0x035C
	PE_O18_PE1_BT20_CTRL_14_T                         pe1_bt20_ctrl_14;	//0x0360
	PE_O18_PE1_BT20_CTRL_15_T                         pe1_bt20_ctrl_15;	//0x0364
	PE_O18_PE1_BT20_CTRL_STAT_T                       pe1_bt20_ctrl_stat;	//0x0368
	UINT32                                            reserved198;	//0x36c
	PE_O18_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0x0370
	PE_O18_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0x0374
	PE_O18_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0x0378
	PE_O18_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0x037C
	PE_O18_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0x0380
	PE_O18_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0x0384
	PE_O18_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0x0388
	PE_O18_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0x038C
	PE_O18_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0x0390
	PE_O18_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0x0394
	PE_O18_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0x0398
	PE_O18_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0x039C
	PE_O18_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0x03A0
	PE_O18_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0x03A4
	PE_O18_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0x03A8
	PE_O18_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0x03AC
	PE_O18_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0x03B0
	PE_O18_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0x03B4
	PE_O18_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0x03B8
	PE_O18_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0x03BC
	PE_O18_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0x03C0
	PE_O18_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0x03C4
	PE_O18_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0x03C8
	PE_O18_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0x03CC
	PE_O18_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0x03D0
	PE_O18_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0x03D4
	PE_O18_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0x03D8
	PE_O18_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0x03DC
	PE_O18_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0x03E0
	PE_O18_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0x03E4
	PE_O18_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0x03E8
	PE_O18_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0x03EC
	PE_O18_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0x03F0
	PE_O18_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0x03F4
	PE_O18_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0x03F8
	PE_O18_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0x03FC
	PE_O18_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0x0400
	PE_O18_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0x0404
	PE_O18_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0x0408
	PE_O18_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0x040C
	PE_O18_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0x0410
	PE_O18_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0x0414
	PE_O18_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0x0418
	PE_O18_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0x041C
	PE_O18_PE1_LOGO_STAT_00_T                         pe1_logo_stat_00;	//0x0420
	PE_O18_PE1_LOGO_STAT_01_T                         pe1_logo_stat_01;	//0x0424
	PE_O18_PE1_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0x0428
	UINT32                                            reserved245;	//0x42c
	PE_O18_PE_DSE_Y_REGION_PT0_T                      pe_dse_y_region_pt0;	//0x0430
	PE_O18_PE_DSE_Y_REGION_PT1_T                      pe_dse_y_region_pt1;	//0x0434
	PE_O18_PE_DSE_Y_REGION_PT2_T                      pe_dse_y_region_pt2;	//0x0438
	PE_O18_PE_DSE_Y_REGION_PT3_T                      pe_dse_y_region_pt3;	//0x043C
	PE_O18_PE_DSE_Y_REGION_PT4_T                      pe_dse_y_region_pt4;	//0x0440
	PE_O18_PE_DSE_Y_REGION_PT5_T                      pe_dse_y_region_pt5;	//0x0444
	PE_O18_PE_DSE_Y_REGION_PT6_T                      pe_dse_y_region_pt6;	//0x0448
	PE_O18_PE_DSE_Y_REGION_PT7_T                      pe_dse_y_region_pt7;	//0x044C
	PE_O18_PE_DSE_H_REGION_PT0_T                      pe_dse_h_region_pt0;	//0x0450
	PE_O18_PE_DSE_H_REGION_PT1_T                      pe_dse_h_region_pt1;	//0x0454
	PE_O18_PE_DSE_H_REGION_PT2_T                      pe_dse_h_region_pt2;	//0x0458
	PE_O18_PE_DSE_H_REGION_PT3_T                      pe_dse_h_region_pt3;	//0x045C
	PE_O18_PE_DSE_H_REGION_PT4_T                      pe_dse_h_region_pt4;	//0x0460
	PE_O18_PE_DSE_H_REGION_PT5_T                      pe_dse_h_region_pt5;	//0x0464
	PE_O18_PE_DSE_H_REGION_PT6_T                      pe_dse_h_region_pt6;	//0x0468
	PE_O18_PE_DSE_H_REGION_PT7_T                      pe_dse_h_region_pt7;	//0x046C
	PE_O18_PE1_DRC_CTRL_00_T                          pe1_drc_ctrl_00;	//0x0470
	PE_O18_PE1_DRC_CTRL_01_T                          pe1_drc_ctrl_01;	//0x0474
	PE_O18_PE1_DRC_CTRL_02_T                          pe1_drc_ctrl_02;	//0x0478
	PE_O18_PE1_DRC_CTRL_03_T                          pe1_drc_ctrl_03;	//0x047C
	PE_O18_PE1_DRC_CTRL_04_T                          pe1_drc_ctrl_04;	//0x0480
	PE_O18_PE1_DRC_CTRL_05_T                          pe1_drc_ctrl_05;	//0x0484
	PE_O18_PE1_DRC_CTRL_06_T                          pe1_drc_ctrl_06;	//0x0488
	PE_O18_PE1_DRC_CTRL_07_T                          pe1_drc_ctrl_07;	//0x048C
	PE_O18_PE1_DRC_CTRL_08_T                          pe1_drc_ctrl_08;	//0x0490
	PE_O18_PE1_DRC_CTRL_09_T                          pe1_drc_ctrl_09;	//0x0494
	PE_O18_PE1_DRC_CTRL_10_T                          pe1_drc_ctrl_10;	//0x0498
	PE_O18_PE1_DRC_CTRL_11_T                          pe1_drc_ctrl_11;	//0x049C
	PE_O18_PE1_DRC_CTRL_12_T                          pe1_drc_ctrl_12;	//0x04A0
	PE_O18_PE1_DRC_CTRL_13_T                          pe1_drc_ctrl_13;	//0x04A4
	PE_O18_PE1_DRC_CTRL_14_T                          pe1_drc_ctrl_14;	//0x04A8
	PE_O18_PE1_DRC_CTRL_15_T                          pe1_drc_ctrl_15;	//0x04AC
	PE_O18_PE1_DRC_CTRL_16_T                          pe1_drc_ctrl_16;	//0x04B0
	PE_O18_PE1_DRC_CTRL_17_T                          pe1_drc_ctrl_17;	//0x04B4
	PE_O18_PE1_DRC_CTRL_18_T                          pe1_drc_ctrl_18;	//0x04B8
	PE_O18_PE1_DRC_CTRL_19_T                          pe1_drc_ctrl_19;	//0x04BC
	PE_O18_PE1_DRC_CTRL_20_T                          pe1_drc_ctrl_20;	//0x04C0
	PE_O18_PE1_DRC_CTRL_21_T                          pe1_drc_ctrl_21;	//0x04C4
	PE_O18_PE1_DRC_CTRL_22_T                          pe1_drc_ctrl_22;	//0x04C8
	PE_O18_PE1_DRC_CTRL_23_T                          pe1_drc_ctrl_23;	//0x04CC
	PE_O18_PE1_DRC_CTRL_24_T                          pe1_drc_ctrl_24;	//0x04D0
	PE_O18_PE1_DRC_CTRL_25_T                          pe1_drc_ctrl_25;	//0x04D4
	PE_O18_PE1_DRC_CTRL_26_T                          pe1_drc_ctrl_26;	//0x04D8
	PE_O18_PE1_DRC_CTRL_27_T                          pe1_drc_ctrl_27;	//0x04DC
	PE_O18_PE1_DRC_CTRL_28_T                          pe1_drc_ctrl_28;	//0x04E0
	PE_O18_PE1_DRC_CTRL_29_T                          pe1_drc_ctrl_29;	//0x04E4
	PE_O18_PE1_DRC_CTRL_30_T                          pe1_drc_ctrl_30;	//0x04E8
	PE_O18_PE1_DRC_CTRL_31_T                          pe1_drc_ctrl_31;	//0x04EC
	PE_O18_PE1_DRC_CTRL_32_T                          pe1_drc_ctrl_32;	//0x04F0
	PE_O18_PE1_DRC_CTRL_33_T                          pe1_drc_ctrl_33;	//0x04F4
	PE_O18_PE1_DRC_CTRL_34_T                          pe1_drc_ctrl_34;	//0x04F8
	PE_O18_PE1_DRC_CTRL_35_T                          pe1_drc_ctrl_35;	//0x04FC
}PE_CE_PE1_REG_O18_T;

typedef struct
{ 
	PE_O18_PE1_TOP_CTRL_00_T                          pe1_top_ctrl_00;	//0x0000
	PE_O18_PE1_TOP_CTRL_01_T                          pe1_top_ctrl_01;	//0x0004
	PE_O18_PE1_TOP_CTRL_02_T                          pe1_top_ctrl_02;	//0x0008
	PE_O18_PE1_TOP_CTRL_03_T                          pe1_top_ctrl_03;	//0x000C
	PE_O18_PE1_TOP_CTRL_04_T                          pe1_top_ctrl_04;	//0x0010
	UINT32                                            reserved5[3];	//0x14-0x1c
	PE_O18_CO_PE1_FSW_CTRL_00_T                          pe1_fsw_ctrl_00;	//0x0020
	PE_O18_CO_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_01;	//0x0024
	PE_O18_CO_PE1_FSW_CTRL_02_T                          pe1_fsw_ctrl_02;	//0x0028
	PE_O18_CO_PE1_FSW_CTRL_03_T                          pe1_fsw_ctrl_03;	//0x002C
	UINT32                                            reserved9;	//0x30
	PE_O18_PE1_WIN2_CTRL_00_T                         pe1_win2_ctrl_00;	//0x0034
	PE_O18_PE1_WIN2_CTRL_01_T                         pe1_win2_ctrl_01;	//0x0038
	PE_O18_PE1_WIN2_CTRL_02_T                         pe1_win2_ctrl_02;	//0x003C
	PE_O18_PE1_WIN2_CTRL_03_T                         pe1_win2_ctrl_03;	//0x0040
	PE_O18_PE1_WIN2_CTRL_04_T                         pe1_win2_ctrl_04;	//0x0044
	UINT32                                            reserved14[2];	//0x48-0x4c
	PE_O18_PE1_APL_CTRL_00_T                          pe1_apl_ctrl_00;	//0x0050
	PE_O18_PE1_APL_CTRL_01_T                          pe1_apl_ctrl_01;	//0x0054
	PE_O18_PE1_APL_CTRL_02_T                          pe1_apl_ctrl_02;	//0x0058
	PE_O18_PE1_APL_STAT_00_T                          pe1_apl_stat_00;	//0x005C
	PE_O18_PE1_APL_STAT_01_T                          pe1_apl_stat_01;	//0x0060
	UINT32                                            reserved19[3];	//0x64-0x6c
	PE_O18_PE1_TPG_CTRL_00_T                          pe1_tpg_ctrl_00;	//0x0070
	PE_O18_PE1_TPG_CTRL_01_T                          pe1_tpg_ctrl_01;	//0x0074
	PE_O18_PE1_TPG_CTRL_02_T                          pe1_tpg_ctrl_02;	//0x0078
	PE_O18_PE1_TPG_CTRL_03_T                          pe1_tpg_ctrl_03;	//0x007C
	PE_O18_PE1_TPG_CTRL_04_T                          pe1_tpg_ctrl_04;	//0x0080
	PE_O18_PE1_TPG_IA_CTRL_T                          pe1_tpg_ia_ctrl;	//0x0084
	PE_O18_PE1_TPG_IA_DATA_T                          pe1_tpg_ia_data;	//0x0088
	UINT32                                            reserved26;	//0x8c
	PE_O18_PE1_VSPYC_CTRL_00_T                        pe1_vspyc_ctrl_00;	//0x0090
	PE_O18_PE1_VSPYC_CTRL_01_T                        pe1_vspyc_ctrl_01;	//0x0094
	PE_O18_PE1_VSPYC_CTRL_02_T                        pe1_vspyc_ctrl_02;	//0x0098
	PE_O18_PE1_VSPYC_CTRL_03_T                        pe1_vspyc_ctrl_03;	//0x009C
	PE_O18_PE1_VSPYC_CTRL_04_T                        pe1_vspyc_ctrl_04;	//0x00A0
	PE_O18_PE1_VSPYC_CTRL_05_T                        pe1_vspyc_ctrl_05;	//0x00A4
	PE_O18_PE1_VSPYC_CTRL_06_T                        pe1_vspyc_ctrl_06;	//0x00A8
	PE_O18_PE1_VSPYC_CTRL_07_T                        pe1_vspyc_ctrl_07;	//0x00AC
	PE_O18_PE1_VSPYC_CTRL_08_T                        pe1_vspyc_ctrl_08;	//0x00B0
	PE_O18_PE1_VSPYC_CTRL_09_T                        pe1_vspyc_ctrl_09;	//0x00B4
	PE_O18_PE1_VSPYC_CTRL_10_T                        pe1_vspyc_ctrl_10;	//0x00B8
	PE_O18_PE1_VSPYC_CTRL_11_T                        pe1_vspyc_ctrl_11;	//0x00BC
	PE_O18_PE1_VSPYC_CTRL_12_T                        pe1_vspyc_ctrl_12;	//0x00C0
	PE_O18_PE1_VSPYC_CTRL_13_T                        pe1_vspyc_ctrl_13;	//0x00C4
	PE_O18_PE1_VSPYC_CTRL_14_T                        pe1_vspyc_ctrl_14;	//0x00C8
	PE_O18_PE1_VSPYC_CTRL_15_T                        pe1_vspyc_ctrl_15;	//0x00CC
	PE_O18_PE1_VSPYC_CTRL_16_T                        pe1_vspyc_ctrl_16;	//0x00D0
	PE_O18_PE1_VSPYC_CTRL_17_T                        pe1_vspyc_ctrl_17;	//0x00D4
	PE_O18_PE1_VSPYC_CTRL_18_T                        pe1_vspyc_ctrl_18;	//0x00D8
	UINT32                                            reserved45;	//0xdc
	PE_O18_PE1_CEN_CTRL_00_T                          pe1_cen_ctrl_00;	//0x00E0
	PE_O18_PE1_CEN_CTRL_01_T                          pe1_cen_ctrl_01;	//0x00E4
	PE_O18_PE1_CEN_CTRL_02_T                          pe1_cen_ctrl_02;	//0x00E8
	PE_O18_PE1_CEN_CTRL_03_T                          pe1_cen_ctrl_03;	//0x00EC
	PE_O18_PE1_CEN_CTRL_04_T                          pe1_cen_ctrl_04;	//0x00F0
	PE_O18_PE1_CEN_CTRL_05_T                          pe1_cen_ctrl_05;	//0x00F4
	PE_O18_PE1_CEN_CTRL_06_T                          pe1_cen_ctrl_06;	//0x00F8
	PE_O18_PE1_CEN_CTRL_07_T                          pe1_cen_ctrl_07;	//0x00FC
	UINT32                                            reserved53[4];	//0x100-0x10c
	PE_O18_PE1_CEN_IA_CTRL_T                          pe1_cen_ia_ctrl;	//0x0110
	PE_O18_PE1_CEN_IA_DATA_T                          pe1_cen_ia_data;	//0x0114
	PE_O18_PE1_CEN_DELTA_IA_CTRL_T                    pe1_cen_delta_ia_ctrl;	//0x0118
	PE_O18_PE1_CEN_DELTA_IA_DATA_T                    pe1_cen_delta_ia_data;	//0x011C
	PE_O18_PE1_DCE_CTRL_00_T                          pe1_dce_ctrl_00;	//0x0120
	PE_O18_PE1_DCE_CTRL_01_T                          pe1_dce_ctrl_01;	//0x0124
	PE_O18_PE1_DCE_CTRL_02_T                          pe1_dce_ctrl_02;	//0x0128
	PE_O18_PE1_DCE_CTRL_03_T                          pe1_dce_ctrl_03;	//0x012C
	PE_O18_PE1_DCE_CTRL_04_T                          pe1_dce_ctrl_04;	//0x0130
	PE_O18_PE1_DCE_CTRL_05_T                          pe1_dce_ctrl_05;	//0x0134
	PE_O18_PE1_DCE_IA_CTRL_T                          pe1_dce_ia_ctrl;	//0x0138
	PE_O18_PE1_DCE_IA_DATA_T                          pe1_dce_ia_data;	//0x013C
	PE_O18_PE1_DCE_CTRL_08_T                          pe1_dce_ctrl_08;	//0x0140
	PE_O18_PE1_DCE_CTRL_09_T                          pe1_dce_ctrl_09;	//0x0144
	PE_O18_PE1_DCE_HIST_IA_CTRL_T                     pe1_dce_hist_ia_ctrl;	//0x0148
	PE_O18_PE1_DCE_HIST_IA_DATA1_T                    pe1_dce_hist_ia_data1;	//0x014C
	PE_O18_PE1_DCE_HIST_IA_DATA2_T                    pe1_dce_hist_ia_data2;	//0x0150
	PE_O18_PE1_DCE_CHR_GAIN_T                         pe1_dce_chr_gain;	//0x0154
	PE_O18_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0x0158
	UINT32                                            reserved72;	//0x15c
	PE_O18_PE1_DSE_CTRL_00_T                          pe1_dse_ctrl_00;	//0x0160
	PE_O18_PE1_DSE_CTRL_01_T                          pe1_dse_ctrl_01;	//0x0164
	PE_O18_PE1_DSE_CTRL_02_T                          pe1_dse_ctrl_02;	//0x0168
	PE_O18_PE1_DSE_IA_CTRL_T                          pe1_dse_ia_ctrl;	//0x016C
	PE_O18_PE1_DSE_IA_DATA_T                          pe1_dse_ia_data;	//0x0170
	PE_O18_PE1_DSE_CTRL_03_T                          pe1_dse_ctrl_03;	//0x0174
	PE_O18_PE1_DSE_CTRL_04_T                          pe1_dse_ctrl_04;	//0x0178
	UINT32                                            reserved79;	//0x17c
	PE_O18_PE1_CW_CTRL_00_T                           pe1_cw_ctrl_00;	//0x0180
	PE_O18_PE1_CW_CTRL_01_T                           pe1_cw_ctrl_01;	//0x0184
	UINT32                                            reserved81[2];	//0x188-0x18c
	PE_O18_PE1_CW_CTRL_04_T                           pe1_cw_ctrl_04;	//0x0190
	UINT32                                            reserved82[3];	//0x194-0x19c
	PE_O18_PE1_CONV_CTRL_00_T                         pe1_conv_ctrl_00;	//0x01A0
	PE_O18_PE1_CONV_CTRL_01_T                         pe1_conv_ctrl_01;	//0x01A4
	PE_O18_PE1_CONV_CTRL_02_T                         pe1_conv_ctrl_02;	//0x01A8
	PE_O18_PE1_CONV_CTRL_03_T                         pe1_conv_ctrl_03;	//0x01AC
	PE_O18_PE1_CONV_CTRL_04_T                         pe1_conv_ctrl_04;	//0x01B0
	PE_O18_PE1_CONV_CTRL_05_T                         pe1_conv_ctrl_05;	//0x01B4
	PE_O18_PE1_CONV_CTRL_06_T                         pe1_conv_ctrl_06;	//0x01B8
	PE_O18_PE1_CONV_CTRL_07_T                         pe1_conv_ctrl_07;	//0x01BC
	PE_O18_PE1_CONV_CTRL_08_T                         pe1_conv_ctrl_08;	//0x01C0
	PE_O18_PE1_CONV_CTRL_09_T                         pe1_conv_ctrl_09;	//0x01C4
	PE_O18_PE1_CONV_CTRL_0A_T                         pe1_conv_ctrl_0a;	//0x01C8
	PE_O18_PE1_CONV_CTRL_0B_T                         pe1_conv_ctrl_0b;	//0x01CC
	PE_O18_PE1_CONV_CTRL_0C_T                         pe1_conv_ctrl_0c;	//0x01D0
	PE_O18_PE1_CONV_CTRL_0D_T                         pe1_conv_ctrl_0d;	//0x01D4
	PE_O18_PE1_CONV_CTRL_0E_T                         pe1_conv_ctrl_0e;	//0x01D8
	PE_O18_PE1_CONV_CTRL_0F_T                         pe1_conv_ctrl_0f;	//0x01DC
	PE_O18_PE1_CONV_CTRL_10_T                         pe1_conv_ctrl_10;	//0x01E0
	PE_O18_PE1_CONV_CTRL_11_T                         pe1_conv_ctrl_11;	//0x01E4
	PE_O18_PE1_CONV_CTRL_12_T                         pe1_conv_ctrl_12;	//0x01E8
	UINT32                                            reserved101;	//0x1ec
	PE_O18_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0x01F0
	PE_O18_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0x01F4
	PE_O18_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0x01F8
	PE_O18_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0x01FC
	PE_O18_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0x0200
	PE_O18_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0x0204
	PE_O18_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0x0208
	PE_O18_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0x020C
	PE_O18_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0x0210
	PE_O18_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0x0214
	PE_O18_PE1_MUTE_CTRL_0A_T                         pe1_mute_ctrl_0a;	//0x0218
	PE_O18_PE1_MUTE_CTRL_0B_T                         pe1_mute_ctrl_0b;	//0x021C
	PE_O18_PE1_MUTE_CTRL_0C_T                         pe1_mute_ctrl_0c;	//0x0220
	PE_O18_PE1_MUTE_CTRL_0D_T                         pe1_mute_ctrl_0d;	//0x0224
	PE_O18_PE1_MUTE_CTRL_0E_T                         pe1_mute_ctrl_0e;	//0x0228
	PE_O18_PE1_MUTE_CTRL_0F_T                         pe1_mute_ctrl_0f;	//0x022C
	UINT32                                            reserved117[14];	//0x230-0x264
	PE_O18_PE1_LOGO_L3SC_CTRL_00_T                    pe1_logo_l3sc_ctrl_00;	//0x0268
	PE_O18_PE1_LOGO_L3SC_CTRL_01_T                    pe1_logo_l3sc_ctrl_01;	//0x026C
	PE_O18_PE1_LOGO_L3SC_CTRL_02_T                    pe1_logo_l3sc_ctrl_02;	//0x0270
	PE_O18_PE1_LOGO_L3SC_CTRL_03_T                    pe1_logo_l3sc_ctrl_03;	//0x0274
	PE_O18_PE1_LOGO_L3SC_CTRL_04_T                    pe1_logo_l3sc_ctrl_04;	//0x0278
	PE_O18_PE1_LOGO_L3SC_CTRL_05_T                    pe1_logo_l3sc_ctrl_05;	//0x027C
	PE_O18_PE1_LOGO_L3SC_CTRL_06_T                    pe1_logo_l3sc_ctrl_06;	//0x0280
	PE_O18_PE1_LOGO_L3SC_CTRL_07_T                    pe1_logo_l3sc_ctrl_07;	//0x0284
	PE_O18_PE1_LOGO_L3SC_CTRL_08_T                    pe1_logo_l3sc_ctrl_08;	//0x0288
	PE_O18_PE1_LOGO_L3SC_CTRL_09_T                    pe1_logo_l3sc_ctrl_09;	//0x028C
	PE_O18_PE1_LOGO_L3SC_CTRL_10_T                    pe1_logo_l3sc_ctrl_10;	//0x0290
	PE_O18_PE1_LOGO_L3SC_CTRL_11_T                    pe1_logo_l3sc_ctrl_11;	//0x0294
	PE_O18_PE1_LOGO_L3SC_CTRL_12_T                    pe1_logo_l3sc_ctrl_12;	//0x0298
	UINT32                                            reserved130;	//0x29c
	PE_O18_PE1_LRCR_CTRL_00_T                         pe1_lrcr_ctrl_00;	//0x02A0
	PE_O18_PE1_LRCR_CTRL_01_T                         pe1_lrcr_ctrl_01;	//0x02A4
	PE_O18_PE1_LRCR_CTRL_02_T                         pe1_lrcr_ctrl_02;	//0x02A8
	PE_O18_PE1_LRCR_CTRL_03_T                         pe1_lrcr_ctrl_03;	//0x02AC
	PE_O18_PE1_LRCR_CTRL_04_T                         pe1_lrcr_ctrl_04;	//0x02B0
	PE_O18_PE1_LRCR_CTRL_05_T                         pe1_lrcr_ctrl_05;	//0x02B4
	PE_O18_PE1_LRCR_CTRL_06_T                         pe1_lrcr_ctrl_06;	//0x02B8
	PE_O18_PE1_LRCR_CTRL_07_T                         pe1_lrcr_ctrl_07;	//0x02BC
	PE_O18_G_ADJ_GAIN_T                               g_adj_gain;	//0x02C0
	PE_O18_B_ADJ_GAIN_T                               b_adj_gain;	//0x02C4
	PE_O18_R_ADJ_GAIN_T                               r_adj_gain;	//0x02C8
	UINT32                                            reserved141[13];	//0x2cc-0x2fc
	PE_O18_PE1_DEBUG_CTRL_00_T                        pe1_debug_ctrl_00;	//0x0300
	PE_O18_PE1_DEBUG_CTRL_01_T                        pe1_debug_ctrl_01;	//0x0304
	PE_O18_PE1_DEBUG_CTRL_02_T                        pe1_debug_ctrl_02;	//0x0308
	UINT32                                            reserved144;	//0x30c
	PE_O18_PE1_BT20_CTRL_00_T                         pe1_bt20_ctrl_00;	//0x0310
	PE_O18_PE1_BT20_CTRL_01_T                         pe1_bt20_ctrl_01;	//0x0314
	PE_O18_PE1_BT20_CTRL_02_T                         pe1_bt20_ctrl_02;	//0x0318
	PE_O18_PE1_BT20_CTRL_03_T                         pe1_bt20_ctrl_03;	//0x031C
	PE_O18_PE1_BT20_CTRL_04_T                         pe1_bt20_ctrl_04;	//0x0320
	PE_O18_PE1_BT20_CTRL_05_T                         pe1_bt20_ctrl_05;	//0x0324
	PE_O18_PE1_BT20_CTRL_06_T                         pe1_bt20_ctrl_06;	//0x0328
	PE_O18_PE1_BT20_CTRL_07_T                         pe1_bt20_ctrl_07;	//0x032C
	PE_O18_PE1_BT20_CTRL_08_T                         pe1_bt20_ctrl_08;	//0x0330
	PE_O18_PE1_BT20_CTRL_09_T                         pe1_bt20_ctrl_09;	//0x0334
	PE_O18_PE1_BT20_CTRL_0A_T                         pe1_bt20_ctrl_0a;	//0x0338
	PE_O18_PE1_BT20_CTRL_0B_T                         pe1_bt20_ctrl_0b;	//0x033C
	PE_O18_PE1_BT20_CTRL_0C_T                         pe1_bt20_ctrl_0c;	//0x0340
	PE_O18_PE1_BT20_CTRL_0D_T                         pe1_bt20_ctrl_0d;	//0x0344
	PE_O18_PE1_BT20_CTRL_0E_T                         pe1_bt20_ctrl_0e;	//0x0348
	PE_O18_PE1_BT20_CTRL_0F_T                         pe1_bt20_ctrl_0f;	//0x034C
	PE_O18_PE1_BT20_CTRL_10_T                         pe1_bt20_ctrl_10;	//0x0350
	PE_O18_PE1_BT20_CTRL_11_T                         pe1_bt20_ctrl_11;	//0x0354
	PE_O18_PE1_BT20_CTRL_12_T                         pe1_bt20_ctrl_12;	//0x0358
	PE_O18_PE1_BT20_CTRL_13_T                         pe1_bt20_ctrl_13;	//0x035C
	PE_O18_PE1_BT20_CTRL_14_T                         pe1_bt20_ctrl_14;	//0x0360
	PE_O18_PE1_BT20_CTRL_15_T                         pe1_bt20_ctrl_15;	//0x0364
	PE_O18_PE1_BT20_CTRL_STAT_T                       pe1_bt20_ctrl_stat;	//0x0368
	UINT32                                            reserved167;	//0x36c
	PE_O18_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0x0370
	PE_O18_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0x0374
	PE_O18_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0x0378
	PE_O18_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0x037C
	PE_O18_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0x0380
	PE_O18_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0x0384
	PE_O18_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0x0388
	PE_O18_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0x038C
	PE_O18_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0x0390
	PE_O18_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0x0394
	PE_O18_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0x0398
	PE_O18_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0x039C
	PE_O18_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0x03A0
	PE_O18_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0x03A4
	PE_O18_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0x03A8
	PE_O18_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0x03AC
	PE_O18_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0x03B0
	PE_O18_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0x03B4
	PE_O18_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0x03B8
	PE_O18_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0x03BC
	PE_O18_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0x03C0
	PE_O18_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0x03C4
	PE_O18_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0x03C8
	PE_O18_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0x03CC
	PE_O18_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0x03D0
	PE_O18_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0x03D4
	PE_O18_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0x03D8
	PE_O18_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0x03DC
	PE_O18_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0x03E0
	PE_O18_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0x03E4
	PE_O18_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0x03E8
	PE_O18_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0x03EC
	PE_O18_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0x03F0
	PE_O18_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0x03F4
	PE_O18_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0x03F8
	PE_O18_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0x03FC
	PE_O18_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0x0400
	PE_O18_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0x0404
	PE_O18_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0x0408
	PE_O18_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0x040C
	PE_O18_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0x0410
	PE_O18_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0x0414
	PE_O18_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0x0418
	PE_O18_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0x041C
	PE_O18_PE1_LOGO_STAT_00_T                         pe1_logo_stat_00;	//0x0420
	PE_O18_PE1_LOGO_STAT_01_T                         pe1_logo_stat_01;	//0x0424
	UINT32                                            reserved213[2];	//0x428-0x42c
	PE_O18_PE_DSE_Y_REGION_PT0_T                      pe_dse_y_region_pt0;	//0x0430
	PE_O18_PE_DSE_Y_REGION_PT1_T                      pe_dse_y_region_pt1;	//0x0434
	PE_O18_PE_DSE_Y_REGION_PT2_T                      pe_dse_y_region_pt2;	//0x0438
	PE_O18_PE_DSE_Y_REGION_PT3_T                      pe_dse_y_region_pt3;	//0x043C
	PE_O18_PE_DSE_Y_REGION_PT4_T                      pe_dse_y_region_pt4;	//0x0440
	PE_O18_PE_DSE_Y_REGION_PT5_T                      pe_dse_y_region_pt5;	//0x0444
	PE_O18_PE_DSE_Y_REGION_PT6_T                      pe_dse_y_region_pt6;	//0x0448
	PE_O18_PE_DSE_Y_REGION_PT7_T                      pe_dse_y_region_pt7;	//0x044C
	PE_O18_PE_DSE_H_REGION_PT0_T                      pe_dse_h_region_pt0;	//0x0450
	PE_O18_PE_DSE_H_REGION_PT1_T                      pe_dse_h_region_pt1;	//0x0454
	PE_O18_PE_DSE_H_REGION_PT2_T                      pe_dse_h_region_pt2;	//0x0458
	PE_O18_PE_DSE_H_REGION_PT3_T                      pe_dse_h_region_pt3;	//0x045C
	PE_O18_PE_DSE_H_REGION_PT4_T                      pe_dse_h_region_pt4;	//0x0460
	PE_O18_PE_DSE_H_REGION_PT5_T                      pe_dse_h_region_pt5;	//0x0464
	PE_O18_PE_DSE_H_REGION_PT6_T                      pe_dse_h_region_pt6;	//0x0468
	PE_O18_PE_DSE_H_REGION_PT7_T                      pe_dse_h_region_pt7;	//0x046C
}PE_CO_PE1_REG_O18_T;
#endif