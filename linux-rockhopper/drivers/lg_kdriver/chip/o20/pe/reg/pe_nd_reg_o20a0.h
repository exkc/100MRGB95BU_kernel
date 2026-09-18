#ifndef _PE_ND_REG_O20A0_H_
#define _PE_ND_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc9018100L pe0_load                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	load_time                          :1 ,	// 0 
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_O20_PE0_ND_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9018104L pe0_intr                             
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
}PE_O20_PE0_ND_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9018108L pe0_status0                             
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
}PE_O20_PE0_ND_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc901810cL pe0_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt                           :12,	// 11:0
	reserved01                         :4 ,	// reserved
	timer_cnt                          :16;	// 31:16
}PE_O20_PE0_ND_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9018110L pe0_opmode                             
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
	reserved02                         :1 ,	// reserved
	detour_enable                      :1 ,	// 16
	half_rate_en                       :1 ,	// 17
	ibuf_en                            :2 ,	// 19:18
	minfo_hsample_mode                 :3 ,	// 22:20
	minfo_vsample_mode                 :3 ,	// 25:23
	o_line_ctrl_mode                   :1 ,	// 26
	o_line_ctrl_en                     :1 ,	// 27
	tnr_in_lsb_mode                    :2 ,	// 29:28
	m_run_id                           :2 ;	// 31:30
}PE_O20_PE0_ND_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9018114L pe0_src_size                             
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
}PE_O20_PE0_SRC_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9018118L pe0_field                             
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
}PE_O20_PE0_FIELD_T;
/*-----------------------------------------------------------------------------
                             0xc901811cL pe0_debug_lend_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	in_hsize                           :12,	// 11:0
	reserved01                         :2 ,	// reserved
	lend_manual_vsize                  :1 ,	// 14
	reserved02                         :1 ,	// reserved
	in_vsize                           :12,	// 27:16
	ptn_en_c                           :1 ,	// 28
	ptn_en_y                           :1 ,	// 29
	lend_manual_hsize                  :1 ,	// 30
	lend_ctrl_en                       :1 ;	// 31
}PE_O20_PE0_DEBUG_LEND_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9018120L pe0_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O20_PE0_ND_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc9018124L pe0_in_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O20_PE0_ND_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9018128L fbc_ctrl0                             
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
}PE_O20_FBC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc901812cL fbc_ctrl1                             
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
}PE_O20_FBC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc9018130L pe0_mem_req                             
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
	manual_mem_off                     :1 ;	// 15
}PE_O20_PE0_MEM_REQ_T;
/*-----------------------------------------------------------------------------
                             0xc9018134L pe0_debug_lreq_dly                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lreq_dly_c                         :11,	// 10:0
	lreq_dly_c_en                      :1 ,	// 11
	reserved01                         :4 ,	// reserved
	lreq_dly_y                         :11,	// 26:16
	lreq_dly_y_en                      :1 ;	// 27
}PE_O20_PE0_DEBUG_LREQ_DLY_T;
/*-----------------------------------------------------------------------------
                             0xc9018138L tnrw_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O20_TNRW_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc901813cL tnrw_out_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O20_TNRW_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9018140L tnr_ctrl_00                             
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
	reg_decon_blend_en                 :1 ,	// 17
	reg_minfo_mode32                   :2 ,	// 19:18
	reg_minfo_mode74                   :4 ,	// 23:20
	reg_sad_8x3_iir_alpha              :8 ;	// 31:24
}PE_O20_TNR_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018144L tnr_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_show                       :4 ,	// 3:0
	reg_ma_motion_iir_alpha            :8 ,	// 11:4
	reg_ma_motion_iir_en               :1 ,	// 12
	reg_ma_motion_chroma_en            :1 ,	// 13
	reg_ma_motion_res                  :2 ,	// 15:14
	reg_dbg_tnrw                       :2 ,	// 17:16
	reg_ma_motion_lsb6_sel             :1 ,	// 18
	reg_sad_8x3_lsb6_sel               :1 ,	// 19
	reg_tnri_debug_mode                :2 ,	// 21:20
	reserved01                         :2 ,	// reserved
	reg_minfo_mode118                  :4 ,	// 27:24
	reg_sc_scale2                      :3 ;	// 30:28
}PE_O20_TNR_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018148L tnr_ctrl_02                             
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
}PE_O20_TNR_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901814cL tnr_ctrl_03                             
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
}PE_O20_TNR_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018150L tnr_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_debug_bar_09                :8 ,	// 7:0
	manual_debug_bar_10                :8 ,	// 15:8
	manual_debug_bar_11                :8 ,	// 23:16
	manual_debug_bar_12                :8 ;	// 31:24
}PE_O20_TNR_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018154L tnr_ctrl_05                             
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
}PE_O20_TNR_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018158L tnr_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_me_lb_base                     :8 ,	// 7:0
	reg_me_pv_base                     :8 ,	// 15:8
	reg_me_lb_polarity                 :1 ;	// 16
}PE_O20_TNR_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901815cL tnr_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_5x5_sad_cut                    :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	reg_sc_en                          :1 ;	// 8 
}PE_O20_TNR_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018160L tnr_ctrl_08                             
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
}PE_O20_TNR_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018164L tnr_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_base                       :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_lb_smooth_clip                 :6 ,	// 13:8
	reserved02                         :2 ,	// reserved
	reg_pv_smooth_clip                 :6 ;	// 21:16
}PE_O20_TNR_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018168L tnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901816cL tnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lb_smooth_en                       :1 ,	// 0 
	pv_smooth_en                       :1 ,	// 1 
	pmv_hist_en                        :1 ,	// 2 
	reserved01                         :28,	// reserved
	reg_me_n15_protection              :1 ;	// 31
}PE_O20_TNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9018170L tnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9018174L tnr_ctrl_13                             
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
}PE_O20_TNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9018178L tnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc901817cL tnr_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9018180L tnr_ctrl_16                             
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
	reg_n_vblk                         :5 ;	// 24:20
}PE_O20_TNR_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9018184L tnr_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blk_vsize                      :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_blk_hsize                      :12;	// 27:16
}PE_O20_TNR_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9018188L tnr_ctrl_18                             
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
}PE_O20_TNR_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc901818cL tnr_ctrl_19                             
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
}PE_O20_TNR_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9018190L tnr_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_detail_beta_mul                :8 ,	// 7:0
	reg_detail_alpha_mul               :8 ,	// 15:8
	reg_edge_beta_mul                  :8 ,	// 23:16
	reg_edge_alpha_mul                 :8 ;	// 31:24
}PE_O20_TNR_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9018194L tnr_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_svar_scale                     :3 ,	// 2:0
	reserved01                         :5 ,	// reserved
	reg_sad_8x3_res2                   :2 ;	// 9:8
}PE_O20_TNR_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc9018198L tnr_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc901819cL tnr_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90181a0L tnr_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	// reserved
	reg_ombc_en                        :1 ,	// 1 
	reserved02                         :2 ,	// reserved
	reg_luma_gain_en                   :1 ,	// 4 
	reg_crgn_gain_en                   :1 ,	// 5 
	reg_chroma_sad_res                 :2 ,	// 7:6
	reserved03                         :4 ,	// reserved
	reg_5x5_sad_cut                    :2 ,	// 13:12
	reserved04                         :2 ,	// reserved
	reg_avg_cmp_en                     :1 ,	// 16
	reg_avg_cmp_res                    :3 ,	// 19:17
	reg_debug_sel                      :4 ,	// 23:20
	reserved05                         :4 ,	// reserved
	reg_cnt_mode                       :3 ,	// 30:28
	reg_chroma_sad_en                  :1 ;	// 31
}PE_O20_TNR_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90181a4L tnr_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :24,	// reserved
	reg_skin_master_gain               :8 ;	// 31:24
}PE_O20_TNR_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc90181a8L tnr_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_yy_x2            :10,	// 9:0
	reg_tnr_final_lut_yy_y3            :10,	// 19:10
	reg_tnr_final_lut_yy_x3            :10;	// 29:20
}PE_O20_TNR_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc90181acL tnr_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_yy_y1            :10,	// 9:0
	reg_tnr_final_lut_yy_x1            :10,	// 19:10
	reg_tnr_final_lut_yy_y2            :10;	// 29:20
}PE_O20_TNR_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc90181b0L tnr_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_yy_y0            :10,	// 9:0
	reg_tnr_final_lut_yy_x0            :10;	// 19:10
}PE_O20_TNR_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc90181b4L tnr_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cb_x2            :10,	// 9:0
	reg_tnr_final_lut_cb_y3            :10,	// 19:10
	reg_tnr_final_lut_cb_x3            :10;	// 29:20
}PE_O20_TNR_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc90181b8L tnr_ctrl_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cb_y1            :10,	// 9:0
	reg_tnr_final_lut_cb_x1            :10,	// 19:10
	reg_tnr_final_lut_cb_y2            :10;	// 29:20
}PE_O20_TNR_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc90181bcL tnr_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cb_y0            :10,	// 9:0
	reg_tnr_final_lut_cb_x0            :10;	// 19:10
}PE_O20_TNR_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc90181c0L tnr_status_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_gsad                             :8 ,	// 7:0
	w_gmv                              :9 ,	// 16:8
	reserved01                         :7 ,	// reserved
	w_apl_detail                       :8 ;	// 31:24
}PE_O20_TNR_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc90181c4L tnr_status_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_apl_motion                       :8 ,	// 7:0
	w_apl_mc_sad                       :8 ,	// 15:8
	w_apl_var                          :8 ,	// 23:16
	w_apl_edge                         :8 ;	// 31:24
}PE_O20_TNR_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc90181c8L tnr_status_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc90181ccL tnr_status_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc90181d0L tnr_main_lut_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	main_lut_indir_addr                :6 ,	// 5:0
	reserved01                         :6 ,	// reserved
	main_lut_ai_enable                 :1 ,	// 12
	reserved02                         :2 ,	// reserved
	main_lut_load                      :1 ;	// 15
}PE_O20_TNR_MAIN_LUT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90181d4L tnr_main_lut_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	main_lut_indir_data0;	// 31:0
}PE_O20_TNR_MAIN_LUT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90181dcL tnr_status_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sc_measure                         :8 ,	// 7:0
	apl_y                              :8 ,	// 15:8
	sc_measure_16                      :16;	// 31:16
}PE_O20_TNR_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc90181e0L tnr_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_gf_gain                        :8 ,	// 23:16
	reg_blur_coef                      :8 ;	// 31:24
}PE_O20_TNR_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc90181e4L tnr_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	same_protection_en                 :1 ,	// 0 
	reg_p_mv0_only                     :1 ,	// 1 
	reg_p_non_mv0_only                 :1 ,	// 2 
	reg_final_lut_en                   :1 ,	// 3 
	reserved01                         :4 ,	// reserved
	reg_same_sad_th                    :8 ,	// 15:8
	reg_move_step                      :8 ;	// 23:16
}PE_O20_TNR_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc90181e8L tnr_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cr_x2            :10,	// 9:0
	reg_tnr_final_lut_cr_y3            :10,	// 19:10
	reg_tnr_final_lut_cr_x3            :10;	// 29:20
}PE_O20_TNR_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc90181ecL tnr_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cr_y1            :10,	// 9:0
	reg_tnr_final_lut_cr_x1            :10,	// 19:10
	reg_tnr_final_lut_cr_y2            :10;	// 29:20
}PE_O20_TNR_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc90181f0L tnr_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tnr_final_lut_cr_y0            :10,	// 9:0
	reg_tnr_final_lut_cr_x0            :10;	// 19:10
}PE_O20_TNR_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc90181f4L tnr_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc90181f8L tnr_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc90181fcL tnr_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_TNR_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9018200L ipc_ctrl_00                             
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
}PE_O20_IPC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018204L ipc_ctrl_01                             
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
}PE_O20_IPC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018208L ipc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fuzzy_ctrl_point_x0                :8 ,	// 7:0
	fuzzy_ctrl_point_x4                :8 ,	// 15:8
	fuzzy_ctrl_point_x1                :8 ,	// 23:16
	fuzzy_ctrl_point_y1                :8 ;	// 31:24
}PE_O20_IPC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901820cL ipc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	fuzzy_ctrl_point_x2                :8 ,	// 7:0
	fuzzy_ctrl_point_y2                :8 ,	// 15:8
	fuzzy_ctrl_point_x3                :8 ,	// 23:16
	fuzzy_ctrl_point_y3                :8 ;	// 31:24
}PE_O20_IPC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018210L ipc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	et_offset__s7                      :8 ,	// 7:0
	motion_x_tearing_gain              :8 ,	// 15:8
	tearing_gain                       :8 ,	// 23:16
	motion_gain                        :8 ;	// 31:24
}PE_O20_IPC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018214L ipc_ctrl_05                             
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
}PE_O20_IPC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018218L ipc_ctrl_06                             
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
}PE_O20_IPC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901821cL ipc_ctrl_07                             
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
}PE_O20_IPC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018220L ipc_ctrl_08                             
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
}PE_O20_IPC_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018224L ipc_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pn_fmd_a_th                        :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	pn_variance_th                     :8 ,	// 23:16
	pn_fmd_motion_th                   :8 ;	// 31:24
}PE_O20_IPC_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018228L ipc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pcnc_fmd_a_th                      :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	pcnc_variance_th                   :8 ,	// 23:16
	pcnc_fmd_motion_th                 :8 ;	// 31:24
}PE_O20_IPC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901822cL ipc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_pndiff_th                       :8 ,	// 7:0
	cr_center_bound_ctrl               :8 ,	// 15:8
	cr_dn_bound_ctrl                   :8 ,	// 23:16
	cr_up_bound_ctrl                   :8 ;	// 31:24
}PE_O20_IPC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9018230L ipc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th                    :8 ,	// 7:0
	reg_fmd_ratio_th                   :8 ,	// 15:8
	reg_fmd_max_th                     :8 ,	// 23:16
	reg_fmd_min_th                     :8 ;	// 31:24
}PE_O20_IPC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9018234L ipc_ctrl_13                             
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
}PE_O20_IPC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9018238L ipc_ctrl_14                             
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
}PE_O20_IPC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc901823cL ipc_ctrl_15                             
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
}PE_O20_IPC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9018240L ipc_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th2                   :8 ,	// 7:0
	reg_still_prev_ratio               :8 ,	// 15:8
	reg_lock_reducer                   :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	reg_badedit_protect                :1 ;	// 31
}PE_O20_IPC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9018244L ipc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_inv_resolution                  :2 ,	// 1:0
	cr_field_manual_mode               :2 ,	// 3:2
	cr_field_inverse                   :1 ,	// 4 
	reserved01                         :19,	// reserved
	cr_tearing_a_th                    :8 ;	// 31:24
}PE_O20_IPC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc9018248L ipc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_ud_gain                         :8 ,	// 7:0
	cr_lr_gain                         :8 ,	// 15:8
	cr_h_grad_gain                     :8 ,	// 23:16
	cr_v_grad_gain                     :8 ;	// 31:24
}PE_O20_IPC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc901824cL ipc_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_errs_gain                      :8 ,	// 7:0
	reg_confidence_gain                :8 ,	// 15:8
	reg_2d_offset                      :8 ,	// 23:16
	reg_flicker_gain                   :8 ;	// 31:24
}PE_O20_IPC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9018250L ipc_status_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_v_count                       :16,	// 15:0
	r_nc_v_count                       :16;	// 31:16
}PE_O20_IPC_STATUS_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018254L ipc_status_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_nc_same                       :16,	// 15:0
	r_pn_v_count                       :16;	// 31:16
}PE_O20_IPC_STATUS_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018258L ipc_status_02                             
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
}PE_O20_IPC_STATUS_02_T;
/*-----------------------------------------------------------------------------
                             0xc901825cL ipc_status_03                             
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
}PE_O20_IPC_STATUS_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018260L clc_ctrl_00                             
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
}PE_O20_CLC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018264L clc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_motion_a_th                     :8 ,	// 7:0
	cl_motion_b_th                     :8 ,	// 15:8
	cl_y_protect_th0                   :8 ,	// 23:16
	cl_y_protect_th1                   :8 ;	// 31:24
}PE_O20_CLC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018268L clc_ctrl_02                             
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
}PE_O20_CLC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901826cL clc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_sat_min                         :8 ,	// 7:0
	reserved01                         :2 ,	// reserved
	cl_var_measure_th1                 :10,	// 19:10
	cl_var_measure_th2                 :10,	// 29:20
	cl_pt_enable                       :2 ;	// 31:30
}PE_O20_CLC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018270L clc_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cl_tearing_pt_th1                  :12,	// 11:0
	cl_motionp2n2_th_pal_low           :8 ,	// 19:12
	cl_frame_min                       :12;	// 31:20
}PE_O20_CLC_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018274L clc_ctrl_05                             
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
}PE_O20_CLC_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018278L clc_ctrl_06                             
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
}PE_O20_CLC_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901827cL clc_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	cl_detection_count                 :16;	// 31:16
}PE_O20_CLC_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018280L ipc_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_v_diff_y0                     :8 ,	// 7:0
	tava_v_diff_x0                     :8 ,	// 15:8
	tava_v_diff_y1                     :8 ,	// 23:16
	tava_v_diff_x1                     :8 ;	// 31:24
}PE_O20_IPC_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9018284L ipc_ctrl_35                             
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
}PE_O20_IPC_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9018288L ipc_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th                    :8 ,	// 7:0
	reg_fmd_ratio_th                   :8 ,	// 15:8
	reg_fmd_max_th                     :8 ,	// 23:16
	reg_fmd_min_th                     :8 ;	// 31:24
}PE_O20_IPC_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc901828cL ipc_ctrl_37                             
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
}PE_O20_IPC_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9018290L ipc_ctrl_38                             
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
}PE_O20_IPC_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9018294L ipc_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_still_pn_th2                   :8 ,	// 7:0
	reg_still_prev_ratio               :8 ,	// 15:8
	reg_lock_reducer                   :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	reg_badedit_protect                :1 ;	// 31
}PE_O20_IPC_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9018298L ipc_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_toosmall_en                    :1 ,	// 0 
	reg_toosmall_min                   :7 ,	// 7:1
	reg_toosmall_max                   :8 ,	// 15:8
	reg_pndiff_disable                 :1 ;	// 16
}PE_O20_IPC_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc901829cL ipc_ctrl_41                             
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
}PE_O20_IPC_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90182a0L ipc_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_yy_diff_gain                   :4 ,	// 3:0
	reg_hv_add_gain                    :4 ,	// 7:4
	reg_v_motion_gain                  :4 ,	// 11:8
	reg_h_motion_gain                  :4 ,	// 15:12
	reg_cc_diff_gain                   :4 ;	// 19:16
}PE_O20_IPC_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90182a4L ipc_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	n1b_motion_gain_y0                 :8 ,	// 7:0
	n1b_motion_gain_x0                 :8 ,	// 15:8
	n1b_motion_gain_y1                 :8 ,	// 23:16
	n1b_motion_gain_x1                 :8 ;	// 31:24
}PE_O20_IPC_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90182a8L ipc_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	n1b_variance_gain_y0               :8 ,	// 7:0
	n1b_variance_gain_x0               :8 ,	// 15:8
	n1b_variance_gain_y1               :8 ,	// 23:16
	n1b_variance_gain_x1               :8 ;	// 31:24
}PE_O20_IPC_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90182acL ipc_ctrl_45                             
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
}PE_O20_IPC_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90182b0L ipc_ctrl_46                             
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
}PE_O20_IPC_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90182b4L ipc_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_max_va_diff_th                 :8 ,	// 7:0
	reg_max_edi_diff_th                :8 ,	// 15:8
	reg_edi_va_protect_min             :8 ,	// 23:16
	reg_edi_va_blend_min               :8 ;	// 31:24
}PE_O20_IPC_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90182b8L ipc_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2d_top_lut_y0                  :8 ,	// 7:0
	reg_2d_top_lut_x0                  :8 ,	// 15:8
	reg_2d_top_lut_y1                  :8 ,	// 23:16
	reg_2d_top_lut_x1                  :8 ;	// 31:24
}PE_O20_IPC_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc90182bcL ipc_ctrl_49                             
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
}PE_O20_IPC_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc90182c0L ipc_ctrl_50                             
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
}PE_O20_IPC_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc90182c4L ipc_ctrl_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt_th_0                      :12,	// 11:0
	line_cnt_th_1                      :12;	// 23:12
}PE_O20_IPC_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc90182c8L ipc_ctrl_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_n1b_limit                       :9 ,	// 8:0
	reserved01                         :3 ,	// reserved
	cr_n1b_resolution                  :3 ,	// 14:12
	reserved02                         :9 ,	// reserved
	cr_pre_sc_th                       :8 ;	// 31:24
}PE_O20_IPC_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc90182ccL ipc_ctrl_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_y0                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	cr_hmc_text_rgn_x0                 :11;	// 26:16
}PE_O20_IPC_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc90182d0L ipc_ctrl_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_y1                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	cr_hmc_text_rgn_x1                 :11;	// 26:16
}PE_O20_IPC_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc90182d4L ipc_ctrl_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_hmc_text_rgn_en                 :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	cr_hmc_text_rgn_sad_max            :8 ,	// 15:8
	cr_hmc_text_rgn_sad_min            :8 ;	// 23:16
}PE_O20_IPC_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc90182e0L mmd_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mmd_vtap_yy                        :2 ,	// 1:0
	reserved01                         :2 ,	// reserved
	mmd_htap_yy                        :2 ,	// 5:4
	reserved02                         :2 ,	// reserved
	mmd_vtap_cc                        :2 ,	// 9:8
	reserved03                         :2 ,	// reserved
	mmd_htap_cc                        :2 ,	// 13:12
	reserved04                         :2 ,	// reserved
	reg_chroma_mmd_en                  :1 ;	// 16
}PE_O20_MMD_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90182f0L ipc_ctrl_20                             
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
}PE_O20_IPC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90182f4L ipc_ctrl_21                             
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
}PE_O20_IPC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90182f8L ipc_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_vmc_v_diff_max                  :8 ,	// 7:0
	cr_vmc_v_diff_protect_mul          :8 ,	// 15:8
	es_err_value                       :8 ,	// 23:16
	et_err_value                       :8 ;	// 31:24
}PE_O20_IPC_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90182fcL ipc_ctrl_23                             
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
}PE_O20_IPC_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc9018300L ipc_ctrl_24                             
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
}PE_O20_IPC_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc9018304L ipc_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vdiff_en                       :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	reg_vdiff_th                       :8 ,	// 15:8
	reg_hmc_err_max                    :8 ,	// 23:16
	reg_hmc_err_min                    :8 ;	// 31:24
}PE_O20_IPC_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc9018308L ipc_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cr_fmd_check_en                    :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	cr_fmd_ath                         :8 ,	// 15:8
	reserved02                         :8 ,	// reserved
	cr_fmd_ratio_th                    :8 ;	// 31:24
}PE_O20_IPC_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc901830cL ipc_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	chroma_st_flt_ctrl_x0              :8 ,	// 7:0
	chroma_st_flt_ctrl_x1              :8 ,	// 15:8
	luma_st_flt_ctrl_x0                :8 ,	// 23:16
	luma_st_flt_ctrl_x1                :8 ;	// 31:24
}PE_O20_IPC_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc9018310L ipc_ctrl_28                             
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
}PE_O20_IPC_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc9018314L ipc_ctrl_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hmc_alpha_th                       :8 ,	// 7:0
	reserved01                         :8 ,	// reserved
	hmc_flt_ctrl_x0                    :8 ,	// 23:16
	hmc_st_flt_ctrl_x1                 :8 ;	// 31:24
}PE_O20_IPC_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc9018318L ipc_ctrl_30                             
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
}PE_O20_IPC_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc901831cL ipc_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_toosmall_en                    :1 ,	// 0 
	reg_toosmall_min                   :7 ,	// 7:1
	reg_toosmall_max                   :8 ,	// 15:8
	reg_pndiff_disable                 :1 ;	// 16
}PE_O20_IPC_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc9018320L ipc_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_errt_y2                       :8 ,	// 7:0
	tava_errt_x2                       :8 ,	// 15:8
	tava_errt_y3                       :8 ,	// 23:16
	tava_errt_x3                       :8 ;	// 31:24
}PE_O20_IPC_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc9018324L ipc_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	tava_errt_y0                       :8 ,	// 7:0
	tava_errt_x0                       :8 ,	// 15:8
	tava_errt_y1                       :8 ,	// 23:16
	tava_errt_x1                       :8 ;	// 31:24
}PE_O20_IPC_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc9018328L ipc_status_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_v_count_d                     :16,	// 15:0
	r_nc_v_count_d                     :16;	// 31:16
}PE_O20_IPC_STATUS_04_T;
/*-----------------------------------------------------------------------------
                             0xc901832cL ipc_status_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_pc_nc_same_d                     :16,	// 15:0
	r_pn_v_count_d                     :16;	// 31:16
}PE_O20_IPC_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018330L ipc_status_06                             
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
}PE_O20_IPC_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc9018334L ipc_status_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	r_inv_inversed_cnt                 :16,	// 15:0
	r_inv_original_cnt                 :16;	// 31:16
}PE_O20_IPC_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018338L ipc_status_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IPC_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc901833cL ipc_status_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IPC_STATUS_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018340L tpd_ctrl_00                             
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
}PE_O20_TPD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018344L tpd_ctrl_01                             
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
}PE_O20_TPD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018348L tpd_ctrl_02                             
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
}PE_O20_TPD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901834cL tpd_ctrl_03                             
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
}PE_O20_TPD_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018350L tpd_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winb_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winb_y1                            :12;	// 27:16
}PE_O20_TPD_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018354L tpd_ctrl_05                             
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
}PE_O20_TPD_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018358L tpd_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winc_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winc_y1                            :12;	// 27:16
}PE_O20_TPD_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901835cL tpd_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_y                        :10,	// 9:0
	reg_force_y_max_th                 :10,	// 19:10
	reg_force_y_min_th                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_y_enable                 :1 ;	// 31
}PE_O20_TPD_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018360L tpd_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cb                       :10,	// 9:0
	reg_force_cb_max_th                :10,	// 19:10
	reg_force_cb_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cb_enable                :1 ;	// 31
}PE_O20_TPD_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018364L tpd_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cr                       :10,	// 9:0
	reg_force_cr_max_th                :10,	// 19:10
	reg_force_cr_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cr_enable                :1 ;	// 31
}PE_O20_TPD_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018368L tpd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_pixel_count                   :22;	// 21:0
}PE_O20_TPD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc901836cL clc_ctrl_07                             
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
}PE_O20_CLC_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018370L bbd_ctrl_00                             
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
}PE_O20_BBD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018374L bbd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O20_BBD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018378L bbd_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O20_BBD_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901837cL bbd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O20_BBD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018380L bbd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :12,	// 11:0
	reserved01                         :4 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O20_BBD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018384L apl_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y_g_s_apl                          :10,	// 9:0
	cb_b_s_apl                         :10,	// 19:10
	cr_r_s_apl                         :10;	// 29:20
}PE_O20_APL_STAT_00_T;

/*-----------------------------------------------------------------------------
                             0xc9018388L tpd_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_s_th_max                       :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_s_th_min                       :10;	// 25:16
}PE_O20_TPD_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc901838cL tpd_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_th_max                       :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_y_th_min                       :10;	// 25:16
}PE_O20_TPD_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9018390L tpd_hist_ai_ctrl                             
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
	reserved03                         :1 ,	// reserved
	hist_read_enable                   :1 ,	// 30
	hist_read_done                     :1 ;	// 31
}PE_O20_TPD_HIST_AI_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9018394L tpd_hist_ai_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status                        :22;	// 21:0
}PE_O20_TPD_HIST_AI_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9018398L lvcrtl_ctrl_00                             
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
}PE_O20_LVCRTL_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc901839cL tpd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32 hist_pixel_count                   :22;	//21:0
}PE_O20_TPD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90183a0L tnr_status_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_05_T;
/*-----------------------------------------------------------------------------
                             0xc90183a4L tnr_status_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_06_T;
/*-----------------------------------------------------------------------------
                             0xc90183a8L tnr_status_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_07_T;
/*-----------------------------------------------------------------------------
                             0xc90183acL tnr_status_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_TNR_STATUS_08_T;
/*-----------------------------------------------------------------------------
                             0xc90183c0L tnr_reset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gmv_rst                        :1 ,	// 0 
	reg_bmv_rst                        :1 ,	// 1 
	reg_me_rst                         :1 ,	// 2 
	reg_mc_rst                         :1 ,	// 3 
	reg_ma_rst                         :1 ;	// 4 
}PE_O20_TNR_RESET_T;
/*-----------------------------------------------------------------------------
                             0xc90183d0L tnr_ctrl_40                             
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
}PE_O20_TNR_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc90183d4L tnr_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mul_base_t                     :8 ,	// 7:0
	reg_mul_base_e                     :8 ;	// 15:8
}PE_O20_TNR_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc90183d8L tnr_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_a_lut_edge_y0                  :8 ,	// 7:0
	reg_a_lut_edge_x0                  :8 ,	// 15:8
	reg_a_lut_edge_y1                  :8 ,	// 23:16
	reg_a_lut_edge_x1                  :8 ;	// 31:24
}PE_O20_TNR_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc90183dcL tnr_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_a_lut_detail_y0                :8 ,	// 7:0
	reg_a_lut_detail_x0                :8 ,	// 15:8
	reg_a_lut_detail_y1                :8 ,	// 23:16
	reg_a_lut_detail_x1                :8 ;	// 31:24
}PE_O20_TNR_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc90183e0L tnr_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_t_lut_edge_y0                  :8 ,	// 7:0
	reg_t_lut_edge_x0                  :8 ,	// 15:8
	reg_t_lut_edge_y1                  :8 ,	// 23:16
	reg_t_lut_edge_x1                  :8 ;	// 31:24
}PE_O20_TNR_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc90183e4L tnr_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_t_lut_detail_y0                :8 ,	// 7:0
	reg_t_lut_detail_x0                :8 ,	// 15:8
	reg_t_lut_detail_y1                :8 ,	// 23:16
	reg_t_lut_detail_x1                :8 ;	// 31:24
}PE_O20_TNR_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc90183e8L tnr_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_minmax_y0                 :8 ,	// 7:0
	reg_edge_minmax_x0                 :8 ,	// 15:8
	reg_edge_minmax_y1                 :8 ,	// 23:16
	reg_edge_minmax_x1                 :8 ;	// 31:24
}PE_O20_TNR_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc90183ecL tnr_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_detail_minmax_y0               :8 ,	// 7:0
	reg_detail_minmax_x0               :8 ,	// 15:8
	reg_detail_minmax_y1               :8 ,	// 23:16
	reg_detail_minmax_x1               :8 ;	// 31:24
}PE_O20_TNR_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc90183f0L tnr_ctrl_48                             
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
}PE_O20_TNR_CTRL_48_T;
/*-----------------------------------------------------------------------------
		0xc90183f4L pe1_fsw_ctrl_00 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd0_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd0_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd0_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd0_hue_bin_9                      : 8 ;  // 31:24
} PE_O20_PE1_FSW_CTRL_00_T;

/*-----------------------------------------------------------------------------
		0xc90183f8L pe1_fsw_ctrl_01 ''
-----------------------------------------------------------------------------*/
typedef struct {
	UINT32 nd1_hue_bin_6                      : 8 ;  //  7: 0
	UINT32 nd1_hue_bin_7                      : 8 ;  // 15: 8
	UINT32 nd1_hue_bin_8                      : 8 ;  // 23:16
	UINT32 nd1_hue_bin_9                      : 8 ;  // 31:24
} PE_O20_PE1_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
		0xc90183fcL pe1_fsw_ctrl_02 ''
-----------------------------------------------------------------------------*/
typedef struct {
	
	UINT32
	reserved                          :32;	// 15:0
} PE_O20_PE1_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9018400L tnr_ne_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	valid_cnt                          :16;	// 15:0
}PE_O20_TNR_NE_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018404L tnr_ne_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_1                             :16,	// 15:0
	hist_0                             :16;	// 31:16
}PE_O20_TNR_NE_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018408L tnr_ne_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_3                             :16,	// 15:0
	hist_2                             :16;	// 31:16
}PE_O20_TNR_NE_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc901840cL tnr_ne_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_5                             :16,	// 15:0
	hist_4                             :16;	// 31:16
}PE_O20_TNR_NE_STAT_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018410L tnr_ne_stat_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_7                             :16,	// 15:0
	hist_6                             :16;	// 31:16
}PE_O20_TNR_NE_STAT_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018414L tnr_ne_stat_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_9                             :16,	// 15:0
	hist_8                             :16;	// 31:16
}PE_O20_TNR_NE_STAT_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018418L tnr_ne_stat_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_11                            :16,	// 15:0
	hist_10                            :16;	// 31:16
}PE_O20_TNR_NE_STAT_06_T;
/*-----------------------------------------------------------------------------
                             0xc901841cL tnr_ne_stat_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_13                            :16,	// 15:0
	hist_12                            :16;	// 31:16
}PE_O20_TNR_NE_STAT_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018420L tnr_ne_stat_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_15                            :16,	// 15:0
	hist_14                            :16;	// 31:16
}PE_O20_TNR_NE_STAT_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018440L hist2_ctrl_00                             
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
}PE_O20_HIST2_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018444L hist2_ctrl_01                             
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
}PE_O20_HIST2_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018448L hist2_ctrl_02                             
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
}PE_O20_HIST2_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901844cL hist2_ctrl_03                             
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
}PE_O20_HIST2_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018450L hist2_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winb_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winb_y1                            :12;	// 27:16
}PE_O20_HIST2_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018454L hist2_ctrl_05                             
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
}PE_O20_HIST2_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018458L hist2_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	winc_x1                            :12,	// 11:0
	reserved01                         :4 ,	// reserved
	winc_y1                            :12;	// 27:16
}PE_O20_HIST2_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc901845cL hist2_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_y                        :10,	// 9:0
	reg_force_y_max_th                 :10,	// 19:10
	reg_force_y_min_th                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_y_enable                 :1 ;	// 31
}PE_O20_HIST2_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018460L hist2_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cb                       :10,	// 9:0
	reg_force_cb_max_th                :10,	// 19:10
	reg_force_cb_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cb_enable                :1 ;	// 31
}PE_O20_HIST2_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018464L hist2_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_force_cr                       :10,	// 9:0
	reg_force_cr_max_th                :10,	// 19:10
	reg_force_cr_min_th                :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_force_cr_enable                :1 ;	// 31
}PE_O20_HIST2_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018468L hist2_ctrl_0a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_s_th_max                       :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_s_th_min                       :10;	// 25:16
}PE_O20_HIST2_CTRL_0A_T;
/*-----------------------------------------------------------------------------
                             0xc901846cL hist2_ctrl_0b                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_y_th_max                       :10,	// 9:0
	reserved01                         :6 ,	// reserved
	reg_y_th_min                       :10;	// 25:16
}PE_O20_HIST2_CTRL_0B_T;
/*-----------------------------------------------------------------------------
                             0xc9018470L hist2_hist_ai_ctrl                             
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
	reserved03                         :1 ,	// reserved
	hist_read_enable                   :1 ,	// 30
	hist_read_done                     :1 ;	// 31
}PE_O20_HIST2_HIST_AI_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9018474L hist2_hist_ai_data                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_status                        :22;	// 21:0
}PE_O20_HIST2_HIST_AI_DATA_T;
/*-----------------------------------------------------------------------------
                             0xc9018478L hist2_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hist_pixel_count                   :22;	// 21:0
}PE_O20_HIST2_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018480L nd_fsw_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	chroma_st_flt_ctrl_x0              : 8 ,  //  7: 0     
	chroma_st_flt_ctrl_x1              : 8 ,  // 15: 8     
	luma_st_flt_ctrl_x0                : 8 ,  // 23:16     
	luma_st_flt_ctrl_x1                : 8 ;  // 31:24     
}PE_O20_ND_FSW_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018484L nd_fsw_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	motion_x_tearing_gain              : 8 ,  //  7: 0     
	motion_gain                        : 8 ;  // 15: 8     
}PE_O20_ND_FSW_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018488L nd_fsw_ctrl_02                             
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
}PE_O20_ND_FSW_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901848cL nd_fsw_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_ND_FSW_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018490L tnr_etc_ctrl_00                             
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
}PE_O20_TNR_ETC_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018494L tnr_etc_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_y1                             :12,	// 11:0
	reserved01                         :4 ,	// reserved
	win_x1                             :13,	// 28:16
	reserved02                         :2 ,	// reserved
	win_tnrw_en                        :1 ;	// 31
}PE_O20_TNR_ETC_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018498L tnr_etc_ctrl_02                             
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
}PE_O20_TNR_ETC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901849cL tnr_etc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_clc_minfo_dly                  :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_clc_flt_dly                    :3 ;	// 6:4
}PE_O20_TNR_ETC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90184a0L tnr_ctrl_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_mc_ctrl_pt_y0              :8 ,	// 7:0
	reg_sad_mc_ctrl_pt_x0              :8 ,	// 15:8
	reg_sad_mc_ctrl_pt_y1              :8 ,	// 23:16
	reg_sad_mc_ctrl_pt_x1              :8 ;	// 31:24
}PE_O20_TNR_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc90184a4L tnr_ctrl_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_mc_ctrl_pt_y2              :8 ,	// 7:0
	reg_sad_mc_ctrl_pt_x2              :8 ,	// 15:8
	reg_sad_mc_ctrl_pt_y3              :8 ,	// 23:16
	reg_sad_mc_ctrl_pt_x3              :8 ;	// 31:24
}PE_O20_TNR_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc90184a8L tnr_ctrl_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_abs_mv_ctrl_pt_y0              :8 ,	// 7:0
	reg_abs_mv_ctrl_pt_x0              :8 ,	// 15:8
	reg_abs_mv_ctrl_pt_y1              :8 ,	// 23:16
	reg_abs_mv_ctrl_pt_x1              :8 ;	// 31:24
}PE_O20_TNR_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc90184acL tnr_ctrl_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_abs_mv_ctrl_pt_y2              :8 ,	// 7:0
	reg_abs_mv_ctrl_pt_x2              :8 ,	// 15:8
	reg_abs_mv_ctrl_pt_y3              :8 ,	// 23:16
	reg_abs_mv_ctrl_pt_x3              :8 ;	// 31:24
}PE_O20_TNR_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc90184b0L tnr_ctrl_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_ma_ctrl_pt_y0              :8 ,	// 7:0
	reg_sad_ma_ctrl_pt_x0              :8 ,	// 15:8
	reg_sad_ma_ctrl_pt_y1              :8 ,	// 23:16
	reg_sad_ma_ctrl_pt_x1              :8 ;	// 31:24
}PE_O20_TNR_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc90184b4L tnr_ctrl_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sad_ma_ctrl_pt_y2              :8 ,	// 7:0
	reg_sad_ma_ctrl_pt_x2              :8 ,	// 15:8
	reg_sad_ma_ctrl_pt_y3              :8 ,	// 23:16
	reg_sad_ma_ctrl_pt_x3              :8 ;	// 31:24
}PE_O20_TNR_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc90184b8L pe0_debug3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mif_prefetch_ctrl                  :8 ,	// 7:0
	mif_vreverse_en                    :11,	// 18:8
	reserved01                         :1 ,	// reserved
	global_cg_blk_off                  :4 ,	// 23:20
	power_cg_blk_off                   :4 ;	// 27:24
}PE_O20_PE0_DEBUG3_T;
/*-----------------------------------------------------------------------------
                             0xc90184c0L fbc_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dcof_off                       :1 ,	// 0 
	reg_abab_pr_off                    :1 ,	// 1 
	reg_abab_ls_off                    :1 ,	// 2 
	reg_aabb_off                       :1 ,	// 3 
	reserved01                         :4 ,	// reserved
	reg_abba_off                       :1 ,	// 8 
	reserved02                         :1 ,	// reserved
	reg_abab_th                        :6 ;	// 15:10
}PE_O20_FBC_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc90184c4L fbc_ctrl_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dcof_off                       :1 ,	// 0 
	reg_abab_pr_off                    :1 ,	// 1 
	reg_abab_ls_off                    :1 ,	// 2 
	reg_aabb_off                       :1 ,	// 3 
	reserved01                         :4 ,	// reserved
	reg_abba_off                       :1 ,	// 8 
	reserved02                         :1 ,	// reserved
	reg_abab_th                        :6 ;	// 15:10
}PE_O20_FBC_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc90184d0L gfd_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_h_th0_a                    :8 ,	// 7:0
	reg_gfd_h_th1_a                    :8 ,	// 15:8
	reg_gfd_h_th0_b                    :8 ,	// 23:16
	reg_gfd_h_th1_b                    :8 ;	// 31:24
}PE_O20_GFD_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc90184d4L gfd_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_s_th                       :8 ,	// 7:0
	reg_gfd_v_th                       :8 ,	// 15:8
	reserved01                         :14,	// reserved
	reg_scale                          :2 ;	// 31:30
}PE_O20_GFD_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc90184d8L gfd_stat_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_a01                  :16,	// 15:0
	reg_gfd_count_a00                  :16;	// 31:16
}PE_O20_GFD_STAT_00_T;
/*-----------------------------------------------------------------------------
                             0xc90184dcL gfd_stat_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_a11                  :16,	// 15:0
	reg_gfd_count_a10                  :16;	// 31:16
}PE_O20_GFD_STAT_01_T;
/*-----------------------------------------------------------------------------
                             0xc90184e0L gfd_stat_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_b01                  :16,	// 15:0
	reg_gfd_count_b00                  :16;	// 31:16
}PE_O20_GFD_STAT_02_T;
/*-----------------------------------------------------------------------------
                             0xc90184e4L gfd_stat_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gfd_count_b11                  :16,	// 15:0
	reg_gfd_count_b10                  :16;	// 31:16
}PE_O20_GFD_STAT_03_T;



/*-----------------------------------------------------------------------------
                             0xc9018500L pe0_load                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :1 ,	// reserved
	load_enable                        :1 ,	// 1 
	load_type                          :1 ;	// 2 
}PE_O20_PE0_LOAD_T;
/*-----------------------------------------------------------------------------
                             0xc9018504L pe0_intr                             
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
}PE_O20_PE0_INTR_T;
/*-----------------------------------------------------------------------------
                             0xc9018508L pe0_status0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	dnr_frame_id                       :8 ,	// 23:16
	pic_init_frame_id                  :4 ;	// 27:24
}PE_O20_PE0_STATUS0_T;
/*-----------------------------------------------------------------------------
                             0xc901850cL pe0_status1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_cnt                           :11,	// 10:0
	reserved01                         :5 ,	// reserved
	timer_cnt                          :16;	// 31:16
}PE_O20_PE0_STATUS1_T;
/*-----------------------------------------------------------------------------
                             0xc9018510L pe0_opmode                             
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
}PE_O20_PE0_OPMODE_T;
/*-----------------------------------------------------------------------------
                             0xc9018514L pe0_in_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :1 ,	// reserved
	chroma_sampling_type               :3 ,	// 15:13
	vsize                              :12;	// 27:16
}PE_O20_PE0_IN_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9018518L pe0_in_offset                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hoffset                            :12,	// 11:0
	reserved01                         :18,	// reserved
	hsize_sel                          :1 ,	// 30
	crop_en                            :1 ;	// 31
}PE_O20_PE0_IN_OFFSET_T;
/*-----------------------------------------------------------------------------
                             0xc901851cL pe0_out_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsize                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	vsize                              :12;	// 27:16
}PE_O20_PE0_OUT_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc9018520L win_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y0                                 :12;	// 27:16
}PE_O20_WIN_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018524L win_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O20_WIN_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9018528L win_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x0                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y0                                 :12,	// 27:16
	ac_bnr_feature_cal_mode            :2 ;	// 29:28
}PE_O20_WIN_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc901852cL win_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1                                 :11,	// 10:0
	reserved01                         :5 ,	// reserved
	y1                                 :12;	// 27:16
}PE_O20_WIN_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9018530L cup_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bypass                             :1 ,	// 0 
	reg_v_upsample_en                  :1 ,	// 1 
	reg_h_upsample_en                  :1 ,	// 2 
	reg_sd_mode                        :1 ;	// 3 
}PE_O20_CUP_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018534L cup_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bypass                             :1 ,	// 0 
	reg_v_upsample_en                  :1 ,	// 1 
	reg_h_upsample_en                  :1 ,	// 2 
	reg_sd_mode                        :1 ;	// 3 
}PE_O20_CUP_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018538L cup_ctrl_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_CUP_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc9018580L vfilter_ctrl_00                             
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
}PE_O20_VFILTER_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc9018584L vfilter_ctrl_01                             
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
}PE_O20_VFILTER_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc9018588L vfilter_ctrl_02                             
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
}PE_O20_VFILTER_CTRL_02_T;
/*-----------------------------------------------------------------------------
                             0xc901858cL cti_ctrl_0                             
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
}PE_O20_REG_CTI_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018590L cti_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cti_coring_th0                     :8 ,	// 7:0
	cti_coring_th1                     :8 ,	// 15:8
	cti_coring_smooth                  :3 ,	// 18:16
	reserved01                         :1 ,	// reserved
	reg_cti_tap2                       :2 ;	// 21:20
}PE_O20_REG_CTI_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9018594L dnr_max_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dnr_max_enable                 :1 ,	// 0 
	reg_ifc_max_enable                 :1 ,	// 1 
	reg_dnr_ifc_sel                    :1 ,	// 2 
	reg_decon_max_sum_sel              :1 ,	// 3 
	reg_decon_ori_sel                  :1 ,	// 4 
	reg_decon_max_enable               :1 ,	// 5 
	reg_max_decon_dbg_en               :1 ,	// 6 
	reg_half_rate_cg_n                 :1 ,	// 7 
	reg_max_dbg_en                     :1 ,	// 8 
	reg_dnr_motion_sel                 :1 ,	// 9 
	reg_tnr_decon_en                   :1 ,	// 10
	reserved01                         :5 ,	// reserved
	reg_win_en                         :1 ,	// 16
	reg_bdr_en                         :1 ,	// 17
	reg_win_inout                      :1 ,	// 18
	reserved02                         :2 ,	// reserved
	reg_ipc_motion_en                  :1 ,	// 21
	reg_motion_bit_ctrl                :3 ,	// 24:22
	reg_delta_ifc_th                   :7 ;	// 31:25
}PE_O20_DNR_MAX_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9018598L dnr_dbar_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dbg_en                         :1 ,	// 0 
	reg_show_f3d                       :1 ,	// 1 
	reg_show_bnr                       :1 ,	// 2 
	reg_f3d_mode                       :1 ,	// 3 
	reg_acness_or_acness_gain          :1 ;	// 4 
}PE_O20_DNR_DBAR_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc901859cL reg_c420_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_detect_level_th                :10;	// 25:16
}PE_O20_REG_C420_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90185a0L mnr_ctrl_0                             
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
}PE_O20_MNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90185a4L mnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_y_max                      :8 ,	// 7:0
	reg_mmd_y_min                      :8 ,	// 15:8
	reg_mmd_x_max                      :8 ,	// 23:16
	reg_mmd_x_min                      :8 ;	// 31:24
}PE_O20_MNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90185a8L mnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mnr_debug_mode                 :4 ,	// 3:0
	reg_mnr_debug_en                   :1 ,	// 4 
	reserved01                         :19,	// reserved
	reg_equal_snr_th                   :8 ;	// 31:24
}PE_O20_MNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90185acL mnr_ctrl_3                             
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
}PE_O20_MNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90185b0L mnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_fil_x_3                    :8 ,	// 7:0
	reg_mmd_fil_x_2                    :8 ,	// 15:8
	reg_mmd_fil_x_1                    :8 ,	// 23:16
	reg_mmd_fil_x_0                    :8 ;	// 31:24
}PE_O20_MNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90185b4L mnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_fil_y_3                    :8 ,	// 7:0
	reg_mmd_fil_y_2                    :8 ,	// 15:8
	reg_mmd_fil_y_1                    :8 ,	// 23:16
	reg_mmd_fil_y_0                    :8 ;	// 31:24
}PE_O20_MNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90185b8L detail_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_detail_max              :8 ,	// 7:0
	reg_bnr_ac_detail_min              :8 ,	// 15:8
	reg_bnr_diff_l                     :8 ,	// 23:16
	reg_bnr_diff_p                     :8 ;	// 31:24
}PE_O20_DETAIL_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc90185bcL dc_bnr_ctrl_0                             
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
}PE_O20_DC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90185c0L dc_bnr_ctrl_1                             
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
}PE_O20_DC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90185c4L dc_bnr_ctrl_2                             
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
}PE_O20_DC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90185c8L dc_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_bnr_var_th3                 :8 ,	// 7:0
	reg_dc_bnr_var_th2                 :8 ,	// 15:8
	reg_dc_bnr_var_th1                 :8 ,	// 23:16
	reg_dc_bnr_var_th0                 :8 ;	// 31:24
}PE_O20_DC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90185ccL dc_bnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_motion_y_min                :8 ,	// 7:0
	reg_dc_motion_y_max                :8 ;	// 15:8
}PE_O20_DC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90185d0L dc_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dc_var_y_th0                   :8 ,	// 7:0
	reg_dc_var_y_th1                   :8 ,	// 15:8
	reg_dc_var_y_th2                   :8 ,	// 23:16
	reg_dc_var_y_th3                   :8 ;	// 31:24
}PE_O20_DC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90185d4L ac_bnr_ctrl_0                             
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
}PE_O20_AC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90185d8L ac_bnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_global_motion_th        :8 ,	// 7:0
	reg_bnr_ac_h_acness_max            :8 ,	// 15:8
	reg_bnr_ac_h_acness_min            :8 ,	// 23:16
	reg_bnr_ac_bin_th                  :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90185dcL ac_bnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_motion_3                :8 ,	// 7:0
	reg_bnr_ac_motion_2                :8 ,	// 15:8
	reg_bnr_ac_motion_1                :8 ,	// 23:16
	reg_bnr_ac_motion_0                :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90185e0L dnr_stat_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	c420_tearing_cnt                   :16,	// 15:0
	global_motion_iir                  :8 ,	// 23:16
	global_dc_gain                     :8 ;	// 31:24
}PE_O20_DNR_STAT_0_T;
/*-----------------------------------------------------------------------------
                             0xc90185e4L ac_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_motion_y_3              :8 ,	// 7:0
	reg_bnr_ac_motion_y_2              :8 ,	// 15:8
	reg_bnr_ac_motion_y_1              :8 ,	// 23:16
	reg_bnr_ac_motion_y_0              :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90185e8L ac_bnr_ctrl_4                             
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
}PE_O20_AC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90185ecL dnr_stat_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_v_l                         :8 ,	// 7:0
	acness_h_l                         :8 ,	// 15:8
	acness_v_g                         :8 ,	// 23:16
	acness_h_g                         :8 ;	// 31:24
}PE_O20_DNR_STAT_1_T;
/*-----------------------------------------------------------------------------
                             0xc90185f0L ac_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_detail_th4              :8 ,	// 7:0
	reg_bnr_ac_detail_th3              :8 ,	// 15:8
	reg_bnr_ac_detail_th2              :8 ,	// 23:16
	reg_bnr_ac_detail_th1              :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc90185f4L ac_bnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_pos_gain_h2             :8 ,	// 7:0
	reg_bnr_ac_pos_gain_h1             :8 ,	// 15:8
	reg_bnr_ac_pos_gain_h0             :8 ,	// 23:16
	reg_bnr_ac_detail_gain_th          :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90185f8L ac_bnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bnr_ac_pos_gain_l2             :8 ,	// 7:0
	reg_bnr_ac_pos_gain_l1             :8 ,	// 15:8
	reg_bnr_ac_pos_gain_l0             :8 ,	// 23:16
	reg_bnr_ac_pos_gain_h3             :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90185fcL dnr_stat_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_init                             :8 ,	// 7:0
	v_init                             :8 ,	// 15:8
	reserved01                         :4 ,	// reserved
	reg_vfilter_tearing_cnt            :12;	// 31:20
}PE_O20_DNR_STAT_2_T;
/*-----------------------------------------------------------------------------
                             0xc9018600L ac_bnr_ctrl_8                             
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
}PE_O20_AC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9018604L ac_bnr_ctrl_9                             
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
}PE_O20_AC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9018608L ac_bnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ac_detail_gain_y_min           :8 ,	// 7:0
	reg_ac_detail_gain_y_max           :8 ,	// 15:8
	reg_bnr_ac_acness_y_min            :8 ,	// 23:16
	reg_bnr_ac_acness_y_max            :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901860cL ac_bnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ac_detail_alpha2_y_min         :8 ,	// 7:0
	reg_ac_detail_alpha2_y_max         :8 ,	// 15:8
	reg_ac_detail_alpha4_y_min         :8 ,	// 23:16
	reg_ac_detail_alpha4_y_max         :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9018610L ac_bnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_g_motion_manual                :8 ,	// 7:0
	reg_acness_scale_mul               :8 ,	// 15:8
	reg_bnr_ac_detail_max              :8 ,	// 23:16
	reg_bnr_ac_detail_min              :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9018614L ifc_ctrl_0                             
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
}PE_O20_IFC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018618L ifc_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_ddrvt_gain_y1             :8 ,	// 7:0
	reg_edge_ddrvt_gain_x1             :8 ,	// 15:8
	reg_edge_ddrvt_gain_y0             :8 ,	// 23:16
	reg_edge_ddrvt_gain_x0             :8 ;	// 31:24
}PE_O20_IFC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc901861cL ifc_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_c_drvt_hcoef_sel               :3 ,	// 2:0
	reserved01                         :1 ,	// reserved
	reg_c_ddrvt_hcoef_sel              :2 ,	// 5:4
	reg_c_edge_gain_res                :1 ;	// 6 
}PE_O20_IFC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9018620L ifc_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_c_edge_gain_y1                 :8 ,	// 7:0
	reg_c_edge_gain_x1                 :8 ,	// 15:8
	reg_c_edge_gain_y0                 :8 ,	// 23:16
	reg_c_edge_gain_x0                 :8 ;	// 31:24
}PE_O20_IFC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9018624L ifc_ctrl_4                             
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
}PE_O20_IFC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9018628L ifc_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_crs_gain_y1                    :8 ,	// 7:0
	reg_crs_gain_x1                    :8 ,	// 15:8
	reg_crs_gain_y0                    :8 ,	// 23:16
	reg_crs_gain_x0                    :8 ;	// 31:24
}PE_O20_IFC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc901862cL ifc_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9018630L ifc_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9018634L ifc_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ifc_en                         :1 ,	// 0 
	reg_clp_on                         :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	reg_edge_en                        :1 ,	// 4 
	reserved02                         :15,	// reserved
	reg_clp_tap                        :2 ,	// 21:20
	reg_ifc_flt_sel                    :2 ,	// 23:22
	reg_debug_en                       :2 ,	// 25:24
	reg_debug_mode                     :4 ,	// 29:26
	reg_bld_tap                        :2 ;	// 31:30
}PE_O20_IFC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9018638L ifc_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc901863cL ifc_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9018640L ifc_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc9018644L ifc_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_crs_zero_th                    :8 ,	// 23:16
	reg_dst_cdst_th                    :8 ;	// 31:24
}PE_O20_IFC_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9018648L ifc_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc901864cL ifc_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc9018650L ifc_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_medge_gain_y1                  :8 ,	// 7:0
	reg_medge_gain_x1                  :8 ,	// 15:8
	reg_medge_gain_y0                  :8 ,	// 23:16
	reg_medge_gain_x0                  :8 ;	// 31:24
}PE_O20_IFC_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc9018654L ifc_ctrl_16                             
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
}PE_O20_IFC_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc9018658L ifc_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_crs_op_gain_y1                 :8 ,	// 7:0
	reg_crs_op_gain_x1                 :8 ,	// 15:8
	reg_crs_op_gain_y0                 :8 ,	// 23:16
	reg_crs_op_gain_x0                 :8 ;	// 31:24
}PE_O20_IFC_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc901865cL ifc_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc9018660L ifc_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :16,	// reserved
	reg_medge_op_th                    :8 ,	// 23:16
	reg_mmd_gain_en                    :1 ,	// 24
	reg_mmd_gain_flt                   :2 ,	// 26:25
	reg_mmd_gain_tap                   :2 ,	// 28:27
	reg_mmd_gain_res                   :1 ;	// 29
}PE_O20_IFC_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc9018664L ifc_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_IFC_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc9018668L ifc_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_gain_y1                    :8 ,	// 7:0
	reg_mmd_gain_x1                    :8 ,	// 15:8
	reg_mmd_gain_y0                    :8 ,	// 23:16
	reg_mmd_gain_x0                    :8 ;	// 31:24
}PE_O20_IFC_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc901866cL sc_bnr_ctrl_0                             
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
}PE_O20_SC_BNR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018670L sc_bnr_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_post2_iir_gain                 :8 ,	// 7:0
	reg_frm_cnt_th                     :8 ,	// 15:8
	reg_bin_ratio_th                   :8 ,	// 23:16
	reg_detect_th                      :8 ;	// 31:24
}PE_O20_SC_BNR_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc9018674L sc_bnr_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bin_ratio_div                  :8 ,	// 7:0
	reg_bin_ratio_mul                  :8 ,	// 15:8
	reg_min_bin_th                     :8 ,	// 23:16
	reg_detector_iir_gain              :8 ;	// 31:24
}PE_O20_SC_BNR_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9018678L sc_bnr_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_grid_th1                       :8 ,	// 7:0
	reg_grid_th2                       :8 ,	// 15:8
	reg_grid_th3                       :8 ;	// 23:16
}PE_O20_SC_BNR_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc901867cL sc_bnr_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pos_gain_th                    :8 ,	// 7:0
	reserved01                         :11,	// reserved
	reg_scale_div_v                    :4 ,	// 22:19
	reg_scale_mul_v                    :9 ;	// 31:23
}PE_O20_SC_BNR_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9018680L sc_bnr_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_pos_gain_3                     :8 ,	// 7:0
	reg_pos_gain_2                     :8 ,	// 15:8
	reg_pos_gain_1                     :8 ,	// 23:16
	reg_pos_gain_0                     :8 ;	// 31:24
}PE_O20_SC_BNR_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc9018684L sc_bnr_ctrl_6                             
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
}PE_O20_SC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9018688L c_pre_blur_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pre_121_blur_en                    :1 ,	// 0 
	pre_median_en                      :1 ;	// 1 
}PE_O20_C_PRE_BLUR_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc901869cL ac_bnr_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_acness_gain_h_l                :8 ,	// 15:8
	reg_acness_gain_h_g                :8 ,	// 23:16
	reg_acness_gain_h                  :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90186a0L ac_bnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_acness_gain_v_l                :8 ,	// 15:8
	reg_acness_gain_v_g                :8 ,	// 23:16
	reg_acness_gain_v                  :8 ;	// 31:24
}PE_O20_AC_BNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90186a4L dc_bnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_x_th0               :8 ,	// 7:0
	reg_fil_motion_x_th1               :8 ,	// 15:8
	reg_fil_motion_x_th2               :8 ,	// 23:16
	reg_fil_motion_x_th3               :8 ;	// 31:24
}PE_O20_DC_BNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90186a8L dc_bnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_y_th0               :8 ,	// 7:0
	reg_fil_motion_y_th1               :8 ,	// 15:8
	reg_fil_motion_y_th2               :8 ,	// 23:16
	reg_fil_motion_y_th3               :8 ;	// 31:24
}PE_O20_DC_BNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90186acL sqm_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_mmd_sel                        :2 ,	// 1:0
	reserved01                         :6 ,	// reserved
	reg_hist_bin_th0                   :8 ,	// 15:8
	reg_hist_bin_th1                   :8 ,	// 23:16
	reg_hist_bin_th2                   :8 ;	// 31:24
}PE_O20_SQM_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90186b0L sqm_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hist_bin_th3                   :8 ,	// 7:0
	reg_hist_bin_th4                   :8 ,	// 15:8
	reg_hist_bin_th5                   :8 ,	// 23:16
	reg_hist_bin_th6                   :8 ;	// 31:24
}PE_O20_SQM_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc90186b4L sqm_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_trans_mmd_th                   :8 ,	// 7:0
	reserved01                         :2 ,	// reserved
	reg_edge_a_th                      :10,	// 19:10
	reg_edf_mmd_th                     :8 ;	// 27:20
}PE_O20_SQM_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90186b8L sqm_ctrl_3                             
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
}PE_O20_SQM_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90186bcL sqm_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_sqm_win_mode_y1                :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_sqm_win_mode_y0                :13;	// 28:16
}PE_O20_SQM_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc90186c0L tpd_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_tp_binary_th                   :8 ;	// 7:0
}PE_O20_TPD_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc90186c4L window_mode_0                             
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
}PE_O20_WINDOW_MODE_0_T;
/*-----------------------------------------------------------------------------
                             0xc90186c8L window_mode_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_win_mode_y1                    :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_win_mode_y0                    :13;	// 28:16
}PE_O20_WINDOW_MODE_1_T;
/*-----------------------------------------------------------------------------
                             0xc90186d0L dnr_stat_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_v_g                         :8 ,	// 7:0
	acness_h_g                         :8 ,	// 15:8
	acness_v                           :8 ,	// 23:16
	acness_h                           :8 ;	// 31:24
}PE_O20_DNR_STAT_3_T;
/*-----------------------------------------------------------------------------
                             0xc90186d4L dnr_stat_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bad_up_cnt                         :12,	// 11:0
	reserved01                         :4 ,	// reserved
	acness_v_l                         :8 ,	// 23:16
	acness_h_l                         :8 ;	// 31:24
}PE_O20_DNR_STAT_4_T;
/*-----------------------------------------------------------------------------
                             0xc90186d8L dnr_stat_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_gain_v_l                    :8 ,	// 7:0
	acness_gain_h_l                    :8 ,	// 15:8
	acness_gain_v_g                    :8 ,	// 23:16
	acness_gain_h_g                    :8 ;	// 31:24
}PE_O20_DNR_STAT_5_T;
/*-----------------------------------------------------------------------------
                             0xc90186dcL dnr_stat_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_DNR_STAT_6_T;
/*-----------------------------------------------------------------------------
                             0xc90186e0L dnr_stat_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	acness_gain_v                      :8 ,	// 7:0
	acness_gain_h                      :8 ,	// 15:8
	acness_v_iir                       :8 ,	// 23:16
	acness_h_iir                       :8 ;	// 31:24
}PE_O20_DNR_STAT_7_T;
/*-----------------------------------------------------------------------------
                             0xc90186e4L dnr_stat_8_sc_bnr0                             
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
}PE_O20_DNR_STAT_8_SC_BNR0_T;
/*-----------------------------------------------------------------------------
                             0xc90186e8L dnr_stat_9_sc_bnr1                             
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
}PE_O20_DNR_STAT_9_SC_BNR1_T;
/*-----------------------------------------------------------------------------
                             0xc90186ecL dnr_stat_10_sc_bnr2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w_max_index_iir_v                  :7 ;	// 6:0
}PE_O20_DNR_STAT_10_SC_BNR2_T;
/*-----------------------------------------------------------------------------
                             0xc90186f0L dnr_stat_11_sqm_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_1                           :16,	// 15:0
	e_hist_0                           :16;	// 31:16
}PE_O20_DNR_STAT_11_SQM_00_T;
/*-----------------------------------------------------------------------------
                             0xc90186f4L dnr_stat_12_sqm_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_3                           :16,	// 15:0
	e_hist_2                           :16;	// 31:16
}PE_O20_DNR_STAT_12_SQM_01_T;
/*-----------------------------------------------------------------------------
                             0xc90186f8L dnr_stat_13_sqm_02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_5                           :16,	// 15:0
	e_hist_4                           :16;	// 31:16
}PE_O20_DNR_STAT_13_SQM_02_T;
/*-----------------------------------------------------------------------------
                             0xc90186fcL dnr_stat_14_sqm_03                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	e_hist_7                           :16,	// 15:0
	e_hist_6                           :16;	// 31:16
}PE_O20_DNR_STAT_14_SQM_03_T;
/*-----------------------------------------------------------------------------
                             0xc9018700L dnr_stat_15_sqm_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_1                           :16,	// 15:0
	f_hist_0                           :16;	// 31:16
}PE_O20_DNR_STAT_15_SQM_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018704L dnr_stat_16_sqm_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_3                           :16,	// 15:0
	f_hist_2                           :16;	// 31:16
}PE_O20_DNR_STAT_16_SQM_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018708L dnr_stat_17_sqm_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_5                           :16,	// 15:0
	f_hist_4                           :16;	// 31:16
}PE_O20_DNR_STAT_17_SQM_06_T;
/*-----------------------------------------------------------------------------
                             0xc901870cL dnr_stat_18_sqm_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	f_hist_7                           :16,	// 15:0
	f_hist_6                           :16;	// 31:16
}PE_O20_DNR_STAT_18_SQM_07_T;
/*-----------------------------------------------------------------------------
                             0xc9018710L dnr_stat_19_sqm_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_1                           :16,	// 15:0
	t_hist_0                           :16;	// 31:16
}PE_O20_DNR_STAT_19_SQM_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018714L dnr_stat_20_sqm_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_3                           :16,	// 15:0
	t_hist_2                           :16;	// 31:16
}PE_O20_DNR_STAT_20_SQM_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018718L dnr_stat_21_sqm_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_5                           :16,	// 15:0
	t_hist_4                           :16;	// 31:16
}PE_O20_DNR_STAT_21_SQM_10_T;
/*-----------------------------------------------------------------------------
                             0xc901871cL dnr_stat_22_sqm_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	t_hist_7                           :16,	// 15:0
	t_hist_6                           :16;	// 31:16
}PE_O20_DNR_STAT_22_SQM_11_T;
/*-----------------------------------------------------------------------------
                             0xc9018720L dnr_stat_23_tpd_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_h_cnt_2                        :16,	// 15:0
	res_h_cnt_1                        :16;	// 31:16
}PE_O20_DNR_STAT_23_TPD_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018724L dnr_stat_24_tpd_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_v_cnt_2                        :16,	// 15:0
	res_v_cnt_1                        :16;	// 31:16
}PE_O20_DNR_STAT_24_TPD_1_T;
/*-----------------------------------------------------------------------------
                             0xc9018728L dnr_stat_25_tpd_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	res_v_cnt_3                        :16,	// 15:0
	res_h_cnt_3                        :16;	// 31:16
}PE_O20_DNR_STAT_25_TPD_2_T;
/*-----------------------------------------------------------------------------
                             0xc9018730L ac_bnr_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_x_th3               :8 ,	// 7:0
	reg_fil_motion_x_th2               :8 ,	// 15:8
	reg_fil_motion_x_th1               :8 ,	// 23:16
	reg_fil_motion_x_th0               :8 ;	// 31:24
}PE_O20_AC_BNR_15_T;
/*-----------------------------------------------------------------------------
                             0xc9018734L ac_bnr_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_fil_motion_y_th3               :8 ,	// 7:0
	reg_fil_motion_y_th2               :8 ,	// 15:8
	reg_fil_motion_y_th1               :8 ,	// 23:16
	reg_fil_motion_y_th0               :8 ;	// 31:24
}PE_O20_AC_BNR_16_T;
/*-----------------------------------------------------------------------------
                             0xc9018738L vfilter_ctrl_03                             
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
}PE_O20_VFILTER_CTRL_03_T;
/*-----------------------------------------------------------------------------
                             0xc901873cL vfilter_ctrl_04                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_x_3                     :8 ,	// 7:0
	reg_motion_x_2                     :8 ,	// 15:8
	reg_motion_x_1                     :8 ,	// 23:16
	reg_motion_x_0                     :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_04_T;
/*-----------------------------------------------------------------------------
                             0xc9018740L vfilter_ctrl_05                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_y_3                     :8 ,	// 7:0
	reg_motion_y_2                     :8 ,	// 15:8
	reg_motion_y_1                     :8 ,	// 23:16
	reg_motion_y_0                     :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_05_T;
/*-----------------------------------------------------------------------------
                             0xc9018744L vfilter_ctrl_06                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_global_x_3                     :8 ,	// 7:0
	reg_global_x_2                     :8 ,	// 15:8
	reg_global_x_1                     :8 ,	// 23:16
	reg_global_x_0                     :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_06_T;
/*-----------------------------------------------------------------------------
                             0xc9018748L vfilter_ctrl_07                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_global_y_3                     :8 ,	// 7:0
	reg_global_y_2                     :8 ,	// 15:8
	reg_global_y_1                     :8 ,	// 23:16
	reg_global_y_0                     :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_07_T;
/*-----------------------------------------------------------------------------
                             0xc901874cL vfilter_ctrl_08                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_x_3                      :8 ,	// 7:0
	reg_blend_x_2                      :8 ,	// 15:8
	reg_blend_x_1                      :8 ,	// 23:16
	reg_blend_x_0                      :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_08_T;
/*-----------------------------------------------------------------------------
                             0xc9018750L vfilter_ctrl_09                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blend_y_3                      :8 ,	// 7:0
	reg_blend_y_2                      :8 ,	// 15:8
	reg_blend_y_1                      :8 ,	// 23:16
	reg_blend_y_0                      :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_09_T;
/*-----------------------------------------------------------------------------
                             0xc9018754L vfilter_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_x_3                        :8 ,	// 7:0
	reg_hmc_x_2                        :8 ,	// 15:8
	reg_hmc_x_1                        :8 ,	// 23:16
	reg_hmc_x_0                        :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9018758L vfilter_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_y_3                        :8 ,	// 7:0
	reg_hmc_y_2                        :8 ,	// 15:8
	reg_hmc_y_1                        :8 ,	// 23:16
	reg_hmc_y_0                        :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc901875cL vfilter_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_local_x_3                      :8 ,	// 7:0
	reg_local_x_2                      :8 ,	// 15:8
	reg_local_x_1                      :8 ,	// 23:16
	reg_local_x_0                      :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc9018760L vfilter_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_hmc_y_3                        :8 ,	// 7:0
	reg_local_y_2                      :8 ,	// 15:8
	reg_local_y_1                      :8 ,	// 23:16
	reg_local_y_0                      :8 ;	// 31:24
}PE_O20_VFILTER_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc9018764L reg_decon_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_use_osd_map         :1 ,	// 0 
	reg_2nd_out_rd_out_clip            :1 ,	// 1 
	reg_1st_out_rd_out_clip            :1 ,	// 2 
	reserved01                         :4 ,	// reserved
	reg_decon_dnr_motion_sel           :1 ,	// 7 
	reg_11bit_debug_mode_en            :1 ,	// 8 
	reg_out_bit_opt                    :1 ,	// 9 
	reg_tnr_decon_out_bit_sel          :1 ,	// 10
	reg_tnr_decon_in_bit_sel           :1 ,	// 11
	reg_1st_out_rd_max_alpha           :8 ,	// 19:12
	reg_1st_out_rd_min_alpha           :8 ,	// 27:20
	reg_1st_out_rd_bit                 :3 ,	// 30:28
	reg_1st_out_rd_on                  :1 ;	// 31
}PE_O20_REG_DECON_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc9018768L reg_decon_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_min_pel_cb          :12,	// 11:0
	reg_1st_out_rd_min_pel_yy          :12;	// 23:12
}PE_O20_REG_DECON_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc901876cL reg_decon_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_yy          :12,	// 11:0
	reg_1st_out_rd_min_pel_cr          :12;	// 23:12
}PE_O20_REG_DECON_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc9018770L reg_decon_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_max_pel_cr          :12,	// 11:0
	reg_1st_out_rd_max_pel_cb          :12;	// 23:12
}PE_O20_REG_DECON_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc9018774L reg_decon_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc9018778L reg_decon_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc901877cL reg_decon_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_1st_out_rd_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc9018780L reg_decon_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_bit                 :4 ,	// 7:4
	reserved02                         :3 ,	// reserved
	reg_2nd_out_rd_use_osd_map         :1 ,	// 11
	reg_2nd_out_rd_max_alpha           :8 ,	// 19:12
	reg_2nd_out_rd_min_alpha           :8 ,	// 27:20
	reserved03                         :3 ,	// reserved
	reg_2nd_out_rd_on                  :1 ;	// 31
}PE_O20_REG_DECON_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc9018784L reg_decon_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_min_pel_cb          :12,	// 11:0
	reg_2nd_out_rd_min_pel_yy          :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_2nd_out_rd_max_lsb_2b          :2 ,	// 29:28
	reg_2nd_out_rd_min_lsb_2b          :2 ;	// 31:30
}PE_O20_REG_DECON_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9018788L reg_decon_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_yy          :12,	// 11:0
	reg_2nd_out_rd_min_pel_cr          :12;	// 23:12
}PE_O20_REG_DECON_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc901878cL reg_decon_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_max_pel_cr          :12,	// 11:0
	reg_2nd_out_rd_max_pel_cb          :12;	// 23:12
}PE_O20_REG_DECON_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc9018790L reg_dc_bnr_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_x3                        :8 ,	// 7:0
	reg_gain_x2                        :8 ,	// 15:8
	reg_gain_x1                        :8 ,	// 23:16
	reg_gain_x0                        :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc9018794L reg_dc_bnr_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_x7                        :8 ,	// 7:0
	reg_gain_x6                        :8 ,	// 15:8
	reg_gain_x5                        :8 ,	// 23:16
	reg_gain_x4                        :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc9018798L reg_dc_bnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_y3                        :8 ,	// 7:0
	reg_gain_y2                        :8 ,	// 15:8
	reg_gain_y1                        :8 ,	// 23:16
	reg_gain_y0                        :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc901879cL reg_dc_bnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_gain_y7                        :8 ,	// 7:0
	reg_gain_y6                        :8 ,	// 15:8
	reg_gain_y5                        :8 ,	// 23:16
	reg_gain_y4                        :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90187a0L reg_cti_ctrl_2                             
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
}PE_O20_REG_CTI_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc90187a4L reg_cti_ctrl_3                             
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
}PE_O20_REG_CTI_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc90187a8L reg_mnr_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_small_mmd_flat_th              :8 ,	// 7:0
	reg_large_mmd_flat_th              :8 ,	// 15:8
	reserved01                         :12,	// reserved
	reg_mmd_chroma_gain_en             :1 ,	// 28
	reg_mmd_dist_kernal_width          :2 ,	// 30:29
	reg_mmd_dist_gain_en               :1 ;	// 31
}PE_O20_REG_MNR_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc90187acL reg_mnr_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dist_gain_x3                   :8 ,	// 7:0
	reg_dist_gain_x2                   :8 ,	// 15:8
	reg_dist_gain_x1                   :8 ,	// 23:16
	reg_dist_gain_x0                   :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc90187b0L reg_mnr_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_dist_gain_y3                   :8 ,	// 7:0
	reg_dist_gain_y2                   :8 ,	// 15:8
	reg_dist_gain_y1                   :8 ,	// 23:16
	reg_dist_gain_y0                   :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc90187b4L reg_mnr_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chroma_gain_x3                 :8 ,	// 7:0
	reg_chroma_gain_x2                 :8 ,	// 15:8
	reg_chroma_gain_x1                 :8 ,	// 23:16
	reg_chroma_gain_x0                 :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc90187b8L reg_mnr_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_chroma_gain_y3                 :8 ,	// 7:0
	reg_chroma_gain_y2                 :8 ,	// 15:8
	reg_chroma_gain_y1                 :8 ,	// 23:16
	reg_chroma_gain_y0                 :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc90187bcL reg_mnr_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_i_sel_mmd_x3                   :8 ,	// 7:0
	reg_i_sel_mmd_x2                   :8 ,	// 15:8
	reg_i_sel_mmd_x1                   :8 ,	// 23:16
	reg_i_sel_mmd_x0                   :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90187c0L reg_mnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_i_sel_mmd_y3                   :8 ,	// 7:0
	reg_i_sel_mmd_y2                   :8 ,	// 15:8
	reg_i_sel_mmd_y1                   :8 ,	// 23:16
	reg_i_sel_mmd_y0                   :8 ;	// 31:24
}PE_O20_REG_MNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90187c4L reg_decon_ctrl_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_11_T;
/*-----------------------------------------------------------------------------
                             0xc90187c8L reg_decon_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc90187ccL reg_decon_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_out_rd_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90187d0L reg_decon_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90187d4L reg_decon_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90187d8L reg_decon_ctrl_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_err_out_rd_simple_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_16_T;
/*-----------------------------------------------------------------------------
                             0xc90187dcL reg_decon_ctrl_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_lb_var_cut_res            :4 ,	// 3:0
	reserved01                         :2 ,	// reserved
	reg_blur_lb_var_en                 :1 ,	// 6 
	reg_l6_var_2x2_bit                 :1 ,	// 7 
	reg_force_block_v                  :6 ,	// 13:8
	reg_1st_debug_en                   :1 ,	// 14
	reg_l6_var_csc_en                  :1 ,	// 15
	reg_force_block_no_h               :6 ,	// 21:16
	reg_4k_5x3_mode_en                 :1 ,	// 22
	reg_rd_simple_clip                 :1 ,	// 23
	reg_rd_clip                        :1 ,	// 24
	reg_input_csc_en                   :1 ,	// 25
	reg_1st_debug_mode                 :4 ,	// 29:26
	reg_force_block_no_en              :1 ,	// 30
	reg_decon_1st_en                   :1 ;	// 31
}PE_O20_REG_DECON_CTRL_17_T;
/*-----------------------------------------------------------------------------
                             0xc90187e0L reg_decon_ctrl_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_var_chroma_en                  :1 ,	// 0 
	reserved01                         :1 ,	// reserved
	reg_blur_final_size                :1 ,	// 2 
	reserved02                         :1 ,	// reserved
	reg_blur_div_zero                  :1 ,	// 4 
	reg_diff_hblur                     :2 ,	// 6:5
	reg_diff_vblur                     :2 ,	// 8:7
	reg_motion_shft                    :3 ,	// 11:9
	reg_motion_en                      :1 ,	// 12
	reg_led_10b_mode_blending          :1 ,	// 13
	reg_led_10b_mode_diff_pel          :1 ,	// 14
	reserved03                         :1 ,	// reserved
	reg_luma_bit_opt                   :1 ,	// 16
	reg_var_bit_opt                    :1 ,	// 17
	reg_l6_var_bit_opt                 :1 ,	// 18
	reg_l6_blur_bit_opt                :1 ,	// 19
	reg_var_v_gain                     :4 ,	// 23:20
	reg_var_h_gain                     :4 ,	// 27:24
	reg_var_cut_resolution             :4 ;	// 31:28
}PE_O20_REG_DECON_CTRL_18_T;
/*-----------------------------------------------------------------------------
                             0xc90187e4L reg_decon_ctrl_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_x_th0               :8 ,	// 7:0
	reg_decon_diff_x_th1               :8 ,	// 15:8
	reg_decon_diff_x_th2               :8 ,	// 23:16
	reg_decon_diff_x_th3               :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_19_T;
/*-----------------------------------------------------------------------------
                             0xc90187e8L reg_decon_ctrl_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_diff_y_th0               :8 ,	// 7:0
	reg_decon_diff_y_th1               :8 ,	// 15:8
	reg_decon_diff_y_th2               :8 ,	// 23:16
	reg_decon_diff_y_th3               :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_20_T;
/*-----------------------------------------------------------------------------
                             0xc90187ecL reg_decon_ctrl_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_x_th2                :10,	// 9:0
	reg_decon_var_x_th1                :10,	// 19:10
	reg_decon_var_x_th0                :10;	// 29:20
}PE_O20_REG_DECON_CTRL_21_T;
/*-----------------------------------------------------------------------------
                             0xc90187f0L reg_decon_ctrl_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_var_y_th1                :10,	// 9:0
	reg_decon_var_y_th0                :10,	// 19:10
	reg_decon_var_x_th3                :10;	// 29:20
}PE_O20_REG_DECON_CTRL_22_T;
/*-----------------------------------------------------------------------------
                             0xc90187f4L reg_decon_ctrl_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th0               :10,	// 9:0
	reg_decon_var_y_th3                :10,	// 19:10
	reg_decon_var_y_th2                :10;	// 29:20
}PE_O20_REG_DECON_CTRL_23_T;
/*-----------------------------------------------------------------------------
                             0xc90187f8L reg_decon_ctrl_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th3               :10,	// 9:0
	reg_decon_luma_x_th2               :10,	// 19:10
	reg_decon_luma_x_th1               :10;	// 29:20
}PE_O20_REG_DECON_CTRL_24_T;
/*-----------------------------------------------------------------------------
                             0xc90187fcL reg_decon_ctrl_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_x_th6               :10,	// 9:0
	reg_decon_luma_x_th5               :10,	// 19:10
	reg_decon_luma_x_th4               :10;	// 29:20
}PE_O20_REG_DECON_CTRL_25_T;
/*-----------------------------------------------------------------------------
                             0xc9018800L reg_decon_ctrl_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th1               :10,	// 9:0
	reg_decon_luma_y_th0               :10,	// 19:10
	reg_decon_luma_x_th7               :10;	// 29:20
}PE_O20_REG_DECON_CTRL_26_T;
/*-----------------------------------------------------------------------------
                             0xc9018804L reg_decon_ctrl_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th4               :10,	// 9:0
	reg_decon_luma_y_th3               :10,	// 19:10
	reg_decon_luma_y_th2               :10;	// 29:20
}PE_O20_REG_DECON_CTRL_27_T;
/*-----------------------------------------------------------------------------
                             0xc9018808L reg_decon_ctrl_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_luma_y_th7               :10,	// 9:0
	reg_decon_luma_y_th6               :10,	// 19:10
	reg_decon_luma_y_th5               :10;	// 29:20
}PE_O20_REG_DECON_CTRL_28_T;
/*-----------------------------------------------------------------------------
                             0xc901880cL reg_decon_ctrl_29                             
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
}PE_O20_REG_DECON_CTRL_29_T;
/*-----------------------------------------------------------------------------
                             0xc9018810L reg_decon_ctrl_30                             
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
}PE_O20_REG_DECON_CTRL_30_T;
/*-----------------------------------------------------------------------------
                             0xc9018814L reg_decon_ctrl_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_alpha_blur_l6_var_th1          :10,	// 9:0
	reg_alpha_blur_l6_var_th0          :10,	// 19:10
	reg_lb_var_cut_res                 :4 ,	// 23:20
	reg_master_gain                    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_31_T;
/*-----------------------------------------------------------------------------
                             0xc9018818L reg_decon_ctrl_32                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_x_th2                   :10,	// 9:0
	reg_l6_var_x_th1                   :10,	// 19:10
	reg_l6_var_x_th0                   :10,	// 29:20
	reg_lb_var_opt                     :1 ,	// 30
	reg_lb_var_en                      :1 ;	// 31
}PE_O20_REG_DECON_CTRL_32_T;
/*-----------------------------------------------------------------------------
                             0xc901881cL reg_decon_ctrl_33                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th1                   :10,	// 9:0
	reg_l6_var_y_th0                   :10,	// 19:10
	reg_l6_var_x_th3                   :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_lb_var_lut_bit                 :1 ;	// 31
}PE_O20_REG_DECON_CTRL_33_T;
/*-----------------------------------------------------------------------------
                             0xc9018820L reg_decon_ctrl_34                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_y_th3                   :10,	// 9:0
	reg_l6_var_y_th2                   :10,	// 19:10
	reg_l6_pel_trunc                   :2 ,	// 21:20
	reg_var_v_cut                      :2 ,	// 23:22
	reg_var_h_cut                      :2 ,	// 25:24
	reg_var_t7_offset                  :2 ,	// 27:26
	reg_decon_rd_simple_bit            :3 ,	// 30:28
	reg_decon_rd_simple_on             :1 ;	// 31
}PE_O20_REG_DECON_CTRL_34_T;
/*-----------------------------------------------------------------------------
                             0xc9018824L reg_decon_ctrl_35                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_35_T;
/*-----------------------------------------------------------------------------
                             0xc9018828L reg_decon_ctrl_36                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_36_T;
/*-----------------------------------------------------------------------------
                             0xc901882cL reg_decon_ctrl_37                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_decon_rd_simple_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_37_T;
/*-----------------------------------------------------------------------------
                             0xc9018830L reg_decon_ctrl_38                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_min_pel_cb                  :12,	// 11:0
	reg_rd_min_pel_yy                  :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_rd_bit                         :3 ,	// 30:28
	reg_decon_rd_on                    :1 ;	// 31
}PE_O20_REG_DECON_CTRL_38_T;
/*-----------------------------------------------------------------------------
                             0xc9018834L reg_decon_ctrl_39                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_yy                  :12,	// 11:0
	reg_rd_min_pel_cr                  :12;	// 23:12
}PE_O20_REG_DECON_CTRL_39_T;
/*-----------------------------------------------------------------------------
                             0xc9018838L reg_decon_ctrl_40                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_max_pel_cr                  :12,	// 11:0
	reg_rd_max_pel_cb                  :12;	// 23:12
}PE_O20_REG_DECON_CTRL_40_T;
/*-----------------------------------------------------------------------------
                             0xc901883cL reg_decon_ctrl_41                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_41_T;
/*-----------------------------------------------------------------------------
                             0xc9018840L reg_decon_ctrl_42                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_42_T;
/*-----------------------------------------------------------------------------
                             0xc9018844L reg_decon_ctrl_43                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_rd_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_43_T;
/*-----------------------------------------------------------------------------
                             0xc9018848L reg_decon_ctrl_44                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_x3                 :8 ,	// 7:0
	reg_motion_gain_x2                 :8 ,	// 15:8
	reg_motion_gain_x1                 :8 ,	// 23:16
	reg_motion_gain_x0                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_44_T;
/*-----------------------------------------------------------------------------
                             0xc901884cL reg_decon_ctrl_45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_motion_gain_y3                 :8 ,	// 7:0
	reg_motion_gain_y2                 :8 ,	// 15:8
	reg_motion_gain_y1                 :8 ,	// 23:16
	reg_motion_gain_y0                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_45_T;
/*-----------------------------------------------------------------------------
                             0xc9018850L reg_decon_ctrl_46                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_y0                         :12,	// 11:0
	reg_bbd_x0                         :12,	// 23:12
	reserved01                         :4 ,	// reserved
	reg_blur3_sim_en                   :1 ,	// 28
	reg_blur2_sim_en                   :1 ,	// 29
	reg_amf_lut_bit                    :1 ,	// 30
	reg_bbd_en                         :1 ;	// 31
}PE_O20_REG_DECON_CTRL_46_T;
/*-----------------------------------------------------------------------------
                             0xc9018854L reg_decon_ctrl_47                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_bbd_y1                         :12,	// 11:0
	reg_bbd_x1                         :12,	// 23:12
	reserved01                         :2 ,	// reserved
	reg_blur3_sim_ratio                :3 ,	// 28:26
	reg_blur2_sim_ratio                :3 ;	// 31:29
}PE_O20_REG_DECON_CTRL_47_T;
/*-----------------------------------------------------------------------------
                             0xc9018858L reg_decon_ctrl_48                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_blur_sim_x3                :8 ,	// 7:0
	reg_lut_blur_sim_x2                :8 ,	// 15:8
	reg_lut_blur_sim_x1                :8 ,	// 23:16
	reg_lut_blur_sim_x0                :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_48_T;
/*-----------------------------------------------------------------------------
                             0xc901885cL reg_decon_ctrl_49                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_blur_sim_y3                :8 ,	// 7:0
	reg_lut_blur_sim_y2                :8 ,	// 15:8
	reg_lut_blur_sim_y1                :8 ,	// 23:16
	reg_lut_blur_sim_y0                :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_49_T;
/*-----------------------------------------------------------------------------
                             0xc9018860L reg_decon_ctrl_50                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_yy_x3                 :8 ,	// 7:0
	reg_lut_skin_yy_x2                 :8 ,	// 15:8
	reg_lut_skin_yy_x1                 :8 ,	// 23:16
	reg_lut_skin_yy_x0                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_50_T;
/*-----------------------------------------------------------------------------
                             0xc9018864L reg_decon_ctrl_51                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_cb_x3                 :8 ,	// 7:0
	reg_lut_skin_cb_x2                 :8 ,	// 15:8
	reg_lut_skin_cb_x1                 :8 ,	// 23:16
	reg_lut_skin_cb_x0                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_51_T;
/*-----------------------------------------------------------------------------
                             0xc9018868L reg_decon_ctrl_52                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_cr_x3                 :8 ,	// 7:0
	reg_lut_skin_cr_x2                 :8 ,	// 15:8
	reg_lut_skin_cr_x1                 :8 ,	// 23:16
	reg_lut_skin_cr_x0                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_52_T;
/*-----------------------------------------------------------------------------
                             0xc901886cL reg_decon_ctrl_53                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_skin_y3                    :8 ,	// 7:0
	reg_lut_skin_y2                    :8 ,	// 15:8
	reg_lut_skin_y1                    :8 ,	// 23:16
	reg_lut_skin_y0                    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_53_T;
/*-----------------------------------------------------------------------------
                             0xc9018870L reg_decon_ctrl_54                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_face_x3                    :8 ,	// 7:0
	reg_lut_face_x2                    :8 ,	// 15:8
	reg_lut_face_x1                    :8 ,	// 23:16
	reg_lut_face_x0                    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_54_T;
/*-----------------------------------------------------------------------------
                             0xc9018874L reg_decon_ctrl_55                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_lut_face_y3                    :8 ,	// 7:0
	reg_lut_face_y2                    :8 ,	// 15:8
	reg_lut_face_y1                    :8 ,	// 23:16
	reg_lut_face_y0                    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_55_T;
/*-----------------------------------------------------------------------------
                             0xc9018878L reg_decon_ctrl_56                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :19,	// reserved
	reg_face_skin_opt                  :1 ,	// 19
	reg_face_master_gain               :8 ,	// 27:20
	reg_face_shft                      :2 ,	// 29:28
	reg_face_en                        :1 ,	// 30
	reg_skin_en                        :1 ;	// 31
}PE_O20_REG_DECON_CTRL_56_T;
/*-----------------------------------------------------------------------------
                             0xc901887cL reg_decon_ctrl_57                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_dist_h             :4 ,	// 3:0
	reg_l6_var_diff_dist_w             :4 ;	// 7:4
}PE_O20_REG_DECON_CTRL_57_T;
/*-----------------------------------------------------------------------------
                             0xc9018880L reg_decon_ctrl_58                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_cr              :10,	// 9:0
	reg_l6_var_diff_th_cb              :10,	// 19:10
	reg_l6_var_diff_th_yy              :10;	// 29:20
}PE_O20_REG_DECON_CTRL_58_T;
/*-----------------------------------------------------------------------------
                             0xc9018884L reg_decon_ctrl_59                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_yy3             :10,	// 9:0
	reg_l6_var_diff_th_yy2             :10;	// 19:10
}PE_O20_REG_DECON_CTRL_59_T;
/*-----------------------------------------------------------------------------
                             0xc9018888L reg_decon_ctrl_60                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_yy3         :10,	// 9:0
	reg_l6_var_diff_th_min_yy2         :10,	// 19:10
	reg_l6_var_diff_th_min_yy          :10;	// 29:20
}PE_O20_REG_DECON_CTRL_60_T;
/*-----------------------------------------------------------------------------
                             0xc901888cL reg_decon_ctrl_61                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_diff_th_min_cc3         :10,	// 9:0
	reg_l6_var_diff_th_min_cc2         :10,	// 19:10
	reg_l6_var_diff_th_min_cc          :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_l6_var_reshape_en              :1 ;	// 31
}PE_O20_REG_DECON_CTRL_61_T;
/*-----------------------------------------------------------------------------
                             0xc9018890L reg_decon_ctrl_62                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_yy_cond_cb_adj_ratio  :8 ,	// 7:0
	reg_l6_var_v_yy_cond_yy_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_diff_yy_cond_ratio    :8 ,	// 23:16
	reg_l6_var_v_diff_yy_cond_ratio    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_62_T;
/*-----------------------------------------------------------------------------
                             0xc9018894L reg_decon_ctrl_63                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_yy_cond_cr_adj_ratio  :8 ,	// 7:0
	reg_l6_var_h_yy_cond_cb_adj_ratio  :8 ,	// 15:8
	reg_l6_var_h_yy_cond_yy_adj_ratio  :8 ,	// 23:16
	reg_l6_var_v_yy_cond_cr_adj_ratio  :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_63_T;
/*-----------------------------------------------------------------------------
                             0xc9018898L reg_dc_bnr_ctrl_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blur_y_max                 :8 ,	// 7:0
	reg_psp_blur_y_min                 :8 ,	// 15:8
	reg_psp_blur_x_max                 :8 ,	// 23:16
	reg_psp_blur_x_min                 :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_12_T;
/*-----------------------------------------------------------------------------
                             0xc901889cL reg_dc_bnr_ctrl_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_x_th3                :8 ,	// 7:0
	reg_psp_blend_x_th2                :8 ,	// 15:8
	reg_psp_blend_x_th1                :8 ,	// 23:16
	reg_psp_blend_x_th0                :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_13_T;
/*-----------------------------------------------------------------------------
                             0xc90188a0L reg_dc_bnr_ctrl_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_y_th1                :8 ,	// 7:0
	reg_psp_blend_y_th0                :8 ,	// 15:8
	reg_psp_blend_x_th5                :8 ,	// 23:16
	reg_psp_blend_x_th4                :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_14_T;
/*-----------------------------------------------------------------------------
                             0xc90188a4L reg_dc_bnr_ctrl_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_blend_y_th5                :8 ,	// 7:0
	reg_psp_blend_y_th4                :8 ,	// 15:8
	reg_psp_blend_y_th3                :8 ,	// 23:16
	reg_psp_blend_y_th2                :8 ;	// 31:24
}PE_O20_REG_DC_BNR_CTRL_15_T;
/*-----------------------------------------------------------------------------
                             0xc90188a8L reg_decon_ctrl_64                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	reg_l6_var_cc_cond_cr_adj_ratio    :8 ,	// 15:8
	reg_l6_var_cc_cond_cb_adj_ratio    :8 ,	// 23:16
	reg_l6_var_cc_cond_yy_adj_ratio    :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_64_T;
/*-----------------------------------------------------------------------------
                             0xc90188acL reg_decon_ctrl_65                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_v_diff_cut_value        :12,	// 11:0
	reg_l6_var_v_diff_th               :12;	// 23:12
}PE_O20_REG_DECON_CTRL_65_T;
/*-----------------------------------------------------------------------------
                             0xc90188b0L reg_decon_ctrl_66                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_h_diff_cut_value        :12,	// 11:0
	reg_l6_var_h_diff_th               :12;	// 23:12
}PE_O20_REG_DECON_CTRL_66_T;
/*-----------------------------------------------------------------------------
                             0xc90188b4L reg_decon_ctrl_67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_max_rep_value:12,	// 11:0
	reg_l6_var_total_diff_max_th       :12;	// 23:12
}PE_O20_REG_DECON_CTRL_67_T;
/*-----------------------------------------------------------------------------
                             0xc90188b8L reg_decon_ctrl_68                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_l6_var_total_diff_low_rep_value:12,	// 11:0
	reg_l6_var_total_diff_low_th       :12;	// 23:12
}PE_O20_REG_DECON_CTRL_68_T;
/*-----------------------------------------------------------------------------
                             0xc90188bcL reg_decon_ctrl_69                             
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
}PE_O20_REG_DECON_CTRL_69_T;
/*-----------------------------------------------------------------------------
                             0xc90188c0L reg_decon_ctrl_70                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th2                 :10,	// 9:0
	reg_2nd_luma_x_th1                 :10,	// 19:10
	reg_2nd_luma_x_th0                 :10,	// 29:20
	reserved01                         :1 ,	// reserved
	reg_444_mode                       :1 ;	// 31
}PE_O20_REG_DECON_CTRL_70_T;
/*-----------------------------------------------------------------------------
                             0xc90188c4L reg_decon_ctrl_71                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_x_th5                 :10,	// 9:0
	reg_2nd_luma_x_th4                 :10,	// 19:10
	reg_2nd_luma_x_th3                 :10,	// 29:20
	reg_2nd_luma_bit_opt               :2 ;	// 31:30
}PE_O20_REG_DECON_CTRL_71_T;
/*-----------------------------------------------------------------------------
                             0xc90188c8L reg_decon_ctrl_72                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th0                 :10,	// 9:0
	reg_2nd_luma_x_th7                 :10,	// 19:10
	reg_2nd_luma_x_th6                 :10;	// 29:20
}PE_O20_REG_DECON_CTRL_72_T;
/*-----------------------------------------------------------------------------
                             0xc90188ccL reg_decon_ctrl_73                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th3                 :10,	// 9:0
	reg_2nd_luma_y_th2                 :10,	// 19:10
	reg_2nd_luma_y_th1                 :10;	// 29:20
}PE_O20_REG_DECON_CTRL_73_T;
/*-----------------------------------------------------------------------------
                             0xc90188d0L reg_decon_ctrl_74                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_luma_y_th6                 :10,	// 9:0
	reg_2nd_luma_y_th5                 :10,	// 19:10
	reg_2nd_luma_y_th4                 :10;	// 29:20
}PE_O20_REG_DECON_CTRL_74_T;
/*-----------------------------------------------------------------------------
                             0xc90188d4L reg_decon_ctrl_75                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_x_th1                  :10,	// 9:0
	reg_2nd_var_x_th0                  :10,	// 19:10
	reg_2nd_luma_y_th7                 :10;	// 29:20
}PE_O20_REG_DECON_CTRL_75_T;
/*-----------------------------------------------------------------------------
                             0xc90188d8L reg_decon_ctrl_76                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th0                  :10,	// 9:0
	reg_2nd_var_x_th3                  :10,	// 19:10
	reg_2nd_var_x_th2                  :10;	// 29:20
}PE_O20_REG_DECON_CTRL_76_T;
/*-----------------------------------------------------------------------------
                             0xc90188dcL reg_decon_ctrl_77                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_var_y_th3                  :10,	// 9:0
	reg_2nd_var_y_th2                  :10,	// 19:10
	reg_2nd_var_y_th1                  :10;	// 29:20
}PE_O20_REG_DECON_CTRL_77_T;
/*-----------------------------------------------------------------------------
                             0xc90188e0L reg_decon_ctrl_78                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_x_th0                 :8 ,	// 7:0
	reg_2nd_diff_x_th1                 :8 ,	// 15:8
	reg_2nd_diff_x_th2                 :8 ,	// 23:16
	reg_2nd_diff_x_th3                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_78_T;
/*-----------------------------------------------------------------------------
                             0xc90188e4L reg_decon_ctrl_79                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_diff_y_th0                 :8 ,	// 7:0
	reg_2nd_diff_y_th1                 :8 ,	// 15:8
	reg_2nd_diff_y_th2                 :8 ,	// 23:16
	reg_2nd_diff_y_th3                 :8 ;	// 31:24
}PE_O20_REG_DECON_CTRL_79_T;
/*-----------------------------------------------------------------------------
                             0xc90188e8L reg_decon_ctrl_80                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_yy;	// 31:0
}PE_O20_REG_DECON_CTRL_80_T;
/*-----------------------------------------------------------------------------
                             0xc90188ecL reg_decon_ctrl_81                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cb;	// 31:0
}PE_O20_REG_DECON_CTRL_81_T;
/*-----------------------------------------------------------------------------
                             0xc90188f0L reg_decon_ctrl_82                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_2nd_rd_simple_init_cr;	// 31:0
}PE_O20_REG_DECON_CTRL_82_T;
/*-----------------------------------------------------------------------------
                             0xc90188f4L reg_decon_ctrl_83                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_boundary_x_end                 :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_boundary_x_start               :13,	// 28:16
	reserved02                         :1 ,	// reserved
	reg_boundary_side                  :1 ,	// 30
	reg_boundary_en                    :1 ;	// 31
}PE_O20_REG_DECON_CTRL_83_T;


/*-----------------------------------------------------------------------------
                             0xc9019200L psp_ctrl00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_img_wid                        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_img_hei                        :12;	// 27:16
}PE_O20_PSP_CTRL00_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019204L psp_ctrl01                             
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
}PE_O20_PSP_CTRL01_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019208L psp_ctrl02                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vs_inv                         :1 ,	// 0 
	reg_psp_en                         :1 ,	// 1 
	reg_hist_sel                       :2 ,	// 3:2
	reg_repeat_h_num                   :5 ,	// 8:4
	reg_cg_disp_clk                    :1 ,	// 9 
	reg_repeat_v_num                   :5 ,	// 14:10
	reserved                           :1 ,	// 15
	reg_margin_hei                     :8 ,	// 23:16
	reg_margin_wid                     :8 ;	// 31:24
}PE_O20_PSP_CTRL02_O_T;
/*-----------------------------------------------------------------------------
                             0xc901920cL edge_th                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_th                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_w_box_th                       :8 ,	// 23:16
	reg_h_box_th                       :8 ;	// 31:24
}PE_O20_EDGE_TH_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019210L fg_position                             
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
}PE_O20_FG_POSITION_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019214L perspect_lut_x0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_0;	// 31:0
}PE_O20_PERSPECT_LUT_X0_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019218L perspect_lut_x1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_1;	// 31:0
}PE_O20_PERSPECT_LUT_X1_O_T;
/*-----------------------------------------------------------------------------
                             0xc901921cL perspect_lut_x2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_2;	// 31:0
}PE_O20_PERSPECT_LUT_X2_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019220L perspect_lut_x3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_3;	// 31:0
}PE_O20_PERSPECT_LUT_X3_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019224L perspect_lut_y0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_0;	// 31:0
}PE_O20_PERSPECT_LUT_Y0_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019228L perspect_lut_y1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_1;	// 31:0
}PE_O20_PERSPECT_LUT_Y1_O_T;
/*-----------------------------------------------------------------------------
                             0xc901922cL perspect_lut_y2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_2;	// 31:0
}PE_O20_PERSPECT_LUT_Y2_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019230L perspect_lut_y3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_3;	// 31:0
}PE_O20_PERSPECT_LUT_Y3_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019234L prob_map                             
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
}PE_O20_PROB_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019238L ellips_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_master                 :8 ,	// 7:0
	reg_e_mul_a                        :9 ,	// 16:8
	reserved01                         :3 ,	// reserved
	reg_e_mul_b                        :9 ,	// 28:20
	reserved02                         :1 ,	// reserved
	reg_ellipse_disable                :1 ,	// 30
	reg_fg_mul_ellipse_en              :1 ;	// 31
}PE_O20_ELLIPS_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc901923cL prob_diff_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_offset                 :8 ,	// 7:0
	reg_bg_diff_mul                    :10,	// 17:8
	reserved01                         :2 ,	// reserved
	reg_fg_diff_mul                    :10;	// 29:20
}PE_O20_PROB_DIFF_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019240L object_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_p_offset                       :8 ,	// 7:0
	reg_e_offset                       :8 ,	// 15:8
	reg_dbg_map_sel                    :3 ;	// 18:16
}PE_O20_OBJECT_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019244L blur_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_en                        :1 ;	// 0 
}PE_O20_BLUR_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019248L display_debug_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_disp_gain_l0                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_disp_gain_vrtx                 :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_bot_bnd_enable                 :1 ,	// 8 
	reg_left_bnd_disable               :1 ,	// 9 
	reg_top_bnd_disable                :1 ,	// 10
	reserved03                         :1 ,	// reserved
	reg_fifo_detour                    :1 ,	// 12
	reserved04                         :2 ,	// reserved
	reg_pic_end_status                 :1 ,	// 15
	reg_dst_valid_count                :5 ;	// 20:16
}PE_O20_DISPLAY_DEBUG_MAP_O_T;
/*-----------------------------------------------------------------------------
                             0xc901924cL psp_iir                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_iir_alpha                  :6 ,	// 5:0
	reserved01                         :25,	// reserved
	reg_psp_gain_init                  :1 ;	// 31
}PE_O20_PSP_IIR_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019250L psp_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	psp_gain                           :1 ,	// 0 
	psp_gain_dbg                       :1 ;	// 1 
}PE_O20_PSP_GAIN_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019254L psp_dbg_mon00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h1_pos                             :7 ,	// 6:0
	h2_pos                             :7 ,	// 13:7
	w1_pos                             :7 ,	// 20:14
	w2_pos                             :7 ,	// 27:21
	r_edge_total_lsb                   :4 ;	// 31:28
}PE_O20_PSP_DBG_MON00_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019258L psp_dbg_mon01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_max_flat_length_h              :7 ,	// 6:0
	out_max_flat_length_w              :7 ,	// 13:7
	r_edge_total_msb                   :18;	// 31:14
}PE_O20_PSP_DBG_MON01_O_T;
/*-----------------------------------------------------------------------------
                             0xc901925cL vrtx_cpc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vrtx_gain_tl_i                 :8 ,	// 7:0
	reg_vrtx_gain_tr_i                 :8 ,	// 15:8
	reg_vrtx_gain_bl_i                 :8 ,	// 23:16
	reg_vrtx_gain_br_i                 :8 ;	// 31:24
}PE_O20_VRTX_CPC_CTRL_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019260L blur_hcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef1                             :10;	// 25:16
}PE_O20_BLUR_HCOEF01_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019264L blur_hcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef3                             :10;	// 25:16
}PE_O20_BLUR_HCOEF23_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019268L blur_hcoef45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef4                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef5                             :10;	// 25:16
}PE_O20_BLUR_HCOEF45_O_T;
/*-----------------------------------------------------------------------------
                             0xc901926cL blur_hcoef67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef6                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef7                             :10;	// 25:16
}PE_O20_BLUR_HCOEF67_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019270L blur_hcoef8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef8                             :10;	// 9:0
}PE_O20_BLUR_HCOEF8_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019274L blur_vcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef1                             :10;	// 25:16
}PE_O20_BLUR_VCOEF01_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019278L blur_vcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef3                             :10;	// 25:16
}PE_O20_BLUR_VCOEF23_O_T;
/*-----------------------------------------------------------------------------
                             0xc901927cL blur_vcoef4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef4                             :10;	// 9:0
}PE_O20_BLUR_VCOEF4_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019280L histogram_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_0_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019284L histogram_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_1_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019288L histogram_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_2_O_T;
/*-----------------------------------------------------------------------------
                             0xc901928cL histogram_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_3_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019290L histogram_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_4_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019294L histogram_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_5_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019298L histogram_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_6_O_T;
/*-----------------------------------------------------------------------------
                             0xc901929cL histogram_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_7_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192a0L histogram_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_8_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192a4L histogram_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_9_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192a8L histogram_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_10_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192acL histogram_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_11_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192b0L histogram_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_12_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192b4L histogram_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_13_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192b8L histogram_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_14_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192bcL histogram_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_15_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192c0L histogram_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_16_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192c4L histogram_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_17_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192c8L histogram_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_18_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192ccL histogram_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_19_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192d0L histogram_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_20_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192d4L histogram_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_21_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192d8L histogram_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_22_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192dcL histogram_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_23_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192e0L histogram_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_24_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192e4L histogram_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_25_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192e8L histogram_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_26_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192ecL histogram_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_27_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192f0L histogram_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_28_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192f4L histogram_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_29_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192f8L histogram_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_30_O_T;
/*-----------------------------------------------------------------------------
                             0xc90192fcL histogram_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_31_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019300L l5_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :8 ,	// 7:0
	x0_point                           :8 ,	// 15:8
	y1_point                           :8 ,	// 23:16
	x1_point                           :8 ;	// 31:24
}PE_O20_L5_GAIN_LUT1_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019304L l5_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :8 ,	// 7:0
	x2_point                           :8 ,	// 15:8
	y3_point                           :8 ,	// 23:16
	x3_point                           :8 ;	// 31:24
}PE_O20_L5_GAIN_LUT2_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019308L l0_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :8 ,	// 7:0
	x0_point                           :8 ,	// 15:8
	y1_point                           :8 ,	// 23:16
	x1_point                           :8 ;	// 31:24
}PE_O20_L0_GAIN_LUT1_O_T;
/*-----------------------------------------------------------------------------
                             0xc901930cL l0_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :8 ,	// 7:0
	x2_point                           :8 ,	// 15:8
	y3_point                           :8 ,	// 23:16
	x3_point                           :8 ;	// 31:24
}PE_O20_L0_GAIN_LUT2_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019310L edge_win_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	h_end                              :12;	// 27:16
}PE_O20_EDGE_WIN_H_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019314L edge_win_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	v_end                              :12;	// 27:16
}PE_O20_EDGE_WIN_V_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019318L edge0_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_fg                           :23;	// 22:0
}PE_O20_EDGE0_FG_O_T;
/*-----------------------------------------------------------------------------
                             0xc901931cL edge0_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_bg                           :23;	// 22:0
}PE_O20_EDGE0_BG_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019320L edge1_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_fg                           :23;	// 22:0
}PE_O20_EDGE1_FG_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019324L edge1_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_bg                           :23;	// 22:0
}PE_O20_EDGE1_BG_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019328L psp_iir1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cliping_en                         :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	th_lower                           :6 ,	// 9:4
	reserved02                         :2 ,	// reserved
	th_upper                           :6 ,	// 17:12
	reserved03                         :2 ,	// reserved
	prc_step                           :6 ;	// 25:20
}PE_O20_PSP_IIR1_O_T;
/*-----------------------------------------------------------------------------
                             0xc901932cL bg_measure_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_measure_en                      :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	h_num                              :4 ,	// 7:4
	v_num                              :4 ,	// 11:8
	obj_th0                            :6 ,	// 17:12
	reserved02                         :2 ,	// reserved
	obj_th1                            :8 ;	// 27:20
}PE_O20_BG_MEASURE_CTRL_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019330L bg_measure_read0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit0                         :16,	// 15:0
	line_unit1                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ0_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019334L bg_measure_read1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit2                         :16,	// 15:0
	line_unit3                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ1_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019338L bg_measure_read2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit4                         :16,	// 15:0
	line_unit5                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ2_O_T;
/*-----------------------------------------------------------------------------
                             0xc901933cL bg_measure_read3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit6                         :16,	// 15:0
	line_unit7                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ3_O_T;
/*-----------------------------------------------------------------------------
                             0xc9019340L bg_measure_read4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit8                         :16;	// 15:0
}PE_O20_BG_MEASURE_READ4_O_T;









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
}PE_O20_CTRL_M0_Y_LEVEL_CTRL_T;


/*-----------------------------------------------------------------------------
                             0xc9019400L psp_ctrl00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_img_wid                        :12,	// 11:0
	reserved01                         :4 ,	// reserved
	reg_img_hei                        :12;	// 27:16
}PE_O20_PSP_CTRL00_T;
/*-----------------------------------------------------------------------------
                             0xc9019404L psp_ctrl01                             
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
}PE_O20_PSP_CTRL01_T;
/*-----------------------------------------------------------------------------
                             0xc9019408L psp_ctrl02                             
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
	reserved                           :1 ,	// 15
	reg_margin_hei                     :8 ,	// 23:16
	reg_margin_wid                     :8 ;	// 31:24
}PE_O20_PSP_CTRL02_T;
/*-----------------------------------------------------------------------------
                             0xc901940cL edge_th                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_edge_th                        :13,	// 12:0
	reserved01                         :3 ,	// reserved
	reg_w_box_th                       :8 ,	// 23:16
	reg_h_box_th                       :8 ;	// 31:24
}PE_O20_EDGE_TH_T;
/*-----------------------------------------------------------------------------
                             0xc9019410L fg_position                             
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
}PE_O20_FG_POSITION_T;

/*-----------------------------------------------------------------------------
                             0xc9019414L perspect_lut_x0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_0;	// 31:0
}PE_O20_PERSPECT_LUT_X0_T;
/*-----------------------------------------------------------------------------
                             0xc9019418L perspect_lut_x1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_1;	// 31:0
}PE_O20_PERSPECT_LUT_X1_T;
/*-----------------------------------------------------------------------------
                             0xc901941cL perspect_lut_x2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_2;	// 31:0
}PE_O20_PERSPECT_LUT_X2_T;
/*-----------------------------------------------------------------------------
                             0xc9019420L perspect_lut_x3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_x_3;	// 31:0
}PE_O20_PERSPECT_LUT_X3_T;
/*-----------------------------------------------------------------------------
                             0xc9019424L perspect_lut_y0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_0;	// 31:0
}PE_O20_PERSPECT_LUT_Y0_T;
/*-----------------------------------------------------------------------------
                             0xc9019428L perspect_lut_y1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_1;	// 31:0
}PE_O20_PERSPECT_LUT_Y1_T;
/*-----------------------------------------------------------------------------
                             0xc901942cL perspect_lut_y2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_2;	// 31:0
}PE_O20_PERSPECT_LUT_Y2_T;
/*-----------------------------------------------------------------------------
                             0xc9019430L perspect_lut_y3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_perspect_lut_y_3;	// 31:0
}PE_O20_PERSPECT_LUT_Y3_T;

/*-----------------------------------------------------------------------------
                             0xc9019434L prob_map                             
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
}PE_O20_PROB_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9019438L ellips_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_master                 :8 ,	// 7:0
	reg_e_mul_a                        :9 ,	// 16:8
	reserved01                         :3 ,	// reserved
	reg_e_mul_b                        :9 ,	// 28:20
	reserved02                         :1 ,	// reserved
	reg_ellipse_disable                :1 ,	// 30
	reg_fg_mul_ellipse_en              :1 ;	// 31
}PE_O20_ELLIPS_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc901943cL prob_diff_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_ellipse_offset                 :8 ,	// 7:0
	reg_bg_diff_mul                    :10,	// 17:8
	reserved01                         :2 ,	// reserved
	reg_fg_diff_mul                    :10;	// 29:20
}PE_O20_PROB_DIFF_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9019440L object_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_p_offset                       :8 ,	// 7:0
	reg_e_offset                       :8 ,	// 15:8
	reg_dbg_map_sel                    :3 ;	// 18:16
}PE_O20_OBJECT_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9019444L blur_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_blur_en                        :1 ;	// 0 
}PE_O20_BLUR_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc9019448L display_debug_map                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_disp_gain_l0                   :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	reg_disp_gain_vrtx                 :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	reg_bot_bnd_enable                 :1 ,	// 8 
	reg_left_bnd_disable               :1 ,	// 9 
	reg_top_bnd_disable                :1 ,	// 10
	reserved03                         :1 ,	// reserved
	reg_fifo_detour                    :1 ,	// 12
	reserved04                         :2 ,	// reserved
	reg_pic_end_status                 :1 ,	// 15
	reg_dst_valid_count                :5 ;	// 20:16
}PE_O20_DISPLAY_DEBUG_MAP_T;
/*-----------------------------------------------------------------------------
                             0xc901944cL psp_iir                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_psp_iir_alpha                  :6 ,	// 5:0
	reserved01                         :25,	// reserved
	reg_psp_gain_init                  :1 ;	// 31
}PE_O20_PSP_IIR_T;
/*-----------------------------------------------------------------------------
                             0xc9019450L psp_gain                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	psp_gain                           :1 ,	// 0 
	psp_gain_dbg                       :1 ;	// 1 
}PE_O20_PSP_GAIN_T;
/*-----------------------------------------------------------------------------
                             0xc9019454L psp_dbg_mon00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h1_pos                             :7 ,	// 6:0
	h2_pos                             :7 ,	// 13:7
	w1_pos                             :7 ,	// 20:14
	w2_pos                             :7 ,	// 27:21
	r_edge_total_lsb                   :4 ;	// 31:28
}PE_O20_PSP_DBG_MON00_T;
/*-----------------------------------------------------------------------------
                             0xc9019458L psp_dbg_mon01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	out_max_flat_length_h              :7 ,	// 6:0
	out_max_flat_length_w              :7 ,	// 13:7
	r_edge_total_msb                   :18;	// 31:14
}PE_O20_PSP_DBG_MON01_T;
/*-----------------------------------------------------------------------------
                             0xc901945cL vrtx_cpc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_vrtx_gain_tl_i                 :8 ,	// 7:0
	reg_vrtx_gain_tr_i                 :8 ,	// 15:8
	reg_vrtx_gain_bl_i                 :8 ,	// 23:16
	reg_vrtx_gain_br_i                 :8 ;	// 31:24
}PE_O20_VRTX_CPC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9019460L blur_hcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef1                             :10;	// 25:16
}PE_O20_BLUR_HCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc9019464L blur_hcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef3                             :10;	// 25:16
}PE_O20_BLUR_HCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc9019468L blur_hcoef45                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef4                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef5                             :10;	// 25:16
}PE_O20_BLUR_HCOEF45_T;
/*-----------------------------------------------------------------------------
                             0xc901946cL blur_hcoef67                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef6                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	hcoef7                             :10;	// 25:16
}PE_O20_BLUR_HCOEF67_T;
/*-----------------------------------------------------------------------------
                             0xc9019470L blur_hcoef8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hcoef8                             :10;	// 9:0
}PE_O20_BLUR_HCOEF8_T;
/*-----------------------------------------------------------------------------
                             0xc9019474L blur_vcoef01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef0                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef1                             :10;	// 25:16
}PE_O20_BLUR_VCOEF01_T;
/*-----------------------------------------------------------------------------
                             0xc9019478L blur_vcoef23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef2                             :10,	// 9:0
	reserved01                         :6 ,	// reserved
	vcoef3                             :10;	// 25:16
}PE_O20_BLUR_VCOEF23_T;
/*-----------------------------------------------------------------------------
                             0xc901947cL blur_vcoef4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcoef4                             :10;	// 9:0
}PE_O20_BLUR_VCOEF4_T;
/*-----------------------------------------------------------------------------
                             0xc9019480L histogram_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_0_T;
/*-----------------------------------------------------------------------------
                             0xc9019484L histogram_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_1_T;
/*-----------------------------------------------------------------------------
                             0xc9019488L histogram_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_2_T;
/*-----------------------------------------------------------------------------
                             0xc901948cL histogram_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_3_T;
/*-----------------------------------------------------------------------------
                             0xc9019490L histogram_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_4_T;
/*-----------------------------------------------------------------------------
                             0xc9019494L histogram_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_5_T;
/*-----------------------------------------------------------------------------
                             0xc9019498L histogram_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_6_T;
/*-----------------------------------------------------------------------------
                             0xc901949cL histogram_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_7_T;
/*-----------------------------------------------------------------------------
                             0xc90194a0L histogram_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_8_T;
/*-----------------------------------------------------------------------------
                             0xc90194a4L histogram_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_9_T;
/*-----------------------------------------------------------------------------
                             0xc90194a8L histogram_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_10_T;
/*-----------------------------------------------------------------------------
                             0xc90194acL histogram_11                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_11_T;
/*-----------------------------------------------------------------------------
                             0xc90194b0L histogram_12                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_12_T;
/*-----------------------------------------------------------------------------
                             0xc90194b4L histogram_13                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_13_T;
/*-----------------------------------------------------------------------------
                             0xc90194b8L histogram_14                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_14_T;
/*-----------------------------------------------------------------------------
                             0xc90194bcL histogram_15                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_15_T;
/*-----------------------------------------------------------------------------
                             0xc90194c0L histogram_16                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_16_T;
/*-----------------------------------------------------------------------------
                             0xc90194c4L histogram_17                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_17_T;
/*-----------------------------------------------------------------------------
                             0xc90194c8L histogram_18                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_18_T;
/*-----------------------------------------------------------------------------
                             0xc90194ccL histogram_19                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_19_T;
/*-----------------------------------------------------------------------------
                             0xc90194d0L histogram_20                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_20_T;
/*-----------------------------------------------------------------------------
                             0xc90194d4L histogram_21                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_21_T;
/*-----------------------------------------------------------------------------
                             0xc90194d8L histogram_22                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_22_T;
/*-----------------------------------------------------------------------------
                             0xc90194dcL histogram_23                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_23_T;
/*-----------------------------------------------------------------------------
                             0xc90194e0L histogram_24                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_24_T;
/*-----------------------------------------------------------------------------
                             0xc90194e4L histogram_25                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_25_T;
/*-----------------------------------------------------------------------------
                             0xc90194e8L histogram_26                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_26_T;
/*-----------------------------------------------------------------------------
                             0xc90194ecL histogram_27                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_27_T;
/*-----------------------------------------------------------------------------
                             0xc90194f0L histogram_28                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_28_T;
/*-----------------------------------------------------------------------------
                             0xc90194f4L histogram_29                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_29_T;
/*-----------------------------------------------------------------------------
                             0xc90194f8L histogram_30                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_30_T;
/*-----------------------------------------------------------------------------
                             0xc90194fcL histogram_31                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	data_bg                            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	data_fg                            :13;	// 28:16
}PE_O20_HISTOGRAM_31_T;
/*-----------------------------------------------------------------------------
                             0xc9019500L l5_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :8 ,	// 7:0
	x0_point                           :8 ,	// 15:8
	y1_point                           :8 ,	// 23:16
	x1_point                           :8 ;	// 31:24
}PE_O20_L5_GAIN_LUT1_T;
/*-----------------------------------------------------------------------------
                             0xc9019504L l5_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :8 ,	// 7:0
	x2_point                           :8 ,	// 15:8
	y3_point                           :8 ,	// 23:16
	x3_point                           :8 ;	// 31:24
}PE_O20_L5_GAIN_LUT2_T;
/*-----------------------------------------------------------------------------
                             0xc9019508L l0_gain_lut1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_point                           :8 ,	// 7:0
	x0_point                           :8 ,	// 15:8
	y1_point                           :8 ,	// 23:16
	x1_point                           :8 ;	// 31:24
}PE_O20_L0_GAIN_LUT1_T;
/*-----------------------------------------------------------------------------
                             0xc901950cL l0_gain_lut2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y2_point                           :8 ,	// 7:0
	x2_point                           :8 ,	// 15:8
	y3_point                           :8 ,	// 23:16
	x3_point                           :8 ;	// 31:24
}PE_O20_L0_GAIN_LUT2_T;
/*-----------------------------------------------------------------------------
                             0xc9019510L edge_win_h                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	h_end                              :12;	// 27:16
}PE_O20_EDGE_WIN_H_T;
/*-----------------------------------------------------------------------------
                             0xc9019514L edge_win_v                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	v_str                              :12,	// 11:0
	reserved01                         :4 ,	// reserved
	v_end                              :12;	// 27:16
}PE_O20_EDGE_WIN_V_T;
/*-----------------------------------------------------------------------------
                             0xc9019518L edge0_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_fg                           :23;	// 22:0
}PE_O20_EDGE0_FG_T;
/*-----------------------------------------------------------------------------
                             0xc901951cL edge0_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge0_bg                           :23;	// 22:0
}PE_O20_EDGE0_BG_T;
/*-----------------------------------------------------------------------------
                             0xc9019520L edge1_fg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_fg                           :23;	// 22:0
}PE_O20_EDGE1_FG_T;
/*-----------------------------------------------------------------------------
                             0xc9019524L edge1_bg                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	edge1_bg                           :23;	// 22:0
}PE_O20_EDGE1_BG_T;
/*-----------------------------------------------------------------------------
                             0xc9019528L psp_iir1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cliping_en                         :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	th_lower                           :6 ,	// 9:4
	reserved02                         :2 ,	// reserved
	th_upper                           :6 ,	// 17:12
	reserved03                         :2 ,	// reserved
	prc_step                           :6 ;	// 25:20
}PE_O20_PSP_IIR1_T;
/*-----------------------------------------------------------------------------
                             0xc901952cL bg_measure_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	bg_measure_en                      :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	h_num                              :4 ,	// 7:4
	v_num                              :4 ,	// 11:8
	obj_th0                            :6 ,	// 17:12
	reserved02                         :2 ,	// reserved
	obj_th1                            :8 ;	// 27:20
}PE_O20_BG_MEASURE_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc9019530L bg_measure_read0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit0                         :16,	// 15:0
	line_unit1                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ0_T;
/*-----------------------------------------------------------------------------
                             0xc9019534L bg_measure_read1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit2                         :16,	// 15:0
	line_unit3                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ1_T;
/*-----------------------------------------------------------------------------
                             0xc9019538L bg_measure_read2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit4                         :16,	// 15:0
	line_unit5                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ2_T;
/*-----------------------------------------------------------------------------
                             0xc901953cL bg_measure_read3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit6                         :16,	// 15:0
	line_unit7                         :16;	// 31:16
}PE_O20_BG_MEASURE_READ3_T;
/*-----------------------------------------------------------------------------
                             0xc9019540L bg_measure_read4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_unit8                         :16;	// 15:0
}PE_O20_BG_MEASURE_READ4_T;
/*-----------------------------------------------------------------------------
                             0xc9019544L face0_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face0_en                           :1 ;	// 31
}PE_O20_FACE0_SET_T;
/*-----------------------------------------------------------------------------
                             0xc9019548L face1_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face0_en                           :1 ;	// 31
}PE_O20_FACE1_SET_T;
/*-----------------------------------------------------------------------------
                             0xc901954cL face2_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face0_en                           :1 ;	// 31
}PE_O20_FACE2_SET_T;
/*-----------------------------------------------------------------------------
                             0xc9019550L face3_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_w2_pos                         :7 ,	// 6:0
	reserved01                         :1 ,	// reserved
	reg_w1_pos                         :7 ,	// 14:8
	reserved02                         :1 ,	// reserved
	reg_h2_pos                         :7 ,	// 22:16
	reserved03                         :1 ,	// reserved
	reg_h1_pos                         :7 ,	// 30:24
	face0_en                           :1 ;	// 31
}PE_O20_FACE3_SET_T;
/*-----------------------------------------------------------------------------
                             0xc9019554L ellips0_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_ELLIPS0_SET_T;
/*-----------------------------------------------------------------------------
                             0xc9019558L ellips1_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_ELLIPS1_SET_T;
/*-----------------------------------------------------------------------------
                             0xc901955cL ellips2_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_ELLIPS2_SET_T;
/*-----------------------------------------------------------------------------
                             0xc9019560L ellips3_set                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reg_e_mul_a                        :9 ,	// 8:0
	reserved01                         :7 ,	// reserved
	reg_e_mul_b                        :9 ;	// 24:16
}PE_O20_ELLIPS3_SET_T;



typedef union {
	UINT32 udata32;
	struct {						//0xC900EC00 copy from MNR_CTRL_0
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
}PE_O20_ND0_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EC04 copy from MNR_CTRL_3
	UINT32 reg_blur_sel                     :1;	//0 //
	UINT32 reg_pattern_en                   :1;	//1 //
	UINT32 resvd                            :6;
	UINT32 reg_pattern_th                   :8;	//15:8	//
	UINT32 reg_equal_th                     :8;	//23:16	//
	UINT32 reg_mmd_scale                    :8;	//31:24	//
	};
}PE_O20_ND0_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EC08 copy from REG_MNR_CTRL_11
	UINT32 reg_i_sel_mmd_x3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_x2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_x1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_x0                 :8;	//31:24	//
	};
}PE_O20_ND0_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900EC0C copy from REG_MNR_CTRL_12
	UINT32 reg_i_sel_mmd_y3                 :8;	//7:0	//
	UINT32 reg_i_sel_mmd_y2                 :8;	//15:8	//
	UINT32 reg_i_sel_mmd_y1                 :8;	//23:16	//
	UINT32 reg_i_sel_mmd_y0                 :8;	//31:24	//
	};
}PE_O20_ND0_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O20_ND0_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xC900EC00
	PE_O20_ND0_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xC900EC04
	PE_O20_ND0_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xC900EC08
	PE_O20_ND0_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xC900EC0C
}PE_ND_ND0_VERI_REG_O20_T;


typedef struct
{ 
	PE_O20_PE0_ND_LOAD_T                              pe0_load;	//0x0000
	PE_O20_PE0_ND_INTR_T                              pe0_intr;	//0x0004
	PE_O20_PE0_ND_STATUS0_T                           pe0_status0;	//0x0008
	PE_O20_PE0_ND_STATUS1_T                           pe0_status1;	//0x000C
	PE_O20_PE0_ND_OPMODE_T                            pe0_opmode;	//0x0010
	PE_O20_PE0_SRC_SIZE_T                             pe0_src_size;	//0x0014
	PE_O20_PE0_FIELD_T                                pe0_field;	//0x0018
	PE_O20_PE0_DEBUG_LEND_CTRL_T                      pe0_debug_lend_ctrl;	//0x001C
	PE_O20_PE0_ND_IN_OFFSET_T                         pe0_in_offset;	//0x0020
	PE_O20_PE0_ND_IN_SIZE_T                           pe0_in_size;	//0x0024
	PE_O20_FBC_CTRL0_T                                fbc_ctrl0;	//0x0028
	PE_O20_FBC_CTRL1_T                                fbc_ctrl1;	//0x002C
	PE_O20_PE0_MEM_REQ_T                              pe0_mem_req;	//0x0030
	PE_O20_PE0_DEBUG_LREQ_DLY_T                       pe0_debug_lreq_dly;	//0x0034
	PE_O20_TNRW_IN_OFFSET_T                           tnrw_in_offset;	//0x0038
	PE_O20_TNRW_OUT_SIZE_T                            tnrw_out_size;	//0x003C
	PE_O20_TNR_CTRL_00_T                              tnr_ctrl_00;	//0x0040
	PE_O20_TNR_CTRL_01_T                              tnr_ctrl_01;	//0x0044
	PE_O20_TNR_CTRL_02_T                              tnr_ctrl_02;	//0x0048
	PE_O20_TNR_CTRL_03_T                              tnr_ctrl_03;	//0x004C
	PE_O20_TNR_CTRL_04_T                              tnr_ctrl_04;	//0x0050
	PE_O20_TNR_CTRL_05_T                              tnr_ctrl_05;	//0x0054
	PE_O20_TNR_CTRL_06_T                              tnr_ctrl_06;	//0x0058
	PE_O20_TNR_CTRL_07_T                              tnr_ctrl_07;	//0x005C
	PE_O20_TNR_CTRL_08_T                              tnr_ctrl_08;	//0x0060
	PE_O20_TNR_CTRL_09_T                              tnr_ctrl_09;	//0x0064
	PE_O20_TNR_CTRL_10_T                              tnr_ctrl_10;	//0x0068
	PE_O20_TNR_CTRL_11_T                              tnr_ctrl_11;	//0x006C
	PE_O20_TNR_CTRL_12_T                              tnr_ctrl_12;	//0x0070
	PE_O20_TNR_CTRL_13_T                              tnr_ctrl_13;	//0x0074
	PE_O20_TNR_CTRL_14_T                              tnr_ctrl_14;	//0x0078
	PE_O20_TNR_CTRL_15_T                              tnr_ctrl_15;	//0x007C
	PE_O20_TNR_CTRL_16_T                              tnr_ctrl_16;	//0x0080
	PE_O20_TNR_CTRL_17_T                              tnr_ctrl_17;	//0x0084
	PE_O20_TNR_CTRL_18_T                              tnr_ctrl_18;	//0x0088
	PE_O20_TNR_CTRL_19_T                              tnr_ctrl_19;	//0x008C
	PE_O20_TNR_CTRL_20_T                              tnr_ctrl_20;	//0x0090
	PE_O20_TNR_CTRL_21_T                              tnr_ctrl_21;	//0x0094
	PE_O20_TNR_CTRL_22_T                              tnr_ctrl_22;	//0x0098
	PE_O20_TNR_CTRL_23_T                              tnr_ctrl_23;	//0x009C
	PE_O20_TNR_CTRL_24_T                              tnr_ctrl_24;	//0x00A0
	PE_O20_TNR_CTRL_25_T                              tnr_ctrl_25;	//0x00A4
	PE_O20_TNR_CTRL_26_T                              tnr_ctrl_26;	//0x00A8
	PE_O20_TNR_CTRL_27_T                              tnr_ctrl_27;	//0x00AC
	PE_O20_TNR_CTRL_28_T                              tnr_ctrl_28;	//0x00B0
	PE_O20_TNR_CTRL_29_T                              tnr_ctrl_29;	//0x00B4
	PE_O20_TNR_CTRL_30_T                              tnr_ctrl_30;	//0x00B8
	PE_O20_TNR_CTRL_31_T                              tnr_ctrl_31;	//0x00BC
	PE_O20_TNR_STATUS_00_T                            tnr_status_00;	//0x00C0
	PE_O20_TNR_STATUS_01_T                            tnr_status_01;	//0x00C4
	PE_O20_TNR_STATUS_02_T                            tnr_status_02;	//0x00C8
	PE_O20_TNR_STATUS_03_T                            tnr_status_03;	//0x00CC
	PE_O20_TNR_MAIN_LUT_00_T                          tnr_main_lut_00;	//0x00D0
	PE_O20_TNR_MAIN_LUT_01_T                          tnr_main_lut_01;	//0x00D4
	UINT32                                            reserved00;	//0x00D8-0x00D8
	PE_O20_TNR_STATUS_04_T                            tnr_status_04;	//0x00DC
	PE_O20_TNR_CTRL_32_T                              tnr_ctrl_32;	//0x00E0
	PE_O20_TNR_CTRL_33_T                              tnr_ctrl_33;	//0x00E4
	PE_O20_TNR_CTRL_34_T                              tnr_ctrl_34;	//0x00E8
	PE_O20_TNR_CTRL_35_T                              tnr_ctrl_35;	//0x00EC
	PE_O20_TNR_CTRL_36_T                              tnr_ctrl_36;	//0x00F0
	PE_O20_TNR_CTRL_37_T                              tnr_ctrl_37;	//0x00F4
	PE_O20_TNR_CTRL_38_T                              tnr_ctrl_38;	//0x00F8
	PE_O20_TNR_CTRL_39_T                              tnr_ctrl_39;	//0x00FC
	PE_O20_IPC_CTRL_00_T                              ipc_ctrl_00;	//0x0100
	PE_O20_IPC_CTRL_01_T                              ipc_ctrl_01;	//0x0104
	PE_O20_IPC_CTRL_02_T                              ipc_ctrl_02;	//0x0108
	PE_O20_IPC_CTRL_03_T                              ipc_ctrl_03;	//0x010C
	PE_O20_IPC_CTRL_04_T                              ipc_ctrl_04;	//0x0110
	PE_O20_IPC_CTRL_05_T                              ipc_ctrl_05;	//0x0114
	PE_O20_IPC_CTRL_06_T                              ipc_ctrl_06;	//0x0118
	PE_O20_IPC_CTRL_07_T                              ipc_ctrl_07;	//0x011C
	PE_O20_IPC_CTRL_08_T                              ipc_ctrl_08;	//0x0120
	PE_O20_IPC_CTRL_09_T                              ipc_ctrl_09;	//0x0124
	PE_O20_IPC_CTRL_10_T                              ipc_ctrl_10;	//0x0128
	PE_O20_IPC_CTRL_11_T                              ipc_ctrl_11;	//0x012C
	PE_O20_IPC_CTRL_12_T                              ipc_ctrl_12;	//0x0130
	PE_O20_IPC_CTRL_13_T                              ipc_ctrl_13;	//0x0134
	PE_O20_IPC_CTRL_14_T                              ipc_ctrl_14;	//0x0138
	PE_O20_IPC_CTRL_15_T                              ipc_ctrl_15;	//0x013C
	PE_O20_IPC_CTRL_16_T                              ipc_ctrl_16;	//0x0140
	PE_O20_IPC_CTRL_17_T                              ipc_ctrl_17;	//0x0144
	PE_O20_IPC_CTRL_18_T                              ipc_ctrl_18;	//0x0148
	PE_O20_IPC_CTRL_19_T                              ipc_ctrl_19;	//0x014C
	PE_O20_IPC_STATUS_00_T                            ipc_status_00;	//0x0150
	PE_O20_IPC_STATUS_01_T                            ipc_status_01;	//0x0154
	PE_O20_IPC_STATUS_02_T                            ipc_status_02;	//0x0158
	PE_O20_IPC_STATUS_03_T                            ipc_status_03;	//0x015C
	PE_O20_CLC_CTRL_00_T                              clc_ctrl_00;	//0x0160
	PE_O20_CLC_CTRL_01_T                              clc_ctrl_01;	//0x0164
	PE_O20_CLC_CTRL_02_T                              clc_ctrl_02;	//0x0168
	PE_O20_CLC_CTRL_03_T                              clc_ctrl_03;	//0x016C
	PE_O20_CLC_CTRL_04_T                              clc_ctrl_04;	//0x0170
	PE_O20_CLC_CTRL_05_T                              clc_ctrl_05;	//0x0174
	PE_O20_CLC_CTRL_06_T                              clc_ctrl_06;	//0x0178
	PE_O20_CLC_STAT_00_T                              clc_stat_00;	//0x017C
	PE_O20_IPC_CTRL_34_T                              ipc_ctrl_34;	//0x0180
	PE_O20_IPC_CTRL_35_T                              ipc_ctrl_35;	//0x0184
	PE_O20_IPC_CTRL_36_T                              ipc_ctrl_36;	//0x0188
	PE_O20_IPC_CTRL_37_T                              ipc_ctrl_37;	//0x018C
	PE_O20_IPC_CTRL_38_T                              ipc_ctrl_38;	//0x0190
	PE_O20_IPC_CTRL_39_T                              ipc_ctrl_39;	//0x0194
	PE_O20_IPC_CTRL_40_T                              ipc_ctrl_40;	//0x0198
	PE_O20_IPC_CTRL_41_T                              ipc_ctrl_41;	//0x019C
	PE_O20_IPC_CTRL_42_T                              ipc_ctrl_42;	//0x01A0
	PE_O20_IPC_CTRL_43_T                              ipc_ctrl_43;	//0x01A4
	PE_O20_IPC_CTRL_44_T                              ipc_ctrl_44;	//0x01A8
	PE_O20_IPC_CTRL_45_T                              ipc_ctrl_45;	//0x01AC
	PE_O20_IPC_CTRL_46_T                              ipc_ctrl_46;	//0x01B0
	PE_O20_IPC_CTRL_47_T                              ipc_ctrl_47;	//0x01B4
	PE_O20_IPC_CTRL_48_T                              ipc_ctrl_48;	//0x01B8
	PE_O20_IPC_CTRL_49_T                              ipc_ctrl_49;	//0x01BC
	PE_O20_IPC_CTRL_50_T                              ipc_ctrl_50;	//0x01C0
	PE_O20_IPC_CTRL_51_T                              ipc_ctrl_51;	//0x01C4
	PE_O20_IPC_CTRL_52_T                              ipc_ctrl_52;	//0x01C8
	PE_O20_IPC_CTRL_53_T                              ipc_ctrl_53;	//0x01CC
	PE_O20_IPC_CTRL_54_T                              ipc_ctrl_54;	//0x01D0
	PE_O20_IPC_CTRL_55_T                              ipc_ctrl_55;	//0x01D4
	UINT32                                            reserved01[2];	//0x01D8-0x01DC
	PE_O20_MMD_CTRL_T                                 mmd_ctrl;	//0x01E0
	UINT32                                            reserved02[3];	//0x01E4-0x01EC
	PE_O20_IPC_CTRL_20_T                              ipc_ctrl_20;	//0x01F0
	PE_O20_IPC_CTRL_21_T                              ipc_ctrl_21;	//0x01F4
	PE_O20_IPC_CTRL_22_T                              ipc_ctrl_22;	//0x01F8
	PE_O20_IPC_CTRL_23_T                              ipc_ctrl_23;	//0x01FC
	PE_O20_IPC_CTRL_24_T                              ipc_ctrl_24;	//0x0200
	PE_O20_IPC_CTRL_25_T                              ipc_ctrl_25;	//0x0204
	PE_O20_IPC_CTRL_26_T                              ipc_ctrl_26;	//0x0208
	PE_O20_IPC_CTRL_27_T                              ipc_ctrl_27;	//0x020C
	PE_O20_IPC_CTRL_28_T                              ipc_ctrl_28;	//0x0210
	PE_O20_IPC_CTRL_29_T                              ipc_ctrl_29;	//0x0214
	PE_O20_IPC_CTRL_30_T                              ipc_ctrl_30;	//0x0218
	PE_O20_IPC_CTRL_31_T                              ipc_ctrl_31;	//0x021C
	PE_O20_IPC_CTRL_32_T                              ipc_ctrl_32;	//0x0220
	PE_O20_IPC_CTRL_33_T                              ipc_ctrl_33;	//0x0224
	PE_O20_IPC_STATUS_04_T                            ipc_status_04;	//0x0228
	PE_O20_IPC_STATUS_05_T                            ipc_status_05;	//0x022C
	PE_O20_IPC_STATUS_06_T                            ipc_status_06;	//0x0230
	PE_O20_IPC_STATUS_07_T                            ipc_status_07;	//0x0234
	PE_O20_IPC_STATUS_08_T                            ipc_status_08;	//0x0238
	PE_O20_IPC_STATUS_09_T                            ipc_status_09;	//0x023C
	PE_O20_TPD_CTRL_00_T                              tpd_ctrl_00;	//0x0240
	PE_O20_TPD_CTRL_01_T                              tpd_ctrl_01;	//0x0244
	PE_O20_TPD_CTRL_02_T                              tpd_ctrl_02;	//0x0248
	PE_O20_TPD_CTRL_03_T                              tpd_ctrl_03;	//0x024C
	PE_O20_TPD_CTRL_04_T                              tpd_ctrl_04;	//0x0250
	PE_O20_TPD_CTRL_05_T                              tpd_ctrl_05;	//0x0254
	PE_O20_TPD_CTRL_06_T                              tpd_ctrl_06;	//0x0258
	PE_O20_TPD_CTRL_07_T                              tpd_ctrl_07;	//0x025C
	PE_O20_TPD_CTRL_08_T                              tpd_ctrl_08;	//0x0260
	PE_O20_TPD_CTRL_09_T                              tpd_ctrl_09;	//0x0264
	PE_O20_TPD_STAT_00_T                              tpd_stat_00;	//0x0268
	PE_O20_CLC_CTRL_07_T                              clc_ctrl_07;	//0x026C
	PE_O20_BBD_CTRL_00_T                              bbd_ctrl_00;	//0x0270
	PE_O20_BBD_CTRL_01_T                              bbd_ctrl_01;	//0x0274
	PE_O20_BBD_CTRL_02_T                              bbd_ctrl_02;	//0x0278
	PE_O20_BBD_STAT_00_T                              bbd_stat_00;	//0x027C
	PE_O20_BBD_STAT_01_T                              bbd_stat_01;	//0x0280
	PE_O20_APL_STAT_00_T                              apl_stat_00;	//0x0284
	PE_O20_TPD_CTRL_0A_T                              tpd_ctrl_0a;	//0x0288
	PE_O20_TPD_CTRL_0B_T                              tpd_ctrl_0b;	//0x028C
	PE_O20_TPD_HIST_AI_CTRL_T                         tpd_hist_ai_ctrl;	//0x0290
	PE_O20_TPD_HIST_AI_DATA_T                         tpd_hist_ai_data;	//0x0294
	PE_O20_LVCRTL_CTRL_00_T                           lvcrtl_ctrl_00;	//0x0298
	PE_O20_TPD_STAT_01_T                              tpd_stat_01;	//0x029C
	PE_O20_TNR_STATUS_05_T                            tnr_status_05;	//0x02A0
	PE_O20_TNR_STATUS_06_T                            tnr_status_06;	//0x02A4
	PE_O20_TNR_STATUS_07_T                            tnr_status_07;	//0x02A8
	PE_O20_TNR_STATUS_08_T                            tnr_status_08;	//0x02AC
	UINT32                                            reserved03[4];	//0x02B0-0x02BC
	PE_O20_TNR_RESET_T                                tnr_reset;	//0x02C0
	UINT32                                            reserved04[3];	//0x02C4-0x02CC
	PE_O20_TNR_CTRL_40_T                              tnr_ctrl_40;	//0x02D0
	PE_O20_TNR_CTRL_41_T                              tnr_ctrl_41;	//0x02D4
	PE_O20_TNR_CTRL_42_T                              tnr_ctrl_42;	//0x02D8
	PE_O20_TNR_CTRL_43_T                              tnr_ctrl_43;	//0x02DC
	PE_O20_TNR_CTRL_44_T                              tnr_ctrl_44;	//0x02E0
	PE_O20_TNR_CTRL_45_T                              tnr_ctrl_45;	//0x02E4
	PE_O20_TNR_CTRL_46_T                              tnr_ctrl_46;	//0x02E8
	PE_O20_TNR_CTRL_47_T                              tnr_ctrl_47;	//0x02EC
	PE_O20_TNR_CTRL_48_T                              tnr_ctrl_48;	//0x02F0
	PE_O20_PE1_FSW_CTRL_00_T                          pe1_fsw_ctrl_00;
	PE_O20_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_01;
	PE_O20_PE1_FSW_CTRL_01_T                          pe1_fsw_ctrl_02;//0x02F4-0x02FC
	PE_O20_TNR_NE_STAT_00_T                           tnr_ne_stat_00;	//0x0300
	PE_O20_TNR_NE_STAT_01_T                           tnr_ne_stat_01;	//0x0304
	PE_O20_TNR_NE_STAT_02_T                           tnr_ne_stat_02;	//0x0308
	PE_O20_TNR_NE_STAT_03_T                           tnr_ne_stat_03;	//0x030C
	PE_O20_TNR_NE_STAT_04_T                           tnr_ne_stat_04;	//0x0310
	PE_O20_TNR_NE_STAT_05_T                           tnr_ne_stat_05;	//0x0314
	PE_O20_TNR_NE_STAT_06_T                           tnr_ne_stat_06;	//0x0318
	PE_O20_TNR_NE_STAT_07_T                           tnr_ne_stat_07;	//0x031C
	PE_O20_TNR_NE_STAT_08_T                           tnr_ne_stat_08;	//0x0320
	UINT32                                            reserved06[4];	//0x0324-0x0330
	UINT32                                            reserved205[3];	//0x334-0x33c
	PE_O20_HIST2_CTRL_00_T                            hist2_ctrl_00;	//0x0340
	PE_O20_HIST2_CTRL_01_T                            hist2_ctrl_01;	//0x0344
	PE_O20_HIST2_CTRL_02_T                            hist2_ctrl_02;	//0x0348
	PE_O20_HIST2_CTRL_03_T                            hist2_ctrl_03;	//0x034C
	PE_O20_HIST2_CTRL_04_T                            hist2_ctrl_04;	//0x0350
	PE_O20_HIST2_CTRL_05_T                            hist2_ctrl_05;	//0x0354
	PE_O20_HIST2_CTRL_06_T                            hist2_ctrl_06;	//0x0358
	PE_O20_HIST2_CTRL_07_T                            hist2_ctrl_07;	//0x035C
	PE_O20_HIST2_CTRL_08_T                            hist2_ctrl_08;	//0x0360
	PE_O20_HIST2_CTRL_09_T                            hist2_ctrl_09;	//0x0364
	PE_O20_HIST2_CTRL_0A_T                            hist2_ctrl_0a;	//0x0368
	PE_O20_HIST2_CTRL_0B_T                            hist2_ctrl_0b;	//0x036C
	PE_O20_HIST2_HIST_AI_CTRL_T                       hist2_hist_ai_ctrl;	//0x0370
	PE_O20_HIST2_HIST_AI_DATA_T                       hist2_hist_ai_data;	//0x0374
	PE_O20_HIST2_STAT_00_T                            hist2_stat_00;	//0x0378
	UINT32                                            reserved220;	//0x37c
	PE_O20_ND_FSW_CTRL_00_T                           nd_fsw_ctrl_00;	//0x0380
	PE_O20_ND_FSW_CTRL_01_T                           nd_fsw_ctrl_01;	//0x0384
	PE_O20_ND_FSW_CTRL_02_T                           nd_fsw_ctrl_02;	//0x0388
	PE_O20_ND_FSW_CTRL_03_T                           nd_fsw_ctrl_03;	//0x038C
	PE_O20_TNR_ETC_CTRL_00_T                          tnr_etc_ctrl_00;	//0x0390
	PE_O20_TNR_ETC_CTRL_01_T                          tnr_etc_ctrl_01;	//0x0394
	PE_O20_TNR_ETC_CTRL_02_T                          tnr_etc_ctrl_02;	//0x0398
	PE_O20_TNR_ETC_CTRL_03_T                          tnr_etc_ctrl_03;	//0x039C
	PE_O20_TNR_CTRL_56_T                              tnr_ctrl_56;	//0x03A0
	PE_O20_TNR_CTRL_57_T                              tnr_ctrl_57;	//0x03A4
	PE_O20_TNR_CTRL_58_T                              tnr_ctrl_58;	//0x03A8
	PE_O20_TNR_CTRL_59_T                              tnr_ctrl_59;	//0x03AC
	PE_O20_TNR_CTRL_60_T                              tnr_ctrl_60;	//0x03B0
	PE_O20_TNR_CTRL_61_T                              tnr_ctrl_61;	//0x03B4
	PE_O20_PE0_DEBUG3_T                               pe0_debug3;	//0x03B8
	UINT32                                            reserved07;	//0x03BC-0x03BC
	PE_O20_FBC_CTRL_02_T                              fbc_ctrl_02;	//0x03C0
	PE_O20_FBC_CTRL_03_T                              fbc_ctrl_03;	//0x03C4
	UINT32                                            reserved08[2];	//0x03C8-0x03CC
	PE_O20_GFD_CTRL_00_T                              gfd_ctrl_00;	//0x03D0
	PE_O20_GFD_CTRL_01_T                              gfd_ctrl_01;	//0x03D4
	PE_O20_GFD_STAT_00_T                              gfd_stat_00;	//0x03D8
	PE_O20_GFD_STAT_01_T                              gfd_stat_01;	//0x03DC
	PE_O20_GFD_STAT_02_T                              gfd_stat_02;	//0x03E0
	PE_O20_GFD_STAT_03_T                              gfd_stat_03;	//0x03E4
}PE_ND_ND0_REG_O20_T;



typedef struct
{ 
	PE_O20_PE0_LOAD_T                                 pe0_load;	//0x0000
	PE_O20_PE0_INTR_T                                 pe0_intr;	//0x0004
	PE_O20_PE0_STATUS0_T                              pe0_status0;	//0x0008
	PE_O20_PE0_STATUS1_T                              pe0_status1;	//0x000C
	PE_O20_PE0_OPMODE_T                               pe0_opmode;	//0x0010
	PE_O20_PE0_IN_SIZE_T                              pe0_in_size;	//0x0014
	PE_O20_PE0_IN_OFFSET_T                            pe0_in_offset;	//0x0018
	PE_O20_PE0_OUT_SIZE_T                             pe0_out_size;	//0x001C
	PE_O20_WIN_CTRL_0_T                               win_ctrl_0;	//0x0020
	PE_O20_WIN_CTRL_1_T                               win_ctrl_1;	//0x0024
	PE_O20_WIN_CTRL_2_T                               win_ctrl_2;	//0x0028
	PE_O20_WIN_CTRL_3_T                               win_ctrl_3;	//0x002C
	PE_O20_CUP_CTRL_00_T                              cup_ctrl_00;	//0x0030
	PE_O20_CUP_CTRL_01_T                              cup_ctrl_01;	//0x0034
	PE_O20_CUP_CTRL_02_T                              cup_ctrl_02;	//0x0038
	UINT32                                            reserved00[17];	//0x003C-0x007C
	PE_O20_VFILTER_CTRL_00_T                          vfilter_ctrl_00;	//0x0080
	PE_O20_VFILTER_CTRL_01_T                          vfilter_ctrl_01;	//0x0084
	PE_O20_VFILTER_CTRL_02_T                          vfilter_ctrl_02;	//0x0088
	PE_O20_REG_CTI_CTRL_0_T                           reg_cti_ctrl_0;	//0x008C
	PE_O20_REG_CTI_CTRL_1_T                           reg_cti_ctrl_1;	//0x0090
	PE_O20_DNR_MAX_CTRL_T                             dnr_max_ctrl;	//0x0094
	PE_O20_DNR_DBAR_CTRL_T                            dnr_dbar_ctrl;	//0x0098
	PE_O20_REG_C420_CTRL_T                            reg_c420_ctrl;	//0x009C
	PE_O20_MNR_CTRL_0_T                               mnr_ctrl_0;	//0x00A0
	PE_O20_MNR_CTRL_1_T                               mnr_ctrl_1;	//0x00A4
	PE_O20_MNR_CTRL_2_T                               mnr_ctrl_2;	//0x00A8
	PE_O20_MNR_CTRL_3_T                               mnr_ctrl_3;	//0x00AC
	PE_O20_MNR_CTRL_4_T                               mnr_ctrl_4;	//0x00B0
	PE_O20_MNR_CTRL_5_T                               mnr_ctrl_5;	//0x00B4
	PE_O20_DETAIL_CTRL_T                              detail_ctrl;	//0x00B8
	PE_O20_DC_BNR_CTRL_0_T                            dc_bnr_ctrl_0;	//0x00BC
	PE_O20_DC_BNR_CTRL_1_T                            dc_bnr_ctrl_1;	//0x00C0
	PE_O20_DC_BNR_CTRL_2_T                            dc_bnr_ctrl_2;	//0x00C4
	PE_O20_DC_BNR_CTRL_3_T                            dc_bnr_ctrl_3;	//0x00C8
	PE_O20_DC_BNR_CTRL_4_T                            dc_bnr_ctrl_4;	//0x00CC
	PE_O20_DC_BNR_CTRL_5_T                            dc_bnr_ctrl_5;	//0x00D0
	PE_O20_AC_BNR_CTRL_0_T                            ac_bnr_ctrl_0;	//0x00D4
	PE_O20_AC_BNR_CTRL_1_T                            ac_bnr_ctrl_1;	//0x00D8
	PE_O20_AC_BNR_CTRL_2_T                            ac_bnr_ctrl_2;	//0x00DC
	PE_O20_DNR_STAT_0_T                               dnr_stat_0;	//0x00E0
	PE_O20_AC_BNR_CTRL_3_T                            ac_bnr_ctrl_3;	//0x00E4
	PE_O20_AC_BNR_CTRL_4_T                            ac_bnr_ctrl_4;	//0x00E8
	PE_O20_DNR_STAT_1_T                               dnr_stat_1;	//0x00EC
	PE_O20_AC_BNR_CTRL_5_T                            ac_bnr_ctrl_5;	//0x00F0
	PE_O20_AC_BNR_CTRL_6_T                            ac_bnr_ctrl_6;	//0x00F4
	PE_O20_AC_BNR_CTRL_7_T                            ac_bnr_ctrl_7;	//0x00F8
	PE_O20_DNR_STAT_2_T                               dnr_stat_2;	//0x00FC
	PE_O20_AC_BNR_CTRL_8_T                            ac_bnr_ctrl_8;	//0x0100
	PE_O20_AC_BNR_CTRL_9_T                            ac_bnr_ctrl_9;	//0x0104
	PE_O20_AC_BNR_CTRL_10_T                           ac_bnr_ctrl_10;	//0x0108
	PE_O20_AC_BNR_CTRL_11_T                           ac_bnr_ctrl_11;	//0x010C
	PE_O20_AC_BNR_CTRL_12_T                           ac_bnr_ctrl_12;	//0x0110
	PE_O20_IFC_CTRL_0_T                               ifc_ctrl_0;	//0x0114
	PE_O20_IFC_CTRL_1_T                               ifc_ctrl_1;	//0x0118
	PE_O20_IFC_CTRL_2_T                               ifc_ctrl_2;	//0x011C
	PE_O20_IFC_CTRL_3_T                               ifc_ctrl_3;	//0x0120
	PE_O20_IFC_CTRL_4_T                               ifc_ctrl_4;	//0x0124
	PE_O20_IFC_CTRL_5_T                               ifc_ctrl_5;	//0x0128
	PE_O20_IFC_CTRL_6_T                               ifc_ctrl_6;	//0x012C
	PE_O20_IFC_CTRL_7_T                               ifc_ctrl_7;	//0x0130
	PE_O20_IFC_CTRL_8_T                               ifc_ctrl_8;	//0x0134
	PE_O20_IFC_CTRL_9_T                               ifc_ctrl_9;	//0x0138
	PE_O20_IFC_CTRL_10_T                              ifc_ctrl_10;	//0x013C
	PE_O20_IFC_CTRL_11_T                              ifc_ctrl_11;	//0x0140
	PE_O20_IFC_CTRL_12_T                              ifc_ctrl_12;	//0x0144
	PE_O20_IFC_CTRL_13_T                              ifc_ctrl_13;	//0x0148
	PE_O20_IFC_CTRL_14_T                              ifc_ctrl_14;	//0x014C
	PE_O20_IFC_CTRL_15_T                              ifc_ctrl_15;	//0x0150
	PE_O20_IFC_CTRL_16_T                              ifc_ctrl_16;	//0x0154
	PE_O20_IFC_CTRL_17_T                              ifc_ctrl_17;	//0x0158
	PE_O20_IFC_CTRL_18_T                              ifc_ctrl_18;	//0x015C
	PE_O20_IFC_CTRL_19_T                              ifc_ctrl_19;	//0x0160
	PE_O20_IFC_CTRL_20_T                              ifc_ctrl_20;	//0x0164
	PE_O20_IFC_CTRL_21_T                              ifc_ctrl_21;	//0x0168
	PE_O20_SC_BNR_CTRL_0_T                            sc_bnr_ctrl_0;	//0x016C
	PE_O20_SC_BNR_CTRL_1_T                            sc_bnr_ctrl_1;	//0x0170
	PE_O20_SC_BNR_CTRL_2_T                            sc_bnr_ctrl_2;	//0x0174
	PE_O20_SC_BNR_CTRL_3_T                            sc_bnr_ctrl_3;	//0x0178
	PE_O20_SC_BNR_CTRL_4_T                            sc_bnr_ctrl_4;	//0x017C
	PE_O20_SC_BNR_CTRL_5_T                            sc_bnr_ctrl_5;	//0x0180
	PE_O20_SC_BNR_CTRL_6_T                            sc_bnr_ctrl_6;	//0x0184
	PE_O20_C_PRE_BLUR_CTRL_0_T                        c_pre_blur_ctrl_0;	//0x0188
	UINT32                                            reserved01[4];	//0x018C-0x0198
	PE_O20_AC_BNR_CTRL_13_T                           ac_bnr_ctrl_13;	//0x019C
	PE_O20_AC_BNR_CTRL_14_T                           ac_bnr_ctrl_14;	//0x01A0
	PE_O20_DC_BNR_CTRL_6_T                            dc_bnr_ctrl_6;	//0x01A4
	PE_O20_DC_BNR_CTRL_7_T                            dc_bnr_ctrl_7;	//0x01A8
	PE_O20_SQM_CTRL_0_T                               sqm_ctrl_0;	//0x01AC
	PE_O20_SQM_CTRL_1_T                               sqm_ctrl_1;	//0x01B0
	PE_O20_SQM_CTRL_2_T                               sqm_ctrl_2;	//0x01B4
	PE_O20_SQM_CTRL_3_T                               sqm_ctrl_3;	//0x01B8
	PE_O20_SQM_CTRL_4_T                               sqm_ctrl_4;	//0x01BC
	PE_O20_TPD_CTRL_0_T                               tpd_ctrl_0;	//0x01C0
	PE_O20_WINDOW_MODE_0_T                            window_mode_0;	//0x01C4
	PE_O20_WINDOW_MODE_1_T                            window_mode_1;	//0x01C8
	UINT32                                            reserved115;	//0x1cc
	PE_O20_DNR_STAT_3_T                               dnr_stat_3;	//0x01D0
	PE_O20_DNR_STAT_4_T                               dnr_stat_4;	//0x01D4
	PE_O20_DNR_STAT_5_T                               dnr_stat_5;	//0x01D8
	PE_O20_DNR_STAT_6_T                               dnr_stat_6;	//0x01DC
	PE_O20_DNR_STAT_7_T                               dnr_stat_7;	//0x01E0
	PE_O20_DNR_STAT_8_SC_BNR0_T                       dnr_stat_8_sc_bnr0;	//0x01E4
	PE_O20_DNR_STAT_9_SC_BNR1_T                       dnr_stat_9_sc_bnr1;	//0x01E8
	PE_O20_DNR_STAT_10_SC_BNR2_T                      dnr_stat_10_sc_bnr2;	//0x01EC
	PE_O20_DNR_STAT_11_SQM_00_T                       dnr_stat_11_sqm_00;	//0x01F0
	PE_O20_DNR_STAT_12_SQM_01_T                       dnr_stat_12_sqm_01;	//0x01F4
	PE_O20_DNR_STAT_13_SQM_02_T                       dnr_stat_13_sqm_02;	//0x01F8
	PE_O20_DNR_STAT_14_SQM_03_T                       dnr_stat_14_sqm_03;	//0x01FC
	PE_O20_DNR_STAT_15_SQM_04_T                       dnr_stat_15_sqm_04;	//0x0200
	PE_O20_DNR_STAT_16_SQM_05_T                       dnr_stat_16_sqm_05;	//0x0204
	PE_O20_DNR_STAT_17_SQM_06_T                       dnr_stat_17_sqm_06;	//0x0208
	PE_O20_DNR_STAT_18_SQM_07_T                       dnr_stat_18_sqm_07;	//0x020C
	PE_O20_DNR_STAT_19_SQM_08_T                       dnr_stat_19_sqm_08;	//0x0210
	PE_O20_DNR_STAT_20_SQM_09_T                       dnr_stat_20_sqm_09;	//0x0214
	PE_O20_DNR_STAT_21_SQM_10_T                       dnr_stat_21_sqm_10;	//0x0218
	PE_O20_DNR_STAT_22_SQM_11_T                       dnr_stat_22_sqm_11;	//0x021C
	PE_O20_DNR_STAT_23_TPD_0_T                        dnr_stat_23_tpd_0;	//0x0220
	PE_O20_DNR_STAT_24_TPD_1_T                        dnr_stat_24_tpd_1;	//0x0224
	PE_O20_DNR_STAT_25_TPD_2_T                        dnr_stat_25_tpd_2;	//0x0228
	UINT32                                            reserved02;	//0x022C-0x022C
	PE_O20_AC_BNR_15_T                                ac_bnr_15;	//0x0230
	PE_O20_AC_BNR_16_T                                ac_bnr_16;	//0x0234
	PE_O20_VFILTER_CTRL_03_T                          vfilter_ctrl_03;	//0x0238
	PE_O20_VFILTER_CTRL_04_T                          vfilter_ctrl_04;	//0x023C
	PE_O20_VFILTER_CTRL_05_T                          vfilter_ctrl_05;	//0x0240
	PE_O20_VFILTER_CTRL_06_T                          vfilter_ctrl_06;	//0x0244
	PE_O20_VFILTER_CTRL_07_T                          vfilter_ctrl_07;	//0x0248
	PE_O20_VFILTER_CTRL_08_T                          vfilter_ctrl_08;	//0x024C
	PE_O20_VFILTER_CTRL_09_T                          vfilter_ctrl_09;	//0x0250
	PE_O20_VFILTER_CTRL_10_T                          vfilter_ctrl_10;	//0x0254
	PE_O20_VFILTER_CTRL_11_T                          vfilter_ctrl_11;	//0x0258
	PE_O20_VFILTER_CTRL_12_T                          vfilter_ctrl_12;	//0x025C
	PE_O20_VFILTER_CTRL_13_T                          vfilter_ctrl_13;	//0x0260
	PE_O20_REG_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0264
	PE_O20_REG_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0268
	PE_O20_REG_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x026C
	PE_O20_REG_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0270
	PE_O20_REG_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0274
	PE_O20_REG_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0278
	PE_O20_REG_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x027C
	PE_O20_REG_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0280
	PE_O20_REG_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0284
	PE_O20_REG_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0288
	PE_O20_REG_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x028C
	PE_O20_REG_DC_BNR_CTRL_8_T                        reg_dc_bnr_ctrl_8;	//0x0290
	PE_O20_REG_DC_BNR_CTRL_9_T                        reg_dc_bnr_ctrl_9;	//0x0294
	PE_O20_REG_DC_BNR_CTRL_10_T                       reg_dc_bnr_ctrl_10;	//0x0298
	PE_O20_REG_DC_BNR_CTRL_11_T                       reg_dc_bnr_ctrl_11;	//0x029C
	PE_O20_REG_CTI_CTRL_2_T                           reg_cti_ctrl_2;	//0x02A0
	PE_O20_REG_CTI_CTRL_3_T                           reg_cti_ctrl_3;	//0x02A4
	PE_O20_REG_MNR_CTRL_6_T                           reg_mnr_ctrl_6;	//0x02A8
	PE_O20_REG_MNR_CTRL_7_T                           reg_mnr_ctrl_7;	//0x02AC
	PE_O20_REG_MNR_CTRL_8_T                           reg_mnr_ctrl_8;	//0x02B0
	PE_O20_REG_MNR_CTRL_9_T                           reg_mnr_ctrl_9;	//0x02B4
	PE_O20_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0x02B8
	PE_O20_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0x02BC
	PE_O20_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0x02C0
	PE_O20_REG_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x02C4
	PE_O20_REG_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x02C8
	PE_O20_REG_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x02CC
	PE_O20_REG_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x02D0
	PE_O20_REG_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x02D4
	PE_O20_REG_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x02D8
	PE_O20_REG_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x02DC
	PE_O20_REG_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x02E0
	PE_O20_REG_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x02E4
	PE_O20_REG_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x02E8
	PE_O20_REG_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x02EC
	PE_O20_REG_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x02F0
	PE_O20_REG_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x02F4
	PE_O20_REG_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x02F8
	PE_O20_REG_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x02FC
	PE_O20_REG_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x0300
	PE_O20_REG_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x0304
	PE_O20_REG_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x0308
	PE_O20_REG_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x030C
	PE_O20_REG_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x0310
	PE_O20_REG_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x0314
	PE_O20_REG_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x0318
	PE_O20_REG_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x031C
	PE_O20_REG_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x0320
	PE_O20_REG_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x0324
	PE_O20_REG_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x0328
	PE_O20_REG_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x032C
	PE_O20_REG_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x0330
	PE_O20_REG_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x0334
	PE_O20_REG_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x0338
	PE_O20_REG_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x033C
	PE_O20_REG_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x0340
	PE_O20_REG_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0344
	PE_O20_REG_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x0348
	PE_O20_REG_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x034C
	PE_O20_REG_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x0350
	PE_O20_REG_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0354
	PE_O20_REG_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x0358
	PE_O20_REG_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x035C
	PE_O20_REG_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x0360
	PE_O20_REG_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0364
	PE_O20_REG_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x0368
	PE_O20_REG_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x036C
	PE_O20_REG_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x0370
	PE_O20_REG_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0374
	PE_O20_REG_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x0378
	PE_O20_REG_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x037C
	PE_O20_REG_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x0380
	PE_O20_REG_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0384
	PE_O20_REG_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x0388
	PE_O20_REG_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x038C
	PE_O20_REG_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x0390
	PE_O20_REG_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0394
	PE_O20_REG_DC_BNR_CTRL_12_T                       reg_dc_bnr_ctrl_12;	//0x0398
	PE_O20_REG_DC_BNR_CTRL_13_T                       reg_dc_bnr_ctrl_13;	//0x039C
	PE_O20_REG_DC_BNR_CTRL_14_T                       reg_dc_bnr_ctrl_14;	//0x03A0
	PE_O20_REG_DC_BNR_CTRL_15_T                       reg_dc_bnr_ctrl_15;	//0x03A4
	PE_O20_REG_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x03A8
	PE_O20_REG_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x03AC
	PE_O20_REG_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x03B0
	PE_O20_REG_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x03B4
	PE_O20_REG_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x03B8
	PE_O20_REG_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x03BC
	PE_O20_REG_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x03C0
	PE_O20_REG_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x03C4
	PE_O20_REG_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x03C8
	PE_O20_REG_DECON_CTRL_73_T                        reg_decon_ctrl_73;	//0x03CC
	PE_O20_REG_DECON_CTRL_74_T                        reg_decon_ctrl_74;	//0x03D0
	PE_O20_REG_DECON_CTRL_75_T                        reg_decon_ctrl_75;	//0x03D4
	PE_O20_REG_DECON_CTRL_76_T                        reg_decon_ctrl_76;	//0x03D8
	PE_O20_REG_DECON_CTRL_77_T                        reg_decon_ctrl_77;	//0x03DC
	PE_O20_REG_DECON_CTRL_78_T                        reg_decon_ctrl_78;	//0x03E0
	PE_O20_REG_DECON_CTRL_79_T                        reg_decon_ctrl_79;	//0x03E4
	PE_O20_REG_DECON_CTRL_80_T                        reg_decon_ctrl_80;	//0x03E8
	PE_O20_REG_DECON_CTRL_81_T                        reg_decon_ctrl_81;	//0x03EC
	PE_O20_REG_DECON_CTRL_82_T                        reg_decon_ctrl_82;	//0x03F0
	PE_O20_REG_DECON_CTRL_83_T                        reg_decon_ctrl_83;	//0x03F4
}PE_ND_DNR0_REG_O20_T;

typedef struct
{ 
	PE_O20_PSP_CTRL00_O_T                               psp_ctrl00;	//0x0000
	PE_O20_PSP_CTRL01_O_T                               psp_ctrl01;	//0x0004
	PE_O20_PSP_CTRL02_O_T                               psp_ctrl02;	//0x0008
	PE_O20_EDGE_TH_O_T                                  edge_th;	//0x000C
	PE_O20_FG_POSITION_O_T                              fg_position;	//0x0010
	PE_O20_PERSPECT_LUT_X0_O_T                          perspect_lut_x0;	//0x0014
	PE_O20_PERSPECT_LUT_X1_O_T                          perspect_lut_x1;	//0x0018
	PE_O20_PERSPECT_LUT_X2_O_T                          perspect_lut_x2;	//0x001C
	PE_O20_PERSPECT_LUT_X3_O_T                          perspect_lut_x3;	//0x0020
	PE_O20_PERSPECT_LUT_Y0_O_T                          perspect_lut_y0;	//0x0024
	PE_O20_PERSPECT_LUT_Y1_O_T                          perspect_lut_y1;	//0x0028
	PE_O20_PERSPECT_LUT_Y2_O_T                          perspect_lut_y2;	//0x002C
	PE_O20_PERSPECT_LUT_Y3_O_T                          perspect_lut_y3;	//0x0030
	PE_O20_PROB_MAP_O_T                                 prob_map;	//0x0034
	PE_O20_ELLIPS_MAP_O_T                               ellips_map;	//0x0038
	PE_O20_PROB_DIFF_MAP_O_T                            prob_diff_map;	//0x003C
	PE_O20_OBJECT_MAP_O_T                               object_map;	//0x0040
	PE_O20_BLUR_MAP_O_T                                 blur_map;	//0x0044
	PE_O20_DISPLAY_DEBUG_MAP_O_T                        display_debug_map;	//0x0048
	PE_O20_PSP_IIR_O_T                                  psp_iir;	//0x004C
	PE_O20_PSP_GAIN_O_T                                 psp_gain;	//0x0050
	PE_O20_PSP_DBG_MON00_O_T                            psp_dbg_mon00;	//0x0054
	PE_O20_PSP_DBG_MON01_O_T                            psp_dbg_mon01;	//0x0058
	PE_O20_VRTX_CPC_CTRL_O_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_BLUR_HCOEF01_O_T                             blur_hcoef01;	//0x0060
	PE_O20_BLUR_HCOEF23_O_T                             blur_hcoef23;	//0x0064
	PE_O20_BLUR_HCOEF45_O_T                             blur_hcoef45;	//0x0068
	PE_O20_BLUR_HCOEF67_O_T                             blur_hcoef67;	//0x006C
	PE_O20_BLUR_HCOEF8_O_T                              blur_hcoef8;	//0x0070
	PE_O20_BLUR_VCOEF01_O_T                             blur_vcoef01;	//0x0074
	PE_O20_BLUR_VCOEF23_O_T                             blur_vcoef23;	//0x0078
	PE_O20_BLUR_VCOEF4_O_T                              blur_vcoef4;	//0x007C
	PE_O20_HISTOGRAM_0_O_T                              histogram_0;	//0x0080
	PE_O20_HISTOGRAM_1_O_T                              histogram_1;	//0x0084
	PE_O20_HISTOGRAM_2_O_T                              histogram_2;	//0x0088
	PE_O20_HISTOGRAM_3_O_T                              histogram_3;	//0x008C
	PE_O20_HISTOGRAM_4_O_T                              histogram_4;	//0x0090
	PE_O20_HISTOGRAM_5_O_T                              histogram_5;	//0x0094
	PE_O20_HISTOGRAM_6_O_T                              histogram_6;	//0x0098
	PE_O20_HISTOGRAM_7_O_T                              histogram_7;	//0x009C
	PE_O20_HISTOGRAM_8_O_T                              histogram_8;	//0x00A0
	PE_O20_HISTOGRAM_9_O_T                              histogram_9;	//0x00A4
	PE_O20_HISTOGRAM_10_O_T                             histogram_10;	//0x00A8
	PE_O20_HISTOGRAM_11_O_T                             histogram_11;	//0x00AC
	PE_O20_HISTOGRAM_12_O_T                             histogram_12;	//0x00B0
	PE_O20_HISTOGRAM_13_O_T                             histogram_13;	//0x00B4
	PE_O20_HISTOGRAM_14_O_T                             histogram_14;	//0x00B8
	PE_O20_HISTOGRAM_15_O_T                             histogram_15;	//0x00BC
	PE_O20_HISTOGRAM_16_O_T                             histogram_16;	//0x00C0
	PE_O20_HISTOGRAM_17_O_T                             histogram_17;	//0x00C4
	PE_O20_HISTOGRAM_18_O_T                             histogram_18;	//0x00C8
	PE_O20_HISTOGRAM_19_O_T                             histogram_19;	//0x00CC
	PE_O20_HISTOGRAM_20_O_T                             histogram_20;	//0x00D0
	PE_O20_HISTOGRAM_21_O_T                             histogram_21;	//0x00D4
	PE_O20_HISTOGRAM_22_O_T                             histogram_22;	//0x00D8
	PE_O20_HISTOGRAM_23_O_T                             histogram_23;	//0x00DC
	PE_O20_HISTOGRAM_24_O_T                             histogram_24;	//0x00E0
	PE_O20_HISTOGRAM_25_O_T                             histogram_25;	//0x00E4
	PE_O20_HISTOGRAM_26_O_T                             histogram_26;	//0x00E8
	PE_O20_HISTOGRAM_27_O_T                             histogram_27;	//0x00EC
	PE_O20_HISTOGRAM_28_O_T                             histogram_28;	//0x00F0
	PE_O20_HISTOGRAM_29_O_T                             histogram_29;	//0x00F4
	PE_O20_HISTOGRAM_30_O_T                             histogram_30;	//0x00F8
	PE_O20_HISTOGRAM_31_O_T                             histogram_31;	//0x00FC
	PE_O20_L5_GAIN_LUT1_O_T                             l5_gain_lut1;	//0x0100
	PE_O20_L5_GAIN_LUT2_O_T                             l5_gain_lut2;	//0x0104
	PE_O20_L0_GAIN_LUT1_O_T                             l0_gain_lut1;	//0x0108
	PE_O20_L0_GAIN_LUT2_O_T                             l0_gain_lut2;	//0x010C
	PE_O20_EDGE_WIN_H_O_T                               edge_win_h;	//0x0110
	PE_O20_EDGE_WIN_V_O_T                               edge_win_v;	//0x0114
	PE_O20_EDGE0_FG_O_T                                 edge0_fg;	//0x0118
	PE_O20_EDGE0_BG_O_T                                 edge0_bg;	//0x011C
	PE_O20_EDGE1_FG_O_T                                 edge1_fg;	//0x0120
	PE_O20_EDGE1_BG_O_T                                 edge1_bg;	//0x0124
	PE_O20_PSP_IIR1_O_T                                 psp_iir1;	//0x0128
	PE_O20_BG_MEASURE_CTRL_O_T                          bg_measure_ctrl;	//0x012C
	PE_O20_BG_MEASURE_READ0_O_T                         bg_measure_read0;	//0x0130
	PE_O20_BG_MEASURE_READ1_O_T                         bg_measure_read1;	//0x0134
	PE_O20_BG_MEASURE_READ2_O_T                         bg_measure_read2;	//0x0138
	PE_O20_BG_MEASURE_READ3_O_T                         bg_measure_read3;	//0x013C
	PE_O20_BG_MEASURE_READ4_O_T                         bg_measure_read4;	//0x0140
}PE_DNR0_OBC_OBJT_REG_O20_T;

typedef struct
{ 
	PE_O20_PSP_CTRL00_T                               psp_ctrl00;	//0x0000
	PE_O20_PSP_CTRL01_T                               psp_ctrl01;	//0x0004
	PE_O20_PSP_CTRL02_T                               psp_ctrl02;	//0x0008
	PE_O20_EDGE_TH_T                                  edge_th;	//0x000C
	PE_O20_FG_POSITION_T                              fg_position;	//0x0010
	PE_O20_PERSPECT_LUT_X0_T                          perspect_lut_x0;	//0x0014
	PE_O20_PERSPECT_LUT_X1_T                          perspect_lut_x1;	//0x0018
	PE_O20_PERSPECT_LUT_X2_T                          perspect_lut_x2;	//0x001C
	PE_O20_PERSPECT_LUT_X3_T                          perspect_lut_x3;	//0x0020
	PE_O20_PERSPECT_LUT_Y0_T                          perspect_lut_y0;	//0x0024
	PE_O20_PERSPECT_LUT_Y1_T                          perspect_lut_y1;	//0x0028
	PE_O20_PERSPECT_LUT_Y2_T                          perspect_lut_y2;	//0x002C
	PE_O20_PERSPECT_LUT_Y3_T                          perspect_lut_y3;	//0x0030
	PE_O20_PROB_MAP_T                                 prob_map;	//0x0034
	PE_O20_ELLIPS_MAP_T                               ellips_map;	//0x0038
	PE_O20_PROB_DIFF_MAP_T                            prob_diff_map;	//0x003C
	PE_O20_OBJECT_MAP_T                               object_map;	//0x0040
	PE_O20_BLUR_MAP_T                                 blur_map;	//0x0044
	PE_O20_DISPLAY_DEBUG_MAP_T                        display_debug_map;	//0x0048
	PE_O20_PSP_IIR_T                                  psp_iir;	//0x004C
	PE_O20_PSP_GAIN_T                                 psp_gain;	//0x0050
	PE_O20_PSP_DBG_MON00_T                            psp_dbg_mon00;	//0x0054
	PE_O20_PSP_DBG_MON01_T                            psp_dbg_mon01;	//0x0058
	PE_O20_VRTX_CPC_CTRL_T                            vrtx_cpc_ctrl;	//0x005C
	PE_O20_BLUR_HCOEF01_T                             blur_hcoef01;	//0x0060
	PE_O20_BLUR_HCOEF23_T                             blur_hcoef23;	//0x0064
	PE_O20_BLUR_HCOEF45_T                             blur_hcoef45;	//0x0068
	PE_O20_BLUR_HCOEF67_T                             blur_hcoef67;	//0x006C
	PE_O20_BLUR_HCOEF8_T                              blur_hcoef8;	//0x0070
	PE_O20_BLUR_VCOEF01_T                             blur_vcoef01;	//0x0074
	PE_O20_BLUR_VCOEF23_T                             blur_vcoef23;	//0x0078
	PE_O20_BLUR_VCOEF4_T                              blur_vcoef4;	//0x007C
	PE_O20_HISTOGRAM_0_T                              histogram_0;	//0x0080
	PE_O20_HISTOGRAM_1_T                              histogram_1;	//0x0084
	PE_O20_HISTOGRAM_2_T                              histogram_2;	//0x0088
	PE_O20_HISTOGRAM_3_T                              histogram_3;	//0x008C
	PE_O20_HISTOGRAM_4_T                              histogram_4;	//0x0090
	PE_O20_HISTOGRAM_5_T                              histogram_5;	//0x0094
	PE_O20_HISTOGRAM_6_T                              histogram_6;	//0x0098
	PE_O20_HISTOGRAM_7_T                              histogram_7;	//0x009C
	PE_O20_HISTOGRAM_8_T                              histogram_8;	//0x00A0
	PE_O20_HISTOGRAM_9_T                              histogram_9;	//0x00A4
	PE_O20_HISTOGRAM_10_T                             histogram_10;	//0x00A8
	PE_O20_HISTOGRAM_11_T                             histogram_11;	//0x00AC
	PE_O20_HISTOGRAM_12_T                             histogram_12;	//0x00B0
	PE_O20_HISTOGRAM_13_T                             histogram_13;	//0x00B4
	PE_O20_HISTOGRAM_14_T                             histogram_14;	//0x00B8
	PE_O20_HISTOGRAM_15_T                             histogram_15;	//0x00BC
	PE_O20_HISTOGRAM_16_T                             histogram_16;	//0x00C0
	PE_O20_HISTOGRAM_17_T                             histogram_17;	//0x00C4
	PE_O20_HISTOGRAM_18_T                             histogram_18;	//0x00C8
	PE_O20_HISTOGRAM_19_T                             histogram_19;	//0x00CC
	PE_O20_HISTOGRAM_20_T                             histogram_20;	//0x00D0
	PE_O20_HISTOGRAM_21_T                             histogram_21;	//0x00D4
	PE_O20_HISTOGRAM_22_T                             histogram_22;	//0x00D8
	PE_O20_HISTOGRAM_23_T                             histogram_23;	//0x00DC
	PE_O20_HISTOGRAM_24_T                             histogram_24;	//0x00E0
	PE_O20_HISTOGRAM_25_T                             histogram_25;	//0x00E4
	PE_O20_HISTOGRAM_26_T                             histogram_26;	//0x00E8
	PE_O20_HISTOGRAM_27_T                             histogram_27;	//0x00EC
	PE_O20_HISTOGRAM_28_T                             histogram_28;	//0x00F0
	PE_O20_HISTOGRAM_29_T                             histogram_29;	//0x00F4
	PE_O20_HISTOGRAM_30_T                             histogram_30;	//0x00F8
	PE_O20_HISTOGRAM_31_T                             histogram_31;	//0x00FC
	PE_O20_L5_GAIN_LUT1_T                             l5_gain_lut1;	//0x0100
	PE_O20_L5_GAIN_LUT2_T                             l5_gain_lut2;	//0x0104
	PE_O20_L0_GAIN_LUT1_T                             l0_gain_lut1;	//0x0108
	PE_O20_L0_GAIN_LUT2_T                             l0_gain_lut2;	//0x010C
	PE_O20_EDGE_WIN_H_T                               edge_win_h;	//0x0110
	PE_O20_EDGE_WIN_V_T                               edge_win_v;	//0x0114
	PE_O20_EDGE0_FG_T                                 edge0_fg;	//0x0118
	PE_O20_EDGE0_BG_T                                 edge0_bg;	//0x011C
	PE_O20_EDGE1_FG_T                                 edge1_fg;	//0x0120
	PE_O20_EDGE1_BG_T                                 edge1_bg;	//0x0124
	PE_O20_PSP_IIR1_T                                 psp_iir1;	//0x0128
	PE_O20_BG_MEASURE_CTRL_T                          bg_measure_ctrl;	//0x012C
	PE_O20_BG_MEASURE_READ0_T                         bg_measure_read0;	//0x0130
	PE_O20_BG_MEASURE_READ1_T                         bg_measure_read1;	//0x0134
	PE_O20_BG_MEASURE_READ2_T                         bg_measure_read2;	//0x0138
	PE_O20_BG_MEASURE_READ3_T                         bg_measure_read3;	//0x013C
	PE_O20_BG_MEASURE_READ4_T                         bg_measure_read4;	//0x0140
	PE_O20_FACE0_SET_T                                face0_set;	//0x0144
	PE_O20_FACE1_SET_T                                face1_set;	//0x0148
	PE_O20_FACE2_SET_T                                face2_set;	//0x014C
	PE_O20_FACE3_SET_T                                face3_set;	//0x0150
	PE_O20_ELLIPS0_SET_T                              ellips0_set;	//0x0154
	PE_O20_ELLIPS1_SET_T                              ellips1_set;	//0x0158
	PE_O20_ELLIPS2_SET_T                              ellips2_set;	//0x015C
	PE_O20_ELLIPS3_SET_T                              ellips3_set;	//0x0160
}PE_DNR0_OBC_FACE_REG_O20_T;

typedef struct {
	PE_O20_CTRL_M0_Y_LEVEL_CTRL_T         ctrl_m0_y_level_ctrl;
}PE_TOP_IMX_REG_O20_T;

#endif
