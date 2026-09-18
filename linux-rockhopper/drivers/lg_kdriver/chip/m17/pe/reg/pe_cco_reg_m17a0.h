#ifndef _PE_CCO_REG_M17A0_H_
#define _PE_CCO_REG_M17A0_H_
/*-----------------------------------------------------------------------------
                             0xc9025000L PE1_TOP_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 load_time                          :1 ;	//0 
	UINT32 load_enable                        :1 ;	//1 
	UINT32 load_type                          :1 ;	//2 
}PE_M17_CE_PE1_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025004L PE1_TOP_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 width                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 height                             :12;	//27:16
}PE_M17_CE_PE1_TOP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025008L PE1_TOP_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_position                       :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 pe1_detour                         :1 ;	//2 
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 async_delay_mode                   :1 ;	//5 
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 mode_3d                            :1 ;	//7 
	UINT32 vdpulse_pos                        :12;	//19:8
	UINT32 line_masking_mode                  :2 ;	//21:20
	UINT32 reserved04                         :2 ;	//reserved
	UINT32 master_en                          :1 ;	//24
}PE_M17_CE_PE1_TOP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902500cL PE1_TOP_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt                               :12;	//11:0
	UINT32 va_pe1_in                          :1 ;	//12
	UINT32 va_pe1_out                         :1 ;	//13
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 vcnt2                              :12;	//27:16
}PE_M17_CE_PE1_TOP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025010L PE1_TOP_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_to_cnt                           :12;	//11:0
}PE_M17_CE_PE1_TOP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025020L PE1_FSW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_s_status_0                     : 8 ;  //  7: 0
	UINT32 reg_s_status_1                     : 8 ;  // 15: 8
	UINT32 reg_s_apl_0                        : 8 ;  // 23:16
	UINT32 reg_fmd_en_0                       : 1 ;  //    24
	UINT32 reg_fmd_en_1                       : 1 ;  //    25
	UINT32 reg_tnr_auto_en                    : 1 ;  //    26
	UINT32 cl_filter_en_stat                  : 1 ;  //    27
	UINT32 clc_detection_en_stat              : 1 ;  //    28
	UINT32 reg_color_filter_status            : 2 ;  // 30:29
	UINT32 reg_shp_fw_en                      : 1 ;  //    31
}PE_M17_CE_PE1_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025024L PE1_FSW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_histo_fw_en                    : 1 ;  //     0
	UINT32 reg_drc_dc_mode                    : 2 ;  //  2: 1
	UINT32 reg_drc_dc_bypass                  : 1 ;  //     3
	UINT32 reg_drc_dc_sc_cnt                  : 4 ;  //  7: 4
	UINT32 pre_121_blur_en                    : 1 ;  //     8
	UINT32 pre_median_en                      : 1 ;  //     9
	UINT32 tnr_sc_measure_en                  : 1 ;  //    10
	UINT32 reg_is_oled                        : 1 ;  //    11
	UINT32                                    : 2 ;  // 13:12     reserved
	UINT32 reg_hdr_effect                     : 2 ;  // 15:14
	UINT32 tnr_sc_measure_th                  : 16;  // 31:16
}PE_M17_CE_PE1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025028L PE1_FSW_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_src_info                       : 6 ;  //  5: 0
	UINT32 reg_src_freeze                     : 1 ;  //     6
}PE_M17_CE_PE1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902502cL PE1_FSW_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_nt_lvl                         : 8 ;  //  7: 0
	UINT32 reg_s_status                       : 8 ;  // 15: 8
	UINT32 reg_s_apl                          : 8 ;  // 23:16
}PE_M17_CE_PE1_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025034L PE1_WIN2_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win0_en                            :1 ;	//0 
	UINT32 win1_en                            :1 ;	//1 
	UINT32 win01_en                           :1 ;	//2 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 win_outside                        :1 ;	//6 
	UINT32 win_en                             :1 ;	//7 
	UINT32 bdr_alpha                          :5 ;	//12:8
	UINT32 bdr_wid                            :2 ;	//14:13
	UINT32 bdr_en                             :1 ;	//15
	UINT32 cr5                                :5 ;	//20:16
	UINT32 cb5                                :5 ;	//25:21
	UINT32 yy6                                :6 ;	//31:26
}PE_M17_CE_PE1_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025038L PE1_WIN2_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y0                          :12;	//27:16
}PE_M17_CE_PE1_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc902503cL PE1_WIN2_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y1                          :12;	//27:16
}PE_M17_CE_PE1_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9025040L PE1_WIN2_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y0                          :12;	//27:16
}PE_M17_CE_PE1_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025044L PE1_WIN2_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y1                          :12;	//27:16
}PE_M17_CE_PE1_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025050L PE1_APL_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_win_ctrl_x0                    :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 apl_win_ctrl_y0                    :12;	//27:16
}PE_M17_CE_PE1_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025054L PE1_APL_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_win_ctrl_x1                    :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 apl_win_ctrl_y1                    :12;	//27:16
}PE_M17_CE_PE1_APL_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025058L PE1_APL_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_position                       :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 act_win_mode                       :1 ;	//8 
}PE_M17_CE_PE1_APL_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902505cL PE1_APL_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_cb                             :10;	//9:0
	UINT32 apl_yg                             :10;	//19:10
	UINT32 apl_cr                             :10;	//29:20
}PE_M17_CE_PE1_APL_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025060L PE1_APL_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_cb_other_side                  :10;	//9:0
	UINT32 apl_yg_other_side                  :10;	//19:10
	UINT32 apl_cr_other_side                  :10;	//29:20
}PE_M17_CE_PE1_APL_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025070L PE1_TPG_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_enable                         :1 ;	//0 
	UINT32 pattern_type                       :2 ;	//2:1
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 blend_alpha                        :4 ;	//7:4
	UINT32 blt_size_x                         :12;	//19:8
	UINT32 blt_size_y                         :12;	//31:20
}PE_M17_CE_PE1_TPG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025074L PE1_TPG_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 gradation_stride                   :7 ;	//6:0
	UINT32 gradation_direction                :1 ;	//7 
	UINT32 gradation_bar_0_en                 :1 ;	//8 
	UINT32 gradation_bar_1_en                 :1 ;	//9 
	UINT32 gradation_bar_2_en                 :1 ;	//10
	UINT32 gradation_bar_3_en                 :1 ;	//11
}PE_M17_CE_PE1_TPG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025078L PE1_TPG_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 patch_0_en                         :1 ;	//0 
	UINT32 patch_1_en                         :1 ;	//1 
	UINT32 patch_2_en                         :1 ;	//2 
	UINT32 patch_3_en                         :1 ;	//3 
	UINT32 patch_4_en                         :1 ;	//4 
	UINT32 patch_5_en                         :1 ;	//5 
	UINT32 patch_6_en                         :1 ;	//6 
	UINT32 patch_7_en                         :1 ;	//7 
	UINT32 patch_8_en                         :1 ;	//8 
	UINT32 patch_9_en                         :1 ;	//9 
	UINT32 patch_10_en                        :1 ;	//10
	UINT32 patch_11_en                        :1 ;	//11
	UINT32 patch_12_en                        :1 ;	//12
	UINT32 patch_13_en                        :1 ;	//13
	UINT32 patch_14_en                        :1 ;	//14
	UINT32 patch_15_en                        :1 ;	//15
}PE_M17_CE_PE1_TPG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902507cL PE1_TPG_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 patch_0_inout_sel                  :1 ;	//0 
	UINT32 patch_1_inout_sel                  :1 ;	//1 
	UINT32 patch_2_inout_sel                  :1 ;	//2 
	UINT32 patch_3_inout_sel                  :1 ;	//3 
	UINT32 patch_4_inout_sel                  :1 ;	//4 
	UINT32 patch_5_inout_sel                  :1 ;	//5 
	UINT32 patch_6_inout_sel                  :1 ;	//6 
	UINT32 patch_7_inout_sel                  :1 ;	//7 
	UINT32 patch_8_inout_sel                  :1 ;	//8 
	UINT32 patch_9_inout_sel                  :1 ;	//9 
	UINT32 patch_10_inout_sel                 :1 ;	//10
	UINT32 patch_11_inout_sel                 :1 ;	//11
	UINT32 patch_12_inout_sel                 :1 ;	//12
	UINT32 patch_13_inout_sel                 :1 ;	//13
	UINT32 patch_14_inout_sel                 :1 ;	//14
	UINT32 patch_15_inout_sel                 :1 ;	//15
}PE_M17_CE_PE1_TPG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025080L PE1_TPG_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :10;	//9:0
	UINT32 bg_color_b                         :10;	//19:10
	UINT32 bg_color_g                         :10;	//29:20
}PE_M17_CE_PE1_TPG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025084L PE1_TPG_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_indir_addr                     :7 ;	//6:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 tpg_indir_ai_en                    :1 ;	//12
}PE_M17_CE_PE1_TPG_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025088L PE1_TPG_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_indir_data;	//31:0
}PE_M17_CE_PE1_TPG_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90250a0L PE1_VSPYC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 graycolor_enable                   :1 ;	//1 
	UINT32 color_only_enable                  :1 ;	//2 
	UINT32 cb_info                            :1 ;	//3 
	UINT32 cr_info                            :1 ;	//4 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 center_position                    :8 ;	//15:8
	UINT32 contrast                           :10;	//25:16
}PE_M17_CE_PE1_VSPYC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90250a4L PE1_VSPYC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 saturation                         :8 ;	//15:8
	UINT32 brightness                         :10;	//25:16
}PE_M17_CE_PE1_VSPYC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90250b0L PE1_DEBUG_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable_debug_mode                  :1 ;	//0 
	UINT32 status_enable                      :1 ;	//1 
	UINT32 debug_mode                         :1 ;	//2 
	UINT32 reserved01                         :17;	//reserved
	UINT32 show_apl                           :1 ;	//20
}PE_M17_CE_PE1_DEBUG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90250b4L PE1_DEBUG_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 yc_debug_en                        :1 ;	//0 
	UINT32 force_yy_enable                    :1 ;	//1 
	UINT32 force_cb_enable                    :1 ;	//2 
	UINT32 force_cr_enable                    :1 ;	//3 
	UINT32 yc_debug_mode_sel                  :3 ;	//6:4
}PE_M17_CE_PE1_DEBUG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90250b8L PE1_DEBUG_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 force_yy                           :10;	//9:0
	UINT32 force_cb                           :10;	//19:10
	UINT32 force_cr                           :10;	//29:20
}PE_M17_CE_PE1_DEBUG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90250e0L PE1_CEN_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cen_detour                         :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 select_hsv                         :1 ;	//2 
	UINT32 select_rgb                         :1 ;	//3 
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 vsp_sel                            :1 ;	//5 
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 reg_cen_bypass                     :1 ;	//7 
	UINT32 reg_cen_debug_mode                 :1 ;	//8 
	UINT32 reserved04                         :1 ;	//reserved
	UINT32 core_1st__gain_disable             :1 ;	//10
	UINT32 core_2nd_gain_disable              :1 ;	//11
	UINT32 reserved05                         :1 ;	//reserved
	UINT32 debugging_mode_core                :2 ;	//14:13
	UINT32 reserved06                         :1 ;	//reserved
	UINT32 demo_mode                          :8 ;	//23:16
	UINT32 reserved07                         :7 ;	//reserved
	UINT32 win_control_mode                   :1 ;	//31
}PE_M17_CE_PE1_CEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90250e4L PE1_CEN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 show_color_region0                 :1 ;	//0 
	UINT32 show_color_region1                 :1 ;	//1 
	UINT32 show_color_region2                 :1 ;	//2 
	UINT32 show_color_region3                 :1 ;	//3 
	UINT32 show_color_region4                 :1 ;	//4 
	UINT32 show_color_region5                 :1 ;	//5 
	UINT32 show_color_region6                 :1 ;	//6 
	UINT32 show_color_region7                 :1 ;	//7 
	UINT32 show_color_region8                 :1 ;	//8 
	UINT32 show_color_region9                 :1 ;	//9 
	UINT32 show_color_region10                :1 ;	//10
	UINT32 show_color_region11                :1 ;	//11
	UINT32 show_color_region12                :1 ;	//12
	UINT32 show_color_region13                :1 ;	//13
	UINT32 show_color_region14                :1 ;	//14
	UINT32 show_color_region15                :1 ;	//15
	UINT32 color_region_en0                   :1 ;	//16
	UINT32 color_region_en1                   :1 ;	//17
	UINT32 color_region_en2                   :1 ;	//18
	UINT32 color_region_en3                   :1 ;	//19
	UINT32 color_region_en4                   :1 ;	//20
	UINT32 color_region_en5                   :1 ;	//21
	UINT32 color_region_en6                   :1 ;	//22
	UINT32 color_region_en7                   :1 ;	//23
	UINT32 color_region_en8                   :1 ;	//24
	UINT32 color_region_en9                   :1 ;	//25
	UINT32 color_region_en10                  :1 ;	//26
	UINT32 color_region_en11                  :1 ;	//27
	UINT32 color_region_en12                  :1 ;	//28
	UINT32 color_region_en13                  :1 ;	//29
	UINT32 color_region_en14                  :1 ;	//30
	UINT32 color_region_en15                  :1 ;	//31
}PE_M17_CE_PE1_CEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90250e8L PE1_CEN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ihsv_sgain                         :8 ;	//7:0
	UINT32 ihsv_vgain                         :8 ;	//15:8
}PE_M17_CE_PE1_CEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90250ecL PE1_CEN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ihsv_hoffset                       :8 ;	//7:0
	UINT32 ihsv_soffset                       :8 ;	//15:8
	UINT32 ihsv_voffset                       :8 ;	//23:16
}PE_M17_CE_PE1_CEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90250f0L PE1_CEN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr0                :8 ;	//7:0
	UINT32 reg_master_gain_cr1                :8 ;	//15:8
	UINT32 reg_master_gain_cr2                :8 ;	//23:16
	UINT32 reg_master_gain_cr3                :8 ;	//31:24
}PE_M17_CE_PE1_CEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90250f4L PE1_CEN_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr4                :8 ;	//7:0
	UINT32 reg_master_gain_cr5                :8 ;	//15:8
	UINT32 reg_master_gain_cr6                :8 ;	//23:16
	UINT32 reg_master_gain_cr7                :8 ;	//31:24
}PE_M17_CE_PE1_CEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90250f8L PE1_CEN_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr8                :8 ;	//7:0
	UINT32 reg_master_gain_cr9                :8 ;	//15:8
	UINT32 reg_master_gain_cr10               :8 ;	//23:16
	UINT32 reg_master_gain_cr11               :8 ;	//31:24
}PE_M17_CE_PE1_CEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90250fcL PE1_CEN_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr12               :8 ;	//7:0
	UINT32 reg_master_gain_cr13               :8 ;	//15:8
	UINT32 reg_master_gain_cr14               :8 ;	//23:16
	UINT32 reg_master_gain_cr15               :8 ;	//31:24
}PE_M17_CE_PE1_CEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025110L PE1_CEN_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_address                    :8 ;	//7:0
	UINT32 hif_cen_ai_sel                     :3 ;	//10:8
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 hif_cen_ai                         :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_cen_enable                     :1 ;	//15
}PE_M17_CE_PE1_CEN_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025114L PE1_CEN_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_y_wdata                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_cen_x_wdata                    :10;	//25:16
}PE_M17_CE_PE1_CEN_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025118L PE1_CEN_DELTA_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_delta_address              :5 ;	//4:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 hif_cen_delta_ai                   :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_cen_delta_enable               :1 ;	//15
}PE_M17_CE_PE1_CEN_DELTA_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902511cL PE1_CEN_DELTA_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_vr_data                    :8 ;	//7:0
	UINT32 hif_cen_sb_data                    :8 ;	//15:8
	UINT32 hif_cen_hg_data                    :8 ;	//23:16
}PE_M17_CE_PE1_CEN_DELTA_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025120L PE1_DCE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dynamic_contrast_en                :1 ;	//0 
	UINT32 hist_bin_mode                      :2 ;	//2:1
	UINT32 hist_clear                         :1 ;	//3 
	UINT32 window01_enable                    :1 ;	//4 
	UINT32 window0_enable                     :1 ;	//5 
	UINT32 window1_enable                     :1 ;	//6 
	UINT32 window_acquire                     :1 ;	//7 
	UINT32 color_region0_sel                  :1 ;	//8 
	UINT32 color_region1_sel                  :1 ;	//9 
	UINT32 color_region2_sel                  :1 ;	//10
	UINT32 color_region3_sel                  :1 ;	//11
	UINT32 color_region4_sel                  :1 ;	//12
	UINT32 color_region5_sel                  :1 ;	//13
	UINT32 color_region6_sel                  :1 ;	//14
	UINT32 color_region7_sel                  :1 ;	//15
	UINT32 color_region8_sel                  :1 ;	//16
	UINT32 color_region9_sel                  :1 ;	//17
	UINT32 color_region10_sel                 :1 ;	//18
	UINT32 color_region11_sel                 :1 ;	//19
	UINT32 color_region12_sel                 :1 ;	//20
	UINT32 color_region13_sel                 :1 ;	//21
	UINT32 color_region14_sel                 :1 ;	//22
	UINT32 color_region15_sel                 :1 ;	//23
	UINT32 dce_domain_sel                     :1 ;	//24
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 window_mode_enable                 :1 ;	//26
	UINT32 window_inout_sel                   :1 ;	//27
	UINT32 histogram_mode                     :2 ;	//29:28
}PE_M17_CE_PE1_DCE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025124L PE1_DCE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_bin_min_position              :8 ;	//7:0
	UINT32 hist_bin_max_position              :8 ;	//15:8
	UINT32 color_region_gain                  :8 ;	//23:16
}PE_M17_CE_PE1_DCE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025128L PE1_DCE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 color_region_en                    :1 ;	//0 
	UINT32 color_debug_en                     :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 y_grad_gain                        :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 cb_grad_gain                       :2 ;	//9:8
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 cr_grad_gain                       :2 ;	//13:12
}PE_M17_CE_PE1_DCE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902512cL PE1_DCE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 y_range_max                        :10;	//25:16
}PE_M17_CE_PE1_DCE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025130L PE1_DCE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cb_range_min                       :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 cb_range_max                       :10;	//25:16
}PE_M17_CE_PE1_DCE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025134L PE1_DCE_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_range_min                       :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 cr_range_max                       :10;	//25:16
}PE_M17_CE_PE1_DCE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025138L PE1_DCE_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_address                    :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hif_dce_load                       :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hif_dce_ai                         :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hif_dce_enable                     :1 ;	//15
}PE_M17_CE_PE1_DCE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902513cL PE1_DCE_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_wdata_y                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dyc_wdata_x                    :10;	//25:16
}PE_M17_CE_PE1_DCE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025140L PE1_DCE_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_wdata_y_32nd               :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dyc_wdata_x_32nd               :10;	//25:16
}PE_M17_CE_PE1_DCE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025144L PE1_DCE_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 dce_ktd_csc_sel                    :1 ;	//1 
}PE_M17_CE_PE1_DCE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025148L PE1_DCE_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :5 ;	//4:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
	UINT32 hif_status_address                 :3 ;	//18:16
	UINT32 reserved03                         :9 ;	//reserved
	UINT32 hif_status_ai                      :1 ;	//28
	UINT32 hif_mask                           :1 ;	//29
}PE_M17_CE_PE1_DCE_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902514cL PE1_DCE_HIST_IA_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status0                       :23;	//22:0
}PE_M17_CE_PE1_DCE_HIST_IA_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9025150L PE1_DCE_HIST_IA_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status1                       :29;	//28:0
}PE_M17_CE_PE1_DCE_HIST_IA_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9025154L PE1_DCE_CHR_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dce_chr_gain2                      :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 dce_chr_gain1                      :10;	//25:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 chroma_gain_enable                 :1 ;	//28
}PE_M17_CE_PE1_DCE_CHR_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc9025158L PE1_DCE_CHR_ALPHA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dce_chr_alpha2                     :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 dce_chr_alpha1                     :10;	//25:16
}PE_M17_CE_PE1_DCE_CHR_ALPHA_T;
/*-----------------------------------------------------------------------------
                             0xc9025160L PE1_DSE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dynamic_saturation_en              :1 ;	//0 
	UINT32 window_mode_enable                 :1 ;	//1 
	UINT32 window_inout_sel                   :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 window01_enable                    :1 ;	//4 
	UINT32 window0_enable                     :1 ;	//5 
	UINT32 window1_enable                     :1 ;	//6 
	UINT32 window_acquire                     :1 ;	//7 
	UINT32 color_region0_sel                  :1 ;	//8 
	UINT32 color_region1_sel                  :1 ;	//9 
	UINT32 color_region2_sel                  :1 ;	//10
	UINT32 color_region3_sel                  :1 ;	//11
	UINT32 color_region4_sel                  :1 ;	//12
	UINT32 color_region5_sel                  :1 ;	//13
	UINT32 color_region6_sel                  :1 ;	//14
	UINT32 color_region7_sel                  :1 ;	//15
	UINT32 color_region8_sel                  :1 ;	//16
	UINT32 color_region9_sel                  :1 ;	//17
	UINT32 color_region10_sel                 :1 ;	//18
	UINT32 color_region11_sel                 :1 ;	//19
	UINT32 color_region12_sel                 :1 ;	//20
	UINT32 color_region13_sel                 :1 ;	//21
	UINT32 color_region14_sel                 :1 ;	//22
	UINT32 color_region15_sel                 :1 ;	//23
}PE_M17_CE_PE1_DSE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025164L PE1_DSE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dse_cr_mode_sel                :1 ;	//0 
	UINT32 reg_yh_cr_en                       :1 ;	//1 
	UINT32 reg_yh_debug                       :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_dse_y_grad                       :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 r_dse_h_grad                       :2 ;	//9:8
	UINT32 reserved03                         :14;	//reserved
	UINT32 color_region_gain                  :8 ;	//31:24
}PE_M17_CE_PE1_DSE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025168L PE1_DSE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_wdata_y_32nd               :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dse_wdata_x_32nd               :10;	//25:16
}PE_M17_CE_PE1_DSE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902516cL PE1_DSE_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_address                    :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hif_dse_load                       :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hif_dse_ai                         :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hif_dse_enable                     :1 ;	//15
}PE_M17_CE_PE1_DSE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025170L PE1_DSE_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_wdata_y                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dse_wdata_x                    :10;	//25:16
}PE_M17_CE_PE1_DSE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025174L PE1_DSE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 y_range_max                        :10;	//25:16
}PE_M17_CE_PE1_DSE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025178L PE1_DSE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 h_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 h_range_max                        :10;	//25:16
}PE_M17_CE_PE1_DSE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025180L PE1_CW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cw_en                              :1 ;	//0 
}PE_M17_CE_PE1_CW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025184L PE1_CW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 user_ctrl_g_gain                   :8 ;	//7:0
	UINT32 user_ctrl_b_gain                   :8 ;	//15:8
	UINT32 user_ctrl_r_gain                   :8 ;	//23:16
}PE_M17_CE_PE1_CW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025190L PE1_CW_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 color_region0_sel                  :1 ;	//0 
	UINT32 color_region1_sel                  :1 ;	//1 
	UINT32 color_region2_sel                  :1 ;	//2 
	UINT32 color_region3_sel                  :1 ;	//3 
	UINT32 color_region4_sel                  :1 ;	//4 
	UINT32 color_region5_sel                  :1 ;	//5 
	UINT32 color_region6_sel                  :1 ;	//6 
	UINT32 color_region7_sel                  :1 ;	//7 
	UINT32 color_region8_sel                  :1 ;	//8 
	UINT32 color_region9_sel                  :1 ;	//9 
	UINT32 color_region10_sel                 :1 ;	//10
	UINT32 color_region11_sel                 :1 ;	//11
	UINT32 color_region12_sel                 :1 ;	//12
	UINT32 color_region13_sel                 :1 ;	//13
	UINT32 color_region14_sel                 :1 ;	//14
	UINT32 color_region15_sel                 :1 ;	//15
	UINT32 color_region_gain                  :8 ;	//23:16
}PE_M17_CE_PE1_CW_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90251a0L PE1_CONV_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 conv_3d_r_en                       :1 ;	//0 
	UINT32 fpacking_r_en                      :1 ;	//1 
	UINT32 ffmode_r_en                        :1 ;	//2 
	UINT32 load_parity_r                      :1 ;	//3 
	UINT32 conv_3d_l_en                       :1 ;	//4 
	UINT32 fpacking_l_en                      :1 ;	//5 
	UINT32 ffmode_l_en                        :1 ;	//6 
	UINT32 load_parity_l                      :1 ;	//7 
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 start_parity_r                     :1 ;	//16
	UINT32 start_parity_l                     :1 ;	//17
}PE_M17_CE_PE1_CONV_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90251a4L PE1_CONV_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 offset_r                           :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 offset_l                           :8 ;	//23:16
}PE_M17_CE_PE1_CONV_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90251a8L PE1_CONV_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_grey                      :8 ;	//7:0
}PE_M17_CE_PE1_CONV_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90251acL PE1_CONV_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CE_PE1_CONV_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90251b0L PE1_CONV_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CE_PE1_CONV_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90251b4L PE1_CONV_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_CONV_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90251b8L PE1_CONV_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_CONV_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90251bcL PE1_CONV_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CE_PE1_CONV_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90251c0L PE1_CONV_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CE_PE1_CONV_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90251c4L PE1_CONV_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CE_PE1_CONV_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90251c8L PE1_CONV_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_CONV_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90251ccL PE1_CONV_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_CONV_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90251d0L PE1_CONV_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CE_PE1_CONV_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90251d4L PE1_CONV_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mux3d_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_out_mux                        :2 ;	//5:4
	UINT32 start_parity                       :1 ;	//6 
	UINT32 load_parity                        :1 ;	//7 
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 alpha1_gain                        :8 ;	//23:16
	UINT32 alpha0_gain                        :8 ;	//31:24
}PE_M17_CE_PE1_CONV_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90251d8L PE1_CONV_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_l_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_l_window_v_en                  :1 ;	//31
}PE_M17_CE_PE1_CONV_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90251dcL PE1_CONV_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_CONV_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90251e0L PE1_CONV_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_r_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_r_window_v_en                  :1 ;	//31
}PE_M17_CE_PE1_CONV_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90251e4L PE1_CONV_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_CONV_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90251e8L PE1_CONV_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :8 ;	//7:0
	UINT32 bg_color_b                         :8 ;	//15:8
	UINT32 bg_color_g                         :8 ;	//23:16
}PE_M17_CE_PE1_CONV_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90251f0L PE1_MUTE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CE_PE1_MUTE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90251f4L PE1_MUTE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CE_PE1_MUTE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90251f8L PE1_MUTE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_MUTE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90251fcL PE1_MUTE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_MUTE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025200L PE1_MUTE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CE_PE1_MUTE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025204L PE1_MUTE_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CE_PE1_MUTE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025208L PE1_MUTE_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CE_PE1_MUTE_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902520cL PE1_MUTE_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_MUTE_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025210L PE1_MUTE_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CE_PE1_MUTE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025214L PE1_MUTE_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CE_PE1_MUTE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025218L PE1_MUTE_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mux3d_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_out_mux                        :2 ;	//5:4
	UINT32 start_parity                       :1 ;	//6 
	UINT32 reserved02                         :9 ;	//reserved
	UINT32 alpha1_gain                        :8 ;	//23:16
	UINT32 alpha0_gain                        :8 ;	//31:24
}PE_M17_CE_PE1_MUTE_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902521cL PE1_MUTE_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_l_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_l_window_v_en                  :1 ;	//31
}PE_M17_CE_PE1_MUTE_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9025220L PE1_MUTE_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_MUTE_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9025224L PE1_MUTE_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_r_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_r_window_v_en                  :1 ;	//31
}PE_M17_CE_PE1_MUTE_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9025228L PE1_MUTE_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_MUTE_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc902522cL PE1_MUTE_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :8 ;	//7:0
	UINT32 bg_color_b                         :8 ;	//15:8
	UINT32 bg_color_g                         :8 ;	//23:16
}PE_M17_CE_PE1_MUTE_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90252a0L PE1_LRCR_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 adjust_en                          :1 ;	//1 
	UINT32 protection_en                      :1 ;	//2 
	UINT32 adjust_en2                         :1 ;	//3 
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 ff_mode_en                         :1 ;	//8 
	UINT32 ff_mode_parity                     :1 ;	//9 
	UINT32 ll_mode_enable                     :1 ;	//10
	UINT32 line_parity_select                 :1 ;	//11
	UINT32 lrcr_out_mux                       :1 ;	//12
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_lrcr_gain                      :4 ;	//19:16
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hist_mode                          :2 ;	//23:22
}PE_M17_CE_PE1_LRCR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90252a4L PE1_LRCR_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 th_max_hist                        :8 ;	//7:0
	UINT32 th_valid_bins                      :8 ;	//15:8
	UINT32 th1                                :8 ;	//23:16
	UINT32 th0                                :8 ;	//31:24
}PE_M17_CE_PE1_LRCR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90252a8L PE1_LRCR_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hist_l_window_h_en                 :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hist_l_window_v_en                 :1 ;	//31
}PE_M17_CE_PE1_LRCR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90252acL PE1_LRCR_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_LRCR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90252b0L PE1_LRCR_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hist_r_window_h_en                 :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hist_r_window_v_en                 :1 ;	//31
}PE_M17_CE_PE1_LRCR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90252b4L PE1_LRCR_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_LRCR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90252b8L PE1_LRCR_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 active_window_h_en                 :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 active_window_v_en                 :1 ;	//31
}PE_M17_CE_PE1_LRCR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90252bcL PE1_LRCR_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CE_PE1_LRCR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90252c0L G_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CE_G_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90252c4L B_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CE_B_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90252c8L R_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CE_R_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90252ccL HIST_CTRL_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bin_mode                           :2 ;	//1:0
	UINT32 histo_ctrl                         :2 ;	//3:2
	UINT32 reserved01                         :19;	//reserved
	UINT32 histo_clear                        :1 ;	//23
}PE_M17_CE_HIST_CTRL_MODE_T;
/*-----------------------------------------------------------------------------
                             0xc90252d0L PE1_L_G_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_L_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252d4L PE1_L_G_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_L_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90252d8L PE1_L_B_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_L_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252dcL PE1_L_B_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_L_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90252e0L PE1_L_R_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_L_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252e4L PE1_L_R_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_L_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90252e8L PE1_R_G_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_R_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252ecL PE1_R_G_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_R_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90252f0L PE1_R_B_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_R_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252f4L PE1_R_B_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_R_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90252f8L PE1_R_R_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CE_PE1_R_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90252fcL PE1_R_R_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CE_PE1_R_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025310L PE1_BT20_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef1                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef0                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025314L PE1_BT20_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef3a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef2                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025318L PE1_BT20_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef5a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef4a                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902531cL PE1_BT20_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef7a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef6a                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025320L PE1_BT20_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst0                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_coef8a                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025324L PE1_BT20_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst2                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_ofst1                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025328L PE1_BT20_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst3                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_ofst4                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902532cL PE1_BT20_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 r_degamma_en                       :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 r_1x3_en                           :1 ;	//8 
	UINT32 reserved03                         :7 ;	//reserved
	UINT32 r_2x3_ofst5                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025330L PE1_BT20_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dither_en                          :1 ;	//0 
	UINT32 decontour_en                       :1 ;	//1 
	UINT32 dither_random_freeze_en            :1 ;	//2 
	UINT32 demo_pattern_enable                :1 ;	//3 
	UINT32 bit_mode                           :2 ;	//5:4
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 decontour_gain_r                   :8 ;	//15:8
	UINT32 decontour_gain_g                   :8 ;	//23:16
	UINT32 decontour_gain_b                   :8 ;	//31:24
}PE_M17_CE_PE1_BT20_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025334L PE1_BT20_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef3b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_csc_cb_th                      :10;	//25:16
}PE_M17_CE_PE1_BT20_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025338L PE1_BT20_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef5b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef4b                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902533cL PE1_BT20_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef7b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef6b                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9025340L PE1_BT20_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_csc_cr_th                      :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 r_2x3_coef8b                       :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9025344L PE1_BT20_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef1                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef0                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9025348L PE1_BT20_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef3                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef2                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc902534cL PE1_BT20_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef5                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef4                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9025350L PE1_BT20_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef7                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef6                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9025354L PE1_BT20_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 r_1x3_coef8                        :15;	//30:16
}PE_M17_CE_PE1_BT20_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9025358L PE1_BT20_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst1                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst0                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc902535cL PE1_BT20_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst3                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst2                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9025360L PE1_BT20_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst5                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst4                        :11;	//26:16
}PE_M17_CE_PE1_BT20_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9025370L PE1_LOGO_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 logo_param_logo_en                 :1 ;	//0 
	UINT32 logo_param_logo_debug_en           :2 ;	//2:1
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 region_gain_en                     :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 region_gain_offset                 :9 ;	//16:8
	UINT32 reserved03                         :7 ;	//reserved
	UINT32 logo_param_logo_master_gain        :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025374L PE1_LOGO_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bound_proc_en                      :1 ;	//0 
	UINT32 bound_proc_logocheck               :1 ;	//1 
	UINT32 bound_proc_gain                    :8 ;	//9:2
	UINT32 bound_proc_range_x                 :11;	//20:10
	UINT32 bound_proc_range_y                 :11;	//31:21
}PE_M17_CE_PE1_LOGO_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025378L PE1_LOGO_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 boundary_position_x0               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 boundary_position_x1               :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902537cL PE1_LOGO_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 boundary_position_y0               :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 boundary_position_y1               :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025380L PE1_LOGO_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_position_x0                 :8 ;	//7:0
	UINT32 region_position_x1                 :8 ;	//15:8
	UINT32 region_position_x2                 :8 ;	//23:16
	UINT32 region_position_x3                 :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025384L PE1_LOGO_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_position_x4                 :8 ;	//7:0
	UINT32 region_position_x5                 :8 ;	//15:8
	UINT32 region_position_x6                 :8 ;	//23:16
	UINT32 region_position_x7                 :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025388L PE1_LOGO_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_position_y0                 :8 ;	//7:0
	UINT32 region_position_y1                 :8 ;	//15:8
	UINT32 region_position_y2                 :8 ;	//23:16
	UINT32 region_position_y3                 :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902538cL PE1_LOGO_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_position_y4                 :8 ;	//7:0
	UINT32 region_position_y5                 :8 ;	//15:8
	UINT32 region_position_y6                 :8 ;	//23:16
	UINT32 region_position_y7                 :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025390L PE1_LOGO_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_gain_x0                     :8 ;	//7:0
	UINT32 region_gain_x1                     :8 ;	//15:8
	UINT32 region_gain_x2                     :8 ;	//23:16
	UINT32 region_gain_x3                     :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025394L PE1_LOGO_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_gain_x4                     :8 ;	//7:0
	UINT32 region_gain_x5                     :8 ;	//15:8
	UINT32 region_gain_x6                     :8 ;	//23:16
	UINT32 region_gain_x7                     :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025398L PE1_LOGO_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 logo_lut_en                        :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 window01_enable                    :1 ;	//4 
	UINT32 window0_enable                     :1 ;	//5 
	UINT32 window1_enable                     :1 ;	//6 
	UINT32 window_acquire                     :1 ;	//7 
	UINT32 window_mode_enable                 :1 ;	//8 
	UINT32 reserved02                         :7 ;	//reserved
	UINT32 window_inout_sel                   :1 ;	//16
}PE_M17_CE_PE1_LOGO_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902539cL PE1_LOGO_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y0                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90253a0L PE1_LOGO_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y1                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90253a4L PE1_LOGO_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y0                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90253a8L PE1_LOGO_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y1                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90253acL PE1_LOGO_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_logo_wdata_y_32nd              :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_logo_wdata_x_32nd              :10;	//25:16
}PE_M17_CE_PE1_LOGO_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90253b0L PE1_LOGO_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_logo_address                   :4 ;	//3:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_logo_load                      :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hif_logo_ai                        :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hif_logo_enable                    :1 ;	//15
}PE_M17_CE_PE1_LOGO_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90253b4L PE1_LOGO_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_logo_wdata_y                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_logo_wdata_x                   :10;	//25:16
}PE_M17_CE_PE1_LOGO_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90253b8L PE1_LOGO_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_gain_y0                     :8 ;	//7:0
	UINT32 region_gain_y1                     :8 ;	//15:8
	UINT32 region_gain_y2                     :8 ;	//23:16
	UINT32 region_gain_y3                     :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90253bcL PE1_LOGO_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 region_gain_y4                     :8 ;	//7:0
	UINT32 region_gain_y5                     :8 ;	//15:8
	UINT32 region_gain_y6                     :8 ;	//23:16
	UINT32 region_gain_y7                     :8 ;	//31:24
}PE_M17_CE_PE1_LOGO_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90253c0L PE1_LOGO_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_blend_alpha_delay         :8 ;	//7:0
}PE_M17_CE_PE1_LOGO_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90253c4L PE1_LOGO_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_in_hoffset                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_in_voffset                     :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90253c8L PE1_LOGO_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_in_hactive                     :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_in_vactive                     :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90253ccL PE1_LOGO_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_in_hsize                       :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_in_vsize                       :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90253d0L PE1_LOGO_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_out_pic_width                  :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_out_pic_height                 :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90253d4L PE1_LOGO_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_phase_off_h                    :6 ;	//5:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_phase_off_v                    :6 ;	//13:8
	UINT32 reserved02                         :17;	//reserved
	UINT32 reg_sampling_mode                  :1 ;	//31
}PE_M17_CE_PE1_LOGO_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90253d8L PE1_LOGO_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_numerator_h                    :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_numerator_v                    :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90253dcL PE1_LOGO_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denominator_h                  :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_denominator_v                  :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90253e0L PE1_LOGO_CTRL_1A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pic_rptr_man                   :2 ;	//1:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_pic_rptr_man_en                :1 ;	//3 
	UINT32 reg_pic_wptr_man                   :2 ;	//5:4
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_pic_wptr_man_en                :1 ;	//7 
	UINT32 reg_pic_data_man                   :2 ;	//9:8
	UINT32 reg_pic_rptr_on                    :1 ;	//10
	UINT32 reg_pic_wptr_on                    :1 ;	//11
	UINT32 reg_pic_wd_man                     :4 ;	//15:12
	UINT32 reg_pic_wd_man_on                  :1 ;	//16
	UINT32 reg_pic_rd_lsb_man                 :2 ;	//18:17
	UINT32 reg_ro_buf_wrcnt                   :10;	//28:19
	UINT32 reg_ro_buf_wrsel                   :1 ;	//29
}PE_M17_CE_PE1_LOGO_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc90253e4L PE1_LOGO_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ro_buf_rptr                        :2 ;	//1:0
	UINT32 ro_buf_wptr_d                      :2 ;	//3:2
	UINT32 ro_core_wd_ptr                     :2 ;	//5:4
	UINT32 ro_buf_rcnt                        :10;	//15:6
	UINT32 ro_buf_wcnt                        :10;	//25:16
	UINT32 ro_buf_wre_cnt                     :4 ;	//29:26
}PE_M17_CE_PE1_LOGO_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90253e8L PE1_LOGO_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ro_out_v_line                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 ro_in_v_line                       :12;	//27:16
}PE_M17_CE_PE1_LOGO_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90253ecL PE1_LOGO_CTRL_1B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win0_en                            :1 ;	//0:0
	UINT32 win1_en                            :1 ;	//1:1
	UINT32 win01_en                           :1 ;	//2:2
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 win_outside                        :1 ;	//6:6
	UINT32 win_en                             :1 ;	//7:7
	UINT32 bdr_alpha                          :5 ;	//12:8
	UINT32 bdr_wid                            :2 ;	//14:13
	UINT32 bdr_en                             :1 ;	//15:15
	UINT32 cr5                                :5 ;	//20:16
	UINT32 cb5                                :5 ;	//25:21
	UINT32 yy6                                :6 ;	//31:26
}PE_M17_CE_PE1_LOGO_CTRL_1B_T;
/*-----------------------------------------------------------------------------
                             0xc90253f0L PE1_LOGO_CTRL_1C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y0                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_1C_T;
/*-----------------------------------------------------------------------------
                             0xc90253f4L PE1_LOGO_CTRL_1D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y1                          :12;	//27:16
}PE_M17_CE_PE1_LOGO_CTRL_1D_T;
/*-----------------------------------------------------------------------------
                             0xc9025400L PE_PCC_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_gam22_en                   :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_pcc_gam045_en                  :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_pcc_en                         :1 ;	//8 
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_dither_en                      :1 ;	//12
	UINT32 reserved04                         :3 ;	//reserved
	UINT32 reg_dither_temporal_en             :1 ;	//16
}PE_M17_CE_PE_PCC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025404L PE1_PCC_COEF0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef0                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF0_T;
/*-----------------------------------------------------------------------------
                             0xc9025408L PE1_PCC_COEF1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef1                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF1_T;
/*-----------------------------------------------------------------------------
                             0xc902540cL PE1_PCC_COEF2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef2                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF2_T;
/*-----------------------------------------------------------------------------
                             0xc9025410L PE1_PCC_COEF3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef3                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF3_T;
/*-----------------------------------------------------------------------------
                             0xc9025414L PE1_PCC_COEF4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef4                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF4_T;
/*-----------------------------------------------------------------------------
                             0xc9025418L PE1_PCC_COEF5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef5                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF5_T;
/*-----------------------------------------------------------------------------
                             0xc902541cL PE1_PCC_COEF6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef6                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF6_T;
/*-----------------------------------------------------------------------------
                             0xc9025420L PE1_PCC_COEF7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef7                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF7_T;
/*-----------------------------------------------------------------------------
                             0xc9025424L PE1_PCC_COEF8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pcc_coef8                      :15;	//14:0
}PE_M17_CE_PE1_PCC_COEF8_T;
/*-----------------------------------------------------------------------------
                             0xc9025430L PE_DSE_Y_REGION_PT0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt0_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt0_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9025434L PE_DSE_Y_REGION_PT1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt1_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt1_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9025438L PE_DSE_Y_REGION_PT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt2_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt2_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc902543cL PE_DSE_Y_REGION_PT3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt3_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt3_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9025440L PE_DSE_Y_REGION_PT4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt4_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt4_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9025444L PE_DSE_Y_REGION_PT5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt5_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt5_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9025448L PE_DSE_Y_REGION_PT6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt6_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt6_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc902544cL PE_DSE_Y_REGION_PT7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt7_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt7_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_Y_REGION_PT7_T;
/*-----------------------------------------------------------------------------
                             0xc9025450L PE_DSE_H_REGION_PT0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt0_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt0_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9025454L PE_DSE_H_REGION_PT1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt1_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt1_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9025458L PE_DSE_H_REGION_PT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt2_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt2_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc902545cL PE_DSE_H_REGION_PT3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt3_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt3_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9025460L PE_DSE_H_REGION_PT4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt4_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt4_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9025464L PE_DSE_H_REGION_PT5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt5_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt5_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9025468L PE_DSE_H_REGION_PT6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt6_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt6_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc902546cL PE_DSE_H_REGION_PT7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt7_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt7_x                 :10;	//17:8
}PE_M17_CE_PE_DSE_H_REGION_PT7_T;
/*-----------------------------------------------------------------------------
                             0xc9025470L PE1_DRC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_en                         :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_drc_shp_apl_sel                :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_drc_rgb_sel                    :2 ;	//9:8
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 reg_drc_gm_mode                    :3 ;	//14:12
	UINT32 reserved04                         :1 ;	//reserved
	UINT32 reg_drc_lk_blf_apf                 :1 ;	//16
	UINT32 reserved05                         :3 ;	//reserved
	UINT32 reg_mode_2ch                       :1 ;	//20
	UINT32 reserved06                         :7 ;	//reserved
	UINT32 reg_dbg_disp_blf                   :1 ;	//28
	UINT32 reg_dbg_disp_lcont                 :1 ;	//29
	UINT32 reg_dbg_disp_reflect               :1 ;	//30
}PE_M17_CE_PE1_DRC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025474L PE1_DRC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_rw_sel                  :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_drc_gm_op_sel                  :1 ;	//4 
	UINT32 reserved02                         :11;	//reserved
	UINT32 reg_drc_gm_forced_sel              :1 ;	//16
	UINT32 reg_drc_gm_protected_sel           :1 ;	//17
}PE_M17_CE_PE1_DRC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025478L PE1_DRC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_bnh                        :7 ;	//6:0
	UINT32 reserved01                         :9 ;	//reserved
	UINT32 reg_drc_bnv                        :6 ;	//21:16
}PE_M17_CE_PE1_DRC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902547cL PE1_DRC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_bsh                        :9 ;	//8:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_drc_bsv                        :9 ;	//24:16
}PE_M17_CE_PE1_DRC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025480L PE1_DRC_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_apl2                    :10;	//9:0
	UINT32 reg_drc_gm_apl1                    :10;	//19:10
	UINT32 reg_drc_gm_apl0                    :10;	//29:20
}PE_M17_CE_PE1_DRC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025484L PE1_DRC_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_apl5                    :10;	//9:0
	UINT32 reg_drc_gm_apl4                    :10;	//19:10
	UINT32 reg_drc_gm_apl3                    :10;	//29:20
}PE_M17_CE_PE1_DRC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025488L PE1_DRC_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_blf_wei_cen                :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_drc_apl_iir                    :7 ;	//22:16
}PE_M17_CE_PE1_DRC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902548cL PE1_DRC_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_shp_clip_n                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_drc_shp_clip_p                 :12;	//27:16
}PE_M17_CE_PE1_DRC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025490L PE1_DRC_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_gn                     :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_th                     :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025494L PE1_DRC_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_adj_l                  :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_drc_apl_adj_h                  :8 ;	//23:16
}PE_M17_CE_PE1_DRC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025498L PE1_DRC_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_x2_p                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_x1_p                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc902549cL PE1_DRC_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_x4_p                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_x3_p                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90254a0L PE1_DRC_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y1_p                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y0_p                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90254a4L PE1_DRC_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y3_p                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y2_p                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90254a8L PE1_DRC_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y5_p                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y4_p                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90254acL PE1_DRC_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_x2_n                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_x1_n                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90254b0L PE1_DRC_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_x4_n                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_x3_n                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90254b4L PE1_DRC_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y1_n                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y0_n                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90254b8L PE1_DRC_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y3_n                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y2_n                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90254bcL PE1_DRC_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_apl_y5_n                   :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_drc_apl_y4_n                   :10;	//25:16
}PE_M17_CE_PE1_DRC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90254c0L PE1_DRC_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_lut_addr_clr               :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_drc_hfc_rd_sel                 :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_drc_vfc_rd_sel                 :1 ;	//8 
}PE_M17_CE_PE1_DRC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90254c4L PE1_DRC_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_lk_blf_hfc_data            :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90254c8L PE1_DRC_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_lk_blf_vfc_data            :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90254ccL PE1_DRC_CTRL_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_hfc_rdata                  :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90254d0L PE1_DRC_CTRL_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_vfc_rdata                  :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90254d4L PE1_DRC_CTRL_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_blf_wei_wdata              :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90254d8L PE1_DRC_CTRL_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_blf_wei_rdata              :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90254dcL PE1_DRC_CTRL_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_wdata                   :30;	//29:0
}PE_M17_CE_PE1_DRC_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90254e0L PE1_DRC_CTRL_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_rdata                   :30;	//29:0
}PE_M17_CE_PE1_DRC_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90254e4L PE1_DRC_CTRL_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_wdata                   :30;	//29:0
}PE_M17_CE_PE1_DRC_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90254e8L PE1_DRC_CTRL_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_rdata                   :30;	//29:0
}PE_M17_CE_PE1_DRC_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90254ecL PE1_DRC_CTRL_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_hpf_wei_wdata              :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90254f0L PE1_DRC_CTRL_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_hpf_wei_rdata              :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90254f4L PE1_DRC_CTRL_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_bl_apl_raddr_h             :7 ;	//6:0
	UINT32 reserved01                         :9 ;	//reserved
	UINT32 reg_drc_bl_apl_raddr_v             :6 ;	//21:16
}PE_M17_CE_PE1_DRC_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90254f8L PE1_DRC_CTRL_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_bl_apl_rdata               :10;	//9:0
}PE_M17_CE_PE1_DRC_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90254fcL PE1_DRC_CTRL_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_drc_gm_rw_sel                  :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_drc_gm_op_sel                  :1 ;	//4 
}PE_M17_CE_PE1_DRC_CTRL_35_T;

/*-----------------------------------------------------------------------------
                             0xc9025500L PE1_TOP_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 load_time                          :1 ;	//0 
	UINT32 load_enable                        :1 ;	//1 
	UINT32 load_type                          :1 ;	//2 
}PE_M17_CO_PE1_TOP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025504L PE1_TOP_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 width                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 height                             :12;	//27:16
}PE_M17_CO_PE1_TOP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025508L PE1_TOP_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_position                       :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 pe1_detour                         :1 ;	//2 
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 async_delay_mode                   :1 ;	//5 
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 mode_3d                            :1 ;	//7 
	UINT32 vdpulse_pos                        :12;	//19:8
	UINT32 line_masking_mode                  :2 ;	//21:20
	UINT32 reserved04                         :2 ;	//reserved
	UINT32 master_en                          :1 ;	//24
}PE_M17_CO_PE1_TOP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902550cL PE1_TOP_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 vcnt                               :12;	//11:0
	UINT32 va_pe1_in                          :1 ;	//12
	UINT32 va_pe1_out                         :1 ;	//13
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 vcnt2                              :12;	//27:16
}PE_M17_CO_PE1_TOP_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025510L PE1_TOP_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_to_cnt                           :12;	//11:0
}PE_M17_CO_PE1_TOP_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025520L PE1_FSW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 m0_y_h_12t_m_idx                   : 8 ;  //  7: 0
	UINT32 m0_y_v_12t_m_idx                   : 8 ;  // 15: 8
	UINT32 m0_y_h_12t_h_idx                   : 8 ;  // 23:16
	UINT32 m0_y_v_12t_h_idx                   : 8 ;  // 31:24
}PE_M17_CO_PE1_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025524L PE1_FSW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 m0_y_h_08t_f_idx                   : 8 ;  //  7: 0
	UINT32 m0_y_v_08t_f_idx                   : 8 ;  // 15: 8
	UINT32 reserved0                          : 8 ;  // 23:16
	UINT32 reserved1                          : 8 ;  // 31:24
}PE_M17_CO_PE1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025528L PE1_FSW_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 m0_c_h_12t_m_idx                   : 8 ;  //  7: 0
	UINT32 m0_c_v_12t_m_idx                   : 8 ;  // 15: 8
	UINT32 m0_c_h_12t_h_idx                   : 8 ;  // 23:16
	UINT32 m0_c_v_12t_h_idx                   : 8 ;  // 31:24
}PE_M17_CO_PE1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902552cL PE1_FSW_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 g0_y_vh_08t_m_idx                   : 8 ;  //  7: 0
	UINT32 g0_c_vh_04t_h_idx                   : 8 ;  // 15: 8
	UINT32 g1_y_vh_08t_m_idx                   : 8 ;  // 23:16
	UINT32 g1_c_vh_04t_h_idx                   : 8 ;  // 31:24
}PE_M17_CO_PE1_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025534L PE1_WIN2_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win0_en                            :1 ;	//0 
	UINT32 win1_en                            :1 ;	//1 
	UINT32 win01_en                           :1 ;	//2 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 win_outside                        :1 ;	//6 
	UINT32 win_en                             :1 ;	//7 
	UINT32 bdr_alpha                          :5 ;	//12:8
	UINT32 bdr_wid                            :2 ;	//14:13
	UINT32 bdr_en                             :1 ;	//15
	UINT32 cr5                                :5 ;	//20:16
	UINT32 cb5                                :5 ;	//25:21
	UINT32 yy6                                :6 ;	//31:26
}PE_M17_CO_PE1_WIN2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025538L PE1_WIN2_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y0                          :12;	//27:16
}PE_M17_CO_PE1_WIN2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc902553cL PE1_WIN2_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w0_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w0_y1                          :12;	//27:16
}PE_M17_CO_PE1_WIN2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9025540L PE1_WIN2_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x0                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y0                          :12;	//27:16
}PE_M17_CO_PE1_WIN2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025544L PE1_WIN2_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_w1_x1                          :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_w1_y1                          :12;	//27:16
}PE_M17_CO_PE1_WIN2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025550L PE1_APL_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_win_ctrl_x0                    :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 apl_win_ctrl_y0                    :12;	//27:16
}PE_M17_CO_PE1_APL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025554L PE1_APL_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_win_ctrl_x1                    :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 apl_win_ctrl_y1                    :12;	//27:16
}PE_M17_CO_PE1_APL_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025558L PE1_APL_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_position                       :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 act_win_mode                       :1 ;	//8 
}PE_M17_CO_PE1_APL_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902555cL PE1_APL_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_cb                             :10;	//9:0
	UINT32 apl_yg                             :10;	//19:10
	UINT32 apl_cr                             :10;	//29:20
}PE_M17_CO_PE1_APL_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025560L PE1_APL_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 apl_cb_other_side                  :10;	//9:0
	UINT32 apl_yg_other_side                  :10;	//19:10
	UINT32 apl_cr_other_side                  :10;	//29:20
}PE_M17_CO_PE1_APL_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025570L PE1_TPG_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_enable                         :1 ;	//0 
	UINT32 pattern_type                       :2 ;	//2:1
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 blend_alpha                        :4 ;	//7:4
	UINT32 blt_size_x                         :12;	//19:8
	UINT32 blt_size_y                         :12;	//31:20
}PE_M17_CO_PE1_TPG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025574L PE1_TPG_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 gradation_stride                   :7 ;	//6:0
	UINT32 gradation_direction                :1 ;	//7 
	UINT32 gradation_bar_0_en                 :1 ;	//8 
	UINT32 gradation_bar_1_en                 :1 ;	//9 
	UINT32 gradation_bar_2_en                 :1 ;	//10
	UINT32 gradation_bar_3_en                 :1 ;	//11
}PE_M17_CO_PE1_TPG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025578L PE1_TPG_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 patch_0_en                         :1 ;	//0 
	UINT32 patch_1_en                         :1 ;	//1 
	UINT32 patch_2_en                         :1 ;	//2 
	UINT32 patch_3_en                         :1 ;	//3 
	UINT32 patch_4_en                         :1 ;	//4 
	UINT32 patch_5_en                         :1 ;	//5 
	UINT32 patch_6_en                         :1 ;	//6 
	UINT32 patch_7_en                         :1 ;	//7 
	UINT32 patch_8_en                         :1 ;	//8 
	UINT32 patch_9_en                         :1 ;	//9 
	UINT32 patch_10_en                        :1 ;	//10
	UINT32 patch_11_en                        :1 ;	//11
	UINT32 patch_12_en                        :1 ;	//12
	UINT32 patch_13_en                        :1 ;	//13
	UINT32 patch_14_en                        :1 ;	//14
	UINT32 patch_15_en                        :1 ;	//15
}PE_M17_CO_PE1_TPG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902557cL PE1_TPG_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 patch_0_inout_sel                  :1 ;	//0 
	UINT32 patch_1_inout_sel                  :1 ;	//1 
	UINT32 patch_2_inout_sel                  :1 ;	//2 
	UINT32 patch_3_inout_sel                  :1 ;	//3 
	UINT32 patch_4_inout_sel                  :1 ;	//4 
	UINT32 patch_5_inout_sel                  :1 ;	//5 
	UINT32 patch_6_inout_sel                  :1 ;	//6 
	UINT32 patch_7_inout_sel                  :1 ;	//7 
	UINT32 patch_8_inout_sel                  :1 ;	//8 
	UINT32 patch_9_inout_sel                  :1 ;	//9 
	UINT32 patch_10_inout_sel                 :1 ;	//10
	UINT32 patch_11_inout_sel                 :1 ;	//11
	UINT32 patch_12_inout_sel                 :1 ;	//12
	UINT32 patch_13_inout_sel                 :1 ;	//13
	UINT32 patch_14_inout_sel                 :1 ;	//14
	UINT32 patch_15_inout_sel                 :1 ;	//15
}PE_M17_CO_PE1_TPG_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025580L PE1_TPG_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :10;	//9:0
	UINT32 bg_color_b                         :10;	//19:10
	UINT32 bg_color_g                         :10;	//29:20
}PE_M17_CO_PE1_TPG_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025584L PE1_TPG_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_indir_addr                     :7 ;	//6:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 tpg_indir_ai_en                    :1 ;	//12
}PE_M17_CO_PE1_TPG_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025588L PE1_TPG_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tpg_indir_data;							//31:0
}PE_M17_CO_PE1_TPG_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90255a0L PE1_VSPYC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 graycolor_enable                   :1 ;	//1 
	UINT32 color_only_enable                  :1 ;	//2 
	UINT32 cb_info                            :1 ;	//3 
	UINT32 cr_info                            :1 ;	//4 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 center_position                    :8 ;	//15:8
	UINT32 contrast                           :10;	//25:16
}PE_M17_CO_PE1_VSPYC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90255a4L PE1_VSPYC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 saturation                         :8 ;	//15:8
	UINT32 brightness                         :10;	//25:16
}PE_M17_CO_PE1_VSPYC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90255b0L PE1_DEBUG_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable_debug_mode                  :1 ;	//0 
	UINT32 status_enable                      :1 ;	//1 
	UINT32 debug_mode                         :1 ;	//2 
	UINT32 reserved01                         :17;	//reserved
	UINT32 show_apl                           :1 ;	//20
}PE_M17_CO_PE1_DEBUG_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90255b4L PE1_DEBUG_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 yc_debug_en                        :1 ;	//0 
	UINT32 force_yy_enable                    :1 ;	//1 
	UINT32 force_cb_enable                    :1 ;	//2 
	UINT32 force_cr_enable                    :1 ;	//3 
	UINT32 yc_debug_mode_sel                  :3 ;	//6:4
}PE_M17_CO_PE1_DEBUG_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90255b8L PE1_DEBUG_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 force_yy                           :10;	//9:0
	UINT32 force_cb                           :10;	//19:10
	UINT32 force_cr                           :10;	//29:20
}PE_M17_CO_PE1_DEBUG_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90255e0L PE1_CEN_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cen_detour                         :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 select_hsv                         :1 ;	//2 
	UINT32 select_rgb                         :1 ;	//3 
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 vsp_sel                            :1 ;	//5 
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 reg_cen_bypass                     :1 ;	//7 
	UINT32 reg_cen_debug_mode                 :1 ;	//8 
	UINT32 reserved04                         :1 ;	//reserved
	UINT32 core_1st__gain_disable             :1 ;	//10
	UINT32 core_2nd_gain_disable              :1 ;	//11
	UINT32 reserved05                         :1 ;	//reserved
	UINT32 debugging_mode_core                :2 ;	//14:13
	UINT32 reserved06                         :1 ;	//reserved
	UINT32 demo_mode                          :8 ;	//23:16
	UINT32 reserved07                         :7 ;	//reserved
	UINT32 win_control_mode                   :1 ;	//31
}PE_M17_CO_PE1_CEN_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90255e4L PE1_CEN_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 show_color_region0                 :1 ;	//0 
	UINT32 show_color_region1                 :1 ;	//1 
	UINT32 show_color_region2                 :1 ;	//2 
	UINT32 show_color_region3                 :1 ;	//3 
	UINT32 show_color_region4                 :1 ;	//4 
	UINT32 show_color_region5                 :1 ;	//5 
	UINT32 show_color_region6                 :1 ;	//6 
	UINT32 show_color_region7                 :1 ;	//7 
	UINT32 show_color_region8                 :1 ;	//8 
	UINT32 show_color_region9                 :1 ;	//9 
	UINT32 show_color_region10                :1 ;	//10
	UINT32 show_color_region11                :1 ;	//11
	UINT32 show_color_region12                :1 ;	//12
	UINT32 show_color_region13                :1 ;	//13
	UINT32 show_color_region14                :1 ;	//14
	UINT32 show_color_region15                :1 ;	//15
	UINT32 color_region_en0                   :1 ;	//16
	UINT32 color_region_en1                   :1 ;	//17
	UINT32 color_region_en2                   :1 ;	//18
	UINT32 color_region_en3                   :1 ;	//19
	UINT32 color_region_en4                   :1 ;	//20
	UINT32 color_region_en5                   :1 ;	//21
	UINT32 color_region_en6                   :1 ;	//22
	UINT32 color_region_en7                   :1 ;	//23
	UINT32 color_region_en8                   :1 ;	//24
	UINT32 color_region_en9                   :1 ;	//25
	UINT32 color_region_en10                  :1 ;	//26
	UINT32 color_region_en11                  :1 ;	//27
	UINT32 color_region_en12                  :1 ;	//28
	UINT32 color_region_en13                  :1 ;	//29
	UINT32 color_region_en14                  :1 ;	//30
	UINT32 color_region_en15                  :1 ;	//31
}PE_M17_CO_PE1_CEN_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90255e8L PE1_CEN_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ihsv_sgain                         :8 ;	//7:0
	UINT32 ihsv_vgain                         :8 ;	//15:8
}PE_M17_CO_PE1_CEN_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90255ecL PE1_CEN_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ihsv_hoffset                       :8 ;	//7:0
	UINT32 ihsv_soffset                       :8 ;	//15:8
	UINT32 ihsv_voffset                       :8 ;	//23:16
}PE_M17_CO_PE1_CEN_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90255f0L PE1_CEN_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr0                :8 ;	//7:0
	UINT32 reg_master_gain_cr1                :8 ;	//15:8
	UINT32 reg_master_gain_cr2                :8 ;	//23:16
	UINT32 reg_master_gain_cr3                :8 ;	//31:24
}PE_M17_CO_PE1_CEN_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90255f4L PE1_CEN_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr4                :8 ;	//7:0
	UINT32 reg_master_gain_cr5                :8 ;	//15:8
	UINT32 reg_master_gain_cr6                :8 ;	//23:16
	UINT32 reg_master_gain_cr7                :8 ;	//31:24
}PE_M17_CO_PE1_CEN_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90255f8L PE1_CEN_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr8                :8 ;	//7:0
	UINT32 reg_master_gain_cr9                :8 ;	//15:8
	UINT32 reg_master_gain_cr10               :8 ;	//23:16
	UINT32 reg_master_gain_cr11               :8 ;	//31:24
}PE_M17_CO_PE1_CEN_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90255fcL PE1_CEN_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_master_gain_cr12               :8 ;	//7:0
	UINT32 reg_master_gain_cr13               :8 ;	//15:8
	UINT32 reg_master_gain_cr14               :8 ;	//23:16
	UINT32 reg_master_gain_cr15               :8 ;	//31:24
}PE_M17_CO_PE1_CEN_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025610L PE1_CEN_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_address                    :8 ;	//7:0
	UINT32 hif_cen_ai_sel                     :3 ;	//10:8
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 hif_cen_ai                         :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_cen_enable                     :1 ;	//15
}PE_M17_CO_PE1_CEN_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025614L PE1_CEN_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_y_wdata                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_cen_x_wdata                    :10;	//25:16
}PE_M17_CO_PE1_CEN_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025618L PE1_CEN_DELTA_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_delta_address              :5 ;	//4:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 hif_cen_delta_ai                   :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_cen_delta_enable               :1 ;	//15
}PE_M17_CO_PE1_CEN_DELTA_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902561cL PE1_CEN_DELTA_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_cen_vr_data                    :8 ;	//7:0
	UINT32 hif_cen_sb_data                    :8 ;	//15:8
	UINT32 hif_cen_hg_data                    :8 ;	//23:16
}PE_M17_CO_PE1_CEN_DELTA_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025620L PE1_DCE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dynamic_contrast_en                :1 ;	//0 
	UINT32 hist_bin_mode                      :2 ;	//2:1
	UINT32 hist_clear                         :1 ;	//3 
	UINT32 window01_enable                    :1 ;	//4 
	UINT32 window0_enable                     :1 ;	//5 
	UINT32 window1_enable                     :1 ;	//6 
	UINT32 window_acquire                     :1 ;	//7 
	UINT32 color_region0_sel                  :1 ;	//8 
	UINT32 color_region1_sel                  :1 ;	//9 
	UINT32 color_region2_sel                  :1 ;	//10
	UINT32 color_region3_sel                  :1 ;	//11
	UINT32 color_region4_sel                  :1 ;	//12
	UINT32 color_region5_sel                  :1 ;	//13
	UINT32 color_region6_sel                  :1 ;	//14
	UINT32 color_region7_sel                  :1 ;	//15
	UINT32 color_region8_sel                  :1 ;	//16
	UINT32 color_region9_sel                  :1 ;	//17
	UINT32 color_region10_sel                 :1 ;	//18
	UINT32 color_region11_sel                 :1 ;	//19
	UINT32 color_region12_sel                 :1 ;	//20
	UINT32 color_region13_sel                 :1 ;	//21
	UINT32 color_region14_sel                 :1 ;	//22
	UINT32 color_region15_sel                 :1 ;	//23
	UINT32 dce_domain_sel                     :1 ;	//24
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 window_mode_enable                 :1 ;	//26
	UINT32 window_inout_sel                   :1 ;	//27
	UINT32 histogram_mode                     :2 ;	//29:28
}PE_M17_CO_PE1_DCE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025624L PE1_DCE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_bin_min_position              :8 ;	//7:0
	UINT32 hist_bin_max_position              :8 ;	//15:8
	UINT32 color_region_gain                  :8 ;	//23:16
}PE_M17_CO_PE1_DCE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025628L PE1_DCE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 color_region_en                    :1 ;	//0 
	UINT32 color_debug_en                     :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 y_grad_gain                        :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 cb_grad_gain                       :2 ;	//9:8
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 cr_grad_gain                       :2 ;	//13:12
}PE_M17_CO_PE1_DCE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902562cL PE1_DCE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 y_range_max                        :10;	//25:16
}PE_M17_CO_PE1_DCE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025630L PE1_DCE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cb_range_min                       :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 cb_range_max                       :10;	//25:16
}PE_M17_CO_PE1_DCE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025634L PE1_DCE_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_range_min                       :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 cr_range_max                       :10;	//25:16
}PE_M17_CO_PE1_DCE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025638L PE1_DCE_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_address                    :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hif_dce_load                       :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hif_dce_ai                         :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hif_dce_enable                     :1 ;	//15
}PE_M17_CO_PE1_DCE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902563cL PE1_DCE_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_wdata_y                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dyc_wdata_x                    :10;	//25:16
}PE_M17_CO_PE1_DCE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025640L PE1_DCE_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dyc_wdata_y_32nd               :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dyc_wdata_x_32nd               :10;	//25:16
}PE_M17_CO_PE1_DCE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025644L PE1_DCE_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 dce_ktd_csc_sel                    :1 ;	//1 
}PE_M17_CO_PE1_DCE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025648L PE1_DCE_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :5 ;	//4:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
	UINT32 hif_status_address                 :3 ;	//18:16
	UINT32 reserved03                         :9 ;	//reserved
	UINT32 hif_status_ai                      :1 ;	//28
	UINT32 hif_mask                           :1 ;	//29
}PE_M17_CO_PE1_DCE_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc902564cL PE1_DCE_HIST_IA_DATA1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status0                       :23;	//22:0
}PE_M17_CO_PE1_DCE_HIST_IA_DATA1_T;
/*-----------------------------------------------------------------------------
                             0xc9025650L PE1_DCE_HIST_IA_DATA2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status1                       :29;	//28:0
}PE_M17_CO_PE1_DCE_HIST_IA_DATA2_T;
/*-----------------------------------------------------------------------------
                             0xc9025654L PE1_DCE_CHR_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dce_chr_gain2                      :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 dce_chr_gain1                      :10;	//25:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 chroma_gain_enable                 :1 ;	//28
}PE_M17_CO_PE1_DCE_CHR_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc9025658L PE1_DCE_CHR_ALPHA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dce_chr_alpha2                     :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 dce_chr_alpha1                     :10;	//25:16
}PE_M17_CO_PE1_DCE_CHR_ALPHA_T;
/*-----------------------------------------------------------------------------
                             0xc9025660L PE1_DSE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dynamic_saturation_en              :1 ;	//0 
	UINT32 window_mode_enable                 :1 ;	//1 
	UINT32 window_inout_sel                   :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 window01_enable                    :1 ;	//4 
	UINT32 window0_enable                     :1 ;	//5 
	UINT32 window1_enable                     :1 ;	//6 
	UINT32 window_acquire                     :1 ;	//7 
	UINT32 color_region0_sel                  :1 ;	//8 
	UINT32 color_region1_sel                  :1 ;	//9 
	UINT32 color_region2_sel                  :1 ;	//10
	UINT32 color_region3_sel                  :1 ;	//11
	UINT32 color_region4_sel                  :1 ;	//12
	UINT32 color_region5_sel                  :1 ;	//13
	UINT32 color_region6_sel                  :1 ;	//14
	UINT32 color_region7_sel                  :1 ;	//15
	UINT32 color_region8_sel                  :1 ;	//16
	UINT32 color_region9_sel                  :1 ;	//17
	UINT32 color_region10_sel                 :1 ;	//18
	UINT32 color_region11_sel                 :1 ;	//19
	UINT32 color_region12_sel                 :1 ;	//20
	UINT32 color_region13_sel                 :1 ;	//21
	UINT32 color_region14_sel                 :1 ;	//22
	UINT32 color_region15_sel                 :1 ;	//23
}PE_M17_CO_PE1_DSE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025664L PE1_DSE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dse_cr_mode_sel                :1 ;	//0 
	UINT32 reg_yh_cr_en                       :1 ;	//1 
	UINT32 reg_yh_debug                       :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_dse_y_grad                       :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 r_dse_h_grad                       :2 ;	//9:8
	UINT32 reserved03                         :14;	//reserved
	UINT32 color_region_gain                  :8 ;	//31:24
}PE_M17_CO_PE1_DSE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025668L PE1_DSE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_wdata_y_32nd               :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dse_wdata_x_32nd               :10;	//25:16
}PE_M17_CO_PE1_DSE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902566cL PE1_DSE_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_address                    :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 hif_dse_load                       :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 hif_dse_ai                         :1 ;	//12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 hif_dse_enable                     :1 ;	//15
}PE_M17_CO_PE1_DSE_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9025670L PE1_DSE_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_dse_wdata_y                    :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 hif_dse_wdata_x                    :10;	//25:16
}PE_M17_CO_PE1_DSE_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025674L PE1_DSE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 y_range_max                        :10;	//25:16
}PE_M17_CO_PE1_DSE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025678L PE1_DSE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 h_range_min                        :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 h_range_max                        :10;	//25:16
}PE_M17_CO_PE1_DSE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025680L PE1_CW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cw_en                              :1 ;	//0 
}PE_M17_CO_PE1_CW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025684L PE1_CW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 user_ctrl_g_gain                   :8 ;	//7:0
	UINT32 user_ctrl_b_gain                   :8 ;	//15:8
	UINT32 user_ctrl_r_gain                   :8 ;	//23:16
}PE_M17_CO_PE1_CW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025690L PE1_CW_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 color_region0_sel                  :1 ;	//0 
	UINT32 color_region1_sel                  :1 ;	//1 
	UINT32 color_region2_sel                  :1 ;	//2 
	UINT32 color_region3_sel                  :1 ;	//3 
	UINT32 color_region4_sel                  :1 ;	//4 
	UINT32 color_region5_sel                  :1 ;	//5 
	UINT32 color_region6_sel                  :1 ;	//6 
	UINT32 color_region7_sel                  :1 ;	//7 
	UINT32 color_region8_sel                  :1 ;	//8 
	UINT32 color_region9_sel                  :1 ;	//9 
	UINT32 color_region10_sel                 :1 ;	//10
	UINT32 color_region11_sel                 :1 ;	//11
	UINT32 color_region12_sel                 :1 ;	//12
	UINT32 color_region13_sel                 :1 ;	//13
	UINT32 color_region14_sel                 :1 ;	//14
	UINT32 color_region15_sel                 :1 ;	//15
	UINT32 color_region_gain                  :8 ;	//23:16
}PE_M17_CO_PE1_CW_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90256a0L PE1_CONV_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 conv_3d_r_en                       :1 ;	//0 
	UINT32 fpacking_r_en                      :1 ;	//1 
	UINT32 ffmode_r_en                        :1 ;	//2 
	UINT32 load_parity_r                      :1 ;	//3 
	UINT32 conv_3d_l_en                       :1 ;	//4 
	UINT32 fpacking_l_en                      :1 ;	//5 
	UINT32 ffmode_l_en                        :1 ;	//6 
	UINT32 load_parity_l                      :1 ;	//7 
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 start_parity_r                     :1 ;	//16
	UINT32 start_parity_l                     :1 ;	//17
}PE_M17_CO_PE1_CONV_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90256a4L PE1_CONV_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 offset_r                           :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 offset_l                           :8 ;	//23:16
}PE_M17_CO_PE1_CONV_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90256a8L PE1_CONV_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_grey                      :8 ;	//7:0
}PE_M17_CO_PE1_CONV_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90256acL PE1_CONV_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CO_PE1_CONV_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90256b0L PE1_CONV_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CO_PE1_CONV_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc90256b4L PE1_CONV_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_CONV_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc90256b8L PE1_CONV_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_CONV_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90256bcL PE1_CONV_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CO_PE1_CONV_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90256c0L PE1_CONV_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CO_PE1_CONV_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc90256c4L PE1_CONV_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CO_PE1_CONV_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc90256c8L PE1_CONV_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_CONV_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc90256ccL PE1_CONV_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_CONV_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90256d0L PE1_CONV_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CO_PE1_CONV_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90256d4L PE1_CONV_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mux3d_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_out_mux                        :2 ;	//5:4
	UINT32 start_parity                       :1 ;	//6 
	UINT32 load_parity                        :1 ;	//7 
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 alpha1_gain                        :8 ;	//23:16
	UINT32 alpha0_gain                        :8 ;	//31:24
}PE_M17_CO_PE1_CONV_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90256d8L PE1_CONV_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_l_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_l_window_v_en                  :1 ;	//31
}PE_M17_CO_PE1_CONV_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90256dcL PE1_CONV_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CO_PE1_CONV_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90256e0L PE1_CONV_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_r_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_r_window_v_en                  :1 ;	//31
}PE_M17_CO_PE1_CONV_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90256e4L PE1_CONV_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CO_PE1_CONV_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90256e8L PE1_CONV_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :8 ;	//7:0
	UINT32 bg_color_b                         :8 ;	//15:8
	UINT32 bg_color_g                         :8 ;	//23:16
}PE_M17_CO_PE1_CONV_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90256f0L PE1_MUTE_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CO_PE1_MUTE_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90256f4L PE1_MUTE_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CO_PE1_MUTE_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90256f8L PE1_MUTE_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_MUTE_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90256fcL PE1_MUTE_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_MUTE_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025700L PE1_MUTE_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CO_PE1_MUTE_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025704L PE1_MUTE_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_xpos                       :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_ypos                       :12;	//27:16
	UINT32 pxl_rep_in                         :1 ;	//28
	UINT32 pxl_rep_out                        :1 ;	//29
}PE_M17_CO_PE1_MUTE_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025708L PE1_MUTE_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_width                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 pxl_rep_height                     :12;	//27:16
}PE_M17_CO_PE1_MUTE_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902570cL PE1_MUTE_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_MUTE_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025710L PE1_MUTE_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pxl_rep_value_g                    :10;	//9:0
	UINT32 pxl_rep_value_b                    :10;	//19:10
	UINT32 pxl_rep_value_r                    :10;	//29:20
}PE_M17_CO_PE1_MUTE_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025714L PE1_MUTE_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_col_fil_g_valid                :1 ;	//0 
	UINT32 reg_col_fil_b_valid                :1 ;	//1 
	UINT32 reg_col_fil_r_valid                :1 ;	//2 
	UINT32 reg_col_fil_g_nvalid               :1 ;	//3 
	UINT32 reg_col_fil_b_nvalid               :1 ;	//4 
	UINT32 reg_col_fil_r_nvalid               :1 ;	//5 
}PE_M17_CO_PE1_MUTE_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025718L PE1_MUTE_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mux3d_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_out_mux                        :2 ;	//5:4
	UINT32 start_parity                       :1 ;	//6 
	UINT32 reserved02                         :9 ;	//reserved
	UINT32 alpha1_gain                        :8 ;	//23:16
	UINT32 alpha0_gain                        :8 ;	//31:24
}PE_M17_CO_PE1_MUTE_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902571cL PE1_MUTE_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_l_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_l_window_v_en                  :1 ;	//31
}PE_M17_CO_PE1_MUTE_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9025720L PE1_MUTE_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CO_PE1_MUTE_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9025724L PE1_MUTE_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 mux_r_window_h_en                  :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 mux_r_window_v_en                  :1 ;	//31
}PE_M17_CO_PE1_MUTE_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9025728L PE1_MUTE_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CO_PE1_MUTE_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc902572cL PE1_MUTE_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bg_color_r                         :8 ;	//7:0
	UINT32 bg_color_b                         :8 ;	//15:8
	UINT32 bg_color_g                         :8 ;	//23:16
}PE_M17_CO_PE1_MUTE_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90257a0L PE1_LRCR_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 adjust_en                          :1 ;	//1 
	UINT32 protection_en                      :1 ;	//2 
	UINT32 adjust_en2                         :1 ;	//3 
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 ff_mode_en                         :1 ;	//8 
	UINT32 ff_mode_parity                     :1 ;	//9 
	UINT32 ll_mode_enable                     :1 ;	//10
	UINT32 line_parity_select                 :1 ;	//11
	UINT32 lrcr_out_mux                       :1 ;	//12
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_lrcr_gain                      :4 ;	//19:16
}PE_M17_CO_PE1_LRCR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90257b8L PE1_LRCR_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 active_window_h_en                 :1 ;	//15
	UINT32 y0                                 :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 active_window_v_en                 :1 ;	//31
}PE_M17_CO_PE1_LRCR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc90257bcL PE1_LRCR_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_CO_PE1_LRCR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc90257c0L G_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CO_G_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90257c4L B_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CO_B_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90257c8L R_ADJ_GAIN                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 clock_gating_disable               :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 bright                             :10;	//13:4
	UINT32 contrast                           :10;	//23:14
	UINT32 center_position                    :8 ;	//31:24
}PE_M17_CO_R_ADJ_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc90257ccL HIST_CTRL_MODE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bin_mode                           :2 ;	//1:0
	UINT32 histo_ctrl                         :2 ;	//3:2
	UINT32 reserved01                         :19;	//reserved
	UINT32 histo_clear                        :1 ;	//23
}PE_M17_CO_HIST_CTRL_MODE_T;
/*-----------------------------------------------------------------------------
                             0xc90257d0L PE1_L_G_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_L_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257d4L PE1_L_G_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_L_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90257d8L PE1_L_B_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_L_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257dcL PE1_L_B_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_L_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90257e0L PE1_L_R_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_L_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257e4L PE1_L_R_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_L_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90257e8L PE1_R_G_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_R_G_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257ecL PE1_R_G_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_R_G_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90257f0L PE1_R_B_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_R_B_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257f4L PE1_R_B_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_R_B_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90257f8L PE1_R_R_HIST_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 hif_hist_enable                    :1 ;	//15
}PE_M17_CO_PE1_R_R_HIST_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90257fcL PE1_R_R_HIST_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status;	//31:0
}PE_M17_CO_PE1_R_R_HIST_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9025810L PE1_BT20_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef1                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef0                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025814L PE1_BT20_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef3a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef2                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025818L PE1_BT20_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef5a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef4a                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902581cL PE1_BT20_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef7a                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef6a                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025820L PE1_BT20_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst0                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_coef8a                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025824L PE1_BT20_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst2                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_ofst1                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025828L PE1_BT20_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_ofst3                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_2x3_ofst4                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902582cL PE1_BT20_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_en                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 r_degamma_en                       :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 r_1x3_en                           :1 ;	//8 
	UINT32 reserved03                         :7 ;	//reserved
	UINT32 r_2x3_ofst5                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025830L PE1_BT20_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 dither_en                          :1 ;	//0 
	UINT32 decontour_en                       :1 ;	//1 
	UINT32 dither_random_freeze_en            :1 ;	//2 
	UINT32 demo_pattern_enable                :1 ;	//3 
	UINT32 bit_mode                           :2 ;	//5:4
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 decontour_gain_r                   :8 ;	//15:8
	UINT32 decontour_gain_g                   :8 ;	//23:16
	UINT32 decontour_gain_b                   :8 ;	//31:24
}PE_M17_CO_PE1_BT20_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025834L PE1_BT20_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef3b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_csc_cb_th                      :10;	//25:16
}PE_M17_CO_PE1_BT20_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025838L PE1_BT20_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef5b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef4b                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902583cL PE1_BT20_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_2x3_coef7b                       :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_2x3_coef6b                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9025840L PE1_BT20_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_csc_cr_th                      :10;	//9:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 r_2x3_coef8b                       :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc9025844L PE1_BT20_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef1                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef0                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc9025848L PE1_BT20_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef3                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef2                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc902584cL PE1_BT20_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef5                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef4                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc9025850L PE1_BT20_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_coef7                        :15;	//14:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 r_1x3_coef6                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9025854L PE1_BT20_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 r_1x3_coef8                        :15;	//30:16
}PE_M17_CO_PE1_BT20_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9025858L PE1_BT20_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst1                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst0                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc902585cL PE1_BT20_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst3                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst2                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9025860L PE1_BT20_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_1x3_ofst5                        :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 r_1x3_ofst4                        :11;	//26:16
}PE_M17_CO_PE1_BT20_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9025870L PE1_LOGO_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_00;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9025874L PE1_LOGO_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_01;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9025878L PE1_LOGO_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_02;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc902587cL PE1_LOGO_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_03;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9025880L PE1_LOGO_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_04;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9025884L PE1_LOGO_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_05;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9025888L PE1_LOGO_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_06;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc902588cL PE1_LOGO_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_07;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9025890L PE1_LOGO_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_08;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9025894L PE1_LOGO_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_09;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9025898L PE1_LOGO_CTRL_0A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0a;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc902589cL PE1_LOGO_CTRL_0B                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0b;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc90258a0L PE1_LOGO_CTRL_0C                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0c;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0C_T;
/*-----------------------------------------------------------------------------
                             0xc90258a4L PE1_LOGO_CTRL_0D                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0d;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0D_T;
/*-----------------------------------------------------------------------------
                             0xc90258a8L PE1_LOGO_CTRL_0E                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0e;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0E_T;
/*-----------------------------------------------------------------------------
                             0xc90258acL PE1_LOGO_CTRL_0F                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_0f;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_0F_T;
/*-----------------------------------------------------------------------------
                             0xc90258b0L PE1_LOGO_IA_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl;	//31:0
}PE_M17_CO_PE1_LOGO_IA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90258b4L PE1_LOGO_IA_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_stat;	//31:0
}PE_M17_CO_PE1_LOGO_IA_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc90258b8L PE1_LOGO_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_10;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90258bcL PE1_LOGO_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_11;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90258c0L PE1_LOGO_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_12;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90258c4L PE1_LOGO_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_13;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90258c8L PE1_LOGO_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_14;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90258ccL PE1_LOGO_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_15;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90258d0L PE1_LOGO_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_16;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90258d4L PE1_LOGO_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_17;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90258d8L PE1_LOGO_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_18;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90258dcL PE1_LOGO_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_19;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90258e0L PE1_LOGO_CTRL_1A                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_1a;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_1A_T;
/*-----------------------------------------------------------------------------
                             0xc90258e4L PE1_LOGO_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_stat_00;	//31:0
}PE_M17_CO_PE1_LOGO_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90258e8L PE1_LOGO_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_stat_01;	//31:0
}PE_M17_CO_PE1_LOGO_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90258ecL PE1_LOGO_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_20;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90258f0L PE1_LOGO_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_21;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90258f4L PE1_LOGO_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_logo_ctrl_22;	//31:0
}PE_M17_CO_PE1_LOGO_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc9025930L PE_DSE_Y_REGION_PT0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt0_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt0_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9025934L PE_DSE_Y_REGION_PT1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt1_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt1_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9025938L PE_DSE_Y_REGION_PT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt2_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt2_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc902593cL PE_DSE_Y_REGION_PT3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt3_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt3_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9025940L PE_DSE_Y_REGION_PT4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt4_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt4_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9025944L PE_DSE_Y_REGION_PT5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt5_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt5_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9025948L PE_DSE_Y_REGION_PT6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt6_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt6_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc902594cL PE_DSE_Y_REGION_PT7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_region_pt7_y                 :8 ;	//7:0
	UINT32 reg_y_region_pt7_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_Y_REGION_PT7_T;
/*-----------------------------------------------------------------------------
                             0xc9025950L PE_DSE_H_REGION_PT0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt0_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt0_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT0_T;
/*-----------------------------------------------------------------------------
                             0xc9025954L PE_DSE_H_REGION_PT1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt1_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt1_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT1_T;
/*-----------------------------------------------------------------------------
                             0xc9025958L PE_DSE_H_REGION_PT2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt2_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt2_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT2_T;
/*-----------------------------------------------------------------------------
                             0xc902595cL PE_DSE_H_REGION_PT3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt3_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt3_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT3_T;
/*-----------------------------------------------------------------------------
                             0xc9025960L PE_DSE_H_REGION_PT4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt4_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt4_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT4_T;
/*-----------------------------------------------------------------------------
                             0xc9025964L PE_DSE_H_REGION_PT5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt5_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt5_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT5_T;
/*-----------------------------------------------------------------------------
                             0xc9025968L PE_DSE_H_REGION_PT6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt6_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt6_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT6_T;
/*-----------------------------------------------------------------------------
                             0xc902596cL PE_DSE_H_REGION_PT7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_h_region_pt7_y                 :8 ;	//7:0
	UINT32 reg_h_region_pt7_x                 :10;	//17:8
}PE_M17_CO_PE_DSE_H_REGION_PT7_T;

typedef struct
{ 
	PE_M17_CE_PE1_TOP_CTRL_00_T                         pe1_top_ctrl_00;	//0x0000
	PE_M17_CE_PE1_TOP_CTRL_01_T                         pe1_top_ctrl_01;	//0x0004
	PE_M17_CE_PE1_TOP_CTRL_02_T                         pe1_top_ctrl_02;	//0x0008
	PE_M17_CE_PE1_TOP_CTRL_03_T                         pe1_top_ctrl_03;	//0x000C
	PE_M17_CE_PE1_TOP_CTRL_04_T                         pe1_top_ctrl_04;	//0x0010
	UINT32                                            reserved5[3];	//0x14-0x1c
	PE_M17_CE_PE1_FSW_CTRL_00_T                         pe1_fsw_ctrl_00;	//0x0020
	PE_M17_CE_PE1_FSW_CTRL_01_T                         pe1_fsw_ctrl_01;	//0x0024
	PE_M17_CE_PE1_FSW_CTRL_02_T                         pe1_fsw_ctrl_02;	//0x0028
	PE_M17_CE_PE1_FSW_CTRL_03_T                         pe1_fsw_ctrl_03;	//0x002C
	UINT32                                            reserved9;	//0x30
	PE_M17_CE_PE1_WIN2_CTRL_00_T                        pe1_win2_ctrl_00;	//0x0034
	PE_M17_CE_PE1_WIN2_CTRL_01_T                        pe1_win2_ctrl_01;	//0x0038
	PE_M17_CE_PE1_WIN2_CTRL_02_T                        pe1_win2_ctrl_02;	//0x003C
	PE_M17_CE_PE1_WIN2_CTRL_03_T                        pe1_win2_ctrl_03;	//0x0040
	PE_M17_CE_PE1_WIN2_CTRL_04_T                        pe1_win2_ctrl_04;	//0x0044
	UINT32                                            reserved14[2];	//0x48-0x4c
	PE_M17_CE_PE1_APL_CTRL_00_T                         pe1_apl_ctrl_00;	//0x0050
	PE_M17_CE_PE1_APL_CTRL_01_T                         pe1_apl_ctrl_01;	//0x0054
	PE_M17_CE_PE1_APL_CTRL_02_T                         pe1_apl_ctrl_02;	//0x0058
	PE_M17_CE_PE1_APL_STAT_00_T                         pe1_apl_stat_00;	//0x005C
	PE_M17_CE_PE1_APL_STAT_01_T                         pe1_apl_stat_01;	//0x0060
	UINT32                                            reserved19[3];	//0x64-0x6c
	PE_M17_CE_PE1_TPG_CTRL_00_T                         pe1_tpg_ctrl_00;	//0x0070
	PE_M17_CE_PE1_TPG_CTRL_01_T                         pe1_tpg_ctrl_01;	//0x0074
	PE_M17_CE_PE1_TPG_CTRL_02_T                         pe1_tpg_ctrl_02;	//0x0078
	PE_M17_CE_PE1_TPG_CTRL_03_T                         pe1_tpg_ctrl_03;	//0x007C
	PE_M17_CE_PE1_TPG_CTRL_04_T                         pe1_tpg_ctrl_04;	//0x0080
	PE_M17_CE_PE1_TPG_IA_CTRL_T                         pe1_tpg_ia_ctrl;	//0x0084
	PE_M17_CE_PE1_TPG_IA_DATA_T                         pe1_tpg_ia_data;	//0x0088
	UINT32                                            reserved26[5];	//0x8c-0x9c
	PE_M17_CE_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0x00A0
	PE_M17_CE_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0x00A4
	UINT32                                            reserved28[2];	//0xa8-0xac
	PE_M17_CE_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0x00B0
	PE_M17_CE_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0x00B4
	PE_M17_CE_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0x00B8
	UINT32                                            reserved31[9];	//0xbc-0xdc
	PE_M17_CE_PE1_CEN_CTRL_00_T                         pe1_cen_ctrl_00;	//0x00E0
	PE_M17_CE_PE1_CEN_CTRL_01_T                         pe1_cen_ctrl_01;	//0x00E4
	PE_M17_CE_PE1_CEN_CTRL_02_T                         pe1_cen_ctrl_02;	//0x00E8
	PE_M17_CE_PE1_CEN_CTRL_03_T                         pe1_cen_ctrl_03;	//0x00EC
	PE_M17_CE_PE1_CEN_CTRL_04_T                         pe1_cen_ctrl_04;	//0x00F0
	PE_M17_CE_PE1_CEN_CTRL_05_T                         pe1_cen_ctrl_05;	//0x00F4
	PE_M17_CE_PE1_CEN_CTRL_06_T                         pe1_cen_ctrl_06;	//0x00F8
	PE_M17_CE_PE1_CEN_CTRL_07_T                         pe1_cen_ctrl_07;	//0x00FC
	UINT32                                            reserved39[4];	//0x100-0x10c
	PE_M17_CE_PE1_CEN_IA_CTRL_T                         pe1_cen_ia_ctrl;	//0x0110
	PE_M17_CE_PE1_CEN_IA_DATA_T                         pe1_cen_ia_data;	//0x0114
	PE_M17_CE_PE1_CEN_DELTA_IA_CTRL_T                   pe1_cen_delta_ia_ctrl;	//0x0118
	PE_M17_CE_PE1_CEN_DELTA_IA_DATA_T                   pe1_cen_delta_ia_data;	//0x011C
	PE_M17_CE_PE1_DCE_CTRL_00_T                         pe1_dce_ctrl_00;	//0x0120
	PE_M17_CE_PE1_DCE_CTRL_01_T                         pe1_dce_ctrl_01;	//0x0124
	PE_M17_CE_PE1_DCE_CTRL_02_T                         pe1_dce_ctrl_02;	//0x0128
	PE_M17_CE_PE1_DCE_CTRL_03_T                         pe1_dce_ctrl_03;	//0x012C
	PE_M17_CE_PE1_DCE_CTRL_04_T                         pe1_dce_ctrl_04;	//0x0130
	PE_M17_CE_PE1_DCE_CTRL_05_T                         pe1_dce_ctrl_05;	//0x0134
	PE_M17_CE_PE1_DCE_IA_CTRL_T                         pe1_dce_ia_ctrl;	//0x0138
	PE_M17_CE_PE1_DCE_IA_DATA_T                         pe1_dce_ia_data;	//0x013C
	PE_M17_CE_PE1_DCE_CTRL_08_T                         pe1_dce_ctrl_08;	//0x0140
	PE_M17_CE_PE1_DCE_CTRL_09_T                         pe1_dce_ctrl_09;	//0x0144
	PE_M17_CE_PE1_DCE_HIST_IA_CTRL_T                    pe1_dce_hist_ia_ctrl;	//0x0148
	PE_M17_CE_PE1_DCE_HIST_IA_DATA1_T                   pe1_dce_hist_ia_data1;	//0x014C
	PE_M17_CE_PE1_DCE_HIST_IA_DATA2_T                   pe1_dce_hist_ia_data2;	//0x0150
	PE_M17_CE_PE1_DCE_CHR_GAIN_T                        pe1_dce_chr_gain;	//0x0154
	PE_M17_CE_PE1_DCE_CHR_ALPHA_T                       pe1_dce_chr_alpha;	//0x0158
	UINT32                                            reserved58;	//0x15c
	PE_M17_CE_PE1_DSE_CTRL_00_T                         pe1_dse_ctrl_00;	//0x0160
	PE_M17_CE_PE1_DSE_CTRL_01_T                         pe1_dse_ctrl_01;	//0x0164
	PE_M17_CE_PE1_DSE_CTRL_02_T                         pe1_dse_ctrl_02;	//0x0168
	PE_M17_CE_PE1_DSE_IA_CTRL_T                         pe1_dse_ia_ctrl;	//0x016C
	PE_M17_CE_PE1_DSE_IA_DATA_T                         pe1_dse_ia_data;	//0x0170
	PE_M17_CE_PE1_DSE_CTRL_03_T                         pe1_dse_ctrl_03;	//0x0174
	PE_M17_CE_PE1_DSE_CTRL_04_T                         pe1_dse_ctrl_04;	//0x0178
	UINT32                                            reserved65;	//0x17c
	PE_M17_CE_PE1_CW_CTRL_00_T                          pe1_cw_ctrl_00;	//0x0180
	PE_M17_CE_PE1_CW_CTRL_01_T                          pe1_cw_ctrl_01;	//0x0184
	UINT32                                            reserved67[2];	//0x188-0x18c
	PE_M17_CE_PE1_CW_CTRL_04_T                          pe1_cw_ctrl_04;	//0x0190
	UINT32                                            reserved68[3];	//0x194-0x19c
	PE_M17_CE_PE1_CONV_CTRL_00_T                        pe1_conv_ctrl_00;	//0x01A0
	PE_M17_CE_PE1_CONV_CTRL_01_T                        pe1_conv_ctrl_01;	//0x01A4
	PE_M17_CE_PE1_CONV_CTRL_02_T                        pe1_conv_ctrl_02;	//0x01A8
	PE_M17_CE_PE1_CONV_CTRL_03_T                        pe1_conv_ctrl_03;	//0x01AC
	PE_M17_CE_PE1_CONV_CTRL_04_T                        pe1_conv_ctrl_04;	//0x01B0
	PE_M17_CE_PE1_CONV_CTRL_05_T                        pe1_conv_ctrl_05;	//0x01B4
	PE_M17_CE_PE1_CONV_CTRL_06_T                        pe1_conv_ctrl_06;	//0x01B8
	PE_M17_CE_PE1_CONV_CTRL_07_T                        pe1_conv_ctrl_07;	//0x01BC
	PE_M17_CE_PE1_CONV_CTRL_08_T                        pe1_conv_ctrl_08;	//0x01C0
	PE_M17_CE_PE1_CONV_CTRL_09_T                        pe1_conv_ctrl_09;	//0x01C4
	PE_M17_CE_PE1_CONV_CTRL_0A_T                        pe1_conv_ctrl_0a;	//0x01C8
	PE_M17_CE_PE1_CONV_CTRL_0B_T                        pe1_conv_ctrl_0b;	//0x01CC
	PE_M17_CE_PE1_CONV_CTRL_0C_T                        pe1_conv_ctrl_0c;	//0x01D0
	PE_M17_CE_PE1_CONV_CTRL_0D_T                        pe1_conv_ctrl_0d;	//0x01D4
	PE_M17_CE_PE1_CONV_CTRL_0E_T                        pe1_conv_ctrl_0e;	//0x01D8
	PE_M17_CE_PE1_CONV_CTRL_0F_T                        pe1_conv_ctrl_0f;	//0x01DC
	PE_M17_CE_PE1_CONV_CTRL_10_T                        pe1_conv_ctrl_10;	//0x01E0
	PE_M17_CE_PE1_CONV_CTRL_11_T                        pe1_conv_ctrl_11;	//0x01E4
	PE_M17_CE_PE1_CONV_CTRL_12_T                        pe1_conv_ctrl_12;	//0x01E8
	UINT32                                            reserved87;	//0x1ec
	PE_M17_CE_PE1_MUTE_CTRL_00_T                        pe1_mute_ctrl_00;	//0x01F0
	PE_M17_CE_PE1_MUTE_CTRL_01_T                        pe1_mute_ctrl_01;	//0x01F4
	PE_M17_CE_PE1_MUTE_CTRL_02_T                        pe1_mute_ctrl_02;	//0x01F8
	PE_M17_CE_PE1_MUTE_CTRL_03_T                        pe1_mute_ctrl_03;	//0x01FC
	PE_M17_CE_PE1_MUTE_CTRL_04_T                        pe1_mute_ctrl_04;	//0x0200
	PE_M17_CE_PE1_MUTE_CTRL_05_T                        pe1_mute_ctrl_05;	//0x0204
	PE_M17_CE_PE1_MUTE_CTRL_06_T                        pe1_mute_ctrl_06;	//0x0208
	PE_M17_CE_PE1_MUTE_CTRL_07_T                        pe1_mute_ctrl_07;	//0x020C
	PE_M17_CE_PE1_MUTE_CTRL_08_T                        pe1_mute_ctrl_08;	//0x0210
	PE_M17_CE_PE1_MUTE_CTRL_09_T                        pe1_mute_ctrl_09;	//0x0214
	PE_M17_CE_PE1_MUTE_CTRL_0A_T                        pe1_mute_ctrl_0a;	//0x0218
	PE_M17_CE_PE1_MUTE_CTRL_0B_T                        pe1_mute_ctrl_0b;	//0x021C
	PE_M17_CE_PE1_MUTE_CTRL_0C_T                        pe1_mute_ctrl_0c;	//0x0220
	PE_M17_CE_PE1_MUTE_CTRL_0D_T                        pe1_mute_ctrl_0d;	//0x0224
	PE_M17_CE_PE1_MUTE_CTRL_0E_T                        pe1_mute_ctrl_0e;	//0x0228
	PE_M17_CE_PE1_MUTE_CTRL_0F_T                        pe1_mute_ctrl_0f;	//0x022C
	UINT32                                            reserved103[28];	//0x230-0x29c
	PE_M17_CE_PE1_LRCR_CTRL_00_T                        pe1_lrcr_ctrl_00;	//0x02A0
	PE_M17_CE_PE1_LRCR_CTRL_01_T                        pe1_lrcr_ctrl_01;	//0x02A4
	PE_M17_CE_PE1_LRCR_CTRL_02_T                        pe1_lrcr_ctrl_02;	//0x02A8
	PE_M17_CE_PE1_LRCR_CTRL_03_T                        pe1_lrcr_ctrl_03;	//0x02AC
	PE_M17_CE_PE1_LRCR_CTRL_04_T                        pe1_lrcr_ctrl_04;	//0x02B0
	PE_M17_CE_PE1_LRCR_CTRL_05_T                        pe1_lrcr_ctrl_05;	//0x02B4
	PE_M17_CE_PE1_LRCR_CTRL_06_T                        pe1_lrcr_ctrl_06;	//0x02B8
	PE_M17_CE_PE1_LRCR_CTRL_07_T                        pe1_lrcr_ctrl_07;	//0x02BC
	PE_M17_CE_G_ADJ_GAIN_T                              g_adj_gain;	//0x02C0
	PE_M17_CE_B_ADJ_GAIN_T                              b_adj_gain;	//0x02C4
	PE_M17_CE_R_ADJ_GAIN_T                              r_adj_gain;	//0x02C8
	PE_M17_CE_HIST_CTRL_MODE_T                          hist_ctrl_mode;	//0x02CC
	PE_M17_CE_PE1_L_G_HIST_IA_CTRL_T                    pe1_l_g_hist_ia_ctrl;	//0x02D0
	PE_M17_CE_PE1_L_G_HIST_IA_DATA_T                    pe1_l_g_hist_ia_data;	//0x02D4
	PE_M17_CE_PE1_L_B_HIST_IA_CTRL_T                    pe1_l_b_hist_ia_ctrl;	//0x02D8
	PE_M17_CE_PE1_L_B_HIST_IA_DATA_T                    pe1_l_b_hist_ia_data;	//0x02DC
	PE_M17_CE_PE1_L_R_HIST_IA_CTRL_T                    pe1_l_r_hist_ia_ctrl;	//0x02E0
	PE_M17_CE_PE1_L_R_HIST_IA_DATA_T                    pe1_l_r_hist_ia_data;	//0x02E4
	PE_M17_CE_PE1_R_G_HIST_IA_CTRL_T                    pe1_r_g_hist_ia_ctrl;	//0x02E8
	PE_M17_CE_PE1_R_G_HIST_IA_DATA_T                    pe1_r_g_hist_ia_data;	//0x02EC
	PE_M17_CE_PE1_R_B_HIST_IA_CTRL_T                    pe1_r_b_hist_ia_ctrl;	//0x02F0
	PE_M17_CE_PE1_R_B_HIST_IA_DATA_T                    pe1_r_b_hist_ia_data;	//0x02F4
	PE_M17_CE_PE1_R_R_HIST_IA_CTRL_T                    pe1_r_r_hist_ia_ctrl;	//0x02F8
	PE_M17_CE_PE1_R_R_HIST_IA_DATA_T                    pe1_r_r_hist_ia_data;	//0x02FC
	UINT32                                            reserved127[4];	//0x300-0x30c
	PE_M17_CE_PE1_BT20_CTRL_00_T                        pe1_bt20_ctrl_00;	//0x0310
	PE_M17_CE_PE1_BT20_CTRL_01_T                        pe1_bt20_ctrl_01;	//0x0314
	PE_M17_CE_PE1_BT20_CTRL_02_T                        pe1_bt20_ctrl_02;	//0x0318
	PE_M17_CE_PE1_BT20_CTRL_03_T                        pe1_bt20_ctrl_03;	//0x031C
	PE_M17_CE_PE1_BT20_CTRL_04_T                        pe1_bt20_ctrl_04;	//0x0320
	PE_M17_CE_PE1_BT20_CTRL_05_T                        pe1_bt20_ctrl_05;	//0x0324
	PE_M17_CE_PE1_BT20_CTRL_06_T                        pe1_bt20_ctrl_06;	//0x0328
	PE_M17_CE_PE1_BT20_CTRL_07_T                        pe1_bt20_ctrl_07;	//0x032C
	PE_M17_CE_PE1_BT20_CTRL_08_T                        pe1_bt20_ctrl_08;	//0x0330
	PE_M17_CE_PE1_BT20_CTRL_09_T                        pe1_bt20_ctrl_09;	//0x0334
	PE_M17_CE_PE1_BT20_CTRL_0A_T                        pe1_bt20_ctrl_0a;	//0x0338
	PE_M17_CE_PE1_BT20_CTRL_0B_T                        pe1_bt20_ctrl_0b;	//0x033C
	PE_M17_CE_PE1_BT20_CTRL_0C_T                        pe1_bt20_ctrl_0c;	//0x0340
	PE_M17_CE_PE1_BT20_CTRL_0D_T                        pe1_bt20_ctrl_0d;	//0x0344
	PE_M17_CE_PE1_BT20_CTRL_0E_T                        pe1_bt20_ctrl_0e;	//0x0348
	PE_M17_CE_PE1_BT20_CTRL_0F_T                        pe1_bt20_ctrl_0f;	//0x034C
	PE_M17_CE_PE1_BT20_CTRL_10_T                        pe1_bt20_ctrl_10;	//0x0350
	PE_M17_CE_PE1_BT20_CTRL_11_T                        pe1_bt20_ctrl_11;	//0x0354
	PE_M17_CE_PE1_BT20_CTRL_12_T                        pe1_bt20_ctrl_12;	//0x0358
	PE_M17_CE_PE1_BT20_CTRL_13_T                        pe1_bt20_ctrl_13;	//0x035C
	PE_M17_CE_PE1_BT20_CTRL_14_T                        pe1_bt20_ctrl_14;	//0x0360
	UINT32                                            reserved148[3];	//0x364-0x36c
	PE_M17_CE_PE1_LOGO_CTRL_00_T                        pe1_logo_ctrl_00;	//0x0370
	PE_M17_CE_PE1_LOGO_CTRL_01_T                        pe1_logo_ctrl_01;	//0x0374
	PE_M17_CE_PE1_LOGO_CTRL_02_T                        pe1_logo_ctrl_02;	//0x0378
	PE_M17_CE_PE1_LOGO_CTRL_03_T                        pe1_logo_ctrl_03;	//0x037C
	PE_M17_CE_PE1_LOGO_CTRL_04_T                        pe1_logo_ctrl_04;	//0x0380
	PE_M17_CE_PE1_LOGO_CTRL_05_T                        pe1_logo_ctrl_05;	//0x0384
	PE_M17_CE_PE1_LOGO_CTRL_06_T                        pe1_logo_ctrl_06;	//0x0388
	PE_M17_CE_PE1_LOGO_CTRL_07_T                        pe1_logo_ctrl_07;	//0x038C
	PE_M17_CE_PE1_LOGO_CTRL_08_T                        pe1_logo_ctrl_08;	//0x0390
	PE_M17_CE_PE1_LOGO_CTRL_09_T                        pe1_logo_ctrl_09;	//0x0394
	PE_M17_CE_PE1_LOGO_CTRL_0A_T                        pe1_logo_ctrl_0a;	//0x0398
	PE_M17_CE_PE1_LOGO_CTRL_0B_T                        pe1_logo_ctrl_0b;	//0x039C
	PE_M17_CE_PE1_LOGO_CTRL_0C_T                        pe1_logo_ctrl_0c;	//0x03A0
	PE_M17_CE_PE1_LOGO_CTRL_0D_T                        pe1_logo_ctrl_0d;	//0x03A4
	PE_M17_CE_PE1_LOGO_CTRL_0E_T                        pe1_logo_ctrl_0e;	//0x03A8
	PE_M17_CE_PE1_LOGO_CTRL_0F_T                        pe1_logo_ctrl_0f;	//0x03AC
	PE_M17_CE_PE1_LOGO_IA_CTRL_T                        pe1_logo_ia_ctrl;	//0x03B0
	PE_M17_CE_PE1_LOGO_IA_DATA_T                        pe1_logo_ia_data;	//0x03B4
	PE_M17_CE_PE1_LOGO_CTRL_10_T                        pe1_logo_ctrl_10;	//0x03B8
	PE_M17_CE_PE1_LOGO_CTRL_11_T                        pe1_logo_ctrl_11;	//0x03BC
	PE_M17_CE_PE1_LOGO_CTRL_12_T                        pe1_logo_ctrl_12;	//0x03C0
	PE_M17_CE_PE1_LOGO_CTRL_13_T                        pe1_logo_ctrl_13;	//0x03C4
	PE_M17_CE_PE1_LOGO_CTRL_14_T                        pe1_logo_ctrl_14;	//0x03C8
	PE_M17_CE_PE1_LOGO_CTRL_15_T                        pe1_logo_ctrl_15;	//0x03CC
	PE_M17_CE_PE1_LOGO_CTRL_16_T                        pe1_logo_ctrl_16;	//0x03D0
	PE_M17_CE_PE1_LOGO_CTRL_17_T                        pe1_logo_ctrl_17;	//0x03D4
	PE_M17_CE_PE1_LOGO_CTRL_18_T                        pe1_logo_ctrl_18;	//0x03D8
	PE_M17_CE_PE1_LOGO_CTRL_19_T                        pe1_logo_ctrl_19;	//0x03DC
	PE_M17_CE_PE1_LOGO_CTRL_1A_T                        pe1_logo_ctrl_1a;	//0x03E0
	PE_M17_CE_PE1_LOGO_STAT_00_T                        pe1_logo_stat_00;	//0x03E4
	PE_M17_CE_PE1_LOGO_STAT_01_T                        pe1_logo_stat_01;	//0x03E8
	PE_M17_CE_PE1_LOGO_CTRL_1B_T                        pe1_logo_ctrl_1b;	//0x03EC
	PE_M17_CE_PE1_LOGO_CTRL_1C_T                        pe1_logo_ctrl_1c;	//0x03F0
	PE_M17_CE_PE1_LOGO_CTRL_1D_T                        pe1_logo_ctrl_1d;	//0x03F4
	UINT32                                            reserved182[2];	//0x3f8-0x3fc
	PE_M17_CE_PE_PCC_CTRL_T                             pe_pcc_ctrl;	//0x0400
	PE_M17_CE_PE1_PCC_COEF0_T                           pe1_pcc_coef0;	//0x0404
	PE_M17_CE_PE1_PCC_COEF1_T                           pe1_pcc_coef1;	//0x0408
	PE_M17_CE_PE1_PCC_COEF2_T                           pe1_pcc_coef2;	//0x040C
	PE_M17_CE_PE1_PCC_COEF3_T                           pe1_pcc_coef3;	//0x0410
	PE_M17_CE_PE1_PCC_COEF4_T                           pe1_pcc_coef4;	//0x0414
	PE_M17_CE_PE1_PCC_COEF5_T                           pe1_pcc_coef5;	//0x0418
	PE_M17_CE_PE1_PCC_COEF6_T                           pe1_pcc_coef6;	//0x041C
	PE_M17_CE_PE1_PCC_COEF7_T                           pe1_pcc_coef7;	//0x0420
	PE_M17_CE_PE1_PCC_COEF8_T                           pe1_pcc_coef8;	//0x0424
	UINT32                                            reserved192[2];	//0x428-0x42c
	PE_M17_CE_PE_DSE_Y_REGION_PT0_T                     pe_dse_y_region_pt0;	//0x0430
	PE_M17_CE_PE_DSE_Y_REGION_PT1_T                     pe_dse_y_region_pt1;	//0x0434
	PE_M17_CE_PE_DSE_Y_REGION_PT2_T                     pe_dse_y_region_pt2;	//0x0438
	PE_M17_CE_PE_DSE_Y_REGION_PT3_T                     pe_dse_y_region_pt3;	//0x043C
	PE_M17_CE_PE_DSE_Y_REGION_PT4_T                     pe_dse_y_region_pt4;	//0x0440
	PE_M17_CE_PE_DSE_Y_REGION_PT5_T                     pe_dse_y_region_pt5;	//0x0444
	PE_M17_CE_PE_DSE_Y_REGION_PT6_T                     pe_dse_y_region_pt6;	//0x0448
	PE_M17_CE_PE_DSE_Y_REGION_PT7_T                     pe_dse_y_region_pt7;	//0x044C
	PE_M17_CE_PE_DSE_H_REGION_PT0_T                     pe_dse_h_region_pt0;	//0x0450
	PE_M17_CE_PE_DSE_H_REGION_PT1_T                     pe_dse_h_region_pt1;	//0x0454
	PE_M17_CE_PE_DSE_H_REGION_PT2_T                     pe_dse_h_region_pt2;	//0x0458
	PE_M17_CE_PE_DSE_H_REGION_PT3_T                     pe_dse_h_region_pt3;	//0x045C
	PE_M17_CE_PE_DSE_H_REGION_PT4_T                     pe_dse_h_region_pt4;	//0x0460
	PE_M17_CE_PE_DSE_H_REGION_PT5_T                     pe_dse_h_region_pt5;	//0x0464
	PE_M17_CE_PE_DSE_H_REGION_PT6_T                     pe_dse_h_region_pt6;	//0x0468
	PE_M17_CE_PE_DSE_H_REGION_PT7_T                     pe_dse_h_region_pt7;	//0x046C
	PE_M17_CE_PE1_DRC_CTRL_00_T                         pe1_drc_ctrl_00;	//0x0470
	PE_M17_CE_PE1_DRC_CTRL_01_T                         pe1_drc_ctrl_01;	//0x0474
	PE_M17_CE_PE1_DRC_CTRL_02_T                         pe1_drc_ctrl_02;	//0x0478
	PE_M17_CE_PE1_DRC_CTRL_03_T                         pe1_drc_ctrl_03;	//0x047C
	PE_M17_CE_PE1_DRC_CTRL_04_T                         pe1_drc_ctrl_04;	//0x0480
	PE_M17_CE_PE1_DRC_CTRL_05_T                         pe1_drc_ctrl_05;	//0x0484
	PE_M17_CE_PE1_DRC_CTRL_06_T                         pe1_drc_ctrl_06;	//0x0488
	PE_M17_CE_PE1_DRC_CTRL_07_T                         pe1_drc_ctrl_07;	//0x048C
	PE_M17_CE_PE1_DRC_CTRL_08_T                         pe1_drc_ctrl_08;	//0x0490
	PE_M17_CE_PE1_DRC_CTRL_09_T                         pe1_drc_ctrl_09;	//0x0494
	PE_M17_CE_PE1_DRC_CTRL_10_T                         pe1_drc_ctrl_10;	//0x0498
	PE_M17_CE_PE1_DRC_CTRL_11_T                         pe1_drc_ctrl_11;	//0x049C
	PE_M17_CE_PE1_DRC_CTRL_12_T                         pe1_drc_ctrl_12;	//0x04A0
	PE_M17_CE_PE1_DRC_CTRL_13_T                         pe1_drc_ctrl_13;	//0x04A4
	PE_M17_CE_PE1_DRC_CTRL_14_T                         pe1_drc_ctrl_14;	//0x04A8
	PE_M17_CE_PE1_DRC_CTRL_15_T                         pe1_drc_ctrl_15;	//0x04AC
	PE_M17_CE_PE1_DRC_CTRL_16_T                         pe1_drc_ctrl_16;	//0x04B0
	PE_M17_CE_PE1_DRC_CTRL_17_T                         pe1_drc_ctrl_17;	//0x04B4
	PE_M17_CE_PE1_DRC_CTRL_18_T                         pe1_drc_ctrl_18;	//0x04B8
	PE_M17_CE_PE1_DRC_CTRL_19_T                         pe1_drc_ctrl_19;	//0x04BC
	PE_M17_CE_PE1_DRC_CTRL_20_T                         pe1_drc_ctrl_20;	//0x04C0
	PE_M17_CE_PE1_DRC_CTRL_21_T                         pe1_drc_ctrl_21;	//0x04C4
	PE_M17_CE_PE1_DRC_CTRL_22_T                         pe1_drc_ctrl_22;	//0x04C8
	PE_M17_CE_PE1_DRC_CTRL_23_T                         pe1_drc_ctrl_23;	//0x04CC
	PE_M17_CE_PE1_DRC_CTRL_24_T                         pe1_drc_ctrl_24;	//0x04D0
	PE_M17_CE_PE1_DRC_CTRL_25_T                         pe1_drc_ctrl_25;	//0x04D4
	PE_M17_CE_PE1_DRC_CTRL_26_T                         pe1_drc_ctrl_26;	//0x04D8
	PE_M17_CE_PE1_DRC_CTRL_27_T                         pe1_drc_ctrl_27;	//0x04DC
	PE_M17_CE_PE1_DRC_CTRL_28_T                         pe1_drc_ctrl_28;	//0x04E0
	PE_M17_CE_PE1_DRC_CTRL_29_T                         pe1_drc_ctrl_29;	//0x04E4
	PE_M17_CE_PE1_DRC_CTRL_30_T                         pe1_drc_ctrl_30;	//0x04E8
	PE_M17_CE_PE1_DRC_CTRL_31_T                         pe1_drc_ctrl_31;	//0x04EC
	PE_M17_CE_PE1_DRC_CTRL_32_T                         pe1_drc_ctrl_32;	//0x04F0
	PE_M17_CE_PE1_DRC_CTRL_33_T                         pe1_drc_ctrl_33;	//0x04F4
	PE_M17_CE_PE1_DRC_CTRL_34_T                         pe1_drc_ctrl_34;	//0x04F8
	PE_M17_CE_PE1_DRC_CTRL_35_T                         pe1_drc_ctrl_35;	//0x04FC
}PE_CE_PE1_REG_M17_T;

typedef struct
{ 
	PE_M17_CO_PE1_TOP_CTRL_00_T                         pe1_top_ctrl_00;	//0x0000
	PE_M17_CO_PE1_TOP_CTRL_01_T                         pe1_top_ctrl_01;	//0x0004
	PE_M17_CO_PE1_TOP_CTRL_02_T                         pe1_top_ctrl_02;	//0x0008
	PE_M17_CO_PE1_TOP_CTRL_03_T                         pe1_top_ctrl_03;	//0x000C
	PE_M17_CO_PE1_TOP_CTRL_04_T                         pe1_top_ctrl_04;	//0x0010
	UINT32                                            reserved5[3];	//0x14-0x1c
	PE_M17_CO_PE1_FSW_CTRL_00_T                         pe1_fsw_ctrl_00;	//0x0020
	PE_M17_CO_PE1_FSW_CTRL_01_T                         pe1_fsw_ctrl_01;	//0x0024
	PE_M17_CO_PE1_FSW_CTRL_02_T                         pe1_fsw_ctrl_02;	//0x0028
	PE_M17_CO_PE1_FSW_CTRL_03_T                         pe1_fsw_ctrl_03;	//0x002C
	UINT32                                            reserved9;	//0x30
	PE_M17_CO_PE1_WIN2_CTRL_00_T                        pe1_win2_ctrl_00;	//0x0034
	PE_M17_CO_PE1_WIN2_CTRL_01_T                        pe1_win2_ctrl_01;	//0x0038
	PE_M17_CO_PE1_WIN2_CTRL_02_T                        pe1_win2_ctrl_02;	//0x003C
	PE_M17_CO_PE1_WIN2_CTRL_03_T                        pe1_win2_ctrl_03;	//0x0040
	PE_M17_CO_PE1_WIN2_CTRL_04_T                        pe1_win2_ctrl_04;	//0x0044
	UINT32                                            reserved14[2];	//0x48-0x4c
	PE_M17_CO_PE1_APL_CTRL_00_T                         pe1_apl_ctrl_00;	//0x0050
	PE_M17_CO_PE1_APL_CTRL_01_T                         pe1_apl_ctrl_01;	//0x0054
	PE_M17_CO_PE1_APL_CTRL_02_T                         pe1_apl_ctrl_02;	//0x0058
	PE_M17_CO_PE1_APL_STAT_00_T                         pe1_apl_stat_00;	//0x005C
	PE_M17_CO_PE1_APL_STAT_01_T                         pe1_apl_stat_01;	//0x0060
	UINT32                                            reserved19[3];	//0x64-0x6c
	PE_M17_CO_PE1_TPG_CTRL_00_T                         pe1_tpg_ctrl_00;	//0x0070
	PE_M17_CO_PE1_TPG_CTRL_01_T                         pe1_tpg_ctrl_01;	//0x0074
	PE_M17_CO_PE1_TPG_CTRL_02_T                         pe1_tpg_ctrl_02;	//0x0078
	PE_M17_CO_PE1_TPG_CTRL_03_T                         pe1_tpg_ctrl_03;	//0x007C
	PE_M17_CO_PE1_TPG_CTRL_04_T                         pe1_tpg_ctrl_04;	//0x0080
	PE_M17_CO_PE1_TPG_IA_CTRL_T                         pe1_tpg_ia_ctrl;	//0x0084
	PE_M17_CO_PE1_TPG_IA_DATA_T                         pe1_tpg_ia_data;	//0x0088
	UINT32                                            reserved26[5];	//0x8c-0x9c
	PE_M17_CO_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0x00A0
	PE_M17_CO_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0x00A4
	UINT32                                            reserved28[2];	//0xa8-0xac
	PE_M17_CO_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0x00B0
	PE_M17_CO_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0x00B4
	PE_M17_CO_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0x00B8
	UINT32                                            reserved31[9];	//0xbc-0xdc
	PE_M17_CO_PE1_CEN_CTRL_00_T                         pe1_cen_ctrl_00;	//0x00E0
	PE_M17_CO_PE1_CEN_CTRL_01_T                         pe1_cen_ctrl_01;	//0x00E4
	PE_M17_CO_PE1_CEN_CTRL_02_T                         pe1_cen_ctrl_02;	//0x00E8
	PE_M17_CO_PE1_CEN_CTRL_03_T                         pe1_cen_ctrl_03;	//0x00EC
	PE_M17_CO_PE1_CEN_CTRL_04_T                         pe1_cen_ctrl_04;	//0x00F0
	PE_M17_CO_PE1_CEN_CTRL_05_T                         pe1_cen_ctrl_05;	//0x00F4
	PE_M17_CO_PE1_CEN_CTRL_06_T                         pe1_cen_ctrl_06;	//0x00F8
	PE_M17_CO_PE1_CEN_CTRL_07_T                         pe1_cen_ctrl_07;	//0x00FC
	UINT32                                            reserved39[4];	//0x100-0x10c
	PE_M17_CO_PE1_CEN_IA_CTRL_T                         pe1_cen_ia_ctrl;	//0x0110
	PE_M17_CO_PE1_CEN_IA_DATA_T                         pe1_cen_ia_data;	//0x0114
	PE_M17_CO_PE1_CEN_DELTA_IA_CTRL_T                   pe1_cen_delta_ia_ctrl;	//0x0118
	PE_M17_CO_PE1_CEN_DELTA_IA_DATA_T                   pe1_cen_delta_ia_data;	//0x011C
	PE_M17_CO_PE1_DCE_CTRL_00_T                         pe1_dce_ctrl_00;	//0x0120
	PE_M17_CO_PE1_DCE_CTRL_01_T                         pe1_dce_ctrl_01;	//0x0124
	PE_M17_CO_PE1_DCE_CTRL_02_T                         pe1_dce_ctrl_02;	//0x0128
	PE_M17_CO_PE1_DCE_CTRL_03_T                         pe1_dce_ctrl_03;	//0x012C
	PE_M17_CO_PE1_DCE_CTRL_04_T                         pe1_dce_ctrl_04;	//0x0130
	PE_M17_CO_PE1_DCE_CTRL_05_T                         pe1_dce_ctrl_05;	//0x0134
	PE_M17_CO_PE1_DCE_IA_CTRL_T                         pe1_dce_ia_ctrl;	//0x0138
	PE_M17_CO_PE1_DCE_IA_DATA_T                         pe1_dce_ia_data;	//0x013C
	PE_M17_CO_PE1_DCE_CTRL_08_T                         pe1_dce_ctrl_08;	//0x0140
	PE_M17_CO_PE1_DCE_CTRL_09_T                         pe1_dce_ctrl_09;	//0x0144
	PE_M17_CO_PE1_DCE_HIST_IA_CTRL_T                    pe1_dce_hist_ia_ctrl;	//0x0148
	PE_M17_CO_PE1_DCE_HIST_IA_DATA1_T                   pe1_dce_hist_ia_data1;	//0x014C
	PE_M17_CO_PE1_DCE_HIST_IA_DATA2_T                   pe1_dce_hist_ia_data2;	//0x0150
	PE_M17_CO_PE1_DCE_CHR_GAIN_T                        pe1_dce_chr_gain;	//0x0154
	PE_M17_CO_PE1_DCE_CHR_ALPHA_T                       pe1_dce_chr_alpha;	//0x0158
	UINT32                                            reserved58;	//0x15c
	PE_M17_CO_PE1_DSE_CTRL_00_T                         pe1_dse_ctrl_00;	//0x0160
	PE_M17_CO_PE1_DSE_CTRL_01_T                         pe1_dse_ctrl_01;	//0x0164
	PE_M17_CO_PE1_DSE_CTRL_02_T                         pe1_dse_ctrl_02;	//0x0168
	PE_M17_CO_PE1_DSE_IA_CTRL_T                         pe1_dse_ia_ctrl;	//0x016C
	PE_M17_CO_PE1_DSE_IA_DATA_T                         pe1_dse_ia_data;	//0x0170
	PE_M17_CO_PE1_DSE_CTRL_03_T                         pe1_dse_ctrl_03;	//0x0174
	PE_M17_CO_PE1_DSE_CTRL_04_T                         pe1_dse_ctrl_04;	//0x0178
	UINT32                                            reserved65;	//0x17c
	PE_M17_CO_PE1_CW_CTRL_00_T                          pe1_cw_ctrl_00;	//0x0180
	PE_M17_CO_PE1_CW_CTRL_01_T                          pe1_cw_ctrl_01;	//0x0184
	UINT32                                            reserved67[2];	//0x188-0x18c
	PE_M17_CO_PE1_CW_CTRL_04_T                          pe1_cw_ctrl_04;	//0x0190
	UINT32                                            reserved68[3];	//0x194-0x19c
	PE_M17_CO_PE1_CONV_CTRL_00_T                        pe1_conv_ctrl_00;	//0x01A0
	PE_M17_CO_PE1_CONV_CTRL_01_T                        pe1_conv_ctrl_01;	//0x01A4
	PE_M17_CO_PE1_CONV_CTRL_02_T                        pe1_conv_ctrl_02;	//0x01A8
	PE_M17_CO_PE1_CONV_CTRL_03_T                        pe1_conv_ctrl_03;	//0x01AC
	PE_M17_CO_PE1_CONV_CTRL_04_T                        pe1_conv_ctrl_04;	//0x01B0
	PE_M17_CO_PE1_CONV_CTRL_05_T                        pe1_conv_ctrl_05;	//0x01B4
	PE_M17_CO_PE1_CONV_CTRL_06_T                        pe1_conv_ctrl_06;	//0x01B8
	PE_M17_CO_PE1_CONV_CTRL_07_T                        pe1_conv_ctrl_07;	//0x01BC
	PE_M17_CO_PE1_CONV_CTRL_08_T                        pe1_conv_ctrl_08;	//0x01C0
	PE_M17_CO_PE1_CONV_CTRL_09_T                        pe1_conv_ctrl_09;	//0x01C4
	PE_M17_CO_PE1_CONV_CTRL_0A_T                        pe1_conv_ctrl_0a;	//0x01C8
	PE_M17_CO_PE1_CONV_CTRL_0B_T                        pe1_conv_ctrl_0b;	//0x01CC
	PE_M17_CO_PE1_CONV_CTRL_0C_T                        pe1_conv_ctrl_0c;	//0x01D0
	PE_M17_CO_PE1_CONV_CTRL_0D_T                        pe1_conv_ctrl_0d;	//0x01D4
	PE_M17_CO_PE1_CONV_CTRL_0E_T                        pe1_conv_ctrl_0e;	//0x01D8
	PE_M17_CO_PE1_CONV_CTRL_0F_T                        pe1_conv_ctrl_0f;	//0x01DC
	PE_M17_CO_PE1_CONV_CTRL_10_T                        pe1_conv_ctrl_10;	//0x01E0
	PE_M17_CO_PE1_CONV_CTRL_11_T                        pe1_conv_ctrl_11;	//0x01E4
	PE_M17_CO_PE1_CONV_CTRL_12_T                        pe1_conv_ctrl_12;	//0x01E8
	UINT32                                            reserved87;	//0x1ec
	PE_M17_CO_PE1_MUTE_CTRL_00_T                        pe1_mute_ctrl_00;	//0x01F0
	PE_M17_CO_PE1_MUTE_CTRL_01_T                        pe1_mute_ctrl_01;	//0x01F4
	PE_M17_CO_PE1_MUTE_CTRL_02_T                        pe1_mute_ctrl_02;	//0x01F8
	PE_M17_CO_PE1_MUTE_CTRL_03_T                        pe1_mute_ctrl_03;	//0x01FC
	PE_M17_CO_PE1_MUTE_CTRL_04_T                        pe1_mute_ctrl_04;	//0x0200
	PE_M17_CO_PE1_MUTE_CTRL_05_T                        pe1_mute_ctrl_05;	//0x0204
	PE_M17_CO_PE1_MUTE_CTRL_06_T                        pe1_mute_ctrl_06;	//0x0208
	PE_M17_CO_PE1_MUTE_CTRL_07_T                        pe1_mute_ctrl_07;	//0x020C
	PE_M17_CO_PE1_MUTE_CTRL_08_T                        pe1_mute_ctrl_08;	//0x0210
	PE_M17_CO_PE1_MUTE_CTRL_09_T                        pe1_mute_ctrl_09;	//0x0214
	PE_M17_CO_PE1_MUTE_CTRL_0A_T                        pe1_mute_ctrl_0a;	//0x0218
	PE_M17_CO_PE1_MUTE_CTRL_0B_T                        pe1_mute_ctrl_0b;	//0x021C
	PE_M17_CO_PE1_MUTE_CTRL_0C_T                        pe1_mute_ctrl_0c;	//0x0220
	PE_M17_CO_PE1_MUTE_CTRL_0D_T                        pe1_mute_ctrl_0d;	//0x0224
	PE_M17_CO_PE1_MUTE_CTRL_0E_T                        pe1_mute_ctrl_0e;	//0x0228
	PE_M17_CO_PE1_MUTE_CTRL_0F_T                        pe1_mute_ctrl_0f;	//0x022C
	UINT32                                            reserved103[28];	//0x230-0x29c
	PE_M17_CO_PE1_LRCR_CTRL_00_T                        pe1_lrcr_ctrl_00;	//0x02A0
	UINT32                                            reserved104[5];	//0x2a4-0x2b4
	PE_M17_CO_PE1_LRCR_CTRL_06_T                        pe1_lrcr_ctrl_06;	//0x02B8
	PE_M17_CO_PE1_LRCR_CTRL_07_T                        pe1_lrcr_ctrl_07;	//0x02BC
	PE_M17_CO_G_ADJ_GAIN_T                              g_adj_gain;	//0x02C0
	PE_M17_CO_B_ADJ_GAIN_T                              b_adj_gain;	//0x02C4
	PE_M17_CO_R_ADJ_GAIN_T                              r_adj_gain;	//0x02C8
	PE_M17_CO_HIST_CTRL_MODE_T                          hist_ctrl_mode;	//0x02CC
	PE_M17_CO_PE1_L_G_HIST_IA_CTRL_T                    pe1_l_g_hist_ia_ctrl;	//0x02D0
	PE_M17_CO_PE1_L_G_HIST_IA_DATA_T                    pe1_l_g_hist_ia_data;	//0x02D4
	PE_M17_CO_PE1_L_B_HIST_IA_CTRL_T                    pe1_l_b_hist_ia_ctrl;	//0x02D8
	PE_M17_CO_PE1_L_B_HIST_IA_DATA_T                    pe1_l_b_hist_ia_data;	//0x02DC
	PE_M17_CO_PE1_L_R_HIST_IA_CTRL_T                    pe1_l_r_hist_ia_ctrl;	//0x02E0
	PE_M17_CO_PE1_L_R_HIST_IA_DATA_T                    pe1_l_r_hist_ia_data;	//0x02E4
	PE_M17_CO_PE1_R_G_HIST_IA_CTRL_T                    pe1_r_g_hist_ia_ctrl;	//0x02E8
	PE_M17_CO_PE1_R_G_HIST_IA_DATA_T                    pe1_r_g_hist_ia_data;	//0x02EC
	PE_M17_CO_PE1_R_B_HIST_IA_CTRL_T                    pe1_r_b_hist_ia_ctrl;	//0x02F0
	PE_M17_CO_PE1_R_B_HIST_IA_DATA_T                    pe1_r_b_hist_ia_data;	//0x02F4
	PE_M17_CO_PE1_R_R_HIST_IA_CTRL_T                    pe1_r_r_hist_ia_ctrl;	//0x02F8
	PE_M17_CO_PE1_R_R_HIST_IA_DATA_T                    pe1_r_r_hist_ia_data;	//0x02FC
	UINT32                                            reserved122[4];	//0x300-0x30c
	PE_M17_CO_PE1_BT20_CTRL_00_T                        pe1_bt20_ctrl_00;	//0x0310
	PE_M17_CO_PE1_BT20_CTRL_01_T                        pe1_bt20_ctrl_01;	//0x0314
	PE_M17_CO_PE1_BT20_CTRL_02_T                        pe1_bt20_ctrl_02;	//0x0318
	PE_M17_CO_PE1_BT20_CTRL_03_T                        pe1_bt20_ctrl_03;	//0x031C
	PE_M17_CO_PE1_BT20_CTRL_04_T                        pe1_bt20_ctrl_04;	//0x0320
	PE_M17_CO_PE1_BT20_CTRL_05_T                        pe1_bt20_ctrl_05;	//0x0324
	PE_M17_CO_PE1_BT20_CTRL_06_T                        pe1_bt20_ctrl_06;	//0x0328
	PE_M17_CO_PE1_BT20_CTRL_07_T                        pe1_bt20_ctrl_07;	//0x032C
	PE_M17_CO_PE1_BT20_CTRL_08_T                        pe1_bt20_ctrl_08;	//0x0330
	PE_M17_CO_PE1_BT20_CTRL_09_T                        pe1_bt20_ctrl_09;	//0x0334
	PE_M17_CO_PE1_BT20_CTRL_0A_T                        pe1_bt20_ctrl_0a;	//0x0338
	PE_M17_CO_PE1_BT20_CTRL_0B_T                        pe1_bt20_ctrl_0b;	//0x033C
	PE_M17_CO_PE1_BT20_CTRL_0C_T                        pe1_bt20_ctrl_0c;	//0x0340
	PE_M17_CO_PE1_BT20_CTRL_0D_T                        pe1_bt20_ctrl_0d;	//0x0344
	PE_M17_CO_PE1_BT20_CTRL_0E_T                        pe1_bt20_ctrl_0e;	//0x0348
	PE_M17_CO_PE1_BT20_CTRL_0F_T                        pe1_bt20_ctrl_0f;	//0x034C
	PE_M17_CO_PE1_BT20_CTRL_10_T                        pe1_bt20_ctrl_10;	//0x0350
	PE_M17_CO_PE1_BT20_CTRL_11_T                        pe1_bt20_ctrl_11;	//0x0354
	PE_M17_CO_PE1_BT20_CTRL_12_T                        pe1_bt20_ctrl_12;	//0x0358
	PE_M17_CO_PE1_BT20_CTRL_13_T                        pe1_bt20_ctrl_13;	//0x035C
	PE_M17_CO_PE1_BT20_CTRL_14_T                        pe1_bt20_ctrl_14;	//0x0360
	UINT32                                            reserved143[3];	//0x364-0x36c
	PE_M17_CO_PE1_LOGO_CTRL_00_T                        pe1_logo_ctrl_00;	//0x0370
	PE_M17_CO_PE1_LOGO_CTRL_01_T                        pe1_logo_ctrl_01;	//0x0374
	PE_M17_CO_PE1_LOGO_CTRL_02_T                        pe1_logo_ctrl_02;	//0x0378
	PE_M17_CO_PE1_LOGO_CTRL_03_T                        pe1_logo_ctrl_03;	//0x037C
	PE_M17_CO_PE1_LOGO_CTRL_04_T                        pe1_logo_ctrl_04;	//0x0380
	PE_M17_CO_PE1_LOGO_CTRL_05_T                        pe1_logo_ctrl_05;	//0x0384
	PE_M17_CO_PE1_LOGO_CTRL_06_T                        pe1_logo_ctrl_06;	//0x0388
	PE_M17_CO_PE1_LOGO_CTRL_07_T                        pe1_logo_ctrl_07;	//0x038C
	PE_M17_CO_PE1_LOGO_CTRL_08_T                        pe1_logo_ctrl_08;	//0x0390
	PE_M17_CO_PE1_LOGO_CTRL_09_T                        pe1_logo_ctrl_09;	//0x0394
	PE_M17_CO_PE1_LOGO_CTRL_0A_T                        pe1_logo_ctrl_0a;	//0x0398
	PE_M17_CO_PE1_LOGO_CTRL_0B_T                        pe1_logo_ctrl_0b;	//0x039C
	PE_M17_CO_PE1_LOGO_CTRL_0C_T                        pe1_logo_ctrl_0c;	//0x03A0
	PE_M17_CO_PE1_LOGO_CTRL_0D_T                        pe1_logo_ctrl_0d;	//0x03A4
	PE_M17_CO_PE1_LOGO_CTRL_0E_T                        pe1_logo_ctrl_0e;	//0x03A8
	PE_M17_CO_PE1_LOGO_CTRL_0F_T                        pe1_logo_ctrl_0f;	//0x03AC
	PE_M17_CO_PE1_LOGO_IA_CTRL_T                        pe1_logo_ia_ctrl;	//0x03B0
	PE_M17_CO_PE1_LOGO_IA_DATA_T                        pe1_logo_ia_data;	//0x03B4
	PE_M17_CO_PE1_LOGO_CTRL_10_T                        pe1_logo_ctrl_10;	//0x03B8
	PE_M17_CO_PE1_LOGO_CTRL_11_T                        pe1_logo_ctrl_11;	//0x03BC
	PE_M17_CO_PE1_LOGO_CTRL_12_T                        pe1_logo_ctrl_12;	//0x03C0
	PE_M17_CO_PE1_LOGO_CTRL_13_T                        pe1_logo_ctrl_13;	//0x03C4
	PE_M17_CO_PE1_LOGO_CTRL_14_T                        pe1_logo_ctrl_14;	//0x03C8
	PE_M17_CO_PE1_LOGO_CTRL_15_T                        pe1_logo_ctrl_15;	//0x03CC
	PE_M17_CO_PE1_LOGO_CTRL_16_T                        pe1_logo_ctrl_16;	//0x03D0
	PE_M17_CO_PE1_LOGO_CTRL_17_T                        pe1_logo_ctrl_17;	//0x03D4
	PE_M17_CO_PE1_LOGO_CTRL_18_T                        pe1_logo_ctrl_18;	//0x03D8
	PE_M17_CO_PE1_LOGO_CTRL_19_T                        pe1_logo_ctrl_19;	//0x03DC
	PE_M17_CO_PE1_LOGO_CTRL_1A_T                        pe1_logo_ctrl_1a;	//0x03E0
	PE_M17_CO_PE1_LOGO_STAT_00_T                        pe1_logo_stat_00;	//0x03E4
	PE_M17_CO_PE1_LOGO_STAT_01_T                        pe1_logo_stat_01;	//0x03E8
	PE_M17_CO_PE1_LOGO_CTRL_20_T                        pe1_logo_ctrl_20;	//0x03EC
	PE_M17_CO_PE1_LOGO_CTRL_21_T                        pe1_logo_ctrl_21;	//0x03F0
	PE_M17_CO_PE1_LOGO_CTRL_22_T                        pe1_logo_ctrl_22;	//0x03F4
	UINT32                                            reserved177[14];	//0x3f8-0x42c
	PE_M17_CO_PE_DSE_Y_REGION_PT0_T                     pe_dse_y_region_pt0;	//0x0430
	PE_M17_CO_PE_DSE_Y_REGION_PT1_T                     pe_dse_y_region_pt1;	//0x0434
	PE_M17_CO_PE_DSE_Y_REGION_PT2_T                     pe_dse_y_region_pt2;	//0x0438
	PE_M17_CO_PE_DSE_Y_REGION_PT3_T                     pe_dse_y_region_pt3;	//0x043C
	PE_M17_CO_PE_DSE_Y_REGION_PT4_T                     pe_dse_y_region_pt4;	//0x0440
	PE_M17_CO_PE_DSE_Y_REGION_PT5_T                     pe_dse_y_region_pt5;	//0x0444
	PE_M17_CO_PE_DSE_Y_REGION_PT6_T                     pe_dse_y_region_pt6;	//0x0448
	PE_M17_CO_PE_DSE_Y_REGION_PT7_T                     pe_dse_y_region_pt7;	//0x044C
	PE_M17_CO_PE_DSE_H_REGION_PT0_T                     pe_dse_h_region_pt0;	//0x0450
	PE_M17_CO_PE_DSE_H_REGION_PT1_T                     pe_dse_h_region_pt1;	//0x0454
	PE_M17_CO_PE_DSE_H_REGION_PT2_T                     pe_dse_h_region_pt2;	//0x0458
	PE_M17_CO_PE_DSE_H_REGION_PT3_T                     pe_dse_h_region_pt3;	//0x045C
	PE_M17_CO_PE_DSE_H_REGION_PT4_T                     pe_dse_h_region_pt4;	//0x0460
	PE_M17_CO_PE_DSE_H_REGION_PT5_T                     pe_dse_h_region_pt5;	//0x0464
	PE_M17_CO_PE_DSE_H_REGION_PT6_T                     pe_dse_h_region_pt6;	//0x0468
	PE_M17_CO_PE_DSE_H_REGION_PT7_T                     pe_dse_h_region_pt7;	//0x046C
}PE_CO_PE1_REG_M17_T;
#endif
