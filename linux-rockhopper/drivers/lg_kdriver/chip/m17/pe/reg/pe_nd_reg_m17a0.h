#ifndef _PE_TNR_REG_M17A0_H_
#define _PE_TNR_REG_M17A0_H_
/*-----------------------------------------------------------------------------
                             0xc9004100L PE0_TNR_LOAD
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 load_time                          :1 ;	//0 
	UINT32 load_enable                        :1 ;	//1 
	UINT32 load_type                          :1 ;	//2 
}PE_M17_PE0_TNR_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9004104L PE0_TNR_INTR
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 intr_enable                        :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 intr_src                           :3 ;	//6:4
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 timer_rst_sel                      :1 ;	//8 
	UINT32 reserved03                         :7 ;	//reserved
	UINT32 intr_line_pos                      :11;	//26:16
}PE_M17_PE0_TNR_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9004108L PE0_TNR_STATUS0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tnr_frame_id                       :4 ;	//3:0
	UINT32 ipc_frame_id                       :4 ;	//7:4
	UINT32 tnrw_y_frame_id                    :4 ;	//11:8
	UINT32 tnrw_c_frame_id                    :4 ;	//15:12
	UINT32 dnr_frame_id                       :8 ;	//23:16
	UINT32 pic_init_frame_id                  :4 ;	//27:24
}PE_M17_PE0_TNR_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc900410cL PE0_TNR_STATUS1
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 line_cnt                           :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 timer_cnt                          :16;	//31:16
}PE_M17_PE0_TNR_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9004110L PE0_TNR_OPMODE
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tnr_c_en                           :1 ;	//0 
	UINT32 tnr_y_en                           :1 ;	//1 
	UINT32 ipc_c_en                           :1 ;	//2 
	UINT32 ipc_y_en                           :1 ;	//3 
	UINT32 tnr_c_444_as_420                   :1 ;	//4 
	UINT32 tnr_y2_en                          :1 ;	//5 
	UINT32 force_422_to_420                   :1 ;	//6 
	UINT32 ipc0_y_en_prog                     :1 ;	//7 
	UINT32 mif_last_mode                      :3 ;	//10:8
	UINT32 tnrw_off                           :1 ;	//11
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 tnr_m_en                           :1 ;	//13
	UINT32 force_444_to_422                   :1 ;	//14
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 detour_enable                      :1 ;	//16
	UINT32 half_rate_en                       :1 ;	//17
	UINT32 ibuf_en                            :2 ;	//19:18
	UINT32 minfo_hsample_mode                 :3 ;	//22:20
	UINT32 minfo_vsample_mode                 :3 ;	//25:23
	UINT32 o_line_ctrl_mode                   :1 ;	//26
	UINT32 o_line_ctrl_en                     :1 ;	//27
	UINT32 tnr_in_lsb_mode                    :2 ;	//29:28
	UINT32 m_run_id                           :2 ;	//31:30
}PE_M17_PE0_TNR_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9004114L PE0_TNR_SRC_SIZE
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsize                              :12;	//11:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cs_type                            :3 ;	//15:13
	UINT32 vsize                              :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 scan_type                          :1 ;	//31
}PE_M17_PE0_TNR_SRC_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9004118L PE0_TNR_FIELD
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 field_id                           :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 field_mode                         :2 ;	//5:4
	UINT32 field_inv                          :1 ;	//6 
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 secam_line                         :1 ;	//8 
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 secam_line_mode                    :2 ;	//13:12
}PE_M17_PE0_TNR_FIELD_T;
/*-----------------------------------------------------------------------------
                             0xc900411cL PE0_TNR_DEBUG_LEND_CTRL
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 in_hsize                           :12;	//11:0
	UINT32 reserved01                         :16;	//reserved
	UINT32 ptn_en_c                           :1 ;	//28
	UINT32 ptn_en_y                           :1 ;	//29
	UINT32 lend_manual_hsize                  :1 ;	//30
	UINT32 lend_ctrl_en                       :1 ;	//31
}PE_M17_PE0_TNR_DEBUG_LEND_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9004120L PE0_TNR_IN_OFFSET
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hoffset                            :12;	//11:0
	UINT32 reserved01                         :18;	//reserved
	UINT32 hsize_sel                          :1 ;	//30
	UINT32 crop_en                            :1 ;	//31
}PE_M17_PE0_TNR_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9004124L PE0_TNR_IN_SIZE
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsize                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 vsize                              :12;	//27:16
}PE_M17_PE0_TNR_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9004128L FBC_CTRL0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fbc_core_en_y                      :1 ;	//0 
	UINT32 fbc_core_20p_y                     :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 fbc_dual_haar_th_y                 :4 ;	//7:4
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 fbc_dpcm_reset_mode_y              :2 ;	//17:16
	UINT32 reserved03                         :5 ;	//reserved
	UINT32 fbc_en_y                           :1 ;	//23
}PE_M17_FBC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900412cL FBC_CTRL1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fbc_core_en_c                      :1 ;	//0 
	UINT32 fbc_core_20p_c                     :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 fbc_dual_haar_th_c                 :4 ;	//7:4
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 fbc_dpcm_reset_mode_c              :2 ;	//17:16
	UINT32 reserved03                         :5 ;	//reserved
	UINT32 fbc_en_c                           :1 ;	//23
}PE_M17_FBC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9004130L PE0_DEBUG_MEM_REQ                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 en_rd_t1_y                         :1 ;	//0 
	UINT32 en_rd_t1_c                         :1 ;	//1 
	UINT32 en_rd_t2_y                         :1 ;	//2 
	UINT32 en_rd_t2_c                         :1 ;	//3 
	UINT32 en_rd_t3_y                         :1 ;	//4 
	UINT32 en_rd_t3_c                         :1 ;	//5 
	UINT32 en_rd_t4_y                         :1 ;	//6 
	UINT32 en_rd_t1_m                         :1 ;	//7 
	UINT32 en_wr_tnrw_y                       :1 ;	//8 
	UINT32 en_wr_tnrw_c                       :1 ;	//9 
	UINT32 en_wr_tnrw_m                       :1 ;	//10
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 manual_mem_en                      :1 ;	//15
}PE_M17_PE0_DEBUG_MEM_REQ_T;
/*-----------------------------------------------------------------------------
                             0xc9004134L PE0_DEBUG_LREQ_DLY                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 lreq_dly_c                         :11;	//10:0
	UINT32 lreq_dly_c_en                      :1 ;	//11
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 lreq_dly_y                         :11;	//26:16
	UINT32 lreq_dly_y_en                      :1 ;	//27
}PE_M17_PE0_DEBUG_LREQ_DLY_T;
/*-----------------------------------------------------------------------------
                             0xc9004138L TNRW_IN_OFFSET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hoffset                            :12;	//11:0
	UINT32 reserved01                         :18;	//reserved
	UINT32 hsize_sel                          :1 ;	//30
	UINT32 crop_en                            :1 ;	//31
}PE_M17_TNRW_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900413cL TNRW_OUT_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsize                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 vsize                              :12;	//27:16
}PE_M17_TNRW_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9004140L TNR_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_tnr_en                         :1 ;	//0:0
	UINT32 reg_nlvl_input_sel                 :1 ;	//1:1
	UINT32 reg_sc_detect_hres                 :1 ;	//2:2
	UINT32 reg_clc_nt_pal                     :1 ;	//3:3
	UINT32 reg_clc_mem_wr_mode                :2 ;	//5:4
	UINT32 reg_sad_8x3_res                    :2 ;	//7:6
	UINT32 reg_sad_8x3_iir_en                 :1 ;	//8:8
	UINT32 reg_sad_8x3_chroma_en              :1 ;	//9:9
	UINT32 reg_minfo_sw                       :2 ;	//11:10
	UINT32 reg_minfo_mode10                   :2 ;	//13:12
	UINT32 reg_minfo_flt                      :2 ;	//15:14
	UINT32 reg_tnr_half_rate                  :1 ;	//16:16
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_minfo_mode32                   :2 ;	//19:18
	UINT32 reg_minfo_mode74                   :4 ;	//23:20
	UINT32 reg_sad_8x3_iir_alpha              :8 ;	//31:24
}PE_M17_TNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004144L TNR_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dbg_show                       :4 ;	//3:0
	UINT32 reserved01                         :12;	//reserved
	UINT32 reg_dbg_tnrw                       :2 ;	//17:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_tnri_debug_mode                :2 ;	//21:20
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 reg_bsum_scale                     :2 ;	//25:24
}PE_M17_TNR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004148L TNR_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 sc_en                              :1 ;	//0 
	UINT32 sc_max_flt_en                      :1 ;	//1 
	UINT32 sc_calc_prev_hist                  :1 ;	//2 
	UINT32 sc_chroma_en                       :1 ;	//3 
	UINT32 sc_scale                           :3 ;	//6:4
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 sc_max_flt_tap                     :3 ;	//10:8
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 sc_chroma_gain                     :3 ;	//14:12
	UINT32 sc_out_mode                        :1 ;	//15
	UINT32 sc_th_ma                           :8 ;	//23:16
	UINT32 sc_th_memc                         :8 ;	//31:24
}PE_M17_TNR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900414cL TNR_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 show_dbg_bar_scale                 :3 ;	//2:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 show_dbg_bar_en                    :4 ;	//7:4
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 show_dbg_bar0_mux                  :4 ;	//19:16
	UINT32 show_dbg_bar1_mux                  :4 ;	//23:20
	UINT32 show_dbg_bar2_mux                  :4 ;	//27:24
	UINT32 show_dbg_bar3_mux                  :4 ;	//31:28
}PE_M17_TNR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004150L TNR_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 manual_debug_bar_09                :8 ;	//7:0
	UINT32 manual_debug_bar_10                :8 ;	//15:8
	UINT32 manual_debug_bar_11                :8 ;	//23:16
	UINT32 manual_debug_bar_12                :8 ;	//31:24
}PE_M17_TNR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9004154L TNR_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mamc_blend_mode                :2 ;	//1:0
	UINT32 reg_mamc_blend_mv_max_or_sum       :1 ;	//2 
	UINT32 reg_mamc_ma_sad_cut                :1 ;	//3 
	UINT32 reg_mamc_mc_sad_cut                :1 ;	//4 
	UINT32 reserved01                         :11;	//reserved
	UINT32 reg_mv_pv_fix_v                    :4 ;	//19:16
	UINT32 reg_mv_pv_fix_h                    :5 ;	//24:20
	UINT32 reserved02                         :6 ;	//reserved
	UINT32 reg_mv_pv_fix_en                   :1 ;	//31
}PE_M17_TNR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004158L TNR_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_me_lb_base                     :8 ;	//7:0
	UINT32 reg_me_pv_base                     :8 ;	//15:8
	UINT32 reg_me_lb_polarity                 :1 ;	//16
}PE_M17_TNR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900415cL TNR_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_sc_en                          :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_5x5_sad_cut                    :1 ;	//8 
}PE_M17_TNR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004160L TNR_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mv_h_fix_val                   :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_mv_v_fix_val                   :4 ;	//11:8
	UINT32 reg_mv_h_fix_fb_val                :5 ;	//16:12
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_mv_v_fix_fb_val                :4 ;	//23:20
	UINT32 reg_debug_sel                      :4 ;	//27:24
	UINT32 reg_lb_monitor_sel                 :2 ;	//29:28
	UINT32 reg_mv_fb_fix                      :1 ;	//30
	UINT32 reg_mv_fix                         :1 ;	//31
}PE_M17_TNR_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9004164L TNR_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_base                       :7 ;	//6:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_lb_smooth_clip                 :6 ;	//13:8
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_pv_smooth_clip                 :6 ;	//21:16
}PE_M17_TNR_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9004168L TNR_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 phase_bm_off                       :2 ;	//1:0
	UINT32 phase_sm_off                       :2 ;	//3:2
	UINT32 phase_lb_off                       :2 ;	//5:4
	UINT32 phase_pv_off                       :2 ;	//7:6
	UINT32 phase_mc_off                       :2 ;	//9:8
}PE_M17_TNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900416cL TNR_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 lb_smooth_en                       :1 ;	//0 
	UINT32 pv_smooth_en                       :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 lb_mv_h_off                        :2 ;	//5:4
	UINT32 lb_mv_v_off                        :2 ;	//7:6
	UINT32 pv_mv_h_off                        :2 ;	//9:8
	UINT32 pv_mv_v_off                        :2 ;	//11:10
	UINT32 reg_mv_fb_reverse                  :1 ;	//12
	UINT32 reserved02                         :9 ;	//reserved
	UINT32 reg_zero_sad_ratio                 :5 ;	//26:22
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_zero_sad_adv                   :1 ;	//30
	UINT32 reg_me_n15_protection              :1 ;	//31
}PE_M17_TNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9004170L TNR_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9004174L TNR_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9004178L TNR_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900417cL TNR_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9004180L TNR_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_acc_mode                   :2 ;	//1:0
	UINT32 reg_bmv_fix_en                     :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_bmv_fix_v                      :4 ;	//7:4
	UINT32 reg_bmv_fix_h                      :5 ;	//12:8
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_n_hblk                         :4 ;	//19:16
	UINT32 reg_n_vblk                         :5 ;	//24:20
}PE_M17_TNR_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9004184L TNR_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blk_vsize                      :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_blk_hsize                      :12;	//27:16
}PE_M17_TNR_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9004188L TNR_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bsad_scale                     :3 ;	//2:0
	UINT32 reg_bmv_rst_mode                   :1 ;	//3 
	UINT32 reg_gsad_scale                     :3 ;	//6:4
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_gmv_gmv_tl                     :8 ;	//15:8
	UINT32 reg_bmv_gmv_tl                     :8 ;	//23:16
	UINT32 reg_bmv_pmv_tl                     :8 ;	//31:24
}PE_M17_TNR_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900418cL TNR_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bmv_coring_th                      :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 gmv_0mv_tl                         :7 ;	//22:16
	UINT32 gmv_0mv_tl_en                      :1 ;	//23
	UINT32 bmv_0mv_tl                         :7 ;	//30:24
	UINT32 bmv_0mv_tl_en                      :1 ;	//31
}PE_M17_TNR_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9004190L TNR_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_detail_beta_mul                :8 ;	//7:0
	UINT32 reg_detail_alpha_mul               :8 ;	//15:8
	UINT32 reg_edge_beta_mul                  :8 ;	//23:16
	UINT32 reg_edge_alpha_mul                 :8 ;	//31:24
}PE_M17_TNR_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9004194L TNR_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_svar_scale                     :3 ;	//2:0
}PE_M17_TNR_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc9004198L TNR_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc900419cL TNR_CTRL_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90041a0L TNR_CTRL_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_p2f_mode                       :1 ;	//0 
	UINT32 reg_ombc_en                        :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_luma_gain_en                   :1 ;	//4 
	UINT32 reg_crgn_gain_en                   :1 ;	//5 
	UINT32 reg_chroma_sad_res                 :2 ;	//7:6
	UINT32 reg_sad_sum_cut                    :2 ;	//9:8
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_5x5_sad_cut                    :2 ;	//13:12
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 reg_avg_cmp_en                     :1 ;	//16
	UINT32 reg_avg_cmp_res                    :3 ;	//19:17
	UINT32 reg_debug_sel                      :4 ;	//23:20
	UINT32 reserved04                         :4 ;	//reserved
	UINT32 reg_cnt_mode                       :3 ;	//30:28
	UINT32 reg_chroma_sad_en                  :1 ;	//31
}PE_M17_TNR_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90041a4L TNR_CTRL_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre_blur_en                        :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cut_resolution                     :2 ;	//3:2
	UINT32 reg_pre_blur_g00                   :4 ;	//7:4
	UINT32 reg_pre_blur_g01                   :3 ;	//10:8
	UINT32 reg_pre_blur_g02                   :3 ;	//13:11
	UINT32 reg_pre_blur_g10                   :3 ;	//16:14
	UINT32 reg_pre_blur_g11                   :3 ;	//19:17
	UINT32 reg_pre_blur_g12                   :3 ;	//22:20
	UINT32 reg_pre_blur_g20                   :3 ;	//25:23
	UINT32 reg_pre_blur_g21                   :3 ;	//28:26
	UINT32 reg_pre_blur_g22                   :3 ;	//31:29
}PE_M17_TNR_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90041a8L TNR_CTRL_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre_blur_en                        :1 ;	//0 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cut_resolution                     :2 ;	//3:2
	UINT32 reg_pre_blur_g00                   :4 ;	//7:4
	UINT32 reg_pre_blur_g01                   :3 ;	//10:8
	UINT32 reg_pre_blur_g02                   :3 ;	//13:11
	UINT32 reg_pre_blur_g10                   :3 ;	//16:14
	UINT32 reg_pre_blur_g11                   :3 ;	//19:17
	UINT32 reg_pre_blur_g12                   :3 ;	//22:20
	UINT32 reg_pre_blur_g20                   :3 ;	//25:23
	UINT32 reg_pre_blur_g21                   :3 ;	//28:26
	UINT32 reg_pre_blur_g22                   :3 ;	//31:29
}PE_M17_TNR_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90041acL TNR_CTRL_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90041b0L TNR_CTRL_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre_filtered_en                    :1 ;	//0 
	UINT32 luma_gain_en                       :1 ;	//1 
	UINT32 cut_resolution                     :2 ;	//3:2
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_pre_detail_cttl_g0             :7 ;	//11:5
	UINT32 reg_pre_detail_cttl_g4             :5 ;	//16:12
	UINT32 reg_pre_detail_cttl_g3             :5 ;	//21:17
	UINT32 reg_pre_detail_cttl_g2             :5 ;	//26:22
	UINT32 reg_pre_detail_cttl_g1             :5 ;	//31:27
}PE_M17_TNR_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90041b4L TNR_CTRL_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_master_en                        :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 r_master_gain                      :8 ;	//15:8
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 r_diff_limit                       :8 ;	//31:24
}PE_M17_TNR_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90041b8L TNR_CTRL_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pre_filtered_en                :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_cut_resolution                 :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_denoise_gain                   :8 ;	//15:8
	UINT32 reg_denoise_ctrl_g0                :7 ;	//22:16
}PE_M17_TNR_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90041bcL TNR_CTRL_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_denoise_ctrl_g4                :5 ;	//4:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_denoise_ctrl_g3                :5 ;	//12:8
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_denoise_ctrl_g2                :5 ;	//20:16
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_denoise_ctrl_g1                :5 ;	//28:24
}PE_M17_TNR_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90041c0L TNR_STATUS_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 w_gsad                             :8 ;	//7:0
	UINT32 w_gmv                              :9 ;	//16:8
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 w_apl_detail                       :8 ;	//31:24
}PE_M17_TNR_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc90041c4L TNR_STATUS_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 w_apl_motion                       :8 ;	//7:0
	UINT32 w_apl_mc_sad                       :8 ;	//15:8
	UINT32 w_apl_var                          :8 ;	//23:16
	UINT32 w_apl_edge                         :8 ;	//31:24
}PE_M17_TNR_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc90041c8L TNR_STATUS_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc90041ccL TNR_STATUS_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc90041d0L TNR_MAIN_LUT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 main_lut_indir_addr                :6 ;	//5:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 main_lut_ai_enable                 :1 ;	//12
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 main_lut_load                      :1 ;	//15
}PE_M17_TNR_MAIN_LUT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90041d4L TNR_MAIN_LUT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 main_lut_indir_data0;	//31:0
}PE_M17_TNR_MAIN_LUT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90041dcL TNR_STATUS_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 sc_measure                         :8 ;	//7:0
	UINT32 apl_y                              :8 ;	//15:8
	UINT32 sc_measure_16                      :16;	//31:16
}PE_M17_TNR_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc90041e0L TNR_CTRL_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 reg_gf_gain                        :8 ;	//23:16
	UINT32 reg_blur_coef                      :8 ;	//31:24
}PE_M17_TNR_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90041e4L TNR_CTRL_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 same_protection_en                 :1 ;	//0 
	UINT32 p_mv0_only                         :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 move_step                          :4 ;	//7:4
	UINT32 same_sad_th                        :8 ;	//15:8
}PE_M17_TNR_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90041e8L TNR_CTRL_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90041ecL TNR_CTRL_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc90041f0L TNR_CTRL_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc90041f4L TNR_CTRL_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc90041f8L TNR_CTRL_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc90041fcL TNR_CTRL_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9004200L IPC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_luma_mode                       :2 ;	//1:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cr_n1_cc_blend_en                  :1 ;	//3 
	UINT32 cr_chroma_mode                     :2 ;	//5:4
	UINT32 cr_integer_edi                     :1 ;	//6 
	UINT32 cr_chroma_edi                      :1 ;	//7 
	UINT32 cr_st_2d_v_flt_range2              :4 ;	//11:8
	UINT32 cr_st_2d_v_flt_range               :4 ;	//15:12
	UINT32 cr_ori_3d_blur_y                   :2 ;	//17:16
	UINT32 cr_ori_3d_blur_c                   :2 ;	//19:18
	UINT32 cr_tava_v_edge_adap                :1 ;	//20
	UINT32 cr_tava_debug_mode                 :1 ;	//21
	UINT32 cr_tava_st_adap                    :1 ;	//22
	UINT32 cr_tava_en                         :1 ;	//23
	UINT32 cr_hmc_force_fmd                   :1 ;	//24
	UINT32 cr_st_2d_v_flt_en                  :1 ;	//25
	UINT32 cr_clc_fmd_off                     :1 ;	//26
	UINT32 cr_chroma_tava_only                :1 ;	//27
	UINT32 cr_film_auto_gain                  :1 ;	//28
	UINT32 cr_film_apply_c                    :1 ;	//29
	UINT32 cr_film_apply_y                    :1 ;	//30
	UINT32 cr_film_mode_enable                :1 ;	//31
}PE_M17_IPC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004204L IPC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_hmc_en_sel1                     :2 ;	//1:0
	UINT32 cr_hmc_en_sel2                     :2 ;	//3:2
	UINT32 st_flt_mode                        :1 ;	//4 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cr_fmd_vfilter_en                  :1 ;	//6 
	UINT32 cr_fend_auto                       :1 ;	//7 
	UINT32 cr_st_iir_dec_gain                 :4 ;	//11:8
	UINT32 cr_st_iir_inc_gain                 :4 ;	//15:12
	UINT32 cr_st_flt_enable                   :1 ;	//16
	UINT32 cr_st_iir_en                       :1 ;	//17
	UINT32 cr_hmc_flt_enable                  :1 ;	//18
	UINT32 cr_game_mode                       :1 ;	//19
	UINT32 cr_st_2d_v_flt_range               :4 ;	//23:20
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 cr_black_mask                      :1 ;	//25
	UINT32 cr_ipc_debug_show                  :5 ;	//30:26
	UINT32 cr_5f_mode                         :1 ;	//31
}PE_M17_IPC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004208L IPC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fuzzy_ctrl_point_x0                :8 ;	//7:0
	UINT32 fuzzy_ctrl_point_x4                :8 ;	//15:8
	UINT32 fuzzy_ctrl_point_x1                :8 ;	//23:16
	UINT32 fuzzy_ctrl_point_y1                :8 ;	//31:24
}PE_M17_IPC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900420cL IPC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fuzzy_ctrl_point_x2                :8 ;	//7:0
	UINT32 fuzzy_ctrl_point_y2                :8 ;	//15:8
	UINT32 fuzzy_ctrl_point_x3                :8 ;	//23:16
	UINT32 fuzzy_ctrl_point_y3                :8 ;	//31:24
}PE_M17_IPC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004210L IPC_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 et_offset__s7                      :8 ;	//7:0
	UINT32 motion_x_tearing_gain              :8 ;	//15:8
	UINT32 tearing_gain                       :8 ;	//23:16
	UINT32 motion_gain                        :8 ;	//31:24
}PE_M17_IPC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9004214L IPC_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :12;	//reserved
	UINT32 cr_t_grad_weight                   :4 ;	//15:12
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 cr_v_grad_weight                   :4 ;	//23:20
	UINT32 reserved03                         :4 ;	//reserved
	UINT32 cr_h_grad_weight                   :4 ;	//31:28
}PE_M17_IPC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004218L IPC_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_normalize_en                    :1 ;	//0 
	UINT32 cr_flat_only                       :1 ;	//1 
	UINT32 cr_motion_iir_en                   :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cr_tearing_normalize_en            :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 cr_normalize_base                  :8 ;	//15:8
	UINT32 cr_normalize_center                :8 ;	//23:16
	UINT32 cr_motion_coring                   :8 ;	//31:24
}PE_M17_IPC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900421cL IPC_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cr_v_en                            :1 ;	//1 
	UINT32 cr_45_en                           :1 ;	//2 
	UINT32 cr_15_en                           :1 ;	//3 
	UINT32 reserved02                         :20;	//reserved
	UINT32 cr_iir_motion_gain                 :8 ;	//31:24
}PE_M17_IPC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004220L IPC_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 fmd_caption_range_top              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 fmd_caption_range_bot              :12;	//27:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 caption_flow_detected              :1 ;	//30
	UINT32 hmc_when_cap_not_detected          :1 ;	//31
}PE_M17_IPC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9004224L IPC_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pn_fmd_a_th                        :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 pn_variance_th                     :8 ;	//23:16
	UINT32 pn_fmd_motion_th                   :8 ;	//31:24
}PE_M17_IPC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9004228L IPC_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pcnc_fmd_a_th                      :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 pcnc_variance_th                   :8 ;	//23:16
	UINT32 pcnc_fmd_motion_th                 :8 ;	//31:24
}PE_M17_IPC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900422cL IPC_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_pndiff_th                       :8 ;	//7:0
	UINT32 cr_center_bound_ctrl               :8 ;	//15:8
	UINT32 cr_dn_bound_ctrl                   :8 ;	//23:16
	UINT32 cr_up_bound_ctrl                   :8 ;	//31:24
}PE_M17_IPC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9004230L IPC_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_still_pn_th                    :8 ;	//7:0
	UINT32 reg_fmd_ratio_th                   :8 ;	//15:8
	UINT32 reg_fmd_max_th                     :8 ;	//23:16
	UINT32 reg_fmd_min_th                     :8 ;	//31:24
}PE_M17_IPC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9004234L IPC_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_tava_chroma_mul                 :8 ;	//7:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 cr_hmc_alpha_th                    :8 ;	//19:12
	UINT32 cr_hmc_debug_mode                  :1 ;	//20
	UINT32 cr_hmc_debug_gain                  :6 ;	//26:21
	UINT32 cr_hmc_debug_dir                   :5 ;	//31:27
}PE_M17_IPC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9004238L IPC_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_lockcnt_en                     :1 ;	//0 
	UINT32 reserved                           :1 ;	//1 
	UINT32 reg_lock_speed                     :6 ;	//7:2
	UINT32 reg_lockcnt_th                     :8 ;	//15:8
	UINT32 reg_same_th                        :8 ;	//23:16
	UINT32 reg_still_frame_limit              :8 ;	//31:24
}PE_M17_IPC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900423cL IPC_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_3_2_detect_en                  :1 ;	//0 
	UINT32 reg_3_2_detect_only                :1 ;	//1 
	UINT32 reg_3_2_lockcnt_255_en             :1 ;	//2 
	UINT32 reg_3_2_pndiff_disable             :1 ;	//3 
	UINT32 reg_hd_mode                        :1 ;	//4 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_3_2_pndiff_th                  :8 ;	//15:8
	UINT32 reg_3_2_pn_ratio_max_th            :8 ;	//23:16
	UINT32 reg_3_2_pn_ratio_min_th            :8 ;	//31:24
}PE_M17_IPC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9004240L IPC_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_still_pn_th2                   :8 ;	//7:0
	UINT32 reg_still_prev_ratio               :8 ;	//15:8
	UINT32 reg_lock_reducer                   :8 ;	//23:16
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_badedit_protect                :1 ;	//31
}PE_M17_IPC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9004244L IPC_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_inv_resolution                  :2 ;	//1:0
	UINT32 cr_field_manual_mode               :2 ;	//3:2
	UINT32 cr_field_inverse                   :1 ;	//4 
	UINT32 reserved01                         :19;	//reserved
	UINT32 cr_tearing_a_th                    :8 ;	//31:24
}PE_M17_IPC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9004248L IPC_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_ud_gain                         :8 ;	//7:0
	UINT32 cr_lr_gain                         :8 ;	//15:8
	UINT32 cr_h_grad_gain                     :8 ;	//23:16
	UINT32 cr_v_grad_gain                     :8 ;	//31:24
}PE_M17_IPC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900424cL IPC_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_errs_gain                      :8 ;	//7:0
	UINT32 reg_confidence_gain                :8 ;	//15:8
	UINT32 reg_2d_offset                      :8 ;	//23:16
	UINT32 reg_flicker_gain                   :8 ;	//31:24
}PE_M17_IPC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9004250L IPC_STATUS_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_pc_v_count                       :16;	//15:0
	UINT32 r_nc_v_count                       :16;	//31:16
}PE_M17_IPC_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004254L IPC_STATUS_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_pc_nc_same                       :16;	//15:0
	UINT32 r_pn_v_count                       :16;	//31:16
}PE_M17_IPC_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004258L IPC_STATUS_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :6 ;	//5:0
	UINT32 r_fmd_32_min_th_flag_u             :1 ;	//6 
	UINT32 r_fmd_32_max_th_flag_u             :1 ;	//7 
	UINT32 r_fmd_still_limit_flag_u           :1 ;	//8 
	UINT32 r_fmd_still_pn_th2_flag_u          :1 ;	//9 
	UINT32 r_fmd_still_pn_th_flag_u           :1 ;	//10
	UINT32 r_fmd_still_prev_ratio_flag_u      :1 ;	//11
	UINT32 r_fmd_bigger_flag_u                :1 ;	//12
	UINT32 r_fmd_smaller_flag_u               :1 ;	//13
	UINT32 r_fmd_3_2_fmd_comb_mode_u          :2 ;	//15:14
	UINT32 r_pn_diff_count                    :16;	//31:16
}PE_M17_IPC_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc900425cL IPC_STATUS_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 same_ng_flag_d                     :1 ;	//0 
	UINT32 too_small_flag_d                   :1 ;	//1 
	UINT32 r_fmd_still_flag_d                 :1 ;	//2 
	UINT32 r_fmd_possibility_flag_d           :1 ;	//3 
	UINT32 base_pn_ratio_flag_d               :1 ;	//4 
	UINT32 r_32_detected_flag_d               :1 ;	//5 
	UINT32 r_fmd_comb_mode_d                  :2 ;	//7:6
	UINT32 r_fmd_lock_count_d                 :8 ;	//15:8
	UINT32 same_ng_flag_u                     :1 ;	//16
	UINT32 too_small_flag_u                   :1 ;	//17
	UINT32 r_fmd_still_flag_u                 :1 ;	//18
	UINT32 r_fmd_possibility_flag_u           :1 ;	//19
	UINT32 base_pn_ratio_flag_u               :1 ;	//20
	UINT32 r_32_uetected_flag_u               :1 ;	//21
	UINT32 r_fmd_comb_mode_u                  :2 ;	//23:22
	UINT32 r_fmd_lock_count_u                 :8 ;	//31:24
}PE_M17_IPC_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004260L CLC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cl_filter_enable                   :1 ;	//1 
	UINT32 clc_detection_enable               :1 ;	//2 
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 motion_window                      :2 ;	//5:4
	UINT32 cl_pattern_dist                    :2 ;	//7:6
	UINT32 reserved03                         :4 ;	//reserved
	UINT32 cl_ab_ratio                        :4 ;	//15:12
	UINT32 cl_y_hdistance                     :2 ;	//17:16
	UINT32 cl_c_hdistance                     :2 ;	//19:18
	UINT32 cl_y_protect_en                    :1 ;	//20
	UINT32 reserved04                         :7 ;	//reserved
	UINT32 cl_motion_a_filter                 :1 ;	//28
	UINT32 cl_motion_b_filter                 :1 ;	//29
	UINT32 cl_motion_a_mode                   :1 ;	//30
}PE_M17_CLC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004264L CLC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_motion_a_th                     :8 ;	//7:0
	UINT32 cl_motion_b_th                     :8 ;	//15:8
	UINT32 cl_y_protect_th0                   :8 ;	//23:16
	UINT32 cl_y_protect_th1                   :8 ;	//31:24
}PE_M17_CLC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004268L CLC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_y_bound_th                      :7 ;	//6:0
	UINT32 cl_c_bound_use_4line               :1 ;	//7 
	UINT32 cl_c_bound_th                      :7 ;	//14:8
	UINT32 cl_c_bound_type                    :1 ;	//15
	UINT32 cl_y_bound_width_chroma            :2 ;	//17:16
	UINT32 cl_y_bound_ignore_cc               :1 ;	//18
	UINT32 cl_y_bound_ignore_p2               :1 ;	//19
	UINT32 cl_y_bound_ignore_p4               :1 ;	//20
	UINT32 reg_bin3x1_flt_en                  :1 ;	//21
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_bin5x1_flt_en                  :1 ;	//24
	UINT32 reg_bin5x1_flt_th                  :3 ;	//27:25
	UINT32 reg_vm_original_mode               :1 ;	//28
	UINT32 reg_vm_other_mode                  :1 ;	//29
	UINT32 cl_motionp2n2_th_pal_high          :2 ;	//31:30
}PE_M17_CLC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900426cL CLC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_sat_min                         :8 ;	//7:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 cl_var_measure_th1                 :10;	//19:10
	UINT32 cl_var_measure_th2                 :10;	//29:20
	UINT32 cl_pt_enable                       :2 ;	//31:30
}PE_M17_CLC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004270L CLC_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_tearing_pt_th1                  :12;	//11:0
	UINT32 cl_motionp2n2_th_pal_low           :8 ;	//19:12
	UINT32 cl_frame_min                       :12;	//31:20
}PE_M17_CLC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9004274L CLC_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_data_line_switching_sel         :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 clc_bin_flt_th                     :3 ;	//10:8
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 clc_bin_flt_en                     :1 ;	//15
	UINT32 clc_dbg_show_mask                  :13;	//28:16
}PE_M17_CLC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004278L CLC_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cc_c_filter_gain                   :8 ;	//7:0
	UINT32 cc_y_filter_when_cc_detected       :1 ;	//8 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cl_cc_original_en                  :1 ;	//10
	UINT32 clc_force_non_fmd                  :1 ;	//11
	UINT32 cl_c_filter_when_cl_detected       :1 ;	//12
	UINT32 cl_y_filter_when_cl_detected       :1 ;	//13
	UINT32 clc_filter_mode                    :2 ;	//15:14
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 cl_cc_protection_th                :8 ;	//31:24
}PE_M17_CLC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900427cL CLC_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 cl_detection_count                 :16;	//31:16
}PE_M17_CLC_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004280L IPC_CTRL_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tava_v_diff_y0                     :8 ;	//7:0
	UINT32 tava_v_diff_x0                     :8 ;	//15:8
	UINT32 tava_v_diff_y1                     :8 ;	//23:16
	UINT32 tava_v_diff_x1                     :8 ;	//31:24
}PE_M17_IPC_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9004284L IPC_CTRL_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_div_en                         :1 ;	//0 
	UINT32 cr_bound_exp_en                    :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 cr_sub_main_sel                    :1 ;	//4 
	UINT32 reserved02                         :11;	//reserved
	UINT32 reg_manual_en                      :1 ;	//16
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_manual_mode2                   :2 ;	//21:20
	UINT32 reg_manual_mode1                   :2 ;	//23:22
	UINT32 reg_div_position                   :8 ;	//31:24
}PE_M17_IPC_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9004288L IPC_CTRL_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_still_pn_th                    :8 ;	//7:0
	UINT32 reg_fmd_ratio_th                   :8 ;	//15:8
	UINT32 reg_fmd_max_th                     :8 ;	//23:16
	UINT32 reg_fmd_min_th                     :8 ;	//31:24
}PE_M17_IPC_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc900428cL IPC_CTRL_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_lockcnt_en                     :1 ;	//0 
	UINT32 reserved                           :1 ;	//1 
	UINT32 reg_lock_speed                     :6 ;	//7:2
	UINT32 reg_lockcnt_th                     :8 ;	//15:8
	UINT32 reg_same_th                        :8 ;	//23:16
	UINT32 reg_still_frame_limit              :8 ;	//31:24
}PE_M17_IPC_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9004290L IPC_CTRL_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_3_2_detect_en                  :1 ;	//0 
	UINT32 reg_3_2_detect_only                :1 ;	//1 
	UINT32 reg_3_2_lockcnt_255_en             :1 ;	//2 
	UINT32 reg_3_2_pndiff_disable             :1 ;	//3 
	UINT32 reg_hd_mode                        :1 ;	//4 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_3_2_pndiff_th                  :8 ;	//15:8
	UINT32 reg_3_2_pn_ratio_max_th            :8 ;	//23:16
	UINT32 reg_3_2_pn_ratio_min_th            :8 ;	//31:24
}PE_M17_IPC_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9004294L IPC_CTRL_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_still_pn_th2                   :8 ;	//7:0
	UINT32 reg_still_prev_ratio               :8 ;	//15:8
	UINT32 reg_lock_reducer                   :8 ;	//23:16
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_badedit_protect                :1 ;	//31
}PE_M17_IPC_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9004298L IPC_CTRL_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_toosmall_en                    :1 ;	//0 
	UINT32 reg_toosmall_min                   :7 ;	//7:1
	UINT32 reg_toosmall_max                   :8 ;	//15:8
	UINT32 reg_pndiff_disable                 :1 ;	//16
}PE_M17_IPC_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc900429cL IPC_CTRL_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_fend_position                  :11;	//10:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 cr_sc_length                       :3 ;	//14:12
	UINT32 reserved02                         :11;	//reserved
	UINT32 cr_vmc_dir                         :3 ;	//28:26
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 cr_vmc_en                          :1 ;	//31
}PE_M17_IPC_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90042a0L IPC_CTRL_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_yy_diff_gain                   :4 ;	//3:0
	UINT32 reg_hv_add_gain                    :4 ;	//7:4
	UINT32 reg_v_motion_gain                  :4 ;	//11:8
	UINT32 reg_h_motion_gain                  :4 ;	//15:12
	UINT32 reg_cc_diff_gain                   :4 ;	//19:16
}PE_M17_IPC_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90042a4L IPC_CTRL_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 n1b_motion_gain_y0                 :8 ;	//7:0
	UINT32 n1b_motion_gain_x0                 :8 ;	//15:8
	UINT32 n1b_motion_gain_y1                 :8 ;	//23:16
	UINT32 n1b_motion_gain_x1                 :8 ;	//31:24
}PE_M17_IPC_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90042a8L IPC_CTRL_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 n1b_variance_gain_y0               :8 ;	//7:0
	UINT32 n1b_variance_gain_x0               :8 ;	//15:8
	UINT32 n1b_variance_gain_y1               :8 ;	//23:16
	UINT32 n1b_variance_gain_x1               :8 ;	//31:24
}PE_M17_IPC_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90042acL IPC_CTRL_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hmc_use_tnr_mv                 :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_cr_hmc_y_th                    :4 ;	//11:8
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 max_penalty                        :8 ;	//23:16
	UINT32 min_penalty                        :8 ;	//31:24
}PE_M17_IPC_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90042b0L IPC_CTRL_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_min_diff_th                    :8 ;	//7:0
	UINT32 reg_edi_va_blend_mul               :10;	//17:8
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_edi_va_protect_mul             :10;	//29:20
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_m16_edi_va_blend_en            :1 ;	//31
}PE_M17_IPC_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90042b4L IPC_CTRL_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_max_va_diff_th                 :8 ;	//7:0
	UINT32 reg_max_edi_diff_th                :8 ;	//15:8
	UINT32 reg_edi_va_protect_min             :8 ;	//23:16
	UINT32 reg_edi_va_blend_min               :8 ;	//31:24
}PE_M17_IPC_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90042b8L IPC_CTRL_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_2d_top_lut_y0                  :8 ;	//7:0
	UINT32 reg_2d_top_lut_x0                  :8 ;	//15:8
	UINT32 reg_2d_top_lut_y1                  :8 ;	//23:16
	UINT32 reg_2d_top_lut_x1                  :8 ;	//31:24
}PE_M17_IPC_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc90042bcL IPC_CTRL_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_hmc_enable_1                    :1 ;	//0 
	UINT32 cr_lock_th_1                       :7 ;	//7:1
	UINT32 cr_lr_ratio_th_1                   :8 ;	//15:8
	UINT32 cr_hmc_expend_1                    :3 ;	//18:16
	UINT32 cr_lr_ratio_check_en_1             :1 ;	//19
	UINT32 cr_robustness_1                    :4 ;	//23:20
	UINT32 cr_center_weight_1                 :8 ;	//31:24
}PE_M17_IPC_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc90042c0L IPC_CTRL_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_hmc_enable_2                    :1 ;	//0 
	UINT32 cr_lock_th_2                       :7 ;	//7:1
	UINT32 cr_lr_ratio_th_2                   :8 ;	//15:8
	UINT32 cr_hmc_expend_2                    :3 ;	//18:16
	UINT32 cr_lr_ratio_check_en_2             :1 ;	//19
	UINT32 cr_robustness_2                    :4 ;	//23:20
	UINT32 cr_center_weight_2                 :8 ;	//31:24
}PE_M17_IPC_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc90042c4L IPC_CTRL_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 line_cnt_th_0                      :10;	//9:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 line_cnt_th_1                      :10;	//21:12
}PE_M17_IPC_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc90042c8L IPC_CTRL_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_n1b_limit                       :9 ;	//8:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 cr_n1b_resolution                  :3 ;	//14:12
	UINT32 reserved02                         :9 ;	//reserved
	UINT32 cr_pre_sc_th                       :8 ;	//31:24
}PE_M17_IPC_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc90042e0L MMD_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mmd_vtap                           :2 ;	//1:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 mmd_htap                           :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 mmd_vmode                          :1 ;	//8 
}PE_M17_MMD_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90042f0L IPC_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_cubic_coef0                    :8 ;	//7:0
	UINT32 reg_cubic_coef1                    :8 ;	//15:8
	UINT32 reg_va_blending_ctrl_lv1           :3 ;	//18:16
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_va_blending_ctrl_lv2           :3 ;	//22:20
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_va_blending_ctrl_lv3           :3 ;	//26:24
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 reg_va_blending_ctrl_lv4           :3 ;	//30:28
}PE_M17_IPC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90042f4L IPC_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_va_cubic                       :1 ;	//0 
	UINT32 reg_boundary_window                :1 ;	//1 
	UINT32 reg_force_va                       :1 ;	//2 
	UINT32 reg_half_pel_va                    :1 ;	//3 
	UINT32 reg_dir_med_tap                    :2 ;	//5:4
	UINT32 reg_diff_med_tap                   :2 ;	//7:6
	UINT32 reg_va_blending_ctrl1              :3 ;	//10:8
	UINT32 reg_wide_angle_protection_1        :1 ;	//11
	UINT32 reg_va_blending_ctrl2              :3 ;	//14:12
	UINT32 reg_wide_angle_protection_2        :1 ;	//15
	UINT32 reg_errs_chroma_blend_coef         :8 ;	//23:16
	UINT32 reg_strong_global_th               :6 ;	//29:24
	UINT32 narrow_angle_week                  :1 ;	//30
	UINT32 narrow_angle_protection            :1 ;	//31
}PE_M17_IPC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90042f8L IPC_CTRL_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_vmc_v_diff_max                  :8 ;	//7:0
	UINT32 cr_vmc_v_diff_protect_mul          :8 ;	//15:8
	UINT32 es_err_value                       :8 ;	//23:16
	UINT32 et_err_value                       :8 ;	//31:24
}PE_M17_IPC_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90042fcL IPC_CTRL_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_hmc_enable_0                    :1 ;	//0 
	UINT32 cr_lock_th_0                       :7 ;	//7:1
	UINT32 cr_lr_ratio_th_0                   :8 ;	//15:8
	UINT32 cr_hmc_expend_0                    :3 ;	//18:16
	UINT32 cr_lr_ratio_check_en_0             :1 ;	//19
	UINT32 cr_robustness_0                    :4 ;	//23:20
	UINT32 cr_center_weight_0                 :8 ;	//31:24
}PE_M17_IPC_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9004300L IPC_CTRL_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_noise_en                        :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 cr_noise_th                        :8 ;	//15:8
	UINT32 cr_gds_resolution                  :2 ;	//17:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 cr_hmc_h_range                     :12;	//31:20
}PE_M17_IPC_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc9004304L IPC_CTRL_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_vdiff_en                       :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_vdiff_th                       :8 ;	//15:8
	UINT32 reg_hmc_err_max                    :8 ;	//23:16
	UINT32 reg_hmc_err_min                    :8 ;	//31:24
}PE_M17_IPC_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc9004308L IPC_CTRL_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cr_fmd_check_en                    :1 ;	//0 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 cr_fmd_ath                         :8 ;	//15:8
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 cr_fmd_ratio_th                    :8 ;	//31:24
}PE_M17_IPC_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc900430cL IPC_CTRL_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 chroma_st_flt_ctrl_x0              :8 ;	//7:0
	UINT32 chroma_st_flt_ctrl_x1              :8 ;	//15:8
	UINT32 luma_st_flt_ctrl_x0                :8 ;	//23:16
	UINT32 luma_st_flt_ctrl_x1                :8 ;	//31:24
}PE_M17_IPC_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc9004310L IPC_CTRL_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hmc_bonus_es_en                :1 ;	//0 
	UINT32 reg_hmc_bonus_et_en                :1 ;	//1 
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_hmc_bonus_es                   :8 ;	//15:8
	UINT32 reg_hmc_bonus_th                   :8 ;	//23:16
	UINT32 reg_hmc_bonus_et                   :8 ;	//31:24
}PE_M17_IPC_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc9004314L IPC_CTRL_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hmc_alpha_th                       :8 ;	//7:0
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 hmc_flt_ctrl_x0                    :8 ;	//23:16
	UINT32 hmc_st_flt_ctrl_x1                 :8 ;	//31:24
}PE_M17_IPC_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc9004318L IPC_CTRL_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_vmc_motion_th                  :8 ;	//7:0
	UINT32 reg_vmc_debug                      :1 ;	//8 
	UINT32 reg_vmc_en                         :1 ;	//9 
	UINT32 reg_vmc_still_check                :1 ;	//10
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_vmc_mul                        :2 ;	//13:12
	UINT32 reg_vmc_out_mul                    :2 ;	//15:14
	UINT32 reg_vmc_protect_th                 :8 ;	//23:16
	UINT32 reg_protection_en                  :1 ;	//24
	UINT32 reg_2filed_check_en                :1 ;	//25
	UINT32 reg_vmc_tnrmotion_dis              :1 ;	//26
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_vmc_mm_ratio                   :4 ;	//31:28
}PE_M17_IPC_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc900431cL IPC_CTRL_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_toosmall_en                    :1 ;	//0 
	UINT32 reg_toosmall_min                   :7 ;	//7:1
	UINT32 reg_toosmall_max                   :8 ;	//15:8
	UINT32 reg_pndiff_disable                 :1 ;	//16
}PE_M17_IPC_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc9004320L IPC_CTRL_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tava_errt_y2                       :8 ;	//7:0
	UINT32 tava_errt_x2                       :8 ;	//15:8
	UINT32 tava_errt_y3                       :8 ;	//23:16
	UINT32 tava_errt_x3                       :8 ;	//31:24
}PE_M17_IPC_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc9004324L IPC_CTRL_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tava_errt_y0                       :8 ;	//7:0
	UINT32 tava_errt_x0                       :8 ;	//15:8
	UINT32 tava_errt_y1                       :8 ;	//23:16
	UINT32 tava_errt_x1                       :8 ;	//31:24
}PE_M17_IPC_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc9004328L IPC_STATUS_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_pc_v_count_d                     :16;	//15:0
	UINT32 r_nc_v_count_d                     :16;	//31:16
}PE_M17_IPC_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc900432cL IPC_STATUS_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_pc_nc_same_d                     :16;	//15:0
	UINT32 r_pn_v_count_d                     :16;	//31:16
}PE_M17_IPC_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004330L IPC_STATUS_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :6 ;	//5:0
	UINT32 r_fmd_32_min_th_flag_d             :1 ;	//6 
	UINT32 r_fmd_32_max_th_flag_d             :1 ;	//7 
	UINT32 r_fmd_still_limit_flag_d           :1 ;	//8 
	UINT32 r_fmd_still_pn_th2_flag_d          :1 ;	//9 
	UINT32 r_fmd_still_pn_th_flag_d           :1 ;	//10
	UINT32 r_fmd_still_prev_ratio_flag_d      :1 ;	//11
	UINT32 r_fmd_bigger_flag_d                :1 ;	//12
	UINT32 r_fmd_smaller_flag_d               :1 ;	//13
	UINT32 r_fmd_3_2_fmd_comb_mode_d          :2 ;	//15:14
	UINT32 r_pn_diff_count_d                  :16;	//31:16
}PE_M17_IPC_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc9004334L IPC_STATUS_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 r_inv_inversed_cnt                 :16;	//15:0
	UINT32 r_inv_original_cnt                 :16;	//31:16
}PE_M17_IPC_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004338L IPC_STATUS_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_IPC_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc900433cL IPC_STATUS_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_IPC_STATUS_09_T;
/*-----------------------------------------------------------------------------
                             0xc9004340L TPD_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_show_scale                     :3 ;	//2:0
	UINT32 reg_bbd_show                       :1 ;	//3 
	UINT32 reg_show_bar_1                     :1 ;	//4 
	UINT32 reg_show_bar_2                     :1 ;	//5 
	UINT32 reg_show_bar_3                     :1 ;	//6 
	UINT32 reg_bar1_data_mux                  :2 ;	//8:7
	UINT32 reg_bar2_data_mux                  :2 ;	//10:9
	UINT32 reg_bar3_data_mux                  :2 ;	//12:11
	UINT32 reg_hist0_data_mux                 :4 ;	//16:13
	UINT32 reg_hist1_data_mux                 :4 ;	//20:17
	UINT32 reg_hist2_data_mux                 :4 ;	//24:21
	UINT32 reg_hist0_win_sel                  :2 ;	//26:25
	UINT32 reg_hist1_win_sel                  :2 ;	//28:27
	UINT32 reg_hist2_win_sel                  :2 ;	//30:29
	UINT32 reg_status_eo_sel                  :1 ;	//31
}PE_M17_TPD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004344L TPD_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 wina_x0                            :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_wina_hen                       :1 ;	//15
	UINT32 wina_y0                            :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_wina_ven                       :1 ;	//31
}PE_M17_TPD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004348L TPD_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 wina_x1                            :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 wina_y1                            :12;	//27:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_hist_hsv_hsl_sel               :1 ;	//30
	UINT32 reg_hist_vscaling_en               :1 ;	//31
}PE_M17_TPD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900434cL TPD_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 winb_x0                            :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_winb_hen                       :1 ;	//15
	UINT32 winb_y0                            :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_winb_ven                       :1 ;	//31
}PE_M17_TPD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004350L TPD_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 winb_x1                            :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 winb_y1                            :12;	//27:16
}PE_M17_TPD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9004354L TPD_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 winc_x0                            :12;	//11:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_winc_hen                       :1 ;	//15
	UINT32 winc_y0                            :12;	//27:16
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_winc_ven                       :1 ;	//31
}PE_M17_TPD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004358L TPD_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 winc_x1                            :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 winc_y1                            :12;	//27:16
}PE_M17_TPD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900435cL TPD_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_force_y                        :10;	//9:0
	UINT32 reg_force_y_max_th                 :10;	//19:10
	UINT32 reg_force_y_min_th                 :10;	//29:20
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_force_y_enable                 :1 ;	//31
}PE_M17_TPD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004360L TPD_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_force_cb                       :10;	//9:0
	UINT32 reg_force_cb_max_th                :10;	//19:10
	UINT32 reg_force_cb_min_th                :10;	//29:20
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_force_cb_enable                :1 ;	//31
}PE_M17_TPD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9004364L TPD_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_force_cr                       :10;	//9:0
	UINT32 reg_force_cr_max_th                :10;	//19:10
	UINT32 reg_force_cr_min_th                :10;	//29:20
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_force_cr_enable                :1 ;	//31
}PE_M17_TPD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9004368L TPD_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_pixel_count                   :22;	//21:0
}PE_M17_TPD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900436cL CLC_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cl_lcount_enable                   :1 ;	//0 
	UINT32 cl_lcnt_mode                       :2 ;	//2:1
	UINT32 cl_scene_change_enable             :1 ;	//3 
	UINT32 cl_scene_change_mode               :1 ;	//4 
	UINT32 cl_scene_change_manual             :1 ;	//5 
	UINT32 cl_lcnt_th                         :4 ;	//9:6
	UINT32 cl_plus_lcount                     :3 ;	//12:10
	UINT32 cl_minus_lcount                    :2 ;	//14:13
	UINT32 cl_scene_change_protect            :1 ;	//15
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 cl_tearing_pt_th2                  :12;	//31:20
}PE_M17_CLC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004370L BBD_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bbd_en                         :1 ;	//0 
	UINT32 reg_hys_mode                       :5 ;	//5:1
	UINT32 reg_op_mode                        :1 ;	//6 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_cnt_th                         :8 ;	//15:8
	UINT32 reg_diff_th                        :8 ;	//23:16
	UINT32 reg_bbd_mux                        :3 ;	//26:24
	UINT32 reg_apl_mux                        :3 ;	//29:27
	UINT32 reg_apl_win_sel                    :2 ;	//31:30
}PE_M17_BBD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004374L BBD_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y0                                 :12;	//27:16
}PE_M17_BBD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004378L BBD_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_BBD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900437cL BBD_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y0                                 :12;	//27:16
}PE_M17_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004380L BBD_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004384L APL_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 y_g_s_apl                          :10;	//9:0
	UINT32 cb_b_s_apl                         :10;	//19:10
	UINT32 cr_r_s_apl                         :10;	//29:20
}PE_M17_APL_STAT_00_T;
/*-----------------------------------------------------------------------------
		0xc9004388L pe1_fsw_ctrl_00 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd0_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd0_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd0_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd0_hue_bin_9                      : 8 ;  // 31:24
} PE_M17_PE1_FSW_CTRL_00_T;

/*-----------------------------------------------------------------------------
		0xc900438cL pe1_fsw_ctrl_01 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd1_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd1_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd1_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd1_hue_bin_9                      : 8 ;  // 31:24
} PE_M17_PE1_FSW_CTRL_01_T;

/*-----------------------------------------------------------------------------
                             0xc9004390L TPD_HIST_AI_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hif_hist_address                   :5 ;	//4:0
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 hif_hist_ai                        :1 ;	//12
	UINT32 reg_read_hist_sel                  :2 ;	//14:13
	UINT32 hif_hist_enable                    :1 ;	//15
	UINT32 reserved02                         :12;	//reserved
	UINT32 hist_rd_available                  :1 ;	//28
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 hist_rd_en                         :1 ;	//30
	UINT32 hist_read_done                     :1 ;	//31
}PE_M17_TPD_HIST_AI_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9004394L TPD_HIST_AI_DATA                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_status                        :22;	//21:0
}PE_M17_TPD_HIST_AI_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9004398L LVCRTL_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 enable                             :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 y_offset                           :10;	//13:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 center_position                    :8 ;	//23:16
	UINT32 y_gain                             :8 ;	//31:24
}PE_M17_LVCRTL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90043a0L TNR_STATUS_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc90043a4L TNR_STATUS_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc90043a8L TNR_STATUS_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc90043acL TNR_STATUS_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc90043c0L TNR_RESET                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_gmv_rst                        :1 ;	//0 
	UINT32 reg_bmv_rst                        :1 ;	//1 
	UINT32 reg_me_rst                         :1 ;	//2 
	UINT32 reg_mc_rst                         :1 ;	//3 
	UINT32 reg_ma_rst                         :1 ;	//4 
}PE_M17_TNR_RESET_T;
/*-----------------------------------------------------------------------------
                             0xc90043d0L TNR_CTRL_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_a_normalize_en                 :1 ;	//2 
	UINT32 reg_t_normalize_en                 :1 ;	//3 
	UINT32 reg_t_cut_resolution               :2 ;	//5:4
	UINT32 reg_ne_normalize_en                :1 ;	//6 
	UINT32 reserved02                         :9 ;	//reserved
	UINT32 reg_cross_th_ne                    :8 ;	//23:16
	UINT32 reg_cross_th                       :8 ;	//31:24
}PE_M17_TNR_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc90043d4L TNR_CTRL_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mul_base_t                     :8 ;	//7:0
	UINT32 reg_mul_base_e                     :8 ;	//15:8
}PE_M17_TNR_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90043d8L TNR_CTRL_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_a_lut_edge_y0                  :8 ;	//7:0
	UINT32 reg_a_lut_edge_x0                  :8 ;	//15:8
	UINT32 reg_a_lut_edge_y1                  :8 ;	//23:16
	UINT32 reg_a_lut_edge_x1                  :8 ;	//31:24
}PE_M17_TNR_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90043dcL TNR_CTRL_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_a_lut_detail_y0                :8 ;	//7:0
	UINT32 reg_a_lut_detail_x0                :8 ;	//15:8
	UINT32 reg_a_lut_detail_y1                :8 ;	//23:16
	UINT32 reg_a_lut_detail_x1                :8 ;	//31:24
}PE_M17_TNR_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90043e0L TNR_CTRL_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_t_lut_edge_y0                  :8 ;	//7:0
	UINT32 reg_t_lut_edge_x0                  :8 ;	//15:8
	UINT32 reg_t_lut_edge_y1                  :8 ;	//23:16
	UINT32 reg_t_lut_edge_x1                  :8 ;	//31:24
}PE_M17_TNR_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90043e4L TNR_CTRL_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_t_lut_detail_y0                :8 ;	//7:0
	UINT32 reg_t_lut_detail_x0                :8 ;	//15:8
	UINT32 reg_t_lut_detail_y1                :8 ;	//23:16
	UINT32 reg_t_lut_detail_x1                :8 ;	//31:24
}PE_M17_TNR_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90043e8L TNR_CTRL_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_edge_minmax_y0                 :8 ;	//7:0
	UINT32 reg_edge_minmax_x0                 :8 ;	//15:8
	UINT32 reg_edge_minmax_y1                 :8 ;	//23:16
	UINT32 reg_edge_minmax_x1                 :8 ;	//31:24
}PE_M17_TNR_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90043ecL TNR_CTRL_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_detail_minmax_y0               :8 ;	//7:0
	UINT32 reg_detail_minmax_x0               :8 ;	//15:8
	UINT32 reg_detail_minmax_y1               :8 ;	//23:16
	UINT32 reg_detail_minmax_x1               :8 ;	//31:24
}PE_M17_TNR_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90043f0L TNR_CTRL_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sel_ne_type                    :2 ;	//1:0
	UINT32 reg_sel_re_type                    :1 ;	//2 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_sel_at_mode                    :2 ;	//5:4
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 reg_hist_xscale                    :3 ;	//10:8
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 reg_hist_yscale                    :2 ;	//13:12
	UINT32 reserved04                         :2 ;	//reserved
	UINT32 reg_th_atmap                       :8 ;	//23:16
	UINT32 reg_th_motion                      :8 ;	//31:24
}PE_M17_TNR_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc9004400L TNR_NE_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 valid_cnt                          :16;	//15:0
}PE_M17_TNR_NE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004404L TNR_NE_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_1                             :16;	//15:0
	UINT32 hist_0                             :16;	//31:16
}PE_M17_TNR_NE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004408L TNR_NE_STAT_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_3                             :16;	//15:0
	UINT32 hist_2                             :16;	//31:16
}PE_M17_TNR_NE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900440cL TNR_NE_STAT_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_5                             :16;	//15:0
	UINT32 hist_4                             :16;	//31:16
}PE_M17_TNR_NE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004410L TNR_NE_STAT_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_7                             :16;	//15:0
	UINT32 hist_6                             :16;	//31:16
}PE_M17_TNR_NE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9004414L TNR_NE_STAT_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_9                             :16;	//15:0
	UINT32 hist_8                             :16;	//31:16
}PE_M17_TNR_NE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9004418L TNR_NE_STAT_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_11                            :16;	//15:0
	UINT32 hist_10                            :16;	//31:16
}PE_M17_TNR_NE_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900441cL TNR_NE_STAT_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_13                            :16;	//15:0
	UINT32 hist_12                            :16;	//31:16
}PE_M17_TNR_NE_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9004420L TNR_NE_STAT_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_15                            :16;	//15:0
	UINT32 hist_14                            :16;	//31:16
}PE_M17_TNR_NE_STAT_08_T;
/*-----------------------------------------------------------------------------
                             0xc9004480L ND_FSW_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 chroma_st_flt_ctrl_x0              : 8 ;  //  7: 0     
	UINT32 chroma_st_flt_ctrl_x1              : 8 ;  // 15: 8     
	UINT32 luma_st_flt_ctrl_x0                : 8 ;  // 23:16     
	UINT32 luma_st_flt_ctrl_x1                : 8 ;  // 31:24     
}PE_M17_ND_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004484L ND_FSW_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 motion_x_tearing_gain              : 8 ;  //  7: 0     
	UINT32 motion_gain                        : 8 ;  // 15: 8     
}PE_M17_ND_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004488L ND_FSW_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_ND_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900448cL ND_FSW_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_ND_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9004490L TNR_ETC_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_y0                             :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_x0                             :13;	//28:16
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 win_mode                           :1 ;	//30
	UINT32 win_en                             :1 ;	//31
}PE_M17_TNR_ETC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9004494L TNR_ETC_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 win_y1                             :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 win_x1                             :13;	//28:16
	UINT32 reserved02                         :2 ;	//reserved
	UINT32 win_tnrw_en                        :1 ;	//31
}PE_M17_TNR_ETC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9004498L TNR_ETC_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 minfo_tnr_rd_m_delay               :4 ;	//3:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 minfo_tnr_rd_mv_delay              :4 ;	//11:8
	UINT32 reserved02                         :4 ;	//reserved
	UINT32 minfo_tnr_wr_m_delay               :4 ;	//19:16
	UINT32 minfo_lstart_delay                 :4 ;	//23:20
	UINT32 minfo_clc_offset                   :2 ;	//25:24
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 minfo_tnr_wr_mv_delay              :4 ;	//31:28
}PE_M17_TNR_ETC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900449cL TNR_ETC_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;	//31:0
}PE_M17_TNR_ETC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90044a0L TNR_CTRL_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_mc_ctrl_pt_y0              :8 ;	//7:0
	UINT32 reg_sad_mc_ctrl_pt_x0              :8 ;	//15:8
	UINT32 reg_sad_mc_ctrl_pt_y1              :8 ;	//23:16
	UINT32 reg_sad_mc_ctrl_pt_x1              :8 ;	//31:24
}PE_M17_TNR_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc90044a4L TNR_CTRL_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_mc_ctrl_pt_y2              :8 ;	//7:0
	UINT32 reg_sad_mc_ctrl_pt_x2              :8 ;	//15:8
	UINT32 reg_sad_mc_ctrl_pt_y3              :8 ;	//23:16
	UINT32 reg_sad_mc_ctrl_pt_x3              :8 ;	//31:24
}PE_M17_TNR_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc90044a8L TNR_CTRL_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_abs_mv_ctrl_pt_y0              :8 ;	//7:0
	UINT32 reg_abs_mv_ctrl_pt_x0              :8 ;	//15:8
	UINT32 reg_abs_mv_ctrl_pt_y1              :8 ;	//23:16
	UINT32 reg_abs_mv_ctrl_pt_x1              :8 ;	//31:24
}PE_M17_TNR_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc90044acL TNR_CTRL_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_abs_mv_ctrl_pt_y2              :8 ;	//7:0
	UINT32 reg_abs_mv_ctrl_pt_x2              :8 ;	//15:8
	UINT32 reg_abs_mv_ctrl_pt_y3              :8 ;	//23:16
	UINT32 reg_abs_mv_ctrl_pt_x3              :8 ;	//31:24
}PE_M17_TNR_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc90044b0L TNR_CTRL_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_ma_ctrl_pt_y0              :8 ;	//7:0
	UINT32 reg_sad_ma_ctrl_pt_x0              :8 ;	//15:8
	UINT32 reg_sad_ma_ctrl_pt_y1              :8 ;	//23:16
	UINT32 reg_sad_ma_ctrl_pt_x1              :8 ;	//31:24
}PE_M17_TNR_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc90044b4L TNR_CTRL_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sad_ma_ctrl_pt_y2              :8 ;	//7:0
	UINT32 reg_sad_ma_ctrl_pt_x2              :8 ;	//15:8
	UINT32 reg_sad_ma_ctrl_pt_y3              :8 ;	//23:16
	UINT32 reg_sad_ma_ctrl_pt_x3              :8 ;	//31:24
}PE_M17_TNR_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc90044b8L PE0_DEBUG3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 mif_prefetch_ctrl                  :8 ;	//7:0
}PE_M17_PE0_DEBUG3_T;


/*-----------------------------------------------------------------------------
                             0xc9008100L PE0_DNR_LOAD
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 load_enable                        :1 ;	//1 
	UINT32 load_type                          :1 ;	//2 
}PE_M17_PE0_DNR_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9008104L PE0_DNR_INTR
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 intr_enable                        :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 intr_src                           :3 ;	//6:4
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 timer_rst_sel                      :1 ;	//8 
	UINT32 reserved03                         :7 ;	//reserved
	UINT32 intr_line_pos                      :11;	//26:16
}PE_M17_PE0_DNR_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9008108L PE0_DNR_STATUS0
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 dnr_frame_id                       :8 ;	//23:16
	UINT32 pic_init_frame_id                  :4 ;	//27:24
}PE_M17_PE0_DNR_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc900810cL PE0_DNR_STATUS1
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 line_cnt                           :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 timer_cnt                          :16;	//31:16
}PE_M17_PE0_DNR_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9008110L PE0_DNR_OPMODE
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_sd_5l_mode_en                  :1 ;	//8 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 dnr_out_420_vsample_mode           :1 ;	//12
	UINT32 dnr_out_cs_type                    :3 ;	//15:13
	UINT32 detour_enable                      :1 ;	//16
	UINT32 half_rate_en                       :1 ;	//17
	UINT32 reserved03                         :2 ;	//reserved
	UINT32 ibuf_en                            :2 ;	//21:20
	UINT32 dnr_out_422_hsample_mode           :1 ;	//22
	UINT32 reserved04                         :1 ;	//reserved
	UINT32 dnr_in_lsb_mode                    :2 ;	//25:24
	UINT32 dnr_out_lsb_mode                   :2 ;	//27:26
	UINT32 reserved05                         :2 ;	//reserved
	UINT32 m_run_id                           :2 ;	//31:30
}PE_M17_PE0_DNR_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9008114L PE0_DNR_IN_SIZE
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsize                              :12;	//11:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 chroma_sampling_type               :3 ;	//15:13
	UINT32 vsize                              :12;	//27:16
}PE_M17_PE0_DNR_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9008118L PE0_DNR_IN_OFFSET
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hoffset                            :12;	//11:0
	UINT32 reserved01                         :18;	//reserved
	UINT32 hsize_sel                          :1 ;	//30
	UINT32 crop_en                            :1 ;	//31
}PE_M17_PE0_DNR_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900811cL PE0_OUT_SIZE                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hsize                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 vsize                              :12;	//27:16
}PE_M17_PE0_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9008120L WIN_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 y0                                 :12;	//27:16
}PE_M17_WIN_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008124L WIN_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_WIN_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9008128L WIN_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x0                                 :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 y0                                 :12;	//27:16
	UINT32 ac_bnr_feature_cal_mode            :2 ;	//29:28
}PE_M17_WIN_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900812cL WIN_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 x1                                 :11;	//10:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 y1                                 :12;	//27:16
}PE_M17_WIN_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9008130L CUP_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bypass                             :1 ;	//0 
	UINT32 reg_v_upsample_en                  :1 ;	//1 
	UINT32 reg_h_upsample_en                  :1 ;	//2 
	UINT32 reg_sd_mode                        :1 ;	//3 
}PE_M17_CUP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008134L CUP_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :1 ;	//0 
	UINT32 bypass                             :1 ;	//1 
	UINT32 reg_v_upsample_en                  :1 ;	//2 
	UINT32 reg_h_upsample_en                  :1 ;	//3 
}PE_M17_CUP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008138L CUP_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_CUP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9008150L _3DFD_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 aw_offset_x                        :8 ;	//7:0
	UINT32 aw_offset_y                        :8 ;	//15:8
	UINT32 cb_th1                             :8 ;	//23:16
	UINT32 cb_th2                             :8 ;	//31:24
}PE_M17__3DFD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008154L _3DFD_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cc_th1                             :8 ;	//7:0
	UINT32 cc_th2                             :8 ;	//15:8
	UINT32 ll_th1                             :8 ;	//23:16
	UINT32 ll_th2                             :8 ;	//31:24
}PE_M17__3DFD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008158L _3DFD_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pt_th                              :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 sstb_th                            :8 ;	//23:16
	UINT32 debug_mode                         :3 ;	//26:24
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 div_mode                           :1 ;	//28
}PE_M17__3DFD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900815cL _3DFD_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 small_delta_th                     :19;	//18:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 small_delta_en                     :1 ;	//24
}PE_M17__3DFD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008160L _3DFD_STAT_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cb_count                           :16;	//15:0
	UINT32 cc_count                           :16;	//31:16
}PE_M17__3DFD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008164L _3DFD_STAT_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ll_count                           :16;	//15:0
	UINT32 trid_format                        :4 ;	//19:16
}PE_M17__3DFD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008168L _3DFD_STAT_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 delta_ss_h                         :23;	//22:0
}PE_M17__3DFD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900816cL _3DFD_STAT_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 delta_ss_v                         :23;	//22:0
}PE_M17__3DFD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008170L _3DFD_STAT_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 delta_tb_v                         :23;	//22:0
}PE_M17__3DFD_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008174L _3DFD_STAT_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 delta_tb_h                         :23;	//22:0
}PE_M17__3DFD_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008178L _3DFD_STAT_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 ss_ratio                           :23;	//22:0
}PE_M17__3DFD_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900817cL _3DFD_STAT_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 tb_ratio                           :23;	//22:0
}PE_M17__3DFD_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008180L VFILTER_CTRL_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_glb_tearing_th                 :8 ;	//7:0
	UINT32 reg_glb_mode_th                    :4 ;	//11:8
	UINT32 reg_tearing_strength               :1 ;	//12
	UINT32 reg_glb_tearing_cnt_normal         :3 ;	//15:13
	UINT32 reg_vf_a_th                        :8 ;	//23:16
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_vflt_force_en                  :1 ;	//30
	UINT32 reg_vflt_en                        :1 ;	//31
}PE_M17_VFILTER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9008184L VFILTER_CTRL_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_vflt_debug_en                  :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_fmd_mode                       :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_glb_mode                       :1 ;	//8 
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_glb_mode_fw_en                 :1 ;	//12
	UINT32 reserved04                         :3 ;	//reserved
	UINT32 reg_glb_vflt_en                    :1 ;	//16
	UINT32 reserved05                         :3 ;	//reserved
	UINT32 reg_fmd_vflt_en                    :1 ;	//20
	UINT32 reserved06                         :3 ;	//reserved
	UINT32 reg_fmd_tearing_cnt_en             :1 ;	//24
	UINT32 reserved07                         :3 ;	//reserved
	UINT32 reg_fmd_motion_en                  :1 ;	//28
}PE_M17_VFILTER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9008188L VFILTER_CTRL_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hmc_vflt_en                    :1 ;	//0 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_hmc_tearing_cnt_en             :1 ;	//4 
	UINT32 reserved02                         :3 ;	//reserved
	UINT32 reg_hmc_motion_en                  :1 ;	//8 
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_loc_vflt_en                    :1 ;	//12
	UINT32 reserved04                         :3 ;	//reserved
	UINT32 reg_loc_tearing_cnt_en             :1 ;	//16
	UINT32 reserved05                         :3 ;	//reserved
	UINT32 reg_loc_motion_en_                 :1 ;	//20
	UINT32 reserved06                         :3 ;	//reserved
	UINT32 reg_alpha_sel_mode                 :2 ;	//25:24
	UINT32 reserved07                         :2 ;	//reserved
	UINT32 reg_alpha_sel_mode_en              :2 ;	//29:28
}PE_M17_VFILTER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900818cL CTI_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cti_en                             :1 ;	//0 
	UINT32 cti_clipping_mode                  :1 ;	//1 
	UINT32 cti_pre_flt_mode                   :2 ;	//3:2
	UINT32 cti_tap                            :1 ;	//4 
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 cti_gain                           :8 ;	//15:8
	UINT32 cti_debug_mode                     :3 ;	//18:16
}PE_M17_CTI_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008190L CTI_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 cti_coring_th0                     :8 ;	//7:0
	UINT32 cti_coring_th1                     :8 ;	//15:8
	UINT32 cti_coring_smooth                  :3 ;	//18:16
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_cti_tap2                       :2 ;	//21:20
}PE_M17_CTI_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9008194L DNR_MAX_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dnr_max_enable                 :1 ;	//0 
	UINT32 reg_ifc_max_enable                 :1 ;	//1 
	UINT32 reg_dnr_ifc_sel                    :1 ;	//2 
	UINT32 reg_decon_max_sum_sel              :1 ;	//3 
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_max_dbg_en                     :1 ;	//8 
	UINT32 reg_dnr_motion_sel                 :1 ;	//9 
	UINT32 reserved02                         :6 ;	//reserved
	UINT32 reg_win_en                         :1 ;	//16
	UINT32 reg_bdr_en                         :1 ;	//17
	UINT32 reg_win_inout                      :1 ;	//18
	UINT32 reserved03                         :3 ;	//reserved
	UINT32 reg_motion_bit_ctrl                :3 ;	//24:22
	UINT32 reg_delta_ifc_th                   :7 ;	//31:25
}PE_M17_DNR_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9008198L DNR_DBAR_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dbg_en                         :1 ;	//0 
	UINT32 reg_show_f3d                       :1 ;	//1 
	UINT32 reg_show_bnr                       :1 ;	//2 
	UINT32 reg_f3d_mode                       :1 ;	//3 
	UINT32 reg_acness_or_acness_gain          :1 ;	//4 
}PE_M17_DNR_DBAR_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900819cL REG_C420_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 reg_detect_level_th                :10;	//25:16
}PE_M17_REG_C420_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90081a0L MNR_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mnr_enable                     :1 ;	//0 
	UINT32 reg_mnr_debug                      :1 ;	//1 
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_mnr_chroma_en                  :1 ;	//3 
	UINT32 reg_h_expand                       :2 ;	//5:4
	UINT32 reg_sel_mmd                        :2 ;	//7:6
	UINT32 reg_mnr_master_gain                :8 ;	//15:8
	UINT32 reg_snr_th                         :8 ;	//23:16
	UINT32 reg_th_max                         :8 ;	//31:24
}PE_M17_MNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90081a4L MNR_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mmd_y_max                      :8 ;	//7:0
	UINT32 reg_mmd_y_min                      :8 ;	//15:8
	UINT32 reg_mmd_x_max                      :8 ;	//23:16
	UINT32 reg_mmd_x_min                      :8 ;	//31:24
}PE_M17_MNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90081a8L MNR_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mnr_debug_mode                 :3 ;	//2:0
	UINT32 reg_mnr_debug_en                   :1 ;	//3 
	UINT32 reserved01                         :20;	//reserved
	UINT32 reg_equal_snr_th                   :8 ;	//31:24
}PE_M17_MNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90081acL MNR_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blur_sel                       :1 ;	//0 
	UINT32 reg_pattern_en                     :1 ;	//1 
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_pattern_th                     :8 ;	//15:8
	UINT32 reg_equal_th                       :8 ;	//23:16
	UINT32 reg_mmd_scale                      :8 ;	//31:24
}PE_M17_MNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90081b0L MNR_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mmd_fil_x_3                    :8 ;	//7:0
	UINT32 reg_mmd_fil_x_2                    :8 ;	//15:8
	UINT32 reg_mmd_fil_x_1                    :8 ;	//23:16
	UINT32 reg_mmd_fil_x_0                    :8 ;	//31:24
}PE_M17_MNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90081b4L MNR_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mmd_fil_y_3                    :8 ;	//7:0
	UINT32 reg_mmd_fil_y_2                    :8 ;	//15:8
	UINT32 reg_mmd_fil_y_1                    :8 ;	//23:16
	UINT32 reg_mmd_fil_y_0                    :8 ;	//31:24
}PE_M17_MNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90081b8L DETAIL_CTRL                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_detail_max              :8 ;	//7:0
	UINT32 reg_bnr_ac_detail_min              :8 ;	//15:8
	UINT32 reg_bnr_diff_l                     :8 ;	//23:16
	UINT32 reg_bnr_diff_p                     :8 ;	//31:24
}PE_M17_DETAIL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90081bcL DC_BNR_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dc_bnr_enable                  :1 ;	//0 
	UINT32 reg_dc_blur_debug_mode             :1 ;	//1 
	UINT32 reg_dc_blur_sel                    :2 ;	//3:2
	UINT32 reg_dc_output_debug_mode           :4 ;	//7:4
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_dc_motion_max                  :8 ;	//23:16
	UINT32 reg_dc_motion_min                  :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90081c0L DC_BNR_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_manual_fil_motion_gain         :8 ;	//15:8
	UINT32 reg_var_chroma_en                  :1 ;	//16
	UINT32 reg_fil_manual_en                  :1 ;	//17
	UINT32 reg_dc_pattern_en                  :1 ;	//18
	UINT32 reg_luma_gain_en                   :1 ;	//19
	UINT32 reg_var_v_gain                     :4 ;	//23:20
	UINT32 reg_var_h_gain                     :4 ;	//27:24
	UINT32 reg_var_cut_resolution             :4 ;	//31:28
}PE_M17_DC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90081c4L DC_BNR_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dc_var_en                      :1 ;	//0 
	UINT32 reg_dc_motion_en                   :1 ;	//1 
	UINT32 reg_dc_protection_en               :1 ;	//2 
	UINT32 reserved01                         :7 ;	//reserved
	UINT32 reg_dc_bnr_mastergain              :6 ;	//15:10
	UINT32 reg_dc_bnr_chromagain              :8 ;	//23:16
	UINT32 reg_dc_protection_th               :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90081c8L DC_BNR_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dc_bnr_var_th3                 :8 ;	//7:0
	UINT32 reg_dc_bnr_var_th2                 :8 ;	//15:8
	UINT32 reg_dc_bnr_var_th1                 :8 ;	//23:16
	UINT32 reg_dc_bnr_var_th0                 :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90081ccL DC_BNR_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dc_motion_y_min                :8 ;	//7:0
	UINT32 reg_dc_motion_y_max                :8 ;	//15:8
}PE_M17_DC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90081d0L DC_BNR_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_dc_var_y_th0                   :8 ;	//7:0
	UINT32 reg_dc_var_y_th1                   :8 ;	//15:8
	UINT32 reg_dc_var_y_th2                   :8 ;	//23:16
	UINT32 reg_dc_var_y_th3                   :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90081d4L AC_BNR_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_h_en                    :1 ;	//0 
	UINT32 reg_bnr_ac_v_en                    :1 ;	//1 
	UINT32 reg_bnr_ac_h_chroma_en             :1 ;	//2 
	UINT32 reg_bnr_ac_v_chroma_en             :1 ;	//3 
	UINT32 reg_bnr_ac_acness_resol_h          :2 ;	//5:4
	UINT32 reg_multi_run_mode                 :1 ;	//6 
	UINT32 reg_ac_bnr_gain_yc_sel             :1 ;	//7 
	UINT32 reg_bnr_ac_diff_min_v_th           :8 ;	//15:8
	UINT32 reg_bnr_ac_diff_min_h_th           :8 ;	//23:16
	UINT32 reg_bnr_ac_iir_gain                :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90081d8L AC_BNR_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_global_motion_th        :8 ;	//7:0
	UINT32 reg_bnr_ac_h_acness_max            :8 ;	//15:8
	UINT32 reg_bnr_ac_h_acness_min            :8 ;	//23:16
	UINT32 reg_bnr_ac_bin_th                  :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90081dcL AC_BNR_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_motion_3                :8 ;	//7:0
	UINT32 reg_bnr_ac_motion_2                :8 ;	//15:8
	UINT32 reg_bnr_ac_motion_1                :8 ;	//23:16
	UINT32 reg_bnr_ac_motion_0                :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90081e0L DNR_STAT_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 c420_tearing_cnt                   :16;	//15:0
	UINT32 global_motion_iir                  :8 ;	//23:16
	UINT32 global_dc_gain                     :8 ;	//31:24
}PE_M17_DNR_STAT_0_T;
/*-----------------------------------------------------------------------------
                             0xc90081e4L AC_BNR_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_motion_y_3              :8 ;	//7:0
	UINT32 reg_bnr_ac_motion_y_2              :8 ;	//15:8
	UINT32 reg_bnr_ac_motion_y_1              :8 ;	//23:16
	UINT32 reg_bnr_ac_motion_y_0              :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90081e8L AC_BNR_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_v_init_offset           :3 ;	//2:0
	UINT32 reg_bnr_ac_h_init_offset           :3 ;	//5:3
	UINT32 reg_bnr_ac_acness_resol_v          :2 ;	//7:6
	UINT32 reg_bnr_ac_debug_mode              :4 ;	//11:8
	UINT32 reg_bnr_ac_hsy_mode                :4 ;	//15:12
	UINT32 reg_bnr_ac_v_acness_max            :8 ;	//23:16
	UINT32 reg_bnr_ac_v_acness_min            :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90081ecL DNR_STAT_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 acness_v_l                         :8 ;	//7:0
	UINT32 acness_h_l                         :8 ;	//15:8
	UINT32 acness_v_g                         :8 ;	//23:16
	UINT32 acness_h_g                         :8 ;	//31:24
}PE_M17_DNR_STAT_1_T;
/*-----------------------------------------------------------------------------
                             0xc90081f0L AC_BNR_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_detail_th4              :8 ;	//7:0
	UINT32 reg_bnr_ac_detail_th3              :8 ;	//15:8
	UINT32 reg_bnr_ac_detail_th2              :8 ;	//23:16
	UINT32 reg_bnr_ac_detail_th1              :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90081f4L AC_BNR_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_pos_gain_h2             :8 ;	//7:0
	UINT32 reg_bnr_ac_pos_gain_h1             :8 ;	//15:8
	UINT32 reg_bnr_ac_pos_gain_h0             :8 ;	//23:16
	UINT32 reg_bnr_ac_detail_gain_th          :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90081f8L AC_BNR_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bnr_ac_pos_gain_l2             :8 ;	//7:0
	UINT32 reg_bnr_ac_pos_gain_l1             :8 ;	//15:8
	UINT32 reg_bnr_ac_pos_gain_l0             :8 ;	//23:16
	UINT32 reg_bnr_ac_pos_gain_h3             :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90081fcL DNR_STAT_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 h_init                             :8 ;	//7:0
	UINT32 v_init                             :8 ;	//15:8
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 reg_vfilter_tearing_cnt            :12;	//31:20
}PE_M17_DNR_STAT_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008200L AC_BNR_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_ac_master_c_gain               :8 ;	//7:0
	UINT32 reg_ac_bnr_enable                  :1 ;	//8 
	UINT32 reg_ac_bnr_motion_en               :1 ;	//9 
	UINT32 reg_ac_bnr_acness_en               :1 ;	//10
	UINT32 reg_ac_bnr_position_en             :1 ;	//11
	UINT32 reg_detail_sel                     :1 ;	//12
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_bnr_ac_manual_init_v           :3 ;	//18:16
	UINT32 reg_ac_manual_init_en_v            :1 ;	//19
	UINT32 reg_bnr_ac_manual_init_h           :3 ;	//22:20
	UINT32 reg_ac_manual_init_en_h            :1 ;	//23
	UINT32 reg_bnr_ac_pos_gain_l3             :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9008204L AC_BNR_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_acness_sel                     :1 ;	//0 
	UINT32 reg_g_motion_manual_en             :1 ;	//1 
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_ac_bnr_debug_h_en              :1 ;	//8 
	UINT32 reg_ac_bnr_debug_v_en              :1 ;	//9 
	UINT32 reg_ac_master_y_gain               :6 ;	//15:10
	UINT32 reg_g_motion_scale                 :3 ;	//18:16
	UINT32 reg_g_motion_div                   :2 ;	//20:19
	UINT32 reserved02                         :10;	//reserved
	UINT32 reg_ac_flt_level_sel               :1 ;	//31
}PE_M17_AC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9008208L AC_BNR_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_ac_detail_gain_y_min           :8 ;	//7:0
	UINT32 reg_ac_detail_gain_y_max           :8 ;	//15:8
	UINT32 reg_bnr_ac_acness_y_min            :8 ;	//23:16
	UINT32 reg_bnr_ac_acness_y_max            :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900820cL AC_BNR_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_ac_detail_alpha2_y_min         :8 ;	//7:0
	UINT32 reg_ac_detail_alpha2_y_max         :8 ;	//15:8
	UINT32 reg_ac_detail_alpha4_y_min         :8 ;	//23:16
	UINT32 reg_ac_detail_alpha4_y_max         :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008210L AC_BNR_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_g_motion_manual                :8 ;	//7:0
	UINT32 reg_acness_scale_mul               :8 ;	//15:8
	UINT32 reg_bnr_ac_detail_max              :8 ;	//23:16
	UINT32 reg_bnr_ac_detail_min              :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9008214L IFC_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_y_drvt_hcoef_sel               :3 ;	//2:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_y_ddrvt_hcoef_sel              :2 ;	//5:4
	UINT32 reg_y_edge_gain_res                :1 ;	//6 
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_y_drvt2_hcoef_sel              :3 ;	//10:8
	UINT32 reg_medge_meth                     :1 ;	//11
	UINT32 reg_medge_th                       :8 ;	//19:12
	UINT32 reg_medge_coring_th                :8 ;	//27:20
	UINT32 reg_medge_ch_tap                   :2 ;	//29:28
	UINT32 reg_edge_meth                      :2 ;	//31:30
}PE_M17_IFC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008218L IFC_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_edge_ddrvt_gain_y1             :8 ;	//7:0
	UINT32 reg_edge_ddrvt_gain_x1             :8 ;	//15:8
	UINT32 reg_edge_ddrvt_gain_y0             :8 ;	//23:16
	UINT32 reg_edge_ddrvt_gain_x0             :8 ;	//31:24
}PE_M17_IFC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900821cL IFC_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_c_drvt_hcoef_sel               :3 ;	//2:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_c_ddrvt_hcoef_sel              :2 ;	//5:4
	UINT32 reg_c_edge_gain_res                :1 ;	//6 
}PE_M17_IFC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008220L IFC_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_c_edge_gain_y1                 :8 ;	//7:0
	UINT32 reg_c_edge_gain_x1                 :8 ;	//15:8
	UINT32 reg_c_edge_gain_y0                 :8 ;	//23:16
	UINT32 reg_c_edge_gain_x0                 :8 ;	//31:24
}PE_M17_IFC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9008224L IFC_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_crs_para_tap                   :2 ;	//1:0
	UINT32 reg_cdst_th                        :10;	//11:2
	UINT32 reg_crs_op_tap                     :2 ;	//13:12
	UINT32 reg_crs_gain_res                   :1 ;	//14
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_cdiff_hcoef_sel                :2 ;	//17:16
	UINT32 reserved02                         :10;	//reserved
	UINT32 reg_crs_point                      :2 ;	//29:28
	UINT32 reg_crs_meth                       :2 ;	//31:30
}PE_M17_IFC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9008228L IFC_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :8 ;	//7:0
	UINT32 reg_crs_gain_y1                    :8 ;	//15:8
	UINT32 reg_crs_gain_x1                    :8 ;	//23:16
	UINT32 reg_crs_gain_y0                    :8 ;	//31:24
}PE_M17_IFC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900822cL IFC_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9008230L IFC_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9008234L IFC_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :1 ;	//0 
	UINT32 reg_ifc_en                         :1 ;	//1 
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_clp_on                         :1 ;	//4 
	UINT32 reserved02                         :15;	//reserved
	UINT32 reg_edge_en                        :2 ;	//21:20
	UINT32 reg_clp_tap                        :2 ;	//23:22
	UINT32 reg_ifc_flt_sel                    :2 ;	//25:24
	UINT32 reg_debug_en                       :4 ;	//29:26
	UINT32 reg_debug_mode                     :2 ;	//31:30
}PE_M17_IFC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9008238L IFC_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900823cL IFC_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008240L IFC_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008244L IFC_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 reserved                           :8 ;	//23:16
	UINT32 reg_crs_zero_th                    :8 ;	//31:24
}PE_M17_IFC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9008248L IFC_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900824cL IFC_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9008250L IFC_CTRL_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_medge_gain_y1                  :8 ;	//7:0
	UINT32 reg_medge_gain_x1                  :8 ;	//15:8
	UINT32 reg_medge_gain_y0                  :8 ;	//23:16
	UINT32 reg_medge_gain_x0                  :8 ;	//31:24
}PE_M17_IFC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008254L IFC_CTRL_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_crs_op_gain_isel               :2 ;	//1:0
	UINT32 reg_crs_op_gain_res                :1 ;	//2 
	UINT32 reg_crs_cdst_flt                   :3 ;	//5:3
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_crs_cdst_vmdn                  :1 ;	//7 
	UINT32 reg_crs_cdst_op_flt                :3 ;	//10:8
	UINT32 reserved02                         :5 ;	//reserved
	UINT32 reg_op_wgain_coef1                 :2 ;	//17:16
	UINT32 reg_op_wgain_coef2                 :2 ;	//19:18
	UINT32 reg_op_wgain_coef3                 :2 ;	//21:20
}PE_M17_IFC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008258L IFC_CTRL_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :8 ;	//7:0
	UINT32 reg_crs_op_gain_y1                 :8 ;	//15:8
	UINT32 reg_crs_op_gain_x1                 :8 ;	//23:16
	UINT32 reg_crs_op_gain_y0                 :8 ;	//31:24
}PE_M17_IFC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900825cL IFC_CTRL_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9008260L IFC_CTRL_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :16;	//reserved
	UINT32 reserved                           :8 ;	//23:16
	UINT32 reg_medge_op_th                    :1 ;	//24
	UINT32 reg_mmd_gain_en                    :2 ;	//26:25
	UINT32 reg_mmd_gain_flt                   :2 ;	//28:27
	UINT32 reg_mmd_gain_tap                   :1 ;	//29
}PE_M17_IFC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9008264L IFC_CTRL_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_IFC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9008268L IFC_CTRL_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mmd_gain_y1                    :8 ;	//7:0
	UINT32 reg_mmd_gain_x1                    :8 ;	//15:8
	UINT32 reg_mmd_gain_y0                    :8 ;	//23:16
	UINT32 reg_mmd_gain_x0                    :8 ;	//31:24
}PE_M17_IFC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc900826cL SC_BNR_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sc_bnr_en                      :1 ;	//0 
	UINT32 reg_sc_bnr_manual_h_en             :1 ;	//1 
	UINT32 reg_scene_ch_flag                  :1 ;	//2 
	UINT32 reg_iir_en                         :1 ;	//3 
	UINT32 reg_scale_mul_h                    :9 ;	//12:4
	UINT32 reg_scale_div_h                    :4 ;	//16:13
	UINT32 reg_sc_bnr_manual_v_en             :1 ;	//17
	UINT32 reg_sc_bnr_en_h                    :1 ;	//18
	UINT32 reg_sc_bnr_en_v                    :1 ;	//19
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_avg_scale_mul_h                :4 ;	//25:22
	UINT32 reg_avg_scale_div_h                :3 ;	//28:26
	UINT32 reg_max_index_diff_th              :3 ;	//31:29
}PE_M17_SC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008270L SC_BNR_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_post2_iir_gain                 :8 ;	//7:0
	UINT32 reg_frm_cnt_th                     :8 ;	//15:8
	UINT32 reg_bin_ratio_th                   :8 ;	//23:16
	UINT32 reg_detect_th                      :8 ;	//31:24
}PE_M17_SC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9008274L SC_BNR_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_bin_ratio_div                  :8 ;	//7:0
	UINT32 reg_bin_ratio_mul                  :8 ;	//15:8
	UINT32 reg_min_bin_th                     :8 ;	//23:16
	UINT32 reg_detector_iir_gain              :8 ;	//31:24
}PE_M17_SC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008278L SC_BNR_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_grid_th1                       :8 ;	//7:0
	UINT32 reg_grid_th2                       :8 ;	//15:8
	UINT32 reg_grid_th3                       :8 ;	//23:16
}PE_M17_SC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900827cL SC_BNR_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pos_gain_th                    :8 ;	//7:0
	UINT32 reserved01                         :11;	//reserved
	UINT32 reg_scale_div_v                    :4 ;	//22:19
	UINT32 reg_scale_mul_v                    :9 ;	//31:23
}PE_M17_SC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9008280L SC_BNR_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_pos_gain_3                     :8 ;	//7:0
	UINT32 reg_pos_gain_2                     :8 ;	//15:8
	UINT32 reg_pos_gain_1                     :8 ;	//23:16
	UINT32 reg_pos_gain_0                     :8 ;	//31:24
}PE_M17_SC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc9008284L SC_BNR_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sc_bnr_debug_en                :1 ;	//0 
	UINT32 reg_sc_bnr_debug_mode              :3 ;	//3:1
	UINT32 reg_avg_scale_div_v                :3 ;	//6:4
	UINT32 reg_avg_scale_mul_v                :4 ;	//10:7
	UINT32 reserved01                         :13;	//reserved
	UINT32 reg_acness_th                      :8 ;	//31:24
}PE_M17_SC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9008288L C_PRE_BLUR_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 pre_121_blur_en                    :1 ;	//0 
	UINT32 pre_median_en                      :1 ;	//1 
}PE_M17_C_PRE_BLUR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900828cL TEXTURE_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_texture_cnt_div                :3 ;	//2:0
	UINT32 reserved01                         :5 ;	//reserved
	UINT32 reg_texture_cnt_mul                :8 ;	//15:8
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 reg_cross_th                       :8 ;	//31:24
}PE_M17_TEXTURE_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008290L TEXTURE_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_TEXTURE_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9008294L TEXTURE_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_TEXTURE_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008298L TEXTURE_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_TEXTURE_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900829cL AC_BNR_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_acness_gain_h_l                :8 ;	//15:8
	UINT32 reg_acness_gain_h_g                :8 ;	//23:16
	UINT32 reg_acness_gain_h                  :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90082a0L AC_BNR_CTRL_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved01                         :8 ;	//reserved
	UINT32 reg_acness_gain_v_l                :8 ;	//15:8
	UINT32 reg_acness_gain_v_g                :8 ;	//23:16
	UINT32 reg_acness_gain_v                  :8 ;	//31:24
}PE_M17_AC_BNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90082a4L DC_BNR_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_fil_motion_x_th0               :8 ;	//7:0
	UINT32 reg_fil_motion_x_th1               :8 ;	//15:8
	UINT32 reg_fil_motion_x_th2               :8 ;	//23:16
	UINT32 reg_fil_motion_x_th3               :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90082a8L DC_BNR_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_fil_motion_y_th0               :8 ;	//7:0
	UINT32 reg_fil_motion_y_th1               :8 ;	//15:8
	UINT32 reg_fil_motion_y_th2               :8 ;	//23:16
	UINT32 reg_fil_motion_y_th3               :8 ;	//31:24
}PE_M17_DC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90082acL SQM_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_mmd_sel                        :2 ;	//1:0
	UINT32 reserved01                         :6 ;	//reserved
	UINT32 reg_hist_bin_th0                   :8 ;	//15:8
	UINT32 reg_hist_bin_th1                   :8 ;	//23:16
	UINT32 reg_hist_bin_th2                   :8 ;	//31:24
}PE_M17_SQM_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90082b0L SQM_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_hist_bin_th3                   :8 ;	//7:0
	UINT32 reg_hist_bin_th4                   :8 ;	//15:8
	UINT32 reg_hist_bin_th5                   :8 ;	//23:16
	UINT32 reg_hist_bin_th6                   :8 ;	//31:24
}PE_M17_SQM_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90082b4L SQM_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_trans_mmd_th                   :8 ;	//7:0
	UINT32 reserved01                         :2 ;	//reserved
	UINT32 reg_edge_a_th                      :10;	//19:10
	UINT32 reg_edf_mmd_th                     :8 ;	//27:20
}PE_M17_SQM_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90082b8L SQM_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sqm_win_mode_x1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_sqm_win_mode_x0                :13;	//28:16
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_sqm_win_mode_mode              :1 ;	//30
	UINT32 reg_sqm_win_mode_en                :1 ;	//31
}PE_M17_SQM_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90082bcL SQM_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_sqm_win_mode_y1                :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_sqm_win_mode_y0                :13;	//28:16
}PE_M17_SQM_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90082c0L TPD_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_tp_binary_th                   :8 ;	//7:0
}PE_M17_TPD_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90082c4L WINDOW_MODE_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_win_mode_x1                    :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_win_mode_x0                    :13;	//28:16
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 reg_win_mode_mode                  :1 ;	//30
	UINT32 reg_win_mode_en                    :1 ;	//31
}PE_M17_WINDOW_MODE_0_T;
/*-----------------------------------------------------------------------------
                             0xc90082c8L WINDOW_MODE_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_win_mode_y1                    :13;	//12:0
	UINT32 reserved01                         :3 ;	//reserved
	UINT32 reg_win_mode_y0                    :13;	//28:16
}PE_M17_WINDOW_MODE_1_T;
/*-----------------------------------------------------------------------------
                             0xc90082d0L DNR_STAT_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 acness_v_g                         :8 ;	//7:0
	UINT32 acness_h_g                         :8 ;	//15:8
	UINT32 acness_v                           :8 ;	//23:16
	UINT32 acness_h                           :8 ;	//31:24
}PE_M17_DNR_STAT_3_T;
/*-----------------------------------------------------------------------------
                             0xc90082d4L DNR_STAT_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bad_up_cnt                         :12;	//11:0
	UINT32 reserved01                         :4 ;	//reserved
	UINT32 acness_v_l                         :8 ;	//23:16
	UINT32 acness_h_l                         :8 ;	//31:24
}PE_M17_DNR_STAT_4_T;
/*-----------------------------------------------------------------------------
                             0xc90082d8L DNR_STAT_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved                           :8 ;	//7:0
	UINT32 acness_gain_v_l                    :8 ;	//15:8
	UINT32 acness_gain_h_l                    :8 ;	//23:16
	UINT32 acness_gain_v_g                    :8 ;	//31:24
}PE_M17_DNR_STAT_5_T;
/*-----------------------------------------------------------------------------
                             0xc90082dcL DNR_STAT_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_DNR_STAT_6_T;
/*-----------------------------------------------------------------------------
                             0xc90082e0L DNR_STAT_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 acness_gain_v                      :8 ;	//7:0
	UINT32 acness_gain_h                      :8 ;	//15:8
	UINT32 acness_v_iir                       :8 ;	//23:16
	UINT32 acness_h_iir                       :8 ;	//31:24
}PE_M17_DNR_STAT_7_T;
/*-----------------------------------------------------------------------------
                             0xc90082e4L DNR_STAT_8_SC_BNR0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 bin_ratio_iir_h                    :8 ;	//7:0
	UINT32 bin_ratio_v                        :8 ;	//15:8
	UINT32 bin_ratio_h                        :8 ;	//23:16
	UINT32 hys_cnt_v                          :3 ;	//26:24
	UINT32 hys_cnt_h                          :3 ;	//29:27
	UINT32 sc_bnr_flag_v                      :1 ;	//30
	UINT32 sc_bnr_flag_h                      :1 ;	//31
}PE_M17_DNR_STAT_8_SC_BNR0_T;
/*-----------------------------------------------------------------------------
                             0xc90082e8L DNR_STAT_9_SC_BNR1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 max_index_iir_h                    :7 ;	//6:0
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 max_index_v                        :7 ;	//14:8
	UINT32 reserved02                         :1 ;	//reserved
	UINT32 max_index_h                        :7 ;	//22:16
	UINT32 reserved03                         :1 ;	//reserved
	UINT32 bin_ratio_iir_v                    :8 ;	//31:24
}PE_M17_DNR_STAT_9_SC_BNR1_T;
/*-----------------------------------------------------------------------------
                             0xc90082ecL DNR_STAT_10_SC_BNR2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 w_max_index_iir_v                  :7 ;	//6:0
}PE_M17_DNR_STAT_10_SC_BNR2_T;
/*-----------------------------------------------------------------------------
                             0xc90082f0L DNR_STAT_11_SQM_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 e_hist_1                           :16;	//15:0
	UINT32 e_hist_0                           :16;	//31:16
}PE_M17_DNR_STAT_11_SQM_00_T;
/*-----------------------------------------------------------------------------
                             0xc90082f4L DNR_STAT_12_SQM_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 e_hist_3                           :16;	//15:0
	UINT32 e_hist_2                           :16;	//31:16
}PE_M17_DNR_STAT_12_SQM_01_T;
/*-----------------------------------------------------------------------------
                             0xc90082f8L DNR_STAT_13_SQM_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 e_hist_5                           :16;	//15:0
	UINT32 e_hist_4                           :16;	//31:16
}PE_M17_DNR_STAT_13_SQM_02_T;
/*-----------------------------------------------------------------------------
                             0xc90082fcL DNR_STAT_14_SQM_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 e_hist_7                           :16;	//15:0
	UINT32 e_hist_6                           :16;	//31:16
}PE_M17_DNR_STAT_14_SQM_03_T;
/*-----------------------------------------------------------------------------
                             0xc9008300L DNR_STAT_15_SQM_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 f_hist_1                           :16;	//15:0
	UINT32 f_hist_0                           :16;	//31:16
}PE_M17_DNR_STAT_15_SQM_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008304L DNR_STAT_16_SQM_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 f_hist_3                           :16;	//15:0
	UINT32 f_hist_2                           :16;	//31:16
}PE_M17_DNR_STAT_16_SQM_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008308L DNR_STAT_17_SQM_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 f_hist_5                           :16;	//15:0
	UINT32 f_hist_4                           :16;	//31:16
}PE_M17_DNR_STAT_17_SQM_06_T;
/*-----------------------------------------------------------------------------
                             0xc900830cL DNR_STAT_18_SQM_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 f_hist_7                           :16;	//15:0
	UINT32 f_hist_6                           :16;	//31:16
}PE_M17_DNR_STAT_18_SQM_07_T;
/*-----------------------------------------------------------------------------
                             0xc9008310L DNR_STAT_19_SQM_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 t_hist_1                           :16;	//15:0
	UINT32 t_hist_0                           :16;	//31:16
}PE_M17_DNR_STAT_19_SQM_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008314L DNR_STAT_20_SQM_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 t_hist_3                           :16;	//15:0
	UINT32 t_hist_2                           :16;	//31:16
}PE_M17_DNR_STAT_20_SQM_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008318L DNR_STAT_21_SQM_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 t_hist_5                           :16;	//15:0
	UINT32 t_hist_4                           :16;	//31:16
}PE_M17_DNR_STAT_21_SQM_10_T;
/*-----------------------------------------------------------------------------
                             0xc900831cL DNR_STAT_22_SQM_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 t_hist_7                           :16;	//15:0
	UINT32 t_hist_6                           :16;	//31:16
}PE_M17_DNR_STAT_22_SQM_11_T;
/*-----------------------------------------------------------------------------
                             0xc9008320L DNR_STAT_23_TPD_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 res_h_cnt_2                        :16;	//15:0
	UINT32 res_h_cnt_1                        :16;	//31:16
}PE_M17_DNR_STAT_23_TPD_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008324L DNR_STAT_24_TPD_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 res_v_cnt_2                        :16;	//15:0
	UINT32 res_v_cnt_1                        :16;	//31:16
}PE_M17_DNR_STAT_24_TPD_1_T;
/*-----------------------------------------------------------------------------
                             0xc9008328L DNR_STAT_25_TPD_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 res_v_cnt_3                        :16;	//15:0
	UINT32 res_h_cnt_3                        :16;	//31:16
}PE_M17_DNR_STAT_25_TPD_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008330L AC_BNR_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_fil_motion_x_th3               :8 ;	//7:0
	UINT32 reg_fil_motion_x_th2               :8 ;	//15:8
	UINT32 reg_fil_motion_x_th1               :8 ;	//23:16
	UINT32 reg_fil_motion_x_th0               :8 ;	//31:24
}PE_M17_AC_BNR_15_T;
/*-----------------------------------------------------------------------------
                             0xc9008334L AC_BNR_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_tearing                  :8 ;	//7:0
	UINT32 reg_fil_motion_y_th3               :8 ;	//15:8
	UINT32 reg_fil_motion_y_th2               :8 ;	//23:16
	UINT32 reg_fil_motion_y_th1               :8 ;	//31:24
}PE_M17_AC_BNR_16_T;
/*-----------------------------------------------------------------------------
                             0xc9008338L VFILTER_CTRL_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_tearing;
}PE_M17_VFILTER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900833cL VFILTER_CTRL_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_motion_1;
}PE_M17_VFILTER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9008340L VFILTER_CTRL_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_motion_2;
}PE_M17_VFILTER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9008344L VFILTER_CTRL_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_global_1;
}PE_M17_VFILTER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9008348L VFILTER_CTRL_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_global_2;
}PE_M17_VFILTER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900834cL VFILTER_CTRL_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_fmd_1;
}PE_M17_VFILTER_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9008350L VFILTER_CTRL_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_fmd_2;
}PE_M17_VFILTER_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9008354L VFILTER_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_hmc_1;
}PE_M17_VFILTER_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008358L VFILTER_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_hmc_2;
}PE_M17_VFILTER_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900835cL VFILTER_CTRL_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_local_1;
}PE_M17_VFILTER_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9008360L VFILTER_CTRL_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_blend_local_2;
}PE_M17_VFILTER_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9008364L REG_DECON_CTRL_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_diff_mul                       :8 ;	//7:0
	UINT32 reg_force_block_no_v               :6 ;	//13:8
	UINT32 reg_debug_en                       :1 ;	//14
	UINT32 reserved01                         :1 ;	//reserved
	UINT32 reg_force_block_no_h               :6 ;	//21:16
	UINT32 reserved02                         :8 ;	//reserved
	UINT32 reg_force_block_no_en              :1 ;	//30
	UINT32 reg_decon_en                       :1 ;	//31
}PE_M17_REG_DECON_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9008368L REG_DECON_CTRL_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_var_chroma_en                  :1 ;	//0 
	UINT32 reserved01                         :19;	//reserved
	UINT32 reg_var_v_gain                     :4 ;	//23:20
	UINT32 reg_var_h_gain                     :4 ;	//27:24
	UINT32 reg_var_cut_resolution             :4 ;	//31:28
}PE_M17_REG_DECON_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900836cL REG_DECON_CTRL_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_diff_x_th0               :8 ;	//7:0
	UINT32 reg_decon_diff_x_th1               :8 ;	//15:8
	UINT32 reg_decon_diff_x_th2               :8 ;	//23:16
	UINT32 reg_decon_diff_x_th3               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9008370L REG_DECON_CTRL_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_diff_y_th0               :8 ;	//7:0
	UINT32 reg_decon_diff_y_th1               :8 ;	//15:8
	UINT32 reg_decon_diff_y_th2               :8 ;	//23:16
	UINT32 reg_decon_diff_y_th3               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9008374L REG_DECON_CTRL_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_var_x_th0                :8 ;	//7:0
	UINT32 reg_decon_var_x_th1                :8 ;	//15:8
	UINT32 reg_decon_var_x_th2                :8 ;	//23:16
	UINT32 reg_decon_var_x_th3                :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9008378L REG_DECON_CTRL_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_var_y_th0                :8 ;	//7:0
	UINT32 reg_decon_var_y_th1                :8 ;	//15:8
	UINT32 reg_decon_var_y_th2                :8 ;	//23:16
	UINT32 reg_decon_var_y_th3                :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900837cL REG_DECON_CTRL_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_luma_x_th0               :8 ;	//7:0
	UINT32 reg_decon_luma_x_th1               :8 ;	//15:8
	UINT32 reg_decon_luma_x_th2               :8 ;	//23:16
	UINT32 reg_decon_luma_x_th3               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9008380L REG_DECON_CTRL_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_luma_x_th4               :8 ;	//7:0
	UINT32 reg_decon_luma_x_th5               :8 ;	//15:8
	UINT32 reg_decon_luma_x_th6               :8 ;	//23:16
	UINT32 reg_decon_luma_x_th7               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9008384L REG_DECON_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_luma_y_th0               :8 ;	//7:0
	UINT32 reg_decon_luma_y_th1               :8 ;	//15:8
	UINT32 reg_decon_luma_y_th2               :8 ;	//23:16
	UINT32 reg_decon_luma_y_th3               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9008388L REG_DECON_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_decon_luma_y_th4               :8 ;	//7:0
	UINT32 reg_decon_luma_y_th5               :8 ;	//15:8
	UINT32 reg_decon_luma_y_th6               :8 ;	//23:16
	UINT32 reg_decon_luma_y_th7               :8 ;	//31:24
}PE_M17_REG_DECON_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900838cL REG_DECON_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reserved;
}PE_M17_REG_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9008390L REG_DC_BNR_CTRL_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_gain_x3                        :8 ;	//7:0
	UINT32 reg_gain_x2                        :8 ;	//15:8
	UINT32 reg_gain_x1                        :8 ;	//23:16
	UINT32 reg_gain_x0                        :8 ;	//31:24
}PE_M17_REG_DC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9008394L REG_DC_BNR_CTRL_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_gain_x7                        :8 ;	//7:0
	UINT32 reg_gain_x6                        :8 ;	//15:8
	UINT32 reg_gain_x5                        :8 ;	//23:16
	UINT32 reg_gain_x4                        :8 ;	//31:24
}PE_M17_REG_DC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9008398L REG_DC_BNR_CTRL_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_gain_y3                        :8 ;	//7:0
	UINT32 reg_gain_y2                        :8 ;	//15:8
	UINT32 reg_gain_y1                        :8 ;	//23:16
	UINT32 reg_gain_y0                        :8 ;	//31:24
}PE_M17_REG_DC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900839cL REG_DC_BNR_CTRL_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 reg_gain_y7                        :8 ;	//7:0
	UINT32 reg_gain_y6                        :8 ;	//15:8
	UINT32 reg_gain_y5                        :8 ;	//23:16
	UINT32 reg_gain_y4                        :8 ;	//31:24
}PE_M17_REG_DC_BNR_CTRL_11_T;


/*-----------------------------------------------------------------------------
		0xc90010B8L ctrl_m0_y_level_ctrl ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 reg_lvctrl_en                       :  1; //     0     
	UINT32 reg_lvctrl_detour                   :  1; //     1     
	UINT32                                     :  2; //  3:2     reserved   
	UINT32 level_offset                        : 10; //13: 4     
	UINT32                                     :  2; // 15:14     reserved 
	UINT32 level_center                        :  8; // 23:16     
	UINT32 level_gain                          :  8; // 31:24     
}PE_M17_CTRL_M0_Y_LEVEL_CTRL_T;

/*-----------------------------------------------------------------------------
		0xc9001400L ipp_ctrl0 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 o_c_fmt                            : 3 ;  //  2: 0     
	UINT32 prew_rd_422                        : 1 ;  //     3     
	UINT32 i_c_fmt                            : 3 ;  //  6: 4     
	UINT32                                    : 1 ;  //     7     reserved
	UINT32 hdmi420_on                         : 1 ;  //     8     
	UINT32 c_vsample_en                       : 1 ;  //     9     
	UINT32 c_hsample_en                       : 1 ;  //    10     
	UINT32 hsc_sw_en                          : 1 ;  //    11     
	UINT32 prew_mux_sel                       : 1 ;  //    12     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 cvi_mux_sel                        : 3 ;  // 18:16     
	UINT32                                    : 5 ;  // 23:19     reserved
	UINT32 wr_disalbe                         : 1 ;  //    24     
	UINT32                                    : 4 ;  // 28:25     reserved
	UINT32 set_mvi_val                        : 1 ;  //    29     
	UINT32                                    : 1 ;  //    30     reserved
	UINT32 pr_sq                              : 1 ;  //    31     
} PE_M17_IPP_CTRL0_T;

/*-----------------------------------------------------------------------------
		0xc9001434L ipp_size_i ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 hsize_i                            : 13;  // 12: 0     
	UINT32                                    : 3 ;  // 15:13     reserved
	UINT32 vsize_i                            : 12;  // 27:16     
} PE_M17_IPP_SIZE_I_T;

typedef struct
{ 
	PE_M17_PE0_TNR_LOAD_T                            pe0_tnr_load;	//0x0000
	PE_M17_PE0_TNR_INTR_T                            pe0_tnr_intr;	//0x0004
	PE_M17_PE0_TNR_STATUS0_T                         pe0_tnr_status0;	//0x0008
	PE_M17_PE0_TNR_STATUS1_T                         pe0_tnr_status1;	//0x000C
	PE_M17_PE0_TNR_OPMODE_T                          pe0_tnr_opmode;	//0x0010
	PE_M17_PE0_TNR_SRC_SIZE_T                        pe0_tnr_src_size;	//0x0014
	PE_M17_PE0_TNR_FIELD_T                           pe0_tnr_field;	//0x0018
	PE_M17_PE0_TNR_DEBUG_LEND_CTRL_T                 pe0_tnr_debug_lend_ctrl;	//0x001C
	PE_M17_PE0_TNR_IN_OFFSET_T                       pe0_tnr_in_offset;	//0x0020
	PE_M17_PE0_TNR_IN_SIZE_T                         pe0_tnr_in_size;	//0x0024
	PE_M17_FBC_CTRL0_T                               fbc_ctrl0;	//0x0028
	PE_M17_FBC_CTRL1_T                               fbc_ctrl1;	//0x002C
	PE_M17_PE0_DEBUG_MEM_REQ_T                       pe0_debug_mem_req;	//0x0030
	PE_M17_PE0_DEBUG_LREQ_DLY_T                      pe0_debug_lreq_dly;	//0x0034
	PE_M17_TNRW_IN_OFFSET_T                          tnrw_in_offset;	//0x0038
	PE_M17_TNRW_OUT_SIZE_T                           tnrw_out_size;	//0x003C
	PE_M17_TNR_CTRL_00_T                             tnr_ctrl_00;	//0x0040
	PE_M17_TNR_CTRL_01_T                             tnr_ctrl_01;	//0x0044
	PE_M17_TNR_CTRL_02_T                             tnr_ctrl_02;	//0x0048
	PE_M17_TNR_CTRL_03_T                             tnr_ctrl_03;	//0x004C
	PE_M17_TNR_CTRL_04_T                             tnr_ctrl_04;	//0x0050
	PE_M17_TNR_CTRL_05_T                             tnr_ctrl_05;	//0x0054
	PE_M17_TNR_CTRL_06_T                             tnr_ctrl_06;	//0x0058
	PE_M17_TNR_CTRL_07_T                             tnr_ctrl_07;	//0x005C
	PE_M17_TNR_CTRL_08_T                             tnr_ctrl_08;	//0x0060
	PE_M17_TNR_CTRL_09_T                             tnr_ctrl_09;	//0x0064
	PE_M17_TNR_CTRL_10_T                             tnr_ctrl_10;	//0x0068
	PE_M17_TNR_CTRL_11_T                             tnr_ctrl_11;	//0x006C
	PE_M17_TNR_CTRL_12_T                             tnr_ctrl_12;	//0x0070
	PE_M17_TNR_CTRL_13_T                             tnr_ctrl_13;	//0x0074
	PE_M17_TNR_CTRL_14_T                             tnr_ctrl_14;	//0x0078
	PE_M17_TNR_CTRL_15_T                             tnr_ctrl_15;	//0x007C
	PE_M17_TNR_CTRL_16_T                             tnr_ctrl_16;	//0x0080
	PE_M17_TNR_CTRL_17_T                             tnr_ctrl_17;	//0x0084
	PE_M17_TNR_CTRL_18_T                             tnr_ctrl_18;	//0x0088
	PE_M17_TNR_CTRL_19_T                             tnr_ctrl_19;	//0x008C
	PE_M17_TNR_CTRL_20_T                             tnr_ctrl_20;	//0x0090
	PE_M17_TNR_CTRL_21_T                             tnr_ctrl_21;	//0x0094
	PE_M17_TNR_CTRL_22_T                             tnr_ctrl_22;	//0x0098
	PE_M17_TNR_CTRL_23_T                             tnr_ctrl_23;	//0x009C
	PE_M17_TNR_CTRL_24_T                             tnr_ctrl_24;	//0x00A0
	PE_M17_TNR_CTRL_25_T                             tnr_ctrl_25;	//0x00A4
	PE_M17_TNR_CTRL_26_T                             tnr_ctrl_26;	//0x00A8
	PE_M17_TNR_CTRL_27_T                             tnr_ctrl_27;	//0x00AC
	PE_M17_TNR_CTRL_28_T                             tnr_ctrl_28;	//0x00B0
	PE_M17_TNR_CTRL_29_T                             tnr_ctrl_29;	//0x00B4
	PE_M17_TNR_CTRL_30_T                             tnr_ctrl_30;	//0x00B8
	PE_M17_TNR_CTRL_31_T                             tnr_ctrl_31;	//0x00BC
	PE_M17_TNR_STATUS_00_T                           tnr_status_00;	//0x00C0
	PE_M17_TNR_STATUS_01_T                           tnr_status_01;	//0x00C4
	PE_M17_TNR_STATUS_02_T                           tnr_status_02;	//0x00C8
	PE_M17_TNR_STATUS_03_T                           tnr_status_03;	//0x00CC
	PE_M17_TNR_MAIN_LUT_00_T                         tnr_main_lut_00;	//0x00D0
	PE_M17_TNR_MAIN_LUT_01_T                         tnr_main_lut_01;	//0x00D4
	UINT32                                            reserved00;	//0x00D8-0x00D8
	PE_M17_TNR_STATUS_04_T                           tnr_status_04;	//0x00DC
	PE_M17_TNR_CTRL_32_T                             tnr_ctrl_32;	//0x00E0
	PE_M17_TNR_CTRL_33_T                             tnr_ctrl_33;	//0x00E4
	PE_M17_TNR_CTRL_34_T                             tnr_ctrl_34;	//0x00E8
	PE_M17_TNR_CTRL_35_T                             tnr_ctrl_35;	//0x00EC
	PE_M17_TNR_CTRL_36_T                             tnr_ctrl_36;	//0x00F0
	PE_M17_TNR_CTRL_37_T                             tnr_ctrl_37;	//0x00F4
	PE_M17_TNR_CTRL_38_T                             tnr_ctrl_38;	//0x00F8
	PE_M17_TNR_CTRL_39_T                             tnr_ctrl_39;	//0x00FC
	PE_M17_IPC_CTRL_00_T                             ipc_ctrl_00;	//0x0100
	PE_M17_IPC_CTRL_01_T                             ipc_ctrl_01;	//0x0104
	PE_M17_IPC_CTRL_02_T                             ipc_ctrl_02;	//0x0108
	PE_M17_IPC_CTRL_03_T                             ipc_ctrl_03;	//0x010C
	PE_M17_IPC_CTRL_04_T                             ipc_ctrl_04;	//0x0110
	PE_M17_IPC_CTRL_05_T                             ipc_ctrl_05;	//0x0114
	PE_M17_IPC_CTRL_06_T                             ipc_ctrl_06;	//0x0118
	PE_M17_IPC_CTRL_07_T                             ipc_ctrl_07;	//0x011C
	PE_M17_IPC_CTRL_08_T                             ipc_ctrl_08;	//0x0120
	PE_M17_IPC_CTRL_09_T                             ipc_ctrl_09;	//0x0124
	PE_M17_IPC_CTRL_10_T                             ipc_ctrl_10;	//0x0128
	PE_M17_IPC_CTRL_11_T                             ipc_ctrl_11;	//0x012C
	PE_M17_IPC_CTRL_12_T                             ipc_ctrl_12;	//0x0130
	PE_M17_IPC_CTRL_13_T                             ipc_ctrl_13;	//0x0134
	PE_M17_IPC_CTRL_14_T                             ipc_ctrl_14;	//0x0138
	PE_M17_IPC_CTRL_15_T                             ipc_ctrl_15;	//0x013C
	PE_M17_IPC_CTRL_16_T                             ipc_ctrl_16;	//0x0140
	PE_M17_IPC_CTRL_17_T                             ipc_ctrl_17;	//0x0144
	PE_M17_IPC_CTRL_18_T                             ipc_ctrl_18;	//0x0148
	PE_M17_IPC_CTRL_19_T                             ipc_ctrl_19;	//0x014C
	PE_M17_IPC_STATUS_00_T                           ipc_status_00;	//0x0150
	PE_M17_IPC_STATUS_01_T                           ipc_status_01;	//0x0154
	PE_M17_IPC_STATUS_02_T                           ipc_status_02;	//0x0158
	PE_M17_IPC_STATUS_03_T                           ipc_status_03;	//0x015C
	PE_M17_CLC_CTRL_00_T                             clc_ctrl_00;	//0x0160
	PE_M17_CLC_CTRL_01_T                             clc_ctrl_01;	//0x0164
	PE_M17_CLC_CTRL_02_T                             clc_ctrl_02;	//0x0168
	PE_M17_CLC_CTRL_03_T                             clc_ctrl_03;	//0x016C
	PE_M17_CLC_CTRL_04_T                             clc_ctrl_04;	//0x0170
	PE_M17_CLC_CTRL_05_T                             clc_ctrl_05;	//0x0174
	PE_M17_CLC_CTRL_06_T                             clc_ctrl_06;	//0x0178
	PE_M17_CLC_STAT_00_T                             clc_stat_00;	//0x017C
	PE_M17_IPC_CTRL_34_T                             ipc_ctrl_34;	//0x0180
	PE_M17_IPC_CTRL_35_T                             ipc_ctrl_35;	//0x0184
	PE_M17_IPC_CTRL_36_T                             ipc_ctrl_36;	//0x0188
	PE_M17_IPC_CTRL_37_T                             ipc_ctrl_37;	//0x018C
	PE_M17_IPC_CTRL_38_T                             ipc_ctrl_38;	//0x0190
	PE_M17_IPC_CTRL_39_T                             ipc_ctrl_39;	//0x0194
	PE_M17_IPC_CTRL_40_T                             ipc_ctrl_40;	//0x0198
	PE_M17_IPC_CTRL_41_T                             ipc_ctrl_41;	//0x019C
	PE_M17_IPC_CTRL_42_T                             ipc_ctrl_42;	//0x01A0
	PE_M17_IPC_CTRL_43_T                             ipc_ctrl_43;	//0x01A4
	PE_M17_IPC_CTRL_44_T                             ipc_ctrl_44;	//0x01A8
	PE_M17_IPC_CTRL_45_T                             ipc_ctrl_45;	//0x01AC
	PE_M17_IPC_CTRL_46_T                             ipc_ctrl_46;	//0x01B0
	PE_M17_IPC_CTRL_47_T                             ipc_ctrl_47;	//0x01B4
	PE_M17_IPC_CTRL_48_T                             ipc_ctrl_48;	//0x01B8
	PE_M17_IPC_CTRL_49_T                             ipc_ctrl_49;	//0x01BC
	PE_M17_IPC_CTRL_50_T                             ipc_ctrl_50;	//0x01C0
	PE_M17_IPC_CTRL_51_T                             ipc_ctrl_51;	//0x01C4
	PE_M17_IPC_CTRL_52_T                             ipc_ctrl_52;	//0x01C8
	UINT32                                            reserved01[5];	//0x01CC-0x01DC
	PE_M17_MMD_CTRL_T                                mmd_ctrl;	//0x01E0
	UINT32                                            reserved02[3];	//0x01E4-0x01EC
	PE_M17_IPC_CTRL_20_T                             ipc_ctrl_20;	//0x01F0
	PE_M17_IPC_CTRL_21_T                             ipc_ctrl_21;	//0x01F4
	PE_M17_IPC_CTRL_22_T                             ipc_ctrl_22;	//0x01F8
	PE_M17_IPC_CTRL_23_T                             ipc_ctrl_23;	//0x01FC
	PE_M17_IPC_CTRL_24_T                             ipc_ctrl_24;	//0x0200
	PE_M17_IPC_CTRL_25_T                             ipc_ctrl_25;	//0x0204
	PE_M17_IPC_CTRL_26_T                             ipc_ctrl_26;	//0x0208
	PE_M17_IPC_CTRL_27_T                             ipc_ctrl_27;	//0x020C
	PE_M17_IPC_CTRL_28_T                             ipc_ctrl_28;	//0x0210
	PE_M17_IPC_CTRL_29_T                             ipc_ctrl_29;	//0x0214
	PE_M17_IPC_CTRL_30_T                             ipc_ctrl_30;	//0x0218
	PE_M17_IPC_CTRL_31_T                             ipc_ctrl_31;	//0x021C
	PE_M17_IPC_CTRL_32_T                             ipc_ctrl_32;	//0x0220
	PE_M17_IPC_CTRL_33_T                             ipc_ctrl_33;	//0x0224
	PE_M17_IPC_STATUS_04_T                           ipc_status_04;	//0x0228
	PE_M17_IPC_STATUS_05_T                           ipc_status_05;	//0x022C
	PE_M17_IPC_STATUS_06_T                           ipc_status_06;	//0x0230
	PE_M17_IPC_STATUS_07_T                           ipc_status_07;	//0x0234
	PE_M17_IPC_STATUS_08_T                           ipc_status_08;	//0x0238
	PE_M17_IPC_STATUS_09_T                           ipc_status_09;	//0x023C
	PE_M17_TPD_CTRL_00_T                             tpd_ctrl_00;	//0x0240
	PE_M17_TPD_CTRL_01_T                             tpd_ctrl_01;	//0x0244
	PE_M17_TPD_CTRL_02_T                             tpd_ctrl_02;	//0x0248
	PE_M17_TPD_CTRL_03_T                             tpd_ctrl_03;	//0x024C
	PE_M17_TPD_CTRL_04_T                             tpd_ctrl_04;	//0x0250
	PE_M17_TPD_CTRL_05_T                             tpd_ctrl_05;	//0x0254
	PE_M17_TPD_CTRL_06_T                             tpd_ctrl_06;	//0x0258
	PE_M17_TPD_CTRL_07_T                             tpd_ctrl_07;	//0x025C
	PE_M17_TPD_CTRL_08_T                             tpd_ctrl_08;	//0x0260
	PE_M17_TPD_CTRL_09_T                             tpd_ctrl_09;	//0x0264
	PE_M17_TPD_STAT_00_T                             tpd_stat_00;	//0x0268
	PE_M17_CLC_CTRL_07_T                             clc_ctrl_07;	//0x026C
	PE_M17_BBD_CTRL_00_T                             bbd_ctrl_00;	//0x0270
	PE_M17_BBD_CTRL_01_T                             bbd_ctrl_01;	//0x0274
	PE_M17_BBD_CTRL_02_T                             bbd_ctrl_02;	//0x0278
	PE_M17_BBD_STAT_00_T                             bbd_stat_00;	//0x027C
	PE_M17_BBD_STAT_01_T                             bbd_stat_01;	//0x0280
	PE_M17_APL_STAT_00_T                             apl_stat_00;	//0x0284
	PE_M17_PE1_FSW_CTRL_00_T                         pe1_fsw_ctrl_00;
	PE_M17_PE1_FSW_CTRL_01_T                         pe1_fsw_ctrl_01;
	PE_M17_TPD_HIST_AI_CTRL_T                        tpd_hist_ai_ctrl;	//0x0290
	PE_M17_TPD_HIST_AI_DATA_T                        tpd_hist_ai_data;	//0x0294
	PE_M17_LVCRTL_CTRL_00_T                          lvcrtl_ctrl_00;	//0x0298
	UINT32                                            reserved04;	//0x029C-0x029C
	PE_M17_TNR_STATUS_05_T                           tnr_status_05;	//0x02A0
	PE_M17_TNR_STATUS_06_T                           tnr_status_06;	//0x02A4
	PE_M17_TNR_STATUS_07_T                           tnr_status_07;	//0x02A8
	PE_M17_TNR_STATUS_08_T                           tnr_status_08;	//0x02AC
	UINT32                                            reserved05[4];	//0x02B0-0x02BC
	PE_M17_TNR_RESET_T                               tnr_reset;	//0x02C0
	UINT32                                            reserved06[3];	//0x02C4-0x02CC
	PE_M17_TNR_CTRL_40_T                             tnr_ctrl_40;	//0x02D0
	PE_M17_TNR_CTRL_41_T                             tnr_ctrl_41;	//0x02D4
	PE_M17_TNR_CTRL_42_T                             tnr_ctrl_42;	//0x02D8
	PE_M17_TNR_CTRL_43_T                             tnr_ctrl_43;	//0x02DC
	PE_M17_TNR_CTRL_44_T                             tnr_ctrl_44;	//0x02E0
	PE_M17_TNR_CTRL_45_T                             tnr_ctrl_45;	//0x02E4
	PE_M17_TNR_CTRL_46_T                             tnr_ctrl_46;	//0x02E8
	PE_M17_TNR_CTRL_47_T                             tnr_ctrl_47;	//0x02EC
	PE_M17_TNR_CTRL_48_T                             tnr_ctrl_48;	//0x02F0
	UINT32                                            reserved07[3];	//0x02F4-0x02FC
	PE_M17_TNR_NE_STAT_00_T                          tnr_ne_stat_00;	//0x0300
	PE_M17_TNR_NE_STAT_01_T                          tnr_ne_stat_01;	//0x0304
	PE_M17_TNR_NE_STAT_02_T                          tnr_ne_stat_02;	//0x0308
	PE_M17_TNR_NE_STAT_03_T                          tnr_ne_stat_03;	//0x030C
	PE_M17_TNR_NE_STAT_04_T                          tnr_ne_stat_04;	//0x0310
	PE_M17_TNR_NE_STAT_05_T                          tnr_ne_stat_05;	//0x0314
	PE_M17_TNR_NE_STAT_06_T                          tnr_ne_stat_06;	//0x0318
	PE_M17_TNR_NE_STAT_07_T                          tnr_ne_stat_07;	//0x031C
	PE_M17_TNR_NE_STAT_08_T                          tnr_ne_stat_08;	//0x0320
	UINT32                                            reserved08[4];	//0x0324-0x0330
	UINT32                                            reserved205[19];	//0x334-0x37c
	PE_M17_ND_FSW_CTRL_00_T                          nd_fsw_ctrl_00;	//0x0380
	PE_M17_ND_FSW_CTRL_01_T                          nd_fsw_ctrl_01;	//0x0384
	PE_M17_ND_FSW_CTRL_02_T                          nd_fsw_ctrl_02;	//0x0388
	PE_M17_ND_FSW_CTRL_03_T                          nd_fsw_ctrl_03;	//0x038C
	PE_M17_TNR_ETC_CTRL_00_T                         tnr_etc_ctrl_00;	//0x0390
	PE_M17_TNR_ETC_CTRL_01_T                         tnr_etc_ctrl_01;	//0x0394
	PE_M17_TNR_ETC_CTRL_02_T                         tnr_etc_ctrl_02;	//0x0398
	PE_M17_TNR_ETC_CTRL_03_T                         tnr_etc_ctrl_03;	//0x039C
	PE_M17_TNR_CTRL_56_T                             tnr_ctrl_56;	//0x03A0
	PE_M17_TNR_CTRL_57_T                             tnr_ctrl_57;	//0x03A4
	PE_M17_TNR_CTRL_58_T                             tnr_ctrl_58;	//0x03A8
	PE_M17_TNR_CTRL_59_T                             tnr_ctrl_59;	//0x03AC
	PE_M17_TNR_CTRL_60_T                             tnr_ctrl_60;	//0x03B0
	PE_M17_TNR_CTRL_61_T                             tnr_ctrl_61;	//0x03B4
	PE_M17_PE0_DEBUG3_T                              pe0_debug3;	//0x03B8
}PE_ND_ND0_REG_M17_T;


typedef struct
{ 
	PE_M17_PE0_DNR_LOAD_T                                pe0_load;	//0x0000
	PE_M17_PE0_DNR_INTR_T                                pe0_intr;	//0x0004
	PE_M17_PE0_DNR_STATUS0_T                             pe0_status0;	//0x0008
	PE_M17_PE0_DNR_STATUS1_T                             pe0_status1;	//0x000C
	PE_M17_PE0_DNR_OPMODE_T                              pe0_opmode;	//0x0010
	PE_M17_PE0_DNR_IN_SIZE_T                             pe0_in_size;	//0x0014
	PE_M17_PE0_DNR_IN_OFFSET_T                           pe0_in_offset;	//0x0018
	PE_M17_PE0_OUT_SIZE_T                            pe0_out_size;	//0x001C
	PE_M17_WIN_CTRL_0_T                              win_ctrl_0;	//0x0020
	PE_M17_WIN_CTRL_1_T                              win_ctrl_1;	//0x0024
	PE_M17_WIN_CTRL_2_T                              win_ctrl_2;	//0x0028
	PE_M17_WIN_CTRL_3_T                              win_ctrl_3;	//0x002C
	PE_M17_CUP_CTRL_00_T                             cup_ctrl_00;	//0x0030
	PE_M17_CUP_CTRL_01_T                             cup_ctrl_01;	//0x0034
	PE_M17_CUP_CTRL_02_T                             cup_ctrl_02;	//0x0038
	UINT32                                            reserved00[5];	//0x003C-0x004C
	PE_M17__3DFD_CTRL_00_T                           pe0_3dfd_ctrl_00;	//0x0050
	PE_M17__3DFD_CTRL_01_T                           pe0_3dfd_ctrl_01;	//0x0054
	PE_M17__3DFD_CTRL_02_T                           pe0_3dfd_ctrl_02;	//0x0058
	PE_M17__3DFD_CTRL_03_T                           pe0_3dfd_ctrl_03;	//0x005C
	PE_M17__3DFD_STAT_00_T                           pe0_3dfd_stat_00;	//0x0060
	PE_M17__3DFD_STAT_01_T                           pe0_3dfd_stat_01;	//0x0064
	PE_M17__3DFD_STAT_02_T                           pe0_3dfd_stat_02;	//0x0068
	PE_M17__3DFD_STAT_03_T                           pe0_3dfd_stat_03;	//0x006C
	PE_M17__3DFD_STAT_04_T                           pe0_3dfd_stat_04;	//0x0070
	PE_M17__3DFD_STAT_05_T                           pe0_3dfd_stat_05;	//0x0074
	PE_M17__3DFD_STAT_06_T                           pe0_3dfd_stat_06;	//0x0078
	PE_M17__3DFD_STAT_07_T                           pe0_3dfd_stat_07;	//0x007C
	PE_M17_VFILTER_CTRL_00_T                         vfilter_ctrl_00;	//0x0080
	PE_M17_VFILTER_CTRL_01_T                         vfilter_ctrl_01;	//0x0084
	PE_M17_VFILTER_CTRL_02_T                         vfilter_ctrl_02;	//0x0088
	PE_M17_CTI_CTRL_0_T                              cti_ctrl_0;	//0x008C
	PE_M17_CTI_CTRL_1_T                              cti_ctrl_1;	//0x0090
	PE_M17_DNR_MAX_CTRL_T                            dnr_max_ctrl;	//0x0094
	PE_M17_DNR_DBAR_CTRL_T                           dnr_dbar_ctrl;	//0x0098
	PE_M17_REG_C420_CTRL_T                           reg_c420_ctrl;	//0x009C
	PE_M17_MNR_CTRL_0_T                              mnr_ctrl_0;	//0x00A0
	PE_M17_MNR_CTRL_1_T                              mnr_ctrl_1;	//0x00A4
	PE_M17_MNR_CTRL_2_T                              mnr_ctrl_2;	//0x00A8
	PE_M17_MNR_CTRL_3_T                              mnr_ctrl_3;	//0x00AC
	PE_M17_MNR_CTRL_4_T                              mnr_ctrl_4;	//0x00B0
	PE_M17_MNR_CTRL_5_T                              mnr_ctrl_5;	//0x00B4
	PE_M17_DETAIL_CTRL_T                             detail_ctrl;	//0x00B8
	PE_M17_DC_BNR_CTRL_0_T                           dc_bnr_ctrl_0;	//0x00BC
	PE_M17_DC_BNR_CTRL_1_T                           dc_bnr_ctrl_1;	//0x00C0
	PE_M17_DC_BNR_CTRL_2_T                           dc_bnr_ctrl_2;	//0x00C4
	PE_M17_DC_BNR_CTRL_3_T                           dc_bnr_ctrl_3;	//0x00C8
	PE_M17_DC_BNR_CTRL_4_T                           dc_bnr_ctrl_4;	//0x00CC
	PE_M17_DC_BNR_CTRL_5_T                           dc_bnr_ctrl_5;	//0x00D0
	PE_M17_AC_BNR_CTRL_0_T                           ac_bnr_ctrl_0;	//0x00D4
	PE_M17_AC_BNR_CTRL_1_T                           ac_bnr_ctrl_1;	//0x00D8
	PE_M17_AC_BNR_CTRL_2_T                           ac_bnr_ctrl_2;	//0x00DC
	PE_M17_DNR_STAT_0_T                              dnr_stat_0;	//0x00E0
	PE_M17_AC_BNR_CTRL_3_T                           ac_bnr_ctrl_3;	//0x00E4
	PE_M17_AC_BNR_CTRL_4_T                           ac_bnr_ctrl_4;	//0x00E8
	PE_M17_DNR_STAT_1_T                              dnr_stat_1;	//0x00EC
	PE_M17_AC_BNR_CTRL_5_T                           ac_bnr_ctrl_5;	//0x00F0
	PE_M17_AC_BNR_CTRL_6_T                           ac_bnr_ctrl_6;	//0x00F4
	PE_M17_AC_BNR_CTRL_7_T                           ac_bnr_ctrl_7;	//0x00F8
	PE_M17_DNR_STAT_2_T                              dnr_stat_2;	//0x00FC
	PE_M17_AC_BNR_CTRL_8_T                           ac_bnr_ctrl_8;	//0x0100
	PE_M17_AC_BNR_CTRL_9_T                           ac_bnr_ctrl_9;	//0x0104
	PE_M17_AC_BNR_CTRL_10_T                          ac_bnr_ctrl_10;	//0x0108
	PE_M17_AC_BNR_CTRL_11_T                          ac_bnr_ctrl_11;	//0x010C
	PE_M17_AC_BNR_CTRL_12_T                          ac_bnr_ctrl_12;	//0x0110
	PE_M17_IFC_CTRL_0_T                              ifc_ctrl_0;	//0x0114
	PE_M17_IFC_CTRL_1_T                              ifc_ctrl_1;	//0x0118
	PE_M17_IFC_CTRL_2_T                              ifc_ctrl_2;	//0x011C
	PE_M17_IFC_CTRL_3_T                              ifc_ctrl_3;	//0x0120
	PE_M17_IFC_CTRL_4_T                              ifc_ctrl_4;	//0x0124
	PE_M17_IFC_CTRL_5_T                              ifc_ctrl_5;	//0x0128
	PE_M17_IFC_CTRL_6_T                              ifc_ctrl_6;	//0x012C
	PE_M17_IFC_CTRL_7_T                              ifc_ctrl_7;	//0x0130
	PE_M17_IFC_CTRL_8_T                              ifc_ctrl_8;	//0x0134
	PE_M17_IFC_CTRL_9_T                              ifc_ctrl_9;	//0x0138
	PE_M17_IFC_CTRL_10_T                             ifc_ctrl_10;	//0x013C
	PE_M17_IFC_CTRL_11_T                             ifc_ctrl_11;	//0x0140
	PE_M17_IFC_CTRL_12_T                             ifc_ctrl_12;	//0x0144
	PE_M17_IFC_CTRL_13_T                             ifc_ctrl_13;	//0x0148
	PE_M17_IFC_CTRL_14_T                             ifc_ctrl_14;	//0x014C
	PE_M17_IFC_CTRL_15_T                             ifc_ctrl_15;	//0x0150
	PE_M17_IFC_CTRL_16_T                             ifc_ctrl_16;	//0x0154
	PE_M17_IFC_CTRL_17_T                             ifc_ctrl_17;	//0x0158
	PE_M17_IFC_CTRL_18_T                             ifc_ctrl_18;	//0x015C
	PE_M17_IFC_CTRL_19_T                             ifc_ctrl_19;	//0x0160
	PE_M17_IFC_CTRL_20_T                             ifc_ctrl_20;	//0x0164
	PE_M17_IFC_CTRL_21_T                             ifc_ctrl_21;	//0x0168
	PE_M17_SC_BNR_CTRL_0_T                           sc_bnr_ctrl_0;	//0x016C
	PE_M17_SC_BNR_CTRL_1_T                           sc_bnr_ctrl_1;	//0x0170
	PE_M17_SC_BNR_CTRL_2_T                           sc_bnr_ctrl_2;	//0x0174
	PE_M17_SC_BNR_CTRL_3_T                           sc_bnr_ctrl_3;	//0x0178
	PE_M17_SC_BNR_CTRL_4_T                           sc_bnr_ctrl_4;	//0x017C
	PE_M17_SC_BNR_CTRL_5_T                           sc_bnr_ctrl_5;	//0x0180
	PE_M17_SC_BNR_CTRL_6_T                           sc_bnr_ctrl_6;	//0x0184
	PE_M17_C_PRE_BLUR_CTRL_0_T                       c_pre_blur_ctrl_0;	//0x0188
	PE_M17_TEXTURE_CTRL_0_T                          texture_ctrl_0;	//0x018C
	PE_M17_TEXTURE_CTRL_1_T                          texture_ctrl_1;	//0x0190
	PE_M17_TEXTURE_CTRL_2_T                          texture_ctrl_2;	//0x0194
	PE_M17_TEXTURE_CTRL_3_T                          texture_ctrl_3;	//0x0198
	PE_M17_AC_BNR_CTRL_13_T                          ac_bnr_ctrl_13;	//0x019C
	PE_M17_AC_BNR_CTRL_14_T                          ac_bnr_ctrl_14;	//0x01A0
	PE_M17_DC_BNR_CTRL_6_T                           dc_bnr_ctrl_6;	//0x01A4
	PE_M17_DC_BNR_CTRL_7_T                           dc_bnr_ctrl_7;	//0x01A8
	PE_M17_SQM_CTRL_0_T                              sqm_ctrl_0;	//0x01AC
	PE_M17_SQM_CTRL_1_T                              sqm_ctrl_1;	//0x01B0
	PE_M17_SQM_CTRL_2_T                              sqm_ctrl_2;	//0x01B4
	PE_M17_SQM_CTRL_3_T                              sqm_ctrl_3;	//0x01B8
	PE_M17_SQM_CTRL_4_T                              sqm_ctrl_4;	//0x01BC
	PE_M17_TPD_CTRL_0_T                              tpd_ctrl_0;	//0x01C0
	PE_M17_WINDOW_MODE_0_T                           window_mode_0;	//0x01C4
	PE_M17_WINDOW_MODE_1_T                           window_mode_1;	//0x01C8
	UINT32                                            reserved115;	//0x1cc
	PE_M17_DNR_STAT_3_T                              dnr_stat_3;	//0x01D0
	PE_M17_DNR_STAT_4_T                              dnr_stat_4;	//0x01D4
	PE_M17_DNR_STAT_5_T                              dnr_stat_5;	//0x01D8
	PE_M17_DNR_STAT_6_T                              dnr_stat_6;	//0x01DC
	PE_M17_DNR_STAT_7_T                              dnr_stat_7;	//0x01E0
	PE_M17_DNR_STAT_8_SC_BNR0_T                      dnr_stat_8_sc_bnr0;	//0x01E4
	PE_M17_DNR_STAT_9_SC_BNR1_T                      dnr_stat_9_sc_bnr1;	//0x01E8
	PE_M17_DNR_STAT_10_SC_BNR2_T                     dnr_stat_10_sc_bnr2;	//0x01EC
	PE_M17_DNR_STAT_11_SQM_00_T                      dnr_stat_11_sqm_00;	//0x01F0
	PE_M17_DNR_STAT_12_SQM_01_T                      dnr_stat_12_sqm_01;	//0x01F4
	PE_M17_DNR_STAT_13_SQM_02_T                      dnr_stat_13_sqm_02;	//0x01F8
	PE_M17_DNR_STAT_14_SQM_03_T                      dnr_stat_14_sqm_03;	//0x01FC
	PE_M17_DNR_STAT_15_SQM_04_T                      dnr_stat_15_sqm_04;	//0x0200
	PE_M17_DNR_STAT_16_SQM_05_T                      dnr_stat_16_sqm_05;	//0x0204
	PE_M17_DNR_STAT_17_SQM_06_T                      dnr_stat_17_sqm_06;	//0x0208
	PE_M17_DNR_STAT_18_SQM_07_T                      dnr_stat_18_sqm_07;	//0x020C
	PE_M17_DNR_STAT_19_SQM_08_T                      dnr_stat_19_sqm_08;	//0x0210
	PE_M17_DNR_STAT_20_SQM_09_T                      dnr_stat_20_sqm_09;	//0x0214
	PE_M17_DNR_STAT_21_SQM_10_T                      dnr_stat_21_sqm_10;	//0x0218
	PE_M17_DNR_STAT_22_SQM_11_T                      dnr_stat_22_sqm_11;	//0x021C
	PE_M17_DNR_STAT_23_TPD_0_T                       dnr_stat_23_tpd_0;	//0x0220
	PE_M17_DNR_STAT_24_TPD_1_T                       dnr_stat_24_tpd_1;	//0x0224
	PE_M17_DNR_STAT_25_TPD_2_T                       dnr_stat_25_tpd_2;	//0x0228
	UINT32                                            reserved01;	//0x022C-0x022C
	PE_M17_AC_BNR_15_T                               ac_bnr_15;	//0x0230
	PE_M17_AC_BNR_16_T                               ac_bnr_16;	//0x0234
	PE_M17_VFILTER_CTRL_03_T                         vfilter_ctrl_03;	//0x0238
	PE_M17_VFILTER_CTRL_04_T                         vfilter_ctrl_04;	//0x023C
	PE_M17_VFILTER_CTRL_05_T                         vfilter_ctrl_05;	//0x0240
	PE_M17_VFILTER_CTRL_06_T                         vfilter_ctrl_06;	//0x0244
	PE_M17_VFILTER_CTRL_07_T                         vfilter_ctrl_07;	//0x0248
	PE_M17_VFILTER_CTRL_08_T                         vfilter_ctrl_08;	//0x024C
	PE_M17_VFILTER_CTRL_09_T                         vfilter_ctrl_09;	//0x0250
	PE_M17_VFILTER_CTRL_10_T                         vfilter_ctrl_10;	//0x0254
	PE_M17_VFILTER_CTRL_11_T                         vfilter_ctrl_11;	//0x0258
	PE_M17_VFILTER_CTRL_12_T                         vfilter_ctrl_12;	//0x025C
	PE_M17_VFILTER_CTRL_13_T                         vfilter_ctrl_13;	//0x0260
	PE_M17_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0x0264
	PE_M17_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0x0268
	PE_M17_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0x026C
	PE_M17_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0x0270
	PE_M17_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0x0274
	PE_M17_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0x0278
	PE_M17_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0x027C
	PE_M17_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0x0280
	PE_M17_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0x0284
	PE_M17_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0x0288
	PE_M17_REG_DECON_CTRL_10_T                       reg_decon_ctrl_10;	//0x028C
	PE_M17_REG_DC_BNR_CTRL_8_T                       reg_dc_bnr_ctrl_8;	//0x0290
	PE_M17_REG_DC_BNR_CTRL_9_T                       reg_dc_bnr_ctrl_9;	//0x0294
	PE_M17_REG_DC_BNR_CTRL_10_T                      reg_dc_bnr_ctrl_10;	//0x0298
	PE_M17_REG_DC_BNR_CTRL_11_T                      reg_dc_bnr_ctrl_11;	//0x029C
}PE_ND_DNR0_REG_M17_T;


typedef struct {
	PE_M17_CTRL_M0_Y_LEVEL_CTRL_T         ctrl_m0_y_level_ctrl;
}PE_TOP_IMX_REG_M17_T;

typedef struct {
	PE_M17_IPP_CTRL0_T               	ipp_ctrl0;                    //0xc8001400L
	UINT32                             	reserved01[12];               //0xc8001404L ~0xc8001430L
	PE_M17_IPP_SIZE_I_T              	ipp_size_i;                   //0xc8001434L
}PE_IPP_REG_M17_T;

#endif

