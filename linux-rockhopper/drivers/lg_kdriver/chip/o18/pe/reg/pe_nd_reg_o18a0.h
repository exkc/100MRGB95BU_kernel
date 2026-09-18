#ifndef _PE_ND_REG_O18A0_H_
#define _PE_ND_REG_O18A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9003100L pe0_load                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	load_time                          :1 ,	// 0 
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_O18_PE0_ND_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9003104L pe0_intr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	intr_enable                        :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	intr_src                           :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	timer_rst_sel                      :1 ,	// 8 
	reserved03                         :7 ,	// reserved
	intr_line_pos                      :11;	// 26:16
}PE_O18_PE0_ND_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9003108L pe0_status0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tnr_frame_id                       :4 ,	// 3:0
	ipc_frame_id                       :4 ,	// 7:4
	tnrw_y_frame_id                    :4 ,	// 11:8
	tnrw_c_frame_id                    :4 ,	// 15:12
	dnr_frame_id                       :8 ,	// 23:16
	pic_init_frame_id                  :4 ;	// 27:24
}PE_O18_PE0_ND_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc900310cL pe0_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt                           :11,	// 10:0
	reserved01                         :5 ,	// reserved
	timer_cnt                          :16;	// 31:16
}PE_O18_PE0_ND_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9003110L pe0_opmode                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tnr_c_en                           :1 ,	// 0 
	tnr_y_en                           :1 ,	// 1 
	ipc_c_en                           :1 ,	// 2 
	ipc_y_en                           :1 ,	// 3 
	tnr_c_444_as_420                   :1 ,	// 4 
	tnr_y2_en                          :1 ,	// 5 
	force_422_to_420                   :1 ,	// 6 
	ipc0_y_en_prog                     :1 ,	// 7 
	mif_last_mode                      :3 ,	// 10:8
	tnrw_off                           :1 ,	// 11
	reserved01                         :1 ,	// reserved
	tnr_m_en                           :1 ,	// 13
	force_444_to_422                   :1 ,	// 14
	minfo_rpt_o_last_en                :1 ,	// 15
	detour_enable                      :1 ,	// 16
	half_rate_en                       :1 ,	// 17
	ibuf_en                            :2 ,	// 19:18
	minfo_hsample_mode                 :3 ,	// 22:20
	minfo_vsample_mode                 :3 ,	// 25:23
	o_line_ctrl_mode                   :1 ,	// 26
	o_line_ctrl_en                     :1 ,	// 27
	tnr_in_lsb_mode                    :2 ,	// 29:28
	m_run_id                           :2 ;	// 31:30
}PE_O18_PE0_ND_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9003114L pe0_src_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :1 ,	// reserved
	cs_type                            :3 ,	// 15:13
	vsize                              :12,	// 27:16
	reserved02                         :3 ,	// reserved
	scan_type                          :1 ;	// 31
}PE_O18_PE0_ND_SRC_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9003118L pe0_field                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	field_id                           :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	field_mode                         :2 ,	// 5:4
	field_inv                          :1 ,	// 6 
	reserved02                         :1 ,	// reserved
	secam_line                         :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	secam_line_mode                    :2 ,	// 13:12
	reserved04                         :2 ,	// reserved
	out_cs_type                        :3 ,	// 18:16
	reserved05                         :1 ,	// reserved
	out_422_hsample_mode               :1 ,	// 20
	out_420_vsample_mode               :1 ;	// 21
}PE_O18_PE0_FIELD_T;
/*-----------------------------------------------------------------------------
                             0xc900311cL pe0_debug_lend_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	in_hsize                           :12,	// 11:0
	reserved01                         :16,	// reserved
	ptn_en_c                           :1 ,	// 28
	ptn_en_y                           :1 ,	// 29
	lend_manual_hsize                  :1 ,	// 30
	lend_ctrl_en                       :1 ;	// 31
}PE_O18_PE0_DEBUG_LEND_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9003120L pe0_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O18_PE0_ND_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9003124L pe0_in_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O18_PE0_ND_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9003128L fbc_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fbc_core_en_y                      :1 ,	// 0 
	fbc_core_20p_y                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	fbc_dual_haar_th_y                 :4 ,	// 7:4
	reserved02                         :8 ,	// reserved
	fbc_dpcm_reset_mode_y              :2 ,	// 17:16
	reserved03                         :5 ,	// reserved
	fbc_en_y                           :1 ;	// 23
}PE_O18_FBC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900312cL fbc_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fbc_core_en_c                      :1 ,	// 0 
	fbc_core_20p_c                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	fbc_dual_haar_th_c                 :4 ,	// 7:4
	reserved02                         :8 ,	// reserved
	fbc_dpcm_reset_mode_c              :2 ,	// 17:16
	reserved03                         :5 ,	// reserved
	fbc_en_c                           :1 ;	// 23
}PE_O18_FBC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9003130L pe0_debug_mem_req                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	en_rd_t1_y                         :1 ,	// 0 
	en_rd_t1_c                         :1 ,	// 1 
	en_rd_t2_y                         :1 ,	// 2 
	en_rd_t2_c                         :1 ,	// 3 
	en_rd_t3_y                         :1 ,	// 4 
	en_rd_t3_c                         :1 ,	// 5 
	en_rd_t4_y                         :1 ,	// 6 
	en_rd_t1_m                         :1 ,	// 7 
	en_wr_tnrw_y                       :1 ,	// 8 
	en_wr_tnrw_c                       :1 ,	// 9 
	en_wr_tnrw_m                       :1 ,	// 10
	reserved01                         :4 ,	// reserved
	manual_mem_en                      :1 ;	// 15
}PE_O18_PE0_DEBUG_MEM_REQ_T;
/*-----------------------------------------------------------------------------
                             0xc9003134L pe0_debug_lreq_dly                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lreq_dly_c                         :11,	// 10:0
	lreq_dly_c_en                      :1 ,	// 11
	reserved01                         :4 ,	// reserved
	lreq_dly_y                         :11,	// 26:16
	lreq_dly_y_en                      :1 ;	// 27
}PE_O18_PE0_DEBUG_LREQ_DLY_T;
/*-----------------------------------------------------------------------------
                             0xc9003138L tnrw_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O18_TNRW_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900313cL tnrw_out_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O18_TNRW_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9003140L tnr_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_en                         :1 ,	// 0:0
	reg_nlvl_input_sel                 :1 ,	// 1:1
	reg_sc_detect_hres                 :1 ,	// 2:2
	reg_clc_nt_pal                     :1 ,	// 3:3
	reg_clc_mem_wr_mode                :2 ,	// 5:4
	reg_sad_8x3_res                    :2 ,	// 7:6
	reg_sad_8x3_iir_en                 :1 ,	// 8:8
	reg_sad_8x3_chroma_en              :1 ,	// 9:9
	reg_minfo_sw                       :2 ,	// 11:10
	reg_minfo_mode10                   :2 ,	// 13:12
	reg_minfo_flt                      :2 ,	// 15:14
	reg_tnr_single_en                  :1 ,	// 16:16
	reserved01                         :1 ,	// reserved
	reg_minfo_mode32                   :2 ,	// 19:18
	reg_minfo_mode74                   :4 ,	// 23:20
	reg_sad_8x3_iir_alpha              :8 ;	// 31:24
}PE_O18_TNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003144L tnr_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_show                       :4 ,	// 3:0
	reg_minfo_mode9_8                  :2 ,	// 5:4
	reg_minfo_mode11_10                :2 ,	// 7:6
	reg_dbg_p2_vline_sel               :5 ,	// 12:8
	reserved01                         :3 ,	// reserved
	reg_dbg_tnrw                       :2 ,	// 17:16
	reserved02                         :2 ,	// reserved
	reg_tnri_debug_mode                :2 ,	// 21:20
	reserved03                         :2 ,	// reserved
	reg_bsum_scale                     :2 ;	// 25:24
}PE_O18_TNR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003148L tnr_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sc_en                              :1 ,	// 0 
	sc_max_flt_en                      :1 ,	// 1 
	sc_calc_prev_hist                  :1 ,	// 2 
	sc_chroma_en                       :1 ,	// 3 
	sc_scale                           :3 ,	// 6:4
	reserved01                         :1 ,	// reserved
	sc_max_flt_tap                     :3 ,	// 10:8
	reserved02                         :1 ,	// reserved
	sc_chroma_gain                     :3 ,	// 14:12
	sc_out_mode                        :1 ,	// 15
	sc_th_ma                           :8 ,	// 23:16
	sc_th_memc                         :8 ;	// 31:24
}PE_O18_TNR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900314cL tnr_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	show_dbg_bar_scale                 :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	show_dbg_bar_en                    :4 ,	// 7:4
	reserved02                         :8 ,	// reserved
	show_dbg_bar0_mux                  :4 ,	// 19:16
	show_dbg_bar1_mux                  :4 ,	// 23:20
	show_dbg_bar2_mux                  :4 ,	// 27:24
	show_dbg_bar3_mux                  :4 ;	// 31:28
}PE_O18_TNR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003150L tnr_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_debug_bar_09                :8 ,	// 7:0
	manual_debug_bar_10                :8 ,	// 15:8
	manual_debug_bar_11                :8 ,	// 23:16
	manual_debug_bar_12                :8 ;	// 31:24
}PE_O18_TNR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003154L tnr_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mamc_blend_mode                :2 ,	// 1:0
	reg_mamc_blend_mv_max_or_sum       :1 ,	// 2 
	reg_mamc_ma_sad_cut                :1 ,	// 3 
	reg_mamc_mc_sad_cut                :1 ,	// 4 
	reserved01                         :11,	// reserved
	reg_mv_pv_fix_v                    :4 ,	// 19:16
	reg_mv_pv_fix_h                    :5 ,	// 24:20
	reserved02                         :6 ,	// reserved
	reg_mv_pv_fix_en                   :1 ;	// 31
}PE_O18_TNR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003158L tnr_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_me_lb_base                     :8 ,	// 7:0
	reg_me_pv_base                     :8 ,	// 15:8
	reg_me_lb_polarity                 :1 ,	// 16
	reserved01                         :7 ,	// reserved
	reg_me_rgn_base                    :8 ;	// 31:24
}PE_O18_TNR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900315cL tnr_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_5x5_sad_cut                    :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_sc_en                          :1 ;	// 8 
}PE_O18_TNR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003160L tnr_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mv_h_fix_val                   :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_mv_v_fix_val                   :4 ,	// 11:8
	reg_mv_h_fix_fb_val                :5 ,	// 16:12
	reserved02                         :3 ,	// reserved
	reg_mv_v_fix_fb_val                :4 ,	// 23:20
	reg_debug_sel                      :4 ,	// 27:24
	reg_lb_monitor_sel                 :2 ,	// 29:28
	reg_mv_fb_fix                      :1 ,	// 30
	reg_mv_fix                         :1 ;	// 31
}PE_O18_TNR_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003164L tnr_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_base                       :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lb_smooth_clip                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_pv_smooth_clip                 :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_rgn_smooth_clip                :6 ;	// 29:24
}PE_O18_TNR_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003168L tnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	phase_bm_off                       :2 ,	// 1:0
	phase_sm_off                       :2 ,	// 3:2
	phase_lb_off                       :2 ,	// 5:4
	phase_pv_off                       :2 ,	// 7:6
	phase_mc_off                       :2 ;	// 9:8
}PE_O18_TNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900316cL tnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lb_smooth_en                       :1 ,	// 0 
	pv_smooth_en                       :1 ,	// 1 
	rgn_smooth_en                      :1 ,	// 2 
	reg_lb_dist_wgt_en                 :2 ,	// 4:3
	lb_mv_h_off                        :2 ,	// 6:5
	lb_mv_v_off                        :2 ,	// 8:7
	pv_mv_h_off                        :2 ,	// 10:9
	pv_mv_v_off                        :2 ,	// 12:11
	reserved01                         :18,	// reserved
	reg_me_n15_protection              :1 ;	// 31
}PE_O18_TNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003170L tnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_rgn_area_cut_lsb_ofst          :3 ,	// 18:16
	reserved02                         :1 ,	// reserved
	reg_lb_area_cut_lsb_ofst           :3 ;	// 22:20
}PE_O18_TNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003174L tnr_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_min_sad_ratio                  :8 ,	// 7:0
	reg_lb_cost_ratio                  :8 ,	// 15:8
	reg_zero_sad_ratio                 :8 ,	// 23:16
	reg_zero_mv_blk_mv_sel             :2 ,	// 25:24
	reserved01                         :2 ,	// reserved
	reg_zero_sad_adv                   :1 ;	// 28
}PE_O18_TNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9003178L tnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rgn_max_cost                   :8 ,	// 7:0
	reg_rgn_max_cost_shft              :4 ;	// 11:8
}PE_O18_TNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900317cL tnr_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rgn_heigt                      :12,	// 11:0
	reg_rgn_area_wgt_en                :1 ,	// 12
	reserved01                         :3 ,	// reserved
	reg_rgn_width                      :12,	// 27:16
	reserved02                         :2 ,	// reserved
	reg_frc_rgn_mv_vfast_en            :1 ,	// 30
	reg_pv_9x15_hist_en                :1 ;	// 31
}PE_O18_TNR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9003180L tnr_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_acc_mode                   :2 ,	// 1:0
	reg_bmv_fix_en                     :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	reg_bmv_fix_v                      :4 ,	// 7:4
	reg_bmv_fix_h                      :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_n_hblk                         :4 ,	// 19:16
	reg_n_vblk                         :5 ,	// 24:20
	reserved03                         :6 ,	// reserved
	reg_blk_area_wgt_en                :1 ;	// 31
}PE_O18_TNR_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9003184L tnr_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blk_vsize                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_blk_hsize                      :12;	// 27:16
}PE_O18_TNR_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9003188L tnr_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bsad_scale                     :3 ,	// 2:0
	reg_bmv_rst_mode                   :1 ,	// 3 
	reg_gsad_scale                     :3 ,	// 6:4
	reserved01                         :1 ,	// reserved
	reg_gmv_gmv_tl                     :7 ,	// 14:8
	reg_gmv_gmv_tl_en                  :1 ,	// 15
	reg_bmv_gmv_tl                     :7 ,	// 22:16
	reg_bmv_gmv_tl_en                  :1 ,	// 23
	reg_bmv_pmv_tl                     :7 ,	// 30:24
	reg_bmv_pmv_tl_en                  :1 ;	// 31
}PE_O18_TNR_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900318cL tnr_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bmv_coring_th                      :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	gmv_0mv_tl                         :7 ,	// 22:16
	gmv_0mv_tl_en                      :1 ,	// 23
	bmv_0mv_tl                         :7 ,	// 30:24
	bmv_0mv_tl_en                      :1 ;	// 31
}PE_O18_TNR_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9003190L tnr_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_detail_beta_mul                :8 ,	// 7:0
	reg_detail_alpha_mul               :8 ,	// 15:8
	reg_edge_beta_mul                  :8 ,	// 23:16
	reg_edge_alpha_mul                 :8 ;	// 31:24
}PE_O18_TNR_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9003194L tnr_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_svar_scale                     :3 ;	// 2:0
}PE_O18_TNR_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc9003198L tnr_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc900319cL tnr_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90031a0L tnr_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_p2f_mode                       :1 ,	// 0 
	reg_ombc_en                        :1 ,	// 1 
	reg_decontour_blend_en             :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	reg_luma_gain_en                   :1 ,	// 4 
	reg_crgn_gain_en                   :1 ,	// 5 
	reg_chroma_sad_res                 :2 ,	// 7:6
	reg_sad_sum_cut                    :2 ,	// 9:8
	reserved02                         :2 ,	// reserved
	reg_5x5_sad_cut                    :2 ,	// 13:12
	reserved03                         :2 ,	// reserved
	reg_avg_cmp_en                     :1 ,	// 16
	reg_avg_cmp_res                    :3 ,	// 19:17
	reg_debug_sel                      :4 ,	// 23:20
	reserved04                         :4 ,	// reserved
	reg_cnt_mode                       :3 ,	// 30:28
	reg_chroma_sad_en                  :1 ;	// 31
}PE_O18_TNR_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90031a4L tnr_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_blur_en                        :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	cut_resolution                     :2 ,	// 3:2
	reg_pre_blur_g00                   :4 ,	// 7:4
	reg_pre_blur_g01                   :3 ,	// 10:8
	reg_pre_blur_g02                   :3 ,	// 13:11
	reg_pre_blur_g10                   :3 ,	// 16:14
	reg_pre_blur_g11                   :3 ,	// 19:17
	reg_pre_blur_g12                   :3 ,	// 22:20
	reg_pre_blur_g20                   :3 ,	// 25:23
	reg_pre_blur_g21                   :3 ,	// 28:26
	reg_pre_blur_g22                   :3 ;	// 31:29
}PE_O18_TNR_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90031a8L tnr_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_blur_en                        :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	cut_resolution                     :2 ,	// 3:2
	reg_pre_blur_g00                   :4 ,	// 7:4
	reg_pre_blur_g01                   :3 ,	// 10:8
	reg_pre_blur_g02                   :3 ,	// 13:11
	reg_pre_blur_g10                   :3 ,	// 16:14
	reg_pre_blur_g11                   :3 ,	// 19:17
	reg_pre_blur_g12                   :3 ,	// 22:20
	reg_pre_blur_g20                   :3 ,	// 25:23
	reg_pre_blur_g21                   :3 ,	// 28:26
	reg_pre_blur_g22                   :3 ;	// 31:29
}PE_O18_TNR_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90031acL tnr_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90031b0L tnr_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_filtered_en                    :1 ,	// 0 
	luma_gain_en                       :1 ,	// 1 
	cut_resolution                     :2 ,	// 3:2
	reserved01                         :1 ,	// reserved
	reg_pre_detail_cttl_g0             :7 ,	// 11:5
	reg_pre_detail_cttl_g4             :5 ,	// 16:12
	reg_pre_detail_cttl_g3             :5 ,	// 21:17
	reg_pre_detail_cttl_g2             :5 ,	// 26:22
	reg_pre_detail_cttl_g1             :5 ;	// 31:27
}PE_O18_TNR_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90031b4L tnr_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_master_en                        :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	r_master_gain                      :8 ,	// 15:8
	reserved02                         :8 ,	// reserved
	r_diff_limit                       :8 ;	// 31:24
}PE_O18_TNR_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90031b8L tnr_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pre_filtered_en                :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_cut_resolution                 :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_denoise_gain                   :8 ,	// 15:8
	reg_denoise_ctrl_g0                :7 ;	// 22:16
}PE_O18_TNR_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90031bcL tnr_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_denoise_ctrl_g4                :5 ,	// 4:0
	reserved01                         :3 ,	// reserved
	reg_denoise_ctrl_g3                :5 ,	// 12:8
	reserved02                         :3 ,	// reserved
	reg_denoise_ctrl_g2                :5 ,	// 20:16
	reserved03                         :3 ,	// reserved
	reg_denoise_ctrl_g1                :5 ;	// 28:24
}PE_O18_TNR_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90031c0L tnr_status_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_gsad                             :8 ,	// 7:0
	w_gmv                              :9 ,	// 16:8
	reserved01                         :7 ,	// reserved
	w_apl_detail                       :8 ;	// 31:24
}PE_O18_TNR_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc90031c4L tnr_status_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_apl_motion                       :8 ,	// 7:0
	w_apl_mc_sad                       :8 ,	// 15:8
	w_apl_var                          :8 ,	// 23:16
	w_apl_edge                         :8 ;	// 31:24
}PE_O18_TNR_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc90031c8L tnr_status_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc90031ccL tnr_status_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc90031d0L tnr_main_lut_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	main_lut_indir_addr                :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	main_lut_ai_enable                 :1 ,	// 12
	reserved02                         :2 ,	// reserved
	main_lut_load                      :1 ;	// 15
}PE_O18_TNR_MAIN_LUT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90031d4L tnr_main_lut_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	main_lut_indir_data0;	// 31:0
}PE_O18_TNR_MAIN_LUT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90031dcL tnr_status_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sc_measure                         :8 ,	// 7:0
	apl_y                              :8 ,	// 15:8
	sc_measure_16                      :16;	// 31:16
}PE_O18_TNR_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc90031e0L tnr_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_gf_gain                        :8 ,	// 23:16
	reg_blur_coef                      :8 ;	// 31:24
}PE_O18_TNR_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90031e4L tnr_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	same_protection_en                 :1 ,	// 0 
	p_mv0_only                         :1 ,	// 1 
	same_protection2_en                :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	move_step                          :4 ,	// 7:4
	same_sad_th                        :8 ;	// 15:8
}PE_O18_TNR_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90031e8L tnr_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90031ecL tnr_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc90031f0L tnr_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc90031f4L tnr_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc90031f8L tnr_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc90031fcL tnr_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O18_TNR_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9003200L ipc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_luma_mode                       :2 ,	// 1:0
	reserved01                         :1 ,	// reserved
	cr_n1_cc_blend_en                  :1 ,	// 3 
	cr_chroma_mode                     :2 ,	// 5:4
	cr_integer_edi                     :1 ,	// 6 
	cr_chroma_edi                      :1 ,	// 7 
	cr_st_2d_v_flt_range2              :4 ,	// 11:8
	cr_st_2d_v_flt_range               :4 ,	// 15:12
	cr_ori_3d_blur_y                   :2 ,	// 17:16
	cr_ori_3d_blur_c                   :2 ,	// 19:18
	cr_tava_v_edge_adap                :1 ,	// 20
	cr_tava_debug_mode                 :1 ,	// 21
	cr_tava_st_adap                    :1 ,	// 22
	cr_tava_en                         :1 ,	// 23
	cr_hmc_force_fmd                   :1 ,	// 24
	cr_st_2d_v_flt_en                  :1 ,	// 25
	cr_clc_fmd_off                     :1 ,	// 26
	cr_chroma_tava_only                :1 ,	// 27
	cr_film_auto_gain                  :1 ,	// 28
	cr_film_apply_c                    :1 ,	// 29
	cr_film_apply_y                    :1 ,	// 30
	cr_film_mode_enable                :1 ;	// 31
}PE_O18_IPC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003204L ipc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_en_sel1                     :2 ,	// 1:0
	cr_hmc_en_sel2                     :2 ,	// 3:2
	st_flt_mode                        :1 ,	// 4 
	reserved01                         :1 ,	// reserved
	cr_fmd_vfilter_en                  :1 ,	// 6 
	cr_fend_auto                       :1 ,	// 7 
	cr_st_iir_dec_gain                 :4 ,	// 11:8
	cr_st_iir_inc_gain                 :4 ,	// 15:12
	cr_st_flt_enable                   :1 ,	// 16
	cr_st_iir_en                       :1 ,	// 17
	cr_hmc_flt_enable                  :1 ,	// 18
	cr_game_mode                       :1 ,	// 19
	cr_st_2d_v_flt_range               :4 ,	// 23:20
	reserved02                         :1 ,	// reserved
	cr_black_mask                      :1 ,	// 25
	cr_ipc_debug_show                  :5 ,	// 30:26
	cr_5f_mode                         :1 ;	// 31
}PE_O18_IPC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003208L ipc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fuzzy_ctrl_point_x0                :8 ,	// 7:0
	fuzzy_ctrl_point_x4                :8 ,	// 15:8
	fuzzy_ctrl_point_x1                :8 ,	// 23:16
	fuzzy_ctrl_point_y1                :8 ;	// 31:24
}PE_O18_IPC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900320cL ipc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fuzzy_ctrl_point_x2                :8 ,	// 7:0
	fuzzy_ctrl_point_y2                :8 ,	// 15:8
	fuzzy_ctrl_point_x3                :8 ,	// 23:16
	fuzzy_ctrl_point_y3                :8 ;	// 31:24
}PE_O18_IPC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003210L ipc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	et_offset__s7                      :8 ,	// 7:0
	motion_x_tearing_gain              :8 ,	// 15:8
	tearing_gain                       :8 ,	// 23:16
	motion_gain                        :8 ;	// 31:24
}PE_O18_IPC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003214L ipc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :12,	// reserved
	cr_t_grad_weight                   :4 ,	// 15:12
	reserved02                         :4 ,	// reserved
	cr_v_grad_weight                   :4 ,	// 23:20
	reserved03                         :4 ,	// reserved
	cr_h_grad_weight                   :4 ;	// 31:28
}PE_O18_IPC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003218L ipc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_normalize_en                    :1 ,	// 0 
	cr_flat_only                       :1 ,	// 1 
	cr_motion_iir_en                   :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	cr_tearing_normalize_en            :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	cr_normalize_base                  :8 ,	// 15:8
	cr_normalize_center                :8 ,	// 23:16
	cr_motion_coring                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900321cL ipc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	// reserved
	cr_v_en                            :1 ,	// 1 
	cr_45_en                           :1 ,	// 2 
	cr_15_en                           :1 ,	// 3 
	reserved02                         :20,	// reserved
	cr_iir_motion_gain                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003220L ipc_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fmd_caption_range_top              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	fmd_caption_range_bot              :12,	// 27:16
	reserved02                         :2 ,	// reserved
	caption_flow_detected              :1 ,	// 30
	hmc_when_cap_not_detected          :1 ;	// 31
}PE_O18_IPC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003224L ipc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pn_fmd_a_th                        :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	pn_variance_th                     :8 ,	// 23:16
	pn_fmd_motion_th                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003228L ipc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pcnc_fmd_a_th                      :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	pcnc_variance_th                   :8 ,	// 23:16
	pcnc_fmd_motion_th                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900322cL ipc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_pndiff_th                       :8 ,	// 7:0
	cr_center_bound_ctrl               :8 ,	// 15:8
	cr_dn_bound_ctrl                   :8 ,	// 23:16
	cr_up_bound_ctrl                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003230L ipc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th                    :8 ,	// 7:0
	reg_fmd_ratio_th                   :8 ,	// 15:8
	reg_fmd_max_th                     :8 ,	// 23:16
	reg_fmd_min_th                     :8 ;	// 31:24
}PE_O18_IPC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003234L ipc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_tava_chroma_mul                 :8 ,	// 7:0
	reserved01                         :4 ,	// reserved
	cr_hmc_alpha_th                    :8 ,	// 19:12
	cr_hmc_debug_mode                  :1 ,	// 20
	cr_hmc_debug_gain                  :6 ,	// 26:21
	cr_hmc_debug_dir                   :5 ;	// 31:27
}PE_O18_IPC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9003238L ipc_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lockcnt_en                     :1 ,	// 0 
	reserved                           :1 ,	// 1 
	reg_lock_speed                     :6 ,	// 7:2
	reg_lockcnt_th                     :8 ,	// 15:8
	reg_same_th                        :8 ,	// 23:16
	reg_still_frame_limit              :8 ;	// 31:24
}PE_O18_IPC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc900323cL ipc_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3_2_detect_en                  :1 ,	// 0 
	reg_3_2_detect_only                :1 ,	// 1 
	reg_3_2_lockcnt_255_en             :1 ,	// 2 
	reg_3_2_pndiff_disable             :1 ,	// 3 
	reg_hd_mode                        :1 ,	// 4 
	reserved01                         :3 ,	// reserved
	reg_3_2_pndiff_th                  :8 ,	// 15:8
	reg_3_2_pn_ratio_max_th            :8 ,	// 23:16
	reg_3_2_pn_ratio_min_th            :8 ;	// 31:24
}PE_O18_IPC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9003240L ipc_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th2                   :8 ,	// 7:0
	reg_still_prev_ratio               :8 ,	// 15:8
	reg_lock_reducer                   :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	reg_badedit_protect                :1 ;	// 31
}PE_O18_IPC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9003244L ipc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_inv_resolution                  :2 ,	// 1:0
	cr_field_manual_mode               :2 ,	// 3:2
	cr_field_inverse                   :1 ,	// 4 
	reserved01                         :19,	// reserved
	cr_tearing_a_th                    :8 ;	// 31:24
}PE_O18_IPC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9003248L ipc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_ud_gain                         :8 ,	// 7:0
	cr_lr_gain                         :8 ,	// 15:8
	cr_h_grad_gain                     :8 ,	// 23:16
	cr_v_grad_gain                     :8 ;	// 31:24
}PE_O18_IPC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc900324cL ipc_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_errs_gain                      :8 ,	// 7:0
	reg_confidence_gain                :8 ,	// 15:8
	reg_2d_offset                      :8 ,	// 23:16
	reg_flicker_gain                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9003250L ipc_status_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_v_count                       :16,	// 15:0
	r_nc_v_count                       :16;	// 31:16
}PE_O18_IPC_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003254L ipc_status_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_nc_same                       :16,	// 15:0
	r_pn_v_count                       :16;	// 31:16
}PE_O18_IPC_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003258L ipc_status_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :6 ,	// 5:0
	r_fmd_32_min_th_flag_u             :1 ,	// 6 
	r_fmd_32_max_th_flag_u             :1 ,	// 7 
	r_fmd_still_limit_flag_u           :1 ,	// 8 
	r_fmd_still_pn_th2_flag_u          :1 ,	// 9 
	r_fmd_still_pn_th_flag_u           :1 ,	// 10
	r_fmd_still_prev_ratio_flag_u      :1 ,	// 11
	r_fmd_bigger_flag_u                :1 ,	// 12
	r_fmd_smaller_flag_u               :1 ,	// 13
	r_fmd_3_2_fmd_comb_mode_u          :2 ,	// 15:14
	r_pn_diff_count                    :16;	// 31:16
}PE_O18_IPC_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc900325cL ipc_status_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	same_ng_flag_d                     :1 ,	// 0 
	too_small_flag_d                   :1 ,	// 1 
	r_fmd_still_flag_d                 :1 ,	// 2 
	r_fmd_possibility_flag_d           :1 ,	// 3 
	base_pn_ratio_flag_d               :1 ,	// 4 
	r_32_detected_flag_d               :1 ,	// 5 
	r_fmd_comb_mode_d                  :2 ,	// 7:6
	r_fmd_lock_count_d                 :8 ,	// 15:8
	same_ng_flag_u                     :1 ,	// 16
	too_small_flag_u                   :1 ,	// 17
	r_fmd_still_flag_u                 :1 ,	// 18
	r_fmd_possibility_flag_u           :1 ,	// 19
	base_pn_ratio_flag_u               :1 ,	// 20
	r_32_uetected_flag_u               :1 ,	// 21
	r_fmd_comb_mode_u                  :2 ,	// 23:22
	r_fmd_lock_count_u                 :8 ;	// 31:24
}PE_O18_IPC_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003260L clc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	// reserved
	cl_filter_enable                   :1 ,	// 1 
	clc_detection_enable               :1 ,	// 2 
	reserved02                         :1 ,	// reserved
	motion_window                      :2 ,	// 5:4
	cl_pattern_dist                    :2 ,	// 7:6
	reserved03                         :4 ,	// reserved
	cl_ab_ratio                        :4 ,	// 15:12
	cl_y_hdistance                     :2 ,	// 17:16
	cl_c_hdistance                     :2 ,	// 19:18
	cl_y_protect_en                    :1 ,	// 20
	reserved04                         :7 ,	// reserved
	cl_motion_a_filter                 :1 ,	// 28
	cl_motion_b_filter                 :1 ,	// 29
	cl_motion_a_mode                   :1 ;	// 30
}PE_O18_CLC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003264L clc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_motion_a_th                     :8 ,	// 7:0
	cl_motion_b_th                     :8 ,	// 15:8
	cl_y_protect_th0                   :8 ,	// 23:16
	cl_y_protect_th1                   :8 ;	// 31:24
}PE_O18_CLC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003268L clc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_y_bound_th                      :7 ,	// 6:0
	cl_c_bound_use_4line               :1 ,	// 7 
	cl_c_bound_th                      :7 ,	// 14:8
	cl_c_bound_type                    :1 ,	// 15
	cl_y_bound_width_chroma            :2 ,	// 17:16
	cl_y_bound_ignore_cc               :1 ,	// 18
	cl_y_bound_ignore_p2               :1 ,	// 19
	cl_y_bound_ignore_p4               :1 ,	// 20
	reg_bin3x1_flt_en                  :1 ,	// 21
	reserved01                         :2 ,	// reserved
	reg_bin5x1_flt_en                  :1 ,	// 24
	reg_bin5x1_flt_th                  :3 ,	// 27:25
	reg_vm_original_mode               :1 ,	// 28
	reg_vm_other_mode                  :1 ,	// 29
	cl_motionp2n2_th_pal_high          :2 ;	// 31:30
}PE_O18_CLC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900326cL clc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_sat_min                         :8 ,	// 7:0
	reserved01                         :2 ,	// reserved
	cl_var_measure_th1                 :10,	// 19:10
	cl_var_measure_th2                 :10,	// 29:20
	cl_pt_enable                       :2 ;	// 31:30
}PE_O18_CLC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003270L clc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_tearing_pt_th1                  :12,	// 11:0
	cl_motionp2n2_th_pal_low           :8 ,	// 19:12
	cl_frame_min                       :12;	// 31:20
}PE_O18_CLC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003274L clc_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_data_line_switching_sel         :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	clc_bin_flt_th                     :3 ,	// 10:8
	reserved02                         :4 ,	// reserved
	clc_bin_flt_en                     :1 ,	// 15
	clc_dbg_show_mask                  :13;	// 28:16
}PE_O18_CLC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003278L clc_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cc_c_filter_gain                   :8 ,	// 7:0
	cc_y_filter_when_cc_detected       :1 ,	// 8 
	reserved01                         :1 ,	// reserved
	cl_cc_original_en                  :1 ,	// 10
	clc_force_non_fmd                  :1 ,	// 11
	cl_c_filter_when_cl_detected       :1 ,	// 12
	cl_y_filter_when_cl_detected       :1 ,	// 13
	clc_filter_mode                    :2 ,	// 15:14
	reserved02                         :8 ,	// reserved
	cl_cc_protection_th                :8 ;	// 31:24
}PE_O18_CLC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900327cL clc_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	cl_detection_count                 :16;	// 31:16
}PE_O18_CLC_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003280L ipc_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_v_diff_y0                     :8 ,	// 7:0
	tava_v_diff_x0                     :8 ,	// 15:8
	tava_v_diff_y1                     :8 ,	// 23:16
	tava_v_diff_x1                     :8 ;	// 31:24
}PE_O18_IPC_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9003284L ipc_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_div_en                         :1 ,	// 0 
	cr_bound_exp_en                    :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	cr_sub_main_sel                    :1 ,	// 4 
	reserved02                         :11,	// reserved
	reg_manual_en                      :1 ,	// 16
	reserved03                         :3 ,	// reserved
	reg_manual_mode2                   :2 ,	// 21:20
	reg_manual_mode1                   :2 ,	// 23:22
	reg_div_position                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9003288L ipc_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th                    :8 ,	// 7:0
	reg_fmd_ratio_th                   :8 ,	// 15:8
	reg_fmd_max_th                     :8 ,	// 23:16
	reg_fmd_min_th                     :8 ;	// 31:24
}PE_O18_IPC_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc900328cL ipc_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lockcnt_en                     :1 ,	// 0 
	reserved                           :1 ,	// 1 
	reg_lock_speed                     :6 ,	// 7:2
	reg_lockcnt_th                     :8 ,	// 15:8
	reg_same_th                        :8 ,	// 23:16
	reg_still_frame_limit              :8 ;	// 31:24
}PE_O18_IPC_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9003290L ipc_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_3_2_detect_en                  :1 ,	// 0 
	reg_3_2_detect_only                :1 ,	// 1 
	reg_3_2_lockcnt_255_en             :1 ,	// 2 
	reg_3_2_pndiff_disable             :1 ,	// 3 
	reg_hd_mode                        :1 ,	// 4 
	reserved01                         :3 ,	// reserved
	reg_3_2_pndiff_th                  :8 ,	// 15:8
	reg_3_2_pn_ratio_max_th            :8 ,	// 23:16
	reg_3_2_pn_ratio_min_th            :8 ;	// 31:24
}PE_O18_IPC_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9003294L ipc_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th2                   :8 ,	// 7:0
	reg_still_prev_ratio               :8 ,	// 15:8
	reg_lock_reducer                   :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	reg_badedit_protect                :1 ;	// 31
}PE_O18_IPC_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9003298L ipc_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_toosmall_en                    :1 ,	// 0 
	reg_toosmall_min                   :7 ,	// 7:1
	reg_toosmall_max                   :8 ,	// 15:8
	reg_pndiff_disable                 :1 ;	// 16
}PE_O18_IPC_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc900329cL ipc_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fend_position                  :11,	// 10:0
	reserved01                         :1 ,	// reserved
	cr_sc_length                       :3 ,	// 14:12
	reserved02                         :11,	// reserved
	cr_vmc_dir                         :3 ,	// 28:26
	reserved03                         :2 ,	// reserved
	cr_vmc_en                          :1 ;	// 31
}PE_O18_IPC_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90032a0L ipc_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_diff_gain                   :4 ,	// 3:0
	reg_hv_add_gain                    :4 ,	// 7:4
	reg_v_motion_gain                  :4 ,	// 11:8
	reg_h_motion_gain                  :4 ,	// 15:12
	reg_cc_diff_gain                   :4 ;	// 19:16
}PE_O18_IPC_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90032a4L ipc_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	n1b_motion_gain_y0                 :8 ,	// 7:0
	n1b_motion_gain_x0                 :8 ,	// 15:8
	n1b_motion_gain_y1                 :8 ,	// 23:16
	n1b_motion_gain_x1                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90032a8L ipc_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	n1b_variance_gain_y0               :8 ,	// 7:0
	n1b_variance_gain_x0               :8 ,	// 15:8
	n1b_variance_gain_y1               :8 ,	// 23:16
	n1b_variance_gain_x1               :8 ;	// 31:24
}PE_O18_IPC_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90032acL ipc_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_use_tnr_mv                 :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	reg_cr_hmc_y_th                    :4 ,	// 11:8
	reserved02                         :4 ,	// reserved
	max_penalty                        :8 ,	// 23:16
	min_penalty                        :8 ;	// 31:24
}PE_O18_IPC_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90032b0L ipc_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_min_diff_th                    :8 ,	// 7:0
	reg_edi_va_blend_mul               :10,	// 17:8
	reserved01                         :2 ,	// reserved
	reg_edi_va_protect_mul             :10,	// 29:20
	reserved02                         :1 ,	// reserved
	reg_m16_edi_va_blend_en            :1 ;	// 31
}PE_O18_IPC_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90032b4L ipc_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_max_va_diff_th                 :8 ,	// 7:0
	reg_max_edi_diff_th                :8 ,	// 15:8
	reg_edi_va_protect_min             :8 ,	// 23:16
	reg_edi_va_blend_min               :8 ;	// 31:24
}PE_O18_IPC_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90032b8L ipc_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2d_top_lut_y0                  :8 ,	// 7:0
	reg_2d_top_lut_x0                  :8 ,	// 15:8
	reg_2d_top_lut_y1                  :8 ,	// 23:16
	reg_2d_top_lut_x1                  :8 ;	// 31:24
}PE_O18_IPC_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc90032bcL ipc_ctrl_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_enable_1                    :1 ,	// 0 
	cr_lock_th_1                       :7 ,	// 7:1
	cr_lr_ratio_th_1                   :8 ,	// 15:8
	cr_hmc_expend_1                    :3 ,	// 18:16
	cr_lr_ratio_check_en_1             :1 ,	// 19
	cr_robustness_1                    :4 ,	// 23:20
	cr_center_weight_1                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc90032c0L ipc_ctrl_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_enable_2                    :1 ,	// 0 
	cr_lock_th_2                       :7 ,	// 7:1
	cr_lr_ratio_th_2                   :8 ,	// 15:8
	cr_hmc_expend_2                    :3 ,	// 18:16
	cr_lr_ratio_check_en_2             :1 ,	// 19
	cr_robustness_2                    :4 ,	// 23:20
	cr_center_weight_2                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc90032c4L ipc_ctrl_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt_th_0                      :12,	// 11:0
	line_cnt_th_1                      :12;	// 23:12
}PE_O18_IPC_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc90032c8L ipc_ctrl_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_n1b_limit                       :9 ,	// 8:0
	reserved01                         :3 ,	// reserved
	cr_n1b_resolution                  :3 ,	// 14:12
	reserved02                         :9 ,	// reserved
	cr_pre_sc_th                       :8 ;	// 31:24
}PE_O18_IPC_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc90032ccL ipc_ctrl_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_y0                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	cr_hmc_text_rgn_x0                 :11;	// 26:16
}PE_O18_IPC_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc90032d0L ipc_ctrl_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_y1                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	cr_hmc_text_rgn_x1                 :11;	// 26:16
}PE_O18_IPC_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc90032d4L ipc_ctrl_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_en                 :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	cr_hmc_text_rgn_sad_max            :8 ,	// 15:8
	cr_hmc_text_rgn_sad_min            :8 ;	// 23:16
}PE_O18_IPC_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc90032e0L mmd_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mmd_vtap_yy                        :4 ,	// 3:0
	mmd_htap_yy                        :2 ,	// 5:4
	reserved01                         :2 ,	// reserved
	mmd_vtap_cc                        :4 ,	// 11:8
	mmd_htap_cc                        :2 ,	// 13:12
	reserved02                         :2 ,	// reserved
	reg_chroma_mmd_en                  :1 ;	// 16
}PE_O18_MMD_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90032f0L ipc_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_cubic_coef0                    :8 ,	// 7:0
	reg_cubic_coef1                    :8 ,	// 15:8
	reg_va_blending_ctrl_lv1           :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_va_blending_ctrl_lv2           :3 ,	// 22:20
	reserved02                         :1 ,	// reserved
	reg_va_blending_ctrl_lv3           :3 ,	// 26:24
	reserved03                         :1 ,	// reserved
	reg_va_blending_ctrl_lv4           :3 ;	// 30:28
}PE_O18_IPC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90032f4L ipc_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_va_cubic                       :1 ,	// 0 
	reg_boundary_window                :1 ,	// 1 
	reg_force_va                       :1 ,	// 2 
	reg_half_pel_va                    :1 ,	// 3 
	reg_dir_med_tap                    :2 ,	// 5:4
	reg_diff_med_tap                   :2 ,	// 7:6
	reg_va_blending_ctrl1              :3 ,	// 10:8
	reg_wide_angle_protection_1        :1 ,	// 11
	reg_va_blending_ctrl2              :3 ,	// 14:12
	reg_wide_angle_protection_2        :1 ,	// 15
	reg_errs_chroma_blend_coef         :8 ,	// 23:16
	reg_strong_global_th               :6 ,	// 29:24
	narrow_angle_week                  :1 ,	// 30
	narrow_angle_protection            :1 ;	// 31
}PE_O18_IPC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90032f8L ipc_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_vmc_v_diff_max                  :8 ,	// 7:0
	cr_vmc_v_diff_protect_mul          :8 ,	// 15:8
	es_err_value                       :8 ,	// 23:16
	et_err_value                       :8 ;	// 31:24
}PE_O18_IPC_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90032fcL ipc_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_enable_0                    :1 ,	// 0 
	cr_lock_th_0                       :7 ,	// 7:1
	cr_lr_ratio_th_0                   :8 ,	// 15:8
	cr_hmc_expend_0                    :3 ,	// 18:16
	cr_lr_ratio_check_en_0             :1 ,	// 19
	cr_robustness_0                    :4 ,	// 23:20
	cr_center_weight_0                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9003300L ipc_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_noise_en                        :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	cr_noise_th                        :8 ,	// 15:8
	cr_gds_resolution                  :2 ,	// 17:16
	reserved02                         :2 ,	// reserved
	cr_hmc_h_range                     :12;	// 31:20
}PE_O18_IPC_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc9003304L ipc_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vdiff_en                       :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	reg_vdiff_th                       :8 ,	// 15:8
	reg_hmc_err_max                    :8 ,	// 23:16
	reg_hmc_err_min                    :8 ;	// 31:24
}PE_O18_IPC_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc9003308L ipc_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_fmd_check_en                    :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	cr_fmd_ath                         :8 ,	// 15:8
	reserved02                         :8 ,	// reserved
	cr_fmd_ratio_th                    :8 ;	// 31:24
}PE_O18_IPC_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc900330cL ipc_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	chroma_st_flt_ctrl_x0              :8 ,	// 7:0
	chroma_st_flt_ctrl_x1              :8 ,	// 15:8
	luma_st_flt_ctrl_x0                :8 ,	// 23:16
	luma_st_flt_ctrl_x1                :8 ;	// 31:24
}PE_O18_IPC_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc9003310L ipc_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_bonus_es_en                :1 ,	// 0 
	reg_hmc_bonus_et_en                :1 ,	// 1 
	reserved01                         :6 ,	// reserved
	reg_hmc_bonus_es                   :8 ,	// 15:8
	reg_hmc_bonus_th                   :8 ,	// 23:16
	reg_hmc_bonus_et                   :8 ;	// 31:24
}PE_O18_IPC_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc9003314L ipc_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hmc_alpha_th                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	hmc_flt_ctrl_x0                    :8 ,	// 23:16
	hmc_st_flt_ctrl_x1                 :8 ;	// 31:24
}PE_O18_IPC_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc9003318L ipc_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vmc_motion_th                  :8 ,	// 7:0
	reg_vmc_debug                      :1 ,	// 8 
	reg_vmc_en                         :1 ,	// 9 
	reg_vmc_still_check                :1 ,	// 10
	reserved01                         :1 ,	// reserved
	reg_vmc_mul                        :2 ,	// 13:12
	reg_vmc_out_mul                    :2 ,	// 15:14
	reg_vmc_protect_th                 :8 ,	// 23:16
	reg_protection_en                  :1 ,	// 24
	reg_2filed_check_en                :1 ,	// 25
	reg_vmc_tnrmotion_dis              :1 ,	// 26
	reserved02                         :1 ,	// reserved
	reg_vmc_mm_ratio                   :4 ;	// 31:28
}PE_O18_IPC_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc900331cL ipc_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_toosmall_en                    :1 ,	// 0 
	reg_toosmall_min                   :7 ,	// 7:1
	reg_toosmall_max                   :8 ,	// 15:8
	reg_pndiff_disable                 :1 ;	// 16
}PE_O18_IPC_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc9003320L ipc_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_errt_y2                       :8 ,	// 7:0
	tava_errt_x2                       :8 ,	// 15:8
	tava_errt_y3                       :8 ,	// 23:16
	tava_errt_x3                       :8 ;	// 31:24
}PE_O18_IPC_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc9003324L ipc_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_errt_y0                       :8 ,	// 7:0
	tava_errt_x0                       :8 ,	// 15:8
	tava_errt_y1                       :8 ,	// 23:16
	tava_errt_x1                       :8 ;	// 31:24
}PE_O18_IPC_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc9003328L ipc_status_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_v_count_d                     :16,	// 15:0
	r_nc_v_count_d                     :16;	// 31:16
}PE_O18_IPC_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc900332cL ipc_status_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_nc_same_d                     :16,	// 15:0
	r_pn_v_count_d                     :16;	// 31:16
}PE_O18_IPC_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003330L ipc_status_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :6 ,	// 5:0
	r_fmd_32_min_th_flag_d             :1 ,	// 6 
	r_fmd_32_max_th_flag_d             :1 ,	// 7 
	r_fmd_still_limit_flag_d           :1 ,	// 8 
	r_fmd_still_pn_th2_flag_d          :1 ,	// 9 
	r_fmd_still_pn_th_flag_d           :1 ,	// 10
	r_fmd_still_prev_ratio_flag_d      :1 ,	// 11
	r_fmd_bigger_flag_d                :1 ,	// 12
	r_fmd_smaller_flag_d               :1 ,	// 13
	r_fmd_3_2_fmd_comb_mode_d          :2 ,	// 15:14
	r_pn_diff_count_d                  :16;	// 31:16
}PE_O18_IPC_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc9003334L ipc_status_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_inv_inversed_cnt                 :16,	// 15:0
	r_inv_original_cnt                 :16;	// 31:16
}PE_O18_IPC_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003338L ipc_status_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IPC_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc900333cL ipc_status_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IPC_STATUS_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003340L tpd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_show_scale                     :3 ,	// 2:0
	reg_bbd_show                       :1 ,	// 3 
	reg_show_bar_1                     :1 ,	// 4 
	reg_show_bar_2                     :1 ,	// 5 
	reg_show_bar_3                     :1 ,	// 6 
	reg_bar1_data_mux                  :2 ,	// 8:7
	reg_bar2_data_mux                  :2 ,	// 10:9
	reg_bar3_data_mux                  :2 ,	// 12:11
	reg_hist0_data_mux                 :4 ,	// 16:13
	reg_hist1_data_mux                 :4 ,	// 20:17
	reg_hist2_data_mux                 :4 ,	// 24:21
	reg_hist0_win_sel                  :2 ,	// 26:25
	reg_hist1_win_sel                  :2 ,	// 28:27
	reg_hist2_win_sel                  :2 ,	// 30:29
	hist_rd_en                         :1 ;	// 31
}PE_O18_TPD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003344L tpd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wina_x0                            :12,	// 11:0
	reserved01                         :3 ,	// reserved
	reg_wina_hen                       :1 ,	// 15
	wina_y0                            :12,	// 27:16
	reserved02                         :3 ,	// reserved
	reg_wina_ven                       :1 ;	// 31
}PE_O18_TPD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003348L tpd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	wina_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	wina_y1                            :12,	// 27:16
	reserved02                         :2 ,	// reserved
	reg_hist_hsv_hsl_sel               :1 ,	// 30
	reg_hist_vscaling_en               :1 ;	// 31
}PE_O18_TPD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900334cL tpd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winb_x0                            :12,	// 11:0
	reserved01                         :3 ,	// reserved
	reg_winb_hen                       :1 ,	// 15
	winb_y0                            :12,	// 27:16
	reserved02                         :3 ,	// reserved
	reg_winb_ven                       :1 ;	// 31
}PE_O18_TPD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003350L tpd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winb_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winb_y1                            :12;	// 27:16
}PE_O18_TPD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003354L tpd_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winc_x0                            :12,	// 11:0
	reserved01                         :3 ,	// reserved
	reg_winc_hen                       :1 ,	// 15
	winc_y0                            :12,	// 27:16
	reserved02                         :3 ,	// reserved
	reg_winc_ven                       :1 ;	// 31
}PE_O18_TPD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003358L tpd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winc_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winc_y1                            :12;	// 27:16
}PE_O18_TPD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900335cL tpd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_y                        :10,	// 9:0
	reg_force_y_max_th                 :10,	// 19:10
	reg_force_y_min_th                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_y_enable                 :1 ;	// 31
}PE_O18_TPD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003360L tpd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cb                       :10,	// 9:0
	reg_force_cb_max_th                :10,	// 19:10
	reg_force_cb_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cb_enable                :1 ;	// 31
}PE_O18_TPD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003364L tpd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cr                       :10,	// 9:0
	reg_force_cr_max_th                :10,	// 19:10
	reg_force_cr_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cr_enable                :1 ;	// 31
}PE_O18_TPD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003368L tpd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 
	hist_pixel_count                   :22;	//21:0
}PE_O18_TPD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc900336cL clc_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_lcount_enable                   :1 ,	// 0 
	cl_lcnt_mode                       :2 ,	// 2:1
	cl_scene_change_enable             :1 ,	// 3 
	cl_scene_change_mode               :1 ,	// 4 
	cl_scene_change_manual             :1 ,	// 5 
	cl_lcnt_th                         :4 ,	// 9:6
	cl_plus_lcount                     :3 ,	// 12:10
	cl_minus_lcount                    :2 ,	// 14:13
	cl_scene_change_protect            :1 ,	// 15
	reserved01                         :4 ,	// reserved
	cl_tearing_pt_th2                  :12;	// 31:20
}PE_O18_CLC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003370L bbd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_en                         :1 ,	// 0 
	reg_hys_mode                       :5 ,	// 5:1
	reg_op_mode                        :1 ,	// 6 
	reserved01                         :1 ,	// reserved
	reg_cnt_th                         :8 ,	// 15:8
	reg_diff_th                        :8 ,	// 23:16
	reg_bbd_mux                        :3 ,	// 26:24
	reg_apl_mux                        :3 ,	// 29:27
	reg_apl_win_sel                    :2 ;	// 31:30
}PE_O18_BBD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003374L bbd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O18_BBD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003378L bbd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O18_BBD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900337cL bbd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O18_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003380L bbd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O18_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003384L apl_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_g_s_apl                          :10,	// 9:0
	cb_b_s_apl                         :10,	// 19:10
	cr_r_s_apl                         :10;	// 29:20
}PE_O18_APL_STAT_00_T;
/*-----------------------------------------------------------------------------
		0xc9004388L pe1_fsw_ctrl_00 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd0_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd0_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd0_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd0_hue_bin_9                      : 8 ;  // 31:24
} PE_O18_PE1_FSW_CTRL_00_T;

/*-----------------------------------------------------------------------------
		0xc900438cL pe1_fsw_ctrl_01 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd1_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd1_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd1_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd1_hue_bin_9                      : 8 ;  // 31:24
} PE_O18_PE1_FSW_CTRL_01_T;

/*-----------------------------------------------------------------------------
                             0xc9003390L tpd_hist_ai_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hif_hist_address                   :5 ,	// 4:0
	reserved01                         :7 ,	// reserved
	hif_hist_ai                        :1 ,	// 12
	reg_read_hist_sel                  :2 ,	// 14:13
	hif_hist_enable                    :1 ,	// 15
	reserved02                         :12,	// reserved
	hist_rd_available                  :1 ,	// 28
	reserved03                         :1 ,	//reserved
	hist_rd_en                         :1 ,	//30
	hist_read_done                     :1 ;	// 31
}PE_O18_TPD_HIST_AI_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9003394L tpd_hist_ai_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status                        :22;	// 21:0
}PE_O18_TPD_HIST_AI_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9003398L lvcrtl_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	y_offset                           :10,	// 13:4
	reserved02                         :2 ,	// reserved
	center_position                    :8 ,	// 23:16
	y_gain                             :8 ;	// 31:24
}PE_O18_LVCRTL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90033a0L tnr_status_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc90033a4L tnr_status_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc90033a8L tnr_status_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc90033acL tnr_status_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc90033c0L tnr_reset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gmv_rst                        :1 ,	// 0 
	reg_bmv_rst                        :1 ,	// 1 
	reg_me_rst                         :1 ,	// 2 
	reg_mc_rst                         :1 ,	// 3 
	reg_ma_rst                         :1 ;	// 4 
}PE_O18_TNR_RESET_T;
/*-----------------------------------------------------------------------------
                             0xc90033d0L tnr_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :2 ,	// reserved
	reg_a_normalize_en                 :1 ,	// 2 
	reg_t_normalize_en                 :1 ,	// 3 
	reg_t_cut_resolution               :2 ,	// 5:4
	reg_ne_normalize_en                :1 ,	// 6 
	reserved02                         :9 ,	// reserved
	reg_cross_th_ne                    :8 ,	// 23:16
	reg_cross_th                       :8 ;	// 31:24
}PE_O18_TNR_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc90033d4L tnr_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mul_base_t                     :8 ,	// 7:0
	reg_mul_base_e                     :8 ;	// 15:8
}PE_O18_TNR_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90033d8L tnr_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_a_lut_edge_y0                  :8 ,	// 7:0
	reg_a_lut_edge_x0                  :8 ,	// 15:8
	reg_a_lut_edge_y1                  :8 ,	// 23:16
	reg_a_lut_edge_x1                  :8 ;	// 31:24
}PE_O18_TNR_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90033dcL tnr_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_a_lut_detail_y0                :8 ,	// 7:0
	reg_a_lut_detail_x0                :8 ,	// 15:8
	reg_a_lut_detail_y1                :8 ,	// 23:16
	reg_a_lut_detail_x1                :8 ;	// 31:24
}PE_O18_TNR_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90033e0L tnr_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_t_lut_edge_y0                  :8 ,	// 7:0
	reg_t_lut_edge_x0                  :8 ,	// 15:8
	reg_t_lut_edge_y1                  :8 ,	// 23:16
	reg_t_lut_edge_x1                  :8 ;	// 31:24
}PE_O18_TNR_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90033e4L tnr_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_t_lut_detail_y0                :8 ,	// 7:0
	reg_t_lut_detail_x0                :8 ,	// 15:8
	reg_t_lut_detail_y1                :8 ,	// 23:16
	reg_t_lut_detail_x1                :8 ;	// 31:24
}PE_O18_TNR_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90033e8L tnr_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_minmax_y0                 :8 ,	// 7:0
	reg_edge_minmax_x0                 :8 ,	// 15:8
	reg_edge_minmax_y1                 :8 ,	// 23:16
	reg_edge_minmax_x1                 :8 ;	// 31:24
}PE_O18_TNR_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90033ecL tnr_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_detail_minmax_y0               :8 ,	// 7:0
	reg_detail_minmax_x0               :8 ,	// 15:8
	reg_detail_minmax_y1               :8 ,	// 23:16
	reg_detail_minmax_x1               :8 ;	// 31:24
}PE_O18_TNR_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90033f0L tnr_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sel_ne_type                    :2 ,	// 1:0
	reg_sel_re_type                    :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	reg_sel_at_mode                    :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_hist_xscale                    :3 ,	// 10:8
	reserved03                         :1 ,	// reserved
	reg_hist_yscale                    :2 ,	// 13:12
	reserved04                         :2 ,	// reserved
	reg_th_atmap                       :8 ,	// 23:16
	reg_th_motion                      :8 ;	// 31:24
}PE_O18_TNR_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc9003400L tnr_ne_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	valid_cnt                          :16;	// 15:0
}PE_O18_TNR_NE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003404L tnr_ne_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_1                             :16,	// 15:0
	hist_0                             :16;	// 31:16
}PE_O18_TNR_NE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003408L tnr_ne_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_3                             :16,	// 15:0
	hist_2                             :16;	// 31:16
}PE_O18_TNR_NE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900340cL tnr_ne_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_5                             :16,	// 15:0
	hist_4                             :16;	// 31:16
}PE_O18_TNR_NE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003410L tnr_ne_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_7                             :16,	// 15:0
	hist_6                             :16;	// 31:16
}PE_O18_TNR_NE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003414L tnr_ne_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_9                             :16,	// 15:0
	hist_8                             :16;	// 31:16
}PE_O18_TNR_NE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003418L tnr_ne_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_11                            :16,	// 15:0
	hist_10                            :16;	// 31:16
}PE_O18_TNR_NE_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900341cL tnr_ne_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_13                            :16,	// 15:0
	hist_12                            :16;	// 31:16
}PE_O18_TNR_NE_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003420L tnr_ne_stat_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_15                            :16,	// 15:0
	hist_14                            :16;	// 31:16
}PE_O18_TNR_NE_STAT_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003430L tnr_frc_rmv_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	frc_rmv_indir_addr                 :7 ,	// 6:0
	reserved01                         :5 ,	// reserved
	frc_rmv_ai_enable                  :1 ,	// 12
	reserved02                         :2 ,	// reserved
	frc_rmv_load                       :1 ;	// 15
}PE_O18_TNR_FRC_RMV_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003434L tnr_frc_rmv_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	frc_rmv_indir_data0;	// 31:0
}PE_O18_TNR_FRC_RMV_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003440L tnr_decon_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003444L tnr_decon_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003448L tnr_decon_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900344cL tnr_decon_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003450L tnr_decon_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003454L tnr_decon_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003458L tnr_decon_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc900345cL tnr_decon_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003460L tnr_decon_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003464L tnr_decon_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003468L tnr_decon_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900346cL tnr_decon_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_DECON_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003480L nd_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	chroma_st_flt_ctrl_x0              : 8 ,  //  7: 0     
	chroma_st_flt_ctrl_x1              : 8 ,  // 15: 8     
	luma_st_flt_ctrl_x0                : 8 ,  // 23:16     
	luma_st_flt_ctrl_x1                : 8 ;  // 31:24     
}PE_O18_ND_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003484L nd_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	motion_x_tearing_gain              : 8 ,  //  7: 0     
	motion_gain                        : 8 ,  // 15: 8     
	cr_lr_ratio_check_en_0             : 1 ;  // 16     
}PE_O18_ND_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003488L nd_fsw_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_luma_mode                       :2 ,	// 1:0
	reserved01                         :1 ,	// reserved
	cr_n1_cc_blend_en                  :1 ,	// 3 
	cr_chroma_mode                     :2 ,	// 5:4
	cr_integer_edi                     :1 ,	// 6 
	cr_chroma_edi                      :1 ,	// 7 
	cr_st_2d_v_flt_range2              :4 ,	// 11:8
	cr_st_2d_v_flt_range               :4 ,	// 15:12
	cr_ori_3d_blur_y                   :2 ,	// 17:16
	cr_ori_3d_blur_c                   :2 ,	// 19:18
	cr_tava_v_edge_adap                :1 ,	// 20
	cr_tava_debug_mode                 :1 ,	// 21
	cr_tava_st_adap                    :1 ,	// 22
	cr_tava_en                         :1 ,	// 23
	cr_hmc_force_fmd                   :1 ,	// 24
	cr_st_2d_v_flt_en                  :1 ,	// 25
	cr_clc_fmd_off                     :1 ,	// 26
	cr_chroma_tava_only                :1 ,	// 27
	cr_film_auto_gain                  :1 ,	// 28
	cr_film_apply_c                    :1 ,	// 29
	cr_film_apply_y                    :1 ,	// 30
	cr_film_mode_enable                :1 ;	// 31
}PE_O18_ND_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900348cL nd_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_ND_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003490L tnr_etc_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_y0                             :12,	// 11:0
	reserved01                         :4 ,	// reserved
	win_x0                             :13,	// 28:16
	reserved02                         :1 ,	// reserved
	win_mode                           :1 ,	// 30
	win_en                             :1 ;	// 31
}PE_O18_TNR_ETC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003494L tnr_etc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_y1                             :12,	// 11:0
	reserved01                         :4 ,	// reserved
	win_x1                             :13,	// 28:16
	reserved02                         :2 ,	// reserved
	win_tnrw_en                        :1 ;	// 31
}PE_O18_TNR_ETC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003498L tnr_etc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	minfo_tnr_rd_m_delay               :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	minfo_tnr_rd_mv_delay              :4 ,	// 11:8
	reserved02                         :4 ,	// reserved
	minfo_tnr_wr_m_delay               :4 ,	// 19:16
	minfo_lstart_delay                 :4 ,	// 23:20
	minfo_clc_offset                   :2 ,	// 25:24
	reserved03                         :2 ,	// reserved
	minfo_tnr_wr_mv_delay              :4 ;	// 31:28
}PE_O18_TNR_ETC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900349cL tnr_etc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TNR_ETC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90034a0L tnr_ctrl_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_mc_ctrl_pt_y0              :8 ,	// 7:0
	reg_sad_mc_ctrl_pt_x0              :8 ,	// 15:8
	reg_sad_mc_ctrl_pt_y1              :8 ,	// 23:16
	reg_sad_mc_ctrl_pt_x1              :8 ;	// 31:24
}PE_O18_TNR_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc90034a4L tnr_ctrl_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_mc_ctrl_pt_y2              :8 ,	// 7:0
	reg_sad_mc_ctrl_pt_x2              :8 ,	// 15:8
	reg_sad_mc_ctrl_pt_y3              :8 ,	// 23:16
	reg_sad_mc_ctrl_pt_x3              :8 ;	// 31:24
}PE_O18_TNR_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc90034a8L tnr_ctrl_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_abs_mv_ctrl_pt_y0              :8 ,	// 7:0
	reg_abs_mv_ctrl_pt_x0              :8 ,	// 15:8
	reg_abs_mv_ctrl_pt_y1              :8 ,	// 23:16
	reg_abs_mv_ctrl_pt_x1              :8 ;	// 31:24
}PE_O18_TNR_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc90034acL tnr_ctrl_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_abs_mv_ctrl_pt_y2              :8 ,	// 7:0
	reg_abs_mv_ctrl_pt_x2              :8 ,	// 15:8
	reg_abs_mv_ctrl_pt_y3              :8 ,	// 23:16
	reg_abs_mv_ctrl_pt_x3              :8 ;	// 31:24
}PE_O18_TNR_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc90034b0L tnr_ctrl_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_ma_ctrl_pt_y0              :8 ,	// 7:0
	reg_sad_ma_ctrl_pt_x0              :8 ,	// 15:8
	reg_sad_ma_ctrl_pt_y1              :8 ,	// 23:16
	reg_sad_ma_ctrl_pt_x1              :8 ;	// 31:24
}PE_O18_TNR_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc90034b4L tnr_ctrl_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_ma_ctrl_pt_y2              :8 ,	// 7:0
	reg_sad_ma_ctrl_pt_x2              :8 ,	// 15:8
	reg_sad_ma_ctrl_pt_y3              :8 ,	// 23:16
	reg_sad_ma_ctrl_pt_x3              :8 ;	// 31:24
}PE_O18_TNR_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc90034b8L pe0_debug3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mif_prefetch_ctrl                  :8 ;	// 7:0
}PE_O18_PE0_DEBUG3_T;
/*-----------------------------------------------------------------------------
                             0xc90034c0L fbc_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fbc_y_dc_offset_off                :1 ,	// 0:0
	fbc_y_abab_pr_off                  :1 ,	// 1:1
	fbc_y_abab_ls_off                  :1 ,	// 2:2
	fbc_y_aabb_off                     :1 ,	// 3:3
	reserved01                         :4 ,	// reserved
	fbc_y_abba_off                     :1 ,	// 8:8
	fbc_y_dpcm_reset4_off              :1 ,	// 9:9
	fbc_y_abab_th                      :6 ;	// 15:10
}PE_O18_FBC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc90034c4L fbc_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fbc_c_dc_offset_off                :1 ,	// 0:0
	fbc_c_abab_pr_off                  :1 ,	// 1:1
	fbc_c_abab_ls_off                  :1 ,	// 2:2
	fbc_c_aabb_off                     :1 ,	// 3:3
	reserved01                         :4 ,	// reserved
	fbc_c_abba_off                     :1 ,	// 8:8
	fbc_c_dpcm_reset4_off              :1 ,	// 9:9
	fbc_c_abab_th                      :6 ;	// 15:10
}PE_O18_FBC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc90034d0L gfd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_h_th0_a                    :8 ,	// 7:0
	reg_gfd_h_th1_a                    :8 ,	// 15:8
	reg_gfd_h_th0_b                    :8 ,	// 23:16
	reg_gfd_h_th1_b                    :8 ;	// 31:24
}PE_O18_GFD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90034d4L gfd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_s_th                       :8 ,	// 7:0
	reg_gfd_v_th                       :8 ,	// 15:8
	reserved01                         :14,	// reserved
	reg_scale                          :2 ;	// 31:30
}PE_O18_GFD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90034d8L gfd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_a01                  :16,	// 15:0
	reg_gfd_count_a00                  :16;	// 31:16
}PE_O18_GFD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90034dcL gfd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_a11                  :16,	// 15:0
	reg_gfd_count_a10                  :16;	// 31:16
}PE_O18_GFD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90034e0L gfd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_b01                  :16,	// 15:0
	reg_gfd_count_b00                  :16;	// 31:16
}PE_O18_GFD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc90034e4L gfd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_b11                  :16,	// 15:0
	reg_gfd_count_b10                  :16;	// 31:16
}PE_O18_GFD_STAT_03_T;


/*-----------------------------------------------------------------------------
                             0xc9003500L pe0_load                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	// reserved
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_O18_PE0_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9003504L pe0_intr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	intr_enable                        :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	intr_src                           :3 ,	// 6:4
	reserved02                         :1 ,	// reserved
	timer_rst_sel                      :1 ,	// 8 
	reserved03                         :7 ,	// reserved
	intr_line_pos                      :11;	// 26:16
}PE_O18_PE0_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9003508L pe0_status0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	dnr_frame_id                       :8 ,	// 23:16
	pic_init_frame_id                  :4 ;	// 27:24
}PE_O18_PE0_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc900350cL pe0_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt                           :11,	// 10:0
	reserved01                         :5 ,	// reserved
	timer_cnt                          :16;	// 31:16
}PE_O18_PE0_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9003510L pe0_opmode                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_sd_5l_mode_en                  :1 ,	// 8 
	reserved02                         :3 ,	// reserved
	dnr_out_420_vsample_mode           :1 ,	// 12
	dnr_out_cs_type                    :3 ,	// 15:13
	detour_enable                      :1 ,	// 16
	half_rate_en                       :1 ,	// 17
	reserved03                         :2 ,	// reserved
	ibuf_en                            :2 ,	// 21:20
	dnr_out_422_hsample_mode           :1 ,	// 22
	reserved04                         :1 ,	// reserved
	dnr_in_lsb_mode                    :2 ,	// 25:24
	dnr_out_lsb_mode                   :2 ,	// 27:26
	reserved05                         :2 ,	// reserved
	m_run_id                           :2 ;	// 31:30
}PE_O18_PE0_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9003514L pe0_in_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :1 ,	// reserved
	chroma_sampling_type               :3 ,	// 15:13
	vsize                              :12;	// 27:16
}PE_O18_PE0_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9003518L pe0_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O18_PE0_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc900351cL pe0_out_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O18_PE0_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9003520L win_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O18_WIN_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003524L win_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O18_WIN_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003528L win_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y0                                 :12,	// 27:16
	ac_bnr_feature_cal_mode            :2 ;	// 29:28
}PE_O18_WIN_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900352cL win_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O18_WIN_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9003530L cup_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bypass                             :1 ,	// 0 
	reg_v_upsample_en                  :1 ,	// 1 
	reg_h_upsample_en                  :1 ,	// 2 
	reg_sd_mode                        :1 ;	// 3 
}PE_O18_CUP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003534L cup_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ,	// 0 
	bypass                             :1 ,	// 1 
	reg_v_upsample_en                  :1 ,	// 2 
	reg_h_upsample_en                  :1 ;	// 3 
}PE_O18_CUP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003538L cup_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_CUP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9003550L _3dfd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	aw_offset_x                        :8 ,	// 7:0
	aw_offset_y                        :8 ,	// 15:8
	cb_th1                             :8 ,	// 23:16
	cb_th2                             :8 ;	// 31:24
}PE_O18__3DFD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003554L _3dfd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cc_th1                             :8 ,	// 7:0
	cc_th2                             :8 ,	// 15:8
	ll_th1                             :8 ,	// 23:16
	ll_th2                             :8 ;	// 31:24
}PE_O18__3DFD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003558L _3dfd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pt_th                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	sstb_th                            :8 ,	// 23:16
	debug_mode                         :3 ,	// 26:24
	reserved02                         :1 ,	// reserved
	div_mode                           :1 ;	// 28
}PE_O18__3DFD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900355cL _3dfd_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	small_delta_th                     :19,	// 18:0
	reserved01                         :5 ,	// reserved
	small_delta_en                     :1 ;	// 24
}PE_O18__3DFD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003560L _3dfd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cb_count                           :16,	// 15:0
	cc_count                           :16;	// 31:16
}PE_O18__3DFD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003564L _3dfd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ll_count                           :16,	// 15:0
	trid_format                        :4 ;	// 19:16
}PE_O18__3DFD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003568L _3dfd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	delta_ss_h                         :23;	// 22:0
}PE_O18__3DFD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc900356cL _3dfd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	delta_ss_v                         :23;	// 22:0
}PE_O18__3DFD_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003570L _3dfd_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	delta_tb_v                         :23;	// 22:0
}PE_O18__3DFD_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003574L _3dfd_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	delta_tb_h                         :23;	// 22:0
}PE_O18__3DFD_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003578L _3dfd_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ss_ratio                           :23;	// 22:0
}PE_O18__3DFD_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc900357cL _3dfd_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tb_ratio                           :23;	// 22:0
}PE_O18__3DFD_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003580L vfilter_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_glb_tearing_th                 :8 ,	// 7:0
	reg_glb_mode_th                    :4 ,	// 11:8
	reg_tearing_strength               :1 ,	// 12
	reg_glb_tearing_cnt_normal         :3 ,	// 15:13
	reg_vf_a_th                        :8 ,	// 23:16
	reserved01                         :6 ,	// reserved
	reg_vflt_force_en                  :1 ,	// 30
	reg_vflt_en                        :1 ;	// 31
}PE_O18_VFILTER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9003584L vfilter_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vflt_debug_en                  :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_fmd_mode                       :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_glb_mode                       :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	reg_glb_mode_fw_en                 :1 ,	// 12
	reserved04                         :3 ,	// reserved
	reg_glb_vflt_en                    :1 ,	// 16
	reserved05                         :3 ,	// reserved
	reg_fmd_vflt_en                    :1 ,	// 20
	reserved06                         :3 ,	// reserved
	reg_fmd_tearing_cnt_en             :1 ,	// 24
	reserved07                         :3 ,	// reserved
	reg_fmd_motion_en                  :1 ;	// 28
}PE_O18_VFILTER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9003588L vfilter_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_vflt_en                    :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_hmc_tearing_cnt_en             :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_hmc_motion_en                  :1 ,	// 8 
	reserved03                         :3 ,	// reserved
	reg_loc_vflt_en                    :1 ,	// 12
	reserved04                         :3 ,	// reserved
	reg_loc_tearing_cnt_en             :1 ,	// 16
	reserved05                         :3 ,	// reserved
	reg_loc_motion_en_                 :1 ,	// 20
	reserved06                         :3 ,	// reserved
	reg_alpha_sel_mode                 :2 ,	// 25:24
	reserved07                         :2 ,	// reserved
	reg_alpha_sel_mode_en              :2 ;	// 29:28
}PE_O18_VFILTER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc900358cL reg_cti_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cti_en                             :1 ,	// 0 
	cti_clipping_mode                  :1 ,	// 1 
	cti_pre_flt_mode                   :1 ,	// 2 
	cti_tap                            :2 ,	// 4:3
	reserved01                         :3 ,	// reserved
	cti_gain                           :8 ,	// 15:8
	cti_debug_mode                     :3 ;	// 18:16
}PE_O18_REG_CTI_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003590L reg_cti_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cti_coring_th0                     :8 ,	// 7:0
	cti_coring_th1                     :8 ,	// 15:8
	cti_coring_smooth                  :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_cti_tap2                       :2 ;	// 21:20
}PE_O18_REG_CTI_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003594L dnr_max_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dnr_max_enable                 :1 ,	// 0 
	reg_ifc_max_enable                 :1 ,	// 1 
	reg_dnr_ifc_sel                    :1 ,	// 2 
	reg_decon_max_sum_sel              :1 ,	// 3 
	reg_decon_ori_sel                  :1 ,	// 4 
	reg_decon_en                       :1 ,	// 5 
	reserved01                         :2 ,	// reserved
	reg_max_dbg_en                     :1 ,	// 8 
	reg_dnr_motion_sel                 :1 ,	// 9 
	reg_tnr_decon_en                   :1 ,	// 10
	reserved02                         :5 ,	// reserved
	reg_win_en                         :1 ,	// 16
	reg_bdr_en                         :1 ,	// 17
	reg_win_inout                      :1 ,	// 18
	reserved03                         :3 ,	// reserved
	reg_motion_bit_ctrl                :3 ,	// 24:22
	reg_delta_ifc_th                   :7 ;	// 31:25
}PE_O18_DNR_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9003598L dnr_dbar_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_en                         :1 ,	// 0 
	reg_show_f3d                       :1 ,	// 1 
	reg_show_bnr                       :1 ,	// 2 
	reg_f3d_mode                       :1 ,	// 3 
	reg_acness_or_acness_gain          :1 ;	// 4 
}PE_O18_DNR_DBAR_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900359cL reg_c420_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_detect_level_th                :10;	// 25:16
}PE_O18_REG_C420_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90035a0L mnr_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mnr_enable                     :1 ,	// 0 
	reg_mnr_debug                      :1 ,	// 1 
	reg_mnr_mmd_chroma_en              :1 ,	// 2 
	reg_mnr_chroma_en                  :1 ,	// 3 
	reg_h_expand                       :2 ,	// 5:4
	reg_sel_mmd                        :2 ,	// 7:6
	reg_mnr_master_gain                :8 ,	// 15:8
	reg_snr_th                         :8 ,	// 23:16
	reg_th_max                         :8 ;	// 31:24
}PE_O18_MNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90035a4L mnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_y_max                      :8 ,	// 7:0
	reg_mmd_y_min                      :8 ,	// 15:8
	reg_mmd_x_max                      :8 ,	// 23:16
	reg_mmd_x_min                      :8 ;	// 31:24
}PE_O18_MNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90035a8L mnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mnr_debug_mode                 :4 ,	// 3:0
	reg_mnr_debug_en                   :1 ,	// 4 
	reserved01                         :19,	// reserved
	reg_equal_snr_th                   :8 ;	// 31:24
}PE_O18_MNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90035acL mnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_sel                       :1 ,	// 0 
	reg_pattern_en                     :1 ,	// 1 
	reserved01                         :6 ,	// reserved
	reg_pattern_th                     :8 ,	// 15:8
	reg_equal_th                       :8 ,	// 23:16
	reg_mmd_scale                      :8 ;	// 31:24
}PE_O18_MNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90035b0L mnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_fil_x_3                    :8 ,	// 7:0
	reg_mmd_fil_x_2                    :8 ,	// 15:8
	reg_mmd_fil_x_1                    :8 ,	// 23:16
	reg_mmd_fil_x_0                    :8 ;	// 31:24
}PE_O18_MNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90035b4L mnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_fil_y_3                    :8 ,	// 7:0
	reg_mmd_fil_y_2                    :8 ,	// 15:8
	reg_mmd_fil_y_1                    :8 ,	// 23:16
	reg_mmd_fil_y_0                    :8 ;	// 31:24
}PE_O18_MNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90035b8L detail_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_detail_max              :8 ,	// 7:0
	reg_bnr_ac_detail_min              :8 ,	// 15:8
	reg_bnr_diff_l                     :8 ,	// 23:16
	reg_bnr_diff_p                     :8 ;	// 31:24
}PE_O18_DETAIL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90035bcL dc_bnr_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_bnr_enable                  :1 ,	// 0 
	reg_dc_blur_debug_mode             :1 ,	// 1 
	reg_dc_blur_sel                    :2 ,	// 3:2
	reg_dc_output_debug_mode           :4 ,	// 7:4
	reg_en_obj_amf_ctrl                :1 ,	// 8 
	reserved01                         :4 ,	// reserved
	reg_obj_gain_mul                   :2 ,	// 14:13
	reg_obj_gain_en                    :1 ,	// 15
	reg_dc_motion_max                  :8 ,	// 23:16
	reg_dc_motion_min                  :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90035c0L dc_bnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_manual_fil_motion_gain         :8 ,	// 15:8
	reg_var_chroma_en                  :1 ,	// 16
	reg_fil_manual_en                  :1 ,	// 17
	reg_dc_pattern_en                  :1 ,	// 18
	reg_luma_gain_en                   :1 ,	// 19
	reg_var_v_gain                     :4 ,	// 23:20
	reg_var_h_gain                     :4 ,	// 27:24
	reg_var_cut_resolution             :4 ;	// 31:28
}PE_O18_DC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90035c4L dc_bnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_var_en                      :1 ,	// 0 
	reg_dc_motion_en                   :1 ,	// 1 
	reg_dc_protection_en               :1 ,	// 2 
	reserved01                         :7 ,	// reserved
	reg_dc_bnr_mastergain              :6 ,	// 15:10
	reg_dc_bnr_chromagain              :8 ,	// 23:16
	reg_dc_protection_th               :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90035c8L dc_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_bnr_var_th3                 :8 ,	// 7:0
	reg_dc_bnr_var_th2                 :8 ,	// 15:8
	reg_dc_bnr_var_th1                 :8 ,	// 23:16
	reg_dc_bnr_var_th0                 :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90035ccL dc_bnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_motion_y_min                :8 ,	// 7:0
	reg_dc_motion_y_max                :8 ;	// 15:8
}PE_O18_DC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90035d0L dc_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_var_y_th0                   :8 ,	// 7:0
	reg_dc_var_y_th1                   :8 ,	// 15:8
	reg_dc_var_y_th2                   :8 ,	// 23:16
	reg_dc_var_y_th3                   :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90035d4L ac_bnr_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_h_en                    :1 ,	// 0 
	reg_bnr_ac_v_en                    :1 ,	// 1 
	reg_bnr_ac_h_chroma_en             :1 ,	// 2 
	reg_bnr_ac_v_chroma_en             :1 ,	// 3 
	reg_bnr_ac_acness_resol_h          :2 ,	// 5:4
	reg_multi_run_mode                 :1 ,	// 6 
	reg_ac_bnr_gain_yc_sel             :1 ,	// 7 
	reg_bnr_ac_diff_min_v_th           :8 ,	// 15:8
	reg_bnr_ac_diff_min_h_th           :8 ,	// 23:16
	reg_bnr_ac_iir_gain                :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90035d8L ac_bnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_global_motion_th        :8 ,	// 7:0
	reg_bnr_ac_h_acness_max            :8 ,	// 15:8
	reg_bnr_ac_h_acness_min            :8 ,	// 23:16
	reg_bnr_ac_bin_th                  :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90035dcL ac_bnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_motion_3                :8 ,	// 7:0
	reg_bnr_ac_motion_2                :8 ,	// 15:8
	reg_bnr_ac_motion_1                :8 ,	// 23:16
	reg_bnr_ac_motion_0                :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90035e0L dnr_stat_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c420_tearing_cnt                   :16,	// 15:0
	global_motion_iir                  :8 ,	// 23:16
	global_dc_gain                     :8 ;	// 31:24
}PE_O18_DNR_STAT_0_T;
/*-----------------------------------------------------------------------------
                             0xc90035e4L ac_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_motion_y_3              :8 ,	// 7:0
	reg_bnr_ac_motion_y_2              :8 ,	// 15:8
	reg_bnr_ac_motion_y_1              :8 ,	// 23:16
	reg_bnr_ac_motion_y_0              :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90035e8L ac_bnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_v_init_offset           :3 ,	// 2:0
	reg_bnr_ac_h_init_offset           :3 ,	// 5:3
	reg_bnr_ac_acness_resol_v          :2 ,	// 7:6
	reg_bnr_ac_debug_mode              :4 ,	// 11:8
	reg_bnr_ac_hsy_mode                :4 ,	// 15:12
	reg_bnr_ac_v_acness_max            :8 ,	// 23:16
	reg_bnr_ac_v_acness_min            :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90035ecL dnr_stat_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_v_l                         :8 ,	// 7:0
	acness_h_l                         :8 ,	// 15:8
	acness_v_g                         :8 ,	// 23:16
	acness_h_g                         :8 ;	// 31:24
}PE_O18_DNR_STAT_1_T;
/*-----------------------------------------------------------------------------
                             0xc90035f0L ac_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_detail_th4              :8 ,	// 7:0
	reg_bnr_ac_detail_th3              :8 ,	// 15:8
	reg_bnr_ac_detail_th2              :8 ,	// 23:16
	reg_bnr_ac_detail_th1              :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90035f4L ac_bnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_pos_gain_h2             :8 ,	// 7:0
	reg_bnr_ac_pos_gain_h1             :8 ,	// 15:8
	reg_bnr_ac_pos_gain_h0             :8 ,	// 23:16
	reg_bnr_ac_detail_gain_th          :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90035f8L ac_bnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_pos_gain_l2             :8 ,	// 7:0
	reg_bnr_ac_pos_gain_l1             :8 ,	// 15:8
	reg_bnr_ac_pos_gain_l0             :8 ,	// 23:16
	reg_bnr_ac_pos_gain_h3             :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90035fcL dnr_stat_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_init                             :8 ,	// 7:0
	v_init                             :8 ,	// 15:8
	reserved01                         :4 ,	// reserved
	reg_vfilter_tearing_cnt            :12;	// 31:20
}PE_O18_DNR_STAT_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003600L ac_bnr_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ac_master_c_gain               :8 ,	// 7:0
	reg_ac_bnr_enable                  :1 ,	// 8 
	reg_ac_bnr_motion_en               :1 ,	// 9 
	reg_ac_bnr_acness_en               :1 ,	// 10
	reg_ac_bnr_position_en             :1 ,	// 11
	reg_detail_sel                     :1 ,	// 12
	reserved01                         :3 ,	// reserved
	reg_bnr_ac_manual_init_v           :3 ,	// 18:16
	reg_ac_manual_init_en_v            :1 ,	// 19
	reg_bnr_ac_manual_init_h           :3 ,	// 22:20
	reg_ac_manual_init_en_h            :1 ,	// 23
	reg_bnr_ac_pos_gain_l3             :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9003604L ac_bnr_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_acness_sel                     :1 ,	// 0 
	reg_g_motion_manual_en             :1 ,	// 1 
	reserved01                         :6 ,	// reserved
	reg_ac_bnr_debug_h_en              :1 ,	// 8 
	reg_ac_bnr_debug_v_en              :1 ,	// 9 
	reg_ac_master_y_gain               :6 ,	// 15:10
	reg_g_motion_scale                 :3 ,	// 18:16
	reg_g_motion_div                   :2 ,	// 20:19
	reserved02                         :10,	// reserved
	reg_ac_flt_level_sel               :1 ;	// 31
}PE_O18_AC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9003608L ac_bnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ac_detail_gain_y_min           :8 ,	// 7:0
	reg_ac_detail_gain_y_max           :8 ,	// 15:8
	reg_bnr_ac_acness_y_min            :8 ,	// 23:16
	reg_bnr_ac_acness_y_max            :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900360cL ac_bnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ac_detail_alpha2_y_min         :8 ,	// 7:0
	reg_ac_detail_alpha2_y_max         :8 ,	// 15:8
	reg_ac_detail_alpha4_y_min         :8 ,	// 23:16
	reg_ac_detail_alpha4_y_max         :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003610L ac_bnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_g_motion_manual                :8 ,	// 7:0
	reg_acness_scale_mul               :8 ,	// 15:8
	reg_bnr_ac_detail_max              :8 ,	// 23:16
	reg_bnr_ac_detail_min              :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003614L ifc_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_drvt_hcoef_sel               :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_y_ddrvt_hcoef_sel              :2 ,	// 5:4
	reg_y_edge_gain_res                :1 ,	// 6 
	reserved02                         :1 ,	// reserved
	reg_y_drvt2_hcoef_sel              :3 ,	// 10:8
	reg_medge_meth                     :1 ,	// 11
	reg_medge_th                       :8 ,	// 19:12
	reg_medge_coring_th                :8 ,	// 27:20
	reg_medge_ch_tap                   :2 ,	// 29:28
	reg_edge_meth                      :2 ;	// 31:30
}PE_O18_IFC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003618L ifc_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_ddrvt_gain_y1             :8 ,	// 7:0
	reg_edge_ddrvt_gain_x1             :8 ,	// 15:8
	reg_edge_ddrvt_gain_y0             :8 ,	// 23:16
	reg_edge_ddrvt_gain_x0             :8 ;	// 31:24
}PE_O18_IFC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900361cL ifc_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_c_drvt_hcoef_sel               :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_c_ddrvt_hcoef_sel              :2 ,	// 5:4
	reg_c_edge_gain_res                :1 ;	// 6 
}PE_O18_IFC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003620L ifc_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_c_edge_gain_y1                 :8 ,	// 7:0
	reg_c_edge_gain_x1                 :8 ,	// 15:8
	reg_c_edge_gain_y0                 :8 ,	// 23:16
	reg_c_edge_gain_x0                 :8 ;	// 31:24
}PE_O18_IFC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9003624L ifc_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_crs_para_tap                   :2 ,	// 1:0
	reg_cdst_th                        :10,	// 11:2
	reg_crs_op_tap                     :2 ,	// 13:12
	reg_crs_gain_res                   :1 ,	// 14
	reserved01                         :1 ,	// reserved
	reg_cdiff_hcoef_sel                :2 ,	// 17:16
	reserved02                         :10,	// reserved
	reg_crs_point                      :2 ,	// 29:28
	reg_crs_meth                       :2 ;	// 31:30
}PE_O18_IFC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9003628L ifc_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :8 ,	// 7:0
	reg_crs_gain_y1                    :8 ,	// 15:8
	reg_crs_gain_x1                    :8 ,	// 23:16
	reg_crs_gain_y0                    :8 ;	// 31:24
}PE_O18_IFC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900362cL ifc_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9003630L ifc_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9003634L ifc_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :1 ,	// 0 
	reg_ifc_en                         :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	reg_clp_on                         :1 ,	// 4 
	reserved02                         :15,	// reserved
	reg_edge_en                        :2 ,	// 21:20
	reg_clp_tap                        :2 ,	// 23:22
	reg_ifc_flt_sel                    :2 ,	// 25:24
	reg_debug_en                       :4 ,	// 29:26
	reg_debug_mode                     :2 ;	// 31:30
}PE_O18_IFC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9003638L ifc_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900363cL ifc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9003640L ifc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003644L ifc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reserved                           :8 ,	// 23:16
	reg_crs_zero_th                    :8 ;	// 31:24
}PE_O18_IFC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003648L ifc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc900364cL ifc_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9003650L ifc_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_medge_gain_y1                  :8 ,	// 7:0
	reg_medge_gain_x1                  :8 ,	// 15:8
	reg_medge_gain_y0                  :8 ,	// 23:16
	reg_medge_gain_x0                  :8 ;	// 31:24
}PE_O18_IFC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9003654L ifc_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_crs_op_gain_isel               :2 ,	// 1:0
	reg_crs_op_gain_res                :1 ,	// 2 
	reg_crs_cdst_flt                   :3 ,	// 5:3
	reserved01                         :1 ,	// reserved
	reg_crs_cdst_vmdn                  :1 ,	// 7 
	reg_crs_cdst_op_flt                :3 ,	// 10:8
	reserved02                         :5 ,	// reserved
	reg_op_wgain_coef1                 :2 ,	// 17:16
	reg_op_wgain_coef2                 :2 ,	// 19:18
	reg_op_wgain_coef3                 :2 ;	// 21:20
}PE_O18_IFC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9003658L ifc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :8 ,	// 7:0
	reg_crs_op_gain_y1                 :8 ,	// 15:8
	reg_crs_op_gain_x1                 :8 ,	// 23:16
	reg_crs_op_gain_y0                 :8 ;	// 31:24
}PE_O18_IFC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc900365cL ifc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9003660L ifc_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reserved                           :8 ,	// 23:16
	reg_medge_op_th                    :1 ,	// 24
	reg_mmd_gain_en                    :2 ,	// 26:25
	reg_mmd_gain_flt                   :2 ,	// 28:27
	reg_mmd_gain_tap                   :1 ;	// 29
}PE_O18_IFC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9003664L ifc_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_IFC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9003668L ifc_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_gain_y1                    :8 ,	// 7:0
	reg_mmd_gain_x1                    :8 ,	// 15:8
	reg_mmd_gain_y0                    :8 ,	// 23:16
	reg_mmd_gain_x0                    :8 ;	// 31:24
}PE_O18_IFC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc900366cL sc_bnr_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sc_bnr_en                      :1 ,	// 0 
	reg_sc_bnr_manual_h_en             :1 ,	// 1 
	reg_scene_ch_flag                  :1 ,	// 2 
	reg_iir_en                         :1 ,	// 3 
	reg_scale_mul_h                    :9 ,	// 12:4
	reg_scale_div_h                    :4 ,	// 16:13
	reg_sc_bnr_manual_v_en             :1 ,	// 17
	reg_sc_bnr_en_h                    :1 ,	// 18
	reg_sc_bnr_en_v                    :1 ,	// 19
	reserved01                         :2 ,	// reserved
	reg_avg_scale_mul_h                :4 ,	// 25:22
	reg_avg_scale_div_h                :3 ,	// 28:26
	reg_max_index_diff_th              :3 ;	// 31:29
}PE_O18_SC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003670L sc_bnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post2_iir_gain                 :8 ,	// 7:0
	reg_frm_cnt_th                     :8 ,	// 15:8
	reg_bin_ratio_th                   :8 ,	// 23:16
	reg_detect_th                      :8 ;	// 31:24
}PE_O18_SC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003674L sc_bnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bin_ratio_div                  :8 ,	// 7:0
	reg_bin_ratio_mul                  :8 ,	// 15:8
	reg_min_bin_th                     :8 ,	// 23:16
	reg_detector_iir_gain              :8 ;	// 31:24
}PE_O18_SC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003678L sc_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_grid_th1                       :8 ,	// 7:0
	reg_grid_th2                       :8 ,	// 15:8
	reg_grid_th3                       :8 ;	// 23:16
}PE_O18_SC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900367cL sc_bnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pos_gain_th                    :8 ,	// 7:0
	reserved01                         :11,	// reserved
	reg_scale_div_v                    :4 ,	// 22:19
	reg_scale_mul_v                    :9 ;	// 31:23
}PE_O18_SC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9003680L sc_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pos_gain_3                     :8 ,	// 7:0
	reg_pos_gain_2                     :8 ,	// 15:8
	reg_pos_gain_1                     :8 ,	// 23:16
	reg_pos_gain_0                     :8 ;	// 31:24
}PE_O18_SC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc9003684L sc_bnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sc_bnr_debug_en                :1 ,	// 0 
	reg_sc_bnr_debug_mode              :3 ,	// 3:1
	reg_avg_scale_div_v                :3 ,	// 6:4
	reg_avg_scale_mul_v                :4 ,	// 10:7
	reserved01                         :13,	// reserved
	reg_acness_th                      :8 ;	// 31:24
}PE_O18_SC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9003688L c_pre_blur_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_121_blur_en                    :1 ,	// 0 
	pre_median_en                      :1 ;	// 1 
}PE_O18_C_PRE_BLUR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900368cL texture_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_texture_cnt_div                :8 ,	// 15:8
	reserved02                         :8 ,	// reserved
	reg_texture_cnt_mul                :8 ;	// 31:24
}PE_O18_TEXTURE_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003690L texture_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TEXTURE_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003694L texture_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TEXTURE_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003698L texture_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_TEXTURE_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900369cL ac_bnr_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_acness_gain_h_l                :8 ,	// 15:8
	reg_acness_gain_h_g                :8 ,	// 23:16
	reg_acness_gain_h                  :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90036a0L ac_bnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_acness_gain_v_l                :8 ,	// 15:8
	reg_acness_gain_v_g                :8 ,	// 23:16
	reg_acness_gain_v                  :8 ;	// 31:24
}PE_O18_AC_BNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90036a4L dc_bnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_x_th0               :8 ,	// 7:0
	reg_fil_motion_x_th1               :8 ,	// 15:8
	reg_fil_motion_x_th2               :8 ,	// 23:16
	reg_fil_motion_x_th3               :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90036a8L dc_bnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_y_th0               :8 ,	// 7:0
	reg_fil_motion_y_th1               :8 ,	// 15:8
	reg_fil_motion_y_th2               :8 ,	// 23:16
	reg_fil_motion_y_th3               :8 ;	// 31:24
}PE_O18_DC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90036acL sqm_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_sel                        :2 ,	// 1:0
	reserved01                         :6 ,	// reserved
	reg_hist_bin_th0                   :8 ,	// 15:8
	reg_hist_bin_th1                   :8 ,	// 23:16
	reg_hist_bin_th2                   :8 ;	// 31:24
}PE_O18_SQM_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90036b0L sqm_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hist_bin_th3                   :8 ,	// 7:0
	reg_hist_bin_th4                   :8 ,	// 15:8
	reg_hist_bin_th5                   :8 ,	// 23:16
	reg_hist_bin_th6                   :8 ;	// 31:24
}PE_O18_SQM_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90036b4L sqm_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_trans_mmd_th                   :8 ,	// 7:0
	reserved01                         :2 ,	// reserved
	reg_edge_a_th                      :10,	// 19:10
	reg_edf_mmd_th                     :8 ;	// 27:20
}PE_O18_SQM_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90036b8L sqm_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_win_mode_x1                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_sqm_win_mode_x0                :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_sqm_win_mode_mode              :1 ,	// 30
	reg_sqm_win_mode_en                :1 ;	// 31
}PE_O18_SQM_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90036bcL sqm_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_win_mode_y1                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_sqm_win_mode_y0                :13;	// 28:16
}PE_O18_SQM_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90036c0L tpd_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tp_binary_th                   :8 ;	// 7:0
}PE_O18_TPD_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90036c4L window_mode_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mode_x1                    :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_mode_x0                    :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_win_mode_mode                  :1 ,	// 30
	reg_win_mode_en                    :1 ;	// 31
}PE_O18_WINDOW_MODE_0_T;
/*-----------------------------------------------------------------------------
                             0xc90036c8L window_mode_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mode_y1                    :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_mode_y0                    :13;	// 28:16
}PE_O18_WINDOW_MODE_1_T;
/*-----------------------------------------------------------------------------
                             0xc90036d0L dnr_stat_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_v_g                         :8 ,	// 7:0
	acness_h_g                         :8 ,	// 15:8
	acness_v                           :8 ,	// 23:16
	acness_h                           :8 ;	// 31:24
}PE_O18_DNR_STAT_3_T;
/*-----------------------------------------------------------------------------
                             0xc90036d4L dnr_stat_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bad_up_cnt                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	acness_v_l                         :8 ,	// 23:16
	acness_h_l                         :8 ;	// 31:24
}PE_O18_DNR_STAT_4_T;
/*-----------------------------------------------------------------------------
                             0xc90036d8L dnr_stat_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved                           :8 ,	// 7:0
	acness_gain_v_l                    :8 ,	// 15:8
	acness_gain_h_l                    :8 ,	// 23:16
	acness_gain_v_g                    :8 ;	// 31:24
}PE_O18_DNR_STAT_5_T;
/*-----------------------------------------------------------------------------
                             0xc90036dcL dnr_stat_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O18_DNR_STAT_6_T;
/*-----------------------------------------------------------------------------
                             0xc90036e0L dnr_stat_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_gain_v                      :8 ,	// 7:0
	acness_gain_h                      :8 ,	// 15:8
	acness_v_iir                       :8 ,	// 23:16
	acness_h_iir                       :8 ;	// 31:24
}PE_O18_DNR_STAT_7_T;
/*-----------------------------------------------------------------------------
                             0xc90036e4L dnr_stat_8_sc_bnr0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bin_ratio_iir_h                    :8 ,	// 7:0
	bin_ratio_v                        :8 ,	// 15:8
	bin_ratio_h                        :8 ,	// 23:16
	hys_cnt_v                          :3 ,	// 26:24
	hys_cnt_h                          :3 ,	// 29:27
	sc_bnr_flag_v                      :1 ,	// 30
	sc_bnr_flag_h                      :1 ;	// 31
}PE_O18_DNR_STAT_8_SC_BNR0_T;
/*-----------------------------------------------------------------------------
                             0xc90036e8L dnr_stat_9_sc_bnr1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	max_index_iir_h                    :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	max_index_v                        :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	max_index_h                        :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	bin_ratio_iir_v                    :8 ;	// 31:24
}PE_O18_DNR_STAT_9_SC_BNR1_T;
/*-----------------------------------------------------------------------------
                             0xc90036ecL dnr_stat_10_sc_bnr2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_max_index_iir_v                  :7 ;	// 6:0
}PE_O18_DNR_STAT_10_SC_BNR2_T;
/*-----------------------------------------------------------------------------
                             0xc90036f0L dnr_stat_11_sqm_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_1                           :16,	// 15:0
	e_hist_0                           :16;	// 31:16
}PE_O18_DNR_STAT_11_SQM_00_T;
/*-----------------------------------------------------------------------------
                             0xc90036f4L dnr_stat_12_sqm_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_3                           :16,	// 15:0
	e_hist_2                           :16;	// 31:16
}PE_O18_DNR_STAT_12_SQM_01_T;
/*-----------------------------------------------------------------------------
                             0xc90036f8L dnr_stat_13_sqm_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_5                           :16,	// 15:0
	e_hist_4                           :16;	// 31:16
}PE_O18_DNR_STAT_13_SQM_02_T;
/*-----------------------------------------------------------------------------
                             0xc90036fcL dnr_stat_14_sqm_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_7                           :16,	// 15:0
	e_hist_6                           :16;	// 31:16
}PE_O18_DNR_STAT_14_SQM_03_T;
/*-----------------------------------------------------------------------------
                             0xc9003700L dnr_stat_15_sqm_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_1                           :16,	// 15:0
	f_hist_0                           :16;	// 31:16
}PE_O18_DNR_STAT_15_SQM_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003704L dnr_stat_16_sqm_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_3                           :16,	// 15:0
	f_hist_2                           :16;	// 31:16
}PE_O18_DNR_STAT_16_SQM_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003708L dnr_stat_17_sqm_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_5                           :16,	// 15:0
	f_hist_4                           :16;	// 31:16
}PE_O18_DNR_STAT_17_SQM_06_T;
/*-----------------------------------------------------------------------------
                             0xc900370cL dnr_stat_18_sqm_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_7                           :16,	// 15:0
	f_hist_6                           :16;	// 31:16
}PE_O18_DNR_STAT_18_SQM_07_T;
/*-----------------------------------------------------------------------------
                             0xc9003710L dnr_stat_19_sqm_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_1                           :16,	// 15:0
	t_hist_0                           :16;	// 31:16
}PE_O18_DNR_STAT_19_SQM_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003714L dnr_stat_20_sqm_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_3                           :16,	// 15:0
	t_hist_2                           :16;	// 31:16
}PE_O18_DNR_STAT_20_SQM_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003718L dnr_stat_21_sqm_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_5                           :16,	// 15:0
	t_hist_4                           :16;	// 31:16
}PE_O18_DNR_STAT_21_SQM_10_T;
/*-----------------------------------------------------------------------------
                             0xc900371cL dnr_stat_22_sqm_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_7                           :16,	// 15:0
	t_hist_6                           :16;	// 31:16
}PE_O18_DNR_STAT_22_SQM_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003720L dnr_stat_23_tpd_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_h_cnt_2                        :16,	// 15:0
	res_h_cnt_1                        :16;	// 31:16
}PE_O18_DNR_STAT_23_TPD_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003724L dnr_stat_24_tpd_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_v_cnt_2                        :16,	// 15:0
	res_v_cnt_1                        :16;	// 31:16
}PE_O18_DNR_STAT_24_TPD_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003728L dnr_stat_25_tpd_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_v_cnt_3                        :16,	// 15:0
	res_h_cnt_3                        :16;	// 31:16
}PE_O18_DNR_STAT_25_TPD_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003730L ac_bnr_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_x_th3               :8 ,	// 7:0
	reg_fil_motion_x_th2               :8 ,	// 15:8
	reg_fil_motion_x_th1               :8 ,	// 23:16
	reg_fil_motion_x_th0               :8 ;	// 31:24
}PE_O18_AC_BNR_15_T;
/*-----------------------------------------------------------------------------
                             0xc9003734L ac_bnr_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_y_th3               :8 ,	// 7:0
	reg_fil_motion_y_th2               :8 ,	// 15:8
	reg_fil_motion_y_th1               :8 ,	// 23:16
	reg_fil_motion_y_th0               :8 ;	// 31:24
}PE_O18_AC_BNR_16_T;
/*-----------------------------------------------------------------------------
                             0xc9003738L vfilter_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tearing_y_1                    :4 ,	// 3:0
	reserved01                         :4 ,	// reserved
	reg_tearing_y_0                    :4 ,	// 11:8
	reserved02                         :4 ,	// reserved
	reg_tearing_x_1                    :4 ,	// 19:16
	reserved03                         :4 ,	// reserved
	reg_tearing_x_0                    :4 ;	// 27:24
}PE_O18_VFILTER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc900373cL vfilter_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_x_3                     :8 ,	// 7:0
	reg_motion_x_2                     :8 ,	// 15:8
	reg_motion_x_1                     :8 ,	// 23:16
	reg_motion_x_0                     :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9003740L vfilter_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_y_3                     :8 ,	// 7:0
	reg_motion_y_2                     :8 ,	// 15:8
	reg_motion_y_1                     :8 ,	// 23:16
	reg_motion_y_0                     :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9003744L vfilter_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_global_x_3                     :8 ,	// 7:0
	reg_global_x_2                     :8 ,	// 15:8
	reg_global_x_1                     :8 ,	// 23:16
	reg_global_x_0                     :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9003748L vfilter_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_global_y_3                     :8 ,	// 7:0
	reg_global_y_2                     :8 ,	// 15:8
	reg_global_y_1                     :8 ,	// 23:16
	reg_global_y_0                     :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc900374cL vfilter_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_x_3                      :8 ,	// 7:0
	reg_blend_x_2                      :8 ,	// 15:8
	reg_blend_x_1                      :8 ,	// 23:16
	reg_blend_x_0                      :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9003750L vfilter_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_y_3                      :8 ,	// 7:0
	reg_blend_y_2                      :8 ,	// 15:8
	reg_blend_y_1                      :8 ,	// 23:16
	reg_blend_y_0                      :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9003754L vfilter_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_x_3                        :8 ,	// 7:0
	reg_hmc_x_2                        :8 ,	// 15:8
	reg_hmc_x_1                        :8 ,	// 23:16
	reg_hmc_x_0                        :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9003758L vfilter_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_y_3                        :8 ,	// 7:0
	reg_hmc_y_2                        :8 ,	// 15:8
	reg_hmc_y_1                        :8 ,	// 23:16
	reg_hmc_y_0                        :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc900375cL vfilter_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_local_x_3                      :8 ,	// 7:0
	reg_local_x_2                      :8 ,	// 15:8
	reg_local_x_1                      :8 ,	// 23:16
	reg_local_x_0                      :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003760L vfilter_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_y_3                        :8 ,	// 7:0
	reg_local_y_2                      :8 ,	// 15:8
	reg_local_y_1                      :8 ,	// 23:16
	reg_local_y_0                      :8 ;	// 31:24
}PE_O18_VFILTER_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9003764L reg_decon_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_use_osd_map         :1 ,	// 0 
	reg_2nd_out_rd_out_clip            :1 ,	// 1 
	reg_1st_out_rd_out_clip            :1 ,	// 2 
	reserved01                         :5 ,	// reserved
	reg_11bit_debug_mode_en            :1 ,	// 8 
	reg_out_bit_opt                    :1 ,	// 9 
	reg_tnr_decon_out_bit_sel          :1 ,	// 10
	reg_tnr_decon_in_bit_sel           :1 ,	// 11
	reg_1st_out_rd_max_alpha           :8 ,	// 19:12
	reg_1st_out_rd_min_alpha           :8 ,	// 27:20
	reg_1st_out_rd_bit                 :3 ,	// 30:28
	reg_1st_out_rd_on                  :1 ;	// 31
}PE_O18_REG_DECON_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003768L reg_decon_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_min_pel_cb          :12,	// 11:0
	reg_1st_out_rd_min_pel_yy          :12;	// 23:12
}PE_O18_REG_DECON_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900376cL reg_decon_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_yy          :12,	// 11:0
	reg_1st_out_rd_min_pel_cr          :12;	// 23:12
}PE_O18_REG_DECON_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003770L reg_decon_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_cr          :12,	// 11:0
	reg_1st_out_rd_max_pel_cb          :12;	// 23:12
}PE_O18_REG_DECON_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9003774L reg_decon_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9003778L reg_decon_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900377cL reg_decon_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9003780L reg_decon_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_on           :1 ,	// 0 
	reg_err_out_rd_simple_bit          :3 ,	// 3:1
	reg_2nd_out_rd_bit                 :4 ,	// 7:4
	reserved01                         :3 ,	// reserved
	reg_2nd_out_rd_use_osd_map         :1 ,	// 11
	reg_2nd_out_rd_max_alpha           :8 ,	// 19:12
	reg_2nd_out_rd_min_alpha           :8 ,	// 27:20
	reserved02                         :3 ,	// reserved
	reg_2nd_out_rd_on                  :1 ;	// 31
}PE_O18_REG_DECON_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9003784L reg_decon_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_min_pel_cb          :12,	// 11:0
	reg_2nd_out_rd_min_pel_yy          :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_max_lsb_2b          :2 ,	// 29:28
	reg_2nd_out_rd_min_lsb_2b          :2 ;	// 31:30
}PE_O18_REG_DECON_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9003788L reg_decon_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_yy          :12,	// 11:0
	reg_2nd_out_rd_min_pel_cr          :12;	// 23:12
}PE_O18_REG_DECON_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900378cL reg_decon_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_cr          :12,	// 11:0
	reg_2nd_out_rd_max_pel_cb          :12,	// 23:12
	reserved01                         :7 ,	// reserved
	reg_err_out_rd_simple_clip         :1 ;	// 31
}PE_O18_REG_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9003790L reg_dc_bnr_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_x3                        :8 ,	// 7:0
	reg_gain_x2                        :8 ,	// 15:8
	reg_gain_x1                        :8 ,	// 23:16
	reg_gain_x0                        :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9003794L reg_dc_bnr_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_x7                        :8 ,	// 7:0
	reg_gain_x6                        :8 ,	// 15:8
	reg_gain_x5                        :8 ,	// 23:16
	reg_gain_x4                        :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9003798L reg_dc_bnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_y3                        :8 ,	// 7:0
	reg_gain_y2                        :8 ,	// 15:8
	reg_gain_y1                        :8 ,	// 23:16
	reg_gain_y0                        :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900379cL reg_dc_bnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_y7                        :8 ,	// 7:0
	reg_gain_y6                        :8 ,	// 15:8
	reg_gain_y5                        :8 ,	// 23:16
	reg_gain_y4                        :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90037a0L reg_decon_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90037a4L reg_decon_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90037a8L reg_decon_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90037acL reg_decon_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90037b0L reg_decon_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90037b4L reg_decon_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90037b8L reg_decon_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_diff_mul_old                   :8 ,	// 7:0
	reg_force_block_v                  :6 ,	// 13:8
	reg_1st_debug_en                   :1 ,	// 14
	reg_l6_var_csc_en                  :1 ,	// 15
	reg_force_block_no_h               :6 ,	// 21:16
	reserved01                         :1 ,	// reserved
	reg_rd_simple_clip                 :1 ,	// 23
	reg_rd_clip                        :1 ,	// 24
	reg_input_csc_en                   :1 ,	// 25
	reg_1st_debug_mode                 :4 ,	// 29:26
	reg_force_block_no_en              :1 ,	// 30
	reg_decon_1st_en                   :1 ;	// 31
}PE_O18_REG_DECON_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90037bcL reg_decon_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_var_chroma_en                  :1 ,	// 0 
	reg_diff_sel                       :1 ,	// 1 
	reg_ups_sel                        :1 ,	// 2 
	reserved01                         :12,	// reserved
	reg_old_luma_bit_opt               :1 ,	// 15
	reg_luma_bit_opt                   :1 ,	// 16
	reg_var_bit_opt                    :1 ,	// 17
	reg_l6_var_bit_opt                 :1 ,	// 18
	reg_l6_blur_bit_opt                :1 ,	// 19
	reg_var_v_gain                     :4 ,	// 23:20
	reg_var_h_gain                     :4 ,	// 27:24
	reg_var_cut_resolution             :4 ;	// 31:28
}PE_O18_REG_DECON_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90037c0L reg_decon_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_x_th0               :8 ,	// 7:0
	reg_decon_diff_x_th1               :8 ,	// 15:8
	reg_decon_diff_x_th2               :8 ,	// 23:16
	reg_decon_diff_x_th3               :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90037c4L reg_decon_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_y_th0               :8 ,	// 7:0
	reg_decon_diff_y_th1               :8 ,	// 15:8
	reg_decon_diff_y_th2               :8 ,	// 23:16
	reg_decon_diff_y_th3               :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90037c8L reg_decon_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_x_th2                :10,	// 9:0
	reg_decon_var_x_th1                :10,	// 19:10
	reg_decon_var_x_th0                :10;	// 29:20
}PE_O18_REG_DECON_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90037ccL reg_decon_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_y_th1                :10,	// 9:0
	reg_decon_var_y_th0                :10,	// 19:10
	reg_decon_var_x_th3                :10;	// 29:20
}PE_O18_REG_DECON_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90037d0L reg_decon_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th0               :10,	// 9:0
	reg_decon_var_y_th3                :10,	// 19:10
	reg_decon_var_y_th2                :10;	// 29:20
}PE_O18_REG_DECON_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90037d4L reg_decon_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th3               :10,	// 9:0
	reg_decon_luma_x_th2               :10,	// 19:10
	reg_decon_luma_x_th1               :10;	// 29:20
}PE_O18_REG_DECON_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90037d8L reg_decon_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th6               :10,	// 9:0
	reg_decon_luma_x_th5               :10,	// 19:10
	reg_decon_luma_x_th4               :10;	// 29:20
}PE_O18_REG_DECON_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90037dcL reg_decon_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th1               :10,	// 9:0
	reg_decon_luma_y_th0               :10,	// 19:10
	reg_decon_luma_x_th7               :10;	// 29:20
}PE_O18_REG_DECON_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90037e0L reg_decon_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th4               :10,	// 9:0
	reg_decon_luma_y_th3               :10,	// 19:10
	reg_decon_luma_y_th2               :10;	// 29:20
}PE_O18_REG_DECON_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90037e4L reg_decon_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th7               :10,	// 9:0
	reg_decon_luma_y_th6               :10,	// 19:10
	reg_decon_luma_y_th5               :10;	// 29:20
}PE_O18_REG_DECON_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90037e8L reg_decon_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_block_size_v                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_block_size_h                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_block_no_v                     :6 ,	// 21:16
	reserved03                         :2 ,	// reserved
	reg_block_no_h                     :6 ,	// 29:24
	reserved04                         :1 ,	// reserved
	reg_block_info_force_en            :1 ;	// 31
}PE_O18_REG_DECON_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90037ecL reg_decon_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_last_block_size_v              :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_last_block_size_h              :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_diff_mul_new                   :4 ,	// 19:16
	reg_diff_shift                     :3 ,	// 22:20
	reg_osd_run_mode                   :1 ,	// 23
	reg_alpha_blur_l6_var_sm           :1 ,	// 24
	reg_alpha_blur_mode                :2 ,	// 26:25
	reg_blending_alpha_use_l6_var      :2 ,	// 28:27
	reg_diff_use_seldiff               :1 ,	// 29
	reg_diff_calc_mode                 :2 ;	// 31:30
}PE_O18_REG_DECON_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90037f0L reg_decon_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_alpha_blur_l6_var_th1          :10,	// 9:0
	reg_alpha_blur_l6_var_th0          :10;	// 19:10
}PE_O18_REG_DECON_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90037f4L reg_decon_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_x_th2                   :10,	// 9:0
	reg_l6_var_x_th1                   :10,	// 19:10
	reg_l6_var_x_th0                   :10;	// 29:20
}PE_O18_REG_DECON_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90037f8L reg_decon_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th1                   :10,	// 9:0
	reg_l6_var_y_th0                   :10,	// 19:10
	reg_l6_var_x_th3                   :10;	// 29:20
}PE_O18_REG_DECON_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90037fcL reg_decon_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th3                   :10,	// 9:0
	reg_l6_var_y_th2                   :10,	// 19:10
	reserved01                         :8 ,	// reserved
	reg_decon_rd_simple_bit            :3 ,	// 30:28
	reg_decon_rd_simple_on             :1 ;	// 31
}PE_O18_REG_DECON_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9003800L reg_decon_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9003804L reg_decon_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc9003808L reg_decon_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc900380cL reg_decon_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_min_pel_cb                  :12,	// 11:0
	reg_rd_min_pel_yy                  :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_rd_bit                         :3 ,	// 30:28
	reg_decon_rd_on                    :1 ;	// 31
}PE_O18_REG_DECON_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9003810L reg_decon_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_yy                  :12,	// 11:0
	reg_rd_min_pel_cr                  :12;	// 23:12
}PE_O18_REG_DECON_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9003814L reg_decon_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_cr                  :12,	// 11:0
	reg_rd_max_pel_cb                  :12;	// 23:12
}PE_O18_REG_DECON_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc9003818L reg_decon_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc900381cL reg_decon_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc9003820L reg_decon_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc9003824L reg_decon_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_dist_h             :4 ,	// 3:0
	reg_l6_var_diff_dist_w             :4 ,	// 7:4
	reg_l6_var_max_cut_value           :12,	// 19:8
	reg_l6_var_max_th                  :12;	// 31:20
}PE_O18_REG_DECON_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc9003828L reg_decon_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_cr              :10,	// 9:0
	reg_l6_var_diff_th_cb              :10,	// 19:10
	reg_l6_var_diff_th_yy              :10;	// 29:20
}PE_O18_REG_DECON_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc900382cL reg_decon_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_yy3             :10,	// 9:0
	reg_l6_var_diff_th_yy2             :10;	// 19:10
}PE_O18_REG_DECON_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc9003830L reg_decon_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_t_min_yy3          :10,	// 9:0
	reg_l6_var_diff_t_min_yy2          :10,	// 19:10
	reg_l6_var_diff_t_min_yy           :10;	// 29:20
}PE_O18_REG_DECON_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc9003834L reg_decon_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_cc3         :10,	// 9:0
	reg_l6_var_diff_th_min_cc2         :10,	// 19:10
	reg_l6_var_diff_th_min_cc          :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_l6_var_reshape_en              :1 ;	// 31
}PE_O18_REG_DECON_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc9003838L reg_decon_ctrl_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_yy_cond_cb_adj_ratio  :8 ,	// 7:0
	reg_l6_var_v_yy_cond_yy_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_diff_yy_cond_ratio    :8 ,	// 23:16
	reg_l6_var_v_diff_yy_cond_ratio    :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc900383cL reg_decon_ctrl_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_yy_cond_cr_adj_ratio  :8 ,	// 7:0
	reg_l6_var_h_yy_cond_cb_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_yy_cond_yy_adj_ratio  :8 ,	// 23:16
	reg_l6_var_v_yy_cond_cr_adj_ratio  :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc9003840L reg_decon_ctrl_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_l6_var_cc_cond_cr_adj_ratio    :8 ,	// 15:8
	reg_l6_var_cc_cond_cb_adj_ratio    :8 ,	// 23:16
	reg_l6_var_cc_cond_yy_adj_ratio    :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc9003844L reg_decon_ctrl_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_diff_cut_value        :12,	// 11:0
	reg_l6_var_v_diff_th               :12;	// 23:12
}PE_O18_REG_DECON_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc9003848L reg_decon_ctrl_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_diff_cut_value        :12,	// 11:0
	reg_l6_var_h_diff_th               :12;	// 23:12
}PE_O18_REG_DECON_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc900384cL reg_decon_ctrl_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_max_rep_value:12,	// 11:0
	reg_l6_var_total_diff_max_th       :12;	// 23:12
}PE_O18_REG_DECON_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc9003850L reg_decon_ctrl_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_low_rep_value:12,	// 11:0
	reg_l6_var_total_diff_low_th       :12,	// 23:12
	reserved01                         :2 ,	// reserved
	reg_l6_var_mopology_3rd_sel        :2 ,	// 27:26
	reg_l6_var_mopology_2nd_sel        :2 ,	// 29:28
	reg_l6_var_mopology_1st_sel        :2 ;	// 31:30
}PE_O18_REG_DECON_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc9003854L reg_decon_ctrl_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_mopology_2nd_cut_th     :12,	// 11:0
	reg_l6_var_mopology_1st_cut_th     :12;	// 23:12
}PE_O18_REG_DECON_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc9003858L reg_decon_ctrl_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_mopology_3rd_cut_th     :12;	// 11:0
}PE_O18_REG_DECON_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc900385cL reg_decon_ctrl_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_diff_mul                       :4 ,	// 3:0
	reg_2nd_diff_shift                 :3 ,	// 6:4
	reg_2nd_alpha_blur_mode            :1 ,	// 7 
	reg_2nd_debug_mode                 :3 ,	// 10:8
	reg_odd_sel                        :1 ,	// 11
	reg_2nd_osd_run_mode               :1 ,	// 12
	reg_2nd_rd_simple_bit              :3 ,	// 15:13
	reg_2nd_rd_simple_on               :1 ,	// 16
	reg_input_csc_en                   :1 ,	// 17
	reg_2nd_var_v_gain                 :2 ,	// 19:18
	reg_2nd_var_h_gain                 :2 ,	// 21:20
	reg_2nd_var_cut_resolution         :3 ,	// 24:22
	reg_2nd_var_chroma_en              :1 ,	// 25
	reg_2nd_var_sel_tmp                :2 ,	// 27:26
	reg_2nd_fil_sel_tmp                :2 ,	// 29:28
	reg_2nd_debug_en                   :1 ,	// 30
	reg_decon_2nd_en                   :1 ;	// 31
}PE_O18_REG_DECON_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc9003860L reg_decon_ctrl_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th2                 :10,	// 9:0
	reg_2nd_luma_x_th1                 :10,	// 19:10
	reg_2nd_luma_x_th0                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_444_mode                       :1 ;	// 31
}PE_O18_REG_DECON_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc9003864L reg_decon_ctrl_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th5                 :10,	// 9:0
	reg_2nd_luma_x_th4                 :10,	// 19:10
	reg_2nd_luma_x_th3                 :10,	// 29:20
	reg_2nd_luma_bit_opt               :2 ;	// 31:30
}PE_O18_REG_DECON_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc9003868L reg_decon_ctrl_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th0                 :10,	// 9:0
	reg_2nd_luma_x_th7                 :10,	// 19:10
	reg_2nd_luma_x_th6                 :10;	// 29:20
}PE_O18_REG_DECON_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc900386cL reg_decon_ctrl_62                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th3                 :10,	// 9:0
	reg_2nd_luma_y_th2                 :10,	// 19:10
	reg_2nd_luma_y_th1                 :10;	// 29:20
}PE_O18_REG_DECON_CTRL_62_T;
/*-----------------------------------------------------------------------------
                             0xc9003870L reg_decon_ctrl_63                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th6                 :10,	// 9:0
	reg_2nd_luma_y_th5                 :10,	// 19:10
	reg_2nd_luma_y_th4                 :10;	// 29:20
}PE_O18_REG_DECON_CTRL_63_T;
/*-----------------------------------------------------------------------------
                             0xc9003874L reg_decon_ctrl_64                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_x_th1                  :10,	// 9:0
	reg_2nd_var_x_th0                  :10,	// 19:10
	reg_2nd_luma_y_th7                 :10;	// 29:20
}PE_O18_REG_DECON_CTRL_64_T;
/*-----------------------------------------------------------------------------
                             0xc9003878L reg_decon_ctrl_65                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th0                  :10,	// 9:0
	reg_2nd_var_x_th3                  :10,	// 19:10
	reg_2nd_var_x_th2                  :10;	// 29:20
}PE_O18_REG_DECON_CTRL_65_T;
/*-----------------------------------------------------------------------------
                             0xc900387cL reg_decon_ctrl_66                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th3                  :10,	// 9:0
	reg_2nd_var_y_th2                  :10,	// 19:10
	reg_2nd_var_y_th1                  :10;	// 29:20
}PE_O18_REG_DECON_CTRL_66_T;
/*-----------------------------------------------------------------------------
                             0xc9003880L reg_decon_ctrl_67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_x_th0                 :8 ,	// 7:0
	reg_2nd_diff_x_th1                 :8 ,	// 15:8
	reg_2nd_diff_x_th2                 :8 ,	// 23:16
	reg_2nd_diff_x_th3                 :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_67_T;
/*-----------------------------------------------------------------------------
                             0xc9003884L reg_decon_ctrl_68                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_y_th0                 :8 ,	// 7:0
	reg_2nd_diff_y_th1                 :8 ,	// 15:8
	reg_2nd_diff_y_th2                 :8 ,	// 23:16
	reg_2nd_diff_y_th3                 :8 ;	// 31:24
}PE_O18_REG_DECON_CTRL_68_T;
/*-----------------------------------------------------------------------------
                             0xc9003888L reg_decon_ctrl_69                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_yy;	// 31:0
}PE_O18_REG_DECON_CTRL_69_T;
/*-----------------------------------------------------------------------------
                             0xc900388cL reg_decon_ctrl_70                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cb;	// 31:0
}PE_O18_REG_DECON_CTRL_70_T;
/*-----------------------------------------------------------------------------
                             0xc9003890L reg_decon_ctrl_71                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cr;	// 31:0
}PE_O18_REG_DECON_CTRL_71_T;
/*-----------------------------------------------------------------------------
                             0xc9003894L reg_decon_ctrl_72                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_diff_ker_dl                :5 ,	// 4:0
	reg_err_diff_ker_ur                :5 ,	// 9:5
	reg_err_diff_ker_um                :5 ,	// 14:10
	reg_err_diff_ker_ul                :5 ,	// 19:15
	reserved01                         :10,	// reserved
	reg_err_out_clip                   :1 ,	// 30
	reg_err_diff_en                    :1 ;	// 31
}PE_O18_REG_DECON_CTRL_72_T;
/*-----------------------------------------------------------------------------
                             0xc9003898L reg_dc_bnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blur_y_max                 :8 ,	// 7:0
	reg_psp_blur_y_min                 :8 ,	// 15:8
	reg_psp_blur_x_max                 :8 ,	// 23:16
	reg_psp_blur_x_min                 :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc900389cL reg_dc_bnr_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_x_th3                :8 ,	// 7:0
	reg_psp_blend_x_th2                :8 ,	// 15:8
	reg_psp_blend_x_th1                :8 ,	// 23:16
	reg_psp_blend_x_th0                :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90038a0L reg_dc_bnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_y_th1                :8 ,	// 7:0
	reg_psp_blend_y_th0                :8 ,	// 15:8
	reg_psp_blend_x_th5                :8 ,	// 23:16
	reg_psp_blend_x_th4                :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90038a4L reg_dc_bnr_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_y_th5                :8 ,	// 7:0
	reg_psp_blend_y_th4                :8 ,	// 15:8
	reg_psp_blend_y_th3                :8 ,	// 23:16
	reg_psp_blend_y_th2                :8 ;	// 31:24
}PE_O18_REG_DC_BNR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90038a8L reg_mnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_small_mmd_flat_th              :8 ,	// 7:0
	reg_large_mmd_flat_th              :8 ,	// 15:8
	reserved01                         :12,	// reserved
	reg_mmd_chroma_gain_en             :1 ,	// 28
	reg_mmd_dist_kernel_width          :2 ,	// 30:29
	reg_mmd_dist_gain_en               :1 ;	// 31
}PE_O18_REG_MNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90038acL reg_mnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dist_gain_x3                   :8 ,	// 7:0
	reg_dist_gain_x2                   :8 ,	// 15:8
	reg_dist_gain_x1                   :8 ,	// 23:16
	reg_dist_gain_x0                   :8 ;	// 31:24
}PE_O18_REG_MNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90038b0L reg_mnr_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dist_gain_y3                   :8 ,	// 7:0
	reg_dist_gain_y2                   :8 ,	// 15:8
	reg_dist_gain_y1                   :8 ,	// 23:16
	reg_dist_gain_y0                   :8 ;	// 31:24
}PE_O18_REG_MNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc90038b4L reg_mnr_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chroma_gain_x3                 :8 ,	// 7:0
	reg_chroma_gain_x2                 :8 ,	// 15:8
	reg_chroma_gain_x1                 :8 ,	// 23:16
	reg_chroma_gain_x0                 :8 ;	// 31:24
}PE_O18_REG_MNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc90038b8L reg_mnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chroma_gain_y3                 :8 ,	// 7:0
	reg_chroma_gain_y2                 :8 ,	// 15:8
	reg_chroma_gain_y1                 :8 ,	// 23:16
	reg_chroma_gain_y0                 :8 ;	// 31:24
}PE_O18_REG_MNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90038bcL reg_cti_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_en                         :1 ,	// 0 
	reg_lti_clipping_mode              :1 ,	// 1 
	reserved01                         :1 ,	// reserved
	reg_lti_tap                        :2 ,	// 4:3
	reserved02                         :3 ,	// reserved
	reg_lti_gain                       :8 ,	// 15:8
	reserved03                         :4 ,	// reserved
	reg_ycm_c_gain                     :4 ,	// 23:20
	reg_ycm_y_gain                     :4 ,	// 27:24
	reg_ycm_band_sel                   :3 ,	// 30:28
	reg_ycm_en                         :1 ;	// 31
}PE_O18_REG_CTI_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90038c0L reg_cti_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lti_coring_th0                 :8 ,	// 7:0
	reg_lti_coring_th1                 :8 ,	// 15:8
	reg_lti_coring_sm                  :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_lti_tap2                       :2 ,	// 21:20
	reserved02                         :2 ,	// reserved
	reg_ycm_diff_th                    :8 ;	// 31:24
}PE_O18_REG_CTI_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90038c4L reg_psv_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_h_x_th0             :8 ,	// 7:0
	reg_fil_motion_h_x_th1             :8 ,	// 15:8
	reg_fil_motion_h_x_th2             :8 ,	// 23:16
	reg_fil_motion_h_x_th3             :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90038c8L reg_psv_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_h_y_th0             :8 ,	// 7:0
	reg_fil_motion_h_y_th1             :8 ,	// 15:8
	reg_fil_motion_h_y_th2             :8 ,	// 23:16
	reg_fil_motion_h_y_th3             :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90038ccL reg_psv_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_v_x_th0             :8 ,	// 7:0
	reg_fil_motion_v_x_th1             :8 ,	// 15:8
	reg_fil_motion_v_x_th2             :8 ,	// 23:16
	reg_fil_motion_v_x_th3             :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90038d0L reg_psv_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_v_y_th0             :8 ,	// 7:0
	reg_fil_motion_v_y_th1             :8 ,	// 15:8
	reg_fil_motion_v_y_th2             :8 ,	// 23:16
	reg_fil_motion_v_y_th3             :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90038d4L reg_psv_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_x_th0               :8 ,	// 7:0
	reg_fil_motion_x_th1               :8 ,	// 15:8
	reg_fil_motion_x_th2               :8 ,	// 23:16
	reg_fil_motion_x_th3               :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90038d8L reg_psv_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_y_th0               :8 ,	// 7:0
	reg_fil_motion_y_th1               :8 ,	// 15:8
	reg_fil_motion_y_th2               :8 ,	// 23:16
	reg_fil_motion_y_th3               :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90038dcL reg_psv_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_en_h_protect                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_h_blk_cnt_th                   :3 ;	// 6:4
}PE_O18_REG_PSV_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90038e0L reg_psv_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_avg_th_hgh                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_h_avg_th_low                   :10;	// 25:16
}PE_O18_REG_PSV_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90038e4L reg_psv_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_h_pos_gain_3                   :8 ,	// 7:0
	reg_h_pos_gain_2                   :8 ,	// 15:8
	reg_h_pos_gain_1                   :8 ,	// 23:16
	reg_h_pos_gain_0                   :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc90038e8L reg_psv_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_en_v_protect                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_en_v_local_sm                  :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_b_blk_ftr_sm_tb                :4 ;	// 11:8
}PE_O18_REG_PSV_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc90038ecL reg_psv_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_v_avg_th_hgh                   :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_v_avg_th_low                   :10;	// 25:16
}PE_O18_REG_PSV_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90038f0L reg_psv_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_v_pos_gain_3                   :8 ,	// 7:0
	reg_v_pos_gain_2                   :8 ,	// 15:8
	reg_v_pos_gain_1                   :8 ,	// 23:16
	reg_v_pos_gain_0                   :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90038f4L reg_psv_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_master_gain_v_c                :8 ,	// 7:0
	reg_master_gain_v_y                :8 ,	// 15:8
	reg_master_gain_h_c                :8 ,	// 23:16
	reg_master_gain_h_y                :8 ;	// 31:24
}PE_O18_REG_PSV_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90038f8L reg_psv_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bnr_gain_debug_v_en                :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	bnr_gain_debug_h_en                :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_blur_sel                       :3 ,	// 10:8
	reserved03                         :1 ,	// reserved
	reg_status_shift                   :4 ,	// 15:12
	reg_pos_force_v                    :3 ,	// 18:16
	reserved04                         :1 ,	// reserved
	reg_pos_force_h                    :3 ,	// 22:20
	reg_pos_force_en                   :1 ,	// 23
	reg_debug_map_mode                 :3 ,	// 26:24
	reg_debug_map_en                   :1 ,	// 27
	reserved05                         :2 ,	// reserved
	reg_psv_bnr_en_c                   :1 ,	// 30
	reg_psv_bnr_en_y                   :1 ;	// 31
}PE_O18_REG_PSV_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9003900L reg_psv_status_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_8_hist_else                      :16,	// 15:0
	h_8_hist_max                       :16;	// 31:16
}PE_O18_REG_PSV_STATUS_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003904L reg_psv_status_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_8_hist_else                      :16,	// 15:0
	v_8_hist_max                       :16;	// 31:16
}PE_O18_REG_PSV_STATUS_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003908L reg_psv_status_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_16_f_hist_else                   :16,	// 15:0
	h_16_f_hist_max                    :16;	// 31:16
}PE_O18_REG_PSV_STATUS_2_T;
/*-----------------------------------------------------------------------------
                             0xc900390cL reg_psv_status_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_16_e_hist_else                   :16,	// 15:0
	h_16_e_hist_max                    :16;	// 31:16
}PE_O18_REG_PSV_STATUS_3_T;
/*-----------------------------------------------------------------------------
                             0xc9003910L reg_psv_status_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_16_f_hist_else                   :16,	// 15:0
	v_16_f_hist_max                    :16;	// 31:16
}PE_O18_REG_PSV_STATUS_4_T;
/*-----------------------------------------------------------------------------
                             0xc9003914L reg_psv_status_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_16_e_hist_else                   :16,	// 15:0
	v_16_e_hist_max                    :16;	// 31:16
}PE_O18_REG_PSV_STATUS_5_T;


/*-----------------------------------------------------------------------------
                             0xc9003b00L psp_ctrl00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_img_wid                        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_img_hei                        :12,	// 27:16
	reserved02                         :3 ,	// reserved
	reg_valid_mask                     :1 ;	// 31
}PE_O18_PSP_CTRL00_T;
/*-----------------------------------------------------------------------------
                             0xc9003b04L psp_ctrl01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blk_wid                        :6 ,	// 5:0
	reserved01                         :2 ,	// reserved
	reg_blk_hei                        :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_l5_wid                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_l5_hei                         :7 ;	// 30:24
}PE_O18_PSP_CTRL01_T;
/*-----------------------------------------------------------------------------
                             0xc9003b08L psp_ctrl02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vs_inv                         :1 ,	// 0 
	reg_psp_en                         :1 ,	// 1 
	reg_hist_sel                       :2 ,	// 3:2
	reg_repeat_h_num                   :5 ,	// 8:4
	reserved01                         :1 ,	// reserved
	reg_repeat_v_num                   :5 ,	// 14:10
	reserved02                         :1 ,	// reserved
	reg_margin_hei                     :8 ,	// 23:16
	reg_margin_wid                     :8 ;	// 31:24
}PE_O18_PSP_CTRL02_T;
/*-----------------------------------------------------------------------------
                             0xc9003b0cL edge_th                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_vh                        :13,	// 12:0
	reg_line_sel                       :1 ,	// 13
	reserved01                         :2 ,	// reserved
	reg_w_box_th                       :8 ,	// 23:16
	reg_h_box_th                       :8 ;	// 31:24
}PE_O18_EDGE_TH_T;
/*-----------------------------------------------------------------------------
                             0xc9003b10L fg_position                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_w1_pos                   :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_force_h1_pos                   :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_force_w2_pos                   :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_force_h2_pos                   :7 ,	// 30:24
	reg_force_pos_en                   :1 ;	// 31
}PE_O18_FG_POSITION_T;
/*-----------------------------------------------------------------------------
                             0xc9003b14L perspect_lut_x0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_0;	// 31:0
}PE_O18_PERSPECT_LUT_X0_T;
/*-----------------------------------------------------------------------------
                             0xc9003b18L perspect_lut_x1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_1;	// 31:0
}PE_O18_PERSPECT_LUT_X1_T;
/*-----------------------------------------------------------------------------
                             0xc9003b1cL perspect_lut_x2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_2;	// 31:0
}PE_O18_PERSPECT_LUT_X2_T;
/*-----------------------------------------------------------------------------
                             0xc9003b20L perspect_lut_x3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_3;	// 31:0
}PE_O18_PERSPECT_LUT_X3_T;
/*-----------------------------------------------------------------------------
                             0xc9003b24L perspect_lut_y0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_0;	// 31:0
}PE_O18_PERSPECT_LUT_Y0_T;
/*-----------------------------------------------------------------------------
                             0xc9003b28L perspect_lut_y1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_1;	// 31:0
}PE_O18_PERSPECT_LUT_Y1_T;
/*-----------------------------------------------------------------------------
                             0xc9003b2cL perspect_lut_y2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_2;	// 31:0
}PE_O18_PERSPECT_LUT_Y2_T;
/*-----------------------------------------------------------------------------
                             0xc9003b30L perspect_lut_y3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_3;	// 31:0
}PE_O18_PERSPECT_LUT_Y3_T;
/*-----------------------------------------------------------------------------
                             0xc9003b34L prob_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bg_prob_factor                 :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_fg_prob_factor                 :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_stat_flat_w_mul                :4 ,	// 19:16
	reg_stat_flat_h_mul                :4 ;	// 23:20
}PE_O18_PROB_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b38L ellips_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_master                 :8 ,	// 7:0
	reg_e_mul_a                        :9 ,	// 16:8
	reserved01                         :3 ,	// reserved
	reg_e_mul_b                        :9 ,	// 28:20
	reserved02                         :2 ,	// reserved
	reg_fg_mul_ellipse_en              :1 ;	// 31
}PE_O18_ELLIPS_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b3cL prob_diff_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_offset                 :8 ,	// 7:0
	reg_bg_diff_mul                    :10,	// 17:8
	reserved01                         :2 ,	// reserved
	reg_fg_diff_mul                    :10;	// 29:20
}PE_O18_PROB_DIFF_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b40L object_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_p_offset                       :8 ,	// 7:0
	reg_e_offset                       :8 ,	// 15:8
	reg_dbg_map_sel                    :3 ;	// 18:16
}PE_O18_OBJECT_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b44L blur_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_en                        :1 ;	// 0 
}PE_O18_BLUR_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b48L display_debug_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_disp_gain_l0                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_disp_gain_vrtx                 :1 ;	// 4 
}PE_O18_DISPLAY_DEBUG_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9003b4cL psp_iir                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_iir_alpha                  :6 ,	// 5:0
	reserved01                         :25,	// reserved
	reg_psp_gain_init                  :1 ;	// 31
}PE_O18_PSP_IIR_T;
/*-----------------------------------------------------------------------------
                             0xc9003b50L psp_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	psp_gain                           :1 ,	// 0 
	psp_gain_dbg                       :1 ;	// 1 
}PE_O18_PSP_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc9003b54L psp_dbg_mon00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h1_pos                             :7 ,	// 6:0
	h2_pos                             :7 ,	// 13:7
	w1_pos                             :7 ,	// 20:14
	w2_pos                             :7 ,	// 27:21
	r_edge_total_lsb                   :4 ;	// 31:28
}PE_O18_PSP_DBG_MON00_T;
/*-----------------------------------------------------------------------------
                             0xc9003b58L psp_dbg_mon01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_max_flat_length_h              :7 ,	// 6:0
	out_max_flat_length_w              :7 ,	// 13:7
	r_edge_total_msb                   :18;	// 31:14
}PE_O18_PSP_DBG_MON01_T;
/*-----------------------------------------------------------------------------
                             0xc9003b5cL vrtx_cpc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vrtx_gain_tl_i                 :8 ,	// 7:0
	reg_vrtx_gain_tr_i                 :8 ,	// 15:8
	reg_vrtx_gain_bl_i                 :8 ,	// 23:16
	reg_vrtx_gain_br_i                 :8 ;	// 31:24
}PE_O18_VRTX_CPC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9003b60L blur_hcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef1                             :10;	// 25:16
}PE_O18_BLUR_HCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc9003b64L blur_hcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef3                             :10;	// 25:16
}PE_O18_BLUR_HCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc9003b68L blur_hcoeff45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef4                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef5                             :10;	// 25:16
}PE_O18_BLUR_HCOEFF45_T;
/*-----------------------------------------------------------------------------
                             0xc9003b6cL blur_hcoeff67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef6                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef7                             :10;	// 25:16
}PE_O18_BLUR_HCOEFF67_T;
/*-----------------------------------------------------------------------------
                             0xc9003b70L blur_hcoef8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef8                             :10;	// 9:0
}PE_O18_BLUR_HCOEF8_T;
/*-----------------------------------------------------------------------------
                             0xc9003b74L blur_vcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef1                             :10;	// 25:16
}PE_O18_BLUR_VCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc9003b78L blur_vcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef3                             :10;	// 25:16
}PE_O18_BLUR_VCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc9003b7cL blur_vcoef4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef4                             :10;	// 9:0
}PE_O18_BLUR_VCOEF4_T;
/*-----------------------------------------------------------------------------
                             0xc9003b80L histogram_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_0_T;
/*-----------------------------------------------------------------------------
                             0xc9003b84L histogram_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_1_T;
/*-----------------------------------------------------------------------------
                             0xc9003b88L histogram_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_2_T;
/*-----------------------------------------------------------------------------
                             0xc9003b8cL histogram_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_3_T;
/*-----------------------------------------------------------------------------
                             0xc9003b90L histogram_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_4_T;
/*-----------------------------------------------------------------------------
                             0xc9003b94L histogram_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_5_T;
/*-----------------------------------------------------------------------------
                             0xc9003b98L histogram_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_6_T;
/*-----------------------------------------------------------------------------
                             0xc9003b9cL histogram_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_7_T;
/*-----------------------------------------------------------------------------
                             0xc9003ba0L histogram_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_8_T;
/*-----------------------------------------------------------------------------
                             0xc9003ba4L histogram_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_9_T;
/*-----------------------------------------------------------------------------
                             0xc9003ba8L histogram_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_10_T;
/*-----------------------------------------------------------------------------
                             0xc9003bacL histogram_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_11_T;
/*-----------------------------------------------------------------------------
                             0xc9003bb0L histogram_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_12_T;
/*-----------------------------------------------------------------------------
                             0xc9003bb4L histogram_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_13_T;
/*-----------------------------------------------------------------------------
                             0xc9003bb8L histogram_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_14_T;
/*-----------------------------------------------------------------------------
                             0xc9003bbcL histogram_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_15_T;
/*-----------------------------------------------------------------------------
                             0xc9003bc0L histogram_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_16_T;
/*-----------------------------------------------------------------------------
                             0xc9003bc4L histogram_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_17_T;
/*-----------------------------------------------------------------------------
                             0xc9003bc8L histogram_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_18_T;
/*-----------------------------------------------------------------------------
                             0xc9003bccL histogram_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_19_T;
/*-----------------------------------------------------------------------------
                             0xc9003bd0L histogram_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_20_T;
/*-----------------------------------------------------------------------------
                             0xc9003bd4L histogram_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_21_T;
/*-----------------------------------------------------------------------------
                             0xc9003bd8L histogram_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_22_T;
/*-----------------------------------------------------------------------------
                             0xc9003bdcL histogram_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_23_T;
/*-----------------------------------------------------------------------------
                             0xc9003be0L histogram_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_24_T;
/*-----------------------------------------------------------------------------
                             0xc9003be4L histogram_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_25_T;
/*-----------------------------------------------------------------------------
                             0xc9003be8L histogram_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_26_T;
/*-----------------------------------------------------------------------------
                             0xc9003becL histogram_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_27_T;
/*-----------------------------------------------------------------------------
                             0xc9003bf0L histogram_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_28_T;
/*-----------------------------------------------------------------------------
                             0xc9003bf4L histogram_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_29_T;
/*-----------------------------------------------------------------------------
                             0xc9003bf8L histogram_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_30_T;
/*-----------------------------------------------------------------------------
                             0xc9003bfcL histogram_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O18_HISTOGRAM_31_T;

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
}PE_O18_CTRL_M0_Y_LEVEL_CTRL_T;

typedef struct
{ 
	PE_O18_PE0_ND_LOAD_T                              pe0_load;	//0x0000
	PE_O18_PE0_ND_INTR_T                              pe0_intr;	//0x0004
	PE_O18_PE0_ND_STATUS0_T                           pe0_status0;	//0x0008
	PE_O18_PE0_ND_STATUS1_T                           pe0_status1;	//0x000C
	PE_O18_PE0_ND_OPMODE_T                            pe0_opmode;	//0x0010
	PE_O18_PE0_ND_SRC_SIZE_T                          pe0_src_size;	//0x0014
	PE_O18_PE0_FIELD_T                                pe0_field;	//0x0018
	PE_O18_PE0_DEBUG_LEND_CTRL_T                      pe0_debug_lend_ctrl;	//0x001C
	PE_O18_PE0_ND_IN_OFFSET_T                         pe0_in_offset;	//0x0020
	PE_O18_PE0_ND_IN_SIZE_T                           pe0_in_size;	//0x0024
	PE_O18_FBC_CTRL0_T                                fbc_ctrl0;	//0x0028
	PE_O18_FBC_CTRL1_T                                fbc_ctrl1;	//0x002C
	PE_O18_PE0_DEBUG_MEM_REQ_T                        pe0_debug_mem_req;	//0x0030
	PE_O18_PE0_DEBUG_LREQ_DLY_T                       pe0_debug_lreq_dly;	//0x0034
	PE_O18_TNRW_IN_OFFSET_T                           tnrw_in_offset;	//0x0038
	PE_O18_TNRW_OUT_SIZE_T                            tnrw_out_size;	//0x003C
	PE_O18_TNR_CTRL_00_T                              tnr_ctrl_00;	//0x0040
	PE_O18_TNR_CTRL_01_T                              tnr_ctrl_01;	//0x0044
	PE_O18_TNR_CTRL_02_T                              tnr_ctrl_02;	//0x0048
	PE_O18_TNR_CTRL_03_T                              tnr_ctrl_03;	//0x004C
	PE_O18_TNR_CTRL_04_T                              tnr_ctrl_04;	//0x0050
	PE_O18_TNR_CTRL_05_T                              tnr_ctrl_05;	//0x0054
	PE_O18_TNR_CTRL_06_T                              tnr_ctrl_06;	//0x0058
	PE_O18_TNR_CTRL_07_T                              tnr_ctrl_07;	//0x005C
	PE_O18_TNR_CTRL_08_T                              tnr_ctrl_08;	//0x0060
	PE_O18_TNR_CTRL_09_T                              tnr_ctrl_09;	//0x0064
	PE_O18_TNR_CTRL_10_T                              tnr_ctrl_10;	//0x0068
	PE_O18_TNR_CTRL_11_T                              tnr_ctrl_11;	//0x006C
	PE_O18_TNR_CTRL_12_T                              tnr_ctrl_12;	//0x0070
	PE_O18_TNR_CTRL_13_T                              tnr_ctrl_13;	//0x0074
	PE_O18_TNR_CTRL_14_T                              tnr_ctrl_14;	//0x0078
	PE_O18_TNR_CTRL_15_T                              tnr_ctrl_15;	//0x007C
	PE_O18_TNR_CTRL_16_T                              tnr_ctrl_16;	//0x0080
	PE_O18_TNR_CTRL_17_T                              tnr_ctrl_17;	//0x0084
	PE_O18_TNR_CTRL_18_T                              tnr_ctrl_18;	//0x0088
	PE_O18_TNR_CTRL_19_T                              tnr_ctrl_19;	//0x008C
	PE_O18_TNR_CTRL_20_T                              tnr_ctrl_20;	//0x0090
	PE_O18_TNR_CTRL_21_T                              tnr_ctrl_21;	//0x0094
	PE_O18_TNR_CTRL_22_T                              tnr_ctrl_22;	//0x0098
	PE_O18_TNR_CTRL_23_T                              tnr_ctrl_23;	//0x009C
	PE_O18_TNR_CTRL_24_T                              tnr_ctrl_24;	//0x00A0
	PE_O18_TNR_CTRL_25_T                              tnr_ctrl_25;	//0x00A4
	PE_O18_TNR_CTRL_26_T                              tnr_ctrl_26;	//0x00A8
	PE_O18_TNR_CTRL_27_T                              tnr_ctrl_27;	//0x00AC
	PE_O18_TNR_CTRL_28_T                              tnr_ctrl_28;	//0x00B0
	PE_O18_TNR_CTRL_29_T                              tnr_ctrl_29;	//0x00B4
	PE_O18_TNR_CTRL_30_T                              tnr_ctrl_30;	//0x00B8
	PE_O18_TNR_CTRL_31_T                              tnr_ctrl_31;	//0x00BC
	PE_O18_TNR_STATUS_00_T                            tnr_status_00;	//0x00C0
	PE_O18_TNR_STATUS_01_T                            tnr_status_01;	//0x00C4
	PE_O18_TNR_STATUS_02_T                            tnr_status_02;	//0x00C8
	PE_O18_TNR_STATUS_03_T                            tnr_status_03;	//0x00CC
	PE_O18_TNR_MAIN_LUT_00_T                          tnr_main_lut_00;	//0x00D0
	PE_O18_TNR_MAIN_LUT_01_T                          tnr_main_lut_01;	//0x00D4
	UINT32                                            reserved00;	//0x00D8-0x00D8
	PE_O18_TNR_STATUS_04_T                            tnr_status_04;	//0x00DC
	PE_O18_TNR_CTRL_32_T                              tnr_ctrl_32;	//0x00E0
	PE_O18_TNR_CTRL_33_T                              tnr_ctrl_33;	//0x00E4
	PE_O18_TNR_CTRL_34_T                              tnr_ctrl_34;	//0x00E8
	PE_O18_TNR_CTRL_35_T                              tnr_ctrl_35;	//0x00EC
	PE_O18_TNR_CTRL_36_T                              tnr_ctrl_36;	//0x00F0
	PE_O18_TNR_CTRL_37_T                              tnr_ctrl_37;	//0x00F4
	PE_O18_TNR_CTRL_38_T                              tnr_ctrl_38;	//0x00F8
	PE_O18_TNR_CTRL_39_T                              tnr_ctrl_39;	//0x00FC
	PE_O18_IPC_CTRL_00_T                              ipc_ctrl_00;	//0x0100
	PE_O18_IPC_CTRL_01_T                              ipc_ctrl_01;	//0x0104
	PE_O18_IPC_CTRL_02_T                              ipc_ctrl_02;	//0x0108
	PE_O18_IPC_CTRL_03_T                              ipc_ctrl_03;	//0x010C
	PE_O18_IPC_CTRL_04_T                              ipc_ctrl_04;	//0x0110
	PE_O18_IPC_CTRL_05_T                              ipc_ctrl_05;	//0x0114
	PE_O18_IPC_CTRL_06_T                              ipc_ctrl_06;	//0x0118
	PE_O18_IPC_CTRL_07_T                              ipc_ctrl_07;	//0x011C
	PE_O18_IPC_CTRL_08_T                              ipc_ctrl_08;	//0x0120
	PE_O18_IPC_CTRL_09_T                              ipc_ctrl_09;	//0x0124
	PE_O18_IPC_CTRL_10_T                              ipc_ctrl_10;	//0x0128
	PE_O18_IPC_CTRL_11_T                              ipc_ctrl_11;	//0x012C
	PE_O18_IPC_CTRL_12_T                              ipc_ctrl_12;	//0x0130
	PE_O18_IPC_CTRL_13_T                              ipc_ctrl_13;	//0x0134
	PE_O18_IPC_CTRL_14_T                              ipc_ctrl_14;	//0x0138
	PE_O18_IPC_CTRL_15_T                              ipc_ctrl_15;	//0x013C
	PE_O18_IPC_CTRL_16_T                              ipc_ctrl_16;	//0x0140
	PE_O18_IPC_CTRL_17_T                              ipc_ctrl_17;	//0x0144
	PE_O18_IPC_CTRL_18_T                              ipc_ctrl_18;	//0x0148
	PE_O18_IPC_CTRL_19_T                              ipc_ctrl_19;	//0x014C
	PE_O18_IPC_STATUS_00_T                            ipc_status_00;	//0x0150
	PE_O18_IPC_STATUS_01_T                            ipc_status_01;	//0x0154
	PE_O18_IPC_STATUS_02_T                            ipc_status_02;	//0x0158
	PE_O18_IPC_STATUS_03_T                            ipc_status_03;	//0x015C
	PE_O18_CLC_CTRL_00_T                              clc_ctrl_00;	//0x0160
	PE_O18_CLC_CTRL_01_T                              clc_ctrl_01;	//0x0164
	PE_O18_CLC_CTRL_02_T                              clc_ctrl_02;	//0x0168
	PE_O18_CLC_CTRL_03_T                              clc_ctrl_03;	//0x016C
	PE_O18_CLC_CTRL_04_T                              clc_ctrl_04;	//0x0170
	PE_O18_CLC_CTRL_05_T                              clc_ctrl_05;	//0x0174
	PE_O18_CLC_CTRL_06_T                              clc_ctrl_06;	//0x0178
	PE_O18_CLC_STAT_00_T                              clc_stat_00;	//0x017C
	PE_O18_IPC_CTRL_34_T                              ipc_ctrl_34;	//0x0180
	PE_O18_IPC_CTRL_35_T                              ipc_ctrl_35;	//0x0184
	PE_O18_IPC_CTRL_36_T                              ipc_ctrl_36;	//0x0188
	PE_O18_IPC_CTRL_37_T                              ipc_ctrl_37;	//0x018C
	PE_O18_IPC_CTRL_38_T                              ipc_ctrl_38;	//0x0190
	PE_O18_IPC_CTRL_39_T                              ipc_ctrl_39;	//0x0194
	PE_O18_IPC_CTRL_40_T                              ipc_ctrl_40;	//0x0198
	PE_O18_IPC_CTRL_41_T                              ipc_ctrl_41;	//0x019C
	PE_O18_IPC_CTRL_42_T                              ipc_ctrl_42;	//0x01A0
	PE_O18_IPC_CTRL_43_T                              ipc_ctrl_43;	//0x01A4
	PE_O18_IPC_CTRL_44_T                              ipc_ctrl_44;	//0x01A8
	PE_O18_IPC_CTRL_45_T                              ipc_ctrl_45;	//0x01AC
	PE_O18_IPC_CTRL_46_T                              ipc_ctrl_46;	//0x01B0
	PE_O18_IPC_CTRL_47_T                              ipc_ctrl_47;	//0x01B4
	PE_O18_IPC_CTRL_48_T                              ipc_ctrl_48;	//0x01B8
	PE_O18_IPC_CTRL_49_T                              ipc_ctrl_49;	//0x01BC
	PE_O18_IPC_CTRL_50_T                              ipc_ctrl_50;	//0x01C0
	PE_O18_IPC_CTRL_51_T                              ipc_ctrl_51;	//0x01C4
	PE_O18_IPC_CTRL_52_T                              ipc_ctrl_52;	//0x01C8
	PE_O18_IPC_CTRL_53_T                              ipc_ctrl_53;	//0x01CC
	PE_O18_IPC_CTRL_54_T                              ipc_ctrl_54;	//0x01D0
	PE_O18_IPC_CTRL_55_T                              ipc_ctrl_55;	//0x01D4
	UINT32                                            reserved01[2];	//0x01D8-0x01DC
	PE_O18_MMD_CTRL_T                                 mmd_ctrl;	//0x01E0
	UINT32                                            reserved02[3];	//0x01E4-0x01EC
	PE_O18_IPC_CTRL_20_T                              ipc_ctrl_20;	//0x01F0
	PE_O18_IPC_CTRL_21_T                              ipc_ctrl_21;	//0x01F4
	PE_O18_IPC_CTRL_22_T                              ipc_ctrl_22;	//0x01F8
	PE_O18_IPC_CTRL_23_T                              ipc_ctrl_23;	//0x01FC
	PE_O18_IPC_CTRL_24_T                              ipc_ctrl_24;	//0x0200
	PE_O18_IPC_CTRL_25_T                              ipc_ctrl_25;	//0x0204
	PE_O18_IPC_CTRL_26_T                              ipc_ctrl_26;	//0x0208
	PE_O18_IPC_CTRL_27_T                              ipc_ctrl_27;	//0x020C
	PE_O18_IPC_CTRL_28_T                              ipc_ctrl_28;	//0x0210
	PE_O18_IPC_CTRL_29_T                              ipc_ctrl_29;	//0x0214
	PE_O18_IPC_CTRL_30_T                              ipc_ctrl_30;	//0x0218
	PE_O18_IPC_CTRL_31_T                              ipc_ctrl_31;	//0x021C
	PE_O18_IPC_CTRL_32_T                              ipc_ctrl_32;	//0x0220
	PE_O18_IPC_CTRL_33_T                              ipc_ctrl_33;	//0x0224
	PE_O18_IPC_STATUS_04_T                            ipc_status_04;	//0x0228
	PE_O18_IPC_STATUS_05_T                            ipc_status_05;	//0x022C
	PE_O18_IPC_STATUS_06_T                            ipc_status_06;	//0x0230
	PE_O18_IPC_STATUS_07_T                            ipc_status_07;	//0x0234
	PE_O18_IPC_STATUS_08_T                            ipc_status_08;	//0x0238
	PE_O18_IPC_STATUS_09_T                            ipc_status_09;	//0x023C
	PE_O18_TPD_CTRL_00_T                              tpd_ctrl_00;	//0x0240
	PE_O18_TPD_CTRL_01_T                              tpd_ctrl_01;	//0x0244
	PE_O18_TPD_CTRL_02_T                              tpd_ctrl_02;	//0x0248
	PE_O18_TPD_CTRL_03_T                              tpd_ctrl_03;	//0x024C
	PE_O18_TPD_CTRL_04_T                              tpd_ctrl_04;	//0x0250
	PE_O18_TPD_CTRL_05_T                              tpd_ctrl_05;	//0x0254
	PE_O18_TPD_CTRL_06_T                              tpd_ctrl_06;	//0x0258
	PE_O18_TPD_CTRL_07_T                              tpd_ctrl_07;	//0x025C
	PE_O18_TPD_CTRL_08_T                              tpd_ctrl_08;	//0x0260
	PE_O18_TPD_CTRL_09_T                              tpd_ctrl_09;	//0x0264
	PE_O18_TPD_STAT_00_T                              tpd_stat_00;	//0x0268
	PE_O18_CLC_CTRL_07_T                              clc_ctrl_07;	//0x026C
	PE_O18_BBD_CTRL_00_T                              bbd_ctrl_00;	//0x0270
	PE_O18_BBD_CTRL_01_T                              bbd_ctrl_01;	//0x0274
	PE_O18_BBD_CTRL_02_T                              bbd_ctrl_02;	//0x0278
	PE_O18_BBD_STAT_00_T                              bbd_stat_00;	//0x027C
	PE_O18_BBD_STAT_01_T                              bbd_stat_01;	//0x0280
	PE_O18_APL_STAT_00_T                              apl_stat_00;	//0x0284
	PE_O18_PE1_FSW_CTRL_00_T                          pe1_fsw_ctrl_00;
	PE_O18_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_01;//0x0288-0x028C
	PE_O18_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0x0290
	PE_O18_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0x0294
	PE_O18_LVCRTL_CTRL_00_T                           lvcrtl_ctrl_00;	//0x0298
	UINT32                                            reserved04;	//0x029C-0x029C
	PE_O18_TNR_STATUS_05_T                            tnr_status_05;	//0x02A0
	PE_O18_TNR_STATUS_06_T                            tnr_status_06;	//0x02A4
	PE_O18_TNR_STATUS_07_T                            tnr_status_07;	//0x02A8
	PE_O18_TNR_STATUS_08_T                            tnr_status_08;	//0x02AC
	UINT32                                            reserved05[4];	//0x02B0-0x02BC
	PE_O18_TNR_RESET_T                                tnr_reset;	//0x02C0
	UINT32                                            reserved06[3];	//0x02C4-0x02CC
	PE_O18_TNR_CTRL_40_T                              tnr_ctrl_40;	//0x02D0
	PE_O18_TNR_CTRL_41_T                              tnr_ctrl_41;	//0x02D4
	PE_O18_TNR_CTRL_42_T                              tnr_ctrl_42;	//0x02D8
	PE_O18_TNR_CTRL_43_T                              tnr_ctrl_43;	//0x02DC
	PE_O18_TNR_CTRL_44_T                              tnr_ctrl_44;	//0x02E0
	PE_O18_TNR_CTRL_45_T                              tnr_ctrl_45;	//0x02E4
	PE_O18_TNR_CTRL_46_T                              tnr_ctrl_46;	//0x02E8
	PE_O18_TNR_CTRL_47_T                              tnr_ctrl_47;	//0x02EC
	PE_O18_TNR_CTRL_48_T                              tnr_ctrl_48;	//0x02F0
	UINT32                                            reserved07[3];	//0x02F4-0x02FC
	PE_O18_TNR_NE_STAT_00_T                           tnr_ne_stat_00;	//0x0300
	PE_O18_TNR_NE_STAT_01_T                           tnr_ne_stat_01;	//0x0304
	PE_O18_TNR_NE_STAT_02_T                           tnr_ne_stat_02;	//0x0308
	PE_O18_TNR_NE_STAT_03_T                           tnr_ne_stat_03;	//0x030C
	PE_O18_TNR_NE_STAT_04_T                           tnr_ne_stat_04;	//0x0310
	PE_O18_TNR_NE_STAT_05_T                           tnr_ne_stat_05;	//0x0314
	PE_O18_TNR_NE_STAT_06_T                           tnr_ne_stat_06;	//0x0318
	PE_O18_TNR_NE_STAT_07_T                           tnr_ne_stat_07;	//0x031C
	PE_O18_TNR_NE_STAT_08_T                           tnr_ne_stat_08;	//0x0320
	UINT32                                            reserved08[3];	//0x0324-0x032C
	PE_O18_TNR_FRC_RMV_00_T                           tnr_frc_rmv_00;	//0x0330
	PE_O18_TNR_FRC_RMV_01_T                           tnr_frc_rmv_01;	//0x0334
	UINT32                                            reserved206[2];	//0x338-0x33c
	PE_O18_TNR_DECON_CTRL_00_T                        tnr_decon_ctrl_00;	//0x0340
	PE_O18_TNR_DECON_CTRL_01_T                        tnr_decon_ctrl_01;	//0x0344
	PE_O18_TNR_DECON_CTRL_02_T                        tnr_decon_ctrl_02;	//0x0348
	PE_O18_TNR_DECON_CTRL_03_T                        tnr_decon_ctrl_03;	//0x034C
	PE_O18_TNR_DECON_CTRL_04_T                        tnr_decon_ctrl_04;	//0x0350
	PE_O18_TNR_DECON_CTRL_05_T                        tnr_decon_ctrl_05;	//0x0354
	PE_O18_TNR_DECON_CTRL_06_T                        tnr_decon_ctrl_06;	//0x0358
	PE_O18_TNR_DECON_CTRL_07_T                        tnr_decon_ctrl_07;	//0x035C
	PE_O18_TNR_DECON_CTRL_08_T                        tnr_decon_ctrl_08;	//0x0360
	PE_O18_TNR_DECON_CTRL_09_T                        tnr_decon_ctrl_09;	//0x0364
	PE_O18_TNR_DECON_CTRL_10_T                        tnr_decon_ctrl_10;	//0x0368
	PE_O18_TNR_DECON_CTRL_11_T                        tnr_decon_ctrl_11;	//0x036C
	UINT32                                            reserved218[4];	//0x370-0x37c
	PE_O18_ND_FSW_CTRL_00_T                           nd_fsw_ctrl_00;	//0x0380
	PE_O18_ND_FSW_CTRL_01_T                           nd_fsw_ctrl_01;	//0x0384
	PE_O18_ND_FSW_CTRL_02_T                           nd_fsw_ctrl_02;	//0x0388
	PE_O18_ND_FSW_CTRL_03_T                           nd_fsw_ctrl_03;	//0x038C
	PE_O18_TNR_ETC_CTRL_00_T                          tnr_etc_ctrl_00;	//0x0390
	PE_O18_TNR_ETC_CTRL_01_T                          tnr_etc_ctrl_01;	//0x0394
	PE_O18_TNR_ETC_CTRL_02_T                          tnr_etc_ctrl_02;	//0x0398
	PE_O18_TNR_ETC_CTRL_03_T                          tnr_etc_ctrl_03;	//0x039C
	PE_O18_TNR_CTRL_56_T                              tnr_ctrl_56;	//0x03A0
	PE_O18_TNR_CTRL_57_T                              tnr_ctrl_57;	//0x03A4
	PE_O18_TNR_CTRL_58_T                              tnr_ctrl_58;	//0x03A8
	PE_O18_TNR_CTRL_59_T                              tnr_ctrl_59;	//0x03AC
	PE_O18_TNR_CTRL_60_T                              tnr_ctrl_60;	//0x03B0
	PE_O18_TNR_CTRL_61_T                              tnr_ctrl_61;	//0x03B4
	PE_O18_PE0_DEBUG3_T                               pe0_debug3;	//0x03B8
	UINT32                                            reserved233;	//0x3bc
	PE_O18_FBC_CTRL2_T                                fbc_ctrl2;	//0x03C0
	PE_O18_FBC_CTRL3_T                                fbc_ctrl3;	//0x03C4
	UINT32                                            reserved235[2];	//0x3c8-0x3cc
	PE_O18_GFD_CTRL_00_T                              gfd_ctrl_00;	//0x03D0
	PE_O18_GFD_CTRL_01_T                              gfd_ctrl_01;	//0x03D4
	PE_O18_GFD_STAT_00_T                              gfd_stat_00;	//0x03D8
	PE_O18_GFD_STAT_01_T                              gfd_stat_01;	//0x03DC
	PE_O18_GFD_STAT_02_T                              gfd_stat_02;	//0x03E0
	PE_O18_GFD_STAT_03_T                              gfd_stat_03;	//0x03E4
}PE_ND_ND0_REG_O18_T;

typedef struct
{ 
	PE_O18_PE0_LOAD_T                                 pe0_load;	//0x0000
	PE_O18_PE0_INTR_T                                 pe0_intr;	//0x0004
	PE_O18_PE0_STATUS0_T                              pe0_status0;	//0x0008
	PE_O18_PE0_STATUS1_T                              pe0_status1;	//0x000C
	PE_O18_PE0_OPMODE_T                               pe0_opmode;	//0x0010
	PE_O18_PE0_IN_SIZE_T                              pe0_in_size;	//0x0014
	PE_O18_PE0_IN_OFFSET_T                            pe0_in_offset;	//0x0018
	PE_O18_PE0_OUT_SIZE_T                             pe0_out_size;	//0x001C
	PE_O18_WIN_CTRL_0_T                               win_ctrl_0;	//0x0020
	PE_O18_WIN_CTRL_1_T                               win_ctrl_1;	//0x0024
	PE_O18_WIN_CTRL_2_T                               win_ctrl_2;	//0x0028
	PE_O18_WIN_CTRL_3_T                               win_ctrl_3;	//0x002C
	PE_O18_CUP_CTRL_00_T                              cup_ctrl_00;	//0x0030
	PE_O18_CUP_CTRL_01_T                              cup_ctrl_01;	//0x0034
	PE_O18_CUP_CTRL_02_T                              cup_ctrl_02;	//0x0038
	UINT32                                            reserved00[5];	//0x003C-0x004C
	PE_O18__3DFD_CTRL_00_T                            _3dfd_ctrl_00;	//0x0050
	PE_O18__3DFD_CTRL_01_T                            _3dfd_ctrl_01;	//0x0054
	PE_O18__3DFD_CTRL_02_T                            _3dfd_ctrl_02;	//0x0058
	PE_O18__3DFD_CTRL_03_T                            _3dfd_ctrl_03;	//0x005C
	PE_O18__3DFD_STAT_00_T                            _3dfd_stat_00;	//0x0060
	PE_O18__3DFD_STAT_01_T                            _3dfd_stat_01;	//0x0064
	PE_O18__3DFD_STAT_02_T                            _3dfd_stat_02;	//0x0068
	PE_O18__3DFD_STAT_03_T                            _3dfd_stat_03;	//0x006C
	PE_O18__3DFD_STAT_04_T                            _3dfd_stat_04;	//0x0070
	PE_O18__3DFD_STAT_05_T                            _3dfd_stat_05;	//0x0074
	PE_O18__3DFD_STAT_06_T                            _3dfd_stat_06;	//0x0078
	PE_O18__3DFD_STAT_07_T                            _3dfd_stat_07;	//0x007C
	PE_O18_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0x0080
	PE_O18_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0x0084
	PE_O18_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0x0088
	PE_O18_REG_CTI_CTRL_0_T                           reg_cti_ctrl_0;	//0x008C
	PE_O18_REG_CTI_CTRL_1_T                           reg_cti_ctrl_1;	//0x0090
	PE_O18_DNR_MAX_CTRL_T                             dnr_max_ctrl;	//0x0094
	PE_O18_DNR_DBAR_CTRL_T                            dnr_dbar_ctrl;	//0x0098
	PE_O18_REG_C420_CTRL_T                            reg_c420_ctrl;	//0x009C
	PE_O18_MNR_CTRL_0_T                               mnr_ctrl_0;	//0x00A0
	PE_O18_MNR_CTRL_1_T                               mnr_ctrl_1;	//0x00A4
	PE_O18_MNR_CTRL_2_T                               mnr_ctrl_2;	//0x00A8
	PE_O18_MNR_CTRL_3_T                               mnr_ctrl_3;	//0x00AC
	PE_O18_MNR_CTRL_4_T                               mnr_ctrl_4;	//0x00B0
	PE_O18_MNR_CTRL_5_T                               mnr_ctrl_5;	//0x00B4
	PE_O18_DETAIL_CTRL_T                              detail_ctrl;	//0x00B8
	PE_O18_DC_BNR_CTRL_0_T                            dc_bnr_ctrl_0;	//0x00BC
	PE_O18_DC_BNR_CTRL_1_T                            dc_bnr_ctrl_1;	//0x00C0
	PE_O18_DC_BNR_CTRL_2_T                            dc_bnr_ctrl_2;	//0x00C4
	PE_O18_DC_BNR_CTRL_3_T                            dc_bnr_ctrl_3;	//0x00C8
	PE_O18_DC_BNR_CTRL_4_T                            dc_bnr_ctrl_4;	//0x00CC
	PE_O18_DC_BNR_CTRL_5_T                            dc_bnr_ctrl_5;	//0x00D0
	PE_O18_AC_BNR_CTRL_0_T                            ac_bnr_ctrl_0;	//0x00D4
	PE_O18_AC_BNR_CTRL_1_T                            ac_bnr_ctrl_1;	//0x00D8
	PE_O18_AC_BNR_CTRL_2_T                            ac_bnr_ctrl_2;	//0x00DC
	PE_O18_DNR_STAT_0_T                               dnr_stat_0;	//0x00E0
	PE_O18_AC_BNR_CTRL_3_T                            ac_bnr_ctrl_3;	//0x00E4
	PE_O18_AC_BNR_CTRL_4_T                            ac_bnr_ctrl_4;	//0x00E8
	PE_O18_DNR_STAT_1_T                               dnr_stat_1;	//0x00EC
	PE_O18_AC_BNR_CTRL_5_T                            ac_bnr_ctrl_5;	//0x00F0
	PE_O18_AC_BNR_CTRL_6_T                            ac_bnr_ctrl_6;	//0x00F4
	PE_O18_AC_BNR_CTRL_7_T                            ac_bnr_ctrl_7;	//0x00F8
	PE_O18_DNR_STAT_2_T                               dnr_stat_2;	//0x00FC
	PE_O18_AC_BNR_CTRL_8_T                            ac_bnr_ctrl_8;	//0x0100
	PE_O18_AC_BNR_CTRL_9_T                            ac_bnr_ctrl_9;	//0x0104
	PE_O18_AC_BNR_CTRL_10_T                           ac_bnr_ctrl_10;	//0x0108
	PE_O18_AC_BNR_CTRL_11_T                           ac_bnr_ctrl_11;	//0x010C
	PE_O18_AC_BNR_CTRL_12_T                           ac_bnr_ctrl_12;	//0x0110
	PE_O18_IFC_CTRL_0_T                               ifc_ctrl_0;	//0x0114
	PE_O18_IFC_CTRL_1_T                               ifc_ctrl_1;	//0x0118
	PE_O18_IFC_CTRL_2_T                               ifc_ctrl_2;	//0x011C
	PE_O18_IFC_CTRL_3_T                               ifc_ctrl_3;	//0x0120
	PE_O18_IFC_CTRL_4_T                               ifc_ctrl_4;	//0x0124
	PE_O18_IFC_CTRL_5_T                               ifc_ctrl_5;	//0x0128
	PE_O18_IFC_CTRL_6_T                               ifc_ctrl_6;	//0x012C
	PE_O18_IFC_CTRL_7_T                               ifc_ctrl_7;	//0x0130
	PE_O18_IFC_CTRL_8_T                               ifc_ctrl_8;	//0x0134
	PE_O18_IFC_CTRL_9_T                               ifc_ctrl_9;	//0x0138
	PE_O18_IFC_CTRL_10_T                              ifc_ctrl_10;	//0x013C
	PE_O18_IFC_CTRL_11_T                              ifc_ctrl_11;	//0x0140
	PE_O18_IFC_CTRL_12_T                              ifc_ctrl_12;	//0x0144
	PE_O18_IFC_CTRL_13_T                              ifc_ctrl_13;	//0x0148
	PE_O18_IFC_CTRL_14_T                              ifc_ctrl_14;	//0x014C
	PE_O18_IFC_CTRL_15_T                              ifc_ctrl_15;	//0x0150
	PE_O18_IFC_CTRL_16_T                              ifc_ctrl_16;	//0x0154
	PE_O18_IFC_CTRL_17_T                              ifc_ctrl_17;	//0x0158
	PE_O18_IFC_CTRL_18_T                              ifc_ctrl_18;	//0x015C
	PE_O18_IFC_CTRL_19_T                              ifc_ctrl_19;	//0x0160
	PE_O18_IFC_CTRL_20_T                              ifc_ctrl_20;	//0x0164
	PE_O18_IFC_CTRL_21_T                              ifc_ctrl_21;	//0x0168
	PE_O18_SC_BNR_CTRL_0_T                            sc_bnr_ctrl_0;	//0x016C
	PE_O18_SC_BNR_CTRL_1_T                            sc_bnr_ctrl_1;	//0x0170
	PE_O18_SC_BNR_CTRL_2_T                            sc_bnr_ctrl_2;	//0x0174
	PE_O18_SC_BNR_CTRL_3_T                            sc_bnr_ctrl_3;	//0x0178
	PE_O18_SC_BNR_CTRL_4_T                            sc_bnr_ctrl_4;	//0x017C
	PE_O18_SC_BNR_CTRL_5_T                            sc_bnr_ctrl_5;	//0x0180
	PE_O18_SC_BNR_CTRL_6_T                            sc_bnr_ctrl_6;	//0x0184
	PE_O18_C_PRE_BLUR_CTRL_0_T                        c_pre_blur_ctrl_0;	//0x0188
	PE_O18_TEXTURE_CTRL_0_T                           texture_ctrl_0;	//0x018C
	PE_O18_TEXTURE_CTRL_1_T                           texture_ctrl_1;	//0x0190
	PE_O18_TEXTURE_CTRL_2_T                           texture_ctrl_2;	//0x0194
	PE_O18_TEXTURE_CTRL_3_T                           texture_ctrl_3;	//0x0198
	PE_O18_AC_BNR_CTRL_13_T                           ac_bnr_ctrl_13;	//0x019C
	PE_O18_AC_BNR_CTRL_14_T                           ac_bnr_ctrl_14;	//0x01A0
	PE_O18_DC_BNR_CTRL_6_T                            dc_bnr_ctrl_6;	//0x01A4
	PE_O18_DC_BNR_CTRL_7_T                            dc_bnr_ctrl_7;	//0x01A8
	PE_O18_SQM_CTRL_0_T                               sqm_ctrl_0;	//0x01AC
	PE_O18_SQM_CTRL_1_T                               sqm_ctrl_1;	//0x01B0
	PE_O18_SQM_CTRL_2_T                               sqm_ctrl_2;	//0x01B4
	PE_O18_SQM_CTRL_3_T                               sqm_ctrl_3;	//0x01B8
	PE_O18_SQM_CTRL_4_T                               sqm_ctrl_4;	//0x01BC
	PE_O18_TPD_CTRL_0_T                               tpd_ctrl_0;	//0x01C0
	PE_O18_WINDOW_MODE_0_T                            window_mode_0;	//0x01C4
	PE_O18_WINDOW_MODE_1_T                            window_mode_1;	//0x01C8
	UINT32                                            reserved115;	//0x1cc
	PE_O18_DNR_STAT_3_T                               dnr_stat_3;	//0x01D0
	PE_O18_DNR_STAT_4_T                               dnr_stat_4;	//0x01D4
	PE_O18_DNR_STAT_5_T                               dnr_stat_5;	//0x01D8
	PE_O18_DNR_STAT_6_T                               dnr_stat_6;	//0x01DC
	PE_O18_DNR_STAT_7_T                               dnr_stat_7;	//0x01E0
	PE_O18_DNR_STAT_8_SC_BNR0_T                       dnr_stat_8_sc_bnr0;	//0x01E4
	PE_O18_DNR_STAT_9_SC_BNR1_T                       dnr_stat_9_sc_bnr1;	//0x01E8
	PE_O18_DNR_STAT_10_SC_BNR2_T                      dnr_stat_10_sc_bnr2;	//0x01EC
	PE_O18_DNR_STAT_11_SQM_00_T                       dnr_stat_11_sqm_00;	//0x01F0
	PE_O18_DNR_STAT_12_SQM_01_T                       dnr_stat_12_sqm_01;	//0x01F4
	PE_O18_DNR_STAT_13_SQM_02_T                       dnr_stat_13_sqm_02;	//0x01F8
	PE_O18_DNR_STAT_14_SQM_03_T                       dnr_stat_14_sqm_03;	//0x01FC
	PE_O18_DNR_STAT_15_SQM_04_T                       dnr_stat_15_sqm_04;	//0x0200
	PE_O18_DNR_STAT_16_SQM_05_T                       dnr_stat_16_sqm_05;	//0x0204
	PE_O18_DNR_STAT_17_SQM_06_T                       dnr_stat_17_sqm_06;	//0x0208
	PE_O18_DNR_STAT_18_SQM_07_T                       dnr_stat_18_sqm_07;	//0x020C
	PE_O18_DNR_STAT_19_SQM_08_T                       dnr_stat_19_sqm_08;	//0x0210
	PE_O18_DNR_STAT_20_SQM_09_T                       dnr_stat_20_sqm_09;	//0x0214
	PE_O18_DNR_STAT_21_SQM_10_T                       dnr_stat_21_sqm_10;	//0x0218
	PE_O18_DNR_STAT_22_SQM_11_T                       dnr_stat_22_sqm_11;	//0x021C
	PE_O18_DNR_STAT_23_TPD_0_T                        dnr_stat_23_tpd_0;	//0x0220
	PE_O18_DNR_STAT_24_TPD_1_T                        dnr_stat_24_tpd_1;	//0x0224
	PE_O18_DNR_STAT_25_TPD_2_T                        dnr_stat_25_tpd_2;	//0x0228
	UINT32                                            reserved01;	//0x022C-0x022C
	PE_O18_AC_BNR_15_T                                ac_bnr_15;	//0x0230
	PE_O18_AC_BNR_16_T                                ac_bnr_16;	//0x0234
	PE_O18_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0x0238
	PE_O18_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0x023C
	PE_O18_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0x0240
	PE_O18_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0x0244
	PE_O18_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0x0248
	PE_O18_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0x024C
	PE_O18_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0x0250
	PE_O18_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0x0254
	PE_O18_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0x0258
	PE_O18_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0x025C
	PE_O18_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0x0260
	PE_O18_REG_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0264
	PE_O18_REG_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0268
	PE_O18_REG_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x026C
	PE_O18_REG_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0270
	PE_O18_REG_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0274
	PE_O18_REG_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0278
	PE_O18_REG_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x027C
	PE_O18_REG_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0280
	PE_O18_REG_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0284
	PE_O18_REG_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0288
	PE_O18_REG_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x028C
	PE_O18_REG_DC_BNR_CTRL_8_T                        reg_dc_bnr_ctrl_8;	//0x0290
	PE_O18_REG_DC_BNR_CTRL_9_T                        reg_dc_bnr_ctrl_9;	//0x0294
	PE_O18_REG_DC_BNR_CTRL_10_T                       reg_dc_bnr_ctrl_10;	//0x0298
	PE_O18_REG_DC_BNR_CTRL_11_T                       reg_dc_bnr_ctrl_11;	//0x029C
	PE_O18_REG_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x02A0
	PE_O18_REG_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x02A4
	PE_O18_REG_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x02A8
	PE_O18_REG_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x02AC
	PE_O18_REG_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x02B0
	PE_O18_REG_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x02B4
	PE_O18_REG_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x02B8
	PE_O18_REG_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x02BC
	PE_O18_REG_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x02C0
	PE_O18_REG_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x02C4
	PE_O18_REG_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x02C8
	PE_O18_REG_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x02CC
	PE_O18_REG_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x02D0
	PE_O18_REG_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x02D4
	PE_O18_REG_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x02D8
	PE_O18_REG_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x02DC
	PE_O18_REG_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x02E0
	PE_O18_REG_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x02E4
	PE_O18_REG_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x02E8
	PE_O18_REG_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x02EC
	PE_O18_REG_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x02F0
	PE_O18_REG_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x02F4
	PE_O18_REG_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x02F8
	PE_O18_REG_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x02FC
	PE_O18_REG_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x0300
	PE_O18_REG_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x0304
	PE_O18_REG_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x0308
	PE_O18_REG_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x030C
	PE_O18_REG_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x0310
	PE_O18_REG_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x0314
	PE_O18_REG_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x0318
	PE_O18_REG_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x031C
	PE_O18_REG_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0320
	PE_O18_REG_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x0324
	PE_O18_REG_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x0328
	PE_O18_REG_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x032C
	PE_O18_REG_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0330
	PE_O18_REG_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x0334
	PE_O18_REG_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x0338
	PE_O18_REG_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x033C
	PE_O18_REG_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0340
	PE_O18_REG_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x0344
	PE_O18_REG_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x0348
	PE_O18_REG_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x034C
	PE_O18_REG_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0350
	PE_O18_REG_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x0354
	PE_O18_REG_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x0358
	PE_O18_REG_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x035C
	PE_O18_REG_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0360
	PE_O18_REG_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x0364
	PE_O18_REG_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x0368
	PE_O18_REG_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x036C
	PE_O18_REG_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0370
	PE_O18_REG_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x0374
	PE_O18_REG_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x0378
	PE_O18_REG_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x037C
	PE_O18_REG_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x0380
	PE_O18_REG_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x0384
	PE_O18_REG_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x0388
	PE_O18_REG_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x038C
	PE_O18_REG_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x0390
	PE_O18_REG_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x0394
	PE_O18_REG_DC_BNR_CTRL_12_T                       reg_dc_bnr_ctrl_12;	//0x0398
	PE_O18_REG_DC_BNR_CTRL_13_T                       reg_dc_bnr_ctrl_13;	//0x039C
	PE_O18_REG_DC_BNR_CTRL_14_T                       reg_dc_bnr_ctrl_14;	//0x03A0
	PE_O18_REG_DC_BNR_CTRL_15_T                       reg_dc_bnr_ctrl_15;	//0x03A4
	PE_O18_REG_MNR_CTRL_6_T                           reg_mnr_ctrl_6;	//0x03A8
	PE_O18_REG_MNR_CTRL_7_T                           reg_mnr_ctrl_7;	//0x03AC
	PE_O18_REG_MNR_CTRL_8_T                           reg_mnr_ctrl_8;	//0x03B0
	PE_O18_REG_MNR_CTRL_9_T                           reg_mnr_ctrl_9;	//0x03B4
	PE_O18_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0x03B8
	PE_O18_REG_CTI_CTRL_2_T                           reg_cti_ctrl_2;	//0x03BC
	PE_O18_REG_CTI_CTRL_3_T                           reg_cti_ctrl_3;	//0x03C0
	PE_O18_REG_PSV_CTRL_0_T                           reg_psv_ctrl_0;	//0x03C4
	PE_O18_REG_PSV_CTRL_1_T                           reg_psv_ctrl_1;	//0x03C8
	PE_O18_REG_PSV_CTRL_2_T                           reg_psv_ctrl_2;	//0x03CC
	PE_O18_REG_PSV_CTRL_3_T                           reg_psv_ctrl_3;	//0x03D0
	PE_O18_REG_PSV_CTRL_4_T                           reg_psv_ctrl_4;	//0x03D4
	PE_O18_REG_PSV_CTRL_5_T                           reg_psv_ctrl_5;	//0x03D8
	PE_O18_REG_PSV_CTRL_6_T                           reg_psv_ctrl_6;	//0x03DC
	PE_O18_REG_PSV_CTRL_7_T                           reg_psv_ctrl_7;	//0x03E0
	PE_O18_REG_PSV_CTRL_8_T                           reg_psv_ctrl_8;	//0x03E4
	PE_O18_REG_PSV_CTRL_9_T                           reg_psv_ctrl_9;	//0x03E8
	PE_O18_REG_PSV_CTRL_10_T                          reg_psv_ctrl_10;	//0x03EC
	PE_O18_REG_PSV_CTRL_11_T                          reg_psv_ctrl_11;	//0x03F0
	PE_O18_REG_PSV_CTRL_12_T                          reg_psv_ctrl_12;	//0x03F4
	PE_O18_REG_PSV_CTRL_13_T                          reg_psv_ctrl_13;	//0x03F8
	UINT32                                            reserved254;	//0x3fc
	PE_O18_REG_PSV_STATUS_0_T                         reg_psv_status_0;	//0x0400
	PE_O18_REG_PSV_STATUS_1_T                         reg_psv_status_1;	//0x0404
	PE_O18_REG_PSV_STATUS_2_T                         reg_psv_status_2;	//0x0408
	PE_O18_REG_PSV_STATUS_3_T                         reg_psv_status_3;	//0x040C
	PE_O18_REG_PSV_STATUS_4_T                         reg_psv_status_4;	//0x0410
	PE_O18_REG_PSV_STATUS_5_T                         reg_psv_status_5;	//0x0414
}PE_ND_DNR0_REG_O18_T;

typedef struct
{ 
	PE_O18_PSP_CTRL00_T                               psp_ctrl00;	//0x0000
	PE_O18_PSP_CTRL01_T                               psp_ctrl01;	//0x0004
	PE_O18_PSP_CTRL02_T                               psp_ctrl02;	//0x0008
	PE_O18_EDGE_TH_T                                  edge_th;	//0x000C
	PE_O18_FG_POSITION_T                              fg_position;	//0x0010
	PE_O18_PERSPECT_LUT_X0_T                          perspect_lut_x0;	//0x0014
	PE_O18_PERSPECT_LUT_X1_T                          perspect_lut_x1;	//0x0018
	PE_O18_PERSPECT_LUT_X2_T                          perspect_lut_x2;	//0x001C
	PE_O18_PERSPECT_LUT_X3_T                          perspect_lut_x3;	//0x0020
	PE_O18_PERSPECT_LUT_Y0_T                          perspect_lut_y0;	//0x0024
	PE_O18_PERSPECT_LUT_Y1_T                          perspect_lut_y1;	//0x0028
	PE_O18_PERSPECT_LUT_Y2_T                          perspect_lut_y2;	//0x002C
	PE_O18_PERSPECT_LUT_Y3_T                          perspect_lut_y3;	//0x0030
	PE_O18_PROB_MAP_T                                 prob_map;	//0x0034
	PE_O18_ELLIPS_MAP_T                               ellips_map;	//0x0038
	PE_O18_PROB_DIFF_MAP_T                            prob_diff_map;	//0x003C
	PE_O18_OBJECT_MAP_T                               object_map;	//0x0040
	PE_O18_BLUR_MAP_T                                 blur_map;	//0x0044
	PE_O18_DISPLAY_DEBUG_MAP_T                        display_debug_map;	//0x0048
	PE_O18_PSP_IIR_T                                  psp_iir;	//0x004C
	PE_O18_PSP_GAIN_T                                 psp_gain;	//0x0050
	PE_O18_PSP_DBG_MON00_T                            psp_dbg_mon00;	//0x0054
	PE_O18_PSP_DBG_MON01_T                            psp_dbg_mon01;	//0x0058
	PE_O18_VRTX_CPC_CTRL_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O18_BLUR_HCOEF01_T                             blur_hcoef01;	//0x0060
	PE_O18_BLUR_HCOEF23_T                             blur_hcoef23;	//0x0064
	PE_O18_BLUR_HCOEFF45_T                            blur_hcoeff45;	//0x0068
	PE_O18_BLUR_HCOEFF67_T                            blur_hcoeff67;	//0x006C
	PE_O18_BLUR_HCOEF8_T                              blur_hcoef8;	//0x0070
	PE_O18_BLUR_VCOEF01_T                             blur_vcoef01;	//0x0074
	PE_O18_BLUR_VCOEF23_T                             blur_vcoef23;	//0x0078
	PE_O18_BLUR_VCOEF4_T                              blur_vcoef4;	//0x007C
	PE_O18_HISTOGRAM_0_T                              histogram_0;	//0x0080
	PE_O18_HISTOGRAM_1_T                              histogram_1;	//0x0084
	PE_O18_HISTOGRAM_2_T                              histogram_2;	//0x0088
	PE_O18_HISTOGRAM_3_T                              histogram_3;	//0x008C
	PE_O18_HISTOGRAM_4_T                              histogram_4;	//0x0090
	PE_O18_HISTOGRAM_5_T                              histogram_5;	//0x0094
	PE_O18_HISTOGRAM_6_T                              histogram_6;	//0x0098
	PE_O18_HISTOGRAM_7_T                              histogram_7;	//0x009C
	PE_O18_HISTOGRAM_8_T                              histogram_8;	//0x00A0
	PE_O18_HISTOGRAM_9_T                              histogram_9;	//0x00A4
	PE_O18_HISTOGRAM_10_T                             histogram_10;	//0x00A8
	PE_O18_HISTOGRAM_11_T                             histogram_11;	//0x00AC
	PE_O18_HISTOGRAM_12_T                             histogram_12;	//0x00B0
	PE_O18_HISTOGRAM_13_T                             histogram_13;	//0x00B4
	PE_O18_HISTOGRAM_14_T                             histogram_14;	//0x00B8
	PE_O18_HISTOGRAM_15_T                             histogram_15;	//0x00BC
	PE_O18_HISTOGRAM_16_T                             histogram_16;	//0x00C0
	PE_O18_HISTOGRAM_17_T                             histogram_17;	//0x00C4
	PE_O18_HISTOGRAM_18_T                             histogram_18;	//0x00C8
	PE_O18_HISTOGRAM_19_T                             histogram_19;	//0x00CC
	PE_O18_HISTOGRAM_20_T                             histogram_20;	//0x00D0
	PE_O18_HISTOGRAM_21_T                             histogram_21;	//0x00D4
	PE_O18_HISTOGRAM_22_T                             histogram_22;	//0x00D8
	PE_O18_HISTOGRAM_23_T                             histogram_23;	//0x00DC
	PE_O18_HISTOGRAM_24_T                             histogram_24;	//0x00E0
	PE_O18_HISTOGRAM_25_T                             histogram_25;	//0x00E4
	PE_O18_HISTOGRAM_26_T                             histogram_26;	//0x00E8
	PE_O18_HISTOGRAM_27_T                             histogram_27;	//0x00EC
	PE_O18_HISTOGRAM_28_T                             histogram_28;	//0x00F0
	PE_O18_HISTOGRAM_29_T                             histogram_29;	//0x00F4
	PE_O18_HISTOGRAM_30_T                             histogram_30;	//0x00F8
	PE_O18_HISTOGRAM_31_T                             histogram_31;	//0x00FC
}PE_ND_PSP_REG_O18_T;
typedef struct {
	PE_O18_CTRL_M0_Y_LEVEL_CTRL_T         ctrl_m0_y_level_ctrl;
}PE_TOP_IMX_REG_O18_T;

#endif
