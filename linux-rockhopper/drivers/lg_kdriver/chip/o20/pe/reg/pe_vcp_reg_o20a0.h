#ifndef _PE_VCP_REG_O20A0_H_
#define _PE_VCP_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif
/*-----------------------------------------------------------------------------
                             0xc900c400L vcp_disp_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	mask_pic_init_y_mux_u0_cdc         :1 ,	// 0 
	mask_pic_init_c_mux_u0_cdc         :1 ,	// 1 
	mask_pic_init_y_mux_u1_cdc         :1 ,	// 2 
	mask_pic_init_c_mux_u1_cdc         :1 ,	// 3 
	reserved01                         :4 ,	// reserved
	mask_pic_init_y_mux_m_wcp          :1 ,	// 8 
	mask_pic_init_c_mux_m_wcp          :1 ,	// 9 
	reserved                           :1 ,	// 10
	reserved1                          :1 ,	// 11
	mask_pic_init_y_mux_ms_wcp         :1 ,	// 12
	mask_pic_init_c_mux_ms_wcp         :1 ,	// 13
	reserved02                         :2 ,	// reserved
	mask_pic_start_y_mux_u0_cdc        :1 ,	// 16
	mask_pic_start_c_mux_u0_cdc        :1 ,	// 17
	mask_pic_start_y_mux_u1_cdc        :1 ,	// 18
	mask_pic_start_c_mux_u1_cdc        :1 ,	// 19
	reserved03                         :4 ,	// reserved
	mask_pic_start_y_mux_m_wcp         :1 ,	// 24
	mask_pic_start_c_mux_m_wcp         :1 ,	// 25
	reserved2                          :1 ,	// 26
	reserved3                          :1 ;	// 27
}PE_O20_VCP_DISP_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c404L vcp_disp_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_DISP_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c408L vcp_disp_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_inverse_3d_lr                  :1 ,	// 0 
	vcp_u1_disp_clk_cg                 :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	wcp_m_mix_enable                   :2 ,	// 5:4
	cg_disable                         :1 ,	// 6 
	reserved02                         :1 ,	// reserved
	en_bypass_sync_my                  :1 ,	// 8 
	en_bypass_sync_mc                  :1 ,	// 9 
	en_bypass_sync_sy                  :1 ,	// 10
	en_bypass_sync_sc                  :1 ;	// 11
}PE_O20_VCP_DISP_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c40cL vcp_disp_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_DISP_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc900c410L vcp_cdc_mv_sync_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	u0_cdc_y_sync_sel                  :2 ,	// 1:0
	u0_cdc_c_sync_sel                  :2 ,	// 3:2
	u1_cdc_y_sync_sel                  :2 ,	// 5:4
	u1_cdc_c_sync_sel                  :2 ,	// 7:6
	reserved01                         :8 ,	// reserved
	mon_u0_cdc_y_pi_ps_pos_sel         :2 ,	// 17:16
	mon_u0_cdc_c_pi_ps_pos_sel         :2 ,	// 19:18
	mon_u1_cdc_y_pi_ps_pos_sel         :2 ,	// 21:20
	mon_u1_cdc_c_pi_ps_pos_sel         :2 ;	// 23:22
}PE_O20_VCP_CDC_MV_SYNC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c414L vcp_cdc_mv_rst_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	u0_cdc_y_disp_sreset               :1 ,	// 0 
	u0_cdc_c_disp_sreset               :1 ,	// 1 
	u1_cdc_y_disp_sreset               :1 ,	// 2 
	u1_cdc_c_disp_sreset               :1 ;	// 3 
}PE_O20_VCP_CDC_MV_RST_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c420L vcp_u0_win_o_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_pos_x                    :13;	// 28:16
}PE_O20_VCP_U0_WIN_O_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c424L vcp_u0_win_o_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y                   :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_size_x                   :13;	// 28:16
}PE_O20_VCP_U0_WIN_O_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c428L vcp_u0_pg_pat_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	ramp_pat_en                        :2 ,	// 5:4
	mpg_o_color_sel                    :2 ,	// 7:6
	reserved02                         :8 ,	// reserved
	peaking_en                         :1 ,	// 16
	peak_min_max_clip                  :1 ,	// 17
	reserved03                         :2 ,	// reserved
	peak_even_odd_sel                  :1 ,	// 20
	reg_odd_size_dbg                   :1 ,	// 21
	reserved04                         :2 ,	// reserved
	peak_gain                          :8 ;	// 31:24
}PE_O20_VCP_U0_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c42cL vcp_u0_pg_peak_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	peak_hsize                         :13;	// 12:0
}PE_O20_VCP_U0_PG_PEAK_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c430L vcp_u0_cdc_y_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	// 4:0
	cdc_rdy_ctrl                       :1 ,	// 5 
	cdc_auto_v_half                    :1 ,	// 6 
	cdc_black_mask                     :1 ,	// 7 
	cdc_vmode                          :3 ,	// 10:8
	cdc_vmode_cnt_sel                  :1 ,	// 11
	cdc_scan_type                      :3 ,	// 14:12
	reserved01                         :1 ,	// reserved
	cdc_hmode                          :3 ,	// 18:16
	cdc_hmode_cnt_sel                  :1 ,	// 19
	cdc_ch                             :2 ,	// 21:20
	cdc_de_mode                        :1 ,	// 22
	reserved02                         :1 ,	// reserved
	cdc_format                         :4 ,	// 27:24
	cdc_lsb_omode                      :4 ;	// 31:28
}PE_O20_VCP_U0_CDC_Y_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c434L vcp_u0_cdc_y_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	// 7:0
	nactive_color_cb                   :8 ,	// 15:8
	nactive_color_y                    :8 ,	// 23:16
	nactive_window_end_ctrl            :3 ,	// 26:24
	reserved01                         :1 ,	// reserved
	nactive_window_start_ctrl          :3 ,	// 30:28
	nactive_color_enable               :1 ;	// 31
}PE_O20_VCP_U0_CDC_Y_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c438L vcp_u0_cdc_y_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_u0_cdc          :4 ,	// 3:0
	set_pic_start_y_mux_u0_cdc         :4 ,	// 7:4
	sel_de_type                        :2 ,	// 9:8
	sel_de_type_manual                 :1 ,	// 10
	reserved01                         :5 ,	// reserved
	cdc_xpos_end                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	en_sel_cdc_xpos_end                :1 ;	// 31
}PE_O20_VCP_U0_CDC_Y_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c43cL vcp_u0_cdc_y_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_U0_CDC_Y_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c440L vcp_u0_cdc_c_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	// 4:0
	cdc_rdy_ctrl                       :1 ,	// 5 
	cdc_auto_v_half                    :1 ,	// 6 
	cdc_black_mask                     :1 ,	// 7 
	cdc_vmode                          :3 ,	// 10:8
	cdc_vmode_cnt_sel                  :1 ,	// 11
	cdc_scan_type                      :3 ,	// 14:12
	reserved01                         :1 ,	// reserved
	cdc_hmode                          :3 ,	// 18:16
	cdc_hmode_cnt_sel                  :1 ,	// 19
	cdc_ch                             :2 ,	// 21:20
	cdc_de_mode                        :1 ,	// 22
	reserved02                         :1 ,	// reserved
	cdc_format                         :4 ,	// 27:24
	cdc_lsb_omode                      :4 ;	// 31:28
}PE_O20_VCP_U0_CDC_C_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c444L vcp_u0_cdc_c_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	// 7:0
	nactive_color_cb                   :8 ,	// 15:8
	nactive_color_y                    :8 ,	// 23:16
	nactive_window_end_ctrl            :3 ,	// 26:24
	reserved01                         :1 ,	// reserved
	nactive_window_start_ctrl          :3 ,	// 30:28
	nactive_color_enable               :1 ;	// 31
}PE_O20_VCP_U0_CDC_C_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c448L vcp_u0_cdc_c_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_c_mux_u0_cdc          :4 ,	// 3:0
	set_pic_start_c_mux_u0_cdc         :4 ,	// 7:4
	sel_de_type                        :2 ,	// 9:8
	sel_de_type_manual                 :1 ,	// 10
	reserved01                         :5 ,	// reserved
	cdc_xpos_end                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	en_sel_cdc_xpos_end                :1 ;	// 31
}PE_O20_VCP_U0_CDC_C_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c44cL vcp_u0_cdc_c_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_U0_CDC_C_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c450L vcp_u1_win_o_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_pos_x                    :13;	// 28:16
}PE_O20_VCP_U1_WIN_O_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c454L vcp_u1_win_o_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y                   :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_size_x                   :13;	// 28:16
}PE_O20_VCP_U1_WIN_O_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c458L vcp_u1_pg_pat_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	ramp_pat_en                        :2 ,	// 5:4
	mpg_o_color_sel                    :2 ,	// 7:6
	reserved02                         :8 ,	// reserved
	peaking_en                         :1 ,	// 16
	peak_min_max_clip                  :1 ,	// 17
	reserved03                         :2 ,	// reserved
	peak_even_odd_sel                  :1 ,	// 20
	reg_odd_size_dbg                   :1 ,	// 21
	reserved04                         :2 ,	// reserved
	peak_gain                          :8 ;	// 31:24
}PE_O20_VCP_U1_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c45cL vcp_u1_pg_peak_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	peak_hsize                         :13;	// 12:0
}PE_O20_VCP_U1_PG_PEAK_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c460L vcp_u1_cdc_y_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	// 4:0
	cdc_rdy_ctrl                       :1 ,	// 5 
	cdc_auto_v_half                    :1 ,	// 6 
	cdc_black_mask                     :1 ,	// 7 
	cdc_vmode                          :3 ,	// 10:8
	cdc_vmode_cnt_sel                  :1 ,	// 11
	cdc_scan_type                      :3 ,	// 14:12
	reserved01                         :1 ,	// reserved
	cdc_hmode                          :3 ,	// 18:16
	cdc_hmode_cnt_sel                  :1 ,	// 19
	cdc_ch                             :2 ,	// 21:20
	cdc_de_mode                        :1 ,	// 22
	reserved02                         :1 ,	// reserved
	cdc_format                         :4 ,	// 27:24
	cdc_lsb_omode                      :4 ;	// 31:28
}PE_O20_VCP_U1_CDC_Y_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c464L vcp_u1_cdc_y_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	// 7:0
	nactive_color_cb                   :8 ,	// 15:8
	nactive_color_y                    :8 ,	// 23:16
	nactive_window_end_ctrl            :3 ,	// 26:24
	reserved01                         :1 ,	// reserved
	nactive_window_start_ctrl          :3 ,	// 30:28
	nactive_color_enable               :1 ;	// 31
}PE_O20_VCP_U1_CDC_Y_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c468L vcp_u1_cdc_y_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_u1_cdc          :4 ,	// 3:0
	set_pic_start_y_mux_u1_cdc         :4 ,	// 7:4
	sel_de_type                        :2 ,	// 9:8
	sel_de_type_manual                 :1 ,	// 10
	reserved01                         :5 ,	// reserved
	cdc_xpos_end                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	en_sel_cdc_xpos_end                :1 ;	// 31
}PE_O20_VCP_U1_CDC_Y_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c46cL vcp_u1_cdc_y_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_U1_CDC_Y_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c470L vcp_u1_cdc_c_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_voffset                        :5 ,	// 4:0
	cdc_rdy_ctrl                       :1 ,	// 5 
	cdc_auto_v_half                    :1 ,	// 6 
	cdc_black_mask                     :1 ,	// 7 
	cdc_vmode                          :3 ,	// 10:8
	cdc_vmode_cnt_sel                  :1 ,	// 11
	cdc_scan_type                      :3 ,	// 14:12
	reserved01                         :1 ,	// reserved
	cdc_hmode                          :3 ,	// 18:16
	cdc_hmode_cnt_sel                  :1 ,	// 19
	cdc_ch                             :2 ,	// 21:20
	cdc_de_mode                        :1 ,	// 22
	reserved02                         :1 ,	// reserved
	cdc_format                         :4 ,	// 27:24
	cdc_lsb_omode                      :4 ;	// 31:28
}PE_O20_VCP_U1_CDC_C_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c474L vcp_u1_cdc_c_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	nactive_color_cr                   :8 ,	// 7:0
	nactive_color_cb                   :8 ,	// 15:8
	nactive_color_y                    :8 ,	// 23:16
	nactive_window_end_ctrl            :3 ,	// 26:24
	reserved01                         :1 ,	// reserved
	nactive_window_start_ctrl          :3 ,	// 30:28
	nactive_color_enable               :1 ;	// 31
}PE_O20_VCP_U1_CDC_C_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c478L vcp_u1_cdc_c_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_c_mux_u1_cdc          :4 ,	// 3:0
	set_pic_start_c_mux_u1_cdc         :4 ,	// 7:4
	sel_de_type                        :2 ,	// 9:8
	sel_de_type_manual                 :1 ,	// 10
	reserved01                         :5 ,	// reserved
	cdc_xpos_end                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	en_sel_cdc_xpos_end                :1 ;	// 31
}PE_O20_VCP_U1_CDC_C_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c47cL vcp_u1_cdc_c_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_U1_CDC_C_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c480L vcp_u0_win_o_pos_aux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y_aux                :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_pos_x_aux                :13;	// 28:16
}PE_O20_VCP_U0_WIN_O_POS_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c484L vcp_u0_win_o_size_aux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y_aux               :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_size_x_aux               :13,	// 28:16
	reserved02                         :2 ,	// reserved
	cdc_win_aux_auto                   :1 ;	// 31
}PE_O20_VCP_U0_WIN_O_SIZE_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c488L vcp_u1_win_o_pos_aux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_pos_y_aux                :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_pos_x_aux                :13;	// 28:16
}PE_O20_VCP_U1_WIN_O_POS_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c48cL vcp_u1_win_o_size_aux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	cdc_win_o_size_y_aux               :14,	// 13:0
	reserved01                         :2 ,	// reserved
	cdc_win_o_size_x_aux               :13,	// 28:16
	reserved02                         :2 ,	// reserved
	cdc_win_aux_auto                   :1 ;	// 31
}PE_O20_VCP_U1_WIN_O_SIZE_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e0L vcp_sg_mvy_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e4L vcp_sg_mvy_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c4e8L vcp_sg_mvy_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c4ecL vcp_sg_mvy_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f0L vcp_sg_mvy_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	// 15:0
	sync_i_h_sel                       :1 ,	// 16
	sync_i_v_sel                       :1 ,	// 17
	sync_i_inv_ha                      :1 ,	// 18
	sync_i_inv_va                      :1 ,	// 19
	sync_o_sel_ha                      :1 ,	// 20
	sync_o_sel_va                      :1 ,	// 21
	sync_o_sel_hs                      :1 ,	// 22
	sync_o_sel_vs                      :1 ,	// 23
	tp_update_hv_zero                  :1 ,	// 24
	reserved01                         :3 ,	// reserved
	manual_cnt_h_value_en              :1 ,	// 28
	manual_cnt_v_value_en              :1 ,	// 29
	reserved02                         :1 ,	// reserved
	update_force                       :1 ;	// 31
}PE_O20_VCP_SG_MVY_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f4L vcp_sg_mvy_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c4f8L vcp_sg_mvy_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c4fcL vcp_sg_mvy_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	// 14:0
	auto_general_en                    :1 ,	// 15
	auto_va_delay                      :15,	// 30:16
	auto_seamless                      :1 ;	// 31
}PE_O20_VCP_SG_MVY_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c500L vcp_sg_mvy_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	// 14:0
	auto_general_en                    :1 ,	// 15
	auto_vs_delay                      :15,	// 30:16
	auto_seamless                      :1 ;	// 31
}PE_O20_VCP_SG_MVY_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c504L vcp_sg_mvy_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :31,	// reserved
	sync_out_disable                   :1 ;	// 31
}PE_O20_VCP_SG_MVY_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c510L vcp_sg_mvc_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vsync                              :16,	// 15:0
	vfp                                :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c514L vcp_sg_mvc_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	va                                 :16,	// 15:0
	vbp                                :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c518L vcp_sg_mvc_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	hsync                              :16,	// 15:0
	hfp                                :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c51cL vcp_sg_mvc_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	ha                                 :16,	// 15:0
	hbp                                :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c520L vcp_sg_mvc_ctrl_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	line_start_pos                     :16,	// 15:0
	sync_i_h_sel                       :1 ,	// 16
	sync_i_v_sel                       :1 ,	// 17
	sync_i_inv_ha                      :1 ,	// 18
	sync_i_inv_va                      :1 ,	// 19
	sync_o_sel_ha                      :1 ,	// 20
	sync_o_sel_va                      :1 ,	// 21
	sync_o_sel_hs                      :1 ,	// 22
	sync_o_sel_vs                      :1 ,	// 23
	tp_update_hv_zero                  :1 ,	// 24
	reserved01                         :3 ,	// reserved
	manual_cnt_h_value_en              :1 ,	// 28
	manual_cnt_v_value_en              :1 ,	// 29
	reserved02                         :1 ,	// reserved
	update_force                       :1 ;	// 31
}PE_O20_VCP_SG_MVC_CTRL_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c524L vcp_sg_mvc_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_h_dly                         :16,	// 15:0
	sync_v_dly                         :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c528L vcp_sg_mvc_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	manual_cnt_h_value                 :16,	// 15:0
	manual_cnt_v_value                 :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c52cL vcp_sg_mvc_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_ha_delay                      :15,	// 14:0
	auto_general_en                    :1 ,	// 15
	auto_va_delay                      :15,	// 30:16
	auto_seamless                      :1 ;	// 31
}PE_O20_VCP_SG_MVC_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c530L vcp_sg_mvc_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	auto_hs_delay                      :15,	// 14:0
	auto_general_en                    :1 ,	// 15
	auto_vs_delay                      :15,	// 30:16
	auto_seamless                      :1 ;	// 31
}PE_O20_VCP_SG_MVC_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c534L vcp_sg_mvc_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 31:0
}PE_O20_VCP_SG_MVC_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c538L mon_vcp_u0y_pic_init_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0y_pic_init_hpos              :16,	// 15:0
	vcp_u0y_pic_init_vpos              :16;	// 31:16
}PE_O20_MON_VCP_U0Y_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c53cL mon_vcp_u0y_pic_start_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0y_pic_start_hpos             :16,	// 15:0
	vcp_u0y_pic_start_vpos             :16;	// 31:16
}PE_O20_MON_VCP_U0Y_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c540L mon_vcp_u0c_pic_init_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0c_pic_init_hpos              :16,	// 15:0
	vcp_u0c_pic_init_vpos              :16;	// 31:16
}PE_O20_MON_VCP_U0C_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c544L mon_vcp_u0c_pic_start_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u0c_pic_start_hpos             :16,	// 15:0
	vcp_u0c_pic_start_vpos             :16;	// 31:16
}PE_O20_MON_VCP_U0C_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c548L mon_vcp_u1y_pic_init_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1y_pic_init_hpos              :16,	// 15:0
	vcp_u1y_pic_init_vpos              :16;	// 31:16
}PE_O20_MON_VCP_U1Y_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c54cL mon_vcp_u1y_pic_start_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1y_pic_start_hpos             :16,	// 15:0
	vcp_u1y_pic_start_vpos             :16;	// 31:16
}PE_O20_MON_VCP_U1Y_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c550L mon_vcp_u1c_pic_init_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1c_pic_init_hpos              :16,	// 15:0
	vcp_u1c_pic_init_vpos              :16;	// 31:16
}PE_O20_MON_VCP_U1C_PIC_INIT_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c554L mon_vcp_u1c_pic_start_pos                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_u1c_pic_start_hpos             :16,	// 15:0
	vcp_u1c_pic_start_vpos             :16;	// 31:16
}PE_O20_MON_VCP_U1C_PIC_START_POS_T;
/*-----------------------------------------------------------------------------
                             0xc900c5b8L vcp_wcp_m_disp_size                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	pg1ch_win_o_size_y                 :14,	// 13:0
	reserved01                         :2 ,	// reserved
	pg1ch_win_o_size_x                 :13;	// 28:16
}PE_O20_VCP_WCP_M_DISP_SIZE_T;
/*-----------------------------------------------------------------------------
                             0xc900c5bcL vcp_wcp_m_pg_pat_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	lattice_pat_en                     :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	ramp_pat_en                        :2 ,	// 5:4
	mpg_o_color_sel                    :2 ,	// 7:6
	border_sel                         :4 ,	// 11:8
	reserved02                         :3 ,	// reserved
	status_bar_en                      :1 ,	// 15
	reserved03                         :4 ,	// reserved
	status0_00_src_sel                 :2 ,	// 21:20
	status0_01_src_sel                 :2 ,	// 23:22
	status0_02_src_sel                 :2 ,	// 25:24
	status0_03_src_sel                 :2 ,	// 27:26
	cg_disable                         :1 ,	// 28
	reserved04                         :2 ,	// reserved
	mean_fil_en                        :1 ;	// 31
}PE_O20_VCP_WCP_M_PG_PAT_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c5c8L vcp_wcp_m_pixel_read_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rd_pel_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rd_pel_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rd_pel_pat_en                      :1 ;	// 31
}PE_O20_VCP_WCP_M_PIXEL_READ_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c5ccL vcp_wcp_m_pixel_read_ctrl_aux                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rd_pel_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rd_pel_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rd_pel_pat_en                      :1 ;	// 31
}PE_O20_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T;
/*-----------------------------------------------------------------------------
                             0xc900c5d0L vcp_wcp_m_line_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	even_line_cr                       :8 ,	// 7:0
	even_line_cb                       :8 ,	// 15:8
	even_line_y                        :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	even_line_pat_en                   :1 ;	// 31
}PE_O20_VCP_WCP_M_LINE_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c5d4L vcp_wcp_m_line_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	odd_line_cr                        :8 ,	// 7:0
	odd_line_cb                        :8 ,	// 15:8
	odd_line_y                         :8 ,	// 23:16
	reserved01                         :7 ,	// reserved
	odd_line_pat_en                    :1 ;	// 31
}PE_O20_VCP_WCP_M_LINE_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e0L vcp_wcp_m_rec0_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec0_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec0_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec0_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC0_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e4L vcp_wcp_m_rec0_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec0_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec0_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec0_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC0_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c5e8L vcp_wcp_m_rec1_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec1_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec1_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec1_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC1_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c5ecL vcp_wcp_m_rec1_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec1_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec1_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec1_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC1_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f0L vcp_wcp_m_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	repeat_odd_1st_pix_y               :1 ,	// 0 
	repeat_even_1st_pix_y              :1 ,	// 1 
	repeat_odd_end_pix_y               :1 ,	// 2 
	repeat_even_end_pix_y              :1 ,	// 3 
	repeat_odd_1st_pix_c               :1 ,	// 4 
	repeat_even_1st_pix_c              :1 ,	// 5 
	repeat_odd_end_pix_c               :1 ,	// 6 
	repeat_even_end_pix_c              :1 ,	// 7 
	reserved01                         :16,	// reserved
	compare_lr_diff_sel                :2 ,	// 25:24
	compare_lr_sync_sel                :1 ,	// 26
	compare_lr_mark_org_nac            :1 ,	// 27
	reserved02                         :3 ,	// reserved
	compare_lr_en                      :1 ;	// 31
}PE_O20_VCP_WCP_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f4L vcp_wcp_m_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	compare_lr_th_c                    :8 ,	// 7:0
	compare_lr_th_y                    :8 ;	// 15:8
}PE_O20_VCP_WCP_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c5f8L vcp_wcp_m_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_nac_cr                         :4 ,	// 3:0
	clr_nac_cb                         :4 ,	// 7:4
	clr_nac_y                          :8 ,	// 15:8
	clr_bdr_cr                         :4 ,	// 19:16
	clr_bdr_cb                         :4 ,	// 23:20
	clr_bdr_y                          :8 ;	// 31:24
}PE_O20_VCP_WCP_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c5fcL vcp_wcp_m_ctrl_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w1_clr_dark_cr                     :4 ,	// 3:0
	w1_clr_dark_cb                     :4 ,	// 7:4
	w1_clr_dark_y                      :8 ,	// 15:8
	w0_clr_dark_cr                     :4 ,	// 19:16
	w0_clr_dark_cb                     :4 ,	// 23:20
	w0_clr_dark_y                      :8 ;	// 31:24
}PE_O20_VCP_WCP_M_CTRL_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c604L vcp_wcp_m_ctrl_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_imux_ctrl                   :3 ,	// 2:0
	set_w0_dark_en                     :1 ,	// 3 
	set_w1_imux_ctrl                   :3 ,	// 6:4
	set_w1_dark_en                     :1 ,	// 7 
	cg_disable                         :1 ,	// 8 
	reserved01                         :7 ,	// reserved
	set_lparity_w0_imux_en             :1 ,	// 16
	set_lparity_w0_imux                :1 ,	// 17
	reserved02                         :2 ,	// reserved
	set_lparity_w1_imux_en             :1 ,	// 20
	set_lparity_w1_imux                :1 ,	// 21
	reserved03                         :2 ,	// reserved
	set_lparity_sync_c                 :3 ,	// 26:24
	reserved04                         :1 ,	// reserved
	set_lparity_sync_y                 :3 ;	// 30:28
}PE_O20_VCP_WCP_M_CTRL_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c608L vcp_wcp_m_ctrl_6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_a0_c_imux_ctrl                 :3 ,	// 2:0
	set_a0_c_constant_en               :1 ,	// 3 
	set_a1_c_imux_ctrl                 :3 ,	// 6:4
	set_a1_c_constant_en               :1 ,	// 7 
	reserved01                         :8 ,	// reserved
	set_a0_y_imux_ctrl                 :3 ,	// 18:16
	set_a0_y_constant_en               :1 ,	// 19
	set_a1_y_imux_ctrl                 :3 ,	// 22:20
	set_a1_y_constant_en               :1 ;	// 23
}PE_O20_VCP_WCP_M_CTRL_6_T;
/*-----------------------------------------------------------------------------
                             0xc900c60cL vcp_wcp_m_ctrl_7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_w0_abr_en                      :2 ,	// 1:0
	set_w1_abr_en                      :2 ,	// 3:2
	reserved01                         :4 ,	// reserved
	set_w0_awb_cr                      :1 ,	// 8 
	set_w0_awb_cb                      :1 ,	// 9 
	set_w0_awb_y                       :1 ,	// 10
	reserved02                         :1 ,	// reserved
	set_w1_awb_cr                      :1 ,	// 12
	set_w1_awb_cb                      :1 ,	// 13
	set_w1_awb_y                       :1 ,	// 14
	reserved03                         :8 ,	// reserved
	w1_clr_alpha_nac_en                :1 ,	// 23
	w1_clr_alpha_nac                   :8 ;	// 31:24
}PE_O20_VCP_WCP_M_CTRL_7_T;
/*-----------------------------------------------------------------------------
                             0xc900c610L vcp_wcp_m_ctrl_8                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	w0_clr_alpha                       :8 ,	// 7:0
	w1_clr_alpha                       :8 ;	// 15:8
}PE_O20_VCP_WCP_M_CTRL_8_T;
/*-----------------------------------------------------------------------------
                             0xc900c614L vcp_wcp_m_ctrl_9                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_ha_o_mux_ctrl                  :4 ,	// 3:0
	set_va_o_mux_ctrl                  :4 ,	// 7:4
	set_de_o_mux_ctrl                  :4 ;	// 11:8
}PE_O20_VCP_WCP_M_CTRL_9_T;
/*-----------------------------------------------------------------------------
                             0xc900c618L vcp_wcp_m_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_m_wcp           :4 ,	// 3:0
	set_pic_start_y_mux_m_wcp          :4 ,	// 7:4
	set_pic_init_c_mux_m_wcp           :4 ,	// 11:8
	set_pic_start_c_mux_m_wcp          :4 ;	// 15:12
}PE_O20_VCP_WCP_M_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900c650L vcp_wcp_m_pixel_read_data_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	// 7:0
	msb8_rd_pel_cb                     :8 ,	// 15:8
	msb8_rd_pel_y                      :8 ,	// 23:16
	lsb2_rd_pel_cr                     :2 ,	// 25:24
	lsb2_rd_pel_cb                     :2 ,	// 27:26
	lsb2_rd_pel_y                      :2 ;	// 29:28
}PE_O20_VCP_WCP_M_PIXEL_READ_DATA_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c654L vcp_wcp_m_pixel_read_data_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	// reserved
	msb8_rd_pel_cb                     :8 ,	// 15:8
	msb8_rd_pel_y                      :8 ,	// 23:16
	lsb2_rd_pel_cr                     :2 ,	// 25:24
	lsb2_rd_pel_cb                     :2 ,	// 27:26
	lsb2_rd_pel_y                      :2 ;	// 29:28
}PE_O20_VCP_WCP_M_PIXEL_READ_DATA_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c658L vcp_wcp_m_pixel_read_data_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	// 7:0
	msb8_rd_pel_cb                     :8 ,	// 15:8
	msb8_rd_pel_y                      :8 ,	// 23:16
	lsb2_rd_pel_cr                     :2 ,	// 25:24
	lsb2_rd_pel_cb                     :2 ,	// 27:26
	lsb2_rd_pel_y                      :2 ;	// 29:28
}PE_O20_VCP_WCP_M_PIXEL_READ_DATA_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c65cL vcp_wcp_m_pixel_read_data_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	msb8_rd_pel_cr                     :8 ,	// 7:0
	msb8_rd_pel_cb                     :8 ,	// 15:8
	msb8_rd_pel_y                      :8 ,	// 23:16
	lsb2_rd_pel_cr                     :2 ,	// 25:24
	lsb2_rd_pel_cb                     :2 ,	// 27:26
	lsb2_rd_pel_y                      :2 ;	// 29:28
}PE_O20_VCP_WCP_M_PIXEL_READ_DATA_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c660L vcp_sg_bdr_v0_param_pos_m                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0_auto                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0_auto                    :13;	// 28:16
}PE_O20_VCP_SG_BDR_V0_PARAM_POS_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c664L vcp_sg_bdr_v0_param_size_m                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_size_y_auto                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_size_x_auto                    :13,	// 28:16
	reserved02                         :1 ,	// reserved
	win_enable_4ch_auto                :1 ,	// 30
	win_enable_auto                    :1 ;	// 31
}PE_O20_VCP_SG_BDR_V0_PARAM_SIZE_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c668L vcp_sg_bdr_v1_param_pos_m                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0_auto                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0_auto                    :13;	// 28:16
}PE_O20_VCP_SG_BDR_V1_PARAM_POS_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c66cL vcp_sg_bdr_v1_param_size_m                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_size_y_auto                    :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_size_x_auto                    :13,	// 28:16
	reserved02                         :1 ,	// reserved
	win_enable_4ch_auto                :1 ,	// 30
	win_enable_auto                    :1 ;	// 31
}PE_O20_VCP_SG_BDR_V1_PARAM_SIZE_M_T;
/*-----------------------------------------------------------------------------
                             0xc900c680L vcp_sg_bdr_v0_0_m_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V0_0_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c684L vcp_sg_bdr_v0_0_m_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x1                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V0_0_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c688L vcp_sg_bdr_v0_0_m_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	// 0 
	sync_ha_sub_en                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	num_ch                             :2 ,	// 5:4
	reserved02                         :10,	// reserved
	win_border_width_right             :4 ,	// 19:16
	win_border_width_left              :4 ,	// 23:20
	win_border_width_down              :4 ,	// 27:24
	win_border_width_up                :4 ;	// 31:28
}PE_O20_VCP_SG_BDR_V0_0_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c690L vcp_sg_bdr_v0_1_m_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V0_1_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c694L vcp_sg_bdr_v0_1_m_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x1                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V0_1_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c698L vcp_sg_bdr_v0_1_m_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	// 0 
	sync_ha_sub_en                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	num_ch                             :2 ,	// 5:4
	reserved02                         :10,	// reserved
	win_border_width_right             :4 ,	// 19:16
	win_border_width_left              :4 ,	// 23:20
	win_border_width_down              :4 ,	// 27:24
	win_border_width_up                :4 ;	// 31:28
}PE_O20_VCP_SG_BDR_V0_1_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c0L vcp_sg_bdr_v1_0_m_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V1_0_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c4L vcp_sg_bdr_v1_0_m_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x1                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V1_0_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c6c8L vcp_sg_bdr_v1_0_m_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	// 0 
	sync_ha_sub_en                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	num_ch                             :2 ,	// 5:4
	reserved02                         :10,	// reserved
	win_border_width_right             :4 ,	// 19:16
	win_border_width_left              :4 ,	// 23:20
	win_border_width_down              :4 ,	// 27:24
	win_border_width_up                :4 ;	// 31:28
}PE_O20_VCP_SG_BDR_V1_0_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d0L vcp_sg_bdr_v1_1_m_ctrl_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y0                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x0                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V1_1_M_CTRL_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d4L vcp_sg_bdr_v1_1_m_ctrl_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	win_pos_y1                         :14,	// 13:0
	reserved01                         :2 ,	// reserved
	win_pos_x1                         :13;	// 28:16
}PE_O20_VCP_SG_BDR_V1_1_M_CTRL_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c6d8L vcp_sg_bdr_v1_1_m_ctrl_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	sync_ha_sub_sel                    :1 ,	// 0 
	sync_ha_sub_en                     :1 ,	// 1 
	reserved01                         :2 ,	// reserved
	num_ch                             :2 ,	// 5:4
	reserved02                         :10,	// reserved
	win_border_width_right             :4 ,	// 19:16
	win_border_width_left              :4 ,	// 23:20
	win_border_width_down              :4 ,	// 27:24
	win_border_width_up                :4 ;	// 31:28
}PE_O20_VCP_SG_BDR_V1_1_M_CTRL_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c780L vcp_wcp_m_rec5_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec5_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec5_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec5_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC5_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c784L vcp_wcp_m_rec5_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec5_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec5_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec5_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC5_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c788L vcp_wcp_m_rec5_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC5_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c78cL vcp_wcp_m_rec6_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec6_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec6_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec6_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC6_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c790L vcp_wcp_m_rec6_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec6_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec6_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec6_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC6_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c794L vcp_wcp_m_rec6_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC6_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c798L vcp_wcp_m_rec7_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec7_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec7_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec7_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC7_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c79cL vcp_wcp_m_rec7_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec7_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec7_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec7_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC7_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a0L vcp_wcp_m_rec7_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC7_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a4L vcp_wcp_m_rec8_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec8_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec8_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec8_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC8_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c7a8L vcp_wcp_m_rec8_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec8_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec8_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec8_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC8_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7acL vcp_wcp_m_rec8_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC8_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b0L vcp_wcp_m_rec9_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec9_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec9_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec9_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC9_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b4L vcp_wcp_m_rec9_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec9_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec9_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec9_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC9_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c7b8L vcp_wcp_m_rec9_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC9_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c7c4L vcp_wcp_ms_ctrl_10                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_pic_init_y_mux_ms_wcp          :4 ,	// 3:0
	set_pic_start_y_mux_ms_wcp         :4 ,	// 7:4
	set_pic_init_c_mux_ms_wcp          :4 ,	// 11:8
	set_pic_start_c_mux_ms_wcp         :4 ;	// 15:12
}PE_O20_VCP_WCP_MS_CTRL_10_T;
/*-----------------------------------------------------------------------------
                             0xc900c800L vcp_wcp_alpha_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	set_region_m_y_sync_sel            :2 ,	// 5:4
	set_region_m_c_sync_sel            :2 ,	// 7:6
	reserved02                         :23,	// reserved
	alpha_gen_disable                  :1 ;	// 31
}PE_O20_VCP_WCP_ALPHA_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c804L vcp_wcp_alpha_gen_y_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_vsize                          :16,	// 15:0
	set_hsize                          :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_Y_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c808L vcp_wcp_alpha_gen_y_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	region_shape                       :2 ,	// 1:0
	alpha_inversion_y                  :1 ,	// 2 
	rm_op_mode                         :2 ,	// 4:3
	rm_enable                          :1 ,	// 5 
	ellipse_ez_set                     :1 ,	// 6 
	rm_yc_same_align                   :1 ,	// 7 
	reserved01                         :8 ,	// reserved
	alpha_1                            :8 ,	// 23:16
	alpha_0                            :8 ;	// 31:24
}PE_O20_VCP_WCP_ALPHA_GEN_Y_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c80cL vcp_wcp_alpha_gen_y_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_a_q                             :16,	// 15:0
	x0_p                               :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_Y_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c810L vcp_wcp_alpha_gen_y_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1_y1_tx_pp;	// 31:0
}PE_O20_VCP_WCP_ALPHA_GEN_Y_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c814L vcp_wcp_alpha_gen_y_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	b_c_qq;	// 31:0
}PE_O20_VCP_WCP_ALPHA_GEN_Y_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c818L vcp_wcp_alpha_gen_y_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dy                                 :16,	// 15:0
	dx                                 :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_Y_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c81cL vcp_wcp_alpha_gen_c_0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	set_vsize                          :16,	// 15:0
	set_hsize                          :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_C_0_T;
/*-----------------------------------------------------------------------------
                             0xc900c820L vcp_wcp_alpha_gen_c_1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	region_shape                       :2 ,	// 1:0
	alpha_inversion_c                  :1 ,	// 2 
	eo_mode_en                         :1 ,	// 3 
	reserved01                         :12,	// reserved
	alpha_1                            :8 ,	// 23:16
	alpha_0                            :8 ;	// 31:24
}PE_O20_VCP_WCP_ALPHA_GEN_C_1_T;
/*-----------------------------------------------------------------------------
                             0xc900c824L vcp_wcp_alpha_gen_c_2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	y0_a_q                             :16,	// 15:0
	x0_p                               :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_C_2_T;
/*-----------------------------------------------------------------------------
                             0xc900c828L vcp_wcp_alpha_gen_c_3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	x1_y1_tx_pp;	// 31:0
}PE_O20_VCP_WCP_ALPHA_GEN_C_3_T;
/*-----------------------------------------------------------------------------
                             0xc900c82cL vcp_wcp_alpha_gen_c_4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	b_c_qq;	// 31:0
}PE_O20_VCP_WCP_ALPHA_GEN_C_4_T;
/*-----------------------------------------------------------------------------
                             0xc900c830L vcp_wcp_alpha_gen_c_5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	dy                                 :16,	// 15:0
	dx                                 :16;	// 31:16
}PE_O20_VCP_WCP_ALPHA_GEN_C_5_T;
/*-----------------------------------------------------------------------------
                             0xc900c834L vcp_wcp_m_rec2_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec2_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec2_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec2_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC2_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c838L vcp_wcp_m_rec2_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec2_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec2_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec2_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC2_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c83cL vcp_wcp_m_rec3_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec3_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec3_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec3_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC3_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c840L vcp_wcp_m_rec3_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec3_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec3_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec3_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC3_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c844L vcp_wcp_m_rec4_pos_x                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec4_e_pos_x                       :13,	// 12:0
	reserved01                         :3 ,	// reserved
	rec4_s_pos_x                       :13,	// 28:16
	reserved02                         :2 ,	// reserved
	rec4_en                            :1 ;	// 31
}PE_O20_VCP_WCP_M_REC4_POS_X_T;
/*-----------------------------------------------------------------------------
                             0xc900c848L vcp_wcp_m_rec4_pos_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	rec4_e_pos_y                       :14,	// 13:0
	reserved01                         :2 ,	// reserved
	rec4_s_pos_y                       :14,	// 29:16
	reserved02                         :1 ,	// reserved
	rec4_fill_en                       :1 ;	// 31
}PE_O20_VCP_WCP_M_REC4_POS_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c84cL vcp_wcp_m_rec0_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC0_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c850L vcp_wcp_m_rec1_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC1_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c854L vcp_wcp_m_rec2_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC2_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c858L vcp_wcp_m_rec3_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC3_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c85cL vcp_wcp_m_rec4_clr                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	clr_cr                             :8 ,	// 7:0
	clr_cb                             :8 ,	// 15:8
	clr_y                              :8 ;	// 23:16
}PE_O20_VCP_WCP_M_REC4_CLR_T;
/*-----------------------------------------------------------------------------
                             0xc900c860L vcp_vsp_u0_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	// 0 
	reserved01                         :3 ,	// reserved
	cg_disable                         :1 ,	// 4 
	reserved02                         :3 ,	// reserved
	center_position                    :8 ,	// 15:8
	contrast                           :10;	// 25:16
}PE_O20_VCP_VSP_U0_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900c864L vcp_vsp_u0_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	saturation                         :8 ,	// 15:8
	brightness                         :10;	// 25:16
}PE_O20_VCP_VSP_U0_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900c868L vcp_vsp_u1_ctrl_00                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	enable                             :1 ,	// 0 
	reserved01                         :7 ,	// reserved
	center_position                    :8 ,	// 15:8
	contrast                           :10;	// 25:16
}PE_O20_VCP_VSP_U1_CTRL_00_T;
/*-----------------------------------------------------------------------------
                             0xc900c86cL vcp_vsp_u1_ctrl_01                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :8 ,	// reserved
	saturation                         :8 ,	// 15:8
	brightness                         :10;	// 25:16
}PE_O20_VCP_VSP_U1_CTRL_01_T;
/*-----------------------------------------------------------------------------
                             0xc900c870L vcp_crc_ctrl                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	crc_enable                         :1 ,	// 0 
	crc_reset                          :1 ,	// 1 
	reserved01                         :1 ,	// reserved
	auto_reset_disable                 :1 ,	// 3 
	vs_level                           :1 ,	// 4 
	hs_level                           :1 ,	// 5 
	vs_mask                            :1 ,	// 6 
	hs_mask                            :1 ;	// 7 
}PE_O20_VCP_CRC_CTRL_T;
/*-----------------------------------------------------------------------------
                             0xc900c874L vcp_crc_data_mask0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_CRC_DATA_MASK0_T;
/*-----------------------------------------------------------------------------
                             0xc900c878L vcp_crc_data_mask1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_CRC_DATA_MASK1_T;
/*-----------------------------------------------------------------------------
                             0xc900c884L vcp_crc_out0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_CRC_OUT0_T;
/*-----------------------------------------------------------------------------
                             0xc900c888L vcp_crc_out1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved;	// 0:31
}PE_O20_VCP_CRC_OUT1_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a0L vcp_sg_mvy_ctrl_a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	// 15:0
	v_cnt                              :16;	// 31:16
}PE_O20_VCP_SG_MVY_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a4L vcp_sg_mvc_ctrl_a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	// 15:0
	v_cnt                              :16;	// 31:16
}PE_O20_VCP_SG_MVC_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8a8L vcp_sg_svy_ctrl_a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	// 15:0
	v_cnt                              :16;	// 31:16
}PE_O20_VCP_SG_SVY_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c8acL vcp_sg_svc_ctrl_a                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	h_cnt                              :16,	// 15:0
	v_cnt                              :16;	// 31:16
}PE_O20_VCP_SG_SVC_CTRL_A_T;
/*-----------------------------------------------------------------------------
                             0xc900c900L vcp_disp_intr_mask                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_mask           :1 ,	// 0 
	vcp_mv_y_disp_intr1_mask           :1 ,	// 1 
	vcp_mv_y_w0_intr_mask              :1 ,	// 2 
	vcp_mv_y_w1_intr_mask              :1 ,	// 3 
	reserved01                         :2 ,	// reserved
	vcp_sv_y_disp_intr0_mask           :1 ,	// 6 
	vcp_sv_y_disp_intr1_mask           :1 ,	// 7 
	vcp_sv_y_w0_intr_mask              :1 ,	// 8 
	reserved02                         :3 ,	// reserved
	vcp_ms_y_disp_intr_mask            :1 ,	// 12
	reserved03                         :3 ,	// reserved
	vcp_mv_c_disp_intr0_mask           :1 ,	// 16
	vcp_mv_c_disp_intr1_mask           :1 ,	// 17
	vcp_mv_c_w0_intr_mask              :1 ,	// 18
	vcp_mv_c_w1_intr_mask              :1 ,	// 19
	reserved04                         :2 ,	// reserved
	vcp_sv_c_disp_intr0_mask           :1 ,	// 22
	vcp_sv_c_disp_intr1_mask           :1 ,	// 23
	vcp_sv_c_w0_intr_mask              :1 ;	// 24
}PE_O20_VCP_DISP_INTR_MASK_T;
/*-----------------------------------------------------------------------------
                             0xc900c904L vcp_disp_intr_clear                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_clear          :1 ,	// 0 
	vcp_mv_y_disp_intr1_clear          :1 ,	// 1 
	vcp_mv_y_w0_intr_clear             :1 ,	// 2 
	vcp_mv_y_w1_intr_clear             :1 ,	// 3 
	reserved01                         :2 ,	// reserved
	vcp_sv_y_disp_intr0_clear          :1 ,	// 6 
	vcp_sv_y_disp_intr1_clear          :1 ,	// 7 
	vcp_sv_y_w0_intr_clear             :1 ,	// 8 
	reserved02                         :3 ,	// reserved
	vcp_ms_y_disp_intr_clear           :1 ,	// 12
	reserved03                         :3 ,	// reserved
	vcp_mv_c_disp_intr0_clear          :1 ,	// 16
	vcp_mv_c_disp_intr1_clear          :1 ,	// 17
	vcp_mv_c_w0_intr_clear             :1 ,	// 18
	vcp_mv_c_w1_intr_clear             :1 ,	// 19
	reserved04                         :2 ,	// reserved
	vcp_sv_c_disp_intr0_clear          :1 ,	// 22
	vcp_sv_c_disp_intr1_clear          :1 ,	// 23
	vcp_sv_c_w0_intr_clear             :1 ;	// 24
}PE_O20_VCP_DISP_INTR_CLEAR_T;
/*-----------------------------------------------------------------------------
                             0xc900c908L vcp_disp_intr_status                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_y_disp_intr0_status         :1 ,	// 0 
	vcp_mv_y_disp_intr1_status         :1 ,	// 1 
	vcp_mv_y_w0_intr_status            :1 ,	// 2 
	vcp_mv_y_w1_intr_status            :1 ,	// 3 
	reserved01                         :2 ,	// reserved
	vcp_sv_y_disp_intr0_status         :1 ,	// 6 
	vcp_sv_y_disp_intr1_status         :1 ,	// 7 
	vcp_sv_y_w0_intr_status            :1 ,	// 8 
	reserved02                         :3 ,	// reserved
	vcp_ms_y_disp_intr_status          :1 ,	// 12
	reserved03                         :3 ,	// reserved
	vcp_mv_c_disp_intr0_status         :1 ,	// 16
	vcp_mv_c_disp_intr1_status         :1 ,	// 17
	vcp_mv_c_w0_intr_status            :1 ,	// 18
	vcp_mv_c_w1_intr_status            :1 ,	// 19
	reserved04                         :2 ,	// reserved
	vcp_sv_c_disp_intr0_status         :1 ,	// 22
	vcp_sv_c_disp_intr1_status         :1 ,	// 23
	vcp_sv_c_w0_intr_status            :1 ;	// 24
}PE_O20_VCP_DISP_INTR_STATUS_T;
/*-----------------------------------------------------------------------------
                             0xc900c90cL vcp_disp_intr0_pos_mv_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr0_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_mv_disp_intr0_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR0_POS_MV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c910L vcp_disp_intr1_pos_mv_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr1_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_mv_disp_intr1_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR1_POS_MV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c914L vcp_disp_intr0_pos_mv_c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr0_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_mv_disp_intr0_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR0_POS_MV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c918L vcp_disp_intr1_pos_mv_c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_mv_disp_intr1_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_mv_disp_intr1_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR1_POS_MV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c91cL vcp_disp_intr0_pos_sv_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr0_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_sv_disp_intr0_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR0_POS_SV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c920L vcp_disp_intr1_pos_sv_y                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr1_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_sv_disp_intr1_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR1_POS_SV_Y_T;
/*-----------------------------------------------------------------------------
                             0xc900c924L vcp_disp_intr0_pos_sv_c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr0_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_sv_disp_intr0_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR0_POS_SV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c928L vcp_disp_intr1_pos_sv_c                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_sv_disp_intr1_pos_x            :13,	// 12:0
	reserved01                         :3 ,	// reserved
	vcp_sv_disp_intr1_pos_y            :13;	// 28:16
}PE_O20_VCP_DISP_INTR1_POS_SV_C_T;
/*-----------------------------------------------------------------------------
                             0xc900c92cL vcp_disp_intr_src_sel                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_intr_mv_y_v_src                :1 ,	// 0 
	vcp_intr_mv_y_h_src                :1 ,	// 1 
	reserved01                         :1 ,	// reserved
	vcp_intr_mv_y_enable               :1 ,	// 3 
	vcp_intr_mv_c_v_src                :1 ,	// 4 
	vcp_intr_mv_c_h_src                :1 ,	// 5 
	reserved02                         :1 ,	// reserved
	vcp_intr_mv_c_enable               :1 ,	// 7 
	vcp_intr_sv_y_v_src                :1 ,	// 8 
	vcp_intr_sv_y_h_src                :1 ,	// 9 
	reserved03                         :1 ,	// reserved
	vcp_intr_sv_y_enable               :1 ,	// 11
	vcp_intr_sv_c_v_src                :1 ,	// 12
	vcp_intr_sv_c_h_src                :1 ,	// 13
	reserved04                         :1 ,	// reserved
	vcp_intr_sv_c_enable               :1 ;	// 15
}PE_O20_VCP_DISP_INTR_SRC_SEL_T;
/*-----------------------------------------------------------------------------
                             0xc900c930L vcp_u0_csc_ctrl7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	reserved01                         :4 ,	// reserved
	vcp_422_mean_filter_en             :1 ,	// 4 
	vcp_maunal_size                    :1 ,	// 5 
	reserved02                         :2 ,	// reserved
	vcp_422_mean_filter_last_pixel     :13;	// 20:8
}PE_O20_VCP_U0_CSC_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc900c934L csc_ctrl0                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_coefficient1               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	vcp_csc_coefficient0               :15;	// 30:16
}PE_O20_VCP_CSC_CTRL0_T;
/*-----------------------------------------------------------------------------
                             0xc900c938L csc_ctrl1                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_coefficient3               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	vcp_csc_coefficient2               :15;	// 30:16
}PE_O20_VCP_CSC_CTRL1_T;
/*-----------------------------------------------------------------------------
                             0xc900c93cL csc_ctrl2                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_coefficient5               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	vcp_csc_coefficient4               :15;	// 30:16
}PE_O20_VCP_CSC_CTRL2_T;
/*-----------------------------------------------------------------------------
                             0xc900c940L csc_ctrl3                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_coefficient7               :15,	// 14:0
	reserved01                         :1 ,	// reserved
	vcp_csc_coefficient6               :15;	// 30:16
}PE_O20_VCP_CSC_CTRL3_T;
/*-----------------------------------------------------------------------------
                             0xc900c944L csc_ctrl4                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_offset0                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	vcp_csc_coefficient8               :15;	// 30:16
}PE_O20_VCP_CSC_CTRL4_T;
/*-----------------------------------------------------------------------------
                             0xc900c948L csc_ctrl5                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_offset2                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	vcp_csc_offset1                    :11;	// 26:16
}PE_O20_VCP_CSC_CTRL5_T;
/*-----------------------------------------------------------------------------
                             0xc900c94cL csc_ctrl6                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_offset4                    :11,	// 10:0
	reserved01                         :5 ,	// reserved
	vcp_csc_offset3                    :11;	// 26:16
}PE_O20_VCP_CSC_CTRL6_T;
/*-----------------------------------------------------------------------------
                             0xc900c950L vcp_u1_csc_ctrl7                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	vcp_csc_coeff_load                 :1 ,	// 0 
	vcp_csc_en                         :1 ,	// 1 
	vcp_csc_pcg_off                    :1 ,	// 2 
	reserved01                         :1 ,	// reserved
	vcp_422_mean_filter_en             :1 ,	// 4 
	vcp_maunal_size                    :1 ,	// 5 
	reserved02                         :2 ,	// reserved
	vcp_422_mean_filter_last_pixel     :13,	// 20:8
	vcp_csc_offset5                    :11;	// 31:21
}PE_O20_VCP_U1_CSC_CTRL7_T;
/*-----------------------------------------------------------------------------
                             0xc900c954L vcp_active_line_cnt                             
-----------------------------------------------------------------------------*/
typedef struct
{
	UINT32
	                                   :1 ,	// 0 
	vcp_active_line_cnt_en             :1 ,	// 1 
	vcp_cnt_ref                        :15;	// 16:2
}PE_O20_VCP_ACTIVE_LINE_CNT_T;


typedef struct
{ 
	PE_O20_VCP_DISP_CTRL0_T                           vcp_disp_ctrl0;	//0x0400
	PE_O20_VCP_DISP_CTRL1_T                           vcp_disp_ctrl1;	//0x0404
	PE_O20_VCP_DISP_CTRL2_T                           vcp_disp_ctrl2;	//0x0408
	PE_O20_VCP_DISP_CTRL3_T                           vcp_disp_ctrl3;	//0x040C
	PE_O20_VCP_CDC_MV_SYNC_CTRL_T                     vcp_cdc_mv_sync_ctrl;	//0x0410
	PE_O20_VCP_CDC_MV_RST_CTRL_T                      vcp_cdc_mv_rst_ctrl;	//0x0414
	UINT32                                            reserved00[2];	//0x0418-0x041C
	PE_O20_VCP_U0_WIN_O_POS_T                         vcp_u0_win_o_pos;	//0x0420
	PE_O20_VCP_U0_WIN_O_SIZE_T                        vcp_u0_win_o_size;	//0x0424
	PE_O20_VCP_U0_PG_PAT_CTRL_T                       vcp_u0_pg_pat_ctrl;	//0x0428
	PE_O20_VCP_U0_PG_PEAK_SIZE_T                      vcp_u0_pg_peak_size;	//0x042C
	PE_O20_VCP_U0_CDC_Y_CTRL0_T                       vcp_u0_cdc_y_ctrl0;	//0x0430
	PE_O20_VCP_U0_CDC_Y_CTRL1_T                       vcp_u0_cdc_y_ctrl1;	//0x0434
	PE_O20_VCP_U0_CDC_Y_CTRL2_T                       vcp_u0_cdc_y_ctrl2;	//0x0438
	PE_O20_VCP_U0_CDC_Y_STATUS_T                      vcp_u0_cdc_y_status;	//0x043C
	PE_O20_VCP_U0_CDC_C_CTRL0_T                       vcp_u0_cdc_c_ctrl0;	//0x0440
	PE_O20_VCP_U0_CDC_C_CTRL1_T                       vcp_u0_cdc_c_ctrl1;	//0x0444
	PE_O20_VCP_U0_CDC_C_CTRL2_T                       vcp_u0_cdc_c_ctrl2;	//0x0448
	PE_O20_VCP_U0_CDC_C_STATUS_T                      vcp_u0_cdc_c_status;	//0x044C
	PE_O20_VCP_U1_WIN_O_POS_T                         vcp_u1_win_o_pos;	//0x0450
	PE_O20_VCP_U1_WIN_O_SIZE_T                        vcp_u1_win_o_size;	//0x0454
	PE_O20_VCP_U1_PG_PAT_CTRL_T                       vcp_u1_pg_pat_ctrl;	//0x0458
	PE_O20_VCP_U1_PG_PEAK_SIZE_T                      vcp_u1_pg_peak_size;	//0x045C
	PE_O20_VCP_U1_CDC_Y_CTRL0_T                       vcp_u1_cdc_y_ctrl0;	//0x0460
	PE_O20_VCP_U1_CDC_Y_CTRL1_T                       vcp_u1_cdc_y_ctrl1;	//0x0464
	PE_O20_VCP_U1_CDC_Y_CTRL2_T                       vcp_u1_cdc_y_ctrl2;	//0x0468
	PE_O20_VCP_U1_CDC_Y_STATUS_T                      vcp_u1_cdc_y_status;	//0x046C
	PE_O20_VCP_U1_CDC_C_CTRL0_T                       vcp_u1_cdc_c_ctrl0;	//0x0470
	PE_O20_VCP_U1_CDC_C_CTRL1_T                       vcp_u1_cdc_c_ctrl1;	//0x0474
	PE_O20_VCP_U1_CDC_C_CTRL2_T                       vcp_u1_cdc_c_ctrl2;	//0x0478
	PE_O20_VCP_U1_CDC_C_STATUS_T                      vcp_u1_cdc_c_status;	//0x047C
	PE_O20_VCP_U0_WIN_O_POS_AUX_T                     vcp_u0_win_o_pos_aux;	//0x0480
	PE_O20_VCP_U0_WIN_O_SIZE_AUX_T                    vcp_u0_win_o_size_aux;	//0x0484
	PE_O20_VCP_U1_WIN_O_POS_AUX_T                     vcp_u1_win_o_pos_aux;	//0x0488
	PE_O20_VCP_U1_WIN_O_SIZE_AUX_T                    vcp_u1_win_o_size_aux;	//0x048C
	UINT32                                            reserved01[20];	//0x0490-0x04DC
	PE_O20_VCP_SG_MVY_CTRL_0_T                        vcp_sg_mvy_ctrl_0;	//0x04E0
	PE_O20_VCP_SG_MVY_CTRL_1_T                        vcp_sg_mvy_ctrl_1;	//0x04E4
	PE_O20_VCP_SG_MVY_CTRL_2_T                        vcp_sg_mvy_ctrl_2;	//0x04E8
	PE_O20_VCP_SG_MVY_CTRL_3_T                        vcp_sg_mvy_ctrl_3;	//0x04EC
	PE_O20_VCP_SG_MVY_CTRL_4_T                        vcp_sg_mvy_ctrl_4;	//0x04F0
	PE_O20_VCP_SG_MVY_CTRL_5_T                        vcp_sg_mvy_ctrl_5;	//0x04F4
	PE_O20_VCP_SG_MVY_CTRL_6_T                        vcp_sg_mvy_ctrl_6;	//0x04F8
	PE_O20_VCP_SG_MVY_CTRL_7_T                        vcp_sg_mvy_ctrl_7;	//0x04FC
	PE_O20_VCP_SG_MVY_CTRL_8_T                        vcp_sg_mvy_ctrl_8;	//0x0500
	PE_O20_VCP_SG_MVY_CTRL_9_T                        vcp_sg_mvy_ctrl_9;	//0x0504
	UINT32                                            reserved02[2];	//0x0508-0x050C
	PE_O20_VCP_SG_MVC_CTRL_0_T                        vcp_sg_mvc_ctrl_0;	//0x0510
	PE_O20_VCP_SG_MVC_CTRL_1_T                        vcp_sg_mvc_ctrl_1;	//0x0514
	PE_O20_VCP_SG_MVC_CTRL_2_T                        vcp_sg_mvc_ctrl_2;	//0x0518
	PE_O20_VCP_SG_MVC_CTRL_3_T                        vcp_sg_mvc_ctrl_3;	//0x051C
	PE_O20_VCP_SG_MVC_CTRL_4_T                        vcp_sg_mvc_ctrl_4;	//0x0520
	PE_O20_VCP_SG_MVC_CTRL_5_T                        vcp_sg_mvc_ctrl_5;	//0x0524
	PE_O20_VCP_SG_MVC_CTRL_6_T                        vcp_sg_mvc_ctrl_6;	//0x0528
	PE_O20_VCP_SG_MVC_CTRL_7_T                        vcp_sg_mvc_ctrl_7;	//0x052C
	PE_O20_VCP_SG_MVC_CTRL_8_T                        vcp_sg_mvc_ctrl_8;	//0x0530
	PE_O20_VCP_SG_MVC_CTRL_9_T                        vcp_sg_mvc_ctrl_9;	//0x0534
	PE_O20_MON_VCP_U0Y_PIC_INIT_POS_T                 mon_vcp_u0y_pic_init_pos;	//0x0538
	PE_O20_MON_VCP_U0Y_PIC_START_POS_T                mon_vcp_u0y_pic_start_pos;	//0x053C
	PE_O20_MON_VCP_U0C_PIC_INIT_POS_T                 mon_vcp_u0c_pic_init_pos;	//0x0540
	PE_O20_MON_VCP_U0C_PIC_START_POS_T                mon_vcp_u0c_pic_start_pos;	//0x0544
	PE_O20_MON_VCP_U1Y_PIC_INIT_POS_T                 mon_vcp_u1y_pic_init_pos;	//0x0548
	PE_O20_MON_VCP_U1Y_PIC_START_POS_T                mon_vcp_u1y_pic_start_pos;	//0x054C
	PE_O20_MON_VCP_U1C_PIC_INIT_POS_T                 mon_vcp_u1c_pic_init_pos;	//0x0550
	PE_O20_MON_VCP_U1C_PIC_START_POS_T                mon_vcp_u1c_pic_start_pos;	//0x0554
	UINT32                                            reserved03[24];	//0x0558-0x05B4
	PE_O20_VCP_WCP_M_DISP_SIZE_T                      vcp_wcp_m_disp_size;	//0x05B8
	PE_O20_VCP_WCP_M_PG_PAT_CTRL_T                    vcp_wcp_m_pg_pat_ctrl;	//0x05BC
	UINT32                                            reserved04[2];	//0x05C0-0x05C4
	PE_O20_VCP_WCP_M_PIXEL_READ_CTRL_T                vcp_wcp_m_pixel_read_ctrl;	//0x05C8
	PE_O20_VCP_WCP_M_PIXEL_READ_CTRL_AUX_T            vcp_wcp_m_pixel_read_ctrl_aux;	//0x05CC
	PE_O20_VCP_WCP_M_LINE_CTRL0_T                     vcp_wcp_m_line_ctrl0;	//0x05D0
	PE_O20_VCP_WCP_M_LINE_CTRL1_T                     vcp_wcp_m_line_ctrl1;	//0x05D4
	UINT32                                            reserved05[2];	//0x05D8-0x05DC
	PE_O20_VCP_WCP_M_REC0_POS_X_T                     vcp_wcp_m_rec0_pos_x;	//0x05E0
	PE_O20_VCP_WCP_M_REC0_POS_Y_T                     vcp_wcp_m_rec0_pos_y;	//0x05E4
	PE_O20_VCP_WCP_M_REC1_POS_X_T                     vcp_wcp_m_rec1_pos_x;	//0x05E8
	PE_O20_VCP_WCP_M_REC1_POS_Y_T                     vcp_wcp_m_rec1_pos_y;	//0x05EC
	PE_O20_VCP_WCP_M_CTRL_0_T                         vcp_wcp_m_ctrl_0;	//0x05F0
	PE_O20_VCP_WCP_M_CTRL_1_T                         vcp_wcp_m_ctrl_1;	//0x05F4
	PE_O20_VCP_WCP_M_CTRL_2_T                         vcp_wcp_m_ctrl_2;	//0x05F8
	PE_O20_VCP_WCP_M_CTRL_3_T                         vcp_wcp_m_ctrl_3;	//0x05FC
	UINT32                                            reserved06;	//0x0600-0x0600
	PE_O20_VCP_WCP_M_CTRL_5_T                         vcp_wcp_m_ctrl_5;	//0x0604
	PE_O20_VCP_WCP_M_CTRL_6_T                         vcp_wcp_m_ctrl_6;	//0x0608
	PE_O20_VCP_WCP_M_CTRL_7_T                         vcp_wcp_m_ctrl_7;	//0x060C
	PE_O20_VCP_WCP_M_CTRL_8_T                         vcp_wcp_m_ctrl_8;	//0x0610
	PE_O20_VCP_WCP_M_CTRL_9_T                         vcp_wcp_m_ctrl_9;	//0x0614
	PE_O20_VCP_WCP_M_CTRL_10_T                        vcp_wcp_m_ctrl_10;	//0x0618
	UINT32                                            reserved07[13];	//0x061C-0x064C
	PE_O20_VCP_WCP_M_PIXEL_READ_DATA_0_T              vcp_wcp_m_pixel_read_data_0;	//0x0650
	PE_O20_VCP_WCP_M_PIXEL_READ_DATA_1_T              vcp_wcp_m_pixel_read_data_1;	//0x0654
	PE_O20_VCP_WCP_M_PIXEL_READ_DATA_2_T              vcp_wcp_m_pixel_read_data_2;	//0x0658
	PE_O20_VCP_WCP_M_PIXEL_READ_DATA_3_T              vcp_wcp_m_pixel_read_data_3;	//0x065C
	PE_O20_VCP_SG_BDR_V0_PARAM_POS_M_T                vcp_sg_bdr_v0_param_pos_m;	//0x0660
	PE_O20_VCP_SG_BDR_V0_PARAM_SIZE_M_T               vcp_sg_bdr_v0_param_size_m;	//0x0664
	PE_O20_VCP_SG_BDR_V1_PARAM_POS_M_T                vcp_sg_bdr_v1_param_pos_m;	//0x0668
	PE_O20_VCP_SG_BDR_V1_PARAM_SIZE_M_T               vcp_sg_bdr_v1_param_size_m;	//0x066C
	UINT32                                            reserved08[4];	//0x0670-0x067C
	PE_O20_VCP_SG_BDR_V0_0_M_CTRL_0_T                 vcp_sg_bdr_v0_0_m_ctrl_0;	//0x0680
	PE_O20_VCP_SG_BDR_V0_0_M_CTRL_1_T                 vcp_sg_bdr_v0_0_m_ctrl_1;	//0x0684
	PE_O20_VCP_SG_BDR_V0_0_M_CTRL_2_T                 vcp_sg_bdr_v0_0_m_ctrl_2;	//0x0688
	UINT32                                            reserved09;	//0x068C-0x068C
	PE_O20_VCP_SG_BDR_V0_1_M_CTRL_0_T                 vcp_sg_bdr_v0_1_m_ctrl_0;	//0x0690
	PE_O20_VCP_SG_BDR_V0_1_M_CTRL_1_T                 vcp_sg_bdr_v0_1_m_ctrl_1;	//0x0694
	PE_O20_VCP_SG_BDR_V0_1_M_CTRL_2_T                 vcp_sg_bdr_v0_1_m_ctrl_2;	//0x0698
	UINT32                                            reserved010[9];	//0x069C-0x06BC
	PE_O20_VCP_SG_BDR_V1_0_M_CTRL_0_T                 vcp_sg_bdr_v1_0_m_ctrl_0;	//0x06C0
	PE_O20_VCP_SG_BDR_V1_0_M_CTRL_1_T                 vcp_sg_bdr_v1_0_m_ctrl_1;	//0x06C4
	PE_O20_VCP_SG_BDR_V1_0_M_CTRL_2_T                 vcp_sg_bdr_v1_0_m_ctrl_2;	//0x06C8
	UINT32                                            reserved011;	//0x06CC-0x06CC
	PE_O20_VCP_SG_BDR_V1_1_M_CTRL_0_T                 vcp_sg_bdr_v1_1_m_ctrl_0;	//0x06D0
	PE_O20_VCP_SG_BDR_V1_1_M_CTRL_1_T                 vcp_sg_bdr_v1_1_m_ctrl_1;	//0x06D4
	PE_O20_VCP_SG_BDR_V1_1_M_CTRL_2_T                 vcp_sg_bdr_v1_1_m_ctrl_2;	//0x06D8
	UINT32                                            reserved012[41];	//0x06DC-0x077C
	PE_O20_VCP_WCP_M_REC5_POS_X_T                     vcp_wcp_m_rec5_pos_x;	//0x0780
	PE_O20_VCP_WCP_M_REC5_POS_Y_T                     vcp_wcp_m_rec5_pos_y;	//0x0784
	PE_O20_VCP_WCP_M_REC5_CLR_T                       vcp_wcp_m_rec5_clr;	//0x0788
	PE_O20_VCP_WCP_M_REC6_POS_X_T                     vcp_wcp_m_rec6_pos_x;	//0x078C
	PE_O20_VCP_WCP_M_REC6_POS_Y_T                     vcp_wcp_m_rec6_pos_y;	//0x0790
	PE_O20_VCP_WCP_M_REC6_CLR_T                       vcp_wcp_m_rec6_clr;	//0x0794
	PE_O20_VCP_WCP_M_REC7_POS_X_T                     vcp_wcp_m_rec7_pos_x;	//0x0798
	PE_O20_VCP_WCP_M_REC7_POS_Y_T                     vcp_wcp_m_rec7_pos_y;	//0x079C
	PE_O20_VCP_WCP_M_REC7_CLR_T                       vcp_wcp_m_rec7_clr;	//0x07A0
	PE_O20_VCP_WCP_M_REC8_POS_X_T                     vcp_wcp_m_rec8_pos_x;	//0x07A4
	PE_O20_VCP_WCP_M_REC8_POS_Y_T                     vcp_wcp_m_rec8_pos_y;	//0x07A8
	PE_O20_VCP_WCP_M_REC8_CLR_T                       vcp_wcp_m_rec8_clr;	//0x07AC
	PE_O20_VCP_WCP_M_REC9_POS_X_T                     vcp_wcp_m_rec9_pos_x;	//0x07B0
	PE_O20_VCP_WCP_M_REC9_POS_Y_T                     vcp_wcp_m_rec9_pos_y;	//0x07B4
	PE_O20_VCP_WCP_M_REC9_CLR_T                       vcp_wcp_m_rec9_clr;	//0x07B8
	UINT32                                            reserved013[2];	//0x07BC-0x07C0
	PE_O20_VCP_WCP_MS_CTRL_10_T                       vcp_wcp_ms_ctrl_10;	//0x07C4
	UINT32                                            reserved014;	//0x07C8-0x07C8
	UINT32                                            reserved243[13];	//0x7cc-0x7fc
	PE_O20_VCP_WCP_ALPHA_CTRL_T                       vcp_wcp_alpha_ctrl;	//0x0800
	PE_O20_VCP_WCP_ALPHA_GEN_Y_0_T                    vcp_wcp_alpha_gen_y_0;	//0x0804
	PE_O20_VCP_WCP_ALPHA_GEN_Y_1_T                    vcp_wcp_alpha_gen_y_1;	//0x0808
	PE_O20_VCP_WCP_ALPHA_GEN_Y_2_T                    vcp_wcp_alpha_gen_y_2;	//0x080C
	PE_O20_VCP_WCP_ALPHA_GEN_Y_3_T                    vcp_wcp_alpha_gen_y_3;	//0x0810
	PE_O20_VCP_WCP_ALPHA_GEN_Y_4_T                    vcp_wcp_alpha_gen_y_4;	//0x0814
	PE_O20_VCP_WCP_ALPHA_GEN_Y_5_T                    vcp_wcp_alpha_gen_y_5;	//0x0818
	PE_O20_VCP_WCP_ALPHA_GEN_C_0_T                    vcp_wcp_alpha_gen_c_0;	//0x081C
	PE_O20_VCP_WCP_ALPHA_GEN_C_1_T                    vcp_wcp_alpha_gen_c_1;	//0x0820
	PE_O20_VCP_WCP_ALPHA_GEN_C_2_T                    vcp_wcp_alpha_gen_c_2;	//0x0824
	PE_O20_VCP_WCP_ALPHA_GEN_C_3_T                    vcp_wcp_alpha_gen_c_3;	//0x0828
	PE_O20_VCP_WCP_ALPHA_GEN_C_4_T                    vcp_wcp_alpha_gen_c_4;	//0x082C
	PE_O20_VCP_WCP_ALPHA_GEN_C_5_T                    vcp_wcp_alpha_gen_c_5;	//0x0830
	PE_O20_VCP_WCP_M_REC2_POS_X_T                     vcp_wcp_m_rec2_pos_x;	//0x0834
	PE_O20_VCP_WCP_M_REC2_POS_Y_T                     vcp_wcp_m_rec2_pos_y;	//0x0838
	PE_O20_VCP_WCP_M_REC3_POS_X_T                     vcp_wcp_m_rec3_pos_x;	//0x083C
	PE_O20_VCP_WCP_M_REC3_POS_Y_T                     vcp_wcp_m_rec3_pos_y;	//0x0840
	PE_O20_VCP_WCP_M_REC4_POS_X_T                     vcp_wcp_m_rec4_pos_x;	//0x0844
	PE_O20_VCP_WCP_M_REC4_POS_Y_T                     vcp_wcp_m_rec4_pos_y;	//0x0848
	PE_O20_VCP_WCP_M_REC0_CLR_T                       vcp_wcp_m_rec0_clr;	//0x084C
	PE_O20_VCP_WCP_M_REC1_CLR_T                       vcp_wcp_m_rec1_clr;	//0x0850
	PE_O20_VCP_WCP_M_REC2_CLR_T                       vcp_wcp_m_rec2_clr;	//0x0854
	PE_O20_VCP_WCP_M_REC3_CLR_T                       vcp_wcp_m_rec3_clr;	//0x0858
	PE_O20_VCP_WCP_M_REC4_CLR_T                       vcp_wcp_m_rec4_clr;	//0x085C
	PE_O20_VCP_VSP_U0_CTRL_00_T                       vcp_vsp_u0_ctrl_00;	//0x0860
	PE_O20_VCP_VSP_U0_CTRL_01_T                       vcp_vsp_u0_ctrl_01;	//0x0864
	PE_O20_VCP_VSP_U1_CTRL_00_T                       vcp_vsp_u1_ctrl_00;	//0x0868
	PE_O20_VCP_VSP_U1_CTRL_01_T                       vcp_vsp_u1_ctrl_01;	//0x086C
	PE_O20_VCP_CRC_CTRL_T                             vcp_crc_ctrl;	//0x0870
	PE_O20_VCP_CRC_DATA_MASK0_T                       vcp_crc_data_mask0;	//0x0874
	PE_O20_VCP_CRC_DATA_MASK1_T                       vcp_crc_data_mask1;	//0x0878
	UINT32                                            reserved015[2];	//0x087C-0x0880
	PE_O20_VCP_CRC_OUT0_T                             vcp_crc_out0;	//0x0884
	PE_O20_VCP_CRC_OUT1_T                             vcp_crc_out1;	//0x0888
	UINT32                                            reserved016[5];	//0x088C-0x089C
	PE_O20_VCP_SG_MVY_CTRL_A_T                        vcp_sg_mvy_ctrl_a;	//0x08A0
	PE_O20_VCP_SG_MVC_CTRL_A_T                        vcp_sg_mvc_ctrl_a;	//0x08A4
	PE_O20_VCP_SG_SVY_CTRL_A_T                        vcp_sg_svy_ctrl_a;	//0x08A8
	PE_O20_VCP_SG_SVC_CTRL_A_T                        vcp_sg_svc_ctrl_a;	//0x08AC
	UINT32                                            reserved017;	//0x08B0-0x08B0
	UINT32                                            reserved288[19];	//0x8b4-0x8fc
	PE_O20_VCP_DISP_INTR_MASK_T                       vcp_disp_intr_mask;	//0x0900
	PE_O20_VCP_DISP_INTR_CLEAR_T                      vcp_disp_intr_clear;	//0x0904
	PE_O20_VCP_DISP_INTR_STATUS_T                     vcp_disp_intr_status;	//0x0908
	PE_O20_VCP_DISP_INTR0_POS_MV_Y_T                  vcp_disp_intr0_pos_mv_y;	//0x090C
	PE_O20_VCP_DISP_INTR1_POS_MV_Y_T                  vcp_disp_intr1_pos_mv_y;	//0x0910
	PE_O20_VCP_DISP_INTR0_POS_MV_C_T                  vcp_disp_intr0_pos_mv_c;	//0x0914
	PE_O20_VCP_DISP_INTR1_POS_MV_C_T                  vcp_disp_intr1_pos_mv_c;	//0x0918
	PE_O20_VCP_DISP_INTR0_POS_SV_Y_T                  vcp_disp_intr0_pos_sv_y;	//0x091C
	PE_O20_VCP_DISP_INTR1_POS_SV_Y_T                  vcp_disp_intr1_pos_sv_y;	//0x0920
	PE_O20_VCP_DISP_INTR0_POS_SV_C_T                  vcp_disp_intr0_pos_sv_c;	//0x0924
	PE_O20_VCP_DISP_INTR1_POS_SV_C_T                  vcp_disp_intr1_pos_sv_c;	//0x0928
	PE_O20_VCP_DISP_INTR_SRC_SEL_T                    vcp_disp_intr_src_sel;	//0x092C
	PE_O20_VCP_U0_CSC_CTRL7_T                         vcp_u0_csc_ctrl7;	//0x0930
	PE_O20_VCP_CSC_CTRL0_T                                csc_ctrl0;	//0x0934
	PE_O20_VCP_CSC_CTRL1_T                                csc_ctrl1;	//0x0938
	PE_O20_VCP_CSC_CTRL2_T                                csc_ctrl2;	//0x093C
	PE_O20_VCP_CSC_CTRL3_T                                csc_ctrl3;	//0x0940
	PE_O20_VCP_CSC_CTRL4_T                                csc_ctrl4;	//0x0944
	PE_O20_VCP_CSC_CTRL5_T                                csc_ctrl5;	//0x0948
	PE_O20_VCP_CSC_CTRL6_T                                csc_ctrl6;	//0x094C
	PE_O20_VCP_U1_CSC_CTRL7_T                         vcp_u1_csc_ctrl7;	//0x0950
	PE_O20_VCP_ACTIVE_LINE_CNT_T                      vcp_active_line_cnt;	//0x0954
}PE_VCP_DISP_REG_O20_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC463F00 RW 0x0000_0000
	UINT32 head_apl                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 body_apl                   :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O20_VSD_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC463F04 RW 0x0000_0000
	UINT32 head_map                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 depth_map                  :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O20_VSD_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900B808 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//15:8	//
	UINT32 contrast                         :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_O20_VSD_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900B80C RW
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//15:8	//
	UINT32 brightness                       :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_O20_VSD_VERI_SYS_VERI_3_T;

typedef struct {
	PE_O20_VSD_VERI_SYS_VERI_0_T                                sys_veri_0;	//0xC900B800
	PE_O20_VSD_VERI_SYS_VERI_1_T                                sys_veri_1;	//0xC900B804
	PE_O20_VSD_VERI_SYS_VERI_2_T                                sys_veri_2;	//0xC900B808
	PE_O20_VSD_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xC900B80C
}PE_VSD_VERI_REG_O20_T;

#endif
